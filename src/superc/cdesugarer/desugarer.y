/*   Copyright (C) 1989,1990 James A. Roskind, All rights reserved.
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

import xtc.lang.cpp.Declarator;
import xtc.lang.cpp.Declarator.EmptyDeclarator;
import xtc.lang.cpp.Declarator.SimpleDeclarator;
import xtc.lang.cpp.Declarator.PointerDeclarator;
import xtc.lang.cpp.Declarator.QualifiedPointerDeclarator;
import xtc.lang.cpp.Declarator.PointerAbstractDeclarator;
import xtc.lang.cpp.Declarator.QualifiedPointerAbstractDeclarator;
import xtc.lang.cpp.Declarator.ArrayDeclarator;
import xtc.lang.cpp.Declarator.ArrayAbstractDeclarator;
import xtc.lang.cpp.Declarator.FunctionDeclarator;
import xtc.lang.cpp.Declarator.ParameterListDeclarator;

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
import java.util.Map;
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

TranslationUnit:  /** complete **/
        ExternalDeclarationList
        {
          try {
            OutputStreamWriter writer = new OutputStreamWriter(System.out);

            // emit headers
            writer.write("#include <stdbool.h>\n");
            writer.write("\n");

            // emit extern declarations for desugaring runtime.
            writer.write("extern void __static_type_error(char *msg);\n");
            writer.write("extern void __static_renaming(char *renaming, char *original);\n");
            writer.write("extern void __static_condition_renaming(char *renaming, char *expression);\n");
            writer.write("\n");

            // emit static initializer declaration.
            String static_initializer_name = freshCId("static_initializer");
            String static_initializer_signature = String.format("void %s()", static_initializer_name);
            writer.write(String.format("%s;\n", static_initializer_signature));
            writer.write("\n");
            
            // emit the static initializer definition
            writer.write(String.format("%s {\n%s\n%s\n};\n",
                                       static_initializer_signature,
                                       recordedRenamings.toString(),
                                       invalidGlobals.toString()));
            
            
            // writes the extern declarations for the renamed preprocessor BDDs
            System.err.println("TODO: record original presence condition strings in file as well once raw strings are collected");
            for (Integer hash : condVars.keySet()) {
              writer.write(String.format("extern const bool %s;\n", condVars.get(hash)));
            }

            SymbolTable symtab = ((CContext) subparser.scope).getSymbolTable();

            // write the user-defined types at the top of the scope.
            CContext scope = ((CContext) subparser.scope);
            writer.write(scope.getDeclarations(subparser.getPresenceCondition()));

            System.err.println(symtab);

            // write the transformed C
            writer.write(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()).toString());
            writer.write("\n");

            writer.flush();
          } catch(IOException e) {
            e.printStackTrace();
            System.exit(1);
          }
        }
        ;

// ------------------------------------------------------ External definitions

ExternalDeclarationList: /** list, complete **/
        /* empty */  // ADDED gcc allows empty program
        {
          String valuesb = "";
          setTransformationValue(value, valuesb);
        }
        | ExternalDeclarationList ExternalDeclaration
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(concatAllStrings(getNodeAt(subparser, 2), subparser.getPresenceCondition()));
          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          setTransformationValue(value, valuesb.toString());
        }
        ;

ExternalDeclaration:  /** complete **/
        FunctionDefinitionExtension
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | DeclarationExtension
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | AssemblyDefinition
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | EmptyDefinition
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        ;

EmptyDefinition:  /** complete **/
        SEMICOLON
        {
          setTransformationValue(value, (String) getNodeAt(subparser, 1).getTokenText());
        }
        ;

FunctionDefinitionExtension:  /** complete **/  // ADDED
        FunctionDefinition
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | __EXTENSION__ FunctionDefinition
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(getNodeAt(subparser, 2).getTokenText());
          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          setTransformationValue(value, valuesb.toString());
        }
        ;

FunctionDefinition:  /** complete **/ // added scoping  // String
        FunctionPrototype { ReenterScope(subparser); } LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        {
          // similar to Declaration, but different in that this has a
          // compoundstatement, while declaration has an initializer.
          PresenceCondition pc = subparser.getPresenceCondition();

          String leftcurly = getNodeAt(subparser, 4).getTokenText();
          String body = concatAllStrings(getNodeAt(subparser, 3), subparser.getPresenceCondition()).toString();
          String rightcurly = getNodeAt(subparser, 1).getTokenText();
          
          /* System.err.println("TYPE: " + typebuildermv); */
          /* System.err.println("DECLARATOR: " + declaratormv); */

          // add all variations of the function declaration to the symtab
          CContext scope = (CContext)subparser.scope;

          // declarations, including function definitions, should
          // appear unconditionally in the desugared output, since
          // renaming handles different configurations.  so add all
          // resulting definitions to a single element multiverse
          // under the true condition.
          StringBuilder sb = new StringBuilder();

          // TODO: optimization: dedeuplicate functions that have the
          // same type.  this type deduplication maybe also be useful
          // for typechecking to find a single type eror.

          // TODO: investigate why the function prototype can still
          // have a conditional underneath even though the complete
          // annotation isn't on functionprototype.  this is why we
          // are getting all nodes at this point
          Multiverse<Node> prototypeNodemv = getAllNodeConfigs(getNodeAt(subparser, 6), subparser.getPresenceCondition());
          for (Element<Node> prototypeNode : prototypeNodemv) {
            FunctionPrototypeValue prototype = (FunctionPrototypeValue) getTransformationValue(prototypeNode.getData());
            Multiverse<TypeBuilder> typebuildermv = prototype.typebuilder;
            Multiverse<Declarator> declaratormv = prototype.declarator;

            assert scope.isGlobal(); // function definitions should be global.  nested functions have a separate subgrammar.
          
            for (Element<TypeBuilder> typebuilder : typebuildermv) {
              PresenceCondition typebuilderCond = prototypeNode.getCondition().and(typebuilder.getCondition());
              for (Element<Declarator> declarator : declaratormv) {
                PresenceCondition combinedCond = typebuilderCond.and(declarator.getCondition());
                String originalName = declarator.getData().getName();
                Declaration originalDeclaration = new Declaration(typebuilder.getData(), declarator.getData());

                if (originalDeclaration.hasTypeError()) {
                  // if type is invalid, put an error entry, emit a call
                  // to the type error function
                  scope.putError(originalName, combinedCond);
                  recordInvalidGlobalDeclaration(originalName, combinedCond);
                  System.err.println(String.format("INFO: \"%s\" has an invalid type specifier", originalName));
                } else {
                  // otherwise loop over each existing entry check for
                  // type errors or add a new declaration
                  Multiverse<SymbolTable.Entry> entries = scope.getCurrentScope(originalName, combinedCond);
                  for (Element<SymbolTable.Entry> entry : entries) {
                    String renaming = freshCId(originalName);
                    Declarator renamedDeclarator = declarator.getData().rename(renaming);
                    Declaration renamedDeclaration = new Declaration(typebuilder.getData(),
                                                                     renamedDeclarator);

                    // renamedDeclaration must be a FunctionT because
                    // that is created by a FunctionDeclarator
                    Type declarationType = renamedDeclaration.getType();
                    Type type = new NamedFunctionT(declarationType.toFunction().getResult(),
                                                   renaming,
                                                   declarationType.toFunction().getParameters(),
                                                   declarationType.toFunction().isVarArgs());
                    
                    if (entry.getData() == SymbolTable.ERROR) {
                      // ERROR entry
                      System.err.println(String.format("INFO: \"%s\" is being redeclared in an existing invalid declaration", originalName));
                    } else if (entry.getData() == SymbolTable.UNDECLARED) {
                      // UNDECLARED entry

                      // update the symbol table for this presence condition
                      scope.put(originalName, type, entry.getCondition());

                      // add the forward declaration to the scope to
                      // facilitate matching of signatures for linking
                      StringBuilder forward = new StringBuilder();
                      forward.append(renamedDeclaration.toString());
                      forward.append(";\n");
                      scope.addDeclaration(forward.toString());
                      forward = null;
                      
                      sb.append(renamedDeclaration.toString());
                      sb.append(" ");
                      sb.append(leftcurly);
                      sb.append("\n");
                      sb.append(body);
                      sb.append("\n");
                      sb.append(rightcurly);
                      sb.append("\n");
                      recordRenaming(renaming, originalName);

                    } else {
                      if (entry.getData().getType() instanceof NamedFunctionT) {  // there is no Type.isFunctionOrMethod()
                        FunctionT newtype = ((NamedFunctionT) type).toFunctionT();
                        FunctionT previoustype = ((NamedFunctionT) entry.getData().getType()).toFunctionT();

                        // TODO: make sure a function is only defined
                        // once, although it can be declared multiple
                        // times.
                    
                        // already declared entries
                        if (cOps.equal(newtype, previoustype)) {
                          System.err.println("TODO: distinguish between previous declaration vs definition.");
                          sb.append(renamedDeclaration.toString());
                          sb.append(" ");
                          sb.append(getNodeAt(subparser, 4).getTokenText());
                          sb.append("\n");
                          sb.append((String) getTransformationValue(subparser, 3));
                          sb.append("\n");
                          sb.append(getNodeAt(subparser, 1).getTokenText());
                          sb.append("\n");
                          System.err.println(String.format("INFO: %s is being redeclared in global scope to compatible type", originalName));
                        } else {
                          scope.putError(originalName, entry.getCondition());
                          recordInvalidGlobalDeclaration(originalName, entry.getCondition());
                          // emit the same declaration, since it's legal to redeclare globals to a compatible type
                        }
                      } else { // existing entry is a function type
                        scope.putError(originalName, entry.getCondition());
                        recordInvalidGlobalDeclaration(originalName, entry.getCondition());
                        System.err.println(String.format("INFO: attempted to redeclare \"%s\" as function instead of non-function", originalName));
                      }  // end of check for existing function type
                    }  // end test of symtab entry type
                    sb.append("\n"); // TODO: pass results through a pretty printer or ultimately preserve input file formatting
                  } // end loop over symtab entries
                }
              
                combinedCond.delRef();
              } // end of loop over declarators
              typebuilderCond.delRef();
            } // end of loop over typebuilders
            // TODO: improve memory usage by destructing these.
            // challenge is that they are shared by nodes.
            /* typebuildermv.destruct(); */
            /* declaratormv.destruct(); */
          } // end of check for invalid typebuilder
          if (debug) System.err.println(scope.getSymbolTable());
          prototypeNodemv.destruct();          
          setTransformationValue(value, sb.toString());
        }
        | FunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        {
          // TODO
          System.err.println("WARNING: unsupported semantic action: FunctionDefinition");
          System.exit(1);
        }
        ;

/* Functions have their own compound statement because of the need for
   reentering scope. */
FunctionCompoundStatement:  /** nomerge, name(CompoundStatement) **/  // String
        LocalLabelDeclarationListOpt DeclarationOrStatementList
        {
          // TODO: same as CompoundStatement
          PresenceCondition pc = subparser.getPresenceCondition();

          StringBuilder valuesb = new StringBuilder();
          valuesb.append(concatAllStrings(getNodeAt(subparser, 2), subparser.getPresenceCondition()));

          // print user-defined type declarations at top of scope
          CContext scope = ((CContext) subparser.scope);
          valuesb.append(scope.getDeclarations(subparser.getPresenceCondition()));

          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          if (debug) System.err.println(((CContext) subparser.scope).getSymbolTable());
          setTransformationValue(value, valuesb.toString());
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
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          // TODO: handle the case when there is no type spec, i.e.,
          // it defaults to int, so just create a new
          // typebuildermultiverse with one int inside under the current presence condition
        }
        | DeclarationSpecifier     IdentifierDeclarator
        {
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue((Multiverse<TypeBuilder>) getTransformationValue(subparser, 2),
                                                                   (Multiverse<Declarator>) getTransformationValue(subparser, 1)));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue((Multiverse<TypeBuilder>) getTransformationValue(subparser, 2),
                                                                   (Multiverse<Declarator>) getTransformationValue(subparser, 1)));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue((Multiverse<TypeBuilder>) getTransformationValue(subparser, 2),
                                                                   (Multiverse<Declarator>) getTransformationValue(subparser, 1)));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue((Multiverse<TypeBuilder>) getTransformationValue(subparser, 2),
                                                                   (Multiverse<Declarator>) getTransformationValue(subparser, 1)));
        }
        |                          OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionPrototype");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

FunctionOldPrototype:  /** nomerge **/
        OldFunctionDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
        ;

/* Nested function's declarator can't just be an IdentifierDeclarator
   or it gets a conflict.  gcc seems to behave this way too since it
   yields a parsing error. */
NestedFunctionDefinition:  /** complete **/ // added scoping
        NestedFunctionPrototype { ReenterScope(subparser); } LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | NestedFunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        ;

NestedFunctionPrototype:  /** nomerge **/
          DeclarationSpecifier     IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }

        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        ;

NestedFunctionOldPrototype:  /** nomerge **/
        DeclarationSpecifier       OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("WARNING: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
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

DeclarationExtension:  /** complete **/  // ADDED
        Declaration
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | __EXTENSION__ Declaration
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(getNodeAt(subparser, 2).getTokenText());
          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          setTransformationValue(value, valuesb.toString());
        }
        ;

