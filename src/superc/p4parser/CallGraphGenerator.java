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
import java.util.function.Function;

import javax.sound.midi.SysexMessage;
import javax.swing.plaf.synth.SynthLookAndFeel;
import javax.xml.crypto.dsig.spec.DigestMethodParameterSpec;

import superc.core.Syntax;
import superc.core.Syntax.Language;
import superc.p4parser.*;
import superc.p4parser.P4LanguageObject.*;
import superc.p4parser.P4LanguageObject.Parameter;
import superc.p4parser.P4LanguageObject.LanguageObject;
import superc.p4parser.P4LanguageObject.ConstantTreeGlobalObjects;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.Type;

import superc.core.PresenceConditionManager.PresenceCondition;
import superc.core.Syntax.Kind;
import superc.p4parser.P4Tag;
import superc.p4parser.GraphViz;
// import superc.p4parser.AbstractObjectOfLanguage;

public class CallGraphGenerator {

    private static final P4LanguageObject p4LanguageObject = new P4LanguageObject();
    public static final AbstractObjectOfLanguage global_scope = p4LanguageObject.new ConstantTreeGlobalObjects("GLOBAL");
    public static final AbstractObjectOfLanguage undefined_scope = p4LanguageObject.new ConstantTreeGlobalObjects("UNDEFINED");
    public static final AbstractObjectOfLanguage default_language_object = p4LanguageObject.new ConstantTreeGlobalObjects("DEFAULT");
    private static final BaseTypes baseTypes = p4LanguageObject.new BaseTypes();
    private static final Direction directionClass = p4LanguageObject.new Direction();
    Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab;
    Stack<AbstractObjectOfLanguage> scope;
    // A list of grammar constructs that are not yet supported and might contain invocation
    HashSet<String> notExplicitlySupported = new HashSet<>(Arrays.asList());
    // private Map<BaseTypes, AbstractObjectOfLanguage> baseTypeObjectOfLanguages = new HashMap<>();
    // private Map<String, BaseTypes> baseTypeValues = new HashMap<>();

    // accept and reject are two parser states not defined by the user but is in the logic
    ArrayList<String> implicitParserStates = new ArrayList<>() {{
                                                                add("accept");
                                                                add("reject");
                                                               }};
    HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject;

    //PC Scope

    public CallGraphGenerator() {
        this.symtab = new HashMap<>();
        this.scope = new Stack<>();
        this.callGraphObject = new HashMap<>();

        // for (BaseTypes e: BaseTypes.values()) {
        //     baseTypeValues.put(e.baseString, e);
        //     baseTypeObjectOfLanguages.put(e, new AbstractObjectOfLanguage(e.baseString, AbstractObjectOfLanguage.global_scope));
        // }

        scope.add(global_scope);
    }

    // public AbstractObjectOfLanguage getObjectOfLanguageForBaseType(String typeString, AbstractObjectOfLanguage scope) {
    //     assert baseTypeValues.containsKey(typeString) : "Not a type string. Assuming that the passed in value has been previously check if it a valid base type";
    //     AbstractObjectOfLanguage check = baseTypeObjectOfLanguages.get(BaseTypes.BIT);
    //     return baseTypeObjectOfLanguages.get(baseTypeValues.get(typeString));
    // }

