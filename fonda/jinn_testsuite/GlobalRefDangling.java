import java.lang.reflect.Method;
import java.util.Vector;
public class GlobalRefDangling {
  static {
    System.loadLibrary("GlobalRefDangling");
  }
  public static void main(String[] args) {
    foo();
  }
  static native void foo();
}
