import java.lang.reflect.Method;
import java.util.Vector;
public class GlobalRefLeak {
  static {
    System.loadLibrary("GlobalRefLeak");
  }
  public static void main(String[] args) {
    foo();
  }
  static native void foo();
}
