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
package xtc.lang.cpp;

import java.io.StringReader;

import java.lang.StringBuilder;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Iterator;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.PreprocessorTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;
import xtc.lang.cpp.Syntax.ConditionalBlock;
import xtc.lang.cpp.Syntax.Error;
import xtc.lang.cpp.Syntax.ErrorType;

import xtc.lang.cpp.MacroTable;
import xtc.lang.cpp.MacroTable.Macro;
import xtc.lang.cpp.MacroTable.Macro.Object;
import xtc.lang.cpp.MacroTable.Macro.Function;
import xtc.lang.cpp.MacroTable.Entry;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.tree.Location;

import net.sf.javabdd.BDD;

/**
 * This class expands macros and processes header files
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.197 $
 */
public class Preprocessor implements Iterator<Syntax> {
  /** Don't expand the macro. */
  public static int NO_EXPAND = 0;

  /** The token has preceding whitespace. */
  public static int PREV_WHITE = 1;

  /** The token is the left operand of a token-pasting. */
  public static int PASTE_LEFT = 2;

  /**
   * The token is not to be pasted.  Used to prevent incorrect
   * pasting when the right operand is empty.
   */
  public static int AVOID_PASTE = 3;

  /** The token is to be stringified. */
  public static int STRINGIFY_ARG = 4;

  /** The function has already been hoisted. */
  public static int HOISTED_FUNCTION = 5;

  /** The macro is not a valid function invocation. */
  public static int NON_FUNCTION = 6;

  /** The macro has an unknown definition. */
  public static int UNKNOWN_DEF = 7;

  /** The token indicates an end-of-include. */
  public static int EOI = 8;

  /**
   * The token indicates an end-of-expansion.  This flag is
   * used to mark the end of a macro expansion while that expansion is
   * recursively passed to the preprocessor.
   */
  public static int EOE = 9;

  /**
   * An empty token.  Used to replace preprocessor directives and
   * macros that have no contents.
   */
  public static Layout EMPTY = new Layout("");

  /** A space token. */
  public static Layout SPACE = new Layout(" ");

  /**
   * A special token used to avoid incorrect token-pasting when the
   * right operand is empty.
   */
  public static Layout AVOID_PASTE_TOKEN = new Layout("");
  static {
    AVOID_PASTE_TOKEN.setFlag(AVOID_PASTE);
  }

  /**
   * Turn on optimized hoisting.  Used for performance testing of
   * optimized hoisting.
   */
  final private static boolean OPTIMIZED_HOISTING = true;

  /**
   * Don't return tokens from infeasible branches.  When this is off,
   * no preprocessing is done in infeasible branches, but their tokens
   * are still returned.
   */
  final private static boolean EMPTY_INFEASIBLE_BRANCHES = true;

  /**
   * Experimental handling of #error directives.  Disjoin presence
   * conditions of all errors and make any subsequent branches with
   * the same presence conditions empty.
   */
  final private static boolean EMPTY_INVALID_BRANCHES = false;

  /**
   * Experimental handling of tokens after hoisted functions.  Turned
   * off for now.
   */
  final private static boolean JOIN_ORPHANS = false;

  /**
   * The stream from which the Preprocessor gets tokens and
   * directives
   */
  private Iterator<Syntax> stream;
  
  /** The file manager for main file and header streams. */
  private HeaderFileManager fileManager;
  
  /** The macro table. */
  private MacroTable macroTable;
  
  /** The global presenceCondition. */
  private PresenceConditionManager presenceConditionManager;

  /** The expression evaluator. */
  private ConditionEvaluator evaluator;

  /** The token creator. */
  private TokenCreator tokenCreator;

  /**
   * Whether to gather statistics.  These are output to standard
   * error, since statistics-gathering is permitting along with
   * preprocessor output.
   */
  private boolean preprocessorStatistics = false;

  /**
   * Whether to show the presence condition of each static
   * conditional.
   */
  private boolean showPresenceConditions = false;

  /**
   * Maps the presence condition's BDD hash code to the string
   * representation's hash code.  This is used to compare presence
   * conditions across compilation units.
   */
  HashMap<Integer, Integer> printedpc = new HashMap<Integer, Integer>();

  /** Whether to print configs used at each conditional. */
  private boolean showConditionConfigs = false;

  /** Save error directive constraints. */
  boolean saveErrorConstraints = false;

  /** Error directive constraints in CNF. */
  List<String> errorConstraints  = null;

  /** Error directive constraints in CNF. */
  List<PresenceCondition> printConstraints  = null;

  /** Whether to print error directive conditions. */
  private boolean printErrorConditions = false;

  /** Whether to emit errors to stderr. */
  private boolean showErrors = false;

  /**
   * The stack of macro presenceConditions.  Used to keep track of
   * nested macro expansions and for backing up in the input.
   */
  private LinkedList<TokenBuffer> stackOfBuffers;

  /**
   * Used when prescanning a function-like invocation's arguments and
   * also when collecting the unexpanded tokens of a defined operand
   * in a conditional expression.  It is zero when not prescanning,
   * greater than zero when prescanning.  It is not a boolean since
   * conditional directives, and hence defined operands, can appear
   * inside of function-like macro invocations.
   */
  private int prescanning;

  /** The location used by built-in macros. */
  Location location;

  /** The conjunction of all invalid configurations. */
  private PresenceCondition invalid;
  
  /**
   * Stack to store depth and breadth of nested conditionals.  It's a
   * linked list to use the stack methods.
   */
  LinkedList<Integer> nestedConditionals;

  /** The "defined" keyword. */
  private final Syntax DEFINED;

  /** An EOF token. */
  private final Syntax EOF;

  /** Create a new macro preprocessor */
  public Preprocessor(HeaderFileManager fileManager, MacroTable macroTable,
                      PresenceConditionManager presenceConditionManager,
                      ConditionEvaluator evaluator, TokenCreator tokenCreator) {
    this.fileManager = fileManager;
    this.macroTable = macroTable;
    this.presenceConditionManager = presenceConditionManager;
    this.tokenCreator = tokenCreator;

    this.evaluator = evaluator;
    this.stackOfBuffers = new LinkedList<TokenBuffer>();
    this.prescanning = 0;
    if (EMPTY_INVALID_BRANCHES) {
      this.invalid = presenceConditionManager.new PresenceCondition(false);
    }
    this.nestedConditionals = new LinkedList<Integer>();
    this.DEFINED = tokenCreator.createIdentifier("defined");
    this.EOF = new Syntax.EOF();
  }

  /**
   * Turn preprocessor statistics collection on.  Default is off.
   *
   * @param b True is on.
   */
  public void collectStatistics(boolean b) {
    preprocessorStatistics = b;
  }

  /**
   * Show preprocessor conditions.  Default is off.
   *
   * @param b True is on.
   */
  public void showPresenceConditions(boolean b) {
    showPresenceConditions = b;
  }
  
  /**
   * Save
   *
   * @param list The list to add CNF clauses to.
   */
  public void saveErrorConstraints(List<String> errorConstraints) {
    saveErrorConstraints = true;
    this.errorConstraints = errorConstraints;
  }
  
  /**
   * Show configs used at each condition.  Default is off.
   *
   * @param b True is on.
   */
  public void showConditionConfigs(boolean b) {
    showConditionConfigs = b;
  }
  
  /**
   * Print error directive configs.  Default is off.
   *
   * @param b True is on.
   */
  public List<PresenceCondition> printErrorConditions(boolean b) {
    printErrorConditions = b;
    if (printErrorConditions) {
      this.printConstraints = new ArrayList<PresenceCondition>();
      return this.printConstraints;
    } else {
      return null;
    }
  }
  
  /**
   * Show preprocessor errors.  Default is on.
   *
   * @param b True is on.
   */
  public void showErrors(boolean b) {
    showErrors = b;
  }
  
  /**
   * This class scans the input tokens, expanding macros and
   * evaluating directives, and returns tokens.
   */
  public Syntax next() {
    // Get the next token from the source file or the token buffer.
    Syntax syntax = getNext();

    // System.err.println("getNext: " + syntax);
    // System.err.println("PASTE_LEFT: " + syntax.testFlag(PASTE_LEFT));
    // System.err.println("PREV_WHITE: " + syntax.testFlag(PREV_WHITE));
    // System.err.println("prescanning: " + prescanning);
    // System.err.println("presenceCondition: " + presenceConditionManager.reference());

    boolean isValid;
    if (EMPTY_INVALID_BRANCHES) {
      PresenceCondition current = presenceConditionManager.reference();
      PresenceCondition andNot = current.andNot(invalid);
      current.delRef();
      isValid = ! andNot.isFalse();
      andNot.delRef();
    } else {
      isValid = true;
    }

    // Evaluate the token.
    switch (syntax.kind()) {
    case LANGUAGE:
      Language<?> token = syntax.toLanguage();

      if (EMPTY_INFEASIBLE_BRANCHES) {
        if (presenceConditionManager.isFalse()) {
          return EMPTY;
        } else if (0 == prescanning && token.tag().hasName() && isValid) {
          // Expand macros.
          return processToken(token);
        } else {
          return syntax;
        }
      } else {
        if (0 == prescanning && token.tag().hasName()
            && ! presenceConditionManager.isFalse() && isValid) {
          // Expand macros.
          return processToken(token);
        } else {
          return syntax;
        }
      }

    case DIRECTIVE:
      if (0 == prescanning) {
        if (! presenceConditionManager.isFalse() && isValid) {
          return evaluateDirective(syntax.toDirective());
        } else {
          // Always evaluate conditionals, since these are what update
          // the presence condition.
          switch (syntax.toDirective().tag()) {
          case IF:
          case IFDEF:
          case IFNDEF:
          case ELIF:
          case ELSE:
          case ENDIF:
            return evaluateDirective(syntax.toDirective());

          default:
            return syntax;
          }
        }
      } else {
        return syntax;
      }

    case CONDITIONAL:
      if (0 == prescanning) {
        Conditional conditional = syntax.toConditional();
        switch (conditional.tag()) {
        case START:
          presenceConditionManager.push();
          // Fall through.

        case NEXT:
          presenceConditionManager.enter(syntax.toConditional().presenceCondition.getBDD().id());
          break;

        case END:
          presenceConditionManager.pop();
          break;
        }
      }
      return syntax;

    case CONDITIONAL_BLOCK:
      // A conditional block.  Serialize it into conditionals and
      // regular tokens.
      ConditionalBlock block = (ConditionalBlock) syntax;
      List<Syntax> serial = new LinkedList<Syntax>();
      boolean first = true;
      for (int i = 0; i < block.branches.size(); i++) {
        if (first) {
          serial.add(new Conditional(ConditionalTag.START,
                                     block.presenceConditions.get(i),
                                     block.getLocation()));
          first = false;
        } else {
          serial.add(new Conditional(ConditionalTag.NEXT,
                                     block.presenceConditions.get(i),
                                     block.getLocation()));
        }
        block.presenceConditions.get(i).addRef();
          
        if (null != block.branches.get(i)) {
          // Non-empty branch.
          for (Syntax s : block.branches.get(i)) {
            serial.add(s);
          }
        }
      }
        
      if (! first) {
        serial.add(new Conditional(ConditionalTag.END,
                                   null,
                                   block.getLocation()));
      }

      stackOfBuffers.push(new PlainTokenBuffer(serial));

      return EMPTY;

    case EOF:
      // Fall through.
    default:
      return syntax;
    }
  }
  
  public boolean hasNext() {
    return !stackOfBuffers.isEmpty() || fileManager.hasNext();
  }

  /**
   * Get the next token from the input or from a token buffer.
   *
   * @return The next token.
   */
  private Syntax getNext() {
    if (stackOfBuffers.isEmpty()) {
      // Pull the next token from the file.
      Syntax next = fileManager.next();

      location = next.getLocation();
      return next;
    } else {
      if (! stackOfBuffers.peek().hasNext()) {
        // Reached the end of a toke buffer.
        if (stackOfBuffers.peek().hasMacroName()) {
          // Re-enable the macro after expansion.
          macroTable.enable(stackOfBuffers.peek().getMacroName());
        }

        stackOfBuffers.pop();

        return EMPTY;
      }

      Syntax syntax = stackOfBuffers.peek().next();

      // This handles a special case where __LINE__ arguments expand
      // to the incorrect line when there are in the arguments of a
      // function-like invocation but expanded under the presence
      // condition where the function-like is a non-function like
      // macro.  See $CPPTEST/cpp/function_lines.c for an example.
      boolean updateLocation = true;
      for (TokenBuffer t : stackOfBuffers) {
        if (t.hasMacroName() || t.isMacroArgument()) {
          updateLocation = false;
          break;
        }
      }
      if (updateLocation && syntax.getLocation() != null) {
        location = syntax.getLocation();
      }

      // Increment the BDD reference count.
      if (syntax.kind() == Kind.CONDITIONAL
          && ( syntax.toConditional().tag() == ConditionalTag.START
               || syntax.toConditional().tag() == ConditionalTag.NEXT)) {
        syntax.toConditional().presenceCondition().addRef();
      }

      // Perform token-pasting.
      while (syntax.testFlag(PASTE_LEFT)) {
        // Get the right operand.  ## is not allowed at the end of a
        // definition.
        Syntax next;
        do {
          next = stackOfBuffers.peek().next();
        } while (! (next.kind() == Kind.LANGUAGE
                    || next.kind() == Kind.CONDITIONAL_BLOCK
                    || next.testFlag(AVOID_PASTE)));

        if (next.testFlag(AVOID_PASTE)) {
          // The AVOID_PASTE flag was seen.  Don't paste this token.
          syntax = syntax.copy();
          syntax.clearFlag(PASTE_LEFT);
          stackOfBuffers.push(new OneTokenBuffer(next));

        } else if (syntax.kind() == Kind.LANGUAGE
                   && next.kind() == Kind.LANGUAGE) {
          // Paste two language tokens with the TokenCreator instance.
          Syntax pasted
            = tokenCreator.pasteTokens(syntax.toLanguage(), next.toLanguage());
          
          if (null != pasted) {
            // The paste was successful.

            // Copy the PREV_WHITE and PASTE_LEFT flags to the newly
            // pasted token and set it's location.

            if (syntax.testFlag(PREV_WHITE)) {
              pasted.setFlag(PREV_WHITE);
            }

            // Use left operand's location for the newly-pasted
            // token's location.
            pasted.setLocation(syntax.getLocation());
              
            // Update the syntax variable.  It may be a macro that
            // requires expansion.
            syntax = pasted;
              
            if (next.testFlag(PASTE_LEFT)) {
              syntax.setFlag(PASTE_LEFT);
            }
              
            if (preprocessorStatistics) {
              System.err.format("paste %s %s %s %d\n",
                                "token", "token",
                                getNestedLocation(), 1);
            }

          } else {
            // The paste was unsuccessful.  Add a space between
            // the tokens.

            // Error location 1
            String message = "pasting \"" + syntax.getTokenText() + "\" and \""
              + next.getTokenText() + "\" does not give a valid preprocessing "
              + "token";

            if (showErrors) {
              error(message);
            }

            // Remove the paste_left flag from the token.
            syntax = syntax.copy();
            syntax.clearFlag(PASTE_LEFT);

            // Push a new token buffer containing the space and the
            // right-side of the paste operation.  The left operand
            // will be returned by this call to scan().
            stackOfBuffers.push(new TwoTokenBuffer(SPACE, next));

            // Push the error token.
            stackOfBuffers.push(new OneTokenBuffer(new Error(message, false)));
          }
            
        } else if (syntax.kind() == Kind.CONDITIONAL_BLOCK
                   || next.kind() == Kind.CONDITIONAL_BLOCK) {
          // One or both of the token-paste arguments is a
          // conditional.  Hoist the conditionals around the
          // token-paste operation.

          // Return the hoisted pasting via the syntax variable.
          syntax = pasteHoist(syntax, next);
        } else {
          throw new RuntimeException("invalid tokens for paste");
        }
      } // while there is a token-paste operation

      return syntax;
    }
  }
  
