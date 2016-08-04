/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 IBM Corp.
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
package xtc.lang.jeannie;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

import xtc.Constants;
import xtc.Limits;
import xtc.lang.CAnalyzer;
import xtc.lang.JavaAnalyzer;
import xtc.lang.JavaEntities;
import xtc.lang.JavaTypeConverter;
import xtc.tree.GNode;
import xtc.tree.LineMarker;
import xtc.tree.Locatable;
import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.type.ClassOrInterfaceT;
import xtc.type.ClassT;
import xtc.type.FunctionT;
import xtc.type.MethodT;
import xtc.type.PointerT;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.VoidT;
import xtc.type.Type.Tag;
import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.SymbolTable.Scope;

/**
 * A visitor that constructs separate C and Java ASTs from a JNI AST. Assumes
 * that the input AST has been simplified with jeannie.AstSimplifier, and its types
 * have been analyzed with jeannie.Analyzer.
 * 
 * @author Martin Hirzel
 */
public class CodeGenerator extends Visitor {
  public static final class Context {
    final String _activeLanguage;
    final String _cEnvStructName;
    final boolean _cHasEnv;
    final String _javaEnvClassName;
    final String _javaEnvPackageName;
    final boolean _javaIsStatic;
    final String _openArray;
    final Type _snippetType;

    public Context(final Context other, final String activeLanguage) {
      this(activeLanguage, other._cEnvStructName, other._cHasEnv,
          other._javaEnvClassName, other._javaEnvPackageName,
          other._javaIsStatic, other._openArray, other._snippetType);
    }

    public Context(final String activeLanguage, final String cEnvStructName,
        final boolean cHasEnv, final String javaEnvClassName,
        final String javaEnvPackageName, final boolean javaIsStatic,
        final String openArray, final Type snippetType) {
      _activeLanguage = activeLanguage;
      _cEnvStructName = cEnvStructName;
      _cHasEnv = cHasEnv;
      _javaEnvClassName = javaEnvClassName;
      _javaEnvPackageName = javaEnvPackageName;
      _javaIsStatic = javaIsStatic;
      _openArray = openArray;
      _snippetType = snippetType;
    }
  }
  public static final class Out {
    public final List<Node> _cExternalDeclarations;
    public final List<Node> _cMembers;
    public final Node _cNode;
    public final List<Node> _javaMembers;
    public final Node _javaNode;

    public Out(final List<Node> cExternalDeclarations,
        final List<Node> cMembers, final Node cNode,
        final List<Node> javaMembers, final Node javaNode) {
      _cExternalDeclarations = cExternalDeclarations;
      _cMembers = cMembers;
      _cNode = cNode;
      _javaMembers = javaMembers;
      _javaNode = javaNode;
    }

    public final Out addAll(final Out other) {
      if (null != other) {
        _cExternalDeclarations.addAll(other._cExternalDeclarations);
        _cMembers.addAll(other._cMembers);
        _javaMembers.addAll(other._javaMembers);
      }
      return this;
    }
  }
  
  static final class StringString {
    final String _s1;
    final String _s2;
    StringString(final String s1, final String s2) {
      _s1 = s1;
      _s2 = s2;
    }
  }  
  
  static final class Substitutions implements Iterable<StringString>{
    private final Map<String, Map<String, String>> _map = new HashMap<String, Map<String, String>>();
    final String get(final SymbolTable.Scope scope, final String srcId) {
      final Map<String, String> m = _map.get(scope.getQualifiedName());
      return null == m ? null : m.get(srcId);
    }
    public Iterator<StringString> iterator() {
      final List<StringString> l = new ArrayList<StringString>();
      for (final String scopeName : _map.keySet())
        for (final String srcId : _map.get(scopeName).keySet())
          l.add(new StringString(scopeName, srcId));
      return l.iterator();
    }
    final Substitutions put(final SymbolTable.Scope scope, final String srcId, final String tgtId) {
      final String scopeName = scope.getQualifiedName();
      if (!_map.containsKey(scopeName))
        _map.put(scopeName, new HashMap<String, String>());
      _map.get(scopeName).put(srcId, tgtId);
      return this;
    }
  }
  
  private static String getFileStem(final GNode n) {
    final String fileName = n.getLocation().file;
    final int lastSlash = Math.max(fileName.lastIndexOf('/'), fileName.lastIndexOf('\\'));
    final int firstDot = fileName.indexOf('.', lastSlash);
    final int end = -1 == firstDot ? fileName.length() : firstDot;
    return fileName.substring(1 + lastSlash, end);
  }

  private static Type getType(final GNode n) {
    return (Type) n.getProperty(Constants.TYPE);
  }

  private static GNode idNode(final Locatable loc, final String id) {
    return setLoc(loc, GNode.create("PrimaryIdentifier", id));
  }

  /** Set location from loc to n, return n. */
  public static GNode setLoc(final Locatable loc, final GNode n) {
    n.setLocation(loc);
    return n;
  }

  final Substitutions _cSubstitutions;
  final Substitutions _javaSubstitutions;
  final Map<String, String> _methodSubstitutions;
  final JeannieJavaFactory _astFactoryJava;
  final JeannieCFactory _astFactoryC;
  final Stack<Context> _contexts;
  final Map<String, Integer> _freshIdCount;
  final Runtime _runtime;
  final SymbolTable _table;

  Set<String> _usedIdentifiers;

  public CodeGenerator(final Runtime runtime, final SymbolTable table) {
    _astFactoryC = new JeannieCFactory();
    _astFactoryJava = new JeannieJavaFactory();
    _contexts = new Stack<Context>();
    _cSubstitutions = new Substitutions();
    _freshIdCount = new HashMap<String, Integer>();
    _javaSubstitutions = new Substitutions();
    _methodSubstitutions = new HashMap<String, String>();
    _runtime = runtime;
    _table = table;
  }

  private GNode abruptFlowCheck(final Locatable loc, final List<Node> cMembers, final List<Node> javaMembers) {
    final GNode fieldName = cStringNode(liftIdJava(currentMethodScope(), loc, "returnAbrupt", JavaEntities.nameToBaseType("boolean"), javaMembers));
    final GNode jump = abruptFlowJump(loc, cMembers);
    final GNode result;
    if (existsOpenArrayInSameSnippet()) {
      final String arr = context()._openArray;
      final String releaseAbrupt = liftIdC(declaringScope(arr), arr + "ReleaseAbrupt", typedefType("jint"), cMembers);
      result = (GNode) _astFactoryC.abruptFlowCheckOpenArray(releaseAbrupt, fieldName, jump);
    } else {
      result = (GNode) _astFactoryC.abruptFlowCheck(fieldName, jump);
    }
    return setLoc(loc, result);
  }
  
  private GNode abruptFlowJump(final Locatable loc, final List<Node> cMembers) {
    final GNode jumpStatement;
    if (existsOpenArrayInSameSnippet()) {
      final String arr = context()._openArray;
      final String label = liftIdCLabel(declaringScope(arr), "release_" + arr);
      jumpStatement = (GNode) _astFactoryC.abruptFlowJumpOpenArray(label);
    } else {
      final Type returnType = context()._snippetType;
      final GNode value = returnType.hasTag(Tag.VOID)
        ? null
        : GNode.create("CastExpression", Utilities.cTypeToAst(returnType, null, "TypeName"), GNode.create("IntegerConstant", "0"));
      jumpStatement = GNode.create("ReturnStatement", value);
    }
    return setLoc(loc, jumpStatement);
  }
  
  private GNode cEnvJavaTypeAst() {
    final String name;
    switch (Limits.POINTER_SIZE) {
      case 4: name = "int"; break;
      case 8: name = "long"; break;
      default: throw new Error();
    }
    return JavaEntities.javaTypeToAst(_table, JavaEntities.nameToBaseType(name));
  }

  private Out cInJavaCode(final GNode n, final boolean isExpression) {
    assert "Java".equals(context()._activeLanguage);
    final GNode childNode = n.getGeneric(0);
    final Type childType = isExpression ? getType(childNode) : VoidT.TYPE;
    _contexts.push(new Context("C", context()._cEnvStructName, true, context()._javaEnvClassName,
        context()._javaEnvPackageName, context()._javaIsStatic, context()._openArray, childType));
    final Out childOut = (Out) dispatch(childNode);
    _contexts.pop();
    final Type ownType = isExpression ? getType(n) : JavaEntities.nameToBaseType("void");
    final String methodName = freshIdentifier("j2c");
    final List<Node> javaMembers = cInJavaCode_javaMembers(methodName, ownType, childOut);
    final Out ownOut = new Out(
        cInJavaCode_cExternalDeclarations(methodName, childType, childOut),
        childOut._cMembers, null,
        javaMembers,
        cInJavaCode_javaNode(n, methodName, javaMembers, isExpression));
    return ownOut;
  }
  
