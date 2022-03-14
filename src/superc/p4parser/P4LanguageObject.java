package superc.p4parser;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;


// For symbols
class P4LanguageObject {
    // Boolean flags to turn on and off features
    boolean OUTPUT_TYPES = true;

    // conditioned callees
    enum LObjectKind {
        CONSTANTVALUE,
        HEADERTYPEDECLARATION,
        HEADERUNIONDECLARATION,
        STRUCTTYPEDECLARATION,
        ENUMDECLARATION,
        TYPEDEFDECLARATION,
        PARSERTYPEDECLARATION,
        PARSERTYPEDECLARATIONGENERATOR,
        PACKAGETYPEDECLARATION,
        PACKAGETYPEDECLARATIONGENERATOR,
        EXTERNDECLARATION,
        EXTERNDECLARATIONGENERATOR,
        EXTERNFUNCTIONDECLARATION,
        PARAMETER,
        CONTROLTYPEDECLARATION,
        TYPEORVOID,
        TYPEPARAMETER,
        STRUCTFIELD,
        STRING,
        DEFAULT,
        FUNCTIONPROTOTYPE,
        FUNCTIONPROTOTYPEGENERATOR,
        CONTROLDECLARATION,
        PARSERDECLARATION,
        PARSERDECLARATIONGENERATOR,
        TABLEDECLARATION,
        INVOKABLEKEYWORD,
        BUILTINFUNCTION,
        VARIABLE,
        BASETYPE,
        FUNCTION,
        METHOD,
        TUPLETYPE,
        SPECIALIZEDTYPE,
        HEADERSTACKTYPE,
        ANONYMOUS,
        SUBCLASS,
        FUNCTIONDECLARATION
    }

    // TODO handle constructor method prototype parameters & action declarations

    abstract class AbstractObjectOfLanguage {
        private final String name;
        private final AbstractObjectOfLanguage nameSpace;
        abstract boolean isScoped();
        // not making this private to avoid allocating memory since it is not present most times
        private ArrayList<Parameter> optConstructorParameters = null;
        // private ArrayList<Annotation> optAnnotations = null;
        private ArrayList<Parameter> parameters;
        
        // abstract method to return respective enum
        abstract LObjectKind getConstructType();

        abstract boolean isGeneratorClass();

        boolean hasAssociatedType() {
            return false;
        }

        public boolean hasParameters() {
            return ! this.parameters.isEmpty();
        }

        public void addParameter(Parameter parameter) {
            this.parameters.add(parameter);
        }

        public ArrayList<Parameter> getParameters() {
            return this.parameters;
        }

        AbstractObjectOfLanguage getType() {
            // System.err.println("No associated type found for: \"" + name + "\"");
            // System.exit(1);
            assert false : "No associated type found for: \"" + name + "\"";
            return null;
        }

        public String getName() {
            return this.getName(false);
        }

