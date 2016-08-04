package xtc.lang.blink;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import xtc.lang.blink.Blink.DebugerControlStatus;
import xtc.lang.blink.CallStack.LocalVariable;
import xtc.lang.blink.CallStack.JavaCallFrame;
import xtc.lang.blink.Event.Java2NativeCompletionEvent;
import xtc.lang.blink.Event.JavaBreakPointHitEvent;
import xtc.lang.blink.Event.JavaExceptionEvent;
import xtc.lang.blink.Event.JavaLoadLibraryEvent;
import xtc.lang.blink.Event.JavaStepCompletionEvent;
import xtc.lang.blink.Event.RawTextMessageEvent;
import xtc.lang.blink.EventUtil.RegExpReplyHandler;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.agent.AgentJavaDeclaration;

/** JDB driver for Blink debugger. */
public class JavaDebugger extends StdIOProcess implements AgentJavaDeclaration {

  /** JDB's macro event. */
  public static class ListenAddressEvent extends Event {
    /** JVM JDWP listen address. */
    private final String address;
    /** Constructor. */
    ListenAddressEvent(JavaDebugger jvm, String address) {
      super(jvm);
      this.address = address;
    }
    /** Getter methods. */
    public String getAddress() { return address;}
    public String getName() {return "JDBListen:" + address;}
  }

  /** JDB's macro event. */
  public static class InitializedEvent extends Event {
    /** Constructor. */
    InitializedEvent(JavaDebugger jdb) {
      super(jdb);
    }
    /** Getter methods. */
    public String getName() {return "JDBInitialized:";}
  }

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

  /**
   * A state when JDB is waiting for the completion of the J2C debugger
   * transition.
   */
  private boolean j2c_pending = false;

  /** The internal message buffer to parse the JDB's output. */
  private final StringBuffer sbStdout = new StringBuffer();

  /** Whether or not the JDB' listen address event was fired. */
  private boolean jdbListenAddressEventFired = false;

  /** Whether or not the JDB's initialization event was fired. */
  private boolean jdbInitializedEventFired = false;

  /**
   * @param dbg The Blink debugger.
   * @param name The user friendly name.
   */
  public JavaDebugger(Blink dbg, String name) {
    super(dbg, name);
  }

  /**
   * Start a JDB process.
   * @param args The JDB extra argument.
   */
  public void startListening(final String[] args) {
    final List<String> cmd = new LinkedList<String>();
    for(String a: new String[] {"jdb", "-listenany",}) {
      cmd.add(a);
    }
    for(String a:args) {
      cmd.add(a);
    }
    begin(cmd.toArray(new String[0]));
  }

  public void j2c()  {
    sendMessage("eval " + BDA_AGENT_NAME + "." + BDA_J2C + "()\n");
    j2c_pending = true;
  }

  public void run()  {
    sendMessage("run\n");
  }

  /** Let the Debugee continue.*/
  public void cont()  {
    sendMessage("cont\n");
  }
  
  public void step()  {
    sendMessage("step\n");
  }

  public void next()  {
    sendMessage("next\n");
  }

  public void stepi()  {
    raeJDB("stepi\n");
  }

  public void exit()  {
    sendMessage("exit\n");
  }

  public void setLoadLibraryEvent()  {
    raeJDB("stop in java.lang.System.loadLibrary\n");
  }

  public void resetLoadLibraryEvent()  {
    raeJDB("clear java.lang.System.loadLibrary\n");
  }

  public void prepareLoadLibrary()  {
    raeJDB("step up\n");
  }

  public void setBreakPoint(String className, int line)  {
    raeJDB("stop at " + className + ":" + line + "\n");
  }

  public void clearBreakPoint(String classNameAndMethod, int line)  {
    raeJDB("clear " + classNameAndMethod + ":" + line + "\n");  
  }

  public void setBreakPoint(String classNameAndMethod)  {
    raeJDB("stop in " + classNameAndMethod + "\n");
  }

  public void clearBreakPoint(String classNameAndMethod)  {
    raeJDB("clear " + classNameAndMethod + "\n");  
  }

  public String eval(String jexpr)  {
    String cmd = String.format("eval %s\n", jexpr);
    String value =raeJDB(cmd, ".+ = (.+)\\n" + "(?:.*\\n)*\\S+\\[\\d+\\] ").group(1);
    return value;
  }