  private List<Node> cInJavaCode_cExternalDeclarations(
      final String methodName, final Type childType, final Out childOut) {
    final String functionName = mangledFunctionName(methodName);
    _methodSubstitutions.put(functionName, Utilities.currentFunctionOrMethodName(_table));
    final GNode function;
    { //parse prototype with empty body first
      final String jniCall = _runtime.getString("jniCall"); 
      // on cygwin: "__attribute__((__stdcall__))"
      final String core = null == jniCall ? functionName : jniCall + " " + functionName;
      final Type pure = Utilities.pureCType(_table, _runtime, childType);
      String code = Utilities.cTypeToString(pure, core) + "(";
      code = Utilities.copyDropAuto(code);
      code += "  JNIEnv *env, jobject jEnv";
      // represent C pointer as Java long, i.e., using 64 bits
      if (context()._cHasEnv)
        switch (Limits.POINTER_SIZE) {
          case 4: code += ", const jint cEnv"; break;
          case 8: code += ", const jlong cEnv"; break;
          default: throw new Error();
        }
      code += ") { }";
      final Set<String> typedefs = Utilities.typedefs(childType);
      typedefs.addAll(Utilities.standardJniTypeDefs());
      function = Utilities.cStringToAst("FunctionDefinition", code, typedefs);
    }
    { //then plug in real body
      final String tag = context()._cEnvStructName;
      final Node action = childOut._cNode;
      final Node body;
      if (context()._cHasEnv)
        body = childType.isVoid()
          ? _astFactoryC.cInJavaStatementWithCEnv(tag, action)
          : _astFactoryC.cInJavaExpressionWithCEnv(tag, action);
      else
        body = childType.isVoid()
          ? _astFactoryC.cInJavaStatementWithoutCEnv(tag, action)
          : _astFactoryC.cInJavaExpressionWithoutCEnv(tag, action);
      function.set(function.size() - 1, setLoc(childOut._cNode, (GNode)body));        
    }
    final List<Node> result = childOut._cExternalDeclarations;
    result.add(function);
    return result;
  }
  
  private List<Node> cInJavaCode_javaMembers(
      final String methodName, final Type ownType, final Out childOut) {
    final GNode returnType = JavaEntities.javaTypeToAst(_table, ownType);
    final Node n = context()._cHasEnv
      ? _astFactoryJava.cInJavaCodeWithCEnv(returnType, methodName, cEnvJavaTypeAst())
      : _astFactoryJava.cInJavaCodeWithoutCEnv(returnType, methodName);
    //TD 41 throws clause on j2c native method
    final List<Node> result = childOut._javaMembers;
    result.add(setLoc(childOut._cNode, (GNode)n));
    return result;
  }

  private GNode cInJavaCode_javaNode(final Locatable loc, final String methodName, final List<Node> javaMembers, final boolean isExpression) {
    final Node result;
    if (isExpression) {
      result = context()._cHasEnv
        ? _astFactoryJava.cInJavaExpressionWithCEnv(methodName)
        : _astFactoryJava.cInJavaExpressionWithoutCEnv(methodName);
    } else {
      final String returnAbruptName = liftIdJava(currentMethodScope(), loc, "returnAbrupt", JavaEntities.nameToBaseType("boolean"), javaMembers);
      result = context()._cHasEnv
        ? _astFactoryJava.cInJavaStatementWithCEnv(methodName, returnAbruptName)
        : _astFactoryJava.cInJavaStatementWithoutCEnv(methodName, returnAbruptName);
    }
    return setLoc(loc, (GNode)result);
  }
  
  private final Context context() {
    return _contexts.peek();
  }

  private GNode cStringNode(final String string) {
    return GNode.create("StringConstant", "\"" + string + "\"");
  }

  private SymbolTable.Scope currentMethodScope() {
    for (SymbolTable.Scope s = _table.current(); !s.isRoot(); s = s.getParent()) {
      final String scopeName = s.getName();
      if (   SymbolTable.isInNameSpace(scopeName, "method")
          || SymbolTable.isFunctionScopeName(scopeName)
          || SymbolTable.isMacroScopeName(scopeName))
        return s;
    }
    return null;
  }

  private SymbolTable.Scope declaringScope(final String id) {
    return _table.lookupScope(id);
  }

  private boolean existsOpenArrayInSameSnippet() {
    final String o = context()._openArray;
    if (null == o)
      return false;
    final String a = context()._activeLanguage;
    for (int i=_contexts.size() - 2; i >= 0; i--) {
      final Context c = _contexts.get(i);
      if (!a.equals(c._activeLanguage))
        return false;
      if (!o.equals(c._openArray))
        return true;
    }
    return true;
  }

  /**
   * Returns a new globally unique identifier that starts with the base name.
   * Takes care to avoid shadowing other identifiers that the program already
   * uses, including free identifiers that are bound in imports or superclasses,
   * and even "funny names" that programmers are unlikely to write but that may
   * arise in other automatically generated code.
   */
  private String freshIdentifier(final String base) {
    int i = _freshIdCount.containsKey(base) ? _freshIdCount.get(base)
        .intValue() : -1;
    String result;
    do {
      i++;
      result = (0 == i) ? base : base + i;
    } while (_usedIdentifiers.contains(result));
    _freshIdCount.put(base, new Integer(i));
    _usedIdentifiers.add(result);
    return result;
  }

  private boolean isUtf8(final Type cPtrType, final Type javaType) {
    if (JavaTypeConverter.isIdentical(javaType, JavaEntities.tString(_table))) {
      final Type cTgtType = ((PointerT)Utilities.c().pointerize(cPtrType)).getType();
      return Utilities.hasTypedefName(cTgtType, "jbyte");
    }
    return false;
  }

  private Out javaInCCode(final GNode n, final boolean isExpression) {
    assert "C".equals(context()._activeLanguage);
    _contexts.push(new Context(context(), "Java"));
    final Out javaOut = (Out) dispatch(n);
    _contexts.pop();
    final Type javaType = isExpression ? 
        JavaAnalyzer.getRValueNoError(getType(n)) : JavaEntities.nameToBaseType("void");
    final String methodName = freshIdentifier("c2j");
    recordMethodSubstitution(methodName);
    final List<Node> cMembers = javaOut._cMembers;
    final List<Node> javaMembers = javaOut._javaMembers;
    final boolean isNonVoidExpression = isExpression && !getType(n).isVoid();
    final Out ownOut = new Out(javaOut._cExternalDeclarations,
        cMembers, javaInCCode_cNode(methodName, javaType, isNonVoidExpression, n, cMembers, javaMembers),
        javaInCCode_javaMembers(methodName, javaType, isExpression, javaOut), null);
    return ownOut;
  }

  private GNode javaInCCode_cNode(
      final String methodName, final Type javaType, final boolean isExpression, final GNode n, final List<Node> cMembers, final List<Node> javaMembers) {
    final GNode name = cStringNode(methodName);
    final boolean is32bit = 4 == Limits.POINTER_SIZE;
    assert is32bit || 8 == Limits.POINTER_SIZE;
    final GNode signature = cStringNode((is32bit ? "(I)" : "(J)") + JavaEntities.typeToDescriptor(_table, javaType));
    final String apiFunction = "CallNonvirtual" + Utilities.javaTypeToApiType(javaType, true, false) + "Method";
    final GNode abruptFlowCheck = abruptFlowCheck(n, cMembers, javaMembers);
    final Node result;
    if (isExpression) {
      final Type cType = Utilities.javaTypeToCType(_table, _runtime, n, javaType, false);
      final GNode tmpDeclaration = Utilities.cTypeToAst(cType, "tmp", "Declaration");
      result = is32bit
        ? _astFactoryC.javaInCExpression32(name, signature, tmpDeclaration, apiFunction, abruptFlowCheck)
        : _astFactoryC.javaInCExpression64(name, signature, tmpDeclaration, apiFunction, abruptFlowCheck);
    } else {
      result = is32bit
        ? _astFactoryC.javaInCStatement32(name, signature, apiFunction, abruptFlowCheck)
        : _astFactoryC.javaInCStatement64(name, signature, apiFunction, abruptFlowCheck);
    }
    return setLoc(n, (GNode) result);
  }