Declaration:  /** complete **/  // String
        SUEDeclarationSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
        	Multiverse<TypeBuilder> structtypesmv
            = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 3);
        	StringBuilder sb = new StringBuilder();  // the desugared output

          for (Element<TypeBuilder> typebuilder : structtypesmv) {
            if (! typebuilder.getData().hasTypeError()) {
              sb.append(typebuilder.getData().toString());
              sb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
            } else {
              CContext scope = ((CContext) subparser.scope);
              if (scope.isGlobal()) {
                recordInvalidGlobalDeclaration(typebuilder.getData().getStructTag(),
                                               typebuilder.getCondition());
              } else {
                sb.append("if (");
                sb.append(condToCVar(typebuilder.getCondition()));
                sb.append(") {\n");
                sb.append(emitError(String.format("invalid declaration of struct: %s",
                                                  typebuilder.getData().getStructTag())));
                sb.append("}\n");
              }
            }
          }
          sb.append("\n");
          
          /* System.err.println(((CContext) subparser.scope).getSymbolTable()); */
          setTransformationValue(value, sb.toString());
        }
        | SUETypeSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
        	Multiverse<TypeBuilder> structtypesmv
            = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 3);
        	StringBuilder sb = new StringBuilder();  // the desugared output

          for (Element<TypeBuilder> typebuilder : structtypesmv) {
            if (! typebuilder.getData().hasTypeError()) {
              sb.append(typebuilder.getData().toString());
              sb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
            } else {
              CContext scope = ((CContext) subparser.scope);
              if (scope.isGlobal()) {
                recordInvalidGlobalDeclaration(typebuilder.getData().getStructTag(),
                                               typebuilder.getCondition());
              } else {
                sb.append("if (");
                sb.append(condToCVar(typebuilder.getCondition()));
                sb.append(") {\n");
                sb.append(emitError(String.format("invalid declaration of struct: %s",
                                                  typebuilder.getData().getStructTag())));
                sb.append("}\n");
              }
            }
          }
          sb.append("\n");
          
          /* System.err.println(((CContext) subparser.scope).getSymbolTable()); */
          setTransformationValue(value, sb.toString());
        }
        | DeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          CContext scope = ((CContext) subparser.scope);
        	StringBuilder valuesb = new StringBuilder();  // the desugared output

          /*
           * to desugar declarations, we need to iterate over all
           * combinations of (1) declarators in the declaring list,
           * (2) the type multiverse, (3) the declarator multiverse,
           * and (4) the initializer multiverse.  TODO: also add the
           * assembly and attribute contents, although this is not
           * necessary for source-level analysis.
           */

          // loop over each element of the declaration list
        	List<DeclaringListValue> declaringlistvalues = (List<DeclaringListValue>) getTransformationValue(subparser, 3);
          for (DeclaringListValue declaringlistvalue : declaringlistvalues) {
            // unpack type specifier, declarators, and initializers from the transformation value
            Multiverse<TypeBuilder> typebuildermv = declaringlistvalue.typebuilder;
            Multiverse<Declarator> declaratormv = declaringlistvalue.declarator;
            Multiverse<String> initializermv = declaringlistvalue.initializer;

            // TODO: use typebuilder/declarator to reclassify the
            // tokens as typedef/ident in parsing context

            for (Element<TypeBuilder> typebuilder : typebuildermv) {
              PresenceCondition typebuilderCond = subparser.getPresenceCondition().and(typebuilder.getCondition());
              for (Element<String> initializer : initializermv) {
                // TODO: optimization opportunity, share multiple
                // initialiers with one renaming (harder for globals)
                PresenceCondition initializerCond = typebuilderCond.and(initializer.getCondition());
                for (Element<Declarator> declarator : declaratormv) {
                  PresenceCondition combinedCond = initializerCond.and(declarator.getCondition());
                  String originalName = declarator.getData().getName();

                  // get xtc type from type and declarator

                  if (typebuilder.getData().hasTypeError()) {
                    // if type is invalid, put an error entry, emit a call
                    // to the type error function
                    scope.putError(originalName, combinedCond);
                    if (scope.isGlobal()) {
                      recordInvalidGlobalDeclaration(originalName, combinedCond);
                    } else {
                      valuesb.append("if (");
                      valuesb.append(condToCVar(combinedCond));
                      valuesb.append(") {\n");
                      valuesb.append(emitError(String.format("invalid declaration of \"%s\" under this presence condition",
                                                             originalName)));
                      valuesb.append("}\n");
                    }
                  } else {
                    // otherwise loop over each existing entry check for
                    // type errors or add a new declaration
                    Multiverse<SymbolTable.Entry> entries = scope.getCurrentScope(originalName, combinedCond);
                    for (Element<SymbolTable.Entry> entry : entries) {
                      String renaming = freshCId(originalName);
                      Declarator renamedDeclarator = declarator.getData().rename(renaming);
                      Declaration renamedDeclaration = new Declaration(typebuilder.getData(),
                                                                       renamedDeclarator);

                      StringBuilder entrysb = new StringBuilder();

                      Type declarationType = renamedDeclaration.getType();
                      Type type = renamedDeclaration.typebuilder.isTypedef()
                        ? new AliasT(renaming, declarationType)
                        : (scope.isGlobal()
                           ? VariableT.newGlobal(declarationType, renaming)
                           : VariableT.newLocal(declarationType, renaming));

                      if (entry.getData() == SymbolTable.ERROR) {
                        // ERROR entry
                        System.err.println(String.format("INFO: \"%s\" is being redeclared in an existing invalid declaration", originalName));

                      } else if (entry.getData() == SymbolTable.UNDECLARED) {
                        // UNDECLARED entry
                        // update the symbol table for this presence condition
                        scope.put(originalName, type, entry.getCondition());
                    
                        entrysb.append(renamedDeclaration.toString());
                        entrysb.append(initializer.getData());
                        entrysb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
                        recordRenaming(renaming, originalName);

                      } else {  // already declared entries
                        if (! scope.isGlobal()) {
                          // not allowed to redeclare local symbols at all
                          scope.putError(originalName, entry.getCondition());
                          entrysb.append("if (");
                          entrysb.append(condToCVar(entry.getCondition()));
                          entrysb.append(") {\n");
                          entrysb.append(emitError(String.format("redeclaration of local symbol: %s",
                                                                 originalName)));
                          entrysb.append("}\n");
                        } else {  // global scope

                          // declarations only set VariableT or AliasT
                          boolean sameTypeKind
                            = entry.getData().getType().isVariable() && type.isVariable()
                            ||  entry.getData().getType().isAlias() && type.isAlias();

                          // check compatibility of types
                          if (sameTypeKind) {
                            boolean compatibleTypes = false;
                            if (type.isVariable()) {
                              compatibleTypes = cOps.equal(entry.getData().getType().toVariable().getType(),
                                                           type.toVariable().getType());
                            } else if (type.isAlias()) {
                              compatibleTypes = cOps.equal(entry.getData().getType().toAlias().getType(),
                                                           type.toAlias().getType());
                            } else {
                              throw new AssertionError("should not be possible given sameTypeKind");
                            }
                            
                            if (! compatibleTypes) {
                              // not allowed to redeclare globals to a different type
                              scope.putError(originalName, entry.getCondition());
                              recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                            } else {
                              // emit the same declaration, since it's legal to redeclare globals to a compatible type
                              entrysb.append(renamedDeclaration.toString());
                              entrysb.append(initializer.getData());
                              entrysb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
                              System.err.println(String.format("INFO: \"%s\" is being redeclared in global scope to compatible type", originalName));
                            }

                          } else { // not the same kind of type
                            scope.putError(originalName, entry.getCondition());
                            System.err.println(String.format("INFO: attempted to redeclare global to a different kind of type: %s", originalName));
                            recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                          } // end check for variable type
                        } // end check global/local scope
                      } // end entry kind
                      entrysb.append("\n");

                      if (renamedDeclaration.typebuilder.isTypedef()) {
                        // typedefs are moved to the top of the scope
                        // to support forward references of structs
                        scope.addDeclaration(entrysb.toString());
                        valuesb.append("// typedef moved to top of scope\n");
                      } else {
                        // not a typedef, so add it to regular output
                        valuesb.append(entrysb.toString());
                      }
                    } // end loop over symtab entries
                  }
              
                  combinedCond.delRef();
                } // end loop over declarators
                initializerCond.delRef();
              } // end loop over initializers
              typebuilderCond.delRef();
            } // end loop over typebuilders
            // TODO: these destructs causes nullpointer errors due to
            // the sharing of semantic values.  not destructing will
            // cause memory leak
            /* typebuildermv.destruct(); */
            /* declaratormv.destruct(); */
            /* initializermv.destruct(); */
          } // end loop over declaringlistvalues
          
          if (debug) System.err.println(scope.getSymbolTable());

          setTransformationValue(value, valuesb.toString());
        }
        | DefaultDeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          System.err.println("TODO: Declaration (4)");
          System.exit(1);
        }
        ;

/* Note that if a typedef were  redeclared,  then  a  declaration
   specifier must be supplied */

DefaultDeclaringList:  /** nomerge **/  /* Can't  redeclare typedef names */
        DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          System.err.println("TODO: DeclarationDeclaringList (1)");
          System.exit(1);
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 6);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 5);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<String> initializers = new Multiverse<String>("", subparser.getPresenceCondition());
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          System.err.println("TODO: DeclarationDeclaringList (3)");
          System.exit(1);
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 6);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 5);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<String> initializers = new Multiverse<String>("", subparser.getPresenceCondition());
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
        | DefaultDeclaringList COMMA AttributeSpecifierListOpt IdentifierDeclarator
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList (5)");
          System.exit(1);
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        }
        AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          System.err.println("WARNING: unsupported semantic action: DefaultDeclaringList (6)");
          System.exit(1);
        }
        ;

DeclaringList:  /** nomerge **/
        DeclarationSpecifier Declarator AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          saveBaseType(subparser, getNodeAt(subparser, 5));
          bindIdent(subparser, getNodeAt(subparser, 5), getNodeAt(subparser, 4));  // TODO: use new bindIdent to find typedefname

          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 5);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 4);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<String> initializers = (Multiverse<String>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
        | TypeSpecifier Declarator AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 5), getNodeAt(subparser, 4));  // TODO: use new bindIdent to find typedefname

          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 5);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 4);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<String> initializers = (Multiverse<String>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator
        {
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
          System.err.println("TODO: DeclaringList (3)");
          System.exit(1);
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          // TODO: hoist initiazliers around the entire InitializedDeclaration
          List<DeclaringListValue> declaringlist = (List<DeclaringListValue>) getTransformationValue(subparser, 8);
          // there must be at least one element in the DeclaringList
          // according to the grammar
          assert declaringlist.size() > 0;
          // each element is given the same typebuildermultiverse, so
          // we can take it from the first element, which is
          // guaranteed to be there.
          Multiverse<TypeBuilder> types = declaringlist.get(0).typebuilder;
          // the rest of the action is the same as its other
          // productions, except we add to the list instead of making
          // a new one
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 5);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<String> initializers = (Multiverse<String>) getTransformationValue(subparser, 1);
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
        ;


DeclarationSpecifier:  /**  nomerge **/
        BasicDeclarationSpecifier        /* Arithmetic or void */
				{
	  			Multiverse<TypeBuilder> decl = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
	  			setTransformationValue(value, decl);
				}
        | SUEDeclarationSpecifier          /* struct/union/enum */
				{
          Multiverse<TypeBuilder> t = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
        	setTransformationValue(value,t);
				}
        | TypedefDeclarationSpecifier      /* typedef*/
				{
          Multiverse<TypeBuilder> t = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
        	setTransformationValue(value,t);
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
          Multiverse<TypeBuilder> t = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
        	setTransformationValue(value,t);
				}
        | SUETypeSpecifier                 /* Struct/Union/Enum */
				{
          Multiverse<TypeBuilder> t = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
        	setTransformationValue(value,t);
				}
				| TypedefTypeSpecifier             /* Typedef */
				{
					setTransformationValue(value,(Multiverse<TypeBuilder>) getTransformationValue(subparser,1));
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
      	  Multiverse<TypeBuilder> storage = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
      	  setTransformationValue(value, storage);
      	  updateSpecs(subparser,
          getSpecsAt(subparser, 1),
          value);
      	}
      	| TypeQualifierList StorageClass
      	{
      	  Multiverse<TypeBuilder> qualList = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
      	  Multiverse<TypeBuilder> storage = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
      	  Multiverse<TypeBuilder> tb = qualList.product(storage, DesugaringOperators.TBCONCAT);
      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | DeclarationQualifierList DeclarationQualifier
      	{
      	  Multiverse<TypeBuilder> qualList = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
      	  Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
      	  Multiverse<TypeBuilder> tb = qualList.product(qual, DesugaringOperators.TBCONCAT);
      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        ;

TypeQualifierList:  /** list, nomerge **/
        TypeQualifier
      	{
      	  Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
      	  setTransformationValue(value, qual);
    	    updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | TypeQualifierList TypeQualifier
      	{
      	  Multiverse<TypeBuilder> qualList = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
      	  Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
      	  Multiverse<TypeBuilder> tb = qualList.product(qual, DesugaringOperators.TBCONCAT);
      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        ;

DeclarationQualifier:
        TypeQualifier                  /* const or volatile */
        {
          Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, qual);
        }
        | StorageClass
        {
          Multiverse<TypeBuilder> storage = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, storage);
        }
        ;

TypeQualifier:    // const, volatile, and restrict can have underscores
        ConstQualifier
        {
          Multiverse<TypeBuilder> qual = new Multiverse<TypeBuilder>(new TypeBuilder("const"), subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VolatileQualifier
        {
          Multiverse<TypeBuilder> qual = new Multiverse<TypeBuilder>(new TypeBuilder("volatile"), subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | RestrictQualifier
        {
          Multiverse<TypeBuilder> qual = new Multiverse<TypeBuilder>(new TypeBuilder("restrict"), subparser.getPresenceCondition());
          setTransformationValue(value, qual);
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
          Multiverse<TypeBuilder> qual = new Multiverse<TypeBuilder>(new TypeBuilder("inline"), subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

// TODO: syntax
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

// TODO: syntax
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

// TODO: syntax
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

// TODO: syntax
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
        Multiverse<TypeBuilder> basicTypeSpecifier = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
        Multiverse<TypeBuilder> storageClass = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

        // combine the partial type specs
        Multiverse<TypeBuilder> tb = basicTypeSpecifier.product(storageClass, DesugaringOperators.TBCONCAT);

        setTransformationValue(value, tb);
	      updateSpecs(subparser,
                    getSpecsAt(subparser, 2),
                    getSpecsAt(subparser, 1),
                    value);
        }
        | DeclarationQualifierList BasicTypeName {
	        Multiverse<TypeBuilder> qualList = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> basicTypeName = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          // combine the partial type specs
          Multiverse<TypeBuilder> tb = qualList.product(basicTypeName, DesugaringOperators.TBCONCAT);

	        setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier DeclarationQualifier
        {
 	        Multiverse<TypeBuilder> decl = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          // combine the partial type specs
          Multiverse<TypeBuilder> tb = decl.product(qual, DesugaringOperators.TBCONCAT);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier BasicTypeName
        {
	        Multiverse<TypeBuilder> basicDeclSpecifier = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> basicTypeName = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          // combine the partial type specs
          Multiverse<TypeBuilder> tb = basicDeclSpecifier.product(basicTypeName, DesugaringOperators.TBCONCAT);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

BasicTypeSpecifier: /**  nomerge **/  // Multiverse<TypeBuilder>
        BasicTypeName           /* Arithmetic or void */
        {
          // TUTORIAL: a semantic action that sets the semantic value
          // to a new typebuilder by adding a property derived from
          // the child semantic value(s)
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);

        }
        | TypeQualifierList BasicTypeName
	      {
          Multiverse<TypeBuilder> qualList = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> basicTypeName = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          Multiverse<TypeBuilder> tb = qualList.product(basicTypeName, DesugaringOperators.TBCONCAT);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier TypeQualifier
	      {
          Multiverse<TypeBuilder> basicTypeSpecifier = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> qual = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          Multiverse<TypeBuilder> tb = basicTypeSpecifier.product(qual, DesugaringOperators.TBCONCAT);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier BasicTypeName
        {
          // get the semantic values of each child
          Multiverse<TypeBuilder> basicTypeSpecifier = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> basicTypeName = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);

          // combine the partial type specs
          Multiverse<TypeBuilder> tb = basicTypeSpecifier.product(basicTypeName, DesugaringOperators.TBCONCAT);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

SUEDeclarationSpecifier: /** nomerge **/          /* StorageClass + struct/union/enum */   // Multiverse<TypeBuilder>
        SUETypeSpecifier StorageClass
        {
          // TODO: unit test this action
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        | DeclarationQualifierList ElaboratedTypeName
        {
          // TODO: unit test this action
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        | SUEDeclarationSpecifier DeclarationQualifier
        {
          // TODO: unit test this action
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        ;

SUETypeSpecifier: /** nomerge **/
        ElaboratedTypeName              /* struct/union/enum */
        {
        	setTransformationValue(value,
            (Multiverse<TypeBuilder>) getTransformationValue(subparser,1));
        }
        | TypeQualifierList ElaboratedTypeName
        {
          // TODO: unit test this action
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        | SUETypeSpecifier TypeQualifier
        {
          // TODO: unit test this action
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        ;


TypedefDeclarationSpecifier: /** nomerge **/       /*Storage Class + typedef types */
        TypedefTypeSpecifier StorageClass
      	{
      	  Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        | DeclarationQualifierList TYPEDEFname
        {
          // TODO: needs a unit test
          Multiverse<TypeBuilder> qualtbmv = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry> entries
            = ((CContext)subparser.scope).getAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
      	  Multiverse<TypeBuilder> typedefnametbmv = DesugaringOperators.typedefEntriesToTypeBuilder.transform(entries);
          // combine with the existing qualifier list
          Multiverse<TypeBuilder> combinedtbmv = qualtbmv.product(typedefnametbmv, DesugaringOperators.TBCONCAT);
          typedefnametbmv.destruct();
          setTransformationValue(value, combinedtbmv);
        }
        | TypedefDeclarationSpecifier DeclarationQualifier
      	{
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
        }
        ;

TypedefTypeSpecifier: /** nomerge **/              /* typedef types */
        TYPEDEFname
      	{
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry> entries
            = ((CContext)subparser.scope).getAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
      	  Multiverse<TypeBuilder> typedefnametbmv = DesugaringOperators.typedefEntriesToTypeBuilder.transform(entries);
          setTransformationValue(value, typedefnametbmv);
        }
        | TypeQualifierList TYPEDEFname
      	{
          Multiverse<TypeBuilder> qualtbmv = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry> entries
            = ((CContext)subparser.scope).getAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
      	  Multiverse<TypeBuilder> typedefnametbmv = DesugaringOperators.typedefEntriesToTypeBuilder.transform(entries);
          // combine with the existing qualifier list
          Multiverse<TypeBuilder> combinedtbmv = qualtbmv.product(typedefnametbmv, DesugaringOperators.TBCONCAT);
          typedefnametbmv.destruct();
          setTransformationValue(value, combinedtbmv);
      	}
        | TypedefTypeSpecifier TypeQualifier
        {
          Multiverse<TypeBuilder> tb = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<TypeBuilder> tb1 = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, tb.product(tb1, DesugaringOperators.TBCONCAT));
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

// TODO: syntax
StorageClass:
        TYPEDEF
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          Multiverse<TypeBuilder> storage = new Multiverse<TypeBuilder>(new TypeBuilder(storageName), subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF;
        }
        | EXTERN
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          Multiverse<TypeBuilder> storage = new Multiverse<TypeBuilder>(new TypeBuilder(storageName), subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN;
        }
        | STATIC
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          Multiverse<TypeBuilder> storage = new Multiverse<TypeBuilder>(new TypeBuilder(storageName), subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC;
        }
        | AUTO
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          Multiverse<TypeBuilder> storage = new Multiverse<TypeBuilder>(new TypeBuilder(storageName), subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO;
        }
        | REGISTER
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          Multiverse<TypeBuilder> storage = new Multiverse<TypeBuilder>(new TypeBuilder(storageName), subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_REGISTER;
        }
        ;

// TODO: syntax
BasicTypeName:
        VOID
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(VoidT.TYPE), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).type = VoidT.TYPE;

        }
        | CHAR
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.CHAR), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).seenChar = true;
        }
        | SHORT
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.SHORT), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).seenShort = true;
        }
        | INT
        {
          // See xtc.type.* for the class hiearchy for types
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.INT), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
                    getSpecsAt(subparser, 1).seenInt = true;
        }
        | __INT128
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.__INT128), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
                	  getSpecsAt(subparser, 1).seenInt = true;
        }
        | LONG
        {
          // See xtc.type.* for the class hiearchy for types
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.LONG), subparser.getPresenceCondition());
      	  setTransformationValue(value, tb);
                	  getSpecsAt(subparser, 1).longCount++;
        }
        | FLOAT
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.FLOAT), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
                    getSpecsAt(subparser, 1).seenFloat = true;
        }
        | DOUBLE
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(NumberT.DOUBLE), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).seenDouble = true;
        }
        | SignedKeyword
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder("signed"), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).seenSigned = true;
        }
        | UNSIGNED
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder("unsigned"), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          getSpecsAt(subparser, 1).seenUnsigned = true;
        }
        | _BOOL
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder(BooleanT.TYPE), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          	  getSpecsAt(subparser, 1).seenBool = true;
        }
        | ComplexKeyword
        {
          Multiverse<TypeBuilder> tb = new Multiverse<TypeBuilder>(new TypeBuilder("complex"), subparser.getPresenceCondition());
          setTransformationValue(value, tb);
          getSpecsAt(subparser, 1).seenComplex = true;
        }
        ;

