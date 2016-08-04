#ifndef _AGENT_H_
#define _AGENT_H_

/* Java Agent classes */
#define AGENT_CLASS_NAME "xtc/lang/blink/agent/Agent"
#define AGENT_VARIABLE_CLASS_NAME "xtc/lang/blink/agent/AgentVariable"
#define AGENT_JNI_ASSERTION_FAILURE_CLASS_NAME "xtc/lang/blink/agent/JNIAssertionFailure"

/* The internal break point type. */
typedef enum {
    J2C_DEBUGGER, JNI_WARNING,
    J2C_JNI_CALL, J2C_JNI_RETURN,
    C2J_JNI_CALL, C2J_JNI_RETURN,
} breakpoint_type;

/* Java or native program location. */
struct bda_location {
    const void *native_address; /* native code address */
    const char *cname; /* Java class name */
    const char *mname; /* Java method name */
    const char *mdesc; /* Java descriptor name */
    int line_number; /* line number */
    int bcindex; /* bytecode index */
};

/* The Blink internal break point. */
extern void bda_cbp(
    breakpoint_type bptype,
    struct bda_state_info *state,
    struct bda_location *target);

extern void bda_check_handle_assertion_fail(
    struct bda_state_info *state, 
    jthrowable pending_exception, 
    const char *fmt, ...);

/* If set to be 1, activate the j2c_call breakpoint.*/
extern int bda_j2c_call_breakpoint;

/* If set to be 1, activate the j2c_return breakpoint. */
extern int bda_j2c_return_breakpoint;

/* If set to be 1, activate the c2j_call breakpoint.*/
extern int bda_c2j_call_breakpoint;

/* If set to be 1, activate the c2j_return breakpoint.*/
extern int bda_c2j_return_breakpoint;

/* If set to be nonzeoro, the [j2c|c2j]_[call|return] event is
   triggered only when the number of language transitions on the call
   stack matches this transition count.*/
extern int bda_transition_count;

/* The beginning and ending of the JDWP agent memory region. */
extern void *bda_jdwp_region_begin;
extern void *bda_jdwp_region_end;

extern void bda_agent_init(JNIEnv *env); 
extern void bda_j2c_proxy_init();

/* Trigger c2j transition. */
extern int bda_c2j();

/* call to dummy. */
extern int bda_dummy_java();

extern int bda_dummy_native();

/* The getter and setter functions for convenience variables. */
extern int bda_cv_set_jboolean(jboolean exprValue);
extern int bda_cv_set_jint(jint exprValue);
extern int bda_cv_set_jdouble(jdouble exprValue);
extern int bda_cv_set_jobject(jobject exprValue);

extern jboolean bda_cv_get_jboolean(int vjid);
extern jint     bda_cv_get_jint(int vjid);
extern jdouble  bda_cv_get_jdouble(int vjid);
extern jobject  bda_cv_get_jobject(int vjid);

#endif /* _AGENT_H_ */
