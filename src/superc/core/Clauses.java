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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Visitor;

import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;

/**
 * Manager for SAT solving and clauses.  Converts expressions to CNF
 * form, manages variable names, and initializes and runs the SAT
 * solver.  After construction, use addClause() to add boolean
 * expressions as parse trees.  Then the clauses can be iterated over,
 * returning an integer array on each iteration corresponding to one
 * CNF clause.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.10 $
 */
public class Clauses implements Iterable<ArrayList<Integer>> {
  private ArrayList<String> variables;
  private Map<String, Integer> varmap;
  private ArrayList<ArrayList<Integer>> clauses;
  private boolean isFalse;

  public Clauses() {
    this.varmap = new HashMap<String, Integer>();
    this.variables = new ArrayList<String>();
    this.clauses = new ArrayList<ArrayList<Integer>>();
    this.isFalse = false;
  }

  /**
   * The copy constructor.
   *
   * @param clauses The clauses object to copy.
   */
  public Clauses(Clauses clausesin) {
    this.varmap = new HashMap<String, Integer>(clausesin.varmap);
    this.variables = new ArrayList<String>(clausesin.variables);
    this.clauses = new ArrayList<ArrayList<Integer>>(clausesin.clauses);
    this.isFalse = clausesin.isFalse;
  }

  public boolean isFalse() {
    return this.isFalse;
  }

  public Map<String, Integer> getVarmap() {
    return varmap;
  }

  /**
   * Add an int array clause.
   *
   * @param int_clause The clause.
   */
  public void addClause(ArrayList<Integer> int_clause) {
    this.clauses.add(int_clause);
  }

  private ArrayList<ArrayList<Integer>> getClauses(Node tree) {
    ArrayList<ArrayList<Integer>> newClauses = (ArrayList<ArrayList<Integer>>) cnfVisitor.dispatch(tree);
    this.isFalse = newClauses == ZERO;
    return newClauses;
  }

  private void addClauses(ArrayList<ArrayList<Integer>> newClauses) {
    if (null != newClauses) {
      this.clauses.addAll(newClauses);
    } else {
      System.err.println("warning: null tree");
    }
  }

  /**
   * Add a clause given as a Rats! C expression AST.
   *
   * @param tree The expression tree.
   */
  public void addClause(Node tree) {
    ArrayList<ArrayList<Integer>> newClauses = getClauses(tree);
    addClauses(newClauses);
  }

  /**
   * Add a clause in CNF style, formatted like "(VARNAME,
   * -VARNAME2,)(VARNAME3)"
   *
   * @param clausestring The clause string.
   */
  public void addClauses(String clausestring) {
    int i = 0;
    char c;
    //read all clauses and add them
    while (i < clausestring.length()) {
      c = clausestring.charAt(i);

      if ('1' == c) {
        // true clauses contribute nothing
        i++;
        continue;
      }

      if ('0' == c) {
        // false clauses make the entire expression false
        this.isFalse = true;
        break;
      }

      // read each clause
      ArrayList<Integer> int_clause = new ArrayList<Integer>();
      if ('(' != c) {
        System.err.println("invalid clause string");
        break;
      }
      // move past the (
      i++;
      c = clausestring.charAt(i);
      while (')' != c) {
        boolean isneg = false;
        if ('-' == c) {
          isneg = true;
          // move past the -
          i++;
          c = clausestring.charAt(i);
        }

        // read each var
        StringBuilder sb_varname = new StringBuilder();
        while (',' != c) {
          sb_varname.append(c);
          i++;
          c = clausestring.charAt(i);
        }
        // move past the ,
        i++;
        c = clausestring.charAt(i);

        // convert the varname to a varnum
        // System.err.println(sb_varname.toString());
        int varnum = this.getVarNum(sb_varname.toString());
        sb_varname = null;

        if (isneg) {
          varnum *= -1;
        }

        // TODO add varnum to clause vector
        int_clause.add(varnum);
      }

      // System.err.println(int_clause);
      if (int_clause.size() > 0) {
        this.addClause(int_clause);
      }

      i++;
    }
  }

  public boolean varExists(String var) {
    return this.varmap.containsKey(var);
  }

  public int getVarNum(String var) {
    if (varExists(var)) {
      return this.varmap.get(var);
    } else {
      this.variables.add(var);
      this.varmap.put(var, this.variables.size());
      return this.variables.size();
    }
  }

  public String getVarName(int varnum) {
    int arrayIndex = varnum - 1;
    if (arrayIndex >= 0 && arrayIndex < this.variables.size()) {
      return this.variables.get(arrayIndex);
    } else {
      return null;
    }
  }

  public int getNumVars() {
    return this.variables.size();
  }

  public int size() {
    return this.clauses.size();
  }

  public Iterator<ArrayList<Integer>> iterator() {
    return this.clauses.iterator();
  }

  final private static ArrayList<ArrayList<Integer>> ONE =
    new ArrayList<ArrayList<Integer>>();
  final private static ArrayList<ArrayList<Integer>> ZERO =
    new ArrayList<ArrayList<Integer>>();