// TODO: syntax
SignedKeyword:
        SIGNED
	{
	  System.err.println("TODO: use token");
	}
        | __SIGNED
	{
	  System.err.println("TODO: use token");
	}
        | __SIGNED__
	{
	  System.err.println("TODO: use token");
	}
        ;

// TODO: syntax
ComplexKeyword:
        _COMPLEX
	{
	  System.err.println("TODO: use token");
	}
        | __COMPLEX__
	{
	  System.err.println("TODO: use token");
	}
        ;

ElaboratedTypeName: /** passthrough, nomerge **/
        StructSpecifier
        {
        	setTransformationValue(value,
            (Multiverse<TypeBuilder>) getTransformationValue(subparser,1));
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

/**
 * This construct represents all possible configurations of a struct
 * specifier.  Struct specifiers are type specifiers, so they are
 * represented by (a subclass of) TypeBuilder.  To preserve all
 * configurations of it, these actions produce
 * Multiverse<TypeBuilder>.
 */
// transformation notes:
//   we can either take all combinations of declaration lists and make a new, renamed type spec
//   or we can combine all fields into a single struct, renaming the fields
StructSpecifier: /** nomerge **/  // ADDED attributes  // Multiverse<TypeBuilder>
        STRUCT LBRACE StructDeclarationList RBRACE
        {
          // legacy type checking
          Node tag     = null;
          Node members = getNodeAt(subparser, 2);
          Node attrs   = null;
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);

          List<Multiverse<Declaration>> structfields
            = (List<Multiverse<Declaration>>) getTransformationValue(subparser,2);

          // for anonymous structs, just take every combination and
          // make new declaration for it.  since there is no tag,
          // there is no way to reference this struct type again.

          // get scope to make an anonymous tag
          CContext scope = (CContext)subparser.scope;

          // TODO: make a new desugaring operator that turns a
          // List<Multiverse<Declaration>> into a
          // Multiverse<List<Declaration>>.  use for struct specifiers
          // and param lists

          // (1) start with an empty multiverse of declaration lists
          Multiverse<List<Declaration>> listsmv
            = new Multiverse<List<Declaration>>(new LinkedList<Declaration>(), subparser.getPresenceCondition());
          // (2) go through each declaration multiverse
          for (Multiverse<Declaration> structfield : structfields) {
            // (3) turn each declaration into a single-element list
            Multiverse<List<Declaration>> wrappeddeclarationmv = DesugaringOperators.declarationListWrap.transform(structfield);
            // (4) make a new multiverse of declaration form the
            // product of the previous with the single-element
            // declaration lists from (3), allowing for missing
            // declarations in some configurations
            // with complementedProduct
            Multiverse<List<Declaration>> newlistsmv
              = listsmv.complementedProduct(wrappeddeclarationmv, DesugaringOperators.DECLARATIONLISTCONCAT);
            wrappeddeclarationmv.destruct();
            listsmv.destruct();
            listsmv = newlistsmv;
          }

          // create a multiverse of struct types
          Multiverse<TypeBuilder> valuemv = new Multiverse<TypeBuilder>();
          for (Element<List<Declaration>> declarationlist : listsmv) {
            // give it an anonymous tag name (CAnalyzer)
            String structTag = freshName("anonymous");

            // no need to rename anonymous structs, since the tag is
            // not emitted
            TypeBuilder tb = new TypeBuilder();
            tb.setStructDefinition(structTag,  
                                   declarationlist.getData());
            valuemv.add(tb, declarationlist.getCondition());

            System.err.println("TODO: check if tb has an error before entering in symtab.");
            // use separate, global symtab for structs
            scope.put(structTag,
                       tb.toType(),
                       declarationlist.getCondition());
            System.err.println("STRUCTTYPE: " + tb.toType());
            // declared as this type
          }
          // should be non-empty, since we start with a single entry multiverse containing an empty list
          assert ! valuemv.isEmpty();
          
        	setTransformationValue(value, valuemv);
        }
        | STRUCT IdentifierOrTypedefName LBRACE StructDeclarationList RBRACE
        {

          // for tagged structs, always replace it with a reference to
          // the original tag name.  save each configuration of the
          // struct in the global namespace, so that we can later emit
          // all of the (renamed) variations at the top of output and
          // use a union-based struct for the original struct tag.

          Node tag     = getNodeAt(subparser, 4);
          Node members = getNodeAt(subparser, 2);
          Node attrs   = null;
          updateSpecs(subparser,
                      makeStructSpec(subparser, tag, members, attrs),
                      value);

          String structTag = ((Syntax) getNodeAt(subparser, 4).get(0)).getTokenText();
          List<Multiverse<Declaration>> structfields
            = (List<Multiverse<Declaration>>) getTransformationValue(subparser, 2);

          // hoist all possible combinations of struct fields
          
          // (1) start with an empty multiverse of declaration lists
          Multiverse<List<Declaration>> listsmv
            = new Multiverse<List<Declaration>>(new LinkedList<Declaration>(), subparser.getPresenceCondition());
          // (2) go through each declaration multiverse
          for (Multiverse<Declaration> structfield : structfields) {
            // (3) turn each declaration into a single-element list
            Multiverse<List<Declaration>> wrappeddeclarationmv = DesugaringOperators.declarationListWrap.transform(structfield);
            // (4) make a new multiverse of declaration form the
            // product of the previous with the single-element
            // declaration lists from (3), allowing for missing
            // declarations in some configurations
            // with complementedProduct
            Multiverse<List<Declaration>> newlistsmv
              = listsmv.complementedProduct(wrappeddeclarationmv, DesugaringOperators.DECLARATIONLISTCONCAT);
            wrappeddeclarationmv.destruct();
            listsmv.destruct();
            listsmv = newlistsmv;
          }
          // listsmv contains a multiverse of declaration lists

          // TODO: track when a struct is being redeclared in some
          // configuration, which should be possible from the symtab
          
          CContext scope = (CContext)subparser.scope;

          Multiverse<TypeBuilder> valuemv = new Multiverse<TypeBuilder>();
          Multiverse<SymbolTable.Entry> entries = scope.getCurrentScope(CContext.toTagName(structTag), subparser.getPresenceCondition());
          for (Element<SymbolTable.Entry> entry : entries) {
            if (entry.getData() == SymbolTable.ERROR) {
              System.err.println(String.format("INFO: trying to use an invalid specifier: %s", structTag));
              TypeBuilder typebuilder = new TypeBuilder();
              typebuilder.setTypeError();
              valuemv.add(typebuilder, entry.getCondition());
              // no need to add to symtab since this config is
              // already an error
            } else if (entry.getData() == SymbolTable.UNDECLARED) {
              // create a multiverse of struct types
              for (Element<List<Declaration>> declarationlist : listsmv) {
                String renamedTag = freshCId(structTag);
                PresenceCondition combinedCond = entry.getCondition().and(declarationlist.getCondition());

                TypeBuilder typebuilder = new TypeBuilder();
                typebuilder.setStructDefinition(structTag, renamedTag, declarationlist.getData());

                if (! typebuilder.hasTypeError()) {
                  scope.put(CContext.toTagName(structTag),
                            typebuilder.toType(),
                            combinedCond);
                  StringBuilder sb = new StringBuilder();
                  sb.append(typebuilder.toString());
                  // TODO: syntax list
                  sb.append(";\n");
                  scope.addDeclaration(sb.toString());
                  todoReminder("record struct renamings as well");
                } else {
                  scope.putError(CContext.toTagName(structTag), combinedCond);
                }
                
                // just use a struct ref for the transformation value, since
                // we will print all struct defs at the top of the scope in
                // the output
                TypeBuilder reftypebuilder = new TypeBuilder();
                reftypebuilder.setStructReference(structTag, structTag);
                valuemv.add(reftypebuilder, combinedCond);
              }
            } else {
              System.err.println(String.format("INFO: trying redefine a struct: %s", structTag));
              TypeBuilder typebuilder = new TypeBuilder();
              typebuilder.setStructReference(structTag, structTag);  // set a struct ref for later error output
              typebuilder.setTypeError();
              valuemv.add(typebuilder, entry.getCondition());

              // this configuration has a type error entry
              scope.putError(CContext.toTagName(structTag), entry.getCondition());
            }
          }
          // should not be empty because symtab.get is not supposed
          // to be empty
          assert ! valuemv.isEmpty();

          setTransformationValue(value, valuemv);
        }
        | STRUCT IdentifierOrTypedefName
        {
          // get scope to make an anonymous tag
          CContext scope = (CContext)subparser.scope;

          String structTag = ((Syntax) getNodeAt(subparser, 1).get(0)).getTokenText();

          // global structs are handled by compositing every (renamed)
          // field, so their renaming entry should just be the
          // original name

          // forward references are not allowed in local scope, so
          // we can just use the renamed struct from the symtab
          
          Multiverse<TypeBuilder> valuemv = new Multiverse<TypeBuilder>();
          Multiverse<SymbolTable.Entry> entries = scope.getAnyScope(CContext.toTagName(structTag),
                                                                    subparser.getPresenceCondition());
          for (Element<SymbolTable.Entry> entry : entries) {
            TypeBuilder typebuilder = new TypeBuilder();
            if (entry.getData() == SymbolTable.ERROR) {
              System.err.println(String.format("INFO: trying to use an invalid specifier: %s", structTag));
              typebuilder.setTypeError();
            } else if (entry.getData() == SymbolTable.UNDECLARED) {
              System.err.println(String.format("TODO: local structs must be defined before being used, unless it's a pointer to a struct: %s", structTag));
              /* typebuilder.setTypeError(); */
              typebuilder.setStructReference(structTag, structTag);
            } else {
              assert entry.getData().getType().isStruct() || entry.getData().getType().isUnion();
              if (entry.getData().getType().isStruct()) {
                // just use the original tag name, since we will use a
                // union type for it
                typebuilder.setStructReference(structTag, structTag);
                /* typebuilder.setStructReference(structTag, */
                /*                                entry.getData().getType().toStruct().getName()); */
              } else {
                System.err.println("TODO: expected a struct type in the tag namespace.  this is either a bug or due to mishandling of union types.");
                System.exit(1);
                typebuilder.setTypeError();
              }
            }
            valuemv.add(typebuilder, entry.getCondition());
          }
          // should not be empty because symtab.get is not supposed
          // to be empty
          assert ! valuemv.isEmpty();
          setTransformationValue(value, valuemv);
        }
        | STRUCT AttributeSpecifierList { EnterScope(subparser); } LBRACE
          StructDeclarationList { ExitScope(subparser); }
        RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: StructSpecifier (4)");
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
          System.err.println("WARNING: unsupported semantic action: StructSpecifier (5)");
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
          System.err.println("WARNING: unsupported semantic action: StructSpecifier (6)");
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
/*
 * This construct returns a list of declaration multiverses, i.e., a
 * list of declarations, where each declaration may be different
 * depending on the configuration.
 */
StructDeclarationList: /** list, nomerge **/  // List<Multiverse<Declaration>>
        /* StructDeclaration */ /* ADDED gcc empty struct */
        {
          ((Node) value).setProperty(SPECS, new Specifiers()); // legacy type checking

          setTransformationValue(value, new LinkedList<Multiverse<Declaration>>());
        }
        | StructDeclarationList StructDeclaration {
          //legacy type checking
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);

          List<Multiverse<Declaration>> structfields
            = (LinkedList<Multiverse<Declaration>>) getTransformationValue(subparser,2);
          Multiverse<Declaration> declarationvalue
            = (Multiverse<Declaration>) getTransformationValue(subparser,1);
          structfields.add(declarationvalue);
          setTransformationValue(value, structfields);
        }
        ;

StructDeclaration: /** nomerge **/  // returns Multiverse<Declaration>
        StructDeclaringList SEMICOLON
        {
          // TODO: implement like Declaration, except return a
          // multiverse of declarations instead of strings
          
        	List<StructDeclaringListValue> declaringlistvalues = (List<StructDeclaringListValue>) getTransformationValue(subparser, 2);

          // take all combinations of type specifiers and declarators
          // and produce a multiverse of declaration objects.
          Multiverse<Declaration> resultmv = new Multiverse<Declaration>();
          for (StructDeclaringListValue declaringlistvalue : declaringlistvalues) {
            // unpack type specifier, declarators, and initializers from the transformation value
            Multiverse<TypeBuilder> typebuildermv = declaringlistvalue.typebuilder;
            Multiverse<Declarator> declaratormv = declaringlistvalue.declarator;
            
            for (Element<TypeBuilder> typebuilder : typebuildermv) {
              PresenceCondition typebuilderCond = subparser.getPresenceCondition().and(typebuilder.getCondition());
              for (Element<Declarator> declarator : declaratormv) {
                PresenceCondition combinedCond = typebuilderCond.and(declarator.getCondition());
                resultmv.add(new Declaration(typebuilder.getData(), declarator.getData()), combinedCond);
                combinedCond.delRef();
              } // end loop over declarators
              typebuilderCond.delRef();
            } // end loop over typebuilders
          } // end loop of declaring list values
          // should be non-empty since structdeclaringlist cannot be
          // empty
          assert ! resultmv.isEmpty();

          setTransformationValue(value, resultmv);
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

StructDeclaringList: /** list, nomerge **/  // returns List<StructDeclaringListValue>
        TypeSpecifier StructDeclarator AttributeSpecifierListOpt
        {
          List<StructDeclaringListValue> declaringlist = new LinkedList<StructDeclaringListValue>();
          Multiverse<TypeBuilder> typebuilders = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 3);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 2);
          System.err.println("TODO: support attribuetspecifierlistopt in StructDeclarator");
          declaringlist.add(new StructDeclaringListValue(typebuilders, declarators));
          setTransformationValue(value, declaringlist);
        }
        | StructDeclaringList COMMA StructDeclarator AttributeSpecifierListOpt
        {
          List<StructDeclaringListValue> declaringlist = (List<StructDeclaringListValue>) getTransformationValue(subparser, 4);
          assert declaringlist.size() > 0;
          Multiverse<TypeBuilder> typebuilders = declaringlist.get(0).typebuilder;
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 2);
          System.err.println("TODO: support attribuetspecifierlistopt in StructDeclarator");
          declaringlist.add(new StructDeclaringListValue(typebuilders, declarators));
          setTransformationValue(value, declaringlist);
        }
        ;


