/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004, 2006 Robert Grimm
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

import java.util.Iterator;

import xtc.tree.LineMarker;
import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Pragma;
import xtc.tree.Printer;
import xtc.tree.Visitor;

/**
 * A visitor to collect statistics on a C program.
 *
 * @author Robert Grimm
 * @version $Revision: 1.9 $
 */
public class CCounter extends Visitor {

  /** The counter for top-level declarations. */
  public int countTopLevelDeclaration;

  /** The counter for top-level function definitions. */
  public int countTopLevelFunction;

  /** The counter for nested declarations. */
  public int countNestedDeclaration;

  /** The counter for nested function definitions. */
  public int countNestedFunction;

  /** The counter for local label declarations. */
  public int countLocalLabelDecl;

  /** The counter for named labels. */
  public int countNamedLabel;

  /** The counter for case labels. */
  public int countCaseLabel;

  /** The counter for default labels. */
  public int countDefaultLabel;

  /** The counter for compound statements. */
  public int countCompoundStmt;

  /** The counter for if statements. */
  public int countIfStmt;

  /** The counter for if-else statements. */
  public int countIfElseStmt;

  /** The counter for while statements. */
  public int countWhileStmt;

  /** The counter for do-while statements. */
  public int countDoStmt;

  /** The counter for for statements. */
  public int countForStmt;

  /** The coutner for switch statements. */
  public int countSwitchStmt;

  /** The counter for break statements. */
  public int countBreakStmt;

  /** The counter for continue statements. */
  public int countContinueStmt;

  /** The counter for return statements. */
  public int countReturnStmt;

  /** The counter for goto statements. */
  public int countGotoStmt;

  /** The counter for expression statements. */
  public int countExpressionStmt;

  /** The counter for assembly statements. */
  public int countAssemblyStmt;

  /** The counter for empty statements. */
  public int countEmptyStmt;

  /** The counter for line markers. */
  public int countLineMarker;

  /** The counter for pragmas. */
  public int countPragma;

  /** The flag for top-level constructs. */
  protected boolean isTopLevel;

  /** Create a new C counter. */
  public CCounter() {
    clearCounters();
  }

  /** Clear all counters. */
  public void clearCounters() {
    countTopLevelDeclaration = 0;
    countTopLevelFunction    = 0;
    countNestedDeclaration   = 0;
    countNestedFunction      = 0;
    countLocalLabelDecl      = 0;
    countNamedLabel          = 0;
    countCaseLabel           = 0;
    countDefaultLabel        = 0;
    countCompoundStmt        = 0;
    countIfStmt              = 0;
    countIfElseStmt          = 0;
    countWhileStmt           = 0;
    countDoStmt              = 0;
    countForStmt             = 0;
    countSwitchStmt          = 0;
    countBreakStmt           = 0;
    countContinueStmt        = 0;
    countReturnStmt          = 0;
    countGotoStmt            = 0;
    countExpressionStmt      = 0;
    countAssemblyStmt        = 0;
    countEmptyStmt           = 0;
    countLineMarker          = 0;
    countPragma              = 0;
  }

