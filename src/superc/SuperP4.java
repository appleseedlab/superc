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
package superc;
import java.lang.reflect.*;

import java.lang.StringBuilder;
import java.nio.Buffer;
import java.io.File;
import java.io.Reader;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.StringReader;
import java.io.OutputStreamWriter;
import java.io.IOException;

import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.Stack;

import superc.core.Lexer;
import superc.core.LexerCreator;
import superc.core.TokenCreator;
import superc.core.HeaderFileManager;
import superc.core.MacroTable;
import superc.core.ExpressionParser;
import superc.core.ConditionEvaluator;
import superc.core.StopWatch;
import superc.core.StreamTimer;
import superc.core.Preprocessor;
import superc.core.TokenFilter;
import superc.core.ForkMergeParser;
import superc.core.SemanticValues;
import superc.core.DirectiveParser;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.Clauses;

import superc.core.Syntax;
import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;
import superc.core.Syntax.Error;
import superc.core.Syntax.ErrorType;

import superc.expression.ExpressionRats;

import superc.p4parser.P4ParseTables;
import superc.p4parser.P4Values;
import superc.p4parser.P4Actions;
import superc.p4parser.P4Context;
import superc.p4parser.P4LexerCreator;
import superc.p4parser.P4TokenCreator;

import superc.p4parser.GraphViz;
// import static guru.nidi.graphviz.model.Factory.*;
import superc.p4parser.CallGraphGenerator;

import superc.p4parser.P4Context.SymbolTable.STField;

import xtc.tree.Node;
import xtc.tree.GNode;
import xtc.tree.Location;

import xtc.Constants;

import xtc.util.Tool;
import xtc.util.Pair;

import xtc.lang.CParser;

import xtc.parser.Result;
import xtc.parser.ParseException;

import net.sf.javabdd.BDD;

import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;
import org.sat4j.specs.ContradictionException;
import org.sat4j.specs.IProblem;
import org.sat4j.specs.ISolver;
import org.sat4j.specs.TimeoutException;
import org.sat4j.tools.ModelIterator;

/**
 * The SuperC configuration-preserving preprocessor and parsing.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.130 $
 */
public class SuperP4 extends Tool {
  /** The user defined include paths */
  List<String> I;
  
  /** Additional paths for quoted header file names */
  List<String> iquote;
  
  /** Additional paths for system headers */
  List<String> sysdirs;
  
  /** Command-line macros and includes */
  StringReader commandline;

  /** Plug-in to create a new lexer for a given parser. */
  private final static LexerCreator lexerCreator = new P4LexerCreator();

  /** Preprocessor support for token-creation. */
  private final static TokenCreator tokenCreator = new P4TokenCreator();

  /** Simplify nested conditionals in preprocessor output. */
  private final static boolean SIMPLIFY_NESTED_CONDITIONALS = true;

  HashSet set = new HashSet<>();
  ArrayList<String> blockValues = new ArrayList<String>();
  HashMap<String, String> template_block_map = new HashMap<>();
  HashMap<String, HashSet<String>> conditionalsInsideSpecificBlosk;
  HashMap<String, HashSet<String>> conditionalsInsideEverything = new HashMap<>();
  int counter = 0;
  /** Create a new tool. */
  public SuperP4() { /* Nothing to do. */ }

  /**
   * Return the name of this object.
   * 
   * @return The name of this object.
   */
  public String getName() {
    return "SuperP4";
  }


  /**
   * Return a copy of the Constants used.
   * 
   * @return The copy of the Constants.
   */
  public String getCopy() {
    return "(C) 2009-2012 New York University\n"
      + "Portions Copyright (c) 1989, 1990 James A. Roskind";
  }


  public String getExplanation() {
    return
      "By default, SuperP4 performs all optimizations besides " +
      "platoffOrdering.  If one or more " +
      "individual optimizations are specified as command line flags, all " +
      "other optimizations are automatically disabled.";
  }

  public void init() {
    super.init();
    
    runtime.
      // Regular preprocessor arguments.
      word("I", "I", true,
           "Add a directory to the header file search path.").
      word("isystem", "isystem", true,
           "Add a system directory to the header file search path.").
      word("iquote", "iquote", true,
           "Add a quote directory to the header file search path.").
      bool("nostdinc", "nostdinc", false,
           "Don't use the standard include paths.").
      word("D", "D", true, "Define a macro.").
      word("U", "U", true, "Undefine a macro.  Occurs after all -D arguments "
           + "which is a departure from gnu cpp.").
      word("include", "include", true, "Include a header.").
      
      // Extra preprocessor arguments.
      bool("nobuiltins", "nobuiltins", false,
           "Disable gcc built-in macros.").
      bool("nocommandline", "nocommandline", false,
           "Do not process command-line defines (-D), undefines (-U), or " +
           "includes (-include).  Useful for testing the preprocessor.").
      word("mandatory", "mandatory", false,
           "Include the given header file even if nocommandline is on.").
      word("restrictConfigToPrefix", "restrictConfigToPrefix", false,
           "Assume non-config free macros are false when used like "
           + "configuration variables, but keep them free in the macro table").
      word("restrictFreeToPrefix", "restrictFreeToPrefix", false,
           "Restricts free macros to those that have the given prefix").
      bool("singleConfigSysheaders", "singleConfigSysheaders", false,
           "Disables configuration-awareness inside of system headers.").

      // SuperC component selection.
      bool("E", "E", false,
           "Just do configuration-preserving preprocessing.").
      bool("lexer", "lexer", false,
           "Just do lexing and print out the tokens.").
      bool("lexerNoPrint", "lexerNoPrint", false,
           "Lex but don't print.").
      bool("directiveParser", "directiveParser", false,
           "Just do lexing and directive parsing and print out the tokens.").
      bool("preprocessor", "preprocessor", false,
           "Preprocess but don't print.").
      bool("follow-set", "follow-set", false,
           "Compute the FOLLOW sets of each token in the preprocessed input.").

      // // Desugarer component selection
      // bool("desugar", "desugarer", false,
      //      "Run the desugarer.").

      // Preprocessor optimizations.
      /*bool("Odedup", "optimizeDedup", false,
        "Turn off macro definition deduplication.  Not recommended " +
        "except for analysis.")*/

      // FMLR algorithm optimizations.
      bool("Onone", "doNotOptimize", false,
           "Turn off all optimizations, but still use the follow-set.").
      bool("Oshared", "optimizeSharedReductions", true,
           "Turn on the \"shared reductions\" optimization.").
      bool("Olazy", "optimizeLazyForking", true,
           "Turn on the \"lazy forking\" optimization.").
      bool("Oearly", "optimizeEarlyReduce", true,
           "Turn on the \"early reduce\" optimization.").

      // Platoff ordering has no effect with the other optimizations.
      bool("platoffOrdering", "platoffOrdering", false,
           "Turn on the Platoff ordering optimization.  Off by default.").

      // Deoptimize with early shifts.
      bool("earlyShift", "earlyShift", false,
           "Deoptimize FMLR by putting shifts first.  Incompatible with " +
           "early reduce.").

      // Other optimizations.
      bool("noFollowCaching", "noFollowCaching", false,
           "Turn off follow-set caching.  On by default.").

      // New error handling.
      bool("newErrorHandling", "newErrorHandling", false,
           "Use new error handling that puts errors in the AST.").

      // Naive FMLR.
      bool("naiveFMLR", "naiveFMLR", false,
           "Naive FMLR Turn off all optimizations and don't "
           + "use the follow-set.").

      // Subparser explosion kill switch.
      word("killswitch", "killswitch", false,
           "Stop parsing if subparser set reaches or exceeds the given size. "
           + "This protects against subparser exponential explosion.  An "
           + "error message will be reported.").

      // Type checking and analysis
      bool("checkers", "checkers", false,
           "Turn on semantic checkers.").
      word("featureModel", "featureModel", false,
           "Specify a feature model to use when finding satisfiable bugs.").
      word("modelAssumptions", "modelAssumptions", false,
           "Specify model assumptions to feed the sat solver,e.g., "
           + "unselectable config vars.").
      bool("symbolTable", "symbolTable", false,
           "Print the symbolTable.").
      bool("functionAnalysis", "functionAnalysis", false,
           "Print function definitions, calls, and unresolved calls.  Function "
           + "definitions conditions are already negated for easier bug-finding."). 
      bool("printErrorConditions", "printErrorConditions", false,
           "Print error directive presence conditions, negated for easier use.").
      word("extraConstraints", "extraConstraints", false,
           "Add extra constraints to add to the featureModel.  One per line in "
           + "CNF-style format, e.g., from printErrorConditions.").
      bool("keepErrors", "keepErrors", false,
           "Pass preprocessor error tokens to the parser.  Makes for more "
           + "specific presence conditions.").

      // Statistics, analyses, and timing.
      bool("preprocessorStatistics", "statisticsPreprocessor", false,
           "Dynamic analysis of the preprocessor.").
      bool("languageStatistics", "statisticsLanguage", false,
           "Dynamic analysis of the language usage.").
      bool("parserStatistics", "statisticsParser", false,
           "Parser statistics.").
      bool("configurationVariables", "configurationVariables", false,
           "Report a list of all configuration variables.  A configuration " +
           "variable is a macro used in a conditional expression before or " +
           "without being defined").
      bool("headerGuards", "headerGuards", false,
           "Report a list of all header guard macros.  Header guards are " +
           "found with gcc's idiom: #ifndef MACRO\\n#define MACRO\\n...\\n" +
           "#endif.").
      bool("size", "size", false,
           "Report the size, in bytes, of the compilation unit.  This is " +
           "the size of the main file plus the size of all headers " +
           "for every time each header is included.").
      bool("time", "time", false,
           "Running time in milliseconds broken down: " +
           "(1) lexer, (2) preprocessor and lexer, and " +
           "(3) parser, preprocessor and lexer.").
      bool("presenceConditions", "presenceConditions", false,
           "Show presence conditions for each static conditional.").
      word("headerChain", "headerChain", true,
           "Find, if any, the chain of includes to reach the given header.").
      bool("conditionConfigs", "conditionConfigs", false,
           "Show configs for each static conditional.").
      bool("conditionGranularity", "conditionGranularity", false,
           "Show configs for each static conditional.").

      // Validation
      bool("checkExpressionParser", "checkExpressionParser", false,
           "Check SuperC's expression parser against Rats!'").
      bool("checkAST", "checkAST", false,
           "Check SuperC's C AST against Rats!'").

      // Output and debugging
      bool("printAST", "printAST", false,
           "Print the parsed AST.").
      bool("preprocessorUsageMatrix", "preprocessorUsageMatrix", false,
           "Print intersection matrix of grammar constructs and preprocessor present inside each construct.").
      word("templateFileForMatrix", "templateFileForMatrix", true,
           "Path to text file containing the blocks names in the main package instantiation..").
      bool("callGraph", "callGraph", false,
           "Print Call graph image").
      bool("printSource", "printSource", false,
           "Print the parsed AST in C source form.").
      bool("suppressConditions", "suppressConditions", false,
           "Do not print presence conditions to save space.").
      bool("configureAllYes", "configureAllYes", false,
           "Print all tokens of the all yes configuration of the AST.").
      bool("configureAllNo", "configureAllNo", false,
           "Print all tokens of the all no configuration of the AST.").
      word("configureExceptions", "configureExceptions", false,
           "Add exceptions to the all yes or no configuration.").
      word("configFile", "configFile", false,
           "Add exceptions to the all yes configuration via a linux .config file.").
      /*bool("showCPresenceCondition", "showCPresenceCondition", false,
        "Show scope changes and identifier bindings.").*/
      /*bool("traceIncludes", "traceInclude", false,
        "Show every header entrance and exit.").*/
      bool("hideErrors", "hideErrors", false,
           "Hide preprocessing and parsing errors in standard err.").
      bool("showAccepts", "showAccepts", false,
           "Emit ACCEPT messages when a subparser accepts input.").
      bool("showActions", "showActions", false,
           "Show all parsing actions.").
      bool("showFM", "showFM", false,
           "Show all forks and merges.").
      bool("showHeaders", "showHeaders", false,
           "Show header entry and exit.").
      bool("showLookaheads", "showLookaheads", false,
           "Show lookaheads on each parse loop (warning: very voluminous "
           + "output!)").
      bool("macroTable", "macroTable", false,
           "Show the macro symbol table.").
      bool("macroDependencies", "macroDependencies", false,
      "Show which macros depend on free macros")
      ;
  }
  
