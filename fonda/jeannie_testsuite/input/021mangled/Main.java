class Main {
  static { System.loadLibrary("Main"); }
  public static void main(String[] args) {
    int[] a = { 3, 1, 4, 2, 4, 1, 7, 9 };
    foo(a);
    System.out.print("expected 5 3 4 2, got");
    for (int i=0; i<a.length; i++)
      System.out.print(" " + a[i]);
    System.out.println();
  }
  static void foo(int[] ja) {
    JavaEnvFor_Main_foo jEnv = new JavaEnvFor_Main_foo(ja);
  }
  private static final class JavaEnvFor_Main_foo {
    int[] _ja;
    JavaEnvFor_Main_foo(final int[] ja) {
      _ja = ja;
      j2c();
    }
    private native void j2c();
    private int[] c2j(long cEnv) {
      return _ja;
    }
  }
}
