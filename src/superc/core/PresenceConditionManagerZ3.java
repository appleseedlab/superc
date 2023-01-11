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

import java.io.Writer;
import java.io.StringWriter;
import java.io.IOException;
import java.io.StringReader;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

import superc.core.Syntax.Kind;

import xtc.tree.Node;
import xtc.tree.GNode;

import net.sf.javabdd.BDDFactory;
import net.sf.javabdd.BDD;

import com.microsoft.z3.Context;
import com.microsoft.z3.Solver;
import com.microsoft.z3.BoolExpr;
import com.microsoft.z3.Tactic;
import com.microsoft.z3.Goal;
import com.microsoft.z3.ApplyResult;

/** Presence condition manager.  It abstracts away the nitty-gritty of
  * using BDDs.
  *
  * @author Paul Gazzillo
  * @version $Revision: 1.14 $
  */
public class PresenceConditionManagerZ3 extends PresenceConditionManager {

  /**
   * Create a new presence condition manager.
   */
  public PresenceConditionManagerZ3() {
    super();
  }

  /**
   * Copy a presence condition manager.
   *
   * @param The presence condition manager to copy.
   */
  public PresenceConditionManagerZ3(PresenceConditionManagerZ3 presenceConditionManager) {
    super(presenceConditionManager);
    this.ctx = presenceConditionManager.ctx;
    this.vars = presenceConditionManager.vars;
  }

  @Override
  public PresenceCondition newCondition(BDD bdd) {
    throw new UnsupportedOperationException("need more than bdd to create new presence condition for z3 version");
  }

  public PresenceCondition newCondition(BDD bdd, Node tree, BoolExpr expr) {
    return new PresenceConditionZ3(bdd, tree, expr);
  }

  @Override
  public PresenceCondition newTrue() {
    return new PresenceConditionZ3(true);
  }

  @Override
  public PresenceCondition newFalse() {
    return new PresenceConditionZ3(false);
  }

  @Override
  public PresenceCondition getVariable(String name) {
    // get variable gives a new bdd, which presence condition expects
    return new PresenceConditionZ3(getVariableManager().getVariable(name),
                                  GNode.create("PrimaryIdentifier", name),
                                  ctx.mkBoolConst(name));
  }

  @Override
  public PresenceCondition getDefinedVariable(String name) {
    // get defined variable gives a new bdd, which presence condition expects
    return new PresenceConditionZ3(getVariableManager().getDefinedVariable(name),
                                  GNode.create("DefinedExpression", GNode.create("PrimaryIdentifier", name)),
                                  ctx.mkBoolConst(getVariableManager().createDefinedVariable(name)));
  }

  /**
   * The z3 context factory used to create z3 expressions.  This is
   * used by ConditionEvaluator.
   *
   * @return The z3 context.
   */
  public Context getZ3Context() {
    return ctx;
  }

  /*
     PresenceCondition variations:
     1. traditional one, just BDDs
     2. desguaring versions, maintain BDDs and z3 simultaneously
     3. optimal (?) one, just BDDs, but translate to z3 only when requested/printed
  */

  /** A reference-counted presence condition that automatically cleans up BDD when
    * nothing references it anymore.
    */
  public class PresenceConditionZ3 extends PresenceConditionManager.PresenceConditionBDD {
    /** The tree representation of this expression. */
    private Node tree;

    /** The z3 expression representation of this expression. */
    private BoolExpr expr;

    /** Creates a new PresenceCondition out of the given bdd.  Make sure the bdd
      * is not shared by anyone else.
      */
    private PresenceConditionZ3(BDD bdd, Node tree, BoolExpr expr) {
      super(bdd);
      this.tree = tree;
      this.expr = expr;
      // this.simplify();
    }
    
    private PresenceConditionZ3(boolean value) {
      super(value);
      this.tree = value ? oneNode : zeroNode;
      this.expr = value ? ctx.mkTrue() : ctx.mkFalse();
    }
    
    // TODO: z3 simplify
    // ApplyResult ar = applyTactic(ctx, ctx.mkTactic("simplify"), goal);
    
