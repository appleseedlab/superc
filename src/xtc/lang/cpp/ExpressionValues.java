/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
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
package xtc.lang.cpp;

import xtc.lang.cpp.ForkMergeParser.Subparser;
import xtc.tree.GNode;
import xtc.util.Pair;
/**
 * This class is generated from grammar annotations and provides semantic
 * value and action support.
 */
public class ExpressionValues implements SemanticValues {
  private static ExpressionValues ref;

  public static ExpressionValues getInstance() {
    if (ref == null)
        ref = new ExpressionValues();
    return ref;
  }

  public Object getValue(int id, String name, Pair<Object> values) {
    Object value;

    if (values == Pair.<Object>empty()) {
      value = GNode.create(name);

    } else {
      value = GNode.createFromPair(name, values.head(), values.tail());
    }

    return value;
  }
  public ValueType getValueType(int id) {
    if (0 <= id && id < 43) {
      return ValueType.NODE;
    }
    switch (id - 43) {
      case 0: // ARROW (43)
        // Fall through
      case 22: // LPAREN (65)
        // Fall through
      case 23: // RPAREN (66)
        // Fall through
      case 24: // COMMA (67)
        // Fall through
      case 27: // LBRACE (70)
        // Fall through
      case 28: // RBRACE (71)
        // Fall through
      case 29: // LBRACK (72)
        // Fall through
      case 30: // RBRACK (73)
        // Fall through
      case 31: // DOT (74)
        // Fall through
      case 44: // QUESTION (87)
        // Fall through
      case 45: // COLON (88)
        // Fall through
      case 46: // SEMICOLON (89)
        // Fall through
      case 47: // ASSIGN (90)
        return ValueType.LAYOUT;

      case 102: // CheckDefined (145)
        return ValueType.ACTION;

      case 85: // ConstantExpression (128)
        // Fall through
      case 86: // Constant (129)
        // Fall through
      case 89: // PrimaryExpression (132)
        // Fall through
      case 91: // UnaryExpression (134)
        // Fall through
      case 103: // MultiplicativeExpression (146)
        // Fall through
      case 104: // AdditiveExpression (147)
        // Fall through
      case 105: // ShiftExpression (148)
        // Fall through
      case 106: // RelationalExpression (149)
        // Fall through
      case 107: // EqualityExpression (150)
        // Fall through
      case 108: // BitwiseAndExpression (151)
        // Fall through
      case 110: // BitwiseXorExpression (153)
        // Fall through
      case 112: // BitwiseOrExpression (155)
        // Fall through
      case 114: // LogicalAndExpression (157)
        // Fall through
      case 116: // LogicalOrExpression (159)
        // Fall through
      case 118: // ConditionalExpression (161)
        // Fall through
      case 119: // Word (162)
        return ValueType.PASS_THROUGH;

      case 93: // UnaryMinusOp (136)
        // Fall through
      case 95: // UnaryPlusOp (138)
        // Fall through
      case 97: // LogicalNegateOp (140)
        // Fall through
      case 99: // BitwiseNegateOp (142)
        // Fall through
      case 101: // DefinedKeyword (144)
        // Fall through
      case 109: // BitwiseAndOp (152)
        // Fall through
      case 111: // BitwiseXorOp (154)
        // Fall through
      case 113: // BitwiseOrOp (156)
        // Fall through
      case 115: // LogicalAndOp (158)
        // Fall through
      case 117: // LogicalOrOp (160)
        return ValueType.VOID;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 128: // ConstantExpression
      // Fall through
    case 129: // Constant
      // Fall through
    case 161: // ConditionalExpression
      // Fall through
    case 130: // IntegerConstant
      // Fall through
    case 132: // PrimaryExpression
      // Fall through
    case 133: // PrimaryIdentifier
      // Fall through
    case 134: // UnaryExpression
      // Fall through
    case 135: // UnaryMinusExpression
      // Fall through
    case 137: // UnaryPlusExpression
      // Fall through
    case 139: // LogicalNegationExpression
      // Fall through
    case 141: // BitwiseNegationExpression
      // Fall through
    case 143: // DefinedExpression
      // Fall through
    case 145: // CheckDefined
      // Fall through
    case 146: // MultiplicativeExpression
      // Fall through
    case 147: // AdditiveExpression
      // Fall through
    case 148: // ShiftExpression
      // Fall through
    case 149: // RelationalExpression
      // Fall through
    case 150: // EqualityExpression
      // Fall through
    case 151: // BitwiseAndExpression
      // Fall through
    case 153: // BitwiseXorExpression
      // Fall through
    case 155: // BitwiseOrExpression
      // Fall through
    case 157: // LogicalAndExpression
      // Fall through
    case 159: // LogicalOrExpression
      return true;

    default:
      return false;
    }
  }

  public boolean changeName(int id) {
    switch(id) {
    default:
      return false;
    }
  }

  public String newName(int id) {
    switch(id) {
    default:
      return null;
    }
  }


}
