/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
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
package superc.core;

import java.lang.StringBuilder;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;

import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.util.Pair;

import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;
import superc.core.Syntax.Error;
import superc.core.Syntax.ErrorType;

import superc.core.PresenceConditionManager.PresenceCondition;

/**
 * This class expands macros and processes header files
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.272 $
 */
public class ForkMergeParser {
  /** The name of the AST conditional node. */
  public static String CHOICE_NODE_NAME = "Conditional";

  /** A different way to merge choice nodes is to flatten them instead
   * of creating a hierarchy. */
  public static boolean FLATTEN_MERGED_CHOICE_NODES = false;

  /** Parsing actions. */
  private static enum ParsingAction {
    NONE,
    SHIFT,
    REDUCE,
    ACCEPT,
    ERROR
  }

  /** Array of error messages. */
  final private static String[] ERRMSG = {
    "no default action",
    "invalid table entry",
    "fatal preprocessing error",
    "error directive"};

  /** Error code for no default action.  */
  final private static int NODEFAULT = 0;
  
  /** Error code for invalid table entry. */
  final private static int INVALID = 1;
  
  /** Error code for seen an error directive. */
  final private static int ERRDIRECTIVE = 2;
  
  /** Error code for seen an error directive. */
  final private static int NONFATAL = 3;
  
  /** The state number of the the starting state. */
  final private static int STARTSTATE = 0;

  /** Turn new error handling on. */
  private static boolean newErrorHandling = false;

  /** Save the disjunction of invalid configurations. */
  private boolean saveErrorCond = false;

  /** The disjunction of parse error conditions. */
  private PresenceCondition errorCond;

  /** The parse tables. */
  private ParseTables tables;

  /** The semantic values plugin. */
  private SemanticValues semanticValues;

  /** The semantic actions plugin. */
  private SemanticActions semanticActions;

  /** True when the grammar has a semantic actions plugin. */
  private boolean hasSemanticActions = false;

  /** The intitial parsing context. */
  private ParsingContext initialParsingContext;

  /** 
   * Flag that informs to track all productions under 
   * conditionGranularity 
   */
  private boolean trackAllProductions = false;

  /** True when the language has a parsing context. */
  private boolean hasParsingContext = false;

  /** The stream from which the parser gets syntactic units */
  private Iterator<Syntax> stream;
  
  /** The presenceCondition manager. */
  private PresenceConditionManager presenceConditionManager;

  /** The accepted subparsers. */
  List<Subparser> accepted;

  /**
   * The sequence numbers of nested conditionals.  Used by lazy
   * forking to only fork the closest conditional when it has empty
   * branches.
   */
  private LinkedList<Integer> nestedConditionals;

  /** Whether to save layout tokens or not. */
  private boolean saveLayoutTokens = false;

  /** Whether shared reductions is on or not. */
  private boolean optimizeSharedReductions = true;

  /** Whether lazy forking is on or not. */
  private boolean optimizeLazyForking = true;

  /** Whether early reduction is on or not. */
  private boolean optimizeEarlyReduce = true;

  /** Whether Platoff ordering is on or not. */
  private boolean optimizePlatoffOrdering = false;

  /** Whether follow-set caching is on. */
  private boolean optimizeFollowSetCaching = true;

  /** Whether deoptimize early shift is on or not. */
  private boolean deoptimizeEarlyShift = false;

  /** The follow-set cache. */
  private Map<Integer, Collection<Lookahead>> followCache;

  /** The skipConditional cache. */
  private Map<Integer, OrderedSyntax> skipConditionalCache;

  /**
   * The comparator method for the priority queue of subparsers.  For
   * optimization, there are two subparser ordering comparators: (1)
   * the fully-optimized one and (2) a configurable one.  The
   * fully-optimized comparator saves times since it does not need to
   * check which optimizations are set.
   */
  private Comparator<Subparser> subparserComparator;

  /** Show all parsing actions. */
  private boolean showActions = false;

  /** Show errors. */
  private boolean showErrors = true;

  /** Show accepts. */
  private boolean showAccepts = false;

  /** Show all fork and merge actions. */
  private boolean showFM = false;

  /** Show lookaheads on each parse loop. */
  private boolean showLookaheads = false;

  /** Turn parser statistics collection on. */
  private boolean parserStatistics = false;

  /** The productions to track for granularity. */
  private Set<String> trackedProductions;

  /** Turn condition granularity collection on. */
  private boolean conditionGranularity = false;

  /**
   * Emit the conditional after-set of productions
   * when the conditional inside-set is empty after reduction
   */
  private boolean emitConditionalAfterSet = false;

  /** Turn the subparser kill-switch on. */
  private boolean killswitch = false;

  /** The kill-switch cutoff for number of subparsers. */
  private int killswitchCutoff;

  /** Count the number of parser loop iterations. */
  private int iterations;

  /** Count the number of lazy forks. */
  private int lazyForks;

  /** Count the number of lazy forks with empty branches. */
  private int lazyForksEmptyBranches;

  /** Count the number of conditionals with empty branches. */
  private HashMap<Integer, Boolean> emptyConditionals;

  /** Collect the distribution of subparsers throughout parsing. */
  private HashMap<Integer, Integer> nsubparsers;

  /** Count the number of times FOLLOW is called. */
  private int nfollow;

  /** Create a new parser. */
  public ForkMergeParser(ParseTables tables, SemanticValues semanticValues,
                         Iterator<Syntax> stream,
                         PresenceConditionManager presenceConditionManager) {
    this(tables, semanticValues, null, null, stream, presenceConditionManager);
  }

  /** Create a new parser. */
  public ForkMergeParser(ParseTables tables, SemanticValues semanticValues,
                         SemanticActions semanticActions,
                         ParsingContext parsingContext,
                         Iterator<Syntax> stream,
                         PresenceConditionManager presenceConditionManager) {
    this.tables = tables;
    this.semanticValues = semanticValues;
    this.setSemanticActions(semanticActions);
    this.setInitialContext(parsingContext);
    this.stream = stream;
    this.presenceConditionManager = presenceConditionManager;

    this.accepted = new ArrayList<Subparser>();
    this.nestedConditionals = new LinkedList<Integer>();

    skipConditionalCache = new HashMap<Integer, OrderedSyntax>();

    this.errorCond = presenceConditionManager.newFalse();
  }

  /**
   * Enables new error handling, where error parsers are allowed to
   * merge with others instead of being dropped immediately on parser
   * error.
   */
  public static void setNewErrorHandling(boolean b) {
    newErrorHandling = b;
  }

  /**
   * Save a presence condition that is the union of all presence
   * conditions.
   */
  public void setSaveErrorCond(boolean b) {
    saveErrorCond = b;
  }

  /**
   * Get the current parse error condition.
   */
  public PresenceCondition getErrorCond() {
    return this.errorCond.addRef();
  }

  /**
   * Save layout tokens or not.  Default is off.
   *
   * @param b True is on.
   */
  public void saveLayoutTokens(boolean b) {
    saveLayoutTokens = b;
  }

  /**
   * Set lazy forking on or off.  The default is on.
   *
   * @param b True is on.
   */
  public void setLazyForking(boolean b) {
    optimizeLazyForking = b;
  }

  /**
   * Set shared reductions on or off.  The default is on.
   *
   * @param b True is on.
   */
  public void setSharedReductions(boolean b) {
    optimizeSharedReductions = b;
    setComparator();
  }

  /**
   * Set early reduces on or off.  The default is on.
   *
   * @param b True is on.
   */
  public void setEarlyReduce(boolean b) {
    optimizeEarlyReduce = b;
    setComparator();
  }

  /**
   * Set longest stack ordering on or off.  The default is off.
   *
   * @param b True is on.
   */
  public void setLongestStack(boolean b) {
    optimizePlatoffOrdering = b;
  }

  /**
   * Set early shifts on or off.  The default is off.
   *
   * @param b True is on.
   */
  public void setEarlyShift(boolean b) {
    deoptimizeEarlyShift = b;
  }

  /**
   * Switch between the optimized or configurable subparser comparator
   * based on the current optimization settings.
   */
  private void setComparator() {
    if (optimizeEarlyReduce && ! optimizePlatoffOrdering
        && ! deoptimizeEarlyShift) {
      subparserComparator = subparserComparatorOptimized;
    } else {
      subparserComparator = subparserComparatorConfigurable;
    }
  }

  /**
   * Set follow-set caching on or off.  The default is on.
   *
   * @param b True is on.
   */
  public void setFollowSetCaching(boolean b) {
    optimizeFollowSetCaching = b;
    if (optimizeFollowSetCaching && null == followCache) {
      followCache = new HashMap<Integer, Collection<Lookahead>>();
    }
  }

  /**
   * Turn parser statistics collection on.  Default is off.
   *
   * @param b True is on.
   */
  public void collectStatistics(boolean b) {
    parserStatistics = b;
  }

  /**
   * Set C productions to track for conditionals.
   *
   * @param trackedProductions The productions to track.
   */
  public void conditionGranularity(boolean b) {
    trackedProductions = new HashSet<String>();
    trackedProductions.add("Declaration");
    trackedProductions.add("LabeledStatement");    // Statements
    trackedProductions.add("CompoundStatement");
    trackedProductions.add("ExpressionStatement");
    trackedProductions.add("SelectionStatement");
    trackedProductions.add("IterationStatement");
    trackedProductions.add("JumpStatement");
    trackedProductions.add("AssemblyStatement");
    trackedProductions.add("AssemblyDefinition");  // ExternalDeclarations
    trackedProductions.add("FunctionPrototype");
    trackedProductions.add("FunctionOldPrototype");
    trackedProductions.add("EmptyDefinition");
    conditionGranularity = b;
  }

  /**
   * Enable conditional tracking for all productions.
   *
   * @param b True means to track conditional productions.
   * @param trackAll True means to track all productions.
   * @param afterSetb True means to emit the conditional after-set 
   * of productions when conditional inside-set is empty
   */
  public void conditionGranularity(boolean b, boolean trackAll, boolean afterSetb) {
    conditionGranularity = b;
    trackAllProductions = trackAll;
    emitConditionalAfterSet = afterSetb;
  }

  /**
   * Show parsing actions taken.  Default is off.
   *
   * @param b True is on.
   */
  public void showActions(boolean b) {
    showActions = b;
  }

  /**
   * Show parsing errors.  Default is on.
   *
   * @param b True is on.
   */
  public void showErrors(boolean b) {
    showErrors = b;
  }

  /**
   * Show accept actions.  Default is off.
   *
   * @param b True is on.
   */
  public void showAccepts(boolean b) {
    showAccepts = b;
  }

  /**
   * Show forks and merges.  Default is off.
   *
   * @param b True is on.
   */
  public void showFM(boolean b) {
    showFM = b;
  }

  /**
   * Show lookaheads on each parse loop.  Default is off.
   *
   * @param b True is on.
   */
  public void showLookaheads(boolean b) {
    showLookaheads = b;
  }

  /**
   * Set a kill-switch.  The parser will stop after the given number
   * of seconds.
   *
   * @param cutoff The number of seconds to stop after.
   */
  public void setKillSwitch(int cutoff) {
    assert cutoff > 0;
    killswitch = true;
    killswitchCutoff = cutoff;
  }

  /**
   * Set the plugin for the semantic actions of the language.
   *
   * @param semanticActions The semantic actions implementation.
   */
  private void setSemanticActions(SemanticActions semanticActions) {
    this.semanticActions = semanticActions;
    this.hasSemanticActions = semanticActions != null ? true : false;
  }

