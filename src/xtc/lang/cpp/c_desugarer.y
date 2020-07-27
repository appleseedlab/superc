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

/* top-level annotations */
/** prevent_merge_on_actions **/

/* keywords */
%token AUTO            DOUBLE          INT             STRUCT
%token BREAK
%token ELSE            LONG            SWITCH
%token CASE            ENUM            REGISTER        TYPEDEF
%token CHAR            EXTERN
%token RETURN  
%token UNION
%token CONST           FLOAT           SHORT           UNSIGNED
%token CONTINUE
%token FOR             SIGNED          VOID
%token DEFAULT
%token GOTO
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
%token  ARROW            /*    ->                              */
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
%token LPAREN
%token RPAREN
%token COMMA
%token HASH
%token DHASH
%token LBRACE
%token RBRACE
%token LBRACK
%token RBRACK
%token DOT
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
%token QUESTION
%token COLON
%token SEMICOLON
%token ASSIGN

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

import xtc.lang.cpp.SymbolTable.STField;

import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Visitor;

import xtc.util.Pair;
import java.util.Random;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;
import xtc.lang.cpp.Syntax.Error;

import xtc.lang.cpp.Multiverse;

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

/* import xtc.util.SymbolTable; */
/* import xtc.util.SymbolTable.Scope; */
import xtc.util.SingletonIterator;
import xtc.util.Utilities;

import xtc.lang.cpp.Multiverse.Element;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.lang.cpp.SymbolTable.Entry;

import xtc.lang.cpp.ForkMergeParser.StackFrame;

import java.lang.StringBuilder;

import java.util.ArrayList;
import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.HashMap;

import java.io.File;
import java.io.Reader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.StringReader;
import java.io.OutputStreamWriter;
import java.io.IOException;

import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.StructT;
import xtc.type.VariableT;
import xtc.type.UnitT;
/* TUTORIAL: add any additional type classes here */

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
        {
          try {
            OutputStreamWriter writer = new OutputStreamWriter(System.out);
            setCPC(value, PCtoString(subparser.getPresenceCondition()));
            /** writes transformation code */
            writer.write("#include <stdbool.h>\n");
            //writer.write("#include \"desugared_macros.h\" /* configuration macros converted to C variables */\n");

            /** writes the extern declarations for the renamed preprocessor BDDs */
            StringBuilder temp = new StringBuilder();
            for (String originalExpr : boolVarRenamings.keySet()) {
              temp.append(originalExpr);
              writer.write("extern bool " + boolVarRenamings.get(originalExpr) + "; " + "/* renamed from " + temp.toString() + " */" + "\n");
              writer.write("extern bool " + boolVarRenamings.get(originalExpr) + "_DEFINED;" + "\n");

              temp.setLength(0);
            }

            // TODO: handle functions properly and remove this main function placeholder
            System.err.println("TODO: generated main() is a placeholder.");
            writer.write("\nint main(void) {\n");

            /** writes all file-dependent transformation code that isn't
             *  a renamed config macro declaration
             */
            Multiverse<StringBuilder> sbmv = getSBMVAt(subparser, 1);
            for (Element<StringBuilder> elemSB : sbmv) {
              /** Writes generated code that exists in all presence conditions,
               *  without hoisting "if (1)", because variables declared here need
               *  to be accessible from all other presence conditions
               */
              if (elemSB.getCondition().getBDD().isOne())
              {
                writer.write(elemSB.getData().toString());
              }
              else {
                writer.write("\nif (" + elemSB.getCondition() + ") {");
                writer.write("\n" + elemSB.getData().toString() + "\n}\n");
              }
            }

            // TODO: handle functions properly and remove this main function placeholder
            System.err.println("TODO: generated curly braces are a placeholder.");
            writer.write("\n}\n");

            writer.flush();
          }
          catch(Exception IOException) {
            System.err.println("ERROR: unable to write output");
            System.exit(1);
          }
        }
        ;

// ------------------------------------------------------ External definitions

ExternalDeclarationList: /** list, complete **/
        /* empty */  // ADDED gcc allows empty program
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> result = new Multiverse<StringBuilder>();
          result.add(new StringBuilder(""), subparser.getPresenceCondition());
          setTFValue(value, result);
        }
        | ExternalDeclarationList ExternalDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child1 = getNodeAt(subparser, 2);
          Node child2 = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child2, child1);
          setTFValue(value, product);
        }
        ;

ExternalDeclaration:  /** passthrough, complete **/
        FunctionDefinitionExtension
        {
          // TODO: do these actions need setCPC?
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | AssemblyDefinition
        {
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | EmptyDefinition
        {
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

EmptyDefinition:  /** complete **/
        SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

FunctionDefinitionExtension:  /** passthrough, complete **/  // ADDED
        FunctionDefinition
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | __EXTENSION__ FunctionDefinition
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

FunctionDefinition:  /** complete **/ // added scoping
        FunctionPrototype { ReenterScope(subparser); } LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        {
          //Get FunctionPrototype
          //Get FunctionCompoundStatement
          System.err.println("WARNING: skipping over transformation code at some nodes in FunctionDefinition.");
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 3); // TODO: add other children once supported
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | FunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          // TODO
          System.err.println("WARNING: unsupported semantic action: FunctionDefinition");
          System.exit(1);
        }
        ;

/* Functions have their own compound statement because of the need for
   reentering scope. */
FunctionCompoundStatement:  /** nomerge, name(CompoundStatement) **/
        LocalLabelDeclarationListOpt DeclarationOrStatementList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

/* Having a function prototype node in the AST allows this to be a
   complete AST.  So if something in the prototype is configurable,
   the conditional will only be hoisted around the prototype, not the
   entire function definition. */
FunctionPrototype:  /** nomerge **/
        IdentifierDeclarator
        {
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | DeclarationSpecifier     IdentifierDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          StringBuilder sb = new StringBuilder();

          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
           if (type.size() == 1)
             sb.append(type.get(0).getData().toType() + " ");
          else {
	          System.err.println("ERROR: Configurable typedefs not yet supported.");
		        // System.exit(1);
  	      }
          // TODO
          /*sb.append(getStringBuilderAt(subparser, 1));
          //System.err.println("main function signature is " + sb.toString());
      	  setStringBuilder(value, sb);
          */
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        |                          OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

FunctionOldPrototype:  /** nomerge **/
        OldFunctionDeclarator
        {
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

/* Nested function's declarator can't just be an IdentifierDeclarator
   or it gets a conflict.  gcc seems to behave this way too since it
   yields a parsing error. */
NestedFunctionDefinition:  /** complete **/ // added scoping
        NestedFunctionPrototype { ReenterScope(subparser); } LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 7), getNodeAt(subparser, 4), getNodeAt(subparser, 3));
          setTFValue(value, product);
        }
        | NestedFunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 8), getNodeAt(subparser, 6), getNodeAt(subparser, 4), getNodeAt(subparser, 3));
          setTFValue(value, product);
        }
        ;

NestedFunctionPrototype:  /** nomerge **/
          DeclarationSpecifier     IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }

        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

NestedFunctionOldPrototype:  /** nomerge **/
        DeclarationSpecifier       OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
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
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | __EXTENSION__ Declaration
        {
          System.err.println("ERROR: unsupported construct: Declaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

Declaration:  /** complete **/
        SUEDeclarationSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 3);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | SUETypeSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
        	// gets the type, the declarations, and any initializers
        	TypeAndDeclInitList TBDBList = getTBDBListAt(subparser, 3);
        	TypeBuilderMultiverse type = TBDBList.type;
        	List<TypeAndDeclInitList.DeclAndInit> declAndInits = TBDBList.declAndInitList;


        	// all declarations get generated, with no if(PC) {} wrapped around them,
          // so we can append every declaration to a single stringbuilder
        	StringBuilder sb = new StringBuilder();

          // generates declarations and statements with the retrieved information
        	for (TypeAndDeclInitList.DeclAndInit declAndInit : declAndInits) {
        		DeclBuilder decl = declAndInit.decl;
	          String oldIdent = decl.identifier;
	          System.err.println(decl.toString() + " " + type.toString());

            // if the declaration has an initializer under at least one presence condition,
            // then we iterate through every initializer, add a new instance to the symtab,
            // then write the declaration of that new variable with its initializer.
            if (declAndInit.hasInitializer) {
              Multiverse<StringBuilder> configInitializers = declAndInit.initializerSBMV;

              for (Element<StringBuilder> initializer : configInitializers) {
                addSUEDeclsToSymTab(subparser.getPresenceCondition().and(initializer.getCondition()), (CContext)subparser.scope, type, decl);
                Multiverse<SymbolTable.Entry> entries
                  = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition().and(initializer.getCondition()));
                // TODO: destruct multiverse when done
                
                // ensures that entries does not contain more than one renaming under this PC
                if (entries.size() > 1) {
                  System.err.println("ERROR: symboltable contains multiple renamings under a single presence condition");
                }

                // writes the declaration
                for (Element<SymbolTable.Entry> elem : entries) {
                  DeclBuilder renamedDecl = new DeclBuilder(decl);
                  renamedDecl.identifier = elem.getData().getRenaming();
                  if (type.size() == 1) {
                    if (type.get(0).getData().toType().getClass().getName().equals("xtc.type.TypedefT")) {
                      System.err.println("WARNING: typedef transformations not yet supported.");
                    }
                    sb.append("\n" + type.get(0).getData().toType() + " " + renamedDecl + " /* renamed from " + oldIdent + " */ ");
                  } else {
                    System.err.println("ERROR: Configurable typedefs not yet supported.");
                    // System.exit(1);
                  }
                }
                sb.append(initializer.getData());
                sb.append(";\n");
              }
            } else {
              // if there is no initializer under any presence condition,
              // then we add this variable to the symboltable, and write its declaration.
              addSUEDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
              Multiverse<SymbolTable.Entry> entries
                = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
              // TODO: destruct multiverse when done
              
              // ensures that entries does not contain more than one renaming under this PC
              if (entries.size() > 1) {
                System.err.println("ERROR: symboltable contains multiple renamings under a single presence condition");
              }

              // writes the declaration
              for (Element<SymbolTable.Entry> elem : entries) {
                DeclBuilder renamedDecl = new DeclBuilder(decl);
                renamedDecl.identifier = elem.getData().getRenaming();
                if (type.size() == 1) {
                  if (type.get(0).getData().toType().getClass().getName().equals("xtc.type.TypedefT")) {
                    System.err.println("WARNING: typedef transformations not yet supported.");
                  }
                  sb.append("\n" + type.get(0).getData().toType() + " " + renamedDecl + ";" + " /* renamed from " + oldIdent + " */ \n");
                } else {
                  System.err.println("ERROR: Configurable typedefs not yet supported.");
                  // System.exit(1);
                }
              }
            }
        	}

        	// stores the generated declarations and initializing statements in an SBMV wrapper,
        	// then sets the SBMV as this node's semantic value
          Multiverse<StringBuilder> declarationSBMVWrapper = new Multiverse<StringBuilder>();
        	declarationSBMVWrapper.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, declarationSBMVWrapper);
        }
        | DeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
        	// gets the type, the declarations, and any initializers
        	TypeAndDeclInitList TBDBList = getTBDBListAt(subparser, 3);
        	TypeBuilderMultiverse type = TBDBList.type;
        	List<TypeAndDeclInitList.DeclAndInit> declAndInits = TBDBList.declAndInitList;


        	// all declarations get generated, with no if(PC) {} wrapped around them,
          // so we can append every declaration to a single stringbuilder
        	StringBuilder sb = new StringBuilder();

          // generates declarations and statements with the retrieved information
        	for (TypeAndDeclInitList.DeclAndInit declAndInit : declAndInits) {
        		DeclBuilder decl = declAndInit.decl;
	          String oldIdent = decl.identifier;
	          System.err.println(decl.toString() + " " + type.toString());

            // if the declaration has an initializer under at least one presence condition,
            // then we iterate through every initializer, add a new instance to the symtab,
            // then write the declaration of that new variable with its initializer.
            if (declAndInit.initializerSBMV.size() > 0) {
              Multiverse<StringBuilder> configInitializers = declAndInit.initializerSBMV;

              for (Element<StringBuilder> initializer : configInitializers) {
                addDeclsToSymTab(subparser.getPresenceCondition().and(initializer.getCondition()), (CContext)subparser.scope, type, decl);
                Multiverse<SymbolTable.Entry> entries
                  = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition().and(initializer.getCondition()));
                // TODO: destruct multiverse when done
                
                // ensures that entries does not contain more than one renaming under this PC
                if (entries.size() > 1) {
                  System.err.println("ERROR: symboltable contains multiple renamings under a single presence condition");
                }

                // writes the declaration
                for (Element<SymbolTable.Entry> elem : entries) {
                  DeclBuilder renamedDecl = new DeclBuilder(decl);
                  renamedDecl.identifier = elem.getData().getRenaming();
                  if (type.size() == 1) {
                    if (type.get(0).getData().toType().getClass().getName().equals("xtc.type.TypedefT")) {
                      System.err.println("WARNING: typedef transformations not yet supported.");
                    }
                    sb.append("\n" + type.get(0).getData().toType() + " " + renamedDecl + " /* renamed from " + oldIdent + " */ ");
                  } else {
                    System.err.println("ERROR: Configurable typedefs not yet supported.");
                    // System.exit(1);
                  }
                }
                sb.append(initializer.getData());
                sb.append(";\n");
              }
            } else {
              // if there is no initializer under any presence condition,
              // then we add this variable to the symboltable, and write its declaration.
              addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
              Multiverse<SymbolTable.Entry> entries
                = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
              // TODO: destruct multiverse when done
              
              // ensures that entries does not contain more than one renaming under this PC
              if (entries.size() > 1) {
                System.err.println("ERROR: symboltable contains multiple renamings under a single presence condition");
              }

              // writes the declaration
              for (Element<SymbolTable.Entry> elem : entries) {
                DeclBuilder renamedDecl = new DeclBuilder(decl);
                renamedDecl.identifier = elem.getData().getRenaming();
                if (type.size() == 1) {
                  if (type.get(0).getData().toType().getClass().getName().equals("xtc.type.TypedefT")) {
                    System.err.println("WARNING: typedef transformations not yet supported.");
                  }
                  sb.append("\n" + type.get(0).getData().toType() + " " + renamedDecl + ";" + " /* renamed from " + oldIdent + " */ \n");
                } else {
                  System.err.println("ERROR: Configurable typedefs not yet supported.");
                  // System.exit(1);
                }
              }
            } 
        	}

        	// stores the generated declarations and initializing statements in an SBMV wrapper,
        	// then sets the SBMV as this node's semantic value
          Multiverse<StringBuilder> declarationSBMVWrapper = new Multiverse<StringBuilder>();
        	declarationSBMVWrapper.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, declarationSBMVWrapper);
        }
        | DefaultDeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 3);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

