package xtc.lang.blink;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.io.File;

import xtc.lang.blink.CallStack.NativeCallFrame.NativeFrameType;

/**
 * The Java/C mixed call stack representation.
 * 
 * @author Byeongcheol Lee
 */
public final class CallStack {

  /** The language of the stack frame. */
  static enum FrameLanguage {JAVA, C, JEANNIE};

  /**
   * Extract a mixed language call stack.
   * 
   * @param dbg The Blink debugger.
   * @param remapper The symbol remapper.
   * @return The call stack.
   */
  public static CallStack extractCallStack(Blink dbg, SymbolMapper remapper) {
    FrameLanguage lang;
    List<JavaCallFrame> jFrames;
    List<NativeCallFrame> nFrames;
    switch (dbg.getDebugControlStatus()) {
    case JDB:
      lang = FrameLanguage.JAVA;
      // get java frames
      jFrames = dbg.jdb.getFrames();
      // get C frames
      dbg.j2c();
      nFrames = dbg.ndb.getFrames(); 
      dbg.jret();
      //remove naive frames due to the j2c transition. 
      nFrames.remove(0);
      nFrames.remove(0);
      break;
    case GDB:
      lang = FrameLanguage.C;
      // get C frames
      nFrames = dbg.ndb.getFrames();
      // get Java frames.
      dbg.c2j();
      jFrames = dbg.jdb.getFrames();
      dbg.jret();
      break;
    default:
      assert false : "should not be reachable.";
      return null;
    }

    // build mixed frames.
    List<MicroCallFrame> interleaved = interleaveFrames(lang, jFrames, nFrames);
    List<MicroCallFrame> simplified = simplifyFrames(interleaved);
    List<ICallFrame> mixed = processJeannieFrames(simplified, remapper);

    CallStack callStack = new CallStack(mixed);
    return callStack;
  }

  /**
   * Interleave call frames beginning with the current language.
   *
   * @param lang The top frame language.
   * @param jframes The Java frames.
   * @param nframes The native frames.
   * @return The interleaved frames.
   */
  private static List<MicroCallFrame> interleaveFrames(FrameLanguage lang,
      List<JavaCallFrame> jframes, List<NativeCallFrame> nframes) {
    LinkedList<MicroCallFrame> interleaved = new LinkedList<MicroCallFrame>();
    ListIterator<JavaCallFrame> jframeIt = jframes.listIterator();
    ListIterator<NativeCallFrame> nframeIt = nframes.listIterator();
    NativeCallFrame nframe = nframeIt.hasNext() ? nframeIt.next() : null;
    JavaCallFrame jframe = jframeIt.hasNext() ? jframeIt.next() : null;
    while(nframe != null || jframe != null) {
      switch(lang) {
      case C:
        if (nframe != null) {
          interleaved.addLast(nframe);
          if (nframe.getType() == NativeFrameType.J2C_PROXY) {
            lang = FrameLanguage.JAVA;
            assert jframe != null && jframe.isJavaNativeMethod();
          }
          nframe = nframeIt.hasNext() ? nframeIt.next() : null;
        } else {
          lang = FrameLanguage.JAVA;
        }
        break;
      case JAVA:
        if (jframe != null) {
          interleaved.addLast(jframe);
          if (jframeIt.hasNext()) {
            jframe = jframeIt.next();
            if (jframe.isJavaNativeMethod()) {
              lang = FrameLanguage.C;
              assert nframe != null;
              assert nframe.getType() == NativeFrameType.C2J_PROXY;
            }
          } else {
            jframe = null;
          }
        } else {
          lang = FrameLanguage.C;
        }
        break;
      }
    }
    return interleaved;
  }

  /**
   * Simplify the input call frames by eliminating agent frames and redundant
   * frames.
   * 
   * @param interleaved The interleaved frames.
   * @return The simplified frames.
   */
  private static List<MicroCallFrame> simplifyFrames(
      List<MicroCallFrame> interleaved) {
    LinkedList<MicroCallFrame> simplified = new LinkedList<MicroCallFrame>();
    for(final MicroCallFrame frame: interleaved) {
      if (frame instanceof JavaCallFrame) {
        JavaCallFrame jframe = (JavaCallFrame)frame;
        if (!jframe.isJavaNativeMethod()) {
          simplified.add(jframe);
        }
      } else if (frame instanceof NativeCallFrame) {
        NativeCallFrame nframe = (NativeCallFrame)frame;
        NativeFrameType type = nframe.getType();
        switch(type) {
        case NORMAL:
          simplified.add(nframe);
          break;
        case J2C_PROXY:
        case C2J_PROXY:
          break;
        default:
          assert false : "not reachable";
          break;
        }
      } else {
        assert false : "not reachable";
      }
    }
    return simplified;
  }

