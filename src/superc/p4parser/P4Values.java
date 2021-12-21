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
    if (0 <= id && id < 121 || 271 < id) {
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
      case 31: // parserLocalElements (152)
        // Fall through
      case 36: // parserStates (157)
        // Fall through
      case 39: // parserStatements (160)
        // Fall through
      case 46: // selectCaseList (167)
        // Fall through
      case 50: // simpleExpressionList (171)
        // Fall through
      case 58: // controlLocalDeclarations (179)
        // Fall through
      case 65: // methodPrototypes (186)
        // Fall through
      case 82: // typeParameterList (203)
        // Fall through
      case 84: // typeArgumentList (205)
        // Fall through
      case 86: // realTypeArgumentList (207)
        // Fall through
      case 96: // structFieldList (217)
        // Fall through
      case 101: // specifiedIdentifierList (222)
        // Fall through
      case 105: // identifierList (226)
        // Fall through
      case 117: // statOrDeclList (238)
        // Fall through
      case 119: // switchCases (240)
        // Fall through
      case 124: // tablePropertyList (245)
        // Fall through
      case 126: // keyElementList (247)
        // Fall through
      case 128: // actionList (249)
        // Fall through
      case 132: // entriesList (253)
        // Fall through
      case 139: // argumentList (260)
        // Fall through
      case 140: // nonEmptyArgList (261)
        // Fall through
      case 142: // expressionList (263)
        // Fall through
      case 148: // expression (269)
        // Fall through
      case 149: // invokingExpression (270)
        // Fall through
      case 150: // nonBraceExpression (271)
        return ValueType.LIST;

      case 19: // $@1 (140)
        // Fall through
      case 20: // $@2 (141)
        // Fall through
      case 29: // $@3 (150)
        // Fall through
      case 30: // $@4 (151)
        // Fall through
      case 34: // $@5 (155)
        // Fall through
      case 35: // $@6 (156)
        // Fall through
      case 38: // $@7 (159)
        // Fall through
      case 42: // $@8 (163)
        // Fall through
      case 56: // $@9 (177)
        // Fall through
      case 57: // $@10 (178)
        // Fall through
      case 62: // $@11 (183)
        // Fall through
      case 63: // $@12 (184)
        // Fall through
      case 67: // $@13 (188)
        // Fall through
      case 69: // $@14 (190)
        // Fall through
      case 90: // $@15 (211)
        // Fall through
      case 91: // $@16 (212)
        // Fall through
      case 94: // $@17 (215)
        // Fall through
      case 95: // $@18 (216)
        // Fall through
      case 99: // $@19 (220)
        // Fall through
      case 100: // $@20 (221)
        // Fall through
      case 116: // $@21 (237)
        // Fall through
      case 145: // $@22 (266)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // constantDeclaration
      // Fall through
    case 257: // optInitializer
      // Fall through
    case 258: // initializer
      // Fall through
    case 259: // functionDeclaration
      // Fall through
    case 260: // argumentList
      // Fall through
    case 261: // nonEmptyArgList
      // Fall through
    case 262: // argument
      // Fall through
    case 263: // expressionList
      // Fall through
    case 265: // dot_name
      // Fall through
    case 266: // $@22
      // Fall through
    case 267: // lvalue
      // Fall through
    case 268: // lvalueExpression
      // Fall through
    case 269: // expression
      // Fall through
    case 270: // invokingExpression
      // Fall through
    case 271: // nonBraceExpression
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
    case 143: // instantiationWithAssignment
      // Fall through
    case 147: // optConstructorParameters
      // Fall through
    case 149: // parserDeclaration
      // Fall through
    case 150: // $@3
      // Fall through
    case 151: // $@4
      // Fall through
    case 152: // parserLocalElements
      // Fall through
    case 153: // parserLocalElement
      // Fall through
    case 154: // parserTypeDeclaration
      // Fall through
    case 155: // $@5
      // Fall through
    case 156: // $@6
      // Fall through
    case 157: // parserStates
      // Fall through
    case 158: // parserState
      // Fall through
    case 159: // $@7
      // Fall through
    case 160: // parserStatements
      // Fall through
    case 161: // parserStatement
      // Fall through
    case 162: // parserBlockStatement
      // Fall through
    case 163: // $@8
      // Fall through
    case 164: // transitionStatement
      // Fall through
    case 165: // stateExpression
      // Fall through
    case 166: // selectExpression
      // Fall through
    case 167: // selectCaseList
      // Fall through
    case 169: // keysetExpression
      // Fall through
    case 170: // tupleKeysetExpression
      // Fall through
    case 171: // simpleExpressionList
      // Fall through
    case 172: // reducedSimpleKeysetExpression
      // Fall through
    case 173: // simpleKeysetExpression
      // Fall through
    case 174: // valueSetDeclaration
      // Fall through
    case 175: // controlDeclaration
      // Fall through
    case 176: // controlTypeDeclaration
      // Fall through
    case 177: // $@9
      // Fall through
    case 178: // $@10
      // Fall through
    case 179: // controlLocalDeclarations
      // Fall through
    case 180: // controlLocalDeclaration
      // Fall through
    case 181: // controlBody
      // Fall through
    case 182: // externDeclaration
      // Fall through
    case 183: // $@11
      // Fall through
    case 184: // $@12
      // Fall through
    case 185: // externFunctionDeclaration
      // Fall through
    case 186: // methodPrototypes
      // Fall through
    case 188: // $@13
      // Fall through
    case 189: // methodPrototype
      // Fall through
    case 190: // $@14
      // Fall through
    case 191: // constructorMethodPrototype
      // Fall through
    case 192: // typeRef
      // Fall through
    case 193: // namedType
      // Fall through
    case 194: // prefixedType
      // Fall through
    case 195: // typeName
      // Fall through
    case 196: // tupleType
      // Fall through
    case 197: // headerStackType
      // Fall through
    case 198: // specializedType
      // Fall through
    case 201: // optTypeParameters
      // Fall through
    case 202: // typeParameters
      // Fall through
    case 203: // typeParameterList
      // Fall through
    case 205: // typeArgumentList
      // Fall through
    case 207: // realTypeArgumentList
      // Fall through
    case 208: // typeDeclaration
      // Fall through
    case 209: // derivedTypeDeclaration
      // Fall through
    case 210: // headerTypeDeclaration
      // Fall through
    case 211: // $@15
      // Fall through
    case 212: // $@16
      // Fall through
    case 213: // structTypeDeclaration
      // Fall through
    case 214: // headerUnionDeclaration
      // Fall through
    case 215: // $@17
      // Fall through
    case 216: // $@18
      // Fall through
    case 217: // structFieldList
      // Fall through
    case 218: // structField
      // Fall through
    case 219: // enumDeclaration
      // Fall through
    case 220: // $@19
      // Fall through
    case 221: // $@20
      // Fall through
    case 222: // specifiedIdentifierList
      // Fall through
    case 223: // specifiedIdentifier
      // Fall through
    case 224: // errorDeclaration
      // Fall through
    case 225: // matchKindDeclaration
      // Fall through
    case 226: // identifierList
      // Fall through
    case 227: // typedefDeclaration
      // Fall through
    case 228: // assignmentOrMethodCallStatement
      // Fall through
    case 230: // emptyStatement
      // Fall through
    case 231: // exitStatement
      // Fall through
    case 232: // returnStatement
      // Fall through
    case 233: // conditionalStatement
      // Fall through
    case 234: // directApplication
      // Fall through
    case 235: // statement
      // Fall through
    case 236: // blockStatement
      // Fall through
    case 237: // $@21
      // Fall through
    case 238: // statOrDeclList
      // Fall through
    case 239: // switchStatement
      // Fall through
    case 240: // switchCases
      // Fall through
    case 241: // switchCase
      // Fall through
    case 243: // statementOrDeclaration
      // Fall through
    case 244: // tableDeclaration
      // Fall through
    case 245: // tablePropertyList
      // Fall through
    case 246: // tableProperty
      // Fall through
    case 247: // keyElementList
      // Fall through
    case 248: // keyElement
      // Fall through
    case 249: // actionList
      // Fall through
    case 250: // action
      // Fall through
    case 251: // actionRef
      // Fall through
    case 252: // entry
      // Fall through
    case 253: // entriesList
      // Fall through
    case 254: // actionDeclaration
      // Fall through
    case 255: // variableDeclaration
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
