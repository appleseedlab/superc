// ccparse.h            see license.txt for copyright and terms of use
// data structures used during parsing of Java code

#ifndef JAVAPARSE_H
#define JAVAPARSE_H

#include "macros.h"        // NORETURN
#include "strtable.h"      // StringTable
#include "srcloc.h"        // SourceLoc
#include "locstr.h"        // LocString
#include "java_flags.h"    // Modifiers
#include "java_ast.h"      // Expression
#include "java_lang.h"     // JavaLang, Bool3

// parsing action state
class ParseEnv {

public:
  StringTable &str;                       // string table
  int errors;                             // parse errors
  int warnings;                           // and warnings
  JavaLang &lang;                         // language options

public:
  ParseEnv(StringTable &table, JavaLang &aLang)
    : str(table),
      errors(0),
      warnings(0),
      lang(aLang)
   {}
  ~ParseEnv() {}

  // manipulate modifiers
  Modifiers combine(SourceLoc loc, Modifiers m1, Modifiers m2);

  // merge functions
  Expression* mergeUnary(Expression* e1, Expression* e2);
  Expression* mergePostfix(Expression* e1, Expression* e2);
  void noMerge(char const* desc, Expression* e1, Expression* e2) NORETURN;
  
  // generate a LocString suitable for use during parsing
  LocString * /*owner*/ ls(SourceLoc loc, char const *name);

  // report an error or warning
  void error(SourceLoc loc, char const *msg);
  void warning(SourceLoc loc, char const *msg);
  
  // depending on 'b', accept, accept with warning, or reject
  void diagnose3(Bool3 b, SourceLoc loc, char const *msg);
};

#endif // JAVAPARSE_H
