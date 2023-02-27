package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;

import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.VoidT;
import xtc.type.PointerT;
import xtc.type.ArrayT;
import xtc.type.FunctionT;
import xtc.type.VariableT;
import xtc.type.StructT;
import superc.core.PresenceConditionManager.PresenceCondition;
import superc.cdesugarer.Multiverse.Element;

/**
 * The superclass of all C declarator constructs.
 *
 * This is basically an AST for C declarators.  This class needs to do
 * three things:
 *
 * 1) preserve the original syntax for use in a renaming
 * transformation;
 *
 * 2) preserve type-relevant information for use in constructing the
 * symbol's type; and
 *
 * 3) enable renaming of the declarator's identifier.
 *
 * It does not yet support attributes or K&amp;R-style function
 * declarators.
 */
abstract class Declarator {
  /**
   * Get the identifier of this declarator, if any.  Abstract
   * declarators do not have a name.
   */
  abstract public String getName();

  /**
   * Returns true if the declarator has a name.
   */
  abstract public boolean hasName();

  /**
   * Create a new declarator with the new name.  Abstract declarators
   * do not have a name.
   */
  abstract public Declarator rename(String newName);

  /**
   * Create a new declarator with the new name.  Abstract declarators
   * do not have a name.
   */
  abstract public Type getType(Type type);

  /**
   * Returns true if any type builder contained in the declarator has
   * a type error.
   */
  abstract public boolean hasTypeError();

  /** Returns true if this is a EmptyDeclarator object. */
  public boolean isEmptyDeclarator() { return false; }
  
  /** Returns true if this is a ParenDeclarator object. */
  public boolean isParenDeclarator() { return false; }
  
  /** Returns true if this is a SimpleDeclarator object. */
  public boolean isSimpleDeclarator() { return false; }
  
  /** Returns true if this is a QualifiedPointerDeclarator object. */
  public boolean isQualifiedPointerDeclarator() { return false; }
  
  /** Returns true if this is a PointerDeclarator object. */
  public boolean isPointerAbstractDeclarator() { return false; }
  
  /** Returns true if this is a QualifiedPointerDeclarator object. */
  public boolean isQualifiedPointerAbstractDeclarator() { return false; }
  
  /** Returns true if this is a PointerDeclarator object. */
  public boolean isPointerDeclarator() { return false; }
  
  /** Returns true if this is a FunctionDeclarator object. */
  public boolean isFunctionDeclarator() { return false; }
  
  /** Returns true if this is a ParameterListDeclarator object. */
  public boolean isParameterListDeclarator() { return false; }
  
  /** Returns true if this is a ArrayAbstractDeclarator object. */
  public boolean isArrayDeclarator() { return false; }
  
  /** Returns true if this is a ArrayAbstractDeclarator object. */
  public boolean isArrayAbstractDeclarator() { return false; }

  /** Returns true if this is a BitFieldSizeDeclarator object. */
  public boolean isBitFieldSizeDeclarator() { return false; }

  /** Returns true if this is a NamedBitFieldSizeDeclarator object. */
  public boolean isNamedBitFieldSizeDeclarator() { return false; }

  public boolean isFlexible() { return false;}
  
  public String toString(int len) {
      return "ERROR: incompatible array length specifier";
    }
  
  public Declarator switchForwardRef(List<Type> oldParams, PresenceCondition cond, CContext scope) {
    System.err.println("Error: tried to switch forward reference parrams for non-function declarator");
    System.exit(1);
    return this;
  }
  
  public abstract String printType();
  /**
   * This empty declarator is used for abstract declarators that only
   * have a type.
   */
  public static class EmptyDeclarator extends Declarator {
    public EmptyDeclarator() {
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public Type getType(Type type) {
      return type;
    }

    public boolean hasTypeError() {
      return false;
    }

    @Override
    public boolean isEmptyDeclarator() { return true; }

    public String toString() {
      // empty declarators have no string
      return "";
    }

    public String printType() {
      return "";
    }
  }