        public String getName(boolean output_types) {
            if(this.name == null) {
                System.err.println(this.getConstructType().toString() + " construct does not have a name associated with it.");
            }

            if(output_types) {
                if(this.hasAssociatedType() &&
                   this.getConstructType() != LObjectKind.FUNCTIONPROTOTYPE &&
                   this.getConstructType() != LObjectKind.ENUMDECLARATION &&
                   this.getConstructType() != LObjectKind.STRUCTTYPEDECLARATION
                   ) {
                    return this.name +  "(" + this.getType().getConstructType() + ")";    
                } else {
                    return this.name +  "(" + this.getConstructType() + ")";
                }
            } else {
                return this.name;
            }
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

        void addParsedOptTypeParameters(AbstractObjectOfLanguage typeParameter) {
            System.err.println("This object does not passed in values for generic parameters.");
            System.exit(1);
        }

        boolean hasParsedOptTypeParameters() {
            return false;
        }

        ArrayList<AbstractObjectOfLanguage> getParsedOptTypeParameters() {
            System.err.println("Cannot obtain parsed type parameters for this object (" + this.name + ")");
            System.exit(1);
            return null;
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
            this.parameters = new ArrayList<>();
        }

        public AbstractObjectOfLanguage(AbstractObjectOfLanguage nameSpace) {
            this(null, nameSpace);
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
        public String toStringExtensive(Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab, HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject, AbstractObjectOfLanguage global_scope) {
            String finalString = name + ": ";

            Iterator<String> itr = symtab.get(this).keySet().iterator();

            ArrayList<String> parentCalleeNames = new ArrayList<>();
            if(callGraphObject.containsKey(this)) {
                for(AbstractObjectOfLanguage callee : callGraphObject.get(this)) {
                    parentCalleeNames.add(callee.getName(OUTPUT_TYPES) + "(" + callee.getNameSpace().getName(OUTPUT_TYPES) + ")");
                }
            }

            if(! parentCalleeNames.isEmpty()) {
                for(int i = 0; i < parentCalleeNames.size(); i++) {
                    finalString += parentCalleeNames.get(i) + (i == parentCalleeNames.size() - 1 ? "" : ", ");
                }
            }
            
            finalString += (itr.hasNext() && !parentCalleeNames.isEmpty() ? ", " : "");

            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                AbstractObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += childLangObj.getName(OUTPUT_TYPES);
                if(symtab.containsKey(childLangObj)) {
                    finalString += itr.hasNext() ? ", " : "";
                    continue;
                }
                // System.out.println("debug: " + childLangObj.getName() + " with parent: " + childLangObj.getParentNameSpaces(global_scope));

                ArrayList<String> calleeNames = new ArrayList<>();
                if(callGraphObject.containsKey(childLangObj)) {
                    for(AbstractObjectOfLanguage callee : callGraphObject.get(childLangObj)) {
                        calleeNames.add(callee.getName(OUTPUT_TYPES));
                    }
                }

                if(! calleeNames.isEmpty()) {
                    finalString += ": " + calleeNames.toString();
                }
                finalString += (itr.hasNext() ? ", " : "");
            }

            return finalString;
        }

        public String toDotString(Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab, HashMap<AbstractObjectOfLanguage, HashSet<AbstractObjectOfLanguage>> callGraphObject, AbstractObjectOfLanguage global_scope) {
            String finalString = "";

            Iterator<String> itr = symtab.get(this).keySet().iterator();
            finalString += this.hashCode(global_scope) + ";";
            finalString += this.hashCode(global_scope) + " [label=\"" + this.getName(OUTPUT_TYPES) + "\"];";
            ArrayList<AbstractObjectOfLanguage> parentCalleeNames = new ArrayList<>();
            if(callGraphObject.containsKey(this)) {
                for(AbstractObjectOfLanguage callee : callGraphObject.get(this)) {
                    parentCalleeNames.add(callee);
                }
            }

            if(! parentCalleeNames.isEmpty()) {
                for(AbstractObjectOfLanguage localCallee : parentCalleeNames) {
                    finalString += this.hashCode(global_scope) + "->" + localCallee.hashCode(global_scope) + ";";
                    finalString += localCallee.hashCode(global_scope) + " [label=\"" + localCallee.getName(OUTPUT_TYPES) + "\"];";
                }
            }

            while(itr.hasNext()) {
                String childKey = (String) itr.next();
                AbstractObjectOfLanguage childLangObj = symtab.get(this).get(childKey);
                finalString += this.hashCode(global_scope) + " -> " + childLangObj.hashCode(global_scope) + " [style=dashed, color=blue];";
                finalString += childLangObj.hashCode(global_scope) + " [label=\"" + childLangObj.getName(OUTPUT_TYPES) + "\"];";

                // If it is a subclass, put it under the parent class in graph
                if(childLangObj.getConstructType() == LObjectKind.SUBCLASS) {
                    finalString += ((SubClass) childLangObj).getOriginalClass().hashCode(global_scope) + "->" + childLangObj.hashCode(global_scope) + "[color=red]";
                    finalString += childLangObj.hashCode(global_scope) + " [style=filled, fillcolor=bisque];";
                }

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
                        finalString += childLangObj.hashCode(global_scope) + "->" + localCallee.hashCode(global_scope) + ";";
                        finalString += localCallee.hashCode(global_scope) + " [label=\"" + localCallee.name + "\"];";
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

    abstract class Generator extends AbstractObjectOfLanguage {
        private RegularLanguageObject originalRegularObject;
        private ArrayList<TypeParameter> optTypeParameters;

        void addOptTypeParameters(TypeParameter typeParameter) {
            this.optTypeParameters.add(typeParameter);
        }

        boolean hasOptTypeParameters() {
            return !this.optTypeParameters.isEmpty();
        }

        ArrayList<TypeParameter> getOptTypeParameters() {
            return this.optTypeParameters;
        }

        @Override
        public boolean isGeneratorClass() {
            return true;
        }

        @Override
        public boolean isScoped() {
            return originalRegularObject.isScoped();
        }

        public RegularLanguageObject getRegularLanguageObject() {
            return this.originalRegularObject;
        }

        public AbstractObjectOfLanguage generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters,
                                                        ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                        Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                        Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
            return this.generateInstance(parsedTypeParameters, parsedParameters, this.getOptTypeParameters(), valuesUnderScope, symtab);
        }

        // type mappings are introduced for cases one generator function calls a child generator construct's generateInstance function and passes in
        // in its own (parent) parsedTypeParameters and parsedParameters to the child generator construct. So in those cases those values
        // are passed to the parent's generic types and not the child's. Hence to differentiate it we pass in typeMappings
        // example is ExternDeclarationGenerator potentially calling a child functionPrototype's generator function

        abstract public AbstractObjectOfLanguage generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                               ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                               ArrayList<TypeParameter> typeMappings,
                                                               Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                               Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab);

        public Generator(RegularLanguageObject regularLanguageObject) {
            super(regularLanguageObject.getName(), regularLanguageObject.getNameSpace());
            assert regularLanguageObject.hasName() : "Anonymous class types not allowed for generators";

            this.originalRegularObject = regularLanguageObject;
            this.optTypeParameters = new ArrayList<>();
        }
    }

    abstract class RegularLanguageObject extends AbstractObjectOfLanguage {
        @Override
        public boolean isGeneratorClass() {
            return false;
        }

        public RegularLanguageObject(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }

        public RegularLanguageObject(AbstractObjectOfLanguage nameSpace) {
            super(nameSpace);
        }
    }

    // Generator classes

    class PackageTypeDeclarationGenerator extends Generator {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PACKAGETYPEDECLARATIONGENERATOR;
        }

        public PackageTypeDeclarationGenerator(PackageTypeDeclaration packageTypeDeclaration) {
            super(packageTypeDeclaration);
        }

        @Override
        public PackageTypeDeclaration generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                      ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                      ArrayList<TypeParameter> typeMappings,
                                                      Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                      Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
            PackageTypeDeclaration newInstance = new PackageTypeDeclaration(this.getName(), this.getNameSpace());
            if(! parsedTypeParameters.isEmpty()) {
                assert this.hasParameters() : "Assuming that if package type declaration has type parameters, then there are regular parameters passed in with generic types";
                assert ! parsedParameters.isEmpty();
            }

            assert this.getParameters().size() == parsedParameters.size();
            
            ArrayList<Parameter> originalParameters = this.getParameters();
            for(int i = 0; i < this.getParameters().size(); i++) {
                Parameter currentParam = originalParameters.get(i);
                if(currentParam.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                    assert this.getOptTypeParameters().contains(currentParam.getType());

                    int typeIndex = this.getOptTypeParameters().indexOf(currentParam.getType());
                    AbstractObjectOfLanguage type = parsedTypeParameters.get(typeIndex);
                    Parameter newParam = new Parameter(currentParam.getName(), newInstance, type, currentParam.getDirection(), currentParam.getAssignedExpression());
                    newInstance.addParameter(newParam);
                    addToSymtab(newInstance, newParam.getName(), newParam, symtab);
                } else {
                    Parameter newParam = new Parameter(currentParam.getName(), newInstance, currentParam.getType(), currentParam.getDirection(), currentParam.getAssignedExpression());
                    newInstance.addParameter(newParam);
                    addToSymtab(newInstance, newParam.getName(), newParam, symtab);
                }
            }

            return newInstance;
        }
    }