  private List<Node> javaInCCode_javaMembers(
      final String methodName, final Type javaType, final boolean isExpression, final Out javaOut) {
    final GNode typeAst = JavaEntities.javaTypeToAst(_table, javaType);
    final Node n = isExpression ? javaType.isVoid()
      ? _astFactoryJava.javaInCExpressionVoid(methodName, cEnvJavaTypeAst(), javaOut._javaNode)
      : _astFactoryJava.javaInCExpression(typeAst, methodName, cEnvJavaTypeAst(), javaOut._javaNode)
      : _astFactoryJava.javaInCStatement(methodName, cEnvJavaTypeAst(), javaOut._javaNode);
    final List<Node> result = javaOut._javaMembers;
    result.add(setLoc(javaOut._javaNode, (GNode)n));
    return result;
  }

  private Out jeannieCancelOrCommit(final Locatable loc, final String arr, final boolean isCommit) {
    final List<Node> cMembers = new ArrayList<Node>();
    final GNode jump = abruptFlowJump(loc, cMembers);
    final String field = liftIdC(declaringScope(arr), arr + "ReleaseAbrupt", typedefType("jint"), cMembers);
    final Node n = isCommit ? _astFactoryC.commit(field, jump) : _astFactoryC.cancel(field, jump);
    setLoc(loc, (GNode) n);
    final Out ownOut = new Out(new ArrayList<Node>(0), cMembers, (GNode)n, new ArrayList<Node>(0), null);
    return ownOut;
  }

  private String jeannieCopyApiFunction(final Type javaType, final boolean isAcquire, final boolean isUtf8) {
    final StringBuffer result = new StringBuffer();
    result.append(isAcquire ? "Get" : "Set");
    if (JavaTypeConverter.isIdentical(javaType, JavaEntities.tString(_table)))
      result.append(isUtf8 ? "StringUTF" : "String");
    else
      result.append(Utilities.javaTypeToApiType(javaType, true, true));
    result.append("Region");
    return result.toString();
  }
  
  private String liftIdC(final SymbolTable.Scope scope, final String srcId, final Type type, final List<Node> cMembers) {
    if (null == _cSubstitutions.get(scope, srcId)) {
      final String tgtId = freshIdentifier("_" + srcId);
      final Type pureCType = Utilities.c().pointerize(Utilities.pureCType(_table, _runtime, type));
      final GNode fieldDecl = Utilities.cTypeToAst(pureCType, tgtId, "StructureDeclaration");
      cMembers.add(fieldDecl);
      _cSubstitutions.put(scope, srcId, tgtId);
    }
    return _cSubstitutions.get(scope, srcId);
  }

  private String liftIdCLabel(final SymbolTable.Scope scope, final String srcId) {
    //TD 41 avoid clashes with locals
    if (null == _cSubstitutions.get(scope, srcId)) {
      final String tgtId = freshIdentifier(srcId);
      _cSubstitutions.put(scope, srcId, tgtId);
    }
    return _cSubstitutions.get(scope, srcId);
  }
  
  private String liftIdJava(final SymbolTable.Scope scope, final Locatable loc, final String srcId, final Type type, final List<Node> javaMembers) {
    if (null == _javaSubstitutions.get(scope, srcId)) {
      final String tgtId = freshIdentifier("_" + srcId);
      final Type r = JavaEntities.isGeneralLValueT(type) ? JavaEntities.dereference(type) : type;
      final Node n = _astFactoryJava.declareField(JavaEntities.javaTypeToAst(_table, r), tgtId);
      javaMembers.add(setLoc(loc, (GNode)n));
      _javaSubstitutions.put(scope, srcId, tgtId);
    }
    return _javaSubstitutions.get(scope, srcId);
  }

  private String mangledFunctionName(final String methodName) {
    final String packageAndClass;
    if (null == context()._javaEnvPackageName) {
      final ClassT baseClass = JavaEntities.currentType(_table).toClass();
      final String baseName = JavaEntities.qNameWithDollars(_table, baseClass);
      packageAndClass = baseName + "$" + context()._javaEnvClassName;
    } else {
      final String slashes = context()._javaEnvPackageName + context()._javaEnvClassName;
      packageAndClass = slashes.replace('/', '.');
    }
    final String qualifiedName = packageAndClass + '.' + methodName;
    final String result = "Java_" + Utilities.jniMangledName(qualifiedName);
    return result;
  }

  private Out processBuiltin(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    final String name = n.getGeneric(0).getString(0);
    final Out argsOut = (Out) dispatch(n.getGeneric(1));
    assert null == argsOut._javaNode;
    if ("_copyFromJava".equals(name)) {
      final GNode cArray = argsOut._cNode.getGeneric(0);
      final GNode cArrayStart = argsOut._cNode.getGeneric(1);
      final GNode javaArray = argsOut._cNode.getGeneric(2);
      final GNode javaArrayStart = argsOut._cNode.getGeneric(3);
      final GNode length = argsOut._cNode.getGeneric(4);
      final GNode abruptFlowCheck = abruptFlowCheck(n, argsOut._cMembers, argsOut._javaMembers);
      final Type javaType = Utilities.cTypeToJavaType(_table, _runtime, n.getGeneric(1).getGeneric(2), getType(n.getGeneric(1).getGeneric(2)));
      final boolean primiv = JavaTypeConverter.isIdentical(javaType, JavaEntities.tString(_table)) || javaType.isArray() && JavaEntities.isPrimitiveT(JavaEntities.arrayElementType(javaType.toArray()));
      final Node ownNode;
      if (primiv) {
        final boolean utf8 = isUtf8(getType(n.getGeneric(1).getGeneric(0)), javaType);
        final String apiFunction = jeannieCopyApiFunction(javaType, true, utf8);
        ownNode = utf8
          ? _astFactoryC.copyBetweenJavaAndCUTF(javaArray, javaArrayStart, length, apiFunction, cArray, cArrayStart, abruptFlowCheck)
          : _astFactoryC.copyBetweenJavaAndC(apiFunction, javaArray, javaArrayStart, length, cArray, cArrayStart, abruptFlowCheck);
      } else {
        ownNode = _astFactoryC.copyFromJavaReference(javaArray, javaArrayStart, length, cArray, cArrayStart, abruptFlowCheck);
      }
      setLoc(n, (GNode)ownNode);
      final Out ownOut = new Out(argsOut._cExternalDeclarations, argsOut._cMembers, (GNode) ownNode, argsOut._javaMembers, null);
      return ownOut;
    } else if ("_copyToJava".equals(name)) {
      final GNode javaArray = argsOut._cNode.getGeneric(0);
      final GNode javaArrayStart = argsOut._cNode.getGeneric(1);
      final GNode cArray = argsOut._cNode.getGeneric(2);
      final GNode cArrayStart = argsOut._cNode.getGeneric(3);
      final GNode length = argsOut._cNode.getGeneric(4);
      final GNode abruptFlowCheck = abruptFlowCheck(n, argsOut._cMembers, argsOut._javaMembers);
      final Type javaType = Utilities.cTypeToJavaType(_table, _runtime, n.getGeneric(1).getGeneric(0), getType(n.getGeneric(1).getGeneric(0)));
      final boolean primiv = JavaTypeConverter.isIdentical(javaType, JavaEntities.tString(_table)) || javaType.isArray() && JavaEntities.isPrimitiveT(JavaEntities.arrayElementType(javaType.toArray()));
      final Node ownNode;
      if (primiv) {
        final boolean utf8 = isUtf8(getType(n.getGeneric(1).getGeneric(2)), javaType);
        final String apiFunction = jeannieCopyApiFunction(javaType, false, utf8);
        ownNode = utf8
          ? _astFactoryC.copyBetweenJavaAndCUTF(javaArray, javaArrayStart, length, apiFunction, cArray, cArrayStart, abruptFlowCheck)
          : _astFactoryC.copyBetweenJavaAndC(apiFunction, javaArray, javaArrayStart, length, cArray, cArrayStart, abruptFlowCheck);
      } else {
        ownNode = _astFactoryC.copyToJavaReference(javaArray, javaArrayStart, length, cArray, cArrayStart, abruptFlowCheck);
      }
      setLoc(n, (GNode)ownNode);
      final Out ownOut = new Out(argsOut._cExternalDeclarations, argsOut._cMembers, (GNode) ownNode, argsOut._javaMembers, null);
      return ownOut;
    } else if ("_newJavaString".equals(name)) {
      final Type t = getType(n.getGeneric(1).getGeneric(0));
      final String apiFunction = "NewString" + (Utilities.isPtrTypedef(t, "jchar") ? "" : "UTF");
      final GNode cString = argsOut._cNode.getGeneric(0);
      final GNode abruptFlowCheck = abruptFlowCheck(n, argsOut._cMembers, argsOut._javaMembers);
      final GNode cNode = (GNode) _astFactoryC.newJavaString(apiFunction, cString, abruptFlowCheck);
      setLoc(n, (GNode)cNode);
      final Out ownOut = new Out(argsOut._cExternalDeclarations, argsOut._cMembers,
          cNode, argsOut._javaMembers, null);
      return ownOut;
    } else if ("_stringUTFLength".equals(name)) {
      final Node ac = argsOut._cNode;
      final Node javaString = ac.getNode(0);
      final Node cNode;
      if (1 == n.getGeneric(1).size())
        cNode = _astFactoryC.stringUTFLength1(javaString);
      else
        cNode = _astFactoryC.stringUTFLength3(javaString, ac.getNode(1), ac.getNode(2));
      final Out ownOut = new Out(argsOut._cExternalDeclarations, argsOut._cMembers,
          setLoc(n, (GNode)cNode), argsOut._javaMembers, null);
      return ownOut;
    } else {
      throw new Error("builtin " + name + " not (yet) implemented");
    }
  }