  /**
   * Print all counters.
   *
   * @param printer The printer.
   */
  public void print(Printer printer) {
    printer.pln().sep().pln();

    printer.indent().p("// Top-level declarations         : ").
      pln(countTopLevelDeclaration);
    printer.indent().p("// Top-level function definitions : ").
      pln(countTopLevelFunction);
    printer.indent().p("// Nested declarations            : ").
      pln(countNestedDeclaration);
    printer.indent().p("// Nested function definitions    : ").
      pln(countNestedFunction);
    printer.indent().p("// Local label declarations       : ").
      pln(countLocalLabelDecl);
    printer.indent().p("// Named labels                   : ").
      pln(countNamedLabel);
    printer.indent().p("// Case labels                    : ").
      pln(countCaseLabel);
    printer.indent().p("// Default labels                 : ").
      pln(countDefaultLabel);
    printer.indent().p("// Compound statements            : ").
      pln(countCompoundStmt);
    printer.indent().p("// If statements                  : ").
      pln(countIfStmt);
    printer.indent().p("// If-else statements             : ").
      pln(countIfElseStmt);
    printer.indent().p("// While statements               : ").
      pln(countWhileStmt);
    printer.indent().p("// Do statements                  : ").
      pln(countDoStmt);
    printer.indent().p("// For statements                 : ").
      pln(countForStmt);
    printer.indent().p("// Switch statements              : ").
      pln(countSwitchStmt);
    printer.indent().p("// Break statements               : ").
      pln(countBreakStmt);
    printer.indent().p("// Continue statements            : ").
      pln(countContinueStmt);
    printer.indent().p("// Return statements              : ").
      pln(countReturnStmt);
    printer.indent().p("// Goto statements                : ").
      pln(countGotoStmt);
    printer.indent().p("// Expression statements          : ").
      pln(countExpressionStmt);
    printer.indent().p("// Assembly statements            : ").
      pln(countAssemblyStmt);
    printer.indent().p("// Empty statements               : ").
      pln(countEmptyStmt);
    printer.indent().p("// Line markers                   : ").
      pln(countLineMarker);
    printer.indent().p("// Pragmas                        : ").
      pln(countPragma);

    printer.pln().sep().pln();
  }

  /** Visit the specified translation unit node. */
  public void visitTranslationUnit(GNode n) {
    Iterator iter = n.iterator();
    while (iter.hasNext()) {
      isTopLevel  = true;
      dispatch((Node)iter.next());
    }
  }

  /** Visit the specified function definition node. */
  public void visitFunctionDefinition(GNode n) {
    if (isTopLevel) {
      countTopLevelFunction++;
    } else {
      countNestedFunction++;
    }
    isTopLevel = false;

    dispatch(n.getNode(3));
    dispatch(n.getNode(4));
  }

  /** Visit the specified declaration list node. */
  public void visitDeclarationList(GNode n) {
    Iterator iter = n.iterator();
    while (iter.hasNext()) {
      dispatch((Node)iter.next());
    }
  }

  /** Visit the specified declaration node. */
  public void visitDeclaration(GNode n) {
    if (isTopLevel) {
      countTopLevelDeclaration++;
    } else {
      countNestedDeclaration++;
    }
    isTopLevel = false;
  }

  /** Visit the specified labeled statement node. */
  public void visitLabeledStatement(GNode n) {
    dispatch(n.getNode(0));
    dispatch(n.getNode(1));
  }

  /** Visit the specified named label node. */
  public void visitNamedLabel(GNode n) {
    countNamedLabel++;
  }

  /** Visit the specified case label node. */
  public void visitCaseLabel(GNode n) {
    countCaseLabel++;
  }

  /** Visit the specified default label node. */
  public void visitDefaultLabel(GNode n) {
    countDefaultLabel++;
  }

  /** Visit the specified compound statement node. */
  public void visitCompoundStatement(GNode n) {
    countCompoundStmt++;

    Iterator iter = n.iterator();
    while (iter.hasNext()) {
      dispatch((Node)iter.next());
    }
  }

  /** Visit the specified local label declaration node. */
  public void visitLocalLabelDeclaration(GNode n) {
    countLocalLabelDecl += n.size();
  }

  /** Visit the specified if else statement node. */
  public void visitIfElseStatement(GNode n) {
    countIfElseStmt++;

    dispatch(n.getNode(1));
    dispatch(n.getNode(2));
  }

  /** Visit the specified if statement node. */
  public void visitIfStatement(GNode n) {
    countIfStmt++;

    dispatch(n.getNode(1));
  }

  /** Visit the specified while statement node. */
  public void visitWhileStatement(GNode n) {
    countWhileStmt++;

    dispatch(n.getNode(1));
  }

