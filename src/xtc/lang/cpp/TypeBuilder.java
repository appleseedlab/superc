package xtc.lang.cpp;
import java.util.LinkedList;
import java.util.List;
import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.UnitT;
import xtc.type.TypedefT;
import xtc.Constants;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.lang.cpp.Multiverse.Element;

public class TypeBuilder extends Multiverse<TypeBuilderUnit>
{
  static int count = 0;
  Integer personalCount;;
  public List<Type> toType() {
    List<Type> types = new LinkedList<Type>();
    for (Element<TypeBuilderUnit> t : contents)
	    types.add(t.getData().toType());
    return types;	
  }
    
  public List<PresenceCondition> getConditions()
  {	
    List<PresenceCondition> conds = new LinkedList<PresenceCondition>();
    for (Element<TypeBuilderUnit> e : contents)
	    conds.add(e.getCondition());
    return conds;
  }

    
  public void addSpec(String name)
  {
    for (Element<TypeBuilderUnit> e : contents)
	    {
        e.setData(new TypeBuilderUnit(e.getData(), name));
	    }
  }

  // creates a new typebuilder using a string (which is NOT a type)
  public TypeBuilder(String name, PresenceCondition p)
  {
    super();
    contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(name), p));
  }

  // creates a new typebuilder using only a type
  public TypeBuilder(Type type, PresenceCondition p)
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
  public TypeBuilder()
  {
    super();
  }

  // copy constructor creates a deep copy
  public TypeBuilder(TypeBuilder old)
  {
    super();
    for (Element<TypeBuilderUnit> e : old.contents)
	    {
        contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(e.getData()),e.getCondition()));
	    }
  }


  public TypeBuilder combine(TypeBuilder with)
  {
    TypeBuilder t = new TypeBuilder();
    for (Element<TypeBuilderUnit> e : contents)
      for (Element<TypeBuilderUnit> f : with.contents)
        if (!e.exclusiveFrom(f.getCondition()))
          t.contents.add(new Element<TypeBuilderUnit>(e.getData().combine(f.getData()),
                                                      e.getCondition().and(f.getCondition())));
    return t;
  }

  public List<Boolean> isTypeDef()
  {
    List<Boolean> vals = new LinkedList<Boolean>();
    for (Element<TypeBuilderUnit> t : contents)
	    vals.add( new Boolean(t.getData().isTypeDef()));
    return vals;
  }

  public void setTypedef(String name, Multiverse<Universe> unis, PresenceCondition p)
  {
    //At this point, you can't actually have more than one
    //typedef and typedef is the only source of
    //explosion in a decl. builders.size SHOULD always be 1,
    //but we will create a cross product regardless
    List<Element<TypeBuilderUnit>> l = new LinkedList<Element<TypeBuilderUnit>>();
    if (contents.size() == 0)
	    {
        contents.add(new Element<TypeBuilderUnit>(new TypeBuilderUnit(), p));
	    }
    for (Element<Universe> u : unis)
	    for (Element<TypeBuilderUnit> e : contents)
        {
          if (!u.exclusiveFrom(e.getCondition()))
            {
              TypeBuilderUnit t = new TypeBuilderUnit(e.getData());
              t.setTypedef(name, u.getData().getRenaming(), u.getData().getType());
              l.add(new Element<TypeBuilderUnit>(t, u.getCondition().and(e.getCondition()) ));
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
