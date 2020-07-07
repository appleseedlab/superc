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
        | ExternalDeclarationList ExternalDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          System.err.println("before");
          Node child1 = getNodeAt(subparser, 2);
          Node child2 = getNodeAt(subparser, 1);
          System.err.println("child1 " + child1);
          System.err.println("child2 " + child2);
          System.err.println("getSBMV(child1) " + getSBMV(child1));
          System.err.println("getSBMV(child2) " + getSBMV(child2));
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child2, child1);
          System.err.println("after");
          System.err.println("product " + product);
          setTFValue(value, product);
        }
        ;

ExternalDeclaration:  /** passthrough, complete **/
        FunctionDefinitionExtension
        {
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | AssemblyDefinition
        {
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | EmptyDefinition
        {
          System.err.println("ERROR: unsupported construct: ExternalDeclaration");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        ;

EmptyDefinition:  /** complete **/
        SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> result = new Multiverse<StringBuilder>();
          // TODO: should this use the current presence condition, i.e., subparser.getPresenceCondition()
          result.add(new StringBuilder("; "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true));
          setTFValue(value, result);
        }
        ;

FunctionDefinitionExtension:  /** passthrough, complete **/  // ADDED
        FunctionDefinition
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          Node child;
          System.err.println("WARNING: skipping over transformation code at some nodes in FunctionDefinition.");
          // TODO: uncomment these lines once FunctionPrototype sets an SBMV.
          //child = getNodeAt(subparser, 6);
          //temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          //sbmv.destruct();
          child = getNodeAt(subparser, 3);
          temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          sbmv.destruct();
          setTFValue(value, temp);
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | DeclarationSpecifier     IdentifierDeclarator
        {
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          addMapping(subparser,type,decl);
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

          addMapping(subparser,type,decl);
  	      List<Type> typeList = type.toType();
  	      if (typeList.size() == 1)
  		      sb.append(typeList.get(0) + " ");
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
          addMapping(subparser,type,decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addMapping(subparser,type,decl);
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
          addMapping(subparser,type,decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addMapping(subparser,type,decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addMapping(subparser,type,decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          TypeBuilderMultiverse type = getTBAt(subparser, 2);
          DeclBuilder decl = getDBAt(subparser, 1);
          addMapping(subparser,type,decl);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

FunctionOldPrototype:  /** nomerge **/
        OldFunctionDeclarator
        {
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          System.err.println("declaration is setting: " + product);
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
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          Node child;
          child = getNodeAt(subparser, 3);
          temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          sbmv.destruct();
          setTFValue(value, temp);
        }
        | SUETypeSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          Node child;
          child = getNodeAt(subparser, 3);
          temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          sbmv.destruct();
          setTFValue(value, temp);
        }
        | DeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          Node child;
          child = getNodeAt(subparser, 3);
          temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          sbmv.destruct();
          setTFValue(value, temp);
        }
        | DefaultDeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          Node child;
          child = getNodeAt(subparser, 3);
          temp = cartesianProductWithChild(sbmv, child, subparser.getPresenceCondition());
          sbmv.destruct();
          setTFValue(value, temp);
        }
        ;

/* Note that if a typedef were  redeclared,  then  a  declaration
   specifier must be supplied */

DefaultDeclaringList:  /** nomerge **/  /* Can't  redeclare typedef names */
        DeclarationQualifierList IdentifierDeclarator
        {

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
      	  TypeBuilderMultiverse type = getTBAt(subparser, 5);
      	  DeclBuilder decl = getDBAt(subparser, 4);
          System.err.println(decl.toString() + " " + type.toString());
          addMapping(subparser, type, decl);
      	  saveBaseType(subparser, getNodeAt(subparser, 5));
          bindIdent(subparser, getTBAt(subparser, 5), getDBAt(subparser, 4));
        }
        | TypeSpecifier Declarator AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
      	  DeclBuilder decl = getDBAt(subparser, 4);
      	  TypeBuilderMultiverse type = getTBAt(subparser, 5);
      	  saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, type, decl);

          String oldIdent = decl.identifier;
          System.err.println(decl.toString() + " " + type.toString());
          Multiverse<SymbolTable.Entry> unis = addMapping(subparser, type, decl);
          List<StringBuilder> renamings = getRenamings(unis);
      	  Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          StringBuilder sb = new StringBuilder();

          /** writes declarations of renamed variables */
      	  for (StringBuilder renaming : renamings)
      	  {
      	    decl.identifier = renaming.toString();
      	    List<Type> typeList = type.toType();
      	    if (typeList.size() == 1) {
      	      if (typeList.get(0).getClass().getName().equals("xtc.type.TypedefT"))
      	        System.err.println("WARNING: typedef transformations not yet supported.");
      	      sb.append("\n" + typeList.get(0) + " " + decl + ";" + " /* renamed from " + oldIdent + " */\n");
      	    } else {
      	      System.err.println("ERROR: Configurable typedefs not yet supported.");
      	      // System.exit(1);
    	      }
        	}

          // TODO: handle AttributeSpecifierListOpt

          /** hoists and writes initializing statements using the renamed variables */
          Multiverse<StringBuilder> childSBMV = getSBMVAt(subparser, 1);
          if (childSBMV != null)
            for (Element<SymbolTable.Entry> u : unis)
              for (Element<StringBuilder> sbelem : childSBMV)
                sb.append("\nif (" + PCtoString(u.getCondition().and(sbelem.getCondition())) + ") {\n" +
                         (new StringBuilder(u.getData().getRenaming())).toString() +
                         sbelem.getData() + ";" +
                         "\n}\n");

          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator
        {
          System.err.println("WARNING: unsupported semantic action: DeclaringList");
          System.exit(1);
          // reuses saved base type
	        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          System.err.println("WARNING: unsupported semantic action: DeclaringList");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: ConstQualifier");
          System.exit(1);
        }
        | __CONST
        {
          System.err.println("WARNING: unsupported semantic action: ConstQualifier");
          System.exit(1);
        }
        | __CONST__
        {
          System.err.println("WARNING: unsupported semantic action: ConstQualifier");
          System.exit(1);
        }
        ;

VolatileQualifier:   // ADDED
        VOLATILE
        {
          System.err.println("WARNING: unsupported semantic action: VolatileQualifier");
          System.exit(1);
        }
        | __VOLATILE
        {
          System.err.println("WARNING: unsupported semantic action: VolatileQualifier");
          System.exit(1);
        }
        | __VOLATILE__
        {
          System.err.println("WARNING: unsupported semantic action: VolatileQualifier");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: FunctionSpecifier");
          System.exit(1);
        }
        | __INLINE
        {
          System.err.println("WARNING: unsupported semantic action: FunctionSpecifier");
          System.exit(1);
        }
        | __INLINE__
        {
          System.err.println("WARNING: unsupported semantic action: FunctionSpecifier");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: SUETypeSpecifier");
          System.exit(1);
        }
        | TypeQualifierList ElaboratedTypeName
        {
          System.err.println("WARNING: unsupported semantic action: SUETypeSpecifier");
          System.exit(1);
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
    	    TypeBuilderMultiverse storage = new TypeBuilderMultiverse("typedef", subparser.getPresenceCondition());
    	    setTFValue(value, storage);
              	    getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF;
    	  }
        | EXTERN
  	    {
  	      TypeBuilderMultiverse storage = new TypeBuilderMultiverse("extern", subparser.getPresenceCondition());
  	      setTFValue(value, storage);
            	      getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN;
  	    }
        | STATIC
  	    {
  	      TypeBuilderMultiverse storage = new TypeBuilderMultiverse("static", subparser.getPresenceCondition());
  	      setTFValue(value, storage);
            	      getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC;
  	    }
        | AUTO
  	    {
  	      TypeBuilderMultiverse storage = new TypeBuilderMultiverse("auto", subparser.getPresenceCondition());
  	      setTFValue(value, storage);
            	      getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO;
  	    }
        | REGISTER
  	    {
  	      TypeBuilderMultiverse storage = new TypeBuilderMultiverse("register", subparser.getPresenceCondition());
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
          System.err.println(tb.toString());
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
          System.err.println("WARNING: unsupported semantic action: SignedKeyword");
          System.exit(1);
        }
        | __SIGNED
        {
          System.err.println("WARNING: unsupported semantic action: SignedKeyword");
          System.exit(1);
        }
        | __SIGNED__
        {
          System.err.println("WARNING: unsupported semantic action: SignedKeyword");
          System.exit(1);
        }
        ;

ComplexKeyword:
        _COMPLEX
        {
          System.err.println("WARNING: unsupported semantic action: ComplexKeyword");
          System.exit(1);
        }
        | __COMPLEX__
        {
          System.err.println("WARNING: unsupported semantic action: ComplexKeyword");
          System.exit(1);
        }
        ;

ElaboratedTypeName: /** passthrough, nomerge **/
        StructSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: ElaboratedTypeName");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: StructSpecifier");
          System.exit(1);
          Node tag     = getNodeAt(subparser, 6);
          Node members = getNodeAt(subparser, 3);
          Node attrs   = null;
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);
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
          System.err.println("WARNING: unsupported semantic action: StructDeclarationList");
          System.exit(1);
        }
        | StructDeclarationList StructDeclaration {
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
          System.err.println("WARNING: unsupported semantic action: StructDeclarationList");
          System.exit(1);
        }
        ;