StructDeclarator: /** nomerge **/  // returns Multiverse<Declarator>
        Declarator BitFieldSizeOpt
        {
          System.err.println("TODO: support bitfieldsizeopt in a new StructDeclarator");
          setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser, 2));
        }
        | BitFieldSize
        {
          System.err.println("WARNING: unsupported semantic action: StructDeclarator (2)");
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

ParameterTypeList:  /** nomerge **/  // List<Multiverse<Declaration>>
        ParameterList
        {
          setTransformationValue(value, (List<Multiverse<Declaration>>) getTransformationValue(subparser,1));
        }
        | ParameterList COMMA ELLIPSIS
        {
          List<Multiverse<Declaration>> paramlist
            = (List<Multiverse<Declaration>>) getTransformationValue(subparser,3);
          System.err.println("TODO: support variadic parameter lists");  // add a special parameterdeclarationvalue to the list
          setTransformationValue(value, paramlist);
        }
        ;

// returns a multiverse of nonconfigurable parameter lists
ParameterList:  /** list, nomerge **/ // List<Multiverse<Declaration>>
        ParameterDeclaration
        {
          // create a new list
          List<Multiverse<Declaration>> parameters
            = new LinkedList<Multiverse<Declaration>>();
          Multiverse<Declaration> declarationvalue
            = (Multiverse<Declaration>) getTransformationValue(subparser,1);
          parameters.add(declarationvalue);
          setTransformationValue(value, parameters);
        }
        | ParameterList COMMA ParameterDeclaration
        {
          // add to the existing parameter list.  this reuse of a
          // semantic value may be an issue if static conditionals are
          // permitted under parameterlists
          List<Multiverse<Declaration>> parameters
            = (LinkedList<Multiverse<Declaration>>) getTransformationValue(subparser,3);
          Multiverse<Declaration> declarationvalue
            = (Multiverse<Declaration>) getTransformationValue(subparser,1);
          parameters.add(declarationvalue);
          setTransformationValue(value, parameters);
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

ParameterDeclaration:  /** nomerge **/  // Multiverse<Declaration>
        /*
         * This action, akin to declaration, adds each parameter
         * declaration to the (function-local) symtab.  It handles
         * renaming.  The difference is that this needs to return
         * declarators because it is actually part of another
         * different declarator (FunctionDeclarator).
         */
        ParameterIdentifierDeclaration
        {
          ParameterDeclarationValue declarationvalue = (ParameterDeclarationValue) getTransformationValue(subparser,1);

          CContext scope = (CContext)subparser.scope;
          
          // create a multiverse of parameterdeclarators and add the
          // symbols to the function-local symbol table, which
          // PostfixingFunctionDeclarator enters and exits, before
          // FunctionDefinition reenters and exits.
          Multiverse<Declaration> valuemv = new Multiverse<Declaration>();
          for (Element<TypeBuilder> typebuilder : declarationvalue.typebuilder) {
            PresenceCondition typebuilderCond = subparser.getPresenceCondition().and(typebuilder.getCondition());
            for (Element<Declarator> declarator : declarationvalue.declarator) {
              PresenceCondition combinedCond = typebuilderCond.and(declarator.getCondition());

              // for each combination of typebuilder and declarator

              // (1) rename the declarator part and create a
              // Declaration for use as the semantic value
              String originalName = declarator.getData().getName();
              String renaming = freshCId(originalName);
              Declarator renamedDeclarator = declarator.getData().rename(renaming);
              Declaration renamedDeclaration = new Declaration(typebuilder.getData(),
                                                               renamedDeclarator);

              valuemv.add(renamedDeclaration, combinedCond);

              // (2) add the parameter to the symbol table
              if (typebuilder.getData().hasTypeError()) {
                scope.putError(declarator.getData().getName(), combinedCond);
              } else {
                // getName() shouldn't have an error, because thit is
                // the identifierdeclaration.  abstract declarators
                // can't go in the symbol table, because there is no
                // symbol.
                Multiverse<SymbolTable.Entry> entries = scope.getCurrentScope(declarator.getData().getName(), combinedCond);

                // TODO: check for multiply-defined parameter names,
                // which (I believe) should make the entire function
                // declarator invalid.

                for (Element<SymbolTable.Entry> entry : entries) {
                  if (entry.getData() == SymbolTable.ERROR) {
                    System.err.println("INFO: invalid parameter declaration for function");
                    System.err.println("TODO: any invalid parameter declarations should cause the entire function declaration to be invalid under that condition");
                    scope.putError(declarator.getData().getName(), combinedCond);
                  } else if (entry.getData() == SymbolTable.UNDECLARED) {
                    // get the type and add it to the symtab
                    Type type = VariableT.newParam(renamedDeclaration.getType(),
                                                   renamedDeclaration.getName());
                    scope.put(originalName, type, entry.getCondition());
                  } else {
                    System.err.println("INFO: reuse of the same parameter name in function");
                    System.err.println("TODO: any invalid parameter declarations should cause the entire function declaration to be invalid under that condition");
                    scope.putError(declarator.getData().getName(), combinedCond);
                  }  // end test of symtab entry type
                } // end loop over symtab entries
              } // end of check for invalid typebuilder

              combinedCond.delRef();
            } // end loop over declarators
            typebuilderCond.delRef();
          } // end loop over typebuilders
          // should be non-empty because
          // parameteridentifierdeclaration should always return a
          // typebuildermv and declaratormv
          assert ! valuemv.isEmpty();

          /* if (debug) System.err.println(context.getSymbolTable()); */

          setTransformationValue(value, valuemv);
        }
        | ParameterAbstractDeclaration
        {
          // TODO: needs a unit test
          ParameterDeclarationValue declarationvalue = (ParameterDeclarationValue) getTransformationValue(subparser,1);
          
          // create a multiverse of parameterdeclarators
          Multiverse<Declaration> valuemv = new Multiverse<Declaration>();
          for (Element<TypeBuilder> typebuilder : declarationvalue.typebuilder) {
            PresenceCondition typebuilderCond = subparser.getPresenceCondition().and(typebuilder.getCondition());
            for (Element<Declarator> declarator : declarationvalue.declarator) {
              PresenceCondition combinedCond = typebuilderCond.and(declarator.getCondition());
              Declaration declaration = new Declaration(typebuilder.getData(),
                                                        declarator.getData());

              // for each combination of typebuilder and declarator
              // create a Declaration for use in the semantic
              // value.  abstract declarators have no name, so should
              // not need to rename or add to a symtab.
              valuemv.add(declaration, combinedCond);
              
              combinedCond.delRef();
            } // end loop over declarators
            typebuilderCond.delRef();
          } // end loop over typebuilders
          // should be non-empty because
          // parameteridentifierdeclaration should always return a
          // typebuildermv and declaratormv
          assert ! valuemv.isEmpty();

          setTransformationValue(value, valuemv);
        }
        ;

/*
 * These actions just bundle the typebuilders and declarators for
 * processing by ParameterDeclaration
 */
ParameterAbstractDeclaration: // ParameterDeclarationValue
        DeclarationSpecifier
        {
          System.err.println("TODO: reimplement parameterabstractdeclaration (1)");
          System.exit(1);
        }
        | DeclarationSpecifier AbstractDeclarator
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 1);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationQualifierList
        {
          System.err.println("TODO: reimplement parameterabstractdeclaration (3)");
          System.exit(1);
        }
        | DeclarationQualifierList AbstractDeclarator
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 1);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          Multiverse<Declarator> declarators = new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier AbstractDeclarator
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 1);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeQualifierList
        {
          System.err.println("TODO: reimplement parameterabstractdeclaration (7)");
          System.exit(1);
        }
        | TypeQualifierList AbstractDeclarator
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 1);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        ;

/*
 * These actions just bundle the typebuilders and declarators for
 * processing by ParameterDeclaration
 */
ParameterIdentifierDeclaration:  // ParameterDeclarationValue
        DeclarationSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          Multiverse<TypeBuilder> types = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 4);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser, 3);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
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
          // get token text from the parent
        }
        | TYPEDEFname
        {
          // get token text from the parent
        }
        ;

TypeName: /** nomerge **/
        TypeSpecifier
        {
          Multiverse<TypeBuilder> type = (Multiverse<TypeBuilder>) getTransformationValue(subparser, 1);
          setTransformationValue(value, type);
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

InitializerOpt: /** nomerge **/ // ExpressionValue
        /* nothing */
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked InitializerOpt (1)");
          Multiverse<String> emptyInit = new Multiverse<String>("", subparser.getPresenceCondition());
          setTransformationValue(value, emptyInit);
        }
        | ASSIGN DesignatedInitializer
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked InitializerOpt (2)");
          // TODO: syntax
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        ;

DesignatedInitializer:/** nomerge, passthrough **/ /* ADDED */ // ExpressionValue
        Initializer
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked DesignatedInitializer (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<String> product = getProductOfSomeChildren(pc, child);
          setTransformationValue(value, product);
        }
        | Designation Initializer
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked DesignatedInitializer (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        ;

/*InitializerStandard:  // ADDED gcc can have empty Initializer lists
        LBRACE InitializerList RBRACE
        | AssignmentExpression
        ;*/

Initializer: /** nomerge **/  // ADDED gcc can have empty Initializer lists // ExpressionValue
        LBRACE MatchedInitializerList RBRACE
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked Initializer (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | LBRACE MatchedInitializerList DesignatedInitializer RBRACE
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked Initializer (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 4), getNodeAt(subparser, 3), getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | AssignmentExpression
        {
          todoReminder("initializers need to have expressionvalue since they need to be typechecked Initializer (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Node child = getNodeAt(subparser, 1);
          Multiverse<String> product = getProductOfSomeChildren(pc, child);
          setTransformationValue(value, product);
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
          Multiverse<String> s = new Multiverse<String>("", subparser.getPresenceCondition());
          setTransformationValue(value, s);
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
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | IdentifierDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

TypedefDeclarator:  /**  nomerge **/  // ADDED
        TypedefDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        ;

TypedefDeclaratorMain:  /**  nomerge **/
        ParenTypedefDeclarator  /* would be ambiguous as Parameter*/
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | ParameterTypedefDeclarator   /* not ambiguous as param*/
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

ParameterTypedefDeclarator: /** nomerge **/
        TYPEDEFname
        {
          System.err.println("TODO: do we need to expand all possible typedef names here? parametertypedefdeclarator");
          Multiverse<Declarator> valuemv = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 1)), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
        | TYPEDEFname PostfixingAbstractDeclarator
      	{
          Multiverse<Declarator> declarators = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 2)),
                                                                          subparser.getPresenceCondition());
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          declarators.destruct();  // safe to destruct because not added as transformation value
          /* abstractdeclarators.destruct(); */
          // no need to filter since declarators started with subparser's pc
          setTransformationValue(value, valuemv);
        }
        | CleanTypedefDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

    /*  The  following have at least one STAR. There is no (redundant)
    LPAREN between the STAR and the TYPEDEFname. */

CleanTypedefDeclarator: /** nomerge **/
        CleanPostfixTypedefDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | STAR ParameterTypedefDeclarator
      	{
          // TODO: do we need to conjoin with subparser.getPresenceCondition() in all these declarators?
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList ParameterTypedefDeclarator
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,2);
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

CleanPostfixTypedefDeclarator: /** nomerge **/
        LPAREN CleanTypedefDeclarator RPAREN
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        }
        | LPAREN CleanTypedefDeclarator RPAREN PostfixingAbstractDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,3);
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

    /* The following have a redundant LPAREN placed immediately  to  the
    left of the TYPEDEFname */

ParenTypedefDeclarator:  /** nomerge **/
        ParenPostfixTypedefDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | STAR LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,2);
          Multiverse<Declarator> valuemv = DesugaringOperators.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
      	| STAR TypeQualifierList
      	LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,4);
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,2);
          Multiverse<Declarator> valuemv = DesugaringOperators.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR ParenTypedefDeclarator
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList ParenTypedefDeclarator
      	{
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

ParenPostfixTypedefDeclarator: /** nomerge **/ /* redundant paren to left of tname*/
        LPAREN ParenTypedefDeclarator RPAREN
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        }
        | LPAREN SimpleParenTypedefDeclarator PostfixingAbstractDeclarator RPAREN /* redundant paren */
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,3);
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,2);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | LPAREN ParenTypedefDeclarator RPAREN PostfixingAbstractDeclarator
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,3);
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

SimpleParenTypedefDeclarator: /** nomerge **/
        TYPEDEFname
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | LPAREN SimpleParenTypedefDeclarator RPAREN
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        }
        ;

IdentifierDeclarator:  /**  nomerge **/
        IdentifierDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

IdentifierDeclaratorMain:  /** nomerge **/
        UnaryIdentifierDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        | ParenIdentifierDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        ;

UnaryIdentifierDeclarator: /** nomerge **/
        PostfixIdentifierDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        | STAR IdentifierDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
      	}
        | STAR TypeQualifierList IdentifierDeclarator
      	{
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
      	}
        ;

PostfixIdentifierDeclarator: /** nomerge **/
        FunctionDeclarator
        {
          setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | ArrayDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | AttributedDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | LPAREN UnaryIdentifierDeclarator RPAREN PostfixingAbstractDeclarator
      	{
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,3);
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

AttributedDeclarator: /** nomerge **/
        LPAREN UnaryIdentifierDeclarator RPAREN
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        }
        ;

FunctionDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator PostfixingFunctionDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,2);
          Multiverse<Declarator> parameters = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(parameters, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declaratorsmv.destruct(); */
          /* parametersmv.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

PostfixingFunctionDeclarator:  /** nomerge **/ // Multiverse<ParameterListDeclarator>
        LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN
        {
          // TODO: account for parameterdeclarationvalue that is the ellipsis
          List<Multiverse<Declaration>> parameterdeclaratorlistsmv
            = (List<Multiverse<Declaration>>) getTransformationValue(subparser,3);

          // find each combination of single-configuration parameter
          // lists.  not using a product, because it is combining two
          // different types, typebuilder and declarator.  perhaps
          // having a typebuilderdeclarator would make this possible.
          Multiverse<List<Declaration>> parametersmv
            = new Multiverse<List<Declaration>>(new LinkedList<Declaration>(), subparser.getPresenceCondition());
          for (Multiverse<Declaration> nextparameter : parameterdeclaratorlistsmv) {
            // take the product of that multiverse with the existing, hoisted list of parameters
            // (1) wrap each element of the multiverse in a list 
            Multiverse<List<Declaration>> nextparameterwrapped
              = DesugaringOperators.declarationListWrap.transform(nextparameter);
            // (2) take the product of the existing parameter list
            // with the new, single-element parameter list, allowing
            // for missing parameters in some configurations
            // complementedProduct
            Multiverse<List<Declaration>> newparametersmv
              = parametersmv.complementedProduct(nextparameterwrapped, DesugaringOperators.DECLARATIONLISTCONCAT);
            nextparameterwrapped.destruct();
            parametersmv.destruct();
            // (3) use the new list for the next iteration
            parametersmv = newparametersmv;
          }
          // parametersmv should now contains all possible
          // single-configuration parameter lists

          // (4) transform the resulting List<Declaration>
          // into a ParameterListDeclarator, so that it can be used in
          // the Declarator AST
          Multiverse<ParameterListDeclarator> paramlistmv = DesugaringOperators.toParameterList.transform(parametersmv);
          parametersmv.destruct();
          // no need to filter, since we started parametersmv with the subparser pc
          setTransformationValue(value, paramlistmv);
        }
        ;

ArrayDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator ArrayAbstractDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,2);
          Multiverse<Declarator> arrayabstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(arrayabstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        ;

ParenIdentifierDeclarator:  /** nomerge **/
        SimpleDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        | LPAREN ParenIdentifierDeclarator RPAREN
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
      	}
        ;

SimpleDeclarator: /** nomerge **/
        IDENTIFIER  /* bind */
        {
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 1)), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
        ;

OldFunctionDeclarator: /** nomerge **/
        PostfixOldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
        }
        | STAR OldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
        }
        | STAR TypeQualifierList OldFunctionDeclarator
        {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
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
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | PostfixAbstractDeclarator
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        | PostfixingAbstractDeclarator
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

PostfixingAbstractDeclarator: /**  nomerge **/
        ArrayAbstractDeclarator
      	{
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
      	}
        /* | LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN */
        | PostfixingFunctionDeclarator
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,1));
        }
        ;

