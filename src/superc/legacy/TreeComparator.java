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
package superc;

import java.util.List;
import java.util.LinkedList;
import java.util.Arrays;

import java.io.StringReader;

import superc.core.SemanticValues;

import superc.core.Syntax;
import superc.core.Syntax.Kind;
import superc.core.Syntax.Language;

import superc.cparser.CParseTables;
import superc.cparser.CValues;

import xtc.parser.Result;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;

public class TreeComparator {
  /** A stack to hold the pending nodes of the first AST. */
  private LinkedList<Object> s1;

  /** A stack to hold the pending nodes of the second AST. */
  private LinkedList<Object> s2;

  /** The array of symbols indexed by symbol id. */
  List symbols;

  /** Create a new comparator.  This object is a singleton. */
  private TreeComparator() {
    this.symbols = Arrays.asList(CParseTables.getInstance().yytname);
  }

  /**
   * Compare two ASTs.  This method checks whether the pre-order
   * traversal of both trees is the same.  This is done because
   * SuperC's AST has extra nodes, e.g., Conditional and *List nodes
   * that the Rats! AST doesn't have.  Comparing pre-order makes it
   * easy to skip these nodes.
   *
   * @param o1 The SuperC AST.
   * @param o2 The Rats AST.
   * @return true if their pre-order traversals are equal.
   */
  public boolean traverse(Object o1, Object o2) {
    s1 = new LinkedList<Object>();
    s2 = new LinkedList<Object>();

    s1.push(o1);
    s2.push(o2);

    while (traverse()) {
      if (s1.isEmpty() && s2.isEmpty()) return true;
    }

    return false;
  }

  /**
   * Perform the actual comparison.  This assumes s1 and s2 are stacks
   * containing the top-level node of both trees.
   *
   * @return true if the ASTs' pre-order traversals are equal.
   */
  private boolean traverse() {
    // Skip nulls in Rats! ASTs
    if (! s2.isEmpty() && null == s2.peek()) {
      if (s1.peek() instanceof GNode) {
        GNode g = (GNode) s1.peek();
        if (g.getName().endsWith("List") && g.size() == 0) {
          // Equate empty lists with null
          s1.pop();
        }
      }
      s2.pop();
      return true;
    }

    if (s1.isEmpty() && s2.isEmpty()) return true;

    if (s1.isEmpty() || s2.isEmpty()) {
      System.err.println("sizes differ");
      return false;
    }

    Object o1 = s1.pop();
    Object o2 = s2.pop();

    if (null == o1 && null == o2) return true;

    // Move past SuperC's FunctionProtoype nodes.
    if (o1 instanceof GNode
        && ((GNode)o1).getName().equals("FunctionPrototype")) {
      Node a = (Node) o1;
      GNode g = (GNode) a;
      System.err.println("is function prototype " + a.getName());
      for (int i = g.size() - 1; i >= 0; i--) {
        s1.push(g.get(i));
      }
      s2.push(o2);
      return true;
    }

    // Check for mismatched null.
    if (null == o1 || null == o2) {
      System.err.println("mismatched null");
      System.err.println("a: " + o1 + "\n");
      System.err.println("b: " + o2 + "\n");
      return false;
    }

    if (o1 instanceof String && o2 instanceof Syntax
        || o1 instanceof Syntax && o2 instanceof String) {
      // Equate a SuperC token with a Rats!' string
      return o1.toString().equals(o2.toString());
    } else if (o1 instanceof Syntax.Text && o2 instanceof GNode) {
      // Equate SuperC's tokens with scannerless Rats!'s AST nodes
      Syntax.Text s = (Syntax.Text) o1;
      GNode r = (GNode) o2;
      System.err.println(s.tag() + ":" + s.toString());
      System.err.println(r.getName() + ":" + r.toString());
      return o1.toString().equals(((GNode) o2).get(0).toString());
    }
    
    Node a = (Node) o1;
    Node b = (Node) o2;

    if (a.isToken() && b.isToken()) {
      return a.getTokenText().equals(b.getTokenText());
    }

    // Compare type names.  SuperC has tokens, Rats! has AST nodes.
    if (a instanceof Language && b.size() == 0
        && (a.toString() + "()").equals(b.toString().toLowerCase())) {
      return true;
    }

    if (! (a.isGeneric() && b.isGeneric())) {
      System.err.println("node types differ");
      System.err.println("a: " + a + "\n");
      System.err.println("b: " + b + "\n");
      return false;
    }

    GNode g = (GNode) a;
    GNode h = (GNode) b;

    // Skip Conditional nodes
    if (g.getName().equals("Conditional")) {
      s1.push(g.get(1));
      s2.push(o2);
      return true;
    }

    // Expand SuperC AST's lists, but not ExpressionList, which is a
    // Node in the Rats! grammar.
    if (! g.getName().equals("ExpressionList")
        && CValues
        .getInstance().getValueType(symbols.indexOf(g.getName()))
        == SemanticValues.ValueType.LIST) {
      System.err.println("is list " + a.getName());
      for (int i = g.size() - 1; i >= 0; i--) {
        s1.push(g.get(i));
      }
      s2.push(o2);
      return true;
    }

    // TODO: SuperC should have a unified DeclarationSpecifiers
    // production is possible.
    if (h.getName().equals("DeclarationSpecifiers")) {
      if (g.getName().equals("DeclarationSpecifier")
          || g.getName().equals("TypeSpecifier")
          || g.getName().equals("DeclarationQualifierList")
          || g.getName().equals("TypeQualifierList")) {
      }
    } else if (! g.getName().equals(h.getName())) {
      System.err.println("node names differ");
      System.err.println("a: " + a + "\n");
      System.err.println("b: " + b + "\n");
      return false;
    }

    for (int i = g.size() - 1; i >= 0; i--) {
      s1.push(g.get(i));
    }

    for (int i = h.size() - 1; i >= 0; i--) {
      s2.push(h.get(i));
    }

    return true;
  }

