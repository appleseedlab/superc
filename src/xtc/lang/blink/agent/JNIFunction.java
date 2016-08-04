/**
 * 
 */
package xtc.lang.blink.agent;

import java.util.ArrayList;
import java.util.HashMap;

import xtc.lang.blink.agent.JNIType.ReferenceType;

/**
 * A JNI function description.
 * 
 * @author Byeongcheol Lee
 */
final class JNIFunction implements JNIConstants {

  public static enum ExtraArgumentType {
    NONE, 
    DOT_DOT_DOT, 
    VA_LIST, 
    JVALUE_ARRAY,
  };

  public static enum JNIFunctionClass {
    JNI_CALL_NOT_CLASSIFIED,
    JNI_CALL_INSTANCE,
    JNI_CALL_NONVIRTUAL,
    JNI_CALL_STATIC,
  }

  final int index;
	final String name;
	final JNIAnnotatedType[] argumenTypes; // does not count the first common argument with JNIEnv
	final JNIAnnotatedType returnType;
	final ExtraArgumentType extraArgType;
	final JNIFunctionClass fclass;

	private JNIFunction(int index, String name, JNIAnnotatedType returnType, JNIAnnotatedType[] argumenTypes,
	    JNIFunctionClass fclass, ExtraArgumentType extraArgType) {
	  this.index = index;
		this.argumenTypes = argumenTypes;
		this.name = name;
		this.returnType = returnType;
		this.fclass = fclass;
		this.extraArgType = extraArgType;
	}
	
	public boolean hasReturnType() {
	  return returnType.jniType != VOID;
	}
	
	public boolean hasReferenceReturn() {
	  return returnType.jniType instanceof ReferenceType; 
	}
  
  public boolean returnLocalReference() {
    return this.hasReferenceReturn() && 
      (this != JNIFunction.NewGlobalRef) && (this != JNIFunction.NewWeakGlobalRef);
  }
	
  public boolean hasNonNullParameter() {
    for(JNIAnnotatedType t : argumenTypes) {
      if (t.nonNull) {
        return true;
      }
    }
    return false;
  }

  public boolean hasJNIReferenceParameter() {
	  for(JNIAnnotatedType t: argumenTypes) {
		  if (t.jniType instanceof JNIType.ReferenceType) {
			  return true;
		  }
	  }
	  return false;
  }
  static class JNIAnnotatedType {
		final JNIType jniType;
		final boolean nonNull;
    public JNIAnnotatedType(JNIType name, boolean nullable) {
      this.jniType = name;
      this.nonNull = nullable;
    }
    public JNIAnnotatedType(JNIType name) {
      this(name, false);
    }
    public String getTypeName() {
      return jniType.name;
    }
    public boolean isVoid() {
      return jniType.equals("void");
    }
	}

	final static ArrayList<JNIFunction> jniFunctionList = new ArrayList<JNIFunction>(); 
	final static HashMap<String,JNIFunction> jniFunctionMap = new HashMap<String,JNIFunction>();

	public static void main(String[] args) {
		int i;

		i = 1;
		System.out.println("Here are exception-sensitive functions.");		
		for(JNIFunction f: jniFunctionList) {
			if (!f.isExceptionOblivious()) {
				System.out.printf("%3d %s\n", i++,f.name);
			}
		}
		System.out.println("");

		i = 1;
		System.out.println("Here are critical-section sensitive functions.");		
		for(JNIFunction f: jniFunctionList) {
			if (!f.isExceptionOblivious()) {
				System.out.printf("%3d %s\n", i++,f.name);
			}
		}
		System.out.println("");

		i = 1;
		System.out.println("Here are producers of JNI object references.");		
		for(JNIFunction f: jniFunctionList) {
			if (f.hasReferenceReturn()) {
				System.out.printf("%3d %s\n", i++,f.name);
			}
		}
		System.out.println("");

		i = 1;
		System.out.println("Here are consumers of JNI object references.");
		for(JNIFunction f: jniFunctionList) {
			if (f.hasJNIReferenceParameter()) {
				System.out.printf("%3d %s\n", i++,f.name);
			}
		}
	}
	
	static JNIAnnotatedType t(JNIType type) {
	  return new JNIAnnotatedType(type);
	}

	static JNIAnnotatedType nt(JNIType type) {
    return new JNIAnnotatedType(type, true);
  }

  /** 
   * Check a JNI function is free to be called with and without a
   * pending JVM exception. According to Ch 11.8.2 of the JNI
   * programming guide [Liang99], 28 JNI functions are free from the
   * pending exception hazard.
   */
  public boolean isExceptionOblivious() {    
    if ((this == ExceptionOccurred) || (this == ExceptionDescribe)
        || (this == ExceptionClear) || (this == ExceptionCheck)
        || (this == ReleaseStringChars) || (this == ReleaseStringUTFChars)
        || (this == ReleaseStringCritical) || (this == ReleaseBooleanArrayElements)
        || (this == ReleaseByteArrayElements) || (this == ReleaseCharArrayElements)
        || (this == ReleaseShortArrayElements) || (this == ReleaseIntArrayElements)
        || (this == ReleaseLongArrayElements) || (this == ReleaseFloatArrayElements)
        || (this == ReleaseDoubleArrayElements)
        || (this == ReleasePrimitiveArrayCritical) || (this == DeleteLocalRef)
        || (this == DeleteGlobalRef) || (this == DeleteWeakGlobalRef)
        || (this == MonitorExit)) {
      return true;
    } else {
      return false;
    }
  }


	static final String JNI_JAVA_CALL_TYPE =
	  "(|Nonvirtual|Static)";
	static final String JNI_JAVA_CALL_RETURN =
	  "(Object|Boolean|Byte|Char|Short|Int|Long|Float|Double|Void)";
  static final String JNI_JAVA_CALL_SUFFIX =
    "(|V|A)";
  static final String JNI_INSTANCE_METHOD = "Call" + JNI_JAVA_CALL_RETURN + "Method" + JNI_JAVA_CALL_SUFFIX;
  static final String JNI_NONVIRTUAL_METHOD = "Call" + "Nonvirtual" +  JNI_JAVA_CALL_RETURN + "Method" +JNI_JAVA_CALL_SUFFIX;
  static final String JNI_STATIC_METHOD = "Call" + "Static" + JNI_JAVA_CALL_RETURN + "Method" + JNI_JAVA_CALL_SUFFIX;
  
  static final String JNI_EXTRA_ARG_DOT_DOT_DOT = "NewObject" + "|" +  "Call" + JNI_JAVA_CALL_TYPE + JNI_JAVA_CALL_RETURN + "Method";
  static final String JNI_EXTRA_ARG_VA_LIST = "NewObjectV" + "|" +  "Call" + JNI_JAVA_CALL_TYPE + JNI_JAVA_CALL_RETURN + "MethodV";
  static final String JNI_EXTRA_ARG_JVALUE_ARRAY = "NewObjectA" + "|" +  "Call" + JNI_JAVA_CALL_TYPE + JNI_JAVA_CALL_RETURN + "MethodA";
  
  private static JNIFunctionClass getCallType(String fname) {

    if (fname.matches(JNI_INSTANCE_METHOD)) {
      return JNIFunctionClass.JNI_CALL_INSTANCE;
    } else if (fname.matches(JNI_NONVIRTUAL_METHOD)) {
      return JNIFunctionClass.JNI_CALL_NONVIRTUAL;
    } else if (fname.matches(JNI_STATIC_METHOD)) {
      return JNIFunctionClass.JNI_CALL_STATIC;
    } else {
      return JNIFunctionClass.JNI_CALL_NOT_CLASSIFIED;
    }
  }

