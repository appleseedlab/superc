/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004-2008 Robert Grimm
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
import xtc.tree.SourceIdentity;
import xtc.tree.Token;
import xtc.tree.Visitor;

/**
 * A pretty printer for C.
 *
 * <p />A note on operator precedence: This printer uses precedence
 * levels to control when to print parentheses around expressions.
 * The actual precedence values are the standard C precedence levels
 * multiplied by ten.
 *
 * @author Robert Grimm
 * @version $Revision: 1.75 $
 */
public class CPrinter extends Visitor {

  /**
   * The flag for printing additional parentheses to avoid gcc
   * warnings.
   */
  public static final boolean EXTRA_PARENTHESES = true;

  /**
   * The base precedence level. This level corresponds to the
   * expression nonterminal.
   */
  public static final int PREC_BASE = 0;

  /**
   * The list precedence level.  This level corresponds to the
   * assignment expression nonterminal.
   */
  public static final int PREC_LIST = 11;

  /**
   * The constant precedence level.  This level corresponds to the
   * conditional expression nonterminal.
   */
  public static final int PREC_CONSTANT = 21;

  /** The flag for any statement besides an if or if-else statement. */
  public static final int STMT_ANY = 0;

  /** The flag for an if statement. */
  public static final int STMT_IF = 1;

  /** The flag for an if-else statement. */
  public static final int STMT_IF_ELSE = 2;

  /** The printer for this C printer. */
  protected final Printer printer;

  /**
   * The flag for whether to line up declarations and statements with
   * their source locations.
   */
  protected final boolean lineUp;

  /** The flag for whether to use GNU coding guidelines. */
  protected final boolean gnuify;

  /** The flag for whether we just printed a declaration. */
  protected boolean isDeclaration;

  /**
   * The flag for whether we just printed a declaration spanning
   * several lines.
   */
  protected boolean isLongDecl;

  /** The flag for whether we just printed a statement. */
  protected boolean isStatement;

  /** The flag for whether the last statement ended with an open line. */
  protected boolean isOpenLine;

  /**
   * The flag for whether the current statement requires nesting or
   * for whether the current declaration is nested within a for
   * statement.
   */
  protected boolean isNested;

  /**
   * The flag for whether this statement is the else clause of an
   * if-else statement.
   */
  protected boolean isIfElse;

  /**
   * The flag for whether this compound statement is an expression (as
   * in the GCC extension).
   */
  protected boolean isStmtAsExpr;

  /**
   * The flag for whether this declarator is a function definition.
   */
  protected boolean isFunctionDef;

  /** The operator precedence level for the current expression. */
  protected int precedence;

  /**
   * Create a new C printer.
   *
   * @param printer The printer.
   */
  public CPrinter(Printer printer) {
    this(printer, false, false);
  }

  /**
   * Create a new C printer.
   *
   * @param printer The printer.
   * @param lineUp The flag for whether to line up declaratons and
   *   statements with their source locations.
   * @param gnuify The flag for whether to use GNU code formatting
   *   conventions.
   */
  public CPrinter(Printer printer, boolean lineUp, boolean gnuify) {
    this.printer = printer;
    this.lineUp  = lineUp;
    this.gnuify  = gnuify;
    printer.register(this);
  }

  /**
   * Determine whether the specified generic node contains a long type
   * definition.  A long type definition requires multiple lines for
   * readability.  Examples include enumeration, structure, and union
   * type definitions. 
   *
   * @param specs The generic node, representing a list of specifiers.
   * @return <code>true</code> if the specifiers contain a long
   *   type specifier.
   */
  protected boolean containsLongType(GNode specs) {
    for (Object o : specs) {
      GNode node = GNode.cast(o);
      if (node.hasName("EnumerationTypeDefinition") ||
          node.hasName("StructureTypeDefinition") ||
          node.hasName("UnionTypeDefinition")) {
        return true;
      }
    }

    return false;
  }

  /**
   * Determine whether the specified declaration is long.  A long
   * declaration requires multiple lines for readability.  Examples
   * include declarations containing enumeration, structure, and union
   * type definitions.
   *
   * @param decl The declaration.
   * @return <code>true</code> if the specified declaration is long.
   */
  protected boolean isLongDeclaration(GNode decl) {
    // Make sure the specified generic node actually is a declaration.
    if (! decl.hasName("Declaration")) return false;

    // Check the declaration specifiers for enumeration, structure,
    // and union definitions (but not declarations).
    if (containsLongType(decl.getGeneric(1))) return true;

    // Check the initialized declarator list for initializer lists.
    GNode n = decl.getGeneric(2);
    if (null != n) {
      for (Object o : n) {
        GNode elem = GNode.cast(o).getGeneric(3);
        if ((null != elem) && elem.hasName("InitializerList")) {
          return true;
        }
      }
    }

    // Done.
    return false;
  }

  /**
   * Print an expression as a truth value.  This method prints the
   * specified node.  If that node represents an assignment expression
   * and {@link #EXTRA_PARENTHESES} is <code>true</code>, this method
   * adds an extra set of parentheses around the expression to avoid
   * gcc warnings.
   *
   * @param n The node to print.
   */
  protected void formatAsTruthValue(Node n) {
    if (GNode.cast(n).hasName("AssignmentExpression")) {
      printer.p('(').p(n).p(')');
    } else {
      printer.p(n);
    }
  }

  /**
   * Start a new statement.  This method and the corresponding {@link
   * #prepareNested()} and {@link #endStatement(boolean)} methods
   * provide a reasonable default for newlines and indentation when
   * printing statements.  They manage the {@link #isDeclaration},
   * {@link #isStatement}, {@link #isOpenLine}, {@link #isNested}, and
   * {@link #isIfElse} flags.
   *
   * @param kind The kind of statement, which must be one of the
   *   three statement flags defined by this class.
   * @param node The statement's node.
   * @return The flag for whether the current statement is nested.
   */
  protected boolean startStatement(int kind, Node node) {
    if (isIfElse && ((STMT_IF == kind) || (STMT_IF_ELSE == kind))) {
      isNested = false;
    } else {
      if (lineUp) {
        if (isOpenLine) printer.pln();
        printer.lineUp(node);
      } else {
        if (isDeclaration || isOpenLine) {
          printer.pln();
        }
      }
      if (isNested) {
        printer.incr();
      }
    }

    isOpenLine     = false;
    boolean nested = isNested;
    isNested       = false;

    return nested;
  }

