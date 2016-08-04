import java.util.Vector;
public class CompoundData {
  static {System.loadLibrary("CompoundData");}
  public static void main(String[] args) {
    Vector strings = new Vector();
    strings.add("2.50290"); 
    strings.add("2.71828");
    strings.add("3.14159");
    strings.add("4.66920");
    double[] doubles = new double[strings.size()];
    doubles[0] = 3.48;
    parse(doubles.length, doubles, strings);
    for( int i = 0; i < doubles.length;i++)
      System.out.println(doubles[i]);
  }
  public static native void parse(int size, double[] doubles, Vector strings);
}
