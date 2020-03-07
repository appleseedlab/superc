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

import java.util.HashMap;
import java.util.Vector;
import java.util.ArrayList;
import java.util.List;
import xtc.util.Utilities;
import net.sf.javabdd.BDD;

import xtc.lang.cpp.Syntax.*;

import java.io.*;
/**
 * A tool that gathers usage statistics information about how statements are used in
 * combination with preprocessor conditions.
 *
 * @author Zach Patterson
 * @version 0.5
 */
public class SuperCAdvancedUsageStats
{
    private HashMap<String,Integer> inCondStats, condStats, same, branchDiff;
    private Vector<String> fluffValues;
    private Vector<HashMap<String,Boolean> > explosionValues;
    private Vector<String> explosionCount;
    private boolean inDepth;
    private Integer lineNum;
    private GNode lineNums;
    
    /**
     * Initializes the advanced statistics. This includes initializing
     * various hashmaps and compiling a list of filler nodes to remove
     */
    public SuperCAdvancedUsageStats(boolean depth)
    {
	lineNum = 1;
	lineNums = GNode.create(lineNum.toString(), true);
	condStats = new HashMap<String,Integer>();
	inCondStats = new HashMap<String,Integer>();
	same = new HashMap<String,Integer>();
	branchDiff = new HashMap<String,Integer>();
	fluffValues = new Vector<String>();
	fluffValues.add("ExternalDeclarationList");
	fluffValues.add("CompoundStatement");
	fluffValues.add("DeclarationOrStatementList");
	fluffValues.add("LocalLabelDeclarationListOpt");
	fluffValues.add("xtc.lang.cpp.Syntax$Language");
	fluffValues.add("xtc.lang.cpp.Syntax$Text");
	explosionValues = new Vector< HashMap<String,Boolean> >();
	HashMap<String,Boolean> temp = new HashMap<String,Boolean>();
	temp.put("FunctionPrototype",new Boolean(true));
	explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
        temp.put("IterationStatement",new Boolean(true));temp.put("ExpressionStatement",new Boolean(false));temp.put("CompoundStatement",new Boolean(false));temp.put("SelectionStatement",new Boolean(false));
	explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
	temp.put("SelectionStatement",new Boolean(true)); temp.put("IterationStatement",new Boolean(false));temp.put("ExpressionStatement",new Boolean(false));temp.put("CompoundStatement",new Boolean(false));
	explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
	temp.put("Declaration",new Boolean(true)); temp.put("EnumSpecifier",new Boolean(false)); temp.put("UnionSpecifier",new Boolean(false)); temp.put("StructSpecifier",new Boolean(false));
        explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
	temp.put("StructSpecifier",new Boolean(true));
        explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
	temp.put("EnumSpecifier",new Boolean(true));
        explosionValues.add(temp );
	temp = new HashMap<String,Boolean>();
	temp.put("UnionSpecifier",new Boolean(true));
        explosionValues.add(temp );
	explosionCount = new Vector<String>();
	inDepth = depth;
    }

    public SuperCAdvancedUsageStats()
    {
	this(false);
    }

    /**
     * Prints the relavant AST. unlike the -printAST flag, this
     * deals with children through identation, as well as it
     * removes cumbersome nodes that don't effect usage statistics. Each
     * node is printed out, followed by a recursive call on all of it's 
     * children with an extra tab added to the indents. This method also constructs
     * a replica AST which matches line numbers.
     *
     * @param node the current node being printed.
     * @param parent the string name of the node immediately above this one.
     * @param idents the identations that occur before any print at this level.
     * @param lineParent the parent of this node in the recreation of the AST line numbers
     */
    public void print(Node node, String parent, String indents, GNode lineParent)
    {
	if (node == null)
	    return;
	
	String curName = node.getName();
	int size = node.size();
	for (int i = 0; i < size; ++i)
	    {
		Object o =  node.get(i);
		if (o instanceof Text)
		    {
			System.out.println(lineNum.toString() + indents + ((Text<?>)o).getTokenText());
		        lineNum++;
		    }
		if (o instanceof Language)
		    {
			System.out.println(lineNum.toString() + indents + ((Language<?>)(o)).tag);
		        lineNum++;
		    }
		if (o instanceof Node)
		    {
			System.out.println(lineNum.toString() + indents + ((Node)o).getName());
			GNode x = GNode.create(lineNum.toString(), true);
			lineNum++;
			print((Node)o, curName, indents + "\t", x);
			lineParent.add(x);
		    }
		else
		    {
			//if (! (o instanceof PresenceCondition))
			    System.out.println(lineNum.toString() + indents +  o);
			    //else
			    //System.out.println(lineNum.toString() + indents + "presenceCondition!");
			GNode x = GNode.create(lineNum.toString(), false);
			lineParent.add(x);
			lineNum++;
		    }
	    }
	
    }

