/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004 Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package xtc.parser;

import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import java.text.DateFormat;

import xtc.Constants;

import xtc.util.Utilities;

import xtc.tree.Attribute;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.tree.Visitor;

/**
 * The code generator. 
 *
 * <p />The code generator makes the following assumptions about the
 * intermediate language:<ul>
 *
 * <li>Each {@link Production production} must have an {@link
 * OrderedChoice ordered choice} as its element.<p /></li>
 * 
 * <li>Each {link Production production} must have been annotated
 * with the appropriate {@link MetaData meta-data}.<p /></li>
 *
 * <li>Each option of an {@link OrderedChoice ordered choice} must
 * be a {@link Sequence sequence}.<p /></li>
 *
 * <li>Generally, all {@link Option options}, {@link Repetition
 * repetitions}, and nested {@link OrderedChoice ordered choices} must
 * have been desugared into equivalent productions.  However, an
 * ordered choice may appear as the <i>last</i> element of a sequence
 * (that is <i>not</i> part of a predicate), and a repetition may
 * appear if the repeated expressions need not be memoized.<p /></li>
 *
 * <li>The element of a {@link Repetition repetition} must be a {@link
 * Sequence sequence} (with the last element possibly being an ordered
 * choice; see previous assumption).<p /></li>
 *
 * <li>The {@link FollowedBy#element} and {@link
 * NotFollowedBy#element} fields must reference a sequence.<p /></li>
 *
 * <li>All elements in a {@link CharSwitch character switch} must
 * either be ordered choices or sequences.  Furthermore, character
 * switches may only appear as the last element in a sequence and not
 * within predicates.<p /></li>
 *
 * </ul>
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public class CodeGenerator extends Visitor {

  /**
   * The {@link Attribute attribute} name for printing debugging
   * information while parsing.  For grammars with this attribute, the
   * code generator emits code that prints debugging information to
   * the console while parsing.
   */
  public static final String ATT_DEBUG = "debug";

  /**
   * The {@link Attribute attribute} name for annotating instances of
   * {@link Node} with their location information:
   * <code>location</code>.  For grammars with this attribute, the
   * code generator emits code that automatically annotates all nodes
   * with their grammar {@link Location location information}.
   */
  public static final String ATT_LOCATION = "location";

  /**
   * The {@link Attribute attribute} name for making variable bindings
   * constant: <code>constantBinding</code>.  For grammars with this
   * attribute, the code generator declares all variable bindings to
   * be constant (in the case of Java, final).
   */
  public static final String ATT_CONSTANT_BINDING = "constantBinding";

  /**
   * The {@link Attribute attribute} name for not generating specific
   * parse errors when a string literal or string match fails:
   * <code>noMatchingErrors</code>.  For grammars with this attribute,
   * parse errrors are only generated at the granularity of an entire
   * production (pointing to the beginning of the production).
   */
  public static final String ATT_NO_MATCHING_ERRORS = "noMatchingErrors";

  /** The size of chunks. */
  public static final int CHUNK_SIZE = 10;

  /** The prefix for parsing method names. */
  public static final String PREFIX_METHOD = "p";

  /** The prefix for field names that memoize the parsers results. */
  public static final String PREFIX_FIELD = "f";

  /** The general prefix for internal parser fields and variables. */
  public static final String PREFIX = "yy";
  
  /** The name for the character parsing method. */
  public static final String PARSE_CHAR = "character";

  /** The name for the file name variable. */
  public static final String FILE = PREFIX + "File";

  /** The name for the line number variable. */
  public static final String LINE = PREFIX + "Line";

  /** The name for the column number variable. */
  public static final String COLUMN = PREFIX + "Column";

  /** The name for the character variable. */
  public static final String CHAR = PREFIX + "C";

  /** The name for the parser variable. */
  public static final String PARSER = PREFIX + "Parser";

  /** The prefix for the parser variable for nested choices. */
  public static final String NESTED_CHOICE = PREFIX + "Choice";

  /** The prefix for the parser variable for repetitions. */
  public static final String REPETITION = PREFIX + "Repetition";

  /**
   * The prefix for the flag indicating that a repetition has been
   * matched at least once.
   */
  public static final String REPEATED = PREFIX + "Repeated";

  /** The name for the regular result variable. */
  public static final String RESULT = PREFIX + "Result";

  /** The name for the parse error variable. */
  public static final String PARSE_ERROR = PREFIX + "Error";

  /** The name for the predicate result variable. */
  public static final String PRED_RESULT = PREFIX + "PredResult";

  /** The name for the predicate matched variable. */
  public static final String MATCHED = PREFIX + "PredMatched";

  /** The name for the value variable. */
  public static final String VALUE = PREFIX + "Value";

  // ========================================================================

  /** The analyzer utility. */
  protected final Analyzer analyzer;

  /** The printer utility. */
  protected final Printer printer;

  /** The number of spaces to align variable declarations to. */
  protected int      alignment = 0;

  /** The flag for generating debugging code. */
  protected boolean  attributeDebug;

  /**
   * The flag for generating code to annotate nodes with location
   * information.
   */
  protected boolean  attributeLocation;

  /** The flag for making variable bindings constant. */
  protected boolean  attributeConstantBinding;

  /** The flag for not generating matching errors. */
  protected boolean  attributeNoMatchingErrors;

  /** The class name for the current grammar. */
  protected String   cName;

  /** Flag for whether the memoization fields are organized in chunks. */
  protected boolean  chunked;

  /** The map from nonterminals to chunk numbers. */
  protected Map      chunkMap;

  /** The number of chunks. */
  protected int      chunkCount;

  /** The flag for the first element in a top-level choice. */
  protected boolean  firstElement;

  /** The saved first element. */
  protected boolean  savedFirstElement;

  /** The expression for the base parser. */
  protected String   baseParser;

  /** The flag for using the base parser. */
  protected boolean  useBaseParser;

  /** The saved base parser. */
  protected String   savedBaseParser;

  /** The saved flag for using the base parser. */
  protected boolean  savedUseBaseParser;

  /** The nesting level for nested choices. */
  protected int      choiceLevel;

  /** The nesting level for repetitions. */
  protected int      repetitionLevel;

  /** The saved repetition level (for predicates). */
  protected int      savedRepetitionLevel;

  /** The flag for at-least-once repetitions. */
  protected boolean  repeatOnce;

  /** Flag for whether a test has been emitted. */
  protected boolean  seenTest;

  /** Flag for whether the current choice ends with a parse error. */
  protected boolean  endsWithParseError;

  /** The iterator over the elements of a sequence. */
  protected Iterator elementIter;

  /** The name of the result variable. */
  protected String   resultName;

  /** The name of the current binding. */
  protected String   bindingName;

  /** The element being bound. */
  protected Element  bindingElement;
  
  /** Flag for whether we are currently emitting a predicate. */
  protected boolean  predicate;

  /**
   * Flag for whether the current predicate is a not-followed-by
   * predicate.
   */
  protected boolean  notFollowedBy;

  /** The predicate iterator. */
  protected Iterator predicateIter;

  // ========================================================================

  /**
   * Create a new code generator.
   *
   * @param analyzer The analyzer for the new code generator.
   * @param printer The printer for the new code generator.
   */
  public CodeGenerator(Analyzer analyzer, Printer printer) {
    this.analyzer = analyzer;
    this.printer  = printer;
  }

  // ========================================================================

  /**
   * Generate the field name for the specified nonterminal.
   *
   * @param nt The nonterminal.
   * @return The corresponding field name.
   */
  public String fieldName(NonTerminal nt) {
    if (chunked) {
      return PREFIX + "Chunk" + chunkMap.get(nt) + "." +
        PREFIX_FIELD + nt.name;
    } else {
      return PREFIX_FIELD + nt.name;
    }
  }

  /**
   * Generate the method name for the specified nonterminal.
   *
   * @param nt The nonterminal.
   * @return The corresponding method name.
   */
  public String methodName(NonTerminal nt) {
    return PREFIX_METHOD + nt.name;
  }

  // ========================================================================

  /**
   * Determine the variable alignment for parse method declarations.
   *
   * @param includeParser Flag for whether a parser variable needs to
   *   be declared.
   */
  protected void alignment(boolean includeParser) {
    alignment   = 0;
    if (includeParser) {
      alignment = Math.max(alignment, cName.length()        + 1);
    }
    alignment   = Math.max(alignment, "ParseError".length() + 1);
  }

  // ========================================================================

  /** Generate code for the specified grammar. */
  public void visit(Grammar g) {
    // (Re)Initialize code generator state.
    analyzer.register(this);
    printer.register(this);
    analyzer.init(g);
    cName = g.cName;

    // Record the grammar attributes.
    Set attributes;
    if (null != g.attributes) {
      attributes = new HashSet(g.attributes);
    } else {
      attributes = new HashSet();
    }
    attributeDebug            =
      attributes.contains(new Attribute(ATT_DEBUG));
    attributeLocation         =
      attributes.contains(new Attribute(ATT_LOCATION));
    attributeConstantBinding  =
      attributes.contains(new Attribute(ATT_CONSTANT_BINDING));
    attributeNoMatchingErrors =
      attributes.contains(new Attribute(ATT_NO_MATCHING_ERRORS));

    chunked    = false;
    chunkMap   = null;
    chunkCount = 0;

    // Emit header.
    printer.sep();
    printer.indent().pln("// This file has been generated by");
    printer.indent().p("// Rats! Parser Generator, Version ").
      p(Constants.VERSION).p(", ").pln(Constants.COPY);
    Date now = new Date();
    printer.indent().p("// on ").
      p(DateFormat.getDateInstance(DateFormat.FULL).format(now)).
      p(" at ").
      p(DateFormat.getTimeInstance(DateFormat.MEDIUM).format(now)).pln('.');
    printer.indent().pln("// Edit at your own risk.");
    printer.sep();
    printer.pln();

    // Emit package name.
    if (null != g.pName) {
      printer.indent().p("package ").p(g.pName).pln(';');
      printer.pln();
    }

    // Emit imports.
    printer.indent().pln("import java.io.IOException;");
    printer.indent().pln("import java.io.Reader;");
    printer.pln();
    printer.indent().pln("import xtc.util.Pair;");
    if (attributeLocation) {
      printer.pln();
      printer.indent().pln("import xtc.tree.Node;");
    }
    printer.pln();
    printer.indent().pln("import xtc.parser.PackratParser;");
    printer.indent().pln("import xtc.parser.Result;");
    printer.indent().pln("import xtc.parser.SemanticValue;");
    printer.indent().pln("import xtc.parser.ParseError;");
    printer.pln();

    // Emit header.
    if (null != g.header) {
      action(g.header);
      printer.pln();
    }

    // Emit class name.
    printer.indent().pln("/**");
    if (null != g.location) {
      printer.indent().p(" * Packrat parser for grammar ").p(g.location.file).
        pln('.');
    } else {
      printer.indent().pln(" * Packrat parser.");
    }
    printer.indent().
      p(" * This class has been generated by the <i>Rats!</i> parser ").
      p("generator, v. ").p(Constants.VERSION).pln('.');
    printer.indent().pln(" */");
    printer.indent().p("public final class ").p(cName).
      pln(" extends PackratParser {").incr();
    printer.pln();

    // Emit debug flag.
    if (attributeDebug) {
      printer.indent().
        p("/** Flag for whether to emit debugging information while ").
        pln("parsing. */");
      printer.indent().pln("public static final boolean DEBUG = true;");
      printer.pln();
    }
    
    // Determine the number of productions that require memoization.
    int memoCount = 0;

    Iterator iter = g.productions.iterator();
    while (iter.hasNext()) {
      Production p  = (Production)iter.next();
      MetaData   md = (MetaData)p.getProperty(MetaData.NAME);
      // Only memoize non-transient productions that are used more
      // than once.
      if ((1 < md.usageCount) && (! p.isTransient)) {
        memoCount++;
      }
    }

    // To chunk or not to chunk.
    if (Rats.optimizeChunks && (CHUNK_SIZE <= memoCount)) {
      chunked    = true;
      chunkMap   = new HashMap(memoCount * 4 / 3);

      Integer  number  = null;
      String   sNumber = null;
      int      i       = CHUNK_SIZE;
      boolean  first   = true;
      iter             = g.productions.iterator();

      while (iter.hasNext()) {
        Production p  = (Production)iter.next();
        MetaData   md = (MetaData)p.getProperty(MetaData.NAME);

        // Skip memoization for productions that are transient or used
        // at most once.
        if ((1 >= md.usageCount) || (Rats.optimizeTransient && p.isTransient)) {
          continue;
        }

        if (CHUNK_SIZE <= i) {
          chunkCount++;
          number  = new Integer(chunkCount);
          sNumber = Integer.toString(chunkCount);
          i       = 0;

          if (first) {
            first = false;
            printer.sep();
          } else {
            printer.decr().indent().pln('}');
          }
          printer.pln();
          printer.indent().p("/** Chunk ").p(sNumber).
            pln(" of memoized results. */");
          printer.indent().p("static final class Chunk").p(sNumber).
            pln(" {").incr();
        }

        NonTerminal nt = p.nonTerminal;

        chunkMap.put(nt, number);
        i++;

        printer.indent().p("Result ").p(PREFIX_FIELD).p(nt.name).
          pln(';');
      }

      printer.decr().indent().pln('}');
      printer.pln();
    }

    // Emit fields.  Note that the field for memoizing the result of
    // the character parsing method is already defined in
    // PackratParser.
    printer.sep().pln();
    if (chunked) {
      for (int i=1; i<=chunkCount; i++) {
        printer.indent().p("private Chunk").p(i).p(' ').p(PREFIX).p("Chunk").
          p(i).pln(';');
      }

    } else {
      iter = g.productions.iterator();
      while (iter.hasNext()) {
        Production p  = (Production)iter.next();
        MetaData   md = (MetaData)p.getProperty(MetaData.NAME);

        // Only create memoization fields for non-transient
        // productions that are used more than once.
        if (((! Rats.optimizeChunks)    || (1 < md.usageCount)) &&
            ((! Rats.optimizeTransient) || (! p.isTransient))) {
          printer.indent().p("private Result ").p(fieldName(p.nonTerminal)).
            pln(';');
        }
      }
    }
    printer.pln();

    // Emit constructors.
    printer.sep().pln();
    printer.indent().
      pln("/** Create a new packrat parser for the specified file. */");
    printer.indent().p("public ").p(cName).
      pln("(Reader reader, String file) {").incr();
    printer.indent().pln("super(reader, file);");
    printer.decr().indent().pln('}');
    printer.pln();

    printer.indent().p("/** Create a new packrat parser, moving ahead one ").
      pln("character. */");
    printer.indent().p("protected ").p(cName).p('(').p(cName).
      pln(" previous) {").incr();
    printer.indent().pln("super(previous);");
    printer.decr().indent().pln('}');
    printer.pln();

    // Emit code for creating the next parser.
    printer.sep().pln();
    printer.indent().pln("protected PackratParser next() {").incr();
    printer.indent().p("return new ").p(cName).pln("(this);");
    printer.decr().indent().pln('}');
    printer.pln();
    
    // Emit code for productions.
    iter = g.productions.iterator();
    while (iter.hasNext()) {
      analyzer.process((Production)iter.next());
    }

    // Emit code for body.
    if (null != g.body) {
      printer.sep().pln();
      action(g.body);
    }

    // Finish parser class.
    printer.decr().indent().pln('}');

    // Emit footer.
    if (null != g.footer) {
      printer.pln().sep().pln();
      action(g.footer);
    }
  }

  // ========================================================================

  /** Generate code for the specified production. */
  public void visit(Production p) {
    MetaData md     = (MetaData)p.getProperty(MetaData.NAME);
    String   field  = fieldName(p.nonTerminal);
    String   method = methodName(p.nonTerminal);

    printer.sep().pln();
    printer.indent().pln("/**");
    printer.indent().p(" * Parse ");
    if (p.hasProperty(Constants.SYNTHETIC) &&
        ((Boolean)p.getProperty(Constants.SYNTHETIC)).booleanValue()) {
      printer.p("synthetic ");
    }
    printer.p("nonterminal ").p(p.nonTerminal.name).pln('.');
    if (p.hasProperty(DuplicateProductionFolder.DUPLICATES)) {
      List sources = (List)p.getProperty(DuplicateProductionFolder.DUPLICATES);
      printer.indent().
        pln(" * This nonterminal represents the duplicate productions ").
        indent().p(" * ").p(Utilities.format(sources)).pln('.');
    }
    printer.indent().pln(" *");
    printer.indent().pln(" * @return The result.");
    printer.indent().pln(" * @throws IOException Signals an I/O error.");
    printer.indent().pln(" */");
    printer.indent();
    if (analyzer.isTopLevel(p.nonTerminal)) {
      // Top-level parsing methods are public.
      printer.p("public");
    } else {
      // The rest is private.
      printer.p("private");
    }
    printer.p(" Result ").p(method).pln("() throws IOException {").incr();

    // Only memoize non-transient productions that are used more than
    // once.
    if (((! Rats.optimizeChunks)    || (1 < md.usageCount)) &&
        ((! Rats.optimizeTransient) || (! p.isTransient))) {
      if (chunked) {
        String chunk = chunkMap.get(p.nonTerminal).toString();
        printer.indent().p("if (null == ").p(PREFIX).p("Chunk").
          p(chunk).p(") ").p(PREFIX).p("Chunk").p(chunk).p(" = new Chunk").
          p(chunk).pln("();");
      }
      printer.indent().p("if (null == ").p(field).p(") ").p(field).p(" = ").
        p(method).pln("$1();");
      printer.indent().p("return ").p(field).pln(';');
      printer.decr().indent().pln('}');

      printer.pln();

      printer.indent().p("/** Actually parse ");
      if (p.hasProperty(Constants.SYNTHETIC)) {
        printer.p("synthetic ");
      }
      printer.p("nonterminal <code>").p(p.nonTerminal.name).pln("</code>. */");
      printer.indent().p("private Result ").p(method).
        pln("$1() throws IOException {").incr();

      if (attributeDebug) {
        printer.indent().p("if (DEBUG) System.out.println(\"").p(method).
          pln("$1: \" + toString());");
        printer.pln();
      }

    } else if (attributeDebug) {
      printer.indent().p("if (DEBUG) System.out.println(\"").p(method).
        pln(": \" + toString());");
      printer.pln();
    }

    // Emit variable declarations.
    alignment(md.requiresParser || (0 < md.repetitions.size()));
    if (md.requiresParser) {
      printer.indent().p(cName).align(alignment).p(PARSER).pln(';');
    }
    printer.indent().p("Result").align(alignment).p(RESULT).pln(';');
    printer.indent().p("ParseError").align(alignment).p(PARSE_ERROR).
      pln(" = ParseError.DUMMY;");
    if (md.requiresPredicate) {
      printer.indent().p("Result").align(alignment).p(PRED_RESULT).pln(';');
    }
    if (md.requiresMatched) {
      printer.indent().p("boolean").align(alignment).p(MATCHED).pln(';');
    }
    for (int i=0; i<md.repetitions.size(); i++) {
      printer.indent().p(cName).align(alignment).p(REPETITION).p(i+1).pln(';');
      if (((Boolean)md.repetitions.get(i)).booleanValue()) {
        printer.indent().p("boolean").align(alignment).p(REPEATED).
          p(i+1).pln(';');
      }
    }
    if (Type.isVoidT(p.type)) {
      printer.indent().p(Type.voidRefT()).
        align(Type.voidRefT().length(), alignment);
    } else {
      printer.indent().p(p.type).align(p.type.length(), alignment);
    }
    printer.p(VALUE).pln(';');
    if (md.requiresChar) {
      printer.indent().p(Type.charT()).align(alignment).p(CHAR).pln(';');
    }

    // Emit code for production element.
    resultName           = RESULT;
    baseParser           = "this";
    useBaseParser        = true;
    choiceLevel          = -1;
    repetitionLevel      = 0;
    savedRepetitionLevel = 0;
    repeatOnce           = false;
    seenTest             = false;
    endsWithParseError   = false;
    p.element.accept(this);

    if (seenTest) {
      printer.pln();
      printer.indent().pln("// Done.");
      if (endsWithParseError) {
        parseError();
      }
      printer.indent().p("return ").p(PARSE_ERROR).pln(';');
    }
    printer.decr().indent().pln('}');
    printer.pln();
  }

  // ========================================================================

  /**
   * Emit the code for assigning the result variable, threading the
   * parse error, and for testing the result.
   *
   * @param methodName The name of the parser method to use.
   * @param saveParser Flag for whether to save the parser in the
   *   parser variable.
   */
  protected void result(String methodName, boolean saveParser) {
    printer.pln();

    // Clear the first element flag.
    firstElement = false;

    if (useBaseParser) {
      // The first result of an ordered choice or repetition as well
      // as the first element after a repetition always builds on the
      // current base parser.  The first element of a predicate also
      // builds on the current base parser.

      if (saveParser) {
        // Assign parser and result.
        printer.indent().p(PARSER).p(" = ").p(baseParser).pln(';');
        printer.indent().p(resultName).p(" = ").p(PARSER).p('.').
          p(methodName).pln("();");
      } else {
        // Assign result.
        printer.indent().p(resultName).p(" = ").p(baseParser).p('.').
          p(methodName).pln("();");
      }

      // Thread parse error.
      if ((! notFollowedBy()) && (! PARSE_CHAR.equals(methodName))) {
        printer.indent().p(PARSE_ERROR).p("  = ").p(PARSE_ERROR).p(".select(").
          p(resultName).pln(".parseError());");
      }

      useBaseParser = false;

    } else {
      // All other elements build on the last regular/predicate
      // result, depending on whether we are processing regular or
      // predicate elements.

      if (saveParser) {
        // Assign parser and result.
        printer.indent().p(PARSER).p(" = (").p(cName).p(')').p(resultName).
          pln(".parser;");
        printer.indent().p(resultName).p(" = ").p(PARSER).p('.').
          p(methodName).pln("();");

      } else {
        // Assign result.
        printer.indent().p(resultName).p(" = ((").p(cName).p(')').p(resultName).
          p(".parser).").p(methodName).pln("();");
      }

      // Thread parse error.
      if ((! notFollowedBy()) && (! PARSE_CHAR.equals(methodName))) {
        printer.indent().p(PARSE_ERROR).p("  = ").p(PARSE_ERROR).p(".select(").
          p(resultName).pln(".parseError());");
      }
    }
  }

  /** Emit the code testing whether the result has a value. */
  protected void valueTest() {
    printer.indent().p("if (").p(resultName).pln(".hasValue()) {").incr();
  }

  /**
   * Emit the code for testing the result.
   *
   * @param text The expected text value.
   */
  protected void valueTest(String text) {
    printer.indent().p("if (").p(resultName).pln(".hasValue() &&").
      indent().p("   \"").escape(text, Utilities.JAVA_ESCAPES).p("\".equals(").
      p(resultName).pln(".semanticValue())) {").incr();
  }

  /**
   * Note that a test has been emitted.  This method should be called
   * at the <i>end</i> of the method that emitted the test.
   */
  protected void tested() {
    seenTest = true;
  }

  /**
   * Emit the code for the next element. If the next element is the
   * last element in the main sequence, the code for returning a
   * semantic value is also emitted.
   *
   * @see #returnValue()
   */
  protected void nextElement() {
    // Process predicate elements first.
    if (predicate) {
      if (predicateIter.hasNext()) {
        // Emit code for the next predicate element.
        ((Element)predicateIter.next()).accept(this);
        return;

      } else if (savedRepetitionLevel < repetitionLevel) {
        // Assign the repetition parser variable and, if necessary,
        // the repeated flag; then continue with the loop.
        printer.pln();
        printer.indent().p(REPETITION).p(repetitionLevel).p(" = (").
          p(cName).p(')').p(resultName).pln(".parser;");
        if (repeatOnce) {
          printer.indent().p(REPEATED).p(repetitionLevel).pln("   = true;");
        }
        printer.indent().pln("continue;");
        return;

      } else {
        // Assign matched variable for not-followed-by predicates.
        if (notFollowedBy) {
          printer.pln();
          printer.indent().p(MATCHED).pln(" = true;");
          return;
        }

        // Restore regular element processing and fall through for
        // followed-by predicates.
        predicate     = false;
        baseParser    = savedBaseParser;
        useBaseParser = savedUseBaseParser;
        resultName    = RESULT;
      }
    }

    // Process the next regular grammar element.
    if (elementIter.hasNext()) {
      ((Element)elementIter.next()).accept(this);

    } else if (0 < repetitionLevel) {
      printer.pln();
      printer.indent().p(REPETITION).p(repetitionLevel).p(" = (").
        p(cName).p(')').p(resultName).pln(".parser;");
      if (repeatOnce) {
        printer.indent().p(REPEATED).p(repetitionLevel).pln("   = true;");
      }
      printer.indent().pln("continue;");

    } else {
      returnValue();
    }
  }

  /**
   * Emit the code for annotating semantic values with their location.
   */
  private void location() {
    // Do not include location information if the grammar does not
    // have the location attribute or the type of the production's
    // semantic value is not a node.  Note that void and text-only
    // productions automatically fall under the second case.
    if ((! attributeLocation) || Type.isNotANode(analyzer.current().type)) {
      return;
    }

    // Emit the location test.
    printer.indent().p("if (").p(VALUE).pln(" instanceof Node) {").incr();
    printer.indent().p("((Node)").p(VALUE).p(").").p("setLocation(").
      p(FILE).p(", ").p(LINE).p(", ").p(COLUMN).pln(");");
    printer.decr().indent().pln('}');
  }

  /**
   * Emit the code for returning a semantic value.
   */
  protected void returnValue() {
    printer.pln();

    if (useBaseParser) {
      location();

      printer.indent().p("return new SemanticValue(").p(VALUE).
        p(", ").p(baseParser).p(", ").p(PARSE_ERROR).pln(");");

      useBaseParser = false;

    } else {
      location();

      if (Rats.optimizeValues) {
        printer.indent().p("return ").p(RESULT).p(".createValue(").
          p(VALUE).p(", ").p(PARSE_ERROR).pln(");");
      } else {
        printer.indent().p("return new SemanticValue(").p(VALUE).
          p(", ").p(RESULT).p(".parser, ").p(PARSE_ERROR).pln(");");
      }
    }
  }

  /**
   * Emit the code for generating a parse error.
   */
  protected void parseError() {
    printer.indent().p(PARSE_ERROR).p(" = ").p(PARSE_ERROR).
      p(".select(\"").
      p(Utilities.toDescription(analyzer.current().nonTerminal.name)).
      pln(" expected\", this);");
  }

  /**
   * Emit the code for generating a parse error.
   *
   * @param text The expected text.
   */
  protected void parseError(String text) {
    printer.indent().p(PARSE_ERROR).p(" = ").p(PARSE_ERROR).
      p(".select(\"\\\"").
      p(Utilities.escape(text,
                         Utilities.JAVA_ESCAPES | Utilities.ESCAPE_DOUBLE)).
      p("\\\" expected\", ").p(PARSER).pln(");");
  }

  // ========================================================================

  /**
   * Return the name of the parser variable for the current nested
   * choice level.
   *
   * @return The nested choice parser variable.
   */
  protected String nestedChoice() {
    return NESTED_CHOICE + Integer.toString(choiceLevel);
  }

  /** Generate code for the specified ordered choice. */
  public void visit(OrderedChoice c) {
    String  base = baseParser;
    boolean used = useBaseParser;
    choiceLevel++;

    // For non-top-level choices, declare a parser variable and save
    // the current parser.
    if (0 != choiceLevel) {
      printer.pln();

      if (useBaseParser) {
        printer.indent().p("final ").p(cName).p(' ').p(nestedChoice()).
          p(" = ").p(base).pln(';');
      } else {
        printer.indent().p("final ").p(cName).p(' ').p(nestedChoice()).
          p(" = (").p(cName).p(')').p(resultName).pln(".parser;");
      }
    }

    // Process the options.
    Iterator optionIter   = c.options.iterator();
    int      optionNumber = 0;

    while (optionIter.hasNext()) {
      elementIter   = ((Sequence)optionIter.next()).elements.iterator();
      firstElement  = (0 == choiceLevel);
      baseParser    = (0 == choiceLevel)? "this" : nestedChoice();
      useBaseParser = true;
      seenTest      = false;
      optionNumber++;

      printer.pln();
      if (0 == choiceLevel) {
        printer.indent().p("// Option ").p(optionNumber).pln('.');
      } else {
        printer.indent().p("// Nested option ").p(optionNumber).pln('.');
      }

      nextElement();
    }

    choiceLevel--;
    useBaseParser = used;
    baseParser    = base;
  }

  // ========================================================================

  /** Generate code for the specified repetition. */
  public void visit(Repetition r) {
    firstElement = false;
    String  base = baseParser; 
    boolean used = useBaseParser;
    boolean once = repeatOnce;
    repeatOnce   = r.once;
    repetitionLevel++;

    // Save current parser.
    printer.pln();
    printer.indent().p(REPETITION).p(repetitionLevel).p(" = ");
    if (useBaseParser) {
      printer.p(base).pln(';');
    } else {
      printer.p('(').p(cName).p(')').p(resultName).pln(".parser;");
    }

    // Reset repeated flag if necessary.
    if (repeatOnce) {
      printer.indent().p(REPEATED).p(repetitionLevel).pln("   = false;");
    }

    // Save current code generation state.
    Iterator iter;
    if (predicate) {
      iter          = predicateIter;
      predicateIter = ((Sequence)r.element).elements.iterator();
    } else {
      iter          = elementIter;
      elementIter   = ((Sequence)r.element).elements.iterator();
    }

    // Emit code for the repeated elements.
    printer.indent().pln("while (true) {").incr();
    baseParser    = REPETITION + Integer.toString(repetitionLevel);
    useBaseParser = true;
    nextElement();
    printer.indent().pln("break;");
    printer.decr().indent().pln('}');

    // Restore code generation state.
    if (predicate) {
      predicateIter    = iter;
    } else {
      elementIter      = iter;
    }

    // Emit code for the rest of the current sequence.
    if (repeatOnce) {
      printer.pln();
      printer.indent().p("if (").p(REPEATED).p(repetitionLevel).pln(") {").
        incr();
    }
    repetitionLevel--;
    repeatOnce = once;

    baseParser    = REPETITION + Integer.toString(repetitionLevel + 1);
    useBaseParser = true;
    if (! r.once) {
      seenTest    = false;
    }
    nextElement();

    if (r.once) {
      printer.decr().indent().pln('}');
      tested();
    }
    baseParser    = base;
    useBaseParser = used;
  }

  // ========================================================================

  /** Generate code for the specified followed-by predicate. */
  public void visit(FollowedBy p) {
    if (predicate) {
      throw new IllegalStateException("Predicate within predicate");
    }

    predicate            = true;
    notFollowedBy        = false;
    savedFirstElement    = firstElement;
    savedBaseParser      = baseParser;
    if (! useBaseParser) {
      // Only set a new base parser if the base parser is not used for
      // the next element.
      baseParser         = "((" + cName + ")" + RESULT + ".parser)";
    }
    savedUseBaseParser   = useBaseParser;
    savedRepetitionLevel = repetitionLevel;
    useBaseParser        = true;
    resultName           = PRED_RESULT;
    predicateIter        = ((Sequence)p.element).elements.iterator();

    // Emit code for the followed-by predicate and the rest of the
    // rule sequence.
    nextElement();

    tested();
  }

  // ========================================================================

  /**
   * Determine whether we are processing a not-followed-by predicate.
   *
   * @return <code>true</code> if we are processing a not-followed-by
   * predicate.
   */
  protected boolean notFollowedBy() {
    return (predicate && notFollowedBy);
  }

  /** Generate code for the specified not-followed-by predicate. */
  public void visit(NotFollowedBy p) {
    if (predicate) {
      throw new IllegalStateException("Predicate within predicate");
    }

    predicate            = true;
    notFollowedBy        = true;
    savedFirstElement    = firstElement;
    savedBaseParser      = baseParser;
    if (! useBaseParser) {
      // Only set a new base parser if the base parser is not used for
      // the next element.
      baseParser         = "((" + cName + ")" + RESULT + ".parser)";
    }
    savedUseBaseParser   = useBaseParser;
    useBaseParser        = true;
    savedRepetitionLevel = repetitionLevel;
    resultName           = PRED_RESULT;
    predicateIter        = ((Sequence)p.element).elements.iterator();

    // Emit code for the not-followed-by predicate.
    printer.pln();
    printer.indent().p(MATCHED).pln(" = false;");

    nextElement();

    // Restore regular element processing.
    predicate     = false;
    firstElement  = savedFirstElement;
    baseParser    = savedBaseParser;
    useBaseParser = savedUseBaseParser;
    resultName    = RESULT;

    // Emit code for the rest of the rule sequence.
    printer.pln();
    printer.indent().p("if (! ").p(MATCHED).pln(") {").incr();

    nextElement();

    printer.decr().indent().pln("} else {").incr();
    parseError();
    printer.decr().indent().pln('}');

    tested();
  }

  // ========================================================================

  /** Generate code for the specified semantic predicate. */
  public void visit(SemanticPredicate p) {
    printer.pln().indent().p("if (");

    Action a = (Action)p.element;
    if (1 == a.code.size()) {
      printer.p((String)a.code.get(0)).pln(") {").incr();
    } else {
      boolean  first = true;
      Iterator iter  = a.code.iterator();
      while (iter.hasNext()) {
        if (first) {
          printer.p((String)iter.next()).incr();
          first = false;
        } else {
          printer.pln().indent().p((String)iter.next());
        }
        printer.pln(") {");
      }
    }

    nextElement();

    printer.decr().indent().pln('}');

    if (! notFollowedBy()) {
      endsWithParseError = true;
    }

    tested();
  }

  // ========================================================================

  /** Generate code for the specified binding. */
  public void visit(Binding b) {
    // Save old name and element.
    String  oldName    = bindingName;
    Element oldElement = bindingElement;

    // Set up new name and element;
    bindingName    = b.name;
    bindingElement = b.element;

    // Visit element.
    b.element.accept(this);

    // Restore old name and element.
    bindingName    = oldName;
    bindingElement = oldElement;
  }

  /**
   * Determine whether the current element has a binding.
   *
   * @return <code>true</code> if the current element has a binding.
   */
  protected boolean hasBinding() {
    return (null != bindingName);
  }

  /** Actually emit the code for the last visited binding. */
  protected void binding() {
    if (bindingElement instanceof NonTerminal) {
      String type = analyzer.lookup((NonTerminal)bindingElement).type;
      binding1(type, bindingName, type, resultName + ".semanticValue()");

    } else if (bindingElement instanceof CharTerminal) {
      if (VALUE.equals(bindingName)) {
        binding1(Type.charRefT(), bindingName, null,
                 "new Character(" + resultName + ".charValue())");
      } else {
        binding1(Type.charT(), bindingName, null, resultName + ".charValue()");
      }

    } else if (bindingElement instanceof StringLiteral) {
      binding1(Type.stringT(), bindingName, null,
               "\"" + Utilities.escape(((StringLiteral)bindingElement).text,
                                       Utilities.JAVA_ESCAPES) + "\"");

    } else if (bindingElement instanceof StringMatch) {
      binding1(Type.stringT(), bindingName, null,
               "\"" + Utilities.escape(((StringMatch)bindingElement).text,
                                       Utilities.JAVA_ESCAPES) + "\"");

    } else {
      throw new IllegalStateException("Unrecognized binding element " +
                                      bindingElement);
    }
  }

  /**
   * Emit the binding code.
   *
   * @param type The variable type.
   * @param name The variable name.
   * @param cast The cast type, or <code>null</code> for no cast.
   * @param expr The value producing expression.
   */
  private void binding1(String type, String name, String cast, String expr) {
    printer.indent();

    if (VALUE.equals(name)) {
      printer.p(VALUE).p(" = ");

    } else {
      if (attributeConstantBinding) {
        printer.p("final ");
      }
      printer.p(type).p(' ').p(name).p(" = ");
    }

    if (null != cast) {
      printer.p('(').p(cast).p(')');
    }

    printer.p(expr).pln(';');
  }

  /** Clear binding information after usage. */
  protected void clearBinding() {
    bindingName    = null;
    bindingElement = null;
  }

  // ========================================================================

  /** Generate code for the specified string match. */
  public void visit(StringMatch m) {
    final boolean first = firstElement;

    // At this point, the element of the string match must be a
    // nonterminal.
    NonTerminal nt = (NonTerminal)m.element;

    result(methodName(nt), ((! notFollowedBy()) && (! first)));
    valueTest(m.text);

    if (hasBinding()) {
      binding();
      clearBinding();
    }

    nextElement();

    if (notFollowedBy()) {
      printer.decr().indent().pln('}');
    } else if (attributeNoMatchingErrors || (Rats.optimizeErrors && first)) {
      printer.decr().indent().pln('}');
      endsWithParseError = true;
    } else {
      printer.decr().indent().pln("} else {").incr();
      parseError(m.text);
      printer.decr().indent().pln('}');
    }

    tested();
  }

  // ========================================================================

  /** Generate code for the specified nonterminal. */
  public void visit(NonTerminal nt) {
    result(methodName(nt), false);
    valueTest();

    if (hasBinding()) {
      binding();
      clearBinding();
    }

    nextElement();

    printer.decr().indent().pln('}');
    tested();
  }

  // ========================================================================

  /** Generate code for the any character element. */
  public void visit(AnyChar a) {
    result(PARSE_CHAR, false);
    valueTest();

    if (hasBinding()) {
      binding();
      clearBinding();
    }

    nextElement();

    printer.decr().indent().pln('}');

    if (! notFollowedBy()) {
      endsWithParseError = true;
    }

    tested();
  }
  
  // ========================================================================
  
  /** Generate code for the specified character literal. */
  public void visit(CharLiteral l) {
    result(PARSE_CHAR, false);
    valueTest();

    String name;
    if (hasBinding()) {
      binding();
      name = bindingName;
      clearBinding();
    } else {
      printer.indent().p(CHAR).p(" = ").p(resultName).pln(".charValue();");
      name = CHAR;
    }

    printer.pln();
    printer.indent().p("if (\'").escape(l.c, Utilities.JAVA_ESCAPES).
      p("\' == ").p(name).pln(") {").incr();

    nextElement();

    printer.decr().indent().pln('}');
    printer.decr().indent().pln('}');

    if (! notFollowedBy()) {
      endsWithParseError = true;
    }

    tested();
  }

  // ========================================================================

  /** Generate code for the specified character class. */
  public void visit(CharClass c) {
    result(PARSE_CHAR, false);
    valueTest();

    String name;
    if (hasBinding()) {
      binding();
      name = bindingName;
      clearBinding();
    } else {
      printer.indent().p(CHAR).p(" = ").p(resultName).pln(".charValue();");
      name = CHAR;
    }

    printer.pln();
    
    final int length = c.ranges.size();
    Iterator iter    = c.ranges.iterator();

    if (1 == length) {
      printer.indent().p("if ");
    } else {
      printer.indent().p("if (");
    }

    while (iter.hasNext()) {
      CharRange r = (CharRange)iter.next();

      if (c.exclusive) {
        if (r.first == r.last) {
          printer.p("(\'").escape(r.first, Utilities.JAVA_ESCAPES).p("\' != ").
            p(name).p(')');
        } else {
          printer.p('(').p(name).p(" < \'").
            escape(r.first, Utilities.JAVA_ESCAPES).p(") || (\'").
            escape(r.last, Utilities.JAVA_ESCAPES).p("\' < ").p(name).p("))");
        }

      } else {
        if (r.first == r.last) {
          printer.p("(\'").escape(r.first, Utilities.JAVA_ESCAPES).p("\' == ").
            p(name).p(')');
        } else {
          printer.p("((\'").escape(r.first, Utilities.JAVA_ESCAPES).p("\' <= ").
            p(name).p(") && (").p(name).p(" <= \'").
            escape(r.last, Utilities.JAVA_ESCAPES).p("\'))");
        }
      }

      if (iter.hasNext()) {
        if (c.exclusive) {
          printer.pln(" &&");
        } else {
          printer.pln(" ||");
        }
        printer.indent().p("    ");
      }
    }

    if (1 == length) {
      printer.pln(" {").incr();
    } else {
      printer.pln(") {").incr();
    }

    nextElement();

    printer.decr().indent().pln('}');
    printer.decr().indent().pln('}');

    if (! notFollowedBy()) {
      endsWithParseError = true;
    }

    tested();
  }

  // ========================================================================

  /** Generate code for the specified literal. */
  public void visit(StringLiteral l) {
    final boolean first  = firstElement;
    final int     length = l.text.length();

    for (int i=0; i<length; i++) {
      char c = l.text.charAt(i);

      result(PARSE_CHAR, ((0 == i) && (! notFollowedBy()) && (! first)));
      valueTest();
      printer.indent().p(CHAR).p(" = ").p(resultName).pln(".charValue();");
      printer.pln();
      printer.indent().p("if (\'").escape(c, Utilities.JAVA_ESCAPES).
        p("\' == ").p(CHAR).pln(") {").incr();
    }

    if (hasBinding()) {
      binding();
      clearBinding();
    }

    nextElement();

    for (int i=0; i<length; i++) {
      if (notFollowedBy()) {
        printer.decr().indent().pln('}');
        printer.decr().indent().pln('}');
      } else if (attributeNoMatchingErrors ||
                 (Rats.optimizeErrors && first)) {
        printer.decr().indent().pln('}');
        printer.decr().indent().pln('}');
        endsWithParseError = true;
      } else {
        printer.decr().indent().pln("} else {").incr();
        parseError(l.text);
        printer.decr().indent().pln('}');
        printer.decr().indent().pln("} else {").incr();
        parseError(l.text);
        printer.decr().indent().pln('}');
      }
    }

    tested();
  }

  // ========================================================================

  /** Generate code for the specified character switch. */
  public void visit(CharSwitch s) {
    result(PARSE_CHAR, false);
    valueTest();

    String name;
    if (hasBinding()) {
      binding();
      name = bindingName;
      clearBinding();
    } else {
      printer.indent().p(CHAR).p(" = ").p(resultName).pln(".charValue();");
      name = CHAR;
    }

    printer.pln();
    printer.indent().p("switch (").p(name).pln(") {").incr();

    Iterator iter = s.cases.iterator();
    while (iter.hasNext()) {
      CharCase c     = (CharCase)iter.next();
      Iterator iter2 = c.klass.ranges.iterator();
      while (iter2.hasNext()) {
        CharRange r  = (CharRange)iter2.next();

        for (char k=r.first; k<=r.last; k++) {
          printer.indentLess().p("case \'").escape(k, Utilities.JAVA_ESCAPES).
            pln("\':");
        }
      }

      if (null == c.element) {
        printer.indent().pln("/* No match. */");
        printer.indent().pln("break;");

      } else {
        printer.indent().p('{').incr();
        // The line terminator is printed by emitting code for
        // c.element.
        
        seenTest = false;
        
        if (c.element instanceof OrderedChoice) {
          c.element.accept(this);
        } else {
          elementIter = ((Sequence)c.element).elements.iterator();
          nextElement();
        }
        
        printer.decr().indent().pln('}');
        if (seenTest) {
          printer.indent().pln("break;");
        }
      }

      printer.pln();
    }

    if (null == s.base) {
      printer.indentLess().pln("default:");
      printer.indent().pln("/* No match. */");
    } else {
      printer.indentLess().pln("default:");
      printer.indent().p('{').incr();
      // The line terminator is printed by emitting code for s.base.
      if (s.base instanceof OrderedChoice) {
        s.base.accept(this);
      } else {
        elementIter = ((Sequence)s.base).elements.iterator();
        nextElement();
      }
      printer.decr().indent().pln('}');
    }

    printer.decr().indent().pln('}');
    printer.decr().indent().pln('}');

    endsWithParseError = true;
    tested();
  }

  // ========================================================================

  /** Actually emit code for the specified action. */
  protected void action(Action a) {
    Iterator iter = a.code.iterator();
    while (iter.hasNext()) {
      printer.indent().pln(iter.next().toString());
    }
  }

  /** Generate code for the specified action. */
  public void visit(Action a) {
    printer.pln();
    action(a);

    nextElement();
  }

  // ========================================================================

  /** Generate code for the specified null value. */
  public void visit(NullValue v) {
    printer.pln();
    printer.indent().p(VALUE).pln(" = null;");

    nextElement();
  }

  /** Generate code for the specified string value. */
  public void visit(StringValue v) {
    printer.pln();
    printer.indent().p(VALUE).p(" = \"").
      escape(v.text, Utilities.JAVA_ESCAPES).pln("\";");

    nextElement();
  }

  /** Generate code for the specified text value. */
  public void visit(TextValue v) {
    if (predicate) {
      throw new IllegalStateException("Text value within predicate");
    }

    printer.pln();
    if (firstElement) {
      printer.indent().p(VALUE).pln(" = \"\";");
    } else if (useBaseParser) {
      printer.indent().p(VALUE).p(" = getDifference(").p(baseParser).pln(");");
    } else {
      printer.indent().p(VALUE).p(" = getDifference(").p(RESULT).
        pln(".parser);");
    }

    nextElement();
  }

  /** Generate code for the specified empty list value. */
  public void visit(EmptyListValue v) {
    printer.pln();
    printer.indent().p(VALUE).pln(" = Pair.EMPTY;");

    nextElement();
  }

  /** Generate code for the specified singleton list value. */
  public void visit(SingletonListValue v) {
    printer.pln();
    printer.indent().p(VALUE).p(" = new Pair(").p(v.value).pln(");");

    nextElement();
  }

  /** Generate code for the specified list value. */
  public void visit(ListValue v) {
    printer.pln();
    printer.indent().p(VALUE).p(" = new Pair(").p(v.value).p(", ").p(v.list).
      pln(");");

    nextElement();
  }

}
