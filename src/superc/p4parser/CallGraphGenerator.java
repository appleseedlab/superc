package superc;
import java.lang.reflect.*;
import java.sql.CallableStatement;
import java.time.LocalDate;
import java.lang.Iterable;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;
import superc.core.Syntax;
import superc.core.Syntax.Language;

import org.w3c.dom.NameList;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

// import xtc.type.P4;
import xtc.type.Type;

import superc.core.PresenceConditionManager.PresenceCondition;
import superc.core.MacroTable.Macro;
import superc.core.MacroTable.Entry;
import superc.core.Syntax.Kind;
import superc.p4parser.P4Tag;

public class CallGraphGenerator {

    Map<LanguageObject, Map<String, LanguageObject>> symtab;
    Stack<LanguageObject> scope;
    LanguageObject global_scope = new LanguageObject("GLOBAL", null);
    LanguageObject undefined_scope = new LanguageObject("UNDEFINED", null);
    // A list of grammar constructs that are not yet supported and might contain invocation
    HashSet<String> notExplicitlySupported = new HashSet<>(Arrays.asList("constantDeclaration",
                                                                         "tableDeclaration",
                                                                         "instantiation",
                                                                         "emptyStatement",
                                                                         "returnStatement",
                                                                         "exitStatement",
                                                                         "switchStatement",
                                                                         "functionPrototypes",
                                                                         "invokingExpression"));
    //PC Scope

    public CallGraphGenerator() {
        this.symtab = new HashMap<>();
        this.scope = new Stack<>();

        // TODO: do a second run to map UNDEFINED scopes with blocks defined after
        // OR, first traverse declarations and then pass through for uses - separate call graph and declaration passes
        // OR in single pass, with flags to say declared or not (separate type checking pass)

        scope.add(global_scope);
    }

    class LanguageObject {
        public final String name;
        public final LanguageObject nameSpace;
        public HashSet<LanguageObject> callees;

        public LanguageObject(String name, LanguageObject nameSpace) {
            this.name = name;
            this.nameSpace = nameSpace;
            callees = new HashSet<>();
        }

        @Override
        public String toString() {
            // For simple toString calls where the current value is not present under the symbol table
            if(this == global_scope) {
                return name;
            }
            
            return name + "(" + this.nameSpace.name + ")";
        }

        /**
         * A toString function to use when in-depth detail about current object is needed.
         * Outputs the callees present under the current object if it is not present under the global scope.
         * @return
         */
        public String toStringExtensive() {
            String finalString = name + ": ";

            Iterator<String> itr = symtab.get(this).keySet().iterator();

            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                finalString += symtab.get(this).get(childKey).toString();

                if(symtab.containsKey(childKey)) {
                    finalString += itr.hasNext() ? ", " : "";
                    continue;
                }

                ArrayList<String> calleeNames = new ArrayList<>();
                for(LanguageObject callee : symtab.get(this).get(childKey).callees) {
                    calleeNames.add(callee.toString());
                }

                if(! calleeNames.isEmpty()) {
                    finalString += ": " + calleeNames.toString();
                }
                finalString += (itr.hasNext() ? ", " : "");
            }

            return finalString;
        }

        /**
         * Having same name under the same scope means they are "equal" for our usage and have same hash value
         */
        @Override
        public boolean equals(Object object) {
            if(this == object) {
                return true;    
            }
            if(object == null) {
                return false;
            }
            if (object instanceof LanguageObject == false) {
                return false;
            }

            LanguageObject compObject = (LanguageObject) object;

            if(compObject == global_scope || this == global_scope) {
                // if both are global_scope, then it should have returned true at the beginning
                return false;
            }

            if(compObject.name.equals(this.name)
               && compObject.nameSpace.equals(this.nameSpace)) {
                   return true;
            }

            return false;
        }

