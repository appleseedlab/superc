// javaparse.cc            see license.txt for copyright and terms of use
// code for javaparse.h

#include "javaparse.h"    // this module
#include "trace.h"        // TRACE

#include <iostream.h>     // cout


// ----------------------- ParseEnv -----------------------
Modifiers ParseEnv::combine(SourceLoc loc, Modifiers m1, Modifiers m2)
{
  // any duplicate flags?
  Modifiers dups = (Modifiers)(m1 & m2);
  if (dups) {
    error(loc, stringc << "duplicate modifier: " << toString(dups));
  }

  // any of public, protected, private at the same time?
  Modifiers result = (Modifiers)(m1 | m2);

  if (result & MOD_PUBLIC) {
    if (result & MOD_PROTECTED) {
      error(loc, "public and protected modifiers");

    } else if (result & MOD_PRIVATE) {
      error(loc, "public and private modifiers");
    }

  } else if (result & MOD_PROTECTED) {
    if (result & MOD_PRIVATE) {
      error(loc, "protected and private modifiers");
    }
  }

  // done
  return result;
}

#define SELECT(higherKind, lowerKind) \
  if ((higherKind == k1) && (lowerKind  == k2)) return e1; \
  if ((lowerKind  == k1) && (higherKind == k2)) return e2

Expression* ParseEnv::mergeUnary(Expression* e1, Expression* e2)
{
  Expression::Kind k1 = e1->kind();
  Expression::Kind k2 = e2->kind();

  // Cast expressions take precedence over invocations.
  SELECT(Expression::CASTEXPRESSION, Expression::INVOCATIONEXPRESSION);

  // There should be no other ambiguities...
  noMerge("unary operations", e1, e2);
}


Expression* ParseEnv::mergePostfix(Expression* e1, Expression* e2)
{
  Expression::Kind k1 = e1->kind();
  Expression::Kind k2 = e2->kind();

  // New array expressions take precedence over subscript expressions
  SELECT(Expression::NEWARRAYEXPRESSION, Expression::SUBSCRIPTEXPRESSION);

  // There should be no other ambiguities...
  noMerge("postfix expressions", e1, e2);
}


void ParseEnv::noMerge(char const* desc, Expression* e1, Expression* e2)
{
  cout << toString(e1->loc)
       << ": error: unable to merge "
       << desc
       << ' '
       << e1->kindName()
       << " and "
       << e2->kindName()
       << endl;
  abort();
}


LocString * /*owner*/ ParseEnv::ls(SourceLoc loc, char const *name)
{
  return new LocString(loc, str(name));
}


void ParseEnv::error(SourceLoc loc, char const *msg)
{
  cout << toString(loc) << ": error: " << msg << endl;
  errors++;
}


void ParseEnv::warning(SourceLoc loc, char const *msg)
{
  cout << toString(loc) << ": warning: " << msg << endl;
  warnings++;
}


void ParseEnv::diagnose3(Bool3 b, SourceLoc loc, char const *msg)
{
  if (!b) {
    error(loc, msg);
  }
  else if (b == B3_WARN) {
    warning(loc, msg);
  }
}

// EOF
