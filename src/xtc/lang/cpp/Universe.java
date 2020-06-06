package xtc.lang.cpp;
import xtc.type.Type;

public class Universe
{
    public Universe()
    {
	rename = "";
	type = null;
    }
    public Universe(String rename, Type type)
    {
	this.rename = rename;
	this.type = type;
    }
    
    public String rename;
    public Type type;
    
    public String getRenaming() {
	return rename;
    }

    public Type getType()
    {
	return type;
    }

    public String toString()
    {
	return rename + " " + type.toString();
    }
}
