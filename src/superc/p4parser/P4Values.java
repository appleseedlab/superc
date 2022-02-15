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
    if (0 <= id && id < 121 || 284 < id) {
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
      case 60: // controlLocalDeclarations (181)
        // Fall through
      case 69: // methodPrototypes (190)
        // Fall through
      case 88: // typeParameterList (209)
        // Fall through
      case 90: // typeArgumentList (211)
        // Fall through
      case 92: // realTypeArgumentList (213)
        // Fall through
      case 104: // structFieldList (225)
        // Fall through
      case 109: // specifiedIdentifierList (230)
        // Fall through
      case 113: // identifierList (234)
        // Fall through
      case 125: // statOrDeclList (246)
        // Fall through
      case 127: // switchCases (248)
        // Fall through
      case 134: // tablePropertyList (255)
        // Fall through
      case 136: // keyElementList (257)
        // Fall through
      case 138: // actionList (259)
        // Fall through
      case 142: // entriesList (263)
        // Fall through
      case 152: // nonEmptyArgList (273)
        // Fall through
      case 154: // expressionList (275)
        // Fall through
      case 160: // expression (281)
        // Fall through
      case 161: // invokingExpression (282)
        // Fall through
      case 162: // nonBraceExpression (283)
        // Fall through
      case 163: // invokingNonBraceExpression (284)
        return ValueType.LIST;

      case 15: // $@1 (136)
        // Fall through
      case 20: // $@2 (141)
        // Fall through
      case 21: // $@3 (142)
        // Fall through
      case 29: // $@4 (150)
        // Fall through
      case 30: // $@5 (151)
        // Fall through
      case 34: // $@6 (155)
        // Fall through
      case 35: // $@7 (156)
        // Fall through
      case 38: // $@8 (159)
        // Fall through
      case 42: // $@9 (163)
        // Fall through
      case 55: // $@10 (176)
        // Fall through
      case 56: // $@11 (177)
        // Fall through
      case 58: // $@12 (179)
        // Fall through
      case 59: // $@13 (180)
        // Fall through
      case 64: // $@14 (185)
        // Fall through
      case 65: // $@15 (186)
        // Fall through
      case 66: // $@16 (187)
        // Fall through
      case 67: // $@17 (188)
        // Fall through
      case 71: // $@18 (192)
        // Fall through
      case 73: // $@19 (194)
        // Fall through
      case 86: // $@20 (207)
        // Fall through
      case 87: // $@21 (208)
        // Fall through
      case 96: // $@22 (217)
        // Fall through
      case 97: // $@23 (218)
        // Fall through
      case 99: // $@24 (220)
        // Fall through
      case 100: // $@25 (221)
        // Fall through
      case 102: // $@26 (223)
        // Fall through
      case 103: // $@27 (224)
        // Fall through
      case 107: // $@28 (228)
        // Fall through
      case 108: // $@29 (229)
        // Fall through
      case 124: // $@30 (245)
        // Fall through
      case 132: // $@31 (253)
        // Fall through
      case 133: // $@32 (254)
        // Fall through
      case 144: // $@33 (265)
        // Fall through
      case 150: // $@34 (271)
        // Fall through
      case 157: // $@35 (278)
        return ValueType.ACTION;

      default:
        return ValueType.NODE;
    }
  }
  public boolean isComplete(int id) {
    switch(id) {
    case 256: // tableProperty
      // Fall through
    case 257: // keyElementList
      // Fall through
    case 258: // keyElement
      // Fall through
    case 259: // actionList
      // Fall through
    case 260: // action
      // Fall through
    case 261: // actionRef
      // Fall through
    case 262: // entry
      // Fall through
    case 263: // entriesList
      // Fall through
    case 264: // actionDeclaration
      // Fall through
    case 265: // $@33
      // Fall through
    case 266: // variableDeclaration
      // Fall through
    case 267: // constantDeclaration
      // Fall through
    case 268: // optInitializer
      // Fall through
    case 269: // initializer
      // Fall through
    case 270: // functionDeclaration
      // Fall through
    case 271: // $@34
      // Fall through
    case 272: // argumentList
      // Fall through
    case 273: // nonEmptyArgList
      // Fall through
    case 274: // argument
      // Fall through
    case 275: // expressionList
      // Fall through
    case 277: // dot_name
      // Fall through
    case 278: // $@35
      // Fall through
    case 279: // lvalue
      // Fall through
    case 280: // lvalueExpression
      // Fall through
    case 281: // expression
      // Fall through
    case 282: // invokingExpression
      // Fall through
    case 283: // nonBraceExpression
      // Fall through
    case 284: // invokingNonBraceExpression
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
    case 147: // optConstructorParameters
      // Fall through
    case 149: // parserDeclaration
      // Fall through
    case 150: // $@4
      // Fall through
    case 151: // $@5
      // Fall through
    case 152: // parserLocalElements
      // Fall through
    case 153: // parserLocalElement
      // Fall through
    case 154: // parserTypeDeclaration
      // Fall through
    case 155: // $@6
      // Fall through
    case 156: // $@7
      // Fall through
    case 157: // parserStates
      // Fall through
    case 158: // parserState
      // Fall through
    case 159: // $@8
      // Fall through
    case 160: // parserStatements
      // Fall through
    case 161: // parserStatement
      // Fall through
    case 162: // parserBlockStatement
      // Fall through
    case 163: // $@9
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
    case 176: // $@10
      // Fall through
    case 177: // $@11
      // Fall through
    case 178: // controlTypeDeclaration
      // Fall through
    case 179: // $@12
      // Fall through
    case 180: // $@13
      // Fall through
    case 181: // controlLocalDeclarations
      // Fall through
    case 182: // controlLocalDeclaration
      // Fall through
    case 183: // controlBody
      // Fall through
    case 184: // externDeclaration
      // Fall through
    case 185: // $@14
      // Fall through
    case 186: // $@15
      // Fall through
    case 187: // $@16
      // Fall through
    case 188: // $@17
      // Fall through
    case 189: // externFunctionDeclaration
      // Fall through
    case 190: // methodPrototypes
      // Fall through
    case 192: // $@18
      // Fall through
    case 193: // methodPrototype
      // Fall through
    case 194: // $@19
      // Fall through
    case 195: // constructorMethodPrototype
      // Fall through
    case 196: // typeRef
      // Fall through
    case 197: // namedType
      // Fall through
    case 198: // prefixedType
      // Fall through
    case 199: // typeName
      // Fall through
    case 200: // tupleType
      // Fall through
    case 201: // headerStackType
      // Fall through
    case 202: // specializedType
      // Fall through
    case 205: // optTypeParameters
      // Fall through
    case 206: // typeParameters
      // Fall through
    case 207: // $@20
      // Fall through
    case 208: // $@21
      // Fall through
    case 209: // typeParameterList
      // Fall through
    case 211: // typeArgumentList
      // Fall through
    case 213: // realTypeArgumentList
      // Fall through
    case 214: // typeDeclaration
      // Fall through
    case 215: // derivedTypeDeclaration
      // Fall through
    case 216: // headerTypeDeclaration
      // Fall through
    case 217: // $@22
      // Fall through
    case 218: // $@23
      // Fall through
    case 219: // structTypeDeclaration
      // Fall through
    case 220: // $@24
      // Fall through
    case 221: // $@25
      // Fall through
    case 222: // headerUnionDeclaration
      // Fall through
    case 223: // $@26
      // Fall through
    case 224: // $@27
      // Fall through
    case 225: // structFieldList
      // Fall through
    case 226: // structField
      // Fall through
    case 227: // enumDeclaration
      // Fall through
    case 228: // $@28
      // Fall through
    case 229: // $@29
      // Fall through
    case 230: // specifiedIdentifierList
      // Fall through
    case 231: // specifiedIdentifier
      // Fall through
    case 232: // errorDeclaration
      // Fall through
    case 233: // matchKindDeclaration
      // Fall through
    case 234: // identifierList
      // Fall through
    case 235: // typedefDeclaration
      // Fall through
    case 236: // assignmentOrMethodCallStatement
      // Fall through
    case 238: // emptyStatement
      // Fall through
    case 239: // exitStatement
      // Fall through
    case 240: // returnStatement
      // Fall through
    case 241: // conditionalStatement
      // Fall through
    case 242: // directApplication
      // Fall through
    case 243: // statement
      // Fall through
    case 244: // blockStatement
      // Fall through
    case 245: // $@30
      // Fall through
    case 246: // statOrDeclList
      // Fall through
    case 247: // switchStatement
      // Fall through
    case 248: // switchCases
      // Fall through
    case 249: // switchCase
      // Fall through
    case 251: // statementOrDeclaration
      // Fall through
    case 252: // tableDeclaration
      // Fall through
    case 253: // $@31
      // Fall through
    case 254: // $@32
      // Fall through
    case 255: // tablePropertyList
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
