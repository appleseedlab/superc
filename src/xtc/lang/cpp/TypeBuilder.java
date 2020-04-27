package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;

import xtc.type.NumberT;
import xtc.type.Type;
import xtc.type.UnitT;


public class TypeBuilder {
  Type type; // void, char, short, int, long, float, double, SUE, typedef

  // note: these can appear in any order (in the source file), and they will be initialized to false
  boolean isAuto;
  boolean isConst;
  boolean isVolatile;
  boolean isExtern;
  boolean isStatic;
  boolean isRegister;
  boolean isThreadlocal;
  boolean isInline;
  boolean isSigned;
  boolean isUnsigned;
  boolean isComplex;
  
  int longCount;

  List<String> attributes;

  boolean isTypeError;

  public String attributesToString() {
    return String.join(" ", attributes);
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();

    // TODO: check if the order of these matters

    if (isAuto)
      sb.append("auto ");
    if (isConst)
      sb.append("const ");
    if (isVolatile)
      sb.append("volatile ");
    if (isExtern)
      sb.append("extern ");
    if (isStatic)
      sb.append("static ");
    if (isRegister)
      sb.append("register ");
    if (isThreadlocal)
      sb.append("__thread ");
    if (isInline)
      sb.append("inline");
    if (isSigned)
      sb.append("signed");
    if (isUnsigned)
      sb.append("unsigned");
    if (isComplex)
      sb.append("complex");

    for (int i = 0; i < longCount; i++)
      sb.append("long ");

    sb.append(attributesToString());

    if (type instanceof UnitT) {
      System.err.println("ERROR: identifier has no valid type.");
      System.exit(1);
    }
    else
      sb.append(type.toString());

    return sb.toString();
  }

  public Type toType() {
    return type; // placeholder
     // TODO: create the type based on all of the fields, then return that.
  }

  public TypeBuilder(TypeBuilder old, String name) {
    type = old.type;
    isAuto = old.isAuto;
    isConst = old.isConst;
    isVolatile = old.isVolatile;
    isExtern = old.isExtern;
    isStatic = old.isStatic;
    isRegister = old.isRegister;
    isThreadlocal = old.isRegister;
    isInline = old.isInline;
    isSigned = old.isSigned;
    isUnsigned = old.isUnsigned;
    isComplex = old.isComplex;
    longCount = old.longCount;
    attributes = new LinkedList<String>(old.attributes);
    isTypeError = old.isTypeError;

    if (name.equals("auto"))
      isAuto = true;
    else if (name.equals("const"))
      isConst = true;
    else if (name.equals("volatile"))
      isVolatile = true;
    else if (name.equals("extern"))
      isExtern = true;
    else if (name.equals("static"))
      isStatic = true;
    else if (name.equals("register"))
      isRegister = true;
    else if (name.equals("__thread"))
      isThreadlocal = true;
    else if (name.equals("inline"))
      isInline = true;
    else if (name.equals("signed"))
      isSigned = true;
    else if (name.equals("unsigned"))
      isUnsigned = true;
    else if (name.equals("complex"))
      isComplex = true;
    else if (name.equals("long"))
      longCount += 1;
    else {
      attributes.add(name);
    }
  }

  // creates a new typebuilder using a string (which is NOT a type)
  public TypeBuilder(String name) {
    type = new UnitT();
    isAuto = false;
    isConst = false;
    isVolatile = false;
    isExtern = false;
    isStatic = false;
    isRegister = false;
    isThreadlocal = false;
    isInline = false;
    isSigned = false;
    isUnsigned = false;
    isComplex = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
    
    if (name.equals("auto"))
      isAuto = true;
    else if (name.equals("const"))
      isConst = true;
    else if (name.equals("volatile"))
      isVolatile = true;
    else if (name.equals("extern"))
      isExtern = true;
    else if (name.equals("static"))
      isStatic = true;
    else if (name.equals("register"))
      isRegister = true;
    else if (name.equals("__thread"))
      isThreadlocal = true;
    else if (name.equals("inline"))
      isInline = true;
    else if (name.equals("signed"))
      isSigned = true;
    else if (name.equals("unsigned"))
      isUnsigned = true;
    else if (name.equals("complex"))
      isComplex = true;
    else if (name.equals("long"))
      longCount += 1;
    else {
      attributes.add(name);
    }
  }

  // creates a new typebuilder using only a type
  public TypeBuilder(Type type) {
    this.type = type;
    isAuto = false;
    isConst = false;
    isVolatile = false;
    isExtern = false;
    isStatic = false;
    isRegister = false;
    isThreadlocal = false;
    isInline = false;
    isSigned = false;
    isUnsigned = false;
    isComplex = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
  }

