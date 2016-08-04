package xtc.lang.blink;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.concurrent.LinkedBlockingQueue;
import static java.lang.String.format;

import xtc.lang.blink.CallStack.JavaCallFrame;
import xtc.lang.blink.Event.DummyCallCompletionEvent;
import xtc.lang.blink.Event.J2CBreakPointHitEvent;
import xtc.lang.blink.Event.Java2NativeCallEvent;
import xtc.lang.blink.Event.Java2NativeCompletionEvent;
import xtc.lang.blink.Event.Java2NativeReturnEvent;
import xtc.lang.blink.Event.JavaStepCompletionEvent;
import xtc.lang.blink.Event.LanguageTransitionEvent;
import xtc.lang.blink.Event.Native2JavaCallEvent;
import xtc.lang.blink.Event.Native2JavaCompletionEvent;
import xtc.lang.blink.Event.Native2JavaReturnEvent;
import xtc.lang.blink.Event.NativeBreakPointHitEvent;
import xtc.lang.blink.Event.JavaBreakPointHitEvent;
import xtc.lang.blink.Event.NativeStepCompletionEvent;
import xtc.lang.blink.Event.RawTextMessageEvent;
import xtc.lang.blink.JavaDebugger.InitializedEvent;
import xtc.lang.blink.JavaDebugger.ListenAddressEvent;
import xtc.lang.blink.NativeDebugger.LanguageTransitionEventType;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.agent.AgentNativeDeclaration;
import xtc.lang.blink.EventLoop.ReplyHandler;
import xtc.lang.blink.EventUtil.EventReplyHandler;
import xtc.lang.blink.EventUtil.ConjunctiveReplyHandler;
import xtc.lang.blink.EventUtil.DeathReplyHandler;
import xtc.lang.blink.EventUtil.J2CCompletionEventHandler;
import xtc.lang.blink.EventUtil.EventReplyHandler.EventFilter;
import static xtc.lang.blink.agent.AgentJavaDeclaration.*;

/**
 * The Blink debugger for the Java/C mixed mode source level debugging. 
 * 
 * @author Byeongcheol Lee
 */
public class Blink implements AgentNativeDeclaration {

  /** The debugger control status. */
  enum DebugerControlStatus {
    NONE, JDB, GDB, JDB_IN_GDB, GDB_IN_JDB,
  }

  /**
   * Prints a usage message to the user and shows what is wrong in the command
   * line arguments. Then, terminates the Blink debugger with an error code
   * (-1).
   * 
   * @param msg The message.
   */
  private static void usage(String msg) {
    StringBuffer buf = new StringBuffer();
    if (msg != null && msg.length() > 0) {
      buf.append(msg).append("\n\n");
    }
    String usage =
      "Usage: xtc.lang.blink.Blink [options] CLASS [arguments]\n"
      + "Blink options:\n"
      + "\t-help\n"
      + "\t-jniassert\n"
      + "\t-agentpath\n"
      +'\n'

      + "options forwarded to JDB:\n"
      + "\t-sourcepath                <directories separated by \":\">\n"
      + "\t-dbgtrace\n"
      +'\n'

      + "options forwarded to debuggee JVM:\n"
      + "\t-v -verbose[:class|gc|jni]\n"
      + "\t-D<name>=<value>           system property\n"
      + "\t-classpath                 <directories separated by \":\">\n"
      + "\t-X<option>\n"
      +'\n'

      + "environment variables:\n"
      + "\tOSTYPE                       one of linux-gnu, mingw, and win32\n"
      + "\tJAVA_DEV_ROOT                xtc installation path\n"
      ;

    buf.append(usage);
    System.out.println(buf.toString());
    System.exit(-1);
  }

  /**
   * Print the help message for the Blink command.
   */
  final void help() {
    String msg = 
      "\n"
      + "help               print help\n"
      + "exit               exit the Blink debugger\n"
      + "run                start the program run\n"
      + "\n"
      + "break [file:line]             add a break point e.g.) break Main.jni:9\n"
      + "stop at <classid>:<line>      add a break point  e.g.) stop at Main:15\n"
      + "stop in <classid>:<method>    add a break point  e.g.) stop in Main:main\n"
      + "info break                    list break points\n"
      + "delete [n]                    delete a break/watch point with its id [n].\n"
      + "\n"
      + "where                     dump stack trace\n"
      + "up [n]                    select n frames up\n"
      + "down [n]                  select n frames down\n"
      + "list                      print source code.\n"
      + "locals                    print local variables in selected frame\n"
      + "print <jexpr>             print Jeannie expression\n"
      + "\n"
      + "continue                  coninue running.\n"
      + "step                      execute until another line reached\n"
      + "next                      execute the next line, including function calls\n";
    out("%s", msg);
  }

