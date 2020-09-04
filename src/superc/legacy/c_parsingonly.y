 /* Copyright (C) 1989,1990 James A. Roskind, All rights reserved.
     This grammar was developed  and  written  by  James  A.  Roskind.
     Copying  of  this  grammar  description, as a whole, is permitted
     providing this notice is intact and applicable  in  all  complete
     copies.   Translations as a whole to other parser generator input
     languages  (or  grammar  description  languages)   is   permitted
     provided  that  this  notice is intact and applicable in all such
     copies,  along  with  a  disclaimer  that  the  contents  are   a
     translation.   The reproduction of derived text, such as modified
     versions of this grammar, or the output of parser generators,  is
     permitted,  provided  the  resulting  work includes the copyright
     notice "Portions Copyright (c)  1989,  1990  James  A.  Roskind".
     Derived products, such as compilers, translators, browsers, etc.,
     that  use  this  grammar,  must also provide the notice "Portions
     Copyright  (c)  1989,  1990  James  A.  Roskind"  in   a   manner
     appropriate  to  the  utility,  and in keeping with copyright law
     (e.g.: EITHER displayed when first invoked/executed; OR displayed
     continuously on display terminal; OR via placement in the  object
     code  in  form  readable in a printout, with or near the title of
     the work, or at the end of the file).  No royalties, licenses  or
     commissions  of  any  kind are required to copy this grammar, its
     translations, or derivative products, when the copies are made in
     compliance with this notice. Persons or corporations that do make
     copies in compliance with this notice may charge  whatever  price
     is  agreeable  to  a  buyer, for such copies or derivative works.
     THIS GRAMMAR IS PROVIDED ``AS IS'' AND  WITHOUT  ANY  EXPRESS  OR
     IMPLIED  WARRANTIES,  INCLUDING,  WITHOUT LIMITATION, THE IMPLIED
     WARRANTIES  OF  MERCHANTABILITY  AND  FITNESS  FOR  A  PARTICULAR
     PURPOSE.
 
     James A. Roskind
     Independent Consultant
     516 Latania Palm Drive
     Indialantic FL, 32903
     (407)729-4348
     jar@ileaf.com

     Modifications for GCC Extensions Copyright (C) 2009-2012 New York
     University
 */

/**
 * Definition of C's complete syntactic unit syntax.
 *
 * @version $Revision: 1.1 $
 */

%expect 1

/* keywords */
%token AUTO            DOUBLE          INT             STRUCT
%token BREAK  /** layout **/
%token ELSE            LONG            SWITCH
%token CASE            ENUM            REGISTER        TYPEDEF
%token CHAR            EXTERN
%token RETURN  /** layout **/
%token UNION
%token CONST           FLOAT           SHORT           UNSIGNED
%token CONTINUE  /** layout **/
%token FOR             SIGNED          VOID
%token DEFAULT
%token GOTO  /** layout **/
%token SIZEOF          VOLATILE
%token DO              IF              STATIC          WHILE

/* ANSI Grammar suggestions */
%token IDENTIFIER              STRINGliteral
%token FLOATINGconstant        INTEGERconstant        CHARACTERconstant
%token OCTALconstant           HEXconstant

/* New Lexical element, whereas ANSI suggested non-terminal */

%token TYPEDEFname /* Lexer will tell the difference between this and 
    an  Identifier!   An  Identifier  that is CURRENTLY in scope as a 
    typedef name is provided to the parser as a TYPEDEFname.*/

/* Multi-Character operators */
%token  ARROW  /** layout **/            /*    ->                              */
%token  ICR DECR         /*    ++      --                      */
%token  LS RS            /*    <<      >>                      */
%token  LE GE EQ NE      /*    <=      >=      ==      !=      */
%token  ANDAND OROR      /*    &&      ||                      */
%token  ELLIPSIS         /*    ...                             */

/* modifying assignment operators */
%token MULTassign  DIVassign    MODassign   /*   *=      /=      %=      */
%token PLUSassign  MINUSassign              /*   +=      -=              */
%token LSassign    RSassign                 /*   <<=     >>=             */
%token ANDassign   ERassign     ORassign    /*   &=      ^=      |=      */

/* punctuation */
%token LPAREN  /** layout **/
%token RPAREN  /** layout **/
%token COMMA  /** layout **/
%token HASH
%token DHASH
%token LBRACE  /** layout **/
%token RBRACE  /** layout **/
%token LBRACK  /** layout **/
%token RBRACK  /** layout **/
%token DOT  /** layout **/
%token AND
%token STAR
%token PLUS
%token MINUS
%token NEGATE
%token NOT
%token DIV
%token MOD
%token LT
%token GT
%token XOR
%token PIPE
%token QUESTION  /** layout **/
%token COLON  /** layout **/
%token SEMICOLON  /** layout **/
%token ASSIGN  /** layout **/

//tokens for gcc extensions
%token ASMSYM
%token _BOOL
%token _COMPLEX
%token RESTRICT
%token __ALIGNOF
%token __ALIGNOF__
%token ASM
%token __ASM
%token __ASM__
%token AT
%token USD
%token __ATTRIBUTE
%token __ATTRIBUTE__
%token __BUILTIN_OFFSETOF
%token __BUILTIN_TYPES_COMPATIBLE_P
%token __BUILTIN_VA_ARG
%token __BUILTIN_VA_LIST
%token __COMPLEX__
%token __CONST
%token __CONST__
%token __EXTENSION__
%token INLINE
%token __INLINE
%token __INLINE__
%token __LABEL__
%token __RESTRICT
%token __RESTRICT__
%token __SIGNED
%token __SIGNED__
%token __THREAD
%token TYPEOF
%token __TYPEOF
%token __TYPEOF__
%token __VOLATILE
%token __VOLATILE__

//preprocessor number catch-all token
%token PPNUM

//backslash for assembly
%token BACKSLASH

//%token DOTSTAR
//%token DCOLON

%{
import xtc.tree.Node;
import xtc.tree.Location;
import xtc.util.Pair;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.lang.cpp.ForkMergeParser.StackFrame;
%}

