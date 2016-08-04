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

import java.io.CharArrayWriter;
import java.io.File;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.regex.Pattern;

import xtc.Constants;
import xtc.lang.CAnalyzer;
import xtc.lang.JavaEntities;
import xtc.lang.JavaTypeConverter;
import xtc.lang.JavaUnitTests;
import xtc.parser.Result;
import xtc.parser.SemanticValue;
import xtc.tree.GNode;
import xtc.tree.LineMarker;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Visitor;
import xtc.type.AliasT;
import xtc.type.C;
import xtc.type.ClassOrInterfaceT;
import xtc.type.ErrorT;
import xtc.type.Language;
import xtc.type.MethodT;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.SourcePrinter;
import xtc.type.Type;
import xtc.type.VoidT;
import xtc.type.WrappedT;
import xtc.util.Runtime;
import xtc.util.SymbolTable;

/**
 * Static helper routines related to JNI and Jeannie.
 * This is a good place to put code that is useful for more than one visitor. 
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.30 $
 */
public final class Utilities {
  static class MiniVisitor_containsCToJavaTransition extends Visitor {
    public final Boolean visit(final LineMarker m) {
      final Node n = m.getNode();
      return null == n ? Boolean.FALSE : (Boolean)dispatch(n);
    }
    
    public final Boolean visit(final Node n) {
      for (int i = 0; i < n.size(); i++)
        if (n.get(i) instanceof Node)
          if (((Boolean) dispatch(n.getNode(i))).booleanValue())
            return Boolean.TRUE;
      return Boolean.FALSE;
    }

