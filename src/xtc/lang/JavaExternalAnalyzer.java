/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2006-2007 IBM Corp.
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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import xtc.Constants;
import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.type.AliasT;
import xtc.type.ClassOrInterfaceT;
import xtc.type.ClassT;
import xtc.type.InterfaceT;
import xtc.type.Language;
import xtc.type.MethodT;
import xtc.type.PackageT;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.Utilities;

/**
 * A visitor that constructs externally visible types and fills the symbol table
 * for a Java file. Does not descend into method bodies, just finds the class,
 * interface, method, and field signatures. Used in conjunction with
 * JavaAnalyzer. Let F be the file currently analyzed by the JavaAnalyzer; then
 * the JavaExternalAnalyzer is used on (i) classes defined in F, and (ii)
 * compilation units that define classes whose name gets used in F. Packages,
 * classes, and interfaces go into namespace "tag(..)", methods go into
 * namespace "method(..)", and fields go into the default namespace. The scopes
 * associated with packages and types do not have the namespace in their name,
 * only the symbols do. For example, scope "java" contains scope "lang", but
 * scope "java" maps symbol "tag(lang)" to an instance of PackageT. Declared
 * types are represented by instances of ClassT or InterfaceT, whereas names
 * used, for example, as method return types are represented by instances of
 * AliasT.
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.71 $
 */
public class JavaExternalAnalyzer extends Visitor {
  protected static List<Attribute> MODIFIERS_CLASS =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_CONSTRUCTOR =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_FIELD =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_INTERFACE =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_INTERFACE_FIELD = 
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_INTERFACE_MEMBERTYPE =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_INTERFACE_METHOD =
    new ArrayList<Attribute>();

  protected static List<Attribute> MODIFIERS_METHOD =
    new ArrayList<Attribute>();

