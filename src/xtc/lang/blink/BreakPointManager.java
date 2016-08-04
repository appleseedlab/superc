package xtc.lang.blink;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

/**
 * The Blink break point manager.
 * 
 * @author Byeongcheol Lee
 */
public final class BreakPointManager {

  /** The break point state. */
  public enum BreakPointState {
    ENABLED,
    DISABLED
  }

  /** invalid breakpoint identifier. */
  public static final int INVALID_BREAKPOINT_ID = -1;

  /**
   * The debugger.
   */
  private final Blink dbg;

  /** The Blink user break point list. */
  private final HashMap<Integer, BlinkBreakPoint> breakpoints 
    = new HashMap<Integer, BlinkBreakPoint>();

  /** The deferred Native break point list. */
  private final HashMap<Integer, NativeBreakpoint> deferredNativeBreakpoints 
    = new HashMap<Integer, NativeBreakpoint>();

  /** The next identification sequence number.*/
  private int nextUserBreakPointID = 1;

  /** The saved break point state.*/
  private final HashSet<BlinkBreakPoint> frozenBreakpoints = 
    new HashSet<BlinkBreakPoint>(); 

  /**
   * @param dbg The debugger to work with.
   */
  BreakPointManager(Blink dbg) {
    this.dbg = dbg;
  }

  /**
   * Allocate a new identification number.
   * 
   * @return A new identification number.
   */
  private synchronized int getNextUserBreakPointID() {
    return nextUserBreakPointID++;
  }

  /**
   * Add a native user break point.
   * 
   * @param sourceFile The source file name.
   * @param sourceLine The source line number.
   */
  NativeSourceLineBreakPoint setNativeBreakpoint(String sourceFile, int sourceLine) 
     {
    //create a native breakpoint.
    NativeSourceLineBreakPoint nbp;
    boolean deferred;
    if (dbg.IsNativeDebuggerAttached()) {
      dbg.ensureGDBContext();
      int nbpID = dbg.ndb.createBreakpoint(sourceFile, sourceLine);   
      nbp = new NativeSourceLineBreakPoint(nbpID, sourceFile,
          sourceLine);
      deferred = false;
    } else {
      nbp = new NativeSourceLineBreakPoint(sourceFile, sourceLine);
      deferred = true;
      dbg.out("the break point is delayed until the native debugger attached.\n");
    }

    //register
    int id = getNextUserBreakPointID();
    breakpoints.put(id, nbp);
    if (deferred) {
      deferredNativeBreakpoints.put(id, nbp);
    }
    return nbp;
  }

  NativeSymbolBreakpoint setNativeBreakpoint(String symbol)  {
    NativeSymbolBreakpoint nbp;
    boolean deferred;
    if (dbg.IsNativeDebuggerAttached()) {
      dbg.ensureGDBContext();
      int nbpID = dbg.ndb.createBreakpoint(symbol);
      nbp = new NativeSymbolBreakpoint(nbpID, symbol);
      deferred = false;
    } else {
      nbp = new NativeSymbolBreakpoint(symbol);
      deferred = true;
    }
    int id = getNextUserBreakPointID();
    breakpoints.put(id, nbp);
    if (deferred) {
      deferredNativeBreakpoints.put(id, nbp);
    }
    return nbp;
  }

  /**
   * Add a Java user break point.
   * 
   * @param classFile The class name.
   * @param sourceLine The source line number.
   * @return The break point.
   */
  JavaSourceLineBreakPoint setJavaBreakPoint(String classFile, int sourceLine) {
    int id =getNextUserBreakPointID();
    JavaSourceLineBreakPoint jbp = new JavaSourceLineBreakPoint(classFile, sourceLine);
    breakpoints.put(id, jbp);
    if (!jbp.enable(dbg)) {
      dbg.out("the break point is delayed \n");
    }
    return jbp;
  }

  /**
   * Add a Java user break point.
   * 
   * @param cname The class name.
   * @param mname The method name.
   * @return The breakpoint. 
   */
  JavaEntryBreakpoint setJavaBreakPoint(String cname, String mname) {
    int id = getNextUserBreakPointID();
    JavaEntryBreakpoint jbp = new JavaEntryBreakpoint(cname, mname);
    breakpoints.put(id, jbp);
    if (!jbp.enable(dbg)) {
      dbg.out("the break point is delayed\n");
    }
    return jbp;
  }

