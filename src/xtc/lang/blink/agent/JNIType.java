package xtc.lang.blink.agent;

/**
 * 9 primitives types: jboolean, jbyte, jchar, jshort, jint, jlong, jfloat, jdouble, jsize
 * 
 * 15 reference types: jobject, jclass, jstring, jarray, jbooleanArray, jbyteArray,
 *   jcharArray, jshortArray, jintArray, jlongArray, jfloatArray,
 *   jdoubleArray, jobjectArray, jthrowable, jweak
 *
 * 2 identifiers:jmethodID and jfieldID
 * 
 * 6 UTF-8 C string (const char*)
 *  + generic string message
 *  +  method name
 *  + field name
 *  + class descriptors (e.g., "java/lang/String")
 *  + field descriptors (e.g., "Ljava/lang/String;")
 *  + method descriptors (e.g., "()Ljava/lang/String;"
 *
 * Unknown
 * 
 * @author Byeongcheol Lee
 */
public abstract class JNIType {

  final String name; 
   
  JNIType(String name) {
    this.name = name;
  }

  static final class VoidType extends JNIType {
    public VoidType() {
      super("void");
    }    
  }
  
  static final class PrimitiveType extends JNIType {
    public PrimitiveType(String name) {
      super(name);
    }   
  }

  static class ReferenceType extends JNIType{
    ReferenceType(String name) {
      super(name);
    }
  }

  static class JMethodIDType extends JNIType{
    JMethodIDType(String name) {
      super(name);
    }
  }
  
  static class JFieldIDType extends JNIType{
    JFieldIDType(String name) {
      super(name);
    }
  }
  
  static final class ArrayReferenceType extends ReferenceType {
    final JNIType elementType;
    public ArrayReferenceType(String name, JNIType elementType) {
      super(name);
      this.elementType = elementType;
    }
  }
  
  static class PointerType extends JNIType {
    PointerType(String name) {
      super(name);
    }
  }

  static class CStringType extends PointerType { 
    CStringType(String name) {
      super(name);
    }
  }

}
