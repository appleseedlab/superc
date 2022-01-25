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
package superc.p4parser;

import superc.core.SemanticValues;
import superc.core.ForkMergeParser.Subparser;
import xtc.tree.GNode;
import xtc.util.Pair;
/**
 * This class is generated from grammar annotations and provides semantic
 * value and action support.
 */
public class P4Values implements SemanticValues {
  private static P4Values ref;

  public static P4Values getInstance() {
    if (ref == null)
        ref = new P4Values();
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
    if (0 <= id && id < 121 || 285 < id) {
      return ValueType.NODE;
    }
    switch (id - 121) {
      case 0: // input (121)
        // Fall through
      case 7: // annotations (128)
        // Fall through
      case 10: // annotationBody (131)
        // Fall through
      case 12: // kvList (133)
        // Fall through
      case 14: // parameterList (135)
        // Fall through
      case 16: // nonEmptyParameterList (137)
        // Fall through
      case 32: // parserLocalElements (153)
        // Fall through
      case 37: // parserStates (158)
        // Fall through
      case 40: // parserStatements (161)
        // Fall through
      case 47: // selectCaseList (168)
        // Fall through
      case 51: // simpleExpressionList (172)
        // Fall through
      case 61: // controlLocalDeclarations (182)
        // Fall through
      case 70: // methodPrototypes (191)
        // Fall through
      case 89: // typeParameterList (210)
        // Fall through
      case 91: // typeArgumentList (212)
        // Fall through
      case 93: // realTypeArgumentList (214)
        // Fall through
      case 105: // structFieldList (226)
        // Fall through
      case 110: // specifiedIdentifierList (231)
        // Fall through
      case 114: // identifierList (235)
        // Fall through
      case 126: // statOrDeclList (247)
        // Fall through
      case 128: // switchCases (249)
        // Fall through
      case 135: // tablePropertyList (256)
        // Fall through
      case 137: // keyElementList (258)
        // Fall through
      case 139: // actionList (260)
        // Fall through
      case 143: // entriesList (264)
        // Fall through
      case 152: // argumentList (273)
        // Fall through
      case 153: // nonEmptyArgList (274)
        // Fall through
      case 155: // expressionList (276)
        // Fall through
      case 161: // expression (282)
        // Fall through
      case 162: // invokingExpression (283)
        // Fall through
      case 163: // nonBraceExpression (284)
        // Fall through
      case 164: // invokingNonBraceExpression (285)
        return ValueType.LIST;

      case 15: // $@1 (136)
        // Fall through
      case 20: // $@2 (141)
        // Fall through
      case 21: // $@3 (142)
        // Fall through
      case 30: // $@4 (151)
        // Fall through
      case 31: // $@5 (152)
        // Fall through
      case 35: // $@6 (156)
        // Fall through
      case 36: // $@7 (157)
        // Fall through
      case 39: // $@8 (160)
        // Fall through
      case 43: // $@9 (164)
        // Fall through
      case 56: // $@10 (177)
        // Fall through
      case 57: // $@11 (178)
        // Fall through
      case 59: // $@12 (180)
        // Fall through
      case 60: // $@13 (181)
        // Fall through
      case 65: // $@14 (186)
        // Fall through
      case 66: // $@15 (187)
        // Fall through
      case 67: // $@16 (188)
        // Fall through
      case 68: // $@17 (189)
        // Fall through
      case 72: // $@18 (193)
        // Fall through
      case 74: // $@19 (195)
        // Fall through
      case 87: // $@20 (208)
        // Fall through
      case 88: // $@21 (209)
        // Fall through
      case 97: // $@22 (218)
        // Fall through
      case 98: // $@23 (219)
        // Fall through
      case 100: // $@24 (221)
        // Fall through
      case 101: // $@25 (222)
        // Fall through
      case 103: // $@26 (224)
        // Fall through
      case 104: // $@27 (225)
        // Fall through
      case 108: // $@28 (229)
        // Fall through
      case 109: // $@29 (230)
        // Fall through
      case 125: // $@30 (246)
        // Fall through
      case 133: // $@31 (254)
        // Fall through
      case 134: // $@32 (255)
        // Fall through
      case 145: // $@33 (266)
        // Fall through
      case 151: // $@34 (272)
        // Fall through
      case 158: // $@35 (279)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // tablePropertyList
      // Fall through
    case 257: // tableProperty
      // Fall through
    case 258: // keyElementList
      // Fall through
    case 259: // keyElement
      // Fall through
    case 260: // actionList
      // Fall through
    case 261: // action
      // Fall through
    case 262: // actionRef
      // Fall through
    case 263: // entry
      // Fall through
    case 264: // entriesList
      // Fall through
    case 265: // actionDeclaration
      // Fall through
    case 266: // $@33
      // Fall through
    case 267: // variableDeclaration
      // Fall through
    case 268: // constantDeclaration
      // Fall through
    case 269: // optInitializer
      // Fall through
    case 270: // initializer
      // Fall through
    case 271: // functionDeclaration
      // Fall through
    case 272: // $@34
      // Fall through
    case 273: // argumentList
      // Fall through
    case 274: // nonEmptyArgList
      // Fall through
    case 275: // argument
      // Fall through
    case 276: // expressionList
      // Fall through
    case 278: // dot_name
      // Fall through
    case 279: // $@35
      // Fall through
    case 280: // lvalue
      // Fall through
    case 281: // lvalueExpression
      // Fall through
    case 282: // expression
      // Fall through
    case 283: // invokingExpression
      // Fall through
    case 284: // nonBraceExpression
      // Fall through
    case 285: // invokingNonBraceExpression
      // Fall through
    case 119: // start
      // Fall through
    case 120: // program
      // Fall through
    case 121: // input
      // Fall through
    case 122: // declaration
      // Fall through
    case 127: // optAnnotations
      // Fall through
    case 128: // annotations
      // Fall through
    case 129: // annotation
      // Fall through
    case 131: // annotationBody
      // Fall through
    case 133: // kvList
      // Fall through
    case 134: // kvPair
      // Fall through
    case 135: // parameterList
      // Fall through
    case 136: // $@1
      // Fall through
    case 137: // nonEmptyParameterList
      // Fall through
    case 138: // parameter
      // Fall through
    case 140: // packageTypeDeclaration
      // Fall through
    case 141: // $@2
      // Fall through
    case 142: // $@3
      // Fall through
    case 143: // instantiation
      // Fall through
    case 144: // instantiationWithAssignment
      // Fall through
    case 148: // optConstructorParameters
      // Fall through
    case 150: // parserDeclaration
      // Fall through
    case 151: // $@4
      // Fall through
    case 152: // $@5
      // Fall through
    case 153: // parserLocalElements
      // Fall through
    case 154: // parserLocalElement
      // Fall through
    case 155: // parserTypeDeclaration
      // Fall through
    case 156: // $@6
      // Fall through
    case 157: // $@7
      // Fall through
    case 158: // parserStates
      // Fall through
    case 159: // parserState
      // Fall through
    case 160: // $@8
      // Fall through
    case 161: // parserStatements
      // Fall through
    case 162: // parserStatement
      // Fall through
    case 163: // parserBlockStatement
      // Fall through
    case 164: // $@9
      // Fall through
    case 165: // transitionStatement
      // Fall through
    case 166: // stateExpression
      // Fall through
    case 167: // selectExpression
      // Fall through
    case 168: // selectCaseList
      // Fall through
    case 170: // keysetExpression
      // Fall through
    case 171: // tupleKeysetExpression
      // Fall through
    case 172: // simpleExpressionList
      // Fall through
    case 173: // reducedSimpleKeysetExpression
      // Fall through
    case 174: // simpleKeysetExpression
      // Fall through
    case 175: // valueSetDeclaration
      // Fall through
    case 176: // controlDeclaration
      // Fall through
    case 177: // $@10
      // Fall through
    case 178: // $@11
      // Fall through
    case 179: // controlTypeDeclaration
      // Fall through
    case 180: // $@12
      // Fall through
    case 181: // $@13
      // Fall through
    case 182: // controlLocalDeclarations
      // Fall through
    case 183: // controlLocalDeclaration
      // Fall through
    case 184: // controlBody
      // Fall through
    case 185: // externDeclaration
      // Fall through
    case 186: // $@14
      // Fall through
    case 187: // $@15
      // Fall through
    case 188: // $@16
      // Fall through
    case 189: // $@17
      // Fall through
    case 190: // externFunctionDeclaration
      // Fall through
    case 191: // methodPrototypes
      // Fall through
    case 193: // $@18
      // Fall through
    case 194: // methodPrototype
      // Fall through
    case 195: // $@19
      // Fall through
    case 196: // constructorMethodPrototype
      // Fall through
    case 197: // typeRef
      // Fall through
    case 198: // namedType
      // Fall through
    case 199: // prefixedType
      // Fall through
    case 200: // typeName
      // Fall through
    case 201: // tupleType
      // Fall through
    case 202: // headerStackType
      // Fall through
    case 203: // specializedType
      // Fall through
    case 206: // optTypeParameters
      // Fall through
    case 207: // typeParameters
      // Fall through
    case 208: // $@20
      // Fall through
    case 209: // $@21
      // Fall through
    case 210: // typeParameterList
      // Fall through
    case 212: // typeArgumentList
      // Fall through
    case 214: // realTypeArgumentList
      // Fall through
    case 215: // typeDeclaration
      // Fall through
    case 216: // derivedTypeDeclaration
      // Fall through
    case 217: // headerTypeDeclaration
      // Fall through
    case 218: // $@22
      // Fall through
    case 219: // $@23
      // Fall through
    case 220: // structTypeDeclaration
      // Fall through
    case 221: // $@24
      // Fall through
    case 222: // $@25
      // Fall through
    case 223: // headerUnionDeclaration
      // Fall through
    case 224: // $@26
      // Fall through
    case 225: // $@27
      // Fall through
    case 226: // structFieldList
      // Fall through
    case 227: // structField
      // Fall through
    case 228: // enumDeclaration
      // Fall through
    case 229: // $@28
      // Fall through
    case 230: // $@29
      // Fall through
    case 231: // specifiedIdentifierList
      // Fall through
    case 232: // specifiedIdentifier
      // Fall through
    case 233: // errorDeclaration
      // Fall through
    case 234: // matchKindDeclaration
      // Fall through
    case 235: // identifierList
      // Fall through
    case 236: // typedefDeclaration
      // Fall through
    case 237: // assignmentOrMethodCallStatement
      // Fall through
    case 239: // emptyStatement
      // Fall through
    case 240: // exitStatement
      // Fall through
    case 241: // returnStatement
      // Fall through
    case 242: // conditionalStatement
      // Fall through
    case 243: // directApplication
      // Fall through
    case 244: // statement
      // Fall through
    case 245: // blockStatement
      // Fall through
    case 246: // $@30
      // Fall through
    case 247: // statOrDeclList
      // Fall through
    case 248: // switchStatement
      // Fall through
    case 249: // switchCases
      // Fall through
    case 250: // switchCase
      // Fall through
    case 252: // statementOrDeclaration
      // Fall through
    case 253: // tableDeclaration
      // Fall through
    case 254: // $@31
      // Fall through
    case 255: // $@32
      return true;

    default:
      return false;
    }
  }

  public boolean changeName(int id) {
    switch(id) {
    default:
      return false;
    }
  }

  public String newName(int id) {
    switch(id) {
    default:
      return null;
    }
  }


}