  /**
   * Prepare for a nested statement.
   *
   * @see #startStatement
   */
  protected void prepareNested() {
    isDeclaration = false;
    isStatement   = false;
    isOpenLine    = true;
    isNested      = true;
  }

  /**
   * End a statement.
   *
   * @see #startStatement
   *
   * @param nested The flag for whether the current statement is nested.
   */
  protected void endStatement(boolean nested) {
    if (nested) {
      printer.decr();
    }
    isDeclaration = false;
    isStatement   = true;
  }

  /**
   * Enter an expression context.  The new context has the specified
   * precedence level.
   *
   * @see #exitContext(int)
   *
   * @param prec The precedence level for the expression context.
   * @return The previous precedence level.
   */
  protected int enterContext(int prec) {
    int old    = precedence;
    precedence = prec;
    return old;
  }

  /**
   * Enter an expression context.  The new context is appropriate for
   * an operand opposite the associativity of the current operator.
   * For example, when printing an additive expression, this method
   * should be called before printing the second operand, as additive
   * operators associate left-to-right.
   *
   * @see #exitContext(int)
   *
   * @return The previous precedence level.
   */
  protected int enterContext() {
    int old     = precedence;
    precedence += 1;
    return old;
  }

  /**
   * Exit an expression context.
   *
   * @see #enterContext(int)
   * @see #enterContext()
   *
   * @param prec The previous precedence level.
   */
  protected void exitContext(int prec) {
    precedence = prec;
  }

  /**
   * Start printing an expression at the specified operator precedence
   * level.
   *
   * @see #endExpression(int)
   *
   * @param prec The expression's precedence level.
   * @return The previous precedence level.
   */
  protected int startExpression(int prec) {
    if (prec < precedence) {
      printer.p('(');
    }

    int old    = precedence;
    precedence = prec;
    return old;
  }

  /**
   * Stop printing an expression.
   *
   * @see #startExpression(int)
   *
   * @param prec The previous precedence level.
   */
  protected void endExpression(int prec) {
    if (precedence < prec) {
      printer.p(')');
    }
    precedence = prec;
  }

  /** Visit the specified translation unit node. */
  public void visitTranslationUnit(GNode n) {
    // Reset the state.
    isDeclaration  = false;
    isLongDecl     = false;
    isStatement    = false;
    isOpenLine     = false;
    isNested       = false;
    isIfElse       = false;
    isStmtAsExpr   = false;
    isFunctionDef  = false;
    precedence     = PREC_BASE;

    if (lineUp) printer.line(1);

    for (Object o : n) {
      printer.p((Node)o);
    }
  }

  /** Visit the specified function definition node. */
  public void visitFunctionDefinition(GNode n) {
    if (lineUp) {
      if (isOpenLine) printer.pln();
      printer.lineUp(n);
    } else if (isStatement || isDeclaration || isLongDecl) {
      if (isOpenLine) printer.pln();
      printer.pln();
    }

    isDeclaration = false;
    isLongDecl    = false;
    isStatement   = false;
    isOpenLine    = false;
    isNested      = false;
    isIfElse      = false;

    // Print extension and return type.
    printer.indent();
    if ((null != n.get(0)) || (null != n.get(1))) {
      if (null != n.get(0)) {
        printer.p("__extension__ ");
      }
      printer.p(n.getNode(1));
    }

    // Print function name and parameters.
    Node declor = n.getNode(2);
    if (gnuify) {
      GNode g = GNode.cast(declor);
      if (g.hasName("PointerDeclarator")) {
        isFunctionDef = true;
        printer.p(' ').p(declor);
        declor = g.getNode(1);
      }
      printer.pln().indent();
    } else if (null != n.get(1)) {
      printer.p(' ');
    }
    printer.p(declor);
    if (null != n.get(3)) {
      printer.pln().incr().p(n.getNode(3)).decr();
    } else if (gnuify) {
      printer.pln();
      isOpenLine = false;
    } else {
      isOpenLine = true;
    }

    isDeclaration = false;
    isLongDecl    = false;
    isStatement   = false;
    isNested      = false;
    isIfElse      = false;

    printer.p(n.getNode(4)).pln();

    isDeclaration = true;
    isLongDecl    = true;
    isStatement   = false;
    isOpenLine    = false;
    isNested      = false;
    isIfElse      = false;
  }

  /** Visit the specified empty definition. */
  public void visitEmptyDefinition(GNode n) {
    /* We are not printing anything. */
  }

  /** Visit the specified declaration list node. */
  public void visitDeclarationList(GNode n) {
    for (Object o : n) printer.p((Node)o);
  }

  /** Visit the specified declaration node. */
  public void visitDeclaration(GNode n) {
    boolean nested = isNested;
    if (! nested) {
      if (lineUp) {
        if (isOpenLine) printer.pln();
        printer.lineUp(n);
      } else if (isStatement || isLongDecl) {
        if (isOpenLine) printer.pln();
        printer.pln();
      } else if (isLongDeclaration(n)) {
        printer.pln();
      }
      printer.indent();
    }

    isDeclaration  = false;
    isLongDecl     = false;
    isStatement    = false;
    isOpenLine     = false;
    isNested       = false;
    isIfElse       = false;

    if (null != n.get(0)) {
      printer.p("__extension__ ");
    }
    printer.p(n.getNode(1));
    if (null != n.get(2)) {
      printer.p(' ').p(n.getNode(2));
    }
    if (! nested) {
      printer.p(';').fitMore().pln();
    }

    isDeclaration  = true;
    isStatement    = false;
    isOpenLine     = false;
    isNested       = false;
    isIfElse       = false;
  }

