import java.lang.reflect.Method;
import java.util.Vector;
public class LocalRefOverflow {
  static {
    System.loadLibrary("LocalRefOverflow");
  }
  public static void main(String[] args) {
    foo(new Vector<String>());
  }
  static native void foo(Vector v);
}
