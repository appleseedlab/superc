/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2005-2007 IBM Corp.
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

import java.io.CharArrayWriter;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Formatter;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import xtc.Constants;
import xtc.parser.ParseException;
import xtc.parser.Result;
import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.LineMarker;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Visitor;
import xtc.type.AliasT;
import xtc.type.AnnotatedT;
import xtc.type.ArrayT;
import xtc.type.BooleanT;
import xtc.type.ClassOrInterfaceT;
import xtc.type.ClassT;
import xtc.type.DynamicReference;
import xtc.type.FunctionOrMethodT;
import xtc.type.IntegerT;
import xtc.type.InterfaceT;
import xtc.type.MethodT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.PackageT;
import xtc.type.Type;
import xtc.type.TypePrinter;
import xtc.type.VariableT;
import xtc.type.VoidT;
import xtc.type.WrappedT;
import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.Utilities;
import xtc.util.SymbolTable.Scope;

/**
 * Common functionality for handling Java entities outside the AST.
 * 
 * <p><u>Composite types</u>
 * <table border=0>
 * <tr><td>ExpressionT       <td>&gt; <td>GeneralLValueT, GeneralRValueT
 * <tr><td>GeneralLValueT    <td>&gt; <td><b>LValueT</b>, FieldT, LocalT, ParameterT
 * <tr><td><b>LValueT</b>    <td>=    <td>RValueT
 * <tr><td>FieldT            <td>&gt; <td><b>VariableT</b>:(FIELD Name WrappedRValueT)
 * <tr><td>LocalT            <td>&gt; <td><b>VariableT</b>:(LOCAL Name WrappedRValueT)
 * <tr><td>ParameterT        <td>&gt; <td><b>VariableT</b>:(PARAMETER Name RValueT)
 * <tr><td>GeneralRValueT    <td>&gt; <td><b>NullT</b>, WrappedRValueT
 * <tr><td>RValueT           <td>&gt; <td>PrimitiveT, <b>ArrayT</b>, WrappedClassT, WrappedInterfaceT
 * <tr><td><b>ArrayT</b>     <td>=    <td><b>LValueT</b>
 * <tr><td><b>ClassT</b>     <td>=    <td>Name WrappedClassT WrappedInterfaceT* Members
 * <tr><td><b>InterfaceT</b> <td>=    <td>Name WrappedInterfaceT* Members
 * <tr><td>Members</b>       <td>=    <td>FieldT* MethodT* WrappedClassT* WrappedInterfaceT*
 * <tr><td><b>MethodT</b>    <td>=    <td>ReturnT Name ParameterT* WrappedClassT*
 * <tr><td>NotAValueT        <td>&gt; <td><b>PackageT</b>, <b>AnnotatedT</b>:ReturnT --- annotated with Constants.ATT_NOT_A_VALUE
 * <tr><td>ReturnT           <td>&gt; <td><b>VoidT</b>, RValueT
 * </table>
 * 
 * <p><u>Wrapped types</u>
 * <table border=0>
 * <tr><td>WrappedRValueT</td>     <td>&gt; <td><b>ConstantT</b>:RValueT / RValueT
 * <tr><td>WrappedClassT</td>      <td>&gt; <td><b>AliasT</b>:Name / <b>AliasT</b>:<b>ClassT</b> / <b>ClassT</b>
 * <tr><td>WrappedInterfaceT</td>  <td>&gt; <td><b>AliasT</b>:Name / <b>AliasT</b>:<b>InterfaceT</b> / <b>InterfaceT</b>
 * </table>
 * 
 * <p><u>Basetypes</u>
 * <table border=0>
 * <tr><td>PrimitiveT      <td>&gt; <td><b>BooleanT</b>, <b>NumberT</b>
 * <tr><td><b>NumberT</b>  <td>&gt; <td><b>IntegerT</b>, <b>FloatT</b>
 * <tr><td>NullT           <td>=    <td><b>ConstantT</b>:<b>VoidT</b>
 * </table>
 * </table>
 *  
 * <p><u>Explanation</u>
 * <table border=0>
 * <tr><td><b>Bold font entities</b>          <td>are represented explicitly in xtc.type
 * <tr><td><i>Super &gt;  Sub1, ..., SubN</i> <td>any of the <i>SubI</i> can appear where a <i>Super</i> is expected
 * <tr><td><i>Whole = Part1, ..., PartN</i>   <td>the <i>Whole</i> consists of all the parts <i>PartI</i>
 * <tr><td><i>Whole = Part1 / ... / PartN</i> <td>the <i>Whole</i> consists of one of the parts <i>PartI</i>
 * <tr><td><i>Wrapper:Contents</i>            <td>the <i>Wrapper</i> must wrap an instance of <i>Contents</i>
 * <tr><td><i>Repetee</i>*                    <td>zero or more occurences
 * </table>
 * 
 * @author Martin Hirzel
 */
public final class JavaEntities {
  public static final class JavaTypePrinter extends TypePrinter {
    private boolean _showDetails;

    private final SymbolTable _table;

    public JavaTypePrinter(final SymbolTable tab, final boolean showDetails, final Printer initPrinter) {
      super(initPrinter);
      _showDetails = showDetails;
      _table = tab;
    }

    private boolean isJavaLangObject(final Type t) {
      if (null == t)
        return false;
      if (t.isClass())
        return t.toClass().getQName().equals("java.lang.Object");
      assert t.isAlias();
      final String n = t.toAlias().getName();
      return n.equals("Object") || n.equals("java.lang.Object");
    }

    public final boolean printAnnotations(final Type t) {
      printAttributes(t);
      return t.hasAttributes();
    }

    public final void printAttributes(final Type t) {
      if (t.hasAttributes())
        for (final Attribute att : t.attributes())
          printer.p(modifierToName(att)).p(' ');
    }
    
    private final void printMethodNoDetails(final MethodT t) {
      assert !_showDetails;
      dispatch(JavaEntities.declaringType(_table, t));
      printer.p('.').p(t.getName());
    }

    public final void printSignature(final FunctionOrMethodT t) {
      if (!_showDetails)
        throw new Error();
      _showDetails = false;
      printer.p('(');
      for (final Iterator<Type> iter = t.getParameters().iterator(); iter.hasNext(); ) {
        printer.p(iter.next());
        if (iter.hasNext() || t.isVarArgs())
          printer.p(", ");
      }
      if (t.isVarArgs())
        printer.p("...");
      printer.p(") -> ");
      if (t.getResult().resolve().isFunction())
        printer.p('(').p(t.getResult()).p(')');
      else
        printer.p(t.getResult());
      if ((null != t.getExceptions()) && (! t.getExceptions().isEmpty())) {
        printer.p(" throws ");
        for (Iterator<Type> iter = t.getExceptions().iterator(); iter.hasNext(); ) {
          printer.p(iter.next());
          if (iter.hasNext())
            printer.p(", ");
        }
      }
      _showDetails = true;
    }

    public final void visit(final AliasT t) {
      printer.p(t.getName());
    }

    public final void visit(final AnnotatedT t) {
      if (JavaEntities.isNullT(t)) {
        printer.p("null");
        return;
      }
      if (_showDetails)
        printAttributes(t);
      printer.p(t.getType());
    }

    public final void visit(final ArrayT t) {
      printer.p(arrayElementType(t)).p("[]");
    }
    
    public final void visit(final BooleanT t) {
      printer.p("boolean");
    }
    
    public final void visit(final ClassT t) {
      if (!_showDetails) {
        printer.p(t.getQName());
        return;
      }
      printAttributes(t);
      printer.p("class ").p(t.getQName());
      if (!isJavaLangObject(t.getParent()))
        printer.p(" extends ").p(t.getParent());
      if (!t.getInterfaces().isEmpty()) {
        printer.p(" implements ");
        for (final Iterator<Type> i = t.getInterfaces().iterator(); i.hasNext();) {
          printer.p(i.next());
          if (i.hasNext())
            printer.p(", ");
        }
      }
      printer.p("{");
      final Scope scope = _table.getScope(typeToScopeName(t));
      final TreeSet<String> sortedMembers = new TreeSet<String>();
      for (final Iterator<String> i = scope.symbols(); i.hasNext();)
        sortedMembers.add(i.next());
      for (final String s : sortedMembers) {
        final Type m = (Type) scope.lookupLocally(s);
        assert null != m;
        dispatch(m);
        printer.p("; ");
      }
      printer.p("}");
    }

    public final void visit(final InterfaceT t) {
      if (!_showDetails) {
        printer.p(t.getQName());
        return;
      }
      printAttributes(t);
      printer.p("interface ").p(t.getQName());
      if (!t.getInterfaces().isEmpty()) {
        printer.p(" extends ");
        for (final Iterator<Type> i = t.getInterfaces().iterator(); i.hasNext();) {
          printer.p(i.next());
          if (i.hasNext())
            printer.p(", ");
        }
      }
      printer.p("{");
      final Scope scope = _table.getScope(typeToScopeName(t));
      final TreeSet<String> sortedMembers = new TreeSet<String>();
      for (final Iterator<String> i = scope.symbols(); i.hasNext();)
        sortedMembers.add(i.next());
      for (final String s : sortedMembers) {
        final Type m = (Type) scope.lookupLocally(s);
        assert null != m;
        dispatch(m);
        printer.p("; ");
      }
      printer.p("}");
    }

    public final void visit(final MethodT t) {
      if (_showDetails)
        super.visit(t);
      else
        printMethodNoDetails(t);
    }
  }
  
