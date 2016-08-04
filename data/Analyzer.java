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
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import xtc.Constants;

import xtc.tree.Utility;
import xtc.tree.Visitor;

/** 
 * Utility for analyzing and modifying grammars.  This class provides
 * the following functionality:<ul>
 *
 * <li>A mapping from nonterminals to productions, which is
 * initialized through {@link #init(Grammar)} and accessed through
 * {@link #isDefined(NonTerminal)} and {@link #lookup(NonTerminal)}.<p
 * /></li>
 *
 * <li>The set of top-level nonterminals, which is accessed through
 * {@link #isTopLevel(NonTerminal)}.<p /></li>
 *
 * <li>Methods to start {@link #process processing} a production and
 * to {@link #current determine} the current production.<p /></li>
 *
 * <li>A working set, marked set, and processed set to determine
 * properties of productions.  The idea behind these three sets is
 * that the working set keeps track of all productions during an
 * analysis pass and is used to prevent infinite recursion, the marked
 * set tracks the productions having the property, and the processed
 * set (which is a superset of the marked set) tracks the analyzed
 * productions.  The working set is accessed through {@link
 * #workingOn(NonTerminal)}, {@link #notWorkingOn(NonTerminal)},
 * {@link #isBeingWorkedOn(NonTerminal)}, and {@link #working()}.  The
 * marked set is accessed through {@link #mark(NonTerminal)}, {@link
 * #unmark(NonTerminal)}, {@link #isMarked(NonTerminal)}, and {@link
 * #marked()}.  Finally, the processed set is accessed through {@link
 * #processed(NonTerminal)} and {@link #isProcessed(NonTerminal)}.<p
 * /></li>
 *
 * <li>Methods to add and remove productions from a grammar.  New
 * productions are prepared for addition through {@link
 * #add(Production)} and committed to the grammar through {@link
 * #addNewProductionsAt(int)}.  Existing productions are removed
 * through {@link #remove(Production)}.<p /></li>
 *
 * <li>A set of methods for creating temporary variable names and
 * nonterminals for new productions: {@link #variable()}, {@link
 * #choice()}, {@link #star()}, {@link #plus()}, {@link #option()},
 * and {@link #shared()}.<p /></li>
 *
 * <li>A method to {@link #strip(Element) strip} unnecessary ordered
 * choices and sequences from an element.<p /></li>
 *
 * <li>A method to test whether an element {@link
 * #matchesEmpty(Element) matches the empty input}.<p /></li>
 *
 * <li>A method to {@link #copy(Element) copy} an element.<p /></li>
 *
 * <li>A set of methods for optimizing sequences that start with
 * terminals through character switches: {@link
 * #hasTerminalPrefix(Sequence)}, {@link #normalize(Sequence)}, and
 * {@link #join(Sequence,Element)}.<p /></li>
 *
 * <li>A method to {@link #matchingText(Element) get the text} of an
 * element.<p /></li>
 *
 * <li>A method to {@link #bind(Sequence) add bindings} to a
 * sequence.<p /></li>
 *
 * </ul>
 *
 * To utilize this analyzer utility for a given grammar, the utility
 * must be {@link #init initialized(Grammar)} with the grammar, and
 * each production must be {@link #process processed} with the
 * utility.  Furthermore, new productions must be added through {@link
 * #add(Production)} and obsolete productions must be removed through
 * {@link #remove(Production)}.
 *
 * <p />The analyzer utility tracks the current grammar so that it
 * need not recreate its internal state (notably, the mapping from
 * nonterminals to productions) as long as the same analyzer utility
 * is used across different visitors.
 *
 * @author Robert Grimm
 * @version $Revision: 1.2 $
 */
public class Analyzer extends Utility {

  /**
   * The separator character for creating new nonterminals, which
   * should be illegal in regular variable or nonterminal names.
   *
   */
  public static final String SEPARATOR = "$";

  /** The base name for nonterminals representing shared productions. */
  public static final String SHARED = SEPARATOR + "Shared";

  /** The base name for temporary variables. */
  public static final String VARIABLE = "v" + SEPARATOR;

  /** The suffix for nonterminals representing choices. */
  public static final String CHOICE = SEPARATOR + "Choice";
  