  /**
   * Set the initial parsing context, if the language to be parsed is
   * context-sensitive.
   *
   * @param parsingContext The initial parsing context.
   */
  private void setInitialContext(ParsingContext parsingContext) {
    this.initialParsingContext = parsingContext;
    this.hasParsingContext = parsingContext != null ? true : false;
  }

  /**
   * This comparator enforces the subparser set ordering policy and
   * can be configured to add or remove optimizations.
   */
  private Comparator<Subparser> subparserComparatorConfigurable
    = new Comparator<Subparser>() {
    public int compare(Subparser o1, Subparser o2) {
      int result = o1.lookahead.token.order - o2.lookahead.token.order;

      if (0 == result) {
        if (optimizeEarlyReduce) {
          // Put reduces first.
          if (ParsingAction.SHIFT == o1.lookahead.getAction()) {
            return 1;
          } else if (ParsingAction.SHIFT == o2.lookahead.getAction()) {
            return -1;
          } else if (optimizePlatoffOrdering) {
            // Reduce with longer stack goes first.
            return o1.stack.getHeight() >= o2.stack.getHeight() ? -1 : 1;
          }
        } else if (optimizePlatoffOrdering) {
          if (ParsingAction.REDUCE == o1.lookahead.getAction()
              && ParsingAction.REDUCE == o2.lookahead.getAction()) {
            return o1.stack.getHeight() >= o2.stack.getHeight() ? -1 : 1;
          }
        } else if (deoptimizeEarlyShift) {
          // Put shifts first.
          if (ParsingAction.SHIFT == o1.lookahead.getAction()) {
            return -1;
          } else if (ParsingAction.SHIFT == o2.lookahead.getAction()) {
            return 1;
          }
        }
      }

      return result;
    }

    public boolean equals(Object o) {
      return this == o;
    }
  };

  /**
   * The fully-optimized subparser set ordering policy comparator
   * method.  Optimizations cannot be turned on or off.
   */
  private Comparator<Subparser> subparserComparatorOptimized
    = new Comparator<Subparser>() {
    public int compare(Subparser o1, Subparser o2) {
      int result = o1.lookahead.token.order - o2.lookahead.token.order;

      if (0 == result) {
        // // Handle errors last to allow merging with shifting parsers
        // if (ParsingAction.ERROR == o1.lookahead.action) {
        //   return 1;
        // } else if (ParsingAction.ERROR == o2.lookahead.action) {
        //   return -1;
        // }

        // // Do early reduces by default.
        // if (ParsingAction.SHIFT == o1.lookahead.action) {
        //   return 1;
        // } else if (ParsingAction.SHIFT == o2.lookahead.action) {
        //   return -1;
        // }

        switch (o1.lookahead.action) {
        case SHIFT:
        case ERROR:
          return 1;
        }
        switch (o2.lookahead.action) {
        case SHIFT:
        case ERROR:
          return -1;
        }
      }

      return result;
    }

    public boolean equals(Object o) {
      return this == o;
    }
  };

  /**
   * Parse the syntax stream.
   *
   * @return The AST.
   */
  public Object parse() {
    // Create initial subparser.
    OrderedSyntax startOfFile = new OrderedSyntax(stream);
    Subparser firstSubparser
      = new Subparser(new Lookahead(startOfFile,
                                    presenceConditionManager.newTrue()), 
                      new StackFrame(STARTSTATE, 0, null, null),
                      presenceConditionManager.newTrue(),
                      initialParsingContext);
    firstSubparser.lookahead.token = firstSubparser.lookahead.token.getNext();
    
    // Initialize subparser set.
    PriorityQueue<Subparser> subparsers
      = new PriorityQueue<Subparser>(11, subparserComparator);
    subparsers.add(firstSubparser);

    if (parserStatistics) {
      // Initialize statistics collection.
      iterations = 0;
      nsubparsers = new HashMap<Integer, Integer>();
      nfollow = 0;
      lazyForks = 0;
      lazyForksEmptyBranches = 0;
      emptyConditionals = new HashMap<Integer, Boolean>();
    }

    // Initialize the list of processed subparsers, added back to the
    // subparser set after each iteration of the parsing loop.
    LinkedList<Subparser> processedParsers = new LinkedList<Subparser>();

    // Instantiate the followSet collection.
    Collection<Lookahead> followSet = new LinkedList<Lookahead>();

    // Last subparser count
    int lastSubparserCount = 0;

    // Main parsing loop.
    while (true) {
      // Get earliest token.  Since subparsers is ordered, we just get
      // the first subparser in the list's token.
      OrderedSyntax earliestToken = subparsers.peek().lookahead.token;
      // The subparser should always be on a token or conditional.
      assert earliestToken.syntax.kind() == Kind.CONDITIONAL
        && earliestToken.syntax.toConditional().tag()
        == ConditionalTag.START
        || earliestToken.syntax.kind() == Kind.LANGUAGE
        || earliestToken.syntax.kind() == Kind.EOF
        || earliestToken.syntax.kind() == Kind.ERROR;

      // True when at least one subparser reduced in this iteration.
      // Used to delay shifts when the earlyReduce optimization is on.
      boolean seenReduce = false;

      // True when a subparser is on a conditional but hasn't yet had
      // its follow-set computed.  Used to delay forking until all
      // subparsers are ready when the lazyFork optimization is on.
      // earlyReduce makes this unnecessary.
      boolean waitToFork = false;

      if (showFM & lastSubparserCount != subparsers.size()) {
        System.err.println("subparsers " + subparsers.size());
        lastSubparserCount = subparsers.size();
      }

      if (showLookaheads) {
        System.err.println("subparser lookaheads");
        for (Subparser s : subparsers) {
          System.err.println(s.stack.state + " " + s.lookahead);
        }
      }

      // Process each subparser on that is at earliestToken.
      while (subparsers.size() > 0 && (subparsers.peek().lookahead.token.order
                                       - earliestToken.order) == 0) {
        if (optimizeEarlyReduce && seenReduce &&
            (subparsers.peek().lookahead.getAction() == ParsingAction.SHIFT ||
             subparsers.peek().lookahead.getAction() == ParsingAction.ERROR)) {
          // Do reduces first.
          break;
        }

        // Process one subparser.
        Subparser subparser = subparsers.poll();

        if (ParsingAction.ERROR == subparser.lookahead.action) {
          if (handleError(subparser)) {
            processedParsers.add(subparser);
          }
        } else if (subparser.lookahead.isSet()) {
          // Process a multi-headed subparser.
          switch (subparser.lookahead.getAction()) {
          case REDUCE:
            // Shared reduce.
            reduce(subparser);
            seenReduce = true;
            waitToFork = true;

            // Recompute subparser heads if parsing actions changed.
            boolean repartition = false;
            int lastProduction = -1;
            for (Lookahead n : ((LookaheadSet) subparser.lookahead).set) {
              getAction(n, subparser.stack);
              if (ParsingAction.REDUCE != n.getAction()
                  || -1 != lastProduction
                  && n.getActionData() != lastProduction) {
                repartition = true;
                break;
              }
              lastProduction = n.getActionData();
            }

            if (repartition) {
              LookaheadSet lookaheadSet = (LookaheadSet) subparser.lookahead;
              Collection<Lookahead> tokenSet
                = partition(lookaheadSet.set, subparser);

              processedParsers.addAll(fork(subparser, tokenSet));

              // Free the subparser's presence condition.
              subparser.lookahead.presenceCondition.delRef();

              // Don't free presence conditions from the follow-set,
              // since all are part of new subparser heads.
              subparser.presenceCondition.delRef();
              if (hasParsingContext) {
                subparser.scope.free();
              }
            } else {
              // Update the subparser's parsing action.
              subparser.lookahead
                .copyAction(((LookaheadSet) subparser.lookahead).set.get(0));
              processedParsers.add(subparser);
            }
            break;

          case SHIFT:
            if (waitToFork) {
              processedParsers.add(subparser);
            } else {
              // Lazy fork.
              Collection<Lookahead> set;

              if (subparser.lookahead.token.syntax.kind()
                  == Kind.CONDITIONAL) {
                set = lazyFork((LookaheadSet) subparser.lookahead);
              } else {
                // Can't lazy fork Implicit conditionals.
                set = ((LookaheadSet) subparser.lookahead).set;
              }
              processedParsers.addAll(fork(subparser, set));

              // Free the subparser's presence condition.
              subparser.lookahead.presenceCondition.delRef();
              // Don't free presence conditions from the follow-set,
              // since all are part of new subparser heads.
              subparser.presenceCondition.delRef();
              if (hasParsingContext) {
                subparser.scope.free();
              }
            }
            break;

          default:
            throw new RuntimeException("fatal error: invalid parsing action "
                                       + "on multi-headed subparser");
          }
        } else {  // Process a single-headed subparser.
          // Compute the follow-set.
          switch (subparser.lookahead.token.syntax.kind()) {
          case EOF:
            // Fall through
          case ERROR:
            // Fall through
          case LANGUAGE:
            followSet.clear();
            followSet
              .add(new Lookahead(subparser.lookahead.token,
                                 subparser.presenceCondition.addRef()));
            break;

          case CONDITIONAL:
            if (optimizeFollowSetCaching) {
              Collection<Lookahead> cachedFollowSet;

              if (hasCachedSet(subparser.lookahead.token)) {
                cachedFollowSet = getCachedSet(subparser.lookahead.token);
              } else {
                PresenceCondition T
                  = presenceConditionManager.newTrue();

                cachedFollowSet
                  = follow(subparser.lookahead.token, T).values();
                T.delRef();
                setCachedSet(subparser.lookahead.token, cachedFollowSet);
              }

              // Combine follow-set presence conditions with the
              // subparser's.
              followSet.clear();
              for (Lookahead n : cachedFollowSet) {
                PresenceCondition and
                  = subparser.presenceCondition.and(n.presenceCondition);

                if (and.isFalse()) {
                  // Trim infeasible tokens.
                  and.delRef();
                } else {
                  followSet.add(new Lookahead(n.token, and));
                }
              }
            } else {
              // No follow-set caching.
              followSet = follow(subparser.lookahead.token,
                                 subparser.presenceCondition).values();
            }
            break;

          default:
            throw new UnsupportedOperationException();
          }

          // Reclassify tokens with parsing context.
          if (hasParsingContext
              && subparser.scope.shouldReclassify(followSet)) {
            Collection<Lookahead> newTokens
              = subparser.scope.reclassify(followSet);
            if (null != newTokens) {
              Collection<Lookahead> newSet = new LinkedList<Lookahead>();
              newSet.addAll(followSet);
              newSet.addAll(newTokens);
              followSet = newSet;
            }
          }

          if (followSet.size() == 1) {  // Regular LR
            // Update subparser with reclassified token.
            subparser.lookahead.presenceCondition.delRef();
            subparser.lookahead = followSet.iterator().next();

            getAction(subparser.lookahead, subparser.stack);
            switch (subparser.lookahead.getAction()) {
            case SHIFT:
              shift(subparser);

              // Move to next token or start conditional.
              subparser.lookahead.token = subparser.lookahead.token.getNext();
              while (subparser.lookahead.token.syntax.kind()
                     == Kind.CONDITIONAL
                     && subparser.lookahead.token.syntax.toConditional().tag
                     != ConditionalTag.START) {
                Conditional conditional
                  = subparser.lookahead.token.syntax.toConditional();
                switch (conditional.tag()) {
                case START:
                  // Done
                  break;
                case NEXT:
                  subparser.lookahead.token
                    = skipConditional(subparser.lookahead.token);
                  break;
                case END:
                  subparser.lookahead.token
                    = subparser.lookahead.token.getNext();
                  break;
                default:
                  throw new UnsupportedOperationException();
                }
              }

              if (conditionGranularity) {
                if (subparser.lookahead.token.syntax.kind() == Kind.CONDITIONAL
                    && subparser.lookahead.token.syntax.toConditional().tag()
                    == ConditionalTag.START) {
                  subparser.stack.conditionalAfter = true;
                  subparser.stack.afterSet.add(subparser.lookahead.token.
                                               syntax.getLocation() + "");
                }
              }

              if (hasParsingContext
                  && subparser.scope.shouldReclassify(followSet)) {
                subparser.lookahead.clearAction();
              } else if (subparser.lookahead.token.syntax.kind()
                         == Kind.LANGUAGE
                         || subparser.lookahead.token.syntax.kind()
                         == Kind.EOF) {
                getAction(subparser.lookahead, subparser.stack);
              } else {
                subparser.lookahead.clearAction();
              }
              processedParsers.add(subparser);
              break;

            case REDUCE:
              reduce(subparser);
              seenReduce = true;
              getAction(subparser.lookahead, subparser.stack);
              processedParsers.add(subparser);
              break;

            case ACCEPT:
              accepted.add(subparser);
              if (showAccepts) {
                System.err.println("ACCEPT");
              }
              break;

            case ERROR:
              if (handleError(subparser)) {
                processedParsers.add(subparser);
              }
              break;
            }
          } else if (followSet.size() > 1) {  // Fork subparsers.
            assert subparser.lookahead.token.syntax.kind() == Kind.LANGUAGE
              || subparser.lookahead.token.syntax.toConditional().tag()
              == ConditionalTag.START;

            Collection<Lookahead> tokenSet = partition(followSet, subparser);

            processedParsers.addAll(fork(subparser, tokenSet));
            waitToFork = true;

            // Free old subparser's presence condition.
            subparser.lookahead.presenceCondition.delRef();
            subparser.presenceCondition.delRef();
            if (hasParsingContext) {
              subparser.scope.free();
            }
          } else {
            throw new RuntimeException("fatal error: follow-set was 0");
          }
        }
      }

      for (Subparser subparser : processedParsers) {
        subparsers.add(subparser);
      }
      processedParsers.clear();

      if (subparsers.size() == 0) {
        // Done.
        break;
      }

      // Merge subparsers.
      if (subparsers.size() > 1) {
        stagedMerge(subparsers);
      }

      if (parserStatistics && ! waitToFork) {
        iterations++;
        if (! nsubparsers.containsKey(subparsers.size())) {
          nsubparsers.put(subparsers.size(), 0);
        }
        nsubparsers.put(subparsers.size(),
                        nsubparsers.get(subparsers.size()) + 1);
      }
    }

    if (parserStatistics) {
      int max = 0;
      System.err.println(String.format("iterations %d", iterations));
      for (Integer size : nsubparsers.keySet()) {
        if (size > max) max = size;

        System.err.println(String.format("subparsers %d %d", size, nsubparsers.get(size)));
      }
      System.err.println(String.format("max_subparsers %d", max)); 
      System.err.println(String.format("follow %d", nfollow)); 
      System.err.println(String.format("lazy_forks %d %d",
                          lazyForks,
                          lazyForksEmptyBranches));

      int empty = 0;
      for (Integer i : emptyConditionals.keySet()) {
        if (emptyConditionals.get(i)) {
          empty++;
        }
      }
      System.err.println(String.format("empty_conditionals %d %d",
                          emptyConditionals.size(),
                          empty)); 
    }

    if (subparsers.size() > 0) {
      throw new RuntimeException("need to handle remaining error subparsers");
    }

    if (accepted.size() == 0) {
      return null;
    } else {
      // Merge the accepted subparsers.
      accepted = merge(accepted);
      if (accepted.size() == 1) {
        return (Node) accepted.get(0).stack.value;
      } else {
        // Combine the semantic values of the accepted subparsers.
        Node root = GNode.create(CHOICE_NODE_NAME);

        for (Subparser subparser : accepted) {
          root.add(subparser.presenceCondition.addRef());
          root.add(subparser.stack.value);

          // Free presence conditions.
          subparser.lookahead.presenceCondition.delRef();
          subparser.presenceCondition.delRef();
          if (hasParsingContext) {
            subparser.scope.free();
          }
        }

        return root;
      }
    }
  }

