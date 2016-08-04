/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 IBM Corp.
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
package xtc.lang.jeannie;

import java.util.Stack;

import xtc.lang.CPrinter;
import xtc.lang.JavaPrinter;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Visitor;

/**
  A pretty printer for Jeannie (pretty JNI).
 
  This is an example of combining two visitors (CPrinter and JavaPrinter). But it
  is slightly unusual in that those visitors don't call dispatch() on themselves for
  children directly; instead, they call it indirectly through Printer, which is not
  a visitor itself.
  
  TD 41 double-check that this takes care of precedence, dangling else, and such
 
 <h2>Simplified abstract Jeannie grammar:</h2>

This grammar describes the kinds of AST nodes that can occur in a Jeannie AST; in
addition, all AST nodes from the plain C and Java grammars that are not modified here
can also occur. See JavaAstSimplifier for notation explanation.<p>

<p><u>Notation explanation</u>
<table border=0>
<tr><td><i>Whole = Part1 Part2 ... PartN</i>        <td>the <i>Whole</i> consists of all the parts <i>Part<sub>i</sub></i>
<tr><td><i>Whole = Part1 / Part2 / ... / PartN</i>  <td>the <i>Whole</i> consists of one of the parts <i>Part<sub>i</sub></i>
<tr><td><i>Super &gt;  Sub1, Sub2, ..., SubN</i>    <td>any of the <i>Sub<sub>i</sub></i> can appear where a <i>Super</i> is expected
<tr><td><i>Super &gt; {Pre1,Pre2,...,PreN}Sub</i>   <td>shorthand for <i>Super &gt; Pre1Sub, Pre2Sub, ..., PreNSub</i>
<tr><td><i>Super</i> : <i>Lit1, Lit2, ..., LitN</i>        <td>shorthand for <i>Super &gt; "Lit1", "Lit2", ..., "LitN"</i>
<tr><td>[<i>Option</i>]                             <td>zero or one occurrences
<tr><td><i>Repetee</i>*                             <td>zero or more occurrences
<tr><td><i>Repetee</i>+                             <td>one or more occurrences
<tr><td>"<i>token</i>"                              <td>literal string token
</table>

<hr size=1>

<u>Modifications to Java grammar</u>

<table border=0>
<tr><td>CompilationUnit          <td>=    <td>[PackageDeclaration] JavaImports CDeclarations JeannieJava.Declaration*
<tr><td>Block                    <td>&gt; <td>JavaInJavaBlock, CInJavaBlock
<tr><td>JeannieJava.Expression   <td>&gt; <td>..., CInJavaExpression
</table>

<u>Modifications to C grammar</u>

<table border=0>
<tr><td>TranslationUnit          <td>=    <td>[JavaImports] ExternalDeclaration* Annotations
<tr><td>CompoundStatement        <td>&gt; <td>CInCBlock, JavaInCBlock
<tr><td>FunctionDeclarator       <td>=    <td>(ParameterTypeList / IdentifierList) JavaThrows
<tr><td>JeannieC.Statement       <td>&gt; <td>..., JavaInCStatement, CancelStatement, CommitStatement, WithStatement
<tr><td>JeannieC.UnaryExpression <td>&gt; <td>..., JavaInCExpression
<tr><td>TypeSpecifier            <td>&gt; <td>..., JavaType
</table>

<u>New productions</u>

<table border=0>
<tr><td>JeannieFile              <td>&gt; <td>TranslationUnit, CompilationUnit
<tr><td>CDeclarations            <td>=    <td>ExternalDeclaration*
<tr><td>CInCBlock                <td>=    <td>LocalLabelDeclaration* JeannieC.DeclarationOrStatement* Annotations
<tr><td>CInJavaBlock             <td>=    <td>CInCBlock
<tr><td>CInJavaExpression        <td>=    <td>JeannieC.UnaryExpression
<tr><td>JavaImports              <td>=    <td>ImportDeclaration*
<tr><td>JavaInCBlock             <td>=    <td>JavaInJavaBlock
<tr><td>JavaInCExpression        <td>=    <td>JeannieJava.UnaryExpression
<tr><td>JavaInCStatement         <td>=    <td>TryStatement / SynchronizedStatement / ThrowStatement
<tr><td>JavaInJavaBlock          <td>=    <td>JeannieJava.DeclarationOrStatement*
<tr><td>JavaThrows               <td>=    <td>[ThrowsClause]
<tr><td>JavaType                 <td>=    <td>QualifiedIdentifier
<tr><td>CancelStatement          <td>=    <td>JeannieC.PrimaryIdentifier
<tr><td>CommitStatement          <td>=    <td>JeannieC.PrimaryIdentifier
<tr><td>WithStatement            <td>=    <td>WithInitializer CInCBlock
<tr><td>WithInitializer          <td>&gt; <td>JeannieC.Declaration, JeannieC.AssignmentExpression
</table>

  @author Martin Hirzel
  @version $Revision: 1.8 $
 */
