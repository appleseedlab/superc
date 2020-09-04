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
 * @version $Revision: 1.12 $
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
%token __INT128

//preprocessor number catch-all token
%token PPNUM

//backslash for assembly
%token BACKSLASH

//%token DOTSTAR
//%token DCOLON

%{
import xtc.Constants;
import xtc.Limits;

import superc.cparser.CContext.SymbolTable.STField;

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
          IdentifierDeclarator { bindFunDef(subparser, null, getNodeAt(subparser, 1)); }
        | DeclarationSpecifier     IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } 
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } 
        | TypeQualifierList        IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } 

        |                          OldFunctionDeclarator { bindFunDef(subparser, null, getNodeAt(subparser, 1)); }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

FunctionOldPrototype:  /** complete **/
          OldFunctionDeclarator { bindFunDef(subparser, null, getNodeAt(subparser, 1)); }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

/* Nested function's declarator can't just be an IdentifierDeclarator
   or it gets a conflict.  gcc seems to behave this way too since it
   yields a parsing error. */
NestedFunctionDefinition:  /** complete **/ // added scoping
         NestedFunctionPrototype { ReenterScope(subparser); } LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        | NestedFunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        ;

NestedFunctionPrototype:  /** complete **/
          DeclarationSpecifier     IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }

        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

