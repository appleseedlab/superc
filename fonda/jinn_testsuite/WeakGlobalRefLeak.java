import java.lang.reflect.Method;

public class WeakGlobalRefLeak {
  static {
    System.loadLibrary("WeakGlobalRefLeak");
  }
  public static void main(String[] args) {
    foo();
  }
  static native void foo();
}
