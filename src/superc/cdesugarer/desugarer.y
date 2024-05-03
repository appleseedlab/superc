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
import java.lang.StringBuilder;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.Map;
import java.util.HashMap;
import java.util.Random;
import java.util.AbstractMap;

import java.io.File;
import java.io.Reader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.StringReader;
import java.io.OutputStreamWriter;
import java.io.IOException;

import java.math.BigInteger;

import java.util.Collections;
import java.util.Comparator;
 
import xtc.Constants;
import xtc.Limits;

import superc.cdesugarer.OldSymbolTable.STField;

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

import superc.cdesugarer.Multiverse;

import superc.cdesugarer.Declarator;
import superc.cdesugarer.Declarator.EmptyDeclarator;
import superc.cdesugarer.Declarator.SimpleDeclarator;
import superc.cdesugarer.Declarator.PointerDeclarator;
import superc.cdesugarer.Declarator.QualifiedPointerDeclarator;
import superc.cdesugarer.Declarator.PointerAbstractDeclarator;
import superc.cdesugarer.Declarator.QualifiedPointerAbstractDeclarator;
import superc.cdesugarer.Declarator.ArrayDeclarator;
import superc.cdesugarer.Declarator.ArrayAbstractDeclarator;
import superc.cdesugarer.Declarator.FunctionDeclarator;
import superc.cdesugarer.Declarator.ParameterListDeclarator;
import superc.cdesugarer.Declarator.BitFieldSizeDeclarator;

import superc.cdesugarer.Initializer;
import superc.cdesugarer.Initializer.EmptyInitializer;
import superc.cdesugarer.Initializer.AssignInitializer;
import superc.cdesugarer.Initializer.ExpressionInitializer;
import superc.cdesugarer.Initializer.InitializerList;
import superc.cdesugarer.Initializer.DesignatedInitializer;
import superc.cdesugarer.Initializer.Designation;
import superc.cdesugarer.Initializer.OffsetofMemberDesignator;
import superc.cdesugarer.Initializer.Designator;
import superc.cdesugarer.Initializer.ArrayDesignator;
import superc.cdesugarer.Initializer.StructUnionDesignator;

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
import xtc.type.FunctionOrMethodT;
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
import xtc.type.PointerT;
import xtc.type.AnnotatedT;
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
import xtc.type.WrappedT;
import xtc.type.Parameter;
 
 
/* import xtc.util.SymbolTable; */
/* import xtc.util.SymbolTable.Scope; */
import xtc.util.SingletonIterator;
import xtc.util.Utilities;

import superc.cdesugarer.Multiverse.Element;
import superc.cdesugarer.SymbolTable.Entry;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.ForkMergeParser;
import superc.core.ForkMergeParser.StackFrame;

import xtc.type.Type;
import xtc.type.NumberT;
import xtc.type.StructT;
import xtc.type.VariableT;
import xtc.type.UnitT;
/* TUTORIAL: add any additional type classes here */

import com.microsoft.z3.BoolExpr;

%}

%%

TranslationUnit:  /** complete **/  // String
        ExternalDeclarationList
        {
          PresenceConditionManager p = new PresenceConditionManager();
          PresenceCondition one = p.newTrue();
          List<Node> extdecls = (List<Node>) getTransformationValue(subparser,1);
	  String result = "";
	  for (Node n : extdecls) {
	    if (!n.hasBeenPrinted) {
	      n.hasBeenPrinted = true;
	      result += concatMultiverseStrings(getCompleteNodeSingleValue(n,one));
	    }
	    
	  }
	  CContext.addOutput(result);
	}
;

// ------------------------------------------------------ External definitions

/* annotate this as a list to improve performance when generating the ast */
ExternalDeclarationList: /** list, complete **/  // Multiverse<String>
        /* empty */  // ADDED gcc allows empty program
        {
          
          setTransformationValue(value, new LinkedList<Node>());
        }
        | ExternalDeclarationList ExternalDeclaration
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Node> list = (List<Node>)getTransformationValue(subparser, 2);
          Node elem = getNodeAt(subparser, 1);
          list.add(elem);
          setTransformationValue(value, list);
        }
        ;

ExternalDeclaration:  /** complete **/  // String
        FunctionDefinitionExtension
        {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
        | DeclarationExtension
        {
          
          List<Multiverse<String>> declmv = getCompleteNodeListValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          String s = "";
          for (Multiverse<String> m : declmv) {
            s += concatMultiverseStrings(m);
            m.destruct();
          }
          setTransformationValue(value, s);
        }
        | AssemblyDefinition
        {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
        | EmptyDefinition
        {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
        ;

EmptyDefinition:  /** complete **/  // String
        SEMICOLON
        {
          setTransformationValue(value, (String) getNodeAt(subparser, 1).getTokenText());
        }
        ;

FunctionDefinitionExtension:  /** complete **/  // ADDED  // String
        FunctionDefinition
        {
          Multiverse<String> funcmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(funcmv)); funcmv.destruct();
        }
        | __EXTENSION__ FunctionDefinition
        {
          Multiverse<String> funcmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(getNodeAt(subparser, 2).getTokenText());
          valuesb.append(concatMultiverseStrings(funcmv)); funcmv.destruct();
          setTransformationValue(value, valuesb.toString());
        }
        ;

FunctionDefinition:  /** complete **/ // added scoping  // String
FunctionPrototype
{
  restartLabelFunction();
  // similar to Declaration, but different in that this has a
  // compoundstatement, while declaration has an initializer.
  PresenceCondition pc = subparser.getPresenceCondition();
          
  // add all variations of the function declaration to the symtab
  CContext scope = (CContext)subparser.scope;
  Multiverse<Node> prototypeNodemv = staticCondToMultiverse(getNodeAt(subparser, 1), pc);
  // produce a multiverse of strings for the body to use
  Multiverse<String> prototypestrmv = new Multiverse<String>();
  // collect the set of configurations that have valid function prototypes
  for (Element<Node> prototypeNode : prototypeNodemv) {
    FunctionPrototypeValue prototype = (FunctionPrototypeValue) getTransformationValue(prototypeNode.getData());
    Multiverse<TypeSpecifier> typespecifiermv = prototype.typespecifier;
    Multiverse<Declarator> declaratormv = prototype.declarator;
    Multiverse<Declarator> newDeclarations = new Multiverse<Declarator>();
    Multiverse<TypeSpecifier> newTypes = new Multiverse<TypeSpecifier>();
    assert scope.isGlobal(); // function definitions should be global.  nested functions have a separate subgrammar.
    for (Element<TypeSpecifier> typespecifier : typespecifiermv) {
      PresenceCondition typespecifierCond = prototypeNode.getCondition().and(typespecifier.getCondition());
      for (Element<Declarator> declarator : declaratormv) {
        PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
        if (combinedCond.isFalse()) {
          combinedCond.delRef();
          continue;
        }
        String originalName = declarator.getData().getName();
        Declaration originalDeclaration = new Declaration(typespecifier.getData(), declarator.getData());
        if (originalDeclaration.hasTypeError()) {
          // if type is invalid, put an error entry, emit a call
          // to the type error function
          scope.putError(originalName, combinedCond);
          recordInvalidGlobalDeclaration(originalName, combinedCond);
          System.err.println(String.format("INFO: \"%s\" has an invalid type specifier", originalName));
        } else if (! originalDeclaration.getType().isFunction()) {
          // if type is not a function type, put an error entry, emit a call
          // to the type error function
          scope.putError(originalName, combinedCond);
          recordInvalidGlobalDeclaration(originalName, combinedCond);
          System.err.println(String.format("INFO: \"%s\" non-function type specifier in function prototype.  this can happen when, e.g., header guards make typedefs conditional.", originalName));
        } else {
          // otherwise loop over each existing entry check for
          // type errors or add a new declaration
          Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, combinedCond);
          for (Element<SymbolTable.Entry<Type>> entry : entries) {

            // the renamed declaration is used to get the type entry in the symtab
            String renaming;
            String funcName = "";
            if (!entry.getData().isDeclared()) {
              renaming = freshCId(originalName);
            } else { //is declared
              funcName = entry.getData().getValue().getName();
              renaming = freshCId(entry.getData().getValue().getName());
            }
            Declarator renamedDeclarator = declarator.getData().rename(renaming);
            Declaration renamedDeclaration = new Declaration(typespecifier.getData(), renamedDeclarator);
            boolean invalidTypeSpec = false;
            // the renamed function is static to enable linking the original function name
            if (Constants.ATT_STORAGE_EXTERN == typespecifier.getData().getStorageClass()
                || Constants.ATT_STORAGE_AUTO == typespecifier.getData().getStorageClass()
                || Constants.ATT_STORAGE_REGISTER == typespecifier.getData().getStorageClass()
                || Constants.ATT_STORAGE_TYPEDEF == typespecifier.getData().getStorageClass()) {
              todoReminder("check that function definitions don't have an auto, extern, register, or typedef storage class and produce a type error if so");
              invalidTypeSpec = true;
            }

            // make all renamed declarations static until project-wide, configuration-aware linking is possible
            String desugaredDeclaration;
            desugaredDeclaration = renamedDeclaration.toString();
            assert null != desugaredDeclaration;
                    
            // renamedDeclaration must be a FunctionT because
            // that is created by a FunctionDeclarator
            Type declarationType = renamedDeclaration.getType();

            if (! declarationType.isFunction()) {
              System.err.println(String.format("FATAL: unexpected type in function prototype: %s %s", declarationType, renaming));
              System.exit(1);
            }
            Type type = new NamedFunctionT(declarationType.toFunction().getResult(),
                                           renaming,
                                           declarationType.toFunction().getParameters(),
                                           declarationType.toFunction().isVarArgs());
            
            if (entry.getData().isError() || invalidTypeSpec) {
              // ERROR entry
              System.err.println(String.format("INFO: \"%s\" is being redeclared in an existing invalid declaration", originalName));
            } else if (entry.getData().isUndeclared()) {
              // UNDECLARED entry

              todoReminder("multiplex functions to so that each can have its own function name.  try using function pointers as a kind of vtable.");
              //((NamedFunctionT)type).setDefined();
              // update the symbol table for this presence condition
              scope.put(originalName, type, entry.getCondition());
 
              // record the global/extern declaration using the original name for later use in handling linking
              if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                externalLinkage.put(originalName, originalDeclaration, entry.getCondition());
              }
 
              newDeclarations.add(renamedDeclarator, entry.getCondition());
              newTypes.add(typespecifier.getData(),entry.getCondition());
               
                // shouldn't need to add forward decl, since if
                // the function had a decl before, that will do
                // the renaming.  if the function is missing a
                // decl before def, then the function is
                // implicitly declared to be () -> int
                      
                recordRenaming(renaming, originalName);
            } else { 
              if (entry.getData().getValue().isNamedFunction()) {  // there is no Type.isFunctionOrMethod()
                FunctionT newtype = ((NamedFunctionT) type).toFunctionT();
                FunctionT previoustype = ((NamedFunctionT) entry.getData().getValue()).toFunctionT();

                //newtype.setDefined(entry.getCondition());
                //((NamedFunctionT) entry.getData().getValue()).setDefined(entry.getCondition());
                // TODO: make sure a function is only defined
                // once, although it can be declared multiple
                // times.
                System.err.println(newtype+"::"+previoustype);
                // already declared entries
                if (cOps.equal(newtype, previoustype)) {
                System.err.println("eq");
                  newDeclarations.add(renamedDeclarator, entry.getCondition());
                  newTypes.add(typespecifier.getData(),entry.getCondition());
                  CContext.addMultiplex(funcName,renaming,entry.getCondition());
                } else if (functionCouldExist(newtype,previoustype,scope,entry.getCondition())) {
                System.err.println("could");
                  transformFunctionRefs(renamedDeclarator,previoustype,entry.getCondition(),newDeclarations,typespecifier.getData(),newTypes,scope);
                  CContext.addMultiplex(funcName,renaming,entry.getCondition());
                } else {
                System.err.println("err");
                  
                  scope.putError(originalName, entry.getCondition());
                  recordInvalidGlobalDeclaration(originalName, entry.getCondition());
                  // record the global/extern declaration using the original name for later use in handling linking
                  if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                    externalLinkage.putError(originalName, entry.getCondition());
                  }
                }
              } else { // existing entry is not a function type
                scope.putError(originalName, entry.getCondition());
                recordInvalidGlobalDeclaration(originalName, entry.getCondition());
                // record the global/extern declaration using the original name for later use in handling linking
                if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                  externalLinkage.putError(originalName, entry.getCondition());
                }
                System.err.println(String.format("INFO: attempted to redeclare \"%s\" as function instead of non-function", originalName));
              }  // end of check for existing function type
            }  // end test of symtab entry type
          } // end loop over symtab entries
        }
              
        combinedCond.delRef();
      } // end of loop over declarators
      typespecifierCond.delRef();
    } // end of loop over typespecifiers
    prototype.declarator.destruct();
    prototype.declarator = newDeclarations;
    prototype.typespecifier.destruct();
    prototype.typespecifier = newTypes;
  } 
} CompoundStatement
{
  PresenceCondition pc = subparser.getPresenceCondition();
          
  // add all variations of the function declaration to the symtab
  CContext scope = (CContext)subparser.scope;

  Multiverse<Node> prototypeNodemv = staticCondToMultiverse(getNodeAt(subparser, 3), pc);

  Multiverse<String> resultmv = new Multiverse<String>();
  
  for (Element<Node> prototypeNode : prototypeNodemv) {
    FunctionPrototypeValue prototype = (FunctionPrototypeValue) getTransformationValue(prototypeNode.getData());
    Multiverse<TypeSpecifier> typespecifiermv = prototype.typespecifier;
    Multiverse<Declarator> declaratormv = prototype.declarator;

    if (declaratormv.isEmpty()) {
      continue;
    }
    for (Element<TypeSpecifier> typespecifier : typespecifiermv) {
      PresenceCondition typespecifierCond = prototypeNode.getCondition().and(typespecifier.getCondition());
      for (Element<Declarator> declarator : declaratormv) {
        PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
        if (combinedCond.isFalse()) {
          combinedCond.delRef();
          continue;
        }
        Declaration renamedDeclaration = new Declaration(typespecifier.getData(), declarator.getData());
        String desugaredDeclaration;
        desugaredDeclaration = renamedDeclaration.toString();
        resultmv.add(desugaredDeclaration,combinedCond);
      }
    }
  }
  
  StringBuilder sb = new StringBuilder();
  if (! resultmv.isEmpty()) {
    Multiverse<String> subprototypestrmv = resultmv.filter(pc);
    resultmv.destruct();
    
    Multiverse<DeclarationOrStatementValue> bodymv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
    // declarations, including function definitions, should
    // appear unconditionally in the desugared output, since
    // renaming handles different configurations.  so add all
    // resulting definitions to a single element multiverse
    // under the true condition.
    for (Element<String> prototypestr : subprototypestrmv) {
      sb.append(prototypestr.getData());
      sb.append(" //M:" + getCompoundRange(bodymv, prototypestr.getCondition()) + "\n");
      sb.append("{\n");
      sb.append(emitStatementDSV(bodymv, prototypestr.getCondition()));
      sb.append("}\n");
    }
    bodymv.destruct();
  } else {
    // the prototype can be empty if there are type errors.
    System.err.println("/* no function due to type errors in the function prototype */\n");
    sb.append("/* no function due to type errors in the function prototype */\n");
  }
  setTransformationValue(value, sb.toString());
}
        /* | FunctionOldPrototype CompoundStatement */
        | FunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE FunctionCompoundStatement { ExitScope(subparser); } RBRACE
        /* | FunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE CompoundStatement { ExitScope(subparser); } RBRACE */
        {
          // TODO
          System.err.println("ERROR: unsupported semantic action: FunctionDefinition");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;
/* FunctionCompoundStatement is now only for old prototypes. */
/* Functions have their own compound statement because of the need for
   reentering scope. */
FunctionCompoundStatement:  /** nomerge, name(CompoundStatement) **/  // String
        LocalLabelDeclarationListOpt DeclarationOrStatementList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);

          Multiverse<String> locallabelmv = getCompleteNodeSingleValue(subparser, 2, pc);
          Multiverse<String> declorstmtmv = getCompleteNodeSingleValue(subparser, 1, pc);
          
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(concatMultiverseStrings(locallabelmv)); locallabelmv.destruct();
          // print user-defined type declarations at top of scope
          valuesb.append(scope.getDeclarations(subparser.getPresenceCondition()));
          // DeclarationOrStatementList already resolves
          // configurations, so just print all the possible strings
          // under the static conditional
          valuesb.append(concatMultiverseStrings(declorstmtmv)); declorstmtmv.destruct();

          setTransformationValue(value, valuesb.toString());
        }
        ;

/* Having a function prototype node in the AST allows this to be a
   complete AST.  So if something in the prototype is configurable,
   the conditional will only be hoisted around the prototype, not the
   entire function definition. */
FunctionPrototype:  /** complete **/
        IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          bindFunDef(subparser, null, getNodeAt(subparser, 1));

          // functions without a type-specifier default to int
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(new Language<CTag>(CTag.INT));
          setTransformationValue(value,
                                 new FunctionPrototypeValue(new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition()),
                                                            this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | DeclarationSpecifier     IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        |                          OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (6)");
          subparser.lookahead.setError();
          //System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (7)");
          subparser.lookahead.setError();
          //System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (8)");
          subparser.lookahead.setError();
          //System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (9)");
          subparser.lookahead.setError();
          //System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (10)");
          subparser.lookahead.setError();
          //System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
        ;

FunctionOldPrototype:  /** nomerge **/
        OldFunctionDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

/* Nested function's declarator can't just be an IdentifierDeclarator
   or it gets a conflict.  gcc seems to behave this way too since it
   yields a parsing error. */
NestedFunctionDefinition:  /** complete **/ // added scoping
        NestedFunctionPrototype
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition");
          subparser.lookahead.setError();
          //System.exit(1);
        } CompoundStatement {
        }
        | NestedFunctionOldPrototype { ReenterScope(subparser); } DeclarationList LBRACE LocalLabelDeclarationListOpt DeclarationOrStatementList { ExitScope(subparser); } RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

NestedFunctionPrototype:  /** nomerge **/
          DeclarationSpecifier     IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | TypeSpecifier            IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | TypeQualifierList        IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
        | DeclarationSpecifier     OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(5)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(6)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(7)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(8)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

NestedFunctionOldPrototype:  /** nomerge **/
        DeclarationSpecifier       OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeSpecifier            OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | DeclarationQualifierList OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeQualifierList        OldFunctionDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          subparser.lookahead.setError();
          //System.exit(1);
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

DeclarationExtension:  /** complete **/  // ADDED  // List<Multivese<String>>
        Declaration
        {
          setTransformationValue(value, getCompleteNodeListValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | __EXTENSION__ Declaration
        {
          List<Multiverse<String>> declmv = getCompleteNodeListValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          for (Multiverse<String> d : declmv) {
            d = d.prependScalar(getNodeAt(subparser, 2).getTokenText(), DesugarOps.concatStrings);
          }
          setTransformationValue(value, declmv);
        }
        ;

Declaration:  /** complete **/  // List<Multiverse<String>>
        SUEDeclarationSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
        	Multiverse<TypeSpecifier> structtypesmv
            = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 3, pc);
          StringBuilder sb = new StringBuilder();  // the desugared output
          Multiverse<String> m = new Multiverse<String>();
          m.add("",pc);
          for (Element<TypeSpecifier> typespecifier : structtypesmv) {
            typespecifier.getData().addTransformation((Syntax)getNodeAt(subparser, 1));
            if (! typespecifier.getData().getType().isError()) {
              sb.append(typespecifier.getData().toString());
              m = appendStringToMV(m,typespecifier.getData().toString(),typespecifier.getCondition());
              
              sb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
              m = appendStringToMV(m,getNodeAt(subparser, 1).getTokenText(),typespecifier.getCondition());
              m = appendStringToMV(m,typespecLines(typespecifier.getData()),typespecifier.getCondition());
              
            } else {
              CContext scope = ((CContext) subparser.scope);
              if (scope.isGlobal()) {
                recordInvalidGlobalDeclaration("TODO_struct_tag1",
                                               typespecifier.getCondition());
              } else {
                // TODO: don't print if when it's always true
                sb.append("if (");
                m = appendStringToMV(m,"if (",typespecifier.getCondition());
                String x = condToCVar(typespecifier.getCondition());
                sb.append(x);
                m = appendStringToMV(m,x,typespecifier.getCondition());
                sb.append(") {\n");
                m = appendStringToMV(m,") {\n",typespecifier.getCondition());
                sb.append(emitError(String.format("invalid declaration of struct: %s",
                                                  /* typespecifier.getData().getStructTag()))); */
                                                  "TODO_struct_tag2")));
                m = appendStringToMV(m,emitError(String.format("invalid declaration of struct: %s",
                                                               /* typespecifier.getData().getStructTag()))); */
                                                               "TODO_struct_tag2")),typespecifier.getCondition());
                sb.append(";\n");
                m = appendStringToMV(m,";\n",typespecifier.getCondition());
                sb.append("}\n");
                m = appendStringToMV(m,"}" + typespecLines(typespecifier.getData()) + "\n",typespecifier.getCondition());
              }
            }
          }
          sb.append("\n");
          m = appendStringToMV(m,"\n",pc);
          List<Multiverse<String>> l = new LinkedList<Multiverse<String>>();
          l.add(m);
          setTransformationValue(value, l);
        }
        | SUETypeSpecifier { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();

        	Multiverse<TypeSpecifier> structtypesmv
            = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 3, pc);
          StringBuilder sb = new StringBuilder();  // the desugared output
          Multiverse<String> m = new Multiverse<String>();
          m.add("",pc);
          
          for (Element<TypeSpecifier> typespecifier : structtypesmv) {
            if (! typespecifier.getData().getType().isError()) {
              sb.append(typespecifier.getData().toString());
              m = appendStringToMV(m,typespecifier.getData().toString(),typespecifier.getCondition());
              sb.append(getNodeAt(subparser, 1).getTokenText());  // semi-colon
              m = appendStringToMV(m,getNodeAt(subparser, 1).getTokenText(),typespecifier.getCondition());
              m = appendStringToMV(m,typespecLines(typespecifier.getData()),typespecifier.getCondition());
              
            } else {
              CContext scope = ((CContext) subparser.scope);
              if (scope.isGlobal()) {
                /* recordInvalidGlobalDeclaration(typespecifier.getData().getStructTag(), */
                recordInvalidGlobalDeclaration("TODO_struct_tag3",
                                               typespecifier.getCondition());
              } else {
                sb.append("if (");
                m = appendStringToMV(m,"if (",typespecifier.getCondition());
                String x = condToCVar(typespecifier.getCondition());
                sb.append(x);
                m = appendStringToMV(m,x,typespecifier.getCondition());
                sb.append(") {\n");
                m = appendStringToMV(m,") {\n",typespecifier.getCondition());
                sb.append(emitError(String.format("invalid declaration of struct: %s",
                                                  /* typespecifier.getData().getStructTag()))); */
                                                  "TODO_struct_tag4")));
                m = appendStringToMV(m,emitError(String.format("invalid declaration of struct: %s",
                                                               /* typespecifier.getData().getStructTag()))); */
                                                               "TODO_struct_tag4")),typespecifier.getCondition());
                sb.append(";\n");
                m = appendStringToMV(m,";\n",typespecifier.getCondition());
                sb.append("}\n");
                m = appendStringToMV(m,"}" + typespecLines(typespecifier.getData()) + "\n",typespecifier.getCondition());
              }
            }
          }
          sb.append("\n");
          m = appendStringToMV(m,"\n",pc);
          List<Multiverse<String>> l = new LinkedList<Multiverse<String>>();
          l.add(m);
          setTransformationValue(value, l);
        }
        | DeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);
          
        	List<DeclaringListValue> declaringlistvalues = getCompleteNodeDeclaringListValueList(subparser, 3);
          String semi = getNodeAt(subparser, 1).getTokenText();
          semi += declaringListRange(declaringlistvalues,(Syntax)getNodeAt(subparser,1));          
          //List<Multiverse<String>> valuestring = declarationAction(declaringlistvalues, semi, pc, scope);
          //          
          //semi += declaringListRange(declaringlistvalues,(Syntax)getNodeAt(subparser,1));
          semi += "\n";
          List<Multiverse<String>> valuestring;
          if (scope.isGlobal()) {
            valuestring = declarationAction(declaringlistvalues, semi, pc, scope);
          } else {
            valuestring = declAddSemi(declaringlistvalues, semi, pc);
          }
          setTransformationValue(value, valuestring);
        }
        | DefaultDeclaringList { KillReentrantScope(subparser); } SEMICOLON
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);
          
        	List<DeclaringListValue> declaringlistvalues = getCompleteNodeDeclaringListValueList(subparser, 3);
          String semi = getNodeAt(subparser, 1).getTokenText();
          semi += declaringListRange(declaringlistvalues,(Syntax)getNodeAt(subparser,1));          
          semi += "\n";
          List<Multiverse<String>> valuestring;
          if (scope.isGlobal()) {
            valuestring = declarationAction(declaringlistvalues, semi, pc, scope);
          } else {
            valuestring = declAddSemi(declaringlistvalues, semi, pc);
          }
          setTransformationValue(value, valuestring);
        }
        ;

/* Note that if a typedef were  redeclared,  then  a  declaration
   specifier must be supplied */

DefaultDeclaringList:  /** nomerge **/  /* Can't  redeclare typedef names */
        DeclarationQualifierList IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(new Language<CTag>(CTag.INT));
          Multiverse<TypeSpecifier> inttbmv
            = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          types = types.product(inttbmv, DesugarOps.specifierProduct);  // don't destruct prior types, since it is a semantic value
          inttbmv.destruct();
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);;
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }
        | TypeQualifierList IdentifierDeclarator
        {

          //TODO : If EmptyInitializer, check how semicolon is added. 
          
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(new Language<CTag>(CTag.INT));
          Multiverse<TypeSpecifier> inttbmv
            = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          types = types.product(inttbmv, DesugarOps.specifierProduct);  // don't destruct prior types, since it is a semantic value
          inttbmv.destruct();
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);;
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }          
        | DefaultDeclaringList COMMA AttributeSpecifierListOpt IdentifierDeclarator
        {
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          PresenceCondition pc = subparser.getPresenceCondition();
          List<DeclaringListValue> declaringlist = getCompleteNodeDeclaringListValueList(subparser, 4);
          assert declaringlist.size() > 0;
          Multiverse<TypeSpecifier> types = declaringlist.get(0).typespecifier;
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);;
          List<DeclaringListValue> declaringlist = getCompleteNodeDeclaringListValueList(subparser,8);
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }
        ;

DeclaringList:  /** nomerge **/
        DeclarationSpecifier Declarator {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);;
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }
        | TypeSpecifier Declarator {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);;
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }
        | DeclaringList COMMA AttributeSpecifierListOpt Declarator
        {
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
          PresenceCondition pc = subparser.getPresenceCondition();
          List<DeclaringListValue> declaringlist = getCompleteNodeDeclaringListValueList(subparser, 4);
          assert declaringlist.size() > 0;
          Multiverse<TypeSpecifier> types = declaringlist.get(0).typespecifier;
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!((CContext) subparser.scope).isGlobal()) {
            Multiverse<String> combo = declarationListAction(types,declarators,subparser.getPresenceCondition(),((CContext) subparser.scope));
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),combo));
          } else {
            setTransformationValue(value, new DeclaringListValue(types,declarators,new Multiverse<Initializer>(new EmptyInitializer(),subparser.getPresenceCondition()),pc));
          }
        } AssemblyExpressionOpt AttributeSpecifierListOpt InitializerOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Initializer> initializers = this.<Initializer>getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclaringListValue decl = getCompleteNodeDeclaringListValue(subparser,4,pc);
          List<DeclaringListValue> declaringlist = getCompleteNodeDeclaringListValueList(subparser,8);
          if (((CContext) subparser.scope).isGlobal()) {
            decl.initializer = initializers;
            declaringlist.add(decl);
          } else {
            setupInitials(declaringlist,decl,initializers,pc,((CContext) subparser.scope));
          }
          setTransformationValue(value, declaringlist);
        }
        ;


DeclarationSpecifier:  /**  nomerge **/
        BasicDeclarationSpecifier        /* Arithmetic or void */
				{
          PresenceCondition pc = subparser.getPresenceCondition();
        	Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
	  			setTransformationValue(value, decl);
				}
        | SUEDeclarationSpecifier          /* struct/union/enum */
				{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
        | TypedefDeclarationSpecifier      /* typedef*/
				{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
        | VarArgDeclarationSpecifier  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
        | TypeofDeclarationSpecifier // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
        ;

TypeSpecifier:  /** complete **/ // Multiverse<TypeSpecifer>
        BasicTypeSpecifier                 /* Arithmetic or void */
				{
          // TODO: are there any issues with sharing references to the same type builder object?
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
        | SUETypeSpecifier                 /* Struct/Union/Enum */
				{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
				| TypedefTypeSpecifier             /* Typedef */
				{
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
        | VarArgTypeSpecifier  // ADDED
				{
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
        | TypeofTypeSpecifier // ADDED
				{
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
        ;

DeclarationQualifierList:  /** list, complete **/  /* const/volatile, AND storage class */
        StorageClass
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  setTransformationValue(value, storage);
      	  updateSpecs(subparser,
          getSpecsAt(subparser, 1),
          value);
      	}
      	| TypeQualifierList StorageClass
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!qualList.isEmpty() && !storage.isEmpty()) {
            Multiverse<TypeSpecifier> tb = qualList.product(storage, DesugarOps.specifierProduct);
            setTransformationValue(value, tb);
          } else {
            TypeSpecifier E = new TypeSpecifier();
            E.setError();
            setTransformationValue(value,new Multiverse<TypeSpecifier>(E,pc));
          }
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | DeclarationQualifierList DeclarationQualifier
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          if (!qualList.isEmpty() && !qual.isEmpty()) {
            Multiverse<TypeSpecifier> tb = qualList.product(qual, DesugarOps.specifierProduct);
            setTransformationValue(value, tb);
          } else {
            TypeSpecifier E = new TypeSpecifier();
            E.setError();
            setTransformationValue(value,new Multiverse<TypeSpecifier>(E,pc));
          }
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
        ;

TypeQualifierList:  /** list, complete **/
        TypeQualifier
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  setTransformationValue(value, qual);
    	    updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
      	}
        | TypeQualifierList TypeQualifier
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  Multiverse<TypeSpecifier> tb = qualList.product(qual, DesugarOps.specifierProduct);
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
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, qual);
        }
        | StorageClass
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, storage);
        }
        ;

TypeQualifier:    // const, volatile, and restrict can have underscores
        ConstQualifier
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitConstantQualifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> qual = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | VolatileQualifier
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitVolatileQualifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> qual = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | RestrictQualifier
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitRestrictQualifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> qual = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | AttributeSpecifier // ADDED
        {
          TypeSpecifier ts = new TypeSpecifier();
          todoReminder("collect attributes in AttributeSpecifier");
          Multiverse<TypeSpecifier> valuemv = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        | FunctionSpecifier  // ADDED
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitFunctionSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> qual = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, qual);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
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

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
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

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
RestrictQualifier:   // ADDED
        RESTRICT
        {
        }
        | __RESTRICT
        {
        }
        | __RESTRICT__
        {
        }
        ;

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
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

BasicDeclarationSpecifier: /** complete **/      /*StorageClass+Arithmetic or void*/
        BasicTypeSpecifier  StorageClass
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> basicTypeSpecifier = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> storageClass = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = basicTypeSpecifier.product(storageClass, DesugarOps.specifierProduct);

          setTransformationValue(value, tb);
          updateSpecs(subparser,
                    getSpecsAt(subparser, 2),
                    getSpecsAt(subparser, 1),
                    value);
        }
        | DeclarationQualifierList BasicTypeName {
          PresenceCondition pc = subparser.getPresenceCondition();

	        Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> basicTypeName = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          if (!qualList.isEmpty() && !basicTypeName.isEmpty()) {
            Multiverse<TypeSpecifier> tb = qualList.product(basicTypeName, DesugarOps.specifierProduct);
            setTransformationValue(value, tb);
          } else {
            TypeSpecifier E = new TypeSpecifier();
            E.setError();
            setTransformationValue(value,new Multiverse<TypeSpecifier>(E,pc));
          }
          updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier DeclarationQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicDeclarationSpecifier BasicTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

	        Multiverse<TypeSpecifier> basicDeclSpecifier = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> basicTypeName = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = basicDeclSpecifier.product(basicTypeName, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

BasicTypeSpecifier: /**  complete **/  // Multiverse<TypeSpecifier>
        BasicTypeName           /* Arithmetic or void */
        {
          // TUTORIAL: a semantic action that sets the semantic value
          // to a new typespecifier by adding a property derived from
          // the child semantic value(s)
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);

        }
        | TypeQualifierList BasicTypeName
	      {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> basicTypeName = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          Multiverse<TypeSpecifier> tb = qualList.product(basicTypeName, DesugarOps.specifierProduct);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier TypeQualifier
	      {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> basicTypeSpecifier = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          Multiverse<TypeSpecifier> tb = basicTypeSpecifier.product(qual, DesugarOps.specifierProduct);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | BasicTypeSpecifier BasicTypeName
        {
          // get the semantic values of each child
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> basicTypeSpecifier = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> basicTypeName = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = basicTypeSpecifier.product(basicTypeName, DesugarOps.specifierProduct);

          setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

SUEDeclarationSpecifier: /** complete **/          /* StorageClass + struct/union/enum */   // Multiverse<TypeSpecifier>
        SUETypeSpecifier StorageClass
        {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | DeclarationQualifierList ElaboratedTypeName
        {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | SUEDeclarationSpecifier DeclarationQualifier
        {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        ;

SUETypeSpecifier: /** complete **/
        ElaboratedTypeName              /* struct/union/enum */
        {
          PresenceCondition pc = subparser.getPresenceCondition();

        	setTransformationValue(value,
            this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | TypeQualifierList ElaboratedTypeName
        {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | SUETypeSpecifier TypeQualifier
        {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        ;


TypedefDeclarationSpecifier: /** complete **/       /*Storage Class + typedef types */
        TypedefTypeSpecifier StorageClass
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | DeclarationQualifierList TYPEDEFname
        {
          // TODO: needs a unit test
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> qualtbmv = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry<Type>> entries
            = ((CContext)subparser.scope).getInAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
      	  Multiverse<TypeSpecifier> typedefnametbmv = DesugarOps.typedefEntriesToTypeSpecifier.transform(entries);
          // combine with the existing qualifier list
          Multiverse<TypeSpecifier> combinedtbmv = qualtbmv.product(typedefnametbmv, DesugarOps.specifierProduct);
          typedefnametbmv.destruct();
          setTransformationValue(value, combinedtbmv);
        }
        | TypedefDeclarationSpecifier DeclarationQualifier
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<TypeSpecifier> tbF = tb.product(tb1, DesugarOps.specifierProduct);
          setTransformationValue(value, tbF);
        }
        ;

TypedefTypeSpecifier: /** complete **/              /* typedef types */
        TYPEDEFname
      	{
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry<Type>> entries
            = ((CContext)subparser.scope).getInAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
          Multiverse<TypeSpecifier> typedefnametbmv = DesugarOps.typedefEntriesToTypeSpecifier.transform(entries);
          setTransformationValue(value, typedefnametbmv);
        }
        | TypeQualifierList TYPEDEFname
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualtbmv = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry<Type>> entries
            = ((CContext)subparser.scope).getInAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
      	  Multiverse<TypeSpecifier> typedefnametbmv = DesugarOps.typedefEntriesToTypeSpecifier.transform(entries);
          // combine with the existing qualifier list
          Multiverse<TypeSpecifier> combinedtbmv = qualtbmv.product(typedefnametbmv, DesugarOps.specifierProduct);
          typedefnametbmv.destruct();
          setTransformationValue(value, combinedtbmv);
      	}
        | TypedefTypeSpecifier TypeQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        ;

TypeofDeclarationSpecifier: /** complete **/      /*StorageClass+Arithmetic or void*/
        TypeofTypeSpecifier  StorageClass
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | DeclarationQualifierList Typeofspecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeofDeclarationSpecifier DeclarationQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeofDeclarationSpecifier Typeofspecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

TypeofTypeSpecifier: /** complete **/  // ADDED
        Typeofspecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          
      	  setTransformationValue(value, decl);
        }
        | TypeQualifierList Typeofspecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeofTypeSpecifier TypeQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        | TypeofTypeSpecifier Typeofspecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

 	        Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = decl.product(qual, DesugarOps.specifierProduct);

      	  setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
        ;

Typeofspecifier: /** complete **/  // ADDED
        Typeofkeyword LPAREN TypeName RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<TypeSpecifier> tmv = getCompleteNodeMultiverseValue(subparser, 4, pc);
          for (Element<TypeSpecifier> e : tmv) {
            TypeSpecifier t = new TypeSpecifier(e.getData());
            
            t.addTransformation(((Syntax) getNodeAt(subparser, 3)));
            e.setData(t);
          }
          Multiverse<Declaration> dmv = getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> newtm = new Multiverse<TypeSpecifier>();
          for (Element<Declaration> d : dmv) {
            for (Element<TypeSpecifier> t : tmv) {
              PresenceCondition p = t.getCondition().and(d.getCondition());
              if (p.isNotFalse()) {
                TypeSpecifier ts = new TypeSpecifier(t.getData());
                ts.visitTypeofSpecifier(d.getData().getType());
                ts.addTransformation(new Layout(d.getData().toString()));
                newtm.add(ts, p);
              }
              p.delRef();
            }
          }
          tmv.destruct(); dmv.destruct();
          for (Element<TypeSpecifier> e : newtm) {
            e.getData().addTransformation(((Syntax) getNodeAt(subparser, 1)));
          }
          setTransformationValue(value, newtm);
        }
        | Typeofkeyword LPAREN Expression RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<TypeSpecifier> tmv = getCompleteNodeMultiverseValue(subparser, 4, pc);
          for (Element<TypeSpecifier> e : tmv) {
            TypeSpecifier t = new TypeSpecifier(e.getData());
            t.addTransformation(((Syntax) getNodeAt(subparser, 3)));
            e.setData(t);
          }
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> newtm = new Multiverse<TypeSpecifier>();
          for (Element<Type> e : exprval.type) {
            String standin = "";
            if (e.getData() != ErrorT.TYPE) {
              standin = freshCId("typeofStandin");
              ((CContext)subparser.scope).addDeclaration("typeof("+ e.getData().printType()+")" + standin + ";\n");
            }
            for (Element<TypeSpecifier> t : tmv) {
              //add a declaration of a dummy variable at the top of scope to use instead
              //for user defined types
              PresenceCondition p = t.getCondition().and(e.getCondition());
              if (p.isNotFalse()) {
                TypeSpecifier ts = new TypeSpecifier(t.getData());
                ts.visitTypeofSpecifier(e.getData());
                ts.addTransformation(new Layout(standin));
                if (e.getData() == ErrorT.TYPE) {
                  ts.setError();
                }
                System.err.println(e.getData() + ":" + ts.getType());
                newtm.add(ts, p);
              }
              p.delRef();
            }
          }
          tmv.destruct();
          for (Element<TypeSpecifier> e : newtm) {
            e.getData().addTransformation(((Syntax) getNodeAt(subparser, 1)));
          }
          
          setTransformationValue(value, newtm);
        }
        ;

Typeofkeyword: /** complete **/  // ADDED
        TYPEOF
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> res = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, res);
        }
        | __TYPEOF
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> res = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, res);
        }
        | __TYPEOF__
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> res = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, res);
        }
        ;

VarArgDeclarationSpecifier:      /*StorageClass+Arithmetic or void*/
        VarArgTypeSpecifier StorageClass
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | DeclarationQualifierList VarArgTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | VarArgDeclarationSpecifier DeclarationQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | VarArgDeclarationSpecifier VarArgTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        ;

VarArgTypeSpecifier:
        VarArgTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | TypeQualifierList VarArgTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | VarArgTypeSpecifier TypeQualifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        | VarArgTypeSpecifier VarArgTypeName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
        ;

VarArgTypeName:  // ADDED
        __BUILTIN_VA_LIST
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitVarArgListSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> tb = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, tb);
        }
        ;

// TODO: syntax
StorageClass:
        TYPEDEF
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitTypedefSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF;
        }
        | EXTERN
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitExternSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN;
        }
        | STATIC
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitStaticSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC;
        }
        | AUTO
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitAutoSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO;
        }
        | REGISTER
        {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitRegisterSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_REGISTER;
        }
        ;

// TODO: syntax
BasicTypeName:
        VOID
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitVoidTypeSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).type = VoidT.TYPE;

        }
        | CHAR
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitChar();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenChar = true;
        }
        | SHORT
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitShort();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenShort = true;
        }
        | INT
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenInt = true;
        }
        | __INT128
        {
          // TODO: support int128 in typespecifier
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenInt = true;
        }
        | LONG
        {
          // See xtc.type.* for the class hiearchy for types
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitLong();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).longCount++;
        }
        | FLOAT
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitFloat();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenFloat = true;
        }
        | DOUBLE
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitDouble();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenDouble = true;
        }
        | SignedKeyword
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitSigned();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenSigned = true;
        }
        | UNSIGNED
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitUnsigned();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenUnsigned = true;
        }
        | _BOOL
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitBool();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenBool = true;
        }
        | ComplexKeyword
        {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitComplex();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenComplex = true;
        }
        ;

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
SignedKeyword:
          SIGNED
        | __SIGNED
        | __SIGNED__
        ;

// These are intentionally empty, since the caller knows the qualifier
// for building the type specifier.
ComplexKeyword:
          _COMPLEX
        | __COMPLEX__
        ;

ElaboratedTypeName: /** complete **/
        StructOrUnionSpecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();
        	setTransformationValue(value, this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        /* StructSpecifier */
        /* { */
        /* 	setTransformationValue(value, */
        /*     this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser,1)); */
        /* } */
        /* | UnionSpecifier */
        /* { */
        /*   System.err.println("ERROR: unsupported semantic action: ElaboratedTypeName"); */
        /*   System.exit(1); */
        /* } */
        | EnumSpecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();
        	setTransformationValue(value, this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

/**
 * This construct represents all possible configurations of a struct
 * specifier.  Struct specifiers are type specifiers, so they are
 * represented by (a subclass of) TypeSpecifier.  To preserve all
 * configurations of it, these actions produce
 * Multiverse<TypeSpecifier>.
 */
// transformation notes:
//   - we can either take all combinations of declaration lists and make a new, renamed type spec
//   - or we can combine all fields into a single struct, renaming the fields
//   - for anonymous structs, there should be way for another struct to
//     have the same tag name, so just add it to the symtab referring to
//     itself
// TODO: check whether a struct is being declared in a parameter list, which is a wraning.
StructOrUnionSpecifier: /** complete **/  // ADDED attributes  // Multiverse<TypeSpecifier>
        STRUCT AttributeSpecifierListOpt LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = (Syntax) getNodeAt(subparser, 5);
          // TODO: add attributes to type spec
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          String structTag = freshCId("anonymous_tag");
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinitionWithFlex(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);
          setTransformationValue(value, valuemv);
        }
        | STRUCT AttributeSpecifierListOpt IDENTIFIER LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          Multiverse<Syntax> msy = getSyntaxMV(subparser, 6, pc);
          Syntax keyword = msy.get(0).getData();
          msy.destruct();
          // TODO: add attributes to type spec
          Multiverse<Syntax> structTag = getSyntaxMV(subparser, 4, pc);
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinitionMV(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);
          setTransformationValue(value, valuemv);
        }
        | STRUCT AttributeSpecifierListOpt TYPEDEFname LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
         
          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinitionWithFlex(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | STRUCT AttributeSpecifierListOpt IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);
	        setTransformationValue(value, valuemv);
        }
        | STRUCT AttributeSpecifierListOpt TYPEDEFname
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | UNION AttributeSpecifierListOpt LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = (Syntax) getNodeAt(subparser, 5);
          // TODO: add attributes to type spec
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          String structTag = freshCId("anonymous_tag");
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinitionWithFlex(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | UNION AttributeSpecifierListOpt IDENTIFIER LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinitionWithFlex(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | UNION AttributeSpecifierListOpt TYPEDEFname LBRACE StructDeclarationList RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | UNION AttributeSpecifierListOpt IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        | UNION AttributeSpecifierListOpt TYPEDEFname
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
        ;

/* UnionSpecifier: /\** complete **\/  // ADDED attributes */
/*         UNION { EnterScope(subparser); } LBRACE */
/*           StructDeclarationList { ExitScope(subparser); } */
/*         RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | UNION IdentifierOrTypedefName { EnterScope(subparser); } LBRACE */
/*           StructDeclarationList { ExitScope(subparser); } */
/*         RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | UNION IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | UNION AttributeSpecifierList { EnterScope(subparser); } LBRACE */
/*           StructDeclarationList { ExitScope(subparser); } */
/*         RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | UNION AttributeSpecifierList IdentifierOrTypedefName { EnterScope(subparser); } LBRACE */
/*           StructDeclarationList { ExitScope(subparser); } */
/*         RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         /\* { *\/ */
/*         /\*    updateSpecs(subparser, */
/*                           makeStruct()); *\/ */
/*         /\* } *\/ */
/*         | UNION AttributeSpecifierList IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: UnionSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         ; */

// TODO: use Multiverse<List<Declaration>> and wrap and concat the lists here instead

/*
 * This construct returns a list of declaration multiverses, i.e., a
 * list of declarations, where each declaration may be different
 * depending on the configuration.
 */
StructDeclarationList: /** list, complete **/  // List<Multiverse<Declaration>>
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

          PresenceCondition pc = subparser.getPresenceCondition().presenceConditionManager().newTrue();
          //PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);
          List<Multiverse<Declaration>> declarationvalues = this.<Declaration>getCompleteNodeListValue(subparser, 1, pc);
          structfields.addAll(declarationvalues);
          setTransformationValue(value, structfields);
        }
        ;

StructDeclaration: /** complete **/  // returns List<Multiverse<Declaration>>
        StructDeclaringList SEMICOLON
        {
          // TODO: implement like Declaration, except return a
          // multiverse of declarations instead of strings
          
	  List<StructDeclaringListValue> declaringlistvalues = getCompleteNodeStructDeclListValue(getNodeAt(subparser,2), subparser.getPresenceCondition());

          // take all combinations of type specifiers and declarators
          // and produce a multiverse of declaration objects.
          List<Multiverse<Declaration>> list = new LinkedList<Multiverse<Declaration>>();
          for (StructDeclaringListValue declaringlistvalue : declaringlistvalues) {
            // unpack type specifier, declarators, and initializers from the transformation value
            Multiverse<TypeSpecifier> typespecifiermv = declaringlistvalue.typespecifier;
            Multiverse<Declarator> declaratormv = declaringlistvalue.declarator;
            
            Multiverse<Declaration> declarationmv = new Multiverse<Declaration>();
            for (Element<TypeSpecifier> typespecifier : typespecifiermv) {
              PresenceCondition typespecifierCond = subparser.getPresenceCondition().and(typespecifier.getCondition());
              for (Element<Declarator> declarator : declaratormv) {
                PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
                Type t = typespecifier.getData().getType().resolve();
                if ((t.isStruct() || t.isUnion()) &&
                    ((StructOrUnionT)t).getName().startsWith("__forward_tag_reference_") &&
                    !declarator.getData().isPointerDeclarator()) {
                  TypeSpecifier ts = new TypeSpecifier();
                  ts.setType(new ErrorT());
                  declarationmv.add(new Declaration(ts, new EmptyDeclarator()), combinedCond);
                } else {
                  declarationmv.add(new Declaration(typespecifier.getData(), declarator.getData()), combinedCond);
                }
                combinedCond.delRef();
              } // end loop over declarators
              typespecifierCond.delRef();
            } // end loop over typespecifiers
            assert ! declarationmv.isEmpty();
            list.add(declarationmv);
          } // end loop of declaring list values
          // should be non-empty since structdeclaringlist cannot be
          // empty

          setTransformationValue(value, list);
        }
        | StructDefaultDeclaringList SEMICOLON
        {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeQualifierList SEMICOLON  // ADDED Declarator is optional
        {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (3)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | TypeSpecifier SEMICOLON  // ADDED Declarator is optional
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> typespecmv = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declaration> valuemv = DesugarOps.typespecToDeclaration.transform(typespecmv);
          for (Element<Declaration> e : valuemv) {
            if (!e.getData().hasName()) {
              e.setData(new Declaration(e.getData().getTypeSpec(),new SimpleDeclarator(freshAnonId())));
              
            }
          }
          List<Multiverse<Declaration>> list = new LinkedList<Multiverse<Declaration>>();
          list.add(valuemv);
          setTransformationValue(value, list);
        }
        | SEMICOLON // ADDED gcc allows empty struct field in declaration
        {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (5)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

StructDefaultDeclaringList: /** list, complete **/        /* doesn't redeclare typedef*/
        TypeQualifierList StructIdentifierDeclarator AttributeSpecifierListOpt
        {
          System.err.println("ERROR: unsupported semantic action: StructDefaultDeclaringList (1)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | StructDefaultDeclaringList COMMA StructIdentifierDeclarator AttributeSpecifierListOpt
        {
          System.err.println("ERROR: unsupported semantic action: StructDefaultDeclaringList (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

StructDeclaringList: /** list, complete **/  // returns List<StructDeclaringListValue>
        TypeSpecifier StructDeclarator AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          List<StructDeclaringListValue> declaringlist = new LinkedList<StructDeclaringListValue>();
          Multiverse<TypeSpecifier> typespecifiers = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          System.err.println("TODO: support attribuetspecifierlistopt in StructDeclarator");
          declaringlist.add(new StructDeclaringListValue(typespecifiers, declarators));
	  setTransformationValue(value, declaringlist);
        }
        | StructDeclaringList COMMA StructDeclarator AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          List<StructDeclaringListValue> declaringlist = (List<StructDeclaringListValue>) getTransformationValue(subparser, 4);
          assert declaringlist.size() > 0;
          Multiverse<TypeSpecifier> typespecifiers = declaringlist.get(0).typespecifier;
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          System.err.println("TODO: support attribuetspecifierlistopt in StructDeclarator");
          declaringlist.add(new StructDeclaringListValue(typespecifiers, declarators));
          setTransformationValue(value, declaringlist);
        }
        ;


StructDeclarator: /** complete **/  // returns Multiverse<Declarator>
        Declarator BitFieldSizeOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> bitfieldsize = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          if (bitfieldsize.size() == 1 && bitfieldsize.get(0).getData().isEmptyDeclarator()) {
            // if there's no bitfieldsize, there should just be a multiverse of size one with an empty declarator
            setTransformationValue(value, declarator);
          } else {
            setTransformationValue(value, declarator.join(bitfieldsize, DesugarOps.joinBitFieldSize));
          }
        }
        | BitFieldSize
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          // pass along the bitfieldsize declarator by itself
          setTransformationValue(value,
				 (new Multiverse<Declarator>(new SimpleDeclarator(freshAnonId()),pc)).join(this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc),DesugarOps.joinBitFieldSize));
        }
        ;

StructIdentifierDeclarator: /** nomerge **/
        IdentifierDeclarator BitFieldSizeOpt
        {
          System.err.println("ERROR: unsupported semantic action: StructIdentifierDeclarator");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | BitFieldSize
        {
          System.err.println("ERROR: unsupported semantic action: StructIdentifierDeclarator");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

BitFieldSizeOpt: /** nomerge **/  // Multiverse<Declarator>, single, empty declarator means no bitfieldsize
        /* nothing */
        {
          setTransformationValue(value, new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition()));
        }
        | BitFieldSize
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          // pass along the bitfieldsize declarator by itself
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

BitFieldSize: /** nomerge **/  // Multiverse<Declarator>
        COLON ConstantExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          String colon = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Declarator> valuemv = new Multiverse<Declarator>();
          PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
          todoReminder("check that the bitfieldsize is a constant");
          for (Element<String> transformation : exprval.transformation) {
            PresenceCondition combinedCond = pc.and(transformation.getCondition());
            if (combinedCond.isNotFalse()) {
              Multiverse<Type> filtered = exprval.type.filter(combinedCond);
              assert filtered.size() == 1;  // desugarer should only have one type for each expression transformation
              if (filtered.get(0).getData().isNumber()) {
                valuemv.add(new BitFieldSizeDeclarator(transformation.getData(), filtered.get(0).getData()), combinedCond);
              } else {
                PresenceCondition newErrorCond = errorCond.or(combinedCond);
                errorCond.delRef(); errorCond = newErrorCond;
              }
              filtered.destruct();
            }
            combinedCond.delRef();
          }
          
          if (errorCond.isNotFalse()) {
            valuemv.add(new BitFieldSizeDeclarator(String.format("%s;", emitError("type error in BitFieldSize")),
                                                   ErrorT.TYPE),
                        errorCond);
          }
          assert null != valuemv;
          errorCond.delRef();
          setTransformationValue(value, valuemv);
        }
        ;

/* EnumSpecifier: /\** nomerge **\/  /\* ADDED attributes *\/ */
/*         ENUM LBRACE EnumeratorList RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM IdentifierOrTypedefName LBRACE EnumeratorList RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM LBRACE EnumeratorList COMMA RBRACE /\* ADDED gcc extra comma *\/ */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /\* ADDED gcc extra comma *\/ */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList LBRACE EnumeratorList RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList RBRACE */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList LBRACE EnumeratorList COMMA RBRACE /\* ADDED gcc extra comma *\/ */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList IdentifierOrTypedefName LBRACE EnumeratorList COMMA RBRACE /\* ADDED gcc extra comma *\/ */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         ; */

/* EnumSpecifier: /\** nomerge **\/  /\* ADDED attributes *\/ */
/*         ENUM EnumSpecifierList */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM IdentifierOrTypedefName EnumSpecifierList */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList EnumSpecifierList */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList IdentifierOrTypedefName EnumSpecifierList */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         | ENUM AttributeSpecifierList IdentifierOrTypedefName */
/*         { */
/*           System.err.println("ERROR: unsupported semantic action: EnumSpecifier"); */
/*           System.exit(1); */
/*         } */
/*         ; */

EnumSpecifier: /** complete **/  /* ADDED attributes */   // Multiverse<TypeSpecifier>
        ENUM AttributeSpecifierListOpt EnumSpecifierList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          String enumTag = freshCId("anonymous_tag");
          
          // TODO: add attributes to type spec
          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 1),
                                                                                                  subparser.getPresenceCondition());

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumDefinition(keyword, enumTag, freshCId(enumTag),list, pc, scope);
          setTransformationValue(value, valuemv);
        }
        | ENUM AttributeSpecifierListOpt IDENTIFIER EnumSpecifierList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 4));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 3),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          // TODO: add attributes to type spec
          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 1),
                                                                                                  subparser.getPresenceCondition());

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumDefinition(keyword, enumTag, freshCId(enumTag),list, pc, scope);
          setTransformationValue(value, valuemv);
        }
        | ENUM AttributeSpecifierListOpt TYPEDEFname EnumSpecifierList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 4));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 3),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          // TODO: add attributes to type spec
          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 1),
                                                                                                  subparser.getPresenceCondition());
          
          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumDefinition(keyword, enumTag, freshCId(enumTag), list, pc, scope);
          
          setTransformationValue(value, valuemv);
        }
        | ENUM AttributeSpecifierListOpt IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          // TODO: add attributes to type spec
          
          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumReference(keyword, enumTag, pc,(CContext)subparser.scope,freshIdCreator);
          setTransformationValue(value, valuemv);
        }
        | ENUM AttributeSpecifierListOpt TYPEDEFname
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          // TODO: add attributes to type spec

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumReference(keyword, enumTag, pc,(CContext)subparser.scope,freshIdCreator);
          
          setTransformationValue(value, valuemv);
        }
        ;

EnumSpecifierList: /** complete **/  /* ADDED attributes */ // List<Multiverse<EnumeratorValue>>
        LBRACE EnumeratorList RBRACE
        {
          setTransformationValue(value, this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 2),
                                                                                       subparser.getPresenceCondition()));
        }
        | LBRACE EnumeratorList COMMA RBRACE /* ADDED gcc extra comma */
        {
          setTransformationValue(value, this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 3),
                                                                                       subparser.getPresenceCondition()));
        }
        ;

/*EnumeratorList:
        IdentifierOrTypedefName EnumeratorValueOpt
        | EnumeratorList COMMA IdentifierOrTypedefName EnumeratorValueOpt
        ;*/

EnumeratorList:  /** list, complete **/  // easier to bind  // List<Multiverse<EnumeratorValue>>
        Enumerator
        {
          List<Multiverse<EnumeratorValue>> list = new LinkedList<Multiverse<EnumeratorValue>>();
          Multiverse<EnumeratorValue> enumerator
            = (Multiverse<EnumeratorValue>) this.<EnumeratorValue>getCompleteNodeMultiverseValue(subparser,
                                                                                                 1,
                                                                                                 subparser.getPresenceCondition());
          list.add(enumerator);
          setTransformationValue(value, list);
        }
        | EnumeratorList COMMA Enumerator
        {
          PresenceCondition pc = subparser.getPresenceCondition().presenceConditionManager().newTrue();

          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(subparser, 3, pc);
          Multiverse<EnumeratorValue> enumerator
            = (Multiverse<EnumeratorValue>) this.<EnumeratorValue>getCompleteNodeMultiverseValue(subparser,
                                                                                                 1,
                                                                                                 subparser.getPresenceCondition());
          list.add(enumerator);
          setTransformationValue(value, list);
        }
        ;

Enumerator: /** complete **/ // Multiverse<EnumeratorValue>
        IDENTIFIER { BindEnum(subparser); } EnumeratorValueOpt
        {
          todoReminder("record enum type errors in the global or local scope");
          CContext scope = ((CContext) subparser.scope);
          String name = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<EnumeratorValValue> val = (Multiverse<EnumeratorValValue>) getTransformationValue(subparser, 1);
          Multiverse<EnumeratorValue> enumeratorvaluemv = new Multiverse<EnumeratorValue>();
          for (Element<EnumeratorValValue> elem : val) {
            PresenceCondition valcond = subparser.getPresenceCondition().and(elem.getCondition());
            if (!elem.getData().hasValue() || (elem.getData().getType() != ErrorT.TYPE && (elem.getData().getType().hasConstant() ||
                                                                                           elem.getData().getType().hasAttribute(Constants.ATT_CONSTANT)))){
            
              Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(name, valcond);
              for (Element<SymbolTable.Entry<Type>> entry : entries) {
                String renaming = freshCId(name);
                PresenceCondition combinedCond = valcond.and(entry.getCondition());
                if (entry.getData().isError()) {
                  // this is already an error
                  System.err.println(String.format("INFO: enumerator \"%s\" is being redeclared in an existing invalid configuration",
                                                   name));
                  enumeratorvaluemv.add(new EnumeratorValue(name, renaming, ErrorT.TYPE), combinedCond);
                } else if (entry.getData().isUndeclared()) {
                  // create a new constant int declaration of the enumerator
                  TypeSpecifier ratortb = new TypeSpecifier();
                  /* Type ratortype = cOps.fit(ratorvalue); */  // TODO: support gcc's non-ISO large enumerators
                  // TODO: replace null with the actual value of the
                  // enumerator, if needed.  this may require keeping a
                  // multiverse of last values in the list of
                  // enumerators.
                  Type ratorbasetype = NumberT.INT.copy();
                  ratorbasetype.addAttribute(Constants.ATT_CONSTANT);
                  Type ratortype = new EnumeratorT(ratorbasetype, renaming, BigInteger.ONE);  // TODO: use real values if needed
                  
                  ratortb.setType(ratortype);
                  ratortb.visitConstantQualifier();
                  // the type specifier has no transformation value,
                  // because enumerators have no explicit type
                  // specifier.

                  scope.put(name, ratortype, combinedCond);

                  String transformation;
                  if (elem.getData().hasValue()) {
                    /* transformation = String.format("%s = %s", renaming, elem.getData().getTransformation()); */
                    todoReminder("type check values of enumerators");
                    transformation = String.format("%s = %s", renaming, elem.getData().getTransformation());
                  } else {
                    transformation = renaming;
                  }
                  enumeratorvaluemv.add(new EnumeratorValue(name, transformation, ratortype), combinedCond);
                } else {
                  System.err.println(String.format("redeclaration of enumerator \"%s\"",
                                                   name));
                  scope.putError(name, combinedCond);
                  enumeratorvaluemv.add(new EnumeratorValue(name, renaming, ErrorT.TYPE), combinedCond);
                }
                combinedCond.delRef();
              }
            } else { //the value being initialized is an error
              enumeratorvaluemv.add(new EnumeratorValue(name, "<error>", ErrorT.TYPE), valcond);
            }
            valcond.delRef();
          }
          assert ! enumeratorvaluemv.isEmpty();

          setTransformationValue(value, enumeratorvaluemv);

        }
        | TYPEDEFname  { BindEnum(subparser); } EnumeratorValueOpt
        {
          todoReminder("record enum type errors in the global or local scope");
          CContext scope = ((CContext) subparser.scope);
          String name = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<EnumeratorValValue> val = (Multiverse<EnumeratorValValue>) getTransformationValue(subparser, 1);
          Multiverse<EnumeratorValue> enumeratorvaluemv = new Multiverse<EnumeratorValue>();
          for (Element<EnumeratorValValue> elem : val) {
            PresenceCondition valcond = subparser.getPresenceCondition().and(elem.getCondition());

            Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(name, valcond);
            for (Element<SymbolTable.Entry<Type>> entry : entries) {
              String renaming = freshCId(name);
              PresenceCondition combinedCond = valcond.and(entry.getCondition());
              if (entry.getData().isError()) {
                // this is already an error
                System.err.println(String.format("INFO: enumerator \"%s\" is being redeclared in an existing invalid configuration", name));
                enumeratorvaluemv.add(new EnumeratorValue(name, renaming, ErrorT.TYPE), combinedCond);
              } else if (entry.getData().isUndeclared()) {
                // create a new constant int declaration of the enumerator
                TypeSpecifier ratortb = new TypeSpecifier();
                /* Type ratortype = cOps.fit(ratorvalue); */  // TODO: support gcc's non-ISO large enumerators
                // TODO: replace null with the actual value of the
                // enumerator, if needed.  this may require keeping a
                // multiverse of last values in the list of
                // enumerators.
                Type ratorbasetype = NumberT.INT;
                Type ratortype = new EnumeratorT(ratorbasetype, renaming, BigInteger.ONE);
                ratortb.setType(ratortype);
                // the type specifier has no transformation value,
                // because enumerators have no explicit type
                // specifier.

                scope.put(name, ratortype, combinedCond);

                String transformation;
                if (elem.getData().hasValue()) {
                  /* transformation = String.format("%s = %s", renaming, elem.getData().getTransformation()); */
                  todoReminder("type check values of enumerators");
                  transformation = String.format("%s = %s", renaming, elem.getData().getTransformation());
                } else {
                  transformation = renaming;
                }
                enumeratorvaluemv.add(new EnumeratorValue(name, transformation, ratortype), combinedCond);
              } else {
                System.err.println(String.format("redeclaration of enumerator \"%s\"",
                                                 name));
                scope.putError(name, combinedCond);
                enumeratorvaluemv.add(new EnumeratorValue(name, renaming, ErrorT.TYPE), combinedCond);
              }
              combinedCond.delRef();
            }
            valcond.delRef();
          }
          assert ! enumeratorvaluemv.isEmpty();

          setTransformationValue(value, enumeratorvaluemv);
        }
        ;

/* Enumerator: /\** nomerge **\/ // EnumeratorValue */
/*         IDENTIFIER { BindEnum(subparser); } EnumeratorValueOpt */
/*         { */
/*           String name = ((Syntax) getNodeAt(subparser, 3)).getTokenText(); */
/*           // TODO: handle valueopt and add to the EnumeratorValue class */
/*           setTransformationValue(value, new EnumeratorValue(name)); */
/*         } */
/*         | TYPEDEFname { BindEnum(subparser); } EnumeratorValueOpt */
/*         { */
/*           String name = ((Syntax) getNodeAt(subparser, 3)).getTokenText(); */
/*           // TODO: handle valueopt and add to the EnumeratorValue class */
/*           setTransformationValue(value, new EnumeratorValue(name)); */
/*         } */
/*         ; */

EnumeratorValueOpt: /** nomerge **/  // Multiverse<EnumeratorValValue>
        /* Empty */
        {
          
          setTransformationValue(value, new Multiverse<EnumeratorValValue>(new EnumeratorValValue(), subparser.getPresenceCondition()));
        }
        | ASSIGN ConstantExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<EnumeratorValValue> evmv = new Multiverse<EnumeratorValValue>();
          if (exprval.hasValidType()) {
            for (Element<String> transformation : exprval.transformation) {
              PresenceCondition combinedCond = pc.and(transformation.getCondition());
              if (combinedCond.isNotFalse()) {
                Multiverse<Type> filtered = exprval.type.filter(combinedCond);
                assert filtered.size() == 1;  // desugarer should only have one type for each expression transformation
                evmv.add(new EnumeratorValValue(transformation.getData(), filtered.get(0).getData()), combinedCond);
                filtered.destruct();
              }
              combinedCond.delRef();
            }
            if (evmv.isEmpty()) {
              todoReminder("double-check whether enumerator value can have empty mv due to type errors in the pc");
            }
            assert ! evmv.isEmpty();
          } else {  // expression mv is all type errors
            evmv.add(new EnumeratorValValue(null, ErrorT.TYPE), pc);
          }
          setTransformationValue(value, evmv);
        }
        ;

ParameterTypeList:  /** nomerge **/  // ParameterTypeListValue which contains List<Multiverse<Declaration>>
        ParameterList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<Declaration>> paramlist = this.<Declaration>getCompleteNodeListValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterTypeListValue(paramlist, false));
        }
        | ParameterList COMMA ELLIPSIS
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<Declaration>> paramlist = this.<Declaration>getCompleteNodeListValue(subparser, 3, pc);
          setTransformationValue(value, new ParameterTypeListValue(paramlist, true));
        }
        ;


// TODO: change the semantic value to Multiverse<List<Declaration>>
// and do the list wrapping and concatenating here
          
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
          PresenceCondition pc = subparser.getPresenceCondition().presenceConditionManager().newTrue();//subparser.getPresenceCondition();
          // add to the existing parameter list.  this reuse of a
          // semantic value may be an issue if static conditionals are
          // permitted under parameterlists
          List<Multiverse<Declaration>> parameters = this.<Declaration>getCompleteNodeListValue(subparser, 3, pc);
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
          for (Element<TypeSpecifier> typespecifier : declarationvalue.typespecifier) {
            PresenceCondition typespecifierCond = subparser.getPresenceCondition().and(typespecifier.getCondition());
            for (Element<Declarator> declarator : declarationvalue.declarator) {
              PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
	      if (combinedCond.isNotFalse()) {
		// for each combination of typespecifier and declarator

		// (1) rename the declarator part and create a
		// Declaration for use as the semantic value
		String originalName = declarator.getData().getName();
		String renaming = freshCId(originalName);
		Declarator renamedDeclarator = declarator.getData().rename(renaming);
		Declaration renamedDeclaration = new Declaration(typespecifier.getData(),
								 renamedDeclarator);

		valuemv.add(renamedDeclaration, combinedCond);
              
		// (2) add the parameter to the symbol table
		if (typespecifier.getData().getType().isError()) {
		  scope.putError(declarator.getData().getName(), combinedCond);
		} else {
		  // getName() shouldn't have an error, because thit is
		  // the identifierdeclaration.  abstract declarators
		  // can't go in the symbol table, because there is no
		  // symbol.
		  Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(declarator.getData().getName(), combinedCond);

		  // TODO: check for multiply-defined parameter names,
		  // which (I believe) should make the entire function
		  // declarator invalid.

		  for (Element<SymbolTable.Entry<Type>> entry : entries) {
		    if (entry.getData().isError()) {
		      System.err.println("INFO: invalid parameter declaration for function");
		      System.err.println("TODO: any invalid parameter declarations should cause the entire function declaration to be invalid under that condition");
		      scope.putError(declarator.getData().getName(), combinedCond);
		    } else if (entry.getData().isUndeclared()) {
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
		} // end of check for invalid typespecifier
	      }
              combinedCond.delRef();
            } // end loop over declarators
            typespecifierCond.delRef();
          } // end loop over typespecifiers
          // should be non-empty because
          // parameteridentifierdeclaration should always return a
          // typespecifiermv and declaratormv
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
          for (Element<TypeSpecifier> typespecifier : declarationvalue.typespecifier) {
            PresenceCondition typespecifierCond = subparser.getPresenceCondition().and(typespecifier.getCondition());
            for (Element<Declarator> declarator : declarationvalue.declarator) {
              PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
              Declaration declaration = new Declaration(typespecifier.getData(),
                                                        declarator.getData());

              // for each combination of typespecifier and declarator
              // create a Declaration for use in the semantic
              // value.  abstract declarators have no name, so should
              // not need to rename or add to a symtab.
              valuemv.add(declaration, combinedCond);
              
              combinedCond.delRef();
            } // end loop over declarators
            typespecifierCond.delRef();
          } // end loop over typespecifiers
          // should be non-empty because
          // parameteridentifierdeclaration should always return a
          // typespecifiermv and declaratormv
          assert ! valuemv.isEmpty();

          setTransformationValue(value, valuemv);
        }
        ;

/*
 * These actions just bundle the typespecifiers and declarators for
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
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationQualifierList
        {
          System.err.println("TODO: reimplement parameterabstractdeclaration (3)");
          System.exit(1);
        }
        | DeclarationQualifierList AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarators = new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeQualifierList
        {
          System.err.println("TODO: reimplement parameterabstractdeclaration (7)");
          System.exit(1);
        }
        | TypeQualifierList AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        ;

/*
 * These actions just bundle the typespecifiers and declarators for
 * processing by ParameterDeclaration
 */
ParameterIdentifierDeclaration:  // ParameterDeclarationValue
        DeclarationSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | DeclarationQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeSpecifier ParameterTypedefDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
        | TypeQualifierList IdentifierDeclarator
        {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        } AttributeSpecifierListOpt
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
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
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | IdentifierList COMMA Identifier
        {
          System.err.println("ERROR: unsupported semantic action: IdentifierList");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

Identifier:  /** nomerge **/
       IDENTIFIER
       {
         String originalName = ((Node)getNodeAt(subparser, 1)).getTokenText();
          //Multiverse<String> sbmv = new Multiverse<String>();
          //sbmv.add(new Element<String>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));

          CContext scope = (CContext) subparser.scope;

          // get the renamings from the symtab
          PresenceCondition cond = subparser.getPresenceCondition();
          Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(originalName, cond);

          // convert the renamings to stringbuilders
          Multiverse<String> sbmv = new Multiverse<String>();
          Multiverse<Type> typemv = new Multiverse<Type>();
          // any presence conditions with an error can be omitted from
          // the desugaring.  instead, this information is preserved
          // in the type value for use by the statement.
          /* System.err.println("IDENT: " + entries); */
          for (Element<SymbolTable.Entry<Type>> entry : entries) {
            if (entry.getData().isError()) {
              System.err.println(String.format("type error: use of symbol with invalid declaration: %s", originalName));
              typemv.add(ErrorT.TYPE, entry.getCondition());
              sbmv.add("error", entry.getCondition());
            } else if (entry.getData().isUndeclared()) {
              System.err.println(String.format("type error: use of undeclared symbol: %s", originalName));
              sbmv.add("error", entry.getCondition());
              typemv.add(ErrorT.TYPE, entry.getCondition());
            } else {
              // TODO: add type checking.  may need to tag the resulting
              // stringbuilder with the type to handle this

              if (entry.getData().getValue().isVariable()) {
                String result  // use the renamed symbol
                  = String.format(" %s ", entry.getData().getValue().toVariable().getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(entry.getData().getValue().toVariable().getType(), entry.getCondition());
              } else if (entry.getData().getValue() instanceof NamedFunctionT) {
                String result  // use the renamed symbol
                  = String.format(" %s ", ((NamedFunctionT) entry.getData().getValue()).getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(((NamedFunctionT) entry.getData().getValue()).toFunctionT(), entry.getCondition());
              } else if (entry.getData().getValue() instanceof EnumeratorT) {
                String result  // use the renamed symbol
                  = String.format(" %s ", entry.getData().getValue().toEnumerator().getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(entry.getData().getValue().toEnumerator().getType(), entry.getCondition());
              } else {
                System.err.println(String.format("type error: use of symbol other than variable, function, or enumerator: %s", originalName));
                sbmv.add("error", entry.getCondition());
                typemv.add(ErrorT.TYPE, entry.getCondition());
              }
            }
          }
          // should be nonempty, since the above loop always adds to
          // it and the symtab should always return a non-empty mv
          assert ! sbmv.isEmpty();
          entries.destruct();
          /* System.err.println(sbmv); */
          /* System.err.println(typemv); */

          setTransformationValue(value, new ExpressionValue(sbmv, typemv));
        
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

// This construct is used in places like casts, where you can specify
// the type spec and the abstract declarator (pointers, arrays, etc).
// So we use a declaration class, which holds both a typespec and a
// declarator.
TypeName: /** nomerge **/  // Multiverse<Declaration>
        TypeSpecifier
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarator
            = (Multiverse<Declarator>) new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
          declarator.destruct();
        }
        | TypeSpecifier AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
        }
        | TypeQualifierList
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarator
            = (Multiverse<Declarator>) new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
         declarator.destruct();
        }
        | TypeQualifierList AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
        }
        ;

InitializerOpt: /** complete **/ // Multiverse<Initializer>
        /* nothing */
        {
          // EmptyInitializer
          setTransformationValue(value, new Multiverse<Initializer>(new EmptyInitializer(),
                                                                    subparser.getPresenceCondition()));
        }
        | ASSIGN Initializer  // n1570.pdf section 6.7.9
        {
          // AssignmentInitializer
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          setTransformationValue(value, DesugarOps.toAssignInitializer.transform(initializers));
        }
        ;

/*InitializerStandard:  // ADDED gcc can have empty Initializer lists
        LBRACE InitializerList RBRACE
        | AssignmentExpression
        ;*/

Initializer: /** nomerge **/  // ADDED gcc can have empty Initializer lists // Multiverse<Initializer>
        LBRACE MatchedInitializerList RBRACE
        {
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 2);
          setTransformationValue(value, DesugarOps.toInitializerList.transform(lists));
        }
        | LBRACE MatchedInitializerList DesignatedInitializer RBRACE
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = getCompleteNodeMultiverseValue(subparser, 3,pc);
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform(getCompleteNodeMultiverseValue(subparser, 2,pc));
          Multiverse<List<Initializer>> cproduct = lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT);
          //lists.destruct(); newelem.destruct();
          setTransformationValue(value, DesugarOps.toInitializerList.transform(cproduct));
        }
        | AssignmentExpression
        {
          // ExpressionInitializer
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition());
          if (!exprval.isAlwaysError()) {
            setTransformationValue(value, exprval.type.join(exprval.transformation, DesugarOps.joinExpressionInitializer));
          } else {
            PresenceCondition errorCond = exprval.type.getConditionOf(ErrorT.TYPE);
            Multiverse<Initializer> mi = new Multiverse<Initializer>();
            if (!exprval.transformation.isEmpty()) {
              for (Element<String> e : exprval.transformation) {
                PresenceCondition combo = errorCond.and(e.getCondition());
                if (combo.isNotFalse()) {
                  Initializer i = new ExpressionInitializer(ErrorT.TYPE, e.getData());
                  mi.add(i,e.getCondition());
                }
                combo.delRef();
              }
            } else {
              Initializer i = new ExpressionInitializer(ErrorT.TYPE, "error");
              mi.add(i,errorCond);
            }
            errorCond.delRef();
            setTransformationValue(value, mi);
          }
        }
        ;

InitializerList:  /** nomerge **/ //modified so that COMMAS are on the right  // Multiverse<InitializerList>
        MatchedInitializerList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          // TODO: destruct return value from getTransformationValue
          setTransformationValue(value, (Multiverse<InitializerList>) getTransformationValue(subparser, 1));
        }
        | MatchedInitializerList DesignatedInitializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 2);
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform((Multiverse<Initializer>) getTransformationValue(subparser, 1));
          setTransformationValue(value, lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT));
          newelem.destruct();
        }
        ;

MatchedInitializerList:  /** list, nomerge **/  // Multiverse<InitializerList>
        /* empty */
        {
          setTransformationValue(value, new Multiverse<List>(new LinkedList<Initializer>(),
                                                                  subparser.getPresenceCondition()));
        }
        | MatchedInitializerList DesignatedInitializer COMMA
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = getCompleteNodeMultiverseValue(subparser, 3, pc);
          
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform((Multiverse<Initializer>) getTransformationValue(subparser, 2));
          setTransformationValue(value, lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT));
        }
        ;

DesignatedInitializer:/** nomerge, passthrough **/ /* ADDED */ // Multiverse<Initializer>
        Initializer
        {
          // pass through
          todoReminder("typecheck initializers DesignatedInitializer (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<Initializer> mv = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          setTransformationValue(value, mv);
        }
        | Designation Initializer
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          // DesignatedInitializer
          Multiverse<Designation> designations = getCompleteNodeMultiverseValue(subparser, 2,pc);
          Multiverse<Initializer> initializers = getCompleteNodeMultiverseValue(subparser, 1,pc);
          setTransformationValue(value, designations.join(initializers, DesugarOps.joinDesignatedInitializer));
        }
        ;

Designation:   /* ADDED */  // Multiverse<Designation>
        DesignatorList ASSIGN
        {
          // TODO: unit tests
          Multiverse<List<Designator>> list = (Multiverse<List<Designator>>) getTransformationValue(subparser, 2);
          setTransformationValue(value, DesugarOps.toDesignation.transform(list));
        }
        | ObsoleteArrayDesignation
        {
          System.err.println("ERROR: unsupported semantic action: Designation (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | ObsoleteFieldDesignation
        {
          System.err.println("ERROR: unsupported semantic action: Designation (3)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

DesignatorList:  /** list, nomerge **/  /* ADDED */  // Multiverse<List<Designator>>
        Designator
        {
          // TODO: unit tests
          Multiverse<Designator> designators = (Multiverse<Designator>) getTransformationValue(subparser, 1);
          Multiverse<List<Designator>> newlist = DesugarOps.designatorListWrap.transform(designators);
          setTransformationValue(value, newlist);
        }
        | DesignatorList Designator
        {
          // TODO: unit tests
          Multiverse<List<Designator>> list = (Multiverse<List<Designator>>) getTransformationValue(subparser, 2);
          Multiverse<Designator> designators = (Multiverse<Designator>) getTransformationValue(subparser, 1);
          Multiverse<List<Designator>> newlist = DesugarOps.designatorListWrap.transform(designators);
          setTransformationValue(value, list.complementedProduct(newlist, DesugarOps.DESIGNATORLISTCONCAT));
          newlist.destruct();
        }
        ;

// TODO: unit tests
Designator:   /* ADDED */  // Multiverse<Designator>
        LBRACK ConstantExpression RBRACK
        {
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          setTransformationValue(value,
                                 exprval.type.join(exprval.transformation, DesugarOps.joinArrayDesignator));
        }
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        {
          System.err.println("ERROR: unsupported semantic action: Designator (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | DOT IDENTIFIER //IDENTIFIER
        {
          todoReminder("replace the designator with the renamed struct field");
          setTransformationValue(value,
                                 new Multiverse<Designator>(new StructUnionDesignator(((Syntax) getNodeAt(subparser, 1)).getTokenText()),
                                                            subparser.getPresenceCondition()));
        }
        | DOT TYPEDEFname // ADDED hack to get around using typedef names as struct fields
        {
          todoReminder("replace the designator with the renamed struct field");
          setTransformationValue(value,
                                 new Multiverse<Designator>(new StructUnionDesignator(((Syntax) getNodeAt(subparser, 1)).getTokenText()),
                                                            subparser.getPresenceCondition()));
        }
        ;

ObsoleteArrayDesignation: /** nomerge **/  /* ADDED */
        LBRACK ConstantExpression RBRACK
        {
          System.err.println("ERROR: unsupported semantic action: ObsoleteArrayDesignation");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | LBRACK ConstantExpression ELLIPSIS ConstantExpression RBRACK
        {
          System.err.println("ERROR: unsupported semantic action: ObsoleteArrayDesignation");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

ObsoleteFieldDesignation: /** nomerge **/  /* ADDED */
        IDENTIFIER COLON
        {
          System.err.println("ERROR: unsupported semantic action: ObsoleteFieldDesignation");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

Declarator:  /** nomerge**/
        TypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | IdentifierDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

TypedefDeclarator:  /**  nomerge **/  // ADDED
        TypedefDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        ;

TypedefDeclaratorMain:  /**  nomerge **/
        ParenTypedefDeclarator  /* would be ambiguous as Parameter*/
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | ParameterTypedefDeclarator   /* not ambiguous as param*/
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 2)),
                                                                          subparser.getPresenceCondition());
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
          declarators.destruct();  // safe to destruct because not added as transformation value
          /* abstractdeclarators.destruct(); */
          // no need to filter since declarators started with subparser's pc
          setTransformationValue(value, valuemv);
        }
        | CleanTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

    /*  The  following have at least one STAR. There is no (redundant)
    LPAREN between the STAR and the TYPEDEFname. */

CleanTypedefDeclarator: /** nomerge **/
        CleanPostfixTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | STAR ParameterTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // TODO: do we need to conjoin with subparser.getPresenceCondition() in all these declarators?
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList ParameterTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.createQualifiedPointerDeclarator(declarators, qualifierlists);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
        | LPAREN CleanTypedefDeclarator RPAREN PostfixingAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | STAR LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
      	| STAR TypeQualifierList
      	LPAREN SimpleParenTypedefDeclarator RPAREN /* redundant paren */
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> valuemv = DesugarOps.createQualifiedPointerDeclarator(declarators, qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* qualifierlists.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR ParenTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList ParenTypedefDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.createQualifiedPointerDeclarator(declarators, qualifierlists);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
        | LPAREN SimpleParenTypedefDeclarator PostfixingAbstractDeclarator RPAREN /* redundant paren */
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | LPAREN ParenTypedefDeclarator RPAREN PostfixingAbstractDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | LPAREN SimpleParenTypedefDeclarator RPAREN
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
        ;

IdentifierDeclarator:  /**  nomerge **/
        IdentifierDeclaratorMain //AssemblyExpressionOpt AttributeSpecifierListOpt
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

IdentifierDeclaratorMain:  /** nomerge **/
        UnaryIdentifierDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        | ParenIdentifierDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        ;

UnaryIdentifierDeclarator: /** nomerge **/
        PostfixIdentifierDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        | STAR IdentifierDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
      	}
        | STAR TypeQualifierList IdentifierDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.createQualifiedPointerDeclarator(declarators, qualifierlists);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | ArrayDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | AttributedDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | LPAREN UnaryIdentifierDeclarator RPAREN PostfixingAbstractDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
        ;

FunctionDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator PostfixingFunctionDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> parameters = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(parameters, DesugarOps.createCompoundDeclarator);
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
          ParameterTypeListValue parametertypelist
            = (ParameterTypeListValue) getTransformationValue(subparser,3);
          List<Multiverse<Declaration>> parameterdeclaratorlistsmv = parametertypelist.list;
          boolean varargs = parametertypelist.varargs;
          // use Multiverse<List<Parameter>> for ParameterTypeListOpt
          
          // find each combination of single-configuration parameter
          // lists.  not using a product, because it is combining two
          // different types, typespecifier and declarator.  perhaps
          // having a typespecifierdeclarator would make this possible.
          Multiverse<List<Declaration>> parametersmv
            = new Multiverse<List<Declaration>>(new LinkedList<Declaration>(), subparser.getPresenceCondition());
          for (Multiverse<Declaration> nextparameter : parameterdeclaratorlistsmv) {
            // take the product of that multiverse with the existing, hoisted list of parameters
            // (1) wrap each element of the multiverse in a list 
            Multiverse<List<Declaration>> nextparameterwrapped
              = DesugarOps.declarationListWrap.transform(nextparameter);
            // (2) take the product of the existing parameter list
            // with the new, single-element parameter list, allowing
            // for missing parameters in some configurations
            // complementedProduct
            Multiverse<List<Declaration>> newparametersmv
              = parametersmv.complementedProduct(nextparameterwrapped, DesugarOps.DECLARATIONLISTCONCAT);
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
          Multiverse<ParameterListDeclarator> paramlistmv;
          if (varargs) {
            paramlistmv = DesugarOps.toVarArgsParameterList.transform(parametersmv);
          } else {
            paramlistmv = DesugarOps.toParameterList.transform(parametersmv);
          }
          parametersmv.destruct();
          // no need to filter, since we started parametersmv with the subparser pc
          setTransformationValue(value, paramlistmv);
        }
        ;

ArrayDeclarator:  /** nomerge **/
        ParenIdentifierDeclarator ArrayAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> arrayabstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(arrayabstractdeclarators, DesugarOps.createCompoundDeclarator);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        | LPAREN ParenIdentifierDeclarator RPAREN
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
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
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | LPAREN OldFunctionDeclarator RPAREN
        {
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | LPAREN OldFunctionDeclarator RPAREN PostfixingAbstractDeclarator
        {
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

AbstractDeclarator: /** nomerge **/
        UnaryAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | PostfixAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        | PostfixingAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

PostfixingAbstractDeclarator: /**  nomerge **/
        ArrayAbstractDeclarator
      	{
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
        /* | LPAREN { EnterScope(subparser); } ParameterTypeListOpt { ExitReentrantScope(subparser); } RPAREN */
        | PostfixingFunctionDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
        ;

ParameterTypeListOpt: /** nomerge **/  // ParameterTypeListValue which contains List<Multiverse<Declaration>>
        /* empty */
        {
          setTransformationValue(value, new ParameterTypeListValue(new LinkedList<Multiverse<Declaration>>(), false));
        }
        | ParameterTypeList
        {
          setTransformationValue(value, (ParameterTypeListValue) getTransformationValue(subparser,1));
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
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          Multiverse<String> arrayBounds = exprval.transformation;
          Multiverse<Declarator> valuemv = DesugarOps.toAbstractArrayDeclarator.transform(arrayBounds);
          // this is getting an empty mv on filtered for /usr/include/x86_64-linux-gnu/bits/types.h in typesizes.h
          for (Element<Declarator> e : valuemv) {
            ArrayAbstractDeclarator a = ((ArrayAbstractDeclarator)e.getData());
            for (Element<Type> et : exprval.type) {
              if (e.getCondition().is(et.getCondition().and(e.getCondition()))) {
                a.setTypeError(et.getData() == ErrorT.TYPE || (!et.getData().hasConstant() &&
                                                               !et.getData().hasAttribute(Constants.ATT_CONSTANT)));
              }
            }
          }
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          setTransformationValue(value, filtered);
	      }
        | ArrayAbstractDeclarator LBRACK ConstantExpression RBRACK
	      {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          todoReminder("check expression in ArrayAbstractDeclarator (2)");
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());

      	  Multiverse<Declarator> arrayabstractdeclarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<String> arrayBounds = exprval.transformation;

          // get each combination of the existing array abstract declarators and the new constant expressions
          // TODO: is there a way to do this with product?  harder because not combining the same types
          // TODO: replace using a Joiner
          Multiverse<Declarator> valuemv = new Multiverse<Declarator>();
          for (Element<Declarator> declarator : arrayabstractdeclarator) {
            PresenceCondition declaratorCond = subparser.getPresenceCondition().and(declarator.getCondition());
            for (Element<String> expression : arrayBounds) {
              Type t = null;
              for (Element<Type> et : exprval.type) {
                if (et.getCondition().is(expression.getCondition())) {
                  t = et.getData();
                  break;
                }
              }
              PresenceCondition combinedCondition = declaratorCond.and(expression.getCondition());
              ArrayAbstractDeclarator a = new ArrayAbstractDeclarator((ArrayAbstractDeclarator) declarator.getData(),
                                                                      expression.getData());
              if (!t.hasConstant() && !t.hasAttribute(Constants.ATT_CONSTANT)) {
                a.setTypeError(true);
              }
              valuemv.add(a, combinedCondition);
              
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
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toQualifiedPointerAbstractDeclarator.transform(qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
        | STAR TypeQualifierList AbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.createQualifiedPointerDeclarator(declarators, qualifierlists);
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
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        } 
        | LPAREN PostfixAbstractDeclarator RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        } 
        | LPAREN PostfixingAbstractDeclarator RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        } 
        | LPAREN UnaryAbstractDeclarator RPAREN PostfixingAbstractDeclarator
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> abstractdeclarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = declarators.product(abstractdeclarators, DesugarOps.createCompoundDeclarator);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          /* abstractdeclarators.destruct(); */
          setTransformationValue(value, filtered);
        } 
        ;

// ---------------------------------------------------------------- Statements


// These just hoist any static conditionals by turning them into multiverses, combining the node's semantic values
/*
use this to get one pc for all errors in the types
PresenceCondition errorCond = typemv.getPresenceCondition(ErrorT.TYPE);
 */
Statement:  /** complete **/  // Multiverse<DeclarationOrStringValue>
        LabeledStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        /* | SwitchLabeledStatement */
        /* { */
        /*   setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())); */
        /* } */
        | CompoundStatement
        {
          // CompoundStatement produces just a string (not a multiverse), since it's children resolve all
          // configurations, so we only need to resolve static conditionals around the CompoundStatement.
          setTransformationValue(value, getCompleteNodeSingleValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        /* | LBRACE { EnterScope(subparser); } CompoundStatement { ExitScope(subparser); } RBRACE */
        /* { */
        /*   PresenceCondition pc = subparser.getPresenceCondition(); */
        /*   // CompoundStatement produces just a string (not a multiverse), since it's children resolve all */
        /*   // configurations, so we only need to resolve static conditionals around the CompoundStatement. */
        /*   Multiverse<String> lbrace = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc); */
        /*   Multiverse<String> cmpdmv = getCompleteNodeSingleValue(getNodeAt(subparser, 3), pc); */
        /*   Multiverse<String> rbrace = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc); */

        /*   setTransformationValue(value, productAll(DesugarOps.concatStrings, */
        /*                                            lbrace, */
        /*                                            cmpdmv, */
        /*                                            rbrace)); */
        /*   lbrace.destruct(); cmpdmv.destruct(); rbrace.destruct(); */
        /* } */
        | ExpressionStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | SelectionStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | IterationStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | JumpStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        | AssemblyStatement  // ADDED
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
        ;

LabeledStatement:  /** complete **/  // ADDED attributes  // Multiverse<String>
IDENTIFIER COLON AttributeSpecifierListOpt Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Syntax id = (getSyntaxMV(subparser, 4,pc)).get(0).getData();
          String ident = id.getTokenText();
          
          // TODO: save attributes
          Multiverse<DeclarationOrStatementValue>  stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue();
          dsv.setLabel(ident);
          dsv.setChildrenBlock("",stmtmv,"");
          Multiverse<DeclarationOrStatementValue> dsvm = new Multiverse<DeclarationOrStatementValue>(dsv,pc);
                    
          setTransformationValue(value, dsvm);
        }
        | TYPEDEFname COLON AttributeSpecifierListOpt Statement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          String ident = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          // TODO: save attributes
          Multiverse<DeclarationOrStatementValue>  stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue();
          dsv.setLabel(ident);
          dsv.setChildrenBlock("",stmtmv,"");
          Multiverse<DeclarationOrStatementValue> dsvm = new Multiverse<DeclarationOrStatementValue>(dsv,pc);

          setTransformationValue(value, dsvm);
        }

        ;

// convert statements to if statements
SwitchLabeledStatement:  /** complete **/  // Multiverse<String>
        CASE ConstantExpression COLON CompoundStatementBody
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          String casestr = "case";  // hacky fix for unexpected conditionals around the case keyword
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, subparser.getPresenceCondition());
          String colonstr = ":";  // hacky fix for unexpected conditionals around the colon
          /* Multiverse<String> stmt = getCompleteNodeMultiverseValue(subparser, 1, pc); */

          /* String stmtstr = emitStatement(stmt, pc); stmt.destruct(); */
          List<Multiverse<DeclarationOrStatementValue>> body = (List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 1);
          Multiverse<String> appended = exprval.transformation.appendScalar(colonstr, DesugarOps.concatStrings);
          Multiverse<String> valuemv = appended.prependScalar(casestr, DesugarOps.concatStrings);
          appended.destruct();
          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(valuemv);
          for (Element<DeclarationOrStatementValue> e : dsv) {
            e.getData().setChildrenBlock("",body,"");
            e.getData().setType(exprval.type.filter(e.getCondition()));
          }
          setTransformationValue(value, dsv);
        }
        | CASE ConstantExpression ELLIPSIS ConstantExpression COLON CompoundStatementBody  // ADDED case range
        {
          todoReminder("check that case expression is int");
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: SwitchLabeledStatement (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | DEFAULT COLON CompoundStatementBody
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          String defaultstr = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          String colonstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          /* Multiverse<String> stmt = getCompleteNodeMultiverseValue(subparser, 1, pc); */
          DeclarationOrStatementValue d = new DeclarationOrStatementValue(defaultstr + colonstr);
          d.setChildrenBlock("",(List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 1),"");
          d.setType(null);
          Multiverse<DeclarationOrStatementValue> dsv = new Multiverse<DeclarationOrStatementValue>();
          dsv.add(d, pc);          
          setTransformationValue(value, dsv);
        
        }
        ;

SwitchLabeledStatementList:  /** list, nomerge **/  // Multiverse<List<String>>
        SwitchLabeledStatement
        {
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, subparser.getPresenceCondition());
          List<Multiverse<DeclarationOrStatementValue>> l = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          l.add(stmtmv);
          setTransformationValue(value, l);
        }
        | SwitchLabeledStatementList SwitchLabeledStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<DeclarationOrStatementValue>> list = getCompleteNodeDeclStmtValueList(subparser, 2, pc);
          Multiverse<DeclarationOrStatementValue> elem = getCompleteNodeMultiverseValue(subparser, 1, pc);
          list.add(elem);
          setTransformationValue(value, list);
          pc.delRef();
        }
        ;

/*CompoundStatement:
        LBRACE RBRACE
        | LBRACE DeclarationList RBRACE
        | LBRACE StatementList RBRACE
        | LBRACE DeclarationList StatementList RBRACE
        ;*/

CompoundStatement:  /** complete **/  /* ADDED */  // String
        LBRACE { ReenterScope(subparser); } CompoundStatementBody {   ExitScope(subparser); } RBRACE
        {
          LineNumbers lBraceLN = new LineNumbers((Syntax)getNodeAt(subparser,5));
          LineNumbers rBraceLN = new LineNumbers((Syntax)getNodeAt(subparser,1));
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);
          
          List<Multiverse<DeclarationOrStatementValue>> body = (List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 3);
          StringBuilder valuesb = new StringBuilder();
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue("");
          dsv.setChildrenBlock("{"+lBraceLN.getComment(),body,"}"+rBraceLN.getComment());

          setTransformationValue(value, dsv);
        }
        ;

CompoundStatementBody:  /** nomerge **/  /* ADDED */  // String
        LocalLabelDeclarationListOpt DeclarationOrStatementList
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);

          Multiverse<String> locallabelmv = getCompleteNodeSingleValue(subparser, 2, pc);
          List<Multiverse<DeclarationOrStatementValue>> listmv = getCompleteNodeDeclStmtValueList(subparser, 1, pc);
          List<Multiverse<DeclarationOrStatementValue>> retmv = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          retmv.add(DesugarOps.StringToDSV.transform(locallabelmv));
          retmv.add(new Multiverse<DeclarationOrStatementValue>(new DeclarationOrStatementValue(scope.getDeclarations(pc)),pc));
          retmv.addAll(listmv);
	  setTransformationValue(value, retmv);
        }
        ;

/* CompoundStatement:  /\** complete **\/  /\* ADDED *\/  // String */
/*         LocalLabelDeclarationListOpt DeclarationOrStatementList */
/*         { */
/*           PresenceCondition pc = subparser.getPresenceCondition(); */
/*           CContext scope = ((CContext) subparser.scope); */

/*           Multiverse<String> locallabelmv = getCompleteNodeSingleValue(subparser, 2, pc); */
/*           Multiverse<String> declorstmtmv = getCompleteNodeSingleValue(subparser, 1, pc); */
          
/*           StringBuilder valuesb = new StringBuilder(); */
/*           valuesb.append(concatMultiverseStrings(locallabelmv)); locallabelmv.destruct(); */
/*           // print user-defined type declarations at top of scope */
/*           valuesb.append(scope.getDeclarations(subparser.getPresenceCondition())); */
/*           // DeclarationOrStatementList already resolves */
/*           // configurations, so just print all the possible strings */
/*           // under the static conditional */
/*           valuesb.append(concatMultiverseStrings(declorstmtmv)); declorstmtmv.destruct(); */

/*           setTransformationValue(value, valuesb.toString()); */
/*         } */
/*         ; */

LocalLabelDeclarationListOpt: /** complete **/ // String
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

LocalLabelDeclarationList:  /** list, complete **/ // String
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
          System.err.println("ERROR: unsupported semantic action: LocalLabelDeclaration");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

LocalLabelList:  /** list, complete **/  // ADDED
        IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: LocalLabelList");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        | LocalLabelList COMMA IDENTIFIER
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: LocalLabelList");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

DeclarationOrStatementList:  /** list, complete **/  /* ADDED */  // List<Multiverse<DeclarationOrStatementValue>>
        /* empty */
        {
          List<Multiverse<DeclarationOrStatementValue>> n = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          setTransformationValue(value, n);
        }
        | DeclarationOrStatementList DeclarationOrStatement
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<DeclarationOrStatementValue>> list = getCompleteNodeDeclStmtValueList(subparser, 2, pc);
          List<Multiverse<DeclarationOrStatementValue>>  ds = getCompleteNodeDeclStmtValueList(subparser, 1, pc);
          list.addAll(ds);
          setTransformationValue(value, list);
        }
        ;

DeclarationOrStatement: /** complete **/  /* ADDED */  // List<Multiverse<DeclarationOrStatementValue>>
        DeclarationExtension
        {
          // declarations are already just strings, so get the multiverse of any static conditionals around them
          List<Multiverse<String>> ss = getCompleteNodeListValue(getNodeAt(subparser, 1),subparser.getPresenceCondition());
          List<Multiverse<DeclarationOrStatementValue>> ds = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          for (Multiverse<String> ms : ss) {
            Multiverse<DeclarationOrStatementValue> decl = DesugarOps.StringToDSV.transform(ms);
            for (Element<DeclarationOrStatementValue> e : decl) {
              e.getData().setDecl();
            }
            ds.add(decl);
          }
          setTransformationValue(value, ds);
        }
        | Statement
        {
          // statements have multiverses, so hoist any static conditionals around them by combining with the statement multiverses
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<DeclarationOrStatementValue> m = getCompleteNodeMultiverseValue(subparser,1,pc);
          List<Multiverse<DeclarationOrStatementValue>> l = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          l.add(m);
          setTransformationValue(value, l);
        }
        | NestedFunctionDefinition
        {
          System.err.println("nestedfunctiondefinition not implemented yet");
          System.exit(1);
        }
        ;

DeclarationList:  /** list, complete **/  // String
        DeclarationExtension
        {
          Multiverse<String> valuemv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(valuemv)); valuemv.destruct();
        }
        | DeclarationList DeclarationExtension
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          StringBuilder valuesb = new StringBuilder();
          Multiverse<String> listmv = getCompleteNodeSingleValue(subparser, 2, pc);
          Multiverse<String> declmv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          valuesb.append(concatMultiverseStrings(listmv)); listmv.destruct();
          valuesb.append(concatMultiverseStrings(declmv)); declmv.destruct();
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
          
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          Multiverse<Type> exprtype = exprval.type;
          PresenceCondition errorCond = exprtype.getConditionOf(ErrorT.TYPE);
          Multiverse<String> valuemv;

          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          Multiverse<LineNumbers> lns = exprval.integrateSyntax((Syntax) getNodeAt(subparser, 1));
          Multiverse<String> comments = DesugarOps.LineNumbersToString.transform(lns);
          
          
          if (! exprval.isAlwaysError()) {
            Multiverse<String> expr = exprval.transformation;
          
            // if filtering of type errors is done right, this add 
           // should not violate mutual-exclusion in the multiverse
            // TODO: use dce and other optimizations to remove superfluous __static_type_error calls
            // since desugarOps can't have empty multiverses we need to add error entries
           // so here we should purge the errorCond from the string multiverse before appending
            todoReminder("add emitError back to ExpressionStatement once type checking is done");
            if (errorCond.isNotFalse()) {
              expr = expr.filter(errorCond.not());
              expr.add(emitError("type error"), errorCond);
            }
            valuemv = expr.appendScalar(semi, DesugarOps.concatStrings);
            
          } else {
            System.err.println("type error: ExpressionStatement found no valid expressions");
            valuemv = new Multiverse<String>(String.format("%s;", emitError("type error : no valid expression")), errorCond);
          }
          assert valuemv != null;
          /* System.err.println("EXPSMT: " + valuemv); */
          
          errorCond.delRef();
          valuemv = valuemv.product(comments, DesugarOps.concatStrings);
          Multiverse<DeclarationOrStatementValue> mds = DesugarOps.StringToDSV.transform(valuemv);
          for (Element<DeclarationOrStatementValue> e : mds) {
            Multiverse<Type> mt = exprtype.filter(e.getCondition());
            e.getData().setType(mt);
          }
          setTransformationValue(value, mds);
        }
        ;

// TODO: destruct the multiverses after product
// TODO: use emitExpression and emitStatement to avoid doing any product at all
SelectionStatement:  /** complete **/ // Multiverse<String>
        IF LPAREN Expression RPAREN Statement
        {
          todoReminder("check the type of the conditional expression SelectionStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);
          Syntax ifsyn = (getSyntaxMV(subparser, 5,pc)).get(0).getData();
          String ifstr = ifsyn.getTokenText();
          String lparenstr = (getSyntaxMV(subparser, 4,pc)).get(0).getData().getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          Syntax rparensyn = (getSyntaxMV(subparser, 2,pc)).get(0).getData();
          String rparenstr = rparensyn.getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          LineNumbers lw = new LineNumbers(ifsyn,rparensyn);
          String errorstmt = String.format("%s;", emitError("invalid type found in if statement"));
          if (exprval.hasValidType(pc)) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", ifstr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr + lw.getComment(), DesugarOps.concatStrings); prependmv.destruct();

            Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appendmv);

            for (Element<DeclarationOrStatementValue> d : dsv) {
              d.getData().setChildrenBlock("",stmtmv,"");
            }
            
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            dsv.add(new DeclarationOrStatementValue(errorstmt), invalidCond);
            setTransformationValue(value, dsv);
          } else {
            setTransformationValue(value, DesugarOps.StringToDSV.transform(new Multiverse<String>(errorstmt, pc)));
          }
        }
        | IF LPAREN Expression RPAREN Statement ELSE Statement
        {
          todoReminder("check the type of the conditional expression SelectionStatement (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 5, pc);
          Multiverse<Syntax> ifsynm = getSyntaxMV(subparser,7,pc);
          Syntax ifsyn = ifsynm.get(0).getData();
          String ifstr = ifsyn.getTokenText();
          String lparenstr = "(";
          Multiverse<String> exprmv = exprval.transformation;
          Syntax rparensyn = (getSyntaxMV(subparser, 4,pc)).get(0).getData();
          String rparenstr = rparensyn.getTokenText();
          LineNumbers lw = new LineNumbers(ifsyn, rparensyn);
          Multiverse<DeclarationOrStatementValue> ifbranchmv = getCompleteNodeMultiverseValue(subparser, 3, pc);
          String elsestr = (getSyntaxMV(subparser, 2,pc)).get(0).getData().getTokenText();
          LineNumbers elw = new LineNumbers((getSyntaxMV(subparser, 2,pc)).get(0).getData());
          elsestr += elw.getComment();
          Multiverse<DeclarationOrStatementValue> elsebranchmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

          String errorstmt = String.format("%s;", emitError("invalid type found in ifelse statement"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", ifstr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr + lw.getComment(), DesugarOps.concatStrings); prependmv.destruct();

            Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appendmv);

            for (Element<DeclarationOrStatementValue> d : dsv) {
              d.getData().setChildrenElse(ifbranchmv,elsestr,elsebranchmv);
            }
                        
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            dsv.add(new DeclarationOrStatementValue(errorstmt), invalidCond);
            setTransformationValue(value, dsv);
          } else {
            setTransformationValue(value, DesugarOps.StringToDSV.transform(new Multiverse<String>(errorstmt, pc)));
          }
        }
        | SWITCH LPAREN Expression RPAREN LBRACE SwitchLabeledStatementList RBRACE
        {
          // n1570 6.8.4.2 for switch statements
	  PresenceCondition pc = subparser.getPresenceCondition();
          // n1570 labeled statement, 6.8.1, case and default are only to be used under switch statements
          Syntax switchsyn = (getSyntaxMV(subparser, 7,pc)).get(0).getData();
          String switchstr = switchsyn.getTokenText();
          String lparen = ((Syntax) (getSyntaxMV(subparser, 6,pc)).get(0).getData()).getTokenText();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 5, subparser.getPresenceCondition());
          Syntax rparensyn = (getSyntaxMV(subparser, 4,pc)).get(0).getData();
          String rparen = (rparensyn).getTokenText();
          String lbrace = (getSyntaxMV(subparser, 3,pc)).get(0).getData().getTokenText();
          LineNumbers lw = new LineNumbers(switchsyn, rparensyn);
          List<Multiverse<DeclarationOrStatementValue>> body = (List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 2);
          Multiverse<List<DeclarationOrStatementValue>> bodyswap = listMultiverseSwap(body,subparser.getPresenceCondition());
          for (Element<List<DeclarationOrStatementValue>> el : bodyswap) {
            for (DeclarationOrStatementValue ds : el.getData()) {
              ds.filterTypes(el.getCondition());
            }
          }
          String rbrace = (getSyntaxMV(subparser, 1,pc)).get(0).getData().getTokenText();

          todoReminder("check that switch statement expression should be an int");

          String prefix = String.format("%s %s", switchstr, lparen);
          Multiverse<String> prepended = exprval.transformation.prependScalar(prefix, DesugarOps.concatStrings);
          String suffix = String.format("%s%s", rparen, lw.getComment() );
          Multiverse<String> appended = prepended.appendScalar(suffix, DesugarOps.concatStrings);
          prepended.destruct();
          Multiverse<String> errorless = appended.filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
          appended.destruct();
          if (errorless.isEmpty()) {
            errorless.add("error",exprval.type.getConditionOf(ErrorT.TYPE));
          }
          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(errorless).filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
          errorless.destruct();
          Multiverse<DeclarationOrStatementValue> newdsv = new Multiverse<DeclarationOrStatementValue>();
          if (!dsv.isEmpty() && !bodyswap.isEmpty()) {
            for (Element<DeclarationOrStatementValue> e : dsv) {
              for (Element<List<DeclarationOrStatementValue>> b : bodyswap) {
                if (!e.getCondition().isMutuallyExclusive(b.getCondition())) {
                  DeclarationOrStatementValue d = new DeclarationOrStatementValue(e.getData());
                  d.setSwitchChildrenBlock("{",b.getData(),"}");
                  newdsv.add(d,e.getCondition().and(b.getCondition()));
                }
              }
            }
          }
          newdsv.add(new DeclarationOrStatementValue(emitError("invalid switch expression") + ";"), exprval.type.getConditionOf(ErrorT.TYPE));
          PresenceCondition badCases = (new PresenceConditionManager()).newFalse();
          for (Element<List<DeclarationOrStatementValue>> el : bodyswap ) {
            PresenceCondition cc = el.getCondition();
            for(DeclarationOrStatementValue ds : el.getData()) {
              if (!ds.goodSwitchCase(cc)) {
                badCases = badCases.or(cc);
                break;
              }
            }
            cc.delRef();
          }
          for (Element<DeclarationOrStatementValue> eds : newdsv) {
            if (eds.getData().hasRepeatChildName()) {
              badCases = badCases.or(eds.getCondition());
            }
          }
          if (badCases.isNotFalse()) {
            newdsv = newdsv.filter(badCases.not());
            newdsv.add(new DeclarationOrStatementValue(emitError("Switch cases are incompatible") + ";"), badCases);
          }
          badCases.delRef();
          setTransformationValue(value, newdsv);
        }
        ;
// TODO: destruct the multiverses after product
IterationStatement:  /** complete **/  // Multiverse<String>
        WHILE LPAREN Expression RPAREN Statement
        {
          todoReminder("check the type of the conditional expression IterationStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);

          Syntax whilesyn = (getSyntaxMV(subparser, 5,pc)).get(0).getData();
          String whilestr = whilesyn.getTokenText();
          String lparenstr = (getSyntaxMV(subparser, 4,pc)).get(0).getData().getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          Syntax rparensyn = (getSyntaxMV(subparser, 2,pc)).get(0).getData();
          String rparenstr = (rparensyn).getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          LineNumbers lw = new LineNumbers(whilesyn, rparensyn);
          String errorstmt = String.format("%s;", emitError("invalid type found in while statement"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", whilestr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr + lw.getComment(), DesugarOps.concatStrings); prependmv.destruct();

            Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appendmv);

            for (Element<DeclarationOrStatementValue> d : dsv) {
              d.getData().setChildrenBlock("",stmtmv,"");
            }
            
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            dsv.add(new DeclarationOrStatementValue(errorstmt), invalidCond);
            setTransformationValue(value, dsv);
          } else {
            setTransformationValue(value, DesugarOps.StringToDSV.transform(new Multiverse<String>(errorstmt, pc)));
          }
        }
        | DO Statement WHILE LPAREN Expression RPAREN SEMICOLON
        {
          todoReminder("check the type of the conditional expression IterationStatement (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);

          String dostr = (String)((Syntax) getNodeAt(subparser, 7)).getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 6, pc);
          Syntax whilesyn = (Syntax) getNodeAt(subparser, 5);
          String whilestr =  whilesyn.getTokenText();
          String lparenstr = (String)((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String rparenstr = (String)((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Syntax semisyn = (Syntax) getNodeAt(subparser, 1);
          String semistr =   semisyn.getTokenText();
          LineNumbers lw = new LineNumbers(whilesyn, semisyn);
          Multiverse<String> prependmv
              = exprmv.prependScalar(whilestr + lparenstr, DesugarOps.concatStrings); exprmv.destruct();
          Multiverse<String> appendmv
            = prependmv.appendScalar(rparenstr + semistr + lw.getComment(), DesugarOps.concatStrings); prependmv.destruct();

          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appendmv);
          
          for (Element<DeclarationOrStatementValue> d : dsv) {
            d.getData().setChildrenBlock(dostr,stmtmv,"");
            d.getData().setDo();
          }
          String errorstmt = String.format("%s;", emitError("invalid type found in do-while statement"));
          PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
          dsv = dsv.filter(invalidCond.not());
          dsv.add(new DeclarationOrStatementValue(errorstmt), invalidCond);
          setTransformationValue(value, dsv);
        }
        | FOR LPAREN ExpressionOpt SEMICOLON ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement
        {
          todoReminder("check the type of the conditional expression IterationStatement (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<Syntax> forsynm = getSyntaxMV(subparser,9,pc);
          Syntax forsyn = forsynm.get(0).getData();
          String forkeyword = forsyn.getTokenText();
          String lparen = "(";
          ExpressionValue initval = getCompleteNodeExpressionValue(subparser, 7, pc);
          String semi1 = ";";
          ExpressionValue testval = getCompleteNodeExpressionValue(subparser, 5, pc);
          String semi2 = ";";
          ExpressionValue updateval = getCompleteNodeExpressionValue(subparser, 3, pc);
          Syntax rparensyn = (getSyntaxMV(subparser, 2,pc)).get(0).getData(); 
          String rparen = rparensyn.getTokenText();
          LineNumbers lw = new LineNumbers(forsyn,rparensyn);

          if (initval.hasValidType() && testval.hasValidType() && updateval.hasValidType()) {
            PresenceCondition cond1 = initval.validTypeCondition(pc);
            PresenceCondition cond2 = cond1.and(testval.validTypeCondition(pc)); cond1.delRef();
            PresenceCondition validcond = cond2.and(updateval.validTypeCondition(pc)); cond2.delRef();

            if (validcond.isNotFalse()) {
              Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

              Multiverse<String> initmv = initval.transformation;
              Multiverse<String> testmv = testval.transformation;
              Multiverse<String> updatemv = updateval.transformation;

          
              String forlparen = String.format("for (");

              Multiverse<String> mv1 = initmv.prependScalar(forlparen, DesugarOps.concatStrings);
              Multiverse<String> mv2 = mv1.appendScalar(semi1, DesugarOps.concatStrings); mv1.destruct();
              Multiverse<String> mv3 = mv2.product(testmv, DesugarOps.concatStrings); mv2.destruct();
              Multiverse<String> mv4 = mv3.appendScalar(semi2, DesugarOps.concatStrings); mv3.destruct();
              Multiverse<String> mv5 = mv4.product(updatemv, DesugarOps.concatStrings); mv4.destruct();
              Multiverse<String> valuemv = mv5.appendScalar(rparen + lw.getComment(), DesugarOps.concatStrings); mv5.destruct();
              
              valuemv = valuemv.filter(initval.type.getConditionOf(ErrorT.TYPE).not()).
                filter(testval.type.getConditionOf(ErrorT.TYPE).not()).filter(updateval.type.getConditionOf(ErrorT.TYPE).not());

              Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(valuemv);
          
              for (Element<DeclarationOrStatementValue> d : dsv) {
                d.getData().setChildrenBlock("",stmtmv,"");
              }

              dsv = dsv.filter(initval.type.getConditionOf(ErrorT.TYPE).not());
              dsv.add(new DeclarationOrStatementValue(emitError("initialization type error in this presence condition") + ";"),initval.type.getConditionOf(ErrorT.TYPE));

              dsv = dsv.filter(testval.type.getConditionOf(ErrorT.TYPE).not());
              dsv.add(new DeclarationOrStatementValue(emitError("test condition type error in this presence condition") + ";"),testval.type.getConditionOf(ErrorT.TYPE));
              
              dsv = dsv.filter(updateval.type.getConditionOf(ErrorT.TYPE).not());
              dsv.add(new DeclarationOrStatementValue(emitError("update value type error in this presence condition") + ";"),updateval.type.getConditionOf(ErrorT.TYPE));
              
              setTransformationValue(value, dsv);
            } else {
              setTransformationValue(value, new Multiverse<DeclarationOrStatementValue>(new DeclarationOrStatementValue (emitError("no valid type in iterationstatement (3)") + ";"), pc));
            }
          } else {
            setTransformationValue(value, new Multiverse<DeclarationOrStatementValue>(new DeclarationOrStatementValue (emitError("no valid type in iterationstatement (3)") + ";"), pc));
          }
        }
        // n1570 6.8.5 Iteration statements allows for a declaration in the initializer of a for loop
        | FOR LPAREN { EnterScope(subparser); } Declaration ExpressionOpt SEMICOLON
                ExpressionOpt RPAREN Statement { ExitScope(subparser); }
        {
          // TODO: use a reentrant scope to add the declaration's symbol to the for-loop's scope
          // TODO: Declaration returns a String, not a multiverse.  We need a multiverse to hoist around the entire for loop.
          // TODO: consider rewriting this to put the declaration outside the for loop.  since it's renamed, we should have conflicts, and it resolves issues with scope and semantic values
          todoReminder("check the type of the conditional expression IterationStatement (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 10), (Syntax) getNodeAt(subparser, 3));
          Multiverse<String> formv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 10)).getTokenText(), pc);
          Multiverse<String> lparen = new Multiverse<String>(((Syntax) getNodeAt(subparser, 9)).getTokenText(), pc);
          List<Multiverse<String>> declstring = getCompleteNodeListValue(getNodeAt(subparser, 7),subparser.getPresenceCondition());
          ExpressionValue testval = getCompleteNodeExpressionValue(subparser, 6, pc);
          Multiverse<String> testmv = testval.transformation;
          Multiverse<String> semi2mv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc);
          ExpressionValue updateval = getCompleteNodeExpressionValue(subparser, 4, pc);
          Multiverse<String> updatemv = updateval.transformation;
          Multiverse<String> rparen = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc);
          Multiverse<String> comment = new Multiverse<String>(lw.getComment(),pc);
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 2, pc);

          // rewrite by moving the declaration above the for-loop.
          // add the new declarations and the for loop to their own
          // compound statements to avoid scoping issues and ensure
          // each is a single statement.  this is a little hack to get
          // around the fact that a declaration is not a multiverse,
          // but is already just a string because of renaming.
          Multiverse<String> lbrace = new Multiverse<String>("{", pc);
          Multiverse<String> rbrace = new Multiverse<String>("}", pc);
          Multiverse<String> semi1mv = new Multiverse<String>(";", pc);  // add an empty initializer expression
          Multiverse<String> valuemv = productAll(DesugarOps.concatStrings,
                                                lbrace,
                                                  declstring.get(0),
                                                formv,
                                                lparen,
                                                semi1mv,
                                                testmv,
                                                semi2mv,
                                                updatemv,
                                                  rparen,
                                                  comment);
          valuemv = valuemv.filter(testval.type.getConditionOf(ErrorT.TYPE).not()).filter(updateval.type.getConditionOf(ErrorT.TYPE).not());

          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(valuemv);
          
          for (Element<DeclarationOrStatementValue> d : dsv) {
            d.getData().setChildrenBlock("",stmtmv,"}");
          }
          
          dsv.add(new DeclarationOrStatementValue(emitError("test condition type error in this presence condition") + ";"),testval.type.getConditionOf(ErrorT.TYPE));
          
          dsv.add(new DeclarationOrStatementValue(emitError("update value type error in this presence condition") + ";"),updateval.type.getConditionOf(ErrorT.TYPE));
          
          setTransformationValue(value, dsv);
        }
        ;

JumpStatement:  /** complete **/ // Multiverse<String>
        GotoStatement
        {
          setTransformationValue(value, getCompleteNodeMultiverseValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | ContinueStatement
        {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
        | BreakStatement
        {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
        | ReturnStatement
        {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
        ;

GotoStatement:  /** complete **/ // Multiverse<DeclarationOrStatementValue>
        GOTO IdentifierOrTypedefName SEMICOLON
        {
          String ident = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();

          DeclarationOrStatementValue d = new DeclarationOrStatementValue();
          d.setGotoLabel(ident);
          
          setTransformationValue(value, new Multiverse<DeclarationOrStatementValue>(d,subparser.getPresenceCondition()));
        }
        | GOTO STAR Expression SEMICOLON  // ADDED
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: GotoStatement (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

ContinueStatement:  /** complete **/ // Multiverse<String>
        CONTINUE SEMICOLON
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 2),(Syntax) getNodeAt(subparser, 1));
          String continuetoken = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          setTransformationValue(value, new Multiverse<String>(String.format("%s %s %s", continuetoken, semi, lw.getComment()),
                                                               subparser.getPresenceCondition()));
        }
        ;

BreakStatement:  /** complete **/ // Multiverse<String>
        BREAK SEMICOLON
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 2),(Syntax) getNodeAt(subparser, 1));
          String breaktoken = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          setTransformationValue(value, new Multiverse<String>(String.format("%s %s %s", breaktoken, semi, lw.getComment()),
                                                               subparser.getPresenceCondition()));
        }
        ;

ReturnStatement:  /** complete **/ // Multiverse<String>
        RETURN ExpressionOpt SEMICOLON
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 3),(Syntax) getNodeAt(subparser, 1));
          todoReminder("check the type of the return value");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          String returnkeyword = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          String errorstmt
            = String.format("%s;", emitError("invalid type found in return expression"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            Multiverse<String> prependmv
              = validmv.prependScalar(returnkeyword, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> valuemv
              = prependmv.appendScalar(semi + lw.getComment(), DesugarOps.concatStrings); prependmv.destruct();
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            valuemv.add(errorstmt, invalidCond);
            setTransformationValue(value, valuemv);
          } else {
            setTransformationValue(value, new Multiverse<String>(errorstmt, pc));
          }  
        }
        ;

// --------------------------------------------------------------- Expressions

/* CONSTANTS */
Constant: /** nomerge **/  // ExpressionValue
        FLOATINGconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new FloatT(NumberT.Kind.FLOAT).attribute(Constants.ATT_CONSTANT), new Multiverse<LineNumbers>(new LineNumbers((Syntax) getNodeAt(subparser, 1)),subparser.getPresenceCondition()), subparser.getPresenceCondition()));
        }
        | INTEGERconstant
        {
          /* value = GNode.create("Constant", getNodeAt(subparser, 1)); */
          /* System.err.println(value); */
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT),new Multiverse<LineNumbers>(new LineNumbers((Syntax) getNodeAt(subparser, 1)), subparser.getPresenceCondition()), subparser.getPresenceCondition()));

          /* System.err.println("Constant: " + value.hashCode()); */
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
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT),new Multiverse<LineNumbers>(new LineNumbers((Syntax) getNodeAt(subparser, 1)), subparser.getPresenceCondition()), subparser.getPresenceCondition()));
        }
        | HEXconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT),new Multiverse<LineNumbers>(new LineNumbers((Syntax) getNodeAt(subparser, 1)), subparser.getPresenceCondition()), subparser.getPresenceCondition()));
        }
        | CHARACTERconstant
        {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.SHORT).attribute(Constants.ATT_CONSTANT),new Multiverse<LineNumbers>(new LineNumbers((Syntax) getNodeAt(subparser, 1)), subparser.getPresenceCondition()), subparser.getPresenceCondition()));
        }
        ;

/* STRING LITERALS */
// TODO: unit tests
StringLiteralListString:  /** list, nomerge **/ // String
        STRINGliteral
        {
          setTransformationValue(value, new StringListPair(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                           new LineNumbers((Syntax) getNodeAt(subparser, 1))));
        }
        | StringLiteralListString STRINGliteral
        {
          StringListPair s = new StringListPair(((StringListPair)getTransformationValue(subparser, 2)).str +
                                                ((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                new LineNumbers(new LineNumbers((Syntax) getNodeAt(subparser, 1)), ((StringListPair)getTransformationValue(subparser, 2)).lines));
          setTransformationValue(value, s);
        }
        ;

// This nontermal just adds type information to the string literal
StringLiteralList:  /** list, nomerge **/ // ExpressionValue
        StringLiteralListString
        {
          // TODO: CAnalyzer distinguishes between wide and non-wide characters
          // TODO: use a fixed-size array instead of a pointer to char
          setTransformationValue(value,
                                 new ExpressionValue(((StringListPair) getTransformationValue(subparser, 1)).str,
                                                     new PointerT(NumberT.CHAR),
                                                     new Multiverse<LineNumbers>(((StringListPair) getTransformationValue(subparser, 1)).lines, subparser.getPresenceCondition()),
                                                     subparser.getPresenceCondition()));
        }
        ;


/* EXPRESSIONS */
PrimaryExpression:  /** nomerge, passthrough **/ // ExpressionValue
        PrimaryIdentifier
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | Constant
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | StringLiteralList
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | LPAREN Expression RPAREN
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 3),(Syntax) getNodeAt(subparser, 1));
          
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          /* System.err.println("PRIMARY: " + exprval.transformation); */
          /* System.err.println("PRIMARY: " + exprval.type); */

          if (exprval.hasValidType() && !exprval.transformation.isEmpty()) {
            String lparen = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
            Multiverse<String> exprmv = exprval.transformation;
            String rparen = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

            Multiverse<String> prepended = exprmv.prependScalar(lparen, DesugarOps.concatStrings);
            Multiverse<String> appended = prepended.appendScalar(rparen, DesugarOps.concatStrings); prepended.destruct();

            setTransformationValue(value, new ExpressionValue(appended, exprval.type,new Multiverse<LineNumbers>(lw,pc)));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type for the primary expression"),
                                                              ErrorT.TYPE,new Multiverse<LineNumbers>(lw,pc),
                                                              pc));
          }
        }
        | StatementAsExpression  // ADDED
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | VariableArgumentAccess  // ADDED
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        ;

PrimaryIdentifier: /** nomerge **/ // ExpressionValue
        IDENTIFIER
        {
          String originalName = ((Node)getNodeAt(subparser, 1)).getTokenText();
          //Multiverse<String> sbmv = new Multiverse<String>();
          //sbmv.add(new Element<String>(sb, subparser.getPresenceCondition().presenceConditionManager().newTrue()));

          CContext scope = (CContext) subparser.scope;

          // get the renamings from the symtab
          PresenceCondition cond = subparser.getPresenceCondition();
          Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(originalName, cond);
          // convert the renamings to stringbuilders
          Multiverse<String> sbmv = new Multiverse<String>();
          Multiverse<Type> typemv = new Multiverse<Type>();
          // any presence conditions with an error can be omitted from
          // the desugaring.  instead, this information is preserved
          // in the type value for use by the statement.
          for (Element<SymbolTable.Entry<Type>> entry : entries) {
            if (entry.getData().isError()) {
              System.err.println(String.format("type error: use of symbol with invalid declaration: %s", originalName));
              sbmv.add("error",entry.getCondition());
              typemv.add(ErrorT.TYPE, entry.getCondition());
            } else if (entry.getData().isUndeclared()) {
              System.err.println(String.format("type error: use of undeclared symbol: %s", originalName));
              sbmv.add("error",entry.getCondition());
              typemv.add(ErrorT.TYPE, entry.getCondition());
            } else {
              // TODO: add type checking.  may need to tag the resulting
              // stringbuilder with the type to handle this
              
              if (entry.getData().getValue().isVariable()) {
                VariableT vt= (VariableT)entry.getData().getValue();
                if (vt.getType().isUnion() &&
                    ((UnionT)vt.getType()).getName().startsWith("__forward_tag_reference_")) {
                  for (VariableT vtt : ((UnionT)vt.getType()).getMembers()) {
                    String result  // use the renamed symbol
                      = String.format(" %s ",vt.getName());
                    Multiverse<String> m = scope.getEnumMultiverse(vtt.getName(), entry.getCondition());
                    for (Element<String> e : m) {
                      if (e.getData().equals("<error>")) {
                        typemv.add(ErrorT.TYPE,e.getCondition());
                        sbmv.add("error",e.getCondition());
                      } else if (e.getData().equals("<undeclared>")) {
                        typemv.add(ErrorT.TYPE,e.getCondition());
                        sbmv.add("error",e.getCondition());
                      } else {
                        typemv.add(NumberT.INT,e.getCondition());
                        sbmv.add(result + "." + e.getData(),e.getCondition());
                      }
                    }
                  }
                } else {
                  String result  // use the renamed symbol
                    = String.format(" %s ", entry.getData().getValue().toVariable().getName());
                  sbmv.add(result, entry.getCondition());
                  typemv.add(entry.getData().getValue().toVariable().getType(), entry.getCondition());
                }
              } else if (entry.getData().getValue() instanceof NamedFunctionT) {
                String result;  // use the renamed symbol
                if (!keepMem || !(Arrays.asList(memNames)).contains(originalName) ) {
                  result = String.format(" %s ", ((NamedFunctionT) entry.getData().getValue()).getName());
                } else {
                  result = originalName;
                }
                sbmv.add(result, entry.getCondition());
                typemv.add(((NamedFunctionT) entry.getData().getValue()).toFunctionT(), entry.getCondition());
              } else if (entry.getData().getValue() instanceof EnumeratorT) {
                String result  // use the renamed symbol
                  = String.format(" %s ", entry.getData().getValue().toEnumerator().getName());
                sbmv.add(result, entry.getCondition());
                typemv.add(entry.getData().getValue().toEnumerator().getType(), entry.getCondition());
                //check for union of forward reference enums
              } else {
                System.err.println(String.format("type error: use of symbol other than variable, function, or enumerator: %s", originalName));
                sbmv.add("error", entry.getCondition());
                typemv.add(ErrorT.TYPE, entry.getCondition());
              }
            }
          }
          // should be nonempty, since the above loop always adds to
          // it and the symtab should always return a non-empty mv
          assert ! sbmv.isEmpty();
          entries.destruct();
          setTransformationValue(value, new ExpressionValue(sbmv, typemv,new Multiverse<LineNumbers>(new LineNumbers((Syntax)getNodeAt(subparser, 1)),cond)));
        }  /* We cannot use a typedef name as a variable */
        ;

VariableArgumentAccess:  /** nomerge **/  // ADDED
        __BUILTIN_VA_ARG LPAREN AssignmentExpression COMMA TypeName RPAREN
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 6),(Syntax) getNodeAt(subparser, 1));
   
          PresenceCondition pc = subparser.getPresenceCondition();
          String prefix = String.format("%s %s",
                                        ((Syntax) getNodeAt(subparser, 6)).getTokenText(),
                                        ((Syntax) getNodeAt(subparser, 5)).getTokenText());
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 4, pc);
          String infix = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 2);
          String suffix = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          // convert to string and append tokens
          Multiverse<String> exprmv = exprval.transformation;
          Multiverse<String> prepended = exprmv.prependScalar(prefix, DesugarOps.concatStrings);
          Multiverse<String> expr_appended = prepended.appendScalar(infix, DesugarOps.concatStrings);
          
          Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          Multiverse<String> typename_appended = typenamestr.appendScalar(suffix, DesugarOps.concatStrings);
          Multiverse<String> transformationmv = expr_appended.product(typename_appended, DesugarOps.concatStrings);
          typename_appended.destruct(); typenamestr.destruct(); prepended.destruct();
          
          Multiverse<Type> typemv = DesugarOps.typenameToType.transform(typename);
          typemv = typemv.filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
          typemv.add(ErrorT.TYPE, exprval.type.getConditionOf(ErrorT.TYPE));
          expr_appended.destruct(); 
          todoReminder("typecheck VariableArgumentAccess (1)");

          setTransformationValue(value, new ExpressionValue(transformationmv, typemv,new Multiverse<LineNumbers>(lw,pc)));
        }
        ;

StatementAsExpression:  /** nomerge **/  //ADDED
        LPAREN { EnterScope(subparser); } CompoundStatement { ExitScope(subparser); } RPAREN
        /* LPAREN  LBRACE { EnterScope(subparser); } CompoundStatement { ExitScope(subparser); } RBRACE RPAREN */
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 5),(Syntax) getNodeAt(subparser, 1));
          
          // TODO: unit test this construct
          todoReminder("get last expression's type from compound statement in StatementAsExpression");

          PresenceCondition pc = subparser.getPresenceCondition();
          String lparen = ((Syntax) getNodeAt(subparser, 5)).getTokenText();
          Multiverse<DeclarationOrStatementValue>  ds = getCompleteNodeSingleValue(subparser, 3, pc);
          String rparen = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<DeclarationOrStatementValue> expanded = new Multiverse<DeclarationOrStatementValue>();
          for (Element<DeclarationOrStatementValue> e : ds) {
            Multiverse<List<DeclarationOrStatementValue>> inner = e.getData().separate(e.getCondition());
            for (Element<List<DeclarationOrStatementValue>> el : inner) {
              List<Multiverse<DeclarationOrStatementValue>> tempmv = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
              for (DeclarationOrStatementValue d : el.getData()) {
                tempmv.add(new Multiverse<DeclarationOrStatementValue>(d,el.getCondition()));
              }
              DeclarationOrStatementValue dsv = new DeclarationOrStatementValue("");
              dsv.setChildrenBlock("{",tempmv,"}");
              dsv.setIsStatementAsExpression();
              expanded.add(dsv,el.getCondition());
            }
          }
          
          Multiverse<String> valuemv = new Multiverse<String>();
          Multiverse<Type> typemv = new Multiverse<Type>();
          
          for (Element<DeclarationOrStatementValue> e : expanded) { 
            
            String res = "( " + e.getData().getString(e.getCondition(),this) + " )";
            valuemv.add(res,e.getCondition());
            Multiverse<Type> tt = e.getData().getType();
            if (tt != null && !tt.isEmpty()) {
              typemv.addAll(tt);
            } else {
              typemv.add(ErrorT.TYPE,e.getCondition());
            }
          }
          
          setTransformationValue(value, new ExpressionValue(valuemv,
                                                            typemv, new Multiverse<LineNumbers>(lw,pc)));  // TODO: placeholder; get type from compoundstatement
        }
        ;

PostfixExpression:  /** passthrough, nomerge **/ // ExpressionValue
        PrimaryExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | Subscript
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | FunctionCall
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | DirectSelection
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | IndirectSelection
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | Increment
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | Decrement
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | CompoundLiteral  /* ADDED */
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        ;

Subscript:  /** nomerge **/
        PostfixExpression LBRACK Expression RBRACK
        {
          // TODO: check that expression is numeric, check that postfixexpression is array, and get arrays types
          todoReminder("typecheck Subscript");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue postfixexprval = getCompleteNodeExpressionValue(subparser, 4, pc);
          String lbrack = (String) getNodeAt(subparser, 3).getTokenText();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          String rbrack = (String) getNodeAt(subparser, 1).getTokenText();

          Multiverse<String> prepended = exprval.transformation.prependScalar(lbrack, DesugarOps.concatStringsPropError);
          Multiverse<String> appended = prepended.appendScalar(rbrack, DesugarOps.concatStringsPropError);
          Multiverse<String> transformationmv = postfixexprval.transformation.product(appended, DesugarOps.concatStrings);
          prepended.destruct(); appended.destruct();
          
          if (postfixexprval.hasValidType() && exprval.hasValidType() && !transformationmv.isEmpty()) {
            Multiverse<Type> typemv = new Multiverse<Type>();
            for (int i = 0; i < postfixexprval.type.size(); ++i)
              {
                Element<Type> elemT = postfixexprval.type.get(i);
                if (elemT.getData().isError()) {
                  typemv.add(elemT.getData(), elemT.getCondition());
                  // __static_error (...) [2];
                } else {
                  Type tempT = elemT.getData();
                  while (tempT.isAnnotated() || tempT.isAlias()) {
                    tempT = ((WrappedT)tempT).getType();
                  }
                  // postfix expression should be a pointer or array type
                  if (tempT.isPointer()) {
                    // type should be whatever type the pointer point to
                    typemv.add(tempT.toPointer().getType(), elemT.getCondition());
                  } else if (tempT.isArray()) {
                    // type should be whatever type the array points to
                    typemv.add(tempT.toArray().getType(), elemT.getCondition());
                  } else {
                    typemv.add(ErrorT.TYPE, elemT.getCondition());
                    //stringmv.add(emitError("invalid subscript access"), elemS.getCondition());
                  }
                }
              }
            if (!typemv.isEmpty()) {
              typemv = typemv.filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
              typemv.add(ErrorT.TYPE, exprval.type.getConditionOf(ErrorT.TYPE));
              PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
              PresenceCondition validTypes = errorCond.not();
              transformationmv = transformationmv.filter(validTypes);
            } else {
              PresenceCondition errorCond = postfixexprval.type.getConditionOf(ErrorT.TYPE);
              transformationmv = transformationmv.filter(errorCond.not());
              typemv.add(ErrorT.TYPE,errorCond);
            }
            setTransformationValue(value, new ExpressionValue(transformationmv,
                                                              typemv, postfixexprval.integrateSyntax((Syntax)getNodeAt(subparser, 1))));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in subscript expression"),
                                                              ErrorT.TYPE, postfixexprval.integrateSyntax((Syntax)getNodeAt(subparser, 1)),
                                                              pc));
          }
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
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);
          String lparen = "(";
          String rparen = ")";


          if (exprval.hasValidType()) {
            String appendstr = String.format("%s %s", lparen, rparen);
            Multiverse<String> valuemv = new Multiverse<String>();
            // the resulting type of the function call is the return value
            Multiverse<Type> returntype = DesugarOps.getReturnType.transform(exprval.type);

            
            for (Element<Type> et : exprval.type ) {
              Type x = et.getData();
              if (x.isPointer()) {
                x = ((PointerT)x).getType().resolve();
              }
              if (
                  (x.isFunction() || x instanceof NamedFunctionT) &&
                  (
                   ((FunctionOrMethodT)x).getParameters().size() == 0
                   ||
                   (((FunctionOrMethodT)x).getParameters().size() == 1 &&
                    ((FunctionOrMethodT)x).getParameters().get(0).resolve().isVoid()
                    ))) {
                for (Element<String> es : exprval.transformation) {
                  if (es.getCondition().is(et.getCondition())) {
                    valuemv.add(es.getData() + "( )",et.getCondition());
                  }
                }
              } else {
                returntype = returntype.filter(et.getCondition().not());
                returntype.add(ErrorT.TYPE,et.getCondition());
                valuemv.add(emitError("Parameters expected in empty function call"), et.getCondition());
              }
            }
            setTransformationValue(value, new ExpressionValue(valuemv,
                                                              returntype, exprval.integrateSyntax((Syntax)getNodeAt(subparser, 1)))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in function call"),
                                                              ErrorT.TYPE, exprval.integrateSyntax((Syntax)getNodeAt(subparser, 1)),
                                                              pc));
          }
        }
        | PostfixExpression LPAREN ExpressionList RPAREN
        {
          // type check by making sure the postfixexpression type is a
          // function, that each type of the expressionlist matches
          // each type of the function types's list, and setting the
          // return value to the type
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue postfixexprval = getCompleteNodeExpressionValue(subparser, 4, pc);
          /* System.err.println("PFTYPE: " + postfixexprval.type); */
          /* System.err.println("PFTRAN: " + postfixexprval.transformation); */
          if (postfixexprval.hasValidType()) {
            /* postfixexprval.transformation; */
            Multiverse<String> lparen
              = new Multiverse<String>("(", pc);
            Multiverse<String> rparen
              = new Multiverse<String>(")", pc);

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
            boolean hasinvalidparameter = false;
            for (ExpressionValue listelem : exprlist) {
              if (! listelem.hasValidType()) {
                hasinvalidparameter = true;
                break;
              }
              // wrap each listelem's string and type in a list
              /* System.err.println("LISTELEM: " + listelem.transformation); */
              /* System.err.println("LISTELEM: " + listelem.type); */
              Multiverse<List<String>> wrapped_listelem_transformation
                = DesugarOps.stringListWrap.transform(listelem.transformation);
              Multiverse<List<Type>> wrapped_listelem_type
                = DesugarOps.typeListWrap.transform(listelem.type);

              // take the product of the multiverse of lists collected
              // so far with the new element
              Multiverse<List<String>> new_exprlistmv
                = exprlistmv.complementedProduct(wrapped_listelem_transformation,
                                                 DesugarOps.STRINGLISTCONCAT);
              Multiverse<List<Type>> new_exprlisttypemv
                = exprlisttypemv.complementedProduct(wrapped_listelem_type,
                                                     DesugarOps.TYPELISTCONCAT);

              exprlistmv.destruct(); exprlistmv = new_exprlistmv;
              exprlisttypemv.destruct(); exprlisttypemv = new_exprlisttypemv;
            }
            if (! hasinvalidparameter) {

              /* System.err.println("EXPRLISTMV: " + exprlistmv); */
              /* System.err.println("EXPRLISTTYPEMV: " + exprlisttypemv); */

              // typecheck each combination of postfix expression and
              // parameter list.
              Multiverse<Type> typemv = new Multiverse<Type>();
              Multiverse<String> valuemv = new Multiverse<String>();
              // collect the presence condition of all type errors
              PresenceCondition errorCond
                = subparser.getPresenceCondition().presenceConditionManager().newFalse();
              // loop over each combination of postfix expression and
              // parameter list
              for (Element<Type> postfixelem : postfixexprval.type) {
                Multiverse<String> startCall = postfixexprval.transformation.filter(postfixelem.getCondition());
                if (!startCall.isEmpty()) {
                  for (Element<String> ess : startCall) {
                    valuemv.add(ess.getData() + " (", ess.getCondition());
                  }
                }
                Type xx = postfixelem.getData();
                if (xx.isPointer()) {
                  xx = ((PointerT)xx).getType().resolve();
                }
                // check that postfix expression is a function type
                if (xx.isFunction() || xx instanceof NamedFunctionT) {
                  PresenceCondition remain = postfixelem.getCondition();
                  FunctionT functiontype = xx.toFunction();
                  List<Type> formals = functiontype.getParameters();
                  for (Element<List<Type>> exprlisttype : exprlisttypemv) {
                    for (Element<List<String>> exprliststring : exprlistmv) { 
                      PresenceCondition combinedCond = postfixelem.getCondition().and(exprlisttype.getCondition().and(exprliststring.getCondition()));
                      //if there is no overlap between the two move on
                      if (combinedCond.isFalse()) {
                        continue;
                      }
                      remain = remain.and(combinedCond.not());
                      // compare formal vs actual parameter types
                      int size1 =  formals.size();
                      int size2 = exprlisttype.getData().size();
                      int min = Math.min(size1, size2);
                      boolean hasError = false;
                      for (Type t : exprlisttype.getData()) {
                        if (t == ErrorT.TYPE) {
                          hasError = true;
                          break;
                        }
                      }
                      if (hasError || exprliststring.getData().size() != size2) {
                        PresenceCondition new_errorCond = errorCond.or(combinedCond);
                        valuemv = valuemv.filter(combinedCond.not());
                        valuemv.add(emitError("A parameter expression is an error"), combinedCond);
                        errorCond.delRef(); errorCond = new_errorCond;
                      }
                      else if (size1 > size2) {
                        // TODO: unit test
                        PresenceCondition new_errorCond = errorCond.or(combinedCond);
                        valuemv = valuemv.filter(combinedCond.not());
                        valuemv.add(emitError("too few arguments to function"), combinedCond);
                        errorCond.delRef(); errorCond = new_errorCond;
                      } else if ((! functiontype.isVarArgs()) && (size1 < size2)) {
                        // TODO: unit test
                        PresenceCondition new_errorCond = errorCond.or(combinedCond);
                        valuemv = valuemv.filter(combinedCond.not());
                        valuemv.add(emitError("too many arguments to function"), combinedCond);
                        errorCond.delRef(); errorCond = new_errorCond;
                      } else {  // parameter size is right
                        // check compare each of the parameters' types
                        // one-at-a-time and if one doesn't match, break
                        // and set the presence condition to be an error
                        boolean match = true;
                        for (int i = 0; i < min; i++) {
                          Type formal = formals.get(i).resolve();
                          Type actual = exprlisttype.getData().get(i).resolve();
                          if (formal.isUnion() && !actual.isUnion()) {
                            //assuming size 1
                            Multiverse<Boolean> matches = hasField((UnionT)formal,actual,(CContext)subparser.scope,combinedCond);
                            if (!matches.isEmpty() && matches.get(0).getData() ) {
                              valuemv = appendStringToMV(valuemv, "(union " + ((UnionT)formal).getName() + ")", combinedCond);
                              valuemv = appendStringToMV(valuemv, exprliststring.getData().get(i) + ",", combinedCond);
                            } else {
                              match = false;
                              break;
                            }
                          
                          } else if (compatParam(formal, actual)) {
                            valuemv = appendStringToMV(valuemv, exprliststring.getData().get(i) + ",", combinedCond);
                          } else {
                            match = false;
                            break;
                          }
                        }
                        for (int i = min; i < size2; ++i) {
                          Multiverse<List<String>> tt = exprlistmv.filter(combinedCond);
                          for (Element<List<String>> tte : tt) {
                            valuemv = appendStringToMV(valuemv, tte.getData().get(i) + ",", tte.getCondition());
                          }
                          tt.destruct();
                        }
                        if (match) {
                          // the expression's type is the return value's type of the function being called
                          typemv.add(functiontype.getResult(), combinedCond);
                        } else {
                          todoReminder("do proper type checking for function calls");
                          valuemv = valuemv.filter(combinedCond.not());
                          valuemv.add(emitError("parameter type mismatch"),combinedCond);
                          PresenceCondition new_errorCond = errorCond.or(combinedCond);
                          errorCond.delRef(); errorCond = new_errorCond;
                        }
                      }
                      combinedCond.delRef();
                    } // end loop over parameter list strings
                  }  // end loop over parameter list
                  //there are not expression lists under this condition within postfixelem
                  if (remain.isNotFalse()) {
                    valuemv = valuemv.filter(remain.not());
                    valuemv.add(emitError("expression list undefined"),remain);
                    PresenceCondition new_errorCond = errorCond.or(remain);
                    errorCond.delRef(); errorCond = new_errorCond;
                  }
                  remain.delRef();
                } else {  // not a function type
                  PresenceCondition new_errorCond = errorCond.or(postfixelem.getCondition());
                  // TODO: unit test
                  valuemv = valuemv.filter(postfixelem.getCondition().not());
                  valuemv.add(emitError("attempting function call on non-function type"),postfixelem.getCondition());
                  errorCond.delRef(); errorCond = new_errorCond;
                } // end check for function type
              } // end loop over postfixelems
              typemv.add(ErrorT.TYPE, errorCond);
              
              // should be non-empty because either errorCond is
              // non-false or some parameter list matched and added the
              // return type
              assert ! typemv.isEmpty();
              
              // filter out the postfix value and the expression list
              // values that are type errors.
              PresenceCondition validTypes = errorCond.not();
              valuemv = removeTrailing(valuemv,validTypes);
              valuemv = appendStringToMV(valuemv, ")", validTypes);
              errorCond.delRef(); validTypes.delRef();
              
              assert ! valuemv.isEmpty();
              setTransformationValue(value, new ExpressionValue(valuemv, typemv, postfixexprval.integrateSyntax((Syntax)getNodeAt(subparser, 1))));
            } else {
              setTransformationValue(value, new ExpressionValue(emitError("no valid type for one or more arguments of the function call"),
                                                                ErrorT.TYPE, postfixexprval.integrateSyntax((Syntax)getNodeAt(subparser, 1)),
                                                                pc));
            }
          } else { // types of postfixexprval are all errors
            // TODO: this throws away the type message from the child,
            // so perhaps copy the child's mv values instead.
            setTransformationValue(value, new ExpressionValue(emitError("no valid type for the function part of the function call"),
                                                              ErrorT.TYPE, postfixexprval.integrateSyntax((Syntax)getNodeAt(subparser, 1)),
                                                              pc));
          }
        }
        ;

DirectSelection:  /** nomerge **/  // ExpressionValue
        PostfixExpression DOT IdentifierOrTypedefName
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          todoReminder("correctly handle anonymous union direct selection");
          ExpressionValue postfixval = getCompleteNodeExpressionValue(subparser, 3, subparser.getPresenceCondition());

          Multiverse<String> postfixmv = postfixval.transformation;
          Multiverse<String> dotmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(),
                                     subparser.getPresenceCondition());
          String ident = ((Syntax) getNodeAt(subparser, 1).get(0)).getTokenText();

          // get each struct type
          // check whether its a forward reference or not
          // for regular structs, look up the fieldname in the lookaside table, and expand all possible renamings
          // for forward reference structs, go the actual struct, find its renamings, and find the field names in the lookaside table (these must be defined by now, per C's forward reference rules)

          // go through each type and see which have a field with this
          // name and collect the resulting type
          Multiverse<Type> postfixtype = postfixval.type;
          Multiverse<Type> typemv = new Multiverse<Type>();  // resulting type
          Multiverse<String> identmv = new Multiverse<String>();  // desugaring
          CContext scope = ((CContext) subparser.scope);
          boolean hasValidType = false;
          for (Element<Type> type : postfixtype) {
            // check that the postfix type is a struct or union
            Type resolvedType = type.getData().resolve();  // unwrap any typedef aliasing
            /* System.err.println("UNWRAPPED TYPE: " + resolvedType); */
            if (resolvedType.isStruct() || resolvedType.isUnion()) {
              StructOrUnionT sutype = resolvedType.toStructOrUnion();
              String tag = sutype.getName();
              assert tag != null;  // even anonymous structs get a name

              // the struct type specifier ensures that the type is
              // already entered in the symbol table, so we can assume
              // it's there and in the lookaside table.
              
              // the ref will either be to a renamed tag or to a forward reference
              if (tag.startsWith("__forward_tag_reference_")) {
                // TODO: is there a safer way to check for this?

                String originalTag = scope.getForwardTagReferenceAnyScope(tag);
                

                Multiverse<SymbolTable.Entry<Type>> originalTagEntries
                  = scope.getInAnyScope(CContext.toTagName(originalTag), type.getCondition());
                
                // add an indirect reference to the real struct via the forward-referenced struct
                for (Element<SymbolTable.Entry<Type>> tagentry : originalTagEntries) {
                  if (tagentry.getData().isError()) {
                    System.err.println("INFO: type error, access to undeclared struct/union field");
                    typemv.add(ErrorT.TYPE, tagentry.getCondition());
                  } else if (tagentry.getData().isUndeclared()) {
                    // no declaration in this configuration
                    System.err.println(String.format("INFO: type error, access to undeclared struct/union %s", originalTag));
                    typemv.add(ErrorT.TYPE, tagentry.getCondition());
                  } else {  // the struct/union is defined under this configuration
                    Type renamedStruct = tagentry.getData().getValue();

                    if (renamedStruct.isStruct() || renamedStruct.isUnion()) {
                      // get the referenced type's renaming
                      String renamedTag = renamedStruct.toStructOrUnion().getName();
                      
                      // check the lookaside table for the renamings of the struct field
                      SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(renamedTag);

                      // renamed the field according to the tag lookaside
                      // table, or produce an error if that configuration is
                      // missing the field.  expand to all possible
                      // variations of the field.
                      Multiverse<SymbolTable.Entry<Declaration>> fieldentries = tagtab.get(ident, tagentry.getCondition());
                      for (Element<SymbolTable.Entry<Declaration>> fieldentry : fieldentries) {
                        if (fieldentry.getData().isError()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else if (fieldentry.getData().isUndeclared()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else {  // declared
                          VariableT fieldtype = fieldentry.getData().getValue().getType().toVariable();  // these are stored as VariableT
                          typemv.add(fieldtype.getType(), fieldentry.getCondition());
                          String indirectaccess = String.format("%s . %s", renamedTag, fieldentry.getData().getValue().getName());
                          identmv.add(indirectaccess, fieldentry.getCondition());
                          hasValidType = true;
                        }
                      }
                    } else {  // is not a struct/union type
                      System.err.println(String.format("INFO: type error, DirectSelect on non-struct/union tag %s", originalTag));
                      typemv.add(ErrorT.TYPE, tagentry.getCondition());
                    }  // finished check for struct/union type
                  } // finished looking at the entry
                }  // finished going over the original tag's renamings
                
              } else {  // a renamed tag, rather than a forward reference tag
                // as long as the struct type specifiers are correct,
                // this should always refer to a known (renamed)
                // struct tag.

                //when here, we also need to check fields nested inside of anon structs/unions.
                //these can't be forward references, so it only needs to be handled here.
                PresenceCondition temp = type.getCondition();
                Multiverse<Map.Entry<String,Declaration>> access = getNestedFields(tag,ident,temp,scope);
                if (!access.isEmpty()) {
                  for (Element<Map.Entry<String,Declaration>> e : access) {
                    String fields = e.getData().getKey();
                    if (fields.equals("")) {
                      //more than one match was found
                      typemv.add(ErrorT.TYPE, e.getCondition());
                      identmv.add("", e.getCondition());
                    } else {
                      //found a match
                      VariableT fieldType = ((VariableT)e.getData().getValue().getType());
                      typemv.add(fieldType.getType(), e.getCondition());
                      identmv.add(e.getData().getValue().getName(), e.getCondition());
                      hasValidType = true;
                    }
                  }
                  if (!access.getComplement().and(temp).isFalse()) {
                    typemv.add(ErrorT.TYPE, access.getComplement().and(temp));
                    identmv.add("", access.getComplement().and(temp));
                  }
                } else {
                  typemv.add(ErrorT.TYPE, temp);
                  identmv.add("", temp);
                }
                temp.delRef();
              }
            } else {
              System.err.println("INFO: type error, not a struct/union type in DirectSelection");
              typemv.add(ErrorT.TYPE, type.getCondition());
            }
          }
              
          assert ! typemv.isEmpty();

          if (hasValidType && !postfixmv.isEmpty()) {
            Multiverse<String> valuemv = postfixmv.product(dotmv,DesugarOps.concatStrings);
            valuemv = valuemv.product(identmv, DesugarOps.concatStrings);
            dotmv.destruct(); identmv.destruct();
            // valuemv shouldn't need to filtered for error conditions,
            // because identmv only has those configurations that were
            // correctly typed

            /* System.err.println("valuemv " + valuemv); */
            /*           PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition typesafeCond = errorCond.not();
            valuemv = valuemv.filter(typesafeCond);
            errorCond.delRef(); typesafeCond.delRef();*/
            setTransformationValue(value, new ExpressionValue(valuemv, typemv, postfixval.integrateSyntax(((Syntax) getNodeAt(subparser, 1).get(0)))));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in direct expression"),
                                                              ErrorT.TYPE, postfixval.integrateSyntax(((Syntax) getNodeAt(subparser, 1).get(0))),
                                                              pc));
          }
        }
;

IndirectSelection:  /** nomerge **/
        PostfixExpression ARROW IdentifierOrTypedefName
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          // TODO: need to cast PostfixExpression to the union field
          // of the configurable struct declaration.  this means we
          // need to know the type of postfixexpression

          // TODO: check that postfix expression is a pointer to a struct and that the identifier is one of its fields

          ExpressionValue postfixval = getCompleteNodeExpressionValue(subparser, 3, subparser.getPresenceCondition());

          Multiverse<String> postfixmv = postfixval.transformation;
          String arrow = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String ident = ((Syntax) getNodeAt(subparser, 1).get(0)).getTokenText();

          // go through each type and see which have a field with this
          // name and collect the resulting type
          Multiverse<Type> postfixtype = postfixval.type;
          Multiverse<Type> typemv = new Multiverse<Type>();  // resulting type
          Multiverse<String> identmv = new Multiverse<String>();  // desugaring
          CContext scope = ((CContext) subparser.scope);
          boolean hasValidType = false;
          for (Element<Type> type : postfixtype) {
            // check that the postfix type is a pointer to a struct/union
            Type resolvedType = type.getData().resolve();  // unwrap any typedef aliasing
            if (resolvedType.isPointer()
                && (resolvedType.toPointer().getType().resolve().isStruct()
                    || resolvedType.toPointer().getType().resolve().isUnion())) {
              StructOrUnionT sutype = resolvedType.toPointer().getType().resolve().toStructOrUnion();
              String tag = sutype.getName();
              assert tag != null;  // even anonymous structs get a name, e.g., anonymous(0)

              // below is the same as directselection
              
              // the ref will either be to a renamed tag or to a forward reference
              if (tag.startsWith("__forward_tag_reference_")) {
                // TODO: is there a safer way to check for this?

                String originalTag = scope.getForwardTagReferenceAnyScope(tag);
                
                
                Multiverse<SymbolTable.Entry<Type>> originalTagEntries
                  = scope.getInAnyScope(CContext.toTagName(originalTag), type.getCondition());

                // add an indirect reference to the real struct via the forward-referenced struct
                for (Element<SymbolTable.Entry<Type>> tagentry : originalTagEntries) {
                  if (tagentry.getData().isError()) {
                    System.err.println("INFO: type error, access to undeclared struct/union field");
                    typemv.add(ErrorT.TYPE, tagentry.getCondition());
                  } else if (tagentry.getData().isUndeclared()) {
                    // no declaration in this configuration
                    System.err.println(String.format("INFO: type error, access to undeclared struct/union %s", originalTag));
                    typemv.add(ErrorT.TYPE, tagentry.getCondition());
                  } else {  // the struct/union is defined under this configuration
                    Type renamedStruct = tagentry.getData().getValue();

                    if (renamedStruct.isStruct() || renamedStruct.isUnion()) {
                      // get the referenced type's renaming
                      String renamedTag = renamedStruct.toStructOrUnion().getName();
                      
                      // check the lookaside table for the renamings of the struct field
                      SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(renamedTag);

                      // renamed the field according to the tag lookaside
                      // table, or produce an error if that configuration is
                      // missing the field.  expand to all possible
                      // variations of the field.
                      Multiverse<SymbolTable.Entry<Declaration>> fieldentries = tagtab.get(ident, tagentry.getCondition());
                      for (Element<SymbolTable.Entry<Declaration>> fieldentry : fieldentries) {
                        if (fieldentry.getData().isError()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else if (fieldentry.getData().isUndeclared()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else {  // declared
                          VariableT fieldtype = fieldentry.getData().getValue().getType().toVariable();  // these are stored as VariableT
                          typemv.add(fieldtype.getType(), fieldentry.getCondition());
                          String indirectaccess = String.format("%s . %s", renamedTag, fieldentry.getData().getValue().getName());
                          identmv.add(indirectaccess, fieldentry.getCondition());
                          hasValidType = true;
                        }
                      }
                    } else {  // is not a struct/union type
                      System.err.println(String.format("INFO: type error, IndirectSelect on non-struct/union tag %s", originalTag));
                      typemv.add(ErrorT.TYPE, tagentry.getCondition());
                    }  // finished check for struct/union type
                  } // finished looking at the entry
                }  // finished going over the original tag's renamings
                
              } else {
                // a renamed tag, rather than a forward reference tag
                // as long as the struct type specifiers are correct,
                // this should always refer to a known (renamed)
                // struct tag.
                SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(tag);

                // renamed the field according to the tag lookaside
                // table, or produce an error if that configuration is
                // missing the field.  expand to all possible
                // variations of the field.
                Multiverse<SymbolTable.Entry<Declaration>> fieldentries = tagtab.get(ident, type.getCondition());
                for (Element<SymbolTable.Entry<Declaration>> fieldentry : fieldentries) {
                  if (fieldentry.getData().isError()) {
                    typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                  } else if (fieldentry.getData().isUndeclared()) {
                    typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                  } else {  // declared
                    VariableT fieldtype = fieldentry.getData().getValue().getType().toVariable();  // these are stored as VariableT
                    typemv.add(fieldtype.getType(), fieldentry.getCondition());
                    identmv.add(fieldentry.getData().getValue().getName(), fieldentry.getCondition());
                    hasValidType = true;
                  }
                }
              }
    
            } else {
              // TODO: not a pointer, type error
              typemv.add(ErrorT.TYPE, type.getCondition());
            }
          }
          
          assert ! typemv.isEmpty();

          /* System.err.println("typemv " + typemv); */
          /* System.err.println("identmv " + identmv); */

          if (hasValidType && !postfixmv.isEmpty()) {
            Multiverse<String> prepend = identmv.prependScalar(arrow, DesugarOps.concatStrings);
            Multiverse<String> valuemv = postfixmv.product(prepend, DesugarOps.concatStrings);
            identmv.destruct(); prepend.destruct();
            if (!valuemv.isEmpty()) {
              valuemv = valuemv.filter(typemv.getConditionOf(ErrorT.TYPE).not());
            }
            valuemv.add(emitError("no valid type found in indirect expression"), typemv.getConditionOf(ErrorT.TYPE));
            /* System.err.println("valuemv " + valuemv); */
            setTransformationValue(value, new ExpressionValue(valuemv, typemv, postfixval.integrateSyntax(((Syntax) getNodeAt(subparser, 1).get(0)))));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in indirect expression"),
                                                              ErrorT.TYPE, postfixval.integrateSyntax(((Syntax) getNodeAt(subparser, 1).get(0))),
                                                              pc));
          }
        }
        ;

Increment:  /** nomerge **/  // ExpressionValue
        PostfixExpression ICR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);

          Multiverse<Syntax> opmv = getSyntaxMV(subparser, 1, pc);
          if (exprval.hasValidType() && !exprval.isEmpty() && !opmv.isEmpty()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = exprval.transformation.product(opstr, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv,
                                                       exprval.integrateSyntax((Syntax) getNodeAt(subparser, 1))));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE, exprval.integrateSyntax((Syntax) getNodeAt(subparser, 1)),
                                                              pc));
          }
        }
        ;

Decrement:  /** nomerge **/  // ExpressionValue
        PostfixExpression DECR
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);

          Multiverse<Syntax> opmv = getSyntaxMV(subparser, 1, pc);
          if (exprval.hasValidType() && !opmv.isEmpty()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = exprval.transformation.product(opstr, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv, exprval.integrateSyntax((Syntax) getNodeAt(subparser, 1))));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE, exprval.integrateSyntax((Syntax) getNodeAt(subparser, 1)),
                                                              pc));
          }
        }
        ;

CompoundLiteral:  /** nomerge **/  /* ADDED */
        LPAREN TypeName RPAREN LBRACE InitializerList RBRACE
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 6),(Syntax) getNodeAt(subparser, 1));
          
          // TODO compare the expression's type against the type name
          // to rule out invalid casts.
          todoReminder("check the legality of the cast and the initializer list types");

          PresenceCondition pc = subparser.getPresenceCondition();
          
          String lparen = ((Syntax) getNodeAt(subparser, 6)).getTokenText();
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 5);
          String rparen = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          String lbrace = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<List<Initializer>> initializerlist = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 2);
          String rbrace = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          Multiverse<String> mv1 = typenamestr.prependScalar(lparen, DesugarOps.concatStrings); typenamestr.destruct();
          Multiverse<String> mv2 = mv1.appendScalar(rparen, DesugarOps.concatStrings); mv1.destruct();
          Multiverse<Initializer> initializerlistmv
            = DesugarOps.toInitializerList.transform(initializerlist);
          
          Multiverse<String> initializerliststr = new Multiverse<String>();
	  PresenceCondition error = (new PresenceConditionManager()).newFalse();
          for (Element<Declaration> ed : typename) {
            for (Element<Initializer> ei : initializerlistmv) {
              PresenceCondition cc = ed.getCondition().and(ei.getCondition()); 
              initializerliststr.addAll(ei.getData().renamedList(new Multiverse<Type>(ed.getData().getType().resolve(),cc),cc,(CContext)subparser.scope));
	      PresenceCondition thisError = ei.getData().getErrorsIn(new Multiverse<Type>(ed.getData().getType().resolve(),cc),cc);
	      error = error.or(thisError);
	      thisError.delRef();
              cc.delRef();
            }
          }
	        initializerlistmv.destruct();

          Multiverse<String> mv4
            = mv2.product(initializerliststr, DesugarOps.concatStrings); initializerliststr.destruct(); //mv3.destruct();
          //Multiverse<String> transformationmv = mv4.appendScalar(rbrace, DesugarOps.concatStrings); mv4.destruct();

          Multiverse<Type> typemv = DesugarOps.typenameToType.transform(typename);
	  Multiverse<Type> filtered = typemv.filter(error.not());
	  filtered.add(ErrorT.TYPE,error); typemv.destruct();
	    
          setTransformationValue(value, new ExpressionValue(mv4, filtered, new Multiverse<LineNumbers>(lw,pc)));
        }
        ;

ExpressionList:  /** list, nomerge **/  // List<ExpressionValue>
        AssignmentExpression
        {
          // create a new list
          List<ExpressionValue> exprlist = new LinkedList<ExpressionValue>();
          ExpressionValue exprval
            = getCompleteNodeExpressionValue(subparser,1, subparser.getPresenceCondition());
          exprlist.add(exprval);
          setTransformationValue(value, exprlist);
        }
        | ExpressionList COMMA AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // add to the existing expression list.  this reuse of a
          // semantic value may be an issue if static conditionals are
          // permitted under expressionlists
          List<ExpressionValue> exprlist = getCompleteNodeExpressionListValue(subparser, 3, pc);
          ExpressionValue exprval
            = getCompleteNodeExpressionValue(subparser,1, subparser.getPresenceCondition());
          exprlist.add(exprval);
          setTransformationValue(value, exprlist);

          /* // add to the existing expression list.  this reuse of a */
          /* // semantic value may be an issue if static conditionals are */
          /* // permitted under expressionlists */
          /* List<ExpressionValue> exprlist */
          /*   = (LinkedList<ExpressionValue>) getTransformationValue(subparser,3); */
          /* ExpressionValue exprval */
          /*   = getCompleteNodeExpressionValue(subparser,1, subparser.getPresenceCondition()); */
          /* exprlist.add(exprval); */
          /* setTransformationValue(value, exprlist); */
        }
        ;

UnaryExpression:  /** passthrough, nomerge **/  // ExpressionValue
        PostfixExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | ICR UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Syntax> opmv = getSyntaxMV(subparser, 2, pc);
          if (exprval.hasValidType() && !exprval.isEmpty() && !opmv.isEmpty()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = opstr.product(exprval.transformation, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv, exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2))));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2)),
                                                              pc));
          }
        }
        | DECR UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Syntax> opmv = getSyntaxMV(subparser, 2, pc);
          if (exprval.hasValidType() && !exprval.isEmpty() && !opmv.isEmpty()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = opstr.product(exprval.transformation, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv,exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2))));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2)),
                                                              pc));
          }
        }
| Unaryoperator CastExpression
{
  // TODO: need to look at the unaryoperator to determine whether it's the correct type usage
  PresenceCondition pc = subparser.getPresenceCondition();
  ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);
  Multiverse<String> resultmv = new Multiverse<String>();
  Multiverse<Type> resulttypemv = new Multiverse<Type>();
          
  Multiverse<Syntax> opmv = this.<Syntax>getCompleteNodeSingleValue(subparser, 2, pc);
  Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
  for (Element<String> op : opstr) {
    if (op.getData().equals("*")) {

      Multiverse<Type> types = exprval.type.filter(op.getCondition());
      for (Element<Type> t : types) {
        if (!t.getData().isPointer() && !t.getData().isArray()) {
          resultmv.add(emitError("no valid type found in unary operation"),t.getCondition());
          resulttypemv.add(ErrorT.TYPE,t.getCondition());
        } else {
          
          Type innerType;
          if (t.getData().isPointer()) {
            innerType = t.getData().toPointer().getType();
          } else {
            innerType = t.getData().toArray().getType();
          }
          if (innerType.isStruct() && innerType.toStruct().getName().startsWith("__forward_tag_reference")) {
            CContext scope = (CContext) subparser.scope;
            String originalTag = scope.getForwardTagReferenceAnyScope(innerType.getName());
                       
            Multiverse<SymbolTable.Entry<Type>> originalTagEntries
              = scope.getInAnyScope(CContext.toTagName(originalTag), t.getCondition());
            
            for (Element<SymbolTable.Entry<Type>> e : originalTagEntries) {
              if (e.getData().isError()) {
                resultmv.add(emitError("no valid type found in unary operation"),t.getCondition());
                resulttypemv.add(ErrorT.TYPE,e.getCondition());
              } else {
                StructT refed =  e.getData().getValue().toStruct();
                for (Element<String> es : exprval.transformation.filter(e.getCondition())) {
                  resultmv.add(es.getData() + "->" + refed.getName(), es.getCondition());
                  resulttypemv.add(refed,es.getCondition());
                }
              }
            }
          } else {
            if (exprval.hasValidType() && !exprval.transformation.isEmpty()) {
              Multiverse<String> strings = opstr.filter(t.getCondition()).product(exprval.transformation, DesugarOps.concatStrings);
              Multiverse<Type> subtypes = exprval.type.filter(t.getCondition()).join(opmv, DesugarOps.checkUnaryOp);
              PresenceCondition errorCond = subtypes.getConditionOf(ErrorT.TYPE);
              PresenceCondition validTypes = errorCond.not();
              resultmv.addAll(strings.filter(validTypes));
              resulttypemv.addAll(subtypes);
            } else {
              resultmv.add(emitError("no valid type found in unary operation"),t.getCondition());
              resulttypemv.add(ErrorT.TYPE,t.getCondition());

            }
          }
        }
      }
    } else {
      if (exprval.hasValidType() && !exprval.transformation.isEmpty()) {
        Multiverse<String> strings = opstr.filter(op.getCondition()).product(exprval.transformation, DesugarOps.concatStrings);
        Multiverse<Type> types = exprval.type.filter(op.getCondition()).join(opmv, DesugarOps.checkUnaryOp);
        PresenceCondition errorCond = types.getConditionOf(ErrorT.TYPE);
        PresenceCondition validTypes = errorCond.not();
        resultmv.addAll(strings.filter(validTypes));
        resulttypemv.addAll(types);
      } else {
        resultmv.add(emitError("no valid type found in unary operation"),op.getCondition());
        resulttypemv.add(ErrorT.TYPE,op.getCondition());

      }
    }
  }
setTransformationValue(value, new ExpressionValue(resultmv,resulttypemv,
                                                  exprval.integrateSyntax(opmv)));
}
| SIZEOF UnaryExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> exprmv = sizeofExpansion(exprval.transformation, exprval.type,freshIdCreator,(CContext)subparser.scope,pc);
          todoReminder("typecheck unaryexpression (5)");

          Type constSizeOf = C.SIZEOF.copy();
          constSizeOf.addAttribute(Constants.ATT_CONSTANT);
          
          Multiverse<Type> type = new Multiverse<Type>();
          for (Element<Type> e : exprval.type) {
            if (e.getData() != ErrorT.TYPE) {
              type.add(constSizeOf,e.getCondition());
            }
          }
          type.add(ErrorT.TYPE, exprval.type.getConditionOf(ErrorT.TYPE));
          setTransformationValue(value,
                                 new ExpressionValue(exprmv,
                                                     type,
                                                     exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2))));
        }
        | SIZEOF LPAREN TypeName RPAREN
        {
         
          PresenceCondition pc = subparser.getPresenceCondition();
          String prefix = String.format("%s %s",
                                        ((Syntax) getNodeAt(subparser, 4)).getTokenText(),
                                        ((Syntax) getNodeAt(subparser, 3)).getTokenText());
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 2);
          Multiverse<Type> directTypes = new Multiverse<Type>();
          for (Element<Declaration> e : typename) {
            directTypes.add(e.getData().getType().resolve(),e.getCondition());
          }
          String suffix = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 4),(Syntax) getNodeAt(subparser, 1));
          
          // convert to string and append tokens
          
          //Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          //To deal with stucts in sizeof, we need to offload this to emulate struct size calculation
          
          Multiverse<String> typenamestr = sizeofExpansion(directTypes,freshIdCreator,(CContext)subparser.scope,pc);
          todoReminder("typecheck unaryexpression (6)");
          Type constSizeOf = C.SIZEOF.copy();
          constSizeOf.addAttribute(Constants.ATT_CONSTANT);
          Multiverse<Type> type = new Multiverse<Type>();

          for (Element<Declaration> e : typename) {
            if (e.getData().getType() != ErrorT.TYPE) {
              type.add(constSizeOf,e.getCondition());
            } else {
              type.add(ErrorT.TYPE, e.getCondition());
            }
          }
          
          
          setTransformationValue(value, new ExpressionValue(typenamestr, type, new Multiverse<LineNumbers>(lw,pc)));
        }
        | LabelAddressExpression  // ADDED
        {
          todoReminder("typecheck unaryexpression (7)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | AlignofExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (8)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | ExtensionExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (9)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | OffsetofExpression // ADDED
        {
          todoReminder("typecheck unaryexpression (10)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | TypeCompatibilityExpression  // ADDED
        {
          todoReminder("typecheck unaryexpression (11)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        ;

TypeCompatibilityExpression:  /** nomerge **/
        __BUILTIN_TYPES_COMPATIBLE_P LPAREN TypeName COMMA TypeName RPAREN
        {
          System.err.println("ERROR: unsupported semantic action: TypeCompatibilityExpression");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

// per https://gcc.gnu.org/onlinedocs/gcc/Offsetof.html
OffsetofMemberDesignator:  // Multiverse<OffsetofMemberDesignator>
        IDENTIFIER
        {
          todoReminder("typcheck offsetofmemberdesignator (1)");
          String ident = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          List<Designator> list = new LinkedList<Designator>();
          setTransformationValue(value,
                                 new Multiverse<OffsetofMemberDesignator>(new OffsetofMemberDesignator(ident, list),
                                                                          subparser.getPresenceCondition()));
        }
        | IDENTIFIER DesignatorList
        {
          todoReminder("typcheck offsetofmemberdesignator (2)");
          Multiverse<String> identmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(),
                                     subparser.getPresenceCondition());
          Multiverse<List<Designator>> listmv
            = (Multiverse<List<Designator>>) getTransformationValue(subparser, 1);
          setTransformationValue(value, identmv.join(listmv, DesugarOps.joinOffsetof));
        }
        ;

OffsetofExpression:  /** nomerge **/
        /* __BUILTIN_OFFSETOF LPAREN TypeName COMMA PostfixExpression RPAREN */
        __BUILTIN_OFFSETOF LPAREN TypeName COMMA OffsetofMemberDesignator RPAREN
        {
          LineNumbers lw = new LineNumbers((Syntax) getNodeAt(subparser, 6),(Syntax) getNodeAt(subparser, 1));
          PresenceCondition pc = subparser.getPresenceCondition();
          String prefix = String.format("%s %s",
                                        ((Syntax) getNodeAt(subparser, 6)).getTokenText(),
                                        ((Syntax) getNodeAt(subparser, 5)).getTokenText());
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 4);
          String infix = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          Multiverse<OffsetofMemberDesignator> designator = (Multiverse<OffsetofMemberDesignator>) getTransformationValue(subparser, 2);
          String suffix = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          // convert to string and append tokens
          Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          Multiverse<String> prepended = typenamestr.prependScalar(prefix, DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(infix, DesugarOps.concatStrings);
          typenamestr.destruct(); prepended.destruct();

          Multiverse<String> offsetofstr = DesugarOps.offsetofToString.transform(designator);
          Multiverse<String> offsetofappended = offsetofstr.appendScalar(suffix, DesugarOps.concatStrings);
          
          todoReminder("typecheck OffsetofExpression (1)");
          // TODO: check that the expression references something in the typespec given by typename
          Multiverse<Type> type = new Multiverse<Type>(C.SIZEOF, pc);

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                appended,
                                                                offsetofappended),
                                                     type,new Multiverse<LineNumbers>(lw,pc)));
          appended.destruct(); offsetofappended.destruct();
        }
        ;

ExtensionExpression:  /** nomerge **/  // ExpressionValue
        __EXTENSION__ CastExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);
          
          Multiverse<String> extmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugarOps.concatStrings, extmv, exprmv),
                                                     exprval.type,exprval.integrateSyntax((Syntax) getNodeAt(subparser, 2))));
          extmv.destruct();
        }
        ;

AlignofExpression:  /** nomerge **/ // ExpressionValue
        Alignofkeyword LPAREN TypeName RPAREN
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          Syntax keysyn = (Syntax) getTransformationValue(subparser, 4);
          String keyword = keysyn.getTokenText();
          String lparen = getNodeAt(subparser, 3).getTokenText();
          Multiverse<Declaration> typenamemv = (Multiverse<Declaration>) getTransformationValue(subparser, 2);
          Syntax rparensyn = (Syntax)getNodeAt(subparser, 1);
          String rparen = getNodeAt(subparser, 1).getTokenText();
          LineNumbers lw = new LineNumbers(keysyn,rparensyn); 
          // go through each typespecifier and either (1) construct the
          // transformation or (2) preserve the type error.
          Multiverse<String> valuestr = new Multiverse<String>();
          Multiverse<Type> valuetype = new Multiverse<Type>();
          PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
          for (Element<Declaration> typename : typenamemv) {
            PresenceCondition combinedCond = pc.and(typename.getCondition());
            Type tbtype = typename.getData().getType();

            if (tbtype.isError()) {
              // save the set of configurations with type errors
              PresenceCondition newErrorCond = errorCond.or(combinedCond);
              errorCond.delRef(); errorCond = newErrorCond;
              newErrorCond.delRef();
            } else {
              // add the desugared string and type to the resulting
              // semantic value
              valuestr.add(String.format("%s %s %s %s", keyword, lparen, typename.getData().toString(), rparen), combinedCond);
              valuetype.add(xtc.type.C.SIZEOF, combinedCond);
            }
            combinedCond.delRef();
          }

          if (! errorCond.isFalse()) {
            valuestr.add(emitError("invalid alignof expression"), errorCond);
            valuetype.add(ErrorT.TYPE, errorCond);
          }
          assert ! valuestr.isEmpty();
          assert ! valuetype.isEmpty();
          errorCond.delRef();
          
          ExpressionValue exprval = new ExpressionValue(valuestr, valuetype,new Multiverse<LineNumbers>(lw,pc));
          
          setTransformationValue(value, exprval);
        }
        | Alignofkeyword UnaryExpression
        {
          System.err.println("ERROR: unsupported semantic action: AlignofExpression (2)");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

Alignofkeyword:  // Syntax
        __ALIGNOF__
        {
          setTransformationValue(value, (Syntax)getNodeAt(subparser, 1));
        }
        | __ALIGNOF
        {
          setTransformationValue(value, (Syntax) getNodeAt(subparser, 1));
        }
        ;

LabelAddressExpression:  /** nomerge  **/  // ADDED
        ANDAND IDENTIFIER
        {
          System.err.println("ERROR: unsupported semantic action: LabelAddressExpression");
          subparser.lookahead.setError();
          //System.exit(1);
        }
        ;

Unaryoperator:  // Syntax
        AND
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        | STAR
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        | PLUS
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        | MINUS
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        | NEGATE
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        | NOT
        {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
        ;

CastExpression:  /** passthrough, nomerge **/  // ExpressionValue
        UnaryExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | LPAREN TypeName RPAREN CastExpression
        {
          // TODO compare the expression's type against the type name
          // to rule out invalid casts.
          todoReminder("check the legality of the cast");

          PresenceCondition pc = subparser.getPresenceCondition();
          
          String prefix = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 3);
          String suffix = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          Multiverse<String> prepended = typenamestr.prependScalar(prefix, DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(suffix, DesugarOps.concatStrings);
          typenamestr.destruct(); prepended.destruct();

          Multiverse<String> transformationmv = appended.product(exprval.transformation, DesugarOps.concatStrings);
          appended.destruct();

          Multiverse<Type> typemv = DesugarOps.typenameToType.transform(typename);
	  PresenceCondition errorCond = exprval.type.getConditionOf(ErrorT.TYPE);
	  for (Element<Declaration> e : typename) {
	    if (e.getData().hasTypeError()) {
	      errorCond = errorCond.or(e.getCondition());
	    }
	  }
          typemv = typemv.filter(errorCond.not());
          typemv.add(ErrorT.TYPE, errorCond);
          setTransformationValue(value, new ExpressionValue(transformationmv, typemv, exprval.integrateSyntax((Syntax) getNodeAt(subparser, 4))));
        }
        ;



          /* PresenceCondition pc = subparser.getPresenceCondition(); */
          /* ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2); */

          /* Multiverse<String> lparenmv */
          /*   = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc); */
          /* Multiverse<String> exprmv = exprval.transformation; */
          /* Multiverse<String> rparenmv */
          /*   = new Multiverse<String>(((Syntax) getNodeAt(subparser, 1)).getTokenText(), pc); */

          /* setTransformationValue(value, */
          /*                        new ExpressionValue(productAll(DesugarOps.concatStrings, lparenmv, exprmv, rparenmv), */
          /*                                            exprval.type)); */
          /* lparenmv.destruct(); rparenmv.destruct(); */

MultiplicativeExpression:  /** passthrough, nomerge **/  // ExpressionValue
        CastExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | MultiplicativeExpression STAR CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;
	  
          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.multOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
          opmv.destruct();
        }
        | MultiplicativeExpression DIV CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;
	  if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.multOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
          opmv.destruct();
        }
        | MultiplicativeExpression MOD CastExpression
        {
          todoReminder("typecheck MultiplicativeExpression (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;
          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.modOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
          opmv.destruct();
        }
        ;

AdditiveExpression:  /** passthrough, nomerge **/  // ExpressionValue
        MultiplicativeExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | AdditiveExpression PLUS MultiplicativeExpression
        {
          todoReminder("typecheck AdditiveExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.addOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | AdditiveExpression MINUS MultiplicativeExpression
        {
          todoReminder("typecheck AdditiveExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.subOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

ShiftExpression:  /** passthrough, nomerge **/  // ExpressionValue
        AdditiveExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | ShiftExpression LS AdditiveExpression
        {
          todoReminder("typecheck ShiftExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              leftval.type.product(rightval.type, DesugarOps.shiftOp),
                                                              leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | ShiftExpression RS AdditiveExpression
        {
          todoReminder("typecheck ShiftExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              leftval.type.product(rightval.type, DesugarOps.shiftOp),
                                                              leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

RelationalExpression:  /** passthrough, nomerge **/ // ExpressionValue
        ShiftExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | RelationalExpression LT ShiftExpression
        {
          todoReminder("typecheck RelationalExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | RelationalExpression GT ShiftExpression
        {
          todoReminder("typecheck RelationalExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | RelationalExpression LE ShiftExpression
        {
          todoReminder("typecheck RelationalExpression (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | RelationalExpression GE ShiftExpression
        {
          todoReminder("typecheck RelationalExpression (5)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

EqualityExpression:  /** passthrough, nomerge **/  // ExpressionValue
        RelationalExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | EqualityExpression EQ RelationalExpression
        {
          todoReminder("typecheck EqualityExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
	    Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
	    
	    ExpressionValue ret =  new ExpressionValue(productmv,
						       productAll(DesugarOps.eqOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers));
	    setTransformationValue(value,ret); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        | EqualityExpression NE RelationalExpression
        {
          todoReminder("typecheck EqualityExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftmv.isEmpty() && !rightmv.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.eqOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

AndExpression:  /** passthrough, nomerge **/  // ExpressionValue
        EqualityExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | AndExpression AND EqualityExpression
        {
          todoReminder("typecheck AndExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.bitOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

ExclusiveOrExpression:  /** passthrough, nomerge **/  // ExpressionValue
        AndExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | ExclusiveOrExpression XOR AndExpression
        {
          todoReminder("typecheck ExclusiveOrExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType() && !leftval.isEmpty() && !rightval.isEmpty()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.bitOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

InclusiveOrExpression:  /** passthrough, nomerge **/  // ExpressionValue
        ExclusiveOrExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | InclusiveOrExpression PIPE ExclusiveOrExpression
        {
          todoReminder("typecheck InclusiveOrExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.bitOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

LogicalAndExpression:  /** passthrough, nomerge **/  // ExpressionValue
        InclusiveOrExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | LogicalAndExpression ANDAND InclusiveOrExpression
        {
          todoReminder("typecheck LogicalAndExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          
          

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            ExpressionValue e = new ExpressionValue(productmv, productAll(DesugarOps.scalarOp,
									  leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers));
            setTransformationValue(value, e);
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

LogicalORExpression:  /** passthrough, nomerge **/ // ExpressionValue
        LogicalAndExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | LogicalORExpression OROR LogicalAndExpression
        {
          todoReminder("typecheck LogicalORExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.scalarOp, leftval.type, rightval.type),leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

ConditionalExpression:  /** passthrough, nomerge **/  // ExpressionValue
        LogicalORExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | LogicalORExpression QUESTION Expression COLON
                ConditionalExpression
        {
          todoReminder("typecheck ConditionalExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue condval = getCompleteNodeExpressionValue(subparser, 5, pc);
          ExpressionValue ifval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue elseval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> condmv = condval.transformation;
          Multiverse<String> quesmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 4)).getTokenText(), pc);
          Multiverse<String> ifmv = ifval.transformation;
          Multiverse<String> colonmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> elsemv = elseval.transformation;

          if (condval.hasValidType() && ifval.hasValidType() && elseval.hasValidType()) {
            Multiverse<Type> resType = ifval.type.filter(
                                                         (condval.type.getConditionOf(ErrorT.TYPE).or(elseval.type.getConditionOf(ErrorT.TYPE))).not()
                                                         );
            resType.add(ErrorT.TYPE, condval.type.getConditionOf(ErrorT.TYPE).or(elseval.type.getConditionOf(ErrorT.TYPE)));
            // check that condval is a condition type
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         condmv,
                                                                         quesmv,
                                                                         ifmv,
                                                                         colonmv,
                                                                         elsemv),
                                                              resType,
                                                              condval.lines.product(elseval.lines, DesugarOps.combineLineNumbers)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in conditionalexpression expression"),
                                                              ErrorT.TYPE,
                                                              condval.lines.product(elseval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
          quesmv.destruct(); colonmv.destruct();
        }
        | LogicalORExpression QUESTION COLON  // ADDED gcc innomerge conditional
                ConditionalExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue condval = getCompleteNodeExpressionValue(subparser, 4, pc);
          ExpressionValue elseval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<String> condmv = condval.transformation;
          Multiverse<String> center = new Multiverse<String>("? : ",pc);
          Multiverse<String> elsemv = elseval.transformation;
          if (condval.hasValidType() && elseval.hasValidType()) {
            Multiverse<Type> resType = elseval.type.filter(condval.type.getConditionOf(ErrorT.TYPE).not());
            resType.add(ErrorT.TYPE, condval.type.getConditionOf(ErrorT.TYPE));
            // check that condval is a condition type
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         condmv,
                                                                         center,
                                                                         elsemv),
                                                              resType,
                                                              condval.lines.product(elseval.lines, DesugarOps.combineLineNumbers)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in conditionalexpression expression"),
                                                              ErrorT.TYPE,
                                                              condval.lines.product(elseval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
        }
        ;

AssignmentExpression:  /** passthrough, nomerge **/  // ExpressionValue
        ConditionalExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | UnaryExpression AssignmentOperator AssignmentExpression
        {
          PresenceCondition pc = subparser.getPresenceCondition();

          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<String> assign = rightval.transformation;
          Multiverse<String> expr = leftval.transformation;
            
          if (leftval.hasValidType() && rightval.hasValidType() &&
              !assign.isEmpty() && !expr.isEmpty()) {
            
            Multiverse<String> op = this.<String>getCompleteNodeSingleValue(subparser, 2, pc);
            
            // type-checking
            Multiverse<Type> exprtype = leftval.type;
            Multiverse<Type> assigntype = rightval.type;
            Multiverse<Type> producttype = DesugarOps.checkAssignmentType(exprtype, assigntype, op, pc, false);
            
            Multiverse<Type> typemv = producttype;
            
            // filter out configurations with type errors
            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition typesafeCond = errorCond.not();

            // carefully take the product of each combinations of the
            // left side, operator, right side to check for infeasible
            // combinations.
            Multiverse<String> valuemv;
            Multiverse<String> suffix = expr.product(op, DesugarOps.concatStrings); op.destruct();
            
            if (!suffix.isEmpty()) {
              Multiverse<String> product = suffix.product(assign, DesugarOps.concatStrings); suffix.destruct();
              if (!product.isEmpty()) {
                valuemv = product.filter(typesafeCond); product.destruct();
              } else {
                valuemv = product;
              }
            } else {
              valuemv = suffix;
            }
	    if (errorCond.isNotFalse()) {
	      if (!valuemv.isEmpty()) {
		valuemv = valuemv.filter(errorCond.not());
	      }
	      valuemv.add("invalid assignment expression", errorCond);
	    }
            errorCond.delRef(); typesafeCond.delRef();
	          setTransformationValue(value, new ExpressionValue(valuemv, typemv, leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers)));
            
          } else {  // no valid types
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in assignment expression"),
                                                              ErrorT.TYPE,
                                                              leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers),
                                                              pc));
          }
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
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        ;

Expression:  /** passthrough, nomerge **/  // ExpressionValue
        AssignmentExpression
        {
          setTransformationValue(value, this.<ExpressionValue>getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
        | Expression COMMA AssignmentExpression
        {
          // n1570, 6.5.17. left operand is a void expression; result
          // has right operand's type (and value).

          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          String comma = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

	  PresenceCondition errorC = leftval.type.getConditionOf(ErrorT.TYPE);
	  Multiverse<Type> n = rightval.type.filter(errorC.not());
	  n.add(ErrorT.TYPE,errorC);
	  
          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> appended = leftmv.appendScalar(comma, DesugarOps.concatStrings);
          Multiverse<String> rightmv = rightval.transformation;

          Multiverse<String> transformationmv = appended.product(rightmv, DesugarOps.concatStrings);
          appended.destruct();
          Multiverse<LineNumbers> lnsmv = leftval.lines.product(rightval.lines, DesugarOps.combineLineNumbers);

          setTransformationValue(value, new ExpressionValue(transformationmv, n, lnsmv));
        }
        ;

ConstantExpression: /** passthrough, nomerge **/  // ExpressionValue
        ConditionalExpression
        {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
	      ;

AttributeSpecifierListOpt: /** nomerge **/  // ADDED // Multiverse<String>
        /* empty */
        {
          todoReminder("support AttributeSpecifierListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AttributeSpecifierList
        {
          todoReminder("support AttributeSpecifierListOpt (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AttributeSpecifierList:  /** list, nomerge **/  // ADDED
        AttributeSpecifier
        {
          todoReminder("support AttributeSpecifierList (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AttributeSpecifierList AttributeSpecifier
        {
          todoReminder("support AttributeSpecifierList (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AttributeSpecifier: /** nomerge **/  // ADDED
        AttributeKeyword LPAREN LPAREN AttributeListOpt RPAREN RPAREN
        {
          Syntax keyword = ((Syntax) getNodeAt(subparser, 6).get(0));
          todoReminder("support AttributeSpecifier, replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AttributeKeyword:   // ADDED
        __ATTRIBUTE
        {
          // read token from parent
        }
        | __ATTRIBUTE__
        {
          // read token from parent
        }
        ;

AttributeListOpt:   // ADDED  // String
        /* empty */
        {
          todoReminder("support AttributeListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AttributeList
        {
          todoReminder("support AttributeListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AttributeList:  /** list, nomerge **/  // ADDED  // String
        Word AttributeExpressionOpt
        {
          String word = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();
          todoReminder("support AttributeList (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AttributeList COMMA Word AttributeExpressionOpt
        {
          String word = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();
          todoReminder("support AttributeList (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AttributeList COMMA
        {
          //attribute lists may end in a series of commas, to accomodate VA_ARGS
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AttributeExpressionOpt:   // ADDED  // String
        /* empty */
        {
          setTransformationValue(value, "");
        }
        | LPAREN RPAREN
        {
          setTransformationValue(value, String.format("%s %s",
                                                      getNodeAt(subparser, 2).getTokenText(),
                                                      getNodeAt(subparser, 1).getTokenText()));
        }
        | LPAREN ExpressionList RPAREN
        {
          // TODO: need to check type of expression list to make sure
          // it's legal and return a type error if it is.
          todoReminder("support AttributeExpressionOpt, replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

// return syntax, not a multiverse
Word:  // ADDED  // Syntax
        IDENTIFIER
        {
          // get token from parent
        }
        | AUTO
        {
          // get token from parent
        }
        | DOUBLE
        {
          // get token from parent
        }
        | INT
        {
          // get token from parent
        }
        | STRUCT
        {
          // get token from parent
        }
        | BREAK
        {
          // get token from parent
        }
        | ELSE
        {
          // get token from parent
        }
        | LONG
        {
          // get token from parent
        }
        | SWITCH
        {
          // get token from parent
        }
        | CASE
        {
          // get token from parent
        }
        | ENUM
        {
          // get token from parent
        }
        | REGISTER
        {
          // get token from parent
        }
        | TYPEDEF
        {
          // get token from parent
        }
        | CHAR
        {
          // get token from parent
        }
        | EXTERN
        {
          // get token from parent
        }
        | RETURN
        {
          // get token from parent
        }
        | UNION
        {
          // get token from parent
        }
        | CONST
        {
          // get token from parent
        }
        | FLOAT
        {
          // get token from parent
        }
        | SHORT
        {
          // get token from parent
        }
        | UNSIGNED
        {
          // get token from parent
        }
        | CONTINUE
        {
          // get token from parent
        }
        | FOR
        {
          // get token from parent
        }
        | SIGNED
        {
          // get token from parent
        }
        | VOID
        {
          // get token from parent
        }
        | DEFAULT
        {
          // get token from parent
        }
        | GOTO
        {
          // get token from parent
        }
        | SIZEOF
        {
          // get token from parent
        }
        | VOLATILE
        {
          // get token from parent
        }
        | DO
        {
          // get token from parent
        }
        | IF
        {
          // get token from parent
        }
        | STATIC
        {
          // get token from parent
        }
        | WHILE
        {
          // get token from parent
        }
        | ASMSYM
        {
          // get token from parent
        }
        | _BOOL
        {
          // get token from parent
        }
        | _COMPLEX
        {
          // get token from parent
        }
        | RESTRICT
        {
          // get token from parent
        }
        | __ALIGNOF
        {
          // get token from parent
        }
        | __ALIGNOF__
        {
          // get token from parent
        }
        | ASM
        {
          // get token from parent
        }
        | __ASM
        {
          // get token from parent
        }
        | __ASM__
        {
          // get token from parent
        }
        | __ATTRIBUTE
        {
          // get token from parent
        }
        | __ATTRIBUTE__
        {
          // get token from parent
        }
        | __BUILTIN_OFFSETOF
        {
          // get token from parent
        }
        | __BUILTIN_TYPES_COMPATIBLE_P
        {
          // get token from parent
        }
        | __BUILTIN_VA_ARG
        {
          // get token from parent
        }
        | __BUILTIN_VA_LIST
        {
          // get token from parent
        }
        | __COMPLEX__
        {
          // get token from parent
        }
        | __CONST
        {
          // get token from parent
        }
        | __CONST__
        {
          // get token from parent
        }
        | __EXTENSION__
        {
          // get token from parent
        }
        | INLINE
        {
          // get token from parent
        }
        | __INLINE
        {
          // get token from parent
        }
        | __INLINE__
        {
          // get token from parent
        }
        | __LABEL__
        {
          // get token from parent
        }
        | __RESTRICT
        {
          // get token from parent
        }
        | __RESTRICT__
        {
          // get token from parent
        }
        | __SIGNED
        {
          // get token from parent
        }
        | __SIGNED__
        {
          // get token from parent
        }
        | __THREAD
        {
          // get token from parent
        }
        | TYPEOF
        {
          // get token from parent
        }
        | __TYPEOF
        {
          // get token from parent
        }
        | __TYPEOF__
        {
          // get token from parent
        }
        | __VOLATILE
        {
          // get token from parent
        }
        | __VOLATILE__
        {
          // get token from parent
        }
        ;

// ------------------------------------------------------------------ Assembly

AssemblyDefinition:  /** nomerge **/
        AssemblyExpression SEMICOLON
        {
          todoReminder("support AssemblyDefinition (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AssemblyExpression:  /** nomerge **/
        AsmKeyword LPAREN StringLiteralList RPAREN
        {
          ExpressionValue e = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          Multiverse<String> temp = e.transformation;
          Multiverse<String> prepended = temp.prependScalar("__asm__(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(")", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          setTransformationValue(value, appended);
        }
        ;

AssemblyExpressionOpt:  /** nomerge **/
        /* empty */
        {
          todoReminder("support AssemblyExpressionOpt (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AssemblyExpression
        {
          todoReminder("support AssemblyExpressionOpt (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AssemblyStatement:   /** nomerge **/ // ADDED
        AsmKeyword LPAREN Assemblyargument RPAREN SEMICOLON
        /* gcc>=4.5 */
        {
          ExpressionValue temp = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition());
          Multiverse<String> prepended = temp.transformation.prependScalar("__asm__(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(");", DesugarOps.concatStrings);
          temp.transformation.destruct(); prepended.destruct();
          appended = appended.filter(temp.type.getConditionOf(ErrorT.TYPE).not());
          appended.add(emitError("invalid type in Assembly Argument")+";",temp.type.getConditionOf(ErrorT.TYPE));
          setTransformationValue(value, DesugarOps.StringToDSV.transform(appended));
        }
        | AsmKeyword GOTO LPAREN AssemblyGotoargument RPAREN SEMICOLON
        {
          todoReminder("support AssemblyStatement (2)");
          System.exit(0);
          Multiverse<DeclarationOrStatementValue> m = new Multiverse<DeclarationOrStatementValue>();
          m.add(new DeclarationOrStatementValue("asm2"),subparser.getPresenceCondition());
          setTransformationValue(value, m);
        }
        | AsmKeyword TypeQualifier LPAREN Assemblyargument RPAREN SEMICOLON
        {
          Multiverse<TypeSpecifier> qual = getCompleteNodeMultiverseValue(subparser, 5, subparser.getPresenceCondition());
          Multiverse<String> qualS = DesugarOps.TypeSpecifierToString.transform(qual);
          qual.destruct();
          Multiverse<String> preTemp = qualS.prependScalar("__asm__ ", DesugarOps.concatStrings);
          qualS.destruct();
          ExpressionValue temp = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition());
          
          Multiverse<String> prepended = temp.transformation.prependScalar(" (", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(");", DesugarOps.concatStrings);
          temp.transformation.destruct(); prepended.destruct();
          Multiverse<String> res = preTemp.product(appended, DesugarOps.concatStrings);
          preTemp.destruct(); appended.destruct();
          res = res.filter(temp.type.getConditionOf(ErrorT.TYPE).not());
          res.add(emitError("invalid type in Assembly Argument")+";",temp.type.getConditionOf(ErrorT.TYPE));
          setTransformationValue(value, DesugarOps.StringToDSV.transform(res));
        }
        ;

Assemblyargument:  /** nomerge **/  // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON Assemblyclobbers
        {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,7,subparser.getPresenceCondition()).transformation;
          ExpressionValue sec = getCompleteNodeExpressionValue(subparser,5,subparser.getPresenceCondition());
          ExpressionValue third = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition());
          Multiverse<String> fourth = (Multiverse<String>)getTransformationValue(subparser,1);
          if (sec.isEmpty() || third.isEmpty() || first.isEmpty() || fourth.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(
                                                              new Multiverse<String>("",subparser.getPresenceCondition()),
                                                              new Multiverse<Type>(ErrorT.TYPE,subparser.getPresenceCondition())
                                                              ));
          
          } else {
            Multiverse<String> prep2 = sec.transformation.prependScalar(":", DesugarOps.concatStrings);
            Multiverse<String> prep3 = third.transformation.prependScalar(":", DesugarOps.concatStrings);
            Multiverse<String> prep4 = fourth.prependScalar(":", DesugarOps.concatStrings);
            fourth.destruct();
            Multiverse<String> last = prep3.product(prep4, DesugarOps.concatStrings);
            prep3.destruct(); prep4.destruct();
            Multiverse<String> later = prep2.product(last, DesugarOps.concatStrings);
            prep2.destruct(); last.destruct();
            Multiverse<String> res = first.product(later, DesugarOps.concatStrings);
            first.destruct(); later.destruct();
            Multiverse<Type> ty = sec.type.product(third.type,DesugarOps.propTypeError);
            setTransformationValue(value, new ExpressionValue(res,ty));
          }
        }
        | StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt
        {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,5,subparser.getPresenceCondition()).transformation;
          ExpressionValue sec = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition());
          ExpressionValue third = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition());
          if (sec.isEmpty() || third.isEmpty() || first.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(
                                                              new Multiverse<String>("",subparser.getPresenceCondition()),
                                                              new Multiverse<Type>(ErrorT.TYPE,subparser.getPresenceCondition())
                                                              ));
          } else {
            Multiverse<String> prep2 = sec.transformation.prependScalar(":", DesugarOps.concatStrings);
            sec.transformation.destruct();
            Multiverse<String> prep3 = third.transformation.prependScalar(":", DesugarOps.concatStrings);
            third.transformation.destruct();
            Multiverse<String> later = prep2.product(prep3, DesugarOps.concatStrings);
            Multiverse<Type> ty = sec.type.product(third.type,DesugarOps.propTypeError);
            Multiverse<String> res = first.product(later, DesugarOps.concatStrings);
            setTransformationValue(value, new ExpressionValue(res,ty));
          }
        }
        | StringLiteralList COLON AssemblyoperandsOpt
        {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition()).transformation;
          ExpressionValue sec = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition());
          if (sec.isEmpty() || first.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(
                                                              new Multiverse<String>("",subparser.getPresenceCondition()),
                                                              new Multiverse<Type>(ErrorT.TYPE,subparser.getPresenceCondition())
                                                              ));
            
          } else {
            Multiverse<String> prep = sec.transformation.prependScalar(":", DesugarOps.concatStrings);
            prep = first.product(prep,DesugarOps.concatStrings);
            setTransformationValue(value, new ExpressionValue(prep,sec.type));
          }
        }
        | StringLiteralList
        {
          ExpressionValue first = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition());
          if (first.isEmpty()) {
            setTransformationValue(value, new ExpressionValue(
                                                              new Multiverse<String>("",subparser.getPresenceCondition()),
                                                              new Multiverse<Type>(ErrorT.TYPE,subparser.getPresenceCondition())
                                                              ));
            
          } else {
            setTransformationValue(value,first);
          }
          
        }
        ;

AssemblyoperandsOpt:  /** nomerge **/  // ADDED
        /* empty */
        {
          setTransformationValue(value, new ExpressionValue(new Multiverse<String>("", subparser.getPresenceCondition()),new Multiverse<Type>(new IntegerT(NumberT.Kind.INT),subparser.getPresenceCondition())));
        }
        | Assemblyoperands
        {
          setTransformationValue(value, getTransformationValue(subparser,1));
        }
        ;

Assemblyoperands:  /** list, nomerge **/  // ADDED
        Assemblyoperand
        {
          setTransformationValue(value, getTransformationValue(subparser,1));
        }
        | Assemblyoperands COMMA Assemblyoperand
        {
          ExpressionValue  prev = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition());
          ExpressionValue  cur = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition());
          Multiverse<String> prep = cur.transformation.prependScalar(",", DesugarOps.concatStrings);
          if (!prev.type.isEmpty() && !cur.type.isEmpty() && !cur.transformation.isEmpty() && !prev.transformation.isEmpty()) {
            Multiverse<Type> prept;
            prept = prev.type.product(cur.type,DesugarOps.propTypeError);
            setTransformationValue(value, new ExpressionValue(prev.transformation.product(prep, DesugarOps.concatStrings),prept));
          } else {
            setTransformationValue(value,
                                   new ExpressionValue(new Multiverse<String>("",subparser.getPresenceCondition()),
                                                       new Multiverse<Type>(ErrorT.TYPE,subparser.getPresenceCondition())));
          }
        }
        ;

Assemblyoperand:  /** nomerge **/  // ADDED
        StringLiteralList LPAREN Expression RPAREN
        {
          ExpressionValue str = getCompleteNodeExpressionValue(subparser,4,subparser.getPresenceCondition());
          ExpressionValue expr = getCompleteNodeExpressionValue(subparser,2,subparser.getPresenceCondition());
          Multiverse<String> temp = expr.transformation;
          Multiverse<String> prepended = temp.prependScalar("(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(")", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          
          setTransformationValue(value, new ExpressionValue(str.transformation.product(appended, DesugarOps.concatStrings),expr.type));
        }
        | LBRACK Word RBRACK StringLiteralList LPAREN Expression RPAREN
        {
          //String word = ((Syntax) getNodeAt(subparser, 6).get(0)).getTokenText();
          todoReminder("Assembly operand 2, add Word");
          ExpressionValue str = getCompleteNodeExpressionValue(subparser,4,subparser.getPresenceCondition());
          ExpressionValue expr = getCompleteNodeExpressionValue(subparser,2,subparser.getPresenceCondition());
          Multiverse<String> temp = expr.transformation;
          Multiverse<String> prepended = temp.prependScalar("(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(")", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          
          setTransformationValue(value, new ExpressionValue(str.transformation.product(appended, DesugarOps.concatStrings),expr.type));
        }
        ;

AssemblyclobbersOpt:  /** nomerge **/ // ADDED
        /* empty */
        {
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | Assemblyclobbers
        {
          setTransformationValue(value, (Multiverse<String>)getTransformationValue(subparser,1));
        }
        ;

Assemblyclobbers:  /** nomerge **/  // ADDED
        StringLiteralList
        {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition()).transformation;
          setTransformationValue(value, first);
        }
        | Assemblyclobbers COMMA StringLiteralList
        {
          Multiverse<String> first = (Multiverse<String>)getTransformationValue(subparser,3);
          Multiverse<String> second = getCompleteNodeExpressionValue(subparser,1,subparser.getPresenceCondition()).transformation;
          Multiverse<String> prep2 = second.prependScalar(",", DesugarOps.concatStrings);
          second.destruct();
          Multiverse<String> res = first.product(prep2, DesugarOps.concatStrings);
          first.destruct(); prep2.destruct();
          setTransformationValue(value, res);
        }
        ;

AssemblyGotoargument:  /** nomerge **/ // ADDED
        StringLiteralList COLON AssemblyoperandsOpt COLON AssemblyoperandsOpt COLON AssemblyclobbersOpt COLON AssemblyJumpLabels
        {
          todoReminder("support AssemblyGotoargument (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

AssemblyJumpLabels:  /** nomerge **/ // ADDED
        Identifier
        {
          todoReminder("support AssemblyJumpLabels (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        | AssemblyJumpLabels COMMA Identifier
        {
          todoReminder("support AssemblyJumpLabels (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
        ;

// No actions necessary, since the token will be retrieved by the parent.
AsmKeyword:   // ADDED
        ASM
        | __ASM
        | __ASM__
        ;

%%

boolean wrotePrologue = false;

static boolean keepMem = false;
static String memNames[] = {"malloc", "calloc", "free", "fopen", "fclose", "rand", "memcpy", "memset", "strdup", "strcmp"};

public static void keepMemoryNames(boolean f) {
  keepMem = f;
}

// TUTORIAL: this section of the grammar gets copied into the
// resulting parser, specifically the CActions.java class

/***************************************************************************
 **** Semantic actions
 ***************************************************************************/
 protected List<Multiverse<String>> declAddSemi(List<DeclaringListValue> declaringlistvalues,
                                               String semi,
                                               PresenceCondition pc) {
  List<Multiverse<String>> toret = new LinkedList<Multiverse<String>>();
  for (DeclaringListValue d : declaringlistvalues ) {
    toret.add(d.desugared.appendScalar(semi,DesugarOps.concatStrings));
  }
  return toret;
 }

 protected void setupInitials(List<DeclaringListValue> declList, DeclaringListValue decl, Multiverse<Initializer> initializermv, PresenceCondition pc, CContext scope){
   if (initializermv.size() == 1 && initializermv.get(0).getData().isEmpty()) {
     declList.add(decl);
   } else {
     for (Element<Declarator> declarator : decl.declarator) {
       String originalName = declarator.getData().getName();
       Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, declarator.getCondition());
       for (Element<SymbolTable.Entry<Type>> entry : entries) {
         if (!entry.getData().isDeclared()) {
           continue;
         }
         Type t = entry.getData().getValue().toVariable().getType();
         if (initializermv.size() == 1 && ! initializermv.get(0).getData().hasList()) {
           declList.add(checkInitializers(decl.filter(entry.getCondition()),initializermv,entry.getCondition(),scope,false));
         } else {
           declList.add(decl.filter(entry.getCondition()));
           for (Element<Initializer> ei : initializermv) {
             if (!ei.getData().isEmpty()) {
               declList.add(checkInitializers(decl.filter(entry.getCondition()),initializermv.filter(ei.getCondition()),ei.getCondition(),scope,true));
             }
           }
         }
       }
     }
   }
 }

 protected DeclaringListValue checkInitializers(DeclaringListValue decl, Multiverse<Initializer> initializermv, PresenceCondition pc, CContext scope, boolean splitMainInit) {
   Multiverse<String> initStr;
   if (splitMainInit) {
     initStr = new Multiverse<String>("if (" + condToCVar(pc) + ") {\n" ,pc);
   } else {
     initStr = new Multiverse<String>("",pc);
   }
  for (Element<Initializer> initializer : initializermv) {
    if (initializer.getData().isEmpty()) {
      continue;
    }
    for (Element<Declarator> declarator : decl.declarator) {
      PresenceCondition combinedCond = initializer.getCondition().and(declarator.getCondition()).and(pc);
      String originalName = declarator.getData().getName();
      if (!initializer.getData().hasValidType()) {
        scope.putError(originalName,combinedCond);
        continue;
      }
      for (Element<TypeSpecifier> typespecifier : decl.typespecifier) {
        PresenceCondition finalcond = typespecifier.getCondition().and(combinedCond);
        if (finalcond.isFalse()) {
          continue;
        }
        Declaration originalDeclaration = new Declaration(typespecifier.getData(), declarator.getData());
        Type declarationType = originalDeclaration.getType();
        
        StringBuilder entrysb = new StringBuilder();  // the desugared output
        Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, finalcond);
        for (Element<SymbolTable.Entry<Type>> entry : entries) {
          String renaming = entry.getData().getValue().toVariable().getName();
          if (initializer.getData().hasList() && !scope.isGlobal() &&
              (!declarationType.hasAttribute(Constants.ATT_CONSTANT) && !declarationType.hasConstant())) {
            Type tempT = declarationType;
            while (tempT.isWrapped()) {
              tempT = ((WrappedT)tempT).getType();
            }
            if (tempT.isStruct() || tempT.isUnion()){
              entrysb.append("{\n" + initStruct(renaming, (StructOrUnionT)tempT, initializer.getData(), scope, finalcond) + "}");
            }
            if (tempT.isArray()){
              entrysb.append("{\n" + initArray(renaming, (ArrayT)tempT, initializer.getData(), scope, finalcond) + "}");
            }
          } else {
            boolean compatibleTypes = true;
            //check for initializer list
            if (initializer.getData().hasList()) {
              compatibleTypes = !initializer.getData().hasNonConst();
            }
            if (compatibleTypes) {
              String toAddStr = "";
              if (initializer.getData().hasList()) {
                Multiverse<String> mvs = initializer.getData().renamedList(new Multiverse<Type>(declarationType.resolve(),finalcond),finalcond,scope);
                for (Element<String> evs : mvs) {
                  if (evs.getData() != "") {
                    if (splitMainInit) {
                      toAddStr += renaming;
                    }
                    toAddStr += (evs.getData());
                  } else {
                    scope.putError(originalName, entry.getCondition());
                    recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                    if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                      externalLinkage.putError(originalName, entry.getCondition());
                    } else if (!scope.isGlobal()) {
                      toAddStr += ("if (");
                      toAddStr += (condToCVar(entry.getCondition()));
                      toAddStr += (") {\n");
                      toAddStr += (emitError(String.format("improper designator value: %s", originalName)));
                      toAddStr += (";\n");
                      toAddStr += ("}\n");
                    }
                  }
                }
              } else {
                if (splitMainInit) {
                  toAddStr += renaming;
                }
                toAddStr += (initializer.getData().toString());
              }
              if ((declarationType.hasAttribute(Constants.ATT_CONSTANT) || declarationType.hasConstant()) &&
                  scope.isGlobal()) {
              } else {
                entrysb.append(toAddStr + ";");
              }
            } else {
              scope.putError(originalName, entry.getCondition());
              recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
              if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                externalLinkage.putError(originalName, entry.getCondition());
              } else if (!scope.isGlobal()) {
                entrysb.append("if (");
                entrysb.append(condToCVar(entry.getCondition()));
                entrysb.append(") {\n");
                entrysb.append(emitError(String.format("non const value in constant list or struct: %s",
                                                       originalName)));
                entrysb.append(";\n");
                entrysb.append("}\n");
              }
            } 
          }
          Multiverse<String> toApply = new Multiverse<String>();
          toApply.add(entrysb.toString(),finalcond);
          toApply.add("",finalcond.not());
          initStr = initStr.product(toApply,DesugarOps.concatStrings);
          toApply.destruct();
        }
      }
    }
  }
  if (splitMainInit) {
    initStr = initStr.product(new Multiverse<String>("}",pc), DesugarOps.concatStrings);
    return new DeclaringListValue(decl.typespecifier, decl.declarator, initializermv, initStr);
  }
  return new DeclaringListValue(decl.typespecifier, decl.declarator, initializermv, decl.desugared.product(initStr,DesugarOps.concatStrings));
 }        

protected List<Multiverse<String>> declarationAction(List<DeclaringListValue> declaringlistvalues,
                                                     String semi,
                                                     PresenceCondition pc,
                                                     CContext scope) {
  /*
   * to desugar declarations, we need to iterate over all
   * combinations of (1) declarators in the declaring list,
   * (2) the type multiverse, (3) the declarator multiverse,
   * and (4) the initializer multiverse.  TODO: also add the
   * assembly and attribute contents, although this is not
   * necessary for source-level analysis.
   */
  todoReminder("typecheck initializers");
  StringBuilder valuesb = new StringBuilder();  // the desugared output
  List<Multiverse<String>> retmv = new LinkedList<Multiverse<String>>();
  
  // loop over each element of the declaration list
  for (DeclaringListValue declaringlistvalue : declaringlistvalues) {
    // unpack type specifier, declarators, and initializers from the transformation value
    Multiverse<TypeSpecifier> typespecifiermv = declaringlistvalue.typespecifier;
    Multiverse<Declarator> declaratormv = declaringlistvalue.declarator;
    Multiverse<Initializer> initializermv = declaringlistvalue.initializer;
    Multiverse<String> valuemv = new Multiverse<String>();
    valuemv.add("",pc);
    // TODO: use typespecifier/declarator to reclassify the
    // tokens as typedef/ident in parsing context
    if (!declaringlistvalue.isEmpty()) {
      for (Element<TypeSpecifier> typespecifier : typespecifiermv) {
        PresenceCondition typespecifierCond = pc.and(typespecifier.getCondition());
        if (typespecifierCond.isNotFalse()) {
          for (Element<Initializer> initializer : initializermv) {
            // TODO: optimization opportunity, share multiple
            // initialiers with one renaming (harder for globals)
            PresenceCondition initializerCond = typespecifierCond.and(initializer.getCondition());
            if (initializerCond.isNotFalse()) {
              for (Element<Declarator> declarator : declaratormv) {
                PresenceCondition combinedCond = initializerCond.and(declarator.getCondition());
                if (combinedCond.isNotFalse()) {
                
                  String originalName = declarator.getData().getName();

                  // get xtc type from type and declarator
                  Declaration tempD = new Declaration(typespecifier.getData(), declarator.getData());
                  if (typespecifier.getData().getType().isError()
                      || ! initializer.getData().hasValidType()
                      || tempD.hasTypeError()) {
                    // if type is invalid, put an error entry, emit a call
                    // to the type error function
                    scope.putError(originalName, combinedCond);
                    if (scope.isGlobal()) {
                      recordInvalidGlobalDeclaration(originalName, combinedCond);
                    } else {
                      valuesb.append("if (");
                      valuemv = appendStringToMV(valuemv,"if (",combinedCond);
                      String tempC = condToCVar(combinedCond); 
                      valuesb.append(tempC);
                      valuemv = appendStringToMV(valuemv,tempC,combinedCond);
                      valuesb.append(") {\n");
                      valuemv = appendStringToMV(valuemv,") {\n",combinedCond);
                      valuesb.append(emitError(String.format("invalid declaration of %s under this presence condition",
                                                             originalName)));
                      valuemv = appendStringToMV(valuemv,emitError(String.format("invalid declaration of %s under this presence condition",
                                                                                 originalName)),combinedCond);
                      valuesb.append(";\n");
                      valuemv = appendStringToMV(valuemv,";\n",combinedCond);
                      valuesb.append("}\n");
                      valuemv = appendStringToMV(valuemv,"}\n",combinedCond);
                    
                    }
                  } else {
                    // otherwise loop over each existing entry check for
                    // type errors or add a new declaration
                    Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, combinedCond);
                    for (Element<SymbolTable.Entry<Type>> entry : entries) {
                      String renaming = freshCId(originalName);
                      Declarator renamedDeclarator = declarator.getData().rename(renaming);
                      Declaration renamedDeclaration = new Declaration(typespecifier.getData(),
                                                                       renamedDeclarator);
                      Declaration originalDeclaration = new Declaration(typespecifier.getData(), declarator.getData());

                      StringBuilder entrysb = new StringBuilder();

                      Type declarationType = renamedDeclaration.getType();
                      Type type;
                      //System.err.println("has typedef:" + renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF));
                      if (renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF)) {
                        type = new AliasT(renaming, declarationType);
                      } else if (declarationType.isFunction()) {
                        type = new NamedFunctionT(declarationType.toFunction().getResult(),
                                                  renaming,
                                                  declarationType.toFunction().getParameters(),
                                                  declarationType.toFunction().isVarArgs());
                      } else {
                        if (scope.isGlobal()) {
                          type = VariableT.newGlobal(declarationType, renaming);
                        } else {
                          type = VariableT.newLocal(declarationType, renaming);
                        }
                      }
                      assert null != type;

                      // make all renamed declarations static until project-wide, configuration-aware linking is possible
                      String desugaredDeclaration;
                      // disabling the thunks for now, pending
                      // configuration-aware linking support
                      if (false && type instanceof NamedFunctionT && hasExternalLinkage(typespecifier.getData())) {  // is extern
                        todoReminder("account for void or abstract declarators in linker thunk functions");
                        StringBuilder contents = new StringBuilder();
                        contents.append(originalName);
                        contents.append("(");
                        String delim = "";
                        todoReminder("do type-checking of extern function thunks");
                        for (Type parmtype : ((NamedFunctionT) type).toFunctionT().getParameters()) {
                          // function definitions must have named parameters, so
                          // the parameter types should be wrapped in a
                          // variablet type.
                          assert parmtype.isVariable() && parmtype.toVariable().hasName();
                          contents.append(delim);
                          contents.append(parmtype.toVariable().getName());
                          delim = ", ";
                        }
                        contents.append(")");
                        contents.append("; /* call external thunk */\n");
                        String staticPrototype = makeStaticDeclaration(typespecifier.getData(), renamedDeclarator);
                        // replace the extern function declaration with a static, renamed function
                        desugaredDeclaration = String.format("%s ;\n", staticPrototype);
                        // define that function to call the originally-named extern function
                        externFunctionThunks.append(String.format("%s {\n%s}\n", staticPrototype, contents.toString()));
                        assert 0 == initializer.getData().toString().length();  // extern function declarations should not have an initializer
                      } else {
                        desugaredDeclaration = renamedDeclaration.toString();
                      }
                      assert null != desugaredDeclaration;
                      if (entry.getData().isError()) {
                        // ERROR entry
                        System.err.println(String.format("INFO: \"%s\" is being redeclared in an existing invalid declaration", originalName));

                      } else if (entry.getData().isUndeclared()) {
                        // UNDECLARED entry
                        // update the symbol table for this presence condition

                        // the renamed function is static to enable linking the original function name
                        if (scope.isGlobal() && Constants.ATT_STORAGE_AUTO == typespecifier.getData().getStorageClass()) {
                          scope.putError(originalName, entry.getCondition());
                        } else {

                          scope.put(originalName, type, entry.getCondition());

                          if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                            externalLinkage.put(originalName, originalDeclaration, entry.getCondition());
                          }
                          /* entrysb.append(renamedDeclaration.toString()); */
                          if (initializer.getData().hasList() && !scope.isGlobal() &&
                              (!declarationType.hasAttribute(Constants.ATT_CONSTANT) && !declarationType.hasConstant())) {
                            Type tempT = declarationType;
                            while (tempT.isWrapped()) {
                              tempT = ((WrappedT)tempT).getType();
                            }
                            if (tempT.isStruct() || tempT.isUnion()){
                              entrysb.append(desugaredDeclaration);
                              entrysb.append(semi + "\n");  // semi-colon
                              entrysb.append("{\n" + initStruct(renaming, (StructOrUnionT)tempT, initializer.getData(), scope, combinedCond) + "}");
                              recordRenaming(renaming, originalName);
                            }
                            if (tempT.isArray()){
                              if (((ArrayT)tempT).hasLength()) {
                                entrysb.append(desugaredDeclaration);
                              } else {
                                System.err.println("no len assigned");
                                //if  the length is implcit, we need to manually assign a value
                                int siz = trueInitSize(initializer.getData());
                                ((ArrayT)tempT).setLength(siz);
                                entrysb.append(renamedDeclaration.toString(siz));
                              }
                              entrysb.append(semi + "\n");  // semi-colon
                              entrysb.append("{\n" + initArray(renaming, (ArrayT)tempT, initializer.getData(), scope, combinedCond) + "}");
                              recordRenaming(renaming, originalName);
                            }
                          } else {
                            boolean compatibleTypes = true;
                            //check for initializer list
                            if (initializer.getData().hasList()) {
                              compatibleTypes = !initializer.getData().hasNonConst();
                            }
                            if (compatibleTypes) {
                              String toAddStr = "";
                              if (initializer.getData().hasList()) {
                                Multiverse<String> mvs = initializer.getData().renamedList(new Multiverse<Type>(declarationType.resolve(),combinedCond),combinedCond,scope);
                                for (Element<String> evs : mvs) {
                                  if (evs.getData() != "") {
                                    toAddStr += desugaredDeclaration;
                                    toAddStr += (evs.getData());
                                    toAddStr += (semi);  // semi-colon
                                    recordRenaming(renaming, originalName);
                                  } else {
                                    scope.putError(originalName, entry.getCondition());
                                    recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                                    if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                                      externalLinkage.putError(originalName, entry.getCondition());
                                    } else if (!scope.isGlobal()) {
                                      toAddStr += ("if (");
                                      toAddStr += (condToCVar(entry.getCondition()));
                                      toAddStr += (") {\n");
                                      toAddStr += (emitError(String.format("improper designator value: %s", originalName)));
                                      toAddStr += (";\n");
                                      toAddStr += ("}\n");
                                    }
                                  }
                                }
                              } else {
                                toAddStr += desugaredDeclaration;
                                toAddStr += (initializer.getData().toString());
                                toAddStr += (semi);  // semi-colon
                                recordRenaming(renaming, originalName);
                              }
                              if ((declarationType.hasAttribute(Constants.ATT_CONSTANT) || declarationType.hasConstant()) &&
                                  scope.isGlobal()) {
                                scope.addDeclaration(toAddStr+"\n");
                              } else {
                                entrysb.append(toAddStr);
                              }
                            } else {
                              scope.putError(originalName, entry.getCondition());
                              recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                              if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                                externalLinkage.putError(originalName, entry.getCondition());
                              } else if (!scope.isGlobal()) {
                                entrysb.append("if (");
                                entrysb.append(condToCVar(entry.getCondition()));
                                entrysb.append(") {\n");
                                entrysb.append(emitError(String.format("non const value in constant list or struct: %s",
                                                                       originalName)));
                                entrysb.append(";\n");
                                entrysb.append("}\n");
                              }
                            }
                          }
                        }
                      } else {  // already declared entries
                        if (! scope.isGlobal()) {
                          // not allowed to redeclare local symbols at all
                          scope.putError(originalName, entry.getCondition());
                          entrysb.append("if (");
                          entrysb.append(condToCVar(entry.getCondition()));
                          entrysb.append(") {\n");
                          entrysb.append(emitError(String.format("redeclaration of local symbol: %s",
                                                                 originalName)));
                          entrysb.append(";\n");
                          entrysb.append("}\n");
                        } else {  // global scope
                          // declarations only set VariableT or AliasT
                          boolean sameTypeKind
                            = entry.getData().getValue().isVariable() && type.isVariable()
                            ||  entry.getData().getValue().isAlias() && type.isAlias()
                            ||  entry.getData().getValue().isNamedFunction() && type.isNamedFunction();

                          // check compatibility of types
                          if (sameTypeKind) {
                            boolean compatibleTypes = false;
                            if (type.isVariable()) {
                              compatibleTypes = cOps.equal(entry.getData().getValue().toVariable().getType(),
                                                           type.toVariable().getType());
                            } else if (type.isAlias()) {
                              compatibleTypes = cOps.equal(entry.getData().getValue().toAlias().getType(),
                                                           type.toAlias().getType());
                            } else if (type.isNamedFunction()) {
                              compatibleTypes = cOps.equal(entry.getData().getValue(),
                                                           type.toFunction());

                            } else {
                              throw new AssertionError("should not be possible given sameTypeKind");
                            }

                            if (! compatibleTypes) {
                              // not allowed to redeclare globals to a different type
                              scope.putError(originalName, entry.getCondition());
                              recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                              if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                                externalLinkage.putError(originalName, entry.getCondition());
                              }
                            } else {
                              // emit the same declaration, since it's legal to redeclare globals to a compatible type
                              /* entrysb.append(renamedDeclaration.toString()); */
                              entrysb.append(desugaredDeclaration);
                              entrysb.append(initializer.getData().toString());
                              entrysb.append(semi);  // semi-colon
                              System.err.println(String.format("INFO: \"%s\" is being redeclared in global scope to compatible type", originalName));
                            }

                          } else { // not the same kind of type
                            scope.putError(originalName, entry.getCondition());
                            System.err.println(String.format("INFO: attempted to redeclare global to a different kind of type: %s", originalName));
                            recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                            if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                              externalLinkage.putError(originalName, entry.getCondition());
                            }
                          } // end check for variable type
                        } // end check global/local scope
                      } // end entry kind

                      if (renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF)) {
                        // typedefs are moved to the top of the scope
                        // to support forward references of structs
                        scope.addDeclaration(entrysb.toString());
                        valuesb.append("// typedef moved to top of scope\n");
                        valuemv = appendStringToMV(valuemv,"// typedef moved to top of scope\n",combinedCond);
                      } else {
                        // not a typedef, so add it to regular output
                        valuesb.append(entrysb.toString());
                        valuemv = appendStringToMV(valuemv,entrysb.toString(),combinedCond);
                      }
                    } // end loop over symtab entries
                    entries.destruct();
                  }
                } // end check for false combinedCond
                combinedCond.delRef();
              } // end loop over declarators
            } // end check for false initializerCond
            initializerCond.delRef();
          } // end loop over initializers
        } // end check for false typespecifierCond
        typespecifierCond.delRef();
      } // end loop over typespecifiers
      // TODO: these destructs causes nullpointer errors due to
      // the sharing of semantic values.  not destructing will
      // cause memory leak
      /* typespecifiermv.destruct(); */
      /* declaratormv.destruct(); */
      /* initializermv.destruct(); */
      retmv.add(valuemv);
    } //declaringlist is not empty
  } // end loop over declaringlistvalues
  return retmv;
}

protected Multiverse<String> declarationListAction(Multiverse<TypeSpecifier> typespecifiermv,
                                                         Multiverse<Declarator> declaratormv,
                                                         PresenceCondition pc,
                                                   CContext scope) {
  
  StringBuilder valuesb = new StringBuilder();  // the desugared output
  Multiverse<String> valuemv = new Multiverse<String>();
  
  valuemv.add("",pc);
  // TODO: use typespecifier/declarator to reclassify the
  // tokens as typedef/ident in parsing context
  for (Element<TypeSpecifier> typespecifier : typespecifiermv) {
    PresenceCondition typespecifierCond = pc.and(typespecifier.getCondition());
    for (Element<Declarator> declarator : declaratormv) {
      PresenceCondition combinedCond = typespecifierCond.and(declarator.getCondition());
      if (combinedCond.isNotFalse()) {
                
        String originalName = declarator.getData().getName();
        // get xtc type from type and declarator
        Declaration tempD = new Declaration(typespecifier.getData(), declarator.getData());
        if (typespecifier.getData().getType().isError()
            || tempD.hasTypeError()
            || (!scope.isGlobal() && new Declaration(typespecifier.getData(), declarator.getData()).isNonPointerForwardRef())
            ) {
          // if type is invalid, put an error entry, emit a call
          // to the type error function
          scope.putError(originalName, combinedCond);
          if (scope.isGlobal()) {
            recordInvalidGlobalDeclaration(originalName, combinedCond);
          } else {
            valuesb.append("if (");
            valuemv = appendStringToMV(valuemv,"if (",combinedCond);
            String tempC = condToCVar(combinedCond); 
            valuesb.append(tempC);
            valuemv = appendStringToMV(valuemv,tempC,combinedCond);
            valuesb.append(") {\n");
            valuemv = appendStringToMV(valuemv,") {\n",combinedCond);
            valuesb.append(emitError(String.format("invalid declaration of %s under this presence condition",
                                                   originalName)));
            valuemv = appendStringToMV(valuemv,emitError(String.format("invalid declaration of %s under this presence condition",
                                                                       originalName)),combinedCond);
            valuesb.append(";\n");
            valuemv = appendStringToMV(valuemv,";\n",combinedCond);
            valuesb.append("}\n");
            valuemv = appendStringToMV(valuemv,"}\n",combinedCond);
            
          }
        } else {
          // otherwise loop over each existing entry check for
          // type errors or add a new declaration
          Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, combinedCond);
          for (Element<SymbolTable.Entry<Type>> entry : entries) {
            String renaming = freshCId(originalName);
            Declarator renamedDeclarator = declarator.getData().rename(renaming);
            Declaration renamedDeclaration = new Declaration(typespecifier.getData(),
                                                             renamedDeclarator);
            Declaration originalDeclaration = new Declaration(typespecifier.getData(), declarator.getData());

            StringBuilder entrysb = new StringBuilder();

            Type declarationType = renamedDeclaration.getType();
            Type type;
            //System.err.println("has typedef:" + renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF));
            if (renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF)) {
              type = new AliasT(renaming, declarationType);
            } else if (declarationType.isFunction()) {
              type = new NamedFunctionT(declarationType.toFunction().getResult(),
                                        renaming,
                                        declarationType.toFunction().getParameters(),
                                        declarationType.toFunction().isVarArgs());
            } else {
              if (scope.isGlobal()) {
                type = VariableT.newGlobal(declarationType, renaming);
              } else {
                type = VariableT.newLocal(declarationType, renaming);
              }
            }
            
            // make all renamed declarations static until project-wide, configuration-aware linking is possible
            String desugaredDeclaration;
            // disabling the thunks for now, pending
            // configuration-aware linking support
            desugaredDeclaration = renamedDeclaration.toString();
            if (entry.getData().isError()) {
              // ERROR entry
              System.err.println(String.format("INFO: \"%s\" is being redeclared in an existing invalid declaration", originalName));

            } else if (entry.getData().isUndeclared()) {
              // UNDECLARED entry
              // update the symbol table for this presence condition

              // the renamed function is static to enable linking the original function name
              if (scope.isGlobal() && Constants.ATT_STORAGE_AUTO ==
                  typespecifier.getData().getStorageClass()) {
                scope.putError(originalName, entry.getCondition());
              } else {
                
                scope.put(originalName, type, entry.getCondition());

                if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                  externalLinkage.put(originalName, originalDeclaration, entry.getCondition());
                }
                String toAddStr = "";
                
                toAddStr += desugaredDeclaration;
                recordRenaming(renaming, originalName);
                if ((declarationType.hasAttribute(Constants.ATT_CONSTANT) || declarationType.hasConstant()) &&
                    scope.isGlobal()) {
                  scope.addDeclaration(toAddStr+";\n");
                } else {
                  entrysb.append(toAddStr);
                }
              }    
            } else {  // already declared entries
              if (! scope.isGlobal()) {
                // not allowed to redeclare local symbols at all
                scope.putError(originalName, entry.getCondition());
                entrysb.append("if (");
                entrysb.append(condToCVar(entry.getCondition()));
                entrysb.append(") {\n");
                entrysb.append(emitError(String.format("redeclaration of local symbol: %s",
                                                       originalName)));
                entrysb.append(";\n");
                entrysb.append("}\n");
              } else {  // global scope
                        
                // declarations only set VariableT or AliasT
                boolean sameTypeKind
                  = entry.getData().getValue().isVariable() && type.isVariable()
                  ||  entry.getData().getValue().isAlias() && type.isAlias();

                // check compatibility of types
                if (sameTypeKind) {
                  boolean compatibleTypes = false;
                  if (type.isVariable()) {
                    compatibleTypes = cOps.equal(entry.getData().getValue().toVariable().getType(),
                                                 type.toVariable().getType());
                  } else if (type.isAlias()) {
                    compatibleTypes = cOps.equal(entry.getData().getValue().toAlias().getType(),
                                                 type.toAlias().getType());
                  } else {
                    throw new AssertionError("should not be possible given sameTypeKind");
                  }

                  if (! compatibleTypes) {
                    // not allowed to redeclare globals to a different type
                    scope.putError(originalName, entry.getCondition());
                    recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                    if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                      externalLinkage.putError(originalName, entry.getCondition());
                    }
                  } else {
                    // emit the same declaration, since it's legal to redeclare globals to a compatible type
                    /* entrysb.append(renamedDeclaration.toString()); */
                    entrysb.append(desugaredDeclaration);
                    System.err.println(String.format("INFO: \"%s\" is being redeclared in global scope to compatible type", originalName));
                  }

                } else { // not the same kind of type
                  scope.putError(originalName, entry.getCondition());
                  System.err.println(String.format("INFO: attempted to redeclare global to a different kind of type: %s", originalName));
                  recordInvalidGlobalRedeclaration(originalName, entry.getCondition());
                  if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                    externalLinkage.putError(originalName, entry.getCondition());
                  }
                } // end check for variable type
              } // end check global/local scope
            } // end entry kind

            if (renamedDeclaration.typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF)) {
              // typedefs are moved to the top of the scope
              // to support forward references of structs
              scope.addDeclaration(entrysb.toString() + ";");
              valuesb.append("// typedef moved to top of scope\n");
              valuemv = appendStringToMV(valuemv,"// typedef moved to top of scope\n",combinedCond);
            } else {
              // not a typedef, so add it to regular output
              valuesb.append(entrysb.toString());
              valuemv = appendStringToMV(valuemv,entrysb.toString(),combinedCond);
            }
          } // end loop over symtab entries
          entries.destruct();
        }
      } // end check for false combinedCond
      combinedCond.delRef();
    } // end loop over declarators
  } // end loop over typespecifiers
  return valuemv;
}


class IDSort implements Comparator<Map.Entry<String,Declaration>> {
  private int getID(String x){
    String res = "";
    int pos = x.length()-1;
    while(x.charAt(pos) != '_') {
      res = x.charAt(pos) + res;
      pos--;
    }
    return Integer.parseInt(res);
  }
  public int compare(Map.Entry<String,Declaration> a, Map.Entry<String,Declaration> b) {
    return getID(((VariableT)a.getValue().getType()).getName()) - getID(((VariableT)b.getValue().getType()).getName());
  }
}

public String initStruct(String name, StructOrUnionT t, Initializer i, CContext scope, PresenceCondition p)
{
  //NOTE: All fields are presumably using . as the access method. Chagne this to . / -> depending
  //on the context
  SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(t.getName());
  Multiverse<List<Map.Entry<String,Declaration>>> m = tagtab.getLists(p);
  //for now, I'm making the assumption all field defs are in order, although this isn't the case.
  //this can be solved by sort each list by it's appended number
  
  //SORT

  for (Element<List<Map.Entry<String,Declaration>>> e : m) {
    List<Map.Entry<String,Declaration>> l = e.getData();
    Collections.sort(l,new IDSort());
    e.setData(l);
  }
  
  // for each list, we need to write an if statement for assigning initial values
  // under each pc. We need a list of either expressions to assign, or designators, and
  // go through the list assigning approprietly.

  List<Initializer> inits = i.getList();
  StringBuilder entrysb = new StringBuilder();
   
  for (Element<List<Map.Entry<String,Declaration>>> e : m) {
    entrysb.append("if (");
    entrysb.append(condToCVar(e.getCondition()));
    entrysb.append(") {\n");
    //lists can never have errors due to how they are built. The declaration of
    //the struct will have an error, so the type error is already dealt with
    
    int spot  = 0;
    for (Initializer init : inits) {
      if (init.isDesignated()) {
        Designation d = ((DesignatedInitializer)init).getDesignation();
        Designator des = d.getDesignator();
        if (des.isStructUnion()) {
          int newSpot;
          for (newSpot = 0; newSpot < e.getData().size(); ++newSpot) {
            if ((((StructUnionDesignator)des).getName()).equals(e.getData().get(newSpot).getKey())) {
              Initializer in = init.getChild();
              //at this point, we get the direct field being accessed. If it is a struct(list) then
              //we recursively call this, the Initializer is a new list with the first object
              //being removed. If it is a singular value, we can just handle it the same way all
              //individual values are handled.
              if (d.getListSize() == 1) {
                if (in.isList()) {
                  VariableT newT = ((VariableT)e.getData().get(newSpot).getValue().getType());
                  if (newT.getType().isStruct() || newT.getType().isUnion()) {
                    entrysb.append(initStruct( name + "." + newT.getName(),
                                               (StructOrUnionT)newT.getType(), in, scope, e.getCondition()));
                  } else if (newT.getType().isArray()) {
                    entrysb.append(initArray( name + "." + newT.getName(),
                                              (ArrayT)newT.getType(), in, scope, e.getCondition()));
                  } else {
                    entrysb.append(emitError("A list can't be assigned to this type.") + ";\n");
                  }
                } else {
                  entrysb.append(name + "." + ((VariableT)e.getData().get(newSpot).getValue().getType()).getName() + " = " + ((DesignatedInitializer)init).getInitString() + ";\n");
                }
              } else {
                List<Designator> newDesList = new LinkedList<Designator>();
                for (int k = 1; k < d.getListSize(); ++k ) {
                  newDesList.add(d.getDesignator(k));
                }
                Initializer newInit = new DesignatedInitializer(new Designation(newDesList), in);
                if (in.isList()) {
                  VariableT newT = ((VariableT)e.getData().get(newSpot).getValue().getType());
                  if (newT.getType().isStruct() || newT.getType().isUnion()) {
                    entrysb.append(initStruct( name + "." + newT.getName(),
                                               (StructOrUnionT)newT.getType(), newInit, scope, e.getCondition()));
                  } else if (newT.getType().isArray()) {
                    entrysb.append(initArray( name + "." + newT.getName(),
                                              (ArrayT)newT.getType(), newInit, scope, e.getCondition()));
                  } else {
                    entrysb.append(emitError("A list can't be assigned to this type.") + ";\n");
                  }
                } else {
                  Multiverse<String> writes =
                    getDesigTransforms(name + "." +
                                       ((VariableT)e.getData().get(newSpot).getValue().getType()).getName(),
                                       newDesList,
                                       ((VariableT)e.getData().get(newSpot).getValue().getType()).getType(),
                                       e.getCondition(),
                                       scope);
                  for (Element<String> es : writes) {
                    entrysb.append("if (");
                    entrysb.append(condToCVar(es.getCondition()));
                    entrysb.append(") {\n");
                    entrysb.append(es.getData() + " = " +
                                   ((DesignatedInitializer)init).getInitString() + ";\n");
                    entrysb.append("}\n");
                  }
                }
              }
              break;
            }
          }
          if (newSpot == e.getData().size()) {
            entrysb.append(emitError("designator doesn't exist.") + ";\n");
            break;
          }
          spot = newSpot + 1;
          //if it is an array access
        } else {
          entrysb.append(emitError("array designator on struct.") + ";\n}\n");
          return entrysb.toString();
        }
      } else {
        if (spot >= e.getData().size()) {
          entrysb.append(emitError("assigning value out of struct range.") + ";\n");
        } else {
          //gotta handle this differently if it's a list, in fact, recursive call.
          if (init.isList()) {
            VariableT newT = ((VariableT)e.getData().get(spot).getValue().getType());
            if (newT.getType().isStruct() || newT.getType().isUnion()) {
              entrysb.append(initStruct( name + "." + newT.getName(),
                                         (StructOrUnionT)newT.getType(), init, scope, e.getCondition()));
            } else if (newT.getType().isArray()) {
              entrysb.append(initArray( name + "." + newT.getName(),
                                        (ArrayT)newT.getType(), init, scope, e.getCondition()));
            } else {
              entrysb.append(emitError("A list can't be assigned to this type.") + ";\n");
            }
          } else {
            entrysb.append(name + "." + ((VariableT)e.getData().get(spot).getValue().getType()).getName() + " = " + init.toString() + ";\n");
          }
        }
        spot++;
      }
    }
    entrysb.append("}\n");
  }



  return entrysb.toString();
}

public String initArray(String name, ArrayT t, Initializer i, CContext scope, PresenceCondition p)
{
  List<Initializer> inits = i.getList();
  StringBuilder entrysb = new StringBuilder();
   
    
  int spot  = 0;
  for (Initializer init : inits) {
    String accessSpot;
    Initializer next = init;
    if (init.isDesignated()) {
      Designation d = ((DesignatedInitializer)init).getDesignation();
      Designator des = d.getDesignator();
      next = init.getChild();
      if (des.isArray()) {
        //currently making the assumption that expression accesses are just numbers.
        //this isn't correct.
        spot = new Integer(((ArrayDesignator)des).getExpression());
      } else {
        entrysb.append(emitError("struct designator on array.") + "\n}\n");
        return entrysb.toString();
      }

      if (d.getListSize() > 1) {
        Initializer in = init.getChild();
        List<Designator> newDesList = new LinkedList<Designator>();
        for (int k = 1; k < d.getListSize(); ++k ) {
          newDesList.add(d.getDesignator(k));
        }
        Initializer newInit = new DesignatedInitializer(new Designation(newDesList), in);
        if (in.isList()) {
          if (t.getType().isStruct() || t.getType().isUnion()) {
            entrysb.append(initStruct( name + "[" + Integer.toString(spot) + "]",
                                       (StructOrUnionT)t.getType(), newInit, scope, p));
          } else if (t.getType().isArray()) {
            entrysb.append(initArray( name + "[" + Integer.toString(spot) + "]",
                                      (ArrayT)t.getType(), newInit, scope, p));
          } else {
            entrysb.append(emitError("A list can't be assigned to this type."));
          }
        } else {
          Multiverse<String> writes =
            getDesigTransforms(name + "[" + Integer.toString(spot) + "]",
                               newDesList,
                               t.getType(),
                               p,
                               scope);
          for (Element<String> es : writes) {
            entrysb.append("if (");
            entrysb.append(condToCVar(es.getCondition()));
            entrysb.append(") {\n");
            entrysb.append(es.getData() + " = " +
                           ((DesignatedInitializer)init).getInitString() + ";\n");
            entrysb.append("}\n");
          }
        }
        //If this was a designation list, everything is handled, go to the next step
        spot++;
        continue;
      }
    }
    accessSpot = "[" + Integer.toString(spot) + "]";
    if (next.isList()) {
      if (t.getType().isStruct() || t.getType().isUnion()) {
        entrysb.append(initStruct( name + accessSpot,
                                   (StructOrUnionT)t.getType(), next, scope, p));
      } else if (t.getType().isArray()) {
        entrysb.append(initArray( name + accessSpot,
                                  (ArrayT)t.getType(), next, scope, p));
      } else {
        entrysb.append(emitError("A list can't be assigned to this type."));
      }
    } else {
      entrysb.append(name + accessSpot + " = " + next.toString() + ";\n");
    }
    spot++;
  }
  return entrysb.toString();
}


private Multiverse<String> getDesigTransforms(String prefix, List<Designator> l, Type t, PresenceCondition p, CContext scope) {
  if (l.size() == 0) {
    Multiverse<String> ret = new Multiverse<String>();
    ret.add(prefix, p);
    return ret;
  }
  Designator d = l.get(0);
  List<Designator> newD = new LinkedList<Designator>();
  for (int i = 1; i < l.size(); ++i) {
    newD.add(l.get(i));
  }
  if (d.isArray()) {
    //making the assumption that we have a valid array here.
    return getDesigTransforms(prefix + d.toString(), newD, ((ArrayT)t).getType(), p, scope );
  } else {
    //using the current struct,
    Multiverse<String> ret = new Multiverse<String>();
    SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(((StructOrUnionT)t).getName());
    Multiverse<Entry<Declaration>> m = tagtab.get(((StructUnionDesignator)d).getName(), p);
    for (Element<Entry<Declaration>> e : m) {
      Multiverse<String> toAdd = getDesigTransforms(prefix + "." +
                                                    ((VariableT)e.getData().getValue().getType()).getName(),
                                                    newD,
                                                    ((VariableT)e.getData().getValue().getType()).getType(),
                                                    e.getCondition(),
                                                    scope);
      for (Element<String> es : toAdd) {
        ret.add(es);
      }
    }
    return ret;
  }
}

private int trueInitSize(Initializer i) {
  int curSize = 0;
  int maxSize = 0;
  List<Initializer> l = i.getList();
  if (l == null) {
    //shouldn't ever happen
    return -1;
  }
  for (Initializer init : l) {
    if (init.isDesignated()) {
      Designator d = ((DesignatedInitializer)init).getDesignation().getDesignator();
      if (!d.isArray()) {
        //shouldn't ever happen
        return -1;
      }
      //once again assuming we are just using numbers.
      curSize = new Integer(((ArrayDesignator)d).getExpression());
    } else {
      curSize++;
    }
    if (curSize > maxSize) {
      maxSize = curSize;
    }
  }
  return maxSize;
}


Multiverse<Map.Entry<String,Declaration>> getNestedFields(String structId, String fieldId, PresenceCondition pc, CContext scope) {
  Multiverse<Map.Entry<String,Declaration>> result = new Multiverse<Map.Entry<String,Declaration>>();
  SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(structId);
  Multiverse<Entry<Declaration>> m = tagtab.get(fieldId, pc);
  for (Element<Entry<Declaration>> e  : m) {
    if (e.getData().isUndeclared() || e.getData().isError()) {
      continue;
    }
    //no checking needs to be done here since we know the multiverse returned has no
    //violations
    result.add(new AbstractMap.SimpleImmutableEntry<String,Declaration>(((VariableT)e.getData().getValue().getType()).getName(),
                                                                 e.getData().getValue()), e.getCondition().and(pc));
  }
  m.destruct();
  //recursive call on anonymous ids
  List<String> anonIds = tagtab.getAnonIds();
  for (String a : anonIds) {
    m = tagtab.get(a, pc);
    for (Element<Entry<Declaration>> e : m) {
      if (e.getData().isUndeclared()) {
        continue;
      }
      PresenceCondition p = e.getCondition().and(pc);
      VariableT v = ((VariableT)e.getData().getValue().getType());
      if (!v.getType().isStruct() && !v.getType().isUnion()) {
	continue;
      }
      Multiverse<Map.Entry<String,Declaration>> inner = getNestedFields(((StructOrUnionT)v.getType()).getName(), fieldId, p, scope);
      p.delRef();
      //add anonymous id . to front of string.
      //anonymous fields cannot be pointers
      if (!inner.isEmpty()) {
        for (Element<Map.Entry<String,Declaration>> ei : inner) {
          ei.setData(new AbstractMap.SimpleImmutableEntry<String,Declaration>(((VariableT)e.getData().getValue().getType()).getName()
                                                                       + " . " + ei.getData().getKey()
                                                                       ,
									      (ei.getData().getValue()).rename(((VariableT)e.getData().getValue().getType()).getName()
                                                                       + " . " + ei.getData().getValue().getName())
									      ));
        }
        for (Element<Map.Entry<String,Declaration>> ei : inner) {
          if (!result.isEmpty()) {
            boolean remade;
            do {
              remade = false;
              for (Element<Map.Entry<String,Declaration>> er : result) {
                p = er.getCondition().and(ei.getCondition());
                if (!p.isFalse() && !er.getData().getKey().equals("")) {
                  //there is an overlap in presence conditions, which is a type error
                  Multiverse<Map.Entry<String,Declaration>> newR = new Multiverse<Map.Entry<String,Declaration>>();
                  for (Element<Map.Entry<String,Declaration>> en : result) {
                    if (en != er) {
                      newR.add(en);
                    } else {
                      newR.add(en.getData(), p);
                      newR.add(en.getData(), er.getCondition().and(ei.getCondition().not()));
                    }
              
                  }
                  result.destruct();
                  result = newR;
                  remade = true;
                  p.delRef();
                  break;
                }
                p.delRef();
              }
            } while (remade);
            if (!ei.getCondition().and(result.getComplement()).isFalse()) {
              result.add(ei.getData(), ei.getCondition().and(result.getComplement()));
            }
          } else //result is empty, complement is 1, we can just add
            {
              result.add(ei);
            }
        }
      }
    }
  }
  return result;
}

public Multiverse<String> injectErrorIntoStrMv(Multiverse<String> mvs, Multiverse<Type> mvt, String msg) {
  PresenceCondition ec = mvt.getConditionOf(ErrorT.TYPE);
  Multiverse<String> newmv = mvs.filter(ec.not());
  newmv.add(emitError(msg) + ";", ec);
  ec.delRef();
  return newmv;
}

public Multiverse<String> removeTrailing(Multiverse<String> oldmv, PresenceCondition pc) {
  Multiverse<String> toRem = oldmv.filter(pc);
  Multiverse<String> safe = oldmv.filter(pc.not());
  if (!toRem.isEmpty()) {
    for (Element<String> e : toRem) {
      String s = e.getData();
      e.setData(s.substring(0,s.length()-1));
    }
  }
  toRem.addAll(safe);
  safe.destruct();
  return toRem;
}

public Multiverse<String> appendStringToMV(Multiverse<String> oldmv, String app, PresenceCondition pc) {
  Multiverse<String> newmv = new Multiverse<String>(oldmv);
  boolean remade;
  do {
    remade = false;
    for (Element<String> el : newmv) {
      PresenceCondition p = el.getCondition().and(pc);
      //if the presencondition is a subset, but isn't 0
      //issue is, that we also add if e is strictly greater than.
      if (el.getCondition().is(p)) {
        el.setData(el.getData() + app);
      } else if (!p.isFalse()) {
        Multiverse<String> newermv = new Multiverse<String>();
        for (Element<String> elN : newmv) {
          if (elN != el) {
            newermv.add(elN.getData(), elN.getCondition());
          }
        }
        String s = new String(el.getData());
        newermv.add(el.getData(), p);
        newermv.add(s, el.getCondition().and(pc.not()));
        newmv.destruct();
        newmv = newermv;
        remade = true;
        p.delRef();
        break;
      }
    }
  } while (remade);
  return newmv;
}


static public Multiverse<List<DeclarationOrStatementValue>> listMultiverseSwap(List<Multiverse<DeclarationOrStatementValue>> listOfObjects, PresenceCondition pc) {
  Multiverse<List<DeclarationOrStatementValue>> listMV = new Multiverse<List<DeclarationOrStatementValue>>();
  listMV.add(new LinkedList<DeclarationOrStatementValue>(), pc);
  for (Multiverse<? extends DeclarationOrStatementValue> m : listOfObjects) {
    for (Element<? extends DeclarationOrStatementValue> e : m) {
      //for each value, check to see if any 'and's does not result
      //in not. If it doesn't split the list.
      boolean remade;
      do {
        remade = false;
        for (Element<List<DeclarationOrStatementValue>> el : listMV) {
          PresenceCondition intersect = el.getCondition().and(e.getCondition());
          //if the intersection is the same as the element in the listMV
          //then the listMV pc is strictly a subset, and we add the object
          //to the listMV object.
          if (el.getCondition().is(intersect)) {
            el.getData().add(e.getData().deepCopy());
          } else if (!intersect.isFalse()) {
            Multiverse<List<DeclarationOrStatementValue>> newLists = new Multiverse<List<DeclarationOrStatementValue>>();
            for (Element<List<DeclarationOrStatementValue>> elN : listMV) {
              if (elN != el) {
                newLists.add(elN.getData(), elN.getCondition());
              }
            }
            List<DeclarationOrStatementValue> tL = new LinkedList<DeclarationOrStatementValue>();
            for (DeclarationOrStatementValue c : el.getData()) {
              tL.add(c.deepCopy());
            }
            newLists.add(el.getData(), intersect);
            newLists.add(tL, el.getCondition().and(intersect.not()));
            listMV.destruct();
            listMV = newLists;
            remade = true;
            intersect.delRef();
            break;
          }
        }
      } while (remade);
    } 
  }
  return listMV;
}

static public String typespecLines(TypeSpecifier t) {
  List<Syntax> l = t.getTokens();
  LineNumbers ln = new LineNumbers();
  for (Syntax s : l) {
    if (s.hasLocation()) {
      LineNumbers temp = new LineNumbers(s);
      ln = new LineNumbers(ln,temp);
    }
  }
  return ln.getComment();
}

static public String declaringListRange(List<DeclaringListValue> ds, Syntax syn) {
  LineNumbers ln = new LineNumbers();
  for (DeclaringListValue d : ds) {
    for (Element<TypeSpecifier> e : d.typespecifier) {
      TypeSpecifier t = e.getData();
      List<Syntax> l = t.getTokens();
      for (Syntax s : l) {
        if (s.hasLocation()) {
          LineNumbers temp = new LineNumbers(s);
          ln = new LineNumbers(ln,temp);
        }
      }
    }
  }
  ln = new LineNumbers(ln, new LineNumbers(syn));
  return ln.getComment();
}

public static class SortByCreation implements Comparator<Map.Entry<String,Declaration>> {
  public int compare(Map.Entry<String,Declaration> a, Map.Entry<String,Declaration> b) {
    String as = a.getValue().getName();
    String bs = b.getValue().getName();
    int bval = 0, aval = 0;
    int mult = 1, ind = 1;
    while (as.charAt(as.length()-ind) != '_') {
      aval += mult * (as.charAt(as.length()-ind) - '0');
      ind++; mult *= 10;
    }
    mult = 1; ind = 1;
    while (bs.charAt(bs.length()-ind) != '_') {
      bval += mult * (bs.charAt(bs.length()-ind) - '0');
      ind++; mult *= 10;
    }
    return aval - bval;
  }
}

static public List<Map.Entry<String,Declaration>> sortByCreation(List<Map.Entry<String,Declaration>> l) {
  List<Map.Entry<String,Declaration>> nl =  new LinkedList<Map.Entry<String,Declaration>>(l);
  Collections.sort(nl,new SortByCreation());
  return nl;
}

static public Multiverse<String> sizeofBody(Type t, FreshIDCreator fic, CContext scope, PresenceCondition p) {
  Multiverse<String> ret = new Multiverse<String>();
  SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(t.getName());
  Multiverse<List<Map.Entry<String,Declaration>>> m = tagtab.getLists(p);
  if (!m.isEmpty()) {
    for (Element<List<Map.Entry<String,Declaration>>> el : m) {
      Multiverse<List<String>> structEq = new Multiverse<List<String>>();
      String typ = t.isStruct() ? "struct" : "union";
      structEq.add(new LinkedList<String>(){{add(typ + " {");}},el.getCondition());
      boolean moreThanOne = false;
      List<Map.Entry<String,Declaration>> l = sortByCreation(el.getData());
      for (Map.Entry<String,Declaration> me : l) {
        Type fieldT = me.getValue().getType().resolve();
        if (fieldT.isStruct() || fieldT.isUnion()) {
          Multiverse<String> innerStruct = sizeofBody(fieldT,fic,scope,el.getCondition());
          innerStruct = innerStruct.appendScalar(fic.freshCId() + ";",DesugarOps.concatStrings);
          //I believe this should always be complete. If the struct is undefined or an
          //error, than the struct it is inside of should be an error in that condition
          //as well.
          structEq = structEq.product(DesugarOps.StringToStringList.transform(innerStruct),DesugarOps.concatStringsList);
        } else {
          if (me.getValue().getDeclarator().isBitFieldSizeDeclarator() || me.getValue().getDeclarator().isNamedBitFieldSizeDeclarator()) {
            structEq = structEq.appendScalar(new LinkedList<String>(){{add(me.getValue().printType(fic.freshCId()) +  ";");}},DesugarOps.concatStringsList);
          } else {
            structEq = structEq.appendScalar(new LinkedList<String>(){{add( "typeof( " + me.getValue().printType() + ") " + fic.freshCId() + ";");}},DesugarOps.concatStringsList);
          }
        }
      }
      structEq = structEq.appendScalar(new LinkedList<String>(){{add("}");}},DesugarOps.concatStringsList);
      for (Element<List<String>> es : structEq) {
        String X = "";
        for (String s : es.getData()) {
          X = X + s;
        }
        ret.add(X,es.getCondition());
      }
    }
  }
  return ret;
}

static public Multiverse<String> sizeofExpansion(Multiverse<Type> t, FreshIDCreator fic, CContext scope, PresenceCondition p) {
  return sizeofExpansion(new Multiverse<String>(),t,fic,scope,p);
}


static public Multiverse<String> sizeofExpansion(Multiverse<String> es, Multiverse<Type> t, FreshIDCreator fic, CContext scope, PresenceCondition p) {
  Multiverse<String> ret = new Multiverse<String>();
  for (Element<Type> et : t.filter(p)) {
    Type tempT = et.getData().resolve();
    if (tempT.isStruct() || tempT.isUnion()) {
      Multiverse<String> innerStruct = sizeofBody(tempT,fic,scope,et.getCondition());
      for (Element<String> e : innerStruct) {
        if (!es.isEmpty()) {
          String standin = "";
          standin = fic.freshCId("sizeofStandin");
          scope.addDeclaration(e.getData() + standin + ";\n");
          ret.add("sizeof(" + standin + ")",e.getCondition());
        } else {
          String standin = "";
          standin = fic.freshCId("sizeofStandin");
          scope.addDeclaration(e.getData() + standin + ";\n");
          ret.add("sizeof(typeof(" + standin + "))",e.getCondition());
        }
      }
    } else {
      if (!es.isEmpty() && !(es.filter(et.getCondition())).isEmpty()) {
        for (Element<String> ex : es.filter(et.getCondition())) {
          if (ex.getData().equals("")) {
            ret.add("sizeof(" + et.getData().printType() + ")",ex.getCondition());
          } else {
            ret.add("sizeof(" + ex.getData() + ")",ex.getCondition());
          }
        }
      } else {
        ret.add("sizeof(" + et.getData().printType() + ")", et.getCondition());
      }
    }
  }
  return ret;
}

//note, I'm pretty sure this shoudl always be size one, but I'm being thurough
static public Multiverse<Boolean> hasField(UnionT u, Type t, CContext scope, PresenceCondition p) {
  SymbolTable<Declaration> tagtab = scope.getLookasideTableAnyScope(u.getName());
  Multiverse<List<Map.Entry<String,Declaration>>> fields = tagtab.getLists(p);
  Multiverse<Boolean> res = new Multiverse<Boolean>();
  for (Element<List<Map.Entry<String,Declaration>>> e : fields) {
    Boolean found = new Boolean(false);
    for (Map.Entry<String,Declaration> m: e.getData()) { 
      if (compatTypes(m.getValue().getType(),t)) {
        found = new Boolean(true);
      }
    }
    res.add(found,e.getCondition());
  }
  return res;
}

static public boolean compatParam(Type t1u, Type t2u) {
  Type t1 = t1u.resolve(), t2 = t2u.resolve();
  if ((t1.isPointer() || t1.isArray()) && t2.isNumber()) {
    return true;
  } else if (t2.isPointer() && t1.isPointer()) {
    return true;
  } else if (t2.isFunction() && (t1.isPointer() || t1.isFunction())) {
    return true;
  }
  return compatTypes(t1u,t2u);
}

static public boolean compatTypes(Type t1u, Type t2u) {
  Type t1 = t1u.resolve(), t2 = t2u.resolve();
  //we'll say that numbers are compatible
  if ((t1.isNumber()) && (t2.isNumber())) {
    return true;
  }
  //if both variables are pointers/arrays direct compare inner types
  if ( (t1.isPointer() || t1.isArray()) &&
       (t2.isPointer() || t2.isArray())) {
    Type innerT1, innerT2;
    if (t1.isPointer()) {
      innerT1 = ((PointerT)t1).getType().resolve();
    } else {
      innerT1 = ((ArrayT)t1).getType().resolve();
    }
    if (t2.isPointer()) {
      innerT2 = ((PointerT)t2).getType().resolve();
    } else {
      innerT2 = ((ArrayT)t2).getType().resolve();
    }
    return (cOps.equal(innerT1, innerT2)) || innerT1.isVoid();
  }
  //outside of these, just direct equal
  return cOps.equal(t1, t2);
}

static public boolean functionCouldExist(Type newType, Type prevType, CContext scope, PresenceCondition cond) {
  if (!newType.isFunction() || !prevType.isFunction()) {
    return false;
  }
  FunctionT newf = newType.toFunction();
  FunctionT oldf = prevType.toFunction();

  if (!cOps.equal(newf.getResult(),oldf.getResult())) {
    if (!typeCouldBeRef(newf.getResult(),oldf.getResult(),scope,cond)) {
      return false;
    }

  }
  
  List<Type> newParams = newf.getParameters();
  List<Type> oldParams = oldf.getParameters();

  if (newParams.size() != oldParams.size()) {
    return false;
  }
  for (int i = 0; i < newParams.size(); ++i) {
    Type newT = ((VariableT)newParams.get(i)).getType();
    Type oldT = ((VariableT)oldParams.get(i)).getType();
    if (cOps.equal(newT.resolve(),oldT.resolve())) {
      continue;
    }
    if (!typeCouldBeRef(newT,oldT,scope,cond)) {
      return false;
    }
  }
  return true;
}

static public boolean typeCouldBeRef(Type newT, Type oldT, CContext scope, PresenceCondition cond) {
  while (newT.isPointer() || newT.isAnnotated() || newT.isArray()) {
    if (newT.isPointer()) {
      if (!oldT.isPointer()) {
        return false;
      }
      newT = ((PointerT)newT).getType();
      oldT = ((PointerT)oldT).getType();
    }
    if (newT.isArray()) {
      if (!oldT.isArray()) {
        return false;
      }
      newT = ((ArrayT)newT).getType();
      oldT = ((ArrayT)oldT).getType();
    }
    if (newT.isAnnotated()) {
      if (newT.toAnnotated().sameAnnotations(oldT)) {
        return false;
      }
      newT = ((AnnotatedT)newT).getType();
      oldT = ((AnnotatedT)oldT).getType();
    }
  }
  
  
  if (newT.isStruct() && oldT.isStruct()) {
    if (! ((StructT)oldT).getName().startsWith("__forward_tag_reference")){
      return false;
    }
    String originalTag = scope.getForwardTagReferenceAnyScope(((StructT)oldT).getName());                
    
    Multiverse<SymbolTable.Entry<Type>> originalTagEntries
      = scope.getInAnyScope(CContext.toTagName(originalTag), cond);
    
    boolean found = false;
    for (Element<SymbolTable.Entry<Type>> e : originalTagEntries) {
      found = found || cOps.equal(e.getData().getValue(),newT);
    }
    if (!found) {
      return false;
    }
  } else {
    return false;
  }
  return true;
}

static public void transformFunctionRefs(Declarator toTransform, Type prevType, PresenceCondition cond, Multiverse<Declarator> decs, TypeSpecifier typespec, Multiverse<TypeSpecifier> types , CContext scope) {
  if (!prevType.isFunction()) {
    System.err.println("Error reverting refs of nonfunction");
    System.exit(1);
  }
  List<Type> oldParams = ((FunctionT)prevType).getParameters();
  decs.add(toTransform.switchForwardRef(oldParams,cond,scope),cond);
  Type resType = prevType.toFunction().getResult();
  while (resType.isPointer()) {resType = resType.toPointer().getType();}
  if (resType.isStruct() && ((StructT)resType).getName().startsWith("__forward_tag_reference_")) {
    String originalTag = scope.getForwardTagReferenceAnyScope(((StructT)resType).getName());
    Multiverse<SymbolTable.Entry<Type>> originalTagEntries
      = scope.getInAnyScope(CContext.toTagName(originalTag), cond);
    List<String> names = new LinkedList<String>();
    for (Element<SymbolTable.Entry<Type>> e : originalTagEntries) {
      names.add(((StructT)e.getData().getValue()).getName());
    }
    types.add(typespec.revertForwardRefs(names,((StructT)resType).getName(),toTransform.getName()),cond);
  } else {
    types.add(typespec,cond);
  }
}


/***************************************************************************
 **** Class to create fresh ids.
 ***************************************************************************/

public static class FreshIDCreator {

  /** The fresh name count. */
  protected int freshNameCount;

  /** The fresh identifier count. */
  protected int freshIdCount;

  /** The fresh anon identifier count. */
  protected int freshAnonIdCount;

  public FreshIDCreator() {
    this(0, 0, 0);
  }
  
  public FreshIDCreator(int freshNameCount, int freshIdCount, int freshAnonIdCount) {
    this.freshNameCount = freshNameCount;
    this.freshIdCount = freshIdCount;
    this.freshAnonIdCount = freshAnonIdCount;
  }

  // The following naming and namespacing functionality is taken
  // directly from xtc.util.SymbolTable.

  public String freshAnonId() {
    String r = "anon_id_";
    r += Integer.toString(freshAnonIdCount);
    freshAnonIdCount++;
    return r;
  }
  
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
}

FreshIDCreator freshIdCreator = new FreshIDCreator();

public String freshCId(String base) {
  return freshIdCreator.freshCId(base);
}

public String freshAnonId() {
  return freshIdCreator.freshAnonId();
}

/**
 * This class manages the struct and union types, since xtc's type
 * system uses a nonce to distinguish tagged types of the same name.
 * This class caches existing tag types to ensure type equivalence.
 */
public static class StructOrUnionTypeCreator {
  /** Maps tag to type. */
  Map <String, Type> typeCache;
  
  public StructOrUnionTypeCreator() {
    typeCache = new HashMap<String, Type>();
  }

  public Type create(Syntax keyword, String tag) {
    return create(keyword.getTokenText(), tag);
  }

  public Type createStruct(String tag) {
    return create("struct", tag);
  }

  public Type createUnion(String tag) {
    return create("union", tag);
  }

  public Type create(String keyword, String tag) {
    if (typeCache.containsKey(tag)) {
      // this does not validate that the previous type matches the
      // current keyword (struct/union)
      return typeCache.get(tag);
    } else {
      Type newType;
      if (keyword.equals("struct")) {
        newType = new StructT(tag);
      } else if (keyword.equals("union")) {
        newType = new UnionT(tag);
      } else {
        throw new AssertionError("unexpected keyword to createStructOrUnionRefType");
      }
      assert null != newType;
      typeCache.put(tag, newType);
      return newType;
    }
  }
}

StructOrUnionTypeCreator suTypeCreator = new StructOrUnionTypeCreator();


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
  public Multiverse<TypeSpecifier> typespecifier;
  
  /** The declarator */
  public Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private FunctionPrototypeValue(Multiverse<TypeSpecifier> typespecifier, Multiverse<Declarator> declarator) {
    this.typespecifier = typespecifier;
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
  public final Multiverse<TypeSpecifier> typespecifier;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** The initializer. */
  public Multiverse<Initializer> initializer;

  public Multiverse<String> desugared;
  
  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   * @param declarator is the initializer.
   */
  private DeclaringListValue(Multiverse<TypeSpecifier> typespecifier,
                             Multiverse<Declarator> declarator,
                             Multiverse<Initializer> initializer,
                             PresenceCondition p) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
    this.initializer = initializer;
    this.desugared = new Multiverse<String>("",p);
  }

    private DeclaringListValue(Multiverse<TypeSpecifier> typespecifier,
                             Multiverse<Declarator> declarator,
                             Multiverse<Initializer> initializer,
                             Multiverse<String> desugared) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
    this.initializer = initializer;
    this.desugared = desugared;
  }

  public boolean isEmpty() {
    return typespecifier.isEmpty() ||
      declarator.isEmpty() ||
      initializer.isEmpty() ||
      desugared.isEmpty();
  }
  
  public String toString()
  {
    return "TypeSpec: " + typespecifier.toString() +
      "\nDeclarator: " + declarator.toString() +
      "\nInitializer: " + initializer.toString() +
      "\nDesugared: " + desugared.toString();
  }

  public DeclaringListValue filter(PresenceCondition p ) {
    return new DeclaringListValue(typespecifier.filter(p),declarator.filter(p),initializer.filter(p),desugared.filter(p));
  }

  public void destruct() {
    typespecifier.destruct(); declarator.destruct(); initializer.destruct(); desugared.destruct();
  }

  public void addAll(DeclaringListValue d) {
    typespecifier.addAll(d.typespecifier);
    declarator.addAll(d.declarator);
    initializer.addAll(d.initializer);
    desugared.addAll(d.desugared);
  }
}

/*
 * This class is the semantic value for parameters.
 */
private static class ParameterDeclarationValue {
  /** The type. */
  public final Multiverse<TypeSpecifier> typespecifier;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private ParameterDeclarationValue(Multiverse<TypeSpecifier> typespecifier,
                                    Multiverse<Declarator> declarator) {
    this.typespecifier = typespecifier;
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
  public final Multiverse<TypeSpecifier> typespecifier;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   */
  private StructDeclaringListValue(Multiverse<TypeSpecifier> typespecifier,
                                 Multiverse<Declarator> declarator) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
  }

  public String toString() {
    return typespecifier.toString() + " " + declarator.toString();
  }
}

/**
 * This semantic value holds a parameter list so it can preserve
 * whether there was a variable number of arguments or not.
 */
private static class ParameterTypeListValue {
  /** The parameter list. */
  public final List<Multiverse<Declaration>> list;

  /** Whether the list has variable arguments or not. */
  public final boolean varargs;

  public ParameterTypeListValue(List<Multiverse<Declaration>> list, boolean varargs) {
    this.list = list;
    this.varargs = varargs;
  }

  public String toString() {
    return list.toString();
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

  public final Multiverse<LineNumbers> lines;
  
  /**
   * The cached valid type condition.
   */
  protected PresenceCondition validTypeCondition = null;

  public String toString()
  {
    String ret = "";
    ret += "type:" + type.toString();
    ret += "transform:" + transformation.toString();
    ret += "comment:" + lines.toString();
    return ret;
  }

  public ExpressionValue(Multiverse<String> transformation, Multiverse<Type> type) {
    this.transformation = transformation;
    this.type = type;
    lines = new Multiverse<LineNumbers>();
    PresenceConditionManager p = new PresenceConditionManager();
    PresenceCondition one = p.newTrue();
    lines.add(new LineNumbers(Integer.MAX_VALUE, 0), one);
  }

  public ExpressionValue(Multiverse<String> transformation, Multiverse<Type> type, Multiverse<LineNumbers> lns) {
    this.transformation = transformation;
    this.type = type;
    lines = lns;
  }
  
  /**
   * Create a new expression value from a single type and a single
   * transformation string.
   */
  public ExpressionValue(String transformation, Type type, PresenceCondition pc) {
    this.transformation = new Multiverse<String>(transformation, pc);
    this.type = new Multiverse<Type>(type, pc);
    
    lines = new Multiverse<LineNumbers>();
    lines.add(new LineNumbers(Integer.MAX_VALUE, 0), pc);
  }
  /**
   * Create a new expression value from a single type and a single
   * transformation string.
   */
  public ExpressionValue(String transformation, Type type, Multiverse<LineNumbers> lmv, PresenceCondition pc) {
    this.transformation = new Multiverse<String>(transformation, pc);
    this.type = new Multiverse<Type>(type, pc);
    lines = lmv;
  }
  
  /**
   * Return true there is at least one type that is not an error.
   * This is the negation of isAlwaysError().
   */
  public boolean hasValidType() {
    return ! isAlwaysError();
  }

  /**
   * Return true there is at least one type that is not an error under the given condition.
   * This is the negation of isAlwaysErrorUnder().
   */
  public boolean hasValidType(PresenceCondition p) {
    return ! isAlwaysErrorUnder(p);
  }
  
  /**
   * Returns true if this expression is a type error in every
   * configuration under the given condition in which there is a value.  Note that this excludes
   * the configurations in which there is no value at all, i.e., the
   * complement of the multiverse.
   */
  public boolean isAlwaysErrorUnder(PresenceCondition p) {
    Multiverse<Type> mtv = type.filter(p);
    // return true unless we find one type that isn't an error
    for (Element<Type> elem : mtv) {
      /* System.err.println("ELEM: " + elem.getData()); */
      if (! elem.getData().isError() && elem.getCondition().isNotFalse()) {
        return false;
      }
    }
    return true;
  }

  /**
   * Returns true if this expression is a type error in every
   * configuration in which there is a value.  Note that this excludes
   * the configurations in which there is no value at all, i.e., the
   * complement of the multiverse.
   */
  public boolean isAlwaysError() {
    // return true unless we find one type that isn't an error
    if (type.isEmpty()) {
      return true;
    }
    for (Element<Type> elem : type) {
      /* System.err.println("ELEM: " + elem.getData()); */
      if (! elem.getData().isError() && elem.getCondition().isNotFalse()) {
        return false;
      }
    }
    return true;
  }

  public boolean isEmpty() {
    return type.isEmpty() || transformation.isEmpty();
    
  }
  
  /**
   * Get only those transformation from a valid type under the given
   * presence condition.
   *
   * @param pc The current presence condition.
   * @return A new multiverse containing only valid transformations.
   */
  public Multiverse<String> validTransformations(PresenceCondition pc) {
    PresenceCondition validpc = this.validTypeCondition(pc);
    Multiverse<String> validmv = transformation.filter(validpc);
    validpc.delRef();
    return validmv;
  }
  
  /**
   * Get only the valid types under the given presence condition.
   *
   * @param pc The current presence condition.
   * @return A new multiverse containing only valid types.
   */
  public Multiverse<Type> validTypes(PresenceCondition pc) {
    PresenceCondition validpc = this.validTypeCondition(pc);
    Multiverse<Type> validmv = type.filter(validpc);
    validpc.delRef();
    return validmv;
  }
  
  /**
   * Get the presence condition under which the type is valid, given
   * the current presence condition.
   *
   * @returns A new presence condition.
   */
  public PresenceCondition validTypeCondition(PresenceCondition pc) {
    if (null == validTypeCondition) {
      PresenceCondition validCond = pc.presenceConditionManager().newFalse();
      for (Element<Type> elem : type) {
        /* System.err.println("ELEM: " + elem.getData()); */
        if (! elem.getData().isError()) {
          PresenceCondition newValidCond = validCond.or(elem.getCondition());
          validCond.delRef(); validCond = newValidCond;
        }
      }
      validTypeCondition = validCond;
    }
    return pc.and(validTypeCondition);
  }
  
  /**
   * Get the presence condition under which the type is invalid, i.e.,
   * an error or undeclared, given the current presence condition.
   *
   * @param pc The current presence condition.
   * @returns A new presence condition.
   */
  public PresenceCondition invalidTypeCondition(PresenceCondition pc) {
    PresenceCondition validCond = validTypeCondition(pc.presenceConditionManager().newTrue());
    PresenceCondition result = pc.andNot(validCond);
    validCond.delRef();
    return result;
  }

  public Multiverse<LineNumbers> integrateSyntax(Syntax s) {
    LineNumbers l = new LineNumbers(s);
    Multiverse<LineNumbers> lns = new Multiverse<LineNumbers>();
    for (Element<LineNumbers> e : lines) {
      lns.add(new LineNumbers(e.getData(), l), e.getCondition());
    }
    return lns;
  }

  public Multiverse<LineNumbers> integrateSyntax(Multiverse<Syntax> sm) {
    Multiverse<LineNumbers> lns = new Multiverse<LineNumbers>();
    for (Element<Syntax> es : sm) {
      Syntax s = es.getData();
      LineNumbers l = new LineNumbers(s);
      for (Element<LineNumbers> e : lines) {
        PresenceCondition p = es.getCondition().and(e.getCondition());
        if (p.isNotFalse()) {
          lns.add(new LineNumbers(e.getData(), l), p);
        }
        p.delRef();
      }
    }
    return lns;
  }
}

/**
 * Semantic value for an enumerator.
 */
protected static class EnumeratorValue {
  /** The name of the enumerator. */
  public final String name;

  /** The value of the expression, if set. */
  String transformation;

  /** The type of the expression, if set. */
  Type type;

  public EnumeratorValue(String name, String transformation, Type type) {
    this.name = name;
    this.transformation = transformation;
    this.type = type;
  }

  /**
   * Gets the transformation value.
   */
  public String getTransformation() {
    return this.transformation;
  }

  /**
   * Gets the type.
   */
  public Type getType() {
    return this.type;
  }

  public String toString() {
    return name + "(" +transformation + ", " + type + ")";
  }
}

/**
 * Semantic value For an enumerator's value.
 */
private static class EnumeratorValValue {
  /** True when there is value set. */
  boolean hasValue;

  /** The value of the expression, if set. */
  String transformation;

  /** The type of the expression, if set. */
  Type type;

  protected EnumeratorValValue(boolean hasValue, String transformation, Type type) {
    this.hasValue = hasValue;
    this.transformation = transformation;
    this.type = type;
  }

  public EnumeratorValValue() {
    this(false, null, null);
  }

  public EnumeratorValValue(String transformation, Type type) {
    this(true, transformation, type);
  }

  protected EnumeratorValValue(EnumeratorValValue other) {
    this.hasValue = other.hasValue;
    this.transformation = other.transformation;
    this.type = other.type;
  }

  
  public boolean hasValue() { return hasValue; }

  /**
   * Gets the value, if any, otherwise throws an illegal state
   * exception.
   */
  public String getTransformation() {
    if (this.hasValue()) {
      return this.transformation;
    } else {
      throw new AssertionError("trying to get value from empty enumerator value");
    }
  }

  /**
   * Gets the type, if any, otherwise throws an illegal state
   * exception.
   */
  public Type getType() {
    if (this.hasValue()) {
      return this.type;
    } else {
      throw new AssertionError("trying to get value from empty enumerator value");
    }
  }
}

public static class StringListPair {
  public String str;
  public LineNumbers lines;
  public StringListPair(String s, LineNumbers l) {
    str = s;
    lines = l;
  }
}

public static class LineNumbers {
  public int earliestLine;
  public int latestLine;
  public LineNumbers() {
    earliestLine = Integer.MAX_VALUE;
    latestLine = 0;
  }
  public LineNumbers(int line) {
    
    earliestLine = line;
    latestLine = line;
  }
  public LineNumbers(Syntax line) {
    if (line.getLocation() != null)
      {
	earliestLine = line.getLocation().line;
	latestLine = line.getLocation().line;
      }
    else {
      earliestLine = Integer.MAX_VALUE;
      latestLine = 0;
    }
  }
  public LineNumbers(int line1, int line2) {
    
    earliestLine = line1;
    latestLine = line2;
  }
  public LineNumbers(Syntax line1, Syntax line2) {
   
    earliestLine = line1.getLocation().line;
    latestLine = line2.getLocation().line;
  }
  public LineNumbers(LineNumbers one, LineNumbers two) {
    
    earliestLine = one.earliestLine < two.earliestLine ? one.earliestLine : two.earliestLine;
    latestLine = one.latestLine > two.latestLine ? one.latestLine : two.latestLine;
  }
  
  public String getComment() {
    if (earliestLine == latestLine)
      return "// L" + Integer.toString(earliestLine);
    else if (earliestLine == Integer.MAX_VALUE &&
             latestLine == 0) {
      return "// L0";
    } else {
      return "// L" + Integer.toString(earliestLine) + ":L" + Integer.toString(latestLine);
    }
  }
  public String toString() {
    return getComment();
  }
}

public interface Copyable {
  public Copyable deepCopy();
}

public static class DeclarationOrStatementValue implements Copyable{
  private String mainValue;
  private List<Multiverse<DeclarationOrStatementValue>> children;
  private List<DeclarationOrStatementValue> switchChildren;
  private String childPrepend;
  private boolean isElse;
  private String elseString;
  private boolean isDo;
  private String childAppend;
  private boolean isDecl;
  private boolean isEmpty;
  private boolean isGotoLabel;
  private boolean isLabel;
  private boolean isStatementAsExpression;
  private String Label;
  private Multiverse<Type> typeVal;
  public DeclarationOrStatementValue() {
    mainValue = "";
    childPrepend = "";
    childAppend = "";
    children = null;
    switchChildren = null;
    isElse = false;
    elseString = "else";
    isDo = false;
    isDecl = false;
    isEmpty = false;
    isGotoLabel = false;
    isLabel = false;
    Label = "";
    typeVal = null;
  }
  public DeclarationOrStatementValue(String x) {
    if (x.equals("")) {
      isEmpty = true;
    } else {
      isEmpty = false;
    }
    mainValue = x;
    childPrepend = "";
    childAppend = "";
    children = null;
    switchChildren = null;
    isElse = false;
    elseString = "else";
    isDo = false;
    isDecl = false;
    isLabel = false;
    Label = "";
    isGotoLabel = false;
    isStatementAsExpression = false;
    typeVal = null;
  }

  public DeclarationOrStatementValue(DeclarationOrStatementValue x) {
    isEmpty = x.isEmpty;
    mainValue = x.mainValue;
    childPrepend = x.childPrepend;
    childAppend = x.childAppend;
    children = x.children;
    switchChildren = x.switchChildren;
    isElse = x.isElse;
    elseString = x.elseString;
    isDo = x.isDo;
    isDecl = x.isDecl;
    isLabel = x.isLabel;
    Label = x.Label;
    isGotoLabel = x.isGotoLabel;
    isStatementAsExpression = x.isStatementAsExpression;
    typeVal = x.typeVal;
  }

  public DeclarationOrStatementValue deepCopy() {
    //while this is a deepCopy, only the surface level typeVals are
    //ever going to be rewritten to.
    DeclarationOrStatementValue d = new DeclarationOrStatementValue();
    d.isEmpty = isEmpty;
    d.mainValue = mainValue;
    d.childPrepend = childPrepend;
    d.childAppend = childAppend;
    if (children != null) {
      d.children = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
      for (Multiverse<DeclarationOrStatementValue> m : children) {
        if (!m.isEmpty()) {
          Multiverse<DeclarationOrStatementValue> mv = new Multiverse<DeclarationOrStatementValue>();
          for (Element<DeclarationOrStatementValue> ev : m) {
            mv.add(ev.getData().deepCopy(),ev.getCondition());
          }
          d.children.add(mv);
        }
      }
    } else {
      d.children = null;
    }
    if (switchChildren != null) {
      d.switchChildren = new LinkedList<DeclarationOrStatementValue>();
      for (DeclarationOrStatementValue dv : switchChildren) {
        d.switchChildren.add(dv.deepCopy());
      }
    } else {
      d.switchChildren = null;
    }
    d.isElse = isElse;
    d.elseString = elseString;
    d.isDo = isDo;
    d.isDecl = isDecl;
    d.isLabel = isLabel;
    d.Label = new String(Label);
    d.isGotoLabel = isGotoLabel;
    d.isStatementAsExpression = isStatementAsExpression;
    if (typeVal != null) {
      d.typeVal = new Multiverse<Type>();
      if (!typeVal.isEmpty()) {
        for (Element<Type> e : typeVal) {
          d.typeVal.add(e.getData().copy(),e.getCondition());
        }
      }
    } else {
      d.typeVal = null;
    }
    return d;
  }

  public void setLabel(String label) {
    Label = label;
    isLabel = true;
  }

  public void setGotoLabel(String label) {
    Label = label;
    isGotoLabel = true;
  }
  
  public void setChildrenBlock(String p, Multiverse<DeclarationOrStatementValue> c, String a) {
    List x = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
    x.add(c);
    setChildrenBlock(p,x,a);
    isEmpty = false;
    setTypeFrom(c);
  }

  public void setChildrenBlock(String p, List<Multiverse<DeclarationOrStatementValue>> c, String a) {
    childPrepend = p;
    children = c;
    childAppend = a;
    isEmpty = false;
    setTypeFrom(c.get(c.size()-1));
  }

  public void setSwitchChildrenBlock(String p, List<DeclarationOrStatementValue> c, String a) {
    childPrepend = p;
    switchChildren = c;
    childAppend = a;
    isEmpty = false;
  }
  
  public void setChildrenElse(Multiverse<DeclarationOrStatementValue> a, String elseStr, Multiverse<DeclarationOrStatementValue> b) {
    isElse = true;
    elseString = elseStr;
    children = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
    children.add(a);
    children.add(b);
    isEmpty = false;
  }

  public void setDo() {
    isDo = true;
  }

  public void setDecl() {
    isDecl = true;
  }

  public boolean getEmpty() {
    return isEmpty;
  }

  public void setIsStatementAsExpression() {
    isStatementAsExpression = true;
  }

  public void nameLabels(PresenceCondition p) {
    if (isLabel) {
      addLabelInFunction(Label,p);
    }
    if (children != null && !children.isEmpty()) {
      for (Multiverse<DeclarationOrStatementValue> m : children) {
        for (Element<DeclarationOrStatementValue> e : m) {
          PresenceCondition cc = p.and(e.getCondition());
          if (cc.isNotFalse() && !cc.isSubsetOf(CContext.getParseErrorCond())) {
            e.getData().nameLabels(cc);
          }
          cc.delRef();
        }
      }
    } else if(switchChildren != null) {
      for (DeclarationOrStatementValue d : switchChildren) {
        if (p.isNotFalse() && !p.isSubsetOf(CContext.getParseErrorCond())) {
          d.nameLabels(p);
        }
      }
    }
  }

  public String getPrepend() {
    return childPrepend;
  }
  public String getAppend() {
    return childAppend;
  }
  
  public String getString(PresenceCondition p, CActions ca) {
    String ret = "";
    if (p.isSubsetOf(CContext.getParseErrorCond())) {
      return ret;
    }
    int count = 0;
    if (!isDo) {
      ret = mainValue + "\n";
    }
    if (isLabel) {
      List<String> labels = getLabelInFunction(Label,p);
      for (String s : labels) {
        ret += s + ":\n";
      }
    }
    if (isGotoLabel) {
      List<String> labels = getLabelInFunction(Label,p);
      if (labels.size() == 0) {
        ret += String.format("__static_type_error(\"%s\");\n", "invalid goto label");
      } else {
        ret += "{\n";
        for (String s : labels) {
          ret += "goto " + s + ";\n";
        }
        ret += "}\n";
      }
    }
    if (!childPrepend.equals("")) {
      ret += childPrepend + "\n";
    }
    if (!isElse) {
      if (children != null) {
        if (!isStatementAsExpression) {
          ret += "{\n";
        }
        for (Multiverse<DeclarationOrStatementValue> m : children) {
          for (Element<DeclarationOrStatementValue> e : m) {
            PresenceCondition combinedCond = e.getCondition().and(p);
            if (combinedCond.isNotFalse() && !combinedCond.isSubsetOf(CContext.getParseErrorCond())) {
              if (combinedCond.is(p) || e.getData().isDecl) {
                ret += e.getData().getString(p,ca);
              } else {
                if (!e.getData().getEmpty()) {
                  ret += "if (";
                  ret += ca.condToCVar(combinedCond);
                  ret += ") {\n";
                  ret += e.getData().getString(combinedCond, ca);
                  ret += "}\n";
                }
              }
            }
            combinedCond.delRef();
          }
        }
        if (!isStatementAsExpression) {
          ret += "}\n";
        }
      } else if (switchChildren != null) {
        for (DeclarationOrStatementValue d : switchChildren) {
          ret += d.getString(p,ca);
        }
      }
    } else {
      ret += "{\n";
      for (Element<DeclarationOrStatementValue> e : children.get(0)) {
        if (e.getCondition().and(p).isNotFalse()) {
          if (e.getCondition().is(p) || e.getData().isDecl) {
            ret += e.getData().getString(p,ca);
          } else {
            PresenceCondition combinedCond = e.getCondition().and(p);
            ret += "if (";
            ret += ca.condToCVar(combinedCond);
            ret += ") {\n";
            ret += e.getData().getString(combinedCond, ca);
            ret += "}\n";
            combinedCond.delRef();
          }
        }
      }
      ret += "}\n";
      ret += elseString;
      ret += "\n{\n";
      for (Element<DeclarationOrStatementValue> e : children.get(1)) {
        if (e.getCondition().and(p).isNotFalse()) {
          if (e.getCondition().is(p) || e.getData().isDecl) {
            ret += e.getData().getString(p,ca);
          } else {
            PresenceCondition combinedCond = e.getCondition().and(p);
            ret += "if (";
            ret += ca.condToCVar(combinedCond);
            ret += ") {\n";
            ret += e.getData().getString(combinedCond, ca);
            ret += "}\n";
            combinedCond.delRef();
          }
        }
      }
      ret += "}\n";
    }
    if (!childAppend.equals("")) {
      ret += childAppend + "\n";
    }
    if (isDo) {
      ret += mainValue + "\n";
    }
    return ret;
  }
  
  public Multiverse<List<DeclarationOrStatementValue>> separate(PresenceCondition p ) {
    return listMultiverseSwap(children,p);
  }

  private void setTypeFrom(Multiverse<DeclarationOrStatementValue> m) {
    typeVal = new Multiverse<Type>();
    for (Element<DeclarationOrStatementValue> e : m) {
      if (e.getData().typeVal != null && !e.getData().typeVal.isEmpty()) {
        Multiverse<Type> t = e.getData().typeVal.filter(e.getCondition());
        typeVal.addAll(t);
      }
    }
  }

  public void setType(Multiverse<Type> m) {
    typeVal = m;
  }

  public Multiverse<Type> getType() {
    return typeVal;
  }

  public void filterTypes(PresenceCondition p ) {
    if (typeVal != null && !typeVal.isEmpty()) {
      typeVal = typeVal.filter(p);
    }
  }

  public boolean goodSwitchCase(PresenceCondition p) {
    if (typeVal == null || typeVal.isEmpty()) {
      return true;
    }
    Multiverse<Type> subset = typeVal.filter(p);
    if (subset.isEmpty()) {
      return false;
    }
    for (Element<Type> et : subset) {
      if ((!(et.getData().resolve().isNumber() && (et.getData().hasConstant() || et.getData().hasAttribute(Constants.ATT_CONSTANT))))||(et.getData() == ErrorT.TYPE))
        return false;
    }
    return true;
  }

  public boolean hasRepeatChildName() {
    if (switchChildren == null)
      return false;
    List<String> names = new LinkedList<String>();
    for (DeclarationOrStatementValue ds : switchChildren) {
      boolean found = false;
      for (String s : names) {
        if (s.equals(ds.mainValue)) {
          return true;
        }
      }
      names.add(ds.mainValue);
    }
    return false;
  }
  
  public String toString() {
    return getString((new PresenceConditionManager()).newTrue(),new CActions()) + "Type: " + getType();
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
 * Get the semantic value of a non-static-choice node.  The caller is
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
 * Get the semantic value of a non-static-choice node.  The caller is
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
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is a multiverse.  The complete annotation
 * means the child node may be a static conditional, so create a new
 * multiverse that concatenates the multiverse values from all
 * children of the static conditional.
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A multiverse of all semantic values of the given node.
 */
private <T> Multiverse<T> getCompleteNodeMultiverseValue(Subparser subparser, int component, PresenceCondition pc) {
  return  getCompleteNodeMultiverseValue(getNodeAt(subparser, component), pc);
}

/**
 * Get a new multiverse for the semantic value of the node.  If the
 * given node is a static choice node, the resulting multiverse is the
 * combination of all the static conditional's children's semantic
 * values, filtered by their branches static condition.  The caller is
 * responsible for destructing the resulting multiverse.
 *
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new multiverse containing the semantic values for all configurations.
 */
private <T> Multiverse<T> getCompleteNodeMultiverseValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  Multiverse<T> resultmv = new Multiverse<T>();
  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  if (nodemv.isEmpty()) {
    return resultmv;
  }
  for (Element<Node> elem : nodemv) {
    Multiverse<T> nodevaluemv = (Multiverse<T>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    Multiverse<T> filtered = nodevaluemv.filter(elem.getCondition());
    resultmv.addAll(filtered);
    filtered.destruct();
  }
  nodemv.destruct();
  
  // it should not be possible to have an empty multiverse, as long as
  // the pc correponds to the current subparsers's pc.
  assert ! resultmv.isEmpty();

  if (resultmv.isEmpty()) {
    return resultmv;
  }
  
  Multiverse<T> filtered = resultmv.filter(pc);
  resultmv.destruct();
    
  assert ! filtered.isEmpty();

  return filtered;
}

/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is not a multiverse.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new multiverse that concatenates the multiverse values
 * from all children of the static conditional.
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A multiverse of all semantic values of the given node.
 */
private <T> Multiverse<T> getCompleteNodeSingleValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeSingleValue(getNodeAt(subparser, component), pc);
}

/**
 * Get a new multiverse for the semantic value of the node.  If the
 * given node is a static choice node, the resulting multiverse is the
 * combination of all the static conditional's children's semantic
 * values, filtered by their branches static condition.  The caller is
 * responsible for destructing the resulting multiverse.
 *
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new multiverse containing the semantic values for all configurations.
 */
public <T> Multiverse<T> getCompleteNodeSingleValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  Multiverse<T> resultmv = new Multiverse<T>();

  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    resultmv.add((T) ((Node) elem.getData()).getProperty(TRANSFORMATION),
                 elem.getCondition());
  }
  nodemv.destruct();
  
  // it should not be possible to have an empty multiverse, as long as
  // the pc correponds to the current subparsers's pc.
  assert ! resultmv.isEmpty();

  Multiverse<T> filtered = resultmv.filter(pc);
  resultmv.destruct();
    
  assert ! filtered.isEmpty();

  return filtered;
}

/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is a list of multiverses.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new list that concatenates the multiverse values from all
 * children of the static conditional, filtering out infeasible
 * elements along the way.
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A list of all semantic values of the given node.
 */
private <T> List<Multiverse<T>> getCompleteNodeListValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeListValue(getNodeAt(subparser, component), pc);
}

/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is a list of multiverses.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new list that concatenates the multiverse values from all
 * children of the static conditional, filtering out infeasible
 * elements along the way.
 *
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new list containing the semantic values for all configurations.
 */
private <T> List<Multiverse<T>> getCompleteNodeListValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  List<Multiverse<T>> resultlist = new LinkedList<Multiverse<T>>();
  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    PresenceCondition combinedCond = pc.and(elem.getCondition());
    List<Multiverse<T>> mvlist = (List<Multiverse<T>>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    for (Multiverse<T> mv : mvlist) {
      Multiverse<T> filtered = mv.filter(combinedCond);
      if (! filtered.isEmpty()) {
        // empty multiverse, means no feasible configs.  don't add to
        // list since empty multiverses represent an illegal state
        // during transformation
        resultlist.add(filtered);
      }
    }
    combinedCond.delRef();
  }
  nodemv.destruct();
  
  // the resulting list can be empty, e.g., of the
  // declarationorstatementlist is empty
  return resultlist;
}

/**
 * Get the nodes associated with terminals, some of these may turn to
 * a multiverse with merging.
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A list of all semantic values of the given node.
 */
private Multiverse<Syntax> getSyntaxMV(Subparser subparser, int component, PresenceCondition pc) {
  return getSyntaxMV(getNodeAt(subparser, component), pc);
}

/**
 * Get the nodes associated with terminals, some of these may turn to
 * a multiverse with merging.
 *
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new list containing the semantic values for all configurations.
 */
private Multiverse<Syntax> getSyntaxMV(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  Multiverse<Syntax> resultmv = new Multiverse<Syntax>();

  for (Element<Node> elem : nodemv) {
    resultmv.add((Syntax)elem.getData(),elem.getCondition());
  }
  nodemv.destruct();
  
  return resultmv;
}

/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is a list of multiverses.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new list that concatenates the multiverse values from all
 * children of the static conditional, filtering out infeasible
 * elements along the way.
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A list of all semantic values of the given node.
 */
private List<ExpressionValue> getCompleteNodeExpressionListValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeExpressionListValue(getNodeAt(subparser, component), pc);
}

/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is a list of multiverses.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new list that concatenates the multiverse values from all
 * children of the static conditional, filtering out infeasible
 * elements along the way.
 *
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new list containing the semantic values for all configurations.
 */
private List<ExpressionValue> getCompleteNodeExpressionListValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  List<ExpressionValue> resultlist = new LinkedList<ExpressionValue>();

  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    PresenceCondition combinedCond = pc.and(elem.getCondition());
    List<ExpressionValue> mvlist = (List<ExpressionValue>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    for (ExpressionValue exprval : mvlist) {
      resultlist.add(exprval);
      /* Multiverse<String> filtered_transformation = exprval.transformation.filter(combinedCond); */
      /* Multiverse<Type> filtered_type = exprval.type.filter(combinedCond); */
      /* if (! filtered_transformation.isEmpty() && ! filtered_type.isEmpty()) { */
      /*   // empty multiverse, means no feasible configs.  don't add to */
      /*   // list since empty multiverses represent an illegal state */
      /*   // during transformation */
      /*   resultlist.add(new ExpressionValue(filtered_transformation, filtered_type)); */
      /* } */
    }
    combinedCond.delRef();
  }
  nodemv.destruct();
  
  // the resulting list can be empty, e.g., of the
  // declarationorstatementlist is empty
  return resultlist;
}

private List<StructDeclaringListValue> getCompleteNodeStructDeclListValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeStructDeclListValue(getNodeAt(subparser, component), pc);
}
private List<StructDeclaringListValue> getCompleteNodeStructDeclListValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  List<StructDeclaringListValue> resultlist = new LinkedList<StructDeclaringListValue>();

  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    PresenceCondition combinedCond = pc.and(elem.getCondition());
    List<StructDeclaringListValue> mvlist = (List<StructDeclaringListValue>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    for (StructDeclaringListValue dvlval : mvlist) {
      resultlist.add(dvlval);
    }
    combinedCond.delRef();
  }
  nodemv.destruct();
  
  // the resulting list can be empty, e.g., of the
  // declarationorstatementlist is empty
  return resultlist;
}

private List<DeclaringListValue> getCompleteNodeDeclaringListValueList(Subparser subparser, int component) {
  return getCompleteNodeDeclaringListValueList(getNodeAt(subparser, component), subparser.getPresenceCondition());
}
private List<DeclaringListValue> getCompleteNodeDeclaringListValueList(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  List<DeclaringListValue> resultlist = new LinkedList<DeclaringListValue>();

  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    PresenceCondition combinedCond = pc.and(elem.getCondition());
    List<DeclaringListValue> mvlist = (List<DeclaringListValue>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    for (DeclaringListValue dvlval : mvlist) {
      resultlist.add(dvlval);
    }
    combinedCond.delRef();
  }
  nodemv.destruct();
  
  // the resulting list can be empty, e.g., of the
  // declarationorstatementlist is empty
  return resultlist;
}


private DeclaringListValue getCompleteNodeDeclaringListValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeDeclaringListValue(getNodeAt(subparser, component), pc);
}

private DeclaringListValue getCompleteNodeDeclaringListValue(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  DeclaringListValue resultDeclList = new DeclaringListValue(new Multiverse<TypeSpecifier>(), new Multiverse<Declarator>(),
                                                             new Multiverse<Initializer>(), new Multiverse<String>());
  if (nodemv.isEmpty()) {
    return resultDeclList;
  }
  for (Element<Node> elem : nodemv) {
    DeclaringListValue innerDecl = (DeclaringListValue) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    if (!innerDecl.isEmpty()) {
      DeclaringListValue filtered = innerDecl.filter(elem.getCondition());
      if (!filtered.isEmpty()) {
        resultDeclList.addAll(filtered);
      }
      filtered.destruct();
    }
  }
  nodemv.destruct();
  
  // it should not be possible to have an empty multiverse, as long as
  // the pc correponds to the current subparsers's pc.
  assert ! resultDeclList.isEmpty();

  if (resultDeclList.isEmpty()) {
    return resultDeclList;
  }
  
  DeclaringListValue filtered = resultDeclList.filter(pc);
  resultDeclList.destruct();
    
  return filtered;
}



/**
 * Get the semantic value for node that has a "complete" annotation
 * where the semantic value is an expression value.  The complete
 * annotation means the child node may be a static conditional, so
 * create a new expression that concatenates the expression values
 * from all children of the static conditional.
 *
 * @param subparser The subparser containing the semantic expression stack.
 * @param component The index into the semantic expression stack.
 * @param pc The presence condition of the semantic action.
 * @returns A expression value containing all semantic values of the given node.
 */
private ExpressionValue getCompleteNodeExpressionValue(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeExpressionValue(getNodeAt(subparser, component), pc);
}

/**
 * Get a new expression for the semantic value of the node.  If the
 * given node is a static choice node, the resulting expression is the
 * combination of all the static conditional's children's semantic
 * values, filtered by their branches static condition.  The caller is
 * responsible for destructing the resulting expression.
 *
 * @param node The AST node holding the semantic expression.
 * @param pc The presence condition of the semantic action.
 * @return A new expression containing the semantic values for all configurations.
 */
private ExpressionValue getCompleteNodeExpressionValue(Node node, PresenceCondition pc) {
  if (node instanceof GNode && ((GNode) node).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
    Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
    Multiverse<String> transformation = new Multiverse<String>();
    Multiverse<Type> type = new Multiverse<Type>();
    Multiverse<LineNumbers> lns = new Multiverse<LineNumbers>();
    for (Element<Node> elem : nodemv) {
      PresenceCondition combinedCond = pc.and(elem.getCondition());
      ExpressionValue exprval = (ExpressionValue) ((Node) elem.getData()).getProperty(TRANSFORMATION);
      if (!exprval.transformation.isEmpty() && !exprval.type.isEmpty() && !exprval.lines.isEmpty() ) {
        Multiverse<String> transformation_filtered = exprval.transformation.filter(combinedCond);
        Multiverse<Type> type_filtered = exprval.type.filter(combinedCond);
        Multiverse<LineNumbers> lnsfilt = exprval.lines.filter(combinedCond);
        transformation.addAll(transformation_filtered);
        type.addAll(type_filtered);
        lns.addAll(lnsfilt);
        transformation_filtered.destruct(); type_filtered.destruct(); lnsfilt.destruct();
      }
      combinedCond.delRef();
    }
    nodemv.destruct();
  
    // it should not be possible to have an empty expression, as long as
    // the pc correponds to the current subparsers's pc.
    assert ! transformation.isEmpty();
    assert ! type.isEmpty();

    return new ExpressionValue(transformation, type, lns);
  } else {
    // don't bother converting to a multiverse it it's not a conditional node
    return (ExpressionValue) getTransformationValue(node);
  }
}

/**
 *
 * @param subparser The subparser containing the semantic multiverse stack.
 * @param component The index into the semantic multiverse stack.
 * @param pc The presence condition of the semantic action.
 * @returns A list of all semantic values of the given node.
 */
private List<Multiverse<DeclarationOrStatementValue>> getCompleteNodeDeclStmtValueList(Subparser subparser, int component, PresenceCondition pc) {
  return getCompleteNodeDeclStmtValueList(getNodeAt(subparser, component), pc);
}

/**
 * Get a new expression for the semantic value of the node.  If the
 * given node is a static choice node, the resulting expression is the
 * concatination of all of the lists.  The caller is
 * responsible for destructing the resulting expression.
 * 
 * @param node The AST node holding the semantic multiverse.
 * @param pc The presence condition of the semantic action.
 * @return A new list containing the semantic values for all configurations.
 */
private List<Multiverse<DeclarationOrStatementValue>> getCompleteNodeDeclStmtValueList(Node node, PresenceCondition pc) {
  Multiverse<Node> nodemv = staticCondToMultiverse(node, pc);
  List<Multiverse<DeclarationOrStatementValue>> resultlist = new LinkedList<Multiverse<DeclarationOrStatementValue>>();

  // loop through each node, get its multiverse and add to the
  // resultmv.  update each node's multiverse elements with the static
  // conditional branch's presence condition using filter.
  for (Element<Node> elem : nodemv) {
    PresenceCondition combinedCond = pc.and(elem.getCondition());
    List<Multiverse<DeclarationOrStatementValue>> mvlist = (List<Multiverse<DeclarationOrStatementValue>>) ((Node) elem.getData()).getProperty(TRANSFORMATION);
    resultlist.addAll(mvlist);
    combinedCond.delRef();
  }
  nodemv.destruct();
  
  // the resulting list can be empty, e.g., of the
  // declarationorstatementlist is empty
  return resultlist;
}

/**
 * Just concatenates all strings in the multiverse.  Used for
 * declarations and top-level nodes where multiple configurations have
 * already been transformed by renaming declarations or surrounding
 * statements with C conditionals
 */
public String concatMultiverseStrings(Multiverse<String> value) {
  StringBuilder valuesb = new StringBuilder();
  for (Element<String> elem : value) {
    valuesb.append(elem.getData());
  }
  return valuesb.toString();
}

/**
 * Writes if (presence condition) { } around a statement, for all configurations.
 *
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
    PresenceCondition combinedCond = statement.getCondition().and(pc);
    if (! combinedCond.isFalse()) {
      // don't print at all if an infeasible configuration
      if (! combinedCond.isTrue()) {
        // don't print the C conditionals if condition is for all configurations
        sb.append("\nif (");
        sb.append(condToCVar(combinedCond));
        sb.append(") {\n");
      }
      sb.append(statement.getData());
      sb.append("\n");
      if (! combinedCond.isTrue()) {
        // don't print the C conditionals if condition is for all configurations
        sb.append("\n}");
      }
      sb.append("\n");
    }
    combinedCond.delRef();
  }
  if (allStatementConfigs.size() > 1) {
    sb.append("\n}");
  }
  return sb.toString();
}

private String getCompoundRange(Multiverse<DeclarationOrStatementValue> allStatementConfigs, PresenceCondition pc) {
  int earliest = 0;
  int latest = 0;
  for (Multiverse.Element<DeclarationOrStatementValue> statement : allStatementConfigs) {
    String leftBrace = statement.getData().getPrepend();
    String rightBrace = statement.getData().getAppend();
    int leftNum = Integer.parseInt(leftBrace.replaceAll("[^0-9]",""));
    int rightNum = Integer.parseInt(rightBrace.replaceAll("[^0-9]",""));
    if (leftNum < earliest || earliest == 0) {
      earliest = leftNum;
    }
    if (rightNum > latest || latest == 0) {
      latest = rightNum;
    }
  }
  return "L" + Integer.toString(earliest) + ":L" + Integer.toString(latest);
}

private String emitStatementDSV(Multiverse<DeclarationOrStatementValue> allStatementConfigs, PresenceCondition pc) {
  StringBuilder sb = new StringBuilder();
  if (allStatementConfigs.size() > 1) {
    sb.append("\n{");
  }
  for (Multiverse.Element<DeclarationOrStatementValue> statement : allStatementConfigs) {
    PresenceCondition combinedCond = statement.getCondition().and(pc);
    statement.getData().nameLabels(combinedCond);
    if (! combinedCond.isFalse()) {
      // don't print at all if an infeasible configuration
      if (! combinedCond.isTrue()) {
        // don't print the C conditionals if condition is for all configurations
        sb.append("\nif (");
        sb.append(condToCVar(combinedCond));
        sb.append(") {\n");
      }
      sb.append(statement.getData().getString(combinedCond,this));
      sb.append("\n");
      if (! combinedCond.isTrue()) {
        // don't print the C conditionals if condition is for all configurations
        sb.append("\n}");
      }
      sb.append("\n");
    }
    combinedCond.delRef();
  
  }
  if (allStatementConfigs.size() > 1) {
    sb.append("\n}");
  }
  return sb.toString();
}



/* /\** */
/*  * Writes nested ternary expressions to preserve configurations of an expression. */
/*  * */
/*  * @param allStatementConfigs A multiverse containing all configurations of a statement. */
/*  * @param pc The current presence condition. */
/*  * @return A String containing the transformed statement. */
/*  *\/ */
/* private String emitExpression(Multiverse<String> allStatementConfigs, PresenceCondition pc) { */
/*   StringBuilder sb = new StringBuilder(); */
/*   if (allStatementConfigs.size() > 1) { */
/*     sb.append("\n("); */
/*   } */
/*   for (Multiverse.Element<String> statement : allStatementConfigs) { */
/*     PresenceCondition combinedCond = statement.getCondition().and(pc); */
/*     if (! combinedCond.isFalse()) { */
/*       // don't print at all if an infeasible configuration */
/*       if (! combinedCond.isTrue()) { */
/*         // don't print the C conditionals if condition is for all configurations */
/*         sb.append("\nif ("); */
/*         sb.append(condToCVar(combinedCond)); */
/*         sb.append(") {\n"); */
/*       } */
/*       sb.append(statement.getData()); */
/*       if (! combinedCond.isTrue()) { */
/*         // don't print the C conditionals if condition is for all configurations */
/*         sb.append("\n}"); */
/*       } */
/*       sb.append("\n"); */
/*     } */
/*     combinedCond.delRef(); */
/*   } */
/*   if (allStatementConfigs.size() > 1) { */
/*     sb.append("\n)"); */
/*   } */
/*   return sb.toString(); */
/* } */

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
 * Given a node that may be a static conditional node, convert that
 * static choice into a multiverse of nodes.  This traverses all
 * nested static choice nodes until non-static choice nodes are
 * reached.  A normal node is just wrapped in a single-element
 * multiverse under the given condition.
 * 
 * @param node The node to convert.
 * @param presenceCondition The condition of the calling semantic action.
 * @return A multiverse of node.
 */
protected static Multiverse<Node> staticCondToMultiverse(Node node, PresenceCondition presenceCondition) {
  Multiverse<Node> allConfigs = new Multiverse<Node>();

  if (node instanceof GNode && ((GNode) node).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
    PresenceCondition pc = null;
    PresenceCondition covered = (new PresenceConditionManager()).newFalse();
    for (Object child : node) {

      if (child instanceof PresenceCondition) {
        pc = (PresenceCondition)child;
        if (!covered.isMutuallyExclusive(pc)) {
          pc = pc.and(covered.not());
        }
        covered = covered.or(pc);
      } else if (child instanceof Node) {
        // assumes that all static choice nodes are mutually exclusive and already ANDed with the subparser's pc
        Multiverse<Node> someChildren = staticCondToMultiverse((Node)child, pc);
        if (!someChildren.isEmpty()) {
          someChildren = someChildren.filter(pc);
          allConfigs.addAll(someChildren);
        }
        someChildren.destruct();
      } else {
        System.err.println("unsupported AST child type in staticCondToMultiverse");
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

  Multiverse<Node> filtered = allConfigs.filter(presenceCondition);
  allConfigs.destruct();
    
  assert ! filtered.isEmpty();

  return filtered;
}

/*****************************************************************************
 ********* Methods to record global desugaring information.  These
 ********* will go into a special initializer function defined at the
 ********* end of the transformation.
 *****************************************************************************/

/**
 * Variable renamings.
 */
private StringBuilder recordedRenamings = new StringBuilder();

/**
 * Globals with type errors.
 */
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

public String printMultiplexes(CContext scope, PresenceCondition pc) {
  String ret = "";
  for (Map.Entry<String,Multiverse<String>> m : CContext.getMultiplexes().entrySet()) {
    String originalName = m.getKey();
    while (originalName.charAt(originalName.length()-1) >= '0' && originalName.charAt(originalName.length()-1) <= '9') {
      originalName = originalName.substring(0,originalName.length()-1);
    }
    originalName = originalName.substring(2,originalName.length()-1);
    Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(originalName, pc);
    System.err.println(entries);
    for (Element<SymbolTable.Entry<Type>> entry : entries) {
      if (!entry.getData().isDeclared()) { continue; }
      Type t = entry.getData().getValue();
      if (!t.isNamedFunction()) { continue; }
      NamedFunctionT nft = t.toNamedFunction();
      if (!m.getKey().equals(nft.getName())) { continue; }
      ret += nft.printType() + " {\n";
      String params = nft.getParamNames();
      for (Element<String> plex : m.getValue()) {
        ret += String.format("if (%s) { return %s(%s); }\n",
                             condToCVar(plex.getCondition()),
                             plex.getData(),
                             params);
      }
      ret += "}\n";
    }
  }  
  return ret;
}

public String printMain(CContext scope, PresenceCondition pc) {
  String ret = "";
  ret += "int main(int argc, char **argv) {\n__static_initializer_default();\n";
  Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope("main", pc);
  for (Element<SymbolTable.Entry<Type>> entry : entries) {
    ret += "if (";
    ret += condToCVar(entry.getCondition());
    ret += ") {\n";
    if (entry.getData().isError()) {
      ret += emitError("main function error") + ";\n";
    } else if (entry.getData().isUndeclared()) {
      ret += emitError("main function undefined") + ";\n";
    } else if (!(entry.getData().getValue() instanceof FunctionOrMethodT)){
      ret += emitError("main illegally defined") + ";\n";
    } else {
      NamedFunctionT mainMethod = (NamedFunctionT) entry.getData().getValue();
      if (mainMethod.getResult().isInteger()) {
        ret += "return ";
      }
      ret +=  mainMethod.getName() + "(";
      if (mainMethod.getParameters().size() == 2) {
        ret += "argc, argv";
      }
      ret += ");\n";
      if (!mainMethod.getResult().isInteger()) {
        ret += "return 0;\n";
      }
    }  // end test of symtab entry type
    ret += "}\n";
  } // end loop over symtab entries
  ret += "return 0; }\n";
  return ret;
}

public String staticInitialization(boolean showParseError) {
  StringBuilder sb = new StringBuilder();

  String parseErrorCond = condToCVar(CContext.getParseErrorCond());
  
  // emit static initializer declaration.
  String static_initializer_name = String.format("__static_initializer_%s", unitUID);
  String static_initializer_signature = String.format("void %s()", static_initializer_name);
  sb.append(String.format("%s;\n", static_initializer_signature));
  sb.append("\n");
  
  // writes the extern declarations for the renamed preprocessor BDDs
  System.err.println("TODO: record original presence condition strings in file as well once raw strings are collected");
  for (Integer hash : condVars.keySet()) {
    //sb.append(String.format("int %s() {return rand()%%2;};\n", condVars.get(hash)));
    sb.append(String.format("extern const bool %s();\n", condVars.get(hash)));
  }

  sb.append(String.format("%s {\n%s\n%s\n",
                          static_initializer_signature,
                          recordedRenamings.toString(),
                          staticConditionRenamings.toString(),
                          invalidGlobals.toString()));
  if (showParseError && CContext.getParseErrorCond().isNotFalse()) {
  sb.append("if (" + parseErrorCond +
            ") {\n__static_parse_error(\"Unable to parse\");\n}\n");
  }

  sb.append("};\n");
  
  return sb.toString();
}
/*****************************************************************************
 ********* Methods to record external linking.  These will be used to
 ********* multiplex functions and variables with external linkage.
 ********* This will be unnecessary once configuration-aware linkage
 ********* is collected for a whole project.
 *****************************************************************************/

/**
 * The global symbols' declarations, using the original name.  This
 * holds both global and extern declarations.
 */
private SymbolTable<Declaration> externalLinkage = new SymbolTable();

/**
 * The definitions of renamed function calls to functions.  These
 * thunks defined the renamed functions as static and just call the
 * originally-named function.
 */
private StringBuilder externFunctionThunks = new StringBuilder();

/**
 * Returns true when the type specifier's storage class indicates the
 * symbol is either global (assuming that we are in the global scope)
 * or extern.  This is used to collect only those symbols that have
 * external linkage.
 *
 * @returns true if the symbol is global (no storage class) or extern.
 */
private static boolean isGlobalOrExtern(TypeSpecifier typespecifier) {
  return hasGlobalLinkage(typespecifier) || hasExternalLinkage(typespecifier);
}

/**
 * Returns true when the type specifier's storage class indicates the
 * symbol is global (assuming that we are in the global scope).  This
 * is used to collect only those symbols that have external linkage.
 *
 * @returns true if the symbol is global (no storage class).
 */
private static boolean hasGlobalLinkage(TypeSpecifier typespecifier) {
  return
    (Constants.ATT_STORAGE_EXTERN != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_STATIC != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_AUTO != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_REGISTER != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_TYPEDEF != typespecifier.getStorageClass());
}

/**
 * Returns true when the type specifier's storage class indicates the
 * symbol is extern.  This is used to collect only those symbols that
 * have external linkage.
 *
 * @returns true if the symbol is extern.
 */
private static boolean hasExternalLinkage(TypeSpecifier typespecifier) {
  return
    (Constants.ATT_STORAGE_EXTERN == typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_STATIC != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_AUTO != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_REGISTER != typespecifier.getStorageClass()
     && Constants.ATT_STORAGE_TYPEDEF != typespecifier.getStorageClass());
}

/**
 * When the declaration is global or extern, produce a desugaring that
 * just has static.
 *
 * @return A string containing the declaration with static added and
 * extern removed as needed.
 */
protected String makeStaticDeclaration(TypeSpecifier typespecifier, Declarator declarator) {
  StringBuilder sb = new StringBuilder();
  sb.append("static ");
  for (Syntax token : typespecifier.getTokens()) {
    switch (token.kind()) {
    case LANGUAGE:
      switch (((Language<CTag>) token).tag()) {
      case EXTERN:
        // remove extern
        break;
      case STATIC:
        // remove static (since we added it above)
        break;
      default:
        // otherwise, keep the type specifier the same
        sb.append(token.getTokenText());
        sb.append(" ");
        break;
      }
      break;
    default:
      // only need to print language tokens, not spacing, etc
      break;
    }
  }
  sb.append(declarator.toString());
  return sb.toString();
}

/**
 * Preserve the original function names by multiplexing the renamed
 * functions.
 *
 * @returns The multiplexed function definitions.
 */
public String linkerThunks(CContext scope, PresenceCondition pc) {
  if (! scope.isGlobal()) {
    throw new AssertionError("linker thunks should only be created for the global scope");
  }
  
  StringBuilder sb = new StringBuilder();

  // until we can support cross-compilation unit,
  // configuration-preserving linkage, we prohibit conflicting linkage
  // for global symbols, i.e., combinations of extern/global or
  // function/variable for globals is not permitted.  in the future,
  // instead of creating thunks, we can first get a list of external
  // symbols for a project, and then use that during desugaring to
  // perform renamings.
  for (String symbol : externalLinkage) {
    Declaration onedecl = null;
    Type onedecltype = null;
    StringBuilder body = new StringBuilder();
    boolean isGlobal = false;  // otherwise it's extern
    boolean isFunction = false;  // otherwise it's a variable

    Multiverse<SymbolTable.Entry<Declaration>> entries = externalLinkage.get(symbol, pc);
    for (Element<SymbolTable.Entry<Declaration>> entry : entries) {
      if (entry.getData().isDeclared()) {
        boolean hasrenaming = false;
        if (null == onedecl) {
          onedecl = entry.getData().getValue();
          onedecltype = onedecl.getType();
          if (onedecltype.isFunction()) {
            isFunction = true;
          } else {
            isFunction = false;
          }
          assert isGlobalOrExtern(onedecl.typespecifier);
          if (! onedecl.typespecifier.contains(Constants.ATT_STORAGE_EXTERN)) {
            isGlobal = true;
          } else {
            isGlobal = false;
          }
          hasrenaming = true;
        } else {
          // for now we just allow one type of the symbol to have
          // external linkage, so check that the types match.
          Declaration newdecl = entry.getData().getValue();
          Type newdecltype = newdecl.getType();
          boolean sameLinkage =
            (isGlobal && (! newdecl.typespecifier.contains(Constants.ATT_STORAGE_EXTERN))   // both are global, or
             ||
             !isGlobal && (newdecl.typespecifier.contains(Constants.ATT_STORAGE_EXTERN)))  // both are not global
            &&  // and
            (isFunction && newdecltype.isFunction()  // both a functions, or
             ||
             !isFunction && newdecltype.isVariable());  // both are not functions
            
          if (sameLinkage && cOps.equal(newdecltype, onedecltype)) {
            hasrenaming = true;
          } else {
            System.err.println(String.format("WARNING: found different types for global symbol, using the first one only:\n    - %s\n    - %s",
                                             onedecl, newdecl));
            todoReminder("support project-wide, configuration-aware linkage.");
          }
        }
        if (hasrenaming) {
          Multiverse<SymbolTable.Entry<Type>> renamingEntries = scope.getInCurrentScope(symbol, entry.getCondition());
          if (1 != renamingEntries.size()) {
            // we should be in the global scope and the symbol should
            // only have one entry, since the externalLinkage table
            // should only be updated with the regular symbol table
            throw new AssertionError("the externalLinkage and regular symtab should match presence conditions");
          }
          Type renamedType = renamingEntries.get(0).getData().getValue();
          renamingEntries = null;
          if (isFunction) {
            String renaming = ((NamedFunctionT) renamedType).getName();
            if (isGlobal) {
              body.append("if (");
              body.append(condToCVar(entry.getCondition()));
              body.append(") {\n");
              body.append(renaming);
              body.append("(");
              String delim = "";
              todoReminder("account for void or abstract declarators in linker thunk functions");
              for (Type parmtype : onedecltype.toFunction().getParameters()) {
                // function definitions must have named parameters, so
                // the parameter types should be wrapped in a
                // variablet type.
                assert parmtype.isVariable() && parmtype.toVariable().hasName();
                body.append(delim);
                body.append(parmtype.toVariable().getName());
                delim = ", ";
              }
              body.append(")");
              body.append(";\n");
              body.append("}\n");
            } else {  // it's extern
              // no need to do anything, since the declaration creates
              // the definition in externFunctionThunks
            }
          } else {  // is a variable
            if (isGlobal) {
            } else {  // it's extern
            }
          }
        }
      }
    }

    if (isFunction) {
      if (isGlobal) {
        sb.append(onedecl.toString());
        sb.append(" /* global linkage thunk */ {\n");
        sb.append(body);
        sb.append("}\n");
      } else {  // it's extern
        sb.append(onedecl.toString());
        sb.append(" /* external linkage thunk */;\n");
      }
    } else {  // is a variable
      if (isGlobal) {
        todoReminder("handle global variables");
      } else {  // it's extern
        todoReminder("handle extern variables");
      }
    }
  }


  // emit the static function definitions that make calls to
  // externally-defined functions.
  sb.append(externFunctionThunks);

  return sb.toString();
}


/*****************************************************************************
 ********* Parameters to the actions class.
 *****************************************************************************/

/** True when statistics should be output. */
private boolean languageStatistics = false;

/** Turn on error reporting. */
private static boolean showErrors = false;

/** Turn on debugging messages. */
private static boolean debug = false;

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

/*****************************************************************************
 ********* Helper functions for accesses semantic values.
 *****************************************************************************/

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

public static Map<String, Multiverse<String>> labelTable = new  HashMap<String, Multiverse<String>>();
public static int counter;

public static void restartLabelFunction() {
  for (Multiverse<String> m : labelTable.values()) {
    m.destruct();
  }
  counter = 0;
  labelTable.clear();
}

public static void addLabelInFunction(String label, PresenceCondition p) {
  if (labelTable.containsKey(label)) {
    Multiverse<String> m  = labelTable.get(label);
    Multiverse<String> nm = m.filter(p.not());
    m.destruct();
    nm.add(label + "_" + Integer.toString(counter),p);
    labelTable.replace(label,nm);
  } else {
    labelTable.put(label, new Multiverse<String>(label + "_" + Integer.toString(counter), p));
  }
  counter++;
}

public static List<String> getLabelInFunction(String label, PresenceCondition p) {
  List<String> ret = new LinkedList<String>();
  if (labelTable.containsKey(label)) {
    Multiverse<String> m  = labelTable.get(label);
    for (Element<String> e : m) {
      if (!e.getCondition().isMutuallyExclusive(p)) {
        ret.add(e.getData());
      }
    }
  }
  return ret;
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

  if (null != typespec)
    typedef = nextRelTagIsTypedef(typespec) == 2;

  if (languageStatistics && typedef) {
        Location location = subparser.lookahead.token.syntax.getLocation();
        System.err.println(String.format("typedef %s %s", ident, location));
  }
  
  if (showErrors) {
    System.err.println("bind: " + ident.getTokenText() + " " + typedef);
  }
  if (debug) {
    System.err.println("def: " + ident.getTokenText() + " " + alsoSet);
  }
  STField field = typedef ? STField.TYPEDEF : STField.IDENT;
  scope.getOldSymbolTable().setbool(ident.getTokenText(), field, true, presenceCondition);
  if (null != alsoSet) {
    scope.getOldSymbolTable().setbool(ident.getTokenText(), alsoSet, true, presenceCondition);
  }
  /* if (typedef) { */
  /*   scope.getOldSymbolTable().setbool(ident.getTokenText(), STField.TYPEDEF, true, presenceCondition); */
  /* } else { */
  /*   scope.getOldSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition); */
  /* } */
  /* scope.bind(ident.getTokenText(), typedef, presenceCondition); */
}

int nextRelTagIsTypedef(Object a)
{
  if ( ! (a instanceof Syntax)) {
    Node n = (Node) a;
    int loc = n.hasName(ForkMergeParser.CHOICE_NODE_NAME) ? 1 : 0 ;
    while (loc < n.size()) {
      if ( ! (n.get(loc) instanceof PresenceCondition)) {
        int status = nextRelTagIsTypedef(n.get(loc));
        if (status == 2 || status == 0) {
          return status;
        }
      }
      ++loc;
      //issue here is that we always assume we aren't ever sending in
      //a presence condition. However a pc can exist after something like
      //the word const.
    }
    return 1;
  } else if (a instanceof Pair) {
    int status = nextRelTagIsTypedef(((Pair)a).head());
    if (status == 2 || status == 0) {
        return status;
    }
    return nextRelTagIsTypedef(((Pair)a).tail());
  }
    
  Language t = (Language) a;
  
  if (CTag.TYPEDEF == t.tag()) {
    //binding a typedef
    return 2;
  } else if (CTag.VOLATILE == t.tag() || CTag.__VOLATILE == t.tag() || CTag.__VOLATILE__ == t.tag() ||
             CTag.CONST == t.tag() || CTag.__CONST == t.tag() || CTag.__CONST__ == t.tag() ||
             CTag.__RESTRICT == t.tag() || CTag.__RESTRICT__ == t.tag()){
    return 1;
  } else {
    // Binding a variable name.
    return 0;
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
  scope.getOldSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition);
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
  scope.getOldSymbolTable().setbool(ident, STField.IDENT, true, presenceCondition);
  /* scope.bind(ident, false, presenceCondition); */
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

private static String SPECS = "superc.core.Specifiers";

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

private Map<Integer, String> condVars = new HashMap<Integer, String>();
private StringBuilder staticConditionRenamings = new StringBuilder();

// TODO: record the string values of the condVars as well as the C
// variables.  also emit the renaming from the c var to the
// preprocessor expression it represents

private String unitUID = "default";

public String condToCVar(PresenceCondition cond) {
  if (cond.isTrue()) {
    return "1";
  } else if (cond.isFalse()) {
    return "0";
  } else {
    // TODO: traverse the (simplified) expression AST and convert
    // non-boolean leaves to C variables.
    int key = cond.toString().hashCode();
    if (condVars.containsKey(key)) {
      return condVars.get(key)+"()";
    } else {
      String cvar = freshCId(String.format("static_condition_%s", unitUID));
      condVars.put(key, cvar);
      staticConditionRenamings.append(String.format("__static_condition_renaming(\"%s\", \"%s\");\n", cvar, cond.toString()));
      return cvar+"()";
    }
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

protected static C cOps = DesugarOps.cOps;


// ---------- Declarators

/* private static String DECL = "superc.core.Declarator"; */

/* private static String NAME = "superc.core.Name"; */

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