  /**
   * Condense a sequence Java and native frames into a single Jeannie frame.
   * Condense as much as possible, and return mixed Java, native and Jeannie
   * frames.
   * 
   * @param frames The interleaved frame.
   * @param remapper The symbol remapper.
   * @return The mixed frames.
   */
  private static List<ICallFrame> processJeannieFrames(
      List<MicroCallFrame> frames, SymbolMapper remapper) {
    List<ICallFrame> mixedFrames = new LinkedList<ICallFrame>();
    LinkedList<MicroCallFrame> framesForJeannie = null;
    String jeannieMethodName = null;
    for (final MicroCallFrame frame : frames) {
      String sname = frame.getSymbolName();
      String srcName = frame.getSourceFile();
      SymbolMapper.MethodRemapEntry e = null;
      if (srcName != null && new File(srcName).canRead()) {
        e = remapper.lookupMethodRemap(sname, srcName);
      }
      boolean isJeannieMicroFrame = (e != null);
      if (isJeannieMicroFrame) {
        if (framesForJeannie == null) {
          // The start of the Jeannie frame.
          jeannieMethodName = e.getSourceLanguageName();
          framesForJeannie = new LinkedList<MicroCallFrame>();
        }
        // The middle or the end of Jeannie frame.
        framesForJeannie.add(frame);
      } else {
        // Flush any pending Jeannie frame.
        if (framesForJeannie != null) {
          mixedFrames.add(new JeannieCallFrame(jeannieMethodName,
              framesForJeannie));
          framesForJeannie = null;
        }
        // add a normal Java/C frame.
        mixedFrames.add(frame);
      }
    }
    // Flush any pending Jeannie frame.
    if (framesForJeannie != null) {
      mixedFrames.add(new JeannieCallFrame(jeannieMethodName, framesForJeannie));
      framesForJeannie = null;
    }
    return mixedFrames;
  }

  /**
   * Create a user readable representation of java and native frames for
   * debugging purpose.
   * 
   * @param jframes The Java frames.
   * @param nframes The native frames.
   * @return The user readable string representation.
   */
  private static String toString(List<JavaCallFrame> jframes, 
      List<NativeCallFrame> nframes) {
    StringBuffer buf = new StringBuffer();
    buf.append("Dumping java and native frames\n");
    buf.append("Java frames: \n");
    for(JavaCallFrame f : jframes) {
      buf.append(f.toString()).append('\n');
    }
    buf.append("Native frames: \n");
    for(NativeCallFrame f : nframes) {
      buf.append(f.toString()).append('\n');
    }
    return buf.toString();
  }

  /** a list of Java, C, and Jeannie call frames. */
  private final List<ICallFrame> mixedFrames;

  /**
   * The constructor.
   *
   * @param mixedFrames The mixed Java/C frame.
   * @param topFrameLanguage The language of the top frame.
   * @param javaFrames The list of Java call frames.
   * @param nativeFrames The list of Native call frames.
   */
  private CallStack(List<ICallFrame> mixedFrames) {
    this.mixedFrames= mixedFrames;
  }

  /**
   * Get mixed stack frame by specifying its id.
   *  
   * @param id the frame id.
   */
  public ICallFrame getCallFrame(int id) {
    assert id >= 0 && id < size();
    return mixedFrames.get(id);
  }

  /**
   * Try to get Java frame at a frame id. If the frame at the id is Java frame,
   * just return this frame. If the frame is a Jeannie macro frame, try obtaining
   * a Java frame within the Jeannie macro frame. Otherwise, just return null.
   *
   * @param id The frame identifier.
   * @return The Java frame or null. 
   */
  public NativeCallFrame getNativeCallFrame(int id) {
    ICallFrame f = getCallFrame(id);
    if (f instanceof NativeCallFrame) {
      return (NativeCallFrame)f;
    } else if (f instanceof JeannieCallFrame) {
      JeannieCallFrame jeannieFrame = (JeannieCallFrame)f;
      return jeannieFrame.getTopNativeFrame();
    } else {
      assert f instanceof JavaCallFrame;
      return null;
    }
  }

