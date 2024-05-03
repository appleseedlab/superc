package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

import xtc.tree.Attribute;

import xtc.type.C;
import xtc.type.Type;
import xtc.type.Type.Tag;
import xtc.type.BooleanT;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.VoidT;
import xtc.type.UnitT;
import xtc.type.AliasT;
import xtc.type.StructT;
import xtc.type.VariableT;
import xtc.type.InternalT;
import xtc.type.ErrorT;
import superc.cdesugarer.CActions.LineNumbers;

import xtc.Constants;

import superc.core.Syntax;
import superc.core.Syntax.Text;

/**
 * A C type specifier.  Adapted from xtc.lang.CAnalyzer.Specifiers.
 * The visitors are instead semantic actions in the parser.
 */
class TypeSpecifier {
  /** The transformation of this specifier. */
  List<Syntax> transformation;
  
  /** The type, if any. */
  protected Type type;

  /** The storage class attribute, if any. */
  private Attribute storage;

  /** The thread-local attribute, if any. */
  private Attribute threadlocal;

  /** The inline attribute, if any. */
  private Attribute function;

  /** Any other attributes. */
  private List<Attribute> attributes;


  // The internal state for tracking type specifiers.
  private boolean seenSigned;
  private boolean seenUnsigned;
  private boolean seenBool;
  private boolean seenChar;
  private boolean seenShort;
  private boolean seenInt;
  private int     longCount;
  private boolean seenFloat;
  private boolean seenDouble;
  private boolean seenComplex;

  /* Create a new, empty TypeSpecifier */
  public TypeSpecifier() {
    this.transformation = new LinkedList<Syntax>();
  }

  /** The copy constructor. */
  public TypeSpecifier(TypeSpecifier ts) {
    this.transformation = new LinkedList<Syntax>(ts.transformation);
    this.type = ts.type;
    this.storage = ts.storage;
    this.threadlocal = ts.threadlocal;
    this.function = ts.function;
    if (null != ts.attributes) this.attributes = new ArrayList<Attribute>(ts.attributes);
    this.seenSigned = ts.seenSigned;
    this.seenUnsigned = ts.seenUnsigned;
    this.seenBool = ts.seenBool;
    this.seenChar = ts.seenChar;
    this.seenShort = ts.seenShort;
    this.seenInt = ts.seenInt;
    this.longCount = ts.longCount;
    this.seenFloat = ts.seenFloat;
    this.seenDouble = ts.seenDouble;
    this.seenComplex = ts.seenComplex;
  }

  /**
   * This looks at the state of the specifier and builds an xtc type.
   *
   * @returns Type The xtc type.
   */
  public Type getType() {
    Type discovered_type;
    // Fill in the resulting type.
    if (null != this.type) {
      discovered_type = this.type;
    } else if (seenBool) {
      discovered_type = BooleanT.TYPE;
    } else if (seenChar) {
      if (seenUnsigned) {
        discovered_type = NumberT.U_CHAR;
      } else if (seenSigned) {
        discovered_type = NumberT.S_CHAR;
      } else {
        discovered_type = NumberT.CHAR;
      }
    } else if (seenShort) {
      if (seenUnsigned) {
        discovered_type = NumberT.U_SHORT;
      } else {
        discovered_type = NumberT.SHORT;
      }
    } else if (seenFloat) {
      if (seenComplex) {
        discovered_type = NumberT.FLOAT_COMPLEX;
      } else {
        discovered_type = NumberT.FLOAT;
      }
    } else if (seenDouble) {
      if (0 < longCount) {
        if (seenComplex) {
          discovered_type = NumberT.LONG_DOUBLE_COMPLEX;
        } else {
          discovered_type = NumberT.LONG_DOUBLE;
        }
      } else {
        if (seenComplex) {
          discovered_type = NumberT.DOUBLE_COMPLEX;
        } else {
          discovered_type = NumberT.DOUBLE;
        }
      }
    } else if (1 == longCount) {
      if (seenUnsigned) {
        discovered_type = NumberT.U_LONG;
      } else {
        discovered_type = NumberT.LONG;
      }
    } else if (1 < longCount) {
      if (seenUnsigned) {
        discovered_type = NumberT.U_LONG_LONG;
      } else {
        discovered_type = NumberT.LONG_LONG;
      }
    } else if (seenUnsigned) {
      discovered_type = NumberT.U_INT;
    } else if (seenSigned) {
      discovered_type = NumberT.S_INT;
    } else if (seenInt) {
      discovered_type = NumberT.INT;
    } else {
      discovered_type = C.IMPLICIT;
    }

    // Annotate the type.
    if ((! discovered_type.hasError()) && (null != attributes)) {
      discovered_type = discovered_type.annotate().attribute(attributes);
    }

    // TODO: do i need to do full annotation (i.e., typedef, inline, thread?)

    return discovered_type;
  }

