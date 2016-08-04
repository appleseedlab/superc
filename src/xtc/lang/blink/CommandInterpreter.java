package xtc.lang.blink;

import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import static java.lang.String.format;

import xtc.tree.GNode;
import xtc.tree.Token;
import xtc.tree.Visitor;
import xtc.lang.jeannie.Utilities;
import xtc.lang.blink.CommandAstAnalyzer.Language;
import xtc.lang.blink.CallStack.JavaCallFrame;
import xtc.lang.blink.CallStack.NativeCallFrame;
import xtc.lang.blink.SymbolMapper.SourceFileAndLine;
import xtc.lang.blink.SymbolMapper.VariableRemapEntry;
import xtc.lang.blink.Event.Java2NativeReturnEvent;
import xtc.lang.blink.Event.JavaBreakPointHitEvent;
import xtc.lang.blink.Event.JavaStepCompletionEvent;
import xtc.lang.blink.Event.Native2JavaReturnEvent;
import xtc.lang.blink.Event.NativeBreakPointHitEvent;
import xtc.lang.blink.Event.NativeStepCompletionEvent;
import xtc.lang.blink.Event.SessionFinishRequestEvent;

/**
 * The user command line interpreter. 
 * 
 * @author Byeongcheol Lee
 */
public final class CommandInterpreter extends Visitor {

  /* Type equivalences for Primitive Types in JNI and Java. */
  private static Map<String,String> c2jPrimitiveType = new HashMap<String,String>();
  private static Map<String,String> j2cPrimitiveType = new HashMap<String,String>();
  static {
    c2jPrimitiveType.put("jboolean", "jboolean");
    c2jPrimitiveType.put("jbyte", "jbyte");
    c2jPrimitiveType.put("jshort", "jshort");
    c2jPrimitiveType.put("jchar", "jchar");
    c2jPrimitiveType.put("jint", "jint");
    c2jPrimitiveType.put("jlong", "jlong");
    c2jPrimitiveType.put("jfloat", "jfloat");
    c2jPrimitiveType.put("jdouble", "jdouble");    
    c2jPrimitiveType.put("int", "jint");  // implicit conversion

    j2cPrimitiveType.put("boolean", "jboolean");
    j2cPrimitiveType.put("byte", "jbyte");
    j2cPrimitiveType.put("short", "jshort");
    j2cPrimitiveType.put("char", "jchar");
    j2cPrimitiveType.put("int", "jint");
    j2cPrimitiveType.put("long", "jlong");
    j2cPrimitiveType.put("float", "jfloat");
    j2cPrimitiveType.put("double", "jdouble");
  }

  /* Opaque reference types in JNI. */
  private static Set<String> opaqueJNITypes = new HashSet<String>();
  static {
    opaqueJNITypes.add("jobject");
    opaqueJNITypes.add("jclass");
    opaqueJNITypes.add("jthrowable");
    opaqueJNITypes.add("jstring");
    opaqueJNITypes.add("jarray");
    opaqueJNITypes.add("jbooleanArray");
    opaqueJNITypes.add("jbyteArray");
    opaqueJNITypes.add("jcharArray");
    opaqueJNITypes.add("jshortArray");
    opaqueJNITypes.add("jintArray");
    opaqueJNITypes.add("jlongArray");
    opaqueJNITypes.add("jfloatArray");
    opaqueJNITypes.add("jdoubleArray");
    opaqueJNITypes.add("jobjectArray");    
  }

  /** Generate an expression. */
  private static String gen(String format, Object ... args) {
      return format(format, args);
  }

  private static String getJNITypeNameFromJavaTypeName(String javaTypeName) {
    if (j2cPrimitiveType.containsKey(javaTypeName)) {
      return j2cPrimitiveType.get(javaTypeName);
    } else {
      return "jobject";
    }
  }

  /** Getter the language property of the node. */
  private static Language getLanguage(final GNode n) {
    return (Language) n.getProperty("language");
  }

  private static String mapToJNIType(String ctypeName) {
    if (c2jPrimitiveType.containsKey(ctypeName)) {
      return c2jPrimitiveType.get(ctypeName);
    } else if (opaqueJNITypes.contains(ctypeName)) { 
      return "jobject";
    } else {
      return null;
    }
  }

