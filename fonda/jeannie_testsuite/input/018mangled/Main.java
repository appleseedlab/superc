import java.lang.reflect.Method;

class Main {
  public static final int REPEAT = 100 * 1000;

  static {
    System.loadLibrary("Main");
  }

  static void report(long start, String name) {
    long end  = System.currentTimeMillis();
    System.err.println("mangled: time " + (end - start) + ", " + name);
  }

  public static void emptyCBlockInJava() {
    long n = REPEAT;
    long start = System.currentTimeMillis();
    for(long i=0; i < n; i++) {
      emptyCBlockInJava_j2c();
    }
    report(start, "emptyCBlockInJava");
  }
  static native void emptyCBlockInJava_j2c();

  public static void emptyJavaBlockInC() {
    long start = System.currentTimeMillis();
    emptyJavaBlockInC_j2c();
    report(start, "emptyJavaBlockInC");
  }
  static native void emptyJavaBlockInC_j2c();
  static void emptyJavaBlockInC_c2j() { }

  public static void constantCExpressionInJava() {
    long n = REPEAT;
    long start = System.currentTimeMillis();
    long s = 0;
    for (long i=0; i<n; i++)
      s += constantCExpressionInJava_j2c();
    if (n != s)
      System.out.println("error");
    report(start, "constantCExpressionInJava");
  }
  static native int constantCExpressionInJava_j2c();

  public static void constantJavaExpressionInC() {
    long start = System.currentTimeMillis();
    constantJavaExpressionInC_j2c();
    report(start, "constantJavaExpressionInC");
  }
  static int constantJavaExpressionInC_c2j() {
    return 1;
  }
  static native void constantJavaExpressionInC_j2c();

  public static void arrayReadAccess() {
    long start = System.currentTimeMillis();
    arrayReadAccess_j2c();
    report(start, "arrayReadAccess");
  }
  static native void arrayReadAccess_j2c();
  static int[] arrayReadAccess_c2j() {
    int[] a = new int[1000];
    for (int i=0; i<a.length; i++)
      a[i] = 1;
    return a;
  }

  public static void arrayWriteAccess() {
    int[] a = new int[1000];
    long start = System.currentTimeMillis();
    arrayWriteAccess_j2c(a);
    report(start, "arrayWriteAccess");
    for(int i=0; i<a.length; i++)
      if (1 != a[i]) System.out.println("error");
  }
  static native void arrayWriteAccess_j2c(int[] a);

  public static void exceptionJavaInCInJava() {
    long n = REPEAT;
    long start = System.currentTimeMillis();
    for (long i=0; i<n; i++) {
      try{
        exceptionJavaInCInJava_j2c();
      } catch (Exception e) {
        /* empty catch block */
      }
    }
    report(start, "exceptionJavaInCInJava");
  }
  static native void exceptionJavaInCInJava_j2c() throws Exception;
  static void exceptionJavaInCInJava_c2j() throws Exception {
    throw new Exception();
  }

  public static void main(String[] args) throws Exception {
    if (1 == args.length) {
      final Method m = Main.class.getMethod(args[0], (Class[])null);
      m.invoke(null, new Object[]{});
      return;
    }
    emptyCBlockInJava();
    System.gc();
    emptyJavaBlockInC();
    System.gc();
    constantCExpressionInJava();
    System.gc();
    constantJavaExpressionInC();
    System.gc();
    arrayReadAccess();
    System.gc();
    arrayWriteAccess();
    System.gc();
    exceptionJavaInCInJava();
  }
}