  /**
   * This declarator is for preserving placement of parentheses.  It
   * is currently not used, since it causes issues with detecting
   * abstract postif declarators and is not needed since explicit
   * ordering of the output is done by always putting parentheses.
   */
  public static class ParenDeclarator extends Declarator {
    /**
     * The wrapped declarator.
     */
    protected final Declarator declarator;
    
    public ParenDeclarator(Declarator declarator) {
      this.declarator = declarator;
    }

    public String getName() {
      return declarator.getName();
    }

    public boolean hasName() {
      return declarator.hasName();
    }
    
    public Declarator rename(String newName) {
	return new ParenDeclarator(declarator.rename(newName));
    }

    public Type getType(Type type) {
      return declarator.getType(type);
    }

    public boolean hasTypeError() {
      return declarator.hasTypeError();
    }


    @Override
    public boolean isParenDeclarator() { return true; }

    public String toString() {
      String inner = declarator.toString();
      if (inner.equals(""))
        return "";
      return String.format("(%s)",inner);
    }
    public String toString(int len) {
      return String.format("(%s)", declarator.toString(len));
    }
    public String printType() {
      return String.format("(%s)", declarator.printType());
    }

    public boolean isFlexible() {
      return declarator.isFlexible();
    }
  }

  /**
   * A simple declarator just stores the name of the symbol.  This
   * symbol will be renamed during the desugaring transformation.
   */
  public static class SimpleDeclarator extends Declarator {
    /** The declarator's identifier. */
    protected final String name;

    public SimpleDeclarator(String name) {
      this.name = name;
    }

    public String getName() {
      return name;
    }

    public boolean hasName() {
      return true;
    }
    
    public Declarator rename(String newName) {
      return new SimpleDeclarator(newName);
    }

    public Type getType(Type type) {
      return type;
    }

    public boolean hasTypeError() {
      return false;
    }

    @Override
    public boolean isSimpleDeclarator() { return true; }

    public String toString() {
      return name;
    }
    public String printType() {
      return "";
    }
  }

  /**
   * A pointer declarator, which has another declarator nested inside of
   * it.
   */
  public static class PointerDeclarator extends Declarator {
    /** Points to this declarator. */
    protected final Declarator declarator;

    public PointerDeclarator(Declarator declarator) {
      this.declarator = declarator;
    }

    public String getName() {
      return declarator.getName();
    }

    public boolean hasName() {
      return declarator.hasName();
    }
    
    public Declarator rename(String newName) {
      return new PointerDeclarator(declarator.rename(newName));
    }

    public Type getType(Type type) {
      return declarator.getType(new PointerT(type));
    }

    public boolean hasTypeError() {
      return declarator.hasTypeError();
    }
  
    @Override
    public boolean isPointerDeclarator() { return true; }

    public String toString() {
      String inner = declarator.toString();
      if (inner.equals(""))
        return "*";
      return String.format("* (%s)", inner);  // preserve order of operations
    }
    
    public String toString(int len) {
      return String.format("* (%s)", declarator.toString(len));  // preserve order of operations
    }
    public String printType() {
      String inner = declarator.printType();
      if (inner.equals(""))
        return "*";
      return String.format("* (%s)", inner);  // preserve order of operations
    }

    public Declarator switchForwardRef(List<Type> oldParams, PresenceCondition cond, CContext scope) {
      return new PointerDeclarator(declarator.switchForwardRef(oldParams,cond,scope));
    }
  }

  /**
   * A qualified pointer declarator, which has another declarator nested
   * inside of it as well as a list of qualifiers.
   */
  public static class QualifiedPointerDeclarator extends Declarator {
    /** Points to this declarator. */
    protected final Declarator declarator;

    /** Qualifiers of this pointer. */
    protected final TypeSpecifier qualifiers;

    public QualifiedPointerDeclarator(Declarator declarator,
                                      TypeSpecifier qualifiers) {
      this.declarator = declarator;
      this.qualifiers = qualifiers;
    }

    public String getName() {
      return declarator.getName();
    }

    public boolean hasName() {
      return declarator.hasName();
    }
    
    public Declarator rename(String newName) {
      return new QualifiedPointerDeclarator(declarator.rename(newName), qualifiers);
    }

