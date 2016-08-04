class Main {
  static  {
    System.loadLibrary("Main");
  }
  native static void foo();
  public static void main(final String[] args) {
    foo();
  }
}
