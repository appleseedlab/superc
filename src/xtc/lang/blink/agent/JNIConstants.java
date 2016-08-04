package xtc.lang.blink.agent;

import xtc.lang.blink.agent.JNIType.ArrayReferenceType;
import xtc.lang.blink.agent.JNIType.CStringType;
import xtc.lang.blink.agent.JNIType.JFieldIDType;
import xtc.lang.blink.agent.JNIType.JMethodIDType;
import xtc.lang.blink.agent.JNIType.PointerType;
import xtc.lang.blink.agent.JNIType.PrimitiveType;
import xtc.lang.blink.agent.JNIType.ReferenceType;
import xtc.lang.blink.agent.JNIType.VoidType;

public interface JNIConstants {

  public static final PrimitiveType JBOOLEAN = new PrimitiveType("jboolean");
  public static final PrimitiveType JBYTE = new PrimitiveType("jbyte");
  public static final PrimitiveType JCHAR = new PrimitiveType("jchar");
  public static final PrimitiveType JSHORT = new PrimitiveType("jshort");
  public static final PrimitiveType JINT = new PrimitiveType("jint");
  public static final PrimitiveType JLONG = new PrimitiveType("jlong");
  public static final PrimitiveType JFLOAT = new PrimitiveType("jfloat");
  public static final PrimitiveType JDOUBLE = new PrimitiveType("jdouble");
  public static final PrimitiveType JSIZE = new PrimitiveType("jsize");

  public static final PointerType JBOOLEAN_POINTER = new PointerType("jboolean *");
  public static final PointerType JBYTE_POINTER = new PointerType("jbyte *");
  public static final PointerType JCHAR_POINTER = new PointerType("jchar *");
  public static final PointerType JSHORT_POINTER = new PointerType("jshort *");
  public static final PointerType JINT_POINTER = new PointerType("jint *");
  public static final PointerType JLONG_POINTER = new PointerType("jlong *");
  public static final PointerType JFLOAT_POINTER = new PointerType("jfloat *");
  public static final PointerType JDOUBLE_POINTER = new PointerType("jdouble *");
  public static final PointerType JSIZE_POINTER = new PointerType("jsize *");
  
  public static final PointerType JBOOLEAN_CONST_POINTER = new PointerType("const jboolean *");
  public static final PointerType JBYTE_CONST_POINTER = new PointerType("const jbyte *");
  public static final PointerType JCHAR_CONST_POINTER = new PointerType("const jchar *");
  public static final PointerType JSHORT_CONST_POINTER = new PointerType("const jshort *");
  public static final PointerType JINT_CONST_POINTER = new PointerType("const jint *");
  public static final PointerType JLONG_CONST_POINTER = new PointerType("const jlong *");
  public static final PointerType JFLOAT_CONST_POINTER = new PointerType("const jfloat *");
  public static final PointerType JDOUBLE_CONST_POINTER = new PointerType("const jdouble *");
  public static final PointerType JSIZE_CONST_POINTER = new PointerType("const jsize *");
  
  public static final ReferenceType JOBJECT = new ReferenceType("jobject");
  public static final ReferenceType JCLASS = new ReferenceType("jclass");
  public static final ReferenceType JSTRING = new ReferenceType("jstring");
  public static final ReferenceType JTHROWABLE = new ReferenceType("jthrowable");

  public static final ArrayReferenceType JARRAY = new ArrayReferenceType("jarray", JOBJECT);
  public static final ArrayReferenceType JBOOLEANARRAY = new ArrayReferenceType("jbooleanArray", JBOOLEAN);
  public static final ArrayReferenceType JBYTEARRAY = new ArrayReferenceType("jbyteArray", JBYTE);
  public static final ArrayReferenceType JCHARARRAY = new ArrayReferenceType("jcharArray", JCHAR);
  public static final ArrayReferenceType JSHORTARRAY = new ArrayReferenceType("jshortArray", JSHORT);
  public static final ArrayReferenceType JINTARRAY = new ArrayReferenceType("jintArray", JINT);
  public static final ArrayReferenceType JLONGARRAY = new ArrayReferenceType("jlongArray", JLONG);
  public static final ArrayReferenceType JFLOATARRAY = new ArrayReferenceType("jfloatArray", JFLOAT);
  public static final ArrayReferenceType JDOUBLEARRAY = new ArrayReferenceType("jdoubleArray", JDOUBLE);
  public static final ArrayReferenceType JOBJECTARRAY = new ArrayReferenceType("jobjectArray", JOBJECT);

  public static final ReferenceType JWEAK = new ReferenceType("jweak");
  
  public static final JMethodIDType JMETHODID = new JMethodIDType("jmethodID");
  public static final JFieldIDType JFIELDID = new JFieldIDType("jfieldID");
  
  public static final CStringType UTF8_METHOD_NAME = new CStringType("const char *");
  public static final CStringType UTF8_FIELD_NAME = new CStringType("const char *");
  public static final CStringType UTF8_CLASS_DESC = new CStringType("const char *");
  public static final CStringType UTF8_FIELD_DESC = new CStringType("const char *");
  public static final CStringType UTF8_METHOD_DESC = new CStringType("const char *");
  public static final CStringType UTF8_MESSAGE = new CStringType("const char *");
  public static final CStringType UTF8_MESSAGE_BUFFER = new CStringType("char *");

  public static final VoidType VOID = new VoidType();
  public static final PointerType VOID_POINTER = new PointerType("void *");
  public static final PointerType VA_LIST = new PointerType("va_list");
  public static final PointerType JVALUE_POINTER = new PointerType("const jvalue *");
  public static final PointerType JAVA_VM_POINTER = new PointerType("JavaVM **");
  public static final PointerType JAVA_NATIVE_METHOD_POINTER = new PointerType("const JNINativeMethod *");
  public static final PrimitiveType JOBJECT_REF_TYPE = new PrimitiveType("jobjectRefType");
  public static final PointerType JNI_ENV = new PointerType("JNIEnv *");
}