  /**
   * Let the Blink debugger to talk to the jdb and obtain Java stack frame list.
   * Then, parse the output messages and constuct a list of Java stack frames.
   * 
   * @return The list of java stack frames.
   */
  public List<JavaCallFrame> getFrames()  {
    // run the jdb command.
    String output = raeJDB("where\n");

    // parse the output from jdb.
    LinkedList<JavaCallFrame> javaFrames = new LinkedList<JavaCallFrame>();
    Pattern frameLinePattern = Pattern.compile("^\\s+"
        + "\\[([0-9]+)\\]" + "\\s+"       // frame id -- > g1
        + "((\\S+)\\.([^\\.]+))" + "\\s+" // class(g3) and method(g4)
        + "("                             // g5
          + "\\(([^:]+):([0-9,]+)\\)"      // sourceName(g6) and Line(g7) 
          + "|"                           // or
          + "(\\(native method\\))"       // "(native frame)"(g8)
        +")" 
        + "$"
    );
    for (final String line : output.split("\n")) {
      Matcher m = frameLinePattern.matcher(line);
      if (!m.find()) {
        dbg.err("could not recognize jdb output: " + line + "\n");
        continue;
      }
      int id = Integer.valueOf(m.group(1));
      String className = m.group(3);
      String methodName = m.group(4);
      String srcFile= m.group(6);
      int lineno = m.group(7) == null ? -1: Integer.parseInt(m.group(7).replace(",", ""));
      boolean isTransition = m.group(8) != null;

      if (srcFile != null && srcFile.equals(BDA_AGENT_SOURCE_FILE)) {
        continue; //skip frames related to the c2j transition.
      }
      if (className.equals("sun.reflect.NativeMethodAccessorImpl")
          && methodName.equals("invoke0")) {
        // Treat the reflection frame as if a pure Java frame because the
        // reflection bypasses the c2j_proxy in Hotspot and J9.
        isTransition = false; 
      }
      JavaCallFrame frame = new JavaCallFrame(id, srcFile, lineno,
          isTransition, className, methodName);
      javaFrames.addLast(frame);
    }
    return javaFrames;
  }

  /** Get current location. */
  public SourceFileAndLine getCurrentLocation()  {
    List<JavaCallFrame> list = getFrames();
    SourceFileAndLine loc = null; 
    if (list.size() > 0 ) {
      JavaCallFrame top = list.get(0);
      String sourceFile = top.getSourceFile();
      int line = top.getLineNumber();
      if (sourceFile != null && line >= 0) {
        loc = new SourceFileAndLine(sourceFile, line);
      }
    } else {
    	assert false: "empty Java stack frames";
    }

    assert loc != null: "Java frames without source lines information";
    return loc;
  }

  /**
   * The the current source line for a frame.
   * @param jframe The frame.
   * @return The source line.
   */
  String getSourceLine(JavaCallFrame jframe)  {
    selectFrame(jframe);
    String lines = raeJDB("list\n");
    String line = "";
    StringTokenizer t = new StringTokenizer(lines, "\n");
    while(t.hasMoreTokens()) {
     String l = t.nextToken();
     if (l.matches("\\d+ =>.*")) {
       line = l;
     } else if (l.matches("Source file not found: .+")) {
       line = l;
     }
    }
    return line;
  }

  /**
   * Select a java frame in the jdb context.
   * 
   * @param dbg The debugger.
   * @param jframe The Java frame.
   */
  private void selectFrame(JavaCallFrame jframe)  {
    DebugerControlStatus dbgControl = dbg.getDebugControlStatus(); 
    assert dbgControl == DebugerControlStatus.JDB
        || dbgControl == DebugerControlStatus.JDB_IN_GDB;
    int target = jframe.getJdbIdentifier();
  
    String posBefore = raeJDB(
        "where\n", 
        "  \\[(\\d+)\\] .+\\n" + "(?:.*\\n)*\\S+\\[\\d+\\] "
    ).group(1);
    int before = Integer.parseInt(posBefore);
  
    int diff = target - before;
  
    if (diff > 0) {
      // up toward bottom of stack.
      raeJDB("up " + diff + "\n");
    } else if (diff < 0) {
      // down toward bottom of stack.
      int nWalks = - (diff); 
      raeJDB("down " + nWalks + "\n");
    }
  
    String posAfter = raeJDB(
        "where\n", 
        "\\s \\[(\\d+)\\] .+\\n" + "(?:.*\\n)*" + "\\S+\\[\\d+\\] "
    ).group(1);
    int after = Integer.parseInt(posAfter);
    assert after == target;
  }

