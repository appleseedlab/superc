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
    if (0 <= id && id < 131 || 351 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 33: // DeclarationQualifierList (164)
        // Fall through
      case 34: // TypeQualifierList (165)
        // Fall through
      case 73: // StructDeclarationList (204)
        // Fall through
      case 75: // StructDefaultDeclaringList (206)
        // Fall through
      case 76: // StructDeclaringList (207)
        // Fall through
      case 82: // EnumeratorList (213)
        // Fall through
      case 88: // ParameterList (219)
        // Fall through
      case 98: // IdentifierList (229)
        // Fall through
      case 105: // MatchedInitializerList (236)
        // Fall through
      case 108: // DesignatorList (239)
        // Fall through
      case 149: // LocalLabelDeclarationList (280)
        // Fall through
      case 151: // LocalLabelList (282)
        // Fall through
      case 152: // DeclarationOrStatementList (283)
        // Fall through
      case 154: // DeclarationList (285)
        // Fall through
      case 164: // StringLiteralListString (295)
        // Fall through
      case 165: // StringLiteralList (296)
        // Fall through
      case 180: // ExpressionList (311)
        // Fall through
      case 207: // AttributeSpecifierList (338)
        // Fall through
      case 211: // AttributeList (342)
        // Fall through
      case 220: // Assemblyoperands (351)
        return ValueType.LIST;

      case 5: // $@1 (136)
        // Fall through
      case 6: // $@2 (137)
        // Fall through
      case 7: // $@3 (138)
        // Fall through
      case 8: // $@4 (139)
        // Fall through
      case 13: // $@5 (144)
        // Fall through
      case 14: // $@6 (145)
        // Fall through
      case 15: // $@7 (146)
        // Fall through
      case 16: // $@8 (147)
        // Fall through
      case 21: // $@9 (152)
        // Fall through
      case 22: // $@10 (153)
        // Fall through
      case 23: // $@11 (154)
        // Fall through
      case 24: // $@12 (155)
        // Fall through
      case 26: // $@13 (157)
        // Fall through
      case 27: // $@14 (158)
        // Fall through
      case 28: // $@15 (159)
        // Fall through
      case 30: // $@16 (161)
        // Fall through
      case 60: // $@17 (191)
        // Fall through
      case 61: // $@18 (192)
        // Fall through
      case 62: // $@19 (193)
        // Fall through
      case 63: // $@20 (194)
        // Fall through
      case 65: // $@21 (196)
        // Fall through
      case 66: // $@22 (197)
        // Fall through
      case 67: // $@23 (198)
        // Fall through
      case 68: // $@24 (199)
        // Fall through
      case 69: // $@25 (200)
        // Fall through
      case 70: // $@26 (201)
        // Fall through
      case 71: // $@27 (202)
        // Fall through
      case 72: // $@28 (203)
        // Fall through
      case 84: // $@29 (215)
        // Fall through
      case 85: // $@30 (216)
        // Fall through
      case 92: // $@31 (223)
        // Fall through
      case 93: // $@32 (224)
        // Fall through
      case 94: // $@33 (225)
        // Fall through
      case 95: // $@34 (226)
        // Fall through
      case 96: // $@35 (227)
        // Fall through
      case 97: // $@36 (228)
        // Fall through
      case 128: // $@37 (259)
        // Fall through
      case 129: // $@38 (260)
        // Fall through
      case 135: // $@39 (266)
        // Fall through
      case 136: // $@40 (267)
        // Fall through
      case 146: // $@41 (277)
        // Fall through
      case 147: // $@42 (278)
        // Fall through
      case 170: // $@43 (301)
        // Fall through
      case 171: // $@44 (302)
        return ValueType.ACTION;

      case 58: // ElaboratedTypeName (189)
        // Fall through
      case 106: // DesignatedInitializer (237)
        // Fall through
      case 163: // Constant (294)
        // Fall through
      case 166: // PrimaryExpression (297)
        // Fall through
      case 172: // PostfixExpression (303)
        // Fall through
      case 181: // UnaryExpression (312)
        // Fall through
      case 189: // CastExpression (320)
        // Fall through
      case 190: // MultiplicativeExpression (321)
        // Fall through
      case 191: // AdditiveExpression (322)
        // Fall through
      case 192: // ShiftExpression (323)
        // Fall through
      case 193: // RelationalExpression (324)
        // Fall through
      case 194: // EqualityExpression (325)
        // Fall through
      case 195: // AndExpression (326)
        // Fall through
      case 196: // ExclusiveOrExpression (327)
        // Fall through
      case 197: // InclusiveOrExpression (328)
        // Fall through
      case 198: // LogicalAndExpression (329)
        // Fall through
      case 199: // LogicalORExpression (330)
        // Fall through
      case 200: // ConditionalExpression (331)
        // Fall through
      case 201: // AssignmentExpression (332)
        // Fall through
      case 203: // ExpressionOpt (334)
        // Fall through
      case 204: // Expression (335)
        // Fall through
      case 205: // ConstantExpression (336)
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
    case 143: // NestedFunctionDefinition
      // Fall through
    case 274: // Statement
      // Fall through
    case 275: // LabeledStatement
      // Fall through
    case 276: // CompoundStatement
      // Fall through
    case 150: // DeclarationExtension
      // Fall through
    case 151: // Declaration
      // Fall through
    case 279: // LocalLabelDeclarationListOpt
      // Fall through
    case 280: // LocalLabelDeclarationList
      // Fall through
    case 281: // LocalLabelDeclaration
      // Fall through
    case 282: // LocalLabelList
      // Fall through
    case 283: // DeclarationOrStatementList
      // Fall through
    case 284: // DeclarationOrStatement
      // Fall through
    case 285: // DeclarationList
      // Fall through
    case 286: // ExpressionStatement
      // Fall through
    case 287: // SelectionStatement
      // Fall through
    case 288: // IterationStatement
      // Fall through
    case 289: // JumpStatement
      // Fall through
    case 290: // GotoStatement
      // Fall through
    case 291: // ContinueStatement
      // Fall through
    case 292: // BreakStatement
      // Fall through
    case 293: // ReturnStatement
      return true;

    default:
      return false;
    }
  }

  public boolean changeName(int id) {
    switch(id) {
    case 140: // FunctionCompoundStatement
      return true;

    default:
      return false;
    }
  }

  public String newName(int id) {
    switch(id) {
    case 140: // FunctionCompoundStatement
      return "CompoundStatement";

    default:
      return null;
    }
  }


}
