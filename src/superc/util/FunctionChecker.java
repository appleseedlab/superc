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
package superc.util;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.StringReader;
import java.io.InputStreamReader;

import java.net.Socket;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.zip.Inflater;

import superc.expression.ExpressionRats;

import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.Clauses;

import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.Constants;

import xtc.util.Tool;
import xtc.util.Pair;

import xtc.lang.CParser;

import xtc.parser.Result;
import xtc.parser.ParseException;

import net.sf.javabdd.BDD;

import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;
import org.sat4j.specs.ContradictionException;
import org.sat4j.specs.IProblem;
import org.sat4j.specs.ISolver;
import org.sat4j.specs.TimeoutException;
import org.sat4j.tools.ModelIterator;

class FunctionChecker {
  private static int ZLIB_BUFFER = 4096;
  // static private int ZLIB_BUFFER = 10;

  private static Map<String, Map<String, ByteWrapper>> global_fundefs;

  private static Map<String, Map<String, ByteWrapper>> undef_funcalls;

  private static Map<String, List<ByteWrapper>> extra_constraints;

  private static Map<String, String> unit_pcs;

  private static Map<String, String> subdir_pcs;

  private static boolean debug = false;

  private static Clauses kconfigClauses = null;

  private static LinkedList<String> unit_queue;

  private static VecInt assumpvec;

  private static boolean useServer = false;

  private static String server;

  private static int port;

  private static boolean checkModel = false;

  private static String in_callunit;
  
  private static String in_funname;
  
  private static String in_defunit;

  private static boolean union_units = true;
  
  private static String getNextUnit() {
    if (useServer) {
      try {
        String filename;

        do {
          Socket socket= new Socket(server, port);
          BufferedReader in =
            new BufferedReader(new InputStreamReader(socket.getInputStream()));

          filename = in.readLine();
          socket.close();
        } while (null == filename);

        if (filename.equals("$end")) {
          return null;
        }
        return filename;

      } catch (java.net.ConnectException e) {
        e.printStackTrace();
        return null;
      } catch (java.io.IOException e) {
        e.printStackTrace();
        return null;
      }
    } else if (unit_queue.isEmpty()) {
      return null;
    } else {
      return unit_queue.remove();
    }
  }

