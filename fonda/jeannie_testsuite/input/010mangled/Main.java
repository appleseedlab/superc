class Main {
  static { System.loadLibrary("Main"); }
  public static void main(String args[]) {
    new JavaEnvFor_main(args);
  }
  private static final class JavaEnvFor_main {
    String[] _args;
    int _a;
    int _b;
    JavaEnvFor_main(final String[] args) {
      _args = args;
      _a = 0;
      _b = 0;
      _b = j2c();
      System.out.println(_a + ", " + _b);
    }
    private native int j2c();
    private int c2j() {
      return _a = 1;
    }
  }
}
