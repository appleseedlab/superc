package xtc.lang.blink;

import xtc.lang.blink.Blink.DebugerControlStatus;
import xtc.lang.blink.Event.JavaBreakPointHitEvent;
import xtc.lang.blink.Event.JavaPauseEvent;
import xtc.lang.blink.Event.JavaExceptionEvent;
import xtc.lang.blink.Event.JavaLoadLibraryEvent;
import xtc.lang.blink.Event.DeathEvent;
import xtc.lang.blink.Event.NativeJNIWarningEvent;
import xtc.lang.blink.Event.SubDebuggerEvent;
import xtc.lang.blink.Event.NativeBreakPointHitEvent;
import xtc.lang.blink.Event.NativeSignalEvent;
import xtc.lang.blink.Event.UserCommandEvent;
import xtc.lang.blink.Event.SessionFinishRequestEvent;
import xtc.tree.GNode;

/**
 * The Blink event loop.
 *
 * @author Byeongcheol Lee
 */
public class EventLoop {

  /** The Blink debugger. */
  private final Blink dbg;

  /** The Blink command interpreter. */
  final CommandInterpreter interpreter;

  /** keeping state of sub systems. */
  private boolean jvmFinished = false;
  private boolean jdbFinisned = false;
  private boolean gdbFinished = false;

  /**
   * Constructor.
   * 
   * @param dbg The Blink debugger.
   */
  EventLoop(Blink dbg) {
    this.dbg = dbg;
    this.interpreter = new CommandInterpreter(dbg, dbg.breakpointManager);
  }

  /**
   * Run the main event loop. Wait until an event is available in the event
   * queue, and, if the event is ready, dequeue this event. Then, dispatch the
   * event to the corresponding handler, depending on the event type. This
   * command loop may return if any micro debuggers such as jdb and gdb
   * terminates or if the user asks the termination by typing "exit" command.
   * @ 
   */
  void main()  {
    boolean exitRequested = false;
    while (!exitRequested) {
      Event e = dbg.dequeEvent();
      if (e instanceof DeathEvent) {
        dbg.exit();
        assert false : "unreachable";
        break;
      }
      switch(e.consumer) {
      case BlinkController:
        if (e instanceof UserCommandEvent) {
          dispatch((UserCommandEvent) e);
        } else if (e instanceof SubDebuggerEvent) {
          dispatch((SubDebuggerEvent) e);
        } else if (e instanceof SessionFinishRequestEvent) {
          exitRequested = true;
         }
        break;
      case JavaDebugger:
        dbg.jdb.dispatch(e);
        break;
      case NativerDebugger:
        dbg.ndb.dispatch(e);
        break;
      }
    }
  }
  
  /**
   * Run a command, and repeat event dispatch to the handler until the handler
   * is satisfied.
   *
   * @param handler The message handler for the replier.
   * @return The response from the reply handler.
   */
  public static Object subLoop(Blink dbg, ReplyHandler handler)
     {

    // wait until the replyHandler is satisfied.
    boolean satisfied = false;
    while (!satisfied) {
      Event e = dbg.dequeEvent();
      if (e instanceof DeathEvent) {
        dbg.exit();
        assert false : "unreachable";
        break;
      }
      switch(e.consumer) {
      case BlinkController:
        if (e instanceof UserCommandEvent) {
          dbg.eventLoop.dispatch((UserCommandEvent) e);
        } else {
          satisfied = handler.dispatch(e);
        }
        break;
      case JavaDebugger:
          dbg.jdb.dispatch(e);
        break;
      case NativerDebugger:
          dbg.ndb.dispatch(e);
        break;
      }
    }
    assert satisfied == true;

    return handler.getResult();
  }

  /**
   * Dispatch a user command event.
   * 
   * @param e The event.
   */
  void dispatch(UserCommandEvent e) {
    String line = e.getCommandLine();
    executeBlinkCommand(line);
    dbg.showPrompt();
  }

  /**
   * Dispatch an asynchronous micro DebuggerUserdebugger event.
   * 
   * @param e The event.
   * @ 
   */
  private void dispatch(SubDebuggerEvent e)  {
    if (e instanceof DeathEvent) {
      dispatch((DeathEvent) e);
    } else if (e instanceof JavaLoadLibraryEvent) {
        dispatch((JavaLoadLibraryEvent)e);
    } else if (e instanceof NativeBreakPointHitEvent) {
      dispatch((NativeBreakPointHitEvent)e);
    } else if (e instanceof NativeJNIWarningEvent) {
      dispatch((NativeJNIWarningEvent)e);
    } else if (e instanceof JavaPauseEvent) {
      dispatch((JavaPauseEvent)e);
    } else if (e instanceof NativeSignalEvent) {
      dispatch((NativeSignalEvent)e);
    } else {
      assert false;
    }
  }

  /**
   * Dispatch an asynchronous component debugger death event.
   * 
   * @param e The event.
   */
  private void dispatch(DeathEvent e) {
    if (e.getSource() == dbg.jvm) {
      assert jvmFinished == false : "no double death!";
      jvmFinished = true;
    } else if (e.getSource() == dbg.jdb) {
      assert jdbFinisned == false : "no double death!";
      jdbFinisned = true;
    } else if (e.getSource() == dbg.ndb) {
      assert gdbFinished == false;
      gdbFinished = true;
    }

    // check whether or not to finish the debugging session.
    if (jvmFinished && jdbFinisned 
        && (!dbg.IsNativeDebuggerAttached() || gdbFinished)) {
      dbg.enqueEvent(new SessionFinishRequestEvent("Application finished"));
    }
  }

