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

import java.lang.StringBuilder;

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
import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.IdentityHashMap;
import java.util.HashSet;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

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

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

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

import superc.cdesugarer.CParseTables;
import superc.cdesugarer.CValues;
import superc.cdesugarer.CActions;
import superc.cdesugarer.CContext;
import superc.cdesugarer.CLexerCreator;
import superc.cdesugarer.CTokenCreator;

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

/**
 * The SugarC C/preprocessor to C desugarer.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.130 $
 */
public class SugarC extends Tool {
  /** The user defined include paths */
  List<String> I;
  
  /** Additional paths for quoted header file names */
  List<String> iquote;
  
  /** Additional paths for system headers */
  List<String> sysdirs;
  
  /** Command-line macros and includes */
  StringReader commandline;

  /** Plug-in to create a new lexer for a given parser. */
  private final static LexerCreator lexerCreator = new CLexerCreator();

  /** Preprocessor support for token-creation. */
  private final static TokenCreator tokenCreator = new CTokenCreator();

  /** Simplify nested conditionals in preprocessor output. */
  private final static boolean SIMPLIFY_NESTED_CONDITIONALS = true;

  /** Create a new tool. */
  public SugarC() { /* Nothing to do. */ }

  /**
   * Return the name of this object.
   * 
   * @return The name of this object.
   */
  public String getName() {
    return "SugarC";
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
      "By default, SugarC performs all optimizations besides " +
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

      // Subparser explosion kill switch.
      word("killswitch", "killswitch", false,
           "Stop parsing if subparser set reaches or exceeds the given size. "
           + "This protects against subparser exponential explosion.  An "
           + "error message will be reported.").

      // Type checking and analysis
      bool("keepErrors", "keepErrors", false,
           "Pass preprocessor error tokens to the parser.  Makes for more "
           + "specific presence conditions.").

      // Output and debugging
      bool("printAST", "printAST", false,
           "Print the parsed AST.").
      bool("hideErrors", "hideErrors", false,
           "Hide preprocessing and parsing errors in standard err.").
      bool("showAccepts", "showAccepts", false,
           "Emit ACCEPT messages when a subparser accepts input.").
      bool("showActions", "showActions", false,
           "Show all parsing actions.").
      bool("showFM", "showFM", false,
           "Show all forks and merges.").
      bool("showLookaheads", "showLookaheads", false,
           "Show lookaheads on each parse loop (warning: very voluminous "
           + "output!)")
      ;
  }
  
  /**
   * Prepare for file processing.  Build header search paths.
   * Include command-line headers. Process command-line and built-in macros.
   */
  public void prepare() {
    // Set the command-line argument defaults.
    runtime.initDefaultValues();

    runtime.setValue("optionSilent", true);

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

    // Initialize the preprocessor with built-ins and command-line
    // macros and includes.
    macroTable = new MacroTable(tokenCreator);
    presenceConditionManager = new PresenceConditionManager();
    expressionParser = ExpressionParser.fromRats();
    conditionEvaluator = new ConditionEvaluator(expressionParser,
                                                presenceConditionManager,
                                                macroTable);

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
      fileManager.showErrors(! runtime.test("hideErrors"));

      preprocessor = new Preprocessor(fileManager,
                                      macroTable,
                                      presenceConditionManager,
                                      conditionEvaluator,
                                      tokenCreator);
      ((Preprocessor) preprocessor)
        .showErrors(! runtime.test("hideErrors"));

      do {
        syntax = preprocessor.next();
      } while (syntax.kind() != Kind.EOF);

      commandline = null;
    }
    
    fileManager = new HeaderFileManager(in, file, iquote, I, sysdirs,
                                        lexerCreator, tokenCreator, lexerTimer,
                                        runtime.getString(xtc.util.Runtime.INPUT_ENCODING));
    fileManager.showErrors(! runtime.test("hideErrors"));

    preprocessor = new Preprocessor(fileManager,
                                    macroTable,
                                    presenceConditionManager,
                                    conditionEvaluator,
                                    tokenCreator);
    
    ((Preprocessor) preprocessor)
      .showErrors(! runtime.test("hideErrors"));

    // Run SuperC.

    // Run the SuperC preprocessor and parser.
    ForkMergeParser parser;
    Object translationUnit;
      
    // Only pass ordinary tokens and conditionals to the parser.
    preprocessor = new TokenFilter(preprocessor, runtime.test("keepErrors"));

    // Create a new semantic values class for C.
    SemanticValues semanticValues;
    semanticValues = CValues.getInstance();

    CActions actions = CActions.getInstance();

    CContext initialParsingContext = new CContext();

    parser = new ForkMergeParser(CParseTables.getInstance(), semanticValues,
                                 actions, initialParsingContext,
                                 preprocessor, presenceConditionManager);
    parser.saveLayoutTokens(true); // need these for desugaring
    parser.setLazyForking(true);
    parser.setSharedReductions(true);
    parser.setEarlyReduce(true);
    parser.setFollowSetCaching(true);
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

    translationUnit = parser.parse();

    if (null != translationUnit
        && ! ((Node) translationUnit).getName().equals("TranslationUnit")) {
      GNode tu = GNode.create("TranslationUnit");
      tu.add(translationUnit);
      translationUnit = tu;
    }

    initialParsingContext.free();

    if (runtime.test("printAST")) {
      runtime.console().format((Node) translationUnit).pln().flush();
    }

    result = (Node) translationUnit;

    return result;
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
    new SugarC().run(args);
  }
}
