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

import java.lang.*;

import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.PrintWriter;

import java.util.HashSet;
import java.util.HashMap;

/**
 * This class generates a base class for semantic actions for a
 * grammar.  It takes "name, type" pairs from the standard input.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.9 $
 */
public class GenerateValuesClass {
  public static void main(String args[]) throws Exception {
    BufferedReader inputStream = null;
    PrintWriter outputStream = null;

    if (args.length != 2) {
      System.err.println("USAGE: GenerateValuesClass outClassName"
                         + " parseTablesClassName");
      System.exit(1);
    }

    String outClassName = args[0];
    String parseTablesClassName = args[1];
    ParseTables parseTables
      = (ParseTables) Class.forName(parseTablesClassName).newInstance();
    
    try {
      outputStream = new PrintWriter(System.out);
      
      outputStream.print("" +
"/*\n" +
" * xtc - The eXTensible Compiler\n" +
" * Copyright (C) 2009-2012 New York University\n" +
" *\n" +
" * This program is free software; you can redistribute it and/or\n" +
" * modify it under the terms of the GNU General Public License\n" +
" * version 2 as published by the Free Software Foundation.\n" +
" *\n" +
" * This program is distributed in the hope that it will be useful,\n" +
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n" +
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n" +
" * GNU General Public License for more details.\n" +
" *\n" +
" * You should have received a copy of the GNU General Public License\n" +
" * along with this program; if not, write to the Free Software\n" +
" * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,\n" +
" * USA.\n" +
" */\n" +
"package xtc.lang.cpp;\n" + 
"\n" +  
"import xtc.lang.cpp.ForkMergeParser.Subparser;\n" +  
"import xtc.tree.GNode;\n" +
"import xtc.util.Pair;" +
"\n" +  
"/**\n" +
" * This class is generated from grammar annotations and provides semantic\n" +
" * value and action support.\n" +
" */\n"
                         );
      inputStream = new BufferedReader(new InputStreamReader(System.in));

      HashSet<Integer> list = new HashSet<Integer>();
      HashSet<Integer> layout = new HashSet<Integer>();
      HashMap<Integer, String> action = new HashMap<Integer, String>();
      HashSet<Integer> passthrough = new HashSet<Integer>();
      HashSet<Integer> complete = new HashSet<Integer>();
      HashSet<Integer> voidSymbol = new HashSet<Integer>();
      HashMap<Integer, String> symbolName = new HashMap<Integer, String>();
      boolean prevent_merge_on_actions = false;

      String l;
      while ((l = inputStream.readLine()) != null) {
        if (l.startsWith("%")) {  // top-level annotations
          if (l.substring(1).equals("prevent_merge_on_actions")) {
            // this annotations stops the default behavior of treating
            // semantics action symbols as complete, thereby
            // preventing subparser merging after processing actions.
            prevent_merge_on_actions = true;
          }
        } else {  // per-symbol annotations
          String[] a = l.split(" ");
          String name = a[0];
          String type = a[1];
          String parm = a.length > 2 ? a[2] : null;
          int sym = -1;
        
          for (int i = 0; i < parseTables.yytname.length; i++) {
            if (parseTables.yytname[i].equals(name)) {
              sym = i;
              break;
            }
          }
        
          if (sym >= 0) {
            if (type.equals("list")) {
              list.add(sym);
            } else if (type.equals("layout")) {
              layout.add(sym);
            } else if (type.equals("action")) {
              action.put(sym, name);
              complete.add(sym);
            } else if (type.equals("passthrough")) {
              passthrough.add(sym);
            } else if (type.equals("complete")) {
              complete.add(sym);
            } else if (type.equals("void")) {
              voidSymbol.add(sym);
            } else if (type.equals("name")) {
              symbolName.put(sym, parm);
            } else {
              System.err.println("error: node " + name + " has unknown " +
                                 "type " + type);
            }
          } else {
            System.err.println("error: there is no node " + name + " in the " +
                               "grammar");
          }
        }
      }

      // Add support for automatically identifying inline, mid-rule
      // actions.
      for (int sym = 0; sym < parseTables.yytname.length; sym++) {
        String name = parseTables.yytname[sym];
        if (name.startsWith("$@")) {
          action.put(sym, name);
          if (! prevent_merge_on_actions) {
            complete.add(sym);  // all inline action nodes should be
                                // complete lest they prevent merging!
          }
        }
      }

      outputStream.print("" +
"public class " + outClassName + " implements SemanticValues {\n" +
"  private static " + outClassName + " ref;\n" +
"\n" +
"  public static " + outClassName + " getInstance() {\n" +
"    if (ref == null)\n" +
"        ref = new " + outClassName + "();\n" +
"    return ref;\n" +
"  }\n" +
"\n"
                         );


      outputStream.print("" +
"  public Object getValue(int id, String name, Pair<Object> values) {\n" +
"    Object value;\n" +
"\n" +
"    if (values == Pair.<Object>empty()) {\n" +
"      value = GNode.create(name);\n" +
"\n" +
"    } else {\n" +
"      value = GNode.createFromPair(name, values.head(), values.tail());\n" +
"    }\n" +
"\n" +
"    return value;\n" +
"  }\n" +
                         "");

      outputStream.print("" + 
"  public ValueType getValueType(int id) {\n");

      // Find out the ranges [0,frontStreak) and (backStreak,SIZE)
      // where production id is the default NODE types.
      int frontStreak, backStreak;

      for (frontStreak = 0;
           frontStreak < parseTables.yytname.length
             && ! list.contains(frontStreak)
             && ! layout.contains(frontStreak)
             && ! action.containsKey(frontStreak)
             && ! passthrough.contains(frontStreak);
           frontStreak++);

      for (backStreak = parseTables.yytname.length - 1;
           backStreak >= 0
             && ! list.contains(backStreak)
             && ! layout.contains(backStreak)
             && ! action.containsKey(backStreak)
             && ! passthrough.contains(backStreak);
           backStreak--);

      outputStream.print("" +
"    if (0 <= id && id < " + frontStreak);
      if (backStreak < parseTables.yytname.length - 1) {
        outputStream.print("" +
" || " + backStreak + " < id");
      }

      outputStream.print("" +
") {\n" +
"      return ValueType.NODE;\n" +
"    }\n");

      int c; // Used to emit return statement;

      outputStream.print("" +
"    switch (id - " + frontStreak + ") {\n");
      c = 0;
      for (int i = 0; i < parseTables.yytname.length; i++) {
        if (list.contains(i)) {
          outputStream.print("" +
"      case " + (i - frontStreak) + ": // " + parseTables.yytname[i] + " (" + i + ")\n");
          if (c < list.size() - 1) {
          outputStream.print("" +
"        // Fall through\n");
          } else {
          outputStream.print("" +
"        return ValueType.LIST;\n\n");
          }
          c++;
        }
      }

      c = 0;
      for (int i = 0; i < parseTables.yytname.length; i++) {
        if (layout.contains(i)) {
          outputStream.print("" +
"      case " + (i - frontStreak) + ": // " + parseTables.yytname[i] + " (" + i + ")\n");
          if (c < layout.size() - 1) {
          outputStream.print("" +
"        // Fall through\n");
          } else {
          outputStream.print("" +
"        return ValueType.LAYOUT;\n\n");
          }
          c++;
        }
      }

      c = 0;
      for (int i = 0; i < parseTables.yytname.length; i++) {
        if (action.containsKey(i)) {
          outputStream.print("" +
"      case " + (i - frontStreak) + ": // " + parseTables.yytname[i] + " (" + i + ")\n");
          if (c < action.keySet().size() - 1) {
          outputStream.print("" +
"        // Fall through\n");
          } else {
          outputStream.print("" +
"        return ValueType.ACTION;\n\n");
          }
          c++;
        }
      }

      c = 0;
      for (int i = 0; i < parseTables.yytname.length; i++) {
        if (passthrough.contains(i)) {
          outputStream.print("" +
"      case " + (i - frontStreak) + ": // " + parseTables.yytname[i] + " (" + i + ")\n");
          if (c < passthrough.size() - 1) {
            outputStream.print("" +
"        // Fall through\n");
          } else {
            outputStream.print("" +
"        return ValueType.PASS_THROUGH;\n\n");
          }
          c++;
        }
      }

      c = 0;
      for (int i = 0; i < parseTables.yytname.length; i++) {
        if (voidSymbol.contains(i)) {
          outputStream.print("" +
"      case " + (i - frontStreak) + ": // " + parseTables.yytname[i] + " (" + i + ")\n");
          if (c < voidSymbol.size() - 1) {
            outputStream.print("" +
"        // Fall through\n");
          } else {
            outputStream.print("" +
"        return ValueType.VOID;\n\n");
          }
          c++;
        }
      }

      outputStream.print("" +
"      default:\n" +
"        return ValueType.NODE;\n" +
"    }\n" +
"  }\n");

      outputStream.print("" + 
"  public boolean isComplete(int id) {\n" +
"    switch(id) {\n");
      c = 0;
      for (Integer i : complete) {
        outputStream.print("" +
"    case " + i + ": " + "// " + parseTables.yytname[i] + "\n");
        if (c < complete.size() - 1) {
          outputStream.print("" +
"      // Fall through\n");
        } else {
          outputStream.print("" +
"      return true;\n\n"); 
        }
        c++;
      }
      outputStream.print("" +
"    default:\n" +
"      return false;\n" +
"    }\n" +
"  }\n" +
"\n");

      outputStream.print("" + 
"  public boolean changeName(int id) {\n" +
"    switch(id) {\n");
      c = 0;
      for (Integer i : symbolName.keySet()) {
        outputStream.print("" +
"    case " + i + ": " + "// " + parseTables.yytname[i] + "\n");
        if (c < symbolName.size() - 1) {
          outputStream.print("" +
"      // Fall through\n");
        } else {
          outputStream.print("" +
"      return true;\n\n"); 
        }
        c++;
      }
      outputStream.print("" +
"    default:\n" +
"      return false;\n" +
"    }\n" +
"  }\n" +
"\n");

      outputStream.print("" + 
"  public String newName(int id) {\n" +
"    switch(id) {\n");
      c = 0;
      for (Integer i : symbolName.keySet()) {
        outputStream.print("" +
"    case " + i + ": " + "// " + parseTables.yytname[i] + "\n");
        if (c < symbolName.size() - 1) {
          outputStream.print("" +
"      // Fall through\n");
        } else {
          outputStream.print("" +
"      return \"" + symbolName.get(i) + "\";\n\n"); 
        }
        c++;
      }
      outputStream.print("" +
"    default:\n" +
"      return null;\n" +
"    }\n" +
"  }\n" +
"\n");

      outputStream.print("" + 
"\n" +
"}\n");

    } catch (Exception e) {
      e.printStackTrace();

    } finally {

      if (inputStream != null) {
          inputStream.close();
      }

      if (outputStream != null) {
          outputStream.close();
      }
    }
    
  }
}
