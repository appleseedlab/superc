/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004-2007, 2011 Robert Grimm
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
package xtc.lang;

import java.lang.reflect.Method;

import java.io.File;
import java.io.IOException;
import java.io.Reader;

import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.tree.ParseTreePrinter;
import xtc.tree.ParseTreeStripper;
import xtc.tree.Printer;

import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.Tool;

import xtc.parser.Result;
import xtc.parser.ParseException;

/**
 * The Java tool.
 *
 * @author Robert Grimm
 * @version $Revision: 1.40 $
 */
public class Java extends Tool {

  /** The method for printing the memoization table's profile. */
  protected Method profile;

  /** The method for printing the parser's memoization table. */
  protected Method dump;

  /** Create a new Java tool. */
  public Java() {
    /* Nothing to do. */
  }

  public String getName() {
    return "xtc Java Tool";
  }

  public String getCopy() {
    return "(C) 2004-2007, 2011 IBM, Robert Grimm, and NYU";
  }

  public String getExplanation() {
    return
      "By default, this tool simply parses Java sources using the Rats!-" +
      "generated recognizer.  If the ast option is specified, it also " +
      "generates an AST, which can then be further processed and printed.  " +
      "If the pt option is specified, it also embeds all formatting in " +
      "the resulting AST.";
  }

  public void init() {
    super.init();
    runtime.
      bool("memoProfile", "printMemoProfile", false,
           "Print profile of parser's memoization table.").
      bool("memoTable", "printMemoTable", false,
           "Print parser's memoization table.").
      bool("java5", "optionJava5", false,
           "Process Java 5.").
      bool("java7", "optionJava7", false,
           "Process Java 7.").
      bool("ast", "optionAST", false,
           "Use parser that builds abstract syntax tree.").
      bool("parsetree", "optionParseTree", false,
           "Use parser that builds parse tree.").
      bool("strip", "optionStrip", false,
           "Strip any annotations from the AST before printing.").
      bool("simplifyAST", "optionSimplifyAST", false,
           "Simplify the AST.").
      bool("printAST", "printAST", false,
           "Print the AST in generic form.").
      bool("locateAST", "optionLocateAST", false,
           "Include location information when printing the AST in " + 
           "generic form.").
      bool("printSource", "printSource", false,
           "Print the AST in Java source form.").
      bool("analyze", "optionAnalyze", false,
           "Analyze the program's AST.").
      bool("printSymbolTable", "printSymbolTable", false,
           "Print the program's symbol table.").
      bool("g", "debug", false,
           "Ignored; provided for compatibility with jacks.").
      bool("deprecated", "deprecated", false,
           "Ignored; provided for compatibility with jacks.");
  }

  public void prepare() {
    super.prepare();
    if (runtime.test("printMemoProfile")) {
      // Ensure the parser has a profile(Printer) method.
      Class<?> klass;
      String name;
      if (runtime.test("optionAST")) {
        klass = JavaParser.class;
        name  = "Java parser";
      } else if (runtime.test("optionParseTree")) {
        klass = JavaReader.class;
        name  = "Java reader";
      } else {
        klass = JavaRecognizer.class;
        name  = "Java recognizer";
      }
      try {
        profile = klass.getMethod("profile", Printer.class);
      } catch (NoSuchMethodException x) {
        runtime.error(name + " generated without profile attribute");
      } catch (SecurityException x) {
        runtime.error("unable to access " + name + "'s profile() method");
      }
    }
    if (runtime.test("printMemoTable")) {
      // Ensure the parser has a dump(Printer) method.
      Class<?> klass;
      String name;
      if (runtime.test("optionAST")) {
        klass = JavaParser.class;
        name  = "Java parser";
      } else if (runtime.test("optionParseTree")) {
        klass = JavaReader.class;
        name  = "Java reader";
      } else {
        klass = JavaRecognizer.class;
        name  = "Java recognizer";
      }
      try {
        dump = klass.getMethod("dump", Printer.class);
      } catch (NoSuchMethodException x) {
        runtime.error(name + " generated without dump attribute");
      } catch (SecurityException x) {
        runtime.error("unable to access " + name + "'s dump() method");
      }
    }
    if (runtime.test("optionJava7")) {
      if (runtime.test("optionJava5")) {
        runtime.error("java5 and java7 options are mutually exclusive");
      }
      if ((! runtime.test("optionAST")) && (! runtime.test("optionParseTree"))) {
        runtime.error("java7 option requires ast or parseTree option");
      }
    }
    if (runtime.test("optionJava5")) {
      if ((! runtime.test("optionAST")) && (! runtime.test("optionParseTree"))) {
        runtime.error("java5 option requires ast or parseTree option");
      }
    }
    if (runtime.test("optionStrip") ||
        runtime.test("optionSimplifyAST") ||
        runtime.test("printAST") ||
        runtime.test("printSource")) {
      if ((! runtime.test("optionAST")) && (! runtime.test("optionParseTree"))) {
        runtime.error("processing of AST requires ast or pt option");
      }
    }
    if (runtime.test("optionLocateAST")) {
      if (! runtime.test("printAST")) {
        runtime.error("locateAST option requires printAST option");
      }
    }
    if (runtime.test("optionAnalyze") && !runtime.test("optionSimplifyAST"))
      runtime.error("type checker only works on simplified AST;" + 
          "run with -ast -simplifyAST -analyze");
  }

