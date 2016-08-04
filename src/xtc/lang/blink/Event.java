package xtc.lang.blink;

import xtc.lang.blink.NativeDebugger.LanguageTransitionEventType;

/** A common Blink event class. */
public abstract class Event {

  /** dummy event source when we do not care about the source. */
  public static final BlinkEventSource dummySource = new BlinkEventSource() {
    public String getEventSourceName() {
      return "dummy";
    }
  };
  
  /** The intended consumer of a Blink event. */
  public enum EventConsumer {
    BlinkController,
    JavaDebugger,
    NativerDebugger,
  }
  
  /** The Blink event source. */
  final BlinkEventSource source;

  /** The event consumer. */
  final EventConsumer consumer;
  
  /**
   * Constructor.
   * 
   * @param source The event source.
   */
  Event(BlinkEventSource source) {
    this(source, EventConsumer.BlinkController);
  }
  
  /**
   * Constructor.
   * 
   * @param source The source.
   */
  Event(BlinkEventSource source, EventConsumer consumer) {
    assert source != null;
    this.source = source;
    this.consumer = consumer;
  }

  /** Getter method for the EventSource. */
  public BlinkEventSource getSource() {
    return source;
  }

  /** User-friendly description of this event type. */
  public abstract String getName();
  
  /** User-friendly description. */
  public String toString() {
    return "Event[" + getName() 
      + "," + getSource().getEventSourceName()  
      + "," + consumer
      + "]";
  }

  /** The Blink event source tag. */
  static interface BlinkEventSource {

    /** Getter method for readable event source. */
    public abstract String getEventSourceName();
  }

  /**
   * A Blink user command event.
   */
  static class UserCommandEvent extends Event {

    /** The Blink user command. */
    private final String userCommand;

    /**
     * Constructor.
     * 
     * @param source The event source.
     * @param line The command line.
     */
    UserCommandEvent(CommandLineInterface source, String line) {
      super(source);
      this.userCommand = line;
    }

    /** Getter method for the User command. */
    public String getCommandLine() {
      return userCommand;
    }
    
    /** User-friendly description of this event type. */
    public String getName() {
      return "UserCommand";
    }

    /** User friendly message.*/
    public String toString() {
      return super.toString() + userCommand;
    }
  }

  /** The raw text output message event. */
  static class RawTextMessageEvent extends Event {

    /** The message. */
    final char[] message;

    /**
     * Constructor.
     * 
     * @param source The source micro debugger.
     * @param message The message.
     */
    RawTextMessageEvent(BlinkEventSource source, char[] message) {
      this(source, message, 0, message.length);
    }

    /**
     * Constructor.
     * 
     * @param source THe source.
     * @param msgBuf The buffer.
     * @param index The beginning of the message with the buffer. 
     * @param len The message length.
     */
    RawTextMessageEvent(BlinkEventSource source,
        char[] msgBuf, int index, int len) {
      super(source);
      assert msgBuf != null && index >= 0 && len > 0
          && msgBuf.length >= (index + len);
      this.message = new char[len];
      System.arraycopy(msgBuf, index, message, 0, len);
    }

    /** Getter method for the message. */
    char[] getMessage() {
      return message;
    }

    /** User-friendly description of this event type. */
    public String getName() {
      return "RawMessage";
    }

    /**
     * Obtain a user readable description of this event.
     * 
     * @return The description.
     */
    public String toString() {
      return super.toString()
        + new String(message);//.replace("\n", "\\n"); 
    }
  }

  /** The session finish request event. */
  public static class SessionFinishRequestEvent extends Event {
    /** The user friendly Reason. */
    private final String reason;
    
    /** The constructor.*/
    SessionFinishRequestEvent(String reason) {
      super(dummySource);
      this.reason = reason;
    }

    /** The getter for the reason. */
    public String getReason() {
      return reason;
    }
    
    /** User-friendly description of this event type. */
    public String getName() {
      return "BlinkSessionEnd";
    }

    public String toString() {
      return super.toString()
        + reason;
    }
  }

