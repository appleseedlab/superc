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

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Set;

import xtc.Constants;

import xtc.util.Utilities;

import xtc.tree.Attribute;
import xtc.tree.Node;
import xtc.tree.Visitor;

/** 
 * Visitor to check a grammar for consistency.  This visitor should be
 * applied on a grammar right after parsing, before any other
 * visitors.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public class Checker extends Visitor {
  
  /** The analyzer utility. */
  protected final Analyzer analyzer;

  /** The source file, one line per array entry. */
  protected String[] source;

  /** Flag for whether we have seen an error. */
  protected boolean error;

  /** Flag for whether we are currently processing a predicate. */
  protected boolean predicate;

  /**
   * Create a new checker.
   *
   * @param analyzer The analyzer utility for the new checker.
   */
  public Checker(Analyzer analyzer) {
    this.analyzer = analyzer;
  }

  /**
   * Print the specified error message. Calling this method also sets
   * the error flag.
   *
   * @param msg The error message.
   * @param n The offending node.
   */
  protected void msg(String msg, Node n) {
    String context = (null != analyzer.current())?
      analyzer.current().nonTerminal.name : null;
    System.err.println();
    Utilities.msg(msg, n.location, context, source);
    error = true;
  }

  /**
   * Analyze the specified grammar. This method returns a boolean flag
   * indicating whether the grammar contains errors.
   */
  public Boolean visit(Grammar g) {
    // (Re)initialize the per-grammar state.
    LeftRecurser recurser  = new LeftRecurser(analyzer);
    g.accept(recurser);
    Set          recursive = recurser.recursive();

    source                 = (String[])g.getProperty(Constants.SOURCE);
    error                  = false;
    predicate              = false;

    // (Re)initialize the analyzer.
    analyzer.register(this);
    analyzer.init(g);

    // Check attributes (or, options).
    if (null != g.attributes) {
      int length = g.attributes.size();
      for (int i=0; i<length; i++) {
        Attribute att = (Attribute)g.attributes.get(i);

        if ((! CodeGenerator.ATT_LOCATION.equals(att.name)) &&
            (! CodeGenerator.ATT_CONSTANT_BINDING.equals(att.name)) &&
            (! CodeGenerator.ATT_DEBUG.equals(att.name)) &&
            (! CodeGenerator.ATT_NO_MATCHING_ERRORS.equals(att.name))) {
          msg("unrecognized option " + att.name, att);

        } else {
          for (int j=0; j<i; j++) {
            if (att.equals(g.attributes.get(j))) {
              msg("duplicate option " + att.name, att);
              break;
            }
          }
        }
      }
    }

    // Check the top-level declarations.
    int length = g.topLevel.size();
    for (int i=0; i<length; i++) {
      NonTerminal nt = (NonTerminal)g.topLevel.get(i);

      if (! analyzer.isDefined(nt)) {
        msg("undefined top-level nonterminal " + nt.name, nt);

      } else if (Type.isVoidT(analyzer.lookup(nt).type)) {
        msg("void top-level nonterminal " + nt.name, nt);

      } else {
        for (int j=0; j<i; j++) {
          if (nt.equals(g.topLevel.get(j))) {
            msg("duplicate top-level nonterminal " + nt.name, nt);
            break;
          }
        }
      }
    }

    // Check the actual productions.
    length = g.productions.size();
    for (int i=0; i<length; i++) {
      Production p = (Production)g.productions.get(i);

      // Check the production's elements.
      analyzer.process(p);

      // Check for left-recursive definitions.
      if (recursive.contains(p.nonTerminal)) {
        msg("left-recursive definition for nonterminal " + p.nonTerminal.name,
            p);
      }

      // Check for duplicate definitions.
      for (int j=0; j<i; j++) {
        Production p2 = (Production)g.productions.get(j);

        if (p.nonTerminal.equals(p2.nonTerminal)) {
          msg("duplicate definition for nonterminal " + p.nonTerminal.name,
              p);
          break;
        }
      }
    }

    // Error check.
    return (error)? Boolean.TRUE : Boolean.FALSE;
  }

  /** Analyze the specified production. */
  public void visit(Production p) {
    if (Type.isPrimitive(p.type)) {
      msg("primitive type " + p.type + " for production " + p.nonTerminal.name,
          p);
    }
    p.element.accept(this);
  }
  
  /** Analyze the specified ordered choice. */
  public void visit(OrderedChoice c) {
    Iterator iter = c.options.iterator();
    while (iter.hasNext()) {
      ((Element)iter.next()).accept(this);
    }
  }

  /** Analyze the specified repetition. */
  public void visit(Repetition r) {
    if (analyzer.strip(r.element) instanceof Action) {
      msg("repeated action", r);
    }
    r.element.accept(this);
  }

  /** Analyze the specified option.  */
  public void visit(Option o) {
    if (analyzer.strip(o.element) instanceof Action) {
      msg("optional action", o);
    }
    o.element.accept(this);
  }
  
  /** Analyze the specified sequence. */
  public void visit(Sequence s) {
    Iterator iter = s.elements.iterator();
    while (iter.hasNext()) {
      ((Element)iter.next()).accept(this);
    }
  }

  /** Analyze the specified predicate. */
  public void visit(Predicate p) {
    if (predicate) {
      msg("syntactic predicate within syntactic predicate", p);
    }

    boolean pred = predicate;
    predicate    = true;
    p.element.accept(this);
    predicate    = pred;
  }

  /** Analyze the specified semantic predicate. */
  public void visit(SemanticPredicate p ) {
    if (! (p.element instanceof Action)) {
      msg("malformed semantic predicate", p);
    } else {
      Action a = (Action)p.element;
      if ((null == a.code) || (0 >= a.code.size())) {
        msg("empty test for semantic predicate", p);
      }
    }

    p.element.accept(this);
  }

  /** Analyze the specified binding. */
  public void visit(Binding b) {
    Element bound = analyzer.strip(b.element);

    if (bound instanceof Sequence) {
      msg("binding for sequence", b);

    } else if (bound instanceof NonTerminal) {
      NonTerminal nt = (NonTerminal)bound;
      Production  p  = analyzer.lookup(nt);

      if ((null != p) && Type.isVoidT(p.type)) {
        msg("binding for void nonterminal " + nt.name, b);
      }

    } else if (bound instanceof Action) {
      msg("binding for action", b);
    }
 
   b.element.accept(this);
  }

  /** Analyze the specified string match. */
  public void visit(StringMatch m) {
    Element matched = analyzer.strip(m.element);

    if (matched instanceof Sequence) {
      msg("match for sequence", m);

    } else if (matched instanceof NonTerminal) {
      NonTerminal nt = (NonTerminal)matched;
      Production  p  = analyzer.lookup(nt);

      if ((null != p) && Type.isVoidT(p.type)) {
        msg("match for void nonterminal " + nt.name, m);
      }

    } else if (matched instanceof Terminal) {
      msg("match for terminal", m);

    } else if (matched instanceof Action) {
      msg("match for action", m);
    }

    m.element.accept(this);
  }
  
  /** Analyze the specified nonterminal. */
  public void visit(NonTerminal nt) {
    if (! analyzer.isDefined(nt)) {
      msg("undefined nonterminal " + nt.name, nt);
    }
  }

  /** Analyze the specified terminal. */
  public void visit(Terminal t) {
    // Nothing to do.
  }

  /** Analyze the specified string literal. */
  public void visit(StringLiteral l) {
    if (0 == l.text.length()) {
      msg("empty string literal", l);
    }
  }

  /** Analyze the specified character class. */
  public void visit(CharClass c) {
    final int length = c.ranges.size();

    if (0 >= length) {
      msg("empty character class", c);

    } else {
      ArrayList list = new ArrayList(c.ranges);
      Collections.sort(list);

      for (int i=0; i<length-1; i++) {
        CharRange r1 = (CharRange)list.get(i);
        CharRange r2 = (CharRange)list.get(i+1);
        
        if (r1.last >= r2.first) {
          boolean single1 = (r1.first == r1.last);
          boolean single2 = (r2.first == r2.last);

          if (single1) {
            if (single2) {
              msg("duplicate character \'" +
                  Utilities.escape(r1.last, Utilities.FULL_ESCAPES) +
                  "\' in character class", c);
            } else {
              msg("character \'" +
                  Utilities.escape(r1.last, Utilities.FULL_ESCAPES) +
                  "\' already contained in range " +
                  Utilities.escape(r2.first, Utilities.FULL_ESCAPES) +
                  "-" + Utilities.escape(r2.last, Utilities.FULL_ESCAPES), c);
            }
          } else {
            if (single2) {
              msg("character \'" +
                  Utilities.escape(r2.first, Utilities.FULL_ESCAPES) +
                  "\' already contained in range " +
                  Utilities.escape(r1.first, Utilities.FULL_ESCAPES) +
                  "-" + Utilities.escape(r1.last, Utilities.FULL_ESCAPES), c);
            } else {
              msg("ranges " +
                  Utilities.escape(r1.first, Utilities.FULL_ESCAPES) +
                  "-" + Utilities.escape(r1.last, Utilities.FULL_ESCAPES) +
                  " and " +
                  Utilities.escape(r2.first, Utilities.FULL_ESCAPES) +
                  "-" + Utilities.escape(r2.last, Utilities.FULL_ESCAPES) +
                  " overlap", c);
            }
          }
        }
      }
    }
  }

  /** Analyze the specified action. */
  public void visit(Action a) {
    // Nothing to do.
  }

  /** Analyze the specified internal element. */
  public void visit(InternalElement e) {
    msg("internal element", (Element)e);
  }

}
