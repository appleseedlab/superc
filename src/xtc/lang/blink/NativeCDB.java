package xtc.lang.blink;

import java.io.IOException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import xtc.lang.blink.CallStack.LocalVariable;
import xtc.lang.blink.CallStack.NativeCallFrame;
import xtc.lang.blink.CallStack.NativeCallFrame.NativeFrameType;
import xtc.lang.blink.Event.DummyCallCompletionEvent;
import xtc.lang.blink.Event.Java2NativeCallEvent;
import xtc.lang.blink.Event.Java2NativeReturnEvent;
import xtc.lang.blink.Event.Native2JavaCallEvent;
import xtc.lang.blink.Event.J2CBreakPointHitEvent;
import xtc.lang.blink.Event.Native2JavaCompletionEvent;
import xtc.lang.blink.Event.Native2JavaReturnEvent;
import xtc.lang.blink.Event.NativeBreakPointHitEvent;
import xtc.lang.blink.Event.NativeJNIWarningEvent;
import xtc.lang.blink.Event.NativeStepCompletionEvent;
import xtc.lang.blink.Event.RawTextMessageEvent;
import xtc.lang.blink.EventLoop.ReplyHandler;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.agent.AgentNativeDeclaration;

/** Microsoft CDB driver as a native component debugger. */
public class NativeCDB extends StdIOProcess
  implements NativeDebugger, AgentNativeDeclaration  {

  /** CDB user command prompt. */
  private static final String PROMPT_PATTERN = "\\d+\\:\\d+\\> ";

  /** The pattern cache. */
  private static final HashMap<String,Pattern> patternCache = 
    new HashMap<String,Pattern>();

  /**
   * Find or create regular expression pattern.
   * @param patternString The pattern string.
   * @return The regular expression pattern.
   */
  private static final Pattern p(String patternString) {
    Pattern pattern = patternCache.get(patternString);
    if (pattern == null) {
      pattern = Pattern.compile(patternString);
      patternCache.put(patternString, pattern);
    }
    return pattern;
  }

  /** CDB internal event to notify that CDB is attached to the target JVM. */
  private static class CDBAttachEvent extends Event {
    CDBAttachEvent(NativeCDB g) {
      super(g, EventConsumer.BlinkController);
    }
    public String getName() {return "CDBAttachEvent";}
  }

  /** CDB internal output message event. */
  private static class CDBRawMessageEvent extends Event {
    private final String message;
    CDBRawMessageEvent(NativeCDB g, String message) {
      super(g, EventConsumer.BlinkController);
      this.message = message;
    }    
    public String getMessage() {return message;}
    public String getName() {return "CDBRawMessageEvent";}
    public String toString() {
      return super.toString() + message;
    }
  }

  /**
   * Debug agent's internal breakpoint hit event. This internal event could be
   * interpreted as on one of the DebugContextSwitching events and Language
   * transition events.
   */
  private static class AgentBreakPointHitEvent extends Event {
    private final int bpID; //CDB break point identifier.
    private final String message; //CDB's detailed message.
    AgentBreakPointHitEvent(NativeCDB g, int bpID, String message) {
      super(g, EventConsumer.NativerDebugger);
      this.bpID = bpID;
      this.message = message;
    }
    /** Getters. */
    public int getBpID() {return bpID;}
    public String getMessage() {return message;}
    public String getName() {return "AgentInternalBreakPointHit";}
  }

  /** Internal step completion event. */
  private static class InternalStepCompletionEvent extends Event {
	InternalStepCompletionEvent(NativeCDB g) {
      super(g, EventConsumer.NativerDebugger);
     }
	public String getName() {return "InternalStepCompletionEvent";}
  }

  /** The internal native breakpoint within Blink agent. */
  private int cbpBreakPointId;

  /** Beginning of the Agent native shared library. */
  private long agent_address_begin;

  /** Ending of the Agent native shared library. */
  private long agent_address_end;

  /** The next break point identifier. */
  private int nextBreakPointIdentifier;

  /** Whether or not the CDB is attached to the JVM debugee. */
  private boolean cdbAttached = false;

  /** Whether or not this CDB driver activated xtc.lang.agent.Agent.dummyJava. */
  private volatile boolean callDummyRequested = false;

  /** 
   * Whether or not this CDB driver yielded to Java debugger by activating a
   * call to xtc.lang.agent.Agent.c2j().
   */
  private volatile boolean callNative2JavaRequested = false;

  /**
   * Whether or not the CDB source-level single-stepping was requested and is
   * being processed.
   */
  private volatile boolean stepRequested = false;

  /**
   * Internal raw message buffer to capture interesting event such as break
   * point hit. See processMeaageEvent. This buffer chops CDB's raw output text
   * message by CDB's prompt.
   */
  private final StringBuffer sbStdout = new StringBuffer();

  /**
   * Constructor.
   *
   * @param dbg The Blink debugger.
   * @param name The user friendly name.
   */
  public NativeCDB(Blink dbg, String name) {
    super(dbg, name);
  }

  /**
   * Process message for internal processing.
   *
   * @param e The event.
   */
  void processMessageEvent(RawTextMessageEvent e) {
    sbStdout.append(e.getMessage());
    Pattern p1 = Pattern.compile(PROMPT_PATTERN);
    Matcher m1 = p1.matcher(sbStdout);
    if (m1.find()) {
      boolean hasReminder = !Pattern.compile("(?:.*\n)*" + PROMPT_PATTERN + "$")
          .matcher(sbStdout).matches();
      String[] frags = p1.split(sbStdout);
      for(int i = 0; i < frags.length-1;i++) {
        processCDBRawMessage(frags[i]);
      }
      String lastOne = frags.length > 0 ? frags[frags.length-1] :"";
      if (hasReminder) {
        sbStdout.setLength(0);
        sbStdout.append(lastOne);
      } else {
        processCDBRawMessage(lastOne);
        sbStdout.setLength(0);
      }
    }
  }

  /**
   * Process a CDB raw message. 
   *
   * @param s The message. 
   */
  private void processCDBRawMessage(String s) {
    if (!cdbAttached) {
      dbg.enqueEvent(new CDBAttachEvent(this));
      cdbAttached = true;
      return;
    }

    //now check any interesting event.
    Pattern breakpointHitPattern = p("(?:.*\n)*Breakpoint (\\d+) hit\n" + "((?:.*\n)*)");
    Matcher breakpointHitMatcher = breakpointHitPattern.matcher(s); 
    if (breakpointHitMatcher.find()) {
      int bpid = Integer.parseInt(breakpointHitMatcher.group(1));
      String msg = breakpointHitMatcher.group(2);
      stepRequested = false;
      //check internal break point hit.
      if (bpid == cbpBreakPointId) {
        dbg.enqueEvent(new AgentBreakPointHitEvent(this, bpid, msg));
      } else {
        // visible native break point.
        dbg.enqueEvent(new NativeBreakPointHitEvent(this, bpid, msg));
      }
      return;
    }
    if (callDummyRequested || callNative2JavaRequested) {
      Pattern callReturnPattern = p(".call returns:\n" + "(.+)\\n" + "(?:.*\n)*");
      Matcher callReturnMatcher = callReturnPattern.matcher(s);
      if (callReturnMatcher.find()) {
        assert callDummyRequested ^ callNative2JavaRequested;
        if (callDummyRequested) {
          callDummyRequested = false;
          dbg.enqueEvent(new DummyCallCompletionEvent(this));
        } else if (callNative2JavaRequested) {
          callNative2JavaRequested = false;
          dbg.enqueEvent(new Native2JavaCompletionEvent(this));
        }
        return;
      }
    }
    if (stepRequested) {
    	dbg.enqueEvent(new InternalStepCompletionEvent(this));
      stepRequested = false;
      return;
    } 
    dbg.enqueEvent(new CDBRawMessageEvent(this, s));
  }

  /**
   *  Process an event in the main thread.
   *
   *  @param e The event.
   */
  public void dispatch(Event e) {
    if (e instanceof AgentBreakPointHitEvent) {
      dispatch((AgentBreakPointHitEvent)e);
    } else if (e instanceof InternalStepCompletionEvent) {
    	String eipString = raeLine("r eip\n", "eip=([0-9a-f]+)")[1];
      long eip = Long.parseLong(eipString, 16);
      assert agent_address_begin != 0L && agent_address_end != 0L;
      if (isInAgentLibrary(eip)) {
      	sendMessage("G\n");
      } else {
      	dbg.enqueEvent(new NativeStepCompletionEvent(this));
      }
    }
  }

  /**
   * Process an internal agent breakpoint hit event in the event handler
   * thread.
   * 
   * @param e The event.
   */
  private void dispatch(AgentBreakPointHitEvent e) {
    if (e.getBpID() == cbpBreakPointId) {
      String bptype = readEnum(BDA_CBP_BPTYPE);
      if (bptype.equals(BDA_BPTYPE_J2C_DEBUGGER)) {
        dbg.enqueEvent(new J2CBreakPointHitEvent(this));
      } else if (bptype.equals(BDA_BPTYPE_J2C_JNI_CALL)) {
        long native_target_address = readAddressValue(BDA_CBP_TARGET_NATIVE_ADDRESS);
        advance(native_target_address);
        rae("t\n");
        dbg.enqueEvent(new Java2NativeCallEvent(this));
      } else if (bptype.equals(BDA_BPTYPE_J2C_JNI_RETURN)) {
        String cname = readStringValue(BDA_CBP_TARGET_CNAME);
        int lineNumber = readIntValue(BDA_CBP_TARGET_LINE_NUMBER);
        dbg.enqueEvent(new Java2NativeReturnEvent(this, cname, lineNumber));
      } else if (bptype.equals(BDA_BPTYPE_C2J_JNI_CALL)) {
        String cname = readStringValue(BDA_CBP_TARGET_CNAME);
        int lineNumber = readIntValue(BDA_CBP_TARGET_LINE_NUMBER);
        dbg.enqueEvent(new Native2JavaCallEvent(this, cname, lineNumber));
      } else if (bptype.equals(BDA_BPTYPE_C2J_JNI_RETURN)) {
        rae("gu\n"); // bda_cbp -> jni_state_c2j_return
        rae("gu\n"); // jni_state_c2j_return -> c2j_proxyCallXXXMethod
        rae("gu\n"); // caller of the (*env)->CallXXXMethod
        dbg.enqueEvent(new Native2JavaReturnEvent(this));
      } else if (bptype.equals(BDA_BPTYPE_JNI_WARNING)) {
        String message = readStringValue(BDA_CBP_STATE_MESSAGE);
        dbg.enqueEvent(new NativeJNIWarningEvent(this, message));
      } else {
        assert false : "can not recognize an internal break point";            
      }
    } else {
      assert false : "can not recognize an internal break point";
    }
  }

  /** 
   * Read a string typed value.
   * @param name The variable name.
   * @return The string value.
   */
  private String readStringValue(String name)  {
    String s = raeLine("?? " + name + "\n", " \"(.+)\"")[1];
    return s;
  }

  /**
   * Read an integer typed value.
   * @param name The variable name.
   * @return The integer value.
   */
  private int readIntValue(String name)  {
   String s = raeLine("?? " + name + "\n", "int ([0-9]+)")[1];
    return Integer.parseInt(s);
  }

  /**
   * Read an address typed value.
   * @param name The variable name.
   * @return The address.
   */
  private long readAddressValue(String name)  {
    String s = raeLine("?? " + name + "\n", "^.+0x([0-9a-f]+)$")[1];
    return Long.parseLong(s, 16);
  }

  /**
   * Read an enumeration typed value.
   * @param name The variable name.
   * @return The enumeration name.
   */
  private String readEnum(String name)  {
    return raeLine("?? " + name + "\n", "^.+ (.+) .*$")[1];
  }

  /**
   * Attach CDB to the debugee JVM.
   * @param pid The process id of the debbugee.
   */
  public void attach(int pid)  {
    final String[] cdbCommandArray = new String[] {
        "cdb",
        "-lines", 
        "-G",
        "-pid", String.valueOf(pid),
    };
    begin(cdbCommandArray);
    EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof CDBAttachEvent) {
          return true;
        } else {
          return false;
        }
      }
    });

    cbpBreakPointId = createSymbolBreakPoint(BDA_CBP);
    nextBreakPointIdentifier = cbpBreakPointId + 1;

    Pattern p = Pattern.compile("([0-9a-f]+) ([0-9a-f]+) +([^ ]+) +.+");
    String sharedLibries = rae("lm\n");
    for (StringTokenizer t = new StringTokenizer(sharedLibries, "\n"); t
    .hasMoreElements();) {
    	Matcher m = p.matcher(t.nextToken());
    	if (m.matches()) {
    		String name = m.group(3);
    		if (name.equals("jdwp")) {
    			String begin = m.group(1);
    			String end = m.group(2);
    		    setVariable(BDA_JDWP_REGION_BEGIN_VARIABLE, begin);
    		    setVariable(BDA_JDWP_REGION_END_VARIABLE, end);
    		} else if (name.equals(BDA_SHARED_LIBRARY_NAME)) {
    	        String begin = m.group(1);
    	        String end = m.group(2);
    	        agent_address_begin = Long.parseLong(begin, 16);
    	        agent_address_end = Long.parseLong(end, 16);	
    		}
    	}
    }
    sendMessage("G\n");
  }

  /** Detach and terminate the CDB. */
  public void detach()  {
    sendMessage(".detach\nQ\n");
  }

  /** Active a native-to-Java transition. */
  public void callNative2Java()  {
    String callCommand = ".call " + BDA_C2J +"()\n";
    rae(callCommand);
    callNative2JavaRequested = true;
    sendMessage("G\n");
  }

  /** Continue the debugee JVM. */
  public void cont()  {
    sendMessage("G\n");
  }

  /** Abruptly termindate the debugee JVM. */
  public void quit()  {
    sendMessage("Q\n");
  }

  /**
   * Run a CDB command and return the output message. This is for
   * internal-debugging purpose.
   * 
   * @param command The CDB command.
   */
  public String runCommand(String command)  {
    return rae(command + "\n");
  }

  /**
   * Create a native breakpoint, and return the breaakpoint identifier.
   *
   * @param sourceFile The source file.
   * @param line The line number.
   * @return The breakpoint identifier.
   */
  public int createBreakpoint(String sourceFile, int line)  {
    int bpid = nextBreakPointID();
    String cmd ="bp" + bpid + " `" + sourceFile + ":" + line +"`\n";
    String rst = rae(cmd);
    if (rst != null && rst.length() > 0) {
      dbg.out("%s", rst); // perhaps some problem.
    }
    return bpid;
  }

  public int createBreakpoint(String symbol)  {
    int bpid = nextBreakPointID();
    String cmd ="bp" + bpid + " " + symbol + "\n";
    String rst = rae(cmd);
    if (rst != null && rst.length() > 0) {
      dbg.out("%s", rst); // perhaps some problem.
    }
    return bpid;    
  }

  /**
   * Create a native breakpiont, and return the breakpoint identifier.
   * 
   * @param symbol The symbol name.
   * @return The breakpoint identifier.
   */
  private int createSymbolBreakPoint(String symbol)  {
    String[] rsts = raeLine(
        "bm " + symbol + "\n",
        "^\\s*(\\d+)\\: \\p{XDigit}+ \\@\\!\"(.+)\"$"
    );
    int bpid = Integer.valueOf(rsts[1]);
    return bpid;
  }

  /**
   * Get a new  breakpiont identifier.
   *
   * @return The breakpint identifier.
   */
  private int nextBreakPointID() {
    return nextBreakPointIdentifier++;
  }
  
  
  /**
   * Advance the program counter to a specified address.
   * 
   * @param address The target native address.
   */
  private void advance(long address)  {
	 final int bpid = nextBreakPointID(); 
	 rae("bp" + bpid + " /1 " + Long.toHexString(address) + "\n");
	 sendMessage("g\n");
	 EventLoop.subLoop(dbg, new ReplyHandler() {
	   public boolean dispatch(Event e) {
	     if (e instanceof NativeBreakPointHitEvent) {
	    	 NativeBreakPointHitEvent ne = (NativeBreakPointHitEvent)e;
	    	 if (bpid == ne.getDebuggerBreakpointID()) {
	    		 return true;
	    	 }
	     }
	     return false;
	   }
	 });
  }

  /**
   * Enable a breakpoint.
   *
   * @param bpid The breakpoint identifier.
   */
  public void enableBreakpoint(int bpid)  {
    rae("be " + bpid + "\n");
  }

  /**
   * Disable a breakpoint.
   *
   * @param bpid The breakpoint identifier.
   */
  public void disableBreakpoint(int bpid)  {
    rae("bd " + bpid + "\n");
  }

  /**
   * Delete a breakpoint.
   * @param bpid The breakpoint identifier.
   */
  public void deleteBreakpoint(int bpid)  {
    assert false : "Not implemented";    
  }

  /** Followings are for inspecting calling context and program state.*/
  public List<NativeCallFrame> getFrames()  {
    // extract frames
    String framesText = rae("kn\n");
    LinkedList<NativeCallFrame> frames = new LinkedList<NativeCallFrame>();
    for (StringTokenizer t = new StringTokenizer(framesText, "\n"); t
        .hasMoreElements();) {
      String l = t.nextToken();
      Pattern p = p("^(\\p{XDigit}+) (\\p{XDigit}+) (\\p{XDigit}+) (\\S+)(?: (\\[.+\\]))?");
      Matcher m = p.matcher(l);
      if (m.matches()) {
        int frameID = Integer.valueOf(m.group(1), 16);
        String position = m.group(4);
        String sourceInfo = m.group(5);

        //parse position
        String functionName;
        NativeFrameType frameType = NativeFrameType.NORMAL;
        Pattern posPattern = p("(.+)\\!(.+)(?:\\+0x(\\p{XDigit}+))?|(.+)\\+0x(\\p{XDigit}+)|0x(\\p{XDigit}+)");
        Matcher posMatcher = posPattern.matcher(position);
        boolean matched = posMatcher.matches();
        assert matched == true : "can not parse position: " + position + "\n";
        if (posMatcher.group(1) != null) {
          String moduleName = posMatcher.group(1);
          String funcName = posMatcher.group(2);
          functionName = funcName;
          if (moduleName.equals(BDA_SHARED_LIBRARY_NAME)) {
            if (funcName.startsWith("bda_j2c_proxy")) {
              frameType = NativeFrameType.J2C_PROXY;
            } else if (funcName.startsWith("bda_c2j_proxy")) {
              frameType = NativeFrameType.C2J_PROXY;
            } 
          }
        } else if (posMatcher.group(4) != null) {
          String moduleName = posMatcher.group(4);
          int moduleOffset = Integer.parseInt(posMatcher.group(5), 16);
          functionName = moduleName + "+0x" + Integer.toHexString(moduleOffset);
        } else {
          //raw address
          assert posMatcher.group(6) != null; 
          functionName = "0x" + posMatcher.group(6);
        }

        //parse sourceInfo
        String sourceFile = null;
        int lineno = 1;
        if (sourceInfo!= null) {
          Pattern frameSourceInfoPattern = p("\\[(.+) \\@ ([0-9]+)\\]");
          Matcher frameSourceInfoMatcher = frameSourceInfoPattern.matcher(sourceInfo);
          if (frameSourceInfoMatcher.matches()) {
            sourceFile = frameSourceInfoMatcher.group(1);
            lineno = Integer.parseInt(frameSourceInfoMatcher.group(2));
          } 
        }

        NativeCallFrame frame = new NativeCallFrame(frameID, functionName, sourceFile, lineno,
            frameType);
        frames.addLast(frame);
      } else if (l.matches("^WARNING: .+$")) {
      } else if (l.matches("\\s+#\\s+ChildEBP\\s+RetAddr\\s*")) {
        //skip header.
      } else {
        assert false :"can not recognize CDB output: " + l;
      }
    }
    return frames;
  }

  public SourceFileAndLine getCurrentLocation()  {
    SourceFileAndLine loc = null;    
    String frames = rae("kn1\n");
    Pattern p = Pattern.compile("0+ [0-9a-f]+ [0-9a-f]+ .+ \\[(.+) @ ([0-9]+)\\]");
    StringTokenizer t = new StringTokenizer(frames, "\n");
    while(t.hasMoreTokens()) {
    	String s = t.nextToken();
    	Matcher m = p.matcher(s);
    	if (m.matches()) {
    		String file = m.group(1);
    		int line = Integer.parseInt(m.group(2));
    		loc = new SourceFileAndLine(file, line);
    	}
    }
    return loc;
  }

  public String getSourceLines(String filename, int line, int count)  {
    assert filename != null && line >=0 && count >=0;
    rae("lsf " + filename + "\n");
    String lines = rae("ls " + line + ", " + count + "\n");
    return lines;
  }

  public List<LocalVariable> getLocals(NativeCallFrame f)  {
    LinkedList<LocalVariable> localList = new LinkedList<LocalVariable>();
	  rae(".frame " + f.getFrameID() + "\n");
	  String localsText = rae("dv\n");
	  Pattern localVariablePattern = Pattern.compile("^\\s*(.+) = (.+)$");
	  for(StringTokenizer t = new StringTokenizer(localsText, "\n");
	  t.hasMoreElements();) {
	    String l = t.nextToken();
	    Matcher m = localVariablePattern.matcher(l);
	    if (m.matches()) {
	      String name = m.group(1);
	      String value = m.group(2);
	      LocalVariable v = new LocalVariable(name, value);
	      localList.addLast(v);
	    } else
	      assert false : "CDB: can not recognize: " + l + "\n";
	    }
    return localList;
  }

  /* Followings are for inter-language stepping. */
  public void step()  {
    rae("l+t\n");
    stepRequested = true;
    sendMessage("t\n");
  }

  public void next()  {
    rae("l+t\n");
    stepRequested = true;
    sendMessage("p\n");
  }

  public int getLanguageTransitionCount()  {
	rae(".call " + BDA_GET_CURRENT_TRANSITION_COUNT + "()\n");
	String countString = raeLine("g\n", "int (\\d+)")[1];
	return Integer.parseInt(countString);
  }

  private static String getBreakpointControlVariable(LanguageTransitionEventType bptype) {
    switch (bptype) {
    case J2C_CALL:
      return BDA_J2C_CALL_BREAKPOINT_VARIABLE;
    case J2C_RETURN:
      return BDA_J2C_RETURN_BREAKPOINT_VARIABLE;
    case C2J_CALL:
      return BDA_C2J_CALL_BREAKPOINT_VARIABLE;
    case C2J_RETURN:
      return BDA_C2J_RETURN_BREAKPOINT_VARIABLE;
    default:
      assert false : "not reachable";
      return "";
    }
  }

  public void setTransitionBreakPoint(LanguageTransitionEventType bptype, int transitionCount)
     {
    String controlVariable = getBreakpointControlVariable(bptype);
    rae("ed " + controlVariable + " 1\n");
    rae("ed " + BDA_TRANSITION_COUNT + "  " + transitionCount +"\n");
  }

  public void clearTransitionBreakPoint(LanguageTransitionEventType bptype)
     {
    String controlVariable = getBreakpointControlVariable(bptype);
    rae("ed " + controlVariable + " 0\n");
  }

  public void callJavaDummy()  {
    rae(".call " + BDA_DUMMY_JAVA + "()" + "\n");
    callDummyRequested = true;
    sendMessage("g\n");
  }

  private boolean isInAgentLibrary(long addr) {
	    return agent_address_begin <= addr && addr < agent_address_end; 
	  }

  /** Following are for expression evaluation. */
  public String eval(NativeCallFrame f, String expr)  {
    assert false : "Not implemented";
    return null;
  }

  public void setVariable(NativeCallFrame f, String name, String expr)
       {
    assert false : "Not implemented";
  }

  public String whatis(NativeCallFrame f, String expr)  {
    assert false : "Not implemented";
    return null;
  }

  private void setVariable(String name, String value)  {
	  rae("ed " + name + " " + value +"\n");
  }

  /**
   * Run a CDB command, and get text message from the CDB.
   * 
   * @param cmd The command.
   * @return The result message.
   */
  private String rae(final String cmd)  {
    sendMessage(cmd);
    return (String) EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof CDBRawMessageEvent) {
          CDBRawMessageEvent ge =(CDBRawMessageEvent)e;
          setResult(ge.getMessage());
            return true;
        } 
        return false;
      }
    });
  }

  /**
   * Run a CDB command and search for a expected line until the CDB prompt. At
   * the end, return an array of Strings from the matching regular expression.
   * If multiple CDB output lines match the expected message, take the last one.
   * 
   * @param cmd The command.
   * @param expect The expected line.
   * @return The matcher object.
   */
  private String[] raeLine(final String cmd, final String expect)  {   
    final Pattern p = Pattern.compile(expect);
    sendMessage(cmd);
    return (String[]) EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof CDBRawMessageEvent) {
          CDBRawMessageEvent ge =(CDBRawMessageEvent)e;
          String[] lines = ge.getMessage().split("\n");
          for(String l :lines) {
            Matcher m = p.matcher(l);
            if (m.matches()) {
              String[] frags = new String[m.groupCount()+1];
              for(int i = 0; i <= m.groupCount();i++) {
                frags[i] = m.group(i); 
              }
              setResult(frags);
              return true;
            }
          }
          setResult(null);
          return true;
        }
        return false;
      }
    });
  }

  private int nextVCIdentifier = 0;

  public String getNewCTmpVarIdentifier() {
    return "$vc" + nextVCIdentifier++;
  }
  
  public void resetConvenienceVariables() { 
    nextVCIdentifier = 0;
  }

}
