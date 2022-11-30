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

import java.lang.Iterable;

import java.util.List;
import java.util.Iterator;
import java.util.Set;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.C;
import xtc.type.Type;

import superc.core.PresenceConditionManager.PresenceCondition;
import superc.core.MacroTable.Macro;
import superc.core.MacroTable.Entry;
import superc.core.Syntax.Kind;

import net.sf.javabdd.BDD;
import net.sf.javabdd.BDDFactory;

import com.microsoft.z3.BoolExpr;
import com.microsoft.z3.Context;
import com.microsoft.z3.Expr;

/**
 * Generate a BDD from a preprocessor conditional expression.
 *
 * @author Paul Gazzillo
 */
public class ConditionEvaluatorZ3 extends ConditionEvaluator {
  /** Manages presence conditions. */
  protected PresenceConditionManagerZ3 presenceConditionManager;

  /** An optional macro table used for the defined operator.  */
  private MacroTable macroTable;

  /** The expression parser. */
  private ExpressionParser parser;
  
  /** The BDD factory. */
  private BDDFactory B;
  
  /** The z3 context. */
  private Context ctx;
  
  /** The common type operations for C. */
  private final C cops;

  /**
   * True when the evaluator is constructing a string version of a
   * subexpression.  This is necessary to represent non-boolean
   * subexpression as variables in a boolean function.
   */
  private boolean dostring = false;

  /** Flag for non-boolean subexpressions. */
  private boolean nonboolean = false;

  /** Setting that pulls all undefined macros to false and empty. */
  private boolean pullUndefinedFalse = false;

  /** An optional set of free configs seen. */
  private Set<String> seenConfigs = null;

  /** Restrict free macros to the given prefix. */
  private boolean enableRestrictPrefix = false;

  /** The prefix to restrict free macros to. */
  private String restrictPrefix = null;

  /** Use the z3 backend in addition to bdds. */
  private boolean z3Backend = false;
  

  /**
   * Set the pullUndefinedFalse flag.
   *
   * @param b The new setting.
   */
  public void setPullUndefinedFalse(boolean b) {
    this.pullUndefinedFalse = b;
  }

  /**
   * Save free configs to the given list.
   *
   * @param seenConfigs The set of free configs.
   */
  public void setSeenConfigs(Set<String> seenConfigs) {
    this.seenConfigs = seenConfigs;
  }

  /** Stop saving free configs. */
  public void unsetSeenConfigs() {
    this.seenConfigs = null;
  }

  /** 
   * Restrict free macros to the given prefix.
   *
   * @param The prefix to restrict or null for no restriction.
   */
  public void restrictPrefix(String prefix) {
    if (null == prefix) {
      enableRestrictPrefix = false;
      this.restrictPrefix = null;
    } else {
      enableRestrictPrefix = true;
      this.restrictPrefix = prefix;
    }
  }

  /**
   * Get the current macro prefix restriction.
   *
   * @return The macro prefix restriction or null if none.
   */
  public String getRestrictPrefix() {
    return restrictPrefix;
  }

  /**
   * Use the z3 backend in addition to bdds.
   */
  public void z3Backend(boolean value) {
    z3Backend = value;
  }

  /**
   * Create a new condition evaluator.
   *
   * @param presenceConditionManager Manages presence conditions.
   * @param macroTable The macro table.
   */  
  public ConditionEvaluatorZ3(ExpressionParser parser,
                              PresenceConditionManagerZ3 presenceConditionManager,
                              MacroTable macroTable) {
    super(parser, presenceConditionManager, macroTable);
    this.presenceConditionManager = presenceConditionManager;
    this.macroTable = macroTable;
    this.parser = parser;

    this.B = presenceConditionManager.getBDDFactory();
    this.ctx = presenceConditionManager.getZ3Context();
    this.cops = new C();
  }

  /**
   * Create a new condition evaluator without macro resolution.
   *
   * @param presenceConditionManager Manages presence conditions.
   */
  public ConditionEvaluatorZ3(ExpressionParser parser,
                              PresenceConditionManagerZ3 presenceConditionManager) {
    this(parser, presenceConditionManager, null);
  }