/* Note that if a typedef were  redeclared,  then  a  declaration
   specifier must be supplied */

DefaultDeclaringList:  /** nomerge **/  /* Can't  redeclare typedef names */
        DeclarationQualifierList IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
        }
        | TypeQualifierList IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
        }
        | DefaultDeclaringList COMMA AttributeSpecifierListOpt IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList");
          System.exit(1);
        }
        ;

DeclaringList:  /** nomerge **/
        DeclarationSpecifier Declarator AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          // gets the type, declaration, and optional initializer information from the children nodes
          TypeBuilderMultiverse type = getTBAt(subparser, 5);
          DeclBuilder decl = getDBAt(subparser, 4);
          System.err.println(decl.toString() + " " + type.toString());
          saveBaseType(subparser, getNodeAt(subparser, 5));
          bindIdent(subparser, getTBAt(subparser, 5), getDBAt(subparser, 4));
          Multiverse<StringBuilder> initializer = getSBMVAt(subparser, 1);

          // TODO: AssemblyExpressionOpt and AttributeSpecifierListOpt
          System.err.println("WARNING: skipping some children of DeclaringList");

          // wraps the information in a TypeAndDeclInitList
          TypeAndDeclInitList TBDBList = new TypeAndDeclInitList(type, decl, initializer);

          setTFValue(value, TBDBList);
        }
        | TypeSpecifier Declarator AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          // gets the type, declaration, and optional initializer information from the children nodes
          DeclBuilder decl = getDBAt(subparser, 4);
          TypeBuilderMultiverse type = getTBAt(subparser, 5);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, type, decl);
          Multiverse<StringBuilder> initializer = getSBMVAt(subparser, 1);
          
          // TODO: AssemblyExpressionOpt and AttributeSpecifierListOpt
          System.err.println("WARNING: skipping some children of DeclaringList");

          // wraps the information in a TypeAndDeclInitList
          TypeAndDeclInitList TBDBList = new TypeAndDeclInitList(type, decl, initializer);

          setTFValue(value, TBDBList);
        }
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator
        {
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          // gets the type, declaration, and optional initializer information from the children nodes
          Multiverse<StringBuilder> initializer = getSBMVAt(subparser, 1);
          DeclBuilder decl = getDBAt(subparser, 5);
          TypeAndDeclInitList TBDBListChild = getTBDBListAt(subparser, 8);

          // TODO: AssemblyExpressionOpt and AttributeSpecifierListOpt
          System.err.println("WARNING: skipping some children of DeclaringList");
          
          // copies the child declaring list
          TypeAndDeclInitList TBDBList = new TypeAndDeclInitList(TBDBListChild);

          // adds this new declaration to the list of declarations
          TBDBList.addDeclAndInit(decl, initializer);
          
          setTFValue(value, TBDBList);
        }
        ;


DeclarationSpecifier:  /**  nomerge **/
        BasicDeclarationSpecifier        /* Arithmetic or void */
				{
	  			TypeBuilderMultiverse decl = getTBAt(subparser, 1);
	  			setTFValue(value, decl);
				}
        | SUEDeclarationSpecifier          /* struct/union/enum */
				{
					System.err.println("Unsupported grammar DeclarationSpecifier-SUE"); // TODO
          System.exit(1);
				}
        | TypedefDeclarationSpecifier      /* typedef*/
				{
	 				TypeBuilderMultiverse decl = getTBAt(subparser, 1);
	  			setTFValue(value, decl);
				}
        | VarArgDeclarationSpecifier  // ADDED
        {
					System.err.println("Unsupported grammar DeclarationSpecifier-VarArg"); // TODO
          System.exit(1);
				}
        | TypeofDeclarationSpecifier // ADDED
        {
					System.err.println("Unsupported grammar DeclarationSpecifier-TypeofDeclSpec"); // TODO
          System.exit(1);
				}
        ;

TypeSpecifier:  /** nomerge **/
        BasicTypeSpecifier                 /* Arithmetic or void */
				{
          // TODO: are there any issues with sharing references to the same type builder object?
          TypeBuilderMultiverse t = getTBAt(subparser,1);
        	setTFValue(value,t);
				}
        | SUETypeSpecifier                 /* Struct/Union/Enum */
				{
					System.err.println("Unsupported grammar TypeSpecifier-SUE"); // TODO
          System.exit(1);
				}
				| TypedefTypeSpecifier             /* Typedef */
				{
					setTFValue(value,getTBAt(subparser,1));
				}
        | VarArgTypeSpecifier  // ADDED
				{
					System.err.println("Unsupported grammar TypeSpecifier-VarArg"); // TODO
          System.exit(1);
				}
        | TypeofTypeSpecifier // ADDED
				{
					System.err.println("Unsupported grammar TypeSpecifier-Typeof"); // TODO
					System.exit(1);
				}
        ;