  /**
   * The main method for the Blink debugger.
   * 
   * @param args The command line arguments.
   */
  public static void main(String[] args) {
    InternalOption debuggerOptions = new InternalOption();
    List<String> sbJVMOptions = new LinkedList<String>();
    List<String> sbJDBOptions = new LinkedList<String>();
    StringBuffer sbGDBOPtions = new StringBuffer();
    String mainClass = null;
    List<String> sbMainOptions = new LinkedList<String>();

    // parse arguments
    for (int i = 0; i < args.length; i++) {
      String arg = args[i];
      // [options] CLASS
      if (mainClass == null) {
        if (arg.equals("-help")) {
          usage("");
        } else if (arg.equals("-jniassert")) { 
          debuggerOptions.setJniCheck(true);
          //jdb options
        } else if (arg.equals("-agentpath")) {
          String agentPath = args[++i];
          debuggerOptions.setAgentPath(agentPath);
        } else if (arg.equals("-sourcepath")) {
          if ((i + 1) >= args.length)
            usage("Please, specify path after -sourcepath.");
          String argPath = args[++i];
          sbJDBOptions.add(arg);
          sbJDBOptions.add(argPath);
        } else if (arg.equals("-dbgtrace")) {
          sbJDBOptions.add(arg);
        //jvm options
        } else if (arg.equals("-classpath")) {
          if ((i + 1) >= args.length)
            usage("Please, specify path after -classpath.");
          String argPath = args[++i];
          sbJVMOptions.add(arg);
          sbJVMOptions.add(argPath);
        } else if (arg.equals("-v") || Pattern.matches("-verbose(:(class|gc|jni))?", arg)) {
          sbJVMOptions.add(arg);
        } else if (arg.matches("-X.+")) {
          sbJVMOptions.add(arg);
        } else if (arg.matches("-D[^=]+=.*")) {
          sbJVMOptions.add(arg);
        }else {
          mainClass = arg;
        }
      } else {
        // app options
        sbMainOptions.add(arg);
      }
    }

    // check arguments
    if (mainClass == null) {
      usage("Please, specify the main CLASS name.");
    }

    // build jvm arguments
    sbJVMOptions.add(mainClass);
    for(String a:sbMainOptions) {
      sbJVMOptions.add(a);
    }

    //now actually launch the Blink.
    try {
      Blink debugger = new Blink(mainClass, sbJVMOptions.toArray(new String[0]),
          sbJDBOptions.toArray(new String[0]), sbGDBOPtions.toString(), debuggerOptions);
      debugger.startSession();
      debugger.eventLoop.main();
    } catch (Exception e) {
      e.printStackTrace();
    }

    System.exit(0);
  }

  /** Ensure the JAVA_DEV_ROOT directory is available. */
  private static String ensureJavaDevRoot() {
    String java_dev_root= System.getenv("JAVA_DEV_ROOT");
    if (java_dev_root == null || java_dev_root.equals("")) {
      usage("JAVA_DEV_ROOT environment variable is not set");
      assert false:"not reachable";
    }
    if (!new File(java_dev_root).isDirectory()) {
      usage(format("JAVA_DEV_ROOT(=%s) is expected to be directory", java_dev_root));
      assert false:"not reachable";
    }
    return java_dev_root;
  }

  /** Ensure the agent  exists and return its full path. */
  String ensureAgentLibraryPath() {
    String apath = options.getAgentPath();
    if (apath != null && new File(apath).exists()) {
       return apath;
    }
    String java_dev_root = ensureJavaDevRoot();
    String libpath = format("%s%sbin", java_dev_root, java.io.File.separator);
    String agentPath;
    String osType=System.getProperty("OSTYPE");
    if ("linux-gnu".equals(osType)) {
      agentPath = format("%s%slib%s.so", libpath, java.io.File.separator, BDA_SHARED_LIBRARY_NAME);
    } else if ("win32".equals(osType)) {
      agentPath = format("%s%s%s.dll", libpath, java.io.File.separator, BDA_SHARED_LIBRARY_NAME);
    } else if ("mingw".equals(osType)) {
      agentPath = format("%s%s%s_mingw.dll", libpath, java.io.File.separator, BDA_SHARED_LIBRARY_NAME);
    } else {
      agentPath = format("%s%slib%s.so", libpath, java.io.File.separator, BDA_SHARED_LIBRARY_NAME);
    }
    if (new File(libpath).exists()) {
      return agentPath;
    } else {
      usage(format("can not find Blink agent native library in %s/bin",java_dev_root));
      return null;
    }
  }

  /**
   * check if the Blink run jdb process, and create Blink's jdb controller. If
   * the Blink can not correctly create the jdb process, terminate the current
   * debugging session.
   */
  private static JavaDebugger ensureJavaDebugger(Blink dbg) {
    try {
      Process p = Runtime.getRuntime().exec("jdb -version");
      BufferedReader r = new BufferedReader(new InputStreamReader(
          p.getInputStream()));
      String firstLine = r.readLine();
      if (firstLine.startsWith("This is jdb version")) {
        int exitCode = p.waitFor();
        r.close();
        if (exitCode != 0) {
          usage("can not correctly access jdb in the current environment.");
        }
      }
    } catch(InterruptedException ie) {
      usage("can not correctly access jdb in the current environment.");
      System.exit(-1);
    } catch(IOException e) {
      usage("can not correctly access jdb in the current environment.");
      System.exit(-1);
    }
    
    return new JavaDebugger(dbg, "jdb");
  }

