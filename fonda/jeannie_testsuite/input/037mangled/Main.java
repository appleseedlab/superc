class Main {
  static {
    System.loadLibrary("Main");
  }

  public static void main(String []  args) {
    JavaEnvFor_main jEnv = new JavaEnvFor_main(args);
  }

  private static final class JavaEnvFor_main {
    int _x1;
    String _x2;

    JavaEnvFor_main(String[] args) {
      {
        this._x1 = 2;
        this._x1 += 1;
        this.j2c();
      }
      {
        this._x2 = "two";
        this._x2 += "one";
        System.out.println(this._x2);
      }
    }

    private int c2j() throws Exception {
      return this._x1;
    }

    private native int j2c();
  }
}
