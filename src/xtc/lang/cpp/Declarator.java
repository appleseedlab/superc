package xtc.lang.cpp;

import java.util.List;
import java.util.LinkedList;

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
  abstract public Declarator rename(String newName); // copy constructors except for simple

  /** Returns true if this is a SimpleDeclarator object. */
  public boolean isSimpleDeclarator() { return false; }
  
  /** Returns true if this is a QualifiedPointerDeclarator object. */
  public boolean isQualifiedPointerDeclarator() { return false; }
  
  /** Returns true if this is a PointerDeclarator object. */
  public boolean isPointerDeclarator() { return false; }
  
  /** Returns true if this is a FunctionDeclarator object. */
  public boolean isFunctionDeclarator() { return false; }
  
  /** Returns true if this is a FunctionPointerDeclarator object. */
  public boolean isFunctionPointerDeclarator() { return false; }
  
  /** Returns true if this is a ArrayDeclarator object. */
  public boolean isArrayDeclarator() { return false; }

  /** Casts declarator. */
  public SimpleDeclarator toSimpleDeclarator() {
    return (SimpleDeclarator) this;
  }

  /** Casts declarator. */
  public QualifiedPointerDeclarator toQualifiedPointerDeclarator() {
    return (QualifiedPointerDeclarator) this;
  }

  /** Casts declarator. */
  public PointerDeclarator toPointerDeclarator() {
    return (PointerDeclarator) this;
  }

  /** Casts declarator. */
  public FunctionDeclarator toFunctionDeclarator() {
    return (FunctionDeclarator) this;
  }

  /** Casts declarator. */
  public FunctionPointerDeclarator toFunctionPointerDeclarator() {
    return (FunctionPointerDeclarator) this;
  }

  /** Casts declarator. */
  public ArrayDeclarator toArrayDeclarator() {
    return (ArrayDeclarator) this;
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

    public Declarator rename(String newName) {
      return new SimpleDeclarator(newName);
    }

    @Override
      public boolean isSimpleDeclarator() { return true; }
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

    public Declarator rename(String newName) {
      return new PointerDeclarator(declarator.rename(newName));
    }
  
    @Override
      public boolean isPointerDeclarator() { return true; }
  }

  // note this uses TypeBuilderUnit, not a Multiverse, so the action needs to hoist, because TypeQualifiers returns a Multiverse
  /**
   * A qualified pointer declarator, which has another declarator nested
   * inside of it as well as a list of qualifiers.
   */
  public static class QualifiedPointerDeclarator extends Declarator {
    /** Points to this declarator. */
    protected final Declarator declarator;

    /** Qualifiers, if any, of this pointer. */
    protected final TypeBuilderUnit qualifiers;

    public QualifiedPointerDeclarator(Declarator declarator,
                                      TypeBuilderUnit qualifiers) {
      this.declarator = declarator;
      this.qualifiers = qualifiers;
    }

    public Declarator rename(String newName) {
      return new QualifiedPointerDeclarator(declarator.rename(newName), qualifiers);
    }
  
    @Override
      public boolean isQualifiedPointerDeclarator() { return true; }
  }

  // do we ever need to know the syntax of the array's expression?  if
  // so, we'd have to store an AST node instead.
  /**
   * An array declarator, which contains the contents of the expression
   * between its brackets.
   */
  public static class ArrayDeclarator extends Declarator {
    /**
     * The string contents of each array declarator.  A string will be
     * empty (but not null) if there is no expression between the
     * brackets.
     */
    protected final List<StringBuilder> expressions;

    public ArrayDeclarator(ArrayDeclarator arraydeclarator,
                           StringBuilder expression) {
      this.expressions = new LinkedList(arraydeclarator.expressions);
      this.expressions.add(expression);
    }

    public Declarator rename(String newName) {
      // no need to copy since it's immutable.
      return this;
    }

    @Override
      public boolean isArrayDeclarator() { return true; }
  }

  /**
   * A function declarator contains the function name and a list of
   * parameters.
   */
  public static class FunctionDeclarator extends Declarator {
    /** The declarators's identifier. */
    protected final String name;

    /**
     * The list of parameters for ths function declarator.  This list
     * will be empty (but not null) if there are no parameters.
     */  
    protected final List<Parameter> parameters;

    public FunctionDeclarator(String name, List<Parameter> parameters) {
      this.name = name;
      this.parameters = new LinkedList<Parameter>(parameters);
    }

    public Declarator rename(String newName) {
      return new FunctionDeclarator(newName, parameters);
    }
  
    @Override
      public boolean isFunctionDeclarator() { return true; }
  }

  /**
   * A function declarator contains the function name and a list of
   * parameters.
   */
  public static class FunctionPointerDeclarator extends Declarator {
    /** This is the pointer declarator. */
    protected final Declarator declarator;

    /**
     * The list of parameters for ths function declarator.  This list
     * will be empty (but not null) if there are no parameters.
     */  
    protected final List<Parameter> parameters;

    public FunctionPointerDeclarator(Declarator declarator,
                                     List<Parameter> parameters) {
      this.declarator = declarator;
      this.parameters = new LinkedList<Parameter>(parameters);
    }

    public Declarator rename(String newName) {
      return new FunctionPointerDeclarator(declarator.rename(newName), parameters);
    }
  
    @Override
      public boolean isFunctionPointerDeclarator() { return true; }
  }
}