  private List<Node> processDeclarators(final GNode declarators, final List<Node> cExternalDeclarations, final List<Node> cMembers, final List<Node> javaMembers) {
    assert "Java".equals(context()._activeLanguage) && declarators.hasName("Declarators");
    final List<Node> result = new ArrayList<Node>();
    for (final Object declObj : declarators) {
      final GNode declNode = (GNode) declObj;
      final GNode initNode = declNode.getGeneric(2);
      if (null == initNode)
        continue;
      final Out initOut = (Out) dispatch(initNode);
      assert null == initOut._cNode;
      cExternalDeclarations.addAll(initOut._cExternalDeclarations);
      cMembers.addAll(initOut._cMembers);
      javaMembers.addAll(initOut._javaMembers);
      final VariableT type = getType(declNode).toVariable();
      final String srcId = type.getName();
      final String subst = liftIdJava(declaringScope(srcId), declNode, srcId, type, javaMembers);
      final Node javaNode;
      if (initOut._javaNode.hasName("ArrayInitializer")) {
        final GNode typeAst = JavaEntities.javaTypeToAst(_table, type.getType());
        javaNode = setLoc(initOut._javaNode, GNode.create("NewArrayExpression", typeAst.getGeneric(0), null, typeAst.getGeneric(1), initOut._javaNode));
      } else {
        javaNode = initOut._javaNode;
      }
      result.add(setLoc(javaNode, (GNode) _astFactoryJava.setThisDotField(subst, javaNode)));
    }
    return result;
  }

  private void recordMethodSubstitution(final String methodName) {
    final String src = Utilities.currentFunctionOrMethodName(_table);
    final StringBuilder tgt = new StringBuilder();
    final ClassOrInterfaceT t = JavaEntities.currentType(_table);
    if (null == t) {
      final String p = context()._javaEnvPackageName;
      if (0 < p.length())
        tgt.append(p.substring(0, p.length() - 1).replace('/', '.') + '$');
    } else {
      tgt.append(JavaEntities.qNameWithDollars(_table, t)).append('$');
    }
    tgt.append(context()._javaEnvClassName).append('.').append(methodName);
    _methodSubstitutions.put(tgt.toString(), src);
  }

  private Type typedefType(final String symbol) {
    final Type result = (Type) _table.root().lookup(symbol);
    assert null != result;
    return result;
  }
  
  public final Out visit(final LineMarker m) {
    final boolean c = "C".equals(context()._activeLanguage);
    final Node n = m.getNode();
    if (null == n)
      return new Out(new ArrayList<Node>(0), new ArrayList<Node>(0), c ? m : null, new ArrayList<Node>(0), c ? null : m);
    final Out childOut = (Out) dispatch(n);
    if (c) {
      assert null != childOut._cNode && null == childOut._javaNode;
      m.setNode(childOut._cNode);
    } else {
      assert null == childOut._cNode && null != childOut._javaNode;
      m.setNode(childOut._javaNode);
    }
    final Out result = new Out(childOut._cExternalDeclarations, childOut._cMembers, c ? m : null, childOut._javaMembers, c ? null : m);
    return result;
  }

  /** Catch-all visit method. */
  public final Out visit(final Node n) {
    _table.enter(n);
    //TD 42 don't create a new node, just rewrite the old node's children
    final GNode ownNode = setLoc(n, GNode.create(n.getName(), n.size()));
    final boolean c = "C".equals(context()._activeLanguage);
    final Out ownOut = new Out(new ArrayList<Node>(), new ArrayList<Node>(),
        c ? ownNode : null, new ArrayList<Node>(), c ? null : ownNode);
    for (int i = 0; i < n.size(); i++)
      if (n.get(i) instanceof Node) {
        final Out childOut = (Out) dispatch(n.getNode(i));
        ownNode.add(i, c ? childOut._cNode : childOut._javaNode);
        ownOut.addAll(childOut);
        assert null == (c ? childOut._javaNode : childOut._cNode);
      } else {
        ownNode.add(i, n.get(i));
      }
    _table.exit(n);
    return ownOut;
  }
  
  /**
   * Visit a BasicForControl = Modifiers Type Declarators [Expression] [ExpressionList]
   *   / null null [ExpressionList] [Expression] [ExpressionList] (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#40898">&sect;8.3</a>).
   */
  public final Out visitBasicForControl(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    if (null == context()._javaEnvClassName || null == n.get(0))
      return visit(n);
    final List<Node> cExternalDeclarations = new ArrayList<Node>();
    final List<Node> cMembers = new ArrayList<Node>();
    final List<Node> javaMembers = new ArrayList<Node>();
    final List<Node> decls = processDeclarators(n.getGeneric(2), cExternalDeclarations, cMembers, javaMembers);
    final GNode initNode = 0 == decls.size() ? null : setLoc(n.getGeneric(2), (GNode)GNode.create("ExpressionList", decls.size()).addAll(decls));
    final Out testOut = (Out) dispatch(n.getGeneric(3));
    final Out incrOut = (Out) dispatch(n.getGeneric(4));
    final GNode javaNode = setLoc(n, GNode.create("BasicForControl", null, null, initNode, testOut._javaNode, incrOut._javaNode));
    final Out ownOut = new Out(cExternalDeclarations, cMembers, null, javaMembers, javaNode);
    ownOut.addAll(testOut).addAll(incrOut);
    return ownOut;
  }

  /** Visit a CancelStatement = JeannieC.PrimaryIdentifier. */
  public final Out visitCancelStatement(final GNode n) {
    return jeannieCancelOrCommit(n, n.getGeneric(0).getString(0), false);
  }

  /** Visit a CDeclarations = ExternalDeclaration* Annotations. */
  public final Out visitCDeclarations(final GNode n) {
    final Out ownOut = new Out(new ArrayList<Node>(), new ArrayList<Node>(),
        null, new ArrayList<Node>(), null);
    assert _table.current().isRoot();
    assert 1 == _contexts.size() && "C".equals(context()._activeLanguage);
    for (int i=0; i<n.size() - 1; i++) {
      final Out childOut = (Out) dispatch(n.getNode(i));
      assert null == childOut._javaNode;
      ownOut._javaMembers.addAll(childOut._javaMembers);
      ownOut._cExternalDeclarations.addAll(childOut._cExternalDeclarations);
      ownOut._cExternalDeclarations.add(childOut._cNode);
    }
    assert _table.current().isRoot();
    return ownOut;
  }

