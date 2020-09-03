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
package superc.cdesugarer;

import superc.core.SemanticValues;
import superc.core.ForkMergeParser.Subparser;
import xtc.tree.GNode;
import xtc.util.Pair;
/**
 * This class is generated from grammar annotations and provides semantic
 * value and action support.
 */
public class CValues implements SemanticValues {
  private static CValues ref;

  public static CValues getInstance() {
    if (ref == null)
        ref = new CValues();
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
    if (0 <= id && id < 131 || 343 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 32: // DeclarationQualifierList (163)
        // Fall through
      case 33: // TypeQualifierList (164)
        // Fall through
      case 64: // StructDeclarationList (195)
        // Fall through
      case 66: // StructDefaultDeclaringList (197)
        // Fall through
      case 67: // StructDeclaringList (198)
        // Fall through
      case 73: // EnumeratorList (204)
        // Fall through
      case 79: // ParameterList (210)
        // Fall through
      case 89: // IdentifierList (220)
        // Fall through
      case 96: // MatchedInitializerList (227)
        // Fall through
      case 99: // DesignatorList (230)
        // Fall through
      case 141: // LocalLabelDeclarationList (272)
        // Fall through
      case 143: // LocalLabelList (274)
        // Fall through
      case 144: // DeclarationOrStatementList (275)
        // Fall through
      case 146: // DeclarationList (277)
        // Fall through
      case 156: // StringLiteralListString (287)
        // Fall through
      case 157: // StringLiteralList (288)
        // Fall through
      case 172: // ExpressionList (303)
        // Fall through
      case 199: // AttributeSpecifierList (330)
        // Fall through
      case 203: // AttributeList (334)
        // Fall through
      case 212: // Assemblyoperands (343)
        return ValueType.LIST;

      case 5: // $@1 (136)
        // Fall through
      case 6: // $@2 (137)
        // Fall through
      case 7: // $@3 (138)
        // Fall through
      case 12: // $@4 (143)
        // Fall through
      case 13: // $@5 (144)
        // Fall through
      case 14: // $@6 (145)
        // Fall through
      case 15: // $@7 (146)
        // Fall through
      case 20: // $@8 (151)
        // Fall through
      case 21: // $@9 (152)
        // Fall through
      case 22: // $@10 (153)
        // Fall through
      case 23: // $@11 (154)
        // Fall through
      case 25: // $@12 (156)
        // Fall through
      case 26: // $@13 (157)
        // Fall through
      case 27: // $@14 (158)
        // Fall through
      case 29: // $@15 (160)
        // Fall through
      case 59: // $@16 (190)
        // Fall through
      case 60: // $@17 (191)
        // Fall through
      case 61: // $@18 (192)
        // Fall through
      case 62: // $@19 (193)
        // Fall through
      case 75: // $@20 (206)
        // Fall through
      case 76: // $@21 (207)
        // Fall through
      case 83: // $@22 (214)
        // Fall through
      case 84: // $@23 (215)
        // Fall through
      case 85: // $@24 (216)
        // Fall through
      case 86: // $@25 (217)
        // Fall through
      case 87: // $@26 (218)
        // Fall through
      case 88: // $@27 (219)
        // Fall through
      case 119: // $@28 (250)
        // Fall through
      case 120: // $@29 (251)
        // Fall through
      case 126: // $@30 (257)
        // Fall through
      case 127: // $@31 (258)
        // Fall through
      case 137: // $@32 (268)
        // Fall through
      case 138: // $@33 (269)
        // Fall through
      case 162: // $@34 (293)
        // Fall through
      case 163: // $@35 (294)
        return ValueType.ACTION;

      case 57: // ElaboratedTypeName (188)
        // Fall through
      case 97: // DesignatedInitializer (228)
        // Fall through
      case 155: // Constant (286)
        // Fall through
      case 158: // PrimaryExpression (289)
        // Fall through
      case 164: // PostfixExpression (295)
        // Fall through
      case 173: // UnaryExpression (304)
        // Fall through
      case 181: // CastExpression (312)
        // Fall through
      case 182: // MultiplicativeExpression (313)
        // Fall through
      case 183: // AdditiveExpression (314)
        // Fall through
      case 184: // ShiftExpression (315)
        // Fall through
      case 185: // RelationalExpression (316)
        // Fall through
      case 186: // EqualityExpression (317)
        // Fall through
      case 187: // AndExpression (318)
        // Fall through
      case 188: // ExclusiveOrExpression (319)
        // Fall through
      case 189: // InclusiveOrExpression (320)
        // Fall through
      case 190: // LogicalAndExpression (321)
        // Fall through
      case 191: // LogicalORExpression (322)
        // Fall through
      case 192: // ConditionalExpression (323)
        // Fall through
      case 193: // AssignmentExpression (324)
        // Fall through
      case 195: // ExpressionOpt (326)
        // Fall through
      case 196: // Expression (327)
        // Fall through
      case 197: // ConstantExpression (328)
        return ValueType.PASS_THROUGH;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 130: // TranslationUnit
      // Fall through
    case 131: // ExternalDeclarationList
      // Fall through
    case 132: // ExternalDeclaration
      // Fall through
    case 133: // EmptyDefinition
      // Fall through
    case 134: // FunctionDefinitionExtension
      // Fall through
    case 135: // FunctionDefinition
      // Fall through
    case 265: // Statement
      // Fall through
    case 266: // LabeledStatement
      // Fall through
    case 267: // CompoundStatement
      // Fall through
    case 142: // NestedFunctionDefinition
      // Fall through
    case 271: // LocalLabelDeclarationListOpt
      // Fall through
    case 272: // LocalLabelDeclarationList
      // Fall through
    case 273: // LocalLabelDeclaration
      // Fall through
    case 274: // LocalLabelList
      // Fall through
    case 275: // DeclarationOrStatementList
      // Fall through
    case 276: // DeclarationOrStatement
      // Fall through
    case 149: // DeclarationExtension
      // Fall through
    case 277: // DeclarationList
      // Fall through
    case 150: // Declaration
      // Fall through
    case 278: // ExpressionStatement
      // Fall through
    case 279: // SelectionStatement
      // Fall through
    case 280: // IterationStatement
      // Fall through
    case 281: // JumpStatement
      // Fall through
    case 282: // GotoStatement
      // Fall through
    case 283: // ContinueStatement
      // Fall through
    case 284: // BreakStatement
      // Fall through
    case 285: // ReturnStatement
      return true;

    default:
      return false;
    }
  }

  public boolean changeName(int id) {
    switch(id) {
    case 139: // FunctionCompoundStatement
      return true;

    default:
      return false;
    }
  }

  public String newName(int id) {
    switch(id) {
    case 139: // FunctionCompoundStatement
      return "CompoundStatement";

    default:
      return null;
    }
  }


}
