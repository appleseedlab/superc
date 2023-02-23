package xtc.type;

public class TypeString {

  public String retType; 
  public String declPre; 
  public String declPost; 
  public String corePost; 
  public String id;
  public boolean inReturn;
  
  public TypeString() {
    retType = "";
    declPre = "";
    declPost = "";
    corePost = "";
    id = "";
    inReturn = false;
  }

  public void addToFront(String s) {
    if (inReturn) {
      retType = retType + s; 
    } else {
      declPre = declPre + s;
    }
  }

  public void addArray() {
    if (inReturn) {
      corePost = "[]" + corePost;
    } else {
      declPre = "(" + declPre;
      declPost = declPost + ")[]";
    }
  }
  
  public void addArray(long l) {
    if (inReturn) {
      corePost = "[" + String.valueOf(l) + "]" + corePost;
    } else {
      declPre = "(" + declPre;
      declPost = declPost + ")[" + String.valueOf(l) + "]";
    }
  }

  public String toString() {
    if (!retType.equals(""))
      return retType + "(" + declPre + id + declPost + ")" + corePost;
    return declPre + id + declPost + corePost;
  }
}
