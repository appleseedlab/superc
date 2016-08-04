class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    int _z;
    boolean _returnAbrupt;
    String[]  _args;

    private int c2j(final long cEnv) throws Exception {
      return this._z;
    }
    private native int j2c();

    JavaEnvFor_main(String []  args) {
      this._returnAbrupt = false;
      this._args = args;
      this._z = 1;
      this._z = this.j2c();
      System.err.println(this._z);
    }
  }
}