StructDeclaration: /** nomerge **/
        StructDeclaringList SEMICOLON
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaration");
          System.exit(1);
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
          System.exit(1);
        }
        | StructDefaultDeclaringList COMMA StructIdentifierDeclarator AttributeSpecifierListOpt
        {
          System.err.println("WARNING: unsupported semantic action: StructDefaultDeclaringList");
          System.exit(1);
        }
        ;

StructDeclaringList: /** list, nomerge **/
        TypeSpecifier StructDeclarator AttributeSpecifierListOpt
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclaringList");
          System.exit(1);
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
          System.err.println("WARNING: unsupported semantic action: StructDeclarator");
          System.exit(1);
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
          List<Parameter> ps = getParamAt(subparser,3);
          Parameter p = new Parameter();
          p.setEllipsis();
          ps.add(p);
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
          List<Parameter> p = getParamAt(subparser,3);

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
          System.err.println("ParameterDeclaration-Abstract not supported");
        }
        ;

ParameterAbstractDeclaration:
        DeclarationSpecifier
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | DeclarationSpecifier AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | DeclarationQualifierList
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | DeclarationQualifierList AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | TypeSpecifier
        {
          StringBuilder sb = new StringBuilder();
          List<Type> typeList = getTBAt(subparser, 1).toType();
  	      if (typeList.size() == 1)
        		sb.append(typeList.get(0));
  	      else {
        		System.err.println("ERROR: Configurable typedefs not yet supported."); // TODO
        		// System.exit(1);
  	      }
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | TypeSpecifier AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | TypeQualifierList
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        | TypeQualifierList AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterAbstractDeclaration");
          System.exit(1);
        }
        ;

