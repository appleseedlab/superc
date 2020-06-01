package xtc.lang.cpp;
import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.type.Type;
import xtc.Constants;

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
