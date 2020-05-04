package xtc.lang.cpp;
import java.util.LinkedList;
import java.util.List;
import xtc.type.NumberT;
import xtc.type.Type;
import xtc.type.UnitT;

public class TypeBuilder {
  Type type; // void, char, short, int, long, float, double, SUE, typedef                        
    enum QUAL {isAuto, isConst, isVolatile, isExtern, isStatic, isRegister, isThreadLocal,
               isInline, isSigned, isUnsigned}
    final int NUM_QUALS = 11;
    enum FOUND_TYPE {seenInt, seenLong, seenLongLong, seenChar, seenShort, seenFloat, seenDouble,
                     seenComplex}
    final int NUM_TYPES = 8;
    // note: these can appear in any order (in the source file), and they will be initialized to false                                                                        /*boolean isAuto;                                                                                           
    boolean qualifiers[] = new boolean[NUM_QUALS];
    boolean foundTypes[] = new boolean[NUM_TYPES];
    
    List<String> attributes;
    
    boolean isTypeError;
    
    public String attributesToString() {
	if (attributes == null)
	    return "";
	return String.join(" ", attributes);
    }

  public String toString() {
      if (isTypeError) {
	  return "ERROR:";
      }
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
    if (qualifiers[QUAL.isThreadLocal.ordinal()])
      sb.append("__thread ");
    if (qualifiers[QUAL.isInline.ordinal()])
      sb.append("inline");
    if (qualifiers[QUAL.isSigned.ordinal()])
      sb.append("signed");
    if (qualifiers[QUAL.isUnsigned.ordinal()])
      sb.append("unsigned");

    if (foundTypes[FOUND_TYPE.seenLong.ordinal()])
	sb.append("long ");
    if (foundTypes[FOUND_TYPE.seenLongLong.ordinal()])
	sb.append("long long ");
    if (foundTypes[FOUND_TYPE.seenChar.ordinal()])
	sb.append("char ");
    if (foundTypes[FOUND_TYPE.seenShort.ordinal()])
	sb.append("short ");
    if (foundTypes[FOUND_TYPE.seenInt.ordinal()])
	sb.append("int ");
    if (foundTypes[FOUND_TYPE.seenFloat.ordinal()])
	sb.append("float ");
    if (foundTypes[FOUND_TYPE.seenDouble.ordinal()])
	sb.append("double ");
    if (foundTypes[FOUND_TYPE.seenComplex.ordinal()])
	sb.append("complex ");
    
    sb.append(attributesToString());

    return sb.toString();
  }

  public Type toType() {
      return type; // placeholder
      // TODO: create the type based on all of the fields, then return that.
  }


    private void addQual(QUAL q){
	if(qualifiers[q.ordinal()])
	    isTypeError = true;
        else
	    qualifiers[q.ordinal()] = true;
    }
    private void addType(FOUND_TYPE f){
	if(foundTypes[f.ordinal()])
	    isTypeError = true;
        else
	    foundTypes[f.ordinal()] = true;
    }
    
    private void add(String x) {
	if (x.equals("auto"))
	    addQual(QUAL.isAuto);
	else if (x.equals("const"))
	    addQual(QUAL.isConst);
	else if (x.equals("volatile"))
	    addQual(QUAL.isVolatile);
	else if (x.equals("extern"))
	    addQual(QUAL.isExtern);
	else if (x.equals("static"))
	    addQual(QUAL.isStatic);
	else if (x.equals("register"))
	    addQual(QUAL.isRegister);
	else if (x.equals("__thread"))
	    addQual(QUAL.isThreadLocal);
	else if (x.equals("inline"))
	    addQual(QUAL.isInline);
	else if (x.equals("signed"))
	    addQual(QUAL.isSigned);
	else if (x.equals("unsigned"))
	    addQual(QUAL.isUnsigned);
        else if (x.equals("int"))
	    addType(FOUND_TYPE.seenInt);
	else if (x.equals("long"))
	    if (foundTypes[FOUND_TYPE.seenLong.ordinal()])
		{
		    foundTypes[FOUND_TYPE.seenLong.ordinal()] = false;
		    addType(FOUND_TYPE.seenLongLong);
		}
	    else
		addType(FOUND_TYPE.seenLong);
	else if (x.equals("char"))
	    addType(FOUND_TYPE.seenChar);
	else if (x.equals("short"))
	    addType(FOUND_TYPE.seenShort);
	else if (x.equals("float"))
	    addType(FOUND_TYPE.seenFloat);
	else if (x.equals("double"))
	    addType(FOUND_TYPE.seenDouble);
	else if (x.equals("complex"))
	    addType(FOUND_TYPE.seenComplex);
	else {
	    attributes.add(x);
	}
    }
     
    
  public TypeBuilder(TypeBuilder old, String name) {
    type = old.type;
    for (int i = 0; i < NUM_QUALS; ++i)
	qualifiers[i] = old.qualifiers[i];
    attributes = new LinkedList<String>(old.attributes);    
    isTypeError = old.isTypeError;

    add(name);
  }