ParameterIdentifierDeclaration:
        DeclarationSpecifier IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
        }
        | DeclarationSpecifier ParameterTypedefDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
        }
        | TypeSpecifier IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);
          System.err.println("ParamIdent:" + type.toString());
          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
        }
        | TypeSpecifier ParameterTypedefDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
        }
        | TypeQualifierList IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: ParameterIdentifierDeclaration");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          DeclBuilder decl = getDBAt(subparser, 3);
          TypeBuilderMultiverse type = getTBAt(subparser, 4);

          Parameter p = new Parameter();
          p.setMultiverse(addMapping(subparser, type, decl));
          setTFValue(value, p);
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
          System.err.println("WARNING: unsupported semantic action: IdentifierOrTypedefName");
          System.exit(1);
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
        | ASSIGN DesignatedInitializer
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> allAssignVals = getSBMVAt(subparser, 1);
          if (allAssignVals != null) {
            CContext scope = (CContext) subparser.scope;
            /** Gets all renamings of the variable, and adds them to the sbmv */
            for (Multiverse.Element<StringBuilder> sbelem : allAssignVals) {
              Multiverse<SymbolTable.Entry> renamings = scope.getSymbolTable().map.get(sbelem.getData().toString());
              /** Checks for renamings in the symbol table */
              if (renamings != null) {
                /** Writes part of the assignment using the variables' renamings */
                for (Multiverse.Element<SymbolTable.Entry> renaming : renamings) {
                  sbmv.add(new Element<StringBuilder>(new StringBuilder(" = " + renaming.getData().getRenaming()), sbelem.getCondition().and(renaming.getCondition())/*subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)*/));
                }
              } else {
                /** If there is no renaming, then we are assigning something other than a variable (such as a constant).
                  * So, we do not get the renaming of what we are assigning, and instead just add that to the stringbuilder.
                  */
                sbmv.add(new Element<StringBuilder>(new StringBuilder(" = " + sbelem.getData().toString()), sbelem.getCondition()));
              }
            }
          }
          setTFValue(value, sbmv);
        }
        ;

