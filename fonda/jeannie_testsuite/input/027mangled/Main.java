/* call from a top-level C function to Java */
class JavaEnvForF {
  private void callMainG() {
    Main.g();
  }
}

class Main {
  static {
    System.loadLibrary("Main");
    onLoad();
  }
  static void g() {
    System.out.println("Main.g"); System.out.flush();
  }
  static native void callF();
  static native void onLoad();
  public static void main(String[] args) {
    System.out.println("Main.main 1"); System.out.flush();
    callF();
    System.out.println("Main.main 2"); System.out.flush();
  }
}