  static class MiniVisitor_allUsedIdentifiers extends Visitor {
    public final Set<String> visit(final LineMarker m) {
      final Node n = m.getNode();
      return null == n ? EMPTY_SET : stringSet(dispatch(n));
    }
    public final Set<String> visit(final Node n) {
      final Set<String> result = new HashSet<String>();
      for (int i = 0; i < n.size(); i++) {
        if (n.get(i) instanceof String)
          result.add(n.getString(i));
        else if (n.get(i) instanceof Node)
          result.addAll(stringSet(dispatch(n.getNode(i))));
      }
      return result;
    }
    public final Set<String> visitBinaryExpression(final GNode n) {
      final Set<String> result = new HashSet<String>();
      result.addAll(stringSet(dispatch(n.getNode(0))));
      result.addAll(stringSet(dispatch(n.getNode(2))));
      return result;
    }
    public final Set<String> visitBlockDeclaration(final GNode n) {
      return stringSet(dispatch(n.getNode(1)));
    }
    public final Set<String> visitBooleanLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitCharacterLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitFieldDeclaration(final GNode n) {
      final Set<String> result = new HashSet<String>();
      result.addAll(stringSet(dispatch(n.getNode(1))));
      result.addAll(stringSet(dispatch(n.getNode(2))));
      return result;
    }
    public final Set<String> visitFloatingPointLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitForInit(final GNode n) {
      if (1 == n.size())
        return stringSet(dispatch(n.getNode(0)));
      return stringSet(dispatch(n.getNode(1)));
    }
    public final Set<String> visitFormalParameter(final GNode n) {
      final Set<String> result = new HashSet<String>();
      result.addAll(stringSet(dispatch(n.getNode(1))));
      result.add(n.getString(3));
      return result;
    }
    public final Set<String> visitImportDeclaration(final GNode n) {
      return stringSet(dispatch(n.getNode(1)));
    }
    public final Set<String> visitIntegerLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitNullLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitPostfixUnaryExpression(final GNode n) {
      return stringSet(dispatch(n.getNode(0)));
    }
    public final Set<String> visitPrefixUnaryExpression(final GNode n) {
      return stringSet(dispatch(n.getNode(1)));
    }
    public final Set<String> visitStringLiteral(final GNode n) {
      return EMPTY_SET;
    }
    public final Set<String> visitType(final GNode n) {
      return stringSet(dispatch(n.getNode(0)));
    }
  }

  static class MiniVisitor_scrubLocations extends Visitor {
    public final void visit(final Node n) {
      n.setLocation((Location)null);
      for (final Object o : n)
        if (o instanceof Node)
          dispatch((Node)o);
    }
  }

  /**
   * Enumerates all the types from which this type may inherit methods or
   * fields. For classes and interfaces, this means all reflexive or transitive
   * super-classes/insterfaces. For arrays, this means Object, Cloneable, or
   * Serializable. This iterator will resolve any aliases it encounters on the
   * way. This iterator only applies to reference types.
   */
  static final class SuperTypesIter implements Iterator<Type> {
    private static String key(final Type type) {
      final Type t = type.isAlias() ? ((AliasT) type).getType() : type;
      if (t.isArray())
        return key(JavaEntities.arrayElementType(t.toArray())) + "[]";
      if (JavaEntities.isPrimitiveT(type))
        return type.toString();
      return JavaEntities.resolveToRawClassOrInterfaceT(t).getQName();
    }

    private final List<File> _paths;   

    /** Set of String keys: current and former contents of todo. */
    private final Set<String> _seen = new HashSet<String>();

    private final SymbolTable _tab; 

    /** List of Types; add to end, remove from front. */
    private final LinkedList<Type>  _todo = new LinkedList<Type>();

    public SuperTypesIter(final SymbolTable tab, final List<File> paths,
        final Type start) {
      this(tab, paths, start, true);
    }

    public SuperTypesIter(final SymbolTable tab, final List<File> paths,
        final Type start, final boolean reflexive) {
      _tab = tab;
      _paths = paths;
      final Type rStart = JavaEntities.resolveToRValue(start);
      if (reflexive)
        add(rStart);
      else
        addDirectSupertypes(rStart);
    }

    private final void add(final Type type) {
      assert null != type;
      assert JavaEntities.isReferenceT(type);
      if (_seen.add(key(type)))
        _todo.addLast(type);
    }

    private void addDirectSupertypes(final Type sub) {
      for (final ClassOrInterfaceT sup : JavaEntities.directSuperTypes(_tab, _paths, sub))
        add(sup);
    }

    public final boolean hasNext() {
      return !_todo.isEmpty();
    }

    public final Type next() {
      if (_todo.isEmpty())
        return null;
      final Type result = _todo.removeFirst();
      addDirectSupertypes(result);
      return result;
    }
    
    public final void remove() {
      throw new UnsupportedOperationException();
    }
  }
  
  public static final class UnicodeUnescaper extends Reader {
    private boolean _havePeek;
    private int _peek;
    private final Reader _reader;

    public UnicodeUnescaper(final Reader reader) {
      _havePeek = false;
      _peek = -1;
      _reader = reader;
    }
    
    public final void close() throws IOException {
      _reader.close();
    }

    public final int read() throws IOException {
      if (_havePeek) {
        _havePeek = false;
        return _peek;
      }
      final int a = _reader.read();
      if ('\\' != a)
        return a;
      _peek = _reader.read();
      if ('u' != _peek) {
        _havePeek = true;
        return a;
      }
      int curr = _peek;
      while ('u' == curr)
        curr = _reader.read();
      final byte[] digits = new byte[4];
      for (int i=0; i<4; i++) {
        if (0 != i)
          curr = _reader.read();
        switch (curr) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          digits[i] = (byte)(curr - '0');
          break;
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
          digits[i] = (byte)(10 + curr - 'a');
          break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
          digits[i] = (byte)(10 + curr - 'A');
          break;
        default:
          throw new Error("illegal unicode sequence");
        }
      }
      int result = 0;
      for (int i=0; i<4; i++)
        result = (result << 4) | digits[i];
      return result;
    }