  /**
   * The suffix for nonterminals representing zero or more
   * repetitions.
   */
  public static final String STAR = SEPARATOR + "Star";

  /**
   * The suffix for nonterminals representing one or more
   * repetitions.
   */
  public static final String PLUS = SEPARATOR + "Plus";

  /** The suffix for nonterminals representing options. */
  public static final String OPTION = SEPARATOR + "Option";

  /**
   * The maximum character count for turning character classes into
   * character switches.
   */
  public static final int MAX_COUNT = 22;

  // =======================================================================

  /** The element copier. */
  protected final Copier xerox;

  /** The current grammar. */
  protected Grammar    grammar;

  /** The map from nonterminals to productions. */
  protected Map        pMap;

  /** The set of top-level nonterminals. */
  protected Set        pTop;

  /** The current production. */
  protected Production pCurrent;

  /**
   * The set of nonterminals corresponding to productions currently
   * being processed.
   */
  protected Set        pWorking;

  /**
   * The set of nonterminals corresponding to productions having
   * been marked.
   */
  protected Set        pMarked;

  /**
   * The set of nonterminals corresponding to productions having
   * been processed.
   */
  protected Set        pProcessed;

  /** The list of newly added productions. */
  protected List       pNew;

  /** The count of temporary variables for the current production. */
  protected int        varCount;

  /** The count of lifted choices for the current production. */
  protected int        choiceCount;

  /** The count of desugared star repetitions for the current production. */
  protected int        starCount;

  /** The count of desugared plus repetitions for the current production. */
  protected int        plusCount;

  /** The count of desugared options for the current production. */
  protected int        optionCount;

  /** The count of shared productions. */
  protected int        sharedCount;

  // =======================================================================

  /** Create a new analyzer utility. */
  public Analyzer() {
    xerox       = new Copier();
    pMap        = new HashMap();
    pTop        = new HashSet();
    pWorking    = new HashSet();
    pMarked     = new HashSet();
    pProcessed  = new HashSet();
    pNew        = new ArrayList();
    sharedCount = 1;
  }

  /** Forcibly reset the analyzer utility. */
  public void reset() {
    grammar     = null;
    pCurrent    = null;
    pMap.clear();
    pTop.clear();
    pWorking.clear();
    pMarked.clear();
    pProcessed.clear();
    pNew.clear();
    varCount    = 1;
    choiceCount = 1;
    starCount   = 1;
    plusCount   = 1;
    optionCount = 1;
    sharedCount = 1;
  }

  // =======================================================================

  /**
   * Initialize this analyzer for the specified grammar.  This method
   * initializes the map from nonterminals to productions and the set
   * of top-level nonterminals.  It also clears the sets of marked and
   * processed nonterminals.  It should be called before iterating
   * over a grammar's productions.
   *
   * @param g The grammar.
   */
  public void init(Grammar g) {
    // Initialize the map from nonterminals to productions and the set
    // of top-level nonterminals.
    if (grammar != g) {
      grammar = g;

      pMap.clear();
      Iterator iter = g.productions.iterator();
      while (iter.hasNext()) {
        Production p = (Production)iter.next();
        pMap.put(p.nonTerminal, p);
      }

      pTop.clear();
      iter = g.topLevel.iterator();
      while (iter.hasNext()) {
        pTop.add(iter.next());
      }
    }

    // Clear the sets of marked and processed productions.
    pMarked.clear();
    pProcessed.clear();

    // Clear the current production.
    pCurrent = null;
  }

  /**
   * Determine whether the specified nonterminal is defined.  A
   * nonterminal is defined if the current grammar contains a
   * production for that nonterminal.
   *
   * @param nt The nonterminal.
   * @return <code>true</code> if the nonterminal is defined.
   */
  public boolean isDefined(NonTerminal nt) {
    return pMap.containsKey(nt);
  }

  /**
   * Determine whether the specified nonterminal is top-level.
   *
   * @param nt The nonterminal.
   * @return <code>true</code> if the nonterminal is top-level.
   */
  public boolean isTopLevel(NonTerminal nt) {
    return pTop.contains(nt);
  }