  private static ExtraArgumentType getExtraArgumentType(String fname) {
     if (fname.matches(JNI_EXTRA_ARG_DOT_DOT_DOT)) {
       return ExtraArgumentType.DOT_DOT_DOT;
     } else if (fname.matches(JNI_EXTRA_ARG_VA_LIST)) {
       return ExtraArgumentType.VA_LIST;
     } else if (fname.matches(JNI_EXTRA_ARG_JVALUE_ARRAY)) {
       return ExtraArgumentType.JVALUE_ARRAY;
     } else {
       return ExtraArgumentType.NONE;
     }
  }

	static JNIFunction create(int index, boolean varArgument, String fname, JNIAnnotatedType returnType, JNIAnnotatedType ... formalTypes) {
	  JNIAnnotatedType[] formalTypesWithJNIEnv = new JNIAnnotatedType[formalTypes.length + 1];
	  formalTypesWithJNIEnv[0] = nt(JNI_ENV);
	  System.arraycopy(formalTypes, 0, formalTypesWithJNIEnv, 1, formalTypes.length);
	  ExtraArgumentType extraArgtype = getExtraArgumentType(fname);
	  JNIFunctionClass jniClass = getCallType(fname);
	  JNIFunction j = new JNIFunction(index, fname, returnType, formalTypesWithJNIEnv, jniClass, extraArgtype);
	  jniFunctionList.add(j);
	  jniFunctionMap.put(fname, j);
	  return j;
	}

  //  jint (JNICALL * GetVersion)(JNIEnv *env);
  public static final JNIFunction GetVersion = JNIFunction.create(4, false, "GetVersion",JNIFunction.t(JINT));

  //  jclass (JNICALL * DefineClass)(JNIEnv *env, const char *name, jobject loader, const jbyte *buf, jsize bufLen);
  public static final JNIFunction DefineClass = JNIFunction.create(5, false, "DefineClass",JNIFunction.t(JCLASS), JNIFunction.nt(UTF8_CLASS_DESC), JNIFunction.t(JOBJECT), JNIFunction.nt(JBYTE_CONST_POINTER),JNIFunction.t(JSIZE));

  //  jclass (JNICALL * FindClass)(JNIEnv *env, const char *name);
  public static final JNIFunction FindClass = JNIFunction.create(6, false, "FindClass",JNIFunction.t(JCLASS), JNIFunction.nt(UTF8_CLASS_DESC));

  //  jmethodID (JNICALL * FromReflectedMethod)(JNIEnv *env, jobject method);
  public static final JNIFunction FromReflectedMethod = JNIFunction.create(7, false, "FromReflectedMethod",JNIFunction.t(JMETHODID), JNIFunction.nt(JOBJECT));

  //  jfieldID (JNICALL * FromReflectedField)(JNIEnv *env, jobject field);
  public static final JNIFunction FromReflectedField = JNIFunction.create(8, false, "FromReflectedField",JNIFunction.t(JFIELDID), JNIFunction.nt(JOBJECT));

