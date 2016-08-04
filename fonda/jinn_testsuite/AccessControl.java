public class AccessControl {
  static {
    System.loadLibrary(AccessControl.class.getName());
  }
  public static void main(String[] args) {
    mutateString("Hello");
    System.out.println("Hello");
  }  
  public static native void mutateString(String s); 
}
