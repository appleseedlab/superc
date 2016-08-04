/* (C) Copyright IBM Corp 2005-2007. */
package xtc.lang.jeannie;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;
import java.io.Writer;

import xtc.lang.CPrinter;
import xtc.lang.JavaEntities;
import xtc.lang.JavaPrinter;
import xtc.parser.ParseException;
import xtc.parser.Result;
import xtc.parser.SemanticValue;
import xtc.tree.LineupPrinter;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Visitor;
import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.Tool;

/**
 * A compiler from Jeannie to separate Java and C files that use JNI.
 *
 * @author Martin Hirzel
 */
public final class Jeannie extends Tool {
  public static String getStem(final String fileName) {
    final int lastSlash = fileName.lastIndexOf(File.separatorChar);
    final int extensionStart = fileName.indexOf('.', lastSlash);
    return -1 == extensionStart ? fileName : fileName.substring(0, extensionStart);
  }

  public static void main(String[] args) {
    new Jeannie().run(args);
  }

  public final String getCopy() {
    return "(C) 2005-2007 IBM, Robert Grimm, and NYU";
  }

  public final String getName() {
    return "Jeannie compiler";
  }

  public final void init() {
    super.init();
    runtime.
      bool("printAST", "printAST", false,
           "Print the AST in generic form.").
      bool("printSource", "printSource", false,
           "Print the AST in Jeannie source form.").
      bool("analyze", "optionAnalyze", false,
           "Analyze the program's AST.").
      bool("printSymbolTable", "printSymbolTable", false,
           "Print the program's symbol table.").
      bool("translate", "translate", false,
           "Generate separate C and Java code.").
      bool("markAST", "optionMarkAST", true,
           "Mark AST nodes with types.").
      bool("strict", "optionStrict", true,
           "Enforce strict C99 compliance.").
      bool("pedantic", "optionPedantic", false,
           "Enforce strict C99 compliance.").
      bool("builtins", "optionBuiltIns", false,
           "Declare C built-ins before analysis.").
      bool("pretty", "pretty", false,
           "Optimize output for human-readability.").
      word("jniCall", "jniCall", false,
           "Calling conventions qualifier to C JNI functions."
           + " The default is the empty string \"\"." 
           + " On cygwin, use -jniCall \"__attribute__((__stdcall__))\".").
      bool("showFilePaths", "showFilePaths", false,
           "Should line markers in the generated Java source code show "
           + " file paths (true), or just relative file names (false)?");
    runtime.setValue("optionMarkAST", true);
    runtime.setValue("optionStrict", true);
    runtime.setValue("optionPedantic", true);
  }

  public final Node parse(final Reader in, final File file) throws IOException, ParseException {
    final Reader inUnescaped = new JavaEntities.UnicodeUnescaper(in);
    final JeannieParser parser = new JeannieParser(inUnescaped, file.toString(), (int)file.length());
    final Result parseResult = parser.pFile(0);
    if (!parseResult.hasValue())
      parser.signal(parseResult.parseError());
    final Node messy = (Node)((SemanticValue)parseResult).value;
    final Node result = (Node)new AstSimplifier(null).dispatch(messy);
    result.setProperty("originalFileName", file.getCanonicalPath());
    return result;
  }
  
  public final void prepare() {
    super.prepare();
    if (runtime.test("printSymbolTable") || runtime.test("translate"))
      if (!runtime.test("optionAnalyze"))
        runtime.error("need analyze option to obtain symbol table");
  }

  public final void process(final Node node) {
    if (runtime.test("optionAnalyze")) {
      // Make sure the classpath is set.
      if (!runtime.hasValue(Runtime.INPUT_DIRECTORY))
        runtime.setValue(Runtime.INPUT_DIRECTORY, new File(System.getProperty("user.dir")));

      // Perform type checking.
      final SymbolTable tab = new SymbolTable();
      if (runtime.test("optionBuiltIns"))
        new xtc.type.CFactory("__builtin_", tab.root()).declareBuiltIns(false);
      final Analyzer ana = new Analyzer(runtime, tab, null);
      ana.dispatch(node);
      if (0 < runtime.errorCount())
        System.exit(-1);

      // Print the symbol table.
      if (runtime.test("printSymbolTable")) {
        final Visitor visitor = runtime.console().visitor();
        try {
          tab.root().dump(runtime.console());
        } finally {
          runtime.console().register(visitor);
        }
        runtime.console().flush();
      }
      
      // Generate code.
      if (runtime.test("translate")) {
        final String outStem = getStem((String) node.getProperty("originalFileName"));
        final boolean sfp = runtime.test("showFilePaths");
        final CodeGenerator cg = new CodeGenerator(runtime, tab);
        final CodeGenerator.Out cgOut =
          (CodeGenerator.Out)cg.dispatch(node);
        try {
          final Writer writer = new BufferedWriter(new FileWriter(outStem + ".i"));
          final Printer printer = runtime.test("pretty") ? new Printer(writer) : new LineupPrinter(writer, sfp);
          new CPrinter(printer).dispatch(cgOut._cNode);
          printer.flush();
          writer.close();
        } catch (final IOException e) {
          throw new Error(e);
        }
        try {
          final Writer writer = new BufferedWriter(new FileWriter(outStem + ".java"));
          final Printer printer = runtime.test("pretty") ? new Printer(writer) : new LineupPrinter(writer, sfp);
          new JavaPrinter(printer).dispatch(cgOut._javaNode);
          printer.flush();
          writer.close();
        } catch (final IOException e) {
          throw new Error(e);
        }
        if (!runtime.test("pretty"))
          try {
            final PrintWriter writer = new PrintWriter(new FileWriter(outStem + ".jni.symbols"));
            Utilities.printTopLevelDeclarations(writer, cgOut._javaNode);
            Utilities.printLocalVariableMap(writer, node, tab, cg._cSubstitutions, cg._javaSubstitutions);
            Utilities.printMethodMap(writer, tab, cg._methodSubstitutions);
            writer.close();
          } catch (final IOException e) {
            throw new Error(e);
          }
      }
    }
    if (runtime.test("printAST")) {
      runtime.console().format(node).pln().flush();
    }
    if (runtime.test("printSource")) {
      new JeanniePrinter(runtime.console(), null).dispatch(node);
      runtime.console().flush();
    }
  }
}
