package xtc.lang.blink.agent;

/**
 * The Blink Agent's constant values visible to the Blink through the Java
 * component debugger. The constant here should be consistent with the agent.h
 * file.
 * @author Byeongcheol Lee
 */
public interface AgentNativeDeclaration {

  /** Agent shared library name.*/
  public static final String BDA_SHARED_LIBRARY_NAME = "jinn";
  
  /** The internal break point type name for Java-to-native call. */
  public static final String BDA_BPTYPE_J2C_DEBUGGER = "J2C_DEBUGGER";

  /** The internal break point type name for c2j_call. */
  public static final String BDA_BPTYPE_C2J_JNI_CALL = "C2J_JNI_CALL";

  /** The internal break point type name for c2j_return. */
  public static final String BDA_BPTYPE_C2J_JNI_RETURN = "C2J_JNI_RETURN";

  /** The internal breakpoint type name for j2c_call. */
  public static final String BDA_BPTYPE_J2C_JNI_CALL = "J2C_JNI_CALL";

  /** The internal breakpoint type name for j2c_return. */
  public static final String BDA_BPTYPE_J2C_JNI_RETURN = "J2C_JNI_RETURN";

  /** The internal JNI warning breakpoint.*/
  public static final String BDA_BPTYPE_JNI_WARNING = "JNI_WARNING";

  /**
   * A Blink debug agent's flag variable name that triggers a break point for
   * a call during native-to-java transition.
   */
  public static final String BDA_C2J_CALL_BREAKPOINT_VARIABLE = "bda_c2j_call_breakpoint";

  /**
   * A Blink debug agent's flag variable name that triggers a break point for a
   * return during native-to-java transition.
   */
  public static final String BDA_C2J_RETURN_BREAKPOINT_VARIABLE = "bda_c2j_return_breakpoint";

  /**
   * A Blink debug agent's flag variable name that triggers a breakpoint for a
   * call before the java-to-native transition.
   */
  public static final String BDA_J2C_CALL_BREAKPOINT_VARIABLE = "bda_j2c_call_breakpoint";

  /**
   * A Blink debug agent's flag variable name that triggers a breakpoint for a
   * return after the java-to-native transition.
   */
  public static final String BDA_J2C_RETURN_BREAKPOINT_VARIABLE = "bda_j2c_return_breakpoint";

  /**
   * A Blink debug agent's variable name that constraint the condition for the language
   * transition breakpoints. 
   */
  public static final String BDA_TRANSITION_COUNT= "bda_transition_count";

  /** The beginning address of the JDWP agent library. */
  public static final String BDA_JDWP_REGION_BEGIN_VARIABLE = "bda_jdwp_region_begin";

  /** The ending address of the the JDWP agent library. */
  public static final String BDA_JDWP_REGION_END_VARIABLE = "bda_jdwp_region_end";

  /** The native entry to call the agent's Java dummy code. */
  public static final String BDA_DUMMY_JAVA = "bda_dummy_java";

  /** A blink agent's master breakpoint. */
  public static final String BDA_CBP = "bda_cbp";

  /** C expression to get the break point type at the bda_cbp.*/
  public static final String BDA_CBP_BPTYPE = "bptype";

  /** C expression to get the target native code address at the bda_cbp. */
  public static final String BDA_CBP_TARGET_NATIVE_ADDRESS = "target->native_address";

  /** C expression to get the target java class name at the bda_cbp. */
  public static final String BDA_CBP_TARGET_CNAME = "target->cname";

  /** C expression to get the target line number at the bda_cbp. */
  public static final String BDA_CBP_TARGET_LINE_NUMBER = "target->line_number";

  /** C expression to get the JNI environment variable at the bda_cbp. */
  public static final String BDA_CBP_STATE_JNI_ENV = "state->jni_env";

  /** C expression to get the JNI environment variable at the bda_cbp. */
  public static final String BDA_CBP_STATE_TRANSITIONS_IN_STACK = "state->transitions_in_stack";

  /** C expression to get the details message from the breakpoint. */
  public static final String BDA_CBP_STATE_MESSAGE = "(char *)state->msgbuf";

  /** Yield the control from C debugger to Java debugger.*/
  public static final String BDA_C2J = "bda_c2j";

  /** The native entry name to get language transition count. */
  public static final String BDA_GET_CURRENT_TRANSITION_COUNT = "bda_get_current_transition_count";
}
