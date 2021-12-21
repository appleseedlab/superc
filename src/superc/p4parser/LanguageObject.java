package superc.p4parser;
import java.beans.Expression;
import java.io.ObjectInputStream;
import java.lang.StackWalker.Option;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;

import javax.naming.ldap.PagedResultsResponseControl;
import javax.sound.midi.SysexMessage;

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
    enum LObjectKind {
        VARIABLE,
        FUNCTION,
        STRUCT,
        HEADER,
        CONTROLBLOCK,
        EXTERNDECLARATION,
        EXTERNFUNCTIONDECLARATION,
        METHODPROTOTYPE,
        FUNCTIONPROTOTYPE,
        PARAMETER,
        EXPRESSION,
        SPECIALIZEDTYPE,
        HEADERSTACKTYPE,
        TUPLETYPE,
        PREFIXEDTYPE,
        TYPENAME,
        CONSTRUCTORMETHODPROTOTYPE,
        TYPEARGUMENT,
        NAMEDTYPE,
        INVOKINGEXPRESSION,
        NAME,
        ARGUMENT,
        REALTYPEARGUMENT,
        CONSTANTVALUE,
        TYPEREF,
        KVPAIR,
        STRUCTUREDANNOTATIONBODY,
        ANNOTATIONBODY,
        STRING,
        OPTINITIALIZER,
        INITIALIZER,
        CONTROLTYPE,
        TYPEPARAMETER,
        STRUCTFIELD,
        IDENTIFIERLIST,
        HEADERTYPEDECLARATION,
        HEADERUNION,
        STRUCTTYPEDECLARATION,
        ENUMDECLARATION,
        TYPEDEFDECLARATION,
        PARSERTYPEDECLARATION,
        PACKAGETYPEDECLARATION,
        ERROR,
        MATCHKIND,
        ASSIGNMENT,
        METHODCALLSTATEMENT,
        RETURNSTATEMENT,
        LVALUE,
        LVALUEEXPRESSION,
        CONDITIONALSTATEMENT,
        DIRECTAPPLICATION,
        BLOCKSTATEMENT,
        SWITCHSTATEMENT,
        SWITCHCASE,
        TABLEDECLARATION,
        TABLEPROPERTY,
        KEYELEMENT,
        ACTION,
        ACTIONREF,
        ENTRY,
        ACTIONDECLARATION,
        CONSTANTDECLARATION,
        FUNCTIONDECLARATION,
        NONBRACEEXPRESSION,
        INVOKINGNONBRACEEXPRESSION,
        INTEGER,
        VARIABLEDECLARATION,
        ANNOTATION,
        INSTANTIATION,
        INSTANTIATIONWITHASSIGNMENT,
        OBJINITIALIZER,
        PARSERDECLARATION,
        PARSERSTATE,
        PARSERBLOCKSTATEMENT,
        STATEEXPRESSION,
        SELECTEXPRESSION,
        SELECTCASE
    }

    abstract class ObjectOfLanguage {
        private final String name;
        private final ObjectOfLanguage nameSpace;
        abstract boolean isScoped();
        // not making this private to avoid allocating memory since it is not present most times
        private ArrayList<Parameter> optConstructorParameters = null;
        private ArrayList<Annotation> optAnnotations = null;
        private ArrayList<TypeParameter> optTypeParameters = null;
        // abstract method to return respective enum
        abstract LObjectKind getConstructType();

        boolean hasAssociatedType() {
            return false;
        }

        public String getName() {
            if(this.name == null) {
                System.err.println(this.getConstructType().toString() + " construct does not have a name associated with it.");
            }

            return this.name;
        }

        public boolean hasName() {
            return this.name != null;
        }

        public boolean hasOptConstructorParameters() {
            return (optConstructorParameters != null);
        }

        public boolean hasOptAnnotations() {
            return optAnnotations != null;
        }

        void addOptTypeParameters(TypeParameter typeParameter) {
            if(this.optTypeParameters == null) {
                this.optTypeParameters = new ArrayList<>();
            }

            this.optTypeParameters.add(typeParameter);
        }

        boolean hasOptTypeParameters() {
            return !this.optTypeParameters.isEmpty();
        }

        ArrayList<TypeParameter> getOptTypeParameters() {
            return this.optTypeParameters;
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

        public ArrayList<Parameter> getOptConstructorParameters() {
            return this.optConstructorParameters;
        }

        public void addToOptConstructorParametersList(Parameter parameter) {
            if(optConstructorParameters == null) {
                this.optConstructorParameters = new ArrayList<>();
            }

            this.optConstructorParameters.add(parameter);
        }

        public void addToOptAnnotations(Annotation annotation) {
            if (optAnnotations == null) {
                this.optAnnotations = new ArrayList<>();
            }

            this.optAnnotations.add(annotation);
        }

        public ObjectOfLanguage(String name, ObjectOfLanguage nameSpace) {
            this.name = name;
            this.nameSpace = nameSpace;
        }

        public ObjectOfLanguage(ObjectOfLanguage nameSpace) {
            this.name = null;
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
        private final boolean isScoped;
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.CONSTANTVALUE;
        }

        @Override
        public boolean isScoped() {
            return isScoped;
        }

        @Override
        public ObjectOfLanguage getNameSpace() {
            System.err.println("ConstantTreeGlobalObjects do not have a namespace since they are global level");
            System.exit(1);

            return null;
        }

        public ConstantTreeGlobalObjects(String name, boolean isScoped) {
            super(name, null);
            this.isScoped = isScoped;
        }

        public ConstantTreeGlobalObjects(String name) {
            super(name, null);
            this.isScoped = true;
        }
    }

    class ControlDeclaration extends ObjectOfLanguage {
        ControlTypeDeclaration controlTypeDeclaration;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONTROLBLOCK;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public ControlDeclaration(String name, ObjectOfLanguage nameSpace, ControlTypeDeclaration controlTypeDeclaration) {
            super(name, nameSpace);
            this.controlTypeDeclaration = controlTypeDeclaration;
        }
    }

    class ControlTypeDeclaration extends ObjectOfLanguage {
        private ArrayList<Parameter> parameterList;
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.CONTROLTYPE;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasParameters() {
            return !this.parameterList.isEmpty();
        }

        public void addParameter(Parameter parameter) {
            this.parameterList.add(parameter);
        }

        public ControlTypeDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList<>();
        }
    }

    class TypeParameter extends ObjectOfLanguage {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEPARAMETER;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        TypeParameter(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
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
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNDECLARATION;
        }

        // technically scoped for "optAnnotations EXTERN name SEMICOLON" production as well
        @Override
        public boolean isScoped() {
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

        public boolean hasMethodPrototypes() {
            return !this.methodPrototypes.isEmpty();
        }
    }

    class ExternFunctionDeclaration extends ObjectOfLanguage {
        private final FunctionPrototype functionPrototype;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNFUNCTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public FunctionPrototype getFunctionDeclaration() {
            return this.functionPrototype;
        }

        public ExternFunctionDeclaration(ObjectOfLanguage nameSpace, FunctionPrototype functionPrototype) {
            super(functionPrototype.getName(), nameSpace);
            this.functionPrototype = functionPrototype;
        }
    }

    class FunctionPrototype extends ObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;
        private final TypeOrVoid typeOrVoid;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.FUNCTIONPROTOTYPE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public ArrayList<Parameter> getParameters() {
            return this.parameterList;
        }

        TypeOrVoid getReturnType() {
            return this.typeOrVoid;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type object
        // and will pass it to us
        public FunctionPrototype(String name, ObjectOfLanguage nameSpace, TypeOrVoid typeOrVoid) {
            super(name, nameSpace);
            parameterList = new ArrayList<>();
            this.typeOrVoid = typeOrVoid;
        }
    }

    class TypeOrVoid extends ObjectOfLanguage {
        private TypeRef typeRef;
        private ConstantTreeGlobalObjects voidVar;
        private ObjectOfLanguage identifier;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARAMETER;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        // void and dontcare are still types
        @Override
        boolean hasAssociatedType() {
            return true;
        }

        boolean isConstantTreeGlobalObjects() {
            return voidVar != null;
        }

        boolean isTypeRef() {
            return typeRef != null;
        }

        boolean isIdentifier() {
            return identifier != null;
        }

        TypeOrVoid(TypeRef typeRef, ObjectOfLanguage nameSpace) {
            super(typeRef.getName(), nameSpace);
            this.typeRef = typeRef;
            this.identifier = null;
            this.voidVar = null;
        }

        TypeOrVoid(ObjectOfLanguage identifier, ObjectOfLanguage nameSpace) {
            super(identifier.getName(), nameSpace);
            this.identifier = identifier;
            this.typeRef = null;
            this.voidVar = null;
        }

        TypeOrVoid(ConstantTreeGlobalObjects voidVar, ObjectOfLanguage nameSpace) {
            super(voidVar.getName(), nameSpace);
            this.identifier = null;
            this.typeRef = null;
            this.voidVar = voidVar;
        }

    }

    class StructField extends ObjectOfLanguage {
        private final TypeRef type;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.STRUCTFIELD;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public TypeRef getType() {
            return this.type;
        }

        public StructField(String name, ObjectOfLanguage nameSpace, TypeRef typeRef) {
            super(name, nameSpace);
            this.type = typeRef;
        }
    }

    class IdentifierList extends ObjectOfLanguage {
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.IDENTIFIERLIST;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public IdentifierList(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class SpecifiedIdentifier extends ObjectOfLanguage {
        // Initializer is just expression
        private final Initializer initializer;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.IDENTIFIERLIST;
        }

        @Override
        public boolean isScoped() {
            return initializer.isScoped();
        }

        public Initializer getInitializer() {
            return this.initializer;
        }

        public SpecifiedIdentifier(String name, ObjectOfLanguage nameSpace, Initializer initializer) {
            super(name, nameSpace);
            this.initializer = initializer;
        }
    }

    class HeaderTypeDeclaration extends ObjectOfLanguage {
        private final ArrayList<StructField> structFieldList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.HEADERTYPEDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        ArrayList<StructField> getStructFieldList() {
            return this.structFieldList;
        }

        public boolean hasStructFieldList() {
            return !this.structFieldList.isEmpty();
        }

        public void addToStructFieldList(StructField structField) {
            this.structFieldList.add(structField);
        }

        HeaderTypeDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    class HeaderUnion extends ObjectOfLanguage {
        private final ArrayList<StructField> structFieldList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.HEADERUNION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        ArrayList<StructField> getStructFieldList() {
            return this.structFieldList;
        }

        public boolean hasStructFieldList() {
            return !this.structFieldList.isEmpty();
        }

        public void addToStructFieldList(StructField structField) {
            this.structFieldList.add(structField);
        }

        HeaderUnion(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    class StructTypeDeclaration extends ObjectOfLanguage {
        private final ArrayList<StructField> structFieldList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.STRUCTTYPEDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        ArrayList<StructField> getStructFieldList() {
            return this.structFieldList;
        }

        public boolean hasStructFieldList() {
            return !this.structFieldList.isEmpty();
        }

        public void addToStructFieldList(StructField structField) {
            this.structFieldList.add(structField);
        }

        StructTypeDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    class EnumDeclaration extends ObjectOfLanguage {
        // normal enums and serializable enums that have an associated type
        private final TypeRef type;
        private final ArrayList<IdentifierList> identifierList;
        private final ArrayList<SpecifiedIdentifier> specifiedIdentifierList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ENUMDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        @Override
        boolean hasAssociatedType() {
            return this.type != null;
        }

        public TypeRef getType() {
            return this.type;
        }

        public boolean hasIdentifiersList() {
            return (this.identifierList != null && 
                    !this.identifierList.isEmpty());
        }

        public boolean hasSpecifiedIdentifiersList() {
            return (this.specifiedIdentifierList != null 
                    && !this.specifiedIdentifierList.isEmpty());
        }

        public void addToIdentifierList(IdentifierList identifier) {
            this.identifierList.add(identifier);
        }

        public void addToSpecifiedIdentifierList(SpecifiedIdentifier identifier) {
            this.specifiedIdentifierList.add(identifier);
        }

        public ArrayList<IdentifierList> getIdentifierList() {
            return this.identifierList;
        }

        public ArrayList<SpecifiedIdentifier> getSpecifiedIdentifierList() {
            return this.specifiedIdentifierList;
        }

        public EnumDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.type = null;
            this.identifierList = new ArrayList<>();
            this.specifiedIdentifierList = null;
        }

        public EnumDeclaration(String name, ObjectOfLanguage nameSpace, TypeRef type) {
            super(name, nameSpace);
            this.type = type;
            this.specifiedIdentifierList = new ArrayList<>();
            this.identifierList = null;
        }
    }

    class TypeDefDeclaration extends ObjectOfLanguage {
        // typdef vs type -> difference is made in parsing context where both values
        // are stored in symtab for TYPEDEF while only newly declared variable name is stored
        // in symtab for TYPE
        private final ObjectOfLanguage type;
        private final boolean isTypeDef;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEDEFDECLARATION;
        }

        /* Since type can either be of TypeRef or derivedTypeDeclaration
        where derivedTypeDeclaration can be headerTypeDeclaration, headerUnionDeclaration
        structTypeDeclaration, or enumDeclaration, and they can be scoped.
        */
        @Override
        public boolean isScoped() {
            if(type.getClass().equals(TypeRef.class)) {
                return false;
            } else {
                return type.isScoped();
            }
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public ObjectOfLanguage getType() {
            return this.type;
        }

        public boolean isTypeDef() {
            return this.isTypeDef;
        }

        public TypeDefDeclaration(String name, ObjectOfLanguage nameSpace, ObjectOfLanguage type, Boolean typeDef) {
            super(name, nameSpace);

            Class typeClass = type.getClass();
            if(typeClass == HeaderTypeDeclaration.class || typeClass == StructTypeDeclaration.class
               || typeClass == EnumDeclaration.class || typeClass == TypeRef.class) {
               } else {
                    System.err.println("Error: Type used in TypeDef for " + name + " has to be of type either TypeRef or DerivedTypeDeclaration");
                    System.exit(1);
            }

            this.type = type;
            this.isTypeDef = typeDef;
        }
    }

    class ParserTypeDeclaration extends ObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERTYPEDECLARATION;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        public boolean hasParameters() {
            return !this.parameterList.isEmpty();
        }

        public void addToParameterList(Parameter parameter) {
            this.parameterList.add(parameter);
        }

        public ArrayList<Parameter> getParameterList() {
            return this.parameterList;
        }

        public ParserTypeDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList();
        }
    }

    class PackageTypeDeclaration extends ObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PACKAGETYPEDECLARATION;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        public boolean hasParameters() {
            return !this.parameterList.isEmpty();
        }

        public void addToParameterList(Parameter parameter) {
            this.parameterList.add(parameter);
        }

        public ArrayList<Parameter> getParameterList() {
            return this.parameterList;
        }

        public PackageTypeDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList();
        }
    }

    class Instantiation extends ObjectOfLanguage {
        private final ArrayList<Annotation> annotations;
        private final ArrayList<Argument> argumentList;
        private final TypeRef type;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.INSTANTIATION;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public boolean hasAssociatedType() {
            return true;
        }

        public TypeRef getType() {
            return this.type;
        }

        public boolean hasArgumentList() {
            return this.argumentList != null;
        }

        public ArrayList<Argument> getArgumentList() {
            return this.argumentList;
        }

        public void addToArgumentList(Argument argument) {
            this.argumentList.add(argument);
        }

        public boolean hasAnnotations() {
            return this.annotations != null;
        }

        public void addToAnnotationsList(Annotation annotation) {
            this.annotations.add(annotation);
        }

        public ArrayList<Annotation> getAnnotations() {
            return this.annotations;
        }

        public Instantiation(String name, ObjectOfLanguage nameSpace, TypeRef type, boolean hasAnnotations) {
            super(name, nameSpace);
            this.type = type;
            this.argumentList = new ArrayList<>();
            if(hasAnnotations) {
                this.annotations = new ArrayList<>();
            } else {
                this.annotations = null;
            }
        }
    }

    class InstantiationWithAssignment extends ObjectOfLanguage {
        private final ArrayList<Annotation> annotations;
        private final ArrayList<Argument> argumentList;
        private final TypeRef type;
        private final ObjInitializer objInitializer;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.INSTANTIATIONWITHASSIGNMENT;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        @Override
        public boolean hasAssociatedType() {
            return true;
        }

        public TypeRef getType() {
            return this.type;
        }

        public boolean hasArgumentList() {
            return this.argumentList != null;
        }

        public ArrayList<Argument> getArgumentList() {
            return this.argumentList;
        }

        public void addToArgumentList(Argument argument) {
            this.argumentList.add(argument);
        }

        public boolean hasAnnotations() {
            return this.annotations != null;
        }

        public void addToAnnotationsList(Annotation annotation) {
            this.annotations.add(annotation);
        }

        public ArrayList<Annotation> getAnnotations() {
            return this.annotations;
        }

        public ObjInitializer getObjInitializer() {
            return this.objInitializer;
        }

        public InstantiationWithAssignment(String name, ObjectOfLanguage nameSpace, TypeRef type, boolean hasAnnotations, ObjInitializer objInitializer) {
            super(name, nameSpace);
            this.type = type;
            this.argumentList = new ArrayList<>();
            this.objInitializer = objInitializer;
            if(hasAnnotations) {
                this.annotations = new ArrayList<>();
            } else {
                this.annotations = null;
            }
        }
    }

    class ObjInitializer extends ObjectOfLanguage {
        private final ArrayList<ObjectOfLanguage> objDeclarations;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.OBJINITIALIZER;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasObjDeclarations() {
            return !this.objDeclarations.isEmpty();
        }

        public void addToObjDeclarations(ObjectOfLanguage obj) {
            assert obj.getClass().equals(FunctionDeclaration.class) || obj.getClass().equals(Instantiation.class);
            this.objDeclarations.add(obj);
        }

        public ArrayList<ObjectOfLanguage> getObjDeclarations() {
            return this.objDeclarations;
        }

        public ObjInitializer(ObjectOfLanguage nameSpace) {
            super(nameSpace);
            this.objDeclarations = new ArrayList<>();
        }
    }

    class ParserDeclaration extends ObjectOfLanguage {
        private final ParserTypeDeclaration parserTypeDeclaration;
        private final ArrayList<ObjectOfLanguage> parserLocalElements;
        private final ArrayList<ParserState> parserStates;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasParserStates() {
            assert !this.parserStates.isEmpty() : "There needs to be at least one parser statement";

            return true;
        }
        
        public void addToParserStates(ParserState pState) {
            this.parserStates.add(pState);
        }

        public ArrayList<ParserState> getParserStates() {
            assert !this.parserStates.isEmpty() : "There needs to be at least one parser statement";

            return this.parserStates;
        }

        public boolean hasParserLocalElements() {
            return !this.parserLocalElements.isEmpty();
        }

        public void addToParserLocalElements(ObjectOfLanguage element) {
            this.parserLocalElements.add(element);
        }

        public ArrayList<ObjectOfLanguage> getParserLocalElements() {
            return this.parserLocalElements;
        }

        public ParserTypeDeclaration getParserTypeDeclaration() {
            return this.parserTypeDeclaration;
        }

        public ParserDeclaration(String name, ObjectOfLanguage nameSpace, ParserTypeDeclaration pTypeDeclaration) {
            super(name, nameSpace);
            this.parserTypeDeclaration = pTypeDeclaration;
            this.parserLocalElements = new ArrayList<>();
            this.parserStates = new ArrayList<>();
        }
    }

    class ParserState extends ObjectOfLanguage {
        private final ArrayList<ObjectOfLanguage> parserStatements;
        private final StateExpression transitionStatement;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERSTATE;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasParserStatements() {
            return !this.parserStatements.isEmpty();
        }

        public void addToParserStatements(ObjectOfLanguage element) {
            this.parserStatements.add(element);
        }

        public ArrayList<ObjectOfLanguage> getParseStatements() {
            return this.parserStatements;
        }

        public boolean hasTransitionStatement() {
            return this.transitionStatement != null;
        }

        public StateExpression getTransitionStatement() {
            return this.transitionStatement;
        }

        public ParserState(String name, ObjectOfLanguage nameSpace, StateExpression transitionStatement) {
            super(name, nameSpace);
            this.transitionStatement = transitionStatement;
            this.parserStatements = new ArrayList<>();
        }
    }

    class ParserBlockStatement extends ObjectOfLanguage {
        private final ArrayList<ObjectOfLanguage> parserStatements;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERBLOCKSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasParserStatements() {
            return !this.parserStatements.isEmpty();
        }

        public void addToParserStatements(ObjectOfLanguage element) {
            this.parserStatements.add(element);
        }

        public ArrayList<ObjectOfLanguage> getParseStatements() {
            return this.parserStatements;
        }

        public ParserBlockStatement(ObjectOfLanguage nameSpace) {
            super(nameSpace);
            this.parserStatements = new ArrayList<>();
        }
    }

    class StateExpression extends ObjectOfLanguage {
        private final SelectExpression selectExpression;
        private final ObjectOfLanguage transitionBlock;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.STATEEXPRESSION;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public String getName() {
            if(this.transitionBlock != null) {
                assert this.selectExpression == null;

                return this.getName();
            } else {
                System.err.println("This state expression has multiple values associated with it (select expression)");
                System.exit(1);
                return "";
            }
        }

        public boolean hasSelectionExpression() {
            return this.selectExpression != null;
        }

        public SelectExpression getSelectExpression() {
            return this.selectExpression;
        }

        public ObjectOfLanguage getTransitionBlock() {
            return this.transitionBlock;
        }

        public StateExpression(String name, ObjectOfLanguage nameSpace, ObjectOfLanguage transitionBlock) {
            super(name, nameSpace);
            this.selectExpression = null;
            this.transitionBlock = transitionBlock;
        }

        public StateExpression(ObjectOfLanguage nameSpace, SelectExpression selectExpression) {
            super(nameSpace);
            this.selectExpression = selectExpression;
            this.transitionBlock = null;
        }
    }

    class SelectExpression extends ObjectOfLanguage {
        private final ArrayList<Expression> expressionList;
        private final ArrayList<SelectCase> selectCaseList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.SELECTEXPRESSION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public void addToExpressionList(Expression expression) {
            this.expressionList.add(expression);
        }

        public boolean hasExpressionList() {
            return ! this.expressionList.isEmpty();
        }

        public ArrayList<Expression> getExpressionList() {
            return this.expressionList;
        }

        public void addToSelectCaseList(SelectCase expression) {
            this.selectCaseList.add(expression);
        }

        public boolean hasSelectCaseList() {
            return ! this.selectCaseList.isEmpty();
        }

        public ArrayList<SelectCase> getSelectCaseList() {
            return this.selectCaseList;
        }

        public SelectExpression(ObjectOfLanguage nameSpace) {
            super(nameSpace);
            this.expressionList = new ArrayList<>();
            this.selectCaseList = new ArrayList<>();
        }
    }
    
    class SelectCase extends ObjectOfLanguage {
        private final ObjectOfLanguage keySetExpression;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.SELECTCASE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public ObjectOfLanguage getKeySetExpression() {
            return this.keySetExpression;
        }

        public SelectCase(String name, ObjectOfLanguage nameSpace, ObjectOfLanguage keySetExpression) {
            super(name, nameSpace);
            this.keySetExpression = keySetExpression;
        }
    }

    class Error extends ObjectOfLanguage {
        private ArrayList<IdentifierList> identifierList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ERROR;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasIdentifiers() {
            return !this.identifierList.isEmpty();
        }

        public void addToIdentifierList(IdentifierList identifier) {
            this.identifierList.add(identifier);
        }

        public ArrayList<IdentifierList> getIdentifierList() {
            return this.identifierList;
        }

        public Error(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.identifierList = new ArrayList<>();
        }
    }

    class MatchKind extends ObjectOfLanguage {
        private ArrayList<IdentifierList> identifierList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.MATCHKIND;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasIdentifiers() {
            return !this.identifierList.isEmpty();
        }

        public void addToIdentifierList(IdentifierList identifier) {
            this.identifierList.add(identifier);
        }

        public ArrayList<IdentifierList> getIdentifierList() {
            return this.identifierList;
        }

        public MatchKind(ObjectOfLanguage nameSpace) {
            super("match_kind", nameSpace);
            this.identifierList = new ArrayList<>();
        }
    }

    class Assignment extends ObjectOfLanguage {
        private final LValue lvalue;
        private final Expression expression;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ASSIGNMENT;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public LValue getLValue() {
            return this.lvalue;
        }

        public Expression getExpression() {
            return this.expression;
        }

        public Assignment(String name, ObjectOfLanguage nameSpace, LValue lvalue, Expression expression) {
            super(name, nameSpace);
            this.lvalue = lvalue;
            this.expression = expression;
        }
    }

    class MethodCallStatement extends ObjectOfLanguage {
        private final LValue lvalue;
        private final ArrayList<Argument> argumentList;
        private final ArrayList<TypeArgument> typeArgumentList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.METHODCALLSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public LValue getLValue() {
            return this.lvalue;
        }

        public boolean hasArgumentList() {
            return this.argumentList != null;
        }

        public ArrayList<Argument> getArgumentList() {
            return this.argumentList;
        }

        public void addToArgumentList(Argument argument) {
            this.argumentList.add(argument);
        }

        public boolean hasTypeArgumentList() {
            return this.typeArgumentList != null;
        }

        public ArrayList<TypeArgument> getTypeArgumentList() {
            return this.typeArgumentList;
        }

        public void addToArgumentList(TypeArgument argument) {
            this.typeArgumentList.add(argument);
        }

        public MethodCallStatement(LValue lvalue, ObjectOfLanguage nameSpace) {
            super(lvalue.getName(), nameSpace);
            this.lvalue = lvalue;
            this.argumentList = new ArrayList<>();
            this.typeArgumentList = new ArrayList<>();
        }
    }

    class ReturnStatement extends ObjectOfLanguage {
        private final Expression expression;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.RETURNSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasExpression() {
            return this.expression != null;
        }

        public Expression getExpression() {
            return this.expression;
        }

        public ReturnStatement(ObjectOfLanguage nameSpace) {
            super("return", nameSpace);
            this.expression = null;
        }

        public ReturnStatement(ObjectOfLanguage nameSpace, Expression expression) {
            super("return", nameSpace);
            this.expression = expression;
        }
    }

    class LValue extends ObjectOfLanguage {
        private final Name associatedValue;
        private final LValueExpression lvalueExpression;
        private boolean hasDotPrefix;
        private LValue recursiveLValue;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.LVALUE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasDotPrefix() {
            return this.hasDotPrefix;
        }

        public boolean hasAssociatedValue() {
            return this.associatedValue != null;
        }

        public ObjectOfLanguage getAssociatedValue() {
            return this.associatedValue;
        }

        public boolean hasLValueExpression() {
            return this.lvalueExpression != null;
        }

        public LValueExpression getLValueExpression() {
            return this.lvalueExpression;
        }

        public boolean hasRecursiveLValue() {
            return this.recursiveLValue != null;
        }

        public LValue getLValueRecursive() {
            return this.recursiveLValue;
        }

        public LValue(String prefixedNonTypeName, boolean hasDotPrefix, ObjectOfLanguage nameSpace) {
            super(prefixedNonTypeName, nameSpace);
            this.associatedValue = null;
            this.hasDotPrefix = hasDotPrefix;
            this.lvalueExpression = null;
            this.recursiveLValue = null;
        }

        public LValue(Name name, LValue recursiveLvalue, ObjectOfLanguage nameSpace) {
            super(recursiveLvalue.getName(), nameSpace);
            this.associatedValue = name;
            this.lvalueExpression = null;
            this.hasDotPrefix = false;
            this.recursiveLValue = recursiveLvalue;
        }

        public LValue(LValueExpression lvalueExpression, LValue recursiveLvalue, ObjectOfLanguage nameSpace) {
            super(recursiveLvalue.getName(), nameSpace);
            this.associatedValue = null;
            this.lvalueExpression = lvalueExpression;
            this.hasDotPrefix = false;
            this.recursiveLValue = recursiveLvalue;
        }

        public LValue(ObjectOfLanguage nameSpace) {
            super("this", nameSpace);
            this.associatedValue = null;
            this.lvalueExpression = null;
            this.hasDotPrefix = false;
            this.recursiveLValue = null;
        }
    }

    class ConditionalStatement extends ObjectOfLanguage {
        private final Expression expresion;
        private final ObjectOfLanguage ifStatement;
        private final ObjectOfLanguage elseStatement;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONDITIONALSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasElseStatement() {
            return this.elseStatement != null;
        }

        public Expression getExpression() {
            return this.expresion;
        }

        public ObjectOfLanguage getIfStatement() {
            return this.ifStatement;
        }

        public ObjectOfLanguage getElseStatement() {
            return this.elseStatement;
        }

        public ConditionalStatement(Expression expression, ObjectOfLanguage ifStatement, ObjectOfLanguage nameSpace) {
            super(expression.getName(), nameSpace);
            this.ifStatement = ifStatement;
            this.elseStatement = null;
            this.expresion = expression;
        }

        public ConditionalStatement(Expression expression, ObjectOfLanguage ifStatement, ObjectOfLanguage elseStatement, ObjectOfLanguage nameSpace) {
            super(expression.getName(), nameSpace);
            this.ifStatement = ifStatement;
            this.elseStatement = elseStatement;
            this.expresion = expression;
        }
    }

    class DirectApplication extends ObjectOfLanguage {
        private final ObjectOfLanguage invokingObject;
        private final ArrayList<Argument> argumentList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.DIRECTAPPLICATION;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasArguments() {
            return !this.argumentList.isEmpty();
        }

        public ArrayList<Argument> getArgumentList() {
            return this.argumentList;
        }

        public void addToArgumentList(Argument argument) {
            this.argumentList.add(argument);
        }

        public ObjectOfLanguage getInvokingObject() {
            return this.invokingObject;
        }

        public DirectApplication(ObjectOfLanguage invokingType, ObjectOfLanguage nameSpace) {
            super(invokingType.getName(), nameSpace);
            this.invokingObject = invokingType;
            this.argumentList = new ArrayList<>();
        }
    }

    class BlockStatement extends ObjectOfLanguage {
        private final ArrayList<ObjectOfLanguage> statmentOrDeclList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.BLOCKSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasStatementOrDeclList() {
            return !this.statmentOrDeclList.isEmpty();
        }

        public ArrayList<ObjectOfLanguage> getStatementOrDeclList() {
            return this.statmentOrDeclList;
        }

        public void addToStatementOrDeclList(ObjectOfLanguage obj) {
            this.statmentOrDeclList.add(obj);
        }

        public BlockStatement(ObjectOfLanguage nameSpace) {
            super("block_statement", nameSpace);
            this.statmentOrDeclList = new ArrayList<>();
        }
    }

    class SwitchStatement extends ObjectOfLanguage {
        private final Expression expression;
        private final ArrayList<SwitchCase> switchCases;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.SWITCHSTATEMENT;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasSwitchCases() {
            return !this.switchCases.isEmpty();
        }

        public ArrayList<SwitchCase> getSwitchCases() {
            return this.switchCases;
        }

        public void addToSwitchCases(SwitchCase switchCase) {
            this.switchCases.add(switchCase);
        }

        public Expression getExpression() {
            return this.expression;
        }

        public SwitchStatement(Expression expression, ObjectOfLanguage nameSpace) {
            super("switch", nameSpace);
            this.expression = expression;
            this.switchCases = new ArrayList<>();
        }
    }

    class SwitchCase extends ObjectOfLanguage {
        private final NonBraceExpression nonBraceExpression;
        // Switch label -> can either be DEFAULT or NonBraceExpression
        private final BlockStatement blockStatement;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.SWITCHCASE;
        }

        // Since block statements are scoped and a SwitchCase can optionally have a blockstatement
        @Override
        public boolean isScoped() {
            if(this.blockStatement == null) {
                return false;
            } else {
                return true;
            }
        }

        public boolean hasBlockStatement() {
            return this.blockStatement != null;
        }

        public BlockStatement getBlockStatement() {
            return this.blockStatement;
        }

        public boolean hasNonBraceExpression() {
            return this.nonBraceExpression != null;
        }

        public NonBraceExpression getNonBraceExpression() {
            return this.nonBraceExpression;
        }

        public SwitchCase(ObjectOfLanguage nameSpace) {
            super("default", nameSpace);
            this.blockStatement = null;
            this.nonBraceExpression = null;
        }

        public SwitchCase(BlockStatement blockStatement, ObjectOfLanguage nameSpace) {
            super("default", nameSpace);
            this.blockStatement = blockStatement;
            this.nonBraceExpression = null;
        }

        public SwitchCase(NonBraceExpression nonBraceExpression, ObjectOfLanguage nameSpace) {
            super(nonBraceExpression.getName(), nameSpace);
            this.blockStatement = null;
            this.nonBraceExpression = nonBraceExpression;
        }

        public SwitchCase(BlockStatement blockStatement, NonBraceExpression nonBraceExpression, ObjectOfLanguage nameSpace) {
            super(nonBraceExpression.getName(), nameSpace);
            this.blockStatement = blockStatement;
            this.nonBraceExpression = nonBraceExpression;
        }
    }

    class TableDeclaration extends ObjectOfLanguage {
        private final ArrayList<TableProperty> tablePropertyList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.TABLEDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public boolean hasTableProperties() {
            assert !tablePropertyList.isEmpty() : "Trying to retrieve list of table properties before parsing and adding them";
            return true;
        }

        public ArrayList<TableProperty> getTableProperties() {
            return this.tablePropertyList;
        }

        public void addToTablePropertyList(TableProperty tp) {
            this.tablePropertyList.add(tp);
        }

        public TableDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.tablePropertyList = new ArrayList<>();
        }
    }

    class TableProperty extends ObjectOfLanguage {
        private final ArrayList<KeyElement> keyElementList;
        private final ArrayList<Action> actionList;
        private final ArrayList<Entry> entriesList;
        private final Initializer initializer;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.TABLEPROPERTY;
        }

        // Four productions for tableproperty, three of which have explicit braces for scoping
        // but one has an initializer
        @Override
        boolean isScoped() {
            if(initializer == null) {
                return true;
            } else {
                return initializer.isScoped();
            }
        }

        public boolean hasKeyElementList() {
            return !this.keyElementList.isEmpty();
        }

        public boolean hasActionList() {
            return !this.actionList.isEmpty();
        }

        public boolean hasEntriesList() {
            return !this.entriesList.isEmpty();
        }

        public boolean hasInitializer() {
            return this.initializer != null;
        }

        public void addToKeyElementList(KeyElement element) {
            this.keyElementList.add(element);
        }

        public void addToActionList(Action element) {
            this.actionList.add(element);
        }

        public void addToEntriesList(Entry element) {
            this.entriesList.add(element);
        }

        public ArrayList<KeyElement> getKeyElementList() {
            return this.keyElementList;
        }

        public ArrayList<Action> getActionList() {
            return this.actionList;
        }

        public ArrayList<Entry> getEntriesList() {
            return this.entriesList;
        }

        public Initializer getInitializer() {
            return this.initializer;
        }

        public TableProperty(String start, ObjectOfLanguage nameSpace) {
            super("table_property", nameSpace);
            switch(start) {
                case "key":
                    this.keyElementList = new ArrayList<>();
                    this.actionList = null;
                    this.entriesList = null;
                    this.initializer = null;
                    break;
                case "actions":
                    this.keyElementList = null;
                    this.actionList = new ArrayList<>();
                    this.entriesList = null;
                    this.initializer = null;
                    break;
                case "entries":
                    this.keyElementList = null;
                    this.actionList = null;
                    this.entriesList = new ArrayList<>();
                    this.initializer = null;
                    break;
                default:
                    System.err.print("Please passed in a valid value for table property");
                    System.exit(1);
                    this.keyElementList = null;
                    this.actionList = null;
                    this.entriesList = null;
                    this.initializer = null;
            }
        }

        public TableProperty(ObjectOfLanguage potentialName, Initializer initializer, ObjectOfLanguage nameSpace) {
            super(potentialName.getName(), nameSpace);
            this.initializer = initializer;
            this.keyElementList = null;
            this.actionList = null;
            this.entriesList = null;
        }
    }

    class KeyElement extends ObjectOfLanguage {
        private final Expression expression;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.KEYELEMENT;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public Expression getExpression() {
            return this.expression;
        }

        public KeyElement(String name, Expression expression, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.expression = expression;
        }
    }

    class Action extends ObjectOfLanguage {
        private final ActionRef actionRef;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ACTION;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public ActionRef getActionRef() {
            return this.actionRef;
        }

        public Action(ActionRef actionRef, ObjectOfLanguage nameSpace) {
            super("action", nameSpace);
            this.actionRef = actionRef;
        }
    }

    class ActionRef extends ObjectOfLanguage {
        private final ArrayList<Argument> argumentList;
        private final boolean hasDotPrefix;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ACTIONREF;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasArgumentList() {
            return !this.argumentList.isEmpty();
        }

        public void addToArgumentList(Argument argument) {
            this.argumentList.add(argument);
        }

        public ArrayList<Argument> getArgumentList() {
            return this.argumentList;
        }

        public boolean hasDotPrefix() {
            return this.hasDotPrefix;
        }

        public ActionRef(String prefixedNonTypeName, boolean hasDotPrefix, ObjectOfLanguage nameSpace) {
            super(prefixedNonTypeName, nameSpace);
            this.hasDotPrefix = hasDotPrefix;
            this.argumentList = new ArrayList<>();
        }
    }

    class Entry extends ObjectOfLanguage {
        private final ObjectOfLanguage keySetExpression;
        private final ActionRef actionRef;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ENTRY;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public ObjectOfLanguage getKeySetExpression() {
            return this.keySetExpression;
        }

        public ActionRef getActionRef() {
            return this.actionRef;
        }

        public Entry(ObjectOfLanguage keySet, ActionRef actionRef, ObjectOfLanguage nameSpace) {
            super("entry", nameSpace);
            this.actionRef = actionRef;
            this.keySetExpression = keySet;
        }
    }

    class ActionDeclaration extends ObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.ACTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public void addParameter(Parameter parameter) {
            parameterList.add(parameter);
        }

        public ArrayList<Parameter> getParameterList() {
            return this.parameterList;
        }

        public boolean hasParameterList() {
            return !this.parameterList.isEmpty();
        }

        public ActionDeclaration(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList<>();
        }
    }

    class ConstantDeclaration extends ObjectOfLanguage {
        private final TypeRef type;
        private final Initializer initializer;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONSTANTDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return initializer.isScoped();
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public TypeRef getType() {
            return this.type;
        }

        public Initializer getInitializer() {
            return this.initializer;
        }

        public ConstantDeclaration(String name, TypeRef type, Initializer initializer, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.type = type;
            this.initializer = initializer;
        }
    }

    class FunctionDeclaration extends ObjectOfLanguage {
        private final FunctionPrototype functionPrototype;
        private final ObjectOfLanguage blockStatement;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.FUNCTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public FunctionPrototype getFunctionPrototype() {
            return this.functionPrototype;
        }

        public ObjectOfLanguage getBlockStatement() {
            return this.blockStatement;
        }

        public FunctionDeclaration(String name, ObjectOfLanguage nameSpace, FunctionPrototype functionPrototype, ObjectOfLanguage blockStatement) {
            super(name, nameSpace);
            this.functionPrototype = functionPrototype;
            this.blockStatement = blockStatement;
        }
    }

    class LValueExpression extends ObjectOfLanguage {
        private final Expression expression;
        private final Expression secondExpression;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.LVALUEEXPRESSION;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public boolean hasBitSplice() {
            return this.secondExpression != null;
        }

        public Expression getExpression() {
            return this.expression;
        }

        public Expression getSecondExpression() {
            return this.secondExpression;
        }

        public LValueExpression(LValue lvalue, Expression expression,ObjectOfLanguage nameSpace) {
            super(lvalue.getName(), nameSpace);
            this.expression = expression;
            this.secondExpression = null;
            assert !expression.isScoped();
        }

        public LValueExpression(LValue lvalue, Expression expression, Expression secondExpression, ObjectOfLanguage nameSpace) {
            super(lvalue.getName(), nameSpace);
            this.expression = expression;
            this.secondExpression = secondExpression;
            assert !expression.isScoped();
            assert !secondExpression.isScoped();
        }
    }

    class Parameter extends ObjectOfLanguage {
        private final TypeRef type;
        private final Expression assignedExpression;
        private final ConstantTreeGlobalObjects direction;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARAMETER;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        boolean hasAssignedExpression() {
            return (assignedExpression != null);
        }

        public Expression getAssignedExpression() {
            return this.assignedExpression;
        }

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
            this.direction = direction;
            this.assignedExpression = null;
        }

        public Parameter(String name, ObjectOfLanguage nameSpace, TypeRef type, ConstantTreeGlobalObjects direction, Expression assignedExpression) {
            super(name, nameSpace);
            this.type = type;
            this.assignedExpression = assignedExpression;
            this.direction = direction;
        }
    }

    class TypeRef extends ObjectOfLanguage {
        /*
        Possible types:
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
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEREF;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        boolean hasAssociatedType() {
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

        public boolean hasTypeArguments() {
            return !this.typeArgumentList.isEmpty();
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.SPECIALIZEDTYPE;
        }

        @Override
        boolean hasAssociatedType() {
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
        private final Expression expression;

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

        public Expression getExpression() {
            return this.expression;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.HEADERSTACKTYPE;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public boolean hasTypeName() {
            return this.type != null;
        }

        public boolean hasSpecializedType() {
            return this.specializedType != null;
        }

        public HeaderStackType(TypeName type, ObjectOfLanguage nameSpace, Expression expression) {
            super(type.getName(), nameSpace);
            this.type = type;
            this.specializedType = null;
            this.expression = expression;
            assert !expression.isScoped();
        }

        public HeaderStackType(SpecializedType specializedType, ObjectOfLanguage nameSpace, Expression expression) {
            super(specializedType.getType().getName(), nameSpace);
            this.specializedType = specializedType;
            this.type = null;
            this.expression = expression;
            assert !expression.isScoped();
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
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TUPLETYPE;
        }

        public TupleType(ObjectOfLanguage nameSpace) {
            super(nameSpace);
            this.typeArgumentList = new ArrayList<>();
        }
    }

    // Merged PrefixedType with TypeName as it is the only place where it is used
    class TypeName extends ObjectOfLanguage {
        private final ObjectOfLanguage type;
        private final boolean hasDotPrefix;

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TYPENAME;
        }

        @Override
        boolean hasAssociatedType() {
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
        private final TypeName typeName;
        private final SpecializedType specializedType;

        public ObjectOfLanguage getType() {
            if(this.typeName != null) {
                return this.typeName;
            } else {
                assert this.specializedType != null : "Unexpected error in NamedType";
                return this.specializedType;
            }
        }

        public Class getTypeClass() {
            return type.getClass();
        }

        public boolean isTypeName() {
            return this.typeName != null;
        }

        public boolean isSpecializedType() {
            return this.specializedType != null;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.NAMEDTYPE;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public NamedType (TypeName typeName, ObjectOfLanguage nameSpace) {
            super(typeName.getName(), nameSpace);
            this.typeName = typeName;
            this.specializedType = null;
        }

        public NamedType (SpecializedType specializedType, ObjectOfLanguage nameSpace) {
            super(specializedType.getName(), nameSpace);
            this.typeName = null;
            this.specializedType = specializedType;
        }
    }

    class MethodPrototype extends ObjectOfLanguage {
        private final boolean isAbstract;
        private FunctionPrototype functionPrototype;

        public boolean isAbstract() {
            return this.isAbstract;
        }

        public FunctionPrototype getFunctionPrototype() {
            return this.functionPrototype;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.METHODPROTOTYPE;
        }

        public MethodPrototype(FunctionPrototype functionPrototype, ObjectOfLanguage nameSpace, boolean isAbstract) {
            super(functionPrototype.getName(), nameSpace);
            this.functionPrototype = functionPrototype;
            this.isAbstract = isAbstract;
        }
    }

    class ConstructorMethodPrototype extends ObjectOfLanguage {
        private final ObjectOfLanguage typeIdentifier;
        private final ArrayList<Parameter> parameterList;

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.CONSTRUCTORMETHODPROTOTYPE;
        }

        public void addParameter(Parameter parameter) {
            parameterList.add(parameter);
        }

        public ArrayList<Parameter> getParameterList() {
            return this.parameterList;
        }

        public boolean hasParameterList() {
            return !this.parameterList.isEmpty();
        }

        ObjectOfLanguage getTypeIdentifier() {
            return this.typeIdentifier;
        }

        public ConstructorMethodPrototype(ObjectOfLanguage typeIdentifier, ObjectOfLanguage nameSpace) {
            super(typeIdentifier.getName(), nameSpace);
            this.typeIdentifier = typeIdentifier;
            parameterList = new ArrayList<>();
        }
    }

    class TypeArgument extends ObjectOfLanguage {
        // Can be of class TypeRef, NonTypename, or BaseTypes
        private final ObjectOfLanguage type;

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEARGUMENT;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public ObjectOfLanguage getType() {
            return this.type;
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
        private final boolean isScoped;

        public boolean isInvokingExpression() {
            return invokingExpression != null;
        }

        // What about expressions with L_BRACE?
        @Override
        boolean isScoped() {
            return this.isScoped;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXPRESSION;
        }

        public Expression(String name, ObjectOfLanguage nameSpace, boolean isScoped) {
            super(name, nameSpace);
            this.invokingExpression = null;
            this.isScoped = isScoped;
        }

        public Expression(InvokingExpression invokingExpression, ObjectOfLanguage nameSpace) {
            super(invokingExpression.getName(), nameSpace);
            this.invokingExpression = invokingExpression;
            this.isScoped = false;
        }
    }

    class InvokingExpression extends ObjectOfLanguage {
        private final ArrayList<Argument> argumentList;
        private final ArrayList<RealTypeArgument> realTypeArgumentList;
        private final Expression expression;
        private final NamedType namedType;
        private final TypeRef typeRef;

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.INVOKINGEXPRESSION;
        }

        @Override
        boolean hasAssociatedType() {
            return typeRef != null;
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

    class NonBraceExpression extends ObjectOfLanguage {
        /*
        Terminal (Integer, string literal, true, false, this)
        nonTypeName (w/ dotPrefix)
        kvList
        typeName (w/ dot_name)
        ERROR DOT name

        Assuming that the parser will find the terminal and pass a string to this constructor
        */

        private final InvokingNonBraceExpression invokingNonBraceExpression;
        private final boolean isScoped;

        public boolean isInvokingNonBraceExpression() {
            return invokingNonBraceExpression != null;
        }

        @Override
        public boolean isScoped() {
            return this.isScoped;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.NONBRACEEXPRESSION;
        }

        public NonBraceExpression(String name, ObjectOfLanguage nameSpace, boolean isScoped) {
            super(name, nameSpace);
            this.invokingNonBraceExpression = null;
            this.isScoped = isScoped;
        }

        public NonBraceExpression(InvokingNonBraceExpression invokingNonBraceExpression, ObjectOfLanguage nameSpace) {
            super(invokingNonBraceExpression.getName(), nameSpace);
            this.invokingNonBraceExpression = invokingNonBraceExpression;
            this.isScoped = false;
        }
    }

    class InvokingNonBraceExpression extends ObjectOfLanguage {
        private final ArrayList<Argument> argumentList;
        private final ArrayList<RealTypeArgument> realTypeArgumentList;
        private final NonBraceExpression nonBraceexpression;
        private final NamedType namedType;
        private final TypeRef typeRef;

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.INVOKINGNONBRACEEXPRESSION;
        }

        @Override
        boolean hasAssociatedType() {
            return typeRef != null;
        }

        public ArrayList<Argument> getArgumentList() {
            assert this.argumentList != null;

            return this.argumentList;
        }

        public ArrayList<RealTypeArgument> getRealTypeArgumentList() {
            assert this.realTypeArgumentList != null;

            return this.realTypeArgumentList;
        }

        public NonBraceExpression getExpression() {
            assert this.nonBraceexpression != null;

            return this.nonBraceexpression;
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

        public InvokingNonBraceExpression(NonBraceExpression expression, ObjectOfLanguage nameSpace) {
            super(expression.getName(), nameSpace);
            this.nonBraceexpression = expression;
            this.realTypeArgumentList = new ArrayList<>();
            this.argumentList = new ArrayList<>();
            this.namedType = null;
            this.typeRef = null;
        }

        public InvokingNonBraceExpression(NamedType namedType, ObjectOfLanguage nameSpace) {
            super(namedType.getName(), nameSpace);
            this.nonBraceexpression = null;
            this.realTypeArgumentList = null;
            this.argumentList = new ArrayList<>();
            this.namedType = namedType;
            this.typeRef = null;
        }

        public InvokingNonBraceExpression(TypeRef typeRef, NonBraceExpression expression, ObjectOfLanguage nameSpace) {
            super(typeRef.getName(), nameSpace);
            this.nonBraceexpression = expression;
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
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.REALTYPEARGUMENT;
        }

        public boolean hasAssociatedType() {
            return true;
        }

        public ObjectOfLanguage getType() {
            if(this.void_or_dontcare != null) {
                assert this.typeRef == null;

                return this.void_or_dontcare;
            } else {
                assert this.void_or_dontcare == null;

                return this.typeRef;
            }
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

        // since argument can be an expression and an expression can be scoped
        @Override
        public boolean isScoped() {
            if(dontcare != null) {
                return false;
            } else {
                return expression.isScoped();
            }
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.ARGUMENT;
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
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.NAME;
        }

        public ObjectOfLanguage getNameObject() {
            return this.name;
        }

        public Name(ObjectOfLanguage name, ObjectOfLanguage scope) {
            super(name.getName(), scope);
            this.name = name;
        }
    }

    class OLangString extends ObjectOfLanguage {
        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.STRING;
        }

        public OLangString(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class OLangInteger extends ObjectOfLanguage {
        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.INTEGER;
        }

        public OLangInteger(String name, ObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class VariableDeclaration extends ObjectOfLanguage {
        private ArrayList<Annotation> annotations;
        private TypeRef type;
        private OptInitializer optInitializer;

        boolean hasOptInitializer() {
            return optInitializer != null;
        }

        OptInitializer getOptInitializer() {
            return this.optInitializer;
        }

        TypeRef getType() {
            return this.type;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.VARIABLEDECLARATION;
        }

        boolean hasAnnotations() {
            return !this.annotations.isEmpty();
        }

        ArrayList<Annotation> getAnnotations() {
            return this.annotations;
        }

        public VariableDeclaration(String name, ObjectOfLanguage nameSpace, TypeRef type) {
            super(name, nameSpace);
            this.type = type;
            this.annotations = new ArrayList();
            this.optInitializer = null;
        }

        public VariableDeclaration(String name, ObjectOfLanguage nameSpace, TypeRef type, OptInitializer optInitializer) {
            super(name, nameSpace);
            this.type = type;
            this.annotations = new ArrayList();
            this.optInitializer = optInitializer;
        }
    }

    class Annotation extends ObjectOfLanguage {
        private final StructuredAnnotationBody structuredAnnotationBody;
        private final AnnotationBody annotationBody;

        public boolean hasAnnotationBody() {
            return annotationBody != null;
        }

        public boolean hasStructuredAnnotationBody() {
            return structuredAnnotationBody != null;
        }

        public StructuredAnnotationBody getStructuredAnnotationBody() {
            return this.structuredAnnotationBody;
        }

        public AnnotationBody getAnnotationBody() {
            return this.annotationBody;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.ANNOTATION;
        }

        public Annotation(String name, ObjectOfLanguage nameSpace, AnnotationBody annotationBody) {
            super(name, nameSpace);
            this.annotationBody = annotationBody;
            this.structuredAnnotationBody = null;
        }

        public Annotation(String name, ObjectOfLanguage nameSpace, StructuredAnnotationBody structuredAnnotationBody) {
            super(name, nameSpace);
            this.annotationBody = null;
            this.structuredAnnotationBody = structuredAnnotationBody;
        }
    }
    
    class StructuredAnnotationBody extends ObjectOfLanguage {
        private final ArrayList<Expression> expressionList;
        private final ArrayList<KVPair> kvList;

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.STRUCTUREDANNOTATIONBODY;
        }

        public boolean isExpressionList() {
            return this.expressionList != null;
        }

        public boolean isKVList() {
            return this.kvList != null;
        }

        public ArrayList<Expression> getExpressionList() {
            return this.expressionList;
        }

        public ArrayList<KVPair> getKVList() {
            return this.kvList;
        }

        public void addToExpressionList(Expression expression) {
            this.expressionList.add(expression);
        }

        public boolean hasExpressionList() {
            return ! this.expressionList.isEmpty();
        }

        public boolean hasKVList() {
            return ! this.kvList.isEmpty();
        }

        public void addToKVList(KVPair kPair) {
            this.kvList.add(kPair);
        }

        public StructuredAnnotationBody(ObjectOfLanguage nameSpace, boolean isExpressionList) {
            super(nameSpace);
            if(isExpressionList) {
                this.expressionList = new ArrayList<>();
                this.kvList = null;
            } else {
                this.kvList = new ArrayList<>();
                this.expressionList = null;
            }
        }
    }

    class AnnotationBody extends ObjectOfLanguage {
        private AnnotationBody annotationBody;
        private String annotationToken;

        AnnotationBody getNestedAnnotationBody() {
            return this.annotationBody;
        }

        boolean hasToken() {
            return annotationToken != null;
        }

        String getToken() {
            return this.annotationToken;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.ANNOTATIONBODY;
        }

        public AnnotationBody(ObjectOfLanguage nameSpace, AnnotationBody annotationBody) {
            super(nameSpace);
            this.annotationBody = annotationBody;
            this.annotationToken = null;
        }

        public AnnotationBody(ObjectOfLanguage nameSpace, AnnotationBody annotationBody, String annotationToken) {
            super(nameSpace);
            this.annotationBody = annotationBody;
            this.annotationToken = annotationToken;
        }
    }

    class KVPair extends ObjectOfLanguage {
        private Expression expression;

        Expression getExpression() {
            return this.expression;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.KVPAIR;
        }

        KVPair(String name, ObjectOfLanguage nameSpace, Expression expression) {
            super(name, nameSpace);
            this.expression = expression;
        }
    }
    
    class OptInitializer extends ObjectOfLanguage {
        private final Initializer initializer;

        @Override
        public boolean isScoped() {
            return initializer.isScoped();
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.OPTINITIALIZER;
        }

        public Initializer getInitializer() {
            return this.initializer;
        }

        public OptInitializer(Initializer initializer, ObjectOfLanguage nameSpace) {
            super(initializer.getName(), nameSpace);
            this.initializer = initializer;
        }
    }

    class Initializer extends ObjectOfLanguage {
        Expression expression;

        @Override
        public boolean isScoped() {
            return expression.isScoped();
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.OPTINITIALIZER;
        }

        public Initializer(Expression expression, ObjectOfLanguage nameSpace) {
            super(expression.getName(), nameSpace);
            this.expression = expression;
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