%%

TranslationUnit:  /** complete, passthrough **/
        ExternalDeclarationList
        ;

// ------------------------------------------------------ External definitions

ExternalDeclarationList: /** list, complete **/
        /* empty */  // ADDED gcc allows empty program
        | ExternalDeclarationList ExternalDeclaration
        ;

ExternalDeclaration:  /** passthrough, complete **/
        FunctionDefinitionExtension
        | DeclarationExtension
        | AssemblyDefinition
        | EmptyDefinition
        ;

EmptyDefinition:  /** complete **/
        SEMICOLON
        ;

FunctionDefinitionExtension:  /** passthrough, complete **/  // ADDED
        FunctionDefinition
        | __EXTENSION__ FunctionDefinition
        ;

FunctionDefinition:  /** complete **/ // added scoping
         FunctionPrototype { ReenterScope(subparser); } LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        | FunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        ;

/* Functions have their own compound statement because of the need for
   reentering scope. */
FunctionCompoundStatement:  /** complete, name(CompoundStatement) **/
        LocalLabelDeclarationListOpt DeclarationOrStatementList
        ;

/* Having a function prototype node in the AST allows this to be a
   complete AST.  So if something in the prototype is configurable,
   the conditional will only be hoisted around the prototype, not the
   entire function definition. */
FunctionPrototype:  /** complete **/
                                     IdentifierDeclarator { BindVar(subparser); }
        | DeclarationSpecifier      IdentifierDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             IdentifierDeclarator { BindIdentifier(subparser); } 
        | DeclarationQualifierList IdentifierDeclarator { BindIdentifier(subparser); } 
        | TypeQualifierList        IdentifierDeclarator { BindIdentifier(subparser); } 

        |                            OldFunctionDeclarator { BindVar(subparser); }
        | DeclarationSpecifier      OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             OldFunctionDeclarator { BindIdentifier(subparser); }
        | DeclarationQualifierList OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeQualifierList        OldFunctionDeclarator { BindIdentifier(subparser); }
        ;

FunctionOldPrototype:  /** complete **/
                                     OldFunctionDeclarator { BindVar(subparser); }
        | DeclarationSpecifier      OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             OldFunctionDeclarator { BindIdentifier(subparser); }
        | DeclarationQualifierList OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeQualifierList        OldFunctionDeclarator { BindIdentifier(subparser); }
        ;

/* Nested function's declarator can't just be an IdentifierDeclarator
   or it gets a conflict.  gcc seems to behave this way too since it
   yields a parsing error. */
NestedFunctionDefinition:  /** complete **/ // added scoping
         NestedFunctionPrototype { ReenterScope(subparser); } LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        | NestedFunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        ;

NestedFunctionPrototype:  /** complete **/
          DeclarationSpecifier      IdentifierDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             IdentifierDeclarator { BindIdentifier(subparser); } 
        | DeclarationQualifierList IdentifierDeclarator { BindIdentifier(subparser); } 
        | TypeQualifierList        IdentifierDeclarator { BindIdentifier(subparser); } 

        | DeclarationSpecifier      OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             OldFunctionDeclarator { BindIdentifier(subparser); }
        | DeclarationQualifierList OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeQualifierList        OldFunctionDeclarator { BindIdentifier(subparser); }
        ;

NestedFunctionOldPrototype:  /** complete **/
          DeclarationSpecifier      OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeSpecifier             OldFunctionDeclarator { BindIdentifier(subparser); }
        | DeclarationQualifierList OldFunctionDeclarator { BindIdentifier(subparser); }
        | TypeQualifierList        OldFunctionDeclarator { BindIdentifier(subparser); }
        ;

// -------------------------------------------------------------- Declarations

    /* The following is different from the ANSI C specified  grammar.  
    The  changes  were  made  to  disambiguate  typedef's presence in 
    DeclarationSpecifiers (vs.  in the Declarator for redefinition); 
    to allow struct/union/enum tag declarations without  Declarators, 
    and  to  better  reflect the parsing of declarations (Declarators 
    must be combined with DeclarationSpecifiers ASAP  so  that  they 
    are visible in scope).

    Example  of  typedef  use  as either a DeclarationSpecifier or a 
    Declarator:

      typedef int T;
      struct S { T T;}; /* redefinition of T as member name * /

    Example of legal and illegal Statements detected by this grammar:

      int; /* syntax error: vacuous declaration * /
      struct S;  /* no error: tag is defined or elaborated * /

    Example of result of proper declaration binding:
        
        int a=sizeof(a); /* note that "a" is declared with a type  in 
            the name space BEFORE parsing the Initializer * /

        int b, c[sizeof(b)]; /* Note that the first Declarator "b" is 
             declared  with  a  type  BEFORE the second Declarator is 
             parsed * /

    */

DeclarationExtension:  /** passthrough, complete **/  // ADDED
        Declaration
        | __EXTENSION__ Declaration
        ;

Declaration:  /** complete **/
        SUEDeclarationSpecifier { KillReentrantScope(subparser); } SEMICOLON
        | SUETypeSpecifier { KillReentrantScope(subparser); } SEMICOLON
        | DeclaringList { KillReentrantScope(subparser); } SEMICOLON
        | DefaultDeclaringList { KillReentrantScope(subparser); } SEMICOLON
        ;

/* Note that if a typedef were  redeclared,  then  a  declaration 
   specifier must be supplied */

