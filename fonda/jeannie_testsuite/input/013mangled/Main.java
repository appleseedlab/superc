class Main {
  static { System.loadLibrary("Main"); }
  public static void main(String[] args) {
    int[] a = { 3, 1, 4 };
    System.out.println("expected 8, got " + sum(a));
  }
  static int sum(int[] ja) {
    JavaEnvFor_Main_sum jEnv = new JavaEnvFor_Main_sum(ja);
    return jEnv._result;
  }
  private static final class JavaEnvFor_Main_sum {
    int[] _ja;
    int _result;
    JavaEnvFor_Main_sum(final int[] ja) {
      _ja = ja;
      j2c();
    }
    private native void j2c();
    private int c2j1(long cEnv) {
      return _ja.length;
    }
    private int[] c2j2(long cEnv) {
      return _ja;
    }
  }
}
