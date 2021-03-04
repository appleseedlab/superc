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
 * The superclass of all declaration initializers.
 *
 * This is basically an AST for initializer that needs to
 *
 * 1) preserve the original syntax for use in a renaming
 * transformation;
 *
 * 2) preserve type-relevant information for use in checking correct
 * the type usage
 */
abstract class Initializer {

  private Initializer() { }

  /** True if an empty initializer */
  boolean isEmpty() { return false; }

  /** True if an assign initializer */
  boolean isAssign() { return false; }

  /** True if a designated initializer */
  boolean isDesignated() { return false; }

  /** True if an assignment expression initializer */
  boolean isExpression() { return false; }
  
  /** True if an list initializer */
  boolean isList() { return false; }

  // /**
  //  * Return the type of this initializer for use in checking against
  //  * the declaration.
  //  */
  // abstract public Type getType();

  abstract public boolean hasValidType();
  public boolean hasList() { return false; }
  public List<Initializer> getList() { return null; }
  public boolean hasChild() { return false; }
  public Initializer getChild() { return null; }
  
  public String toString() {
    throw new AssertionError("Initializer subclass has not implemented toString yet");
  }


  // InitializerOpt: empty or assign
  public static class EmptyInitializer extends Initializer {
    public EmptyInitializer() { }
    
    boolean isEmpty() { return true; }

    public boolean hasValidType() {
      return true;
    }

    public String toString() {
      return "";
    }
  }

  /**
   * The assign initializer has an equals sign followed by an
   * expression or list initializer.
   */
  public static class AssignInitializer extends Initializer {
    /** The initializer this assigns to. */
    protected final Initializer initializer;
      
    public AssignInitializer(Initializer initializer) {
      assert initializer.isExpression() || initializer.isList();
      this.initializer = initializer;
    }
    
    boolean isAssign() { return true; }

    public boolean hasValidType() {
      return initializer.hasValidType();
    }

    public String toString() {
      return String.format("= %s", initializer.toString());
    }

    public boolean hasList() { return initializer.hasList(); }
    public List<Initializer> getList() { return initializer.getList(); }
    public boolean hasChild() { return true; }
  public Initializer getChild() { return initializer; }
  
  }

  /**
   * An expression initializer is an initializer for primitives, where
   * they are assigned to the value of an expression.  This also holds
   * the type of the expression to typecheck the expression against
   * the declared type.
   */
  public static class ExpressionInitializer extends Initializer {
    /** The type of the expression. */
    protected final Type type;

    /** The transformation of the expression. */
    protected final String expression;

    public ExpressionInitializer(Type type, String expression) {
      this.type = type;
      this.expression = expression;
    }
    
    boolean isExpression() { return true; }

    public boolean hasValidType() {
      return ! type.isError();
    }

    public String toString() {
      return expression;
    }
  }

  /**
   * An initializer list holds a list of other initializers between
   * braces.  It is used to intialize an array or struct/union.  The
   * elements of the list are one of the regular initializers (list or
   * expression) or a designated initializer (which adds a designation
   * before a list or exprssion).
   */
  public static class InitializerList extends Initializer {
    protected final List<Initializer> list;

    public InitializerList(List<Initializer> list) {
      this.list = list;
    }
    
    /** True if an list initializer */
    boolean isList() { return true; }

    public boolean hasValidType() {
      // all the initializers in the list need to be valid types for
      // the initializer list to have a valid type
      for (Initializer initializer : list) {
        if (! initializer.hasValidType()) {
          return false;
        }
      }
      return true;
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      String delim = "";
      for (Initializer initializer : list) {
        sb.append(delim);
        sb.append(initializer.toString());
        delim = ", ";
      }
      return String.format("{ %s }", sb.toString());
    }

    public boolean hasList() { return true; }
    public List<Initializer> getList() { return list; }
  }

  /**
   * A designated initializer is only found in initializer lists and
   * is a Designation, i.e., a list of either array or struct/union
   * designators, followed by a regular initializer (which is an
   * expression or list of other initializers).
   */
  public static class DesignatedInitializer extends Initializer {
    /** The designation portion of the initializer. */
    protected final Designation designation;

    /** The regular initializer this designates. */
    protected final Initializer initializer;

    public DesignatedInitializer(Designation designation, Initializer initializer) {
      this.designation = designation;
      assert initializer.isExpression() || initializer.isList();
      this.initializer = initializer;
    }
    
    boolean isDesignated() { return true; }

    public boolean hasValidType() {
      return initializer.hasValidType();
    }

    public String toString() {
      return String.format("%s %s", designation.toString(), initializer.toString());
    }

    public Designation getDesignation() {
      return designation;
    }

    public String getInitString() {
      return initializer.toString();
    }
    
    public boolean hasChild() { return true; }
    public Initializer getChild() { return initializer; }
  }

  /**
   * A Designation is a list of array or struct/union designators.
   */
  public static class Designation {
    /** The list of designators. */
    protected final List<Designator> list;

    public Designation(List<Designator> list) {
      this.list = list;
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      for (Designator designator : list) {
        sb.append(designator.toString());
      }
      return String.format("%s =", sb.toString());
    }

    public int getListSize() {
      return list.size();
    }

    public Designator getDesignator() {
      return list.get(0);
    }
    public Designator getDesignator(int i) {
      return list.get(i);
    }
    
  }

  /**
   * This designator is specifically for gcc's OffsetofMemberDesignator.
   */
  public static class OffsetofMemberDesignator {
    /** The offsetof member identifier. */
    protected String ident;
    
    /** The list of designators, if any. */
    protected final List<Designator> list;

    public OffsetofMemberDesignator(String ident, List<Designator> list) {
      this.ident = ident;
      this.list = list;
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append(ident);
      sb.append(" ");
      for (Designator designator : list) {
        sb.append(designator.toString());
      }
      return String.format("%s", sb.toString());
    }
  }

  /**
   * This is the abstract superclass of designators.
   */
  public static abstract class Designator {
    /** True if an array designator. */
    public boolean isArray() { return false; }

    /** True if a struct or union designator. */
    public boolean isStructUnion() { return false; }
  }

  /**
   * An array designator references the index of an array in an
   * initializer.
   */
  public static class ArrayDesignator extends Designator {
    /** The type of the expression. */
    protected final Type type;

    /** The transformation of the expression. */
    protected final String expression;

    public ArrayDesignator(Type type, String expression) {
      this.type = type;
      this.expression = expression;
    }
    
    public boolean isArray() { return true; }

    public String toString() {
      return String.format("[%s]", expression);
    }
  }

  /**
   * A struct/union designator references a struct/union field in an
   * initializer.
   */
  public static class StructUnionDesignator extends Designator {
    /** The identifier of the field. */
    protected final String ident;

    public StructUnionDesignator(String ident) {
      this.ident = ident;
    }
      
    public boolean isStructUnion() { return true; }

    public String toString() {
      return String.format(".%s", ident);
    }

    public String getName() {
      return ident;
    }
  }
}
