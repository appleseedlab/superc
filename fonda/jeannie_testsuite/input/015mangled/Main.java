class Main {
  static {
    System.loadLibrary("Main");
  }
  public static void main(String[] args) {
    new JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(args);
  }
  private static final class JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2 {
    boolean _returnAbrupt;
    String[] _args ;
    JavaEnvFor_Main_main___3Ljava_0002flang_0002fString_2(String[] args) {
      this._returnAbrupt = false;
      this._args = args;
      System.out.println("J1");
      j2c();
      if (this._returnAbrupt)
        return;
      System.out.println("J3");
    }
    private void c2j(final long cEnv) throws Exception {
      System.out.println("J2");
      this._returnAbrupt = true;
      return;
    }
    private native void j2c();
  }
}
