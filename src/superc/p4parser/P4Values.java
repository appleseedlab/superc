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
    if (0 <= id && id < 121 || 269 < id) {
      return ValueType.NODE;
    }
    switch (id - 121) {
      case 0: // input (121)
        // Fall through
      case 7: // annotations (128)
        // Fall through
      case 9: // annotationBody (130)
        // Fall through
      case 11: // kvList (132)
        // Fall through
      case 13: // parameterList (134)
        // Fall through
      case 14: // nonEmptyParameterList (135)
        // Fall through
      case 29: // parserLocalElements (150)
        // Fall through
      case 34: // parserStates (155)
        // Fall through
      case 37: // parserStatements (158)
        // Fall through
      case 44: // selectCaseList (165)
        // Fall through
      case 48: // simpleExpressionList (169)
        // Fall through
      case 56: // controlLocalDeclarations (177)
        // Fall through
      case 63: // methodPrototypes (184)
        // Fall through
      case 80: // typeParameterList (201)
        // Fall through
      case 82: // typeArgumentList (203)
        // Fall through
      case 84: // realTypeArgumentList (205)
        // Fall through
      case 94: // structFieldList (215)
        // Fall through
      case 99: // specifiedIdentifierList (220)
        // Fall through
      case 103: // identifierList (224)
        // Fall through
      case 115: // statOrDeclList (236)
        // Fall through
      case 117: // switchCases (238)
        // Fall through
      case 122: // tablePropertyList (243)
        // Fall through
      case 124: // keyElementList (245)
        // Fall through
      case 126: // actionList (247)
        // Fall through
      case 130: // entriesList (251)
        // Fall through
      case 137: // argumentList (258)
        // Fall through
      case 138: // nonEmptyArgList (259)
        // Fall through
      case 140: // expressionList (261)
        // Fall through
      case 146: // expression (267)
        // Fall through
      case 147: // invokingExpression (268)
        // Fall through
      case 148: // nonBraceExpression (269)
        return ValueType.LIST;

      case 18: // $@1 (139)
        // Fall through
      case 19: // $@2 (140)
        // Fall through
      case 27: // $@3 (148)
        // Fall through
      case 28: // $@4 (149)
        // Fall through
      case 32: // $@5 (153)
        // Fall through
      case 33: // $@6 (154)
        // Fall through
      case 36: // $@7 (157)
        // Fall through
      case 40: // $@8 (161)
        // Fall through
      case 54: // $@9 (175)
        // Fall through
      case 55: // $@10 (176)
        // Fall through
      case 60: // $@11 (181)
        // Fall through
      case 61: // $@12 (182)
        // Fall through
      case 65: // $@13 (186)
        // Fall through
      case 67: // $@14 (188)
        // Fall through
      case 88: // $@15 (209)
        // Fall through
      case 89: // $@16 (210)
        // Fall through
      case 92: // $@17 (213)
        // Fall through
      case 93: // $@18 (214)
        // Fall through
      case 97: // $@19 (218)
        // Fall through
      case 98: // $@20 (219)
        // Fall through
      case 114: // $@21 (235)
        // Fall through
      case 143: // $@22 (264)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // initializer
      // Fall through
    case 257: // functionDeclaration
      // Fall through
    case 258: // argumentList
      // Fall through
    case 259: // nonEmptyArgList
      // Fall through
    case 260: // argument
      // Fall through
    case 261: // expressionList
      // Fall through
    case 263: // dot_name
      // Fall through
    case 264: // $@22
      // Fall through
    case 265: // lvalue
      // Fall through
    case 266: // lvalueExpression
      // Fall through
    case 267: // expression
      // Fall through
    case 268: // invokingExpression
      // Fall through
    case 269: // nonBraceExpression
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
    case 130: // annotationBody
      // Fall through
    case 132: // kvList
      // Fall through
    case 133: // kvPair
      // Fall through
    case 134: // parameterList
      // Fall through
    case 135: // nonEmptyParameterList
      // Fall through
    case 136: // parameter
      // Fall through
    case 138: // packageTypeDeclaration
      // Fall through
    case 139: // $@1
      // Fall through
    case 140: // $@2
      // Fall through
    case 141: // instantiation
      // Fall through
    case 145: // optConstructorParameters
      // Fall through
    case 147: // parserDeclaration
      // Fall through
    case 148: // $@3
      // Fall through
    case 149: // $@4
      // Fall through
    case 150: // parserLocalElements
      // Fall through
    case 151: // parserLocalElement
      // Fall through
    case 152: // parserTypeDeclaration
      // Fall through
    case 153: // $@5
      // Fall through
    case 154: // $@6
      // Fall through
    case 155: // parserStates
      // Fall through
    case 156: // parserState
      // Fall through
    case 157: // $@7
      // Fall through
    case 158: // parserStatements
      // Fall through
    case 159: // parserStatement
      // Fall through
    case 160: // parserBlockStatement
      // Fall through
    case 161: // $@8
      // Fall through
    case 162: // transitionStatement
      // Fall through
    case 163: // stateExpression
      // Fall through
    case 164: // selectExpression
      // Fall through
    case 165: // selectCaseList
      // Fall through
    case 167: // keysetExpression
      // Fall through
    case 168: // tupleKeysetExpression
      // Fall through
    case 169: // simpleExpressionList
      // Fall through
    case 170: // reducedSimpleKeysetExpression
      // Fall through
    case 171: // simpleKeysetExpression
      // Fall through
    case 172: // valueSetDeclaration
      // Fall through
    case 173: // controlDeclaration
      // Fall through
    case 174: // controlTypeDeclaration
      // Fall through
    case 175: // $@9
      // Fall through
    case 176: // $@10
      // Fall through
    case 177: // controlLocalDeclarations
      // Fall through
    case 178: // controlLocalDeclaration
      // Fall through
    case 179: // controlBody
      // Fall through
    case 180: // externDeclaration
      // Fall through
    case 181: // $@11
      // Fall through
    case 182: // $@12
      // Fall through
    case 183: // externFunctionDeclaration
      // Fall through
    case 184: // methodPrototypes
      // Fall through
    case 186: // $@13
      // Fall through
    case 187: // methodPrototype
      // Fall through
    case 188: // $@14
      // Fall through
    case 189: // constructorMethodPrototype
      // Fall through
    case 190: // typeRef
      // Fall through
    case 191: // namedType
      // Fall through
    case 192: // prefixedType
      // Fall through
    case 193: // typeName
      // Fall through
    case 194: // tupleType
      // Fall through
    case 195: // headerStackType
      // Fall through
    case 196: // specializedType
      // Fall through
    case 199: // optTypeParameters
      // Fall through
    case 200: // typeParameters
      // Fall through
    case 201: // typeParameterList
      // Fall through
    case 203: // typeArgumentList
      // Fall through
    case 205: // realTypeArgumentList
      // Fall through
    case 206: // typeDeclaration
      // Fall through
    case 207: // derivedTypeDeclaration
      // Fall through
    case 208: // headerTypeDeclaration
      // Fall through
    case 209: // $@15
      // Fall through
    case 210: // $@16
      // Fall through
    case 211: // structTypeDeclaration
      // Fall through
    case 212: // headerUnionDeclaration
      // Fall through
    case 213: // $@17
      // Fall through
    case 214: // $@18
      // Fall through
    case 215: // structFieldList
      // Fall through
    case 216: // structField
      // Fall through
    case 217: // enumDeclaration
      // Fall through
    case 218: // $@19
      // Fall through
    case 219: // $@20
      // Fall through
    case 220: // specifiedIdentifierList
      // Fall through
    case 221: // specifiedIdentifier
      // Fall through
    case 222: // errorDeclaration
      // Fall through
    case 223: // matchKindDeclaration
      // Fall through
    case 224: // identifierList
      // Fall through
    case 225: // typedefDeclaration
      // Fall through
    case 226: // assignmentOrMethodCallStatement
      // Fall through
    case 228: // emptyStatement
      // Fall through
    case 229: // exitStatement
      // Fall through
    case 230: // returnStatement
      // Fall through
    case 231: // conditionalStatement
      // Fall through
    case 232: // directApplication
      // Fall through
    case 233: // statement
      // Fall through
    case 234: // blockStatement
      // Fall through
    case 235: // $@21
      // Fall through
    case 236: // statOrDeclList
      // Fall through
    case 237: // switchStatement
      // Fall through
    case 238: // switchCases
      // Fall through
    case 239: // switchCase
      // Fall through
    case 241: // statementOrDeclaration
      // Fall through
    case 242: // tableDeclaration
      // Fall through
    case 243: // tablePropertyList
      // Fall through
    case 244: // tableProperty
      // Fall through
    case 245: // keyElementList
      // Fall through
    case 246: // keyElement
      // Fall through
    case 247: // actionList
      // Fall through
    case 248: // action
      // Fall through
    case 249: // actionRef
      // Fall through
    case 250: // entry
      // Fall through
    case 251: // entriesList
      // Fall through
    case 252: // actionDeclaration
      // Fall through
    case 253: // variableDeclaration
      // Fall through
    case 254: // constantDeclaration
      // Fall through
    case 255: // optInitializer
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
