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

    public void addMapping(String name, List<Universe> unis)
    {
      // stores the renaming
      List<Universe> value = mapping.get(name);
      if (value == null)
	  {
	      List<Universe> newEntry = new LinkedList<Universe>();
	      for (Universe x : unis)
		  newEntry.add(x);
	      mapping.put(name, newEntry);
	  }
      else
	  {
	      for (Universe x : unis)
		  {
		      boolean noCollision = true;
		      for (Universe u : value)
			  {
			      noCollision = noCollision && u.exclusiveFromPC(x.pc);
			  }
		      if (!noCollision)
			  {
			      System.out.println("MultipleDef");
			      System.exit(1);
			  }
		      value.add(x);
		  }
	  }
      System.out.println(toString());
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
    public List<Universe> getTypedefsOf(String ident)
    {
	List<Universe> ret = new LinkedList<Universe>();
	List<Universe> value = mapping.get(ident);
	if (value != null)
	    {
		for (Universe u : value)
		    {
			if (u.type.hasAttribute(Constants.ATT_STORAGE_TYPEDEF))
			    ret.add(u);
		    }
		if (ret.size() == 0)
		    {
			System.out.println("no typedef found for id " + ident);
			System.exit(1);
		    }
	    }
	return ret;
    }
}