public class JeanniePrinter extends Visitor {
  private static final class Context {
    final Visitor _activePrinter;

    final TransitionKind _transitionKind;

    Context(final Visitor activePrinter, final TransitionKind transitionKind) {
      _activePrinter = activePrinter;
      _transitionKind = transitionKind;
    }
  }
  
  private static final class JeannieCPrinter extends CPrinter {
    JeannieCPrinter(final Printer p) {
      super(p);
    }
    public void endExpression(final int prec) {
      super.endExpression(prec);
    }
    public int startExpression(final int prec) {
      return super.startExpression(prec);
    }
  }

  private static final class JeannieJPrinter extends JavaPrinter {
    JeannieJPrinter(final Printer p) {
      super(p);
    }
    public void endExpression(final int prec) {
      super.endExpression(prec);
    }
    public int startExpression(final int prec) {
      return super.startExpression(prec);
    }
  }

  protected enum TransitionKind { SILENT, SHORT, LONG }

  protected final Printer _printer;

  private final Stack<Context> _stack;

  private final JeannieCPrinter _cPrinter;

  private final JeannieJPrinter _jPrinter;

  public JeanniePrinter(final Printer printer, final String language) {
    _printer = printer;
    _cPrinter = new JeannieCPrinter(printer);
    _jPrinter = new JeannieJPrinter(printer);
    printer.register(this);
    _stack = new Stack<Context>();
    if ("C".equals(language))
      enterC(TransitionKind.SILENT);
    if ("Java".equals(language))
      enterJava(TransitionKind.SILENT);
  }
  
  private Visitor activePrinter() {
    return _stack.isEmpty() ? null : _stack.peek()._activePrinter;
  }

  protected final void enterC(final TransitionKind transitionKind) {
    assert _cPrinter != activePrinter();
    _stack.push(new Context(_cPrinter, transitionKind));
    switch (transitionKind) {
    case SILENT: break;
    case SHORT: _printer.p('`'); break;
    case LONG: _printer.indent().p("`.C {"); break;
    }
  }

  protected final void enterJava(final TransitionKind transitionKind) {
    assert _jPrinter != activePrinter();
    _stack.push(new Context(_jPrinter, transitionKind));
    switch(transitionKind) {
    case SILENT: break;
    case SHORT: _printer.p('`');break;
    case LONG: _printer.indent().p("`.Java {"); break;
    }
  }

  protected final void exitC() {
    assert _cPrinter == activePrinter();
    final Context old = _stack.pop();
    if (TransitionKind.LONG == old._transitionKind)
      _printer.p("}");
  }

  protected final void exitJava() {
    assert _jPrinter == activePrinter();
    final Context old = _stack.pop();
    if (TransitionKind.LONG == old._transitionKind)
      _printer.p("}");
  }

  public final void visit(final Node n) {
    activePrinter().dispatch(n);
  }

  /** Visit a Block &gt; JavaInJavaBlock, CInJavaBlock. */
  public final void visitBlock(final GNode n) {
    assert _jPrinter == activePrinter();
    assert null == n;
  }

  /** Visit a CancelStatement = JeannieC.PrimaryIdentifier. */
  public final void visitCancelStatement(final GNode n) {
    assert _cPrinter == activePrinter();
    _printer.p("_cancel ").p(n.getNode(0)).p(";");
  }

  /** Visit a CDeclarations = ExternalDeclaration*. */
  public final void visitCDeclarations(final GNode n) {
    enterC(TransitionKind.LONG);
    for (int i = 0; i < n.size(); i++)
      dispatch(n.getNode(i));
    exitC();
  }
  
  /** Visit a CInCBlock = LocalLabelDeclaration* JeannieC.DeclarationOrStatement* Annotations. */
  public final void visitCInCBlock(final GNode n) {
    assert _cPrinter == activePrinter();
    _cPrinter.visitCompoundStatement(n);
  }
  
