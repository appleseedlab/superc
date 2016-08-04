import java.io.IOException;

class StdIO {
  static {
    System.loadLibrary("Main");
  }

  public static long stdOut() {
    JavaEnvFor_stdOut jEnv = new JavaEnvFor_stdOut();
    return jEnv._returnResult;
  }

  private static final class JavaEnvFor_stdOut {
    boolean _returnAbrupt;
    long _returnResult;
    private native void j2c();
    JavaEnvFor_stdOut() {
      this._returnAbrupt = false;
      this.j2c();
    }
  }

  public static void fputs(String s, long stream) throws IOException {
    JavaEnvFor_fputs jEnv = new JavaEnvFor_fputs(s, stream);
  }

  private static final class JavaEnvFor_fputs {
    java.lang.String _s;
    boolean _returnAbrupt1;
    long _stream;

    private java.lang.String c2j(final long cEnv) throws Exception {
      return this._s;
    }
    private java.lang.String c2j1(final long cEnv) throws Exception {
      return this._s;
    }
    private int c2j2(final long cEnv) throws Exception {
      return this._s.length();
    }
    private long c2j3(final long cEnv) throws Exception {
      return this._stream;
    }
    private void c2j4(final long cEnv) throws Exception {
      throw new IOException(this.j2c1(cEnv));
    }
    private native java.lang.String j2c1(final long cEnv);
    private native void j2c2();

    JavaEnvFor_fputs(String s, long stream) {
      this._returnAbrupt1 = false;
      this._s = s;
      this._stream = stream;
      this.j2c2();
    }
  }

  public static void fflush(long stream) throws IOException {
    JavaEnvFor_fflush jEnv = new JavaEnvFor_fflush(stream);
  }

  private static final class JavaEnvFor_fflush {
    long _stream1;
    boolean _returnAbrupt2;

    private long c2j5(final long cEnv) throws Exception {
      return this._stream1;
    }
    private void c2j6(final long cEnv) throws Exception {
      throw new IOException(this.j2c3(cEnv));
    }
    private native java.lang.String j2c3(final long cEnv);
    private native void j2c4();

    JavaEnvFor_fflush(long stream) {
      this._returnAbrupt2 = false;
      this._stream1 = stream;
      this.j2c4();
    }
  }
}

public class Main {
  public static void main(String []  args) throws IOException {
    StdIO.fputs("Sch\u00F6ne Gr\u00FC\u00DFe!", StdIO.stdOut());
    StdIO.fflush(StdIO.stdOut());
  }
}
