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

public class TypeBuilder
{
    List<TypeBuilderUnit> builders;
    List<PresenceCondition> conditions;
    

    public String toString()
    {
	String output = "";
        for (int i = 0; i < builders.size(); ++i)
	    {
		output += builders.get(i).toString() + "{" + conditions.get(i).toString() + "}";
		if (i < builders.size() - 1)
		    output += "/";
	    }
	return output;
    }
    
    public List<Type> toType() {
	List<Type> types = new LinkedList<Type>();
	for (TypeBuilderUnit t : builders)
	    types.add(t.toType());
	return types;	
    }
    public List<PresenceCondition> getConditions()
    {	
	List<PresenceCondition> conds = new LinkedList<PresenceCondition>();
	for (PresenceCondition p : conditions)
	    conds.add(p);
	return conds;
    }

    
    public TypeBuilder(TypeBuilder old, String name)
    {
	builders = new LinkedList<TypeBuilderUnit>();
	for (TypeBuilderUnit t : old.builders)
	    builders.add(new TypeBuilderUnit(t, name));
	conditions = new LinkedList<PresenceCondition>();
	for (PresenceCondition p : old.conditions)
	    conditions.add(p);
    }

    // creates a new typebuilder using a string (which is NOT a type)
    public TypeBuilder(String name, PresenceCondition p)
    { 
	builders = new LinkedList<TypeBuilderUnit>();
	builders.add(new TypeBuilderUnit(name));
	conditions = new LinkedList<PresenceCondition>();
	conditions.add(p);
    }

    // creates a new typebuilder using only a type
    public TypeBuilder(Type type, PresenceCondition p)
    { 
	builders = new LinkedList<TypeBuilderUnit>();
	builders.add(new TypeBuilderUnit(type));
	conditions = new LinkedList<PresenceCondition>();
	conditions.add(p);
    }

    // copy constructor that changes type (should be used whenever a type is found)
    // the default constructor should be used before this ever gets called.
    public TypeBuilder(TypeBuilder old, Type type) 
    {
	builders = new LinkedList<TypeBuilderUnit>();
	for (TypeBuilderUnit t : old.builders)
	    builders.add(new TypeBuilderUnit(t, type));
	conditions = new LinkedList<PresenceCondition>();
	for (PresenceCondition p : old.conditions)
	    conditions.add(p);
    }
    // sets all flags to false and type starts as unit
    public TypeBuilder()
    {
        builders = new LinkedList<TypeBuilderUnit>();
	conditions = new LinkedList<PresenceCondition>();
    }

    // copy constructor creates a deep copy
    public TypeBuilder(TypeBuilder old)
    {
	builders = new LinkedList<TypeBuilderUnit>();
	for (TypeBuilderUnit t : old.builders)
	    builders.add(new TypeBuilderUnit(t));
	conditions = new LinkedList<PresenceCondition>();
	for (PresenceCondition p : old.conditions)
	    conditions.add(p);
    }


    public TypeBuilder combine(TypeBuilder with)
    {
	TypeBuilder t = new TypeBuilder();
	for (int i = 0; i < builders.size(); ++i)
		if (builders.get(i) != null)
		    for (int j = 0; j < with.builders.size(); ++j)
			if (with.builders.get(j) != null)
			    if (!conditions.get(i).isMutuallyExclusive(with.conditions.get(j)))
				{
				    t.builders.add(builders.get(i).combine(with.builders.get(j)));
				    t.conditions.add(conditions.get(i).and(with.conditions.get(j)));
				}
	return t;
    }

    public List<Boolean> isTypeDef()
    {
	List<Boolean> vals = new LinkedList<Boolean>();
	for (TypeBuilderUnit t : builders)
	    vals.add( new Boolean(t.isTypeDef()));
	return vals;
    }

    public void setTypedef(String name, List<Universe> unis)
    {
	//At this point, you can't actually have more than one
	//typedef and typedef is the only source of
	//explosion in a decl. builders.size SHOULD always be 1,
	//but we will create a cross product regardless
	List<TypeBuilderUnit> newBuilders = new LinkedList<TypeBuilderUnit>();
	List<PresenceCondition> newConditions = new LinkedList<PresenceCondition>();

	for (Universe u : unis)
	    for (int i = 0; i < builders.size(); ++i)
		{
		    if (! (u.pc.isMutuallyExclusive(conditions.get(i))))
			{
			    TypeBuilderUnit t = new TypeBuilderUnit(builders.get(i));
			    t.setTypedef(name, u.rename, u.type);
			    newBuilders.add(t);
			    newConditions.add(u.pc.and(conditions.get(i)));
			}
		}
	builders = newBuilders;
	conditions = newConditions;
    }

    public boolean getIsValid()
    {
        boolean vals = true;
	for (TypeBuilderUnit t : builders)
	    vals = vals &&t.getIsValid();
	return vals;
    }

    public List<Boolean> validDeclQuals()
    {
	List<Boolean> vals = new LinkedList<Boolean>();
	for (TypeBuilderUnit t : builders)
	    vals.add(new Boolean(t.validDeclQuals()));
	return vals;
    }
    public String qualString()
    {
	String output = "";
        for (int i = 0; i < builders.size(); ++i)
	    {
		output += builders.get(i).qualString() + "{" + conditions.get(i).toString() + "}";
		if (i < builders.size() - 1)
		    output += "/";
	    }
	return output;
    }
    public TypeBuilderUnit getQualTU()
    {
	return builders.get(0);
    }
}