        @Override
        public int hashCode() {
            String hashString = "";
            if(this.nameSpace != null) {
                // not the GLOBAL LanguageObject
                hashString += this.nameSpace.name + "/";
            }
            hashString += this.name;
            
            return hashString.hashCode();
        }
        // TODO: pull out callees
        // conditioned callees
    }

    /**
     * Creates the scope if not present, creates entity for name under scope if not present.
     * Adds the entity to the given scope if it doesn't already exist.
     * 
     * Returns the existing or newly created entity.
     * @param scope
     * @param name
     * @return
     */
    public LanguageObject addToSymtab(LanguageObject scope, String name) {
        LanguageObject nodeObj = null;

        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        if(symtab.get(scope).containsKey(name)) {
            nodeObj = symtab.get(scope).get(name);
        } else {
            nodeObj = new LanguageObject(name, scope);
            symtab.get(scope).put(name, nodeObj);
        }

        return nodeObj;
    }

    /**
     * Checks if scope exists in the symbol table.
     * Returns true if it does, false otherwise.
     * @param scope
     * @return Boolean
     */
    public boolean doesScopeExist(LanguageObject scope) {
        return symtab.containsKey(scope);
    }

    /**
     * Checks if the given name exists under the given scope.
     * Returns true if it does, false otherwise.
     * @param scope The scope to check under
     * @param name The name to find under the scope
     * @return Boolean
     */
    public boolean doesSymbolExist(LanguageObject scope, String name) {
        if( !doesScopeExist(scope) ||
            !symtab.get(scope).containsKey(name)) {
                return false;
        }

        return true;
    }

    /**
     * Checks if scope and symbol exists, returns the corresponding object from symtab if it does.
     * Recursively goes through the parent scopes if not found under current scope.
     * Assertion error is invoked if it does not exist.
     * @param localScope
     * @param typeName
     * @return
     */
    public LanguageObject symtabLookup(LanguageObject localScope, String typeName) {
        assert !typeName.isBlank() : "typeName is not supposed to be empty when looking it up on symbol table";

        // base case where global_scope is the top-most parent
        if(localScope.equals(global_scope)) {
            assert doesSymbolExist(localScope, typeName) : "Calling to an undefined symbol \"" + typeName + "\"";
            return symtab.get(localScope).get(typeName);
        }

        // if the symbol does not exist in the current scope, check under its parent scope
        if( !doesSymbolExist(localScope, typeName)) {
            return symtabLookup(localScope.nameSpace, typeName);
        } else {
            return symtab.get(localScope).get(typeName);
        }
    }

    // TODO: this will change when separating out call graph generation
    public void lookupInSymTabAndAddAsCallee(String name) {
        // exists, add when doing only declarations

        LanguageObject callee = symtabLookup(scope.peek(), name);

        assert callee != null : "UNCAUGHT Calling to an undefined symbol when expecting it to be defined beforehand (" + name + ")";
        scope.peek().callees.add(callee);
    }

    public void doEverything(Node translationUnit) {
        definitionsVisitor.dispatch(translationUnit.getGeneric(0));
        callGraphVisitor.dispatch(translationUnit.getGeneric(0));
    }

    private Visitor definitionsVisitor = new Visitor() {
        // default visitor
        public Node visit(GNode n) {
            // filtering out block that aren't supported yet and can cause silent failures
            assert ! notExplicitlySupported.contains(n.getName()) : n.getName() + " is not supported at the moment";

            // just visiting the child nodes since no specific dispatch is available for current node
            Iterator itr = n.iterator();
            while(itr.hasNext()) {
                Object nextObj = itr.next();
                // assert (!nextObj.getClass().equals(PresenceCondition.class)) : "PresenceCondition nodes not supported at the moment. Under node: " + nextObj;
                if(nextObj instanceof Syntax) {
                    // Since Syntax objects are not nodes
                    // System.out.println("It's a syntax obj: " + nextObj.toString());
                    // System.out.println("tag: " + ((Language) nextObj).tag());
                    continue;
                } else if(nextObj instanceof PresenceCondition) {
                    // TODO handle PC scenarios under conditional nodes

                    assert ((PresenceCondition) nextObj).getAllConfigs().size() == 0 : "non-empty PresenceCondition nodes not supported at the moment";
                    continue;
                }
                dispatch((Node) nextObj);
            }
            return n;
        }

        public Node visitcontrolDeclaration(GNode n) {
            // If need to parse parameters, visit the controltypedeclaration instead of static function to get name
            String controlBlockName = getNameOfControlBlock(n.getGeneric(0));

            LanguageObject controlObj = addToSymtab(scope.peek(), controlBlockName);
            scope.add(controlObj);

            // skipping visiting controlTypeDeclaration

            dispatch(n.getGeneric(3)); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = n.getGeneric(5); // controlBody
            LanguageObject apply = addToSymtab(scope.peek(), applyBlockName);
            scope.add(apply);

            dispatch(n.getGeneric(0)); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            return n;
        }

        public Node visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(n.getGeneric(2));
            LanguageObject actionObj =  addToSymtab(scope.peek(), actionBlockName);
            scope.add(actionObj);

            dispatch(n.getGeneric(4)); // parameterList
            dispatch(n.getGeneric(6)); // TODO: blockStatement 

            scope.pop();

            return n;
        }

        // follow similar as last time (break into three different grammar constructs)
        // . member values has structfield list inside it, so no function calls inside it - but matters for data flow
        // header functions - push_front
        // TODO: write out explanation for lvalue
        public Node visitassignmentOrMethodCallStatement(GNode n) {

            if(n.size() == 4) { // assignment statement
                // TODO: figure out if need to implement scope for lvalue that is not an identifier (like identifier DOT identifier)
                String leftSizeValue = getPrefixedNonTypeNameFromLvalue(n.getGeneric(0)); // right now assuming just one identifier value is present
                dispatch(n.getGeneric(2)); // expression
                return n;
            } else { // method call statement
                int LPARENindx = 1;

                if(n.size() == 8) {
                    LPARENindx = 4;
                }

                // leaving it here cause argumentlist can contain assignments and expression
                dispatch(n.getGeneric(LPARENindx + 1)); // argumentList

                return n;
            }
        }

        // Interesting: functionDeclaration not part of P416? not in online language specification -- experimental
        //
        public Node visitfunctionDeclaration(GNode n) {
            // TODO: need to take care of typeOrVoid if we are keeping track of defined variables (can devolve into identifier or type ident)
            // dispatch(n.getGeneric(0));

            // as per language specification, functionPrototype will describe the name and type signature of the function
            String functionName = getStringUnderFunctionPrototype(n.getGeneric(0));
            LanguageObject functionObj = addToSymtab(scope.peek(), functionName);
            scope.add(functionObj);

            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return n;
        }

        public Node visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(n.getGeneric(0)); // TODO: take of parameter list here if needed to
            LanguageObject parserObj = addToSymtab(scope.peek(), parserName);
            scope.add(parserObj);

            dispatch(n.getGeneric(3)); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(n.getGeneric(4)); // parserStates

            scope.pop();

            return n;
        }

        public Node visitparserState(GNode n) {
            String stateName = getStringUnderName(n.getGeneric(2));
            LanguageObject stateObj = addToSymtab(scope.peek(), stateName);
            scope.add(stateObj);

            dispatch(n.getGeneric(4)); // parserStatements
            dispatch(n.getGeneric(5)); // transitionStatement

            scope.pop();
            
            return n;

        }

        public Node visitstateExpression(GNode n) {
            if(n.size() == 1) { // selectExpression; (name SEMICOLON is handled in callGraphVisitor)
                dispatch(n.getGeneric(0));
            }
            return n;
        }

        // TODO: check if we need to list table scope (if not, remove from callGraphGenerator as well)
        public Node visittableDeclaration(GNode n) {
            String tableName = getStringUnderName(n.getGeneric(2));
            LanguageObject tableObj = addToSymtab(scope.peek(), tableName);
            scope.add(tableObj);

            dispatch(n.getGeneric(4)); // tablePropertyList

            scope.pop();

            return n;
        }

        // TODO: functionprototype, extern declaration. lvalue, invkingexpression, expression
        // TODO: go through expressions and see which ones can make function calls (specs doc helps)
        // inside invoking expression we can specify that only 3-4 expressions can be valid syntactically (write the reasoning and have asserts)

    };

    private Visitor callGraphVisitor = new Visitor() {
        // default visitor
        public Node visit(GNode n) {
            // filtering out block that aren't supported yet and can cause silent failures
            assert ! notExplicitlySupported.contains(n.getName()) : n.getName() + " is not supported at the moment";

            // just visiting the child nodes since no specific dispatch is available for current node
            Iterator itr = n.iterator();
            while(itr.hasNext()) {
                Object nextObj = itr.next();
                // assert (!nextObj.getClass().equals(PresenceCondition.class)) : "PresenceCondition nodes not supported at the moment. Under node: " + nextObj;
                if(nextObj instanceof Syntax) {
                    // Since Syntax objects are not nodes
                    // System.out.println("It's a syntax obj: " + nextObj.toString());
                    // System.out.println("tag: " + ((Language) nextObj).tag());
                    continue;
                } else if(nextObj instanceof PresenceCondition) {
                    // TODO handle PC scenarios under conditional nodes

                    assert ((PresenceCondition) nextObj).getAllConfigs().size() == 0 : "non-empty PresenceCondition nodes not supported at the moment";
                    continue;
                }
                dispatch((Node) nextObj);
            }
            return n;
        }

        // TODO: Annotate the tree with the language object for the scope

        public Node visitcontrolDeclaration(GNode n) {
            // If need to parse parameters, visit the controltypedeclaration instead of static function to get name
            String controlBlockName = getNameOfControlBlock(n.getGeneric(0));

            LanguageObject controlObj = symtabLookup(scope.peek(), controlBlockName);
            scope.add(controlObj);

            // skipping visiting controlTypeDeclaration

            dispatch(n.getGeneric(3)); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = n.getGeneric(5); // controlBody
            LanguageObject apply = symtabLookup(scope.peek(), applyBlockName);
            lookupInSymTabAndAddAsCallee(applyBlockName); // TODO: ask if need to insert this as a callee?
            scope.add(apply);

            dispatch(n.getGeneric(0)); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            return n;
        }

        public Node visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(n.getGeneric(2));
            LanguageObject actionObj =  symtabLookup(scope.peek(), actionBlockName);
            scope.add(actionObj);

            dispatch(n.getGeneric(4)); // parameterList
            dispatch(n.getGeneric(6)); // TODO: blockStatement 

            scope.pop();

            return n;
        }

        // Interesting: functionDeclaration not part of P416? not in online language specification -- experimental
        //
        public Node visitfunctionDeclaration(GNode n) {
            // TODO: need to take care of typeOrVoid if we are keeping track of defined variables (can devolve into identifier or type ident)
            // dispatch(n.getGeneric(0));

            // as per language specification, functionPrototype will describe the name and type signature of the function
            String functionName = getStringUnderFunctionPrototype(n.getGeneric(0));
            LanguageObject functionObj = symtabLookup(scope.peek(), functionName);
            scope.add(functionObj);

            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return n;
        }

        public Node visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(n.getGeneric(0)); // TODO: take of parameter list here if needed to
            LanguageObject parserObj = symtabLookup(scope.peek(), parserName);
            scope.add(parserObj);

            dispatch(n.getGeneric(3)); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(n.getGeneric(4)); // parserStates

            scope.pop();

            return n;
        }

        public Node visitparserState(GNode n) {
            String stateName = getStringUnderName(n.getGeneric(2));
            LanguageObject stateObj = symtabLookup(scope.peek(), stateName);
            scope.add(stateObj);

            dispatch(n.getGeneric(4)); // parserStatements
            dispatch(n.getGeneric(5)); // transitionStatement

            scope.pop();
            
            return n;

        }

        public Node visitdirectApplication(GNode n) {
            // As per the grammar we can have only one typename before the `.apply`, so nesting can't happen
            
            String calleeName = getNameFromTypeName(n.getGeneric(0));
            // TODO: below doesn't tell that it's also doing type checking, separate it out
            lookupInSymTabAndAddAsCallee(calleeName);

            // dispatch(n.getGeneric(4)); // argumentList

            return n;
        }

        // TODO: comment on why using size or break assingmentOrMethodCallStatement into two
        // TODO: build control_duplicate with a main module
        public Node visitassignmentOrMethodCallStatement(GNode n) {
            if(n.size() == 4) { // assignment statement
                // TODO: figure out if need to implement scope for lvalue that is not an identifier (like identifier DOT identifier)
                dispatch(n.getGeneric(2)); // expression
                return n;
            } else { // method call statement
                int LPARENindx = 1;

                if(n.size() == 8) {
                    LPARENindx = 4;
                }

                LanguageObject methodCallee = getMethodPrefixedNonTypeNameFromLvalue(n.getGeneric(0), this, scope.peek());
                scope.peek().callees.add(methodCallee);

                // dispatch(n.getGeneric(LPARENindx + 1)); // argumentList
            }
            return n;
        }

        // TODO: check if we need to list table scope (if not, remove from definitions dispatcher as well)
        public Node visittableDeclaration(GNode n) {
            String tableName = getStringUnderName(n.getGeneric(2));
            LanguageObject tableObj = symtabLookup(scope.peek(), tableName);
            scope.add(tableObj);

            dispatch(n.getGeneric(4)); // tablePropertyList

            scope.pop();

            return n;
        }

        public Node visitstateExpression(GNode n) {
            if(n.size() == 2) { // name SEMICOLON
                // TODO: need to handle keywords like accept or reject
                String stateName = getStringUnderName(n.getGeneric(0));
                lookupInSymTabAndAddAsCallee(stateName);
            } else { // selectExpression;
                dispatch(n.getGeneric(0));
            }
            return n;
        }

        public Node visitselectCase(GNode n) {
            // TODO trace keysetExpression for data

            String selectName = getStringUnderName(n.getGeneric(2));
            lookupInSymTabAndAddAsCallee(selectName);

            return n;
        }

        // TODO: weird handling of constructs tagged as list
        // TODO: can change grammar for actionList to be similar keyElementList
        public Node visitactionList(GNode n) {
            if(n.size() == 0) { // empty production
                return n;
            }

            // Since there can be any number of children with any number of actionRefs, go through the children
            Iterator itr = n.iterator();

            while(itr.hasNext()) {
                Object next = itr.next();
                if (next instanceof Syntax) { // final SEMICOLON
                    continue;
                }
                GNode nextNode = (GNode) next;
                if(nextNode.getName() == "actionList") {
                    dispatch(nextNode);
                } else if(nextNode.getName() == "optAnnotations") {
                    continue;
                } else if(nextNode.getName() == "actionRef") {
                    getNameUnderActionRefAndAddAsCallee(nextNode);
                } else if(nextNode.getName() == "Conditional") {
                    handleConditionalNodesUnderActionList(nextNode);
                } else {
                    assert false : "Unexpected value under actionList. Node name: " + nextNode.getName();
                }
            }

            return n;
        }

        // TODO: lvalue -- note why that doesn't matter for us, invkingexpression, expression

    };

    /**
     * Given an actionRef node, gets the name of the mentioned action and adds as callee
     * Separating this out from call graph visitor as it is reused by handleConditionalNodesUnderActionList
     * @param n actionRef node
     */
    public void getNameUnderActionRefAndAddAsCallee(GNode n) {
        assert n.getName() == "actionRef";

        String actionRefName = getStringUnderActionRef(n);
        lookupInSymTabAndAddAsCallee(actionRefName);
    }

    /**
     * Goes through conditional nodes and either calls the call graph visitor or adds actionRef as a callee
     * 
     * Specific for actionList node as it is tagged as list and will contain conditional nodes inside it
     * that wrap other grammar nodes.
     * @param n conditional node
     */
    // TODO: conditional node always has 2 children right?
    public void handleConditionalNodesUnderActionList(GNode n) {
        assert n.getName() == "Conditional";
        assert n.size() == 2;

        if (n.get(1) instanceof Syntax) { // final SEMICOLON
            return;
        }

        GNode insideNode = n.getGeneric(1);
        if(insideNode.getName() == "actionList") {
            callGraphVisitor.dispatch(insideNode);
        } else if(insideNode.getName() == "optAnnotations") {
            return;
        } else if(insideNode.getName() == "actionRef") {
            getNameUnderActionRefAndAddAsCallee(insideNode);
        } else if(insideNode.getName() == "Conditional") {
            handleConditionalNodesUnderActionList(insideNode);
        } else {
            assert false : "Unexpected value under actionList. Node name: " + insideNode.getName();
        }      
    }

    public String getNameFromTypeName(GNode n) {
        assert n.getName() == "typeName";

        // only child is prefixedType and that is used only under typeName
        n = n.getGeneric(0);

        // prefixedType can have just TYPE_IDENTIFIER or can be prefixed with a dot
        if(n.size() > 1) {
            // prefixed with a dot
            // TODO: handle cases where .TYPE_IDENTIFIER means something under scope
            return n.get(1).toString();
        } else {
            return n.get(0).toString();
        }
    }

    public String getNameOfControlBlock(GNode n) {
        assert n.getName() == "controlTypeDeclaration";

        // Third child node is the `name` construct
        return getStringUnderName(n.getGeneric(2));
    }

    public String getStringUnderName(GNode n) {
        assert n.getName() == "name";

        // child is either nonTypeName or TYPE_IDENTIFIER
        if(n.get(0) instanceof Syntax) {
            // TYPE_IDENTIFIER
            return n.get(0).toString();
        } else {
            // nonTypeName
            return getStringUnderNonTypeName(n.getGeneric(0));
        }
    }

    public String getStringUnderNonTypeName(GNode n) {
        assert n.getName() == "nonTypeName";

        // only terminals under nonTypeName, but right now only handling IDENTIFIER tokens, not reserved keywords
        assert (P4Tag.IDENTIFIER == ((Language) n.get(0)).tag() || n.get(0).toString() == "apply") : "non-IDENTIFIER terminals not supported under nonTypeName atm";
        return n.get(0).toString();
    }

    public String getStringUnderPrefixedNonTypeName(GNode n) {
        assert n.getName() == "prefixedNonTypeName";
        assert ! ((GNode) n.getGeneric(0)).getName().equals("dotPrefix") : "Retrieving nontypenames with a dot as a prefix not supported yet";

        return getStringUnderNonTypeName(n.getGeneric(0));
    }

    public String getPrefixedNonTypeNameFromLvalue(GNode n) {
        assert n.getName() == "lvalue";
        assert n.getGeneric(0) instanceof GNode && ((GNode) n.getGeneric(0)).getName() == "prefixedNonTypeName" : "lvalue construct not supported with values other than prefixedNonTypeName";

        return getStringUnderPrefixedNonTypeName(n.getGeneric(0));
    }

    public LanguageObject getMethodPrefixedNonTypeNameFromLvalue(Object node, Visitor visitor, LanguageObject scope) {
        if(node instanceof Syntax) {
            return scope;
        }

        assert node instanceof GNode;
        GNode n = (GNode) node;

        if(n.getName() == "prefixedNonTypeName") {
            String prefixedNonTypeName = getStringUnderPrefixedNonTypeName(n);
            LanguageObject pNTN = symtabLookup(scope, prefixedNonTypeName);
            return pNTN;
        } else if(n.getName() == "dot_name") {
            String dotName = getStringUnderDotName(n);
            LanguageObject name = symtabLookup(scope, dotName);
            return name;
        } else if(n.getName() == "expression") {
            // don't need to add current scope to the scope stack since the expression will be invoked under
            // the "main" scope and not the lvalue scope
            visitor.dispatch(n);
            return scope;
        } else if(n.getName() == "lvalue") {
            Iterator itr = n.iterator();

            while(itr.hasNext()) {
                scope = getMethodPrefixedNonTypeNameFromLvalue(itr.next(), visitor, scope);
            }
        } else {
            assert false : "hmm unhandled case in getMethodPrefixedNonTypeNameFromLvalue";
        }

        return scope;
    }

    public String getStringUnderDotName(GNode n) {
        return getStringUnderName(n.getGeneric(1));
    }

    public String getStringUnderFunctionPrototype(GNode n) {
        assert n.getName() == "functionPrototype";
        
        return getStringUnderName(n.getGeneric(1));
    }

    public String getStringUnderParserTypeDeclaration(GNode n) {
        assert n.getName() == "parserTypeDeclaration";

        return getStringUnderName(n.getGeneric(2));
    }

    public String getStringUnderActionRef(GNode n) {
        assert n.getName() == "actionRef";

        String prefixedNonTypeName = getStringUnderPrefixedNonTypeName(n.getGeneric(0));

        // TODO: parse argumentList?

        return prefixedNonTypeName;
    }

    public void printCallGraph() {
        for(LanguageObject key : symtab.keySet()) {
            System.out.println(key.toStringExtensive());
        }
    }
}

// Notes:
/*
L-value (lvalue) has a production that uses namespace to retrieve certain values (using the dot notation).
According to the language specification (section 6.6), only structure, header, and header union field member access operations
can happen using the dot notation. And none of productions can contain any type of function declaration and nothing inside those
productions can be invoked.
Hence it isn't necessary to traverse lvalue for call graphs, but is necessary for data flow analysis.


None of the grammar constructs (control, action, function, and parser) that define invokable blocks allow for nested declarations of the same type inside themselves.

*/