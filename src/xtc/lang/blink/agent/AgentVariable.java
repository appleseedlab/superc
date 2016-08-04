package xtc.lang.blink.agent;

import static java.lang.String.format;

/**
 * Blink's support for the convenience variables in Java. This class 
 * in particular represents a set of polymorphic
 * convenience variables to hold both the java primitive and reference
 * values.
 *
 * @author Byeongcheol Lee 
 */
public class AgentVariable {

  /** The unique identifier. */
  private int id;  

  /** The value. */
  private Object value;

  /** A Java expression to read the value from the Java debugger. */
  private String accessExpression;

  /** The Java type representation. */
  private String typeName;

  /** Constructor. */
  private AgentVariable(int id) {this.id = id;}

  /** The Blink Java multi-typed variable array. */
  private static AgentVariable[] jvars;

  /** The next unique variable identifier. */
  private static int nextVJIdentifier;

  /** Perform initialization. */
  public static void init() {
    jvars = new AgentVariable[100];
    nextVJIdentifier = 0;
  }

  /** Create a new instance of the convenience variable. */
  private static AgentVariable createVariable() {
    if (nextVJIdentifier < jvars.length) {
      AgentVariable vj = new AgentVariable(nextVJIdentifier);
      jvars[nextVJIdentifier] = vj;
      nextVJIdentifier++;
      return vj;
    } else {
      AgentVariable[] newJVars = new AgentVariable[jvars.length * 2];
      System.arraycopy(jvars, 0, newJVars, 0, nextVJIdentifier);
      jvars = newJVars;
      return createVariable();
    }
  }

  /** clean up the temp variables table. */
  public static void cleanTempVars() {
    for(int i = 0; i < jvars.length;i++) {
      if( jvars[i] != null ) {
        jvars[i] = null;
      }
    }
    nextVJIdentifier = 0;
  }

  private static String genAccessExpression(int vid, String methodName, String typeName) {
    return format("((%s)%s.%s(%d))",
        typeName,
        "xtc.lang.blink.agent.AgentVariable",
        methodName, vid);
  }
  /**
   * Take a class instance and return the fully qualified name of the
   * type that the class instance represents.
   *
   * @param cls The class instance.
   * @return The fully qualified name.
   */
  private static String getFullyQualifiedName(Class<?> cls) {
    String type = cls.getName();
    int i = 0, dim = 0;
    if (type.charAt(i) == '[') {
      for(; type.charAt(i) == '[';i++) {
        dim++;
       }
    }
    StringBuilder type_rhs = new StringBuilder();
    for(int d = 0; d < dim;d++) {
      type_rhs.append('[');
     }
    for(int d = 0; d < dim;d++) {
      type_rhs.append(']');
    }
    String type_lhs;
    if (dim == 0) {
      type_lhs = type;
    } else {
      switch(type.charAt(i)) {
      case 'L':
        type_lhs = type.substring(i+1, type.length() - 1);
       break;
      case 'Z':
        type_lhs = "boolean";
        break;
      case 'B':
        type_lhs = "byte";
        break;
      case 'C':
        type_lhs = "char";
        break;
      case 'D':
        type_lhs = "double";
        break;
      case 'F':
        type_lhs = "float";
        break;
      case 'I':
        type_lhs = "int";
        break;
      case 'J':
        type_lhs = "long";
        break;
      case 'S':
        type_lhs = "short";
        break;
      default:
        type_lhs = "failure";
        break;
      }
    }
  
    return type_lhs + type_rhs.toString();
  }

  /**
   * Take a boolean primitive value, create convenience variable, and
   * assign the boolean value to the convenience variable.
   *
   * @param value
   * @return The convenience variable identifier.
   */
  public static int set(boolean value) {
    AgentVariable vj = createVariable();
    vj.value = new Boolean(value);
    vj.typeName = "boolean";
    vj.accessExpression = genAccessExpression(vj.id, "getAsBoolean", vj.typeName); 
    return vj.id;
  }

  /**
   * Take an integer primitive value, create convenience variable, and
   * assign the integer value to the convenience variable.
   *
   * @param value
   * @return The convenience variable identifier.
   */
  public static int set(int value) {
    AgentVariable vj = createVariable();
    vj.value = new Integer(value);
    vj.typeName = "int";
    vj.accessExpression = genAccessExpression(vj.id, "getAsInt", vj.typeName);
    return vj.id;
  }

  /**
   * Take an double primitive value, create convenience variable, and
   * assign the double value to the convenience variable.
   *
   * @param value
   * @return The convenience variable identifier.
   */
  public static int set(double value) {
    AgentVariable vj = createVariable();
    vj.value = new Double(value);
    vj.typeName = "double";
    vj.accessExpression = genAccessExpression(vj.id, "getAsDouble", vj.typeName);
    return vj.id;
  }

  /**
   * Take a reference value, create convenience variable, and assign
   * the reference value to the convenience variable.
   *
   * @param obj The reference.
   * @return The convenience variable identifier.
   */
  public static int set(Object obj) {
    AgentVariable vj = createVariable();
    if (obj != null) {
      String fqname = getFullyQualifiedName(obj.getClass());
      vj.value = obj;
      vj.typeName = fqname;
      vj.accessExpression = genAccessExpression(vj.id, "getAsObject", vj.typeName); 
    } else {
      vj.value = null;
      vj.typeName = "java.lang.Object";
      vj.accessExpression="(null)";
    }
    return vj.id;
  }

  /** 
   * Create a Java expression so that the Java debugger will read the
   * value of the convenience variable. 
   * @param vjid The convenience variable identifier.
   * @return The Java expression.
   */
  public static String getJavaExpression(int vjid) {
    return jvars[vjid].accessExpression;
  }

  /** 
   * Get the Java type representation of a convenience variable.
   * @param vjid The convenience variable identifier.
   * @return The Java expression.
   */
  public static String getTypeName(int vjid) {
    return jvars[vjid].typeName;
  }

  /** 
   * Get the boolean value of the convience variable.
   * @param vjid The convenience variable identifier.
   * @return The boolean value.
   */
  public static boolean getAsBoolean(int vjid) {
    Object obj = jvars[vjid].value;
    Boolean bobj = (Boolean)obj;
    return bobj.booleanValue();
  }

  /** 
   * Get the integer value of the convience variable.
   * @param vjid The convenience variable identifier.
   * @return The integer value.
   */
  public static int getAsInt(int vjid) {
    Object obj = jvars[vjid].value;
    Integer bobj = (Integer)obj;
    return bobj.intValue();
  }

  /** 
   * Get the double value of the convience variable.
   * @param vjid The convenience variable identifier.
   * @return The double value.
   */
  public static double getAsDouble(int vjid) {
    Object obj = jvars[vjid].value;
    Double bobj = (Double)obj;
    return bobj.doubleValue();
  }

  /** 
   * Get the reference value of the convience variable.
   * @param vjid The convenience variable identifier.
   * @return The reference value.
   */
  public static Object getAsObject(int vjid) {
    Object obj = jvars[vjid].value;
    Object bobj = (Object)obj;
    return bobj;
  }
}