  /**
   * Handle a subparser in an error state.
   *
   * @return true to keep the subparser, false to throw it away.
   */
  public boolean handleError(Subparser subparser) {
    if (showErrors) {
      error("parse error on "
            + (subparser.lookahead.token.syntax.kind()
               == Kind.EOF ? "EOF"
               : "\"" + subparser.lookahead.token.syntax + "\"")
            + " at "
            + subparser.lookahead.token.syntax.getLocation());
    }

    // if (SAVE_ERROR_COND) {
    //   PresenceCondition or = this.invalid.or(subparser.getPresenceCondition());
    //   this.invalid.delRef();
    //   this.invalid = or;
    // }

    if (newErrorHandling) {
      //if the error subparser still exists at EOF, it can't merge and should end.
      if (subparser.lookahead.token.syntax.kind() == Kind.EOF) {
        PresenceCondition newErrorCond = this.errorCond.or(subparser.getPresenceCondition());
        this.errorCond.delRef();
        this.errorCond = newErrorCond;
        return false;
      }
      // Move to the next token or start conditional.
      subparser.lookahead.token
        = subparser.lookahead.token.getNext();
      while (subparser.lookahead.token.syntax.kind()
             == Kind.CONDITIONAL
             && subparser.lookahead.token.syntax.toConditional().tag
             != ConditionalTag.START) {
        Conditional conditional
          = subparser.lookahead.token.syntax.toConditional();

        switch (conditional.tag()) {
        case START:
          // Done
          break;
        case NEXT:
          subparser.lookahead.token
            = skipConditional(subparser.lookahead.token);
          break;
        case END:
          subparser.lookahead.token
            = subparser.lookahead.token.getNext();
          break;
        default:
          throw new UnsupportedOperationException();
        }
      }
      
      return true;
    } else {
      // Free presence conditions.
      subparser.lookahead.presenceCondition.delRef();
      subparser.presenceCondition.delRef();
      if (hasParsingContext) {
        subparser.scope.free();
      }

      return false;
    }
  }

