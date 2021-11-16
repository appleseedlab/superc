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
    if (0 <= id && id < 121 || 263 < id) {
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
      case 62: // methodPrototypes (183)
        // Fall through
      case 77: // typeParameterList (198)
        // Fall through
      case 79: // typeArgumentList (200)
        // Fall through
      case 81: // realTypeArgumentList (202)
        // Fall through
      case 91: // structFieldList (212)
        // Fall through
      case 96: // specifiedIdentifierList (217)
        // Fall through
      case 100: // identifierList (221)
        // Fall through
      case 111: // statOrDeclList (232)
        // Fall through
      case 113: // switchCases (234)
        // Fall through
      case 118: // tablePropertyList (239)
        // Fall through
      case 120: // keyElementList (241)
        // Fall through
      case 122: // actionList (243)
        // Fall through
      case 125: // entriesList (246)
        // Fall through
      case 132: // argumentList (253)
        // Fall through
      case 133: // nonEmptyArgList (254)
        // Fall through
      case 135: // expressionList (256)
        // Fall through
      case 140: // expression (261)
        // Fall through
      case 141: // invokingExpression (262)
        // Fall through
      case 142: // nonBraceExpression (263)
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
      case 64: // $@13 (185)
        // Fall through
      case 85: // $@14 (206)
        // Fall through
      case 86: // $@15 (207)
        // Fall through
      case 89: // $@16 (210)
        // Fall through
      case 90: // $@17 (211)
        // Fall through
      case 94: // $@18 (215)
        // Fall through
      case 95: // $@19 (216)
        // Fall through
      case 110: // $@20 (231)
        // Fall through
      case 138: // $@21 (259)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // expressionList
      // Fall through
    case 258: // dot_name
      // Fall through
    case 259: // $@21
      // Fall through
    case 260: // lvalue
      // Fall through
    case 261: // expression
      // Fall through
    case 262: // invokingExpression
      // Fall through
    case 263: // nonBraceExpression
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
    case 183: // methodPrototypes
      // Fall through
    case 185: // $@13
      // Fall through
    case 186: // methodPrototype
      // Fall through
    case 187: // typeRef
      // Fall through
    case 188: // namedType
      // Fall through
    case 189: // prefixedType
      // Fall through
    case 190: // typeName
      // Fall through
    case 191: // tupleType
      // Fall through
    case 192: // headerStackType
      // Fall through
    case 193: // specializedType
      // Fall through
    case 196: // optTypeParameters
      // Fall through
    case 197: // typeParameters
      // Fall through
    case 198: // typeParameterList
      // Fall through
    case 200: // typeArgumentList
      // Fall through
    case 202: // realTypeArgumentList
      // Fall through
    case 203: // typeDeclaration
      // Fall through
    case 204: // derivedTypeDeclaration
      // Fall through
    case 205: // headerTypeDeclaration
      // Fall through
    case 206: // $@14
      // Fall through
    case 207: // $@15
      // Fall through
    case 208: // structTypeDeclaration
      // Fall through
    case 209: // headerUnionDeclaration
      // Fall through
    case 210: // $@16
      // Fall through
    case 211: // $@17
      // Fall through
    case 212: // structFieldList
      // Fall through
    case 213: // structField
      // Fall through
    case 214: // enumDeclaration
      // Fall through
    case 215: // $@18
      // Fall through
    case 216: // $@19
      // Fall through
    case 217: // specifiedIdentifierList
      // Fall through
    case 218: // specifiedIdentifier
      // Fall through
    case 219: // errorDeclaration
      // Fall through
    case 220: // matchKindDeclaration
      // Fall through
    case 221: // identifierList
      // Fall through
    case 222: // typedefDeclaration
      // Fall through
    case 223: // assignmentOrMethodCallStatement
      // Fall through
    case 224: // emptyStatement
      // Fall through
    case 225: // exitStatement
      // Fall through
    case 226: // returnStatement
      // Fall through
    case 227: // conditionalStatement
      // Fall through
    case 228: // directApplication
      // Fall through
    case 229: // statement
      // Fall through
    case 230: // blockStatement
      // Fall through
    case 231: // $@20
      // Fall through
    case 232: // statOrDeclList
      // Fall through
    case 233: // switchStatement
      // Fall through
    case 234: // switchCases
      // Fall through
    case 235: // switchCase
      // Fall through
    case 237: // statementOrDeclaration
      // Fall through
    case 238: // tableDeclaration
      // Fall through
    case 239: // tablePropertyList
      // Fall through
    case 240: // tableProperty
      // Fall through
    case 241: // keyElementList
      // Fall through
    case 242: // keyElement
      // Fall through
    case 243: // actionList
      // Fall through
    case 244: // actionRef
      // Fall through
    case 245: // entry
      // Fall through
    case 246: // entriesList
      // Fall through
    case 247: // actionDeclaration
      // Fall through
    case 248: // variableDeclaration
      // Fall through
    case 249: // constantDeclaration
      // Fall through
    case 250: // optInitializer
      // Fall through
    case 251: // initializer
      // Fall through
    case 252: // functionDeclaration
      // Fall through
    case 253: // argumentList
      // Fall through
    case 254: // nonEmptyArgList
      // Fall through
    case 255: // argument
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
