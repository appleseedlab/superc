// java_flags.h            see license.txt for copyright and terms of use
// enumerated flags for parsing Java

// Basically, this module is a set of enums that are used by at
// least two different modules in the Java front end (if they
// were only used by one module, they'd be declared in that
// module instead).  It's intended to be a lightweight module,
// dependent on almost nothing else.
//
// Each enum has a 'toString' that yields a printable representation.
// If it yields 'char const *', then it's guaranteed to be a valid
// pointer with unchanging contents throughout execution.
//
// Those that are OR-able together have the necessary operators
// declared (ENUM_BITWISE_OPS), and their 'toString' uses bitwise-OR
// syntax.

#ifndef JAVA_FLAGS_H
#define JAVA_FLAGS_H

#include "srcloc.h"  // SourceLoc
#include "str.h"     // string

// Modifiers

enum Modifiers {
  MOD_NONE           = 0,
  MOD_PUBLIC         = 0x00000001,
  MOD_PROTECTED      = 0x00000002,
  MOD_PRIVATE        = 0x00000004,
  MOD_STATIC         = 0x00000008,
  MOD_ABSTRACT       = 0x00000010,
  MOD_FINAL          = 0x00000020,
  MOD_NATIVE         = 0x00000040,
  MOD_SYNCHRONIZED   = 0x00000080,
  MOD_TRANSIENT      = 0x00000100,
  MOD_VOLATILE       = 0x00000200,
  MOD_STRICTFP       = 0x00000400,
  ALL_MODIFIERS      = 0x000007FF,
  NUM_MODIFIERS      = 11
};

extern char const * const modifierNames[NUM_MODIFIERS];
string toString(Modifiers m);

// Binary operators

enum BinaryOperator {
  BIN_MULT,
  BIN_DIV,
  BIN_MOD,
  BIN_PLUS,
  BIN_MINUS,
  BIN_LSHIFT,
  BIN_RSHIFT,
  BIN_URSHIFT,
  BIN_LT,
  BIN_GT,
  BIN_LTEQ,
  BIN_GTEQ,
  BIN_INSTANCE,
  BIN_EQ,
  BIN_NOTEQ,
  BIN_BITAND,
  BIN_BITXOR,
  BIN_BITOR,
  BIN_AND,
  BIN_OR,
  BIN_ASSIGN,
  NUM_BINARY_OPS
};

inline bool isValid(BinaryOperator op) {
  return (unsigned)op < NUM_BINARY_OPS;
}
extern char const * const binaryOpNames[NUM_BINARY_OPS];   // "*", ..
char const *toString(BinaryOperator op);

// Unary operators

enum UnaryOperator {
  UN_PLUS,
  UN_MINUS,
  UN_PREINC,
  UN_PREDEC,
  UN_POSTINC,
  UN_POSTDEC,
  UN_BITNOT,
  UN_NOT,
  NUM_UNARY_OPS
};

inline bool isValid(UnaryOperator op) {
  return (unsigned)op < NUM_UNARY_OPS;
}
extern char const * const unaryOpNames[NUM_UNARY_OPS];
char const *toString(UnaryOperator op);

// Basic types

enum BasicType {
  TYPE_VOID,
  TYPE_BYTE,
  TYPE_SHORT,
  TYPE_CHAR,
  TYPE_INT,
  TYPE_LONG,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  TYPE_BOOLEAN,
  NUM_TYPES
};

inline bool isValid(BasicType t) {
  return (unsigned)t < NUM_TYPES;
}
extern char const * const basicTypeNames[NUM_TYPES];
char const *toString(BasicType t);

#endif // JAVA_FLAGS_H