  /**
   * Evaluate a conditional expression.
   *
   * @param expression An expression iterator.
   * @return A presence condition.
   */
  public PresenceCondition evaluate(Iterator<Syntax> expression) {
    Node tree = parser.parse(expression);
    BDD bdd = evaluate(tree);
    PresenceCondition pc;
    BoolExpr expr = evaluatez3(tree);
    pc = ((PresenceConditionManagerZ3) presenceConditionManager).newCondition(bdd, tree, expr);
    ((PresenceConditionManagerZ3.PresenceConditionZ3) pc).simplify();
    return pc;
  }

  // /**
  //  * Evaluate a conditional expression.
  //  *
  //  * @param expression An expression iterator.
  //  * @return A presence condition.
  //  */
  // public PresenceCondition evaluate(Iterator<Syntax> expression) {
  //   Node tree = parser.parse(expression);
  //   BDD bdd = evaluate(tree);
  //   BoolExpr expr = evaluatez3(tree);
  //   PresenceCondition pc = presenceConditionManager.newCondition(bdd, tree, expr);
  //   pc.simplify();
  //   return pc;
  // }

  /**
   * Evaluate a conditional expression's AST and return a z3 boolean
   * expression.
   *
   * @param ast An AST of an expression.
   * @return A z3 BoolExpr
   */
  public BoolExpr evaluatez3(Node ast) {
    nonboolean = false;
    dostring = false;
    if (null == ast) {
      return ctx.mkFalse();
    } else {
      // ApplyResult ar = applyTactic(ctx, ctx.mkTactic("simplify"), goal);
      // TODO: z3 simplify
      return ensureBoolExpr(z3visitor.dispatch(ast));
    }
  }

  /**
   * Return true if the expression had a non-boolean subexpression.
   *
   * @return true if there was a non-boolean subexpression.
   */
  public boolean sawNonboolean() {
    return nonboolean;
  }


  /** Takes whatever the evaluation returns, string, boolean, or integer, and
    * creates a BoolExpr out of it if isn't already.
    */
  public BoolExpr ensureBoolExpr(Object o) {
    if (o instanceof BoolExpr) {
      return (BoolExpr) o;
    }
    else if (o instanceof Long) {
      if (((Long) o).equals(new Long(0))) {
        return ctx.mkFalse();
      }
      else {
        return ctx.mkTrue();
      }
    }
    else if (o instanceof String) {
      String s = parens(o);

      // ensure the predicate is in the variable manager
      presenceConditionManager.getVariableManager().getVariable(s);

      return ctx.mkBoolConst(s);
    }
    else if (o instanceof Boolean) {
      Boolean b = (Boolean) o;
      
      if (b) {
        return ctx.mkTrue();
      }
      else {
        return ctx.mkFalse();
      }
    }
    else {
      System.err.println("FATAL: ensureBoolExpr, unforeseen type from evaluator");
      System.err.println(o);
      System.err.println(o.getClass());
      System.exit(-1);
      
      return null;
    }
  }

