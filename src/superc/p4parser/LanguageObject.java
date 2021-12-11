package superc.p4parser;
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
}