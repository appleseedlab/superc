package xtc.lang.cpp;
import java.util.LinkedList;
import java.util.List;
import xtc.type.NumberT;
import xtc.type.Type;
import xtc.type.UnitT;

public class TypeBuilder {
  Type type; // void, char, short, int, long, float, double, SUE, typedef                        
    enum QUAL {isAuto, isConst, isVolatile, isExtern, isStatic, isRegister, isThreadlocal,
               isInline, isSigned, isUnsigned, isComplex}
    final int NUM_QUALS = 11;
    enum FOUND_TYPE {seenInt, seenLong, seenLongLong, seenChar, seenShort, seenFloat, seenDouble,
                     seenComplex}
    final int NUM_TYPES = 8;
  // note: these can appear in any order (in the source file), and they will be initialized to false                                                                        /*boolean isAuto;                                                                                           
  boolean isConst;                                                                                                                                                                                                 


    boolean qualifiers[] = new boolean[NUM_QUALS];
    boolean foundTypes[] = new boolean[NUM_TYPES];
 // boolean seenInt;     
  
  int longCount;

  List<String> attributes;

  boolean isTypeError;

  public String attributesToString() {
    return String.join(" ", attributes);
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();

    // TODO: check if the order of these matters

    if (qualifiers[QUAL.isAuto.ordinal()])
      sb.append("auto ");
    if (qualifiers[QUAL.isConst.ordinal()])
      sb.append("const ");
    if (qualifiers[QUAL.isVolatile.ordinal()])
      sb.append("volatile ");
    if (qualifiers[QUAL.isExtern.ordinal()])
      sb.append("extern ");
    if (qualifiers[QUAL.isStatic.ordinal()])
      sb.append("static ");
    if (qualifiers[QUAL.isRegister.ordinal()])
      sb.append("register ");
    if (qualifiers[QUAL.isThreadlocal.ordinal()])
      sb.append("__thread ");
    if (qualifiers[QUAL.isInline.ordinal()])
      sb.append("inline");
    if (qualifiers[QUAL.isSigned.ordinal()])
      sb.append("signed");
    if (qualifiers[QUAL.isUnsigned.ordinal()])
      sb.append("unsigned");
    if (qualifiers[QUAL.isComplex.ordinal()])
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
		
		for (int i = 0; i < NUM_QUALS; ++i)
		qualifiers[i] = old.qualifiers[i];
		
		attributes = new LinkedList<String>(old.attributes);
    
		isTypeError = old.isTypeError;

    if (name.equals("auto"))
      qualifiers[QUAL.isAuto.ordinal()] = true;
    else if (name.equals("const"))
      qualifiers[QUAL.isConst.ordinal()] = true;
    else if (name.equals("volatile"))
      qualifiers[QUAL.isVolatile.ordinal()] = true;
    else if (name.equals("extern"))
      qualifiers[QUAL.isExtern.ordinal()] = true;
    else if (name.equals("static"))
      qualifiers[QUAL.isStatic.ordinal()] = true;
    else if (name.equals("register"))
      qualifiers[QUAL.isRegister.ordinal()] = true;
    else if (name.equals("__thread"))
      qualifiers[QUAL.isThreadlocal.ordinal()] = true;
    else if (name.equals("inline"))
      qualifiers[QUAL.isInline.ordinal()] = true;
    else if (name.equals("signed"))
      qualifiers[QUAL.isSigned.ordinal()] = true;
    else if (name.equals("unsigned"))
      qualifiers[QUAL.isUnsigned.ordinal()] = true;
    else if (name.equals("complex"))
      qualifiers[QUAL.isComplex.ordinal()] = true;
    else if (name.equals("long"))
      longCount += 1;
    else {
      attributes.add(name);
    }
  }

  // creates a new typebuilder using a string (which is NOT a type)
  public TypeBuilder(String name) {
    type = new UnitT();
    for (int i = 0; i < NUM_QUALS; ++i)
		  qualifiers[i] = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
    
    if (name.equals("auto"))
      qualifiers[QUAL.isAuto.ordinal()] = true;
    else if (name.equals("const"))
      qualifiers[QUAL.isConst.ordinal()] = true;
    else if (name.equals("volatile"))
      qualifiers[QUAL.isVolatile.ordinal()] = true;
    else if (name.equals("extern"))
      qualifiers[QUAL.isExtern.ordinal()] = true;
    else if (name.equals("static"))
      qualifiers[QUAL.isStatic.ordinal()] = true;
    else if (name.equals("register"))
      qualifiers[QUAL.isRegister.ordinal()] = true;
    else if (name.equals("__thread"))
      qualifiers[QUAL.isThreadlocal.ordinal()] = true;
    else if (name.equals("inline"))
      qualifiers[QUAL.isInline.ordinal()] = true;
    else if (name.equals("signed"))
      qualifiers[QUAL.isSigned.ordinal()] = true;
    else if (name.equals("unsigned"))
      qualifiers[QUAL.isUnsigned.ordinal()] = true;
    else if (name.equals("complex"))
      qualifiers[QUAL.isComplex.ordinal()] = true;
    else if (name.equals("long"))
      longCount += 1;
    else {
      attributes.add(name);
    }
  }

