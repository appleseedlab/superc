package xtc.lang.cpp;
import java.util.LinkedList;
import java.util.List;
import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.VoidT;
import xtc.type.UnitT;
import xtc.type.AliasT;
import xtc.type.StructT;
import xtc.type.VariableT;
import xtc.Constants;

/**
 * A type specific for a single configuration.  This is used to build
 * the type specifier during parsing.
 */
public class TypeBuilder {
    Type type; // void, char, short, int, long, float, double, SUE, typedefname
    enum QUAL {isAuto, isConst, isVolatile, isExtern, isStatic, isRegister, isThreadLocal,
	       isInline, isSigned, isUnsigned, isTypedef}
    final int NUM_QUALS = 12;
    enum FOUND_TYPE {seenVoid, seenInt, seenLong, seenLongLong, seenChar, seenShort, seenFloat,
                     seenDouble, seenComplex, seenTypedefType, seenStructReference, seenStructDefinition}
    final int NUM_TYPES = 12;
    // note: these can appear in any order (in the source file), and they will be initialized to false                                                                        /*boolean isAuto;
  boolean qualifiers[] = new boolean[NUM_QUALS];
  boolean foundTypes[] = new boolean[NUM_TYPES];

    List<String> attributes;

    boolean isTypeError;

    AliasT typedefType;  // used with seenTypedefType

    // used with seenStructDefinition, seenStructReference
    String structTag;  
    String structRenamedTag;
    boolean structIsAnon;  // is the struct anonymous, so don't print tag
    List<Declaration> structMembers;  // null for seenStructReference
    StructT structType;

    public String attributesToString() {
	if (attributes == null)
	    return "";
	return String.join(" ", attributes);
    }

    public String toString() {
      if (isTypeError) {
        throw new IllegalStateException("invalid type specifiers cannot be printed as a string");
      }
	StringBuilder sb = new StringBuilder();

	// TODO: check if the order of these matters

	if (qualifiers[QUAL.isTypedef.ordinal()])
	    sb.append("typedef ");
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
	    sb.append("inline ");
	if (qualifiers[QUAL.isSigned.ordinal()])
	    sb.append("signed ");
	if (qualifiers[QUAL.isUnsigned.ordinal()])
	    sb.append("unsigned ");

      // TODO: check that only one seen is here

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
	if (foundTypes[FOUND_TYPE.seenVoid.ordinal()])
	    sb.append("void ");
	if (foundTypes[FOUND_TYPE.seenTypedefType.ordinal()])
      sb.append(typedefType.getName());
    if (foundTypes[FOUND_TYPE.seenStructReference.ordinal()]) {
      sb.append("struct ");
      // struct refs can't be anonymous
      sb.append(structRenamedTag);
    }
    if (foundTypes[FOUND_TYPE.seenStructDefinition.ordinal()]) {
      sb.append("struct ");
      if (! this.structIsAnon) {
        sb.append(structRenamedTag);
        sb.append(" ");
      }
      sb.append("{\n");
      for (Declaration declaration : this.structMembers) {
        sb.append(declaration.toString());
        sb.append(";\n");
      }
      sb.append("}");
    }
	sb.append(attributesToString());

	return sb.toString();
    }