  /** A base event class for the sub-debugger event. */
  static abstract class SubDebuggerEvent extends Event {
    SubDebuggerEvent(BlinkEventSource s) {
      super(s);
    }
  }
  
  /** A death event class. */
  static class DeathEvent extends SubDebuggerEvent {

    /**
     * Constructor.
     * @param source The source.
     */
    DeathEvent(BlinkEventSource source) {
      super(source);
    }

    public String getName() {
      return "Death";
    }
  }

  /** A Language transition event. */
  static abstract class LanguageTransitionEvent extends SubDebuggerEvent {
    final LanguageTransitionEventType bptype;
  
    public LanguageTransitionEvent(NativeDebugger s,
        LanguageTransitionEventType bptype) {
      this(s, bptype, null);
    }
    public LanguageTransitionEvent(NativeDebugger s,
        LanguageTransitionEventType bptype, String c2jtarget) {
      super(s);
      this.bptype = bptype;
    }
  }
  
  static final class Java2NativeCallEvent extends LanguageTransitionEvent {
    Java2NativeCallEvent(NativeDebugger s) {
      super(s, LanguageTransitionEventType.J2C_CALL);
    }
    public String getName() {return "Java2NativeCallEvent";}
  }
  static final class Java2NativeReturnEvent extends LanguageTransitionEvent {
    private final String targetClassName;
    private final int targetLineNumber;
    Java2NativeReturnEvent(NativeDebugger s, String javaTarget, int targetLineNumber) {
      super(s, LanguageTransitionEventType.J2C_RETURN);
      this.targetClassName = javaTarget;
      this.targetLineNumber = targetLineNumber;
    }
    public int getTargetLineNumber() {return targetLineNumber;}
    public String getJavaTarget() {return targetClassName;}
    public String getName() {return "Java2NativeReturnEvent";}
  }

  static final class Native2JavaCallEvent extends LanguageTransitionEvent {
    private final String cname; /* Target java class name.*/
    private final int lineNumber; /* Target line number. */ 
    Native2JavaCallEvent(NativeDebugger s, String cname, int lineNumber) {
      super(s, LanguageTransitionEventType.C2J_CALL);
      this.cname = cname;
      this.lineNumber = lineNumber;
    }
    public String getClassName() {return cname;}
    public int getLineNumber() {return lineNumber;}
    public String getName() {return "Native2JavaCallEvent";}
  }
  static final class Native2JavaReturnEvent extends LanguageTransitionEvent {
    Native2JavaReturnEvent(NativeDebugger s) {
      super(s, LanguageTransitionEventType.C2J_RETURN);
    }
    public String getName() {return "Native2JavaReturnEvent";}
  }

  /** A native break point hit. */
  static class NativeBreakPointHitEvent extends SubDebuggerEvent {
    private final int debuggerBreakpointID;
    private final String message;
    
    public NativeBreakPointHitEvent(BlinkEventSource s, int bpid, String message) {
      super(s);
      this.debuggerBreakpointID = bpid;
      this.message = message;
    }

    /** Getters. */
    public int getDebuggerBreakpointID() {return debuggerBreakpointID;}
    public String getMessage() {return message;}
    public String getName() {return "NativeBreakPointHit";}
  }
  
  static class NativeSignalEvent extends SubDebuggerEvent {
    final String signal;
    NativeSignalEvent(BlinkEventSource s, String signal) {
      super(s);
      this.signal = signal;
    }
    public String getName() {
      return "SignalEvent";
    }
  }


  static class NativeJNIWarningEvent extends SubDebuggerEvent {
    private final String message;

    public NativeJNIWarningEvent(BlinkEventSource s,
        String message) {
      super(s);
      this.message = message;
    }
    public String getMessage() {return message;}
    public String getName() {return "JNIWarningEvent";}
  }

