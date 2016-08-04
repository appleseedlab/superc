// java_flags.cc            see license.txt for copyright and terms of use
// code for java_flags.h

#include "java_flags.h"   // this module
#include "xassert.h"      // xassert

// the check for array[limit-1] is meant to ensure that there
// are as many specified entries as there are total entries
#define MAKE_TOSTRING(T, limit, array)        \
  char const *toString(T index)               \
  {                                           \
    xassert((unsigned)index < limit);         \
    xassert(array[limit-1] != NULL);          \
    return array[index];                      \
  }


char const * const modifierNames[NUM_MODIFIERS] = {
  "public",
  "protected",
  "private",
  "static",
  "abstract",
  "final",
  "native",
  "synchronized",
  "transient",
  "volatile",
  "strictfp"
};

string bitmapString(int bitmap, char const * const *names, int numflags)
{
  stringBuilder sb;
  int count=0;
  for (int i=0; i<numflags; i++) {
    if (bitmap & (1 << i)) {
      if (count++) {
        sb << " ";
      }
      sb << names[i];
    }
  }

  return sb;
}

string toString(Modifiers m) {
  xassert(modifierNames[NUM_MODIFIERS-1] != NULL);
  return bitmapString(m, modifierNames, NUM_MODIFIERS);
}

char const * const binaryOpNames[NUM_BINARY_OPS] = {
  "*",
  "/",
  "%",
  "+",
  "-",
  "<<",
  ">>",
  ">>>",
  "<",
  ">",
  "<=",
  ">=",
  "instanceof",
  "==",
  "!=",
  "&",
  "^",
  "|",
  "&&",
  "||",
  "="
};

MAKE_TOSTRING(BinaryOperator, NUM_BINARY_OPS, binaryOpNames)

char const * const unaryOpNames[NUM_UNARY_OPS] = {
  "+",
  "-",
  "++",
  "--",
  "++",
  "--",
  "~",
  "!"
};

MAKE_TOSTRING(UnaryOperator, NUM_UNARY_OPS, unaryOpNames)

char const * const basicTypeNames[NUM_TYPES] = {
  "void",
  "byte",
  "short",
  "char",
  "int",
  "long",
  "float",
  "double",
  "boolean"
};

MAKE_TOSTRING(BasicType, NUM_TYPES, basicTypeNames)
