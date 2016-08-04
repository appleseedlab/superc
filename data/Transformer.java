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
import java.util.Iterator;
import java.util.List;

import xtc.tree.Visitor;

/**
 * Visitor to transform productions.  This visitor lifts repetitions,
 * options, and nested choices into their own productions, desugars
 * reptitions and options, and adds the appropriate semantic values to
 * expressions that require them.  It also ensures that all options
 * and syntactic predicates are sequences, thus fullfilling the
 * requirements for {@link CodeGenerator code generation}.  Before
 * applying this visitor on a grammar, the grammar must have been
 * {@link Simplifier simplified} and all text-only productions should
 * be marked as such by applying the {@link TextTester} visitor.
 *
 * @author Robert Grimm
 * @version $Revision: 1.2 $
 */
public class Transformer extends Visitor {

  /** The analyzer utility. */
  protected final Analyzer analyzer;

  /** The flag for whether the current production is text-only. */
  protected boolean isTextOnly;

  /** The flag for whether the current production is void. */
  protected boolean isVoid;

  /** The flag for whether the current element is top-level. */
  protected boolean isTopLevel;

  /**
   * The flag for whether to transform ordered choices, repetition,
   * and options in place, instead of creating a new production.
   */
  protected boolean transformInPlace;

  /**
   * The flag for whether the current element is the last element in a
   * sequence.
   */
  protected boolean isLastElement;

  /** The flag for whether we are currently processing a predicate. */
  protected boolean isPredicate;

  /** The flag for whether the current element is bound. */
  protected boolean isBound;

  /**
   * Create a new transformer.
   *
   * @param analyzer The analyzer utility for the new transformer.
   */
  public Transformer(Analyzer analyzer) {
    this.analyzer = analyzer;
  }

  /**
   * Determine whether the current production may contain repetitions.
   * A production may contain repetitions if it is transient void or
   * transient text-only and if the corresponding optimization option
   * ("<code>-Orepeated</code>") is set.
   */
  protected boolean repeatable() {
    return (Rats.optimizeRepeated &&
            analyzer.current().isTransient &&
            (isVoid || isTextOnly));
  }

  /** Visit the specified grammar. */
  public void visit(Grammar g) {
    // Initialize the per-grammar state.
    analyzer.register(this);
    analyzer.init(g);

    // Now, process the productions.
    for (int i=0; i<g.productions.size(); i++) {
      Production p = (Production)g.productions.get(i);

      // Initialize the per-production state.
      isTextOnly       = TextTester.isTextOnly(p);
      isVoid           = Type.isVoidT(p.type);
      transformInPlace = false;
      isTopLevel       = true;
      isLastElement    = false;
      isPredicate      = false;
      isBound          = false;

      // Process the production.
      analyzer.startAdding();
      analyzer.process(p);

      // If there are new productions, add them to the grammar and
      // make sure they are not processed again.
      i += analyzer.addNewProductionsAt(i+1);
    }
  }

  /** Visit the specified production. */
  public void visit(Production p) {
    // Note that we initialize all per-production state within the
    // visit() method for the grammar.
    p.element = (Element)p.element.accept(this);
  }

  /** Visit the specified ordered choice. */
  public Element visit(OrderedChoice c) {
    boolean top      = isTopLevel;
    isTopLevel       = false;
    boolean last     = isLastElement;
    isLastElement    = false;
    boolean bound    = isBound;
    isBound          = false;
    boolean inPlace  = transformInPlace;
    transformInPlace = false;

    // If this choice is top-level, has only a single option, and that
    // option consists of only a repetition or option (the '?' kind),
    // replace this ordered choice with the desugared repetition or
    // option, unless the repetition need not be desugared.
    if (top && (1 == c.options.size())) {
      Element e = (Element)c.options.get(0);

      if (((! repeatable()) && (e instanceof Repetition)) ||
          (e instanceof Option)) {
        if (Rats.optionVerbose) {
          System.out.print("[Transforming top-level ");
          if (e instanceof Repetition) {
            System.out.print("repitition");
          } else {
            System.out.print("option");
          }
          System.out.println(" in production " +
                             analyzer.current().nonTerminal.name +
                             " in place]");
        }

        transformInPlace = true;
        return (Element)e.accept(this);
      }
    }

    // Process the options and ensure that every option has a semantic
    // value.
    String    type   = null;
    final int length = c.options.size();
    for (int i=0; i<length; i++) {
      Sequence s = 
        Sequence.ensure((Element)((Element)c.options.get(i)).accept(this));

      if (! inPlace) {
        // Only add semantic values if the sequence does not end in
        // another choice.
        if (s.isEmpty() || (! (s.get(s.length()-1) instanceof OrderedChoice))) {
          if (isTextOnly) {
            if (top || bound || last) {
              String text = analyzer.matchingText(s);
              if ((null == text) || (! Rats.optimizeTerminals)) {
                s.elements.add(TextValue.VALUE);
              } else {
                s.elements.add(new StringValue(text));
              }
              type = Type.stringT();
            } else {
              s.elements.add(NullValue.VALUE);
              type = Type.voidT();
            }
            
          } else if (isVoid && (! bound)) {
            s.elements.add(NullValue.VALUE);
            type = Type.voidT();
            
          } else if (! last) {
            // In general, we do not add semantic values for the last
            // choice in a sequence.
            Binding b = analyzer.bind(s);
            if (null != b) {
              // Patch the variable name to be the semantic value.
              b.name = CodeGenerator.VALUE;
              if (null == type) {
                type = Type.type(b.element, analyzer);
              } else {
                type = Type.unify(type, Type.type(b.element, analyzer));
              }
            } else {
              type   = Type.rootT();
            }
          }
        }
      }
        
      c.options.set(i, s);
    }

    // If the ordered choice (1) is the top-level choice, (2) is being
    // transformed in place, or (3) is the last element in a sequence
    // (but not within a predicate), we are done.
    if (top || inPlace || (last && (! isPredicate))) {
      return c;
    }

    // Otherwise, lift the choice.
    NonTerminal nt = analyzer.choice();
    Production  p  = new Production(analyzer.current().isTransient,type,nt,c);
    if (isTextOnly && Type.isStringT(type)) {
      TextTester.markTextOnly(p);
    }
    analyzer.add(p);

    // Done.
    return nt;
  }

