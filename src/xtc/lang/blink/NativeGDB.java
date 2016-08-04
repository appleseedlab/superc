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
import xtc.lang.blink.Event.Native2JavaCompletionEvent;
import xtc.lang.blink.Event.EventConsumer;
import xtc.lang.blink.Event.J2CBreakPointHitEvent;
import xtc.lang.blink.Event.Native2JavaReturnEvent;
import xtc.lang.blink.Event.NativeJNIWarningEvent;
import xtc.lang.blink.Event.RawTextMessageEvent;
import xtc.lang.blink.Event.NativeBreakPointHitEvent;
import xtc.lang.blink.Event.NativeStepCompletionEvent;
import xtc.lang.blink.Event.NativeSignalEvent;
import xtc.lang.blink.EventLoop.ReplyHandler;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.agent.AgentNativeDeclaration;

/**
 * GNU GDB implementation as the native debugger.
 */
public class NativeGDB extends StdIOProcess implements NativeDebugger,
  AgentNativeDeclaration {

  private static class GDBAttachEvent extends Event {
    GDBAttachEvent(NativeGDB g) {
      super(g, EventConsumer.BlinkController);
    }
    public String getName() {return "GDBAttached";}
  }

  /**
   * Debug agent's internal break point hit event. This internal event could be
   * interpreted as on one of the DebugContextSwitching events and Language
   * transition events.
   */
  private static class BDA_CBP_BreakpointHitEvent extends Event {
    private final int bpID; // CDB break point identifier.
    private final String message; // CDB's detailed message.
    BDA_CBP_BreakpointHitEvent(NativeGDB g, int bpID, String message) {
      super(g, EventConsumer.NativerDebugger);
      this.bpID = bpID;
      this.message = message;
    }
    public int getBpID() {return bpID;}
    public String getMessage() {return message;}
    public String getName() {return "AgentInternalBreakPointHit";}
  }

  private static class InternalStepCompletionEvent extends Event {
    InternalStepCompletionEvent(NativeGDB g) {
      super(g, EventConsumer.NativerDebugger);
    }
    public String getName() {
      return "InternalStepCompletionEvent";
    }
  }

  private static class GDBRawMessageEvent extends Event {
    private final String message;
    GDBRawMessageEvent(NativeGDB g, String message) {
      super(g, EventConsumer.BlinkController);
      this.message = message;
    }
    public String getMessage() {return message;}
    public String getName() {return "GDBRawMessageEvent";}
    public String toString() {return super.toString() + message;}
  }

  /** GDB prompt. */
  private static final String PROMPT = "(gdb) ";

  /** The pattern cache. */
  private static final HashMap<String,Pattern> patternCache = 
    new HashMap<String,Pattern>();

  private static final Pattern p(String patternString) {
    Pattern pattern = patternCache.get(patternString);
    if (pattern == null) {
      pattern = Pattern.compile(patternString);
      patternCache.put(patternString, pattern);
    }
    return pattern;
  }

  private final StringBuffer sbStdout = new StringBuffer();

  /** A primitive break point inside the Blink debugging agent. */
  private int cbpBreakPointId;

  private long agent_address_begin;
  
  private long agent_address_end;
  
  private boolean gdbAttached = false;

  private volatile boolean native2JavaCallRequested = false;

  private volatile boolean callJavaDummyRequested = false;

  private volatile boolean steppingRequested = false;
    
  /**
   * @param dbg The Blink debugger.
   * @param name The user friendly name.
   */
  public NativeGDB(Blink dbg, String name) {
    super(dbg, name);
  }

  /**
   * Attach the GDB to the debugee JVM process.
   * 
   * @param pid The process identifier.
   */
  public void attach(int pid)  {
    final String[] gdbCommandArray = new String[] { "gdb", "-nw", "-quiet",
        "--pid", Integer.toString(pid), "-ex", "echo blinkgdbready\\n", };
    begin(gdbCommandArray);
    EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof GDBAttachEvent) {
          return true;
        } else {
          return false;
        }
      }
    });

    // do gdb initialization.
    raeGDB("set language c\n");
    raeGDB("set width 0\n");
    raeGDB("set step-mode on\n");
    raeGDB("set breakpoint pending on\n");
    cbpBreakPointId = createSymbolBreakPoint(BDA_CBP);

    String sharedLibries = raeGDB("info shar\n");
    Pattern p = Pattern.compile("^0x([0-9a-f]+) +0x([0-9a-f]+) +\\S(.+)$");
    for (StringTokenizer t = new StringTokenizer(sharedLibries, "\n"); t
        .hasMoreElements();) {
      Matcher m = p.matcher(t.nextToken());
      if (m.matches()) {
        String name = m.group(3);
        if (name.endsWith("libjdwp.so")||name.endsWith("jdwp.dll")) {
          String begin = m.group(1);
          String end = m.group(2);
          setVariable(BDA_JDWP_REGION_BEGIN_VARIABLE, "0x"+begin);
          setVariable(BDA_JDWP_REGION_END_VARIABLE, "0x"+end);
        } else if (name.endsWith("lib" + BDA_SHARED_LIBRARY_NAME + ".so")
          ||name.endsWith(BDA_SHARED_LIBRARY_NAME + ".dll")) {
          String begin = m.group(1);
          String end = m.group(2);
          agent_address_begin = Long.parseLong(begin, 16);
          agent_address_end = Long.parseLong(end, 16);
        }
      }
    }

    assert  agent_address_begin > 0 && (agent_address_begin < agent_address_end); 
    sendMessage("continue\n");
  }

  public void callNative2Java()  {
    native2JavaCallRequested = true;
    sendMessage("call " + BDA_C2J + "()\n");
  }

  public void step()  {
    steppingRequested = true;
    sendMessage("step\n");
  }

  public void next()  {
    steppingRequested = true;
    sendMessage("next\n");
  }

  /** trigger detach sequence. */
  public void detach()  {
    sendMessage("detach\nquit\n");
  }

  public void quit()  {
    sendMessage("kill\nquit\n");
  }

  /** Continue the debuggee's execution. */
  public void cont()  {
    sendMessage("continue\n");
  }

  public String eval(NativeCallFrame f, String expr)  {
    if (f != null) {
      raeGDB("frame " + f.getFrameID() + "\n");
    }
    Matcher m = raeGDB("print " + expr + "\n", "\\$\\d+ = (.+)\\n");
    String rst = m.group(1);
    return rst;
  }

  public void callJavaDummy()  {
    callJavaDummyRequested = true;
    sendMessage("call " + BDA_DUMMY_JAVA + "()" + "\n");
  }

  private void setVariable(String name, String value)  {
    raeGDB("set " + name + " = " + value + "\n");
  }

  public void setVariable(NativeCallFrame f, String name, String value)
       {
    raeGDB("frame " + f.getFrameID() + "\n");
    raeGDB("set " + name + " = " + value + "\n");
  }

  public int createBreakpoint(String sourceFile, int line)  {
    Matcher m = raeGDB("break " + sourceFile + ":" + line + "\n",
        "Breakpoint ([0-9]+) .*\\n");
    int bpid = Integer.valueOf(m.group(1));
    return bpid;
  }

  public int createBreakpoint(String symbol)  {
    Matcher m = raeGDB("break " + symbol + "\n", "Breakpoint ([0-9]+) .*\\n");
    int bpid = Integer.valueOf(m.group(1));
    return bpid;
  }

  public int createRawAddressBreakPoint(String address)  {
    Matcher m = raeGDB("break *" + address + "\n", "Breakpoint ([0-9]+) .*\\n");
    int bpid = Integer.valueOf(m.group(1));
    return bpid;
  }

  private int createSymbolBreakPoint(String symbol)  {
    Matcher m = raeGDB("break " + symbol + "\n",
        "(?:.*\n)*Breakpoint (\\d+) at.*\\n");
    int bpid = Integer.valueOf(m.group(1));
    return bpid;
  }

  public void enableBreakpoint(int bpid)  {
    raeGDB("enable " + bpid + "\n");
  }

  public void disableBreakpoint(int bpid)  {
    raeGDB("disable " + bpid + "\n");
  }

  public void deleteBreakpoint(int bpid)  {
    raeGDB("delete " + bpid + "\n");
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

  public int getLanguageTransitionCount()  {
    String s = raeGDB("call " + BDA_GET_CURRENT_TRANSITION_COUNT + "()\n",
        "\\$\\d+ = (\\d+)\n" + "(?:.*\n)*").group(1);
    return Integer.parseInt(s);
  }

  public void setTransitionBreakPoint(LanguageTransitionEventType bptype, int transitionCount)
       {
    String controlVariable = getBreakpointControlVariable(bptype);
    raeGDB("set " + controlVariable + " = 1\n");
    raeGDB("set " + BDA_TRANSITION_COUNT + " = " + transitionCount +"\n");
  }

  public void clearTransitionBreakPoint(LanguageTransitionEventType bptype)
       {
    String controlVariable = getBreakpointControlVariable(bptype);
    raeGDB("set " + controlVariable + " = 0\n");
  }

  public String whatis(NativeCallFrame f, String expr)  {
    raeGDB("frame " + f.getFrameID() + "\n");
    String type = raeGDB("whatis " + expr + "\n", ".+ = (.+)\\n").group(1);
    return type;
  }

  public void dispatch(Event e) {
    assert e.consumer == EventConsumer.NativerDebugger;
    if (e instanceof BDA_CBP_BreakpointHitEvent) {
      dispatch((BDA_CBP_BreakpointHitEvent) e);
    } else if (e instanceof InternalStepCompletionEvent) {
      String pc_str = raeGDB("p/x $pc\n",
          "\\s*\\$\\d+ = 0x([0-9a-f]+)\n").group(1);
      long pc = Long.parseLong(pc_str, 16);
      if (isInAgentLibrary(pc)) {
        sendMessage("continue\n");
      } else {
        dbg.enqueEvent(new NativeStepCompletionEvent(this));
      }
    }
  }

  private boolean isInAgentLibrary(long addr) {
    return agent_address_begin <= addr && addr < agent_address_end; 
  }

  private String readEnum(String name)  {
    return raeGDB("print " +name + "\n", "\\s*\\$\\d+ = (.+)\n").group(1);
  }
  
  private String readAddressValue(String name)  {
    return raeGDB(
        "print/x " + name + "\n",
        "\\s*\\$\\d+ = (0x[0-9a-f]+)\n").group(1);
  }
  private String readStringValue(String name)  {
    return raeGDB("print " + name + "\n",
    "\\s*\\$\\d+ = 0x.+ \"(.+)\"\n").group(1);
  }
  private int readIntValue(String name)  {
    String value = raeGDB("print " + name + "\n",
    "\\s*\\$\\d+ = (\\d+)\n").group(1);
    return Integer.parseInt(value);
  }

  /** process internal event in the event handler thread. */
  private void dispatch(BDA_CBP_BreakpointHitEvent e) {
    if (e.getBpID() == cbpBreakPointId) {
      String bptype = readEnum(BDA_CBP_BPTYPE);
      if (bptype.equals(BDA_BPTYPE_J2C_DEBUGGER)) {
        dbg.enqueEvent(new J2CBreakPointHitEvent(this));
      } else if (bptype.equals(BDA_BPTYPE_J2C_JNI_CALL)) {
        String native_target_address = readAddressValue(BDA_CBP_TARGET_NATIVE_ADDRESS); 
        // move the control to the prologue of the native method.
        raeGDB("finish\n"); //bda_cbp -> jni_state_j2c_call
        raeGDB("finish\n"); //jni_state_j2c_call -> j2c_proxy_xxx
        raeGDB("advance *" + native_target_address + "\n");
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
        raeGDB("finish\n"); // bda_cbp -> jni_state_c2j_return
        raeGDB("finish\n"); // jni_state_c2j_return -> c2j_proxyCallXXXMethod
        raeGDB("finish\n"); // caller of the *env->CallXXXMethod
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
   * Internally process the raw message to generate macro event.
   * 
   * @param e The raw text message event.
   */
  protected void processMessageEvent(RawTextMessageEvent e) {
    sbStdout.append(e.getMessage());
    int begin = 0;
    int match = sbStdout.indexOf(PROMPT);
    if (match == -1) {
      return;
    }
    while (match != -1) {
      assert begin <= match;
      String s = sbStdout.substring(begin, match);
      processMessage(s);
      begin = match + PROMPT.length();
      match = sbStdout.indexOf(PROMPT, begin);
    }
    int bufLen = sbStdout.length();
    if (begin < bufLen) {
      String remainder = sbStdout.substring(begin, bufLen - 1);
      sbStdout.setLength(0);
      sbStdout.append(remainder);
    } else {
      sbStdout.setLength(0);
    }
  }

  private void processMessage(String msg) {
    if (!gdbAttached) {
      gdbAttached = true;
      dbg.enqueEvent(new GDBAttachEvent(this));
    }

    if (!checkBreakPointHitPattern(msg) && !checkCallCompletionPattern(msg)
        && !checkStepCompletion(msg) && !checkSignal(msg)) {
      dbg.enqueEvent(new GDBRawMessageEvent(this, msg));
    }

    Pattern exitPattern = p("(Program|Inferior).* exited normally.\\n");
    Matcher exitMatcher = exitPattern.matcher(msg);
    if (exitMatcher.find()) {
      sendMessage("quit\n");
    }
  }

  private boolean checkBreakPointHitPattern(String msg) {
    Pattern p = p("(?:.*\n)*" + "Breakpoint (\\d+), (.*\n(?:.*\\n)*)");
    Matcher mgdbbp = p.matcher(msg);
    if (mgdbbp.matches()) {
      int bpid = Integer.valueOf(mgdbbp.group(1));
      String message = mgdbbp.group(2);
      steppingRequested = false;
      if (bpid ==cbpBreakPointId) {
        dbg.enqueEvent(new BDA_CBP_BreakpointHitEvent(this, bpid, message));
      } else {
        dbg.enqueEvent(new NativeBreakPointHitEvent(this, bpid, message));
      }
      return true;
    }
    return false;
  }

  private boolean checkCallCompletionPattern(String msg) {
    if (!native2JavaCallRequested && !callJavaDummyRequested) {
      return false;
    }
    Pattern p = p("(?:.*\n)*" + "\\$\\d+ = \\d+\n" + "(?:.*\n)*");
    Matcher m = p.matcher(msg);
    if (!m.matches()) {
      return false;
    }
    assert native2JavaCallRequested ^ callJavaDummyRequested;
    if (native2JavaCallRequested) {
      native2JavaCallRequested = false;
      dbg.enqueEvent(new Native2JavaCompletionEvent(this));
    } else {
      assert callJavaDummyRequested;
      callJavaDummyRequested = false;
      dbg.enqueEvent(new DummyCallCompletionEvent(this));
    }
    return true;
  }

  private boolean checkStepCompletion(String msg) {
    if (!steppingRequested) {
      return false;
    }
    dbg.enqueEvent(new InternalStepCompletionEvent(this));
    steppingRequested = false;
    return true;
  }

  private boolean checkSignal(String msg) {
    Pattern p = p("(?:.*\n)*" + "Program received signal (.+), .+\n" + "(?:.*\n)*");
    Matcher m = p.matcher(msg);
    if (!m.matches()) {
      return false;
    } else {
      String signal = m.group(1);
      dbg.enqueEvent(new NativeSignalEvent(this, signal));
      return true;
    }
  }

  /**
   * Let the Blink debug to talk to gdb and obtain native stack frame list.
   * Then, parse the output messages and constuct a list of native stack frames.
   * 
   * @return The list of native stack frames.
   */
  public LinkedList<NativeCallFrame> getFrames()  {
    String output = raeGDB("where\n");
    Pattern frameLinePattern = Pattern.compile("^#([0-9]+)" + "\\s+" // id
        + "(0x[a-f0-9]+)?" + "\\s+" // address
        + "(in\\s+(\\S+)|(\\S+))" + "\\s+" // function name
        + "\\(.*\\)" + "\\s*" // argument --> ignore
        + "(at (.+):([0-9]+))?" // source file and line
        + "(from \\S+)?" + "$");
    LinkedList<NativeCallFrame> frames = new LinkedList<NativeCallFrame>();
    for (final String line : output.split("\n")) {
      Matcher m = frameLinePattern.matcher(line);
      if (!m.find()) {
        continue;
      }
      int id = Integer.valueOf(m.group(1));
      String func = m.group(4) != null ? m.group(4) : m.group(5);
      String srcFile = m.group(7);
      int lineno = m.group(8) == null ? -1 : Integer.parseInt(m.group(8));
      NativeFrameType frameType;
      if (func.startsWith("bda_j2c_proxy")) {
        frameType = NativeFrameType.J2C_PROXY;
      } else if (func.startsWith("bda_c2j_proxy")) {
        frameType = NativeFrameType.C2J_PROXY;
      } else {
        frameType = NativeFrameType.NORMAL;
      }

      NativeCallFrame frame = new NativeCallFrame(id, func, srcFile, lineno,
          frameType);
      frames.addLast(frame);
    }
    return frames;
  }

  public SourceFileAndLine getCurrentLocation()  {
    raeGDB("frame 0\n");
    String frameText = raeGDB("bt 1\n");
    String firstLine = new StringTokenizer(frameText, "\n").nextToken();
    Pattern frameLineWithSourceFileAndLinePattern = Pattern
        .compile("^#0.+at (.+):([0-9]+).*$"); // source file and line
    Matcher m = frameLineWithSourceFileAndLinePattern.matcher(firstLine);
    SourceFileAndLine loc = null;
    if (m.matches()) {
      String sourceFile = m.group(1);
      int lineNumber = Integer.parseInt(m.group(2));
      loc = new SourceFileAndLine(sourceFile, lineNumber);
    }
    return loc;
  }

  public List<LocalVariable> getLocals(NativeCallFrame f)  {
    LinkedList<LocalVariable> localList = new LinkedList<LocalVariable>();
    raeGDB("frame " + f.getFrameID() + "\n");
    String args = raeGDB("info args\n");
    String locals = raeGDB("info locals\n");
    String argsAndLocals = args.concat(locals);
    Pattern p = Pattern.compile("^(.+) = (.+)$");
    for (final String line : argsAndLocals.split("\n")) {
      Matcher m = p.matcher(line);
      if (m.matches()) {
        String name = m.group(1);
        String value = m.group(2);
        localList.add(new LocalVariable(name, value));
      } else if (line.equals("No locals.")) {
        continue; // skip
      } else {
        dbg.err("can not recognize this GDB output: " + line + "\n");
      }
    }
    return localList;
  }

  public String getSourceLines(String filename, int line, int count)
       {
    raeGDB("set listsize " + count + "\n");
    return raeGDB("list " + filename + ":" + line + "\n");
  }

  public String runCommand(String command)  {
    return raeGDB(command + "\n");
  }

  /**
   * Send a message to the gdb process, and wait until the gdb sends back an
   * expected message. Here, the expected message is a regular expression, and
   * its corresponding matcher obejct will be returned.
   * 
   * @param msg The message to send.
   * @param expect The message to be expected from the gdb.
   * @return The matched string for the regular expression.
   */
  private Matcher raeGDB(final String msg, String expect)  {
    final Pattern p = Pattern.compile(expect);
    sendMessage(msg);
    return (Matcher) EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof GDBRawMessageEvent) {
          GDBRawMessageEvent ge = (GDBRawMessageEvent) e;
          Matcher tm = p.matcher(ge.getMessage());
          if (tm.matches()) {
            setResult(tm);
            return true;
          }
        }
        return false;
      }
    });
  }

  /**
   * Issue a gdb command, and get text message from the gdb.
   * @param cmd The command.
   * @return The result message.
   */
  private String raeGDB(final String cmd)  {
    sendMessage(cmd);
    String lines = (String) EventLoop.subLoop(dbg, new ReplyHandler() {
      public boolean dispatch(Event e) {
        if (e instanceof GDBRawMessageEvent) {
          setResult(((GDBRawMessageEvent) e).getMessage());
          return true;
        } else {
          return false;
        }
      }
    });
    return lines;
  }

  private int nextVCIdentifier = 0;

  public String getNewCTmpVarIdentifier() {
    return "$vc" + nextVCIdentifier++;
  }
  
  public void resetConvenienceVariables() { 
    nextVCIdentifier = 0;
  }
}
