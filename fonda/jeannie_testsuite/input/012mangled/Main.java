class Main {
  static { System.loadLibrary("Main"); }
  public static void main(String[] args) {
    new JavaEnvFor_main(args);
  }
  private static final class JavaEnvFor_main {
    String[] _args;
    int _j1;
    int _j2;
    JavaEnvFor_main(final String[] args) {
      _args = args;
      _j2 = 0;
      j2c2();
      System.out.println("j2: expected 2, got " + _j2);
    }
    private native void j2c2();
    private void c2j1(long cEnv) {
      _j1 = 0;
      j2c1(cEnv);
      _j2++;
      System.out.println("j1: expected 1, got " + _j1);
    }
    private native void j2c1(long cEnv);
    private void c2j0(long cEnv) {
      j2c0(cEnv);
      _j2++;
      _j1++;
    }
    private native void j2c0(long cEnv);
  }
}
