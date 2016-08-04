// main.cc            see license.txt for copyright and terms of use
// entry-point module for a program that parses Java

#include <iostream.h>     // cout
#include <stdlib.h>       // exit, getenv, abort
#include <fstream.h>      // ofstream

#include "trace.h"        // traceAddSys
#include "exc.h"          // xfatal
#include "srcloc.h"       // SourceLocManager
#include "ckheap.h"       // malloc_stats
#include "glr.h"          // GLR
#include "lexer.h"        // Lexer
#include "java_ast.h"     // Java AST
#include "java_lang.h"    // JavaLang
#include "parsetables.h"  // ParseTables
#include "java.gr.gen.h"  // JavaParse
#include "nonport.h"      // getMilliseconds
#include "ptreenode.h"    // PTreeNode
#include "ptreeact.h"     // ParseTreeLexer, ParseTreeActions

#ifdef COUNT_CYCLES
#include "cycles.h"       // getCycles_ll
#endif

void if_malloc_stats()
{
  if (tracingSys("malloc_stats")) {
    malloc_stats();
  }
}


// this is a dumb way to organize argument processing...
char *myProcessArgs(int argc, char **argv, char const *additionalInfo)
{
  // remember program name
  char const *progName = argv[0];

  // process args
  while (argc >= 2) {
    if (traceProcessArg(argc, argv)) {
      continue;
    }
    else {
      break;     // didn't find any more options
    }
  }

  if (argc != 2) {
    cout << "usage: " << progName << " [options] input-file\n"
            "  options:\n"
            "    -tr <flags>:       turn on given tracing flags (comma-separated)\n"
         << (additionalInfo? additionalInfo : "");
    exit(argc==1? 0 : 2);    // error if any args supplied
  }

  return argv[1];
}


void doit(int argc, char **argv)
{
  // I think this is more noise than signal at this point
  //xBase::logExceptions = false;

  traceAddSys("progress");
  //traceAddSys("parse-tree");

  if_malloc_stats();

  SourceLocManager mgr;

  // string table for storing parse tree identifiers
  StringTable strTable;

  // parsing language options
  JavaLang lang;

  // ------------- process command-line arguments ---------
  char const *inputFname = myProcessArgs
    (argc, argv,
     "\n"
     "  parsing and output options:\n"
     "    noTree             do not make a (parse or abstract syntax) tree\n"
     "    parseTree          build a parse tree and print that, only\n"
     "    printAST           print AST after parsing\n"
     "\n"
     "  debugging output:\n"
     "    malloc_stats       print malloc stats every so often\n"
     "\n"
     "  (grep in source for \"trace\" to find more obscure flags)\n"
     "");

  if (tracingSys("test_xfatal")) {
    xfatal("this is a test error message");
  }

  if (!tracingSys("nowarnings")) {
    lang.enableAllWarnings();
  }
  
  if (tracingSys("only_works_on_32bit") &&
      sizeof(long) != 4) {
    // we are running a regression test, and the testcase is known to
    // fail due to dependence on architecture parameters, so skip it
    cout << "skipping test b/c this is not a 32-bit architecture\n";
    exit(0);
  }

  // --------------- parse --------------
  CompilationUnit* unit;
  int parseWarnings = 0;
  long start = getMilliseconds();
#ifdef COUNT_CYCLES
  long startCycles = getCycles_ll();
#endif

  SemanticValue treeTop;

  traceProgress(2) << "creating lexer and parser objects...\n";
  Lexer* lexer = new Lexer(strTable, lang, inputFname);
  LexerInterface* lexerInt = lexer;
  JavaParse* parseContext = new JavaParse(strTable, lang);
  UserActions* userAct = parseContext;
  
  traceProgress(2) << "building parse tables from internal data...\n";
  ParseTables *tables = parseContext->makeTables();
  
  if (tracingSys("noTree")) {
    traceProgress(2) << "not building any tree...\n";
    userAct = new TrivialUserActions();

    // delete parseContext?

  } else if (tracingSys("parseTree")) {
    // make some helpful aliases
    LexerInterface *underLexer = lexer;
    UserActions *underAct = parseContext;
    
    // replace the lexer and parser with parse-tree-building versions
    traceProgress(2) << "building parse tree...\n";
    lexerInt = new ParseTreeLexer(underLexer, underAct);
    userAct = new ParseTreeActions(underAct, tables);
    
    // delete underLexer and parseContext?
  }

  GLR glr(userAct, tables);
  if (! glr.glrParse(*lexerInt, treeTop)) {
    exit(2); // parse error
  }
  
  // check for parse errors detected by the context class
  if (parseContext->errors || lexer->errors) {
    exit(2);
  }
  parseWarnings = lexer->warnings + parseContext->warnings;

  // emit parse time
  long end = getMilliseconds();
#ifdef COUNT_CYCLES
  long endCycles = getCycles_ll();
#endif

  cout << "Parsing " << inputFname << " took " <<
    ((double)(end-start))/1000.0 << "s" <<
#ifdef COUNT_CYCLES
    ", " << (endCycles-startCycles) << " cycles" <<
#endif
    "\n";

  if_malloc_stats();
  
  if (tracingSys("parseTree")) {
    // the 'treeTop' is actually a PTreeNode pointer; print the
    // tree and bail
    PTreeNode *ptn = (PTreeNode*)treeTop;
    ptn->printTree(cout, PTreeNode::PF_EXPAND);
    
    delete parseContext;
    delete tables;
    
    return;
  }
  
  // treeTop is a TranslationUnit pointer
  unit = (CompilationUnit*)treeTop;
  
  //unit->debugPrint(cout, 0);
  
  delete parseContext;
  delete tables;
  
  checkHeap();
  
  // print abstract syntax tree
  if (tracingSys("printAST")) {
    unit->debugPrint(cout, 0);
  }
}

int main(int argc, char **argv)
{
  try {
    doit(argc, argv);
  }
  catch (XUnimp &x) {
    HANDLER();
    cout << x << endl;

    // don't consider this the same as dying on an assertion failure;
    // I want to have tests in regrtest that are "expected" to fail
    // for the reason that they use unimplemented language features
    return 10;
  }
  catch (XFatal &x) {
    HANDLER();
    
    // similar to XUnimp
    cout << x << endl;
    return 10;
  }
  catch (xBase &x) {
    HANDLER();
    cout << x << endl;
    abort();
  }

  //malloc_stats();

  return 0;
}