  /** Visit a CInCBlock = LocalLabelDeclaration* JeannieC.DeclarationOrStatement* Annotations. */
  public final Out visitCInCBlock(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    final Out genericOut = visit(n);
    assert genericOut._cNode.hasName("CInCBlock");
    final List<Node> cNodes = new ArrayList<Node>(n.size() - 1);
    for (int i=0; i<n.size() - 1; i++) {
      final GNode src = n.getGeneric(i), tgt = genericOut._cNode.getGeneric(i);
      if (src.hasName("Declaration")) {
        if (tgt.hasName("CompoundStatement")) //flatten, to expand scope of auxiliary declarations
          for (final Object t : tgt)
            cNodes.add((GNode) t);
        else if (!tgt.hasName("EmptyStatement")) //skip, to keep code more readable
          cNodes.add(tgt);
      } else {
        cNodes.add(tgt);
      }
    }
    final Out ownOut = new Out(genericOut._cExternalDeclarations,
        genericOut._cMembers, setLoc(n, GNode.create("CompoundStatement", cNodes.size() + 1)),
        genericOut._javaMembers, genericOut._javaNode);
    for (int i=0; i<cNodes.size(); i++)
      ownOut._cNode.add(i, cNodes.get(i));
    return ownOut;
  }

  /** Visit a CInJavaBlock = CInCBlock. */
  public final Out visitCInJavaBlock(final GNode n) {
    return cInJavaCode(n, false);
  }

  /** Visit a CInJavaExpression = JeannieC.UnaryExpression. */
  public final Out visitCInJavaExpression(final GNode n) {
    return cInJavaCode(n, true);
  }
  
  /**
   * Visit a ClassBody = Declaration* (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#18988">&sect;8.1.5</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#236431">&sect;9.1.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#41147">&sect;15.9</a>).
   */
  public final Out visitClassBody(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    _table.enter(n);
    final Out ownOut = new Out(new ArrayList<Node>(), new ArrayList<Node>(),
        null, new ArrayList<Node>(), setLoc(n, GNode.create("ClassBody")));
    if (Utilities.containsJavaToCTransition(n)) {
      if (JavaEntities.isTypeTopLevel(JavaEntities.currentType(_table))) {
        final GNode name = GNode.create("StringLiteral", "\"" + getFileStem(n) + "\"");
        final Node block = _astFactoryJava.loadLibrary(name);
        ownOut._javaNode.add(setLoc(n, GNode.create("BlockDeclaration", "static", block)));
      }
    }
    for (final Object child : n) {
      final Out childOut = (Out) dispatch((GNode) child);
      ownOut._cExternalDeclarations.addAll(childOut._cExternalDeclarations);
      assert childOut._cMembers.isEmpty() && null == childOut._cNode;
      ownOut._javaNode.add(childOut._javaNode);
      ownOut._javaNode.addAll(childOut._javaMembers);
    }
    _table.exit(n);
    return ownOut;
  }
  
  /** Visit a CommitStatement = JeannieC.PrimaryIdentifier. */
  public final Out visitCommitStatement(final GNode n) {
    return jeannieCancelOrCommit(n, n.getGeneric(0).getString(0), true);
  }
  
  /** Visit a CompilationUnit = [PackageDeclaration] JavaImports CDeclarations JeannieJava.Declaration*.
   * (gosling_et_al_2000 
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/packages.doc.html#40031">&sect;7.3</a>).
   */
  public final Out visitCompilationUnit(final GNode n) {
    assert _contexts.isEmpty();
    _usedIdentifiers = JavaEntities.allUsedIdentifiers(n);
    final GNode cNode = setLoc(n, GNode.create("TranslationUnit"));
    final Out cChildOut;
    {
      final StringBuffer packageName = new StringBuffer();
      if (null != n.get(0))
        for (final Object o : n.getNode(0).getNode(1))
          packageName.append(o).append('/');
      _contexts.push(new Context("C", null, false, null, packageName.toString(), true, null, null));
      cChildOut = (Out) dispatch(n.getGeneric(2));
      _contexts.pop();
    }
    assert cChildOut._cMembers.isEmpty() && null == cChildOut._cNode && null == cChildOut._javaNode;
    cNode.addAll(cChildOut._cExternalDeclarations);
    final GNode javaNode = setLoc(n, GNode.create("CompilationUnit"));
    javaNode.add(n.getGeneric(0));
    for (final Object o : n.getGeneric(1))
      javaNode.add(o);
    _contexts.push(new Context("Java", null, false, null, null, true, null, null));
    JavaEntities.enterScopeByQualifiedName(_table, (String) n.getProperty(Constants.SCOPE));
    for (int i = 3; i < n.size(); i++) {
      final Out javaChildOut = (Out) dispatch(n.getGeneric(i));
      cNode.addAll(javaChildOut._cExternalDeclarations);
      javaNode.add(javaChildOut._javaNode);
      assert javaChildOut._cMembers.isEmpty() && null == javaChildOut._cNode && javaChildOut._javaMembers.isEmpty();
    }
    javaNode.addAll(cChildOut._javaMembers);
    _contexts.pop();
    final Out ownOut = new Out(null, null, cNode, null, javaNode);
    return ownOut;
  }

  /** Visit a JeannieC.Declaration = ["__extension__"] DeclarationSpecifiers [InitializedDeclaratorList]. */
  public final Out visitDeclaration(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    if (null == context()._cEnvStructName || null == n.get(2))
      return visit(n);
    final List<Node> cExternalDeclarations = new ArrayList<Node>();
    final List<Node> cMembers = new ArrayList<Node>();
    final List<Node> javaMembers = new ArrayList<Node>();
    final List<Node> declResults = new ArrayList<Node>();
    for (final Object declObj : n.getGeneric(2)) {
      final GNode declNode = (GNode) declObj;
      final String srcId = Utilities.getSimpleDeclarator(declNode);
      final Type type = Utilities.pureCType(_table, _runtime, (Type) _table.lookup(srcId));
      final String tgtId = liftIdC(declaringScope(srcId), srcId, type, cMembers);
      if (declNode.getGeneric(1).hasName("ArrayDeclarator")) {
        final Out specsOut = (Out) dispatch(n.getGeneric(1));
        assert null == specsOut._javaNode;
        cExternalDeclarations.addAll(specsOut._cExternalDeclarations);
        cMembers.addAll(specsOut._cMembers);
        javaMembers.addAll(specsOut._javaMembers);
        final Out declOut = (Out) dispatch(declNode);
        assert null == declOut._javaNode;
        cExternalDeclarations.addAll(declOut._cExternalDeclarations);
        cMembers.addAll(declOut._cMembers);
        javaMembers.addAll(declOut._javaMembers);        
        final GNode declLocal = setLoc(declNode, GNode.create("Declaration", n.getString(0), specsOut._cNode, GNode.create("InitializedDeclaratorList", declOut._cNode)));
        declResults.add(declLocal);
        final GNode setField = (GNode) _astFactoryC.setPCEnvField(tgtId, GNode.create("PrimaryIdentifier", srcId));
        declResults.add(setLoc(declNode, setField));
      } else if (null != declNode.getGeneric(4)) {
        final Out initOut = (Out) dispatch(declNode.getGeneric(4));
        assert null == initOut._javaNode;
        cExternalDeclarations.addAll(initOut._cExternalDeclarations);
        cMembers.addAll(initOut._cMembers);
        javaMembers.addAll(initOut._javaMembers);
        final GNode typeAST = Utilities.cTypeToAst(type, null, "TypeName");
        final GNode cast = GNode.create("CastExpression", typeAST, initOut._cNode);
        declResults.add(setLoc(declNode, (GNode) _astFactoryC.setPCEnvField(tgtId, cast)));
      }
    }
    final Node cNode =
          (0 == declResults.size()) ? GNode.create("EmptyStatement")
        : (1 == declResults.size()) ? declResults.get(0)
        : /* else */                  _astFactoryC.block(declResults);
    final Out ownOut = new Out(cExternalDeclarations, cMembers, setLoc(n.getGeneric(2), (GNode)cNode), javaMembers, null);
    return ownOut;
  }

