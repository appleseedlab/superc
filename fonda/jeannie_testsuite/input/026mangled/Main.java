class Main {
  static {
    System.loadLibrary("Main");
  }

  static void report(long start, String name) {
    long end = System.currentTimeMillis();
    System.err.println("mangled: time " + (end - start) + ", " + name);
  }

  static void culprit() {
    JavaEnvFor_culprit jEnv = new JavaEnvFor_culprit();
  }

  private static final class JavaEnvFor_culprit {
    long _start;
    boolean _returnAbrupt;

    private void c2j(final long cEnv) throws Exception {
    }

    private native void j2c();

    JavaEnvFor_culprit() {
      this._returnAbrupt = false;
      this._start = System.currentTimeMillis();
      this.j2c();
      if (this._returnAbrupt)
        return;
      report(this._start, "culprit");
    }
  }

  static void victim() {
    JavaEnvFor_victim jEnv = new JavaEnvFor_victim();
  }

  private static final class JavaEnvFor_victim {
    long _start1;
    int _i1;
    boolean _returnAbrupt1;

    private void c2j1(final long cEnv) throws Exception {
    }

    private native void j2c1();

    JavaEnvFor_victim() {
      this._returnAbrupt1 = false;
      this._start1 = System.currentTimeMillis();
      for (this._i1 = 0; this._i1 < 10000; this._i1++) {
        this.j2c1();
        if (this._returnAbrupt1)
          return;
      }
      report(this._start1, "victim");
    }
  }

  public static void main(String []  args) {
    victim();
    culprit();
    victim();
    System.err.println("returning from main ..."); System.err.flush();
  }
}