ParameterTypeListOpt: /** nomerge **/  // List<Multiverse<Declaration>>
        /* empty */
        {
          setTransformationValue(value, new LinkedList<Multiverse<Declaration>>());
        }
        | ParameterTypeList
        {
          setTransformationValue(value, (List<Multiverse<Declaration>>) getTransformationValue(subparser,1));
        }
        ;

ArrayAbstractDeclarator: /** nomerge **/
        LBRACK RBRACK
        {
          String expression = "";
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new ArrayAbstractDeclarator(expression), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
        | LBRACK ConstantExpression RBRACK
        {
          todoReminder("check expression in ArrayAbstractDeclarator (2)");
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);
          
          Multiverse<String> arrayBounds = exprval.transformation;
          Multiverse<Declarator> valuemv = DesugaringOperators.toAbstractArrayDeclarator.transform(arrayBounds);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
	      }
        | ArrayAbstractDeclarator LBRACK ConstantExpression RBRACK
	      {
          todoReminder("check expression in ArrayAbstractDeclarator (2)");
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);

      	  Multiverse<Declarator> arrayabstractdeclarator = (Multiverse<Declarator>) getTransformationValue(subparser,4);
          Multiverse<String> arrayBounds = exprval.transformation;

          // get each combination of the existing array abstract declarators and the new constant expressions
          // TODO: is there a way to do this with product?  harder because not combining the same types
          Multiverse<Declarator> valuemv = new Multiverse<Declarator>();
          for (Element<Declarator> declarator : arrayabstractdeclarator) {
            PresenceCondition declaratorCond = subparser.getPresenceCondition().and(declarator.getCondition());
            for (Element<String> expression : arrayBounds) {
              PresenceCondition combinedCondition = declaratorCond.and(expression.getCondition());
              valuemv.add(new ArrayAbstractDeclarator((ArrayAbstractDeclarator) declarator.getData(),
                                                 expression.getData()),
                     combinedCondition);
              combinedCondition.delRef();
            }
            declaratorCond.delRef();
          }
          // should be non-empty because arrayabstractdeclarator
          // returns a non-empty multiverse.  an array abstract
          // declarator, i.e., [], will be a single-element multiverse
          // containing the empty string
          assert ! valuemv.isEmpty();
          /* arrayabstractdeclarator.destruct(); */
          setTransformationValue(value, valuemv);;
	      }
        ;

UnaryAbstractDeclarator: /** nomerge **/
        STAR
        {
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new PointerAbstractDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);
        }
        | STAR TypeQualifierList
        {
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.toQualifiedPointerAbstractDeclarator.transform(qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR AbstractDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList AbstractDeclarator
        {
          Multiverse<TypeBuilder> qualifierlists = (Multiverse<TypeBuilder>) getTransformationValue(subparser,2);
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = DesugaringOperators.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
      	}
        ;

PostfixAbstractDeclarator: /** nomerge **/
        LPAREN UnaryAbstractDeclarator RPAREN
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        } 
        | LPAREN PostfixAbstractDeclarator RPAREN
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        } 
        | LPAREN PostfixingAbstractDeclarator RPAREN
        {
      	  setTransformationValue(value, (Multiverse<Declarator>) getTransformationValue(subparser,2));
        } 
        | LPAREN UnaryAbstractDeclarator RPAREN PostfixingAbstractDeclarator
        {
          Multiverse<Declarator> declarators = (Multiverse<Declarator>) getTransformationValue(subparser,3);
          Multiverse<Declarator> abstractdeclarators = (Multiverse<Declarator>) getTransformationValue(subparser,1);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugaringOperators.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        } 
        ;

// ---------------------------------------------------------------- Statements


// TODO: passthrough transformation value
/*
use this to get one pc for all errors in the types
PresenceCondition errorCond = typemv.getPresenceCondition(ErrorT.TYPE);
 */
Statement:  /** complete **/  // Multiverse<String>
        LabeledStatement
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | CompoundStatement
        {
	  // NOTE: calling emitStatement() here can also break switch cases.
          PresenceCondition pc = subparser.getPresenceCondition();
          // compound statements contain already-hoisted constructs
          // (declarations and statements), so just wrap this in a
          // single-element multiverse
          Multiverse<String> valuemv
            = new Multiverse<String>((String) getTransformationValue(subparser, 1), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);
        }
        | ExpressionStatement
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | SelectionStatement
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | IterationStatement
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | JumpStatement
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | AssemblyStatement  // ADDED
        {
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        ;

LabeledStatement:  /** complete **/  // ADDED attributes
        IdentifierOrTypedefName COLON AttributeSpecifierListOpt Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression COLON Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | CASE ConstantExpression ELLIPSIS ConstantExpression COLON Statement  // ADDED case range
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LabeledStatement");
          System.exit(1);
        }
        | DEFAULT COLON Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
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
          System.err.println("TODO: compoundstatement maybe need to reenter scope rather than enterscope to support for loops with declarations");
          PresenceCondition pc = subparser.getPresenceCondition();
          
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(getNodeAt(subparser, 6).getTokenText());
          valuesb.append(concatAllStrings(getNodeAt(subparser, 4), subparser.getPresenceCondition()));

          // print user-defined type declarations at top of scope
          CContext scope = ((CContext) subparser.scope);
          valuesb.append(scope.getDeclarations(subparser.getPresenceCondition()));

          valuesb.append((String) getTransformationValue(subparser, 3));
          valuesb.append(getNodeAt(subparser, 1).getTokenText());
          setTransformationValue(value, valuesb.toString());
        }
        ;

LocalLabelDeclarationListOpt: /** complete **/
        /* empty */
        {
          setTransformationValue(value, "");
        }
        | LocalLabelDeclarationList
        {
          System.err.println("implement locallabeldeclarationlistopt (2)");
          // do hoisting here, return a stringbuilder, not a multiverse
          System.exit(1);
        }
        ;

LocalLabelDeclarationList:  /** list, complete **/
        LocalLabelDeclaration
        {
          System.err.println("implement locallabeldeclarationlist (1)");
          System.exit(1);
        }
        | LocalLabelDeclarationList LocalLabelDeclaration
        {
          System.err.println("implement locallabeldeclarationlist (2)");
          System.exit(1);
        }
        ;

LocalLabelDeclaration: /** complete **/  /* ADDED */
        __LABEL__ LocalLabelList SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LocalLabelDeclaration");
          System.exit(1);
        }
        ;

LocalLabelList:  /** list, complete **/  // ADDED
        IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        | LocalLabelList COMMA IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
        ;

DeclarationOrStatementList:  /** list, complete **/  /* ADDED */
        /* empty */
        {
          setTransformationValue(value, "");
        }
        | DeclarationOrStatementList DeclarationOrStatement
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(concatAllStrings(getNodeAt(subparser, 2), subparser.getPresenceCondition()));
          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          setTransformationValue(value, valuesb.toString());
        }
        ;

DeclarationOrStatement: /** complete **/  /* ADDED */
        DeclarationExtension
        {
          // declarations are already hoisted, so just pass through the strinbguilder
          setTransformationValue(value, (String) getTransformationValue(subparser, 1));
        }
        | Statement
        {
          // hoist all statements here, that declaratinorstatement is just a string
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1));

          /* StringBuilder allStatements = new StringBuilder(); */

          /* allStatements.append("\n{"); */
          /* for (Multiverse.Element<StringBuilder> statement : product) { */
          /*   PresenceCondition combinedCond = statement.getCondition().and(subparser.getPresenceCondition()); */
          /*   allStatements.append("\nif (" + */
          /*   condToCVar(combinedCond) + */
          /*   ") {\n" + statement.getData().toString() + "\n}\n"); */
          /*   combinedCond.delRef(); */
          /* } */
          /* allStatements.append("\n}"); */

          /* setTransformationValue(value, allStatements); */
          setTransformationValue(value, emitStatement(product, pc));
        }
        | NestedFunctionDefinition
        {
          System.err.println("nestedfunctiondefinition not implemented yet");
          System.exit(1);
        }
        ;

DeclarationList:  /** list, complete **/
        DeclarationExtension
        {
          setTransformationValue(value, concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | DeclarationList DeclarationExtension
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(concatAllStrings(getNodeAt(subparser, 2), subparser.getPresenceCondition()));
          valuesb.append(concatAllStrings(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
          setTransformationValue(value, valuesb.toString());
        }
        ;

/*StatementList:
        Statement
        | StatementList Statement
        ;*/

ExpressionStatement:  /** complete **/  // Multiverse<String>
        ExpressionOpt SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);
          Multiverse<Type> exprtype = exprval.type;
          PresenceCondition errorCond = exprtype.getConditionOf(ErrorT.TYPE);
          System.err.println("EXPTYP: " + exprtype);

          Multiverse<String> valuemv;
          if (! exprval.isAlwaysError()) {
            Multiverse<String> expr = exprval.transformation;
            Multiverse<String> semi
              = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);

            valuemv = productAll(DesugaringOperators.concatStrings, expr, semi);
            // if filtering of type errors is done right, this add
            // should not violate mutual-exclusion in the multiverse
            // TODO: use dce and other optimizations to remove superfluous __static_type_error calls
            todoReminder("add emitError back to ExpressionStatement once type checking is done");
            /* valuemv.add(emitError("type error"), errorCond); */
          } else {
            valuemv = new Multiverse<String>(emitError("type error"), errorCond);
          }
          assert valuemv != null;
          System.err.println("EXPSMT: " + valuemv);
          
          errorCond.delRef();
          setTransformationValue(value, valuemv);
        }
        ;

SelectionStatement:  /** complete **/
        IF LPAREN Expression RPAREN Statement
        {
          todoReminder("check the type of the conditional expression SelectionStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 3);

          Multiverse<String> ifmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc);
          Multiverse<String> lparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 4)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> rparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> stmtmv = (Multiverse<String>) getTransformationValue(subparser, 1);

          setTransformationValue(value, productAll(DesugaringOperators.concatStrings,
                                                   ifmv,
                                                   lparenmv,
                                                   exprmv,
                                                   rparenmv,
                                                   stmtmv));
        }
        | IF LPAREN Expression RPAREN Statement ELSE Statement
        {
          todoReminder("check the type of the conditional expression SelectionStatement (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 5);

          Multiverse<String> ifmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 7)).getTokenText(), pc);
          Multiverse<String> lparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 6)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> rparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 4)).getTokenText(), pc);
          Multiverse<String> ifbranchmv = (Multiverse<String>) getTransformationValue(subparser, 3);
          Multiverse<String> elsemv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> elsebranchmv = (Multiverse<String>) getTransformationValue(subparser, 1);

          setTransformationValue(value, productAll(DesugaringOperators.concatStrings,
                                                   ifmv,
                                                   lparenmv,
                                                   exprmv,
                                                   rparenmv,
                                                   ifbranchmv,
                                                   elsemv,
                                                   elsebranchmv));
        }
        | SWITCH LPAREN Expression RPAREN Statement
        {
          System.err.println("TODO: switch statement");
          System.exit(1);
        }
        ;

IterationStatement:  /** complete **/
        WHILE LPAREN Expression RPAREN Statement
        {
          todoReminder("check the type of the conditional expression IterationStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 3);

          Multiverse<String> whilemv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc);
          Multiverse<String> lparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 4)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> rparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> stmtmv = (Multiverse<String>) getTransformationValue(subparser, 1);

          setTransformationValue(value, productAll(DesugaringOperators.concatStrings,
                                                   whilemv,
                                                   lparenmv,
                                                   exprmv,
                                                   rparenmv,
                                                   stmtmv));
        }
        | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON
        {
          todoReminder("check the type of the conditional expression IterationStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 3);

          Multiverse<String> domv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 7)).getTokenText(), pc);
          Multiverse<String> stmtmv = (Multiverse<String>) getTransformationValue(subparser, 6);
          Multiverse<String> whilemv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc);
          Multiverse<String> lparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 4)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> rparenmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> semimv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);

          setTransformationValue(value, productAll(DesugaringOperators.concatStrings,
                                                   domv,
                                                   stmtmv,
                                                   whilemv,
                                                   lparenmv,
                                                   exprmv,
                                                   rparenmv,
                                                   semimv));
        }
        | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: IterationStatement (6)");
          System.exit(1);
        }
        // n1570 6.8.5 Iteration statements allows for a declaration in the initializer of a for loop
        | FOR LPAREN Declaration ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        {
          // TODO: use a reentrant scope to add the declaration's symbol to the for-loop's scope
          // TODO: Declaration returns a String, not a multiverse.  We need a multiverse to hoist around the entire for loop.
          // TODO: consider rewriting this to put the declaration outside the for loop.  since it's renamed, we should have conflicts, and it resolves issues with scope and semantic values
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: IterationStatement (7)");
          System.exit(1);
        }
        ;

JumpStatement:  /** complete **/
        GotoStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | ContinueStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | BreakStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        | ReturnStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, getProductOfSomeChildren(subparser.getPresenceCondition(), getNodeAt(subparser, 1)));
        }
        ;

GotoStatement:  /** complete **/
        GOTO IdentifierOrTypedefName SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        | GOTO STAR Expression SEMICOLON  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("WARNING: unsupported semantic action: GotoStatement");
          System.exit(1);
        }
        ;

ContinueStatement:  /** complete **/
        CONTINUE SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        ;

BreakStatement:  /** complete **/
        BREAK SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        ;

ReturnStatement:  /** complete **/
        RETURN ExpressionOpt SEMICOLON
        {
          todoReminder("check the type of the return value");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);

          Multiverse<String> returnmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> semimv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);

          setTransformationValue(value, productAll(DesugaringOperators.concatStrings,
                                                   returnmv,
                                                   exprmv,
                                                   semimv));
        }
        ;

// --------------------------------------------------------------- Expressions

/* CONSTANTS */
Constant: /** passthrough, nomerge **/  // ExpressionValue
        FLOATINGconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     NumberT.FLOAT, subparser.getPresenceCondition()));
        }
        | INTEGERconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     NumberT.INT, subparser.getPresenceCondition()));
          // TODO: check whether INT is correct here, or whether we
          // need to look at the token itself to determine long, etc.
        }
        /* We are not including ENUMERATIONConstant here  because  we
        are  treating  it like a variable with a type of "enumeration
        Constant".  */
        | OCTALconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     NumberT.INT, subparser.getPresenceCondition()));
        }
        | HEXconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     NumberT.INT, subparser.getPresenceCondition()));
        }
        | CHARACTERconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     NumberT.CHAR, subparser.getPresenceCondition()));
        }
        ;

/* STRING LITERALS */
// TODO: unit tests
StringLiteralListString:  /** list, nomerge **/ // String
        STRINGliteral
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | StringLiteralListString STRINGliteral
        {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append((String) getTransformationValue(subparser, 2));
          valuesb.append(((Syntax) getNodeAt(subparser, 1)).getTokenText());
          setTransformationValue(value, valuesb.toString());
        }
        ;

// This nontermal just adds type information to the string literal
StringLiteralList:  /** list, nomerge **/ // ExpressionValue
        StringLiteralListString
        {
          // TODO: CAnalyzer distinguishes between wide and non-wide characters
          // TODO: use a fixed-size array instead of a pointer to char
          setTransformationValue(value,
                                 new ExpressionValue((String) getTransformationValue(subparser, 1),
                                                     new PointerT(NumberT.CHAR),
                                                     subparser.getPresenceCondition()));
        }
        ;


/* EXPRESSIONS */
PrimaryExpression:  /** nomerge, passthrough **/ // ExpressionValue
        PrimaryIdentifier
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | Constant
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | StringLiteralList
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | LPAREN Expression RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);

          Multiverse<String> lparenmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> rparenmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings, lparenmv, exprmv, rparenmv),
                                                     exprval.type));
          lparenmv.destruct(); rparenmv.destruct();
        }
        | StatementAsExpression  // ADDED
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | VariableArgumentAccess  // ADDED
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        ;

