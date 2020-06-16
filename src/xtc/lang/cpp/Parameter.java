package xtc.lang.cpp;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.lang.cpp.Multiverse.Element;
import xtc.type.Type;

public class Parameter
{
  Multiverse<Universe> multiverse;
  boolean ellipsis;

  public Parameter()
  {
    multiverse = null;
    ellipsis = false;
  }

  public void setMultiverse(Multiverse<Universe> m)
  {
    multiverse = m;
    ellipsis = false;
  }

  public void setEllipsis()
  {
    ellipsis = true;
    multiverse = null;
  }

  public Multiverse<Universe> getMultiverse()
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
    for (Element<Universe> e : multiverse)
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
}
