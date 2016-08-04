package xtc.lang.blink;

import java.util.List;

import xtc.lang.blink.CallStack.NativeCallFrame;
import xtc.lang.blink.CallStack.LocalVariable;
import xtc.lang.blink.Event.BlinkEventSource;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;

/**
 * The exported feature from the native debugger controlled under the Blink.
 */
public interface NativeDebugger extends BlinkEventSource {

  /** Transition type between Java and native code. */
  static enum LanguageTransitionEventType {
    J2C_CALL, 
    J2C_RETURN, 
    C2J_CALL, 
    C2J_RETURN;
  }

  /** attaching and detaching. */
  public void attach(int pid) ;
  public void detach() ;
  public void quit() ;

  /** user level breakpoint and continuing. */
  public int createBreakpoint(String sourceFile, int line) ;
  public int createBreakpoint(String symbol) ;
  public void enableBreakpoint(int bpid) ;
  public void disableBreakpoint(int bpid) ;
  public void deleteBreakpoint(int bpid) ;
  
  /** Enable and disable the internal transition break point. */
  public int getLanguageTransitionCount() ;
  public void setTransitionBreakPoint(LanguageTransitionEventType bptype, int transitionCount)
    ;
  public void clearTransitionBreakPoint(LanguageTransitionEventType bptype)
    ;

  /** For transitions */
  public void callNative2Java() ;

  /** Continue the debuggee's execution. */
  public void cont() ;

  public void callJavaDummy() ;
  
  /** Calling context. */
  public List<NativeCallFrame> getFrames() ;
  /** Get current location. */
  public SourceFileAndLine getCurrentLocation() ;
  public String getSourceLines(String filename, int line, int count) ;
  public List <LocalVariable> getLocals(NativeCallFrame f) ;

  /** Stepping */
  public void step() ;
  public void next() ;
  
  /** Inspecting the memory. */
  public String eval(NativeCallFrame f, String expr) ;
  public void setVariable(NativeCallFrame f, String name, String expr) ;
  public String getNewCTmpVarIdentifier();  
  public void resetConvenienceVariables(); 

  /** Obtain the type of the C expression including convenience variable. */
  public String whatis(NativeCallFrame f, String expr) ;

  /** Run the native debugger specific raw command line, and return the response. */
  public String runCommand(String command) ;

  /** Perform debugger's internal event handling. */
  public void dispatch(Event e);

  public boolean isDead();
}