  /**
   * Visit a FieldDeclaration = Modifiers Type Declarators (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#40898">&sect;8.3</a>).
   */
  public final Out visitFieldDeclaration(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    if (null == context()._javaEnvClassName)
      return visit(n);
    final List<Node> cExternalDeclarations = new ArrayList<Node>();
    final List<Node> cMembers = new ArrayList<Node>();
    final List<Node> javaMembers = new ArrayList<Node>();
    final List<Node> decls = processDeclarators(n.getGeneric(2), cExternalDeclarations, cMembers, javaMembers);
    final GNode javaNode;
    if (0 == decls.size()) {
      javaNode = GNode.create("EmptyStatement");
    } else if (1 == decls.size()) {
      javaNode = GNode.create("ExpressionStatement", decls.get(0));
    } else {
      javaNode = GNode.create("Block", decls.size());
      for (final Node d : decls)
        javaNode.add(GNode.create("ExpressionStatement", d));
    }
    final Out ownOut = new Out(cExternalDeclarations, cMembers, null, javaMembers, setLoc(n.getGeneric(2), javaNode));
    return ownOut;
  }
  
  /**
   * Visit a ForStatement = (Declaration / [Expression]) [Expression] [Expression] Statement.
   */
  public final Out visitForStatement(final GNode n) {
    if ("Java".equals(context()._activeLanguage) || null == context()._cEnvStructName ||
        null == n.get(0) || !n.getGeneric(0).hasName("Declaration"))
      return visit(n);
    _table.enter(n);
    final Out initOut = (Out) dispatch(n.getGeneric(0));
    final Out testOut = (Out) dispatch(n.getGeneric(1));
    final Out incrOut = (Out) dispatch(n.getGeneric(2));
    final Out bodyOut = (Out) dispatch(n.getGeneric(3));
    final GNode loopNode = GNode.create("ForStatement", null, null == testOut ? null : testOut._cNode, null == incrOut ? null : incrOut._cNode, bodyOut._cNode);
    final GNode cNode = GNode.create("CompoundStatement", initOut._cNode, loopNode, null);
    final Out ownOut = new Out(new ArrayList<Node>(), new ArrayList<Node>(), setLoc(n, cNode), new ArrayList<Node>(), null);
    ownOut.addAll(initOut).addAll(testOut).addAll(incrOut).addAll(bodyOut);
    _table.exit(n);
    return ownOut;
  }

  /** Visit a FunctionCall = (PrimaryIdentifier / JeannieC.PostfixExpression) JeannieC.ExpressionList. */
  public final Out visitFunctionCall(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    if (null == context()._javaEnvClassName)
      return visit(n);
    if (n.getGeneric(0).hasName("PrimaryIdentifier") && Analyzer.BUILTINS.contains(n.getGeneric(0).getString(0)))
      return processBuiltin(n);
    final Out plainOut = visit(n);
    final Type cType = getType(n);
    final GNode cNode;
    final Node call = plainOut._cNode;
    final GNode abruptFlowCheck = abruptFlowCheck(n, plainOut._cMembers, plainOut._javaMembers);
    final Type cTypeMinusAnnotations = cType.isAnnotated() ? cType.toAnnotated().getType() : cType;
    if (cTypeMinusAnnotations.isVoid()) {
      cNode = (GNode) _astFactoryC.checkedFunctionCallVoid(call, abruptFlowCheck);
    } else {
      final GNode tmpDeclaration = Utilities.cTypeToAst(cType, "tmp", "Declaration");
      cNode = (GNode) _astFactoryC.checkedFunctionCallResult(tmpDeclaration, call, abruptFlowCheck);
    }
    setLoc(n, cNode);
    final Out ownOut = new Out(plainOut._cExternalDeclarations, plainOut._cMembers, cNode, plainOut._javaMembers, plainOut._javaNode);
    return ownOut;
  }

  /** Visit a FunctionDeclarator = (ParameterTypeList / IdentifierList) JavaThrows. */
  public final Out visitFunctionDeclarator(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    /* TD 41 jeannie.CodeGenerator.visitFunctionDeclarator: drop the throws clause */
    return visit(n);
  }
  
  /** Visit a FunctionDefinition = ["__extension__"] [DeclarationSpecifiers] Declarator 
   * [DeclarationList] CompoundStatement. */
  public final Out visitFunctionDefinition(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    if (!Utilities.containsCToJavaTransition(n))
      return visit(n);
    _table.enter(n);
    final String functionName = SymbolTable.fromNameSpace(_table.current().getName());
    final String javaEnvClassName = freshIdentifier("JavaEnvFor_" + functionName);
    final String cEnvStructName = freshIdentifier("CEnvFor_" + functionName);
    final FunctionT function = ((Type) _table.current().getParent().lookupLocally(functionName)).resolve().toFunction();
    _contexts.push(new Context("C", cEnvStructName, true, javaEnvClassName,
        context()._javaEnvPackageName, true, null, function.getResult()));
    final Out childOut = (Out) dispatch(n.getNode(4));
    final GNode cNode;
    {
      final Node body;
      final GNode javaEnvNode = GNode.create("StringConstant", '"' + context()._javaEnvPackageName + javaEnvClassName + '"');
      final GNode copyFormals = setLoc(n.getGeneric(2), GNode.create("CompoundStatement", function.getParameters().size() - 1));
      for (final Type formal : function.getParameters()) {
        final String srcId = formal.toVariable().getName();
        if (!"env".equals(srcId)) {
          final String fieldName = liftIdC(declaringScope(srcId), srcId, formal.toVariable().getType(), childOut._cMembers);
          final Node copy = _astFactoryC.setPCEnvField(fieldName, GNode.create("PrimaryIdentifier", srcId));
          copyFormals.add(copy);
        }
      }
      assert function.getResult().hasTag(Tag.VOID); //TD 06 C function definition that also contains Java code somewhere and returns non-void
      body = _astFactoryC.closureStatement(cEnvStructName, copyFormals, javaEnvNode, childOut._cNode);
      cNode = n;
      cNode.set(4, setLoc(childOut._cNode, (GNode)body));
    }
    final List<Node> cExternalDeclarations = visitMethodDeclaration_cExternalDeclarations(childOut);
    final List<Node> javaTopLevelDeclarations;
    {
      final GNode classBody = GNode.create("ClassBody", childOut._javaMembers.size());
      classBody.addAll(childOut._javaMembers);
      final GNode modifiers = GNode.create("Modifiers", GNode.create("Modifier", "final"));
      final GNode classDecl = setLoc(n, GNode.create("ClassDeclaration", modifiers, context()._javaEnvClassName, null, null, null, classBody));
      javaTopLevelDeclarations = new ArrayList<Node>(1);
      javaTopLevelDeclarations.add(classDecl);
    }
    final Out ownOut = new Out(cExternalDeclarations, new ArrayList<Node>(), 
        cNode, javaTopLevelDeclarations, null);    
    _contexts.pop();
    _table.exit(n);
    return ownOut;
  }
  
  /** Visit a JavaImports = ImportDeclaration*. */
  public final Out visitJavaImports(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    /* TD 41 jeannie.CodeGenerator.visitJavaImports: drop (or don't dispatch in first place) */
    return visit(n);
  }

  /** Visit a JavaInCBlock = JavaInJavaBlock. */
  public final Out visitJavaInCBlock(final GNode n) {
    return javaInCCode(n.getGeneric(0), false);
  }
  
  /** Visit a JavaInCExpression = JeannieJava.UnaryExpression. */
  public final Out visitJavaInCExpression(final GNode n) {
    return javaInCCode(n.getGeneric(0), true);
  }
  
  /** Visit a JavaInCStatement = TryStatement / SynchronizedStatement / ThrowStatement. */
  public final Out visitJavaInCStatement(final GNode n) {
    return javaInCCode(n.getGeneric(0), false);
  }

  /** Visit a JavaInJavaBlock = JeannieJava.DeclarationOrStatement*. */
  public final Out visitJavaInJavaBlock(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    final Out genericOut = visit(n);
    assert genericOut._javaNode.hasName("JavaInJavaBlock");
    final Out ownOut = new Out(genericOut._cExternalDeclarations,
        genericOut._cMembers, genericOut._cNode, genericOut._javaMembers, setLoc(n, GNode.create("Block", n.size())));
    for (int i = 0; i < n.size(); i++)
      ownOut._javaNode.add(i, genericOut._javaNode.get(i));
    return ownOut;
  }

  /** Visit a JavaThrows = [ThrowsClause]. */
  public final Out visitJavaThrows(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    /* TD 41 jeannie.CodeGenerator.visitJavaThrows: drop (or don't dispatch in first place) */
    return visit(n);
  }

