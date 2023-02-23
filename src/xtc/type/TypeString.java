package xtc.type;

public class TypeString {

  public String coreType;
  public String retType; 
  public String declPre; 
  public String declPost; 
  public String corePost; 
  public String id;
  public boolean inReturn;
  public int wrap;
  
  public TypeString() {
    coreType = "";
    retType = "";
    declPre = "";
    declPost = "";
    corePost = "";
    id = "";
    inReturn = false;
    wrap = 0;
  }

  public void setCore(String s) {
    coreType = s;
  }
  
  public void addToFront(String s) {
    if (inReturn) {
      retType = retType + " " + s; 
    } else {
      declPre = declPre + " " + s;
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

  public void addAttribute(String s) {
    if (wrap > 0) {
      addToFront(s);
    }else {
      coreType = s + coreType;
    }
  }
  
  public String toString() {
      return coreType + " " + retType + "(" + declPre + id + declPost + ")" + corePost;
      //return declPre + id + declPost + corePost;
  }
}
