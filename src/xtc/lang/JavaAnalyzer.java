/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2006-2011 IBM Corp., Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */
package xtc.lang;

import java.io.File;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import xtc.Constants;
import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.type.AliasT;
import xtc.type.AnnotatedT;
import xtc.type.ArrayT;
import xtc.type.ClassOrInterfaceT;
import xtc.type.ClassT;
import xtc.type.ErrorT;
import xtc.type.IntegerT;
import xtc.type.InterfaceT;
import xtc.type.LabelT;
import xtc.type.MethodT;
import xtc.type.NumberT;
import xtc.type.PackageT;
import xtc.type.Type;
import xtc.type.VoidT;
import xtc.type.WrappedT;
import xtc.util.Runtime;
import xtc.util.SymbolTable;

/**
 * A visitor that constructs a symbol table for a Java compilation unit. Assumes
 * that the AST has been simplified with JavaAstSimplifier. So far, the visitor
 * doesn't check for errors properly, it only populates the symbol table and
 * annotates AST nodes with their type.
 *
 * <h4>Jacks regression tests</h4>
 *
 * You can use JavaDriver to run the "jacks" compiler regression
 * testing suite for this type checker.
 * Download jacks by doing<ul>
 *   <li>cvs -z 9 -d :pserver:anoncvs@sources.redhat.com:/cvs/mauve co jacks</ul>
 * Make sure it works by setting JAVAC in setup_javac, then doing<ul>
 *   <li>./jacks javac "3.2-valid-1 3.2-invalid-1"</ul>
 * That should report something like<ul>
 *   <li>javac: Total   5011    Passed  2   Skipped 5009    Failed  0</ul>
 * Create an xtc_setup file: copy javac_setup, then change:<ul>
 *   <li>set JAVA_HOME ""
 *   <li>set JAVAC /usr/bin/java
 *   <li>set JAVAC_FLAGS "-cp /Users/hirzel/jeannie/java/classes xtc.lang.JavaDriver -ast -simplifyAST -analyze"
set JAVA "this_variable_intentionally_nonsensical"
 *   <li>set JAVA "this_variable_intentionally_nonsensical"</ul>
 * or whatever is appropriate for your paths. Yes, we intentionally set JAVAC "java",
 * since xtc.lang.JavaAnalyzer will run on a Java virtual machine.<br>
 * Now, try that it works by doing<ul>
 *   <li>./jacks xtc "3.2-valid-1 3.2-invalid-1"</ul>
 * That should report something like<ul>
 *   <li>xtc: Total   5011    Passed  2   Skipped 5009    Failed  0</ul>
 * To run the remaining 5009 tests, omit the last command line argument, and be
 * very patient.
 *
 * @author Martin Hirzel
 */
public class JavaAnalyzer extends Visitor {
  public static final class JavaContext {
    /** Handled by enclosing try/catch, or declared as thrown by enclosing method. */
    public List<Type> _handledExceptions = new ArrayList<Type>();

    /** False if scope should also include parameters of method, catch, or for. */
    public boolean _hasScope = true;

    /** Current expression or array initializer is expected to initialize variable of target type. */
    Type _initializing = null;
    
    /** Can do "break" or "continue" for enclosing while/do/for loop. */
    public boolean _loop = false;
    
    /** Can not use "this" or instance member. */
    public boolean _static = false;
    
    /** Can do "break" for enclosing switch statement. */
    public boolean _switch = false;
    
    public final void restore(final JavaContext other) {
      _handledExceptions = other._handledExceptions;
      _hasScope = other._hasScope;
      _initializing = other._initializing;
      _loop = other._loop;
      _static = other._static;
      _switch = other._switch;
    }
    
    public final JavaContext save() {
      final JavaContext result = new JavaContext();
      result.restore(this);
      return result;
    }
  }
  
  public static Type getRValueNoError(final Type type) {
    assert null != type;
    if (type.isVoid())
      return type;
    if (JavaEntities.isExpressionT(type)) {
      final boolean isL = JavaEntities.isGeneralLValueT(type);
      final Type result = isL ? JavaEntities.dereference(type) : type;
      assert JavaEntities.isGeneralRValueT(result);
      return result;
    }
    return null;
  }

  protected static boolean hasModifier(final Type t, final String m) {
    return JavaEntities.hasModifier(t, m);
  }
  
  public static Type setType(final Node n, final Type result) {
    if (result.isMethod())
      assert n.hasName("Arguments") || n.hasName("MethodDeclaration") || n.hasName("DeconstructorDeclaration");
    n.setProperty(Constants.TYPE, result);
    return result;
  }
  protected final JavaExternalAnalyzer _externalAnalyzer;
  public final JavaContext _context;
  protected final Runtime _runtime;

  protected final SymbolTable _table;

  public JavaAnalyzer(final Runtime runtime, final SymbolTable table) {
    _context = new JavaContext();
    _externalAnalyzer = newExternalAnalyzer(runtime, table);
    _runtime = runtime;
    _table = table;
    JavaEntities.addBaseTypes(_table);
  }

  public JavaExternalAnalyzer newExternalAnalyzer(final Runtime runtime, final SymbolTable table) {
    return new JavaExternalAnalyzer(runtime, table);
  }

  /** Use this for asserting that the input is typed correctly. */
  protected boolean assrt(final Node n, final boolean cond,
      final String msgFormat, final Object... msgArgs) {
    return JavaEntities.runtimeAssrt(_runtime, n, cond, msgFormat, msgArgs);
  }

  protected void assrtLegalHandledExceptions(final GNode n) {
    assert null == n || n.hasName("ThrowsClause") : n.getName();
    final Type tThrowable = JavaEntities.tThrowable(_table);
    final List<Type> legal = new ArrayList<Type>();
    for (int i=0; i<_context._handledExceptions.size(); i++) {
      final Type e = resolveIfAlias(_context._handledExceptions.get(i), n.getNode(i));
      final boolean ok = e.isError() || JavaTypeConverter.isAssignable(_table, classpath(), tThrowable, e);
      if (assrt(n.getNode(i), ok, "throwable expected"))
        legal.add(e);
    }
    _context._handledExceptions = legal;
  }
  
  protected void assrtLegalIdentifier(final GNode n, final String id) {
    assrt(n, !"true".equals(id), "illegal identifier");
    assrt(n, !"false".equals(id), "illegal identifier");
    assrt(n, !"null".equals(id), "illegal identifier");
  }

  protected void assrtLegalMethod(final GNode n, final MethodT method) {
    final ClassOrInterfaceT base = JavaEntities.declaringType(_table, method);
    for (final MethodT m : JavaEntities.methodsOwn(base))
      assrt(n, m == method || !JavaEntities.sameMethodSignature(method, m), "duplicate method");
    if (!JavaEntities.isConstructor(JavaEntities.resolveToRawClassOrInterfaceT(base), method)) {
      final List<MethodT> methodsInherited = JavaEntities.methodsInherited(_table, classpath(), base, true);
      for (final MethodT sup : methodsInherited)
        if (JavaEntities.isSuperMethod(_table, classpath(), sup, method))
          assrtLegalOverride(n, sup, method);
    }
  }

  protected void assrtLegalMethodBody(final GNode n, final Type method) {
    if (null == n.get(7))
      assrt(n, hasModifier(method, "abstract") || hasModifier(method, "native"), "missing method body");
    else
      assrt(n, !hasModifier(method, "abstract") && !hasModifier(method, "native"), "unexpected method body");
  }

  private void assrtLegalOverride(final GNode n, final MethodT sup, final MethodT sub) {
    assrt(n, !hasModifier(sup, "final"), "cannot override final method");
    if (hasModifier(sup, "static"))
      assrt(n, hasModifier(sub, "static"), "instance method cannot override static method");
    else if (JavaEntities.sameMethodSignature(sup, sub))
      assrt(n, !hasModifier(sub, "static"), "static method cannot hide instance method");
    if (hasModifier(sup, "public"))
      assrt(n, hasModifier(sub, "public"), "cannot reduce visibility");
    else if (hasModifier(sup, "protected"))
      assrt(n, hasModifier(sub, "public") || hasModifier(sub, "protected"), "cannot reduce visibility");
    else
      assrt(n, !hasModifier(sub, "private"), "cannot reduce visibility");
    resolveIfAlias(sup.getResult());
    assrt(n, JavaEntities.sameMethodReturnType(sup, sub), "incompatible return type");
    for (final Type e1 : sub.getExceptions()) {
      boolean declared = false;
      for (final Type e2 : sup.getExceptions())
        if (JavaEntities.isSuperClass(_table, classpath(), e2, e1)) {
          declared = true;
          break;
        }
      assrt(n, declared, "incompatible throws clause in overriding method");
    }
  }

  public final List<File> classpath() {
    return JavaEntities.classpath(_runtime);
  }

  public Type dispatchRValue(final GNode n) {
    final Type type = (Type) dispatch(n);
    if (null == type || type.isPackage()) {
      _runtime.error("unknown or ambiguous name", n);
      return JavaEntities.nameToBaseType("int");
    }
    return getRValue(type, n);
  }

  private static char escapeSequenceChar(final String s, final int start) {
    // gosling_et_al_2000 3.3 and 3.10.6
    final int len = s.length();
    assert start + 1 <= len && '\\' == s.charAt(start);
    switch (s.charAt(start + 1)) {
    case 'b':
      return '\b';
    case 't':
      return '\t';
    case 'n':
      return '\n';
    case 'f':
      return '\f';
    case 'r':
      return '\r';
    case '"':
      return '"';
    case '\'':
      return '\'';
    case '\\':
      return '\\';
    }
    int c = 0, i = start + 1;
    while (i < len && '0' <= s.charAt(i) && s.charAt(i) < '8') {
      c = 8 * c + s.charAt(i) - '0';
      i++;
    }
    assert i != start + 1;
    return (char) c;
  }

  private final int escapeSequenceEnd(final String s, final int start) {
    // gosling_et_al_2000 3.3 and 3.10.6
    final int len = s.length();
    assert start + 1 <= len && '\\' == s.charAt(start);
    switch (s.charAt(start + 1)) {
    case 'b':
    case 't':
    case 'n':
    case 'f':
    case 'r':
    case '"':
    case '\'':
    case '\\':
      return start + 2;
    }
    int c = 0, i = start + 1;
    while (i < len && '0' <= s.charAt(i) && s.charAt(i) < '8') {
      c = 8 * c + s.charAt(i) - '0';
      i++;
    }
    return i;
  }

  private Type getRValue(final Type type, final GNode n) {
    final Type result = getRValueNoError(type);
    if (null == result) {
      _runtime.error("unknown or ambiguous name", n);
      return ErrorT.TYPE;
    }
    return result;
  }

  private final boolean isAssignable(final int src, final Type tgt) {
    // gosling_et_al_2000 5.2
    if (JavaEntities.nameToBaseType("byte") == tgt)
      return (byte) src == src;
    if (JavaEntities.nameToBaseType("char") == tgt)
      return (char) src == src;
    if (JavaEntities.nameToBaseType("short") == tgt)
      return (short) src == src;
    return true;
  }

  public boolean isHandled(final Type tThrown) {
    final List<File> classpath = classpath();
    for (final Type tCaught : _context._handledExceptions)
      if (JavaTypeConverter.isAssignable(_table, classpath, tCaught, tThrown))
        return true;
    return false;
  }

  private boolean isStringConstant(final Type x) {
    return x.hasConstant() && JavaEntities.isReferenceT(x) && JavaTypeConverter.isIdentical(x, JavaEntities.tString(_table));
  }

