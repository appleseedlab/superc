public abstract class PingPong {
  static {System.loadLibrary("PingPong");}
  public static void main(String[] args) {
    jPing(3);
  }
  static int jPing(int i) {
    System.out.println("jPing: " + i );
    if (i > 0 )
      cPong(i-1);
    return i;
  }
  native static void cPong(int i);
}
