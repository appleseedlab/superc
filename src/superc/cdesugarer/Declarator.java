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

    public Declarator rename(String newName) {
      return declarator.rename(newName);
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
      return String.format("(%s)", declarator.toString());
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
      return String.format("(* %s)", declarator.toString());  // preserve order of operations
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
    protected final TypeBuilder qualifiers;

    public QualifiedPointerDeclarator(Declarator declarator,
                                      TypeBuilder qualifiers) {
      this.declarator = declarator;
      this.qualifiers = qualifiers;
    }

    public String getName() {
      return declarator.getName();
    }

    public Declarator rename(String newName) {
      return new QualifiedPointerDeclarator(declarator.rename(newName), qualifiers);
    }

    public Type getType(Type type) {
      System.err.println("TODO: check correctness of qualified pointer declarator type");
      Type qualifiedtype = qualifiers.combine(new TypeBuilder(type)).toType();
      return declarator.getType(new PointerT(qualifiedtype));
    }

    public boolean hasTypeError() {
      return qualifiers.hasTypeError() || declarator.hasTypeError();
    }
  
    @Override
    public boolean isQualifiedPointerDeclarator() { return true; }

    public String toString() {
      // return String.format("* %s %s", qualifiers.toString(), declarator.toString());
      return String.format("(* %s %s)", qualifiers.toString(), declarator.toString());  // preserve order of operations
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
  }

  // note this uses TypeBuilder, not a Multiverse, so the action needs to hoist, because TypeQualifiers returns a Multiverse
  /**
   * A qualified pointer declarator without an explicit declarator
   * that it points to.  It has no declarator field, because it is an
   * abstract declarator.
   */
  public static class QualifiedPointerAbstractDeclarator extends Declarator {
    /** Qualifiers, if any, of this pointer. */
    protected final TypeBuilder qualifiers;

    public QualifiedPointerAbstractDeclarator(TypeBuilder qualifiers) {
      this.qualifiers = qualifiers;
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
    }

    public Declarator rename(String newName) {
      // nothing to rename and its immutable, so return this class.
      return this;
    }

    public Type getType(Type type) {
      Type qualifiedtype = qualifiers.combine(new TypeBuilder(type)).toType();
      return new PointerT(qualifiedtype);
    }

    public boolean hasTypeError() {
      return qualifiers.hasTypeError();
    }
  
    @Override
    public boolean isQualifiedPointerAbstractDeclarator() { return true; }

    public String toString() {
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
      System.err.println("WARNING: do we need parentheses?");
      return String.format("(%s%s)", declarator.toString(), arrayabstractdeclarator.toString());
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

    /**
     * The initial single dimension array declarator.
     */
    public ArrayAbstractDeclarator(String expression) {
      this.expressions = new LinkedList();
      this.expressions.add(expression);
    }

    /**
     * Multi-dimensional array declarator.
     */
    public ArrayAbstractDeclarator(ArrayAbstractDeclarator arraydeclarator,
                           String expression) {
      this.expressions = new LinkedList(arraydeclarator.expressions);
      this.expressions.add(expression);
    }

    public Type getType(Type type) {
      Type arrayType = type;
      assert expressions.size() > 0;  // otherwise no arraytype will be made
      System.err.println("TODO: need to handle the expression to see if the array has a variable size of not");
      for (String expression : expressions) {
        arrayType = new ArrayT(arrayType);
      }
      return arrayType;
    }

    public boolean hasTypeError() {
      return false;
    }

    public String getName() {
      throw new IllegalStateException("abstract declarators have no name");
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

    public Declarator rename(String newName) {
      // parameters don't affect the name of the declarator, so just
      // use the original parameters
      return new FunctionDeclarator(declarator.rename(newName),
                                    parameters);
    }

    public Type getType(Type returnType) {
      List<Type> paramtypes = new LinkedList<Type>();
      boolean varargs = false;  // TODO: handle varargs here
      for (Declaration param : parameters.parameters) {
        paramtypes.add(param.getType());
      }

      if (declarator.isSimpleDeclarator()) {
        return new FunctionT(returnType, paramtypes, varargs);
      } else if (declarator.isPointerDeclarator()) {
        // the pointer declarators creator a function pointer
        return declarator.getType(new FunctionT(returnType, paramtypes, varargs));
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
      return String.format("%s %s", declarator.toString(), parameters.toString());
    }
  }

  /** A parameter list. */
  public static class ParameterListDeclarator extends Declarator {
    /** The list of parameters. */
    protected final List<Declaration> parameters;

    public ParameterListDeclarator(List<Declaration> parameters) {
      this.parameters = parameters;
    }

    public String getName() {
      throw new IllegalStateException("parameters don't affect the name of the function");
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
      sb.append(")");
      return sb.toString();
    }
  }
}