PrimaryIdentifier: /** nomerge **/ // ExpressionValue
        IDENTIFIER
        {
          useIdent(subparser, getNodeAt(subparser, 1));  // legacy type checking
          
          String originalName = ((Node)getNodeAt(subparser, 1)).getTokenText();
          //Multiverse<String> sbmv = new Multiverse<String>();
          //sbmv.add(new Element<String>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));

          CContext scope = (CContext) subparser.scope;

          // get the renamings from the symtab
          PresenceCondition cond = subparser.getPresenceCondition().presenceConditionManager().newTrue();
          Multiverse<SymbolTable.Entry> entries = scope.getAnyScope(originalName, cond);
          cond.delRef();

          // convert the renamings to stringbuilders
          Multiverse<String> sbmv = new Multiverse<String>();
          Multiverse<Type> typemv = new Multiverse<Type>();
          // any presence conditions with an error can be omitted from
          // the desugaring.  instead, this information is preserved
          // in the type value for use by the statement.
          for (Element<SymbolTable.Entry> entry : entries) {
            if (entry.getData() == SymbolTable.ERROR) {
              System.err.println(String.format("type error: use of symbol with invalid declaration: %s", originalName));
              typemv.add(ErrorT.TYPE, entry.getCondition());
            } else if (entry.getData() == SymbolTable.UNDECLARED) {
              System.err.println(String.format("type error: use of undeclared symbol: %s", originalName));
              typemv.add(ErrorT.TYPE, entry.getCondition());
            } else {
              // TODO: add type checking.  may need to tag the resulting
              // stringbuilder with the type to handle this

              if (entry.getData().getType().isVariable()) {
                String result  // use the renamed symbol
                  = String.format(" %s ", entry.getData().getType().toVariable().getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(entry.getData().getType().toVariable().getType(), entry.getCondition());
              } else if (entry.getData().getType() instanceof NamedFunctionT) {
                String result  // use the renamed symbol
                  = String.format(" %s ", ((NamedFunctionT) entry.getData().getType()).getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(((NamedFunctionT) entry.getData().getType()), entry.getCondition());
              } else {
                System.err.println(String.format("type error: use of symbol other than variable or function: %s", originalName));
                typemv.add(ErrorT.TYPE, entry.getCondition());
              }
            }
          }
          // should be nonempty, since the above loop always adds to
          // it and the symtab should always return a non-empty mv
          assert ! sbmv.isEmpty();
          entries.destruct();

          System.err.println(sbmv);
          System.err.println(typemv);

          setTransformationValue(value, new ExpressionValue(sbmv, typemv));
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

PostfixExpression:  /** passthrough, nomerge **/ // ExpressionValue
        PrimaryExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | Subscript
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | FunctionCall
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | DirectSelection
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | IndirectSelection
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | Increment
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | Decrement
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | CompoundLiteral  /* ADDED */
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        ;

Subscript:  /** nomerge **/
        PostfixExpression LBRACK Expression RBRACK
        {
          // TODO: check that expression is numeric, check that postfixexpression is array, and get arrays types
          System.err.println("TODO: Subscript");
          System.exit(1);
        }
        ;

FunctionCall:  /** nomerge **/
        PostfixExpression LPAREN RPAREN
        {
          todoReminder("typecheck functioncall (1)");
          // type check by making sure the postfixexpression type is a
          // function, has no params, and setting the return value to
          // the type
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 3);

          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> lparen = new Multiverse<String>((String) getNodeAt(subparser, 2).getTokenText(), pc);
          Multiverse<String> rparen = new Multiverse<String>((String) getNodeAt(subparser, 1).getTokenText(), pc);

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                exprmv,
                                                                lparen,
                                                                rparen),
                                                     exprval.type));  // TODO: placeholder until type checking
        }
        | PostfixExpression LPAREN ExpressionList RPAREN
        {
          // type check by making sure the postfixexpression type is a
          // function, that each type of the expressionlist matches
          // each type of the function types's list, and setting the
          // return value to the type
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue postfixexprval = (ExpressionValue) getTransformationValue(subparser, 4);

          if (postfixexprval.hasValidType()) {
            /* postfixexprval.transformation; */
            Multiverse<String> lparen
              = new Multiverse<String>((String) getNodeAt(subparser, 3).getTokenText(), pc);
            Multiverse<String> rparen
              = new Multiverse<String>((String) getNodeAt(subparser, 1).getTokenText(), pc);

            // Get all possible expression lists by successively taking
            // the combined product of each element of the list.  See
            // postfixingfunctiondeclarator and struct for something
            // similar.
            List<ExpressionValue> exprlist
              = (List<ExpressionValue>) getTransformationValue(subparser, 2);
            Multiverse<List<String>> exprlistmv
              = new Multiverse<List<String>>(new LinkedList<String>(), pc);
            Multiverse<List<Type>> exprlisttypemv
              = new Multiverse<List<Type>>(new LinkedList<Type>(), pc);
            for (ExpressionValue listelem : exprlist) {
              // wrap each listelem's string and type in a list
              Multiverse<List<String>> wrapped_listelem_transformation
                = DesugaringOperators.stringListWrap.transform(listelem.transformation);
              Multiverse<List<Type>> wrapped_listelem_type
                = DesugaringOperators.typeListWrap.transform(listelem.type);

              // take the product of the multiverse of lists collected
              // so far with the new element
              Multiverse<List<String>> new_exprlistmv
                = exprlistmv.complementedProduct(wrapped_listelem_transformation,
                                                 DesugaringOperators.STRINGLISTCONCAT);
              Multiverse<List<Type>> new_exprlisttypemv
                = exprlisttypemv.complementedProduct(wrapped_listelem_type,
                                                     DesugaringOperators.TYPELISTCONCAT);

              exprlistmv.destruct(); exprlistmv = new_exprlistmv;
              exprlisttypemv.destruct(); exprlisttypemv = new_exprlisttypemv;
            }

            System.err.println("EXPRLISTMV: " + exprlistmv);
            System.err.println("EXPRLISTTYPEMV: " + exprlisttypemv);

            // typecheck each combination of postfix expression and
            // parameter list.
            Multiverse<Type> typemv = new Multiverse<Type>();
            Multiverse<String> valuemv = new Multiverse<String>();
            // collect the presence condition of all type errors
            PresenceCondition errorCond
              = subparser.getPresenceCondition().presenceConditionManager().newFalse();
            todoReminder("support variadic arguments.  see CAnalyzer.processFunctionCall");
            // loop over each combination of postfix expression and
            // parameter list
            for (Element<Type> postfixelem : postfixexprval.type) {
              // check that postfix expression is a function type
              if (postfixelem.getData() instanceof NamedFunctionT) {
                FunctionT functiontype = ((NamedFunctionT) postfixelem.getData()).toFunctionT();
                List<Type> formals = functiontype.getParameters();
                for (Element<List<Type>> exprlisttype : exprlisttypemv) {
                  PresenceCondition combinedCond = postfixelem.getCondition().and(exprlisttype.getCondition());
                  // compare formal vs actual parameter types
                  int size1 =  formals.size();
                  int size2 = exprlisttype.getData().size();
                  int min = Math.min(size1, size2);

                  if (size1 > size2) {
                    // TODO: unit test
                    PresenceCondition new_errorCond = errorCond.or(combinedCond);
                    valuemv.add(emitError("too few arguments to function"), combinedCond);
                    errorCond.delRef(); errorCond = new_errorCond;
                  } else if ((! functiontype.isVarArgs()) && (size1 < size2)) {
                    // TODO: unit test
                    PresenceCondition new_errorCond = errorCond.or(combinedCond);
                    valuemv.add(emitError("too many arguments to function"), combinedCond);
                    errorCond.delRef(); errorCond = new_errorCond;
                  } else {  // parameter size is right
                    // check compare each of the parameters' types
                    // one-at-a-time and if one doesn't match, break
                    // and set the presence condition to be an error
                    boolean match = true;
                    for (int i = 0; i < min; i++) {
                      Type formal = formals.get(i);
                      Type actual = exprlisttype.getData().get(i);
                      if (! cOps.equal(formal, actual)) {
                        todoReminder("support C's type coercion rules in function call parameter checking");
                        match = false;
                        break;
                      }
                    }
                    if (match) {
                      // the expression's type is the return value's type of the function being called
                      typemv.add(functiontype.getResult(), combinedCond);
                    } else {
                      // TODO: unit test
                      // parameters don't match.  type error.
                      PresenceCondition new_errorCond = errorCond.or(combinedCond);
                      valuemv.add(emitError("function call parameter types do not match function type"), combinedCond);
                      errorCond.delRef(); errorCond = new_errorCond;
                    }
                  }
                  combinedCond.delRef();
                }  // end loop over parameter list
              } else {  // not a function type
                PresenceCondition new_errorCond = errorCond.or(postfixelem.getCondition());
                // TODO: unit test
                valuemv.add(emitError("attempting function call on non-function type"), postfixelem.getCondition());
                errorCond.delRef(); errorCond = new_errorCond;
              } // end check for function type
            } // end loop over postfixelems
            typemv.add(ErrorT.TYPE, errorCond);
            /* valuemv.add(emitError("type error on function call"), errorCond); */  // TODO: add an option to emit one type error message for all instead of individual messages for each configuration

            // should be non-empty because either errorCond is
            // non-false or some parameter list matched and added the
            // return type
            assert ! typemv.isEmpty();

            // filter out the postfix value and the expression list
            // values that are type errors.
            PresenceCondition validTypes = errorCond.not();
            Multiverse<String> filtered_postfixexpr = postfixexprval.transformation.filter(validTypes);
            Multiverse<List<String>> filtered_exprlistmv = exprlistmv.filter(validTypes);
            errorCond.delRef(); validTypes.delRef();
            
            System.err.println("filtered1: " + filtered_postfixexpr);
            System.err.println("filtered2: " + filtered_exprlistmv);

            if (filtered_postfixexpr.isEmpty() || filtered_exprlistmv.isEmpty()) {
              // if either is empty, there is nothing left to
              // do. there were no valid type checking results for any
              // combination of postfix expr and parameter list.
              // valuemv will only contain the error message.
            } else {
              // construct the resulting function call's transformations
              // and types
              for (Element<String> postfixelem : filtered_postfixexpr) {
                for (Element<List<String>> exprlistelem : filtered_exprlistmv) {
                  PresenceCondition combinedCond = postfixelem.getCondition().and(exprlistelem.getCondition());
                  // note that this does not use the original tokens
                  // from the AST for command and parens
                  String callstring = String.format("%s ( %s )",
                                                    postfixelem.getData(),
                                                    String.join(", ", exprlistelem.getData()));
                  valuemv.add(callstring, combinedCond);
                  combinedCond.delRef();
                }
              }
            }
            assert ! valuemv.isEmpty();
            if (! filtered_postfixexpr.isEmpty()) {
              filtered_postfixexpr.destruct();
            }
            if (! filtered_exprlistmv.isEmpty()) {
              filtered_exprlistmv.destruct();
            }

            System.err.println("FCALLTYPE: " + typemv);
            System.err.println("FCALLERRVALS: " + valuemv);
            
            setTransformationValue(value, new ExpressionValue(valuemv, typemv));
          } else { // types of postfixexprval are all errors
            // TODO: this throws away the type message from the child,
            // so perhaps copy the child's mv values instead.
            setTransformationValue(value, new ExpressionValue(emitError("no valid type for the function part of the function call"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
        ;

DirectSelection:  /** nomerge **/  // ExpressionValue
        PostfixExpression DOT IdentifierOrTypedefName
        {
          ExpressionValue postfixval = (ExpressionValue) getTransformationValue(subparser, 3);

          Multiverse<String> postfixmv = postfixval.transformation;
          Multiverse<String> dotmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(),
                                            subparser.getPresenceCondition());
          String ident = ((Syntax) getNodeAt(subparser, 1).get(0)).getTokenText();

          // go through each type and see which have a field with this
          // name and collect the resulting type
          Multiverse<Type> postfixtype = postfixval.type;
          Multiverse<Type> typemv = new Multiverse<Type>();  // resulting type
          Multiverse<String> identmv = new Multiverse<String>();  // desugaring
          CContext scope = ((CContext) subparser.scope);
          for (Element<Type> type : postfixtype) {
            // check that the postfix type is a struct or union
            if (type.getData().isStruct() || type.getData().isUnion()) {
              StructOrUnionT sutype = (StructT) type.getData();
              String tag = sutype.getName();
              assert tag != null;  // even anonymous structs get a name, e.g., anonymous(0)
              if (tag.startsWith("anonymous(")) {  // anonymous struct or union
                // go through each symtab entry for this struct/union
                Multiverse<SymbolTable.Entry> entries = scope.getAnyScope(tag, type.getCondition());
                for (Element<SymbolTable.Entry> entry : entries) {
                  PresenceCondition combinedCond = type.getCondition().and(entry.getCondition());
                  if (entry.getData() == SymbolTable.ERROR) {
                    // TODO: type error
                    typemv.add(ErrorT.TYPE, combinedCond);
                  } else if (entry.getData() == SymbolTable.UNDECLARED) {
                    // TODO: type error, symbol not declared in this presence condition
                    typemv.add(ErrorT.TYPE, combinedCond);
                  } else {
                    // TODO: check for correct field usage, otherwise type error
                    System.err.println("TODO: finish DirectSelection for anonymous structs");
                    System.exit(1);
                  }
                  combinedCond.delRef();
                }
                entries.destruct();
              } else {  // tagged struct or union
                // tagged structs work by using the original name for
                // a struct that is the union of all variations, so we
                // need to replace the field with level of indirection
                // into this union.

                // first go through each symtab entry for the struct tag
                String tagname = CContext.toTagName(sutype.getName());
                Multiverse<SymbolTable.Entry> entries = scope.getAnyScope(tagname, type.getCondition());
                for (Element<SymbolTable.Entry> entry : entries) {
                  PresenceCondition combinedCond = type.getCondition().and(entry.getCondition());
                  if (entry.getData() == SymbolTable.ERROR) {
                    // TODO: type error
                    typemv.add(ErrorT.TYPE, combinedCond);
                  } else if (entry.getData() == SymbolTable.UNDECLARED) {
                    // TODO: type error, symbol not declared in this presence condition
                    typemv.add(ErrorT.TYPE, combinedCond);
                  } else {
                    // TODO: check for correct field usage, otherwise type error
                    // TODO: insert field of the union inside the original struct/union

                    // since we looked up a tagname, not seeing a
                    // struct/union type likely means there's a bug
                    assert entry.getData().getType().isStruct() || entry.getData().getType().isUnion();
                    StructOrUnionT entrytype = (StructOrUnionT) entry.getData().getType();

                    // similarly, if we looked up a tagname, there
                    // should be definitions with members
                    assert null != entrytype.getMembers();

                    // check that the field exist in this variation of
                    // the struct.  TypeBuilder sets all members to
                    // VariableT FIELD types
                    VariableT fieldtype = (VariableT) entrytype.lookup(ident);
                    if (fieldtype.isError()) {
                      System.err.println(String.format("type error: field \"%s\" not found in this configuration of struct/union %s", ident, sutype.getName()));
                      typemv.add(ErrorT.TYPE, combinedCond);
                    } else {
                      // found a valid field and we now know its type
                      
                      typemv.add(fieldtype.getType(), combinedCond);

                      // add the indirection using the tag (which is
                      // the same name as the field in the combined
                      // struct's union)
                      identmv.add(String.format("%s.%s", entrytype.getName(), fieldtype.getName()), combinedCond);
                    }
                  }
                  combinedCond.delRef();
                }
              }
            } else {
              // TODO: not a struct or union, type error
              typemv.add(ErrorT.TYPE, type.getCondition());
            }
          }
          
          assert ! typemv.isEmpty();

          System.err.println("typemv " + typemv);
          System.err.println("identmv " + identmv);

          todoReminder("check for all type errors or else the product for directselect will fail because of a product of an empty multiverse");
          Multiverse<String> valuemv = productAll(DesugaringOperators.concatStrings, postfixmv, dotmv, identmv);
          dotmv.destruct(); identmv.destruct();  // postfixmv is from child, so don't destruct
          // valuemv shouldn't need to filtered for error conditions,
          // because identmv only has those configurations that were
          // correctly typed

          System.err.println("valuemv " + valuemv);
          setTransformationValue(value, new ExpressionValue(valuemv, typemv));
        }
        ;

IndirectSelection:  /** nomerge **/
        PostfixExpression ARROW IdentifierOrTypedefName
        {
          System.err.println("TODO: IndirectSelection");
          System.exit(1);
          // TODO: need to cast PostfixExpression to the union field
          // of the configurable struct declaration.  this means we
          // need to know the type of postfixexpression
          System.err.println("TODO: rename according to struct fields");
          // TODO: check that postfix expression is a pointer to a struct and that the identifier is one of its fields
        }
        ;

Increment:  /** nomerge **/  // ExpressionValue
        PostfixExpression ICR
        {
          todoReminder("typecheck Increment");
          // TODO: check that postfixexpression is a number or pointer (see CAnalyzer)
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);
          
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> opmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);
          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings, exprmv, opmv),
                                                     exprval.type));
          opmv.destruct();
        }
        ;

