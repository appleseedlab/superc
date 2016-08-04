/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 IBM Corp.
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
package xtc.lang.blink;

import java.io.CharArrayWriter;
import java.io.StringReader;
import java.io.StringWriter;

import xtc.lang.JavaEntities;
import xtc.parser.Result;
import xtc.parser.SemanticValue;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.util.Runtime;

import xtc.lang.jeannie.AstSimplifier;

/**
 * Static helper routines related to Blink.
 * This is a good place to put code that is useful for more than one visitor. 
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.2 $
 */
public final class Utilities {

  public static String debuggerAstToString(final GNode ast) {
    final CharArrayWriter writer = new CharArrayWriter();
    final CommandAstPrinter printer = new CommandAstPrinter(new Printer(writer));
    printer.dispatch(ast);
    return writer.toString();
  }
  
  
  /**
   * Parse the input as a debugger command, and analyze the resulting AST. If
   * either the parse or the analysis fails, return a message String. If neither
   * fails, return an AST Node. If the input contains an embedded expression,
   * the language argument determines whether it is "C" or "Java". The analyzer
   * annotates each node in the AST with the language for that node. It also
   * looks up variables and annotates them with their remapping based on the
   * current file and line number, where available.
   */
  public static Object debuggerParseAndAnalyze(final String language, final String input) {
    final Object result;
    {
      Node ast = null;
      String msg = null;
      try {
        ast = debuggerStringToAst(language, input);
        final StringWriter stringWriter = new StringWriter();
        final CommandAstAnalyzer ana = new CommandAstAnalyzer(newRuntime());
        ana._runtime.setErrConsole(new Printer(stringWriter));
        ana.dispatch(ast);
        msg = stringWriter.toString();
      } catch (final Exception e) {
        msg = e.getMessage();
      }
      result = (null == msg || "".equals(msg)) ? ast : msg;
    }
    assert null != result;
    if (result instanceof Node)
      CommandAstAnalyzer.assertAllNodesHaveLanguage((Node)result);
    return result;
  }
  
  public static GNode debuggerStringToAst(final String language, final String input) throws Exception {
    final CommandParser parser =
      new CommandParser(new StringReader(input), "<input>", input.length());
    final Result parseResult = "C".equals(language) ? parser.pCCommand(0) : parser.pJavaCommand(0);
    if (parseResult.hasValue()) {
      final SemanticValue val = (SemanticValue) parseResult;
      if (val.index != input.length())
        parser.signal(parseResult.parseError());
      final GNode ast = (GNode) val.value;
      return (GNode) new AstSimplifier(language).dispatch(ast);
    }
    parser.signal(parseResult.parseError());
    return null;
  }

  public static Runtime newRuntime() {
    final Runtime runtime = new Runtime();
    runtime.dir("in", Runtime.INPUT_DIRECTORY, true, "").setValue(Runtime.INPUT_DIRECTORY, JavaEntities.TEMP_DIR);
    runtime.bool("markAST", "optionMarkAST", true, "Mark AST nodes with types.").setValue("optionMarkAST", true);
    runtime.bool("strict", "optionStrict", true, "Enforce strict C99 compliance.").setValue("optionStrict", true);
    runtime.bool("pedantic", "optionPedantic", false, "Enforce strict C99 compliance.").setValue("optionPedantic", true);
    runtime.word("jniCall", "jniCall", false, "Calling conventions qualifier to C JNI functions.").setValue("jniCall", "");
    runtime.initDefaultValues();
    return runtime;
  }

  private Utilities() {
    assert false;
  }
}
