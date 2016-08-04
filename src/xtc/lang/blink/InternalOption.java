package xtc.lang.blink;

/**
 * A Blink internal debugger options.
 */
class InternalOption {
  /** Check JNI misuse errors. */
  private boolean jniAssert = false;
  
  private String agentPath = null;
  
  public final boolean hasJniCheck() {
    return jniAssert ;
  }

  public final void setJniCheck(boolean jniCheck) {
    this.jniAssert = jniCheck;
  }

  public final void setAgentPath(String agentPath) {
    this.agentPath = agentPath;
  }
  
  public final String getAgentPath() {
    return this.agentPath;
  }
}