  // creates a new typebuilder using a string (which is NOT a type)
  public TypeBuilder(String name) {
    type = new UnitT();
    attributes = new LinkedList<String>();
    for (int i = 0; i < NUM_QUALS; ++i)
	qualifiers[i] = false;
    for (int i = 0; i < NUM_TYPES; ++i)
	foundTypes[i] = false;
    isTypeError = false;
    add(name);
  }

  // creates a new typebuilder using only a type
  public TypeBuilder(Type type) {
      // set the proper foundTypes flag

      for (int i = 0; i < NUM_QUALS; ++i)
		  qualifiers[i] = false;
      for (int i = 0; i < NUM_TYPES; ++i)
		  foundTypes[i] = false;

      if (type.isNumber()) {
      switch (((NumberT) type).getKind()) {
        case INT:
          foundTypes[FOUND_TYPE.seenInt.ordinal()] = true;
          break;
        case LONG:
          foundTypes[FOUND_TYPE.seenLong.ordinal()] = true;
          break;
        case LONG_LONG:
          foundTypes[FOUND_TYPE.seenLongLong.ordinal()] = true;
          break;
        case CHAR:
          foundTypes[FOUND_TYPE.seenChar.ordinal()] = true;
          break;
        case SHORT:
          foundTypes[FOUND_TYPE.seenShort.ordinal()] = true;
          break;
        case FLOAT:
          foundTypes[FOUND_TYPE.seenFloat.ordinal()] = true;
          break;
        case DOUBLE:
          foundTypes[FOUND_TYPE.seenDouble.ordinal()] = true;
          break;
	  // NOTE: complex is not a complete type, so this is not possible:
	  /*case COMPLEX:
          foundTypes[FOUND_TYPE.seenComplex.ordinal()] = true;
          break;*/
        
        default:
          System.err.println("ERROR: unknown type passed to TypeBuilder(Type type)");
          System.exit(1);
      }
    
    }

    this.type = type;
    attributes = new LinkedList<String>();
    isTypeError = false;
  }

  // copy constructor that changes type (should be used whenever a type is found)
  // the default constructor should be used before this ever gets called.
  public TypeBuilder(TypeBuilder old, Type type) {
    // copy constructor that changes the type
    if (old.type instanceof UnitT) {
      this.type = type;
      for (int i = 0; i < NUM_QUALS; ++i)
	  qualifiers[i] = old.qualifiers[i];
      attributes = new LinkedList<String>(old.attributes);
      isTypeError = old.isTypeError;
    }
    
  }

  // sets all flags to false and type starts as unit
  public TypeBuilder() {
    type = new UnitT();
    for (int i = 0; i < NUM_QUALS; ++i)
		  qualifiers[i] = false;
    for (int i = 0; i < NUM_TYPES; ++i)
		  foundTypes[i] = false;
    attributes = new LinkedList<String>();
    isTypeError = false;
  }

  // copy constructor creates a deep copy
  public TypeBuilder(TypeBuilder old) {
      type = old.type.copy();
      for (int i = 0; i < NUM_QUALS; ++i)
	  qualifiers[i] = old.qualifiers[i];
      for (int i = 0; i < NUM_TYPES; ++i)
	  foundTypes[i] = old.foundTypes[i];
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
	//Notes: While long complex isn't a complete type, it's potentially valid if later joined with double.
	// Since complex double and long double are valid on their own, there is no need to consider the tuple of long complex and double
	//since they are all individually validated by the other types.
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
			   //long complex
			   (typeComboExists(t1,t2,FOUND_TYPE.seenLong,FOUND_TYPE.seenComplex)) ||
			   //long long
			   (i == j && i == FOUND_TYPE.seenLong.ordinal()) ))
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
        qualComboExists(result, with, QUAL.isThreadLocal, QUAL.isAuto) ||
        qualComboExists(result, with, QUAL.isThreadLocal, QUAL.isRegister))
	result.isTypeError = true;
  
    // checks for variables with inline specifier
    if ((result.type.isVariable() || with.type.isVariable()) && (result.qualifiers[QUAL.isInline.ordinal()] || with.qualifiers[QUAL.isInline.ordinal()]))
      result.isTypeError = true;

    if (!isValidTypes(result, with))
	result.isTypeError = true;
    
	for (int i = 0; i < NUM_QUALS; ++i)
	    if (with.qualifiers[i])
		result.addQual(QUAL.values()[i]);
	for (int i = 0; i < NUM_TYPES; ++i)
	    if (with.foundTypes[i] && i != FOUND_TYPE.seenLong.ordinal())
		result.addType(FOUND_TYPE.values()[i]);
	    else if (with.foundTypes[i] && i == FOUND_TYPE.seenLong.ordinal())
		{
		    result.foundTypes[FOUND_TYPE.seenLong.ordinal()] = false;
		    result.foundTypes[FOUND_TYPE.seenLongLong.ordinal()] = true;
		}
		
	return result;
  }
}