  /**
   * Parse the syntax stream.
   *
   * @return The AST.
   */
  public Object parseNaively() {
    // Create initial subparser.
    OrderedSyntax startOfFile = new OrderedSyntax(stream);
    Subparser firstSubparser =
      new Subparser(new Lookahead(startOfFile,
                                  presenceConditionManager.newTrue()), 
                    new StackFrame(STARTSTATE, 0, null, null),
                    presenceConditionManager.newTrue(),
                    initialParsingContext);
    firstSubparser.lookahead.token = firstSubparser.lookahead.token.getNext();

    // Initialize subparser set.
    PriorityQueue<Subparser> subparsers
      = new PriorityQueue<Subparser>(11, subparserComparator);
    subparsers.add(firstSubparser);

    // Create AST root node.
    GNode root = GNode.create(CHOICE_NODE_NAME);

    if (parserStatistics) {
      // Initialize statistics collection.
      iterations = 0;
      nsubparsers = new HashMap<Integer, Integer>();
      nfollow = 0;
    }

    // Main parsing loop.
    while (true) {
      if (killswitch && subparsers.size() >= killswitchCutoff) {
        if (parserStatistics) {
          System.err.println(String.format("killswitch_subparsers %d",
                                           subparsers.size()));
        }
        throw new RuntimeException(String
                                   .format("kill-switch tripped because "
                                           + "subparsers reached %d",
                                           subparsers.size()));
      }

      if (parserStatistics) {
        iterations++;
        if (! nsubparsers.containsKey(subparsers.size())) {
          nsubparsers.put(subparsers.size(), 0);
        }
        nsubparsers.put(subparsers.size(),
                        nsubparsers.get(subparsers.size()) + 1);
      }

      // Get earliest token.  Since subparsers is ordered, we just get
      // the first subparser in the list's token.
      OrderedSyntax earliestToken = subparsers.peek().lookahead.token;

      // Each subparser should be on a token or conditional directive.
      assert earliestToken.syntax.kind() == Kind.CONDITIONAL
        && (earliestToken.syntax.toConditional().tag()
            == ConditionalTag.START
            || earliestToken.syntax.toConditional().tag()
            == ConditionalTag.NEXT
            || earliestToken.syntax.toConditional().tag()
            == ConditionalTag.END)
        || earliestToken.syntax.kind() == Kind.LANGUAGE
        || earliestToken.syntax.kind() == Kind.EOF;

      // Initialize the list of processed subparsers, added back to the
      // subparser set after each iteration of the parsing loop.
      LinkedList<Subparser> processedParsers = new LinkedList<Subparser>();

      // Process each subparser on that is at earliestToken.
      while (subparsers.size() > 0 && (subparsers.peek().lookahead.token.order
                                       - earliestToken.order) == 0) {
        // Process on subparser.
        Subparser subparser = subparsers.poll();

        // Reclassify tokens according to parsing context.
        if (hasParsingContext && subparser.lookahead.token.syntax.kind()
            == Kind.LANGUAGE) {

          // Create new list, add token.  Need to fork immediately if
          // there are new tokens here.

          LinkedList<Lookahead> set = new LinkedList<Lookahead>();

          set.add(subparser.lookahead);

          Collection<Lookahead> newTokens
            = subparser.scope.reclassify(set);

          if (null != newTokens) {
            // There were new tokens during reclassification.  Fork
            // new subparsers immediately.

            processedParsers.addAll(fork(subparser, newTokens));
          }
        }


        if (subparser.lookahead.token.syntax.kind() == Kind.LANGUAGE
            || subparser.lookahead.token.syntax.kind() == Kind.EOF) {

          // Regular LR.

          getAction(subparser.lookahead, subparser.stack);

          switch (subparser.lookahead.getAction()) {
          case SHIFT:
            shift(subparser);

            // Move to the next ordinary token or start conditional
            // (#if).  If the next token ends a branch (#elif or
            // #endif), move to the next ordinary token or start
            // conditional after the conditional.

            subparser.lookahead.token = subparser.lookahead.token.getNext();

            while (subparser.lookahead.token.syntax.kind() == Kind.CONDITIONAL
                   && subparser.lookahead.token.syntax.toConditional().tag
                   != ConditionalTag.START) {
              Conditional conditional = subparser.lookahead.token.syntax.toConditional();

              switch (conditional.tag()) {
              case START:
                // No need to move.
                break;

              case NEXT:
                subparser.lookahead.token = skipConditional(subparser.lookahead.token);
                break;

              case END:
                subparser.lookahead.token = subparser.lookahead.token.getNext();
                break;

              default:
                // No such conditional tag.
                throw new UnsupportedOperationException();
              }
            }


            // We no longer know what the next parsing action is.
            // The next token could be either an ordinary token or a
            // conditional.  The action can be used for subparser
            // ordering, so not clearing it can lead to incorrect
            // results.
              
            subparser.lookahead.clearAction();

            // Re-add the subparser to the ordered set to update its
            // position in the set.

            processedParsers.add(subparser);

            break;

          case REDUCE:

            reduce(subparser);

            // We no longer know what the next parsing action is.
            // The next token could be either an ordinary token or a
            // conditional.  The action can be used for subparser
            // ordering, so not clearing it can lead to incorrect
            // results.
              
            subparser.lookahead.clearAction();


            // Re-add the subparser to the ordered set to update its
            // position in the set.

            processedParsers.add(subparser);

            break;

          case ACCEPT:

            root.add(subparser.presenceCondition.addRef());
            root.add(subparser.stack.value);


            // Clean up subparser scope and presenceCondition.  We will not add
            // it back to the main set of subparsers.

            subparser.lookahead.presenceCondition.delRef();
            subparser.presenceCondition.delRef();
            if (hasParsingContext) {
              subparser.scope.free();
            }

            if (showAccepts) {
              System.err.println("ACCEPT");
            }

            break;

          case ERROR:

            // Clean up subparser scope and presenceCondition.  We will not add
            // it back to the main set of subparsers.

            subparser.lookahead.presenceCondition.delRef();
            subparser.presenceCondition.delRef();
            if (hasParsingContext) {
              subparser.scope.free();
            }

            if (showErrors) {
              error("parse error on "
                    + (subparser.lookahead.token.syntax.kind() == Kind.EOF ?
                       "EOF" : "\"" + subparser.lookahead.token.syntax + "\"")
                    + " at " + subparser.lookahead.token.syntax.getLocation());
            }

            break;
          }

        } else if (subparser.lookahead.token.syntax.kind() == Kind.CONDITIONAL) {

          switch (subparser.lookahead.token.syntax.toConditional().tag()) {
          case START:

            // Fork subparsers on the conditional.

            // Get the first token in each branch of the conditional.
            // Move to #endif if any branches are empty.

            Collection<Lookahead> tokenSet = new LinkedList<Lookahead>();

            OrderedSyntax a = subparser.lookahead.token;


            // Save the presence conditions of all empty branches.

            PresenceCondition emptyConditions = presenceConditionManager.newFalse();


            // The union of the branches conditions.  Used to determine
            // whether there is an implicit else branch or not.

            PresenceCondition union = a.syntax.toConditional().presenceCondition.addRef();


            // Loop through each branch of the conditional, find the
            // first token of each.

            while (! (a.syntax.kind() == Kind.CONDITIONAL
                      && a.syntax.toConditional().tag()
                      == ConditionalTag.END)) {

              // Get the presence condition of the branch.  It is
              // conjoined with the presence condition in which it is
              // nested.

              PresenceCondition nestedPresenceCondition
                = subparser.presenceCondition.and(a.syntax.toConditional().presenceCondition);


              // a is on the conditional starting the branch.  Get the
              // first the token after the one starting the branch.  It
              // will either be the first token in the branch, or the
              // token that ends the branch.

              a = a.getNext();

              if (a.syntax.kind() == Kind.CONDITIONAL
                  && (a.syntax.toConditional().tag()
                      == ConditionalTag.NEXT
                      || a.syntax.toConditional().tag()
                      == ConditionalTag.END)) {

                // The branch is empty.

                PresenceCondition or = emptyConditions.or(nestedPresenceCondition);

                emptyConditions.delRef();
                emptyConditions = or;

              } else {

                // We have the first token in a non-empty branch.

                tokenSet.add(new Lookahead(a,
                                           nestedPresenceCondition.addRef()));

              }

              nestedPresenceCondition.delRef();

              // Skip ahead to the next branch or stop when we find the
              // #endif

              while (true) {

                // If we have reached the next branch or are at the end
                // of the conditional, then leave the loop.

                if (a.syntax.kind() == Kind.CONDITIONAL
                    && (a.syntax.toConditional().tag() == ConditionalTag.NEXT
                        || a.syntax.toConditional().tag()
                        == ConditionalTag.END)) {
                  break;
                }


                // a is now a language token or a start conditional.
                // Move to the next token.

                if (a.syntax.kind() == Kind.CONDITIONAL) {
                  assert a.syntax.toConditional().tag() == ConditionalTag.START
                    || a.syntax.toConditional().tag() == ConditionalTag.NEXT;
                  a = skipConditional(a);
                } else {
                  a = a.getNext();
                }
              }


              // We are now on a next branch or an endif.

              if (a.syntax.kind() == Kind.CONDITIONAL
                  && a.syntax.toConditional().tag() == ConditionalTag.END) {

                // On an #endif we are done.

                break;

              } else {

                // It must be a NEXT conditional.

                assert a.syntax.toConditional().tag() == ConditionalTag.NEXT;


                // Update the union of branch presence conditions.

                PresenceCondition newUnion = union.or(a.syntax.toConditional().presenceCondition);
                union.delRef();
                union = newUnion;
              }
            }


            // Discover whether there is an implicit-else or not.  To do
            // this, we check the union of all branches conditions
            // against the presence condition (presenceCondition) of the
            // current subparser.
            //
            // union.not() is the condition of the implicit else.  If it
            // is always false under the current presence condition,
            // then there is no implicit else.

            PresenceCondition elseBranch = subparser.presenceCondition.andNot(union);
            union.delRef();


            if (! elseBranch.isFalse()) {

              // Save the presence condition of the empty, implicit
              // else.

              PresenceCondition or = emptyConditions.or(elseBranch);
              emptyConditions.delRef();
              emptyConditions = or;
            }

            elseBranch.delRef();
            

            if (! emptyConditions.isFalse()) {
              // We need to fork a subparser that sits on #endif,
              // because their were empty branches.

              tokenSet.add(new Lookahead(a, emptyConditions));
            } else {
              emptyConditions.delRef();
            }


            // Fork and replace the subparser with newly-forked
            // subparsers, one for each token in the follow set.

            processedParsers.addAll(fork(subparser, tokenSet));


            // Clean up subparser scope and presenceCondition.  It is removed
            // from the set of subparsers.

            subparser.lookahead.presenceCondition.delRef();
            subparser.presenceCondition.delRef();
            if (hasParsingContext) {
              subparser.scope.free();
            }

            break;

          case NEXT:

            // Move on and reschedule the subparser.

            subparser.lookahead.token = skipConditional(subparser.lookahead.token);

            processedParsers.add(subparser);
            break;

          case END:

            // Move on and reschedule the subparser.

            subparser.lookahead.token = subparser.lookahead.token.getNext();

            processedParsers.add(subparser);
            break;

          default:
            // Can only be #if or #endif.
            throw new RuntimeException();
          }
        } else {
          // The subparser can only be on LANGUAGE, EOF, and
          // CONDITIONAL tokens.
          throw new RuntimeException();
        }
      }

      // Add the updated subparsers into the priority queue of
      // subparsers.
      for (Subparser subparser : processedParsers) {
        subparsers.add(subparser);
      }

      if (subparsers.size() == 0) {
        // Done
        break;
      }

      // Merge subparsers.  We only need check the earliest subparsers for
      // a merge.
      if (subparsers.size() > 1) {
        stagedMerge(subparsers);
      }
    }


    if (parserStatistics) {
      int max = 0;
      System.err.println(String.format("iterations %d", iterations));
      for (Integer size : nsubparsers.keySet()) {
        if (size > max) max = size;

        System.err.println(String.format("subparsers %d %d",
                                         size, nsubparsers.get(size)));
      }
      System.err.println(String.format("max_subparsers %d", max)); 
      System.err.println(String.format("follow %d", nfollow)); 
    }

    if (hasParsingContext) {
      initialParsingContext.free();
    }

    return root;
  }

  /**
   * Find the FOLLOW set of a given token.  When the given token is an
   * ordinary token, the set is just the token alone.  But when the
   * token is a conditional, this method returns the set of ordinary
   * tokens reachable from this conditional in all configurations.
   *
   * @param a The token to find the follow set of.
   * @param presenceCondition The presence condition of a.  This
   * presence condition will be freed, so pass a reference.
   * @return The follow set of the given token.
   */
  public Map<Integer, Lookahead> follow(OrderedSyntax a,
                                        PresenceCondition presenceCondition) {
    Map<Integer, Lookahead> result = new HashMap<Integer, Lookahead>();

    presenceCondition.addRef();
    if (parserStatistics) {
      nfollow++;
    }
    while (true) {
      // Call FIRST.
      PresenceCondition emptyCondition = first(result, a, presenceCondition);

      // Continue searching with the empty branches' condition.
      presenceCondition.delRef();
      presenceCondition = emptyCondition;

      if (presenceCondition.isFalse()) {
        // Done.
        presenceCondition.delRef();
        return result;
      }

      // Get next token, stepping out of conditionals.
      do {
        switch (a.syntax.kind()) {
        case LANGUAGE:
          a = a.getNext();
          break;

        case CONDITIONAL:
          Conditional conditional = a.syntax.toConditional();

          switch (conditional.tag()) {
          case START:
            a = skipConditional(a);
            break;
          case NEXT:
            a = skipConditional(a);
            break;
          case END:
            a = a.getNext();
            break;
          default:
            throw new UnsupportedOperationException();
          }
          break;

        default:
          throw new RuntimeException("FMLR only takes language " +
                                     "and conditional tokens.");
        }
        // Until a does not end a branch.
      } while (a.syntax.kind() == Kind.CONDITIONAL &&
               (a.syntax.toConditional().tag() == ConditionalTag.NEXT
                || a.syntax.toConditional().tag() == ConditionalTag.END));
    }
  }