  public static void main(String args[]) {
    // Use the Java implementation of JavaBDD. Setting it here means
    // the user doesn't have to set it on the commandline.
    System.setProperty("bdd", "java");

    if (args.length != 5 && args.length != 7 && args.length != 8) {
      System.err.println("" +
"USAGE\n" +
"java superc.util.FunctionChecker functions functions_pc unit_pcs kconfig_model model_assumptions [[server port] | [callunit funname defunit] ]\n" +
"\n" +
"Check for linker errors across the entire Linux kernel.  Requires using\n" +
"$KMAX_ROOT/collection_functions.py to collect global function definitions and\n" +
"calls along with their presence conditions.\n" +
"\n" +
"server and port retrieve unit names from a FilenameService.\n" +
"\n" +
"EXAMPLE\n" +
"java superc.util.FunctionChecker functions_4.0x86.txt functions_pc_4.0x86 unit_pc_4.0x86.txt clauses_4.0x86.txt model_assumptions_4.0x86.txt\n" +
"\n" +
                         "");
      System.exit(1);
    }
    String functions_file = args[0];
    String pc_file = args[1];
    String unit_pc_file = args[2];
    String kconfig_model_file = args[3];
    String model_assumptions = args[4];
    if (args.length == 7) {
      server = args[5];
      port = Integer.parseInt(args[6]);
      useServer = true;
    } else if (args.length == 8) {
      in_callunit = args[5];
      in_funname = args[6];
      in_defunit = args[7];
      checkModel = true;
    }
    global_fundefs = new HashMap<String, Map<String, ByteWrapper>>();
    undef_funcalls = new HashMap<String, Map<String, ByteWrapper>>();
    extra_constraints = new HashMap<String, List<ByteWrapper>>();
    unit_pcs = new HashMap<String, String>();
    subdir_pcs = new HashMap<String, String>();
    try {
      BufferedReader br = new BufferedReader(new FileReader(functions_file));
      BufferedInputStream bis = new BufferedInputStream(new FileInputStream(pc_file));
      BufferedReader unit_pc_br = new BufferedReader(new FileReader(unit_pc_file));
      String unit = null;
      int curpos = 0;

      System.err.println("reading functions and their presence conditions");
      for (String line; (line = br.readLine()) != null; ) {
        if (line.startsWith("compilation_unit")) {
          String[] a = line.split(" ");

          unit = a[1];
        } else if (line.startsWith("global_fundef") ||
                   line.startsWith("undef_funcall") ||
                   line.startsWith("extra_constraint")) {
          String[] a = line.split(" ");
          String funname = null;
          int pc_start;
          int pc_len;

          if (checkModel && ! (unit.equals(in_callunit)
                               || unit.equals(in_defunit))) {
            continue;
          }
          
          if (line.startsWith("extra_constraint")) {
            pc_start = Integer.parseInt(a[1]);
            pc_len = Integer.parseInt(a[2]);
          } else {
            funname = a[1];
            if (checkModel && ! (funname.equals(in_funname))) {
              continue;
            }
            pc_start = Integer.parseInt(a[2]);
            pc_len = Integer.parseInt(a[3]);
          }

          if (pc_start != curpos) {
            // System.err.println("MISSING PC");
            // System.exit(1);
            long skip = pc_start - curpos;
            while ((skip -= bis.skip(skip)) > 0);
            curpos = pc_start;
          }

          if (checkModel && ! (unit.equals(in_callunit)
                               || unit.equals(in_defunit))) {
            long skip = pc_start + pc_len - curpos;
            while ((skip -= bis.skip(skip)) > 0);
            curpos = pc_start + pc_len;
            continue;
          }

          // read the boolean expression
          byte[] pc = new byte[pc_len];
          int bytesread = bis.read(pc, 0, pc_len);

          if (bytesread < 0 || bytesread != pc_len) {
            System.err.println("PROBLEM READING PC FILE");
            System.exit(1);
          }

          curpos += bytesread;

          // if (checkModel && ! (unit.equals(in_callunit)
          //                      || unit.equals(in_defunit))) {
          //   continue;
          // }

          if (line.startsWith("global_fundef")) {
            addTuple(global_fundefs, unit, funname, pc);
          } else if (line.startsWith("undef_funcall")) {
            addTuple(undef_funcalls, unit, funname, pc);
          } else if (line.startsWith("extra_constraint")) {
            addList(extra_constraints, unit, pc);
          }
        }
      }

      System.err.println("reading unit presence conditions");
      for (String line; (line = unit_pc_br.readLine()) != null; ) {
        if (line.startsWith("unit_pc ")) {
          String[] a = line.split(" ", 3);
          String name = a[1];
          // if (!(name.equals(in_callunit) || name.equals(in_defunit))) {
          //   continue;
          // }
          String pc = a[2];
          pc = pc.replace("=y", "");
          unit_pcs.put(name, pc);
          if (debug) System.err.println("adding unit " + name + " " + pc);
        } else if (line.startsWith("subdir_pc ")) {
          String[] a = line.split(" ", 3);
          String name = a[1];
          String pc = a[2];
          pc = pc.replace("=y", "");
          subdir_pcs.put(name, pc);
          if (debug) System.err.println("adding subdir " + name + " " + pc);
        }
      }

      System.err.println("reading kconfig model");
      BufferedReader kconfig_model_br =
        new BufferedReader(new FileReader(kconfig_model_file));
      String  line = kconfig_model_br.readLine();

      kconfigClauses = new Clauses();
      int line_c = 1;
      while (null != line) {
        {
          StringReader reader = new StringReader(line);
          ExpressionRats clauseParser
            = new ExpressionRats(reader, "CLAUSE", line.length());

          Result clauseTree;
          Node tree = null;
          try {
            clauseTree = clauseParser.pConstantExpression(0);
            // tree = (Node) clauseParser.value(clauseTree);
            if (! clauseTree.hasValue()) {
              tree = null;
              System.err.println(clauseParser.format(clauseTree.parseError()));
            } else {
              tree = clauseTree.semanticValue();
              // // System.err.println((Node) clauseParser.value(clauseTree));
              // System.err.println("evaluating the expression on line " + line_c);
              // BDD bdd = conditionEvaluator.evaluate(tree);
              // PresenceCondition pc =
              //   presenceConditionManager.new PresenceCondition(bdd);
              // // System.err.println(pc);
            }
            // System.err.println(tree);
          } catch (java.io.IOException e ) {
            e.printStackTrace();
            throw new RuntimeException("couldn't parse expression");
          }

          if (null != tree) {
            if (true) kconfigClauses.addClause(tree);
          }
        }

        line = kconfig_model_br.readLine();
        line_c++;
      }


      List<Integer> assumptions = new ArrayList<Integer>();
      BufferedReader ma_br =
        new BufferedReader(new FileReader(model_assumptions));
      String ma_line = ma_br.readLine();

      // format is one var name per line, ! before it for assume false
      while (null != ma_line) {
        int sign = 1;
        String varname = ma_line;
        if (ma_line.startsWith("!")) {
          sign = -1;
          varname = ma_line.substring(1);
        }
        
        assumptions.add(sign * kconfigClauses.getVarNum(varname));
        ma_line = ma_br.readLine();
      }

      int[] assumpints = new int[assumptions.size()];
      for (int i = 0; i < assumptions.size(); i++) {
        assumpints[i] = assumptions.get(i);
      }
      assumpvec = new VecInt(assumpints);

      try {
        ISolver solver = SolverFactory.newDefault();
        solver.newVar(kconfigClauses.getNumVars());
        solver.setExpectedNumberOfClauses(kconfigClauses.size());

        for (List<Integer> clause : kconfigClauses) {
          int[] cint = new int[clause.size()];
          int i = 0;
          for (Integer val : clause) {
            cint[i++] = val;
          }
          try {
            solver.addClause(new VecInt(cint));
          } catch (ContradictionException e) {
            System.err.println("kconfig model is self-contradictoary");
            System.exit(1);
          }
        }

        IProblem problem = new ModelIterator(solver);
        if (problem.isSatisfiable(assumpvec)) {
          System.err.println("kconfig model is satisfiable");
        } else {
          System.err.println("kconfig model is unsatisfiable");
          System.exit(1);
        }
      } catch (TimeoutException e) {
        e.printStackTrace();
        System.exit(1);
      }
      

      if (! useServer) {
        unit_queue = new LinkedList<String>();
        for (String calling_unit : undef_funcalls.keySet()) {
          unit_queue.add(calling_unit);
        }
      }

      // map fun calls to union of all pcs of units that define them
      Map<String, List<String>> fundef_to_units = new HashMap<String, List<String>>();
      if (union_units) {
        System.err.println("unioning calls of the same name across compilation units");
        // union pcs for global fundefs across units
        for (String fundef_unit : global_fundefs.keySet()) {
          for (String fundef_name : global_fundefs.get(fundef_unit).keySet()) {
            if (! fundef_to_units.containsKey(fundef_name)) {
              fundef_to_units.put(fundef_name, new ArrayList<String>());
            }
            fundef_to_units.get(fundef_name).add(fundef_unit);
          }
        }
      }

      System.err.println("computing undefined functions");
      String calling_unit = null;
      while (null != (calling_unit = getNextUnit())) {
        if (useServer && ! undef_funcalls.containsKey(calling_unit)) continue;
        // if (! calling_unit.equals("crypto/tcrypt.c")) continue;
        Map<String, ByteWrapper> calls = undef_funcalls.get(calling_unit);
        String calling_unit_pc = conjoinPath(calling_unit);
        List<ByteWrapper> calling_unit_extra = extra_constraints.containsKey(calling_unit) ? extra_constraints.get(calling_unit) : null;
        if (null == calling_unit_pc) continue;
        if (debug) System.err.println(calling_unit);
        for (String call : calls.keySet()) {
          // if (! call.equals("crypto_alloc_ablkcipher")) continue;
          if (union_units) {
            if (fundef_to_units.containsKey(call)) {
              byte[] call_pc = undef_funcalls.get(calling_unit).get(call).bytes;
              List<String> fundef_units = fundef_to_units.get(call);
              System.err.println("checking " + calling_unit + " " + call + " " + fundef_units);
              checkFunction(calling_unit,
                            calling_unit_pc,
                            call,
                            call_pc,
                            fundef_units,
                            calling_unit_extra);
            }
          } else {
            for (String fundef_unit : global_fundefs.keySet()) {
              Map<String, ByteWrapper> globals = global_fundefs.get(fundef_unit);
              if (globals.containsKey(call)) {
                byte[] call_pc = undef_funcalls.get(calling_unit).get(call).bytes;
                List<String> fundef_units = new ArrayList<String>();
                fundef_units.add(fundef_unit);
                System.err.println("checking " + calling_unit + " " + call + " " + fundef_units);
                checkFunction(calling_unit,
                              calling_unit_pc,
                              call,
                              call_pc,
                              fundef_units,
                              calling_unit_extra);
              }
            }
          }
        }
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * Conjoin the configuration boolean expression for the unit and all
   * subdirectories in which its contained.
   *
   * @param unit The name of the compilation unit.  Cannot be null.
   * @return The expression.
   */
  public static String conjoinPath(String unit_c_file) {
    String unit = unit_c_file.substring(0, unit_c_file.length() - 1) + "o";
    if (! unit_pcs.containsKey(unit)) {
      if (debug) System.err.println("no pc found for " + unit);
      return null;
    }
    
    StringBuilder sb = new StringBuilder();

    sb.append("(");
    sb.append(unit_pcs.get(unit));
    sb.append(")");

    // if (debug) System.err.println(unit);

    // for each component of the path.  exclude the last element,
    // because that's the basename.
    String[] subdirs = unit.split("/");
    for (int i = 0; i < subdirs.length - 2 /* exclude last element */; i++) {
      StringBuilder subdir = new StringBuilder();
      String delim = "";
      for (int j = 0; j <= i + 1; j++) {
        subdir.append(delim);
        subdir.append(subdirs[j]);
        delim = "/";
      }
      // if (debug) System.err.println(subdir.toString());
      if (subdir_pcs.containsKey(subdir.toString())) {
        sb.append(" && (");
        sb.append(subdir_pcs.get(subdir.toString()));
        sb.append(")");
      }
    }

    return sb.toString();
  }

  public static void checkFunction(String calling_unit, String calling_unit_pc, String call, byte[] call_pc, List<String> fundef_units, List<ByteWrapper> calling_unit_extra) {
    // Clauses[] unionClauses = new Clauses[3];
    Clauses[] unionClauses = new Clauses[2];
    unionClauses[0] = new Clauses(kconfigClauses);

    /* SAT models:
     * [0] - kconf ^ call_unit ^ call ^ !def_unit
     * [1] - kconf ^ call_unit ^ call             ^ !def
     * [2] - kconf ^ call_unit        ^ !def_unit
     */

    // TODO add support for composite pc updates

    checkModel = true;

    unionClauses[0].addClause(getExpression(calling_unit_pc));
    if (checkModel) System.err.println("calling_unit_pc: " + calling_unit_pc);

    // unionClauses[2] = new Clauses(unionClauses[0]);

    {
      StringBuilder sb = new StringBuilder();
      // and the two pcs.  note that fundef_pc is already negated by
      // SuperC.java when emitted.
      sb.append(decompress(call_pc));
      if (checkModel) System.err.println("call_pc: " + decompress(call_pc));
      unionClauses[0].addClauses(decompress(call_pc));
      sb = null;

      // add any extra constraints
      if (null != calling_unit_extra) {
        for (ByteWrapper b : calling_unit_extra) {
          if (true) unionClauses[0].addClauses(decompress(b.bytes));
        }
      }

    }

    // copy clauses before and'ing !fundef_unit_pc and !fundef_pc
    // separatly
    unionClauses[1] = new Clauses(unionClauses[0]);
    for (String fundef_unit : fundef_units) {
      byte[] fundef_pc = global_fundefs.get(fundef_unit).get(call).bytes;
      String fundef_unit_pc = conjoinPath(fundef_unit);
      List<ByteWrapper> fundef_unit_extra = extra_constraints.containsKey(fundef_unit) ? extra_constraints.get(fundef_unit) : null;
      StringBuilder sb = new StringBuilder();
      sb.append("! (");
      sb.append(fundef_unit_pc);
      if (checkModel) System.err.println("fundef_unit_pc: " + fundef_unit_pc);
      sb.append(")");
      unionClauses[0].addClause(getExpression(sb.toString()));
      // unionClauses[2].addClause(getExpression(sb.toString()));
      sb = null;

      if (null != fundef_pc) {
        String fundef_pc_decompressed = decompress(fundef_pc);
        if (checkModel) System.err.println("fundef_pc: " + fundef_pc_decompressed);
        unionClauses[1].addClauses(fundef_pc_decompressed);
        fundef_pc_decompressed = null;
      }

      // // needs to be in a separate or term
      // if (null != fundef_unit_extra) {
      //   for (ByteWrapper b : fundef_unit_extra) {
      //     // these constrain global def, make sure negation is correct!
      //     if (false) unionClauses[2].addClauses(decompress(b.bytes));
      //   }
      // }
    }

    boolean satisfiable = false;
    for (int ci = 0; ci < unionClauses.length; ci++) {
      // if (union_units && 0 != ci) continue;
      
      Clauses clauses = unionClauses[ci];
      boolean contradiction = false;

      if (checkModel) System.err.println("checking clause " + ci);

      if (unionClauses[ci].isFalse()) {
        if (checkModel) {
          System.err.println("clause is false");
        }
        continue;
      }
      try {
        ISolver solver = SolverFactory.newDefault();

        solver.newVar(clauses.getNumVars());
        solver.setExpectedNumberOfClauses(clauses.size());

        // use set instead of list?
        for (List<Integer> clause : clauses) {
          int[] cint = new int[clause.size()];
          int i = 0;
          // System.err.print("[");
          for (Integer val : clause) {
            cint[i++] = val;
            // System.err.print(val + ", ");
          }
          // System.err.println("]");
          try {
            // IConstr curConstr = solver.addClause(new VecInt(cint));
            solver.addClause(new VecInt(cint));
          } catch (ContradictionException e) {
            if (debug) e.printStackTrace();
            System.err.format("contradiction %s\n", ci);
            if (false) e.printStackTrace();
            contradiction = true;
            break;
            /* System.exit(1); */
          }
          /* if (null == firstConstr) { */
          /*   // save the first constraint to undo later */
          /*   firstConstr = curConstr; */
          /* } */
        }

        IProblem problem;
        if (checkModel) {
          problem = new ModelIterator(solver);
        } else {
          problem = solver;
        }
        int[] model = null;
        if (!contradiction && problem.isSatisfiable(assumpvec)) {
          satisfiable = true;
          System.err.format("sat %s %s %s %s\n", ci, calling_unit, call, fundef_units);
          if (checkModel) {
            model = problem.model();
            System.err.print("model: ");
            String delim = "[";
            for (int i = 0; i < model.length; i++) {
              if (model[i] > 0) {
                System.err.print(delim + clauses.getVarName(model[i]));
                delim = ",";
              }
            }
            System.err.println("]");
          }
        } else {
          if (debug) System.err.println("no linker error found when " + calling_unit + " calls " + call + " defined in " + fundef_units);
        }

        // // remove constraint
        // if (null != firstConstr) {
        //   solver.removeConstr(firstConstr);
        // }
      } catch (TimeoutException e) {
        e.printStackTrace();
        /* System.exit(1); */
      }
    }
    
    // if (satisfiable) {
    //   System.err.println("POTENTIAL LINKER ERROR WHEN " + calling_unit + " calls " + call + " defined in " + fundef_unit);
    // }
  }

  // public static void checkFunction(String calling_unit, String calling_unit_pc, String call, byte[] call_pc, String fundef_unit, String fundef_unit_pc, byte[] fundef_pc, List<ByteWrapper> calling_unit_extra, List<ByteWrapper> fundef_unit_extra) {
  //   Clauses clauses = new Clauses(kconfigClauses);
  //   // Clauses clauses = new Clauses();

  //   // TODO add support for composite pc updates

  //   // checkModel = true;

  //   if (true) clauses.addClause(getExpression(calling_unit_pc));
  //   if (checkModel) System.err.println(calling_unit_pc);

  //   // TODO conjoin the pcs from each directory in the path before
  //   // negating
  //   StringBuilder sb = new StringBuilder();
  //   sb.append("! (");
  //   sb.append(fundef_unit_pc);
  //   if (checkModel) System.err.println(fundef_unit_pc);
  //   sb.append(")");
  //   if (false) clauses.addClause(getExpression(sb.toString()));
  //   sb = null;

  //   sb = new StringBuilder();
  //   // and the two pcs.  note that fundef_pc is already negated by
  //   // SuperC.java when emitted.
  //   if (false) sb.append(decompress(call_pc));
  //   // if (checkModel) System.err.println(decompress(call_pc));
  //   if (false) sb.append(decompress(fundef_pc));
  //   // if (checkModel) System.err.println(decompress(fundef_pc));
  //   clauses.addClauses(sb.toString());
  //   sb = null;

  //   // add any extra constraints
  //   if (null != fundef_unit_extra) {
  //     for (ByteWrapper b : fundef_unit_extra) {
  //       if (false) clauses.addClauses(decompress(b.bytes));
  //     }
  //   }
  //   if (null != calling_unit_extra) {
  //     for (ByteWrapper b : calling_unit_extra) {
  //       if (false) clauses.addClauses(decompress(b.bytes));
  //     }
  //   }

  //   boolean contradiction = false;

  //   try {
  //     ISolver solver = SolverFactory.newDefault();

  //     solver.newVar(clauses.getNumVars());
  //     solver.setExpectedNumberOfClauses(clauses.size());

  //     // use set instead of list?
  //     for (List<Integer> clause : clauses) {
  //       int[] cint = new int[clause.size()];
  //       int i = 0;
  //       // System.err.print("[");
  //       for (Integer val : clause) {
  //         cint[i++] = val;
  //         // System.err.print(val + ", ");
  //       }
  //       // System.err.println("]");
  //       try {
  //         // IConstr curConstr = solver.addClause(new VecInt(cint));
  //         solver.addClause(new VecInt(cint));
  //       } catch (ContradictionException e) {
  //         if (debug) e.printStackTrace();
  //         System.err.println("contradiction");
  //         if (false) e.printStackTrace();
  //         contradiction = true;
  //         break;
  //         /* System.exit(1); */
  //       }
  //       /* if (null == firstConstr) { */
  //       /*   // save the first constraint to undo later */
  //       /*   firstConstr = curConstr; */
  //       /* } */
  //     }

  //     IProblem problem;
  //     if (checkModel) {
  //       problem = new ModelIterator(solver);
  //     } else {
  //       problem = solver;
  //     }
  //     int[] model = null;
  //     // if (!constradiction && problem.isSatisfiable(assumpvec)) {
  //     if (!contradiction && problem.isSatisfiable()) {
  //       System.err.println("POTENTIAL LINKER ERROR WHEN " + calling_unit + " calls " + call + " defined in " + fundef_unit);
  //       if (checkModel) {
  //         model = problem.model();
  //         System.err.print("model: ");
  //         String delim = "[";
  //         for (int i = 0; i < model.length; i++) {
  //           if (model[i] > 0) {
  //             System.err.print(delim + clauses.getVarName(model[i]));
  //             delim = ",";
  //           }
  //         }
  //         System.err.println("]");
  //       }
  //     } else {
  //       if (debug) System.err.println("no linker error found when " + calling_unit + " calls " + call + " defined in " + fundef_unit);
  //     }

  //     // // remove constraint
  //     // if (null != firstConstr) {
  //     //   solver.removeConstr(firstConstr);
  //     // }
  //   } catch (TimeoutException e) {
  //     e.printStackTrace();
  //     /* System.exit(1); */
  //   }
  // }

  public static String decompress(byte[] pc) {
    // decompress the boolean expression string
    StringBuilder sb = new StringBuilder();
    Inflater decompressor = new Inflater();
    decompressor.setInput(pc, 0, pc.length);
    byte[] result = new byte[ZLIB_BUFFER];
    while (decompressor.getRemaining() > 0) {
      try {
        int bytesinflated = decompressor.inflate(result);
        sb.append(new String(result, 0, bytesinflated));
      } catch (Exception e) {
        e.printStackTrace();
        System.exit(1);
      }
    }
    decompressor.end();
    
    return sb.toString();
  }

  public static Node getExpression(String s) {
    // parse the bdd into an expression tree
    StringReader reader = new StringReader(s);
    ExpressionRats clauseParser
      = new ExpressionRats(reader, "CLAUSE", s.length());

    Result clauseTree;
    Node tree = null;
    try {
      clauseTree = clauseParser.pConstantExpression(0);
      // tree = (Node) clauseParser.value(clauseTree);
      if (! clauseTree.hasValue()) {
        tree = null;
        System.err.println(clauseParser.format(clauseTree.parseError()));
      } else {
        tree = clauseTree.semanticValue();
      }
      // System.err.println(tree);
    } catch (java.io.IOException e ) {
      e.printStackTrace();
      throw new RuntimeException("couldn't parse expression");
    }

    return tree;
  }

  public static void addTuple(Map<String, Map<String, ByteWrapper>> map, String unit, String funname, byte[] pc) {
    if (! map.containsKey(unit)) {
      map.put(unit, new HashMap<String, ByteWrapper>());
    }
    map.get(unit).put(funname, new ByteWrapper(pc));
  }

  public static void addList(Map<String, List<ByteWrapper>> list, String unit, byte[] pc) {
    if (! list.containsKey(unit)) {
      list.put(unit, new ArrayList<ByteWrapper>());
    }
    list.get(unit).add(new ByteWrapper(pc));
  }

  public static class ByteWrapper {
    public byte[] bytes = null;
    public ByteWrapper(byte[] bytes) {
      this.bytes = bytes;
    }
  }

  public static class BDDName {
    public String name;
    public byte[] pc;

    public BDDName(String name, byte[] pc) {
      this.name = name;
      this.pc = pc;
    }
  }
}