  /**
   * Hoist conditionals around a token-pasting and perform any valid
   * token-pastes.  The token-pastes are hoisted no matter what, so
   * that the Error tokens get output and since the hoisting work has
   * already been done.  The tradeoff is that the hoisted token-paste
   * may have many more tokens than the original token-paste.
   *
   * @param left A regular or compound token for the left-hand-side of
   * the token-paste.
   * @param right A regular or compound token for the right-hand-side
   * of the token-paste.
   * @return the hoisted and valid token-pastes.
   */
  private Syntax pasteHoist(Syntax left, Syntax right) {
    List<List<Syntax>> leftBranches = null;
    List<PresenceCondition> leftPresenceConditions = null;
    List<List<Syntax>> rightBranches = null;
    List<PresenceCondition> rightPresenceConditions = null;
    
    if (left.kind() == Kind.CONDITIONAL_BLOCK) {
      // Hoist conditionals around the operand.
      List<Syntax> list = new LinkedList<Syntax>();
      list.add(left);
      PresenceCondition current = presenceConditionManager.reference();
      ConditionalBlock hoistedBlock = hoistConditionals(list, current);
      current.delRef();

      leftBranches = hoistedBlock.branches;
      leftPresenceConditions = hoistedBlock.presenceConditions;
    }

    if (right.kind() == Kind.CONDITIONAL_BLOCK) {
      // Hoist conditionals around the operand.
      List<Syntax> list = new LinkedList<Syntax>();
      list.add((ConditionalBlock) right);
      PresenceCondition current = presenceConditionManager.reference();
      ConditionalBlock hoistedBlock = hoistConditionals(list, current);
      current.delRef();

      rightBranches = hoistedBlock.branches;
      rightPresenceConditions = hoistedBlock.presenceConditions;
    }

    // Hoist conditionals around the entire operation and perform
    // token pasting.
    int nvalid = 0;
    ConditionalBlock pastedBlock = null;
    if (left.kind() == Kind.LANGUAGE) {
      for (int i = 0; i < rightBranches.size(); i++) {
        List<Syntax> branch = rightBranches.get(i);

        if (branch.size() > 0) {
          Syntax first = branch.get(0);
          Language<?> pasted = tokenCreator.pasteTokens(left.toLanguage(),
                                                        first.toLanguage());

          if (null != pasted) {
            // A successful paste.
            branch.remove(0);
            branch.add(0, pasted);
            // Use left operand's location for the newly-pasted
            // token.
            pasted.setLocation(left.getLocation());

            nvalid++;

          } else {
            // Error location 2
            String message = "pasting \"" + left.getTokenText() + "\" and \""
              + first.getTokenText() + "\" does not give a valid preprocessing "
              + "token";

            if (showErrors) {
              error(message);
            }

            Syntax leftCopy = left.copy();
            leftCopy.clearFlag(PASTE_LEFT);
            branch.add(0, leftCopy);

            branch.add(0, new Error(message, false));
          }
        }
      }
      pastedBlock = new ConditionalBlock(rightBranches, rightPresenceConditions, right.getLocation());
      
    } else if (right.kind() == Kind.LANGUAGE) {
      for (int i = 0; i < leftBranches.size(); i++) {
        List<Syntax> branch = leftBranches.get(i);

        if (branch.size() > 0) {
          Syntax last = branch.get(branch.size() - 1);
          Language<?> pasted = tokenCreator.pasteTokens(last.toLanguage(),
                                                        right.toLanguage());

          if (null != pasted) {
            // Paste was successful.

            branch.remove(branch.size() - 1);
            branch.add(pasted);

            pasted.setLocation(last.getLocation());

            nvalid++;

          } else {
            // Error location 3
            String message = "pasting \"" + last.getTokenText() + "\" and \""
              + right.getTokenText() + "\" does not give a valid preprocessing "
              + "token";

            if (showErrors) {
              error(message);
            }

            Syntax rightCopy = right.copy();
            rightCopy.clearFlag(PASTE_LEFT);
            branch.add(rightCopy);

            branch.add(0, new Error(message, false));
          }
        }
      }
      pastedBlock = new ConditionalBlock(leftBranches, leftPresenceConditions, left.getLocation());

    } else {
      // Take all combinations of paste operations.
      List<List<Syntax>> comboBranches = new LinkedList<List<Syntax>>();
      List<PresenceCondition> comboPresenceConditions = new LinkedList<PresenceCondition>();
      
      for (int left_i = 0; left_i < leftBranches.size(); left_i++) {
        List<Syntax> leftBranch = leftBranches.get(left_i);

        if (leftBranch.size() > 0) {
          Syntax last = leftBranch.get(leftBranch.size() - 1);

          for (int right_i = 0; right_i < rightBranches.size(); right_i++) {
            List<Syntax> rightBranch = rightBranches.get(right_i);

            if (rightBranch.size() > 0) {
              PresenceCondition comboPresenceCondition
                = leftPresenceConditions.get(left_i).and(rightPresenceConditions.get(right_i));

              if (! comboPresenceCondition.isFalse()) {
                Syntax first = rightBranch.get(0);
                Language<?> pasted
                  = tokenCreator.pasteTokens(last.toLanguage(),
                                             first.toLanguage());

                // Create a new branch in the block of pastes
                List<Syntax> comboBranch = new LinkedList<Syntax>();

                // Copy all tokens except the last from the left
                // branch.
                for (int i = 0, size = leftBranch.size(); i < size - 1; i++) {
                  comboBranch.add(leftBranch.get(i));
                }
                  
                if (null != pasted) {
                  // Add the pasted token.
                  comboBranch.add(pasted);

                  // Use left operand's location for the newly-pasted
                  // token.
                  pasted.setLocation(last.getLocation());

                  nvalid++;
                } else {
                  // Error location 4
                  String message = "pasting \"" + last.getTokenText()
                    + "\" and \"" + first.getTokenText()
                    + "\" does not give a valid preprocessing "
                    + "token";

                  if (showErrors) {
                    error(message);
                  }

                  comboBranch.add(new Error(message, false));
                  comboBranch.add(last);
                  comboBranch.add(first);
                }

                // Copy all tokens except the last from the right
                // branch.
                for (int i = 1, size = rightBranch.size(); i < size; i++) {
                  comboBranch.add(rightBranch.get(i));
                }

                // Add the new branch with its presence condition.
                comboBranches.add(comboBranch);
                comboPresenceConditions.add(comboPresenceCondition);
              } else {
                comboPresenceCondition.delRef();
              } // if (! comboPresenceCondition.isFalse())
            } // if (rightBranch.size() > 0)
          } // for each right branch
        } // if (leftBranch.size() > 0)
      } // for each left branch

      pastedBlock = new ConditionalBlock(comboBranches, comboPresenceConditions, left.getLocation());
    }
    
    // Preserve the PASTE_LEFT flag from the right operand on the
    // pasted token since it may be the left operand of another paste.
    if (right.testFlag(PASTE_LEFT)) {
      pastedBlock.setFlag(PASTE_LEFT);
    } else {
      pastedBlock.clearFlag(PASTE_LEFT);
    }

    if (preprocessorStatistics) {
      System.err.format("paste %s %s %s %d %d\n",
                        left.kind() == Kind.CONDITIONAL_BLOCK
                        ? "conditional" : "token",
                        right.kind() == Kind.CONDITIONAL_BLOCK
                        ? "conditional" : "token",
                        getNestedLocation(),
                        pastedBlock.branches.size(),
                        nvalid);
    }

    return pastedBlock;
  }
  
  /**
   * Evaluate the directive.
   *
   * @param directive The directive to evaluate.
   * @return An empty token, marker, or conditional.
   */
  private Syntax evaluateDirective(Directive directive) {
    // Get the name of the directive.
    int s = 1;
    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() != Kind.LANGUAGE) {
      s++;
    }

