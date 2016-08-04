class Main {
  static {
    System.loadLibrary("Main");
  }

  static int replace(char []  chars, char oldC, char newC) {
    JavaEnvFor_replace jEnv = new JavaEnvFor_replace(chars, oldC, newC);

    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_replace {
    char []  _chars;
    boolean _returnAbrupt;

    private int c2j(final long cEnv) throws Exception {
      return this._chars.length;
    }

    char _oldC;

    private char c2j1(final long cEnv) throws Exception {
      return this._oldC;
    }

    private native int j2c(final long cEnv);

    private char c2j2(final long cEnv) throws Exception {
      return this._chars[this.j2c(cEnv)];
    }

    private native int j2c1(final long cEnv);
    char _newC;

    private char c2j3(final long cEnv) throws Exception {
      return this._chars[this.j2c1(cEnv)] = this._newC;
    }

    int _returnResult;
    private native void j2c2();

    JavaEnvFor_replace(char []  chars, char oldC, char newC) {
      this._returnAbrupt = false;
      this._chars = chars;
      this._oldC = oldC;
      this._newC = newC;

      {
        this.j2c2();
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