  // a version of the visitor that just uses z3 for boolean operations
  private Visitor z3visitor = new Visitor() {
      /** Process an integer constant. */
      public Object visitIntegerConstant(GNode n) {
        xtc.type.Type result;
    
        result = cops.typeInteger(n.getString(0));

        return result.getConstant().bigIntValue().longValue();
      }

      /** Process a character constant. */
      public Object visitCharacterConstant(GNode n) {
        xtc.type.Type result;
    
        result = cops.typeCharacter(n.getString(0));
    
        return result.getConstant().bigIntValue().longValue();
      }

      /** Process primary identifier. */
      public Object visitPrimaryIdentifier(GNode n) {
        // if (enableRestrictPrefix && ! n.getString(0).startsWith(restrictPrefix)) {
        //   return "";
        // }
        // if (pullUndefinedFalse) {
        //   return "";
        // }
        String identifierName = n.getString(0);
        if (macroTable.getConfigurationVariables()) {
          macroTable.configurationVariables.add(identifierName);
        }
        if (null != seenConfigs) {
          seenConfigs.add(identifierName);
        }
        return identifierName;
      }

      /** Process a unary minus. */
      public Object visitUnaryMinusExpression(GNode n) {
        Object a;

        nonboolean = true;
    
        dostring = true;
    
        a = dispatch(n.getGeneric(0));
    
        dostring = false;
    
        if (a instanceof Long) {
          return - (Long) a;
        }
        else {
          return "- " + parens(a);
        }
      }

      /** Process a unary plus. */
      public Object visitUnaryPlusExpression(GNode n) {
        nonboolean = true;

        return dispatch(n.getGeneric(0));
      }

      /** Process a logical negation. */
      public Object visitLogicalNegationExpression(GNode n) {
        if (dostring) {
          Object a = dispatch(n.getGeneric(0));
      
          if (a instanceof Long) {
            return "" + ((((Long) a).equals(new Long(0))) ? 1 : 0);
          }
          else {
            return "! " + parens(a);
          }
        }
        else {
          BoolExpr a = ensureBoolExpr(dispatch(n.getGeneric(0)));
          return ctx.mkNot(a);
        }
      }

      /** Process a bitwise negation. */
      public Object visitBitwiseNegationExpression(GNode n) {
        Object a, result;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
            
        dostring = false;
    
        if (a instanceof Long) {
          result = ~ (Long) a;
        }
        else {
          return "~ " + parens(a);
        }
    
        return result;
      }

      /** Process a multiplicative operation. */
      public Object visitMultiplicativeExpression(GNode n) {
        Object a, b, result;
        String op;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(2));
        op = n.getString(1);
    
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          if ((op.equals("/")
               || op.equals("%")) && ((Long) b).equals(new Long(0))) {
            System.err.println("division by zero in #if");
            result = new Long(0);
          }
          if (op.equals("*")) {
            result = (Long) a * (Long) b;
          }
          else if (op.equals("/")) {
            result = (Long) a / (Long) b;
          }
          else if (op.equals("%")) {
            result = (Long) a % (Long) b;
          }
          else {
            result = "";
          }
        }
        else {
          result = parens(a) + " " + op + " " + parens(b);
        }
    