  public File locate(String name) throws IOException {
    File file = super.locate(name);
    if (Integer.MAX_VALUE < file.length()) {
      throw new IllegalArgumentException(file + ": file too large");
    }
    return file;
  }

  public Node parse(Reader in, File file) throws IOException, ParseException {
    if (runtime.test("optionJava7") && runtime.test("optionParseTree")) {
      JavaSevenReader parser =
        new JavaSevenReader(in, file.toString(), (int)file.length());
      Result         result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else if (runtime.test("optionJava7") && runtime.test("optionAST")) {
      JavaSevenParser parser =
        new JavaSevenParser(in, file.toString(), (int)file.length());
      Result         result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else if (runtime.test("optionJava5") && runtime.test("optionParseTree")) {
      JavaFiveReader parser =
        new JavaFiveReader(in, file.toString(), (int)file.length());
      Result         result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else if (runtime.test("optionJava5") && runtime.test("optionAST")) {
      JavaFiveParser parser =
        new JavaFiveParser(in, file.toString(), (int)file.length());
      Result         result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else if (runtime.test("optionParseTree")) {
      JavaReader parser =
        new JavaReader(in, file.toString(), (int)file.length());
      Result     result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else if (runtime.test("optionAST")) {
      JavaParser parser =
        new JavaParser(in, file.toString(), (int)file.length());
      Result     result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
      
    } else {
      JavaRecognizer parser =
        new JavaRecognizer(in, file.toString(), (int)file.length());
      Result         result = parser.pCompilationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);
    }
  }

  /**
   * Print the specified parser's memoization profile and table.
   *
   * @param parser The parser.
   * @param file The file.
   */
  private void printMemoInfo(Object parser, File file) {
    if (runtime.test("printMemoProfile")) {
      try {
        profile.invoke(parser, new Object[] { runtime.console() });
      } catch (Exception x) {
        runtime.error(file + ": " + x.getMessage());
      }
      runtime.console().flush();
    }
    
    if (runtime.test("printMemoTable")) {
      try {
        dump.invoke(parser, new Object[] { runtime.console() });
      } catch (Exception x) {
        runtime.error(file + ": " + x.getMessage());
      }
      runtime.console().flush();
    }
  }

  public void process(Node node) {
    // Simplify the AST.
    if (runtime.test("optionSimplifyAST")) {
      node = (Node)new JavaAstSimplifier().dispatch(node);
    }

    if (runtime.test("optionAnalyze")) {
      // Make sure the classpath is set.
      if (!runtime.hasValue(Runtime.INPUT_DIRECTORY))
        runtime.setValue(Runtime.INPUT_DIRECTORY,
                         new File(System.getProperty("user.dir")));

      // Perform type checking.
      final SymbolTable table = new SymbolTable();
      new JavaAnalyzer(runtime, table).dispatch(node);

      // Print the symbol table.
      if (runtime.test("printSymbolTable")) {
        final Visitor visitor = runtime.console().visitor();
        try {
          table.root().dump(runtime.console());
        } finally {
          runtime.console().register(visitor);
        }
        runtime.console().flush();
      }
    }

    // Strip the AST.
    if (runtime.test("optionStrip")) {
      node = (Node)new ParseTreeStripper().dispatch(node);
    }

    // Print the AST.
    if (runtime.test("printAST")) {
      runtime.console().format(node, runtime.test("optionLocateAST")).pln().
        flush();
    }

    // Print the source.
    if (runtime.test("printSource")) {
      if (runtime.test("optionParseTree") && (! runtime.test("optionStrip"))) {
        new ParseTreePrinter(runtime.console()).dispatch(node);
      } else {
        new JavaPrinter(runtime.console()).dispatch(node);
      }
      runtime.console().flush();
    }
  }

  /**
   * Run the tool with the specified command line arguments.
   *
   * @param args The command line arguments.
   */
  public static void main(String[] args) {
    new Java().run(args);
  }

}
