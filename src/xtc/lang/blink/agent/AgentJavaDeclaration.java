package xtc.lang.blink.agent;

/**
 * The Blink Agent's constant values visible to the Blink through the Java
 * component debugger. The constant here should be consistent with the agent.h
 * file.
 *
 * @author Byeongcheol Lee
 */
public interface AgentJavaDeclaration {

  /** Agent source file name.*/
  public static final String BDA_AGENT_SOURCE_FILE = "Agent.java";

  /** The agent name.*/
  public static final String BDA_AGENT_NAME = "xtc.lang.blink.agent.Agent";

  /** The agent convenience variable manager name. */
  public static final String BDA_AGENT_VARIABLE_NAME = "xtc.lang.blink.agent.AgentVariable";

  /** The initialization method.*/
  public static final String BDA_INIT = "init";

  /** JBP method. */
  public static final String BDA_JBP = "jbp";

  /** Java to C transition method. */
  public static final String BDA_J2C = "j2c";

  /** Getting the process id of the target JVM.*/
  public static final String BDA_GETPROCESSID = BDA_AGENT_NAME + "." + "getProcessID" + "()";

  /** The native entry name to call dummy Java code. */
  public static final String BDA_DUMMY_JAVA = "dummyJava";

  /** The native entry name to call dummy native code. */
  public static final String BDA_DUMMY_NATIVE = "dummyNative";

  /** Cleaning the Java convenience variables.*/
  public static final String BDA_CLEANTEMPVARS = "cleanTempVars";

  /** Creating a Java convenience variable. */
  public static final String BDA_CV_SET = "set";

  /** Getting JNI type name for a Java convenience variable. */
  public static final String BDA_CV_GET_TYPE_NAME = "getTypeName";

  /** Getting Java expression to read a Java convenience variable.*/
  public static final String BDA_CV_GET_EXPR = "getJavaExpression";

}