  /** Visit the specified repetition. */
  public Element visit(Repetition r) {
    isTopLevel       = false;
    isLastElement    = false;
    boolean bound    = isBound;
    isBound          = false;
    boolean inPlace  = transformInPlace;
    transformInPlace = isTextOnly || isVoid;

    // Process the repeated element first.
    Element e        = (Element)r.element.accept(this);

    // If the current production may contain repetitions and the
    // repetition is not bound, then do not desugar it.
    if (repeatable() && (! bound)) {
      r.element = Sequence.ensure(e);
      return r;
    }

    // Now, desugar the repetition.
    NonTerminal nt;
    if (inPlace) {
      nt = analyzer.current().nonTerminal;
    } else {
      nt = (r.once)? analyzer.plus() : analyzer.star();
    }

    List oldOptions;
    if (e instanceof OrderedChoice) {
      oldOptions = ((OrderedChoice)e).options;
    } else {
      oldOptions = new ArrayList(1);
      oldOptions.add(e);
    }

    List newOptions = new ArrayList(oldOptions.size() +
                                    ((r.once)? oldOptions.size() : 1));

    // The recursive options.
    Iterator iter = oldOptions.iterator();
    while (iter.hasNext()) {
      Sequence s;
      if (r.once) {
        s = new Sequence((Element)iter.next());
      } else {
        s = Sequence.ensure((Element)iter.next());
      }

      if (isTextOnly) {
        s.elements.add(nt);
        if (bound || inPlace) {
          s.elements.add(TextValue.VALUE);
        } else {
          s.elements.add(NullValue.VALUE);
        }
        
      } else if (isVoid && (! bound)) {
        s.elements.add(nt);
        s.elements.add(NullValue.VALUE);
        
      } else {
        Binding b1 = analyzer.bind(s);
        Binding b2 = new Binding(analyzer.variable(), nt);
        
        s.elements.add(b2);
        s.elements.add(new ListValue((null == b1) ?
                                      CodeGenerator.VALUE : b1.name,
                                      b2.name));
      }

      newOptions.add(s);
    }

    // The base option(s).
    if (r.once) {
      iter = oldOptions.iterator();
      while (iter.hasNext()) {
        Sequence s = new Sequence((Element)iter.next());

        if (isTextOnly) {
          if (bound || inPlace) {
            s.elements.add(TextValue.VALUE);
          } else {
            s.elements.add(NullValue.VALUE);
          }

        } else if (isVoid && (! bound)) {
          s.elements.add(NullValue.VALUE);

        } else {
          Binding b = analyzer.bind(s);
          s.elements.add(new SingletonListValue((null == b) ?
                                                CodeGenerator.VALUE : b.name));
        }

        newOptions.add(s);
      }

    } else {
      Sequence s = new Sequence(new ArrayList());

      if (isTextOnly) {
        if (bound || inPlace) {
          s.elements.add(TextValue.VALUE);
        } else {
          s.elements.add(NullValue.VALUE);
        }

      } else if (isVoid && (! bound)) {
        s.elements.add(NullValue.VALUE);

      } else {
        s.elements.add(EmptyListValue.VALUE);
      }

      newOptions.add(s);
    }

    // Create the new ordered choice.
    OrderedChoice c = new OrderedChoice(newOptions);
    if (inPlace) {
      return c;
    }

    // Create the new production.
    String type;
    if (isTextOnly) {
      if (bound || inPlace) {
        type = Type.stringT();
      } else {
        type = Type.voidT();
      }

    } else if (isVoid && (! bound)) {
      type = Type.voidT();

    } else {
      type = Type.listT();
    }

    Production p = new Production(analyzer.current().isTransient, type, nt, c);
    if (isTextOnly && Type.isStringT(type)) {
      TextTester.markTextOnly(p);
    }
    analyzer.add(p);

    // Done.
    return nt;
  }