    /**
     * Gathers useful conditional usage information. Everytime a conditional
     * node is found, it's parent is recorded in {@link #condStats}, as well as if the parent was
     * conditional, the child is recoreded in {@link #inCondstats}. Futhermore, all Node children 
     * are recursively executed. Whenever conditional nodes are found, the contiguous 
     * block of them are sent to {@link #compareBranches}, for differences between branch stats.
     * 
     * @param node the current node being searched.
     * @param parent the name of node's parent.
     * @param variable whether or not the direct parent of this node was conditional or not.
     */
    public void findBranchDiffs(Node node, String parent, boolean variable)
    {
	if (node == null)
	    return;
	
	String curName = node.getName();
	
	if (variable)
	    addToStats(curName, parent, true);

	boolean nextVariable = false;

	if (node.getName().equals("Conditional"))
	    {
		nextVariable = true;
		addToStats(curName, parent, false);
	    }
	
	int size = node.size();
	ArrayList<Object> block = null;
	boolean endBlock = false;
	for (int i = 0; i < size; ++i)
	    {
		Object o =  node.get(i);
	        if (o instanceof Node)
		    {
			findBranchDiffs((Node)o, curName, nextVariable);
			//possibly add to block
			//child is conditional
			if ( ((Node)o).getName().equals("Conditional") )
			    {
				endBlock = false;
				if (block == null)
				    block = new ArrayList<Object>();
				for (int j = 0; j < ((Node)o).size(); ++j)
				    block.add((((Node)o).get(j)));
			    }
			else
			    endBlock = true;
		    }
		else
		    endBlock = true;
		
		if (endBlock && block != null)
		    {
			compareBranches(block);
			block = null;
		    }
	    }
	if (block != null)
	    compareBranches(block);
	
		
    }

    /**
     *
     */
    void findExplosionCount(Node node, HashMap<String,Boolean> active, HashMap<BDD, Boolean> curConditions, HashMap<BDD, Boolean> relConds, GNode lineParent)
    {
	if (node == null)
	    return;
	BDD recentC = null;
        int size = node.size();
	boolean condAdded = false;
	for (int i = 0; i < size; ++i)
	    {
		Object o =  node.get(i);
		
		if (o instanceof Node)
		    {
			Node n = (Node)o;
			String name = getNodeTag(n);
			HashMap<BDD,Boolean> newSetConds = new HashMap<BDD, Boolean>(curConditions);
			boolean newSet = false;
			for (int j = 0; j < explosionValues.size(); ++j)
			    {
				HashMap<String,Boolean> eV = explosionValues.get(j); 
				if ( eV.get(name) != null && eV.get(name))
				    {
					findExplosionCount(n, eV, curConditions, newSetConds, (GNode)lineParent.get(i));
					if (newSetConds.size() > curConditions.size())
					    explosionCount.add("(" + getNodeTag(lineParent.get(i)) + ")" + name + "->" + Integer.toString(newSetConds.size() - curConditions.size() ));
					newSet = true;
					break;
				    }
			    }
			
			if ( active != null &&
			     (!active.containsKey(name)
			      //special switch case
			      ||
			      ( (node.get(0) instanceof Language && (((Language<?>)(node.get(0))).tag.toString()).equals("SWITCH")) ))) 
			    {
				findExplosionCount(n, active, curConditions ,relConds, (GNode)lineParent.get(i));
			    }
			else if (!newSet)
			    {
				
				findExplosionCount(n, active, curConditions,newSetConds, (GNode)lineParent.get(i));
			    }
		    }
		else if(o instanceof PresenceCondition)
		    {
			if (!relConds.containsKey(((PresenceCondition)o).getBDD()))
			    relConds.put(((PresenceCondition)o).getBDD(),true);
			    if (!curConditions.containsKey(((PresenceCondition)o).getBDD()))
			    {
				if(condAdded)
				    {
					curConditions.remove(((PresenceCondition)o).getBDD());
					curConditions.put(((PresenceCondition)o).getBDD(), true);
				    }
				else
				    {
					curConditions.put(((PresenceCondition)o).getBDD(), true);
					condAdded = true;
				    }
				recentC = ((PresenceCondition)o).getBDD();
			    }
		    }
		
	    }
	if (condAdded)
	    curConditions.remove(recentC);
    }

