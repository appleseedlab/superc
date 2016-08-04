class Main {
  static {
    System.loadLibrary("Main");
  }
  static void f(int[] ja) throws Exception {
    new JavaEnvFor_Main_f___3I(ja);
  }
  private static final class JavaEnvFor_Main_f___3I {
    int[] _ja ;
    JavaEnvFor_Main_f___3I(int[] ja) {
      this._ja = ja;
      j2c();
    }
    private int[] c2j(final long cEnv) throws Exception {
      return this._ja;
    }
    private void c2j1(final long cEnv) throws Exception {
      throw new Exception();
    }
    private native void j2c();
  }
  public static void main(String[] args) {
    int[] a  = { 3, 1, 4 };
    try{
      f(a);
      System.out.println("p3");
    } catch (Exception e) {
      System.out.println("p4");
    } 
  }
}
