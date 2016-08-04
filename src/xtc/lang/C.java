/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004-2011 Robert Grimm
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

import xtc.Constants;
import xtc.Limits;

import xtc.tree.Formatting;
import xtc.tree.GNode;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.ParseTreePrinter;
import xtc.tree.ParseTreeStripper;
import xtc.tree.Printer;
import xtc.tree.Visitor;

import xtc.type.CFactory;
import xtc.type.TypePrinter;

import xtc.util.SymbolTable;
import xtc.util.Tool;

import xtc.parser.Result;
import xtc.parser.ParseException;

/**
 * The C tool.
 *
 * @author Robert Grimm
 * @version $Revision: 1.68 $
 */
public class C extends Tool {

  /** The method for printing the memoization table's profile. */
  protected Method profile;

  /** The method for printing the parser's memoization table. */
  protected Method dump;

  /** Create a new C tool. */
  public C() {
    /* Nothing to do. */
  }

  public String getName() {
    return "xtc C Tool";
  }

  public String getCopy() {
    return Constants.COPY;
  }

  public void init() {
    super.init();
    runtime.
      bool("parsetree", "optionParseTree", false,
           "Generate a parse tree.").
      bool("noincr", "optionNoIncr", false,
           "Do not parse incrementally.").
      bool("memoProfile", "printMemoProfile", false,
           "Print profile of parser's memoization table.").
      bool("memoTable", "printMemoTable", false,
           "Print parser's memoization table.").
      bool("analyze", "optionAnalyze", false,
           "Analyze the program's AST.").
      bool("pedantic", "optionPedantic", false,
           "Enforce strict C99 compliance.").
      bool("builtins", "optionBuiltIns", false,
           "Declare C built-ins before analysis.").
      bool("markAST", "optionMarkAST", false,
           "Mark AST nodes with types.").
      bool("printFeatures", "printFeatures", false,
           "Extract and print the program's features.").
      bool("printStats", "printASTStats", false,
           "Collect and print the program's AST statistics.").
      bool("printSymbolTable", "printSymbolTable", false,
           "Print the program's symbol table.").
      bool("strip", "optionStrip", false,
           "Strip any annotations before printing the AST.").
      bool("printAST", "printAST", false,
           "Print the program's AST in generic form.").
      bool("locateAST", "optionLocateAST", false,
           "Include location information when printing the AST in " + 
           "generic form.").
      bool("printSource", "printSource", false,
           "Print the program's AST in C source form.").
      bool("preserveLines", "preserveLines", false,
           "Preserve line spacing when printing C source.").
      bool("formatGNU", "formatGNU", false,
           "Use GNU source formatting guidelines.");
  }

  public void prepare() {
    super.prepare();
    if (runtime.test("printMemoProfile")) {
      // Ensure the parser has a profile(Printer) method.
      Class<?> klass =
        runtime.test("optionParseTree") ? CReader.class : CParser.class;
      String   name =
        runtime.test("optionParseTree") ? "C reader" : "C parser";
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
      Class<?> klass =
        runtime.test("optionParseTree") ? CReader.class : CParser.class;
      String   name =
        runtime.test("optionParseTree") ? "C reader" : "C parser";
      try {
        dump = klass.getMethod("dump", Printer.class);
      } catch (NoSuchMethodException x) {
        runtime.error(name + " generated without dump attribute");
      } catch (SecurityException x) {
        runtime.error("unable to access " + name + "'s dump() method");
      }
    }
    if (runtime.test("optionPedantic")) {
      if (! runtime.test("optionAnalyze")) {
        runtime.error("pedantic option requires analyze option");
      }
    }
    if (runtime.test("optionBuiltIns")) {
      if (! runtime.test("optionAnalyze")) {
        runtime.error("builtins option requires analyze option");
      }
    }
    if (runtime.test("optionMarkAST"))  {
      if (! runtime.test("optionAnalyze")) {
        runtime.error("markAST option requires analyze option");
      }
    }
    if (runtime.test("printSymbolTable")) {
      if (! runtime.test("optionAnalyze")) {
        runtime.error("printSymbolTable option requires analyze option");
      }
    }
    if (runtime.test("printFeatures")) {
      if (! runtime.test("optionAnalyze")) {
        runtime.error("printFeatures option requires analyze option");
      }
      if (! runtime.test("optionMarkAST")) {
        runtime.error("printFeatures option requires markAST option");
      }
    }
    if (runtime.test("optionLocateAST")) {
      if (! runtime.test("printAST")) {
        runtime.error("locateAST option requires printAST option");
      }
    }
    if (runtime.test("preserveLines")) {
      if (! runtime.test("printSource")) {
        runtime.error("preserveLines option requires printSource option");
      }
    }
    if (runtime.test("formatGNU")) {
      if (! runtime.test("printSource")) {
        runtime.error("formatGNU option requires printSource option");
      }
    }
  }

