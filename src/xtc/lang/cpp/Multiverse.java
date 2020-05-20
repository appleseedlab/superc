package xtc.lang.cpp;
import java.util.List;
import java.util.LinkedList;
import java.util.HashMap;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.type.Type;

public class Multiverse
{
    public class Universe
    {
	public Universe()
	{
	    rename = "";
	    type = null;
	    pc = null;
	}
	public Universe(String rename, Type type, PresenceCondition pc)
	{
	    this.rename = rename;
	    this.type = type;
	    this.pc = pc;
	    pc.addRef();
	}
	public boolean exclusiveFromPC(PresenceCondition pc)
	{
	    return this.pc.isMutuallyExclusive(pc);
	}
	public void delRef()
	{
	    pc.delRef();
	}
	public String rename;
	public Type type;
	public PresenceCondition pc;
    }
    
    HashMap<String, List<Universe>> mapping;

    public Multiverse()
    {
	mapping = new HashMap<String,List<Universe>>();
    }

    public boolean addMapping(String name, String rename, Type t, PresenceCondition p)
    {
	List<Universe> value = mapping.get(name);
	if (value == null)
	    {
		List<Universe> newEntry = new LinkedList<Universe>();
		newEntry.add(new Universe(rename, t, p));
		mapping.put(name, newEntry);
	    }
	else
	    {
		boolean noCollision = true;
	        for (Universe u : value)
		    {
			noCollision = noCollision && u.exclusiveFromPC(p);
		    }
		if (!noCollision)
		    return false;
		value.add(new Universe(rename, t, p));
	    }
	return true;
    }
    public void delRefs()
    {
	for (List<Universe> x : mapping.values())
	    for (Universe u : x)
		u.delRef();
    }
}
