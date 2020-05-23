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
    if (0 <= id && id < 7 || 353 < id) {
      return ValueType.NODE;
    }
    switch (id - 7) {
      case 124: // ExternalDeclarationList (131)
        // Fall through
      case 158: // DeclarationQualifierList (165)
        // Fall through
      case 159: // TypeQualifierList (166)
        // Fall through
      case 202: // StructDeclarationList (209)
        // Fall through
      case 204: // StructDefaultDeclaringList (211)
        // Fall through
      case 205: // StructDeclaringList (212)
        // Fall through
      case 211: // EnumeratorList (218)
        // Fall through
      case 217: // ParameterList (224)
        // Fall through
      case 227: // IdentifierList (234)
        // Fall through
      case 235: // MatchedInitializerList (242)
        // Fall through
      case 237: // DesignatorList (244)
        // Fall through
      case 276: // LocalLabelDeclarationList (283)
        // Fall through
      case 278: // LocalLabelList (285)
        // Fall through
      case 279: // DeclarationOrStatementList (286)
        // Fall through
      case 281: // DeclarationList (288)
        // Fall through
      case 291: // StringLiteralList (298)
        // Fall through
      case 306: // ExpressionList (313)
        // Fall through
      case 333: // AttributeSpecifierList (340)
        // Fall through
      case 337: // AttributeList (344)
        // Fall through
      case 346: // Assemblyoperands (353)
        return ValueType.LIST;

      case 0: // BREAK (7)
        // Fall through
      case 10: // RETURN (17)
        // Fall through
      case 16: // CONTINUE (23)
        // Fall through
      case 21: // GOTO (28)
        // Fall through
      case 36: // ARROW (43)
        // Fall through
      case 58: // LPAREN (65)
        // Fall through
      case 59: // RPAREN (66)
        // Fall through
      case 60: // COMMA (67)
        // Fall through
      case 63: // LBRACE (70)
        // Fall through
      case 64: // RBRACE (71)
        // Fall through
      case 65: // LBRACK (72)
        // Fall through
      case 66: // RBRACK (73)
        // Fall through
      case 67: // DOT (74)
        // Fall through
      case 80: // QUESTION (87)
        // Fall through
      case 81: // COLON (88)
        // Fall through
      case 82: // SEMICOLON (89)
        // Fall through
      case 83: // ASSIGN (90)
        return ValueType.LAYOUT;

      case 129: // $@1 (136)
        // Fall through
      case 130: // $@2 (137)
        // Fall through
      case 131: // $@3 (138)
        // Fall through
      case 132: // $@4 (139)
        // Fall through
      case 137: // $@5 (144)
        // Fall through
      case 138: // $@6 (145)
        // Fall through
      case 139: // $@7 (146)
        // Fall through
      case 140: // $@8 (147)
        // Fall through
      case 145: // $@9 (152)
        // Fall through
      case 146: // $@10 (153)
        // Fall through
      case 147: // $@11 (154)
        // Fall through
      case 148: // $@12 (155)
        // Fall through
      case 150: // $@13 (157)
        // Fall through
      case 151: // $@14 (158)
        // Fall through
      case 152: // $@15 (159)
        // Fall through
      case 154: // $@16 (161)
        // Fall through
      case 155: // $@17 (162)
        // Fall through
      case 185: // $@18 (192)
        // Fall through
      case 186: // $@19 (193)
        // Fall through
      case 187: // $@20 (194)
        // Fall through
      case 188: // $@21 (195)
        // Fall through
      case 189: // $@22 (196)
        // Fall through
      case 190: // $@23 (197)
        // Fall through
      case 191: // $@24 (198)
        // Fall through
      case 192: // $@25 (199)
        // Fall through
      case 194: // $@26 (201)
        // Fall through
      case 195: // $@27 (202)
        // Fall through
      case 196: // $@28 (203)
        // Fall through
      case 197: // $@29 (204)
        // Fall through
      case 198: // $@30 (205)
        // Fall through
      case 199: // $@31 (206)
        // Fall through
      case 200: // $@32 (207)
        // Fall through
      case 201: // $@33 (208)
        // Fall through
      case 213: // $@34 (220)
        // Fall through
      case 214: // $@35 (221)
        // Fall through
      case 221: // $@36 (228)
        // Fall through
      case 222: // $@37 (229)
        // Fall through
      case 223: // $@38 (230)
        // Fall through
      case 224: // $@39 (231)
        // Fall through
      case 225: // $@40 (232)
        // Fall through
      case 226: // $@41 (233)
        // Fall through
      case 257: // $@42 (264)
        // Fall through
      case 258: // $@43 (265)
        // Fall through
      case 264: // $@44 (271)
        // Fall through
      case 265: // $@45 (272)
        // Fall through
      case 296: // $@46 (303)
        // Fall through
      case 297: // $@47 (304)
        return ValueType.ACTION;

      case 123: // TranslationUnit (130)
        // Fall through
      case 125: // ExternalDeclaration (132)
        // Fall through
      case 127: // FunctionDefinitionExtension (134)
        // Fall through
      case 143: // DeclarationExtension (150)
        // Fall through
      case 156: // DeclarationSpecifier (163)
        // Fall through
      case 157: // TypeSpecifier (164)
        // Fall through
      case 160: // DeclarationQualifier (167)
        // Fall through
      case 166: // BasicDeclarationSpecifier (173)
        // Fall through
      case 167: // BasicTypeSpecifier (174)
        // Fall through
      case 179: // StorageClass (186)
        // Fall through
      case 180: // BasicTypeName (187)
        // Fall through
      case 183: // ElaboratedTypeName (190)
        // Fall through
      case 218: // ParameterDeclaration (225)
        // Fall through
      case 232: // DesignatedInitializer (239)
        // Fall through
      case 241: // Declarator (248)
        // Fall through
      case 242: // TypedefDeclarator (249)
        // Fall through
      case 243: // TypedefDeclaratorMain (250)
        // Fall through
      case 247: // ParenTypedefDeclarator (254)
        // Fall through
      case 250: // IdentifierDeclarator (257)
        // Fall through
      case 251: // IdentifierDeclaratorMain (258)
        // Fall through
      case 252: // UnaryIdentifierDeclarator (259)
        // Fall through
      case 253: // PostfixIdentifierDeclarator (260)
        // Fall through
      case 260: // ParenIdentifierDeclarator (267)
        // Fall through
      case 267: // PostfixingAbstractDeclarator (274)
        // Fall through
      case 272: // Statement (279)
        // Fall through
      case 280: // DeclarationOrStatement (287)
        // Fall through
      case 285: // JumpStatement (292)
        // Fall through
      case 290: // Constant (297)
        // Fall through
      case 292: // PrimaryExpression (299)
        // Fall through
      case 298: // PostfixExpression (305)
        // Fall through
      case 307: // UnaryExpression (314)
        // Fall through
      case 315: // CastExpression (322)
        // Fall through
      case 316: // MultiplicativeExpression (323)
        // Fall through
      case 317: // AdditiveExpression (324)
        // Fall through
      case 318: // ShiftExpression (325)
        // Fall through
      case 319: // RelationalExpression (326)
        // Fall through
      case 320: // EqualityExpression (327)
        // Fall through
      case 321: // AndExpression (328)
        // Fall through
      case 322: // ExclusiveOrExpression (329)
        // Fall through
      case 323: // InclusiveOrExpression (330)
        // Fall through
      case 324: // LogicalAndExpression (331)
        // Fall through
      case 325: // LogicalORExpression (332)
        // Fall through
      case 326: // ConditionalExpression (333)
        // Fall through
      case 327: // AssignmentExpression (334)
        // Fall through
      case 329: // ExpressionOpt (336)
        // Fall through
      case 330: // Expression (337)
        // Fall through
      case 331: // ConstantExpression (338)
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
    case 150: // DeclarationExtension
      // Fall through
    case 151: // Declaration
      // Fall through
    case 279: // Statement
      // Fall through
    case 280: // LabeledStatement
      // Fall through
    case 281: // CompoundStatement
      // Fall through
    case 282: // LocalLabelDeclarationListOpt
      // Fall through
    case 283: // LocalLabelDeclarationList
      // Fall through
    case 284: // LocalLabelDeclaration
      // Fall through
    case 285: // LocalLabelList
      // Fall through
    case 286: // DeclarationOrStatementList
      // Fall through
    case 287: // DeclarationOrStatement
      // Fall through
    case 288: // DeclarationList
      // Fall through
    case 289: // ExpressionStatement
      // Fall through
    case 290: // SelectionStatement
      // Fall through
    case 291: // IterationStatement
      // Fall through
    case 292: // JumpStatement
      // Fall through
    case 293: // GotoStatement
      // Fall through
    case 294: // ContinueStatement
      // Fall through
    case 295: // BreakStatement
      // Fall through
    case 296: // ReturnStatement
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
