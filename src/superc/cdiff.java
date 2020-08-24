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

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;

import java.util.Iterator;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.Language;

/**
 * Token-based diff.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.31 $
 */
public class cdiff {
  /** The error code for when the input files are different. */
  public static final int DIFFERENT = 1;

  /** The error code for invalid arguments. */
  public static final int INVALID_ARGUMENTS = 2;

  /** The error code for invalid option flag. */
  public static final int INVALID_FLAG = 3;

  /**
   * Print cdiff usage info.
   */
  public static void printUsage() {
    System.err.println(
"cdiff - Compare two C files token-by-token, ignoring directives by default." +
"\n" +
"\n" +
"USAGE:\n" +
"\n" +
"  java xtc.lang.cpp.cdiff -?\n" +
"\n" +
"  java xtc.lang.cpp.cdiff [-l|-d] [-s] [-e #] file1 file2\n" +
"\n" +
"FLAGS:\n" +
"  -l\tTreat directives as individual tokens.\n" +
"  -d\tParse directives and compare them.\n" +
"  -s\tIgnore whitespace inside of string literals.\n" +
"  -e n\tExpect n errors.\n" +
"  -?\tPrint this help message.\n" +
"\n" +
"EXIT CODES:\n" +
"  0   No difference\n" +
"  " + DIFFERENT + "   Different\n" +
"  " + INVALID_ARGUMENTS + "   Invalid arguments\n" +
"  " + INVALID_FLAG + "   Invalid flag\n" +
"  *   Non-cdiff system exit code\n" +
"");
  }

  /**
   * Signal an error.  This method terminates cdiff.
   *
   * @param errcode The error code.
   */
  public static void error(int errcode) {
    switch (errcode) {
    case DIFFERENT:
      System.err.println("error: the files are different.");
      break;

    case INVALID_ARGUMENTS:
      System.err.println("error: the arguments are invalid.");
      break;

    case INVALID_FLAG:
      System.err.println("error: the flag is invalid.");
      break;

    default:
      System.err.println("error: unknown error");
      break;
    }

    System.exit(errcode);
  }