  /** Visit the specified option. */
  public Element visit(Option o) {
    isTopLevel       = false;
    isLastElement    = false;
    boolean bound    = isBound;
    isBound          = false;
    boolean inPlace  = transformInPlace;
    transformInPlace = true;

    // Process the optional element first.
    Element e        = (Element)o.element.accept(this);

    // Now, desugar the option.
    NonTerminal nt =
      (inPlace)? analyzer.current().nonTerminal : analyzer.option();

    List oldOptions;
    if (e instanceof OrderedChoice) {
      oldOptions = ((OrderedChoice)e).options;
    } else {
      oldOptions = new ArrayList(1);
      oldOptions.add(e);
    }

    List   newOptions = new ArrayList(oldOptions.size() + 1);
    String type       = null;

    // The matching options.
    Iterator iter = oldOptions.iterator();
    while (iter.hasNext()) {
      Sequence s  = Sequence.ensure((Element)iter.next());

      if (isTextOnly) {
        if (bound || inPlace) {
          s.elements.add(TextValue.VALUE);
          type = Type.stringT();
        } else {
          s.elements.add(NullValue.VALUE);
          type = Type.voidT();
        }

      } else if (isVoid && (! bound)) {
        s.elements.add(NullValue.VALUE);
        type = Type.voidT();

      } else {
        Binding b = analyzer.bind(s);
        if (null != b) {
          // Path the variable name to be the semantic value.
          b.name = CodeGenerator.VALUE;
          if (null == type) {
            type = Type.type(b.element, analyzer);
          } else {
            type = Type.unify(type, Type.type(b.element, analyzer));
          }
        } else {
          type   = Type.rootT();
        }
      }

      newOptions.add(s);
    }

    // The (empty) alternative option.
    Sequence alt = new Sequence(new ArrayList());

    if (isTextOnly && (bound || inPlace)) {
      alt.elements.add(TextValue.VALUE);
    } else {
      alt.elements.add(NullValue.VALUE);
    }

    newOptions.add(alt);

    // Create the new ordered choice.
    OrderedChoice c = new OrderedChoice(newOptions);
    if (inPlace) {
      return c;
    }

    // Create the new production.
    Production    p = new Production(analyzer.current().isTransient,type,nt,c);
    if (isTextOnly && Type.isStringT(type)) {
      TextTester.markTextOnly(p);
    }
    analyzer.add(p);

    // Done.
    return nt;
  }

  /** Visit the specified sequence. */
  public Element visit(Sequence s) {
    isTopLevel       = false;
    isBound          = false;
    transformInPlace = false;
    final int length = s.length();
    for (int i=0; i<length; i++) {
      isLastElement  = (i == length - 1);
      s.elements.set(i, s.get(i).accept(this));
    }
    isLastElement    = false;
    return s;
  }

  /** Visit the specified predicate. */
  public Element visit(Predicate p) {
    boolean predicate = isPredicate;
    isPredicate       = true;
    isTopLevel        = false;
    isLastElement     = false;
    isBound           = false;
    transformInPlace  = false;
    p.element         = Sequence.ensure((Element)p.element.accept(this));
    isPredicate       = predicate;
    return p;
  }

  /** Visit the specified semantic predicate. */
  public Element visit(SemanticPredicate p) {
    isTopLevel       = false;
    isLastElement    = false;
    isBound          = false;
    transformInPlace = false;
    p.element        = (Element)p.element.accept(this);
    return p;
  }

  /** Visit the specified character case. */
  public CharCase visit(CharCase c) {
    isTopLevel       = false;
    isLastElement    = false;
    isBound          = false;
    transformInPlace = false;
    if (null != c.element) {
      c.element      = (Element)c.element.accept(this);
    }
    return c;
  }

  /** Visit the specified character switch. */
  public Element visit(CharSwitch s) {
    isTopLevel       = false;
    isLastElement    = false;
    isBound          = false;
    transformInPlace = false;
    final int length = s.cases.size();
    for (int i=0; i<length; i++) {
      s.cases.set(i, ((CharCase)s.cases.get(i)).accept(this));
    }
    if (null != s.base) {
      s.base         = (Element)s.base.accept(this);
    }
    return s;
  }

  /**
   * Visit the specified unary operator.  This method provides the
   * default implementation for bindings and string matches.
   */
  public Element visit(UnaryOperator op) {
    isTopLevel       = false;
    isLastElement    = false;
    isBound          = true;
    transformInPlace = false;
    op.element       = (Element)op.element.accept(this);
    return op;
  }

  /**
   * Visit the specified element.  This method provides the default
   * implementation for nonterminals, terminals, actions, and value
   * elements.
   */
  public Element visit(Element e) {
    isTopLevel       = false;
    isLastElement    = false;
    isBound          = false;
    transformInPlace = false;
    return e;
  }

}

