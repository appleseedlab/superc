package xtc.lang.cpp;

import xtc.type.Type;
import xtc.type.ErrorT;

import xtc.lang.cpp.Multiverse.Element;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

public class Parameter
{
  Multiverse<SymbolTable.Entry> multiverse;
  boolean ellipsis;

  public Parameter()
  {
    multiverse = null;
    ellipsis = false;
  }

  public void setMultiverse(Multiverse<SymbolTable.Entry> m)
  {
    multiverse = m;
    ellipsis = false;
  }

  public void setEllipsis()
  {
    ellipsis = true;
    multiverse = null;
  }

  public Multiverse<SymbolTable.Entry> getMultiverse()
  {
    return multiverse;
  }

  public boolean isEllipsis()
  {
    return ellipsis;
  }

  public PresenceCondition getGap(PresenceCondition pc)
  {
    PresenceCondition p = pc;
    for (Element<SymbolTable.Entry> e : multiverse)
      {
        p = p.andNot(e.getCondition());
      }
    return p;
  }

  public Type getType()
  {
    if (ellipsis || multiverse.size() != 1)
      return new ErrorT();
    return multiverse.get(0).getData().getType();
  }

  public String toString()
  {
    if (ellipsis)
      return "...";
    else
      return multiverse.toString();
  }

  public boolean isVoid()
  {
    if (ellipsis || multiverse.size() != 1) {
      return false;
    }
    return multiverse.get(0).getData().getType().isVoid();
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
    if ( multiverse.size() != 1) {
      return false;
    }
    Type t = multiverse.get(0).getData().getType();
    System.err.println(t.toString());
    return !t.isVoid() && !t.isUnit() && !t.isError();
    
  }
}
