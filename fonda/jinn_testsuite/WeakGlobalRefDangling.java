import java.lang.reflect.Method;

public class WeakGlobalRefDangling {
  static {
    System.loadLibrary("WeakGlobalRefDangling");
  }
  public static void main(String[] args) {
    foo();
  }
  static native void foo();
}