  /**
   * Choose a native debugger, check Blink can run this native debugger, and
   * create Blink's native debugger handler. If Blink can not correctly use the
   * native debugger, terminate the current debugging session.
   * 
   * The OSTYPE environment variable controls which native debugger to use.
   */ 
  private static NativeDebugger ensureNativeDebugger(Blink dbg) {
    String ostype = System.getenv("OSTYPE");
    if (ostype == null || !ostype.equals("win32")) {
      // default is gdb.
      try {
        Process p = Runtime.getRuntime().exec("gdb -version");
        BufferedReader r = new BufferedReader(new InputStreamReader(
            p.getInputStream()));
        String firstLine = r.readLine();
        if (firstLine.startsWith("GNU gdb")) {
          int exitCode = p.waitFor();
          r.close();
          if (exitCode != 0) {
            usage("can not correctly access gdb in the current environment.");
          }
        }
      } catch(InterruptedException ie) {  
        usage("can not correctly access gdb in the current environment.");
      } catch(IOException e) {
        usage("can not correctly access gdb in the current environment.");
      }
      return new NativeGDB(dbg, "gdb");
    } else {
      //if OSTYPE is win32, use cdb.
      assert ostype.equals("win32");
      try {
        Process p = Runtime.getRuntime().exec("cdb -version");
        BufferedReader r = new BufferedReader(new InputStreamReader(
            p.getInputStream()));
        String versionLine = r.readLine();
        if (versionLine.matches("cdb version \\d+\\.\\d+\\.\\d+\\.\\d+")) {
          int exitCode = p.waitFor();
          r.close();
          if (exitCode != 0) {
            usage("cdb returned non-zero exit code: " 
                + exitCode + " when running cdb -version.");
          }
        }
      } catch(InterruptedException ie) {
        usage("can not correctly run cdb in the current environemnt.");
      } catch (IOException e) {
        usage("can not correctly run cdb in the current environment.");
      }
      return new NativeCDB(dbg, "cdb");
    }
  }
  
  /** The application main class. */
  private final String mainClass;

  /** The option string to be forwarded to the jvm. */
  private final String[] jvmArguments;

  /** The option string to be forwarded to the jdb. */
  private final String[] jdbArguments;

  /** The user command monitor. */
  private final CommandLineInterface user;

  /** The application. */
  final DebugeeJVM jvm;

  /** The jdb message monitor. */
  final JavaDebugger jdb;

  /** The gdb message monitor. */
  final NativeDebugger ndb;

  /**
   * The Blink event queue. Let the main thread be thread who initiated the
   * eventLoop() method, and this thread consumes events in the queue. There are
   * three event producers: user, jdb and gdb.
   */
  private final LinkedBlockingQueue<Event> eventQueue =
    new LinkedBlockingQueue<Event>();

  final EventLoop eventLoop;

  /** The current debugger control status. */
  private DebugerControlStatus debugControl = DebugerControlStatus.NONE;

  /**
   * This is a flag to recode a fact that the jdb and gdb are initialized for
   * j2c and c2j debugger switching.
   */
  private boolean gdbAttached = false;

  /** The break points manager. */
  final BreakPointManager breakpointManager = 
    new BreakPointManager(this);

  /** The Blink debugger options. */
  final InternalOption options;

  /**
   * Construct the Blink debugger.
   * 
   * @param mainClass The main class name.
   * @param jvmArguments The jvm command line options.
   * @param jdbArguments The jdb command line options.
   * @param gdbOptions The gdb command line options.
   * @param debugOption The Blink debugger options.
   */
  private Blink(final String mainClass, final String[] jvmArguments,
      final String[] jdbArguments, final String gdbOptions,
      final InternalOption debugOptions) {
    this.mainClass = mainClass;
    this.jvmArguments = jvmArguments;
    this.jdbArguments = jdbArguments;
    this.options = debugOptions;
    this.jdb =ensureJavaDebugger(this);
    this.ndb = ensureNativeDebugger(this);
    this.user = new CommandLineInterface(this);
    this.jvm = new DebugeeJVM(this, "jvm");
    this.eventLoop = new EventLoop(this);
  }

