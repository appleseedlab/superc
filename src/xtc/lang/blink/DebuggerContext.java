package xtc.lang.blink;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import xtc.lang.blink.CallStack.ICallFrame;
import xtc.lang.blink.CallStack.JavaCallFrame;
import xtc.lang.blink.CallStack.JeannieCallFrame;
import xtc.lang.blink.CallStack.NativeCallFrame;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.SymbolMapper.TargetSourceLanguage;
import xtc.lang.blink.SymbolMapper.VariableRemapEntry;
import xtc.lang.blink.CallStack.MicroCallFrame;
import xtc.lang.blink.CallStack.LocalVariable;

/**
 * The debugger calling context. 
 *
 * @author Byeongcheol Lee
 */
public class DebuggerContext {

  /** The mixed call stack. */
  private final CallStack callStack;

  /** The currently chosen call frame number. */
  private int currentFrameNumber;

  /**
   * @param callStack The call stack.
   * @param where The source code location.
   */
  DebuggerContext(CallStack callStack) {
    this.callStack = callStack;
    this.currentFrameNumber = 0;
  }

  /**
   * Obtain the name and value pairs for the Jeannie frame.
   * 
   * @param jframe The Jeannie frame.
   * @param dbg The Blink debugger.
   * @param remapper The Jeannie Symbol remapper.
   * @return The list.
   */
  private List<LocalVariable> getJeannieLocals(JeannieCallFrame jframe, 
      Blink dbg, SymbolMapper remapper)  {
    LinkedList<LocalVariable> localList = new LinkedList<LocalVariable>();
  
    // Obtain symbol remap information.
    String sourceFile = jframe.getSourceFile();
    int line = jframe.getLineNumber();
    if (sourceFile == null || line <= 0) {
      dbg.err("no source file and info avaiable.\n");
    }
    assert sourceFile != null && line > 0;
    List<VariableRemapEntry> list = remapper.lookup(sourceFile, line);
  
    // Obtain values from Java side.
    dbg.ensureJDBContext();
    for(VariableRemapEntry v: list) {
      if (v.targetLanguage == TargetSourceLanguage.JAVA) {
        String name = v.sourceVariableName;
        String val = dbg.jdb.print(getCurrentJavaFrame(), v.targetLanguageExpression());
        localList.add(new LocalVariable(name, val));
      }
    }
  
    //obtain values from native side.
    dbg.ensureGDBContext();
    for(VariableRemapEntry v: list) {
      if (v.targetLanguage == TargetSourceLanguage.C) {
        String name = v.sourceVariableName;
        String val = dbg.ndb.eval(getCurrentNativeFrame(), 
            v.targetLanguageExpression());
        localList.add(new LocalVariable(name, val));
      }
    }
  
    return localList;
  }

  /**
   * Present the current calling context to the user.
   * 
   * @param dbg The debugger.
   */
  public void showWhere(Blink dbg) {
    StringBuffer sb = new StringBuffer();
    int nsize = callStack.size(); 
    for(int i = currentFrameNumber;i < nsize;i++) {
      CallStack.ICallFrame f = callStack.getCallFrame(i);
      if (f.getSourceFile() != null) {
        dbg.out(" [%d] %s at %s:%d\n", i, f.getName(), f.getSourceFile(), f.getLineNumber());
      } else {
        dbg.out(" [%d] %s\n", i, f.getName());
      }
    }
  }

  /**
   * Unwind the current call stack n steps. If this n steps unwinding exceed the
   * bottom of the stack, this unwinding stops at the bottom of the stack..
   * 
   * @param dbg The debugger.
   * @param nSteps The number of steps to unwind.
   */
  public void unWindStack(Blink dbg, int nSteps) {
    int maxPosition = callStack.size() - 1;
    int expectedPosition = currentFrameNumber + nSteps;
    if (expectedPosition > maxPosition ) {
      int modifiedStep = maxPosition - currentFrameNumber;
      dbg.err("can not unwind the stack more than " + modifiedStep +"\n");
      currentFrameNumber = maxPosition;
    } else {
      currentFrameNumber = expectedPosition;
    }
    assert currentFrameNumber >= 0 && currentFrameNumber < callStack.size();
  }

