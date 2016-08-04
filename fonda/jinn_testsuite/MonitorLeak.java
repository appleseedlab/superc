public class MonitorLeak {
  static {
    System.loadLibrary("MonitorLeak");
  }
  public static void main(String[] args) {
    foo();
  }
  public static native void foo();
}