  /**
   * Prepare for file processing.  Build header search paths.
   * Include command-line headers. Process command-line and built-in macros.
   */
  public void prepare() {
    // Configure optimizations options.
    boolean explicitOptimizations = runtime.hasPrefixValue("optimize");
    boolean doNotOptimize
      = runtime.hasValue("doNotOptimize")
      && runtime.test("doNotOptimize");
    boolean naiveFMLR
      = runtime.hasValue("naiveFMLR")
      && runtime.test("naiveFMLR");

    // Check optimization options.
    if (explicitOptimizations && doNotOptimize) { 
      runtime.error("no optimizations incompatible with explicitly specified " +
                    "optimizations");
    }
    
    if (naiveFMLR && (explicitOptimizations || doNotOptimize)) {
      runtime.error("naive FMLR is incompatible with all optimizations and "
                    + "with Onone because it does not use the follow set.");
    }

    // Check configure options
    if (runtime.hasValue("configureAllYes") && runtime.test("configureAllYes") &&
        runtime.hasValue("configureAllNo") && runtime.test("configureAllNo")) {
      runtime.error("pick either configureAllYes or configureAllNo, but not " +
                    "both");
    }

    // Now, fill in the defaults.
    if (explicitOptimizations || doNotOptimize || naiveFMLR) {
      runtime.initFlags("optimize", false);
    }

    // Set the command-line argument defaults.
    runtime.initDefaultValues();


    if (runtime.test("optimizeEarlyReduce") && runtime.test("earlyShift")) {
      runtime.error("Cannot have both early reduce and early shift.");
    }


    // Use the Java implementation of JavaBDD. Setting it here means
    // the user doesn't have to set it on the commandline.
    System.setProperty("bdd", "java");

    // Get preprocessor settings.
    iquote = new LinkedList<String>();
    I = new LinkedList<String>();
    sysdirs = new LinkedList<String>();

    // The following shows which command-line options add to ""
    // headers and which add to <> headers.  Additionally, only
    // -isystem are considered system headers.  System headers have a
    // special marker to cpp, but SuperC does not need to use this.

    // currentheaderdirectory iquote I    isystem standardsystem
    // ""                     ""     ""   ""     ""
    //                               <>   <>     <>
    //                                    marked system headers 
    if (!runtime.test("nostdinc")) {
      for (int i = 0; i < Builtins.sysdirs.length; i++) {
        sysdirs.add(Builtins.sysdirs[i]);
      }
    }
    
    for (Object o : runtime.getList("isystem")) {
      if (o instanceof String) {
        String s;
        
        s = (String) o;
        if (sysdirs.indexOf(s) < 0) {
          sysdirs.add(s);
        }
      }
    }

    for (Object o : runtime.getList("I")) {
      if (o instanceof String) {
        String s;

        s = (String) o;

        // Ignore I if already a system path.
        if (sysdirs.indexOf(s) < 0) {
          I.add(s);
        }
      }
    }
    
    for (Object o : runtime.getList("iquote")) {
      if (o instanceof String) {
        String s;
        
        s = (String) o;
        // cpp permits bracket and quote search chains to have
        // duplicate dirs.
        if (iquote.indexOf(s) < 0) {
          iquote.add(s);
        }
      }
    }

    // Make one large file for command-line/builtin stuff.
    StringBuilder commandlinesb;

    commandlinesb = new StringBuilder();
    
    if (! runtime.test("nobuiltins")) {
      commandlinesb.append(Builtins.builtin);
    }
    
    if (! runtime.test("nocommandline")) {
      for (Object o : runtime.getList("D")) {
        if (o instanceof String) {
          String s, name, definition;
          
          s = (String) o;
          
          // Truncate at first newline according to gcc spec.
          if (s.indexOf("\n") >= 0) {
            s = s.substring(0, s.indexOf("\n"));
          }
          if (s.indexOf("=") >= 0) {
            name = s.substring(0, s.indexOf("="));
            definition = s.substring(s.indexOf("=") + 1);
          }
          else {
            name = s;
            // The default for command-line defined guard macros.
            definition = "1";
          }
          commandlinesb.append("#define " + name + " " + definition + "\n");
        }
      }
      
      for (Object o : runtime.getList("U")) {
        if (o instanceof String) {
          String s, name, definition;
          
          s = (String) o;
          // Truncate at first newline according to gcc spec.
          if (s.indexOf("\n") >= 0) {
            s = s.substring(0, s.indexOf("\n"));
          }
          name = s;
          commandlinesb.append("#undef " + name + "\n");
        }
      }
      
      for (Object o : runtime.getList("include")) {
        if (o instanceof String) {
          String filename;
          
          filename = (String) o;
          commandlinesb.append("#include \"" + filename + "\"\n");
        }
      }
    }
    
    if (null != runtime.getString("mandatory")
        && runtime.getString("mandatory").length() > 0) {
      commandlinesb.append("#include \"" + runtime.getString("mandatory")
                           + "\"\n");
    }
    
    if (commandlinesb.length() > 0) {
      commandline = new StringReader(commandlinesb.toString());

    } else {
      commandline = null;
    }
  }

