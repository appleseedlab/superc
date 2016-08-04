public class VMResourceLeak {
  static {System.loadLibrary("VMResourceLeak");}
  public static void main(String[] args) {
    foo("Leak");
  }
  public static native void foo(String s);
}