  //  jobject (JNICALL * ToReflectedMethod)(JNIEnv *env, jclass cls, jmethodID methodID, jboolean isStatic);
  public static final JNIFunction ToReflectedMethod = JNIFunction.create(9, false, "ToReflectedMethod",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JBOOLEAN));

  //  jclass (JNICALL * GetSuperclass)(JNIEnv *env, jclass clazz);
  public static final JNIFunction GetSuperclass = JNIFunction.create(10, false, "GetSuperclass",JNIFunction.t(JCLASS), JNIFunction.nt(JCLASS));

  //  jboolean (JNICALL * IsAssignableFrom)(JNIEnv *env, jclass clazz1, jclass clazz2);
  public static final JNIFunction IsAssignableFrom = JNIFunction.create(11, false, "IsAssignableFrom",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JCLASS), JNIFunction.nt(JCLASS));

  //  jobject (JNICALL * ToReflectedField)(JNIEnv *env, jclass cls, jfieldID fieldID, jboolean isStatic);
  public static final JNIFunction ToReflectedField = JNIFunction.create(12, false, "ToReflectedField",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JBOOLEAN));

  //  jint (JNICALL * Throw)(JNIEnv *env, jthrowable obj);
  public static final JNIFunction Throw = JNIFunction.create(13, false, "Throw",JNIFunction.t(JINT), JNIFunction.nt(JTHROWABLE));

  //  jint (JNICALL * ThrowNew)(JNIEnv *env, jclass clazz, const char *message);
  public static final JNIFunction ThrowNew = JNIFunction.create(14, false, "ThrowNew",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(UTF8_MESSAGE));

  //  jthrowable (JNICALL * ExceptionOccurred)(JNIEnv *env);
  public static final JNIFunction ExceptionOccurred = JNIFunction.create(15, false, "ExceptionOccurred",JNIFunction.t(JTHROWABLE));

  //  void (JNICALL * ExceptionDescribe)(JNIEnv *env);
  public static final JNIFunction ExceptionDescribe = JNIFunction.create(16, false, "ExceptionDescribe",JNIFunction.t(VOID));

  //  void (JNICALL * ExceptionClear)(JNIEnv *env);
  public static final JNIFunction ExceptionClear = JNIFunction.create(17, false, "ExceptionClear",JNIFunction.t(VOID));

  //  void (JNICALL * FatalError)(JNIEnv *env, const char *msg);
  public static final JNIFunction FatalError = JNIFunction.create(18, false, "FatalError",JNIFunction.t(VOID), JNIFunction.nt(UTF8_MESSAGE));

  //  jint (JNICALL * PushLocalFrame)(JNIEnv *env, jint capacity);
  public static final JNIFunction PushLocalFrame = JNIFunction.create(19, false, "PushLocalFrame",JNIFunction.t(JINT),JNIFunction.t(JINT));

  //  jobject (JNICALL * PopLocalFrame)(JNIEnv *env, jobject result);
  public static final JNIFunction PopLocalFrame = JNIFunction.create(20, false, "PopLocalFrame",JNIFunction.t(JOBJECT),JNIFunction.t(JOBJECT));

  //  jobject (JNICALL * NewGlobalRef)(JNIEnv *env, jobject obj);
  public static final JNIFunction NewGlobalRef = JNIFunction.create(21, false, "NewGlobalRef",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT));

  //  void (JNICALL * DeleteGlobalRef)(JNIEnv *env, jobject gref);
  public static final JNIFunction DeleteGlobalRef = JNIFunction.create(22, false, "DeleteGlobalRef",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT));

  //  void (JNICALL * DeleteLocalRef)(JNIEnv *env, jobject localRef);
  public static final JNIFunction DeleteLocalRef = JNIFunction.create(23, false, "DeleteLocalRef",JNIFunction.t(VOID),JNIFunction.t(JOBJECT));

  //  jboolean (JNICALL * IsSameObject)(JNIEnv *env, jobject ref1, jobject ref2);
  public static final JNIFunction IsSameObject = JNIFunction.create(24, false, "IsSameObject",JNIFunction.t(JBOOLEAN),JNIFunction.t(JOBJECT),JNIFunction.t(JOBJECT));

  //  jobject (JNICALL * NewLocalRef)(JNIEnv *env, jobject ref);
  public static final JNIFunction NewLocalRef = JNIFunction.create(25, false, "NewLocalRef",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT));

  //  jint (JNICALL * EnsureLocalCapacity)(JNIEnv *env, jint capacity);
  public static final JNIFunction EnsureLocalCapacity = JNIFunction.create(26, false, "EnsureLocalCapacity",JNIFunction.t(JINT),JNIFunction.t(JINT));

  //  jobject (JNICALL * AllocObject)(JNIEnv *env, jclass clazz);
  public static final JNIFunction AllocObject = JNIFunction.create(27, false, "AllocObject",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS));

  //  jobject (JNICALL * NewObject)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction NewObject = JNIFunction.create(28, true, "NewObject",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jobject (JNICALL * NewObjectV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction NewObjectV = JNIFunction.create(29, false, "NewObjectV",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jobject (JNICALL * NewObjectA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction NewObjectA = JNIFunction.create(30, false, "NewObjectA",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jclass (JNICALL * GetObjectClass)(JNIEnv *env, jobject obj);
  public static final JNIFunction GetObjectClass = JNIFunction.create(31, false, "GetObjectClass",JNIFunction.t(JCLASS), JNIFunction.nt(JOBJECT));

  //  jboolean (JNICALL * IsInstanceOf)(JNIEnv *env, jobject obj, jclass clazz);
  public static final JNIFunction IsInstanceOf = JNIFunction.create(32, false, "IsInstanceOf",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS));

  //  jmethodID (JNICALL * GetMethodID)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
  public static final JNIFunction GetMethodID = JNIFunction.create(33, false, "GetMethodID",JNIFunction.t(JMETHODID), JNIFunction.nt(JCLASS), JNIFunction.nt(UTF8_METHOD_NAME), JNIFunction.nt(UTF8_METHOD_DESC));

  //  jobject (JNICALL * CallObjectMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallObjectMethod = JNIFunction.create(34, true, "CallObjectMethod",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jobject (JNICALL * CallObjectMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallObjectMethodV = JNIFunction.create(35, false, "CallObjectMethodV",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jobject (JNICALL * CallObjectMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallObjectMethodA = JNIFunction.create(36, false, "CallObjectMethodA",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jboolean (JNICALL * CallBooleanMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallBooleanMethod = JNIFunction.create(37, true, "CallBooleanMethod",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jboolean (JNICALL * CallBooleanMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallBooleanMethodV = JNIFunction.create(38, false, "CallBooleanMethodV",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jboolean (JNICALL * CallBooleanMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallBooleanMethodA = JNIFunction.create(39, false, "CallBooleanMethodA",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jbyte (JNICALL * CallByteMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallByteMethod = JNIFunction.create(40, true, "CallByteMethod",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jbyte (JNICALL * CallByteMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallByteMethodV = JNIFunction.create(41, false, "CallByteMethodV",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jbyte (JNICALL * CallByteMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallByteMethodA = JNIFunction.create(42, false, "CallByteMethodA",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jchar (JNICALL * CallCharMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallCharMethod = JNIFunction.create(43, true, "CallCharMethod",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jchar (JNICALL * CallCharMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallCharMethodV = JNIFunction.create(44, false, "CallCharMethodV",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jchar (JNICALL * CallCharMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallCharMethodA = JNIFunction.create(45, false, "CallCharMethodA",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jshort (JNICALL * CallShortMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallShortMethod = JNIFunction.create(46, true, "CallShortMethod",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jshort (JNICALL * CallShortMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallShortMethodV = JNIFunction.create(47, false, "CallShortMethodV",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jshort (JNICALL * CallShortMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallShortMethodA = JNIFunction.create(48, false, "CallShortMethodA",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jint (JNICALL * CallIntMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallIntMethod = JNIFunction.create(49, true, "CallIntMethod",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jint (JNICALL * CallIntMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallIntMethodV = JNIFunction.create(50, false, "CallIntMethodV",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jint (JNICALL * CallIntMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallIntMethodA = JNIFunction.create(51, false, "CallIntMethodA",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jlong (JNICALL * CallLongMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallLongMethod = JNIFunction.create(52, true, "CallLongMethod",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jlong (JNICALL * CallLongMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallLongMethodV = JNIFunction.create(53, false, "CallLongMethodV",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jlong (JNICALL * CallLongMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallLongMethodA = JNIFunction.create(54, false, "CallLongMethodA",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jfloat (JNICALL * CallFloatMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallFloatMethod = JNIFunction.create(55, true, "CallFloatMethod",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jfloat (JNICALL * CallFloatMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallFloatMethodV = JNIFunction.create(56, false, "CallFloatMethodV",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jfloat (JNICALL * CallFloatMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallFloatMethodA = JNIFunction.create(57, false, "CallFloatMethodA",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jdouble (JNICALL * CallDoubleMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallDoubleMethod = JNIFunction.create(58, true, "CallDoubleMethod",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  jdouble (JNICALL * CallDoubleMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallDoubleMethodV = JNIFunction.create(59, false, "CallDoubleMethodV",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jdouble (JNICALL * CallDoubleMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallDoubleMethodA = JNIFunction.create(60, false, "CallDoubleMethodA",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  void (JNICALL * CallVoidMethod)(JNIEnv *env, jobject obj, jmethodID methodID, ...);
  public static final JNIFunction CallVoidMethod = JNIFunction.create(61, true, "CallVoidMethod",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID));

  //  void (JNICALL * CallVoidMethodV)(JNIEnv *env, jobject obj, jmethodID methodID, va_list args);
  public static final JNIFunction CallVoidMethodV = JNIFunction.create(62, false, "CallVoidMethodV",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  void (JNICALL * CallVoidMethodA)(JNIEnv *env, jobject obj, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallVoidMethodA = JNIFunction.create(63, false, "CallVoidMethodA",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jobject (JNICALL * CallNonvirtualObjectMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualObjectMethod = JNIFunction.create(64, true, "CallNonvirtualObjectMethod",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jobject (JNICALL * CallNonvirtualObjectMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualObjectMethodV = JNIFunction.create(65, false, "CallNonvirtualObjectMethodV",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jobject (JNICALL * CallNonvirtualObjectMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallNonvirtualObjectMethodA = JNIFunction.create(66, false, "CallNonvirtualObjectMethodA",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jboolean (JNICALL * CallNonvirtualBooleanMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualBooleanMethod = JNIFunction.create(67, true, "CallNonvirtualBooleanMethod",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jboolean (JNICALL * CallNonvirtualBooleanMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualBooleanMethodV = JNIFunction.create(68, false, "CallNonvirtualBooleanMethodV",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jboolean (JNICALL * CallNonvirtualBooleanMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallNonvirtualBooleanMethodA = JNIFunction.create(69, false, "CallNonvirtualBooleanMethodA",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jbyte (JNICALL * CallNonvirtualByteMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualByteMethod = JNIFunction.create(70, true, "CallNonvirtualByteMethod",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jbyte (JNICALL * CallNonvirtualByteMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualByteMethodV = JNIFunction.create(71, false, "CallNonvirtualByteMethodV",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jbyte (JNICALL * CallNonvirtualByteMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualByteMethodA = JNIFunction.create(72, false, "CallNonvirtualByteMethodA",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jchar (JNICALL * CallNonvirtualCharMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualCharMethod = JNIFunction.create(73, true, "CallNonvirtualCharMethod",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jchar (JNICALL * CallNonvirtualCharMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualCharMethodV = JNIFunction.create(74, false, "CallNonvirtualCharMethodV",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jchar (JNICALL * CallNonvirtualCharMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualCharMethodA = JNIFunction.create(75, false, "CallNonvirtualCharMethodA",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jshort (JNICALL * CallNonvirtualShortMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualShortMethod = JNIFunction.create(76, true, "CallNonvirtualShortMethod",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jshort (JNICALL * CallNonvirtualShortMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualShortMethodV = JNIFunction.create(77, false, "CallNonvirtualShortMethodV",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jshort (JNICALL * CallNonvirtualShortMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualShortMethodA = JNIFunction.create(78, false, "CallNonvirtualShortMethodA",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jint (JNICALL * CallNonvirtualIntMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualIntMethod = JNIFunction.create(79, true, "CallNonvirtualIntMethod",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jint (JNICALL * CallNonvirtualIntMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualIntMethodV = JNIFunction.create(80, false, "CallNonvirtualIntMethodV",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jint (JNICALL * CallNonvirtualIntMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualIntMethodA = JNIFunction.create(81, false, "CallNonvirtualIntMethodA",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jlong (JNICALL * CallNonvirtualLongMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualLongMethod = JNIFunction.create(82, true, "CallNonvirtualLongMethod",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jlong (JNICALL * CallNonvirtualLongMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualLongMethodV = JNIFunction.create(83, false, "CallNonvirtualLongMethodV",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jlong (JNICALL * CallNonvirtualLongMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualLongMethodA = JNIFunction.create(84, false, "CallNonvirtualLongMethodA",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jfloat (JNICALL * CallNonvirtualFloatMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualFloatMethod = JNIFunction.create(85, true, "CallNonvirtualFloatMethod",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jfloat (JNICALL * CallNonvirtualFloatMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualFloatMethodV = JNIFunction.create(86, false, "CallNonvirtualFloatMethodV",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jfloat (JNICALL * CallNonvirtualFloatMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualFloatMethodA = JNIFunction.create(87, false, "CallNonvirtualFloatMethodA",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jdouble (JNICALL * CallNonvirtualDoubleMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualDoubleMethod = JNIFunction.create(88, true, "CallNonvirtualDoubleMethod",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jdouble (JNICALL * CallNonvirtualDoubleMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualDoubleMethodV = JNIFunction.create(89, false, "CallNonvirtualDoubleMethodV",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jdouble (JNICALL * CallNonvirtualDoubleMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallNonvirtualDoubleMethodA = JNIFunction.create(90, false, "CallNonvirtualDoubleMethodA",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  void (JNICALL * CallNonvirtualVoidMethod)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallNonvirtualVoidMethod = JNIFunction.create(91, true, "CallNonvirtualVoidMethod",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  void (JNICALL * CallNonvirtualVoidMethodV)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallNonvirtualVoidMethodV = JNIFunction.create(92, false, "CallNonvirtualVoidMethodV",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  void (JNICALL * CallNonvirtualVoidMethodA)(JNIEnv *env, jobject obj, jclass clazz, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallNonvirtualVoidMethodA = JNIFunction.create(93, false, "CallNonvirtualVoidMethodA",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jfieldID (JNICALL * GetFieldID)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
  public static final JNIFunction GetFieldID = JNIFunction.create(94, false, "GetFieldID",JNIFunction.t(JFIELDID), JNIFunction.nt(JCLASS), JNIFunction.nt(UTF8_FIELD_NAME), JNIFunction.nt(UTF8_FIELD_DESC));

  //  jobject (JNICALL * GetObjectField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetObjectField = JNIFunction.create(95, false, "GetObjectField",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jboolean (JNICALL * GetBooleanField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetBooleanField = JNIFunction.create(96, false, "GetBooleanField",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jbyte (JNICALL * GetByteField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetByteField = JNIFunction.create(97, false, "GetByteField",JNIFunction.t(JBYTE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jchar (JNICALL * GetCharField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetCharField = JNIFunction.create(98, false, "GetCharField",JNIFunction.t(JCHAR), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jshort (JNICALL * GetShortField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetShortField = JNIFunction.create(99, false, "GetShortField",JNIFunction.t(JSHORT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jint (JNICALL * GetIntField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetIntField = JNIFunction.create(100, false, "GetIntField",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jlong (JNICALL * GetLongField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetLongField = JNIFunction.create(101, false, "GetLongField",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jfloat (JNICALL * GetFloatField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetFloatField = JNIFunction.create(102, false, "GetFloatField",JNIFunction.t(JFLOAT), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  jdouble (JNICALL * GetDoubleField)(JNIEnv *env, jobject obj, jfieldID fieldID);
  public static final JNIFunction GetDoubleField = JNIFunction.create(103, false, "GetDoubleField",JNIFunction.t(JDOUBLE), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID));

  //  void (JNICALL * SetObjectField)(JNIEnv *env, jobject obj, jfieldID fieldID, jobject value);
  public static final JNIFunction SetObjectField = JNIFunction.create(104, false, "SetObjectField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID), JNIFunction.t(JOBJECT));

  //  void (JNICALL * SetBooleanField)(JNIEnv *env, jobject obj, jfieldID fieldID, jboolean value);
  public static final JNIFunction SetBooleanField = JNIFunction.create(105, false, "SetBooleanField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JBOOLEAN));

  //  void (JNICALL * SetByteField)(JNIEnv *env, jobject obj, jfieldID fieldID, jbyte value);
  public static final JNIFunction SetByteField = JNIFunction.create(106, false, "SetByteField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JBYTE));

  //  void (JNICALL * SetCharField)(JNIEnv *env, jobject obj, jfieldID fieldID, jchar value);
  public static final JNIFunction SetCharField = JNIFunction.create(107, false, "SetCharField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JCHAR));

  //  void (JNICALL * SetShortField)(JNIEnv *env, jobject obj, jfieldID fieldID, jshort value);
  public static final JNIFunction SetShortField = JNIFunction.create(108, false, "SetShortField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JSHORT));

  //  void (JNICALL * SetIntField)(JNIEnv *env, jobject obj, jfieldID fieldID, jint value);
  public static final JNIFunction SetIntField = JNIFunction.create(109, false, "SetIntField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JINT));

  //  void (JNICALL * SetLongField)(JNIEnv *env, jobject obj, jfieldID fieldID, jlong value);
  public static final JNIFunction SetLongField = JNIFunction.create(110, false, "SetLongField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JLONG));

  //  void (JNICALL * SetFloatField)(JNIEnv *env, jobject obj, jfieldID fieldID, jfloat value);
  public static final JNIFunction SetFloatField = JNIFunction.create(111, false, "SetFloatField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JFLOAT));

  //  void (JNICALL * SetDoubleField)(JNIEnv *env, jobject obj, jfieldID fieldID, jdouble value);
  public static final JNIFunction SetDoubleField = JNIFunction.create(112, false, "SetDoubleField",JNIFunction.t(VOID), JNIFunction.nt(JOBJECT), JNIFunction.nt(JFIELDID),JNIFunction.t(JDOUBLE));

  //  jmethodID (JNICALL * GetStaticMethodID)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
  public static final JNIFunction GetStaticMethodID = JNIFunction.create(113, false, "GetStaticMethodID",JNIFunction.t(JMETHODID), JNIFunction.nt(JCLASS), JNIFunction.nt(UTF8_METHOD_NAME), JNIFunction.nt(UTF8_METHOD_DESC));

  //  jobject (JNICALL * CallStaticObjectMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticObjectMethod = JNIFunction.create(114, true, "CallStaticObjectMethod",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jobject (JNICALL * CallStaticObjectMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticObjectMethodV = JNIFunction.create(115, false, "CallStaticObjectMethodV",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jobject (JNICALL * CallStaticObjectMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticObjectMethodA = JNIFunction.create(116, false, "CallStaticObjectMethodA",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jboolean (JNICALL * CallStaticBooleanMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticBooleanMethod = JNIFunction.create(117, true, "CallStaticBooleanMethod",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jboolean (JNICALL * CallStaticBooleanMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticBooleanMethodV = JNIFunction.create(118, false, "CallStaticBooleanMethodV",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jboolean (JNICALL * CallStaticBooleanMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticBooleanMethodA = JNIFunction.create(119, false, "CallStaticBooleanMethodA",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jbyte (JNICALL * CallStaticByteMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticByteMethod = JNIFunction.create(120, true, "CallStaticByteMethod",JNIFunction.t(JBYTE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jbyte (JNICALL * CallStaticByteMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticByteMethodV = JNIFunction.create(121, false, "CallStaticByteMethodV",JNIFunction.t(JBYTE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jbyte (JNICALL * CallStaticByteMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticByteMethodA = JNIFunction.create(122, false, "CallStaticByteMethodA",JNIFunction.t(JBYTE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jchar (JNICALL * CallStaticCharMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticCharMethod = JNIFunction.create(123, true, "CallStaticCharMethod",JNIFunction.t(JCHAR), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jchar (JNICALL * CallStaticCharMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticCharMethodV = JNIFunction.create(124, false, "CallStaticCharMethodV",JNIFunction.t(JCHAR), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jchar (JNICALL * CallStaticCharMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticCharMethodA = JNIFunction.create(125, false, "CallStaticCharMethodA",JNIFunction.t(JCHAR), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jshort (JNICALL * CallStaticShortMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticShortMethod = JNIFunction.create(126, true, "CallStaticShortMethod",JNIFunction.t(JSHORT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jshort (JNICALL * CallStaticShortMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticShortMethodV = JNIFunction.create(127, false, "CallStaticShortMethodV",JNIFunction.t(JSHORT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jshort (JNICALL * CallStaticShortMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticShortMethodA = JNIFunction.create(128, false, "CallStaticShortMethodA",JNIFunction.t(JSHORT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jint (JNICALL * CallStaticIntMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticIntMethod = JNIFunction.create(129, true, "CallStaticIntMethod",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jint (JNICALL * CallStaticIntMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticIntMethodV = JNIFunction.create(130, false, "CallStaticIntMethodV",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jint (JNICALL * CallStaticIntMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticIntMethodA = JNIFunction.create(131, false, "CallStaticIntMethodA",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jlong (JNICALL * CallStaticLongMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticLongMethod = JNIFunction.create(132, true, "CallStaticLongMethod",JNIFunction.t(JLONG), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jlong (JNICALL * CallStaticLongMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticLongMethodV = JNIFunction.create(133, false, "CallStaticLongMethodV",JNIFunction.t(JLONG), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jlong (JNICALL * CallStaticLongMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticLongMethodA = JNIFunction.create(134, false, "CallStaticLongMethodA",JNIFunction.t(JLONG), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jfloat (JNICALL * CallStaticFloatMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticFloatMethod = JNIFunction.create(135, true, "CallStaticFloatMethod",JNIFunction.t(JFLOAT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jfloat (JNICALL * CallStaticFloatMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticFloatMethodV = JNIFunction.create(136, false, "CallStaticFloatMethodV",JNIFunction.t(JFLOAT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jfloat (JNICALL * CallStaticFloatMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticFloatMethodA = JNIFunction.create(137, false, "CallStaticFloatMethodA",JNIFunction.t(JFLOAT), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jdouble (JNICALL * CallStaticDoubleMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticDoubleMethod = JNIFunction.create(138, true, "CallStaticDoubleMethod",JNIFunction.t(JDOUBLE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  jdouble (JNICALL * CallStaticDoubleMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticDoubleMethodV = JNIFunction.create(139, false, "CallStaticDoubleMethodV",JNIFunction.t(JDOUBLE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  jdouble (JNICALL * CallStaticDoubleMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue *args);
  public static final JNIFunction CallStaticDoubleMethodA = JNIFunction.create(140, false, "CallStaticDoubleMethodA",JNIFunction.t(JDOUBLE), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  void (JNICALL * CallStaticVoidMethod)(JNIEnv *env, jclass clazz, jmethodID methodID, ...);
  public static final JNIFunction CallStaticVoidMethod = JNIFunction.create(141, true, "CallStaticVoidMethod",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID));

  //  void (JNICALL * CallStaticVoidMethodV)(JNIEnv *env, jclass clazz, jmethodID methodID, va_list args);
  public static final JNIFunction CallStaticVoidMethodV = JNIFunction.create(142, false, "CallStaticVoidMethodV",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(VA_LIST));

  //  void (JNICALL * CallStaticVoidMethodA)(JNIEnv *env, jclass clazz, jmethodID methodID, jvalue * args);
  public static final JNIFunction CallStaticVoidMethodA = JNIFunction.create(143, false, "CallStaticVoidMethodA",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JMETHODID),JNIFunction.t(JVALUE_POINTER));

  //  jfieldID (JNICALL * GetStaticFieldID)(JNIEnv *env, jclass clazz, const char *name, const char *sig);
  public static final JNIFunction GetStaticFieldID = JNIFunction.create(144, false, "GetStaticFieldID",JNIFunction.t(JFIELDID), JNIFunction.nt(JCLASS), JNIFunction.nt(UTF8_FIELD_NAME), JNIFunction.nt(UTF8_FIELD_DESC));

  //  jobject (JNICALL * GetStaticObjectField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticObjectField = JNIFunction.create(145, false, "GetStaticObjectField",JNIFunction.t(JOBJECT), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jboolean (JNICALL * GetStaticBooleanField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticBooleanField = JNIFunction.create(146, false, "GetStaticBooleanField",JNIFunction.t(JBOOLEAN), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jbyte (JNICALL * GetStaticByteField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticByteField = JNIFunction.create(147, false, "GetStaticByteField",JNIFunction.t(JBYTE), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jchar (JNICALL * GetStaticCharField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticCharField = JNIFunction.create(148, false, "GetStaticCharField",JNIFunction.t(JCHAR), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jshort (JNICALL * GetStaticShortField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticShortField = JNIFunction.create(149, false, "GetStaticShortField",JNIFunction.t(JSHORT), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jint (JNICALL * GetStaticIntField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticIntField = JNIFunction.create(150, false, "GetStaticIntField",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jlong (JNICALL * GetStaticLongField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticLongField = JNIFunction.create(151, false, "GetStaticLongField",JNIFunction.t(JLONG), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jfloat (JNICALL * GetStaticFloatField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticFloatField = JNIFunction.create(152, false, "GetStaticFloatField",JNIFunction.t(JFLOAT), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  jdouble (JNICALL * GetStaticDoubleField)(JNIEnv *env, jclass clazz, jfieldID fieldID);
  public static final JNIFunction GetStaticDoubleField = JNIFunction.create(153, false, "GetStaticDoubleField",JNIFunction.t(JDOUBLE), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID));

  //  void (JNICALL * SetStaticObjectField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jobject value);
  public static final JNIFunction SetStaticObjectField = JNIFunction.create(154, false, "SetStaticObjectField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID), JNIFunction.t(JOBJECT));

  //  void (JNICALL * SetStaticBooleanField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jboolean value);
  public static final JNIFunction SetStaticBooleanField = JNIFunction.create(155, false, "SetStaticBooleanField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JBOOLEAN));

  //  void (JNICALL * SetStaticByteField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jbyte value);
  public static final JNIFunction SetStaticByteField = JNIFunction.create(156, false, "SetStaticByteField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JBYTE));

  //  void (JNICALL * SetStaticCharField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jchar value);
  public static final JNIFunction SetStaticCharField = JNIFunction.create(157, false, "SetStaticCharField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JCHAR));

  //  void (JNICALL * SetStaticShortField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jshort value);
  public static final JNIFunction SetStaticShortField = JNIFunction.create(158, false, "SetStaticShortField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JSHORT));

  //  void (JNICALL * SetStaticIntField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jint value);
  public static final JNIFunction SetStaticIntField = JNIFunction.create(159, false, "SetStaticIntField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JINT));

  //  void (JNICALL * SetStaticLongField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jlong value);
  public static final JNIFunction SetStaticLongField = JNIFunction.create(160, false, "SetStaticLongField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JLONG));

  //  void (JNICALL * SetStaticFloatField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jfloat value);
  public static final JNIFunction SetStaticFloatField = JNIFunction.create(161, false, "SetStaticFloatField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JFLOAT));

  //  void (JNICALL * SetStaticDoubleField)(JNIEnv *env, jclass clazz, jfieldID fieldID, jdouble value);
  public static final JNIFunction SetStaticDoubleField = JNIFunction.create(162, false, "SetStaticDoubleField",JNIFunction.t(VOID), JNIFunction.nt(JCLASS), JNIFunction.nt(JFIELDID),JNIFunction.t(JDOUBLE));

  //  jstring (JNICALL * NewString)(JNIEnv *env, const jchar *unicodeChars, jsize len);
  public static final JNIFunction NewString = JNIFunction.create(163, false, "NewString",JNIFunction.t(JSTRING), JNIFunction.nt(JCHAR_CONST_POINTER),JNIFunction.t(JSIZE));

  //  jsize (JNICALL * GetStringLength)(JNIEnv *env, jstring string);
  public static final JNIFunction GetStringLength = JNIFunction.create(164, false, "GetStringLength",JNIFunction.t(JSIZE), JNIFunction.nt(JSTRING));

  //  const jchar *(JNICALL * GetStringChars)(JNIEnv *env, jstring string, jboolean *isCopy);
  public static final JNIFunction GetStringChars = JNIFunction.create(165, false, "GetStringChars",JNIFunction.t(JCHAR_CONST_POINTER), JNIFunction.nt(JSTRING),JNIFunction.t(JBOOLEAN_POINTER));

  //  void (JNICALL * ReleaseStringChars)(JNIEnv *env, jstring string, const jchar *utf);
  public static final JNIFunction ReleaseStringChars = JNIFunction.create(166, false, "ReleaseStringChars",JNIFunction.t(VOID), JNIFunction.nt(JSTRING), JNIFunction.nt(JCHAR_CONST_POINTER));

  //  jstring (JNICALL * NewStringUTF)(JNIEnv *env, const char *bytes);
  public static final JNIFunction NewStringUTF = JNIFunction.create(167, false, "NewStringUTF",JNIFunction.t(JSTRING), JNIFunction.nt(UTF8_MESSAGE));

  //  jsize (JNICALL * GetStringUTFLength)(JNIEnv *env, jstring string);
  public static final JNIFunction GetStringUTFLength = JNIFunction.create(168, false, "GetStringUTFLength",JNIFunction.t(JSIZE), JNIFunction.nt(JSTRING));

  //  const char* (JNICALL * GetStringUTFChars)(JNIEnv *env, jstring string, jboolean *isCopy);
  public static final JNIFunction GetStringUTFChars = JNIFunction.create(169, false, "GetStringUTFChars",JNIFunction.t(UTF8_MESSAGE), JNIFunction.nt(JSTRING),JNIFunction.t(JBOOLEAN_POINTER));

  //  void (JNICALL * ReleaseStringUTFChars)(JNIEnv *env, jstring string, const char* utf);
  public static final JNIFunction ReleaseStringUTFChars = JNIFunction.create(170, false, "ReleaseStringUTFChars",JNIFunction.t(VOID), JNIFunction.nt(JSTRING), JNIFunction.nt(UTF8_MESSAGE));

  //  jsize (JNICALL * GetArrayLength)(JNIEnv *env, jarray array);
  public static final JNIFunction GetArrayLength = JNIFunction.create(171, false, "GetArrayLength",JNIFunction.t(JSIZE), JNIFunction.nt(JARRAY));

  //  jobjectArray (JNICALL * NewObjectArray)(JNIEnv *env, jsize length, jclass clazz, jobject initialElement);
  public static final JNIFunction NewObjectArray = JNIFunction.create(172, false, "NewObjectArray",JNIFunction.t(JOBJECTARRAY),JNIFunction.t(JSIZE), JNIFunction.nt(JCLASS),JNIFunction.t(JOBJECT));

  //  jobject (JNICALL * GetObjectArrayElement)(JNIEnv *env, jobjectArray array, jsize index);
  public static final JNIFunction GetObjectArrayElement = JNIFunction.create(173, false, "GetObjectArrayElement",JNIFunction.t(JOBJECT), JNIFunction.nt(JOBJECTARRAY),JNIFunction.t(JSIZE));

  //  void (JNICALL * SetObjectArrayElement)(JNIEnv *env, jobjectArray array, jsize index, jobject value);
  public static final JNIFunction SetObjectArrayElement = JNIFunction.create(174, false, "SetObjectArrayElement",JNIFunction.t(VOID), JNIFunction.nt(JOBJECTARRAY),JNIFunction.t(JSIZE), JNIFunction.nt(JOBJECT));

  //  jbooleanArray (JNICALL * NewBooleanArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewBooleanArray = JNIFunction.create(175, false, "NewBooleanArray",JNIFunction.t(JBOOLEANARRAY),JNIFunction.t(JSIZE));

  //  jbyteArray (JNICALL * NewByteArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewByteArray = JNIFunction.create(176, false, "NewByteArray",JNIFunction.t(JBYTEARRAY),JNIFunction.t(JSIZE));

  //  jcharArray (JNICALL * NewCharArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewCharArray = JNIFunction.create(177, false, "NewCharArray",JNIFunction.t(JCHARARRAY),JNIFunction.t(JSIZE));

  //  jshortArray (JNICALL * NewShortArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewShortArray = JNIFunction.create(178, false, "NewShortArray",JNIFunction.t(JSHORTARRAY),JNIFunction.t(JSIZE));

  //  jintArray (JNICALL * NewIntArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewIntArray = JNIFunction.create(179, false, "NewIntArray",JNIFunction.t(JINTARRAY),JNIFunction.t(JSIZE));

  //  jlongArray (JNICALL * NewLongArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewLongArray = JNIFunction.create(180, false, "NewLongArray",JNIFunction.t(JLONGARRAY),JNIFunction.t(JSIZE));

  //  jfloatArray (JNICALL * NewFloatArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewFloatArray = JNIFunction.create(181, false, "NewFloatArray",JNIFunction.t(JFLOATARRAY),JNIFunction.t(JSIZE));

  //  jdoubleArray (JNICALL * NewDoubleArray)(JNIEnv *env, jsize length);
  public static final JNIFunction NewDoubleArray = JNIFunction.create(182, false, "NewDoubleArray",JNIFunction.t(JDOUBLEARRAY),JNIFunction.t(JSIZE));

  //  jboolean * (JNICALL * GetBooleanArrayElements)(JNIEnv *env, jbooleanArray array, jboolean *isCopy);
  public static final JNIFunction GetBooleanArrayElements = JNIFunction.create(183, false, "GetBooleanArrayElements",JNIFunction.t(JBOOLEAN_POINTER), JNIFunction.nt(JBOOLEANARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jbyte * (JNICALL * GetByteArrayElements)(JNIEnv *env, jbyteArray array, jboolean *isCopy);
  public static final JNIFunction GetByteArrayElements = JNIFunction.create(184, false, "GetByteArrayElements",JNIFunction.t(JBYTE_POINTER), JNIFunction.nt(JBYTEARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jchar * (JNICALL * GetCharArrayElements)(JNIEnv *env, jcharArray array, jboolean *isCopy);
  public static final JNIFunction GetCharArrayElements = JNIFunction.create(185, false, "GetCharArrayElements",JNIFunction.t(JCHAR_POINTER), JNIFunction.nt(JCHARARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jshort * (JNICALL * GetShortArrayElements)(JNIEnv *env, jshortArray array, jboolean *isCopy);
  public static final JNIFunction GetShortArrayElements = JNIFunction.create(186, false, "GetShortArrayElements",JNIFunction.t(JSHORT_POINTER), JNIFunction.nt(JSHORTARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jint * (JNICALL * GetIntArrayElements)(JNIEnv *env, jintArray array, jboolean *isCopy);
  public static final JNIFunction GetIntArrayElements = JNIFunction.create(187, false, "GetIntArrayElements",JNIFunction.t(JINT_POINTER), JNIFunction.nt(JINTARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jlong * (JNICALL * GetLongArrayElements)(JNIEnv *env, jlongArray array, jboolean *isCopy);
  public static final JNIFunction GetLongArrayElements = JNIFunction.create(188, false, "GetLongArrayElements",JNIFunction.t(JLONG_POINTER), JNIFunction.nt(JLONGARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jfloat * (JNICALL * GetFloatArrayElements)(JNIEnv *env, jfloatArray array, jboolean *isCopy);
  public static final JNIFunction GetFloatArrayElements = JNIFunction.create(189, false, "GetFloatArrayElements",JNIFunction.t(JFLOAT_POINTER), JNIFunction.nt(JFLOATARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  jdouble * (JNICALL * GetDoubleArrayElements)(JNIEnv *env, jdoubleArray array, jboolean *isCopy);
  public static final JNIFunction GetDoubleArrayElements = JNIFunction.create(190, false, "GetDoubleArrayElements",JNIFunction.t(JDOUBLE_POINTER), JNIFunction.nt(JDOUBLEARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  void (JNICALL * ReleaseBooleanArrayElements)(JNIEnv *env, jbooleanArray array, jboolean *elems, jint mode);
  public static final JNIFunction ReleaseBooleanArrayElements = JNIFunction.create(191, false, "ReleaseBooleanArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JBOOLEANARRAY), JNIFunction.nt(JBOOLEAN_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseByteArrayElements)(JNIEnv *env, jbyteArray array, jbyte *elems, jint mode);
  public static final JNIFunction ReleaseByteArrayElements = JNIFunction.create(192, false, "ReleaseByteArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JBYTEARRAY), JNIFunction.nt(JBYTE_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseCharArrayElements)(JNIEnv *env, jcharArray array, jchar *elems, jint mode);
  public static final JNIFunction ReleaseCharArrayElements = JNIFunction.create(193, false, "ReleaseCharArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JCHARARRAY), JNIFunction.nt(JCHAR_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseShortArrayElements)(JNIEnv *env, jshortArray array, jshort *elems, jint mode);
  public static final JNIFunction ReleaseShortArrayElements = JNIFunction.create(194, false, "ReleaseShortArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JSHORTARRAY), JNIFunction.nt(JSHORT_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseIntArrayElements)(JNIEnv *env, jintArray array, jint *elems, jint mode);
  public static final JNIFunction ReleaseIntArrayElements = JNIFunction.create(195, false, "ReleaseIntArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JINTARRAY), JNIFunction.nt(JINT_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseLongArrayElements)(JNIEnv *env, jlongArray array, jlong *elems, jint mode);
  public static final JNIFunction ReleaseLongArrayElements = JNIFunction.create(196, false, "ReleaseLongArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JLONGARRAY), JNIFunction.nt(JLONG_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseFloatArrayElements)(JNIEnv *env, jfloatArray array, jfloat *elems, jint mode);
  public static final JNIFunction ReleaseFloatArrayElements = JNIFunction.create(197, false, "ReleaseFloatArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JFLOATARRAY), JNIFunction.nt(JFLOAT_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * ReleaseDoubleArrayElements)(JNIEnv *env, jdoubleArray array, jdouble *elems, jint mode);
  public static final JNIFunction ReleaseDoubleArrayElements = JNIFunction.create(198, false, "ReleaseDoubleArrayElements",JNIFunction.t(VOID), JNIFunction.nt(JDOUBLEARRAY), JNIFunction.nt(JDOUBLE_POINTER),JNIFunction.t(JINT));

  //  void (JNICALL * GetBooleanArrayRegion)(JNIEnv *env, jbooleanArray array, jsize start, jsize len, jboolean *buf);
  public static final JNIFunction GetBooleanArrayRegion = JNIFunction.create(199, false, "GetBooleanArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JBOOLEANARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JBOOLEAN_POINTER));

  //  void (JNICALL * GetByteArrayRegion)(JNIEnv *env, jbyteArray array, jsize start, jsize len, jbyte *buf);
  public static final JNIFunction GetByteArrayRegion = JNIFunction.create(200, false, "GetByteArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JBYTEARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JBYTE_POINTER));

  //  void (JNICALL * GetCharArrayRegion)(JNIEnv *env, jcharArray array, jsize start, jsize len, jchar *buf);
  public static final JNIFunction GetCharArrayRegion = JNIFunction.create(201, false, "GetCharArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JCHARARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JCHAR_POINTER));

  //  void (JNICALL * GetShortArrayRegion)(JNIEnv *env, jshortArray array, jsize start, jsize len, jshort *buf);
  public static final JNIFunction GetShortArrayRegion = JNIFunction.create(202, false, "GetShortArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JSHORTARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JSHORT_POINTER));

  //  void (JNICALL * GetIntArrayRegion)(JNIEnv *env, jintArray array, jsize start, jsize len, jint *buf);
  public static final JNIFunction GetIntArrayRegion = JNIFunction.create(203, false, "GetIntArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JINTARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JINT_POINTER));

  //  void (JNICALL * GetLongArrayRegion)(JNIEnv *env, jlongArray array, jsize start, jsize len, jlong *buf);
  public static final JNIFunction GetLongArrayRegion = JNIFunction.create(204, false, "GetLongArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JLONGARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JLONG_POINTER));

  //  void (JNICALL * GetFloatArrayRegion)(JNIEnv *env, jfloatArray array, jsize start, jsize len, jfloat *buf);
  public static final JNIFunction GetFloatArrayRegion = JNIFunction.create(205, false, "GetFloatArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JFLOATARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JFLOAT_POINTER));

  //  void (JNICALL * GetDoubleArrayRegion)(JNIEnv *env, jdoubleArray array, jsize start, jsize len, jdouble *buf);
  public static final JNIFunction GetDoubleArrayRegion = JNIFunction.create(206, false, "GetDoubleArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JDOUBLEARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JDOUBLE_POINTER));

  //  void (JNICALL * SetBooleanArrayRegion)(JNIEnv *env, jbooleanArray array, jsize start, jsize len, jboolean *buf);
  public static final JNIFunction SetBooleanArrayRegion = JNIFunction.create(207, false, "SetBooleanArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JBOOLEANARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JBOOLEAN_CONST_POINTER));

  //  void (JNICALL * SetByteArrayRegion)(JNIEnv *env, jbyteArray array, jsize start, jsize len, jbyte *buf);
  public static final JNIFunction SetByteArrayRegion = JNIFunction.create(208, false, "SetByteArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JBYTEARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JBYTE_CONST_POINTER));

  //  void (JNICALL * SetCharArrayRegion)(JNIEnv *env, jcharArray array, jsize start, jsize len, jchar *buf);
  public static final JNIFunction SetCharArrayRegion = JNIFunction.create(209, false, "SetCharArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JCHARARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JCHAR_CONST_POINTER));

  //  void (JNICALL * SetShortArrayRegion)(JNIEnv *env, jshortArray array, jsize start, jsize len, jshort *buf);
  public static final JNIFunction SetShortArrayRegion = JNIFunction.create(210, false, "SetShortArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JSHORTARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JSHORT_CONST_POINTER));

  //  void (JNICALL * SetIntArrayRegion)(JNIEnv *env, jintArray array, jsize start, jsize len, jint *buf);
  public static final JNIFunction SetIntArrayRegion = JNIFunction.create(211, false, "SetIntArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JINTARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JINT_CONST_POINTER));

  //  void (JNICALL * SetLongArrayRegion)(JNIEnv *env, jlongArray array, jsize start, jsize len, jlong *buf);
  public static final JNIFunction SetLongArrayRegion = JNIFunction.create(212, false, "SetLongArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JLONGARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JLONG_CONST_POINTER));

  //  void (JNICALL * SetFloatArrayRegion)(JNIEnv *env, jfloatArray array, jsize start, jsize len, jfloat *buf);
  public static final JNIFunction SetFloatArrayRegion = JNIFunction.create(213, false, "SetFloatArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JFLOATARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JFLOAT_CONST_POINTER));

  //  void (JNICALL * SetDoubleArrayRegion)(JNIEnv *env, jdoubleArray array, jsize start, jsize len, jdouble *buf);
  public static final JNIFunction SetDoubleArrayRegion = JNIFunction.create(214, false, "SetDoubleArrayRegion",JNIFunction.t(VOID), JNIFunction.nt(JDOUBLEARRAY),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JDOUBLE_CONST_POINTER));

  //  jint (JNICALL * RegisterNatives)(JNIEnv *env, jclass clazz, const JNINativeMethod *methods, jint nMethods);
  public static final JNIFunction RegisterNatives = JNIFunction.create(215, false, "RegisterNatives",JNIFunction.t(JINT), JNIFunction.nt(JCLASS), JNIFunction.nt(JAVA_NATIVE_METHOD_POINTER),JNIFunction.t(JINT));

  //  jint (JNICALL * UnregisterNatives)(JNIEnv *env, jclass clazz);
  public static final JNIFunction UnregisterNatives = JNIFunction.create(216, false, "UnregisterNatives",JNIFunction.t(JINT), JNIFunction.nt(JCLASS));

  //  jint (JNICALL * MonitorEnter)(JNIEnv *env, jobject obj);
  public static final JNIFunction MonitorEnter = JNIFunction.create(217, false, "MonitorEnter",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT));

  //  jint (JNICALL * MonitorExit)(JNIEnv *env, jobject obj);
  public static final JNIFunction MonitorExit = JNIFunction.create(218, false, "MonitorExit",JNIFunction.t(JINT), JNIFunction.nt(JOBJECT));

  //  jint (JNICALL * GetJavaVM)(JNIEnv *env, JavaVM **vm);
  public static final JNIFunction GetJavaVM = JNIFunction.create(219, false, "GetJavaVM",JNIFunction.t(JINT), JNIFunction.nt(JAVA_VM_POINTER));

  //  void (JNICALL * GetStringRegion)(JNIEnv *env, jstring str, jsize start, jsize len, jchar *buf);
  public static final JNIFunction GetStringRegion = JNIFunction.create(220, false, "GetStringRegion",JNIFunction.t(VOID), JNIFunction.nt(JSTRING),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(JCHAR_POINTER));

  //  void (JNICALL * GetStringUTFRegion)(JNIEnv *env, jstring str, jsize start, jsize len, char *buf);
  public static final JNIFunction GetStringUTFRegion = JNIFunction.create(221, false, "GetStringUTFRegion",JNIFunction.t(VOID), JNIFunction.nt(JSTRING),JNIFunction.t(JSIZE),JNIFunction.t(JSIZE), JNIFunction.nt(UTF8_MESSAGE_BUFFER));

  //  void * (JNICALL * GetPrimitiveArrayCritical)(JNIEnv *env, jarray array, jboolean *isCopy);
  public static final JNIFunction GetPrimitiveArrayCritical = JNIFunction.create(222, false, "GetPrimitiveArrayCritical",JNIFunction.t(VOID_POINTER), JNIFunction.nt(JARRAY),JNIFunction.t(JBOOLEAN_POINTER));

  //  void (JNICALL * ReleasePrimitiveArrayCritical)(JNIEnv *env, jarray array, void *carray, jint mode);
  public static final JNIFunction ReleasePrimitiveArrayCritical = JNIFunction.create(223, false, "ReleasePrimitiveArrayCritical",JNIFunction.t(VOID), JNIFunction.nt(JARRAY), JNIFunction.nt(VOID_POINTER),JNIFunction.t(JINT));

  //  jchar * (JNICALL * GetStringCritical)(JNIEnv *env, jstring string, jboolean *isCopy);
  public static final JNIFunction GetStringCritical = JNIFunction.create(224, false, "GetStringCritical",JNIFunction.t(JCHAR_CONST_POINTER), JNIFunction.nt(JSTRING),JNIFunction.t(JBOOLEAN_POINTER));

  //  void (JNICALL * ReleaseStringCritical)(JNIEnv *env, jstring string, const jchar *carray);
  public static final JNIFunction ReleaseStringCritical = JNIFunction.create(225, false, "ReleaseStringCritical",JNIFunction.t(VOID), JNIFunction.nt(JSTRING), JNIFunction.nt(JCHAR_CONST_POINTER));

  //  jweak (JNICALL * NewWeakGlobalRef)(JNIEnv *env, jobject obj);
  public static final JNIFunction NewWeakGlobalRef = JNIFunction.create(226, false, "NewWeakGlobalRef",JNIFunction.t(JWEAK), JNIFunction.nt(JOBJECT));

  //  void (JNICALL * DeleteWeakGlobalRef)(JNIEnv *env, jweak obj);
  public static final JNIFunction DeleteWeakGlobalRef = JNIFunction.create(227, false, "DeleteWeakGlobalRef",JNIFunction.t(VOID),JNIFunction.t(JWEAK));

  //  jboolean (JNICALL * ExceptionCheck)(JNIEnv *env);
  public static final JNIFunction ExceptionCheck = JNIFunction.create(228, false, "ExceptionCheck",JNIFunction.t(JBOOLEAN));

  //  jobject (JNICALL * NewDirectByteBuffer)(JNIEnv *env, void *address, jlong capacity);
  public static final JNIFunction NewDirectByteBuffer = JNIFunction.create(229, false, "NewDirectByteBuffer",JNIFunction.t(JOBJECT), JNIFunction.nt(VOID_POINTER),JNIFunction.t(JLONG));

  //  void * (JNICALL * GetDirectBufferAddress)(JNIEnv *env, jobject buf);
  public static final JNIFunction GetDirectBufferAddress = JNIFunction.create(230, false, "GetDirectBufferAddress",JNIFunction.t(VOID_POINTER), JNIFunction.nt(JOBJECT));

  //  jlong (JNICALL * GetDirectBufferCapacity)(JNIEnv *env, jobject buf);
  public static final JNIFunction GetDirectBufferCapacity = JNIFunction.create(231, false, "GetDirectBufferCapacity",JNIFunction.t(JLONG), JNIFunction.nt(JOBJECT));

  //  jobjectRefType (JNICALL * GetObjectRefType)(JNIEnv *env, jobject obj);
  public static final JNIFunction GetObjectRefType = JNIFunction.create(232, false, "GetObjectRefType",JNIFunction.t(JOBJECT_REF_TYPE), JNIFunction.nt(JOBJECT));
}