  /**
   * This returns the desugared version of the specifier.  All users
   * of TypeSpecifier need to call addTransformation whenever calling
   * any visit methods or the setType method.  Type errors have not
   * string and cause an IllegalStateException.
   */
  public String toString() {
    if (getType().isError()) {
	return "error";
    } else {
      StringBuilder sb = new StringBuilder();
      for (Syntax token : transformation) {
        sb.append(token.getTokenText());
        sb.append(" ");
      }
      return sb.toString();
      }
  }

  public void addTransformation(Syntax token) {
    transformation.add(token);
  }

  public List<Syntax> getTokens() {
    return new LinkedList<Syntax>(transformation);
  }

  /**
   * Use another type specifier to trigger the visit methods of this
   * type specifier.
   *
   * @param other The other type specifier to use to update this specifier.
   */
  public void visit(TypeSpecifier other) {
    // typedefname
    // typeof
    // voidtype
    // vararglist
    if (null != other.type) {
      this.setType(other.type);
    }

    // auto
    // extern
    // register
    // static
    // typedef
    if (null != other.storage) {
      if (! testStorageClass()) {
        this.storage = other.storage;
      }
    }
    
    if (other.hasThreadLocal()) {
      this.visitThreadSpecifier();
    }

    if (other.hasInline()) {
      this.visitFunctionSpecifier();
    }

    // volatile
    // constant
    // restrict
    if (null != other.attributes) {
      this.visitAttributeSpecifier(other.attributes);
    }

    if (other.seenSigned) {
      this.visitSigned();
    }

    if (other.seenUnsigned) {
      this.visitUnsigned();
    }

    if (other.seenBool) {
      this.visitBool();
    }

    if (other.seenChar) {
      this.visitChar();
    }

    if (other.seenShort) {
      this.visitShort();
    }

    if (other.seenInt) {
      this.visitInt();
    }

    for (int i = 0; i < other.longCount; i++) {
      this.visitLong();
    }

    if (other.seenFloat) {
      this.visitFloat();
    }

    if (other.seenDouble) {
      this.visitDouble();
    }

    if (other.seenComplex) {
      this.visitComplex();
    }

    this.transformation.addAll(other.transformation);
  }

  /**
   * Get the base type.  The base type has been annotated with all
   * attributes besides the storage class and function specifier
   * attributes.
   *
   * @return The base type.
   */
  public Type getBaseType() {
    return type;
  }

  /**
   * Determine whether the base type is the default type.
   *
   * @return <code>true</code> if the base type is the default type.
   */
  public boolean isDefault() {
    return type.hasTag(Tag.INTEGER) &&
      type.resolve().hasAttribute(Constants.ATT_IMPLICIT);
  }

  /**
   * Determine whether the specifiers contain the specified
   * attribute.
   *
   * @param att The attribute.
   * @return <code>true</code> if the specifiers contain the
   *   specified attribute.
   */
  public boolean contains(Attribute att) {
    if ((null != attributes) && attributes.contains(att)) return true;
    if (att.equals(storage)) return true;
    if (att.equals(threadlocal)) return true;
    return att.equals(function);
  }

  /**
   * Determine whether the specifiers include any attributes besides
   * a function specifier, storage class, and thread-local
   * specifier.
   *
   * @return <code>true</code> if the specifiers include any
   *   attributes besides a function specifier, storage class, and
   *   thread-local specifier.
   */
  public boolean hasBaseAttributes() {
    return null != attributes;
  }

  /**
   * Determine whether the specifiers include a function specifier.
   *
   * @return <code>true</code> if the specifiers include a function
   *   specifier.
   */
  public boolean hasInline() {
    return null != function;
  }

  /**
   * Determine whether the specifiers include a thread-local
   * specifier.
   *
   * @return <code>true</code> if the specifiers include a
   *   thread-local specifier.
   */
  public boolean hasThreadLocal() {
    return null != threadlocal;
  }

  /**
   * Get the storage class.
   *
   * @return The storage class or <code>null</code> if the
   * specifiers do contain one.
   */
  public Attribute getStorageClass() {
    return storage;
  }

  /**
   * Annotate the specified base type.  This method annotates the
   * specified type with all attributes besides the storage class,
   * thread-local specifier, and function specifier attributes.
   *
   * @param base The base type.
   * @return The annnotated base type.
   */
  public Type annotateBase(Type base) {
    return (null != attributes)? base.attribute(attributes) : base;
  }

