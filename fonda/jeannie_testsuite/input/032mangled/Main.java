class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String[] args) {
    j2c();
  }

  static native void j2c();
}