  /**
   * Look up the production for the specified nonterminal.
   *
   * @param nt The nonterminal.
   * @return The corresponding production or <code>null</code>
   *   if there is no such production.
   */
  public Production lookup(NonTerminal nt) {
    return (Production)pMap.get(nt);
  }

  // =======================================================================

  /**
   * Process the specified production.  This method clears the set of
   * working nonterminals.  It also resets the counters for creating
   * new variables and nonterminals (besides the counter for shared
   * productions).  It then invokes this analyzer's visitor on the
   * specified production.  This method should be called within the
   * loop iterating over a grammar's productions, but not at other
   * locations within a visitor.
   *
   * @param p The production.
   */
  public void process(Production p) {
    // Initialize the per-production state.
    pWorking.clear();

    varCount    = 1;
    choiceCount = 1;
    starCount   = 1;
    plusCount   = 1;
    optionCount = 1;

    // Remember the current production.
    pCurrent    = p;

    // Now, actually process the production.
    p.accept(visitor());
  }

  /**
   * Get the production currently being processed.
   *
   * @return The current production.
   */
  public Production current() {
    return pCurrent;
  }

  // =======================================================================

  /**
   * Set the status of the specified nonterminal as being worked on.
   *
   * @param nt The nonterminal.
   */
  public void workingOn(NonTerminal nt) {
    pWorking.add(nt);
  }

  /**
   * Set the status of the specified nonterminal as not being worked
   * on.
   *
   * @param nt The nonterminal.
   */
  public void notWorkingOn(NonTerminal nt) {
    pWorking.remove(nt);
  }

  /**
   * Determine whether the specified nonterminal is being worked on.
   *
   * @param nt The nonterminal.
   * @return <code>true</code> if the nonterminal is being worked
   *    on.
   */
  public boolean isBeingWorkedOn(NonTerminal nt) {
    return pWorking.contains(nt);
  }

  /**
   * Get the set of nonterminals being worked on.  Note that the
   * caller must copy the set if it keeps the reference to the
   * returned set after the next call to {@link #process}.
   *
   * @return The working set.
   */
  public Set working() {
    return pWorking;
  }

  // =======================================================================

  /**
   * Mark the specified nonterminal.
   *
   * @param nt The nonterminal.
   */
  public void mark(NonTerminal nt) {
    pMarked.add(nt);
  }

  /**
   * Unmark the specified nonterminal.
   *
   * @param nt The nonterminal.
   */
  public void unmark(NonTerminal nt) {
    pMarked.remove(nt);
  }

  /**
   * Determine whether the specified nonterminal has been marked.
   *
   * @param nt The nonterminal.
   * @return <code>true</code> if the nonterminal has been
   *   marked.
   */
  public boolean isMarked(NonTerminal nt) {
    return pMarked.contains(nt);
  }

  /**
   * Get the set of marked nonterminals.  Note that the called must
   * copy the set if it keeps the reference to the returned set after
   * the next use of this analyzer.
   *
   * @return The marked set.
   */
  public Set marked() {
    return pMarked;
  }

  // =======================================================================

  /**
   * Set the status of the specified nonterminal as processed.
   *
   * @param nt The nonterminal.
   */
  public void processed(NonTerminal nt) {
    pProcessed.add(nt);
  }

  /**
   * Determine whether the specified nonterminal has been processed.
   *
   * @param nt The nonterminal.
   * @return <code>true</code> if the nonterminal has been processed.
   */
  public boolean isProcessed(NonTerminal nt) {
    return pProcessed.contains(nt);
  }

  // =======================================================================

  /**
   * Clear the list of newly generated productions.  This method needs
   * to be called before a processing step that may add new
   * productions through {@link #add(Production)} and {@link
   * #addNewProductionsAt(int)}.
   */
  public void startAdding() {
    pNew.clear();
  }