  public void diagnose() {
    runtime.console().pln();

    runtime.console().p("os        : ").pln(Limits.OS);
    runtime.console().p("arch      : ").pln(Limits.ARCH);
    runtime.console().p("elf       : ");
    if (Limits.IS_ELF) {
      runtime.console().pln("true");
    } else {
      runtime.console().pln("false");
    }
    runtime.console().p("compiler  : ").p(Limits.COMPILER_NAME).p(' ').
      pln(Limits.COMPILER_VERSION);
    runtime.console().p("endian    : ");
    if (Limits.IS_BIG_ENDIAN) {
      runtime.console().pln("big");
    } else {
      runtime.console().pln("little");
    }
    runtime.console().p("size_t    : ").pln(xtc.type.C.SIZEOF.toString());
    runtime.console().p("ptrdiff_t : ").pln(xtc.type.C.PTR_DIFF.toString());
    runtime.console().p("wchar_t   : ").pln(xtc.type.C.WCHAR.toString());
    runtime.console().p("char      : ");
    if (Limits.IS_CHAR_SIGNED) {
      runtime.console().pln("signed");
    } else {
      runtime.console().pln("unsigned");
    }
    runtime.console().p("literal   : ");
    if (Limits.IS_STRING_CONST) {
      runtime.console().pln("const char *");
    } else {
      runtime.console().pln("char *");
    }
    runtime.console().p("int       : ");
    if (Limits.IS_INT_SIGNED) {
      runtime.console().pln("signed in bitfields");
    } else {
      runtime.console().pln("unsigned in bitfields");
    }
    runtime.console().pln();

    runtime.console().
      pln("type      |  b |  c |  s |  i |  l | ll |  f |  d | ld |  p");
    runtime.console().
      pln("----------+----+----+----+----+----+----+----+----+----+----");
    runtime.console().
      p("size      | ").
      pad(Limits.BOOL_SIZE, 2).p(" |  1 | ").
      pad(Limits.SHORT_SIZE, 2).p(" | ").
      pad(Limits.INT_SIZE, 2).p(" | ").
      pad(Limits.LONG_SIZE, 2).p(" | ").
      pad(Limits.LONG_LONG_SIZE, 2).p(" | ").
      pad(Limits.FLOAT_SIZE, 2).p(" | ").
      pad(Limits.DOUBLE_SIZE, 2).p(" | ").
      pad(Limits.LONG_DOUBLE_SIZE, 2).p(" | ").
      pad(Limits.POINTER_SIZE, 2).pln();
    runtime.console().
      p("align     | ").
      pad(Limits.BOOL_ALIGN, 2).p(" |  1 | ").
      pad(Limits.SHORT_ALIGN, 2).p(" | ").
      pad(Limits.INT_ALIGN, 2).p(" | ").
      pad(Limits.LONG_ALIGN, 2).p(" | ").
      pad(Limits.LONG_LONG_ALIGN, 2).p(" | ").
      pad(Limits.FLOAT_ALIGN, 2).p(" | ").
      pad(Limits.DOUBLE_ALIGN, 2).p(" | ").
      pad(Limits.LONG_DOUBLE_ALIGN, 2).p(" | ").
      pad(Limits.POINTER_ALIGN, 2).pln();
    runtime.console().
      p("nat align | ").
      pad(Limits.BOOL_NAT_ALIGN, 2).p(" |  1 | ").
      pad(Limits.SHORT_NAT_ALIGN, 2).p(" | ").
      pad(Limits.INT_NAT_ALIGN, 2).p(" | ").
      pad(Limits.LONG_NAT_ALIGN, 2).p(" | ").
      pad(Limits.LONG_LONG_NAT_ALIGN, 2).p(" | ").
      pad(Limits.FLOAT_NAT_ALIGN, 2).p(" | ").
      pad(Limits.DOUBLE_NAT_ALIGN, 2).p(" | ").
      pad(Limits.LONG_DOUBLE_NAT_ALIGN, 2).p(" | ").
      pad(Limits.POINTER_NAT_ALIGN, 2).pln();
    runtime.console().pln().flush();
  }
      
