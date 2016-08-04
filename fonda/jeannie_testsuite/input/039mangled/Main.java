import java.util.Random;

class Math {
  static {
    System.loadLibrary("Main");
  }
  public static double pow(double x, double y) {
    JavaEnvFor_pow jEnv = new JavaEnvFor_pow(x, y);
    return jEnv._returnResult;
  }
  private static final class JavaEnvFor_pow {
    double _x, _y;
    double _returnResult;
    private double getX() { return this._x; }
    private double getY() { return this._y; }
    private native void j2c();
    JavaEnvFor_pow(double x, double y) {
      this._x = x;
      this._y = y;
      this.j2c();
    }
  }
}

public class Main {
  public static void main(String []  args) {
    Random random = new Random(123);
    for (int i = 0; i < 3; i++) {
      double d = 100.0 * random.nextDouble();
      double r = Math.pow(d, 1.0 / 3.0);
      System.out.println("d " + d + " r " + r + " ^3 " + r * r * r);
    }
  }
}
