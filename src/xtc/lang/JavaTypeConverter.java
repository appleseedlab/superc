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

import java.io.File;
import java.util.Iterator;
import java.util.List;

import xtc.lang.JavaEntities.SuperTypesIter;
import xtc.type.IntegerT;
import xtc.type.InterfaceT;
import xtc.type.MethodT;
import xtc.type.NumberT;
import xtc.type.Type;
import xtc.util.SymbolTable;

/**
 * Java type conversions and promotions.
 * 
 * @author Martin Hirzel
 * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#27529">JLS 2 &sect;5</a>
 */
public final class JavaTypeConverter {
  /**
   * Perform assignment conversion.  Assumes that src and tgt are
   * either not aliases, or if aliases, are already resolved. May
   * resolve other aliases, such as supertypes, method parameter and
   * return types, etc.
   *
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#184206">JLS 2 &sect;5.2</a>
   */
  public static Type convertAssigning(final SymbolTable tab, final List<File> paths,
      final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = convertAssigningInternal(tab, paths, tgt, src);
    assert null == result || JavaEntities.isWrappedRValueT(result);
    return result;
  }

  private static Type convertAssigningInternal(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    final Type resIdentity = convertIdentity(tgt, src);
    if (null != resIdentity)
      return resIdentity;
    final Type resWidenPrimitive = widenPrimitive(tgt, src);
    if (null != resWidenPrimitive)
      return resWidenPrimitive;
    final Type resWidenReference = widenReference(tab, paths, tgt, src);
    if (null != resWidenReference)
      return resWidenReference;
    if (src.hasConstant()) {
      final Type srcRaw = JavaEntities.resolveToRawRValue(src);
      final Type tgtRaw = JavaEntities.resolveToRawRValue(tgt);
      if (srcRaw.isInteger() && tgtRaw.isInteger()) {
        final NumberT srcInt = (IntegerT) srcRaw, tgtInt = (IntegerT) tgtRaw;
        switch (srcInt.getKind()) {
        case BYTE:
        case SHORT:
        case CHAR:
        case INT:
          switch (tgtInt.getKind()) {
          case BYTE:
          case SHORT:
          case CHAR:
            final Type resNarrowPrimitive = narrowPrimitive(tgt, src);
            final Object srcObj = src.getConstant().getValue();
            final Object resObj = resNarrowPrimitive.getConstant().getValue();
            final long srcVal = srcObj instanceof Number ? ((Number)srcObj).longValue() : ((Character)srcObj).charValue();
            final long resVal = resObj instanceof Number ? ((Number)resObj).longValue() : ((Character)resObj).charValue();
            if (srcVal == resVal)
              return resNarrowPrimitive;
          }
        }
      }
    }
    return null;
  }

  /**
   * Perform casting conversion. Assumes that src and tgt are either
   * not aliases, or if aliases, are already resolved. May resolve
   * other aliases, such as supertypes, method parameter and return
   * types, etc.
   * 
   * @return The converted type, or null if this kind of conversion does not
   *         apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#20232">JLS 2 &sect;5.5</a>
   */
  public static Type convertCasting(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = convertCastingInternal(tab, paths, tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result);
    return result;
  }

  private static Type convertCastingInternal(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    final Type resIdentity = convertIdentity(tgt, src);
    if (null != resIdentity)
      return resIdentity;
    final Type resWidenPrimitive = widenPrimitive(tgt, src);
    if (null != resWidenPrimitive)
      return resWidenPrimitive;
    final Type resNarrowPrimitive = narrowPrimitive(tgt, src);
    if (null != resNarrowPrimitive)
      return resNarrowPrimitive;
    final Type resWidenReference = widenReference(tab, paths, tgt, src);
    if (null != resWidenReference)
      return resWidenReference;
    final Type resNarrowReference = narrowReference(tab, paths, tgt, src);
    if (null != resNarrowReference)
      return resNarrowReference;
    return null;
  }

  /**
   * Perform identity conversion. Assumes that src and tgt are either
   * not aliases, or if aliases, are already resolved.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25209">JLS 2 &sect;5.1.1</a>
   */
  public static Type convertIdentity(final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = isIdentical(tgt, src) ? src : null;
    assert null == result || JavaEntities.isGeneralRValueT(result);
    return result;
  }