  /**
   * Prepare the specified production for addition to the grammar.
   * This method adds the specified production to the list of newly
   * generated productions.  It also adds the production to the map
   * from nonterminals to productions and marks it as {@link
   * Constants#SYNTHETIC synthetic}.  However, addition is not
   * complete: the productions in the list of newly generated
   * productions still need to be added into the grammar itself.  This
   * is typically done within the main loop iterating over a grammar's
   * productions and thus through a separate {@link
   * #addNewProductionsAt(int) method}.
   * 
   * @param p The new production.
   */
  public void add(Production p) {
    p.setProperty(Constants.SYNTHETIC, Boolean.TRUE);
    pNew.add(p);
    pMap.put(p.nonTerminal, p);
  }

  /**
   * Add the newly generated productions to the grammar itself.  This
   * method adds the productions collected through {@link
   * #add(Production) add()} into the current grammar at the specified
   * index of the grammar's list of productions.
   *
   * @param idx The index into the grammar's list of productions.
   * @return The number of productions added.
   */
  public int addNewProductionsAt(int idx) {
    final int size = pNew.size();

    if (0 != size) {
      grammar.productions.addAll(idx, pNew);
    }

    return size;
  }

  /**
   * Prepare the specified production for removal from the grammar.
   * This method removes the specified production from the mapping
   * from nonterminals to productions and, if present, from the set of
   * top-level nonterminals.  However, removal is not complete: the
   * production still needs to be removed from the grammar itself.
   * This is typically done within the main loop iterating over a
   * grammar's productions.
   *
   * @param p The production.
   */
  public void remove(Production p) {
    pMap.remove(p.nonTerminal);
    pTop.remove(p.nonTerminal);
  }

  // =======================================================================

  /**
   * Create a new temporary variable.
   *
   * @return The name of the temporary variable.
   */
  public String variable() {
    String temp = VARIABLE + Integer.toString(varCount);
    varCount++;
    return temp;
  }

  /**
   * Create a new nonterminal for a choice.
   *
   * @return The new nonterminal.
   */
  public NonTerminal choice() {
    NonTerminal nt = new NonTerminal(pCurrent.nonTerminal.name + CHOICE +
                                     Integer.toString(choiceCount));
    choiceCount++;
    return nt;
  }

  /**
   * Create a new nonterminal for zero or more repetitions.
   *
   * @return The new nonterminal.
   */
  public NonTerminal star() {
    NonTerminal nt = new NonTerminal(pCurrent.nonTerminal.name + STAR +
                                     Integer.toString(starCount));
    starCount++;
    return nt;
  }

  /**
   * Create a new nonterminal for one or more repetitions.
   *
   * @return The new nonterminal.
   */
  public NonTerminal plus() {
    NonTerminal nt = new NonTerminal(pCurrent.nonTerminal.name + PLUS +
                                     Integer.toString(plusCount));
    plusCount++;
    return nt;
  }

  /**
   * Create a new nonterminal for an option.
   *
   * @return The new nonterminal.
   */
  public NonTerminal option() {
    NonTerminal nt = new NonTerminal(pCurrent.nonTerminal.name + OPTION +
                                     Integer.toString(optionCount));
    optionCount++;
    return nt;
  }

  /**
   * Create a new nonterminal for a shared production.
   *
   * @return The new nonterminal.
   */
  public NonTerminal shared() {
    NonTerminal nt = new NonTerminal(SHARED + Integer.toString(sharedCount));
    sharedCount++;
    return nt;
  }

  // =======================================================================

  /**
   * Strip unnecessary ordered choices and sequences from the specified
   * element.  A choice or sequence is unnecessary if it contains only
   * a single element.
   *
   * @param e The element.
   * @return The stripped element.
   */
  public Element strip(Element e) {
    if (e instanceof OrderedChoice) {
      OrderedChoice c = (OrderedChoice)e;
      if (1 == c.options.size()) {
        e = strip((Element)c.options.get(0));
      }
    } else if (e instanceof Sequence) {
      Sequence s = (Sequence)e;
      if (1 == s.length()) {
        e = strip(s.get(0));
      }
    }
    return e;
  }

  // =======================================================================

