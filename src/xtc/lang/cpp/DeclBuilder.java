package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;

public class DeclBuilder
{
    String identifier;
    int numPointers;
    List<String> arrays;
    DeclBuilder inner;
    boolean isValid;

    public DeclBuilder()
    {
	identifier = "";
	numPointers = 0;
	arrays = new LinkedList<String>();
	inner = null;
	isValid = true;
    }
    
    public DeclBuilder(String name)
    {
	identifier = name;
	numPointers = 0;
	arrays = new LinkedList<String>();
	inner = null;
	isValid = true;
    }
    
    public void addPointer()
    {
	numPointers++;
    }

    public void addArray(String i)
    {
	addArray(i, true);
    }

    public int countArrays()
    {
	int count = 0;
        count += arrays.size();
	if (inner != null)
	    count += inner.countArrays();
	return count;
    }
    
    public void addArray(String i, boolean seen)
    {
        if (!seen)
	    if (countArrays() == 0)
		arrays.add("");
	    else
		isValid = false;
        else
	    arrays.add(i);
	    
    }

    public void addDeclBuilder(DeclBuilder d)
    {
	inner = d;
	if (!d.isValid)
	    isValid = false;
    }

    public void merge(DeclBuilder d)
    {
	numPointers += d.numPointers;
	if (inner != null)
	    {
		if (d.inner != null)
		    isValid = false;
	    }
	else
	    inner = d.inner;
	if (!identifier.equals(""))
	    {
		if (!d.identifier.equals(""))
		     isValid = false;
	    }
	else
	    identifier = d.identifier;
	
	for (int i = 0; i < d.arrays.size(); ++i)
		arrays.add(d.arrays.get(i));	
    }

    public String getID()
    {
	if (identifier.equals("") && inner != null)
	    return inner.getID();
	return identifier;
    }

    public String toString()
    {
	if (!isValid)
	    return "Decl Error";
	String output = "";
	for (int i = 0; i < numPointers; ++i)
	    output += "*";
	if (!identifier.equals(""))
	    output += identifier;
	if (inner != null)
	    output += "(" + inner.toString() + ")";
	for (int i = 0; i < arrays.size(); ++i)
	    {
		output += "[";
		output += arrays.get(i);
		output += "]";
	    }
	return output;
    }
    
}
