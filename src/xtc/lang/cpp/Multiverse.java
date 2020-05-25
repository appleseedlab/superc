package xtc.lang.cpp;
import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.type.Type;
import xtc.Constants;

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

  public String getRenaming() {
    return rename;
  }

	public String toString()
	{
	    return rename + " " + type.toString() + " " + pc.toString();
	}
    }

    HashMap<String, List<Universe>> mapping;

    List<String> getAllRenamings(String key) {
      LinkedList<String> allRenamings = new LinkedList<String>();
      List<Universe> value = mapping.get(key);
      if (value == null)
	  return null;
      for (Universe u : value)
        allRenamings.add(u.getRenaming());
      return allRenamings;
    }

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

    public String toString()
    {
	String output = "";
	for (Map.Entry<String,List<Universe>> x : mapping.entrySet())
	    {
		output += x.getKey() + "\n";
		for (Universe u : x.getValue())
		    output += "\t" + u.toString() + "\n";
	    }
	return output;
    }
    public Type getTypedefOf(String ident)
    {
	List<Universe> value = mapping.get(ident);
	if (value != null)
	    for (Universe u : value)
		{
		    if (u.type.hasAttribute(Constants.ATT_STORAGE_TYPEDEF))
			return u.type;
		}
	return null;
    }
}