DesignatedInitializer:/** nomerge, passthrough **/ /* ADDED */
        Initializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          System.exit(1);
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
          System.err.println(getDBAt(subparser,1) + ":PC::" + subparser.getPresenceCondition());
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
          System.err.println(db + ":PC::" + subparser.getPresenceCondition());
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
          System.err.println("WARNING: unsupported semantic action: AbstractDeclarator");
          System.exit(1);
        }
        | PostfixAbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: AbstractDeclarator");
          System.exit(1);
        }
        | PostfixingAbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: AbstractDeclarator");
          System.exit(1);
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
        | ParameterTypeList
        {
          setTFValue(value,getParamAt(subparser,1));
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
          if (arrayBounds.size() > 1) {
            System.err.println("ERROR: configurable array bounds not yet supported.");
            System.exit(1);
          } else {
            db.addArray(arrayBounds.get(0).getData().toString());
          }
          setTFValue(value, db);
	      }
        | ArrayAbstractDeclarator LBRACK ConstantExpression RBRACK
	      {
      	  DeclBuilder db = getDBAt(subparser,4);
          // TODO: support configurable array bound expressions
          Multiverse<StringBuilder> arrayBounds = getSBMVAt(subparser, 2);
          if (arrayBounds.size() > 1) {
            System.err.println("ERROR: configurable array bounds not yet supported.");
            System.exit(1);
          } else {
            db.addArray(arrayBounds.get(0).getData().toString());
          }
          setTFValue(value, db);
	      }
        ;

UnaryAbstractDeclarator: /** nomerge **/
        STAR
        {
          System.err.println("WARNING: unsupported semantic action: UnaryAbstractDeclarator");
          System.exit(1);
        }
        | STAR TypeQualifierList
        {
          System.err.println("WARNING: unsupported semantic action: UnaryAbstractDeclarator");
          System.exit(1);
        }
        | STAR AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: UnaryAbstractDeclarator");
          System.exit(1);
        }
        | STAR TypeQualifierList AbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: UnaryAbstractDeclarator");
          System.exit(1);
        }
        ;

PostfixAbstractDeclarator: /** nomerge **/
        LPAREN UnaryAbstractDeclarator RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PostfixAbstractDeclarator");
          System.exit(1);
        }
        | LPAREN PostfixAbstractDeclarator RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PostfixAbstractDeclarator");
          System.exit(1);
        }
        | LPAREN PostfixingAbstractDeclarator RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: PostfixAbstractDeclarator");
          System.exit(1);
        }
        | LPAREN UnaryAbstractDeclarator RPAREN PostfixingAbstractDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: PostfixAbstractDeclarator");
          System.exit(1);
        }
        ;

// ---------------------------------------------------------------- Statements

Statement:  /** passthrough, complete **/
        LabeledStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | CompoundStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | ExpressionStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | SelectionStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | IterationStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | JumpStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | AssemblyStatement  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        ;