  public String list(JavaCallFrame f)  {
    assert f != null;
    selectFrame(f);
    return raeJDB("list\n");
  }

  public List <LocalVariable> getLocals(JavaCallFrame f)  {
    LinkedList<LocalVariable> list = new LinkedList<LocalVariable>();
    assert f != null;
    selectFrame(f);
    String locals = raeJDB("locals\n");
    Pattern p = Pattern.compile("^(.+) = (.+)$");
    for(final String line : locals.split("\n")) {
      Matcher m = p.matcher(line);
      if (m.matches()) {
        String name  = m.group(1);
        String value = m.group(2);
        list.add(new LocalVariable(name, value));
      } else if (line.equals("Method arguments:")) {
        //skip
      } else if (line.equals("Local variables:")) {
        //skip
      } else if (line.equals("")) {
      } else {
        dbg.err("can not recognize this JDB output: " + line + "\n");
      }
    }
    return list;
  }

  public String set_j(JavaCallFrame f, String jexpr) 
     {
    if (f != null) {
      selectFrame(f);
    }

    String actualExpr = BDA_AGENT_VARIABLE_NAME + "." + BDA_CV_SET + "(" + jexpr + ")";  
    String vjid = raeJDB(
        "eval " + actualExpr + "\n",
        ".+ = (.+)\\n" + "(?:.*\\n)*" + "\\S+\\[\\d+\\] "
    ).group(1);

    return vjid;
  }

  public String getConvenienceVariableTypeName(String vjid)  {
    return evalAgentVariableMethod(BDA_CV_GET_TYPE_NAME, vjid);
  }

  public String getConvenienceVariableExpression(String vjid)  {
    return evalAgentVariableMethod(BDA_CV_GET_EXPR, vjid);
  }

  public String print(JavaCallFrame f, String expr)  {
    if (f != null) {
      selectFrame(f);
    }
    String rst = raeJDB(
        "print " + expr + "\n",
        "\\S+ = (\\S+)\\n"  + "(?:.*\\n)*\\S+\\[\\d+\\] "
    ).group(1);
    return rst;
  }

  public String runCommand(String cmd)  {
    return raeJDB(cmd+ "\n");
  }

  public void resetConvenienceVariables()  {
    raeJDB("eval " + BDA_AGENT_VARIABLE_NAME + "." + BDA_CLEANTEMPVARS + "()\n");
  }

  public void dispatch(Event e) {}