  private Type processBitwiseBinaryExpression(final GNode n, final String operator) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(1));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final Type result;
    Type tBool = JavaEntities.nameToBaseType("boolean");
    final boolean xIsBool = JavaTypeConverter.isIdentical(x, tBool), yIsBool = JavaTypeConverter.isIdentical(y, tBool);
    assert "&".equals(operator) || "|".equals(operator) || "^".equals(operator);
    if (xIsBool || yIsBool) {
      if (!assrt(n, xIsBool && yIsBool, "operator type mismatch"))
        return setType(n, ErrorT.TYPE);
      if (x.hasConstant() && y.hasConstant()) {
        final boolean valX = x.getConstant().isTrue();
        final boolean valY = y.getConstant().isTrue();
        if ("&".equals(operator))
          result = tBool.annotate().constant(valX & valY);
        else if ("|".equals(operator))
          result = tBool.annotate().constant(valX | valY);
        else
          result = tBool.annotate().constant(valX ^ valY);
      } else {
        result = tBool;
      }
    } else {
      final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
      final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
      if (null == promX || !JavaEntities.resolveToRawRValue(promX).isInteger()) {
        _runtime.error("integral operator expected", n.getNode(0));
        result = x;
      } else if (null == promY || !JavaEntities.resolveToRawRValue(promY).isInteger()) {
        _runtime.error("integral operator expected", n.getNode(2));
        result = x;
      } else if (!x.hasConstant() || !y.hasConstant()){
        result = promX;
      } else {
        final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
        final Number valNumX = (Number) promX.getConstant().getValue();
        final Number valNumY = (Number) promY.getConstant().getValue();
        switch (typNum.getKind()) {
        case INT: {
          final int valX = valNumX.intValue(), valY = valNumY.intValue();
          if ("&".equals(operator))
            result = typNum.annotate().constant(new Integer(valX & valY));
          else if ("|".equals(operator))
            result = typNum.annotate().constant(new Integer(valX | valY));
          else
            result = typNum.annotate().constant(new Integer(valX ^ valY));
          break;
        }
        case LONG: {
          final long valX = valNumX.longValue(), valY = valNumY.longValue();
          if ("&".equals(operator))
            result = typNum.annotate().constant(new Long(valX & valY));
          else if ("|".equals(operator))
            result = typNum.annotate().constant(new Long(valX | valY));
          else
            result = typNum.annotate().constant(new Long(valX ^ valY));
          break;
        }
        default:
          throw new Error();
        }
      }
    }
    return setType(n, result);
  }

  private Type processTypeName(final GNode n) {
    if (n.hasName("PrimitiveType"))
      return (Type) dispatch(n);
    assert n.hasName("QualifiedIdentifier");
    final String typeName = (String) dispatch(n);
    final ClassOrInterfaceT result = JavaEntities.qualifiedNameToType(_table, classpath(), _table.current().getQualifiedName(), typeName);
    return result;
  }
  
  protected final Type resolveIfAlias(final Type type) {
    return resolveIfAlias(type, null);
  }

  protected final Type resolveIfAlias(final Type type, final Node n) {
    final Type resolved = JavaEntities.resolveIfAlias(_table, classpath(), _table.current().getQualifiedName(), type);
    if (null == resolved || resolved.isAlias() && null == resolved.toAlias().getType()) {
      if (null != n)
        _runtime.error("unknown class or interface " + type.toAlias().getName(), n);
      return ErrorT.TYPE;
    }
    return resolved;
  }

  /**
   * Visit an AdditiveExpression = Expression ("+" / "-") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#15746">&sect;15.18</a>).
   */
  public final Type visitAdditiveExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final Type result;
    if ("+".equals(n.getString(1))) {
      final Type tString = JavaEntities.tString(_table);
      if (JavaTypeConverter.isIdentical(tString, x)
          || JavaTypeConverter.isIdentical(tString, y)) {
        if (x.hasConstant() && y.hasConstant()) {
          final Type convX = JavaTypeConverter.convertString(_table, x);
          final Type convY = JavaTypeConverter.convertString(_table, y);
          final String valX = (String) convX.getConstant().getValue();
          final String valY = (String) convY.getConstant().getValue();
          result = tString.annotate().constant(valX + valY);
        } else {
          result = tString;
        }
      } else {
        final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
        final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
        if (null == promX || null == promY) {
          _runtime.error("String or numeric operands expected", n);
          result = JavaEntities.nameToBaseType("double");
        } else if (!promX.hasConstant() || !promY.hasConstant()) {
          result = JavaEntities.resolveToRawRValue(promX);
        } else {
          final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
          final Number valNumX = (Number) promX.getConstant().getValue();
          final Number valNumY = (Number) promY.getConstant().getValue();
          switch (typNum.getKind()) {
          case INT: {
            final int valX = valNumX.intValue(), valY = valNumY.intValue();
            result = typNum.annotate().constant(new Integer(valX + valY));
            break;
          }
          case LONG: {
            final long valX = valNumX.longValue(), valY = valNumY.longValue();
            result = typNum.annotate().constant(new Long(valX + valY));
            break;
          }
          case FLOAT: {
            final float valX = valNumX.floatValue(), valY = valNumY
                .floatValue();
            result = typNum.annotate().constant(new Float(valX + valY));
            break;
          }
          case DOUBLE: {
            final double valX = valNumX.doubleValue(), valY = valNumY
                .doubleValue();
            result = typNum.annotate().constant(new Double(valX + valY));
            break;
          }
          default:
            throw new Error();
          }
        }
      }
    } else {
      assert "-".equals(n.getString(1));
      final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
      final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
      if (null == promX || null == promY) {
        _runtime.error("numeric operands expected", n);
        result = JavaEntities.nameToBaseType("double");
      } else if (!promX.hasConstant() || !promY.hasConstant()) {
        result = JavaEntities.resolveToRawRValue(promX);
      } else {
        final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
        final Number valNumX = (Number) promX.getConstant().getValue();
        final Number valNumY = (Number) promY.getConstant().getValue();
        switch (typNum.getKind()) {
        case INT: {
          final int valX = valNumX.intValue(), valY = valNumY.intValue();
          result = typNum.annotate().constant(new Integer(valX - valY));
          break;
        }
        case LONG: {
          final long valX = valNumX.longValue(), valY = valNumY.longValue();
          result = typNum.annotate().constant(new Long(valX - valY));
          break;
        }
        case FLOAT: {
          final float valX = valNumX.floatValue(), valY = valNumY.floatValue();
          result = typNum.annotate().constant(new Float(valX - valY));
          break;
        }
        case DOUBLE: {
          final double valX = valNumX.doubleValue(), valY = valNumY
              .doubleValue();
          result = typNum.annotate().constant(new Double(valX - valY));
          break;
        }
        default:
          throw new Error();
        }
      }
    }
    return setType(n, result);
  }
  
  /**
   * Visit Arguments = Expression* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#41147">&sect;15.9</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#20448">&sect;15.12</a>).
   */
  public final List<Type> visitArguments(final GNode n) {
    final List<Type> result = new ArrayList<Type>(n.size());
    for (int i = 0; i < n.size(); i++)
      result.add(dispatchRValue(n.getGeneric(i)));
    return result;
  }
  
  /**
   * Visit an ArrayInitializer = VariableInitializer* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/arrays.doc.html#11358">&sect;10.6</a>).
   * Note: VariableInitializer &gt; ArrayInitializer, Expression.
   */
  public final Type visitArrayInitializer(final GNode n) {
    if (assrt(n, _context._initializing.isArray(), "array initializer type mismatch")) {
      final JavaContext savedContext = _context.save();
      _context._initializing = JavaEntities.arrayElementType(_context._initializing.toArray());
      for (int i = 0; i < n.size(); i++) {
        final Type src = dispatchRValue(n.getGeneric(i));
        assrt(n.getGeneric(i), JavaTypeConverter.isAssignable(_table, classpath(), _context._initializing, src), "array initializer type mismatch");
      }
      _context.restore(savedContext);
    }
    return setType(n, _context._initializing);
  }
  
  public final void visitBasicCastExpression(final GNode n) {
    assert false : "must run JavaAstSimplifier first";
  }

  /** Visit a BasicForControl = VariableModifiers Type Declarators [Expression] [ExpressionList]
   *  / null null [ExpressionList] [Expression] [ExpressionList]
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#24588">&sect;14.13</a>).
   */
  public final void visitBasicForControl(final GNode n) {
    if (null == n.get(1)) {
      assert null == n.get(0);
    } else {
      @SuppressWarnings("unchecked")
      final List<Attribute> modifiers = (List<Attribute>) dispatch(n.getNode(0));
      final Type type = (Type) dispatch(n.getGeneric(1));
      _externalAnalyzer.processDeclarators(modifiers, type, n.getGeneric(2));
    }
    dispatch(n.getGeneric(2));
    if (null != n.get(3)) {
      final Type condition = (Type) dispatch(n.getGeneric(3));
      assrt(n.getGeneric(3), JavaEntities.resolveToRawRValue(condition).isBoolean(),
        "condition must be boolean");
    }
    dispatch(n.getGeneric(4));
  }

  /**
   * Visit a BitwiseAndExpression = Expression Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5228">&sect;15.22</a>, 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitBitwiseAndExpression(final GNode n) {
    return processBitwiseBinaryExpression(n, "&");
  }
  
  /**
   * Visit a BitwiseNegationExpression = Expression
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#4990">&sect;15.15</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitBitwiseNegationExpression(final GNode n) {
    final Type type = (Type) dispatch(n.getGeneric(0));
    if (type.isError())
      return setType(n, type);
    final Type promoted = JavaTypeConverter.promoteUnaryNumeric(getRValue(type, n.getGeneric(0)));
    if (!assrt(n, null != promoted, "operand must be numeric"))
      return setType(n, ErrorT.TYPE);
    if (promoted.hasConstant()) {
      final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promoted);
      final Number valNum = (Number) promoted.getConstant().getValue();
      switch (typNum.getKind()) {
      case INT: {
        final int valInt = valNum.intValue();
        return typNum.annotate().constant(new Integer(~valInt));
      }
      case LONG: {
        final long valLong = valNum.longValue();
        return typNum.annotate().constant(new Long(~valLong));
      }
      default: {
        assrt(n, false, "operand must be an integral type");
        return setType(n, ErrorT.TYPE);
      }
      }
    } else {
      return setType(n, promoted);
    }
  }
  
  /**
   * Visit a BitwiseOrExpression = Expression Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5228">&sect;15.22</a>, 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitBitwiseOrExpression(final GNode n) {
    return processBitwiseBinaryExpression(n, "|");
  }
  
  /**
   * Visit a BitwiseXorExpression = Expression Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5228">&sect;15.22</a>, 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitBitwiseXorExpression(final GNode n) {
    return processBitwiseBinaryExpression(n, "^");
  }
  
  /**
   * Visit a Block = DeclarationOrStatement* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#246838">&sect;14.2</a>).
   */
  public final Type visitBlock(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._hasScope = true;
    if (savedContext._hasScope) {
      _table.enter(_table.freshName("block"));
      _table.mark(n);
    }
    for (int i = 0; i < n.size(); i++)
      dispatch(n.getNode(i));
    if (savedContext._hasScope)
      _table.exit();
    _context.restore(savedContext);
    return JavaEntities.nameToBaseType("void");
  }
  
  /** Visit a BlockDeclaration = ["static"] Block (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#246032">&sect;8.6</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#39245">&sect;8.7</a>). */
  public final void visitBlockDeclaration(final GNode n) {
    final JavaContext savedContext = _context.save();
    assert JavaEntities.isScopeForMember(_table.current().getQualifiedName());
    final ClassOrInterfaceT enclosingType = JavaEntities.currentType(_table);
    assert JavaEntities.isWrappedClassT(enclosingType);
    _context._static = null != n.get(0);
    if (JavaEntities.isTypeInner(enclosingType))
      assrt(n, !_context._static, "inner classes may not declare static initializers");
    _context._handledExceptions = new ArrayList<Type>();
    final ClassT clazz = (ClassT) JavaEntities.resolveToRawRValue(enclosingType);
    final boolean isAnonymous = JavaEntities.isTypeAnonymous(clazz);
    if (isAnonymous) {
      _context._handledExceptions.add(JavaEntities.tThrowable(_table));
    } else if (_context._static) {
      // no checked exceptions allowed in static initializer
    } else {
      boolean firstConstructor = true;
      for (final Type m : clazz.getMethods()) {
        final MethodT method = m.toMethod();
        if (JavaEntities.isConstructor(clazz, method)) {
          final List<Type> nuw = method.getExceptions();
          if (firstConstructor) {
            _context._handledExceptions.addAll(nuw);
            firstConstructor = false;
          } else {
            final Set<String> old = new HashSet<String>();
            for (final Type t : _context._handledExceptions)
              old.add(((ClassT) JavaEntities.resolveToRawRValue(t)).getQName());
            _context._handledExceptions.clear();
            for (final Type t : nuw) {
              final String q = ((ClassT) JavaEntities.resolveToRawRValue(t)).getQName();
              if (old.contains(q))
                _context._handledExceptions.add(t);
            }
          }
        }
      }
    }
    dispatch(n.getGeneric(1));
    _context.restore(savedContext);
  }
  
  /**
   * Visit a BooleanLiteral (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#49652">&sect;3.10.3</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitBooleanLiteral(final GNode n) {
    final Type tBool = JavaEntities.nameToBaseType("boolean");
    final boolean isTrue = "true".equals(n.getString(0));
    return setType(n, tBool.annotate().constant(isTrue));
  }

  /**
   * Visit a BreakStatement = [Identifier] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6842">&sect;14.14</a>).
   */
  public final void visitBreakStatement(final GNode n) {
    if (null == n.get(0)) {
      assrt(n, _context._loop || _context._switch, "break without label can only be used in loop or switch");
    } else {
      final String simpleName = n.getString(0);
      final String symbol = SymbolTable.toLabelName(simpleName);
      final LabelT label = (LabelT) _table.current().lookup(symbol);
      assrt(n, null != label, "the label " + simpleName + " is missing");
    }
  }

  /**
   * Visit a CallExpression = [Expression] null MethodName Arguments
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#20448">&sect;15.12</a>).
   */
  public final Type visitCallExpression(final GNode n) {
    // TD 21 (15.12) CallExpression = [Expression] MethodName Arguments
    final Type typeToSearch;
    final boolean inStaticContext;
    String identifier = n.getString(2);
    if ("super".equals(identifier) && n.get(0) == null) {
      // TD 08 (8.8.5.1) allow explicit constructor invocations via this() and super()
      typeToSearch = JavaEntities.currentType(_table).toClass().getParent();
      identifier = resolveIfAlias(typeToSearch).toClass().getName();
      inStaticContext = false;
    } else if (n.get(0) == null) {
      final SymbolTable.Scope oldScope = _table.current();
      outer: while (true) {
        final ClassOrInterfaceT t = JavaEntities.currentType(_table);
        JavaEntities.enterScopeByQualifiedName(_table, JavaEntities.typeToScopeName(t));
        for (final MethodT m : JavaEntities.methodsOwnAndInherited(_table, classpath(), t))
          if (m.getName().equals(identifier)) {
            typeToSearch = t;
            break outer;
          }
        if (JavaEntities.isTypeTopLevel(t)) {
          typeToSearch = t;
          break outer;
        }
        _table.exit();
      }
      _table.setScope(oldScope);
      inStaticContext = _context._static;
    } else {
      final Type t1 = (Type) dispatch(n.getGeneric(0));
      if (!assrt(n.getGeneric(0), !t1.isPackage(), "unknown idenfifier"))
        return setType(n, ErrorT.TYPE);
      inStaticContext = JavaEntities.isNotAValueT(t1);
      final Type t2 = inStaticContext ? JavaEntities.resolveToValue(t1.toAnnotated()) : t1;
      final Type t3 = getRValue(t2, n.getGeneric(0));
      final Type t4 = JavaEntities.isConstantT(t3) ? ((AnnotatedT)t3).getType() : t3;
      typeToSearch = resolveIfAlias(t4);
    }
    final List<Type> actuals = JavaEntities.typeList((List)dispatch(n.getNode(3)));
    for (final Type actual : actuals)
      if (actual.isError())
        return setType(n, ErrorT.TYPE);
    final MethodT method = JavaEntities.typeDotMethod(
        _table, classpath(), typeToSearch, true, identifier, actuals);
    if (!assrt(n, null != method && method.isMethod(), "no such method"))
      return setType(n, ErrorT.TYPE);
    assrt(n, hasModifier(method, "static") || !inStaticContext, "static call to non-static method");
    JavaEntities.resolveIfAliasMethod(_table, classpath(), method);
    for (final Type tThrown : method.getExceptions())
      if (JavaEntities.isCheckedException(_table, classpath(), tThrown))
        assrt(n, isHandled(tThrown), "uncaught exception");
    setType(n.getGeneric(3), method);
    return setType(n, method.getResult());
  }

  /** Visit a CaseClause = Expression DeclarationOrStatement* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#35518">&sect;14.10</a>). */
  public final Type visitCaseClause(final GNode n) {
    final Type key = (Type)dispatch(n.getGeneric(0));
    for (int i = 1; i < n.size(); i++)
      dispatch(n.getGeneric(i));
    return key;
  }

  /**
   * Visit a CastExpression = Type Expression (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#238146">&sect;15.16</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitCastExpression(final GNode n) {
    final Type tgt = (Type) dispatch(n.getGeneric(0));
    if (tgt.isError())
      return setType(n, ErrorT.TYPE);
    final Type src = dispatchRValue(n.getGeneric(1));
    final Type result = JavaTypeConverter.convertCasting(_table, classpath(), tgt, src);
    if (!assrt(n, null != result, "illegal cast"))
      return setType(n, ErrorT.TYPE);
    return setType(n, result);
  }

  /** Visit a CatchClause = FormalParameter Block (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#79311">&sect;14.19</a>). */
  public final Type visitCatchClause(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._hasScope = false;
    _table.enter(_table.freshName("catchClause"));
    _table.mark(n);
    final GNode pNode = n.getGeneric(0);
    final Type tParameter = dispatchRValue(pNode);
    final Type tThrowable = JavaEntities.tThrowable(_table);
    assrt(pNode, JavaEntities.isSuperClass(_table, classpath(), tThrowable,
        tParameter), "illegal type for exception parameter");
    dispatch(n.getGeneric(1));
    _table.exit();
    _context.restore(savedContext);
    return setType(n, tParameter);
  }

  /**
   * Visit a CharacterLiteral (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#100960">&sect;3.10.4</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitCharacterLiteral(final GNode n) {
    final String s = n.getString(0);
    final int len = s.length();
    assert 2 < len && '\'' == s.charAt(0) && '\'' == s.charAt(len - 1);
    Character value = null;
    if (3 == len) {
      value = new Character(s.charAt(1));
    } else {
      try {
        value = new Character(escapeSequenceChar(s, 1));
        if (!assrt(n, len == 1 + escapeSequenceEnd(s, 1), "illegal escape sequence"))
          return setType(n, ErrorT.TYPE);
      } catch (final IllegalArgumentException e) {
        _runtime.error("illegal escape sequence", n);
        return setType(n, ErrorT.TYPE);
      }
    }
    if (!assrt(n, 3 < len || '\r' != value.charValue() && '\n' != value.charValue(), "single character must not be line terminator"))
      return setType(n, ErrorT.TYPE);
    final Type tChar = JavaEntities.nameToBaseType("char");
    return setType(n, tChar.annotate().constant(value));
  }

  /**
   * Visit a ClassBody = Declaration* (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#18988">&sect;8.1.5</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#236431">&sect;9.1.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#41147">&sect;15.9</a>).
   */
  public final void visitClassBody(final GNode n) {
    //TD 07 (8.1.5, 9.1.3, 15.9) ClassBody = Declaration*
    for (int i = 0; i < n.size(); i++)
      dispatch(n.getNode(i));
  }

  /**
   * Visit a ClassDeclaration = Modifiers Identifier null [Extension]
   * [Implementation] ClassBody (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#15372">&sect;8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#247766">&sect;14.3</a>).
   */
  public final void visitClassDeclaration(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._handledExceptions = new ArrayList<Type>();
    _context._hasScope = true;
    _context._switch = false;
    _context._loop = false;
    final String simpleName = n.getString(1);
    assrtLegalIdentifier(n, simpleName);
    ClassT base = (ClassT) _table.current().lookupLocally(SymbolTable.toTagName(simpleName));
    if (null == base)
      base = _externalAnalyzer.visitClassDeclaration(n);
    else
      assrt(n, !JavaEntities.isScopeLocal(_table.current().getQualifiedName()), "conflicting classes");
    {
      final Type parent = base.getParent();
      if (parent.isAlias()) {
        final AliasT alias = parent.toAlias();
        resolveIfAlias(alias, n.getGeneric(3));
        if (null == alias.getType())
          alias.setType(JavaEntities.tObject(_table));
      }
      assrt(n.getGeneric(3), JavaEntities.isWrappedClassT(parent), "class expected");
      assrt(n.getGeneric(3), !hasModifier(parent, "final"), "can't subclass final class");
      assrt(n.getGeneric(3), JavaEntities.isAccessible(_table, classpath(), parent), "inner class not visible");
    }
    final Set<String> seenInterfaces = new HashSet<String>();
    for (int i=0; i<base.getInterfaces().size(); i++) {
      // gosling_et_al_2000 08.1.4
      final Type t = resolveIfAlias(base.getInterfaces().get(i), n.getGeneric(4).getNode(i));
      if (!t.isError() && assrt(n.getGeneric(4), t.isInterface(), "interface expected")) {
        final String qname = t.toInterface().getQName();
        assrt(n.getGeneric(4), !seenInterfaces.contains(qname), "duplicate superinterfaces");
        seenInterfaces.add(qname);
        assrt(n.getGeneric(4), JavaEntities.isAccessible(_table, classpath(), t), "superinterface not accessible");
      }
    }
    final boolean isAbstract = hasModifier(base, "abstract");
    if (JavaEntities.hasAbstractMethods(_table, classpath(), base))
      assrt(n, isAbstract, "must be abstract");
    assrt(n, !JavaEntities.hasCircularDependency(_table, classpath(), base), "circular class");
    _table.enter(simpleName);
    _table.mark(n.getNode(5));
    dispatch(n.getNode(5));
    _table.exit();
    if (isAbstract)
      assrt(n, JavaEntities.couldCreateConcreteSubclass(_table, classpath(), base), "conflicting abstract methods");
    _context.restore(savedContext);
  }
  
  /**
   * Visit a ClassLiteralExpression = Type (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#251530">&sect;15.8.2</a>).
   */
  public final Type visitClassLiteralExpression(final GNode n) {
    final Type t = (Type)dispatch(n.getNode(0));
    assert t.isError() || JavaEntities.isWrappedClassT(t) || JavaEntities.isWrappedInterfaceT(t) || t.isArray() || JavaEntities.isPrimitiveT(t);
    return setType(n, JavaEntities.tClass(_table));
  }
  
  /**
   * Visit a CompilationUnit = [PackageDeclaration] ImportDeclaration*
   * Declaration* (gosling_et_al_2000 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/packages.doc.html#40031">&sect;7.3</a>).
   */
  public void visitCompilationUnit(final GNode n) {
    _externalAnalyzer.dispatch(n);
    if (null == n.get(0))
      visitPackageDeclaration(null);
    else
      dispatch(n.getNode(0));
    _table.enter(JavaEntities.fileNameToScopeName(n.getLocation().file));
    _table.mark(n);
    for (int i = 1; i < n.size(); i++)
      dispatch(n.getNode(i));
    _table.setScope(_table.root());
  }

  /**
   * Visit a ConcreteDimensions = Expression+ (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#46168">&sect;15.10</a>).
   */
  public final List<Type> visitConcreteDimensions(final GNode n) {
    final List<Type> result = new ArrayList<Type>();
    for (int i = 0; i < n.size(); i++) {
      final Type r = dispatchRValue(n.getGeneric(i));
      result.add(r);
      final Type pr = null == r ? null : JavaTypeConverter.promoteUnaryNumeric(r);
      final Type rpr = null == pr ? null : JavaEntities.resolveToRawRValue(pr);
      assrt(n, null != rpr && rpr instanceof IntegerT && NumberT.Kind.INT == ((IntegerT)rpr).getKind(), "dimension must be integer");
    }
    return result;
  }

  /**
   * Visit a ConditionalExpression = Expression Expression Expression
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#290293">&sect;15.25</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitConditionalExpression(final GNode n) {
    final Type typCond = dispatchRValue(n.getGeneric(0));
    final Type rawCond = JavaEntities.resolveToRawRValue(typCond);
    final BigInteger valCond;
    if (rawCond.isBoolean()) {
      if (typCond.hasConstant())
        valCond = typCond.getConstant().bigIntValue();
      else
        valCond = null;
    } else {
      assrt(n, rawCond.isError(), "condition must be boolean");
      valCond = null;
    }
    final Type typX = dispatchRValue(n.getGeneric(1));
    final Type rawX = JavaEntities.resolveToRawRValue(typX);
    final Object valX = typX.hasConstant() ? typX.getConstant().getValue() : null;
    final Type typY = dispatchRValue(n.getGeneric(2));
    final Type rawY = JavaEntities.resolveToRawRValue(typY);
    final Object valY = typY.hasConstant() ? typY.getConstant().getValue() : null;
    final Type result;
    if (JavaTypeConverter.isIdentical(typX, typY)) {
      if (null == valCond)
        result = rawX;
      else
        result = BigInteger.ONE == valCond ? typX : typY;
    } else if (rawX.isNumber() && rawY.isNumber()) {
      final NumberT tByte = (NumberT) JavaEntities.nameToBaseType("byte");
      final NumberT tShort = (NumberT) JavaEntities.nameToBaseType("short");
      final NumberT tChar = (NumberT) JavaEntities.nameToBaseType("char");
      final NumberT tInt = (NumberT) JavaEntities.nameToBaseType("int");
      final NumberT rawResult;
      if (tByte == rawX && tShort == rawY || tShort == rawX && tByte == rawY) {
        rawResult = tShort;
      } else if (tByte == rawX && tInt == rawY && null != valY && (byte) ((Integer) valY).intValue() == ((Integer) valY).intValue()) {
        rawResult = tByte;
      } else if (tShort == rawX && tInt == rawY && null != valY && (short) ((Integer) valY).intValue() == ((Integer) valY).intValue()) {
        rawResult = tShort;
      } else if (tChar == rawX && tInt == rawY && null != valY && (char) ((Integer) valY).intValue() == ((Integer) valY).intValue()) {
        rawResult = tChar;
      } else if (tByte == rawY && tInt == rawX && null != valX && (byte) ((Integer) valX).intValue() == ((Integer) valX).intValue()) {
        rawResult = tByte;
      } else if (tShort == rawY && tInt == rawX && null != valX && (short) ((Integer) valX).intValue() == ((Integer) valX).intValue()) {
        rawResult = tShort;
      } else if (tChar == rawY && tInt == rawX && null != valX && (char) ((Integer) valX).intValue() == ((Integer) valX).intValue()) {
        rawResult = tChar;
      } else {
        final NumberT x = (NumberT) JavaTypeConverter.promoteBinaryNumeric(rawY, rawX);
        final NumberT y = (NumberT) JavaTypeConverter.promoteBinaryNumeric(rawX, rawY);
        if (!assrt(n, null != x && null != y, "type mismatch"))
          return setType(n, ErrorT.TYPE);
        rawResult = x;
      }
      if (BigInteger.ONE == valCond && null != valX) {
        final Object valResult;
        if (valX instanceof Number) {
          final Number numX = (Number) valX;
          switch (rawResult.getKind()) {
          case BYTE:   valResult = new Byte(numX.byteValue());            break;
          case SHORT:  valResult = new Short(numX.shortValue());          break;
          case CHAR:   valResult = new Character((char) numX.intValue()); break;
          case INT:    valResult = new Integer(numX.intValue());          break;
          case LONG:   valResult = new Long(numX.longValue());            break;
          case FLOAT:  valResult = new Float(numX.floatValue());          break;
          case DOUBLE: valResult = new Double(numX.doubleValue());        break;
          default: throw new Error();
          }
        } else {
          final char charX = ((Character) valX).charValue();
          switch (rawResult.getKind()) {
          case BYTE:   valResult = new Byte((byte)charX);   break;
          case SHORT:  valResult = new Short((short)charX); break;
          case CHAR:   valResult = new Character(charX);    break;
          case INT:    valResult = new Integer(charX);      break;
          case LONG:   valResult = new Long(charX);         break;
          case FLOAT:  valResult = new Float(charX);        break;
          case DOUBLE: valResult = new Double(charX);       break;
          default: throw new Error();
          }
        }
        result = rawResult.annotate().constant(valResult);
      } else if (BigInteger.ONE == valCond && null != valY) {
        final Number numY = (Number) valY;
        final Object valResult;
        switch (rawResult.getKind()) {
        case BYTE:   valResult = new Byte(numY.byteValue());            break;
        case SHORT:  valResult = new Short(numY.shortValue());          break;
        case CHAR:   valResult = new Character((char) numY.intValue()); break;
        case INT:    valResult = new Integer(numY.intValue());          break;
        case LONG:   valResult = new Long(numY.longValue());            break;
        case FLOAT:  valResult = new Float(numY.floatValue());          break;
        case DOUBLE: valResult = new Double(numY.doubleValue());        break;
        default: throw new Error();
        }
        result = rawResult.annotate().constant(valResult);
      } else {
        result = rawResult;
      }
    } else if (!JavaEntities.isPrimitiveT(rawX) && !JavaEntities.isPrimitiveT(rawY)) {
      if (JavaEntities.isNullT(rawX)) {
        result = BigInteger.ZERO == valCond ? typY : rawY;
      } else if (JavaEntities.isNullT(rawY)) {
        result = BigInteger.ONE == valCond ? typY : rawY;
      } else {
        final Type convX = JavaTypeConverter.convertAssigning(_table, classpath(), rawY, rawX);
        final Type convY = JavaTypeConverter.convertAssigning(_table, classpath(), rawX, rawY);
        if (!assrt(n, null != convX || null != convY, "mismatched types"))
          return setType(n, ErrorT.TYPE);
        result = null != convX ? convX : convY;
      }
    } else {
      throw new Error();
    }
    return setType(n, result);
  }

  /**
   * Visit a ConditionalStatement = Expression Statement [Statement]
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5991">&sect;14.9</a>).
   */
  public final void visitConditionalStatement(final GNode n) {
    final Type condition = dispatchRValue(n.getGeneric(0));
    if (!JavaEntities.resolveToRawRValue(condition).isBoolean())
      _runtime.error("condition must be boolean", n.getGeneric(0));
    dispatch(n.getNode(1));
    dispatch(n.getNode(2));
  }

  public final void visitConstructorDeclaration(final GNode n) {
    assert false : "must run JavaAstSimplifier first";
  }

  /**
   * Visit a ContinueStatement = [Identifier] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6122">&sect;14.15</a>).
   */
  public final void visitContinueStatement(final GNode n) {
    if (null == n.get(0)) {
      assrt(n, _context._loop, "continue cannot be used outside of a loop");
    } else {
      final String simpleName = n.getString(0);
      final String symbol = SymbolTable.toLabelName(simpleName);
      final LabelT label = (LabelT) _table.current().lookup(symbol);
      if (null == label)
        _runtime.error("the label " + simpleName + " is missing", n);
      else
        assrt(n, label.hasAttribute(Constants.ATT_LOOP), "%s is not a loop label", label.getName());
    }
  }

  /**
   * Visit Declarator = Identifier [Dimensions] [VariableInitializer].
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5920">&sect;14.4</a>).
   * Note: used by FieldDeclaration and ForInit,
   * who are responsible for calling the ExternalAnalyzer first, so
   * that the TYPE attribute is already set.
   * Note: VariableInitializer &gt; ArrayInitializer, * Expression.
   */
  public final Type visitDeclarator(final GNode n) {
    final JavaContext savedContext = _context.save();
    final Type result = resolveIfAlias((Type) n.getProperty(Constants.TYPE), n);
    _context._static = hasModifier(result, "static");
    {
      final Type wrappedRValue = JavaEntities.dereference(result);
      final Type rValue = JavaEntities.isConstantT(wrappedRValue) ? ((AnnotatedT)wrappedRValue).getType() : wrappedRValue;
      if (rValue.isAlias()) {
        final AliasT alias = (AliasT)rValue;
        if (null == alias.getType()) {
          _runtime.error("unknown type " + alias.getName(), n);
          alias.setType(JavaEntities.tObject(_table));
          return result;
        }
      }
    }
    final String id = n.getString(0);
    assrtLegalIdentifier(n, id);
    if (JavaEntities.isParameterT(result)) {
      _runtime.error("duplicate parameter declaration " + id, n);
    } else {
      assert JavaEntities.isFieldT(result) || JavaEntities.isLocalT(result);
      if (JavaEntities.isScopeLocal(_table.current().getQualifiedName()))
        if (!SymbolTable.isInNameSpace(_table.current().getName(), "method")) {
          final Type shadowed = (Type) _table.current().getParent().lookup(id);
          assrt(n, null == shadowed || !JavaEntities.isParameterT(shadowed), "duplicate variable declaration " + id);
        }
    }
    if (null != n.get(2)) {
      _context._initializing = getRValue(result, n);
      final Type src = dispatchRValue((GNode) n.getNode(2));
      if (!src.isError()) {
        assert JavaEntities.isGeneralRValueT(src);
        assrt(n, JavaTypeConverter.isAssignable(_table, classpath(), _context._initializing, src), "initializer type mismatch");
        if (src.hasConstant() && !JavaEntities.isNullT(src) && hasModifier(result, "final")) {
          final WrappedT t = JavaEntities.resolveToRawLValue(result);
          t.setType(src);
        }
      }
    }
    if (_context._static && JavaEntities.isFieldT(result))
      if (JavaEntities.isTypeInner(JavaEntities.currentType(_table)))
        assrt(n, hasModifier(result, "final"), "static variables of inner classes must be compile-time constants");
    _context.restore(savedContext);
    return result;
  }

  /**
   * Visit Declarators = Declarator+
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5920">&sect;14.4</a>).
   * Note: used by FieldDeclaration and ForInit,
   * who are responsible for calling the ExternalAnalyzer first, so
   * that the TYPE attribute is already set.
   */
  public final List<Type> visitDeclarators(final GNode n) {
    final List<Type> result = new ArrayList<Type>();
    for (final Object nDecl : n)
      result.add((Type) dispatch((GNode)nDecl));
    return result;
  }

  /**
   * Visit a DefaultClause = DeclarationOrStatement* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#35518">&sect;14.10</a>).
   */
  public final void visitDefaultClause(final GNode n) {
    for (int i = 0; i < n.size(); i++)
      dispatch(n.getGeneric(i));
  }

  /**
   * Visit a DoWhileStatement = Statement Expression (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6045">&sect;14.12</a>).
   */
  public final void visitDoWhileStatement(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._loop = true;
    dispatch(n.getNode(0));
    final Type condition = dispatchRValue(n.getGeneric(1));
    if (!JavaEntities.resolveToRawRValue(condition).isBoolean())
      _runtime.error("condition must be boolean", n.getGeneric(0));
    _context.restore(savedContext);
  }

  /**
   * Visit a EmptyDeclaration = (no children) (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5970">&sect;14.6</a>).
   */
  public final void visitEmptyDeclaration(final GNode n) { 
    assert 0 == n.size();
  }

  /**
   * Visit a EmptyStatement = (no children) (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5970">&sect;14.6</a>).
   */
  public final void visitEmptyStatement(final GNode n) {
    assert 0 == n.size();
  }

  /**
   * Visit a EqualityExpression = Expression ("==" / "!=") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5192">&sect;15.21</a>).
   */
  public final Type visitEqualityExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final String o = n.getString(1);
    final Type result;
    Type tBool = JavaEntities.nameToBaseType("boolean");
    final boolean xIsBool = JavaTypeConverter.isIdentical(x, tBool), yIsBool = JavaTypeConverter.isIdentical(y, tBool);
    assert "==".equals(o) || "!=".equals(o);
    final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
    final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
    if (null == promX || null == promY) {
      if (xIsBool) {
        if (yIsBool) {
          if (x.hasConstant() && y.hasConstant()) {
            final boolean valX = x.getConstant().isTrue();
            final boolean valY = y.getConstant().isTrue();
            if ("==".equals(o))
              result = tBool.annotate().constant(valX == valY);
            else
              result = tBool.annotate().constant(valX != valY);
          } else {
            result = tBool;
          }
        } else {
          _runtime.error("boolean expected", n.getNode(n.size() - 1));
          result = tBool;
        }
      } else {
        if (JavaEntities.isNullT(x) || JavaEntities.isNullT(y)) {
          assrt(n, (JavaEntities.isReferenceT(x) || JavaEntities.isNullT(x)) && 
              (JavaEntities.isReferenceT(y) || JavaEntities.isNullT(y)), "incompatible types");
          result = tBool;
        } else if (isStringConstant(x) && isStringConstant(y)) {
          final String sx = (String) x.getConstant().getValue(), sy = (String) y.getConstant().getValue();
          result = tBool.annotate().constant("==".equals(o) ? sx.equals(sy) : !sx.equals(sy));
        } else {
          final boolean yx = JavaTypeConverter.isCastable(_table, classpath(), y, x);
          final boolean xy = JavaTypeConverter.isCastable(_table, classpath(), x, y);
          assrt(n, yx || xy, "incompatible types");
          result = tBool;
        }
      }
    } else if (!promX.hasConstant() || !promY.hasConstant()) {
      result = tBool;
    } else {
      final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
      final Number valNumX = (Number) promX.getConstant().getValue();
      final Number valNumY = (Number) promY.getConstant().getValue();
      switch (typNum.getKind()) {
      case INT: {
        final int valX = valNumX.intValue(), valY = valNumY.intValue();
        if ("==".equals(o))
          result = tBool.annotate().constant(valX == valY);
        else
          result = tBool.annotate().constant(valX != valY);
        break;
      }
      case LONG: {
        final long valX = valNumX.longValue(), valY = valNumY.longValue();
        if ("==".equals(o))
          result = tBool.annotate().constant(valX == valY);
        else
          result = tBool.annotate().constant(valX != valY);
        break;
      }
      case FLOAT: {
        final float valX = valNumX.floatValue(), valY = valNumY.floatValue();
        if ("==".equals(o))
          result = tBool.annotate().constant(valX == valY);
        else
          result = tBool.annotate().constant(valX != valY);
        break;
      }
      case DOUBLE: {
        final double valX = valNumX.doubleValue(), valY = valNumY.doubleValue();
        if ("==".equals(o))
          result = tBool.annotate().constant(valX == valY);
        else
          result = tBool.annotate().constant(valX != valY);
        break;
      }
      default:
        throw new Error();
      }
    }
    return setType(n, result);
  }
  
  /**
   * Visit a Expression = Expression ("=" / "+=" / "-=" / "*=" / "/=" / "&amp;=" / "|=" / "^=" / "%=" / "&lt;&lt;=" / "&gt;&gt;=" / "&gt;&gt;&gt;=") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5281">&sect;15.26</a>).
   */
  public final Type visitExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final String o = n.getString(1);
    assert "=".equals(o) || "+=".equals(o) || "-=".equals(o)
          || "*=".equals(o) || "/=".equals(o) || "%=".equals(o) || "&=".equals(o)
          || "|=".equals(o) || "^=".equals(o) || "<<=".equals(o)
          || ">>=".equals(o) || ">>>=".equals(o);
    if (!JavaEntities.isGeneralLValueT(xLvalue)) {
      _runtime.error("left operand of assignment not l-value", n);
    } else if (hasModifier(xLvalue, "final")) {
      _runtime.error("left operand of assignment is final", n);
      // TD 30 (15.26) should allow assignments to "blank final" variables, but that
      // would require flow-sensitive analysis, which is quite complicated
      // for final parameters, assignment should definitely be forbidden
    } else if ("=".equals(o)) {
      // gosling_et_al_2000 15.26.1 Simple Assignment Operator =
      assrt(n.getGeneric(2), JavaTypeConverter.isAssignable(_table, classpath(), x, y), "illegal assignment");
    } else {
      // gosling_et_al_2000 15.26.2 Compound Assignment Operators
      final char op = o.charAt(0);
      final boolean string;
      if ('+' == op) {
        final Type tString = JavaEntities.tString(_table);
        string = JavaTypeConverter.isIdentical(x, tString);
      } else {
        string = false;
      }
      if (!string) {
        final Type rawX = JavaEntities.resolveToRawRValue(x);
        final Type rawY = JavaEntities.resolveToRawRValue(y);
        switch (op) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
          assrt(n, rawX.isNumber() && rawY.isNumber(), "illegal assignment");
          break;
        case '&':
        case '|':
        case '^':
          assrt(n, rawX.isBoolean() && rawY.isBoolean()
              || rawX.isInteger() && rawY.isInteger(), "illegal assignment");
          break;
        case '<':
        case '>':
          assrt(n, rawX.isInteger() && rawY.isInteger(), "illegal assignment");
          break;
        default:
          assert false;
        }
      }
    }
    return setType(n, x);
  }

  /**
   * Visit an ExpressionList = Expression* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#24588">&sect;14.13</a>).
   */
  public final List<Type> visitExpressionList(final GNode n) {
    final List<Type> result = new ArrayList<Type>();
    for (int i = 0; i < n.size(); i++)
      result.add(dispatchRValue(n.getGeneric(i)));
    return result;
  }

  /**
   * Visit an ExpressionStatement = Expression (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5984">&sect;14.8</a>).
   */
  public final void visitExpressionStatement(final GNode n) {
    dispatch(n.getNode(0));
  }

  /**
   * Visit a FieldDeclaration = Modifiers Type Declarators (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#40898">&sect;8.3</a>).
   */
  public final List<Type> visitFieldDeclaration(final GNode n) {
    //TD 42 don't treat static initializer like local variable
//    if (JavaEntities.isScopeLocal(_table.current().getQualifiedName()))
    if (null == n.getGeneric(2).getGeneric(0).getProperty(Constants.TYPE))
      _externalAnalyzer.dispatch(n);
    return JavaEntities.typeList((List)dispatch(n.getNode(2)));
  }

  /**
   * Visit a FloatingPointLiteral (gosling_et_al <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#230798">&sect;3.10.2</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitFloatingPointLiteral(final GNode n) {
    final String s = n.getString(0);
    final boolean isFloat = 'f' == Character.toLowerCase(s.charAt(s.length() - 1));
    final Number value = isFloat ? (Number)new Float(s) : new Double(s);
    if (!assrt(n, isFloat ? !((Float)value).isInfinite() : !((Double)value).isInfinite(), "literal out of range")
        || !assrt(n, (0.0 == value.doubleValue()) == JavaEntities.zeroLiteral(s), "literal out of range"))
      return setType(n, ErrorT.TYPE);
    final Type type = JavaEntities.nameToBaseType(isFloat ? "float" : "double");
    return setType(n, type.annotate().constant(value));
  }

  /**
   * Visit a FormalParameter = [Modifier] Type null Identifier [Dimensions] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#38698">&sect;8.4.1</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#29488">8.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#79311">&sect;14.19</a>).
   */
  public final Type visitFormalParameter(final GNode n) {
    final boolean isInCatch = SymbolTable.isInNameSpace(_table.current().getName(), "catchClause");
    final String id = n.getString(3);
    final Type result;
    final Type t = (Type) _table.lookup(id);
    if (isInCatch) {
      assrt(n, null == t, "duplicate parameter " + id);
      result = null == t ? (Type) _externalAnalyzer.visitFormalParameter(n) : t;
    } else {
      result = t;
    }
    resolveIfAlias(JavaEntities.dereference(result), n.getNode(1));
    return setType(n, result);
  }

  /** Visit FormalParameters = FormalParameter* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#38698">&sect;8.4.1</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#29488">8.8.1</a>. */
  public final List<Type> visitFormalParameters(final GNode n) {
    final List<Type> result = new ArrayList<Type>(n.size());
    for (int i = 0; i < n.size(); i++)
      result.add((Type)dispatch(n.getNode(i)));
    return result;
  }

  /**
   * Visit a ForStatement = ForControl Statement
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#24588">&sect;14.13</a>).
   * Note that ForControl &gt; BasicForControl.
   */
  public final void visitForStatement(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._loop = true;
    _context._hasScope = false;
    _table.enter(_table.freshName("forStatement"));
    _table.mark(n);
    dispatch(n.getGeneric(0));
    dispatch(n.getGeneric(1));
    _table.exit();
    _context.restore(savedContext);
  }

  /**
   * Visit a ImportDeclaration = QualifiedIdentifier ["*"] (gosling_et_al_2000
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/packages.doc.html#70209">&sect;7.5</a>).
   */
  public final void visitImportDeclaration(final GNode n) {
    _externalAnalyzer.visitImportDeclaration(n);
  }

  /**
   * Visit an InstanceOfExpression = Expression Type (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#40641">&sect;15.20</a>).
   */
  public final Type visitInstanceOfExpression(final GNode n) {
    final GNode nExpression = n.getGeneric(0);
    final Type tExpression = dispatchRValue(nExpression);
    if (!tExpression.isError()) {
      if (JavaEntities.isReferenceT(tExpression) || JavaEntities.isNullT(tExpression)) {
        final GNode nType = n.getGeneric(1);
        final Type tType = (Type) dispatch(nType);
        if (!tType.isError()) {
          if (JavaEntities.isReferenceT(tType))
            assrt(n, JavaTypeConverter.isCastable(_table, classpath(), tType, tExpression), "not castable");
          else
            _runtime.error("reference type expected", nType);
        }
      } else {
        _runtime.error("reference type expected", nExpression);
      }
    }
    return setType(n, JavaEntities.nameToBaseType("boolean"));
  }

  /**
   * Visit an IntegerLiteral (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#48282">&sect;3.10.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitIntegerLiteral(final GNode n) {
    final String s = n.getString(0);
    final int len = s.length(), radix, digitsStart;
    final boolean isNeg = '-' == s.charAt(0);
    final boolean isLong = 'L' == Character.toUpperCase(s.charAt(len - 1));
    final int digitsEnd = isLong ? len - 1 : len;
    if (s.startsWith("0x") || s.startsWith("0X")) {
      radix = 16;
      digitsStart = isNeg ? 3 : 2;
    } else if (1 < digitsEnd && '0' == s.charAt(0)) {
      radix = 8;
      digitsStart = isNeg ? 2 : 1;
    } else {
      radix = 10;
      digitsStart = isNeg ? 1 : 0;
    }
    final String digits = s.substring(digitsStart, digitsEnd);
    BigInteger bigInt = new BigInteger(digits, radix);
    assert bigInt.compareTo(BigInteger.ZERO) >= 0;
    final BigInteger halfLong = new BigInteger("8000000000000000", 16);
    final BigInteger halfInt = new BigInteger("80000000", 16);
    final BigInteger fullLong = halfLong.add(halfLong), fullInt = halfInt.add(halfInt);
    final BigInteger max;
    if (10 == radix)
      if (isLong)
        max = isNeg ? halfLong : halfLong.subtract(BigInteger.ONE);
      else
        max = isNeg ? halfInt : halfInt.subtract(BigInteger.ONE);
    else
      max = (isLong ? fullLong : fullInt).subtract(BigInteger.ONE);
    if (!assrt(n, bigInt.compareTo(max) <= 0, "literal out of range"))
      return setType(n, ErrorT.TYPE);
    if (10 != radix && isLong && bigInt.compareTo(halfLong) >= 0)
      bigInt = bigInt.subtract(fullLong);
    if (10 != radix && !isLong && bigInt.compareTo(halfInt) >= 0)
      bigInt = bigInt.subtract(fullInt);
    if (isNeg)
      bigInt = BigInteger.ZERO.subtract(bigInt);
    final Type type = JavaEntities.nameToBaseType(isLong ? "long" : "int");
    final Number value = isLong ? (Number)new Long(bigInt.longValue()) : new Integer(bigInt.intValue());
    if (!assrt(n, bigInt.equals(BigInteger.valueOf(value.longValue())), "literal out of range"))
      return setType(n, ErrorT.TYPE);
    return setType(n, type.annotate().constant(value));
  }

  /**
   * Visit a InterfaceDeclaration = Modifiers Identifier null [Extension] ClassBody
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#35470">&sect;9.1</a>).
   */
  public final void visitInterfaceDeclaration(final GNode n) {
    if (JavaEntities.isScopeLocal(_table.current().getQualifiedName())) {
      _runtime.error("interface cannot be local", n);
      return;
    }
    final JavaContext savedContext = _context.save();
    _context._handledExceptions = new ArrayList<Type>();
    _context._hasScope = true;
    _context._switch = false;
    _context._loop = false;
    final String simpleName = n.getString(1);
    assrtLegalIdentifier(n, simpleName);
    InterfaceT base = (InterfaceT) _table.current().lookupLocally(SymbolTable.toTagName(simpleName));
    if (null == base)
      base = _externalAnalyzer.visitInterfaceDeclaration(n);
    final Set<String> seenInterfaces = new HashSet<String>();
    for (int i=0; i<base.getInterfaces().size(); i++) {
      // gosling_et_al_2000 9.1.2
      final Type t = resolveIfAlias(base.getInterfaces().get(i), n.getGeneric(3).getNode(i));
      if (!t.isError() && assrt(n.getGeneric(3), t.isInterface(), "interface expected")) {
        final String qname = t.toInterface().getQName();
        assrt(n.getGeneric(3), !seenInterfaces.contains(qname), "duplicate superinterfaces");
        seenInterfaces.add(qname);
        assrt(n.getGeneric(3), JavaEntities.isAccessible(_table, classpath(), t), "superinterface not accessible");
      }
    }
    assrt(n, !JavaEntities.hasCircularDependency(_table, classpath(), base), "circular class");
    _table.enter(simpleName);
    _table.mark(n.getNode(4));
    dispatch(n.getNode(4));
    _table.exit();
    _context.restore(savedContext);
  }

  /**
   * Visit a LabeledStatement = Identifier Statement (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#78993">&sect;14.7</a>).
   */
  public final void visitLabeledStatement(final GNode n) {
    _table.enter(_table.freshName("labeledStatement"));
    _table.mark(n);
    final String simpleName = n.getString(0);
    final String symbol = SymbolTable.toLabelName(simpleName);
    final SymbolTable.Scope scope = _table.current();
    SymbolTable.Scope s = scope;
    while (true) {
      final String q = s.getQualifiedName();
      if (JavaEntities.isScopeTopLevel(q) || JavaEntities.isScopeForMember(q))
        break;
      assrt(n, null == s.lookupLocally(symbol), "duplicate label " + simpleName);
      s = s.getParent();
    }
    final LabelT label = new LabelT(simpleName);
    scope.define(symbol, label);
    final String kind = n.getNode(1).getName();
    if ("ForStatement".equals(kind) || "WhileStatement".equals(kind) || "DoWhileStatement".equals(kind))
      label.addAttribute(Constants.ATT_LOOP);
    dispatch(n.getNode(1));
    _table.exit();
  }

  /**
   * Visit a LogicalAndExpression = Expression Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5228">&sect;15.22</a>, 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitLogicalAndExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(1));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final Type result;
    final Type tBool = JavaEntities.nameToBaseType("boolean");
    final boolean xIsBool = JavaTypeConverter.isIdentical(x, tBool), yIsBool = JavaTypeConverter.isIdentical(y, tBool);
    assrt(n.getGeneric(0), xIsBool, "operand must be boolean");
    assrt(n.getGeneric(1), yIsBool, "operand must be boolean");
    if (xIsBool && x.hasConstant() && yIsBool && y.hasConstant())
      result = tBool.annotate().constant(x.getConstant().isTrue() && y.getConstant().isTrue());
    else
      result = tBool;
    return setType(n, result);
  }

  /**
   * Visit a LogicalNegationExpression = Expression
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#4990">&sect;15.15</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitLogicalNegationExpression(final GNode n) {
    final Type type = (Type) dispatch(n.getGeneric(0));
    if (type.isError())
      return setType(n, type);
    final Type tBool = JavaEntities.nameToBaseType("boolean");
    if (!assrt(n, JavaTypeConverter.isIdentical(getRValue(type, n), tBool), "operand must be boolean"))
      return setType(n, ErrorT.TYPE);
    if (type.hasConstant())
      return setType(n, tBool.annotate().constant(!type.getConstant().isTrue()));
    return setType(n, type);
  }

  /**
   * Visit a LogicalOrExpression = Expression Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5228">&sect;15.22</a>, 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitLogicalOrExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(1));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final Type result;
    final Type tBool = JavaEntities.nameToBaseType("boolean");
    final boolean xIsBool = JavaTypeConverter.isIdentical(x, tBool), yIsBool = JavaTypeConverter.isIdentical(y, tBool);
    assrt(n.getGeneric(0), xIsBool, "operand must be boolean");
    assrt(n.getGeneric(1), yIsBool, "operand must be boolean");
    if (xIsBool && x.hasConstant() && yIsBool && y.hasConstant())
      result = tBool.annotate().constant(x.getConstant().isTrue() || y.getConstant().isTrue());
    else
      result = tBool;
    return setType(n, result);
  }

  /**
   * Visit a MethodDeclaration = Modifiers null Type Identifier FormalParameters [Dimensions]
   * [ThrowsClause] [Block] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#40420">&sect;8.4</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#41652">8.8</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#78651">9.4</a>).
   */
  public Type visitMethodDeclaration(final GNode n) {
    assrtLegalIdentifier(n, n.getString(3));
    _table.enter(JavaEntities.methodSymbolFromAst(n));
    _table.mark(n);
    final JavaContext savedContext = _context.save();
    _context._hasScope = false;
    final MethodT result = JavaEntities.currentMethod(_table);
    _context._static = hasModifier(result, "static");
    resolveIfAlias(result.getResult(), n.getNode(2));
    _context._handledExceptions = null == n.get(6) ? new ArrayList<Type>() : result.getExceptions();
    assrtLegalHandledExceptions(n.getGeneric(6));
    assrtLegalMethodBody(n, result);
    assrtLegalMethod(n, result);
    dispatch(n.getNode(4));
    dispatch(n.getNode(7));
    _context.restore(savedContext);
    _table.exit();
    return setType(n, result);
  }

  /** Visit a Modifiers = Modifier* (gosling_et_al_2000 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#21613">&sect;8.1.1</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#78091">&sect;8.3.1</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#78188">&sect;8.4.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#247581">&sect;8.5.1</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#42018">&sect;8.8.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#235947">&sect;9.1.1</a>). */
  public final List<Attribute> visitModifiers(final GNode n) {
    return _externalAnalyzer.visitModifiers(n);
  }

  /**
   * Visit a MultiplicativeExpression = Expression ("*" / "/" / "%") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#239829">&sect;15.17</a>).
   */
  public final Type visitMultiplicativeExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final String o = n.getString(1);
    assert "*".equals(o) || "/".equals(o) || "%".equals(o);
    final Type result;
    final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
    final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
    if (null == promX || null == promY) {
      _runtime.error("numeric operands expected", n);
      result = JavaEntities.nameToBaseType("double");
    } else if (!promX.hasConstant() || !promY.hasConstant()) {
      result = JavaEntities.resolveToRawRValue(promX);
    } else {
      final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
      final Number valNumX = (Number) promX.getConstant().getValue();
      final Number valNumY = (Number) promY.getConstant().getValue();
      switch (typNum.getKind()) {
      case INT: {
        final int valX = valNumX.intValue(), valY = valNumY.intValue();
        if ("*".equals(o))
          result = typNum.annotate().constant(new Integer(valX * valY));
        else if (0 == valY)
          result = typNum;
        else if ("/".equals(o))
          result = typNum.annotate().constant(new Integer(valX / valY));
        else
          result = typNum.annotate().constant(new Integer(valX % valY));
        break;
      }
      case LONG: {
        final long valX = valNumX.longValue(), valY = valNumY.longValue();
        if ("*".equals(o))
          result = typNum.annotate().constant(new Long(valX * valY));
        else if (0 == valY)
          result = typNum;
        else if ("/".equals(o))
          result = typNum.annotate().constant(new Long(valX / valY));
        else
          result = typNum.annotate().constant(new Long(valX % valY));
        break;
      }
      case FLOAT: {
        final float valX = valNumX.floatValue(), valY = valNumY.floatValue();
        if ("*".equals(o))
          result = typNum.annotate().constant(new Float(valX * valY));
        else if ("/".equals(o))
          result = typNum.annotate().constant(new Float(valX / valY));
        else
          result = typNum.annotate().constant(new Float(valX % valY));
        break;
      }
      case DOUBLE: {
        final double valX = valNumX.doubleValue(), valY = valNumY
        .doubleValue();
        if ("*".equals(o))
          result = typNum.annotate().constant(new Double(valX * valY));
        else if ("/".equals(o))
          result = typNum.annotate().constant(new Double(valX / valY));
        else
          result = typNum.annotate().constant(new Double(valX % valY));
        break;
      }
      default:
        throw new Error();
      }
    }
    return setType(n, result);
  }  
  
  /** Visit a NewArrayExpression = TypeName ConcreteDimensions [Dimensions] null / TypeName null [Dimensions] ArrayInitializer.
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#46168">&sect;15.10</a>). */
  public final Type visitNewArrayExpression(final GNode n) {
    final Type component = processTypeName(n.getGeneric(0));
    if (component.isError())
      return setType(n, ErrorT.TYPE);
    dispatch(n.getNode(1));
    final int abstractDim = JavaExternalAnalyzer.countDimensions(n.getGeneric(2));
    final int dim = abstractDim + (null == n.get(1) ? 0 : n.getGeneric(1).size());
    final Type result = JavaEntities.typeWithDimensions(component, dim);
    if (null != n.get(3)) {
      final JavaContext savedContext = _context.save();
      _context._initializing = getRValue(result, n.getGeneric(0));
      final Type src = dispatchRValue(n.getGeneric(3));
      if (!result.isError() && !src.isError())
        assrt(n, JavaTypeConverter.isAssignable(_table, classpath(), _context._initializing, src), "initializer type mismatch");
      _context.restore(savedContext);      
    }
    return setType(n, result);
  }
  
  /**
   * Visit a NewClassExpression = [Expression] Type TypeName Arguments [ClassBody]
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#41147">&sect;15.9</a>).
   */
  public final Type visitNewClassExpression(final GNode n) {
    assrt(n, null == n.get(4), "anonymous classes not yet implemented");
    dispatch(n.getNode(0));
    final Type result = processTypeName(n.getGeneric(2));
    if (result.isError()
        || !assrt(n.getGeneric(2), result.isClass(), "can only instantiate class types")
        || !assrt(n.getGeneric(2), !hasModifier(result, "abstract"), "cannot instantiate abstract type"))
      return setType(n, ErrorT.TYPE);
    final List<Type> actuals = JavaEntities.typeList((List)dispatch(n.getNode(3)));
    final Type constructor = JavaEntities.typeDotMethod(
        _table, classpath(), result, false, JavaEntities.typeToSimpleName(result), actuals);
    if (null == constructor) {
      _runtime.error("could not find constructor", n);
      setType(n.getGeneric(3), ErrorT.TYPE);
    } else {
      setType(n.getGeneric(3), constructor);
    }
    return setType(n, result);
  }

  /**
   * Visit a NullLiteral (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#230717">&sect;3.10.7</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>).
   */
  public final Type visitNullLiteral(final GNode n) {
    return setType(n, JavaEntities.nameToBaseType("null"));
  }

  /**
   * Visit a PackageDeclaration = QualifiedIdentifier (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/packages.doc.html#26619">&sect;7.4</a>).
   */
  public final void visitPackageDeclaration(final GNode n) {
    _externalAnalyzer.visitPackageDeclaration(n);
  }

  /**
   * Visit a PostfixExpression = Expression ("++" / "--")
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#36254">&sect;15.14</a>).
   */
  public final Type visitPostfixExpression(final GNode n) {
    final Type lValue = (Type) dispatch(n.getGeneric(0));
    if (lValue.isError())
      return setType(n, ErrorT.TYPE);
    if (!assrt(n, JavaEntities.isGeneralLValueT(lValue), "operand of %s must be variable", n.getString(1)))
      return setType(n, lValue);
    assrt(n, !hasModifier(lValue, "final"), "operand of %s must not be final", n.getString(1));
    final Type result = JavaEntities.dereference(lValue);
    final Type raw = JavaEntities.resolveToRawRValue(result);
    assrt(n, raw.isNumber(), "operand of %s must be number", n.getString(1));
    return setType(n, result);
  }

  /**
   * Visit a PrimaryIdentifier = Identifier (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/names.doc.html#106941">&sect;6.5</a>).
   */
  public Type visitPrimaryIdentifier(final GNode n) {
    // TD 02 (6.5.2, 15.11.1) PrimaryIdentifier = Identifier
    final String id = n.getString(0);
    final Type t = JavaEntities.simpleNameToPackageOrTypeOrExpression(
        _table, classpath(), _table.current().getQualifiedName(), id);
    assert t.isPackage() || JavaEntities.isWrappedClassT(t) || JavaEntities.isWrappedInterfaceT(t) ||
        JavaEntities.isLocalT(t) || JavaEntities.isFieldT(t) || JavaEntities.isParameterT(t);
    if (JavaEntities.isFieldT(t))
      assrt(n, hasModifier(t, "static") || !_context._static, "static use of instance field");
    final Type result = JavaEntities.notAValueIfClassOrInterface(t);
    return setType(n, result);
  }
  
  /**
   * Visit a PrimitiveType = ("byte" / "short" / "char" / "int" / "long" / "float" / "double" / "boolean")
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/typesValues.doc.html#85587">&sect;4.2</a>).
   */
  public final Type visitPrimitiveType(final GNode n) {
    return JavaEntities.nameToBaseType(n.getString(0));
  }

  /**
   * Visit a QualifiedIdentifier = Identifier+ (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/names.doc.html#106941">&sect;6.5</a>).
   */
  public final String visitQualifiedIdentifier(final GNode n) {
    return _externalAnalyzer.visitQualifiedIdentifier(n);
  }

  /**
   * Visit a RelationalExpression = Expression ("&lt;" / "&gt;" / "&lt;=" / "&gt;=") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#40641">&sect;15.20</a>).
   */
  public final Type visitRelationalExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final String o = n.getString(1);
    final Type result;
    Type tBool = JavaEntities.nameToBaseType("boolean");
    assert "<".equals(o) || ">".equals(o) || "<=".equals(o) || ">=".equals(o);
    final Type promX = JavaTypeConverter.promoteBinaryNumeric(y, x);
    final Type promY = JavaTypeConverter.promoteBinaryNumeric(x, y);
    if (null == promX || null == promY) {
      _runtime.error("numeric operands expected", n);
      result = tBool;
    } else if (!promX.hasConstant() || !promY.hasConstant()) {
      result = tBool;
    } else {
      final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promX);
      final Number valNumX = (Number) promX.getConstant().getValue();
      final Number valNumY = (Number) promY.getConstant().getValue();
      switch (typNum.getKind()) {
      case INT: {
        final int valX = valNumX.intValue(), valY = valNumY.intValue();
        if ("<".equals(o))
          result = tBool.annotate().constant(valX < valY);
        else if ("<=".equals(o))
          result = tBool.annotate().constant(valX <= valY);
        else if (">".equals(o))
          result = tBool.annotate().constant(valX > valY);
        else
          result = tBool.annotate().constant(valX >= valY);
        break;
      }
      case LONG: {
        final long valX = valNumX.longValue(), valY = valNumY.longValue();
        if ("<".equals(o))
          result = tBool.annotate().constant(valX < valY);
        else if ("<=".equals(o))
          result = tBool.annotate().constant(valX <= valY);
        else if (">".equals(o))
          result = tBool.annotate().constant(valX > valY);
        else
          result = tBool.annotate().constant(valX >= valY);
        break;
      }
      case FLOAT: {
        final float valX = valNumX.floatValue(), valY = valNumY.floatValue();
        if ("<".equals(o))
          result = tBool.annotate().constant(valX < valY);
        else if ("<=".equals(o))
          result = tBool.annotate().constant(valX <= valY);
        else if (">".equals(o))
          result = tBool.annotate().constant(valX > valY);
        else
          result = tBool.annotate().constant(valX >= valY);
        break;
      }
      case DOUBLE: {
        final double valX = valNumX.doubleValue(), valY = valNumY
        .doubleValue();
        if ("<".equals(o))
          result = tBool.annotate().constant(valX < valY);
        else if ("<=".equals(o))
          result = tBool.annotate().constant(valX <= valY);
        else if (">".equals(o))
          result = tBool.annotate().constant(valX > valY);
        else
          result = tBool.annotate().constant(valX >= valY);
        break;
      }
      default:
        throw new Error();
      }
    }
    return setType(n, result);
  }

  /**
   * Visit a ReturnStatement = [Expression] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6767">&sect;14.16</a>).
   */
  public void visitReturnStatement(final GNode n) {
    final MethodT method = JavaEntities.currentMethod(_table);
    if (null == method) {
      _runtime.error("return statement outside method", n);
      return;
    }
    final Type t1 = null == n.get(0) ? VoidT.TYPE : dispatchRValue(n.getGeneric(0));
    final Type result = method.getResult();
    if (t1.isError() || result.isError())
      return;
    if (result.isVoid()) {
      assrt(n, t1.isVoid(), "'return' with a value, in method returning void");
    } else {
      if (t1.isVoid())
        _runtime.error("'return' with no value, in method returning non-void", n);
      else
        assrt(n, JavaTypeConverter.isAssignable(_table, classpath(), result, t1), "return type mismatch");
    }
  }

  /**
   * Visit a SelectionExpression = Expression Identifier (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#37055">&sect;15.11.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitSelectionExpression(final GNode n) {
    //TD 19 (15.11.1, 15.28) SelectionExpression = Expression Identifier
    final Type basePackageOrTypeOrField = (Type) dispatch(n.getGeneric(0));
    final Type baseExpressionType = getRValueNoError(basePackageOrTypeOrField);
    final String selector = n.getString(1);
    final Type t;
    if (null != baseExpressionType) {
      t = JavaEntities.typeDotTypeOrField(_table, classpath(), baseExpressionType, true, selector);
    } else if (basePackageOrTypeOrField.isPackage()) {
      t = JavaEntities.packageDotPackageOrType(_table, classpath(), (PackageT) basePackageOrTypeOrField, selector);
    } else if (JavaEntities.isNotAValueT(basePackageOrTypeOrField)) {
      final Type baseType = JavaEntities.resolveToValue(basePackageOrTypeOrField.toAnnotated());
      t = JavaEntities.typeDotTypeOrField(_table, classpath(), baseType, true, selector);
      if (!assrt(n, null != t, "unknown or ambiguous type or field %s", selector)
          || !assrt(n, null == t || JavaEntities.hasModifier(t, "static"), "static access to non-static field"))
        return setType(n, ErrorT.TYPE);
    } else if (JavaEntities.isWrappedClassT(basePackageOrTypeOrField) || JavaEntities.isWrappedInterfaceT(basePackageOrTypeOrField)) {
      t = JavaEntities.typeDotTypeOrField(_table, classpath(), basePackageOrTypeOrField, true, selector);
    } else {
      throw new Error(basePackageOrTypeOrField.getClass().getName());
    }
    if (null == t)
      return setType(n, ErrorT.TYPE);
    final Type result = JavaEntities.notAValueIfClassOrInterface(t);
    return setType(n, result);
  }

  /**
   * Visit a ShiftExpression = Expression ("&lt;&lt;" / "&gt;&gt;" / "&gt;&gt;&gt;") Expression
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5121">&sect;15.19</a>).
   */
  public final Type visitShiftExpression(final GNode n) {
    final Type xLvalue = (Type) dispatch(n.getGeneric(0));
    final Type x = getRValue(xLvalue, n.getGeneric(0));
    final Type y = dispatchRValue(n.getGeneric(2));
    if (x.isError() || y.isError())
      return setType(n, ErrorT.TYPE);
    final String o = n.getString(1);
    final Type result;
    assert "<<".equals(o) || ">>".equals(o) || ">>>".equals(o);
    final Type promX = JavaTypeConverter.promoteUnaryNumeric(x);
    final Type promY = JavaTypeConverter.promoteUnaryNumeric(y);
    if (null == promX) {
      _runtime.error("integral operand expected", n.getNode(0));
      result = JavaEntities.nameToBaseType("long");
    } else if (null == promY) {
      _runtime.error("integral operand expected", n.getNode(2));
      result = promX;
    } else {
      final NumberT typNumX = (NumberT) JavaEntities.resolveToRawRValue(promX);
      final NumberT typNumY = (NumberT) JavaEntities.resolveToRawRValue(promY);
      if (!typNumX.isInteger()) {
        _runtime.error("integral operand expected", n.getNode(0));
        result = JavaEntities.nameToBaseType("int");
      } else if (!typNumY.isInteger()) {
        _runtime.error("integral operand expected", n.getNode(2));
        result = promX;
      } else if (!promX.hasConstant() || !promY.hasConstant()) {
        result = promX;
      } else {
        final Number valNumX = (Number) promX.getConstant().getValue();
        final Number valNumY = (Number) promY.getConstant().getValue();
        final long valY = valNumY.longValue();
        switch (typNumX.getKind()) {
        case INT: {
          final int valX = valNumX.intValue();
          if ("<<".equals(o))
            result = typNumX.annotate().constant(new Integer(valX << valY));
          else if (">>".equals(o))
            result = typNumX.annotate().constant(new Integer(valX >> valY));
          else
            result = typNumX.annotate().constant(new Integer(valX >>> valY));
          break;
        }
        case LONG: {
          final long valX = valNumX.longValue();
          if ("<<".equals(o))
            result = typNumX.annotate().constant(new Long(valX << valY));
          else if (">>".equals(o))
            result = typNumX.annotate().constant(new Long(valX >> valY));
          else
            result = typNumX.annotate().constant(new Long(valX >>> valY));
          break;
        }
        default:
          throw new Error();
        }
      }
    }
    return setType(n, result);
  }

  /** Visit a StringLiteral (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/lexical.doc.html#101083">&sect;3.10.5</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#224125">&sect;15.8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>). */
  public final Type visitStringLiteral(final GNode n) {
    final Type tString = JavaEntities.tString(_table);
    final String s = n.getString(0);
    final StringBuffer result = new StringBuffer();
    final int len = s.length() - 1;
    int i = 1;
    try {
      while (i < len) {
        final char c = s.charAt(i);
        if (c == '\\') {
          result.append(escapeSequenceChar(s, i));
          i = escapeSequenceEnd(s, i);
        } else {
          if (!assrt(n, '\r' != c && '\n' != c, "string must not contain line terminator"))
            return setType(n, ErrorT.TYPE);
          result.append(c);
          i++;
        }
      }
    } catch (final IllegalArgumentException e) {
      _runtime.error("illegal escape sequence", n);
      return setType(n, ErrorT.TYPE);
    }
    return setType(n, tString.annotate().constant(result.toString()));
  }

  /**
   * Visit a SubscriptExpression = Expression Expression (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#239587">&sect;15.13</a>).
   */
  public final Type visitSubscriptExpression(final GNode n) {
    final Type arrayT = dispatchRValue(n.getGeneric(0));
    if (!assrt(n, arrayT.isArray(), "array reference expression expected"))
      return setType(n, ErrorT.TYPE);
    final Type indexT = dispatchRValue(n.getGeneric(1));
    assrt(n, JavaEntities.isInt(indexT), "integer expression expected");
    final AnnotatedT result = (AnnotatedT) ((ArrayT) arrayT).getType();
    resolveIfAlias(JavaEntities.dereference(result));
    return setType(n, result);
  }

  /**
   * Visit a SuperExpression = [Type] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#20860">&sect;15.11.2</a>).
   */
  public final Type visitSuperExpression(final GNode n) {
    // TD 20 (15.11.2) SuperExpression = [Type]
    assrt(n, !_context._static, "static use of super");
    final Type subType = JavaEntities.currentType(_table);
    final ClassT rawSubType = (ClassT)JavaEntities.resolveToRawClassOrInterfaceT(subType);
    final Type result = JavaEntities.resolveIfAlias(_table, classpath(),
        JavaEntities.typeToScopeName(subType), rawSubType.getParent());
    return setType(n, result);
  }

  /**
   * Visit a SwitchStatement = Expression SwitchClause* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#35518">&sect;14.10</a>).
   */
  public final void visitSwitchStatement(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._switch = true;
    final Type expression = (Type) dispatch(n.getGeneric(0));
    final Type eRaw;
    {
      final Type r = JavaEntities.isGeneralLValueT(expression) ? JavaEntities
          .dereference(expression) : expression;
      eRaw = JavaEntities.resolveToRawRValue(r);
    }
    assrt(n.getGeneric(0), JavaEntities.nameToBaseType("char") == eRaw
        || JavaEntities.nameToBaseType("byte") == eRaw
        || JavaEntities.nameToBaseType("short") == eRaw
        || JavaEntities.nameToBaseType("int") == eRaw,
        "switch expression must be char, byte, short, or int");
    boolean sawDefault = false;
    final Set<Integer> seenValues = new HashSet<Integer>();
    for (int iClause = 1; iClause < n.size(); iClause++) {
      final GNode clauseNode = n.getGeneric(iClause);
      if (clauseNode.hasName("DefaultClause")) {
        dispatch(clauseNode);
        if (sawDefault)
          _runtime.error("duplicate default clause", clauseNode);
        sawDefault = true;
      } else {
        //final Type clauseType = dispatchRValue(clauseNode);
        final Type clauseTypeL = (Type)dispatch(clauseNode);
        final Type clauseType = getRValue(clauseTypeL, clauseNode);
        if (JavaTypeConverter.isAssignable(_table, classpath(), eRaw, clauseType)) {
          if (null == clauseType)
            throw new Error();
          if (JavaEntities.isConstantT(clauseType)) {
            final Object clauseValue = clauseType.getConstant().getValue();
            if (null == clauseValue)
              throw new Error();
            final int i = clauseValue instanceof Character ? ((Character) clauseValue).charValue() : ((Number) clauseValue).intValue();
            if (seenValues.contains(new Integer(i)))
              _runtime.error("duplicate case clause", clauseNode);
            else
              seenValues.add(new Integer(i));
            assrt(clauseNode, isAssignable(i, eRaw), "invalid case clause");
          } else {
            assrt(n, JavaEntities.isGeneralLValueT(clauseTypeL) && hasModifier(clauseTypeL, "final"), "case expression must be constant");
          }
        } else {
          _runtime.error("invalid case clause", clauseNode);
        }
      }
    }
    _context.restore(savedContext);
  }

  /**
   * Visit a SynchronizedStatement = Expression Block (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#255769">&sect;14.18</a>).
   */
  public final void visitSynchronizedStatement(final GNode n) {
    final GNode nMonitor = n.getGeneric(0);
    final Type tMonitor = dispatchRValue(nMonitor);
    assrt(nMonitor, !JavaEntities.isNullT(tMonitor) && JavaEntities.isReferenceT(tMonitor), "invalid type for synchronized statement");
    dispatch(n.getNode(1));
  }

  /** 
   * Visit a ThisExpression = [Expression] (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#251519">&sect;15.8.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#251603">&sect;15.8.4</a>).
   */
  public final Type visitThisExpression(final GNode n) {
    // TD 25 (15.8.3, 15.8.4) ThisExpression = [Expression]
    assrt(n, !_context._static, "static use of this");
    return setType(n, JavaEntities.currentType(_table));
  }

  /**
   * Visit a ThrowStatement = Expression (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#237350">&sect;14.17</a>).
   */
  public final void visitThrowStatement(final GNode n) {
    final Type tThrown = dispatchRValue(n.getGeneric(0));
    final Type tThrowable = JavaEntities.tThrowable(_table);
    if (!JavaTypeConverter.isAssignable(_table, classpath(), tThrowable, tThrown))
      _runtime.error("exception must be throwable", n.getNode(0));
    else if (JavaEntities.isCheckedException(_table, classpath(), tThrown))
      assrt(n, isHandled(tThrown), "uncaught exception");
  }

  /**
   * Visit a TryCatchFinallyStatement = null Block CatchClause* [Block]
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#79311">&sect;14.19</a>).
   */
  public final List<Type> visitTryCatchFinallyStatement(final GNode n) {
    final List<Type> result = new ArrayList<Type>();
    for (int i = 2; i < n.size() - 1; i++)
      result.add((Type)dispatch(n.getNode(i)));
    final JavaContext savedContext = _context.save();
    _context._handledExceptions = new ArrayList<Type>();
    _context._handledExceptions.addAll(savedContext._handledExceptions);
    _context._handledExceptions.addAll(result);    
    dispatch(n.getNode(1));
    _context.restore(savedContext);
    dispatch(n.getNode(n.size() - 1));
    return result;
  }

  /**
   * Visit a Type = TypeName Dimensions
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/typesValues.doc.html#48440">&sect;4</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/arrays.doc.html#25518">&sect;10.1</a>).
   * Note that TypeName is either PrimitiveType or ClassType, i.e., QualifiedIdentifier.
   */
  public final Type visitType(final GNode n) {
    //TD 01 (4, 10.1) Type = TypeName Dimensions
    final Type t = _externalAnalyzer.visitType(n);
    final Type result = resolveIfAlias(t, n);
    return setType(n, result);
  }

  /**
   * Visit a UnaryExpression = ("+" / "-" / "++" / "--") Expression
   * (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#4990">&sect;15.15</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#5313">&sect;15.28</a>).
   */
  public final Type visitUnaryExpression(final GNode n) {
    final Type type = (Type) dispatch(n.getGeneric(1));
    if (type.isError())
      return setType(n, type);
    String operator = n.getString(0);
    if ("++".equals(operator) || "--".equals(operator)) {
      if (JavaEntities.isGeneralLValueT(type)) {
        assrt(n, !hasModifier(type, "final"), "operand of %s must not be final", operator);
        final Type rValue = JavaEntities.dereference(type);
        final Type raw = JavaEntities.resolveToRawRValue(rValue);
        if (!assrt(n, raw.isNumber(), "operand of %s must be number", operator))
          return setType(n, ErrorT.TYPE);
        return setType(n, rValue);
      }
      _runtime.error("operand of " + operator + " must be variable", n);
      return setType(n, type);
    } else {
      assert "+".equals(operator) || "-".equals(operator);
      final Type promoted = JavaTypeConverter.promoteUnaryNumeric(getRValue(type, n.getGeneric(1)));
      if (!assrt(n, null != promoted, "operand must be numeric"))
        return setType(n, ErrorT.TYPE);
      if (promoted.hasConstant()) {
        if ("+".equals(operator))
          return setType(n, promoted);
        final NumberT typNum = (NumberT) JavaEntities.resolveToRawRValue(promoted);
        final Number valNum = (Number) promoted.getConstant().getValue();
        switch (typNum.getKind()) {
        case INT: {
          final int valInt = valNum.intValue();
          return typNum.annotate().constant(new Integer("-".equals(operator) ? -valInt : ~valInt));
        }
        case LONG: {
          final long valLong = valNum.longValue();
          return typNum.annotate().constant(new Long("-".equals(operator) ? -valLong : ~valLong));
        }
        case FLOAT: {
          if (!assrt(n, "-".equals(operator), "operand must be an integral type"))
            return setType(n, ErrorT.TYPE);
          return typNum.annotate().constant(new Float(-valNum.floatValue()));
        }
        case DOUBLE: {
          if (!assrt(n, "-".equals(operator), "operand must be an integral type"))
            return setType(n, ErrorT.TYPE);
          return typNum.annotate().constant(new Double(-valNum.doubleValue()));
        }
        default:
          throw new Error();
        }
      } else {
        return setType(n, promoted);
      }
    }
  }

  /**
   * Visit a WhileStatement = Expression Statement (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#237277">&sect;14.11</a>).
   */
  public final void visitWhileStatement(final GNode n) {
    final JavaContext savedContext = _context.save();
    _context._loop = true;
    final Type condition = dispatchRValue(n.getGeneric(0));
    if (!JavaEntities.resolveToRawRValue(condition).isBoolean())
      _runtime.error("condition must be boolean", n.getGeneric(0));
    dispatch(n.getNode(1));
    _context.restore(savedContext);
  }
}