  /**
   * Start the Blink debugger and wait until the end of this Blink session.
   */
  private void startSession()  {

    // Launch Java debugger and get the listening address.
    jdb.startListening(jdbArguments);
    final String address = (String) EventLoop.subLoop(this,
        new EventLoop.ReplyHandler() {
          boolean dispatch(Event e) {
            if (e instanceof ListenAddressEvent
                && e.getSource() == Blink.this.jdb) {
              ListenAddressEvent listenEvent = (ListenAddressEvent) e;
              setResult(listenEvent.getAddress());
              return true;
            } else {
              return false;
            }
          }
        });

    // Launch JVM and attach the JVM to the JDB.
    jvm.beginDebugSession(jvmArguments, address);
    EventLoop.subLoop(this, new EventLoop.ReplyHandler() {
      boolean dispatch(Event e) {
        if (e instanceof InitializedEvent 
            && e.getSource() == Blink.this.jdb) {
          setResult(new Boolean(true));
          return true;
        } else {
          return false;
        }
      }
    });

    // Advance the program execution to the main method.
    jdb.setBreakPoint(mainClass + ".main");
    jdb.run();
    EventLoop.subLoop(this, new EventLoop.ReplyHandler() {
      boolean dispatch(Event e) {
        if (e instanceof JavaBreakPointHitEvent) {
          JavaBreakPointHitEvent je = (JavaBreakPointHitEvent) e;
          if (je.getClassName().equals(mainClass)
              && je.getMethodName().equals("main")) {
            setResult(new Boolean(true));
            return true;
          } else {
            assert false : "unknown Java breakpoint hit";
            return false;
          }
        } else if (e instanceof RawTextMessageEvent) {
            return false;
        } else {
          assert false : "To be implemented for " + e.toString();
          return false;
        }
      }
    });

    changeDebugControlStatus(DebugerControlStatus.JDB);
    jdb.clearBreakPoint(mainClass + ".main");
    initj();

    // show welcome message.
    out("Blink a Java/C mixed language debugger.\n");
    changeDebugControlStatus(DebugerControlStatus.JDB);

    // Now, enable the user command line processing.
    user.start();
    showPrompt();

  }

  /**
   * Present a terminal command prompt to the user.
   */
  void showPrompt() {
    switch(debugControl) {
    case JDB:
      out("(bdb-j) ");
      break;
    case GDB:
      out("(bdb-c) ");
      break;
    case JDB_IN_GDB:
      out("(bdb-c2j) ");
      break;
    case GDB_IN_JDB:
      out("(bdb-j2c) ");
      break;      
    }
  }

  /** Implement Blink "run" command. */
  void run() {
    assert (getDebugControlStatus() == DebugerControlStatus.JDB);
    jdb.run();
    changeDebugControlStatus(Blink.DebugerControlStatus.NONE);
  }

  /**
   * Prepare jdb and gdb for j2c and c2j debugger switching. Internally, this
   * will initilize the Blink debugger agent by running a number of jdb and gdb
   * commands.
   */
  boolean initj()  {
    if (gdbAttached) {
      err("the initj was run before.");
      return true;
    }

    assert debugControl == DebugerControlStatus.JDB;
    // try to initialize the DebugAgent
    jdb.setBreakPoint(BDA_AGENT_NAME + "." + BDA_JBP );

    // Obtain the process ID of the debuggee by using the agent.
    int pid = Integer.parseInt(jdb.eval(BDA_GETPROCESSID));

    // Attach gdb to the debugee using the process ID.
    ndb.attach(pid);
    gdbAttached = true;

    assert getDebugControlStatus() == DebugerControlStatus.JDB;
    return true;
  }

  /**
   * Implements the j2c macro command. This will activate the gdb assuming that
   * the jdb has control over the debuggee.
   */
  void j2c() {
    if (!IsNativeDebuggerAttached()) {
      err("please run initj before j2c\n");
      return;
    }
    jdb.j2c();
    Event e = (Event) EventLoop.subLoop(this, new EventReplyHandler(
        new EventFilter[] { new EventFilter(ndb, J2CBreakPointHitEvent.class),
            new EventFilter(ndb, LanguageTransitionEvent.class), }));
    if (e instanceof LanguageTransitionEvent) {
      ndb.cont();
      EventLoop.subLoop(this,
          new EventReplyHandler(new EventFilter[] { new EventFilter(ndb,
              J2CBreakPointHitEvent.class), }));
    }
    changeDebugControlStatus(DebugerControlStatus.GDB_IN_JDB);
  }

  /**
   * Implements the c2j macro command. This will activate the jdb assuming that
   * gdb has control over the debugee.
   */
  void c2j() {
    if (!IsNativeDebuggerAttached()) {
      err("please run initj before c2j\n");
      return;
    }
    ndb.callNative2Java();
    EventLoop.subLoop(this, new EventReplyHandler( new EventFilter[] {
        new EventFilter(jdb, JavaBreakPointHitEvent.class),
    }));

    changeDebugControlStatus(DebugerControlStatus.JDB_IN_GDB);
  }