  /**
   * Determine whether the specified element matches the empty input.
   * Note that this method assumes that nonterminals do not match the
   * empty input.
   *
   * @param e The element.
   * @return <code>true</code> if the specified element matches the
   *   empty input.
   */
  public boolean matchesEmpty(Element e) {
    if (e instanceof OrderedChoice) {
      OrderedChoice c    = (OrderedChoice)e;
      Iterator      iter = c.options.iterator();
      while (iter.hasNext()) {
        if (matchesEmpty((Element)iter.next())) {
          return true;
        }
      }
      return false;

    } else if (e instanceof Repetition) {
      Repetition r = (Repetition)e;

      if (r.once) {
        return matchesEmpty(r.element);
      } else {
        return true;
      }

    } else if (e instanceof Option) {
      return true;

    } else if (e instanceof Sequence) {
      Sequence s    = (Sequence)e;
      Iterator iter = s.elements.iterator();
      while (iter.hasNext()) {
        if (! matchesEmpty((Element)iter.next())) {
          return false;
        }
      }
      return true;

    } else if ((e instanceof SemanticPredicate) ||
               (e instanceof StringMatch) ||
               (e instanceof NonTerminal) ||
               (e instanceof Terminal)) {
      return false;

    } else {
      // Actions and value elements do not match anything.
      return true;
    }
  }

  // =======================================================================

  /**
   * Make a deep copy of the specified element.
   *
   * @param e The element.
   * @return A deep copy.
   */
  public Element copy(Element e) {
    return (Element)e.accept(xerox);
  }

  // =======================================================================

  /**
   * Determine whether the specified sequence starts with terminals
   * that can be optimized.  This method returns <code>true</code> if
   * the terminals can be optimized through character switches.
   * Currently, this is only the case for character and string
   * literals.
   *
   * @param s The sequence.
   * @return <code>true</code> if the sequence starts with optimizable
   *   terminals.
   */
  public boolean hasTerminalPrefix(Sequence s) {
    if (1 <= s.length()) {
      Element e = s.get(0);

      if ((e instanceof CharLiteral) ||
          (e instanceof StringLiteral) ||
          ((e instanceof CharClass) &&
           (((CharClass)e).count() <= MAX_COUNT))) {
        return true;
      }
    }

    return false;
  }

  /**
   * Determine the length of the specified sequence after
   * normalization.
   *
   * @param s The sequence
   * @return The size of the normalized sequence or -1 if the sequence
   *   already is in normal form.
   */
  private int normalLength(Sequence s) {
    final int length = s.length();
    boolean   normal = true;
    int       count  = 0;

    for (int i=0; i<length; i++) {
      Element e = s.get(i);

      if (e instanceof CharLiteral) {
        normal = false;
        count++;

      } else if (e instanceof StringLiteral) {
        normal = false;
        count += ((StringLiteral)e).text.length();

      } else if (e instanceof CharClass) {
        count++;

      } else {
        count += (length - i);
        break;
      }
    }

    return (normal)? -1 : count;
  }

  /**
   * Normalize the specified sequence for {@link
   * #join(Sequence,Element) joining} with other elements during
   * terminal optimization.  Currently, this method converts string
   * literals into equivalent subsequences of character literals.
   *
   * @param s The sequence.
   * @return The optimized sequence.
   */
  public Sequence normalize(Sequence s) {
    final int nl = normalLength(s);
    if (-1 == nl) return s;

    final int l  = s.length();
    Sequence  s2 = new Sequence(new ArrayList(nl));

    for (int i=0; i<l; i++) {
      Element e = s.get(i);

      if (e instanceof CharLiteral) {
        s2.elements.add(new CharClass(((CharLiteral)e).c));

      } else if (e instanceof StringLiteral) {
        StringLiteral sl = (StringLiteral)e;

        for (int j=0; j<sl.text.length(); j++) {
          s2.elements.add(new CharClass(sl.text.charAt(j)));
        }

      } else if (e instanceof CharClass) {
        s2.elements.add(e);

      } else {
        s2.elements.addAll(s.elements.subList(i, l));
        break;
      }
    }

    return s2;
  }