  /**
   * Implement "delete [n]" command.
   * 
   * @param id The identifier of break point or watch point.
   */
  void clearBreakpoint(int id) {
    if (!breakpoints.containsKey(id)) {
      dbg.err("not valid break point id -" + id);
      return;
    }

    //check deferred break point.
    if (deferredNativeBreakpoints.containsKey(id)) {
      deferredNativeBreakpoints.remove(id);
    } 

    if (breakpoints.containsKey(id)) {
      BlinkBreakPoint bp = breakpoints.get(id);
      bp.disable(dbg);
      breakpoints.remove(id);
    }
  }

  /**
   * Find a breakpoint using the native breakpoint identifier.
   * @param nativeBreakPointID The identifier.
   * @return The Breakpoint identifier. 
   */
  int findNativeBreakpoint(int nativeBreakPointID) {
    for(final int bpid: breakpoints.keySet()) {
      BlinkBreakPoint bp = breakpoints.get(bpid);
      if (bp instanceof NativeBreakpoint) {
        NativeBreakpoint nbp = (NativeBreakpoint)bp;
        if (nbp.getNativeBreakPointID()== nativeBreakPointID) {
          return bpid; //found
        }
      }
    }
    return INVALID_BREAKPOINT_ID; // not found
  }

  int findJavaBreakpoint(String cname, String mname, int lineNumber) {
    for(final int bpid: breakpoints.keySet()) {
      BlinkBreakPoint bp = breakpoints.get(bpid);
      if (bp instanceof JavaSourceLineBreakPoint) {
        JavaSourceLineBreakPoint jbp = (JavaSourceLineBreakPoint)bp;
        if (jbp.getClassName().equals(cname) 
            && jbp.getLineNumber() == lineNumber) {
          return bpid;
        }
      } else if (bp instanceof JavaEntryBreakpoint) {
        JavaEntryBreakpoint jbp = (JavaEntryBreakpoint)bp;
        if (jbp.matches(cname, mname)) {
          return bpid;
        }
      }
    }
    
    return INVALID_BREAKPOINT_ID; // not found
  }
  
  /**
   * Implement "info break" command.
   */
  void showUserBreakPointList() {
    TreeSet<Integer> breakPointIDList = new TreeSet<Integer>();
    breakPointIDList.addAll(breakpoints.keySet());
    StringBuilder sb = new StringBuilder();
    for (final Integer id : breakPointIDList) {
      BlinkBreakPoint bp = breakpoints.get(id);
      sb.append(id).append("  ");
      sb.append(bp.toString()).append('\n');
    }
    dbg.out("%s", sb.toString());
  }

  /**
   * @return true if there is blink deferred C break point.
   */
  boolean hasDeferredNativeBreakpoint() {
    return deferredNativeBreakpoints.size() > 0;
  }

  /**
   * Handle deferred native break points when the shared library is loaded into
   * the debuggee JVM.
   */
  void handleDeferredNativeBreakPoint() {
    assert dbg.IsNativeDebuggerAttached();
    dbg.ensureGDBContext();
    Set<Integer> resolved = new TreeSet<Integer>();
    try {
      for(final Integer id : deferredNativeBreakpoints.keySet()) {
        NativeBreakpoint bp = deferredNativeBreakpoints.get(id);
        if (bp instanceof NativeSourceLineBreakPoint) {
          NativeSourceLineBreakPoint sbp = (NativeSourceLineBreakPoint)bp;
          int nbpid = dbg.ndb.createBreakpoint(sbp.getSourceFileName(), 
              sbp.getSourceLineNumber());
          sbp.setNativeBreakPointID(nbpid);
          resolved.add(id);
        }
      }
    } finally {
      for(final Integer id : resolved) {
        deferredNativeBreakpoints.remove(id);
      }
    }
  }

  /**
   * Freeze all the active user break points for the expression evaluation.
   */
  void freezeActiveBreakPoints() {
    for(BlinkBreakPoint b: breakpoints.values()) {
      BreakPointState s = b.getState();
      if (s == BreakPointState.ENABLED) {        
        if (b.disable(dbg)) {
          frozenBreakpoints.add(b);
        } else {
          dbg.err("could not freeze :  " + b + "\n");
        }
      }
    }
  }

