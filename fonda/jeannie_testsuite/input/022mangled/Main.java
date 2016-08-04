class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String[] args) {
JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2    jEnv = new JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(args);
  }

  private static final class JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
    java.lang.String _js;
    boolean _returnAbrupt;

    private String c2j(final long cEnv) throws Exception {
      return this._js;
    }

    private int c2j1(final long cEnv) throws Exception {
      return this._js.length();
    }

    private native void j2c();
    String[] _args;

    JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(String[] args) {
      this._returnAbrupt = false;
      this._args = args;

      {
        {
          this._js = "abc";
        }
         {
          this.j2c();
          if (this._returnAbrupt)
            return;
        }
      }
    }
  }
}
