class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String[] args) {
    f(0);
  }

  static void f(int x) {
    new JavaEnvFor_Main_f__I(x);
  }
  private static final class JavaEnvFor_Main_f__I {
    int _x, _z;
    JavaEnvFor_Main_f__I(int x) {
      this._x = x;
      m1();
    }
    private native void m1();
    private void m2(final long cEnv) throws Exception {
      this._z = 1 + m3(cEnv);
      System.out.println(this._x);
      System.out.println(this._z);
    }
    private native int m3(final long cEnv);
    private int m4(final long cEnv) throws Exception {
      return this._x = 1;
    }
  }
}
