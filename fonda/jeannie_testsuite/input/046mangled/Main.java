class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    int []  _ja;
    boolean _returnAbrupt;

    private int []  c2j(final long cEnv) throws Exception {
      return this._ja;
    }

    private void c2j1(final long cEnv) throws Exception {
      throw new ArithmeticException("/ by 0");
    }

    private native void j2c(final long cEnv);
    private native void j2c1(final long cEnv);
    private native void j2c2(final long cEnv);

    private void c2j2(final long cEnv) throws Exception {
      try {
        this.j2c(cEnv);
        if (this._returnAbrupt)
          return;
      } catch (ArithmeticException e) {
        this.j2c1(cEnv);
        if (this._returnAbrupt)
          return;
      } finally {
        this.j2c2(cEnv);
        if (this._returnAbrupt)
          return;
      }
    }

    private native void j2c3();
    int _i1;
    String []  _args;

    JavaEnvFor_main(String []  args) {
      this._returnAbrupt = false;
      this._args = args;

      {
        this._ja = new int[] {
          1, 2, 3, 0
        };

        {
          this.j2c3();
          if (this._returnAbrupt)
            return;
        }

        for (this._i1 = 0; this._i1 < 4; this._i1++)
          System.out.println("ja[" + this._i1 + "] == " + this._ja[this._i1]);
      }
    }
  }
}
