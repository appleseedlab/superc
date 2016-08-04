/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 Robert Grimm
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

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Reader;

import java.util.HashMap;
import java.util.Map;

import xtc.Constants;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Transducer;

import xtc.util.Tool;
import xtc.util.Utilities;

import xtc.parser.ParseException;

/**
 * A factory of factories.  This tool reads in a factory declaration,
 * which contains one or more snippets of literal Java or C code and
 * then creates the corresponding Java factory class.  The class has
 * one method per snippet, with each method instantiating the abstract
 * syntax tree representing the code snippet.  Code snippets may be:
 * <ul>
 * <li>Declarations,</li>
 * <li>Statements,</li>
 * <li>Expressions.</li>
 * </ul>
 * Code snippets may also contain pattern variables:
 * <ul>
 * <li><code>#</code><i>Name</i> represents a single value, to be
 * supplied when instantiating the pattern.</li>
 * <li><code>#[</code><i>Name</i><code>]</code> represents a list of
 * values, also to be supplied when instantiating the pattern.</li>
 * </ul>
 * For each pattern variable, the corresponding method has a parameter
 * of the same name; the actual argument supplies the correponding
 * value(s) when instantiating the pattern.  Single-valued pattern
 * variables may appear instead of:
 * <ul>
 * <li>Declarations or statements in blocks,</li>
 * <li>Types or identifiers in variable declarations,</li>
 * <li>Expressions.</li>
 * </ul>
 * List-valued pattern variables may appear instead of:
 * <ul>
 * <li>Declarations or statements in blocks,</li>
 * <li>Arguments to a function or method call.</li>
 * </ul>
 *
 * <p />Consider this example factory description containing C
 * snippets:<pre>
 * alias number;
 *
 * factory xtc.lang.Stuff {
 *   declare { number * #name ; }
 *   block   { { int i; double d; #[statements] } }
 *   add     { #number + 5 }
 *   call    { #function ( #[arguments] ) }
 * }
 * </pre>
 * The optional alias declaration may only appear in factory
 * declarations with C snippets; it lists all typedef names used in
 * the C snippets as a comma-separate list.  In the example,
 * "<code>number</code>" is a typedef name.  It is followed by the
 * factory declaration itself, whose name, here
 * "<code>xtc.lang.Stuff</code>", is the fully qualified name of the
 * generated Java class.  The body of the factory declaration consists
 * of one or more method declarations, with each method declaration
 * consisting of a method name followed by the Java or C snippet
 * enclodes in curley braces.  The example declares four methods:<ul>
 *
 * <li><code>declare</code> creates a variable declaration of some
 * <em>name</em> being a pointer to <code>number</code>.</li>
 *
 * <li><code>block</code> creates a compound statement with variable
 * declarations for <code>i</code> and <code>d</code> and some list of
 * <em>statements</em>.</li>
 *
 * <li><code>add</code> creates an additive expression that adds
 * some expression <em>number</em> to the integer 5.</li>
 *
 * <li><code>call</code> creates a function call of some
 * <em>function</em> on some list of <em>arguments</em>.</li>
 * </ul>
 *
 * <p />The recommended file extension for factory declarations with
 * Java snippets is "<code>.ffj</code>" and with C snippets
 * "<code>.ffc</code>".
 *
 * @author Robert Grimm
 * @version $Revision: 1.16 $
 */
public class FactoryFactory extends Tool {

  /** Create a new factory factory. */
  public FactoryFactory() {
    /* Nothing to do. */
  }

  public String getName() {
    return "xtc Factory Factory";
  }

  public String getCopy() {
    return Constants.COPY;
  }

  public String getExplanation() {
    return
      "This tool translates factory declarations into the corresponding " +
      "Java classes.  Each declaration contains one or more snippets of " +
      "literal Java or C code, which are then translated into methods that " +
      "create the corresponding AST.  Snippets may be declarations, " +
      "statements, or expressions; they may also contain pattern variables. " +
      "The default language for snippets is Java; use the -C option for C.";
  }