DeclarationQualifierList:  /** list, nomerge **/  /* const/volatile, AND storage class */
        StorageClass
      	{
      	  TypeBuilderMultiverse storage = getTBAt(subparser,1);
      	  setTFValue(value, storage);
      	  updateSpecs(subparser,
          getSpecsAt(subparser, 1),
          value);
      	}
      	| TypeQualifierList StorageClass
      	{
      	  TypeBuilderMultiverse qualList = getTBAt(subparser, 2);
      	  TypeBuilderMultiverse storage = getTBAt(subparser, 1);
      	  TypeBuilderMultiverse tb = qualList.combine(storage);
      	  setTFValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | DeclarationQualifierList DeclarationQualifier
      	{
      	  TypeBuilderMultiverse qualList = getTBAt(subparser, 2);
      	  TypeBuilderMultiverse qual = getTBAt(subparser, 1);
      	  TypeBuilderMultiverse tb = qualList.combine(qual);
      	  setTFValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        ;

TypeQualifierList:  /** list, nomerge **/
        TypeQualifier
      	{
      	  TypeBuilderMultiverse qual = getTBAt(subparser, 1);
      	  setTFValue(value, qual);
    	    updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | TypeQualifierList TypeQualifier
      	{
      	  TypeBuilderMultiverse qualList = getTBAt(subparser, 2);
      	  TypeBuilderMultiverse qual = getTBAt(subparser, 1);
      	  TypeBuilderMultiverse tb = qualList.combine(qual);
      	  setTFValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        ;

DeclarationQualifier:
        TypeQualifier                  /* const or volatile */
        {
          TypeBuilderMultiverse qual = getTBAt(subparser, 1);
          setTFValue(value, qual);
        }
        | StorageClass
        {
          TypeBuilderMultiverse storage = getTBAt(subparser, 1);
          setTFValue(value, storage);
        }
        ;

TypeQualifier:    // const, volatile, and restrict can have underscores
        ConstQualifier
        {
          TypeBuilderMultiverse qual = new TypeBuilderMultiverse("const", subparser.getPresenceCondition());
          setTFValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VolatileQualifier
        {
          TypeBuilderMultiverse qual = new TypeBuilderMultiverse("volatile", subparser.getPresenceCondition());
          setTFValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | RestrictQualifier
        {
          TypeBuilderMultiverse qual = new TypeBuilderMultiverse("restrict", subparser.getPresenceCondition());
          setTFValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | AttributeSpecifier // ADDED
        {
          System.err.println("Unsupported grammar TypeQualifier-Attribute"); // TODO
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | FunctionSpecifier  // ADDED
        {
          TypeBuilderMultiverse qual = new TypeBuilderMultiverse("inline", subparser.getPresenceCondition());
          setTFValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

ConstQualifier:    // ADDED
        CONST
        {
        }
        | __CONST
        {
        }
        | __CONST__
        {
        }
        ;

VolatileQualifier:   // ADDED
        VOLATILE
        {
        }
        | __VOLATILE
        {
        }
        | __VOLATILE__
        {
        }
        ;

RestrictQualifier:   // ADDED
        RESTRICT
        {
          System.err.println("WARNING: unsupported semantic action: RestrictQualifier");
          System.exit(1);
        }
        | __RESTRICT
        {
          System.err.println("WARNING: unsupported semantic action: RestrictQualifier");
          System.exit(1);
        }
        | __RESTRICT__
        {
          System.err.println("WARNING: unsupported semantic action: RestrictQualifier");
          System.exit(1);
        }
        ;

FunctionSpecifier:  // ADDED
        INLINE
        {
        }
        | __INLINE
        {
        }
        | __INLINE__
        {
        }
        ;

BasicDeclarationSpecifier: /** nomerge **/      /*StorageClass+Arithmetic or void*/
        BasicTypeSpecifier  StorageClass
        {
        TypeBuilderMultiverse basicTypeSpecifier = getTBAt(subparser, 2);
        TypeBuilderMultiverse storageClass = getTBAt(subparser, 1);

        // combine the partial type specs
        TypeBuilderMultiverse tb = basicTypeSpecifier.combine(storageClass);

        setTFValue(value, tb);
	      updateSpecs(subparser,
                    getSpecsAt(subparser, 2),
                    getSpecsAt(subparser, 1),
                    value);
        }
        | DeclarationQualifierList BasicTypeName {
	        TypeBuilderMultiverse qualList = getTBAt(subparser, 2);
          TypeBuilderMultiverse basicTypeName = getTBAt(subparser, 1);

          // combine the partial type specs
          TypeBuilderMultiverse tb = qualList.combine(basicTypeName);

	        setTFValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier DeclarationQualifier
        {
 	        TypeBuilderMultiverse decl = getTBAt(subparser, 2);
          TypeBuilderMultiverse qual = getTBAt(subparser, 1);

          // combine the partial type specs
          TypeBuilderMultiverse tb = decl.combine(qual);

      	  setTFValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier BasicTypeName
        {
	        TypeBuilderMultiverse basicDeclSpecifier = getTBAt(subparser, 2);
          TypeBuilderMultiverse basicTypeName = getTBAt(subparser, 1);

          // combine the partial type specs
          TypeBuilderMultiverse tb = basicDeclSpecifier.combine(basicTypeName);

      	  setTFValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

BasicTypeSpecifier: /**  nomerge **/
        BasicTypeName           /* Arithmetic or void */
        {
          // TUTORIAL: a semantic action that sets the semantic value
          // to a new typebuilder by adding a property derived from
          // the child semantic value(s)
          TypeBuilderMultiverse tb = getTBAt(subparser, 1);
          setTFValue(value, tb);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);

        }
        | TypeQualifierList BasicTypeName
	      {
          TypeBuilderMultiverse qualList = getTBAt(subparser, 2);
          TypeBuilderMultiverse basicTypeName = getTBAt(subparser, 1);

          TypeBuilderMultiverse tb = qualList.combine(basicTypeName);

          setTFValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier TypeQualifier
	      {
          TypeBuilderMultiverse basicTypeSpecifier = getTBAt(subparser, 2);
          TypeBuilderMultiverse qual = getTBAt(subparser, 1);

          TypeBuilderMultiverse tb = basicTypeSpecifier.combine(qual);

          setTFValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier BasicTypeName
        {
          // get the semantic values of each child
          TypeBuilderMultiverse basicTypeSpecifier = getTBAt(subparser, 2);
          TypeBuilderMultiverse basicTypeName = getTBAt(subparser, 1);

          // combine the partial type specs
          TypeBuilderMultiverse tb = basicTypeSpecifier.combine(basicTypeName);

          setTFValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

SUEDeclarationSpecifier: /** nomerge **/          /* StorageClass + struct/union/enum */
        SUETypeSpecifier StorageClass
        {
          System.err.println("WARNING: unsupported semantic action: SUEDeclarationSpecifier");
          System.exit(1);
        }
        | DeclarationQualifierList ElaboratedTypeName
        {
          System.err.println("WARNING: unsupported semantic action: SUEDeclarationSpecifier");
          System.exit(1);
        }
        | SUEDeclarationSpecifier DeclarationQualifier
        {
          System.err.println("WARNING: unsupported semantic action: SUEDeclarationSpecifier");
          System.exit(1);
        }
        ;

SUETypeSpecifier: /** nomerge **/
        ElaboratedTypeName              /* struct/union/enum */
        {
          setTFValue(value, getTBDBListAt(subparser, 1));
        }
        | TypeQualifierList ElaboratedTypeName
        {
          System.err.println("WARNING: unsupported semantic action: SUETypeSpecifier");
          //System.exit(1);
        }
        | SUETypeSpecifier TypeQualifier
        {
          System.err.println("WARNING: unsupported semantic action: SUETypeSpecifier");
          System.exit(1);
        }
        ;


TypedefDeclarationSpecifier: /** nomerge **/       /*Storage Class + typedef types */
        TypedefTypeSpecifier StorageClass
      	{
      	  TypeBuilderMultiverse tb = getTBAt(subparser, 2);
          TypeBuilderMultiverse tb1 = getTBAt(subparser, 1);
          setTFValue(value, tb.combine(tb1));
                	}
        | DeclarationQualifierList TYPEDEFname
        {
      	  TypeBuilderMultiverse tb = getTBAt(subparser, 2);
          TypeBuilderMultiverse tb1 = new TypeBuilderMultiverse();
      	  String typeName = getStringAt(subparser, 1);
      	  tb1.setTypedef(typeName, getTypeOfTypedef(subparser, typeName), subparser.getPresenceCondition());
          setTFValue(value, tb.combine(tb1));
                	}
        | TypedefDeclarationSpecifier DeclarationQualifier
      	{
      	  TypeBuilderMultiverse tb1 = getTBAt(subparser, 2);
      	  TypeBuilderMultiverse dq = getTBAt(subparser,1);
      	  TypeBuilderMultiverse tb = tb1.combine(dq);
          setTFValue(value, tb);
                	}
        ;

TypedefTypeSpecifier: /** nomerge **/              /* typedef types */
        TYPEDEFname
      	{
      	  TypeBuilderMultiverse tb1 = new TypeBuilderMultiverse();
      	  String typeName = getStringAt(subparser, 1);
      	  tb1.setTypedef(typeName, getTypeOfTypedef(subparser, typeName), subparser.getPresenceCondition());
          setTFValue(value, tb1);
                	}
        | TypeQualifierList TYPEDEFname
      	{
      	  TypeBuilderMultiverse tb = getTBAt(subparser, 2);
          TypeBuilderMultiverse tb1 = new TypeBuilderMultiverse();
      	  String typeName = getStringAt(subparser, 1);
      	  tb1.setTypedef(typeName, getTypeOfTypedef(subparser, typeName), subparser.getPresenceCondition());
          setTFValue(value, tb.combine(tb1));

      	}
        | TypedefTypeSpecifier TypeQualifier
        {
          TypeBuilderMultiverse tb = getTBAt(subparser, 2);
          TypeBuilderMultiverse tb1 = getTBAt(subparser, 1);
          setTFValue(value, tb.combine(tb1));
                  }
;

TypeofDeclarationSpecifier: /** nomerge **/      /*StorageClass+Arithmetic or void*/
        TypeofTypeSpecifier  StorageClass
        {
          System.err.println("WARNING: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
        | DeclarationQualifierList Typeofspecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
        | TypeofDeclarationSpecifier DeclarationQualifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
        | TypeofDeclarationSpecifier Typeofspecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
        ;

TypeofTypeSpecifier: /** nomerge **/  // ADDED
        Typeofspecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
        | TypeQualifierList Typeofspecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
        | TypeofTypeSpecifier TypeQualifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
        | TypeofTypeSpecifier Typeofspecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
        ;

Typeofspecifier: /** nomerge **/  // ADDED
        Typeofkeyword LPAREN TypeName RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: Typeofspecifier");
          System.exit(1);
        }
        | Typeofkeyword LPAREN Expression RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: Typeofspecifier");
          System.exit(1);
        }
        ;

Typeofkeyword: /** nomerge **/  // ADDED
        TYPEOF
        {
          System.err.println("WARNING: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
        | __TYPEOF
        {
          System.err.println("WARNING: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
        | __TYPEOF__
        {
          System.err.println("WARNING: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
        ;

VarArgDeclarationSpecifier:      /*StorageClass+Arithmetic or void*/
        VarArgTypeSpecifier StorageClass
        {
          System.err.println("WARNING: unsupported semantic action: VarArgDeclarationSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | DeclarationQualifierList VarArgTypeName
        {
          System.err.println("WARNING: unsupported semantic action: VarArgDeclarationSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgDeclarationSpecifier DeclarationQualifier
        {
          System.err.println("WARNING: unsupported semantic action: VarArgDeclarationSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgDeclarationSpecifier VarArgTypeName
        {
          System.err.println("WARNING: unsupported semantic action: VarArgDeclarationSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

VarArgTypeSpecifier:
        VarArgTypeName
        {
          System.err.println("WARNING: unsupported semantic action: VarArgTypeSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeQualifierList VarArgTypeName
        {
          System.err.println("WARNING: unsupported semantic action: VarArgTypeSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgTypeSpecifier TypeQualifier
        {
          System.err.println("WARNING: unsupported semantic action: VarArgTypeSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VarArgTypeSpecifier VarArgTypeName
        {
          System.err.println("WARNING: unsupported semantic action: VarArgTypeSpecifier");
          System.exit(1);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

VarArgTypeName:  // ADDED
        __BUILTIN_VA_LIST
        {
          System.err.println("WARNING: unsupported semantic action: VarArgTypeName");
          System.exit(1);
          getSpecsAt(subparser, 1).type = InternalT.VA_LIST;
        }
        ;

StorageClass:
        TYPEDEF
    	{
          String storageName = getNodeAt(subparser, 1).getTokenText();
    	  TypeBuilderMultiverse storage = new TypeBuilderMultiverse(storageName, subparser.getPresenceCondition());
    	  setTFValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF;
    	}
        | EXTERN
  	{
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeBuilderMultiverse storage = new TypeBuilderMultiverse(storageName, subparser.getPresenceCondition());
  	  setTFValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN;
  	}
        | STATIC
  	{
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeBuilderMultiverse storage = new TypeBuilderMultiverse(storageName, subparser.getPresenceCondition());
  	  setTFValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC;
  	}
        | AUTO
  	{
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeBuilderMultiverse storage = new TypeBuilderMultiverse(storageName, subparser.getPresenceCondition());
  	  setTFValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO;
  	}
        | REGISTER
  	{
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeBuilderMultiverse storage = new TypeBuilderMultiverse(storageName, subparser.getPresenceCondition());
  	  setTFValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_REGISTER;
        }
        ;

BasicTypeName:
        VOID
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(VoidT.TYPE, subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).type = VoidT.TYPE;

        }
        | CHAR
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.CHAR, subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).seenChar = true;
        }
        | SHORT
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.SHORT, subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).seenShort = true;
        }
        | INT
        {
          // See xtc.type.* for the class hiearchy for types
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.INT, subparser.getPresenceCondition());
          setTFValue(value, tb);
                    getSpecsAt(subparser, 1).seenInt = true;
        }
        | __INT128
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.__INT128, subparser.getPresenceCondition());
          setTFValue(value, tb);
                	  getSpecsAt(subparser, 1).seenInt = true;
        }
        | LONG
        {
          // See xtc.type.* for the class hiearchy for types
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.LONG, subparser.getPresenceCondition());
      	  setTFValue(value, tb);
                	  getSpecsAt(subparser, 1).longCount++;
        }
        | FLOAT
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.FLOAT, subparser.getPresenceCondition());
          setTFValue(value, tb);
                    getSpecsAt(subparser, 1).seenFloat = true;
        }
        | DOUBLE
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(NumberT.DOUBLE, subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).seenDouble = true;
        }
        | SignedKeyword
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse("signed", subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).seenSigned = true;
        }
        | UNSIGNED
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse("unsigned", subparser.getPresenceCondition());
          setTFValue(value, tb);
          getSpecsAt(subparser, 1).seenUnsigned = true;
        }
        | _BOOL
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse(BooleanT.TYPE, subparser.getPresenceCondition());
          setTFValue(value, tb);
          	  getSpecsAt(subparser, 1).seenBool = true;
        }
        | ComplexKeyword
        {
          TypeBuilderMultiverse tb = new TypeBuilderMultiverse("complex", subparser.getPresenceCondition());
          setTFValue(value, tb);
          getSpecsAt(subparser, 1).seenComplex = true;
        }
        ;

SignedKeyword:
        SIGNED
	{
	  System.err.println("WARNING: empty semantic action: SignedKeyword");
	}
        | __SIGNED
	{
	  System.err.println("WARNING: empty semantic action: SignedKeyword");
	}
        | __SIGNED__
	{
	  System.err.println("WARNING: empty semantic action: SignedKeyword");
	}
        ;

ComplexKeyword:
        _COMPLEX
	{
	  System.err.println("WARNING: empty semantic action: ComplexKeyword");
	}
        | __COMPLEX__
	{
	  System.err.println("WARNING: empty semantic action: ComplexKeyword");
	}
        ;

ElaboratedTypeName: /** passthrough, nomerge **/
        StructSpecifier
        {
          setTFValue(value, getTBDBListAt(subparser, 1));
        }
        | UnionSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: ElaboratedTypeName");
          System.exit(1);
        }
        | EnumSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: ElaboratedTypeName");
          System.exit(1);
        }
        ;

StructSpecifier: /** nomerge **/  // ADDED attributes
        STRUCT { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
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
          DeclBuilder d = getDBAt(subparser,6);
          d.setFields(getFieldAt(subparser,3));
          TypeBuilderMultiverse t = new TypeBuilderMultiverse();
          TypeBuilderUnit tu = new TypeBuilderUnit();
          tu.setIsStruct();
          t.add(tu, subparser.getPresenceCondition());
          TypeAndDeclInitList.DeclAndInit declAndInit = new TypeAndDeclInitList.DeclAndInit();
          declAndInit.addDeclNoInit(d);
        	LinkedList<TypeAndDeclInitList.DeclAndInit> declAndInitList =
            new LinkedList<TypeAndDeclInitList.DeclAndInit>();
        	declAndInitList.add(declAndInit);
          TypeAndDeclInitList TBDBList = new TypeAndDeclInitList(t, declAndInitList);
          setTFValue(value, TBDBList);
        }
        | STRUCT IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
        }
        | STRUCT AttributeSpecifierList { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
          Node tag     = getNodeAt(subparser, 6);
          Node members = getNodeAt(subparser, 3);
          Node attrs   = getNodeAt(subparser, 7);
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
        }
        | STRUCT AttributeSpecifierList IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
        }
        ;

UnionSpecifier: /** nomerge **/  // ADDED attributes
        UNION { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        | UNION IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        | UNION IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        | UNION AttributeSpecifierList { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        | UNION AttributeSpecifierList IdentifierOrTypedefName { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        /* { */
        /*    updateSpecs(subparser,
                          makeStruct()); */
        /* } */
        | UNION AttributeSpecifierList IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: UnionSpecifier");
          System.exit(1);
        }
        ;

StructDeclarationList: /** list, nomerge **/
        /* StructDeclaration */ /* ADDED gcc empty struct */
        {
          ((Node) value).setProperty(SPECS, new Specifiers());
          List<Multiverse<VariableT>> l = new LinkedList<Multiverse<VariableT>>();
          setTFValue(value, l);
        }
        | StructDeclarationList StructDeclaration {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
          List<Multiverse<VariableT>> l = getFieldAt(subparser, 2);
          l.addAll(getFieldAt(subparser, 1));
          setTFValue(value, l);
        }
        ;

StructDeclaration: /** nomerge **/
        StructDeclaringList SEMICOLON
        {
          setTFValue(value, getFieldAt(subparser, 2));
        }
        | StructDefaultDeclaringList SEMICOLON
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaration");
          System.exit(1);
        }
        | TypeQualifierList SEMICOLON  // ADDED Declarator is optional
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaration");
          System.exit(1);
        }
        | TypeSpecifier SEMICOLON  // ADDED Declarator is optional
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaration");
          System.exit(1);
        }
        | SEMICOLON // ADDED gcc allows empty struct field in declaration
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaration");
          System.exit(1);
        }
        ;

StructDefaultDeclaringList: /** list, nomerge **/        /* doesn't redeclare typedef*/
        TypeQualifierList StructIdentifierDeclarator AttributeSpecifierListOpt
        {
          System.err.println("WARNING: unsupported semantic action: StructDefaultDeclaringList");
          //System.exit(1);
        }
        | StructDefaultDeclaringList COMMA StructIdentifierDeclarator AttributeSpecifierListOpt
        {
          System.err.println("WARNING: unsupported semantic action: StructDefaultDeclaringList");
          //System.exit(1);
        }
        ;

StructDeclaringList: /** list, nomerge **/
        TypeSpecifier StructDeclarator AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 2);
      	  TypeBuilderMultiverse type = getTBAt(subparser, 3);
          Multiverse<VariableT> mv = new Multiverse<VariableT>();
          for (Element<TypeBuilderUnit> e : type) {
            DeclBuilder temp = new DeclBuilder(decl);
            temp.addType(e.getData().toType());
            mv.add(VariableT.newField(temp.toType(), temp.getID()), e.getCondition());
          }
          List<Multiverse<VariableT>> l = new LinkedList<Multiverse<VariableT>>();
          l.add(mv);
          setTFValue(value, l);
        }
        | StructDeclaringList COMMA StructDeclarator AttributeSpecifierListOpt
        {
          
          System.err.println("WARNING: unsupported semantic action: StructDeclaringList");
          System.exit(1);
        }
        ;

StructDeclarator: /** nomerge **/
        Declarator BitFieldSizeOpt
        {
          DeclBuilder db = getDBAt(subparser,2);
      	  setTFValue(value, db);
        }
        | BitFieldSize
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclarator");
          System.exit(1);
        }
        ;

StructIdentifierDeclarator: /** nomerge **/
        IdentifierDeclarator BitFieldSizeOpt
        {
          System.err.println("WARNING: unsupported semantic action: StructIdentifierDeclarator");
          System.exit(1);
        }
        | BitFieldSize
        {
          System.err.println("WARNING: unsupported semantic action: StructIdentifierDeclarator");
          System.exit(1);
        }
        ;

BitFieldSizeOpt: /** nomerge **/
        /* nothing */
        | BitFieldSize
        {
          System.err.println("WARNING: unsupported semantic action: BitFieldSizeOpt");
          System.exit(1);
        }
        ;

BitFieldSize: /** nomerge **/
        COLON ConstantExpression
        {
          System.err.println("WARNING: unsupported semantic action: BitFieldSize");
          System.exit(1);
        }
        ;

EnumSpecifier: /** nomerge **/  /* ADDED attributes */
        ENUM LBRACE EnumeratorList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM IdentifierOrTypedefName LBRACE EnumeratorList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM AttributeSpecifierList LBRACE EnumeratorList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM AttributeSpecifierList IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM AttributeSpecifierList LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        {
          System.err.println("WARNING: unsupported semantic action: EnumSpecifier");
          System.exit(1);
        }
        ;

/*EnumeratorList:
        IdentifierOrTypedefName EnumeratorValueOpt
        | EnumeratorList COMMA IdentifierOrTypedefName EnumeratorValueOpt
        ;*/

EnumeratorList:  /** list, nomerge **/  // easier to bind
        Enumerator
        {
          System.err.println("WARNING: unsupported semantic action: EnumeratorList");
          System.exit(1);
        }
        | EnumeratorList COMMA Enumerator
        {
          System.err.println("WARNING: unsupported semantic action: EnumeratorList");
          System.exit(1);
        }
        ;

Enumerator: /** nomerge **/
        IDENTIFIER { BindEnum(subparser); } EnumeratorValueOpt
        {
          System.err.println("WARNING: unsupported semantic action: Enumerator");
          System.exit(1);
        }
        | TYPEDEFname { BindEnum(subparser); } EnumeratorValueOpt
        {
          System.err.println("WARNING: unsupported semantic action: Enumerator");
          System.exit(1);
        }
        ;

EnumeratorValueOpt: /** nomerge **/
        /* Nothing */
        | ASSIGN ConstantExpression
        {
          System.err.println("WARNING: unsupported semantic action: EnumeratorValueOpt");
          System.exit(1);
        }
        ;

ParameterTypeList:  /** nomerge **/
        ParameterList
        {
          setTFValue(value, getParamAt(subparser,1));
        }
        | ParameterList COMMA ELLIPSIS
        {
          List<Multiverse<Parameter>> ps = getParamAt(subparser,3);
          Parameter p = new Parameter();
          p.setEllipsis();
          Multiverse<Parameter> m = new Multiverse<Parameter>();
          m.add(p,subparser.getPresenceCondition());
          ps.add(m);
          setTFValue(value,ps);
        }
        ;

ParameterList:  /** list, nomerge **/
        ParameterDeclaration
        {
          setTFValue(value, getParamAt(subparser,1));
        }
        | ParameterList COMMA ParameterDeclaration
        {
          List<Multiverse<Parameter>> p = getParamAt(subparser,3);
          p.addAll(getParamAt(subparser,1));
          setTFValue(value,p);
        }
        ;

/* ParameterDeclaration:  /\** nomerge **\/ */
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

ParameterDeclaration:  /** nomerge **/
        ParameterIdentifierDeclaration
        {
          setTFValue(value, getParamAt(subparser,1));
        }
        | ParameterAbstractDeclaration
        {
          setTFValue(value, getParamAt(subparser,1));
        }
        ;

ParameterAbstractDeclaration:
        DeclarationSpecifier
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid()) {
              ent = new Entry("",e.getData().toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter x = new Parameter();
            x.setVar(ent);
            p.add(x, e.getCondition());
          }            
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | DeclarationSpecifier AbstractDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder d = getDBAt(subparser,1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid() && d.getIsValid()) {
              DeclBuilder x = new DeclBuilder(d);
              x.addType(e.getData().toType());
              ent = new Entry("",x.toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter pa = new Parameter();
            pa.setVar(ent);
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | DeclarationQualifierList
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid()) {
              ent = new Entry("",e.getData().toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter x = new Parameter();
            x.setVar(ent);
            p.add(x, e.getCondition());
          }            
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | DeclarationQualifierList AbstractDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder d = getDBAt(subparser,1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid() && d.getIsValid()) {
              DeclBuilder x = new DeclBuilder(d);
              x.addType(e.getData().toType());
              ent = new Entry("",x.toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter pa = new Parameter();
            pa.setVar(ent);
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeSpecifier
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid()) {
              ent = new Entry("",e.getData().toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter x = new Parameter();
            x.setVar(ent);
            p.add(x, e.getCondition());
          }            
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeSpecifier AbstractDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder d = getDBAt(subparser,1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid() && d.getIsValid()) {
              DeclBuilder x = new DeclBuilder(d);
              x.addType(e.getData().toType());
              ent = new Entry("",x.toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter pa = new Parameter();
            pa.setVar(ent);
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeQualifierList
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid()) {
              ent = new Entry("",e.getData().toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter x = new Parameter();
            x.setVar(ent);
            p.add(x, e.getCondition());
          }            
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeQualifierList AbstractDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder d = getDBAt(subparser,1);
          Multiverse<Parameter> p = new Multiverse<Parameter>();
          for (Element<TypeBuilderUnit> e : type) {
            Entry ent;
            if (e.getData().getIsValid() && d.getIsValid()) {
              DeclBuilder x = new DeclBuilder(d);
              x.addType(e.getData().toType());
              ent = new Entry("",x.toType());
            }
            else {
              ent = SymbolTable.ERROR;
            }
            Parameter pa = new Parameter();
            pa.setVar(ent);
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        ;

ParameterIdentifierDeclaration:
        DeclarationSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | DeclarationSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Multiverse<Parameter> p = new Multiverse<Parameter>();
          addDeclsToSymTab(subparser.getPresenceCondition(), (CContext)subparser.scope, type, decl);
          Multiverse<SymbolTable.Entry> entries
            = ((CContext) subparser.scope).getSymbolTable().get(decl.getID(), subparser.getPresenceCondition());
          for (Element<Entry> e : entries) {
            Parameter pa = new Parameter();
            pa.setVar(e.getData());
            p.add(pa, e.getCondition());
          }
          List<Multiverse<Parameter>> lp = new LinkedList<Multiverse<Parameter>>();
          lp.add(p);
          setTFValue(value, lp);
        }
        ;

    /*  ANSI  C  section  3.7.1  states  "An Identifier declared as a
    typedef name shall not be redeclared as a Parameter".  Hence  the
    following is based only on IDENTIFIERs */

IdentifierList:  /** list, nomerge **/
        Identifier
        {
          System.err.println("WARNING: unsupported semantic action: IdentifierList");
          System.exit(1);
        }
        | IdentifierList COMMA Identifier
        {
          System.err.println("WARNING: unsupported semantic action: IdentifierList");
          System.exit(1);
        }
        ;

Identifier:  /** nomerge **/
       IDENTIFIER
       {
         System.err.println("WARNING: unsupported semantic action: Identifier");
         System.exit(1);
         BindVar(subparser);
       }
       ;

IdentifierOrTypedefName: /** nomerge **/
        IDENTIFIER
        {
          DeclBuilder db = new DeclBuilder(getStringAt(subparser, 1));
          setTFValue(value, db);
        }
        | TYPEDEFname
        {
          System.err.println("WARNING: unsupported semantic action: IdentifierOrTypedefName");
          System.exit(1);
        }
        ;

TypeName: /** nomerge **/
        TypeSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: TypeName");
          System.exit(1);
        }
        | TypeSpecifier AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: TypeName");
          System.exit(1);
        }
        | TypeQualifierList
        {
          System.err.println("WARNING: unsupported semantic action: TypeName");
          System.exit(1);
        }
        | TypeQualifierList AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: TypeName");
          System.exit(1);
        }
        ;

InitializerOpt: /** nomerge **/
        /* nothing */
        {
          Multiverse<StringBuilder> emptyInit = new Multiverse<StringBuilder>();
          setTFValue(value, emptyInit);
        }
        | ASSIGN DesignatedInitializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

DesignatedInitializer:/** nomerge, passthrough **/ /* ADDED */
        Initializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Designation Initializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

/*InitializerStandard:  // ADDED gcc can have empty Initializer lists
        LBRACE InitializerList RBRACE
        | AssignmentExpression
        ;*/

Initializer: /** nomerge **/  // ADDED gcc can have empty Initializer lists
        LBRACE MatchedInitializerList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | LBRACE MatchedInitializerList DesignatedInitializer RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

InitializerList:  /** nomerge **/ //modified so that COMMAS are on the right
        MatchedInitializerList
        {
          System.err.println("WARNING: unsupported semantic action: InitializerList");
          System.exit(1);
        }
        | MatchedInitializerList DesignatedInitializer
        {
          System.err.println("WARNING: unsupported semantic action: InitializerList");
          System.exit(1);
        }
        ;

MatchedInitializerList:  /** list, nomerge **/
        | MatchedInitializerList DesignatedInitializer COMMA
        {
          System.err.println("WARNING: unsupported semantic action: MatchedInitializerList");
          // System.exit(1);
          Multiverse<StringBuilder> s = new Multiverse<StringBuilder>();
          s.add(new StringBuilder(""), subparser.getPresenceCondition());
          setTFValue(value, s);
        }
        ;

Designation:   /* ADDED */
        DesignatorList ASSIGN
        {
          System.err.println("WARNING: unsupported semantic action: Designation");
          System.exit(1);
        }
        | ObsoleteArrayDesignation
        {
          System.err.println("WARNING: unsupported semantic action: Designation");
          System.exit(1);
        }
        | ObsoleteFieldDesignation
        {
          System.err.println("WARNING: unsupported semantic action: Designation");
          System.exit(1);
        }
        ;

DesignatorList:  /** list, nomerge **/  /* ADDED */
        Designator
        {
          System.err.println("WARNING: unsupported semantic action: DesignatorList");
          System.exit(1);
        }
        | DesignatorList Designator
        {
          System.err.println("WARNING: unsupported semantic action: DesignatorList");
          System.exit(1);
        }
        ;

Designator:   /* ADDED */
        LBRACK ConstantExpression RBRACK
        {
          System.err.println("WARNING: unsupported semantic action: Designator");
          System.exit(1);
        }
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        {
          System.err.println("WARNING: unsupported semantic action: Designator");
          System.exit(1);
        }
        | DOT IDENTIFIER //IDENTIFIER
        {
          System.err.println("WARNING: unsupported semantic action: Designator");
          System.exit(1);
        }
        | DOT TYPEDEFname // ADDED hack to get around using typedef names as struct fields
        {
          System.err.println("WARNING: unsupported semantic action: Designator");
          System.exit(1);
        }
        ;

ObsoleteArrayDesignation: /** nomerge **/  /* ADDED */
        LBRACK ConstantExpression RBRACK
        {
          System.err.println("WARNING: unsupported semantic action: ObsoleteArrayDesignation");
          System.exit(1);
        }
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        {
          System.err.println("WARNING: unsupported semantic action: ObsoleteArrayDesignation");
          System.exit(1);
        }
        ;

ObsoleteFieldDesignation: /** nomerge **/  /* ADDED */
        IDENTIFIER COLON
        {
          System.err.println("WARNING: unsupported semantic action: ObsoleteFieldDesignation");
          System.exit(1);
        }
        ;

Declarator:  /** nomerge**/
        TypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
        }
        | IdentifierDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
        }
        ;

TypedefDeclarator:  /**  nomerge **/  // ADDED
        TypedefDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);

      	}
        ;

TypedefDeclaratorMain:  /**  nomerge **/
        ParenTypedefDeclarator  /* would be ambiguous as Parameter*/
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        | ParameterTypedefDeclarator   /* not ambiguous as param*/
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        ;

ParameterTypedefDeclarator: /** nomerge **/
        TYPEDEFname
        {
          setTFValue(value, new DeclBuilder(getStringAt(subparser, 1)));
                  }
        | TYPEDEFname PostfixingAbstractDeclarator
      	{
      	  DeclBuilder name = new DeclBuilder(getStringAt(subparser, 2));
      	  DeclBuilder post = getDBAt(subparser,1);
      	  name.merge(post);
          setTFValue(value, name);
                  }
        | CleanTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        ;

    /*  The  following have at least one STAR. There is no (redundant)
    LPAREN between the STAR and the TYPEDEFname. */

CleanTypedefDeclarator: /** nomerge **/
        CleanPostfixTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        | STAR ParameterTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  db.addPointer();
      	  setTFValue(value, db);
                	}
        | STAR TypeQualifierList ParameterTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  DeclBuilder outter = new DeclBuilder();
      	  outter.addPointer();
      	  outter.addQuals(getTBAt(subparser,2),db);
      	  setTFValue(value,outter);
                	}
        ;

CleanPostfixTypedefDeclarator: /** nomerge **/
        LPAREN CleanTypedefDeclarator RPAREN
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  db.addDeclBuilder(getDBAt(subparser,2));
      	  setTFValue(value, db);
                	}
        | LPAREN CleanTypedefDeclarator RPAREN PostfixingAbstractDeclarator
        {
      	  DeclBuilder db = new DeclBuilder();
      	  db.addDeclBuilder(getDBAt(subparser,3));
      	  db.merge(getDBAt(subparser,1));
      	  setTFValue(value, db);
                	}
        ;

    /* The following have a redundant LPAREN placed immediately  to  the
    left of the TYPEDEFname */

ParenTypedefDeclarator:  /** nomerge **/
        ParenPostfixTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        | STAR LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  db.addDeclBuilder(getDBAt(subparser,2));
      	  db.addPointer();
      	  setTFValue(value, db);
                	}
      	| STAR TypeQualifierList
      	LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
      	  DeclBuilder db = getDBAt(subparser,2);
      	  DeclBuilder paren = new DeclBuilder();
      	  DeclBuilder outter = new DeclBuilder();
      	  outter.addPointer();
      	  paren.addDeclBuilder(db);
      	  outter.addQuals(getTBAt(subparser,4),paren);
      	  setTFValue(value,outter);
                	}
        | STAR ParenTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  db.addPointer();
      	  setTFValue(value, db);
                	}
        | STAR TypeQualifierList ParenTypedefDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  DeclBuilder outter = new DeclBuilder();
      	  outter.addPointer();
      	  outter.addQuals(getTBAt(subparser,2),db);
      	  setTFValue(value,outter);
                	}
        ;

ParenPostfixTypedefDeclarator: /** nomerge **/ /* redundant paren to left of tname*/
        LPAREN ParenTypedefDeclarator RPAREN
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  db.addDeclBuilder(getDBAt(subparser,2));
      	  setTFValue(value, db);
                	}
        | LPAREN SimpleParenTypedefDeclarator PostfixingAbstractDeclarator RPAREN /* redundant paren */
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  DeclBuilder base = getDBAt(subparser,3);
      	  base.merge(getDBAt(subparser,2));
      	  db.addDeclBuilder(base);
      	  setTFValue(value, db);
                	}
        | LPAREN ParenTypedefDeclarator RPAREN PostfixingAbstractDeclarator
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  DeclBuilder base = getDBAt(subparser,3);
      	  db.addDeclBuilder(base);
      	  db.merge(getDBAt(subparser,1));
      	  setTFValue(value, db);
                	}
        ;

