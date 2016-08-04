import java.lang.reflect.Method;
public class FixedTyping {
  static {
    System.loadLibrary("FixedTyping");
  }  
  public static void main(String[] args) throws Exception {
    new FixedTyping().foo();
  }
  final int number = 7;
  public native void foo();

}
