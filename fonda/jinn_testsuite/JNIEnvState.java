public class JNIEnvState extends Thread {
  static {
    System.loadLibrary("JNIEnvState");
  }
  public static void main(String[] args) throws Exception {
    JNIEnvState t = new JNIEnvState();
    t.workInMainThread();
    t.start();
    t.join();
  }
  public void run() {
    workInMyThread();
  }
  public native void workInMainThread();
  public native void workInMyThread();
}
