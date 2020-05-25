package xtc.type;

import java.io.IOException;

import xtc.Limits;

/**
 * The superclass of all number types.
 *
 * @author Robert Grimm
 * @version $Revision: 1.27 $
 */
public class TypedefT extends Type {
    private String typeName;
    private Type typedefType;
    public TypedefT()
    {
	typeName = "";
	typedefType = null;
    }
    
    public TypedefT(String t, Type type)
    {
	typeName = t;
	typedefType = type;
    }

    public Tag tag()
    {
	return typedefType.tag();
    }

    public TypedefT copy()
    {
	return new TypedefT(typeName, typedefType.copy());
    }
}