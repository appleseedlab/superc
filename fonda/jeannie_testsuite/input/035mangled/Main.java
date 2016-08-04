class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    java.lang.String _s;
    boolean _returnAbrupt;

    private java.lang.String c2j(final long cEnv) throws Exception {
      return this._s;
    }

    private java.lang.String c2j1(final long cEnv) throws Exception {
      return this._s;
    }

    private native void j2c();
    String []  _args;

    JavaEnvFor_main(String []  args) {
      this._returnAbrupt = false;
      this._args = args;

      {
        this._s = "Sch\u00F6ne Gr\u00FC\u00DFe!";

        {
          this.j2c();
          if (this._returnAbrupt)
            return;
        }
      }
    }
  }
}
