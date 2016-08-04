class Main {
  static {
    System.loadLibrary("Main");
  }

  static int replace(char []  chars, char oldC, char newC) {
    JavaEnvFor_replace jEnv = new JavaEnvFor_replace(chars, oldC, newC);

    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_replace {
    char _oldC;
    boolean _returnAbrupt;

    private char c2j(final long cEnv) throws Exception {
      return this._oldC;
    }

    char _newC;

    private char c2j1(final long cEnv) throws Exception {
      return this._newC;
    }

    char []  _chars;

    private int c2j2(final long cEnv) throws Exception {
      return this._chars.length;
    }

    private char []  c2j3(final long cEnv) throws Exception {
      return this._chars;
    }

    private char []  c2j4(final long cEnv) throws Exception {
      return this._chars;
    }

    int _returnResult;
    private native void j2c();

    JavaEnvFor_replace(char []  chars, char oldC, char newC) {
      this._returnAbrupt = false;
      this._chars = chars;
      this._oldC = oldC;
      this._newC = newC;

      {
        this.j2c();
        if (this._returnAbrupt)
          return;
      }
    }
  }

  public static void main(String []  args) {
    char []  a = {
      'a', 'b', 'c'
    };

    int r;

    r = replace(a, 'b', 'd');
    System.out.println(r + "  " + new String(a));
    r = replace(a, 'b', 'd');
    System.out.println(r + "  " + new String(a));
  }
}
