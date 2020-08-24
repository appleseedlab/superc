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

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;

import java.util.HashSet;
import java.util.HashMap;

/**
 * This class generates a base class for semantic actions for a
 * grammar.  It takes "name, type" pairs from the standard input.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.11 $
 */
public class GenerateActionsClass {
  public static void main(String args[]) throws Exception {
    BufferedReader inputStream = null;
    PrintWriter outputStream = null;

    if (args.length < 2) {
      System.err.println("USAGE: GenerateValuesClass outClassName"
                         + " parseTablesClassName [all]");
      System.err.println("\n" +
"This will create an abstract java class with methods for each action" +
"annotation.  Specifying \"all\" will create a java class with empty" +
"methods for every production, regardless of annotation.");
      System.exit(1);
    }

    String outClassName = args[0];
    String parseTablesClassName = args[1];
    String actionSwitchFile = args.length > 2 ? args[2] : null;
    String prologueFile = args.length > 3 ? args[3] : null;
    String epilogueFile = args.length > 4 ? args[4] : null;
    ParseTables parseTables
      = (ParseTables) Class.forName(parseTablesClassName).newInstance();
    
    try {
      String l;
      HashMap<Integer, String> action;

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
"\n");

      if (null != prologueFile) {
        inputStream = new BufferedReader(new FileReader(prologueFile));

        outputStream.println("/* from " + prologueFile + " */");

        while ((l = inputStream.readLine()) != null) {
          outputStream.println(l);
        }
      }

      outputStream.print("" +
"\n" +  
"/**\n" +
" * This class is generated from grammar annotations and provides semantic\n" +
" * action support.\n" +
" */\n"
                         );
      action = new HashMap<Integer, String>();
      inputStream = new BufferedReader(new InputStreamReader(System.in));

      while ((l = inputStream.readLine()) != null) {
        if (l.startsWith("%")) {  // top-level annotations
          // no top-level annotations affect action generation
        } else {  // per-symbol annotations
          String[] a = l.split(" ");
          String name = a[0];
          String type = a[1];
          int sym = -1;

          for (int i = 0; i < parseTables.yytname.length; i++) {
            if (parseTables.yytname[i].equals(name)) {
              sym = i;
              break;
            }
          }

          if (sym >= 0) {
            if (type.equals("action")) {
              action.put(sym, name);
            }
          } else {
            System.err.println("error: there is no node " + name + " in the " +
                               "grammar");
          }
        }
      }

      outputStream.print("" +
"public class " + outClassName + " implements SemanticActions {\n" +
"\n" +
"  /** The instance of this class */\n" +
"  private static " + outClassName + " ref;\n" +
"\n" +
"  /** Get the instance of this class */\n" +
"  public static " + outClassName + " getInstance() {\n" +
"    if (null == ref) {\n" +
"      ref = new " + outClassName + "();\n" +
"    }\n" +
"    return ref;\n" +
"  }\n" +
"\n");

      outputStream.print("" + 
"  public Object action(int production, Subparser subparser, Object value) {\n");

      if (null != actionSwitchFile) {
        inputStream = new BufferedReader(new FileReader(actionSwitchFile));

        outputStream.print("" +
"    switch (production) {\n");
        while ((l = inputStream.readLine()) != null) {
          outputStream.println(l);
        }
        outputStream.print("" +
"    }\n" +
"  return value;\n");
      } else {
        outputStream.print("return null;\n");
      }

      outputStream.print("" +
"  }\n");


      if (action.size() > 0) {
        outputStream.print("" + 
"  public void dispatch(int id, Subparser subparser) {\n" +
"    switch(id) {\n");
        for (Integer i : action.keySet()) {
          String name = action.get(i);
        
          outputStream.print("" +
"    case " + i + ":\n" +
"      " + name + "(subparser);\n" +
"      break;\n\n"); 
        }
        outputStream.print("" +
"    default:\n" +
"      // Do nothing\n" +
"      break;\n" +
"    }\n" +
"  }\n" +
"\n");
      } else {
        outputStream.print("" +
"  public void dispatch(int id, Subparser subparser) {\n" +
"    // no action productions\n" +
"  }\n"
                           );
      }

      if (null != epilogueFile) {
        inputStream = new BufferedReader(new FileReader(epilogueFile));

        outputStream.println("  /* from " + epilogueFile + " */");

        while ((l = inputStream.readLine()) != null) {
          outputStream.println(l);
        }
      }


      outputStream.print("" + 
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
