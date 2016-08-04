public class CriticalSectionState {
  static {System.loadLibrary("CriticalSectionState");}
  public static void main(String[] args) {
    cfoo("critical");
  }
  public static void jbar() {
    System.out.println("jbar");
  }
  public static native void cfoo(String s);
}