    public final int read(final char[] cbuf, final int off, final int len) throws IOException {
      int result = 0;
      while (result < len) {
        final int c = read();
        if (-1 == c)
          return -1;
        cbuf[off + result] = (char)c;
        result++;
      }
      return result;
    }
  }

  public static final File TEMP_DIR;
  
  public static final Set<String> EMPTY_SET = Collections.emptySet();

  private static final Map<Attribute,String> MODIFIER_TO_NAME = new HashMap<Attribute,String>();

  private static final Map<String,Type>      NAME_TO_BASETYPE = new HashMap<String,Type>();

  private static final Map<String,Attribute> NAME_TO_MODIFIER = new HashMap<String,Attribute>();

  private static boolean recursiveTypeDotType = false;
  
  static {
    final String[] names = new String[] {
      System.getProperty("TMP"), System.getProperty("TEMP"), "/tmp", "/cygwin/tmp", "."
    };
    File tempDir = null;
    for (final String name : names) {
      if (null != name) {
        final File f = new File(name);
        if (f.exists()) {
          tempDir = f;
          break;
        }
      }
    }
    assert null != tempDir && tempDir.exists();
    TEMP_DIR = tempDir;

    NAME_TO_MODIFIER.put("public", Constants.ATT_PUBLIC);
    NAME_TO_MODIFIER.put("protected", Constants.ATT_PROTECTED);
    NAME_TO_MODIFIER.put("private", Constants.ATT_PRIVATE);
    NAME_TO_MODIFIER.put("static", Constants.ATT_STORAGE_STATIC);
    NAME_TO_MODIFIER.put("abstract", Constants.ATT_ABSTRACT);
    NAME_TO_MODIFIER.put("final", Constants.ATT_CONSTANT);
    NAME_TO_MODIFIER.put("native", Constants.ATT_NATIVE);
    NAME_TO_MODIFIER.put("synchronized", Constants.ATT_SYNCHRONIZED);
    NAME_TO_MODIFIER.put("transient", Constants.ATT_TRANSIENT);
    NAME_TO_MODIFIER.put("volatile", Constants.ATT_VOLATILE);
    NAME_TO_MODIFIER.put("strictfp", Constants.ATT_STRICT_FP);
    for (final Map.Entry<String,Attribute> e : NAME_TO_MODIFIER.entrySet())
      MODIFIER_TO_NAME.put(e.getValue(), e.getKey());
    NAME_TO_BASETYPE.put("boolean", BooleanT.TYPE);
    NAME_TO_BASETYPE.put("byte", NumberT.BYTE);
    NAME_TO_BASETYPE.put("char", NumberT.CHAR);
    NAME_TO_BASETYPE.put("double", NumberT.DOUBLE);
    NAME_TO_BASETYPE.put("float", NumberT.FLOAT);
    NAME_TO_BASETYPE.put("int", NumberT.INT);
    NAME_TO_BASETYPE.put("long", NumberT.LONG);
    NAME_TO_BASETYPE.put("null", VoidT.TYPE.annotate().constant(NullReference.NULL));
    NAME_TO_BASETYPE.put("short", NumberT.SHORT);
    NAME_TO_BASETYPE.put("void", VoidT.TYPE);
  }

  public static void addBaseTypes(final SymbolTable tab) {
    if (null == tab.lookup("int")) {
      final String oldScope = JavaEntities.enterScopeByQualifiedName(tab, "");
      for (final String name : NAME_TO_BASETYPE.keySet())
        tab.current().define(name, nameToBaseType(name));
      JavaEntities.enterScopeByQualifiedName(tab, oldScope);
    }
  }
  
  public static List<MethodT> allAbstractMethods(final SymbolTable tab,
      final List<File> paths, final ClassT clazz) {
    final List<MethodT> all = allMethods(tab, paths, clazz);
    final List<MethodT> specific = mostSpecificMethods(tab, paths, all);
    final List<MethodT> result = new ArrayList<MethodT>();
    for (final MethodT method : specific)
      if (hasModifier(method, "abstract"))
        result.add(method);
    return result;
  }
  
  public static List<MethodT> allMethods(final SymbolTable tab, final List<File> paths,
      final ClassT base) {
    final List<MethodT> result = new ArrayList<MethodT>();
    for (final Iterator<Type> i = new SuperTypesIter(tab, paths, base); i.hasNext();)
      result.addAll(methodsOwn(i.next()));
    return result;
  }

  public static Set<String> allUsedIdentifiers(final GNode ast) {
    final MiniVisitor_allUsedIdentifiers v = new MiniVisitor_allUsedIdentifiers();
    final Set<String> result = stringSet(v.dispatch(ast));
    return result;
  }

  public static Type arrayElementType(final ArrayT arrayT) {
    final AnnotatedT l = (AnnotatedT)arrayT.getType();
    final Type result = l.getType();
    assert isRValueT(result);
    return result;
  }
  
  public static VariableT arrayLengthField() {
    final VariableT result = VariableT.newField(nameToBaseType("int"), "length");
    result.addAttribute(nameToModifier("final"));
    result.addAttribute(nameToModifier("public"));
    result.scope(".package(java.lang).file().Object");
    assert isFieldT(result);
    return result;
  }

  public static String baseTypeToName(final Type baseType) {
    return typeToString(null, false, baseType);
  }

  public static ClassOrInterfaceT canonicalAliasToType(final SymbolTable tab,
      final List<File> paths, final AliasT alias, final boolean mayBeInUnnamedPackage) {
    if (alias.getType() == null)
      alias.setType(canonicalNameToType(tab, paths, alias.getName(), mayBeInUnnamedPackage));
    return (ClassOrInterfaceT) alias.getType();
  }

  public static String canonicalName(final SymbolTable tab,
      final String simpleName) {
    final ClassOrInterfaceT enclosingClass = currentType(tab);
    if (enclosingClass != null)
      return Utilities.qualify(enclosingClass.getQName(), simpleName);
    final PackageT enclosingPackage = currentPackage(tab);
    if (enclosingPackage == null) {
      final Error e = new Error();
      e.printStackTrace();
      throw e;
    }
    if ("".equals(enclosingPackage.getName()))
      return simpleName;
    return Utilities.qualify(enclosingPackage.getName(), simpleName);
  }

  public static PackageT canonicalNameToPackage(final SymbolTable tab,
      final String name) {
    if (name.indexOf('.') == -1)
      return simpleNameToPackage(tab, name);
    final PackageT base = canonicalNameToPackage( //
        tab, Utilities.getQualifier(name));
    return packageDotPackage(tab, base, Utilities.unqualify(name));
  }
  
  public static Type canonicalNameToPackageOrType(final SymbolTable tab,
      final List<File> paths, final String name, final boolean mayBeInUnnamedPackage) {
    final Type t = canonicalNameToType(tab, paths, name, mayBeInUnnamedPackage);
    return t != null ? t : canonicalNameToPackage(tab, name);
  }

  public static ClassOrInterfaceT canonicalNameToType(final SymbolTable tab,
      final List<File> paths, final String name, final boolean mayBeInUnnamedPackage) {
    if (name.indexOf('.') == -1) {
      if (mayBeInUnnamedPackage)
        return packageDotType(tab, paths, simpleNameToPackage(tab, ""), name);
      return null;
    }
    final String qualifier = Utilities.getQualifier(name);
    final String selector = Utilities.unqualify(name);
    if (qualifier.indexOf('.') == -1)
      return packageDotType(tab, paths, simpleNameToPackage(tab, qualifier), selector);
    final Type base = canonicalNameToPackageOrType(tab, paths, qualifier, mayBeInUnnamedPackage);
    if (base.isPackage())
      return packageDotType(tab, paths, base.toPackage(), selector);
    return typeDotType(tab, paths, (ClassOrInterfaceT) base, false, selector);
  }
  
  public static List<File> classpath(final Runtime runtime) {
    return runtime.getFileList(Runtime.INPUT_DIRECTORY);
  }
  
  public static boolean constructorsReturnVoid() { return true; }
    
  /** Can only create concrete subclass that implements all abstract methods if there
   * is no pair of abstract methods with the same signature, but different return types. */
  public static boolean couldCreateConcreteSubclass(final SymbolTable tab, final List<File> paths, final ClassT clazz) {
    final List<MethodT> abstractMethods = allAbstractMethods(tab, paths, clazz);
    for (final MethodT m : abstractMethods)
      resolveIfAliasMethod(tab, paths, m);
    for (final MethodT m1 : abstractMethods)
      for (final MethodT m2 : abstractMethods)
        if (m1.getName().equals(m2.getName()) && sameMethodSignature(m1, m2))
          if (!JavaTypeConverter.isIdentical(m1.getResult(), m2.getResult()))
            return false;
    return true;
  }

  public static List<Type> currentImports(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String n = s.getName();
      if (SymbolTable.isInNameSpace(n, "file"))
        return imports(tab, currentPackage(tab), SymbolTable.fromNameSpace(n));
    }
    return imports(tab, null, null);
  }
  
  public static MethodT currentMethod(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String name = s.getName();
      if (SymbolTable.isInNameSpace(name, "method")) {
        final ClassOrInterfaceT type = currentType(tab);
        for (final Type method : type.getMethods()) {
          assert method.isMethod();
          final String s2;
          assert method.hasScope(false);
          s2 = method.getScope();
          if (s.getQualifiedName().equals(s2))
            return method.toMethod();
        }
      }
    }
    return null;
  }
  
  public static PackageT currentPackage(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String n = s.getName();
      if (n.startsWith("package("))
        return canonicalNameToPackage(tab, SymbolTable.fromNameSpace(n));
    }
    return canonicalNameToPackage(tab, "");
  }
  
  public static ClassOrInterfaceT currentType(final SymbolTable tab) {
    for (SymbolTable.Scope s = tab.current(); !s.isRoot(); s = s.getParent()) {
      final String tagName = SymbolTable.toTagName(s.getName());
      final ClassOrInterfaceT result = (ClassOrInterfaceT)s.getParent().lookup(tagName);
      if (result != null)
        return result;
    }
    return null;
  }
  
  public static PackageT declaringPackage(final SymbolTable tab, final Type type) {
    if (type.isPackage())
      return (PackageT)type;
    if (type instanceof ClassOrInterfaceT && isTypeTopLevel((ClassOrInterfaceT)type)) {
      final String oldScope = enterScopeByQualifiedName(tab, typeToScopeName(type));
      final PackageT result = currentPackage(tab);
      enterScopeByQualifiedName(tab, oldScope);
      return result;
    }
    if (isTypeMember(type))
      return declaringPackage(tab, declaringType(tab, type));
    final String oldScope = enterScopeByQualifiedName(tab, declaringScopeName(type));
    final PackageT result = currentPackage(tab);
    enterScopeByQualifiedName(tab, oldScope);
    return result;
  }

  public static String declaringScopeName(final Type type) {
    assert !type.isAlias();
    final Type u = isConstantT(type) ? ((AnnotatedT)type).getType() : type;
    if (u.hasScope(false)) {
      final String ownScope = u.getScope();
      if (isLocalT(type) || isParameterT(type) || isFieldT(type))
        return ownScope;
      return Utilities.getQualifier(ownScope);
    }
    return null;
  }

  public static ClassOrInterfaceT declaringType(final SymbolTable tab, final Type member) {
    assert member.isMethod() || isFieldT(member)
        || isWrappedClassT(member) || isWrappedInterfaceT(member);
    final String declaringScope = declaringScopeName(member);
    assert null != declaringScope;
    assert isScopeForMember(declaringScope);
    final String oldScope = enterScopeByQualifiedName(tab, declaringScope);
    final ClassOrInterfaceT result = currentType(tab);
    assert null != result;
    enterScopeByQualifiedName(tab, oldScope);
    return result;
  }

  public static Type dereference(final Type generalLValue) {
    assert isGeneralLValueT(generalLValue);
    final WrappedT wrapped = isLValueT(generalLValue) ? (AnnotatedT) generalLValue
        : resolveToRawLValue(generalLValue);
    final Type result = wrapped.getType();
    assert isGeneralRValueT(result);
    return result;
  }

  public static List<ClassOrInterfaceT> directSuperTypes(final SymbolTable tab, final List<File> paths, final Type sub) {
    if (sub.isArray()) {
      final List<ClassOrInterfaceT> result = new ArrayList<ClassOrInterfaceT>();
      result.add(JavaEntities.tObject(tab));
      result.add(JavaEntities.tCloneable(tab));
      result.add(JavaEntities.tSerializable(tab));
      return result;
    }
    final ClassOrInterfaceT rawSub = JavaEntities.resolveToRawClassOrInterfaceT(sub);
    final List<AliasT> aliases = new ArrayList<AliasT>();
    if (JavaEntities.isWrappedClassT(sub)) {
      final Type sup = rawSub.toClass().getParent();
      if (null != sup)
        aliases.add(sup.toAlias());
    }
    for (final Type i : rawSub.getInterfaces())
      aliases.add(i.toAlias());
    final String scope = JavaEntities.typeToScopeName(sub);
    return JavaEntities.qualifiedAliasesToTypes(tab, paths, scope, aliases);
  }

  public static String enterScopeByQualifiedName(final SymbolTable tab,
      final String name) {
    final String oldScopeName = tab.current().getQualifiedName();
    assert null != name;
    tab.setScope(tab.getScope(name));
    return oldScopeName;
  }

  public static List<VariableT> fieldsApplicableAndAccessible(final SymbolTable tab, final List<File> paths,
      final Type base, final boolean parents, final String name) {
    final List<VariableT> fields = parents ? fieldsOwnAndInherited(tab, paths, base) : fieldsOwn(base);
    final List<VariableT> result = new ArrayList<VariableT>();
    for (final VariableT field : fields)
      if (isAccessibleIn(tab, paths, field, base))
        if (isApplicableField(tab, paths, field, name))
          result.add(field);
    return result;
  }
  
  public static List<VariableT> fieldsInherited(final SymbolTable tab, final List<File> paths,
      final Type base) {
    //gosling_et_al_2000 8.3 (before subsections)
    final List<VariableT> result = new ArrayList<VariableT>();
    final List<VariableT> fieldsOwn = fieldsOwn(base);
    final String baseScope = declaringScopeName(base);
    assert null != baseScope || base.isArray();
    final List<ClassOrInterfaceT> superTypes = directSuperTypes(tab, paths, base);
    for (final ClassOrInterfaceT superType : superTypes) {
      final List<VariableT> superFields = fieldsOwnAndInherited(tab, paths, superType);
      superFields: for (final VariableT f : superFields) {
        if (hasModifier(f, "private"))
          continue superFields;
        if (null != baseScope && !isAccessibleFromIn(tab, paths, baseScope, f, superType))
          continue superFields;
        for (final VariableT o : fieldsOwn)
          if (f.getName().equals(o.getName()))
            continue superFields;
        for (final VariableT r : result)
          if (f == r)
            continue superFields;
        result.add(f);
      }
    }
    return result;
  }
  
  public static List<VariableT> fieldsOwn(final Type base) {
    final List<VariableT> result = new ArrayList<VariableT>(1);
    if (base.isArray())
      result.add(arrayLengthField());
    else
      for (final Type f : resolveToRawClassOrInterfaceT(base).getFields())
        result.add(f.toVariable());
    return result;
  }

  public static List<VariableT> fieldsOwnAndInherited(final SymbolTable tab, final List<File> paths,
      final Type base) {
    final List<VariableT> result = new ArrayList<VariableT>();
    result.addAll(fieldsInherited(tab, paths, base));
    result.addAll(fieldsOwn(base));
    return result;
  }

  public static String fileNameToScopeName(final String absolutePath) {
    return SymbolTable.toNameSpace(absolutePath, "file");
  }

  /** Does the class or one of its superclasses declare any abstract methods
   * that have not been implemented here or in a superclass? (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#34944">&sect;8.1.1</a>). */
  public static boolean hasAbstractMethods(final SymbolTable tab,
      final List<File> paths, final ClassT clazz) {
    return !allAbstractMethods(tab, paths, clazz).isEmpty();
  }

  /** Does the class depend on itself by inheritance or by nesting? (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#262560">&sect;8.1.3</a>). */
  public static boolean hasCircularDependency(final SymbolTable tab,
      final List<File> paths, final ClassOrInterfaceT type) {
    final Iterator<Type> iSup = new SuperTypesIter(tab, paths, type, false);
    while (iSup.hasNext()) {
      Type t = iSup.next();
      inner: while (true) {
        if (JavaTypeConverter.isIdentical(type, t))
          return true;
        if (!isTypeMember(t))
          break inner;
        t = declaringType(tab, t);
      }
    }
    return false;
  }

  public static boolean hasModifier(final Type t, final String m) {
    final Type u = t.isAlias() ? ((AliasT) t).getType() : t;
    assert isGeneralLValueT(u) || u.isMethod() || u.isClass() || u.isInterface();
    return u.hasAttribute(nameToModifier(m), false);
  }

  static List<Type> imports(final SymbolTable tab, final PackageT packageT, final String fileName) {
    final String baseScope = null == packageT ? "" : scopeName(packageT, fileName);
    final Object o = tab.lookup(Utilities.qualify(baseScope, "imports(*)"));
    if (null == o)
      return new ArrayList<Type>();
    if (o instanceof List)
      return typeList((List)o);
    final ArrayList<Type> list = new ArrayList<Type>();
    list.add((Type)o);
    return list;
  }

  /** Is it allowed to use the entity from the current scope of the symbol table (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/names.doc.html#104285">&sect;6.6</a>)? */
  public static boolean isAccessible(final SymbolTable tab, final List<File> paths, final Type entity) {
    return isAccessibleIn(tab, paths, entity, null);
  }

  public static boolean isAccessibleFromIn(final SymbolTable tab, final List<File> paths, final String scope, final Type entity, final Type inType) {
    final String oldScope = JavaEntities.enterScopeByQualifiedName(tab, scope);
    final boolean result = isAccessibleIn(tab, paths, entity, inType);
    JavaEntities.enterScopeByQualifiedName(tab, oldScope);
    return result;
  }

  public static boolean isAccessibleIn(final SymbolTable tab, final List<File> paths, final Type entity, final Type inType) {
    if (entity.isArray())
      return true;
    if (entity.isAlias())
      return isAccessible(tab, paths, ((AliasT)entity).getType());
    if (entity.isPackage())
      return true;
    final boolean samePackage = declaringPackage(tab, entity).getName().equals(currentPackage(tab).getName());
    if (isWrappedClassT(entity) || isWrappedInterfaceT(entity)) {
      if (hasModifier(entity, "public"))
        return true;
      if (isTypeTopLevel((ClassOrInterfaceT)entity))
        return samePackage;
    }
    if (!isTypeMember(entity))
      return true;
    final Type base = null == inType ? declaringType(tab, entity) : inType;
    assert null != base;
    if (!isAccessible(tab, paths, base))
      return false;
    if (hasModifier(entity, "public"))
      return true;
    if (hasModifier(entity, "protected")) {
      if (samePackage)
        return true;
      if (entity.isMethod() && isConstructor(base, entity.toMethod())) {
        return false; //TD 36 (6.6.2) isAccessibleIn() for protected constructors in different package
      } else {
        final Type decl = declaringType(tab, entity), curr = currentType(tab);
        return (null == curr || isSuperClass(tab, paths, decl, curr)) && isSuperClass(tab, paths, decl, base);
      }
    }
    if (hasModifier(entity, "private")) {
      final Type top;
      final String oldScope = enterScopeByQualifiedName(tab, typeToScopeName(base));
      while (true) {
        final ClassOrInterfaceT t = JavaEntities.currentType(tab);
        enterScopeByQualifiedName(tab, typeToScopeName(t));
        if (isTypeTopLevel(t)) {
          top = t;
          break;
        }
        tab.exit();
      }
      enterScopeByQualifiedName(tab, oldScope);
      return tab.current().getQualifiedName().startsWith(typeToScopeName(top));
    }
    return samePackage;
  }

  public static boolean isApplicableField(final SymbolTable tab, final List<File> paths, final VariableT field, final String name) {
    if (name.equals(field.getName())) {
      final ClassOrInterfaceT declaringType = declaringType(tab, field);
      resolveIfAlias(tab, paths, typeToScopeName(declaringType), field.getType());
      return true;
    }
    return false;
  }

  public static boolean isApplicableMemberType(final Type memberType, final String name) {
    final ClassOrInterfaceT raw = resolveToRawClassOrInterfaceT(memberType);
    return name.equals(raw.getName());
  }

  public static boolean isApplicableMethod(final SymbolTable tab, final List<File> paths,
      final MethodT callee, final String name, final List<Type> actuals) {
    if (!callee.getName().equals(name))
      return false;
    final List<Type> formals = callee.getParameters();
    if (formals.size() != actuals.size())
      return false;
    final ClassOrInterfaceT declaringType = declaringType(tab, callee);
    final String aScope = tab.current().getQualifiedName();
    final Iterator<Type> iF = formals.iterator(), iA = actuals.iterator();
    while (iF.hasNext()) {
      final Type formal = iF.next();
      resolveIfAlias(tab, paths, typeToScopeName(declaringType), dereference(formal));
      final Type aAlias = iA.next();
      final Type actual = resolveIfAlias(tab, paths, aScope, aAlias);
      final boolean conv = JavaTypeConverter.isParameterPassable(tab,
          paths, dereference(formal), actual);
      if (!conv)
        return false;
    }
    return true;
  }
  
  public static boolean isCheckedException(final SymbolTable tab, final List<File> paths, final Type exc) {
    // gosling_et_al_2000 11.2
    return isSuperClass(tab, paths, tThrowable(tab), exc)
        && !isSuperClass(tab, paths, tRuntimeException(tab), exc)
        && !isSuperClass(tab, paths, tError(tab), exc);
  }
  
  public static boolean isConstantT(final Type t) {
    return (null != t) && t.isAnnotated() && t.hasConstant(false);
  }

  public static boolean isConstructor(final Type declaringType, final MethodT maybeConstructor) {
    if (!declaringType.isClass())
      return false;
    return declaringType.toClass().getName().equals(maybeConstructor.getName());
  }
  
  /** ExpressionT &gt; GeneralLValueT, GeneralRValueT. */
  public static boolean isExpressionT(final Type t) {
    return isGeneralLValueT(t) || isGeneralRValueT(t);
  }

  /** FieldT = Name WrappedRValueT. */
  public static boolean isFieldT(final Type t) {
    return t.isVariable() && VariableT.Kind.FIELD == t.toVariable().getKind();
  }
  
  /** GeneralLValueT &gt; LValueT, VariableT, FieldT, ParameterT. */
  public static boolean isGeneralLValueT(final Type t) {
    return isLValueT(t) || isLocalT(t) || isFieldT(t) || isParameterT(t);
  }
  
  /** GeneralRValueT &gt; NullT, WrappedRValueT. */
  public static boolean isGeneralRValueT(final Type t) {
    return isNullT(t) || isWrappedRValueT(t);
  }
  
  public static boolean isInLocalNameSpace(final String name) {
    final String lastPart = Utilities.unqualify(name);
    return SymbolTable.isInNameSpace(lastPart, "method")
        || SymbolTable.isInNameSpace(lastPart, "block")
        || SymbolTable.isInNameSpace(lastPart, "forStatement")
        || SymbolTable.isInNameSpace(lastPart, "labeledStatement")
        || SymbolTable.isInNameSpace(lastPart, "function") //in Jeannie, not in Java
        || SymbolTable.isInNameSpace(lastPart, "withStatement") //in Jeannie, not in Java
        || SymbolTable.isInNameSpace(lastPart, "matchClause") //in Matchete, not in Java
        || SymbolTable.isInNameSpace(lastPart, "catchClause");
  }

  public static boolean isInt(final Type t) {
    final Type n = JavaTypeConverter.promoteUnaryNumeric(t);
    if (null == n)
      return false;
    final Type r = resolveToRawRValue(n);
    return r.isInteger() && NumberT.Kind.INT == ((IntegerT)r).getKind();
  }
  
  /** LocalT = Name WrappedRValueT. */
  public static boolean isLocalT(final Type t) {
    return t.isVariable() && VariableT.Kind.LOCAL == t.toVariable().getKind();
  }
  
  /** LValueT = RValueT. */
  public static boolean isLValueT(final Type t) {
    return (null != t) && t.isAnnotated() && t.hasShape(false);
  }

  /** NotAValueT &gt; PackageT, AnnotatedT:ReturnT --- annotated with Constants.ATT_NOT_A_VALUE */
  public static boolean isNotAValueT(final Type t) {
    return t.isPackage() || 
      t instanceof AnnotatedT && t.hasAttribute(Constants.ATT_NOT_A_VALUE) && isReturnT(((AnnotatedT)t).getType());
  }

  /** NullT = ConstantT:VoidT. */
  public static boolean isNullT(final Type t) {
    return isConstantT(t) && ((AnnotatedT)t).getType().isVoid();
  }

  /** ParameterT = Name RValueT. */
  public static boolean isParameterT(final Type t) {
    return t.isVariable() && VariableT.Kind.PARAMETER == t.toVariable().getKind();
  }
  
  /** PrimitiveT &gt; BooleanT, NumberT. */
  public static boolean isPrimitiveT(final Type t) {
    return t.isBoolean() || t.isNumber();
  }
  
  /** Is t a class, interface, or array type (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/typesValues.doc.html#9317">&sect;4.3</a>)?  */
  public static boolean isReferenceT(final Type t) {
    if (isNullT(t))
      return true;
    final Type u = isConstantT(t) ? ((AnnotatedT)t).getType() : t;
    return u.isArray() || isWrappedClassT(u) || isWrappedInterfaceT(u);
  }

  /** ReturnT &gt; VoidT, RValueT. */
  public static boolean isReturnT(final Type t) {
    return t.isVoid() || isRValueT(t);
  }

  /** RValueT &gt; PrimitiveT, ArrayT, WrappedClassT, WrappedInterfaceT. */
  public static boolean isRValueT(final Type t) {
    return isPrimitiveT(t) || t.isArray() || isWrappedClassT(t) || isWrappedInterfaceT(t);
  }
  
  public static boolean isScopeForMember(final String scopeName) {
    // gosling_et_al_2000 8.5, 9.5
    return isScopeNested(scopeName) && !isInLocalNameSpace(scopeName);
  }

  public static boolean isScopeLocal(final String scopeName) {
    //gosling_et_al_2000 14.3
    return isInLocalNameSpace(scopeName);
  }

  public static boolean isScopeNested(final String scopeName) {
    //gosling_et_al_2000 intro paragraph to chapters 8 and 9
    if (isScopeTopLevel(scopeName))
      return false;
    return 3 < Utilities.toComponents(scopeName).length;
  }

  public static boolean isScopeTopLevel(final String scopeName) {
    //gosling_et_al_2000 7.6
    if (null == scopeName)
      System.out.println("hohoho");
    assert null != scopeName;
    if ("".equals(scopeName) || ".".equals(scopeName))
      return true; //top-level in C file
    final String[] scopeParts = Utilities.toComponents(scopeName);
    if (0 < scopeParts.length)
      assert "".equals(scopeParts[0]);
    if (2 < scopeParts.length && SymbolTable.isInNameSpace(scopeParts[1], "package")) {
	  assert SymbolTable.isInNameSpace(scopeParts[2], "file");
      return 3 == scopeParts.length; //top-level in Java file
    }
    return false;
  }  

  public static boolean isSuperClass(final SymbolTable tab, final List<File> paths,
      final Type sup, final Type sub) {
    if (!isWrappedClassT(sub) || !isWrappedClassT(sup))
      return false;
    return JavaTypeConverter.isIdentical(sup, sub)
        || JavaTypeConverter.isWiderReference(tab, paths, sup, sub);
  }
  
  /** Note: not symmetric! */
  public static boolean isSuperMethod(final SymbolTable tab, final List<File> paths,
      final MethodT sup, final MethodT sub) {
    if (!sub.getName().equals(sup.getName()))
      return false;
    if (sub.getParameters().size() != sup.getParameters().size())
      return false;
    if (hasModifier(sup, "private"))
      return false;
    final ClassOrInterfaceT dSup = declaringType(tab, sup), dSub = declaringType(tab, sub);
    if (!isAccessibleFromIn(tab, paths, typeToScopeName(dSub), sup, dSup))
      return false;
    if (!JavaTypeConverter.isParameterPassable(tab, paths, dSup, dSub))
      return false;
    final Iterator<Type> iSub = sub.getParameters().iterator();
    final Iterator<Type> iSup = sup.getParameters().iterator();
    while (iSub.hasNext()) {
      final VariableT tSup = iSup.next().toVariable(), tSub = iSub.next().toVariable();
      final Type rSup = tSup.getType(), rSub = tSub.getType();
      resolveIfAlias(tab, paths, declaringScopeName(sup), rSup);
      resolveIfAlias(tab, paths, declaringScopeName(sub), rSub);
      if (!JavaTypeConverter.isParameterPassable(tab, paths, rSup, rSub))
        return false;
    }
    if (JavaTypeConverter.isIdentical(dSup, dSub) && sameMethodSignature(sup, sub)) {
      //Java 1.5 introduces contravariant return types, and we must tackle them in libraries, such as StringBuffer
      final Type tSup = sup.getResult(), tSub = sub.getResult();
      resolveIfAlias(tab, paths, declaringScopeName(sup), tSup);
      resolveIfAlias(tab, paths, declaringScopeName(sub), tSub);
      if (!JavaTypeConverter.isReturnTypeSubstitutable(tab, paths, tSup, tSub))
        return false;
    }
    return true;
  }

  public static boolean isTypeAnonymous(final ClassOrInterfaceT t) {
    return t.isClass() && null == t.toClass().getName();
  }
  
  public static boolean isTypeInner(final ClassOrInterfaceT t) {
    // gosling_et_al_2000 8.1.2
    return !hasModifier(t, "static") && isTypeNested(t);
  }

  public static boolean isTypeLocal(final ClassOrInterfaceT t) {
    // gosling_et_al_2000 14.3
    return isScopeLocal(declaringScopeName(t)) && !isTypeAnonymous(t);
  }

  public static boolean isTypeMember(final Type t) {
    return isScopeForMember(declaringScopeName(t));
  }

  public static boolean isTypeNamed(final ClassOrInterfaceT t) {
    return !isTypeAnonymous(t);
  }

  public static boolean isTypeNested(final ClassOrInterfaceT t) {
    final String scope = declaringScopeName(t);
    assert null != scope;
    return isScopeNested(scope);
  }
  
  public static boolean isTypeTopLevel(final ClassOrInterfaceT t) {
    return isScopeTopLevel(declaringScopeName(t));
  }
  
  /** WrappedClassT = AliasT:Name / AliasT:ResolvedClassT / ResolvedClassT. */
  public static boolean isWrappedClassT(final Type t) {
    if (t.isAlias()) {
      final Type r = ((AliasT) t).getType();
      return null == r || r.isClass();
    }
    return t.isClass();
  }

  /** WrappedInterfaceT = AliasT:Name / AliasT:ResolvedInterfaceT / ResolvedInterfaceT. */
  public static boolean isWrappedInterfaceT(final Type t) {
    if (t.isAlias()) {
      final Type r = ((AliasT) t).getType();
      return null == r || r.isInterface();
    }
    return t.isInterface();
  }

  /** WrappedRValueT = ConstantT:RValueT / RValueT. */
  public static boolean isWrappedRValueT(final Type t) {
    return isConstantT(t) && isRValueT(((AnnotatedT)t).getType()) || isRValueT(t);
  }

  public static String javaAstToString(final Node ast) {
    final CharArrayWriter writer = new CharArrayWriter();
    final JavaPrinter printer = new JavaPrinter(new Printer(writer));
    printer.dispatch(ast);
    return writer.toString();
  }

  /**
   * Don't use this method gratuitously. Originally, I used this to serialize
   * ASTs into strings, then concatenated the strings into more code, then
   * reparsed the result to a larger AST. But that is slow and less elegant
   * than using FactoryFactory.
   */
  private static GNode javaStringToAst(final String production, final String code) {
    try {
      return JavaEntities.javaStringToAst(production, code, true);
    } catch (final Exception e) {
      throw new Error(e);
    }
  }
  
  public static GNode javaStringToAst(final String production,
      final String escaped, final boolean simple) throws Exception {
    final Method method = JavaParser.class.getDeclaredMethod("p" + production, Integer.TYPE);
    method.setAccessible(true);
    final String string = unicodeUnescape(escaped);
    final JavaParser parser = new JavaParser( //
        new StringReader(string), "<input>", string.length());
    final Object[] paramValues = { new Integer(0) };
    final Result parseResult = (Result) method.invoke(parser, paramValues);
    if (! parseResult.hasValue()) parser.signal(parseResult.parseError());
    if (parseResult.index != string.length())
      throw new ParseException("input not fully consumed");
    final GNode ast = (GNode) parseResult.semanticValue();
    if (simple)
      return (GNode) new JavaAstSimplifier().dispatch(ast);
    return ast;
  }

  public static Type javaStringToType(final String code) {
    final SymbolTable tab = new SymbolTable();
    JavaUnitTests.enterPackageFile(tab, "", "<input>");
    return javaStringToType(code, tab);
  }

  private static Type javaStringToType(final String code, final SymbolTable tab) {
    final GNode ast = JavaEntities.javaStringToAst("Type", code);
    final JavaAnalyzer ana = new JavaAnalyzer(JavaUnitTests.newRuntime(), tab);
    final Type result = (Type) ana.dispatch(ast);
    return result;
  }
  
  public static GNode javaTypeToAst(final SymbolTable tab, final Type type) {
    final String s = JavaEntities.javaTypeToString(tab, type);
    final GNode result = JavaEntities.javaStringToAst("ResultType", s);
    return scrubLocations(result);
  }

  public static String javaTypeToString(final SymbolTable tab, final Type type) {
    if (JavaEntities.isGeneralRValueT(type)) {
      final Type r = JavaEntities.resolveToRawRValue(type);
      return JavaEntities.typeToString(tab, false, r);
    }
    return JavaEntities.typeToString(tab, false, type);
  }
  
  /**
   * Resolve single-type import. The name is canonical (gosling_et_al_2000
   * Section 7.5.1) and denotes a class or interface. The only thing that is
   * uncertain is where the package ends and where the nested types start. For
   * example, in a.b.c, it could be that the package is a.b and the class is c,
   * or that the package is a, the outer class is b, and the inner class is c.
   * There can be no ambiguity (gosling_et_al_2000 Section 6.4), because a
   * package must not have a top-level type and a subpackage of the same name.
   */
  static ClassOrInterfaceT lookupImport(final SymbolTable tab, final List<File> paths, final AliasT alias) {
    return canonicalAliasToType(tab, paths, alias, false);
  }

  public static List<Type> memberTypesApplicableAndAccessible(final SymbolTable tab, final List<File> paths,
      final ClassOrInterfaceT base, final boolean parents, final String name) {
    final List<Type> memberTypes = parents ? memberTypesOwnAndInherited(tab, paths, base) : memberTypesOwn(tab, paths, base);
    final List<Type> result = new ArrayList<Type>();
    for (final Type memberType : memberTypes)
      if (isAccessibleIn(tab, paths, memberType, base))
        if (isApplicableMemberType(memberType, name))
          result.add(memberType);
    return result;
  }

  public static List<Type> memberTypesInherited(final SymbolTable tab, final List<File> paths, final ClassOrInterfaceT base) {
    //gosling_et_al_2000 8.5 (before subsections)
    final List<Type> result = new ArrayList<Type>();
    final List<Type> memberTypesOwn = memberTypesOwn(tab, paths, base);
    final String baseScope = declaringScopeName(base);
    assert null != baseScope || base.isArray();
    final List<ClassOrInterfaceT> superTypes = directSuperTypes(tab, paths, base);
    for (final ClassOrInterfaceT superType : superTypes) {
      final List<Type> superMemberTypes = memberTypesOwnAndInherited(tab, paths, superType);
      superMemberTypes: for (final Type t : superMemberTypes) {
        //the private and accessible checks are here for consistency with fieldsInherited, the specification doesn't explicitly mention them
        if (hasModifier(t, "private"))
          continue superMemberTypes;
        if (null != baseScope && !isAccessibleFromIn(tab, paths, baseScope, t, superType))
          continue superMemberTypes;
        final String tName = resolveToRawClassOrInterfaceT(t).getName();
        for (final Type o : memberTypesOwn)
          if (tName.equals(resolveToRawClassOrInterfaceT(o).getName()))
            continue superMemberTypes;
        for (final Type r : result)
          if (t == r)
            continue superMemberTypes;
        result.add(t);
      }
    }
    return result;
  }

  public static List<Type> memberTypesOwn(final SymbolTable tab, final List<File> paths, final ClassOrInterfaceT base) {
    if (base.isArray())
      return new ArrayList<Type>(0);
    final Scope scope = tab.getScope(typeToScopeName(base));
    final List<Type> result = new ArrayList<Type>();
    for (final Iterator<String> i = scope.symbols(); i.hasNext();) {
      final String symbol = i.next();
      final Type member = (Type)scope.lookupLocally(symbol);
      if (isWrappedClassT(member) || isWrappedInterfaceT(member))
        result.add(member);
    }
    return result;
  }

  public static List<Type> memberTypesOwnAndInherited(final SymbolTable tab, final List<File> paths, final ClassOrInterfaceT base) {
    final List<Type> result = new ArrayList<Type>();
    result.addAll(memberTypesInherited(tab, paths, base));
    result.addAll(memberTypesOwn(tab, paths, base));
    return result;
  }

  /** All methods in the base type that are accessible, and whose formals accept the actuals
   * after method invocation conversion (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#18427">&sect;15.12.2.1</a>). */
  public static List<MethodT> methodsApplicableAndAccessible(final SymbolTable tab, final List<File> paths,
      final Type base, final boolean parents, final String name,
      final List<Type> actuals) {
    final List<MethodT> methods = parents ? methodsOwnAndInherited(tab, paths, base) : methodsOwn(base);
    final List<MethodT> result = new ArrayList<MethodT>();
    for (final MethodT method : methods)
      if (isAccessibleIn(tab, paths, method, base))
        if (isApplicableMethod(tab, paths, method, name, actuals))
          result.add(method);
    return result;
  }

  public static List<MethodT> methodsInherited(final SymbolTable tab, final List<File> paths, final Type base, final boolean includeOverridden) {
    //gosling_et_al_2000 8.4.6
    List<MethodT> result = new ArrayList<MethodT>();
    final List<MethodT> methodsOwn = methodsOwn(base);
    final String baseScope = typeToScopeName(base); //declaringScopeName(base);
    assert null != baseScope || base.isArray();
    final List<ClassOrInterfaceT> superTypes = directSuperTypes(tab, paths, base);
    for (final ClassOrInterfaceT superType : superTypes) {
      final List<MethodT> superMethods = methodsOwnAndInherited(tab, paths, superType);
      superMethods: for (final MethodT m : superMethods) {
        resolveIfAliasMethod(tab, paths, m);
        if (hasModifier(m, "private"))
          continue superMethods;
        if (null != baseScope && !isAccessibleFromIn(tab, paths, baseScope, m, superType))
          continue superMethods;
        if (!includeOverridden)
          for (final MethodT o : methodsOwn) {
            resolveIfAliasMethod(tab, paths, o);
            if (sameMethodSignature(o, m))
              continue superMethods;
          }
        boolean mustRemoveDuplicates = false;
        for (final MethodT r : result) {
          if (r == m)
            continue superMethods; //inherited from same interface by two different paths
          if (sameMethodSignature(m, r)) { 
            assert hasModifier(m, "abstract") || hasModifier(r, "abstract");
            if (hasModifier(m, "abstract") && hasModifier(r, "abstract")) {
              //TD 39 (8.4.6) report error if incompatible return types
            } else if (!hasModifier(m, "abstract")) {
              mustRemoveDuplicates = true;
            } else if (!hasModifier(r, "abstract")) {
              //TD 39 (8.4.6) report error if r is static
              continue superMethods;
            }
          }
        }
        result.add(m);
        if (mustRemoveDuplicates) {
          //TD 39 (8.4.6) report error if m is static
          final List<MethodT> oldResult = result;
          result = new ArrayList<MethodT>();
          for (final MethodT r : oldResult)
            if (r == m || !sameMethodSignature(r, m))
              result.add(r);
        }
      }
    }
    return result;
  }

  public static List<MethodT> methodsOwn(final Type base) {
    final List<MethodT> result = new ArrayList<MethodT>();
    if (!base.isArray()) //TD should methodsOwn() list of array type be non-empty?
      for (final Type m : resolveToRawClassOrInterfaceT(base).getMethods())
        result.add(m.toMethod());
    return result; 
  }
  
  public static List<MethodT> methodsOwnAndInherited(final SymbolTable tab, final List<File> paths,
      final Type base) {
    final List<MethodT> result = new ArrayList<MethodT>();
    result.addAll(methodsInherited(tab, paths, base, false));
    result.addAll(methodsOwn(base));
    return result;
  }
  
  public static String methodSymbolFromAst(final GNode ast) {
    final String name = ast.getString(3);
    final String args = javaAstToString(ast.getGeneric(4));
    /* In general, the arguments are unresolved, hence the scope name
     * is not canonical, hence it is useless for future lookup. That
     * is fine as long as we never look up methods or their scopes by
     * name. Instead, we should rely on the SCOPE attribute for that. */
    return "method(" + name + ")" + args;
  }

  public static String methodSymbolFromConstructor(final Constructor method) {
    final StringBuilder result = new StringBuilder();
    result.append("method(<init>)");
    methodSymbolHelper(result, method.getParameterTypes());
    return result.toString();
  }

  public static String methodSymbolFromMethod(final Method method) {
    final StringBuilder result = new StringBuilder();
    result.append("method(").append(method.getName()).append(")");
    methodSymbolHelper(result, method.getParameterTypes());
    return result.toString();
  }

  private static void methodSymbolHelper(final StringBuilder b, final Class[] t) {
    b.append('(');
    for (int i = 0; i < t.length; i++) {
      if (0 < i)
        b.append(',');
      b.append(t[i].getName());
    }
    b.append(')');
  }

  public static String modifiersToString(final Type type) {
    final StringBuilder result = new StringBuilder();
    for (final Attribute att : type.attributes()) {
      if (0 < result.length())
        result.append(' ');
      result.append(modifierToName(att));
    }
    return result.toString();
  }

  public static String modifierToName(final Attribute modifier) {
    return MODIFIER_TO_NAME.get(modifier);
  }

  private static List<MethodT> mostSpecificMethods(final SymbolTable tab,
      final List<File> paths, final List<MethodT> allMethods) {
    final List<MethodT> result = new ArrayList<MethodT>();
    outer: for (final MethodT mOuter : allMethods) {
      for (final MethodT mInner : allMethods)
        if (mOuter != mInner && isSuperMethod(tab, paths, mOuter, mInner))
          continue outer;
      result.add(mOuter);
    }
    return result;
  }

  public static Type nameToBaseType(final String name) {
    return NAME_TO_BASETYPE.get(name);
  }
  
  public static Attribute nameToModifier(final String name) {
    final Attribute result = NAME_TO_MODIFIER.get(name);
    assert null != result;
    return result;
  }
  
  public static MethodT newRawConstructor(final Type base, final List<Type> formals, final List<Type> exceptions) {
    return new MethodT(constructorsReturnVoid() ? nameToBaseType("void") : base, typeToSimpleName(base), formals, false, exceptions);
  }

  public static Type notAValueIfClassOrInterface(final Type t) {
    if (null == t)
      return t;
    if (isWrappedClassT(t) || isWrappedInterfaceT(t)) {
      final Type result = new AnnotatedT(t);
      /* don't call t.attribute(), because that would pollute aliases of t */
      return result.attribute(Constants.ATT_NOT_A_VALUE);
    }
    return t;
  }

  public static PackageT packageDotPackage(final SymbolTable tab,
      final PackageT base, final String selector) {
    final String tagName = SymbolTable.toTagName(selector);
    final String scopeName = packageNameToScopeName(base.getName());
    final String symbol = "." + Utilities.qualify(scopeName, tagName);
    PackageT result = (PackageT) tab.lookup(symbol);
    if (result == null) {
      result = new PackageT(Utilities.qualify(base.getName(), selector));
      SymbolTable.Scope scope = tab.lookupScope(symbol);
      if (scope == null) {
        final SymbolTable.Scope oldScope = tab.current();
        tab.setScope(tab.root());
        tab.enter(packageNameToScopeName(base.getName()));
        scope = tab.current();
        tab.setScope(oldScope);
      }
      scope.define(tagName, result);
    }
    return result;
  }
  
  public static Type packageDotPackageOrType(final SymbolTable tab,
      final List<File> paths, final PackageT base, final String selector) {
    final Type t = packageDotType(tab, paths, base, selector);
    return t != null ? t : packageDotPackage(tab, base, selector);
  }

  static ClassOrInterfaceT packageDotType(final SymbolTable tab, final List<File> paths, final PackageT base, final String selector) {
    assert null != base;
    final ClassOrInterfaceT t1 = packageDotType_existing(tab, base, selector);
    if (null != t1)
      return t1;
    final ClassOrInterfaceT t2 = packageDotType_external(tab, paths, base, selector);
    if (null != t2)
      return t2;
    return packageDotType_noSource(tab, base, selector);
  }

  private static ClassOrInterfaceT packageDotType_existing(final SymbolTable tab, final PackageT base, final String selector) {
    final String tagName = SymbolTable.toTagName(selector);
    final String baseScopeName = "." + packageNameToScopeName(base.getName());
    final SymbolTable.Scope scope = tab.getScope(baseScopeName);
    if (scope != null)
      for (final Iterator<String> i = scope.nested(); i.hasNext();) {
        final String symbol = baseScopeName + "." + i.next() + "." + tagName;
        final Type result = (Type) tab.lookup(symbol);
        if (result != null && !result.isAlias())
          return (ClassOrInterfaceT) result;
      }
    return null;
  }
  
  private static ClassOrInterfaceT packageDotType_external(final SymbolTable tab, final List<File> paths, final PackageT base, final String selector) {
    final String tagName = SymbolTable.toTagName(selector);
    final String suffix = File.separatorChar + Utilities.toPath(base.getName()) + File.separatorChar + selector + ".java";
    for (final File prefix : paths) {
      try {
        final File file = new File(prefix, suffix);
        final String path = file.getAbsolutePath();
        if (file.exists()) {
          final String scopedName = scopeName(base, path) + "." + tagName;
          if (null == tab.lookupScope(scopedName)) {
            final String oldScope = enterScopeByQualifiedName(tab, "");
            FileReader fileReader = null;
            try {
              fileReader = new FileReader(file);
              final UnicodeUnescaper unescaper = new UnicodeUnescaper(fileReader);
              final JavaParser parser = new JavaParser(unescaper, path);
              final Result parseResult = parser.pCompilationUnit(0);
              if (parseResult.hasValue()) {
                final GNode ast = (GNode) parseResult.semanticValue();
                final GNode simple = (GNode) new JavaAstSimplifier().dispatch(ast);
                new JavaExternalAnalyzer(new Runtime(), tab).dispatch(simple);
              }
            } finally {
              if (null != fileReader)
                fileReader.close();
            }
            enterScopeByQualifiedName(tab, oldScope);
          }
          final ClassOrInterfaceT result = (ClassOrInterfaceT) tab.lookup(scopedName);
          if (result != null)
            return result;
        }
      } catch (final IOException e) {
        e.printStackTrace();
      }
    }
    return null;
  }
  
  static ClassOrInterfaceT packageDotType_noSource(final SymbolTable tab, final PackageT base, final String selector) {
    final String scopedName = "." + packageNameToScopeName(base.getName()) + ".file()." + SymbolTable.toTagName(selector);
    if (null == tab.lookup(scopedName)) {
      final Class clazz;
      try {
        clazz = Class.forName(base.getName() + "." + selector);
      } catch (final ClassNotFoundException e) {
        return null;
      }
      if (base.getName().equals(clazz.getPackage().getName())) {
        final String oldScope = enterScopeByQualifiedName(tab, "");
        tab.enter(packageNameToScopeName(base.getName()));
        tab.enter("file()");
        new JavaNoSourceAnalyzer(tab).visitClassOrInterface(clazz);
        enterScopeByQualifiedName(tab, oldScope);
      }
    }
    return (ClassOrInterfaceT) tab.lookup(scopedName);
  }
  
  public static String packageNameToScopeName(final String canonicalName) {
    return SymbolTable.toNameSpace(canonicalName, "package");
  }

  public static String qNameWithDollars(final SymbolTable tab, final ClassOrInterfaceT t) {
    final String allDots = t.getQName();
    if (null == tab)
      return allDots;
    final String packageName = declaringPackage(tab, t).getName();
    if (0 == packageName.length())
      return allDots;
    assert allDots.startsWith(packageName);
    final String afterPackage = allDots.substring(packageName.length() + 1).replace('.', '$');
    final String result = packageName + "." + afterPackage;
    return result;
  }
  
  public static List<ClassOrInterfaceT> qualifiedAliasesToTypes(final SymbolTable tab, final List<File> paths, final String scope, final List<AliasT> aliases) {
    final List<ClassOrInterfaceT> result = new ArrayList<ClassOrInterfaceT>(aliases.size());
    for (final AliasT a : aliases) {
      final ClassOrInterfaceT resolved = JavaEntities.qualifiedAliasToType(tab, paths, scope, a);
      if (null != resolved)
        result.add(resolved);
    }
    return result;
  }

  public static ClassOrInterfaceT qualifiedAliasToType(final SymbolTable tab,
      final List<File> paths, final String scope, final AliasT alias) {
    if (alias.getType() == null)
      alias.setType(qualifiedNameToType(tab, paths, scope, alias.getName()));
    return (ClassOrInterfaceT) alias.getType();
  }

  public static Type qualifiedNameToPackageOrType(final SymbolTable tab,
      final List<File> paths, final String scope, final String name) {
    final Type t = qualifiedNameToType(tab, paths, scope, name);
    return t != null ? t : canonicalNameToPackage(tab, name);
  }

  public static ClassOrInterfaceT qualifiedNameToType(final SymbolTable tab,
      final List<File> paths, final String scope, final String name) {
    if (name.indexOf('.') == -1)
      return simpleNameToType(tab, paths, scope, name);
    final String qualifier = Utilities.getQualifier(name);
    final String selector = Utilities.unqualify(name);
    final Type base = qualifiedNameToPackageOrType(tab, paths, scope, qualifier);
    if (base.isPackage())
      return packageDotType(tab, paths, base.toPackage(), selector);
    return typeDotType(tab, paths, (ClassOrInterfaceT)base, true, selector);
  }

  public static Type resolveIfAlias(final SymbolTable tab, final List<File> paths,
      final String scope, final Type typeThatMayBeAlias) {
    assert null != scope;
    if (null == typeThatMayBeAlias)
      return null;
    if (isGeneralLValueT(typeThatMayBeAlias)) {
      final Type t = dereference(typeThatMayBeAlias);
      resolveIfAlias(tab, paths, scope, t);
      return typeThatMayBeAlias;
    }
    if (typeThatMayBeAlias.isAnnotated()) {
      final Type t = ((AnnotatedT) typeThatMayBeAlias).getType();
      resolveIfAlias(tab, paths, scope, t);
      return typeThatMayBeAlias;
    }
    if (typeThatMayBeAlias.isArray()) {
      final Type t = arrayElementType(typeThatMayBeAlias.toArray());
      resolveIfAlias(tab, paths, scope, t);
      return typeThatMayBeAlias;
    }
    if (typeThatMayBeAlias.isAlias())
      return qualifiedAliasToType(tab, paths, scope, typeThatMayBeAlias.toAlias());
    return typeThatMayBeAlias;
  }

  public static MethodT resolveIfAliasMethod(final SymbolTable tab, final List<File> paths, final MethodT method) {
    final String scope = declaringScopeName(method);
    assert null != scope;
    resolveIfAlias(tab, paths, scope, declaringType(tab, method));
    resolveIfAlias(tab, paths, scope, method.getResult());
    for (final Type p : method.getParameters())
      resolveIfAlias(tab, paths, scope, p);
    for (final Type e : method.getExceptions())
      resolveIfAlias(tab, paths, scope, e);
    return method;
  }

  static ClassOrInterfaceT resolveToRawClassOrInterfaceT(final Type t) {
    return (ClassOrInterfaceT) resolveToRawRValue(t);
  }

  public static WrappedT resolveToRawLValue(final Type t) {
    assert isGeneralLValueT(t);
    final boolean a = t.isAnnotated();
    final WrappedT r = (WrappedT) (a ? ((AnnotatedT) t).getType() : t);
    assert isLValueT(r) || isLocalT(r) || isFieldT(r) || isParameterT(r);
    return r;
  }
  
  public static Type resolveToRawRValue(final Type t) {
    assert isGeneralRValueT(t);
    Type result = t;
    if (!isNullT(result))
      while (true) {
        if (result.isAlias())
          result = ((AliasT) result).getType();
        else if (result.isAnnotated())
          result = ((AnnotatedT) result).getType();
        else if (isConstantT(result))
          result = ((AnnotatedT) result).getType();
        else
          break;
      }
    assert isNullT(result) || isPrimitiveT(result) || result.isArray()
        || result.isClass() || result.isInterface();
    return result;
  }

  public static Type resolveToRValue(final Type t0) {
    assert isGeneralRValueT(t0);
    final Type t1 = isConstantT(t0) ? ((AnnotatedT)t0).getType() : t0;
    final Type t2 = t1.isAlias() ? ((AliasT)t1).getType() : t1;
    assert isPrimitiveT(t2) || t2.isArray() || t2.isClass() || t2.isInterface();
    return t2;
  }

  public static Type resolveToValue(final AnnotatedT notAValue) {
    assert isNotAValueT(notAValue);
    Type result = notAValue.getType();
    for (final Attribute a : notAValue.attributes()) {
      if (!a.equals(Constants.ATT_NOT_A_VALUE))
        result = result.attribute(a);
    }
    if (notAValue.hasScope(false))
      result.scope(notAValue.getScope());
    return result;
  }
  
  public static boolean runtimeAssrt(final Runtime runtime, final Node n,
      final boolean cond, final String msgFormat, final Object... msgArgs) {
    if (!cond) {
      final Formatter message = new Formatter();
      message.format(msgFormat, msgArgs);
      runtime.error(message.toString(), n);
    }
    return cond;
  }

  public static boolean sameMethodReturnType(final MethodT m1, final MethodT m2) {
    final Type r1 = m1.getResult(), r2 = m2.getResult();
    if (r1.isVoid() || r2.isVoid())
      return r1.isVoid() && r2.isVoid();
    return JavaTypeConverter.isIdentical(r1, r2);
  }

  public static boolean sameMethodSignature(final MethodT m1, final MethodT m2) {
    if (!m1.getName().equals(m2.getName()))
      return false;
    final List<Type> params1 = m1.getParameters(), params2 = m2.getParameters();
    if (params1.size() != params2.size())
      return false;
    final Iterator<Type> i1 = params1.iterator(), i2 = params2.iterator();
    while (i1.hasNext()) {
      final Type t1 = i1.next(), t2 = i2.next();
      assert isParameterT(t1) && isParameterT(t2);
      final Type r1 = dereference(t1), r2 = dereference(t2);
      if (!JavaTypeConverter.isIdentical(r1, r2))
        return false;
    }
    return true;
  }
  
  static String scopeName(final PackageT packageT, final String fileName) {
    return "." + packageNameToScopeName(packageT.getName()) + "."
        + fileNameToScopeName(fileName);
  }

  public static GNode scrubLocations(final GNode result) {
    new MiniVisitor_scrubLocations().dispatch(result);
    return result;
  }

  public static Type simpleNameToExpression(final SymbolTable tab,
      final List<File> paths, final String scope, final String name) {
    final String oldScope = enterScopeByQualifiedName(tab, scope);
    final Type result = (Type) tab.lookup(name);
    resolveIfAlias(tab, paths, scope, result);
    final boolean found = null != result && isGeneralLValueT(result);
    if (found) {
      final Type rValue = dereference(result);
      resolveIfAlias(tab, paths, typeToScopeName(currentType(tab)), rValue);
    }
    enterScopeByQualifiedName(tab, oldScope);
    if (!found && isScopeNested(tab.current().getQualifiedName())) {
      final Type c = currentType(tab);
      if (null != c)
        return typeDotField(tab, paths, c, true, name);
    }
    return result;
  }

  public static PackageT simpleNameToPackage(final SymbolTable tab,
      final String name) {
    final String tagName = SymbolTable.toTagName(name);
    final String toplevelScopeDotSymbol = "." + tagName;
    PackageT result = (PackageT) tab.lookup(toplevelScopeDotSymbol);
    if (result == null) {
      result = new PackageT(name);
      tab.lookupScope(toplevelScopeDotSymbol).define(tagName, result);
    }
    return result;
  }

  public static Type simpleNameToPackageOrType(final SymbolTable tab,
      final List<File> paths, final String scope, final String name) {
    final Type t = simpleNameToType(tab, paths, scope, name);
    return t != null ? t : simpleNameToPackage(tab, name);
  }

  public static Type simpleNameToPackageOrTypeOrExpression(
      final SymbolTable tab, final List<File> paths, final String scope,
      final String name) {
    final Type e = simpleNameToExpression(tab, paths, scope, name);
    return e != null ? e : simpleNameToPackageOrType(tab, paths, scope, name);
  }

  public static ClassOrInterfaceT simpleNameToType(final SymbolTable tab,
      final List<File> paths, final String scope, final String name) {
    final String oldScope = enterScopeByQualifiedName(tab, scope);
    ClassOrInterfaceT result = null;
    { // find as local class, member class, single-import, or top-level class
      final Type t = (Type) tab.lookup(SymbolTable.toTagName(name));
      if (null != t && !t.isPackage())
        result = t.isAlias() ? lookupImport(tab, paths, t.toAlias()) : (ClassOrInterfaceT)t;
    }
    if (null == result && isScopeNested(scope)) {
      final ClassOrInterfaceT c = currentType(tab);
      if (null != c)
        result = typeDotType(tab, paths, c, true, name);
    }
    if (null == result)
      // find in other compilation unit of current package
      result = packageDotType(tab, paths, currentPackage(tab), name);
    if (null == result) {
      final List<Type> imports = currentImports(tab);
      if (null != imports)
        // find in import-on-demand
        for (final Type i : imports) {
          result = packageDotType(tab, paths, (PackageT) i, name);
          if (null != result)
            break;
        }
    }
    if (null == result)
      result = packageDotType(tab, paths, canonicalNameToPackage(tab,
          "java.lang"), name);
    enterScopeByQualifiedName(tab, oldScope);
    if (null == result)
      return null;
    return result;
  }

  @SuppressWarnings("unchecked")
  public static Set<String> stringSet(final Object s) {
    return (Set<String>)s;
  }

  public static ClassT tClass(final SymbolTable tab) {
    return tForName(tab, "java.lang.Class").toClass();
  }

  public static InterfaceT tCloneable(final SymbolTable tab) {
    return tForName(tab, "java.lang.Cloneable").toInterface();
  }

  public static ClassT tError(final SymbolTable tab) {
    return tForName(tab, "java.lang.Error").toClass();
  }

  private static ClassOrInterfaceT tForName(final SymbolTable tab, final String name) {
    final List<File> paths = new ArrayList<File>();
    return canonicalNameToType(tab, paths, name, false);
  }

  public static ClassT tObject(final SymbolTable tab) {
    return tForName(tab, "java.lang.Object").toClass();
  }

  public static AliasT tObjectAlias(final SymbolTable tab) {
    return new AliasT("java.lang.Object", tObject(tab));
  }
  
  public static ClassT tRuntimeException(final SymbolTable tab) {
    return tForName(tab, "java.lang.RuntimeException").toClass();
  }

  public static InterfaceT tSerializable(final SymbolTable tab) {
    return tForName(tab, "java.io.Serializable").toInterface();
  }

  public static ClassT tString(final SymbolTable tab) {
    return tForName(tab, "java.lang.String").toClass();
  }

  public static ClassT tThrowable(final SymbolTable tab) {
    return tForName(tab, "java.lang.Throwable").toClass();
  }
  
  public static String typeDeclString(final SymbolTable tab, final Object obj) {
    assert obj instanceof Type || obj instanceof List;
    if (obj instanceof Type)
      return typeToString(tab, true, (Type)obj);
    final StringBuilder result = new StringBuilder();
    for (final Type t : typeList((List)obj))
      result.append(typeToString(tab, true, t)).append(';');
    return result.toString();
  }
  
  public static VariableT typeDotField(final SymbolTable tab,
      final List<File> paths, final Type base, final boolean parents,
      final String name) {
    final List<VariableT> all = fieldsApplicableAndAccessible(tab, paths, base, parents, name);
    if (1 == all.size())
      return all.get(0);
    return null;
  }

  public static MethodT typeDotMethod(final SymbolTable tab,
      final List<File> paths, final Type baseT, final boolean parents,
      final String selector, final List<Type> actuals) {
    final List<MethodT> all = methodsApplicableAndAccessible(tab, paths, baseT, parents, selector, actuals);
    // chose the most specific method: see gosling_et_al_2000 Section 15.12.2.2.
    final List<MethodT> specific = mostSpecificMethods(tab, paths, all);
    final MethodT result;
    if (specific.size() == 1) {
      result = specific.get(0);
    } else {
      int nonAbstract = 0;
      MethodT any = null;
      for (final MethodT m : specific) {
        if (any == null)
          any = m;
        assert sameMethodSignature(m, any);
        if (!hasModifier(m, "abstract")) {
          any = m;
          nonAbstract++;
        }
      }
      assert nonAbstract <= 1;
      result = any;
    }
    if (null == result)
      return null;
    resolveIfAlias(tab, paths, typeToScopeName(baseT), result.getResult());
    return result;
  }

  public static ClassOrInterfaceT typeDotType(final SymbolTable tab,
      final List<File> paths, final ClassOrInterfaceT base, final boolean parents,
      final String selector) {
    if (recursiveTypeDotType)
      return null;
    recursiveTypeDotType = true;
    final List<Type> all = memberTypesApplicableAndAccessible(tab, paths, base, parents, selector);
    recursiveTypeDotType = false;
    if (1 == all.size())
      return (ClassOrInterfaceT) all.get(0);
    return null;
  }

  public static Type typeDotTypeOrField(final SymbolTable tab,
      final List<File> paths, final Type base, final boolean parents,
      final String selector) {
    assert isWrappedClassT(base) || isWrappedInterfaceT(base) || base.isArray();
    if (parents) {
      for (final Iterator<Type> i = new SuperTypesIter(tab, paths, base); i.hasNext();) {
        final Type member = typeDotTypeOrField(tab, paths, i.next(), false, selector);
        if (null != member)
          return member;
      }
      return null;
    }
    final VariableT field = typeDotField(tab, paths, base, false, selector);
    if (null != field)
      return field;
    return typeDotType(tab, paths, (ClassOrInterfaceT)base, false, selector);
  }

  @SuppressWarnings("unchecked")
  public static List<Type> typeList(final List list) {
    return list;
  }
  
  /** A descriptor is a JVM-internal string representation of a type of a field or method, see JVM
   * specification <a href="http://java.sun.com/docs/books/jvms/second_edition/html/ClassFile.doc.html#1169">&sect;4.3</a>. */
  public static String typeToDescriptor(final SymbolTable tab, final Type type) {
    if (isConstantT(type))
      return typeToDescriptor(tab, type.toAnnotated().getType());
    if (type.isBoolean())
      return "Z";
    if (type.isNumber()) {
      switch (((NumberT)type).getKind()) {
        case BYTE: return "B";
        case CHAR: return "C";
        case DOUBLE: return "D";
        case FLOAT: return "F";
        case INT: return "I";
        case LONG: return "J";
        case SHORT: return "S";
      }
    }
    if (type.isVoid())
      return "V";
    if (type.isArray())
      return "[" + typeToDescriptor(tab, arrayElementType(type.toArray()));
    if (isWrappedClassT(type) || isWrappedInterfaceT(type))
      return "L" + qNameWithDollars(tab, resolveToRawClassOrInterfaceT(type)).replace('.', '/') + ";";
    if (type.isMethod()) {
      final StringBuilder b = new StringBuilder();
      b.append('(');
      for (final Type param : type.toMethod().getParameters())
        b.append(typeToDescriptor(tab, dereference(param)));
      b.append(')').append(typeToDescriptor(tab, type.toMethod().getResult()));
      return b.toString();
    }
    throw new Error();
  }

  static String typeToScopeName(final Type type) {
    if (null == type || type.isArray())
      return "";
    final String result = type.getScope();
    assert null != result;
    return result;
  }

  public static String typeToSimpleName(final Type type) {
    if (type.isAlias())
      return Utilities.unqualify(type.toAlias().getName());
    if (isWrappedClassT(type) || isWrappedInterfaceT(type))
      return resolveToRawClassOrInterfaceT(type).getName();
    assert type.isMethod();
    return type.toMethod().getName();
  }

  public static String typeToString(final SymbolTable tab, final boolean showDetails, final Type type) {
    final CharArrayWriter writer = new CharArrayWriter();
    final Printer printer = new Printer(writer);
    final TypePrinter typePrinter = new JavaTypePrinter(tab, showDetails, printer);
    typePrinter.dispatch(type);
    printer.flush();
    return writer.toString();
  }

  public static Type typeWithDimensions(final Type componentT, final int dim) {
    if (dim == 0)
      return componentT;
    final Type rec = typeWithDimensions(componentT, dim - 1);
    // FIXME: plugged in faux reference with faux type.
    final Type rec2 =
      rec.annotate().shape(new DynamicReference(NumberT.INT));
    return new ArrayT(rec2, true);
  }

  public static String unicodeUnescape(final String in) {
    if (!in.contains("\\u"))
      return in;
    final UnicodeUnescaper uu = new UnicodeUnescaper(new StringReader(in));
    final StringBuilder result = new StringBuilder(in.length());
    try {
      while (true) {
        final int c = uu.read();
        if (-1 == c)
          break;
        result.append((char) c);
      }
    } catch (final IOException e) {
      throw new Error("internal error", e);
    }
    return result.toString();
  }
  
  public static boolean zeroLiteral(final String s) {
    for (int i=0; i<s.length(); i++) {
      final char c = s.charAt(i);
      if ('1' <= c && c <= '9')
        return false;
      if ('d' == c || 'D' == c || 'e' == c || 'E' == c || 'f' == c || 'F' == c)
        return true;
    }
    return true;
  }
}
