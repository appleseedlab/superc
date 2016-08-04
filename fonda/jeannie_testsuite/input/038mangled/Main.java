class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String[] args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    private java.lang.String c2j(final long cEnv) { return "hello"; }
    private java.lang.String c2j1(final long cEnv) { return "world"; }
    private java.lang.String c2j2(final long cEnv) { return "moon"; }

    private native void j2c();

    JavaEnvFor_main(String []  args) {
      this.j2c();
    }
  }
}