  /** Visit the specified declaration specifiers node. */
  public void visitDeclarationSpecifiers(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(' ');
      }
    }
  }

  /** Visit the specified auto storage class specifier node. */
  public void visitAutoSpecifier(GNode n) {
    printer.p("auto");
  }

  /** Visit the specified extern storage class specifier node. */
  public void visitExternSpecifier(GNode n) {
    printer.p("extern");
  }

  /** Visit the specified register storage class specifier node. */
  public void visitRegisterSpecifier(GNode n) {
    printer.p("register");
  }

  /** Visit the specified static storage class specifier node. */
  public void visitStaticSpecifier(GNode n) {
    printer.p("static");
  }

  /** Visit the specified thread storage class specifier node. */
  public void visitThreadSpecifier(GNode n) {
    printer.p("__thread");
  }

  /** Visit the specified typedef storage class specifier node. */
  public void visitTypedefSpecifier(GNode n) {
    printer.p("typedef");
  }

  /** Visit the specified volatile qualifier node. */
  public void visitVolatileQualifier(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified constant qualifier node. */
  public void visitConstantQualifier(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified restrict qualifier node. */
  public void visitRestrictQualifier(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified function specifier node. */
  public void visitFunctionSpecifier(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified enumeration type definition. */
  public void visitEnumerationTypeDefinition(GNode n) {
    printer.p("enum ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    if (null != n.get(1)) {
      printer.p(n.getString(1)).p(' ');
    }
    printer.pln('{').incr().p(n.getNode(2)).decr().indent().p('}');
    if (null != n.get(3)) {
      printer.p(' ').p(n.getNode(3));
    }
    isLongDecl = true;
  }

  /** Visit the specified enumerator list node. */
  public void visitEnumeratorList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.indent().p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(',');
      }
      printer.pln();
    }
  }

  /** Visit the specified enumerator node. */
  public void visitEnumerator(GNode n) {
    printer.p(n.getString(0));
    if (null != n.get(1)) {
      int prec = enterContext(PREC_CONSTANT);
      printer.p(" = ").p(n.getNode(1));
      exitContext(prec);
    }
  }

  /** Visit the specified enumeration type reference node. */
  public void visitEnumerationTypeReference(GNode n) {
    printer.p("enum ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getString(1));
  }

  /** Visit the specified structure type definition. */
  public void visitStructureTypeDefinition(GNode n) {
    printer.p("struct ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    if (null != n.get(1)) {
      printer.p(n.getString(1)).p(' ');
    }
    printer.pln('{').incr().p(n.getNode(2)).decr().indent().p('}');
    if (null != n.get(3)) {
      printer.p(' ').p(n.getNode(3));
    }
    isLongDecl = true;
  }

  /** Visit the specified structure type reference. */
  public void visitStructureTypeReference(GNode n) {
    printer.p("struct ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getString(1));
  }

  /** Visit the specified union type definition. */
  public void visitUnionTypeDefinition(GNode n) {
    printer.p("union ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    if (null != n.get(1)) {
      printer.p(n.getString(1)).p(' ');
    }
    printer.pln('{').incr().p(n.getNode(2)).decr().indent().p('}');
    if (null != n.get(3)) {
      printer.p(' ').p(n.getNode(3));
    }
    isLongDecl = true;
  }

  /** Visit the specified union type reference. */
  public void visitUnionTypeReference(GNode n) {
    printer.p("union ");
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getString(1));
  }

  /** Visit the specified structure declaration list node. */
  public void visitStructureDeclarationList(GNode n) {
    boolean wasLong = false;
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      Node node = (Node)iter.next();

      if (! iter.hasNext()) {
        // Do nothing for last child representing annotations.
      } else if (containsLongType(GNode.cast(node).getGeneric(1))) {
        printer.pln();
        wasLong    = true;
      } else if (wasLong) {
        printer.pln();
        wasLong    = false;
      }
      printer.p(node);
    }
  }

  /** Visit the specified structure declaration node. */
  public void visitStructureDeclaration(GNode n) {
    printer.indent();
    if (null != n.get(0)) {
      printer.p("__extension__ ");
    }
    printer.p(n.getNode(1));
    if (null != n.get(2)) {
      printer.p(' ').p(n.getNode(2));
    }
    printer.pln(';');
  }

  /** Visit the specified specifier qualifier list node. */
  public void visitSpecifierQualifierList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) printer.p(' ');
    }
  }

  /** Visit the specified structure declarator list node. */
  public void visitStructureDeclaratorList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified bit field node. */
  public void visitBitField(GNode n) {
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getNode(1)).p(':');

    int prec = enterContext(PREC_CONSTANT);
    printer.p(n.getNode(2));
    exitContext(prec);

    if (null != n.get(3)) {
      printer.p(' ').p(n.getNode(3));
    }
  }

  /** Visit the specified attributed declarator node. */
  public void visitAttributedDeclarator(GNode n) {
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getNode(1));
    if (null != n.get(2)) {
      printer.p(' ').p(n.getNode(2));
    }
  }

  /** Visit the specified pointer declarator node. */
  public void visitPointerDeclarator(GNode n) {
    printer.p(n.getNode(0));
    if (isFunctionDef) {
      isFunctionDef = false;
      return;
    }
    printer.p(n.getNode(1));
  }

  /** Visit the specified pointer node. */
  public void visitPointer(GNode n) {
    printer.p('*').p(n.getNode(0)).p(n.getNode(1));
  }

  /** Visit the specified type qualifier list node. */
  public void visitTypeQualifierList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p(' ').p((Node)iter.next());
      if (! iter.hasNext()) {
        printer.p(' ');
      }
    }
  }

  /** Visit the specified simple declarator node. */
  public void visitSimpleDeclarator(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified function declarator node. */
  public void visitFunctionDeclarator(GNode n) {
    if (n.getGeneric(0).hasName("SimpleDeclarator")) {
      printer.p(n.getNode(0));
    } else {
      printer.p('(').p(n.getNode(0)).p(')');
    }
    printer.p('(').p(n.getNode(1)).p(')');
  }

  /** Visit the specified parameter type list node. */
  public void visitParameterTypeList(GNode n) {
    printer.p(n.getNode(0));
    if (null != n.get(1)) {
      printer.p(", ...");
    }
  }

  /** Visit the specified parameter list node. */
  public void visitParameterList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified parameter declaration node. */
  public void visitParameterDeclaration(GNode n) {
    printer.p(n.getNode(0));
    if (null != n.get(1)) {
      printer.p(' ').p(n.getNode(1));
    }
    if (null != n.get(2)) {
      printer.p(' ').p(n.getNode(2));
    }
  }

  /** Visit the specified attributed abstract declarator node. */
  public void visitAttributedAbstractDeclarator(GNode n) {
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getNode(1));
  }

  /** Visit the specified abstract declarator node. */
  public void visitAbstractDeclarator(GNode n) {
    printer.p(n.getNode(0)).p(n.getNode(1));
  }

  /** Visit the specified direct abstract declarator node. */
  public void visitDirectAbstractDeclarator(GNode n) {
    if (null != n.get(0)) {
      printer.p('(').p(n.getNode(0)).p(')');
    }
    if ("[".equals(n.get(1))) {
      printer.p('[');

      if (null != n.get(2)) {
        int prec = enterContext(PREC_LIST);
        printer.p(n.getNode(2));
        exitContext(prec);
      }

      printer.p(']');

    } else {
      printer.p('(').p(n.getNode(2)).p(')');
    }
  }

  /** Visit the specified identifier list node. */
  public void visitIdentifierList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p(Token.cast(iter.next()));
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified array declarator node. */
  public void visitArrayDeclarator(GNode n) {
    if (n.getGeneric(0).hasName("SimpleDeclarator")) {
      printer.p(n.getNode(0));
    } else {
      printer.p('(').p(n.getNode(0)).p(')');
    }

    printer.p('[');
    int column = printer.column();
    printer.p(n.getNode(1));

    if (null != n.get(2)) {
      if (printer.column() != column) printer.p(' ');
      int prec = enterContext(PREC_LIST);
      printer.p(n.getNode(2));
      exitContext(prec);
    }
    printer.p(']');
  }

  /** Visit the specified variable length node. */
  public void visitVariableLength(GNode n) {
    printer.p('*');
  }

  /** Visit the specified array qualifier list node. */
  public void visitArrayQualifierList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(' ');
      }
    }
  }

  /** Visit the specified complex node. */
  public void visitComplex(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified double node. */
  public void visitDouble(GNode n) {
    printer.p("double");
  }

  /** Visit the specified float node. */
  public void visitFloat(GNode n) {
    printer.p("float");
  }

  /** Visit the specified long node. */
  public void visitLong(GNode n) {
    printer.p("long");
  }

  /** Visit the specified int node. */
  public void visitInt(GNode n) {
    printer.p("int");
  }

  /** Visit the specified short node. */
  public void visitShort(GNode n) {
    printer.p("short");
  }

  /** Visit the specified char node. */
  public void visitChar(GNode n) {
    printer.p("char");
  }

  /** Visit the specified bool node. */
  public void visitBool(GNode n) {
    printer.p("_Bool");
  }

  /** Visit the specified unsigned node. */
  public void visitUnsigned(GNode n) {
    printer.p("unsigned");
  }

  /** Visit the specified signed node. */
  public void visitSigned(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified typedef name node. */
  public void visitTypedefName(GNode n) {
    printer.p(n.getString(0));
  }

  /** Visit the specified typeof specifier node. */
  public void visitTypeofSpecifier(GNode n) {
    int prec = enterContext(PREC_BASE);
    printer.p("typeof(").p(n.getNode(0)).p(')');
    exitContext(prec);
  }

  /** Visit the specified void type specifier node. */
  public void visitVoidTypeSpecifier(GNode n) {
    printer.p("void");
  }

  /** Visit the specified variable argument list specifier node. */
  public void visitVarArgListSpecifier(GNode n) {
    printer.p("__builtin_va_list");
  }

  /** Visit the specified initialized declarator list node. */
  public void visitInitializedDeclaratorList(GNode n) {
    boolean  first = true;
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      if (first) {
        first = false;
      } else {
        printer.buffer();
      }
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ").fitMore();
      }
    }
  }

  /** Visit the specified initialized declarator node. */
  public void visitInitializedDeclarator(GNode n) {
    if (null != n.get(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p(n.getNode(1));
    if (null != n.get(2)) {
      printer.p(' ').p(n.getNode(2));
    }
    if (null != n.get(3)) {
      printer.p(' ').p(n.getNode(3));
    }
    if (null != n.get(4)) {
      printer.p(" = ");
      int prec = enterContext(PREC_LIST);
      printer.p(n.getNode(4));
      exitContext(prec);
    }
  }

  /** Visit the specified initializer list node. */
  public void visitInitializerList(GNode n) {
    if (! n.isEmpty()) {
      printer.pln('{').incr().indent();
      for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
        printer.buffer().p((Node)iter.next());
        if (iter.hasNext()) {
          printer.p(", ");
        }
        printer.fit();
      }
      printer.pln().decr().indent().p('}');
      isLongDecl = true;
    } else {
      printer.p("{ }");
    }
  }

  /** Visit the specified initializer list entry node. */
  public void visitInitializerListEntry(GNode n) {
    printer.p(n.getNode(0));
    int prec = enterContext(PREC_LIST);
    printer.p(n.getNode(1));
    exitContext(prec);
  }

  /** Visit the specified designation node. */
  public void visitDesignation(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(' ');
      }
    }
    printer.p(" = ");
  }

  /** Visit the specified obsolete array designation node. */
  public void visitObsoleteArrayDesignation(GNode n) {
    // Print the obsolete array designation as a standard array
    // designation.
    int prec = enterContext(PREC_CONSTANT);
    printer.p('[').p(n.getNode(1));
    if (3 == n.size() && null != n.getGeneric(2)) {
      printer.p(" ... ").p(n.getNode(2));
    }
    printer.p(']');
    exitContext(prec);
    printer.p(" = ");
  }

  /** Visit the specified obsolete field designation node. */
  public void visitObsoleteFieldDesignation(GNode n) {
    // Print the obsolete field designation as a standard field
    // designation.
    printer.p('.').p(n.getString(0)).p(" = ");
  }

  /** Visit the specified designator entry node. */
  public void visitDesignator(GNode n) {
    if ("[".equals(n.get(0))) {
      int prec = enterContext(PREC_CONSTANT);
      printer.p('[').p(n.getNode(1));
      if (3 == n.size()) {
        printer.p(" ... ").p(n.getNode(2));
      }
      printer.p(']');
      exitContext(prec);
    } else {
      printer.p('.').p(n.getNode(1));
    }
  }

  /** Visit the specified type name node. */
  public void visitTypeName(GNode n) {
    printer.p(n.getNode(0));
    if (null != n.get(1)) {
      printer.p(' ').p(n.getNode(1));
    }
  }

  /** Visit the specified attribute specifier list node. */
  public void visitAttributeSpecifierList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(' ');
      }
    }
  }

  /** Visit the specified attribute specifier node. */
  public void visitAttributeSpecifier(GNode n) {
    printer.p("__attribute__((").p(n.getNode(0)).p("))");
  }

  /** Visit the specified attribute list node. */
  public void visitAttributeList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified attribute list entry node. */
  public void visitAttributeListEntry(GNode n) {
    printer.p(n.getString(0));
    if (null != n.get(1)) {
      printer.p('(').p(n.getNode(1)).p(')');
    }
  }

  /** Visit the specified labeled statement node. */
  public void visitLabeledStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indentLess().p(n.getNode(0)).pln();
    isDeclaration  = false;
    isStatement    = true;
    printer.p(n.getNode(1));
    endStatement(nested);
  }

  /** Visit the specified named label node. */
  public void visitNamedLabel(GNode n) {
    printer.p(n.getString(0));
    if (null == n.get(1)) {
      printer.p(':');
    } else {
      printer.p(": ").p(n.getNode(1));
    }
  }

  /** Visit the specified case label node. */
  public void visitCaseLabel(GNode n) {
    int prec = enterContext(PREC_CONSTANT);
    printer.p("case ").p(n.getNode(0));
    if (2 == n.size()) {
      printer.p(" ... ").p(n.getNode(1));
    }
    printer.p(':');
    exitContext(prec);
  }

  /** Visit the specified default label node. */
  public void visitDefaultLabel(GNode n) {
    printer.p("default:");
  }

  /** Visit the specified compound statement node. */
  public void visitCompoundStatement(GNode n) {
    boolean stmtAsExpr = isStmtAsExpr;
    isStmtAsExpr       = false;
    boolean nested     = isNested;

    if (stmtAsExpr) {
      printer.pln(" ({").incr();
    } else if (nested && gnuify) {
      printer.pln().incr().indent().pln('{').incr();
    } else if (isOpenLine) {
      printer.pln(" {").incr();
    } else {
      printer.indent().pln('{').incr();
    }

    isOpenLine    = false;
    isNested      = false;
    isIfElse      = false;
    for (Object o : n) printer.p((Node)o);

    if (isOpenLine) {
      printer.pln();
    }
    if (stmtAsExpr) {
      printer.decr().indent().p("})");
      isOpenLine = true;
    } else if (nested && gnuify) {
      printer.decr().indent().pln('}').decr();
      isOpenLine = false;
    } else {
      printer.decr().indent().p('}');
      isOpenLine = true;
    }
    isNested      = false;
    isIfElse      = false;
    isStmtAsExpr  = stmtAsExpr;
  }

  /** Visit the specified label declaration node. */
  public void visitLocalLabelDeclaration(GNode n) {
    if (! isNested) {
      if (lineUp) {
        if (isOpenLine) printer.pln();
        printer.lineUp(n);
      } else if (isStatement || isLongDecl) {
        if (isOpenLine) printer.pln();
        printer.pln();
      } else if (isLongDeclaration(n)) {
        printer.pln();
      }
      printer.indent();
    }

    printer.p("__label__ ");
    
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p(Token.cast(iter.next()));
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }

    printer.pln(';');

    isDeclaration  = true;
    isStatement    = false;
    isOpenLine     = false;
    isNested       = false;
    isIfElse       = false;
  }

  /** Visit the specified if else statement node. */
  public void visitIfElseStatement(GNode n) {
    boolean nested = startStatement(STMT_IF_ELSE, n);
    if (isIfElse) {
      printer.p(' ');
    } else {
      printer.indent();
    }
    printer.p("if (");
    formatAsTruthValue(n.getNode(0));
    printer.p(')');
    prepareNested();
    printer.p(n.getNode(1));
    if (isOpenLine) {
      printer.p(" else");
    } else {
      printer.indent().p("else");
    }
    prepareNested();
    boolean ifElse = isIfElse;
    isIfElse       = true;
    printer.p(n.getNode(2));
    isIfElse       = ifElse;
    endStatement(nested);
  }

  /** Visit the specified if statement node. */
  public void visitIfStatement(GNode n) {
    boolean nested = startStatement(STMT_IF, n);
    if (isIfElse) {
      printer.p(' ');
    } else {
      printer.indent();
    }
    printer.p("if (");
    formatAsTruthValue(n.getNode(0));
    printer.p(')');
    prepareNested();
    printer.p(n.getNode(1));
    endStatement(nested);
  }

  /** Visit the specified while statement node. */
  public void visitWhileStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("while (");
    formatAsTruthValue(n.getNode(0));
    printer.p(')');
    prepareNested();
    printer.p(n.getNode(1));
    endStatement(nested);
  }

  /** Visit the specified do statement node. */
  public void visitDoStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("do");
    prepareNested();
    printer.p(n.getNode(0));
    if (isOpenLine) {
      printer.p(' ');
    } else {
      printer.indent();
    }
    printer.p("while (");
    formatAsTruthValue(n.getNode(1));
    printer.pln(");");
    endStatement(nested);
  }

  /** Visit the specified for statement node. */
  public void visitForStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);

    printer.indent().p("for (");
    if (null != n.get(0)) {
      int prec = enterContext(PREC_BASE);
      printer.p(n.getNode(0));
      exitContext(prec);
    }
    printer.p(';');

    if (null != n.get(1)) {
      int prec = enterContext(PREC_BASE);
      printer.p(' ');
      formatAsTruthValue(n.getNode(1));
      exitContext(prec);
    }

    printer.p(';');
    if (null != n.get(2)) {
      int prec = enterContext(PREC_BASE);
      printer.p(' ').p(n.getNode(2));
      exitContext(prec);
    }
    printer.p(')');

    prepareNested();
    printer.p(n.getNode(3));

    endStatement(nested);
  }

  /** Visit the specified switch statement node. */
  public void visitSwitchStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("switch (").p(n.getNode(0)).p(')');
    prepareNested();
    printer.p(n.getNode(1));
    endStatement(nested);
  }

  /** Visit the specified break statement node. */
  public void visitBreakStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().pln("break;");
    endStatement(nested);
  }

  /** Visit the specified continue statement node. */
  public void visitContinueStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().pln("continue;");
    endStatement(nested);
  }

  /** Visit the specified return statement node. */
  public void visitReturnStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("return");
    if (null != n.getNode(0)) {
      printer.p(' ').p(n.getNode(0));
    }
    printer.pln(';');
    endStatement(nested);
  }

  /** Visit the specified goto statement node. */
  public void visitGotoStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("goto ");
    if (null == n.get(0)) {
      printer.p(n.getNode(1));
    } else {
      printer.p('*');
      int prec = enterContext(150);
      printer.p(n.getNode(1));
      exitContext(prec);
    }
    printer.pln(';');
    endStatement(nested);
  }

  /** Visit the specified expression statement node. */
  public void visitExpressionStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p(n.getNode(0)).pln(';');
    endStatement(nested);
  }

  /** Visit the specified empty statement node. */
  public void visitEmptyStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().pln(';');
    endStatement(nested);
  }

  /** Visit the specified comma expression node. */
  public void visitCommaExpression(GNode n) {
    int prec1 = startExpression(10);
    printer.p(n.getNode(0)).p(", ");

    int prec2 = enterContext();
    printer.p(n.getNode(1));
    exitContext(prec2);

    endExpression(prec1);
  }

  /** Visit the specified assignment expression node. */
  public void visitAssignmentExpression(GNode n) {
    int prec1 = startExpression(20);
    int prec2 = enterContext();
    printer.p(n.getNode(0));
    exitContext(prec2);

    printer.p(' ').p(n.getString(1)).p(' ').p(n.getNode(2));
    endExpression(prec1);
  }

  /** Visit the specified conditional expression node. */
  public void visitConditionalExpression(GNode n) {
    int prec1 = startExpression(30);

    int prec2 = enterContext();
    printer.p(n.getNode(0)).p(" ? ");
    exitContext(prec2);

    prec2 = enterContext();
    if (null != n.get(1)) {
      printer.p(n.getNode(1)).p(" : ");
    } else {
      printer.p(" /* Empty */ : ");
    }
    exitContext(prec2);

    printer.p(n.getNode(2));
    endExpression(prec1);
  }

  /** Visit the specified logical or expression node. */
  public void visitLogicalOrExpression(GNode n) {
    int     prec1  = startExpression(40);
    boolean paren1 = n.getGeneric(0).hasName("LogicalAndExpression");
    boolean paren2 = n.getGeneric(1).hasName("LogicalAndExpression");

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(" || ");

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(1)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(1));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified logical and expression node. */
  public void visitLogicalAndExpression(GNode n) {
    int prec1 = startExpression(50);
    printer.p(n.getNode(0)).p(" && ");

    int prec2 = enterContext();
    printer.p(n.getNode(1));
    exitContext(prec2);

    endExpression(prec1);
  }

  /** Visit the specified bitwise or expression node. */
  public void visitBitwiseOrExpression(GNode n) {
    int     prec1  = startExpression(60);
    GNode   op1    = n.getGeneric(0);
    boolean paren1 = (op1.hasName("AdditiveExpression") ||
                      op1.hasName("BitwiseAndExpression") ||
                      op1.hasName("BitwiseXorExpression") ||
                      op1.hasName("RelationalExpression") ||
                      op1.hasName("EqualityExpression"));
    GNode   op2    = n.getGeneric(1);
    boolean paren2 = (op2.hasName("AdditiveExpression") ||
                      op2.hasName("BitwiseAndExpression") ||
                      op2.hasName("BitwiseXorExpression") ||
                      op2.hasName("RelationalExpression") ||
                      op2.hasName("EqualityExpression"));

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(" | ");

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(1)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(1));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified bitwise xor expression node. */
  public void visitBitwiseXorExpression(GNode n) {
    int     prec1  = startExpression(70);
    GNode   op1    = n.getGeneric(0);
    boolean paren1 = (op1.hasName("AdditiveExpression") ||
                      op1.hasName("BitwiseAndExpression") ||
                      op1.hasName("RelationalExpression") ||
                      op1.hasName("EqualityExpression"));
    GNode   op2    = n.getGeneric(1);
    boolean paren2 = (op2.hasName("AdditiveExpression") ||
                      op2.hasName("BitwiseAndExpression") ||
                      op2.hasName("RelationalExpression") ||
                      op2.hasName("EqualityExpression"));

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(" ^ ");

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(1)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(1));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified bitwise and expression node. */
  public void visitBitwiseAndExpression(GNode n) {
    int     prec1  = startExpression(80);
    GNode   op1    = n.getGeneric(0);
    boolean paren1 = (op1.hasName("AdditiveExpression") ||
                      op1.hasName("RelationalExpression") ||
                      op1.hasName("EqualityExpression"));
    GNode   op2    = n.getGeneric(1);
    boolean paren2 = (op2.hasName("AdditiveExpression") ||
                      op2.hasName("RelationalExpression") ||
                      op2.hasName("EqualityExpression"));

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(" & ");

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(1)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(1));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified equality expression node. */
  public void visitEqualityExpression(GNode n) {
    int prec1 = startExpression(90);
    GNode   op1    = n.getGeneric(0);
    boolean paren1 = (op1.hasName("RelationalExpression") ||
                      op1.hasName("EqualityExpression"));
    GNode   op2    = n.getGeneric(2);
    boolean paren2 = (op2.hasName("RelationalExpression") ||
                      op2.hasName("EqualityExpression"));

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(' ').p(n.getString(1)).p(' ');

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(2)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(2));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified relational expression node. */
  public void visitRelationalExpression(GNode n) {
    int     prec1  = startExpression(100);
    GNode   op1    = n.getGeneric(0);
    boolean paren1 = (op1.hasName("RelationalExpression") ||
                      op1.hasName("EqualityExpression"));
    GNode   op2    = n.getGeneric(2);
    boolean paren2 = (op2.hasName("RelationalExpression") ||
                      op2.hasName("EqualityExpression"));

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(' ').p(n.getString(1)).p(' ');

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(2)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(2));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified shift expression node. */
  public void visitShiftExpression(GNode n) {
    int     prec1  = startExpression(110);
    boolean paren1 = n.getGeneric(0).hasName("AdditiveExpression");
    boolean paren2 = n.getGeneric(2).hasName("AdditiveExpression");

    if (EXTRA_PARENTHESES && paren1) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(0)).p(')');
    } else {
      printer.p(n.getNode(0));
    }

    printer.p(' ').p(n.getString(1)).p(' ');

    if (EXTRA_PARENTHESES && paren2) {
      // Force parentheses to make gcc happy.
      printer.p('(').p(n.getNode(2)).p(')');
    } else {
      int prec2 = enterContext();
      printer.p(n.getNode(2));
      exitContext(prec2);
    }

    endExpression(prec1);
  }

  /** Visit the specified additive expression node. */
  public void visitAdditiveExpression(GNode n) {
    int prec1 = startExpression(120);
    printer.p(n.getNode(0)).p(' ').p(n.getString(1)).p(' ');

    int prec2 = enterContext();
    printer.p(n.getNode(2));
    exitContext(prec2);

    endExpression(prec1);
  }

  /** Visit the specified multiplicative expression node. */
  public void visitMultiplicativeExpression(GNode n) {
    int prec1 = startExpression(130);
    printer.p(n.getNode(0)).p(' ').p(n.getString(1)).p(' ');

    int prec2 = enterContext();
    printer.p(n.getNode(2));
    exitContext(prec2);

    endExpression(prec1);
  }

  /** Visit the specified cast expression node. */
  public void visitCastExpression(GNode n) {
    int prec = startExpression(140);
    printer.p('(').p(n.getNode(0)).p(')').p(n.getNode(1));
    endExpression(prec);
  }

  /** Visit the specified sizeof expression node. */
  public void visitSizeofExpression(GNode n) {
    int prec  = startExpression(150);
    int prec2 = enterContext(PREC_BASE);
    printer.p("sizeof(").p(n.getNode(0)).p(')');
    exitContext(prec2);
    endExpression(prec);
  }

  /** Visit the specified alignof expression node. */
  public void visitAlignofExpression(GNode n) {
    int prec  = startExpression(150);
    int prec2 = enterContext(PREC_BASE);
    printer.p("__alignof__(").p(n.getNode(0)).p(')');
    exitContext(prec2);
    endExpression(prec);
  }

  /** Visit the specified offsetof expression node. */
  public void visitOffsetofExpression(GNode n) {
    int prec = startExpression(160);
    printer.p("__builtin_offsetof(").p(n.getNode(0)).p(", ").p(n.getNode(1)).
      p(')');
    endExpression(prec);
  }

  /** Visit the specified type compatability expression. */
  public void visitTypeCompatibilityExpression(GNode n) {
    int prec  = startExpression(150);
    printer.p("__builtin_types_compatible_p(");
    int prec2 = enterContext(PREC_BASE);
    printer.p(n.getNode(0));
    exitContext(prec2);
    prec2     = enterContext(PREC_BASE);
    printer.p(", ").p(n.getNode(1)).p(')');
    exitContext(prec2);
    endExpression(prec);
  }

  /** Visit the specified unary minus expression node. */
  public void visitUnaryMinusExpression(GNode n) {
    int   prec = startExpression(150);
    GNode e    = n.getGeneric(0);
    if (e.hasName("UnaryMinusExpression") ||
        e.hasName("PredecrementExpression")) {
      printer.p("-(").p(n.getNode(0)).p(')');
    } else {
      printer.p('-').p(n.getNode(0));
    }
    endExpression(prec);
  }

  /** Visit the specified unary plus expression node. */
  public void visitUnaryPlusExpression(GNode n) {
    int   prec = startExpression(150);
    GNode e    = n.getGeneric(0);
    if (e.hasName("UnaryPlusExpression") ||
        e.hasName("PreincrementExpression")) {
      printer.p("+(").p(n.getNode(0)).p(')');
    } else {
      printer.p('+').p(n.getNode(0));
    }
    endExpression(prec);
  }

  /** Visit the specified logical negation expression node. */
  public void visitLogicalNegationExpression(GNode n) {
    int prec = startExpression(150);
    printer.p('!').p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the specified bitwise negation expression node. */
  public void visitBitwiseNegationExpression(GNode n) {
    int prec = startExpression(150);
    printer.p('~').p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the specified address expression node. */
  public void visitAddressExpression(GNode n) {
    int   prec = startExpression(150);
    GNode e    = n.getGeneric(0);
    if (e.hasName("AddressExpression") ||
        e.hasName("LabelAddressExpression")) {
      printer.p("&(").p(n.getNode(0)).p(')');
    } else {
      printer.p('&').p(n.getNode(0));
    }
    endExpression(prec);
  }

  /** Visit the specified label address expression node. */
  public void visitLabelAddressExpression(GNode n) {
    int prec = startExpression(150);
    printer.p("&&").p(n.getString(0));
    endExpression(prec);
  }

  /** Visit the specified indirection expression node. */
  public void visitIndirectionExpression(GNode n) {
    int prec = startExpression(150);
    printer.p('*').p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the specified preincrement expression node. */
  public void visitPreincrementExpression(GNode n) {
    int prec = startExpression(150);
    printer.p("++").p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the specified predecrement expression node. */
  public void visitPredecrementExpression(GNode n) {
    int prec = startExpression(150);
    printer.p("--").p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the extension expression node. */
  public void visitExtensionExpression(GNode n) {
    int prec = startExpression(150);
    printer.p("__extension__ ").p(n.getNode(0));
    endExpression(prec);
  }

  /** Visit the specified subscript expression node. */
  public void visitSubscriptExpression(GNode n) {
    int prec1  = startExpression(160);
    printer.p(n.getNode(0));
    int prec2  = enterContext(PREC_BASE);
    printer.p('[').p(n.getNode(1)).p(']');
    exitContext(prec2);
    endExpression(prec1);
  }

  /** Visit the specified direct component selection node. */
  public void visitDirectComponentSelection(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getNode(0)).p('.').p(n.getString(1));
    endExpression(prec);
  }

  /** Visit the specified indirect component selection node. */
  public void visitIndirectComponentSelection(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getNode(0)).p("->").p(n.getString(1));
    endExpression(prec);
  }

  /** Visit the specified function call node. */
  public void visitFunctionCall(GNode n) {
    int  prec = startExpression(160);
    printer.p(n.getNode(0)).p('(').p(n.getNode(1)).p(')');
    endExpression(prec);
  }

  /** Visit the specified expression list node. */
  public void visitExpressionList(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      int prec = enterContext(PREC_LIST);
      printer.p((Node)iter.next());
      exitContext(prec);
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified postincrement expression node. */
  public void visitPostincrementExpression(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getNode(0)).p("++");
    endExpression(prec);
  }

  /** Visit the specified postdecrement expression node. */
  public void visitPostdecrementExpression(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getNode(0)).p("--");
    endExpression(prec);
  }

  /** Visit the specified compound literal node. */
  public void visitCompoundLiteral(GNode n) {
    int prec = startExpression(160);
    printer.p('(').p(n.getNode(0)).p(") ").p(n.getNode(1));
    endExpression(prec);
  }

  /** Visit the specified primary identifier node. */
  public void visitPrimaryIdentifier(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getString(0));
    endExpression(prec);
  }

  /** Visit the specified statement as exprression node. */
  public void visitStatementAsExpression(GNode n) {
    int     prec       = enterContext(PREC_BASE);
    boolean stmtAsExpr = isStmtAsExpr;
    isStmtAsExpr       = true;
    prepareNested();
    printer.p(n.getNode(0));
    isStmtAsExpr       = stmtAsExpr;
    exitContext(prec);
  }

  /** Visit the specified variable argument access node. */
  public void visitVariableArgumentAccess(GNode n) {
    int prec  = startExpression(160);
    printer.p("__builtin_va_arg(");
    int prec2 = enterContext(PREC_LIST);
    printer.p(n.getNode(0));
    exitContext(prec2);
    printer.p(", ").p(n.getNode(1)).p(')');
    endExpression(prec);
  }

  /** Visit the specified assembly definition node. */
  public void visitAssemblyDefinition(GNode n) {
    if (lineUp) {
      if (isOpenLine) printer.pln();
      printer.lineUp(n);
    } else if (isStatement || isDeclaration || isLongDecl) {
      if (isOpenLine) printer.pln();
      printer.pln();
    }

    printer.p(n.getNode(0)).pln(';');

    isDeclaration = false;
    isLongDecl    = false;
    isStatement   = false;
    isOpenLine    = false;
    isNested      = false;
    isIfElse      = false;
  }

  /** Visit the specified simple assembly expression node. */
  public void visitSimpleAssemblyExpression(GNode n) {
    int prec = enterContext(PREC_BASE);
    printer.p("asm(").p(n.getNode(0)).p(')');
    exitContext(prec);
  }

  /** Visit the specified assembly statement node. */
  public void visitAssemblyStatement(GNode n) {
    boolean nested = startStatement(STMT_ANY, n);
    printer.indent().p("asm ");
    if (null != n.getNode(0)) {
      printer.p(n.getNode(0)).p(' ');
    }
    printer.p('(').p(n.getNode(1)).pln(");");
    endStatement(nested);
  }

  /** Visit the specified assembly argument node. */
  public void visitAssemblyArgument(GNode n) {
    final int prec   = enterContext(PREC_BASE);
    final int number = n.size();
    final int align  = printer.column();
    printer.p(n.getNode(0));
    if (number >= 2) {
      if (null == n.get(1)) {
        printer.pln().align(align).p(": /* No output operands */");
      } else {
        printer.pln().align(align).p(": ").p(n.getNode(1));
      }

      if (number >= 3) {
        if (null == n.get(2)) {
          printer.pln().align(align).p(": /* No input operands */");
        } else {
          printer.pln().align(align).p(": ").p(n.getNode(2));
        }

        if (number == 4) {
          printer.pln().align(align).p(": ").p(n.getNode(3));
        }
      }
    }
    exitContext(prec);
  }

  /** Visit the specified assembly operands node. */
  public void visitAssemblyOperands(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified assembly operand node. */
  public void visitAssemblyOperand(GNode n) {
    if (null != n.get(0)) {
      printer.p('[').p(n.getString(0)).p("] ");
    }
    printer.p(n.getNode(1)).p(" (").p(n.getNode(2)).p(')');
  }

  /** Visit the specified assembly clobbers node. */
  public void visitAssemblyClobbers(GNode n) {
    for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
      printer.p((Node)iter.next());
      if (iter.hasNext()) {
        printer.p(", ");
      }
    }
  }

  /** Visit the specified floating constant node. */
  public void visitFloatingConstant(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getString(0));
    endExpression(prec);
  }

  /** Visit the specified integer constant node. */
  public void visitIntegerConstant(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getString(0));
    endExpression(prec);
  }

  /** Visit the specified character constant node. */
  public void visitCharacterConstant(GNode n) {
    int prec = startExpression(160);
    printer.p(n.getString(0));
    endExpression(prec);
  }

  /** Visit the specified string constant node. */
  public void visitStringConstant(GNode n) {
    int prec = startExpression(160);

    if (1 == n.size()) {
      printer.p(n.getString(0));

    } else {
      int align = printer.column();
      for (Iterator<?> iter = n.iterator(); iter.hasNext(); ) {
        printer.p(Token.cast(iter.next()));
        if (iter.hasNext()) {
          printer.pln().align(align);
        }
      }
    }

    endExpression(prec);
  }

  /** Visit the specified line marker. */
  public void visit(LineMarker mark) {
    if (isOpenLine) {
      isOpenLine = false;
      printer.pln();
    }
    if (lineUp) printer.lineUp(mark);

    printer.p("# ").p(mark.line).p(" \"").p(mark.file).p('\"');
    if (0 != (mark.flags & LineMarker.FLAG_START_FILE)) {
      printer.p(" 1");
    }
    if (0 != (mark.flags & LineMarker.FLAG_RETURN_TO_FILE)) {
      printer.p(" 2");
    }
    if (0 != (mark.flags & LineMarker.FLAG_SYSTEM_HEADER)) {
      printer.p(" 3");
    }
    if (0 != (mark.flags & LineMarker.FLAG_EXTERN_C)) {
      printer.p(" 4");
    }
    printer.pln().p(mark.getNode());
  }

  /** Visit the specified pragma. */
  public void visit(Pragma p) {
    if (isOpenLine) {
      isOpenLine = false;
      printer.pln();
    }
    if (lineUp) printer.lineUp(p);

    printer.p("#pragma ").pln(p.directive).p(p.getNode());
  }

  /** Visit the specified source identity marker. */
  public void visit(SourceIdentity ident) {
    if (isOpenLine) {
      isOpenLine = false;
      printer.pln();
    }
    if (lineUp) printer.lineUp(ident);

    printer.p("#ident \"").p(ident.ident).pln('"').p(ident.getNode());
  }

}