NestedFunctionOldPrototype:  /** complete **/
        DeclarationSpecifier       OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
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
        DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | DefaultDeclaringList COMMA AttributeSpecifierListOpt IdentifierDeclarator
        {
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        ;

DeclaringList:  /** complete **/
        DeclarationSpecifier Declarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | TypeSpecifier Declarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator
        {
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
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
        StorageClass {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeQualifierList StorageClass {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | DeclarationQualifierList DeclarationQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

TypeQualifierList:  /** list, complete **/
        TypeQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeQualifierList TypeQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

DeclarationQualifier:  /** passthrough **/
        TypeQualifier                  /* const or volatile */
        | StorageClass
        ;

TypeQualifier:    // const, volatile, and restrict can have underscores
        ConstQualifier
        {
          getSpecsAt(subparser, 1).add(Constants.ATT_CONSTANT);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VolatileQualifier
        {
          getSpecsAt(subparser, 1).add(Constants.ATT_VOLATILE);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | RestrictQualifier
        {
          getSpecsAt(subparser, 1).add(Constants.ATT_RESTRICT);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | AttributeSpecifier // ADDED
        {
          /* TODO AttributeSpecifier */
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | FunctionSpecifier  // ADDED
        {
          getSpecsAt(subparser, 1).add(Constants.ATT_INLINE);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
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

BasicDeclarationSpecifier: /** passthrough, complete **/      /*StorageClass+Arithmetic or void*/
        BasicTypeSpecifier  StorageClass {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | DeclarationQualifierList BasicTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier DeclarationQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier BasicTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

BasicTypeSpecifier: /** passthrough, complete **/
        BasicTypeName {           /* Arithmetic or void */
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeQualifierList BasicTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier TypeQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier BasicTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
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
        VarArgTypeSpecifier StorageClass {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | DeclarationQualifierList VarArgTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgDeclarationSpecifier DeclarationQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgDeclarationSpecifier VarArgTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

VarArgTypeSpecifier:
        VarArgTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeQualifierList VarArgTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgTypeSpecifier TypeQualifier {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgTypeSpecifier VarArgTypeName {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

VarArgTypeName:  // ADDED
        __BUILTIN_VA_LIST { getSpecsAt(subparser, 1).type = InternalT.VA_LIST; }
        ;

StorageClass:  /** passthrough **/
        TYPEDEF     { getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF; }
        | EXTERN    { getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN; }
        | STATIC    { getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC; }
        | AUTO      { getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO; }
        | REGISTER  { getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_REGISTER; }
        ;

BasicTypeName:  /** passthrough **/
        VOID              { getSpecsAt(subparser, 1).type = VoidT.TYPE; }
        | CHAR            { getSpecsAt(subparser, 1).seenChar = true; }
        | SHORT           { getSpecsAt(subparser, 1).seenShort = true; }
        | INT             { getSpecsAt(subparser, 1).seenInt = true; }
        | __INT128        { getSpecsAt(subparser, 1).seenInt = true; }
        | LONG            { getSpecsAt(subparser, 1).longCount++; }
        | FLOAT           { getSpecsAt(subparser, 1).seenFloat = true; }
        | DOUBLE          { getSpecsAt(subparser, 1).seenDouble = true; }
        | SignedKeyword   { getSpecsAt(subparser, 1).seenSigned = true; }
        | UNSIGNED        { getSpecsAt(subparser, 1).seenUnsigned = true; }
        | _BOOL           { getSpecsAt(subparser, 1).seenBool = true; }  // ADDED
        | ComplexKeyword  { getSpecsAt(subparser, 1).seenComplex = true; }  // ADDED
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
        StructSpecifier
        | UnionSpecifier
        | EnumSpecifier
        ;

StructSpecifier: /** complete **/  // ADDED attributes
        STRUCT { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          Node tag     = null;
          Node members = getNodeAt(subparser, 3);
          Node attrs   = null;
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
        }
        | STRUCT IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          Node tag     = getNodeAt(subparser, 6);
          Node members = getNodeAt(subparser, 3);
          Node attrs   = null;
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
        }
        | STRUCT IdentifierOrTypedefName
        | STRUCT AttributeSpecifierList { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          Node tag     = null;
          Node members = getNodeAt(subparser, 3);
          Node attrs   = getNodeAt(subparser, 6);
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
        }
        | STRUCT AttributeSpecifierList IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          Node tag     = getNodeAt(subparser, 6);
          Node members = getNodeAt(subparser, 3);
          Node attrs   = getNodeAt(subparser, 7);
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
        }
        | STRUCT AttributeSpecifierList IdentifierOrTypedefName
        ;

UnionSpecifier: /** complete **/  // ADDED attributes
        UNION { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        | UNION IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        | UNION IdentifierOrTypedefName
        | UNION AttributeSpecifierList { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        | UNION AttributeSpecifierList IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        /* { */
        /*    updateSpecs(subparser,
                          makeStruct()); */
        /* } */
        | UNION AttributeSpecifierList IdentifierOrTypedefName
        ;

StructDeclarationList: /** list, complete **/
        /* StructDeclaration */ /* ADDED gcc empty struct */
        {
          ((Node) value).setProperty(SPECS, new Specifiers());
        }
        | StructDeclarationList StructDeclarationExtension {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

StructDeclarationExtension:  /** passthrough, complete **/  // ADDED
        StructDeclaration
        | __EXTENSION__ StructDeclaration
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

/* ParameterDeclaration:  /\** complete **\/ */
/*         DeclarationSpecifier */
/*         | DeclarationSpecifier AbstractDeclarator */
/*         | DeclarationSpecifier IdentifierDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         | DeclarationSpecifier ParameterTypedefDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         | DeclarationQualifierList  */
/*         | DeclarationQualifierList AbstractDeclarator */
/*         | DeclarationQualifierList IdentifierDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         | TypeSpecifier */
/*         | TypeSpecifier AbstractDeclarator */
/*         | TypeSpecifier IdentifierDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         | TypeSpecifier ParameterTypedefDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         | TypeQualifierList  */
/*         | TypeQualifierList AbstractDeclarator */
/*         | TypeQualifierList IdentifierDeclarator */
/*         { */
/*           saveBaseType(subparser, getNodeAt(subparser, 2)); */
/*           bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1)); */
/*         } AttributeSpecifierListOpt */
/*         ; */

ParameterDeclaration:  /** passthrough, complete **/
        ParameterIdentifierDeclaration
        | ParameterAbstractDeclaration
        ;

ParameterAbstractDeclaration:
        DeclarationSpecifier
        | DeclarationSpecifier AbstractDeclarator
        | DeclarationQualifierList 
        | DeclarationQualifierList AbstractDeclarator
        | TypeSpecifier
        | TypeSpecifier AbstractDeclarator
        | TypeQualifierList 
        | TypeQualifierList AbstractDeclarator
        ;

ParameterIdentifierDeclaration:
        DeclarationSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        | DeclarationSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        | TypeSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        | TypeSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
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
        | ASSIGN Initializer  // n1570.pdf section 6.7.9
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

DesignatedInitializer:/** complete, passthrough **/ /* ADDED */
        Initializer
        | Designation Initializer
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
        {
          /* setDecl(value, new PointerT(getDecl(getNodeAt(subparser, 1)))); */
          /* copyName(subparser, value, 1); */
        }
        | STAR TypeQualifierList IdentifierDeclarator
        {
          /* Specifiers spec = getSpecsAt(subparser, 2); */
          /* Type baseType = getDecl(getNodeAt(subparser, 1));; */
          /* Type result = spec.annotateBase(new PointerT(baseType).annotate()); */
          /* setDecl(value, result); */
          /* copyName(subparser, value, 1); */
        }
        ;
        
PostfixIdentifierDeclarator: /** passthrough, complete **/
        FunctionDeclarator
        | ArrayDeclarator
        | AttributedDeclarator
        | LPAREN UnaryIdentifierDeclarator RPAREN PostfixingAbstractDeclarator
        ;

AttributedDeclarator: /** complete **/
        LPAREN UnaryIdentifierDeclarator RPAREN
        {
          /* copyDeclName(subparser, value, 2); */
        }
        ;

FunctionDeclarator:  /** complete **/
        ParenIdentifierDeclarator PostfixingFunctionDeclarator
        ;

PostfixingFunctionDeclarator:  /** complete **/
        LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN
        ;

ArrayDeclarator:  /** complete **/
        ParenIdentifierDeclarator ArrayAbstractDeclarator
        ;

ParenIdentifierDeclarator:  /** passthrough, complete **/
        SimpleDeclarator { /* copyDeclName(subparser, value, 1); */ }
        | LPAREN ParenIdentifierDeclarator RPAREN { /* copyDeclName(subparser, value, 2); */ }
        ;

SimpleDeclarator: /** complete **/
        IDENTIFIER  /* bind */
        {
          /* setDecl(value, lastSeenType(subparser)); */
          /* setName(value, getStringAt(subparser, 1)); */
        }
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
        /* | LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN */
        | PostfixingFunctionDeclarator
        ;

ParameterTypeListOpt: /** complete **/
        /* empty */
        | ParameterTypeList
        ;

ArrayAbstractDeclarator: /** complete **/
        LBRACK RBRACK
        {
          /* setDecl(value, new ArrayT(getDecl(getNodeAt(subparser, 1)))); */
          /* copyName(subparser, value, 1); */
        }
        | LBRACK ConstantExpression RBRACK
        {
          /* setDecl(value, new ArrayT(getDecl())); */
          /* copyName(subparser, value, 1); */
        }
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
        // n1570 6.8.5 Iteration statements allows for a declaration in the initializer of a for loop
        | FOR LPAREN Declaration ExpressionOpt SEMICOLON
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
        IDENTIFIER { useIdent(subparser, getNodeAt(subparser, 1)); }  /* We cannot use a typedef name as a variable */
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
          PostfixExpression LPAREN RPAREN { callFunction(subparser, getNodeAt(subparser, 3), null); }
        | PostfixExpression LPAREN ExpressionList RPAREN  { callFunction(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 2)); }
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
private CContext.SymbolTable functionTable;

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
  this.functionTable = new CContext.SymbolTable();
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
public CContext.SymbolTable getFunctionTable() {
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
  ((CContext) subparser.scope).lastSeenType =
    ((Specifiers) typespec.getProperty(SPECS)).getType();
}

/**
 * Return the last seen type.
 */
public Type lastSeenType(Subparser subparser) {
  return ((CContext) subparser.scope).lastSeenType;
}

private static class Binding {
  public Language ident;
  public Type type;

  public Binding(Language ident, Type type) {
    this.ident = ident;
    this.type = type;
  }
}

private boolean findToken(Object n, CTag tag) {
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
  boolean static_function;

  if (getident(declarator).equals("ERR_PTR")) {
    System.err.println(typespec);
    System.err.println(declarator);
  }

  if (null == typespec) {
    // only static with static keyword
    static_function = false;
  } else if (typespec.getName().equals("DeclarationSpecifier") ||
             typespec.getName().equals("DeclarationQualifierList")) {
    // the declaration keyword can only appear in these kinds of
    // specifiers
    if (typespec.getProperty(SPECS) != null) {
      static_function = ((Specifiers) typespec.getProperty(SPECS)).storage ==
        Constants.ATT_STORAGE_STATIC;
    } else {
      // traverse subtree looking for static until checkers are finished
      static_function = findToken(typespec, CTag.STATIC);
    }
  } else {
    // the declaration keyword can only appear in these kinds of
    // specifiers
    if (typespec.getProperty(SPECS) != null) {
      static_function = ((Specifiers) typespec.getProperty(SPECS)).storage ==
        Constants.ATT_STORAGE_STATIC;
    } else {
      // traverse subtree looking for static until checkers are finished
      static_function = findToken(typespec, CTag.STATIC);
    }
  }

  if (static_function) {
    bindIdent(subparser, typespec, declarator, STField.STATIC_FUNDEF);
  } else {
    bindIdent(subparser, typespec, declarator, STField.GLOBAL_FUNDEF);
  }
}

public void bindIdent(Subparser subparser, Node typespec, Node declarator) {
  bindIdent(subparser, typespec, declarator, null);
}

/** typespec might be null for declarations and definitions without a
 * type spec; alsoSet is used to set another symbol table bit and
 * might be null.
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, STField alsoSet) {
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  CContext scope = (CContext) subparser.scope;

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
  }

  if (showErrors) {
    System.err.println("bind: " + ident.getTokenText() + " " + typedef);
  }
  if (debug) {
    System.err.println("def: " + ident.getTokenText() + " " + alsoSet);
  }
  STField field = typedef ? STField.TYPEDEF : STField.IDENT;
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
  CContext scope = (CContext) subparser.scope;

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
  CContext scope = (CContext) subparser.scope;

  // Get the identifier in the declarator.  The identifier must
  // occur after an IdentifierOrTypedefName token.
  Object b = stack.get(1).value;
  String ident = getident(b).getTokenText();

  // Bind variable name.
  scope.getSymbolTable().setbool(ident, STField.IDENT, true, presenceCondition);
  /* scope.bind(ident, false, presenceCondition); */
}

public void useIdent(Subparser subparser, Node ident) {
  CContext scope = (CContext) subparser.scope;
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
    /* CContext scope = (CContext) subparser.scope; */
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
  CContext scope = (CContext) subparser.scope;

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

private static String SPECS = "superc.cparser.Specifiers";

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

  ((CContext) subparser.scope).lastSeenType = specs.getType();
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

/* private static String DECL = "superc.cparser.Declarator"; */

/* private static String NAME = "superc.cparser.Name"; */

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