  /**
   * Find the FIRST set of a given token.  An ordinary token has
   * itself and only itself in its first set.  For a conditional, the
   * first set has the first token in each branch.  If there are empty
   * branches, it returns the presence condition of the empty
   * branches, which indicates that the follow set computation needs
   * to continue populating the follow set.
   *
   * This is a helper routine for follow.  It assumes conditionals are
   * well-formed.
   *
   * @param result The follow-set found so far.
   * @param a The token for which to find the first-set.
   * @param presenceCondition The presence condition of a.
   * @return The presence condition of empty branches.  It is
   * non-false if the follow method should continue looking for
   * tokens.
   */
  private PresenceCondition first(Map<Integer, Lookahead> result,
                                  OrderedSyntax a,
                                  PresenceCondition presenceCondition) {
    presenceCondition.addRef();
    while (true) {
      switch (a.syntax.kind()) {
      case ERROR:
      case EOF:
      case LANGUAGE:
        // Add token to the follow set, or update an existing token's
        // presence condition.
        if (! result.containsKey(a.getSequenceNumber())) {
          result.put(a.getSequenceNumber(),
                     new Lookahead(a, presenceCondition.addRef()));
        } else {
          Lookahead n = result.get(a.getSequenceNumber());
          PresenceCondition union = n.presenceCondition.or(presenceCondition);
          n.presenceCondition.delRef();
          n.presenceCondition = union;
        }
        presenceCondition.delRef();
        return presenceConditionManager.newFalse();

      case CONDITIONAL:
        Conditional conditional = a.syntax.toConditional();

        switch (conditional.tag()) {
        case NEXT:
        case END:
          // Continue looking past the conditional
          return presenceCondition;

        case START:
          // Holds the union of empty branch conditions.
          PresenceCondition emptyConditions
            = presenceConditionManager.newFalse();

          // Holds the union of non-empty branches.
          PresenceCondition union
            = a.syntax.toConditional().presenceCondition.addRef();

          // Find the first token of each branch.
          while (! (a.syntax.kind() == Kind.CONDITIONAL
                    && a.syntax.toConditional().tag()
                    == ConditionalTag.END)) {
            PresenceCondition nestedPresenceCondition = presenceCondition
              .and(a.syntax.toConditional().presenceCondition);

            // Move into the branch.
            a = a.getNext();

            if (nestedPresenceCondition.isFalse()) {
              // Branch is not feasible.
            } else {
              // Recursively find first token.
              PresenceCondition emptyBranch
                = first(result, a, nestedPresenceCondition);

              if (! emptyBranch.isFalse()) {
                // Save the empty branch's presence condition.
                PresenceCondition or = emptyConditions.or(emptyBranch);
                emptyConditions.delRef();
                emptyConditions = or;
              }
              emptyBranch.delRef();
            }
            nestedPresenceCondition.delRef();

            // Go to the next branch or #endif.
            while (true) {
              if (a.syntax.kind() == Kind.CONDITIONAL
                  && (a.syntax.toConditional().tag() == ConditionalTag.NEXT
                      || a.syntax.toConditional().tag()
                      == ConditionalTag.END)) {
                // Done.
                break;
              }

              // On token or start conditional.  Move to next token.
              if (a.syntax.kind() == Kind.CONDITIONAL) {
                assert a.syntax.toConditional().tag() == ConditionalTag.START
                  || a.syntax.toConditional().tag() == ConditionalTag.NEXT;
                a = skipConditional(a);
              } else {
                a = a.getNext();
              }
            }

            if (a.syntax.kind() == Kind.CONDITIONAL
                && a.syntax.toConditional().tag() == ConditionalTag.END) {
              // Done.
              break;
            } else {  // Should be an #elif or #else.
              assert a.syntax.toConditional().tag() == ConditionalTag.NEXT;

              // Update the union of non-empty branch conditions.
              PresenceCondition newUnion
                = union.or(a.syntax.toConditional().presenceCondition);
              union.delRef();
              union = newUnion;
            }
          }

          // Check for implicit else (negation of non-empty branches).
          PresenceCondition elseBranch = presenceCondition.andNot(union);
          union.delRef();
          if (! elseBranch.isFalse()) {
            // Add implicit else to union of empty branches.
            PresenceCondition or = emptyConditions.or(elseBranch);
            emptyConditions.delRef();
            emptyConditions = or;
          }
          elseBranch.delRef();
            
          if (parserStatistics) {
            // Count empty conditionals.  The logic below ensures that
            // if there is at least one time when a conditional is
            // non-empty, the conditional is not marked as empty.
            // This is a more conservative way to count empty
            // conditionals.
            if (emptyConditions.isFalse()) {  // Not empty.
              emptyConditionals.put(a.getSequenceNumber(), false);
            } else {  // Empty.
              if (emptyConditionals.containsKey(a.getSequenceNumber())) {
                emptyConditionals.put(a.getSequenceNumber(),
                                      true && emptyConditionals
                                      .get(a.getSequenceNumber()));
              } else {
                emptyConditionals.put(a.getSequenceNumber(), true);
              }
            }
          }

          if (emptyConditions.isFalse()) {
            // No empty branches.
            presenceCondition.delRef();
            return emptyConditions;
          }

          // Continue searching with the empty branch conditions.
          presenceCondition.delRef();
          presenceCondition = emptyConditions;

          // Move past the #endif.
          a = a.getNext();
          break;

        default:
          throw new UnsupportedOperationException();
        }
        break;

      default:
        throw new UnsupportedOperationException();
      }
    }
  }

  /**
   * Test whether the conditional token already has a follow-set
   * computed.
   *
   * @param t The conditional.
   * @return true if the follow-set is cached.
   */
  public boolean hasCachedSet(OrderedSyntax t) {
    return followCache.containsKey(t.getSequenceNumber());
  }

  /**
   * Get the cached follow-set for a conditional token.
   *
   * @param t The conditional.
   * @return The follow-set.
   */
  public Collection<Lookahead> getCachedSet(OrderedSyntax t) {
    return followCache.get(t.getSequenceNumber());
  }

  /**
   * Cache the conditional token's follow-set.
   *
   * @param t The conditional.
   */
  public void setCachedSet(OrderedSyntax t, Collection<Lookahead> follow) {
    followCache.put(t.getSequenceNumber(), follow);
  }

  /** This holds merged subparsers temporarily. */
  private List<Subparser> processed = new LinkedList<Subparser>();

  /** This holds subparsers that need to be merged. */
  private List<Subparser> subset = new ArrayList<Subparser>();

  /**
   * Merge subparsers in the ordered list.
   *
   * @param subparsers The ordered list of subparsers to check for and
   * perform merges.  This method assumes there is more than one
   * subparser.
   */
  private void stagedMerge(PriorityQueue<Subparser> subparsers) {
    int initialCount = subparsers.size();
    
    // Merge each subset of subparsers on the same token.
    while (! subparsers.isEmpty()) {
      Subparser first = subparsers.poll();

      if (subparsers.isEmpty()
          || (first.lookahead.token.order
              - subparsers.peek().lookahead.token.order) != 0) {
        // Only one subparser in the subset.  Don't merge.
        processed.add(first);
      } else {
        // Get the earliest token.
        OrderedSyntax earliestToken = first.lookahead.token;

        // Get subparsers on earliest token.
        subset.add(first);
        while (! subparsers.isEmpty()
               && (subparsers.peek().lookahead.token.order
                   - earliestToken.order) == 0) {
          subset.add(subparsers.poll());
        }

        // Merge subparsers.
        subset = merge(subset);
        processed.addAll(subset);
        subset.clear();
      }
    }

    for (Subparser subparser : processed) {
      subparsers.add(subparser);
    }

    if (showFM && subparsers.size() < initialCount) {
      System.err.println("merged " + initialCount + " to " + subparsers.size());
      for (Subparser s : subparsers) {
        System.err.println(s);
      }
    }

    processed.clear();
  }

  /** This holds error subparsers. */
  private LinkedList<Subparser> errorParsers = new LinkedList<Subparser>();

  /** This holds shifting subparsers. */
  private LinkedList<Subparser> shiftParsers = new LinkedList<Subparser>();

  /**
   * Merge any error subparsers into non-error subparsers.
   *
   * @param subset The subparsers to merge.  They should all be on the
   * same token
   * @return A subset of subparsers that has either no error
   * subparsers or is all error subparsers.
   */
  private List<Subparser> mergeErrors(List<Subparser> subset) {
    for (int i = 0; i < subset.size(); i++) {
      if (ParsingAction.ERROR == subset.get(i).lookahead.action) {
        errorParsers.add(subset.get(i));
        subset.remove(i);
        i--;
      } else if (ParsingAction.SHIFT == subset.get(i).lookahead.action) {
        shiftParsers.add(subset.get(i));
      }
    }

    if (shiftParsers.size() == 0) {
      subset.addAll(errorParsers);
    } else {
      for (Subparser e : errorParsers) {
        StackFrame mergeFrame = null;
        Subparser mergeParser = null;

        for (Subparser s : shiftParsers) {
          StackFrame estate = e.stack;
          StackFrame sstate = s.stack;

          if (sstate.getHeight() > estate.getHeight()) {
            sstate = sstate.get(sstate.getHeight() - estate.getHeight());
          } else {
            estate = estate.get(estate.getHeight() - sstate.getHeight());
          }

          // while (sstate != estate) {
          //   sstate = sstate.next;
          //   estate = estate.next;
          // }

          if (null == mergeFrame
              || mergeFrame.getHeight() < sstate.getHeight()) {
            mergeFrame = sstate;
            mergeParser = s;
          }
        }

        {
          PresenceCondition newErrorCond = this.errorCond.or(e.presenceCondition);
          this.errorCond.delRef();
          this.errorCond = newErrorCond;
        }
          
        // OR the presence conditions.
        PresenceCondition or
          = mergeParser.presenceCondition.or(e.presenceCondition);
        mergeParser.presenceCondition.delRef();
        mergeParser.presenceCondition = or;

        // Update the subparser's head.
        mergeParser.lookahead.presenceCondition.delRef();
        if (! mergeParser.lookahead.isSet()) {
          mergeParser.lookahead.presenceCondition = or.addRef();
        } else {
          // Clear the subparser's multi-head.
          ((LookaheadSet) mergeParser.lookahead).free();
          mergeParser.lookahead
            = new Lookahead(mergeParser.lookahead.token, or.addRef());
        }
        e.lookahead.presenceCondition.delRef();
        e.presenceCondition.delRef();
        if (hasParsingContext) {
          e.scope.free();
        }
      }
    }
    shiftParsers.clear();
    errorParsers.clear();

    return subset;
  }

  /** This holds merged subparsers. */
  private LinkedList<Subparser> mergedParsers = new LinkedList<Subparser>();

  /**
   * Merge a set of subparsers.  This method assumes that all the
   * subparsers in the input set are on the same token already.
   *
   * @param subset The subparsers to merge.  They should all be on the
   * same token.
   * @param The merged set of subparsers.
   */
  private List<Subparser> merge(List<Subparser> subset) {
    if (newErrorHandling) {
      // First merge errors.
      subset = mergeErrors(subset);
      
      // Stop merging if all subparsers are errors.  Since mergeErrors
      // ensures that all or no subparsers are error subparsers, only
      // check the first one.
      if (ParsingAction.ERROR == subset.get(0).lookahead.action) {
        return subset;
      }
    }

    // Try to merge each pair of subparsers.
    for (int outer = 0; outer < subset.size(); outer++) {
      Subparser subparser = subset.get(outer);

      for (int inner = 0; inner < subset.size(); inner++) {
        Subparser compareParser = subset.get(inner);
        
        if (subparser == compareParser) continue;
        assert subparser.lookahead.token.order
          == compareParser.lookahead.token.order;

        // Check merge criteria: (1) at the same token, (2) tokens are
        // same type, (3) have the same parsing state, (4) their
        // presence conditions are not mutually exclusive, (5) the
        // subparsers weren't just forked, (6) the parsing context, or
        // scopes, can be merged, e.g., same nesting level, (7) the
        // grammar node is considered complete, i.e., non-complete
        // nodes shouldn't be children of conditional nodes
        // (8) errors should not be merged here.
        boolean sameTokenType
          = (subparser.lookahead.token.syntax.kind() == Kind.LANGUAGE
             && subparser.lookahead.token.syntax.toLanguage().tag()
             == compareParser.lookahead.token.syntax.toLanguage().tag())
          || subparser.lookahead.token.syntax.kind() != Kind.LANGUAGE;

        if (sameTokenType                                          // (1,2)
            && semanticValues.isComplete(subparser.stack.symbol)   // (7)
            && (! hasParsingContext
                || subparser.scope.mayMerge(compareParser.scope))  // (6)
            && subparser.stack.isMergeable(compareParser.stack)    // (3,4)
            && subparser.stack != compareParser.stack           // (5)
            && ParsingAction.ERROR != subparser.lookahead.action ) { // (8)
          // Move subparser to merge list.
          mergedParsers.addLast(compareParser);
          subset.remove(inner);
          inner--;

          // Update the index for the next subparser.
          if (inner < outer) {
            outer--;
          }
        }
      }

      // Merge subparsers.  
      if (mergedParsers.size() > 0) {
        // Find the least common ancestor stack frame.
        int maxDist = 0;
        StackFrame s = subparser.stack;

        for (Subparser mergedParser : mergedParsers) {
          int dist = 0;
          StackFrame t = mergedParser.stack;

          while (s != null && s != t) {
            s = s.next;
            t = t.next;
            dist++;
          }

          if (dist > maxDist) {
            maxDist = dist;
          }
        }

        // Duplicate the stack frames up to the least common ancestor.
        subparser.stack = new StackFrame(subparser.stack.state,
                                         subparser.stack.symbol,
                                         subparser.stack.value,
                                         subparser.stack.next);
        StackFrame u = subparser.stack;
        for (int i = 0; i < maxDist - 1; i++) {
          u.next = new StackFrame(u.next.state, u.next.symbol,
                                  u.next.value, u.next.next);
          u = u.next;
        }

        // Combine each stack frame's semantic values, updating the
        // presence condition along the way.
        for (Subparser mergedParser : mergedParsers) {
          subparser.stack.merge(subparser.presenceCondition,
                                mergedParser.stack,
                                mergedParser.presenceCondition,
                                maxDist);

          PresenceCondition or =
            subparser.presenceCondition.or(mergedParser.presenceCondition);
          subparser.presenceCondition.delRef();
          subparser.presenceCondition = or;
        }
        // // Combine the subparsers' presence conditions.
        // PresenceCondition disjunction = subparser.presenceCondition;
        // for (Subparser mergedParser : mergedParsers) {
        //   PresenceCondition or
        //     = disjunction.or(mergedParser.presenceCondition);
        //   disjunction.delRef();
        //   disjunction = or;
        // }
        // subparser.presenceCondition = disjunction;

        // Update the subparser's head.
        subparser.lookahead.presenceCondition.delRef();
        if (! subparser.lookahead.isSet()) {
          subparser.lookahead.presenceCondition =
            subparser.presenceCondition.addRef();
        } else {
          // Clear the subparser's multi-head.
          ((LookaheadSet) subparser.lookahead).free();
          subparser.lookahead =
            new Lookahead(subparser.lookahead.token,
                          subparser.presenceCondition.addRef());
        }

        // Merge parsing contexts.
        if (hasParsingContext) {
          for (Subparser mergedParser : mergedParsers) {
            subparser.scope.merge(mergedParser.scope);
          }
        }

        // Free presence conditions and multi-head sets.
        for (Subparser mergedParser : mergedParsers) {
          mergedParser.lookahead.presenceCondition.delRef();
          if (mergedParser.lookahead.isSet()) {
            ((LookaheadSet) mergedParser.lookahead).free();
          }
          mergedParser.presenceCondition.delRef();
          if (hasParsingContext) {
            mergedParser.scope.free();
          }
        }
        mergedParsers.clear();
      }
    }

    return subset;
  }