  /** Visit a JavaType = Java.TypeName. */
  public final Out visitJavaType(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    final Type cType = Utilities.pureCType(_table, _runtime, getType(n));
    final GNode ownNode = Utilities.cTypeToAst(cType, null, "TypeName");
    final Out ownOut = new Out(new ArrayList<Node>(), new ArrayList<Node>(),
        ownNode, new ArrayList<Node>(), null);
    return ownOut;
  }

  /**
   * Visit a MethodDeclaration = Modifiers null Type Identifier FormalParameters [Dimensions]
   * [ThrowsClause] [Block] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#40420">&sect;8.4</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#41652">8.8</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#78651">9.4</a>).
   */
  public final Out visitMethodDeclaration(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    if (!Utilities.containsJavaToCTransition(n))
      return visit(n);
    _table.enter(n);
    final MethodT method = JavaEntities.currentMethod(_table);
    final String javaEnvClassName = freshIdentifier("JavaEnvFor_" + method.getName());
    final String cEnvStructName = freshIdentifier("CEnvFor_" + Utilities.jniMangledName(_table, method));
    _contexts.push(new Context("Java", cEnvStructName, false, javaEnvClassName,
        context()._javaEnvPackageName, Utilities.javaIsStaticMethod(n), null, method.getResult()));
    final Out childOut = (Out) dispatch(n.getGeneric(7));
    final Out ownOut = new Out(
        visitMethodDeclaration_cExternalDeclarations(childOut),
        new ArrayList<Node>(), null, visitMethodDeclaration_javaMembers(n, childOut),
        visitMethodDeclaration_javaNode(n));
    _contexts.pop();
    _table.exit(n);
    return ownOut;
  }

  private List<Node> visitMethodDeclaration_cExternalDeclarations(final Out childOut) {
    final List<Node> members = new ArrayList<Node>(childOut._cMembers.size());
    members.addAll(childOut._cMembers);
    final List<Node> result = new ArrayList<Node>(1 + childOut._cExternalDeclarations.size());
    final GNode struct = (GNode)_astFactoryC.declareStruct(context()._cEnvStructName, members);
    result.add(setLoc(null == childOut._cNode ? childOut._javaNode : childOut._cNode, struct));
    result.addAll(childOut._cExternalDeclarations);
    return result;
  }

  private List<Node> visitMethodDeclaration_javaMembers(final GNode n,
      final Out childOut) {
    final GNode nodeFormals = n.getGeneric(4);
    // field for caching result and formals
    if (!Utilities.javaIsVoidMethod(n))
      liftIdJava(currentMethodScope(), n, "returnResult", getType(n).toMethod().getResult(), childOut._javaMembers);
    for (final Object o : nodeFormals) {
      final GNode formal = (GNode) o;
      final String srcId = formal.getString(3);
      liftIdJava(declaringScope(srcId), formal, srcId, getType(formal), childOut._javaMembers);
    }
    // constructor
    final List<Node> statements = new ArrayList<Node>();
    final String idAbrupt = liftIdJava(currentMethodScope(), n, "returnAbrupt", JavaEntities.nameToBaseType("boolean"), childOut._javaMembers);
    statements.add(GNode.create("ExpressionStatement", _astFactoryJava.setThisDotField(idAbrupt, GNode.create("BooleanLiteral", "false"))));
    for (final Object o : nodeFormals) {
      final GNode formal = (GNode) o;
      final String srcId = formal.getString(3);
      final String tgtId = _javaSubstitutions.get(declaringScope(srcId), srcId);
      statements.add(GNode.create("ExpressionStatement", _astFactoryJava.setThisDotField(tgtId, idNode(formal, srcId))));
    }
    statements.add(childOut._javaNode);
    final GNode constructor = GNode.create("ConstructorDeclaration",
      GNode.create("Modifiers", false), null, context()._javaEnvClassName,
      nodeFormals, null, _astFactoryJava.block(statements));
    {
      final String s = Utilities.currentFunctionOrMethodName(_table);
      _methodSubstitutions.put(s.substring(0, s.indexOf('(')), s);
    }
    recordMethodSubstitution("<init>");
    // class declaration
    childOut._javaMembers.add(constructor);
    final GNode classBody = GNode.create("ClassBody", childOut._javaMembers.size());
    classBody.addAll(childOut._javaMembers);
    final GNode modifiers = context()._javaIsStatic 
      ? GNode.create("Modifiers",
                     GNode.create("Modifier", "private"),
                     GNode.create("Modifier", "static"),
                     GNode.create("Modifier", "final"))
      : GNode.create("Modifiers",
                     GNode.create("Modifier", "private"),
                     GNode.create("Modifier", "final"));
    final GNode classDecl = setLoc(n, GNode.create("ClassDeclaration", modifiers, context()._javaEnvClassName, null, null, null, classBody));
    final List<Node> result = new ArrayList<Node>(1);
    result.add(classDecl);
    return result;
  }

  private GNode visitMethodDeclaration_javaNode(final GNode n) {
    final List<Node> actuals = new ArrayList<Node>(n.getGeneric(4).size());
    for (final Object o : n.getGeneric(4))
      actuals.add(idNode((Locatable)o, ((Node)o).getString(3)));
    final GNode clazz = GNode.create("QualifiedIdentifier", context()._javaEnvClassName);
    final Node body;
    if (Utilities.javaIsVoidMethod(n)) {
      body = _astFactoryJava.closureStatement(clazz, actuals);
    } else {
      final String resultFieldName = _javaSubstitutions.get(currentMethodScope(), "returnResult");
      body = _astFactoryJava.closureExpression(clazz, actuals, resultFieldName);
    }
    final GNode result = setLoc(n, GNode.create("MethodDeclaration", 8));
    result.add(0, GNode.create("Modifiers"));
    for (final Object o : n.getGeneric(0))
      if (!"native".equals(((Node)o).getString(0)))
        result.getGeneric(0).add(o);
    for (int i = 1; i < 7; i++)
      result.add(i, n.get(i));
    result.add(7, body);
    return result;
  }

  /**
   * Visit a PrimaryIdentifier = Identifier (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/names.doc.html#106941">&sect;6.5</a>).
   */
  public final Out visitPrimaryIdentifier(final GNode n) {
    final String id = n.getString(0);
    final Out ownOut;
    final Type type = getType(n);
    if ("C".equals(context()._activeLanguage)) {
      final GNode cNode;
      final List<Node> cMembers = new ArrayList<Node>();
      if (null == type || null == context()._cEnvStructName) {
        cNode = n;
      } else if (!type.isVariable()) {
        if (type.hasAttribute(Constants.ATT_STORAGE_AUTO, true))
          cNode = (GNode) _astFactoryC.getPCEnvField(liftIdC(declaringScope(id), id, type, cMembers));
        else
          cNode = n;
      } else {
        final VariableT var = type.toVariable();
        if (VariableT.Kind.LOCAL == var.getKind() || VariableT.Kind.PARAMETER == var.getKind())
          cNode = (GNode) _astFactoryC.getPCEnvField(liftIdC(declaringScope(id), id, var.getType(), cMembers));
        else
          cNode = n;
      }
      ownOut = new Out(new ArrayList<Node>(0), cMembers, setLoc(n, cNode), new ArrayList<Node>(0), null);
    } else {
      final GNode javaNode;
      final List<Node> javaMembers = new ArrayList<Node>();
      if (null == context()._javaEnvClassName || !JavaEntities.isParameterT(type) && !JavaEntities.isLocalT(type))
        javaNode = n;
      else
        javaNode = (GNode)_astFactoryJava.getThisDotField(liftIdJava(declaringScope(id), n, id, type, javaMembers));
      ownOut = new Out(new ArrayList<Node>(0), new ArrayList<Node>(0), null, javaMembers, setLoc(n, javaNode));
    }
    return ownOut;
  }