Decrement:  /** nomerge **/  // ExpressionValue
        PostfixExpression DECR
        {
          todoReminder("typecheck Decrement");
          // TODO: check that postfixexpression is a number or pointer (see CAnalyzer)
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2);
          
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> opmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc);
          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings, exprmv, opmv),
                                                     exprval.type));
          opmv.destruct();
        }
        ;

CompoundLiteral:  /** nomerge **/  /* ADDED */
        LPAREN TypeName RPAREN LBRACE InitializerList RBRACE
        {
          System.err.println("WARNING: unsupported semantic action: CompoundLiteral");
          System.exit(1);
        }
        ;

ExpressionList:  /** list, nomerge **/  // List<ExpressionValue>
        AssignmentExpression
        {
          // create a new list
          List<ExpressionValue> exprlist = new LinkedList<ExpressionValue>();
          ExpressionValue exprval
            = (ExpressionValue) getTransformationValue(subparser,1);
          exprlist.add(exprval);
          setTransformationValue(value, exprlist);
        }
        | ExpressionList COMMA AssignmentExpression
        {
          // add to the existing expression list.  this reuse of a
          // semantic value may be an issue if static conditionals are
          // permitted under expressionlists
          List<ExpressionValue> exprlist
            = (LinkedList<ExpressionValue>) getTransformationValue(subparser,3);
          ExpressionValue exprval
            = (ExpressionValue) getTransformationValue(subparser,1);
          exprlist.add(exprval);
          setTransformationValue(value, exprlist);
        }
        ;

UnaryExpression:  /** passthrough, nomerge **/  // ExpressionValue
        PostfixExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | ICR UnaryExpression
        {
          todoReminder("typecheck unaryexpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                opmv,
                                                                exprmv),
                                                     exprval.type));  // TODO: placeholder until type checking
        }
        | DECR UnaryExpression
        {
          todoReminder("typecheck unaryexpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                opmv,
                                                                exprmv),
                                                     exprval.type));  // TODO: placeholder until type checking
        }
        | Unaryoperator CastExpression
        {
          // TODO: need to look at the unaryoperator to determine whether it's the correct type usage
          todoReminder("typecheck unaryexpression (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> opmv = new Multiverse<String>((String) getTransformationValue(subparser, 2), pc);
          Multiverse<String> exprmv = exprval.transformation;

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                opmv,
                                                                exprmv),
                                                     exprval.type));  // TODO: placeholder until type checking
        }
        | SIZEOF UnaryExpression
        {
          todoReminder("typecheck unaryexpression (5)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                opmv,
                                                                exprmv),
                                                     exprval.type));  // TODO: placeholder until type checking
        }
        | SIZEOF LPAREN TypeName RPAREN
        {
          System.err.println("WARNING: unsupported unaryexpression (6)");
          System.exit(1);
        }
        | LabelAddressExpression  // ADDED
        {
          todoReminder("typecheck unaryexpression (7)");
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | AlignofExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (8)");
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | ExtensionExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (9)");
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | OffsetofExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (10)");
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | TypeCompatibilityExpression  // ADDED
        {
          todoReminder("typecheck unaryexpression (11)");
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
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

ExtensionExpression:  /** nomerge **/  // ExpressionValue
        __EXTENSION__ CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 1);
          
          Multiverse<String> extmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugaringOperators.concatStrings, extmv, exprmv),
                                                     exprval.type));
          extmv.destruct();
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

Alignofkeyword:  // String
        __ALIGNOF__
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | __ALIGNOF
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        ;

LabelAddressExpression:  /** nomerge  **/  // ADDED
        ANDAND IDENTIFIER
        {
          System.err.println("WARNING: unsupported semantic action: LabelAddressExpression");
          System.exit(1);
        }
        ;

Unaryoperator:  // String
        AND
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | STAR
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | PLUS
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | MINUS
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | NEGATE
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | NOT
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        ;

CastExpression:  /** passthrough, nomerge **/  // ExpressionValue
        UnaryExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | LPAREN TypeName RPAREN CastExpression
        {
          System.err.println("TODO: CastExpression (2) type checking");
          System.exit(1);
        }
        ;



          /* PresenceCondition pc = subparser.getPresenceCondition(); */
          /* ExpressionValue exprval = (ExpressionValue) getTransformationValue(subparser, 2); */

          /* Multiverse<String> lparenmv */
          /*   = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc); */
          /* Multiverse<String> exprmv = exprval.transformation; */
          /* Multiverse<String> rparenmv */
          /*   = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc); */

          /* setTransformationValue(value, */
          /*                        new ExpressionValue(productAll(DesugaringOperators.concatStrings, lparenmv, exprmv, rparenmv), */
          /*                                            exprval.type)); */
          /* lparenmv.destruct(); rparenmv.destruct(); */

MultiplicativeExpression:  /** passthrough, nomerge **/  // ExpressionValue
        CastExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | MultiplicativeExpression STAR CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        | MultiplicativeExpression DIV CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        | MultiplicativeExpression MOD CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        ;