  /**
   * Run a macro user command.
   * 
   * @param command The command. 
   */
  void executeBlinkCommand(String command) {
    // try parsing and executing the command line.
    final String language = dbg.getCurrentLanguageContext();
    final Object astOrMsg = Utilities.debuggerParseAndAnalyze(language, command);
    if (astOrMsg instanceof GNode) {
      final GNode ast = (GNode) astOrMsg;
      interpreter.dispatch(ast);
    } else {
      dbg.err((String) astOrMsg);
    }
  }

  /**
   * The jdb hits the System.loadLibrary event.
   * 
   * @param slave The slave process that gets the System.loadLibrary event.
   */
  private synchronized void dispatch(JavaLoadLibraryEvent e) {
    assert dbg.getDebugControlStatus() == DebugerControlStatus.NONE;
    dbg.changeDebugControlStatus(DebugerControlStatus.JDB);
    dbg.jdb.resetLoadLibraryEvent();
    dbg.jdb.prepareLoadLibrary();
    if (dbg.ensureDebugAgent()) {
      if (dbg.breakpointManager.hasDeferredNativeBreakpoint()) {
        dbg.breakpointManager.handleDeferredNativeBreakPoint();
      }        
    } else {
      dbg.jdb.setLoadLibraryEvent();
    }
    dbg.ensureJDBContext();
    dbg.jdb.cont();
    dbg.changeDebugControlStatus(DebugerControlStatus.NONE);
  }

  /**
   * The Java break point hit notification.
   * 
   * @param classAndMethod The class and name pair.
   * @param line The line number.
   * @param sourceLine The source line.
   */
  private void dispatch(JavaPauseEvent e) {
    assert dbg.getDebugControlStatus() == DebugerControlStatus.NONE;
    dbg.changeDebugControlStatus(DebugerControlStatus.JDB); 
    reportEvent(dbg, e);
    dbg.showPrompt();
  }

  /**
   * @param e The native break point hit event.
   */
  private void dispatch(NativeBreakPointHitEvent e) {
    assert dbg.getDebugControlStatus() == DebugerControlStatus.NONE;
    dbg.changeDebugControlStatus(DebugerControlStatus.GDB);
    reportEvent(dbg, e);
    dbg.showPrompt();
  }

  private void dispatch(NativeSignalEvent e)  {
    assert dbg.getDebugControlStatus() == DebugerControlStatus.NONE;    
    dbg.changeDebugControlStatus(DebugerControlStatus.GDB);
    int s = Integer.valueOf(dbg.ndb.eval(null, "(int)bda_tls_state"));
    if (s != 0) {
      String mode = dbg.ndb.eval(null, "bda_tls_state->mode");
      if ("JVM".equals(mode)) {
         dbg.cont();
         return;
      }
    }
    reportEvent(dbg, e);
    dbg.showPrompt();
  }

  /**
   * Report there is potential JNI function misuse that might crash 
   * the JVM.
   *
   * @param e The native JNI warning event.
   */
  private void dispatch(NativeJNIWarningEvent e) {
    dbg.changeDebugControlStatus(DebugerControlStatus.GDB);
    dbg.out("JNI warning: %s\n", e.getMessage());
    dbg.showPrompt();
  }

  public static void reportEvent(Blink dbg, JavaPauseEvent e) {
    if (e instanceof JavaBreakPointHitEvent) {
      BreakPointManager bpManger = dbg.breakpointManager;
      int bpid = bpManger.findJavaBreakpoint(e.getClassName(), e.getMethodName(), e.getLineNumber());
      String bpidMsg = bpid == BreakPointManager.INVALID_BREAKPOINT_ID ? "?"
          : String.valueOf(bpid);
      dbg.out("Breakpoint %s: thread=%s, %s.%s(), line=%d, bci=%d\n%s", 
          bpidMsg, e.getThreadName(), e.getClassName(), e.getMethodName(),
          e.getLineNumber(), e.getBcindex(), e.getMessage());
    } else if (e instanceof JavaExceptionEvent) {
      JavaExceptionEvent je = (JavaExceptionEvent)e;
      dbg.out("Java exception occured: %s thread=%s, %s.%s(), line=%d bci=%d\n%s",
          je.getExceptionClass(), je.getThreadName(),
          je.getClassName(), je.getMethodName(), 
          e.getLineNumber(), e.getBcindex(), e.getMessage());  
    }
  }

  public static void reportEvent(Blink dbg, NativeBreakPointHitEvent e) {
    BreakPointManager bpManger = dbg.breakpointManager;    
    int bpid = bpManger.findNativeBreakpoint(e.getDebuggerBreakpointID());
    String bpidMsg = bpid == BreakPointManager.INVALID_BREAKPOINT_ID ? "?"
        : String.valueOf(bpid); 
    dbg.out("Breakpoint %s: %s\n", bpidMsg, e.getMessage());
  }

  public static void reportEvent(Blink dbg, NativeSignalEvent e) {
    dbg.out("Signal received: %s\n", e.signal);
  }

  /**
   * A reply handler for the micro debugger. This handler takes and parses a
   * multiple number of events from the micro debugger until some condition is
   * satisfied. If the condition is satisfied, the dispatchMessage will record
   * some summary of the received events.
   */
  abstract static class ReplyHandler {

    /** The result for the reply. */
    protected Object result;

    /**
     * @param result The result of handling the reply.
     */
    protected void setResult(Object result) {
      assert this.result == null : "the result is set only once";
      this.result = result;
    }

    /**
     * @return The result object
     */
    public Object getResult() {
      return result;
    }

    /**
     * Takes an event and consider the previous events to see some waiting
     * condition is satisfied. If this method returns null,
     * 
     * @param e The event.
     * @return true if some condition is satisfied.
     * @ 
     */
    abstract boolean dispatch(Event e) ;
  }
}