    /**
     * Finds and stores preprocessor usage statstics. First the irrelevant nodes
     * are removed from the tree in {@link #deFluff}. Then, the relevant tree is
     * printed in {@link #print}. Then the stastics are gathered in {@link #find(Node, String, boolean)}
     *
     * @param root the root node of the AST.
     */
    public void find(Node root)
    {
	Node transRoot = root;
	if (inDepth)
	    transRoot = deFluff(root, "1");
	print(transRoot, "root", "", lineNums);
	HashMap<BDD,Boolean> constCondition = new HashMap<BDD,Boolean>();
        findExplosionCount(root, (HashMap<String,Boolean>) null, constCondition, new HashMap<BDD,Boolean>(), lineNums);
	if (inDepth)
	    findBranchDiffs(transRoot,"", false);
    }

    /**
     * Prints out the usage stastics found in {@link #condStats}, {@link #inCondStats},
     * {@link #same}, and {@link #branchDiff}.
     */
    public void print()
    {
	System.out.println("Explosion counts:");
	System.out.println(explosionCount);
        if (inDepth)
	    {
		System.out.println("Conditionals used within:");
		System.out.println(condStats);
		
		System.out.println("Used within conditionals:");
		System.out.println(inCondStats);
		
		System.out.println("Same statement types in branches:");
		System.out.println(same);
	
		System.out.println("Branch comparison mismatches:");
		System.out.println(branchDiff);
	    }
    }

    /**
     * Simplifies the AST. A new node is created of variable size that
     * will replace x in the defluffed AST. It simply creates a new node,
     * and then places all of x's children relevant to usage stats, found with {@link #getChildren}.
     * 
     * @param x the current Node being replaced.
     * @param condition the current active presence condition.
     * @return the newly created node.
     */
    private Node deFluff(Node x, String condition)
    {
	if (x == null)
	    return x;
	//turn this into Variable
	Node newNode = GNode.create(x.getName(), true);
        newNode.addAll(getChildren(x, condition));
	return newNode;
    }


    /**
     * Finds relevant children in an AST. Each of x's children is checked. If a child
     * is identified to be superflucdous by {@link #fluffValues}, then it's children are
     * added to the list in it's place. If a child is a constant conditional, or has a presence
     * condition that is redundent, it's children are added to the list in it's place. If the child
     * is a node, then we call {@link #deFluff} with it to get a cleaner representation. If the child is
     * not a node, it is added as is. Whenever a presence condition is found, it becomes the new current
     * condition. 
     * 
     * @param x the current Node.
     * @param condition the current active presence condition.
     * @return all the relevant children to x.
     */
    private Collection<Object> getChildren(Node x, String condition)
    {
	Vector<Object> children = new Vector<Object>();
	for (int i = 0; i < x.size(); ++i)
	    {
		Object o = x.get(i);
		if (o instanceof PresenceCondition)
		    {
			condition = o.toString();
		    }
		if (o instanceof Node)
		    {
			Node y = (Node)o;
			if (fluffValues.contains(y.getName()))
			    {
				children.addAll(getChildren(y, condition));
			    }
			else if(y.getName().equals("Conditional") &&
				(y.get(0).toString().equals("1") || (y.get(0).toString().equals(condition)) ))	    
			    {
				y.remove(0);
				children.addAll(getChildren(y, condition));
			    }
			else
			    {
				if (y.getName().equals("Conditional"))
				    children.add(deFluff(y, y.get(0).toString()));
				else
				    children.add(deFluff(y, condition));
			    }
		    }
		else
		    {
			children.add(o);
		    }
	    }
	return children;
    }
    
