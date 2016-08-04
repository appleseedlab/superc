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

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.List;

import xtc.tree.Attribute;
import xtc.type.AliasT;
import xtc.type.ClassT;
import xtc.type.InterfaceT;
import xtc.type.MethodT;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.VoidT;
import xtc.util.SymbolTable;
import xtc.util.Utilities;

/**
 * Uses reflection to construct externally visible types and fill in the symbol
 * table for entities for which no source code is available. This is not a
 * visitor, but has similar method names to emphasize the similarities with
 * JavaExternalAnalyzer.
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.27 $
 */
public final class JavaNoSourceAnalyzer {
  public final SymbolTable _table;

  public JavaNoSourceAnalyzer(final SymbolTable table) {
    _table = table;
  }

  private final Type defineMethod(final List<Attribute> modifiers, MethodT result, final String symbol) {
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    _table.current().define(symbol, result);
    _table.enter(symbol);
    result.scope(_table.current().getQualifiedName());
    _table.exit();
    JavaEntities.currentType(_table).getMethods().add(result);
    assert result.isMethod();
    return result;
  }

  public final void visitClassBody(final Class clazz) {
    final Class[] classes = clazz.getDeclaredClasses();
    for (int i = 0; i < classes.length; i++)
      visitClassOrInterface(classes[i]);
    final Constructor[] constructors = clazz.getDeclaredConstructors();
    for (int i = 0; i < constructors.length; i++)
      visitMethodDeclaration(constructors[i]);
    final Field[] fields = clazz.getDeclaredFields();
    for (int i = 0; i < fields.length; i++)
      visitFieldDeclaration(fields[i]);
    final Method[] methods = clazz.getDeclaredMethods();
    for (int i = 0; i < methods.length; i++)
      visitMethodDeclaration(methods[i]);
  }

  private static String getQName(final Class clazz) {
    final Class declaringClass = clazz.getDeclaringClass();
    if (null == declaringClass)
      return clazz.getName();
    return Utilities.qualify(getQName(declaringClass), clazz.getSimpleName());
  }
  
  public final Type visitClassDeclaration(final Class clazz) {
    if (clazz.isInterface())
      throw new Error(clazz.getName());
    final List<Attribute> modifiers = visitModifiers(clazz.getModifiers());
    final String canonicalName = getQName(clazz);
    final String simpleName;
    {
      final String name = Utilities.getName(canonicalName);
      final int i = name.lastIndexOf('$');
      if (-1 == i)
        simpleName = name;
      else
        simpleName = name.substring(1 + i);
    }
    final Type parent;
    final Class superClass = clazz.getSuperclass();
    if (null == superClass) {
      parent = null;
      if (!"java.lang.Object".equals(clazz.getName()))
        throw new Error();
    } else {
      parent = visitType(clazz.getSuperclass());
    }
    final List<Type> interfaces = visitTypeList(clazz.getInterfaces());
    final ClassT result = new ClassT(canonicalName, parent, interfaces,
        new ArrayList<Type>(), new ArrayList<Type>());
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    final String tagName = SymbolTable.toTagName(simpleName);
    _table.current().define(tagName, result);
    _table.enter(simpleName);
    result.scope(_table.current().getQualifiedName());
    visitClassBody(clazz);
    _table.exit();
    assert result.isClass();
    return result;
  }

  public final Type visitClassOrInterface(final Class clazz) {
    return clazz.isInterface() ? visitInterfaceDeclaration(clazz)
        : visitClassDeclaration(clazz);
  }

  public final Type visitFieldDeclaration(final Field field) {
    final Type type = visitType(field.getType());
    final VariableT result = VariableT.newField(type, field.getName());
    for (final Attribute mod : visitModifiers(field.getModifiers()))
      result.addAttribute(mod);
    _table.current().define(field.getName(), result);
    result.scope(_table.current().getQualifiedName());
    JavaEntities.currentType(_table).getFields().add(result);
    assert JavaEntities.isFieldT(result);
    return result;
  }

  public final List<Type> visitFormalParameters(final Class[] types) {
    final List<Type> result = new ArrayList<Type>(types.length);
    for (int i = 0; i < types.length; i++) {
      final VariableT p = VariableT.newParam(visitType(types[i]), "x" + i);
      assert JavaEntities.isParameterT(p);
      result.add(p);
    }
    return result;
  }