  // get around capture of ? to CTag warning
  /**
   * Determine whether two files' tokens differ.  Each file is lexed
   * into C tokens and compared token-by-token, ignoring whitespace.
   * If the files are the same, the exit code is 0.  If they differ,
   * the location in each file of the first difference is emitted and
   * the return code is 1.
   */
  public static void main(String[] args) {
    String filename1 = null;
    String filename2 = null;

    // Whether directives should be compare token-by-token.
    boolean pureLexer = false;

    // Whether directives should be parsed first, then compared.
    boolean directives = false;

    // Whether whitespace in string literals should be ignored.
    boolean ignoreStringWhitespace = false;

    // How many errors to allow before terminating.
    int expect = 0;

    if (args.length == 0 || args.length == 1 && args[0].equals("-?")) {
      printUsage();
      // Don't display error message because displaying usage with
      // zero arguments is customary.  Still set the right error code
      // though to avoid falsely reporting equality.
      System.exit(INVALID_ARGUMENTS);
    }

    if (args.length < 2 || args.length > 6) {
      error(INVALID_ARGUMENTS);
    }

    // Gather command-line arguments.
    int i;
    for (i = 0; i < args.length - 2; i++) {
      String flag = args[i];

      if (flag.length() == 0 || flag.length() > 2 || flag.charAt(0) != '-') {
        error(INVALID_FLAG);

      } else if (flag.charAt(1) == 'l') {
        if (pureLexer || directives) error(INVALID_ARGUMENTS);

        pureLexer = true;

      } else if (flag.charAt(1) == 'd') {
        if (pureLexer || directives) error(INVALID_ARGUMENTS);
        
        directives = true;

      } else if (flag.charAt(1) == 's') {
        ignoreStringWhitespace = true;

      } else if (flag.charAt(1) == 'e') {
        if ((i+1) >= (args.length - 2)) {
          error(INVALID_FLAG);
        }
        try {
          expect = Integer.parseInt(args[i+1]);
          if (expect < -1) {
            error(INVALID_FLAG);
          }
          i++;
        } catch (Exception e) {
          error(INVALID_FLAG);
        }

      } else {
        error(INVALID_FLAG);
      }
    }

    filename1 = args[i];
    filename2 = args[i + 1];

    try {
      File file1 = new File(filename1);
      File file2 = new File(filename2);

      BufferedReader reader1 = new BufferedReader(new FileReader(file1));
      BufferedReader reader2 = new BufferedReader(new FileReader(file2));

      final CLexer clexer1 = new CLexer(reader1);
      clexer1.setFileName(filename1);
      Iterator<Syntax> stream1 = new Iterator<Syntax>() {
          Syntax syntax;
    
          public Syntax next() {
            try {
              syntax = clexer1.yylex();
            } catch (java.io.IOException e) {
              e.printStackTrace();
              throw new RuntimeException();
            }
            return syntax;
          }
    
          public boolean hasNext() {
            return syntax.kind() != Kind.EOF;
          }

          public void remove() {
            throw new UnsupportedOperationException();
          }
        };

      final CLexer clexer2 = new CLexer(reader2);
      clexer2.setFileName(filename2);
      Iterator<Syntax> stream2 = new Iterator<Syntax>() {
          Syntax syntax;
    
          public Syntax next() {
            try {
              syntax = clexer2.yylex();
            } catch (java.io.IOException e) {
              e.printStackTrace();
              throw new RuntimeException();
            }
            return syntax;
          }
    
          public boolean hasNext() {
            return syntax.kind() != Kind.EOF;
          }

          public void remove() {
            throw new UnsupportedOperationException();
          }
        };

      boolean end1 = false;
      boolean end2 = false;
      Syntax syntax1 = null;
      Syntax syntax2 = null;

      if ( ! pureLexer) {
        stream1 = new DirectiveParser(stream1, filename1);
        stream2 = new DirectiveParser(stream2, filename2);
      }
      
      while (true) {
        do {
          syntax1 = stream1.next();
        } while (null == syntax1 || syntax1.kind() != Kind.LANGUAGE
                 && syntax1.kind() != Kind.EOF
                 && (! directives || syntax1.kind() != Kind.DIRECTIVE));
        
        do {
          syntax2 = stream2.next();
        } while (null == syntax2 || syntax2.kind() != Kind.LANGUAGE
                 && syntax2.kind() != Kind.EOF
                 && (! directives || syntax2.kind() != Kind.DIRECTIVE));
        
        end1 = syntax1.kind() == Kind.EOF;
        end2 = syntax2.kind() == Kind.EOF;

        if (end1 || end2) {
          if (!end1 || !end2) {
            System.out.println(syntax1.getLocation());
            System.out.println(syntax1);
            System.out.println();
            System.out.println(syntax2.getLocation());
            System.out.println(syntax2);
            if (0 == expect && -1 != expect) {
              System.exit(DIFFERENT);
            } else {
              expect--;
            }
          }
          break;
        } else {
          @SuppressWarnings("unchecked")
            Language<CTag> lang1 = (Language<CTag>)syntax1;
          @SuppressWarnings("unchecked")
            Language<CTag> lang2 = (Language<CTag>)syntax2;
          if (ignoreStringWhitespace
              && syntax1.kind() == Kind.LANGUAGE
              && syntax2.kind() == Kind.LANGUAGE
              && lang1.toLanguage().tag() == CTag.STRINGliteral
              && lang2.toLanguage().tag() == CTag.STRINGliteral
              && syntax1.getTokenText().replaceAll(" ", "")
              .equals(syntax2.getTokenText().replaceAll(" ", ""))) {
            // Don't take into account whitespace when comparing
            // strings.

          } else if (! syntax1.getTokenText().equals(syntax2.getTokenText())) {
            System.out.println(syntax1.getLocation());
            System.out.println(syntax1);
            System.out.println();
            System.out.println(syntax2.getLocation());
            System.out.println(syntax2);
            if (0 == expect && -1 != expect) {
              System.exit(DIFFERENT);
            } else {
              expect--;
            }
          }
        }
      }
      
      System.exit(0);

    } catch (Exception e) {
      e.printStackTrace();
      System.exit(-1);
    }
  }
}
