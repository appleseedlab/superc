package superc.p4parser;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

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

        public int hashCode(ObjectOfLanguage global_scope) {
            String hashString = "";
            if(this.nameSpace != null) {
                // not the GLOBAL ObjectOfLanguage
                hashString += this.getParentNameSpaces(global_scope) + "/";
            }
            hashString += this.name;
            
            return hashString.hashCode();
        }

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
        private ArrayList<MethodPrototype> methodPrototypes;

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
    }

    class ExternFunctionDeclaration extends ObjectOfLanguage {
        private FunctionPrototype functionPrototype;

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

        public void setFunctionPrototype(FunctionPrototype functionPrototype) {
            this.functionPrototype = functionPrototype;
        }

        public ExternFunctionDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class FunctionPrototype extends ObjectOfLanguage {
        private ObjectOfLanguage returnType;
        private ArrayList<Parameter> parameterList;

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

        public void setParameters(ArrayList<Parameter> parameterList) {
            this.parameterList = parameterList;
        }

        public ObjectOfLanguage getReturnType() {
            return this.returnType;
        }

        public void setReturnType(ObjectOfLanguage returnType) {
            this.returnType = returnType;
        }

        public FunctionPrototype(String name, ObjectOfLanguage nameSpace, ObjectOfLanguage returnType) {
            super(name, nameSpace);
            this.returnType = returnType;
            parameterList = new ArrayList<>();
        }
    }

    class Parameter extends ObjectOfLanguage {
        private TypeRef type;
        // private Expression assignedExpression;
        private boolean hasAssignedExpression;
        private ConstantTreeGlobalObjects direction;

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
        ObjectOfLanguage type;

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTypeRef() {
            return true;
        }

        public TypeRef(ObjectOfLanguage type, ObjectOfLanguage nameScope) {
            super(type.getName(), nameScope);
            this.type = type;
        }
    }

    class SpecializedType extends ObjectOfLanguage {
        private TypeName type;
        // private ArrayList<TypeArgument> typeArgumentList;

        public TypeName getType() {
            return this.type;
        }
        public void setType(TypeName type) {
            this.type = type;
        }

        // public ArrayList<TypeArgument> getTypeArgumentList() {
        //     return this.typeArgumentList;
        // }

        // public void setTypeArgumentList(ArrayList<TypeArgument> typeArgumentList) {
        //     this.typeArgumentList = typeArgumentList;
        // }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isSpecializedType() {
            return true;
        }

        public SpecializedType(TypeName type, ObjectOfLanguage nameScope) {
            super(type.getName(), nameScope);
            this.type = type;
            // typeArgumentList = new ArrayList<>();
        }

        // public SpecializedType(TypeName type, ObjectOfLanguage nameScope, ArrayList<TypeArgument> typeArgumentList) {
        //     super(type.getName(), nameScope);
        //     this.type = type;
        //     this.typeArgumentList = typeArgumentList;
        // }
    }

    class HeaderStackType extends ObjectOfLanguage {
        private TypeName type;
        private SpecializedType specializedType;
        private boolean hasTypeName;
        private boolean hasSpecializedType;
        // private Expression expression;

        public TypeName getType() {
            return this.type;
        }

        public void setType(TypeName type) {
            this.type = type;
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

        public boolean hasTypeName() {
            return this.hasTypeName;
        }

        public boolean hasSpecializedType() {
            return this.hasSpecializedType;
        }

        public HeaderStackType(TypeName type, ObjectOfLanguage nameScope) {
            super(type.getName(), nameScope);
            this.type = type;
            hasTypeName = true;
            hasSpecializedType = false;
        }

        public HeaderStackType(SpecializedType specializedType, ObjectOfLanguage nameScope) {
            super(specializedType.getType().getName(), nameScope);
            this.specializedType = specializedType;
            hasTypeName = false;
            hasSpecializedType = true;
        }
    }

    class TupleType extends ObjectOfLanguage {
        // private ArrayList<TypeArgument> typeArgumentList;

        // public ArrayList<TypeArgument> getTypeArgumentList() {
        //     return this.typeArgumentList;
        // }

        // public void setTypeArgumentList(ArrayList<TypeArgument> typeArgumentList) {
        //     this.typeArgumentList = typeArgumentList;
        // }

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTupleType() {
            return true;
        }

        public TupleType(ObjectOfLanguage nameScope) {
            super("TUPLE", nameScope);
        }

        // public TupleType(ObjectOfLanguage nameScope, ArrayList<TypeArgument> typeArgumentList) {
        //     super("TUPLE", nameScope);
        //     this.typeArgumentList = typeArgumentList;
        // }
    }

    class TypeName extends ObjectOfLanguage {
        PrefixedType prefixedType;

        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isTypeName() {
            return true;
        }

        public boolean hasDotPrefix() {
            return this.prefixedType.hasDotPrefix();
        }

        public TypeName(PrefixedType prefixedType,ObjectOfLanguage nameScope) {
            super(prefixedType.getName(), nameScope);
            this.prefixedType = prefixedType;
        }
    }

    class PrefixedType extends ObjectOfLanguage {
        private ObjectOfLanguage type;
        private boolean hasDotPrefix;
        @Override 
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isPrefixedType() {
            return true;
        }

        boolean hasDotPrefix() {
            return this.hasDotPrefix;
        }

        public PrefixedType(String name, ObjectOfLanguage typeObject, ObjectOfLanguage nameScope, boolean hasDotPrefix) {
            super(name, nameScope);
            this.type = typeObject;
            this.hasDotPrefix = hasDotPrefix;
        }
    }

    // todo: method prototype, function prototype, extern function declaration
    class MethodPrototype extends ObjectOfLanguage {
        @Override
        boolean isScoped() {
            return false;
        }

        @Override
        boolean isMethodPrototype() {
            return true;
        }

        public MethodPrototype(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    public class BaseTypes {
        private ArrayList<String> baseTypes;
        private Map<String, ObjectOfLanguage> baseTypeObjects;
        private ConstantTreeGlobalObjects voidObject;
        private String voidString = "void";

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

        public boolean isVoid(String type) {
            return type == voidString;
        }

    }

    public class Direction {
        private ArrayList<String> directions;
        private Map<String, ObjectOfLanguage> directionTypeObjects;

        {
            directions = new ArrayList<>();
            directions.add("bool");
            directions.add("error");
            directions.add("bit");


            for(String type : directions) {
                directionTypeObjects.put(type, new ConstantTreeGlobalObjects(type));
            }
        }

        public ObjectOfLanguage getLanguageObjectOfDirection(String type) {
            assert directions.contains(type);

            return directionTypeObjects.get(type);
        }
    }
// TODO: prioritize expression and typeArgumentList and uncomment corresponding code
}