LabeledStatement:  /** complete **/  // ADDED attributes
        IdentifierOrTypedefName COLON AttributeSpecifierListOpt Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression COLON Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression ELLIPSIS ConstantExpression COLON Statement  // ADDED case range
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | DEFAULT COLON Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
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
        | LocalLabelDeclarationList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        ;

LocalLabelDeclarationList:  /** list, complete **/
        LocalLabelDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LocalLabelDeclaration");
          System.exit(1);
        }
        ;

LocalLabelList:  /** list, complete **/  // ADDED
        IDENTIFIER
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        | LocalLabelList COMMA IDENTIFIER
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        ;

DeclarationOrStatementList:  /** list, complete **/  /* ADDED */
        | DeclarationOrStatementList DeclarationOrStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Node child1 = getNodeAt(subparser, 2);
          Node child2 = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = getProductOfSomeChildren(pc, child1, child2);
          setTFValue(value, product);
        }
        ;

DeclarationOrStatement: /** passthrough, complete **/  /* ADDED */
        DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | NestedFunctionDefinition
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        ;

DeclarationList:  /** list, complete **/
        DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
      	    sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
      	  }
          setTFValue(value, sbmv);
        }
        ;

SelectionStatement:  /** complete **/
        IF LPAREN Expression RPAREN Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: SelectionStatement");
          System.exit(1);
        }
        | IF LPAREN Expression RPAREN Statement ELSE Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: SelectionStatement");
          System.exit(1);
        }
        | SWITCH LPAREN Expression RPAREN Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: SelectionStatement");
          System.exit(1);
        }
        ;

IterationStatement:  /** complete **/
        WHILE LPAREN Expression RPAREN Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: IterationStatement");
          System.exit(1);
        }
        | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: IterationStatement");
          System.exit(1);
        }
        | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: IterationStatement");
          System.exit(1);
        }
        ;

JumpStatement:  /** passthrough, complete **/
        GotoStatement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | ContinueStatement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | BreakStatement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
          System.exit(1);
        }
        | ReturnStatement
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: JumpStatement");
        }
        ;

GotoStatement:  /** complete **/
        GOTO IdentifierOrTypedefName SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        | GOTO STAR Expression SEMICOLON  // ADDED
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        ;

ContinueStatement:  /** complete **/
        CONTINUE SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: ContinueStatement");
          System.exit(1);
        }
        ;

BreakStatement:  /** complete **/
        BREAK SEMICOLON
        {
          setCPC(value, PCtoString(subparser.getPresenceCondition()));
          System.err.println("WARNING: unsupported semantic action: BreakStatement");
          System.exit(1);
        }
        ;

ReturnStatement:  /** complete **/
        RETURN ExpressionOpt SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setCPC(value, PCtoString(pc));
          Multiverse<StringBuilder> temp = new Multiverse<StringBuilder>();
          temp.add(new StringBuilder("return "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true));
          Multiverse<StringBuilder> result = cartesianProductWithChild(temp, getNodeAt(subparser, 2), pc);
          temp.destruct();
          temp = result.product(new StringBuilder("; "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          result.destruct();
          result = temp;
          setTFValue(value, result);
        }
        ;

// --------------------------------------------------------------- Expressions

/* CONSTANTS */
Constant: /** passthrough, nomerge **/
        FLOATINGconstant
        {
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)value).getTokenText());
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | INTEGERconstant
        {
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)value).getTokenText());
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        /* We are not including ENUMERATIONConstant here  because  we
        are  treating  it like a variable with a type of "enumeration
        Constant".  */
        | OCTALconstant
        {
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)value).getTokenText());
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | HEXconstant
        {
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)value).getTokenText());
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | CHARACTERconstant
        {
          StringBuilder sb = new StringBuilder();
          sb.append(((Node)value).getTokenText());
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | Constant
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          //sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));


          CContext scope = (CContext) subparser.scope;

          // get the renamings from the symtab
          PresenceCondition cond = subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true);
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | Subscript
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | FunctionCall
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
          System.exit(1);
        }
        | DirectSelection
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
          System.exit(1);
        }
        | IndirectSelection
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
          System.exit(1);
        }
        | Increment
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | Decrement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | CompoundLiteral  /* ADDED */
        {
          System.err.println("WARNING: unsupported semantic action: PostfixExpression");
          System.exit(1);
        }
        ;