  // collects all information in the typebuilder and generates the corresponding type
  public Type toType() {
      if (isTypeError) {
        throw new IllegalStateException("invalid type specifiers do not have a type");
      }
    // NOTE: .combine() already checked for invalid combinations while merging typebuilders
    if (foundTypes[FOUND_TYPE.seenLongLong.ordinal()]) {
	    if (qualifiers[QUAL.isUnsigned.ordinal()])
        type = new IntegerT(NumberT.Kind.U_LONG_LONG); // unsigned long long
	    else
        type = new IntegerT(NumberT.Kind.LONG_LONG); // long long
    } else if (foundTypes[FOUND_TYPE.seenLong.ordinal()]) {
	    if (foundTypes[FOUND_TYPE.seenInt.ordinal()])
        if (qualifiers[QUAL.isUnsigned.ordinal()])
          type = new IntegerT(NumberT.Kind.LONG); // unsigned long
        else if (qualifiers[QUAL.isSigned.ordinal()])
          type = new IntegerT(NumberT.Kind.LONG); // signed long
        else
          type = new IntegerT(NumberT.Kind.LONG); // long
	    else if (foundTypes[FOUND_TYPE.seenDouble.ordinal()]) {
        if (foundTypes[FOUND_TYPE.seenComplex.ordinal()])
          type = new FloatT(NumberT.Kind.LONG_DOUBLE_COMPLEX); // long double complex
        else
          type = new FloatT(NumberT.Kind.LONG_DOUBLE); // long double
	    }
    } else if (foundTypes[FOUND_TYPE.seenComplex.ordinal()]) {
	    if (foundTypes[FOUND_TYPE.seenDouble.ordinal()])
        type = new FloatT(NumberT.Kind.DOUBLE_COMPLEX); // double complex
	    else
        type = new FloatT(NumberT.Kind.FLOAT_COMPLEX); // float complex
    } else if (foundTypes[FOUND_TYPE.seenFloat.ordinal()]) {
	    type = new FloatT(NumberT.Kind.FLOAT); // float
    } else if (foundTypes[FOUND_TYPE.seenDouble.ordinal()]) {
	    type = new FloatT(NumberT.Kind.DOUBLE); // double
    } else if (foundTypes[FOUND_TYPE.seenInt.ordinal()]) {
	    if (qualifiers[QUAL.isUnsigned.ordinal()])
        type = new IntegerT(NumberT.Kind.U_INT); // unsigned int
	    else if (qualifiers[QUAL.isSigned.ordinal()])
        type = new IntegerT(NumberT.Kind.U_CHAR); // signed int
	    else
        type = new IntegerT(NumberT.Kind.INT); // int
    } else if (foundTypes[FOUND_TYPE.seenChar.ordinal()]) {
	    if (qualifiers[QUAL.isSigned.ordinal()])
        type = new IntegerT(NumberT.Kind.S_CHAR); // signed char
	    else if (qualifiers[QUAL.isUnsigned.ordinal()])
        type = new IntegerT(NumberT.Kind.U_CHAR); // unsigned char
	    else
        type = new IntegerT(NumberT.Kind.CHAR); // char
    } else if (foundTypes[FOUND_TYPE.seenShort.ordinal()]) {
	    if (qualifiers[QUAL.isUnsigned.ordinal()])
        type = new IntegerT(NumberT.Kind.U_SHORT); // unsigned short
	    else
        type = new IntegerT(NumberT.Kind.SHORT); // short
    } else if (foundTypes[FOUND_TYPE.seenTypedefType.ordinal()])
	    {
        type = typedefType;
      } else if (foundTypes[FOUND_TYPE.seenVoid.ordinal()]) {
      type = new VoidT();
    }
    else if (foundTypes[FOUND_TYPE.seenStructReference.ordinal()]) {
      type = this.structType;
    }
    else if (foundTypes[FOUND_TYPE.seenStructDefinition.ordinal()]) {
      type = this.structType;
    }
    else{
	    System.err.println("ERROR: unsupported type found");
	    System.exit(1);
    }

    // adds the qualifiers to the type
    if (qualifiers[QUAL.isAuto.ordinal()])
	    type.addAttribute(Constants.ATT_STORAGE_AUTO);
    if (qualifiers[QUAL.isConst.ordinal()])
	    type.addAttribute(Constants.ATT_CONSTANT);
    if (qualifiers[QUAL.isVolatile.ordinal()])
	    type.addAttribute(Constants.ATT_VOLATILE);
    if (qualifiers[QUAL.isExtern.ordinal()])
	    type.addAttribute(Constants.ATT_STORAGE_EXTERN);
    if (qualifiers[QUAL.isStatic.ordinal()])
	    type.addAttribute(Constants.ATT_STORAGE_STATIC);
    if (qualifiers[QUAL.isRegister.ordinal()])
	    type.addAttribute(Constants.ATT_STORAGE_REGISTER);
    if (qualifiers[QUAL.isThreadLocal.ordinal()])
	    type.addAttribute(Constants.ATT_THREAD_LOCAL);
    if (qualifiers[QUAL.isInline.ordinal()])
	    type.addAttribute(Constants.ATT_INLINE);
    if (qualifiers[QUAL.isTypedef.ordinal()])
	    type.addAttribute(Constants.ATT_STORAGE_TYPEDEF);

    return type;
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
	    qualifiers[QUAL.isConst.ordinal()] = true;
	else if (x.equals("volatile"))
	    qualifiers[QUAL.isVolatile.ordinal()] = true;
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
	else if (x.equals("typedef"))
	    addQual(QUAL.isTypedef);
	else if (x.equals("int"))
	    addType(FOUND_TYPE.seenInt);
	else if (x.equals("long"))
    if (foundTypes[FOUND_TYPE.seenLong.ordinal()]){
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
  else if (x.equals("void"))
	    addType(FOUND_TYPE.seenVoid);
	else {
	    attributes.add(x);
	}
    }

  /**
   * Create a new TypeBuilder with a single type qualifier.
   */
    public TypeBuilder(String qualifier) {
      this();
	add(qualifier);
    }

    // creates a new typebuilder using only a type
    public TypeBuilder(Type type) {
      this();
	// set the proper foundTypes flag

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
  } else if (type instanceof VoidT) {
      foundTypes[FOUND_TYPE.seenVoid.ordinal()] = true;
  }

	this.type = type;
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
	typedefType = null;
      structTag = null;
      structRenamedTag = null;
      structIsAnon = false;
      structMembers = null;
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
    typedefType = old.typedefType;
      structTag = old.structTag;
      structRenamedTag = null;
      structIsAnon = old.structIsAnon;
      structMembers = old.structMembers;
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
    // not allowed to have two struct refs/defs
    if (typeComboExists(t1,t2,FOUND_TYPE.seenStructReference,FOUND_TYPE.seenStructReference)
        || typeComboExists(t1,t2,FOUND_TYPE.seenStructReference,FOUND_TYPE.seenStructDefinition)
        || typeComboExists(t1,t2,FOUND_TYPE.seenStructDefinition,FOUND_TYPE.seenStructDefinition)
        || typeComboExists(t1,t2,FOUND_TYPE.seenStructDefinition,FOUND_TYPE.seenStructDefinition)) {
      return false;
    }
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
        qualComboExists(result, with, QUAL.isThreadLocal, QUAL.isRegister) ||
        qualComboExists(result, with, QUAL.isUnsigned, QUAL.isSigned) ||
        qualComboExists(result, with, QUAL.isTypedef, QUAL.isStatic) ||
        qualComboExists(result, with, QUAL.isTypedef, QUAL.isAuto) ||
        qualComboExists(result, with, QUAL.isTypedef, QUAL.isExtern) ||
        qualComboExists(result, with, QUAL.isTypedef, QUAL.isRegister))
	    result.isTypeError = true;