    public Type getType(Type type) {
      Type pointed = new PointerT(type);
      TypeSpecifier newts = new TypeSpecifier(qualifiers);
      newts.setType(pointed);
      return declarator.getType(newts.getType());
    }

    public boolean hasTypeError() {
      return qualifiers.getType().isError() || declarator.hasTypeError();
    }
  
    @Override
    public boolean isQualifiedPointerDeclarator() { return true; }

    public String toString() {
      // return String.format("* %s %s", qualifiers.toString(), declarator.toString());
      return String.format("* %s %s", qualifiers.toString(), declarator.toString());  // preserve order of operations
    }
    public String toString(int len) {
      // return String.format("* %s %s", qualifiers.toString(), declarator.toString());
      return String.format("* %s %s", qualifiers.toString(), declarator.toString(len));  // preserve order of operations
    }
    public String printType() {
      // return String.format("* %s %s", qualifiers.toString(), declarator.toString());
      return String.format("* %s %s", qualifiers.toString(), declarator.printType());  // preserve order of operations
    }
    public boolean isFlexible() {
      return declarator.isFlexible();
    }
  }

  /**
   * An abstract pointer declarator without an explicit declarator
   * that it points to.  It has no member fields, because it is an
   * abstract declarator.
   */
  public static class PointerAbstractDeclarator extends Declarator {
    public PointerAbstractDeclarator() {
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      // nothing to rename and its immutable, so return this class.
      return this;
    }

    public Type getType(Type type) {
      return new PointerT(type);
    }

    public boolean hasTypeError() {
      return false;
    }
  
    @Override
    public boolean isPointerAbstractDeclarator() { return true; }

    public String toString() {
      // TODO: double-check the position of parentheses around declarators
      return "*";
    }
    public String printType() {
      return "*";
    }
  }

  // note this uses TypeSpecifier, not a Multiverse, so the action needs to hoist, because TypeQualifiers returns a Multiverse
  /**
   * A qualified pointer declarator without an explicit declarator
   * that it points to.  It has no declarator field, because it is an
   * abstract declarator.
   */
  public static class QualifiedPointerAbstractDeclarator extends Declarator {
    /** Qualifiers, if any, of this pointer. */
    protected final TypeSpecifier qualifiers;

    public QualifiedPointerAbstractDeclarator(TypeSpecifier qualifiers) {
      this.qualifiers = qualifiers;
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      // nothing to rename and its immutable, so return this class.
      return this;
    }

    public Type getType(Type type) {
      Type pointed = new PointerT(type);
      TypeSpecifier newts = new TypeSpecifier(qualifiers);
      newts.setType(pointed);
      return newts.getType();
    }
    
    public boolean hasTypeError() {
      return qualifiers.getType().isError();
    }
  
    @Override
    public boolean isQualifiedPointerAbstractDeclarator() { return true; }

    public String toString() {
      return String.format("* %s", qualifiers.toString());
    }
    public String printType() {
      return String.format("* %s", qualifiers.toString());
    }
  }

  /**
   * An array declarator, which contains the declarator and an array
   * abstract declarator.
   */
  public static class ArrayDeclarator extends Declarator {
    /** The declarator that becomes an array. */
    protected final Declarator declarator;

    /** The array part of the declarator. */
    protected final ArrayAbstractDeclarator arrayabstractdeclarator;

    public ArrayDeclarator(Declarator declarator,
                           ArrayAbstractDeclarator arrayabstractdeclarator) {
      this.declarator = declarator;
      this.arrayabstractdeclarator = arrayabstractdeclarator;
    }

    public String getName() {
      return declarator.getName();
    }

    public boolean hasName() {
      return declarator.hasName();
    }
    
    public Declarator rename(String newName) {
      return new ArrayDeclarator(declarator.rename(newName),
                                 (ArrayAbstractDeclarator) arrayabstractdeclarator.rename(newName));
    }

    public Type getType(Type type) {
      // this an array of whatever the declarator is
      System.err.println("TODO: check correctness of array abstract declarator type");
      return declarator.getType(arrayabstractdeclarator.getType(type));
    }