    @Override
    public PresenceCondition not() {
      GNode nottree;
      BoolExpr notexpr;
      if (this.tree.getName().equals("LogicalNegationExpression")) {
        nottree = (GNode) this.tree.get(0);
        // TODO: just remove the negation
        notexpr = (BoolExpr) ctx.mkNot(this.expr).simplify();
      } else {
        nottree = GNode.create("LogicalNegationExpression", this.tree);
        // this.simplify();
        notexpr = ctx.mkNot(this.expr);
      }
      return new PresenceConditionZ3(bdd.not(), nottree, notexpr);
    }
    
    @Override
    public PresenceCondition and(PresenceCondition c) {
      if (this.is(c)) {
        return this.addRef();
      } else if (c.isTrue()) {
        return this.addRef();
      } else if (this.isTrue()) {
        return c.addRef();
      } else if (this.isFalse()) {
        return new PresenceConditionZ3(false);
      } else if (c.isFalse()) {
        return new PresenceConditionZ3(false);
      } else {
        // this.simplify();
        // c.simplify();
        return new PresenceConditionZ3(bdd.and(((PresenceConditionZ3) c).bdd),
                                     GNode.create("LogicalAndExpression", this.tree, ((PresenceConditionZ3) c).tree),
                                     ctx.mkAnd(this.expr, ((PresenceConditionZ3) c).expr));
      }
    }

    /** Return this presence condition and not c.  Free any intermediate bdds. */
    public PresenceCondition andNot(PresenceCondition c) {
      PresenceCondition not = c.not();
      PresenceCondition result = this.and(not);
      not.delRef();
      return result;
      // PresenceCondition newPresenceCondition;
      // BDD notBDD;
      
      // notBDD = c.bdd.not();
      // newPresenceCondition = new PresenceConditionZ3(bdd.and(notBDD));
      // notBDD.free();
      
      // return newPresenceCondition;
    }
    
    /** Return this presence condition or c.  Free any intermediate bdds. */
    public PresenceCondition or(PresenceCondition c) {
      if (this.is(c)) {
        return this.addRef();
      } else if (c.isFalse()) {
        return this.addRef();
      } else if (this.isFalse()) {
        return c.addRef();
      } else if (this.isTrue()) {
        return new PresenceConditionZ3(true);
      } else if (c.isTrue()) {
        return new PresenceConditionZ3(true);
      } else {
        // this.simplify();
        // c.simplify();
        return new PresenceConditionZ3(bdd.or(((PresenceConditionZ3) c).bdd),
                                     GNode.create("LogicalOrExpression", this.tree, ((PresenceConditionZ3) c).tree),
                                     ctx.mkOr(this.expr, ((PresenceConditionZ3) c).expr));
      }
    }

    // TODO: handle restrict and simplify for other representations or
    // // remove their use
    // /** Restrict */
    // public PresenceCondition restrict(PresenceCondition c) {
    //   return new PresenceConditionZ3(bdd.restrict(c.getBDD()));
    // }
    
    // /** Simplify */
    // public PresenceCondition simplify(PresenceCondition c) {
    //   return new PresenceConditionZ3(bdd.simplify(c.getBDD()));
    // }

    // /** One sat */
    // public PresenceCondition satOne() {
    //   // TODO: may need to remove this and rework its users
    //   return new PresenceConditionZ3(bdd.satOne());
    // }
    
    public boolean useContextSimplify = true;
    public String nameContextSimplify = "ctx-simplify";  // better than "simplify" alone
    // public String nameContextSimplify = "ctx-solver-simplify";  // best simplification, but very slow due to calls to solver
    
    protected void simplify() {
      if (! isSimplified) {
        isSimplified = true;
        if (isFalse()) {
          this.expr = ctx.mkFalse();
        } else if (isTrue()) {
          this.expr = ctx.mkTrue();
        } else {
          if (useContextSimplify) {
            this.expr = contextsimplify(expr);
          }
          this.expr = (BoolExpr) expr.simplify();
        }
      }
    }

    protected BoolExpr contextsimplify(BoolExpr expr) {
      Goal goal = ctx.mkGoal(true, false, false);
      goal.add(expr);
      Tactic tactic = ctx.mkTactic(nameContextSimplify);
      ApplyResult ar = tactic.apply(goal);

      if (ar.getNumSubgoals() != 1) {
        throw new AssertionError("expected only one subgoal from z3 tactic");
      }

      Goal result = ar.getSubgoals()[0];
      return result.AsBoolExpr();
    }

