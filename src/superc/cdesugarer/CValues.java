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
    if (0 <= id && id < 131 || 345 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 33: // DeclarationQualifierList (164)
        // Fall through
      case 34: // TypeQualifierList (165)
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
      case 134: // SwitchLabeledStatementList (265)
        // Fall through
      case 140: // LocalLabelDeclarationList (271)
        // Fall through
      case 142: // LocalLabelList (273)
        // Fall through
      case 143: // DeclarationOrStatementList (274)
        // Fall through
      case 145: // DeclarationList (276)
        // Fall through
      case 157: // StringLiteralListString (288)
        // Fall through
      case 158: // StringLiteralList (289)
        // Fall through
      case 173: // ExpressionList (304)
        // Fall through
      case 201: // AttributeSpecifierList (332)
        // Fall through
      case 205: // AttributeList (336)
        // Fall through
      case 214: // Assemblyoperands (345)
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
      case 19: // $@7 (150)
        // Fall through
      case 20: // $@8 (151)
        // Fall through
      case 21: // $@9 (152)
        // Fall through
      case 22: // $@10 (153)
        // Fall through
      case 24: // $@11 (155)
        // Fall through
      case 25: // $@12 (156)
        // Fall through
      case 26: // $@13 (157)
        // Fall through
      case 28: // $@14 (159)
        // Fall through
      case 29: // $@15 (160)
        // Fall through
      case 30: // $@16 (161)
        // Fall through
      case 72: // $@17 (203)
        // Fall through
      case 73: // $@18 (204)
        // Fall through
      case 80: // $@19 (211)
        // Fall through
      case 81: // $@20 (212)
        // Fall through
      case 82: // $@21 (213)
        // Fall through
      case 83: // $@22 (214)
        // Fall through
      case 84: // $@23 (215)
        // Fall through
      case 85: // $@24 (216)
        // Fall through
      case 116: // $@25 (247)
        // Fall through
      case 117: // $@26 (248)
        // Fall through
      case 123: // $@27 (254)
        // Fall through
      case 124: // $@28 (255)
        // Fall through
      case 136: // $@29 (267)
        // Fall through
      case 137: // $@30 (268)
        // Fall through
      case 149: // $@31 (280)
        // Fall through
      case 150: // $@32 (281)
        // Fall through
      case 163: // $@33 (294)
        // Fall through
      case 164: // $@34 (295)
        return ValueType.ACTION;

      case 94: // DesignatedInitializer (225)
        // Fall through
      case 159: // PrimaryExpression (290)
        // Fall through
      case 165: // PostfixExpression (296)
        // Fall through
      case 174: // UnaryExpression (305)
        // Fall through
      case 183: // CastExpression (314)
        // Fall through
      case 184: // MultiplicativeExpression (315)
        // Fall through
      case 185: // AdditiveExpression (316)
        // Fall through
      case 186: // ShiftExpression (317)
        // Fall through
      case 187: // RelationalExpression (318)
        // Fall through
      case 188: // EqualityExpression (319)
        // Fall through
      case 189: // AndExpression (320)
        // Fall through
      case 190: // ExclusiveOrExpression (321)
        // Fall through
      case 191: // InclusiveOrExpression (322)
        // Fall through
      case 192: // LogicalAndExpression (323)
        // Fall through
      case 193: // LogicalORExpression (324)
        // Fall through
      case 194: // ConditionalExpression (325)
        // Fall through
      case 195: // AssignmentExpression (326)
        // Fall through
      case 197: // ExpressionOpt (328)
        // Fall through
      case 198: // Expression (329)
        // Fall through
      case 199: // ConstantExpression (330)
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
    case 264: // SwitchLabeledStatement
      // Fall through
    case 266: // CompoundStatement
      // Fall through
    case 140: // FunctionPrototype
      // Fall through
    case 142: // NestedFunctionDefinition
      // Fall through
    case 270: // LocalLabelDeclarationListOpt
      // Fall through
    case 271: // LocalLabelDeclarationList
      // Fall through
    case 272: // LocalLabelDeclaration
      // Fall through
    case 273: // LocalLabelList
      // Fall through
    case 274: // DeclarationOrStatementList
      // Fall through
    case 275: // DeclarationOrStatement
      // Fall through
    case 148: // DeclarationExtension
      // Fall through
    case 276: // DeclarationList
      // Fall through
    case 149: // Declaration
      // Fall through
    case 277: // ExpressionStatement
      // Fall through
    case 278: // SelectionStatement
      // Fall through
    case 279: // IterationStatement
      // Fall through
    case 282: // JumpStatement
      // Fall through
    case 283: // GotoStatement
      // Fall through
    case 284: // ContinueStatement
      // Fall through
    case 285: // BreakStatement
      // Fall through
    case 286: // ReturnStatement
      // Fall through
    case 163: // TypeSpecifier
      // Fall through
    case 164: // DeclarationQualifierList
      // Fall through
    case 165: // TypeQualifierList
      // Fall through
    case 172: // BasicDeclarationSpecifier
      // Fall through
    case 173: // BasicTypeSpecifier
      // Fall through
    case 174: // SUEDeclarationSpecifier
      // Fall through
    case 175: // SUETypeSpecifier
      // Fall through
    case 176: // TypedefDeclarationSpecifier
      // Fall through
    case 177: // TypedefTypeSpecifier
      // Fall through
    case 178: // TypeofDeclarationSpecifier
      // Fall through
    case 179: // TypeofTypeSpecifier
      // Fall through
    case 180: // Typeofspecifier
      // Fall through
    case 181: // Typeofkeyword
      // Fall through
    case 189: // ElaboratedTypeName
      // Fall through
    case 190: // StructOrUnionSpecifier
      // Fall through
    case 191: // StructDeclarationList
      // Fall through
    case 192: // StructDeclaration
      // Fall through
    case 193: // StructDefaultDeclaringList
      // Fall through
    case 194: // StructDeclaringList
      // Fall through
    case 195: // StructDeclarator
      // Fall through
    case 199: // EnumSpecifier
      // Fall through
    case 200: // EnumSpecifierList
      // Fall through
    case 201: // EnumeratorList
      // Fall through
    case 202: // Enumerator
      // Fall through
    case 221: // InitializerOpt
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