  // copy constructor that changes type (should be used whenever a type is found)
  // the default constructor should be used before this ever gets called.
  public TypeBuilder(TypeBuilder old, Type type) {

    // copy constructor that changes the type
    if (old.type instanceof UnitT) {
      this.type = type;
      isAuto = old.isAuto;
      isConst = old.isConst;
      isVolatile = old.isVolatile;
      isExtern = old.isExtern;
      isStatic = old.isStatic;
      isRegister = old.isRegister;
      isThreadlocal = old.isRegister;
      isInline = old.isInline;
      isSigned = old.isSigned;
      isUnsigned = old.isUnsigned;
      isComplex = old.isComplex;
      longCount = old.longCount;
      attributes = new LinkedList<String>(old.attributes);
      isTypeError = old.isTypeError;
    }
    else {
      System.err.println("ERROR: identifier has multiple conflicting types.");
      System.exit(1);
    }
  }

  // sets all flags to false and type starts as unit
  public TypeBuilder() {
    type = new UnitT();
    isAuto = false;
    isConst = false;
    isVolatile = false;
    isExtern = false;
    isStatic = false;
    isRegister = false;
    isThreadlocal = false;
    isInline = false;
    isSigned = false;
    isUnsigned = false;
    isComplex = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
  }

  // copy constructor
  public TypeBuilder(TypeBuilder original) {
      type = original.type;
      isAuto = original.isAuto;
      isConst = original.isConst;
      isVolatile = original.isVolatile;
      isExtern = original.isExtern;
      isStatic = original.isStatic;
      isRegister = original.isRegister;
      isThreadlocal = original.isRegister;
      isInline = original.isInline;
      isSigned = original.isSigned;
      isUnsigned = original.isUnsigned;
      isComplex = original.isComplex;
      longCount = original.longCount;
      attributes = new LinkedList<String>(original.attributes);
      isTypeError = original.isTypeError;
  }

  public TypeBuilder combine(TypeBuilder with) {
    // TUTORIAL: this is where all the logic for combining specifiers
    // will go

    // this copy might be able to be optimized away, if we know that
    // the reference to the semantic value won't be used again, e.g.,
    // by another subparser
    TypeBuilder result = new TypeBuilder(this);

    // checks for mutually-exclusive qualifiers
    if ((result.isStatic || with.isStatic) && (result.isExtern || with.isExtern))
      isTypeError = true;
    else if ((result.isStatic || with.isStatic) && (result.isAuto || with.isAuto))
      isTypeError = true;
    else if ((result.isExtern || with.isExtern) && (result.isAuto || with.isAuto))
      isTypeError = true;
    else if ((result.isRegister || with.isRegister) && (result.isStatic || with.isStatic))
      isTypeError = true;
    else if ((result.isRegister || with.isRegister) && (result.isAuto || with.isAuto))
      isTypeError = true;
    else if ((result.isRegister || with.isRegister) && (result.isStatic || with.isStatic))
      isTypeError = true;
    else if ((result.isRegister || with.isRegister) && (result.isExtern || with.isExtern))
      isTypeError = true;
    else if ((result.isThreadlocal || with.isThreadlocal) && (result.isAuto || with.isAuto))
      isTypeError = true;
    else if ((result.isThreadlocal || with.isThreadlocal) && (result.isRegister || with.isRegister))
      isTypeError = true;
  
    // checks for variables with inline specifier
    if ((result.type.isVariable() || with.type.isVariable()) && (result.isInline || with.isInline))
      isTypeError = true;

    // see xtc.type.Type for other helper methods for determining the
    // kind of type
    if (result.type.isNumber() && with.type.isNumber()) {
      switch(((NumberT) result.type).getKind()) {
      case INT:
        switch(((NumberT) with.type).getKind()) {
        case INT:
          System.err.println("[INFO] found a type error: int int");
          break;
        case LONG:
	    //needs to handle the existance of int to make sure it doesn't appear twice
          System.err.println("[INFO] found a type: int long");
	  result.type = NumberT.LONG;
          break;
        default:
          System.err.println("[ERROR] unsupported combination of number types");
          System.exit(1);
        }
        break;
      case LONG:
        switch(((NumberT) with.type).getKind()) {
        case INT:
          System.err.println("[INFO] found a valid type: long int");
          result.type = NumberT.LONG;
          break;
        case LONG:
          System.err.println("[INFO] found a valid type: long long");
          result.type = NumberT.LONG_LONG;
          break;
        default:
          System.err.println("[ERROR] unsupported combination of number types");
          System.exit(1);
        }
        break;
      case LONG_LONG:
        switch(((NumberT) with.type).getKind()) {
        case INT:
          System.err.println("[INFO] found a valid type: long long");
          result.type = NumberT.LONG_LONG;
          break;
        default:
          System.err.println("[ERROR] unsupported combination of number types");
          System.exit(1);
        }
        break;
      default:
        System.err.println("[ERROR] unsupported combination of number types");
        System.exit(1);
      }
    } else {
      System.err.println("[ERROR] unsupported: type builders are not numbers");
      System.exit(1);
    }

    // TODO: check all the other combinations of type specs to check
    // for validity and construct the new (partial) type spec

    return result;
  }
}
