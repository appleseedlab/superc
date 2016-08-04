import java.io.UnsupportedEncodingException;

class Main {
  static {
    System.loadLibrary("Main");
  }

  static int utf16LengthJava(final String s) {
    return s.length();
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

  static int utf16LengthNative(final String s) {
    JavaEnvFor_utf16LengthNative jEnv = new JavaEnvFor_utf16LengthNative(s);
    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_utf16LengthNative {
    java.lang.String _s;
    private int c2j(final int cEnv) throws Exception {
      return this._s.length();
    }
    int _returnResult;
    private native void j2c();
    JavaEnvFor_utf16LengthNative(final String s) {
      this._s = s;
      this.j2c();
    }
  }

  static int utf8LengthNative(final String s) {
    JavaEnvFor_utf8LengthNative jEnv = new JavaEnvFor_utf8LengthNative(s);
    return jEnv._returnResult1;
  }

  private static final class JavaEnvFor_utf8LengthNative {
    java.lang.String _s1;
    private java.lang.String c2j1(final int cEnv) throws Exception {
      return this._s1;
    }
    int _returnResult1;
    private native void j2c1();
    JavaEnvFor_utf8LengthNative(final String s) {
      this._s1 = s;
      this.j2c1();
    }
  }

  public static void main(String[] args) {
    final String s = "Sch\u00F6ne Gr\u00FC\u00DFe!";
    System.out.println(s);
    System.out.println("UTF16 length (Java)  : " + utf16LengthJava(s));
    System.out.println("UTF8  length (Java)  : " + utf8LengthJava(s));
    System.out.println("UTF16 length (native): " + utf16LengthNative(s));
    System.out.println("UTF8  length (native): " + utf8LengthNative(s));
  }
}
