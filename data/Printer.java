/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004 Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package xtc.tree;

import java.io.PrintWriter;

import java.util.Collection;
import java.util.Iterator;

import xtc.Constants;

import xtc.util.Utilities;

/** 
 * A node pretty printing utility. This class provides a set of
 * convenience methods to simplify the pretty printing of an abstract
 * syntax tree.
 *
 * @author Robert Grimm
 * @version $Revision: 1.2 $
 */
public class Printer extends Utility {

  /** The length of the line separator. */
  public static final int SEPARATOR_LENGTH =
    System.getProperty("line.separator").length();

  /** The print writer to print to. */
  protected PrintWriter out;

  /** The current indentation level. */
  protected int indent = 0;

  /**
   * The number of characters printed by the most recently invoked
   * method.
   */
  protected int printed = 0;

  // ========================================================================

  /**
   * Create a new printer with the specified print writer.
   *
   * @param out The print writer to output to.
   */
  public Printer(PrintWriter out) {
    this.out = out;
  }

  // ========================================================================

  /**
   * Increase the current indentation level.
   *
   * @return This printer.
   */
  public Printer incr() {
    indent += Constants.INDENTATION;
    return this;
  }

  /**
   * Decrease the current indentation level.
   *
   * @return This printer.
   */
  public Printer decr() {
    indent -= Constants.INDENTATION;
    return this;
  }

  /**
   * Indent.
   *
   * @return This printer.
   */
  public Printer indent() {
    for (int i=0; i<indent; i++) {
      out.print(' ');
    }

    printed = indent;
    return this;
  }

  /**
   * Indent one tab stop less than the current indentation level.
   *
   * @return This printer.
   */
  public Printer indentLess() {
    int w = indent - Constants.INDENTATION;
    if (0 > w) {
      w = 0;
    }

    for (int i=0; i<w; i++) {
      out.print(' ');
    }

    printed = w;
    return this;
  }

  // ========================================================================

  /**
   * Print the specified character.
   *
   * @param c The character to print.
   * @return This printer.
   */
  public Printer p(char c) {
    out.print(c);
    printed = 1;
    return this;
  }

  /**
   * Print the specified integer.
   *
   * @param i The integer to print.
   * @return This printer.
   */
  public Printer p(int i) {
    return p(Integer.toString(i));
  }

  /**
   * Print the specified string.
   *
   * @param s The string to print.
   * @return This printer.
   */
  public Printer p(String s) {
    out.print(s);
    printed = s.length();
    return this;
  }

  /**
   * Print the specified character followed by a newline.
   *
   * @param c The character to print.
   * @return This printer.
   */
  public Printer pln(char c) {
    out.println(c);
    printed = 1 + SEPARATOR_LENGTH;
    return this;
  }

  /**
   * Print the specified integer followed by a newline.
   *
   * @param i The integer to print.
   * @return This printer.
   */
  public Printer pln(int i) {
    return pln(Integer.toString(i));
  }

  /**
   * Print the specified string followed by a newline.
   *
   * @param s The string to print.
   * @return This printer.
   */
  public Printer pln(String s) {
    out.println(s);
    printed = s.length() + SEPARATOR_LENGTH;
    return this;
  }

  /**
   * Print a newline.
   *
   * @return This printer.
   */
  public Printer pln() {
    out.println();
    printed = SEPARATOR_LENGTH;
    return this;
  }
  
  // ========================================================================

  /**
   * Print whitespace to align the output.  This method prints
   * whitespace to cover the difference between the specified number
   * of printed characters and the specified alignment.  If the number
   * of characters already printed is equal or larger than the number
   * of characters to align the output at, a single space character is
   * printed.
   *
   * @param printed The number of characters already printed.
   * @param alignment The number of characters to align at.
   */
  public Printer align(int printed, int alignment) {
    int toPrint = alignment - printed;
    if (0 >= toPrint) toPrint = 1;
    for (int i=0; i<toPrint; i++) {
      out.write(' ');
    }
    printed = toPrint;
    return this;
  }

  /**
   * Print whitespace to align the output.  This method prints
   * whitespace to cover the difference between the number of
   * characters printed by the last invocation to any of this
   * printer's methods (besides {@link #incr()} and {@link #decr()})
   * and the specified alignment. If the number of characters already
   * printed is equal or larger than the number of characters to align
   * the output at, a single space character is printed.
   *
   * @param alignment The number of characters to align at.
   */
  public Printer align(int alignment) {
    return align(printed, alignment);
  }

  // ========================================================================

  /**
   * Print the specified character with the specified escape sequences.
   *
   * @see Utilities
   *
   * @param c The character to print.
   * @param flags The escape flags.
   * @return This printer.
   */
  public Printer escape(char c, int flags) {
    return p(Utilities.escape(c, flags));
  }

  /**
   * Print the specified string with the specified escape sequences.
   *
   * @see Utilities
   *
   * @param s The string to print.
   * @param flags The escape flags.
   * @return This printer.
   */
  public Printer escape(String s, int flags) {
    return p(Utilities.escape(s, flags));
  }

  // ========================================================================

  /**
   * Print an indented separation comment.
   *
   * @return This printer.
   */
  public Printer sep() {
    indent().p("// ");

    int n = 80 - indent - 3 - 3;
    for (int i=0; i<n; i++) {
      out.print('=');
    }

    out.println();
    printed = 77 + SEPARATOR_LENGTH;
    return this;
  }

  // ========================================================================

  /**
   * Print the specified node. If the specified node is
   * <code>null</code>, nothing is printed.
   *
   * @param node The node to print.
   * @return This printer.
   */
  public Printer p(Node node) {
    if (null != node) node.accept(visitor());
    return this;
  }

  /**
   * Print the specified collection of nodes. Nodes are printed in the
   * order of the collection's iterator. If the specified collection
   * is <code>null</code>, nothing is printed.
   *
   * @param coll The collection of nodes to print.
   * @return This printer.
   */
  public Printer p(Collection coll) {
    if (null != coll) {
      Iterator iter = coll.iterator();

      while (iter.hasNext()) {
        p((Node)iter.next());
      }
    }
    return this;
  }

  /**
   * Print the specified collection of nodes. Nodes are printed in the
   * order of the collection's iterator. If the specified collection
   * is <code>null</code> or empty, nothing is printed.
   *
   * @param coll The collection of nodes to print.
   * @param before The string to print before the nodes.
   * @param sep The string to print between nodes.
   */
  public Printer p(Collection coll, String before, String sep) {
    if (null != coll) {
      boolean  first = true;
      Iterator iter  = coll.iterator();

      while (iter.hasNext()) {
        if (first) {
          p(before);
          first = false;
        } else {
          p(sep);
        }
        p((Node)iter.next());
      }
    }
    return this;
  }

  // ========================================================================

  /**
   * Print the original location for the specified node. Note that
   * this method prints nothing.
   *
   * @param node The node.
   * @return This printer.
   */
  public Printer loc(Node node) {
    return this;
  }

}
