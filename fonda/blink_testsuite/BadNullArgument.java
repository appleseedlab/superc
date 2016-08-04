public class BadNullArgument {
  static {
    System.loadLibrary(BadNullArgument.class.getName());
  }
  public static void main(String[] args) {
    String s = foo();
    System.out.printf("The result is %s.\n", s);
  }
  public static native String foo();
}
