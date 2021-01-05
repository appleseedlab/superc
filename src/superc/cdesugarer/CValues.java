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
      case 31: // DeclarationQualifierList (162)
        // Fall through
      case 32: // TypeQualifierList (163)
        // Fall through
      case 58: // StructDeclarationList (189)
        // Fall through
      case 60: // StructDefaultDeclaringList (191)
        // Fall through
      case 61: // StructDeclaringList (192)
        // Fall through
      case 68: // EnumeratorList (199)
        // Fall through
      case 74: // ParameterList (205)
        // Fall through
      case 84: // IdentifierList (215)
        // Fall through
      case 91: // MatchedInitializerList (222)
        // Fall through
      case 94: // DesignatorList (225)
        // Fall through
      case 132: // SwitchLabeledStatementList (263)
        // Fall through
      case 138: // LocalLabelDeclarationList (269)
        // Fall through
      case 140: // LocalLabelList (271)
        // Fall through
      case 141: // DeclarationOrStatementList (272)
        // Fall through
      case 143: // DeclarationList (274)
        // Fall through
      case 155: // StringLiteralListString (286)
        // Fall through
      case 156: // StringLiteralList (287)
        // Fall through
      case 171: // ExpressionList (302)
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
      case 70: // $@15 (201)
        // Fall through
      case 71: // $@16 (202)
        // Fall through
      case 78: // $@17 (209)
        // Fall through
      case 79: // $@18 (210)
        // Fall through
      case 80: // $@19 (211)
        // Fall through
      case 81: // $@20 (212)
        // Fall through
      case 82: // $@21 (213)
        // Fall through
      case 83: // $@22 (214)
        // Fall through
      case 114: // $@23 (245)
        // Fall through
      case 115: // $@24 (246)
        // Fall through
      case 121: // $@25 (252)
        // Fall through
      case 122: // $@26 (253)
        // Fall through
      case 134: // $@27 (265)
        // Fall through
      case 135: // $@28 (266)
        // Fall through
      case 147: // $@29 (278)
        // Fall through
      case 148: // $@30 (279)
        // Fall through
      case 161: // $@31 (292)
        // Fall through
      case 162: // $@32 (293)
        return ValueType.ACTION;

      case 92: // DesignatedInitializer (223)
        // Fall through
      case 157: // PrimaryExpression (288)
        // Fall through
      case 163: // PostfixExpression (294)
        // Fall through
      case 172: // UnaryExpression (303)
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
    case 260: // Statement
      // Fall through
    case 133: // EmptyDefinition
      // Fall through
    case 261: // LabeledStatement
      // Fall through
    case 134: // FunctionDefinitionExtension
      // Fall through
    case 262: // SwitchLabeledStatement
      // Fall through
    case 135: // FunctionDefinition
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
    case 148: // DeclarationExtension
      // Fall through
    case 276: // SelectionStatement
      // Fall through
    case 149: // Declaration
      // Fall through
    case 277: // IterationStatement
      // Fall through
    case 280: // JumpStatement
      // Fall through
    case 281: // GotoStatement
      // Fall through
    case 282: // ContinueStatement
      // Fall through
    case 283: // BreakStatement
      // Fall through
    case 284: // ReturnStatement
      // Fall through
    case 161: // TypeSpecifier
      // Fall through
    case 162: // DeclarationQualifierList
      // Fall through
    case 163: // TypeQualifierList
      // Fall through
    case 170: // BasicDeclarationSpecifier
      // Fall through
    case 171: // BasicTypeSpecifier
      // Fall through
    case 172: // SUEDeclarationSpecifier
      // Fall through
    case 173: // SUETypeSpecifier
      // Fall through
    case 174: // TypedefDeclarationSpecifier
      // Fall through
    case 175: // TypedefTypeSpecifier
      // Fall through
    case 176: // TypeofDeclarationSpecifier
      // Fall through
    case 177: // TypeofTypeSpecifier
      // Fall through
    case 178: // Typeofspecifier
      // Fall through
    case 179: // Typeofkeyword
      // Fall through
    case 187: // ElaboratedTypeName
      // Fall through
    case 188: // StructOrUnionSpecifier
      // Fall through
    case 189: // StructDeclarationList
      // Fall through
    case 190: // StructDeclaration
      // Fall through
    case 191: // StructDefaultDeclaringList
      // Fall through
    case 192: // StructDeclaringList
      // Fall through
    case 193: // StructDeclarator
      // Fall through
    case 197: // EnumSpecifier
      // Fall through
    case 198: // EnumSpecifierList
      // Fall through
    case 199: // EnumeratorList
      // Fall through
    case 200: // Enumerator
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