  /**
   * Fork subparser on a set of tokens.
   *
   * @param tokenSet The set of tokens.
   * @return A collection of the forked subparsers.
   */
  private Collection<Subparser> fork(Subparser subparser,
                                     Collection<Lookahead> tokenSet) {
    LinkedList<Subparser> processedParsers = new LinkedList<Subparser>();

    for (Lookahead n : tokenSet) {
      Subparser forkedSubparser
        = new Subparser(n,
                        subparser.stack,
                        n.presenceCondition.addRef(),
                        hasParsingContext ? subparser.scope.fork() : null);
      processedParsers.addLast(forkedSubparser);
    }

    if (showFM && processedParsers.size() > 1) {
      System.err.println("forked 1 into " + processedParsers.size() + " parsers");
      System.err.println("\n--into--");
      for (Subparser s : processedParsers) {
        System.err.println(s);
      }
    }

    return processedParsers;
  }

  
  /**
   * Partition the follow-set by shared reductions and create new
   * subparsers for the tokens and token-sets resulting from the
   * partition.
   *
   * @param tokenSet The set of tokens.
   * @param subparser The subparser that is being forked.
   * @return The partitioned set of next tokens.
   */
  private Collection<Lookahead> partition(Collection<Lookahead> tokenSet,
                                          Subparser subparser) {
    Collection<Lookahead> partition = new LinkedList<Lookahead>();
    HashMap<Integer, Lookahead> sharedReductions = null;
    Lookahead shifts = null;

    for (Lookahead n : tokenSet) {
      getAction(n, subparser.stack);
      if (optimizeSharedReductions && ParsingAction.REDUCE == n.getAction()) {
        // Group tokens that reduce the same production.
        if (null == sharedReductions) {
          sharedReductions = new HashMap<Integer, Lookahead>();
        }
        if (sharedReductions.containsKey(n.getActionData())) {
          Lookahead element = sharedReductions.get(n.getActionData());
          LookaheadSet set;

          // Add the token to the shared reduce set.
          if (element.isSet()) {
            set = (LookaheadSet) element;
          } else {
            set = new LookaheadSet(subparser.lookahead.token,
                                   element.presenceCondition.addRef(),
                                   element.getAction(),
                                   element.getActionData()); 
            set.add(element);
            sharedReductions.put(n.getActionData(), set);
          }
          set.add(n);

          // Update the set's presence condition.
          PresenceCondition union
            = set.presenceCondition.or(n.presenceCondition);
          set.presenceCondition.delRef();
          set.presenceCondition = union;
        } else {
          sharedReductions.put(n.getActionData(), n);
        }
      } else if (optimizeLazyForking
                 && ParsingAction.SHIFT == n.getAction()) {
        // Add the token to the set of shifts.
        if (null == shifts) {
          shifts = n;
        } else {
          LookaheadSet set;

          if (shifts.isSet()) {
            set = (LookaheadSet) shifts;
          } else {
            Lookahead element = shifts;
            set = new LookaheadSet(subparser.lookahead.token,
                                   element.presenceCondition.addRef(),
                                   element.getAction(),
                                   element.getActionData()); 
            set.add(element);
            shifts = set;
          }
          set.add(n);

          // Update the set's presence condition.
          PresenceCondition union
            = set.presenceCondition.or(n.presenceCondition);
          set.presenceCondition.delRef();
          set.presenceCondition = union;
        }
      } else {
        // No optimization, so no partition.
        partition.add(n);
      }
    }

    if (null != sharedReductions) {
      partition.addAll(sharedReductions.values());
    }

    if (null != shifts) {
      partition.add(shifts);
    }

    return partition;
  }

  /**
   * Lazily fork the set of shifts.  Partition the set of next tokens
   * into individual tokens for the current conditional and a single
   * token for the ordinary token or start conditional that follows
   * the current conditional.
   *
   * @param tokenSet The set that is being lazily forked.
   * @return The partitioned set of tokens.
   * @throws InvalidCastException if subparser.lookahead is not a LookaheadSet
   * object.
   * @throws IllegalStateException if any next token does not cause a
   * shift action.  It also is thrown if the lazy forking optimization
   * is turned off but this method is called.  Additionally it is
   * thrown if tokenSet.token.syntax is not a START conditional.
   */
  private Collection<Lookahead> lazyFork(LookaheadSet tokenSet) {
    if (tokenSet.token.syntax.kind() != Kind.CONDITIONAL
        || tokenSet.token.syntax.toConditional().tag() != ConditionalTag.START
        || ! optimizeLazyForking) {
      throw new IllegalStateException();
    }
    // Only fork tokens within this conditional.
    int min = tokenSet.token.getSequenceNumber();
    OrderedSyntax after = skipConditional(tokenSet.token);
    int maxExclusive = after.getSequenceNumber();

    // Move to the next token or #if.
    while (after.syntax.kind() == Kind.CONDITIONAL
           && after.syntax.toConditional().tag
           != ConditionalTag.START) {
      Conditional conditional = after.syntax.toConditional();

      switch (conditional.tag()) {
      case START:
        // Done.
        break;
      case NEXT:
        after = skipConditional(after);
        break;
      case END:
        after = after.getNext();
        break;
      default:
        // Done.
        throw new UnsupportedOperationException();
      }
    }

    // The tokens between [min, maxExclusive).
    Collection<Lookahead> forkedSet = new LinkedList<Lookahead>();

    // The token at maxExclusive.
    Lookahead remainder = null;

    for (Lookahead n : tokenSet.set) {
      if (min < n.token.getSequenceNumber()
          && n.token.getSequenceNumber() < maxExclusive) {
        forkedSet.add(n);
      } else {
        if (null == remainder) {
          remainder = new Lookahead(after, n.presenceCondition.addRef());
        } else {
          // Union presence conditions of all tokens not being forked.
          PresenceCondition union
            = remainder.presenceCondition.or(n.presenceCondition);
          remainder.presenceCondition.delRef();
          remainder.presenceCondition = union;
        }
        // Free token presence condition.
        n.presenceCondition.delRef();
      }
    }

    if (null != remainder) {
      forkedSet.add(remainder);
    }

    if (parserStatistics) {
      lazyForks++;
      if (null != remainder) {
        lazyForksEmptyBranches++;
      }
    }

    return forkedSet;
  }

  /**
   * Skip an entire conditional block.  The given token must be a
   * conditional start or next token.
   *
   * @param a The conditional start or next token.
   * @return The first token after the end of the conditional.
   */
  private OrderedSyntax skipConditional(OrderedSyntax a) {
    if (a.syntax.toConditional().tag() != ConditionalTag.START
        && a.syntax.toConditional().tag() != ConditionalTag.NEXT) {
      throw new RuntimeException("skipConditional must take a " +
                                 "start or next conditional token.");
    }

    if (skipConditionalCache.containsKey(a.getSequenceNumber())) {
      return skipConditionalCache.get(a.getSequenceNumber());
    }

    // Sequence number is key to cache.
    int sequenceNumber = a.getSequenceNumber();

    // Move past the conditional, landing on #endif.
    int nesting = 1;
    do {
      a = a.getNext();
      if (a.syntax.kind() == Kind.CONDITIONAL) {
        switch (a.syntax.toConditional().tag()) {
        case START:
          nesting++;
          break;
        case END:
          nesting--;
          break;
        }
      }
    } while (nesting > 0);

    // Get the next token after #endif.
    OrderedSyntax returnToken = a.getNext();

    skipConditionalCache.put(sequenceNumber, returnToken);

    return returnToken;
  }

