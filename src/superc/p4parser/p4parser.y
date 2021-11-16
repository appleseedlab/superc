/*
Copyright 2013-present Barefoot Networks, Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


// Use location tracking with our custom location type.

// Use iostreams to print all values.

%token             START_PROGRAM

                   // Lists
                   START_EXPRESSION_LIST
                   START_KV_LIST
                   START_INTEGER_LIST
                   START_INTEGER_OR_STRING_LITERAL_LIST
                   START_STRING_LITERAL_LIST

                   // Singletons
                   START_EXPRESSION
                   START_INTEGER
                   START_INTEGER_OR_STRING_LITERAL
                   START_STRING_LITERAL

                   // Pairs
                   START_EXPRESSION_PAIR
                   START_INTEGER_PAIR
                   START_STRING_LITERAL_PAIR

                   // Triples
                   START_EXPRESSION_TRIPLE
                   START_INTEGER_TRIPLE
                   START_STRING_LITERAL_TRIPLE

                   // P4Runtime annotations
                   START_P4RT_TRANSLATION_ANNOTATION  // @p4runtime_translation

%token             END END_ANNOTATION


///////////////////////////////////////////////////////////////////////////////
//
// Language token definitions.
//
// NB: Tokens defined here should be added to the annotationToken production.
//
///////////////////////////////////////////////////////////////////////////////

%token      UNEXPECTED_TOKEN END_PRAGMA
%token      HASH
%token      DHASH
%token      LE
%token      GE
%token      SHL
%token      AND
%token      OR
%token      NE
%token      EQ
%token      PLUS
%token      MINUS
%token      PLUS_SAT
%token      MINUS_SAT
%token      MUL
%token      DIV
%token      MOD
%token      BIT_OR
%token      BIT_AND
%token      BIT_XOR
%token      COMPLEMENT
%token      L_BRACKET
%token      R_BRACKET
%token      L_BRACE
%token      R_BRACE
%token      L_ANGLE
%token      L_ANGLE_ARGS    // < where template args are expected
%token      R_ANGLE
%token      R_ANGLE_SHIFT   // > immediately followed by another >
%token      L_PAREN
%token      R_PAREN
%token      NOT
%token      COLON
%token      COMMA
%token      QUESTION
%token      DOT
%token      ASSIGN
%token      SEMICOLON
%token      AT
%token      PP
%token      DONTCARE
%token      MASK
%token      RANGE
%token      TRUE FALSE THIS
%token      ABSTRACT ACTION ACTIONS APPLY BOOL BIT CONST CONTROL DEFAULT
                   ELSE ENTRIES ENUM ERROR EXIT EXTERN HEADER HEADER_UNION IF IN INOUT
                   INT KEY SELECT MATCH_KIND TYPE OUT PACKAGE PARSER PRAGMA RETURN STATE
                   STRING STRUCT SWITCH TABLE TRANSITION TUPLE TYPEDEF VARBIT VALUESET VOID

%token IDENTIFIER TYPE_IDENTIFIER STRING_LITERAL
%token INTEGER FLOATING_CONSTANT PPNUM

// End of token definitions ///////////////////////////////////////////////////

%{

import xtc.Constants;
import xtc.Limits;

import superc.p4parser.P4Context.SymbolTable.STField;

import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Visitor;

import xtc.util.Pair;

import superc.core.Syntax;
import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;
import superc.core.Syntax.Error;

import xtc.type.AliasT;
import xtc.type.ArrayT;
import xtc.type.BooleanT;
import xtc.type.C;
import xtc.type.CastReference;
import xtc.type.Constant;
import xtc.type.DynamicReference;
import xtc.type.EnumT;
import xtc.type.EnumeratorT;
import xtc.type.ErrorT;
import xtc.type.FieldReference;
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.Reference;
import xtc.type.StaticReference;
import xtc.type.StringReference;
import xtc.type.StructOrUnionT;
import xtc.type.StructT;
import xtc.type.Tagged;
import xtc.type.Type;
import xtc.type.Type.Tag;
import xtc.type.UnionT;
import xtc.type.VariableT;
import xtc.type.VoidT;

import xtc.util.SymbolTable;
import xtc.util.SymbolTable.Scope;
import xtc.util.SingletonIterator;
import xtc.util.Utilities;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.Clauses;

import superc.core.ForkMergeParser;
import superc.core.ForkMergeParser.StackFrame;

import java.util.ArrayList;
import java.util.List;

import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;
import org.sat4j.specs.ContradictionException;
import org.sat4j.specs.IConstr;
import org.sat4j.specs.IProblem;
import org.sat4j.specs.ISolver;
import org.sat4j.specs.TimeoutException;
import org.sat4j.tools.ModelIterator;

%}

// %precedence COMMA
%precedence QUESTION
%precedence COLON
%left OR
%left AND
%left EQ NE
%left L_ANGLE R_ANGLE LE GE
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left SHL R_ANGLE_SHIFT
%left PP PLUS MINUS PLUS_SAT MINUS_SAT
%left MUL DIV MOD
%precedence PREFIX
%precedence R_BRACKET L_PAREN L_BRACKET L_ANGLE_ARGS
%precedence DOT

%right THEN ELSE /* THEN is a fake token */

/*
FIXME -- we need this %destructor for correct error recovery, but because of the
broken bison C++ skeleton, it gets declarations in the wrong order and it won't
compile.  Not having it (just) means that the symbol table may get confused after
a syntax error causing a spurious error cascade, which isn't too bad.

%destructor {} functionPrototype parserTypeDeclaration
                                         controlTypeDeclaration
*/

%%

/*
   This grammar may look weird in some places, but a lot of effort was put into
   eliminating conflicts.  This sometimes required having the grammar be more
   lenient than necessary.  Moreover, the grammar is context-sensitive, and it
   needs some rudiments of type information to properly perform parsing.  This
   is done with the help of P4ParserDriver's "structure" object, which keeps
   track of which identifiers represent types, and which represent namespaces.
*/

start: /** complete **/
       program;


// program : input END { YYACCEPT; };
program: /** complete **/
      input {}
    ;

input: /** complete, list **/
      %empty
    | input declaration  {}
    | input SEMICOLON          {}   // empty declaration
    ;

declaration: /** complete **/
      constantDeclaration     {}
    | externDeclaration       {}
    | actionDeclaration       {}
    | parserDeclaration       {}
    | typeDeclaration         {}
    | controlDeclaration      {}
    | instantiation           {}
    | errorDeclaration        {}
    | matchKindDeclaration    {}
    | functionDeclaration     {}
    ;

nonTypeName:
    IDENTIFIER  {}
    | APPLY       {}
    | KEY         {}
    | ACTIONS     {}
    | STATE       {}
    | ENTRIES     {}
    | TYPE        {}
    ;

name:
    nonTypeName {}
    | TYPE_IDENTIFIER  {}
    ;

nonTableKwName:
    IDENTIFIER       {}
    | TYPE_IDENTIFIER  {}
    | APPLY            {}
    | STATE            {}
    | TYPE             {}
    ;

optCONST:
    %empty      {}
    | CONST       {}
    ;

optAnnotations: /** complete **/
      %empty      {}
    | annotations {}
    ;

annotations: /** complete, list **/
      annotation  {}
    | annotations annotation {}
    ;

annotation: /** complete **/
      AT name
        {}
    | AT name L_PAREN annotationBody R_PAREN
        {}
    | AT name L_BRACKET expressionList R_BRACKET
        {}
    | AT name L_BRACKET kvList R_BRACKET
        {}
    // Experimental: backwards compatibility with P4-14 pragmas (which
    // themselves are experimental!)
    | PRAGMA name annotationBody END_PRAGMA
        {}
    ;

annotationBody: /** complete, list **/
      %empty  {}
    | annotationBody L_PAREN annotationBody R_PAREN
        {}
    | annotationBody annotationToken
        {}
    ;

annotationToken:
      UNEXPECTED_TOKEN {}
    | ABSTRACT         {}
    | ACTION           {}
    | ACTIONS          {}
    | APPLY            {}
    | BOOL             {}
    | BIT              {}
    | CONST            {}
    | CONTROL          {}
    | DEFAULT          {}
    | ELSE             {}
    | ENTRIES          {}
    | ENUM             {}
    | ERROR            {}
    | EXIT             {}
    | EXTERN           {}
    | FALSE            {}
    | HEADER           {}
    | HEADER_UNION     {}
    | IF               {}
    | IN               {}
    | INOUT            {}
    | INT              {}
    | KEY              {}
    | MATCH_KIND       {}
    | TYPE             {}
    | OUT              {}
    | PARSER           {}
    | PACKAGE          {}
    | PRAGMA           {}
    | RETURN           {}
    | SELECT           {}
    | STATE            {}
    | STRING           {}
    | STRUCT           {}
    | SWITCH           {}
    | TABLE            {}
    | THIS             {}
    | TRANSITION       {}
    | TRUE             {}
    | TUPLE            {}
    | TYPEDEF          {}
    | VARBIT           {}
    | VALUESET         {}
    | VOID             {}
    | DONTCARE              {}

    | IDENTIFIER       {}
    | TYPE_IDENTIFIER  {}
    | STRING_LITERAL   {}
    | INTEGER          {}
    | L_ANGLE_ARGS     {}
    | R_ANGLE_SHIFT    {}
    | RANGE            {}
    | MASK             {}
    | AND              {}
    | OR               {}
    | EQ               {}
    | NE               {}
    | GE               {}
    | LE               {}
    | PP               {}
    | PLUS             {}
    | PLUS_SAT
    | MINUS            {}
    | MINUS_SAT        {}
    | MUL              {}
    | DIV              {}
    | MOD              {}
    | BIT_OR           {}
    | BIT_AND          {}
    | BIT_XOR          {}
    | COMPLEMENT       {}
    | L_BRACKET        {}
    | R_BRACKET        {}
    | L_BRACE          {}
    | R_BRACE          {}
    | L_ANGLE          {}
    | R_ANGLE          {}
    | NOT              {}
    | COLON            {}
    | QUESTION         {}
    | DOT              {}
    | ASSIGN           {}
    | SEMICOLON        {}
    | AT               {}
    | COMMA            {}
    ;