    //invalid if signed/unsigned with float/double
    if ((result.qualifiers[QUAL.isSigned.ordinal()] || with.qualifiers[QUAL.isSigned.ordinal()] ||
         result.qualifiers[QUAL.isUnsigned.ordinal()] || with.qualifiers[QUAL.isUnsigned.ordinal()]) &&
        (result.foundTypes[FOUND_TYPE.seenFloat.ordinal()] || with.foundTypes[FOUND_TYPE.seenFloat.ordinal()] ||
         result.foundTypes[FOUND_TYPE.seenDouble.ordinal()] || with.foundTypes[FOUND_TYPE.seenDouble.ordinal()]))
	    result.isTypeError = true;

    if (!isValidTypes(result, with))
	    result.isTypeError = true;

    for (int i = 0; i < NUM_QUALS; ++i)
	    if (with.qualifiers[i])
        if (i == QUAL.isConst.ordinal() || i == QUAL.isVolatile.ordinal())
          result.qualifiers[i] = true;
        else
          result.addQual(QUAL.values()[i]);
    for (int i = 0; i < NUM_TYPES; ++i){
      if (with.foundTypes[i] && i != FOUND_TYPE.seenLong.ordinal()){
        result.addType(FOUND_TYPE.values()[i]);
      }
      else if (with.foundTypes[i] && i == FOUND_TYPE.seenLong.ordinal()){
        if (result.foundTypes[i])	{
          result.foundTypes[FOUND_TYPE.seenLong.ordinal()] = false;
          result.foundTypes[FOUND_TYPE.seenLongLong.ordinal()] = true;
        }
        else
          result.foundTypes[FOUND_TYPE.seenLong.ordinal()] = true;
      }
    }
    result.isTypeError = result.isTypeError || with.isTypeError;
    result.typedefType = (foundTypes[FOUND_TYPE.seenTypedefType.ordinal()] ? typedefType : with.typedefType);
      result.structTag = (foundTypes[FOUND_TYPE.seenStructDefinition.ordinal()] ? structTag : with.structTag);
      result.structRenamedTag = (foundTypes[FOUND_TYPE.seenStructDefinition.ordinal()] ? structRenamedTag : with.structRenamedTag);
      result.structMembers = (foundTypes[FOUND_TYPE.seenStructReference.ordinal()] ? structMembers : with.structMembers);
      result.structIsAnon = (foundTypes[FOUND_TYPE.seenStructReference.ordinal()] ? structIsAnon : with.structIsAnon);
    return result;
  }

  public boolean isTypedef()
  {
    return qualifiers[QUAL.isTypedef.ordinal()];
  }

  /**
   * Adds a type alias (via a typedefname) to this specifier.
   *
   * @param type The type alias.
   */
  public void setTypedef(AliasT alias)
  {
    foundTypes[FOUND_TYPE.seenTypedefType.ordinal()] = true;
    typedefType = alias;
  }

  /**
   * Adds a tagged struct with its renaming.
   */
  protected void setStructDefinition(String tag, String renamedtag, List<Declaration> members) {
    setStructDefinition(tag, renamedtag, members, false);
  }

  /**
   * Adds an anonymous struct.  For the tag, use the symbol tabl's
   * freshName("tag") method.  Anonymous structs don't need renaming,
   * since the name is not printed out during transformation.
   */
  protected void setStructDefinition(String tag, List<Declaration> members) {
    setStructDefinition(tag, tag, members, true);
  }

  /**
   * Adds a struct specifier to this type.
   */
  protected void setStructDefinition(String tag, String renamedtag, List<Declaration> members, boolean isAnon) {
    // make sure no other types are turned on when a struct def or ref is used
    for (int i = 0; i < NUM_TYPES; i++) {
      if (foundTypes[i]) {
        isTypeError = true;
      }
    }
    foundTypes[FOUND_TYPE.seenStructDefinition.ordinal()] = true;
    this.structTag = tag;
    this.structRenamedTag = renamedtag;
    this.structMembers = members;
    this.structIsAnon = isAnon;

    System.err.println("TODO: check that all members have different names, don't have type errors themselves, and rename selfrefs");
    List<VariableT> memberlist = new LinkedList<VariableT>();
    for (Declaration declaration : this.structMembers) {
      if (declaration.hasTypeError()) {
        this.isTypeError = true;
        // TODO: this should be caught by toString
      } else {
        VariableT member = VariableT.newField(declaration.getType(),
                                              declaration.getName());
        memberlist.add(member);
      }
      // TODO: use Variable.newBitfield()
    }

    // TODO: recursively go through the struct fields and
    // (1) rename recursive struct references
    // (2) check for redeclaration of struct

    // TODO: go through the fields and
    // (1) check that all members have different names
    // (2) check whether any members have a type error themselves (making the struct type an error)
    

    
    // the type in the symtab should have the original tag name, so we
    // can look up and find the struct appropriate for the declared
    // symbol's presence condition.
    this.structType = new StructT(tag, memberlist);
  }

  /**
   * Adds a struct specifier to this type.
   */
  public void setStructReference(String tag, String renamedtag) {
    // make sure no other types are turned on when a struct def or ref is used
    for (int i = 0; i < NUM_TYPES; i++) {
      if (foundTypes[i]) {
        isTypeError = true;
      }
    }
    foundTypes[FOUND_TYPE.seenStructReference.ordinal()] = true;
    this.structTag = tag;
    this.structRenamedTag = renamedtag;
    this.structMembers = null;
    this.structIsAnon = false;
    this.structType = new StructT(tag);
  }

  /**
   * Marks this type builder as a type error.
   */
  public void setTypeError() {
    this.isTypeError = true;
  }

  /**
   * Returns true if the type specifier is invalid.
   */
  public boolean hasTypeError() {
    return isTypeError;
  }
}
