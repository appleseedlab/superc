/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007-2011 Robert Grimm
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
import java.io.Reader;

import xtc.Constants;

import xtc.parser.ParseException;

import xtc.tree.Node;

import xtc.util.SymbolTable;
import xtc.util.Tool;

/**
 * A tool for reading and writing simply typed lambda calculus
 * expressions.
 *
 * @author Robert Grimm
 * @version $Revision: 1.12 $
 */
public class TypedLambda extends Tool {

  /** Create a new driver for the simply typed lambda calculus. */
  public TypedLambda() {
    /* Nothing to do. */
  }

  public String getName() {
    return "xtc Simply Typed Lambda Calculus Driver";
  }

  public String getCopy() {
    return Constants.COPY;
  }

  public void init() {
    super.init();
    runtime.
      bool("printAST", "printAST", false,
           "Print the program's AST in generic form.").
      bool("printSource", "printSource", false,
           "Print the program's AST in source form.");
  }

  public File locate(String name) throws IOException {
    final File file = super.locate(name);
    if (Integer.MAX_VALUE < file.length()) {
      throw new IllegalArgumentException(file + ": file too large");
    }
    return file;
  }

  public Node parse(Reader in, File file) throws IOException, ParseException {
    final TypedLambdaParser parser = 
      new TypedLambdaParser(in, file.toString(), (int)file.length());
    return (Node)parser.value(parser.pExpression(0));
  }

  public void process(Node node) {
    // Print AST.
    if (runtime.test("printAST")) {
      runtime.console().format(node).pln().flush();
    }

    // Print source.
    if (runtime.test("printSource")) {
      new TypedLambdaPrinter(runtime.console()).dispatch(node);
      runtime.console().pln().flush();
    }
  }

  /**
   * Run the driver with the specified command line arguments.
   *
   * @param args The command line arguments.
   */
  public static void main(String[] args) {
    new TypedLambda().run(args);
  }

}
