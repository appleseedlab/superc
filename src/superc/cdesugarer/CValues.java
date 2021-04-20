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
    if (0 <= id && id < 131 || 342 < id) {
      return ValueType.NODE;
    }
    switch (id - 131) {
      case 0: // ExternalDeclarationList (131)
        // Fall through
      case 30: // DeclarationQualifierList (161)
        // Fall through
      case 31: // TypeQualifierList (162)
        // Fall through
      case 57: // StructDeclarationList (188)
        // Fall through
      case 59: // StructDefaultDeclaringList (190)
        // Fall through
      case 60: // StructDeclaringList (191)
        // Fall through
      case 67: // EnumeratorList (198)
        // Fall through
      case 73: // ParameterList (204)
        // Fall through
      case 83: // IdentifierList (214)
        // Fall through
      case 90: // MatchedInitializerList (221)
        // Fall through
      case 93: // DesignatorList (224)
        // Fall through
      case 131: // SwitchLabeledStatementList (262)
        // Fall through
      case 137: // LocalLabelDeclarationList (268)
        // Fall through
      case 139: // LocalLabelList (270)
        // Fall through
      case 140: // DeclarationOrStatementList (271)
        // Fall through
      case 142: // DeclarationList (273)
        // Fall through
      case 154: // StringLiteralListString (285)
        // Fall through
      case 155: // StringLiteralList (286)
        // Fall through
      case 170: // ExpressionList (301)
        // Fall through
      case 198: // AttributeSpecifierList (329)
        // Fall through
      case 202: // AttributeList (333)
        // Fall through
      case 211: // Assemblyoperands (342)
        return ValueType.LIST;

      case 5: // $@1 (136)
        // Fall through
      case 6: // $@2 (137)
        // Fall through
      case 11: // $@3 (142)
        // Fall through
      case 12: // $@4 (143)
        // Fall through
      case 13: // $@5 (144)
        // Fall through
      case 18: // $@6 (149)
        // Fall through
      case 19: // $@7 (150)
        // Fall through
      case 20: // $@8 (151)
        // Fall through
      case 21: // $@9 (152)
        // Fall through
      case 23: // $@10 (154)
        // Fall through
      case 24: // $@11 (155)
        // Fall through
      case 25: // $@12 (156)
        // Fall through
      case 27: // $@13 (158)
        // Fall through
      case 69: // $@14 (200)
        // Fall through
      case 70: // $@15 (201)
        // Fall through
      case 77: // $@16 (208)
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
      case 113: // $@22 (244)
        // Fall through
      case 114: // $@23 (245)
        // Fall through
      case 120: // $@24 (251)
        // Fall through
      case 121: // $@25 (252)
        // Fall through
      case 133: // $@26 (264)
        // Fall through
      case 134: // $@27 (265)
        // Fall through
      case 146: // $@28 (277)
        // Fall through
      case 147: // $@29 (278)
        // Fall through
      case 160: // $@30 (291)
        // Fall through
      case 161: // $@31 (292)
        return ValueType.ACTION;

      case 91: // DesignatedInitializer (222)
        // Fall through
      case 156: // PrimaryExpression (287)
        // Fall through
      case 162: // PostfixExpression (293)
        // Fall through
      case 171: // UnaryExpression (302)
        // Fall through
      case 180: // CastExpression (311)
        // Fall through
      case 181: // MultiplicativeExpression (312)
        // Fall through
      case 182: // AdditiveExpression (313)
        // Fall through
      case 183: // ShiftExpression (314)
        // Fall through
      case 184: // RelationalExpression (315)
        // Fall through
      case 185: // EqualityExpression (316)
        // Fall through
      case 186: // AndExpression (317)
        // Fall through
      case 187: // ExclusiveOrExpression (318)
        // Fall through
      case 188: // InclusiveOrExpression (319)
        // Fall through
      case 189: // LogicalAndExpression (320)
        // Fall through
      case 190: // LogicalORExpression (321)
        // Fall through
      case 191: // ConditionalExpression (322)
        // Fall through
      case 192: // AssignmentExpression (323)
        // Fall through
      case 194: // ExpressionOpt (325)
        // Fall through
      case 195: // Expression (326)
        // Fall through
      case 196: // ConstantExpression (327)
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
    case 259: // Statement
      // Fall through
    case 132: // ExternalDeclaration
      // Fall through
    case 260: // LabeledStatement
      // Fall through
    case 133: // EmptyDefinition
      // Fall through
    case 261: // SwitchLabeledStatement
      // Fall through
    case 134: // FunctionDefinitionExtension
      // Fall through
    case 135: // FunctionDefinition
      // Fall through
    case 263: // CompoundStatement
      // Fall through
    case 139: // FunctionPrototype
      // Fall through
    case 267: // LocalLabelDeclarationListOpt
      // Fall through
    case 268: // LocalLabelDeclarationList
      // Fall through
    case 141: // NestedFunctionDefinition
      // Fall through
    case 269: // LocalLabelDeclaration
      // Fall through
    case 270: // LocalLabelList
      // Fall through
    case 271: // DeclarationOrStatementList
      // Fall through
    case 272: // DeclarationOrStatement
      // Fall through
    case 273: // DeclarationList
      // Fall through
    case 274: // ExpressionStatement
      // Fall through
    case 147: // DeclarationExtension
      // Fall through
    case 275: // SelectionStatement
      // Fall through
    case 148: // Declaration
      // Fall through
    case 276: // IterationStatement
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
    case 160: // TypeSpecifier
      // Fall through
    case 161: // DeclarationQualifierList
      // Fall through
    case 162: // TypeQualifierList
      // Fall through
    case 169: // BasicDeclarationSpecifier
      // Fall through
    case 170: // BasicTypeSpecifier
      // Fall through
    case 171: // SUEDeclarationSpecifier
      // Fall through
    case 172: // SUETypeSpecifier
      // Fall through
    case 173: // TypedefDeclarationSpecifier
      // Fall through
    case 174: // TypedefTypeSpecifier
      // Fall through
    case 175: // TypeofDeclarationSpecifier
      // Fall through
    case 176: // TypeofTypeSpecifier
      // Fall through
    case 177: // Typeofspecifier
      // Fall through
    case 178: // Typeofkeyword
      // Fall through
    case 186: // ElaboratedTypeName
      // Fall through
    case 187: // StructOrUnionSpecifier
      // Fall through
    case 188: // StructDeclarationList
      // Fall through
    case 189: // StructDeclaration
      // Fall through
    case 190: // StructDefaultDeclaringList
      // Fall through
    case 191: // StructDeclaringList
      // Fall through
    case 192: // StructDeclarator
      // Fall through
    case 196: // EnumSpecifier
      // Fall through
    case 197: // EnumSpecifierList
      // Fall through
    case 198: // EnumeratorList
      // Fall through
    case 199: // Enumerator
      return true;

    default:
      return false;
    }
  }

  public boolean changeName(int id) {
    switch(id) {
    case 138: // FunctionCompoundStatement
      return true;

    default:
      return false;
    }
  }

  public String newName(int id) {
    switch(id) {
    case 138: // FunctionCompoundStatement
      return "CompoundStatement";

    default:
      return null;
    }
  }


}