Subscript:  /** nomerge **/
        PostfixExpression LBRACK Expression RBRACK
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 4), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" [ "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 2), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" ] "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        ;

FunctionCall:  /** nomerge **/
        PostfixExpression LPAREN RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: FunctionCall");
          System.exit(1);
          callFunction(subparser, getNodeAt(subparser, 3), null);
        }
        | PostfixExpression LPAREN ExpressionList RPAREN
        {
          System.err.println("WARNING: unsupported semantic action: FunctionCall");
          System.exit(1);
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 2), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" ++ "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        ;

Decrement:  /** nomerge **/
        PostfixExpression DECR
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 2), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" -- "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | ICR UnaryExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          sbmv.add(new StringBuilder(" ++ "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true));
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        | DECR UnaryExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          sbmv.add(new StringBuilder(" -- "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true));
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Multiverse.Element<StringBuilder>(new StringBuilder(" & "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | STAR
        {
          System.err.println("WARNING: unsupported semantic action: Unaryoperator");
          System.exit(1);
        }
        | PLUS
        {
          System.err.println("WARNING: unsupported semantic action: Unaryoperator");
          System.exit(1);
        }
        | MINUS
        {
          System.err.println("WARNING: unsupported semantic action: Unaryoperator");
          System.exit(1);
        }
        | NEGATE
        {
          System.err.println("WARNING: unsupported semantic action: Unaryoperator");
          System.exit(1);
        }
        | NOT
        {
          System.err.println("WARNING: unsupported semantic action: Unaryoperator");
          System.exit(1);
        }
        ;

CastExpression:  /** passthrough, nomerge **/
        UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | MultiplicativeExpression STAR CastExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" * "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        | MultiplicativeExpression DIV CastExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" / "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        | MultiplicativeExpression MOD CastExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" % "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        ;

AdditiveExpression:  /** passthrough, nomerge **/
        MultiplicativeExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | AdditiveExpression PLUS MultiplicativeExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" + "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        | AdditiveExpression MINUS MultiplicativeExpression
        {
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Multiverse<StringBuilder> temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 3), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          temp = sbmv.product(new StringBuilder(" - "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true), SBCONCAT);
          sbmv.destruct();
          sbmv = temp;
          temp = cartesianProductWithChild(sbmv, getNodeAt(subparser, 1), subparser.getPresenceCondition());
          sbmv.destruct();
          sbmv = temp;
          setTFValue(value, sbmv);
        }
        ;

ShiftExpression:  /** passthrough, nomerge **/
        AdditiveExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | RelationalExpression LT ShiftExpression
        {
          System.err.println("WARNING: unsupported semantic action: RelationalExpression");
          System.exit(1);
        }
        | RelationalExpression GT ShiftExpression
        {
          System.err.println("WARNING: unsupported semantic action: RelationalExpression");
          System.exit(1);
        }
        | RelationalExpression LE ShiftExpression
        {
          System.err.println("WARNING: unsupported semantic action: RelationalExpression");
          System.exit(1);
        }
        | RelationalExpression GE ShiftExpression
        {
          System.err.println("WARNING: unsupported semantic action: RelationalExpression");
          System.exit(1);
        }
        ;

EqualityExpression:  /** passthrough, nomerge **/
        RelationalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        | EqualityExpression EQ RelationalExpression
        {
          System.err.println("WARNING: unsupported semantic action: EqualityExpression");
          System.exit(1);
        }
        | EqualityExpression NE RelationalExpression
        {
          System.err.println("WARNING: unsupported semantic action: EqualityExpression");
          System.exit(1);
        }
        ;

AndExpression:  /** passthrough, nomerge **/
        EqualityExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | MULTassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" *= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | DIVassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" /= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | MODassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" %= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | PLUSassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" += ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        | MINUSassign
        {
          StringBuilder sb = new StringBuilder();
          sb.append(" -= ");
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
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
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
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
          sbmv.add(new Element<StringBuilder>(sb, subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true)));
          setTFValue(value, sbmv);
        }
        ;