        return result;
      }

      /** Process an additive operation. */
      public Object visitAdditiveExpression(GNode n) {
        Object a, b, result;
        String op;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(2));
        op = n.getString(1);
    
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          if (op.equals("+")) {
            result = (Long) a + (Long) b;
          }
          else if (op.equals("-")) {
            result = (Long) a - (Long) b;
          }
          else {
            result = "";
          }
        }
        else {
          result = parens(a) + " " + op + " " + parens(b);
        }
    
        return result;
      }

      /** Process a shift expression. */
      public Object visitShiftExpression(GNode n) {
        Object a, b, result;
        String op;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(2));
        op = n.getString(1);
    
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          if (op.equals("<<")) {
            result = (Long) a << (Long) b;
          }
          else if (op.equals(">>")) {
            result = (Long) a >> (Long) b;
          }
          else {
            result = "";
          }
        }
        else {
          result = parens(a) + " " + op + " " + parens(b);
        }
    
        return result;
      }

      /** Process a relational expression. */
      public Object visitRelationalExpression(GNode n) {
        Object a, b, result;
        String op;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(2));
        op = n.getString(1);
    
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          Long x = (Long) a;
          Long y = (Long) b;
          long zero = 0;
          long one = 1;
      
          if (op.equals("<")) {
            result = x < y ? one : zero;
          }
          else if (op.equals("<=")) {
            result = x <= y ? one : zero;
          }
          else if (op.equals(">")) {
            result = x > y ? one : zero;
          }
          else if (op.equals(">=")) {
            result = x >= y ? one : zero;
          }
          else {
            result = "";
          }
        }
        else {
          result = parens(a) + " " + op + " " + parens(b);
        }
    
        return result;
      }

      /** Process a equality expression. */
      public Object visitEqualityExpression(GNode n) {
        Object a, b, result;
        String op;
        boolean mydostring = dostring;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(2));
        op = n.getString(1);
    
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          if (op.equals("==")) {
            result = ((Long) a).equals((Long) b);
          }
          else if (op.equals("!=")) {
            result = ! ((Long) a).equals((Long) b);
          }
          else {
            result = "";
          }
        }
        else {
          String sa, sb;
      
          if (a instanceof String) {
            sa = (String) a;
          }
          else if (a instanceof Long) {
            sa = ((Long) a).toString();
          }
          else {
            return null;
          }
      
          if (b instanceof String) {
            sb = (String) b;
          }
          else if (b instanceof Long) {
            sb = ((Long) b).toString();
          }
          else {
            return null;
          }
      
          if (op.equals("==") && sa.equals(sb)) {
            result = mydostring ? "1" : B.one();
          }
          else {
            result = parens(sa) + " " + op + " " + parens(sb);
          }
        }
    
        return result;
      }

      /** Process a bitwise and. */
      public Object visitBitwiseAndExpression(GNode n) {
        Object a, b, result;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(1));
            
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          result = (Long) a & (Long) b;
        }
        else {
          result = parens(a) + " & " + parens(b);
        }
    
        return result;
      }

      /** Process a bitwise xor. */
      public Object visitBitwiseXorExpression(GNode n) {
        Object a, b, result;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(1));
            
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          result = (Long) a ^ (Long) b;
        }
        else {
          result = parens(a) + " ^ " + parens(b);
        }
    
        return result;
      }

      /** Process a bitwise or. */
      public Object visitBitwiseOrExpression(GNode n) {
        Object a, b, result;
    
        nonboolean = true;

        dostring = true;
    
        a = dispatch(n.getGeneric(0));
        b = dispatch(n.getGeneric(1));
            
        dostring = false;
    
        if (a instanceof Long && b instanceof Long) {
          result = (Long) a | (Long) b;
        }
        else {
          result = parens(a) + " | " + parens(b);
        }
    
        return result;
      }

      /** Process a logical and. */
      public Object visitLogicalAndExpression(GNode n) {
        if (dostring) {
          Object a = dispatch(n.getGeneric(0));
          Object b = dispatch(n.getGeneric(1));
      
          if (a instanceof Long && b instanceof Long) {
            return (Long) a & (Long) b;
          }
          else {
            return parens(a) + " && " + parens(b);
          }
        }
        else {
          BoolExpr a, b;
      
          a = ensureBoolExpr(dispatch(n.getGeneric(0)));
          b = ensureBoolExpr(dispatch(n.getGeneric(1)));
          return ctx.mkAnd(a, b);
        }
      }

      /** Process a logical or. */
      public Object visitLogicalOrExpression(GNode n) {
        if (dostring) {
          Object a = dispatch(n.getGeneric(0));
          Object b = dispatch(n.getGeneric(1));
      
          if (a instanceof Long && b instanceof Long) {
            return (Long) a | (Long) b;
          }
          else {
            return parens(a) + " || " + parens(b);
          }
        }
        else {
          BoolExpr a, b;
      
          a = ensureBoolExpr(dispatch(n.getGeneric(0)));
          b = ensureBoolExpr(dispatch(n.getGeneric(1)));
          return ctx.mkOr(a, b);
        }
      }
  

      /** Make a new BoolExpr argument, "defined M".  If a macro table was supplied
       * to the evaluator, look for M there and evaluate the operation.
       */
      public Object visitDefinedExpression(GNode n) {
        String parameter = n.getGeneric(0).getString(0);

        //evaluate the defined operation, preserving configurations
        if (macroTable != null) {
          List<Entry> definitions = macroTable.get(parameter, presenceConditionManager);

          if (definitions != null && definitions.size() > 0) {
            boolean hasDefined, hasUndefined, hasFree;
        
            //three conditions
            //1) defined under all configurations, so output 1 (true)
            //2) undefined under all configurations, so output 0 (false)
            //3) partially defined, so output union of configurations
        
            hasDefined = false;
            hasUndefined = false;
            hasFree = false;
            for (Entry def : definitions) {
              if (def.macro.state == Macro.State.FREE) {
                hasFree = true;
              }
              else if (def.macro.state == Macro.State.DEFINED) {
                hasDefined = true;
              }
              else if (def.macro.state == Macro.State.UNDEFINED) {
                hasUndefined = true;
              }
            }
        
            if (hasDefined && ! hasUndefined && ! hasFree) {
              //fully defined in this presenceCondition
              return ctx.mkTrue();

            } else if (hasUndefined && ! hasDefined && ! hasFree) {
              //not defined in this presenceCondition
              return ctx.mkFalse();

            } else {
              if (null != seenConfigs) {
                seenConfigs.add(PresenceConditionManager.Variables.
                                createDefinedVariable(parameter));
                for (Entry def : definitions) {
                  if (def.macro.state == Macro.State.FREE) {
                    seenConfigs.addAll(def.presenceCondition.getAllConfigs());
                  }
                }
              }

              //partially defined in this presenceCondition
              BoolExpr defined = ctx.mkFalse();
              List<Token> tokenlist;
              int c;
          
              for (Entry def : definitions) {
                if (def.macro.state == Macro.State.FREE) {
                  // pull FREE to false also if pullUndefinedFalse is
                  // set
                  if (!pullUndefinedFalse) {
                    // ensure the variable manager has a record of this predicate
                    BDD varBoolExpr = presenceConditionManager.getVariableManager()
                      .getDefinedVariable(parameter);
                    varBoolExpr.free();

                    BoolExpr term = ctx.mkAnd(((PresenceConditionManagerZ3.PresenceConditionZ3) def.presenceCondition).z3(), ctx.mkBoolConst(parameter));
                    defined = ctx.mkOr(defined, term);
                  } else {
                    System.err.println("pullUndefinedFalse");
                  }

                } else if (def.macro.state == Macro.State.DEFINED) {
                  BoolExpr newDefined;

                  defined = ctx.mkOr(defined, ((PresenceConditionManagerZ3.PresenceConditionZ3) def.presenceCondition).z3());
                } else if (def.macro.state == Macro.State.UNDEFINED) {
                  //do nothing
                }
              }

              return defined;
            } //end partially defined

          } else {
            // The macro was used in a conditional expression before or
            // without being defined, therefore it is a configuration
            // variable.
            if (macroTable.getConfigurationVariables()) {
              macroTable.configurationVariables.add(parameter);
            }

            if (null != seenConfigs) {
              seenConfigs.add(PresenceConditionManager.Variables.
                              createDefinedVariable(parameter));
            }

            if (enableRestrictPrefix && ! parameter.startsWith(restrictPrefix)) {
              // System.err.println("restricting " + parameter + " to undefined");
              return ctx.mkFalse();
            }

            if (pullUndefinedFalse) {
              return ctx.mkFalse();
            }
          }
        } //end has macro table

        //if there are no macro table entries, just return the operation as is
        return "defined " + parameter;  //return a string
      }
  
      /** Process a conditional expression. */
      public Object visitConditionalExpression(GNode n) {
        if (dostring) {
          Object a = dispatch(n.getGeneric(0));
          Object b = dispatch(n.getGeneric(1));
          Object c = dispatch(n.getGeneric(2));
      
          if (a instanceof Long) {
            return (! ((Long) a).equals(new Long(0))) ? b : c;
          }
          else {
            return parens(a) + " ? " + parens(b) + " : " + parens(c);
          }
        }
        else {
          BoolExpr a = ensureBoolExpr(dispatch(n.getGeneric(0)));
          BoolExpr b = ensureBoolExpr(dispatch(n.getGeneric(1)));
          BoolExpr c = ensureBoolExpr(dispatch(n.getGeneric(2)));

          return ctx.mkITE(a, b, c);
        }
      }
    };
  
  // a version of the visitor that represents C integers in z3

  // implement by turning arithemetic expression into boolean ones
  // when they reach logical operators.  use C semantics, i.e.,
  // (if expr == 0 then false else true) and ...
  
  // private Visitor z3visitor = new Visitor() {
  //     /** Process an integer constant. */
  //     public Expr visitIntegerConstant(GNode n) {
  //       xtc.type.Type result;
    
  //       result = cops.typeInteger(n.getString(0));

  //       return ctx.mkInt(result.getConstant().bigIntValue().longValue());
  //     }

  //     /** Process a character constant. */
  //     public Expr visitCharacterConstant(GNode n) {
  //       xtc.type.Type result;
    
  //       result = cops.typeCharacter(n.getString(0));
    
  //       return ctx.mkInt(result.getConstant().bigIntValue().longValue());
  //     }

  //     /** Process primary identifier. */
  //     public Expr visitPrimaryIdentifier(GNode n) {
  //       // if (enableRestrictPrefix && ! n.getString(0).startsWith(restrictPrefix)) {
  //       //   return "";
  //       // }
  //       // if (pullUndefinedFalse) {
  //       //   return "";
  //       // }
  //       String identifierName = n.getString(0);
  //       if (macroTable.getConfigurationVariables()) {
  //         macroTable.configurationVariables.add(identifierName);
  //       }
  //       if (null != seenConfigs) {
  //         seenConfigs.add(identifierName);
  //       }
  //       return ctx.mkIntConst(identifierName);
  //     }

  //     /** Process a unary minus. */
  //     public Expr visitUnaryMinusExpression(GNode n) {
  //       nonboolean = true;
  //       return ctx.mkUnaryMinus(dispatch(n.getGeneric(0)));
  //     }

  //     /** Process a unary plus. */
  //     public Expr visitUnaryPlusExpression(GNode n) {
  //       nonboolean = true;
  //       return dispatch(n.getGeneric(0));
  //     }

  //     /** Process a logical negation. */
  //     public Expr visitLogicalNegationExpression(GNode n) {
  //       Expr a = dispatch(n.getGeneric(0));
        
  //     }

  //     /** Process a bitwise negation. */
  //     public Expr visitBitwiseNegationExpression(GNode n) {
  //       Expr a, result;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
            
  //       dostring = false;
    
  //       if (a instanceof Long) {
  //         result = ~ (Long) a;
  //       }
  //       else {
  //         return "~ " + parens(a);
  //       }
    
  //       return result;
  //     }

  //     /** Process a multiplicative operation. */
  //     public Expr visitMultiplicativeExpression(GNode n) {
  //       Expr a, b, result;
  //       String op;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(2));
  //       op = n.getString(1);
    
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         if ((op.equals("/")
  //              || op.equals("%")) && ((Long) b).equals(new Long(0))) {
  //           System.err.println("division by zero in #if");
  //           result = new Long(0);
  //         }
  //         if (op.equals("*")) {
  //           result = (Long) a * (Long) b;
  //         }
  //         else if (op.equals("/")) {
  //           result = (Long) a / (Long) b;
  //         }
  //         else if (op.equals("%")) {
  //           result = (Long) a % (Long) b;
  //         }
  //         else {
  //           result = "";
  //         }
  //       }
  //       else {
  //         result = parens(a) + " " + op + " " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process an additive operation. */
  //     public Expr visitAdditiveExpression(GNode n) {
  //       Expr a, b, result;
  //       String op;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(2));
  //       op = n.getString(1);
    
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         if (op.equals("+")) {
  //           result = (Long) a + (Long) b;
  //         }
  //         else if (op.equals("-")) {
  //           result = (Long) a - (Long) b;
  //         }
  //         else {
  //           result = "";
  //         }
  //       }
  //       else {
  //         result = parens(a) + " " + op + " " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a shift expression. */
  //     public Expr visitShiftExpression(GNode n) {
  //       Expr a, b, result;
  //       String op;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(2));
  //       op = n.getString(1);
    
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         if (op.equals("<<")) {
  //           result = (Long) a << (Long) b;
  //         }
  //         else if (op.equals(">>")) {
  //           result = (Long) a >> (Long) b;
  //         }
  //         else {
  //           result = "";
  //         }
  //       }
  //       else {
  //         result = parens(a) + " " + op + " " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a relational expression. */
  //     public Expr visitRelationalExpression(GNode n) {
  //       Expr a, b, result;
  //       String op;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(2));
  //       op = n.getString(1);
    
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         Long x = (Long) a;
  //         Long y = (Long) b;
  //         long zero = 0;
  //         long one = 1;
      
  //         if (op.equals("<")) {
  //           result = x < y ? one : zero;
  //         }
  //         else if (op.equals("<=")) {
  //           result = x <= y ? one : zero;
  //         }
  //         else if (op.equals(">")) {
  //           result = x > y ? one : zero;
  //         }
  //         else if (op.equals(">=")) {
  //           result = x >= y ? one : zero;
  //         }
  //         else {
  //           result = "";
  //         }
  //       }
  //       else {
  //         result = parens(a) + " " + op + " " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a equality expression. */
  //     public Expr visitEqualityExpression(GNode n) {
  //       Expr a, b, result;
  //       String op;
  //       boolean mydostring = dostring;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(2));
  //       op = n.getString(1);
    
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         if (op.equals("==")) {
  //           result = ((Long) a).equals((Long) b);
  //         }
  //         else if (op.equals("!=")) {
  //           result = ! ((Long) a).equals((Long) b);
  //         }
  //         else {
  //           result = "";
  //         }
  //       }
  //       else {
  //         String sa, sb;
      
  //         if (a instanceof String) {
  //           sa = (String) a;
  //         }
  //         else if (a instanceof Long) {
  //           sa = ((Long) a).toString();
  //         }
  //         else {
  //           return null;
  //         }
      
  //         if (b instanceof String) {
  //           sb = (String) b;
  //         }
  //         else if (b instanceof Long) {
  //           sb = ((Long) b).toString();
  //         }
  //         else {
  //           return null;
  //         }
      
  //         if (op.equals("==") && sa.equals(sb)) {
  //           result = mydostring ? "1" : B.one();
  //         }
  //         else {
  //           result = parens(sa) + " " + op + " " + parens(sb);
  //         }
  //       }
    
  //       return result;
  //     }

  //     /** Process a bitwise and. */
  //     public Expr visitBitwiseAndExpression(GNode n) {
  //       Expr a, b, result;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(1));
            
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         result = (Long) a & (Long) b;
  //       }
  //       else {
  //         result = parens(a) + " & " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a bitwise xor. */
  //     public Expr visitBitwiseXorExpression(GNode n) {
  //       Expr a, b, result;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(1));
            
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         result = (Long) a ^ (Long) b;
  //       }
  //       else {
  //         result = parens(a) + " ^ " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a bitwise or. */
  //     public Expr visitBitwiseOrExpression(GNode n) {
  //       Expr a, b, result;
    
  //       nonboolean = true;

  //       dostring = true;
    
  //       a = dispatch(n.getGeneric(0));
  //       b = dispatch(n.getGeneric(1));
            
  //       dostring = false;
    
  //       if (a instanceof Long && b instanceof Long) {
  //         result = (Long) a | (Long) b;
  //       }
  //       else {
  //         result = parens(a) + " | " + parens(b);
  //       }
    
  //       return result;
  //     }

  //     /** Process a logical and. */
  //     public Expr visitLogicalAndExpression(GNode n) {
  //       if (dostring) {
  //         Expr a = dispatch(n.getGeneric(0));
  //         Expr b = dispatch(n.getGeneric(1));
      
  //         if (a instanceof Long && b instanceof Long) {
  //           return (Long) a & (Long) b;
  //         }
  //         else {
  //           return parens(a) + " && " + parens(b);
  //         }
  //       }
  //       else {
  //         BDD a, b, bdd;
      
  //         a = ensureBDD(dispatch(n.getGeneric(0)));
  //         b = ensureBDD(dispatch(n.getGeneric(1)));
      
  //         bdd = a.andWith(b);
      
  //         return bdd;
  //       }
  //     }

  //     /** Process a logical or. */
  //     public Expr visitLogicalOrExpression(GNode n) {
  //       if (dostring) {
  //         Expr a = dispatch(n.getGeneric(0));
  //         Expr b = dispatch(n.getGeneric(1));
      
  //         if (a instanceof Long && b instanceof Long) {
  //           return (Long) a | (Long) b;
  //         }
  //         else {
  //           return parens(a) + " || " + parens(b);
  //         }
  //       }
  //       else {
  //         BDD a, b, bdd;
      
  //         a = ensureBDD(dispatch(n.getGeneric(0)));
  //         b = ensureBDD(dispatch(n.getGeneric(1)));
      
  //         bdd = a.orWith(b);
      
  //         return bdd;
  //       }
  //     }
  

  //     /** Make a new BDD argument, "defined M".  If a macro table was supplied
  //      * to the evaluator, look for M there and evaluate the operation.
  //      */
  //     public Expr visitDefinedExpression(GNode n) {
  //       String parameter = n.getGeneric(0).getString(0);

  //       //evaluate the defined operation, preserving configurations
  //       if (macroTable != null) {
  //         List<Entry> definitions = macroTable.get(parameter, presenceConditionManager);

  //         if (definitions != null && definitions.size() > 0) {
  //           boolean hasDefined, hasUndefined, hasFree;
        
  //           //three conditions
  //           //1) defined under all configurations, so output 1 (true)
  //           //2) undefined under all configurations, so output 0 (false)
  //           //3) partially defined, so output union of configurations
        
  //           hasDefined = false;
  //           hasUndefined = false;
  //           hasFree = false;
  //           for (Entry def : definitions) {
  //             if (def.macro.state == Macro.State.FREE) {
  //               hasFree = true;
  //             }
  //             else if (def.macro.state == Macro.State.DEFINED) {
  //               hasDefined = true;
  //             }
  //             else if (def.macro.state == Macro.State.UNDEFINED) {
  //               hasUndefined = true;
  //             }
  //           }
        
  //           if (hasDefined && ! hasUndefined && ! hasFree) {
  //             //fully defined in this presenceCondition
  //             return B.one(); //the constant true BDD

  //           } else if (hasUndefined && ! hasDefined && ! hasFree) {
  //             //not defined in this presenceCondition
  //             return B.zero(); //the constant false BDD

  //           } else {
  //             if (null != seenConfigs) {
  //               seenConfigs.add(PresenceConditionManager.Variables.
  //                               createDefinedVariable(parameter));
  //               for (Entry def : definitions) {
  //                 if (def.macro.state == Macro.State.FREE) {
  //                   seenConfigs.addAll(def.presenceCondition.getAllConfigs());
  //                 }
  //               }
  //             }

  //             //partially defined in this presenceCondition
  //             BDD defined = B.zero();
  //             List<Token> tokenlist;
  //             int c;
          
  //             for (Entry def : definitions) {
  //               if (def.macro.state == Macro.State.FREE) {
  //                 BDD newDefined;
  //                 BDD varBDD;
  //                 BDD term;

  //                 // pull FREE to false also if pullUndefinedFalse is
  //                 // set
  //                 if (!pullUndefinedFalse) {
  //                   varBDD = presenceConditionManager.getVariableManager()
  //                     .getDefinedVariable(parameter);

  //                   term = def.presenceCondition.getBDD().and(varBDD);
  //                   newDefined = defined.or(term);
  //                   term.free();
  //                   defined.free();
  //                   varBDD.free();
  //                   defined = newDefined;
  //                 } else {
  //                   System.err.println("pullUndefinedFalse");
  //                 }

  //               } else if (def.macro.state == Macro.State.DEFINED) {
  //                 BDD newDefined;
              
  //                 newDefined = defined.or(def.presenceCondition.getBDD());
  //                 defined.free();
  //                 defined = newDefined;
  //               } else if (def.macro.state == Macro.State.UNDEFINED) {
  //                 //do nothing
  //               }
  //             }

  //             return defined;
  //           } //end partially defined

  //         } else {
  //           // The macro was used in a conditional expression before or
  //           // without being defined, therefore it is a configuration
  //           // variable.
  //           if (macroTable.getConfigurationVariables()) {
  //             macroTable.configurationVariables.add(parameter);
  //           }

  //           if (null != seenConfigs) {
  //             seenConfigs.add(PresenceConditionManager.Variables.
  //                             createDefinedVariable(parameter));
  //           }

  //           if (enableRestrictPrefix && ! parameter.startsWith(restrictPrefix)) {
  //             // System.err.println("restricting " + parameter + " to undefined");
  //             return B.zero();
  //           }

  //           if (pullUndefinedFalse) {
  //             return B.zero();
  //           }
  //         }
  //       } //end has macro table

  //       //if there are no macro table entries, just return the operation as is
  //       return "defined " + parameter;  //return a string
  //     }
  
  //     /** Process a conditional expression. */
  //     public Expr visitConditionalExpression(GNode n) {
  //       if (dostring) {
  //         Expr a = dispatch(n.getGeneric(0));
  //         Expr b = dispatch(n.getGeneric(1));
  //         Expr c = dispatch(n.getGeneric(2));
      
  //         if (a instanceof Long) {
  //           return (! ((Long) a).equals(new Long(0))) ? b : c;
  //         }
  //         else {
  //           return parens(a) + " ? " + parens(b) + " : " + parens(c);
  //         }
  //       }
  //       else {
  //         BDD a = ensureBDD(dispatch(n.getGeneric(0)));
  //         BDD b = ensureBDD(dispatch(n.getGeneric(1)));
  //         BDD c = ensureBDD(dispatch(n.getGeneric(2)));
  //         BDD ab, na, nac, bdd;
      
  //         //implement with a & b | !a & c
  //         ab = a.and(b);
  //         b.free();
  //         na = a.not();
  //         a.free();
  //         nac = na.and(c);
  //         c.free();
  //         na.free();
  //         bdd = ab.or(nac);
  //         nac.free();
  //         ab.free();
      
  //         return bdd;
  //       }
  //     }
  //   };
}
