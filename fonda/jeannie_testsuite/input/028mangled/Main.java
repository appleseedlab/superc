/* call from a top-level C function to Java */
class JavaEnvForF {
  private void callMainG(long cEnv) {
    Main.g(retrieveX(cEnv));
  }
  private native int retrieveX(long cEnv);
}

class Main {
  static {
    System.loadLibrary("Main");
    onLoad();
  }
  static void g(int y) {
    System.out.println("Main.g(" + y + ")"); System.out.flush();
  }
  static native void callF();
  static native void onLoad();
  public static void main(String[] args) {
    System.out.println("Main.main() 1"); System.out.flush();
    callF();
    System.out.println("Main.main() 2"); System.out.flush();
  }
}