  // creates a new typebuilder using only a type
  public TypeBuilder(Type type) {
    this.type = type;
    for (int i = 0; i < NUM_QUALS; ++i)
		  qualifiers[i] = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
    //foundTypes[FOUND_TYPE.seenInt.ordinal()] = type.hasKind(NumberT.Kind.INT);
  }

  // copy constructor that changes type (should be used whenever a type is found)
  // the default constructor should be used before this ever gets called.
  public TypeBuilder(TypeBuilder old, Type type) {

    // copy constructor that changes the type
    if (old.type instanceof UnitT) {
      this.type = type;
				for (int i = 0; i < NUM_QUALS; ++i)
					qualifiers[i] = old.qualifiers[i];
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
    for (int i = 0; i < NUM_QUALS; ++i)
		  qualifiers[i] = false;
    longCount = 0;
    attributes = new LinkedList<String>();
    isTypeError = false;
   	foundTypes[FOUND_TYPE.seenInt.ordinal()] = false;
  }

  // copy constructor
  public TypeBuilder(TypeBuilder old) {
      type = old.type;
			for (int i = 0; i < NUM_QUALS; ++i)
				qualifiers[i] = old.qualifiers[i];
      longCount = old.longCount;
      attributes = new LinkedList<String>(old.attributes);
      isTypeError = old.isTypeError;
  }


	private boolean qualComboExists(TypeBuilder t1, TypeBuilder t2, QUAL opt1, QUAL opt2)
	{
		return ((t1.qualifiers[opt1.ordinal()] || t2.qualifiers[opt1.ordinal()]) && (t1.qualifiers[opt2.ordinal()] || t2.qualifiers[opt2.ordinal()]));
	} 

	private boolean typeComboExists(TypeBuilder t1, TypeBuilder t2, FOUND_TYPE opt1, FOUND_TYPE opt2)
	{
		return ((t1.foundTypes[opt1.ordinal()] ^ t2.foundTypes[opt1.ordinal()]) && (t1.foundTypes[opt2.ordinal()] ^ t2.foundTypes[opt2.ordinal()]));
	} 


private boolean isValidTypes(TypeBuilder t1, TypeBuilder t2)
{
	for (int i = 0; i < NUM_TYPES; ++i)
		for (int j = 0; j < NUM_TYPES; ++j)
			if (t1.foundTypes[i] && t2.foundTypes[j])
	            //long int	
				if (! (typeComboExists(t1,t2,FOUND_TYPE.seenLong,FOUND_TYPE.seenInt) || 
            //longlong int
            typeComboExists(t1,t2,FOUND_TYPE.seenLongLong,FOUND_TYPE.seenInt) ||
            //long double
            typeComboExists(t1,t2,FOUND_TYPE.seenLong,FOUND_TYPE.seenDouble) ||
            //float complex
            typeComboExists(t1,t2,FOUND_TYPE.seenFloat,FOUND_TYPE.seenComplex) ||
            //double complex
            typeComboExists(t1,t2,FOUND_TYPE.seenDouble,FOUND_TYPE.seenComplex) ||
            //long double complex
            (typeComboExists(t1,t2,FOUND_TYPE.seenDouble,FOUND_TYPE.seenComplex) && 
						(t1.foundTypes[FOUND_TYPE.seenLong.ordinal()] ^ t2.foundTypes[FOUND_TYPE.seenLong.ordinal()]) )))
					return false;
	return true;
}

  public TypeBuilder combine(TypeBuilder with) {
    // TUTORIAL: this is where all the logic for combining specifiers
    // will go

    // this copy might be able to be optimized away, if we know that
    // the reference to the semantic value won't be used again, e.g.,
    // by another subparser
    TypeBuilder result = new TypeBuilder(this);
    
    // checks for mutually-exclusive qualifiers
 if (qualComboExists(result, with, QUAL.isStatic, QUAL.isExtern) ||
        qualComboExists(result, with, QUAL.isStatic, QUAL.isAuto) ||
        qualComboExists(result, with, QUAL.isAuto, QUAL.isExtern) ||
        qualComboExists(result, with, QUAL.isAuto, QUAL.isRegister) ||
				qualComboExists(result, with, QUAL.isStatic, QUAL.isRegister) ||
        qualComboExists(result, with, QUAL.isRegister, QUAL.isExtern) ||
        qualComboExists(result, with, QUAL.isThreadlocal, QUAL.isAuto) ||
        qualComboExists(result, with, QUAL.isThreadlocal, QUAL.isRegister))

      isTypeError = true;
  
    // checks for variables with inline specifier
    if ((result.type.isVariable() || with.type.isVariable()) && (result.qualifiers[QUAL.isInline.ordinal()] || with.qualifiers[QUAL.isInline.ordinal()]))
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
          // ensures that we don't allow long long int int
          if (result.foundTypes[FOUND_TYPE.seenInt.ordinal()])
            result.isTypeError = true;
          else {
            System.err.println("[INFO] found a valid type: long long");
            result.type = NumberT.LONG_LONG;
          }
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
