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
package xtc.parser;

import java.util.Iterator;
import java.util.List;

import xtc.Constants;

import xtc.util.Utilities;

import xtc.tree.Printer;
import xtc.tree.Visitor;

/**
 * The grammar pretty printer.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public class PrettyPrinter extends Visitor {

  /** Flag for whether to explicitly mark choices. */
  public static final boolean MARK_CHOICE = true;

  /** The printer for this pretty printer. */
  protected final Printer printer;

  /** Flag for whether the last element ended in a newline. */
  protected boolean newline;

  /** Flag for whether the next ordered choice needs to be parenthesized. */
  protected boolean parenChoice;

  /** Flag for whether the next sequence element needs to be parenthesized. */
  protected boolean parenSequence;

  /**
   * Create a new pretty printer.
   *
   * @param printer The printer for the new pretty printer.
   */
  public PrettyPrinter(Printer printer) {
    this.printer = printer;
    printer.register(this);
  }

  /** Print the specified grammar. */
  public void visit(Grammar g) {
    // Emit header.
    printer.sep();
    printer.indent().p("// xtc ").pln(Constants.VERSION);
    printer.indent().pln("// Packrat grammar pretty printer");
    printer.sep();
    printer.pln();

    boolean printed = false;

    // Emit package name.
    if (null != g.pName) {
      printed = true;
      printer.indent().p("package ").p(g.pName).pln(';');
      printer.pln();
    }

    // Emit header.
    if (null != g.header) {
      printed = true;
      printer.indent().p("header ");
      g.header.accept(this);
      printer.pln();
    }

    // Emit class name.
    if (! Grammar.DEFAULT_NAME.equals(g.cName)) {
      printed = true;
      printer.indent().p("class ").p(g.cName).pln(';');
      printer.pln();
    }

    // Emit main action.
    if (null != g.body) {
      printed = true;
      printer.indent().p("body ");
      g.body.accept(this);
      printer.pln();
    }

    // Emit footer.
    if (null != g.footer) {
      printed = true;
      printer.indent().p("footer ");
      g.footer.accept(this);
      printer.pln();
    }

    if (printed) {
      printer.sep();
      printer.pln();
    }

    // Emit the top-level nonterminals. */
    printer.indent().p("top ");
    Iterator iter  = g.topLevel.iterator();
    boolean  first = true;
    while (iter.hasNext()) {
      if (first) {
        first = false;
      } else {
        printer.p(", ");
      }
      ((NonTerminal)iter.next()).accept(this);
    }
    printer.pln(';').pln();

    // Emit the productions.
    iter = g.productions.iterator();
    while (iter.hasNext()) {
      ((Production)iter.next()).accept(this);
    }
    printer.sep().pln();
  }

  /** Print the specified production. */
  public void visit(Production p) {
    if (p.hasProperty(DuplicateProductionFolder.DUPLICATES)) {
      List sources = (List)p.getProperty(DuplicateProductionFolder.DUPLICATES);
      printer.indent().pln("/*");
      printer.indent().p(" * The following production is the result of ").
        pln("folding duplicates");
      printer.indent().p(" * ").pln(Utilities.format(sources));
      printer.indent().pln(" */");
    }
    printer.indent();
    if (p.isTransient) {
      printer.p("transient ");
    }
    printer.p(p.type).p(' ');
    p.nonTerminal.accept(this);
    printer.p(" = ");

    parenChoice   = false;
    parenSequence = false;

    p.element.accept(this);
    printer.incr().indent().pln(';').decr();
    printer.pln();
  }

  /** Print the specified ordered choice. */
  public void visit(OrderedChoice c) {
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    if (choice) {
      printer.p("( ");
    }
    if (MARK_CHOICE) {
      printer.p("/* Choice */ ");
    }
    printer.pln().incr();

    Iterator iter        = c.options.iterator();
    boolean  firstOption = true;
    while (iter.hasNext()) {
      if (firstOption) {
        firstOption = false;
        printer.indent();

      } else {
        printer.indent().p("/ ");
      }

      parenChoice   = true;
      parenSequence = false;
      newline       = false;
      ((Element)iter.next()).accept(this);

      if (! newline) {
        printer.pln();
      }
    }

    printer.decr();
    if (choice) {
      printer.indent().p(')');
    }

    parenChoice   = choice;
    parenSequence = sequence;
    newline       = false;
  }

  /** Print the specified repetition. */
  public void visit(Repetition r) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;

    r.element.accept(this);
    if (r.once) {
      printer.p('+');
    } else {
      printer.p('*');
    }

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified option. */
  public void visit(Option o) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;

    o.element.accept(this);
    printer.p('?');

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified sequence. */
  public void visit(Sequence s) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;

    Iterator iter  = s.elements.iterator();
    boolean  first = true;
    while (iter.hasNext()) {
      if (first) {
        first = false;
        if (sequence) {
          printer.p('(');
        }
      } else {
        printer.p(' ');
      }
      ((Element)iter.next()).accept(this);
    }
    if (sequence) {
      printer.p(')');
    }

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified followed-by element. */
  public void visit(FollowedBy p) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;
    
    printer.p('&');
    p.element.accept(this);

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified not-followed-by element. */
  public void visit(NotFollowedBy p) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;
    
    printer.p('!');
    p.element.accept(this);

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified semantic predicate. */
  public void visit(SemanticPredicate p) {
    if (newline) printer.indent();
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    newline          = false;
    parenChoice      = true;
    parenSequence    = true;
    
    printer.p('&');
    p.element.accept(this);

    parenChoice      = choice;
    parenSequence    = sequence;
  }

  /** Print the specified binding. */
  public void visit(Binding b) {
    if (newline) printer.indent();
    newline = false;
    printer.p(b.name).p(':');
    b.element.accept(this);
  }

  /** Print the specified string match. */
  public void visit(StringMatch m) {
    if (newline) printer.indent();
    newline = false;
    printer.p('\"').escape(m.text, Utilities.JAVA_ESCAPES).p("\":");
    m.element.accept(this);
  }

  /** Print the specified nonterminal. */
  public void visit(NonTerminal nt) {
    if (newline) printer.indent();
    newline = false;
    printer.p(nt.name);
  }

  /** Print the specified string literal. */
  public void visit(StringLiteral l) {
    if (newline) printer.indent();
    newline = false;
    printer.p('\"').escape(l.text, Utilities.JAVA_ESCAPES).p('\"');
  }

  /** Print the specified any character element. */
  public void visit(AnyChar a) {
    if (newline) printer.indent();
    newline = false;
    printer.p('.');
  }

  /** Print the specified character literal. */
  public void visit(CharLiteral l) {
    if (newline) printer.indent();
    newline = false;
    printer.p('\'').escape(l.c, Utilities.JAVA_ESCAPES).p('\'');
  }

  /** Print the specified character range. */
  public void visit(CharRange r) {
    if (newline) printer.indent();
    newline  = false;
    if (r.first == r.last) {
      printer.escape(r.first, Utilities.FULL_ESCAPES);
    } else {
      printer.escape(r.first, Utilities.FULL_ESCAPES).p('-').
        escape(r.last, Utilities.FULL_ESCAPES);
    }
  }

  /** Print the specified character class. */
  public void visit(CharClass c) {
    if (newline) printer.indent();
    newline = false;
    if (c.exclusive) {
      printer.p("/* Exclusive */ !");
    }
    printer.p('[');
    Iterator iter = c.ranges.iterator();
    while (iter.hasNext()) {
      ((CharRange)iter.next()).accept(this);
    }
    printer.p(']');
    if (c.exclusive) {
      printer.p(" .");
    }
  }

  /** Print the specified character case. */
  public void visit(CharCase c) {
    if (newline) printer.indent();
    newline = false;

    c.klass.accept(this);
    printer.p(' ');
    if (null == c.element) {
      printer.p("&{ false }");
    } else {
      c.element.accept(this);
    }
  }

  /** Print the specified character switch. */
  public void visit(CharSwitch s) {
    boolean choice   = parenChoice;
    boolean sequence = parenSequence;

    printer.pln("( /* Switch */").incr();

    Iterator iter      = s.cases.iterator();
    boolean  firstCase = true;
    while (iter.hasNext()) {
      if (firstCase) {
        firstCase = false;
        printer.indent();

      } else {
        printer.indent().p("/ ");
      }

      parenChoice   = true;
      parenSequence = false;
      newline       = false;
      ((CharCase)iter.next()).accept(this);

      if (! newline) {
        printer.pln();
      }
    }

    if (null != s.base) {
      printer.indent().p("/ . ");
      parenChoice   = true;
      parenSequence = false;
      newline       = false;
      s.base.accept(this);

      if (! newline) {
        printer.pln();
      }
    }

    printer.decr().indent().p(')');

    parenChoice   = choice;
    parenSequence = sequence;
    newline       = false;
  }

  /** Print the specified action. */
  public void visit(Action a) {
    if (newline) printer.indent();
    if (0 == a.code.size()) {
      // Nothing to do.
      newline = false;

    } else if (1 == a.code.size()) {
      newline = false;
      printer.p("{ ").p((String)a.code.get(0)).p(" }");

    } else {
      newline = true;
      printer.pln('{').incr();
      Iterator iter = a.code.iterator();
      while (iter.hasNext()) {
        printer.indent().pln((String)iter.next());
      }
      printer.decr().indent().pln('}');
    }
  }

  /** Print the specified null value. */
  public void visit(NullValue v) {
    if (newline) printer.indent();
    newline  = false;
    printer.p("/* value = null; */");
  }

  /** Print the specified string value. */
  public void visit(StringValue v) {
    if (newline) printer.indent();
    if (-1 == v.text.indexOf("*/")) {
      newline = false;
      printer.p("/* value = \"").escape(v.text, Utilities.JAVA_ESCAPES).
        p("\"; */");
    } else {
      // The string value contains the end sequence for a traditional
      // C comment.  We need to use a C++ comment.
      newline = true;
      printer.p("// value = \"").escape(v.text, Utilities.JAVA_ESCAPES).
        pln("\";");
    }
  }

  /** Print the specified text value. */
  public void visit(TextValue v) {
    if (newline) printer.indent();
    newline  = false;
    printer.p("/* value = <text>; */");
  }

  /** Print the specified empty list value. */
  public void visit(EmptyListValue v) {
    if (newline) printer.indent();
    newline  = false;
    printer.p("/* value = []; */");
  }

  /** Print the specified singleton list value. */
  public void visit(SingletonListValue v) {
    if (newline) printer.indent();
    newline  = false;
    printer.p("/* value = [").p(v.value).p("]; */");
  }

  /** Print the specified list value. */
  public void visit(ListValue v) {
    if (newline) printer.indent();
    newline  = false;
    printer.p("/* value = ").p(v.value).p(':').p(v.list).p("; */");
  }

}