SimpleParenTypedefDeclarator: /** nomerge **/
        TYPEDEFname
      	{
      	  setTFValue(value, new DeclBuilder(getStringAt(subparser, 1)));
                	}
        | LPAREN SimpleParenTypedefDeclarator RPAREN
      	{
      	  DeclBuilder db = new DeclBuilder();
      	  DeclBuilder base = getDBAt(subparser,2);
      	  db.addDeclBuilder(base);
      	  setTFValue(value, db);
                	}
        ;

IdentifierDeclarator:  /**  nomerge **/
        IdentifierDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        ;

IdentifierDeclaratorMain:  /** nomerge **/
        UnaryIdentifierDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
      	}
        | ParenIdentifierDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
      	}
        ;

UnaryIdentifierDeclarator: /** nomerge **/
        PostfixIdentifierDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
      	}
        | STAR IdentifierDeclarator
        {
      	  DeclBuilder db = getDBAt(subparser,1);
      	  db.addPointer();
      	  setTFValue(value, db);
      	}
        | STAR TypeQualifierList IdentifierDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  DeclBuilder outter = new DeclBuilder();
      	  outter.addPointer();
      	  outter.addQuals(getTBAt(subparser,2),db);
      	  setTFValue(value,outter);
      	}
        ;

PostfixIdentifierDeclarator: /** nomerge **/
        FunctionDeclarator
        {
          setTFValue(value, getDBAt(subparser,1));
        }
        | ArrayDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        | AttributedDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
                	}
        | LPAREN UnaryIdentifierDeclarator RPAREN PostfixingAbstractDeclarator
      	{
      	  DeclBuilder base = new DeclBuilder();
      	  base.addDeclBuilder(getDBAt(subparser,3));
      	  DeclBuilder db = getDBAt(subparser,1);
      	  base.merge(db);
      	  setTFValue(value,base);
                	}
        ;

AttributedDeclarator: /** nomerge **/
        LPAREN UnaryIdentifierDeclarator RPAREN
        {
      	  DeclBuilder db = new DeclBuilder();
      	  db.addDeclBuilder(getDBAt(subparser,2));
      	  setTFValue(value, db);
                	}
        ;

FunctionDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator PostfixingFunctionDeclarator
        {
          // TODO: construct the declaration of main here using the declbuilder stored at ParenIdentifierDeclarator and PostfixingFunctionDeclarator
          DeclBuilder ident = new DeclBuilder(getDBAt(subparser, 2));
          /*StringBuilder sb = new StringBuilder();
          sb.append(ident);
          sb.append(getStringBuilderAt(subparser, 1));
          System.err.println("Node: " + value.hashCode());
          setStringBuilder(value, sb);*/
          ident.setParams(getParamAt(subparser,1));
          setTFValue(value,ident);
                  }
        ;

PostfixingFunctionDeclarator:  /** nomerge **/
        LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN
        {
          //return whatever is in Parameter TypeListOpt
          System.err.println("WARNING: unsupported semantic action: PostfixingFunctionDeclarator");
          /*StringBuilder sb = new StringBuilder("(");
          for (int i = 1; i <= 3; i++)
            if (getStringBuilderAt(subparser, i) != null && !getStringBuilderAt(subparser, i).equals("null"))
              sb.append(getStringBuilderAt(subparser, i));
          sb.append(")");
          setStringBuilder(value, sb);*/
          setTFValue(value,getParamAt(subparser, 3));
        }
        ;

ArrayDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator ArrayAbstractDeclarator
        {
          DeclBuilder base = getDBAt(subparser,2);
          DeclBuilder array = getDBAt(subparser,1);
          base.merge(array);
          setTFValue(value,base);
                  }
        ;

ParenIdentifierDeclarator:  /** nomerge **/
        SimpleDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value, db);
      	}
        | LPAREN ParenIdentifierDeclarator RPAREN
      	{
      	  DeclBuilder db = getDBAt(subparser,2);
      	  DeclBuilder superDecl = new DeclBuilder();
      	  superDecl.addDeclBuilder(db);
      	  setTFValue(value,superDecl);
      	}
        ;

SimpleDeclarator: /** nomerge **/
        IDENTIFIER  /* bind */
        {
          DeclBuilder db = new DeclBuilder(getStringAt(subparser, 1));
          setTFValue(value, db);
        }
        ;

OldFunctionDeclarator: /** nomerge **/
        PostfixOldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
        }
        | STAR OldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
        }
        | STAR TypeQualifierList OldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
        }
        ;

PostfixOldFunctionDeclarator: /** nomerge **/
        ParenIdentifierDeclarator LPAREN { EnterScope(subparser); } IdentifierList { ExitReentrantScope(subparser); } RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
        | LPAREN OldFunctionDeclarator RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
        | LPAREN OldFunctionDeclarator RPAREN PostfixingAbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
        ;

AbstractDeclarator: /** nomerge **/
        UnaryAbstractDeclarator
        {
          DeclBuilder db = getDBAt(subparser,1);
          setTFValue(value,db);
        }
        | PostfixAbstractDeclarator
        {
          DeclBuilder db = getDBAt(subparser,1);
          setTFValue(value,db);
        }
        | PostfixingAbstractDeclarator
        {
          DeclBuilder db = getDBAt(subparser,1);
          setTFValue(value,db);
        }
        ;

PostfixingAbstractDeclarator: /**  nomerge **/
        ArrayAbstractDeclarator
      	{
      	  DeclBuilder db = getDBAt(subparser,1);
      	  setTFValue(value,db);
      	}
        /* | LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN */
        | PostfixingFunctionDeclarator
        {
          DeclBuilder db = getDBAt(subparser,1);
          setTFValue(value,db);
        }
        ;

ParameterTypeListOpt: /** nomerge **/
        /* empty */
        {
          List<Multiverse<Parameter>> result = new LinkedList<Multiverse<Parameter>>();
          setTFValue(value, result);
        }
        | ParameterTypeList
        {
          List<Multiverse<Parameter>> p = getParamAt(subparser,1);
          setTFValue(value,p);
        }
        ;

ArrayAbstractDeclarator: /** nomerge **/
        LBRACK RBRACK
        {
      	  DeclBuilder db = new DeclBuilder();
      	  db.addArray("",false);
          setTFValue(value, db);
        }
        | LBRACK ConstantExpression RBRACK
        {
      	  DeclBuilder db = new DeclBuilder();
          // TODO: support configurable array bound expressions
          Multiverse<StringBuilder> arrayBounds = getSBMVAt(subparser, 2);
          if (arrayBounds.size() == 1) {
          	db.addArray(arrayBounds.get(0).getData().toString());
          } else if (arrayBounds.size() > 1) {
            System.err.println("ERROR: configurable array bounds not yet supported.");
            System.exit(1);
          } else /* arrayBounds.size() < 1 */ {
            System.err.println("FATAL: children of ArrayAbstractDeclarator should not be missing");
            System.exit(1);
          }
          setTFValue(value, db);
	      }
        | ArrayAbstractDeclarator LBRACK ConstantExpression RBRACK
	      {
      	  DeclBuilder db = getDBAt(subparser,4);
          // TODO: support configurable array bound expressions
          Multiverse<StringBuilder> arrayBounds = getSBMVAt(subparser, 2);
          if (arrayBounds.size() == 1) {
          	db.addArray(arrayBounds.get(0).getData().toString());
          } else if (arrayBounds.size() > 1) {
            System.err.println("ERROR: configurable array bounds not yet supported.");
            System.exit(1);
          } else /* arrayBounds.size() < 1 */ {
            System.err.println("FATAL: children of ArrayAbstractDeclarator should not be missing");
            System.exit(1);
          }
          setTFValue(value, db);
	      }
        ;

UnaryAbstractDeclarator: /** nomerge **/
        STAR
        {
          DeclBuilder d = new DeclBuilder();
          d.addPointer();
          setTFValue(value,d);
        }
        | STAR TypeQualifierList
        {
          DeclBuilder d = new DeclBuilder();
          d.addPointer();
          d.addQuals(getTBAt(subparser,1),null);
          setTFValue(value,d);
        }
        | STAR AbstractDeclarator
        {
          DeclBuilder d = getDBAt(subparser,1);
          d.addPointer();
          setTFValue(value,d);
        }
        | STAR TypeQualifierList AbstractDeclarator
        {
      	  DeclBuilder db = getDBAt(subparser,1);
      	  DeclBuilder outter = new DeclBuilder();
      	  outter.addPointer();
      	  outter.addQuals(getTBAt(subparser,2),db);
      	  setTFValue(value,outter);
      	}
        ;

PostfixAbstractDeclarator: /** nomerge **/
        LPAREN UnaryAbstractDeclarator RPAREN
        {
          DeclBuilder d = new DeclBuilder();
          DeclBuilder db = getDBAt(subparser,2);
          d.addDeclBuilder(db);
          setTFValue(value,d);
        } 
        | LPAREN PostfixAbstractDeclarator RPAREN
        {
          DeclBuilder d = new DeclBuilder();
          DeclBuilder db = getDBAt(subparser,2);
          d.addDeclBuilder(db);
          setTFValue(value,d);
        } 
        | LPAREN PostfixingAbstractDeclarator RPAREN
        {
          DeclBuilder d = new DeclBuilder();
          DeclBuilder db = getDBAt(subparser,2);
          d.addDeclBuilder(db);
          setTFValue(value,d);
        } 
        | LPAREN UnaryAbstractDeclarator RPAREN PostfixingAbstractDeclarator
        {
          DeclBuilder d = new DeclBuilder();
          DeclBuilder db = getDBAt(subparser,3);
          d.addDeclBuilder(db);
          DeclBuilder post = getDBAt(subparser,1);
          d.merge(post);
          setTFValue(value,d);
        } 
        ;

// ---------------------------------------------------------------- Statements

Statement:  /** passthrough, complete **/
        LabeledStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | CompoundStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | ExpressionStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | SelectionStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | IterationStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | JumpStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | AssemblyStatement  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

LabeledStatement:  /** complete **/  // ADDED attributes
        IdentifierOrTypedefName COLON AttributeSpecifierListOpt Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression COLON Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression ELLIPSIS ConstantExpression COLON Statement  // ADDED case range
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | DEFAULT COLON Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        ;

/*CompoundStatement:
        LBRACE RBRACE
        | LBRACE DeclarationList RBRACE
        | LBRACE StatementList RBRACE
        | LBRACE DeclarationList StatementList RBRACE
        ;*/

CompoundStatement:  /** complete **/  /* ADDED */
        LBRACE { EnterScope(subparser); } LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 6), getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

LocalLabelDeclarationListOpt: /** complete **/
        /* empty */
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> result = new Multiverse<StringBuilder>();
          result.add(new StringBuilder(""), subparser.getPresenceCondition());
          setTFValue(value, result);
        }
        | LocalLabelDeclarationList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

LocalLabelDeclarationList:  /** list, complete **/
        LocalLabelDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | LocalLabelDeclarationList LocalLabelDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

LocalLabelDeclaration: /** complete **/  /* ADDED */
        __LABEL__ LocalLabelList SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LocalLabelDeclaration");
          System.exit(1);
        }
        ;

LocalLabelList:  /** list, complete **/  // ADDED
        IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        | LocalLabelList COMMA IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        ;

DeclarationOrStatementList:  /** list, complete **/  /* ADDED */
        /* empty */
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> result = new Multiverse<StringBuilder>();
          result.add(new StringBuilder(""), subparser.getPresenceCondition());
          setTFValue(value, result);
        }
        | DeclarationOrStatementList DeclarationOrStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node list = getNodeAt(subparser, 2);
          Node elem = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, list, elem);
          setTFValue(value, product);
        }
        ;

DeclarationOrStatement: /** passthrough, complete **/  /* ADDED */
        DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | NestedFunctionDefinition
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

DeclarationList:  /** list, complete **/
        DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | DeclarationList DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

/*StatementList:
        Statement
        | StatementList Statement
        ;*/

ExpressionStatement:  /** complete **/
        ExpressionOpt SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();

      	  Multiverse<Node> condChildren = getAllNodeConfigs(getNodeAt(subparser, 2), subparser.getPresenceCondition());

      	  /** Iterates through all configurations of the child node */
      	  for (Multiverse.Element<Node> configNode : condChildren) {
      	    Multiverse<StringBuilder> statements = getSBMV(configNode.getData());
      	    StringBuilder sb = new StringBuilder();

      	    /** Iterates through all configurations of the stringbuilder stored in the child node */
      	    for (Multiverse.Element<StringBuilder> statement : statements) {
              sb.append("\nif (" +
              PCtoString(statement.getCondition().and(subparser.getPresenceCondition())) +
              ") {\n" + statement.getData().toString() + ";\n}\n");
              /**
               * NOTE: When writing the "if (PC)",
               * we AND the child node's PC with each stored stringbuilder PC, and
               * add that to the resultant SBMV.
               */
      	    }
      	    sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
      	  }
          setTFValue(value, sbmv);
        }
        ;

SelectionStatement:  /** complete **/
        IF LPAREN Expression RPAREN Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          
          Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, getNodeAt(subparser, 5), getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2));
          Multiverse<StringBuilder> temp = new Multiverse<StringBuilder>();
          temp = sbmv.product(new StringBuilder(" {\n"), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), pc);
          sbmv.destruct();
          sbmv = temp;

          temp = sbmv.product(new StringBuilder("\n}\n "), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          setTFValue(value, sbmv);
        }
        | IF LPAREN Expression RPAREN Statement ELSE Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));

          Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, getNodeAt(subparser, 7), getNodeAt(subparser, 6), getNodeAt(subparser, 5), getNodeAt(subparser, 4));

          Multiverse<StringBuilder> temp = new Multiverse<StringBuilder>();
          temp = sbmv.product(new StringBuilder(" {\n"), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), pc);
          sbmv.destruct();
          sbmv = temp;

          temp = sbmv.product(new StringBuilder("\n}\n "), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          StringBuilder tokenText = new StringBuilder(" ");
          tokenText.append(getNodeAt(subparser, 2).getTokenText());
          temp = sbmv.product(tokenText, pc, SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          temp = new Multiverse<StringBuilder>();
          temp = sbmv.product(new StringBuilder(" {\n"), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), pc);
          sbmv.destruct();
          sbmv = temp;

          temp = sbmv.product(new StringBuilder("\n}\n "), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          setTFValue(value, sbmv);  
        }
        | SWITCH LPAREN Expression RPAREN Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          // TODO: hard-code curly braces to ensure that any rewritings of the statement (node 1),
          // remain inside the scope of the condition.
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 5), getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

IterationStatement:  /** complete **/
        WHILE LPAREN Expression RPAREN Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, getNodeAt(subparser, 5), getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2));
          Multiverse<StringBuilder> temp = new Multiverse<StringBuilder>();
          temp = sbmv.product(new StringBuilder(" {\n"), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;

          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), pc);
          sbmv.destruct();
          sbmv = temp;

          temp = sbmv.product(new StringBuilder("\n}\n "), subparser.getPresenceCondition().presenceConditionManager().newTrue(), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: IterationStatement");
          System.exit(1);
        }
        | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: IterationStatement");
          System.exit(1);
        }
        ;

JumpStatement:  /** passthrough, complete **/
        GotoStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | ContinueStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | BreakStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | ReturnStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
        }
        ;

GotoStatement:  /** complete **/
        GOTO IdentifierOrTypedefName SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        | GOTO STAR Expression SEMICOLON  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        ;

ContinueStatement:  /** complete **/
        CONTINUE SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: ContinueStatement");
          System.exit(1);
        }
        ;

BreakStatement:  /** complete **/
        BREAK SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("WARNING: unsupported semantic action: BreakStatement");
          System.exit(1);
        }
        ;

ReturnStatement:  /** complete **/
        RETURN ExpressionOpt SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

// --------------------------------------------------------------- Expressions

/* CONSTANTS */
Constant: /** passthrough, nomerge **/
        FLOATINGconstant
        {
        	PresenceCondition pc = subparser.getPresenceCondition();
        	Node child = getNodeAt(subparser, 1);
        	Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, child);
          setTFValue(value, sbmv);
        }
        | INTEGERconstant
        {
        	PresenceCondition pc = subparser.getPresenceCondition();
        	Node child = getNodeAt(subparser, 1);
        	Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, child);
          setTFValue(value, sbmv);
        }
        /* We are not including ENUMERATIONConstant here  because  we
        are  treating  it like a variable with a type of "enumeration
        Constant".  */
        | OCTALconstant
        {
        	PresenceCondition pc = subparser.getPresenceCondition();
        	Node child = getNodeAt(subparser, 1);
        	Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, child);
          setTFValue(value, sbmv);
        }
        | HEXconstant
        {
        	PresenceCondition pc = subparser.getPresenceCondition();
        	Node child = getNodeAt(subparser, 1);
        	Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, child);
          setTFValue(value, sbmv);
        }
        | CHARACTERconstant
        {
        	PresenceCondition pc = subparser.getPresenceCondition();
        	Node child = getNodeAt(subparser, 1);
        	Multiverse<StringBuilder> sbmv = getProductOfSomeChildren(pc, child);
          setTFValue(value, sbmv);
        }
        ;

