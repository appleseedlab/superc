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
    if (inReturn) {
      retType = s + " " + retType;
    } else {
      coreType += " " + s;
    }
  }
  
  public void addToFront(String s) {
    if (inReturn) {
      retType = retType + " " + s; 
    } else {
      declPre = s + " " + declPre;
    }
  }

  public void addArray(Type t) {
    addArray("",t);
  }
  
  public void addArray(String s, Type t) {
    declPost += "[" + s + "]";
  }

  public void addPointer(String s, Type t) {
    if (inReturn) {
      retType = s + " " + retType;
    } else if (t.isArray()) {
      declPre = "(" + s + " " + declPre;
      declPost += ")";
    } else {
      declPre = s + " " + declPre;
    }
  }
  
  public void addAttribute(String s, Type t) {
    if (t.isPointer()) {
      addPointer("* " + s, t.toPointer().getType());
    } else {
      coreType = s + " " + coreType;
    }
  }
  
  public String toString() {
    if (!retType.equals("") && !id.equals("")) {
      declPre = "(" + declPre;
      declPost += ")";
    }
    return coreType + " " + retType + " " + declPre + id + declPost + " " + corePost;
  }
}
