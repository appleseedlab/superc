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
    if (0 <= id && id < 131 || 340 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 32: // DeclarationQualifierList (163)
        // Fall through
      case 33: // TypeQualifierList (164)
        // Fall through
      case 60: // StructDeclarationList (191)
        // Fall through
      case 62: // StructDefaultDeclaringList (193)
        // Fall through
      case 63: // StructDeclaringList (194)
        // Fall through
      case 70: // EnumeratorList (201)
        // Fall through
      case 76: // ParameterList (207)
        // Fall through
      case 86: // IdentifierList (217)
        // Fall through
      case 93: // MatchedInitializerList (224)
        // Fall through
      case 96: // DesignatorList (227)
        // Fall through
      case 138: // LocalLabelDeclarationList (269)
        // Fall through
      case 140: // LocalLabelList (271)
        // Fall through
      case 141: // DeclarationOrStatementList (272)
        // Fall through
      case 143: // DeclarationList (274)
        // Fall through
      case 153: // StringLiteralListString (284)
        // Fall through
      case 154: // StringLiteralList (285)
        // Fall through
      case 169: // ExpressionList (300)
        // Fall through
      case 196: // AttributeSpecifierList (327)
        // Fall through
      case 200: // AttributeList (331)
        // Fall through
      case 209: // Assemblyoperands (340)
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
      case 72: // $@16 (203)
        // Fall through
      case 73: // $@17 (204)
        // Fall through
      case 80: // $@18 (211)
        // Fall through
      case 81: // $@19 (212)
        // Fall through
      case 82: // $@20 (213)
        // Fall through
      case 83: // $@21 (214)
        // Fall through
      case 84: // $@22 (215)
        // Fall through
      case 85: // $@23 (216)
        // Fall through
      case 116: // $@24 (247)
        // Fall through
      case 117: // $@25 (248)
        // Fall through
      case 123: // $@26 (254)
        // Fall through
      case 124: // $@27 (255)
        // Fall through
      case 134: // $@28 (265)
        // Fall through
      case 135: // $@29 (266)
        // Fall through
      case 159: // $@30 (290)
        // Fall through
      case 160: // $@31 (291)
        return ValueType.ACTION;

      case 57: // ElaboratedTypeName (188)
        // Fall through
      case 94: // DesignatedInitializer (225)
        // Fall through
      case 152: // Constant (283)
        // Fall through
      case 155: // PrimaryExpression (286)
        // Fall through
      case 161: // PostfixExpression (292)
        // Fall through
      case 170: // UnaryExpression (301)
        // Fall through
      case 178: // CastExpression (309)
        // Fall through
      case 179: // MultiplicativeExpression (310)
        // Fall through
      case 180: // AdditiveExpression (311)
        // Fall through
      case 181: // ShiftExpression (312)
        // Fall through
      case 182: // RelationalExpression (313)
        // Fall through
      case 183: // EqualityExpression (314)
        // Fall through
      case 184: // AndExpression (315)
        // Fall through
      case 185: // ExclusiveOrExpression (316)
        // Fall through
      case 186: // InclusiveOrExpression (317)
        // Fall through
      case 187: // LogicalAndExpression (318)
        // Fall through
      case 188: // LogicalORExpression (319)
        // Fall through
      case 189: // ConditionalExpression (320)
        // Fall through
      case 190: // AssignmentExpression (321)
        // Fall through
      case 192: // ExpressionOpt (323)
        // Fall through
      case 193: // Expression (324)
        // Fall through
      case 194: // ConstantExpression (325)
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
    case 262: // Statement
      // Fall through
    case 135: // FunctionDefinition
      // Fall through
    case 263: // LabeledStatement
      // Fall through
    case 264: // CompoundStatement
      // Fall through
    case 268: // LocalLabelDeclarationListOpt
      // Fall through
    case 269: // LocalLabelDeclarationList
      // Fall through
    case 142: // NestedFunctionDefinition
      // Fall through
    case 270: // LocalLabelDeclaration
      // Fall through
    case 271: // LocalLabelList
      // Fall through
    case 272: // DeclarationOrStatementList
      // Fall through
    case 273: // DeclarationOrStatement
      // Fall through
    case 274: // DeclarationList
      // Fall through
    case 275: // ExpressionStatement
      // Fall through
    case 276: // SelectionStatement
      // Fall through
    case 149: // DeclarationExtension
      // Fall through
    case 277: // IterationStatement
      // Fall through
    case 150: // Declaration
      // Fall through
    case 278: // JumpStatement
      // Fall through
    case 279: // GotoStatement
      // Fall through
    case 280: // ContinueStatement
      // Fall through
    case 281: // BreakStatement
      // Fall through
    case 282: // ReturnStatement
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