    public boolean hasTypeError() {
      return declarator.hasTypeError() || arrayabstractdeclarator.hasTypeError();
    }

    @Override
    public boolean isArrayDeclarator() { return true; }

    public String toString() {
      if (declarator.isEmptyDeclarator()) {
        return String.format("%s%s", declarator.toString(), arrayabstractdeclarator.toString());
      }
      return String.format("(%s)%s", declarator.toString(), arrayabstractdeclarator.toString());
    }

    public String toString(int len) {
      if (declarator.isEmptyDeclarator()) {
        return String.format("%s%s", declarator.toString(), arrayabstractdeclarator.toString(len));
      }
      return String.format("(%s)%s", declarator.toString(), arrayabstractdeclarator.toString(len));
    }

    public String printType() {
      if (declarator.isEmptyDeclarator() || declarator.isSimpleDeclarator()) {
        return String.format("%s%s", declarator.printType(), arrayabstractdeclarator.printType());
      }
      return String.format("(%s)%s", declarator.printType(), arrayabstractdeclarator.printType());
    }
    public boolean isFlexible() {
      return arrayabstractdeclarator.isFlexible();
    }
  }

  // do we ever need to know the syntax of the array's expression?  if
  // so, we'd have to store an AST node instead.
  /**
   * An array abstract declarator, which contains the contents of the
   * expression between its brackets.
   */
  public static class ArrayAbstractDeclarator extends Declarator {
    /**
     * The string contents of each array declarator.  A string will be
     * empty (but not null) if there is no expression between the
     * brackets.
     */
    protected final List<String> expressions;
    protected boolean typeError;
    
    /**
     * The initial single dimension array declarator.
     */
    public ArrayAbstractDeclarator(String expression) {
      typeError = false;
      this.expressions = new LinkedList();
      this.expressions.add(expression);
    }

    /**
     * Multi-dimensional array declarator.
     */
    public ArrayAbstractDeclarator(ArrayAbstractDeclarator arraydeclarator,
                           String expression) {
      typeError = false;
      this.expressions = new LinkedList(arraydeclarator.expressions);
      this.expressions.add(expression);
    }

    public Type getType(Type type) {
      Type arrayType = type;
      assert expressions.size() > 0;  // otherwise no arraytype will be made
      System.err.println("TODO: need to handle the expression to see if the array has a variable size of not");
      for (String expression : expressions) {
        if (expression != "") {
          arrayType = new ArrayT(arrayType,expression);
        } else {
          arrayType = new ArrayT(arrayType);
        }
      }
      return arrayType;
    }
    
    public void setTypeError(boolean t) {
      typeError = t;
    }
    
    public boolean hasTypeError() {
      return typeError;
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      // no need to copy since it's immutable.
      return this;
    }

    @Override
    public boolean isArrayAbstractDeclarator() { return true; }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      assert expressions.size() > 0;  // otherwise no arraytype will be made
      System.err.println("need to handle the expression to see if the array has a variable size of not");
      for (String expression : expressions) {
        sb.append(String.format("[%s]", expression));
      }
      return sb.toString();
    }

    public String toString(int len) {
      StringBuilder sb = new StringBuilder();
      sb.append(String.format("[%d]", len));
      return sb.toString();
    }

    public String printType() {
      StringBuilder sb = new StringBuilder();
      assert expressions.size() > 0;  // otherwise no arraytype will be made
      System.err.println("need to handle the expression to see if the array has a variable size of not");
      for (String expression : expressions) {
        sb.append(String.format("[%s]", expression == "" ? "" : expression));
      }
      return sb.toString();
    }

    public boolean isFlexible() {
      if (expressions.size() > 1) {
        return false;
      } else if (expressions.size() == 1) {
        return expressions.get(0) == "";
      }
      return true;
      
    }
  }

  /**
   * A function declarator contains the function name and a list of
   * parameters.
   */
  public static class FunctionDeclarator extends Declarator {
    /** The declarator that becomes a function. */
    protected final Declarator declarator;

    /** The function parameters. */
    protected final ParameterListDeclarator parameters;