  /** Visit the specified do statement node. */
  public void visitDoStatement(GNode n) {
    countDoStmt++;

    dispatch(n.getNode(0));
  }

  /** Visit the specified for statement node. */
  public void visitForStatement(GNode n) {
    countForStmt++;

    dispatch(n.getNode(0));
    dispatch(n.getNode(3));
  }

  /** Visit the specified switch statement node. */
  public void visitSwitchStatement(GNode n) {
    countSwitchStmt++;

    dispatch(n.getNode(1));
  }

  /** Visit the specified break statement node. */
  public void visitBreakStatement(GNode n) {
    countBreakStmt++;
  }

  /** Visit the specified continue statement node. */
  public void visitContinueStatement(GNode n) {
    countContinueStmt++;
  }

  /** Visit the specified return statement node. */
  public void visitReturnStatement(GNode n) {
    countReturnStmt++;
  }

  /** Visit the specified goto statement node. */
  public void visitGotoStatement(GNode n) {
    countGotoStmt++;
  }

  /** Visit the specified expression statement node. */
  public void visitExpressionStatement(GNode n) {
    countExpressionStmt++;
  }

  /** Visit the specified assembly statement node. */
  public void visitAssemblyStatement(GNode n) {
    countAssemblyStmt++;
  }

  /** Visit the specified empty statement node. */
  public void visitEmptyStatement(GNode n) {
    countEmptyStmt++;
  }

  /** Visit the specified comma expression node. */
  public void visitCommaExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified assignment expression node. */
  public void visitAssignmentExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified conditional expression node. */
  public void visitConditionalExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified logical or expression node. */
  public void visitLogicalOrExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified logical and expression node. */
  public void visitLogicalAndExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified bitwise or expression node. */
  public void visitBitwiseOrExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified bitwise xor expression node. */
  public void visitBitwiseXorExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified bitwise and expression node. */
  public void visitBitwiseAndExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified equality expression node. */
  public void visitEqualityExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified relational expression node. */
  public void visitRelationalExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified shift expression node. */
  public void visitShiftExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified additive expression node. */
  public void visitAdditiveExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified multiplicative expression node. */
  public void visitMultiplicativeExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified cast expression node. */
  public void visitCastExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified sizeof expression node. */
  public void visitSizeofExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified unary minus expression node. */
  public void visitUnaryMinusExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified unary plus expression node. */
  public void visitUnaryPlusExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified logical negation expression node. */
  public void visitLogicalNegationExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified bitwise negation expression node. */
  public void visitBitwiseNegationExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified address expression node. */
  public void visitAddressExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified indirection expression node. */
  public void visitIndirectionExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified preincrement expression node. */
  public void visitPreincrementExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified predecrement expression node. */
  public void visitPredecrementExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified subscript expression node. */
  public void visitSubscriptExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified direct component selection node. */
  public void visitDirectComponentSelection(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified indirect component selection node. */
  public void visitIndirectComponentSelection(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified function call node. */
  public void visitFunctionCall(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified postincrement expression node. */
  public void visitPostincrementExpression(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified postdecrement expression node. */
  public void visitPostdecrementExpresson(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified compound literal node. */
  public void visitCompoundLiteral(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified primary identifier node. */
  public void visitPrimaryIdentifier(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified floating constant node. */
  public void visitFloatingConstant(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified integer constant node. */
  public void visitIntegerConstant(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified character constant node. */
  public void visitCharacterConstant(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified string constant node. */
  public void visitStringConstant(GNode n) {
    /* Nothing to do, yet. */
  }

  /** Visit the specified line marker. */
  public void visit(LineMarker mark) {
    countLineMarker++;

    dispatch(mark.getNode());
  }

  /** Visit the specified pragma. */
  public void visit(Pragma p) {
    countPragma++;

    dispatch(p.getNode());
  }

}