    /**
     * Finds code differences between conditional branches. Using a list of all children across
     * the possible branches, each one is blocked into a list based off of their presence
     * condition. Then each block is checked against one another to see what the differences 
     * are in {@link #findDiffs}.
     *
     * @param x the list of all objects that occur in contiguous conditional branches
     */
    private void compareBranches(ArrayList<Object> x)
    {
	Vector< Vector<Object> > branches;
	branches = new Vector< Vector<Object> >();

	Vector<Object> curBranch = new Vector<Object>();
	curBranch.add(x.get(0).toString());
	int size = x.size();
	for (int i = 1; i < size; ++i)
	    {
		Object o = x.get(i);
	        if (o instanceof PresenceCondition)
		    {
			if (! o.toString().equals(curBranch.get(0).toString()))
			    {
				branches.add(curBranch);
				curBranch = new Vector<Object>();
				curBranch.add(o.toString());
			    }
		    }
		else
		    curBranch.add(o);
	    }
	branches.add(curBranch);
	
	for (int i = 0; i < branches.size() - 1; ++i)
	    {
		Vector<Object> a = branches.get(i);
		for (int j = i+1; j < branches.size(); ++j)
		    {
		     	Vector<Object> b = branches.get(j);
		
			if (! a.get(0).equals(b.get(0)))
			    {
				GNode nodeA, nodeB;
				nodeA = GNode.create("", true);
				nodeB = GNode.create("", true);
			        for (int w = 1; w < a.size(); ++w)
				    nodeA.add(a.get(w));
				for (int w = 1; w < b.size(); ++w)
				    nodeB.add(b.get(w));
				findDiffs(nodeA, nodeB,"", (String)a.get(0),(String)b.get(0));
			    }
		    }
	    }
	
	
	
    }

    /**
     * a and b are passed into {@link #findDiffs}. Lists are initialized for the differences
     * and number of differences between a and b. These lists are passed as out parameters.
     * Once the lists are returned, only selected comparisons remain and they are added
     * to {@link #branchDiff}.
     *
     * @param a node being compared with b
     * @param b node being compared with a
     * @param base the parents within the branches that a and b have in common
     * @param pcA presence condition associated with a
     * @param pcB presence condition associated with b
     */
    private void findDiffs(Node a,  Node b, String base, String pcA, String pcB)
    {
	Vector<String> output = new Vector<String>();
	Vector<Integer> mismatches = new Vector<Integer>();
	findDiffs(a, b, base, pcA, pcB, output, mismatches);
	for (int i = 0; i < output.size(); ++i)
	    addToHash(output.get(i), branchDiff);
    }

    /**
     * Two nodes are compared and contrasted. All children in a are compared to all children
     * in b. If two nodes match, take the best match for each value. This is defined as farthest depth, 
     * if depth is a tie, then it is what has less early differences. How this is defined is that 
     * recursive calls will return a string of possible outputs (being what are the differences 
     * to add to the hash, along with a list of numbers. Each number represents the differences at 
     * that level of depth. Only the results of the decision made will be returned.
     *
     * @param a the first node being compared
     * @param b the second node being compared
     * @param base all the previous nodes that occured before this starting after the conditional 
     * @param pcA presence condition associated with a
     * @param pcB presence condition associated with b
     * @param output list of all relevant differences between a and b
     * @param mismatches list of the number of differences at each depth between a and b
     */
    private void findDiffs(Node a,  Node b, String base, String pcA, String pcB, Vector<String> output, Vector<Integer> mismatches)
    {
        Vector<Boolean>usedA = new Vector<Boolean>();
        Vector<Boolean>usedB = new Vector<Boolean>();
	for (int i = 0; i < a.size(); ++i)
	    usedA.add(false);
	for (int i = 0; i < b.size(); ++i)
	    usedB.add(false);
	for (int i = 0; i < a.size(); ++i)
	    {
		int best = -1;
		Vector<String> bestOutput = null;
		Vector<Integer> bestDifs = null;
		for (int j = 0; j < b.size(); ++j)
		    if (!usedB.get(j))
			{
			    Object aO = a.get(i), bO = b.get(j);
			    if (aO.getClass() == bO.getClass())
				{
				    if (aO instanceof Node &&
					((Node)aO).getName().equals(((Node)bO).getName())
					)
					{
					    
					    Vector<String> tempOutput = new Vector<String>();
					    Vector<Integer> tempDifs = new Vector<Integer>();
					    findDiffs((Node)aO, (Node)bO, base + ((Node)aO).getName() + "->", pcA, pcB, tempOutput, tempDifs);
					    if (bestDifs == null || (lessMismatches(bestDifs,tempDifs)))
						{
						    bestDifs = tempDifs;
						    bestOutput = tempOutput;
						    best = j;
						}
					    
					}
				    else if (aO.toString().equals(bO.toString()))
					{
					    best = -1;
					    usedB.set(j,true);
					    usedA.set(i,true);
					    addToHash(base + aO.toString(), same);
					    break;
					}
					
					
				}
			}
		if (best != -1)
		    {
			usedB.set(best, true);
			usedA.set(i, true);
			//combine outputs, add sum of mismatches
			output.addAll(bestOutput);
		        for (int j = 0; j < bestDifs.size(); ++j)
			    {
				if (j >= mismatches.size())
				    mismatches.add(bestDifs.get(j));
				else
				    mismatches.set(j, mismatches.get(j) + bestDifs.get(j));
			    }
		    }
	    }

	
	if (usedA.contains(false) || usedB.contains(false))
	    {
		Integer difCount = 0;
		String dif = "[" + pcA + "(";
		Vector<String> unUsedChildren = new Vector<String>();
		for (int i = 0; i < a.size(); ++i)
		    if (!usedA.get(i))
			{
			    unUsedChildren.add(getNodeTag(a.get(i)));
			    ++difCount;
			}
		Collections.sort(unUsedChildren);
		for (int i = 0; i < unUsedChildren.size(); ++i)
		    dif += unUsedChildren.get(i) + (i == unUsedChildren.size() - 1 ? "" : ",");

		dif += ")/" + pcB + "(";
		unUsedChildren.clear();
		for (int i = 0; i < b.size(); ++i)
		    if (!usedB.get(i))
			{
			    unUsedChildren.add(getNodeTag(b.get(i)));
			    ++difCount;
			}
		Collections.sort(unUsedChildren);
		for (int i = 0; i < unUsedChildren.size(); ++i)
		    dif += unUsedChildren.get(i) + (i == unUsedChildren.size() - 1 ? "" : ",");
		dif += ")]";

		mismatches.add(0, difCount);
		output.add(0, base + dif);
	    }
    }