  private static TreeComparator ref = null;

  public static TreeComparator getInstance() {
    if (null == ref) {
      ref = new TreeComparator();
    }

    return ref;
  }

  /**
   * Check whether two xtc ASTs are equivalent.
   *
   * @param o1 The first tree.
   * @param o2 The second tree.
   * @return true if the tress are equivalent.
   */
  public static boolean compare(Object o1, Object o2) {
    if (null == o1 && null == o2) return true;
    if (null == o1 || null == o2) return false;

    if (o1 instanceof String && o2 instanceof Syntax
        || o1 instanceof Syntax && o2 instanceof String) {
      return o1.toString().equals(o2.toString());
    }

    Node a = (Node) o1;
    Node b = (Node) o2;
    if (a.isToken() && b.isToken()) {
      return a.getTokenText().equals(b.getTokenText());
    } else if (a.isGeneric() && b.isGeneric()) {
      if (a.getName().equals(b.getName())) {
        GNode g = (GNode) a;
        GNode h = (GNode) b;

        for (int i = 0; i < Math.max(g.size(), h.size()); i++) {
          if (i >= g.size() || i >= h.size()) {
            System.err.println("sizes differ");
            System.err.println("a: " + g + "\n");
            System.err.println("b: " + h + "\n");
            return false;
          }

          if (!compare(g.get(i), h.get(i))) {
            return false;
          }
        }
        return true;
      } else if (a.getName().equals("Conditional")) {
        return compare(a.get(1), b);
      } else if (b.getName().equals("Conditional")) {
        return compare(a, b.get(1));
      } else {
        System.err.println("node names differ");
        System.err.println("a: " + a + "\n");
        System.err.println("b: " + b + "\n");
        return false;
      }
    } else {
      System.err.println("node types differ");
      System.err.println("a: " + a + "\n");
      System.err.println("b: " + b + "\n");
      return false;
    }
  }
}
