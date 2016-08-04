class Main {
  static {
    System.loadLibrary("Main");
  }

  static int f(int[] ja) {
    JavaEnvFor_Main_f___3I jEnv  = new JavaEnvFor_Main_f___3I(ja);
    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_Main_f___3I {
    JavaEnvFor_Main_f___3I(int[] ja) {
      this._returnAbrupt = false;
      this._ja = ja;
      j2c();
      if (this._returnAbrupt)
        return;
    }

    int[] _ja ;
    boolean _returnAbrupt ;

    private int c2j(final long cEnv) throws Exception {
      return this._ja.length;
    }

    private int[] c2j1(final long cEnv) throws Exception {
      return this._ja;
    }

    int _returnResult ;
    private native void j2c();
  }

  public static void main(String[] args) {
    int[] a  = {
      3, 1, 0, 4
    };
    int i  = f(a);
    System.out.println("result " + i);
  }
}
