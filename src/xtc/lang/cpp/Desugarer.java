/*
 * SuperC
 * Copyright (C) 2019 Paul Gazzillo
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
package xtc.lang.cpp;

import java.lang.StringBuilder;

import java.io.File;
import java.io.Reader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.StringReader;
import java.io.OutputStreamWriter;
import java.io.IOException;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Random;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.lang.cpp.CContext.SymbolTable.STField;

import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.Constants;

class Desugarer {
  /** The instance of this class */
  private static Desugarer ref;

  private static long varcount = 0;


  /**
   * The path of the header file that will contain the extern
   * declarations of the desugared macros.  Macros are equivalent to
   * C variables that are global to all compilation units.
   */
  private String MACRO_HEADER = "desugared_macros.h";

  /** A reference to the presence condition manager */
  PresenceConditionManager presenceConditionManager;

  SymbolTable symtab;

  /** Get the instance of this class */
  public static Desugarer getInstance(PresenceConditionManager presenceConditionManager) {
    if (null == ref) {
      ref = new Desugarer(presenceConditionManager);
    }
    return ref;
  }

  protected Desugarer(PresenceConditionManager presenceConditionManager) {
    this.presenceConditionManager = presenceConditionManager;
    this.symtab = new SymbolTable();
  }

  /**
   * Print an AST (or a subtree of it) in C source form.
   *
   * @param n An AST or a subtree.
   * @param presenceCondition The current nested presence condition.
   * @param writer The writer.
   * @throws IOException Because it writes to output.
   */
  public void desugarConditionals(Node n, OutputStreamWriter writer)
    throws IOException {

    // TODO: allow user to specify the macro header file name

    writer.write(String.format("#include \"%s\" // configuration macros converted to C variables\n", MACRO_HEADER));

    desugarConditionalsNode(n,
                            presenceConditionManager.new PresenceCondition(true),
                            null,
                            writer);

    // multiplex the main method, if it was defined
    if (symtab.hasRenaming("main")) {
      writer.write(multiplexSimple("main", symtab.getRenaming("main"), "int argc, char **argv", "(argc, argv)"));
    }
  }

  // /**
  //  * Take a presence condition and generate the "if (cond)" part of an
  //  * if-statement.  If the condition is true, then don't emit it.
  //  */
  // public String generateIf(PresenceCondition cond) {
  //   StringBuilder sb = new StringBuilder();
  //   sb.append("if (");
  //   sb.append(pc.toString());
  //   sb.append(")");
  //   return sb.toString();
  // }

  /**
   * Multiplex the renamed function definitions by creating a new
   * function using the original that just calls renamed functions
   * under their respective configurations.  This simple version
   * assumes that all renamed functions share the same type (which
   * does not necessarily hold in general).
   */
  public String multiplexSimple(String name, Multiverse renaming, String formals, String call) {
    // TODO: check whether the renaming is actually a function
    StringBuilder sb = new StringBuilder();
    sb.append(String.format("%s(%s) { // multiplexed function\n", name, formals));
    Iterator<Pair<StringBuilder, PresenceCondition>> it_renaming = renaming.iterator();
    while (it_renaming.hasNext()) {
      Pair<StringBuilder, PresenceCondition> next_renaming = it_renaming.next();
      String ident = next_renaming.getKey().toString();
      PresenceCondition pc = next_renaming.getValue();
      sb.append("if (");
      sb.append(PCtoString(pc));
      sb.append(") {\n");
      sb.append(ident);
      sb.append(call);
      sb.append(";\n");
      sb.append("}\n");
    }
    sb.append("}\n");
    return sb.toString();
  }

  private HashMap<String, String> BoolExprs = new HashMap<String, String>();

  public void printBDDC(PresenceCondition cond, OutputStreamWriter writer) throws IOException {
    List allsat = (List) cond.getBDD().allsat();
    ArrayList<String> currentExprs;
    String CBoolExpr;
    boolean firstTerm = true;
    boolean firstTermOuter = true;

    for (Object o : allsat) {
      if (!firstTermOuter)
        writer.write(" || ");
      firstTermOuter = false;
      currentExprs = getBoolExprs((byte[]) o, cond);
      for (String CPPBoolExpr : currentExprs) {
        if (!firstTerm)
          writer.write(" && ");
        firstTerm = false;
        if (BoolExprs.isEmpty() || !BoolExprs.containsKey(CPPBoolExpr)) {
          // generates a new C boolean expression with hashcode appended, then adds it to hashmap and prints it
          CBoolExpr = generateBoolExpr(CPPBoolExpr);
          BoolExprs.put(CPPBoolExpr, CBoolExpr);
          writer.write(CBoolExpr);
        } else if (BoolExprs.containsKey(CPPBoolExpr)) {
          // prints the mapped C expression
          CBoolExpr = BoolExprs.get(CPPBoolExpr);
          writer.write(CBoolExpr);
        }
      }
    }
  }

  public String PCtoString(PresenceCondition cond) {
    List allsat = (List) cond.getBDD().allsat();
    ArrayList<String> currentExprs;
    String CBoolExpr;
    StringBuilder sb = new StringBuilder();
    boolean firstTerm = true;
    boolean firstTermOuter = true;

    for (Object o : allsat) {
      if (!firstTermOuter)
        sb.append(" || ");
      firstTermOuter = false;
      currentExprs = getBoolExprs((byte[]) o, cond);
      for (String CPPBoolExpr : currentExprs) {
        if (!firstTerm)
          sb.append(" && ");
        firstTerm = false;
        if (BoolExprs.isEmpty() || !BoolExprs.containsKey(CPPBoolExpr)) {
          // generates a new C boolean expression with hashcode appended, then adds it to hashmap and returns it
          CBoolExpr = generateBoolExpr(CPPBoolExpr);
          BoolExprs.put(CPPBoolExpr, CBoolExpr);
          sb.append(CBoolExpr);
        } else /* if (BoolExprs.containsKey(CPPBoolExpr)) */ {
          // returns the mapped C expression
          CBoolExpr = BoolExprs.get(CPPBoolExpr);
          sb.append(CBoolExpr);
        }
      }
    }
    return sb.toString();
  }

  // returns a list of every expression in the BDD
  public ArrayList<String> getBoolExprs(byte[] sat, PresenceCondition cond) {
    ArrayList<String> allExprs = new ArrayList<String>();
    for (int i = 0; i < sat.length; i++) {
      if (sat[i] == 1) {
        // builds up a list of the (CPP) boolean expressions within the PresenceCondition
        allExprs.add(cond.presenceConditionManager().getVariableManager().getName(i));
      }
    }
    return allExprs;
  }

  // returns a new (valid C) boolean expression, with hashcode appended
  public String generateBoolExpr(String CPPBoolExpr) {
    StringBuilder sb = new StringBuilder();
    sb.append("_C_");
    sb.append(CPPBoolExpr.hashCode());
    return sb.toString();
  }

  /**
   * Print an AST (or a subtree of it) in C source form.
   *
   * @param n An AST or a subtree.
   * @param presenceCondition The current nested presence condition.
   * @param writer The writer.
   * @throws IOException Because it writes to output.
   */
  public void desugarConditionalsNode(Node n, PresenceCondition presenceCondition,
                                      PresenceCondition lastPresenceCondition,
                                      OutputStreamWriter writer)
    throws IOException {

    if (n.isToken()) {
      writer.write(n.getTokenText());
      writer.write(" ");

    } else if (n instanceof Node) {

      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {

        PresenceCondition newPresenceCondition = lastPresenceCondition;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            PresenceCondition branchCondition = (PresenceCondition) bo;
            lastPresenceCondition = newPresenceCondition;
            newPresenceCondition = presenceCondition.and(branchCondition);
          } else if (bo instanceof Node) {
            if (((Node) bo).getName().equals("Conditional")) {
              desugarConditionalsNode((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
            } else if (((Node) bo).getName().equals("FunctionDefinition")) {
              writer.write("\n");
              desugarConditionalsFunctionDefinition((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
              writer.write("\n");
            } else if (((Node) bo).getName().equals("Declaration")) {
              writer.write("\n");
              desugarConditionalsDeclaration((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
              writer.write("\n");
            } else if (((Node) bo).getName().equals("CompoundStatement")) {
              for (Object cs_child : (Node) bo) {
                desugarConditionalsNode((Node) cs_child, newPresenceCondition, lastPresenceCondition, writer);
              }
            } else {
              desugarConditionalsStatement((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
            }
          }
        }

      } else {
        for (Object o : n) {
          desugarConditionalsNode((Node) o, presenceCondition, lastPresenceCondition, writer);
        }
      }

    } else {
      throw new UnsupportedOperationException("unexpected type");
    }
  }

  public void desugarConditionalsFunctionDefinition(Node n, PresenceCondition presenceCondition,
                                                    PresenceCondition lastPresenceCondition,
                                                    OutputStreamWriter writer)
    throws IOException {

    // traverse the the declaration and traverse the function prototype, updating the conditionals as you go (i.e., hoistNode on each

    // prototypemv = hoistNode(prototype, mv)

    // prototype is the first node

    // hoist the function prototype first
    // Multiverse protomv = hoistNode(n.getNode(0), new Multiverse("", presenceCondition));
    Multiverse mv = new Multiverse("", presenceCondition);
    Multiverse ident = new Multiverse("", presenceCondition);
    Pair<Multiverse, Multiverse> result = hoistDeclaration(n.getNode(0), mv, ident);
    Multiverse protomv = result.getKey();
    Multiverse proto_ident = result.getValue();

    // Multiverse mv = new Multiverse("", presenceCondition);
    // Multiverse result = hoistNode(n, mv);
    // writer.write(result.toString());
    // mv.destruct();

    // key for performance, get the final string for the whole
    // function once, then duplicate it under multple function
    // signagures: use stringwriter only if there are multiple
    // function prototypes

    // get compound statement, or get a list of compound statements,
    // each with a different presence condition.  each version will be
    // its own if block. essentially, we are replacing the compound
    // statement with our own set of compound statements, each under a
    // different conditional.

    // // TODO: create a function that dispatches the original function to the
    // // hoisted functions.  we need to join the types, however
    // StringBuilder multiplexer = new StringBuilder();

    Iterator<Pair<StringBuilder, PresenceCondition>> it_proto = protomv.iterator();
    Iterator<Pair<StringBuilder, PresenceCondition>> it_ident = proto_ident.iterator();
    while (it_proto.hasNext() && it_ident.hasNext()) {
      Pair<StringBuilder, PresenceCondition> next_ident = it_ident.next();
      String elem_ident = next_ident.getKey().toString();
      PresenceCondition pc = next_ident.getValue();
      String renamed_ident = mangleRenaming(FUNCPREFIX, elem_ident);
      symtab.addRenaming(elem_ident, renamed_ident, pc);  // TODO: keep track of types
      String elem_proto = it_proto.next().getKey().toString();
      writer.write(elem_proto.toString().replace(" " +  elem_ident + " ", " " + renamed_ident + " /* renamed from " + elem_ident + " */ "));
      writer.write("{\n");
      writer.write("if (");
      printBDDC(pc, writer);
      writer.write(") { /* from static conditional around function definition */\n");
      writer.flush();
      for (int i = 1; i < n.size(); i++) {
        desugarConditionalsNode(n.getNode(i), presenceCondition, lastPresenceCondition, writer);
      }
      writer.write("\n}\n");
      writer.write("}\n");
    }
    mv.destruct();
    ident.destruct();

    // if (protomv.size() == 1) {
    //   writer.write(protomv.get(0).getKey().toString());
    //   writer.write("{\n");
    //   writer.write("if (");
    //   protomv.get(0).getValue().print(writer);
    //   writer.write(") { /* from static conditional around function definition */\n");
    //   writer.flush();
    //   for (int i = 1; i < n.size(); i++) {
    //     desugarConditionalsNode(n.getNode(i), presenceCondition, lastPresenceCondition, writer);
    //   }
    //   writer.write("\n}\n");
    //   writer.write("}\n");
    // } else {
    //   System.err.println("TODO support multiple function prototypes");
    //   writer.write(protomv.toString());
    // }

    // TODO: hoist the function prototype to have a complete one
    // can't put the function inside of a conditional, instead we need to rename and update the symbol table
    // then put the condition of the function inside of the compound statement

    // there are several options: either multiplex with a conditional
    // inside (hard, because we don't know all the function defs yet;
    // rename if inside (easier, and can do type-checking at function
    // call sites).  still probably need to put the conditional inside
    // the function, because of any dynamic function calls via
    // pointers


    // TODO: write the conditional inside of the compound statement.
    // probably use a different desugaring method specific to
    // functiondefinitions that holds the function's conditional.
    // this also needs to be able to make complete functions for each
    // prototype and explode it.
  }

  private final static char[] charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".toCharArray();
  private final static Random random = new Random();
  private final static int RAND_SIZE = 5;
  private final static String VARPREFIX = "V";  // prefix for renamed variable
  private final static String FUNCPREFIX = "F";  // prefix for renamed function
  private final static String CONFIGPREFIX = "C";  // prefix for config macro
  private final static String DEFINEDPREFIX = "D";  // prefix for config macro's definedness variable
  protected String randomString(int string_size) {
    StringBuilder randomstring = new StringBuilder();
    for (int i = 0; i < string_size; i++) {
      randomstring.append(charset[random.nextInt(charset.length)]);
    }
    return randomstring.toString();
  }

  protected String mangleRenaming(String prefix, String ident) {
    return String.format("_%s%d%s_%s", prefix, varcount++, randomString(RAND_SIZE), ident);
  }

  public void desugarConditionalsDeclaration(Node n, PresenceCondition presenceCondition,
                                             PresenceCondition lastPresenceCondition,
                                             OutputStreamWriter writer)
    throws IOException {

    // TODO: need to merge extern declarations.  perhaps we can just take the largest size extern and do truncation?

    // hoist conditionals around declarations into mv and collect each
    // configuration's identifier in ident
    Multiverse mv = new Multiverse("", presenceCondition);
    Multiverse ident = new Multiverse("", presenceCondition);
    Pair<Multiverse, Multiverse> result = hoistDeclaration(n, mv, ident);
    Multiverse result_decl = result.getKey();
    Multiverse result_ident = result.getValue();

    // (1) rename each variable by adding a increasing counter
    // (varcount), then (2) print each declaration (replacing the var
    // name) without its static conditional.  (3) store the mapping
    // between original and renamed variable in a symbol table for
    // this scope.
    // TODO: use better name mangling by generating random string
    Iterator<Pair<StringBuilder, PresenceCondition>> it_decl = result_decl.iterator();
    Iterator<Pair<StringBuilder, PresenceCondition>> it_ident = result_ident.iterator();
    while (it_decl.hasNext() && it_ident.hasNext()) {
      Pair<StringBuilder, PresenceCondition> next_ident = it_ident.next();
      String elem_ident = next_ident.getKey().toString();
      PresenceCondition pc = next_ident.getValue();
      String renamed_ident = mangleRenaming(VARPREFIX, elem_ident);
      symtab.addRenaming(elem_ident, renamed_ident, pc);
      String elem_decl = it_decl.next().getKey().toString();
      // TODO: should probably have a nicer way to replace the name
      writer.write(elem_decl.toString().replace(" " +  elem_ident + " ", " " + renamed_ident + " /* renamed from " + elem_ident + " */ "));
    }
    mv.destruct();
    ident.destruct();

    System.err.println(symtab.originalToNew);
  }

  public void desugarConditionalsStatement(Node n, PresenceCondition presenceCondition,
                                           PresenceCondition lastPresenceCondition,
                                           OutputStreamWriter writer)
    throws IOException {

    Multiverse mv = new Multiverse("", presenceCondition);
    Multiverse result = hoistStatement(n, mv);
    mv.destruct();
    for (Pair<StringBuilder, PresenceCondition> elem : result) {
      String str = elem.getKey().toString();
      PresenceCondition cond = elem.getValue();
      // if (null != lastPresenceCondition) {
      //   System.err.println("jklfds " + cond.toString());
      //   System.err.println("jklfds " + lastPresenceCondition.toString());
      // }
      if (null != lastPresenceCondition && cond.equals(lastPresenceCondition)) {
        printBDDC(cond, writer);
        writer.write("\n");
        lastPresenceCondition.delRef();
        lastPresenceCondition = cond;
        lastPresenceCondition.addRef();
      } else {
        if (str.length() > 0) {
          writer.write("if (");
          printBDDC(cond, writer);
          writer.write(") { /* from static conditional around statement */\n");
          writer.write(str);
          writer.write("\n}\n");
        } else {
          writer.write("/* omitted empty node */\n");
        }
      }
      if (null == lastPresenceCondition) {
        lastPresenceCondition = cond;
        lastPresenceCondition.addRef();
      }
    }
    if (null != lastPresenceCondition) {
      lastPresenceCondition.delRef();
    }
    result.destruct();

    // TODO: type checking to make sure the resulting uses of symbols
    // does not cause a type error

    // optimization: dedup statements and union presence conditions
  }

  /**
   * Caller destructs the multiverse that it passes.
   */
  public Multiverse hoistNode(Node n, Multiverse mv)
    throws IOException {

    if (n.isToken()) {
      // when we have a single token, append it's string to all lifted
      // strings
      mv.addToAll(n.getTokenText());
      mv.addToAll(" ");
      return mv;
    } else if (n instanceof Node) {
      // when we have a static conditional, recursively add strings to
      // the entire multiverse by performing a cartesian product with
      // the input multiverse
      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
        List<Multiverse> newmvs = new LinkedList<Multiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            Multiverse newmv = hoistNode((Node) bo, new Multiverse("", branchCondition));
            newmvs.add(new Multiverse(mv, newmv));
            newmv.destruct();
          }
        }
        Multiverse combinedmv = new Multiverse(newmvs);
        for (Multiverse elem : newmvs) {
          elem.destruct();
        }
        return combinedmv;

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        Multiverse result = new Multiverse(mv);
        for (Object o : n) {
          Multiverse newResult = hoistNode((Node) o, result);
          if (newResult != result) {
            // the token case does not create a new multiverse, just
            // returning the one passed in, so only destroy if the
            // passed in multiverse is not the same as the returned
            // one
            result.destruct();
          }
          result = newResult;
        }
        return result;
      }
    } else {
      throw new UnsupportedOperationException("unexpected type");
    }
  }

  /**
   * Caller destructs the multiverse that it passes.
   */
  public Pair<Multiverse, Multiverse> hoistDeclaration(Node n, Multiverse mv, Multiverse ident)
    throws IOException {

    if (n instanceof GNode
        && ((GNode) n).hasName("SimpleDeclarator")) {
      String identstr = ((Syntax) n.get(0)).toLanguage().toString();
      if (! ident.allEquals("")) {
        // the grammar should make this error impossible
        System.err.println("ERROR: there should only be one identifier per declaration");
      }
      ident.addToAll(identstr);
    }


    if (n.isToken()) {
      // when we have a single token, append it's string to all lifted
      // strings
      mv.addToAll(n.getTokenText());
      mv.addToAll(" ");
      return new Pair<Multiverse, Multiverse>(mv, ident);
    } else if (n instanceof Node) {
      // when we have a static conditional, recursively add strings to
      // the entire multiverse by performing a cartesian product with
      // the input multiverse
      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
        List<Multiverse> newmvs = new LinkedList<Multiverse>();
        List<Multiverse> newidents = new LinkedList<Multiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            Pair<Multiverse, Multiverse> retval
              = hoistDeclaration((Node) bo, new Multiverse("", branchCondition), new Multiverse("", branchCondition));
            Multiverse newmv = retval.getKey();
            Multiverse newident = retval.getValue();
            newmvs.add(new Multiverse(mv, newmv));
            newmv.destruct();
            newidents.add(new Multiverse(ident, newident));
            newident.destruct();
          }
        }
        Multiverse combinedmv = new Multiverse(newmvs);
        for (Multiverse elem : newmvs) {
          elem.destruct();
        }
        return new Pair<Multiverse, Multiverse>(combinedmv, ident);

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        Pair<Multiverse, Multiverse> result = new Pair<Multiverse, Multiverse>(new Multiverse(mv), ident);
        for (Object o : n) {
          Pair<Multiverse, Multiverse> newResult = hoistDeclaration((Node) o, result.getKey(), result.getValue());
          if (newResult.getKey() != result.getKey()) {
            // the token case does not create a new multiverse, just
            // returning the one passed in, so only destroy if the
            // passed in multiverse is not the same as the returned
            // one
            result.getKey().destruct();
          }
          result = newResult;
        }
        return result;
      }
    } else {
      throw new UnsupportedOperationException("unexpected type");
    }
  }

  /**
   * This hoists conditionals around complete statements, replacing
   * any identifiers with all their renamings.  Caller destructs the
   * multiverse that it passes.
   */
  public Multiverse hoistStatement(Node n, Multiverse mv)
    throws IOException {

    // replace identifiers with its renamings
    if (n instanceof GNode
        && ((GNode) n).hasName("PrimaryIdentifier")) {

      String identstr = ((Syntax) n.get(0)).toLanguage().toString();
      if (! symtab.hasRenaming(identstr)) {
        System.err.println("ERROR: there is a use of an undefined variable: " + identstr);
        System.exit(1);
      }
      Multiverse renaming = symtab.getRenaming(identstr);
      Multiverse newmv = new Multiverse(mv, renaming);
      renaming.destruct();
      newmv.addToAll(" ");
      return newmv;
    }

    if (n.isToken()) {
      // when we have a single token, append it's string to all lifted
      // strings
      mv.addToAll(n.getTokenText());
      mv.addToAll(" ");
      return mv;
    } else if (n instanceof Node) {
      // when we have a static conditional, recursively add strings to
      // the entire multiverse by performing a cartesian product with
      // the input multiverse
      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
        List<Multiverse> newmvs = new LinkedList<Multiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            Multiverse newmv = hoistStatement((Node) bo, new Multiverse("", branchCondition));
            newmvs.add(new Multiverse(mv, newmv));
            newmv.destruct();
          }
        }
        Multiverse combinedmv = new Multiverse(newmvs);
        for (Multiverse elem : newmvs) {
          elem.destruct();
        }
        return combinedmv;

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        Multiverse result = new Multiverse(mv);
        for (Object o : n) {
          Multiverse newResult = hoistStatement((Node) o, result);
          if (newResult != result) {
            // the token case does not create a new multiverse, just
            // returning the one passed in, so only destroy if the
            // passed in multiverse is not the same as the returned
            // one
            result.destruct();
          }
          result = newResult;
        }
        return result;
      }
    } else {
      throw new UnsupportedOperationException("unexpected type");
    }
  }

  public class Multiverse implements Iterable<Pair<StringBuilder, PresenceCondition>> {
    List<Pair<StringBuilder, PresenceCondition>> contents;

    /**
     * Construct a new multiverse
     */
    public Multiverse(String initstring, PresenceCondition initcond) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      StringBuilder sb = new StringBuilder();
      sb.append(initstring);
      Pair<StringBuilder, PresenceCondition> elem = new Pair<StringBuilder, PresenceCondition>(sb, initcond);
      initcond.addRef();
      contents.add(elem);
    }

    /**
     * Construct a new multiverse from two multiverses using the
     * cartesian product.
     */
    public Multiverse(Multiverse a, Multiverse b) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (Pair<StringBuilder, PresenceCondition> elem1 : a.contents) {
        for (Pair<StringBuilder, PresenceCondition> elem2 : b.contents) {
          StringBuilder sb = new StringBuilder(elem1.getKey());
          sb.append(elem2.getKey());
          PresenceCondition pc = elem1.getValue().and(elem2.getValue());
          if (! pc.isFalse()) { // trim infeasible combinations
            contents.add(new Pair<StringBuilder, PresenceCondition>(sb, pc));
          }
        }
      }
    }

    /**
     * Construct a new multiverse by combining a list of multiverses.
     * It is up to the caller to destruct the multiverses in the list.
     */
    public Multiverse(List<Multiverse> mvs) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (Multiverse mv : mvs) {
        for (Pair<StringBuilder, PresenceCondition> elem : mv.contents) {
          StringBuilder sb = new StringBuilder(elem.getKey());
          PresenceCondition pc = elem.getValue();
          elem.getValue().addRef();
          contents.add(new Pair<StringBuilder, PresenceCondition>(sb, pc));
        }
      }
    }

    /**
     * The copy constructor.
     */
    public Multiverse(Multiverse mv) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (Pair<StringBuilder, PresenceCondition> elem : mv.contents) {
        StringBuilder sb = new StringBuilder(elem.getKey());
        PresenceCondition pc = elem.getValue();
        elem.getValue().addRef();
        contents.add(new Pair<StringBuilder, PresenceCondition>(sb, pc));
      }
    }

    /**
     * Decrement the references of all presence conditions and remove
     * the string builders.  Be sure to do this once you no longer
     * need the multiverse, e.g., after constructing a new multiverse
     * using this one.  The multiverse will no longer be useable after
     * calling this function.
     */
    public void destruct() {
      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        // StringBuilder sb = elem.getKey();
        PresenceCondition pc = elem.getValue();
        pc.delRef();
      }
      contents.clear();
      contents = null;
    }

    public void addToAll(String str) {
      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        StringBuilder sb = elem.getKey();
        sb.append(str);
      }
    }

    public boolean allEquals(String str) {
      boolean flag = true;
      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        StringBuilder sb = elem.getKey();
        flag = flag && sb.toString().equals(str);
      }
      return flag;
    }

    /**
     * Get an element of the list.  Warning, the backing storage is a
     * linked list, so this may only be efficient for get(0).
     */
    public Pair<StringBuilder, PresenceCondition> get(int index) {
      return contents.get(0);
    }

    public int size() {
      return contents.size();
    }

    public Iterator<Pair<StringBuilder, PresenceCondition>> iterator() {
      return contents.iterator();
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();

      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        sb.append(elem.toString());
        sb.append("\n");
      }

      return sb.toString();
    }
  }

  protected class Pair<T, U> {
    final T key;
    final U value;

    public Pair(T initkey, U initvalue) {
      key = initkey;
      value = initvalue;
    }

    public T getKey() {
      return key;
    }

    public U getValue() {
      return value;
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();

      sb.append(getKey().toString());
      sb.append(": ");
      sb.append(getValue().toString());

      return sb.toString();
    }
  }

  protected class SymbolTable {
    SymbolTable parent;
    Map<String, Pair<String, PresenceCondition>> newToOriginal;
    Map<String, Multiverse> originalToNew;

    public SymbolTable(SymbolTable parent) {
      this.parent = null;
      this.newToOriginal = new HashMap<String, Pair<String, PresenceCondition>>();
      this.originalToNew = new HashMap<String, Multiverse>();
    }

    public SymbolTable() {
      this(null);
    }

    public boolean isTop() {
      return null == parent;
    }

    public boolean containsLocal(String localvar) {
      if (originalToNew.containsKey(localvar)
          && originalToNew.get(localvar).size() > 0) {
        return true;
      } else {
        return false;
      }
    }

    // TODO: contains, recurisvely search through parent scope

    public void addRenaming(String var, String renamed, PresenceCondition cond) {
      assert null == newToOriginal.put(renamed, new Pair<String, PresenceCondition>(var, cond));
      cond.addRef();
      Multiverse mv = new Multiverse(renamed, cond);
      cond.addRef();
      if (! originalToNew.containsKey(var)) {
        originalToNew.put(var, mv);
      } else {
        Multiverse oldmv = originalToNew.get(var);
        List<Multiverse> list = new LinkedList<Multiverse>();
        list.add(oldmv);
        list.add(mv);
        Multiverse combinedmv = new Multiverse(list);
        oldmv.destruct();
        mv.destruct();
        originalToNew.put(var, combinedmv);
      }
    }

    public boolean hasRenaming(String var) {
      return originalToNew.containsKey(var);
    }

    /**
     * Get the renamings.  This will create a copy of the underlying
     * multiverse that the caller is responsible for destructing.
     * This will return null if no renaming is registered.
     */
    public Multiverse getRenaming(String var) {
      if (! originalToNew.containsKey(var)) {
        return null;
      } else {
        return new Multiverse(originalToNew.get(var));
      }
    }
  }
}
