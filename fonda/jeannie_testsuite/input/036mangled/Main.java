class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    String []  _ja;
    boolean _returnAbrupt;

    private String []  c2j(final long cEnv) throws Exception {
      return this._ja;
    }

    private native void j2c();
    int _i;
    String []  _args;

    JavaEnvFor_main(String []  args) {
      this._returnAbrupt = false;
      this._args = args;

      {
        this._ja = new String[] {
          "!\n", "world", "Hello, "
        };

        {
          this.j2c();
          if (this._returnAbrupt)
            return;
        }

        for (this._i = 0; this._i < this._ja.length; this._i++)
          System.out.print(this._ja[this._i]);
      }
    }
  }
}
