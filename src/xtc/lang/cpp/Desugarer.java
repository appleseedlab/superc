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

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.lang.cpp.CContext.SymbolTable.STField;

import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.Constants;

class Desugarer {
  /** The instance of this class */
  private static Desugarer ref;

  /** A reference to the presence condition manager */
  private PresenceConditionManager presenceConditionManager;

  /** Get the instance of this class */
  public static Desugarer getInstance(PresenceConditionManager presenceConditionManager) {
    if (null == ref) {
      ref = new Desugarer(presenceConditionManager);
    }
    return ref;
  }

  protected Desugarer(PresenceConditionManager presenceConditionManager) {
    this.presenceConditionManager = presenceConditionManager;
  }

  /**
   * Print an AST (or a subtree of it) in C source form.
   *
   * @param n An AST or a subtree.
   * @param presenceCondition The current nested presence condition.
   * @param writer The writer.
   * @throws IOException Because it writes to output. 
   */
  public void desugarConditionals(Node n, PresenceCondition presenceCondition,
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
              desugarConditionals((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
            } else if (((Node) bo).getName().equals("FunctionDefinition")) {
              writer.write("\n");
              desugarConditionalsFunctionDefinition((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
              writer.write("\n");
            } else if (((Node) bo).getName().equals("Declaration")) {
              writer.write("\n");
              desugarConditionalsDeclaration((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
              writer.write("\n");
            } else {
              desugarConditionalsStatement((Node) bo, newPresenceCondition, lastPresenceCondition, writer);
            }
          }
        }

      } else {
        for (Object o : n) {
          desugarConditionals((Node) o, presenceCondition, lastPresenceCondition, writer);
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
    Multiverse protomv = hoistNode(n.getNode(0), new Multiverse("", presenceCondition));
    
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

    

    if (protomv.size() == 1) {
      writer.write(protomv.get(0).getKey().toString());
      writer.write("{\n");
      writer.write("if (");
      protomv.get(0).getValue().print(writer);
      writer.write(") {\n");
      for (int i = 1; i < n.size(); i++) {
        desugarConditionals(n.getNode(i), presenceCondition, lastPresenceCondition, writer);
      }
      writer.write("\n}\n");
      writer.write("}\n");
    } else {
      System.err.println("TODO support multiple function prototypes");
      writer.write(protomv.toString());
    }

    protomv.destruct();
    
    // hoist the function prototype to have a complete one

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

  public void desugarConditionalsDeclaration(Node n, PresenceCondition presenceCondition,
                                             PresenceCondition lastPresenceCondition,
                                             OutputStreamWriter writer)
    throws IOException {

    Multiverse mv = new Multiverse("", presenceCondition);
    Multiverse result = hoistNode(n, mv);
    writer.write(result.toString());
    mv.destruct();

    // process results by adding to symbol table, renaming, and
    // printing
  }

  public void desugarConditionalsStatement(Node n, PresenceCondition presenceCondition,
                                           PresenceCondition lastPresenceCondition,
                                           OutputStreamWriter writer)
    throws IOException {

    Multiverse mv = new Multiverse("", presenceCondition);
    Multiverse result = hoistNode(n, mv);
    writer.write(result.toString());
    mv.destruct();

    // process results by looking up in the symbol table and adjusting
    // the surrounding conditionals, later do type checking

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

  public class Multiverse {
    List<Pair<StringBuilder, PresenceCondition>> contents;

    /**
     * Construct a new multiverse
     */
    public Multiverse(String initstring, PresenceCondition initcond) {
      contents = new LinkedList<Pair<StringBuilder, PresenceCondition>>();
      StringBuilder sb = new StringBuilder();
      sb.append(initstring);
      Pair<StringBuilder, PresenceCondition> elem = new Pair<StringBuilder, PresenceCondition>(sb, initcond);
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

    public String toString() {
      StringBuilder sb = new StringBuilder();

      for (Pair<StringBuilder, PresenceCondition> elem : contents) {
        sb.append(elem.toString());
        sb.append("\n");
      }

      return sb.toString();
    }
  }

  public class Pair<T, U> {
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
}
