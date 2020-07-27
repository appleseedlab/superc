package xtc.lang.cpp;

import xtc.type.Type;
import xtc.type.ErrorT;

import xtc.lang.cpp.Multiverse.Element;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

public class Parameter
{
  SymbolTable.Entry var;
  boolean ellipsis;

  public Parameter()
  {
    var = null;
    ellipsis = false;
  }

  public void setVar(SymbolTable.Entry s)
  {
    var = s;
    ellipsis = false;
  }

  public void setEllipsis()
  {
    ellipsis = true;
    var = null;
  }

  public SymbolTable.Entry getVar()
  {
    return var;
  }

  public boolean isEllipsis()
  {
    return ellipsis;
  }

  public Type getType()
  {
    if (ellipsis)
      return new ErrorT();
    return var.getType();
  }

  public String toString()
  {
    if (ellipsis)
      return "...";
    else
      return var.toString();
  }

  public boolean isVoid()
  {
    if (ellipsis) {
      return false;
    }
    return var.getType().isVoid();
  }
  
  /**
   * Returns if a type is valid for a parameter. If this statement
   * is called, it is assumed that it is not the sole element of a
   * list. If there is more than one possible entry in the multiverse
   * then this was called incorrectly and returns false. A type should
   * be valid provided it is not void, uninitialized, or an error.
   *
   * @return if the parameter type is valid in a list
   */
  public boolean isValidType()
  {
    if (ellipsis) {
      return true;
    }
    Type t = var.getType();
    return !t.isVoid() && !t.isUnit() && !t.isError();
    
  }
}