  /**
   * Try to get Native frame at a frame id. If the frame at the id is native
   * frame, just return this frame. If the frame is a Jeannie macro frame, try
   * obtaining a native frame within the Jeannie macro frame. Otherwise, just
   * return null.
   * 
   * @param id The frame identifier.
   * @return The native frame or null.
   */
  public JavaCallFrame getJavaCallFrame(int id) {
    ICallFrame frame = getCallFrame(id);
    if (frame instanceof JavaCallFrame) {
      return (JavaCallFrame)frame;
    } else if (frame instanceof JeannieCallFrame) {
      JeannieCallFrame jeannieFrame = (JeannieCallFrame)frame;
      return jeannieFrame.getTopJavaFrame();
    } else {
      assert frame instanceof NativeCallFrame;
      return null;
    }
  }

  /**
   * Get the number of the mixed frames.
   * 
   * @return The size of the mixed frame. 
   */
  public int size() {
   return mixedFrames.size(); 
  }

  /**
   * Get the readable representation of this mixed frame.
   * 
   * @return The string representation.
   */
  public String toString() {
    StringBuffer sb = new StringBuffer();
    sb.append("Mixed frames\n");
    int i = 0;
    for(final ICallFrame f : mixedFrames) {
      sb.append("  [" + (i++) + "]" + f + "\n");
    }
    return sb.toString();
  }

  /**
   * The unified call frame interface for mixed langauage.
   */
  static interface ICallFrame {

    /** Getter for the name. */
    public String getName();
    
    /** Getter for the line number. */
    public int getLineNumber();

    /** Getter for the source file. */
    public String getSourceFile();

    /** Getter for the top micro frame. */
    public MicroCallFrame getTopMicroFrame();

    /** Get the langauge. */
    public FrameLanguage getLanguage(); 
  }

  /**
   * A base class for the mixed language frame. 
   */
  static abstract class MicroCallFrame implements ICallFrame {

    /** The source file name. */
    private final String sourceFile;

    /** The line number.*/
    private final int lineNumber;

    /** The constructor. */
    protected MicroCallFrame(final String sourceFile, final int lineNumber) {
      this.sourceFile = sourceFile;
      this.lineNumber = lineNumber;
    }

    /** Getter method for the line number. */
    public final int getLineNumber() {
      return lineNumber;
    }

    /** Getter method for the source file. */
    public final String getSourceFile() {
      return sourceFile;
    }

    /** Getter method for the symbol name. */
    public abstract String getSymbolName();
  }

  /**
   * A Java call frame representation. 
   */
  static class JavaCallFrame extends MicroCallFrame {

    /** The jdb indentifier. */
    private final int frameID;

    /** The class name. */
    private final String className;

    /** The method name. */
    private final String methodName;

    /** Wheather or not Java native method. */
    private final boolean isJavaNativeMethod;

    /**
     * The constructor. 
     * 
     * @param jdbIdentifier The jdb identifier.
     * @param sourceFile The source file name.
     * @param lineNumber The line number.
     * @param isJavaNativeMethod The Java native method flag.
     * @param className The class name.
     * @param methodName The method name.
     */
    protected JavaCallFrame(int jdbIdentifier, String sourceFile,
        int lineNumber, boolean isJavaNativeMethod, String className,
        String methodName) {
      super(sourceFile, lineNumber);
      /** The identifier that the gdb can recognize.*/
      this.frameID = jdbIdentifier;
      this.className = className;
      this.methodName = methodName;
      this.isJavaNativeMethod = isJavaNativeMethod;
    }

    public String getName() {
        return String.format("%s.%s", className, methodName);
    }

    public int getJdbIdentifier() {
      return frameID;
    }
    public final String getClassName() {
      return className;
    }
    public final String getMethodName() {
      return methodName;
    }
    public FrameLanguage getLanguage() {
      return FrameLanguage.JAVA;
    }
    public String getSymbolName() {
      return className+ "."+methodName;
    }
    public MicroCallFrame getTopMicroFrame() {
      return this;
    }
    public final boolean isJavaNativeMethod() {
      return isJavaNativeMethod;
    }

    /**
     * Get readable representation.
     * 
     * @return The representation.
     */
    public String toString() {
      StringBuffer sb = new StringBuffer();
      sb.append(className);
      sb.append('.');
      sb.append(methodName);
      if (getSourceFile() != null && getLineNumber() >= 1) {
        sb.append("  (" + getSourceFile() + ":" + getLineNumber() + ")");
      } else {
        sb.append("  (native method)");
      }
      sb.append(" Java");
      return sb.toString(); 
    }
  }

  /**
   * The Native call frame representation. 
   */
  static class NativeCallFrame extends MicroCallFrame {

    public enum NativeFrameType {NORMAL, J2C_PROXY, C2J_PROXY};

    /** The native debugger specific frame identifier.*/
    private final int frameID;

    /** The function name.*/
    private final String functionName;

    /** The frame type. */
    private final NativeFrameType type;
    