  /**
   * Annotate the specified full type.  This method annotates the
   * specified type with any storage class, thread-local specifier,
   * and function specifier attributes.
   *
   * @param full The full type.
   * @return The annotated full type.
   */
  public Type annotateFull(Type full) {
    // If the full type is the same type as the base type, wrap the
    // type with an annotated pseudo-type to prevent changes to the
    // base type across several declarations.
    if (null != storage || null != threadlocal || null != function) {
      if (type == full)        full = full.annotate();
      if (null != storage)     full = full.attribute(storage);
      if (null != threadlocal) full = full.attribute(threadlocal);
      if (null != function)    full = full.attribute(function);
    }
    return full;
  }

  /** Add the specified attribute. */
  protected void add(Attribute att) {
    if (null == attributes) {
      attributes = new ArrayList<Attribute>();
      attributes.add(att);
    } else if (! attributes.contains(att)) {
      attributes.add(att);
    }
  }

  /** Test for previous storage class specifier and report error. */
  protected boolean testStorageClass() {
    if (null == storage) {
      return false;
    } else {
      errorMsg("multiple storage classes in declaration specifiers");
      return true;
    }
  }

  /** Test for previous type. */
  protected boolean hasType() {
    return
      (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
       seenFloat || seenDouble || seenComplex ||
       (null != type));
  }

  /** Report error indicating multiple types. */
  protected void multipleTypes() {
    errorMsg("multiple data types in declaration specifiers");
    type = ErrorT.TYPE;
  }

  /** Process the auto specifier. */
  public void visitAutoSpecifier() {
    if (Constants.ATT_STORAGE_AUTO.equals(storage)) {
      errorMsg("duplicate 'auto'");
    } else if (! testStorageClass()) {
      storage = Constants.ATT_STORAGE_AUTO;
    }
  }
    
  /** Process the extern specifier. */
  public void visitExternSpecifier() {
    if (Constants.ATT_STORAGE_EXTERN.equals(storage)) {
      errorMsg("duplicate 'extern'");
    } else if (! testStorageClass()) {
      storage = Constants.ATT_STORAGE_EXTERN;

      if (null != threadlocal) {
        errorMsg("'__thread' before 'extern'");
      }
    }
  }
    
  /** Process the register specifier. */
  public void visitRegisterSpecifier() {
    if (Constants.ATT_STORAGE_REGISTER.equals(storage)) {
      errorMsg("duplicate 'register'");
    } else if (! testStorageClass()) {
      storage = Constants.ATT_STORAGE_REGISTER;
    }
  }
    
  /** Process the static specifier. */
  public void visitStaticSpecifier() {
    if (Constants.ATT_STORAGE_STATIC.equals(storage)) {
      errorMsg("duplicate 'static'");
    } else if (! testStorageClass()) {
      storage = Constants.ATT_STORAGE_STATIC;

      if (null != threadlocal) {
        errorMsg("'__thread' before 'static'");
      }
    }
  }
    
  /** Process the typedef specifier. */
  public void visitTypedefSpecifier() {
    if (Constants.ATT_STORAGE_TYPEDEF.equals(storage)) {
      errorMsg("duplicate 'typedef'");
    } else if (! testStorageClass()) {
      storage = Constants.ATT_STORAGE_TYPEDEF;
    }
  }

  /** Process the thread-local specifier. */
  public void visitThreadSpecifier() {
    if (null != threadlocal) {
      errorMsg("duplicate '__thread'");
    } else {
      threadlocal = Constants.ATT_THREAD_LOCAL;
    }
  }

  /** Process the typeof specifier. */
  public void visitTypeofSpecifier(Type t) {
    if (hasType()) {
      multipleTypes();
    } else {
      // Strip any annotations from the type, but do keep the
      // qualifiers.
      if (t.hasEnum()) {
        type = DesugarOps.cOps.qualify(t.toEnum(), t);
      } else {
        type = DesugarOps.cOps.qualify(t.resolve(), t);
      }
    }
  }
    
  /** Process the volatile qualifier. */
  public void visitVolatileQualifier() {
    add(Constants.ATT_VOLATILE);
  }
    
  /** Process the constant qualifier. */
  public void visitConstantQualifier() {
    add(Constants.ATT_CONSTANT);
  }
    
  /** Process the restrict qualifier. */
  public void visitRestrictQualifier() {
    add(Constants.ATT_RESTRICT);
  }
    
  /** Process the function specifier. */
  public void visitFunctionSpecifier() {
    if (null == function) {
      function = Constants.ATT_INLINE;
    }
  }
    
  /** Process the signed type specifier. */
  public void visitSigned() {
    if (seenUnsigned) {
      seenSigned = true;
      errorMsg("both 'signed' and 'unsigned' in declaration specifiers");
    } else if (seenSigned) {
      errorMsg("duplicate 'signed'");
    } else {
      seenSigned = true;
    }
  }
    
