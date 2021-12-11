package superc.p4parser;
import java.lang.reflect.*;
import java.sql.CallableStatement;
import java.text.BreakIterator;
import java.time.LocalDate;
import java.lang.Iterable;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.io.File;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;
import java.util.concurrent.ThreadPoolExecutor.DiscardPolicy;

import javax.sound.midi.SysexMessage;
import javax.swing.plaf.synth.SynthLookAndFeel;
import javax.xml.crypto.dsig.spec.DigestMethodParameterSpec;

import superc.core.Syntax;
import superc.core.Syntax.Language;

import org.w3c.dom.NameList;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.Type;

import superc.core.PresenceConditionManager.PresenceCondition;
import superc.core.Syntax.Kind;
import superc.p4parser.P4Tag;
import superc.p4parser.GraphViz;

public class CallGraphGenerator {

    Map<LanguageObject, Map<String, LanguageObject>> symtab;
    Stack<LanguageObject> scope;
    LanguageObject global_scope = new LanguageObject("GLOBAL", null);
    LanguageObject undefined_scope = new LanguageObject("UNDEFINED", null);
    // A list of grammar constructs that are not yet supported and might contain invocation
    HashSet<String> notExplicitlySupported = new HashSet<>(Arrays.asList());
    private Map<BaseTypes, LanguageObject> baseTypeLanguageObjects = new HashMap<>();
    private Map<String, BaseTypes> baseTypeValues = new HashMap<>();

    // accept and reject are two parser states not defined by the user but is in the logic
    ArrayList<String> implicitParserStates = new ArrayList<>() {{
                                                                add("accept");
                                                                add("reject");
                                                               }};
    HashMap<LanguageObject, HashSet<LanguageObject>> callGraphObject;
    ArrayList<String> baseTypes = new ArrayList<>() {{
                                                        add("bool");
                                                        add("error");
                                                        add("bit");
                                                        add("string");
                                                        add("int");
                                                        add("varbit");
                                                    }};
    enum BaseTypes {
        BOOL("bool"),
        ERROR("error"),
        BIT("bit"),
        STRING("string"),
        INT("int"),
        VARBIT("varbit");


        public String baseString;

        private BaseTypes(String typeString) {
            this.baseString = typeString;
        }
    }

    
    public BaseTypes valueOfBaseType(String typeString) {
        return baseTypeValues.get(typeString);
    }

    public boolean isBaseType(String typeString) {
        return baseTypeValues.containsKey(typeString);
    }

    public Map<String, BaseTypes> getBaseTypeValues() {
        return this.baseTypeValues;
    }

    //PC Scope

    public CallGraphGenerator() {
        this.symtab = new HashMap<>();
        this.scope = new Stack<>();
        this.callGraphObject = new HashMap<>();

        for (BaseTypes e: BaseTypes.values()) {
            baseTypeValues.put(e.baseString, e);
            baseTypeLanguageObjects.put(e, new LanguageObject(e.baseString, global_scope));
        }

        scope.add(global_scope);
    }

    public LanguageObject getLanguageObjectForBaseType(String typeString, LanguageObject scope) {
        assert baseTypeValues.containsKey(typeString) : "Not a type string. Assuming that the passed in value has been previously check if it a valid base type";
        LanguageObject check = baseTypeLanguageObjects.get(BaseTypes.BIT);
        return baseTypeLanguageObjects.get(baseTypeValues.get(typeString));
    }

    // For symbols
    class LanguageObject {
        public final String name;
        public final LanguageObject nameSpace;
        // TODO MAIN: take care of parametrization and typedef (check xor example)

        // Store the type of the object if the current object is a typedef (type or parameter)
        // Three supported classes at the moment: String (base type) and LanguageObject (previously defined) and boolean (for initialization)
        LanguageObject type;
        Boolean isOfType;
        Boolean isScope;

        // TODO: instead of null for type, make a global object for no type and use that?
        public LanguageObject(String name, LanguageObject nameSpace) {
            this(name, nameSpace, null, false);
        }
        public LanguageObject(String name, LanguageObject nameSpace, LanguageObject type) {
            this(name, nameSpace, type, false);
        }
        public LanguageObject(String name, LanguageObject nameSpace, Boolean scope) {
            this(name, nameSpace, null, scope);
        }

        // Construct with all fields
        public LanguageObject(String name, LanguageObject nameSpace, LanguageObject type,
                              Boolean scope) {
            this.name = name;
            this.nameSpace = nameSpace;
            this.type = type;
            if(type != null) {
                this.isOfType = true;
            } else {
                this.isOfType = false;
            }
            this.isOfType = scope;
        }

