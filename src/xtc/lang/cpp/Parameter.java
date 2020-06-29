package xtc.lang.cpp;

import xtc.type.Type;

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
      return null;
    return multiverse.get(0).getData().getType();
  }

  public String toString()
  {
    if (ellipsis)
      return "...";
    else
      return multiverse.toString();
  }
}