  /** Visit a CInJavaBlock = CInCBlock. */
  public final void visitCInJavaBlock(final GNode n) {
    enterC(TransitionKind.SHORT);
    dispatch(n.getNode(0));
    exitC();
  }

  /** Visit a CInJavaExpression = JeannieC.UnaryExpression. */
  public final void visitCInJavaExpression(final GNode n) {
    enterC(TransitionKind.SHORT);
    final int prec = _cPrinter.startExpression(150);
    dispatch(n.getNode(0));
    _cPrinter.endExpression(prec);
    exitC();
  }

  /** Visit a CommitStatement = JeannieC.PrimaryIdentifier. */
  public final void visitCommitStatement(final GNode n) {
    assert _cPrinter == activePrinter();
    _printer.p("_commit ").p(n.getNode(0)).p(";");
  }

  /** Visit a CompilationUnit = [PackageDeclaration] JavaImports CDeclarations JeannieJava.Declaration*. */
  public final void visitCompilationUnit(final GNode n) {
    assert null == activePrinter();
    enterJava(TransitionKind.SILENT);
    activePrinter().dispatch(n);
    exitJava();
  }
  
  /** Visit a CompoundStatement &gt; CInCBlock, JavaInCBlock. */
  public final void visitCompoundStatement(final GNode n) {
    assert null == n;
  }

  /** Visit a File &gt; TranslationUnit, CompilationUnit. */
  public final void visitFile(final GNode n) {
    assert null == n;
  }

  /** Visit a FunctionDeclarator = (ParameterTypeList / IdentifierList) JavaThrows. */
  public final void visitFunctionDeclarator(final GNode n) {
    assert _cPrinter == activePrinter();
    _cPrinter.dispatch(n);
    dispatch(n.getNode(2));
  }

  /** Visit a JavaImports = ImportDeclaration*. */
  public final void visitJavaImports(final GNode n) {
    final boolean needTransition = _cPrinter == activePrinter();
    if (needTransition)
      enterJava(TransitionKind.LONG);
    for (int i = 0; i < n.size(); i++)
      dispatch(n.getNode(i));
    if (needTransition)
      exitJava();
  }

  /** Visit a JavaInCBlock = JavaInJavaBlock. */
  public final void visitJavaInCBlock(final GNode n) {
    enterJava(TransitionKind.SHORT);
    dispatch(n.getNode(0));
    exitJava();
  }

  /** Visit a JavaInCExpression = JeannieJava.UnaryExpression. */
  public final void visitJavaInCExpression(final GNode n) {
    enterJava(TransitionKind.SHORT);
    final int prec = _jPrinter.startExpression(150);
    dispatch(n.getNode(0));
    _jPrinter.endExpression(prec);
    exitJava();
  }

  /** Visit a JavaInCStatement = TryStatement / SynchronizedStatement / ThrowStatement. */
  public final void visitJavaInCStatement(final GNode n) {
    enterJava(TransitionKind.SHORT);
    dispatch(n.getNode(0));
    exitJava();
  }

  /** Visit a JavaInJavaBlock = JeannieJava.DeclarationOrStatement*. */
  public final void visitJavaInJavaBlock(final GNode n) {
    assert _jPrinter == activePrinter();
    _jPrinter.visitBlock(n);
  }

  /** Visit a JavaThrows = [ThrowsClause]. */
  public final void visitJavaThrows(final GNode n) {
    if (null == n.get(0))
      return;
    enterJava(TransitionKind.SHORT);
    dispatch(n.getNode(0));
    exitJava();
  }
  
  /** Visit a JavaType = QualifiedIdentifier. */
  public final void visitJavaType(final GNode n) {
    enterJava(TransitionKind.SHORT);
    dispatch(n.getNode(0));
    exitJava();
  }

  /** Visit a TranslationUnit = [JavaImports] ExternalDeclaration* Annotations. */
  public final void visitTranslationUnit(final GNode n) {
    assert null == activePrinter();
    enterC(TransitionKind.SILENT);
    activePrinter().dispatch(n);
    exitC();
  }

  /** Visit a WithStatement = (JeannieC.Declaration / JeannieC.AssignmentExpression) CInCBlock. */
  public final void visitWithStatement(final GNode n) {
    assert _cPrinter == activePrinter();
    _printer.p("_with (");
    dispatch(n.getNode(0));
    _printer.p(")");
    dispatch(n.getNode(1));
  }
}