  /**
   * Shift the subparser.
   *
   * @param subparser The subparser to shift.
   */
  private void shift(Subparser subparser) {
    Lookahead x = subparser.lookahead;
    Language<? extends LanguageTag> token = x.token.syntax.toLanguage();
    int yystate = x.getActionData();
    int symbol = token.tag().getID();

    if (showActions) {
      System.err.println("shifting " + token.tag() + "("
                         + token.getTokenText() + ")" + " at " + token.getLocation());
    }

    // Don't keep layout unless printing source.
    if (! saveLayoutTokens && SemanticValues.ValueType.LAYOUT
        == semanticValues.getValueType(symbol)) {
      token = null;
    }

    // Push new stack frame.
    subparser.stack = new StackFrame(yystate, symbol, token, subparser.stack);
  }

  
  /**
   * Reduce the subparser.
   *
   * @param subparser The subparser to reduce.
   */
  private void reduce(Subparser subparser) {
    int production = subparser.lookahead.getActionData();
    int yylen = tables.yyr2[production];
    int symbol = tables.yyr1[production];
    String nodeName = semanticValues.changeName(symbol) ?
      semanticValues.newName(symbol) : tables.yytname[symbol];

    if (showActions) {
      System.err.println("reducing " + nodeName + " with " + yylen + " frames");
    }

    boolean conditionalAfter = false;
    boolean conditionalInside = false;
    Set<String> afterSet = new HashSet<String>();
    Set<String> insideSet = new HashSet<String>();

    // Get the semantic values from the stack.
    StackFrame topState = subparser.stack;
    Pair<Object> values = Pair.<Object>empty();
    for (int i = 0; i < yylen; i++) {
      if (conditionGranularity) {
        if (0 == i) {
          conditionalAfter = topState.conditionalAfter;
          afterSet.clear();
          afterSet.addAll(topState.afterSet);
          afterSet.addAll(topState.insideSet);
          
          conditionalInside = topState.conditionalInside;
          insideSet.clear();
          insideSet.addAll(topState.afterSet);
          insideSet.addAll(topState.insideSet);
        } else {
          conditionalInside = conditionalInside
            || topState.conditionalAfter || topState.conditionalInside;
          insideSet.addAll(topState.afterSet);
          insideSet.addAll(topState.insideSet);
        }
      }

      // Don't bother adding null semantic values as children.
      if (null != topState.value) {
        values = new Pair<Object>(topState.value, values);
      }
      topState = topState.next;
    }

    // Get the GOTO state.
    int yystate = tables.yypgoto[symbol - tables.YYNTOKENS] + topState.state;
    if (0 <= yystate && yystate <= tables.YYLAST
        && tables.yycheck[yystate] == topState.state) {
      yystate = tables.yytable[yystate];
    } else {
      yystate= tables
        .yydefgoto[symbol - tables.YYNTOKENS];
    }

    // Create the new semantic value.
    SemanticValues.ValueType valueType = semanticValues.getValueType(symbol);
    Object value;
    switch (valueType) {
    case ACTION:
      if (Pair.<Object>empty() != values) {
        throw new UnsupportedOperationException("semantic actions " + 
                                                "nonterminals should " +
                                                "have no semantic value");
      }
      // Fall-through
    case LAYOUT:
      if (saveLayoutTokens) {
        value = semanticValues.getValue(symbol, nodeName, values);
        break;
      } else {
        // Fall-through
      }
    case VOID:
      value = null;
      break;
    case PASS_THROUGH:
      // Pass-through when there is one child.
      if (Pair.<Object>empty() == values) {
        value = null;
      } else if (values.tail() == Pair.<Object>empty()) {
        value = values.head();
        break;
      } else {
        // Fall through to regular NODE.
      }
    case NODE:
      value = semanticValues.getValue(symbol, nodeName, values);
      break;
    case LIST:
      if (values == Pair.<Object>empty()) {
        value = GNode.create(nodeName);
      } else {
        if (nodeName.equals(((Node) values.head()).getName())) {
          value = ((Node) values.head());
          values = values.tail();
        } else {
          value = GNode.create(nodeName);
        }
        for (Object o : values) {
          GNode conditionalNode = GNode.create(CHOICE_NODE_NAME);
          conditionalNode.add(subparser.presenceCondition.addRef());
          conditionalNode.add(o);
          ((Node) value).add(conditionalNode);
        }
          
      }
      break;
    default:
      throw new UnsupportedOperationException("unsupported node type");
    }

    if (hasSemanticActions) {
      value = semanticActions.action(production, subparser, value);
    }

    // Push the new state.
    subparser.stack = new StackFrame(yystate, symbol, value, topState);

    if (conditionGranularity) {
      subparser.stack.conditionalAfter = conditionalAfter;
      subparser.stack.conditionalInside = conditionalInside;
      subparser.stack.afterSet = afterSet;
      subparser.stack.insideSet = insideSet;
    }

    if (conditionGranularity
        && (emitConditionalAfterSet || conditionalInside)
        && (trackAllProductions || trackedProductions.contains(nodeName))) {
      // Location location = getProductionLocation(value);
      Location location = getProductionLocation(value);

      // Emit the marker.
      if(conditionalInside) {
      System.err.println(String.format("conditional_inside %s %s \"%s\"",
                                       nodeName,
                                       location,
                                       joinSet(insideSet, ",")));
      }
      else if (emitConditionalAfterSet && conditionalAfter) {
        System.err.println(String.format("conditional_after %s %s \"%s\"",
                                        nodeName,
                                        location,
                                        joinSet(afterSet, ",")));
      }
    }

    if (hasSemanticActions) {
      // Handle semantic action node.
      semanticActions.dispatch(symbol, subparser);
    }
  }

  /**
   * Get the parsing action for a token.  This method is adopted from
   * Bison's parsing algorithm.
   *
   * @param x The token to find the parsing action for.
   * @param s The state to use to find the action.
   */
  private void getAction(Lookahead x, StackFrame s) {
    if (ParsingAction.ERROR == x.action) return;

    if (x.token.syntax.kind() == Kind.LANGUAGE
        || x.token.syntax.kind() == Kind.EOF) {
      // Get the parsing state.
      int yystate = s.state;
      int yyn = tables.yypact[yystate];

      if (tables.YYPACT_NINF == yyn) {
        // Reduce without token.  A Bison optimization.
        yyn = tables.yydefact[yystate];
        if (0 == yyn) {
          x.setAction(ParsingAction.ERROR, NODEFAULT);
        } else {
          x.setAction(ParsingAction.REDUCE, yyn);
        }
      } else {  // Lookup the parsing action.
        // Get the token number.
        int yytoken;
        if (x.token.syntax.kind() == Kind.EOF) {
          yytoken = tables.YYEOF;
        } else if (x.token.syntax.kind() == Kind.LANGUAGE) {
          Language<? extends LanguageTag> token = x.token.syntax.toLanguage();
          String str = token.getTokenText();
          LanguageTag tokentype = token.tag();
          yytoken = token.tag().getID();
        } else {
          yytoken = -1;
        }

        // Get the parsing action.
        yyn += yytoken;
        if (yyn < 0 || tables.YYLAST < yyn || tables.yycheck[yyn] != yytoken) {
          yyn = tables.yydefact[yystate];
          if (0 == yyn) {
            x.setAction(ParsingAction.ERROR, NODEFAULT);
          } else {
            x.setAction(ParsingAction.REDUCE, yyn);
          }
        } else {
          yyn = tables.yytable[yyn];
          if (yyn <= 0) {
            if (0 == yyn || tables.YYTABLE_NINF == yyn) {
              x.setAction(ParsingAction.ERROR, INVALID);
            } else {
              yyn = -yyn;
              x.setAction(ParsingAction.REDUCE, yyn);
            }
          } else {
            yystate = yyn;
            if (tables.YYFINAL == yystate) {
              x.setAction(ParsingAction.ACCEPT, -1);
              x.action = ParsingAction.ACCEPT;
            } else {
              x.setAction(ParsingAction.SHIFT, yystate);
            }
          }
        }
      }
    } else if (x.token.syntax.kind() == Kind.ERROR) {
      x.setAction(ParsingAction.ERROR, ERRDIRECTIVE);
    } else {
      throw new UnsupportedOperationException("parser does not handle " +
                                              "any other tokens besides " +
                                              "ordinary and conditional.");
    }
  }

  /** A subparser. */
  public static class Subparser {
    /** The lookahead symbol, either a token or a conditional. **/
    public Lookahead lookahead;
    
    /** The state stack. */
    public StackFrame stack;

    /** The presence condition. */
    public PresenceCondition presenceCondition;

    /** The C typedef/var symbol table. */
    public ParsingContext scope;

    /**
     * Create a new subparser.
     *
     * @param lookahead The next token.
     * @param stack The active state stack element.
     * @param presenceCondition The presence condition.
     * @param scope The parsing presenceCondition.
     */
    public Subparser(Lookahead lookahead, StackFrame stack,
                     PresenceCondition presenceCondition,
                     ParsingContext scope) {
      this.lookahead = lookahead;
      this.stack = stack;
      this.presenceCondition = presenceCondition;
      this.scope = scope;
    }

    /**
     * Get the presence condition of the subparser.
     *
     * @return The presence condition.
     */
    public PresenceCondition getPresenceCondition() {
      return presenceCondition;
    }

    public String toString() {
      return "(" + presenceCondition + ", " + lookahead + ")";
    }
  }
    
  /** A lookahead token. */
  public static class Lookahead {
    /** The token. */
    public OrderedSyntax token;
    
    /** The presenceCondition. */
    public PresenceCondition presenceCondition;
    
    /** The parsing action. */
    private ParsingAction action;
    
    /** The parsing action data. */
    private int actionData;

    /**
     * Create a new instance.
     *
     * @param t The token.
     * @param c The presence condition.
     * @param conditional The conditional in which the token is
     * contained.  Used for lazy forking.
     */
    public Lookahead(OrderedSyntax token,
                     PresenceCondition presenceCondition) {
      this.token = token;
      this.presenceCondition = presenceCondition;

      this.clearAction();
    }

    /**
     * Set the parsing action for this next token.
     *
     * @param action The parsing action.
     * @param actionData The parsing action data, i.e. the shift
     * state, reduced production, or the error id.
     */
    public void setAction(ParsingAction action, int actionData) {
      this.action = action;
      this.actionData = actionData;
    }

    /**
     * Clear the parsing action after taking the action.
     */
    public void clearAction() {
      action = ParsingAction.NONE;
      actionData = -1;
    }

    /**
     * Copy the parsing action from another next token.
     *
     * @param The other next token.
     */
    public void copyAction(Lookahead n) {
      this.setAction(n.getAction(), n.getActionData());
    }

    /**
     * Get the parsing action.
     *
     * @return The parsing action.
     * @throws IllegalStateException if the parsing action has not
     * been set yet.
     */
    public ParsingAction getAction() throws IllegalStateException {
      return action;
    }

    /**
     * Get the parsing action data if there is any.  For actions
     * without data, namely ACCEPT, the behavior of this method is
     * undefined.
     *
     * @return The parsing action data.
     * @throws IllegalStateException if the parsing action has not
     * been set yet.
     */
    public int getActionData() throws IllegalStateException {
      return actionData;
    }

    /**
     * Create a string representation.
     *
     * @return The string representation.
     */
    public String toString() {
      return "(" + token.syntax.toString() + ", " + action + ", "
        + actionData + ", " + token.getParentConditional() + ", "
        + presenceCondition + ")";
    }

    /**
     * Whether the lookahead is a single token or a set of lookahead
     * token.  Lookahead sets are used to implement shared reductions
     * and lazy forking.
     *
     * @return true if it is a set.
     */
    public boolean isSet() {
      return false;
    }

    /** Force an error.  Used by semantic * actions. */
    public void setError() {
      this.setAction(ParsingAction.ERROR, INVALID);
    }

  }

  static class LookaheadSet extends Lookahead {
    public LinkedList<Lookahead> set;

    public LookaheadSet(OrderedSyntax token,
                        PresenceCondition presenceCondition,
                        ParsingAction action,
                        int actionData) {
      super(token, presenceCondition);
      this.setAction(action, actionData);
      this.set = new LinkedList<Lookahead>();
    }

    /**
     * Add a new lookahead to this set.
     *
     * @param l The new lookahead.
     */
    public void add(Lookahead l) {
      set.add(l);
    }

    public boolean isSet() {
      return true;
    }

    /** Free the BDDs in the set. */
    public void free() {
      for (Lookahead l : set) {
        l.presenceCondition.delRef();
      }
    }

    /**
     * Create a string representation.
     *
     * @return The string representation.
     */
    public String toString() {
      return super.toString() + ":" + set;
    }

    /** Force an error.  Used by semantic actions. */
    public void setError() {
      this.setAction(ParsingAction.ERROR, INVALID);
      for (Lookahead l : set) {
        l.setError();
      }
    }
  }
    
  /**
   * A syntax object and it's sequence number, buffered in a
   * linked-list so that multiple subparsers can read tokens from the
   * same stream.  It references a stack of nested conditions in order
   * to store the sequence number of the conditional in which each
   * token lies.
   */
  public class OrderedSyntax {
    /** The syntax */
    public final Syntax syntax;
    
    /** The stream from which to pull syntax */
    private final Iterator<Syntax> stream;
    