/* STRING LITERALS */
StringLiteralList:  /** list, nomerge **/
                STRINGliteral
                {
                  System.err.println("WARNING: unsupported semantic action: StringLiteralList");
                  System.exit(1);
                }
                | StringLiteralList STRINGliteral
                {
                  System.err.println("WARNING: unsupported semantic action: StringLiteralList");
                  System.exit(1);
                }
                ;


/* EXPRESSIONS */
PrimaryExpression:  /** nomerge, passthrough **/
        PrimaryIdentifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Constant
        {
          // TODO: since you are always creating a new empty multiverse, you could factor that out into cartesianProductWithChild so it has to deal with destructing sbmv
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | StringLiteralList
        {
          System.err.println("WARNING: unsupported semantic action: PrimaryExpression");
          System.exit(1);
        }
        | LPAREN Expression RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PrimaryExpression");
          System.exit(1);
        }
        | StatementAsExpression  // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: PrimaryExpression");
          System.exit(1);
        }
        | VariableArgumentAccess  // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: PrimaryExpression");
          System.exit(1);
        }
        ;

PrimaryIdentifier: /** nomerge **/
        IDENTIFIER
        {
          useIdent(subparser, getNodeAt(subparser, 1));
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)getNodeAt(subparser, 1)).getTokenText());
          //Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          //sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));


          CContext scope = (CContext) subparser.scope;

          // get the renamings from the symtab
          PresenceCondition cond = subparser.getPresenceCondition().presenceConditionManager().newTrue();
          Multiverse<SymbolTable.Entry> entries = scope.get(sb.toString(), cond);
          cond.delRef();

          // convert the renamings to stringbuilders
          Multiverse<StringBuilder> sbmv = entryToStringBuilder.transform(entries);
          entries.destruct();

          setTFValue(value, sbmv);
        }  /* We cannot use a typedef name as a variable */
        ;

VariableArgumentAccess:  /** nomerge **/  // ADDED
        __BUILTIN_VA_ARG LPAREN AssignmentExpression COMMA TypeName RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: VariableArgumentAccess");
          System.exit(1);
        }
        ;

StatementAsExpression:  /** nomerge **/  //ADDED
        LPAREN { EnterScope(subparser); } CompoundStatement { ExitScope(subparser); } RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: StatementAsExpression");
          System.exit(1);
        }
        ;

PostfixExpression:  /** passthrough, nomerge **/
        PrimaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Subscript
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | FunctionCall
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
        }
        | DirectSelection
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
        }
        | IndirectSelection
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
          System.exit(1);
        }
        | Increment
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Decrement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | CompoundLiteral  /* ADDED */
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
}
        ;

Subscript:  /** nomerge **/
        PostfixExpression LBRACK Expression RBRACK
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

FunctionCall:  /** nomerge **/
        PostfixExpression LPAREN RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: FunctionCall");
          callFunction(subparser, getNodeAt(subparser, 3), null);
        }
        | PostfixExpression LPAREN ExpressionList RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: FunctionCall");
          callFunction(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 2));
        }
        ;

DirectSelection:  /** nomerge **/
        PostfixExpression DOT IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: DirectSelection");
          System.exit(1);
        }
        ;

IndirectSelection:  /** nomerge **/
        PostfixExpression ARROW IdentifierOrTypedefName
        {
          System.err.println("WARNING: unsupported semantic action: IndirectSelection");
          System.exit(1);
        }
        ;

Increment:  /** nomerge **/
        PostfixExpression ICR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

Decrement:  /** nomerge **/
        PostfixExpression DECR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

CompoundLiteral:  /** nomerge **/  /* ADDED */
        LPAREN TypeName RPAREN LBRACE InitializerList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: CompoundLiteral");
          System.exit(1);
        }
        ;

ExpressionList:  /** list, nomerge **/
        AssignmentExpression
        {
          System.err.println("WARNING: unsupported semantic action: ExpressionList");
          System.exit(1);
        }
        | ExpressionList COMMA AssignmentExpression
        {
          System.err.println("WARNING: unsupported semantic action: ExpressionList");
          System.exit(1);
        }
        ;

UnaryExpression:  /** passthrough, nomerge **/
        PostfixExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | ICR UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DECR UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | Unaryoperator CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | SIZEOF UnaryExpression
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | SIZEOF LPAREN TypeName RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | LabelAddressExpression  // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | AlignofExpression // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | ExtensionExpression // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | OffsetofExpression // ADDED
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        | TypeCompatibilityExpression  // ADEED
        {
          System.err.println("WARNING: unsupported semantic action: UnaryExpression");
          System.exit(1);
        }
        ;

TypeCompatibilityExpression:  /** nomerge **/
        __BUILTIN_TYPES_COMPATIBLE_P LPAREN TypeName COMMA TypeName RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: TypeCompatibilityExpression");
          System.exit(1);
        }
        ;

OffsetofExpression:  /** nomerge **/
        __BUILTIN_OFFSETOF LPAREN TypeName COMMA PostfixExpression RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: OffsetofExpression");
          System.exit(1);
        }
        ;

ExtensionExpression:  /** nomerge **/
        __EXTENSION__ CastExpression
        {
          System.err.println("WARNING: unsupported semantic action: ExtensionExpression");
          System.exit(1);
        }
        ;

AlignofExpression:  /** nomerge **/
        Alignofkeyword LPAREN TypeName RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: AlignofExpression");
          System.exit(1);
        }
        | Alignofkeyword UnaryExpression
        {
          System.err.println("WARNING: unsupported semantic action: AlignofExpression");
          System.exit(1);
        }
        ;

Alignofkeyword:
        __ALIGNOF__
        {
          System.err.println("WARNING: unsupported semantic action: Alignofkeyword");
          System.exit(1);
        }
        | __ALIGNOF
        {
          System.err.println("WARNING: unsupported semantic action: Alignofkeyword");
          System.exit(1);
        }
        ;

LabelAddressExpression:  /** nomerge  **/  // ADDED
        ANDAND IDENTIFIER
        {
          System.err.println("WARNING: unsupported semantic action: LabelAddressExpression");
          System.exit(1);
        }
        ;

Unaryoperator:
        AND
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | STAR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | PLUS
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | MINUS
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | NEGATE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | NOT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

CastExpression:  /** passthrough, nomerge **/
        UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | LPAREN TypeName RPAREN CastExpression
        {
          System.err.println("WARNING: unsupported semantic action: CastExpression");
          System.exit(1);
        }
        ;

MultiplicativeExpression:  /** passthrough, nomerge **/
        CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | MultiplicativeExpression STAR CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | MultiplicativeExpression DIV CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | MultiplicativeExpression MOD CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

AdditiveExpression:  /** passthrough, nomerge **/
        MultiplicativeExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | AdditiveExpression PLUS MultiplicativeExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | AdditiveExpression MINUS MultiplicativeExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

ShiftExpression:  /** passthrough, nomerge **/
        AdditiveExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          // TODO: don't forget to add a reference whenever you use a presence condition.  this applies to all semantic actions that do this
          setTFValue(value, product);
        }
        | ShiftExpression LS AdditiveExpression
        {
          System.err.println("WARNING: unsupported semantic action: ShiftExpression");
          System.exit(1);
        }
        | ShiftExpression RS AdditiveExpression
        {
          System.err.println("WARNING: unsupported semantic action: ShiftExpression");
          System.exit(1);
        }
        ;

RelationalExpression:  /** passthrough, nomerge **/
        ShiftExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | RelationalExpression LT ShiftExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | RelationalExpression GT ShiftExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | RelationalExpression LE ShiftExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | RelationalExpression GE ShiftExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

EqualityExpression:  /** passthrough, nomerge **/
        RelationalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | EqualityExpression EQ RelationalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | EqualityExpression NE RelationalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

AndExpression:  /** passthrough, nomerge **/
        EqualityExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | AndExpression AND EqualityExpression
        {
          System.err.println("WARNING: unsupported semantic action: AndExpression");
          System.exit(1);
        }
        ;

ExclusiveOrExpression:  /** passthrough, nomerge **/
        AndExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | ExclusiveOrExpression XOR AndExpression
        {
          System.err.println("WARNING: unsupported semantic action: ExclusiveOrExpression");
          System.exit(1);
        }
        ;

InclusiveOrExpression:  /** passthrough, nomerge **/
        ExclusiveOrExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | InclusiveOrExpression PIPE ExclusiveOrExpression
        {
          System.err.println("WARNING: unsupported semantic action: InclusiveOrExpression");
          System.exit(1);
        }
        ;

LogicalAndExpression:  /** passthrough, nomerge **/
        InclusiveOrExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | LogicalAndExpression ANDAND InclusiveOrExpression
        {
          System.err.println("WARNING: unsupported semantic action: LogicalAndExpression");
          System.exit(1);
        }
        ;

LogicalORExpression:  /** passthrough, nomerge **/
        LogicalAndExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | LogicalORExpression OROR LogicalAndExpression
        {
          System.err.println("WARNING: unsupported semantic action: LogicalORExpression");
          System.exit(1);
        }
        ;

ConditionalExpression:  /** passthrough, nomerge **/
        LogicalORExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | LogicalORExpression QUESTION Expression COLON
                ConditionalExpression
        {
          System.err.println("WARNING: unsupported semantic action: ConditionalExpression");
          System.exit(1);
        }
        | LogicalORExpression QUESTION COLON  // ADDED gcc innomerge conditional
                ConditionalExpression
        {
          System.err.println("WARNING: unsupported semantic action: ConditionalExpression");
          System.exit(1);
        }
        ;

AssignmentExpression:  /** passthrough, nomerge **/
        ConditionalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | UnaryExpression AssignmentOperator AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

AssignmentOperator: /** nomerge **/
        ASSIGN
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" = ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | MULTassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" *= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | DIVassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" /= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | MODassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" %= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | PLUSassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" += ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | MINUSassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" -= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | LSassign
        {
          System.err.println("WARNING: unsupported semantic action: AssignmentOperator");
          System.exit(1);
        }
        | RSassign
        {
          System.err.println("WARNING: unsupported semantic action: AssignmentOperator");
          System.exit(1);
        }
        | ANDassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" &= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        | ERassign
        {
          System.err.println("WARNING: unsupported semantic action: AssignmentOperator");
          System.exit(1);
        }
        | ORassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" |= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));
          setTFValue(value, sbmv);
        }
        ;

ExpressionOpt:  /** passthrough, nomerge **/
        /* Nothing */
{
  Multiverse<StringBuilder> s = new Multiverse<StringBuilder>();
  s.add(new StringBuilder(""),subparser.getPresenceCondition());
  setTFValue(value, s);
 
}
        | Expression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        ;

Expression:  /** passthrough, nomerge **/
        AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
        | Expression COMMA AssignmentExpression
        {
          System.err.println("WARNING: unsupported semantic action: Expression");
          System.exit(1);
        }
        ;

ConstantExpression: /** passthrough, nomerge **/
        ConditionalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child);
          setTFValue(value, product);
        }
	      ;

AttributeSpecifierListOpt: /** nomerge **/  // ADDED
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AttributeSpecifierListOpt");
        }
        | AttributeSpecifierList
        {
          System.err.println("WARNING: unsupported semantic action: AttributeSpecifierListOpt");
          System.exit(1);
        }
        ;

AttributeSpecifierList:  /** list, nomerge **/  // ADDED
        AttributeSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: AttributeSpecifierList");
          System.exit(1);
        }
        | AttributeSpecifierList AttributeSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: AttributeSpecifierList");
          System.exit(1);
        }
        ;

AttributeSpecifier: /** nomerge **/  // ADDED
        AttributeKeyword LPAREN LPAREN AttributeListOpt RPAREN RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: AttributeSpecifier");
          System.exit(1);
        }
        ;

AttributeKeyword:   // ADDED
        __ATTRIBUTE
        {
          System.err.println("WARNING: unsupported semantic action: AttributeKeyword");
          System.exit(1);
        }
        | __ATTRIBUTE__
        {
          System.err.println("WARNING: unsupported semantic action: AttributeKeyword");
          System.exit(1);
        }
        ;

AttributeListOpt:   // ADDED
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AttributeListOpt");
        }
        | AttributeList
        {
          System.err.println("WARNING: unsupported semantic action: AttributeListOpt");
          System.exit(1);
        }
        ;

AttributeList:  /** list, nomerge **/  // ADDED
        Word AttributeExpressionOpt
        {
          System.err.println("WARNING: unsupported semantic action: AttributeList");
          System.exit(1);
        }
        | AttributeList COMMA Word AttributeExpressionOpt
        {
          System.err.println("WARNING: unsupported semantic action: AttributeList");
          System.exit(1);
        }
        ;

AttributeExpressionOpt:   // ADDED
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AttributeExpressionOpt");
        }
        | LPAREN RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: AttributeExpressionOpt");
          System.exit(1);
        }
        | LPAREN ExpressionList RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: AttributeExpressionOpt");
          System.exit(1);
        }
        ;

Word:  // ADDED
        IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | AUTO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DOUBLE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | INT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | STRUCT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | BREAK
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | ELSE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | LONG
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | SWITCH
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | CASE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | ENUM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | REGISTER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TYPEDEF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | CHAR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | EXTERN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | RETURN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | UNION
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | CONST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | FLOAT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | SHORT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | UNSIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | CONTINUE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | FOR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | SIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | VOID
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DEFAULT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | GOTO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | SIZEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | VOLATILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | DO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | IF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | STATIC
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | WHILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | ASMSYM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | _BOOL
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | _COMPLEX
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | RESTRICT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ALIGNOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ALIGNOF__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | ASM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ASM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ASM__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ATTRIBUTE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __ATTRIBUTE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __BUILTIN_OFFSETOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __BUILTIN_TYPES_COMPATIBLE_P
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __BUILTIN_VA_ARG
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __BUILTIN_VA_LIST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __COMPLEX__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __CONST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __CONST__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __EXTENSION__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | INLINE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __INLINE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __INLINE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __LABEL__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __RESTRICT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __RESTRICT__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __SIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __SIGNED__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __THREAD
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | TYPEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __TYPEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __TYPEOF__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __VOLATILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        | __VOLATILE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTFValue(value, product);
        }
        ;

