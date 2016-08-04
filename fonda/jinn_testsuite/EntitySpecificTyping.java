import java.lang.reflect.Method;
public class EntitySpecificTyping {
  static {
    System.loadLibrary("EntitySpecificTyping");
  }  
  public static void main(String[] args) throws Exception {
    EntitySpecificTyping e = new EntitySpecificTyping();
    e.foo();
    System.gc();
    System.out.println(e.obj);
  }

  Object obj;

  private native void foo();
}