    class ParserTypeDeclarationGenerator extends Generator {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERTYPEDECLARATIONGENERATOR;
        }

        public ParserTypeDeclarationGenerator(ParserTypeDeclaration parserTypeDeclaration) {
            super(parserTypeDeclaration);
        }

        @Override
        public ParserTypeDeclaration generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                      ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                      ArrayList<TypeParameter> typeMappings,
                                                      Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                      Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
            return generateInstance(parsedTypeParameters, parsedParameters, typeMappings, valuesUnderScope, symtab, null);
        }

        public ParserTypeDeclaration generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                      ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                      ArrayList<TypeParameter> typeMappings,
                                                      Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                      Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab,
                                                      AbstractObjectOfLanguage scopeToAddUnder) {
            ParserTypeDeclaration newInstance = new ParserTypeDeclaration(this.getName(), this.getNameSpace());
            if(scopeToAddUnder == null) {
                scopeToAddUnder = newInstance;
            }

            if(! parsedParameters.isEmpty()) {
                assert this.getParameters().size() == parsedParameters.size();
            }
                
            ArrayList<Parameter> originalParameters = this.getParameters();
            for(int i = 0; i < originalParameters.size(); i++) {
                Parameter currentParam = originalParameters.get(i);
                if(currentParam.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                    assert this.getOptTypeParameters().contains(currentParam.getType());

                    int typeIndex = this.getOptTypeParameters().indexOf(currentParam.getType());
                    AbstractObjectOfLanguage type = parsedTypeParameters.get(typeIndex);
                    System.out.println("replacing with type: " + type.getName() + " of: " + currentParam.getName());
                    Parameter newParam = new Parameter(currentParam.getName(), scopeToAddUnder, type, currentParam.getDirection(), currentParam.getAssignedExpression());
                    newInstance.addParameter(newParam);
                    addToSymtab(scopeToAddUnder, newParam.getName(), newParam, symtab);
                } else {
                    Parameter newParam = new Parameter(currentParam.getName(), scopeToAddUnder, currentParam.getType(), currentParam.getDirection(), currentParam.getAssignedExpression());
                    newInstance.addParameter(newParam);
                    addToSymtab(scopeToAddUnder, newParam.getName(), newParam, symtab);
                }
            }

            return newInstance;
        }
    }

    class ExternDeclarationGenerator extends Generator {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNDECLARATIONGENERATOR;
        }

        public ExternDeclarationGenerator(ExternDeclaration externDeclaration) {
            super(externDeclaration);
        }

        public ExternDeclaration generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                      ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                      ArrayList<TypeParameter> typeMappings,
                                                      Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                      Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
            assert this.getOptTypeParameters().size() == parsedTypeParameters.size();
            assert this.getParameters().size() == parsedParameters.size();
            ExternDeclaration newInstance = new ExternDeclaration(this.getName(), this.getNameSpace());

            for(String names : valuesUnderScope.keySet()) {
                AbstractObjectOfLanguage childUnderScope = valuesUnderScope.get(names);
                AbstractObjectOfLanguage newChildToAdd;
                if(childUnderScope.isGeneratorClass()) {
                    newChildToAdd = ((Generator) childUnderScope).generateInstance(parsedTypeParameters, parsedParameters, typeMappings, valuesUnderScope, symtab);
                } else if(childUnderScope.getName().equals(this.getName())) {
                    // constructor
                    newChildToAdd = addToSymtab(newInstance, childUnderScope.getName(), symtab);

                    ArrayList<Parameter> originalParameters = childUnderScope.getParameters();
                    for(int i = 0; i < originalParameters.size(); i++) {
                        Parameter currentParam = originalParameters.get(i);
                        if(currentParam.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                            assert typeMappings.contains(currentParam.getType());
        
                            int typeIndex = typeMappings.indexOf(currentParam.getType());
                            AbstractObjectOfLanguage type = parsedTypeParameters.get(typeIndex);
                            Parameter newParam = new Parameter(currentParam.getName(), newChildToAdd, type, currentParam.getDirection(), currentParam.getAssignedExpression());
                            newChildToAdd.addParameter(newParam);
                            addToSymtab(newChildToAdd, newParam.getName(), newParam, symtab);
                        } else {
                            Parameter newParam = new Parameter(currentParam.getName(), newChildToAdd, currentParam.getType(), currentParam.getDirection(), currentParam.getAssignedExpression());
                            newChildToAdd.addParameter(newParam);
                            addToSymtab(newChildToAdd, newParam.getName(), newParam, symtab);
                        }
                    }
                } else if(childUnderScope.hasAssociatedType() && childUnderScope.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                    assert false : "NEED TO HANDLE THIS! " + childUnderScope.getName() + " has generic type: " + childUnderScope.getType().getName();
                    newChildToAdd = childUnderScope;
                } else {
                    newChildToAdd = childUnderScope;
                }

                addToSymtab(newInstance, newChildToAdd.getName(), newChildToAdd, symtab);
            }

            return newInstance;
        }
    }

    class FunctionPrototypeGenerator extends Generator {
        // not final for generic return types that have to be of this name space, so they will be added later when this
        // object is created and used as that generic type's scope.
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.FUNCTIONPROTOTYPEGENERATOR;
        }

        @Override
        public boolean hasAssociatedType() {
            return super.getRegularLanguageObject().hasAssociatedType();
        }

        @Override
        AbstractObjectOfLanguage getType() {
            return super.getRegularLanguageObject().getType();
        }

        public void setType(AbstractObjectOfLanguage typeOrVoid) {
            ((FunctionPrototype) super.getRegularLanguageObject()).setType(typeOrVoid);
        }

        public FunctionPrototypeGenerator(FunctionPrototype functionPrototype){
            super(functionPrototype);
        }

        public AbstractObjectOfLanguage generateInstance(ArrayList<AbstractObjectOfLanguage> parsedTypeParameters, 
                                                      ArrayList<AbstractObjectOfLanguage> parsedParameters,
                                                      ArrayList<TypeParameter> typeMappings,
                                                      Map<String, AbstractObjectOfLanguage> valuesUnderScope,
                                                      Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
            AbstractObjectOfLanguage newType;
            AbstractObjectOfLanguage typeOrVoid = super.getRegularLanguageObject().getType();
            boolean doesHaveTypeParameters = false;
            if(typeOrVoid.getConstructType() == LObjectKind.TYPEPARAMETER) {
                // can pull this out to be a new helper function
                if(! typeMappings.contains(typeOrVoid)) {
                    doesHaveTypeParameters = true;
                    newType = typeOrVoid;                   
                } else {
                    assert typeMappings.contains(typeOrVoid) : this.getName() + " is supposed to contain the generic: " + typeOrVoid.getName();

                    if(parsedTypeParameters.isEmpty()) {
                        assert doesParameterListContainThisGeneric(this.getParameters(), typeOrVoid);
                        int indexOfGeneric = getIndexOfParameterWithTheGeneric(this.getParameters(), typeOrVoid);
                        // assert indexOfGeneric >= 0 : "Generic: " + typeOrVoid.getName() + " not present inside generator class";
                        newType = parsedParameters.get(indexOfGeneric);
                        if(newType.hasAssociatedType()) {
                            newType = newType.getType();
                        }
                    } else {
                        int indexOfGeneric = typeMappings.indexOf(typeOrVoid);
                        newType = parsedTypeParameters.get(indexOfGeneric);
                    }
                }
            } else {
                newType = typeOrVoid;
            }

            // assert this.getParameters().size() == parsedParameters.size();

            FunctionPrototype newInstance = new FunctionPrototype(this.getName(), this.getNameSpace(), newType);;
            FunctionPrototypeGenerator newPrototypeInstance = null;

            ArrayList<Parameter> originalParameters = this.getParameters();
            if(! doesHaveTypeParameters) {
                for(int i = 0; i < originalParameters.size(); i++) {
                    Parameter currentParam = originalParameters.get(i);
                    if(currentParam.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                        if(! typeMappings.contains(currentParam.getType())) {
                            doesHaveTypeParameters = true;
                            break;
                        }
                    }
                }
            }

            if(doesHaveTypeParameters){
                newPrototypeInstance = new FunctionPrototypeGenerator(newInstance);
                for(TypeParameter e : this.getOptTypeParameters()) {
                    newPrototypeInstance.addOptTypeParameters(e);
                }
            }
            
            for(int i = 0; i < originalParameters.size(); i++) {
                Parameter newParam;
                Parameter currentParam = originalParameters.get(i);
                AbstractObjectOfLanguage newParamType;
                if(currentParam.getType().getConstructType() == LObjectKind.TYPEPARAMETER) {
                    if(! typeMappings.contains(currentParam.getType())) {
                        doesHaveTypeParameters = true;
                        newParamType = currentParam.getType();                   
                    } else {
                        assert typeMappings.contains(currentParam.getType());
    
                        if(parsedTypeParameters.isEmpty()) {
                            assert doesParameterListContainThisGeneric(this.getParameters(), currentParam.getType());
                            int indexOfGeneric = getIndexOfParameterWithTheGeneric(this.getParameters(), currentParam.getType());
                            // assert indexOfGeneric >= 0 : "Generic: " + currentParam.getType().getName() + " not present inside generator class";
                            newParamType = parsedParameters.get(indexOfGeneric);
                            if(newType.hasAssociatedType()) {
                                newParamType = newType.getType();
                            }
                        } else {
                            int indexOfGeneric = typeMappings.indexOf(currentParam.getType());
                            newParamType = parsedTypeParameters.get(indexOfGeneric);
                        }
                    }
                } else {
                    newParamType = currentParam.getType();
                }

                if(doesHaveTypeParameters) {
                    assert newPrototypeInstance != null;
                    newParam = new Parameter(currentParam.getName(), newPrototypeInstance, newParamType, currentParam.getDirection(), currentParam.getAssignedExpression());
                    newPrototypeInstance.addParameter(newParam);
                    addToSymtab(newPrototypeInstance, newParam.getName(), newParam, symtab);
                } else {
                    newParam = new Parameter(currentParam.getName(), newInstance, newParamType, currentParam.getDirection(), currentParam.getAssignedExpression());
                    newInstance.addParameter(newParam);
                    addToSymtab(newInstance, newParam.getName(), newParam, symtab);
                }
            }

            return (doesHaveTypeParameters ? newPrototypeInstance : newInstance);
        }
    }

    // End of generator class

    // Regular classes

    class LanguageObject extends RegularLanguageObject {
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
    class ConstantTreeGlobalObjects extends RegularLanguageObject {
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
            // System.err.println("ConstantTreeGlobalObjects do not have a namespace since they are global level");
            // System.exit(1);
            assert false : "ConstantTreeGlobalObjects do not have a namespace since they are global level";

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

    class HeaderTypeDeclaration extends RegularLanguageObject {
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

    class HeaderUnionDeclaration extends RegularLanguageObject {
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

    class HeaderStackType extends RegularLanguageObject {
        AbstractObjectOfLanguage parentScope;
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.HEADERSTACKTYPE;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        @Override
        public AbstractObjectOfLanguage getNameSpace() {
            return this.parentScope;
        }

        public HeaderStackType(String name, AbstractObjectOfLanguage nameSpace, HeaderTypeDeclaration parentScope) {
            super(name, nameSpace);
            this.parentScope = parentScope;
        }
    }

    class StructTypeDeclaration extends RegularLanguageObject {
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

    class EnumDeclaration extends RegularLanguageObject {
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

        @Override
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

    class TypeDefDeclaration extends RegularLanguageObject {
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

        @Override
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

    class ParserTypeDeclaration extends RegularLanguageObject {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERTYPEDECLARATION;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        public ParserTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class PackageTypeDeclaration extends RegularLanguageObject {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.PACKAGETYPEDECLARATION;
        }

        @Override 
        public boolean isScoped() {
            return false;
        }

        public PackageTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
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
    class ExternDeclaration extends RegularLanguageObject {
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

    class ExternFunctionDeclaration extends RegularLanguageObject {
        private FunctionPrototype functionPrototype;
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.EXTERNFUNCTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public void setFunctionPrototype(FunctionPrototype functionPrototype) {
            assert this.functionPrototype == null;

            this.functionPrototype = functionPrototype;
        }

        public FunctionPrototype getFunctionPrototype() {
            return this.functionPrototype;
        }

        @Override
        public boolean hasAssociatedType() {
            return this.functionPrototype.hasAssociatedType();
        }

        @Override
        AbstractObjectOfLanguage getType() {
            return this.functionPrototype.getType();
        }

        public ExternFunctionDeclaration(String name, AbstractObjectOfLanguage nameSpace){
            super(name, nameSpace);
            this.functionPrototype = null;
        }
    }

    class FunctionDeclaration extends RegularLanguageObject {
        private FunctionPrototype functionPrototype;
        private AbstractObjectOfLanguage blockStatement;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.FUNCTIONDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public void setFunctionPrototype(FunctionPrototype functionPrototype) {
            assert this.functionPrototype == null;

            this.functionPrototype = functionPrototype;
        }

        public void setBlockStatement(AbstractObjectOfLanguage blockStatement) {
            assert this.blockStatement == null;

            this.blockStatement = blockStatement;
        }

        public AbstractObjectOfLanguage getBlockStatement() {
            return this.blockStatement;
        }

        public FunctionPrototype getFunctionPrototype() {
            return this.functionPrototype;
        }

        @Override
        public boolean hasAssociatedType() {
            return this.functionPrototype.hasAssociatedType();
        }

        @Override
        AbstractObjectOfLanguage getType() {
            return this.functionPrototype.getType();
        }

        public FunctionDeclaration(String name, AbstractObjectOfLanguage nameSpace){
            super(name, nameSpace);
            this.functionPrototype = null;
        }
    }

    class FunctionPrototype extends RegularLanguageObject {
        // not final for generic return types that have to be of this name space, so they will be added later when this
        // object is created and used as that generic type's scope.
        private AbstractObjectOfLanguage typeOrVoid;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.FUNCTIONPROTOTYPE;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        @Override
        public boolean hasAssociatedType() {
            return true;
        }

        @Override
        AbstractObjectOfLanguage getType() {
            return this.typeOrVoid;
        }

        public void setType(AbstractObjectOfLanguage typeOrVoid) {
            // assert this.typeOrVoid == null;
            if(this.typeOrVoid != null) {
                System.err.println("Old type being replaced for: " + this.getName() + ". Old type: " + this.typeOrVoid.getName() + ", new type being set: " + typeOrVoid.getName());
            }

            this.typeOrVoid = typeOrVoid;
        }

        public FunctionPrototype(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage typeOrVoid){
            super(name, nameSpace);
            this.typeOrVoid = typeOrVoid;
        }
    }

    // combines control type declaration
    class ControlTypeDeclaration extends RegularLanguageObject {
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONTROLTYPEDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public ControlTypeDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    // Basic AST node classes. Making them new language object to support compiler built in functions
    class ControlDeclaration extends RegularLanguageObject {
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.CONTROLDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public ControlDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class ParserDeclaration extends RegularLanguageObject {
        private ParserTypeDeclaration parserTypeDeclaration;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARSERDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public void setParserTypeDeclaration(ParserTypeDeclaration parserTypeDeclaration) {
            assert this.parserTypeDeclaration == null;

            this.parserTypeDeclaration = parserTypeDeclaration;
        }

        public ParserTypeDeclaration getParserTypeDeclaration() {
            return this.parserTypeDeclaration;
        }

        public ParserDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class TableDeclaration extends RegularLanguageObject {
        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.TABLEDECLARATION;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        public TableDeclaration(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    // Support Classes

    class TypeOrVoid extends RegularLanguageObject {
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

        @Override
        AbstractObjectOfLanguage getType() {
            if(this.typeRef != null) {
                return this.typeRef;
            } else if(this.identifier != null) {
                return this.identifier;
            } else {
                assert this.voidVar != null;
                return this.voidVar;
            }
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

        TypeOrVoid(AbstractObjectOfLanguage nameSpace, ConstantTreeGlobalObjects voidVar) {
            super(voidVar.getName(), nameSpace);
            this.identifier = null;
            this.typeRef = null;
            this.voidVar = voidVar;
        }
    }

    class Variable extends RegularLanguageObject {
        private final AbstractObjectOfLanguage type;
        private AbstractObjectOfLanguage assignedExpression;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.VARIABLE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        boolean hasAssociatedType() {
            return true;
        }

        @Override
        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        boolean hasAssignedExpression() {
            return (assignedExpression != null);
        }

        public AbstractObjectOfLanguage getAssignedExpression() {
            return this.assignedExpression;
        }

        public void setAssignedExpression(AbstractObjectOfLanguage expression) {
            this.assignedExpression = expression;
        }

        public Variable(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type) {
            super(name, nameSpace);
            this.type = type;
            this.assignedExpression = null;
        }

        public Variable(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, AbstractObjectOfLanguage assignedExpression) {
            super(name, nameSpace);
            this.type = type;
            this.assignedExpression = assignedExpression;
        } 
    }

    class Parameter extends Variable {
        private final ConstantTreeGlobalObjects direction;

        @Override 
        public LObjectKind getConstructType() {
            return LObjectKind.PARAMETER;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        public ConstantTreeGlobalObjects getDirection() {
            return this.direction;
        }

        // Right now we are assuming that the invoker has already created or retrieved the type and direction object
        // and will pass it to us
        public Parameter(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, ConstantTreeGlobalObjects direction) {
            super(name, nameSpace, type);
            this.direction = direction;
        }

        public Parameter(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type, ConstantTreeGlobalObjects direction, AbstractObjectOfLanguage assignedExpression) {
            super(name, nameSpace, type, assignedExpression);
            this.direction = direction;
        }
    }

    class TypeParameter extends RegularLanguageObject {
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

    class StructField extends RegularLanguageObject {
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

        @Override
        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        public StructField(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage typeRef) {
            super(name, nameSpace);
            this.type = typeRef;
        }
    }

    class OLangString extends RegularLanguageObject {
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

    class InvokableLanguageKeyword extends RegularLanguageObject {
        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.INVOKABLEKEYWORD;
        }

        public InvokableLanguageKeyword(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class BuiltinFunction extends RegularLanguageObject {
        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.BUILTINFUNCTION;
        }

        public BuiltinFunction(String name, AbstractObjectOfLanguage nameSpace) {
            super(name, nameSpace);
        }
    }

    class BaseTypes extends RegularLanguageObject {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.BASETYPE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public AbstractObjectOfLanguage getNameSpace() {
            // System.err.println("ConstantTreeGlobalObjects do not have a namespace since they are global level");
            // System.exit(1);
            assert false : "Error: Base types cannot be used as namespaces. Referring to (" + this.getName() + ") base type.";

            return null;
        }

        public BaseTypes(String name) {
            super(name, null);
        }
    }

    class AnonymousType extends RegularLanguageObject {
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.ANONYMOUS;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public String getName() {
            System.err.println("Error: cannot get name for anonymous types.");
            System.exit(1);
            return "";
        }

        public AnonymousType(AbstractObjectOfLanguage nameSpace) {
            super("", nameSpace);
        }
    }

    class TupleType extends AnonymousType {
        private final ArrayList<AbstractObjectOfLanguage> typeArgumentsList;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.TUPLETYPE;
        }

        public void addToTypeArgumentList(AbstractObjectOfLanguage typeArg) {
            typeArgumentsList.add(typeArg);
        }

        public ArrayList<AbstractObjectOfLanguage> getTypeArgumentList() {
            return typeArgumentsList;
        }

        public boolean hasTypeArguments() {
            return ! typeArgumentsList.isEmpty();
        }

        public TupleType(AbstractObjectOfLanguage nameSpace) {
            super(nameSpace);
            typeArgumentsList = new ArrayList<>();
        }
    }

    class SpecializedType extends RegularLanguageObject {
        private final ArrayList<AbstractObjectOfLanguage> typeArgumentsList;

        private final AbstractObjectOfLanguage type;
        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.SPECIALIZEDTYPE;
        }

        @Override
        public boolean isScoped() {
            return false;
        }

        @Override
        public boolean hasAssociatedType() {
            return true;
        }

        @Override 
        public AbstractObjectOfLanguage getType() {
            return this.type;
        }

        @Override 
        public AbstractObjectOfLanguage getNameSpace() {
            return this.type;
        }

        @Override
        void addParsedOptTypeParameters(AbstractObjectOfLanguage typeParameter) {
            this.type.addParsedOptTypeParameters(typeParameter);
        }

        @Override 
        boolean hasParsedOptTypeParameters() {
            return this.type.hasParsedOptTypeParameters();
        }

        @Override
        ArrayList<AbstractObjectOfLanguage> getParsedOptTypeParameters() {
            return this.type.getParsedOptTypeParameters();
        }

        public void addToTypeArgumentList(AbstractObjectOfLanguage typeArg) {
            typeArgumentsList.add(typeArg);
        }

        public ArrayList<AbstractObjectOfLanguage> getTypeArgumentList() {
            return typeArgumentsList;
        }

        public boolean hasTypeArguments() {
            return ! typeArgumentsList.isEmpty();
        }

        public SpecializedType(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage type) {
            super(name, nameSpace);
            this.type = type;
            typeArgumentsList = new ArrayList<>();
        }
    }

    public class SubClass extends RegularLanguageObject {
        AbstractObjectOfLanguage originalClass;

        @Override
        public LObjectKind getConstructType() {
            return LObjectKind.SUBCLASS;
        }

        @Override
        public boolean isScoped() {
            return true;
        }

        @Override
        public boolean hasAssociatedType() {
            return true;
        }

        @Override
        public AbstractObjectOfLanguage getType() {
            return this.originalClass;
        }

        // @Override
        // public String getName() {
        //     return "(" + this.originalClass.getName() + ") " + super.getName();
        // }

        public AbstractObjectOfLanguage getOriginalClass() {
            return this.originalClass;
        }

        public SubClass(String name, AbstractObjectOfLanguage nameSpace, AbstractObjectOfLanguage originalClass) {
            super(name, nameSpace);
            this.originalClass = originalClass;
        }
    }

    // End of regular classes

    public class BaseTypesCollection {
        private ArrayList<String> baseTypes;
        private Map<String, AbstractObjectOfLanguage> baseTypeObjects;
        private BaseTypes voidObject;
        private BaseTypes dontCareObject;
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
                baseTypeObjects.put(type, new BaseTypes(type));
            }

            voidObject = new BaseTypes(voidString);
            dontCareObject = new BaseTypes(dontCare);
        }

        public boolean isBaseType(String type) {
            return baseTypes.contains(type);
        }

        public AbstractObjectOfLanguage getLanguageObjectOfBaseType(String type) {
            assert baseTypes.contains(type);

            return baseTypeObjects.get(type);
        }

        public BaseTypes getVoidLanguageObject() {
            return this.voidObject;
        }

        public BaseTypes getDontCareLanguageObject() {
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
        private Map<String, ConstantTreeGlobalObjects> directionTypeObjects;

        {
            directions = new ArrayList<>();
            directions.add("in");
            directions.add("out");
            directions.add("inout");

            directionTypeObjects = new HashMap<>();

            for(String type : directions) {
                directionTypeObjects.put(type, new ConstantTreeGlobalObjects(type));
            }
        }

        public ConstantTreeGlobalObjects getLanguageObjectOfDirection(String type) {
            assert directions.contains(type);

            return directionTypeObjects.get(type);
        }
    }

    static class ReservedKeywords {
        public static HashSet<String> nonTypeNameKeywords = new HashSet<>();
        public static HashSet<String> nonTableKwNameKeywords = new HashSet<>();
        static {
            nonTypeNameKeywords.add("key");
            nonTypeNameKeywords.add("actions");
            nonTypeNameKeywords.add("state");
            nonTypeNameKeywords.add("entries");
            nonTypeNameKeywords.add("type");
            nonTypeNameKeywords.add("apply");

            nonTableKwNameKeywords.add("state");
            nonTableKwNameKeywords.add("type");
            nonTableKwNameKeywords.add("apply");
        }

        public static boolean isNonTypeNameKeyword(String name) {
            return nonTypeNameKeywords.contains(name);
        }

        public static boolean isNonTableKwNameKeywords(String name) {
            return nonTableKwNameKeywords.contains(name);
        }
    }

    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name, Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
        LanguageObject newLangObj = new LanguageObject(name, scope);
        return addToSymtab(scope, name, newLangObj, symtab);
    }

    public AbstractObjectOfLanguage addToSymtab(AbstractObjectOfLanguage scope, String name, AbstractObjectOfLanguage newLangObj, Map<AbstractObjectOfLanguage, Map<String, AbstractObjectOfLanguage>> symtab) {
        if( !symtab.containsKey(scope)) {
            symtab.put(scope, new HashMap<>());
        }

        if(symtab.get(scope).containsKey(name)) {
            boolean isDuplicateFunctionOrMethod = true;
            if(newLangObj.getConstructType() == LObjectKind.FUNCTION ||
                newLangObj.getConstructType() == LObjectKind.METHOD) {
                    // isDuplicateFunctionOrMethod = isFunctionAndMethodDuplicate(newLangObj, symtab.get(scope).get(name));
                    isDuplicateFunctionOrMethod = true;
                }
            // TODO: Tuples are exceptions
            if(isDuplicateFunctionOrMethod) {
                System.err.println("Multiple declaration warning (FIX): another entity with the same name (" 
                                    + name + 
                                    ") already exists");
            }
            // System.exit(1);
        } else {
            // nodeObj = p4LanguageObject.new LanguageObject(name, scope);
            symtab.get(scope).put(name, newLangObj);
        }

        return newLangObj;
    }

    public int getIndexOfParameterWithTheGeneric(ArrayList<Parameter> parameters, AbstractObjectOfLanguage typeParameter) {
        int index = -1;
        for(int i = 0; i < parameters.size(); i++) {
            Parameter p = parameters.get(i);
            if(p.getType().getConstructType() == LObjectKind.TYPEPARAMETER &&
               p.getType() == typeParameter) {
                   index = i;
            }
        }
    
        return index;
    }

    public boolean doesParameterListContainThisGeneric(ArrayList<Parameter> parameters, AbstractObjectOfLanguage type) {
        int indexOfIt = getIndexOfParameterWithTheGeneric(parameters, type);

        if(indexOfIt < 0) {
            return false;
        } else {
            return true;
        }
    }
}

/*
Note: opt type parameters are not allowed inside controlTypeDeclaration if it is used inside control declaration
same with parsers

When the object is declared -> if it has type parameters in it (whether as type) or as a parameter, mark it as generator
Note: if a type variable is created for that specific object, assert that it is present inside optTypeParameter
7.2.10 -> if it is present in the parent object, need not to be present inside the optTypeParameter

 */