  /**
   * Join the specified sequence with the specified element.  Note
   * that the specified sequence must have been {@link
   * #normalize(Sequence) normalized}.  Further note that the combined
   * element is guaranteed to either be a sequence or an ordered
   * choice.
   *
   * @param source The source sequence.
   * @param target The target element.
   * @return The combined element.
   */
  public Element join(Sequence source, Element target) {
    // Handle trivial case first.  Otherwise, normalize target.
    if (null == target) {
      return source;

    } else if (target instanceof Sequence) {
      // Strip sequence containing only an ordered choice.
      Sequence s = (Sequence)target;

      if (1 == s.length()) {
        Element e = s.get(0);

        if (e instanceof OrderedChoice) {
          target = e;
        }
      }
    }

    // Now, do the real joining.
    if (target instanceof Sequence) {
      final Sequence  t  = (Sequence)target;
      final Element   t1 = (t.isEmpty())? null : t.get(0);
      final Element   s1 = (source.isEmpty())? null : source.get(0);

      if ((s1 instanceof CharClass) &&
          (t1 instanceof CharClass) &&
          s1.equals(t1)) {
        // Both sequences start with the same character class.
        // Combine them into a single sequence, independent of the
        // class's count.
        Sequence result = new Sequence(join(source.subSequence(1),
                                            t.subSequence(1)));
        result.elements.add(0, s1);

        return result;

      } else if ((s1 instanceof CharClass) &&
                 (((CharClass)s1).count() <= MAX_COUNT)) {
        CharClass sk = (CharClass)s1;

        if (t1 instanceof CharClass) {
          CharClass tk = (CharClass)t1;

          if (tk.count() <= MAX_COUNT) {
            // Both sequences start with different character classes.
            // Try to combine them into a new character switch.
            return join(source,
                        new Sequence(new CharSwitch(tk, t.subSequence(1))));
          }

          // Fall through to creating an ordered choice.

        } else if (t1 instanceof CharSwitch) {
          CharSwitch sw    = (CharSwitch)t1;

          // Strip the exclusive flag and then look for an existing case.
          CharClass  klass = new CharClass(sk.ranges);
          CharCase   kase  = sw.hasCase(klass);

          if (sk.exclusive) {
            // We can only join the source into the character switch
            // if the switch covers exactly the non-exclusive version.
            if ((null != kase) && (1 == sw.cases.size())) {
              sw.base = join(source.subSequence(1), sw.base);

              return target;
            }

            // Fall through to creating an ordered choice.

          } else {
            if (null != kase) {
              // Join the sequence into the existing character case.
              kase.element = join(source.subSequence(1), kase.element);

              return target;

            } else if ((! sw.overlaps(klass)) && (null == sw.base)) {
              // If there is no overlap with an existing case and the
              // switch does not contain an exclusive character class,
              // add a new character case.
              sw.cases.add(new CharCase(klass, source.subSequence(1)));

              return target;
            }

            // Fall through to creating an ordered choice.
          }
        }
      }

      // Create a new choice with the target and source.
      OrderedChoice c = new OrderedChoice(new ArrayList());
      c.options.add(target);
      c.options.add(source);
      return c;

    } else if (target instanceof OrderedChoice) {
      // Join the source with the last option.
      OrderedChoice c = (OrderedChoice)target;
      final int     l = c.options.size();
      Element       e = join(source, (Element)c.options.get(l-1));

      if (e instanceof OrderedChoice) {
        c.options.remove(l-1);
        c.options.addAll(((OrderedChoice)e).options);
      } else {
        c.options.set(l-1, e);
      }

      return c;

    } else {
      // Join the source with a new sequence containing the target
      // element.
      return join(source, new Sequence(target));
    }
  }

  // =======================================================================

  /**
   * Get the text matched by the specified element.  This method
   * analyzes the specified element, and, if the element always
   * matches the same text, this method returns the constant text.
   * Otherwise, this method returns <code>null</code>.  Note that this
   * method ignores predicates, actions, and value elements, as they
   * do not change the text matched by an element.  Further note that
   * this method recursively analyzes referenced nonterminals.
   *
   * @param e The element.
   * @return The constant text.
   */
  public String matchingText(Element e) {
    StringBuffer buf = new StringBuffer();

    if (matchingText(e, buf)) {
      return buf.toString();
    } else {
      return null;
    }
  }

