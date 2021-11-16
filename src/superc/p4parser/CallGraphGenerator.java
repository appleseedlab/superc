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

import javax.swing.LookAndFeel;
import javax.swing.plaf.synth.SynthLookAndFeel;
import javax.xml.stream.events.Namespace;

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
    // TODO: replace this with a constant LanguageObject global scope obj
    static String GLOBAL_SCOPE_NAME = "GLOBAL";
    // todo; remove these two
    static String APPLY_SCOPE_NAME = "APPLY";
    static String UNDEFINED_SCOPE = "UNDEFINED";
    LanguageObject undefined_scope = new LanguageObject(UNDEFINED_SCOPE, null);
    // what is this 
    HashSet<String> notExplicitlySupported = new HashSet<>(Arrays.asList("constantDeclaration",
                                                                         "tableDeclaration",
                                                                         "instantiation",
                                                                         "emptyStatement",
                                                                         "returnStatement",
                                                                         "exitStatement",
                                                                         "switchStatement",
                                                                         "functionPrototypes",
                                                                         "parserDeclaration",
                                                                         "invokingExpression"));
    //PC Scope

    public CallGraphGenerator() {
        this.symtab = new HashMap<>();
        this.scope = new Stack<>();

        // TODO: do a second run to map UNDEFINED scopes with blocks defined after
        // OR, first traverse declarations and then pass through for uses - separate call graph and declaration passes
        // OR in single pass, with flags to say declared or not (separate type checking pass)

        LanguageObject global_scope = new LanguageObject(GLOBAL_SCOPE_NAME, null);
        scope.add(global_scope);
    }

    // TODO: capitalize
    class LanguageObject {
        public String name;
        public LanguageObject nameSpace; //namespace TODO, make it immutable
        public HashSet<LanguageObject> callees;
        boolean visited; // TODO: remove

        public LanguageObject(String name, LanguageObject nameSpace) {
            this.name = name;
            this.nameSpace = nameSpace;
            callees = new HashSet<>();
            visited = false;
        }
        // TODO: overload hash function, pull out callees, overload toString and use that for hash function (same name under same namescope should have same hash value)
        // conditioned callees
    }

    /**
     * Adds the given block name and its language object to the given scope
     * 
     * @param scope
     * @param name
     * @param nodeObj
     */
    public void addToSymtab(LanguageObject scope, String name, LanguageObject nodeObj) {
        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        assert !symtab.get(scope).containsKey(name) : "Encountered an unexpected situation where trying to insert an existing value in scope. Scope: " + scope.name + ", value: " + name;

        symtab.get(scope).put(name, nodeObj);


        // Set<LanguageObject> currentSet = new HashSet<>();
        // currentSet.add(nodeObj);
        // if(! symtab.containsKey(scope)) {
        //     Map<String, Set<LanguageObject>> childObj = new HashMap<>();
        //     childObj.put(name, currentSet);
        //     symtab.put(scope, childObj);
        // } else {
        //     if(! symtab.get(scope).containsKey(name)) {
        //         symtab.get(scope).put(name, currentSet);
        //     } else {
        //         symtab.get(scope).get(name).add(nodeObj);
        //     }
        // }
    }

    // TODO: create a function to look up if the symbol exists rather than returning null

    // TODO: merge this with symtabLookup, make it recursive rather than while loop with global base case
    public LanguageObject retrieveFromSymtab(LanguageObject scope, String name) {
        assert scope != null : "Unexpected null scope during lookup";

        if( !symtab.containsKey(scope) ||
            ! symtab.get(scope).containsKey(name)) {
                return null;
        }
        // System.out.println("retrieveFromSymtab returning " + symtab.get(scope).get(name));
        return symtab.get(scope).get(name);
    }

    public LanguageObject symtabLookup(LanguageObject localScope, String typeName) {
        assert !typeName.isBlank() : "typeName is not supposed to be empty when looking it up on symbol table";

        LanguageObject retrievedObj = retrieveFromSymtab(localScope, typeName);

        while(retrievedObj == null && localScope.nameSpace != null) {
            localScope = localScope.nameSpace;
            retrievedObj = retrieveFromSymtab(localScope, typeName);
        }

        // assert retrievedObj != null : "Calling to an undefined symbol (" + typeName + ")";

        return retrievedObj;
    }

    // public LanguageObject symtabLookup(LanguageObject localScope, Node node) {
    //     // TODO: check getName
    //     System.out.println("symtablookup name: " + node.getName());
    //     System.out.println("node: " + node.toString());
    //     Object randomTry = visitor.dispatch(node.getGeneric(0));
    //     System.out.println("randomout: " + randomTry);
    //     for(LanguageObject key : symtab.keySet()) {
    //         System.out.print(key.name + ": ");
    //         for(String childKey : symtab.get(key).keySet()) {
    //             System.out.print(childKey + ", ");
    //         }
    //         System.err.println();
    //     }

    //     // LanguageObject retrievedObj = retrieveFromSymtab(localScope, node.getName());
    //     LanguageObject retrievedObj = symtabLookup(localScope, (String) randomTry);

    //     if(retrievedObj == null) {
    //         return null;
    //     }

    //     // if(! node.isEmpty()) {
    //     //     // TODO: check child names how it's handled
    //     //     assert node.get(0) instanceof Node : "Encountering case where node's child is not a node. Node's child is of class: " + node.get(0).getClass();
    //     //     return symtabLookup(retrievedObj, node.getGeneric(0));
    //     // } else {
    //         return retrievedObj;
    //     // }
    // }

    public void lookupInSymTabAndAddAsCallee(String name) {
        lookupInSymTabAndAddAsCallee(name, true);
    }

    // TODO: this will change when separating out call graph generation
    public void lookupInSymTabAndAddAsCallee(String name, boolean lookup) {
        // exists, add when doing only declarations

        LanguageObject callee = symtabLookup(scope.peek(), name);
        if(! lookup) {
            if(callee == null) {
                callee = new LanguageObject(name, undefined_scope);
            }
        }

        assert callee != null : "Calling to an undefined symbol when expecting it to be defined beforehand (" + name + ")";
        scope.peek().callees.add(callee);
    }

    public void doEverything(Node translationUnit) {
        visitor.dispatch(translationUnit.getGeneric(0));
    }

    private Visitor visitor = new Visitor() {
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
            LanguageObject controlObj = new LanguageObject(controlBlockName, scope.peek());

            addToSymtab(scope.peek(), controlBlockName, controlObj);
            scope.add(controlObj);

            // dispatch on rest of control child blocks
            Iterator itr = n.iterator();

            // Note: we do not skip visiting controlTypeDeclaration even though we externally retrieved
            // the name from it cause visitcontrolTypeDeclaration would do different operations

            dispatch(n.getGeneric(3)); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = n.getGeneric(5); // controlBody
            LanguageObject apply = new LanguageObject(applyBlockName, scope.peek());
            scope.peek().callees.add(apply); // edge between parent control block and this apply block
            addToSymtab(scope.peek(), applyBlockName, apply);
            scope.add(apply);

            dispatch(n.getGeneric(0)); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            return n;
        }

        // TODO: remove as handled by default visitor
        public Node visitcontrolLocalDeclaration(GNode n) {
            // if(n.getGeneric(0).getName().equals("actionDeclaration")) {
            //     dispatch(n.getGeneric(0)); //dispatch and not specific visit cause this will be dynamically dispatch when all children are supported
            // } else {
            //     System.err.println("Non-control declarations not supported at the moment");
            //     System.err.println("Unsupported block at: " + n);
            //     System.exit(1);
            // }
            dispatch(n.getGeneric(0));
            return n;
        }

        public Node visitdirectApplication(GNode n) {
            // As per the grammar we can have only one typename before the `.apply`, so nesting can't happen
            
            String calleeName = getNameFromTypeName(n.getGeneric(0));
            // TODO: below doesn't tell that it's also doing type checking, separate it out
            lookupInSymTabAndAddAsCallee(calleeName);
            // LanguageObject callee = symtabLookup(scope.peek(), calleeName);

            dispatch(n.getGeneric(4)); // argumentList

            // LanguageObject caller = scope.peek();
            // caller.callees.add(callee);
            // TODO: add callee under conditional edge

            return n;
        }

        public Node visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(n.getGeneric(2));
            LanguageObject actionObj = new LanguageObject(actionBlockName, scope.peek());

            addToSymtab(scope.peek(), actionBlockName, actionObj);
            scope.add(actionObj);

            dispatch(n.getGeneric(4)); // parameterList
            dispatch(n.getGeneric(6)); // TODO: blockStatement 

            scope.pop();

            return n;
        }

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

                String methodCalleeName = getPrefixedNonTypeNameFromLvalue(n.getGeneric(0));
                lookupInSymTabAndAddAsCallee(methodCalleeName);

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
            LanguageObject functionObj = new LanguageObject(functionName, scope.peek());

            addToSymtab(scope.peek(), functionName, functionObj);
            scope.add(functionObj);

            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return n;
        }

        public Node visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(n.getGeneric(0)); // TODO: take of parameter list here if needed to
            LanguageObject parserObj = new LanguageObject(parserName, scope.peek());
            addToSymtab(scope.peek(), parserName, parserObj);
            scope.add(parserObj);

            dispatch(n.getGeneric(3)); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(n.getGeneric(4)); // parserStates

            scope.pop();

            return n;
        }

        public Node visitparserState(GNode n) {
            String stateName = getStringUnderName(n.getGeneric(2));
            LanguageObject stateObj = new LanguageObject(stateName, scope.peek());
            addToSymtab(scope.peek(), stateName, stateObj);
            scope.add(stateObj);

            dispatch(n.getGeneric(4)); // parserStatements
            dispatch(n.getGeneric(5)); // transitionStatement

            scope.pop();
            
            return n;

        }

        public Node visitstateExpression(GNode n) {
            if(n.size() == 2) { // name SEMICOLON
                String stateName = getStringUnderName(n.getGeneric(0));
                lookupInSymTabAndAddAsCallee(stateName, false);
            } else { // selectExpression;
                dispatch(n.getGeneric(0));
            }
            return n;
        }

        public Node visitselectExpression(GNode n) {
            // TODO trace expressionList for data
            dispatch(n.getGeneric(5)); // selectCaseList - dynamic dispatch cause it's recursive
            return n;
        }

        public Node visitselectCase(GNode n) {
            // TODO trace keysetExpression for data

            String selectName = getStringUnderName(n.getGeneric(2));
            lookupInSymTabAndAddAsCallee(selectName, false);

            return n;
        }

        // TODO: functionprototype, extern declaration. lvalue, invkingexpression, expression

    };

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
        assert P4Tag.IDENTIFIER == ((Language) n.get(0)).tag() : "non-IDENTIFIER terminals not supported under nonTypeName atm";
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

    public String getStringUnderFunctionPrototype(GNode n) {
        assert n.getName() == "functionPrototype";
        
        return getStringUnderName(n.getGeneric(1));
    }

    public String getStringUnderParserTypeDeclaration(GNode n) {
        assert n.getName() == "parserTypeDeclaration";

        return getStringUnderName(n.getGeneric(2));
    }

    public void printCallGraph() {
        for(LanguageObject key : symtab.keySet()) {
            System.out.print(key.name + ": ");

            for(String childKey : symtab.get(key).keySet()) {
                System.out.print(childKey + "(" + (symtab.get(key).get(childKey).nameSpace == null ? "" : symtab.get(key).get(childKey).nameSpace.name) + ")");

                if(symtab.containsKey(childKey)) {
                    // System.err.println(childKey + " is in symtab");
                    System.out.print(", ");
                    continue;
                }

                ArrayList<String> calleeNames = new ArrayList<>();
                for(LanguageObject callee : symtab.get(key).get(childKey).callees) {
                    calleeNames.add(callee.name + "(" + (callee.nameSpace == null ? "" : callee.nameSpace.name) + ")");
                }

                if(! calleeNames.isEmpty()) {
                    System.out.print(": " + calleeNames.toString() + ", ");
                }
            }
            System.err.println();
        }
    }
}