    /**
     * Get the expression tree representation of this presence condition.
     */
    public Node tree() {
      return tree;
    }
    
    /**
     * Get the z3 expression representation of this presence condition.
     */
    public BoolExpr z3() {
      return expr;
    }
    
    @Override
    public void print(Writer writer) throws IOException {
        printz3(expr, writer);
    }

    /**
     * Print the presence condition using z3 to a writer.
     *
     * @param writer The writer.
     * @throws IOException Because it uses a Writer.
     */
    public void printz3(BoolExpr expr, Writer writer) throws IOException {
      // boolean save = useContextSimplify;
      // useContextSimplify = false;
      // this.simplify();
      // useContextSimplify = save;

      // writer.write(expr.toString());

      Solver solver = getZ3Context().mkSimpleSolver();
      solver.add(expr);
      writer.write(solver.toString().replace("\n", ""));
    }

    @Override
    public String toSMT2() {
      // the printer already uses the z3 solver to print out
      return toString();
    }

    // /**
    //  * Print the BDD as a CNF clauses.
    //  *
    //  * @param writer The writer.
    //  * @throws IOException Because it uses a Writer.
    //  */
    // public void printCNF(Writer writer) throws IOException {
    //   if (this.isTrue()) {
    //     writer.write("1");

    //     return;

    //   } else if (this.isFalse()) {
    //     writer.write("0");

    //     return;
    //   }

    //   // We use the allsat() function on the bdd to get the clauses.
    //   // allsat is in DNF, so we first negate the bdd.  Then, to
    //   // generate CNF, we negate the clauses to make them conjunctive
    //   // again.
    //   PresenceCondition not = this.not();
    //   List allsat = (List) not.getBDD().allsat();

    //   for (Object o : allsat) {
    //     byte[] sat = (byte[]) o;
    //     ArrayList<Integer> clause = new ArrayList<Integer>();
    //     StringBuilder sb = new StringBuilder();
    //     for (int i = 0; i < sat.length; i++) {
    //       int sign = 1;
              
    //       switch (sat[i]) {
    //       case 1:
    //         // negate again
    //         sign = -1;
    //       case 0:
    //         String varname = not.presenceConditionManager().getVariableManager().getName(i);
    //         // if (varname.startsWith("(defined ")) {
    //         if (varname.contains("CONFIG")) {
    //         // if (varname.startsWith("(defined CONFIG_")) {
    //           // varname = varname.substring(9, varname.length() - 1);
    //           if (-1 == sign) {
    //             sb.append("-");
    //           }
    //           // sb.append("[");
    //           sb.append(varname);
    //           // sb.append("]");
    //           sb.append(",");
    //         }
    //         break;
    //       }
    //     }
    //     if (sb.toString().length() > 0) {
    //       writer.write("(");
    //       writer.write(sb.toString());
    //       writer.write(")");
    //     }
    //   }

    //   not.delRef();
    // }

    public PresenceConditionManager presenceConditionManager() {
      return PresenceConditionManagerZ3.this;
    }

    // /** Output the presence condition as a valid cpp conditional expression */
    // public String toCNF() {
    //   StringWriter writer = new StringWriter();

    //   try {
    //     PresenceCondition not = this.not();
    //     printNotCNF(not, writer);
    //     not.delRef();
    //   } catch (IOException e) {
    //     // An inelegant way to sidestep not being able to throw an
    //     // exception from the overridden toString method.
    //     throw new RuntimeException();
    //   }

    //   return writer.toString();
    // }

    // /** Output the presence condition as a valid cpp conditional expression */
    // public String toNotCNF() {
    //   StringWriter writer = new StringWriter();

    //   try {
    //     printNotCNF(this, writer);
    //   } catch (IOException e) {
    //     // An inelegant way to sidestep not being able to throw an
    //     // exception from the overridden toString method.
    //     throw new RuntimeException();
    //   }

    //   return writer.toString();
    // }
  }
}
