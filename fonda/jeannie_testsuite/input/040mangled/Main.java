class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    java.lang.String _input;
    boolean _hasDecimalPoint;
    boolean _returnAbrupt;

    private boolean c2j(final long cEnv) throws Exception {
      return this._hasDecimalPoint;
    }

    private java.lang.Float c2j1(final long cEnv) throws Exception {
      return Float.valueOf(this._input);
    }

    private java.lang.Integer c2j2(final long cEnv) throws Exception {
      return Integer.valueOf(this._input);
    }

    private native java.lang.Number j2c(final long cEnv);

    private void c2j3(final long cEnv) throws Exception {
      {
        System.out.println(this.j2c(cEnv));
      }
    }

    private native void j2c1();
    String []  _args;

    JavaEnvFor_main(String []  args) {
      this._returnAbrupt = false;
      this._args = args;

      {
        this._input = "12.34E1";
        this._hasDecimalPoint = -1 != this._input.indexOf('.');

        {
          this.j2c1();
          if (this._returnAbrupt)
            return;
        }
      }
    }
  }
}
