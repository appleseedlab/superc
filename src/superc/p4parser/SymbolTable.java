package superc.p4parser;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

import superc.p4parser.TemporaryParameterValues;
import superc.p4parser.P4LanguageObject.AbstractObjectOfLanguage;
import superc.p4parser.P4LanguageObject.Generator;
import superc.p4parser.P4LanguageObject.LObjectKind;
import superc.p4parser.P4LanguageObject.LanguageObject;
import superc.p4parser.P4LanguageObject.ReservedKeywords;
import superc.p4parser.P4LanguageObject.TypeParameter;
import xtc.tree.Visitor;

public class SymbolTable {
    Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab; 
    private static final P4LanguageObject p4LanguageObject = new P4LanguageObject();  

    public SymbolTable() {
        this.symtab = new HashMap<>();
    }

    public Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> getSymTab() {
        return this.symtab;
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
            if(newLangObj.getConstructType() == LObjectKind.FUNCTIONPROTOTYPEPLACEHOLDER) {
                assert symtab.get(scope).get(name).getConstructType() == LObjectKind.FUNCTIONPROTOTYPEPLACEHOLDER;
            } else if((scope.getConstructType() == LObjectKind.EXTERNDECLARATION || scope.getConstructType() == LObjectKind.EXTERNDECLARATIONGENERATOR)) {
                // Since constructors are added like variables and not functions)
            } else {
                // TODO: Tuples are exceptions
                if(!Symbols.getOverridableConstructs().contains(newLangObj.getConstructType())) {
                    // header default values exception
                    if(scope.getConstructType() == LObjectKind.HEADERSTACKTYPE ||
                       scope.getConstructType() == LObjectKind.HEADERTYPEDECLARATION ||
                       scope.getConstructType() == LObjectKind.HEADERTYPEDECLARATIONGENERATOR ||
                       scope.getConstructType() == LObjectKind.HEADERUNIONDECLARATION ||
                       scope.getConstructType() == LObjectKind.HEADERUNIONDECLARATIONGENERATOR) {
                           if(Symbols.getDefaultHeaderFunctions().contains(name)) {
                               System.err.println("Adding a variable of same name as a default header function, so not adding it and ignoring it: " + name);
                           }
                    } else if(newLangObj.getConstructType() == LObjectKind.VARIABLE) {
                        // assert symtab.get(scope).get(name).getConstructType() == LObjectKind.VARIABLE;
                        System.err.println("Adding a new variable (" + newLangObj.getName() + ") that will overshadow another value (" + symtab.get(scope).get(name).getConstructType() + ")."); // technically not adding it to the symtab, just ignoring it. TODO: check if need to create a new object for data tracing purposes
                    } else if(newLangObj.getConstructType() != symtab.get(scope).get(name).getConstructType()) {
                        System.err.println("Redefining a value named: " + name + ". The new value of construct: " + newLangObj.getConstructType() + " will overshadow old value of construct: " + symtab.get(scope).get(name).getConstructType());
                    } 
                    else {
                        assert false : "Error: " + name + " is already defined and of the same construct type " + newLangObj.getConstructType() + ". Redefining it.";
                        System.err.println("Error: " + name + " is already defined and of the same construct type " + newLangObj.getConstructType() + ". Redefining it.");
                        System.exit(1);
                    }
                } else {
                    System.err.println("Unhandled case where two functions with the same number of parameters are defined. Still need to handle overloading methods when number of parameters are same but parameters names are different: " + name);
                }
                // System.exit(1);
            }
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

    public AbstractObjectOfLanguage nonTypeNameSymtabLookUp(AbstractObjectOfLanguage localScope, String name, boolean canBeNewIdentifier, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor, Stack<AbstractObjectOfLanguage> scope) {
        return nonTypeNameSymtabLookUp(localScope, name, canBeNewIdentifier, true, true, temporaryValues, definitionsVisitor, scope);
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
    public AbstractObjectOfLanguage nonTypeNameSymtabLookUp(AbstractObjectOfLanguage localScope, String name, boolean canBeNewIdentifier, boolean getAssociatedType, boolean generateInstance, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor, Stack<AbstractObjectOfLanguage> scope) {
        AbstractObjectOfLanguage lookupValue = symtabLookupIfExists(localScope, name, getAssociatedType, generateInstance, temporaryValues, definitionsVisitor, scope);
        if(lookupValue == Symbols.getUndeclaredObject()) {
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

    public AbstractObjectOfLanguage symtabLookup(AbstractObjectOfLanguage localScope, String typeName, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor, Stack<AbstractObjectOfLanguage> scope) {
        return symtabLookup(localScope, typeName, true, true, temporaryValues, definitionsVisitor, scope);
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
    public AbstractObjectOfLanguage symtabLookup(AbstractObjectOfLanguage localScope, String typeName, boolean getAssociatedType, boolean generateInstance, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor, Stack<AbstractObjectOfLanguage> scope) {
        // System.out.println("looking up: " + typeName + " under: " + localScope.getName() + " of type: " + localScope.getConstructType());
        // if(localScope.getConstructType() == LObjectKind.SPECIALIZEDTYPE) {
        //     System.out.println("specizlied type: " + localScope.getName() + " type arg list: " + ((SpecializedType)localScope).getTypeArgumentList());
        // }
        AbstractObjectOfLanguage lookupValue =  symtabLookupIfExists(localScope, typeName, getAssociatedType, generateInstance, temporaryValues, definitionsVisitor, scope);
        if(lookupValue == Symbols.getUndeclaredObject()) {
            // System.err.println("Calling to an undefined symbol \"" + typeName + "\"";);
            // System.exit(1);
            assert false : "Calling to an undefined symbol \"" + typeName + "\"";
        }

        return lookupValue;
    }

    public AbstractObjectOfLanguage retrieveSymbolOrTypeVariable(Stack<AbstractObjectOfLanguage> scope, AbstractObjectOfLanguage localScope, String typeName, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor) {
        return retrieveSymbolOrTypeVariable(scope, localScope, typeName, false, temporaryValues, definitionsVisitor);
    }

    /**
     * Similar to symtab lookup, but treats the value as a type variable 
     * if it is not found in the symbol table
     * @param localScope
     * @param typeName
     * @param getAssociatedType if set to true, will return the associated type of object, if it has
     * @return
     */
    public AbstractObjectOfLanguage retrieveSymbolOrTypeVariable(Stack<AbstractObjectOfLanguage> scope, AbstractObjectOfLanguage localScope, String typeName, boolean createTypeVar, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor) {
        AbstractObjectOfLanguage lookupValue = symtabLookupIfExists(localScope, typeName, true, true, temporaryValues, definitionsVisitor, scope);
        if (lookupValue == Symbols.getUndeclaredObject()) {
            TypeParameter typeParameterObj = p4LanguageObject.new TypeParameter(typeName, localScope);
            // System.out.println("Creating new type variable: " + typeParameterObj.getName());
            // NOTE: initially was not adding to symbol table
            addToSymtab(scope.peek(), typeName, typeParameterObj);
            return typeParameterObj;
        } else {
            if(createTypeVar && lookupValue.getConstructType() != LObjectKind.TYPEPARAMETER) {
                System.err.println("Currently parsing type variable identifier " + typeName + " will be shadowing " + typeName + " of construct tye: " + lookupValue.getConstructType());

                TypeParameter typeParameterObj = p4LanguageObject.new TypeParameter(typeName, localScope);
                // System.out.println("Creating new type variable: " + typeParameterObj.getName());
                // NOTE: initially was not adding to symbol table
                addToSymtab(scope.peek(), typeName, typeParameterObj);
                return typeParameterObj;
            }
            return lookupValue;
        }
    }

    /**
     * Checks if scope and symbol exists, returns the corresponding object from symtab if it does.
     * Recursively goes through the parent scopes if not found under current scope.
     * Treats value as a type variable if symbol is not found and canBeTypeVariable is set to true.
     * If canBeTypeVariable is set to false and symbol is not found, an error is thrown.
     * If the retrieved value is of generator class and the temporary variables are not empty,
     * a new instance of that value will be generated
     * @param localScope The scope to check under. Changes as we recursively go through scopes
     * @param typeName
     * @param primaryScope The initial scope that the symbol was supposed to be checked under. Keep track of initial one for type variable declarations.
     * @param canBeTypeVariable A boolean variable indicating whether the symbol can possibly be a new type variable
     * @return
     */
    public AbstractObjectOfLanguage symtabLookupIfExists(AbstractObjectOfLanguage localScope, String typeName, boolean getAssociatedType, boolean generateInstance, Stack<TemporaryParameterValues> temporaryValues, Visitor definitionsVisitor, Stack<AbstractObjectOfLanguage> scope) {
        assert !typeName.isBlank() : "typeName is not supposed to be empty when looking it up on symbol table";

        boolean doesExistInCurrentScope = doesSymbolExist(localScope, typeName);

        // if the symbol does not exist in the current scope, check under its parent scope
        if( !doesExistInCurrentScope) {
            if(localScope.equals(Symbols.getGlobalScope())) {
                return Symbols.getUndeclaredObject();
            }

            return symtabLookupIfExists(localScope.getNameSpace(), typeName, getAssociatedType, generateInstance, temporaryValues, definitionsVisitor, scope);
        } else {
            AbstractObjectOfLanguage symtabValue = symtab.get(localScope).get(typeName);
            if(symtabValue.getConstructType() == LObjectKind.FUNCTIONPROTOTYPEPLACEHOLDER) {
                assert !temporaryValues.isEmpty() : temporaryValues.size();
                typeName += "_" + temporaryValues.peek().getParameters().size();
                assert doesSymbolExist(localScope, typeName) : typeName;
                symtabValue = symtab.get(localScope).get(typeName);
                assert symtabValue.getConstructType() != LObjectKind.FUNCTIONPROTOTYPEPLACEHOLDER;
            }
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

    public void print() {
        System.out.println(symtab);
    }
}
