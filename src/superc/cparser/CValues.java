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
package superc.cparser;

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
    if (0 <= id && id < 7 || 355 < id) {
      return ValueType.NODE;
    }
    switch (id - 7) {
      case 124: // ExternalDeclarationList (131)
        // Fall through
      case 159: // DeclarationQualifierList (166)
        // Fall through
      case 160: // TypeQualifierList (167)
        // Fall through
      case 203: // StructDeclarationList (210)
        // Fall through
      case 206: // StructDefaultDeclaringList (213)
        // Fall through
      case 207: // StructDeclaringList (214)
        // Fall through
      case 213: // EnumeratorList (220)
        // Fall through
      case 219: // ParameterList (226)
        // Fall through
      case 229: // IdentifierList (236)
        // Fall through
      case 236: // MatchedInitializerList (243)
        // Fall through
      case 239: // DesignatorList (246)
        // Fall through
      case 278: // LocalLabelDeclarationList (285)
        // Fall through
      case 280: // LocalLabelList (287)
        // Fall through
      case 281: // DeclarationOrStatementList (288)
        // Fall through
      case 283: // DeclarationList (290)
        // Fall through
      case 293: // StringLiteralList (300)
        // Fall through
      case 308: // ExpressionList (315)
        // Fall through
      case 335: // AttributeSpecifierList (342)
        // Fall through
      case 339: // AttributeList (346)
        // Fall through
      case 348: // Assemblyoperands (355)
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
      case 156: // $@18 (163)
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
      case 193: // $@26 (200)
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
      case 202: // $@34 (209)
        // Fall through
      case 215: // $@35 (222)
        // Fall through
      case 216: // $@36 (223)
        // Fall through
      case 223: // $@37 (230)
        // Fall through
      case 224: // $@38 (231)
        // Fall through
      case 225: // $@39 (232)
        // Fall through
      case 226: // $@40 (233)
        // Fall through
      case 227: // $@41 (234)
        // Fall through
      case 228: // $@42 (235)
        // Fall through
      case 259: // $@43 (266)
        // Fall through
      case 260: // $@44 (267)
        // Fall through
      case 266: // $@45 (273)
        // Fall through
      case 267: // $@46 (274)
        // Fall through
      case 298: // $@47 (305)
        // Fall through
      case 299: // $@48 (306)
        return ValueType.ACTION;

      case 123: // TranslationUnit (130)
        // Fall through
      case 125: // ExternalDeclaration (132)
        // Fall through
      case 127: // FunctionDefinitionExtension (134)
        // Fall through
      case 143: // DeclarationExtension (150)
        // Fall through
      case 157: // DeclarationSpecifier (164)
        // Fall through
      case 158: // TypeSpecifier (165)
        // Fall through
      case 161: // DeclarationQualifier (168)
        // Fall through
      case 167: // BasicDeclarationSpecifier (174)
        // Fall through
      case 168: // BasicTypeSpecifier (175)
        // Fall through
      case 180: // StorageClass (187)
        // Fall through
      case 181: // BasicTypeName (188)
        // Fall through
      case 184: // ElaboratedTypeName (191)
        // Fall through
      case 204: // StructDeclarationExtension (211)
        // Fall through
      case 220: // ParameterDeclaration (227)
        // Fall through
      case 237: // DesignatedInitializer (244)
        // Fall through
      case 243: // Declarator (250)
        // Fall through
      case 244: // TypedefDeclarator (251)
        // Fall through
      case 245: // TypedefDeclaratorMain (252)
        // Fall through
      case 249: // ParenTypedefDeclarator (256)
        // Fall through
      case 252: // IdentifierDeclarator (259)
        // Fall through
      case 253: // IdentifierDeclaratorMain (260)
        // Fall through
      case 254: // UnaryIdentifierDeclarator (261)
        // Fall through
      case 255: // PostfixIdentifierDeclarator (262)
        // Fall through
      case 262: // ParenIdentifierDeclarator (269)
        // Fall through
      case 269: // PostfixingAbstractDeclarator (276)
        // Fall through
      case 274: // Statement (281)
        // Fall through
      case 282: // DeclarationOrStatement (289)
        // Fall through
      case 287: // JumpStatement (294)
        // Fall through
      case 292: // Constant (299)
        // Fall through
      case 294: // PrimaryExpression (301)
        // Fall through
      case 300: // PostfixExpression (307)
        // Fall through
      case 309: // UnaryExpression (316)
        // Fall through
      case 317: // CastExpression (324)
        // Fall through
      case 318: // MultiplicativeExpression (325)
        // Fall through
      case 319: // AdditiveExpression (326)
        // Fall through
      case 320: // ShiftExpression (327)
        // Fall through
      case 321: // RelationalExpression (328)
        // Fall through
      case 322: // EqualityExpression (329)
        // Fall through
      case 323: // AndExpression (330)
        // Fall through
      case 324: // ExclusiveOrExpression (331)
        // Fall through
      case 325: // InclusiveOrExpression (332)
        // Fall through
      case 326: // LogicalAndExpression (333)
        // Fall through
      case 327: // LogicalORExpression (334)
        // Fall through
      case 328: // ConditionalExpression (335)
        // Fall through
      case 329: // AssignmentExpression (336)
        // Fall through
      case 331: // ExpressionOpt (338)
        // Fall through
      case 332: // Expression (339)
        // Fall through
      case 333: // ConstantExpression (340)
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
    case 136: // $@1
      // Fall through
    case 137: // $@2
      // Fall through
    case 138: // $@3
      // Fall through
    case 139: // $@4
      // Fall through
    case 140: // FunctionCompoundStatement
      // Fall through
    case 141: // FunctionPrototype
      // Fall through
    case 142: // FunctionOldPrototype
      // Fall through
    case 143: // NestedFunctionDefinition
      // Fall through
    case 144: // $@5
      // Fall through
    case 145: // $@6
      // Fall through
    case 146: // $@7
      // Fall through
    case 147: // $@8
      // Fall through
    case 148: // NestedFunctionPrototype
      // Fall through
    case 149: // NestedFunctionOldPrototype
      // Fall through
    case 150: // DeclarationExtension
      // Fall through
    case 151: // Declaration
      // Fall through
    case 152: // $@9
      // Fall through
    case 153: // $@10
      // Fall through
    case 154: // $@11
      // Fall through
    case 155: // $@12
      // Fall through
    case 156: // DefaultDeclaringList
      // Fall through
    case 157: // $@13
      // Fall through
    case 158: // $@14
      // Fall through
    case 159: // $@15
      // Fall through
    case 160: // DeclaringList
      // Fall through
    case 161: // $@16
      // Fall through
    case 162: // $@17
      // Fall through
    case 163: // $@18
      // Fall through
    case 164: // DeclarationSpecifier
      // Fall through
    case 165: // TypeSpecifier
      // Fall through
    case 166: // DeclarationQualifierList
      // Fall through
    case 167: // TypeQualifierList
      // Fall through
    case 174: // BasicDeclarationSpecifier
      // Fall through
    case 175: // BasicTypeSpecifier
      // Fall through
    case 176: // SUEDeclarationSpecifier
      // Fall through
    case 177: // SUETypeSpecifier
      // Fall through
    case 178: // TypedefDeclarationSpecifier
      // Fall through
    case 179: // TypedefTypeSpecifier
      // Fall through
    case 180: // TypeofDeclarationSpecifier
      // Fall through
    case 181: // TypeofTypeSpecifier
      // Fall through
    case 182: // Typeofspecifier
      // Fall through
    case 183: // Typeofkeyword
      // Fall through
    case 191: // ElaboratedTypeName
      // Fall through
    case 192: // StructSpecifier
      // Fall through
    case 193: // $@19
      // Fall through
    case 194: // $@20
      // Fall through
    case 195: // $@21
      // Fall through
    case 196: // $@22
      // Fall through
    case 197: // $@23
      // Fall through
    case 198: // $@24
      // Fall through
    case 199: // $@25
      // Fall through
    case 200: // $@26
      // Fall through
    case 201: // UnionSpecifier
      // Fall through
    case 202: // $@27
      // Fall through
    case 203: // $@28
      // Fall through
    case 204: // $@29
      // Fall through
    case 205: // $@30
      // Fall through
    case 206: // $@31
      // Fall through
    case 207: // $@32
      // Fall through
    case 208: // $@33
      // Fall through
    case 209: // $@34
      // Fall through
    case 210: // StructDeclarationList
      // Fall through
    case 211: // StructDeclarationExtension
      // Fall through
    case 212: // StructDeclaration
      // Fall through
    case 213: // StructDefaultDeclaringList
      // Fall through
    case 214: // StructDeclaringList
      // Fall through
    case 215: // StructDeclarator
      // Fall through
    case 216: // StructIdentifierDeclarator
      // Fall through
    case 217: // BitFieldSizeOpt
      // Fall through
    case 218: // BitFieldSize
      // Fall through
    case 219: // EnumSpecifier
      // Fall through
    case 220: // EnumeratorList
      // Fall through
    case 221: // Enumerator
      // Fall through
    case 222: // $@35
      // Fall through
    case 223: // $@36
      // Fall through
    case 224: // EnumeratorValueOpt
      // Fall through
    case 225: // ParameterTypeList
      // Fall through
    case 226: // ParameterList
      // Fall through
    case 227: // ParameterDeclaration
      // Fall through
    case 230: // $@37
      // Fall through
    case 231: // $@38
      // Fall through
    case 232: // $@39
      // Fall through
    case 233: // $@40
      // Fall through
    case 234: // $@41
      // Fall through
    case 235: // $@42
      // Fall through
    case 236: // IdentifierList
      // Fall through
    case 237: // Identifier
      // Fall through
    case 238: // IdentifierOrTypedefName
      // Fall through
    case 239: // TypeName
      // Fall through
    case 240: // InitializerOpt
      // Fall through
    case 241: // Initializer
      // Fall through
    case 242: // InitializerList
      // Fall through
    case 243: // MatchedInitializerList
      // Fall through
    case 244: // DesignatedInitializer
      // Fall through
    case 246: // DesignatorList
      // Fall through
    case 248: // ObsoleteArrayDesignation
      // Fall through
    case 249: // ObsoleteFieldDesignation
      // Fall through
    case 250: // Declarator
      // Fall through
    case 251: // TypedefDeclarator
      // Fall through
    case 252: // TypedefDeclaratorMain
      // Fall through
    case 253: // ParameterTypedefDeclarator
      // Fall through
    case 254: // CleanTypedefDeclarator
      // Fall through
    case 255: // CleanPostfixTypedefDeclarator
      // Fall through
    case 256: // ParenTypedefDeclarator
      // Fall through
    case 257: // ParenPostfixTypedefDeclarator
      // Fall through
    case 258: // SimpleParenTypedefDeclarator
      // Fall through
    case 259: // IdentifierDeclarator
      // Fall through
    case 260: // IdentifierDeclaratorMain
      // Fall through
    case 261: // UnaryIdentifierDeclarator
      // Fall through
    case 262: // PostfixIdentifierDeclarator
      // Fall through
    case 263: // AttributedDeclarator
      // Fall through
    case 264: // FunctionDeclarator
      // Fall through
    case 265: // PostfixingFunctionDeclarator
      // Fall through
    case 266: // $@43
      // Fall through
    case 267: // $@44
      // Fall through
    case 268: // ArrayDeclarator
      // Fall through
    case 269: // ParenIdentifierDeclarator
      // Fall through
    case 270: // SimpleDeclarator
      // Fall through
    case 271: // OldFunctionDeclarator
      // Fall through
    case 272: // PostfixOldFunctionDeclarator
      // Fall through
    case 273: // $@45
      // Fall through
    case 274: // $@46
      // Fall through
    case 275: // AbstractDeclarator
      // Fall through
    case 276: // PostfixingAbstractDeclarator
      // Fall through
    case 277: // ParameterTypeListOpt
      // Fall through
    case 278: // ArrayAbstractDeclarator
      // Fall through
    case 279: // UnaryAbstractDeclarator
      // Fall through
    case 280: // PostfixAbstractDeclarator
      // Fall through
    case 281: // Statement
      // Fall through
    case 282: // LabeledStatement
      // Fall through
    case 283: // CompoundStatement
      // Fall through
    case 284: // LocalLabelDeclarationListOpt
      // Fall through
    case 285: // LocalLabelDeclarationList
      // Fall through
    case 286: // LocalLabelDeclaration
      // Fall through
    case 287: // LocalLabelList
      // Fall through
    case 288: // DeclarationOrStatementList
      // Fall through
    case 289: // DeclarationOrStatement
      // Fall through
    case 290: // DeclarationList
      // Fall through
    case 291: // ExpressionStatement
      // Fall through
    case 292: // SelectionStatement
      // Fall through
    case 293: // IterationStatement
      // Fall through
    case 294: // JumpStatement
      // Fall through
    case 295: // GotoStatement
      // Fall through
    case 296: // ContinueStatement
      // Fall through
    case 297: // BreakStatement
      // Fall through
    case 298: // ReturnStatement
      // Fall through
    case 299: // Constant
      // Fall through
    case 300: // StringLiteralList
      // Fall through
    case 301: // PrimaryExpression
      // Fall through
    case 302: // PrimaryIdentifier
      // Fall through
    case 303: // VariableArgumentAccess
      // Fall through
    case 304: // StatementAsExpression
      // Fall through
    case 305: // $@47
      // Fall through
    case 306: // $@48
      // Fall through
    case 307: // PostfixExpression
      // Fall through
    case 308: // Subscript
      // Fall through
    case 309: // FunctionCall
      // Fall through
    case 310: // DirectSelection
      // Fall through
    case 311: // IndirectSelection
      // Fall through
    case 312: // Increment
      // Fall through
    case 313: // Decrement
      // Fall through
    case 314: // CompoundLiteral
      // Fall through
    case 315: // ExpressionList
      // Fall through
    case 316: // UnaryExpression
      // Fall through
    case 317: // TypeCompatibilityExpression
      // Fall through
    case 318: // OffsetofExpression
      // Fall through
    case 319: // ExtensionExpression
      // Fall through
    case 320: // AlignofExpression
      // Fall through
    case 322: // LabelAddressExpression
      // Fall through
    case 324: // CastExpression
      // Fall through
    case 325: // MultiplicativeExpression
      // Fall through
    case 326: // AdditiveExpression
      // Fall through
    case 327: // ShiftExpression
      // Fall through
    case 328: // RelationalExpression
      // Fall through
    case 329: // EqualityExpression
      // Fall through
    case 330: // AndExpression
      // Fall through
    case 331: // ExclusiveOrExpression
      // Fall through
    case 332: // InclusiveOrExpression
      // Fall through
    case 333: // LogicalAndExpression
      // Fall through
    case 334: // LogicalORExpression
      // Fall through
    case 335: // ConditionalExpression
      // Fall through
    case 336: // AssignmentExpression
      // Fall through
    case 337: // AssignmentOperator
      // Fall through
    case 338: // ExpressionOpt
      // Fall through
    case 339: // Expression
      // Fall through
    case 340: // ConstantExpression
      // Fall through
    case 341: // AttributeSpecifierListOpt
      // Fall through
    case 342: // AttributeSpecifierList
      // Fall through
    case 343: // AttributeSpecifier
      // Fall through
    case 346: // AttributeList
      // Fall through
    case 349: // AssemblyDefinition
      // Fall through
    case 350: // AssemblyExpression
      // Fall through
    case 351: // AssemblyExpressionOpt
      // Fall through
    case 352: // AssemblyStatement
      // Fall through
    case 353: // Assemblyargument
      // Fall through
    case 354: // AssemblyoperandsOpt
      // Fall through
    case 355: // Assemblyoperands
      // Fall through
    case 356: // Assemblyoperand
      // Fall through
    case 357: // AssemblyclobbersOpt
      // Fall through
    case 358: // Assemblyclobbers
      // Fall through
    case 359: // AssemblyGotoargument
      // Fall through
    case 360: // AssemblyJumpLabels
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
