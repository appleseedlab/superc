package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;

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
  }
}