// ------------------------------------------------------------------ Assembly

AssemblyDefinition:  /** nomerge **/
        AssemblyExpression SEMICOLON
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyDefinition");
          System.exit(1);
        }
        ;

AssemblyExpression:  /** nomerge **/
        AsmKeyword LPAREN StringLiteralList RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyExpression");
          System.exit(1);
        }
        ;

AssemblyExpressionOpt:  /** nomerge **/
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyExpressionOpt");
        }
        | AssemblyExpression
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyExpressionOpt");
          System.exit(1);
        }
        ;

AssemblyStatement:   /** nomerge **/ // ADDED
        AsmKeyword LPAREN Assemblyargument RPAREN SEMICOLON
        /* gcc>=4.5 */
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyStatement");
          System.exit(1);
        }
        | AsmKeyword GOTO LPAREN AssemblyGotoargument RPAREN SEMICOLON
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyStatement");
          System.exit(1);
        }
        | AsmKeyword TypeQualifier LPAREN Assemblyargument RPAREN SEMICOLON
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyStatement");
          System.exit(1);
        }
        ;

Assemblyargument:  /** nomerge **/  // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON Assemblyclobbers
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyargument");
          System.exit(1);
        }
        | StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyargument");
          System.exit(1);
        }
        | StringLiteralList COLON AssemblyoperandsOpt
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyargument");
          System.exit(1);
        }
        | StringLiteralList
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyargument");
          System.exit(1);
        }
        ;

AssemblyoperandsOpt:  /** nomerge **/  // ADDED
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyoperandsOpt");
        }
        | Assemblyoperands
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyoperandsOpt");
          System.exit(1);
        }
        ;

Assemblyoperands:  /** list, nomerge **/  // ADDED
        Assemblyoperand
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyoperands");
          System.exit(1);
        }
        | Assemblyoperands COMMA Assemblyoperand
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyoperands");
          System.exit(1);
        }
        ;

Assemblyoperand:  /** nomerge **/  // ADDED
                             StringLiteralList LPAREN Expression RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyoperand");
          System.exit(1);
        }
        | LBRACK Word RBRACK StringLiteralList LPAREN Expression RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyoperand");
          System.exit(1);
        }
        ;

AssemblyclobbersOpt:  /** nomerge **/ // ADDED
        /* empty */
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyclobbersOpt");
        }
        | Assemblyclobbers
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyclobbersOpt");
          System.exit(1);
        }
        ;

Assemblyclobbers:  /** nomerge **/  // ADDED
        StringLiteralList
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyclobbers");
          System.exit(1);
        }
        | Assemblyclobbers COMMA StringLiteralList
        {
          System.err.println("WARNING: unsupported semantic action: Assemblyclobbers");
          System.exit(1);
        }
        ;

AssemblyGotoargument:  /** nomerge **/ // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON AssemblyclobbersOpt COLON AssemblyJumpLabels
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyGotoargument");
          System.exit(1);
        }
        ;

AssemblyJumpLabels:  /** nomerge **/ // ADDED
        Identifier
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyJumpLabels");
          System.exit(1);
        }
        | AssemblyJumpLabels COMMA Identifier
        {
          System.err.println("WARNING: unsupported semantic action: AssemblyJumpLabels");
          System.exit(1);
        }
        ;

AsmKeyword:   // ADDED
        ASM
        {
          System.err.println("WARNING: unsupported semantic action: AsmKeyword");
          System.exit(1);
        }
        | __ASM
        {
          System.err.println("WARNING: unsupported semantic action: AsmKeyword");
          System.exit(1);
        }
        | __ASM__
        {
          System.err.println("WARNING: unsupported semantic action: AsmKeyword");
          System.exit(1);
        }
        ;

%%

// TUTORIAL: this section of the grammar gets copied into the
// resulting parser, specifically the CActions.java class


/**
   This is just a constant string name for a property used to assign
   semantic values that are type builders.
 */
private static final String STRING = "xtc.String";
private static final String TRANSFORMATION = "transformation";

private void setTFValue(Object node, Object value) {
  ((Node)node).setProperty(TRANSFORMATION, value);
}


/** 
 * TypeAndDeclInitList stores type information,
 * with a list of declarations and their optional initializing statements.
 * This is used as the semantic value for declaring lists. 
 * The parent of a declaring list should construct the transformation output using the stored information.
 * 
 */
private static class TypeAndDeclInitList {
	/** The type field */
  private TypeBuilderMultiverse type;
  /** The declaration and initializer list */
  private List<DeclAndInit> declAndInitList;

	/**
	* This constructor creates a TypeAndDeclInitList.
	*
	* @param tb The type information.
	* @param declAndInits The declaration and initializer list.
	*/
  private TypeAndDeclInitList(TypeBuilderMultiverse tb, DeclBuilder decl, Multiverse<StringBuilder> init) {
    type = tb;
    DeclAndInit declAndInit = new DeclAndInit(decl, init);
    declAndInitList = new LinkedList<DeclAndInit>();
    declAndInitList.add(declAndInit);
  }

  /** The copy constructor */
  private TypeAndDeclInitList(TypeAndDeclInitList TBDBList) {
  	type = new TypeBuilderMultiverse(TBDBList.type);
  	declAndInitList = new LinkedList<DeclAndInit>(TBDBList.declAndInitList);
  }

  /** Adds a declaration and an optional initializer to the list */
  private void addDeclAndInit(DeclBuilder decl, Multiverse<StringBuilder> init) {
    DeclAndInit declAndInit = new DeclAndInit(decl, init);
  	declAndInitList.add(declAndInit);
  }

  /** 
	 * DeclAndInit stores the declaration and initializer statement information.
	 */
	private static class DeclAndInit {
		/** The declaration field */
		private DeclBuilder decl;
		/** The initializer statement field*/
	  private Multiverse<StringBuilder> initializerSBMV;

  	/** 
	   * Constructor for declarations with an initializer statement.
	   * @param db The declaration information.
	   * @param initializer The initializer statement.
	   */
	  private DeclAndInit(DeclBuilder db, Multiverse<StringBuilder> initializer) {
	  	decl = db;
	  	initializerSBMV = initializer;
	  }
	}
}

private TypeAndDeclInitList getTBDBList(Object node) {
  return (TypeAndDeclInitList)((Node)node).getProperty(TRANSFORMATION);
}

private TypeAndDeclInitList getTBDBListAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (TypeAndDeclInitList)getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private Multiverse<StringBuilder> getSBMV(Object node) {
  return (Multiverse<StringBuilder>)((Node)node).getProperty(TRANSFORMATION);
}

private Multiverse<StringBuilder> getSBMVAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (Multiverse<StringBuilder>) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private TypeBuilderMultiverse getTB(Object node) {
  return (TypeBuilderMultiverse)((Node)node).getProperty(TRANSFORMATION);
}

private TypeBuilderMultiverse getTBAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (TypeBuilderMultiverse) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private DeclBuilder getDB(Object node) {
  return (DeclBuilder)((Node)node).getProperty(TRANSFORMATION);
}

private DeclBuilder getDBAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (DeclBuilder) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private List<Multiverse<Parameter>> getParamAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (List<Multiverse<Parameter>>) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private List<Multiverse<VariableT>> getFieldAt(Subparser subparser, int component) {
  return (List<Multiverse<VariableT>>) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
}

private void setCPC(Object value, String CPC) {
  // value should be not null and should be a Node type
  setCPC((Node) value, CPC);
}

private void setCPC(Node value, String CPC) {
  // value should be not null and should be a Node type
  value.setProperty("C_PC", CPC);
}

private String getCPC(Subparser subparser, int component) {
  return (String) getNodeAt(subparser, component).getProperty("C_PC");
}

private String getCPC(Node n) {
  return (String) n.getProperty("C_PC");
}

/**
 * Creates the cartesian product of any number of children nodes' SBMVs.
 * @param pc A PresenceCondition.
 * @param children Nodes whose SBMVs should be combined.
 * @return An SBMV containing the product of the passed-in childrens' SBMVs.
 */
private Multiverse<StringBuilder> getProductOfSomeChildren(PresenceCondition pc, Node...children) {
  // NOTE: Nodes must be passed-in in the order that their SBMV stringbuilders should be concatenated.
  Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
  Multiverse<StringBuilder> temp;
  for (Node child : children) {
    if (child.isToken()) {
      StringBuilder tokenText = new StringBuilder(" ");
      tokenText.append(child.getTokenText());
      temp = sbmv.product(tokenText, pc, SBCONCAT);
      sbmv.destruct();
      sbmv = temp;
    } else { 
      temp = cartesianProductWithChild(sbmv, child, pc);
      sbmv.destruct();
      sbmv = temp;
    }
  }
  return sbmv;
}

/**
 * All configurations of this node are then returned in a multiverse.
 * Traverses all nested static choice nodes until non-static choice nodes are reached.
 * @param node The node to get the configurations of.
 * @param presenceCondition The presence condition associated with node.
 * @return A multiverse containing all configurations of the passed-in node.
 */
Multiverse<Node> getAllNodeConfigs(Node node, PresenceCondition presenceCondition) {
  Multiverse<Node> allConfigs = new Multiverse<Node>();

  if (node instanceof GNode && ((GNode) node).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
    PresenceCondition pc = null;
    for (Object child : node) {

      if (child instanceof PresenceCondition) {
        pc = (PresenceCondition)child;
      } else if (child instanceof Node) {
        // assumes that all static choice nodes are mutually exclusive
        Multiverse<Node> someChildren = getAllNodeConfigs((Node)child, pc);
        allConfigs.addAll(someChildren);
        someChildren.destruct();
      } else {
        System.err.println("unsupported AST child type in getNodeMultiverse");
        System.exit(1);
      }
    }

  } else {
    // assumes that if it isn't a static choice node, then it must be a "normal" node
    allConfigs.add(node, presenceCondition);
  }
  // TODO: manage memory
  return allConfigs;
}

/**
 * Takes the cartesian product of the current node's SBMV with one of its children SBMVs.
 * @param sbmv A multiverse that possibly contains the configurations of child's siblings.
 * @param child The child of the current node.
 * @param presenceCondition The presence condition associated with the current node.
 * @return A multiverse containing all configurations of the passed-in node.
 */
Multiverse<StringBuilder> cartesianProductWithChild(Multiverse<StringBuilder> sbmv, Node child, PresenceCondition presenceCondition) {
  if (sbmv == null || child == null)
    return null;
  sbmv = new Multiverse<StringBuilder>(sbmv); // copies the passed-in sbmv because the caller destructs it.
  // getAllNodeConfigs traverses all nested static choice nodes until they reach a regular node
  // and then gets all configurations of that node
  Multiverse<Node> allConfigs = getAllNodeConfigs(child, presenceCondition);
  for (Multiverse.Element<Node> childNode : allConfigs) {
	    Multiverse<StringBuilder> childSBMV = getSBMV(childNode.getData());
	    Multiverse<StringBuilder> temp = sbmv.product(childSBMV, SBCONCAT);
	    sbmv.destruct();
	    sbmv = temp;
  }

  return sbmv;
}

final static Multiverse.Operator<StringBuilder> SBCONCAT = (sb1, sb2) -> {
  StringBuilder newsb = new StringBuilder();
  newsb.append(sb1);
  newsb.append(sb2);
  return newsb;
};

