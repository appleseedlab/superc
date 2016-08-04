/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 Robert Grimm
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
package xtc.lang;

import xtc.tree.GNode;
import xtc.tree.Printer;
import xtc.tree.Visitor;

import xtc.util.Utilities;

/**
 * A pretty printer for the simply typed lambda calculus.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public class TypedLambdaPrinter extends Visitor {

  /** The printer. */
  protected final Printer printer;

  /**
   * Create a new printer for the simply typed lambda calculus.
   *
   * @param printer The printer.
   */
  public TypedLambdaPrinter(Printer printer) {
    this.printer = printer;
    printer.register(this);
  }

  /** Visit the specified application node. */
  public void visitApplication(GNode n) {
    boolean paren = n.getGeneric(0).hasName("Abstraction");
    if (paren) printer.p('(');
    printer.p(n.getNode(0));
    if (paren) printer.p(')');

    printer.p(' ');

    paren = n.getGeneric(1).hasName("Application");
    if (paren) printer.p('(');
    printer.p(n.getNode(1));
    if (paren) printer.p(')');
  }

  /** Visit the specified abstraction node. */
  public void visitAbstraction(GNode n) {
    printer.p("\\ ").p(n.getNode(0)).p(" : ").p(n.getNode(1)).p(" . ").
      p(n.getNode(2));
  }

  /** Visit the specified identifier node. */
  public void visitIdentifier(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified integer constant node. */
  public void visitIntegerConstant(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified string constant node. */
  public void visitStringConstant(GNode n) {
    String s = n.getString(0);
    s        = s.substring(1, s.length()-1);
    printer.p('"').escape(s, Utilities.C_ESCAPES).p('"');
  }

  /** Visit the specified function type node. */
  public void visitFunctionType(GNode n) {
    boolean paren = n.getGeneric(0).hasName("FunctionType");
    if (paren) printer.p('(');
    printer.p(n.getNode(0));
    if (paren) printer.p(')');

    printer.p(" -> ");

    printer.p(n.getNode(1));
  }

  /** Visit the specified integer type node. */
  public void visitIntegerType(GNode n) {
    printer.p("int");
  }

  /** Visit the specified string type node. */
  public void visitStringType(GNode n) {
    printer.p("string");
  }

}