kvList: /** complete, list **/
      kvPair                          {}
    | kvList COMMA kvPair               {}
    ;

kvPair: /** complete **/
      name ASSIGN expression             {}
    ;

parameterList: /** complete, list **/
      %empty                          {}
    | nonEmptyParameterList           {}
    ;

nonEmptyParameterList: /** complete, list **/
      parameter                           {}
    | nonEmptyParameterList COMMA parameter {}
    ;

parameter: /** complete **/
      optAnnotations direction typeRef name {}
    | optAnnotations direction typeRef name ASSIGN expression {}
    ;

direction:
    IN           {}
    | OUT          {}
    | INOUT        {}
    | %empty       {}
    ;

packageTypeDeclaration: /** complete **/
      optAnnotations PACKAGE name {}
      optTypeParameters {}
      L_PAREN parameterList R_PAREN {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
    ;

instantiation: /** complete **/
        annotations typeRef L_PAREN argumentList R_PAREN name SEMICOLON
                     {}
      | typeRef L_PAREN argumentList R_PAREN name SEMICOLON
                     {}
      /* experimental */
      | annotations typeRef L_PAREN argumentList R_PAREN name ASSIGN objInitializer SEMICOLON
                     {}
      /* experimental */
      | typeRef L_PAREN argumentList R_PAREN name ASSIGN objInitializer SEMICOLON
                     {}
    ;

/* experimental; includes the following 3 productions */
objInitializer:
    L_BRACE objDeclarations R_BRACE
                               {}
    ;
// Annonation problem here
objDeclarations: 
      %empty                         {}
    | objDeclarations objDeclaration {}
    ;

objDeclaration:
      functionDeclaration      {}
    | instantiation            {}
    ;

optConstructorParameters: /** complete **/
    %empty                 {}
    | L_PAREN parameterList R_PAREN  {}
    ;

dotPrefix:
    DOT                      {}
    ;

/**************************** PARSER ******************************/

parserDeclaration: /** complete **/
    parserTypeDeclaration optConstructorParameters { EnterScope(subparser); }
      L_BRACE parserLocalElements parserStates { ExitScope(subparser); } R_BRACE
                             {}
    ;

// Adding list annotation to avoid unncessary forks
parserLocalElements: /** complete, list **/
    %empty                                 {}
    | parserLocalElements parserLocalElement {}
    ;

parserLocalElement: /** complete **/
    constantDeclaration             {}
    | instantiation                   {}
    | variableDeclaration             {}
    | valueSetDeclaration             {}
    ;

parserTypeDeclaration: /** complete **/
    optAnnotations
        PARSER name       {}
        optTypeParameters {}
        L_PAREN parameterList R_PAREN {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
    ;

parserStates: /** complete, list **/
    parserState                     {}
    | parserStates parserState        {}
    ;

parserState: /** complete **/
    optAnnotations STATE name {}
      L_BRACE parserStatements transitionStatement R_BRACE
                                      {}
    ;

parserStatements: /** complete, list **/
    %empty                           {}
    | parserStatements parserStatement {}
    ;

parserStatement: /** complete **/
    assignmentOrMethodCallStatement {}
    | directApplication               {}
    | emptyStatement                  {}
    | variableDeclaration             {}
    | constantDeclaration             {}
    | parserBlockStatement            {}
    | conditionalStatement            {}  // experimental
    ;

parserBlockStatement: /** complete **/
    optAnnotations L_BRACE {}
      parserStatements R_BRACE {}
    ;

transitionStatement: /** complete **/
    %empty                      {}
    | TRANSITION stateExpression  {}
    ;

stateExpression: /** complete **/
    name SEMICOLON         {}
    | selectExpression {}
    ;

selectExpression: /** complete **/
    SELECT L_PAREN expressionList R_PAREN L_BRACE selectCaseList R_BRACE
                              {}
    ;

selectCaseList: /** complete, list **/
    %empty                     {}
    | selectCaseList selectCase  {}
    ;

selectCase:
    keysetExpression COLON name SEMICOLON
      {}
    ;

keysetExpression: /** complete **/
    tupleKeysetExpression     {}
    | simpleKeysetExpression    {}
    ;

tupleKeysetExpression: /** complete **/
    L_PAREN simpleKeysetExpression COMMA simpleExpressionList R_PAREN
                                {}
    | L_PAREN reducedSimpleKeysetExpression R_PAREN {}
    ;

simpleExpressionList: /** complete, list **/
    simpleKeysetExpression {}
    | simpleExpressionList COMMA simpleKeysetExpression {}
    ;

reducedSimpleKeysetExpression: /** complete **/
    // like simpleKeysetExpression, but without 'expression', to avoid a conflict
      expression MASK expression {}
    | expression RANGE expression  {}
    | DEFAULT                     {}
    | DONTCARE                         {}
    ;

simpleKeysetExpression: /** complete **/
    expression                  {}
    | expression MASK expression {}
    | expression RANGE expression  {}
    | DEFAULT                     {}
    | DONTCARE                         {}
    ;

valueSetDeclaration: /** complete **/
    optAnnotations
        VALUESET l_angle baseType r_angle L_PAREN expression R_PAREN name SEMICOLON
        {}
    | optAnnotations
        VALUESET l_angle tupleType r_angle L_PAREN expression R_PAREN name SEMICOLON
        {}
    | optAnnotations
        VALUESET l_angle typeName r_angle L_PAREN expression R_PAREN name SEMICOLON
        {}
    ;

/*************************** CONTROL ************************/

controlDeclaration: /** complete **/
    controlTypeDeclaration optConstructorParameters
      L_BRACE controlLocalDeclarations APPLY controlBody R_BRACE
        {}
    ;

controlTypeDeclaration: /** complete **/
        optAnnotations
        CONTROL name {}
        optTypeParameters {}
        L_PAREN parameterList R_PAREN {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
    ;

controlLocalDeclarations: /** complete, list **/
    %empty {}
    | controlLocalDeclarations controlLocalDeclaration {}
    ;

controlLocalDeclaration: /** complete **/
    constantDeclaration      {}
    | actionDeclaration        {}
    | tableDeclaration         {}
    | instantiation            {}
    | variableDeclaration      {}
    ;

controlBody: /** complete **/
    blockStatement {}
    ;

/*************************** EXTERN *************************/

externDeclaration: /** complete **/
    optAnnotations
        EXTERN nonTypeName {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
        optTypeParameters {}
        L_BRACE methodPrototypes R_BRACE 
    | optAnnotations EXTERN functionPrototype SEMICOLON { bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 2)); }
    | optAnnotations EXTERN name SEMICOLON // not present in latest language specification
    ;

methodPrototypes: /** complete, list **/
    %empty                           {}
    | methodPrototypes methodPrototype {}
    ;

functionPrototype:
    typeOrVoid
        name optTypeParameters {}
        L_PAREN parameterList R_PAREN {}
    ;

methodPrototype: /** complete **/
    optAnnotations functionPrototype SEMICOLON {}
    | optAnnotations ABSTRACT functionPrototype SEMICOLON {}  // experimental
    | optAnnotations TYPE_IDENTIFIER L_PAREN parameterList R_PAREN SEMICOLON  // constructor
                                        {}
    ;

/************************** TYPES ****************************/

typeRef: /** complete **/
    baseType                         {}
    | typeName                         {}
    | specializedType                  {}
    | headerStackType                  {}
    | tupleType                        {}
    ;

namedType: /** complete **/
    typeName                         {}
    | specializedType                  {}
    ;

prefixedType: /** complete **/
    TYPE_IDENTIFIER                  {}
    | dotPrefix TYPE_IDENTIFIER        {}
    ;

typeName: /** complete **/
    prefixedType                     {}
    ;

tupleType: /** complete **/
    TUPLE l_angle typeArgumentList r_angle    {}
    ;

headerStackType: /** complete **/
    typeName L_BRACKET expression R_BRACKET         {}
    | specializedType L_BRACKET expression R_BRACKET  {}
    ;

specializedType: /** complete **/
    typeName l_angle typeArgumentList r_angle {}
    ;

baseType:
    BOOL   {}
    | ERROR  {}
    | BIT    {}
    | STRING {}
    | INT    {}
    | BIT l_angle INTEGER r_angle
      {}
    | INT l_angle INTEGER r_angle
      {}
    | VARBIT l_angle INTEGER r_angle
      {}

    | BIT l_angle L_PAREN expression R_PAREN r_angle
      {}
    | INT l_angle L_PAREN expression R_PAREN r_angle
      {}
    | VARBIT l_angle L_PAREN expression R_PAREN r_angle
      {}
    ;

typeOrVoid:
    typeRef     {}
    | VOID        {}
    | IDENTIFIER  {}
        // This is necessary because template arguments may introduce the return type
    ;

optTypeParameters: /** complete **/
    %empty                    {}
    | typeParameters            {}
    ;

typeParameters: /** complete **/
    l_angle typeParameterList r_angle {}
    ;

typeParameterList: /** complete, list **/
    name {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
    | typeParameterList COMMA name {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
    ;

typeArg:
    typeRef                     {}
    | nonTypeName                 {}
        // This is necessary because template arguments may introduce the return type
    | VOID                        {}
    | DONTCARE                         {}
    ;

typeArgumentList: /** complete, list **/
    %empty                         {}
    | typeArg                        {}
    | typeArgumentList COMMA typeArg   {}
    ;

realTypeArg:
    typeRef                     {}
    | VOID                        {}
    | DONTCARE                         {}
    ;

// For use in contexts where the `<` might be a less-than rather than introducing a type
// argument list -- we only allow the token after `<` to be a TYPE_IDENTIFIER, not an ID
realTypeArgumentList: /** complete, list **/
    realTypeArg                        {}
    | realTypeArgumentList COMMA typeArg   {}
    ;

typeDeclaration: /** complete **/
    derivedTypeDeclaration     {}
    | typedefDeclaration SEMICOLON     {}
    | parserTypeDeclaration SEMICOLON  {}
    | controlTypeDeclaration SEMICOLON {}
    | packageTypeDeclaration SEMICOLON {}
    ;

derivedTypeDeclaration: /** complete **/
    headerTypeDeclaration            {}
    | headerUnionDeclaration           {}
    | structTypeDeclaration            {}
    | enumDeclaration                  {}
    ;

headerTypeDeclaration: /** complete **/
    optAnnotations HEADER name {} optTypeParameters {}
      L_BRACE structFieldList R_BRACE
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
    ;

structTypeDeclaration: /** complete **/
    optAnnotations STRUCT name optTypeParameters
      L_BRACE structFieldList R_BRACE
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
    ;

headerUnionDeclaration: /** complete **/
    optAnnotations HEADER_UNION name {} optTypeParameters {}
      L_BRACE structFieldList R_BRACE {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
    ;

structFieldList: /** complete, list **/
    %empty                           {}
    | structFieldList structField      {}
    ;

structField: /** complete **/
    optAnnotations typeRef name SEMICOLON  {}
    ;

enumDeclaration: /** complete **/
    optAnnotations
        ENUM name {}
        L_BRACE identifierList R_BRACE {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
    | optAnnotations ENUM typeRef name {}
	      L_BRACE specifiedIdentifierList R_BRACE {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
    ;

specifiedIdentifierList: /** complete, list **/
    specifiedIdentifier     {}
    | specifiedIdentifierList COMMA specifiedIdentifier {}
    ;

specifiedIdentifier: /** complete **/
    name ASSIGN initializer    {}
    ;

errorDeclaration: /** complete **/
    ERROR L_BRACE identifierList R_BRACE
        {}
    ;

matchKindDeclaration: /** complete **/
    MATCH_KIND L_BRACE identifierList R_BRACE
        {}
    ;

// Weird format when annonating this as a list
identifierList: /** complete, list **/
    name                    {}
    | identifierList COMMA name {}
    ;

typedefDeclaration: /** complete **/
    optAnnotations TYPEDEF typeRef name {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
    | optAnnotations TYPEDEF derivedTypeDeclaration name {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
    | optAnnotations TYPE typeRef name {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
    | optAnnotations TYPE derivedTypeDeclaration name {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
    ;

/*************************** STATEMENTS *************************/

assignmentOrMethodCallStatement: /** complete **/
// These rules are overly permissive, but they avoid some conflicts
      lvalue L_PAREN argumentList R_PAREN SEMICOLON
        {}

    | lvalue l_angle typeArgumentList r_angle L_PAREN argumentList R_PAREN SEMICOLON
        {}

    | lvalue ASSIGN expression SEMICOLON
        {}

    ;

emptyStatement: /** complete **/
    SEMICOLON      {}
    ;

exitStatement: /** complete **/
    EXIT SEMICOLON {}
    ;

returnStatement: /** complete **/
    RETURN SEMICOLON            {}
    | RETURN expression SEMICOLON {}
    ;

conditionalStatement: /** complete **/
    IF L_PAREN expression R_PAREN statement                 %prec THEN
        {}
    | IF L_PAREN expression R_PAREN statement ELSE statement  %prec THEN
        {}
    ;

// To support direct invocation of a control or parser without instantiation
directApplication: /** complete **/
    typeName DOT APPLY L_PAREN argumentList R_PAREN SEMICOLON {}
    ;

statement: /** complete **/
    assignmentOrMethodCallStatement  {}
    | directApplication                {}
    | conditionalStatement             {}
    | emptyStatement                   {}
    | blockStatement                   {}
    | returnStatement                  {}
    | exitStatement                    {}
    | switchStatement                  {}
    ;

blockStatement: /** complete **/
    optAnnotations L_BRACE {}
      statOrDeclList R_BRACE {}
    ;

statOrDeclList: /** complete, list **/
    %empty                                {}
    | statOrDeclList statementOrDeclaration {}
    ;

switchStatement: /** complete **/
    SWITCH L_PAREN expression R_PAREN L_BRACE switchCases R_BRACE {}
    ;

switchCases: /** complete, list **/
    %empty                   {}
    | switchCases switchCase   {}
    ;

switchCase: /** complete **/
    switchLabel COLON blockStatement {}
    | switchLabel COLON                {}
    ;

switchLabel:
    DEFAULT                  {}
    | nonBraceExpression       {}
    ;

statementOrDeclaration: /** complete **/
    variableDeclaration      {}
    | constantDeclaration      {}
    | statement                {}
    | instantiation            {}
    ;

/************************* TABLE *********************************/

tableDeclaration: /** complete **/
    optAnnotations
        TABLE name L_BRACE tablePropertyList R_BRACE
          {}
    ;

tablePropertyList: /** complete, list **/
    tableProperty                      {}
    | tablePropertyList tableProperty    {}
    ;

tableProperty: /** complete **/
    KEY ASSIGN L_BRACE keyElementList R_BRACE
        {}
    | ACTIONS ASSIGN L_BRACE actionList R_BRACE
        {}
    | optAnnotations optCONST ENTRIES ASSIGN L_BRACE entriesList R_BRACE
        {}
    | optAnnotations optCONST nonTableKwName ASSIGN initializer SEMICOLON
        {}
    ;

keyElementList: /** complete, list **/
    %empty                             {}
    | keyElementList keyElement          {}
    ;

keyElement: /** complete **/
    expression COLON name optAnnotations SEMICOLON
                                         {}
    ;

actionList: /** complete, list **/
    %empty {}
    | actionList optAnnotations actionRef SEMICOLON
        {}
    ;

actionRef: /** complete **/
    prefixedNonTypeName
        {}
    | prefixedNonTypeName L_PAREN argumentList R_PAREN
        {}
    ;

entry: /** complete **/
    keysetExpression COLON actionRef optAnnotations SEMICOLON
        {}
    ;

entriesList: /** complete, list **/
    entry                          {}
    | entriesList entry              {}
    ;

/************************* ACTION ********************************/

actionDeclaration: /** complete **/
    optAnnotations ACTION name L_PAREN parameterList R_PAREN blockStatement {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
    ;

/************************* VARIABLES *****************************/

variableDeclaration: /** complete **/
    annotations typeRef name optInitializer SEMICOLON {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
    | typeRef name optInitializer SEMICOLON {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
    ;

constantDeclaration: /** complete **/
    optAnnotations CONST typeRef name ASSIGN initializer SEMICOLON
                                     {}
    ;

optInitializer: /** complete **/
    %empty                           {}
    | ASSIGN initializer                  {}
    ;

initializer: /** complete **/
    expression                          {}
    ;

/**************** Expressions ****************/

functionDeclaration: /** complete **/
    functionPrototype blockStatement   {}
    ;

argumentList: /** complete, list **/
    %empty                             {}
    | nonEmptyArgList                    {}
    ;

nonEmptyArgList: /** complete, list **/
    argument                           {}
    | nonEmptyArgList COMMA argument       {}
    ;

argument: /** complete **/
    expression                         {}
    | name ASSIGN expression                {}
    | DONTCARE                                {}
    ;

expressionList: /** complete, list **/
    %empty                             {}
    | expression                         {}
    | expressionList COMMA expression      {}
    ;

prefixedNonTypeName:
    nonTypeName                        {}
    | dotPrefix nonTypeName              {}
    ;

dot_name: /** complete **/
    DOT {} name {}
    ;

lvalue: /** complete **/
    prefixedNonTypeName                {}
    | THIS                               {}  // experimental
    | lvalue dot_name %prec DOT          {}
    | lvalue L_BRACKET expression R_BRACKET          {}
    | lvalue L_BRACKET expression COLON expression R_BRACKET {}
    ;

expression: /** complete, list **/
    INTEGER                            {}
    | STRING_LITERAL                     {}
    | TRUE                               {}
    | FALSE                              {}
    | THIS                               {}  // experimental
    | nonTypeName                        {}
    | dotPrefix nonTypeName              {}
    | expression L_BRACKET expression R_BRACKET      {}
    | expression L_BRACKET expression COLON expression R_BRACKET {}
    | L_BRACE expressionList R_BRACE             {}
    | L_BRACE kvList R_BRACE                     {}
    | L_PAREN expression R_PAREN                 {}
    | NOT expression %prec PREFIX        {}
    | COMPLEMENT expression %prec PREFIX        {}
    | MINUS expression %prec PREFIX        {}
    | PLUS expression %prec PREFIX        {}
    | typeName dot_name %prec DOT
        {}
    | ERROR DOT name
        {}
    | expression dot_name %prec DOT      {}
    | expression MUL expression          {}
    | expression DIV expression          {}
    | expression MOD expression          {}
    | expression PLUS expression          {}
    | expression MINUS expression          {}
    | expression PLUS_SAT expression        {}
    | expression MINUS_SAT expression        {}
    | expression SHL expression         {}
    | expression R_ANGLE_SHIFT R_ANGLE expression %prec R_ANGLE_SHIFT
        {}
    | expression LE expression         {}
    | expression GE expression         {}
    | expression l_angle expression %prec L_ANGLE
                                         {}
    | expression R_ANGLE expression          {}
    // | expression R_ANGLE_SHIFT expression          {}
    | expression NE expression         {}
    | expression EQ expression         {}
    | expression BIT_AND expression          {}
    | expression BIT_XOR expression          {}
    | expression BIT_OR expression          {}
    | expression PP expression         {}
    | expression AND expression         {}
    | expression OR expression         {}
    | expression QUESTION expression COLON expression {}
    | invokingExpression {}
    ;
invokingExpression: /** complete, list **/
    | expression l_angle realTypeArgumentList r_angle L_PAREN argumentList R_PAREN
        {}
    | expression L_PAREN argumentList R_PAREN
        {}
    | namedType L_PAREN argumentList R_PAREN
        {}
    | L_PAREN typeRef R_PAREN expression %prec PREFIX {}
    ;

nonBraceExpression: /** complete, list **/
    INTEGER                            {}
    | STRING_LITERAL                     {}
    | TRUE                               {}
    | FALSE                              {}
    | THIS                               {}  // experimental
    | nonTypeName                        {}
    | dotPrefix nonTypeName              {}
    | nonBraceExpression L_BRACKET expression R_BRACKET      {}
    | nonBraceExpression L_BRACKET expression COLON expression R_BRACKET {}
    | L_PAREN expression R_PAREN                 {}
    | NOT expression %prec PREFIX        {}
    | COMPLEMENT expression %prec PREFIX        {}
    | MINUS expression %prec PREFIX        {}
    | PLUS expression %prec PREFIX        {}
    | typeName dot_name %prec DOT
        {}
    | ERROR DOT name
        {}
    | nonBraceExpression dot_name %prec DOT      {}
    | nonBraceExpression MUL expression          {}
    | nonBraceExpression DIV expression          {}
    | nonBraceExpression MOD expression          {}
    | nonBraceExpression PLUS expression          {}
    | nonBraceExpression MINUS expression          {}
    | nonBraceExpression PLUS_SAT expression        {}
    | nonBraceExpression MINUS_SAT expression        {}
    | nonBraceExpression SHL expression         {}
    | nonBraceExpression R_ANGLE_SHIFT R_ANGLE expression %prec R_ANGLE_SHIFT
        {}
    | nonBraceExpression LE expression         {}
    | nonBraceExpression GE expression         {}
    | nonBraceExpression l_angle expression %prec L_ANGLE
                                         {}
    | nonBraceExpression R_ANGLE expression          {}
    | nonBraceExpression NE expression         {}
    | nonBraceExpression EQ expression         {}
    | nonBraceExpression BIT_AND expression          {}
    | nonBraceExpression BIT_XOR expression          {}
    | nonBraceExpression BIT_OR expression          {}
    | nonBraceExpression PP expression         {}
    | nonBraceExpression AND expression         {}
    | nonBraceExpression OR expression         {}
    | nonBraceExpression QUESTION expression COLON expression {}
    | nonBraceExpression l_angle realTypeArgumentList r_angle L_PAREN argumentList R_PAREN
        {}
    | nonBraceExpression L_PAREN argumentList R_PAREN
        {}
    | namedType L_PAREN argumentList R_PAREN
        {}
    | L_PAREN typeRef R_PAREN expression %prec PREFIX {}
    ;

intOrStr:
    INTEGER                    {}
    | STRING_LITERAL             {}
    ;

intList:
    INTEGER                    {}
    | intList COMMA INTEGER        {}
    ;

intOrStrList:
    intOrStr                   {}
    | intOrStrList COMMA intOrStr  {}
    ;

strList:
    STRING_LITERAL             {}
    | strList COMMA STRING_LITERAL {}
    ;

l_angle : L_ANGLE | L_ANGLE_ARGS ;
r_angle : R_ANGLE | R_ANGLE_SHIFT ;

/*****************************************************************************/

%%

/** True when statistics should be output. */
private boolean languageStatistics = false;

/** Turn on error reporting. */
private static boolean showErrors = false;

/** Turn on debugging messages. */
private static boolean debug = false;

/** Turn on checkers. */
private static boolean enableCheckers = false;

/** Turn on checkers. */
private static List<String> extraConstraints = null;

/** Turn on function analysis. */
private static boolean enableFunctionAnalysis = false;

/** A symbol table for analysis. */
private P4Context.SymbolTable functionTable;

/** Turn on kconfig feature model clauses. */
private boolean hasClauses = false;

/** The clauses for the kconfig feature model. */
private Clauses featureClauses = null;

/** The kconfig feature model solver. */
private ISolver featureSolver;

/** The assumptions of the feature model, i.e., non-arch config vars. */
private VecInt modelAssumptions;

/**
 * Turn language statistics collection on.  Default is off.
 *
 * @param b True is on.
 */
public void collectStatistics(boolean b) {
  languageStatistics = b;
}

/**
 * Show errors.
 *
 * @param b True is on.
 */
public void showErrors(boolean b) {
  showErrors = b;
}

/**
 * Show debugging messages.
 *
 * @param b True is on.
 */
public void debug(boolean b) {
  debug = b;
}

/**
 * Enable checkers.
 *
 * @param b Enable checkers if true.
 */
public void enableCheckers(boolean b) {
  this.enableCheckers(b, null);
}

/**
 * Enable checkers.
 *
 * @param b Enable checkers if true.
 * @param extraConstraints Extra constraints to SAT solver.
 */
public void enableCheckers(boolean b, List<String> extraConstraints) {
  this.enableCheckers = b;
  if (null == extraConstraints) {
    // avoid having to check for null
    extraConstraints = new ArrayList<String>();
  }
  this.extraConstraints = extraConstraints;
}

/**
 * Enable function analysis.
 */
public void enableFunctionAnalysis() {
  this.enableFunctionAnalysis = true;
  this.functionTable = new P4Context.SymbolTable();
}

/**
 * Add kconfig feature model clauses.
 *
 * @param clauses The clauses.
 */
public void addClauses(Clauses clauses, int[] assumptions) {
  if (null != assumptions) {
    this.modelAssumptions = new VecInt(assumptions);
  } else {
    this.modelAssumptions = new VecInt(new int[0]);
  }

  if (null != clauses) {
    this.hasClauses = true;
    this.featureClauses = clauses;
    this.featureSolver = SolverFactory.newDefault();
    this.featureSolver.newVar(clauses.getNumVars());
    this.featureSolver.setExpectedNumberOfClauses(clauses.size());

    try {
      for (List<Integer> clause : clauses) {
        int[] cint = new int[clause.size()];
        int i = 0;
        for (Integer val : clause) {
          cint[i++] = val;
        }
        this.featureSolver.addClause(new VecInt(cint));
      }
    } catch (ContradictionException e) {
      e.printStackTrace();
      System.exit(1);
    }
  } else {
    this.hasClauses = false;
    this.featureClauses = null;
  }
}

/**
 * Get the checker symbol table.
 *
 * @return The checker symbol table.
 */
public P4Context.SymbolTable getFunctionTable() {
  return this.functionTable;
}

/**
 * A helper function to get the value of a node on the stack, which
 * corresponds to the value of the component of a production.  Unlike
 * bison, this is numbered by the stack, i.e., the closest component
 * to the action has the lowest number, starting with 1.
 *
 * @param subparser The reference to the subparser.
 * @param number The component number, where 1 is the component to the
 * left of the action, and increasing in number while going towards
 * the beginning of the production.
 * @return The node value of the component.
 */
private static Node getNodeAt(Subparser subparser, int component) {
  return (Node) (subparser.stack.get(component).value);
}

private static String getStringAt(Subparser subparser, int component) {
  return ((Syntax) getNodeAt(subparser, component)).toLanguage().getTokenText();
}

/**
 * A helper function to set the type property of the given node.  The
 * given value will be first cast to a Node.
 *
 * @param value A node object.
 * @param type The type to set.
 */
private static void setType(Object value, Type type) {
  ((Node) value).setProperty(Constants.TYPE, type);
}

private static void error(String msg) {
  if (showErrors) {
    System.err.println("error: " + msg);
  }
  /* System.exit(1); */
}

// ---------- Parsing-only context

/**
 * Compute and store the base type indicated by the specifications
 * property of the given node.
 */
public void saveBaseType(Subparser subparser, Node typespec) {
  if (typespec.getProperty(SPECS) == null) {
    if (showErrors) {
      System.err.println("error: no specs available");
    }
    return;
  }
  ((P4Context) subparser.scope).lastSeenType =
    ((Specifiers) typespec.getProperty(SPECS)).getType();
}

/**
 * Return the last seen type.
 */
public Type lastSeenType(Subparser subparser) {
  return ((P4Context) subparser.scope).lastSeenType;
}

private static class Binding {
  public Language ident;
  public Type type;

  public Binding(Language ident, Type type) {
    this.ident = ident;
    this.type = type;
  }
}

private boolean findToken(Object n, P4Tag tag) {
  if (n instanceof Language && ((Language) n).tag() == tag) {
    return true;
  } else if (n instanceof Syntax) {
    return ((Syntax) n).getTokenText().equals(tag.getText());
  } else if (n instanceof Node) {
    boolean b = false;
    for (Object o : ((Node) n)) {
      b |= findToken(o, tag);
      if (b) return true;
    }
    return false;
  } else if (n instanceof PresenceCondition) {
    // ignore
    return false;
  } else {
    System.err.println(n.getClass().getSimpleName());
    return false;
  }
}

public void bindFunDef(Subparser subparser, Node typespec, Node declarator) {
  if (getident(declarator).equals("ERR_PTR")) {
    System.err.println(typespec);
    System.err.println(declarator);
  }

  bindIdent(subparser, typespec, declarator, STField.GLOBAL_FUNDEF);
}

public void bindIdent(Subparser subparser, Node typespec, Node declarator) {
   bindIdent(subparser, typespec, declarator, null, false);
}


/** Another overloaded function for bindIdent to explicity specify it's a TYPDEF value
 * 
 * Cases like typeParameterList don't have a unique preceding value to identify
 * the value as a typedef value. So can use this overloaded function to explicity
 * specify that the value is a typedef.
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, boolean typeVar) {
   bindIdent(subparser, typespec, declarator, null, typeVar);
}

/** Overloaded function with original parameters
 *
 * Original bindIdent (from cparser.y) function is modified with a new parameter,
 * this functions overloads the modified function to behave like how it is in cparser
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, STField alsoSet) {
  bindIdent(subparser, typespec, declarator, alsoSet, false);
}

/** typespec might be null for declarations and definitions without a
 * type spec; alsoSet is used to set another symbol table bit and
 * might be null.
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, STField alsoSet, boolean typeVar) {
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // TODO need to hoist conditionals from typespec and declarator
  // around entire declaration by combining with each other

  // TODO causing an infinite loop on 3.12 init/main.c
  /* if (typespec.getProperty(SPECS) == null) { */
  /*   System.err.println("error: no specs available"); */
  /* } else { */
  /*   Type baseType = ((Specifiers) typespec.getProperty(SPECS)).getType(); */
  /*   Binding binding = grokdeclarator(declarator, baseType); */
  /*   Type type = binding.type; */
  /*   Language ident = binding.ident; */

  /*   System.err.println(ident + " = " + type); */
  /* } */

  // TODO replace old-style typedef checking by using specs above
  Language ident = getident(declarator);


  // Check whether the declaration is a typedef.  This assumes that
  // the typedef keyword is the first token of the declaration.
  boolean typedef = false;

  if (null != typespec) {
    Object a = typespec;
    while (true) {
      if ( ! (a instanceof Syntax)) {
        Node n = (Node) a;
        if (n.hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
          // When it's a conditional node, the first child is a
          // presence condition, the second is the first AST child.
          a = n.get(1);
        } else {
          a = n.get(0);
        }
      } else if (a instanceof Pair) {
        a = ((Pair) a).head();
      } else {
        break;
      }
    }
    Language t = (Language) a;
    if (P4Tag.TYPEDEF == t.tag() || P4Tag.STRUCT == t.tag() || P4Tag.CONTROL == t.tag() || 
        P4Tag.PACKAGE == t.tag() || P4Tag.EXTERN == t.tag() || P4Tag.HEADER == t.tag() ||
        P4Tag.ENUM == t.tag() || P4Tag.PARSER == t.tag() || P4Tag.HEADER_UNION == t.tag() ||
        P4Tag.TYPE == t.tag()) {
      // Bind a typedef name.
      typedef = true;

      if (languageStatistics) {
        if (typedef) {
          Location location = subparser.lookahead.token.syntax.getLocation();
          System.err.println(String.format("typedef %s %s", ident, location));
        }
      }
    } else {
      // Binding a variable name.
      typedef = false;
    }
  }

  if (showErrors) {
    System.err.println("bind: " + ident.getTokenText() + " " + typedef);
  }
  if (debug) {
    System.err.println("def: " + ident.getTokenText() + " " + alsoSet);
  }
  // System.err.println("Setting variable: " + ident.getTokenText() + " to type: " + ((typedef || typeVar) ? "TYPDEF" : "IDENT"));
  STField field = (typedef || typeVar) ? STField.TYPEDEF : STField.IDENT;
  scope.getSymbolTable().setbool(ident.getTokenText(), field, true, presenceCondition);
  if (null != alsoSet) {
    scope.getSymbolTable().setbool(ident.getTokenText(), alsoSet, true, presenceCondition);
  }
  /* if (typedef) { */
  /*   scope.getSymbolTable().setbool(ident.getTokenText(), STField.TYPEDEF, true, presenceCondition); */
  /* } else { */
  /*   scope.getSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition); */
  /* } */
  /* scope.bind(ident.getTokenText(), typedef, presenceCondition); */
}

private static Binding grokdeclarator(Node declarator, Type type) {
  Language ident = null;
  
  while (null != declarator) {
    if (declarator.getName().equals("SimpleDeclarator")) {
      ident = ((Syntax) declarator.get(0)).toLanguage();
      declarator = null;
      
    } else if (declarator.getName().equals("ParenIdentifierDeclarator")) {
      Node parenIdentDecl = null;

      switch (declarator.size()) {
      case 3:
      parenIdentDecl = (Node) declarator.get(1);
        break;
      default:
      error("unexpected grammar structure for " + declarator.getName());
        break;
      }
      declarator = parenIdentDecl;
      
    } else if (declarator.getName().equals("UnaryIdentifierDeclarator")) {
      Node typeQual;
      Node identDecl;
      switch (declarator.size()) {
      case 2:
      typeQual = null;
        identDecl = (Node) declarator.get(1);
        break;
      case 3:
      typeQual = (Node) declarator.get(1);
        identDecl = (Node) declarator.get(2);
        break;
      default:
      typeQual = null;
        identDecl = null;
        error("unexpected grammar structure for " + declarator.getName());
        break;
      }
      
      if (null != typeQual) {
        Specifiers specs = (Specifiers) typeQual.getProperty(SPECS);
        type = specs.annotateBase(new PointerT(type).annotate());
      } else {
        type = new PointerT(type);
      }

      declarator = identDecl;
      
    } else if (declarator.getName().equals("ArrayDeclarator")) {
      Node parenIdentDecl = (Node) declarator.get(0);
      Node arrayAbsDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(arrayAbsDecl, type);
      declarator = parenIdentDecl;
      
    } else if (declarator.getName().equals("PostfixIdentifierDeclarator")) {
      Node unaryIdentDecl = (Node) declarator.get(0);
      Node postfixAbsDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(postfixAbsDecl, type);
      declarator = unaryIdentDecl;

    } else if (declarator.getName().equals("FunctionDeclarator")) {
      Node parenIdentDecl = (Node) declarator.get(0);
      Node postfixFuncDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(postfixFuncDecl, type);
      declarator = parenIdentDecl;

    } else {
      if (debug) {
        System.err.println("TODO support declarator " + declarator.getName());
      }
      declarator = null;
    }
  }

  return new Binding(ident, type);
}

private static Type grokabsdeclarator(Node absdeclarator, Type type) {
  if (absdeclarator.getName().equals("ArrayAbstractDeclarator")) {
    while (null != absdeclarator) {
      Node arraySize = null;
      switch (absdeclarator.size()) {
      case 0:
      arraySize = null;
        absdeclarator = null;
        break;
      case 1:
      arraySize = (Node) absdeclarator.get(0);
        absdeclarator = null;
        break;
      case 2:
      arraySize = (Node) absdeclarator.get(1);
        absdeclarator = (Node) absdeclarator.get(0);
        break;
      default:
      error("unexpected grammar structure for " + absdeclarator.getName());
      }
      type = new ArrayT(type);
    }
      
  } else if (absdeclarator.getName().equals("PostfixingFunctionDeclarator")) {
    Node parms = null;
    switch (absdeclarator.size()) {
    case 1:
    parms = (Node) absdeclarator.get(0);
      break;
    default:
    error("unexpected grammar structure for " + absdeclarator.getName());
      break;
    }

    FunctionT function = getParameterTypes(parms);

    function.setResult(type);
    type = function;

  } else {
    if (debug) {
      System.err.println("TODO support absdeclarator " + absdeclarator.getName());
    }
  }
  
  return type;
}

private static FunctionT getParameterTypes(Node parms) {
  // TODO flesh this out and do type checking
  boolean varArgs = false;
  ArrayList<Type> types = new ArrayList<Type>();

  if (parms != null && parms.size() > 0) {
    parms = (Node) parms.get(0);
    /* System.err.println(parms); */
    switch (parms.size()) {
    case 2:
    varArgs = true;
      // fall through
    case 1:
    parms = (Node) parms.get(0);
      break;
    default:
    error("unexpected grammar structure for " + parms.getName());
      break;
    }
    // parms is now a list node containing ParameterDeclaration elements
    if (parms.getName().equals("ParameterList")) {
      for (Object o : parms) {
        GNode n = (GNode) o;
        if (n.getName().equals("Conditional")) {
          boolean isCond = true;
          for (Object o_parm : n) {
            if (isCond) {
              // TODO get presence condition
            } else {
              GNode parm = (GNode) o_parm;
              Node typespec = (Node) parm.get(0);
              // TODO remove once specs are done
              if (typespec.getProperty(SPECS) == null) continue;
              Type baseType = ((Specifiers) typespec.getProperty(SPECS)).getType();
              if (parm.size() > 1) {
                Node declarator = (Node) parm.get(1);
                if (parm.getName().equals("ParameterIdentifierDeclaration")) {
                  Binding binding = grokdeclarator(declarator, baseType);
                  Language ident = binding.ident;
                  Type type = binding.type;
                  String name = binding.ident.getTokenText();
                  types.add(VariableT.newParam(type, name));

                } else if (parm.getName().equals("ParameterAbstractDeclaration")) {
                  Type type = grokabsdeclarator(declarator, baseType);
                  types.add(type);
                } else {
                  if (showErrors) {
                    System.err.println("unsupported parameter declaration " + parm.getName());
                  }
                }
              } else {
                types.add(baseType);
              }
            }
            isCond = isCond ? false : true;
          }
        } else {
          if (showErrors) {
            System.err.println("parameter is no conditional");
          }
        }
      }
    } else {
      if (showErrors) {
        System.err.println("unexpected parameter list node");
      }
    }
  }

  FunctionT function = new FunctionT(null, types, varArgs);
  function.addAttribute(Constants.ATT_STYLE_NEW);
  return function;
}

public void BindVar(Subparser subparser) {
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // Get the identifier in the declarator.
  Object b = stack.get(1).value;
  Language<?> ident = getident(b);

  // Bind variable name.
  scope.getSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition);
  /* scope.bind(ident.getTokenText(), false, presenceCondition); */
}

public void BindEnum(Subparser subparser) {
  StackFrame stack  = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // Get the identifier in the declarator.  The identifier must
  // occur after an IdentifierOrTypedefName token.
  Object b = stack.get(1).value;
  String ident = getident(b).getTokenText();

  // Bind variable name.
  scope.getSymbolTable().setbool(ident, STField.IDENT, true, presenceCondition);
  /* scope.bind(ident, false, presenceCondition); */
}

public void useIdent(Subparser subparser, Node ident) {
  P4Context scope = (P4Context) subparser.scope;
  String name = ident.getTokenText();

  if (debug) {
    System.err.println("use: " + name);
  }
  if (enableCheckers) {
    PresenceCondition identPresenceCond = scope.symbolPresenceCond(name, STField.IDENT);
    if (null != identPresenceCond && ! identPresenceCond.isFalse()) {
      PresenceCondition not = identPresenceCond.not();
      PresenceCondition andnot = subparser.getPresenceCondition().and(not);
      /* not.delRef(); */
      if (! andnot.isFalse()) {
        boolean satWithKconfig = true;
        boolean contradiction = false;
        int[] model = null;
        // check andnot against kconfig feature model
        if (this.hasClauses) {
          // use double negation to get andnot in cnf form
          PresenceCondition notandnot = andnot.not();
          /* System.err.println(notandnot); */
          List allsat = (List) notandnot.getBDD().allsat();
          ArrayList<ArrayList<Integer>> bugClauses =
            new ArrayList<ArrayList<Integer>>();
      
          for (Object o : allsat) {        
            byte[] sat = (byte[]) o;
            ArrayList<Integer> clause = new ArrayList<Integer>();
            for (int i = 0; i < sat.length; i++) {
              // convert to solver's varnum
              // look up i in variable manager
              // if varname exists in clauses, then add to clause
              int sign = 1;
              
              switch (sat[i]) {
              case 1:
              // negate again
                sign = -1;
              case 0:
              String varname = notandnot.presenceConditionManager().getVariableManager().getName(i);
                if (varname.startsWith("(defined ")) {
                  varname = varname.substring(9, varname.length() - 1);
                  /* System.err.println(varname); */
                  if (this.featureClauses.getVarmap().containsKey(varname)) {
                    int var = this.featureClauses.getVarmap().get(varname);
                    var = sign * var;
                    clause.add(var);
                  }
                }
                break;
              }
            }
            if (clause.size() > 0) {
              /* System.err.println(clause); */
              bugClauses.add(clause);
            }
          }

          // add extra constraints
          for (String extraConstraint : extraConstraints) {
            this.featureClauses.addClauses(extraConstraint);
          }
          // remove them to avoid adding them again the next check
          extraConstraints.clear();

          try {
            ISolver featureSolver = SolverFactory.newDefault();
            featureSolver.newVar(this.featureClauses.getNumVars());
            /* featureSolver.setExpectedNumberOfClauses(this.featureClauses.size() + bugClauses.size()); */

            for (List<Integer> clause : this.featureClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              featureSolver.addClause(new VecInt(cint));
            }

            for (List<Integer> clause : bugClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              IConstr curConstr =
                featureSolver.addClause(new VecInt(cint));
            }

            ISolver bugSolver = SolverFactory.newDefault();
            bugSolver.newVar(this.featureClauses.getNumVars());
            bugSolver.setExpectedNumberOfClauses(bugClauses.size());

            for (List<Integer> clause : bugClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              IConstr curConstr =
                bugSolver.addClause(new VecInt(cint));
            }

            IProblem simpleProblem = new ModelIterator(bugSolver);
            boolean satWithoutKconfig = simpleProblem.isSatisfiable();
            
            /* IProblem problem = featureSolver; */
            IProblem problem = new ModelIterator(featureSolver);
            if (problem.isSatisfiable(modelAssumptions)) {
              satWithKconfig = true;
              if (debug) {
                System.err.println("computing model");
              }
              model = problem.model();
            } else {
              satWithKconfig = false;
              if (satWithoutKconfig) {
                System.err.print("invalid config invalidated by kconfig ");
              } else {
                System.err.print("invalid config invalidated by bug clauses alone ");
              }
              System.err.println(name + " at " + ident.getLocation());
            }
          } catch (ContradictionException e) {
            contradiction = true;
          } catch (TimeoutException e) {
            e.printStackTrace();
            /* System.exit(1); */
          }
          notandnot.delRef();
        }
        if (contradiction) {
          System.err.print("invalid config invalidated by contradiction " + name + " at " + ident.getLocation());
        } else if (satWithKconfig) {
          /* PresenceCondition sat = andnot.satOne(); */
          if (null != scope.symbolPresenceCond(name, STField.GLOBAL_FUNDEF) || null != scope.symbolPresenceCond(name, STField.STATIC_FUNDEF)) {
            System.err.println("found for function def");
          }
          System.err.println("found invalid configuration on "
                             + name + " at " + ident.getLocation());
          /* System.err.println("config " + andnot); */
          /* System.err.println("identPresenceCond: " + identPresenceCond); */
          /* /\* System.err.println("undefined under " + not); *\/ */
          /* /\* System.err.println("used under      " + subparser.getPresenceCondition()); *\/ */
          /* if (this.showExample) { */
          if (true) {
            if (null != model) {
              System.err.print("model: ");
              String delim = "[";
              for (int i = 0; i < model.length; i++) {
                if (model[i] > 0) {
                  System.err.print(delim + featureClauses.getVarName(model[i]));
                  delim = ",";
                }
              }
              System.err.println("]");
            }
          }
          /* sat.delRef(); */
        }
      } else {
        if (debug) {
          System.err.println("valid function call " + name + " at " + ident.getLocation());
          /* System.err.println("not: " + not); */
          /* System.err.println("subparser.getPresenceCondition() " + subparser.getPresenceCondition()); */
        }
      }
      not.delRef();
      andnot.delRef();

      /* PresenceCondition and = subparser.getPresenceCondition().and(identPresenceCond); */
      /* if (and.isFalse()) { */
      /*   System.err.println("found infeasible configuration on " + name + " at " + ident.getLocation() + " defined in " + identPresenceCond); */
      /* } */
      /* and.delRef(); */

      // update configurations the identifier is used in
      scope.getSymbolTable().setbool(name, STField.USED, true, subparser.getPresenceCondition());
    } else {
      if (debug) {
        System.err.println("not an identifier in any config " + name + " at " + ident.getLocation());
      }
    }
  }
}

public void callFunction(Subparser subparser, Node fun, Node parms) {
  if (fun.getName().equals("PrimaryIdentifier") && enableFunctionAnalysis) {
    /* P4Context scope = (P4Context) subparser.scope; */
    /* String name = ((Language<?>) fun.get(0)).getTokenText(); */
    /* scope.getSymbolTable().setbool(name, STField.FUNCALL, true, subparser.getPresenceCondition()); */
    String name = ((Language<?>) fun.get(0)).getTokenText();
    functionTable.setbool(name, STField.FUNCALL, true, subparser.getPresenceCondition());
    return;
  }

  // TODO do later
  if (true) {
    return;
  }
  
  String name = ((Syntax) fun.get(0)).getTokenText();
  P4Context scope = (P4Context) subparser.scope;

  if (debug) {
    System.err.println("function call: " + name);
  }
  if (enableCheckers) {
    PresenceCondition funPresenceCond = scope.symbolPresenceCond(name, STField.GLOBAL_FUNDEF).or(scope.symbolPresenceCond(name, STField.STATIC_FUNDEF));
    if (null != funPresenceCond && ! funPresenceCond.isFalse()) {
      PresenceCondition not = funPresenceCond.not();
      PresenceCondition andnot = subparser.getPresenceCondition().and(not);
      not.delRef();
      if (! andnot.isFalse()) {
        /* PresenceCondition sat = andnot.satOne(); */
        /* System.err.println("found invalid configuration on function call " + name + " at " + fun.getLocation() + " config " + sat);        sat.delRef(); */
      }
      andnot.delRef();

      PresenceCondition and = subparser.getPresenceCondition().and(funPresenceCond);
      if (and.isFalse()) {
        System.err.println("found infeasible configuration on function call " + name + " at " + fun.getLocation() + " defined in " + funPresenceCond);
      }
      and.delRef();

      // update configurations the function is used in
      scope.getSymbolTable().setbool(name, STField.USED, true, subparser.getPresenceCondition());
    } else {
      if (debug) {
        System.err.println("checker error: " + name + " not a function in any configuration");
      }
    }
    funPresenceCond.delRef();
  }
}

public void EnterScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope = ((P4Context) subparser.scope).enterScope(presenceCondition);
}

public void ExitScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope = ((P4Context) subparser.scope).exitScope(presenceCondition);
}

public void ExitReentrantScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).exitReentrantScope(presenceCondition);
}

public void ReenterScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).reenterScope(presenceCondition);
}

public void KillReentrantScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).killReentrantScope(presenceCondition);
}

/**
 * Find the identifier or typedef name in a declarator.  Assume
 * the first identifier in the subtree is the var or typedef name.
 *
 * @param o The semantic value.
 * @return The first identifier in the subtree or null if there is
 * none.
 */
private static Language getident(Object o) {
  if (o instanceof Language) {
    Language token = ((Language) o);

    if (P4Tag.IDENTIFIER == token.tag() || P4Tag.TYPE_IDENTIFIER == token.tag()) {
      return token;

    } else {
      return null;
    }

  } else if (o instanceof Pair) {
    Pair<?> b = (Pair<?>) o;

    while (b != Pair.empty()) {
      Object child = b.head();

      if (null != child) {
        Language ident = getident(child);

        if (null != ident) {
          return ident;
        }
      }

      b = b.tail();
    }

    return null;
  } else if (o instanceof PresenceConditionManager.PresenceCondition) {
    return null;
  } else if (o instanceof Error) {
    return null;
  } else {
    Node b = (Node) o;

    for (int i = 0; i < b.size(); i++) {
      Object child = b.get(i);

      if (null != child) {
        Language ident = getident(child);

        if (null != ident) {
          return ident;
        }
      }
    }

    return null;
  }
}

// ---------- Specifiers

private static String SPECS = "superc.p4parser.Specifiers";

private static class Specifiers {
  /** Presence condition. */
  public PresenceCondition pc;

  /** True if there is a type error. */
  public boolean error;

  /** The type-error message. */
  public String error_message;

  /** The flag for whether a tag reference is a declaration. */
  public boolean refIsDecl;

  /** The type, if any. */
  public Type type;

  /** The storage class attribute, if any. */
  public Attribute storage;

  /** The thread-local attribute, if any. */
  public Attribute threadlocal;

  /** The inline attribute, if any. */
  public Attribute function;

  /** Any other attributes. */
  public List<Attribute> attributes;

  // The internal state for tracking type specifiers.
  public boolean seenSigned;
  public boolean seenUnsigned;
  public boolean seenBool;
  public boolean seenChar;
  public boolean seenShort;
  public boolean seenInt;
  public int     longCount;
  public boolean seenFloat;
  public boolean seenDouble;
  public boolean seenComplex;

  public Specifiers() {
  }

  /* public Specifiers(PresenceCondition pc) { */
  /*   this.pc = pc.addRef(); */
  /* } */

  public Specifiers(PresenceCondition pc, Specifiers s) {
    /* this(pc); */
    this.error = s.error;
    this.error_message = s.error_message;
    this.refIsDecl = s.refIsDecl;
    this.type = s.type;
    this.storage = s.storage;
    this.threadlocal = s.threadlocal;
    this.function = s.function;
    this.attributes = s.attributes;
    this.seenSigned = s.seenSigned;
    this.seenUnsigned = s.seenUnsigned;
    this.seenBool = s.seenBool;
    this.seenChar = s.seenChar;
    this.seenShort = s.seenShort;
    this.seenInt = s.seenInt;
    this.longCount = s.longCount;
    this.seenFloat = s.seenFloat;
    this.seenDouble = s.seenDouble;
    this.seenComplex = s.seenComplex;
  }

  /**
   * Add given specs to this set of specs.  Adds in-place and returns
   * this updated specs object.
   **/
  public Specifiers addSpecs(Specifiers other) {
    if (other.error) {
      this.setError(other.error_message);
      return this;
    }

    if (null != other.type) {
      if (null != this.type) {
        /* System.err.println("1"); */
        this.multipleTypes();
      } else {
        this.type = other.type;
      }
    }

    if (other.seenChar) {
      if (this.hasType()) {
        /* System.err.println("2"); */
        this.multipleTypes();
      } else {
        this.seenChar = true;
      }
    }

    if (other.seenShort) {
      if (this.seenBool || this.seenChar || this.seenShort || (0 < this.longCount) ||
          this.seenFloat || this.seenDouble || this.seenComplex ||
          (null != this.type)) {
        /* System.err.println("3"); */
        this.multipleTypes();
      } else {
        this.seenShort = true;
      }
    }

    if (other.seenInt) {
      if (this.seenBool || this.seenChar || this.seenInt ||
          this.seenFloat || this.seenDouble || this.seenComplex ||
          (null != this.type)) {
        /* System.err.println("4"); */
        this.multipleTypes();
      } else {
        this.seenInt = true;
      }
    }

    for (int i = 0; i < other.longCount; i++) {
      if (this.seenBool || this.seenChar || this.seenShort || (1 < this.longCount) ||
          this.seenFloat ||
          ((this.seenDouble || this.seenComplex) &&
           (0 < this.longCount)) ||
          (null != this.type)) {
        /* System.err.println("5"); */
        this.multipleTypes();
      } else {
        this.longCount++;
      }
    }

    if (other.seenFloat) {
      if (this.seenBool || this.seenChar || this.seenShort || this.seenInt || (0 < this.longCount) ||
          this.seenDouble ||
          (null != this.type)) {
        /* System.err.println("6"); */
        this.multipleTypes();
      } else {
        this.seenFloat = true;
      }
    }

    if (other.seenDouble) {
      if (this.seenBool || this.seenChar || this.seenShort || this.seenInt || (1 < this.longCount) ||
          this.seenFloat ||
          (null != this.type)) {
        /* System.err.println("7"); */
        this.multipleTypes();
      } else {
        this.seenDouble = true;
      }
    }

    if (other.seenSigned) {
      if (this.seenUnsigned) {
        this.seenSigned = true;
        this.setError("both 'signed' and 'unsigned' in declaration specifiers");
      } else if (this.seenSigned) {
        this.setError("duplicate 'signed'");
      } else {
        this.seenSigned = true;
      }
    }

    if (other.seenUnsigned) {
      if (this.seenSigned) {
        this.seenUnsigned = true;
        this.setError("both 'signed' and 'unsigned' in declaration specifiers");
      } else if (this.seenUnsigned) {
        this.setError("duplicate 'unsigned'");
      } else {
        this.seenUnsigned = true;
      }
    }

    if (other.seenBool) {
      if (this.hasType()) {
        /* System.err.println("8"); */
        this.multipleTypes();
      } else {
        this.seenBool = true;
      }
    }

    if (null != other.storage) {
      if (null == this.storage) {
        this.storage = other.storage;
      } else if (this.storage.equals(other.storage)) {
        this.setError("duplicate storage class");
      } else {
        this.setError("multiple storage classes in declaration specifiers");
      }
    }

    return this;
  }

  /**
   * Annotate the specified base type.  This method annotates the
   * specified type with all attributes besides the storage class,
   * thread-local specifier, and function specifier attributes.
   *
   * @param base The base type.
   * @return The annnotated base type.
   */
  public Type annotateBase(Type base) {
    return (null != attributes)? base.attribute(attributes) : base;
  }

  /**
   * Get the resulting type.
   */
  public Type getType() {
    Type type;
    if (seenBool) {
      type = BooleanT.TYPE;
    } else if (seenChar) {
      if (seenUnsigned) {
        type = NumberT.U_CHAR;
      } else if (seenSigned) {
        type = NumberT.S_CHAR;
      } else {
        type = NumberT.CHAR;
      }
    } else if (seenShort) {
      if (seenUnsigned) {
        type = NumberT.U_SHORT;
      } else {
        type = NumberT.SHORT;
      }
    } else if (seenFloat) {
      if (seenComplex) {
        type = NumberT.FLOAT_COMPLEX;
      } else {
        type = NumberT.FLOAT;
      }
    } else if (seenDouble) {
      if (0 < longCount) {
        if (seenComplex) {
          type = NumberT.LONG_DOUBLE_COMPLEX;
        } else {
          type = NumberT.LONG_DOUBLE;
        }
      } else {
        if (seenComplex) {
          type = NumberT.DOUBLE_COMPLEX;
        } else {
          type = NumberT.DOUBLE;
        }
      }
    } else if (1 == longCount) {
      if (seenUnsigned) {
        type = NumberT.U_LONG;
      } else {
        type = NumberT.LONG;
      }
    } else if (1 < longCount) {
      if (seenUnsigned) {
        type = NumberT.U_LONG_LONG;
      } else {
        type = NumberT.LONG_LONG;
      }
    } else if (seenUnsigned) {
      type = NumberT.U_INT;
    } else if (seenSigned) {
      type = NumberT.S_INT;
    } else if (seenInt) {
      type = NumberT.INT;
    } else {
      type = C.IMPLICIT;
    }

    // Annotate the type.
    if ((! type.hasError()) && (null != attributes)) {
      type = type.annotate().attribute(attributes);
    }

    return type;
  }

  /** Test for previous type. */
  protected boolean hasType() {
    return
      (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
       seenFloat || seenDouble || seenComplex ||
       (null != type));
  }

  /** Report error indicating multiple types. */
  protected void multipleTypes() {
    this.setError("multiple data types in declaration specifiers");
  }

  /** Add the specified attribute. */
  protected void add(Attribute att) {
    if (null == attributes) {
      attributes = new ArrayList<Attribute>();
      attributes.add(att);
    } else if (! attributes.contains(att)) {
      attributes.add(att);
    }
  }

  public void setError(String msg) {
    this.error = true;
    this.error_message = msg;
    type = ErrorT.TYPE;
    if (showErrors) {  // showErrors is true
      System.err.println("error in specifiers: " + msg);
    }
  }

  // Get specs.  Gets list of specifiers, checking for type errors.
  // Also need to hoist conditionals around complete type
  // specifiers.  Is it possible to make a hoisting tree-walker?
  // Walk tree, when encountering conditional, fork the spec state
  // and walk both.  No need for merge, since there are two
  // different declarations.
}

/**
 * A helper function to get the specifiers of the value of a component
 * node from the stack.
 *
 * @param subparser The reference to the subparser.
 * @param number The component number.
 * @return The specifiers for the component.
 */
private static Specifiers getSpecsAt(Subparser subparser, int component) {
  Node n = getNodeAt(subparser, component);

  if (n.hasProperty(SPECS)) {
    return (Specifiers) n.getProperty(SPECS);
  } else {
    Specifiers specs = new Specifiers();

    n.setProperty(SPECS, specs);
    return specs;
  }
}

private static void updateSpecs(Subparser subparser,
                                Specifiers new_specs,
                                Object value) {
  updateSpecs(subparser, null, new_specs, value);
}

private static void updateSpecs(Subparser subparser,
                                Specifiers specs,
                                Specifiers new_specs,
                                Object value) {
  if (null == specs) {
    specs = new_specs;
  } else {
    specs = specs.addSpecs(new_specs);
  }

  ((P4Context) subparser.scope).lastSeenType = specs.getType();
  ((Node) value).setProperty(SPECS, specs);
}

private static Specifiers makeUnionSpec(Subparser subparser,
                                        Node tagNode,
                                        Node membersNode,
                                        Node attrsNode) {
  Specifiers specs = new Specifiers();

  return specs;
}

private static Specifiers makeStructSpec(Subparser subparser,
                                         Node tagNode,
                                         Node membersNode,
                                         Node attrsNode) {
  String tag;
  String name;
  if (null == tagNode) {
    // TODO struct tag creation
    /* tag = table.freshName("tag"); */
    tag = "tag(untagged)";
    name = tag;
  } else {
    // TODO check for conditional here
    /* tag = ((Syntax) tagNode.get(0)).toLanguage().getTokenText(); */
    /* name = SymbolTable.toTagName(tag); */
  }

  // TODO remove this once above code is complete
  tag = "tag(untagged)";
  name = tag;

  Type type;

  // TODO struct tag is defined
  /* if (table.current().isDefinedLocally(name)) { */
  /*   final Type t = (Type)table.current().lookupLocally(name); */

  /*   if (! t.isStruct()) { */
  /*     runtime.error("'" + tag + "' defined as wrong kind of tag", n); */
  /*     reportPreviousTag(t); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else if (null != t.toTagged().getMembers()) { */
  /*     runtime.error("redefinition of 'struct " + tag + "'", n); */
  /*     reportPreviousTag(t); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else if (t.hasAttribute(Constants.ATT_DEFINED)) { */
  /*     runtime.error("nested redefinition of 'struct " + tag + "'", n); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else { */
  /*     type = t; */
  /*   } */
  /* } else { */
    // TODO checkNotParameter
    /* checkNotParameter(n, "struct"); */
 
    // Declare the struct so that members can reference it.
    type = new StructT(tag);
    /* table.current().define(name, type); */
  /* } */

  // TODO location
  /* // Update the location. */
  /* type.setLocation(n); */

  // TODO struct attributes
  /* // Update the GCC attributes. */
  /* for (Attribute a : toAttributeList(n.getGeneric(0))) { */
  /*   type.addAttribute(a); */
  /* } */
  /* for (Attribute a : toAttributeList(n.getGeneric(3))) { */
  /*   type.addAttribute(a); */
  /* } */

  // Process the members and update the struct declaration.  Use
  // defined attribute to protect against nested redefinition.
  type.addAttribute(Constants.ATT_DEFINED);
  // TODO struct members
  /* List<VariableT> members = processMembers(n.getGeneric(2), true); */
  List<VariableT> members = null;
  type.toStruct().setMembers(members);
  type.removeAttribute(Constants.ATT_DEFINED);

  Specifiers specs = new Specifiers();
  specs.type = type;

  return specs;
}

/**
 * Check that the tag declaration is not located within a
 * parameter list.  If the declaration is located within a
 * parameter list, this method prints the appropriate warning.
 *
 * @param node The node.
 * @param kind The kind of tag.
 */
private void checkNotParameter(Node node, String kind) {
  // TODO checkNotParameter implementation
  /* if (TMP_SCOPE.equals(table.current().getName())) { */
  /*   final String tag = node.getString(1); */
  /*   final String msg; */
  /*   if (null == tag) { */
  /*     msg = "anonymous " + kind + " declared inside parameter list"; */
  /*   } else { */
  /*     msg = "'" + kind + " " + tag + "' declared inside parameter list"; */
  /*   } */

  /*   runtime.warning(msg, node); */
  /* } */
}

// ---------- Declarators

/* private static String DECL = "superc.p4parser.Declarator"; */

/* private static String NAME = "superc.p4parser.Name"; */

/* private static void setDecl(Object n, Type type) { */
/*   ((Node) n).setProperty(DECL, type); */
/* } */

/* private static Type getDecl(Object n) { */
/*   return ((Type) ((Node) n).getProperty(DECL)); */
/* } */

/* private static void setName(Object n, String name) { */
/*   ((Node) n).setProperty(NAME, name); */
/* } */

/* private static String getName(Object n) { */
/*   return ((String) ((Node) n).getProperty(NAME)); */
/* } */

/* private static void setDecl(Object n, Type type, String name) { */
/*   setDecl(n, type); */
/*   setName(n, name); */
/* } */

/* private static void copyDecl(Subparser subparser, Object value, int from) { */
/*   setDecl(value, (Type) (getNodeAt(subparser, from).getProperty(DECL))); */
/* } */

/* private static void copyName(Subparser subparser, Object value, int from) { */
/*   setName(value, (String) (getNodeAt(subparser, from).getProperty(NAME))); */
/* } */

/* private static void copyDeclName(Subparser subparser, Object value, int from){ */
/*   copyDecl(subparser, value, from); */
/*   copyName(subparser, value, from); */
/* } */
