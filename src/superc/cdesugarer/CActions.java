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
package superc.cdesugarer;

import superc.core.SemanticActions;
import superc.core.ForkMergeParser.Subparser;

/* from desugarer.prologue */

import java.lang.StringBuilder;

import java.util.ArrayList;
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
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.IntegerT;
import xtc.type.FloatT;
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
import xtc.type.WrappedT;

 
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



/**
 * This class is generated from grammar annotations and provides semantic
 * action support.
 */
public class CActions implements SemanticActions {

  /** The instance of this class */
  private static CActions ref;

  /** Get the instance of this class */
  public static CActions getInstance() {
    if (null == ref) {
      ref = new CActions();
    }
    return ref;
  }

  public Object action(int production, Subparser subparser, Object value) {
    switch (production) {
        case 2:
    {
          Multiverse<String> extdeclmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          String result = concatMultiverseStrings(extdeclmv); extdeclmv.destruct();
          setTransformationValue(value, result); 
        }
    break;

  case 3:
    {
          setTransformationValue(value, "");
        }
    break;

  case 4:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          StringBuilder valuesb = new StringBuilder();
          Multiverse<String> listmv = getCompleteNodeSingleValue(subparser, 2, pc);
          Multiverse<String> elemmv = getCompleteNodeSingleValue(subparser, 1, pc);
          valuesb.append(concatMultiverseStrings(listmv)); listmv.destruct();
          valuesb.append(concatMultiverseStrings(elemmv)); elemmv.destruct();
          setTransformationValue(value, valuesb.toString());
        }
    break;

  case 5:
    {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
    break;

  case 6:
    {
          Multiverse<String> declmv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
    break;

  case 7:
    {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
    break;

  case 8:
    {
          Multiverse<String> declmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(declmv)); declmv.destruct();
        }
    break;

  case 9:
    {
          setTransformationValue(value, (String) getNodeAt(subparser, 1).getTokenText());
        }
    break;

  case 10:
    {
          Multiverse<String> funcmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(funcmv)); funcmv.destruct();
        }
    break;

  case 11:
    {
          Multiverse<String> funcmv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
          
          StringBuilder valuesb = new StringBuilder();
          valuesb.append(getNodeAt(subparser, 2).getTokenText());
          valuesb.append(concatMultiverseStrings(funcmv)); funcmv.destruct();
          setTransformationValue(value, valuesb.toString());
        }
    break;

  case 12:
    {
          // similar to Declaration, but different in that this has a
          // compoundstatement, while declaration has an initializer.
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // add all variations of the function declaration to the symtab
          CContext scope = (CContext)subparser.scope;

          todoReminder("don't permit extern prototypes to have a definition");

          // TODO: investigate why the function prototype can still
          // have a conditional underneath even though the complete
          // annotation isn't on functionprototype.  this is why we
          // are getting all nodes at this point
          Multiverse<Node> prototypeNodemv = staticCondToMultiverse(getNodeAt(subparser, 2), pc);
          // produce a multiverse of strings for the body to use
          Multiverse<String> prototypestrmv = new Multiverse<String>();
          // collect the set of configurations that have valid function prototypes
          PresenceCondition validCond = pc.presenceConditionManager().newFalse();
          for (Element<Node> prototypeNode : prototypeNodemv) {
            FunctionPrototypeValue prototype = (FunctionPrototypeValue) getTransformationValue(prototypeNode.getData());
            Multiverse<TypeSpecifier> typespecifiermv = prototype.typespecifier;
            Multiverse<Declarator> declaratormv = prototype.declarator;

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
                    String renaming = freshCId(originalName);
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
                    if (hasGlobalLinkage(typespecifier.getData())) {
                      // disabling the thunks for now, pending
                      // configuration-aware linking support
                      if (true) {
                        desugaredDeclaration = renamedDeclaration.toString();
                      } else {
                        desugaredDeclaration = makeStaticDeclaration(typespecifier.getData(), renamedDeclarator);
                      }
                    } else {
                      desugaredDeclaration = renamedDeclaration.toString();
                    }
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

                      // update the symbol table for this presence condition
                      scope.put(originalName, type, entry.getCondition());

                      // record the global/extern declaration using the original name for later use in handling linking
                      if (scope.isGlobal() && isGlobalOrExtern(typespecifier.getData())) {
                        externalLinkage.put(originalName, originalDeclaration, entry.getCondition());
                      }

                      // emit the renamed function as static to use the original name for linking when possible
                      /* prototypestrmv.add(renamedDeclaration.toString(), entry.getCondition()); */
                      prototypestrmv.add(desugaredDeclaration, entry.getCondition());

                      PresenceCondition newValidCond = validCond.or(entry.getCondition());
                      validCond.delRef(); validCond = newValidCond;

                      // shouldn't need to add forward decl, since if
                      // the function had a decl before, that will do
                      // the renaming.  if the function is missing a
                      // decl before def, then the function is
                      // implicitly declared to be () -> int
                      
                      /* // add the forward declaration to the scope to */
                      /* // facilitate matching of signatures for linking */
                      /* StringBuilder forward = new StringBuilder(); */
                      /* forward.append(renamedDeclaration.toString()); */
                      /* forward.append(";\n"); */
                      /* scope.addDeclaration(forward.toString()); */
                      /* forward = null; */
                      
                      recordRenaming(renaming, originalName);

                    } else {
                      if (entry.getData().getValue() instanceof NamedFunctionT) {  // there is no Type.isFunctionOrMethod()
                        FunctionT newtype = ((NamedFunctionT) type).toFunctionT();
                        FunctionT previoustype = ((NamedFunctionT) entry.getData().getValue()).toFunctionT();

                        // TODO: make sure a function is only defined
                        // once, although it can be declared multiple
                        // times.

                        // already declared entries
                        if (cOps.equal(newtype, previoustype)) {
                          System.err.println("TODO: distinguish between previous declaration vs definition.");
                          System.err.println(String.format("INFO: %s is being redeclared in global scope to compatible type", originalName));
                          String previousname = ((NamedFunctionT) entry.getData().getValue()).getName();
                          Declarator previousDeclarator = declarator.getData().rename(previousname);
                          Declaration previousDeclaration = new Declaration(typespecifier.getData(),
                                                                           previousDeclarator);
                          // emit the renamed function as static to use the original name for linking when possible
                          /* prototypestrmv.add(previousDeclaration.toString(), entry.getCondition()); */
                          prototypestrmv.add(desugaredDeclaration, entry.getCondition());

                          PresenceCondition newValidCond = validCond.or(entry.getCondition());
                          validCond.delRef(); validCond = newValidCond;
                        } else {
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
            // TODO: improve memory usage by destructing these.
            // challenge is that they are shared by nodes.
            /* typespecifiermv.destruct(); */
            /* declaratormv.destruct(); */
          } // end of check for invalid typespecifier
          // prototypestrmv may be empty if none are valid types
          if (debug) System.err.println(scope.getSymbolTable());
          prototypeNodemv.destruct();

          if (validCond.isFalse()) {
            System.err.println("INFO: no valid configuration for this definitions of %s");
          } else {
            if (prototypestrmv.isEmpty()) {
              throw new AssertionError("prototypestrmv should not be empty if validConds is not false");
            }
          }

          // change the semantic value of functionprototype to be the multiverse of strings
          //          setTransformationValue(getNodeAt(subparser, 1), prototypestrmv);
          System.err.println("PROTOTYPESTRMV " + prototypestrmv);
          System.err.println(validCond);
          System.err.println(getNodeAt(subparser, 2));
          

          
          Multiverse<String> resultmv = prototypestrmv;
          /*Node n = getNodeAt(subparser, 3);
          
          if (n.getName().equals("Conditional")) {
            resultmv = new Multiverse<String>();
            for (int i = 0; i < n.size(); ++i){
              if (n.get(i) instanceof Node) {
                System.err.println(((Node)n.get(i)).getProperty(TRANSFORMATION));
                resultmv.addAll((Multiverse<String>)((Node)n.get(i)).getProperty(TRANSFORMATION));
              }
            }
          } else {
            resultmv = (Multiverse<String>) getTransformationValue(subparser, 3);
            }*/
          /* // the function prototype can be empty if all prototypes in */
          /* // that set of configurations all have type errors */
          /* // (redeclarations, invalid types in parameters, etc).  this */
          /* // means that we can't use the regular */
          /* // getCompleteNodeMultiverseValue, which assumes all */
          /* // children are non-empty. */

          /* System.err.println("JKLFDSJ " + getNodeAt(subparser, 3)); */
          /* Multiverse<Node> prototypenodemv = staticCondToMultiverse(getNodeAt(subparser, 3), pc); */
          /* Multiverse<String> resultmv = new Multiverse<String>(); */

          /* // loop through each node, get its multiverse and add to the */
          /* // resultmv.  update each node's multiverse elements with the static */
          /* // conditional branch's presence condition using filter. */
          /* for (Element<Node> elem : prototypenodemv) { */
          /*   System.err.println("ELEM: " + elem.getData()); */
          /*   Multiverse<String> nodevaluemv = (Multiverse<String>) getTransformationValue((Node) elem.getData()); */
          /*   if (! nodevaluemv.isEmpty()) { */
          /*     Multiverse<String> filtered = nodevaluemv.filter(elem.getCondition()); */
          /*     resultmv.addAll(filtered); */
          /*     filtered.destruct(); */
          /*   } */
          /* } */
          /* prototypenodemv.destruct(); */

          StringBuilder sb = new StringBuilder();
          if (! resultmv.isEmpty()) {
            Multiverse<String> subprototypestrmv = resultmv.filter(pc);
            resultmv.destruct();
    
            /* System.err.println("PROTOTYPESTRMV2 " + prototypestrmv); */
            Multiverse<DeclarationOrStatementValue> bodymv = getCompleteNodeSingleValue(subparser, 1, subparser.getPresenceCondition());
            // declarations, including function definitions, should
            // appear unconditionally in the desugared output, since
            // renaming handles different configurations.  so add all
            // resulting definitions to a single element multiverse
            // under the true condition.

            // TODO: optimization: dedeuplicate functions that have the
            // same type.  this type deduplication maybe also be useful
            // for typechecking to find a single type eror.

            // TODO: investigate why the function prototype can still
            // have a conditional underneath even though the complete
            // annotation isn't on functionprototype.  this is why we
            // are getting all nodes at this point
            for (Element<String> prototypestr : subprototypestrmv) {
              sb.append(prototypestr.getData());
              sb.append(" {\n");
              sb.append(emitStatementDSV(bodymv, prototypestr.getCondition()));
              sb.append("\n}\n");
            }
            bodymv.destruct();
          } else {
            // the prototype can be empty if there are type errors.
            sb.append("/* no function due to type errors in the function prototype */\n");
          }
          setTransformationValue(value, sb.toString());
          
        }
    break;

  case 13:
    { ReenterScope(subparser); }
    break;

  case 14:
    { ExitScope(subparser); }
    break;

  case 15:
    {
          // TODO
          System.err.println("ERROR: unsupported semantic action: FunctionDefinition");
          System.exit(1);
        }
    break;

  case 16:
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
    break;

  case 17:
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
    break;

  case 18:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 19:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 20:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 21:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 22:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (6)");
          System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
    break;

  case 23:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (7)");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 24:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (8)");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 25:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (9)");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 26:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionPrototype (10)");
          System.exit(1);
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 27:
    {
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
          bindFunDef(subparser, null, getNodeAt(subparser, 1));
        }
    break;

  case 28:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 29:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 30:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 31:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: FunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 32:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
    break;

  case 33:
    {
        }
    break;

  case 34:
    { ReenterScope(subparser); }
    break;

  case 35:
    { ExitScope(subparser); }
    break;

  case 36:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition");
          System.exit(1);
        }
    break;

  case 37:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 38:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 39:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 40:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // legacy type checking code
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));

          setTransformationValue(value, new FunctionPrototypeValue(this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc),
                                                                   this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc)));
        }
    break;

  case 41:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(5)");
          System.exit(1);
        }
    break;

  case 42:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(6)");
          System.exit(1);
        }
    break;

  case 43:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(7)");
          System.exit(1);
        }
    break;

  case 44:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionDefinition(8)");
          System.exit(1);
        }
    break;

  case 45:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 46:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 47:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 48:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindFunDef(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          System.err.println("ERROR: unsupported semantic action: NestedFunctionOldPrototype");
          System.exit(1);
        }
    break;

  case 49:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 50:
    {
          Multiverse<String> declmv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          declmv = declmv.prependScalar(getNodeAt(subparser, 2).getTokenText(), DesugarOps.concatStrings);
          setTransformationValue(value, declmv);
        }
    break;

  case 51:
    { KillReentrantScope(subparser); }
    break;

  case 52:
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
                m = appendStringToMV(m,"}\n",typespecifier.getCondition());
              }
            }
          }
          sb.append("\n");
          m = appendStringToMV(m,"\n",pc);

          setTransformationValue(value, m);
        }
    break;

  case 53:
    { KillReentrantScope(subparser); }
    break;

  case 54:
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
                m = appendStringToMV(m,"}\n",typespecifier.getCondition());
              }
            }
          }
          sb.append("\n");
          m = appendStringToMV(m,"\n",pc);
          
          /* System.err.println(((CContext) subparser.scope).getSymbolTable()); */
          setTransformationValue(value, m);
        }
    break;

  case 55:
    { KillReentrantScope(subparser); }
    break;

  case 56:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);
          
        	List<DeclaringListValue> declaringlistvalues = (List<DeclaringListValue>) getTransformationValue(subparser, 3);
          String semi = getNodeAt(subparser, 1).getTokenText();
          Multiverse<String> valuestring = declarationAction(declaringlistvalues, semi, pc, scope);
          
          setTransformationValue(value, valuestring);
        }
    break;

  case 57:
    { KillReentrantScope(subparser); }
    break;

  case 58:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);

        	List<DeclaringListValue> declaringlistvalues = (List<DeclaringListValue>) getTransformationValue(subparser, 3);
          String semi = getNodeAt(subparser, 1).getTokenText();

          Multiverse<String> valuestring = declarationAction(declaringlistvalues, semi, pc, scope);
          
          setTransformationValue(value, valuestring);
        }
    break;

  case 59:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
        }
    break;

  case 60:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          // add the int type by default
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 6, pc);
          if (types.isEmpty()) {
            TypeSpecifier t = new TypeSpecifier();
            t.setError();
            types.add(t,pc);
          }
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(new Language<CTag>(CTag.INT));
          Multiverse<TypeSpecifier> inttbmv
            = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          types = types.product(inttbmv, DesugarOps.specifierProduct);  // don't destruct prior types, since it is a semantic value
          inttbmv.destruct();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 5, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 61:
    {
          // legacy type checking
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));  // TODO: use new bindIdent to find typedefname
        }
    break;

  case 62:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          // add the int type by default
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 6, pc);
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(new Language<CTag>(CTag.INT));
          Multiverse<TypeSpecifier> inttbmv
            = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          types = types.product(inttbmv, DesugarOps.specifierProduct);  // don't destruct prior types, since it is a semantic value
          inttbmv.destruct();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 5, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 63:
    {
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        }
    break;

  case 64:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // TODO: hoist initiazliers around the entire InitializedDeclaration
          List<DeclaringListValue> declaringlist = (List<DeclaringListValue>) getTransformationValue(subparser, 8);
          // there must be at least one element in the DeclaringList
          // according to the grammar
          assert declaringlist.size() > 0;
          // each element is given the same typespecifiermultiverse, so
          // we can take it from the first element, which is
          // guaranteed to be there.
          Multiverse<TypeSpecifier> types = declaringlist.get(0).typespecifier;
          // the rest of the action is the same as its other
          // productions, except we add to the list instead of making
          // a new one
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 5, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 65:
    {
          saveBaseType(subparser, getNodeAt(subparser, 5));
          bindIdent(subparser, getNodeAt(subparser, 5), getNodeAt(subparser, 4));  // TODO: use new bindIdent to find typedefname
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 5, pc);
          if (types.isEmpty()) {
            TypeSpecifier t = new TypeSpecifier();
            t.setError();
            types.add(t,pc);
          }
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 4, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 66:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 5), getNodeAt(subparser, 4));  // TODO: use new bindIdent to find typedefname

          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 5, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 4, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          List<DeclaringListValue> declaringlist = new LinkedList<DeclaringListValue>();
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 67:
    {
          // legacy type checking
          // reuses saved base type
          bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 1));
        }
    break;

  case 68:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          // TODO: hoist initiazliers around the entire InitializedDeclaration
          List<DeclaringListValue> declaringlist = (List<DeclaringListValue>) getTransformationValue(subparser, 8);
          // there must be at least one element in the DeclaringList
          // according to the grammar
          assert declaringlist.size() > 0;
          // each element is given the same typespecifiermultiverse, so
          // we can take it from the first element, which is
          // guaranteed to be there.
          Multiverse<TypeSpecifier> types = declaringlist.get(0).typespecifier;
          // the rest of the action is the same as its other
          // productions, except we add to the list instead of making
          // a new one
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 5, pc);
          // TODO: just represent assembly and attributes as strings that get pass with the declaration object
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          declaringlist.add(new DeclaringListValue(types, declarators, initializers));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 69:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
        	Multiverse<TypeSpecifier> decl = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
	  			setTransformationValue(value, decl);
				}
    break;

  case 70:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
    break;

  case 71:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
    break;

  case 72:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
    break;

  case 73:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
    break;

  case 74:
    {
          // TODO: are there any issues with sharing references to the same type builder object?
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
    break;

  case 75:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> t = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
        	setTransformationValue(value,t);
				}
    break;

  case 76:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
    break;

  case 77:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
    break;

  case 78:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
				}
    break;

  case 79:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  setTransformationValue(value, storage);
      	  updateSpecs(subparser,
          getSpecsAt(subparser, 1),
          value);
      	}
    break;

  case 80:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
      	  Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  Multiverse<TypeSpecifier> tb = qualList.product(storage, DesugarOps.specifierProduct);
          setTransformationValue(value, tb);
      	  updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
      	}
    break;

  case 81:
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
    break;

  case 82:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
      	  setTransformationValue(value, qual);
    	    updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
      	}
    break;

  case 83:
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
    break;

  case 84:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qual = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, qual);
        }
    break;

  case 85:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> storage = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, storage);
        }
    break;

  case 86:
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
    break;

  case 87:
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
    break;

  case 88:
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
    break;

  case 89:
    {
          TypeSpecifier ts = new TypeSpecifier();
          todoReminder("collect attributes in AttributeSpecifier");
          Multiverse<TypeSpecifier> valuemv = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);
          updateSpecs(subparser,
                      getSpecsAt(subparser, 1),
                      value);
        }
    break;

  case 90:
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
    break;

  case 91:
    {
        }
    break;

  case 92:
    {
        }
    break;

  case 93:
    {
        }
    break;

  case 94:
    {
        }
    break;

  case 95:
    {
        }
    break;

  case 96:
    {
        }
    break;

  case 97:
    {
        }
    break;

  case 98:
    {
        }
    break;

  case 99:
    {
        }
    break;

  case 100:
    {
        }
    break;

  case 101:
    {
        }
    break;

  case 102:
    {
        }
    break;

  case 103:
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
    break;

  case 104:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

	        Multiverse<TypeSpecifier> qualList = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> basicTypeName = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);

          // combine the partial type specs
          Multiverse<TypeSpecifier> tb = qualList.product(basicTypeName, DesugarOps.specifierProduct);

	        setTransformationValue(value, tb);
	        updateSpecs(subparser,
                      getSpecsAt(subparser, 2),
                      getSpecsAt(subparser, 1),
                      value);
        }
    break;

  case 105:
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
    break;

  case 106:
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
    break;

  case 107:
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
    break;

  case 108:
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
    break;

  case 109:
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
    break;

  case 110:
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
    break;

  case 111:
    {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 112:
    {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          /* System.err.println(getNodeAt(subparser, 2)); */
          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 113:
    {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 114:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

        	setTransformationValue(value,
            this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 115:
    {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 116:
    {
          // TODO: unit test this action
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 117:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

      	  Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 118:
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
    break;

  case 119:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<TypeSpecifier> tbF = tb.product(tb1, DesugarOps.specifierProduct);
          setTransformationValue(value, tbF);
        }
    break;

  case 120:
    {
      	  String typeName = getStringAt(subparser, 1);
          // look up the typedef name
          Multiverse<SymbolTable.Entry<Type>> entries
            = ((CContext)subparser.scope).getInAnyScope(typeName, subparser.getPresenceCondition());
          // expand all renamings of the typedefname and handle type errors
          Multiverse<TypeSpecifier> typedefnametbmv = DesugarOps.typedefEntriesToTypeSpecifier.transform(entries);
          setTransformationValue(value, typedefnametbmv);
        }
    break;

  case 121:
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
    break;

  case 122:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 123:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
    break;

  case 124:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
    break;

  case 125:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
    break;

  case 126:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofDeclarationSpecifier");
          System.exit(1);
        }
    break;

  case 127:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
    break;

  case 128:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
    break;

  case 129:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
    break;

  case 130:
    {
          System.err.println("ERROR: unsupported semantic action: TypeofTypeSpecifier");
          System.exit(1);
        }
    break;

  case 131:
    {
          System.err.println("ERROR: unsupported semantic action: Typeofspecifier");
          System.exit(1);
        }
    break;

  case 132:
    {
          System.err.println("ERROR: unsupported semantic action: Typeofspecifier");
          System.exit(1);
        }
    break;

  case 133:
    {
          System.err.println("ERROR: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
    break;

  case 134:
    {
          System.err.println("ERROR: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
    break;

  case 135:
    {
          System.err.println("ERROR: unsupported semantic action: Typeofkeyword");
          System.exit(1);
        }
    break;

  case 136:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 137:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 138:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 139:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 140:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

					setTransformationValue(value,this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 141:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 142:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 143:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> tb = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<TypeSpecifier> tb1 = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, tb.product(tb1, DesugarOps.specifierProduct));
        }
    break;

  case 144:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitVarArgListSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> tb = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, tb);
        }
    break;

  case 145:
    {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitTypedefSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_TYPEDEF;
        }
    break;

  case 146:
    {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitExternSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_EXTERN;
        }
    break;

  case 147:
    {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitStaticSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_STATIC;
        }
    break;

  case 148:
    {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitAutoSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_AUTO;
        }
    break;

  case 149:
    {
          String storageName = getNodeAt(subparser, 1).getTokenText();
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitRegisterSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> storage = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, storage);
          getSpecsAt(subparser, 1).storage = Constants.ATT_STORAGE_REGISTER;
        }
    break;

  case 150:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitVoidTypeSpecifier();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).type = VoidT.TYPE;

        }
    break;

  case 151:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitChar();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenChar = true;
        }
    break;

  case 152:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitShort();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenShort = true;
        }
    break;

  case 153:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenInt = true;
        }
    break;

  case 154:
    {
          // TODO: support int128 in typespecifier
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitInt();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenInt = true;
        }
    break;

  case 155:
    {
          // See xtc.type.* for the class hiearchy for types
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitLong();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).longCount++;
        }
    break;

  case 156:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitFloat();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenFloat = true;
        }
    break;

  case 157:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitDouble();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenDouble = true;
        }
    break;

  case 158:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitSigned();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenSigned = true;
        }
    break;

  case 159:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitUnsigned();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenUnsigned = true;
        }
    break;

  case 160:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitBool();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenBool = true;
        }
    break;

  case 161:
    {
          TypeSpecifier ts = new TypeSpecifier();
          ts.visitComplex();
          ts.addTransformation(((Syntax) getNodeAt(subparser, 1).get(0)));
          Multiverse<TypeSpecifier> type = new Multiverse<TypeSpecifier>(ts, subparser.getPresenceCondition());
          setTransformationValue(value, type);

          getSpecsAt(subparser, 1).seenComplex = true;
        }
    break;

  case 167:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
        	setTransformationValue(value, this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 168:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
        	setTransformationValue(value, this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 169:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = (Syntax) getNodeAt(subparser, 5);
          // TODO: add attributes to type spec
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          String structTag = freshCId("anonymous_tag");
          
          String renamedTag = structTag;
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, renamedTag, structfields, pc, scope, freshIdCreator, suTypeCreator);
          setTransformationValue(value, valuemv);
        }
    break;

  case 170:
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
            = DesugarOps.processStructDefinitionMV(keyword, structTag, this, structfields, pc, scope, freshIdCreator, suTypeCreator);
          setTransformationValue(value, valuemv);
        }
    break;

  case 171:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
         
          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          // get the renaming of the tag
          String renamedTag = freshCId(structTag);
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, renamedTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 172:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 173:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 174:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;
          
          Syntax keyword = (Syntax) getNodeAt(subparser, 5);
          // TODO: add attributes to type spec
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          String structTag = freshCId("anonymous_tag");
          
          String renamedTag = structTag;
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, renamedTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 175:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          // get the renaming of the tag
          String renamedTag = freshCId(structTag);
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, renamedTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 176:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 6);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          List<Multiverse<Declaration>> structfields = this.<Declaration>getCompleteNodeListValue(subparser, 2, pc);

          // get the renaming of the tag
          String renamedTag = freshCId(structTag);
          
          Multiverse<TypeSpecifier> valuemv
            = DesugarOps.processStructDefinition(keyword, structTag, renamedTag, structfields, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 177:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 178:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = (CContext)subparser.scope;

          Syntax keyword = (Syntax) getNodeAt(subparser, 3);
          // TODO: add attributes to type spec
          String structTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processStructReference(keyword, structTag, pc, scope, freshIdCreator, suTypeCreator);

          setTransformationValue(value, valuemv);
        }
    break;

  case 179:
    {
          ((Node) value).setProperty(SPECS, new Specifiers()); // legacy type checking

          setTransformationValue(value, new LinkedList<Multiverse<Declaration>>());
        }
    break;

  case 180:
    {
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
    break;

  case 181:
    {
          // TODO: implement like Declaration, except return a
          // multiverse of declarations instead of strings
          
        	List<StructDeclaringListValue> declaringlistvalues = (List<StructDeclaringListValue>) getTransformationValue(subparser, 2);

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
    break;

  case 182:
    {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (2)");
          System.exit(1);
        }
    break;

  case 183:
    {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (3)");
          System.exit(1);
        }
    break;

  case 184:
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
    break;

  case 185:
    {
          System.err.println("ERROR: unsupported semantic action: StructDeclaration (5)");
          System.exit(1);
        }
    break;

  case 186:
    {
          System.err.println("ERROR: unsupported semantic action: StructDefaultDeclaringList (1)");
          System.exit(1);
        }
    break;

  case 187:
    {
          System.err.println("ERROR: unsupported semantic action: StructDefaultDeclaringList (2)");
          System.exit(1);
        }
    break;

  case 188:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          List<StructDeclaringListValue> declaringlist = new LinkedList<StructDeclaringListValue>();
          Multiverse<TypeSpecifier> typespecifiers = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 3, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          System.err.println("TODO: support attribuetspecifierlistopt in StructDeclarator");
          declaringlist.add(new StructDeclaringListValue(typespecifiers, declarators));
          setTransformationValue(value, declaringlist);
        }
    break;

  case 189:
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
    break;

  case 190:
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
    break;

  case 191:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          // pass along the bitfieldsize declarator by itself
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 192:
    {
          System.err.println("ERROR: unsupported semantic action: StructIdentifierDeclarator");
          System.exit(1);
        }
    break;

  case 193:
    {
          System.err.println("ERROR: unsupported semantic action: StructIdentifierDeclarator");
          System.exit(1);
        }
    break;

  case 194:
    {
          setTransformationValue(value, new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition()));
        }
    break;

  case 195:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          // pass along the bitfieldsize declarator by itself
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 196:
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
    break;

  case 197:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          // TODO: add attributes to type spec
          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 1),
                                                                                                  subparser.getPresenceCondition());
          String enumTag = freshCId("anonymous_tag");

          CContext scope = (CContext)subparser.scope;

          PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
          PresenceCondition validCond = pc.presenceConditionManager().newFalse();
          for (Multiverse<EnumeratorValue> ratormv : list) {
            for (Element<EnumeratorValue> rator : ratormv) {
              if (rator.getData().getType().isError()) {
                PresenceCondition newerrorCond = errorCond.or(rator.getCondition());
                errorCond.delRef(); errorCond = newerrorCond;
              } else {
                PresenceCondition newvalidCond = validCond.or(rator.getCondition());
                validCond.delRef(); validCond = newvalidCond;
                scope.putEnumerator(enumTag, rator.getData().getTransformation());
                // enumeratorlist.add(rator.getData().getType().toEnumerator());  // no longer storing enumerators with enum type
              }
            }  // end ratormv
          } // end list

          Multiverse<TypeSpecifier> typespecmv = new Multiverse<TypeSpecifier>();

          if (validCond.isNotFalse()) {
            TypeSpecifier typespec = new TypeSpecifier();
            // TODO: get largest type for enum (gcc), instead of ISO standard of int
            Type enumreftype = new EnumT(enumTag);
            typespec.setType(enumreftype);

            typespec.addTransformation(keyword);
            typespec.addTransformation(new Text<CTag>(CTag.IDENTIFIER, enumTag));

            typespecmv.add(typespec, validCond);

            /* scope.put(CContext.toTagName(enumTag), enumreftype, validCond); */
          }
          validCond.delRef();

          if (errorCond.isNotFalse()) {
            TypeSpecifier typespecifier = new TypeSpecifier();
            typespecifier.setType(ErrorT.TYPE);
            typespecmv.add(typespecifier, errorCond);

            /* scope.putError(CContext.toTagName(enumTag), errorCond); */
          }
          errorCond.delRef();

          assert ! typespecmv.isEmpty();

          todoReminder("support gcc's enums larger than ISO C's int");
          // TODO: check whether the list of enums are all errors ornot
                    
          setTransformationValue(value, typespecmv);
        }
    break;

  case 198:
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

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumDefinition(keyword, enumTag, list, pc, scope);
          
          setTransformationValue(value, valuemv);
        }
    break;

  case 199:
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
          
          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumDefinition(keyword, enumTag, list, pc, scope);
          
          setTransformationValue(value, valuemv);
        }
    break;

  case 200:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          // TODO: add attributes to type spec

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumReference(keyword, enumTag, pc);
          
          setTransformationValue(value, valuemv);
        }
    break;

  case 201:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Syntax keyword = ((Syntax) getNodeAt(subparser, 3));
          Multiverse<String> attrs = this.<String>getCompleteNodeMultiverseValue(getNodeAt(subparser, 2),
                                                                                 subparser.getPresenceCondition());
          String enumTag = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          // TODO: add attributes to type spec

          Multiverse<TypeSpecifier> valuemv = DesugarOps.processEnumReference(keyword, enumTag, pc);
          
          setTransformationValue(value, valuemv);
        }
    break;

  case 202:
    {
          setTransformationValue(value, this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 2),
                                                                                       subparser.getPresenceCondition()));
        }
    break;

  case 203:
    {
          setTransformationValue(value, this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 3),
                                                                                       subparser.getPresenceCondition()));
        }
    break;

  case 204:
    {
          List<Multiverse<EnumeratorValue>> list = new LinkedList<Multiverse<EnumeratorValue>>();
          Multiverse<EnumeratorValue> enumerator
            = (Multiverse<EnumeratorValue>) this.<EnumeratorValue>getCompleteNodeMultiverseValue(subparser,
                                                                                                 1,
                                                                                                 subparser.getPresenceCondition());
          list.add(enumerator);
          setTransformationValue(value, list);
        }
    break;

  case 205:
    {
          List<Multiverse<EnumeratorValue>> list = this.<EnumeratorValue>getCompleteNodeListValue(getNodeAt(subparser, 3),
                                                                                                  subparser.getPresenceCondition());
          Multiverse<EnumeratorValue> enumerator
            = (Multiverse<EnumeratorValue>) this.<EnumeratorValue>getCompleteNodeMultiverseValue(subparser,
                                                                                                 1,
                                                                                                 subparser.getPresenceCondition());
          list.add(enumerator);
          setTransformationValue(value, list);
        }
    break;

  case 206:
    { BindEnum(subparser); }
    break;

  case 207:
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
                Type ratorbasetype = NumberT.INT;
                Type ratortype = new EnumeratorT(ratorbasetype, renaming, BigInteger.ONE);  // TODO: use real values if needed
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
    break;

  case 208:
    { BindEnum(subparser); }
    break;

  case 209:
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
    break;

  case 210:
    {
          
          setTransformationValue(value, new Multiverse<EnumeratorValValue>(new EnumeratorValValue(), subparser.getPresenceCondition()));
        }
    break;

  case 211:
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
    break;

  case 212:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<Declaration>> paramlist = this.<Declaration>getCompleteNodeListValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterTypeListValue(paramlist, false));
        }
    break;

  case 213:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<Declaration>> paramlist = this.<Declaration>getCompleteNodeListValue(subparser, 3, pc);
          setTransformationValue(value, new ParameterTypeListValue(paramlist, true));
        }
    break;

  case 214:
    {
          // create a new list
          List<Multiverse<Declaration>> parameters
            = new LinkedList<Multiverse<Declaration>>();
          Multiverse<Declaration> declarationvalue
            = (Multiverse<Declaration>) getTransformationValue(subparser,1);
          parameters.add(declarationvalue);
          setTransformationValue(value, parameters);
        }
    break;

  case 215:
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
    break;

  case 216:
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
    break;

  case 217:
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
    break;

  case 218:
    {
          System.err.println("TODO: reimplement parameterabstractdeclaration (1)");
          System.exit(1);
        }
    break;

  case 219:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 220:
    {
          System.err.println("TODO: reimplement parameterabstractdeclaration (3)");
          System.exit(1);
        }
    break;

  case 221:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 222:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarators = new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 223:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 224:
    {
          System.err.println("TODO: reimplement parameterabstractdeclaration (7)");
          System.exit(1);
        }
    break;

  case 225:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 226:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 227:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 228:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 229:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 230:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 231:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 232:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 233:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 234:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 235:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 236:
    {
          saveBaseType(subparser, getNodeAt(subparser, 2));
          bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
        }
    break;

  case 237:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> types = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 4, pc);
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 3, pc);
          // TODO: save attributes
          setTransformationValue(value, new ParameterDeclarationValue(types, declarators));
        }
    break;

  case 238:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 239:
    {
          System.err.println("ERROR: unsupported semantic action: IdentifierList");
          System.exit(1);
        }
    break;

  case 240:
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
    break;

  case 241:
    {
          // get token text from the parent
        }
    break;

  case 242:
    {
          // get token text from the parent
        }
    break;

  case 243:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarator
            = (Multiverse<Declarator>) new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
          declarator.destruct();
        }
    break;

  case 244:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
        }
    break;

  case 245:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> declarator
            = (Multiverse<Declarator>) new Multiverse<Declarator>(new EmptyDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
          declarator.destruct();
        }
    break;

  case 246:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> type = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> declarator = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          setTransformationValue(value, type.join(declarator, DesugarOps.joinDeclaration));
        }
    break;

  case 247:
    {
          // EmptyInitializer
          setTransformationValue(value, new Multiverse<Initializer>(new EmptyInitializer(),
                                                                    subparser.getPresenceCondition()));
        }
    break;

  case 248:
    {
          // AssignmentInitializer
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          setTransformationValue(value, DesugarOps.toAssignInitializer.transform(initializers));
        }
    break;

  case 249:
    {
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 2);
          setTransformationValue(value, DesugarOps.toInitializerList.transform(lists));
        }
    break;

  case 250:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 3);
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform((Multiverse<Initializer>) getTransformationValue(subparser, 2));
          System.err.println(getTransformationValue(subparser, 2));
          Multiverse<List<Initializer>> cproduct = lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT);
          //lists.destruct(); newelem.destruct();
          setTransformationValue(value, DesugarOps.toInitializerList.transform(cproduct));
        }
    break;

  case 251:
    {
          // ExpressionInitializer
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition());
          /* System.err.println(exprval.type); */
          /* System.err.println(exprval.transformation); */
          setTransformationValue(value, exprval.type.join(exprval.transformation, DesugarOps.joinExpressionInitializer));
        }
    break;

  case 252:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          // TODO: destruct return value from getTransformationValue
          setTransformationValue(value, (Multiverse<InitializerList>) getTransformationValue(subparser, 1));
        }
    break;

  case 253:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 2);
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform((Multiverse<Initializer>) getTransformationValue(subparser, 1));
          setTransformationValue(value, lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT));
          newelem.destruct();
        }
    break;

  case 254:
    {
          setTransformationValue(value, new Multiverse<List>(new LinkedList<Initializer>(),
                                                                  subparser.getPresenceCondition()));
        }
    break;

  case 255:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<List<Initializer>> lists = (Multiverse<List<Initializer>>) getTransformationValue(subparser, 3);
          Multiverse<List<Initializer>> newelem
            = DesugarOps.initializerListWrap.transform((Multiverse<Initializer>) getTransformationValue(subparser, 2));
          setTransformationValue(value, lists.complementedProduct(newelem, DesugarOps.INITIALIZERLISTCONCAT));
          newelem.destruct();
        }
    break;

  case 256:
    {
          // pass through
          todoReminder("typecheck initializers DesignatedInitializer (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          Multiverse<Initializer> mv = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          setTransformationValue(value, mv);
        }
    break;

  case 257:
    {
          // DesignatedInitializer
          Multiverse<Designation> designations = (Multiverse<Designation>) getTransformationValue(subparser, 2);
          Multiverse<Initializer> initializers = (Multiverse<Initializer>) getTransformationValue(subparser, 1);
          setTransformationValue(value, designations.join(initializers, DesugarOps.joinDesignatedInitializer));
        }
    break;

  case 258:
    {
          // TODO: unit tests
          Multiverse<List<Designator>> list = (Multiverse<List<Designator>>) getTransformationValue(subparser, 2);
          setTransformationValue(value, DesugarOps.toDesignation.transform(list));
        }
    break;

  case 259:
    {
          System.err.println("ERROR: unsupported semantic action: Designation (2)");
          System.exit(1);
        }
    break;

  case 260:
    {
          System.err.println("ERROR: unsupported semantic action: Designation (3)");
          System.exit(1);
        }
    break;

  case 261:
    {
          // TODO: unit tests
          Multiverse<Designator> designators = (Multiverse<Designator>) getTransformationValue(subparser, 1);
          Multiverse<List<Designator>> newlist = DesugarOps.designatorListWrap.transform(designators);
          setTransformationValue(value, newlist);
        }
    break;

  case 262:
    {
          // TODO: unit tests
          Multiverse<List<Designator>> list = (Multiverse<List<Designator>>) getTransformationValue(subparser, 2);
          Multiverse<Designator> designators = (Multiverse<Designator>) getTransformationValue(subparser, 1);
          Multiverse<List<Designator>> newlist = DesugarOps.designatorListWrap.transform(designators);
          setTransformationValue(value, list.complementedProduct(newlist, DesugarOps.DESIGNATORLISTCONCAT));
          newlist.destruct();
        }
    break;

  case 263:
    {
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          setTransformationValue(value,
                                 exprval.type.join(exprval.transformation, DesugarOps.joinArrayDesignator));
        }
    break;

  case 264:
    {
          System.err.println("ERROR: unsupported semantic action: Designator (2)");
          System.exit(1);
        }
    break;

  case 265:
    {
          todoReminder("replace the designator with the renamed struct field");
          setTransformationValue(value,
                                 new Multiverse<Designator>(new StructUnionDesignator(((Syntax) getNodeAt(subparser, 1)).getTokenText()),
                                                            subparser.getPresenceCondition()));
        }
    break;

  case 266:
    {
          todoReminder("replace the designator with the renamed struct field");
          setTransformationValue(value,
                                 new Multiverse<Designator>(new StructUnionDesignator(((Syntax) getNodeAt(subparser, 1)).getTokenText()),
                                                            subparser.getPresenceCondition()));
        }
    break;

  case 267:
    {
          System.err.println("ERROR: unsupported semantic action: ObsoleteArrayDesignation");
          System.exit(1);
        }
    break;

  case 268:
    {
          System.err.println("ERROR: unsupported semantic action: ObsoleteArrayDesignation");
          System.exit(1);
        }
    break;

  case 269:
    {
          System.err.println("ERROR: unsupported semantic action: ObsoleteFieldDesignation");
          System.exit(1);
        }
    break;

  case 270:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 271:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 272:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 273:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 274:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 275:
    {
          System.err.println("TODO: do we need to expand all possible typedef names here? parametertypedefdeclarator");
          Multiverse<Declarator> valuemv = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 1)), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
    break;

  case 276:
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
    break;

  case 277:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 278:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 279:
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
    break;

  case 280:
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
    break;

  case 281:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 282:
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
    break;

  case 283:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 284:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
    break;

  case 285:
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
    break;

  case 286:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
    break;

  case 287:
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
    break;

  case 288:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 289:
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
    break;

  case 290:
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
    break;

  case 291:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 292:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 293:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 294:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 295:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 296:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 297:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
      	}
    break;

  case 298:
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
    break;

  case 299:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 300:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 301:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 302:
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
    break;

  case 303:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 304:
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
    break;

  case 305:
    { EnterScope(subparser); }
    break;

  case 306:
    { ExitReentrantScope(subparser); }
    break;

  case 307:
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
    break;

  case 308:
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
    break;

  case 309:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 310:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
      	}
    break;

  case 311:
    {
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new SimpleDeclarator(getStringAt(subparser, 1)), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
    break;

  case 312:
    {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
        }
    break;

  case 313:
    {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
        }
    break;

  case 314:
    {
          System.err.println("OldFunctionDecl not supported");
          System.exit(1);
        }
    break;

  case 315:
    { EnterScope(subparser); }
    break;

  case 316:
    { ExitReentrantScope(subparser); }
    break;

  case 317:
    {
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
    break;

  case 318:
    {
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
    break;

  case 319:
    {
          System.err.println("ERROR: unsupported semantic action: PostfixOldFunctionDeclarator");
          System.exit(1);
        }
    break;

  case 320:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 321:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 322:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 323:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
      	}
    break;

  case 324:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 325:
    {
          setTransformationValue(value, new ParameterTypeListValue(new LinkedList<Multiverse<Declaration>>(), false));
        }
    break;

  case 326:
    {
          setTransformationValue(value, (ParameterTypeListValue) getTransformationValue(subparser,1));
        }
    break;

  case 327:
    {
          String expression = "";
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new ArrayAbstractDeclarator(expression), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);;
        }
    break;

  case 328:
    {
          todoReminder("check expression in ArrayAbstractDeclarator (2)");
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          Multiverse<String> arrayBounds = exprval.transformation;
          System.err.println(exprval);
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
    break;

  case 329:
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
              System.err.println(t.getClass());
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
    break;

  case 330:
    {
          Multiverse<Declarator> valuemv
            = new Multiverse<Declarator>(new PointerAbstractDeclarator(), subparser.getPresenceCondition());
          setTransformationValue(value, valuemv);
        }
    break;

  case 331:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<TypeSpecifier> qualifierlists = this.<TypeSpecifier>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toQualifiedPointerAbstractDeclarator.transform(qualifierlists);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
    break;

  case 332:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
          Multiverse<Declarator> declarators = this.<Declarator>getCompleteNodeMultiverseValue(subparser, 1, pc);
          Multiverse<Declarator> valuemv = DesugarOps.toPointerDeclarator.transform(declarators);
          Multiverse<Declarator> filtered = valuemv.filter(subparser.getPresenceCondition());
          valuemv.destruct();
          /* declarators.destruct(); */
          setTransformationValue(value, filtered);
        }
    break;

  case 333:
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
    break;

  case 334:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 335:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 336:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          
      	  setTransformationValue(value, this.<Declarator>getCompleteNodeMultiverseValue(subparser, 2, pc));
        }
    break;

  case 337:
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
    break;

  case 338:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 339:
    {
          // CompoundStatement produces just a string (not a multiverse), since it's children resolve all
          // configurations, so we only need to resolve static conditionals around the CompoundStatement.
          setTransformationValue(value, getCompleteNodeSingleValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 340:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 341:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 342:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 343:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 344:
    {
          setTransformationValue(value, getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition()));
        }
    break;

  case 345:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          String ident = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          String colon = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          String prefix = String.format("%s %s", ident, colon);
          // TODO: save attributes
          Multiverse<DeclarationOrStatementValue>  stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue(prefix);
          dsv.setChildrenBlock("",stmtmv,"");
          Multiverse<DeclarationOrStatementValue> dsvm = new Multiverse<DeclarationOrStatementValue>(dsv,pc);
                    
          setTransformationValue(value, dsvm);
        }
    break;

  case 346:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          String ident = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          String colon = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          String prefix = String.format("%s %s", ident, colon);
          // TODO: save attributes
          Multiverse<DeclarationOrStatementValue>  stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue(prefix);
          dsv.setChildrenBlock("",stmtmv,"");
          Multiverse<DeclarationOrStatementValue> dsvm = new Multiverse<DeclarationOrStatementValue>(dsv,pc);

          setTransformationValue(value, dsvm);
        }
    break;

  case 347:
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
          }
          
          setTransformationValue(value, dsv);
        }
    break;

  case 348:
    {
          todoReminder("check that case expression is int");
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: SwitchLabeledStatement (2)");
          System.exit(1);
        }
    break;

  case 349:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          String defaultstr = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          String colonstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          /* Multiverse<String> stmt = getCompleteNodeMultiverseValue(subparser, 1, pc); */
          DeclarationOrStatementValue d = new DeclarationOrStatementValue(defaultstr + colonstr);
          d.setChildrenBlock("",(List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 1),"");
          Multiverse<DeclarationOrStatementValue> dsv = new Multiverse<DeclarationOrStatementValue>();
          dsv.add(d, pc);          
          setTransformationValue(value, dsv);
        
        }
    break;

  case 350:
    {
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, subparser.getPresenceCondition());
          List<Multiverse<DeclarationOrStatementValue>> l = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          l.add(stmtmv);
          setTransformationValue(value, l);
        }
    break;

  case 351:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<DeclarationOrStatementValue>> list = getCompleteNodeDeclStmtValueList(subparser, 2, pc);
          Multiverse<DeclarationOrStatementValue> elem = getCompleteNodeMultiverseValue(subparser, 1, pc);
          list.add(elem);
          setTransformationValue(value, list);
          pc.delRef();
        }
    break;

  case 352:
    { ReenterScope(subparser); }
    break;

  case 353:
    {   ExitScope(subparser); }
    break;

  case 354:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          CContext scope = ((CContext) subparser.scope);
          
          List<Multiverse<DeclarationOrStatementValue>> body = (List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 3);
          StringBuilder valuesb = new StringBuilder();
          DeclarationOrStatementValue dsv = new DeclarationOrStatementValue("");
          dsv.setChildrenBlock("{",body,"}");

          setTransformationValue(value, dsv);
        }
    break;

  case 355:
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
    break;

  case 356:
    {
          setTransformationValue(value, "");
        }
    break;

  case 357:
    {
          System.err.println("implement locallabeldeclarationlistopt (2)");
          // do hoisting here, return a stringbuilder, not a multiverse
          System.exit(1);
        }
    break;

  case 358:
    {
          System.err.println("implement locallabeldeclarationlist (1)");
          System.exit(1);
        }
    break;

  case 359:
    {
          System.err.println("implement locallabeldeclarationlist (2)");
          System.exit(1);
        }
    break;

  case 360:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: LocalLabelDeclaration");
          System.exit(1);
        }
    break;

  case 361:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
    break;

  case 362:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: LocalLabelList");
          System.exit(1);
        }
    break;

  case 363:
    {
          List<Multiverse<DeclarationOrStatementValue>> n = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
          setTransformationValue(value, n);
        }
    break;

  case 364:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          List<Multiverse<DeclarationOrStatementValue>> list = getCompleteNodeDeclStmtValueList(subparser, 2, pc);
          Multiverse<DeclarationOrStatementValue>  ds = getCompleteNodeMultiverseValue(subparser, 1, pc);
          list.add(ds);
          setTransformationValue(value, list);
        }
    break;

  case 365:
    {
          // declarations are already just strings, so get the multiverse of any static conditionals around them
          Multiverse<String> ss = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1),subparser.getPresenceCondition());
          Multiverse<DeclarationOrStatementValue> decl = DesugarOps.StringToDSV.transform(ss);
          for (Element<DeclarationOrStatementValue> e : decl) {
            e.getData().setDecl();
          }
          setTransformationValue(value, decl);
        }
    break;

  case 366:
    {
          // statements have multiverses, so hoist any static conditionals around them by combining with the statement multiverses
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, getCompleteNodeMultiverseValue(subparser, 1, pc));
        }
    break;

  case 367:
    {
          System.err.println("nestedfunctiondefinition not implemented yet");
          System.exit(1);
        }
    break;

  case 368:
    {
          Multiverse<String> valuemv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          setTransformationValue(value, concatMultiverseStrings(valuemv)); valuemv.destruct();
        }
    break;

  case 369:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          StringBuilder valuesb = new StringBuilder();
          Multiverse<String> listmv = getCompleteNodeSingleValue(subparser, 2, pc);
          Multiverse<String> declmv = getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition());
          valuesb.append(concatMultiverseStrings(listmv)); listmv.destruct();
          valuesb.append(concatMultiverseStrings(declmv)); declmv.destruct();
          setTransformationValue(value, valuesb.toString());
        }
    break;

  case 370:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          Multiverse<Type> exprtype = exprval.type;
          PresenceCondition errorCond = exprtype.getConditionOf(ErrorT.TYPE);
          /* System.err.println("EXPTYP: " + exprtype); */

          Multiverse<String> valuemv;
          if (! exprval.isAlwaysError()) {
            Multiverse<String> expr = exprval.transformation;
            String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
            
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
          setTransformationValue(value, DesugarOps.StringToDSV.transform(valuemv));
        }
    break;

  case 371:
    {
          todoReminder("check the type of the conditional expression SelectionStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);
          String ifstr = ((Syntax) getNodeAt(subparser, 5)).getTokenText();
          String lparenstr = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String rparenstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

          String errorstmt = String.format("%s;", emitError("invalid type found in if statement"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", ifstr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr, DesugarOps.concatStrings); prependmv.destruct();

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
    break;

  case 372:
    {
          todoReminder("check the type of the conditional expression SelectionStatement (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 5, pc);

          String ifstr = ((Syntax) getNodeAt(subparser, 7)).getTokenText();
          String lparenstr = ((Syntax) getNodeAt(subparser, 6)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String rparenstr = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<DeclarationOrStatementValue> ifbranchmv = getCompleteNodeMultiverseValue(subparser, 3, pc);
          String elsestr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<DeclarationOrStatementValue> elsebranchmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

          String errorstmt = String.format("%s;", emitError("invalid type found in ifelse statement"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", ifstr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr, DesugarOps.concatStrings); prependmv.destruct();

            Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appendmv);

            for (Element<DeclarationOrStatementValue> d : dsv) {
              d.getData().setChildrenElse(ifbranchmv,elsebranchmv);
            }
                        
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            dsv.add(new DeclarationOrStatementValue(errorstmt), invalidCond);
            setTransformationValue(value, dsv);
          } else {
            setTransformationValue(value, DesugarOps.StringToDSV.transform(new Multiverse<String>(errorstmt, pc)));
          }
        }
    break;

  case 373:
    {
          // n1570 6.8.4.2 for switch statements

          // n1570 labeled statement, 6.8.1, case and default are only to be used under switch statements

          String switchstr = ((Syntax) getNodeAt(subparser, 7)).getTokenText();
          String lparen = ((Syntax) getNodeAt(subparser, 6)).getTokenText();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 5, subparser.getPresenceCondition());
          String rparen = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          String lbrace = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          List<Multiverse<DeclarationOrStatementValue>> body = (List<Multiverse<DeclarationOrStatementValue>>) getTransformationValue(subparser, 2);
          String rbrace = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          todoReminder("check that switch statement expression should be an int");

          String prefix = String.format("%s %s", switchstr, lparen);
          Multiverse<String> prepended = exprval.transformation.prependScalar(prefix, DesugarOps.concatStrings);
          String suffix = String.format("%s", rparen);
          Multiverse<String> appended = prepended.appendScalar(suffix, DesugarOps.concatStrings);
          prepended.destruct();
          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(appended);
          appended.destruct();
          for (Element<DeclarationOrStatementValue> e : dsv) {
            e.getData().setChildrenBlock("{",body,"}");
          }
          setTransformationValue(value, dsv);
        }
    break;

  case 374:
    {
          todoReminder("check the type of the conditional expression IterationStatement (1)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);

          String whilestr = ((Syntax) getNodeAt(subparser, 5)).getTokenText();
          String lparenstr = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String rparenstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

          String errorstmt = String.format("%s;", emitError("invalid type found in while statement"));
          if (exprval.hasValidType()) {
            Multiverse<String> validmv = exprval.validTransformations(pc);
            String prependstr = String.format("%s %s", whilestr, lparenstr);
            Multiverse<String> prependmv
              = validmv.prependScalar(prependstr, DesugarOps.concatStrings); validmv.destruct();
            Multiverse<String> appendmv
              = prependmv.appendScalar(rparenstr, DesugarOps.concatStrings); prependmv.destruct();

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
    break;

  case 375:
    {
          todoReminder("check the type of the conditional expression IterationStatement (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);

          String dostr = (String)((Syntax) getNodeAt(subparser, 7)).getTokenText();
          Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 6, pc);
          String whilestr =  (String)((Syntax) getNodeAt(subparser, 5)).getTokenText();
          String lparenstr = (String)((Syntax) getNodeAt(subparser, 4)).getTokenText();
          Multiverse<String> exprmv = exprval.transformation;
          String rparenstr = (String)((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String semistr =   (String)((Syntax) getNodeAt(subparser, 1)).getTokenText();
          Multiverse<String> prependmv
              = exprmv.prependScalar(whilestr + lparenstr, DesugarOps.concatStrings); exprmv.destruct();
          Multiverse<String> appendmv
            = prependmv.appendScalar(rparenstr + semistr, DesugarOps.concatStrings); prependmv.destruct();

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
    break;

  case 376:
    {
          todoReminder("check the type of the conditional expression IterationStatement (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          String forkeyword = ((Syntax) getNodeAt(subparser, 9)).getTokenText();
          String lparen = ((Syntax) getNodeAt(subparser, 8)).getTokenText();
          ExpressionValue initval = getCompleteNodeExpressionValue(subparser, 7, pc);
          String semi1 = ((Syntax) getNodeAt(subparser, 6)).getTokenText();
          ExpressionValue testval = getCompleteNodeExpressionValue(subparser, 5, pc);
          String semi2 = ((Syntax) getNodeAt(subparser, 4)).getTokenText();
          ExpressionValue updateval = getCompleteNodeExpressionValue(subparser, 3, pc);
          String rparen = ((Syntax) getNodeAt(subparser, 2)).getTokenText();


          if (initval.hasValidType() && testval.hasValidType() && updateval.hasValidType()) {
            PresenceCondition cond1 = initval.validTypeCondition(pc);
            PresenceCondition cond2 = cond1.and(testval.validTypeCondition(pc)); cond1.delRef();
            PresenceCondition validcond = cond2.and(updateval.validTypeCondition(pc)); cond2.delRef();

            if (validcond.isNotFalse()) {
              Multiverse<DeclarationOrStatementValue> stmtmv = getCompleteNodeMultiverseValue(subparser, 1, pc);

              Multiverse<String> initmv = initval.transformation;
              Multiverse<String> testmv = testval.transformation;
              Multiverse<String> updatemv = updateval.transformation;

          
              String forlparen = String.format("%s %s",
                                               ((Syntax) getNodeAt(subparser, 9)).getTokenText(),
                                               ((Syntax) getNodeAt(subparser, 8)).getTokenText());

              Multiverse<String> mv1 = initmv.prependScalar(forlparen, DesugarOps.concatStrings);
              Multiverse<String> mv2 = mv1.appendScalar(semi1, DesugarOps.concatStrings); mv1.destruct();
              Multiverse<String> mv3 = mv2.product(testmv, DesugarOps.concatStrings); mv2.destruct();
              Multiverse<String> mv4 = mv3.appendScalar(semi2, DesugarOps.concatStrings); mv3.destruct();
              Multiverse<String> mv5 = mv4.product(updatemv, DesugarOps.concatStrings); mv4.destruct();
              Multiverse<String> valuemv = mv5.appendScalar(rparen, DesugarOps.concatStrings); mv5.destruct();
              
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
    break;

  case 377:
    { EnterScope(subparser); }
    break;

  case 378:
    { ExitScope(subparser); }
    break;

  case 379:
    {
          // TODO: use a reentrant scope to add the declaration's symbol to the for-loop's scope
          // TODO: Declaration returns a String, not a multiverse.  We need a multiverse to hoist around the entire for loop.
          // TODO: consider rewriting this to put the declaration outside the for loop.  since it's renamed, we should have conflicts, and it resolves issues with scope and semantic values
          todoReminder("check the type of the conditional expression IterationStatement (4)");
          PresenceCondition pc = subparser.getPresenceCondition();

          Multiverse<String> formv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 10)).getTokenText(), pc);
          Multiverse<String> lparen = new Multiverse<String>(((Syntax) getNodeAt(subparser, 9)).getTokenText(), pc);
          Multiverse<String> declstring = getCompleteNodeMultiverseValue(getNodeAt(subparser, 7),subparser.getPresenceCondition());
          ExpressionValue testval = getCompleteNodeExpressionValue(subparser, 6, pc);
          Multiverse<String> testmv = testval.transformation;
          Multiverse<String> semi2mv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 5)).getTokenText(), pc);
          ExpressionValue updateval = getCompleteNodeExpressionValue(subparser, 4, pc);
          Multiverse<String> updatemv = updateval.transformation;
          Multiverse<String> rparen = new Multiverse<String>(((Syntax) getNodeAt(subparser, 3)).getTokenText(), pc);
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
                                                declstring,
                                                formv,
                                                lparen,
                                                semi1mv,
                                                testmv,
                                                semi2mv,
                                                updatemv,
                                                  rparen);
          valuemv = valuemv.filter(testval.type.getConditionOf(ErrorT.TYPE).not()).filter(updateval.type.getConditionOf(ErrorT.TYPE).not());

          Multiverse<DeclarationOrStatementValue> dsv = DesugarOps.StringToDSV.transform(valuemv);
          
          for (Element<DeclarationOrStatementValue> d : dsv) {
            d.getData().setChildrenBlock("",stmtmv,"}");
          }
          
          dsv.add(new DeclarationOrStatementValue(emitError("test condition type error in this presence condition") + ";"),testval.type.getConditionOf(ErrorT.TYPE));
          
          dsv.add(new DeclarationOrStatementValue(emitError("update value type error in this presence condition") + ";"),updateval.type.getConditionOf(ErrorT.TYPE));
          
          setTransformationValue(value, dsv);
        }
    break;

  case 380:
    {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
    break;

  case 381:
    {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
    break;

  case 382:
    {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
    break;

  case 383:
    {
          setTransformationValue(value, DesugarOps.StringToDSV.transform(getCompleteNodeMultiverseValue(getNodeAt(subparser, 1), subparser.getPresenceCondition())));
        }
    break;

  case 384:
    {
          String gototoken = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
          String ident = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          setTransformationValue(value, new Multiverse<String>(String.format("%s %s %s", gototoken, ident, semi),
                                                               subparser.getPresenceCondition()));
        }
    break;

  case 385:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          System.err.println("ERROR: unsupported semantic action: GotoStatement (2)");
          System.exit(1);
        }
    break;

  case 386:
    {
          String continuetoken = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          setTransformationValue(value, new Multiverse<String>(String.format("%s %s", continuetoken, semi),
                                                               subparser.getPresenceCondition()));
        }
    break;

  case 387:
    {
          String breaktoken = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          String semi = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          setTransformationValue(value, new Multiverse<String>(String.format("%s %s", breaktoken, semi),
                                                               subparser.getPresenceCondition()));
        }
    break;

  case 388:
    {
          todoReminder("check the type of the return value");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          System.err.println(getNodeAt(subparser, 3) + " " + exprval);
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
              = prependmv.appendScalar(semi, DesugarOps.concatStrings); prependmv.destruct();
            PresenceCondition invalidCond = exprval.invalidTypeCondition(pc);
            valuemv.add(errorstmt, invalidCond);
            setTransformationValue(value, valuemv);
          } else {
            setTransformationValue(value, new Multiverse<String>(errorstmt, pc));
          }  
        }
    break;

  case 389:
    {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new FloatT(NumberT.Kind.FLOAT).attribute(Constants.ATT_CONSTANT), subparser.getPresenceCondition()));
        }
    break;

  case 390:
    {
          /* value = GNode.create("Constant", getNodeAt(subparser, 1)); */
          /* System.err.println(value); */
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT), subparser.getPresenceCondition()));

          /* System.err.println("Constant: " + value.hashCode()); */
          // TODO: check whether INT is correct here, or whether we
          // need to look at the token itself to determine long, etc.
        }
    break;

  case 391:
    {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT), subparser.getPresenceCondition()));
        }
    break;

  case 392:
    {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.INT).attribute(Constants.ATT_CONSTANT), subparser.getPresenceCondition()));
        }
    break;

  case 393:
    {
          setTransformationValue(value,
                                 new ExpressionValue(((Syntax) getNodeAt(subparser, 1)).getTokenText(),
                                                     new IntegerT(NumberT.Kind.SHORT).attribute(Constants.ATT_CONSTANT), subparser.getPresenceCondition()));
        }
    break;

  case 394:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 395:
    {
          StringBuilder valuesb = new StringBuilder();
          valuesb.append((String) getTransformationValue(subparser, 2));
          valuesb.append(((Syntax) getNodeAt(subparser, 1)).getTokenText());
          setTransformationValue(value, valuesb.toString());
        }
    break;

  case 396:
    {
          // TODO: CAnalyzer distinguishes between wide and non-wide characters
          // TODO: use a fixed-size array instead of a pointer to char
          setTransformationValue(value,
                                 new ExpressionValue((String) getTransformationValue(subparser, 1),
                                                     new PointerT(NumberT.CHAR),
                                                     subparser.getPresenceCondition()));
        }
    break;

  case 397:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 398:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 399:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 400:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);
          /* System.err.println("PRIMARY: " + exprval.transformation); */
          /* System.err.println("PRIMARY: " + exprval.type); */

          if (exprval.hasValidType()) {
            String lparen = ((Syntax) getNodeAt(subparser, 3)).getTokenText();
            Multiverse<String> exprmv = exprval.transformation;
            String rparen = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

            Multiverse<String> prepended = exprmv.prependScalar(lparen, DesugarOps.concatStrings);
            Multiverse<String> appended = prepended.appendScalar(rparen, DesugarOps.concatStrings); prepended.destruct();

            setTransformationValue(value, new ExpressionValue(appended, exprval.type));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type for the primary expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 401:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 402:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 403:
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
          
          setTransformationValue(value, new ExpressionValue(sbmv, typemv));
        }
    break;

  case 404:
    {
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

          expr_appended.destruct(); 
          todoReminder("typecheck VariableArgumentAccess (1)");

          setTransformationValue(value, new ExpressionValue(transformationmv, typemv));
        }
    break;

  case 405:
    { EnterScope(subparser); }
    break;

  case 406:
    { ExitScope(subparser); }
    break;

  case 407:
    {
          // TODO: unit test this construct
          todoReminder("get last expression's type from compound statement in StatementAsExpression");

          PresenceCondition pc = subparser.getPresenceCondition();
          String lparen = ((Syntax) getNodeAt(subparser, 5)).getTokenText();
          Multiverse<String> compoundmv = getCompleteNodeSingleValue(subparser, 3, pc);
          String rparen = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          Multiverse<String> prepended = compoundmv.prependScalar(lparen, DesugarOps.concatStrings);
          Multiverse<String> valuemv = prepended.appendScalar(rparen, DesugarOps.concatStrings);
          prepended.destruct();

          Multiverse<Type> typemv = new Multiverse<Type>(NumberT.INT, pc);
          for (Element<String> v : valuemv) {
            typemv.add(NumberT.INT, v.getCondition());
          }
          
          setTransformationValue(value, new ExpressionValue(valuemv,
                                                            typemv));  // TODO: placeholder; get type from compoundstatement
        }
    break;

  case 408:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 409:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 410:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 411:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 412:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 413:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 414:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 415:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 416:
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
          
          if (postfixexprval.hasValidType() && exprval.hasValidType()) {
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
            /* System.err.println("SUBSCRIPTBEFORE: " + postfixexprval.type); */
            /* System.err.println("SUBSCRIPTAFTER: " + typemv); */
            typemv = typemv.filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
            typemv.add(ErrorT.TYPE, exprval.type.getConditionOf(ErrorT.TYPE));
            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            transformationmv = transformationmv.filter(validTypes);
            setTransformationValue(value, new ExpressionValue(transformationmv,
                                                              typemv));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in subscript expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 417:
    {
          todoReminder("typecheck functioncall (1)");
          // type check by making sure the postfixexpression type is a
          // function, has no params, and setting the return value to
          // the type
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 3, pc);

          String lparen = getNodeAt(subparser, 2).getTokenText();
          String rparen = getNodeAt(subparser, 1).getTokenText();


          if (exprval.hasValidType()) {
            String appendstr = String.format("%s %s", lparen, rparen);
            Multiverse<String> valuemv = new Multiverse<String>();
            // the resulting type of the function call is the return value
            Multiverse<Type> returntype = DesugarOps.getReturnType.transform(exprval.type);

            
            for (Element<Type> et : exprval.type ) {
              Type x = et.getData();
              if (x.isFunction() && ((FunctionT)x).getParameters().size() == 0 ) {
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
                                                              returntype)); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in function call"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 418:
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
              todoReminder("support variadic arguments.  see CAnalyzer.processFunctionCall");
              // loop over each combination of postfix expression and
              // parameter list
              for (Element<Type> postfixelem : postfixexprval.type) {
                // check that postfix expression is a function type
                /* System.err.println("FUNTYPE: " + postfixelem.getData()); */
                /* System.err.println("isnamedfunt: " + (postfixelem.getData() instanceof NamedFunctionT)); */
                /* System.err.println("isfunt: " + (postfixelem.getData() instanceof FunctionT)); */
                if (postfixelem.getData().isFunction()) {
                  FunctionT functiontype = postfixelem.getData().toFunction();
                  List<Type> formals = functiontype.getParameters();
                  for (Element<List<Type>> exprlisttype : exprlisttypemv) {
                    PresenceCondition combinedCond = postfixelem.getCondition().and(exprlisttype.getCondition());
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
                    if (hasError) {
                      PresenceCondition new_errorCond = errorCond.or(combinedCond);
                      valuemv.add(emitError("A parameter expression is an error"), combinedCond);
                      errorCond.delRef(); errorCond = new_errorCond;
                    }
                    else if (size1 > size2) {
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
                        todoReminder("do proper type checking for function calls");

                        typemv.add(functiontype.getResult(), combinedCond);
                        /* // TODO: unit test */
                        /* // parameters don't match.  type error. */
                        /* PresenceCondition new_errorCond = errorCond.or(combinedCond); */
                        /* valuemv.add(emitError("function call parameter types do not match function type"), combinedCond); */
                        /* errorCond.delRef(); errorCond = new_errorCond; */
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
            
              /* System.err.println("filtered1: " + filtered_postfixexpr); */
              /* System.err.println("filtered2: " + filtered_exprlistmv); */

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

              /* System.err.println("FCALLTYPE: " + typemv); */
              /* System.err.println("FCALLERRVALS: " + valuemv); */
            
              setTransformationValue(value, new ExpressionValue(valuemv, typemv));
            } else {
              setTransformationValue(value, new ExpressionValue(emitError("no valid type for one or more arguments of the function call"),
                                                                ErrorT.TYPE,
                                                                pc));
            }
          } else { // types of postfixexprval are all errors
            // TODO: this throws away the type message from the child,
            // so perhaps copy the child's mv values instead.
            setTransformationValue(value, new ExpressionValue(emitError("no valid type for the function part of the function call"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 419:
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

                System.err.println("GET: " + tag);
                String originalTag = scope.getForwardTagReferenceAnyScope(tag);
                System.err.println("GET: " + originalTag);


                System.err.println("originalTag: " + originalTag);

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
                      SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(renamedTag);

                      // renamed the field according to the tag lookaside
                      // table, or produce an error if that configuration is
                      // missing the field.  expand to all possible
                      // variations of the field.
                      Multiverse<SymbolTable.Entry<Type>> fieldentries = tagtab.get(ident, tagentry.getCondition());
                      for (Element<SymbolTable.Entry<Type>> fieldentry : fieldentries) {
                        if (fieldentry.getData().isError()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else if (fieldentry.getData().isUndeclared()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else {  // declared
                          VariableT fieldtype = fieldentry.getData().getValue().toVariable();  // these are stored as VariableT
                          typemv.add(fieldtype.getType(), fieldentry.getCondition());
                          String indirectaccess = String.format("%s . %s", renamedTag, fieldtype.getName());
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
                Multiverse<Map.Entry<String,Type>> access = getNestedFields(tag,ident,temp,scope);
                if (!access.isEmpty()) {
                  for (Element<Map.Entry<String,Type>> e : access) {
                    String fields = e.getData().getKey();
                    if (fields.equals("")) {
                      //more than one match was found
                      typemv.add(ErrorT.TYPE, e.getCondition());
                      identmv.add("", e.getCondition());
                    } else {
                      //found a match
                      VariableT fieldType = ((VariableT)e.getData().getValue());
                      typemv.add(fieldType.getType(), e.getCondition());
                      identmv.add(e.getData().getKey(), e.getCondition());
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

          if (hasValidType) {
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
            setTransformationValue(value, new ExpressionValue(valuemv, typemv));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in direct expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 420:
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
                && (resolvedType.toPointer().getType().isStruct()
                    || resolvedType.toPointer().getType().isUnion())) {
              StructOrUnionT sutype = resolvedType.toPointer().getType().toStructOrUnion();
              String tag = sutype.getName();
              assert tag != null;  // even anonymous structs get a name, e.g., anonymous(0)

              // below is the same as directselection
              
              // the ref will either be to a renamed tag or to a forward reference
              if (tag.startsWith("__forward_tag_reference_")) {
                // TODO: is there a safer way to check for this?

                System.err.println("GET: " + tag);
                String originalTag = scope.getForwardTagReferenceAnyScope(tag);
                System.err.println("GET: " + originalTag);

                System.err.println("originalTag: " + originalTag);

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
                      SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(renamedTag);

                      // renamed the field according to the tag lookaside
                      // table, or produce an error if that configuration is
                      // missing the field.  expand to all possible
                      // variations of the field.
                      Multiverse<SymbolTable.Entry<Type>> fieldentries = tagtab.get(ident, tagentry.getCondition());
                      for (Element<SymbolTable.Entry<Type>> fieldentry : fieldentries) {
                        if (fieldentry.getData().isError()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else if (fieldentry.getData().isUndeclared()) {
                          typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                        } else {  // declared
                          VariableT fieldtype = fieldentry.getData().getValue().toVariable();  // these are stored as VariableT
                          typemv.add(fieldtype.getType(), fieldentry.getCondition());
                          String indirectaccess = String.format("%s . %s", renamedTag, fieldtype.getName());
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
                SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(tag);

                // renamed the field according to the tag lookaside
                // table, or produce an error if that configuration is
                // missing the field.  expand to all possible
                // variations of the field.
                Multiverse<SymbolTable.Entry<Type>> fieldentries = tagtab.get(ident, type.getCondition());
                for (Element<SymbolTable.Entry<Type>> fieldentry : fieldentries) {
                  if (fieldentry.getData().isError()) {
                    typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                  } else if (fieldentry.getData().isUndeclared()) {
                    typemv.add(ErrorT.TYPE, fieldentry.getCondition());
                  } else {  // declared
                    VariableT fieldtype = fieldentry.getData().getValue().toVariable();  // these are stored as VariableT
                    typemv.add(fieldtype.getType(), fieldentry.getCondition());
                    identmv.add(fieldtype.getName(), fieldentry.getCondition());
                    hasValidType = true;
                  }
                }
              }

              /* if (tag.startsWith("anonymous(")) {  // anonymous struct or union */
              /*   // go through each symtab entry for this struct/union */
              /*   Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(tag, type.getCondition()); */
              /*   for (Element<SymbolTable.Entry<Type>> entry : entries) { */
              /*     PresenceCondition combinedCond = type.getCondition().and(entry.getCondition()); */
              /*     if (entry.getData().isError()) { */
              /*       // TODO: type error */
              /*       typemv.add(ErrorT.TYPE, combinedCond); */
              /*     } else if (entry.getData().isUndeclared()) { */
              /*       // TODO: type error, symbol not declared in this presence condition */
              /*       typemv.add(ErrorT.TYPE, combinedCond); */
              /*     } else { */
              /*       // TODO: check for correct field usage, otherwise type error */
              /*       // TODO: insert field of the union inside the original struct/union */

              /*       // since we looked up a tagname, not seeing a */
              /*       // struct/union type likely means there's a bug */
              /*       assert entry.getData().getValue().isStruct() || entry.getData().getValue().isUnion(); */
              /*       StructOrUnionT entrytype = (StructOrUnionT) entry.getData().getValue(); */

              /*       // similarly, if we looked up a tagname, there */
              /*       // should be definitions with members */
              /*       assert null != entrytype.getMembers(); */

              /*       // check that the field exist in this variation of */
              /*       // the struct.  TypeSpecifier sets all members to */
              /*       // VariableT FIELD types */
              /*       VariableT fieldtype = (VariableT) entrytype.lookup(ident); */
              /*       if (fieldtype.isError()) { */
              /*         System.err.println(String.format("type error: field \"%s\" not found in this configuration of struct/union %s", ident, sutype.getName())); */
              /*         typemv.add(ErrorT.TYPE, combinedCond); */
              /*       } else { */
              /*         // found a valid field and we now know its type */

              /*         typemv.add(fieldtype.getType(), combinedCond); */

              /*         // add the indirection using the tag (which is */
              /*         // the same name as the field in the combined */
              /*         // struct's union) */
              /*         identmv.add(String.format("%s", fieldtype.getName()), combinedCond); */
              /*       } */
              /*     } */
              /*     combinedCond.delRef(); */
              /*   } */
              /*   entries.destruct(); */
              /* } else {  // tagged struct or union */
              /*   // tagged structs work by using the original name for */
              /*   // a struct that is the union of all variations, so we */
              /*   // need to replace the field with level of indirection */
              /*   // into this union. */

              /*   // first go through each symtab entry for the struct tag */
              /*   String tagname = CContext.toTagName(sutype.getName()); */
              /*   Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(tagname, type.getCondition()); */
              /*   for (Element<SymbolTable.Entry<Type>> entry : entries) { */
              /*     PresenceCondition combinedCond = type.getCondition().and(entry.getCondition()); */
              /*     if (entry.getData().isError()) { */
              /*       // TODO: type error */
              /*       typemv.add(ErrorT.TYPE, combinedCond); */
              /*     } else if (entry.getData().isUndeclared()) { */
              /*       // TODO: type error, symbol not declared in this presence condition */
              /*       typemv.add(ErrorT.TYPE, combinedCond); */
              /*     } else { */
              /*       // TODO: check for correct field usage, otherwise type error */
              /*       // TODO: insert field of the union inside the original struct/union */

              /*       // since we looked up a tagname, not seeing a */
              /*       // struct/union type likely means there's a bug */
              /*       assert entry.getData().getValue().isStruct() || entry.getData().getValue().isUnion(); */
              /*       StructOrUnionT entrytype = (StructOrUnionT) entry.getData().getValue(); */

              /*       // similarly, if we looked up a tagname, there */
              /*       // should be definitions with members */
              /*       assert null != entrytype.getMembers(); */

              /*       // check that the field exist in this variation of */
              /*       // the struct.  TypeSpecifier sets all members to */
              /*       // VariableT FIELD types */
              /*       VariableT fieldtype = (VariableT) entrytype.lookup(ident); */
              /*       if (fieldtype.isError()) { */
              /*         System.err.println(String.format("type error: field \"%s\" not found in this configuration of struct/union %s", ident, sutype.getName())); */
              /*         typemv.add(ErrorT.TYPE, combinedCond); */
              /*       } else { */
              /*         // found a valid field and we now know its type */

              /*         typemv.add(fieldtype.getType(), combinedCond); */

              /*         // add the indirection using the tag (which is */
              /*         // the same name as the field in the combined */
              /*         // struct's union) */
              /*         identmv.add(String.format("%s . %s", entrytype.getName(), fieldtype.getName()), combinedCond); */
              /*       } */
              /*     } */
              /*     combinedCond.delRef(); */
              /*   } */
              /* } */
              
            } else {
              // TODO: not a pointer, type error
              typemv.add(ErrorT.TYPE, type.getCondition());
            }
          }
          
          assert ! typemv.isEmpty();

          /* System.err.println("typemv " + typemv); */
          /* System.err.println("identmv " + identmv); */

          if (hasValidType) {
            Multiverse<String> prepend = identmv.prependScalar(arrow, DesugarOps.concatStrings);
            Multiverse<String> valuemv = postfixmv.product(prepend, DesugarOps.concatStrings);
            identmv.destruct(); prepend.destruct();
            
            /* System.err.println("valuemv " + valuemv); */
            setTransformationValue(value, new ExpressionValue(valuemv, typemv));
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in indirect expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 421:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);

          Multiverse<Syntax> opmv = new Multiverse<Syntax>((Syntax) getNodeAt(subparser, 1), pc);
          if (exprval.hasValidType()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = exprval.transformation.product(opstr, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 422:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 2, pc);

          Multiverse<Syntax> opmv = new Multiverse<Syntax>((Syntax) getNodeAt(subparser, 1), pc);
          if (exprval.hasValidType()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = exprval.transformation.product(opstr, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 423:
    {
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
          Multiverse<String> mv3 = mv2.appendScalar(lbrace, DesugarOps.concatStrings); mv2.destruct();
          Multiverse<Initializer> initializerlistmv
            = DesugarOps.toInitializerList.transform(initializerlist);
          Multiverse<String> initializerliststr
            = DesugarOps.initializerToString.transform(initializerlistmv);  initializerlistmv.destruct();
          Multiverse<String> mv4
            = mv3.product(initializerliststr, DesugarOps.concatStrings); initializerliststr.destruct(); mv3.destruct();
          Multiverse<String> transformationmv = mv4.appendScalar(rbrace, DesugarOps.concatStrings); mv4.destruct();

          Multiverse<Type> typemv = DesugarOps.typenameToType.transform(typename);

          setTransformationValue(value, new ExpressionValue(transformationmv, typemv));
        }
    break;

  case 424:
    {
          // create a new list
          List<ExpressionValue> exprlist = new LinkedList<ExpressionValue>();
          ExpressionValue exprval
            = getCompleteNodeExpressionValue(subparser,1, subparser.getPresenceCondition());
          exprlist.add(exprval);
          setTransformationValue(value, exprlist);
        }
    break;

  case 425:
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
    break;

  case 426:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 427:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Syntax> opmv = new Multiverse<Syntax>((Syntax) getNodeAt(subparser, 2), pc);
          if (exprval.hasValidType()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = opstr.product(exprval.transformation, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 428:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Syntax> opmv = new Multiverse<Syntax>((Syntax) getNodeAt(subparser, 2), pc);
          if (exprval.hasValidType()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = opstr.product(exprval.transformation, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 429:
    {
          // TODO: need to look at the unaryoperator to determine whether it's the correct type usage
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<Syntax> opmv = this.<Syntax>getCompleteNodeSingleValue(subparser, 2, pc);
          if (exprval.hasValidType()) {
            Multiverse<String> opstr = DesugarOps.syntaxToString.transform(opmv);
            Multiverse<String> resultmv = opstr.product(exprval.transformation, DesugarOps.concatStrings);
            Multiverse<Type> typemv = exprval.type.join(opmv, DesugarOps.checkUnaryOp);

            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition validTypes = errorCond.not();
            resultmv = resultmv.filter(validTypes);

            setTransformationValue(value,
                                   new ExpressionValue(resultmv,
                                                       typemv));  // TODO: placeholder until type checking
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in unary operation"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 430:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;

          todoReminder("typecheck unaryexpression (5)");
          Multiverse<Type> type = new Multiverse<Type>(C.SIZEOF, pc);

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                opmv,
                                                                exprmv),
                                                     type));
          opmv.destruct();
        }
    break;

  case 431:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          String prefix = String.format("%s %s",
                                        ((Syntax) getNodeAt(subparser, 4)).getTokenText(),
                                        ((Syntax) getNodeAt(subparser, 3)).getTokenText());
          Multiverse<Declaration> typename = (Multiverse<Declaration>) getTransformationValue(subparser, 2);
          String suffix = ((Syntax) getNodeAt(subparser, 1)).getTokenText();

          // convert to string and append tokens
          Multiverse<String> typenamestr = DesugarOps.typenameToString.transform(typename);
          Multiverse<String> prepended = typenamestr.prependScalar(prefix, DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(suffix, DesugarOps.concatStrings);
          typenamestr.destruct(); prepended.destruct();
          todoReminder("typecheck unaryexpression (6)");
          Multiverse<Type> type = new Multiverse<Type>(C.SIZEOF, pc);
          for (Element<Declaration> e : typename) {
            if (e.getData().getType() == ErrorT.TYPE) {
              type = type.filter(e.getCondition().not());
              type.add(ErrorT.TYPE, e.getCondition());
            }
          }
          
          setTransformationValue(value, new ExpressionValue(appended, type));
        }
    break;

  case 432:
    {
          todoReminder("typecheck unaryexpression (7)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 433:
    {
          todoReminder("typecheck unaryexpression (8)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 434:
    {
          todoReminder("typecheck unaryexpression (9)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 435:
    {
          todoReminder("typecheck unaryexpression (10)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 436:
    {
          todoReminder("typecheck unaryexpression (11)");
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 437:
    {
          System.err.println("ERROR: unsupported semantic action: TypeCompatibilityExpression");
          System.exit(1);
        }
    break;

  case 438:
    {
          todoReminder("typcheck offsetofmemberdesignator (1)");
          String ident = ((Syntax) getNodeAt(subparser, 1)).getTokenText();
          List<Designator> list = new LinkedList<Designator>();
          setTransformationValue(value,
                                 new Multiverse<OffsetofMemberDesignator>(new OffsetofMemberDesignator(ident, list),
                                                                          subparser.getPresenceCondition()));
        }
    break;

  case 439:
    {
          todoReminder("typcheck offsetofmemberdesignator (2)");
          Multiverse<String> identmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(),
                                     subparser.getPresenceCondition());
          Multiverse<List<Designator>> listmv
            = (Multiverse<List<Designator>>) getTransformationValue(subparser, 1);
          setTransformationValue(value, identmv.join(listmv, DesugarOps.joinOffsetof));
        }
    break;

  case 440:
    {
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
          System.err.println(offsetofstr);
          Multiverse<String> offsetofappended = offsetofstr.appendScalar(suffix, DesugarOps.concatStrings);
          
          todoReminder("typecheck OffsetofExpression (1)");
          // TODO: check that the expression references something in the typespec given by typename
          Multiverse<Type> type = new Multiverse<Type>(C.SIZEOF, pc);

          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                appended,
                                                                offsetofappended),
                                                     type));
          appended.destruct(); offsetofappended.destruct();
        }
    break;

  case 441:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue exprval = getCompleteNodeExpressionValue(subparser, 1, pc);
          
          Multiverse<String> extmv
            = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> exprmv = exprval.transformation;
          setTransformationValue(value,
                                 new ExpressionValue(productAll(DesugarOps.concatStrings, extmv, exprmv),
                                                     exprval.type));
          extmv.destruct();
        }
    break;

  case 442:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          String keyword = (String) getTransformationValue(subparser, 4);
          String lparen = getNodeAt(subparser, 3).getTokenText();
          Multiverse<Declaration> typenamemv = (Multiverse<Declaration>) getTransformationValue(subparser, 2);
          String rparen = getNodeAt(subparser, 1).getTokenText();

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
          
          ExpressionValue exprval = new ExpressionValue(valuestr, valuetype);
          
          setTransformationValue(value, exprval);
        }
    break;

  case 443:
    {
          System.err.println("ERROR: unsupported semantic action: AlignofExpression (2)");
          System.exit(1);
        }
    break;

  case 444:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 445:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 446:
    {
          System.err.println("ERROR: unsupported semantic action: LabelAddressExpression");
          System.exit(1);
        }
    break;

  case 447:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 448:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 449:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 450:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 451:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 452:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)));
        }
    break;

  case 453:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 454:
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
          typemv = typemv.filter(exprval.type.getConditionOf(ErrorT.TYPE).not());
          typemv.add(ErrorT.TYPE, exprval.type.getConditionOf(ErrorT.TYPE));
          setTransformationValue(value, new ExpressionValue(transformationmv, typemv));
        }
    break;

  case 455:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 456:
    {
          todoReminder("typecheck MultiplicativeExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          if (leftval.hasValidType() && rightval.hasValidType()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
          opmv.destruct();
        }
    break;

  case 457:
    {
          todoReminder("typecheck MultiplicativeExpression (3)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          if (leftval.hasValidType() && rightval.hasValidType()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
          opmv.destruct();
        }
    break;

  case 458:
    {
          todoReminder("typecheck MultiplicativeExpression (4)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> opmv = new Multiverse<String>(((Syntax) getNodeAt(subparser, 2)).getTokenText(), pc);
          Multiverse<String> rightmv = rightval.transformation;

          if (leftval.hasValidType() && rightval.hasValidType()) {
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         leftmv,
                                                                         opmv,
                                                                         rightmv),
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type)));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in multiplicative expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
          opmv.destruct();
        }
    break;

  case 459:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 460:
    {
          todoReminder("typecheck AdditiveExpression (2)");
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 461:
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 462:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 463:
    {
          todoReminder("typecheck ShiftExpression (2)");
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
                                                              leftval.type)); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 464:
    {
          todoReminder("typecheck ShiftExpression (3)");
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
                                                              leftval.type)); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 465:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 466:
    {
          todoReminder("typecheck RelationalExpression (2)");
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
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 467:
    {
          todoReminder("typecheck RelationalExpression (3)");
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
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 468:
    {
          todoReminder("typecheck RelationalExpression (4)");
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
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 469:
    {
          todoReminder("typecheck RelationalExpression (5)");
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
                                                              productAll(DesugarOps.relOpProduct, leftval.type, rightval.type)));
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 470:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 471:
    {
          todoReminder("typecheck EqualityExpression (2)");
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 472:
    {
          todoReminder("typecheck EqualityExpression (3)");
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 473:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 474:
    {
          todoReminder("typecheck AndExpression (2)");
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 475:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 476:
    {
          todoReminder("typecheck ExclusiveOrExpression (2)");
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
                                                              leftval.type)); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 477:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 478:
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 479:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 480:
    {
          todoReminder("typecheck LogicalAndExpression (2)");
          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);
          System.err.println("L"+leftval);
          System.err.println("R"+rightval);
          
          

          Multiverse<String> leftmv = leftval.transformation;
          String opstr = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          Multiverse<String> rightmv = rightval.transformation;


          if (leftval.hasValidType() && rightval.hasValidType()) {
            Multiverse<String> appendmv = leftmv.appendScalar(opstr, DesugarOps.concatStrings);
            Multiverse<String> productmv = appendmv.product(rightmv, DesugarOps.concatStrings);  appendmv.destruct();
            ExpressionValue e = new ExpressionValue(productmv,
                                                    productAll(DesugarOps.propTypeError, leftval.type, rightval.type));
            System.err.println("E"+e);
            
            setTransformationValue(value, new ExpressionValue(productmv,
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 481:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 482:
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
                                                              productAll(DesugarOps.propTypeError, leftval.type, rightval.type))); // TODO: placeholder for real type
                                                              
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 483:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 484:
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
            // check that condval is a condition type
            setTransformationValue(value, new ExpressionValue(productAll(DesugarOps.concatStrings,
                                                                         condmv,
                                                                         quesmv,
                                                                         ifmv,
                                                                         colonmv,
                                                                         elsemv),
                                                              ifval.type));  // TODO: this is a placeholder for the real type
          } else {
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in conditionalexpression expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
          quesmv.destruct(); colonmv.destruct();
        }
    break;

  case 485:
    {
          System.err.println("TODO: ConditionalExpression");
          System.exit(1);
          /// TODO: check for valid types
        }
    break;

  case 486:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 487:
    {
          PresenceCondition pc = subparser.getPresenceCondition();

          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          if (leftval.hasValidType() && rightval.hasValidType()) {
            
            Multiverse<String> expr = leftval.transformation;
            Multiverse<String> op = this.<String>getCompleteNodeSingleValue(subparser, 2, pc);
            /* Multiverse<String> op */
            /*   = new Multiverse<String>((String) getTransformationValue(subparser, 2), pc); */
            Multiverse<String> assign = rightval.transformation;
            /* System.err.println(expr); */
            /* System.err.println(op); */
            /* System.err.println(assign); */
            /* System.err.println(getNodeAt(subparser, 1)); */

            // type-checking
            Multiverse<Type> exprtype = leftval.type;
            Multiverse<Type> assigntype = rightval.type;
            /* System.err.println("exprtype: " + exprtype); */
            /* System.err.println("assigntype: " + assigntype); */
            /* Multiverse<Type> producttype = exprtype.product(assigntype, DesugarOps.compareTypes); */
            Multiverse<Type> producttype = DesugarOps.checkAssignmentType(exprtype, assigntype, op, pc, false);
            /* System.err.println("TODO: deduplicate ErrorT"); */
            /* System.err.println("TODO: allow type coercion"); */

            Multiverse<Type> typemv = producttype;
            /* Multiverse<Type> typemv = producttype.deduplicate(ErrorT.TYPE); */
            /* producttype.destruct(); */

            // filter out configurations with type errors
            PresenceCondition errorCond = typemv.getConditionOf(ErrorT.TYPE);
            PresenceCondition typesafeCond = errorCond.not();

            // carefully take the product of each combinations of the
            // left side, operator, right side to check for infeasible
            // combinations.
            Multiverse<String> valuemv;
            Multiverse<String> suffix = expr.product(op, DesugarOps.concatStrings); op.destruct();
            
            if (suffix.size() > 0) {
              Multiverse<String> product = suffix.product(assign, DesugarOps.concatStrings); suffix.destruct();
              if (product.size() > 0) {
                valuemv = product.filter(typesafeCond); product.destruct();
              } else {
                valuemv = product;
              }
            } else {
              valuemv = suffix;
            }
            errorCond.delRef(); typesafeCond.delRef();
            setTransformationValue(value, new ExpressionValue(valuemv, typemv));
            
          } else {  // no valid types
            setTransformationValue(value, new ExpressionValue(emitError("no valid type found in assignment expression"),
                                                              ErrorT.TYPE,
                                                              pc));
          }
        }
    break;

  case 488:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 489:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 490:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 491:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 492:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 493:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 494:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 495:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 496:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 497:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 498:
    {
          setTransformationValue(value, ((Syntax) getNodeAt(subparser, 1)).getTokenText());
        }
    break;

  case 499:
    {
          PresenceCondition pc = subparser.getPresenceCondition();
          setTransformationValue(value, new ExpressionValue("",
                                                            UnitT.TYPE,
                                                            pc));
        }
    break;

  case 500:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 501:
    {
          setTransformationValue(value, this.<ExpressionValue>getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 502:
    {
          // n1570, 6.5.17. left operand is a void expression; result
          // has right operand's type (and value).

          PresenceCondition pc = subparser.getPresenceCondition();
          ExpressionValue leftval = getCompleteNodeExpressionValue(subparser, 3, pc);
          String comma = ((Syntax) getNodeAt(subparser, 2)).getTokenText();
          ExpressionValue rightval = getCompleteNodeExpressionValue(subparser, 1, pc);

          Multiverse<String> leftmv = leftval.transformation;
          Multiverse<String> appended = leftmv.appendScalar(comma, DesugarOps.concatStrings);
          Multiverse<String> rightmv = rightval.transformation;

          Multiverse<String> transformationmv = appended.product(rightmv, DesugarOps.concatStrings);
          appended.destruct();

          setTransformationValue(value, new ExpressionValue(transformationmv, rightval.type));
        }
    break;

  case 503:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()));
        }
    break;

  case 504:
    {
          todoReminder("support AttributeSpecifierListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 505:
    {
          todoReminder("support AttributeSpecifierListOpt (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 506:
    {
          todoReminder("support AttributeSpecifierList (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 507:
    {
          todoReminder("support AttributeSpecifierList (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 508:
    {
          Syntax keyword = ((Syntax) getNodeAt(subparser, 6).get(0));
          todoReminder("support AttributeSpecifier, replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 509:
    {
          // read token from parent
        }
    break;

  case 510:
    {
          // read token from parent
        }
    break;

  case 511:
    {
          todoReminder("support AttributeListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 512:
    {
          todoReminder("support AttributeListOpt (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 513:
    {
          String word = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();
          todoReminder("support AttributeList (1), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 514:
    {
          String word = ((Syntax) getNodeAt(subparser, 2).get(0)).getTokenText();
          todoReminder("support AttributeList (2), replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 515:
    {
          setTransformationValue(value, "");
        }
    break;

  case 516:
    {
          setTransformationValue(value, String.format("%s %s",
                                                      getNodeAt(subparser, 2).getTokenText(),
                                                      getNodeAt(subparser, 1).getTokenText()));
        }
    break;

  case 517:
    {
          // TODO: need to check type of expression list to make sure
          // it's legal and return a type error if it is.
          todoReminder("support AttributeExpressionOpt, replaced with empty string now");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 518:
    {
          // get token from parent
        }
    break;

  case 519:
    {
          // get token from parent
        }
    break;

  case 520:
    {
          // get token from parent
        }
    break;

  case 521:
    {
          // get token from parent
        }
    break;

  case 522:
    {
          // get token from parent
        }
    break;

  case 523:
    {
          // get token from parent
        }
    break;

  case 524:
    {
          // get token from parent
        }
    break;

  case 525:
    {
          // get token from parent
        }
    break;

  case 526:
    {
          // get token from parent
        }
    break;

  case 527:
    {
          // get token from parent
        }
    break;

  case 528:
    {
          // get token from parent
        }
    break;

  case 529:
    {
          // get token from parent
        }
    break;

  case 530:
    {
          // get token from parent
        }
    break;

  case 531:
    {
          // get token from parent
        }
    break;

  case 532:
    {
          // get token from parent
        }
    break;

  case 533:
    {
          // get token from parent
        }
    break;

  case 534:
    {
          // get token from parent
        }
    break;

  case 535:
    {
          // get token from parent
        }
    break;

  case 536:
    {
          // get token from parent
        }
    break;

  case 537:
    {
          // get token from parent
        }
    break;

  case 538:
    {
          // get token from parent
        }
    break;

  case 539:
    {
          // get token from parent
        }
    break;

  case 540:
    {
          // get token from parent
        }
    break;

  case 541:
    {
          // get token from parent
        }
    break;

  case 542:
    {
          // get token from parent
        }
    break;

  case 543:
    {
          // get token from parent
        }
    break;

  case 544:
    {
          // get token from parent
        }
    break;

  case 545:
    {
          // get token from parent
        }
    break;

  case 546:
    {
          // get token from parent
        }
    break;

  case 547:
    {
          // get token from parent
        }
    break;

  case 548:
    {
          // get token from parent
        }
    break;

  case 549:
    {
          // get token from parent
        }
    break;

  case 550:
    {
          // get token from parent
        }
    break;

  case 551:
    {
          // get token from parent
        }
    break;

  case 552:
    {
          // get token from parent
        }
    break;

  case 553:
    {
          // get token from parent
        }
    break;

  case 554:
    {
          // get token from parent
        }
    break;

  case 555:
    {
          // get token from parent
        }
    break;

  case 556:
    {
          // get token from parent
        }
    break;

  case 557:
    {
          // get token from parent
        }
    break;

  case 558:
    {
          // get token from parent
        }
    break;

  case 559:
    {
          // get token from parent
        }
    break;

  case 560:
    {
          // get token from parent
        }
    break;

  case 561:
    {
          // get token from parent
        }
    break;

  case 562:
    {
          // get token from parent
        }
    break;

  case 563:
    {
          // get token from parent
        }
    break;

  case 564:
    {
          // get token from parent
        }
    break;

  case 565:
    {
          // get token from parent
        }
    break;

  case 566:
    {
          // get token from parent
        }
    break;

  case 567:
    {
          // get token from parent
        }
    break;

  case 568:
    {
          // get token from parent
        }
    break;

  case 569:
    {
          // get token from parent
        }
    break;

  case 570:
    {
          // get token from parent
        }
    break;

  case 571:
    {
          // get token from parent
        }
    break;

  case 572:
    {
          // get token from parent
        }
    break;

  case 573:
    {
          // get token from parent
        }
    break;

  case 574:
    {
          // get token from parent
        }
    break;

  case 575:
    {
          // get token from parent
        }
    break;

  case 576:
    {
          // get token from parent
        }
    break;

  case 577:
    {
          // get token from parent
        }
    break;

  case 578:
    {
          // get token from parent
        }
    break;

  case 579:
    {
          // get token from parent
        }
    break;

  case 580:
    {
          // get token from parent
        }
    break;

  case 581:
    {
          // get token from parent
        }
    break;

  case 582:
    {
          // get token from parent
        }
    break;

  case 583:
    {
          // get token from parent
        }
    break;

  case 584:
    {
          todoReminder("support AssemblyDefinition (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 585:
    {
          ExpressionValue e = getCompleteNodeExpressionValue(subparser, 2, subparser.getPresenceCondition());
          Multiverse<String> temp = e.transformation;
          Multiverse<String> prepended = temp.prependScalar("__asm__(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(")", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          setTransformationValue(value, appended);
        }
    break;

  case 586:
    {
          todoReminder("support AssemblyExpressionOpt (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 587:
    {
          todoReminder("support AssemblyExpressionOpt (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 588:
    {
          Multiverse<String> temp = (Multiverse<String>)getTransformationValue(subparser,3);
          Multiverse<String> prepended = temp.prependScalar("__asm__(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(");", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          setTransformationValue(value, DesugarOps.StringToDSV.transform(appended));
        }
    break;

  case 589:
    {
          todoReminder("support AssemblyStatement (2)");
          System.exit(0);
          Multiverse<DeclarationOrStatementValue> m = new Multiverse<DeclarationOrStatementValue>();
          m.add(new DeclarationOrStatementValue("asm2"),subparser.getPresenceCondition());
          setTransformationValue(value, m);
        }
    break;

  case 590:
    {
          todoReminder("support AssemblyStatement (3)");
          System.exit(0);
          Multiverse<DeclarationOrStatementValue> m = new Multiverse<DeclarationOrStatementValue>();
          m.add(new DeclarationOrStatementValue("asm3"),subparser.getPresenceCondition());
          setTransformationValue(value, m);
        }
    break;

  case 591:
    {
          todoReminder("support AssemblyArgument (1)");
          System.exit(0);
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 592:
    {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,5,subparser.getPresenceCondition()).transformation;
          Multiverse<String> sec = (Multiverse<String>)getTransformationValue(subparser,3);
          Multiverse<String> third = (Multiverse<String>)getTransformationValue(subparser,1);
          Multiverse<String> prep2 = sec.prependScalar(":", DesugarOps.concatStrings);
          sec.destruct();
          Multiverse<String> prep3 = third.prependScalar(":", DesugarOps.concatStrings);
          third.destruct();
          Multiverse<String> later = prep2.product(prep3, DesugarOps.concatStrings);
          setTransformationValue(value, first.product(later, DesugarOps.concatStrings));
        }
    break;

  case 593:
    {
          Multiverse<String> first = getCompleteNodeExpressionValue(subparser,3,subparser.getPresenceCondition()).transformation;
          Multiverse<String> sec = (Multiverse<String>)getTransformationValue(subparser,1);
          Multiverse<String> prep = sec.prependScalar(":", DesugarOps.concatStrings);
          sec.destruct();
          
          setTransformationValue(value, first.product(prep, DesugarOps.concatStrings));
        }
    break;

  case 594:
    {
          setTransformationValue(value, getCompleteNodeExpressionValue(subparser, 1, subparser.getPresenceCondition()).transformation);
        }
    break;

  case 595:
    {
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 596:
    {
          setTransformationValue(value, getTransformationValue(subparser,1));
        }
    break;

  case 597:
    {
          setTransformationValue(value, getTransformationValue(subparser,1));
        }
    break;

  case 598:
    {
          Multiverse<String> prev = (Multiverse<String>)getTransformationValue(subparser,3);
          Multiverse<String> cur = (Multiverse<String>)getTransformationValue(subparser,1);
          Multiverse<String> prep = cur.prependScalar(",", DesugarOps.concatStrings);
          cur.destruct();
          
          setTransformationValue(value, prev.product(prep, DesugarOps.concatStrings));
        }
    break;

  case 599:
    {
          todoReminder("typecheck Assemblyoperand (1)");
          ExpressionValue str = getCompleteNodeExpressionValue(subparser,4,subparser.getPresenceCondition());
          ExpressionValue expr = getCompleteNodeExpressionValue(subparser,2,subparser.getPresenceCondition());
          Multiverse<String> temp = expr.transformation;
          Multiverse<String> prepended = temp.prependScalar("(", DesugarOps.concatStrings);
          Multiverse<String> appended = prepended.appendScalar(")", DesugarOps.concatStrings);
          temp.destruct(); prepended.destruct();
          
          setTransformationValue(value, str.transformation.product(appended, DesugarOps.concatStrings));
        }
    break;

  case 600:
    {
          String word = ((Syntax) getNodeAt(subparser, 6).get(0)).getTokenText();
          todoReminder("support Assemblyoperand (2)");
          System.exit(0);
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 601:
    {
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 602:
    {
          todoReminder("support Assemblyclobbersopt (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 603:
    {
          todoReminder("support StringLiteralList (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 604:
    {
          todoReminder("support StringLiteralList (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 605:
    {
          todoReminder("support AssemblyGotoargument (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 606:
    {
          todoReminder("support AssemblyJumpLabels (1)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

  case 607:
    {
          todoReminder("support AssemblyJumpLabels (2)");
          setTransformationValue(value, new Multiverse<String>("", subparser.getPresenceCondition()));
        }
    break;

    }
  return value;
  }
  public void dispatch(int id, Subparser subparser) {
    // no action productions
  }
  /* from desugarer.epilogue */


boolean wrotePrologue = false;
        
// TUTORIAL: this section of the grammar gets copied into the
// resulting parser, specifically the CActions.java class

/***************************************************************************
 **** Semantic actions
 ***************************************************************************/

protected Multiverse<String> declarationAction(List<DeclaringListValue> declaringlistvalues,
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
  Multiverse<String> valuemv = new Multiverse<String>();
  valuemv.add("",pc);
  // loop over each element of the declaration list
  for (DeclaringListValue declaringlistvalue : declaringlistvalues) {
    // unpack type specifier, declarators, and initializers from the transformation value
    Multiverse<TypeSpecifier> typespecifiermv = declaringlistvalue.typespecifier;
    Multiverse<Declarator> declaratormv = declaringlistvalue.declarator;
    Multiverse<Initializer> initializermv = declaringlistvalue.initializer;
    
    // TODO: use typespecifier/declarator to reclassify the
    // tokens as typedef/ident in parsing context

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
                        todoReminder("check that global variables don't have auto; produce a type error");
                        System.exit(1);
                      }

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
                            //if  the length is implcit, we need to manually assign a value
                            entrysb.append(renamedDeclaration.toString(trueInitSize(initializer.getData())));
                          }
                          entrysb.append(semi + "\n");  // semi-colon
                          entrysb.append("{\n" + initArray(renaming, (ArrayT)tempT, initializer.getData(), scope, combinedCond) + "}");
                          recordRenaming(renaming, originalName);
                        }
                      } else {
                        entrysb.append(desugaredDeclaration);
                        entrysb.append(initializer.getData().toString());
                        entrysb.append(semi);  // semi-colon
                        recordRenaming(renaming, originalName);
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
                    entrysb.append("\n");

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
  } // end loop over declaringlistvalues
  if (debug) System.err.println(scope.getSymbolTable());
  return valuemv;
}

public String initStruct(String name, StructOrUnionT t, Initializer i, CContext scope, PresenceCondition p)
{
  //NOTE: All fields are presumably using . as the access method. Chagne this to . / -> depending
  //on the context
  SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(t.getName());
  Multiverse<List<Map.Entry<String,Type>>> m = tagtab.getLists(p);
  //for now, I'm making the assumption all field defs are in order, although this isn't the case.
  //this can be solved by sort each list by it's appended number
  
  //SORT
  
  // for each list, we need to write an if statement for assigning initial values
  // under each pc. We need a list of either expressions to assign, or designators, and
  // go through the list assigning approprietly.

  List<Initializer> inits = i.getList();
  StringBuilder entrysb = new StringBuilder();
   
  for (Element<List<Map.Entry<String,Type>>> e : m) {
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
                  VariableT newT = ((VariableT)e.getData().get(newSpot).getValue());
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
                  entrysb.append(name + "." + ((VariableT)e.getData().get(newSpot).getValue()).getName() + " = " + ((DesignatedInitializer)init).getInitString() + ";\n");
                }
              } else {
                List<Designator> newDesList = new LinkedList<Designator>();
                for (int k = 1; k < d.getListSize(); ++k ) {
                  newDesList.add(d.getDesignator(k));
                }
                Initializer newInit = new DesignatedInitializer(new Designation(newDesList), in);
                if (in.isList()) {
                  VariableT newT = ((VariableT)e.getData().get(newSpot).getValue());
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
                                       ((VariableT)e.getData().get(newSpot).getValue()).getName(),
                                       newDesList,
                                       ((VariableT)e.getData().get(newSpot).getValue()).getType(),
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
            VariableT newT = ((VariableT)e.getData().get(spot).getValue());
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
            entrysb.append(name + "." + ((VariableT)e.getData().get(spot).getValue()).getName() + " = " + init.toString() + ";\n");
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
    SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(((StructOrUnionT)t).getName());
    Multiverse<Entry<Type>> m = tagtab.get(((StructUnionDesignator)d).getName(), p);
    for (Element<Entry<Type>> e : m) {
      Multiverse<String> toAdd = getDesigTransforms(prefix + "." +
                                                    ((VariableT)e.getData().getValue()).getName(),
                                                    newD,
                                                    ((VariableT)e.getData().getValue()).getType(),
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


Multiverse<Map.Entry<String,Type>> getNestedFields(String structId, String fieldId, PresenceCondition pc, CContext scope) {
  System.err.println(structId);
  Multiverse<Map.Entry<String,Type>> result = new Multiverse<Map.Entry<String,Type>>();
  SymbolTable<Type> tagtab = scope.getLookasideTableAnyScope(structId);
  Multiverse<Entry<Type>> m = tagtab.get(fieldId, pc);
  for (Element<Entry<Type>> e  : m) {
    if (e.getData().isUndeclared()) {
      continue;
    }
    //no checking needs to be done here since we know the multiverse returned has no
    //violations
    result.add(new AbstractMap.SimpleImmutableEntry<String,Type>(((VariableT)e.getData().getValue()).getName(),
                                                                 e.getData().getValue()), e.getCondition().and(pc));
  }
  m.destruct();
  //recursive call on anonymous ids
  List<String> anonIds = tagtab.getAnonIds();
  for (String a : anonIds) {
    m = tagtab.get(a, pc);
    for (Element<Entry<Type>> e : m) {
      if (e.getData().isUndeclared()) {
        continue;
      }
      PresenceCondition p = e.getCondition().and(pc);
      VariableT v = ((VariableT)e.getData().getValue());
      if (!v.getType().isStruct() && !v.getType().isUnion()) {
        throw new IllegalStateException("Only structs and unions can be anonymously declared fields");
      }
      Multiverse<Map.Entry<String,Type>> inner = getNestedFields(((StructOrUnionT)v.getType()).getName(), fieldId, p, scope);
      p.delRef();
      //add anonymous id . to front of string.
      //anonymous fields cannot be pointers
      if (!inner.isEmpty()) {
        for (Element<Map.Entry<String,Type>> ei : inner) {
          ei.setData(new AbstractMap.SimpleImmutableEntry<String,Type>(((VariableT)e.getData().getValue()).getName()
                                                                       + " . " + ei.getData().getKey()
                                                                       ,ei.getData().getValue()));
        }

        for (Element<Map.Entry<String,Type>> ei : inner) {
          if (!result.isEmpty()) {
            boolean remade;
            do {
              remade = false;
              for (Element<Map.Entry<String,Type>> er : result) {
                p = er.getCondition().and(ei.getCondition());
                if (!p.isFalse() && !er.getData().getKey().equals("")) {
                  //there is an overlap in presence conditions, which is a type error
                  Multiverse<Map.Entry<String,Type>> newR = new Multiverse<Map.Entry<String,Type>>();
                  for (Element<Map.Entry<String,Type>> en : result) {
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
  public final Multiverse<TypeSpecifier> typespecifier;
  
  /** The declarator */
  public final Multiverse<Declarator> declarator;

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

  /** 
   * This constructor creates a new instance.
   * @param type is the type.
   * @param declarator is the declarator.
   * @param declarator is the initializer.
   */
  private DeclaringListValue(Multiverse<TypeSpecifier> typespecifier,
                             Multiverse<Declarator> declarator,
                             Multiverse<Initializer> initializer) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
    this.initializer = initializer;
  }

  public String toString()
  {
    return "TypeSpec: " + typespecifier.toString() +
      "\nDeclarator: " + declarator.toString() +
      "\nInitializer: " + initializer.toString();
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
  
  /**
   * The cached valid type condition.
   */
  protected PresenceCondition validTypeCondition = null;

  public String toString()
  {
    String ret = "";
    ret += "type:" + type.toString();
    ret += "transform:" + transformation.toString();
    return ret;
  }

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
      /* System.err.println("ELEM: " + elem.getData()); */
      if (! elem.getData().isError()) {
        return false;
      }
    }
    return true;
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

public static class DeclarationOrStatementValue {
  private String mainValue;
  private List<Multiverse<DeclarationOrStatementValue>> children;
  private String childPrepend;
  private boolean isElse;
  private boolean isDo;
  private String childAppend;
  private boolean isDecl;
  private boolean isEmpty;
  public DeclarationOrStatementValue() {
    mainValue = "";
    childPrepend = "";
    childAppend = "";
    children = null;
    isElse = false;
    isDo = false;
    isDecl = false;
    isEmpty = false;
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
    isElse = false;
    isDo = false;
    isDecl = false;
  }
  public void setChildrenBlock(String p, Multiverse<DeclarationOrStatementValue> c, String a) {
    List x = new LinkedList<Multiverse<DeclarationOrStatementValue>>();
    x.add(c);
    setChildrenBlock(p,x,a);
    isEmpty = false;
  }

  public void setChildrenBlock(String p, List<Multiverse<DeclarationOrStatementValue>> c, String a) {
    childPrepend = p;
    children = c;
    childAppend = a;
    isEmpty = false;
  }

  public void setChildrenElse(Multiverse<DeclarationOrStatementValue> a,Multiverse<DeclarationOrStatementValue> b) {
    isElse = true;
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
  
  public String getString(PresenceCondition p, CActions ca) {
    String ret = "";
    int count = 0;
    if (!isDo) {
      ret = mainValue + "\n";
    }
    if (!childPrepend.equals("")) {
      ret += childPrepend + "\n";
    }
    if (!isElse) {
      if (children != null) {
        for (Multiverse<DeclarationOrStatementValue> m : children) {
          for (Element<DeclarationOrStatementValue> e : m) {
            PresenceCondition combinedCond = e.getCondition().and(p);
            if (e.getCondition().and(p).isNotFalse()) {
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
      }
    } else {
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
      ret += "else\n";
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
    }
    if (!childAppend.equals("")) {
      ret += childAppend + "\n";
    }
    if (isDo) {
      ret += mainValue + "\n";
    }
    return ret;
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
  return getCompleteNodeMultiverseValue(getNodeAt(subparser, component), pc);
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
  
    for (Element<Node> elem : nodemv) {
      PresenceCondition combinedCond = pc.and(elem.getCondition());
      ExpressionValue exprval = (ExpressionValue) ((Node) elem.getData()).getProperty(TRANSFORMATION);
      Multiverse<String> transformation_filtered = exprval.transformation.filter(combinedCond);
      Multiverse<Type> type_filtered = exprval.type.filter(combinedCond);
      transformation.addAll(transformation_filtered);
      type.addAll(type_filtered);
      transformation_filtered.destruct(); type_filtered.destruct();
      combinedCond.delRef();
    }
    nodemv.destruct();
  
    // it should not be possible to have an empty expression, as long as
    // the pc correponds to the current subparsers's pc.
    assert ! transformation.isEmpty();
    assert ! type.isEmpty();

    return new ExpressionValue(transformation, type);
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

private String emitStatementDSV(Multiverse<DeclarationOrStatementValue> allStatementConfigs, PresenceCondition pc) {
  StringBuilder sb = new StringBuilder();
  if (allStatementConfigs.size() > 1) {
    sb.append("\n{");
  }
  for (Multiverse.Element<DeclarationOrStatementValue> statement : allStatementConfigs) {
    PresenceCondition combinedCond = statement.getCondition().and(pc);
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
    for (Object child : node) {

      if (child instanceof PresenceCondition) {
        pc = (PresenceCondition)child;
      } else if (child instanceof Node) {
        // assumes that all static choice nodes are mutually exclusive and already ANDed with the subparser's pc
        Multiverse<Node> someChildren = staticCondToMultiverse((Node)child, pc);
        allConfigs.addAll(someChildren);
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
    sb.append(String.format("extern const bool %s;\n", condVars.get(hash)));
  }

  sb.append(String.format("%s {\n%s\n%s\n",
                          static_initializer_signature,
                          recordedRenamings.toString(),
                          staticConditionRenamings.toString(),
                          invalidGlobals.toString()));
  if (showParseError && CContext.getParseErrorCond().isNotFalse()) {
  sb.append("if (" + parseErrorCond +
            ")\n{\n__static_parse_error(\"Unable to parse\");\n}\n");
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
    int key = cond.hashCode();
    if (condVars.containsKey(key)) {
      return condVars.get(key);
    } else {
      String cvar = freshCId(String.format("static_condition_%s", unitUID));
      condVars.put(key, cvar);
      staticConditionRenamings.append(String.format("__static_condition_renaming(\"%s\", \"%s\");\n", cvar, cond.toString()));
      return cvar;
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
}
