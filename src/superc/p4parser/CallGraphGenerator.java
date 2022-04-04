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
import java.beans.Expression;
import java.io.File;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;

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
    public static final AbstractObjectOfLanguage undeclared_object = p4LanguageObject.new ConstantTreeGlobalObjects("UNDECLARED OBJECT");
    public static final AbstractObjectOfLanguage default_language_object = p4LanguageObject.new ConstantTreeGlobalObjects("DEFAULT");
    private static final BaseTypesCollection baseTypesCollection = p4LanguageObject.new BaseTypesCollection();
    private static final Direction directionClass = p4LanguageObject.new Direction();
    Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab;
    Stack<AbstractObjectOfLanguage> scope;
    // A list of grammar constructs that are not yet supported and might contain invocation
    HashSet<String> notExplicitlySupported = new HashSet<>(Arrays.asList());
    // private Map<baseTypesCollection, AbstractObjectOfLanguage> baseTypeObjectOfLanguages = new HashMap<>();
    // private Map<String, baseTypesCollection> baseTypeValues = new HashMap<>();

    HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject;

    HashSet<LObjectKind> overridableConstructs;

    // Temporary value classes
    class TemporaryParameterValues {
        ArrayList<AbstractObjectOfLanguage> parameters;
        ArrayList<AbstractObjectOfLanguage> typeParameters;

        public ArrayList<AbstractObjectOfLanguage> getParameters() {
            return this.parameters;
        }

        public ArrayList<AbstractObjectOfLanguage> getTypeParameters() {
            return this.typeParameters;
        }

        public void addToParameters(AbstractObjectOfLanguage parameter) {
            this.parameters.add(parameter);
        }

        public void addToTypeParameters(AbstractObjectOfLanguage parameter) {
            this.typeParameters.add(parameter);
        }

        public TemporaryParameterValues() {
            this.parameters = new ArrayList<>();
            this.typeParameters = new ArrayList<>();
        }
    }

    Stack<TemporaryParameterValues> temporaryValues;
    //PC Scope

    public CallGraphGenerator() {
        this.symtab = new HashMap<>();
        this.scope = new Stack<>();
        this.callGraphObject = new HashMap<>();
        this.temporaryValues = new Stack<>();
        this.overridableConstructs = new HashSet<>();

        this.overridableConstructs.add(LObjectKind.FUNCTION);
        this.overridableConstructs.add(LObjectKind.FUNCTIONDECLARATION);
        this.overridableConstructs.add(LObjectKind.FUNCTIONPROTOTYPE);
        this.overridableConstructs.add(LObjectKind.FUNCTIONPROTOTYPEGENERATOR);
        this.overridableConstructs.add(LObjectKind.METHOD);
        this.overridableConstructs.add(LObjectKind.EXTERNFUNCTIONDECLARATION);
        this.overridableConstructs.add(LObjectKind.EXTERNFUNCTIONDECLARATIONGENERATOR);

        // for (baseTypesCollection e: baseTypesCollection.values()) {
        //     baseTypeValues.put(e.baseString, e);
        //     baseTypeObjectOfLanguages.put(e, new AbstractObjectOfLanguage(e.baseString, AbstractObjectOfLanguage.global_scope));
        // }

        scope.add(global_scope);
    }

    public boolean isFunctionAndMethodDuplicate(AbstractObjectOfLanguage newObj, AbstractObjectOfLanguage oldObj) {
        // TODO: check for same argument length and parameter names if same length (issue1334.p4 for example)

        return true;
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
    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name) {
        LanguageObject newLangObj = p4LanguageObject.new LanguageObject(name, scope);
        return addToSymtab(scope, name, newLangObj);
    }

    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name, AbstractObjectOfLanguage newLangObj) {
        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        if(symtab.get(scope).containsKey(name)) {
            boolean isDuplicateFunctionOrMethod = true;
            if(overridableConstructs.contains(newLangObj.getConstructType())) {
                    isDuplicateFunctionOrMethod = isFunctionAndMethodDuplicate(newLangObj, symtab.get(scope).get(name));
            }
            // TODO: Tuples are exceptions
            if(isDuplicateFunctionOrMethod) {
                if(!overridableConstructs.contains(newLangObj.getConstructType())) {
                       System.err.println("Error: " + name + " is already defined and is neither a function nor a method");
                       System.exit(1);
                } else {
                    System.err.println("Multiple declaration warning (FIX): another entity with the same name (" 
                                        + name + 
                                        ") already exists");
                }
            }
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
     * Returns the type associated with a variable, if it has an associated type.
     * Else returns the passed in variable itself.
     * @param variable
     * @return
     */
    public AbstractObjectOfLanguage getParameterTypeIfPresent(AbstractObjectOfLanguage variable) {
        // System.err.println("Getting parameter type of: " + variable.getName() + " of constructor: " + variable.getConstructType());
        // Note: checking for subclass for example bfd_offload
        if(variable.hasAssociatedType()) {
            if(variable.getType().getConstructType() == LObjectKind.BASETYPE) {
                return variable;
            }
            return variable.getType();
        } else {
            return variable;
        }
    }

    public AbstractObjectOfLanguage nonTypeNameSymtabLookUp(AbstractObjectOfLanguage localScope, String name, boolean canBeNewIdentifier) {
        return nonTypeNameSymtabLookUp(localScope, name, canBeNewIdentifier, true, true);
    }

    /**
     * A symtab look up function specific for non type names since the referring string
     * can either be an already defined value, a reserved keyword, or just a new value.
     * Returns the language object if the value is already defined or if a reserved keyword,
     * else creates a new string language object if it is a new identifier.
     * @param localScope
     * @param name
     * @param canBeNewIdentifier If set to false, then the value must be in symbol table or a reserved keyword.
     * @param getAssociatedType if set to true, will return the associated type of object, if it has
     * @return
     */
    // TODO: no longer need generateInstance parameter -> safely remove that
    public AbstractObjectOfLanguage nonTypeNameSymtabLookUp(AbstractObjectOfLanguage localScope, String name, boolean canBeNewIdentifier, boolean getAssociatedType, boolean generateInstance) {
        AbstractObjectOfLanguage lookupValue = symtabLookupIfExists(localScope, name, getAssociatedType, generateInstance);
        if(lookupValue == undeclared_object) {
            if(canBeNewIdentifier || ReservedKeywords.isNonTypeNameKeyword(name)) {
                // System.out.println("New nontypename identifier: " + name);
                return p4LanguageObject.new OLangString(name, localScope);
            } else {
                // System.err.println("Calling to an undefined symbol \"" + typeName + "\"";);
                // System.exit(1);
                assert false : "Calling to an undefined symbol \"" + name + "\"";
            }
        }
        // System.out.println("found an existing nontypename: " + name);

        return lookupValue;
    }

    public AbstractObjectOfLanguage symtabLookup(AbstractObjectOfLanguage localScope, String typeName) {
        return symtabLookup(localScope, typeName, true, true);
    }

    /**
     * Checks if the scope and symbol exists, returns the corresponding object from symtab if it does.
     * Recursively goes through the parent scopes if not found under current scope.
     * Error is thrown if it does not exist.
     * @param localScope
     * @param typeName
     * @param getAssociatedType if set to true, will return the associated type of object, if it has
     * @return
     */
    public AbstractObjectOfLanguage symtabLookup(AbstractObjectOfLanguage localScope, String typeName, boolean getAssociatedType, boolean generateInstance) {
        // System.out.println("looking up: " + typeName + " under: " + localScope.getName() + " of type: " + localScope.getConstructType());
        // if(localScope.getConstructType() == LObjectKind.SPECIALIZEDTYPE) {
        //     System.out.println("specizlied type: " + localScope.getName() + " type arg list: " + ((SpecializedType)localScope).getTypeArgumentList());
        // }
        AbstractObjectOfLanguage lookupValue =  symtabLookupIfExists(localScope, typeName, getAssociatedType, generateInstance);
        if(lookupValue == undeclared_object) {
            // System.err.println("Calling to an undefined symbol \"" + typeName + "\"";);
            // System.exit(1);
            assert false : "Calling to an undefined symbol \"" + typeName + "\"";
        }

        return lookupValue;
    }

    /**
     * Similar to symtab lookup, but treats the value as a type variable 
     * if it is not found in the symbol table
     * @param localScope
     * @param typeName
     * @param getAssociatedType if set to true, will return the associated type of object, if it has
     * @return
     */
    public AbstractObjectOfLanguage retrieveSymbolOrTypeVariable(AbstractObjectOfLanguage localScope, String typeName) {
        AbstractObjectOfLanguage lookupValue = symtabLookupIfExists(localScope, typeName, true, true);
        if (lookupValue == undeclared_object) {
            TypeParameter typeParameterObj = p4LanguageObject.new TypeParameter(typeName, localScope);
            // System.out.println("Creating new type variable: " + typeParameterObj.getName());
            // NOTE: initially was not adding to symbol table
            addToSymtab(scope.peek(), typeName, typeParameterObj);
            return typeParameterObj;
        } else {
            return lookupValue;
        }
    }

    /**
     * Checks if scope and symbol exists, returns the corresponding object from symtab if it does.
     * Recursively goes through the parent scopes if not found under current scope.
     * Treats value as a type variable if symbol is not found and canBeTypeVariable is set to true.
     * If canBeTypeVariable is set to false and symbol is not found, an error is thrown.
     * @param localScope The scope to check under. Changes as we recursively go through scopes
     * @param typeName
     * @param primaryScope The initial scope that the symbol was supposed to be checked under. Keep track of initial one for type variable declarations.
     * @param canBeTypeVariable A boolean variable indicating whether the symbol can possibly be a new type variable
     * @return
     */
    public AbstractObjectOfLanguage symtabLookupIfExists(AbstractObjectOfLanguage localScope, String typeName, boolean getAssociatedType, boolean generateInstance) {
        assert !typeName.isBlank() : "typeName is not supposed to be empty when looking it up on symbol table";

        // base case where global_scope is the top-most parent
        // System.out.println("name: " + typeName + ", scope: " + localScope.getName() + " constructor: " + localScope.getConstructType());
        boolean doesExistInCurrentScope = doesSymbolExist(localScope, typeName);

        // if the symbol does not exist in the current scope, check under its parent scope
        if( !doesExistInCurrentScope) {
            if(localScope.equals(global_scope)) {
                return undeclared_object;
            }

            return symtabLookupIfExists(localScope.getNameSpace(), typeName, getAssociatedType, generateInstance);
        } else {
            AbstractObjectOfLanguage symtabValue = symtab.get(localScope).get(typeName);
            // if(generateInstance && symtabValue.isGeneratorClass()) {
            // Changed symtab lookup to invoke the generate instance function on a generated class 
            // if and only if either parameters or type parameters were parsed/read in. This makes it simpler to identify when a symtab look up is just to retrieve types 
            // (like in type checking stage where we get type of variable and that type is of generator class) vs. creating an instance of that generator class for calls.
            if(symtabValue.isGeneratorClass() && !temporaryValues.isEmpty() && 
                (!temporaryValues.peek().getParameters().isEmpty() | !temporaryValues.peek().getTypeParameters().isEmpty())) {
                // System.err.println("Generating instance of: " + symtabValue.getName() + "\n");
                // System.out.println("parameters size: " + temporaryValues.peek().getParameters().size() + "; type parameters size: " + temporaryValues.peek().getTypeParameters().size());
                assert (!temporaryValues.isEmpty());
                assert (!temporaryValues.peek().getParameters().isEmpty() | !temporaryValues.peek().getTypeParameters().isEmpty());
                symtabValue = ((Generator) symtabValue).generateInstance(temporaryValues.peek().getTypeParameters(), temporaryValues.peek().getParameters(), symtab.get(symtabValue), symtab, definitionsVisitor, scope);
            }
            if(getAssociatedType) {
                AbstractObjectOfLanguage value = getParameterTypeIfPresent(symtabValue);

                return value;
            } else {
                return symtabValue;
            }
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
        addAsCallee(callee);
    }

    /**
     * Adds the passed in language object as a callee to the current scope.
     * @param callee The object that should be added as a callee
     */
    public void addAsCallee(AbstractObjectOfLanguage callee) {
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
            String controlBlockName = getNameOfControlBlock(getGNodeUnderConditional(n.getGeneric(0)));

            ControlDeclaration controlObj = p4LanguageObject.new ControlDeclaration(controlBlockName, scope.peek());
            addToSymtab(scope.peek(), controlBlockName, controlObj);
            scope.add(controlObj);

            AbstractObjectOfLanguage controlTypeDecl = visitcontrolTypeDeclaration(getGNodeUnderConditional(n.getGeneric(0)), false);

            if(controlTypeDecl.isGeneratorClass()) {
                System.err.println("Control declaration (" + controlBlockName + ") cannot have generics.");
                System.exit(1);
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(1))); // optConstructorParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = getGNodeUnderConditional(n.getGeneric(5)); // controlBody
            AbstractObjectOfLanguage apply = addToSymtab(scope.peek(), applyBlockName);
            scope.add(apply);

            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            controlObj.setNode(n);
            return controlObj;
        }

        public AbstractObjectOfLanguage visitheaderTypeDeclaration(GNode n) {
            String headerTypeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage headerTypeDeclarationObject = p4LanguageObject.new HeaderTypeDeclaration(headerTypeName, scope.peek());

            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) {
                headerTypeDeclarationObject.setNode(n);
                headerTypeDeclarationObject = p4LanguageObject.new HeaderTypeDeclarationGenerator((HeaderTypeDeclaration) headerTypeDeclarationObject);
            }

            addToSymtab(scope.peek(), headerTypeName, headerTypeDeclarationObject);
            scope.add(headerTypeDeclarationObject);

            // default functions associated with headers
            FunctionPrototype isValid = p4LanguageObject.new FunctionPrototype("isValid", scope.peek(), baseTypesCollection.getLanguageObjectOfBaseType("bool"));
            FunctionPrototype setValid = p4LanguageObject.new FunctionPrototype("setValid", scope.peek(), baseTypesCollection.getVoidLanguageObject());
            FunctionPrototype setInvalid = p4LanguageObject.new FunctionPrototype("setInvalid", scope.peek(), baseTypesCollection.getVoidLanguageObject());
            addToSymtab(scope.peek(), "isValid", isValid);
            addToSymtab(scope.peek(), "setValid", setValid);
            addToSymtab(scope.peek(), "setInvalid", setInvalid);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // structFieldList

            scope.pop();

            headerTypeDeclarationObject.setNode(n);
            return headerTypeDeclarationObject;
        }

        public AbstractObjectOfLanguage visitheaderUnionDeclaration(GNode n) {
            String headerUnionName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage headerUnionDeclarationObject = p4LanguageObject.new HeaderUnionDeclaration(headerUnionName, scope.peek());

            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) {
                headerUnionDeclarationObject.setNode(n);
                headerUnionDeclarationObject = p4LanguageObject.new HeaderUnionDeclarationGenerator((HeaderUnionDeclaration) headerUnionDeclarationObject);
            }

            addToSymtab(scope.peek(), headerUnionName, headerUnionDeclarationObject);
            scope.add(headerUnionDeclarationObject);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // structFieldList

            scope.pop();
            headerUnionDeclarationObject.setNode(n);
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
            GNode innerNode = getGNodeUnderConditional(n.getGeneric(0));
            String typeName;
            AbstractObjectOfLanguage typeObject;
    
            switch(innerNode.getName()) {
                case "typeName":
                    typeName = getNameFromTypeName(innerNode);
                    typeObject = symtabLookup(scope.peek(), typeName);
                    // Since type names point directly to the type and not a instance of that type -
                    // Update: generic-struct.p4i - the type can be a typedef
                    // assert !typeObject.hasAssociatedType() : typeObject.getName() + "of constructor: " + typeObject.getConstructType() + " with type: " + typeObject.getType().getName() + " of constructor: " + typeObject.getType().getConstructType();
                    return typeObject;
                case "baseType":
                    String baseTypeString = getBaseTypeAsString(innerNode);
                    if(innerNode.size() > 3) {
                        // if size of baseType is greater than 3 then it is a production with expression inside it
                        dispatch(innerNode.getGeneric(3));
                    }
                    return baseTypesCollection.getLanguageObjectOfBaseType(baseTypeString);
                case "specializedType":
                    return (AbstractObjectOfLanguage) dispatch(innerNode);
                case "headerStackType":
                    return (AbstractObjectOfLanguage) dispatch(innerNode);
                case "tupleType":
                    return (AbstractObjectOfLanguage) dispatch(innerNode);
                default:
                    System.err.println("Unhandled new case for typeRef");
                    System.exit(1);
                    return p4LanguageObject.new ConstantTreeGlobalObjects("ERROR");
            }
        }

        public AbstractObjectOfLanguage visitstructTypeDeclaration(GNode n) {
            String structName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage structTypeObj = p4LanguageObject.new StructTypeDeclaration(structName, scope.peek());

            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) {
                structTypeObj.setNode(n);
                structTypeObj = p4LanguageObject.new StructTypeDeclarationGenerator((StructTypeDeclaration) structTypeObj);
            }

            addToSymtab(scope.peek(), structName, structTypeObj);
            scope.add(structTypeObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // structFieldList

            scope.pop();
            structTypeObj.setNode(n);
            return structTypeObj;
        }

        public AbstractObjectOfLanguage visitstructField(GNode n) {
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations
            AbstractObjectOfLanguage typeRefObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(1)));
            typeRefObj = (typeRefObj.hasAssociatedType() ? typeRefObj.getType() : typeRefObj);
            String fieldName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            // System.out.println("visiting struct field: " + fieldName + " with type: " + typeRefObj.getConstructType() );
            AbstractObjectOfLanguage newStructFieldObj = p4LanguageObject.new Variable(fieldName, scope.peek(), typeRefObj);
            if(typeRefObj.getConstructType() == LObjectKind.TYPEPARAMETER || typeRefObj.isGeneratorClass()) {
                newStructFieldObj.setNode(n);
                newStructFieldObj = p4LanguageObject.new VariableGenerator((Variable) newStructFieldObj);
            }
            addToSymtab(scope.peek(), fieldName, newStructFieldObj);
            newStructFieldObj.setNode(n);

            return newStructFieldObj;
        }

        public AbstractObjectOfLanguage visitvariableDeclaration(GNode n) {
            // Two productions - one that annotations in the beginning and one does not
            int typeRefIndex = 0;
            if(n.size() == 5) { // with the annotations
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // annotations
                typeRefIndex = 1;
            }

            AbstractObjectOfLanguage typeRefObj = (AbstractObjectOfLanguage) dispatch(n.getGeneric(typeRefIndex));
            typeRefObj = (typeRefObj.hasAssociatedType() ? typeRefObj.getType() : typeRefObj);
            String variableName = getStringUnderName(n.getGeneric(typeRefIndex+1));
            AbstractObjectOfLanguage variableObj = p4LanguageObject.new Variable(variableName, scope.peek(), typeRefObj);
            if(typeRefObj.getConstructType() == LObjectKind.TYPEPARAMETER) {
                variableObj.setNode(n);
                variableObj = p4LanguageObject.new VariableGenerator((Variable) variableObj);
            }
            // System.out.println("adding variable named: " + variableName + " under scope: " + scope.peek().getName() + " with type: " + typeRefObj.getName() + " of type: " + typeRefObj.getConstructType());
            addToSymtab(scope.peek(), variableName, variableObj);
            scope.add(variableObj);

            if(getGNodeUnderConditional(n.getGeneric(typeRefIndex + 2)).size() > 0) {
                assert !variableObj.isGeneratorClass() : "Assuming that variable assignment is just default value that has no associated type";
                AbstractObjectOfLanguage optionalInitializer = (AbstractObjectOfLanguage) dispatch(n.getGeneric(typeRefIndex+2));
                ((Variable) variableObj).setAssignedExpression(optionalInitializer);
            }

            scope.pop();
            variableObj.setNode(n);
            return variableObj;
        }

        public AbstractObjectOfLanguage visitenumDeclaration(GNode n) {
            /* 
            Two possible productions: one is normal enums and one is serializable enums, the latter has a type
            First one has 6 values and other has 7 values, the latter cause of added type
            */
            if(n.size() == 6) {
                String enumName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
                EnumDeclaration enumObj = p4LanguageObject.new EnumDeclaration(enumName, scope.peek());
                addToSymtab(scope.peek(), enumName, enumObj);
                scope.add(enumObj);

                // Adding enum identifiers
                GNode identifiersList = getGNodeUnderConditional(n.getGeneric(4));
                Iterator itr = identifiersList.iterator();

                while(itr.hasNext()) {
                    Object next = itr.next();
                    if(next instanceof Syntax) {
                        // COMMA
                        continue;
                    }
                    Object underConditional = getValueUnderConditional((GNode) next);
                    if(underConditional instanceof Syntax) {
                        // also COMMA (but surrounded by conditional)
                        continue;
                    }

                    GNode nextGNode = (GNode) underConditional;
                    assert nextGNode.getName() == "name";
                    String identifierString = getStringUnderName(nextGNode);

                    LanguageObject newIdentifier = p4LanguageObject.new LanguageObject(identifierString, scope.peek());
                    addToSymtab(scope.peek(), identifierString, newIdentifier);
                }

                scope.pop();
                enumObj.setNode(n);
                return enumObj;
            } else {
                String enumName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));
                AbstractObjectOfLanguage type = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(2)));

                assert !type.isGeneratorClass() : "Haven't explored a case where an enum can be declared of generic type.";

                EnumDeclaration enumObj = p4LanguageObject.new EnumDeclaration(enumName, scope.peek(), type);
                addToSymtab(scope.peek(), enumName, enumObj);
                scope.add(enumObj);

                dispatch(getGNodeUnderConditional(n.getGeneric(5))); // specifiedIdentifierList

                scope.pop();
                enumObj.setNode(n);
                return enumObj;
            }
        }

        public AbstractObjectOfLanguage visitspecifiedIdentifier(GNode n) {
            String identifierName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(0)));

            // TODO: for stricter type checking, ensure that the the initializer values are tracked
            // (see grammar) and that they are of the declared enum type
            // TODO: set up initializer for specified identifiers
            LanguageObject newIdentifier = p4LanguageObject.new LanguageObject(identifierName, scope.peek());
            addToSymtab(scope.peek(), identifierName, newIdentifier);

            newIdentifier.setNode(n);
            return newIdentifier;
        }

        public AbstractObjectOfLanguage visittypedefDeclaration(GNode n) {
            // Two types of typeDefs: TYPEDEF and TYPE ()
            // Two types of associated type values: typeRef and derivedTypeDeclaration
            // derivedTypeDeclaration declares a new type and uses that type, so need to parse that first

            String typeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));

            if(getGNodeUnderConditional(n.getGeneric(2)).getName() == "typeRef") {
                // System.out.println(getGNodeUnderConditional(n.getGeneric(2)).getName());
                AbstractObjectOfLanguage typeRefObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(2)));
                // System.out.println(typeRefObj.getClass());
                // System.out.println(typeRefObj.getName());
                assert typeRefObj != default_language_object;
                assert !typeRefObj.isGeneratorClass();

                String typeDefName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));
                TypeDefDeclaration typeDefObj;
                if(n.get(1).toString() == "typedef") {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), typeRefObj, true);
                } else {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), typeRefObj, false);
                }

                addToSymtab(scope.peek(), typeDefName, typeDefObj);
                typeDefObj.setNode(n);

                return typeDefObj;
            } else {
                AbstractObjectOfLanguage derivedTypeDeclarationObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(2)));
                assert derivedTypeDeclarationObj != default_language_object;
                assert !derivedTypeDeclarationObj.isGeneratorClass();

                String typeDefName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));
                TypeDefDeclaration typeDefObj;
                if(n.get(1).toString() == "typedef") {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), derivedTypeDeclarationObj, true);
                } else {
                    typeDefObj = p4LanguageObject.new TypeDefDeclaration(typeDefName, scope.peek(), derivedTypeDeclarationObj, false);
                }

                addToSymtab(scope.peek(), typeDefName, typeDefObj);
                typeDefObj.setNode(n);

                return typeDefObj;
            }
        }

        public AbstractObjectOfLanguage visitparserTypeDeclaration(GNode n) {
            return visitparserTypeDeclaration(n, true);
        }

        /**
         * Pass addToSymtab as false when we consider the type declaration to be part of parser declaration
         * Set it to true if parser type declaration is independent of parser declaration
         * @param n
         * @param addToSymtab
         * @return
         */
        public AbstractObjectOfLanguage visitparserTypeDeclaration(GNode n, boolean addToSymtab) {
            String parserTypeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage parserTypeObj = p4LanguageObject.new ParserTypeDeclaration(parserTypeName, scope.peek());

            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) { // has type parameters, so generator
                parserTypeObj.setNode(n);
                parserTypeObj = p4LanguageObject.new ParserTypeDeclarationGenerator((ParserTypeDeclaration) parserTypeObj);
            }

            if(addToSymtab) {
                addToSymtab(scope.peek(), parserTypeName, parserTypeObj);
                scope.add(parserTypeObj);
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // parameterList

            if(addToSymtab) {
                scope.pop();
            }

            parserTypeObj.setNode(n);

            return parserTypeObj;
        }

        public AbstractObjectOfLanguage visitcontrolTypeDeclaration(GNode n) {
            return visitcontrolTypeDeclaration(n, true);
        }
        /**
         * Pass addToSymtab as false when we consider the type declaration to be part of the control declaration
         * Set it to true if control type declaration is independent of control declaration
         * @param n
         * @param addToSymtab
         * @return
         */
        public AbstractObjectOfLanguage visitcontrolTypeDeclaration(GNode n, Boolean addToSymtab) {
            String controlTypeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage controlTypeObj = p4LanguageObject.new ControlTypeDeclaration(controlTypeName, scope.peek());

            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) { // has type parameters, so generator
                controlTypeObj.setNode(n);
                controlTypeObj = p4LanguageObject.new ControlTypeDeclarationGenerator((ControlTypeDeclaration) controlTypeObj);
            }

            if(addToSymtab) {
                addToSymtab(scope.peek(), controlTypeName, controlTypeObj);
                scope.add(controlTypeObj);
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // parameterList

            if(addToSymtab) {
                // addToSymtab(scope.peek(), "apply");
                scope.pop();
            }

            controlTypeObj.setNode(n);

            return controlTypeObj;
        }

        public AbstractObjectOfLanguage visitpackageTypeDeclaration(GNode n) {
            String packageTypeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage packageTypeObj = p4LanguageObject.new PackageTypeDeclaration(packageTypeName, scope.peek());

            // check if it has generic parameters, if so make it generator class
            if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) {
                packageTypeObj.setNode(n);
                packageTypeObj = p4LanguageObject.new PackageTypeDeclarationGenerator((PackageTypeDeclaration) packageTypeObj);
            }

            addToSymtab(scope.peek(), packageTypeName, packageTypeObj);
            scope.add(packageTypeObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // parameterList

            scope.pop();

            packageTypeObj.setNode(n);

            return packageTypeObj;
        }

        public AbstractObjectOfLanguage visittypeOrVoid(GNode n) {
            if(n.get(0).toString() == "void") {
                return baseTypesCollection.getVoidLanguageObject();
            } else if(n.get(0) instanceof GNode) {
                assert getGNodeUnderConditional(n.getGeneric(0)).getName() == "typeRef";
                return (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            } else { // IDENTIFIER - may be type variable
                String identifier = n.get(0).toString();
                return retrieveSymbolOrTypeVariable(scope.peek(), identifier);
            }
        }

        public AbstractObjectOfLanguage visitfunctionPrototype(GNode n) {
            return visitfunctionPrototype(n, LObjectKind.FUNCTIONPROTOTYPE);
        }

        public AbstractObjectOfLanguage visitfunctionPrototype(GNode n, LObjectKind classType) {
            // AbstractObjectOfLanguage typeOrVoid = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            AbstractObjectOfLanguage typeOrVoid;
            GNode typeOrVoidNode = getGNodeUnderConditional(n.getGeneric(0));
            String identifier = null;
            // visittypeOrVoid
            if(typeOrVoidNode.get(0).toString() == "void") {
                typeOrVoid = baseTypesCollection.getVoidLanguageObject();
            } else if(typeOrVoidNode.get(0) instanceof GNode) {
                assert getGNodeUnderConditional(typeOrVoidNode.getGeneric(0)).getName() == "typeRef";
                typeOrVoid = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(typeOrVoidNode.getGeneric(0)));
            } else { // IDENTIFIER - may be type variable
                identifier = typeOrVoidNode.get(0).toString();
                typeOrVoid = symtabLookupIfExists(scope.peek(), identifier, true, true);
                // System.out.println("looking up result: " + typeOrVoid.getName());  
            }    

            String functionPrototypeName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(1)));
            // System.out.println("Type value is: " + (typeOrVoid.getName()) + " with identifier: " + identifier + " for func prototype: " + functionPrototypeName + " add to symtab value: " + addToSymtab);
            AbstractObjectOfLanguage functionPrototypeObj = p4LanguageObject.getRespectiveFunctionPrototypeClass(functionPrototypeName, scope.peek(), typeOrVoid, classType);

            // can optimize this
            boolean areParametersGeneric = isAnyParameterGeneric(getGNodeUnderConditional(n.getGeneric(4)), getGNodeUnderConditional(n.getGeneric(2)));
            
            if(typeOrVoid.getConstructType() == LObjectKind.TYPEPARAMETER ||
                getGNodeUnderConditional(n.getGeneric(2)).size() > 0 ||
                areParametersGeneric) {
                functionPrototypeObj.setNode(n);
                functionPrototypeObj = p4LanguageObject.getRespectiveFunctionPrototypeGeneratorClass((FunctionPrototype) functionPrototypeObj);
            }

            addToSymtab(scope.peek(), functionPrototypeName, functionPrototypeObj);
            scope.add(functionPrototypeObj);
            if(typeOrVoid == undeclared_object) {
                // System.err.println("adding type parameter to symbol table");
                assert identifier != null;
                typeOrVoid = retrieveSymbolOrTypeVariable(scope.peek(), identifier);
                if(functionPrototypeObj.isGeneratorClass()) {
                    ((FunctionPrototypeGenerator) functionPrototypeObj).setType(typeOrVoid);
                } else {
                    ((FunctionPrototype) functionPrototypeObj).setType(typeOrVoid);
                }
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(2))); // optTypeParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parameterList
            // dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parameterList

            scope.pop();

            // System.out.println("Created function prototype: " + functionPrototypeName + " with parameters: " + 
            // functionPrototypeObj.getParameterList() + " and return type: " + functionPrototypeObj.getType() + 
            // " along with type parameters: " + functionPrototypeObj.getOptTypeParameters());
            functionPrototypeObj.setNode(n);

            return functionPrototypeObj;
        }

        public AbstractObjectOfLanguage visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage actionObj =  addToSymtab(scope.peek(), actionBlockName);
            scope.add(actionObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parameterList
            dispatch(getGNodeUnderConditional(n.getGeneric(6))); // blockStatement

            scope.pop();

            actionObj.setNode(n);

            return actionObj;
        }

        // follow similar as last time (break into three different grammar constructs)
        // . member values has structfield list inside it, so no function calls inside it - but matters for data flow
        // header functions - push_front
        public AbstractObjectOfLanguage visitassignmentOrMethodCallStatement(GNode n) {
            if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "methodCallStatements") {
                // method call statements
                return (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            } else {
                // assignment statement
                AbstractObjectOfLanguage lvalue = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0))); // lvalue
                // Asserting that this lvalue call does not invoke functions
                assert lvalue.getConstructType() != LObjectKind.EXTERNDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.EXTERNFUNCTIONDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.FUNCTION ||
                    lvalue.getConstructType() != LObjectKind.FUNCTIONPROTOTYPE ||
                    lvalue.getConstructType() != LObjectKind.PARSERDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.PARSERTYPEDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.CONTROLDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.CONTROLTYPEDECLARATION ||
                    lvalue.getConstructType() != LObjectKind.PACKAGETYPEDECLARATION;

                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // expression
                return default_language_object;
            }
        }

        public AbstractObjectOfLanguage visitmethodCallStatements(GNode n) {
            temporaryValues.add(new TemporaryParameterValues());

            // There are two possible set of sub productions, both which have argument list under it
            // but one has typeArgumentList before argument list, so argumentList is not at the same place
            // hence check the size to see which production we are currently under and dispatching
            // the visitor at the respective argumentList position
            if(n.size() == 5) {
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // argumentlist
            } else { 
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // typeArgumentList
                dispatch(getGNodeUnderConditional(n.getGeneric(5))); // argumentList
            }


            AbstractObjectOfLanguage method = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0))); // lvalue

            assert !method.isGeneratorClass() : method.getName() + " is called but is still tagged as generator";
            n.setProperty("callee", method);

            temporaryValues.pop();

            return default_language_object;
        }

        // does parsing and type checking
        public AbstractObjectOfLanguage visitlvalue(GNode n) {
            AbstractObjectOfLanguage lvalue = parseLValue(scope.peek(), n, this);
            lvalue.setNode(n);
            return lvalue;
        }

        public AbstractObjectOfLanguage visitlvalueExpression(GNode n) {
            // Two possible productions:
            // L_BRACKET expression R_BRACKET - size 3
            // L_BRACKET expression COLON expression R_BRACKET - size 5

            dispatch(getGNodeUnderConditional(n.getGeneric(1))); // always expression 

            if(n.size() == 5) { // L_BRACKET expression COLON expression R_BRACKET
                dispatch(getGNodeUnderConditional(n.getGeneric(3))); // expression
            }

            return default_language_object;
        }

        public AbstractObjectOfLanguage visitargument(GNode n) {
            assert !temporaryValues.empty();
            if(n.get(0) instanceof Syntax || 
                getValueUnderConditional(n.getGeneric(0)) instanceof Syntax) {
                temporaryValues.peek().addToParameters(baseTypesCollection.getDontCareLanguageObject());
                return baseTypesCollection.getDontCareLanguageObject();
            }
            
            AbstractObjectOfLanguage value; 
            if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "expression") {
                // System.out.println("visiting argument expression with name: " + getGNodeUnderConditional(n.getGeneric(0)).getName());
                value = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            } else {
                // System.out.println("visting names argument expression with name: " + getGNodeUnderConditional(n.getGeneric(0)).toString());
                value = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(2)));
            }
            temporaryValues.peek().addToParameters(value);
            return value;
        }

        public AbstractObjectOfLanguage visitexpression(GNode n) {
            // System.out.println("entering expression: " + n);
            if(n.get(0) instanceof Syntax && n.size() == 1) {
                // TODO: handle booleans separately and "this" word
                return p4LanguageObject.new OLangString(n.get(0).toString(), scope.peek());
            }

            Iterator itr = n.iterator();
            AbstractObjectOfLanguage finalValue = null;
            AbstractObjectOfLanguage localScope = scope.peek();
            while(itr.hasNext()) {
                // System.out.println("new final value: " + localScope + " with name: " + localScope.getName());
                Node next = (Node) itr.next();
                if(next instanceof Syntax) {
                    if(next.toString() == "[") {
                        // System.err.println("encountered [");
                        AbstractObjectOfLanguage number = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional((GNode) itr.next()));
                        Object nextVal = getValueUnderConditional((GNode) itr.next());
                        if(nextVal.toString() == ":") {
                            AbstractObjectOfLanguage secondNumber = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional((GNode) itr.next()));
                            nextVal = getValueUnderConditional((GNode) itr.next());
                        }
                        assert nextVal.toString() == "]";
                    }
                    // eg: NOT expression (skips over NOT and goes to expression)
                    finalValue = p4LanguageObject.new OLangString(next.toString(), scope.peek());
                    continue;
                }
                Object underConditional = getValueUnderConditional((GNode) next);

                if(underConditional instanceof Syntax) {
                    if(underConditional.toString() == "[") {
                        // System.err.println("encountered [");
                        AbstractObjectOfLanguage number = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional((GNode) itr.next()));
                        Object nextVal = getValueUnderConditional((GNode) itr.next());
                        if(nextVal.toString() == ":") {
                            AbstractObjectOfLanguage secondNumber = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional((GNode) itr.next()));
                            nextVal = getValueUnderConditional((GNode) itr.next());
                        }
                        assert nextVal.toString() == "]";
                    }
                    finalValue = p4LanguageObject.new OLangString(underConditional.toString(), scope.peek());
                    continue;
                }

                GNode childNode = (GNode) underConditional;
                // System.out.println("traversing: " + childNode.getName() + " " + childNode.toString());
                switch(childNode.getName()) {
                    // we tell symtab look up to not generate an instance if the look up value is of generator class
                    // since expression parsing for invoking expression is different and that's where we have to generate instances
                    // Here we are just look up values to type check
                    case "expression":
                        finalValue = (AbstractObjectOfLanguage) dispatch(childNode);
                        localScope = finalValue;
                        // System.out.println("expression: " + finalValue.getName());
                        break;
                    case "nonTypeName":
                        // nonTypeName
                        AbstractObjectOfLanguage lookup = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false, true, false);
                        assert !lookup.isGeneratorClass();
                        // System.out.println("found nonTypeName: " + lookup.getName());
                        finalValue = lookup;
                        localScope = lookup;
                        break;
                    case "dotPrefix":
                        // dotPrefix nonTypeName
                        // continuing because the while loop will reach nonTypeName
                        assert getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))).getName() == "nonTypeName";
                        childNode = getGNodeUnderConditional((GNode) itr.next());
                        assert childNode.getName() == "nonTypeName";
                        AbstractObjectOfLanguage lookupNonTypeName = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false, true, false);
                        assert !lookupNonTypeName.isGeneratorClass();

                        return lookupNonTypeName;
                    case "typeName":
                        // typeName dot_name
                        // doing namespacing
                        AbstractObjectOfLanguage typeNameLO = symtabLookup(localScope, getNameFromTypeName(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)))), true, false);
                        assert !typeNameLO.isGeneratorClass();
                        localScope = typeNameLO;
                        finalValue = typeNameLO;
                        // System.out.println("typeName: " + finalValue.getName());
                        break;
                    case "dot_name":
                        String dotNameString = getStringUnderDotName(childNode);
                        // System.out.println("localscope: " + localScope.getName());
                        AbstractObjectOfLanguage symtabLookUpValue = symtabLookup(localScope, dotNameString, true, false);
                        assert !symtabLookUpValue.isGeneratorClass();
                        // System.out.println("look up result: " + symtabLookUpValue.getName() + " under node: " + childNode);
                        finalValue = symtabLookUpValue;
                        localScope = finalValue;
                        // System.out.println("new value under dot name: " + dotNameString);
                        break;
                    default:
                        finalValue = (AbstractObjectOfLanguage) dispatch(childNode);
                        localScope = finalValue;
                        // System.out.println("default: " + finalValue.getName());
                }
            }
            assert finalValue != null;
            return finalValue;
        }

        public AbstractObjectOfLanguage visitinvokingExpression(GNode n) {
            AbstractObjectOfLanguage returnValue;

            temporaryValues.add(new TemporaryParameterValues());

            GNode nGetGeneric0 = getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)));
            if(nGetGeneric0.getName() == "namedType") {
                // one of three possible productions, starts with namedType
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // argumentList

                String namedType = getStringUnderNamedType(nGetGeneric0);
                AbstractObjectOfLanguage namedTypeObj = symtabLookup(scope.peek(), namedType);

                returnValue = namedTypeObj;
            } else { 
                // two possible productions, one contains extra set of type arguments 
                // inside angle brackets (of size 4 & 7)

                if(n.size() == 4) {
                    dispatch(getGNodeUnderConditional(n.getGeneric(2))); // argumentList
                } else {
                    dispatch(getGNodeUnderConditional(n.getGeneric(2))); // realTypeArgumentList
                    dispatch(getGNodeUnderConditional(n.getGeneric(5))); // argumentList
                }

                // first element pointing to name is an expression, extract from that
                AbstractObjectOfLanguage expressionCallee = getCalleeFromExpression(nGetGeneric0, this);

                returnValue = expressionCallee;
            }

            assert !returnValue.isGeneratorClass() : returnValue.getName() + " is called but is still tagged as generator";

            n.setProperty("callee", returnValue);

            temporaryValues.pop(); 
            return returnValue;
        }

        public AbstractObjectOfLanguage visitrealTypeArgumentList(GNode n) {
            // temporaryValues.getTypeParameters().clear();

            Iterator itr = n.iterator();
            while(itr.hasNext()) {
                Object nextVal = getValueUnderConditional(itr.next());
                if(nextVal instanceof Syntax) {
                    // COMMA
                    continue;
                }

                GNode nextChild = (GNode) nextVal;
                dispatch(nextChild);
            }

            return default_language_object;
        }

        public AbstractObjectOfLanguage visitrealTypeArg(GNode n) {
            AbstractObjectOfLanguage returnValue;
            if(getValueUnderConditional(n.get(0)) instanceof Syntax) {
                // void or dontcare (_)
                if(getValueUnderConditional(n.get(0)).toString() == "_") {
                    returnValue = baseTypesCollection.getDontCareLanguageObject();
                } else {
                    returnValue = baseTypesCollection.getVoidLanguageObject();
                }
            } else {
                returnValue = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            }

            assert !temporaryValues.empty();
            temporaryValues.peek().addToTypeParameters(returnValue);
            return returnValue;
        }

        public AbstractObjectOfLanguage visitexternDeclaration(GNode n) {
            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))).getName() == "externFunctionDeclaration") { // separate dispatch available for this
                // TODO: check if externFunctionDeclaration can be merged back again
                return (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))));
            } else {
                if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))).getName() == "nonTypeName") {
                    String externName = getStringUnderNonTypeName(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))));
                    AbstractObjectOfLanguage externObj = p4LanguageObject.new ExternDeclaration(externName, scope.peek());;
                    if(getGNodeUnderConditional(n.getGeneric(3)).size() > 0) {
                        externObj.setNode(n);
                        // has type parameters, so generator
                        externObj = p4LanguageObject.new ExternDeclarationGenerator((ExternDeclaration) externObj);
                    }

                    addToSymtab(scope.peek(), externName, externObj);
                    scope.add(externObj);

                    dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
                    dispatch(getGNodeUnderConditional(n.getGeneric(5))); // methodPrototypes

                    scope.pop();
                    externObj.setNode(n);
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
            // String externFunctionName = getStringUnderFunctionPrototype(n.getGeneric(2));
            // AbstractObjectOfLanguage externFunctionDeclarationObj = p4LanguageObject.new ExternFunctionDeclaration(externFunctionName, scope.peek());

            // if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2)).getGeneric(2)).size() > 0) {
            //     externFunctionDeclarationObj = p4LanguageObject.new ExternFunctionDeclarationGenerator((ExternFunctionDeclaration) externFunctionDeclarationObj);
            // }

            // addToSymtab(scope.peek(), externFunctionName, externFunctionDeclarationObj);
            // scope.add(externFunctionDeclarationObj);

            AbstractObjectOfLanguage functionPrototype = (AbstractObjectOfLanguage) visitfunctionPrototype(getGNodeUnderConditional(n.getGeneric(2)), LObjectKind.EXTERNFUNCTIONDECLARATION);

            // if(externFunctionDeclarationObj.isGeneratorClass()) {
            //     assert functionPrototype.isGeneratorClass();
            //     ((ExternFunctionDeclarationGenerator) externFunctionDeclarationObj).setFunctionPrototype((FunctionPrototypeGenerator)functionPrototype);
            // } else {
            //     assert !functionPrototype.isGeneratorClass();
            //     ((ExternFunctionDeclaration) externFunctionDeclarationObj).setFunctionPrototype((FunctionPrototype)functionPrototype);
            // }
            // // externFunctionDeclarationObj.setFunctionPrototype(functionPrototype);

            // scope.pop();
            functionPrototype.setNode(n);
            return functionPrototype;
        }

        // Interesting: functionDeclaration not part of P416? not in online language specification -- experimental
        //
        public AbstractObjectOfLanguage visitfunctionDeclaration(GNode n) {
            // as per language specification, functionPrototype will describe the name and type signature of the function
            // String functionName = getStringUnderFunctionPrototype(getGNodeUnderConditional(n.getGeneric(0)));
            // AbstractObjectOfLanguage functionObj = p4LanguageObject.new FunctionDeclaration(functionName, scope.peek());

            // if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)).getGeneric(2)).size() > 0) {
            //     functionObj = p4LanguageObject.new FunctionDeclarationGenerator((FunctionDeclaration) functionObj);
            // }

            // addToSymtab(scope.peek(), functionName, functionObj);
            // scope.add(functionObj);

            AbstractObjectOfLanguage functionPrototype = visitfunctionPrototype(getGNodeUnderConditional(n.getGeneric(0)), LObjectKind.FUNCTIONDECLARATION); // functionPrototype (for parameters)
            scope.add(functionPrototype);
            AbstractObjectOfLanguage blockStatement = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(1))); // blockstatement

            if(functionPrototype.isGeneratorClass()) {
                assert functionPrototype.isGeneratorClass();
                // ((FunctionDeclarationGenerator) functionPrototype).setFunctionPrototype((FunctionPrototypeGenerator) functionPrototype);
                ((FunctionDeclarationGenerator) functionPrototype).setBlockStatement(blockStatement);
            } else {
                // ((FunctionDeclaration) functionPrototype).setFunctionPrototype((FunctionPrototype) functionPrototype);
                ((FunctionDeclaration) functionPrototype).setBlockStatement(blockStatement);
            }
            
            scope.pop();
            functionPrototype.setNode(n);
            return functionPrototype;
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

            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))).getName() == "constructorMethodPrototype") {
                return (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))));
            } else if(n.get(1) instanceof Syntax) { // keyword ABSTRACT
                // TODO: need to handle abstract methods
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations

                AbstractObjectOfLanguage functionObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))));

                return functionObj;
            } else {
                assert getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations

                AbstractObjectOfLanguage functionObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))));

                return functionObj;
            }
        }

        public AbstractObjectOfLanguage visitconstructorMethodPrototype(GNode n) {            
            String type_identifier = n.get(1).toString();
            // System.out.println("constructor inside: " + type_identifier);

            // methodPrototype -> constructorMethodPrototype is directly under parent extern scope
            // so can retrieve the extern block's name from the scope

            assert type_identifier.equals(scope.peek().getName()) : "Extern constructor not of the same name as extern block. Potential constructor name: " + type_identifier + ", extern name: " + scope.peek().getName();
            AbstractObjectOfLanguage constructor = addToSymtab(scope.peek(), type_identifier);
            // scope.add(constructor);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // parameterList

            // scope.pop();

            return constructor;
        }

        public AbstractObjectOfLanguage visitparameter(GNode n) {
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations
            GNode typeRefNode = getGNodeUnderConditional(n.getGeneric(2));
            // String type_ref_string = getTypeStringUnderTypeRef(typeRefNode);
            String name = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));
            String directionString;
            if(getGNodeUnderConditional(n.getGeneric(1)).size() > 0) {
                directionString = getGNodeUnderConditional(n.getGeneric(1)).get(0).toString();
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

            parameterType = (AbstractObjectOfLanguage) dispatch(typeRefNode);

            AbstractObjectOfLanguage newParameterObj;
            AbstractObjectOfLanguage expression = null;

            if(n.size() == 6) {
                assert direction == null || direction == directionClass.getLanguageObjectOfDirection("in");
                // "optAnnotations direction typeRef name ASSIGN expression {}" productiom
                // so need to take care of expression
                // The other production is just "optAnnotations direction typeRef name"
                expression = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(5)));

                assert !expression.isGeneratorClass();
                if(expression.hasAssociatedType()) {
                    assert !expression.getType().isGeneratorClass();
                }
            }

            newParameterObj = p4LanguageObject.new Parameter(name, scope.peek(), parameterType, direction, expression);

            if(parameterType.getConstructType() == LObjectKind.TYPEPARAMETER) {
                newParameterObj.setNode(n);
                newParameterObj = p4LanguageObject.new ParameterGenerator((Parameter) newParameterObj);
                // assert scope.peek().isGeneratorClass() : "Trying to add generic parameter: " + newParameterObj.getName() + " but parent is set to be generator class. Parent: " + scope.peek().getName() + "(" + scope.peek().getConstructType() + ")";
            }
            // System.out.println("adding new parameter: '" + name + "' to scope: " + scope.peek().getName() + " " + scope.peek());
            addToSymtab(scope.peek(), name, newParameterObj);
            scope.peek().addParameter(newParameterObj);

            newParameterObj.setNode(n);
            return newParameterObj;
        }

        public AbstractObjectOfLanguage visittypeParameterList(GNode n) {
            /*
            Two possible productions:
                name
                typeParameterList COMMA name ----- list
            */
            TypeParameter typeParameterObj = null;
            // typeParameterList is tagged as list, so instead of being recursive it will have a list
            // of type parameters. So iterating over them
            Iterator itr = n.iterator();
            Node next;
            while(itr.hasNext()) {
                next = (Node) itr.next();
                assert next instanceof GNode == true;
                GNode childNode = (GNode) next;
                Object valueUnderConditional = getValueUnderConditional(childNode);
                if (valueUnderConditional instanceof Syntax) continue; // ","
                childNode = (GNode) valueUnderConditional;
                assert childNode.getName() == "name";
                String name = getStringUnderName(childNode);
                // System.out.println("adding type parameter: " + name + " to scope: " + scope.peek().getName());
                AbstractObjectOfLanguage retrievedValue = retrieveSymbolOrTypeVariable(scope.peek(), name);
                assert retrievedValue.getConstructType() == LObjectKind.TYPEPARAMETER : "assertion failed. Expected typeparmeter construct type but got: " + retrievedValue.getConstructType();
                typeParameterObj = (TypeParameter) retrievedValue;
                // since type parameters only occur inside optTypeParameters
                assert scope.peek().isGeneratorClass() : "Scope is under: " + scope.peek().getName() + " that is not a generator class. Of construct type: " + scope.peek().getConstructType();
                ((Generator) scope.peek()).addOptTypeParameters(typeParameterObj);
                // addToSymtab(scope.peek(), name, typeParameterObj);
            }
            assert typeParameterObj != null;

            return typeParameterObj;
        }

        public AbstractObjectOfLanguage visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(getGNodeUnderConditional(n.getGeneric(0)));
            
            ParserDeclaration parserObj = p4LanguageObject.new ParserDeclaration(parserName, scope.peek());
            // if it has type parameters under parserTypeDeclaration, cannot happen as per language specifications
            // (https://p4.org/p4-spec/docs/P4-16-working-spec.html#sec-parser-decl)
            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))).getGeneric(3).size() > 0) {
                System.err.println("Parser declaration (" + parserName + ") cannot have generics.");
                System.exit(1);
            }

            addToSymtab(scope.peek(), parserName, parserObj);
            scope.add(parserObj);

            AbstractObjectOfLanguage parserTypeDeclaration = visitparserTypeDeclaration(getGNodeUnderConditional(n.getGeneric(0)), false);
            assert !parserTypeDeclaration.isGeneratorClass();
            parserObj.setParserTypeDeclaration((ParserTypeDeclaration) parserTypeDeclaration);

            dispatch(getGNodeUnderConditional(n.getGeneric(1))); // optConstructorParameters
            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parserStates

            // built in parser states
            addToSymtab(scope.peek(), "accept");
            addToSymtab(scope.peek(), "reject");

            // built in functions
            addToSymtab(scope.peek(), "apply", p4LanguageObject.new InvokableLanguageKeyword("apply", scope.peek()));

            scope.pop();

            parserObj.setNode(n);

            return parserObj;
        }

        public AbstractObjectOfLanguage visittypeArg(GNode n) {
            AbstractObjectOfLanguage returnValue;
            if(getValueUnderConditional(n.get(0)) instanceof Syntax) {
                // void or dontcare (_)
                if(getValueUnderConditional(n.get(0)).toString() == "_") {
                    returnValue = baseTypesCollection.getDontCareLanguageObject();
                } else {
                    returnValue = baseTypesCollection.getVoidLanguageObject();
                }
            } else {
                if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "nonTypeName") {
                    String name = getStringUnderNonTypeName(getGNodeUnderConditional(n.getGeneric(0)));
                    returnValue = nonTypeNameSymtabLookUp(scope.peek(), name, true);
                } else {
                    returnValue = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
                }
            }

            assert !temporaryValues.empty();
            temporaryValues.peek().addToTypeParameters(returnValue);
            return returnValue;
        }

        public AbstractObjectOfLanguage visittupleType(GNode n) {
            temporaryValues.add(new TemporaryParameterValues());
            TupleType newTuple = p4LanguageObject.new TupleType(scope.peek());

            dispatch(getGNodeUnderConditional(n.getGeneric(2)));

            temporaryValues.pop();

            newTuple.setNode(n);

            return newTuple;
        }

        public AbstractObjectOfLanguage visitspecializedType(GNode n) {
            return visitspecializedType(n, false);
        }

        // has special variable for fromInstantiation since instantiation construct
        // can provide its own parameter arguments that can be used to look up symtab constructs
        // with generic
        public AbstractObjectOfLanguage visitspecializedType(GNode n, boolean fromInstantiation) {
            String name = getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));

            if(! fromInstantiation) {
                temporaryValues.add(new TemporaryParameterValues());
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(2))); // typeArgumentList

            AbstractObjectOfLanguage typeObj = symtabLookup(scope.peek(), name);

            if(! fromInstantiation) {
                temporaryValues.pop();
            }

            return typeObj;
        }

        public AbstractObjectOfLanguage visitheaderStackType(GNode n) {
            return visitheaderStackType(n, false);
        }

        public AbstractObjectOfLanguage visitheaderStackType(GNode n, boolean fromInstantiation) {
            // since header stack type is just a regular header or specialized type with multiple
            // instances (an array of headers) - https://p4.org/p4-spec/docs/P4-16-working-spec.html#sec-header-stacks
            // TODO: we do not keep track of number of elements in the array
            GNode firstChild = getGNodeUnderConditional(n.getGeneric(0));
            if(firstChild.getName() == "typeName") {
                // TODO: right now the new header name is set to the same of the type itself and is placed under the original value scope
                // ex: complex2.p4
                String name = getNameFromTypeName(firstChild);
                AbstractObjectOfLanguage headerValue = symtabLookup(scope.peek(), name);
                assert headerValue.getConstructType() == LObjectKind.HEADERTYPEDECLARATION;
                // System.out.println("new header stack type: " + name + " creating under scope: " + headerValue.getName());
                HeaderStackType newHdrStack = p4LanguageObject.new HeaderStackType(name, headerValue, (HeaderTypeDeclaration) headerValue);
                addToSymtab(headerValue, name, newHdrStack);

                InvokableLanguageKeyword next = p4LanguageObject.new InvokableLanguageKeyword("next", newHdrStack);
                InvokableLanguageKeyword last = p4LanguageObject.new InvokableLanguageKeyword("last", newHdrStack);
                InvokableLanguageKeyword lastIndex = p4LanguageObject.new InvokableLanguageKeyword("lastIndex", newHdrStack);
                InvokableLanguageKeyword size = p4LanguageObject.new InvokableLanguageKeyword("size", newHdrStack);
                FunctionPrototype pushFront = p4LanguageObject.new FunctionPrototype("push_front", newHdrStack, baseTypesCollection.getVoidLanguageObject());
                FunctionPrototype popFront = p4LanguageObject.new FunctionPrototype("pop_front", newHdrStack, baseTypesCollection.getVoidLanguageObject());
                addToSymtab(newHdrStack, "next", next);
                addToSymtab(newHdrStack, "last", last);
                addToSymtab(newHdrStack, "lastIndex", lastIndex);
                addToSymtab(newHdrStack, "size", size);
                addToSymtab(newHdrStack, "push_front", pushFront);
                addToSymtab(newHdrStack, "pop_front", popFront);

                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // expression

                newHdrStack.setNode(n);

                return newHdrStack;
            } else {
                // specializedType
                assert firstChild.getName() == "specializedType";
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // expression
                AbstractObjectOfLanguage specializedType = (AbstractObjectOfLanguage) visitspecializedType(firstChild, fromInstantiation);
                specializedType.setNode(n);

                return specializedType;
            }
        }

        public AbstractObjectOfLanguage visitvalueSetDeclaration(GNode n) {
            AbstractObjectOfLanguage type;
            String name = getStringUnderName(getGNodeUnderConditional(n.getGeneric(8)));
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations
            AbstractObjectOfLanguage newobj = addToSymtab(scope.peek(), name);
            scope.add(newobj);

            switch(getGNodeUnderConditional(n.getGeneric(3)).getName()) {
                case "typeName":
                    String typeName = getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(3)));
                    type = symtabLookup(scope.peek(), typeName);
                    break;
                case "baseType":
                    String baseTypeString = getBaseTypeAsString(getGNodeUnderConditional(n.getGeneric(3)));
                    type = baseTypesCollection.getLanguageObjectOfBaseType(baseTypeString);
                    break;
                case "tupleType":
                    type = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(3)));
                    break;
            }
            dispatch(getGNodeUnderConditional(n.getGeneric(6))); // expression

            scope.pop();

            newobj.setNode(n);

            return newobj;
        }

        public AbstractObjectOfLanguage visitparserState(GNode n) {
            String stateName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            assert stateName != "accept" && stateName != "reject";
            AbstractObjectOfLanguage stateObj = addToSymtab(scope.peek(), stateName);
            scope.add(stateObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parserStatements
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // transitionStatement

            scope.pop();

            stateObj.setNode(n);
            
            return stateObj;

        }

        public AbstractObjectOfLanguage visitstateExpression(GNode n) {
            if(n.size() == 1) { // selectExpression; (name SEMICOLON is handled in callGraphVisitor)
                return (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            }
            return default_language_object;
        }

        // TODO: check if we need to list table scope (if not, remove from callGraphGenerator as well)
        // TODO: take care of MATCH_KIND and KEY ASSIGN production of tablepropertylist
        public AbstractObjectOfLanguage visittableDeclaration(GNode n) {
            String tableName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage tableObj = addToSymtab(scope.peek(), tableName);
            scope.add(tableObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // tablePropertyList

            // built in functions
            EnumDeclaration actionList = p4LanguageObject.new EnumDeclaration("action_list", scope.peek());
            addToSymtab(scope.peek(), "action_list", actionList);

            InvokableLanguageKeyword applyKeyword = p4LanguageObject.new InvokableLanguageKeyword("apply", scope.peek());
            addToSymtab(scope.peek(), "apply", applyKeyword);
            scope.add(applyKeyword);

            Variable hit = p4LanguageObject.new Variable("hit", scope.peek(), baseTypesCollection.getLanguageObjectOfBaseType("bool"));
            Variable miss = p4LanguageObject.new Variable("miss", scope.peek(), baseTypesCollection.getLanguageObjectOfBaseType("bool"));
            Variable actionRun = p4LanguageObject.new Variable("action_run", scope.peek(), actionList);
            addToSymtab(scope.peek(), "hit", hit);
            addToSymtab(scope.peek(), "miss", miss);
            addToSymtab(scope.peek(), "action_run", actionRun);

            scope.pop();

            scope.pop();

            tableObj.setNode(n);

            return tableObj;
        }

        public AbstractObjectOfLanguage visitconstantDeclaration(GNode n) {
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations
            String name = getStringUnderName(getGNodeUnderConditional(n.getGeneric(3)));
            AbstractObjectOfLanguage typeRefObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(2)));
            typeRefObj = (typeRefObj.hasAssociatedType() ? typeRefObj.getType() : typeRefObj);
            AbstractObjectOfLanguage constVariable = p4LanguageObject.new Variable(name, scope.peek(), typeRefObj);
            if(typeRefObj.getConstructType() == LObjectKind.TYPEPARAMETER || typeRefObj.isGeneratorClass()) {
                constVariable.setNode(n);
                constVariable = p4LanguageObject.new VariableGenerator((Variable) constVariable);
            }
            addToSymtab(scope.peek(), name, constVariable);
            scope.add(constVariable);

            AbstractObjectOfLanguage initializer = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(5)));
            assert !initializer.isGeneratorClass();
            if(constVariable.isGeneratorClass()) {
                ((VariableGenerator) constVariable).setAssignedExpression(initializer);    
            } else {
                ((Variable) constVariable).setAssignedExpression(initializer);
            }

            scope.pop();

            constVariable.setNode(n);

            return constVariable;
        }

        public AbstractObjectOfLanguage visitaction(GNode n) {
            temporaryValues.add(new TemporaryParameterValues());
            String actionRefName = getNameUnderActionRef(getGNodeUnderConditional(n.getGeneric(1)));
            if(getGNodeUnderConditional(n.getGeneric(1)).size() > 1) {
                // actionRef production contains argumentlist
                dispatch(getGNodeUnderConditional(n.getGeneric(1)).getGeneric(2)); // argumentList
            }

            temporaryValues.pop();
            return symtabLookup(scope.peek(), actionRefName);
        }

        public AbstractObjectOfLanguage visitentry(GNode n) {
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // keysetExpression
            String actionRefName = getNameUnderActionRef(getGNodeUnderConditional(n.getGeneric(2)));
            if(getGNodeUnderConditional(n.getGeneric(2)).size() > 1) {
                // actionRef production contains argumentlist
                dispatch(getGNodeUnderConditional(n.getGeneric(2)).getGeneric(2));
            }

            AbstractObjectOfLanguage actionRefObj = symtabLookup(scope.peek(), actionRefName);
            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optAnnotations

            return actionRefObj;
        }

        public AbstractObjectOfLanguage visitinstantiation(GNode n) {
            int typeRefIndx = 0;

            if(n.getGeneric(0).getName() == "annotations") {
                typeRefIndx = 1;
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // annotations
            }

            temporaryValues.add(new TemporaryParameterValues());
            AbstractObjectOfLanguage typeRefObj;
            dispatch(n.getGeneric(typeRefIndx + 2)); // argumentList
            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(typeRefIndx)).getGeneric(0)).getName() == "specializedType") {
                typeRefObj = visitspecializedType(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(typeRefIndx)).getGeneric(0)), true);
            } else if  (getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(typeRefIndx)).getGeneric(0)).getName() == "headerStackType") {
                typeRefObj = visitheaderStackType(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(typeRefIndx)).getGeneric(0)), true);
            } else {
                typeRefObj = (AbstractObjectOfLanguage) dispatch(getGNodeUnderConditional(n.getGeneric(typeRefIndx)));
            }

            String name = getStringUnderName(getGNodeUnderConditional(n.getGeneric(typeRefIndx+4)));
            SubClass instantiationVar = p4LanguageObject.new SubClass(name, scope.peek(), typeRefObj);
            addToSymtab(scope.peek(), name, instantiationVar);

            scope.add(instantiationVar);

            if(n.size() > typeRefIndx + 6) {
                dispatch(getGNodeUnderConditional(n.getGeneric(typeRefIndx + 6))); // objInitializer
            }

            scope.pop();

            temporaryValues.pop();
            instantiationVar.setNode(n);

            return instantiationVar;
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
            String controlBlockName = getNameOfControlBlock(getGNodeUnderConditional(n.getGeneric(0)));

            AbstractObjectOfLanguage controlObj = symtabLookup(scope.peek(), controlBlockName, true, false);
            scope.add(controlObj);

            // skipping visiting controlTypeDeclaration

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // controlLocalDeclarations
            String applyBlockName = n.get(4).toString();

            // start parse controlBody
            GNode oldN = n;
            n = getGNodeUnderConditional(n.getGeneric(5)); // controlBody
            AbstractObjectOfLanguage apply = symtabLookup(scope.peek(), applyBlockName, true, false);
            // lookupInSymTabAndAddAsCallee(applyBlockName); // TODO: ask if need to insert this as a callee?
            scope.add(apply);

            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // controlBody can have only one child
            
            scope.pop();
            n = oldN;
            //end parse controlBody

            scope.pop();
            return n;
        }

        public Node visitactionDeclaration(GNode n) {
            // Each action in the list of actions for a table must have a distinct name
            String actionBlockName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage actionObj = symtabLookup(scope.peek(), actionBlockName, true, false);
            scope.add(actionObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parameterList
            dispatch(getGNodeUnderConditional(n.getGeneric(6))); // blockStatement 

            scope.pop();

            return n;
        }

        // Interesting: functionDeclaration not part of P416? not in online language specification -- experimental
        //
        public Node visitfunctionDeclaration(GNode n) {
            // TODO: need to take care of typeOrVoid if we are keeping track of defined variables (can devolve into identifier or type ident)
            dispatch(getGNodeUnderConditional(n.getGeneric(0)));

            // as per language specification, functionPrototype will describe the name and type signature of the function
            String functionName = getStringUnderFunctionPrototype(getGNodeUnderConditional(n.getGeneric(0)));
            AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName, true, false);
            scope.add(functionObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // functionPrototype (for parameters)
            dispatch(getGNodeUnderConditional(n.getGeneric(1))); // blockstatement

            scope.pop();
            return n;
        }

        public Node visitparserDeclaration(GNode n) {
            String parserName = getStringUnderParserTypeDeclaration(getGNodeUnderConditional(n.getGeneric(0))); // TODO: take of parameter list here if needed to
            AbstractObjectOfLanguage parserObj = symtabLookup(scope.peek(), parserName, true, false);
            scope.add(parserObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // parserLocalElements TODO: valueSetDeclaration needs to be traced for data flow
            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parserStates

            scope.pop();

            return n;
        }

        public Node visitparserState(GNode n) {
            String stateName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));

            AbstractObjectOfLanguage stateObj = symtabLookup(scope.peek(), stateName, true, false);
            scope.add(stateObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // parserStatements
            dispatch(getGNodeUnderConditional(n.getGeneric(5))); // transitionStatement

            scope.pop();
            
            return n;

        }

        public Node visitexternDeclaration(GNode n) {
            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))).getName() == "externFunctionDeclaration") { // generic dispatch
                dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))));
                return n;
            } else {
                if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))).getName() == "nonTypeName") {
                    String externName = getStringUnderNonTypeName(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))));
                    AbstractObjectOfLanguage externObj = symtabLookup(scope.peek(), externName, true, false);
                    scope.add(externObj);

                    dispatch(getGNodeUnderConditional(n.getGeneric(3))); // optTypeParameters
                    dispatch(getGNodeUnderConditional(n.getGeneric(5))); // methodPrototypes

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

            if(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0))).getName() == "constructorMethodPrototype") {
                dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            } else if(n.get(1) instanceof Syntax) { // keyword ABSTRACT
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations

                // TODO: need to handle abstract methods
                String functionName = getStringUnderFunctionPrototype(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2))));
                AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName, true, false);
                scope.add(functionObj);

                dispatch(getGNodeUnderConditional(n.getGeneric(2)));

                scope.pop();
            } else {
                assert getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))).getName() == "functionPrototype" : "unhandled case in method prototype";
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // optAnnotations
                String functionName = getStringUnderFunctionPrototype(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))));
                AbstractObjectOfLanguage functionObj = symtabLookup(scope.peek(), functionName, true, false);
                scope.add(functionObj);

                dispatch(getGNodeUnderConditional(n.getGeneric(1)));

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
            AbstractObjectOfLanguage constructor = symtabLookup(scope.peek(), type_identifier, true, false);
            scope.add(constructor);

            dispatch(getGNodeUnderConditional(n.getGeneric(3))); // parameterList

            scope.pop();

            return n;
        }

        public Node visitdirectApplication(GNode n) {
            // As per the grammar we can have only one typename before the `.apply`, so nesting can't happen
            // TODO: put this in type checker and get callee from node like in visitmethodcallstatment
            temporaryValues.add(new TemporaryParameterValues());

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // argumentList

            String calleeName = getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));

            lookupInSymTabAndAddAsCallee(calleeName);

            temporaryValues.pop();
            return n;
        }

        public Node visitassignmentOrMethodCallStatement(GNode n) {
            if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "methodCallStatements") {
                // method call statements
                dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            } else { // TODO: make clear which production
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // lvalue
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // expression
            }

            return n;
        }

        public Node visitmethodCallStatements(GNode n) {
            assert n.hasProperty("callee");
            addAsCallee((AbstractObjectOfLanguage) n.getProperty("callee"));

            temporaryValues.add(new TemporaryParameterValues());

            // There are two possible set of sub productions, both which have argument list under it
            // but one has typeArgumentList before argument list, so argumentList is not at the same place
            // hence check the size to see which production we are currently under and dispatching
            // the visitor at the respective argumentList position
            if(n.size() == 5) {
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); //argumentlist
            } else {
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // typeArgumentList 
                dispatch(getGNodeUnderConditional(n.getGeneric(5))); // argumentList
            }

            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // lvalue

            // only legal value of lvalue for method call statements is prefixedNonTypeName
            // with dot_name as lvalueExpressions cannot be used for method call statements
            // (see end of document). getStringUnderLvaluePrefixNonTypeName asserts that
            // String calleeMethodName = getStringUnderLvaluePrefixNonTypeName(getGNodeUnderConditional(n.getGeneric(0)), this);
            // AbstractObjectOfLanguage lvalueFinal = parseLValue(scope.peek(), getGNodeUnderConditional(n.getGeneric(0)), this);
            // if(calleeMethodName == "this") {
            //     addAsCallee(getParentInstance(scope.peek()));
            // } else {
            //     // lookupInSymTabAndAddAsCallee(calleeMethodName);
            //     addAsCallee(lvalueFinal);
            // }

            
            temporaryValues.pop();
            return n;
        }

        // TODO: check if we need to list table scope (if not, remove from definitions dispatcher as well)
        public Node visittableDeclaration(GNode n) {
            String tableName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            AbstractObjectOfLanguage tableObj = symtabLookup(scope.peek(), tableName, true, false);
            scope.add(tableObj);

            dispatch(getGNodeUnderConditional(n.getGeneric(4))); // tablePropertyList

            scope.pop();

            return n;
        }

        public Node visitstateExpression(GNode n) {
            if(n.size() == 2) { // name SEMICOLON
                // TODO: need to handle keywords like accept or reject
                String stateName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(0)));
                lookupInSymTabAndAddAsCallee(stateName);
            } else { // selectExpression;
                dispatch(getGNodeUnderConditional(n.getGeneric(0)));
            }
            return n;
        }

        public Node visitselectCase(GNode n) {
            // TODO trace keysetExpression for data
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // keysetExpression

            String selectName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
            lookupInSymTabAndAddAsCallee(selectName);

            return n;
        }

        public Node visitaction(GNode n) {
            // TODO: calculate callee in type checker and retrieve callee from node like in visitmethodcallstatment
            temporaryValues.add(new TemporaryParameterValues());
            String actionRefName = getNameUnderActionRef(getGNodeUnderConditional(n.getGeneric(1)));
            if(getGNodeUnderConditional(n.getGeneric(1)).size() > 1) {
                // actionRef production contains argumentlist
                dispatch(getGNodeUnderConditional(n.getGeneric(1)).getGeneric(2));
            }
            lookupInSymTabAndAddAsCallee(actionRefName);

            temporaryValues.pop();
            return n;
        }

        public Node visitentry(GNode n) {
            dispatch(getGNodeUnderConditional(n.getGeneric(0))); // keysetExpression
            String actionRefName = getNameUnderActionRef(getGNodeUnderConditional(n.getGeneric(2)));
            if(getGNodeUnderConditional(n.getGeneric(2)).size() > 1) {
                // actionRef production contains argumentlist
                dispatch(getGNodeUnderConditional(n.getGeneric(2)).getGeneric(2));
            }
            dispatch(getGNodeUnderConditional(n.getGeneric(3)));

            lookupInSymTabAndAddAsCallee(actionRefName);

            return n;
        }

        public Node visitinvokingExpression(GNode n) {
            assert n.hasProperty("callee");
            addAsCallee((AbstractObjectOfLanguage) n.getProperty("callee"));

            temporaryValues.add(new TemporaryParameterValues());

            GNode nGetGeneric0 = getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)));
            if(nGetGeneric0.getName() == "namedType") {
                // one of three possible productions, starts with namedType
                dispatch(getGNodeUnderConditional(n.getGeneric(2))); // argumentList
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // namedType
            } else { // first element pointing to name is an expression
                if(n.size() == 4) {
                    dispatch(getGNodeUnderConditional(n.getGeneric(2))); // argumentList
                } else {
                    dispatch(getGNodeUnderConditional(n.getGeneric(2))); // realTypeArgumentList
                    dispatch(getGNodeUnderConditional(n.getGeneric(5))); // argumentList
                }

                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // expression
            }

            temporaryValues.pop();

            return n;
        }

        public Node visitinvokingNonBraceExpression(GNode n) {
            temporaryValues.add(new TemporaryParameterValues());

            GNode nGetGeneric0 = getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)));
            if(nGetGeneric0.getName() == "namedType") {
                // one of three possible productions, starts with namedType
                String namedType = getStringUnderNamedType(nGetGeneric0);
                lookupInSymTabAndAddAsCallee(namedType);

                dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2)))); // argumentList
            } else { // first element pointing to name is an expression, extract from that
                AbstractObjectOfLanguage expressionCallee = getCalleeFromNonBraceExpression(nGetGeneric0);
                addAsCallee(expressionCallee);

                // two possible productions, one contains extra set of type arguments 
                // inside angle brackets (of size 4 & 7)
                if(n.size() == 4) {
                    dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(2)))); // argumentList
                } else {
                    dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(3)))); // realTypeArgumentList
                    dispatch(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(5)))); // argumentList
                    // TODO: data inside realTypeArguments? can refer nontypenames
                }
            }

            temporaryValues.pop();

            return n;
        }

        public Node visitinstantiation(GNode n) {
            // TODO: calculate callee in type checking phase
            temporaryValues.add(new TemporaryParameterValues());
            int typeRefIndx = 0;

            if(n.getGeneric(0).getName() == "annotations") {
                typeRefIndx = 1;
                dispatch(getGNodeUnderConditional(n.getGeneric(0))); // annotations
            }
            
            String instanceName = getStringUnderName(getGNodeUnderConditional(n.getGeneric(typeRefIndx + 4)));

            dispatch(getGNodeUnderConditional(n.getGeneric(typeRefIndx + 2))); // argumentList

            AbstractObjectOfLanguage instanceType = symtabLookup(scope.peek(), instanceName);

            // assert instanceType.getConstructType() == LObjectKind.SUBCLASS : instanceType.getName() + " has constructor: " + instanceType.getConstructType() + " instead of ";

            addAsCallee(instanceType);

            scope.add(instanceType);
            if(n.size() > typeRefIndx + 6) {
                dispatch(getGNodeUnderConditional(n.getGeneric(typeRefIndx + 6))); // optInitializer
            }
            scope.pop();
            temporaryValues.pop();

            return n;
        }
    };

    /**
     * Given an actionRef node, gets the name of the mentioned action and returns that
     * @param n actionRef node
     * @return Returns the String present under the actionRef
     */
    public String getNameUnderActionRef(GNode n) {
        assert n.getName() == "actionRef";

        String actionRefName = getStringUnderPrefixedNonTypeName(getGNodeUnderConditional(n.getGeneric(0)));

        return actionRefName;
    }

    public AbstractObjectOfLanguage getAssociatedGenericValueIfGeneric(AbstractObjectOfLanguage typeObject, GNode n) {
        if(typeObject.getConstructType() == LObjectKind.TYPEPARAMETER) {
            return getAssociatedValueOfGenericType(typeObject, n);
        }

        return typeObject;
    }    

    public AbstractObjectOfLanguage getAssociatedValueOfGenericType(AbstractObjectOfLanguage typeParameter, GNode mainNode) {
        assert typeParameter.getConstructType() == LObjectKind.TYPEPARAMETER;

        AbstractObjectOfLanguage parent = typeParameter.getNameSpace();
        // System.out.println("Retrieved parent: " + parent.getName() + " of construct type: " + parent.getConstructType());
        assert parent.isGeneratorClass();
        Generator parent_cast = (Generator) parent;
        assert mainNode.hasProperty("parsedOptTypeParameters") : mainNode;
        ArrayList<AbstractObjectOfLanguage> parsedOptTypeParameters = (ArrayList<AbstractObjectOfLanguage>) mainNode.getProperty("parsedOptTypeParameters");
        // System.out.println("property values: " + parsedOptTypeParameters.get(0).getName());
        int indexOfType = parent_cast.getOptTypeParameters().indexOf(typeParameter);

        assert parsedOptTypeParameters.size() >= indexOfType + 1;

        return parsedOptTypeParameters.get(indexOfType);
        // if(expressionCallee.hasAssociatedType() && expressionCallee.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
        //     // System.out.println("Return type is of type parameter: " + expressionCallee.getType().getName());
        //     int indexOfReturnType = expressionCallee.getOptTypeParameters().indexOf(expressionCallee.getType());
        //     assert expressionCallee.hasParsedOptTypeParameters() && expressionCallee.getParsedOptTypeParameters().size() >= indexOfReturnType + 1;

        //     expressionCallee = expressionCallee.getParsedOptTypeParameters().get(indexOfReturnType);
        //     // System.err.println("It's final return value is of type: " + expressionCallee.getName());
    }

    /**
     * Handles possible expressions that can be used to invoke an entity.
     * 
     * Specifically invoked when the expression is inside an invoking expression
     * and is invoking a previously declared entity (callee).
     * Handles those possible expressions, including namespacing if present, and adds
     * the invoked entity as a call to the current scope object.
     * 
     * nonTypeName, dotPrefix nonTypeName, typeName dot_name, expression dot_name
     * Note: `NOT expression` will be taken care of by recursion
     * @param n
     * @return
     */
    public AbstractObjectOfLanguage getCalleeFromExpression(GNode n, Visitor visitor) {
        Iterator itr = n.iterator();
        AbstractObjectOfLanguage finalValue = null;
        AbstractObjectOfLanguage localScope = scope.peek();
        while(itr.hasNext()) {
            Node next = (Node) itr.next();
            if(next instanceof Syntax) {
                if(next.toString() == "!") {
                    continue;
                } else if(next.toString() == "this") {
                    finalValue = getParentInstance(localScope);
                    localScope = finalValue;
                } else if(next.toString() == "[") {
                    // System.err.println("encountered [");
                    visitor.dispatch(getGNodeUnderConditional((GNode) itr.next()));
                    Object nextVal = getValueUnderConditional((GNode) itr.next());
                    if(nextVal.toString() == ":") {
                        visitor.dispatch(getGNodeUnderConditional((GNode) itr.next()));
                        nextVal = getValueUnderConditional((GNode) itr.next());
                    }
                    assert nextVal.toString() == "]";
                } else if(next.toString() == "(") {
                    // casting -> production: L_PAREN typeRef R_PAREN expression %prec PREFIX
                    // return the value under the last expression value
                    return getCalleeFromExpression(getGNodeUnderConditional(n.getGeneric(3)), visitor);
                }  else {
                    assert false : "Encountered an invalid expression when expecting something to be invoked (" + next.toString() + ")";
                }
                continue;
            }

            Object underConditional = getValueUnderConditional((GNode) next);
            if(underConditional instanceof Syntax) {
                if(underConditional.toString() == "!") {
                    continue;
                } else if(underConditional.toString() == "this") {
                    finalValue = getParentInstance(localScope);
                    localScope = finalValue;
                } else if(underConditional.toString() == "[") {
                    // System.err.println("encountered [");
                    visitor.dispatch(getGNodeUnderConditional((GNode) itr.next()));
                    Object nextVal = getValueUnderConditional((GNode) itr.next());
                    if(nextVal.toString() == ":") {
                        visitor.dispatch(getGNodeUnderConditional((GNode) itr.next()));
                        nextVal = getValueUnderConditional((GNode) itr.next());
                    }
                    assert nextVal.toString() == "]";
                } else if(underConditional.toString() == "(") {
                    // casting -> production: L_PAREN typeRef R_PAREN expression %prec PREFIX
                    // return the value under the last expression value
                    return getCalleeFromExpression(getGNodeUnderConditional(n.getGeneric(3)), visitor);
                } else {
                    assert false : "Encountered an invalid expression when expecting something to be invoked (" + underConditional.toString() + ")";
                }
                continue;
            }

            GNode childNode = (GNode) underConditional;
            switch(childNode.getName()) {
                case "expression":
                    finalValue = getCalleeFromExpression(childNode, visitor);
                    localScope = finalValue;
                    assert getGNodeUnderConditional(n.getGeneric(1)).getName() == "dot_name" : "Not an invoking expression";
                    break;
                case "nonTypeName":
                    // nonTypeName
                    AbstractObjectOfLanguage lookup = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false);

                    finalValue = lookup;
                    localScope = lookup;
                    break;
                case "dotPrefix":
                    // dotPrefix nonTypeName
                    // continuing because the while loop will reach nonTypeName
                    assert getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))).getName() == "nonTypeName";
                    // System.out.println("dot prefix");
                    childNode = getGNodeUnderConditional((GNode) itr.next());
                    assert childNode.getName() == "nonTypeName";
                    AbstractObjectOfLanguage lookupNonTypeName = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false);

                    return lookupNonTypeName;
                case "typeName":
                    // typeName dot_name
                    // doing namespacing
                    AbstractObjectOfLanguage typeNameLO = symtabLookup(localScope, getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0))));
                    assert typeNameLO.getConstructType() != LObjectKind.TYPEPARAMETER;

                    localScope = typeNameLO;
                    finalValue = typeNameLO;
                    break;
                case "dot_name":
                    String dotNameString = getStringUnderDotName(childNode);
                    AbstractObjectOfLanguage nameObj = symtabLookup(localScope, dotNameString);

                    finalValue = nameObj;
                    localScope = finalValue;
                    break;
                case "invokingExpression":
                    Object invokingExpressionResult = visitor.dispatch(childNode);
                    if(invokingExpressionResult instanceof AbstractObjectOfLanguage) {
                        finalValue = localScope = (AbstractObjectOfLanguage) invokingExpressionResult;
                    }
                    break;
                default:
                    assert false : childNode.getName() + "::Encountered a situation where expression inside invoking expression was not of expected value";
            }
        }
        assert finalValue != null;
        assert finalValue.getConstructType() != LObjectKind.TYPEPARAMETER;
        return finalValue;
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
    // TODO: update to be similar as expression
    public AbstractObjectOfLanguage getCalleeFromNonBraceExpression(GNode n) {
        Iterator itr = n.iterator();
        AbstractObjectOfLanguage finalValue = null;
        AbstractObjectOfLanguage localScope = scope.peek();
        while(itr.hasNext()) {
            Node next = (Node) itr.next();
            if(next instanceof Syntax) {
                assert next.toString() == "!" : "Encountered an invalid expression when expecting something to be invoked";
                if(next.toString() != "!") {
                    System.out.println("Encountered an invalid expression when expecting something to be invoked");
                    System.exit(1);
                }
                continue;
            }

            Object underConditional = getValueUnderConditional((GNode) next);

            if(underConditional instanceof Syntax) {
                assert ((Node) underConditional).toString() == "!" : "Encountered an invalid expression when expecting something to be invoked";
                if(((Node) underConditional).toString() != "!") {
                    System.out.println("Encountered an invalid expression when expecting something to be invoked");
                    System.exit(1);
                }
                continue;
            }

            GNode childNode = (GNode) underConditional;
            switch(childNode.getName()) {
                case "nonBraceExpression":
                    finalValue = getCalleeFromNonBraceExpression(childNode);
                    localScope = finalValue;
                    assert getGNodeUnderConditional(n.getGeneric(1)).getName() == "dot_name" : "Not an invoking expression";
                    break;
                case "nonTypeName":
                    // nonTypeName
                    AbstractObjectOfLanguage lookup = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false);
                    // System.out.println("found nonTypeName: " + lookup.getName());
                    finalValue = lookup;
                    localScope = lookup;
                    // return lookup;
                    break;
                case "dotPrefix":
                    // dotPrefix nonTypeName
                    // continuing because the while loop will reach nonTypeName
                    assert getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(1))).getName() == "nonTypeName";
                    // System.out.println("dot prefix");
                    childNode = getGNodeUnderConditional((GNode) itr.next());
                    assert childNode.getName() == "nonTypeName";
                    AbstractObjectOfLanguage lookupNonTypeName = nonTypeNameSymtabLookUp(localScope, getStringUnderNonTypeName(getGNodeUnderConditional(childNode)), false);
                    return lookupNonTypeName;
                case "typeName":
                    // typeName dot_name
                    // doing namespacing
                    AbstractObjectOfLanguage typeNameLO = symtabLookup(localScope, getNameFromTypeName(getGNodeUnderConditional(getGNodeUnderConditional(n.getGeneric(0)))));
                    localScope = typeNameLO;
                    finalValue = typeNameLO;
                    break;
                case "dot_name":
                    String dotNameString = getStringUnderDotName(childNode);
                    finalValue = symtabLookup(localScope, dotNameString);
                    localScope = finalValue;
                    break;
                default:
                    assert false : childNode.getName() + "::Encountered a situation where expression inside invoking expression was not of expected value";
            }
        }
        assert finalValue != null;
        return finalValue;
    }

    public GNode getGNodeUnderConditional(GNode n) {
        Object receivedValue = getValueUnderConditional(n);
        assert receivedValue instanceof GNode : "Got " + receivedValue.toString();

        return (GNode) receivedValue;
    }

    public Object getValueUnderConditional(Object givenNode) {
        if(givenNode instanceof Syntax) {
            return givenNode;
        }

        GNode n = (GNode) givenNode;

        if(n.getName() == "Conditional") {
            // since first child is the presence condition
            return n.get(1);
        } else {
            return n;
        }
    }

    public String getStringUnderNamedType(GNode n) {
        assert n.getName() == "namedType";

        if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "typeName") { // typeName
            return getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));
        } else { //specializedType
            return getStringUnderSpecializedTypeName(getGNodeUnderConditional(n.getGeneric(0)));
        }
    }

    public String getStringUnderSpecializedTypeName(GNode n) {
        assert n.getName() == "specializedType";

        // TODO: take care of typeArgumentList

        return getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));
    }

    public String getNameFromTypeName(GNode n) {
        assert n.getName() == "typeName";

        // only child is prefixedType and that is used only under typeName
        n = getGNodeUnderConditional(n.getGeneric(0));

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
        return getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
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
            return getStringUnderNonTypeName(getGNodeUnderConditional(n.getGeneric(0)));
        }
    }

    public String getStringUnderNonTypeName(GNode n) {
        assert n.getName() == "nonTypeName";
        // System.out.println(n.toString());
        // System.out.println(n.get(0));
        // System.out.println(((Language) n.get(0)).tag());
        // only terminals under nonTypeName, but right now only handling IDENTIFIER tokens, not reserved keywords
        // assert (P4Tag.IDENTIFIER == ((Language) n.get(0)).tag() || n.get(0).toString() == "apply") : "non-IDENTIFIER terminals not supported under nonTypeName atm";
        return n.get(0).toString();
    }

    public String getStringUnderPrefixedNonTypeName(GNode n) {
        assert n.getName() == "prefixedNonTypeName";
        assert ! ((GNode) getGNodeUnderConditional(n.getGeneric(0))).getName().equals("dotPrefix") : "Retrieving nontypenames with a dot as a prefix not supported yet";

        return getStringUnderNonTypeName(getGNodeUnderConditional(n.getGeneric(0)));
    }

    /**
     * Assert that only syntactically legal values are present for method call statements.
     * Returns the string present.
     * @param n Parent GNode containing the lvalue construct
     * @return
     */
    public String getStringUnderLvaluePrefixNonTypeName(GNode n, Visitor visitor) {
        // only legal value of lvalue for method call statements is prefixedNonTypeName
        // as dot_name and lvalueExpressions cannot be used for method call statements
        // (see end of document)

        assert n.getName() == "lvalue";
        assert n.get(0) instanceof Node && ((Node) n.get(0)).isGeneric();

        GNode firstChild = getGNodeUnderConditional(n.getGeneric(0));
        if(firstChild.getName() == "lvalue") {
            return traverseLvalueAndGetStringUnderPrefixedNonTypeName(n, visitor);
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
    public String traverseLvalueAndGetStringUnderPrefixedNonTypeName(GNode n, Visitor visitor) {
        int size = n.size();
        String final_val = "";
        for(int i = 0; i < size; i++) {
            if(getValueUnderConditional(n.get(i)) instanceof Syntax) {
                assert getValueUnderConditional(n.get(i)).toString() == "this";
                return "this";
            }
            if(n.getGeneric(i).getName() == "lvalue") {
                final_val = traverseLvalueAndGetStringUnderPrefixedNonTypeName(n.getGeneric(i), visitor);
            } else if(n.getGeneric(i).getName() == "prefixedNonTypeName") {
                return getStringUnderPrefixedNonTypeName(n.getGeneric(i));
            } else if(n.getGeneric(i).getName() == "dot_name") {
                assert n.getGeneric(i).getGeneric(1).getName() == "name";
                assert n.getGeneric(i).getGeneric(1).get(0) instanceof Syntax == false : "dot_name under a lvalue construct used in a method call statement cannot invoke a type identifier";
            } else if(n.getGeneric(i).getName() == "lvalueExpression") {
                visitor.dispatch(getGNodeUnderConditional(n.getGeneric(1)));
                if(n.size() > 3) {
                    visitor.dispatch(getGNodeUnderConditional(n.getGeneric(3)));
                }
                // assert false : "lvalueExpression cannot be used in an method calling statement";
            }
        }

        assert !final_val.isBlank() : "Unable to retrieve string under a nested lvalue structure";

        return final_val;
    }

    public AbstractObjectOfLanguage getParentInstance(AbstractObjectOfLanguage localScope) {
        // System.out.println("Trying to find parent of: " + localScope.getName() + " with now constructor as: " + localScope.getConstructType());
        if(localScope.getConstructType() == LObjectKind.SUBCLASS) {
            assert ((SubClass) localScope).getOriginalClass().getConstructType() == LObjectKind.EXTERNDECLARATION;
            return ((SubClass) localScope).getOriginalClass();
        } else {
            assert localScope.getConstructType() != LObjectKind.BASETYPE &&
                   localScope.getConstructType() != LObjectKind.ANONYMOUS &&
                   localScope.getConstructType() != LObjectKind.CONSTANTVALUE;
            if(localScope.getConstructType() == LObjectKind.EXTERNDECLARATION) {
                return localScope;
            }
            return getParentInstance(localScope.getNameSpace());
        }
    }

    public ArrayList<AbstractObjectOfLanguage> parseparsedOptTypeParameters(GNode n, Visitor visitor) {
        ArrayList<AbstractObjectOfLanguage> parsedOptTypeParameters = new ArrayList<>();
        assert n.getName() == "realTypeArgumentList";

        Iterator itr = n.iterator();
        while(itr.hasNext()) {
            Object nextVal = getValueUnderConditional(itr.next());
            if(nextVal instanceof Syntax) {
                // COMMA
                continue;
            }

            GNode nextChild = (GNode) nextVal;
            parsedOptTypeParameters.add((AbstractObjectOfLanguage) visitor.dispatch(nextChild));
        }

        return parsedOptTypeParameters;
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
            assert n.get(0).toString() == "this";
            return getParentInstance(localScope);
        }

        Iterator nit = n.iterator();
        AbstractObjectOfLanguage finalValue = null;
        GNode childNode = getGNodeUnderConditional(n.getGeneric(0));

        for(int i = 1; i < n.size() + 1; i++) {
            // System.out.println("child name: " + childNode.getName());
            switch(childNode.getName()) {
                case "prefixedNonTypeName":
                    // has to be "Identifiers of a base or derived type." (https://p4.org/p4-spec/docs/P4-16-working-spec.html#sec-lvalues)
                    String name = getStringUnderPrefixedNonTypeName(childNode);
                    return symtabLookup(localScope, name);
                case "lvalue":
                    AbstractObjectOfLanguage leftSideValue = parseLValue(localScope, childNode, visitor); // has to devolve into prefixedNonTypeName
                    assert leftSideValue != null : "Undefined value used";
                    localScope = leftSideValue;
                    finalValue = leftSideValue;
                    break;
                case "dot_name":
                    String dotValueObjName = getStringUnderName(childNode.getGeneric(1));
                    // System.out.println("dot value looking up name: " + dotValueObjName + " under scope: " + localScope.getName());
                    AbstractObjectOfLanguage dotValueObject = symtabLookup(localScope, dotValueObjName);
                    finalValue = dotValueObject;
                    localScope = dotValueObject;
                    // System.out.println("new dot name scope: " + dotValueObject.getName());
                    // switch(localScope.getConstructType()) {
                    //     case STRUCTTYPEDECLARATION:
                    //     case HEADERTYPEDECLARATION:
                    //     case HEADERUNIONDECLARATION:
                    //         break;
                    //     default:
                    //         // System.err.println("Type error, referring to undefined value: " + childNode.getName());
                    //         assert false : "Type error for dot values, referring to construct: " + scope.peek().getConstructType();
                    //         System.exit(1);
                    // }
                    break;
                case "lvalueExpression":
                    // scope.add(localScope);
                    visitor.dispatch(childNode.getGeneric(1));
                    if(childNode.size() > 3) {
                        visitor.dispatch(childNode.getGeneric(3));
                    }
                    // scope.pop();
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

    /**
     * Takes in parameterList node and return true if any of them have a generic type
     * @param n
     * @return
     */
    public boolean isAnyParameterGeneric(GNode n, GNode optTypeParameters) {
        assert n.getName() == "parameterList";
        assert optTypeParameters.getName() == "optTypeParameters";

        if(n.size() == 0) {
            return false;
        }

        Iterator itr;

        ArrayList<String> typeParams = new ArrayList<>();
        if(optTypeParameters.size() != 0) {
            // typeParameterList iterator
            itr = getGNodeUnderConditional(getGNodeUnderConditional(optTypeParameters.getGeneric(0)).getGeneric(1)).iterator();
                while(itr.hasNext()) {
                Object next = itr.next();
                if(next instanceof Syntax || getValueUnderConditional(next) instanceof Syntax) {
                    // COMMA
                    continue;
                }
                GNode name = getGNodeUnderConditional((GNode) next);
                assert name.getName() == "name";
                typeParams.add(getStringUnderName(name));
            }
        }


        GNode nonEmptyParameterList = getGNodeUnderConditional(n.getGeneric(0));
        itr = nonEmptyParameterList.iterator();
        while(itr.hasNext()) {
            Object next = itr.next();
            if(next instanceof Syntax || getValueUnderConditional(next) instanceof Syntax) {
                // COMMA
                continue;
            }
            GNode parameter = getGNodeUnderConditional((GNode) next);
            GNode typeRef = getGNodeUnderConditional(getGNodeUnderConditional(parameter.getGeneric(2)).getGeneric(0));
            AbstractObjectOfLanguage typeObj;
            String typeName;
            switch(typeRef.getName()) {
                case "typeName":
                    typeName = getNameFromTypeName(typeRef);
                    typeObj = symtabLookupIfExists(scope.peek(), typeName, true, true);
                    // Since type names point directly to the type and not a instance of that type -
                    // Update: generic-struct.p4i - the type can be a typedef
                    // assert !typeObject.hasAssociatedType() : typeObject.getName() + "of constructor: " + typeObject.getConstructType() + " with type: " + typeObject.getType().getName() + " of constructor: " + typeObject.getType().getConstructType();
                    break;
                case "baseType":
                    typeName = getBaseTypeAsString(typeRef);
                    typeObj = baseTypesCollection.getLanguageObjectOfBaseType(typeName);
                    break;
                case "specializedType":
                    typeName = getStringUnderSpecializedTypeName(typeRef);
                    typeObj = symtabLookupIfExists(scope.peek(), typeName, true, true);
                    break;
                case "headerStackType":
                    typeName = getStringUnderHeaderStackType(typeRef);
                    typeObj = symtabLookupIfExists(scope.peek(), typeName, true, true);
                    break;
                case "tupleType":
                    typeObj = default_language_object;
                    typeName = "";
                    break;
                default:
                    System.err.println("Unhandled new case for typeRef: " + typeRef.getName());
                    System.exit(1);
                    typeObj = default_language_object;
                    typeName = "";
            }

            if(typeObj.isGeneratorClass() || typeObj.getConstructType() == LObjectKind.TYPEPARAMETER ||
              (typeObj.hasAssociatedType() && typeObj.getType().isGeneratorClass())) {
                return true;
            } else if(typeObj == undeclared_object && typeParams.contains(typeName)) {
                return true;
            }

        }

        return false;
    }

    public String getTypeStringUnderTypeRef(GNode n) {
        assert n.getName() == "typeRef";
        
        switch(getGNodeUnderConditional(n.getGeneric(0)).getName()) {
            case "typeName":
                return getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));
            case "baseType":
                return getBaseTypeAsString(getGNodeUnderConditional(n.getGeneric(0)));
            case "specializedType":
                return LObjectKind.SPECIALIZEDTYPE.toString();
            case "headerStackType":
                return LObjectKind.HEADERSTACKTYPE.toString();
            case "tupleType":
                return LObjectKind.TUPLETYPE.toString();
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
        if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "typeName") {
            return getNameFromTypeName(getGNodeUnderConditional(n.getGeneric(0)));
        } else if(getGNodeUnderConditional(n.getGeneric(0)).getName() == "specializedType") {
            return getStringUnderSpecializedTypeName(getGNodeUnderConditional(n.getGeneric(0)));
        } else {
            System.err.println("Unhandled header stack type case");
            System.exit(1);
        }

        return "Unhandled case under header stack type";
    }

    public String getStringUnderDotName(GNode n) {
        return getStringUnderName(getGNodeUnderConditional(n.getGeneric(1)));
    }

    public String getStringUnderFunctionPrototype(GNode n) {
        assert n.getName() == "functionPrototype";
        
        return getStringUnderName(getGNodeUnderConditional(n.getGeneric(1)));
    }

    public String getStringUnderParserTypeDeclaration(GNode n) {
        assert n.getName() == "parserTypeDeclaration";

        return getStringUnderName(getGNodeUnderConditional(n.getGeneric(2)));
    }

    public String getStringUnderActionRef(GNode n) {
        assert n.getName() == "actionRef";

        String prefixedNonTypeName = getStringUnderPrefixedNonTypeName(getGNodeUnderConditional(n.getGeneric(0)));

        // TODO: parse argumentList?

        return prefixedNonTypeName;
    }

    public void printCallGraph() {
        ArrayList<AbstractObjectOfLanguage> sortedSymtabKeys = new ArrayList<>(symtab.keySet());
        Collections.sort(sortedSymtabKeys);
        for(AbstractObjectOfLanguage key : sortedSymtabKeys) {
            System.out.println(key.toStringExtensive(symtab, callGraphObject, global_scope));
        }
        // System.out.println(callGraphObject);
    }

    public String toDot() {
        String dotFormat = "";
        for(AbstractObjectOfLanguage key : symtab.keySet()) {
            dotFormat += key.toDotString(symtab, callGraphObject, global_scope);
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