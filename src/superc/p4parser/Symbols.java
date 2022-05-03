package superc.p4parser;

import java.util.ArrayList;
import java.util.HashSet;

import superc.p4parser.P4LanguageObject.AbstractObjectOfLanguage;
import superc.p4parser.P4LanguageObject.LObjectKind;

public class Symbols {
    // Constant values
    public static P4LanguageObject p4LanguageObject = new P4LanguageObject();
    public static final AbstractObjectOfLanguage global_scope = p4LanguageObject.new ConstantTreeGlobalObjects("GLOBAL");
    public static final AbstractObjectOfLanguage undefined_scope = p4LanguageObject.new ConstantTreeGlobalObjects("UNDEFINED");
    public static final AbstractObjectOfLanguage undeclared_object = p4LanguageObject.new ConstantTreeGlobalObjects("UNDECLARED OBJECT");
    public static final AbstractObjectOfLanguage default_language_object = p4LanguageObject.new ConstantTreeGlobalObjects("DEFAULT");

    public static HashSet<LObjectKind> overridableConstructs = new HashSet<>();
    public static ArrayList<String> defaultHeaderFunction = new ArrayList<>();

    static {

        overridableConstructs.add(LObjectKind.FUNCTION);
        overridableConstructs.add(LObjectKind.FUNCTIONDECLARATION);
        overridableConstructs.add(LObjectKind.FUNCTIONPROTOTYPE);
        overridableConstructs.add(LObjectKind.FUNCTIONPROTOTYPEGENERATOR);
        overridableConstructs.add(LObjectKind.METHOD);
        overridableConstructs.add(LObjectKind.EXTERNFUNCTIONDECLARATION);
        overridableConstructs.add(LObjectKind.EXTERNFUNCTIONDECLARATIONGENERATOR);
        overridableConstructs.add(LObjectKind.FUNCTIONPROTOTYPEPLACEHOLDER);

        // issue1334.p4 in the p4c test suite -> turns out control and package blocks are also overridable
        overridableConstructs.add(LObjectKind.CONTROLDECLARATION);
        overridableConstructs.add(LObjectKind.CONTROLTYPEDECLARATION);
        overridableConstructs.add(LObjectKind.CONTROLTYPEDECLARATIONGENERATOR);
        overridableConstructs.add(LObjectKind.PACKAGETYPEDECLARATION);
        overridableConstructs.add(LObjectKind.PACKAGETYPEDECLARATIONGENERATOR);
        overridableConstructs.add(LObjectKind.PARSERDECLARATION);
        overridableConstructs.add(LObjectKind.PARSERDECLARATIONGENERATOR);
        overridableConstructs.add(LObjectKind.PARSERTYPEDECLARATION);
        overridableConstructs.add(LObjectKind.PARSERTYPEDECLARATIONGENERATOR);

        // default functions associated with headers
        defaultHeaderFunction.add("isValid");
        defaultHeaderFunction.add("setValid");
        defaultHeaderFunction.add("setInvalid");
        defaultHeaderFunction.add("minSizeInBits");
        defaultHeaderFunction.add("minSizeInBytes");
    }

    public static HashSet<LObjectKind> getOverridableConstructs() {
        return overridableConstructs;
    }

    public static ArrayList<String> getDefaultHeaderFunctions() {
        return defaultHeaderFunction;
    }

    public static AbstractObjectOfLanguage getGlobalScope() {
        return global_scope;
    }

    public static AbstractObjectOfLanguage getUndefinedScope() {
        return undefined_scope;
    }

    public static AbstractObjectOfLanguage getUndeclaredObject() {
        return undeclared_object;
    }

    public static AbstractObjectOfLanguage getDefaultLanguageObject() {
        return default_language_object;
    }
}