  /**
   * Implements the jret macro command. If the current debugger nesting is
   * jdb->gdb, then this will resume the gdb j2c break point, and the user input
   * redirection will be switched to the jdb. If the current debugger nesting is
   * gdb->jdb, this will resume the jdb c2j break point, and the user input
   * redirection will be switched to the gdb.
   */
  void jret() {
    if (!IsNativeDebuggerAttached()) {
      err("please run initj before jret\n");
      return;
    }
    switch (getDebugControlStatus()) {
    case NONE:
    case JDB:
    case GDB:
      err("jret is for jdb and gdb nesting.");
      break;
    case JDB_IN_GDB:
      jdb.cont();
      EventLoop.subLoop(this, new EventReplyHandler(new EventFilter[] {
          new EventFilter(ndb, Native2JavaCompletionEvent.class),
          new EventFilter(ndb, LanguageTransitionEvent.class), }));
      changeDebugControlStatus(DebugerControlStatus.GDB);
      break;
    case GDB_IN_JDB:
        ndb.cont();
        EventLoop.subLoop(this, new ReplyHandler() {
          boolean dispatch(Event e) {
            if (e instanceof Java2NativeCompletionEvent && e.getSource() == jdb) {
              setResult(new Boolean(true));
              return true;
            } else if (e instanceof NativeBreakPointHitEvent && e.getSource() == ndb) {
              ndb.cont();
              return false;
            } else {
              return false;
            }
          }
        });
        changeDebugControlStatus(DebugerControlStatus.JDB);
      break;
    default:
      break;
    }
  }

  /**
   * Implement Blink "continue/cont" command.
   */
  void cont() {
    assert debugControl != DebugerControlStatus.NONE;

    switch (getDebugControlStatus()) {
      case JDB:
      case GDB:
      if (breakpointManager.hasDeferredNativeBreakpoint()) {
          ensureJDBContext();
          jdb.setLoadLibraryEvent();
      }
      break;
    }

    switch (getDebugControlStatus()) {
    case JDB:
        jdb.cont();
        changeDebugControlStatus(Blink.DebugerControlStatus.NONE);
      break;
    case GDB:
        ndb.cont();
        changeDebugControlStatus(Blink.DebugerControlStatus.NONE);
      break;
    case JDB_IN_GDB:
    case GDB_IN_JDB:
      err("\"continue\" is not allowed in this nested mode:"
          + getDebugControlStatus() + "\n" + "use jret to return to the gdb.\n");
      break;
    default:
      assert false : "not allowed";
      break;
    }
  }

  /**
   * Perform inter-language source level stepping.
   */
  Event step()  {
    ensurePureContext();
    Event e = null;
    SourceFileAndLine start = getCurrentSourceLevelLocation();
    assert start != null;
    SymbolMapper.SourceFileAndLine now = null;
    do {
      switch(getDebugControlStatus()) {
      case JDB:
        e = stepj();
        now = getCurrentSourceLevelLocation();
        break;
      case GDB:
        e = stepc();
        now = getCurrentSourceLevelLocation();
        break;
      default:
        assert false;
        break;
      }
    } while(now == null || start.equals(now));
    return e;
  }