ExpressionOpt:  /** passthrough, nomerge **/
        /* Nothing */
        | Expression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
        ;

Expression:  /** passthrough, nomerge **/
        AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
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
          Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
          Node child = getNodeAt(subparser, 1);
          Multiverse<StringBuilder> product = cartesianProductWithChild(sbmv, child, pc);
          sbmv.destruct();
          setTFValue(value, product);
        }
	      ;

AttributeSpecifierListOpt: /** nomerge **/  // ADDED
        /* empty */
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
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | AUTO
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | DOUBLE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | INT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | STRUCT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | BREAK
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | ELSE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | LONG
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | SWITCH
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | CASE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | ENUM
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | REGISTER
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | TYPEDEF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | CHAR
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | EXTERN
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | RETURN
        {
          Multiverse<StringBuilder> result = new Multiverse<StringBuilder>();
          result.add(new StringBuilder("return "), subparser.getPresenceCondition().presenceConditionManager().new PresenceCondition(true));
          setTFValue(value, result);
        }
        | UNION
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | CONST
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | FLOAT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | SHORT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | UNSIGNED
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | CONTINUE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | FOR
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | SIGNED
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | VOID
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | DEFAULT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | GOTO
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | SIZEOF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | VOLATILE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | DO
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | IF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | STATIC
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | WHILE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | ASMSYM
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | _BOOL
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | _COMPLEX
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | RESTRICT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ALIGNOF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ALIGNOF__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | ASM
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ASM
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ASM__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ATTRIBUTE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __ATTRIBUTE__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __BUILTIN_OFFSETOF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __BUILTIN_TYPES_COMPATIBLE_P
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __BUILTIN_VA_ARG
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __BUILTIN_VA_LIST
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __COMPLEX__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __CONST
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __CONST__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __EXTENSION__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | INLINE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __INLINE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __INLINE__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __LABEL__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __RESTRICT
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __RESTRICT__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __SIGNED
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __SIGNED__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __THREAD
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | TYPEOF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __TYPEOF
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __TYPEOF__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __VOLATILE
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
        }
        | __VOLATILE__
        {
          System.err.println("WARNING: unsupported semantic action: Word");
          System.exit(1);
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

private List<Parameter> getParam(Object node) {
  return (List<Parameter>)((Node)node).getProperty(TRANSFORMATION);
}

private List<Parameter> getParamAt(Subparser subparser, int component) {
  // value should be not null and should be a Node type
  return (List<Parameter>) getNodeAt(subparser, component).getProperty(TRANSFORMATION);
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

// TODO: javadoc
// TODO: make note about how the numbers must be passed-in in the order that you want them concatenated.
private Multiverse<StringBuilder> getProductOfSomeChildren(PresenceCondition pc, Node...children) {
  Multiverse<StringBuilder> sbmv = new Multiverse<StringBuilder>();
  Multiverse<StringBuilder> temp;
  for (Node child : children) {
    temp = cartesianProductWithChild(sbmv, child, pc);
    sbmv.destruct();
    sbmv = temp;
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

  List<Boolean> typedef = typespec.isTypeDef();
  List<PresenceCondition> conds = typespec.getConditions();
  for (int i = 0; i < typedef.size(); ++i)
    {
      if (languageStatistics) {
	if (typedef.get(i)) {
	  Location location = subparser.lookahead.token.syntax.getLocation();
	  System.err.println(String.format("typedef %s %s", ident, location));
	}
      }

      if (showErrors) {
	System.err.println("bind: " + ident + " " + typedef.get(i));
      }
      if (debug) {
	System.err.println("def: " + ident + " " + alsoSet);
      }
      STField field = typedef.get(i) ? STField.TYPEDEF : STField.IDENT;
      scope.getSymbolTable().setbool(ident, field, true, conds.get(i));
      if (null != alsoSet) {
	scope.getSymbolTable().setbool(ident, alsoSet, true,conds.get(i));
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

private Multiverse<SymbolTable.Entry> getType(TypeBuilderMultiverse t, DeclBuilder d, PresenceCondition currentPC)
{
  Multiverse<SymbolTable.Entry> ret = new Multiverse<SymbolTable.Entry>();
  List<Type> types = t.toType();
  List<PresenceCondition> cond = t.getConditions();
  boolean func = d.isFunction();
  Multiverse<List<Parameter>> m = new Multiverse<List<Parameter>>();
  if (func)
    m = d.getParams(currentPC);
  for (int i = 0; i < cond.size(); ++i)
    {
      cond.get(i).addRef();
      DeclBuilder temp = new DeclBuilder(d);
      temp.addType(types.get(i));
      System.err.println("cond:" + cond.get(i).toString() + " current:" + currentPC.toString());
      if (func)
        {
          for(Element<List<Parameter>> e : m)
            if (e.getData().size() > 0)
              {
                List<Type> l = new LinkedList<Type>();
                for (Parameter p : e.getData())
                  if(!p.isEllipsis())
                    l.add(p.getType());
                Type f = new FunctionT(temp.toType(), l, e.getData().get(e.getData().size() - 1).isEllipsis());
                ret.add(new Element<SymbolTable.Entry>(new SymbolTable.Entry(mangleRenaming("",d.getID()), f), cond.get(i).and(e.getCondition())));
              }
            else
              {
                Type f = new FunctionT(temp.toType());
                ret.add(new Element<SymbolTable.Entry>(new SymbolTable.Entry(mangleRenaming("",d.getID()), f), cond.get(i).and(e.getCondition())));
              }
        }
      else
        ret.add(new Element<SymbolTable.Entry>(new SymbolTable.Entry(mangleRenaming("",d.getID()), temp.toType()), cond.get(i).and(currentPC)));
    }
  return ret;
}

private Multiverse<SymbolTable.Entry> addMapping(Subparser subparser, TypeBuilderMultiverse t, DeclBuilder d)
{
  if (t == null || d == null || !t.getIsValid() || !d.getIsValid())
    {
      System.err.println("Invalid declaration");
      // System.exit(1);
      return new Multiverse<SymbolTable.Entry>();
    }
  Multiverse<SymbolTable.Entry> unis = getType(t,d,subparser.getPresenceCondition());
  CContext scope = (CContext) subparser.scope;
  /* scope.getSymbolTable().addMapping(d.getID(), unis); */
  for (Element<SymbolTable.Entry> elem : unis) {
    scope.getSymbolTable().put(d.getID(), elem.getData().getType(), elem.getCondition());
  }
  unis.destruct();

  return scope.getSymbolTable().get(d.getID(), subparser.getPresenceCondition());
}

private List<StringBuilder> getRenamings(Multiverse<SymbolTable.Entry> unis)
{
  List<StringBuilder> sb = new LinkedList<StringBuilder>();
  for (Element<SymbolTable.Entry> u : unis)
    {
      sb.add(new StringBuilder(u.getData().getRenaming()));
    }
  return sb;
}

private static long varcount = 0;
private final static char[] charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".toCharArray();
private final static Random random = new Random();
private final static int RAND_SIZE = 5;

/** Generates a ranom string of proper length for identifier renamings */
private String randomString(int string_size) {
  StringBuilder randomstring = new StringBuilder();
  for (int i = 0; i < string_size; i++) {
    randomstring.append(charset[random.nextInt(charset.length)]);
  }
  return randomstring.toString();
}

/** Renames identifiers in valid C */
private String mangleRenaming(String prefix, String ident) {
    // don't want to exceed c identifier length limit (31)
    if (ident.length() > 22) {
      // shorten ident to be at max, 22 chars
      StringBuilder sb = new StringBuilder(ident);
      sb = sb.delete(23, ident.length());
      ident = sb.toString();
    }
    return String.format("_%s%d%s_%s", prefix, varcount++, randomString(RAND_SIZE), ident);
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
    mv.add(node, presenceConditionManager.new PresenceCondition(true));
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
