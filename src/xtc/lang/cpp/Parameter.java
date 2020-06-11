package xtc.lang.cpp;

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
}