  /** J2C completion event.*/
  static class Native2JavaCompletionEvent extends SubDebuggerEvent {
    public Native2JavaCompletionEvent(NativeDebugger s) {
      super(s);
    }
    /** User-friendly description of this event type. */
    public String getName() {
      return "Native2JavaCompletionEvent";
    }
  }
  
  /** A native stop completion event. */
  static class NativeStepCompletionEvent extends SubDebuggerEvent {
 
    public NativeStepCompletionEvent(NativeDebugger s) {
      super(s);
    }

    /** User-friendly description of this event type. */
    public String getName() {
      return "NativeStepCompleted";
    }
  }

  /** The J2C break point hit event. */
  static class J2CBreakPointHitEvent extends SubDebuggerEvent {

    public J2CBreakPointHitEvent(NativeDebugger s) {
      super(s);
    }
    /** User-friendly description of this event type. */
    public String getName() {
      return "J2CHit";
    }
  }

  static class DummyCallCompletionEvent extends SubDebuggerEvent {
    public DummyCallCompletionEvent(NativeDebugger s) {
      super(s);
    }
    public String getName() {return "DummyCallCompletionEvent";}
  }
  
  /** A Java debugger event that cause the JVM to stop. */
  static abstract class JavaPauseEvent extends SubDebuggerEvent {
    final private String threadName;
    final private String className;
    final private int lineNumber;
    final private String methodName;
    final private int bcindex;
    final private String message;

    public JavaPauseEvent(BlinkEventSource s, String threadName, 
        String className, int lineNumber,
        String methodName, int bcindex, String message) {
      super(s);
      this.threadName = threadName;
      this.className = className;
      this.lineNumber = lineNumber;
      this.methodName = methodName;
      this.bcindex = bcindex;
      this.message = message;
    }
    /** Getters. */
    public String getThreadName() {return threadName;}
    public String getClassName() {return className;}
    public int getLineNumber() {return lineNumber;}
    public String getMethodName() {return methodName;}
    public int getBcindex() {return bcindex;}
    public String getMessage() {return message;}
  }
  
  /** Java breakpoint event. */
  static class JavaBreakPointHitEvent extends JavaPauseEvent {
    public JavaBreakPointHitEvent(JavaDebugger s, String threadName, 
        String className, int lineNumber,
        String methodName, int bcindex, String message) {
      super(s, threadName, className, lineNumber, methodName, bcindex, message);
    }
    public String getName() {return "JavaBPHit";}
  }

  /** Java step completion event. */
  static class JavaStepCompletionEvent extends JavaPauseEvent {
    public JavaStepCompletionEvent(JavaDebugger s, String threadName, 
        String className, int lineNumber,
        String methodName, int bcindex, String message) {
      super(s, threadName, className, lineNumber, methodName, bcindex, message);
    }
    public String getName() {return "JavaStepCompleted";}
  }

  /** Java exception event. */
  static class JavaExceptionEvent extends JavaPauseEvent {
      private final String exceptionClass;
      public JavaExceptionEvent(JavaDebugger s, String threadName, 
          String className, int lineNumber,
          String methodName, int bcindex, String message, String exceptionClass) {
        super(s, threadName, className, lineNumber, methodName, bcindex, message);
        this.exceptionClass = exceptionClass;
      }
      public String getExceptionClass() {return exceptionClass;}
      public String getName() {return "JavaExceptionOccured";}
  }

  /** A Java load library event. */
  static class JavaLoadLibraryEvent extends JavaPauseEvent {
    public JavaLoadLibraryEvent(JavaDebugger s, String threadName, 
        String className, int lineNumber,
        String methodName, int bcindex, String message) {
      super(s, threadName, className, lineNumber, methodName, bcindex, message);
    }
    /** User-friendly description of this event type. */
    public String getName() {return "JavaLoadLibrary";}
  }
  /** J2C completion event.*/
  static class Java2NativeCompletionEvent extends SubDebuggerEvent {
    public Java2NativeCompletionEvent(JavaDebugger s) {
      super(s);
    }
    /** User-friendly description of this event type. */
    public String getName() {
      return "J2CCompletion";
    }
  }
}