  public File locate(String name) throws IOException {
    File file = super.locate(name);
    if (runtime.test("optionNoIncr") && (Integer.MAX_VALUE < file.length())) {
      throw new IllegalArgumentException(file + ": file too large");
    }
    return file;
  }

  public Node parse(Reader in, File file) throws IOException, ParseException {
    if (runtime.test("optionParseTree")) { // ======================== Reader
      if (runtime.test("optionNoIncr")) {
        CReader parser = new CReader(in, file.toString(), (int)file.length());
        Result  result = parser.pTranslationUnit(0);
        printMemoInfo(parser, file);
        return (Node)parser.value(result);

      } else {
        CReader parser = new CReader(in, file.getName());
        GNode   unit   = GNode.create("TranslationUnit");
        unit.setLocation(new Location(file.toString(), 1, 0));
        Node    root   = unit;
        boolean first  = true;
        
        while (! parser.isEOF(0)) {
          Result result =
            first ? parser.pPrelude(0) : parser.pExternalDeclaration(0);
          printMemoInfo(parser, file);
          if (! result.hasValue()) parser.signal(result.parseError());
          
          if (first) {
            root = Formatting.before1(result.semanticValue(), unit);
            first = false;
          } else {
            unit.add(result.semanticValue());
          }
          parser.resetTo(result.index);
        }
        
        // Grab any trailing annotations.
        Result result = parser.pAnnotations(0);
        if (! result.hasValue()) parser.signal(result.parseError());
        unit.add(result.semanticValue());

        return root;
      }

    } else if (runtime.test("optionNoIncr")) { // ==================== Parser
      CParser parser = new CParser(in, file.toString(), (int)file.length());
      Result  result = parser.pTranslationUnit(0);
      printMemoInfo(parser, file);
      return (Node)parser.value(result);

    } else {
      CParser parser = new CParser(in, file.getName());
      GNode   root   = GNode.create("TranslationUnit");
      boolean first  = true;

      while (! parser.isEOF(0)) {
        Result result =
          first ? parser.pPrelude(0) : parser.pExternalDeclaration(0);
        printMemoInfo(parser, file);
        if (! result.hasValue()) parser.signal(result.parseError());

        if (first) {
          first = false;
        } else {
          root.add(result.semanticValue());
        }
        parser.resetTo(result.index);
      }

      // Grab any trailing annotations.
      Result result = parser.pAnnotations(0);
      if (! result.hasValue()) parser.signal(result.parseError());
      root.add(result.semanticValue());

      return root;
    }
  }

  /**
   * Print memoization information.
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
      runtime.console().pln().flush();
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
    // Analyze the AST.
    if (runtime.test("optionAnalyze")) {
      // Create new symbol table.
      SymbolTable table = new SymbolTable();

      // Add built-ins.
      if (runtime.test("optionBuiltIns")) {
        new CFactory("__builtin_", table.root()).declareBuiltIns(false);
      }
        
      // Perform type checking.
      new CAnalyzer(runtime).analyze(node, table);

      // Print the symbol table.
      if (runtime.test("printSymbolTable")) {
        // Save the registered visitor.
        Visitor visitor = runtime.console().visitor();
        // Note that the type printer's constructor registers the just
        // created printer with the console.
        new TypePrinter(runtime.console()); 
        try {
          table.root().dump(runtime.console());
        } finally {
          // Restore the previously registered visitor.
          runtime.console().register(visitor);
        }
        runtime.console().flush();
      }

      // Print program features.
      if (runtime.test("printFeatures") && 0 == runtime.errorCount()) {
        new CFeatureExtractor(runtime).process(node, table);
      }
    }

    // Print AST statistics.
    if (runtime.test("printASTStats")) {
      CCounter counter = new CCounter();
      counter.dispatch(node);
      counter.print(runtime.console());
      runtime.console().flush();
    }

    // Strip AST.
    if (runtime.test("optionStrip")) {
      node = (Node)new ParseTreeStripper().dispatch(node);
    }

    // Print AST.
    if (runtime.test("printAST")) {
      runtime.console().format(node, runtime.test("optionLocateAST")).pln().
        flush();
    }

    // Print source.
    if (runtime.test("printSource")) {
      if (runtime.test("optionParseTree") && (! runtime.test("optionStrip"))) {
        new ParseTreePrinter(runtime.console()).dispatch(node);
      } else {
        new CPrinter(runtime.console(),
                     runtime.test("preserveLines"),
                     runtime.test("formatGNU")).
          dispatch(node);
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
    new C().run(args);
  }

}
