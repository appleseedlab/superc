public class BadErrorChecking {
  static {System.loadLibrary("BadErrorChecking");}
  public static void main(String[] args) {
    BadErrorChecking check = new BadErrorChecking();
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
