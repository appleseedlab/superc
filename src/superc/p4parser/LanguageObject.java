package superc.p4parser;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

import xtc.parser.Transformer.Typer;

// For symbols
class LanguageObject {
    public final String name;
    public final LanguageObject nameSpace;
    public static final LanguageObject global_scope = new LanguageObject("GLOBAL", null);
    public static final LanguageObject undefined_scope = new LanguageObject("UNDEFINED", null);
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

    // public boolean isBaseType() {
    //     return (isType() && baseTypes.contains(this.type));
    // }

    public Object getType() {
        return type;
    }

    /**
        * A toString function to use when in-depth detail about current object is needed.
        * Outputs the callees present under the current object if it is not present under the global scope.
        * @return
        */
    public String toStringExtensive(Map<LanguageObject, Map<String, LanguageObject>> symtab, HashMap<LanguageObject, HashSet<LanguageObject>> callGraphObject) {
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

    public String toDotString(Map<LanguageObject, Map<String, LanguageObject>> symtab, HashMap<LanguageObject, HashSet<LanguageObject>> callGraphObject) {
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

    abstract class ObjectOfLanguage {
        private final String name;
        private final ObjectOfLanguage nameSpace;
        abstract boolean isScoped();
        // not making this private to avoid allocating memory since it is not present most times
        private ArrayList<ObjectOfLanguage> listOfOptConstructorParameters = null;

        boolean isVariable() {
            return false;
        }

        boolean isFunction() {
            return false;
        }

        boolean isStruct() {
            return false;
        }

        boolean isHeader() {
            return false;
        }

        boolean isControlBlock() {
            return false;
        }

        boolean isExternDeclaration() {
            return false;
        }

        boolean isExternFunctionDeclaration() {
            return false;
        }

        boolean isMethodPrototype() {
            return false;
        }

        boolean isFunctionPrototype() {
            return false;
        }

        boolean hasAssociatedType() {
            return false;
        }

        boolean isParameter() {
            return false;
        }

        boolean isExpression() {
            return false;
        }

        boolean isSpecializedType() {
            return false;
        }

        boolean isHeaderStackType() {
            return false;
        }

        boolean isTupleType() {
            return false;
        }

        boolean isPrefixedType() {
            return false;
        }

        boolean isTypeName() {
            return false;
        }

        boolean isTypeRef() {
            return false;
        }

        boolean isConstructorMethodPrototype() {
            return false;
        }

        boolean isTypeArgument() {
            return false;
        }

        boolean isNamedType() {
            return false;
        }

        boolean isInvokingExpression() {
            return false;
        }

        boolean isName() {
            return false;
        }

        boolean isArgument() {
            return false;
        }

        boolean isRealTypeArgument() {
            return false;
        }

        // For GLOBAL and UNDEFINED variables
        boolean isConstantValue() {
            return false;
        }

        public String getName() {
            return this.name;
        }

        public boolean hasOptConstructorParameters() {
            return (listOfOptConstructorParameters != null);
        }

        public ObjectOfLanguage getNameSpace() {
            return this.nameSpace;
        }

        public String getNameSpaceString(ObjectOfLanguage global_scope) {
            if(this == global_scope) {
                return name;
            }
            
            return this.nameSpace.name;
        }

        public ArrayList<ObjectOfLanguage> getListOfOptConstructorParameters() {
            return this.listOfOptConstructorParameters;
        }

        public void addToOptConstructorParametersList(ObjectOfLanguage parameter) {
            if(listOfOptConstructorParameters == null) {
                this.listOfOptConstructorParameters = new ArrayList<>();
            }

            this.listOfOptConstructorParameters.add(parameter);
        }

        public ObjectOfLanguage(String name, ObjectOfLanguage nameSpace) {
            this.name = name;
            this.nameSpace = nameSpace;
            this.listOfOptConstructorParameters = new ArrayList<>();
        }

        public String toString(ObjectOfLanguage global_scope) {
            // For simple toString calls where the current value is not present under the symbol table
            if(this == global_scope) {
                return name;
            }
            
            return name + "(" + this.getNameSpaceString(global_scope) + ")";
        }

        /**
            * A toString function to use when in-depth detail about current object is needed.
            * Outputs the callees present under the current object if it is not present under the global scope.
            * @return
            */
        public String toStringExtensive(Map<ObjectOfLanguage, Map<String, ObjectOfLanguage>> symtab, HashMap<ObjectOfLanguage, HashSet<ObjectOfLanguage>> callGraphObject) {
            String finalString = name + ": ";

            Iterator<String> itr = symtab.get(this).keySet().iterator();

            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                ObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += childLangObj.toString();
                if(symtab.containsKey(childLangObj)) {
                    finalString += itr.hasNext() ? ", " : "";
                    continue;
                }

                ArrayList<String> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(ObjectOfLanguage callee : callGraphObject.get(childLangObj)) {
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

        public String toDotString(Map<ObjectOfLanguage, Map<String, ObjectOfLanguage>> symtab, HashMap<ObjectOfLanguage, HashSet<ObjectOfLanguage>> callGraphObject) {
            String finalString = "";

            Iterator<String> itr = symtab.get(this).keySet().iterator();
            finalString += this.hashCode() + ";";
            finalString += this.hashCode() + " [label=\"" + this.name + "\"];";
            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                ObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += this.hashCode() + " -> " + childLangObj.hashCode() + " [style=dashed, color=blue];";
                finalString += childLangObj.hashCode() + " [label=\"" + childLangObj.name + "\"];";

                if(symtab.containsKey(childLangObj)) {
                    continue;
                }

                ArrayList<ObjectOfLanguage> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(ObjectOfLanguage callee : callGraphObject.get(childLangObj)) {
                        calleeNames.add(callee);
                    }
                }

                if(! calleeNames.isEmpty()) {
                    for(ObjectOfLanguage localCallee : calleeNames) {
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
        public boolean equals(Object object, ObjectOfLanguage global_scope) {
            if(this == object) {
                return true;    
            }
            if(object == null) {
                return false;
            }
            if (object instanceof ObjectOfLanguage == false) {
                return false;
            }

            ObjectOfLanguage compObject = (ObjectOfLanguage) object;

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

        /**
         * Generates a unique hash code based on the scoping ancestry
         * (If two blocks are under the same scope then they are the same piece of code)
         * @param global_scope
         * @return
         */
        public int hashCode(ObjectOfLanguage global_scope) {
            String hashString = "";
            if(this.nameSpace != null) {
                // not the GLOBAL ObjectOfLanguage
                hashString += this.getParentNameSpaces(global_scope) + "/";
            }
            hashString += this.name;
            
            return hashString.hashCode();
        }

        /**
         * Returns a string with current scope name and the ancestry scope name.
         * @param global_scope
         * @return
         */
        public String getParentNameSpaces(ObjectOfLanguage global_scope) {
            String ancestorNameSpace = "";
            ObjectOfLanguage currentNameSpace = this.nameSpace;
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

        // END generic functions

    }

    /**
     * Class used to declare global constant language objects like global scope.
     */
    class ConstantTreeGlobalObjects extends ObjectOfLanguage {
        @Override
        boolean isConstantValue() {
            return true;
        }

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        public ObjectOfLanguage getNameSpace() {
            System.err.println("ConstantTreeGlobalObjects do not have a namespace since they are global level");
            System.exit(1);

            return null;
        }

        public ConstantTreeGlobalObjects(String name) {
            super(name, null);
        }
    }

    class ControlDeclaration extends ObjectOfLanguage {
        @Override 
        boolean isControlBlock() {
            return true;
        }

        @Override
        boolean isScoped() {
            return true;
        }

        public ControlDeclaration(String name, ObjectOfLanguage scope) {
            super(name, scope);
        }
    }

    /**
     * This class is specifically for the production:
     * optAnnotations EXTERN nonTypeName optTypeParameters L_BRACE methodPrototypes R_BRACE
     * 
     * Note:
     * optAnnotations EXTERN name SEMICOLON -- not valid anymore in new language spec
     * 
     * externFunctionDeclaration is under another class
     */
    class ExternDeclaration extends ObjectOfLanguage {
        // method prototypes can occur only inside the first production of extern declaration
        private final ArrayList<MethodPrototype> methodPrototypes;

        @Override
        boolean isExternDeclaration() {
            return true;
        }

        @Override
        boolean isScoped() {
            return true;
        }

        public ExternDeclaration(String name, ObjectOfLanguage scope) {
            super(name, scope);
            methodPrototypes = new ArrayList<>();
        }

        public ArrayList<MethodPrototype> getMethodPrototypes() {
            return this.methodPrototypes;
        }

        public void addMethodPrototype(MethodPrototype newMethodPrototype) {
            this.methodPrototypes.add(newMethodPrototype);
        }
    }

    class ExternFunctionDeclaration extends ObjectOfLanguage {
        private final FunctionPrototype functionPrototype;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isExternDeclaration() {
            return true;
        }

        public FunctionPrototype getFunctionDeclaration() {
            return this.functionPrototype;
        }

        public ExternFunctionDeclaration(String name, ObjectOfLanguage nameSpace, FunctionPrototype functionPrototype) {
            super(name, nameSpace);
            this.functionPrototype = functionPrototype;
        }
    }

    class FunctionPrototype extends ObjectOfLanguage {
        private final ObjectOfLanguage returnType;
        private final ArrayList<Parameter> parameterList;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isFunctionPrototype() {
            return true;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public ArrayList<Parameter> getParameters() {
            return this.parameterList;
        }

        public ObjectOfLanguage getReturnType() {
            return this.returnType;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type object
        // and will pass it to us
        public FunctionPrototype(String name, ObjectOfLanguage nameSpace, ObjectOfLanguage returnType) {
            super(name, nameSpace);
            this.returnType = returnType;
            parameterList = new ArrayList<>();
        }
    }

    class Parameter extends ObjectOfLanguage {
        private final TypeRef type;
        // private final Expression assignedExpression;
        private final boolean hasAssignedExpression;
        private final ConstantTreeGlobalObjects direction;

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isParameter() {
            return true;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        boolean hasAssignedExpression() {
            return hasAssignedExpression;
        }

        // public void setAssignedExpression(Expression expression) {
        //     assignedExpression = expression;
        // }

        // public Expression getAssignedExpression() {
        //     return this.assignedExpression;
        // }

        public TypeRef getType() {
            return this.type;
        }

        public ConstantTreeGlobalObjects getDirection() {
            return this.direction;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type and direction object
        // and will pass it to us
        public Parameter(String name, ObjectOfLanguage nameSpace, TypeRef type, ConstantTreeGlobalObjects direction) {
            super(name, nameSpace);
            this.type = type;
            hasAssignedExpression = false;
            this.direction = direction;
        }

        // public Parameter(String name, ObjectOfLanguage nameSpace, TypeRef type, ConstantTreeGlobalObjects direction, Expression assignedExpression) {
        //     super(name, nameSpace);
        //     this.type = type;
        //     // this.assignedExpression = assignedExpression;
        //     this.direction = direction;
        //     hasAssignedExpression = true;
        // }
    }

    class TypeRef extends ObjectOfLanguage {
        /*
        Possible typed:
        baseType - of class ConstantTreeObject
        typeName - ends up being some ObjectOfLanguage type
        specializedType - has typeName + typeArgumentlist
        headerStackType - can have:
                                typeName + expression
                                specializedType + expression
        tupleType - NO NAME, just the keyword "TUPLE" + typeArgumentlist
        */
        private final ObjectOfLanguage type;

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTypeRef() {
            return true;
        }

        ObjectOfLanguage getType() {
            return this.type;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type object
        // and will pass it to us
        public TypeRef(ObjectOfLanguage type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            this.type = type;
        }
    }

    class SpecializedType extends ObjectOfLanguage {
        private final TypeName type;
        private final ArrayList<TypeArgument> typeArgumentList;

        public TypeName getType() {
            return this.type;
        }

        public ArrayList<TypeArgument> getTypeArgumentList() {
            return this.typeArgumentList;
        }

        public void addTypeArgument(TypeArgument typeArgument) {
            this.typeArgumentList.add(typeArgument);
        }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isSpecializedType() {
            return true;
        }

        public SpecializedType(TypeName type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            this.type = type;
            typeArgumentList = new ArrayList<>();
        }
    }

    class HeaderStackType extends ObjectOfLanguage {
        private final TypeName type;
        private final SpecializedType specializedType;
        private final boolean hasTypeName;
        private final boolean hasSpecializedType;
        // private Expression expression;

        public ObjectOfLanguage getType() {
            // Since both TypeName and SpecializedType are "types" of this constructor
            if(type != null) {
                return this.type;
            } else {
                assert specializedType != null : "Unexpected error where both type and specialized type of header stack are null";
                return this.specializedType;
            }
        }

        public SpecializedType getSpecializedType() {
            return this.specializedType;
        }

        // public void setExpression(Expression expression) {
        //     this.expression = expression;
        // }

        // public Expression getExpression() {
        //     return this.expression;
        // }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isHeaderStackType() {
            return true;
        }

        @Override
        boolean isTypeRef() {
            return true;
        }

        public boolean hasTypeName() {
            return this.hasTypeName;
        }

        public boolean hasSpecializedType() {
            return this.hasSpecializedType;
        }

        public HeaderStackType(TypeName type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            this.type = type;
            this.specializedType = null;
            hasTypeName = true;
            hasSpecializedType = false;
        }

        public HeaderStackType(SpecializedType specializedType, ObjectOfLanguage nameSpace) {
            super(specializedType.getType().getName(), nameSpace);
            this.specializedType = specializedType;
            this.type = null;
            hasTypeName = false;
            hasSpecializedType = true;
        }
    }

    class TupleType extends ObjectOfLanguage {
        private final ArrayList<TypeArgument> typeArgumentList;

        public ArrayList<TypeArgument> getTypeArgumentList() {
            return this.typeArgumentList;
        }

        public void addTypeArgument(TypeArgument typeArgument) {
            this.typeArgumentList.add(typeArgument);
        }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTupleType() {
            return true;
        }

        // @Override
        // boolean isTypeRef() {
        //     return true;
        // }

        public TupleType(ObjectOfLanguage nameSpace) {
            super("TUPLE", nameSpace);
            this.typeArgumentList = new ArrayList<>();
        }
    }

    // Merged PrefixedType with TypeName as it is the only place where it is used
    class TypeName extends ObjectOfLanguage {
        private final ObjectOfLanguage type;
        private final boolean hasDotPrefix;

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTypeName() {
            return true;
        }

        @Override
        boolean isTypeRef() {
            return true;
        }

        public boolean hasDotPrefix() {
            return this.hasDotPrefix();
        }

        public ObjectOfLanguage getType() {
            return this.type;
        }

        // Right now assuming the invoker has retrieved the object referring to the type
        // and will pass it to us. Also that whether the prefixedType has a dot prefix or not
        public TypeName(ObjectOfLanguage typeObject, ObjectOfLanguage nameSpace, boolean hasDotPrefix) {
            super(typeObject.getName(), nameSpace);
            this.type = typeObject;
            this.hasDotPrefix = hasDotPrefix;
        }
    }

    class NamedType extends ObjectOfLanguage {
        private final ObjectOfLanguage type;

        public ObjectOfLanguage getType() {
            return this.type;
        }

        public Class getTypeClass() {
            return type.getClass();
        }

        public boolean isTypeName() {
            return this.type instanceof TypeName == true;
        }

        public boolean isSpecializedType() {
            return this.type instanceof SpecializedType == true;
        }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isNamedType() {
            return true;
        }

        @Override
        boolean isTypeRef() {
            return true;
        }

        public NamedType (ObjectOfLanguage type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            this.type = type;
        }
    }

    class MethodPrototype extends ObjectOfLanguage {
        private final boolean isAbstract;
        private FunctionPrototype functionPrototype;
        // TODO don't this constructor values are needed?
        private ConstructorMethodPrototype constructorMethodPrototype;

        public boolean isAbstract() {
            assert constructorMethodPrototype == null;

            return this.isAbstract;
        }

        public FunctionPrototype getFunctionPrototype() {
            assert constructorMethodPrototype == null;

            return this.functionPrototype;
        }

        public boolean isConstructor() {
            assert functionPrototype == null;

            return constructorMethodPrototype != null;
        }

        public ConstructorMethodPrototype getConstructorMethodPrototype() {
            assert functionPrototype == null;

            return this.constructorMethodPrototype;
        }

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isMethodPrototype() {
            return true;
        }

        public MethodPrototype(ConstructorMethodPrototype constructorMethodPrototype, ObjectOfLanguage nameSpace, boolean isAbstract) {
            super(constructorMethodPrototype.getName(), nameSpace);
            this.constructorMethodPrototype = constructorMethodPrototype;
            this.isAbstract = false;
            this.functionPrototype = null;
        }

        public MethodPrototype(FunctionPrototype functionPrototype, ObjectOfLanguage nameSpace, boolean isAbstract) {
            super(functionPrototype.getName(), nameSpace);
            this.functionPrototype = functionPrototype;
            this.isAbstract = isAbstract;
            this.constructorMethodPrototype = null;
        }
    }

    class ConstructorMethodPrototype extends ObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isConstructorMethodPrototype() {
            return true;
        }

        public void addParameter(Parameter parameter) {
            parameterList.add(parameter);
        }

        public ArrayList<Parameter> getParameterList() {
            return this.parameterList;
        }

        public ConstructorMethodPrototype(ObjectOfLanguage type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            parameterList = new ArrayList<>();
        }
    }

    class TypeArgument extends ObjectOfLanguage {
        // Can be of class TypeRef, NonTypename, or BaseTypes
        private final ObjectOfLanguage type;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTypeArgument() {
            return true;
        }

        public Class getTypeClass() {
            return this.type.getClass();
        }

        public TypeArgument(ObjectOfLanguage type, ObjectOfLanguage nameSpace) {
            super(type.getName(), nameSpace);
            this.type = type;
        }
    }

    class Expression extends ObjectOfLanguage {
        /*
        Terminal (Integer, string literal, true, false, this)
        nonTypeName (w/ dotPrefix)
        kvList
        typeName (w/ dot_name)
        ERROR DOT name

        Assuming that the parser will find the terminal and pass a string to this constructor
        */

        private final InvokingExpression invokingExpression;

        public boolean isInvokingExpression() {
            return invokingExpression != null;
        }

        // What about expressions with L_BRACE?
        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isExpression() {
            return true;
        }

        public Expression(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.invokingExpression = null;
        }

        public Expression(InvokingExpression invokingExpression, ObjectOfLanguage nameSpace) {
            super(invokingExpression.getName(), nameSpace);
            this.invokingExpression = invokingExpression;
        }
    }

    class InvokingExpression extends ObjectOfLanguage {
        private final ArrayList<Argument> argumentList;
        private final ArrayList<RealTypeArgument> realTypeArgumentList;
        private final Expression expression;
        private final NamedType namedType;
        private final TypeRef typeRef;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isInvokingExpression() {
            return true;
        }

        public ArrayList<Argument> getArgumentList() {
            assert this.argumentList != null;

            return this.argumentList;
        }

        public ArrayList<RealTypeArgument> getRealTypeArgumentList() {
            assert this.realTypeArgumentList != null;

            return this.realTypeArgumentList;
        }

        public Expression getExpression() {
            assert this.expression != null;

            return this.expression;
        }

        public NamedType getNamedType() {
            assert this.namedType != null;

            return this.namedType;
        }

        public TypeRef getTypeRef() {
            assert this.typeRef != null;

            return this.typeRef;
        }

        public void addToRealTypeArgumentList(RealTypeArgument typeArgument) {
            assert this.realTypeArgumentList != null;

            this.realTypeArgumentList.add(typeArgument);
        }

        public void addToArgumentList(Argument argument) {
            assert this.argumentList != null;

            this.argumentList.add(argument);
        }

        public InvokingExpression(Expression expression, ObjectOfLanguage nameSpace) {
            super(expression.getName(), nameSpace);
            this.expression = expression;
            this.realTypeArgumentList = new ArrayList<>();
            this.argumentList = new ArrayList<>();
            this.namedType = null;
            this.typeRef = null;
        }

        public InvokingExpression(NamedType namedType, ObjectOfLanguage nameSpace) {
            super(namedType.getName(), nameSpace);
            this.expression = null;
            this.realTypeArgumentList = null;
            this.argumentList = new ArrayList<>();
            this.namedType = namedType;
            this.typeRef = null;
        }

        public InvokingExpression(TypeRef typeRef, Expression expression, ObjectOfLanguage nameSpace) {
            super(typeRef.getName(), nameSpace);
            this.expression = expression;
            this.realTypeArgumentList = null;
            this.argumentList = null;
            this.namedType = null;
            this.typeRef = typeRef;
        }
    }

    class RealTypeArgument extends ObjectOfLanguage {
        private ConstantTreeGlobalObjects void_or_dontcare;
        private TypeRef typeRef;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isRealTypeArgument() {
            return false;
        }

        public boolean isTypeRef() {
            return this.typeRef != null;
        }

        public boolean isVoid() {
            return this.void_or_dontcare.getName() == "void";
        }

        public boolean isDontCare() {
            return this.void_or_dontcare.getName() == "_";
        }

        public ConstantTreeGlobalObjects getVoidOrDontCare() {
            assert this.void_or_dontcare != null;

            return this.void_or_dontcare;
        }

        public TypeRef getTypeRef() {
            assert this.typeRef != null;

            return this.typeRef;
        }

        public RealTypeArgument(ConstantTreeGlobalObjects void_or_dontare, ObjectOfLanguage scope) {
            super(void_or_dontare.getName(), scope);
            this.void_or_dontcare = void_or_dontare;
            this.typeRef = null;
        }

        public RealTypeArgument(TypeRef typeRef, ObjectOfLanguage scope) {
            super(typeRef.getName(), scope);
            this.void_or_dontcare = null;
            this.typeRef = typeRef;
        }
    }

    class Argument extends ObjectOfLanguage {
        private final Expression expression;
        private final Name name;
        private final ConstantTreeGlobalObjects dontcare; // for dont care
        private boolean isAssignment;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isArgument() {
            return true;
        }

        public boolean isAssignment() {
            return this.isAssignment;
        }

        public Expression getExpression() {
            assert this.expression != null;

            return this.expression;
        }

        public Name getNameObject() {
            assert this.name != null;

            return this.name;
        }

        public ConstantTreeGlobalObjects getDontCare() {
            assert this.dontcare != null;

            return this.dontcare;
        }

        Argument(Name name, Expression expression, ObjectOfLanguage scope) {
            super(name.getName(), scope);
            this.name = name;
            this.expression = expression;
            this.dontcare = null;
            this.isAssignment = true;
        }

        Argument(Expression expression, ObjectOfLanguage scope) {
            super(expression.getName(), scope);
            this.name = null;
            this.expression = expression;
            this.dontcare = null;
            this.isAssignment = false;
        }
        Argument(ConstantTreeGlobalObjects dontcare, ObjectOfLanguage scope) {
            super(dontcare.getName(), scope);
            this.name = null;
            this.expression = null;
            this.dontcare = dontcare;
            this.isAssignment = false;
        }
    }
    
    class Name extends ObjectOfLanguage {
        private final ObjectOfLanguage name;

        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isName() {
            return true;
        }

        public Name(ObjectOfLanguage name, ObjectOfLanguage scope) {
            super(name.getName(), scope);
            this.name = name;
        }
    }

    public class BaseTypes {
        private ArrayList<String> baseTypes;
        private Map<String, ObjectOfLanguage> baseTypeObjects;
        private ConstantTreeGlobalObjects voidObject;
        private ConstantTreeGlobalObjects dontCareObject;
        private String voidString = "void";
        private String dontCare = "_";

        {
            baseTypes = new ArrayList<>();
            baseTypes.add("bool");
            baseTypes.add("error");
            baseTypes.add("bit");
            baseTypes.add("string");
            baseTypes.add("int");
            baseTypes.add("varbit");

            baseTypeObjects = new HashMap<>();

            for(String type : baseTypes) {
                baseTypeObjects.put(type, new ConstantTreeGlobalObjects(type));
            }

            voidObject = new ConstantTreeGlobalObjects(voidString);
            dontCareObject = new ConstantTreeGlobalObjects(dontCare);
        }

        public boolean isBaseType(String type) {
            return baseTypes.contains(type);
        }

        public ObjectOfLanguage getLanguageObjectOfBaseType(String type) {
            assert baseTypes.contains(type);

            return baseTypeObjects.get(type);
        }

        public ConstantTreeGlobalObjects getVoidLanguageObject() {
            return this.voidObject;
        }

        public ConstantTreeGlobalObjects getDontCareLanguageObject() {
            return this.dontCareObject;
        }

        public boolean isVoid(String type) {
            return type == voidString;
        }

        public boolean isDontCare(String type) {
            return type == dontCare;
        }
    }

    public class Direction {
        private ArrayList<String> directions;
        private Map<String, ObjectOfLanguage> directionTypeObjects;

        {
            directions = new ArrayList<>();
            directions.add("in");
            directions.add("out");
            directions.add("inout");


            for(String type : directions) {
                directionTypeObjects.put(type, new ConstantTreeGlobalObjects(type));
            }
        }

        public ObjectOfLanguage getLanguageObjectOfDirection(String type) {
            assert directions.contains(type);

            return directionTypeObjects.get(type);
        }
    }
}
// TODO:make isTypeRef() true for all functions with a type variable