  /**
   * Get the text matched by the specified element.
   *
   * @param e The element.
   * @param buf The buffer for the matched text.
   * @return <code>true</code> if the element matches a constant
   *   text.
   */
  private boolean matchingText(Element e, StringBuffer buf) {
    if (e instanceof OrderedChoice) {
      OrderedChoice c = (OrderedChoice)e;
      if (1 == c.options.size()) {
        return matchingText((Element)c.options.get(0), buf);
      } else {
        return false;
      }

    } else if ((e instanceof Repetition) || (e instanceof Option)) {
      return false;

    } else if (e instanceof Sequence) {
      Sequence  s = (Sequence)e;
      final int l = s.length();
      for (int i=0; i<l; i++) {
        if (! matchingText(s.get(i), buf)) {
          return false;
        }
      }
      return true;

    } else if (e instanceof Predicate) {
      return true;

    } else if (e instanceof Binding) {
      return matchingText(((Binding)e).element, buf);

    } else if (e instanceof StringMatch) {
      return matchingText(((StringMatch)e).element, buf);

    } else if (e instanceof NonTerminal) {
      Production p = lookup((NonTerminal)e);
      return matchingText(p.element, buf);

    } else if (e instanceof StringLiteral) {
      buf.append(((StringLiteral)e).text);
      return true;

    } else if (e instanceof CharLiteral) {
      buf.append(((CharLiteral)e).c);
      return true;

    } else if (e instanceof CharClass) {
      CharClass c = (CharClass)e;

      if (1 == c.ranges.size()) {
        CharRange r = (CharRange)c.ranges.get(0);
        if (r.first == r.last) {
          buf.append(r.first);
          return true;
        }
      }
      return false;

    } else if (e instanceof Terminal) {
      // All other terminals do not match a constant character.
      return false;

    } else if ((e instanceof Action) || (e instanceof ValueElement)) {
      return true;

    } else {
      // We don't know this element.
      return false;
    }
  }

  // =======================================================================

  /**
   * Bind the elements in the specified sequence.  This method
   * analyzes the specified sequence and, if necessary, adds in a
   * binding for the semantic value of the elements in the sequence.
   * If the sequence has more than one element to be bound, this
   * method returns <code>null</code> to indicate that we need to rely
   * on the {@link CodeGenerator#VALUE semantic value} to capture the
   * sequence's value.
   *
   * @param s The sequence to bind.
   * @return The corresponding binding.
   */
  public Binding bind(Sequence s) {
    Binding   binding = null;
    Element   bound   = null;
    int       idx     = -1;

    final int length  = s.length();
    for (int i=0; i<length; i++) {
      Element e = s.get(i);

      if ((e instanceof OrderedChoice)
          || (e instanceof Repetition)
          || (e instanceof Option)
          || (e instanceof Sequence)) {
        // Embedded choices, repetitions, options, and sequences
        // should not appear.  All bets are off.
        binding = null;
        idx     = -1;
        break;

      } else if (e instanceof Predicate) {
        // Skip predicates.

      } else if (e instanceof Binding) {
        if (-1 == idx) {
          binding = (Binding)e;
          idx     = i;
        } else {
          binding = null;
          idx     = -1;
          break;
        }

      } else if (e instanceof NonTerminal) {
        Production p = lookup((NonTerminal)e);

        if (Type.isVoidT(p.type)) {
          // Void productions cannot be bound. Skip them.
          continue;
        }

        if (-1 == idx) {
          bound   = e;
          idx     = i;
        } else {
          binding = null;
          idx     = -1;
          break;
        }

      } else if ((e instanceof Terminal)
                 || (e instanceof StringMatch)) {
        if (-1 == idx) {
          bound   = e;
          idx     = i;
        } else {
          binding = null;
          idx     = -1;
          break;
        }

      } else {
        // The element is either an action or a value element. All
        // bets are off.
        binding = null;
        idx     = -1;
        break;
      }
    }

    if (null != binding) {
      // There is a single element that already has a binding.
      return binding;

    } else if (-1 == idx) {
      // There is a sequence of elements. We rely on the semantic
      // value to capture the sequence's value.
      return null;

    } else {
      binding = new Binding(variable(), bound);
      s.elements.set(idx, binding);
      return binding;
    }
  }

}
