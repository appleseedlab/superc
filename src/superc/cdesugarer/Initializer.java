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

  boolean isEmpty() { return false; }
  boolean isAssign() { return false; }
  boolean isDesignated() { return false; }
  boolean isExpression() { return false; }
  
  /**
   * Return the type of this initializer for use in checking against
   * the declaration.
   */
  // abstract public Type getType();

  public String toString() {
    throw new AssertionError("Initializer subclass has not implemented toString yet");
  }


  // InitializerOpt: empty or assign
  public static class EmptyInitializer extends Initializer {
    public EmptyInitializer() { }
    
    boolean isEmpty() { return true; }

    public String toString() {
      return "";
    }
  }

  // assign initializer:  either regular initializer or designatedinitializer
  public static class AssignInitializer extends Initializer {
    protected final Initializer initializer;
      
    public AssignInitializer(Initializer initializer) {
      this.initializer = initializer;
    }
    
    boolean isAssign() { return true; }

    public String toString() {
      return String.format("= %s", initializer.toString());
    }
  }

  // a designation followed by an initializer
  public static class DesignatedInitializer extends Initializer {
    protected final Designation designation;
    protected final Initializer initializer;

    public DesignatedInitializer(Designation designation, Initializer initializer) {
      this.designation = designation;
      this.initializer = initializer;
    }
    
    boolean isDesignated() { return false; }

    public String toString() {
      return String.format("%s %s", designation.toString(), initializer.toString());
    }
  }


  // regular initializer: initializerlist or expressioninitializer
  public static class ExpressionInitializer extends Initializer {
    protected final Type type;
    protected final String expression;

    public ExpressionInitializer(Type type, String expression) {
      this.type = type;
      this.expression = expression;
    }
    
    boolean isExpression() { return false; }

    public String toString() {
      return expression;
    }
  }

  // // holds a list of designatedinitializers
  // public static class InitializerList extends Initializer {
  // }

  // // holds a list of designators, followed by an ASSIGN
  // public static class Designation extends Initializer {
  // }

  // public static abstract class Designator {
  // }

  // public static class ArrayDesignator extends Designator {
  // }

  // public static class StructUnionDesignator extends Designator {
  // }
}