  public void init() {
    super.init();
    runtime.
      bool("C", "createCFactory", false, "Create a factory for C ASTs.").
      bool("simplify", "simplifyAST", false, "Simplify the Java AST.");
  }

  public void prepare() {
    super.prepare();
    if (runtime.test("createCFactory") && runtime.test("simplifyAST")) {
      runtime.error("simplify option only valid for Java ASTs");
    }
  }

  public File locate(String name) throws IOException {
    File file = super.locate(name);
    if (Integer.MAX_VALUE < file.length()) {
      throw new IllegalArgumentException(file + ": file too large");
    }
    return file;
  }

  public Node parse(Reader in, File file) throws IOException, ParseException {
    if (runtime.test("createCFactory")) {
      CFactoryParser parser =
        new CFactoryParser(in, file.toString(), (int)file.length());
      return (Node)parser.value(parser.pFactory(0));

    } else {
      JavaFactoryParser parser =
        new JavaFactoryParser(in, file.toString(), (int)file.length());
      return (Node)parser.value(parser.pFactory(0));
    }
  }

  public void process(Node node) {
    GNode factory = GNode.cast(node);

    // Collapse the factory class name into a string.
    StringBuilder buf   = new StringBuilder();
    boolean       first = true;
    for (Object o : GNode.cast(factory.get(0))) {
      if (first) {
        first = false;
      } else {
        buf.append('.');
      }
      buf.append((String)o);
    }
    String name = buf.toString();

    // Determine the output file and open a printer to it.
    File file = new File(runtime.getOutputDirectory(),
                         Utilities.getName(name) + ".java");
    Printer out;
    try {
      out = new Printer(new PrintWriter(runtime.getWriter(file)));
    } catch (IOException x) {
      if (null == x.getMessage()) {
        runtime.error(file.toString() + ": I/O error");
      } else {
        runtime.error(file.toString() + ": " + x.getMessage());
      }
      return;
    }

    // Print the class declaration.
    String pkg = Utilities.getQualifier(name);

    printHeader(out);

    if (null != pkg) {
      out.indent().p("package ").p(pkg).pln(';');
      out.pln();
    }

    out.indent().pln("import java.util.List;").pln();

    if (! "xtc.tree".equals(pkg)) {
      out.indent().pln("import xtc.tree.Node;");
      out.indent().pln("import xtc.tree.GNode;");
      out.pln();
    }

    out.indent().pln("/**");
    out.indent().p(" * Node factory <code>").p(name).pln("</code>.");
    out.indent().pln(" *");
    out.indent().pln(" * <p />This class has been generated by");
    out.indent().p(" * the xtc Factory Factory, version ").p(getVersion()).
      pln(',');
    out.indent().p(" * ").p(getCopy()).pln('.');
    out.indent().pln(" */");
    out.indent().p("public class ").p(Utilities.getName(name)).
      pln(" {").incr();
    out.pln();

    out.indent().pln("/** Create a new node factory. */");
    out.indent().p("public ").p(Utilities.getName(name)).pln("() {").incr();
    out.indent().pln("// Nothing to do.");
    out.decr().indent().pln('}');
    out.pln();

    Map<String,String> variables = new HashMap<String,String>();
    variables.put("NodeVariable",     "Node"  );
    variables.put("NodeListVariable", "List<Node>");
    variables.put("StringVariable",   "String");
    Transducer         trans     = new Transducer(out, variables);
    JavaAstSimplifier  simple    = null;
    if (runtime.test("simplifyAST")) simple = new JavaAstSimplifier();
    for (Object o : GNode.cast(factory.get(1))) {
      GNode clause = GNode.cast(o);
      Node  ast    = clause.getNode(1);
      if (runtime.test("simplifyAST")) ast = (Node)simple.dispatch(ast);

      trans.process(clause.getString(0), ast);
      out.pln();
    }

    out.decr().indent().pln('}');
    out.flush().close();
  }

  /**
   * Run the factory factory with the specified command line arguments.
   *
   * @param args The command line arguments.
   */
  public static void main(String[] args) {
    new FactoryFactory().run(args);
  }

}
