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

import xtc.type.Type;
import xtc.type.IntegerT;
import xtc.type.NumberT;
import xtc.type.StructT;
import xtc.type.VariableT;

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

    writer.write(String.format("#include <stdbool.h>\n"));
    writer.write(String.format("#include \"%s\" // configuration macros converted to C variables\n", MACRO_HEADER));

    cConditionTagger(n, presenceConditionManager.new PresenceCondition(true), null);

    StringBuilder sb = new StringBuilder();

    for (String originalExpr : allCBoolExprs.keySet()) {
      sb.append(originalExpr);
      sb.deleteCharAt(0);
      sb.setLength(sb.length() - 1);
      writer.write("extern bool " + allCBoolExprs.get(originalExpr) + "; " + "/* renamed from " + sb.toString() + " */" + "\n");
      writer.write("extern bool " + allCBoolExprs.get(originalExpr) + "_DEFINED;" + "\n");
      sb.setLength(0);
    }

    desugarConditionalsNode(n,
                            presenceConditionManager.new PresenceCondition(true),
                            null,
                            writer);

    // multiplex the main method, if it was defined
    if (symtab.hasRenaming("main")) {
      writer.write("int ");  // TODO the symbol table needs to store type information for renamed symbols
      writer.write(multiplexSimple("main", symtab.getRenaming("main"), "int argc, char **argv", "(argc, argv)"));
    }
  }

  HashMap<String, String> allCBoolExprs = new HashMap<String, String>();

  // recursively moves through the tree and tags each node with its presence condition in valid C
  public void cConditionTagger(Node n, PresenceCondition presenceCondition, PresenceCondition lastPresenceCondition) throws IOException {
    n.setProperty("C_PC", PCtoString(presenceCondition));

    if (n.isToken()) {
      return;
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
                cConditionTagger((Node) bo, newPresenceCondition, lastPresenceCondition);
              } else if (((Node) bo).getName().equals("FunctionDefinition")) {
                cConditionTagger((Node) bo, newPresenceCondition, lastPresenceCondition);
              } else if (((Node) bo).getName().equals("Declaration")) {
                cConditionTagger((Node) bo, newPresenceCondition, lastPresenceCondition);
              } else if (((Node) bo).getName().equals("CompoundStatement")) {
                for (Object cs_child : (Node) bo) {
                  cConditionTagger((Node) cs_child, newPresenceCondition, lastPresenceCondition);
                }
              } else {
                cConditionTagger((Node) bo, newPresenceCondition, lastPresenceCondition);
              }
            }
          }

        } else {
          for (Object o : n) {
            cConditionTagger((Node) o, presenceCondition, lastPresenceCondition);
          }
        }
        return;
    } else {
      throw new UnsupportedOperationException("unexpected type");
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
  public String multiplexSimple(String name, TypedStringMultiverse renaming, String formals, String call) {
    // TODO: check whether the renaming is actually a function
    StringBuilder sb = new StringBuilder();
    sb.append(String.format("%s(%s) { // multiplexed function\n", name, formals));
    Iterator<Pair<Pair<StringBuilder, Type>, PresenceCondition>> it_renaming = renaming.iterator();
    while (it_renaming.hasNext()) {
      Pair<Pair<StringBuilder, Type>, PresenceCondition> next_renaming = it_renaming.next();
      Pair<StringBuilder, Type> inner_pair = next_renaming.getKey();
      String ident = inner_pair.getKey().toString();
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

   if (cond.getBDD().isOne()) {
     writer.write("1");
     return;
   } else if (cond.getBDD().isZero()) {
     writer.write("0");
     return;
   }

   for (Object o : allsat) {
     if (!firstTermOuter)
       writer.write(" || ");
     firstTermOuter = false;
     currentExprs = getBoolExprs((byte[]) o, cond);
     firstTerm = true;
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
     } else if (sat[i] == 0) {
       allExprs.add("!" + cond.presenceConditionManager().getVariableManager().getName(i));
     }
   }
   return allExprs;
 }

 // returns a new (valid C) boolean expression, with hashcode appended
 public String generateBoolExpr(String CPPBoolExpr) {
   StringBuilder sb = new StringBuilder();
   boolean falseExpr = false;
   boolean definedExpr = false;

   // need to remove the '!' character from the string, so that it doesn't change the hashcode (then append it later)
   if (CPPBoolExpr.contains("!")) {
     falseExpr = true;
     sb.append(CPPBoolExpr);

     // if there is a '!' character, it will be at the 0th position of sb
     sb.deleteCharAt(0);
     CPPBoolExpr = sb.toString();
     sb.setLength(0);
   }

   // need to remove "defined" from the string, so that it doesn't affect the hashcode (then append it later)
   if (CPPBoolExpr.contains("defined")) {
     definedExpr = true;
     sb.append(CPPBoolExpr);

     // if the expression is a "defined" expression, it will be in the form (defined <>)
     // note that there will not be a '!' character by this point.
     for (int i = 0; i <= 7; i++)
       sb.deleteCharAt(1);

     CPPBoolExpr = sb.toString();
     sb.setLength(0);
   }

   sb.append("_C_");
   sb.append(CPPBoolExpr.hashCode());

   if (sb.charAt(3) == '-')
     sb.replace(3, 4, "n"); // replaces the '-' with 'n'

   if (!allCBoolExprs.containsKey(CPPBoolExpr)) {
     allCBoolExprs.put(CPPBoolExpr, sb.toString());
   }

   sb.setLength(0);

   if (falseExpr)
     sb.append("!");

   sb.append("_C_");
   sb.append(CPPBoolExpr.hashCode());

   if (definedExpr)
     sb.append("_DEFINED");

   // the expression cannot have a '-' character in it (because it would evaluate as subtraction)
   if (falseExpr) {
     // if the expression is false, then the '-' will come later in the string due to the additional '!' character
     if (sb.charAt(4) == '-') {
       sb.replace(4, 5, "n"); // replaces the '-' with 'n'
     }
   } else {
     if (sb.charAt(3) == '-') {
       sb.replace(3, 4, "n"); // replaces the '-' with 'n'
     }
   }

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
    // StringMultiverse protomv = hoistNode(n.getNode(0), new StringMultiverse("", presenceCondition));
    StringMultiverse mv = new StringMultiverse("", presenceCondition);
    StringMultiverse ident = new StringMultiverse("", presenceCondition);
    Pair<StringMultiverse, StringMultiverse> result = hoistDeclaration(n.getNode(0), mv, ident);
    StringMultiverse protomv = result.getKey();
    StringMultiverse proto_ident = result.getValue();

    // StringMultiverse mv = new StringMultiverse("", presenceCondition);
    // StringMultiverse result = hoistNode(n, mv);
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
      Type type = new IntegerT(NumberT.Kind.INT);  // TODO: keep track of types
      symtab.addRenaming(elem_ident, renamed_ident, type, pc);
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
    // don't want to exceed c identifier length limit (31)
    if (ident.length() > 22) {
      // shorten ident to be at max, 22 chars
      StringBuilder sb = new StringBuilder(ident);
      sb = sb.delete(23, ident.length());
      ident = sb.toString();
    }
    return String.format("_%s%d%s_%s", prefix, varcount++, randomString(RAND_SIZE), ident);
  }

  // should only be called on a SimpleDeclarator node
  public void desugarMemberVarDeclaration(Node n, PresenceCondition presenceCondition,
                                             PresenceCondition lastPresenceCondition,
                                             OutputStreamWriter writer, String SUEIdent)
  throws IOException
  {

    // hoist conditionals around declarations into mv and collect each
    // configuration's identifier in ident
    StringMultiverse mv = new StringMultiverse("", presenceCondition); // create a new multiverse (condition-aware symbol table)
    StringMultiverse ident = new StringMultiverse("", presenceCondition); // create a new multiverse
    Pair<StringMultiverse, StringMultiverse> result = hoistDeclaration(n, mv, ident); // create a mapping (pair) of multiverses set equal to hoistDeclaration(the passed-in node, and the two multiverse)
    StringMultiverse result_decl = result.getKey(); // result_decl is a multiverse set equal to the hoistDeclaration
    StringMultiverse result_ident = result.getValue();

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
      StructT type = new StructT(SUEIdent + " member"); // Tags struct member variables as type "struct <struct type identifier> member"
      symtab.addRenaming(elem_ident, renamed_ident, type, pc);
      String elem_decl = it_decl.next().getKey().toString();
      // TODO: should probably have a nicer way to replace the name
      //writer.write(elem_decl.toString().replace(" " +  elem_ident + " ", " " + renamed_ident + " /* renamed from " + elem_ident + " */ "));
    }
    mv.destruct();
    ident.destruct();

    System.err.println(symtab.originalToNew);
  }

  // fills an arraylist with basic type nodes
  public void findSimpleMemberVars(Node n, ArrayList<Node> basicTypeNodes) {
    if (n == null)
     return;

    if (n.getName().toString().equals("SimpleDeclarator")) {
      basicTypeNodes.add(n);
      return;
    }

    // TODO: check an example of a struct inside of a struct to see if this is a node that will be in there
    if (n.getName().toString().equals("SUETypeSpecifier"))
     return;

   for (Object i : n) {
    if (i instanceof String) {
    }
    else if (i instanceof PresenceCondition) {
    }
    else
       findSimpleMemberVars((Node)i, basicTypeNodes);
   }
  }

 public void desugarSUEDeclaration(Node n, PresenceCondition presenceCondition, PresenceCondition lastPresenceCondition, OutputStreamWriter writer)
 throws IOException {
   ArrayList<Node> basicTypeNodes = new ArrayList<Node>();

   // TODO: be able to handle multiple SUE definitions at once
   int SUE; // 0 for struct, 1 for Union, 2 for Enum
   String SUEIdent = "";
   Node SUENode = n;

   for (int i = 0; i < n.size(); i++) {
     if (n.getNode(i).getName().toString().equals("StructSpecifier")) {
       SUENode = n.getNode(i);
       SUE = 0;
     }
     else {
       // TODO - union and enum
     }
   }


   for (int i = 0; i < SUENode.size(); i++) {
      // sets SUEIdent to the name of the struct
      if (SUENode.getNode(i).getName().toString().equals("IdentifierOrTypedefName")) {
        SUEIdent = SUENode.getNode(i).getNode(0).toString();
      }

      if (SUENode.getNode(i).getName().toString().equals("StructDeclarationList")) {
        // member variables in here
        // TODO: add these to symboltable

        findSimpleMemberVars(SUENode.getNode(i), basicTypeNodes);

        // we call this function on any nodes we find that are simpleDeclarators (temp is the node)
        for (Node o : basicTypeNodes)
           desugarMemberVarDeclaration(o, presenceCondition, lastPresenceCondition, writer, SUEIdent);
        // we need to recursively call this function on any SUEs we find.
        // we don't want to call the above function on any simpledeclarators that are inside of SUEs.
      }
   }

   // hoist conditionals around declarations into mv and collect each
   // configuration's identifier in ident
   StringMultiverse mv = new StringMultiverse("", presenceCondition); // create a new multiverse (condition-aware symbol table)
   StringMultiverse ident = new StringMultiverse("", presenceCondition); // create a new multiverse
   Pair<StringMultiverse, StringMultiverse> result = hoistDeclaration(n, mv, ident); // create a mapping (pair) of multiverses set equal to hoistDeclaration(the passed-in node, and the two multiverse)
   StringMultiverse result_decl = result.getKey(); // result_decl is a multiverse set equal to the hoistDeclaration
   StringMultiverse result_ident = result.getValue();

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
     //String renamed_ident = mangleRenaming(VARPREFIX, elem_ident);
     String renamed_ident = mangleRenaming(VARPREFIX, SUEIdent);

     // NOTE: the tag is a string that follows the actual type in the symboltable
     StructT type = new StructT("typename", (List)basicTypeNodes);

     symtab.addRenaming(elem_ident, renamed_ident, type, pc);
     String elem_decl = it_decl.next().getKey().toString();

     // TODO: should probably have a nicer way to replace the name
     writer.write(elem_decl.toString().replace(" " +  elem_ident + " ", " " + renamed_ident + " /* renamed from " + elem_ident + " */ "));
   }
   mv.destruct();
   ident.destruct();

   System.err.println(symtab.originalToNew);
 }

  // returns the type of elem_ident from elem_decl as a string.
  // this is necessary for variables of a custom type.
  public String lexType(String elem_decl, String elem_ident) {
    StringBuilder sb = new StringBuilder();
    sb.insert(0, " ");
    sb.append(elem_decl);

    // removes the semicolon from the stringbuilder
    int semicolon_pos = 0;
    semicolon_pos = sb.indexOf(";");
    if (semicolon_pos != 0)
      sb = sb.deleteCharAt(semicolon_pos);

    int ident_index = sb.indexOf(elem_ident);
    if (ident_index == -1) {
      System.err.println("ERROR: " + elem_ident + " is missing from declaration: " + elem_decl);
      System.exit(1);
    }

    // deletes the character before ident_index (a space)
    // and the rest of the string (the identifier)
    sb = sb.delete(ident_index-1, sb.length());

    int index_of_type = sb.indexOf(" struct ");
    // TODO: (maybe) also check for struct pointers separately from this - remember that a struct pointer could false trigger this to be true (struct *myFirstStruct)
    if (index_of_type != -1)
      sb = sb.delete(index_of_type, index_of_type + 8);
    else
      sb = sb.delete(0, 1);

    return sb.toString();

    // TODO: return the proper type for all identifiers
  }

  // returns true if the type was defined by the user. false o/w
  public boolean isCustomType(String typeName) {
    if (typeName.equals("int") || typeName.equals("float") ) // TODO: add the rest of the basic types
      return false;
    else return true;
  }

  public void desugarConditionalsDeclaration(Node n, PresenceCondition presenceCondition,
                                             PresenceCondition lastPresenceCondition,
                                             OutputStreamWriter writer)
    throws IOException {

    /// TODO: determine if getNode(0) is always the SUETypeSpecifier for SUEs (check strange config options)
    for (int i = 0; i < n.size(); i++)
      if (n.getNode(i).getName().equals("SUETypeSpecifier")) {
        desugarSUEDeclaration(n.getNode(i), presenceCondition, lastPresenceCondition, writer);
        return;
      }

    // TODO: need to merge extern declarations.  perhaps we can just take the largest size extern and do truncation?

    // hoist conditionals around declarations into mv and collect each
    // configuration's identifier in ident
    StringMultiverse mv = new StringMultiverse("", presenceCondition);
    StringMultiverse ident = new StringMultiverse("", presenceCondition);
    Pair<StringMultiverse, StringMultiverse> result = hoistDeclaration(n, mv, ident);
    StringMultiverse result_decl = result.getKey();
    StringMultiverse result_ident = result.getValue();

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

      String elem_decl = it_decl.next().getKey().toString();

      // Need a check to determine if the type is a custom typename (SUE or typedef)
      String typename_original = lexType(elem_decl.toString(), elem_ident);
      boolean CUSTOM_TYPE = false;
      if (isCustomType(typename_original)) // TODO: add suport for other custom types
        CUSTOM_TYPE = true;

      String typename_renamed = "";

      Type type;

      if (CUSTOM_TYPE) {
        TypedStringMultiverse renaming = symtab.getRenaming(typename_original);
        Iterator<Pair<Pair<StringBuilder, Type>, PresenceCondition>> it_renaming = renaming.iterator();
        while (it_renaming.hasNext()) {
          Pair<Pair<StringBuilder, Type>, PresenceCondition> next_renaming = it_renaming.next();
          Pair<StringBuilder, Type> inner_pair = next_renaming.getKey();
          typename_renamed = inner_pair.getKey().toString();
        }
        type = new StructT(typename_renamed);
      }
      else {
        type = new IntegerT(NumberT.Kind.INT); // TODO: handle types better
      }

      symtab.addRenaming(elem_ident, renamed_ident, type, pc);
      // TODO: should probably have a nicer way to replace the name


      String decl_string = elem_decl.toString().replace(" " +  elem_ident + " ", " " + renamed_ident + " /* renamed from " + elem_ident + " */ ");
      if (CUSTOM_TYPE) {
        // replaces the struct name
        String typed_decl_string = decl_string.replace(" " +  typename_original + " ", " " + typename_renamed + " /* renamed from " + typename_original + " */ ");
        writer.write(typed_decl_string);
      }
      else
        writer.write(decl_string);
    }
    mv.destruct();
    ident.destruct();

    System.err.println(symtab.originalToNew);
  }

  public void desugarConditionalsStatement(Node n, PresenceCondition presenceCondition,
                                           PresenceCondition lastPresenceCondition,
                                           OutputStreamWriter writer)
    throws IOException {

    StringMultiverse mv = new StringMultiverse("", presenceCondition);
    StringMultiverse result = hoistStatement(n, mv);
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
  public StringMultiverse hoistNode(Node n, StringMultiverse mv)
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
        List<StringMultiverse> newmvs = new LinkedList<StringMultiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            StringMultiverse newmv = hoistNode((Node) bo, new StringMultiverse("", branchCondition));
            newmvs.add(new StringMultiverse(mv, newmv));
            newmv.destruct();
          }
        }
        StringMultiverse combinedmv = new StringMultiverse(newmvs);
        for (StringMultiverse elem : newmvs) {
          elem.destruct();
        }
        return combinedmv;

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        StringMultiverse result = new StringMultiverse(mv);
        for (Object o : n) {
          StringMultiverse newResult = hoistNode((Node) o, result);
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

  // Calls StringMultiverse.toString(), then lexes the actual string out, and removes the PC
  public String getIdent(StringMultiverse ident)
  {
    // TODO: write the actual method
    System.err.println("WRITE getIdent() method");
    return "PLACEHOLDER_STRUCT_NAME";

  }

  /**
   * Caller destructs the multiverse that it passes.
   */
  public Pair<StringMultiverse, StringMultiverse> hoistDeclaration(Node n, StringMultiverse mv, StringMultiverse ident)
    throws IOException {

    String renamedIdent = "";
    // TODO: change mv to be a list of tokens instead of a string, StringListMultiverse

    if (n instanceof GNode
        && (((GNode) n).hasName("SimpleDeclarator"))) {
      String identstr = ((Syntax) n.get(0)).toLanguage().toString();
      if (! ident.allEquals("")) {
        // this happens when using custom types (structs, etc)

        // TODO: delete this - no longer necessary - I think
        renamedIdent = symtab.getRenaming(getIdent(ident)).toString();

        ident.addToAll(" " + identstr);

        // need to get the presence condition from this StringMultiverse
        for (Pair<StringBuilder, PresenceCondition> elem : ident.contents) {

          ident = new StringMultiverse("", elem.getValue());
        }

        return hoistDeclaration(n, mv, ident);
      }
      else
        ident.addToAll(identstr);
    }

    // renames struct type identifiers
    if (n instanceof GNode
         && ((GNode) n).hasName("IdentifierOrTypedefName")) {
       String identstr = ((Syntax) n.get(0)).toLanguage().toString();
       if (! ident.allEquals("")) {
         // TODO: determine if this is reachable (compound types...?) if so, may need to call recursively or something
       }
       ident.addToAll(identstr);
     }

    if (n.isToken()) {
      // when we have a single token, append it's string to all lifted
      // strings
      mv.addToAll(n.getTokenText());
      mv.addToAll(" ");
      return new Pair<StringMultiverse, StringMultiverse>(mv, ident);
    } else if (n instanceof Node) {
      // when we have a static conditional, recursively add strings to
      // the entire multiverse by performing a cartesian product with
      // the input multiverse
      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
        List<StringMultiverse> newmvs = new LinkedList<StringMultiverse>();
        List<StringMultiverse> newidents = new LinkedList<StringMultiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            Pair<StringMultiverse, StringMultiverse> retval
              = hoistDeclaration((Node) bo, new StringMultiverse("", branchCondition), new StringMultiverse("", branchCondition));
            StringMultiverse newmv = retval.getKey();
            StringMultiverse newident = retval.getValue();
            newmvs.add(new StringMultiverse(mv, newmv));
            newmv.destruct();
            newidents.add(new StringMultiverse(ident, newident));
            newident.destruct();
          }
        }
        StringMultiverse combinedmv = new StringMultiverse(newmvs);
        for (StringMultiverse elem : newmvs) {
          elem.destruct();
        }
        return new Pair<StringMultiverse, StringMultiverse>(combinedmv, ident);

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        Pair<StringMultiverse, StringMultiverse> result = new Pair<StringMultiverse, StringMultiverse>(new StringMultiverse(mv), ident);
        for (Object o : n) {
          Pair<StringMultiverse, StringMultiverse> newResult = hoistDeclaration((Node) o, result.getKey(), result.getValue());
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
  public StringMultiverse hoistStatement(Node n, StringMultiverse mv)
    throws IOException {

    // replace identifiers with its renamings
    if (n instanceof GNode
        && (((GNode) n).hasName("PrimaryIdentifier") || (((GNode)n).hasName("IdentifierOrTypedefName")))) {

      String identstr = ((Syntax) n.get(0)).toLanguage().toString();

      if (! symtab.hasRenaming(identstr)) {
        System.err.println(symtab.originalToNew);
        System.err.println("ERROR: there is a use of an undefined variable: " + identstr);
        System.exit(1);
      }
      StringMultiverse renaming = new StringMultiverse(symtab.getRenaming(identstr));
      StringMultiverse newmv = new StringMultiverse(mv, renaming);
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
        List<StringMultiverse> newmvs = new LinkedList<StringMultiverse>();
        PresenceCondition branchCondition = null;
        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;
          } else if (bo instanceof Node) {
            StringMultiverse newmv = hoistStatement((Node) bo, new StringMultiverse("", branchCondition));
            newmvs.add(new StringMultiverse(mv, newmv));
            newmv.destruct();
          }
        }
        StringMultiverse combinedmv = new StringMultiverse(newmvs);
        for (StringMultiverse elem : newmvs) {
          elem.destruct();
        }
        return combinedmv;

      } else {
        // when we have a sequence of nodes, add each sequence to the
        // multiverse, using the returned multiverse, since there may
        // have been nested static conditionals.
        StringMultiverse result = new StringMultiverse(mv);
        for (Object o : n) {
          StringMultiverse newResult = hoistStatement((Node) o, result);
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

  public abstract class Multiverse<T> implements Iterable<Pair<T, PresenceCondition>> {
    List<Pair<T, PresenceCondition>> contents;

    private Multiverse() {
    }

    /**
     * Decrement the references of all presence conditions and remove
     * the string builders.  Be sure to do this once you no longer
     * need the multiverse, e.g., after constructing a new multiverse
     * using this one.  The multiverse will no longer be useable after
     * calling this function.
     */
    public void destruct() {
      for (Pair<T, PresenceCondition> elem : contents) {
        // T sb = elem.getKey();
        PresenceCondition pc = elem.getValue();
        pc.delRef();
      }
      contents.clear();
      contents = null;
    }

    public boolean allEquals(String str) {
      boolean flag = true;
      for (Pair<T, PresenceCondition> elem : contents) {
        T sb = elem.getKey();
        flag = flag && sb.toString().equals(str);
      }
      return flag;
    }

    /**
     * Get an element of the list.  Warning, the backing storage is a
     * linked list, so this may only be efficient for get(0).
     */
    public Pair<T, PresenceCondition> get(int index) {
      return contents.get(0);
    }

    public int size() {
      return contents.size();
    }

    public Iterator<Pair<T, PresenceCondition>> iterator() {
      return contents.iterator();
    }
  }

  public class StringMultiverse extends Multiverse<StringBuilder> {
    /**
     * Construct a new multiverse
     */
    public StringMultiverse(String initstring, PresenceCondition initcond) {
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
    public StringMultiverse(StringMultiverse a, StringMultiverse b) {
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
    public StringMultiverse(List<StringMultiverse> mvs) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (StringMultiverse mv : mvs) {
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
    public StringMultiverse(StringMultiverse mv) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (Pair<StringBuilder, PresenceCondition> elem : mv.contents) {
        StringBuilder sb = new StringBuilder(elem.getKey());
        PresenceCondition pc = elem.getValue();
        elem.getValue().addRef();
        contents.add(new Pair<StringBuilder, PresenceCondition>(sb, pc));
      }
    }

    /**
     * The copy constructor.
     */
    public StringMultiverse(TypedStringMultiverse mv) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      for (Pair<Pair<StringBuilder, Type>, PresenceCondition> elem : mv.contents) {
        Pair<StringBuilder, Type> inner_elem = elem.getKey();
        StringBuilder sb = new StringBuilder(inner_elem.getKey());
        PresenceCondition pc = elem.getValue();
        elem.getValue().addRef();
        contents.add(new Pair<StringBuilder, PresenceCondition>(sb, pc));
      }
    }

    public void addToAll(String str) {
      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        StringBuilder sb = elem.getKey();
        sb.append(str);
      }
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

  public class TypedStringMultiverse extends Multiverse<Pair<StringBuilder, Type>> {
    /**
     * Construct a new multiverse
     */
    public TypedStringMultiverse(String initstring, Type type, PresenceCondition initcond) {
      contents = new LinkedList<Pair<Pair<StringBuilder, Type>, PresenceCondition>>();
      StringBuilder sb = new StringBuilder();
      sb.append(initstring);
      Pair<StringBuilder, Type> typedstring = new Pair<StringBuilder, Type>(sb, type);
      Pair<Pair<StringBuilder, Type>, PresenceCondition> elem = new Pair<Pair<StringBuilder, Type>, PresenceCondition>(typedstring, initcond);
      initcond.addRef();
      contents.add(elem);
    }

    /**
     * Construct a new multiverse by combining a list of multiverses.
     * It is up to the caller to destruct the multiverses in the list.
     */
    public TypedStringMultiverse(List<TypedStringMultiverse> mvs) {
      contents = new LinkedList<Pair<Pair<StringBuilder, Type>, PresenceCondition>>();
      for (TypedStringMultiverse mv : mvs) {
        for (Pair<Pair<StringBuilder, Type>, PresenceCondition> elem : mv.contents) {
          Pair<StringBuilder, Type> subelem = elem.getKey();
          StringBuilder sb = new StringBuilder(subelem.getKey());
          Type type = subelem.getValue();
          PresenceCondition pc = elem.getValue();
          elem.getValue().addRef();
          Pair<StringBuilder, Type> typedstring = new Pair<StringBuilder, Type>(sb, type);
          contents.add(new Pair<Pair<StringBuilder, Type>, PresenceCondition>(typedstring, pc));
        }
      }
    }

    /**
     * The copy constructor.
     */
    public TypedStringMultiverse(TypedStringMultiverse mv) {
      contents = new LinkedList<Pair<Pair<StringBuilder, Type>, PresenceCondition>>();
      for (Pair<Pair<StringBuilder, Type>, PresenceCondition> elem : mv.contents) {
        Pair<StringBuilder, Type> subelem = elem.getKey();
        StringBuilder sb = new StringBuilder(subelem.getKey());
        Type type = subelem.getValue();
        PresenceCondition pc = elem.getValue();
        elem.getValue().addRef();
        Pair<StringBuilder, Type> typedstring = new Pair<StringBuilder, Type>(sb, type);
        contents.add(new Pair<Pair<StringBuilder, Type>, PresenceCondition>(typedstring, pc));
      }
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();

      for (Pair<Pair<StringBuilder, Type>, PresenceCondition> elem : contents) {
        sb.append(elem.toString());
        sb.append("\n");
      }

      return sb.toString();
    }
  }

  public class StringListMultiverse extends Multiverse<List<String>> {
    /**
     * Construct a new multiverse
     */
    public StringListMultiverse(String initstring, PresenceCondition initcond) {
      contents = new LinkedList<Pair<List<String>, PresenceCondition>>();
      List<String> sb = new LinkedList<String>();
      sb.add(initstring);
      Pair<List<String>, PresenceCondition> elem = new Pair<List<String>, PresenceCondition>(sb, initcond);
      initcond.addRef();
      contents.add(elem);
    }

    /**
     * Construct a new multiverse from two multiverses using the
     * cartesian product.
     */
    public StringListMultiverse(StringListMultiverse a, StringListMultiverse b) {
      contents = new LinkedList<Pair<List<String>, PresenceCondition>>();
      for (Pair<List<String>, PresenceCondition> elem1 : a.contents) {
        for (Pair<List<String>, PresenceCondition> elem2 : b.contents) {
          List<String> sb = new LinkedList<String>();
          sb.addAll(elem1.getKey());
          sb.addAll(elem2.getKey());
          PresenceCondition pc = elem1.getValue().and(elem2.getValue());
          if (! pc.isFalse()) { // trim infeasible combinations
            contents.add(new Pair<List<String>, PresenceCondition>(sb, pc));
          }
        }
      }
    }

    /**
     * Construct a new multiverse by combining a list of multiverses.
     * It is up to the caller to destruct the multiverses in the list.
     */
    public StringListMultiverse(List<StringListMultiverse> mvs) {
      contents = new LinkedList<Pair<List<String>, PresenceCondition>>();
      for (StringListMultiverse mv : mvs) {
        for (Pair<List<String>, PresenceCondition> elem : mv.contents) {
          List<String> sb = new LinkedList<String>();
          sb.addAll(elem.getKey());
          PresenceCondition pc = elem.getValue();
          elem.getValue().addRef();
          contents.add(new Pair<List<String>, PresenceCondition>(sb, pc));
        }
      }
    }

    /**
     * The copy constructor.
     */
    public StringListMultiverse(StringListMultiverse mv) {
      contents = new LinkedList<Pair<List<String>, PresenceCondition>>();
      for (Pair<List<String>, PresenceCondition> elem : mv.contents) {
        List<String> sb = new LinkedList<String>();
        sb.addAll(elem.getKey());
        PresenceCondition pc = elem.getValue();
        elem.getValue().addRef();
        contents.add(new Pair<List<String>, PresenceCondition>(sb, pc));
      }
    }

    public void addToAll(String str) {
      for (Pair<List<String>, PresenceCondition> elem : contents) {
        List<String> sb = elem.getKey();
        sb.add(str);
      }
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();

      for (Pair<List<String>, PresenceCondition> elem : contents) {
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
    Map<String, TypedStringMultiverse> originalToNew;

    public SymbolTable(SymbolTable parent) {
      this.parent = null;
      this.newToOriginal = new HashMap<String, Pair<String, PresenceCondition>>();
      this.originalToNew = new HashMap<String, TypedStringMultiverse>();
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

    public void addRenaming(String var, String renamed, Type type, PresenceCondition cond) {
      assert null == newToOriginal.put(renamed, new Pair<String, PresenceCondition>(var, cond));
      cond.addRef();
      TypedStringMultiverse mv = new TypedStringMultiverse(renamed, type, cond);
      cond.addRef();
      if (! originalToNew.containsKey(var)) {
        originalToNew.put(var, mv);
      } else {
        TypedStringMultiverse oldmv = originalToNew.get(var);
        List<TypedStringMultiverse> list = new LinkedList<TypedStringMultiverse>();
        list.add(oldmv);
        list.add(mv);
        TypedStringMultiverse combinedmv = new TypedStringMultiverse(list);
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
    public TypedStringMultiverse getRenaming(String var) {
      if (! originalToNew.containsKey(var)) {
        return null;
      } else {
        return new TypedStringMultiverse(originalToNew.get(var));
      }
    }
  }
}