  public final Type visitInterfaceDeclaration(final Class interfaze) {
    if (!interfaze.isInterface())
      throw new Error(interfaze.getName());
    final List<Attribute> modifiers = visitModifiers(interfaze.getModifiers());
    final String canonicalName = interfaze.getName();
    final String simpleName;
    {
      final String name = Utilities.getName(canonicalName);
      final int i = name.lastIndexOf('$');
      if (-1 == i)
        simpleName = name;
      else
        simpleName = name.substring(1 + i);
    }
    final List<Type> interfaces = visitTypeList(interfaze.getInterfaces());
    final InterfaceT result = new InterfaceT(canonicalName, interfaces,
        new ArrayList<Type>(), new ArrayList<Type>());
    for (final Attribute mod : modifiers)
      result.addAttribute(mod);
    final String tagName = SymbolTable.toTagName(simpleName);
    _table.current().define(tagName, result);
    _table.enter(simpleName);
    result.scope(_table.current().getQualifiedName());
    visitClassBody(interfaze);
    _table.exit();
    assert result.isInterface();
    return result;
  }
  
  public final Type visitMethodDeclaration(final Constructor method) {
    final List<Attribute> modifiers = visitModifiers(method.getModifiers());
    final Type base = visitType(method.getDeclaringClass());
    final List<Type> exceptions = visitTypeList(method.getExceptionTypes());
    final String symbol = JavaEntities.methodSymbolFromConstructor(method);
    final List<Type> parameters = visitFormalParameters(method.getParameterTypes());
    final MethodT methodT = JavaEntities.newRawConstructor(base, parameters, exceptions);
    final Type result = defineMethod(modifiers, methodT, symbol);
    return result;
  }

  public final Type visitMethodDeclaration(final Method method) {
    final List<Attribute> modifiers = visitModifiers(method.getModifiers());
    final Type returnType = visitType(method.getReturnType());
    final String name = method.getName();
    final List<Type> exceptions = visitTypeList(method.getExceptionTypes());
    final String symbol = JavaEntities.methodSymbolFromMethod(method);
    final List<Type> parameters = visitFormalParameters(method.getParameterTypes());
    final MethodT methodT = new MethodT(returnType, name, parameters, false, exceptions);
    final Type result = defineMethod(modifiers, methodT, symbol);
    return result;
  }

  public final List<Attribute> visitModifiers(final int modifiers) {
    final List<Attribute> result = new ArrayList<Attribute>();
    if (Modifier.isAbstract(modifiers))
      result.add(JavaEntities.nameToModifier("abstract"));
    if (Modifier.isFinal(modifiers))
      result.add(JavaEntities.nameToModifier("final"));
    if (Modifier.isNative(modifiers))
      result.add(JavaEntities.nameToModifier("native"));
    if (Modifier.isPrivate(modifiers))
      result.add(JavaEntities.nameToModifier("private"));
    if (Modifier.isProtected(modifiers))
      result.add(JavaEntities.nameToModifier("protected"));
    if (Modifier.isPublic(modifiers))
      result.add(JavaEntities.nameToModifier("public"));
    if (Modifier.isStatic(modifiers))
      result.add(JavaEntities.nameToModifier("static"));
    if (Modifier.isStrict(modifiers))
      result.add(JavaEntities.nameToModifier("strictfp"));
    if (Modifier.isSynchronized(modifiers))
      result.add(JavaEntities.nameToModifier("synchronized"));
    if (Modifier.isTransient(modifiers))
      result.add(JavaEntities.nameToModifier("transient"));
    if (Modifier.isVolatile(modifiers))
      result.add(JavaEntities.nameToModifier("volatile"));
    return result;
  }

  public final Type visitType(final Class clazz) {
    Class componentC = clazz;
    int dimensions = 0;
    while (componentC.isArray()) {
      componentC = componentC.getComponentType();
      dimensions++;
    }
    final Type componentT = componentC.isPrimitive()
      ? visitTypeName(componentC.getName()) : new AliasT(componentC.getName());
    final Type result = JavaEntities.typeWithDimensions(componentT, dimensions);
    assert JavaEntities.isReturnT(result);
    return result;
  }

  public final List<Type> visitTypeList(final Class[] types) {
    final List<Type> result = new ArrayList<Type>(types.length);
    for (int i = 0; i < types.length; i++)
      result.add(visitType(types[i]));
    return result;
  }

  public final Type visitTypeName(final String name) {
    if (1 == name.length()) {
      switch (name.charAt(0)) {
      case 'Z':
        return JavaEntities.nameToBaseType("boolean");
      case 'B':
        return JavaEntities.nameToBaseType("byte");
      case 'C':
        return JavaEntities.nameToBaseType("char");
      case 'D':
        return JavaEntities.nameToBaseType("double");
      case 'F':
        return JavaEntities.nameToBaseType("float");
      case 'I':
        return JavaEntities.nameToBaseType("int");
      case 'J':
        return JavaEntities.nameToBaseType("long");
      case 'S':
        return JavaEntities.nameToBaseType("short");
      }
    }
    final Type result = JavaEntities.nameToBaseType(name);
    assert result.isBoolean() || result.isNumber()
        || result instanceof VoidT;
    return result;
  }
}