  private String evalAgentVariableMethod(String mname, String vjid)  {
    String actualExpr = BDA_AGENT_VARIABLE_NAME + "." + mname + "(" + vjid + ")";  
    String result = raeJDB(
        "eval " + actualExpr + "\n",
        ".+ = (.+)\\n" + "(?:.*\\n)*" + "\\S+\\[\\d+\\] "
    ).group(1);
    if (result.matches("\".+\"")) {
      result = result.substring(1, result.length()-1);
    }
    return result;
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
  private Matcher raeJDB(final String msg, String expect)  {
    sendMessage(msg);
    return (Matcher)EventLoop.subLoop(dbg, new RegExpReplyHandler(this, expect));
  }

  /**
   * Issue a gdb command, and get text message fro    m the gdb.
   * 
   * @param cmd The command.
   * @return The result messgage.
   */
  private String raeJDB(final String cmd) {
    return raeJDB(cmd, "((?:.+\\n)*)\\S+\\[\\d+\\] ").group(1);
  }

  /**
   * Internally process the raw message to generate macro event.
   * 
   * @param e The raw text message event.
   */
  protected void processMessageEvent(RawTextMessageEvent e) {
    sbStdout.append(new String(e.getMessage()));

    // try to find event.
    if (!jdbListenAddressEventFired) {
      Matcher m = p("Listening at address: (\\S+)\\n").matcher(sbStdout);
      if (m.find()) {
        String reminder = sbStdout.substring(m.end());
        String address = m.group(1);
        sbStdout.setLength(0);
        sbStdout.append(reminder);

        ListenAddressEvent listenEvent = new ListenAddressEvent(this, address);
        dbg.enqueEvent(listenEvent);
        jdbListenAddressEventFired = true;
      }
    } else if (!jdbInitializedEventFired) {
      Matcher m = p("Initializing jdb ...\\n" + "(.*\\n)*" + ".+\\[1\\] ").matcher(sbStdout);
      if (m.find()) {
        String reminder = sbStdout.substring(m.end());
        sbStdout.setLength(0);
        sbStdout.append(reminder);

        InitializedEvent initEvent = new InitializedEvent(this);
        dbg.enqueEvent(initEvent);
        jdbInitializedEventFired = true;
      }
    }

    Matcher mBreakpoint = p("Breakpoint hit: .*"
        + ".thread=(.+)., (.+)\\.([^\\.]+)\\(\\), line=([0-9,]+) bci=([0-9]+)\\n"
        + "((?:.*\\n)*)" + ".+\\[\\d+\\] ").matcher(sbStdout);
    if (mBreakpoint.find()) {
      int end = mBreakpoint.end();
      String reminder = sbStdout.substring(end);

      String threadName = mBreakpoint.group(1);
      String cname = mBreakpoint.group(2);
      String mname = mBreakpoint.group(3);
      int line = Integer.valueOf(mBreakpoint.group(4).replace(",", ""));
      int bcindex = Integer.valueOf(mBreakpoint.group(5));
      String msg = mBreakpoint.group(6);

      sbStdout.setLength(0);
      sbStdout.append(reminder);

      Event bpe;
      if (cname.equals("java.lang.System") && mname.equals("loadLibrary")) {
        bpe = new JavaLoadLibraryEvent(this, threadName,
            cname, line, mname, bcindex, msg);
      } else {
        bpe = new JavaBreakPointHitEvent(this, threadName,
            cname, line, mname, bcindex, msg);
      }
      dbg.enqueEvent(bpe);
      return;
    }

    Matcher mException = p("Exception occurred: (.+) \\(uncaught\\)"
        + ".thread=(.+)., (.+)\\.([^\\.]+)\\(\\), line=([0-9,]+) bci=([0-9]+)\\n"
        + "((?:.*\\n)*)" + ".+\\[\\d+\\] ").matcher(sbStdout);
    if (mException.find()) {
      int end = mException.end();
      String reminder = sbStdout.substring(end);
      String exceptionClass = mException.group(1);
      String thread = mException.group(2);
      String cname = mException.group(3);
      String mname = mException.group(4);
      int lineNumber = Integer.valueOf(mException.group(5).replace(",", ""));
      int bcindex = Integer.valueOf(mException.group(6));
      String msg = mException.group(7);
      
      JavaExceptionEvent bpe = new JavaExceptionEvent(this, thread, 
          cname, lineNumber, mname, bcindex, msg, exceptionClass);
      dbg.enqueEvent(bpe);
      sbStdout.setLength(0);
      sbStdout.append(reminder);
      return;
    }

    Matcher mstep = p("Step completed: " + ".*"
        + ".thread=(.+)., (.+)\\.([^\\.]+)\\(\\), line=([0-9,]+) bci=([0-9]+)\\n"
        + "((?:.*\\n)*)" + ".+\\[\\d+\\] ").matcher(sbStdout);
    if (mstep.find()) {
      int end = mstep.end();
      String reminder = sbStdout.substring(end);

      String threadName = mstep.group(1);
      String cname = mstep.group(2);
      String mname = mstep.group(3);
      int line = Integer.valueOf(mstep.group(4).replace(",", ""));
      int bcindex = Integer.valueOf(mstep.group(5));
      String msg = mstep.group(6);
      JavaStepCompletionEvent jse = new JavaStepCompletionEvent(this, 
          threadName, cname, line, mname, bcindex, msg);
      dbg.enqueEvent(jse);

      sbStdout.setLength(0);
      sbStdout.append(reminder);
    }

    if (j2c_pending) {
      Matcher m = p(BDA_AGENT_NAME + "." + BDA_J2C +"\\(\\) = <void value>\\n"
          + "(?:.+)\\[\\d+\\] ").matcher(sbStdout);
      if (m.find()) {
        int end = m.end();
        String reminder = sbStdout.substring(end);
        
        Java2NativeCompletionEvent je = new Java2NativeCompletionEvent(this);
        j2c_pending = false;
        dbg.enqueEvent(je);
        
        sbStdout.setLength(0);
        sbStdout.append(reminder);
      }
    }
  }
}