  /**
   * Restore the user break point state after the expression evaluation.
   */
  void unfreezeAllBreakpoints() {
    HashSet<NativeBreakpoint> gdbBreakPointToWake = new HashSet<NativeBreakpoint>();
    HashSet<JavaBreakpoint> jdbBreakPointToWake = new HashSet<JavaBreakpoint>();

    for(BlinkBreakPoint b: frozenBreakpoints) {
      if (b instanceof NativeBreakpoint) {
        gdbBreakPointToWake.add((NativeBreakpoint)b);
      } else if (b instanceof JavaBreakpoint ) {
        jdbBreakPointToWake.add((JavaBreakpoint)b);
      }
    }
    for(JavaBreakpoint b: jdbBreakPointToWake) {
     b.enable(dbg); 
    }    
    for(NativeBreakpoint b: gdbBreakPointToWake) {
      b.enable(dbg); 
     }
    frozenBreakpoints.clear(); 
  }

  /**
   * A base class for the Blink break point.
   */
  static abstract class BlinkBreakPoint {

    /** enable the break point. */
    abstract boolean enable(Blink dbg);

    /** disable the break point. */
    abstract boolean disable(Blink dbg);

    /** query the break point state. */
    abstract BreakPointState getState(); 
  }

  /**
   * A base class for the native break point. 
   */
  static abstract class NativeBreakpoint extends BlinkBreakPoint {
    static final int DEFERRED_BREAKPOINT_ID = -1;
    
    /** The break point state. */
    BreakPointState mdbState = BreakPointState.DISABLED;

    /** The native break point identifier. */
    private int nativeBreakpointID;

    /** Constructor. */
    protected NativeBreakpoint(int nbpID) {
      nativeBreakpointID = nbpID;
    }

    /** Getter/setter method for the nativeBreakPointID. */
    public int getNativeBreakPointID() {
      assert nativeBreakpointID != DEFERRED_BREAKPOINT_ID;
      return nativeBreakpointID;
    }

    public void setNativeBreakPointID(int nativeBreakPointID) {
      assert this.nativeBreakpointID == DEFERRED_BREAKPOINT_ID;
      this.nativeBreakpointID = nativeBreakPointID;
    }

    /** Getter method for break point state. */
    public BreakPointState getState() {
      return mdbState;
    }

    /**
     * Enable the break point.
     * @param dbg The debugger.
     */
    boolean enable(Blink dbg) {
      switch(mdbState) {
      case ENABLED:
        return true;
      case DISABLED:        
        if(!dbg.ensureGDBContext()) {
          return false;
        }
        // try to set the break point
        dbg.ndb.enableBreakpoint(nativeBreakpointID);
        mdbState = BreakPointState.ENABLED;
        return true;
      default:
        assert false : "not reachable.";
        return false;
      }
    }

    /**
     * Disable this break point in the gdb.
     * 
     * @param dbg The Blink debugger.
     */
    boolean disable(Blink dbg) {      
      switch(mdbState) {
      case DISABLED:
        return true;
      case ENABLED:
        if (!dbg.ensureGDBContext()) {
          dbg.err("counld not disable break point: " + this + "\n");
         return false; 
        }
        dbg.ndb.disableBreakpoint(nativeBreakpointID);
        mdbState = BreakPointState.DISABLED;
        return true;
      }
      return false;
    }
  }

  /**
   * A Source level GDB break point.
   */
  static class NativeSourceLineBreakPoint extends NativeBreakpoint {

    /** The source file name.*/
    final String sourceFileName;

    /** The line number in the source file. */
    final int sourceLineNumber;

    /** Constructors. */
    NativeSourceLineBreakPoint(String sname, int lineno) {
      this(DEFERRED_BREAKPOINT_ID, sname, lineno);
    }

    NativeSourceLineBreakPoint(int nbpID, String sname, int lineno) {
      super(nbpID);
      sourceFileName = sname;
      sourceLineNumber = lineno;
    }

    /** Getter method for sourceFileName. */
    String getSourceFileName() {
      return sourceFileName;
    }

    /** Getter method for sourceLineNumber.*/
    int getSourceLineNumber() {
      return sourceLineNumber;
    }

    /**
     * Check the equality.
     * @param o The compared object.
     */
    public boolean equals(Object o) {
      if (o instanceof NativeSourceLineBreakPoint == false)
        return false;
      NativeSourceLineBreakPoint nbp = (NativeSourceLineBreakPoint) o;
      return (this == nbp)
          || (this.sourceFileName.equals(nbp.sourceFileName) && this.sourceLineNumber == nbp.sourceLineNumber);
    }