    public FunctionDeclarator(Declarator declarator,
                              ParameterListDeclarator parameters) {
      this.declarator = declarator;
      this.parameters = parameters;
    }

    public String getName() {
      return declarator.getName();
    }

    public boolean hasName() {
      return declarator.hasName();
    }
    
    public Declarator rename(String newName) {
      // parameters don't affect the name of the declarator, so just
      // use the original parameters
      return new FunctionDeclarator(declarator.rename(newName),
                                    parameters);
    }

    public Type getType(Type returnType) {
      List<Type> paramtypes = new LinkedList<Type>();
      for (Declaration param : parameters.parameters) {
        String name;
        if (param.hasName()) {
          name = param.getName();
        } else {
          // xtc allows null to mean no name
          name = null;
        }
        paramtypes.add(VariableT.newParam(param.getType(), name));
      }

      if (declarator.isSimpleDeclarator()) {
        return new FunctionT(returnType, paramtypes, parameters.varargs);
      } else if (declarator.isPointerDeclarator()) {
        // the pointer declarators creator a function pointer
        return declarator.getType(new FunctionT(returnType, paramtypes, parameters.varargs));
      } else if (declarator.isPointerDeclarator()
                 || declarator.isQualifiedPointerDeclarator()
                 || declarator.isPointerAbstractDeclarator()
                 || declarator.isQualifiedPointerAbstractDeclarator()) {
        // the pointer declarators creator a function pointer
        return declarator.getType(new FunctionT(returnType, paramtypes, parameters.varargs));
      } else {
        throw new AssertionError("function declarator should either be simple or pointer");
      }
    }

    public boolean hasTypeError() {
      return declarator.hasTypeError() || parameters.hasTypeError();
    }

    @Override
    public boolean isFunctionDeclarator() { return true; }

    public String toString() {
      return String.format("(%s) %s", declarator.toString(), parameters.toString());
    }
    public String printType() {
      return String.format("(%s) %s", declarator.printType(), parameters.printType());
    }
    public boolean isFlexible() {
      return declarator.isFlexible();
    } 
    public Declarator switchForwardRef(List<Type> oldParams, PresenceCondition cond, CContext scope) {
      return new FunctionDeclarator(declarator,parameters.revertForwardRefs(oldParams,cond,scope));
    }
  }

  /** A parameter list. */
  public static class ParameterListDeclarator extends Declarator {
    /** The list of parameters. */
    protected final List<Declaration> parameters;

    /** Whether this list has variable arguments or not. */
    protected final boolean varargs;

    public ParameterListDeclarator(List<Declaration> parameters, boolean varargs) {
      this.parameters = parameters;
      this.varargs = varargs;
    }

    public String getName() {
      throw new IllegalStateException("parameters don't affect the name of the function");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      throw new IllegalStateException("parameters don't affect the name of the function");
    }

    public Type getType(Type type) {
      throw new IllegalStateException("Should only get parameter types via FunctionDeclarator");
    }

    public boolean hasTypeError() {
      for (Declaration param : parameters) {
        if (param.hasTypeError()) {
          return true;
        }
      }
      if (parameters.size() > 0) {
        if (parameters.size() > 1 && parameters.get(0).getType() == VoidT.TYPE) {
          return true;
        }
      }
      return false;
    }
  
    @Override
    public boolean isParameterListDeclarator() { return true; }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("(");
      String delim = "";
      for (Declaration param : parameters) {
        sb.append(delim);
        sb.append(param.toString());
        delim = ", ";
      }
      if (varargs) {
        sb.append(delim);
        sb.append(" ... ");
      }
      sb.append(")");
      return sb.toString();
    }
    public String printType() {
      StringBuilder sb = new StringBuilder();
      sb.append("(");
      String delim = "";
      for (Declaration param : parameters) {
        sb.append(delim);
        sb.append(param.printType());
        delim = ", ";
      }
      if (varargs) {
        sb.append(delim);
        sb.append(" ... ");
      }
      sb.append(")");
      return sb.toString();
    }