    public final Boolean visitJavaImports(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitJavaInCBlock(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitJavaInCExpression(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitJavaInCStatement(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitJavaThrows(final GNode n) {
      return Boolean.valueOf(null != n && null != n.get(0));
    }

    public final Boolean visitJavaType(final GNode n) {
      return Boolean.valueOf(null != n);
    }
  }
  
  static class MiniVisitor_containsJavaToCTransition extends Visitor {
    public final Boolean visit(final Node n) {
      for (int i = 0; i < n.size(); i++)
        if (n.get(i) instanceof Node)
          if (((Boolean) dispatch(n.getNode(i))).booleanValue())
            return Boolean.TRUE;
      return Boolean.FALSE;
    }

    public final Boolean visitCDeclarations(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitCInJavaBlock(final GNode n) {
      return Boolean.valueOf(null != n);
    }

    public final Boolean visitCInJavaExpression(final GNode n) {
      return Boolean.valueOf(null != n);
    }
  }
  
  static class MiniVisitor_findScopeBoundaries extends Visitor {
    private final Map<String, Location> _ends = new HashMap<String, Location>();
    private final Map<String, Location> _starts = new HashMap<String, Location>();
    private final List<String> _willEnd = new ArrayList<String>();
    
    public final void visit(final Node n) {
      if (n.hasLocation()) {
        final Location loc = n.getLocation();
        for (final String scope : _willEnd)
          _ends.put(scope, loc);
        _willEnd.clear();
        if (n.hasProperty(Constants.SCOPE))
          _starts.put((String) n.getProperty(Constants.SCOPE), loc);
      }
      for (final Object o : n)
        if (o instanceof Node)
          dispatch((Node)o);
      if (n.hasLocation() && n.hasProperty(Constants.SCOPE))
        _willEnd.add((String) n.getProperty(Constants.SCOPE));
    }
  }
  
  static class MiniVisitor_getSimpleDeclarators extends Visitor {
    public final Set<String> visit(final Node n) {
      Set<String> result = Utilities.EMPTY_SET;
      for (final Object o : n) {
        if (o instanceof Node) {
          final Set<String> childSet = Utilities.stringSet(dispatch((Node)o));
          if (!childSet.isEmpty()) {
            if (result.isEmpty())
              result = childSet;
            else
              result.addAll(childSet);
          }
        }
      }
      return result;
    }
    
    public final Set<String> visitSimpleDeclarator(final GNode n) {
      final Set<String> result = new HashSet<String>(1);
      result.add(n.getString(0));
      return result;
    }
  }
  
  static class MiniVisitor_getTopLevelDeclarations extends Visitor {
    public final Set<String> visit(final Node n) {
      Set<String> result = Utilities.EMPTY_SET;
      for (final Object o : n) {
        if (o instanceof Node) {
          final Set<String> childSet = Utilities.stringSet(dispatch((Node)o));
          if (!childSet.isEmpty()) {
            if (result.isEmpty())
              result = childSet;
            else
              result.addAll(childSet);
          }
        }
      }
      return result;
    }

    public final Set<String> visitClassDeclaration(final GNode n) {
      final Set<String> result = new HashSet<String>(1);
      result.add(n.getString(1));
      return result;
    }
    
    public final Set<String> visitInterfaceDeclaration(final GNode n) {
      final Set<String> result = new HashSet<String>(1);
      result.add(n.getString(1));
      return result;
    }
  }
  
  private static final String[] JAVA_BASE_TYPES = { "boolean", "byte", "char",
      "short", "int", "long", "float", "double" };

  public static final Set<String> EMPTY_SET = Collections.emptySet();

  private static final Set<String> STANDARD_JNI_TYPE_DEFS = new HashSet<String>();
  
  private static final Pattern AUTO_PATTERN = Pattern.compile("\\bauto\\b");

//  private static C C = (new Analyzer.JeannieCAnalyzer(new Analyzer(UnitTests.newRuntime(), new SymbolTable(), null))).c();
  private static C C = (new Analyzer.JeannieCAnalyzer(null)).c();

  public static C c() {
    return C;
  }
  
  /**
   * Don't use this method gratuitously. Originally, I used this to serialize
   * ASTs into strings, then concatenated the strings into more code, then
   * reparsed the result to a larger AST. But that is not only slow, it is also
   * brittle, since the same typedefs must be available during both parses.
   * Chances are you can use the ast directly as a parameter to an AST factory
   * generated by FactoryFactory.
   */
  public static String cAstToString(final Node ast) {
    return JavaUnitTests.cAstToString(ast);
  }

  public static boolean containsCToJavaTransition(final Node n) {
    final MiniVisitor_containsCToJavaTransition v = new MiniVisitor_containsCToJavaTransition();
    final Boolean result = (Boolean) v.dispatch(n);
    return result.booleanValue();
  }
  
  public static boolean containsJavaToCTransition(final GNode n) {
    final MiniVisitor_containsJavaToCTransition v = new MiniVisitor_containsJavaToCTransition();
    final Boolean result = (Boolean) v.dispatch(n);
    return result.booleanValue();
  }

  public static String copyDropAuto(final String string) {
    return AUTO_PATTERN.matcher(string).replaceAll("").trim();
  }
  
  public static Type cPtrToBaseType(final Type cPtrType) {
    return ((PointerT)C.pointerize(cPtrType)).getType();
  }
  
  public static GNode cStringToAst(final String production, final String code) {
    return cStringToAst(production, code, null);
  }

  public static GNode cStringToAst(final String production, final String code, final Set<String> typedefs) {
    try {
      final GNode result = JavaUnitTests.cStringToAst(production, code, typedefs);
      return JavaEntities.scrubLocations(result);
    } catch (final Exception e) {
      throw new Error(e);
    }
  }

  public static Type cStringToType(final String code) {
    return cStringToType(code, EMPTY_SET);
  }

  public static Type cStringToType(final String code, final Set<String> typedefs) {
    final GNode ast = cStringToAst("TypeName", code, typedefs);
    final CAnalyzer cAnalyzer = new CAnalyzer(newRuntime());
    try {
      final Field field = CAnalyzer.class.getDeclaredField("table");
      field.setAccessible(true);
      field.set(cAnalyzer, new SymbolTable());
    } catch (final Exception e) {
      throw new Error(e);
    }
    final Type result = cAnalyzer.visitTypeName(ast);
    return result;
  }

  public static GNode cTypeToAst(final Type type, final String id, final String production) {
    final String code;
    if (null == id) {
      assert "TypeName".equals(production);
      code = cTypeToString(type);
    } else {
      assert "StructureDeclaration".equals(production) || "Declaration".equals(production);
      code = cTypeToString(type, id) + ";";
    }
    final GNode result = cStringToAst(production, copyDropAuto(code), typedefs(type));
    return result;    
  }
  
  public static Type cTypeToJavaType(final SymbolTable tab,
      final Runtime runtime, final Node n, final Type cType) {
    if (cType.isVoid())
      return JavaEntities.nameToBaseType("void");
    {
      final Type c = Utilities.getJavaClassOrInterfaceT(cType);
      if (JavaEntities.isWrappedClassT(c) || JavaEntities.isWrappedInterfaceT(c))
        return c;
    }
    for (final String s : Utilities.JAVA_BASE_TYPES) {
      if (Utilities.hasTypedefName(cType, "j" + s))
        return JavaEntities.nameToBaseType(s);
      if (Utilities.hasTypedefName(cType, "j" + s + "Array"))
        return JavaEntities.typeWithDimensions(JavaEntities.nameToBaseType(s), 1);
    }
    if (Utilities.hasTypedefName(cType, "jsize"))
      return JavaEntities.nameToBaseType("int");
    if (Utilities.hasTypedefName(cType, "jclass"))
      return JavaEntities.tClass(tab);
    if (Utilities.hasTypedefName(cType, "jstring"))
      return JavaEntities.tString(tab);
    if (Utilities.hasTypedefName(cType, "jthrowable"))
      return JavaEntities.tThrowable(tab);
    if (Utilities.hasTypedefName(cType, "jobjectArray"))
      return JavaEntities.typeWithDimensions(JavaEntities.tObject(tab), 1);
    if (Utilities.hasTypedefName(cType, "jobject"))
      return JavaEntities.tObject(tab);
    if (C.isIntegral(cType)) {
      String tgt = "long";
      final Type jInt = (Type) tab.root().lookup("jint");
      if (null != jInt && jInt.equals(C.convert(jInt, cType)))
        tgt = "int";
      else if (null != n)
        runtime.warning("converting C type '" + cType + "' to Java type '" + tgt + "'", n);
      return JavaEntities.nameToBaseType(tgt);
    }
    if (C.isArithmetic(cType) && !C.isIntegral(cType)) {
      String tgt = "double";
      final Type jFloat = (Type) tab.root().lookup("jfloat");
      if (null != jFloat && jFloat.equals(C.convert(jFloat, cType)))
        tgt = "float";
      if (null != n)
        runtime.warning("converting C type '" + cType + "' to Java type '" + tgt + "'", n);
      return JavaEntities.nameToBaseType(tgt);
    }
    runtime.error("illegal C type '" + cType + "' in Java expression", n);
    return JavaEntities.nameToBaseType("int");
  }
  
  public static String cTypeToString(final Type type) {
    return cTypeToString(type, null);
  }

  public static String cTypeToString(final Type type, final String id) {
	final CharArrayWriter writer = new CharArrayWriter();
	final Printer printer = new Printer(writer);
	final SourcePrinter sourcePrinter = new SourcePrinter(printer);
    if (null == id)
      sourcePrinter.print(type);
    else
      sourcePrinter.print(type, id);
	printer.flush();
	return writer.toString();
  }
  
  public static Type currentFunctionOrMethod(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String scopeName = s.getName();
      if (SymbolTable.isInNameSpace(scopeName, "method"))
        return JavaEntities.currentMethod(tab);
      if (SymbolTable.isFunctionScopeName(scopeName) || SymbolTable.isMacroScopeName(scopeName)) {
        final String functionName = SymbolTable.fromNameSpace(scopeName);
        return (Type) s.getParent().lookupLocally(functionName);  
      }
    }
    return null;
  }

  public static String currentFunctionOrMethodName(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String scopeName = s.getName();
      if (SymbolTable.isInNameSpace(scopeName, "method")) {
        final MethodT m = JavaEntities.currentMethod(tab);
        return JavaEntities.typeToString(tab, false, m) + JavaEntities.typeToDescriptor(tab, m);
      }
      if (SymbolTable.isFunctionScopeName(scopeName) || SymbolTable.isMacroScopeName(scopeName))
        return SymbolTable.fromNameSpace(scopeName);
    }
    return null;
  }

  public static void dumpLineMarkers(final Set<LineMarker> ms, final int limit) {
    System.err.print("dumpLineNumbers(" + limit + " / " + ms.size() + ")");
    int i = -1 == limit ? Integer.MAX_VALUE : limit;
    for (final LineMarker m : ms) {
      i--;
      if (0 > i)
        break;
      System.err.print(" " + m.line + ":");
      Node j;
      for (j = m; null != j && j instanceof LineMarker; j = ((LineMarker)j).getNode());
      System.err.print(null == j ? "null" : j.getName());
    }
    System.err.println();
  }

  public static Type getJavaClassOrInterfaceT(final Type t) {
    Type i = t;
    do {
      if (JavaEntities.isWrappedClassT(i) || JavaEntities.isWrappedInterfaceT(i))
        return i;
      if (!(i instanceof WrappedT))
        return t;
      i = ((WrappedT) i).getType();
    } while (true);
  }
  
  public static String getSimpleDeclarator(final GNode declNode) {
    final Set<String> all = getSimpleDeclarators(declNode);
    if (all.size() != 1)
      return null;
    return all.iterator().next();
  }

  public static Set<String> getSimpleDeclarators(final GNode declNode) {
    final Visitor v = new MiniVisitor_getSimpleDeclarators();
    @SuppressWarnings("unchecked")
    final Set<String> result = (Set<String>) v.dispatch(declNode);
    return result;
  }

  public static boolean hasTypedefName(final Type t, final String name) {
    Type i = t;
    while (i instanceof WrappedT) {
      if (i instanceof AliasT) {
        final String n = i.toAlias().getName();
        if (n.equals(name))
          return true;
      }
      i = ((WrappedT) i).getType();
    }
    return false;
  }
  
  public static boolean isJavaEntity(final Type e) {
    if (JavaEntities.isWrappedClassT(e) || JavaEntities.isWrappedInterfaceT(e))
      return true;
    if (e.isMethod() || e.isPackage())
      return true;
    if (JavaEntities.isParameterT(e) || JavaEntities.isFieldT(e) || JavaEntities.isLocalT(e))
      return Language.JAVA == e.getLanguage();
    return false;
  }

  public static boolean isPtrChar(final Type t) {
    final Type p = c().pointerize(t);
    if (!p.isPointer())
      return false;
    final Type e = p.toPointer().getType().resolve();
    return e.isNumber() && NumberT.Kind.CHAR == e.toNumber().getKind();
  }

  public static boolean isPtrTypedef(final Type t, final String typedefName) {
    final Type p = c().pointerize(t);
    return p.isPointer() && hasTypedefName(p.toPointer().getType(), typedefName);
  }

  public static String javaAstToString(final Node ast) {
    return JavaEntities.javaAstToString(ast);
  }

  public static boolean javaIsStaticMethod(final GNode n) {
    final Type type = (Type) n.getProperty(Constants.TYPE);
    assert type.isMethod();
    return type.hasAttribute(JavaEntities.nameToModifier("static"));
  }
  
  public static boolean javaIsVoidMethod(final GNode n) {
    final Type returnType = ((Type) n.getProperty(Constants.TYPE)).toMethod().getResult();
    return returnType.isVoid();
  }

  public static String javaTypeToApiType(final Type type) {
    return javaTypeToApiType(type, false, true);
  }

  public static String javaTypeToApiType(final Type type, final boolean upcase, final boolean arrays) {
    if (type.isVoid())
      return "Void";
    if (JavaEntities.isGeneralLValueT(type))
      return javaTypeToApiType(JavaEntities.dereference(type), upcase, arrays);
    final boolean isArray = type.isArray();
    final Type elemType = isArray ? JavaEntities.arrayElementType(type.toArray()) : null;
    String result = "Object";
    for (final String s : JAVA_BASE_TYPES) {
      final Type jBaseType = JavaEntities.nameToBaseType(s);
      if (arrays && isArray) {
        if (JavaTypeConverter.isIdentical(elemType, jBaseType)) {
          result = s + "Array";
          break;
        }
      } else {
        if (JavaTypeConverter.isIdentical(type, jBaseType)) {
          result = s;
          break;
        }
      }
    }
    return upcase ? upcaseFirstLetter(result) : result;
  }
  
  public static Type javaTypeToCType(final SymbolTable tab,
      final Runtime runtime, final Node n, final Type jType,
      final boolean keepIfClassOrInterface) {
    if (jType.isError())
      return ErrorT.TYPE;
    if (jType.isVoid())
      return VoidT.TYPE;
    assert JavaEntities.isGeneralRValueT(jType);
    if (JavaEntities.isNullT(jType))
      return C.typeInteger("0");
    if (keepIfClassOrInterface)
      if (JavaEntities.isWrappedClassT(jType) || JavaEntities.isWrappedInterfaceT(jType))
        return jType;
    String cTypeName = null;
    for (final String s : Utilities.JAVA_BASE_TYPES) {
      final Type jBaseType = JavaEntities.nameToBaseType(s);
      if (JavaTypeConverter.isIdentical(jType, jBaseType))
        cTypeName = "j" + s;
      else if (JavaTypeConverter.isIdentical(jType, JavaEntities
          .typeWithDimensions(jBaseType, 1)))
        cTypeName = "j" + s + "Array";
      if (null != cTypeName)
        break;
    }
    final List<File> paths = JavaEntities.classpath(runtime);
    if (null == cTypeName && JavaTypeConverter.isAssignable(tab, paths, JavaEntities.tClass(tab), jType))
      cTypeName = "jclass";
    if (null == cTypeName && JavaTypeConverter.isAssignable(tab, paths, JavaEntities.tString(tab), jType))
      cTypeName = "jstring";
    if (null == cTypeName && JavaTypeConverter.isAssignable(tab, paths, JavaEntities.tThrowable(tab), jType))
      cTypeName = "jthrowable";
    if (null == cTypeName && jType.isArray()) {
      assert JavaEntities.isReferenceT(JavaEntities.arrayElementType(jType.toArray()));
      cTypeName = "jobjectArray";
    }
    if (null == cTypeName) {
      assert JavaEntities.isReferenceT(jType);
      cTypeName = "jobject";
    }
    final Type cType = (Type) tab.root().lookup(cTypeName);
    if (null != cType)
      return cType;
    runtime.error("C typedef for '" + cTypeName + "' missing; did you forget to #include <jni.h>?", n);
    return ErrorT.TYPE;
  }

  public static String jeannieAstToString(final GNode ast, final String language) {
    final CharArrayWriter writer = new CharArrayWriter();
    final JeanniePrinter printer = new JeanniePrinter(new Printer(writer), language);
    printer.dispatch(ast);
    return writer.toString();
  }

  public static GNode jeannieStringToAst(final String production,
      final String language, final String code) {
    try {
      return jeannieStringToAst(production, language, code, true);
    } catch (final Exception e) {
      throw new Error(e);
    }
  }

  public static GNode jeannieStringToAst(final String production,
      final String language, final String escaped, final boolean simple)
      throws Exception {
    final Class[] paramTypes = { Integer.TYPE };
    final Method method = JeannieParser.class.getDeclaredMethod("p" + production,
        paramTypes);
    method.setAccessible(true);
    final String string = JavaEntities.unicodeUnescape(escaped);
    final JeannieParser parser = new JeannieParser(new StringReader(string), "<input>",
        string.length());
    final Object[] paramValues = { new Integer(0) };
    final Result parseResult = (Result) method.invoke(parser, paramValues);
    if (parseResult.hasValue()) {
      final SemanticValue val = (SemanticValue) parseResult;
      if (val.index != string.length())
        parser.signal(parseResult.parseError());
      final GNode ast = (GNode) val.value;
      if (simple)
        return (GNode) new AstSimplifier(language).dispatch(ast);
      return ast;
    }
    parser.signal(parseResult.parseError());
    return null;
  }
  
  /**
   * Part of name of C function implementing Java method as expected by linker,
   * see JNI Specification <a
   * href="http://java.sun.com/docs/books/jni/html/design.html#9984">&sect;11.3</a>.
   */
  public static String jniMangledName(final String name) {
    final StringBuffer b = new StringBuffer(name.length());
    for (int i = 0; i < name.length(); i++) {
      final char c = name.charAt(i);
      switch (c) {
      case '.':
        b.append('_');
        break;
      case '_':
        b.append("_1");
        break;
      case ';':
        b.append("_2");
        break;
      case '[':
        b.append("_3");
        break;
      default:
        if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c
            && c <= '9') {
          b.append(c);
        } else {
          final String hex = Integer.toHexString(c);
          b.append("_0");
          for (int j=0; j<4-hex.length(); j++)
            b.append('0');
          b.append(hex);
        }
      }
    }
    return b.toString();
  }
  
  public static String jniMangledName(final SymbolTable tab, final Type type) {
    if (type.isClass())
      return jniMangledName(JavaEntities.qNameWithDollars(tab, type.toClass()));
    if (type.isInterface())
      return jniMangledName(JavaEntities.qNameWithDollars(tab, type.toInterface()));
    assert type.isMethod();
    final ClassOrInterfaceT declaringType = JavaEntities.declaringType(tab, type);
    final String declaringMangled = jniMangledName(tab, declaringType);
    final String nameMangled = jniMangledName(type.toMethod().getName());
    final String md = JavaEntities.typeToDescriptor(tab, type);
    final String ad = md.substring(1 + md.indexOf('('), md.indexOf(')'));
    if (0 == ad.length())
      return declaringMangled + "_" + nameMangled;
    return declaringMangled + "_" + nameMangled + "__" + jniMangledName(ad);
  }
  
  public static Runtime newRuntime() {
    final Runtime runtime = new Runtime();
    runtime.dir("in", Runtime.INPUT_DIRECTORY, true, "").setValue(Runtime.INPUT_DIRECTORY, JavaEntities.TEMP_DIR);
    runtime.bool("markAST", "optionMarkAST", true, "Mark AST nodes with types.").setValue("optionMarkAST", true);
    runtime.bool("strict", "optionStrict", true, "Enforce strict C99 compliance.").setValue("optionStrict", true);
    runtime.bool("pedantic", "optionPedantic", false, "Enforce strict C99 compliance.").setValue("optionPedantic", true);
    runtime.word("jniCall", "jniCall", false, "Calling conventions qualifier to C JNI functions.").setValue("jniCall", "");
    runtime.initDefaultValues();
    return runtime;
  }
  
  static void printLocalVariableMap(final PrintWriter out, final Node root,
      final SymbolTable tab, final CodeGenerator.Substitutions cSubstitutions,
      final CodeGenerator.Substitutions javaSubstitutions) {
    final MiniVisitor_findScopeBoundaries boundaries = new MiniVisitor_findScopeBoundaries();
    boundaries.dispatch(root);
    out.println("LocalVariableMap:");
    out.println("# file startLine startCol endLine endCol lang srcId tgtId");
    printLocalVariableMap_helper(out, tab, boundaries, "C", cSubstitutions);
    printLocalVariableMap_helper(out, tab, boundaries, "Java", javaSubstitutions);
    out.println();
  }

  static void printLocalVariableMap_helper(final PrintWriter out,
      final SymbolTable tab, final MiniVisitor_findScopeBoundaries boundaries,
      final String language, final CodeGenerator.Substitutions substitutions) {
    for (final CodeGenerator.StringString ss : substitutions) {
      final String scopeName = ss._s1;
      Location start = null;
      if (false) {
        start = boundaries._starts.get(scopeName);
      } else {
        for (String s = scopeName; 0 < s.length(); s = xtc.util.Utilities.getQualifier(s)) {
          start = boundaries._starts.get(s);
          if (null != start)
            break;
        }
      }
      assert null != start;
      final Location end = boundaries._ends.get(scopeName);
      assert null == end || end.file.equals(start.file);
      final String srcId = ss._s2;
      final String tgtId = substitutions.get(tab.getScope(scopeName), srcId);
      out.print("  " + start.file + " " + start.line + " " + start.column);
      if (null == end)
        out.print(" - -");
      else
        out.print(" " + end.line + " " + end.column);
      out.println(" " + language + " " + srcId + " " + tgtId);
    }
  }


  public static void printMethodMap(final PrintWriter out, final SymbolTable tab, final Map<String, String> substitutions) {
    out.println("MethodMap:");
    out.println("# srcMethod tgtFunctionOrMethod:");
    for (final String tgt : substitutions.keySet())
      out.println("  " + substitutions.get(tgt) + " " + tgt);
    out.println();
  }

  public static void printTopLevelDeclarations(final PrintWriter out, final Node root) {
    final Visitor v = new MiniVisitor_getTopLevelDeclarations();
    out.print("TopLevelClassesOrInterfaces:");
    for (final String s : JavaEntities.stringSet(v.dispatch(root)))
      out.print(" " + s);
    out.println();
    out.println();
  }

  public static Type pureCType(final SymbolTable tab, final Runtime runtime, final Type javaOrCType) {
    if (isJavaEntity(javaOrCType))
      return javaTypeToCType(tab, runtime, null, javaOrCType, false);
    if (javaOrCType.isAnnotated())
      return pureCType(tab, runtime, javaOrCType.toAnnotated().getType());
    if (javaOrCType.isVariable())
      return pureCType(tab, runtime, javaOrCType.toVariable().getType());
    return javaOrCType;
  }
  
  public static String qualifiedIdentifierToString(final GNode n) {
    final StringBuilder b = new StringBuilder();
    for (int i = 0; i < n.size(); i++) {
      if (0 < i)
        b.append(Constants.QUALIFIER);
      b.append(n.getString(i));
    }
    return b.toString();
  }

  public static Type returnType(final Type functionOrMethod) {
    if (functionOrMethod.isMethod())
      return functionOrMethod.toMethod().getResult();
    else
      return functionOrMethod.resolve().toFunction().getResult();
  }
  
  public static Set<String> standardJniTypeDefs() {
    if (STANDARD_JNI_TYPE_DEFS.isEmpty()) {
      for (final String s : JAVA_BASE_TYPES) {
        STANDARD_JNI_TYPE_DEFS.add("j" + s);
        STANDARD_JNI_TYPE_DEFS.add("j" + s + "Array");
      }
      final String[] a = { "JNIEnv", "jclass", "jfieldID", "jmethodID", "jobject", "jstring" };
      for (final String s : a)
        STANDARD_JNI_TYPE_DEFS.add(s);
    }
    return STANDARD_JNI_TYPE_DEFS;
  }

  @SuppressWarnings("unchecked")
  public static Set<String> stringSet(final Object s) {
    return (Set<String>)s;
  }

  public static String stringSetToString(final Set<String> s) {
    final StringBuilder result = new StringBuilder();
    for (final String e : s) {
      if (0 < result.length())
        result.append(' ');
      result.append(e);
    }
    return result.toString();
  }

  public static Set<String> typedefs(Type r) {
    final Set<String> result = new HashSet<String>();
    while (true) {
      if (r.isAlias())
        result.add(r.toAlias().getName());
      if (r instanceof WrappedT)
        r = ((WrappedT)r).getType();
      else if (r instanceof PointerT)
        r = ((PointerT)r).getType();
      else
        break;
    }
    return result;
  }

  public static String upcaseFirstLetter(final String s) {
    final char[] chars = s.toCharArray();
    chars[0] = Character.toUpperCase(chars[0]);
    return new String(chars);
  }

  private Utilities() {
    assert false;
  }
}
