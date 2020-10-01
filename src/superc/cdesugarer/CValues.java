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
    if (0 <= id && id < 136 || 342 < id) {
      return ValueType.NODE;
    }
    switch (id - 136) {
      case 27: // DeclarationQualifierList (163)
        // Fall through
      case 28: // TypeQualifierList (164)
        // Fall through
      case 54: // StructDeclarationList (190)
        // Fall through
      case 56: // StructDefaultDeclaringList (192)
        // Fall through
      case 57: // StructDeclaringList (193)
        // Fall through
      case 64: // EnumeratorList (200)
        // Fall through
      case 70: // ParameterList (206)
        // Fall through
      case 80: // IdentifierList (216)
        // Fall through
      case 87: // MatchedInitializerList (223)
        // Fall through
      case 90: // DesignatorList (226)
        // Fall through
      case 128: // SwitchLabeledStatementList (264)
        // Fall through
      case 134: // LocalLabelDeclarationList (270)
        // Fall through
      case 136: // LocalLabelList (272)
        // Fall through
      case 137: // DeclarationOrStatementList (273)
        // Fall through
      case 139: // DeclarationList (275)
        // Fall through
      case 149: // StringLiteralListString (285)
        // Fall through
      case 150: // StringLiteralList (286)
        // Fall through
      case 165: // ExpressionList (301)
        // Fall through
      case 193: // AttributeSpecifierList (329)
        // Fall through
      case 197: // AttributeList (333)
        // Fall through
      case 206: // Assemblyoperands (342)
        return ValueType.LIST;

      case 0: // $@1 (136)
        // Fall through
      case 1: // $@2 (137)
        // Fall through
      case 2: // $@3 (138)
        // Fall through
      case 7: // $@4 (143)
        // Fall through
      case 8: // $@5 (144)
        // Fall through
      case 9: // $@6 (145)
        // Fall through
      case 10: // $@7 (146)
        // Fall through
      case 15: // $@8 (151)
        // Fall through
      case 16: // $@9 (152)
        // Fall through
      case 17: // $@10 (153)
        // Fall through
      case 18: // $@11 (154)
        // Fall through
      case 20: // $@12 (156)
        // Fall through
      case 21: // $@13 (157)
        // Fall through
      case 22: // $@14 (158)
        // Fall through
      case 24: // $@15 (160)
        // Fall through
      case 66: // $@16 (202)
        // Fall through
      case 67: // $@17 (203)
        // Fall through
      case 74: // $@18 (210)
        // Fall through
      case 75: // $@19 (211)
        // Fall through
      case 76: // $@20 (212)
        // Fall through
      case 77: // $@21 (213)
        // Fall through
      case 78: // $@22 (214)
        // Fall through
      case 79: // $@23 (215)
        // Fall through
      case 110: // $@24 (246)
        // Fall through
      case 111: // $@25 (247)
        // Fall through
      case 117: // $@26 (253)
        // Fall through
      case 118: // $@27 (254)
        // Fall through
      case 130: // $@28 (266)
        // Fall through
      case 131: // $@29 (267)
        // Fall through
      case 155: // $@30 (291)
        // Fall through
      case 156: // $@31 (292)
        return ValueType.ACTION;

      case 88: // DesignatedInitializer (224)
        // Fall through
      case 151: // PrimaryExpression (287)
        // Fall through
      case 157: // PostfixExpression (293)
        // Fall through
      case 166: // UnaryExpression (302)
        // Fall through
      case 175: // CastExpression (311)
        // Fall through
      case 176: // MultiplicativeExpression (312)
        // Fall through
      case 177: // AdditiveExpression (313)
        // Fall through
      case 178: // ShiftExpression (314)
        // Fall through
      case 179: // RelationalExpression (315)
        // Fall through
      case 180: // EqualityExpression (316)
        // Fall through
      case 181: // AndExpression (317)
        // Fall through
      case 182: // ExclusiveOrExpression (318)
        // Fall through
      case 183: // InclusiveOrExpression (319)
        // Fall through
      case 184: // LogicalAndExpression (320)
        // Fall through
      case 185: // LogicalORExpression (321)
        // Fall through
      case 186: // ConditionalExpression (322)
        // Fall through
      case 187: // AssignmentExpression (323)
        // Fall through
      case 189: // ExpressionOpt (325)
        // Fall through
      case 190: // Expression (326)
        // Fall through
      case 191: // ConstantExpression (327)
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
    case 279: // JumpStatement
      // Fall through
    case 280: // GotoStatement
      // Fall through
    case 281: // ContinueStatement
      // Fall through
    case 282: // BreakStatement
      // Fall through
    case 283: // ReturnStatement
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