  private Visitor cnfVisitor = new Visitor() {
      /** Process an integer constant. */
      public ArrayList<ArrayList<Integer>> visitIntegerConstant(GNode n) {
        // xtc.type.Type result = cops.typeInteger(n.getString(0));
        // return result.getConstant().bigIntValue().longValue();
        String s = n.getString(0);
        if (s.equals("0")) {
          return ZERO;
        } else if (s.equals("1")) {
          return ONE;
        } else {
          return null;
        }
      }

      // /** Process a character constant. */
      // public ArrayList<ArrayList<Integer>> visitCharacterConstant(GNode n) {
      //   // xtc.type.Type result = cops.typeCharacter(n.getString(0));
      //   // return result.getConstant().bigIntValue().longValue();
      //   return null;
      // }

      /** Process primary identifier. */
      public ArrayList<ArrayList<Integer>> visitPrimaryIdentifier(GNode n) {
        // create clause with a single variable, hashing to a variable
        // number
        ArrayList<ArrayList<Integer>> a = new ArrayList<ArrayList<Integer>>();
        ArrayList<Integer> clause = new ArrayList<Integer>();
        clause.add(getVarNum(n.getString(0)));
        a.add(clause);
        return a;
      }

      /** Process defined expression. */
      public Object visitDefinedExpression(GNode n) {
        return visitPrimaryIdentifier(n.getGeneric(0));
      }
      
      /** Process a logical negation. */
      public ArrayList<ArrayList<Integer>> visitLogicalNegationExpression(GNode n) {
        // get resulting clauses and do de morgan's on them
        ArrayList<ArrayList<Integer>> a =
          (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(0));
        ArrayList<ArrayList<Integer>> newa = null;

        if (null == a) return null;
        if (ONE == a) return ZERO;
        if (ZERO == a) return ONE;

        // do de morgan's
        for (ArrayList<Integer> clause : a) {
          ArrayList<ArrayList<Integer>> pendinga = new ArrayList<ArrayList<Integer>>();

          // first negate the clause
          ArrayList<Integer> negatedVars = new ArrayList<Integer>();
          for (Integer i : clause) {
            negatedVars.add(-1 * i);
          }
          if (null == newa) {
            pendinga.add(negatedVars);
          } else {
            for (ArrayList<Integer> oldClause : newa) {
              for (Integer negi : negatedVars) {
                ArrayList<Integer> newClause = new ArrayList<Integer>();
                newClause.addAll(oldClause);
                newClause.add(negi);
                pendinga.add(newClause);
              }
            }
          }
          newa = pendinga;
        }

        return newa;
      }

      /** Process a equality expression. */
      public ArrayList<ArrayList<Integer>> visitEqualityExpression(GNode n) {
        // ArrayList<ArrayList<Integer>> a, b, result;
        // String op;
        // boolean mydostring = dostring;
    
        // nonboolean = true;

        // dostring = true;
    
        // a = (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(0));
        // b = (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(2));
        // op = n.getString(1);
    
        // dostring = false;
    
        // if (a instanceof Long && b instanceof Long) {
        //   if (op.equals("==")) {
        //     result = ((Long) a).equals((Long) b);
        //   }
        //   else if (op.equals("!=")) {
        //     result = ! ((Long) a).equals((Long) b);
        //   }
        //   else {
        //     result = "";
        //   }
        // }
        // else {
        //   String sa, sb;
      
        //   if (a instanceof String) {
        //     sa = (String) a;
        //   }
        //   else if (a instanceof Long) {
        //     sa = ((Long) a).toString();
        //   }
        //   else {
        //     return null;
        //   }
      
        //   if (b instanceof String) {
        //     sb = (String) b;
        //   }
        //   else if (b instanceof Long) {
        //     sb = ((Long) b).toString();
        //   }
        //   else {
        //     return null;
        //   }
      
        //   if (op.equals("==") && sa.equals(sb)) {
        //     result = mydostring ? "1" : B.one();
        //   }
        //   else {
        //     result = parens(sa) + " " + op + " " + parens(sb);
        //   }
        // }
    
        // return result;

        // do nothing with equality
        return null;
      }

      /** Process a logical and. */
      public ArrayList<ArrayList<Integer>> visitLogicalAndExpression(GNode n) {
        // append clauses to a single list of clauses
        ArrayList<ArrayList<Integer>> a =
          (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(0));
        ArrayList<ArrayList<Integer>> b =
          (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(1));
        ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();

        if (ONE == a) return b;
        if (ZERO == a) return ZERO;
        if (ONE == b) return a;
        if (ZERO == b) return ZERO;

        if (null != a) result.addAll(a);
        if (null != b) result.addAll(b);

        // return new clause
        return result;
      }

      /** Process a logical or. */
      public ArrayList<ArrayList<Integer>> visitLogicalOrExpression(GNode n) {
        // cartesian product of all clauses from each term of the
        // operation
        ArrayList<ArrayList<Integer>> a =
          (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(0));
        ArrayList<ArrayList<Integer>> b =
          (ArrayList<ArrayList<Integer>>) dispatch(n.getGeneric(1));

        if (ONE == a) return ONE;
        if (ZERO == a) return b;
        if (ONE == b) return ONE;
        if (ZERO == b) return a;
        if (null == a) return b;
        if (null == b) return a;

        ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<Integer>>();
        for (ArrayList<Integer> ai : a) {
          for (ArrayList<Integer> bi : b) {
            ArrayList<Integer> ab = new ArrayList<Integer>();
            ab.addAll(ai);
            ab.addAll(bi);
            result.add(ab);
          }
        }
        return result;
      }
    };
}
