// lexer.h            see license.txt for copyright and terms of use
// lexer for Java source files

#ifndef LEXER_H
#define LEXER_H

#include "baselexer.h"      // BaseLexer
#include "java_tokens.h"    // TokenType

// fwd decls
class JavaLang;             // java_lang.h

// bounds-checking functional interfaces to tables declared in java_tokens.h
char const *toString(TokenType type);
TokenFlag tokenFlags(TokenType type);


// lexer object
class Lexer : public BaseLexer {
private:    // data
  bool prevIsNonsep;               // true if last-yielded token was nonseparating

 public:     // data
  JavaLang &lang;                  // language options

protected:  // funcs
  // see comments at top of lexer.cc
  void checkForNonsep(TokenType t) {
    if (tokenFlags(t) & TF_NONSEPARATOR) {
      if (prevIsNonsep) {
        err("two adjacent nonseparating tokens");
      }
      prevIsNonsep = true;
    }
    else {
      prevIsNonsep = false;
    }
  }

  // consume whitespace
  void whitespace();

  // do everything for a single-spelling token
  int tok(TokenType t);

  // do everything for a multi-spelling token
  int svalTok(TokenType t);

  FLEX_OUTPUT_METHOD_DECLS

public:     // funcs
  // make a lexer to scan the given file
  Lexer(StringTable &strtable, JavaLang &lang, char const *fname);
  Lexer(StringTable &strtable, JavaLang &lang, SourceLoc initLoc,
        char const *buf, int len);
  ~Lexer();

  static void tokenFunc(LexerInterface *lex);
  static void _tokenFunc(LexerInterface *lex);

  // LexerInterface funcs
  virtual NextTokenFunc getTokenFunc() const;
  virtual string tokenDesc() const;
  virtual string tokenKindDesc(int kind) const;
};


#endif // LEXER_H