AdditiveExpression:  /** passthrough, nomerge **/  // ExpressionValue
        MultiplicativeExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | AdditiveExpression PLUS MultiplicativeExpression
        {
          todoReminder("typecheck AdditiveExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        | AdditiveExpression MINUS MultiplicativeExpression
        {
          todoReminder("typecheck AdditiveExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        ;

ShiftExpression:  /** passthrough, nomerge **/  // ExpressionValue
        AdditiveExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | ShiftExpression LS AdditiveExpression
        {
          todoReminder("typecheck ShiftExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        | ShiftExpression RS AdditiveExpression
        {
          todoReminder("typecheck ShiftExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          setTransformationValue(value, new ExpressionValue(productAll(DesugaringOperators.concatStrings,
                                                                       leftmv,
                                                                       opmv,
                                                                       rightmv),
                                                            leftval.type));  // TODO: this is a placeholder for the real type
          opmv.destruct();
        }
        ;

RelationalExpression:  /** passthrough, nomerge **/ // ExpressionValue
        ShiftExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | RelationalExpression LT ShiftExpression
        {
          System.err.println("TODO: RelationalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        | RelationalExpression GT ShiftExpression
        {
          System.err.println("TODO: RelationalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        | RelationalExpression LE ShiftExpression
        {
          System.err.println("TODO: RelationalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        | RelationalExpression GE ShiftExpression
        {
          System.err.println("TODO: RelationalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

EqualityExpression:  /** passthrough, nomerge **/  // ExpressionValue
        RelationalExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | EqualityExpression EQ RelationalExpression
        {
          System.err.println("TODO: EqualityExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        | EqualityExpression NE RelationalExpression
        {
          System.err.println("TODO: EqualityExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

AndExpression:  /** passthrough, nomerge **/  // ExpressionValue
        EqualityExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | AndExpression AND EqualityExpression
        {
          System.err.println("TODO: AndExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

ExclusiveOrExpression:  /** passthrough, nomerge **/  // ExpressionValue
        AndExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | ExclusiveOrExpression XOR AndExpression
        {
          System.err.println("TODO: ExclusiveOrExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

InclusiveOrExpression:  /** passthrough, nomerge **/  // ExpressionValue
        ExclusiveOrExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | InclusiveOrExpression PIPE ExclusiveOrExpression
        {
          System.err.println("TODO: InclusiveOrExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

LogicalAndExpression:  /** passthrough, nomerge **/  // ExpressionValue
        InclusiveOrExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | LogicalAndExpression ANDAND InclusiveOrExpression
        {
          System.err.println("TODO: LogicalAndExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

LogicalORExpression:  /** passthrough, nomerge **/ // ExpressionValue
        LogicalAndExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | LogicalORExpression OROR LogicalAndExpression
        {
          System.err.println("TODO: LogicalORExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

ConditionalExpression:  /** passthrough, nomerge **/  // ExpressionValue
        LogicalORExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | LogicalORExpression QUESTION Expression COLON
                ConditionalExpression
        {
          System.err.println("TODO: ConditionalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        | LogicalORExpression QUESTION COLON  // ADDED gcc innomerge conditional
                ConditionalExpression
        {
          System.err.println("TODO: ConditionalExpression");
          System.exit(1);
          // TODO: check for valid types
        }
        ;

AssignmentExpression:  /** passthrough, nomerge **/  // ExpressionValue
        ConditionalExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | UnaryExpression AssignmentOperator AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          ExpressionValue leftval = (ExpressionValue) getTransformationValue(subparser, 3);
          ExpressionValue rightval = (ExpressionValue) getTransformationValue(subparser, 1);

          Multiverse<String> expr = leftval.transformation;
          Multiverse<String> op
            = new Multiverse<String>((String) getTransformationValue(subparser, 2), pc);
          Multiverse<String> assign = rightval.transformation;

          // type-checking
          Multiverse<Type> exprtype = leftval.type;
          Multiverse<Type> assigntype = rightval.type;
          System.err.println("exprtype: " + exprtype);
          System.err.println("assigntype: " + assigntype);
          Multiverse<Type> producttype = productAll(DesugaringOperators.compareTypes, exprtype, assigntype);
          System.err.println("TODO: deduplicate ErrorT");
          System.err.println("TODO: allow type coercion");
          Multiverse<Type> typemv = producttype;
          /* Multiverse<Type> typemv = producttype.deduplicate(ErrorT.TYPE); */
          /* producttype.destruct(); */

          // filter out configurations with type errors
          PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
          Multiverse<String> product = productAll(DesugaringOperators.concatStrings, expr, op, assign);
          PresenceCondition typesafeCond = errorCond.not();

          todoReminder("TODO: always filter out expressions with type errors so that expressionstatement can convert it to a runtime error.");
          /* Multiverse<String> valuemv = product.filter(typesafeCond); */
          Multiverse<String> valuemv = new Multiverse<String>(product);

          // TODO: need to check for all type errors anywhere that is
          // getting a type.  perhaps use a single value,
          // ExpressionValue that holds two multiverses (instead of
          // trying to combine them in one multiverse element, which
          // doesn't work for parts of the language without a type,
          // like operators.

          System.err.println("assignvalue: " + valuemv);
          System.err.println("assigntype: " + typemv);

          op.destruct(); product.destruct(); errorCond.delRef(); typesafeCond.delRef();
          
          setTransformationValue(value, new ExpressionValue(valuemv, typemv));
        }
        ;

AssignmentOperator: /** nomerge **/  // String
        ASSIGN
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | MULTassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | DIVassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | MODassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | PLUSassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | MINUSassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | LSassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | RSassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | ANDassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | ERassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        | ORassign
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
        ;

ExpressionOpt:  /** passthrough, nomerge **/ // ExpressionValue
        /* Nothing */
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, new ExpressionValue("",
                                                            UnitT.TYPE,
                                                            pc));
        }
        | Expression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        ;

Expression:  /** passthrough, nomerge **/  // ExpressionValue
        AssignmentExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
        }
        | Expression COMMA AssignmentExpression
        {
          System.err.println("TODO: Expression (2)");
        }
        ;

ConstantExpression: /** passthrough, nomerge **/  // ExpressionValue
        ConditionalExpression
        {
          setTransformationValue(value, (ExpressionValue) getTransformationValue(subparser, 1));
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

// return syntax, not a multiverse
Word:  // ADDED  // Syntax
        IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | AUTO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | DOUBLE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | INT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | STRUCT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | BREAK
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | ELSE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | LONG
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | SWITCH
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | CASE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | ENUM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | REGISTER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | TYPEDEF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | CHAR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | EXTERN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | RETURN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | UNION
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | CONST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | FLOAT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | SHORT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | UNSIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | CONTINUE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | FOR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | SIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | VOID
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | DEFAULT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | GOTO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | SIZEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | VOLATILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | DO
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | IF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | STATIC
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | WHILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | ASMSYM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | _BOOL
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | _COMPLEX
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | RESTRICT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ALIGNOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ALIGNOF__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | ASM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ASM
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ASM__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ATTRIBUTE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __ATTRIBUTE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __BUILTIN_OFFSETOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __BUILTIN_TYPES_COMPATIBLE_P
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __BUILTIN_VA_ARG
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __BUILTIN_VA_LIST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __COMPLEX__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __CONST
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __CONST__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __EXTENSION__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | INLINE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __INLINE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __INLINE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __LABEL__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __RESTRICT
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __RESTRICT__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __SIGNED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __SIGNED__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __THREAD
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | TYPEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __TYPEOF
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __TYPEOF__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __VOLATILE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
        }
        | __VOLATILE__
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<String> product = getProductOfSomeChildren(pc, getNodeAt(subparser, 1));
          setTransformationValue(value, product);
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



/***************************************************************************
**** The following naming and namespacing functionality is taken
**** directly from xtc.util.SymbolTable.
***************************************************************************/

/** The fresh name count. */
protected int freshNameCount = 0;

/** The fresh identifier count. */
protected int freshIdCount = 0;

/**
* Create a fresh name.  The returned name has
* "<code>anonymous</code>" as it base name.
*
* @see #freshName(String)
* 
* @return A fresh name.
*/
public String freshName() {
 return freshName("anonymous");
}

/**
* Create a fresh name incorporating the specified base name.  The
* returned name is of the form
* <code><i>name</i>(<i>count</i>)</code>.
*
* @param base The base name.
* @return The corresponding fresh name.
*/
public String freshName(String base) {
  StringBuilder buf = new StringBuilder();
  buf.append(base);
  buf.append(Constants.START_OPAQUE);
  buf.append(freshNameCount++);
  buf.append(Constants.END_OPAQUE);
  return buf.toString();
}

/**
 * Create a fresh C identifier.  The returned identifier has
 * "<code>tmp</code>" as its base name.
 *
 * @see #freshCId(String)
 *
 * @return A fresh C identifier.
 */
public String freshCId() {
  return freshCId("tmp");
}

/**
 * Create a fresh C identifier incorporating the specified base
 * name.  The returned name is of the form
 * <code>__<i>name</i>_<i>count</i></code>.
 *
 * @param base The base name.
 * @return The corresponding fresh C identifier.
 */
public String freshCId(String base) {
  StringBuilder buf = new StringBuilder();
  buf.append("__");
  buf.append(base);
  buf.append('_');
  buf.append(freshIdCount++);
  return buf.toString();
}

/*****************************************************************************
 ********* Methods for Transformation Values
 *****************************************************************************/

/**
   This is just a constant string name for a property used to assign
   semantic values that are type builders.
 */
private static final String STRING = "xtc.String";  // todo remove if not needed
private static final String TRANSFORMATION = "transformation";

private void setTransformationValue(Object node, Object value) {
  ((Node)node).setProperty(TRANSFORMATION, value);
}

/*
 * This class is the semantic value for FunctionPrototype.
 */
private static class FunctionPrototypeValue {
  /** The type. */
  public final Multiverse<TypeBuilder> typebuilder;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private FunctionPrototypeValue(Multiverse<TypeBuilder> typebuilder, Multiverse<Declarator> declarator) {
    this.typebuilder = typebuilder;
    this.declarator = declarator;
  }
}


// TODO: look into making these three types of values sibling classes,
// since they all share typebuidler and declarator
/*
 * This class is the semantic value for DeclaringList.
 */
private static class DeclaringListValue {
  /** The type. */
  public final Multiverse<TypeBuilder> typebuilder;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** The initializer. */
  public Multiverse<String> initializer;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   * @param declarator is the initializer.
   */
  private DeclaringListValue(Multiverse<TypeBuilder> typebuilder,
                             Multiverse<Declarator> declarator,
                             Multiverse<String> initializer) {
    this.typebuilder = typebuilder;
    this.declarator = declarator;
    this.initializer = initializer;
  }
}

/*
 * This class is the semantic value for parameters.
 */
private static class ParameterDeclarationValue {
  /** The type. */
  public final Multiverse<TypeBuilder> typebuilder;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private ParameterDeclarationValue(Multiverse<TypeBuilder> typebuilder,
                                    Multiverse<Declarator> declarator) {
    this.typebuilder = typebuilder;
    this.declarator = declarator;
  }
}

// TODO: can we make a common superclass with DeclaringListValue,
// which only add an initializer?
/*
 * This class is the semantic value for struct fields.
 */
private static class StructDeclaringListValue {
  /** The type. */
  public final Multiverse<TypeBuilder> typebuilder;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private StructDeclaringListValue(Multiverse<TypeBuilder> typebuilder,
                                 Multiverse<Declarator> declarator) {
    this.typebuilder = typebuilder;
    this.declarator = declarator;
  }
}

/**
 * This is the semantic value for expressions.  It contains one
 * multiverse of types and one multiverse of strings for the
 * transformation.  While algorithms over a Multiverse of (type,
 * string) pairs would be easier to write, there are cases where
 * expression strings do not have a type, e.g., puncutation and types
 * that don't have a string value, i.e., error types.  Keeping them
 * separate also enables deduplication of multiple transformations
 * types even if those the transformations have different strings.
 */
private static class ExpressionValue {
  /** The type. */
  public final Multiverse<Type> type;

  /** The transformation. */
  public final Multiverse<String> transformation;

  public ExpressionValue(Multiverse<String> transformation, Multiverse<Type> type) {
    this.transformation = transformation;
    this.type = type;
  }

  /**
   * Create a new expression value from a single type and a single
   * transformation string.
   */
  public ExpressionValue(String transformation, Type type, PresenceCondition pc) {
    this.transformation = new Multiverse<String>(transformation, pc);
    this.type = new Multiverse<Type>(type, pc);
  }

  /**
   * Return true there is at least one type that is not an error.
   * This is the negation of isAlwaysError().
   */
  public boolean hasValidType() {
    return ! isAlwaysError();
  }

  /**
   * Returns true if this expression is a type error in every
   * configuration in which there is a value.  Note that this excludes
   * the configurations in which there is no value at all, i.e., the
   * complement of the multiverse.
   */
  public boolean isAlwaysError() {
    // return true unless we find one type that isn't an error
    for (Element<Type> elem : type) {
      if (! elem.getData().isError()) {
        return false;
      }
    }
    return true;
  }
}

private static boolean haltUnfinished = false;

public static void todoReminder(String msg) {
  System.err.println(String.format("TODO: %s", msg));
  if (haltUnfinished) {
    System.err.println("FATAL: halting on unfinished semantic action");
    System.exit(1);
  }
}

/**
 * Get the semantic value for the transformation.  The caller is
 * responsible for casting the value into the correct type according
 * to its child nodes.
 *
 * @param subparser The subparser containing the semantic value stack.
 * @param component The index into the semantic value stack.
 */
private Object getTransformationValue(Subparser subparser, int component) {
  return getTransformationValue(getNodeAt(subparser, component));
}

/**
 * Get the semantic value for the transformation.  The caller is
 * responsible for casting the value into the correct type according
 * to its child nodes.
 *
 * @param node The AST node holding the semantic value.
 */
private Object getTransformationValue(Object node) {
  Object transformationValue = ((Node) node).getProperty(TRANSFORMATION);
  assert transformationValue != null;
  if (transformationValue == null) {
    throw new IllegalStateException("getting null transformation value");
  }
  return transformationValue;
}

/**
 * Produces the string used when a compile-time error needs to be
 * represented at runtime.
 *
 * @param msg The message.
 * @returns A snippet of C code representing the compile-time error.
 */
private String emitError(String msg) {
  return String.format("__static_type_error(\"%s\")", msg);
}

/**
 * Writes if (presence condition) { } around a statement, for all configurations.
 * @param allStatementConfigs A multiverse containing all configurations of a statement.
 * @param pc The current presence condition.
 * @return A String containing the transformed statement.
 */
private String emitStatement(Multiverse<String> allStatementConfigs, PresenceCondition pc) {
  StringBuilder sb = new StringBuilder();
  if (allStatementConfigs.size() > 1) {
    sb.append("\n{");
  }
  for (Multiverse.Element<String> statement : allStatementConfigs) {
    if (! statement.getCondition().isTrue()) {
      // don't bother using an if the statement applies to all configurations
      sb.append("\nif (");
      sb.append(condToCVar(statement.getCondition().and(pc)));
      sb.append(") {\n");
    }
    sb.append(statement.getData());
    if (! statement.getCondition().isTrue()) {
      sb.append("\n}");
    }
    sb.append("\n");
  }
  if (allStatementConfigs.size() > 1) {
    sb.append("\n}");
  }
  return sb.toString();
}

/*****************************************************************************
 ********* Multiverse handlers for Nodes
 *****************************************************************************/

/*
 * This takes the product of two or more multiverses.
 */
protected static <T> Multiverse<T> productAll(Multiverse.Operator<T> op, Multiverse<T> ...all) {
  if (all.length < 2) {
    throw new IllegalStateException("productAll requires at least two multiverses");
  }

  Multiverse<T> productmv = null;
  for (Multiverse<T> mv : all) {
    if (null == productmv) {
      productmv = new Multiverse<T>(mv);
    } else {
      Multiverse<T> tempmv = productmv.product(mv, op);
      productmv.destruct();
      productmv = tempmv;
    }
  }
  // shouldn't be empty because all is not empty
  assert productmv.size() > 0;

  return productmv;
}

/**
 * All configurations of this node are then returned in a multiverse.
 * Traverses all nested static choice nodes until non-static choice nodes are reached.
 * @param node The node to get the configurations of.
 * @param presenceCondition The presence condition associated with node.
 * @return A multiverse containing all configurations of the passed-in node.
 */
protected static Multiverse<Node> getAllNodeConfigs(Node node, PresenceCondition presenceCondition) {
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
  // shouldn't be empty because node is not null, static choice nodes
  // should not be empty (by superc), and this recursive method will
  // eventually hit the base-case of a non-static-choice node
  assert ! allConfigs.isEmpty();
  // TODO: manage memory
  return allConfigs;
}

/**
 * Get a multiverse of all stringbuilder transformation values from
 * node, including any under a static conditional.
 *
 * @param The node to get the stringbuilder transformation values
 *        from, which can be a static choice node or a regular node.
 * @param The presence condition of the subparser.
 * @returns A multiverse of stringbuilders that are the transformation values.
 */
protected Multiverse<String> getAllNodeValues(Node node, PresenceCondition pc) {
  Multiverse<String> sbmv = new Multiverse<String>();
  Multiverse<Node> allnodes = getAllNodeConfigs(node, pc);
  for (Multiverse.Element<Node> child : allnodes) {
    for (Multiverse.Element<String> childsbmv : (Multiverse<String>) getTransformationValue(child.getData())) {
      sbmv.add(childsbmv.getData(), childsbmv.getCondition().and(child.getCondition()));
    }
  }
  assert ! sbmv.isEmpty();
  
  return sbmv;
}

/**
 * Creates the cartesian product of any number of children nodes' SBMVs.
 * @param pc A PresenceCondition.
 * @param children Nodes whose SBMVs should be combined.
 * @return An SBMV containing the product of the passed-in childrens' SBMVs.
 */
protected Multiverse<String> getProductOfSomeChildren(PresenceCondition pc, Node...children) {
  // NOTE: Nodes must be passed-in in the order that their SBMV stringbuilders should be concatenated.
  Multiverse<String> sbmv
    = new Multiverse<String>("", pc);
  
  Multiverse<String> temp;
  for (Node child : children) {
    if (child.isToken()) {
      String tokenText = " ";
      tokenText += child.getTokenText();
      temp = sbmv.product(tokenText, pc, DesugaringOperators.concatStrings);
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
 * This is for nodes that have static choices under them where all the
 * nodes under the static choice have a String as the
 * transformation value.  This happens with top-level nodes where all
 * desugaring has already been handled by declaration and statement.
 */
protected String concatAllStrings(Node node, PresenceCondition pc) {
  // TODO: create a version of getAllNodeConfigs that doesn't use the
  // presence condition, since it isn't needed to just concat the
  // stringbuilders
  StringBuilder valuesb = new StringBuilder();
  Multiverse<Node> allNodes = getAllNodeConfigs(node, pc);
  for (Element<Node> elem : allNodes) {
    valuesb.append((String) getTransformationValue(elem.getData()));
    // no need for presence conditions, since declaration
    // already handles them via renaming
  }
  return valuesb.toString();
}

/**
 * Takes the cartesian product of the current node's SBMV with one of its children SBMVs.
 * Assumes that the child parameter is not a token.
 * @param sbmv A multiverse that possibly contains the configurations of child's siblings.
 * @param child The child of the current node.
 * @param presenceCondition The presence condition associated with the current node.
 * @return A multiverse containing all configurations of the passed-in node.
 */
protected Multiverse<String> cartesianProductWithChild(Multiverse<String> sbmv, Node child, PresenceCondition presenceCondition) {
  sbmv = new Multiverse<String>(sbmv); // copies the passed-in sbmv because the caller destructs it.
  // getAllNodeConfigs traverses all nested static choice nodes until they reach a regular node
  // and then gets all configurations of that node
  Multiverse<String> allConfigsSBMV = getAllNodeValues(child, presenceCondition);

  Multiverse<String> temp = sbmv.product(allConfigsSBMV, DesugaringOperators.concatStrings);
  sbmv.destruct();
  sbmv = temp;

  return sbmv;
}


/*****************************************************************************
 ********* Methods to record global desugaring information.  These
 ********* will go into a special initializer function defined at the
 ********* end of the transformation.
 *****************************************************************************/

private StringBuilder recordedRenamings = new StringBuilder();
private StringBuilder invalidGlobals = new StringBuilder();

/**
 * Record an invalid global declaration.
 *
 * @param ident The name of the global symbol.
 * @param condition The presence condition under which the error occurred.
 */
private void recordInvalidGlobalDeclaration(String ident, PresenceCondition condition) {
  invalidGlobals.append(String.format("if (%s) { %s; }\n",
                                      condToCVar(condition),
                                      emitError(String.format("invalid global declaration of %s", ident))));
}

/**
 * Record an invalid global declaration.
 *
 * @param ident The name of the global symbol.
 * @param condition The presence condition under which the error occurred.
 */
private void recordInvalidGlobalRedeclaration(String ident, PresenceCondition condition) {
  invalidGlobals.append(String.format("if (%s) { %s; }\n",
                                      condToCVar(condition),
                                      emitError(String.format("invalid global redeclaration of %s", ident))));
}

/**
 * Record a renaming.
 *
 * @param renaming The new name of the symbol.
 * @param original The old name of the symbol.
 */
private void recordRenaming(String renaming, String original) {
  recordedRenamings.append(String.format("__static_renaming(\"%s\", \"%s\");\n", renaming, original));
}
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
    /* name = toTagName(tag); */
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

  // this multiverse should not be empty, because node is not null,
  // static choices contain nodes (from superc), or the else case is
  // hit
  assert ! mv.isEmpty();

  return mv;
}

private Map<Integer, String> condVars = new HashMap<Integer, String>();

// TODO: record the string values of the condVars as well as the C
// variables.  also emit the renaming from the c var to the
// preprocessor expression it represents

public String condToCVar(PresenceCondition cond) {
  // TODO: traverse the (simplified) expression AST and convert
  // non-boolean leaves to C variables.
  int hash = cond.hashCode();
  if (condVars.containsKey(hash)) {
    return condVars.get(hash);
  } else {
    String cvar = freshCId("static_condition");
    condVars.put(hash, cvar);
    return cvar;
  }
}

/* public HashMap<String, String> boolVarRenamings = new HashMap<String, String>(); */
/* private HashMap<String, String> BoolExprs = new HashMap<String, String>(); */

/* /\** Takes a presence condition and generates a valid C string for conditionals *\/ */
/* public String PCtoString(PresenceCondition cond) { */
/*  List allsat = (List) cond.getBDD().allsat(); */
/*  ArrayList<String> currentExprs; */
/*  String CBoolExpr; */
/*  StringBuilder sb = new StringBuilder(); */
/*  boolean firstTerm = true; */
/*  boolean firstTermOuter = true; */

/*  if (cond.getBDD().isOne()) { */
/*    return "1"; */
/*  } else if (cond.getBDD().isZero()) { */
/*    return "0"; */
/*  } */

/*  for (Object o : allsat) { */
/*    if (!firstTermOuter) */
/*      sb.append(" || "); */
/*    firstTermOuter = false; */
/*    currentExprs = getBoolExprs((byte[]) o, cond); */
/*    firstTerm = true; */
/*    for (String CPPBoolExpr : currentExprs) { */
/*      if (!firstTerm) */
/*        sb.append(" && "); */
/*      firstTerm = false; */
/*      if (BoolExprs.isEmpty() || !BoolExprs.containsKey(CPPBoolExpr)) { */
/*        /\** generates a new C boolean expression with hashcode appended, then adds it to hashmap, then returns it *\/ */
/*        CBoolExpr = generateBoolExpr(CPPBoolExpr); */
/*        BoolExprs.put(CPPBoolExpr, CBoolExpr); */
/*        sb.append(CBoolExpr); */
/*      } else /\* if (BoolExprs.containsKey(CPPBoolExpr)) *\/ { */
/*        CBoolExpr = BoolExprs.get(CPPBoolExpr); */
/*        sb.append(CBoolExpr); */
/*      } */
/*    } */
/*  } */
/*  return sb.toString(); */
/* } */

/* /\** returns a list of every expression in the BDD *\/ */
/* public ArrayList<String> getBoolExprs(byte[] sat, PresenceCondition cond) { */
/*  ArrayList<String> allExprs = new ArrayList<String>(); */
/*  for (int i = 0; i < sat.length; i++) { */
/*    if (sat[i] == 1) { */
/*      /\** builds up a list of the (CPP) boolean expressions within the PresenceCondition *\/ */
/*      allExprs.add(cond.presenceConditionManager().getVariableManager().getName(i)); */
/*    } else if (sat[i] == 0) { */
/*      allExprs.add("!" + cond.presenceConditionManager().getVariableManager().getName(i)); */
/*    } */
/*  } */
/*  return allExprs; */
/* } */

/* /\** Returns a new (valid C) boolean expression, with hashcode appended *\/ */
/* public String generateBoolExpr(String CPPBoolExpr) { */
/*  StringBuilder sb = new StringBuilder(); */
/*  boolean falseExpr = false; */
/*  boolean definedExpr = false; */

/*  /\** need to remove the '!' character from the string, so that it doesn't change the hashcode (then append it later) *\/ */
/*  if (CPPBoolExpr.contains("!")) { */
/*    falseExpr = true; */
/*    sb.append(CPPBoolExpr); */

/*    /\** if there is a '!' character, it will be at the 0th position of sb *\/ */
/*    sb.deleteCharAt(0); */
/*    CPPBoolExpr = sb.toString(); */
/*    sb.setLength(0); */
/*  } */

/*  /\** need to remove "defined" from the string, so that it doesn't affect the hashcode (then append it later) *\/ */
/*  if (CPPBoolExpr.contains("defined")) { */
/*    definedExpr = true; */
/*    sb.append(CPPBoolExpr); */

/*    /\** if the expression is a "defined" expression, it will be in the form (defined <>) */
/*     *  note that there will not be a '!' character by this point. */
/*     *\/ */
/*    for (int i = 0; i <= 7; i++) */
/*      sb.deleteCharAt(1); */

/*    /\** removes parentheses *\/ */
/*    sb.deleteCharAt(0); */
/*    sb.deleteCharAt(sb.length() - 1); */

/*    CPPBoolExpr = sb.toString(); */
/*    sb.setLength(0); */
/*  } */

/*  sb.append("_C_"); */
/*  sb.append(CPPBoolExpr.hashCode()); */

/*  if (sb.charAt(3) == '-') */
/*    sb.replace(3, 4, "n"); /\** replaces the '-' with 'n' *\/ */

/*  if (!boolVarRenamings.containsKey(CPPBoolExpr)) { */
/*    boolVarRenamings.put(CPPBoolExpr, sb.toString()); */
/* } */
/*  sb.setLength(0); */

/*  if (falseExpr) */
/*    sb.append("!"); */

/*  sb.append("_C_"); */
/*  sb.append(CPPBoolExpr.hashCode()); */

/*  if (definedExpr) */
/*    sb.append("_DEFINED"); */

/*  /\** the expression cannot have a '-' character in it (because it would evaluate as subtraction) *\/ */
/*  if (falseExpr) { */
/*    /\** if the expression is false, then the '-' will come later in the string due to the additional '!' character *\/ */
/*    if (sb.charAt(4) == '-') { */
/*      sb.replace(4, 5, "n"); /\** replaces the '-' with 'n' *\/ */
/*    } */
/*  } else { */
/*    if (sb.charAt(3) == '-') { */
/*      sb.replace(3, 4, "n"); /\** replaces the '-' with 'n' *\/ */
/*    } */
/*  } */

/*  return sb.toString(); */
/* } */

protected static C cOps = new C();


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