  /**
   * Wind the current call stack n steps. If this n steps exceeds the top of the
   * stack, this winding stops at the top of the stack.
   * 
   * @param dbg The debugger.
   * @param nSteps The number of steps to wind.
   */
  public void windStack(Blink dbg, int nSteps) {
    int minPosition = 0;
    int expectedPosition = currentFrameNumber - nSteps;
    if (expectedPosition < minPosition ) {
      int modifiedStep = currentFrameNumber;
      dbg.err("can not wind stack more than " + modifiedStep + "\n");
      currentFrameNumber = minPosition;
    } else {
      currentFrameNumber = expectedPosition;
    }
    assert currentFrameNumber >= 0 && currentFrameNumber < callStack.size();
  }
  
  /**
   * Show local variables in the currently chosen call stack.
   *  
   * @param dbg The debugger.
   * @param remapper The symbol remapper.
   */
  public void showLocals(Blink dbg, SymbolMapper remapper) 
     {
    
    //obtain a list of local variable info.
    List<LocalVariable> l = null;
    ICallFrame f = callStack.getCallFrame(currentFrameNumber);
    if (f instanceof JavaCallFrame) {
      JavaCallFrame jframe = (JavaCallFrame)f;
      dbg.ensureJDBContext();
      l = dbg.jdb.getLocals(jframe);
    } else if (f instanceof NativeCallFrame) {
      NativeCallFrame nframe = (NativeCallFrame)f;
      dbg.ensureGDBContext();
      l = dbg.ndb.getLocals(nframe);
    } else if ( f instanceof JeannieCallFrame) {
      l = getJeannieLocals((JeannieCallFrame)f, dbg, remapper);
    } else {
      assert false : "can not deal with this call frame: " + f + "\n";
    }

    // show the result.
    if (l.size() == 0) {
      dbg.out("No Locals\n");
    } else {
      for(final LocalVariable lv : l) {
        dbg.out(lv.getName() + " = "  + lv.getValue() + "\n");
      }
    }
  }
  
  /**
   * The source code for the currently chosen frame.
   *
   * @param dbg The debugger.
   */
  public void showSourceCode(Blink dbg) {
    MicroCallFrame frame = callStack.getCallFrame(currentFrameNumber).getTopMicroFrame();
    if (frame instanceof JavaCallFrame) {
      JavaCallFrame jframe = (JavaCallFrame)frame;
      dbg.ensureJDBContext();
      String msg = dbg.jdb.list(jframe);
      dbg.out("%s", msg);
    } else {
      assert frame instanceof NativeCallFrame;
      dbg.ensureGDBContext();
      NativeCallFrame nframe = (NativeCallFrame)frame;
      String sourceFile = nframe.getSourceFile();
      int line = nframe.getLineNumber(); 
      if (sourceFile != null && line > 0) {
        String lines = dbg.ndb.getSourceLines(sourceFile, line, 10);
        dbg.out("%s", lines);
      } else {
        dbg.err("line number is not availble.\n");
      }
    }
  }

  /** Find the current Java frame. */
  public JavaCallFrame getCurrentJavaFrame()  {
    return callStack.getJavaCallFrame(currentFrameNumber);
  }
  
  /** Find the current native frame. */
  public NativeCallFrame getCurrentNativeFrame() {
    return callStack.getNativeCallFrame(currentFrameNumber);
  }

  /** Getter method for the user readable location. */
  public SourceFileAndLine getCurrentLocation() {
    ICallFrame f = callStack.getCallFrame(currentFrameNumber);
    if (f != null) {
      return new SourceFileAndLine(f.getSourceFile(), f.getLineNumber());
    } else {
      return null;
    }
  }
}
