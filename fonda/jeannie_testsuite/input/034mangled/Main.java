import java.io.UnsupportedEncodingException;

class Main {
  static {
    System.loadLibrary("Main");
  }

  static int substringUtf8LengthNative(final String s, final int start, final int length) {
    JavaEnvFor_substringUtf8LengthNative jEnv = new JavaEnvFor_substringUtf8LengthNative(s, start, length);

    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_substringUtf8LengthNative {
    java.lang.String _s;
    private java.lang.String c2j(final int cEnv) throws Exception {
      return this._s;
    }
    int _start;
    private int c2j1(final int cEnv) throws Exception {
      return this._start;
    }
    int _length;
    private int c2j2(final int cEnv) throws Exception {
      return this._length;
    }
    int _returnResult;
    private native void j2c();
    JavaEnvFor_substringUtf8LengthNative(final String s, final int start, final int length) {
      this._s = s;
      this._start = start;
      this._length = length;
      this.j2c();
    }
  }

  static int utf8LengthJava(final String s) {
    try {
      final byte[] utf8 = s.getBytes("UTF-8");
      return utf8.length;
    } catch (final UnsupportedEncodingException e) {
      System.err.println(e);
    }
    throw new Error();
  }

  public static void main(String[] args) {
    final String s = "Sch\u00F6ne Gr\u00FC\u00DFe!";
    for (int start=0; start<s.length(); start++) {
      for (int length=1; length<=s.length()-start; length++) {
        final String sub = s.substring(start, start + length);
        final int jl = utf8LengthJava(sub);
        final int nl = substringUtf8LengthNative(s, start, length);
        if (jl != nl)
          System.out.print("mistake: ");
        System.out.println("|" + sub + "| ==n " + nl + " ==j " + jl);
      }
    }
  }
}
