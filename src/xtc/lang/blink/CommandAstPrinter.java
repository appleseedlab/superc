package xtc.lang.blink;

import xtc.tree.GNode;
import xtc.tree.Printer;
import xtc.lang.jeannie.JeanniePrinter;

public final class CommandAstPrinter extends JeanniePrinter {
  public CommandAstPrinter(final Printer printer) {
    super(printer, null);
  }

  /** Visit a BreakClassCommand = QualifiedIdentifier LineNumber. */
  public final void visitBreakClassCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("stop at ").p(n.getNode(0)).p(':').p(n.getString(1)).pln();
    exitJava();
  }

  /** Visit a BreakFileCommand = FileName LineNumber. */
  public final void visitBreakFileCommand(final GNode n) {
    _printer.p("break ").p(n.getString(0)).p(':').p(n.getString(1)).pln();
  }

  /** Visit a C2jCommand = (no children). */
  public final void visitC2jCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("c2j").pln();
  }

  /** Visit a ContinueCommand = (no children). */
  public final void visitContinueCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("continue").pln();
  }

  /** Visit a DeleteCommand = IntegerLiteral. */
  public final void visitDeleteCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("delete ").p(n.getNode(0)).pln();
    exitJava();
  }

  /** Visit a DownCommand = IntegerLiteral. */
  public final void visitDownCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("down ").p(n.getNode(0)).pln();
    exitJava();
  }

  /** Visit a ExitCommand = (no children). */
  public final void visitExitCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("exit").pln();
  }

  /** Visit a GdbCommand = RestOfLine. */
  public final void visitGdbCommand(final GNode n) {
    _printer.p("gdb ").p(n.getString(0)).pln();
  }
  
  /** Visit a HelpCommand = (no children). */
  public final void visitHelpCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("help").pln();
  }

  /** Visit a InfoBreakCommand = (no children). */
  public final void visitInfoBreakCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("info break").pln();
  }

  /** Visit a InfoWatchCommand = (no children). */
  public final void visitInfoWatchCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("info watch").pln();
  }

  /** Visit an InitJCommand = (no children). */
  public final void visitInitJCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("initj").pln();
  }
  
  /** Visit a J2cCommand = (no children). */
  public final void visitJ2cCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("j2c").pln();
  }
  
  /** Visit a JdbCommand = RestOfLine. */
  public final void visitJdbCommand(final GNode n) {
    _printer.p("jdb ").p(n.getString(0)).pln();
  }
  
  /** Visit a JRetCommand = (no children). */
  public final void visitJRetCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("jret").pln();
  }
  
  /** Visit a ListCommand = (no children). */
  public final void visitListCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("list").pln();
  }

  /** Visit a LocalsCommand = (no children). */
  public final void visitLocalsCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("locals").pln();
  }

  /** Visit a NextCommand = (no children). */
  public final void visitNextCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("next").pln();
  }

  /** Visit a RunCommand = (no children). */
  public final void visitRunCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("run").pln();    
  }
  
  /** Visit a PrintCExpressionCommand = C.Expression. */
  public final void visitPrintCExpressionCommand(final GNode n) {
    enterC(TransitionKind.SILENT);
    _printer.p("print ").p(n.getNode(0)).pln();
    exitC();
  }

  /** Visit a PrintJavaExpressionCommand = Java.Expression. */
  public final void visitPrintJavaExpressionCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("print ").p(n.getNode(0)).pln();
    exitJava();
  }

  /** Visit a StatCommand = (no children). */
  public final void visitStatCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("stat").pln();
  }

  /** Visit a StepCommand = (no children). */
  public final void visitStepCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("step").pln();
  }

  /** Visit a UpCommand = IntegerLiteral. */
  public final void visitUpCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("up ").p(n.getNode(0)).pln();
    exitJava();
  }

  /** Visit a WatchCExpressionCommand = C.Expression. */
  public final void visitWatchCExpressionCommand(final GNode n) {
    enterC(TransitionKind.SILENT);
    _printer.p("watch ").p(n.getNode(0)).pln();
    exitC();
  }

  /** Visit a WatchJavaFieldCommand = WatchKind? QualifiedIdentifier. */
  public final void visitWatchJavaFieldCommand(final GNode n) {
    enterJava(TransitionKind.SILENT);
    _printer.p("watch ");
    if (null != n.get(0))
      _printer.p(n.getString(0)).p(' ');
    _printer.p(n.getNode(1)).pln();
    exitJava();
  }

  /** Visit a WhereCommand = (no children). */
  public final void visitWhereCommand(final GNode n) {
    assert 0 == n.size();
    _printer.p("where").pln();
  }

  /** Visit a MetaVariable = Identifier. */
  public final void visitMetaVariable(final GNode n) {
    _printer.p('$').p(n.getString(0)).pln();
  }
}
