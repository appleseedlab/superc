public class VMResourceDoubleFree {
  static {System.loadLibrary("VMResourceDoubleFree");}
  public static void main(String[] args) {
    foo("Hello");
  }
  public static native void foo(String s);
}
