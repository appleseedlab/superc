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

import java.io.FileWriter;
import java.io.BufferedWriter;

import java.util.HashSet;

/**
 * This tool captures gcc command-line arguments for use by SuperC.
 * It only captures arguments related to header paths, macro
 * (un)definitions, and the filename.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.6 $
 */
public class GCCShunt {
  /**
   * Determines whether a macro definition should be included when
   * doing configuration-preserving preprocessing.  Some Kbuild macros
   * need to be defined for SuperC in for use in stringification.
   *
   * @param The name of the macro defintion.
   * @param true if the macro definition is part of the Kbuild macros.
   */
  static boolean isKbuildName(String definition) {
    return definition.startsWith("KBUILD_STR")
      || definition.startsWith("KBUILD_BASENAME")
      || definition.startsWith("KBUILD_MODNAME");
  }

  public static void main(String args[]) {
    if (args.length < 1) {
      System.err.println(
"USAGE: java GCCShunt [options] gcc-options file\n" +
"\n" +
"Intercept gcc command-line arguments for header paths and macro\n" +
"(un)definitions.\n" +
"\n" +
"\n" +
"OPTIONS\n" +
"  --shunt-filename file\n" +
"\n" +
"      Verify that the filename passed with gcc flags is the right one.\n" +
"      If the filenames don't match, do nothing.\n" +
"\n" +
"  --shunt-verbose\n" +
"\n" +
"      Verbose error message mode.\n" +
"\n" +
"  --shunt-config filename\n" +
"\n" +
"      Write the configuration-related arguments to a given file.\n" +
"\n" +
"  --shunt-superc filename\n" +
"\n" +
"      Write only the path-related arguments to a given file.\n" +
"\n" +
"  --shunt-kbuild\n" +
"\n" +
"      Include the kbuild-related arguments, Write only the path-related arguments to a given file.\n" +
"\n" +
"  --emit-exceptions\n" +
"\n" +
"      Emit defines and undefines as a list in -configureExceptions.\n" +
"\n" +
// "ERROR CODES\n" +
// "  1 - no arguments given\n" +
// "  2 - no gcc filename was given\n" +
// "  3 - gcc filename doesn't match --shunt-filename\n" +
// "  4 - could not write file\n" +
"");
      System.exit(0);  // System.exit(1);
    }

    String configs = "";
    String superc = "";
    boolean KBUILD = false;
    boolean INTENDED_FILENAME = false;
    String intendedFilename = null;
    boolean VERBOSE = false;
    String configsFile = null;
    String supercFile = null;
    boolean EMIT_EXCEPTIONS = false;
    String exceptions = "";

    boolean nostdinc = false;
    for (int i = 0; i < args.length; i++) {
      String arg = args[i];
      if (arg.equals("-nostdinc")) {
        if (! nostdinc) {
          // Linux build puts -nostdinc twice which causes xtc's
          // command-line collector to fail.
          superc += " " + arg;
          nostdinc = true;
        }
      } else if (arg.equals("-I")
          || arg.equals("-isystem")
          || arg.equals("-iquote")) {
        if (i > args.length - 3) {
          System.err.println("(shunt) no filename was given.");
          System.exit(0);  // System.exit(2);
        }
        String header = " " + arg + " " + args[i+1];
        superc += header;
        configs += header;
        i++;

      } else if (arg.startsWith("-I")) {
        // Single-letter arguments need no space.
        String header = " " + arg.substring(0, 2) + " " + arg.substring(2);
        superc += header;
        configs += header;

      } else if (arg.equals("-D")
                 || arg.equals("-U")
                 || arg.equals("-include")) {
        if (i > args.length - 3) {
          System.err.println("(shunt) no filename was given.");
          System.exit(0);  // System.exit(2);
        }
        configs += " " + arg + " " + args[i+1];
        if (KBUILD && isKbuildName(args[i+1])) {
          superc += " " + arg + " " + args[i+1];
        }
        if (EMIT_EXCEPTIONS) {
          String config_string = args[i+1];
          // String config_string = arg.substring(0, 2);
          String[] config_split = config_string.split("=");
          String config_var = config_split[0];
          String config_def = config_split.length > 1 ? config_split[1] : null;
          String exception = "";

          if (arg.equals("-D")) {
            exception = config_var + "="
              + ((config_def != null) ? config_def : "y");
          } else if (arg.equals("-U")) {
            exception = "# " + config_var + " is not set";
          }
          exceptions += exception + ",";
        }
        i++;

      } else if (arg.startsWith("-D")
                 || arg.startsWith("-U")) {
        // Single-letter arguments need no space.
        configs += " " + arg.substring(0, 2) + " " + arg.substring(2);
        if (KBUILD && isKbuildName(arg.substring(2))) {
          superc += " " + arg.substring(0, 2) + " " + arg.substring(2);
        }
        if (EMIT_EXCEPTIONS) {
        }

      } else if (arg.equals("--shunt-filename")) {
        INTENDED_FILENAME = true;
        intendedFilename = args[i+1];
      } else if (arg.equals("--shunt-verbose")) {
        VERBOSE = true;
      } else if (arg.equals("--shunt-config")) {
        configsFile = args[i+1];
      } else if (arg.equals("--shunt-superc")) {
        supercFile = args[i+1];
      } else if (arg.equals("--shunt-kbuild")) {
        KBUILD = true;
      } else if (arg.equals("--emit-exceptions")) {
        EMIT_EXCEPTIONS = true;
      }
    }

    if (INTENDED_FILENAME) {
      String filename = args[args.length - 1];
      if (! filename.equals(intendedFilename)) {
        if (VERBOSE) {
          System.err.println("(shunt) filename doesn't match: " + filename);
        }
        System.exit(0);  // System.exit(3);
      }
    }

    if (null != supercFile) {
      try {
        FileWriter fstream = new FileWriter(supercFile);
        BufferedWriter out = new BufferedWriter(fstream);
        out.write(superc);
        out.close();
      } catch (Exception e) {
        System.err.println("(shunt) " + e.getMessage());
        System.exit(0);  // System.exit(4);
      }
    }

    if (VERBOSE) {
      System.out.println(superc);
    }

    if (null != configsFile) {
      try {
        FileWriter fstream = new FileWriter(configsFile);
        BufferedWriter out = new BufferedWriter(fstream);
        out.write(configs);
        out.close();
      } catch (Exception e) {
        System.err.println("(shunt) " + e.getMessage());
        System.exit(0);  // System.exit(4);
      }      
    }

    if (VERBOSE) {
      System.out.println(configs);
    }

    if (EMIT_EXCEPTIONS) {
      System.out.println(exceptions);
    }
  }
}
