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
class P4LanguageObject {
    // conditioned callees
    enum LObjectKind {
        CONSTANTVALUE,
        HEADERTYPEDECLARATION,
        HEADERUNIONDECLARATION,
        HEADERSTACKTYPE,
        TUPLETYPE,
        STRUCTTYPEDECLARATION,
        ENUMDECLARATION,
        TYPEDEFDECLARATION,
        PARSERTYPEDECLARATION,
        PACKAGETYPEDECLARATION,
        EXTERNDECLARATION,
        EXTERNFUNCTIONDECLARATION,
        PARAMETER,
        CONTROLBLOCK,
        TYPEORVOID,
        TYPEPARAMETER,
        STRUCTFIELD,
        STRING,
        DEFAULT
    }

    abstract class AbstractObjectOfLanguage {
        private final String name;
        private final AbstractObjectOfLanguage nameSpace;
        abstract boolean isScoped();
        // not making this private to avoid allocating memory since it is not present most times
        private ArrayList<Parameter> optConstructorParameters = null;
        // private ArrayList<Annotation> optAnnotations = null;
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

        // public boolean hasOptAnnotations() {
        //     return optAnnotations != null;
        // }

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

        public AbstractObjectOfLanguage getNameSpace() {
            return this.nameSpace;
        }

        public String getNameSpaceString(AbstractObjectOfLanguage global_scope) {
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

        // public void addToOptAnnotations(Annotation annotation) {
        //     if (optAnnotations == null) {
        //         this.optAnnotations = new ArrayList<>();
        //     }

        //     this.optAnnotations.add(annotation);
        // }

        public AbstractObjectOfLanguage(String name, AbstractObjectOfLanguage nameSpace) {
            this.name = name;
            this.nameSpace = nameSpace;
        }

        public AbstractObjectOfLanguage(AbstractObjectOfLanguage nameSpace) {
            this.name = null;
            this.nameSpace = nameSpace;
        }

        public String toString(AbstractObjectOfLanguage global_scope) {
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
        public String toStringExtensive(Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab, HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject) {
            String finalString = name + ": ";

            Iterator<String> itr = symtab.get(this).keySet().iterator();

            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                AbstractObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += childLangObj.toString();
                if(symtab.containsKey(childLangObj)) {
                    finalString += itr.hasNext() ? ", " : "";
                    continue;
                }

                ArrayList<String> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(AbstractObjectOfLanguage callee : callGraphObject.get(childLangObj)) {
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

        public String toDotString(Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab, HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject) {
            String finalString = "";

            Iterator<String> itr = symtab.get(this).keySet().iterator();
            finalString += this.hashCode() + ";";
            finalString += this.hashCode() + " [label=\"" + this.name + "\"];";
            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                AbstractObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += this.hashCode() + " -> " + childLangObj.hashCode() + " [style=dashed, color=blue];";
                finalString += childLangObj.hashCode() + " [label=\"" + childLangObj.name + "\"];";

                if(symtab.containsKey(childLangObj)) {
                    continue;
                }

                ArrayList<AbstractObjectOfLanguage> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(AbstractObjectOfLanguage callee : callGraphObject.get(childLangObj)) {
                        calleeNames.add(callee);
                    }
                }

                if(! calleeNames.isEmpty()) {
                    for(AbstractObjectOfLanguage localCallee : calleeNames) {
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
        public boolean equals(Object object, AbstractObjectOfLanguage global_scope) {
            if(this == object) {
                return true;    
            }
            if(object == null) {
                return false;
            }
            if (object instanceof AbstractObjectOfLanguage == false) {
                return false;
            }

            AbstractObjectOfLanguage compObject = (AbstractObjectOfLanguage) object;

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
        public int hashCode(AbstractObjectOfLanguage global_scope) {
            String hashString = "";
            if(this.nameSpace != null) {
                // not the GLOBAL AbstractObjectOfLanguage
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
        public String getParentNameSpaces(AbstractObjectOfLanguage global_scope) {
            String ancestorNameSpace = "";
            AbstractObjectOfLanguage currentNameSpace = this.nameSpace;
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

    class LanguageObject extends AbstractObjectOfLanguage {
        private final boolean isScoped;
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.DEFAULT;
        }

        @Override
        public boolean isScoped() {
            return isScoped;
        }

        public LanguageObject(String name, AbstractObjectOfLanguage nameSpace, boolean isScoped) {
            super(name, nameSpace);
            this.isScoped = isScoped;
        }

        public LanguageObject(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.isScoped = false;
        }
    }

    /**
     * Class used to declare global constant language objects like global scope.
     */
    class ConstantTreeGlobalObjects extends AbstractObjectOfLanguage {
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
        public AbstractObjectOfLanguage getNameSpace() {
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

    class HeaderTypeDeclaration extends AbstractObjectOfLanguage {
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

        HeaderTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    class HeaderUnionDeclaration extends AbstractObjectOfLanguage {
        private final ArrayList<StructField> structFieldList;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.HEADERUNIONDECLARATION;
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

        HeaderUnionDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    // HeaderStack is used to initialize an array of headers
    // If A is of header type, A[5] a_array -> header stack
    //          initializes a_array with 5 entries of type A
    class HeaderStackType extends AbstractObjectOfLanguage {
        private final AbstractObjectOfLanguage type;
        private final ArrayList<String> typeArgumentList;

        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        // public SpecializedType getSpecializedType() {
        //     return this.specializedType;
        // }

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

        public boolean hasArgumentsList() {
            return !this.typeArgumentList.isEmpty();
        }

        public ArrayList<String> getTypeArgumentsList() {
            return this.typeArgumentList;
        }

        public void addToTypeArgumentsList(String type) {
            this.typeArgumentList.add(type);
        }

        public HeaderStackType(AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type) {
            super(nameSpace);
            this.type = type;
            this.typeArgumentList = new ArrayList<>();
        }
    }

    class TupleType extends AbstractObjectOfLanguage {
        private final ArrayList<String> typeArgumentList;

        public boolean hasArgumentsList() {
            return !this.typeArgumentList.isEmpty();
        }

        public ArrayList<String> getTypeArgumentsList() {
            return this.typeArgumentList;
        }

        public void addToTypeArgumentsList(String type) {
            this.typeArgumentList.add(type);
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TUPLETYPE;
        }

        public TupleType(AbstractObjectOfLanguage nameSpace) {
            super(nameSpace);
            this.typeArgumentList = new ArrayList<>();
        }
    }

    class StructTypeDeclaration extends AbstractObjectOfLanguage {
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

        StructTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.structFieldList = new ArrayList<>();
        }
    }

    class EnumDeclaration extends AbstractObjectOfLanguage {
        // normal enums and serializable enums that have an associated type
        private final AbstractObjectOfLanguage type;
        private final ArrayList<AbstractObjectOfLanguage> identifierList;
        // private final ArrayList<SpecifiedIdentifier> specifiedIdentifierList;

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

        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        public boolean hasIdentifiersList() {
            return (this.identifierList != null && 
                    !this.identifierList.isEmpty());
        }

        // public boolean hasSpecifiedIdentifiersList() {
        //     return (this.specifiedIdentifierList != null 
        //             && !this.specifiedIdentifierList.isEmpty());
        // }

        public void addToIdentifierList(AbstractObjectOfLanguage identifier) {
            this.identifierList.add(identifier);
        }

        // public void addToSpecifiedIdentifierList(SpecifiedIdentifier identifier) {
        //     this.specifiedIdentifierList.add(identifier);
        // }

        public ArrayList<AbstractObjectOfLanguage> getIdentifierList() {
            return this.identifierList;
        }

        // public ArrayList<SpecifiedIdentifier> getSpecifiedIdentifierList() {
        //     return this.specifiedIdentifierList;
        // }

        public EnumDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.type = null;
            this.identifierList = new ArrayList<>();
            // this.specifiedIdentifierList = null;
        }

        public EnumDeclaration(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type) {
            super(name, nameSpace);
            this.type = type;
            // this.specifiedIdentifierList = new ArrayList<>();
            this.identifierList = new ArrayList<>();
        }
    }

    class TypeDefDeclaration extends AbstractObjectOfLanguage {
        // typdef vs type -> difference is made in parsing context where both values
        // are stored in symtab for TYPEDEF while only newly declared variable name is stored
        // in symtab for TYPE
        private final AbstractObjectOfLanguage type;
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
            return type.isScoped();
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        public boolean isTypeDef() {
            return this.isTypeDef;
        }

        public TypeDefDeclaration(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, Boolean typeDef) {
            super(name, nameSpace);
            this.type = type;
            this.isTypeDef = typeDef;
        }
    }

    class ParserTypeDeclaration extends AbstractObjectOfLanguage {
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

        public ParserTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList();
        }
    }

    class PackageTypeDeclaration extends AbstractObjectOfLanguage {
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

        public PackageTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList();
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
    class ExternDeclaration extends AbstractObjectOfLanguage {
        // method prototypes can occur only inside the first production of extern declaration
        // private final ArrayList<MethodPrototype> methodPrototypes;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNDECLARATION;
        }

        // technically scoped for "optAnnotations EXTERN name SEMICOLON" production as well
        @Override
        public boolean isScoped() {
            return true;
        }

        public ExternDeclaration(String name, AbstractObjectOfLanguage scope) {
            super(name, scope);
            // methodPrototypes = new ArrayList<>();
        }

        // public ArrayList<MethodPrototype> getMethodPrototypes() {
        //     return this.methodPrototypes;
        // }

        // public void addMethodPrototype(MethodPrototype newMethodPrototype) {
        //     this.methodPrototypes.add(newMethodPrototype);
        // }

        // public boolean hasMethodPrototypes() {
        //     return !this.methodPrototypes.isEmpty();
        // }
    }

    // combines function prototype
    class ExternFunctionDeclaration extends AbstractObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;
        private final TypeOrVoid typeOrVoid;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNFUNCTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public ArrayList<Parameter> getParameters() {
            return this.parameterList;
        }

        TypeOrVoid getReturnType() {
            return this.typeOrVoid;
        }

        public void addToParameters(Parameter parameter) {
            this.parameterList.add(parameter);
        }

        public ExternFunctionDeclaration(String name, AbstractObjectOfLanguage nameSpace, TypeOrVoid typeOrVoid){
            super(name, nameSpace);
            this.parameterList = new ArrayList<>();
            this.typeOrVoid = typeOrVoid;
        }
    }

    // combines control type declaration
    class ControlDeclaration extends AbstractObjectOfLanguage {
        private final ArrayList<Parameter> parameterList;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONTROLBLOCK;
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

        public ControlDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
            this.parameterList = new ArrayList<>();
        }
    }

    // Support Classes

    class TypeOrVoid extends AbstractObjectOfLanguage {
        private AbstractObjectOfLanguage typeRef;
        private ConstantTreeGlobalObjects voidVar;
        private AbstractObjectOfLanguage identifier;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEORVOID;
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

        TypeOrVoid(AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage typeRef, boolean isTypeRef) {
            super(typeRef.getName(), nameSpace);
            if(isTypeRef) {
                this.typeRef = typeRef;
                this.identifier = null;
            } else {
                this.identifier = typeRef;
                this.typeRef = null;
            }
            this.identifier = null;
            this.voidVar = null;
        }

        TypeOrVoid(ConstantTreeGlobalObjects voidVar, AbstractObjectOfLanguage nameSpace) {
            super(voidVar.getName(), nameSpace);
            this.identifier = null;
            this.typeRef = null;
            this.voidVar = voidVar;
        }
    }

    class Parameter extends AbstractObjectOfLanguage {
        private final AbstractObjectOfLanguage type;
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

        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        public ConstantTreeGlobalObjects getDirection() {
            return this.direction;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type and direction object
        // and will pass it to us
        public Parameter(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, ConstantTreeGlobalObjects direction) {
            super(name, nameSpace);
            this.type = type;
            this.direction = direction;
            this.assignedExpression = null;
        }

        public Parameter(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, ConstantTreeGlobalObjects direction, Expression assignedExpression) {
            super(name, nameSpace);
            this.type = type;
            this.assignedExpression = assignedExpression;
            this.direction = direction;
        }
    }

    class TypeParameter extends AbstractObjectOfLanguage {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TYPEPARAMETER;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        TypeParameter(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class StructField extends AbstractObjectOfLanguage {
        private final AbstractObjectOfLanguage type;
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

        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        public StructField(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage typeRef) {
            super(name, nameSpace);
            this.type = typeRef;
        }
    }

    class OLangString extends AbstractObjectOfLanguage {
        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.STRING;
        }

        public OLangString(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    public class BaseTypes {
        private ArrayList<String> baseTypes;
        private Map<String, AbstractObjectOfLanguage> baseTypeObjects;
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

        public AbstractObjectOfLanguage getLanguageObjectOfBaseType(String type) {
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
        private Map<String, AbstractObjectOfLanguage> directionTypeObjects;

        {
            directions = new ArrayList<>();
            directions.add("in");
            directions.add("out");
            directions.add("inout");


            for(String type : directions) {
                directionTypeObjects.put(type, new ConstantTreeGlobalObjects(type));
            }
        }

        public AbstractObjectOfLanguage getLanguageObjectOfDirection(String type) {
            assert directions.contains(type);

            return directionTypeObjects.get(type);
        }
    }
}