final Multiverse.Transformer<SymbolTable.Entry, StringBuilder> entryToStringBuilder = new Multiverse.Transformer<SymbolTable.Entry, StringBuilder>() {
  StringBuilder transform(SymbolTable.Entry from) {
    return new StringBuilder(from.getRenaming());
  }
};

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
private SymbolTable functionTable;

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
  this.functionTable = new SymbolTable();
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
public SymbolTable getFunctionTable() {
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

private static void setString(Object value, String s) {
  ((Node) value).setProperty(STRING, s);
}

private String getStringAtNode(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (String) getNodeAt(subparser, component).getProperty(STRING);
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
  //System.out.println(typespec.toString() + declarator.toString());
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

public void bindIdent(Subparser subparser, TypeBuilderMultiverse typespec, DeclBuilder declarator)
{
	bindIdent(subparser, typespec, declarator, null);
}

public void bindIdent(Subparser subparser, TypeBuilderMultiverse typespec, DeclBuilder declarator, STField alsoSet) {
  /*
    for this to properly work, we will need to pull the specific presenceCondition for
    each individual TypeBuilderUnit. More or less the actions that were previously taken should take place
    multiple times now.
   */
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  CContext scope = (CContext) subparser.scope;

  String ident = declarator.getID();

  for (Element<TypeBuilderUnit> elem : typespec){
    if (languageStatistics) {
      if (elem.getData().isTypedef()) {
        Location location = subparser.lookahead.token.syntax.getLocation();
        System.err.println(String.format("typedef %s %s", ident, location));
      }
    }

    if (showErrors) {
      System.err.println("bind: " + ident + " " + Boolean.toString(elem.getData().isTypedef()));
    }
    if (debug) {
      System.err.println("def: " + ident + " " + alsoSet);
    }
    STField field = elem.getData().isTypedef() ? STField.TYPEDEF : STField.IDENT;
    scope.getSymbolTable().setbool(ident, field, true, elem.getCondition());
    if (null != alsoSet) {
      scope.getSymbolTable().setbool(ident, alsoSet, true,elem.getCondition());
    }

  }
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

    FunctionT function = getParamTypes(parms);

    function.setResult(type);
    type = function;

  } else {
    if (debug) {
      System.err.println("TODO support absdeclarator " + absdeclarator.getName());
    }
  }

  return type;
}

private static FunctionT getParamTypes(Node parms) {
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
            /*           System.exit(1); */
          }
          notandnot.delRef();
        }
        if (contradiction) {
          System.err.print("invalid config invalidated by contradiction " + name + " at " + ident.getLocation());
        } else if (satWithKconfig) {
          PresenceCondition sat = andnot.satOne();
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
          sat.delRef();
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
        PresenceCondition sat = andnot.satOne();
        System.err.println("found invalid configuration on function call " + name + " at " + fun.getLocation() + " config " + sat);        sat.delRef();
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

private static String SPECS = "xtc.lang.cpp.Specifiers";

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
 * This method adds all given declarations to the symbol table.  It
 * goes through each element of the TypeBuilderMultiverse, completing
 * the type with the given DeclBuilder.
 *
 * @param presenceCondition current presence condition of the subparser
 * @param scope current scope of the subparser 
 * @param typebuilder A Multiverse of type specifier objects.
 * @param declbuidler An object representing the declarator.
 */
private void addDeclsToSymTab(PresenceCondition presenceCondition, CContext scope, TypeBuilderMultiverse typebuilder, DeclBuilder declbuilder) {
  if (typebuilder == null || declbuilder == null ) {
    System.err.println("ERROR: null typebuilder or declbuilder");
    System.exit(1);
  }

  // get the list of parameters if it's a function declarator
  Multiverse<List<Parameter>> parms = null;
  if (declbuilder.isFunction()) {
    parms = declbuilder.getParams(presenceCondition);
  }

  // loop through each configuration of the type specifier, adding the
  // declaration to the symtab
  for (Element<TypeBuilderUnit> elem : typebuilder) {

    TypeBuilderUnit t = elem.getData();

    if (!isTypeDeclValid(t, declbuilder)) {
      PresenceCondition condition = presenceCondition.and(elem.getCondition());
      scope.getSymbolTable().putError(declbuilder.getID(), condition);
      condition.delRef();
    } else {

      // combine the type spec and declarator into a complete type
      DeclBuilder completedecl = new DeclBuilder(declbuilder);
      completedecl.addType(t.toType());

      if (! declbuilder.isFunction()) {
        // bind the symbol name to the type under the current presence condition
        PresenceCondition condition = presenceCondition.and(elem.getCondition());
        putEntry(scope, declbuilder.getID(), completedecl.toType(), condition);
        condition.delRef();

      } else {  // function types
        // go through each combination of parameters, adding each
        // variation of the function declarator to the symtab
        for(Element<List<Parameter>> parmelem : parms) {
          if (!validateParamList(parmelem.getData())) {
            PresenceCondition condition = presenceCondition.and(parmelem.getCondition());
            scope.getSymbolTable().putError(declbuilder.getID(), condition);
            condition.delRef();
          }
          PresenceCondition condition = parmelem.getCondition().and(elem.getCondition());

          if (parmelem.getData().size() == 0) {  // function has no parameters
            Type funcType = new FunctionT(completedecl.toType());
            putEntry(scope, declbuilder.getID(), funcType, condition);
          } else {  // function has parameters
            List<Type> parmlist = new LinkedList<Type>();

            // get list of parameter types
            for (Parameter p : parmelem.getData()) {
              if(! p.isEllipsis()) {
                parmlist.add(p.getType());
              }
            }

            Type funcType = new FunctionT(completedecl.toType(),
                                          parmlist,
                                          parmelem.getData().get(parmelem.getData().size() - 1).isEllipsis());
            putEntry(scope, declbuilder.getID(), funcType, condition);
          }

          condition.delRef();
        }
      }
    }
  }
}

/**
 * This method adds all given declarations to the symbol table, with
 * the knowledge that all decls are SUE types.  It goes through each 
 * element of the TypeBuilderMultiverse, completing
 * the type with the given DeclBuilder.
 *
 * @param presenceCondition current presence condition of the subparser
 * @param scope current scope of the subparser
 * @param typebuilder A Multiverse of type specifier objects.
 * @param declbuidler An object representing the declarator.
 */
private void addSUEDeclsToSymTab(PresenceCondition presenceCondition, CContext scope, TypeBuilderMultiverse typebuilder, DeclBuilder declbuilder) {
  if (typebuilder == null || declbuilder == null ) {
    System.err.println("ERROR: null typebuilder or declbuilder");
    System.exit(1);
  }
  
  // get the list of parameters if it's a function declarator
  Multiverse<List<VariableT>> fields = null;
  fields = declbuilder.getFields(presenceCondition);
  
  // loop through each configuration of the type specifier, adding the
  // declaration to the symtab
  for (Element<TypeBuilderUnit> elem : typebuilder) {

    TypeBuilderUnit t = elem.getData();

    if (!isTypeDeclValid(t, declbuilder)) {
      PresenceCondition condition = presenceCondition.and(elem.getCondition());
      scope.getSymbolTable().putError(declbuilder.getID(), condition);
      condition.delRef();
    } else {

      // combine the type spec and declarator into a complete type
      DeclBuilder completedecl = new DeclBuilder(declbuilder);
      completedecl.addType(t.toType());

      if (! declbuilder.isFunction()) {
        // bind the symbol name to the type under the current presence condition
        PresenceCondition condition = presenceCondition.and(elem.getCondition());
        putEntry(scope, declbuilder.getID(), completedecl.toType(), condition);
        condition.delRef();

      } else {  // function types
        // go through each combination of parameters, adding each
        // variation of the function declarator to the symtab
        for(Element<List<VariableT>> varelem : fields) {
          if (!validateFieldList(varelem.getData())) {
            PresenceCondition condition = presenceCondition.and(varelem.getCondition());
            scope.getSymbolTable().putError(declbuilder.getID(), condition);
            condition.delRef();
          }
          PresenceCondition condition = varelem.getCondition().and(elem.getCondition());
          
          Type structType = new StructT(declbuilder.getID(), varelem.getData());
          putEntry(scope, declbuilder.getID(), structType, condition);
          
          condition.delRef();
        }
      }
    }
  }
}

private Multiverse<SymbolTable.Entry> getTypeOfTypedef(Subparser subparser, String typeName)
{
  /* Multiverse<SymbolTable.Entry> foundType = ((CContext)subparser.scope).getMappings(typeName, subparser.getPresenceCondition()); */
  Multiverse<SymbolTable.Entry> foundType = ((CContext)subparser.scope).get(typeName, subparser.getPresenceCondition());
  return foundType;
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

private Multiverse<Node> getNodeMultiverse(Node node, PresenceConditionManager presenceConditionManager) {
  Multiverse<Node> mv = new Multiverse<Node>();

  if (node instanceof GNode
      && ((GNode) node).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
    PresenceCondition childCondition = null;
    for (Object bo : node) {
      if (bo instanceof PresenceCondition) {
        childCondition = (PresenceCondition) bo;
      } else if (bo instanceof Node) {
        Node childNode = (Node) bo;
        mv.add(childNode, childCondition);
      } else {
        System.err.println("unsupported AST child type in getNodeMultiverse");
        System.exit(1);
      }
    }
  } else {
    mv.add(node, presenceConditionManager.newTrue());
  }

  return mv;
}

public HashMap<String, String> boolVarRenamings = new HashMap<String, String>();
private HashMap<String, String> BoolExprs = new HashMap<String, String>();

/** Takes a presence condition and generates a valid C string for conditionals */
public String PCtoString(PresenceCondition cond) {
 List allsat = (List) cond.getBDD().allsat();
 ArrayList<String> currentExprs;
 String CBoolExpr;
 StringBuilder sb = new StringBuilder();
 boolean firstTerm = true;
 boolean firstTermOuter = true;

 if (cond.getBDD().isOne()) {
   return "1";
 } else if (cond.getBDD().isZero()) {
   return "0";
 }

 for (Object o : allsat) {
   if (!firstTermOuter)
     sb.append(" || ");
   firstTermOuter = false;
   currentExprs = getBoolExprs((byte[]) o, cond);
   firstTerm = true;
   for (String CPPBoolExpr : currentExprs) {
     if (!firstTerm)
       sb.append(" && ");
     firstTerm = false;
     if (BoolExprs.isEmpty() || !BoolExprs.containsKey(CPPBoolExpr)) {
       /** generates a new C boolean expression with hashcode appended, then adds it to hashmap, then returns it */
       CBoolExpr = generateBoolExpr(CPPBoolExpr);
       BoolExprs.put(CPPBoolExpr, CBoolExpr);
       sb.append(CBoolExpr);
     } else /* if (BoolExprs.containsKey(CPPBoolExpr)) */ {
       CBoolExpr = BoolExprs.get(CPPBoolExpr);
       sb.append(CBoolExpr);
     }
   }
 }
 return sb.toString();
}

/** returns a list of every expression in the BDD */
public ArrayList<String> getBoolExprs(byte[] sat, PresenceCondition cond) {
 ArrayList<String> allExprs = new ArrayList<String>();
 for (int i = 0; i < sat.length; i++) {
   if (sat[i] == 1) {
     /** builds up a list of the (CPP) boolean expressions within the PresenceCondition */
     allExprs.add(cond.presenceConditionManager().getVariableManager().getName(i));
   } else if (sat[i] == 0) {
     allExprs.add("!" + cond.presenceConditionManager().getVariableManager().getName(i));
   }
 }
 return allExprs;
}

/** Returns a new (valid C) boolean expression, with hashcode appended */
public String generateBoolExpr(String CPPBoolExpr) {
 StringBuilder sb = new StringBuilder();
 boolean falseExpr = false;
 boolean definedExpr = false;

 /** need to remove the '!' character from the string, so that it doesn't change the hashcode (then append it later) */
 if (CPPBoolExpr.contains("!")) {
   falseExpr = true;
   sb.append(CPPBoolExpr);

   /** if there is a '!' character, it will be at the 0th position of sb */
   sb.deleteCharAt(0);
   CPPBoolExpr = sb.toString();
   sb.setLength(0);
 }

 /** need to remove "defined" from the string, so that it doesn't affect the hashcode (then append it later) */
 if (CPPBoolExpr.contains("defined")) {
   definedExpr = true;
   sb.append(CPPBoolExpr);

   /** if the expression is a "defined" expression, it will be in the form (defined <>)
    *  note that there will not be a '!' character by this point.
    */
   for (int i = 0; i <= 7; i++)
     sb.deleteCharAt(1);

   /** removes parentheses */
   sb.deleteCharAt(0);
   sb.deleteCharAt(sb.length() - 1);

   CPPBoolExpr = sb.toString();
   sb.setLength(0);
 }

 sb.append("_C_");
 sb.append(CPPBoolExpr.hashCode());

 if (sb.charAt(3) == '-')
   sb.replace(3, 4, "n"); /** replaces the '-' with 'n' */

 if (!boolVarRenamings.containsKey(CPPBoolExpr)) {
   boolVarRenamings.put(CPPBoolExpr, sb.toString());
}
 sb.setLength(0);

 if (falseExpr)
   sb.append("!");

 sb.append("_C_");
 sb.append(CPPBoolExpr.hashCode());

 if (definedExpr)
   sb.append("_DEFINED");

 /** the expression cannot have a '-' character in it (because it would evaluate as subtraction) */
 if (falseExpr) {
   /** if the expression is false, then the '-' will come later in the string due to the additional '!' character */
   if (sb.charAt(4) == '-') {
     sb.replace(4, 5, "n"); /** replaces the '-' with 'n' */
   }
 } else {
   if (sb.charAt(3) == '-') {
     sb.replace(3, 4, "n"); /** replaces the '-' with 'n' */
   }
 }

 return sb.toString();
}

private boolean isTypeDeclValid(TypeBuilderUnit t, DeclBuilder d)
{
  if (!t.getIsValid() || !d.getIsValid()) {
    return false;
  }
  if (t.getIsVoid() && !t.isTypedef() && (!d.isPointer() && !d.isFunction())) {
    return false;
  }
  if (t.getIsInline() && !d.isFunction()){
    return false;
  }
  return true;
}

protected static C cOps = new C();

/**
   * When a value is to be added to the symbol table, duplications are allowed
   * if they have the same type and in a global scope. If the parent is not null,
   * the scope is not global and the value is added normally. If the identifier
   * is not in the table, then it can't be a redeclaration and is added normally.
   * Otherwise, the limited scope is checked, in an undeclared match, the value is added
   * in error or same type matching, nothing is done, and in a different type match
   * an error is added.
   *
   * @param ident original name of the declaration
   * @param putEntry type to be added to the symbol table
   * @param putCond condition of the declaration being added
   */
public void putEntry(CContext scope, String ident, Type putEntry, PresenceCondition putCond)
{
  SymbolTable s = scope.getSymbolTable();
  
  Multiverse<SymbolTable.Entry> curMV = s.get(ident, putCond);

  //if the scope is global but no entry exists for the ident, it is fine
  if (curMV == null) {
    s.put(ident, putEntry, putCond);
    return;
  }
  //otherwise, we need to remove intersection with pre-definitions with the same type since these are valid
  //removing the intersection should be valid, as even if that intersection would cause an error with another
  //entry, that error should already exist in the table
  for (Element<SymbolTable.Entry> e : curMV) {
      
    Type t = e.getData().getType();
    PresenceCondition p = e.getCondition();
    p.addRef();
    if (e.getData() == SymbolTable.UNDECLARED) {
      s.put(ident, putEntry, p);
    }
    else if (e.getData() == SymbolTable.ERROR) {
      //do nothing
    }
    else if (!cOps.equal(putEntry, t)) {
      s.putError(ident, p);
    }
    else if (cOps.equal(putEntry, t) && !scope.isGlobal()) {
      s.putError(ident, p);
    }
    else if (cOps.equal(putEntry, t) && scope.isGlobal()) {
      //do nothing
    }
    else {
      //should never happen
      System.err.println("Should never happen");
      System.exit(1);
    }
    
    p.delRef();
  }
  curMV.destruct();
}

/**
 * Returns if the provided list is a valid Parameter list.
 * If there is only one entry, and it is void, then the list
 * is acceptable and should proceed as an empty list. Otherwise
 * if any Parameter in the list is not valid({@link xtc.lang.cpp.Parameter#isValidType()})
 * then the list is invalid and false is returned.
 *
 * @param lp List of Parameters to be checked for validity
 * @return if the list "lp" is valid
 */
boolean validateParamList(List<Parameter> lp)
{
  if (lp.size() == 1 && lp.get(0).isVoid()) {
    lp.remove(0);
    return true;
  }
  
  for (Parameter p : lp) {
    if (!p.isValidType()) {
      return false;
    }
  }
  return true;
}

/**
 * Returns if the provided list is a valid Field list.
 *
 * @param lp List of Parameters to be checked for validity
 * @return if the list "lp" is valid
 */
boolean validateFieldList(List<VariableT> lv)
{
  /*
  for (VariableT v : lv) {
    if (!p.isValidType()) {
      return false;
    }
  }
  */
  return true;
}


// ---------- Declarators

/* private static String DECL = "xtc.lang.cpp.Declarator"; */

/* private static String NAME = "xtc.lang.cpp.Name"; */

/* private static void setDecl(Object n, Type type) { */
/*   ((Node) n).setProperty(DECL, type); */
/* } */

/* private static Type getDecl(Object n) { */
/*   return ((Type) ((Node) n).getProperty(DECL)); */
/* } */

/*private static void setName(Object n, String name) { */
/*   ((Node) n).setProperty(NAME, name); */
/* } */

/* private static String getName(Object n) { */
/*   return ((String) ((Node) n).getProperty(NAME)); */
/* }*/

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
