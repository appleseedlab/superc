class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String[] args) {
    JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2 jEnv =
      new JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(args);
  }

  private static final class JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
    boolean _returnAbrupt;

    private java.lang.String c2j(final long cEnv) throws Exception {
      return "abc";
    }

    private native void j2c();

    JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(String[] args) {
      this._returnAbrupt = false;
      this.j2c();
    }
  }
}
