public class ExceptionState {
  static {System.loadLibrary("ExceptionState");}
  public static void main(String[] args) {
    ExceptionState check = new ExceptionState();
    check.call();
  }
  public void foo() {
    System.out.println("foo");
    throw new RuntimeException("checked by native code");
  }
  public void bar() {
    System.out.println("bar");
  }
  public native void call(); 
}