  /**
   * Perform the inter-language source level stepping from Java context, and
   * return component debugger that finished this single stepping.
   *
   * @return The component event.
   */
  private Event stepj()  {
    assert getDebugControlStatus() == DebugerControlStatus.JDB;

    // try JDB step-into and expect pause at Java or native code.
    j2c();
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.J2C_CALL, 0);
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN, 0);
    jret();
    jdb.step();

    boolean reachedSourceLine = false;
    Event e;
    do { 
      changeDebugControlStatus(DebugerControlStatus.NONE);
      e = (Event)EventLoop.subLoop(this, new EventReplyHandler(new EventFilter[] {
          new EventFilter(jdb, JavaStepCompletionEvent.class),
          new EventFilter(jdb, JavaBreakPointHitEvent.class),
          new EventFilter(ndb, Java2NativeCallEvent.class),
          new EventFilter(ndb, Native2JavaReturnEvent.class)
      }));
      if (e.getSource() == jdb) {
        // stepping from Java remains inside the Java area.
        changeDebugControlStatus(DebugerControlStatus.JDB);
        j2c();
        ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_CALL);
        ndb.clearTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN);
        jret();
        reachedSourceLine = true; // assume all Java byte code has the source line here.
      } else {
        // the control will stay in the native code.
        assert e.getSource() == ndb;
        changeDebugControlStatus(DebugerControlStatus.GDB);
        if (ndb.getCurrentLocation() == null ) {
          changeDebugControlStatus(DebugerControlStatus.NONE);
          ndb.cont();
        } else {
          ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_CALL);
          ndb.clearTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN);

          // flush the JDB's stepping status.
          ndb.callJavaDummy();
          EventLoop.subLoop(this, new EventReplyHandler(new EventFilter[] {
              new EventFilter(jdb, JavaStepCompletionEvent.class)
          }));
          jdb.cont();
          EventLoop.subLoop(this, new EventReplyHandler(new EventFilter[] {
              new EventFilter(ndb, DummyCallCompletionEvent.class)
          }));
          reachedSourceLine = true;
        }
      }
    } while(!reachedSourceLine);
    return e;
  }

  /**
   * Perform an inter-language source level stepping from native code, and return
   * component debugger event that finished this stepping.
   *
   * @return The component event.
   */
  private Event stepc()  {
    assert getDebugControlStatus() == DebugerControlStatus.GDB;

    //set breakpoints for escaping to the Java.
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.C2J_CALL, 0);
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN, 0);
    ndb.step();
    Event e = (Event)EventLoop.subLoop(this, new EventReplyHandler( new EventFilter[] {
        new EventFilter(ndb, Native2JavaCallEvent.class),
        new EventFilter(ndb, Java2NativeReturnEvent.class),
        new EventFilter(ndb, NativeStepCompletionEvent.class),
        new EventFilter(ndb, NativeBreakPointHitEvent.class),
    }));
    ndb.clearTransitionBreakPoint(LanguageTransitionEventType.C2J_CALL);
    ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN);

    if (e instanceof NativeStepCompletionEvent || e instanceof NativeBreakPointHitEvent) {
      //done!
    } else if (e instanceof Native2JavaCallEvent) {
      Native2JavaCallEvent ne = (Native2JavaCallEvent)e;

      //reach the Java target method entry.
      String className= ne.getClassName();
      int lineNumber = ne.getLineNumber();
      c2j();
      jdb.setBreakPoint(className, lineNumber);
      jret();
      changeDebugControlStatus(DebugerControlStatus.NONE);
      ndb.cont();
      EventLoop.subLoop(
        this, new EventReplyHandler( new EventFilter[] {
        new EventFilter(jdb, JavaBreakPointHitEvent.class),
      }));
      changeDebugControlStatus(DebugerControlStatus.JDB);
      jdb.clearBreakPoint(className, lineNumber);
    } else if (e instanceof Java2NativeReturnEvent) {
      Java2NativeReturnEvent ne = (Java2NativeReturnEvent)e;

      //reach the Java return site.
      String cname = ne.getJavaTarget();
      int line = ne.getTargetLineNumber();
      c2j();
      jdb.setBreakPoint(cname, line);
      jret();
      ensureGDBContext();
      changeDebugControlStatus(DebugerControlStatus.NONE);
      ndb.cont();
      EventLoop.subLoop(this, new EventReplyHandler( new EventFilter[] {
          new EventFilter(jdb, JavaBreakPointHitEvent.class),
      }));
      changeDebugControlStatus(DebugerControlStatus.JDB);
      jdb.clearBreakPoint(cname, line);
    }
    return e;
  }

  /**
   * Perform an inter-language source level stepping, and return the component
   * debugger event that terminated the single stepping.
   * 
   * @return The component debugger event.
   */
  Event next()  {
    Event e = null;
    ensurePureContext();
    SymbolMapper.SourceFileAndLine start = getCurrentSourceLevelLocation();
    assert start != null;
    SymbolMapper.SourceFileAndLine now = null;
    do {
      switch(getDebugControlStatus()) {
      case JDB:
        e = nextj();
        now = getCurrentSourceLevelLocation();
        break;
      case GDB:
        e = nextc();
        now = getCurrentSourceLevelLocation();
        break;
      default:
        assert false;
        break;
      }
    } while(now == null || start.equals(now));
    ensurePureContext();
    assert e != null;
    return e;
  }

  /**
   * Perform a source-level step-over from the Java code, and return the
   * component debugger event that terminated this single stepping. At the end
   * of this operation, this debuggee is in either Java or native code.
   * 
   * @return The component debugger event.
   */
  private Event nextj()  {
    assert debugControl == DebugerControlStatus.JDB;
    
    //set c2j_return breakpoint.
    j2c();
    int languageTransitionCountOnStack = ndb.getLanguageTransitionCount();
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN, 
        languageTransitionCountOnStack);
    jret();

    //start a single step from Java.
    changeDebugControlStatus(DebugerControlStatus.NONE);
    jdb.next();    
    Event e =  (Event)EventLoop.subLoop(this, 
        new EventReplyHandler(new EventFilter[] {
            new EventFilter(jdb, JavaStepCompletionEvent.class),
            new EventFilter(jdb, JavaBreakPointHitEvent.class),
            new EventFilter(ndb, Native2JavaReturnEvent.class),
            new EventFilter(ndb, NativeBreakPointHitEvent.class),
    }));
    if (e.getSource() == jdb) {
      changeDebugControlStatus(DebugerControlStatus.JDB);
      j2c();
      ndb.clearTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN);
      jret();
      return e;
    } else {
      assert e.getSource() == ndb;
      changeDebugControlStatus(DebugerControlStatus.GDB);
      ndb.clearTransitionBreakPoint(LanguageTransitionEventType.C2J_RETURN);

      return e;
    }
  }

  /**
   * Perform a source-level step-over from the native code, and return the
   * component debugger event that terminated this single stepping. At the end
   * of this operation, this debuggee is in either Java or native code.
   *
   * @return The component debugger event.
   */
  private Event nextc()  {
    assert debugControl == DebugerControlStatus.GDB;

    //set language transition breakpoint.
    ensureGDBContext();
    int languageTransitionCountOnStack = ndb.getLanguageTransitionCount();
    ndb.setTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN, 
        languageTransitionCountOnStack);

    //resume the execution with native stepping over.
    changeDebugControlStatus(DebugerControlStatus.NONE);
    ndb.next();
    Event e = (Event)EventLoop.subLoop(this, new EventReplyHandler( 
      new EventFilter[] {
        new EventFilter(ndb, NativeStepCompletionEvent.class),
        new EventFilter(ndb, NativeBreakPointHitEvent.class),
        new EventFilter(ndb, Java2NativeReturnEvent.class),
        new EventFilter(jdb, JavaBreakPointHitEvent.class),
    }));

    //handle the step completion cases
    if (e instanceof NativeStepCompletionEvent || 
        e instanceof NativeBreakPointHitEvent) {
      changeDebugControlStatus(DebugerControlStatus.GDB);
      ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN);  
    } else if (e instanceof Java2NativeReturnEvent) {
      changeDebugControlStatus(DebugerControlStatus.GDB);
      ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN);  

      //continue until the program reaches the return site.
      ensureJDBContext();
      Java2NativeReturnEvent event = (Java2NativeReturnEvent)e;
      String cname = event.getJavaTarget();
      int line = event.getTargetLineNumber();
      assert cname != null && line > 0 : "can not put byte code index break point with jdb.";
      jdb.setBreakPoint(cname, line);
      ensureGDBContext();
      changeDebugControlStatus(DebugerControlStatus.NONE);
      ndb.cont();
      boolean returnSiteReached = false;
      do {
        JavaBreakPointHitEvent jbpHitEvent = (JavaBreakPointHitEvent)
        EventLoop.subLoop(this, new EventReplyHandler( new EventFilter[] {
            new EventFilter(jdb, JavaBreakPointHitEvent.class),
        }));
        changeDebugControlStatus(DebugerControlStatus.JDB);
        returnSiteReached =jbpHitEvent.getClassName().equals(cname) && jbpHitEvent.getLineNumber() == line;
      } while (!returnSiteReached);
      jdb.clearBreakPoint(cname, line);      
      changeDebugControlStatus(DebugerControlStatus.JDB); 
    } else if (e instanceof JavaBreakPointHitEvent) {
      changeDebugControlStatus(DebugerControlStatus.JDB);
      j2c(); //this will flush the native single stepping.
      ndb.clearTransitionBreakPoint(LanguageTransitionEventType.J2C_RETURN);
      jret();
    } else {
      assert false : " not reachable";
    }
    return e;
  }

  /** Exit the current debugging session. 
   * @ */
  void exit()  {
    ensurePureContext();
    if (getDebugControlStatus() == DebugerControlStatus.NONE) {
      System.exit(0);
      assert false : "should not reach here";
      return;
    } else if (getDebugControlStatus() == DebugerControlStatus.JDB) {
        // ensure gdb is detached.
        if (gdbAttached && !ndb.isDead()) {
          j2c();
          ndb.detach();
          debugControl = DebugerControlStatus.JDB;
          EventLoop.subLoop(this, new ConjunctiveReplyHandler(
              new J2CCompletionEventHandler(jdb), new DeathReplyHandler(ndb)));
          gdbAttached = false;
        }
        if (!jdb.isDead()) {
          jdb.exit();
          EventLoop.subLoop(this, new ConjunctiveReplyHandler(
              new DeathReplyHandler(jvm), new DeathReplyHandler(jdb)));
          debugControl = DebugerControlStatus.NONE;
        }
      
    } else if (getDebugControlStatus() == DebugerControlStatus.GDB) {
      if (!ndb.isDead()) {
        ndb.quit();
        EventLoop.subLoop(this, new ConjunctiveReplyHandler(
            new DeathReplyHandler(jvm), new DeathReplyHandler(jdb),
            new DeathReplyHandler(ndb)));
      }
    } else {
      assert false : "should not reach here";
      return;
    }
    System.exit(0);
  }

  /**
   * Print a message to the console.
   * 
   * @param msg The message to print.
   */
  void out(String format, Object ... args) {
    String msg = format(format, args);
    user.out(msg);
  }
  
  /**
   * Print an message to the console.
   * 
   * @param b The byte buffer.
   * @param off The offset.
   * @param len The length.
   */
  void out(char[] b) {
    user.out(new String(b));
  }

  /**
   * Print an error message to the console.
   * 
   * @param msg The error message to print.
   */
  void err(String msg) {
    user.err(msg);
  }

  /**
   * Getter method for the debuggerSwitchingInitialized.
   * 
   * @return true if the debug context switching is ready, or false otherwise.
   */
  boolean IsNativeDebuggerAttached() {
    return gdbAttached;
  }

  /**
   * Ensure the debug agent is ready.
   */
  boolean ensureDebugAgent()  {
    assert debugControl ==  DebugerControlStatus.JDB;
    if (IsNativeDebuggerAttached()) {
      return true;
    }
    return initj();
  }

  /**
   * Ensure jdb is available.
   */
  public boolean ensureJDBContext()  {
    switch (debugControl) {
    case JDB:
    case JDB_IN_GDB:
      return true;
    case GDB:
      c2j();
      return true;
    case GDB_IN_JDB:
      jret();
      return true;
    default:
      assert false : "not allowed state";
      return false;
    }
  }

  /**
   * try to ensure gdb is available.
   * 
   * @return true if the gdb context. false otherwise.
   */
  public boolean ensureGDBContext()  {
    if (!IsNativeDebuggerAttached()) {
      return false;
    }
    switch (debugControl) {
    case JDB:
      j2c();
      break;
    case JDB_IN_GDB:
      jret();
      break;
    case GDB:
    case GDB_IN_JDB:
      break;
    default:
      assert false : "not allowed state";
      break;
    }
    return true;
  }

  /**
   * Ensure a pure debug context.
   */
  public final void ensurePureContext() {
    switch(getDebugControlStatus()) {
    case JDB:
    case GDB:
      break;
    case JDB_IN_GDB:
    case GDB_IN_JDB:
      jret();
      break;
    case NONE:
      break;
    }
  }

  /**
   * Switch to the new debugger state.
   * 
   * @param newStatus The requested new state.
   */
  synchronized void changeDebugControlStatus(DebugerControlStatus newStatus) {
    DebugerControlStatus oldStatus = debugControl;
    if (oldStatus == newStatus) {
      return;
    }
    boolean success = false;
    switch (debugControl) {
    case NONE:
      success = newStatus == DebugerControlStatus.JDB
          || newStatus == DebugerControlStatus.GDB;
      break;
    case JDB:
      success = newStatus == DebugerControlStatus.NONE
          || newStatus == DebugerControlStatus.GDB_IN_JDB;
      break;
    case GDB:
      success = newStatus == DebugerControlStatus.NONE
          || newStatus == DebugerControlStatus.JDB_IN_GDB;
      break;
    case JDB_IN_GDB:
      success = newStatus == DebugerControlStatus.GDB;
      break;
    case GDB_IN_JDB:
      success = newStatus == DebugerControlStatus.JDB;
      break;
    }

    debugControl = newStatus;
    if (!success) {
      err("warning: not an expected transition in the following context\n"
          + oldStatus + "->" + newStatus);
      Thread.dumpStack();
    }
  }

  /**
   * @return The debugger control status.
   */
  synchronized DebugerControlStatus getDebugControlStatus() {
    return debugControl;
  }

  /**
   * @return The current language context
   */
  synchronized String getCurrentLanguageContext() {
    switch (debugControl) {
    case JDB_IN_GDB:
    case JDB:
      return "Java";
    case GDB_IN_JDB:
    case GDB:
      return "C";
    default:
      return "None";
    }
  }

  /**
   * Get current location where the debugee suspened.
   * @return The location.
   */
  SourceFileAndLine getCurrentSourceLevelLocation()  {
    ensurePureContext();
    SourceFileAndLine location;
    switch(debugControl) {
    case JDB:
      location = jdb.getCurrentLocation();
      break;
    case GDB:
      location = ndb.getCurrentLocation();
      break;
    default:
      assert false: "not reachable";
      location = null;
      break;
    }
    return location;
  }
  String getCurrentSourceLine()  {
    ensurePureContext();
    String line;
    switch(debugControl) {
    case JDB:
      List<JavaCallFrame> frames = jdb.getFrames();
      assert frames.size() > 0;
      JavaCallFrame top = frames.get(0);
      line = jdb.getSourceLine(top);
      break;
    case GDB:
      SourceFileAndLine loc = getCurrentSourceLevelLocation();
      line = ndb.getSourceLines(loc.getSourceFile(), loc.getSourceLine(), 1);
      break;
    default:
      assert false: "not reachable";
      line = null;
      break;
    } 
    return line;
  }

  /**
   * Enqueue an event.
   * 
   * @param e The event.
   */
  void enqueEvent(Event e) {
    if (!eventQueue.add(e)) {
      err("can not successfully insert event: " + e + " from "
          + Thread.currentThread() + "\n");
      err("Now, I'm discarding that event\n");
    }
  }

  /**
   * Dequeue an event.
   * 
   * @return The event.
   */
  Event dequeEvent() {
    Event event = null;
    try {
      event = eventQueue.take();
    } catch (InterruptedException e) {
      if (event == null) {
        err("could not get non-null event from queue\n");
        return null;
      }
    }
    return event;
  }

  /**
   * Getter method for mainClass.
   * 
   * @return The mainClass.
   */
  public String getMainClass() {
    return mainClass;
  }
}
