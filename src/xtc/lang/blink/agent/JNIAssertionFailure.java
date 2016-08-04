package xtc.lang.blink.agent;

/**
 * @author Byeongcheol Lee
 */
class JNIAssertionFailure extends Error {
  private JNIAssertionFailure() {super();}
  
  public JNIAssertionFailure(String msg) {
    super(msg);
  }
  public JNIAssertionFailure(String msg, Throwable pendingException) {
    super(msg, pendingException);
  }
  public static void assertFail(String msg) {
    throw new JNIAssertionFailure(msg);
  }
  public static void assertFail(String msg, Throwable pendingException) {
    throw new JNIAssertionFailure(msg, pendingException);
  }
}
