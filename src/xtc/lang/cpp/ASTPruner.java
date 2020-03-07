package xtc.lang.cpp;

import java.util.Collection;
import java.util.Collections;
import java.util.Vector;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Set;

import xtc.tree.Printer;
import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import java.util.Vector;
import java.util.ArrayList;
import java.util.List;
import xtc.util.Utilities;
import net.sf.javabdd.BDD;

import java.io.*;

import xtc.lang.cpp.Syntax.*;
/**
 * A tool that gathers usage statistics information about how statements are used in
 * combination with preprocessor conditions.
 *
 * @author Zach Patterson
 * @version 0.1
 */
public class ASTPruner
{
    String fileName;
    public ASTPruner(String f)
    {
	fileName = f;
    }

    private boolean pruneNode(Node node)
    {
	if (node == null)
	    return false;
	
	if (node.hasLocation() && !node.getLocation().file.endsWith(fileName))
	    {
		return false;
	    }
	for (int i = 0; i < node.size(); ++i)
	    if (node.get(i) instanceof Node)
		if (!pruneNode((Node)node.get(i)))
		    if (node.getName().equals("ExternalDeclarationList"))
			node.remove(i--);
		    else
			return false;
	return true;
    }

    public void prune(Node root)
    {
	pruneNode(root);
    }
}