    /** The ordered sequence number */
    private int order;
    
    /** The next ordered token */
    private OrderedSyntax next;

    /** The sequence number of the containing conditional */
    private int parentConditional;
    
    /**
     * Create a new ordered syntax object.  A call to getNext() on an
     * OrderedSyntax object created with this constructor will return
     * the first token from the stream.
     *
     * @param stream The stream from which to pull new tokens.
     */
    public OrderedSyntax(Iterator<Syntax> stream) {
      this(null, 0, 0, stream);
      nestedConditionals.push(0);
    }
    
    /**
     * Create a new ordered syntax object.
     *
     * @param stream The stream from which to pull new tokens.
     * @param syntax The token.
     * @param order The sequence number of the token.
     */
    private OrderedSyntax(Syntax syntax, int order, int parentConditional,
                          Iterator<Syntax> stream) {
      this.syntax = syntax; 
      this.order = order;
      this.parentConditional = parentConditional;
      this.stream = stream;
    }

    /**
     * Create a copy of an ordered syntax object using a different
     * syntax object.  This is useful for reclassifying tokens due to
     * parsing presenceCondition.
     *
     * @param newSyntax The new syntax object.
     * @param old The old OrderedSyntax object to duplicate sequence
     * and next token information from.
     * throws IOException.
     */
    public OrderedSyntax(Syntax newSyntax, OrderedSyntax old) {
      this.stream = old.stream;
      this.syntax = newSyntax;
      this.parentConditional = parentConditional;
      this.order = old.order;

      // Prime the pump, by reading the next token.  This is
      // necessary, because if both the original and the copy of the
      // token have "null" as their next token, they will both call
      // stream.next(), which will advance the read two tokens ahead.
      // Really they both want the same next token.
      old.getNext();
      this.next = old.next;
    }

    /**
     * Create a copy of this object using a new Syntax object.
     *
     * @param syntax The new syntax object.
     * @return A new OrderedSyntax object.
     */
    public OrderedSyntax copy(Syntax syntax) {
      return new OrderedSyntax(syntax, this);
    }

    /**
     * Get the next token from the stream and assign it the next
     * sequence number.
     *
     * @return The next token.
     */
    public OrderedSyntax getNext() {
      if (null == this.next) {
        this.next = new OrderedSyntax(this.stream.next(), this.order + 1,
                                      nestedConditionals.peek(), this.stream);
        if (this.next.syntax.kind() == Kind.CONDITIONAL) {
          switch (this.next.syntax.toConditional().tag()) {
          case START:
            nestedConditionals.push(this.next.order);
            this.next.parentConditional = this.next.order;
            break;
          case NEXT:
            break;
          case END:
            nestedConditionals.pop();
            break;
          }
        }
      }
      
      return next;
    }

    /**
     * Get the sequence number of this token.  The token sequence
     * numbers are strictly monotonically increasing from the start of
     * the file to the end.
     *
     * @return The sequence number.
     */
    public int getSequenceNumber() {
      return order;
    }

    /**
     * Get the sequence number of the this token's parent conditional.
     * This method is undefined when the token is a conditonal itself.
     *
     * @return The sequence number of this token's parent conditional.
     */
    public int getParentConditional() {
      return parentConditional;
    }

    /**
     * Get the string representation.
     *
     * @return The string representation.
     */
    public String toString() {
      return this.order + ":" + this.syntax.toString()
        + this.syntax.getClass();
    }
  }

  /** A frame of the parsing state stack. */
  public static class StackFrame {
    /** The state number */
    public int state;

    /** The semantic value. */
    public Object value;

    /** The symbol id. */
    public int symbol;
    
    /** The next state in the stack */
    public StackFrame next;

    /** The height of the stack.  Maintained internally. */
    private int height;

    /** True when the semantic value has a conditional after it. */
    private boolean conditionalAfter;

    /** True when the semantic value has a conditional in it. */
    private boolean conditionalInside;

    /** Information about conditionals interacting with semantic values. */
    private Set<String> afterSet;

    /** Information about conditionals interacting with semantic values. */
    private Set<String> insideSet;

    /**
     * Make a new state.
     *
     * @param state The state number.
     * @param value The semantic value.
     * @param next The next state stack element in the stack.
     */
    public StackFrame(int state, int symbol, Object value, StackFrame next) {
      this.state = state;
      this.value = value;
      this.symbol = symbol;
      this.next = next;
      this.conditionalAfter = false;
      this.conditionalInside = false;
      this.afterSet = new HashSet<String>();
      this.insideSet = new HashSet<String>();

      if (null == next) {
        height = 1;
      } else {
        height = next.height + 1;
      }
    }

    /**
     * Get the ith state down the stack, "1" returning this state.
     *
     * @param i The state to return.
     * @return The ith state down the stack.
     */
    public StackFrame get(int i) {
      StackFrame state;
      
      state = this;
      while (i > 1) {
        state = state.next;
        i--;
      }
      
      return state;
    }

    /**
     * Get the height of the stack.
     *
     * @return The height.
     */
    public int getHeight() {
      assert checkHeight() == height;
      return height;
    }

    /**
     * Check the height of the stack by following the links.
     *
     * @return The height.
     */
    private int checkHeight() {
      int h = 0;
      StackFrame s = this;

      while (null != s) {
        h++;
        s = s.next;
      }

      return h;
    }

    /**
     * Recursively merge the semantic values from the given state
     * stack into this state stack.  The number of elements to merge
     * is controlled by the dist parameter.  This method assumes that
     * this stack's semantic values are already CHOICE_NODE_NAME nodes.
     *
     * This version is inefficient in that shared semantics values
     * from shared stack elements get referenced twice.
     *
     * @param other The other state stack.
     * @param otherPresenceCondition the presenceCondition of the
     * other state stack's semantic value.
     * @param dist The distance down the stack to merge.
     */
    public void merge(PresenceCondition thisPresenceCondition,
                      StackFrame other,
                      PresenceCondition otherPresenceCondition,
                      int dist) {
      if (dist == 0) return;

      int flags
        = (null != this.value ? 1 : 0)
        | (null != other.value ? 2 : 0);
      // System.err.println("MERGE BEFORE");
      // System.err.println(this.value);
      // System.err.println(thisPresenceCondition);
      // System.err.println(other.value);
      // System.err.println(otherPresenceCondition);

      switch (flags) {
      case 0:
        // Both are null.  Do nothing.
        break;
      case 1:
        // other.value is null, but this.value is not.  There is
        // nothing to add to this semantic value, so do nothing.
        break;
      case 2:
        // this.value is null, but other.value is not.  Create a new
        // conditional to store the non-null other.value and its
        // presence condition.
        GNode conditionalNode = GNode.create(CHOICE_NODE_NAME);

        conditionalNode.add(otherPresenceCondition.addRef());
        conditionalNode.add(other.value);
        this.value = conditionalNode;
        break;

      case 3:
        // Neither are null.  Add other.value and its presence
        // condition.
        if (this.value == other.value ||
            //clause here for comparing typedef and identifiers
            (this.value instanceof Text && other.value instanceof Text &&
             ((Text)this.value).getTokenText().equals(((Text)other.value).getTokenText()))
            ) {
          // Both are already pointing to the same list node.  Don't
          // create a conditional.
        } else if (FLATTEN_MERGED_CHOICE_NODES) {
          // Flatten both values into a single conditional.
          GNode cnode = GNode.create(CHOICE_NODE_NAME);

          if (((Node) this.value).getName().equals(CHOICE_NODE_NAME)) {
            boolean on_cond = true;
            PresenceCondition and = null;

            for (Object o : (Node) this.value) {
              if (on_cond) {
                and = thisPresenceCondition.and((PresenceCondition) o);
                ((PresenceCondition) o).delRef();
              } else {
                if (! and.isFalse()) {
                  cnode.add(and);
                  cnode.add(o);
                } else {
                  and.delRef();
                }
              }
              on_cond = ! on_cond;
            }
          } else {
            cnode.add(thisPresenceCondition.addRef());
            cnode.add(this.value);
          }

          if (((Node) other.value).getName().equals(CHOICE_NODE_NAME)) {
            boolean on_cond = true;
            PresenceCondition and = null;

            for (Object o : (Node) other.value) {
              if (on_cond) {
                and = otherPresenceCondition.and((PresenceCondition) o);
              } else {
                if (! and.isFalse()) {
                  cnode.add(and);
                  cnode.add(o);
                } else {
                  and.delRef();
                }
              }
              on_cond = ! on_cond;
            }
          } else {
            cnode.add(otherPresenceCondition.addRef());
            cnode.add(other.value);
          }

          this.value = cnode;
        // } else if (! ((Node) this.value).getName().equals(CHOICE_NODE_NAME)) {
        } else {
          // Combine the two value, this and other, into a choice
          // node.
          GNode cnode = GNode.create(CHOICE_NODE_NAME);

          cnode.add(thisPresenceCondition.addRef());
          cnode.add(this.value);
          cnode.add(otherPresenceCondition.addRef());
          cnode.add(other.value);
          this.value = cnode;
        // } else {  // causes a cycle in the AST in some cases
        //   // This value is already a conditional, so just add the
        //   // other value.
        //   ((Node) this.value).add(otherPresenceCondition.addRef());
        //   ((Node) this.value).add(other.value);
        }
        break;
      }
      
      // System.err.println("MERGE AFTER");
      // System.err.println(this.value);

      if (this.next != null) {
        this.next.merge(thisPresenceCondition, other.next,otherPresenceCondition, dist - 1);
      }
    }

    /**
     * Get the string representation.
     *
     * @return The string representation.
     */
    public String toString() {
      return value + ":" + next;
    }

    /**
     * Check whether this parsing state can merge with another.
     *
     * @param other The other parsing state.
     * @return true if it can merge with this state.
     */
    public boolean isMergeable(StackFrame other) {
      return isMergeable(this, other);
    }

    /**
     * Check whether two parsing states can merge.
     *
     * @param s The first parsing state.
     * @param t The second parsing state.
     * @return true if they can merge.
     */
    private static boolean isMergeable(StackFrame s, StackFrame t) {
      if (s == t) {
        return true;
      } else if (s == null || t == null) {
        return false;
      } else if (s.state != t.state) {
        return false;
      } else {
        return isMergeable(s.next, t.next);
      }
    }
  }

  /**
   * Determine whether a token is parseable.  The only parseable
   * tokens are Language tokens and EOF.
   *
   * @param syntax The syntax to test for parseability.
   * @return true if the syntax is a Language or EOF token.
   */
  public static boolean isParseable(Syntax syntax) {
    return syntax.kind() == Kind.LANGUAGE || syntax.kind() == Kind.EOF;
  }

  private void error(String msg) {
    System.err.println("error: " + msg);
  }

  /**
   * Get location of a production given its value.
   *
   * @param value The value of the production.
   * @return The location.
   */
  static Location getProductionLocation(Object value) {
    if (value instanceof Node) {
      for (Object o : (Node) value) {
        Location location = getProductionLocation(o);

        if (null != location) {
          return location;
        }
      }

      return ((Node) value).getLocation();
    } else {
      return null;
    }
  }

  /**
   * Concatenate all elements of a set separated with a given
   * delimiter.
   *
   * @param set The set to join.
   * @param delim The delimiter.
   * @return A string of all elements.
   */
  private static <E> String joinSet(Set<E> set, String delim) {
    String ret = "";
    String d = "";
    
    for (E e : set) {
      ret += d + e.toString();
      d = delim;
    }

    return ret;
  }
}

