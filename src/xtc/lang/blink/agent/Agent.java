package xtc.lang.blink.agent;

/**
 * A Blink debug agent. This agent provides two key functionalities. First, the
 * agent allows the Java debugger to yield its control to the native debugger
 * and vice versa. Second, this agent informs the Java debugger of the JVM
 * internal information such as the string representation of a Java method and
 * the JVM process identifier.
 *
 * @author Byeongcheol Lee
 */
class Agent {

  /** The main method for testing purpose. */
  public static void main(String[] args) {
    init();
  }

  /** Initialize the Blink agent. The Java debugger will call this
   * method.  */
  public static void init() {
    AgentVariable.init();
  }

  /** The internal Java break point. */
  public static void jbp() {}

  /** Get a debuggee's process identifier. */
  public static native int getProcessID();

  /** Yield control from the Java debugger to the native debugger. */
  public static native void j2c();

  /** This is dummy utility code to simply run dummy java code. */
  public static int dummyJava() {
    int i = 0;
    i++;
    return i;
  }

  public static native int dummyNative();
}