    /**
     * Creates the scope if not present, creates entity for name under scope if not present.
     * Adds the entity to the given scope if it doesn't already exist.
     * 
     * Returns the existing or newly created entity.
     * @param scope
     * @param name
     * @return
     */
    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name) {
        LanguageObject newLangObj = p4LanguageObject.new LanguageObject(name, scope);
        return addToSymtab(scope, name, newLangObj);
    }

    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name, AbstractObjectOfLanguage newLangObj) {
        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        if(symtab.get(scope).containsKey(name)) {
            // TODO: Functions and method can have overloadings - take care of that
            // TODO: Tuples are exceptions
            System.err.println("Multiple declaration error: another entity with the same name (" 
                                + name + 
                                ") already exists");
            // System.exit(1);
        } else {
            // nodeObj = p4LanguageObject.new LanguageObject(name, scope);
            symtab.get(scope).put(name, newLangObj);
        }

        return newLangObj;
    }

    /**
     * Checks if scope exists in the symbol table.
     * Returns true if it does, false otherwise.
     * @param scope
     * @return Boolean
     */
    public boolean doesScopeExist(AbstractObjectOfLanguage scope) {
        return symtab.containsKey(scope);
    }

    /**
     * Checks if the given name exists under the given scope.
     * Returns true if it does, false otherwise.
     * @param scope The scope to check under
     * @param name The name to find under the scope
     * @return Boolean
     */
    public boolean doesSymbolExist(AbstractObjectOfLanguage scope, String name) {
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
    public AbstractObjectOfLanguage symtabLookup(AbstractObjectOfLanguage localScope, String typeName) {
        assert !typeName.isBlank() : "typeName is not supposed to be empty when looking it up on symbol table";
        // System.err.println(localScope.getName());
        // printCallGraph();
        // base case where global_scope is the top-most parent
        if(localScope.equals(global_scope)) {
            // assert doesSymbolExist(localScope, typeName) : "Calling to an undefined symbol \"" + typeName + "\"";
            return symtab.get(localScope).get(typeName);
        }

        // if the symbol does not exist in the current scope, check under its parent scope
        if( !doesSymbolExist(localScope, typeName)) {
            return symtabLookup(localScope.getNameSpace(), typeName);
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
        AbstractObjectOfLanguage callee = symtabLookup(scope.peek(), name);

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
        public AbstractObjectOfLanguage visit(GNode n) {
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
            return default_language_object;
        }

        public AbstractObjectOfLanguage visitcontrolDeclaration(GNode n) {
            // If need to parse parameters, visit the controltypedeclaration instead of static function to get name
            String controlBlockName = getNameOfControlBlock(n.getGeneric(0));

            AbstractObjectOfLanguage controlObj = addToSymtab(scope.peek(), controlBlockName);
            scope.add(controlObj);

            dispatch(n.getGeneric(0).getGeneric(3)); // controlTypeDeclaration optTypeParameters
            dispatch(n.getGeneric(0).getGeneric(5)); // controlTypeDeclaration parameterList
            dispatch(n.getGeneric(1)); // optConstructorParameters
            dispatch(n.getGeneric(3)); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = n.getGeneric(5); // controlBody
            AbstractObjectOfLanguage apply = addToSymtab(scope.peek(), applyBlockName);
            scope.add(apply);

            dispatch(n.getGeneric(0)); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            return controlObj;
        }

        public AbstractObjectOfLanguage visitheaderTypeDeclaration(GNode n) {
            String headerTypeName = getStringUnderName(n.getGeneric(2));
            HeaderTypeDeclaration headerTypeDeclarationObject = p4LanguageObject.new HeaderTypeDeclaration(headerTypeName, scope.peek());
            addToSymtab(scope.peek(), headerTypeName, headerTypeDeclarationObject);
            scope.add(headerTypeDeclarationObject);

            // default functions associated with headers
            FunctionPrototype isValid = p4LanguageObject.new FunctionPrototype("isValid", scope.peek(), baseTypes.getLanguageObjectOfBaseType("bool"));
            FunctionPrototype setValid = p4LanguageObject.new FunctionPrototype("setValid", scope.peek(), baseTypes.getVoidLanguageObject());
            FunctionPrototype setInvalid = p4LanguageObject.new FunctionPrototype("setInvalid", scope.peek(), baseTypes.getVoidLanguageObject());
            addToSymtab(scope.peek(), "isValid", isValid);
            addToSymtab(scope.peek(), "setValid", setValid);
            addToSymtab(scope.peek(), "setInvalid", setInvalid);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // structFieldList

            scope.pop();

            return headerTypeDeclarationObject;
        }

        public AbstractObjectOfLanguage visitheaderUnionDeclaration(GNode n) {
            String headerUnionName = getStringUnderName(n.getGeneric(2));
            HeaderUnionDeclaration headerUnionDeclarationObject = p4LanguageObject.new HeaderUnionDeclaration(headerUnionName, scope.peek());
            addToSymtab(scope.peek(), headerUnionName, headerUnionDeclarationObject);
            scope.add(headerUnionDeclarationObject);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // structFieldList

            scope.pop();

            return headerUnionDeclarationObject;
        }

        public AbstractObjectOfLanguage visittypeRef(GNode n) {
            /*
            Parses the constructs and returns the type
            For typeName, it looks up in the symbol table and returns it
            For baseType, respective basetype language object is retrieved from the BaseTypes class
            For specializedType and headerStackType the inner constructs are parsed and the value associated with that typeName is returned
            For tupletype, a new "tuple" symbol is added to the symtab and that is returned
            */
            GNode innerNode = n.getGeneric(0);
            String typeName;
            AbstractObjectOfLanguage typeObject;
    
            switch(innerNode.getName()) {
                case "typeName":
                    typeName = getNameFromTypeName(innerNode);
                    typeObject = symtabLookup(scope.peek(), typeName);
                    return typeObject;
                case "baseType":
                    String baseTypeString = getBaseTypeAsString(innerNode);
                    if(innerNode.size() > 3) {
                        // if size of baseType is greater than 3 then it is a production with expression inside it
                        dispatch(innerNode.getGeneric(3));
                    }
                    return baseTypes.getLanguageObjectOfBaseType(baseTypeString);
                case "specializedType":
                    typeName = getNameFromTypeName(innerNode.getGeneric(0));
                    typeObject = symtabLookup(scope.peek(), typeName);
    
                    dispatch(innerNode.getGeneric(2)); // typeArgumentList
    
                    return typeObject;
                case "headerStackType":
                String headerStackName;
                    if(n.getGeneric(1).getName().equals("typeName")) {
                        headerStackName = getNameFromTypeName(n.getGeneric(0));
                    } else {
                        headerStackName = getStringUnderSpecializedTypeName(n.getGeneric(0));
                    }
                
                    typeObject = symtabLookup(scope.peek(), headerStackName);
                
                    dispatch(n.getGeneric(2)); // expression
    
                    return typeObject;
                case "tupleType":
                    System.err.println("Unknown use case for Tuple Type in parser implementation, unhandled at the moment.");
                    System.exit(1);
                    return p4LanguageObject.new ConstantTreeGlobalObjects("TUPLE");
                default:
                    System.err.println("Unhandled new case for typeRef");
                    System.exit(1);
                    return p4LanguageObject.new ConstantTreeGlobalObjects("ERROR");
            }
        }

        public AbstractObjectOfLanguage visitstructTypeDeclaration(GNode n) {
            String structName = getStringUnderName(n.getGeneric(2));
            StructTypeDeclaration structTypeObj = p4LanguageObject.new StructTypeDeclaration(structName, scope.peek());
            addToSymtab(scope.peek(), structName, structTypeObj);
            scope.add(structTypeObj);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // structFieldList

            scope.pop();

            return structTypeObj;
        }

        public AbstractObjectOfLanguage visitenumDeclaration(GNode n) {
            /* 
            Two possible productions: one is normal enums and one is serializable enums, the latter has a type
            First one has 6 values and other has 7 values, the latter cause of added type
            */
            if(n.size() == 6) {
                String enumName = getStringUnderName(n.getGeneric(2));
                EnumDeclaration enumObj = p4LanguageObject.new EnumDeclaration(enumName, scope.peek());
                addToSymtab(scope.peek(), enumName, enumObj);
                scope.add(enumObj);

                dispatch(n.getGeneric(4)); // identifierList

                scope.pop();
                return enumObj;
            } else {
                String enumName = getStringUnderName(n.getGeneric(3));
                String typeName = getNameFromTypeName(n.getGeneric(2));

                AbstractObjectOfLanguage type = symtabLookup(scope.peek(), typeName);
                EnumDeclaration enumObj = p4LanguageObject.new EnumDeclaration(enumName, scope.peek(), type);
                addToSymtab(scope.peek(), enumName, enumObj);
                scope.add(enumObj);

                dispatch(n.getGeneric(5)); // specifiedIdentifierList

                scope.pop();
                return enumObj;
            }
        }

        public AbstractObjectOfLanguage visittypedefDeclaration(GNode n) {
            // Two types of typeDefs: TYPEDEF and TYPE ()
            // Two types of associated type values: typeRef and derivedTypeDeclaration
            // derivedTypeDeclaration declares a new type and uses that type, so need to parse that first

            String typeName = getStringUnderName(n.getGeneric(3));

            if(n.getGeneric(2).getName() == "typeRef") {
                // System.out.println(n.getGeneric(2).getName());
                AbstractObjectOfLanguage typeRefObj = (AbstractObjectOfLanguage) dispatch(n.getGeneric(2));
                // System.out.println(typeRefObj.getClass());
                // System.out.println(typeRefObj.getName());
                assert typeRefObj != default_language_object;

                String typeDefName = getStringUnderName(n.getGeneric(3));
                TypeDefDeclaration typeDefObj;
                if(n.get(2).toString() == "typedef") {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), typeRefObj, true);
                } else {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), typeRefObj, false);
                }

                return typeDefObj;
            } else {
                AbstractObjectOfLanguage derivedTypeDeclarationObj = (AbstractObjectOfLanguage) dispatch(n.getGeneric(2));
                assert derivedTypeDeclarationObj != default_language_object;

                String typeDefName = getStringUnderName(n.getGeneric(3));
                TypeDefDeclaration typeDefObj;
                if(n.get(2).toString() == "typedef") {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), derivedTypeDeclarationObj, true);
                } else {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), derivedTypeDeclarationObj, false);
                }

                return typeDefObj;
            }
        }

        public AbstractObjectOfLanguage visitparserTypeDeclaration(GNode n) {
            String parserTypeName = getStringUnderName(n.getGeneric(2));
            ParserTypeDeclaration parserTypeObj = p4LanguageObject.new ParserTypeDeclaration(parserTypeName, scope.peek());
            addToSymtab(scope.peek(), parserTypeName, parserTypeObj);
            scope.add(parserTypeObj);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // parameterList

            scope.pop();

            return parserTypeObj;
        }

        public AbstractObjectOfLanguage visitcontrolTypeDeclaration(GNode n) {
            String controlTypeName = getStringUnderName(n.getGeneric(2));
            ControlTypeDeclaration controlTypeObj = p4LanguageObject.new ControlTypeDeclaration(controlTypeName, scope.peek());
            addToSymtab(scope.peek(), controlTypeName, controlTypeObj);
            scope.add(controlTypeObj);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // parameterList

            scope.pop();

            return controlTypeObj;
        }

        public AbstractObjectOfLanguage visitpackageTypeDeclaration(GNode n) {
            String packageTypeName = getStringUnderName(n.getGeneric(2));
            PackageTypeDeclaration packageTypeObj = p4LanguageObject.new PackageTypeDeclaration(packageTypeName, scope.peek());
            addToSymtab(scope.peek(), packageTypeName, packageTypeObj);
            scope.add(packageTypeObj);

            dispatch(n.getGeneric(3)); // optTypeParameters
            dispatch(n.getGeneric(5)); // parameterList

            scope.pop();

            return packageTypeObj;
        }

        public AbstractObjectOfLanguage visittypeOrVoid(GNode n) {
            if(n.get(0).toString() == "void") {
                return baseTypes.getVoidLanguageObject();
            } else if(n.get(0) instanceof GNode) {
                assert n.getGeneric(0).getName() == "typeRef";
                return (AbstractObjectOfLanguage) dispatch(n.getGeneric(0));
            } else { // IDENTIFIER
                String identifier = n.get(0).toString();
                return symtabLookup(scope.peek(), identifier);
            }
        }

        public AbstractObjectOfLanguage visitfunctionPrototype(GNode n) {
            AbstractObjectOfLanguage typeOrVoid = (AbstractObjectOfLanguage) dispatch(n.getGeneric(0));

            String functionPrototypeName = getStringUnderName(n.getGeneric(1));
            AbstractObjectOfLanguage functionPrototypeObj = p4LanguageObject.new FunctionPrototype(functionPrototypeName, scope.peek(), typeOrVoid);
            addToSymtab(scope.peek(), functionPrototypeName, functionPrototypeObj);
            scope.add(functionPrototypeObj);

            dispatch(n.getGeneric(2)); // optTypeParameters
            dispatch(n.getGeneric(4)); // parameterList

            scope.pop();

            return functionPrototypeObj;
        }

        public AbstractObjectOfLanguage visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(n.getGeneric(2));
            AbstractObjectOfLanguage actionObj =  addToSymtab(scope.peek(), actionBlockName);
            scope.add(actionObj);

            dispatch(n.getGeneric(4)); // parameterList
            dispatch(n.getGeneric(6)); // blockStatement

            scope.pop();

            return actionObj;
        }

        // follow similar as last time (break into three different grammar constructs)
        // . member values has structfield list inside it, so no function calls inside it - but matters for data flow
        // header functions - push_front
        public AbstractObjectOfLanguage visitassignmentOrMethodCallStatement(GNode n) {
            if(n.getGeneric(0).getName() == "methodCallStatements") {
                // method call statements
                return (AbstractObjectOfLanguage) dispatch(n.getGeneric(0));
            } else {
                // assignment statement
                // TODO: need to assert that this lvalue call does not invoke functions
                dispatch(n.getGeneric(0)); // lvalue
                dispatch(n.getGeneric(2)); // expression
                return default_language_object;
            }
        }

        public AbstractObjectOfLanguage visitmethodCallStatements(GNode n) {
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

            return default_language_object;
        }

        // does parsing and type checking
        public AbstractObjectOfLanguage visitlvalue(GNode n) {
            return parseLValue(scope.peek(), n, this);
        }

        public AbstractObjectOfLanguage visitlvalueExpression(GNode n) {
            // Two possible productions:
            // L_BRACKET expression R_BRACKET - size 3
            // L_BRACKET expression COLON expression R_BRACKET - size 5

            dispatch(n.getGeneric(1)); // always expression 

            if(n.size() == 5) { // L_BRACKET expression COLON expression R_BRACKET
                dispatch(n.getGeneric(3)); // expression
            }

            return default_language_object;
        }

        public AbstractObjectOfLanguage visitexternDeclaration(GNode n) {
            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "externFunctionDeclaration") { // separate dispatch available for this
                // TODO: check if externFunctionDeclaration can be merged back again
                return (AbstractObjectOfLanguage) dispatch(returnSecondChildIfConditional(n.getGeneric(0)));
            } else {
                if(returnSecondChildIfConditional(n.getGeneric(2)).getName() == "nonTypeName") {
                    String externName = getStringUnderNonTypeName(returnSecondChildIfConditional(n.getGeneric(2)));
                    AbstractObjectOfLanguage externObj = p4LanguageObject.new ExternDeclaration(externName, scope.peek());
                    addToSymtab(scope.peek(), externName, externObj);
                    scope.add(externObj);

                    dispatch(n.getGeneric(3)); // optTypeParameters
                    dispatch(n.getGeneric(5)); // methodPrototypes

                    scope.pop();

                    return externObj;
                } else { // only option left is "optAnnotations EXTERN name SEMICOLON" production but that is not valid anymore
                    System.err.println("externDeclaration with the grammar: \"optAnnotations EXTERN name SEMICOLON\" is deprecated");
                    System.exit(1);
                    return default_language_object;
                }
            }
        }

        // extern function declarations are invokable constructs as per the language specs
        // so keeping track of that in the symbol table for future invocations
        public AbstractObjectOfLanguage visitexternFunctionDeclaration(GNode n) {
            FunctionPrototype functionPrototypeObj = (FunctionPrototype) dispatch(n.getGeneric(2));

            ExternFunctionDeclaration externFunctionDeclarationObj = p4LanguageObject.new ExternFunctionDeclaration(functionPrototypeObj.getName(), scope.peek(), functionPrototypeObj);
            addToSymtab(scope.peek(), functionPrototypeObj.getName(), externFunctionDeclarationObj);

            return externFunctionDeclarationObj;
        }

        // Interesting: functionDeclaration not part of P416? not in online language specification -- experimental
        //
        public AbstractObjectOfLanguage visitfunctionDeclaration(GNode n) {
            // TODO: need to take care of typeOrVoid if we are keeping track of defined variables (use FunctionPrototype in P4LanguageObject?)
            // dispatch(n.getGeneric(0));

            // as per language specification, functionPrototype will describe the name and type signature of the function
            String functionName = getStringUnderFunctionPrototype(n.getGeneric(0));
            AbstractObjectOfLanguage functionObj = addToSymtab(scope.peek(), functionName);
            scope.add(functionObj);

            dispatch(n.getGeneric(0)); // functionPrototype (for parameters)
            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return functionObj;
        }

        public AbstractObjectOfLanguage visitmethodPrototype(GNode n) {
            /* methodPrototype
                optAnnotations functionPrototype SEMICOLON
                optAnnotations ABSTRACT functionPrototype SEMICOLON
                constructorMethodPrototype

               constructorMethodPrototype:
                optAnnotations TYPE_IDENTIFIER L_PAREN parameterList R_PAREN SEMICOLON

               Where last one is a constructor 
            */

            if(returnSecondChildIfConditional(n.getGeneric(0)).getName() == "constructorMethodPrototype") {
                return (AbstractObjectOfLanguage) dispatch(returnSecondChildIfConditional(n.getGeneric(0)));
            } else if(n.get(1) instanceof Syntax) { // keyword ABSTRACT
                // TODO: need to handle abstract methods
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(2)));
                AbstractObjectOfLanguage functionObj = addToSymtab(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(returnSecondChildIfConditional(n.getGeneric(2)));

                scope.pop();

                return functionObj;
            } else {
                assert returnSecondChildIfConditional(n.getGeneric(1)).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(1)));
                AbstractObjectOfLanguage functionObj = addToSymtab(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(returnSecondChildIfConditional(n.getGeneric(1)));

                scope.pop();

                return functionObj;
            }
        }

        public AbstractObjectOfLanguage visitconstructorMethodPrototype(GNode n) {            
            String type_identifier = n.get(1).toString();
            // System.out.println("constructor inside: " + type_identifier);

            // methodPrototype -> constructorMethodPrototype is directly under parent extern scope
            // so can retrieve the extern block's name from the scope
            // TODO: check if there is a better way

            assert type_identifier.equals(scope.peek().getName()) : "Extern constructor not of the same name as extern block";
            AbstractObjectOfLanguage constructor = addToSymtab(scope.peek(), type_identifier);
            scope.add(constructor);

            dispatch(n.getGeneric(3)); // parameterList

            scope.pop();

            return constructor;
        }

        public AbstractObjectOfLanguage visitparameter(GNode n) {
            dispatch(n.getGeneric(0)); // optAnnotations

            String type_ref_string = getTypeStringUnderTypeRef(n.getGeneric(2));
            String name = getStringUnderName(n.getGeneric(3));
            String directionString;
            if(n.getGeneric(1).size() > 0) {
                directionString = n.getGeneric(1).get(0).toString();
            } else {
                directionString = "";
            }
            
            ConstantTreeGlobalObjects direction;

            if(!directionString.isEmpty()) {
                direction = (ConstantTreeGlobalObjects) directionClass.getLanguageObjectOfDirection(directionString);
            } else {
                direction = null;
            }

            AbstractObjectOfLanguage parameterType;

            if(baseTypes.isBaseType(type_ref_string)) {
                parameterType = baseTypes.getLanguageObjectOfBaseType(type_ref_string);
            } else {
                parameterType = symtabLookup(scope.peek(), type_ref_string);
            }

            Parameter newParameterObj;

            if(n.size() == 6) {
                // "optAnnotations direction typeRef name ASSIGN expression {}" productiom
                // so need to take care of expression
                // The other production is just "optAnnotations direction typeRef name"
                AbstractObjectOfLanguage expression = (AbstractObjectOfLanguage) dispatch(n.getGeneric(5));
                newParameterObj = p4LanguageObject.new Parameter(name, scope.peek(), parameterType, direction, expression);
            } else {
                newParameterObj = p4LanguageObject.new Parameter(name, scope.peek(), parameterType, direction);
            }

            addToSymtab(scope.peek(), name, newParameterObj);

            return newParameterObj;
        }

        // public AbstractObjectOfLanguage visittypeParameterList(GNode n) {
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

        public AbstractObjectOfLanguage visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(n.getGeneric(0));
            AbstractObjectOfLanguage parserObj = addToSymtab(scope.peek(), parserName);
            scope.add(parserObj);

            dispatch(n.getGeneric(0).getGeneric(3)); // parserTypeDeclaration optTypeParameters
            dispatch(n.getGeneric(0).getGeneric(5)); // parserTypeDeclaration parameterList
            dispatch(n.getGeneric(3)); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(n.getGeneric(4)); // parserStates

            scope.pop();

            return parserObj;
        }

        public AbstractObjectOfLanguage visitparserState(GNode n) {
            String stateName = getStringUnderName(n.getGeneric(2));
            AbstractObjectOfLanguage stateObj = addToSymtab(scope.peek(), stateName);
            scope.add(stateObj);

            dispatch(n.getGeneric(4)); // parserStatements
            dispatch(n.getGeneric(5)); // transitionStatement

            scope.pop();
            
            return stateObj;

        }

        public AbstractObjectOfLanguage visitstateExpression(GNode n) {
            if(n.size() == 1) { // selectExpression; (name SEMICOLON is handled in callGraphVisitor)
                return (AbstractObjectOfLanguage) dispatch(n.getGeneric(0));
            }
            return default_language_object;
        }

        // TODO: check if we need to list table scope (if not, remove from callGraphGenerator as well)
        public AbstractObjectOfLanguage visittableDeclaration(GNode n) {
            String tableName = getStringUnderName(n.getGeneric(2));
            AbstractObjectOfLanguage tableObj = addToSymtab(scope.peek(), tableName);
            scope.add(tableObj);

            dispatch(n.getGeneric(4)); // tablePropertyList

            scope.pop();

            return tableObj;
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

            AbstractObjectOfLanguage controlObj = symtabLookup(scope.peek(), controlBlockName);
            scope.add(controlObj);

            // skipping visiting controlTypeDeclaration

            dispatch(n.getGeneric(3)); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = n.getGeneric(5); // controlBody
            AbstractObjectOfLanguage apply = symtabLookup(scope.peek(), applyBlockName);
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
            AbstractObjectOfLanguage actionObj =  symtabLookup(scope.peek(), actionBlockName);
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
            AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName);
            scope.add(functionObj);

            dispatch(n.getGeneric(0)); // functionPrototype (for parameters)
            dispatch(n.getGeneric(1)); // blockstatement

            scope.pop();

            return n;
        }

        public Node visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(n.getGeneric(0)); // TODO: take of parameter list here if needed to
            AbstractObjectOfLanguage parserObj = symtabLookup(scope.peek(), parserName);
            scope.add(parserObj);

            dispatch(n.getGeneric(3)); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(n.getGeneric(4)); // parserStates

            scope.pop();

            return n;
        }

        public Node visitparserState(GNode n) {
            String stateName = getStringUnderName(n.getGeneric(2));
            AbstractObjectOfLanguage stateObj = symtabLookup(scope.peek(), stateName);
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
                    AbstractObjectOfLanguage externObj = symtabLookup(scope.peek(), externName);
                    scope.add(externObj);

                    dispatch(n.getGeneric(3)); // optTypeParameters
                    dispatch(n.getGeneric(5)); // methodPrototypes

                    scope.pop();
                } else {
                    System.err.println("externDeclaration with the grammar: \"optAnnotations EXTERN name SEMICOLON\" is deprecated");
                    System.exit(1);
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
                AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName);
                scope.add(functionObj);

                dispatch(n.getGeneric(2));

                scope.pop();
            } else {
                assert returnSecondChildIfConditional(n.getGeneric(1)).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(n.getGeneric(0)); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(returnSecondChildIfConditional(n.getGeneric(1)));
                AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName);
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

            assert type_identifier.equals(scope.peek().getName()) : "Extern constructor not of the same name as extern block";
            AbstractObjectOfLanguage constructor = symtabLookup(scope.peek(), type_identifier);
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
            AbstractObjectOfLanguage tableObj = symtabLookup(scope.peek(), tableName);
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
                AbstractObjectOfLanguage expressionCallee = getCalleeFromExpression(nGetGeneric0);
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
                AbstractObjectOfLanguage expressionCallee = getCalleeFromNonBraceExpression(nGetGeneric0);
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
    public AbstractObjectOfLanguage getCalleeFromExpression(GNode n) {
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
                    AbstractObjectOfLanguage typeNameLO = symtabLookup(scope.peek(), getNameFromTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(typeNameLO, dotNameString);
                case "expression":
                    // expression dot_name
                    // namespace
                    assert n.size() == 2 && n.getGeneric(1).getName() == "dot_name";
                    AbstractObjectOfLanguage expressionLO = getCalleeFromExpression(returnSecondChildIfConditional(n.getGeneric(0)));
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
    public AbstractObjectOfLanguage getCalleeFromNonBraceExpression(GNode n) {
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
                    AbstractObjectOfLanguage typeNameLO = symtabLookup(scope.peek(), getNameFromTypeName(returnSecondChildIfConditional(n.getGeneric(0))));
                    dotNameString = getStringUnderDotName(returnSecondChildIfConditional(n.getGeneric(1)));
                    return symtabLookup(typeNameLO, dotNameString);
                case "expression":
                    // nonBraceExpression dot_name
                    // namespace
                    assert n.size() == 2 && n.getGeneric(1).getName() == "dot_name";
                    AbstractObjectOfLanguage expressionLO = getCalleeFromNonBraceExpression(returnSecondChildIfConditional(n.getGeneric(0)));
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

    // TODO: !! (need to change AbstractObjectOfLanguage to include which construct each symbol is from)
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

    /**
     * Parses and type checks the values present inside lvalue constructs (goes through nested namespace)
     * @param localScope
     * @param n
     * @param visitor
     * @return null if it is a lvalueExpression
     * TODO: need to handle cases like .apply()
     */
    public AbstractObjectOfLanguage parseLValue(AbstractObjectOfLanguage localScope, GNode n, Visitor visitor) {
        if(n.get(0) instanceof Syntax) { // keyword "THIS"
            return default_language_object;
        }
        Iterator nit = n.iterator();
        AbstractObjectOfLanguage finalValue = null;
        GNode childNode = n;

        for(int i = 0; i < n.size() + 1; i++) {
            switch(childNode.getName()) {
                case "prefixedNonTypeName":
                    // has to be "Identifiers of a base or derived type." (https://p4.org/p4-spec/docs/P4-16-working-spec.html#sec-lvalues)
                    String name = getStringUnderPrefixedNonTypeName(childNode);
                    return symtabLookup(localScope, name);
                case "lvalue":
                    AbstractObjectOfLanguage leftSideValue = parseLValue(localScope, childNode.getGeneric(0), visitor); // has to devolve into prefixedNonTypeName
                    assert leftSideValue != null : "Undefined value used";
                    localScope = leftSideValue.getNameSpace();
                    finalValue = leftSideValue;
                    break;
                case "dot_name":
                    switch(scope.peek().getConstructType()) {
                        case STRUCTTYPEDECLARATION:
                        case HEADERTYPEDECLARATION:
                        case HEADERUNIONDECLARATION:
                            break;
                        default:
                            // System.err.println("Type error, referring to undefined value: " + childNode.getName());
                            assert false : "Type error for dot values, referring to construct: " + scope.peek().getConstructType();
                            System.exit(1);
                    }
                    String nameValue = getStringUnderDotName(childNode);
                    finalValue = symtabLookup(localScope, nameValue);
                    localScope = finalValue.getNameSpace();
                    break;
                case "lvalueExpression":
                    // TODO: change scope?
                    scope.add(localScope);
                    visitor.dispatch(childNode.getGeneric(1));
                    if(childNode.size() > 3) {
                        visitor.dispatch(childNode.getGeneric(3));
                    }
                    scope.pop();
                    break;
                default:
                    // System.err.println("Unexpected case when parsing l-value. Value: " + childNode.getName());
                    assert false : "Unexpected case when parsing l-value. Value: " + childNode.getName();
                    System.exit(1);
            }

            if(i < n.size())
                childNode = (GNode) n.get(i);
        }

        if(finalValue == null) {
            assert false : "Undefined value accessed : " + n.getName();
        }
        return finalValue;
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
        for(AbstractObjectOfLanguage key : symtab.keySet()) {
            System.out.println(key.toStringExtensive(symtab, callGraphObject));
        }
        // System.out.println(callGraphObject);
    }

    public String toDot() {
        String dotFormat = "";
        for(AbstractObjectOfLanguage key : symtab.keySet()) {
            dotFormat += key.toDotString(symtab, callGraphObject);
        }

        // System.out.println(dotFormat);
        return dotFormat;
    }
    
    public static void createDotGraph(String dotFormat,String fileName) {
        String check = "{rank=same; a1, b1 } {rank=same; a2, b2 } a1 [label=\"This calls\"] a2 [label=\"This defines\"] b1 [label=\"this\"] b2 [label=\"this\"] a1 -> b1 [ minlen=4 ] a2 -> b2 [ style=dashed, color=blue, minlen=4 ]";
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