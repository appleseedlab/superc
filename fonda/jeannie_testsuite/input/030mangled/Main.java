class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    String[] _args;
    int[][] _a;
    boolean _returnAbrupt;

    private int c2j(final long cEnv) throws Exception {
      return this._a[1][0];
    }

    private native int j2c();

    JavaEnvFor_main(String[]  args) {
      this._returnAbrupt = false;
      this._args = args;
      this._a = new int[][] { { 1 }, { 2, 3 } };
      this.j2c();
    }
  }
}
