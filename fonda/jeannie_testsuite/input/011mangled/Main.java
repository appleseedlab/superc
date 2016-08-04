class Main {
  static { System.loadLibrary("Main"); }
  static native void f();
  public static void main(String args[]) {
    f();
  }
  static int c2j(long pc) {
    return 1 + j2c(pc);
  }
  static native int j2c(long pc);
}
