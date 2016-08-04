import java.io.PrintWriter;

class Main {
  static {
    System.loadLibrary("Main");
  }

  static PrintWriter goodGlob;

  static void setGlob(boolean beGood, PrintWriter init) {
    JavaEnvFor_setGlob jEnv = new JavaEnvFor_setGlob(beGood, init);
  }
  private static final class JavaEnvFor_setGlob {
    boolean _beGood;
    java.io.PrintWriter _init;
    private boolean c2j() {
      return this._beGood;
    }
    private java.io.PrintWriter c2j1() {
      return Main.goodGlob = this._init;
    }
    private java.io.PrintWriter c2j2() {
      return this._init;
    }
    private native void j2c();
    JavaEnvFor_setGlob(boolean beGood, PrintWriter init) {
      this._beGood = beGood;
      this._init = init;
      this.j2c();
    }
  }

  static PrintWriter getGlob(boolean beGood) {
    JavaEnvFor_getGlob jEnv = new JavaEnvFor_getGlob(beGood);
    return jEnv._returnResult;
  }
  private static final class JavaEnvFor_getGlob {
    boolean _beGood1;
    java.io.PrintWriter _returnResult;
    private boolean c2j3() {
      return this._beGood1;
    }
    private java.io.PrintWriter c2j4() {
      return Main.goodGlob;
    }
    private native void j2c1();
    JavaEnvFor_getGlob(boolean beGood) {
      this._beGood1 = beGood;
      this.j2c1();
    }
  }

  static void useGlob(boolean beGood, Object obj) {
    JavaEnvFor_useGlob jEnv = new JavaEnvFor_useGlob(beGood, obj);
  }
  private static final class JavaEnvFor_useGlob {
    boolean _beGood2;
    java.io.PrintWriter _out;
    java.lang.Object _obj;
    private void c2j5() {
      this._out = Main.getGlob(this._beGood2);
      this._out.println(this._obj);
      this._out.flush();
    }
    private native void j2c2();
    JavaEnvFor_useGlob(boolean beGood, Object obj) {
      this._beGood2 = beGood;
      this._obj = obj;
      this.j2c2();
    }
  }

  public static void main(String[] args) {
    boolean beGood = true;
    setGlob(beGood, new PrintWriter(System.out));
    for (int i = 0; i < 3; i++) {
      useGlob(beGood, "o_" + i);
      System.gc();
    }
  }
}
