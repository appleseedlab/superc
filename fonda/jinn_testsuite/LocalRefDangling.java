import java.lang.reflect.Method;
import java.util.Vector;
public class LocalRefDangling {
  static {
    System.loadLibrary("LocalRefDangling");
    initNative();
  }
  public static void main(String[] args) {
    new LocalRefDangling().foo();
  }
  public static native void initNative();
  native void foo();
  void bar() {System.out.println("bar");}
}
