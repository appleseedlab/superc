/* Mangled JNI hello-world. */
class Main {
  static {
    System.loadLibrary("Main");
  }
  static native void sayHi();
  public static void main(String[]  args){
    sayHi();
  }
}