  /**
   * Perform method invocation conversion. Assumes that src and tgt
   * are either not aliases, or if aliases, are already resolved.  May
   * resolve other aliases, such as supertypes, method parameter and
   * return types, etc.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#12687">JLS 2 &sect;5.3</a>
   */
  public static Type convertParameterPassing(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src) : "tgt == " + tgt + ", src == " + src;
    final Type result = convertParameterPassingInternal(tab, paths, tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result);
    return result;
  }

  private static Type convertParameterPassingInternal(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    if (isIdentical(tgt, src) || isWiderPrimitive(tgt, src) || isWiderReference(tab, paths, tgt, src))
      return tgt;
    return null;
  }

  /**
   * Perform string conversion. May resolve JavaEntities.tString(tab)
   * if that is an alias.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#176886">JLS 2 &sect;5.1.6</a>
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#186035">JLS 2 &sect;5.4</a>
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/expressions.doc.html#39990">JLS 2 &sect;15.18.1</a>
   */
  public static Type convertString(final SymbolTable tab, final Type src) {
    assert JavaEntities.isGeneralRValueT(src);
    final Type result = convertStringInternal(tab, src);
    assert null == result || JavaEntities.isWrappedRValueT(result);
    return result;
  }

  private static Type convertStringInternal(final SymbolTable tab, final Type src) {
    final Type tgt = JavaEntities.tString(tab);
    if (src.hasConstant()) {
      if (JavaEntities.isNullT(src))
        return tgt.annotate().constant("null");
      return tgt.annotate().constant(src.getConstant().getValue().toString());
    }
    return tgt;
  }

  public static boolean isAssignable(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    return null != convertAssigning(tab, paths, tgt, src);
  }

  public static boolean isCastable(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    return null != convertCasting(tab, paths, tgt, src);
  }

  public static boolean isIdentical(final Type x, final Type y) {
    if (x.isVoid() || y.isVoid())
      return x.isVoid() && y.isVoid();
    assert JavaEntities.isGeneralRValueT(x) && JavaEntities.isGeneralRValueT(y);
    final Type rawX = JavaEntities.resolveToRawRValue(x);
    final Type rawY = JavaEntities.resolveToRawRValue(y);
    if (rawX.isArray()) {
      if (!rawY.isArray())
        return false;
      final Type elemX = JavaEntities.arrayElementType(rawX.toArray());
      final Type elemY = JavaEntities.arrayElementType(rawY.toArray());
      return isIdentical(elemX, elemY);
    }
    return rawX == rawY;
  }

  public static boolean isNarrowerPrimitive(final Type tgt, final Type src) {
    return null != narrowPrimitive(tgt, src);
  }

  public static boolean isNarrowerReference(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    return null != narrowReference(tab, paths, tgt, src);
  }

  public static boolean isParameterPassable(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    return null != convertParameterPassing(tab, paths, tgt, src);
  }

  public static boolean isPromotableBinaryNumeric(final Type other, final Type src) {
    final Type t1 = promoteBinaryNumeric(other, src);
    final Type t2 = promoteBinaryNumeric(src, other);
    return null != t1 && null != t2;
  }

  /**
   * Is src return-type substitutable for tgt? This method implements
   * Java 3 Language Specification &sect;8.4.5, unlike the rest of
   * this type checker, which deals with Java 2 only.
   */
  public static boolean isReturnTypeSubstitutable(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    if (null == tgt || null == src)
      return null == tgt && null == src;
    if (JavaEntities.isPrimitiveT(src))
      return isIdentical(src, tgt);
    if (JavaEntities.isReferenceT(src))
      return isIdentical(src, tgt) || isWiderReference(tab, paths, src, tgt); //contravariant
    if (src.isVoid())
      return tgt.isVoid();
    assert false;
    return false;
  }

  public static boolean isWiderPrimitive(final Type tgt, final Type src) {
    return null != widenPrimitive(tgt, src);
  }

  public static boolean isWiderReference(final SymbolTable tab, final List<File> paths,
      final Type tgt, final Type src) {
    return null != widenReference(tab, paths, tgt, src);
  }

  /**
   * Perform narrowing primitive conversion.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25363">JLS 2 &sect;5.1.3</a>
   */
  public static strictfp Type narrowPrimitive(final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = narrowPrimitiveInternal(tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result) && JavaEntities.resolveToRawRValue(result).isNumber();
    return result;
  }
  
  private static strictfp Type narrowPrimitiveInternal(final Type tgt,
      final Type src) {
    final Type tgtRaw = JavaEntities.resolveToRawRValue(tgt);
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    if (!srcRaw.isNumber() || !tgtRaw.isNumber())
      return null;
    final NumberT srcNum = (NumberT) srcRaw, tgtNum = (NumberT) tgtRaw;
    final NumberT.Kind srcKind = srcNum.getKind(), tgtKind = tgtNum.getKind();
    switch (srcKind) {
    case BYTE:
      if (NumberT.Kind.CHAR != tgtKind)
        return null;
      break;
    case SHORT:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.CHAR != tgtKind)
        return null;
      break;
    case CHAR:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.SHORT != tgtKind)
        return null;
      break;
    case INT:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.SHORT != tgtKind
          && NumberT.Kind.CHAR != tgtKind)
        return null;
      break;
    case LONG:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.SHORT != tgtKind
          && NumberT.Kind.CHAR != tgtKind && NumberT.Kind.INT != tgtKind)
        return null;
      break;
    case FLOAT:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.SHORT != tgtKind
          && NumberT.Kind.CHAR != tgtKind && NumberT.Kind.INT != tgtKind
          && NumberT.Kind.LONG != tgtKind)
        return null;
      break;
    case DOUBLE:
      if (NumberT.Kind.BYTE != tgtKind && NumberT.Kind.SHORT != tgtKind
          && NumberT.Kind.CHAR != tgtKind && NumberT.Kind.INT != tgtKind
          && NumberT.Kind.LONG != tgtKind && NumberT.Kind.FLOAT != tgtKind)
        return null;
    }
    if (src.hasConstant()) {
      final Object obj;
      switch (srcKind) {
      case BYTE: {
        final byte v = ((Byte) src.getConstant().getValue()).byteValue();
        switch (tgtKind) {
        case CHAR: obj = new Character((char) v);  break;
        default: obj = null;
        }
        break;
      }
      case SHORT: {
        final short v = ((Short) src.getConstant().getValue()).shortValue();
        switch (tgtKind) {
        case BYTE: obj = new Byte((byte) v);       break;
        case CHAR: obj = new Character((char) v);  break;
        default: obj = null;
        }
        break;
      }
      case CHAR: {
        final char v = ((Character) src.getConstant().getValue()).charValue();
        switch (tgtKind) {
        case BYTE:  obj = new Byte((byte) v);      break;
        case SHORT: obj = new Short((short) v);    break;
        default: obj = null;
        }
        break;
      }
      case INT: {
        final int v = ((Integer) src.getConstant().getValue()).intValue();
        switch (tgtKind) {
        case BYTE:  obj = new Byte((byte) v);      break;
        case SHORT: obj = new Short((short) v);    break;
        case CHAR:  obj = new Character((char) v); break;
        default: obj = null;
        }
        break;
      }
      case LONG: {
        final long v = ((Long) src.getConstant().getValue()).longValue();
        switch (tgtKind) {
        case BYTE:  obj = new Byte((byte) v);      break;
        case SHORT: obj = new Short((short) v);    break;
        case CHAR:  obj = new Character((char) v); break;
        case INT:   obj = new Integer((int) v);    break;
        default: obj = null;
        }
        break;
      }
      case FLOAT: {
        final float v = ((Float) src.getConstant().getValue()).floatValue();
        switch (tgtKind) {
        case BYTE:  obj = new Byte((byte) v);      break;
        case SHORT: obj = new Short((short) v);    break;
        case CHAR:  obj = new Character((char) v); break;
        case INT:   obj = new Integer((int) v);    break;
        case LONG:  obj = new Long((long) v);      break;
        default: obj = null;
        }
        break;
      }
      case DOUBLE: {
        final double v = ((Double) src.getConstant().getValue()).doubleValue();
        switch (tgtKind) {
        case BYTE:  obj = new Byte((byte) v);      break;
        case SHORT: obj = new Short((short) v);    break;
        case CHAR:  obj = new Character((char) v); break;
        case INT:   obj = new Integer((int) v);    break;
        case LONG:  obj = new Long((long) v);      break;
        case FLOAT: obj = new Float((float) v);    break;
        default: obj = null;
        }
        break;
      }
      default: {
        obj = null;
        break;
      }
      }
      if (null == obj)
        throw new Error();
      return tgtRaw.annotate().constant(obj);
    }
    return tgt;
  }

  /**
   * Perform narrowing reference conversion. Assumes that src and tgt
   * are either not aliases, or if aliases, are already resolved. May
   * resolve other aliases, such as supertypes, method parameter and
   * return types, etc.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25379">JLS 2 &sect;5.1.5</a>
   */
  public static Type narrowReference(final SymbolTable tab, final List<File> paths, final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = narrowReferenceInternal(tab, paths, tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result)
        && !JavaEntities.isPrimitiveT(JavaEntities.resolveToRawRValue(result));
    return result;
  }

  private static Type narrowReferenceInternal(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    if (isIdentical(tgt, src))
      return null; // an identity conversion is not a narrowing conversion
    final Type tgtRaw = JavaEntities.resolveToRawRValue(tgt);
    if (isIdentical(JavaEntities.tObject(tab), src))
      if (JavaEntities.isWrappedClassT(tgt)
          || JavaEntities.isWrappedInterfaceT(tgt)
          || tgtRaw.isArray())
        return tgt;
    if (JavaEntities.isWrappedClassT(src) || JavaEntities.isWrappedInterfaceT(src))
      for (final Iterator<Type> i = new SuperTypesIter(tab, paths, src); i.hasNext();)
        if (isIdentical(tgt, i.next()))
          return null;
    boolean tgtInheritsFromSrc = false;
    if (JavaEntities.isWrappedClassT(tgt) || JavaEntities.isWrappedInterfaceT(tgt))
      for (final Iterator<Type> i = new SuperTypesIter(tab, paths, tgt); i.hasNext();)
        if (isIdentical(i.next(), src)) {
          tgtInheritsFromSrc = true;
          break;
        }
    if (JavaEntities.isWrappedClassT(src)) {
      if (JavaEntities.isWrappedClassT(tgt) && tgtInheritsFromSrc)
        return tgt;
      if (JavaEntities.isWrappedInterfaceT(tgt)
          && !src.hasAttribute(JavaEntities.nameToModifier("final")))
        return tgt;
    }
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    if (JavaEntities.isWrappedInterfaceT(src)) {
      if (JavaEntities.isWrappedClassT(tgt))
        if (tgtInheritsFromSrc
            || !tgt.hasAttribute(JavaEntities.nameToModifier("final")))
          return tgt;
      if (JavaEntities.isWrappedInterfaceT(tgt)) {
        final List<Type> srcMethods = ((InterfaceT) srcRaw).getMethods();
        final List<Type> tgtMethods = ((InterfaceT) tgtRaw).getMethods();
        if (100 < srcMethods.size() * tgtMethods.size())
          throw new Error("implement sub-quadratic algorithm here");
        for (final Type wrappedMethA : srcMethods)
          for (final Type wrappedMethB : tgtMethods) {
            final MethodT methA = wrappedMethA.toMethod();
            final MethodT methB = wrappedMethB.toMethod();
            if (methA.getName().equals(methB.getName())
                && !isIdentical(methA.getResult(), methB.getResult())) {
              final List<Type> lParamA = methA.getParameters();
              final List<Type> lParamB = methB.getParameters();
              if (lParamA.size() == lParamB.size()) {
                final Iterator<Type> iParamA = lParamA.iterator();
                final Iterator<Type> iParamB = lParamB.iterator();
                boolean sameSignature = true;
                while (sameSignature && iParamA.hasNext()) {
                  final Type a = JavaEntities.dereference(iParamA.next());
                  final Type b = JavaEntities.dereference(iParamB.next());
                  sameSignature = isIdentical(a, b);
                }
                if (sameSignature)
                  return null;
              }
            }
          }
        return tgt;
      }
    }
    if (tgtRaw.isArray() && srcRaw.isArray()) {
      final Type tgtElem = JavaEntities.arrayElementType(tgtRaw.toArray());
      final Type srcElem = JavaEntities.arrayElementType(srcRaw.toArray());
      if (isNarrowerReference(tab, paths, tgtElem, srcElem))
        return tgt;
    }
    return null;
  }

  /**
   * Perform binary numeric promotion. Given a binary expression "a op
   * b", this method should be called twice: once with src=a and
   * other=b, and once with src=b and other=a.
   * 
   * @param src The type of the operand that is being promoted.
   * @param other The type of the other operand.
   * @return The converted type of the src operand, or null if this kind of
   *         conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#170983">JLS 2 &sect;5.6.2</a>
   */
  public static Type promoteBinaryNumeric(final Type other, final Type src) {
    assert JavaEntities.isGeneralRValueT(other) && JavaEntities.isGeneralRValueT(src);
    final Type result = promoteBinaryNumericInternal(other, src);
    assert null == result || JavaEntities.isGeneralRValueT(result)
        && JavaEntities.resolveToRawRValue(result).isNumber();
    return result;
  }

  private static Type promoteBinaryNumericInternal(final Type other, final Type src) {
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    final Type otherRaw = JavaEntities.resolveToRawRValue(other);
    if (!srcRaw.isNumber() || !otherRaw.isNumber())
      return null;
    final NumberT srcNum = (NumberT) srcRaw, otherNum = (NumberT) otherRaw;
    final NumberT.Kind srcKind = srcNum.getKind(),otherKind = otherNum.getKind();
    switch (otherKind) {
    case DOUBLE:
      switch (srcKind) {
      case DOUBLE:
        return src;
      }
      return widenPrimitive(other, src);
    case FLOAT:
      switch (srcKind) {
      case DOUBLE:
      case FLOAT:
        return src;
      }
      return widenPrimitive(other, src);
    case LONG:
      switch (srcKind) {
      case DOUBLE:
      case FLOAT:
      case LONG:
        return src;
      }
      return widenPrimitive(other, src);
    default:
      switch (srcKind) {
      case DOUBLE:
      case FLOAT:
      case LONG:
      case INT:
        return src;
      }
      return widenPrimitive(JavaEntities.nameToBaseType("int"), src);
    }
  }

  /**
   * Perform unary numeric promotion.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#170952">JLS 2 &sect;5.6.1</a>
   */
  public static Type promoteUnaryNumeric(final Type src) {
    assert JavaEntities.isGeneralRValueT(src);
    final Type result = promoteUnaryNumericInternal(src);
    assert null == result || JavaEntities.isGeneralRValueT(result)
        && JavaEntities.resolveToRawRValue(result).isNumber();
    return result;
  }

  private static Type promoteUnaryNumericInternal(final Type src) {
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    if (srcRaw.isNumber()) {
      final NumberT.Kind srcKind = ((NumberT) srcRaw).getKind();
      final Type tgt = JavaEntities.nameToBaseType("int");
      switch (srcKind) {
      case BYTE:
      case SHORT:
      case CHAR:
        return widenPrimitive(tgt, src);
      case INT:
      case LONG:
      case FLOAT:
      case DOUBLE:
        return src;
      }
    }
    return null;
  }

  /**
   * Perform widening primitive conversion.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25214">JLS 2 &sect;5.1.2</a>
   */
  public static strictfp Type widenPrimitive(final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(tgt) && JavaEntities.isGeneralRValueT(src);
    final Type result = widenPrimitiveInternal(tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result)
        && JavaEntities.resolveToRawRValue(result).isNumber();
    return result;
  }

  private static strictfp Type widenPrimitiveInternal(final Type tgt,
      final Type src) {
    final Type tgtRaw = JavaEntities.resolveToRawRValue(tgt);
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    if (!JavaEntities.isPrimitiveT(srcRaw) || !JavaEntities.isPrimitiveT(tgtRaw))
      return null;
    if (srcRaw.isBoolean() || tgtRaw.isBoolean())
      return null;
    final NumberT srcNum = (NumberT) srcRaw, tgtNum = (NumberT) tgtRaw;
    final NumberT.Kind srcKind = srcNum.getKind(), tgtKind = tgtNum.getKind();
    switch (srcKind) {
    case BYTE:
      if (NumberT.Kind.SHORT != tgtKind && NumberT.Kind.INT != tgtKind
          && NumberT.Kind.LONG != tgtKind && NumberT.Kind.FLOAT != tgtKind
          && NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case SHORT:
      if (NumberT.Kind.INT != tgtKind && NumberT.Kind.LONG != tgtKind
          && NumberT.Kind.FLOAT != tgtKind && NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case CHAR:
      if (NumberT.Kind.INT != tgtKind && NumberT.Kind.LONG != tgtKind
          && NumberT.Kind.FLOAT != tgtKind && NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case INT:
      if (NumberT.Kind.LONG != tgtKind && NumberT.Kind.FLOAT != tgtKind
          && NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case LONG:
      if (NumberT.Kind.FLOAT != tgtKind && NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case FLOAT:
      if (NumberT.Kind.DOUBLE != tgtKind)
        return null;
      break;
    case DOUBLE:
      return null;
    }
    if (src.hasConstant()) {
      final Object obj;
      switch (srcKind) {
      case BYTE: {
        final byte v = ((Byte) src.getConstant().getValue()).byteValue();
        switch (tgtKind) {
        case SHORT:  obj = new Short(v);   break;
        case INT:    obj = new Integer(v); break;
        case LONG:   obj = new Long(v);    break;
        case FLOAT:  obj = new Float(v);   break;
        case DOUBLE: obj = new Double(v);  break;
        default: obj = null;
        }
        break;
      }
      case SHORT: {
        final short v = ((Short) src.getConstant().getValue()).shortValue();
        switch (tgtKind) {
        case INT:    obj = new Integer(v); break;
        case LONG:   obj = new Long(v);    break;
        case FLOAT:  obj = new Float(v);   break;
        case DOUBLE: obj = new Double(v);  break;
        default: obj = null;
        }
        break;
      }
      case CHAR: {
        final char v = ((Character) src.getConstant().getValue()).charValue();
        switch (tgtKind) {
        case INT:    obj = new Integer(v); break;
        case LONG:   obj = new Long(v);    break;
        case FLOAT:  obj = new Float(v);   break;
        case DOUBLE: obj = new Double(v);  break;
        default: obj = null;
        }
        break;
      }
      case INT: {
        final int v = ((Integer) src.getConstant().getValue()).intValue();
        switch (tgtKind) {
        case LONG:   obj = new Long(v);    break;
        case FLOAT:  obj = new Float(v);   break;
        case DOUBLE: obj = new Double(v);  break;
        default: obj = null;
        }
        break;
      }
      case LONG: {
        final long v = ((Long) src.getConstant().getValue()).longValue();
        switch (tgtKind) {
        case FLOAT:   obj = new Float(v);  break;
        case DOUBLE:  obj = new Double(v); break;
        default: obj = null;
        }
        break;
      }
      case FLOAT: {
        final float v = ((Float) src.getConstant().getValue()).floatValue();
        switch (tgtKind) {
        case DOUBLE:  obj = new Double(v); break;
        default: obj = null;
        }
        break;
      }
      default: {
        obj = null;
        break;
      }
      }
      if (null == obj)
        throw new Error();
      return tgtRaw.annotate().constant(obj);
    }
    return tgt;
  }

  /**
   * Perform widening reference conversion. Assumes that src and tgt
   * are either not aliases, or if aliases, are already resolved.  May
   * resolve other aliases, such as supertypes, method parameter and
   * return types, etc.
   * 
   * @return The converted type, or null if this kind of conversion does not apply.
   * @see <a href="http://java.sun.com/docs/books/jls/second_edition/html/conversions.doc.html#25215">JLS 2 &sect;5.1.4</a>
   */
  public static Type widenReference(final SymbolTable tab, final List<File> paths,
      final Type tgt, final Type src) {
    assert JavaEntities.isGeneralRValueT(src) && JavaEntities.isGeneralRValueT(tgt);
    final Type result = widenReferenceInternal(tab, paths, tgt, src);
    assert null == result || JavaEntities.isGeneralRValueT(result)
        && !JavaEntities.isPrimitiveT(JavaEntities.resolveToRawRValue(result));
    return result;
  }

  private static Type widenReferenceInternal(final SymbolTable tab,
      final List<File> paths, final Type tgt, final Type src) {
    if (isIdentical(tgt, src))
      return null; // an identity conversion is not a widening conversion
    final Type tgtRaw = JavaEntities.resolveToRawRValue(tgt);
    if (JavaEntities.isNullT(src))
      if (JavaEntities.isWrappedClassT(tgt)
          || JavaEntities.isWrappedInterfaceT(tgt)
          || tgtRaw.isArray())
        return tgt;
    final Type srcRaw = JavaEntities.resolveToRawRValue(src);
    if (srcRaw.isClass() || srcRaw.isInterface()) {
      if (isIdentical(tgt, JavaEntities.tObject(tab)))
        return tgt;
      for (Iterator<Type> i = new SuperTypesIter(tab, paths, src); i.hasNext();)
        if (isIdentical(tgt, i.next()))
          return tgt;
    }
    if (srcRaw.isArray()) {
      if (isIdentical(tgt, JavaEntities.tObjectAlias(tab))
          || isIdentical(tgt, JavaEntities.tCloneable(tab))
          || isIdentical(tgt, JavaEntities.tSerializable(tab)))
        return tgt;
      if (tgtRaw.isArray()) {
        final Type tgtElem = JavaEntities.arrayElementType(tgtRaw.toArray());
        final Type srcElem = JavaEntities.arrayElementType(srcRaw.toArray());
        if (isWiderReference(tab, paths, tgtElem, srcElem))
          return tgt;
      }
    }
    return null;
  }
}