    /**
     * @return The string representation.
     */
    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("native").append(" ");
      sb.append(sourceFileName).append(":").append(sourceLineNumber);
      return sb.toString();
    }
  }

  static class NativeSymbolBreakpoint extends NativeBreakpoint {
    private final String symbol;

    NativeSymbolBreakpoint(String symbo) {
      this(DEFERRED_BREAKPOINT_ID, symbo);
    }
    NativeSymbolBreakpoint(int nbpID, String symbo) {
      super(nbpID);
      this.symbol = symbo;
    }

    public final String getSymbo() {
      return symbol;
    }
  }
  
  /**
   * A base class for the JDB break point.
   */
  static abstract class JavaBreakpoint extends BlinkBreakPoint {

    /** The break point state. */
    BreakPointState mdbState = BreakPointState.DISABLED;


    /** Getter method for the state. */
    BreakPointState getState() {
      return mdbState;
    }
  }

  /**
   * A source level JDB break point (e.g. Main:12 ).
   */
  static class JavaSourceLineBreakPoint extends JavaBreakpoint {

    /** The source file name. */
    private final String className;

    /** The line number in the source file. */
    private final int lineNumber;

    /**
     * @param sname The source file name.
     * @param lineno The line number.
     */
    JavaSourceLineBreakPoint(String sname, int lineno) {
      className = sname;
      lineNumber = lineno;
    }

    /** Getter method for class name. */
    String getClassName() {return className;}

    /** Getter method for line number. */
    int getLineNumber() {return lineNumber;}

    /**
     * Check the equality.
     * 
     * @param o The compared object.
     */
    public boolean equals(Object o) {
      if (o instanceof NativeSourceLineBreakPoint == false)
        return false;
      JavaSourceLineBreakPoint nbp = (JavaSourceLineBreakPoint) o;
      return (this == nbp)
          || (this.className.equals(nbp.className) && this.lineNumber == nbp.lineNumber);
    }

    /**
     * @return The string representation.
     */
    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append(" ").append("java").append(" ");
      sb.append(className).append(":").append(lineNumber);
      return sb.toString();
    }

    /**
     * Request the jdb to set my break point
     * 
     * @param dbg The debugger.
     */
    boolean enable(Blink dbg) {
      switch(mdbState) {
      case DISABLED:
        if(!dbg.ensureJDBContext()) {
          return false;
        }
        // try to set the break point
        dbg.jdb.setBreakPoint(className, lineNumber);
        mdbState = BreakPointState.ENABLED;
        return true;
      case ENABLED:
        return true;
      }
      return false;
    }

    /**
     * Delete this break.
     * 
     * @param dbg The Blink debugger.
     */
    boolean disable(Blink dbg) {
      switch(mdbState) {
      case DISABLED:
        return true;
      case ENABLED:
        if (!dbg.ensureJDBContext()) {
          return false;
        }
        dbg.jdb.clearBreakPoint(className, lineNumber);
        mdbState = BreakPointState.DISABLED;
        return true;
      }
      return false;
    }
  }

  /**
   * A JDB method name break point. (e.g. Foo.bar() ).
   */
  static class JavaEntryBreakpoint extends JavaBreakpoint {
    private final String cname;
    private final String mname;

    /**
     * @param classAndmethod The class name and method.
     */
    public JavaEntryBreakpoint(final String cname, final String mname) {
      super();
      this.cname = cname;
      this.mname = mname;
    }

    /** Getters. */
    public String getCname() {return cname;}
    public String getMname() {return mname;}

    public boolean matches(String cname, String mname) {
      return this.cname.equals(cname) && this.mname.equals(mname);
    }
    /**
     * Enable the break point.
     * @param dbg The debugger.
     */
    boolean enable(Blink dbg) {
      switch(mdbState) {
      case DISABLED:
        if(!dbg.ensureJDBContext()) {
          return false;
        }
        // try to set the break point
        dbg.jdb.setBreakPoint(cname + "." + mname);
        mdbState = BreakPointState.ENABLED;
        return true;
      case ENABLED:
        return true;
      }
      return false;
    }

    /**
     * Disable the break point.
     * @param dbg The Blink debugger.
     */
    boolean disable(Blink dbg) {
      switch(mdbState) {
      case DISABLED:
        return true;
      case ENABLED:
        if (!dbg.ensureJDBContext()) {
          return false;
        }
        dbg.jdb.clearBreakPoint(cname + "." + "mname");
        mdbState = BreakPointState.DISABLED;
        return true;
      }
      return false;
    }
  }
}
