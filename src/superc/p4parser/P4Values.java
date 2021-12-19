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
    if (0 <= id && id < 121 || 270 < id) {
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
      case 15: // nonEmptyParameterList (136)
        // Fall through
      case 30: // parserLocalElements (151)
        // Fall through
      case 35: // parserStates (156)
        // Fall through
      case 38: // parserStatements (159)
        // Fall through
      case 45: // selectCaseList (166)
        // Fall through
      case 49: // simpleExpressionList (170)
        // Fall through
      case 57: // controlLocalDeclarations (178)
        // Fall through
      case 64: // methodPrototypes (185)
        // Fall through
      case 81: // typeParameterList (202)
        // Fall through
      case 83: // typeArgumentList (204)
        // Fall through
      case 85: // realTypeArgumentList (206)
        // Fall through
      case 95: // structFieldList (216)
        // Fall through
      case 100: // specifiedIdentifierList (221)
        // Fall through
      case 104: // identifierList (225)
        // Fall through
      case 116: // statOrDeclList (237)
        // Fall through
      case 118: // switchCases (239)
        // Fall through
      case 123: // tablePropertyList (244)
        // Fall through
      case 125: // keyElementList (246)
        // Fall through
      case 127: // actionList (248)
        // Fall through
      case 131: // entriesList (252)
        // Fall through
      case 138: // argumentList (259)
        // Fall through
      case 139: // nonEmptyArgList (260)
        // Fall through
      case 141: // expressionList (262)
        // Fall through
      case 147: // expression (268)
        // Fall through
      case 148: // invokingExpression (269)
        // Fall through
      case 149: // nonBraceExpression (270)
        return ValueType.LIST;

      case 19: // $@1 (140)
        // Fall through
      case 20: // $@2 (141)
        // Fall through
      case 28: // $@3 (149)
        // Fall through
      case 29: // $@4 (150)
        // Fall through
      case 33: // $@5 (154)
        // Fall through
      case 34: // $@6 (155)
        // Fall through
      case 37: // $@7 (158)
        // Fall through
      case 41: // $@8 (162)
        // Fall through
      case 55: // $@9 (176)
        // Fall through
      case 56: // $@10 (177)
        // Fall through
      case 61: // $@11 (182)
        // Fall through
      case 62: // $@12 (183)
        // Fall through
      case 66: // $@13 (187)
        // Fall through
      case 68: // $@14 (189)
        // Fall through
      case 89: // $@15 (210)
        // Fall through
      case 90: // $@16 (211)
        // Fall through
      case 93: // $@17 (214)
        // Fall through
      case 94: // $@18 (215)
        // Fall through
      case 98: // $@19 (219)
        // Fall through
      case 99: // $@20 (220)
        // Fall through
      case 115: // $@21 (236)
        // Fall through
      case 144: // $@22 (265)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // optInitializer
      // Fall through
    case 257: // initializer
      // Fall through
    case 258: // functionDeclaration
      // Fall through
    case 259: // argumentList
      // Fall through
    case 260: // nonEmptyArgList
      // Fall through
    case 261: // argument
      // Fall through
    case 262: // expressionList
      // Fall through
    case 264: // dot_name
      // Fall through
    case 265: // $@22
      // Fall through
    case 266: // lvalue
      // Fall through
    case 267: // lvalueExpression
      // Fall through
    case 268: // expression
      // Fall through
    case 269: // invokingExpression
      // Fall through
    case 270: // nonBraceExpression
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
    case 136: // nonEmptyParameterList
      // Fall through
    case 137: // parameter
      // Fall through
    case 139: // packageTypeDeclaration
      // Fall through
    case 140: // $@1
      // Fall through
    case 141: // $@2
      // Fall through
    case 142: // instantiation
      // Fall through
    case 146: // optConstructorParameters
      // Fall through
    case 148: // parserDeclaration
      // Fall through
    case 149: // $@3
      // Fall through
    case 150: // $@4
      // Fall through
    case 151: // parserLocalElements
      // Fall through
    case 152: // parserLocalElement
      // Fall through
    case 153: // parserTypeDeclaration
      // Fall through
    case 154: // $@5
      // Fall through
    case 155: // $@6
      // Fall through
    case 156: // parserStates
      // Fall through
    case 157: // parserState
      // Fall through
    case 158: // $@7
      // Fall through
    case 159: // parserStatements
      // Fall through
    case 160: // parserStatement
      // Fall through
    case 161: // parserBlockStatement
      // Fall through
    case 162: // $@8
      // Fall through
    case 163: // transitionStatement
      // Fall through
    case 164: // stateExpression
      // Fall through
    case 165: // selectExpression
      // Fall through
    case 166: // selectCaseList
      // Fall through
    case 168: // keysetExpression
      // Fall through
    case 169: // tupleKeysetExpression
      // Fall through
    case 170: // simpleExpressionList
      // Fall through
    case 171: // reducedSimpleKeysetExpression
      // Fall through
    case 172: // simpleKeysetExpression
      // Fall through
    case 173: // valueSetDeclaration
      // Fall through
    case 174: // controlDeclaration
      // Fall through
    case 175: // controlTypeDeclaration
      // Fall through
    case 176: // $@9
      // Fall through
    case 177: // $@10
      // Fall through
    case 178: // controlLocalDeclarations
      // Fall through
    case 179: // controlLocalDeclaration
      // Fall through
    case 180: // controlBody
      // Fall through
    case 181: // externDeclaration
      // Fall through
    case 182: // $@11
      // Fall through
    case 183: // $@12
      // Fall through
    case 184: // externFunctionDeclaration
      // Fall through
    case 185: // methodPrototypes
      // Fall through
    case 187: // $@13
      // Fall through
    case 188: // methodPrototype
      // Fall through
    case 189: // $@14
      // Fall through
    case 190: // constructorMethodPrototype
      // Fall through
    case 191: // typeRef
      // Fall through
    case 192: // namedType
      // Fall through
    case 193: // prefixedType
      // Fall through
    case 194: // typeName
      // Fall through
    case 195: // tupleType
      // Fall through
    case 196: // headerStackType
      // Fall through
    case 197: // specializedType
      // Fall through
    case 200: // optTypeParameters
      // Fall through
    case 201: // typeParameters
      // Fall through
    case 202: // typeParameterList
      // Fall through
    case 204: // typeArgumentList
      // Fall through
    case 206: // realTypeArgumentList
      // Fall through
    case 207: // typeDeclaration
      // Fall through
    case 208: // derivedTypeDeclaration
      // Fall through
    case 209: // headerTypeDeclaration
      // Fall through
    case 210: // $@15
      // Fall through
    case 211: // $@16
      // Fall through
    case 212: // structTypeDeclaration
      // Fall through
    case 213: // headerUnionDeclaration
      // Fall through
    case 214: // $@17
      // Fall through
    case 215: // $@18
      // Fall through
    case 216: // structFieldList
      // Fall through
    case 217: // structField
      // Fall through
    case 218: // enumDeclaration
      // Fall through
    case 219: // $@19
      // Fall through
    case 220: // $@20
      // Fall through
    case 221: // specifiedIdentifierList
      // Fall through
    case 222: // specifiedIdentifier
      // Fall through
    case 223: // errorDeclaration
      // Fall through
    case 224: // matchKindDeclaration
      // Fall through
    case 225: // identifierList
      // Fall through
    case 226: // typedefDeclaration
      // Fall through
    case 227: // assignmentOrMethodCallStatement
      // Fall through
    case 229: // emptyStatement
      // Fall through
    case 230: // exitStatement
      // Fall through
    case 231: // returnStatement
      // Fall through
    case 232: // conditionalStatement
      // Fall through
    case 233: // directApplication
      // Fall through
    case 234: // statement
      // Fall through
    case 235: // blockStatement
      // Fall through
    case 236: // $@21
      // Fall through
    case 237: // statOrDeclList
      // Fall through
    case 238: // switchStatement
      // Fall through
    case 239: // switchCases
      // Fall through
    case 240: // switchCase
      // Fall through
    case 242: // statementOrDeclaration
      // Fall through
    case 243: // tableDeclaration
      // Fall through
    case 244: // tablePropertyList
      // Fall through
    case 245: // tableProperty
      // Fall through
    case 246: // keyElementList
      // Fall through
    case 247: // keyElement
      // Fall through
    case 248: // actionList
      // Fall through
    case 249: // action
      // Fall through
    case 250: // actionRef
      // Fall through
    case 251: // entry
      // Fall through
    case 252: // entriesList
      // Fall through
    case 253: // actionDeclaration
      // Fall through
    case 254: // variableDeclaration
      // Fall through
    case 255: // constantDeclaration
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