    public ParameterListDeclarator revertForwardRefs(List<Type> oldParams,PresenceCondition cond, CContext scope) {
      if (oldParams.size() != parameters.size()) {
        System.err.println("Error bad params given when referting forward references");
        System.exit(1);
      }
      List<Declaration> newDecs = new LinkedList<Declaration>();
      for (int i = 0; i < oldParams.size(); ++i) {
        Type ot = ((VariableT)oldParams.get(i)).getType();
        while (ot.isPointer()) {
          ot = ((PointerT)ot).getType();
        }
        if (ot.isStruct() && ((StructT)ot).getName().startsWith("__forward_tag_reference_")) {
          String originalTag = scope.getForwardTagReferenceAnyScope(((StructT)ot).getName());
          Multiverse<SymbolTable.Entry<Type>> originalTagEntries
            = scope.getInAnyScope(CContext.toTagName(originalTag), cond);
          List<String> names = new LinkedList<String>();
          for (Element<SymbolTable.Entry<Type>> e : originalTagEntries) {
            names.add(((StructT)e.getData().getValue()).getName());
          }
          if (!parameters.get(i).hasName()) {
            System.err.println("error: parameter has no name");
            System.exit(1);
          }
          String renamed = parameters.get(i).getName();
          TypeSpecifier newType = parameters.get(i).getTypeSpec().revertForwardRefs(names,((StructT)ot).getName(),renamed);
          scope = scope.reenterScope(cond);
          scope.getSymbolTable().replaceType(renamed,oldParams.get(i).revertForwardRef(names,((StructT)ot).getName(),renamed),cond);
          scope = scope.exitReentrantScope(cond);
          newDecs.add(new Declaration(newType,parameters.get(i).getDeclarator()));
        } else {
          newDecs.add(parameters.get(i));
        }
      }
      ParameterListDeclarator p = new ParameterListDeclarator(newDecs, varargs);
      return p;
    }
  }

  /**
   * A BitFieldSize declarator contains a struct bit field size.
   */
  public static class BitFieldSizeDeclarator extends Declarator {
    /** The bit field size. */
    protected final String expression;

    /** The type of the expression. */
    protected final Type type;

    public BitFieldSizeDeclarator(String expression, Type type) {
      this.expression = expression;
      this.type = type;
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public boolean hasName() {
      return false;
    }
    
    public Declarator rename(String newName) {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public Type getType(Type returnType) {
      return type;
    }

    public boolean hasTypeError() {
      return type.isError();
    }
  
    @Override
    public boolean isBitFieldSizeDeclarator() { return true; }

    public String toString() {
      return String.format(": %s", expression);
    }

    public String printType() {
      return String.format("%s", expression);
    }
  }

  /**
   * A BitFieldSize declarator contains a struct bit field size.
   */
  public static class NamedBitFieldSizeDeclarator extends Declarator {
    /** The declarator of the bit field size. */
    protected final Declarator declarator;
    
    /** The bit field size. */
    protected final BitFieldSizeDeclarator bitfieldsize;

    public NamedBitFieldSizeDeclarator(Declarator declarator, BitFieldSizeDeclarator bitfieldsize) {
      this.declarator = declarator;
      this.bitfieldsize = bitfieldsize;
    }

    public String getName() {
      return this.declarator.getName();
    }

    public boolean hasName() {
      return this.declarator.hasName();
    }
    
    public Declarator rename(String newName) {
	return new NamedBitFieldSizeDeclarator(this.declarator.rename(newName),bitfieldsize);
    }

    public Type getType(Type returnType) {
      if (this.bitfieldsize.type.isError()) {
        return this.bitfieldsize.type;
      } else {
        return this.declarator.getType(returnType);
      }
    }

    public boolean hasTypeError() {
      return this.declarator.hasTypeError() || this.bitfieldsize.type.isError();
    }
  
    @Override
    public boolean isNamedBitFieldSizeDeclarator() { return true; }

    public String getBitField() { return this.bitfieldsize.toString(); }
    
    public String toString() {
      return String.format("%s : %s", this.declarator.toString(), this.bitfieldsize.expression);
    }
    public String printType() {
      return String.format("%s", bitfieldsize.expression);
    }
  }
}