  public Node parse(Reader in, File file) throws IOException, ParseException {
    HeaderFileManager fileManager;
    MacroTable macroTable;
    PresenceConditionManager presenceConditionManager;
    ExpressionParser expressionParser;
    ConditionEvaluator conditionEvaluator;
    Iterator<Syntax> preprocessor;
    Node result = null;
    StopWatch parserTimer = null, preprocessorTimer = null, lexerTimer = null;

    if (runtime.test("time")) {
      parserTimer = new StopWatch();
      preprocessorTimer = new StopWatch();
      lexerTimer = new StopWatch();

      parserTimer.start();
    }

    if (runtime.test("lexer")
        || runtime.test("lexerNoPrint")
        || runtime.test("directiveParser")) {
      // Just do lexing and/or directive parsing, print the tokens and
      // quit if these options are selected.
      final Lexer clexer = lexerCreator.newLexer(in);
      clexer.setFileName(file.getName());

      Iterator<Syntax> stream = new Iterator<Syntax>() {
          Syntax syntax;
    
          public Syntax next() {
            try {
              syntax = clexer.yylex();
            } catch (IOException e) {
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

      if (runtime.test("directiveParser")) {
        stream = new DirectiveParser(stream, file.getName());
      }

      Syntax syntax = stream.next();

      while (syntax.kind() != Kind.EOF) {
        if (! runtime.test("lexerNoPrint")) {
          System.out.print(syntax.toString());
        }
        syntax = stream.next();
      }

      return null;
    }

    // Initialize the preprocessor with built-ins and command-line
    // macros and includes.
    macroTable = new MacroTable(tokenCreator);
    macroTable
      .getConfigurationVariables(runtime.test("configurationVariables") || 
                                 runtime.test("macroDependencies"));
    macroTable.getHeaderGuards(runtime.test("headerGuards"));
    presenceConditionManager = new PresenceConditionManager();
    if (runtime.test("suppressConditions")) {
      presenceConditionManager.suppressConditions(true);
    }
    // if (runtime.test("checkExpressionParser")) {
    //   expressionParser = ExpressionParser.comparator(presenceConditionManager);
    // } else {
    //   // expressionParser = ExpressionParser.fromSuperC(presenceConditionManager);
      expressionParser = ExpressionParser.fromRats();
    // }
    conditionEvaluator = new ConditionEvaluator(expressionParser,
                                                presenceConditionManager,
                                                macroTable);
    if (null != runtime.getString("restrictFreeToPrefix")) {
      macroTable.restrictPrefix(runtime.getString("restrictFreeToPrefix"));
      conditionEvaluator.restrictPrefix(runtime.getString("restrictFreeToPrefix"));
    }

    if (null != runtime.getString("restrictConfigToPrefix")) {
      // let macros be free!  only restrict them when encountered in a
      // conditional
      conditionEvaluator.restrictPrefix(runtime.getString("restrictConfigToPrefix"));
    }

    if (null != commandline) {
      Syntax syntax;
      
      try {
        commandline.reset();
      }
      catch (Exception e) {
        e.printStackTrace();
      }

      fileManager = new HeaderFileManager(commandline,
                                          new File("<command-line>"),
                                          iquote, I, sysdirs,
                                          lexerCreator, tokenCreator,
                                          lexerTimer);
      fileManager.showHeaders(runtime.test("showHeaders"));
      fileManager.collectStatistics(runtime.test("statisticsPreprocessor"));
      fileManager.showErrors(! runtime.test("hideErrors"));
      fileManager.doTiming(runtime.test("time"));
      preprocessor = new Preprocessor(fileManager,
                                      macroTable,
                                      presenceConditionManager,
                                      conditionEvaluator,
                                      tokenCreator);
      ((Preprocessor) preprocessor)
        .collectStatistics(runtime.test("statisticsPreprocessor"));
      ((Preprocessor) preprocessor)
        .showErrors(! runtime.test("hideErrors"));
      ((Preprocessor) preprocessor)
        .singleConfigurationSysheaders(runtime.test("singleConfigSysheaders"));
      if (runtime.test("time")) {
        preprocessor = new StreamTimer<Syntax>(preprocessor, preprocessorTimer);
      }

      do {
        syntax = preprocessor.next();
      } while (syntax.kind() != Kind.EOF);
      
      commandline = null;
    }
    fileManager = new HeaderFileManager(in, file, iquote, I, sysdirs,
                                        lexerCreator, tokenCreator, lexerTimer,
                                        runtime.getString(xtc.util.Runtime.INPUT_ENCODING));
    System.err.println("Parsing file: " + file.getName());
    fileManager.showHeaders(runtime.test("showHeaders"));
    fileManager.collectStatistics(runtime.test("statisticsPreprocessor"));
    fileManager.showErrors(! runtime.test("hideErrors"));
    fileManager.doTiming(runtime.test("time"));

    if (null != runtime.getList("headerChain")) {
      List<String> h = new LinkedList<String>();
      for (Object o : runtime.getList("headerChain")) {
        if (o instanceof String) {
          h.add((String) o);
        }
      }
      fileManager.showHeaderChains(h);
    }

    preprocessor = new Preprocessor(fileManager,
                                    macroTable,
                                    presenceConditionManager,
                                    conditionEvaluator,
                                    tokenCreator);
    
    ((Preprocessor) preprocessor)
      .collectStatistics(runtime.test("statisticsPreprocessor"));
    ((Preprocessor) preprocessor)
      .showErrors(! runtime.test("hideErrors"));
    ((Preprocessor) preprocessor)
      .singleConfigurationSysheaders(runtime.test("singleConfigSysheaders"));
    ((Preprocessor) preprocessor)
      .showPresenceConditions(runtime.test("presenceConditions"));
    ((Preprocessor) preprocessor)
      .showConditionConfigs(runtime.test("conditionConfigs"));

    List<PresenceCondition> printConstraints = ((Preprocessor) preprocessor)
      .printErrorConditions(runtime.test("printErrorConditions"));

    List<String> errorConstraints = new ArrayList<String>();
    ((Preprocessor) preprocessor)
      .saveErrorConstraints(errorConstraints);

    if (runtime.test("time")) {
      preprocessor = new StreamTimer<Syntax>(preprocessor, preprocessorTimer);
    }
      
    // Run SuperC.
    if (runtime.test("follow-set")) {
      // Compute the follow-set of each token of the preprocessed
      // input.

      // Initialize a parser to use it's follow-set method and ordered
      // syntax class.
      P4Context initialParsingContext = new P4Context();
      initialParsingContext
        .collectStatistics(runtime.test("statisticsLanguage"));
      P4Actions actions = P4Actions.getInstance();
      actions.collectStatistics(runtime.test("statisticsLanguage"));
      ForkMergeParser parser
        = new ForkMergeParser(P4ParseTables.getInstance(),
                              P4Values.getInstance(), actions,
                              initialParsingContext, preprocessor,
                              presenceConditionManager);
      initialParsingContext.free();

      // Initialize the the token stream.  Only pass ordinary tokens
      // and conditionals to the follow-set.
      preprocessor = new TokenFilter(preprocessor);

      ForkMergeParser.OrderedSyntax ordered
        = parser.new OrderedSyntax(preprocessor);

      // A stack of presence conditions.  Used to store the presence
      // conditions of nested conditionals.
      LinkedList<PresenceCondition> presenceConditions = new LinkedList<PresenceCondition>();

      presenceConditions.addLast(presenceConditionManager.newTrue());

      // Read each token from the token stream until EOF.
      while (true) {
        ordered = ordered.getNext();
        Syntax syntax = ordered.syntax;

        // The presence condition of the current token.  For
        // conditionals, it the presence condition of their parent
        // conditional branch (or true if they are at the top-level of
        // the source code.
        PresenceCondition presenceCondition;

        // Print the token.
        System.out.print("SYNTAX " + syntax.toString().trim());

        if (syntax.kind() == Kind.CONDITIONAL) {
          // Update the presence condition.
          Conditional conditional = syntax.toConditional();

          switch (conditional.tag()) {
          case START:
            presenceCondition = presenceConditions.getLast();
            presenceConditions.addLast(conditional.presenceCondition);
            break;

          case NEXT:
            presenceConditions.removeLast();
            presenceCondition = presenceConditions.getLast();
            presenceConditions.addLast(conditional.presenceCondition);
            break;

          case END:
            presenceConditions.removeLast();
            presenceCondition = presenceConditions.getLast();
            break;

          default:
            throw new UnsupportedOperationException();
          }
        } else {
          // Print the presence condition.
          presenceCondition = presenceConditions.getLast();
          System.out.print(" ::: " + presenceConditions.getLast().toString());
        }
        System.out.print("\n");

        // Print the follow set.
        if (syntax.kind() == Kind.LANGUAGE
            || syntax.kind() == Kind.EOF
            || syntax.kind() == Kind.CONDITIONAL
            && syntax.toConditional().tag() == ConditionalTag.START) {

          Map<Integer, ForkMergeParser.Lookahead> follow
            = parser.follow(ordered, presenceCondition.addRef());

          presenceCondition.delRef();

          System.out.print("FOLLOW [\n");
          for (Integer i : follow.keySet()) {
            ForkMergeParser.Lookahead l = follow.get(i);

            System.out.println("  " + l.token.syntax.toString() + " ::: "
                               + l.presenceCondition);
          }
          System.out.print("]\n\n");
        } else {
          System.out.print("\n");
        }

        if (syntax.kind() == Kind.EOF) break;
      }
    } else if (runtime.test("E") || runtime.test("preprocessor")) {
      // Run the SuperC preprocessor only.
      Syntax syntax;
      boolean seenNewline = true;
      
      syntax = preprocessor.next();

      LinkedList<PresenceCondition> parents
        = new LinkedList<PresenceCondition>();

      parents.push(presenceConditionManager.newTrue());
      while (syntax.kind() != Kind.EOF) {
        if (! runtime.test("statisticsPreprocessor")
            && ! runtime.test("preprocessor")) {
          if (syntax.kind() == Kind.LANGUAGE
              || syntax.kind() == Kind.LAYOUT
              || syntax.kind() == Kind.CONDITIONAL
              || (syntax.kind() == Kind.DIRECTIVE
                  && syntax.toDirective().tag() == DirectiveTag.LINEMARKER)
              || syntax.kind() == Kind.ERROR) {

            // Add a newline before a conditional directive or a
            // linemarker to mimic correct preprocessor directive
            // usage.
            if ((syntax.kind() == Kind.CONDITIONAL
                 || syntax.kind() == Kind.DIRECTIVE
                 || syntax.kind() == Kind.ERROR)
                && ! seenNewline) {
              System.out.print("\n");
              seenNewline = true;
            }

            if (syntax.testFlag(Preprocessor.PREV_WHITE)) {
              System.out.print(" ");
            } else {
              System.out.print(" ");
            }

            // if (SIMPLIFY_NESTED_CONDITIONALS
            //     && syntax.kind() == Kind.CONDITIONAL) {
            //   switch (syntax.toConditional().tag()) {
            //   case START:
            //     PresenceCondition restrict1 = syntax.toConditional()
            //       .presenceCondition.simplify(parents.peek());
            //     parents.push(syntax.toConditional().presenceCondition.addRef());
            //     System.out.print(new Conditional(ConditionalTag.START,
            //                                      restrict1));
            //     break;

            //   case NEXT:
            //     parents.pop().delRef();
            //     PresenceCondition restrict2 = syntax.toConditional()
            //       .presenceCondition.simplify(parents.peek());
            //     parents.push(syntax.toConditional().presenceCondition.addRef());
            //     System.out.print(new Conditional(ConditionalTag.NEXT,
            //                                      restrict2));
            //     break;

            //   case END:
            //     parents.pop().delRef();
            //     System.out.print(syntax);
            //     break;
            //   }
            // } else {
              System.out.print(syntax);
            // }
            
            // Keep track of whether we have seen a newline already.
            if (syntax.kind() == Kind.LAYOUT && ((Layout) syntax).hasNewline()
                && syntax.getTokenText().endsWith("\n")) {
              seenNewline = true;
            } else if (syntax.kind() == Kind.CONDITIONAL
                       || syntax.kind() == Kind.DIRECTIVE) {
              System.out.print("\n");
              seenNewline = true;
            } else {
              seenNewline = false;
            }
          }
        }
        
        if (syntax.kind() == Kind.CONDITIONAL
            && ( syntax.toConditional().tag == ConditionalTag.START
                 || syntax.toConditional().tag == ConditionalTag.NEXT)) {
          syntax.toConditional().presenceCondition.delRef();
        }

        syntax = preprocessor.next();
      }
    // } else if (runtime.test("desugarer")) {
    } else {
      // Run the SuperC preprocessor and parser.
      ForkMergeParser parser;
      Object translationUnit;
      
      // Only pass ordinary tokens and conditionals to the parser.
      preprocessor = new TokenFilter(preprocessor, runtime.test("keepErrors"));

      // Create a new semantic values class for C.
      SemanticValues semanticValues;
      if (runtime.test("statisticsLanguage")) {
        // Modify the semantic values class to collect statistics on C
        // statements and declarations.
        final HashSet<String> trackedProductions = new HashSet<String>();

        // Statement and ExternalDeclaration are marked passthrough,
        // so we won't see them.  Instead look for their children.
        trackedProductions.add("Declaration");
        trackedProductions.add("LabeledStatement");    // Statements
        trackedProductions.add("CompoundStatement");
        trackedProductions.add("ExpressionStatement");
        trackedProductions.add("SelectionStatement");
        trackedProductions.add("IterationStatement");
        trackedProductions.add("JumpStatement");
        trackedProductions.add("AssemblyStatement");
        trackedProductions.add("FunctionDefinition");  // ExternalDeclarations
        trackedProductions.add("AssemblyDefinition");
        trackedProductions.add("EmptyDefinition");

        semanticValues = new P4Values() {
            public Object getValue(int id, String name, Pair<Object> values) {
              Object value = super.getValue(id, name, values);

              if (trackedProductions.contains(name)) {
                // Get the location of the production.
                Location location = getProductionLocation(value);

                // Emit the marker.
                runtime.errConsole().pln(String.format("c_construct %s %s",
                                                       name, location)).flush();
              }

              return value;
            }
          };
      } else {
        semanticValues = P4Values.getInstance();
      }

      P4Actions actions = P4Actions.getInstance();
      actions.collectStatistics(runtime.test("statisticsLanguage"));
      actions.enableCheckers(runtime.test("checkers"), errorConstraints);
      if (runtime.test("functionAnalysis")) {
        actions.enableFunctionAnalysis();
      }
      if (runtime.test("checkers") && runtime.getString("featureModel") != null) {
        // convert kconfig model to clauses for sat solver
        Clauses clauses = new Clauses();

        {
          BufferedReader br =
            new BufferedReader(new FileReader(runtime.getString("featureModel")));
          String line = br.readLine();
          while (null != line) {
            StringReader reader = new StringReader(line);
            ExpressionRats clauseParser
              = new ExpressionRats(reader, "CLAUSE", line.length());

            Result clauseTree;
            Node tree = null;
            try {
              clauseTree = clauseParser.pConstantExpression(0);
              // tree = (Node) clauseParser.value(clauseTree);
              if (! clauseTree.hasValue()) {
                tree = null;
                System.err.println(clauseParser.format(clauseTree.parseError()));
              } else {
                tree = clauseTree.semanticValue();
              }
              // System.err.println(tree);
            } catch (java.io.IOException e ) {
              e.printStackTrace();
              throw new RuntimeException("couldn't parse expression");
            }

            if (null != tree) {
              clauses.addClause(tree);
            }

            line = br.readLine();
          }
        }

        if (runtime.getString("extraConstraints") != null) {
          BufferedReader br =
            new BufferedReader(new FileReader(runtime.getString("extraConstraints")));
          String line = br.readLine();
          while (null != line) {
            if (line.startsWith("extra_constraint ")) {
              String[] s = line.split(" ");
              System.err.println(line + s);
              if (s.length > 1) {
                System.err.println("adding extra constraint " + s[1]);
                clauses.addClauses(s[1]);
              }
            }
            line = br.readLine();
          }
        }

        List<Integer> assumptions = new ArrayList<Integer>();
        if (runtime.getString("modelAssumptions") != null) {
          BufferedReader br =
            new BufferedReader(new FileReader(runtime.getString("modelAssumptions")));
          String line = br.readLine();

          // format is one var name per line, ! before it for assume false
          while (null != line) {
            int sign = 1;
            String varname = line;
            if (line.startsWith("!")) {
              sign = -1;
              varname = line.substring(1);
            }
            // if (clauses.varExists(varname)) {
              assumptions.add(sign * clauses.getVarNum(varname));
            // }
            line = br.readLine();
          }
        }
        int[] assumpints = new int[assumptions.size()];
        for (int i = 0; i < assumptions.size(); i++) {
          assumpints[i] = assumptions.get(i);
        }

        ISolver solver = SolverFactory.newDefault();
        solver.newVar(clauses.getNumVars());
        solver.setExpectedNumberOfClauses(clauses.size());

        for (List<Integer> clause : clauses) {
          int[] cint = new int[clause.size()];
          int i = 0;
          for (Integer val : clause) {
            cint[i++] = val;
          }
          try {
            solver.addClause(new VecInt(cint));
          } catch (ContradictionException e) {
            System.err.println("kconfig model is self-contradictory");
            System.exit(1);
          }
        }

        try {
          IProblem problem = new ModelIterator(solver);
          if (problem.isSatisfiable(new VecInt(assumpints))) {
            System.err.println("kconfig model is satisfiable");
          } else {
            System.err.println("kconfig model is not satisfiable");
            System.exit(1);
          }
        } catch (TimeoutException e) {
          e.printStackTrace();
          System.exit(1);
        }

        
        actions.addClauses(clauses, assumpints);
      }

      P4Context initialParsingContext = new P4Context();
      initialParsingContext.collectStatistics(runtime.test("statisticsLanguage"));

      parser = new ForkMergeParser(P4ParseTables.getInstance(), semanticValues,
                                   actions, initialParsingContext,
                                   preprocessor, presenceConditionManager);
      parser.saveLayoutTokens(runtime.test("printSource") 
                              || runtime.test("configureAllYes")
                              || runtime.test("configureAllNo")
                              || runtime.getString("configFile") != null);
      parser.setLazyForking(runtime.test("optimizeLazyForking"));
      parser.setSharedReductions(runtime.test("optimizeSharedReductions"));
      parser.setEarlyReduce(runtime.test("optimizeEarlyReduce"));
      parser.setLongestStack(runtime.test("platoffOrdering"));
      parser.setEarlyShift(runtime.test("earlyShift"));
      parser.setFollowSetCaching(! runtime.test("noFollowCaching"));
      parser.collectStatistics(runtime.test("statisticsParser"));
      parser.conditionGranularity(runtime.test("conditionGranularity"), true, true);
      parser.showActions(runtime.test("showActions"));
      parser.showErrors(! runtime.test("hideErrors"));
      parser.showAccepts(runtime.test("showAccepts"));
      parser.showFM(runtime.test("showFM"));
      parser.showLookaheads(runtime.test("showLookaheads"));

      if (runtime.hasValue("killswitch")
          && null != runtime.getString("killswitch")) {
        try {
          int cutoff = Integer.parseInt(runtime.getString("killswitch"));

          if (cutoff <= 0) {
            throw new NumberFormatException("the -killswitch flag takes a "
                                            + "positive, non-zero integer");
          }
          parser.setKillSwitch(cutoff);
        } catch (NumberFormatException e) {
          throw new NumberFormatException("the -killswitch flag takes a "
                                          + "positive, non-zero integer");
        }
      }

      if (runtime.test("naiveFMLR")) {
        translationUnit = parser.parseNaively();
      } else {
        translationUnit = parser.parse();
      }

      if (null != translationUnit
          && ! ((Node) translationUnit).getName().equals("TranslationUnit")) {
        GNode tu = GNode.create("TranslationUnit");
        tu.add(translationUnit);
        translationUnit = tu;
      }

      // if (runtime.test("printErrorConditions")) {
      //   PresenceCondition restrictCond = presenceConditionManager.getRestrictCond(false);
      //   if (null != printConstraints) {
      //     for (PresenceCondition cond : printConstraints) {
      //       PresenceCondition restricted = cond.restrict(restrictCond);
      //       cond.delRef();
      //       System.err.format("extra_constraint %s\n", restricted.toNotCNF());
      //       restricted.delRef();
      //     }
      //   }
      // }
      // if (runtime.test("functionAnalysis")) {
      //   PresenceCondition restrictCond = presenceConditionManager.getRestrictCond(false);
        
      //   Set<String> global_fundefs = initialParsingContext.getSymbolTable().getNames(STField.GLOBAL_FUNDEF);
      //   Set<String> static_fundefs = initialParsingContext.getSymbolTable().getNames(STField.STATIC_FUNDEF);
      //   Set<String> funcalls = actions.getFunctionTable().getNames(STField.FUNCALL);
      //   for (String s : global_fundefs) {
      //     // global fundef is negated ahead of time
      //     PresenceCondition global_fundef_pc = initialParsingContext.symbolPresenceCond(s, STField.GLOBAL_FUNDEF);
      //     PresenceCondition global_fundef_pc_restricted = global_fundef_pc.restrict(restrictCond);
      //     System.err.println("global_fundef " + s + " " + global_fundef_pc_restricted.toNotCNF());
      //     global_fundef_pc_restricted.delRef();
      //   }
      //   System.err.format("total_funcalls %d\n", funcalls.size());
      //   // for (String s : funcalls) {
      //   //   System.err.println("funcall " + s);
      //   // }
      //   funcalls.removeAll(global_fundefs);
      //   funcalls.removeAll(static_fundefs);
      //   for (String s : funcalls) {
      //     PresenceCondition restricted = actions.getFunctionTable().getPresenceCond(s, STField.FUNCALL).restrict(restrictCond);
      //     System.err.println("undef_funcall " + s + " " + restricted.toCNF());
      //     restricted.delRef();
      //   }
      //   actions.getFunctionTable().delRef();

      //   restrictCond.delRef();
      // }

      initialParsingContext.free();

      // if (runtime.test("checkAST")) {
      //   FileReader ratsReader = new FileReader(file);
      //   CParser ratsParser
      //     = new CParser(ratsReader, file.toString(), (int)file.length());
      //   Result  ratsResult = ratsParser.pTranslationUnit(0);
      //   Node rats = (Node) ratsParser.value(ratsResult);
      //   Node superc = (Node) translationUnit;

      //   if (! TreeComparator.getInstance().traverse(superc, rats)) {
      //     System.err.println("superc: " + superc);
      //     System.err.println("rats:   " + rats);

      //     throw new RuntimeException("C asts are different");
      //   }
      // }

      if (runtime.test("printAST")) {
        runtime.console().format((Node) translationUnit).pln().flush();
      }


      if(runtime.test("callGraph")) {
        CallGraphGenerator graph = new CallGraphGenerator();
        graph.buildSymbolTable((Node) translationUnit);
        graph.buildCallGraph((Node) translationUnit);
        // graph.printCallGraph();
        graph.createCallGraphVisual(file.getName() + ".callGraph");
      }
      if(runtime.test("preprocessorUsageMatrix")) {
        String templateFilePath = null;
        for (Object o : runtime.getList("templateFileForMatrix")) {
          if (o instanceof String) {
            String s;

            if(templateFilePath != null) {
              System.err.println("Passed in two paths for template file. Expecting only one of syntax \"-templateFileForMatrix \"PATH_TO_TEMPLATE_FILE.txt\"\"");
            }
            
            s = (String) o;
            templateFilePath = s;
          }
        }

        if(templateFilePath != null) {
          ArrayList<String> template = readTemplate(templateFilePath);
          collectBlockNames((Node) translationUnit, template);
          template_block_map = (HashMap<String, String>) stripParenthesis(template_block_map);
          blockValues = (ArrayList<String>) stripParenthesis(blockValues);
          initializeConditionalsInside();
          System.out.println("Passed in block names and actual mapped function values:" + template_block_map);
          // System.out.println(blockValues);
    
          // collect macros for specific block names collected based on user input
          walkAST((Node) translationUnit, "", false);
        }    

        //collect macros for all blocks
        walkASTForAllConstructs((Node) translationUnit, null);

        // cleaning up the data
        if(templateFilePath != null) {
          convertNotConditionalsAndRemoveDefinedWordForStatPurposes(conditionalsInsideSpecificBlosk);
          System.out.println("--------Printing out macros present DIRECTLY under the specific construct blocks--------\n");
          printMatrix(conditionalsInsideSpecificBlosk);
          System.out.println("\n--------Done printing macros present DIRECTLY under the specific construct blocks--------\n\n");

          collectASTData((Node) translationUnit);
          convertNotConditionalsAndRemoveDefinedWordForStatPurposes(presenceCondMap);

          for(String e: presenceCondMap.keySet()) {
            if(conditionalsInsideSpecificBlosk.containsKey(e)) {
              if(! conditionalsInsideSpecificBlosk.get(e).equals(presenceCondMap.get(e))) {
                System.err.println("Something not right: " + e);
                System.exit(1);
              }
            }
          }

          expandCPP();
          removeEmpty(presenceCondMap);

          presenceCondMap = keepOnlySpecifics(blockValues, presenceCondMap);
          System.out.println("---!!---Printing out macros present ANYWHERE under the specific construct blocks---!!---\n");
          printMatrix(presenceCondMap);
          System.out.println("\n---!!---Done printing macros present ANYWHERE under the specific construct blocks---!!---\n");
        }

        convertNotConditionalsAndRemoveDefinedWordForStatPurposes(conditionalsInsideEverything);
        System.out.println("--------Printing out macro mappings for all constructs--------\n");
        printMatrix(conditionalsInsideEverything);
        System.out.println("\n--------Done printing mappings for all constructs--------\n");
        
        // System.out.println(presenceCondMap);

        // String dot_string = toDot(callGraph, "callGraph");
        // System.out.println("digraph{" + dot_string + "}");

        if (runtime.test("printSource")) {
          OutputStreamWriter writer = new OutputStreamWriter(System.out);

          System.err.println("Print Source");

          LinkedList<PresenceCondition> parents
            = new LinkedList<PresenceCondition>();

          parents.push(presenceConditionManager.newTrue());

          printSource((Node) translationUnit,
                      presenceConditionManager.newTrue(),
                      parents, writer);

          parents.pop();
          assert(parents.size() == 0);
          
          writer.flush();
        }

        // if (runtime.test("configureAllYes") || runtime.test("configureAllNo")) {
        //   OutputStreamWriter writer = new OutputStreamWriter(System.out);
        //   boolean defaultSetting = runtime.test("configureAllYes") ? true : false;
        //   List<String> clExceptions = null != runtime.getString("configureExceptions") ?
        //     Arrays.asList(runtime.getString("configureExceptions").split(",")) :
        //     null;
        
        //   List<String> exceptions = new LinkedList<String>();
        //   Map<String, String> nonbooleans = new HashMap<String, String>();
        //   ConditionEvaluator evaluator = null;
        //   BDD configuration;

        //   if (null != clExceptions) {
        //     exceptions.addAll(clExceptions);
        //   }

        //   if (null != runtime.getString("configFile")) {
        //     BufferedReader configFile =
        //       new BufferedReader(new FileReader(runtime.getString("configFile")));
        //     String line;

        //     // Turn on the configuration variables from a linux .config
        //     // file
        //     while (null != (line = configFile.readLine())) {
        //       if (line.length() == 0) continue;
        //       if (line.startsWith("#")) continue;
        //       if (line.endsWith("=y")) {  // boolean and tristate
        //         String exception =
        //           "(defined " + line.substring(0,line.length() - 2) + ")";
        //         exceptions.add(exception);
        //       } else { // non-boolean
        //         String[] def = line.split("=");
        //         String exception = "(defined " + def[0] + ")";
        //         exceptions.add(exception);
        //         nonbooleans.put(def[0], def[1]);
        //       }
        //     }
        //   }

        //   // PresenceCondition t = presenceConditionManager.newTrue();
        //   // macroTable._define("CONFIG_64BIT", new MacroTable.Macro.Object(null), t);

        //   // StringBuilder sb;
        //   // String name = "BITS_PER_LONG";
        //   // // String name = "CONFIG_64BIT";
      
        //   // sb = new StringBuilder();
          
        //   // sb.append(name);
        //   // sb.append("\n");
        //   // sb.append("-------------------------------------------");
        //   // sb.append("\n");
        //   // for (MacroTable.Entry e : macroTable.table.get(name)) {
        //   //   sb.append(e);
        //   //   sb.append("\n");
        //   // }
        //   // sb.append("\n");

        //   // System.err.println(sb.toString());

        //   if (null != nonbooleans) {
        //     evaluator = new ConditionEvaluator(ExpressionParser.fromRats(),
        //                                        presenceConditionManager,
        //                                        macroTable);
        //   }

        //   configuration = presenceConditionManager.
        //     createConfiguration(defaultSetting, exceptions);
        //   System.err.println("Configure AST");

        //   configureAST((Node) translationUnit, configuration, nonbooleans, writer);
        //   configuration.free();

        //   writer.flush();
        // } else if (null != runtime.getString("configFile")) {
        //   OutputStreamWriter writer = new OutputStreamWriter(System.out);
        //   Map<String, String> nonbooleans = new HashMap<String, String>();
        //   BufferedReader configFile =
        //     new BufferedReader(new FileReader(runtime.getString("configFile")));
        //   List<String> clExceptions = null != runtime.getString("configureExceptions") ?
        //     Arrays.asList(runtime.getString("configureExceptions").split(",")) :
        //     null;
        //   PresenceCondition t =
        //     presenceConditionManager.newTrue();
        //   Iterator<String> clIterator = null != clExceptions ? clExceptions.iterator()
        //     : null;
        //   String line;
        //   HashSet<String> configuredVars = new HashSet<String>();

        //   // Put the config file definitions into the macro symbol table
        //   while (null != (line = configFile.readLine()) ||
        //          clIterator != null &&
        //          clIterator.hasNext() &&
        //          null != (line = clIterator.next())) {
        //     if (line.length() == 0) {
        //       continue;
        //     } else if (line.startsWith("# ") && line.endsWith(" is not set")) {
        //       String var_name = line.substring(2,line.length() - " is not set".length());
        //       macroTable._define(var_name,
        //                          MacroTable.Macro.undefined,
        //                          t);
        //       configuredVars.add(var_name);
        //     } else if (line.startsWith("#")) { // ignore comments other than undefined config vars
        //       continue;
        //     } else if (line.endsWith("=y")) {  // store boolean and tristate config vars
        //       String var_name = line.substring(0,line.length() - 2);
        //       // if (var_name.equals("__KERNEL__")) System.err.println("before define " + macroTable.contains("__KERNEL__"));
        //       macroTable._define(var_name,
        //                          new MacroTable.Macro.Object(null),
        //                          t);
        //       configuredVars.add(var_name);
        //       // if (var_name.equals("__KERNEL__")) System.err.println("after define " + macroTable.contains("__KERNEL__"));
        //     } else { // store non-boolean config var defs
        //       String[] def = line.split("=");
        //       List<Syntax> def_list = new LinkedList<Syntax>();
        //       final CLexer clexer;
        //       Syntax syntax = null;

        //       if (def.length > 1) {
        //         clexer = new CLexer(new StringReader(def[1]));
        //         clexer.setFileName("config file");

        //         while (true) {
        //           try {
        //             syntax = clexer.yylex();
        //           } catch (IOException e) {
        //             e.printStackTrace();
        //             throw new RuntimeException();
        //           }
        //           if (syntax.kind() == Kind.EOF) break;
        //           def_list.add(syntax);
        //         }
        //         macroTable._define(def[0],
        //                            new MacroTable.Macro.Object(def_list),
        //                            t);
        //         nonbooleans.put(def[0], def[1]);
        //         configuredVars.add(def[0]);
        //       } else {
        //         // System.err.println("wrong " + line);
        //       }
        //     }
        //   }

        //   // Pull any other macros not defined in the config file to false
        //   for (String var_name : macroTable.table.keySet()) {
        //     if (! configuredVars.contains(var_name)) {
        //       macroTable._define(var_name,
        //                          MacroTable.Macro.undefined,
        //                          t);
        //     }
        //   }

        //   // StringBuilder sb;
        //   // // String name = "__KERNEL__";
        //   // // String name = "BITS_PER_LONG";
        //   // // String name = "CONFIG_64BIT";
        //   // // String name = "__CHECKER__";
        //   // String name = "__section";
      
        //   // sb = new StringBuilder();
          
        //   // sb.append(name);
        //   // sb.append("\n");
        //   // sb.append("-------------------------------------------");
        //   // sb.append("\n");
        //   // for (MacroTable.Entry e : macroTable.table.get(name)) {
        //   //   sb.append(e);
        //   //   sb.append("\n");
        //   // }
        //   // sb.append("\n");

        //   // System.err.println(sb.toString());

        //   // Evaluate each BDD variable according to the Linux .config
        //   // file settings.
        //   BDD configuration = presenceConditionManager.newTrue().getBDD();
        //   int var_idx = 0;
        //   String var_name = null;

        //   // conditionEvaluator.setPullUndefinedFalse(true);
        //   while (null != (var_name = presenceConditionManager.getVariableManager().getName(var_idx++))) {
        //     String var_cond = "#if " + var_name + "\n#else\n#endif\n";
        //     // System.err.println(var_cond);
        //     HeaderFileManager var_filemanager =
        //       new HeaderFileManager(new StringReader(var_cond),
        //                             new File(var_name),
        //                             null, null, null, null, null);
        //     // System.err.println("current: " + presenceConditionManager.reference().isTrue())
        //       ;
        //     Preprocessor var_evaluator =
        //       new Preprocessor(var_filemanager,
        //                        macroTable,
        //                        presenceConditionManager,
        //                        conditionEvaluator,
        //                        tokenCreator);

        //     Syntax syntax = var_evaluator.next();

        //     if (syntax.kind() == Kind.CONDITIONAL) {
        //       PresenceCondition presult = ((Conditional) syntax).presenceCondition();
        //       // if (var_name.equals("(defined __KERNEL__)")) {
        //       //   System.err.println("after configure " + var_name);
        //       //   System.err.println("after configure " + var_cond);
        //       //   System.err.println("after configure " + presult.toString());
        //       // }
        //       if (presult.isTrue()) {
        //         configuration.andWith(presenceConditionManager.getVariableManager().getVariable(var_name));
        //         // System.err.println("FJDSKL");
        //       } else // if (presult.isFalse())
        //         {
        //         BDD ith = presenceConditionManager.getVariableManager().getVariable(var_name);
        //         BDD not = ith.not();
        //         ith.free();
        //         configuration.andWith(not);
        //         // System.err.println("noonononon");
        //       } // else {
        //       //   System.err.println("unresolved expression");
        //       //   System.err.println(var_name + " " + presult.toString());
        //       //   System.exit(1);
        //       // }
        //     } else {
        //       System.err.println("handle incorrect evaluation");
        //       System.exit(1);
        //     }

        //     while (syntax.kind() != Kind.EOF) syntax = var_evaluator.next();
        //   }

        //   // Evaluate each macro in the macro table until each is
        //   // unconditionally defined.

        //   // After parsing, replace identifiers, recursively evaluate if
        //   // necessary

        //   // // Evaluate each BDD it using the above evaluator
        //   // BDD configuration = presenceConditionManager.evaluateBDDs(visitor);

        //   System.err.println("Configure AST");
        //   configureAST((Node) translationUnit, configuration, nonbooleans, writer);
        //   configuration.free();

        //   writer.flush();
        // }

        if (runtime.test("statisticsParser")) {
          IdentityHashMap<Object, Integer> seen
            = new IdentityHashMap<Object, Integer>();
          int count = dagNodeCount((Node) translationUnit, seen);
          runtime.errConsole().pln(String.format("dag_nodes %d", count));

          int shared = 0;
          for (Integer i : seen.values()) {
            if (i > 1) {
              shared++;
            }
          }
          runtime.errConsole().pln(String.format("dag_nodes_shared %d", shared));
          runtime.errConsole().flush();
        }

        result = (Node) translationUnit;
      }
    }
    // Print optional statistics and debugging information.
    if (runtime.test("macroTable")) {
      System.err.println("Macro Table");
      System.err.println(macroTable);
    }

    if (runtime.test("configurationVariables")) {
      for (String name : macroTable.configurationVariables) {
        if (! macroTable.headerGuards.contains(name))  {
          System.err.println("config_var " + name);
        }
      }
    }

    if (runtime.test("macroDependencies")) {
      Set<String> configVariables = new HashSet<>();

      for (String name : macroTable.configurationVariables) {
        if (! macroTable.headerGuards.contains(name))  {
          configVariables.add(name);
        }
      }

      System.out.println("Configuration (free) variables: " + configVariables);
      HashMap<String, HashSet<String>> dependentStrings = macroTable.getDependentMacros(configVariables);
      System.out.println(dependentStrings);
      printMatrix(dependentStrings);
    }

    if (runtime.test("headerGuards")) {
      for (String name : macroTable.headerGuards) {
        System.err.println("header_guard " + name);
      }
    }

    if (runtime.test("time")) {
      parserTimer.stop();
      System.err.println(String.format("performance_breakdown %s %f %f %f",
                                       file.toString(),
                                       parserTimer.getTotalSeconds(),
                                       preprocessorTimer.getTotalSeconds(),
                                       lexerTimer.getTotalSeconds()));
    }

    if (runtime.test("size")) {
      System.err.println("size " + fileManager.getSize());
    }

    return result;
  }
  
  /**
   * Get location of a production given its value.
   *
   * @param value The value of the production.
   * @return The location.
   */
  static Location getProductionLocation(Object value) {
    if (value instanceof Node) {
      for (Object o : (Node) value) {
        Location location = getProductionLocation(o);

        if (null != location) {
          return location;
        }
      }

      return ((Node) value).getLocation();
    } else {
      return null;
    }
  }

  /**
   * Print an AST (or a subtree of it) in C source form.
   *
   * @param n An AST or a subtree.
   * @param presenceCondition The current nested presence condition.
   * @param writer The writer.
   * @throws IOException Because it writes to output. 
   */
  private static void printSource(Node n, PresenceCondition presenceCondition,
                                  LinkedList<PresenceCondition> parents,
                                  OutputStreamWriter writer)
    throws IOException {
    if (n.isToken()) {
      writer.write(n.getTokenText());
      writer.write(" ");

    } else if (n instanceof Node) {

      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {

        boolean seenIf = false;
        PresenceCondition branchCondition = null;

        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            branchCondition = (PresenceCondition) bo;

            if (! seenIf) {
              writer.write("\n#if ");
              seenIf = true;
            } else {
              // writer.write("\n#elif ");
              writer.write("\n#endif ");
              writer.write("\n#if ");
              parents.pop();
            }

            if (branchCondition.equals(parents.peek())) {
              writer.write("1");
            } else {
              writer.write(branchCondition.toString());
              // branchCondition.print(writer);
            }
            parents.push(branchCondition);
            
            writer.write("\n");
          } else if (bo instanceof Node) {
            printSource((Node) bo, branchCondition, parents, writer);
          }
        }
        writer.write("\n#endif\n");
        parents.pop();

      } else {
        for (Object o : n) {
          printSource((Node) o, presenceCondition, parents, writer);
        }
      }

    } else {
      throw new UnsupportedOperationException("unexpected type");
    } 
  }

  /**
   * Print one configuration of an AST (or a subtree of it) as C
   * source code.
   *
   * @param n An AST or a subtree.
   * @param configuration A BDD containing the configuration settings.
   * @param writer The writer.
   * @throws IOException Because it writes to output. 
   */
  private static void configureAST(Node n,
                                   BDD configuration,
                                   Map<String,String> nonbooleans,
                                   OutputStreamWriter writer)
    throws IOException {
    if (n.isToken()) {
      if (nonbooleans.containsKey(n.getTokenText())) {
        writer.write(nonbooleans.get(n.getTokenText()));
      } else {
        writer.write(n.getTokenText());
      }
      writer.write(" ");

    } else if (n instanceof Node) {

      if (n instanceof GNode
          && ((GNode) n).hasName(ForkMergeParser.CHOICE_NODE_NAME)) {

        // Pick the first choice that satistifies the configuration

        boolean printNextNode = false;
        PresenceCondition branchCondition = null;

        for (Object bo : n) {
          if (bo instanceof PresenceCondition) {
            BDD restricted;
            boolean satisfies;

            branchCondition = (PresenceCondition) bo;

            // restricted = branchCondition.getBDD().restrict(configuration.id());
            // printNextNode = !restricted.isZero();
            // restricted.free();
            printNextNode = true;
          } else if (bo instanceof Node) {
            if (printNextNode) {
              configureAST((Node) bo, configuration, nonbooleans, writer);
            }
          }
        }
        writer.write("\n");
      } else {
        for (Object o : n) {
          configureAST((Node) o, configuration, nonbooleans, writer);
        }
      }

    } else {
      throw new UnsupportedOperationException("unexpected type");
    } 
  }

  /**
   * Count the number of AST nodes.
   *
   * @param n An AST or a subtree.
   */
  private static int astNodeCount(Node n) {
    if (n.isToken()) {
      return 1;

    } else if (n instanceof Node) {
      int count = 0;

      for (Object bo : n) {
        if (bo instanceof Node) {
          count += astNodeCount((Node) bo);
        }
      }

      return count;

    } else {
      throw new UnsupportedOperationException("unexpected type");
    } 
  }
  
  /**
   * Count the number of DAG nodes.
   *
   * @param n A DAG or a subtree.
   * @param seen A hash map to store the seen nodes.
   */
  private static int dagNodeCount(Node n,
                                  IdentityHashMap<Object, Integer> seen) {
    if (seen.containsKey(n)) {
      seen.put(n, seen.get(n) + 1);
      return 0;
    }

    seen.put(n, 1);

    if (n.isToken()) {
      return 1;

    } else if (n instanceof Node) {
      int count = 0;

      for (Object bo : n) {
        if (bo instanceof Node) {
          count += dagNodeCount((Node) bo, seen);
        }
      }

      return count;

    } else {
      throw new UnsupportedOperationException("unexpected type");
    } 
  }
  
  /**
   * Preprocess the given CPP CST.
   * 
   * @param node The CPP CST
   * @return The preprocessed CPP CST
   */
  public Node preprocess(Node node) {
    return null;
  }

  /**
   * Run the tool with the specified command line arguments.
   *
   * @param args The command line arguments.
   */
  public static void main(String[] args) {
    new SuperP4().run(args);
  }

  /**
   * Takes in the filepath containing the template of the P4 model
   * and returns a list of the template in order
   * 
   * Assumption: First value in template is model name and last value is the word "name" to indicate end of instantiation
   * 
   * @param filepath The path to where the template file is located
   * @return An arraylist containing the order of network model
   * @throws IOException
   */
  public ArrayList readTemplate(String filepath) throws IOException{
    File file = new File(filepath);
    ArrayList<String> template = new ArrayList<>();
    BufferedReader reader = new BufferedReader(new FileReader(file));

    String line;
    boolean seenName = false;
    while((line = reader.readLine()) != null) {
      if(line.toLowerCase().equals("name")) {
        seenName = true;
      }
      template.add(line);
    }

    System.out.println(template);
    
    if(! seenName) {
      System.out.println("'name' word not found in the template to indicate end of parameters");
      System.exit(1);
    }

    return template;
  }

  /**
   * Walks the AST tree to obtain the specific block names from switch instantiation
   * 
   * @param node The obj structure containing the final AST of the program
   * @param template An ArrayList structure containing the order of network model parameters
   */
  public String collectBlockNames(Object obj, ArrayList<String> template) {
    // System.out.println(obj.getClass());
    if(obj instanceof Node) {
      Node node = (Node) obj;
      // System.out.println("name is: " + node.getName() + " of class " + node.getClass());
      // if(node.getName().equals("nonTypeName")) {
      //   System.out.println("next is: " + (node.get(0) instanceof Syntax ? node.get(0) : node.getGeneric(0)));
      // }
      // if(node.isToken()) {
      //   System.out.println("Token texT:" + node.getTokenText());
      // }
      Iterator its = node.iterator();
      // System.out.println(noded.getName());
      String lastValue = "";
      while(its.hasNext()) {
        Object cur = its.next();

        String rValue = collectBlockNames(cur, template);
        // System.out.println("rvalue is: " + rValue);

        if(blockValues.size() == 0) {
          if(node.getName() == "instantiation" &&
          rValue.toLowerCase().equals(template.get(0).toLowerCase())) {
               template_block_map.put(template.get(blockValues.size()), rValue);
               blockValues.add(rValue);
             }
          lastValue = rValue;
        } 
        else {
          lastValue = lastValue.concat(rValue);
          if (node.getName() == "argument") {
            assert blockValues.size() < (template.size()-1) : "number of values in blockValues should be less than number of provided argument, but current it is: " + blockValues.size() + " with the value:"  + blockValues;

            template_block_map.put(template.get(blockValues.size()), lastValue);
            blockValues.add(lastValue);
            lastValue = "";
          } 
          if(node.getName() == "name") {
            assert blockValues.size() == (template.size()-1) : "At the name construct, meaning we should have reached end of instantiation block but not all values obtained. Current values: " + blockValues;

            template_block_map.put(template.get(blockValues.size()), lastValue);
            blockValues.add(lastValue);
            lastValue = "";          
          }
        }
      }
      return lastValue;
    }
    else {
      // System.out.println(obj.toString());
      // set.add(obj.getClass());
      // System.out.println("NOT A NODE\n");
      if(obj instanceof PresenceCondition) {
        PresenceCondition pc = (PresenceCondition) obj;
        // System.out.println(pc);
      }
      if(obj instanceof String) {
        return obj.toString();
      }
      else {
        return "";
      }
    }
    // System.out.println(set);
  }

  public Object stripParenthesis(Object collection) {
    if(collection instanceof ArrayList) {
      ArrayList<String> blockValues = (ArrayList) collection;

      for(int i = 0; i < blockValues.size(); i++) {
        blockValues.set(i, blockValues.get(i).replace("()", ""));
      }

      return blockValues;
    }
    else if(collection instanceof HashMap) {
      HashMap<String, String> map = (HashMap) collection;
      for(String key : map.keySet()) {
        map.put(key, (map.get(key).replace("()", "")));
      }

      return map;
    }

    else {
      System.err.println("ERROR, unsupported type given");
      return collection;
    }
  }

  public void initializeConditionalsInside() {
    conditionalsInsideSpecificBlosk = new HashMap<>();
    if(! blockValues.isEmpty()) {
      // removing package name and the variable name as it is not blocks we are interested in
      blockValues.remove(0);
      blockValues.remove(blockValues.size()-1);

      for(int i = 0; i < blockValues.size(); i++) {
        conditionalsInsideSpecificBlosk.put(blockValues.get(i), new HashSet<>());
      }
    }
  }

  public String walkAST(Object obj, String currentBlock, boolean isDeclaration) {
    // System.out.println(obj.getClass());
    if(obj instanceof Node) {
      Node node = (Node) obj;
      Iterator its = node.iterator();
      while(its.hasNext()) {
        Object cur = its.next();
        String rValue;

        if(cur instanceof Node && ((Node) cur).getName().equals("declaration")) {
          // since the "modules" when instantiating the package are declaration based constructs
          rValue = walkAST(cur, currentBlock, true);
        } else {
          if(cur instanceof Node && ((Node) cur).getName().equals("nonTypeName")) {
            Set methods = ((Node) cur).properties();
              for (Object method : methods) {
                System.out.printf("method: %s", method.toString());
                System.out.println();
              }
          }
          rValue = walkAST(cur, currentBlock, isDeclaration);
        }

        if(cur instanceof Node && ((Node) cur).getName().equals("declaration")){
          // System.out.println("sending back " + currentBlock);
          currentBlock = "";
        }
        else {
          currentBlock = rValue == "" ? currentBlock : rValue;
        }
      }
      return currentBlock;
    }
    else {
      if(obj instanceof PresenceCondition) {
        PresenceCondition pc = (PresenceCondition) obj;
        if(isDeclaration && (! currentBlock.isEmpty())) {
          // System.out.println("curBlock: " + currentBlock);
          // System.out.println(conditionalsInsideSpecificBlosk.get(currentBlock));
          // System.out.println("adding value in block: " + currentBlock + " at loc: " + obj + " " + pc.getAllConfigs().toString());
          // System.out.println(currentBlock);
          conditionalsInsideSpecificBlosk.get(currentBlock).addAll(pc.getAllConfigs());
        }
        // System.out.println(pc);
      }
      if(obj instanceof String) {
        if(blockValues.contains(obj.toString())) {
          return obj.toString();
        }
        return "";
      }
      else {
        return "";
      }
    }
  }

  public void walkASTForAllConstructs(Object obj, ArrayList<String> listOfNestedBlocks) {
    // System.out.println(obj.getClass());
    if(listOfNestedBlocks == null) {
      listOfNestedBlocks = new ArrayList<String>();
    }

    if(obj instanceof Node) {
      Node node = (Node) obj;
      Iterator its = node.iterator();

      while(its.hasNext()) {
        Object cur = its.next();
        if(cur instanceof Node) {
          Node curNode = (Node) cur;
          listOfNestedBlocks.add(curNode.getName());
          walkASTForAllConstructs(cur, listOfNestedBlocks);
          listOfNestedBlocks.remove(listOfNestedBlocks.size()-1);
        } else {
          walkASTForAllConstructs(cur, listOfNestedBlocks);
        }
      }
      return;
    }
    else {
      if(obj instanceof PresenceCondition) {
        PresenceCondition pc = (PresenceCondition) obj;
        for(String blockName: listOfNestedBlocks) {
          if(conditionalsInsideEverything.containsKey(blockName)) {
            conditionalsInsideEverything.get(blockName).addAll(pc.getAllConfigs());
          }
          else {
            conditionalsInsideEverything.put(blockName, new HashSet<>());
            conditionalsInsideEverything.get(blockName).addAll(pc.getAllConfigs());
          }
        }
      }
      return;
    }
  }

  public void eliminateCancellations(ArrayList<String> array, String hashMapKey) {
    HashMap<String, Integer> counter = new HashMap<>();

    for(String element: array) {
      if(counter.containsKey(element)) {
        counter.put(element, counter.get(element) + 1);
      }
      else {
        counter.put(element, 1);
      }
    }

    for(String key: counter.keySet()) {
      if(counter.containsKey("!" + key)) {
        String notVar = "!" + key;
        if(counter.get(key) <= 0 || counter.get(notVar) <= 0) {
          continue;
        }
        int cur_int = counter.get(key);
        int other_int = counter.get(notVar);
        counter.put(key, cur_int - other_int);
        counter.put(notVar, other_int - cur_int);

        // if(counter.get(key) == 0) {
        //   counter.remove(key);
        // }
        // if (counter.get(notVar) == 0) {
        //   counter.remove(notVar);
        // }
      }
    }

    // System.out.println(hashMapKey + ": " + counter);

    conditionalsInsideSpecificBlosk.get(hashMapKey).clear();
    for(String key: counter.keySet()) {
      if(counter.get(key) <= 0) {
        continue;
      }
      conditionalsInsideSpecificBlosk.get(hashMapKey).add(key);
    }
  }
 boolean printUnit = false;
  public void convertNotConditionalsAndRemoveDefinedWordForStatPurposes(HashMap<String, HashSet<String>> workingSet) {
    for(String key : workingSet.keySet()) {
      // System.out.println("OG size for " + key + " is " + workingSet.get(key).size());
      Iterator<String> itr = workingSet.get(key).iterator();
      HashSet<String> temp = new HashSet<>();
      while(itr.hasNext()) {
        String str = itr.next();
        str = str.replace("(defined", "");
        str = str.replace(")", "");
        if(str.startsWith("!")) {
          str = str.substring(1);
        }
        str = str.stripLeading();
        temp.add(str);
        itr.remove();
      }

      workingSet.get(key).addAll(temp);
    }
  }

  public void printMatrix(HashMap<String, HashSet<String>> workingSet) {
    // System.out.println("\nPRINTING MATRIX");
    // System.out.println(workingSet);
    HashSet<String> allValuesTogether = new HashSet<>();

    for(String key : workingSet.keySet()) {
      allValuesTogether.addAll(workingSet.get(key));
    }

    ArrayList<String> sortedConditionalValues = new ArrayList<>(allValuesTogether);
    Collections.sort(sortedConditionalValues);

    ArrayList<String> constructNames = new ArrayList<>(workingSet.keySet());
    // Collections.sort(constructNames);

    int [][] matrix = new int[sortedConditionalValues.size()][constructNames.size()];


    for(int i = 0; i < sortedConditionalValues.size(); i++) {
      for(int j = 0; j < constructNames.size(); j++) {
        matrix[i][j] = workingSet.get(constructNames.get(j)).contains(sortedConditionalValues.get(i)) ? 1 : 0;
      }
    }

    // Loop through all elements of current row
    for (int j = 0; j < matrix[0].length; j++) {
        System.out.print(constructNames.get(j)+ " ");
    }
    System.out.println();
    
    for (int i = 0; i < matrix.length; i++) {
      System.out.print(sortedConditionalValues.get(i) + " ");
      // Loop through all elements of current row
      for (int j = 0; j < matrix[i].length; j++) {
          System.out.print(matrix[i][j] + " ");
      }
      System.out.println();
    }
  }

  public class declarationClass {
    String declarationsString;
    boolean hasName;

    declarationClass(String name, boolean hasName) {
      this.declarationsString = name;
      this.hasName = hasName;
    }

    declarationClass(String name) {
      this.declarationsString = name;
      this.hasName = false;
    }
  }

  HashMap<String, HashSet<String>> presenceCondMap = new HashMap<>();
  HashMap<String, HashSet<String>> callGraph = new HashMap<>();
  Stack<String> blockNames = new Stack<>();
  HashSet<String> declarationsOptions = new HashSet<>(Arrays.asList("constantDeclaration",
                                                      "externDeclaration",
                                                      "actionDeclaration",
                                                      "parserDeclaration",
                                                      "typeDeclaration",
                                                      "controlDeclaration",
                                                      "instantiation",
                                                      "errorDeclaration",
                                                      "matchKindDeclaration",
                                                      "functionDeclaration"));
  int nestedDepth = 0;
  // boolean findingDeclName = false;
  int findingDeclName = 0;
  int findingTypeRefName = 0;
  Stack<declarationClass> declarationsStack = new Stack<>();

  public void collectASTData(Object unit) {
      if(printUnit)
        System.out.println("CURRENT UNIT: " + unit + " of type: " + unit.getClass());
      if(unit instanceof Node){
          visit((Node) unit);
          // collectASTData((Node) unit);
      }
      else if(unit instanceof PresenceCondition) {
          visit((PresenceCondition) unit);
      }
      else if(unit instanceof String) {
          visit((String) unit);
      }
      else {
          System.err.println("interesting error");
          System.exit(1);
      }
      // visit(unit);
  }

  public Object visit(Node node) {
    // System.out.println("name: " + node.getName());
    Iterator itr = node.iterator();

    // declarationoptions - contains only list of blocks names we want to track
    // we check if current node is something we want to track
    if(declarationsOptions.contains(node.getName())) {
      // push on top of scope stack
      declarationsStack.push(new declarationClass(node.getName(), false));

      // if we are entering a new declaration stack, we ideally want to find its name
      // set flag to 1 to indicate we want to find name
      if(findingDeclName == 0) {
        findingDeclName = 1;
      }
    }
    if(findingDeclName == 1 && node.getName().equals("nonTypeName")) {
      // nonTypeName is the construct that is used to name a declaration
      // so if we are entering the nonTypeName after entering a declaration block,
      // the string under nonTypeName will be the name of the current declaration block
      // set flag to 2 to indicate the next string value will be name of current declaration
      findingDeclName = 2;
    }

    if(findingTypeRefName == 0 && node.getName().equals("typeName")) {
      // findingTypeRefName is the flag that will be used to indicate whether
      // we are entering a block that might contains a typeref (declared type_identifier)
      findingTypeRefName = 1;
    }

    while(itr.hasNext()) {
      // Go through child nodes
      Object cur = itr.next();
      collectASTData(cur);
    }

    if(declarationsOptions.contains(node.getName())) {
      assert declarationsStack.peek().declarationsString.equals(node.getName()) : "top of stack not same as outcoming order";
      // Exiting declaration block
      declarationClass popped = declarationsStack.pop();

      if(popped.hasName && findingDeclName == 3) {
        // since we are exiting declaration block, reset global flag and block name

        // System.out.println("Exiting block: " + blockNames.pop() + " for type: " + node.getName());
        findingDeclName = 0;
        printUnit = false;
        blockNames.pop();
      }
    }

    return node;
  }

  public Object visit(PresenceCondition node) {
    if(blockNames.isEmpty()) {
      return node;
    }

    // System.out.println("adding to block: " + blockNames.peek() + " value: " + node.getAllConfigs());

    if(presenceCondMap.containsKey(blockNames.peek())) {
      presenceCondMap.get(blockNames.peek()).addAll(node.getAllConfigs());
    } else {
      presenceCondMap.put(blockNames.peek(), new HashSet<>(node.getAllConfigs()));
    }

    return node;
  }

  public String visit(String node) {
    if(findingDeclName == 2) {
      blockNames.push(node);
      callGraph.put(node, new HashSet<>());
      findingDeclName = 3;

      declarationsStack.peek().hasName = true;

      // System.out.println("new blockname: " + node);
      // if(node.equals("FabricEgress"))
      //   printUnit = true;
    }

    if(findingTypeRefName == 1) {
      if(blockNames.isEmpty()) {
        if(! callGraph.containsKey("Global")) {
          callGraph.put("Global", new HashSet<>());
        }
        callGraph.get("Global").add(node);
      } else {
        assert callGraph.containsKey(blockNames.peek()) : "found a typeref but current blockname is not in callgraph: " + blockNames.peek();

        // Adding the current typeref name (the block that is being called) as a connecting edge to current block
        callGraph.get(blockNames.peek()).add(node);
      }

      findingTypeRefName = 0;
    }
    return node;
  }

  public void expandCPP() {
    int magnitude = magnitude(presenceCondMap);
    int newMagnitude = magnitude;
    do {
      magnitude = newMagnitude;

      for(String key : callGraph.keySet()) {
        if(! presenceCondMap.containsKey(key)) {
          continue;
        }

        Set<String> calleSet = new HashSet<>();

        for(String calleBlock : callGraph.get(key)) {
          if(! presenceCondMap.containsKey(calleBlock))
            continue;
            
            calleSet.addAll(presenceCondMap.get(calleBlock));
        }
        // TODO: use addAll's return value to check if it changes the value
        presenceCondMap.get(key).addAll(calleSet);
      }

      newMagnitude = magnitude(presenceCondMap);

    } while(magnitude != newMagnitude);
  }

  public int magnitude(HashMap<String, HashSet<String>> presenceCondMap) {
    int counter = 0;

    for(String key: presenceCondMap.keySet()) {
      counter += presenceCondMap.get(key).size();
    }

    return counter;
  }

  public HashMap<String, HashSet<String>> removeEmpty(HashMap<String, HashSet<String>> presenceMap) {
    Iterator itr = presenceMap.entrySet().iterator();

    presenceMap.values().removeIf(Set::isEmpty);

    return presenceMap;
  }

  public HashMap<String, HashSet<String>> keepOnlySpecifics(ArrayList<String> blockValues, HashMap<String, HashSet<String>> maps) {
    HashMap<String, HashSet<String>> filtered = new HashMap<>();

    for(String key : maps.keySet()) {
      if(blockValues.contains(key)) {
        filtered.put(key, maps.get(key));
      }
    }

    return filtered;
  }

  public String toDot(HashMap<String, HashSet<String>> callGraph, String filename) {
    String dot_string = "";

    for(String key: callGraph.keySet()) {
      dot_string += key;
      for(String value: callGraph.get(key)) {
        dot_string += "->" + value;
      }
      dot_string += ";";
    }
    System.out.println(dot_string);
    createDotGraph(dot_string, filename);
    return dot_string;
  }

  public static void createDotGraph(String dotFormat,String fileName)
{
    GraphViz gv=new GraphViz();
    gv.addln(gv.start_graph());
    gv.add(dotFormat);
    gv.addln(gv.end_graph());
   // String type = "gif";
    String type = "pdf";
  // gv.increaseDpi();
    gv.decreaseDpi();
    gv.decreaseDpi();
    System.out.println(gv.toString());
    File out = new File(fileName+"."+ type); 
    gv.writeGraphToFile( gv.getGraph( gv.getDotSource(), type ), out );
}

}
