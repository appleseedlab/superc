// lexer.cc            see license.txt for copyright and terms of use
// code for lexer.h

#include "lexer.h"       // this module
#include "java_lang.h"   // JavaLang

#include <ctype.h>       // isdigit
#include <stdlib.h>      // atoi


/* 
 * Note about nonseparating tokens and the 'checkForNonsep' function:
 *
 * To diagnose and report erroneous syntax like "0x5g", which would
 * naively be parsed as "0x5" and "g" (two legal tokens), I divide
 * all tokens into two classes: separating and nonseparating.
 *
 * Separating tokens are allowed to be adjacent to each other and
 * to nonseparating tokens.  An example is "(".
 *
 * Nonseparating tokens are not allowed to be adjacent to each other.
 * They must be separated by either whitespace, or at least one
 * separating token.  The nonseparating tokens are identifiers,
 * alphabetic keywords, and literals.  The lexer would of course never
 * yield two adjacent keywords, due to maximal munch, but classifying 
 * such an event as an error is harmless.
 * 
 * By keeping track of whether the last token yielded is separating or
 * not, we'll see (e.g.) "0x5g" as two consecutive nonseparating tokens,
 * and can report that as an error.
 *
 * The C++ standard is rather vague on this point as far as I can
 * tell.  I haven't checked the C standard.  In the C++ standard,
 * section 2.6 paragraph 1 states:
 *
 *  "There are five kinds of tokens: identifiers, keywords, literals,
 *   operators, and other separators.  Blanks, horizontal and
 *   vertical tabs, newlines, formfeeds, and comments (collectively,
 *   "whitespace"), as described below, are ignored except as they
 *   serve to separate tokens.  [Note: Some white space is required
 *   to separate otherwise adjacent identifiers, keywords, numeric
 *   literals, and alternative tokens containing alphabetic
 *   characters.]"
 *
 * The fact that the restriction is stated only in a parenthetical note
 * is of course nonideal.  I think the qualifier "numeric" on "literals"
 * is a mistake, otherwise "a'b'" would be a legal token sequence.  I
 * do not currently implement the "alternative tokens".
 *
 * Update: Mozilla includes things like "foo""bar", i.e. directly
 * adjacent string literals.  Therefore I'm going to interpret (the
 * note in) the standard literally, and take char and string literals
 * to be separating.
 */


// -------------------- TokenType ---------------------
// these aren't emitted into java_tokens.cc because doing so would
// make that output dependent on smbase/xassert.h
char const *toString(TokenType type)
{
  xassert(NUM_TOKEN_TYPES == tokenNameTableSize);
  xassert((unsigned)type < (unsigned)NUM_TOKEN_TYPES);
  return tokenNameTable[type];
}

TokenFlag tokenFlags(TokenType type)
{
  xassert((unsigned)type < (unsigned)NUM_TOKEN_TYPES);
  return (TokenFlag)tokenFlagTable[type];
}


// ------------------------ Lexer -------------------
Lexer::Lexer(StringTable &s, JavaLang &L, char const *fname)
  : BaseLexer(s, fname),

    prevIsNonsep(false),

    lang(L)
{
  // prime this lexer with the first token
  getTokenFunc()(this);
}


Lexer::Lexer(StringTable &s, JavaLang &L, SourceLoc initLoc,
             char const *buf, int len)
  : BaseLexer(s, initLoc, buf, len),

    prevIsNonsep(false),

    lang(L)
{
  // do *not* prime the lexer; I think it is a mistake above, but
  // am leaving it for now
}


Lexer::~Lexer()
{}


void Lexer::whitespace()
{
  BaseLexer::whitespace();

  // various forms of whitespace can separate nonseparating tokens
  prevIsNonsep = false;
}


// this, and 'svalTok', are out of line because I don't want the
// yylex() function to be enormous; I want that to just have a bunch
// of calls into these routines, which themselves can then have
// plenty of things inlined into them
int Lexer::tok(TokenType t)
{
  checkForNonsep(t);
  updLoc();
  sval = NULL_SVAL;     // catch mistaken uses of 'sval' for single-spelling tokens
  return t;
}


int Lexer::svalTok(TokenType t) 
{
  checkForNonsep(t);
  updLoc();
  sval = (SemanticValue)addString(yytext, yyleng);
  return t;
}


STATICDEF void Lexer::tokenFunc(LexerInterface *lex)
{
  Lexer *ths = static_cast<Lexer*>(lex);

  // call into the flex lexer; this updates 'loc' and sets
  // 'sval' as appropriate
  ths->type = ths->yylex();
}


Lexer::NextTokenFunc Lexer::getTokenFunc() const
{
  return &Lexer::tokenFunc;
}


string Lexer::tokenDesc() const
{
  if (tokenFlags((TokenType)type) & TF_MULTISPELL) {
    // for tokens with multiple spellings, decode 'sval' as a
    // StringRef
    //return string((StringRef)sval);
    return stringc << toString((TokenType)type) << ": " << (StringRef)sval;
  }
  else {
    // for all others, consult the static table
    return string(toString((TokenType)type));
  }
}


string Lexer::tokenKindDesc(int kind) const
{
  // static table only
  return toString((TokenType)kind);
}


// EOF