        public String getNameSpaceString() {
            if(this == global_scope) {
                return name;
            }
            
            return this.nameSpace.name;
        }

        @Override
        public String toString() {
            // For simple toString calls where the current value is not present under the symbol table
            if(this == global_scope) {
                return name;
            }
            
            return name + "(" + this.getNameSpaceString() + ")";
        }

        public boolean isType() {
            return isOfType;
        }

        public boolean isBaseType() {
            return (isType() && baseTypes.contains(this.type));
        }

        public Object getType() {
            return type;
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
                LanguageObject childLangObj = symtab.get(this).get(childKey);
                finalString += childLangObj.toString();
                if(symtab.containsKey(childLangObj)) {
                    finalString += itr.hasNext() ? ", " : "";
                    continue;
                }

                ArrayList<String> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(LanguageObject callee : callGraphObject.get(childLangObj)) {
                        calleeNames.add(callee.toString());
                    }
                }

                if(! calleeNames.isEmpty()) {
                    finalString += ": " + calleeNames.toString();
                }
                finalString += (itr.hasNext() ? ", " : "");
            }

            return finalString;
        }

        public String toDotString() {
            String finalString = "";

            Iterator<String> itr = symtab.get(this).keySet().iterator();
            finalString += this.hashCode() + ";";
            finalString += this.hashCode() + " [label=\"" + this.name + "\"];";
            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                LanguageObject childLangObj = symtab.get(this).get(childKey);
                finalString += this.hashCode() + " -> " + childLangObj.hashCode() + " [style=dashed, color=blue];";
                finalString += childLangObj.hashCode() + " [label=\"" + childLangObj.name + "\"];";

                if(symtab.containsKey(childLangObj)) {
                    continue;
                }

                ArrayList<LanguageObject> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(LanguageObject callee : callGraphObject.get(childLangObj)) {
                        calleeNames.add(callee);
                    }
                }

                if(! calleeNames.isEmpty()) {
                    for(LanguageObject localCallee : calleeNames) {
                        finalString += childLangObj.hashCode() + "->" + localCallee.hashCode() + ";";
                        finalString += localCallee.hashCode() + " [label=\"" + localCallee.name + "\"];";
                    }
                }

            }

            // finalString += this.hashCode() + " [label=\"" + this.name + "\"]";
            // System.out.println(finalString);
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
                hashString += this.getParentNameSpaces() + "/";
            }
            hashString += this.name;
            
            return hashString.hashCode();
        }

        public String getParentNameSpaces() {
            String ancestorNameSpace = "";
            LanguageObject currentNameSpace = this.nameSpace;
            if(this == global_scope || currentNameSpace == global_scope) {
                return "GLOBAL";
            }

            while(currentNameSpace != global_scope) {
                ancestorNameSpace += (ancestorNameSpace.isBlank() ? "" : "/");
                ancestorNameSpace += currentNameSpace.name;
                currentNameSpace = currentNameSpace.nameSpace;
            }

            return ancestorNameSpace;
        }
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
        return addToSymtab(scope, name, null, false);
    }
    public LanguageObject addToSymtab(LanguageObject scope, String name, LanguageObject type, Boolean isScoped) {
        LanguageObject nodeObj = null;

        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        if(symtab.get(scope).containsKey(name)) {
            // System.err.println("Multiple declaration error: another entity with the same name (" 
            //                     + name + 
            //                     ") already exists");
            // System.exit(1);
            System.out.println("Warning: defining with an already existing name ("
                                + name + ").");
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

    /**
     * Looks up the given name in the symbol table and adds it as a callee to the current scope.
     * @param name The name of the symbol to look up
     */
    public void lookupInSymTabAndAddAsCallee(String name) {

        // looks up in the symbol table under the current scope
        // if not in current scope, checks under parent scopes.
        LanguageObject callee = symtabLookup(scope.peek(), name);

        assert callee != null : "UNCAUGHT Calling to an undefined symbol when expecting it to be defined beforehand (" + name + ")";
        if( !callGraphObject.containsKey(scope.peek())) {
            callGraphObject.put(scope.peek(), new HashSet<>());
        }
        callGraphObject.get(scope.peek()).add(callee);
    }

    public void buildSymbolTable(Node translationUnit) {
        definitionsVisitor.dispatch(translationUnit.getGeneric(0));
    }

    public void buildCallGraph(Node translationUnit) {
        callGraphVisitor.dispatch(translationUnit.getGeneric(0));
    }

    public void createCallGraphVisual(String fileName) {
        String dotFormat = toDot();
        createDotGraph(dotFormat, fileName);
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

                    // assert ((PresenceCondition) nextObj).getAllConfigs().size() == 0 : "non-empty PresenceCondition nodes not supported at the moment";
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
            dispatch(n.getGeneric(6)); // blockStatement

            scope.pop();

            return n;
        }

        // follow similar as last time (break into three different grammar constructs)
        // . member values has structfield list inside it, so no function calls inside it - but matters for data flow
        // header functions - push_front
        public Node visitassignmentOrMethodCallStatement(GNode n) {
            if(n.getGeneric(0).getName() == "methodCallStatements") {
                // method call statements
                dispatch(n.getGeneric(0));
            } else {
                // assignment statement
                // TODO: need to assert that this lvalue call does not invoke functions
                dispatch(n.getGeneric(0)); // lvalue
                dispatch(n.getGeneric(2)); // expression
            }
            return n;
        }

        public Node visitmethodCallStatements(GNode n) {
            dispatch(n.getGeneric(0)); // lvalue

            // There are two possible set of sub productions, both which have argument list under it
            // but one has typeArgumentList before argument list, so argumentList is not at the same place
            // hence check the size to see which production we are currently under and dispatching
            // the visitor at the respective argumentList position
            if(n.size() == 5) {
                dispatch(n.getGeneric(2)); //argumentlist
            } else { 
                dispatch(n.getGeneric(5)); // argumentList
            }

            return n;
        }

        // TODO: finish ensureDotValueIsOnlySpecificConstructs and check logic (like .apply()?)
        public Node visitlvalue(GNode n) {
            if(n.get(0) instanceof Syntax) { // keyword "THIS"
                return n;
            }

            switch(n.getGeneric(0).getName()) {
                case "prefixedNonTypeName":
                    break;
                case "lvalue":
                    dispatch(n.getGeneric(0));
                    if(n.getGeneric(1).getName() == "dot_name") {
                        // as per the grammar specifications, lvalue dot values can only be used for structs, headers, and header union fields.
                        // so ensuring that's the case
                        // note: can also be nonTypeName (apply, key, actions,...)  - apply is an invocation
                        // TODO: figure out key, actions...
                        // TODO: can we do controlblock.functioname?
                        // note: if name is type_identifier, then ensure its of one of those constructs
                        // TODO: change LanguageObject to include what constructs to check for this
                        ensureDotValueIsOnlySpecificConstructs(n.getGeneric(1));
                    } else {
                        dispatch(n.getGeneric(1)); // lvalueExpression
                    }
                    break;
                default:
                    assert false : "Unhandled lvalue first element: " + n.getGeneric(0).getName();
            }

            return n;
        }

        public Node visitlvalueExpression(GNode n) {
            // Two possible productions:
            // L_BRACKET expression R_BRACKET - size 3
            // L_BRACKET expression COLON expression R_BRACKET - size 5

            dispatch(n.getGeneric(1)); // always expression 

            if(n.size() == 5) { // L_BRACKET expression COLON expression R_BRACKET
                dispatch(n.getGeneric(3)); // expression
            }

            return n;
        }

        public Node visitexternDeclaration(GNode n) {
            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "externFunctionDeclaration") { // separate dispatch available for this
                // TODO: check if externFunctionDeclaration can be merged back again
                dispatch(returnSecondChildIfConditional(n.getGeneric(0)));
                return n;
            } else {
                if(returnSecondChildIfConditional(n.getGeneric(2)).getName() == "nonTypeName") {
                    String externName = getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(2)));
                    LanguageObject externObj = addToSymtab(scope.peek(), externName);
                    scope.add(externObj);

                    dispatch(n.getGeneric(3)); // optTypeParameters
                    dispatch(n.getGeneric(5)); // methodPrototypes

                    scope.pop();
                } else { // only option left is "optAnnotations EXTERN name SEMICOLON" production
                    assert returnSecondChildIfConditional(n.getGeneric(2)).getName() == "name" : "Unhandled case in extern declarations";
                    String externName = getStringUnderName(returnSecondChildIfConditional(n.getGeneric(2)));
                    LanguageObject externObj = addToSymtab(scope.peek(), externName);
                }

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

            dispatch(n.getGeneric(0)); // functionPrototype (for parameters)
            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return n;
        }

        public Node visitmethodPrototype(GNode n) {
            /* methodPrototype
                optAnnotations functionPrototype SEMICOLON
                optAnnotations ABSTRACT functionPrototype SEMICOLON
                constructorMethodPrototype

               constructorMethodPrototype:
                optAnnotations TYPE_IDENTIFIER L_PAREN parameterList R_PAREN SEMICOLON

               Where last one is a constructor 
            */

            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "constructorMethodPrototype") {
                dispatch(returnSecondChildIfConditional(n.getGeneric(0)));
            } else if(n.get(1) instanceof Syntax) { // keyword ABSTRACT
                // TODO: need to handle abstract methods
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(2)));
                LanguageObject functionObj = addToSymtab(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(returnSecondChildIfConditional(n.getGeneric(2)));

                scope.pop();
            } else {
                assert returnSecondChildIfConditional(n.getGeneric(1)).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(1)));
                LanguageObject functionObj = addToSymtab(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(returnSecondChildIfConditional(n.getGeneric(1)));

                scope.pop();
            }

            return n;
        }

        public Node visitconstructorMethodPrototype(GNode n) {            
            String type_identifier = n.get(1).toString();
            // System.out.println("constructor inside: " + type_identifier);

            // methodPrototype -> constructorMethodPrototype is directly under parent extern scope
            // so can retrieve the extern block's name from the scope
            // TODO: check if there is a better way

            assert type_identifier.equals(scope.peek().name) : "Extern constructor not of the same name as extern block";
            LanguageObject constructor = addToSymtab(scope.peek(), type_identifier);
            scope.add(constructor);

            dispatch(n.getGeneric(3)); // parameterList

            scope.pop();

            return n;
        }

        // public Node visitparameter(GNode n) {
        //     dispatch(n.getGeneric(0)); // optAnnotations

        //     String type_ref_string = getTypeStringUnderTypeRef(n.getGeneric(2));
        //     String name = getStringUnderName(n.getGeneric(3));

        //     LanguageObject parameterObj = addToSymtab(scope.peek(), name);

        //     if(baseTypes.contains(type_ref_string)) {
        //         parameterObj.type = type_ref_string;
        //     } else {
        //         LanguageObject typeObj = symtabLookup(scope.peek(), type_ref_string);
        //         parameterObj.type = typeObj;
        //     }

        //     if(n.size() == 6) {
        //         // "optAnnotations direction typeRef name ASSIGN expression {}" productiom
        //         // so need to take care of expression
        //         // The other production is just "optAnnotations direction typeRef name"
        //         dispatch(n.getGeneric(5));
        //     }

        //     return n;
        // }

        // public Node visittypeParameterList(GNode n) {
        //     /*
        //     Two possible productions:
        //         name
        //         typeParameterList COMMA name ----- recursive
        //     */

        //     if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "typeParameterList") {
        //         // typeParameterList COMMA name ----- recursive
        //         dispatch(n.getGeneric(0));
        //         String name = getStringUnderName(returnSecondChildIfConditional(n.getGeneric(2)));
        //         addToSymtab(scope.peek(), name);
        //     } else {
        //         // just 'name'
        //         String name = getStringUnderName(returnSecondChildIfConditional(n.getGeneric(0)));
        //         addToSymtab(scope.peek(), name);
        //     }

        //     return n;
        // }

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

        // extern function declarations are invokable constructs as per the language specs
        // so keeping track of that in the symbol table for future invocations
        public Node visitexternFunctionDeclaration(GNode n) {
            // TODO: take care of parameters (inside functionPrototype and in general)
            String functionName = getStringUnderFunctionPrototype(n.getGeneric(2));
            LanguageObject functionObj = addToSymtab(scope.peek(), functionName);

            return n;
        }
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

                    // assert ((PresenceCondition) nextObj).getAllConfigs().size() == 0 : "non-empty PresenceCondition nodes not supported at the moment";
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
            dispatch(n.getGeneric(6)); // blockStatement 

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

            dispatch(n.getGeneric(0)); // functionPrototype (for parameters)
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

        public Node visitexternDeclaration(GNode n) {
            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "externFunctionDeclaration") { // generic dispatch
                dispatch(returnSecondChildIfConditional(n.getGeneric(0)));
                return n;
            } else {
                if(returnSecondChildIfConditional(n.getGeneric(2)).getName() == "nonTypeName") {
                    String externName = getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(2)));
                    LanguageObject externObj = symtabLookup(scope.peek(), externName);
                    scope.add(externObj);

                    dispatch(n.getGeneric(3)); // optTypeParameters
                    dispatch(n.getGeneric(5)); // methodPrototypes

                    scope.pop();
                }

                return n;
            }
        }

        public Node visitmethodPrototype(GNode n) {
            /* methodPrototype
                optAnnotations functionPrototype SEMICOLON
                optAnnotations ABSTRACT functionPrototype SEMICOLON
                constructorMethodPrototype

               constructorMethodPrototype:
                optAnnotations TYPE_IDENTIFIER L_PAREN parameterList R_PAREN SEMICOLON

               Where last one is a constructor 
            */

            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "constructorMethodPrototype") {
                dispatch(n.getGeneric(0));
            } else if(n.get(1) instanceof Syntax) { // keyword ABSTRACT
                dispatch(n.getGeneric(0)); // optAnnotations

                // TODO: need to handle abstract methods
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(2)));
                LanguageObject functionObj = symtabLookup(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(n.getGeneric(2));

                scope.pop();
            } else {
                assert returnSecondChildIfConditional(n.getGeneric(1)).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(1)));
                LanguageObject functionObj = symtabLookup(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(n.getGeneric(1));

                scope.pop();
            }

            return n;
        }

        public Node visitconstructorMethodPrototype(GNode n) {            
            String type_identifier = n.get(1).toString();

            // methodPrototype -> constructorMethodPrototype is directly under parent extern scope
            // so can retrieve the extern block's name from the scope
            // TODO: check if there is a better way

            assert type_identifier.equals(scope.peek().name) : "Extern constructor not of the same name as extern block";
            LanguageObject constructor = symtabLookup(scope.peek(), type_identifier);
            scope.add(constructor);

            dispatch(n.getGeneric(3)); // parameterList

            scope.pop();

            return n;
        }

        public Node visitdirectApplication(GNode n) {
            // As per the grammar we can have only one typename before the `.apply`, so nesting can't happen
            
            String calleeName = getNameFromTypeName(n.getGeneric(0));

            lookupInSymTabAndAddAsCallee(calleeName);

            // dispatch(n.getGeneric(4)); // argumentList

            return n;
        }

        public Node visitassignmentOrMethodCallStatement(GNode n) {
            if(n.getGeneric(0).getName() == "methodCallStatements") {
                // method call statements
                dispatch(n.getGeneric(0));
            } else { // TODO: make clear which production
                dispatch(n.getGeneric(0)); // lvalue
                dispatch(n.getGeneric(2)); // expression
            }

            return n;
        }

        public Node visitmethodCallStatements(GNode n) {
            dispatch(n.getGeneric(0)); // lvalue

            // only legal value of lvalue for method call statements is prefixedNonTypeName
            // with dot_name as lvalueExpressions cannot be used for method call statements
            // (see end of document). getStringUnderLvaluePrefixNonTypeName asserts that
            String calleeMethodName = getStringUnderLvaluePrefixNonTypeName(n.getGeneric(0));
            lookupInSymTabAndAddAsCallee(calleeMethodName);

            // There are two possible set of sub productions, both which have argument list under it
            // but one has typeArgumentList before argument list, so argumentList is not at the same place
            // hence check the size to see which production we are currently under and dispatching
            // the visitor at the respective argumentList position
            if(n.size() == 5) {
                dispatch(n.getGeneric(2)); //argumentlist
            } else { 
                dispatch(n.getGeneric(5)); // argumentList
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
                if( !implicitParserStates.contains(stateName)) {
                    lookupInSymTabAndAddAsCallee(stateName);
                }
            } else { // selectExpression;
                dispatch(n.getGeneric(0));
            }
            return n;
        }

        public Node visitselectCase(GNode n) {
            // TODO trace keysetExpression for data
            dispatch(n.getGeneric(0)); // keysetExpression

            String selectName = getStringUnderName(n.getGeneric(2));
            if ( !implicitParserStates.contains(selectName)) {
                lookupInSymTabAndAddAsCallee(selectName);
            }

            return n;
        }

        public Node visitaction(GNode n) {
            String actionRefName = getNameUnderActionRef(n.getGeneric(1), this);
            lookupInSymTabAndAddAsCallee(actionRefName);

            return n;
        }

        public Node visitinvokingExpression(GNode n) {
            GNode nGetGeneric0 = returnSecondChildIfConditional(n.getGeneric(0));
            if(nGetGeneric0.getName() == "namedType") {
                // one of three possible productions, starts with namedType
                String namedType = getStringUnderNamedType(nGetGeneric0);
                lookupInSymTabAndAddAsCallee(namedType);

                dispatch(returnSecondChildIfConditional(n.getGeneric(2))); // argumentList
            } else { // first element pointing to name is an expression, extract from that
                LanguageObject expressionCallee = getCalleeFromExpression(nGetGeneric0);
                callGraphObject.get(scope.peek()).add(expressionCallee);

                // two possible productions, one contains extra set of type arguments 
                // inside angle brackets (of size 4 & 7)
                if(n.size() == 4) {
                    dispatch(returnSecondChildIfConditional(n.getGeneric(2))); // argumentList
                } else {
                    dispatch(returnSecondChildIfConditional(n.getGeneric(4)));
                    // TODO: data inside realTypeArguments? can refer nontypenames
                }
            }

            return n;
        }

        public Node visitinvokingNonBraceExpression(GNode n) {
            GNode nGetGeneric0 = returnSecondChildIfConditional(n.getGeneric(0));
            if(nGetGeneric0.getName() == "namedType") {
                // one of three possible productions, starts with namedType
                String namedType = getStringUnderNamedType(nGetGeneric0);
                lookupInSymTabAndAddAsCallee(namedType);

                dispatch(returnSecondChildIfConditional(n.getGeneric(2))); // argumentList
            } else { // first element pointing to name is an expression, extract from that
                LanguageObject expressionCallee = getCalleeFromNonBraceExpression(nGetGeneric0);
                callGraphObject.get(scope.peek()).add(expressionCallee);

                // two possible productions, one contains extra set of type arguments 
                // inside angle brackets (of size 4 & 7)
                if(n.size() == 4) {
                    dispatch(returnSecondChildIfConditional(n.getGeneric(2))); // argumentList
                } else {
                    dispatch(returnSecondChildIfConditional(n.getGeneric(4)));
                    // TODO: data inside realTypeArguments? can refer nontypenames
                }
            }

            return n;
        }
    };

    /**
     * Given an actionRef node, gets the name of the mentioned action and returns that
     * @param n actionRef node
     * @return Returns the String present under the actionRef
     */
    public String getNameUnderActionRef(GNode n, Visitor visitor) {
        assert n.getName() == "actionRef";

        String actionRefName = getStringUnderPrefixedNonTypeName(n.getGeneric(0));

        if(n.size() > 1) {
            visitor.dispatch(n.getGeneric(2)); // argumentList
        }

        return actionRefName;
    }

    // nonTypeName, dotPrefix nonTypeName, typeName dot_name, expression dot_name
    // Note: `NOT expression` will be taken care of by recursion
    /**
     * Handles possible expressions that can be used to invoke an entity.
     * 
     * Specifically invoked when the expression is inside an invoking expression
     * and is invoking a previously declared entity (callee).
     * Handles those possible expressions, including namespacing if present, and adds
     * the invoked entity as a call to the current scope object.
     * @param n
     * @return
     */
    public LanguageObject getCalleeFromExpression(GNode n) {
        assert n.getName() == "expression" : "current name is: " + n.getName();

        if(n.get(0) instanceof Syntax) { // NOT expression
            assert n.get(0).toString() == "!";
            return getCalleeFromExpression(n.getGeneric(1));
        }

        assert ((Node) n.get(0)).isGeneric();

        String dotNameString;
        boolean currentConditionalFlag = false;
        do {
            currentConditionalFlag = false;
            GNode firstChild = n.getGeneric(0);
            if(n.getGeneric(0).getName() == "Conditional") {
                firstChild = getNodeUnderConditional(n.getGeneric(0));
            }
            switch(firstChild.getName()) {
                case "nonTypeName":
                    // nonTypeName
                    return symtabLookup(scope.peek(), getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                case "dotPrefix":
                    // dotPrefix nonTypeName
                    // TODO: namespacing?
                    assert n.size() > 1;
                    return symtabLookup(scope.peek(), getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(1))));
                case "typeName":
                    // typeName dot_name
                    // doing namespacing
                    LanguageObject typeNameLO = symtabLookup(scope.peek(), getNameFromTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(typeNameLO, dotNameString);
                case "expression":
                    // expression dot_name
                    // namespace
                    assert n.size() == 2 && n.getGeneric(1).getName() == "dot_name";
                    LanguageObject expressionLO = getCalleeFromExpression(returnSecondChildIfConditional(n.getGeneric(0)));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(expressionLO, dotNameString);
                default:
                    assert false : "Encountered a situation where expression inside invoking expression was not of expected value";
            }
        } while(currentConditionalFlag);

        assert false : "should not be reaching this place";
        return symtabLookup(scope.peek(), n.getName());
    }

    // nonTypeName, dotPrefix nonTypeName, typeName dot_name, expression dot_name
    // Note: `NOT expression` will be taken care of by recursion
    /**
     * Handles possible expressions that can be used to invoke an entity.
     * Similar to getCalleeFromExpression
     * 
     * Specifically invoked when the expression is inside an invoking expression
     * and is invoking a previously declared entity (callee).
     * Handles those possible expressions, including namespacing if present, and adds
     * the invoked entity as a call to the current scope object.
     * @param n
     * @return
     */
    public LanguageObject getCalleeFromNonBraceExpression(GNode n) {
        assert n.getName() == "expression" : "current name is: " + n.getName();

        if(n.get(0) instanceof Syntax) { // NOT expression
            assert n.get(0).toString() == "!";
            return getCalleeFromExpression(n.getGeneric(1));
        }

        assert ((Node) n.get(0)).isGeneric();

        String dotNameString;
        boolean currentConditionalFlag = false;
        do {
            currentConditionalFlag = false;
            GNode firstChild = n.getGeneric(0);
            if(n.getGeneric(0).getName() == "Conditional") {
                firstChild = getNodeUnderConditional(n.getGeneric(0));
            }
            switch(firstChild.getName()) {
                case "nonTypeName":
                    // nonTypeName
                    return symtabLookup(scope.peek(), getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                case "dotPrefix":
                    // dotPrefix nonTypeName
                    // TODO: namespacing?
                    assert n.size() > 1;
                    return symtabLookup(scope.peek(), getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(1))));
                case "typeName":
                    // typeName dot_name
                    // doing namespacing
                    LanguageObject typeNameLO = symtabLookup(scope.peek(), getNameFromTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(typeNameLO, dotNameString);
                case "expression":
                    // nonBraceExpression dot_name
                    // namespace
                    assert n.size() == 2 && n.getGeneric(1).getName() == "dot_name";
                    LanguageObject expressionLO = getCalleeFromNonBraceExpression(returnSecondChildIfConditional(n.getGeneric(0)));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(expressionLO, dotNameString);
                default:
                    assert false : "Encountered a situation where expression inside invoking expression was not of expected value";
            }
        } while(currentConditionalFlag);

        assert false : "should not be reaching this place";
        return symtabLookup(scope.peek(), n.getName());
    }

    public GNode returnSecondChildIfConditional(GNode n) {
        if(n.getName() == "Conditional") {
            // since first child is the presence condition
            return n.getGeneric(1);
        } else {
            return n;
        }
    }

    public GNode getNodeUnderConditional(GNode n) {
        assert n.getName() == "Conditional";

        return n.getGeneric(1);
    }

    public String getStringUnderNamedType(GNode n) {
        assert n.getName() == "namedType";

        if(n.getGeneric(0).getName() == "typeName") { // typeName
            return getNameFromTypeName(n.getGeneric(0));
        } else { //specializedType
            return getStringUnderSpecializedTypeName(n.getGeneric(0));
        }
    }

    public String getStringUnderSpecializedTypeName(GNode n) {
        assert n.getName() == "specializedType";

        // TODO: take care of typeArgumentList

        return getNameFromTypeName(n.getGeneric(0));
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

    // TODO: !! (need to change LanguageObject to include which construct each symbol is from)
    public void ensureDotValueIsOnlySpecificConstructs(GNode n) {
        assert true;
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
        // System.out.println(n.toString());
        // System.out.println(n.get(0));
        // System.out.println(((Language) n.get(0)).tag());
        // only terminals under nonTypeName, but right now only handling IDENTIFIER tokens, not reserved keywords
        assert (P4Tag.IDENTIFIER == ((Language) n.get(0)).tag() || n.get(0).toString() == "apply") : "non-IDENTIFIER terminals not supported under nonTypeName atm";
        return n.get(0).toString();
    }

    public String getStringUnderPrefixedNonTypeName(GNode n) {
        assert n.getName() == "prefixedNonTypeName";
        assert ! ((GNode) n.getGeneric(0)).getName().equals("dotPrefix") : "Retrieving nontypenames with a dot as a prefix not supported yet";

        return getStringUnderNonTypeName(n.getGeneric(0));
    }

    /**
     * Assert that only syntactically legal values are present for method call statements.
     * Returns the string present.
     * @param n Parent GNode containing the lvalue construct
     * @return
     */
    public String getStringUnderLvaluePrefixNonTypeName(GNode n) {
        // only legal value of lvalue for method call statements is prefixedNonTypeName
        // as dot_name and lvalueExpressions cannot be used for method call statements
        // (see end of document)

        assert n.getName() == "lvalue";
        assert n.get(0) instanceof Node && ((Node) n.get(0)).isGeneric();

        GNode firstChild = n.getGeneric(0);
        if(firstChild.getName() == "lvalue") {
            return traverseLvalueAndGetStringUnderPrefixedNonTypeName(n);
        } else if(firstChild.getName() == "prefixedNonTypeName") {
            return getStringUnderPrefixedNonTypeName(firstChild);
        } else {
            assert false : "unhandled case in getStringUnderLvaluePrefixNonTypeName where first value name is: " + firstChild.getName();
            return "";
        }
    }

    /**
     * Handles recursive cases where a prefixedNonTypeName is expected but buried under
     * recursive lvalue constructs
     * @param n
     * @return
     */
    public String traverseLvalueAndGetStringUnderPrefixedNonTypeName(GNode n) {
        int size = n.size();
        String final_val = "";
        for(int i = 0; i < size; i++) {
            if(n.getGeneric(i).getName() == "lvalue") {
                final_val = traverseLvalueAndGetStringUnderPrefixedNonTypeName(n.getGeneric(i));
            } else if(n.getGeneric(i).getName() == "prefixedNonTypeName") {
                return getStringUnderPrefixedNonTypeName(n.getGeneric(i));
            } else if(n.getGeneric(i).getName() == "dot_name") {
                assert n.getGeneric(i).getGeneric(1).getName() == "name";
                assert n.getGeneric(i).getGeneric(1).get(0) instanceof Syntax == false : "dot_name under a lvalue construct used in a method call statement cannot invoke a type identifier";
            } else if(n.getGeneric(i).getName() == "lvalueExpression") {
                assert false : "lvalueExpression cannot be used in an method calling statement";
            }
        }

        assert !final_val.isBlank() : "Unable to retrieve string under a nested lvalue structure";

        return final_val;
    }

    public String getTypeStringUnderTypeRef(GNode n) {
        assert n.getName() == "typeRef";
        
        switch(n.getGeneric(0).getName()) {
            case "typeName":
                return getNameFromTypeName(n.getGeneric(0));
            case "baseType":
                return getBaseTypeAsString(n.getGeneric(0));
            case "specializedType":
                return getStringUnderSpecializedTypeName(n.getGeneric(0));
            case "headerStackType":
                return getStringUnderHeaderStackType(n.getGeneric(0));
            case "tupleType":
                return "tuple"; // TODO: example cases and figure out tuple nesting
            default:
                System.err.println("Unhandled new case for typeRef");
                System.exit(1);
        }

        return "Unhandled case under type ref";
    }

    public String getBaseTypeAsString(GNode n) {
        assert n.getName() == "baseType";

        // handle expressions within basetype
        return n.get(0).toString();
    }

    public String getStringUnderHeaderStackType(GNode n) {
        assert n.getName() == "headerStackType";

        // TODO: handle expression inside
        if(n.getGeneric(0).getName() == "typeName") {
            return getNameFromTypeName(n.getGeneric(0));
        } else if(n.getGeneric(0).getName() == "specializedType") {
            return getStringUnderSpecializedTypeName(n.getGeneric(0));
        } else {
            System.err.println("Unhandled header stack type case");
            System.exit(1);
        }

        return "Unhandled case under header stack type";
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
        // System.out.println(callGraphObject);
    }

    public String toDot() {
        String dotFormat = "";
        for(LanguageObject key : symtab.keySet()) {
            dotFormat += key.toDotString();
        }

        // System.out.println(dotFormat);
        return dotFormat;
    }
    
    public static void createDotGraph(String dotFormat,String fileName) {
        String check = "{rank=same; a1, b1 } {rank=same; a2, b2 } a1 [label=\"This defines\"] a2 [label=\"This calls\"] b1 [label=\"this\"] b2 [label=\"this\"] a1 -> b1 [ minlen=4 ] a2 -> b2 [ style=dashed, color=blue, minlen=4 ]";
        dotFormat += check;
        GraphViz gv=new GraphViz();
        gv.addln(gv.start_graph());
        gv.add(dotFormat);
        gv.addln(gv.end_graph());
       // String type = "gif";
        String type = "pdf";
      // gv.increaseDpi();
        gv.decreaseDpi();
        gv.decreaseDpi();
        // System.out.println(gv.toString());
        File out = new File(fileName+"."+ type); 
        gv.writeGraphToFile( gv.getGraph( gv.getDotSource(), type ), out );
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

Expressions.
Possible expressions that can be present in an invocation (invokingExpression).
nonTypeName, dotPrefix nonTypeName, typeName dot_name, expression dot_name
Note: `NOT expression` will be taken care of by recursion
Note: Multiple declarations of same name: cannot occur.
Note: Overloading is possible for functions and method (language specification, 7.2.9.2)
*/