  /** join a number of expressions by inserting a string between them. */
  private static String join(String s, Object[] exprs) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < exprs.length;i++) {
      if (i == 0) {
        sb.append(exprs[i]);
      } else {
        sb.append(s).append(exprs[i]);
      }
    }
    return sb.toString();
  }

  /**
   * The blink debugger for the communication with jdb, gdb and the Blink Debug
   * Agent (BDA).
   */
  private final Blink dbg;

  /** The break point manager. */
  private final BreakPointManager breakpointManager;

  /** The Jeannie symbol remapper. */
  private final SymbolMapper jeannieSymbolRemapper;

  /** The current context for debugging. */
  private DebuggerContext debuggerContext;

  /**
   * Constructor.
   *
   * @param dbg The blink debugger.
   * @param breakpointManager The break point manager.
   */
  CommandInterpreter(final Blink dbg, BreakPointManager breakpointManager) {
    this.dbg = dbg;
    this.breakpointManager = breakpointManager;
    this.jeannieSymbolRemapper = new SymbolMapper();
  }

  /**
   * Transfer data from C to Java.
   * 
   * @param cexpr The C expression.
   * @return The Java convenience variable.
   */
  private String backtick_c2j(String cexpr) throws Exception {
    DebuggerContext c =  ensureDebuggerContext();
    NativeCallFrame nframe = c.getCurrentNativeFrame();
    dbg.ensureGDBContext();
    String cTypeName= dbg.ndb.whatis(nframe, cexpr);
    String jniTypeName = mapToJNIType(cTypeName);
    if (jniTypeName == null) {
      throw new Exception(format(
          "A '%s' value cannot be transferred from C to Java", cTypeName));
    }
    String cExpression = gen("bda_cv_set_%s(%s)", jniTypeName, cexpr);
    String vjid = dbg.ndb.eval(nframe, cExpression);
    dbg.ensureJDBContext();
    String jv = dbg.jdb.getConvenienceVariableExpression(vjid); 
    return jv; 
  }

  /**
   * Transfer data from Java to C.
   * 
   * @param jexpr The Java expression.
   * @return A C convenience variable.
   */
  private String backtick_j2c(String jexpr) throws Exception {
    DebuggerContext c =  ensureDebuggerContext();
    JavaCallFrame jframe = c.getCurrentJavaFrame();
    NativeCallFrame nframe = c.getCurrentNativeFrame();
    dbg.ensureJDBContext();
    String vjid = dbg.jdb.set_j(jframe, jexpr);
    String javaTypeName= dbg.jdb.getConvenienceVariableTypeName(vjid);;
    String jniTypeName = getJNITypeNameFromJavaTypeName(javaTypeName);
    dbg.ensureGDBContext();
    String cv = dbg.ndb.getNewCTmpVarIdentifier();
    String cexpression = gen("bda_cv_get_%s(%s)", jniTypeName, vjid);
    dbg.ndb.setVariable(nframe, cv, cexpression);

    return cv;
  }

  /** Clear the current debugger context. */
  private final void clearDebuggerContext() {
    debuggerContext = null;
  }

  /** Ensure the debugger context is available at the return of this method. */
  private final DebuggerContext ensureDebuggerContext() throws Exception {
    if (debuggerContext != null ) {
      return debuggerContext;
    }
    dbg.ensurePureContext();
    CallStack callStack = CallStack.extractCallStack(dbg,
        jeannieSymbolRemapper);
    debuggerContext = new DebuggerContext(callStack);
    return debuggerContext;
  }

  /** Implement BlinkEventSource. */
  public String getEventSourceName() {
    return "CommandRunner";
  }

  /**
   * Evaluate a C expression.
   * 
   * This is one of the six Blink expression evaluation primitives.
   * @param cexpr The expression.
   * @return The result of evaluating the <String>
   */
  private String print_c(String cexpr) throws Exception {
    DebuggerContext c =  ensureDebuggerContext();
    NativeCallFrame nframe = c.getCurrentNativeFrame();
    dbg.ensureGDBContext();
    String result = dbg.ndb.eval(nframe, cexpr);
    return result;
  }

  /**
   * Evaluate a Java expression.
   * 
   * @param jexpr The expression.
   * @return The string representation of the result value.
   */
  private String print_j(String jexpr) throws Exception {
    dbg.ensureJDBContext();
    DebuggerContext c =  ensureDebuggerContext();
    JavaCallFrame jf = c.getCurrentJavaFrame();
    String result = dbg.jdb.print(jf, jexpr); 
    return result;
  }

  /** Finish the expression evaluation. */
  private final void resetConvenienceVariables() {
    try {
      dbg.ensureJDBContext();
      dbg.jdb.resetConvenienceVariables();
      dbg.ensureGDBContext();
      dbg.ndb.resetConvenienceVariables();
    } catch (Exception e) {
      dbg.err("could not successfully clean JDB temp varaibles.\n");
    }
  }
  
  /** Visit the AbstractDeclarator expression node. */
  public final String visitAbstractDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("%s %s", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
  }
  
  /** Visit the addictive expression node. */
  public final String visitAdditiveExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit an AddressExpression = Expression. */
  public final String visitAddressExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String expr = (String)dispatch(n.getNode(0));
    return gen("(& %s)", expr);
  }

  /** Visit Arguments = Expression*. */
  public final String[] visitArguments(final GNode n) {
    assert getLanguage(n) == Language.JAVA;
    String[] args = new String[n.size()];
    for (int i=0; i<n.size(); i++)
      args[i] = (String)dispatch(n.getNode(i));
    return args;
  }
  
  /** Visit the ArrayDeclarator expression node. */
  public final String visitArrayDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("( %s [ %s ] )", (String) dispatch(n.getNode(0)), (String) dispatch(n.getNode(1)));
  }

  /** Visit the ArrayInitializer expression node. */
  public final String visitArrayInitializer(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /**
   * Visit an AssignmentExpression = Expression ("=" / "+=" / "-=" / "*=" / "/="
   * / "%=" / "&lt;&lt;=" / "&gt;&gt;=" / "&amp;=" / "^=" / "|=") Expression.
   */
  public final String visitAssignmentExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    //  mark the LHS is the l-value expression generator. 
    String expr0 = (String)dispatch(n.getNode(0));
    String operator = n.getString(1);
    String expr1 = (String)dispatch(n.getNode(2));
    return gen("(%s %s %s)", expr0, operator, expr1);
    }

  /** Visit the AutoSpecifier expression node. */
  public final String visitAutoSpecifier(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("auto");
  }

  /** Visit the BasicCastExpression expression node. */
  public final String visitBasicCastExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the bitwise and expression node. */
  public final String visitBitwiseAndExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the bitwise negation expression node. */
  public final String visitBitwiseNegationExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String operand = (String)dispatch(n.getNode(0));
    return gen("(~ %s)", operand);
  }

  /** Visit the bitwise and expression node. */
  public final String visitBitwiseOrExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }
  
  /** Visit the bitwise xor expression node. */
  public final String visitBitwiseXorExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the Bool expression node. */
  public final String visitBool(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("_Bool");
  }

  /** Visit the BooleanLiteral expression node. */
  public final String visitBooleanLiteral(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a BreakClassCommand = QualifiedIdentifier LineNumber. */
  public final void visitBreakClassCommand(final GNode n) {
    String className = n.getNode(0).getString(0);
    int lineNumber = Integer.parseInt( n.getString(1));
    breakpointManager.setJavaBreakPoint(className, lineNumber);
    dbg.ensurePureContext();
  }

  /** Visit a BreakClassCommand = QualifiedIdentifier. */
  public final void visitBreakClassMethodCommand(final GNode n) {
    String classAndMethod= Utilities.qualifiedIdentifierToString(n.getGeneric(0));
    Pattern p = Pattern.compile("^(.+)\\.([^\\.]+)$");
    Matcher m = p.matcher(classAndMethod);
    if (m.matches()) {
      String cname = m.group(1);
      String mname = m.group(2);
      breakpointManager.setJavaBreakPoint(cname, mname);
      dbg.ensurePureContext();
    } else {
      dbg.err("can not recognize as <class>.<method>\n");
    }
  }

  /** Visit a BreakFileCommand = FileName LineNumber. */
  public final void visitBreakFileCommand(final GNode n) {
    String fileName = n.getString(0);
    int lineNumber = Integer.parseInt(n.getString(1));
    try {
      breakpointManager.setNativeBreakpoint(fileName, lineNumber);
    } catch(Exception  e) {
      dbg.err("Can not set breakpoint.");
    }
    dbg.ensurePureContext();
  }

  /** Visit a BreakFunctionCommand = Identifier. */
  public final void visitBreakFunctionCommand(final GNode n) {
    String identifier = n.getString(0);
    try {
      breakpointManager.setNativeBreakpoint(identifier);
    } catch(Exception e) {
      dbg.err("Can not set breakpoint."); 
    }
    dbg.ensurePureContext();
  }

  /** Visit a C2jCommand = (no children). */
  public final void visitC2jCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    dbg.c2j();
  }

  /** Visit a CallExpression = [Expression] null MethodName Arguments. */
  public String visitCallExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    String recv = (String) dispatch(n.getNode(0)); 
    String meth = n.getString(2);
    String[] args = (String[]) dispatch(n.getNode(3));
    return gen("(%s.%s(%s))", recv, meth, join(",",args));
  }

  /** Visit the cast expression node. */
  public final String visitCastExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    return gen("((%s)%s)", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
  }

  /** Visit the Char expression node. */
  public final String visitChar(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("char");
  }
  
  /** Visit the CharacterConstant expression node. */
  public final String visitCharacterConstant(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return n.getString(0);
  }

  /** Visit the CharacterLiteral expression node. */
  public final String visitCharacterLiteral(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a CInJavaExpression = C.UnaryExpression. */
  public final String visitCInJavaExpression(final GNode n)throws Exception {
    return backtick_c2j((String)dispatch(n.getNode(0)));
  }

  /** Visit the ClassLiteralExpression expression node. */
  public final String visitClassLiteralExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the CommaExpression expression node. */
  public final String visitCommaExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] exprs= new String[n.size()];
    for (int i=0; i< n.size(); i++) {
        exprs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(",", exprs));
  }

  /** Visit the ConcreteDimensions expression node. */
  public final String visitConcreteDimensions(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the ConditionalExpression expression node. */
  public final String visitConditionalExpression(final GNode n) throws Exception {
    return gen("(%s ? %s : %s)", 
        (String)dispatch(n.getNode(0)),
        (String)dispatch(n.getNode(1)),
        (String)dispatch(n.getNode(2)));
  }

  /** Visit the ConstantQualifier expression node. */
  public final String visitConstantQualifier(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("%s", n.getString(0));
  }

  /** Visit a ContinueCommand = (no children). */
  public final void visitContinueCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    clearDebuggerContext();
    dbg.cont();
  }

  /** Visit the DeclarationSpecifiers expression node. */
  public final String visitDeclarationSpecifiers(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] specs = new String[n.size()];
    for(int i = 0;i < specs.length;i++) {
      specs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(" ", specs));
  }

  /** Visit the Declarator expression node. */
  public final String visitDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the Declarators expression node. */
  public final String visitDeclarators(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a DeleteCommand = IntegerLiteral. */
  public final void visitDeleteCommand(final GNode n) {
    int id = Integer.parseInt(n.getNode(0).getString(0));
    breakpointManager.clearBreakpoint(id);
    dbg.ensurePureContext();
  }

  /** Visit the Dimensions expression node. */
  public final String visitDimensions(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the DirectAbstractDeclarator expression node. */
  public final String visitDirectAbstractDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    if (n.get(0) == null) {
      if (("[").equals(n.get(1))) {
        if (n.get(2) == null) {
          return gen("[]");  
        } else {
           return gen("[%s]", (String)dispatch(n.getNode(2)));
        }
      } else {
         return gen("(%s)", (String)dispatch(n.getNode(2)));
       }
    } else {
      if (("[").equals(n.get(1))) {
        if (n.get(2) == null) {
          return gen("%s []", (String)dispatch(n.getNode(0)));
        } else {
          return gen("%s [%s]", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(2)));
        }
      } else {
         return gen("%s (%s)", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(2)));
       }
    }
  }

  /** Visit a DirectComponentSelection = Expression String. */
  public final String visitDirectComponentSelection(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String expr = (String)dispatch(n.getNode(0));
    String comp = n.getString(1);
    return gen("(%s.%s)", expr, comp);  
  }

  /** Visit the Double expression node. */
  public final String visitDouble(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("double");
  }

  /** Visit a DownCommand = IntegerLiteral. */
  public final void visitDownCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    int steps = Integer.parseInt( n.getNode(0).getString(0));
    try {
      ensureDebuggerContext();
      debuggerContext.windStack(dbg, steps);
    } catch (Exception e) {
      dbg.err("could not perform up\n");
    } finally {
      dbg.ensurePureContext();
    }
  }

  /** Visit the EnumerationTypeReference expression node. */
  public final String visitEnumerationTypeReference(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("enum %s", n.getString(1));
  }

  /** Visit a EqualityExpression = Expression ("==" / "!=") Expression. */
  public final String visitEqualityExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String expr0 = (String) dispatch(n.getNode(0));
    String operator = n.getString(1);
    String expr1 = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", expr0, operator, expr1);
  }

  /** Visit a ExitCommand = (no children). */
  public final void visitExitCommand(final GNode n) {
    dbg.ensurePureContext();
    dbg.exit();
  }

  /**
   * Visit a Expression = Expression ("=" / "+=" / "-=" / "*=" / "/=" / "&amp;="
   * / "|=" / "^=" / "%=" / "&lt;&lt;=" / "&gt;&gt;=" / "&gt;&gt;&gt;=")
   * Expression.
   */
  public final String visitExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    String lhs = (String)dispatch(n.getNode(0)); 
    String op = n.getString(1); 
    String rhs = (String)dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit ExpressionList = Expression+. */
  public final String visitExpressionList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] exprs= new String[n.size()];
    for (int i=0; i<n.size(); i++) {
        exprs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(",", exprs));
  }

  /** Visit the Float expression node. */
  public final String visitFloat(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("float");
  }

  /** Visit the FloatingConstant expression node. */
  public final String visitFloatingConstant(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(%s)", n.getString(0));
  }

  /** Visit the FloatingPointLiteral expression node. */
  public final String visitFloatingPointLiteral(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a FunctionCall = Expression [ExpressionList]. */
  public final String visitFunctionCall(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String exprFunc = (String)dispatch(n.getNode(0));
    String args = n.getNode(1) == null ? "" : (String)dispatch(n.getNode(1));
    return gen("(%s(%s))", exprFunc, args);
  }

  /** Visit the FunctionDeclarator expression node. */
  public final String visitFunctionDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("%s (%s)", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
  }

  /** Visit a GdbCommand = RestOfLine. */
  public final void visitGdbCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.out("gdb is not activated yet.\n");
      return;
    }
    String cmd = n.getString(0);
    try {
      String msg = dbg.ndb.runCommand(cmd);
      dbg.out("%s", msg);
    } catch (Exception e) {
      dbg.err("can not successfully native debugger command");
    }
  }

  /** Visit a HelpCommand = (no children). */
  public final void visitHelpCommand(final GNode n) {
    dbg.help();
    dbg.ensurePureContext();
  }

  /** Visit the IdentifierList expression node. */
  public final String visitIdentifierList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] exprs= new String[n.size()];
    for (int i=0; i< n.size(); i++) {
        exprs[i] =  Token.cast(n.get(i));
    }
    return gen("%s", join(", ", exprs));
  }

  public final String visitIndirectComponentSelection(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String e = (String)dispatch(n.getNode(0));
    String field = n.getString(1);
    return gen("(%s->%s)", e, field);
  }

  /** Visit an IndirectionExpression = Expression. */
  public final String visitIndirectionExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String expr = (String)dispatch(n.getNode(0));
    return gen("(*%s)", expr);
  }

  /** Visit a InfoBreakCommand = (no children). */
  public final void visitInfoBreakCommand(final GNode n) {
    breakpointManager.showUserBreakPointList();
    dbg.ensurePureContext();
  }

  /** Visit a InfoWatchCommand = (no children). */
  public final void visitInfoWatchCommand(final GNode n) {
    assert false : "not yet implemented";
  }

  /** Visit an InitJCommand = (no children).  */
  public final void visitInitJCommand(final GNode n) throws IOException {
    dbg.initj();
    dbg.ensurePureContext();
  }

  /** Visit the InstanceOfExpression expression node. */
  public final String visitInstanceOfExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }
  
  /** Visit the InstantiatedType expression node. */
  public final String visitInstantiatedType(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the Int expression node. */
  public final String visitInt(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    assert false: "TBI";
    return null;
  }

  /** Visit an IntegerConstant = String. */
  public final String visitIntegerConstant(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(%s)", n.getString(0));
  }

  /** Visit an IntegerLiteral = String. */
  public final String visitIntegerLiteral(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    return gen("(%s)", n.getString(0));
  }

  /** Visit a J2cCommand = (no children). */
  public final void visitJ2cCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    dbg.j2c();
  }

  /** Visit a JavaInStringession = Java.UnaryExpression. */
  public final String visitJavaInCExpression(final GNode n) throws Exception {
    return backtick_j2c((String)dispatch(n.getNode(0)));
  }

  /** Visit a JdbCommand = RestOfLine. */
  public final void visitJdbCommand(final GNode n) {
    String cmd = n.getString(0);
    try {
      String msg = dbg.jdb.runCommand(cmd);
      dbg.out("%s", msg);
    } catch (Exception e) {
      dbg.err("can not successfully run the jdb command");
    }
  }

  /** Visit a JRetCommand = (no children). */
  public final void visitJRetCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    dbg.jret();
  }

  /** Visit a ListCommand = (no children). */
  public final void visitListCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      ensureDebuggerContext();
      debuggerContext.showSourceCode(dbg);
    } catch(Exception e) {
      dbg.err("could not perform the list command.\n");
    } finally {
      dbg.ensurePureContext();
    }
  }

  /** Visit a LocalsCommand = (no children). */
  public final void visitLocalsCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      ensureDebuggerContext();
      debuggerContext.showLocals(dbg, jeannieSymbolRemapper);
    } catch(Exception e) {
      dbg.err("could not perform list command.\n");
    } finally {
      dbg.ensurePureContext();
    }
  }

  /** Visit the LogicalAndExpression expression node. */
  public final String visitLogicalAndExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the LogicalNegationExpression expression node. */
  public final String visitLogicalNegationExpression(final GNode n)
      throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    return gen("(! %s)", (String)dispatch(n.getNode(0)));
  }

  /** Visit the LogicalOrExpression expression node. */
  public final String visitLogicalOrExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the Long expression node. */
  public final String visitLong(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    assert false: "TBI";
    return null;
  }

  /** Visit a MetaVariable = Identifier. */
  public final String visitMetaVariable(final GNode n) throws Exception {
    assert false : "not implemented yet";
    return null;
  }

  /** Visit the MultiplicativeExpression expression node. */
  public final String visitMultiplicativeExpression(final GNode n)
      throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the NewArrayExpression expression node. */
  public final String visitNewArrayExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the NewClassExpression expression node. */
  public final String visitNewClassExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a NextCommand = (no children). */
  public final void visitNextCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      clearDebuggerContext();
      Event e = dbg.next();
      if (e instanceof NativeStepCompletionEvent
          || e instanceof JavaStepCompletionEvent
          || e instanceof Java2NativeReturnEvent
          || e instanceof Native2JavaReturnEvent) {
        SourceFileAndLine loc = dbg.getCurrentSourceLevelLocation();
        String line = dbg.getCurrentSourceLine();
        assert loc != null : "step must be completed at the source line";
        dbg.out("Step completed: %s\n%s\n", loc, line);        
      } else if ( e instanceof NativeBreakPointHitEvent) {
        EventLoop.reportEvent(dbg, (NativeBreakPointHitEvent)e);
      } else if ( e instanceof JavaBreakPointHitEvent) {
        EventLoop.reportEvent(dbg, (JavaBreakPointHitEvent)e);
      } else {
        assert false: "unrecognized event during stepping :" + e;
      }      
    } catch (Exception e) {
      dbg.err("could not correctly perform the next command.\n");
    }
  }

  /** Visit an NullLiteral = (no children). */
  public final String visitNullLiteral(final GNode n) throws Exception{
    assert getLanguage(n) == Language.JAVA;
    return gen("(%s)", "null");
  }

  /** Visit the ParameterDeclaration expression node. */
  public final String visitParameterDeclaration(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    if (n.get(1) == null) {
      return gen("%s", (String)dispatch(n.getNode(0)));
    } else {
      return gen("%s %s", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
    }
  }

  /** Visit the ParameterList expression node. */
  public final String visitParameterList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] exprs= new String[n.size()];
    for (int i=0; i<n.size(); i++) {
        exprs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(",", exprs));
  }

  /** Visit the ParameterTypeList expression node. */
  public final String visitParameterTypeList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    if (n.get(1) == null) {
      return gen("%s", (String)dispatch(n.getNode(0)));
    } else {
      return gen("%s, ...", (String)dispatch(n.getNode(0)));
    }
  }

  /** Visit the Pointer expression node. */
  public final String visitPointer(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("* %s %s", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
  }

  /** Visit the PointerDeclarator expression node. */
  public final String visitPointerDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("* %s %s", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
  }

  /** Visit the PostdecrementExpression expression node. */
  public final String visitPostdecrementExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(%s--)", (String)dispatch(n.getNode(0)));
  }

  /** Visit the PostfixExpression expression node. */
  public final String visitPostfixExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the PostincrementExpression expression node. */
  public final String visitPostincrementExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(%s++)", (String)dispatch(n.getNode(0)));
  }

  /** Visit the PredecrementExpression expression node. */
  public final String visitPredecrementExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(--%s)", (String)dispatch(n.getNode(0)));
  }

  /** Visit the PreincrementExpression expression node. */
  public final String visitPreincrementExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(++%s)", (String)dispatch(n.getNode(0)));
  }

  /** Visit a PrimaryIdentifier = String. */
  public String visitPrimaryIdentifier(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String idName = (String)n.get(0);

    //try id remapping for the Jeannie frame.
    ensureDebuggerContext();
    SourceFileAndLine loc = debuggerContext.getCurrentLocation();
    VariableRemapEntry idRemap = jeannieSymbolRemapper.lookUpVariableRemap(idName, loc
        .getSourceFile(), loc.getSourceLine());
    String idExpr = null;
    if (idRemap != null) {
      idExpr = idRemap.targetLanguageExpression();
    }
    if (idExpr == null) {
      idExpr = idName;
    }

    return gen("(%s)", idExpr);
  }

  /** Visit the PrimitiveType expression node. */
  public final String visitPrimitiveType(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a PrintCExpressionCommand = C.Expression. */
  public final void visitPrintCExpressionCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      breakpointManager.freezeActiveBreakPoints();
      Object obj = dispatch(n.getNode(0));
      dbg.out("====> %s\n", print_c((String)obj));
    } catch(Exception e) {
      dbg.err("could not correctly print the final result\n");
    } finally {
      breakpointManager.unfreezeAllBreakpoints();
      resetConvenienceVariables();
      dbg.ensurePureContext();
    }
  }

  /** Visit a PrintJavaExpressionCommand = Java.Expression. */
  public final void visitPrintJavaExpressionCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      breakpointManager.freezeActiveBreakPoints();
      Object obj = dispatch(n.getNode(0));
      if (obj == null) {return;}
      dbg.out("=====> %s\n", print_j((String)obj));
    } catch(Exception e) {
      dbg.err("could not correctly print the final result\n");
    } finally {
      breakpointManager.unfreezeAllBreakpoints();
      resetConvenienceVariables();
      dbg.ensurePureContext();
    }
  }

  /** Visit a QualifiedIdentifier = Identifier+. */
  public final String visitQualifiedIdentifier(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    return gen("%s", Utilities.qualifiedIdentifierToString(n));  
  }

  /** Visit the RelationalExpression expression node. */
  public final String visitRelationalExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit a NextCommand = (no children). */
  public final void visitRunCommand(final GNode n) {
    dbg.run();
  }

  /** Visit a SelectionExpression = Expression Identifier. */
  public final String visitSelectionExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    return gen("(%s.%s)", ((String)dispatch(n.getNode(0))), n.getString(1));
  }

  /** Visit the ShiftExpression expression node. */
  public final String visitShiftExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String lhs = (String) dispatch(n.getNode(0));
    String op = (String) (n.get(1));
    String rhs = (String) dispatch(n.getNode(2));
    return gen("(%s %s %s)", lhs, op, rhs);
  }

  /** Visit the Short expression node. */
  public final String visitShort(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("short");
  }

  /** Visit the Signed expression node. */
  public final String visitSigned(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("%s", n.getString(0));
  }

  /** Visit the SimpleDeclarator expression node. */
  public final String visitSimpleDeclarator(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return n.getString(0);
  }

  /** Visit the SizeofExpression expression node. */
  public final String visitSizeofExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(sizeof(%s))", (String)dispatch(n.getNode(0)));
  }

  /** Visit the SpecifierQualifierList expression node. */
  public final String visitSpecifierQualifierList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] specs = new String[n.size()];
    for(int i = 0;i < specs.length;i++) {
      specs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(" ", specs));
  }

  /** Visit a StatCommand = (no children). */
  public final void visitStatCommand(final GNode n) {
    dbg.out("control: %s\n", dbg.getDebugControlStatus());
  }

  /** Visit a StepCommand = (no children). */
  public final void visitStepCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
     dbg.err("Blink is not initialized to run this command\n");
     return;
    }
    try {
      clearDebuggerContext();
      dbg.step();
      SourceFileAndLine loc = dbg.getCurrentSourceLevelLocation();
      String line = dbg.getCurrentSourceLine();
      assert loc != null : "step must be completed at the source line";
      dbg.out("Step completed: %s\n%s\n", loc, line);
    } catch(Exception e) {
      dbg.err("could not sucessfully perform stepping\n");
    }
  }

  /** Visit an StringConstant = String. */
  public final String visitStringConstant(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    assert n.size() == 1;
    return gen("(%s)", n.getString(0));
  }

  /** Visit an StringLiteral = String. */
  public final String visitStringLiteral(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    return gen("(%s)",n.getString(0));
  }

  /** Visit the StructureTypeReference expression node. */
  public final String visitStructureTypeReference(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    assert n.get(0) == null;
    return gen("struct %s", n.getString(1));
  }

  /** Visit a SubscriptExpression = Expression Expression. */
  public final String visitSubscriptExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C || getLanguage(n) == Language.JAVA;
    String exprArray = (String) dispatch(n.getNode(0));
    String exprIndex = (String) dispatch(n.getNode(1));
    return gen("(%s[%s])", exprArray, exprIndex);
  }

  /** Visit the SuperExpression expression node. */
  public final String visitSuperExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit a ThisExpression = [Expression]. */
  public final void visitThisExpression(final GNode n) {
    assert getLanguage(n) == Language.JAVA;
    assert false : "The Blink debugger does not support" + 
    "qualified this in Java expression.";
  }

  /** Visit the Type expression node. */
  public final String visitType(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the TypeArguments expression node. */
  public final String visitTypeArguments(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the TypedefName expression node. */
  public final String visitTypedefName(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("%s", n.getString(0));
  }

  /** Visit the TypeInstantiation expression node. */
  public final String visitTypeInstantiation(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the TypeName expression node. */
  public final String visitTypeName(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    if (n.get(1) == null) {
      return gen("%s", (String)dispatch(n.getNode(0)));
    } else {
      return gen("%s %s", (String)dispatch(n.getNode(0)), (String)dispatch(n.getNode(1)));
    }
  }

  /** Visit the TypeParameter expression node. */
  public final String visitTypeParameter(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the TypeParameters expression node. */
  public final String visitTypeParameters(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the TypeQualifierList expression node. */
  public final String visitTypeQualifierList(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    String[] specs = new String[n.size()];
    for(int i = 0;i < specs.length;i++) {
      specs[i] = (String)dispatch(n.getNode(i));
    }
    return gen("%s", join(" ", specs));
  }

  /** Visit the UnaryExpression expression node. */
  public final String visitUnaryExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the UnaryMinusExpression expression node. */
  public final String visitUnaryMinusExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(-%s)", (String)dispatch(n.getNode(0)));
  }

  /** Visit the UnaryPlusExpression expression node. */
  public final String visitUnaryPlusExpression(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("(+%s)", (String)dispatch(n.getNode(0)));
  }
  /** Visit the UnionTypeReference expression node. */
  public final String visitUnionTypeReference(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    assert n.get(0) == null;
    return gen("struct %s", n.getString(1));
  }

  /** Visit the Unsigned expression node. */
  public final String visitUnsigned(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("unsigned");
  }

  /** Visit an UpCommand = IntegerLiteral. */
  public final void visitUpCommand(final GNode n) {
    int steps = Integer.parseInt( n.getNode(0).getString(0));
    try {
      ensureDebuggerContext();
      debuggerContext.unWindStack(dbg, steps);
    } catch (Exception e) {
      dbg.err("could not perform up\n");
    } finally {
      dbg.ensurePureContext();
    }
  }

  /** Visit the VoidType expression node. */
  public final String visitVoidType(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the VoidTypeSpecifier expression node. */
  public final String visitVoidTypeSpecifier(final GNode n) throws Exception {
    assert getLanguage(n) == Language.C;
    return gen("void");
  }

  /** Visit a WatchCExpressionCommand = C.Expression. */
  public final void visitWatchCExpressionCommand(final GNode n) {
    assert false : "not yet implemented";
  }

  /** Visit a WatchJavaFieldCommand = [WatchKind] QualifiedIdentifier. */
  public final void visitWatchJavaFieldCommand(final GNode n) {
    assert false : "not yet implemented";
  }

  /** Visit a WhereCommand = (no children). */
  public final void visitWhereCommand(final GNode n) {
    if (!dbg.IsNativeDebuggerAttached()) {
      dbg.err("Blink is not initialized to run this command\n");
      return;
     }
    try {
      ensureDebuggerContext();
      debuggerContext.showWhere(dbg);
    } catch(Exception e) {
      dbg.err("could not perform where command.\n");
    } finally {
      dbg.ensurePureContext();
    }
  }

  /** Visit the Wildcard expression node. */
  public final String visitWildcard(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }

  /** Visit the WildcardBound expression node. */
  public final String visitWildcardBound(final GNode n) throws Exception {
    assert getLanguage(n) == Language.JAVA;
    assert false: "TBI";
    return null;
  }
}