  static {
    // gosling_et_al_2000 8.1.1
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("protected"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("private"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("abstract"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("final"));
    MODIFIERS_CLASS.add(JavaEntities.nameToModifier("strictfp"));
    // gosling_et_al_2000 8.3.1
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("protected"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("private"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("final"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("transient"));
    MODIFIERS_FIELD.add(JavaEntities.nameToModifier("volatile"));
    // gosling_et_al_2000 8.8
    MODIFIERS_CONSTRUCTOR.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_CONSTRUCTOR.add(JavaEntities.nameToModifier("protected"));
    MODIFIERS_CONSTRUCTOR.add(JavaEntities.nameToModifier("private"));
    // gosling_et_al_2000 9.1.1
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("protected"));
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("private"));
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("abstract"));
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_INTERFACE.add(JavaEntities.nameToModifier("strictfp"));
    // gosling_et_al_2000 9.5
    MODIFIERS_INTERFACE_FIELD.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_INTERFACE_FIELD.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_INTERFACE_FIELD.add(JavaEntities.nameToModifier("final"));
    // gosling_et_al_2000 9.5
    MODIFIERS_INTERFACE_MEMBERTYPE.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_INTERFACE_MEMBERTYPE.add(JavaEntities.nameToModifier("public"));
    // gosling_et_al_2000 9.4
    MODIFIERS_INTERFACE_METHOD.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_INTERFACE_METHOD.add(JavaEntities.nameToModifier("abstract"));
    // gosling_et_al_2000 8.4.3
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("public"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("protected"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("private"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("abstract"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("static"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("final"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("synchronized"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("native"));
    MODIFIERS_METHOD.add(JavaEntities.nameToModifier("strictfp"));
  }

  protected static void addModifier(final List<Attribute> modifiers, final String name) {
    if (!hasModifier(modifiers, name))
      modifiers.add(JavaEntities.nameToModifier(name));
  }

  protected static void addModifiers(final List<Attribute> modifiers,
      final List<Attribute> toAdd) {
    for (final Attribute attribute : toAdd)
      if (!modifiers.contains(attribute))
        modifiers.add(attribute);
  }

  public static int countDimensions(final GNode dimNode) {
    return null == dimNode ? 0 : dimNode.size();
  }

  protected static boolean hasModifier(final List<Attribute> modifiers, final String modifier) {
    return modifiers.contains(JavaEntities.nameToModifier(modifier));
  }

  protected final Runtime _runtime;

  public final SymbolTable _table;

  public JavaExternalAnalyzer(final Runtime runtime, final SymbolTable table) {
    _runtime = runtime;
    _table = table;
  }

  /** Use this for asserting that the input is typed correctly. */
  protected boolean assrt(final GNode n, final boolean cond, final String msgFormat, final Object... msgArgs) {
    return JavaEntities.runtimeAssrt(_runtime, n, cond, msgFormat, msgArgs);
  }

  protected void assrtDiffersFromEnclosing(final GNode n,
      final String canonicalName) {
    final String simpleName = Utilities.getName(canonicalName);
    final String packageName = JavaEntities.currentPackage(_table).getName();
    final String nameWithoutPackage = 0 == packageName.length() ? canonicalName
        : canonicalName.substring(packageName.length() + 1);
    final String middleName = Utilities.getQualifier(nameWithoutPackage);
    if (null != middleName) {
      final String[] c = Utilities.toComponents(middleName);
      for (int i = 0; i < c.length; i++)
        assrt(n, !c[i].equals(simpleName), "name must not match enclosing type");
    }
  }

  protected void assrtLegalModifiers(final GNode n, final List<Attribute> expected,
      final List<Attribute> actual, final String context) {
    final boolean pri = hasModifier(actual, "private");
    final boolean pro = hasModifier(actual, "protected");
    final boolean pub = hasModifier(actual, "public");
    assrt(n, !(pri && pro), "conflicting modifiers private and protected");
    assrt(n, !(pri && pub), "conflicting modifiers private and public");
    assrt(n, !(pro && pub), "conflicting modifiers protected and public");
    for (final Attribute m : actual)
      assrt(n, expected.contains(m), "illegal %s modifier %s", context, m);
    final boolean fin = hasModifier(actual, "final");
    final boolean vol = hasModifier(actual, "volatile");
    assrt(n, !(fin && vol), "conflicting modifiers final and volatile");
  }

  protected final String currentScopeName() {
    return _table.current().getQualifiedName();
  }

  protected final Type declareDefaultConstructorIfNecessary() {
    // gosling_et_al_2000 8.8.7 default constructor
    final Type wrappedBase = JavaEntities.currentType(_table);
    final ClassOrInterfaceT base = JavaEntities.resolveToRawClassOrInterfaceT(wrappedBase);
    for (final Type i : base.getMethods())
      if (JavaEntities.isConstructor(base, i.toMethod()))
        return null;
    final MethodT result = JavaEntities.newRawConstructor(base, new ArrayList<Type>(), new ArrayList<Type>());
    final List<Attribute> modifiers = new ArrayList<Attribute>();
    if (JavaEntities.hasModifier(wrappedBase, "private"))
      modifiers.add(JavaEntities.nameToModifier("private"));
    else if (JavaEntities.hasModifier(wrappedBase, "protected"))
      modifiers.add(JavaEntities.nameToModifier("protected"));
    else if (JavaEntities.hasModifier(wrappedBase, "public"))
      modifiers.add(JavaEntities.nameToModifier("public"));
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    final String symbol = "method(<init>)()";
    _table.current().define(symbol, result);
    _table.enter(symbol);
    result.scope(_table.current().getQualifiedName());
    _table.exit();
    assert JavaEntities.isConstructor(base, result);
    JavaEntities.currentType(_table).getMethods().add(result);
    return result;
  }

  protected final List<Type> makeList(final GNode n) {
    final List<Type> result = new ArrayList<Type>(n.size());
    for (final Object o : n)
      result.add((Type)dispatch((Node)o));
    return result;
  }
  
  protected final boolean memberOfInterface() {
    if (!JavaEntities.isScopeForMember(currentScopeName()))
      return false;
    final Type t = JavaEntities.currentType(_table);
    return null != t && JavaEntities.isWrappedInterfaceT(t);
  }

  public final List<Type> processDeclarators(final List<Attribute> modifiers,
      final Type type, final GNode declarators) {
    assert JavaEntities.isRValueT(type);
    final List<Type> result = new ArrayList<Type>();
    final boolean isLocal = JavaEntities.isScopeLocal(currentScopeName());
    for (final Object i : declarators) {
      final GNode declNode = (GNode) i;
      final String name = declNode.getString(0);
      final Type dimType = JavaEntities.typeWithDimensions(type, countDimensions(declNode.getGeneric(1)));
      final Type entity = isLocal ? VariableT.newLocal(dimType, name) : VariableT.newField(dimType, name);
      for (final Attribute mod : modifiers)
        entity.addAttribute(mod);
      entity.language(Language.JAVA);
      assert isLocal ? JavaEntities.isLocalT(entity) : JavaEntities.isFieldT(entity);
      if (null == _table.current().lookupLocally(name)) {
        result.add(entity);
        _table.current().define(name, entity);
        entity.scope(_table.current().getQualifiedName());
        if (!isLocal)
          JavaEntities.currentType(_table).getFields().add(entity);
      } else {
        if (isLocal)
          _runtime.error("duplicate variable declaration " + name, declNode);
        else
          _runtime.error("duplicate field declaration " + name, declNode);
      }
      declNode.setProperty(Constants.TYPE, entity);
    }
    return result;
  }

  /** Visit a BlockDeclaration = ["static"] Block (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#246032">&sect;8.6</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#39245">&sect;8.7</a>). */
  public final void visitBlockDeclaration(final GNode n) {
    assert 2 == n.size();
  }

  /**
   * Visit a ClassBody = Declaration* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#18988">&sect;8.1.5</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/interfaces.doc.html#236431">&sect;9.1.3</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#41147">&sect;15.9</a>).
   */
  public final void visitClassBody(final GNode n) {
    for (final Object o : n)
      dispatch((Node)o);
  }
  
  /**
   * Visit a ClassDeclaration = Modifiers Identifier null [Extension]
   * [Implementation] ClassBody (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/classes.doc.html#15372">&sect;8.1</a>,
   * <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#247766">&sect;14.3</a>).
   */
  public final ClassT visitClassDeclaration(final GNode n) {
    @SuppressWarnings("unchecked")
    final List<Attribute> modifiers = (List<Attribute>) dispatch(n.getNode(0));
    final boolean isMember = JavaEntities.isScopeForMember(currentScopeName());
    if (isMember) {
      final ClassOrInterfaceT declaringType = JavaEntities.currentType(_table);
      if (JavaEntities.isWrappedInterfaceT(declaringType))
        addModifiers(modifiers, MODIFIERS_INTERFACE_MEMBERTYPE);
      if (JavaEntities.hasModifier(declaringType, "strictfp"))
        addModifier(modifiers, "strictfp");
      if (hasModifier(modifiers, "static"))
        assrt(n, JavaEntities.hasModifier(declaringType, "static") || JavaEntities.isTypeTopLevel(declaringType), "illegal context for static member");
    }
    assrtLegalModifiers(n.getGeneric(0), MODIFIERS_CLASS, modifiers, "class");
    if (hasModifier(modifiers, "public"))
      assrt(n, isMember || JavaEntities.isScopeTopLevel(currentScopeName()), "public class must be member or top-level");
    if (hasModifier(modifiers, "protected") || hasModifier(modifiers, "private"))
      assrt(n, isMember && !memberOfInterface(), "private or protected class must be member of class");
    if (hasModifier(modifiers, "static"))
      assrt(n, isMember, "static class must be member");
    assrt(n, !hasModifier(modifiers, "final") || !hasModifier(modifiers, "abstract"), "can not be both abstract and final");
    final String simpleName = n.getString(1);
    final String canonicalName = JavaEntities.canonicalName(_table, simpleName);
    assrtDiffersFromEnclosing(n, canonicalName);
    final List<Type> extension = JavaEntities.typeList((List) dispatch(n.getNode(3)));
    final Type parent;
    if (null == extension) {
      parent = JavaEntities.tObjectAlias(_table);
    } else {
      assrt(n, 1 == extension.size(), "can only extend one class");
      assrt(n, !"java.lang.Object".equals(canonicalName), "Object can not have an extends clause");
      parent = extension.get(0);
    }
    assrt(n.getGeneric(0), JavaEntities.isWrappedClassT(parent), "class can only extend class");
    final List<Type> interfaces = n.get(4) == null ? new ArrayList<Type>() : JavaEntities.typeList((List) dispatch(n.getNode(4)));
    if ("java.lang.Object".equals(canonicalName))
      assrt(n, 0 == interfaces.size(), "Object can not have an implements clause");
    for (final Type i : interfaces)
      assrt(n.getGeneric(4), JavaEntities.isWrappedInterfaceT(i), "class can only implement interface");
    final ClassT result = new ClassT(canonicalName, parent, interfaces, new ArrayList<Type>(), new ArrayList<Type>());
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    final String tagName = SymbolTable.toTagName(simpleName);
    assert null == _table.current().lookupLocally(tagName);
    _table.current().define(tagName, result);
    _table.enter(simpleName);
    result.scope(_table.current().getQualifiedName());
    dispatch(n.getNode(5));
    declareDefaultConstructorIfNecessary();
    _table.exit();
    assert result.isClass();
    return result;
  }

  /**
   * Visit a CompilationUnit = [PackageDeclaration] ImportDeclaration*
   * Declaration* (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/packages.doc.html#40031">&sect;7.3</a>).
   */
  public final void visitCompilationUnit(final GNode n) {
    if (null == n.get(0))
      visitPackageDeclaration(null);
    else
      dispatch(n.getNode(0));
    _table.enter(JavaEntities.fileNameToScopeName(n.getLocation().file));
    for (int i = 1; i < n.size(); i++) {
      final GNode declNode = n.getGeneric(i);
      assrt(n, declNode.hasName("ImportDeclaration")
          || declNode.hasName("ClassDeclaration")
          || declNode.hasName("InterfaceDeclaration")
          || declNode.hasName("EmptyDeclaration"),
          "unexpected top-level %s", declNode.getName());
      dispatch(declNode);
    }
    _table.setScope(_table.root());
  }

  /**
   * Visit a EmptyDeclaration = (no children) (gosling_et_al_2000 <a
   * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#5970">&sect;14.6</a>).
   */
  public final void visitEmptyDeclaration(final GNode n) { 
    assert 0 == n.size();
  }

  /** Visit an Extension = Type+. */
  public final List<Type> visitExtension(final GNode n) {
    // gosling_et_al_2000 8.1.3, 9.1.2
    final List<Type> result = makeList(n);
    for (final Type t : result)
      assrt(n, JavaEntities.isWrappedClassT(t) || JavaEntities.isWrappedInterfaceT(t), 
          "supertype must be class or interface");
    return result;
  }

  /**
   * Visit a FieldDeclaration = Modifiers Type Declarators.
   * Also descends into Declarators = Declarator+ and into
   * Declarator = Identifier [Dimensions] [VariableInitializer]
   * to get all the fields declared by this node.
   */
  public final List<Type> visitFieldDeclaration(final GNode n) {
    // gosling_et_al_2000 9.3
    @SuppressWarnings("unchecked")
    final List<Attribute> modifiers = (List<Attribute>) dispatch(n.getNode(0));
    if (memberOfInterface()) {
      addModifiers(modifiers, MODIFIERS_INTERFACE_FIELD);
      assrtLegalModifiers(n, MODIFIERS_INTERFACE_FIELD, modifiers,
          "interface field");
    } else {
      assrtLegalModifiers(n, MODIFIERS_FIELD, modifiers, "field");
    }
    final Type type = (Type) dispatch(n.getNode(1));
    assrt(n.getGeneric(1), JavaEntities.isRValueT(type), "illegal type for field");
    return processDeclarators(modifiers, type, n.getGeneric(2));
  }

  /** Visit a FormalParameter = [Modifier] Type null Identifier [Dimensions]. */
  public final Type visitFormalParameter(final GNode n) {
    // gosling_et_al_2000 8.4.1
    assert null == n.get(4) : "must run JavaAstSimplifier first";
    final String id = n.getString(3);
    final Type result = VariableT.newParam((Type) dispatch(n.getNode(1)), id);
    result.language(Language.JAVA);
    if (n.getGeneric(0).size() != 0)
      result.addAttribute(JavaEntities.nameToModifier("final"));
    if (null == _table.current().lookupLocally(id)) {
      _table.current().define(id, result);
      result.scope(_table.current().getQualifiedName());
    } else
      _runtime.error("duplicate parameter declaration " + id, n);
    assert JavaEntities.isParameterT(result);
    return result;
  }

  /** Visit a FormalParameters = FormalParameter*. */
  public final List<Type> visitFormalParameters(final GNode n) {
    // gosling_et_al_2000 8.4.1
    return makeList(n);
  }

  /** Visit an Implementation = Type+. */
  public final List<Type> visitImplementation(final GNode n) {
    // gosling_et_al_2000 8.1.4
    final List<Type> result = makeList(n);
    for (final Iterator iN = n.iterator(), iT = result.iterator(); iT.hasNext();)
      assrt((GNode) iN.next(), JavaEntities.isWrappedInterfaceT((Type) iT
          .next()), "supertype must be class or interface");
    return result;
  }

  /** Visit an ImportDeclaration = QualifiedIdentifier ["*"]. */
  public final void visitImportDeclaration(final GNode n) {
    // gosling_et_al_2000 7.5
    final String canonicalName = (String) dispatch(n.getNode(1));
    if (n.get(2) == null) {
      // defer resolution to JavaAnalyzer.visitPrimaryIdentifier()
      final AliasT t = new AliasT(canonicalName);
      final String simpleName = Utilities.unqualify(canonicalName);
      // TD 03 (7.5) ImportDeclaration = QualifiedIdentifier ["*"] (check whether the name clashes with some existing package)
      assrt(n, JavaEntities.isWrappedClassT(t) || JavaEntities.isWrappedInterfaceT(t), "import must be class or interface");
      _table.current().define(SymbolTable.toTagName(simpleName), t);
    } else {
      final PackageT t = JavaEntities.canonicalNameToPackage(_table, canonicalName);
      _table.current().addDefinition("imports(*)", t);
    }
  }

  /** Visit a InterfaceDeclaration = Modifiers Identifier null [Extension] ClassBody. */
  public final InterfaceT visitInterfaceDeclaration(final GNode n) {
    // gosling_et_al_2000 9.1
    @SuppressWarnings("unchecked")
    final List<Attribute> modifiers = (List<Attribute>) dispatch(n.getNode(0));
    addModifier(modifiers, "abstract");
    final boolean isMember = JavaEntities.isScopeForMember(currentScopeName());
    if (isMember) {
      final ClassOrInterfaceT declaringType = JavaEntities.currentType(_table);
      if (declaringType.isInterface())
        addModifiers(modifiers, MODIFIERS_INTERFACE_MEMBERTYPE);
      if (JavaEntities.hasModifier(declaringType, "strictfp"))
        addModifier(modifiers, "strictfp");
      addModifier(modifiers, "static");
      assrt(n, JavaEntities.hasModifier(declaringType, "static") || JavaEntities.isTypeTopLevel(declaringType), "illegal context for static member");
    }
    if (hasModifier(modifiers, "protected") || hasModifier(modifiers, "private"))
      assrt(n, isMember, "private or protected interface must be member");
    if (hasModifier(modifiers, "static"))
      assrt(n, isMember, "static interface must be member");
    assrtLegalModifiers(n, MODIFIERS_INTERFACE, modifiers, "interface");
    final String simpleName = n.getString(1);
    final String canonicalName = JavaEntities.canonicalName(_table, simpleName);
    assrtDiffersFromEnclosing(n, canonicalName);
    final List<Type> interfaces = null == n.get(3) ? new ArrayList<Type>() : JavaEntities.typeList((List) dispatch(n.getNode(3)));
    final InterfaceT result = new InterfaceT(canonicalName, interfaces, new ArrayList<Type>(), new ArrayList<Type>());
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    final String tagName = SymbolTable.toTagName(simpleName);
    if (null == _table.current().lookupLocally(tagName)) {
      _table.current().define(tagName, result);
      _table.enter(simpleName);
      result.scope(_table.current().getQualifiedName());
      final GNode bodyNode = n.getGeneric(4);
      for (int i = 0; i < bodyNode.size(); i++) {
        final GNode memberNode = bodyNode.getGeneric(i);
        assrt(n, memberNode.hasName("EmptyDeclaration")
            || memberNode.hasName("FieldDeclaration")
            || memberNode.hasName("MethodDeclaration")
            || memberNode.hasName("ClassDeclaration")
            || memberNode.hasName("InterfaceDeclaration"),
            "illegal interface member");
        dispatch(memberNode);
      }
      _table.exit();
      if (JavaEntities.isTypeNested(result))
        assrt(n, !JavaEntities.isTypeInner(JavaEntities.declaringType(_table, result)), "inner classes may not declare member interfaces");
    } else {
      _runtime.error("duplicate declaration " + canonicalName, n);
    }
    assert result.isInterface();
    return result;
  }

  /**
   * Visit a MethodDeclaration = Modifiers null Type Identifier FormalParameters [Dimensions]
   * [ThrowsClause] [Block].
   */
  public final Type visitMethodDeclaration(final GNode n) {
    // gosling_et_al_2000 8.4, 8.8, 9.4
    assert null == n.get(5) : "must run JavaAstSimplifier first";
    @SuppressWarnings("unchecked")
    final List<Attribute> modifiers = (List<Attribute>) dispatch(n.getNode(0));
    final String name = n.getString(3);
    final ClassOrInterfaceT base = JavaEntities.currentType(_table);
    final boolean isConstructor = JavaEntities.typeToSimpleName(base).equals(name);
    final Type returnType = isConstructor ? (JavaEntities.constructorsReturnVoid() ? JavaEntities.nameToBaseType("void") : base) : (Type) dispatch(n.getNode(2));
    if (!isConstructor) {
      assrt(n, null != n.get(2), "missing return type");
      if (JavaEntities.hasModifier(base, "strictfp"))
        addModifier(modifiers, "strictfp");
      if (JavaEntities.hasModifier(base, "final"))
        addModifier(modifiers, "final");
      if (hasModifier(modifiers, "private"))
        addModifier(modifiers, "final");
    }
    if (memberOfInterface()) {
      assrt(n, !isConstructor, "interface can not have constructor");
      addModifiers(modifiers, MODIFIERS_INTERFACE_METHOD);
      assrtLegalModifiers(n, MODIFIERS_INTERFACE_METHOD, modifiers,
          "interface method");
    } else {
      if (isConstructor)
        assrtLegalModifiers(n, MODIFIERS_CONSTRUCTOR, modifiers, "constructor");
      else
        assrtLegalModifiers(n, MODIFIERS_METHOD, modifiers, "method");
    }
    if (hasModifier(modifiers, "static"))
      assrt(n, JavaEntities.hasModifier(base, "static") || JavaEntities.isTypeTopLevel(base), "illegal context for static member");
    final List<Type> exceptions = null == n.get(6) ? new ArrayList<Type>() : JavaEntities.typeList((List) dispatch(n.getNode(6)));
    final String symbol = JavaEntities.methodSymbolFromAst(n);
    _table.enter(symbol);
    final List<Type> parameters = JavaEntities.typeList((List) dispatch(n.getNode(4)));
    final Type result = new MethodT(returnType, name, parameters, false, exceptions);
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    if (JavaEntities.hasModifier(result, "abstract"))
      assrt(n, !JavaEntities.hasModifier(result, "private")
          && !JavaEntities.hasModifier(result, "static")
          && !JavaEntities.hasModifier(result, "final")
          && !JavaEntities.hasModifier(result, "native")
          && !JavaEntities.hasModifier(result, "strictfp")
          && !JavaEntities.hasModifier(result, "synchronized"), "conflicting modifiers");
    assrt(n, !JavaEntities.hasModifier(result, "strictfp") || !JavaEntities.hasModifier(result, "native"), "conflicting modifiers");
    result.scope(_table.current().getQualifiedName());
    _table.exit();
    _table.current().define(symbol, result);
    JavaEntities.currentType(_table).getMethods().add(result);
    assert result.isMethod();
    return result;
  }

  /** Visit a Modifiers = Modifier*. */
  public final List<Attribute> visitModifiers(final GNode n) {
    final List<Attribute> result = new ArrayList<Attribute>();
    for (int i = 0; i < n.size(); i++) {
      final String name = n.getGeneric(i).getString(0);
      final Attribute modifier = JavaEntities.nameToModifier(name);
      if (null == modifier)
        _runtime.error("unexpected modifier " + name, n);
      else if (result.contains(modifier))
        _runtime.error("duplicate modifier " + name, n);
      else
        result.add(modifier);
    }
    return result;
  }

  /** Visit a PackageDeclaration = QualifiedIdentifier. */
  public final PackageT visitPackageDeclaration(final GNode n) {
    // gosling_et_al_2000 9.4
    final String canonicalName = null == n ? "" : (String) dispatch(n.getNode(1));
    final PackageT result = JavaEntities.canonicalNameToPackage(_table,
        canonicalName);
    _table.enter(JavaEntities.packageNameToScopeName(result.getName()));
    return result;
  }

  /** Visit a PrimitiveType = ("byte" / "short" / "char" / "int" / "long" / "float" / "double" / "boolean")
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/typesValues.doc.html#85587">&sect;4.2</a>). */
  public final Type visitPrimitiveType(final GNode n) {
    final Type result = JavaEntities.nameToBaseType(n.getString(0));
    assrt(n, null != result
        && (JavaEntities.isPrimitiveT(result) || result.isVoid()),
        "unknown base type %s", n.getString(0));
    return result;
  }

  /** Visit a QualifiedIdentifier = Identifier+. */
  public final String visitQualifiedIdentifier(final GNode n) {
    // using StringBuffer instead of Utilities.qualify() to avoid O(n^2)
    // behavior
    final StringBuffer b = new StringBuffer();
    for (int i = 0; i < n.size(); i++) {
      if (b.length() > 0)
        b.append(Constants.QUALIFIER);
      b.append(n.getString(i));
    }
    return b.toString();
  }

  /** Visit a ThrowsClause = QualifiedIdentifier+. */
  public final List<Type> visitThrowsClause(final GNode n) {
    //gosling_et_al_2000 8.4.4, 8.8.4, 9.4
    final List<Type> result = new ArrayList<Type>(n.size());
    for (int i = 0; i < n.size(); i++) {
      final String name = (String) dispatch(n.getNode(i));
      result.add(new AliasT(name));
    }
    return result;
  }

  /**
   * Visit a Type = TypeName Dimensions
   * (gosling_et_al_2000 <a href="http://java.sun.com/docs/books/jls/second_edition/html/typesValues.doc.html#48440">&sect;4</a>,
   * <a href="http://java.sun.com/docs/books/jls/second_edition/html/arrays.doc.html#25518">&sect;10.1</a>).
   * Note that TypeName is either PrimitiveType or ClassType, i.e., QualifiedIdentifier.
   * Make no resolution attempt in the case of a qualified identifier, just
   * return an alias every time. The reason is that in general, there is
   * too little information to resolve the type at this point. For example, the
   * name may refer to a type declared in another file, which may recursively
   * mention an entity in this file.
   */
  public final Type visitType(final GNode n) {
    final boolean composite = n.getGeneric(0).hasName("QualifiedIdentifier");
    final Object dispatched0 = dispatch(n.getNode(0));
    final Type componentT = composite ? new AliasT((String) dispatched0) : (Type) dispatched0;
    final int dimensions = countDimensions(n.getGeneric(1));
    final Type result = JavaEntities.typeWithDimensions(componentT, dimensions);
    assrt(n, JavaEntities.isReturnT(result), "unexpected type reference");
    return result;
  }

  /** Visit a VoidType = (no children). */
  public final Type visitVoidType(final GNode n) {
    return JavaEntities.nameToBaseType("void");
  }
}