    /** The constructor. */
    protected NativeCallFrame(int frameID, String functionName,
        String sourceFile, int lineNumber, NativeFrameType type) {
      super(sourceFile, lineNumber);
      this.frameID = frameID;
      this.functionName = functionName;
      this.type = type;
    }
    
    public String getName() {
      return functionName;
    }

    /** Getter method for the gdb identifier. */
    public int getFrameID() {
      return frameID;
    }

    /** Getter method for gdb function symbol name.*/
    public final String getFunctionName() {
      return functionName;
    }

    /** Getter method for the language. */
    public FrameLanguage getLanguage() {
      return FrameLanguage.C;
    }

    /** Getter method for top micro frame. */
    public MicroCallFrame getTopMicroFrame() {
      return this;
    }

    /** Geter method for tye symbol name. */
    public String getSymbolName() {
      return functionName;
    }

    public final NativeFrameType getType() {return type;}
    
    /**
     * @return The string representation.
     */
    public String toString() {
      StringBuffer sb = new StringBuffer();
      sb.append(functionName);
      if (getSourceFile() != null && getLineNumber() >= 1) {
        sb.append("  (" + getSourceFile() + ":" + getLineNumber() + ")");
      }
      sb.append(" C");
      return sb.toString(); 
    }
  }

  /**
   * The Jeannie call frame representation. A list of nonempty micro Java/C
   * frames makes a single macro Jeannie call frame. The first Java/C frame in
   * this list is close to the top of stack frame, and this frame is
   * representive of the current program counter. Therefore, a number of the
   * ICallFrame interface method calls are delegated to the same method of the
   * first element.
   */
  static class JeannieCallFrame implements ICallFrame {

    /** The user visible name of this Jeannie frame. */
    final String name;

    /** The list of Java/Native frames. */
    final MicroCallFrame[] frames;

    /**
     * @param name The name of this Jeannie frame.
     * @param frameList The list of Java/Native frames.
     */
    private JeannieCallFrame(String name, List<MicroCallFrame> frameList) {
      this.name = name;
      this.frames = frameList.toArray(new MicroCallFrame[0]); 
      assert frames != null && frames.length > 0;
    }

    /** Getter method for the line number. */
    public int getLineNumber() {
      return frames[0].getLineNumber();
    }

    /** Getter method for the source file. */
    public String getSourceFile() {
      return frames[0].getSourceFile();
    }

    /** Getter method for the language transition flag. */
    public boolean isTransition() {
      return false;
    }

    /** Getter method for the language. */
    public FrameLanguage getLanguage() {
      return FrameLanguage.JEANNIE;
    }

    public String getName() {
      return name;
    }

    /** Getter method for the top micro frame. */
    public MicroCallFrame getTopMicroFrame() {
      return frames[0];
    }

    /** Getter method for the micro frame. */
    public MicroCallFrame getMicroFrame(int i) {
      assert i >=0 && i < frames.length;
      return frames[i];
    }

    /** Gettter method for the number of micro frames. */
    public int getNumberofMicroFrames() {
      return frames.length;
    }

    /** Getter method for the top Java frame. */
    public JavaCallFrame getTopJavaFrame() {
      for(int i = 0;i <frames.length;i++) {
        MicroCallFrame f = frames[i];
        if (f instanceof JavaCallFrame) {
          return (JavaCallFrame)f;
        }
      }
      return null;
    }

    /** Getter method for the top native frame.*/
    public NativeCallFrame getTopNativeFrame() {
      for(int i = 0;i <frames.length;i++) {
        MicroCallFrame f = frames[i];
        if (f instanceof NativeCallFrame) {
          return (NativeCallFrame)f;
        }
      }
      return null;
    }

    /**
     * Obtain a string representation.
     * 
     * @return The string representation.
     */
    public String toString() {
      StringBuffer sb = new StringBuffer();
      sb.append(name);
      String sourceFile = getSourceFile();
      int lineNumber = getLineNumber();
      if (sourceFile != null && lineNumber >= 1) {
        sb.append("  (" + sourceFile + ":" + lineNumber + ")");
      }
      sb.append(" Jeannie");
      return sb.toString(); 
    }
  }

  /** 
   * A Local variable in the frame.
   */
  static class LocalVariable {

    /** The name of the local variable. */
    private final String name;

    /** The value of the local variable. */
    private final String value;

    /**
     * Constructor.
     * 
     * @param name The name.
     * @param value The value.
     */
    public LocalVariable(String name, String value) {
      this.name = name;
      this.value = value;
    }

    /** Getter method for the name. */
    public String getName() {return name;}

    /** Getter method for the value. */
    public String getValue() {return value;}
  }
}
