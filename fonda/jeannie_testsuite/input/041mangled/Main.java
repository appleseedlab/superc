class Main {
  static {
    System.loadLibrary("Main");
  }
  public static void main(String[] args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main();
  }
  private static final class JavaEnvFor_main {
    private native int j2c();
    JavaEnvFor_main() {
      this.j2c();
    }
  }
}