    /**
     * Returns the relevant name of x. If x is a node, we return the name of the node.
     * otherwise, we return the string interpretation of x.
     *
     * @param x the object we desire the name of.
     * @return the relevant name of x.
     */
    private String getNodeTag(Object x)
    {
	if (x instanceof Node)
	    return ((Node)x).getName();
	else
	    return x.toString();
    }

    /**
     * Adds conditional statistic information. If this occurs inside a conditional,
     * then curName is added to {@link #inCondStats}, otherwise the parent is added
     * to {@link #condStats}.
     *
     * @param curName the name of the current node.
     * @param parent the name of the parent of the current node.
     * @param inCond whether or not the current node is inside a conditional
     */
    private void addToStats(String curName, String parent, boolean inCond)
    {
	if (inCond)
	    addToHash(curName, inCondStats);
	else
	    addToHash(parent, condStats);
    }

    /**
     * Adds x to hashmap y. The string x is queried in hashmap y. If it is found,
     * then the value is incremented by 1. If it is not, then a new entry is
     * put into the map with an initial value of 1.
     *
     * @param x the string to be queried and incremented/added
     * @param y the hashmap that x will be queried in.
     */
    private void addToHash(String x, HashMap<String,Integer> y)
    {
	Integer z = y.get(x);
	if (z != null)
	    y.replace(x, z+1);
	else
	    y.put(x, 1);
    }

    /**
     * compares two lists of Integers to see which one has fewer differences. First the two
     * are compared in size. More size, means a deeper match was reached, this is the most
     * important factor. If the sizes are equal, then we see which had fewer differences
     * at the lowest level. If a branch has lower differences at a lower level, then it is
     * perferred.
     *
     * @param incumbent the current node selection for most accurate match
     * @param challenger the new node being compared to the incumbent
     * @return whether or not the challenger is better than the incumbent
     */
    private boolean lessMismatches(List<Integer> incumbent, List<Integer> challenger)
    {
	if (incumbent.size() > challenger.size())
	    return false;
	else if (incumbent.size() < challenger.size())
	    return true;
	
	for (int i = 0; i < incumbent.size(); ++i)
	    {
		if (incumbent.get(i) < challenger.get(i))
		    return false;
		else if (incumbent.get(i) > challenger.get(i))
		    return true;
	    }
	return false;
    }
}
