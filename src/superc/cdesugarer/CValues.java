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
    if (0 <= id && id < 131 || 344 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 32: // DeclarationQualifierList (163)
        // Fall through
      case 33: // TypeQualifierList (164)
        // Fall through
      case 59: // StructDeclarationList (190)
        // Fall through
      case 61: // StructDefaultDeclaringList (192)
        // Fall through
      case 62: // StructDeclaringList (193)
        // Fall through
      case 69: // EnumeratorList (200)
        // Fall through
      case 75: // ParameterList (206)
        // Fall through
      case 85: // IdentifierList (216)
        // Fall through
      case 92: // MatchedInitializerList (223)
        // Fall through
      case 95: // DesignatorList (226)
        // Fall through
      case 133: // SwitchLabeledStatementList (264)
        // Fall through
      case 139: // LocalLabelDeclarationList (270)
        // Fall through
      case 141: // LocalLabelList (272)
        // Fall through
      case 142: // DeclarationOrStatementList (273)
        // Fall through
      case 144: // DeclarationList (275)
        // Fall through
      case 156: // StringLiteralListString (287)
        // Fall through
      case 157: // StringLiteralList (288)
        // Fall through
      case 172: // ExpressionList (303)
        // Fall through
      case 200: // AttributeSpecifierList (331)
        // Fall through
      case 204: // AttributeList (335)
        // Fall through
      case 213: // Assemblyoperands (344)
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
      case 71: // $@16 (202)
        // Fall through
      case 72: // $@17 (203)
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
      case 84: // $@23 (215)
        // Fall through
      case 115: // $@24 (246)
        // Fall through
      case 116: // $@25 (247)
        // Fall through
      case 122: // $@26 (253)
        // Fall through
      case 123: // $@27 (254)
        // Fall through
      case 135: // $@28 (266)
        // Fall through
      case 136: // $@29 (267)
        // Fall through
      case 148: // $@30 (279)
        // Fall through
      case 149: // $@31 (280)
        // Fall through
      case 162: // $@32 (293)
        // Fall through
      case 163: // $@33 (294)
        return ValueType.ACTION;

      case 93: // DesignatedInitializer (224)
        // Fall through
      case 158: // PrimaryExpression (289)
        // Fall through
      case 164: // PostfixExpression (295)
        // Fall through
      case 173: // UnaryExpression (304)
        // Fall through
      case 182: // CastExpression (313)
        // Fall through
      case 183: // MultiplicativeExpression (314)
        // Fall through
      case 184: // AdditiveExpression (315)
        // Fall through
      case 185: // ShiftExpression (316)
        // Fall through
      case 186: // RelationalExpression (317)
        // Fall through
      case 187: // EqualityExpression (318)
        // Fall through
      case 188: // AndExpression (319)
        // Fall through
      case 189: // ExclusiveOrExpression (320)
        // Fall through
      case 190: // InclusiveOrExpression (321)
        // Fall through
      case 191: // LogicalAndExpression (322)
        // Fall through
      case 192: // LogicalORExpression (323)
        // Fall through
      case 193: // ConditionalExpression (324)
        // Fall through
      case 194: // AssignmentExpression (325)
        // Fall through
      case 196: // ExpressionOpt (327)
        // Fall through
      case 197: // Expression (328)
        // Fall through
      case 198: // ConstantExpression (329)
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
    case 261: // Statement
      // Fall through
    case 134: // FunctionDefinitionExtension
      // Fall through
    case 262: // LabeledStatement
      // Fall through
    case 135: // FunctionDefinition
      // Fall through
    case 263: // SwitchLabeledStatement
      // Fall through
    case 265: // CompoundStatement
      // Fall through
    case 140: // FunctionPrototype
      // Fall through
    case 269: // LocalLabelDeclarationListOpt
      // Fall through
    case 142: // NestedFunctionDefinition
      // Fall through
    case 270: // LocalLabelDeclarationList
      // Fall through
    case 271: // LocalLabelDeclaration
      // Fall through
    case 272: // LocalLabelList
      // Fall through
    case 273: // DeclarationOrStatementList
      // Fall through
    case 274: // DeclarationOrStatement
      // Fall through
    case 275: // DeclarationList
      // Fall through
    case 276: // ExpressionStatement
      // Fall through
    case 149: // DeclarationExtension
      // Fall through
    case 277: // SelectionStatement
      // Fall through
    case 150: // Declaration
      // Fall through
    case 278: // IterationStatement
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
      // Fall through
    case 162: // TypeSpecifier
      // Fall through
    case 163: // DeclarationQualifierList
      // Fall through
    case 164: // TypeQualifierList
      // Fall through
    case 171: // BasicDeclarationSpecifier
      // Fall through
    case 172: // BasicTypeSpecifier
      // Fall through
    case 173: // SUEDeclarationSpecifier
      // Fall through
    case 174: // SUETypeSpecifier
      // Fall through
    case 175: // TypedefDeclarationSpecifier
      // Fall through
    case 176: // TypedefTypeSpecifier
      // Fall through
    case 177: // TypeofDeclarationSpecifier
      // Fall through
    case 178: // TypeofTypeSpecifier
      // Fall through
    case 179: // Typeofspecifier
      // Fall through
    case 180: // Typeofkeyword
      // Fall through
    case 188: // ElaboratedTypeName
      // Fall through
    case 189: // StructOrUnionSpecifier
      // Fall through
    case 190: // StructDeclarationList
      // Fall through
    case 191: // StructDeclaration
      // Fall through
    case 192: // StructDefaultDeclaringList
      // Fall through
    case 193: // StructDeclaringList
      // Fall through
    case 194: // StructDeclarator
      // Fall through
    case 198: // EnumSpecifier
      // Fall through
    case 199: // EnumSpecifierList
      // Fall through
    case 200: // EnumeratorList
      // Fall through
    case 201: // Enumerator
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