DefaultDeclaringList:  /** complete **/  /* Can't  redeclare typedef names */
        DeclarationQualifierList IdentifierDeclarator { BindIdentifier(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | TypeQualifierList IdentifierDeclarator { BindIdentifier(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | DefaultDeclaringList COMMA AttributeSpecifierListOpt IdentifierDeclarator { BindIdentifierInList(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        ;

DeclaringList:  /** complete **/
        DeclarationSpecifier Declarator { BindIdentifier(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | TypeSpecifier Declarator { BindIdentifier(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator { BindIdentifierInList(subparser); } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        ;

DeclarationSpecifier:  /** passthrough, complete **/
        BasicDeclarationSpecifier        /* Arithmetic or void */
        | SUEDeclarationSpecifier          /* struct/union/enum */
        | TypedefDeclarationSpecifier      /* typedef*/
        | VarArgDeclarationSpecifier  // ADDED
        | TypeofDeclarationSpecifier // ADDED
        ;

TypeSpecifier:  /** passthrough, complete **/
        BasicTypeSpecifier                 /* Arithmetic or void */
        | SUETypeSpecifier                 /* Struct/Union/Enum */
        | TypedefTypeSpecifier             /* Typedef */
        | VarArgTypeSpecifier  // ADDED
        | TypeofTypeSpecifier // ADDED
        ;

DeclarationQualifierList:  /** list, complete **/  /* const/volatile, AND storage class */
        StorageClass
        | TypeQualifierList StorageClass
        | DeclarationQualifierList DeclarationQualifier
        ;

TypeQualifierList:  /** list, complete **/
        TypeQualifier
        | TypeQualifierList TypeQualifier
        ;

DeclarationQualifier:  
        TypeQualifier                  /* const or volatile */
        | StorageClass
        ;

TypeQualifier:    // const, volatile, and restrict can have underscores
        ConstQualifier
        | VolatileQualifier
        | RestrictQualifier
        | AttributeSpecifier // ADDED
        | FunctionSpecifier  // ADDED
        ;

ConstQualifier:    // ADDED
        CONST
        | __CONST
        | __CONST__
        ;

VolatileQualifier:   // ADDED
        VOLATILE
        | __VOLATILE
        | __VOLATILE__
        ;

RestrictQualifier:   // ADDED
        RESTRICT
        | __RESTRICT
        | __RESTRICT__
        ;

FunctionSpecifier:  // ADDED
        INLINE
        | __INLINE
        | __INLINE__
        ;

BasicDeclarationSpecifier: /** complete **/      /*StorageClass+Arithmetic or void*/
        BasicTypeSpecifier  StorageClass
        | DeclarationQualifierList BasicTypeName
        | BasicDeclarationSpecifier DeclarationQualifier
        | BasicDeclarationSpecifier BasicTypeName
        ;

BasicTypeSpecifier: /** passthrough, complete **/
        BasicTypeName            /* Arithmetic or void */
        | TypeQualifierList BasicTypeName
        | BasicTypeSpecifier TypeQualifier
        | BasicTypeSpecifier BasicTypeName
        ;

SUEDeclarationSpecifier: /** complete **/          /* StorageClass + struct/union/enum */
        SUETypeSpecifier StorageClass
        | DeclarationQualifierList ElaboratedTypeName
        | SUEDeclarationSpecifier DeclarationQualifier
        ;

SUETypeSpecifier: /** complete **/
        ElaboratedTypeName              /* struct/union/enum */
        | TypeQualifierList ElaboratedTypeName
        | SUETypeSpecifier TypeQualifier
        ;


TypedefDeclarationSpecifier: /** complete **/       /*Storage Class + typedef types */
        TypedefTypeSpecifier StorageClass
        | DeclarationQualifierList TYPEDEFname
        | TypedefDeclarationSpecifier DeclarationQualifier
        ;

TypedefTypeSpecifier: /** complete **/              /* typedef types */
        TYPEDEFname
        | TypeQualifierList TYPEDEFname
        | TypedefTypeSpecifier TypeQualifier
        ;

TypeofDeclarationSpecifier: /** complete **/      /*StorageClass+Arithmetic or void*/
        TypeofTypeSpecifier  StorageClass
        | DeclarationQualifierList Typeofspecifier
        | TypeofDeclarationSpecifier DeclarationQualifier
        | TypeofDeclarationSpecifier Typeofspecifier
        ;

TypeofTypeSpecifier: /** complete **/  // ADDED
        Typeofspecifier
        | TypeQualifierList Typeofspecifier
        | TypeofTypeSpecifier TypeQualifier
        | TypeofTypeSpecifier Typeofspecifier
        ;

Typeofspecifier: /** complete **/  // ADDED
        Typeofkeyword LPAREN TypeName RPAREN
        | Typeofkeyword LPAREN Expression RPAREN
        ;

Typeofkeyword: /** complete **/  // ADDED
        TYPEOF
        | __TYPEOF
        | __TYPEOF__
        ;

VarArgDeclarationSpecifier:      /*StorageClass+Arithmetic or void*/
        VarArgTypeSpecifier  StorageClass
        | DeclarationQualifierList VarArgTypeName
        | VarArgDeclarationSpecifier DeclarationQualifier
        | VarArgDeclarationSpecifier VarArgTypeName
        ;

VarArgTypeSpecifier:
        VarArgTypeName            /* Arithmetic or void */
        | TypeQualifierList VarArgTypeName
        | VarArgTypeSpecifier TypeQualifier
        | VarArgTypeSpecifier VarArgTypeName
        ;

VarArgTypeName:  // ADDED
        __BUILTIN_VA_LIST
        ;

StorageClass:  /** passthrough **/
        TYPEDEF
        | EXTERN
        | STATIC
        | AUTO
        | REGISTER
        ;

BasicTypeName:  /** passthrough **/
        VOID
        | CHAR
        | SHORT
        | INT
        | LONG
        | FLOAT
        | DOUBLE
        | SignedKeyword
        | UNSIGNED
        | _BOOL  // ADDED
        | ComplexKeyword  // ADDED
        ;

SignedKeyword:
        SIGNED
        | __SIGNED
        | __SIGNED__
        ;

ComplexKeyword:
        _COMPLEX
        | __COMPLEX__
        ;

ElaboratedTypeName: /** passthrough, complete **/
        StructOrUnionSpecifier
        | EnumSpecifier
        ;

StructOrUnionSpecifier: /** complete **/  // ADDED attributes
        StructOrUnion { EnterScope(subparser); } LBRACE StructDeclarationList { ExitScope(subparser); } RBRACE
        | StructOrUnion IdentifierOrTypedefName
                { EnterScope(subparser); } LBRACE StructDeclarationList { ExitScope(subparser); } RBRACE
        | StructOrUnion IdentifierOrTypedefName
        | StructOrUnion AttributeSpecifierList { EnterScope(subparser); } LBRACE StructDeclarationList { ExitScope(subparser); } RBRACE
        | StructOrUnion AttributeSpecifierList IdentifierOrTypedefName
                { EnterScope(subparser); } LBRACE StructDeclarationList { ExitScope(subparser); } RBRACE
        | StructOrUnion AttributeSpecifierList IdentifierOrTypedefName
        ;

StructOrUnion:
        STRUCT
        | UNION
        ;

StructDeclarationList: /** list, complete **/
        /* StructDeclaration */ /* ADDED gcc empty struct */
        | StructDeclarationList StructDeclaration
        ;

StructDeclaration: /** complete **/
        StructDeclaringList SEMICOLON
        | StructDefaultDeclaringList SEMICOLON
        | TypeQualifierList SEMICOLON  // ADDED Declarator is optional
        | TypeSpecifier SEMICOLON  // ADDED Declarator is optional
        | SEMICOLON // ADDED gcc allows empty struct field in declaration
        ;

StructDefaultDeclaringList: /** list, complete **/        /* doesn't redeclare typedef*/
        TypeQualifierList StructIdentifierDeclarator AttributeSpecifierListOpt
        | StructDefaultDeclaringList COMMA StructIdentifierDeclarator AttributeSpecifierListOpt
        ;

StructDeclaringList: /** list, complete **/        
        TypeSpecifier StructDeclarator AttributeSpecifierListOpt
        | StructDeclaringList COMMA StructDeclarator AttributeSpecifierListOpt
        ;


StructDeclarator: /** complete **/
        Declarator BitFieldSizeOpt
        | BitFieldSize
        ;

StructIdentifierDeclarator: /** complete **/
        IdentifierDeclarator BitFieldSizeOpt
        | BitFieldSize
        ;

BitFieldSizeOpt: /** complete **/
        /* nothing */
        | BitFieldSize
        ;

BitFieldSize: /** complete **/
        COLON ConstantExpression
        ;

EnumSpecifier: /** complete **/  /* ADDED attributes */
        ENUM LBRACE EnumeratorList RBRACE
        | ENUM IdentifierOrTypedefName LBRACE EnumeratorList RBRACE
        | ENUM IdentifierOrTypedefName
        | ENUM LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */ 
        | ENUM IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        | ENUM AttributeSpecifierList LBRACE EnumeratorList RBRACE
        | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList RBRACE
        | ENUM AttributeSpecifierList IdentifierOrTypedefName
        | ENUM AttributeSpecifierList LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */ 
        | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        ;

/*EnumeratorList:
        IdentifierOrTypedefName EnumeratorValueOpt
        | EnumeratorList COMMA IdentifierOrTypedefName EnumeratorValueOpt
        ;*/

EnumeratorList:  /** list, complete **/  // easier to bind
        Enumerator
        | EnumeratorList COMMA Enumerator
        ;

Enumerator: /** complete **/
        IDENTIFIER { BindEnum(subparser); } EnumeratorValueOpt
        | TYPEDEFname { BindEnum(subparser); } EnumeratorValueOpt
        ;

EnumeratorValueOpt: /** complete **/
        /* Nothing */
        | ASSIGN ConstantExpression
        ;

ParameterTypeList:  /** complete **/
        ParameterList
        | ParameterList COMMA ELLIPSIS
        ;

ParameterList:  /** list, complete **/
        ParameterDeclaration
        | ParameterList COMMA ParameterDeclaration
        ;

ParameterDeclaration:  /** complete **/
        DeclarationSpecifier
        | DeclarationSpecifier AbstractDeclarator
        | DeclarationSpecifier IdentifierDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        | DeclarationSpecifier ParameterTypedefDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        | DeclarationQualifierList 
        | DeclarationQualifierList AbstractDeclarator
        | DeclarationQualifierList IdentifierDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        | TypeSpecifier
        | TypeSpecifier AbstractDeclarator
        | TypeSpecifier IdentifierDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        | TypeSpecifier ParameterTypedefDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        | TypeQualifierList 
        | TypeQualifierList AbstractDeclarator
        | TypeQualifierList IdentifierDeclarator { BindIdentifier(subparser); } AttributeSpecifierListOpt
        ;

    /*  ANSI  C  section  3.7.1  states  "An Identifier declared as a 
    typedef name shall not be redeclared as a Parameter".  Hence  the 
    following is based only on IDENTIFIERs */

IdentifierList:  /** list, complete **/
        Identifier
        | IdentifierList COMMA Identifier
        ;

Identifier:  /** complete **/
       IDENTIFIER { BindVar(subparser); }
       ;

IdentifierOrTypedefName: /** complete **/
        IDENTIFIER
        | TYPEDEFname
        ;

TypeName: /** complete **/
        TypeSpecifier
        | TypeSpecifier AbstractDeclarator
        | TypeQualifierList 
        | TypeQualifierList AbstractDeclarator
        ;

InitializerOpt: /** complete **/
        /* nothing */
        | ASSIGN DesignatedInitializer
        ;

DesignatedInitializer:/** complete, passthrough **/ /* ADDED */
        Initializer
        | Designation Initializer
        ;

/*InitializerStandard:  // ADDED gcc can have empty Initializer lists
        LBRACE InitializerList RBRACE
        | AssignmentExpression
        ;*/

Initializer: /** complete **/  // ADDED gcc can have empty Initializer lists
        LBRACE MatchedInitializerList RBRACE
        | LBRACE MatchedInitializerList DesignatedInitializer RBRACE
        | AssignmentExpression
        ;

InitializerList:  /** complete **/ //modified so that COMMAS are on the right
        MatchedInitializerList
        | MatchedInitializerList DesignatedInitializer
        ;

MatchedInitializerList:  /** list, complete **/
        | MatchedInitializerList DesignatedInitializer COMMA
        ;

Designation:   /* ADDED */
        DesignatorList ASSIGN
        | ObsoleteArrayDesignation
        | ObsoleteFieldDesignation
        ;

DesignatorList:  /** list, complete **/  /* ADDED */
        Designator
        | DesignatorList Designator
        ;

Designator:   /* ADDED */
        LBRACK ConstantExpression RBRACK
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        | DOT IDENTIFIER //IDENTIFIER
        | DOT TYPEDEFname // ADDED hack to get around using typedef names as struct fields
        ;

ObsoleteArrayDesignation: /** complete **/  /* ADDED */
        LBRACK ConstantExpression RBRACK
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        ;

ObsoleteFieldDesignation: /** complete **/  /* ADDED */
        IDENTIFIER COLON
        ;

Declarator:  /** complete, passthrough **/
        TypedefDeclarator
        | IdentifierDeclarator
        ;

TypedefDeclarator:  /** passthrough, complete **/  // ADDED
        TypedefDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
        ;

TypedefDeclaratorMain:  /** passthrough, complete **/
        ParenTypedefDeclarator  /* would be ambiguous as Parameter*/
        | ParameterTypedefDeclarator   /* not ambiguous as param*/
        ;

ParameterTypedefDeclarator: /** complete **/
        TYPEDEFname 
        | TYPEDEFname PostfixingAbstractDeclarator
        | CleanTypedefDeclarator
        ;

    /*  The  following have at least one STAR. There is no (redundant) 
    LPAREN between the STAR and the TYPEDEFname. */

CleanTypedefDeclarator: /** complete **/
        CleanPostfixTypedefDeclarator
        | STAR ParameterTypedefDeclarator
        | STAR TypeQualifierList ParameterTypedefDeclarator  
        ;

CleanPostfixTypedefDeclarator: /** complete **/
        LPAREN CleanTypedefDeclarator RPAREN
        | LPAREN CleanTypedefDeclarator RPAREN PostfixingAbstractDeclarator
        ;

    /* The following have a redundant LPAREN placed immediately  to  the 
    left of the TYPEDEFname */

ParenTypedefDeclarator:  /** passthrough, complete **/
        ParenPostfixTypedefDeclarator
        | STAR LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
        | STAR TypeQualifierList  
                LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
        | STAR ParenTypedefDeclarator
        | STAR TypeQualifierList ParenTypedefDeclarator
        ;
        
ParenPostfixTypedefDeclarator: /** complete **/ /* redundant paren to left of tname*/
        LPAREN ParenTypedefDeclarator RPAREN
        | LPAREN SimpleParenTypedefDeclarator PostfixingAbstractDeclarator RPAREN /* redundant paren */
        | LPAREN ParenTypedefDeclarator RPAREN PostfixingAbstractDeclarator
        ;

SimpleParenTypedefDeclarator: /** complete **/
        TYPEDEFname
        | LPAREN SimpleParenTypedefDeclarator RPAREN
        ;

IdentifierDeclarator:  /** passthrough, complete **/
        IdentifierDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
        ;

IdentifierDeclaratorMain:  /** passthrough, complete **/
        UnaryIdentifierDeclarator
        | ParenIdentifierDeclarator
        ;

UnaryIdentifierDeclarator: /** passthrough, complete **/
        PostfixIdentifierDeclarator
        | STAR IdentifierDeclarator
        | STAR TypeQualifierList IdentifierDeclarator
        ;
        
PostfixIdentifierDeclarator: /** passthrough, complete **/
        FunctionDeclarator
        | ArrayDeclarator
        | AttributedDeclarator
        | LPAREN UnaryIdentifierDeclarator RPAREN PostfixingAbstractDeclarator
        ;

AttributedDeclarator: /** complete **/
        LPAREN UnaryIdentifierDeclarator RPAREN
        ;

FunctionDeclarator:  /** complete **/
        ParenIdentifierDeclarator PostfixingFunctionDeclarator
        ;

PostfixingFunctionDeclarator:  /** passthrough, complete **/
        LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN
        ;

ArrayDeclarator:  /** complete **/
        ParenIdentifierDeclarator ArrayAbstractDeclarator
        ;

ParenIdentifierDeclarator:  /** passthrough, complete **/
        SimpleDeclarator
        | LPAREN ParenIdentifierDeclarator RPAREN
        ;

SimpleDeclarator: /** complete **/
        IDENTIFIER  /* bind */
        ;

OldFunctionDeclarator: /** complete **/
        PostfixOldFunctionDeclarator
        | STAR OldFunctionDeclarator
        | STAR TypeQualifierList OldFunctionDeclarator
        ;

PostfixOldFunctionDeclarator: /** complete **/
        ParenIdentifierDeclarator LPAREN { EnterScope(subparser); } IdentifierList { ExitReentrantScope(subparser); } RPAREN
        | LPAREN OldFunctionDeclarator RPAREN
        | LPAREN OldFunctionDeclarator RPAREN PostfixingAbstractDeclarator
        ;

AbstractDeclarator: /** complete **/
        UnaryAbstractDeclarator
        | PostfixAbstractDeclarator
        | PostfixingAbstractDeclarator
        ;

PostfixingAbstractDeclarator: /** passthrough, complete **/
        ArrayAbstractDeclarator
        | LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN
        ;

ParameterTypeListOpt: /** complete **/
        /* empty */
        | ParameterTypeList
        ;

ArrayAbstractDeclarator: /** complete **/
        LBRACK RBRACK
        | LBRACK ConstantExpression RBRACK
        | ArrayAbstractDeclarator LBRACK ConstantExpression RBRACK
        ;

UnaryAbstractDeclarator: /** complete **/
        STAR 
        | STAR TypeQualifierList 
        | STAR AbstractDeclarator
        | STAR TypeQualifierList AbstractDeclarator
        ;

PostfixAbstractDeclarator: /** complete **/
        LPAREN UnaryAbstractDeclarator RPAREN
        | LPAREN PostfixAbstractDeclarator RPAREN
        | LPAREN PostfixingAbstractDeclarator RPAREN
        | LPAREN UnaryAbstractDeclarator RPAREN PostfixingAbstractDeclarator
        ;

// ---------------------------------------------------------------- Statements

Statement:  /** passthrough, complete **/
        LabeledStatement
        | CompoundStatement
        | ExpressionStatement
        | SelectionStatement
        | IterationStatement
        | JumpStatement
        | AssemblyStatement  // ADDED
        ;

LabeledStatement:  /** complete **/  // ADDED attributes
        IdentifierOrTypedefName COLON AttributeSpecifierListOpt Statement
        | CASE ConstantExpression COLON Statement
        | CASE ConstantExpression ELLIPSIS ConstantExpression COLON Statement  // ADDED case range
        | DEFAULT COLON Statement
        ;

/*CompoundStatement:
        LBRACE RBRACE
        | LBRACE DeclarationList RBRACE
        | LBRACE StatementList RBRACE
        | LBRACE DeclarationList StatementList RBRACE
        ;*/

CompoundStatement:  /** complete **/  /* ADDED */
        LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList RBRACE
        ;

LocalLabelDeclarationListOpt: /** complete **/
        /* empty */
        | LocalLabelDeclarationList
        ;

LocalLabelDeclarationList:  /** list, complete **/
        LocalLabelDeclaration
        | LocalLabelDeclarationList LocalLabelDeclaration
        ;

LocalLabelDeclaration: /** complete **/  /* ADDED */
        __LABEL__ LocalLabelList SEMICOLON
        ;

LocalLabelList:  /** list, complete **/  // ADDED
        IDENTIFIER
        | LocalLabelList COMMA IDENTIFIER
        ;

DeclarationOrStatementList:  /** list, complete **/  /* ADDED */
        | DeclarationOrStatementList DeclarationOrStatement
        ;

DeclarationOrStatement: /** passthrough, complete **/  /* ADDED */
        DeclarationExtension
        | Statement
        | NestedFunctionDefinition
        ;

DeclarationList:  /** list, complete **/
        DeclarationExtension
        | DeclarationList DeclarationExtension
        ;

/*StatementList:
        Statement
        | StatementList Statement
        ;*/

ExpressionStatement:  /** complete **/
        ExpressionOpt SEMICOLON
        ;

SelectionStatement:  /** complete **/
        IF LPAREN Expression RPAREN Statement
        | IF LPAREN Expression RPAREN Statement ELSE Statement
        | SWITCH LPAREN Expression RPAREN Statement
        ;

IterationStatement:  /** complete **/
        WHILE LPAREN Expression RPAREN Statement
        | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON
        | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        ;

JumpStatement:  /** passthrough, complete **/
        GotoStatement
        | ContinueStatement
        | BreakStatement
        | ReturnStatement
        ;

GotoStatement:  /** complete **/
        GOTO IdentifierOrTypedefName SEMICOLON
        | GOTO STAR Expression SEMICOLON  // ADDED
        ;

ContinueStatement:  /** complete **/
        CONTINUE SEMICOLON
        ;

BreakStatement:  /** complete **/
        BREAK SEMICOLON
        ;

ReturnStatement:  /** complete **/
        RETURN ExpressionOpt SEMICOLON
        ;

// --------------------------------------------------------------- Expressions

/* CONSTANTS */
Constant: /** passthrough, complete **/
        FLOATINGconstant
        | INTEGERconstant
        /* We are not including ENUMERATIONConstant here  because  we 
        are  treating  it like a variable with a type of "enumeration 
        Constant".  */
        | OCTALconstant
        | HEXconstant
        | CHARACTERconstant
        ;

/* STRING LITERALS */
StringLiteralList:  /** list, complete **/
                STRINGliteral
                | StringLiteralList STRINGliteral
                ;


/* EXPRESSIONS */
PrimaryExpression:  /** complete, passthrough **/
        PrimaryIdentifier
        | Constant
        | StringLiteralList
        | LPAREN Expression RPAREN
        | StatementAsExpression  // ADDED
        | VariableArgumentAccess  // ADDED
        ;

PrimaryIdentifier: /** complete **/
        IDENTIFIER  /* We cannot use a typedef name as a variable */
        ;

VariableArgumentAccess:  /** complete **/  // ADDED
        __BUILTIN_VA_ARG LPAREN AssignmentExpression COMMA TypeName RPAREN
        ;

StatementAsExpression:  /** complete **/  //ADDED
        LPAREN { EnterScope(subparser); } CompoundStatement { ExitScope(subparser); } RPAREN
        ;

PostfixExpression:  /** passthrough, complete **/
        PrimaryExpression
        | Subscript
        | FunctionCall
        | DirectSelection
        | IndirectSelection
        | Increment
        | Decrement
        | CompoundLiteral  /* ADDED */
        ;

Subscript:  /** complete **/
        PostfixExpression LBRACK Expression RBRACK
        ;

FunctionCall:  /** complete **/
        PostfixExpression LPAREN RPAREN
        | PostfixExpression LPAREN ExpressionList RPAREN
        ;

DirectSelection:  /** complete **/
        PostfixExpression DOT IdentifierOrTypedefName
        ;

IndirectSelection:  /** complete **/
        PostfixExpression ARROW IdentifierOrTypedefName
        ;

Increment:  /** complete **/
        PostfixExpression ICR
        ;

Decrement:  /** complete **/
        PostfixExpression DECR
        ;





CompoundLiteral:  /** complete **/  /* ADDED */
        LPAREN TypeName RPAREN LBRACE InitializerList RBRACE
        ;

ExpressionList:  /** list, complete **/
        AssignmentExpression
        | ExpressionList COMMA AssignmentExpression
        ;

UnaryExpression:  /** passthrough, complete **/
        PostfixExpression
        | ICR UnaryExpression
        | DECR UnaryExpression
        | Unaryoperator CastExpression
        | SIZEOF UnaryExpression
        | SIZEOF LPAREN TypeName RPAREN
        | LabelAddressExpression  // ADDED
        | AlignofExpression // ADDED
        | ExtensionExpression // ADDED
        | OffsetofExpression // ADDED
        | TypeCompatibilityExpression  // ADEED
        ;

TypeCompatibilityExpression:  /** complete **/
        __BUILTIN_TYPES_COMPATIBLE_P LPAREN TypeName COMMA TypeName RPAREN
        ;

OffsetofExpression:  /** complete **/
        __BUILTIN_OFFSETOF LPAREN TypeName COMMA PostfixExpression RPAREN
        ;

ExtensionExpression:  /** complete **/
        __EXTENSION__ CastExpression
        ;

AlignofExpression:  /** complete **/
        Alignofkeyword LPAREN TypeName RPAREN
        | Alignofkeyword UnaryExpression
        ;

Alignofkeyword: 
        __ALIGNOF__
        | __ALIGNOF
        ;

LabelAddressExpression:  /** complete  **/  // ADDED
        ANDAND IDENTIFIER;
        ;

Unaryoperator: 
        AND
        | STAR
        | PLUS
        | MINUS
        | NEGATE
        | NOT
        ;

CastExpression:  /** passthrough, complete **/
        UnaryExpression
        | LPAREN TypeName RPAREN CastExpression
        ;

MultiplicativeExpression:  /** passthrough, complete **/
        CastExpression
        | MultiplicativeExpression STAR CastExpression
        | MultiplicativeExpression DIV CastExpression
        | MultiplicativeExpression MOD CastExpression
        ;

AdditiveExpression:  /** passthrough, complete **/
        MultiplicativeExpression
        | AdditiveExpression PLUS MultiplicativeExpression
        | AdditiveExpression MINUS MultiplicativeExpression
        ;

ShiftExpression:  /** passthrough, complete **/
        AdditiveExpression
        | ShiftExpression LS AdditiveExpression
        | ShiftExpression RS AdditiveExpression
        ;

RelationalExpression:  /** passthrough, complete **/
        ShiftExpression
        | RelationalExpression LT ShiftExpression
        | RelationalExpression GT ShiftExpression
        | RelationalExpression LE ShiftExpression
        | RelationalExpression GE ShiftExpression
        ;

EqualityExpression:  /** passthrough, complete **/
        RelationalExpression
        | EqualityExpression EQ RelationalExpression
        | EqualityExpression NE RelationalExpression
        ;

AndExpression:  /** passthrough, complete **/
        EqualityExpression
        | AndExpression AND EqualityExpression
        ;

ExclusiveOrExpression:  /** passthrough, complete **/
        AndExpression
        | ExclusiveOrExpression XOR AndExpression
        ;

InclusiveOrExpression:  /** passthrough, complete **/
        ExclusiveOrExpression
        | InclusiveOrExpression PIPE ExclusiveOrExpression
        ;

LogicalAndExpression:  /** passthrough, complete **/
        InclusiveOrExpression
        | LogicalAndExpression ANDAND InclusiveOrExpression
        ;

LogicalORExpression:  /** passthrough, complete **/
        LogicalAndExpression
        | LogicalORExpression OROR LogicalAndExpression
        ;

ConditionalExpression:  /** passthrough, complete **/
        LogicalORExpression
        | LogicalORExpression QUESTION Expression COLON
                ConditionalExpression
        | LogicalORExpression QUESTION COLON  // ADDED gcc incomplete conditional
                ConditionalExpression
        ;

AssignmentExpression:  /** passthrough, complete **/
        ConditionalExpression
        | UnaryExpression AssignmentOperator AssignmentExpression
        ;

AssignmentOperator: /** complete **/
        ASSIGN
        | MULTassign
        | DIVassign
        | MODassign
        | PLUSassign
        | MINUSassign
        | LSassign
        | RSassign
        | ANDassign
        | ERassign
        | ORassign
        ;

ExpressionOpt:  /** passthrough, complete **/
        /* Nothing */
        | Expression
        ;

Expression:  /** passthrough, complete **/
        AssignmentExpression
        | Expression COMMA AssignmentExpression
        ;

ConstantExpression: /** passthrough, complete **/
        ConditionalExpression
        ;

AttributeSpecifierListOpt: /** complete **/  // ADDED
        /* empty */
        | AttributeSpecifierList
        ;

AttributeSpecifierList:  /** list, complete **/  // ADDED
        AttributeSpecifier
        | AttributeSpecifierList AttributeSpecifier
        ;

AttributeSpecifier: /** complete **/  // ADDED
        AttributeKeyword LPAREN LPAREN AttributeListOpt RPAREN RPAREN
        ;

AttributeKeyword:   // ADDED
        __ATTRIBUTE
        | __ATTRIBUTE__
        ;

AttributeListOpt:   // ADDED
        /* empty */
        | AttributeList
        ;

AttributeList:  /** list, complete **/  // ADDED
        Word AttributeExpressionOpt
        | AttributeList COMMA Word AttributeExpressionOpt
        ;

AttributeExpressionOpt:   // ADDED
        /* empty */
        | LPAREN RPAREN
        | LPAREN ExpressionList RPAREN
        ;

Word:  // ADDED
        IDENTIFIER
        | AUTO
        | DOUBLE
        | INT
        | STRUCT
        | BREAK
        | ELSE
        | LONG
        | SWITCH
        | CASE
        | ENUM
        | REGISTER
        | TYPEDEF
        | CHAR
        | EXTERN
        | RETURN
        | UNION
        | CONST
        | FLOAT
        | SHORT
        | UNSIGNED
        | CONTINUE
        | FOR
        | SIGNED
        | VOID
        | DEFAULT
        | GOTO
        | SIZEOF
        | VOLATILE
        | DO
        | IF
        | STATIC
        | WHILE
        | ASMSYM
        | _BOOL
        | _COMPLEX
        | RESTRICT
        | __ALIGNOF
        | __ALIGNOF__
        | ASM
        | __ASM
        | __ASM__
        | __ATTRIBUTE
        | __ATTRIBUTE__
        | __BUILTIN_OFFSETOF
        | __BUILTIN_TYPES_COMPATIBLE_P
        | __BUILTIN_VA_ARG
        | __BUILTIN_VA_LIST
        | __COMPLEX__
        | __CONST
        | __CONST__
        | __EXTENSION__
        | INLINE
        | __INLINE
        | __INLINE__
        | __LABEL__
        | __RESTRICT
        | __RESTRICT__
        | __SIGNED
        | __SIGNED__
        | __THREAD
        | TYPEOF
        | __TYPEOF
        | __TYPEOF__
        | __VOLATILE
        | __VOLATILE__
        ;

// ------------------------------------------------------------------ Assembly

AssemblyDefinition:  /** complete **/
        AssemblyExpression SEMICOLON
        ;

AssemblyExpression:  /** complete **/
        AsmKeyword LPAREN StringLiteralList RPAREN
        ;

AssemblyExpressionOpt:  /** complete **/
        /* empty */
        | AssemblyExpression
        ;

AssemblyStatement:   /** complete **/ // ADDED 
        AsmKeyword LPAREN Assemblyargument RPAREN SEMICOLON
        /* gcc>=4.5 */
        | AsmKeyword GOTO LPAREN AssemblyGotoargument RPAREN SEMICOLON
        | AsmKeyword TypeQualifier LPAREN Assemblyargument RPAREN SEMICOLON
        ;

Assemblyargument:  /** complete **/  // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON Assemblyclobbers
        | StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt
        | StringLiteralList COLON AssemblyoperandsOpt
        | StringLiteralList
        ;

AssemblyoperandsOpt:  /** complete **/  // ADDED
        /* empty */
        | Assemblyoperands
        ;

Assemblyoperands:  /** list, complete **/  // ADDED
        Assemblyoperand
        | Assemblyoperands COMMA Assemblyoperand
        ;

Assemblyoperand:  /** complete **/  // ADDED
                             StringLiteralList LPAREN Expression RPAREN
        | LBRACK Word RBRACK StringLiteralList LPAREN Expression RPAREN
        ;

AssemblyclobbersOpt:  /** complete **/ // ADDED
        /* empty */
        | Assemblyclobbers
        ;

Assemblyclobbers:  /** complete **/  // ADDED
        StringLiteralList
        | Assemblyclobbers COMMA StringLiteralList
        ;

AssemblyGotoargument:  /** complete **/ // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON AssemblyclobbersOpt COLON AssemblyJumpLabels
        ;

AssemblyJumpLabels:  /** complete **/ // ADDED
        Identifier
        | AssemblyJumpLabels COMMA Identifier
        ;

AsmKeyword:   // ADDED
        ASM
        | __ASM
        | __ASM__
        ;

%%

  /** True when statistics should be output. */
  private boolean languageStatistics;

  /**
   * Turn language statistics collection on.  Default is off.
   *
   * @param b True is on.
   */
  public void collectStatistics(boolean b) {
    languageStatistics = b;
  }

  // public void action(int production, Subparser subparser) {
  //   // preserve old behavior, ignoring new inline semantic action
  // }

  public void BindIdentifier(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CContext scope = (CContext) subparser.scope;
    boolean typedef;
    Language ident;
      
    // Get the AST nodes that contain the type specifier and the
    // declarator.
    Object a = stack.get(2).value;
    Object b = stack.get(1).value;

    // Check whether the declaration is a typedef.  This assumes that
    // the typedef keyword is the first token of the declaration.
    Language t;
    while (true) {
      if (a instanceof Node && ! (a instanceof Syntax)) {
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
    t = (Language) a;

    // Get the identifier in the declarator.
    ident = getident(b);

    if (CTag.TYPEDEF == t.tag()) {
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
      
    scope.bind(ident.getTokenText(), typedef, presenceCondition);
  }
    
  public void BindIdentifierInList(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CContext scope = (CContext) subparser.scope;
      
    boolean typedef;
    Language ident;
      
    // Get the AST nodes that contain the type specifier and the
    // declarator.
    Object a = stack.get(4).value;
    Object b = stack.get(1).value;
      
    // Check whether the declaration is a typedef.  This assumes that
    // the typedef keyword is the first token of the declaration.
    Language t;
    while (true) {
      if (a instanceof Node && ! (a instanceof Syntax)) {
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
    t = (Language) a;

    // Get the identifier in the declarator.
    ident = getident(b);

    if (CTag.TYPEDEF == t.tag()) {
      // Bind a typedef name.
      typedef = true;

      if (languageStatistics) {
        if (typedef) {
          Location location = subparser.lookahead.token.syntax.getLocation();
          System.err.println(String.format("typedef %s %s", ident, location));
        }
      }
    } else {
      // Bind a variable name.
      typedef = false;
    }
      
    scope.bind(ident.getTokenText(), typedef, presenceCondition);
  }
    
  public void BindVar(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CContext scope = (CContext) subparser.scope;
      
    // Get the identifier in the declarator.
    Object b = stack.get(1).value;
    Language<?> ident = getident(b);

    // Bind variable name.
    scope.bind(ident.getTokenText(), false, presenceCondition);
  }
    
  public void BindEnum(Subparser subparser) {
    StackFrame stack  = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CContext scope = (CContext) subparser.scope;
      
    // Get the identifier in the declarator.  The identifier must
    // occur after an IdentifierOrTypedefName token.
    Object b = stack.get(1).value;
    String ident = getident(b).getTokenText();

    // Bind variable name.
    scope.bind(ident, false, presenceCondition);
  }
    
  public void EnterScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope = ((CContext) subparser.scope).enterScope(presenceCondition);
  }
    
  public void ExitScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope = ((CContext) subparser.scope).exitScope(presenceCondition);
  }

  public void ExitReentrantScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CContext) subparser.scope).exitReentrantScope(presenceCondition);
  }
    
  public void ReenterScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CContext) subparser.scope).reenterScope(presenceCondition);
  }
    
  public void KillReentrantScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CContext) subparser.scope).killReentrantScope(presenceCondition);
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
        
      if (CTag.IDENTIFIER == token.tag()
          || CTag.TYPEDEFname == token.tag()) {
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
