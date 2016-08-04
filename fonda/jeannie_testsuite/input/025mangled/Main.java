class Main {
  static { System.loadLibrary("Main"); }

  static native void j2c();

  public static void main(String[] args) {
    for(int i=0; i < 2; i++)
      j2c();
  }
}
