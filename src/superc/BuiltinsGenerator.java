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
import java.io.*;

/**
 * This class generates <code>Builtins</code> which stores the
 * built-in macros and system directories of the current system.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.11 $
 */
public class BuiltinsGenerator {
  public static void main(String args[]) throws Exception {
    BufferedReader inputStream = null;
    PrintWriter outputStream = null;
    
    if (args.length < 2) {
      System.err.println("USAGE: sysdirs builtins");
      System.exit(-1);
    }

    try {
      String l;
      String delim;
      boolean flag;

      outputStream = new PrintWriter(new FileWriter("Builtins.java"));
      
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
"/** This class's purpose is to provide the built-in macros and system includes.\n" +
"  */\n" +
"public class Builtins {\n" +
"  /** The system include directories */\n"
      );

      inputStream = new BufferedReader(new FileReader(args[0]));  //read sysdirs

      flag = false;
      delim = "";
      outputStream.print("  public static String[] sysdirs = { ");
      while ((l = inputStream.readLine()) != null) {
        if (l.equals("End of search list.")) {
          flag = false;
        }
        if (flag) {
          l = l.trim();
          l = l.split(" ", 2)[0];
          outputStream.print(delim + "\"" + l + "\"");
          delim = ", ";
        }
        if (l.equals("#include <...> search starts here:")) {
          flag = true;
        }
      }
      outputStream.print(" };\n");
      outputStream.print("\n");
      
      outputStream.print("" +
"  /** A string containing the built-in macro definitions */\n" + 
"  public static final String builtin =\n");

      inputStream = new BufferedReader(new FileReader(args[1]));  //read sysdirs
      while ((l = inputStream.readLine()) != null) {
          outputStream.print("    \"" + l.replaceAll("\"", "\\\\\"") + "\\n\" +\n");
      }
      outputStream.print("" + 
"    \"\";\n" +
"    public static void main(String[] args) {\n" +
"      System.out.println(builtin);\n" +
"    }\n" +
"}\n");

    }
    catch (Exception e) {
      e.printStackTrace();
    }
    finally {
      if (inputStream != null) {
          inputStream.close();
      }
      if (outputStream != null) {
          outputStream.close();
      }
    }
    
  }
}