  /**
   * Visit a ReturnStatement = [Expression] (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6767">&sect;14.16</a>).
   */
  public final Out visitReturnStatement(final GNode n) {
    final Out ownOut;
    if ("C".equals(context()._activeLanguage)) {
      if (null == context()._cEnvStructName) {
        ownOut = visit(n);
      } else {
        final List<Node> cExternalDeclarations = new ArrayList<Node>();
        final List<Node> cMembers = new ArrayList<Node>();
        final List<Node> javaMembers = new ArrayList<Node>();
        final GNode ownNode;
        final GNode jumpStatement = abruptFlowJump(n, cMembers);
        final GNode abruptStringAst = cStringNode(liftIdJava(currentMethodScope(), n, "returnAbrupt", JavaEntities.nameToBaseType("boolean"), javaMembers));
        if (null == n.get(0)) {
          ownNode = (GNode)_astFactoryC.returnVoid(abruptStringAst, jumpStatement);
        } else {
          final Out childOut = (Out) dispatch(n.getGeneric(0));
          cExternalDeclarations.addAll(childOut._cExternalDeclarations);
          cMembers.addAll(childOut._cMembers);
          javaMembers.addAll(childOut._javaMembers);
          final Type fun = Utilities.currentFunctionOrMethod(_table);
          assert fun.isMethod(); //TD 06 C return statement in C function that also contains Java code somewhere
          final Type javaType = Utilities.returnType(fun);
          final GNode resultStringAst = cStringNode(liftIdJava(currentMethodScope(), n, "returnResult", javaType, javaMembers));
          final GNode signatureStringAst = cStringNode(JavaEntities.typeToDescriptor(_table, javaType));
          final String setter = "Set" + Utilities.javaTypeToApiType(javaType, true, false) + "Field";
          ownNode = (GNode)_astFactoryC.returnResult(resultStringAst, signatureStringAst, setter, childOut._cNode, abruptStringAst, jumpStatement);
        }
        ownOut = new Out(cExternalDeclarations, cMembers, setLoc(n, ownNode), javaMembers, null);
      }
    } else {
      if (null == context()._javaEnvClassName) {
        ownOut = visit(n);
      } else {
        final List<Node> cExternalDeclarations = new ArrayList<Node>();
        final List<Node> cMembers = new ArrayList<Node>();
        final List<Node> javaMembers = new ArrayList<Node>();
        final Type fun = Utilities.currentFunctionOrMethod(_table);
        assert fun.isMethod(); //TD 06 Java return statement in C function
        final Type javaType = fun.toMethod().getResult();
        final Node ownNode;
        final String substAbrupt = liftIdJava(currentMethodScope(), n, "returnAbrupt", JavaEntities.nameToBaseType("boolean"), javaMembers);
        if (null == n.get(0)) {
          ownNode = _astFactoryJava.returnVoid(substAbrupt);
        } else {
          final Out childOut = (Out) dispatch(n.getGeneric(0));
          cExternalDeclarations.addAll(childOut._cExternalDeclarations);
          cMembers.addAll(childOut._cMembers);
          javaMembers.addAll(childOut._javaMembers);
          final String substResult = liftIdJava(currentMethodScope(), n, "returnResult", javaType, javaMembers);
          ownNode = _astFactoryJava.returnResult(substResult, childOut._javaNode, substAbrupt);
        }  
        ownOut = new Out(cExternalDeclarations, cMembers, null, javaMembers, setLoc(n, (GNode)ownNode));
      }
    }
    return ownOut;
  }

  /** 
   * Visit a ThisExpression = [Expression] (gosling_et_al_2000
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#251519">&sect;15.8.3</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#251603">&sect;15.8.4</a>).
   */
  public final Out visitThisExpression(final GNode n) {
    assert "Java".equals(context()._activeLanguage);
    assert null == n.get(0); //TD 41 allow qualified this expressions in input
    final String s = JavaEntities.currentType(_table).toClass().getName();
    final GNode ownNode = 
      setLoc(n, GNode.create("ThisExpression", 
          GNode.create("Type", 
              GNode.create("QualifiedIdentifier", s), 
              GNode.create("Dimensions"))));
    return visit(ownNode);
  }

  /** Visit a TranslationUnit = [JavaImports] ExternalDeclaration* Annotations. */
  public final Out visitTranslationUnit(final GNode n) {
    assert _contexts.isEmpty();
    assert false && null == n;
    /* TD 41 jeannie.CodeGenerator.visitTranslationUnit: invocation API, when outermost language is C */
    return null;
  }

  /** Visit a WithStatement = (JeannieC.Declaration / JeannieC.AssignmentExpression) CInCBlock. */
  public final Out visitWithStatement(final GNode n) {
    assert "C".equals(context()._activeLanguage);
    _table.enter(n);
    final GNode initNode = n.getGeneric(0);
    final String id;
    final Type cPtrType, javaType;
    final Out lhsOut, rhsOut;
    if (initNode.hasName("Declaration")) {
      final GNode dtor = initNode.getGeneric(2).getGeneric(0);
      final GNode jNode = dtor.getGeneric(4);
      id = CAnalyzer.getDeclaredId(dtor.getGeneric(1)).getString(0);
      lhsOut = (Out) dispatch(setLoc(dtor.getGeneric(1), GNode.create("PrimaryIdentifier", id)));
      rhsOut = (Out) dispatch(jNode);
      cPtrType = ((Type) _table.current().lookupLocally(id));
      javaType = Utilities.cTypeToJavaType(_table, _runtime, jNode, getType(jNode));
    } else {
      assert initNode.hasName("AssignmentExpression");
      final GNode cNode = initNode.getGeneric(0), jNode = initNode.getGeneric(2);
      id = cNode.getString(0);
      lhsOut = (Out) dispatch(cNode);
      rhsOut = (Out) dispatch(jNode);
      cPtrType = getType(cNode);
      javaType = Utilities.cTypeToJavaType(_table, _runtime, jNode, getType(jNode));
    }
    _contexts.push(new Context(context()._activeLanguage,
        context()._cEnvStructName, context()._cHasEnv,
        context()._javaEnvClassName, context()._javaEnvPackageName,
        context()._javaIsStatic, id, context()._snippetType));
    final Out blockOut = (Out) dispatch(n.getGeneric(1));
    _contexts.pop();
    final List<Node> cMembers = new ArrayList<Node>(), javaMembers = new ArrayList<Node>();
    final Node ownNode;
    {
      final GNode abruptFlowCheck = abruptFlowCheck(n, cMembers, javaMembers);
      final Node init = rhsOut._cNode;
      final Scope scope = declaringScope(id);
      final String label = liftIdCLabel(scope, "release_" + id);
      final Node body = blockOut._cNode;
      final String caField = liftIdC(scope, id, cPtrType, cMembers);
      final String releaseAbrupt = liftIdC(scope, id + "ReleaseAbrupt", typedefType("jint"), cMembers);
      if (JavaTypeConverter.isIdentical(javaType, JavaEntities.tString(_table))) {
        final Type cJniType = typedefType("jstring");
        final String jsField = liftIdC(scope, id + "JavaString", cJniType, cMembers);
        ownNode = isUtf8(cPtrType, javaType)
          ? _astFactoryC.withStringUTF(jsField, init, releaseAbrupt, caField, body, label, abruptFlowCheck)
          : _astFactoryC.withString(jsField, init, releaseAbrupt, caField, body, label, abruptFlowCheck);
      } else {
        final Type tElem = JavaEntities.arrayElementType(javaType.toArray());
        final boolean primiv = JavaEntities.isPrimitiveT(tElem);
        final Type cJniType = typedefType(primiv ? "j" + Utilities.javaTypeToApiType(javaType) : "jobject");
        final String jaField = liftIdC(scope, id + "JavaArray", cJniType, cMembers);
        if (primiv){
          final String arrayDeclString = "j" + Utilities.javaTypeToApiType(tElem) + " ca[length];";
          final GNode caNode = Utilities.cStringToAst("Declaration", arrayDeclString, Utilities.standardJniTypeDefs());
          final String getRegion = withArrayFunction(javaType, true);
          final String setRegion = withArrayFunction(javaType, false);
          ownNode = _astFactoryC.withPrimitiveArray(jaField, init, releaseAbrupt, caNode, caField, getRegion, body, label, setRegion, abruptFlowCheck);
        } else {
          ownNode = _astFactoryC.withReferenceArray(jaField, init, releaseAbrupt, caField, body, label, abruptFlowCheck);
        }
      }
    }
    final Out ownOut = new Out(new ArrayList<Node>(0), cMembers, setLoc(n, (GNode) ownNode), javaMembers, null);
    ownOut.addAll(lhsOut).addAll(rhsOut).addAll(blockOut);
    _table.exit(n);
    return ownOut;
  }

  private String withArrayFunction(final Type javaType, final boolean isAquire) {
    final StringBuffer result = new StringBuffer();
    result.append(isAquire ? "Get" : "Set");
    result.append(Utilities.javaTypeToApiType(javaType, true, true));
    result.append("Region");
    return result.toString();
  }
}