  /** Process the unsigned type specifier. */
  public void visitUnsigned() {
    if (seenSigned) {
      seenUnsigned = true;
      errorMsg("both 'signed' and 'unsigned' in declaration specifiers");
    } else if (seenUnsigned) {
      errorMsg("duplicate 'unsigned'");
    } else {
      seenUnsigned = true;
    }
  }
    
  /** Process the boolean type specifier. */
  public void visitBool() {
    if (hasType()) {
      multipleTypes();
    } else {
      seenBool = true;
    }
  }
    
  /** Process the char type specifier. */
  public void visitChar() {
    if (hasType()) {
      multipleTypes();
    } else {
      seenChar = true;
    }
  }
    
  /** Process the short specifier. */
  public void visitShort() {
    if (seenBool || seenChar || seenShort || (0 < longCount) ||
        seenFloat || seenDouble || seenComplex ||
        (null != type)) {
      multipleTypes();
    } else {
      seenShort = true;
    }
  }
    
  /** Process the int type specifier. */
  public void visitInt() {
    if (seenBool || seenChar || seenInt ||
        seenFloat || seenDouble || seenComplex ||
        (null != type)) {
      multipleTypes();
    } else {
      seenInt = true;
    }
  }
    
  /** Process the long type specifier. */
  public void visitLong() {
    if (seenBool || seenChar || seenShort || (1 < longCount) ||
        seenFloat ||
        ((seenDouble || seenComplex) &&
         (0 < longCount)) ||
        (null != type)) {
      multipleTypes();
    } else {
      longCount++;
    }
  }
    
  /** Process the float type specifier. */
  public void visitFloat() {
    if (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
        seenDouble ||
        (null != type)) {
      multipleTypes();
    } else if (seenSigned || seenUnsigned ){
      errorMsg("can't have signed/unsigned floating point value.");
    } else {
      seenFloat = true;
    }
  }
    
  /** Process the double type specifier. */
  public void visitDouble() {
    if (seenBool || seenChar || seenShort || seenInt || (1 < longCount) ||
        seenFloat ||
        (null != type)) {
      multipleTypes();
    } else if (seenSigned || seenUnsigned ){
      errorMsg("can't have signed/unsigned floating point value.");
    } else {
      seenDouble = true;
    }
  }
    
  /** Process the complex type specifier. */
  public void visitComplex() {
    if (seenBool || seenChar || seenShort || seenInt || (1 < longCount) ||
        (null != type)) {
      multipleTypes();
    } else {
      seenComplex = true;
    }
  }

  /** Process the void type specifier. */
  public void visitVoidTypeSpecifier() {
    if (hasType()) {
      multipleTypes();
    } else {
      type = VoidT.TYPE;
    }
  }
    
  /** Process the variable argument list specifier. */
  public void visitVarArgListSpecifier() {
    if (hasType()) {
      multipleTypes();
    } else {
      type = InternalT.VA_LIST;
    }
  }
    
  /**
   * Process the attribute specifier.
   *
   * @param atts The list of Attribute.
   */
  public void visitAttributeSpecifier(List<Attribute> atts) {
    if (! atts.isEmpty()) {
      if (null == attributes) {
        attributes = atts;
      } else {
        attributes.addAll(atts);
      }
    }
  }
    
  /**
   * Set the type.  This is only used for typedefnames, and
   * struct/union/enum defs/refs.
   *
   * @param The renamed type alias.
   */
  public void setType(Type type) {
    if (hasType()) {
      multipleTypes();
    } else {
      this.type = type;
    }
  }

  /**
   * Report error.
   *
   * @param msg The error message.
   */
  protected void errorMsg(String msg) {
    // TODO: tie into error reporting
    System.err.println(msg);
    setError();
  }

  public void setError() {
    this.type = ErrorT.TYPE;
    this.transformation = new LinkedList<Syntax>();
    
  }

  public TypeSpecifier revertForwardRefs(List<String> references, String forwardRef, String rename) {
    TypeSpecifier toRet = new TypeSpecifier(this);
    toRet.type = type.revertForwardRef(references,forwardRef,rename);
    toRet.transformation = new LinkedList<Syntax>();
    for (Syntax s : transformation) {
      boolean found = false;
      for (String s2 : references) {
        if (s.getTokenText().equals(s2)) {
          found = true;
          break;
        }
      }
      if (found && s instanceof Text) {
        toRet.transformation.add(((Text)s).replaceText(forwardRef));
      } else {
        toRet.transformation.add(s);
      }
    }
    return toRet;
  }
}