    // Call the appropriate evaluator.
    switch (directive.tag()) {
    case IF:
      return ifDirective(directive, s);

    case IFDEF:
      return ifdefDirective(directive, s);

    case IFNDEF:
      return ifndefDirective(directive, s);

    case ELIF:
      return elifDirective(directive, s);

    case ELSE:
      return elseDirective(directive, s);

    case ENDIF:
      return endifDirective(directive, s);

    case INCLUDE:
      return includeDirective(directive, s, false);

    case INCLUDE_NEXT:
      return includeDirective(directive, s, true);

    case DEFINE:
      defineDirective(directive, s);
      return EMPTY;

    case UNDEF:
      undefDirective(directive, s);
      return EMPTY;

    case LINE:
      lineDirective(directive, s);
      return EMPTY;

    case ERROR:
      return errorDirective(directive, s);

    case WARNING:
      return warningDirective(directive, s);

    case PRAGMA:
      pragmaDirective(directive, s);
      return EMPTY;

    case LINEMARKER:
      // Pass linemarkers through.  Better for debugging.
      return lineMarker(directive, s);

    case INVALID:
      // Error location 5
      String message = "invalid preprocessing directive #" + directive.get(s);

      if (showErrors) {
        error(message);
      }
      return new Error(message, false);

    default:
      throw new UnsupportedOperationException("unsupported directive type");
    }
  }
  
  /**
   * Process if directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   * It passes the conditional expression to a function that
   * evaluates the expression.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax ifDirective(Directive directive, int s) {

    // Move past the whitespace after the directive name.
    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;

    // Evalute the directive.
    if (s >= directive.size()) {
      // Error location 6
      String message = "#if with no expression";

      if (showErrors) {
        error(message);
      }

      stackOfBuffers
        .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                 presenceConditionManager.new
                                                 PresenceCondition(false),
                                                 directive.getLocation())));

      return new Error(message, false);

    } else {
      List<Syntax> tokens = new LinkedList<Syntax>();
      while (s < directive.size()) {
        Syntax syntax = (Syntax) directive.get(s);

        if (syntax.kind() == Kind.LANGUAGE) {
          tokens.add(syntax);
        }
        
        s++;
      }

      if (preprocessorStatistics || showConditionConfigs) {
        nestedConditionals.push(1);
      }

      BDD bdd = evaluateExpression(tokens, "if");
      
      presenceConditionManager.push();
      presenceConditionManager.enter(bdd);

      if (showPresenceConditions) {
        printPresenceCondition(directive.getLocation(), "if");
      }

      Conditional conditional = new Conditional(ConditionalTag.START,
                                                presenceConditionManager.reference(),
                                                directive.getLocation());

      return conditional;
    }
  }

  private void printPresenceCondition(Location loc, String type) {
    PresenceCondition pc = presenceConditionManager.reference();
    BDD bdd = pc.getBDD();

    int hashCode;
    if (! printedpc.containsKey(bdd.hashCode())) {
      String pcstr = pc.toString();
      hashCode = pcstr.hashCode();
      printedpc.put(bdd.hashCode(), hashCode);
      System.err.println("presence_condition," + hashCode + "," + pcstr);
    } else {
      hashCode = printedpc.get(bdd.hashCode());
    }
    pc.delRef();

    System.err.println("static_conditional," + type + "," + loc + "," + hashCode);
  }
  
  /**
   * Take expression tokens and return an expanded, completed, parsed,
   * and evaluated expression as a BDD.
   *
   * @param tokens The tokens of the expression to evaluate.
   */
  private BDD evaluateExpression(List<Syntax> tokens, String type) {

    // Add an end-of-expansion marker to the list of tokens to
    // preprocess it without reading any tokens after it.
    Layout eoe = new Layout("");
    eoe.setFlag(EOE);
    tokens.add(eoe);
    
    // Preprocess the tokens of the expression in case there are
    // macros.  Since conditionals may appear inside function-like
    // macro invocations, turn off prescanning.
    int savePrescanning = prescanning;
    prescanning = 0;

    int startingDepth = stackOfBuffers.size();

    stackOfBuffers.push(new PlainTokenBuffer(tokens));

    Set<String> seenConfigs = null;

    if (showConditionConfigs) seenConfigs = new HashSet<String>();

    List<Syntax> expanded = new LinkedList<Syntax>();
    while (true) {
      Syntax syntax = next();

      if (syntax.testFlag(EOE)) {
        break;
      }
      
      expanded.add(syntax);

      if (syntax.kind() == Kind.LANGUAGE
          && syntax.getTokenText().equals("defined")) {
        int collect = 1;  // The number of tokens left to collect.

        prescanning++;

        Syntax s;  // Used after the loop.
        while (true) {
          s = next();

          switch (s.kind()) {
          case CONDITIONAL:
            Conditional conditional = syntax.toConditional();
            switch (conditional.tag()) {
            case START:
              presenceConditionManager.push();
              // Fall through.
            case NEXT:
              presenceConditionManager
                .enter(syntax.toConditional().presenceCondition.getBDD().id());
              break;

            case END:
              presenceConditionManager.pop();
              break;
            }
            break;
          }

          if (s.testFlag(EOE)) {
            break;

          } else if (s.kind() == Kind.LANGUAGE
                     && s.toLanguage().tag().ppTag()
                     == PreprocessorTag.OPEN_PAREN) {
            // Collect two more tokens, the macro and the rparen.
            collect = 2;

          } else if (s.kind() == Kind.LANGUAGE
                     && s.toLanguage().tag().ppTag()
                     == PreprocessorTag.CLOSE_PAREN) {
            collect--;

          } else if (s.kind() == Kind.CONDITIONAL) {
            collect--;
            throw new RuntimeException("CONDITIONAL IN DEFINED OPERATION");

          } else if (s.kind() == Kind.LANGUAGE) {
            collect--;

          } else if (s.kind() == Kind.CONDITIONAL_BLOCK) {
            collect--;
            throw new RuntimeException("CONDITIONAL BLOCK IN DEFINED");
          }
          
          expanded.add(s);
          
          if (collect == 0 || (s.kind() == Kind.LANGUAGE
                               && s.toLanguage().tag().ppTag()
                               == PreprocessorTag.CLOSE_PAREN)) {
            break;
          }
        }
        prescanning--;

        if (s.testFlag(EOE)) {
          break;
        }
      } else /* not a "defined" expression */ {
        if (showConditionConfigs) {
          switch (syntax.kind()) {
          case LANGUAGE:
            if (syntax.toLanguage().tag().hasName() &&
                ! syntax.getTokenText().equals("defined")) {
              String containingMacro = getContainingMacro(stackOfBuffers,
                                                          startingDepth);
              // System.err.println("inside macro: " + containingMacro);
              // System.err.println("token in conditional: " + syntax.getTokenText());
              seenConfigs.add(syntax.getTokenText());
            }
            break;
          case CONDITIONAL:
            String containingMacro = getContainingMacro(stackOfBuffers,
                                                        startingDepth);
            // System.err.println("inside macro: " + containingMacro);          
            switch (syntax.toConditional().tag()) {
            case START:
              // Fall through.
            case NEXT:
              // System.err.println("conditional in conditional: " + syntax.toConditional().presenceCondition().getAllConfigs());          
              seenConfigs.addAll(syntax.toConditional().presenceCondition().
                                 getAllConfigs());
              break;

            case END:
              break;
            }
            break;
          case CONDITIONAL_BLOCK:
            System.err.println("CONDITIONAL BLOCK in conditional directive");
            break;
          }
        }
      }
    }

    stackOfBuffers.pop();
    prescanning = savePrescanning;
    
    // Trim leading whitespace.
    while (expanded.size() > 0 && expanded.get(0).kind() == Kind.LAYOUT) {
      expanded.remove(0);
    }

    // Collect conditionals into conditional blocks.
    PresenceCondition global = presenceConditionManager.reference();
    expanded = buildBlocks(expanded, global);
    global.delRef();
    global = null;
    
    // Complete conditional expressions.
    PresenceCondition currentPresenceCondition = presenceConditionManager.reference();
    ConditionalBlock hoistedBlock
      = hoistConditionals(expanded, currentPresenceCondition);

    currentPresenceCondition.delRef();  // Free the presence condition.
    currentPresenceCondition = null;

    expanded.clear();  // Free the list of expanded tokens after
                       // hoisting.
    expanded = null;

    List<List<Syntax>> completed = hoistedBlock.branches;
    List<PresenceCondition> presenceConditions = hoistedBlock.presenceConditions;

    // Union of all terms, where Term = PresenceCondition && CompletedExpression.
    List<BDD> terms = new LinkedList<BDD>();
    for (int i = 0; i < completed.size(); i++) {
      List<Syntax> tokenlist = completed.get(i);
      PresenceCondition presenceCondition = presenceConditions.get(i);

      if (! presenceCondition.isFalse()) {
        boolean unknown = false;

        tokenlist.add(EOF);
        if (showConditionConfigs) evaluator.setSeenConfigs(seenConfigs);
        BDD bdd = evaluator.evaluate(tokenlist.iterator());
        if (showConditionConfigs) evaluator.unsetSeenConfigs();

        // as a test compare new and old evaluators' outputs

        if (! bdd.isZero()) {
          terms.add(bdd.and(presenceCondition.getBDD()));
        }
          
        bdd.free();
      }

      presenceCondition.delRef();
    }

    // Take union of each subexpression term.  Use raw BDD operations
    // for efficiency.
    BDD newBdd = presenceConditionManager.getBDDFactory().zero();

    for (BDD term : terms) {
      BDD bdd = newBdd.or(term);

      term.free();
      newBdd.free();
      newBdd = bdd;
    }
    
    if (preprocessorStatistics || showConditionConfigs) {
      String configsOpt = "";

      if (showConditionConfigs) {
        configsOpt = " [" + joinSet(seenConfigs, ",") + "]";
      }

      System.err.format("conditional %s %s %s %d %d%s\n",
                        type, getNestedLocation(),
                        evaluator.sawNonboolean() ? "nonboolean" : "boolean",
                        nestedConditionals.size() - 1,
                        completed.size(),
                        configsOpt);
    }

    return newBdd;
  }
  
  /**
   * Process ifdef directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax ifdefDirective(Directive directive, int s) {

    // Move past the whitespace after the directive name.
    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    if (s >= directive.size()) {
      // Error location 7
      String message = "no macro name given in #ifdef directive";

      if (showErrors) {
        error(message);
      }

      stackOfBuffers
        .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                 presenceConditionManager.new
                                                 PresenceCondition(false),
                                                 directive.getLocation())));

      return new Error(message, false);

    } else {
      if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
          && ((Syntax) directive.get(s)).toLanguage().tag().hasName()) {
        // Valid macro name.

      } else {
        // Error location 8
        String message = "macro names must be identifiers";

        if (showErrors) {
          error(message);
        }

        stackOfBuffers
          .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                   presenceConditionManager.new
                                                   PresenceCondition(false),
                                                   directive.getLocation())));
        return new Error(message, false);
      }

      Set<String> seenConfigs = null;
      if (showConditionConfigs) seenConfigs = new HashSet<String>();
      if (showConditionConfigs) evaluator.setSeenConfigs(seenConfigs);

      BDD bdd
        = evaluator.evaluate(new ThreeTokenBuffer(DEFINED,
                                                  (Syntax) directive.get(s),
                                                  EOF));
      presenceConditionManager.push();
      presenceConditionManager.enter(bdd);
      
      if (showConditionConfigs) evaluator.unsetSeenConfigs();

      if (showPresenceConditions) {
        printPresenceCondition(directive.getLocation(), "ifdef");
      }

      if (preprocessorStatistics || showConditionConfigs) {
        String configsOpt = "";
        
        if (showConditionConfigs) {
          configsOpt = " [" + joinSet(seenConfigs, ",") + "]";
        }

        System.err.format("conditional %s %s %s %d %d%s\n",
                          "ifdef", getNestedLocation(),
                          "boolean",
                          nestedConditionals.size(),
                          1,
                          configsOpt);
        nestedConditionals.push(1);
      }

      Conditional conditional = new Conditional(ConditionalTag.START,
                                                presenceConditionManager.reference(),
                                                directive.getLocation());

      return conditional;
    }
  }
  
  /**
   * Process ifndef directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax ifndefDirective(Directive directive, int s) {

    // Move past the whitespace after the directive name.

    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    if (s >= directive.size()) {
      // Error location 9
      String message = "no macro name given in #ifndef directive";

      if (showErrors) {
        error(message);
      }

      stackOfBuffers
        .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                 presenceConditionManager.new
                                                 PresenceCondition(false),
                                                 directive.getLocation())));
      return new Error(message, false);

    } else {
      if (((Syntax) directive.get(s)).toLanguage().tag().hasName()) {
        // Valid macro name.

      } else {
        // Error location 10
        String message = "macro names must be identifiers";

        if (showErrors) {
          error(message);
        }

        stackOfBuffers
          .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                   presenceConditionManager.new
                                                   PresenceCondition(false),
                                                   directive.getLocation())));
        return new Error(message, false);
      }

      Set<String> seenConfigs = null;
      if (showConditionConfigs) seenConfigs = new HashSet<String>();
      if (showConditionConfigs) evaluator.setSeenConfigs(seenConfigs);

      BDD bdd
        = evaluator.evaluate(new ThreeTokenBuffer(DEFINED,
                                                  (Syntax) directive.get(s),
                                                  EOF));

      presenceConditionManager.push();
      presenceConditionManager.enter(bdd.not());
      bdd.free();

      if (showConditionConfigs) evaluator.unsetSeenConfigs();

      if (showPresenceConditions) {
        printPresenceCondition(directive.getLocation(), "ifndef");
      }

      if (preprocessorStatistics || showConditionConfigs) {
        String configsOpt = "";
        
        if (showConditionConfigs) {
          configsOpt = " [" + joinSet(seenConfigs, ",") + "]";
        }

        System.err.format("conditional %s %s %s %d %d%s\n",
                          "ifndef", getNestedLocation(),
                          "boolean",
                          nestedConditionals.size(),
                          1,
                          configsOpt);
        nestedConditionals.push(1);
      }

      Conditional conditional = new Conditional(ConditionalTag.START,
                                                presenceConditionManager.reference(),
                                                directive.getLocation());

      return conditional;
    }
  }
  
  /**
   * Process elif directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax elifDirective(Directive directive, int s) {

    // Move past the whitespace after the directive name.

    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    if (s >= directive.size()) {
      // Error location 11
      String message = "#if with no expression";

      if (showErrors) {
        error(message);
      }

      stackOfBuffers
        .push(new OneTokenBuffer(new Conditional(ConditionalTag.START,
                                                 presenceConditionManager.new
                                                 PresenceCondition(false),
                                                 directive.getLocation())));
      return new Error(message, false);
    } else {
      List<Syntax> tokens = new LinkedList<Syntax>();

      while (s < directive.size()) {
        Syntax syntax = (Syntax) directive.get(s);

        if (syntax.kind() == Kind.LANGUAGE) {
          tokens.add(syntax);
        }
        
        s++;
      }
      
      presenceConditionManager.enterElse();
      
      if (preprocessorStatistics || showConditionConfigs) {
        nestedConditionals.push(nestedConditionals.pop() + 1);
      }

      BDD bdd = evaluateExpression(tokens, "elif");
      
      presenceConditionManager.enterElif(bdd);

      if (showPresenceConditions) {
        printPresenceCondition(directive.getLocation(), "elif");
      }

      Conditional conditional = new Conditional(ConditionalTag.NEXT,
                                                presenceConditionManager.reference(),
                                                directive.getLocation());

      return conditional;
    }
  }
  
  /**
   * Process else directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax elseDirective(Directive directive, int s) {

    presenceConditionManager.enterElse();

    if (showPresenceConditions) {
      printPresenceCondition(directive.getLocation(), "else");
    }

    if (preprocessorStatistics || showConditionConfigs) {
      System.err.format("conditional %s %s %s %d %d\n",
                        "else", getNestedLocation(),
                        "boolean",
                        nestedConditionals.size() - 1,
                        1);
      nestedConditionals.push(nestedConditionals.pop() + 1);
    }

    Conditional conditional = new Conditional(ConditionalTag.NEXT,
                                              presenceConditionManager.reference(),
                                              directive.getLocation());

    return conditional;
  }
  
  /**
   * Process endif directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax endifDirective(Directive directive, int s) {

    try {
      presenceConditionManager.pop();

      if (preprocessorStatistics || showConditionConfigs) {
        int breadth = nestedConditionals.pop();

        System.err.format("endif %s %s %d\n",
                          getNestedLocation(),
                          nestedConditionals.size(),
                          breadth);
      }

    } catch (Exception e) {
      throw new RuntimeException("unmatched #endif found");
    }

    Conditional conditional = new Conditional(ConditionalTag.END,
                                              null,
                                              directive.getLocation());

    return conditional;
  }
  
  /**
   * Process include directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   * Computed macros are evaluated.  If the macro is multiply-defined,
   * we generate multiple includes that are wrapped in conditional
   * objects.  The preprocessor needs 
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   * @param includeNext Whether the include directive was an
   * #include_next directive.
   */
  private Syntax includeDirective(Directive directive, int s,
                                  boolean includeNext) {
    // Move past the whitespace after the directive name.
    while (s < directive.size()

           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    StringBuilder sb = new StringBuilder();
    
    // Combine all tokens before next whitespace.  Use a LinkedList
    // for access to removeLast().
    LinkedList<Syntax> tokens = new LinkedList<Syntax>();
    while (s < directive.size()
           && (((Syntax) directive.get(s)).kind() != Kind.LAYOUT)) {
      sb.append(((Syntax) directive.get(s)).getTokenText());
      tokens.add((Syntax) directive.get(s));
      s++;
    }
    
    while (s < directive.size()) {
      tokens.add((Syntax) directive.get(s));
      s++;
    }

    while (tokens.size() > 0 && tokens.getLast().kind() == Kind.LAYOUT) {
      tokens.removeLast();
    }
    
    String str = sb.toString();

    if (str.length() == 0) {
      // Error location 12
      String message = "#include expects \"FILENAME\" or <FILENAME>";

      if (showErrors) {
        error(message);
      }

      return new Error(message, false);
    } else {
      char first = str.charAt(0);
      char last = str.charAt(str.length() - 1);
      
      boolean sysHeader = false;
      if ('<' == first && '>' == last) {
        // System header.
        sysHeader = true;

      } else if ('"' == first && '"' == last) {
        // User header.  Nothing to do.

      } else {
        // Computed header.
          
        // Add an end-of-expansion marker.
        Layout eoe = new Layout("");
        eoe.setFlag(EOE);
        tokens.add(eoe);

        // Create and push a new token buffer for preprocessing.
        stackOfBuffers.push(new PlainTokenBuffer(tokens));
          
        List<Syntax> computed = new LinkedList<Syntax>();
        while (true) {
          Syntax syntax = next();
            
          if (syntax.testFlag(EOE)) {
            break;
          }
            
          computed.add(syntax);
        }
          
        stackOfBuffers.pop();
          
        // Build conditional blocks.  Then hoistConditionals is used
        // to hoist the conditionals around the include's
        // expression.
        PresenceCondition global = presenceConditionManager.reference();
        List<Syntax> blocks = buildBlocks(computed, global);
        global.delRef();
        global = null;
          
        // Make all combinations.
        PresenceCondition currentPresenceCondition = presenceConditionManager.reference();
        ConditionalBlock hoistedBlock
          = hoistConditionals(blocks, currentPresenceCondition);
        currentPresenceCondition.delRef();
        currentPresenceCondition = null;

        List<List<Syntax>> completed = hoistedBlock.branches;
        List<PresenceCondition> presenceConditions = hoistedBlock.presenceConditions;
          
        // Build strings and trim those using macros with unknown
        // definitions.
        List<String> completedStrings = new LinkedList<String>();
        for (int i = 0; i < completed.size(); i++) {
          List<Syntax> tokenlist = completed.get(i);
          PresenceCondition presenceCondition = presenceConditions.get(i);
          StringBuilder string = new StringBuilder();
          boolean unknown = false;
            
          for (Syntax token : tokenlist) {
            if (! (token.testFlag(UNKNOWN_DEF))) {
              string.append(token.getTokenText());
            }
            else {
              // Mark those containing unknown definitions.
              unknown = true;
              string.delete(0, string.length());
              string.append(token.getTokenText());
              break;
            }
          }
            
          if (! unknown) {
            completedStrings.add(string.toString());
          }
          else {
            if (showErrors) {
              warning("computed header used unknown " +
                                 "definition(s): " + string.toString());
            }
            completed.remove(i);
            presenceCondition.delRef();
            presenceConditions.remove(i);
            i--;
          }
        }
          
        return fileManager.includeComputedHeader(completedStrings, presenceConditions,
                                                 includeNext, presenceConditionManager,
                                                 macroTable);
      }

      // It is not a computed header.  Include the file normally.
        
      String headerName = str.substring(1, str.length() - 1);

      Syntax linemarker
        = fileManager.includeHeader(headerName, sysHeader, includeNext,
                                    presenceConditionManager, macroTable);

      return linemarker;
    }
  }

  /**
   * Process define directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   * This function parses the macro, determining whether its function-
   * or object-like and adds a new table entry given the current presenceCondition.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private void defineDirective(Directive directive, int s) {

    // Move past the whitespace after the directive name.

    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;

    if (s >= directive.size()) {
      // Error location 13
      String message = "no macro name given in #define directive";

      if (showErrors) {
        error(message);
      }
      stackOfBuffers.push(new OneTokenBuffer(new Error(message, false)));
      return;

    } else if (! ((Syntax) directive.get(s)).toLanguage().tag().hasName()) {
      // Error location 14
      String message = "macro names must be identifiers";

      if (showErrors) {
        error(message);
      }
      stackOfBuffers.push(new OneTokenBuffer(new Error(message, false)));
      return;

    } else {
      String name = ((Syntax) directive.get(s)).getTokenText();
      List<String> formals = null;
      LinkedList<Syntax> definition = null;  // Uses LinkedList.getLast().
      String variadic = null;
      
      // Move past the macro name.
      s++;
      boolean isFunctionlike = false;
      if (s < directive.size()) {
        
        // Check if macro is function-like.  If so, we need to parse
        // the macros formal arguments.  To be a function-like macro,
        // the macro name, e.g. "F", must be followed immediately by
        // an open paren, e.g. "F()".  "F ()" is an object-like macro
        // as in cpp_testsuite/cpp/function_false_function.c.
        
        if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
            && ((Syntax) directive.get(s)).toLanguage().tag().ppTag()
            == PreprocessorTag.OPEN_PAREN
            && ! ((Syntax) directive.get(s)).toLanguage()
            .testFlag(PREV_WHITE)) {
          // Move past paren.
          s++;
          
          do {
            // Move past whitespace.
            while (s < directive.size()
                   && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
            
            if (s >= directive.size()) {
              // Error location 19
              String message = "missing ')' in macro parameter list";

              if (showErrors) {
                error(message);
              }
              stackOfBuffers
                .push(new OneTokenBuffer(new Error(message, false)));
              return;
            }

            if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
                && ((Syntax) directive.get(s)).toLanguage().tag().hasName()) {
              // We are on a formal argument name.

              if (formals == null) {
                formals = new LinkedList<String>();
              }

              if (null != variadic) {
                // Error location 15
                String message = "missing ')' in macro parameter list";

                if (showErrors) {
                  error(message);
                }
                stackOfBuffers
                  .push(new OneTokenBuffer(new Error(message, false)));
                return;
              }

              // Check for named variadic.
              if (s < (directive.size() - 1)
                  && ((Syntax) directive.get(s + 1)).kind() == Kind.LANGUAGE
                  && ((Syntax) directive.get(s + 1)).toLanguage()
                  .tag().ppTag() == PreprocessorTag.ELLIPSIS) {
                if (null != variadic) {
                  // Error location 16
                  String message = "missing ')' in macro parameter list";

                  if (showErrors) {
                    error(message);
                  }
                  stackOfBuffers
                    .push(new OneTokenBuffer(new Error(message, false)));
                  return;
                }
                variadic = ((Syntax) directive.get(s)).getTokenText();
                s++;

              } else {
                formals.add(((Syntax) directive.get(s)).getTokenText());
              }

            } else if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
                       && ((Syntax) directive.get(s)).toLanguage()
                       .tag().ppTag() == PreprocessorTag.ELLIPSIS) {
              // The formal argument is variadic.
              if (null != variadic) {
                // Error location 17
                String message = "missing ')' in macro parameter list";

                if (showErrors) {
                  error(message);
                }
                stackOfBuffers
                  .push(new OneTokenBuffer(new Error(message, false)));
                return;
              }

              // The default name of the variadic argument.
              variadic = "__VA_ARGS__";

            } else if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
                       && ((Syntax) directive.get(s)).toLanguage()
                       .tag().ppTag() == PreprocessorTag.CLOSE_PAREN
                       && null == formals) {
              // Function-like macro with no arguments.  Done looking
              // for formals.
              s++;
              break;
            } else {
              // Error location 18
              String message = "missing ')' in macro parameter list";

              if (showErrors) {
                error(message);
              }

              stackOfBuffers
                .push(new OneTokenBuffer(new Error(message, false)));
              return;
            }
            
            s++;
            
            //move past whitespace
            while (s < directive.size()
                   && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;

            if (s >= directive.size()) {
              // Error location 20
              String message = "missing ')' in macro parameter list";

              if (showErrors) {
                error(message);
              }
              stackOfBuffers
                .push(new OneTokenBuffer(new Error(message, false)));
              return;
            }
            
            if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
                && ((Syntax) directive.get(s)).toLanguage().tag().ppTag()
                == PreprocessorTag.COMMA) {
              // Comma-separated formal arguments.
              s++;

            } else if (((Syntax) directive.get(s)).kind() == Kind.LANGUAGE
                       && ((Syntax) directive.get(s)).toLanguage()
                       .tag().ppTag() == PreprocessorTag.CLOSE_PAREN) {
              // Done looking for formals.
              s++;
              break;

            } else {
              throw new RuntimeException("unsupported error case");
            }
          } while (true);

          isFunctionlike = true;
        }
        
        // Move past the whitespace after the macro name.
        while (s < directive.size()
               && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
        
        if (s >= directive.size() ) {
          // Empty macro.

        } else {

          // Read in the macro definition, checking token-paste and
          // stringify operations.  The operators are removed and
          // instead the operands of pasting and stringification are
          // flagged as such.

          boolean followingPasteOp = false;
          boolean followingStringify = false;
          boolean prevWhite = false;
          final String pasteError
            = "'##' cannot appear at either end of a macro expansion";
          
          do {
            Syntax syntax = (Syntax) directive.get(s);

            if (isFunctionlike && syntax.kind() == Kind.LANGUAGE
                && syntax.toLanguage().tag().ppTag()
                == PreprocessorTag.HASH) {
              // Stringifification operator.
              
              // Stringification can only be done on macro arguments.
              // The following code checks for that.
              int ss = s + 1;
              boolean valid = false;
              while (ss < directive.size()) {
                Syntax next = (Syntax) directive.get(ss);
                if (next.kind() == Kind.LANGUAGE) {
                  if (null != formals
                      && formals.contains(next.getTokenText())) {
                    valid = true;

                  } else if (null != variadic
                             && next.getTokenText().equals(variadic)) {
                    valid = true;
                  }
                  break;
                }
                ss++;
              }
              
              if (! valid) {
                // Error location 21
                String message = "'#' is not followed by a macro parameter";

                if (showErrors) {
                  error(message);
                }

                stackOfBuffers
                  .push(new OneTokenBuffer(new Error(message, false)));
                return;
              }

            } else if (syntax.kind() == Kind.LANGUAGE
                       && syntax.toLanguage().tag().ppTag()
                       == PreprocessorTag.DOUBLE_HASH) {
              // Token-paste operator.

              // The token-paste operator is binary, so it can't
              // be the first token of the definition.
              if (null == definition) {
                // Error location 22

                if (showErrors) {
                  error(pasteError);
                }

                stackOfBuffers
                  .push(new OneTokenBuffer(new Error(pasteError, false)));
                return;
              }

              // Flag the previous token as the left operand of a
              // token-pasting.
              definition.getLast().setFlag(PASTE_LEFT);
              
            } else if (syntax.kind() == Kind.LANGUAGE) {
              // A regular token.
              Language<?> token;
              
              token = (Language<?>) syntax;
              
              if (null == definition) {
                definition = new LinkedList<Syntax>();
              }

              if (prevWhite) {
                // Flag the token as having whitespace before it.
                // Whitespace tokens are removed from macro
                // definitions.
                token.setFlag(PREV_WHITE);
              }
              
              if (followingStringify) {
                // Flag the token as a stringification argument.
                token.setFlag(STRINGIFY_ARG);
              }
              
              definition.add(token);
              
            } else if (syntax.kind() == Kind.LAYOUT
                       && (! followingStringify)) {
              // Whitespace.
              if (null != definition) {
                prevWhite = true;
              }
            }
            
            if (syntax.kind() == Kind.LANGUAGE) {
              followingPasteOp = syntax.kind() == Kind.LANGUAGE &&
                syntax.toLanguage().tag().ppTag()
                == PreprocessorTag.DOUBLE_HASH;
              followingStringify = syntax.kind() == Kind.LANGUAGE &&
                syntax.toLanguage().tag().ppTag() == PreprocessorTag.HASH;
              
              if (! followingStringify) {
                // If the stringification operator has whitespace
                // before it, flag the stringification argument
                // instead, since we remove the operator.
                prevWhite = false;
              }
            }
            
            s++;
          } while (s < directive.size());
          
          if (followingPasteOp) {
            // Error location 23

            // The token-pasting operator can't appear at the end of a
            // definition since it's a binary operator.
            if (showErrors) {
              error(pasteError);
            }

            stackOfBuffers
              .push(new OneTokenBuffer(new Error(pasteError, false)));
            return;
          }
        }
      }

      // Clear the first token's PREV_WHITE flag.
      if (null != definition) {
        definition.getFirst().clearFlag(PREV_WHITE);
      }

      // Create and store the macro definitions in the macro symbol
      // table.
      Macro macro;
      if (isFunctionlike) {
        macro = new Macro.Function(formals, definition, variadic);
      } else {
        macro = new Macro.Object(definition);
      }
      
      macroTable.define(name, macro, presenceConditionManager);

      if (preprocessorStatistics) {
        System.err.format("define %s %s %s %d\n",
                          name, isFunctionlike ? "fun" : "var",
                          directive.getLocation(),
                          macroTable.countDefinitions(name));
      }
    }
  }
  
  /**
   * Process undef directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private void undefDirective(Directive directive, int s) {
    // Move past the whitespace after the directive name.
    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    // Evaluate the undef directive as long as it's valid.
    if (s >= directive.size()) {
      // Error location 24
      String message = "no macro name given in #undef directive";

      if (showErrors) {
        error(message);
      }
      stackOfBuffers
        .push(new OneTokenBuffer(new Error(message, false)));
    } else {
      Syntax token = (Syntax) directive.get(s);

      if (token.kind() == Kind.LANGUAGE
          && token.toLanguage().tag().hasName()) {
        String name = token.getTokenText();

        macroTable.undefine(name, presenceConditionManager);

        if (preprocessorStatistics) {
          System.err.format("undef %s %s %d\n",
                            name, directive.getLocation(),
                            macroTable.countDefinitions(name));
        }
      } else {
        // Error location 25
        String message = "macro names must be identifiers";

        if (showErrors) {
          error(message);
        }
        stackOfBuffers
          .push(new OneTokenBuffer(new Error(message, false)));
      }
    }
  }
  
  /**
   * Process line directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private void lineDirective(Directive directive, int s) {
    if (preprocessorStatistics) {
      System.err.format("line_directive %s", getNestedLocation());
    }
  }
  
  /**
   * Process error directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Error errorDirective(Directive directive, int s) {
    // Error location 26
    if (showErrors) {
      error(directive.getTokenText());
    }

    if (EMPTY_INVALID_BRANCHES) {
      PresenceCondition current = presenceConditionManager.reference();
      PresenceCondition union = invalid.or(current);
      invalid.delRef();
      current.delRef();
      invalid = union;
    }

    if (preprocessorStatistics) {
      System.err.format("error_directive %s", getNestedLocation());
    }

    if (printErrorConditions || saveErrorConstraints) {
      PresenceCondition cur = presenceConditionManager.reference();
      PresenceCondition errorCond = cur.not();
      cur.delRef();
      if (printErrorConditions) {
        // System.err.format("extra_constraint %s\n", errorCond.toCNF());
        if (null == printConstraints) printConstraints = new ArrayList<PresenceCondition>();
        // add non-negated constraint
        printConstraints.add(cur.addRef());
      }
      if (saveErrorConstraints) {
        // save negated constraint
        errorConstraints.add(errorCond.toCNF());
      }
      errorCond.delRef();
    }

    return new Error(directive.getTokenText(), true);
  }
  
  /**
   * Process warning directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Error warningDirective(Directive directive, int s) {
    // Error location 27
    if (showErrors) {
      warning(directive.getTokenText());
    }

    if (preprocessorStatistics) {
      System.err.format("warning_directive %s", getNestedLocation());
    }

    return new Error(directive.getTokenText(), ErrorType.WARNING);
  }
  
  /**
   * Process pragma directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private void pragmaDirective(Directive directive, int s) {
    while (s < directive.size()
           && ((Syntax) directive.get(s)).kind() == Kind.LAYOUT) s++;
    
    if (s < directive.size()) {
      Syntax token = (Syntax) directive.get(s);

      if (token.kind()
          == Kind.LANGUAGE && token.toLanguage().tag().hasName()) {
        String name = token.getTokenText();

        if (name.equals("superc_bdd")) {
          PresenceCondition current = presenceConditionManager.reference();
          System.out.println(current);
          current.delRef();
        }
      }
    }

    if (preprocessorStatistics) {
      System.err.format("pragma_directive %s", getNestedLocation());
    }
  }
  
  /**
   * Process line directive.  This takes the list of syntactic units
   * and the position of the first syntax after the directive name.
   *
   * @param directive The tokens of the directive.
   * @param s The number of tokens after the directive name.
   */
  private Syntax lineMarker(Directive directive, int s) {
    return EMPTY;
  }
  
  // get around capture of ? to ? warning
  @SuppressWarnings("unchecked")
  /**
   * Check a token to see if it's a defined macro and expand if necessary.
   * Multiply-defined macros are expanded to all definitions, but
   * wrapped with conditionals.  The Preprocessor must check for conditional
   * objects to update the presenceCondition and also to normalize token-pasting
   * and stringification that involve conditionals
   *
   * @param token The token to try to expand.  This methods assumes
   * token.tag().hasName() is true.
   * @return A token.
   */
  private Syntax processToken(Language<?> token) {
    String name = token.getTokenText();

    // Process built-in macros.
    if (name.startsWith("__")) {
      if (name.equals("__FILE__")) {
        // Emit the current filename.
        String fileName = fileManager.include.getLocation().file;
        
        List<Syntax> list = new LinkedList<Syntax>();
        list.add(tokenCreator.createStringLiteral("\"" + fileName + "\""));
        
        stackOfBuffers.push(new SingleExpansionBuffer(name, list));
        // Disable the macro so it can't be recursively expanded.
        macroTable.disable(name);

        if (preprocessorStatistics) {
          System.err.format("object %s %s %d %d %d\n",
                            name, getNestedLocation(),
                            getMacroNestingDepth(), 1, 1);
        }
        return EMPTY;
      } else if (name.equals("__LINE__")) {
        // Emit the current line number.
        int lineNumber = location.line;

        List<Syntax> list = new LinkedList<Syntax>();
        list.add(tokenCreator.createIntegerConstant(lineNumber));
        
        stackOfBuffers.push(new SingleExpansionBuffer(name, list));
        // Disable the macro so it can't be recursively expanded.
        macroTable.disable(name);
        
        if (preprocessorStatistics) {
          System.err.format("object %s %s %d %d %d\n",
                            name, getNestedLocation(),
                            getMacroNestingDepth(), 1, 1);
        }
        return EMPTY;
      } else if (name.equals("__BASE_FILE__")) {
        // Emit the base filename.
        String fileName = fileManager.baseFile;
        
        List<Syntax> list = new LinkedList<Syntax>();
        list.add(tokenCreator.createStringLiteral("\"" + fileName + "\""));
        
        stackOfBuffers.push(new SingleExpansionBuffer(name, list));
        // Disable the macro so it can't be recursively expanded.
        macroTable.disable(name);

        if (preprocessorStatistics) {
          System.err.format("object %s %s %d %d %d\n",
                            name, getNestedLocation(),
                            getMacroNestingDepth(), 1, 1);
        }
        return EMPTY;
      }
    }

    if (! macroTable.contains(name)) {
      // This token is not a macro name.
      return token;

    } else if (token.testFlag(NO_EXPAND)) {
      // Even though this token is a macro name, it has been set for
      // no expansion to prevent recursion.
      return token;

    } else if (! macroTable.isEnabled(name)) {
      // Prevent recursion as required by the C preprocessor
      // specification.
      token = (Language<?>) token.copy();
      token.setFlag(NO_EXPAND);
      return token;

    } else {
      // This token is a macro name.  Expand it.
      List<Entry> entries = macroTable.get(name, presenceConditionManager);

      // Check whether this macro has any definitions in the current
      // presence condition and if any of them are function-like macro
      // definitions.
      if (null == entries) {
        return token;

      } else {
        boolean hasDefinition = false;
        boolean hasFunction = false;
        for (Entry e : entries) {
          if (Macro.State.DEFINED == e.macro.state
              && ! token.testFlag(NON_FUNCTION)) {
            hasDefinition = true;
            if (e.macro.isFunction()) hasFunction = true;
          }
        }

        if (hasDefinition) {
          if (hasFunction) {
            if (token.testFlag(HOISTED_FUNCTION)) {
              return expandFunction(name, token, entries);
            } else {
              return expandAndHoistFunction(name, token, entries);
            }
          } else {
            return expandObject(name, token, entries);
          }
        } else {
          return token;
        }
      }  // if there are entries under the current presence condition
    }
  }

  /**
   * Hoist conditionals around a list of tokens.  Depending on an
   * internal flag setting, OPTIMIZE_HOISTING, this method will call
   * one of two hoisting methods, an unoptimized one or an optimized
   * one.  Both are preserved in the implementation for performance
   * evaluation.
   *
   * @param list The list of tokens where the conditionals to be
   * hoisted are.
   * @param presenceCondition The presence condition to perform the hoisting in.
   * Please delRef after calling this method.
   * @return The hoisted conditional block.  It's branches have no
   * conditionals in them.
   */
  private ConditionalBlock hoistConditionals(List<Syntax> list,
                                             PresenceCondition presenceCondition) {
    List<List<Syntax>> newBranches = new LinkedList<List<Syntax>>();
    List<PresenceCondition> newPresenceConditions = new LinkedList<PresenceCondition>();
    Location location = null;
    if (null != list && list.size() > 0) location = list.get(0).getLocation();

    newBranches.add(new LinkedList<Syntax>());
    newPresenceConditions.add(presenceCondition.addRef());

    if (OPTIMIZED_HOISTING) {
      hoistConditionalsOptimized(newBranches, newPresenceConditions, 0, 1, list);
    } else {
      hoistConditionalsOriginal(list, newBranches, newPresenceConditions);
    }

    return new ConditionalBlock(newBranches, newPresenceConditions, location);
  }


  /**
   * Hoist conditionals around a list of tokens that may contain
   * conditionals.  This method returns a list of token-lists and the
   * presence condition of each token-list via parameters.
   *
   * @param list The list of tokens in the expression.
   * @param tokenlists Returns the hoisted expressions.  Intialized by
   * caller.
   * @param presenceConditions Returns the hoisted expressions' presence
   * conditions.  Initialized by caller.
   */
  private void hoistConditionalsOriginal(List<Syntax> list,
                                         List<List<Syntax>> tokenlists,
                                         List<PresenceCondition> presenceConditions) {
    for (Syntax s : list) {
      if (s.kind() == Kind.LANGUAGE) {
        for (List<Syntax> tokenlist : tokenlists) {
          tokenlist.add(s);
        }

      } else if (s.kind() == Kind.CONDITIONAL_BLOCK) {
        ConditionalBlock block = (ConditionalBlock) s;
        List<List<Syntax>> newTokenlists = new LinkedList<List<Syntax>>();
        List<PresenceCondition> newPresenceConditions = new LinkedList<PresenceCondition>();

        for (int i = 0; i < block.presenceConditions.size(); i++) {
          List<Syntax> branch = block.branches.get(i);
          PresenceCondition presenceCondition = block.presenceConditions.get(i);

          List<List<Syntax>> branchTokenlists = new LinkedList<List<Syntax>>();
          List<PresenceCondition> branchPresenceConditions = new LinkedList<PresenceCondition>();
          branchTokenlists.add(new LinkedList<Syntax>());
          branchPresenceConditions.add(presenceCondition);
          presenceCondition.addRef();
          
          hoistConditionalsOriginal(branch, branchTokenlists, branchPresenceConditions);
          
          // Combine strings and bdds with newStrings and newBdds.
          for (int a = 0; a < tokenlists.size(); a++) {
            for (int b = 0; b < branchTokenlists.size(); b++) {
              List<Syntax> tokenlist = new LinkedList<Syntax>();
              tokenlist.addAll(tokenlists.get(a));
              tokenlist.addAll(branchTokenlists.get(b));

              PresenceCondition newPresenceCondition = presenceConditions.get(a).and(branchPresenceConditions.get(b));
              if (! newPresenceCondition.isFalse()) {
                newTokenlists.add(tokenlist);
                newPresenceConditions.add(newPresenceCondition);
              }
              else {
                newPresenceCondition.delRef();
              }
            }
          }
          
          for (PresenceCondition c : branchPresenceConditions) {
            c.delRef();
          }
        }
        
        tokenlists.clear();
        tokenlists.addAll(newTokenlists);

        for (PresenceCondition c : presenceConditions) {
          c.delRef();
        }
        presenceConditions.clear();
        presenceConditions.addAll(newPresenceConditions);
        
        block.free();
      }
    }
  }
  
  /**
   * Hoist conditionals.
   *
   * @param newBranches
   * @param newPresenceConditions
   * @param start (inclusive)
   * @param end (exclusive)
   * @param list
   * @param The new end of the span.
   */
  private int hoistConditionalsOptimized(List<List<Syntax>> newBranches,
                                         List<PresenceCondition> newPresenceConditions,
                                         int start, int end,
                                         List<Syntax> list) {
    if (end <= start) return end;

    // Process each token in the list, flattening blocks along the
    // way.
    for (Syntax syntax : list) {
      switch (syntax.kind()) {
      case LANGUAGE:
        // Add language tokens to each branch in the range [start,
        // end).
        for (int i = start; i < end; i++) {
          newBranches.get(i).add(syntax);
        }
        break;

      case CONDITIONAL_BLOCK:
        // Take all combinations of the branches in current range
        // [start, end) and this conditional blocks branches.
        ConditionalBlock thisBlock = (ConditionalBlock) syntax;

        // Pull off the branches in the range [start, end) that are to
        // be combined with the new block.
        int span = end - start;
        List<List<Syntax>> spanBranches = new LinkedList<List<Syntax>>();
        List<PresenceCondition> spanPresenceCondition = new LinkedList<PresenceCondition>();

        for (int i = 0; i < span; i++) {
          spanBranches.add(newBranches.get(start));
          newBranches.remove(start);
          spanPresenceCondition.add(newPresenceConditions.get(start));
          newPresenceConditions.remove(start);
        }

        // For each branch in this conditional block, (1) copy the
        // branches in the current range and (2) call flatten on the
        // copied branches.
        int subStart = start;
        int subEnd = subStart;

        for (int i = 0, size = thisBlock.branches.size(); i < size; i++) {
          PresenceCondition thisBranchPresenceCondition = thisBlock.presenceConditions.get(i);

          for (int j = 0; j < span; j++) {
            // Get the new presence condition.  Only add the branch if
            // the new presence condition is not false.

            PresenceCondition subPresenceCondition = spanPresenceCondition.get(j).and(thisBranchPresenceCondition);

            if (subPresenceCondition.isFalse()) {
              // Do not add the mutually exclusive branch.
              subPresenceCondition.delRef();

            } else {
              // Add the new branch.
              List<Syntax> copyBranch
                = new LinkedList<Syntax>(spanBranches.get(j));

              newBranches.add(subEnd, copyBranch);
              newPresenceConditions.add(subEnd, subPresenceCondition);
              subEnd++;
            }
          }

          subEnd = hoistConditionalsOptimized(newBranches, newPresenceConditions,
                                              subStart, subEnd,
                                              thisBlock.branches.get(i));
          subStart = subEnd;
        }

        // Update the indices of the [start, end) range.  Start stays
        // the same, but the end increases with the number of combined
        // branches.
        end = subEnd;

        // Free the original branches that were pulled off new block.
        for (int i = 0, size = spanPresenceCondition.size(); i < size; i++) {
          spanPresenceCondition.get(i).delRef();
        }

        break;

      default:
        // Do nothing with other types of tokens.
        break;
      }
    }

    return end;
  }

  /** An object containing a token and it's presence condition. */
  private static class ConditionalSyntax {
    public Syntax syntax;
    public PresenceCondition presenceCondition;
    
    public ConditionalSyntax(Syntax syntax, PresenceCondition presenceCondition) {
      this.syntax = syntax;
      this.presenceCondition = presenceCondition;
    }

    public String toString() {
      return syntax + " " + presenceCondition;
    }
  }

  /**
   * Expand an object-like macro invocation.  This method will expand
   * all definitions valid under the current presence condition.  For
   * UNDEFINED and FREE table entries, the original macro token is
   * emitted.  Also, to support macros that are defined both as
   * object-like and function-like, this method will also just emit
   * the original macro when the macro is defined as function-like.
   * This matches the behavior of the preprocessor when a
   * function-like macro invocation has no argument list: the original
   * macro name remains and the macro is not expanded.
   *
   * @param token The macro name token.
   * @param entries The definitions of the macro from the macro table.
   * @return A line marker to trace invocations.
   */
  private Syntax expandObject(String name, Syntax token, List<Entry> entries) {
    // Before expanding, check whether the preprocessor needs to
    // output the expansion(s) in a conditional.  Necessary when (1)
    // there is more than expansion or (2) the expansion is in a
    // different presence condition.
    boolean needConditional = true;
    if (entries.size() == 1) {
      PresenceCondition presenceCondition = presenceConditionManager.reference();
      PresenceCondition and = presenceCondition.and(entries.get(0).presenceCondition);
      presenceCondition.delRef();
        
      needConditional = ! presenceConditionManager.is(and);
      and.delRef();
    }

    // Collect statistics.
    if (preprocessorStatistics) {
      int nused = 0;
      for (Entry e : entries) {
        if (Macro.State.DEFINED == e.macro.state) {
          nused++;
        }
      }

      System.err.format("object %s %s %d %d %d\n",
                        name, getNestedLocation(),
                        getMacroNestingDepth(),
                        macroTable.countDefinitions(name),
                        nused);
    }

    // Expand the object-like macro.
    if (needConditional) {
      List<List<Syntax>> lists = new LinkedList<List<Syntax>>();
      List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();
      PresenceCondition nonDefined = null;

      for (Entry e : entries) {
        switch (e.macro.state) {
        case DEFINED:
          presenceConditions.add(e.presenceCondition);

          if (! e.macro.isFunction()) {
            if (token.testFlag(PREV_WHITE)
                && e.macro.definition != null
                && e.macro.definition.size() > 0) {
              List<Syntax> replacement = new LinkedList<Syntax>();
              replacement.addAll(e.macro.definition);
              Syntax copy = replacement.get(0).copy();
              copy.setFlag(PREV_WHITE);
              replacement.set(0, copy);

              lists.add(replacement);
            } else {
              lists.add(e.macro.definition);
            }
            // Disable the macro so it can't be recursively expanded.
            macroTable.disable(name);
          } else {
            List<Syntax> replacement = new LinkedList<Syntax>();
            replacement.add(token);
            lists.add(replacement);
          }
          break;

        default:
          if (null == nonDefined) {
            nonDefined = e.presenceCondition;
          } else {
            PresenceCondition union = nonDefined.or(e.presenceCondition);
            nonDefined.delRef();
            nonDefined = union;
          }
          break;
        }
      }

      if (null != nonDefined) {
        presenceConditions.add(nonDefined);

        List<Syntax> replacement = new LinkedList<Syntax>();
        replacement.add(token);
        lists.add(replacement);
      }

      stackOfBuffers.push(new MultipleExpansionBuffer(name,
                                                      lists,
                                                      presenceConditions,
                                                      token.getLocation()));
      // Don't free entries since their presenceConditions are reused in the
      // resulting conditional.
    } else {
      Entry e = entries.get(0);
      List<Syntax> replacement;

      if (Macro.State.DEFINED == e.macro.state && ! e.macro.isFunction()) {
        if (token.testFlag(PREV_WHITE)
            && e.macro.definition != null
            && e.macro.definition.size() > 0) {
          replacement = new LinkedList<Syntax>();
          replacement.addAll(e.macro.definition);
          Syntax copy = replacement.get(0).copy();
          copy.setFlag(PREV_WHITE);
          replacement.set(0, copy);
        } else {
          replacement = e.macro.definition;
        }
        // Disable the macro so it can't be recursively expanded.
        macroTable.disable(name);
      } else {
        replacement = new LinkedList<Syntax>();
        replacement.add(token);
      }

      stackOfBuffers.push(new SingleExpansionBuffer(name, replacement));
      macroTable.free(entries);
    }

    // Return a line marker containing the macro name.
    return EMPTY; //return new Marker(name, fileManager.include.getLocation());
  }

  /**
   * Expand a function-like macro invocation.  This method assumes
   * that it will see a well-formed function-like invocation call.
   * This means that hoisting is already done, there is an
   * argument-list that begins immediately after the function name,
   * all argument-delimiting tokens appear in the current presence
   * condition, all nested conditionals are well-formed, and the
   * invocation consists only of valid tokens and directives, e.g. no
   * #include directives.  The method expandAndHoistFunction ensures
   * that all of the above is true, so it should always be called
   * before this method.  In fact, expandAndHoistFunction will call
   * this method if no hoisting is necessary; otherwise it will set
   * the HOISTED_FUNCTION flag on the function name, signalling the
   * preprocessor to call this method.
   *
   * Per the GNU C Preprocessor implementation, function-like
   * arguments are collected with preprocessing turned off.  Then they
   * are prescanned for macros before binding the formals with the
   * actuals.  Furthermore stringified and token-pasted arguments do
   * not get preprocessed before binding.
   *
   * Arguments are in a comma-delimited list that is surrounded by
   * parentheses.  Parentheses may be nested in arguments, and commas
   * in nested parentheses do not separate arguments. Function-like
   * macro invocations can have regular tokens, conditionals, and the
   * directives define, undef, error, and warning.
   *
   * This method follows the gcc preprocessor implementation.  The
   * pseudo-code for this algorithm is the following:<br>
   * <pre>
   * if (funlike)
   *  fun funlike_invocation_p
   *    check for paren
   *    fun collect_args
   *      for each argument
   *        call cpp_get_token
   *        while tracking parens and commas
   *          commas must be nesting == 0
   *          don't forget to capture variadics!
   *
   *  fun replace_args
   *    loop through tokens in func macro def
   *      if we encounter an arg
   *        stringify the arg
   *        expand the arg
   *          fun expand_arg
   *            call push_ptoken_presenceCondition of the args tokens
   *            call cpp_get_token
   *              buffer resulting tokens and store for arg replacement
   *            call _cpp_pop_presenceCondition
   *    now we replace the args in the func macro def, loop through
   *      replace expanded, stringified, and do pasting
   *      swallow the comma on variadic arg
   *
   * call _cpp_push_token_presenceCondition of the macro's definition (w/args replaced)
   * </pre>
   *
   * @param name The macro name as a string.
   * @param token The macro name as a token instance.
   * @param entries The definitions of the macro from the macro table.
   * @return A line marker.
   */
  private Syntax expandFunction(String name, Syntax token,
                                List<Entry> entries) {
    // Save the original tokens of the invocation to back out of an
    // invalid invocation and to preserve the arguments when there are
    // object-like definitions.  Uses LinkedList.addFirst().
    LinkedList<Syntax> buffer = new LinkedList<Syntax>();

    // Track the invocation's arguments, parens, variadics, etc.
    FunctionInvocation function = new FunctionInvocation();
    LinkedList<LinkedList<Syntax>> args = new LinkedList<LinkedList<Syntax>>();
    args.add(null);

    // Check for a definition with a variadic argument.
    boolean hasVariadic = false;
    for (Entry e : entries) {
      if (e.macro.isFunction()) {
        if (((Function) e.macro).isVariadic()) {
          hasVariadic = true;
          break;
        }
      }
    }

    // If any definitions have a variadic argument save the
    // arguments their commas and whitespace.
    LinkedList<LinkedList<Syntax>> variadicArgs;
    if (hasVariadic) {
      variadicArgs = new LinkedList<LinkedList<Syntax>>();
      variadicArgs.add(new LinkedList<Syntax>());
    } else {
      variadicArgs = null;
    }

    // Parse the arguments of the invocation.
    Syntax syntax;
    prescanning++;
    while (true) {
      // Get the next token.
      syntax = next();

      // Update the presence condition and evaluate define/undef
      // directives as permissible by the GNU C Preprocessor.
      boolean isConditional = false;
      switch (syntax.kind()) {
      case DIRECTIVE:
        Directive directive = syntax.toDirective();
        
        switch(directive.tag()) {
        case IF:
          // Fall through.
        case IFDEF:
          // Fall through.
        case IFNDEF:
          // Fall through.
        case ELIF:
          // Fall through.
        case ELSE:
          // Fall through.
        case ENDIF:
          syntax = evaluateDirective(directive);
          break;

        case DEFINE:
          // Fall through.
        case UNDEF:
          evaluateDirective(directive);
          break;

        default:
          // Do nothing.
          break;
        }
        break;

      case CONDITIONAL:
        Conditional conditional = syntax.toConditional();
        switch (conditional.tag()) {
        case START:
          presenceConditionManager.push();
          // Fall through.
        case NEXT:
          presenceConditionManager.enter(syntax.toConditional().presenceCondition.getBDD().id());
          break;

        case END:
          presenceConditionManager.pop();
          break;
        }
        break;
      }

      // Save the tokens in a buffer.
      buffer.add(syntax);

      // Build the list of arguments.
      switch (function.parse(syntax)) {
      case ARGUMENT_WHITESPACE:
        if (args.getLast() == null) {
          // Add the whitespace to the end of the last variadic
          // argument.
          if (hasVariadic && function.argc > 1) {
            variadicArgs.get(variadicArgs.size() - 2)
              .add(syntax);
          }

          // Trim leading whitespace by not adding it to the argument.
          break;
        } else {
          // Fall through to add the whitespace.
        }

      case ARGUMENT_TOKEN:
        if (args.getLast() == null) {
          args.removeLast();
          args.add(new LinkedList<Syntax>());
        }

        if (args.getLast().size()
            == 0 && syntax.testFlag(PREV_WHITE)) {
          // Remove the leading whitespace caused by an argument
          // that contains a nested function-like macro expansion.
          // For example: #define _ASM_ALIGN __ASM_SEL(.balign 4,
          // .balign 8) from
          // linux-2.6.38/arch/x86/include/asm/asm.h:22.  The
          // token ".balign" should not have leading whitespace
          // when "__ASM_SEL" is expanded.

          syntax = syntax.copy();
          syntax.clearFlag(PREV_WHITE);
        }

        // Add this token to the current argument.
        args.getLast().add(syntax);
        if (hasVariadic) {
          variadicArgs.getLast().add(syntax);
        }
        break;

      case ARGUMENT_DELIMITER:
        // Add the comma to the variadic arg.
        if (hasVariadic) {
          variadicArgs.getLast().add(syntax);
        }

        // Initialize the next argument.
        function.argc++;
        args.add(null);
        if (hasVariadic) {
          variadicArgs.add(new LinkedList<Syntax>());
        }
        break;

      default:
        // Do nothing.
        break;
      }

      if (function.done) {
        break;
      }
    }
    prescanning--;

    // Trim trailing whitespace.  Important for stringification and
    // pasting, e.g. cpp/token_pasting_linux.c.
    for (int i = 0, size = args.size(); i < size; i++) {
      LinkedList<Syntax> arg = args.get(i);

      if (null != arg) {
        while (arg.getLast().kind() == Kind.LAYOUT) {
          arg.removeLast();
        }
          
        if (arg.size() == 0) {
          args.set(i, null);
        }
      }
    }

    if (FunctionInvocation.Result.VALID == function.result) {
      // Expand the invocation.
      replaceArgs(name, token, args, variadicArgs,
                  entries, buffer);

      if (preprocessorStatistics) {
        int nused = 0;

        for (Entry e : entries) {
          if (Macro.State.DEFINED == e.macro.state) {
            nused++;
          }
        }

        System.err.format("function %s %d %s %d %d %d\n",
                          token.getTokenText(),
                          args.size(),
                          getNestedLocation(),
                          getMacroNestingDepth(),
                          macroTable.countDefinitions(token.getTokenText()),
                          nused);
      }
      return EMPTY; //return new Marker(name, fileManager.include.getLocation());

    } else {
      throw new RuntimeException("expandFunction expects valid function");
    }
  }

  /**
   * Expand a function-like macro invocation.  This method will, if
   * necessary, hoisting conditionals around the invocation, its name,
   * and its arguments.  First the invocation is parsed.  If hoisting
   * is necessary, the method simultaneous parsing each unique
   * invocation, saving the parsing state, tokens, and presence
   * condition of the invocation.  Then it expands each hoisted
   * invocation for all possible definitions of the macro.
   *
   * @param name The macro name as a string.
   * @param token The macro name token.
   * @param entries The definitions of the macro from the macro table.
   * @return A line marker or an empty layout token.
   */
  private Syntax expandAndHoistFunction(String name, Syntax token,
                                        List<Entry> entries) {
    // The algorithm works like this: First we collect the list of
    // presence conditions in which there are different function-like
    // macro invocations.

    // This flag is tripped whenever there is a fork needed,
    // i.e. whenever the parentheses or commas that delimit the
    // argument list appear in a different presence condition than the
    // macro name.
    boolean needHoist = false;

    // Save the original tokens of the invocation to back out of an
    // invalid invocation and to preserve the arguments when there are
    // object-like definitions.  Uses LinkedList.addFirst().
    LinkedList<Syntax> buffer = new LinkedList<Syntax>();

    // Save the presenceConditionManager's state.  This is necessary to back out
    // the changes in presence condition (due to conditionals inside
    // of the function-like macro invocation).

    PresenceConditionManager savedManager = presenceConditionManager;
    presenceConditionManager = new PresenceConditionManager(presenceConditionManager);

    // Initialize the list of invocations with the first one.
    List<FunctionInvocation> functions = new LinkedList<FunctionInvocation>();
    {
      FunctionInvocation firstFunction
        = new FunctionInvocation();
      functions.add(firstFunction);
    }
    List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();
    presenceConditions.add(presenceConditionManager.reference());

    // Parse the arguments of the invocation.
    Syntax syntax;
    prescanning++;
    while (true) {
      // Get the next token.
      syntax = next();

      // Only need to fork when the presence condition may have
      // changed due to a conditional.
      boolean presenceConditionChanged = false;

      // Update the presence condition.
      switch (syntax.kind()) {
      case DIRECTIVE:
        Directive directive = syntax.toDirective();
        
        switch(directive.tag()) {
        case IF:
          // Fall through.
        case IFDEF:
          // Fall through.
        case IFNDEF:
          // Fall through.
        case ELIF:
          // Fall through.
        case ELSE:
          // Fall through.
        case ENDIF:
          Syntax conditional = evaluateDirective(directive);
          if (conditional.kind() == Kind.CONDITIONAL
              && null != conditional.toConditional().presenceCondition) {
            conditional.toConditional().presenceCondition.delRef();
          }
          presenceConditionChanged = true;
          break;

        default:
          // Do nothing.
          break;
        }
        break;

      case CONDITIONAL:
        Conditional conditional = syntax.toConditional();
        switch (conditional.tag()) {
        case START:
          presenceConditionManager.push();
          // Fall through.
        case NEXT:
          presenceConditionManager.enter(syntax.toConditional().presenceCondition.getBDD().id());
          presenceConditionChanged = true;
          break;

        case END:
          presenceConditionManager.pop();
          presenceConditionChanged = true;
          break;
        }
        break;
      }

      buffer.add(syntax);

      // Stop parsing when all invocations are done.
      boolean allDone = true;

      // Update the state of each invocation.  This loop may add new
      // invocations, altering the size of the functions list.
      for (int i = 0; i < functions.size(); i++) {
        FunctionInvocation function = functions.get(i);
        PresenceCondition presenceCondition = presenceConditions.get(i);
        PresenceCondition current = presenceConditionManager.reference();
        PresenceCondition and = presenceCondition.and(current);

        if (! and.isFalse()) {
          if (! presenceCondition.is(current)) {
            // Save the state of the invocation in case we need to fork.
            boolean done = function.done;
            int parenDepth = function.parenDepth;
            int argc = function.argc;
            FunctionInvocation.Result result = function.result;

            // Fork new invocations when the parentheses or commas of
            // the argument-list are controlled by conditionals, since
            // this modifies the number of arguments or whether the
            // invocation is valid or not.
            switch (function.parse(syntax)) {
            case OPEN_PAREN:
              // Fall through.
            case ARGUMENT_DELIMITER:
              // Fall through.
            case CLOSE_PAREN:
              // Need a new invocation when the token's presence
              // condition is differenct than the invocation's.

              // The forked invocation's presence condition is mutually
              // exclusive to the current invocation's.
              PresenceCondition newPresenceCondition = presenceCondition.andNot(current);

              // Update the current invocation's presence condition.
              PresenceCondition updatedPresenceCondition = presenceCondition.and(current);
              presenceCondition.delRef();
              presenceConditions.set(i, updatedPresenceCondition);

              // Add the forked invocation.
              if (! newPresenceCondition.isFalse()) {
                FunctionInvocation newFunction = new FunctionInvocation();

                // The forked invocation has the same state as the current
                // invocation _before_ the last call to parse.
                newFunction.done = done;
                newFunction.parenDepth = parenDepth;
                newFunction.argc = argc;
                newFunction.result = result;

                functions.add(i + 1, newFunction);
                presenceConditions.add(i + 1, newPresenceCondition);
                i++;
                allDone = false;
              } else {
                newPresenceCondition.delRef();
              }

              needHoist = true;
              break;

            default:
              // Do nothing.
              break;
            }

          } else {
            function.parse(syntax);
          }
        }

        current.delRef();
        and.delRef();

        if (! function.done) {
          allDone = false;
        }  // if not done parsing the invocation
      } // for each function invocation

      // Stop when all invocations are done.
      if (allDone) {
        break;
      }
    }
    prescanning--;

    // Restore the original presenceConditionManager state.
    presenceConditionManager.free();
    presenceConditionManager = savedManager;

    // Expand the function invocation if it doesn't need hoisting or
    // hoist conditionals around the invocation.
    if (! needHoist) {
      // No hoisting necessary.
      switch (functions.get(0).result) {
      case VALID:
        stackOfBuffers.push(new PlainTokenBuffer(buffer));
        // Expand the invocation.
        expandFunction(name, token, entries);
        break;

      case INCOMPLETE_ARGUMENTS:
        // Error location 28
        String message = "unterminated argument list invoking macro \""
          + token.getTokenText() + "\"";

        if (showErrors) {
          error(message);
        }

        // Don't emit the partial list of arguments.  Only emit the
        // original token name and, unless it's a conditional, the token
        // that interrupted the list.
        stackOfBuffers.push(new TwoTokenBuffer(token, buffer.getLast()));
        stackOfBuffers.push(new OneTokenBuffer(new Error(message, false)));
        break;

      case NO_ARGUMENTS:
        // Back up the tokens read after the macro name when looking
        // for the opening paren.
        stackOfBuffers.push(new PlainTokenBuffer(buffer));

        // The function-like macro name is at the end of an expansion
        // (EOE).  This can be at the end of (1) another function-like
        // macro's argument expansion, (2) at the end of a conditional
        // expression's expansion, or (3) at the end of a computed
        // include's expansion.  expandArg() will clear the
        // NON_FUNCTION flag, since there may be parentheses in the
        // body of the function-like macro.  See
        // cpp/function_arguments_real_function.c for an example.
        Language<?> copy = (Language<?>) token.copy();
        copy.setFlag(NON_FUNCTION);

        // Expand any object-like definitions of the macros.
        expandObject(name, copy, entries);
        break;

      default:
        throw new RuntimeException("invalid function invocation type");
      }
    } else {
      // Hoist conditionals around the invocation.

      // Save the presenceConditionManager.
      PresenceConditionManager oldManager = presenceConditionManager;
      presenceConditionManager = new PresenceConditionManager(presenceConditionManager);

      // (1) Tag each token with their presence condition.
      List<ConditionalSyntax> cbuffer = new LinkedList<ConditionalSyntax>();
      for (Syntax s : buffer) {
        // Update the presence condition.
        switch (s.kind()) {
        case DIRECTIVE:
          Directive directive = s.toDirective();
        
          switch(directive.tag()) {
          case IF:
            // Fall through.
          case IFDEF:
            // Fall through.
          case IFNDEF:
            // Fall through.
          case ELIF:
            // Fall through.
          case ELSE:
            // Fall through.
          case ENDIF:
            Syntax conditional = evaluateDirective(directive);
            if (conditional.kind() == Kind.CONDITIONAL
                && null != conditional.toConditional().presenceCondition) {
              conditional.toConditional().presenceCondition.delRef();
            }
            cbuffer.add(new ConditionalSyntax(s, null));
            break;

          default:
            cbuffer.add(new ConditionalSyntax(s, presenceConditionManager.reference()));
            break;
          }
          break;

        case CONDITIONAL:
          Conditional conditional = s.toConditional();
          switch (conditional.tag()) {
          case START:
            presenceConditionManager.push();
            // Fall through.
          case NEXT:
            presenceConditionManager.enter(s.toConditional().presenceCondition.getBDD().id());

            break;

          case END:
            presenceConditionManager.pop();
            break;
          }
          cbuffer.add(new ConditionalSyntax(s, null));
          break;

        default:
          cbuffer.add(new ConditionalSyntax(s, presenceConditionManager.reference()));
          break;
        }
      }

      // Restore the original presenceConditionManager.
      presenceConditionManager.free();
      presenceConditionManager = oldManager;

      // (2) Build a new buffer containing all the invocations in
      // surrounded by conditonals.
      List<Syntax> hoisted = new LinkedList<Syntax>();
      for (int i = 0, size = functions.size(); i < size; i++) {
        FunctionInvocation function = functions.get(i);
        PresenceCondition presenceCondition = presenceConditions.get(i);

        // Put each invocation in a conditional controlled by its
        // presence condition.
        if (0 == i) {
          hoisted.add(new Conditional(ConditionalTag.START,
                                      presenceCondition.addRef(),
                                      token.getLocation()));
        } else {
          hoisted.add(new Conditional(ConditionalTag.NEXT,
                                      presenceCondition.addRef(),
                                      token.getLocation()));
        }

        switch (function.result) {
        case VALID:
          // Tell the preprocessor that it need do hoisting again.
          Language<?> functionName = (Language<?>) token.copy();
          functionName.setFlag(HOISTED_FUNCTION);

          hoisted.add(functionName);

          // Traverse the original invocation building well-formed
          // conditionals.
          PresenceCondition currentPresenceCondition = presenceCondition.addRef();
          boolean hasNestedConditional = false;
          for (ConditionalSyntax csyntax : cbuffer) {
            Syntax s = csyntax.syntax;
            PresenceCondition c = csyntax.presenceCondition;
            boolean isConditional = false;

            // Don't emit conditionals.
            switch (s.kind()) {
            case CONDITIONAL:
              isConditional = true;
              break;

            case DIRECTIVE:
              switch (s.toDirective().tag()) {
              case IF:
                // Fall through.
              case IFDEF:
                // Fall through.
              case IFNDEF:
                // Fall through.
              case ELIF:
                // Fall through.
              case ELSE:
                // Fall through.
              case ENDIF:
                isConditional = true;
                break;
              }
              break;
            }

            if (! isConditional) {
              PresenceCondition and = c.and(presenceCondition);
              if (! and.isFalse()) {
                // This complicated code puts tokens with the same
                // presence condition inside the same conditional.
                if (! and.is(currentPresenceCondition)) {

                  if (hasNestedConditional) {
                    hoisted.add(new Conditional(ConditionalTag.END,
                                                null,
                                                token.getLocation()));
                  }
                  if (! and.is(presenceCondition)) {
                    hoisted.add(new Conditional(ConditionalTag.START,
                                                and.addRef(),
                                                token.getLocation()));
                    hasNestedConditional = true;
                  } else {
                    hasNestedConditional = false;
                  }
                  currentPresenceCondition.delRef();
                  currentPresenceCondition = and.addRef();
                }
                hoisted.add(s);
              }  // if (! and.isFalse())
              and.delRef();
            }
          }
          break;

        case INCOMPLETE_ARGUMENTS:
          // Error location 29
          String message = "unterminated argument list invoking macro \""
            + token.getTokenText() + "\"";

          if (showErrors) {
            error(message);
          }

          // Don't emit the partial list of arguments.  Only emit the
          // original token.
          Language<?> noexpand = (Language<?>) token.copy();
          noexpand.setFlag(NO_EXPAND);
          hoisted.add(new Error(message, false));
          hoisted.add(noexpand);
          break;

        case NO_ARGUMENTS:
          // The function-like macro name is at the end of an expansion
          // (EOE).  This can be at the end of (1) another function-like
          // macro's argument expansion, (2) at the end of a conditional
          // expression's expansion, or (3) at the end of a computed
          // include's expansion.  expandArg() will clear the
          // NON_FUNCTION flag, since there may be parentheses in the
          // body of the function-like macro.  See
          // cpp/function_arguments_real_function.c for an example.
          Language<?> nonfunction = (Language<?>) token.copy();
          nonfunction.setFlag(NON_FUNCTION);
          hoisted.add(nonfunction);
          break;

        default:
          throw new RuntimeException("invalid function invocation type");
        }
      }

      hoisted.add(new Conditional(ConditionalTag.END, null, token.getLocation()));

      // Find the presence condition of tokens not in any of the
      // invocations.
      PresenceCondition notUnion;
      {
        PresenceCondition union = presenceConditions.get(0).addRef();
        for (int i = 1, size = presenceConditions.size(); i < size; i++) {
          PresenceCondition newUnion = union.or(presenceConditions.get(i));
          union.delRef();
          union = newUnion;
        }
        
        notUnion = union.not();
        union.delRef();
      }

      // (3) Write out the conditionals that were in the original
      // invocation.  This ensures that any conditionals that were
      // broken by the invocation don't get mismatched.  Also save any
      // tokens that weren't part of any invocation.
      List<ConditionalSyntax> orphanTokens
        = new LinkedList<ConditionalSyntax>();
      for (ConditionalSyntax csyntax : cbuffer) {
        Syntax s = csyntax.syntax;
        boolean isConditional = false;

        // Emit all conditionals to ensure matching.  See
        // cpp/function_if_weird_paren5.c.
        switch (s.kind()) {
        case CONDITIONAL:
          isConditional = true;
          break;

        case DIRECTIVE:
          switch (s.toDirective().tag()) {
          case IF:
            // Fall through.
          case IFDEF:
            // Fall through.
          case IFNDEF:
            // Fall through.
          case ELIF:
            // Fall through.
          case ELSE:
            // Fall through.
          case ENDIF:
            isConditional = true;
            break;
          }
          break;
        }

        if (isConditional) {
          hoisted.add(s);
        } else {
          PresenceCondition nonInvocation = csyntax.presenceCondition.and(notUnion);
          if (! nonInvocation.isFalse()) {
            if (JOIN_ORPHANS) {
              nonInvocation.delRef();
              hoisted.add(csyntax.syntax);
            } else {
              csyntax.presenceCondition.delRef();
              csyntax.presenceCondition = nonInvocation;
              orphanTokens.add(csyntax);
            }
          } else {
            nonInvocation.delRef();
          }
        }
      }

      // (4) Emit any orphan tokens.
      if (orphanTokens.size() > 0) {
        PresenceCondition current = orphanTokens.get(0).presenceCondition;
        hoisted.add(new Conditional(ConditionalTag.START,
                                    current.addRef(),
                                    token.getLocation()));
        for (ConditionalSyntax s : orphanTokens) {
          if (! s.presenceCondition.is(current)) {
            current = s.presenceCondition;
            hoisted.add(new Conditional(ConditionalTag.END,
                                        null,
                                        token.getLocation()));
            hoisted.add(new Conditional(ConditionalTag.START,
                                        current.addRef(),
                                        token.getLocation()));
          }
          hoisted.add(s.syntax);
        }
        hoisted.add(new Conditional(ConditionalTag.END,
                                    null,
                                    token.getLocation()));
      }

      // System.err.println("buffer: " + buffer);
      // System.err.println("\ncbuffer: " + cbuffer);
      // System.err.println("\npresenceConditions: " + presenceConditions);
      // System.err.println("\nhoisted: " + hoisted);

      // Clean up presence conditions.
      for (ConditionalSyntax csyntax : cbuffer) {
        PresenceCondition presenceCondition = csyntax.presenceCondition;

        if (null != presenceCondition) {
          csyntax.presenceCondition.delRef();
        }
      }
      for (PresenceCondition presenceCondition : presenceConditions) {
        presenceCondition.delRef();
      }
      notUnion.delRef();

      // Put the hoisted function of the stack for preprocessing.
      stackOfBuffers.push(new PlainTokenBuffer(hoisted));

      if (preprocessorStatistics) {
        int nhoisted = 0;

        for (FunctionInvocation function : functions) {
          if (FunctionInvocation.Result.VALID == function.result) {
            nhoisted++;
          }
        }

        System.err.format("hoist_function %s %s %d %d\n",
                          token.getTokenText(),
                          getNestedLocation(),
                          getMacroNestingDepth(),
                          nhoisted);
      }
    }

    return EMPTY;
  }

  /**
   * This class abstracts away the parsing of a function-like macro
   * invocation for use by both hoisting and expansion.  It
   * encapsulates the state needed, such argument count paren nesting
   * depth, and provides a method parse() which takes a token, updates
   * the parsing state, and indicates the role the token plays in the
   * invocation, e.g. a comma-delimiter or open parenthesis.
   */
  private static class FunctionInvocation {
    /** True when the invocation is complete or had an error. */
    public boolean done;

    /**
     * Whether the valid or how it's invalid.  Only set after done is
     * true.
     */
    public Result result;
    enum Result {
      VALID,  // Valid invocation with argument list.
        NO_ARGUMENTS,  // No opening paren.
        INCOMPLETE_ARGUMENTS, // Unterminated argument list.
        }

    /** The number of arguments. */
    public int argc;

    /** The parentheses nesting depth. */
    public int parenDepth;

    public FunctionInvocation() {
      this.done = false;
      this.argc = 1;
      this.parenDepth = 0;
    }

    /** The role a token plays in the invocation. */
    enum Role {
      BEFORE_ARGUMENTS,  // Token appears between name and open paren.
        ARGUMENT_TOKEN,  // Token is part of the argument.
        ARGUMENT_WHITESPACE,  // Token whitespace in argument.
        OPEN_PAREN,  // Token is the open paren of the arg list.
        ARGUMENT_DELIMITER,  // Token is the comma-delimiter.
        CLOSE_PAREN,  // Token is the close paren of the arg list.
        TERMINATOR,  // An EOF or EOE token.
        AFTER_ARGUMENTS, // Token appears after the argument list.
        }

    /**
     * Parse one token of the invocation and return the role of that
     * token in the invocation.
     *
     * @param syntax The token.
     * @return The role the token plays in the invocation.
     */
    public Role parse(Syntax syntax) {
      if (done) return Role.AFTER_ARGUMENTS;

      if (0 == parenDepth) {
        // Process tokens between macro name and opening paren.

        // Check for an open paren, directives, EOF, and EOE.
        switch (syntax.kind()) {
        case LANGUAGE:
          if (PreprocessorTag.OPEN_PAREN == syntax.toLanguage().tag().ppTag()) {
            parenDepth++;
            return Role.OPEN_PAREN;
          } else {
            done = true;
            result = Result.NO_ARGUMENTS;
            return Role.BEFORE_ARGUMENTS;
          }

        case DIRECTIVE:
          done = true;
          result = Result.NO_ARGUMENTS;
          return Role.BEFORE_ARGUMENTS;

        case EOF:
          // No arguments list.  Not a function-like invocation.
          done = true;
          result = Result.NO_ARGUMENTS;
          return Role.BEFORE_ARGUMENTS;

        default:
          if (syntax.testFlag(EOE)) {
            done = true;
            result = Result.NO_ARGUMENTS;
          }
          return Role.BEFORE_ARGUMENTS;
        }

      } else {
        // Process the tokens of the argument list.

        // Check for a comma-delimiter, parens, EOF, and EOE.
        switch (syntax.kind()) {
        case LANGUAGE:
          switch (syntax.toLanguage().tag().ppTag()) {
          case OPEN_PAREN:
            parenDepth++;
            return Role.ARGUMENT_TOKEN;

          case CLOSE_PAREN:
            if (parenDepth-- == 1) {
              // This is the end of the argument list.
              done = true;
              result = Result.VALID;
              return Role.CLOSE_PAREN;
            } else {
              return Role.ARGUMENT_TOKEN;
            }

          case COMMA:
            if (1 == parenDepth) {
              // This is the end of the argument list.  Only commas
              // outside of nested parentheses delimit arguments.
              return Role.ARGUMENT_DELIMITER;
            } else {
              return Role.ARGUMENT_TOKEN;
            }

          default:
            return Role.ARGUMENT_TOKEN;
          }

        case EOF:
          // Unterminated argument list.
          done = true;
          result = Result.INCOMPLETE_ARGUMENTS;
          return Role.TERMINATOR;

        case LAYOUT:
          if (syntax.testFlag(EOE)) {
            // Unterminated argument list.
            done = true;
            result = Result.INCOMPLETE_ARGUMENTS;
            return Role.TERMINATOR;
          } else {
            return Role.ARGUMENT_WHITESPACE;
          }

        default:
          return Role.ARGUMENT_TOKEN;
        }
      }
    }
  }
  
  /**
   * Substitute the formal parameters in a macro definition with the
   * actual parameters from the macro invocation and push the
   * invocation onto the token buffer stack.
   *
   * @param token The name of the function-like macro.
   * @param args The actual parameters.  Empty arguments are
   * represented by a null.
   * @param variadicArgs The actual parameters including commas and
   * whitespace.
   * @param entries The macro definitions from the macro symbol table.
   * @param buffer The raw tokens of the macro invocation, except the
   * macro name itself.
   */
  private void replaceArgs(String name,
                           Syntax token,
                           LinkedList<LinkedList<Syntax>> args,
                           LinkedList<LinkedList<Syntax>> variadicArgs,
                           List<Entry> entries,
                           LinkedList<Syntax> buffer) {
    List<List<Syntax>> expanded = null;
    List<List<Syntax>> blockArgs = null;
    List<List<Syntax>> stringified = null;

    // Expand and stringify arguments, but if they are actually used
    // in some definition.
    for (Entry e : entries) {
      if (e.macro.isFunction()) {
        // Skip empty definitions.
        if (null == e.macro.definition) continue;
        
        Function f = (Function) e.macro;

        // Skip definitions without arguments.
        if (null == f.formals) continue;

        // Expand and stringify arguments.  Delay expanding and
        // stringifying variadics, since the number of arguments in
        // the variadic depends on the definition.
        for (int i = 0; i < f.definition.size(); i++ ) {
          Syntax t = f.definition.get(i);
         
          if (! (t.kind() == Kind.LANGUAGE
                 && t.toLanguage().tag().hasName())) continue;
          
          int indexOfFormal = f.formals.indexOf(t.getTokenText());
          
          if (indexOfFormal >= args.size()) {
            indexOfFormal = -1;
          }
          
          if (indexOfFormal >= 0) {
            // The token is a formal argument for the current
            // definition.
            
            if (t.testFlag(STRINGIFY_ARG)) {
              // Stringify the argument.  Stringified arguments are
              // _not_ expanded before stringification.

              if (null == stringified) {
                stringified = new ArrayList<List<Syntax>>();
                for (int init = 0; init < args.size(); init++) {
                  stringified.add(null);
                }
              }

              if (null == stringified.get(indexOfFormal)) {
                PresenceCondition global = presenceConditionManager.reference();

                if (null == blockArgs) {
                  blockArgs = new ArrayList<List<Syntax>>(args.size());
                  for (int init = 0; init < args.size(); init++) {
                    blockArgs.add(null);
                  }
                }
                if (null == blockArgs.get(indexOfFormal)) {
                  blockArgs.set(indexOfFormal,
                                buildBlocks(args.get(indexOfFormal), global));
                }
                stringified.set(indexOfFormal,
                                stringifyArg(blockArgs.get(indexOfFormal),
                                             global));
                global.delRef();
              }

            } else if (t.testFlag(PASTE_LEFT)
                       || (i > 0 && f.definition.get(i - 1)
                           .testFlag(PASTE_LEFT))) {
              // Operands to the token-paste operator are _not_
              // expanded.

              if (null == blockArgs) {
                blockArgs = new ArrayList<List<Syntax>>(args.size());
                for (int init = 0; init < args.size(); init++) {
                  blockArgs.add(null);
                }
              }

              if (null == blockArgs.get(indexOfFormal)) {
                PresenceCondition global = presenceConditionManager.reference();

                blockArgs.set(indexOfFormal,
                              buildBlocks(args.get(indexOfFormal), global));
                global.delRef();
              }

            } else {
              // Expand the argument (i.e. prescan.)

              if (null == expanded) {
                expanded = new ArrayList<List<Syntax>>();
                for (int init = 0, size = args.size(); init < size; init++) {
                  expanded.add(null);
                }
              }

              if (null == expanded.get(indexOfFormal)
                  && null != args.get(indexOfFormal)) {
                expanded.set(indexOfFormal,
                             expandArg(args.get(indexOfFormal)));
              }
            } // Stringify, paste, or expand.
          } // If the token is an argument name.
        } // For each token in the definition.
      } // If it's a function-like macro definition.
    } // For each definition.

    // Subsitute the arguments for each definition.  The result is a
    // list of expansions of the macro.
    List<List<Syntax>> lists = new LinkedList<List<Syntax>>();
    List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();
    PresenceCondition nonFunction = presenceConditionManager.new PresenceCondition(false);

    for (Entry e : entries) {
      if (e.macro.isFunction()) {
        Function f = (Function) e.macro;
        
        // Check that the number of formal arguments matches the
        // number of actuals.  Because of variadics, the number of
        // actuals may legally be greater than the number of formals.
        boolean argsCheck = false;
        if (null == f.formals || f.formals.size() == 0) {
          if (! f.isVariadic()) {
            argsCheck = null == args
              || args.size() == 0
              || args.size() == 1
              && (null == args.get(0) || args.get(0).size() == 0);

            // Determine whether the invocation has no
            // arguments.  It has no arguments if there is only one
            // argument and it contains no regular tokens.
            if (args.size() == 1 && null != args.get(0)
                && args.get(0).size() > 0) {
              argsCheck = true;

              for (Syntax s : args.get(0)) {
                if (s.kind() == Kind.LANGUAGE) {
                  argsCheck = false;
                  break;
                }
              }
            }
            
          } else {
            argsCheck = true;
          }

        } else {
          if (null != args && args.size() == f.formals.size()) {
            argsCheck = true;

          } else if (f.isVariadic() && args.size() >= (f.formals.size() + 1)) {
            argsCheck = true;
          }
        }


        // If the argument number checks out, replace parameters in
        // the definition.
        List<Syntax> replaced;
        if (! argsCheck) {
          // Error location 30
          int passed = null == args ? 0 : args.size();
          int takes = null == f.formals ? 0 : f.formals.size();
          String message;

          if (passed > takes) {
            message = "macro \"" + name + "\" passed " + passed
              + " arguments, but takes just " + takes;
          } else {
            message = "macro \"" + name + "\" requires " + takes
              + " arguments, but only " + passed + " given";
          }

          // The number of arguments does not match the number of
          // formal arguments.
          if (showErrors) {
            error(message + " at " + location.toString());
          }

          // The GNU preprocessor does not expand the macro.  All it
          // does is output the original macro name without the formal
          // parameter list.
          Language<?> newToken = (Language<?>) token.copy();
          newToken.setFlag(NO_EXPAND);
          replaced = new LinkedList<Syntax>();
          replaced.add(new Error(message, false));
          replaced.add(newToken);
          
        } else if (null == f.definition) {
          // The definition was empty, so it expands to nothing.
          replaced = null;

        } else {
          // Substitute the formal arguments with the actual
          // arguments for each definition.

          LinkedList<Syntax> varArg = null;  // Uses
                                             // LinkedList.{get|remove}Last().
          List<Syntax> varStr = null;
          List<Syntax> varBlock = null;
          List<Syntax> varExp = null;
          
          replaced = new LinkedList<Syntax>();
          
          //Expand and stringify the variadic argument if the current
          //definition has one.
          for (int i = 0; i < f.definition.size(); i++ ) {
            Syntax t = f.definition.get(i);
            
            if (! (t.kind() == Kind.LANGUAGE
                   && t.toLanguage().tag().hasName())) continue;

            if (f.isVariadic() && t.getTokenText().equals(f.variadic)) {
              if (null == varArg) {
                // Construct the variadic argument out of several actual
                // arguments.

                varArg = new LinkedList<Syntax>();
                
                for (int argi = null == f.formals ? 0 : f.formals.size();
                     argi < variadicArgs.size(); argi++) {
                  if (null != variadicArgs.get(argi)) {
                    for (Syntax s : variadicArgs.get(argi)) {
                      varArg.add(s);
                    }
                  }
                }
                
                // Remove trailing padding.
                while (varArg.size() > 0
                       && varArg.getLast().kind() == Kind.LAYOUT) {
                  varArg.removeLast();
                }
              }
              
              if (t.testFlag(STRINGIFY_ARG)) {
                // Stringify the variadic argument.

                if (null == varStr) {
                  PresenceCondition  global = presenceConditionManager.reference();

                  if (null == varBlock) {
                    varBlock = buildBlocks(varArg, global);
                  }
                  varStr = stringifyArg(varBlock, global);
                  global.delRef();
                }

              } else if (t.testFlag(PASTE_LEFT)
                         || (i > 0 && f.definition.get(i - 1)
                             .testFlag(PASTE_LEFT))) {
                // Operands to token-pasting are _not_ expanded.  Save
                // the unexpanded variadic argument.

                if (null == varBlock) {
                  PresenceCondition global = presenceConditionManager.reference();

                  varBlock = buildBlocks(varArg, global);
                  global.delRef();
                }

              } else {
                // Expand the variadic argument.
                
                if (null == varExp && null != varArg) {
                  varExp = expandArg(varArg);
                }
              }
            }
          }

          // Finally, substitute the formals with the actuals.
          for (int i = 0; i < f.definition.size(); i++) {
            Syntax t = f.definition.get(i);

            // Substitute the argument if the token names one.
            int indexOfFormal;
            if (null != f.formals) {
              indexOfFormal = f.formals.indexOf(t.getTokenText());
            } else {
              indexOfFormal = -1;
            }
            
            boolean variadic = false;
            if (f.isVariadic() && t.getTokenText().equals(f.variadic)) {
              variadic = true;
            }

            if (indexOfFormal < 0 && ! variadic) {
              if ( (i < f.definition.size() - 1)
                   && null != f.variadic
                   && f.variadic.equals(f.definition.get(i + 1).getTokenText())
                   && t.kind() == Kind.LANGUAGE
                   && t.toLanguage().tag().ppTag() == PreprocessorTag.COMMA
                   && t.testFlag(PASTE_LEFT)
                   ) {
                // The following implements a GCC preprocessor
                // feature.  When an empty variaidic argument is
                // pasted with a comma, the comma is removed.  If the
                // variadic is not empty, no pasting occurs.

                if (args.size() == f.formals.size()) {
                  // Swallow the comma (don't add it to the expanded
                  // definition.)  Then skip the variadic argument
                  // since we know it's empty.
                  i++;

                } else {
                  // Don't attempt to paste the comma with the
                  // variadic.  Even though there are no tokens that
                  // can be pasted with a comma, this avoids the error
                  // message that would be emitted.
                  Language<?> newcomma;
                  
                  newcomma = (Language<?>) t.copy();
                  newcomma.clearFlag(PASTE_LEFT);
                  replaced.add(newcomma);
                }
                
              } else {
                // It's not a formal argument, so just pass it
                // through.
                replaced.add(t);
              }

            } else {
              
              // We found a formal argument.  Substitute it with the
              // actual argument.

              List<Syntax> argArg = null;
              List<Syntax> argStr = null;
              List<Syntax> argBlock = null;
              List<Syntax> argExp = null;

              if (variadic) {
                argArg = varArg;
                argStr = varStr;
                argBlock = varBlock;
                argExp = varExp;

              } else {
                argArg = args.get(indexOfFormal);
                if (null != stringified) {
                  argStr = stringified.get(indexOfFormal);
                }
                if (null != blockArgs) {
                  argBlock = blockArgs.get(indexOfFormal);
                }
                if (null != expanded) {
                  argExp = expanded.get(indexOfFormal);
                }
              }
              
              if (t.testFlag(STRINGIFY_ARG)) {
                // No need since stringifyArg checks for PREV_WHITE itself.
                // if (t.testFlag(PREV_WHITE)
                //     && argStr != null && argStr.size() > 0) {
                //   replaced.add(SPACE);
                // }
                replaced.addAll(argStr);

              } else if (t.testFlag(PASTE_LEFT)) {
                // Expand a macro argument that is the left operand of
                // a token-paste operation.  Only the _last_ token of
                // the actual argument gets pasted, so add the
                // PASTE_LEFT flag to it.
                
                List<Syntax> arg = argBlock;
                if (arg.size() > 0) {
                  Syntax last = (Syntax) arg.get(arg.size() - 1);
    
                  if (null != arg) {
                    if (t.testFlag(PREV_WHITE)) {
                      replaced.add(SPACE);
                    }

                    for (Syntax a : arg) {
                      if (a != last) {
                        replaced.add(a);
                      }
                    }
                  
                    // Copy the token that will received the
                    // PASTE_LEFT token.  This is necessary since the
                    // actual argument may be substituted elsewhere,
                    // i.e. not as the left operand of a
                    // token-pasting.

                    last = (Syntax) last.copy();
                    last.setFlag(PASTE_LEFT);
                    replaced.add(last);
                  }
                }

              } else if ( i > 0 && f.definition.get(i - 1)
                          .testFlag(PASTE_LEFT)) {
                // Expand a macro argument that is the right operand
                // of a token-paste operation.  The only thing we need
                // to do special here is check for an empty argument.
                List<Syntax> arg = argBlock;

                if (null != arg && arg.size() > 0) {
                  if (t.testFlag(PREV_WHITE)) {
                    replaced.add(SPACE);
                  }

                  for (Syntax a : arg) {
                    replaced.add(a);
                  }
                  
                } else {
                  // The argument is empty, so add a special token to
                  // avoid the token-paste.
                  replaced.add(AVOID_PASTE_TOKEN);
                }

              } else if (null != argExp) {
                // Substitute a formal argument with an actual.

                if (t.testFlag(PREV_WHITE) && argExp != null
                    && argExp.size() > 0) {
                  replaced.add(SPACE);
                }

                for (Syntax a : argExp) {
                  replaced.add(a);
                }

              }
            }
          }
        }
        presenceConditions.add(e.presenceCondition);
        lists.add(replaced);
      } else {
        // Don't expand object-like, free, or undefined entries.
        // Instead disjoin their presence conditions and emit the raw
        // tokens of the invocation in a separate token buffer for
        // later preprocessing.
        PresenceCondition union = nonFunction.or(e.presenceCondition);
        nonFunction.delRef();
        nonFunction = union;
      }
    }

    macroTable.free(entries);
    
    // Check whether we need a conditional for the expansion.  When
    // there is only one definition and it is from the same presence
    // condition, we don't need a conditional around the expanded
    // definition(s).
    boolean needConditional = true;
    if (lists.size() == 1) {
      PresenceCondition presenceCondition = presenceConditionManager.reference();
      PresenceCondition and = presenceCondition.and(presenceConditions.get(0));
      presenceCondition.delRef();

      needConditional = ! presenceConditionManager.is(and);
      and.delRef();
    }

    // Preserve the PREV_WHITE tag of the invoking macro token.
    if (token.testFlag(PREV_WHITE)) {
      for (List<Syntax> list : lists) {
        if (null != list && list.size() > 0) {
          Syntax copy = list.get(0).copy();
          copy.setFlag(PREV_WHITE);
          list.set(0, copy);
        }
      }
    }

    if (! nonFunction.isFalse()) {
      // Push a token buffer for the raw tokens of the invocation if
      // there for object, free, and undefined entries.
      List<Syntax> rawTokens = new LinkedList<Syntax>();
      rawTokens.add(new Conditional(ConditionalTag.START,
                                    nonFunction,
                                    token.getLocation()));
      rawTokens.add(token);
      rawTokens.addAll(buffer);
      rawTokens.add(new Conditional(ConditionalTag.END,
                                    null,
                                    token.getLocation()));
      stackOfBuffers.push(new PlainTokenBuffer(rawTokens));
    } else {
      nonFunction.delRef();
    }

    // Push a token buffer with the macro expansion for preprocessing.
    if (needConditional) {
      stackOfBuffers.push(new MultipleExpansionBuffer(name,
                                                      lists,
                                                      presenceConditions,
                                                      token.getLocation()));
    } else {
      stackOfBuffers.push(new SingleExpansionBuffer(name, lists.get(0)));
    }

    // Disable the macro so it can't be recursively expanded.
    macroTable.disable(name);
  }

  /**
   * Stringify a macro argument.  Because of conditionals, there may a
   * different stringified argument by presence condition.  This
   * method hoists the conditional around stringification and returns
   * a list of string literals.
   *
   * @param arg The list of tokens of the macro argument.
   * @param global The current presence condition.  Used to trim
   * infeasible tokens
   * @return The list of string literals.
   */
  private List<Syntax> stringifyArg(List<Syntax> arg,
                                    PresenceCondition global) {
    if (null == arg) {
      // An empty argument just becomes "".
      List<Syntax> list = new LinkedList<Syntax>();
      list.add(tokenCreator.createStringLiteral(""));

      if (preprocessorStatistics) {
        System.err.format("stringify %s %s %d\n",
                          "token", getNestedLocation(), 1);
      }
      
      return list;
      
    } else {
      // Check whether we need to hoist a conditional around the
      // stringification.  Hoisting is necessary when the argument
      // contains conditionals.
      boolean hoist = false;
      for (Syntax s : arg) {
        if (s.kind() == Kind.CONDITIONAL_BLOCK) {
          hoist = true;
          break;
        }
      }

      if (hoist) {
        // Hoist conditionals around stringification.
        List<StringBuilder> strings = new LinkedList<StringBuilder>();
        strings.add(new StringBuilder());

        List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();
        presenceConditions.add(global);
        global.addRef();

        stringifyHoist(arg, strings, presenceConditions, global);

        Location location = null;
        if (arg.size() > 0) location = arg.get(0).getLocation();

        // Generate the conditional containing the stringified tokens.
        List<Syntax> list = new LinkedList<Syntax>();
        for (int i = 0; i < strings.size(); i++) {
          if (! presenceConditions.get(i).isFalse()) {
            String str = escapeString(strings.get(i).toString());

            // Wrap each string individually.  This allows lazy
            // forking to minimize the number of subparsers.
            list.add(new Conditional(ConditionalTag.START,
                                     presenceConditions.get(i),
                                     location));
            list.add(tokenCreator.createStringLiteral(str));
            list.add(new Conditional(ConditionalTag.END,
                                     null,
                                     location));
          }
          else {
            presenceConditions.get(i).delRef();
          }
        }

        if (preprocessorStatistics) {
          System.err.format("stringify %s %s %d\n",
                            "conditional", getNestedLocation(),
                            strings.size());
        }

        return list;
        
      } else {
        // Stringify the argument.  No hoisting required.
        
        StringBuilder sb = new StringBuilder();
        for (Syntax s : arg) {
          if (s.kind() == Kind.LANGUAGE) {
            if (s.testFlag(PREV_WHITE)) {
              sb.append(' ');
            } 
            sb.append(s.getTokenText());
          } else if (s.kind() == Kind.LAYOUT
                     && s.getTokenText().length() > 0) {
            sb.append(' ');
          }

        }
        
        String str = escapeString(sb.toString());
        
        Language<?> stringified = tokenCreator.createStringLiteral(str);
        
        List<Syntax> list = new LinkedList<Syntax>();
        list.add(stringified);
        
        if (preprocessorStatistics) {
          System.err.format("stringify %s %s %d\n",
                            "token", getNestedLocation(), 1);
        }

        return list;
      }
    }
  }
  
  /**
   * Take a list of tokens and conditionals and group the conditionals
   * together into a structured conditional block object.
   *
   * @param list The tokens to build the conditional blocks from.
   * @param global The current presence condition, used to trim
   * infeasible conditional branches.
   */
  private List<Syntax> buildBlocks(List<Syntax> list,
                                   PresenceCondition global) {

    List<Syntax> newList = new LinkedList<Syntax>();
    PlainTokenBuffer tpresenceCondition = new PlainTokenBuffer(list);
    
    Syntax syntax = tpresenceCondition.next();
    boolean hasConditional = false;
    while (null != syntax) {
      if (syntax.kind() == Kind.CONDITIONAL) {
        newList.add(buildBlock(syntax.toConditional(), tpresenceCondition,
                               global));
        hasConditional = true;
      }
      else {
        newList.add(syntax);
      }
      
      syntax = tpresenceCondition.next();
    }

    if (hasConditional && newList.size() > 1) {
      // If conditional blocks were created and there are several
      // tokens in the list, wrap them in a single block.  This is for
      // arguments to stringification and token-pasting that should
      // have a single token for each operand, not a list.

      return wrapBlock(newList);
    } else {
      return newList;
    }
  }
  
  /**
   * Build one conditional block out of a list of tokens.
   *
   * @param start The starting "if" compound token of the conditional.
   * @param streamin The remaining tokens of the conditional.
   * @param global The current presence conditional used to trim
   * infeasible conditional branches.
   * @return The conditional block or EMPTY if it has no feasible
   * branches.
   */
  private Syntax buildBlock(Conditional start, Iterator<Syntax> streamin,
                            PresenceCondition global) {
    List<List<Syntax>> branches = new LinkedList<List<Syntax>>();
    List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();

    List<Syntax> branch = new LinkedList<Syntax>();
    branches.add(branch);
    
    presenceConditions.add(start.presenceCondition);
    start.presenceCondition.addRef();
    
    Syntax syntax = streamin.next();
    while (null != syntax) {
      
      if (syntax.kind() == Kind.CONDITIONAL
          && syntax.toConditional().tag() == ConditionalTag.START) {
        branch.add(buildBlock(syntax.toConditional(),
                              streamin, global));
      }
      else if (syntax.kind() == Kind.CONDITIONAL
               && syntax.toConditional().tag() == ConditionalTag.NEXT) {
        branch = new LinkedList<Syntax>();
        branches.add(branch);
        presenceConditions.add(syntax.toConditional().presenceCondition);
        syntax.toConditional().presenceCondition.addRef();
      }
      else if (syntax.kind() == Kind.CONDITIONAL
               && syntax.toConditional().tag() == ConditionalTag.END) {
        break;
      }
      else {
        branch.add(syntax);
      }
      
      syntax = streamin.next();
    }
    
    // Trim infeasible branches.
    for (int i = 0; i < branches.size(); i++) {
      List<Syntax> list = branches.get(i);
      PresenceCondition local = global.and(presenceConditions.get(i));
      
      if (local.isFalse()) {
        branches.remove(i);
        presenceConditions.remove(i);
      }
      
      local.delRef();
    }

    if (branches.size() == 0) {
      // The block has no feasible branches.
      return EMPTY;
    } else {
      // Add an explicit branch for the implicit else to the block if
      // necessary.
      PresenceCondition union = presenceConditions.get(0);
      union.addRef();
    
      for (int i = 1; i < presenceConditions.size(); i++) {
        PresenceCondition tmp = union.or(presenceConditions.get(i));
        union.delRef();
        union = tmp;
      }
    
      PresenceCondition notUnion = union.not();
      union.delRef();
    
      PresenceCondition implicitElse = global.and(notUnion);
      notUnion.delRef();

      if (! implicitElse.isFalse()) {
        presenceConditions.add(implicitElse);
        branches.add(new LinkedList<Syntax>());
      } else {
        implicitElse.delRef();
      }


      // Create and return a new instance of a block.
      ConditionalBlock block = new ConditionalBlock(branches,
                                                    presenceConditions,
                                                    location);
      // Copy the flags from the old block to the new.
      for (int i = 0; i < Syntax.MAX_FLAGS; i++) {
        if (start.testFlag(i)) {
          block.setFlag(i);
        }
      }
    
      return block;
    }
  }

  /**
   * Wrap a list of tokens in a single conditional block.  The
   * resulting block will have one branch containing the list of
   * tokens and will have a presence condition of TRUE.  This is to
   * create a single token out of several for hoisting token-pasting
   * and stringification around conditionals.
   *
   * @param tokens The list of tokens to wrap.
   * @return A list containing the conditional block with one
   * branch.
   */
  private List<Syntax> wrapBlock(List<Syntax> tokens) {
    List<List<Syntax>> branches
      = new LinkedList<List<Syntax>>();
    List<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();

    branches.add(tokens);
    presenceConditions.add(presenceConditionManager.new PresenceCondition(true));

    List<Syntax> list = new LinkedList<Syntax>();

    Location location = null;
    if (tokens.size() > 0) location = tokens.get(0).getLocation();

    list.add(new ConditionalBlock(branches,
                                  presenceConditions,
                                  location));

    return list;
  }
  
  /**
   * Escape quotes in the string and add quotes.
   *
   * @param str The string to escape.
   * @return The escaped string.
   */
  private static String escapeString(String str) {
    str = str.replace("\\", "\\\\");
    str = str.replace("\"", "\\\"");
    str = "\"" + str + "\"";
    
    return str;
  }
  
  /**
   * Hoist stringification around all conditionals in a list of
   * tokens.  This completes the conditionals by taking all
   * combinations of their branches, resulting in multiplicative
   * explosion in the number of strings.
   *
   * @param list The list of tokens containing conditionals to hoist.
   * @param strings The stringified strings.
   * @param presenceConditions The presence conditions of the hoisted
   * conditionals around each string.
   */
  private static void stringifyHoist(List<Syntax> list,
                                     List<StringBuilder> strings,
                                     List<PresenceCondition> presenceConditions,
                                     PresenceCondition global) {
    for (Syntax s : list) {
      if (s.kind() == Kind.LANGUAGE) {
        for (StringBuilder sb : strings) {
          if (s.testFlag(PREV_WHITE)) {
            sb.append(' ');
          }
          sb.append(s.getTokenText());
        }

      } else if (s.kind() == Kind.LAYOUT) {
        if (s.getTokenText().length() > 0) {
          for (StringBuilder sb : strings) {
            if (sb.charAt(sb.length() - 1) != ' ') {
              sb.append(' ');
            }
          }
        }

      } else if (s.kind() == Kind.CONDITIONAL_BLOCK) {
        ConditionalBlock block = (ConditionalBlock) s;
        List<StringBuilder> newStrings = new LinkedList<StringBuilder>();
        List<PresenceCondition> newPresenceConditions = new LinkedList<PresenceCondition>();

        for (int i = 0; i < block.presenceConditions.size(); i++) {
          List<Syntax> branch = block.branches.get(i);
          PresenceCondition presenceCondition = block.presenceConditions.get(i);

          List<StringBuilder> branchStrings = new LinkedList<StringBuilder>();
          List<PresenceCondition> branchPresenceConditions = new LinkedList<PresenceCondition>();
          branchStrings.add(new StringBuilder());
          branchPresenceConditions.add(presenceCondition);
          presenceCondition.addRef();
          
          stringifyHoist(branch, branchStrings, branchPresenceConditions, global);
          
          // Combine strings and presenceConditions with newStrings and newPresenceConditions.
          for (int a = 0; a < strings.size(); a++) {
            for (int b = 0; b < branchStrings.size(); b++) {
              PresenceCondition tmp = presenceConditions.get(a).and(branchPresenceConditions.get(b));
              PresenceCondition newPresenceCondition = global.and(tmp);
              tmp.delRef();

              if (newPresenceCondition.isFalse()) {
                newPresenceCondition.delRef();
              } else {
                StringBuilder sb = new StringBuilder();
                sb.append(strings.get(a));
                sb.append(branchStrings.get(b));
                newStrings.add(sb);
                newPresenceConditions.add(newPresenceCondition);
              }
            }
          }
          
          for (PresenceCondition c : branchPresenceConditions) {
            c.delRef();
          }
        }
        
        strings.clear();
        strings.addAll(newStrings);

        for (PresenceCondition c : presenceConditions) {
          c.delRef();
        }
        presenceConditions.clear();
        presenceConditions.addAll(newPresenceConditions);
      }
    }
  }
  
  /**
   * Expand an argument by pushing a token presenceCondition and using
   * Preprocessor.
   *
   * @param arg The argument to expand.  This method assumes that arg
   * is not null, which means the argument is empty.
   * @return The expanded argument.
   */
  private List<Syntax> expandArg(List<Syntax> arg) {

    // Add an end-of-expansion marker to the list.
    List<Syntax> argEOE = new LinkedList<Syntax>();
    argEOE.addAll(arg);
    Layout eoe = new Layout("");
    eoe.setFlag(EOE);
    argEOE.add(eoe);

    // Push a new token buffer for the preprocessor to preprocess the
    // argument.
    stackOfBuffers.push(new PlainTokenBuffer(argEOE, true));

    // Track whether the expansion contains conditionals, so we can
    // trim infeasible branches.
    boolean hasConditional = false;

    // Preprocess the argument.
    List<Syntax> expanded = new LinkedList<Syntax>();
    boolean done = false;
    while (true) {
      Syntax syntax = next();

      syntax.clearFlag(NON_FUNCTION);

      if (syntax.testFlag(EOE)) {
        break;
      }

      switch (syntax.kind()) {
      case CONDITIONAL:
        hasConditional = true;
        break;

      case EOF:
        // Error location 31
        String message = "real EOF in argument expansion";

        if (showErrors) {
          error(message);
        }

        done = true;
        break;
      }

      if (done) break;

      expanded.add(syntax);
    }

    stackOfBuffers.pop();

    return expanded;
  }
  
  //process different directives, i.e. definitions
  //update conditional presenceCondition
  //expand macros in program text and in conditional expressions
  //parse function-like macros
  //complete function-like macros
  
  /**
   * Find the current macro invocation nesting depth.  This is used
   * for statistics collection.  The stack of token buffers is
   * searched for macro invocations each is counted.
   *
   * @return The macro invocation nesting depth.
   */
  private int getMacroNestingDepth() {
    if (stackOfBuffers.size() == 0) return 0;

    int count = 0;

    for (TokenBuffer t : stackOfBuffers) {
      if (t.hasMacroName()) {
        count++;
      }
    }

    return count;
  }

  /**
   * Get a special location string that also indicates what macro, if
   * any, is currently being expanded.
   *
   * @return The location string including nested macro.
   */
  private String getNestedLocation() {
    // The current location string.
    String location = fileManager.include.getLocation().toString();

    // Find the macro that is being expanded if there is any.
    String macro = null;

    // This assumes, as the Java documentation verifies, that the top
    // of the stack is at the front of the list.  See
    // download.oracle.com/javase/6/docs/api/java/util/LinkedList.html#pop%28%29

    for (TokenBuffer t : stackOfBuffers) {
      if (t.hasMacroName()) {
        macro = t.getMacroName();
        break;
      }
    }

    if (null == macro) {
      return location;
    } else {
      return String.format("%s:%s", location, macro);
    }
  }
  
  /**
   * A token buffer.  This buffer is used to support nested macro
   * expansion.  It is also used when the preprocessor needs to emit
   * more than one token at a time, e.g. after a failed token-pasting.
   */
  private static abstract class TokenBuffer implements Iterator<Syntax> {
    /**
     * Whether or not this buffer holds a macro expansion.
     *
     * @return true is this buffer is a macro expansion.
     */
    public boolean hasMacroName() {
      return false;
    }

    /**
     * Return the name of the macro that this buffer holds the
     * expansion of.
     *
     * @return The name of the macro.
     * @throws UnsupportedOperationException if hasMacroName() is false.
     */
    public String getMacroName() {
      throw new UnsupportedOperationException();
    }

    /**
     * Whether or not this buffer holds a macro argument expansion.
     *
     * @return true if it holds a macro argument expansion.
     */
    public boolean isMacroArgument() {
      return false;
    }
  }
  
  /**
   * A plain token buffer.  This buffer is used when the preprocessor
   * needs to oput more than one token at a time, e.g. after a failed
   * token-paste.
   */
  private static class PlainTokenBuffer extends TokenBuffer {
    /** An iterator over the buffer's tokens. */
    private Iterator<Syntax> iterator;

    /** Whether it's expanding a macro argument. */
    private boolean isMacroArgument;
    
    /**
     * Create a new buffer from a list of tokens.
     *
     * @param list A list of tokens.
     */
    public PlainTokenBuffer(List<Syntax> list, boolean isMacroArgument) {
      if (null != list) {
        this.iterator = list.iterator();
      } else {
        this.iterator = null;
      }
      this.isMacroArgument = isMacroArgument;
    }

    /**
     * Create a new buffer from a list of tokens.
     *
     * @param list A list of tokens.
     */
    public PlainTokenBuffer(List<Syntax> list) {
      this(list, false);
    }

    public Syntax next() {
      if (null == iterator) {
        return null;
      }
      
      if (iterator.hasNext()) {
        return iterator.next();
      } else {
        return null;
      }
    }
    
    public boolean hasNext() {
      return iterator.hasNext();
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return false;
    }

    public String getMacroName() {
      throw new UnsupportedOperationException();
    }

    public boolean isMacroArgument() {
      return isMacroArgument;
    }
  }

  /** A token buffer containing three tokens that avoids using a list. */
  private static class ThreeTokenBuffer extends TokenBuffer {
    /** The first token. */
    private Syntax a;

    /** The second token. */
    private Syntax b;

    /** The third token. */
    private Syntax c;

    /** The count of tokens emitted. */
    private int count;

    /**
     * Create a new token buffer of just two tokens.
     *
     * @param The first token.
     * @param The second token.
     * @param The third token.
     */
    public ThreeTokenBuffer(Syntax a, Syntax b, Syntax c) {
      this.a = a;
      this.b = b;
      this.c = c;
      count = 0;
    }

    public Syntax next() {
      switch (count) {
      case 0:
        count++;
        return a;

      case 1:
        count++;
        return b;

      case 2:
        count++;
        return c;

      case 3:
        // Fall through
      default:
        return null;
      }
    }
    
    public boolean hasNext() {
      return count < 3;
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return false;
    }

    public String getMacroName() {
      throw new UnsupportedOperationException();
    }
  }

  /** A token buffer containing two tokens that avoids using a list. */
  private static class TwoTokenBuffer extends TokenBuffer {
    /** The first token. */
    private Syntax a;

    /** The second token. */
    private Syntax b;

    /** The count of tokens emitted. */
    private int count;

    /**
     * Create a new token buffer of just two tokens.
     *
     * @param A first token.
     * @param The second token.
     */
    public TwoTokenBuffer(Syntax a, Syntax b) {
      this.a = a;
      this.b = b;
      count = 0;
    }

    public Syntax next() {
      switch (count) {
      case 0:
        count++;
        return a;

      case 1:
        count++;
        return b;

      case 2:
        // Fall through
      default:
        return null;
      }
    }
    
    public boolean hasNext() {
      return count < 2;
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return false;
    }

    public String getMacroName() {
      throw new UnsupportedOperationException();
    }
  }

  /** A token buffer containing one token that avoids using a list. */
  private static class OneTokenBuffer extends TokenBuffer {
    /** The token. */
    private Syntax a;

    /** Whether the token has been emitted or not. */
    private boolean done;

    /**
     * Create a new token buffer of just two tokens.
     *
     * @param A first token.
     * @param The second token.
     */
    public OneTokenBuffer(Syntax a) {
      this.a = a;
      this.done = false;
    }

    public Syntax next() {
      if (! done) {
        done = true;
        return a;
      } else {
        return null;
      }
    }
    
    public boolean hasNext() {
      return !done;
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return false;
    }

    public String getMacroName() {
      throw new UnsupportedOperationException();
    }
  }

  /** A token buffer for a singly-defined macro expansion. */
  private static class SingleExpansionBuffer extends TokenBuffer {
    /** The name of the macro being expanded. */
    private String name;

    /** An iterator over the list of tokens in the macro expansion. */
    private Iterator<Syntax> iterator;

    /**
     * Create a token buffer for the macro expansion.
     *
     * @param name The name of the macro being expanded.
     * @param expansion The tokens of the macro expansion.
     */
    public SingleExpansionBuffer(String name, List<Syntax> expansion) {
      this.name = name;

      if (null == expansion) {
        this.iterator = null;
      } else {
        this.iterator = expansion.iterator();
      }
    }
    
    public Syntax next() {
      if (null == iterator) {
        return null;
      }
      
      if (iterator.hasNext()) {
        return iterator.next();

      } else {
        return null;
      }
    }
    
    public boolean hasNext() {
      return iterator != null && iterator.hasNext();
    }

    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return true;
    }

    public String getMacroName() {
      return name;
    }
  }
  
  /**
   * A token buffer for a multiply-defined macro expansion.
   */
  private static class MultipleExpansionBuffer extends TokenBuffer {
    
    /** The name of the macro being expanded. */
    private String name;

    /** The set of expansions. */
    private List<List<Syntax>> lists;
    
    /** The presence conditions of the expansions. */
    private List<PresenceCondition> presenceConditions;
    
    /** The current expansion. */
    private int list;
    
    /** The position within an expansion. */
    private int i;

    /** The location of this expansion. */
    private Location location;

    /**
     * Create a new MultipleExpansionBuffer.
     *
     * @param name The name of the macro being expanded.
     * @param lists The expansions of the macro.
     * @param presenceConditions The presence conditions of the expansions.
     * @param location The location of the expanded token.
     */
    public MultipleExpansionBuffer(String name,
                                   List<List<Syntax>> lists,
                                   List<PresenceCondition> presenceConditions,
                                   Location location) {
      this.name = name;
      this.lists = lists;
      this.presenceConditions = presenceConditions;
      this.list = -1;
      this.i = 0;
      this.location = location;
    }

    public Syntax next() {
      if (-1 == list) {
        list = 0;
        i = 0;
        presenceConditions.get(list).addRef();

        return new Conditional(ConditionalTag.START,
                               presenceConditions.get(list),
                               location);

      } else if (list < lists.size()) {
        if (null != lists.get(list) && i < lists.get(list).size()) {
          return lists.get(list).get(i++);

        } else {
          list++;
          i = 0;
          if (list < lists.size()) {
            presenceConditions.get(list).addRef();
            
            return new Conditional(ConditionalTag.NEXT,
                                   presenceConditions.get(list),
                                   location);

          } else {
            return new Conditional(ConditionalTag.END,
                                   null,
                                   location);
          }
        }

      } else {
        freePresenceCondition();

        return null;
      }
    }

    public boolean hasNext() {
      return list < lists.size();
    }
    
    public void remove() {
      throw new UnsupportedOperationException();
    }

    public boolean hasMacroName() {
      return true;
    }

    public String getMacroName() {
      return name;
    }

    /**
     * Free the presence condition data structures.
     */
    private void freePresenceCondition() {
      for (PresenceCondition presenceCondition : presenceConditions) {
        presenceCondition.delRef();
      }
    }
  }

  /**
   * This method determines whether we are on a system that uses the
   * Apple build of gcc, because there is (at least one) minor
   * difference in this version.
   *
   * @return true if the system uses the Apple build of gcc.
   */
  private static boolean isAppleGCC() {
    return xtc.Limits.COMPILER_VERSION.indexOf("Apple") >= 0;
  }

  /**
   * Handle an error.
   *
   * @param msg The error message.
   */
  private void error(String msg) {
    System.err.println("error: " + msg);
  }

  /**
   * Handle a warning.
   *
   * @param msg The warning message.
   */
  private void warning(String msg) {
    System.err.println("warning: " + msg);
  }

  public void remove() {
    throw new UnsupportedOperationException();
  }

  /**
   * Find in a stack of token buffers the name of the macro being
   * expanded if any.
   *
   * @param stack The stack of buffers to inspect.
   * @param depth The maximum depth into the stack to inspect.
   * @return The containing macro or null if none.
   */
  private String getContainingMacro(LinkedList<TokenBuffer> stack, int depth) {
    String macroName = null;

    // push adds to the front of a linked-list in java.
    for (int i = 0; i < stack.size() - depth; i++) {
      if (stack.get(i).hasMacroName()) {
        macroName = stack.get(i).getMacroName();
        break;
      }
    }

    return macroName;
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
