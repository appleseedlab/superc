/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2006, 2007 IBM Corp.
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
import xtc.tree.Node;
import xtc.tree.Visitor;

/**
 * A visitor that simplifies Java ASTs. Turns BasicCastExpression into
 * CastExpression, and turns ConstructorDeclaration into MethodDeclaration.
 * Subsumes Dimensions into the close-by Type wherever possible. The resulting
 * AST uses only GNode names that occur in the original grammar.
 * 
 * @author Martin Hirzel
 */
public class JavaAstSimplifier extends Visitor {
  private static GNode concatDims(final GNode d1, final GNode d2) {
    if (null == d1)
      return d2;
    if (null == d2)
      return d1;
    assert false; //TD 04 implement when it gets exercised
    return null;
  }

  /** Copy location from nOld to nNew, then return nNew. */
  public static GNode copyLoc(final GNode nOld, final GNode nNew) {
    nNew.setLocation(nOld);
    return nNew;
  }
  
  /** Catch-all visit method, replaces subtrees in-place by dispatched version. */
  public Node visit(final Node n) {
    for (int i=0; i<n.size(); i++) {
      final Object o = n.get(i);
      if (o instanceof Node)
        n.set(i, dispatch((Node) o));
    }
    return n;
  }

  /** Turn BasicCastExpression into general CastExpression. */
  public final GNode visitBasicCastExpression(final GNode n) {
    final GNode typeName = (GNode) dispatch(n.getGeneric(0));
    final GNode dimensions = (GNode) dispatch(n.getGeneric(1));
    final GNode expression = (GNode) dispatch(n.getGeneric(2));
    final GNode type = copyLoc(n, GNode.create("Type", typeName, dimensions));
    return copyLoc(n, GNode.create("CastExpression", type, expression));
  }
  
  /** Turn ConstructorDeclaration into general MethodDeclaration. */
  public final GNode visitConstructorDeclaration(final GNode n) {
    final GNode modifiers = (GNode) dispatch(n.getNode(0));
    final GNode formals = (GNode) dispatch(n.getNode(3));
    final GNode throwsClause = (GNode) dispatch(n.getNode(4));
    final GNode body = (GNode) dispatch(n.getNode(5));
    final GNode result = copyLoc(n, GNode.create("MethodDeclaration", modifiers,
      null, null, n.getString(2), formals, null, throwsClause, body));
    return result;
  }
  
  /** Move dimensions from parameter declaration into declared type of the parameter. */
  public final GNode visitFormalParameter(final GNode n) {
    final GNode modifiers = (GNode) dispatch(n.getGeneric(0));
    final GNode oldType = (GNode) dispatch(n.getGeneric(1));
    final String name = n.getString(3);
    final GNode dim1 = (GNode) dispatch(n.getGeneric(4));
    final GNode dim2 = oldType.getGeneric(1);
    final GNode newDimensions = concatDims(dim1, dim2);
    final GNode newType = copyLoc(oldType, GNode.create("Type", oldType.get(0), newDimensions));
    return copyLoc(n, GNode.create("FormalParameter", modifiers, newType, null, name, null));
  }
  
  /** Move dimensions from method declaration into the return type. */
  public final GNode visitMethodDeclaration(final GNode n) {
    final GNode modifiers = (GNode) dispatch(n.getGeneric(0));
    final GNode oldResultType = (GNode) dispatch(n.getGeneric(2));
    final String name = n.getString(3);
    final GNode formals = (GNode) dispatch(n.getGeneric(4));
    final GNode dimensions = n.getGeneric(5);
    final GNode throwsClause = (GNode) dispatch(n.getGeneric(6));
    final GNode body = (GNode) dispatch(n.getGeneric(7));
    final GNode newResultType;
    if (null == dimensions) {
      newResultType = oldResultType;
    } else {
      assert oldResultType.hasName("Type");
      final GNode typeName = oldResultType.getGeneric(0);
      final GNode newDimensions = concatDims(n.getGeneric(5), oldResultType.getGeneric(1));
      newResultType = copyLoc(oldResultType, GNode.create("Type", typeName, newDimensions));
    }
    return copyLoc(n, GNode.create("MethodDeclaration", modifiers, null,
        newResultType, name, formals, null, throwsClause, body));
  }

  /** Move unary minus into IntegerLiteral, to simplify checking that the literal is valid in Java. */
  public final GNode visitUnaryExpression(final GNode n) {
    if ("-".equals(n.getString(0)) && n.getGeneric(1).hasName("IntegerLiteral")) {
      final String baseLit = n.getGeneric(1).getString(0);
      if ('-' != baseLit.charAt(0))
        return copyLoc(n, GNode.create("IntegerLiteral", "-" + baseLit));
    }
    n.set(1, dispatch(n.getNode(1)));
    return n;
  }
}
