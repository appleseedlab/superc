package xtc.lang.cpp;

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

  /** Returns true if this is a EmptyDeclarator object. */
  public boolean isEmptyDeclarator() { return false; }
  
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
  
  /** Returns true if this is a FunctionPointerDeclarator object. */
  public boolean isFunctionDeclarator() { return false; }
  
  /** Returns true if this is a FunctionDeclarator object. */
  public boolean isParameterDeclarator() { return false; }
  
  /** Returns true if this is a FunctionDeclarator object. */
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
      throw new IllegalStateException("abstract declarators have no type");
    }

    @Override
    public boolean isSimpleDeclarator() { return true; }

    public String toString() {
      // empty declarators have no string
      return "";
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
      return new PointerT(declarator.getType(type));
    }
  
    @Override
    public boolean isPointerDeclarator() { return true; }

    public String toString() {
      return String.format("(* %s)", declarator.toString());
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
      System.err.println("WARNING: need to add qualifiers from typebuilderunit");
      return new PointerT(declarator.getType(type));
    }
  
    @Override
    public boolean isQualifiedPointerDeclarator() { return true; }

    public String toString() {
      // TODO: waiting on typebuidlerunit tostring
      throw new AssertionError("not yet implemented");
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
      System.err.println("WARNING: need to add qualifiers from typebuilderunit");
      return new PointerT(type);
    }
  
    @Override
    public boolean isQualifiedPointerAbstractDeclarator() { return true; }

    public String toString() {
      // TODO: waiting on typebuidlerunit tostring
      throw new AssertionError("not yet implemented");
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
      return arrayabstractdeclarator.getType(declarator.getType(type));
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
    protected final List<StringBuilder> expressions;

    /**
     * The initial single dimension array declarator.
     */
    public ArrayAbstractDeclarator(StringBuilder expression) {
      this.expressions = new LinkedList();
      this.expressions.add(expression);
    }

    /**
     * Multi-dimensional array declarator.
     */
    public ArrayAbstractDeclarator(ArrayAbstractDeclarator arraydeclarator,
                           StringBuilder expression) {
      this.expressions = new LinkedList(arraydeclarator.expressions);
      this.expressions.add(expression);
    }

    public Type getType(Type type) {
      Type arrayType = type;
      assert expressions.size() > 0;  // otherwise no arraytype will be made
      System.err.println("need to handle the expression to see if the array has a variable size of not");
      for (StringBuilder expression : expressions) {
        arrayType = new ArrayT(arrayType);
      }
      return arrayType;
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
      for (StringBuilder expression : expressions) {
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

    public Type getType(Type type) {
      List<Type> paramtypes = new LinkedList<Type>();
      boolean varargs = false;  // TODO: handle varargs here
      for (ParameterDeclarator param : parameters.parameters) {
        TypeBuilder typebuilder = param.getType();
        paramtypes.add(typebuilder.toType());
      }
      return new FunctionT(declarator.getType(type), paramtypes, varargs);
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
    protected final List<ParameterDeclarator> parameters;

    public ParameterListDeclarator(List<ParameterDeclarator> parameters) {
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
  
    @Override
    public boolean isParameterListDeclarator() { return true; }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("(");
      String delim = "";
      for (ParameterDeclarator param : parameters) {
        sb.append(delim);
        sb.append(param.toString());
        delim = ", ";
      }
      sb.append(")");
      return sb.toString();
    }
  }

  /**
   * A function declarator contains the function name and a list of
   * parameters.
   */
  public static class ParameterDeclarator extends Declarator {
    /** Type of the parameter. */
    protected final TypeBuilder type;

    /** Type of the parameter. */
    protected final Declarator declarator;

    public ParameterDeclarator(TypeBuilder type, Declarator declarator) {
      this.type = type;
      this.declarator = declarator;
    }

    public String getName() {
      throw new IllegalStateException("parameters don't affect the name of the function");
    }

    public Declarator rename(String newName) {
      throw new IllegalStateException("parameters don't affect the name of the function");
    }

    /**
     * Return the typebuilder for this parameter.
     */
    public TypeBuilder getType() {
      return type;
    }

    public Type getType(Type type) {
      throw new IllegalStateException("Should only get parameter types via FunctionDeclarator");
    }
  
    @Override
    public boolean isParameterDeclarator() { return true; }

    public String toString() {
      return String.format("%s %s", type.toString(), declarator.toString());
    }
  }
}
