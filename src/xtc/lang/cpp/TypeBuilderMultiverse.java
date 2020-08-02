package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;

import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.UnitT;
import xtc.Constants;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.lang.cpp.Multiverse.Element;

public class TypeBuilderMultiverse extends Multiverse<TypeBuilderUnit>
{
  static int count = 0;
  Integer personalCount;

  // creates a new typebuilder using a string (which is NOT a type)
  public TypeBuilderMultiverse(String name, PresenceCondition p)
  {
    super();
    contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(name), p));
  }

  // creates a new typebuilder using only a type
  public TypeBuilderMultiverse(Type type, PresenceCondition p)
  {
    super();
    personalCount = new Integer(count);
    count++;
    contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(type), p));
  }
    
  // copy constructor that changes type (should be used whenever a type is found)
  // the default constructor should be used before this ever gets called.
  public void addType(Type t)
  {
    
    for (Element<TypeBuilderUnit> e : contents)
	    {
        e.setData(new TypeBuilderUnit(e.getData(), t));
	    }
  }
    
  // sets all flags to false and type starts as unit
  public TypeBuilderMultiverse()
  {
    super();
  }

  // copy constructor creates a deep copy
  public TypeBuilderMultiverse(TypeBuilderMultiverse old)
  {
    super();
    for (Element<TypeBuilderUnit> e : old.contents)
	    {
        contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(e.getData()),e.getCondition()));
	    }
  }


  // TODO: replace with call to Multiverse.product
  public TypeBuilderMultiverse combine(TypeBuilderMultiverse with)
  {
    TypeBuilderMultiverse t = new TypeBuilderMultiverse();
    for (Element<TypeBuilderUnit> e : contents)
      for (Element<TypeBuilderUnit> f : with.contents)
        if (!e.getCondition().isMutuallyExclusive(f.getCondition()))
          t.contents.add(new Element<TypeBuilderUnit>(e.getData().combine(f.getData()),
                                                      e.getCondition().and(f.getCondition())));
    return t;
  }

  public void setSUE(String name, Multiverse<SymbolTable.Entry> unis, PresenceCondition p)
  {
    setFoundType(name, unis, p, false);
  }

  public void setTypedef(String name, Multiverse<SymbolTable.Entry> unis, PresenceCondition p)
  {
    setFoundType(name, unis, p, true);
  }
  
  // TODO: can this be replaced with a call to product?
  private void setFoundType(String name, Multiverse<SymbolTable.Entry> unis, PresenceCondition p,
                            boolean isTypedef)
  {
    List<Element<TypeBuilderUnit>> l = new LinkedList<Element<TypeBuilderUnit>>();
    if (contents.size() == 0) {
      contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(), p));
    }
    for (Element<SymbolTable.Entry> u : unis) {
	    for (Element<TypeBuilderUnit> e : contents) {
        if (!u.getCondition().isMutuallyExclusive(e.getCondition())) {
          TypeBuilderUnit t = new TypeBuilderUnit(e.getData());
          if (isTypedef) {
            t.setTypedef(name, u.getData().getRenaming(), u.getData().getType());
          }
          else if (u.getData().getType().isStruct()) {
            t.setStruct(name, u.getData().getRenaming(), u.getData().getType());
          }
          l.add(new Element<TypeBuilderUnit>(t, u.getCondition().and(e.getCondition()) ));
        }
      }
    }
    for (Element<TypeBuilderUnit> e : contents)
      {
        e.destruct();
      }
    contents = l;
  }

  public boolean getIsValid()
  {
    boolean vals = true;
    for (Element<TypeBuilderUnit> t : contents)
	    vals = vals &&t.getData().getIsValid();
    return vals;
  }

  // TODO: dead code?
  public List<Boolean> validDeclQuals()
  {
    List<Boolean> vals = new LinkedList<Boolean>();
    for (Element<TypeBuilderUnit> t : contents)
	    vals.add(new Boolean(t.getData().validDeclQuals()));
    return vals;
  }
  public String qualString()
  {
    return toString();
  }
  public TypeBuilderUnit getQualTU()
  {
    return contents.get(0).getData();
  }

  public String toString()
  {
    if (personalCount != null)
      return super.toString() + " " + personalCount.toString();
    return super.toString();
  }
}
