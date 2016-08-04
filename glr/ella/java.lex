/* cc.lex            see license.txt for copyright and terms of use
 * flex description of scanner for Java souce
 */

/* ----------------------- C definitions ---------------------- */
%{

#include "lexer.h"       // Lexer class

// this works around a problem with cygwin & fileno
#define YY_NEVER_INTERACTIVE 1

%}


/* -------------------- flex options ------------------ */
/* no wrapping is needed; setting this means we don't have to link with libfl.a */
%option noyywrap

/* don't use the default-echo rules */
%option nodefault

/* I don't call unput */
%option nounput

/* generate a c++ lexer */
%option c++

/* use the "fast" algorithm with no table compression */
%option full

/* utilize character equivalence classes */
%option ecs

/* the scanner is never interactive */
%option never-interactive

/* and I will define the class (lexer.h) */
%option yyclass="Lexer"

/* output file name */
  /* dsw: Arg!  Don't do this, since it is not overrideable from the
     command line with -o, which I consider to be a flex bug. */
  /* sm: fair enough; agreed */
  /* %option outfile="lexer.yy.cc" */

/* ------------------- definitions -------------------- */
/* newline */
NL            [\n\r]

/* anything but newline */
NOTNL         .

/* any of 256 source characters */
ANY           ({NOTNL}|{NL})

/* backslash */
BACKSL        "\\"

/* end of line (would like EOF to qualify also, but flex doesn't allow it */
EOL           {NL}

/* letter or underscore */
LETTER        [A-Za-z_\$]

/* letter or underscore or digit */
ALNUM         [A-Za-z_\$0-9]

/* digit */
DIGIT         [0-9]
HEXDIGIT      [0-9A-Fa-f]

/* sequence of decimal digits */
DIGITS        ({DIGIT}+)

/* integer suffix */
INT_SUFFIX    [lL]

/* sign of a number */
SIGN          ("+"|"-")

/* floating-point exponent */
EXPONENT      ([eE]{SIGN}?{DIGITS})

/* floating-point suffix letter */
FLOAT_SUFFIX  [fdFD]

/* normal string character: any but quote, newline, or backslash */
STRCHAR       [^\"\n\r\\]

/* (start of) an escape sequence */
ESCAPE        ({BACKSL}{ANY})

/* double quote */
QUOTE         [\"]

/* normal character literal character: any but single-quote, newline, or backslash */
CCHAR         [^\'\n\r\\]

/* single quote */
TICK          [\']


/* ------------- token definition rules --------------- */
%%

  /* this comment is replaced, by an external script, with whatever
   * additional rules a language extension author desires */
  /* EXTENSION RULES GO HERE */


  /* operators, punctuators and keywords: tokens with one spelling */
"abstract"         return tok(TOK_ABSTRACT);
"boolean"          return tok(TOK_BOOLEAN);
"break"            return tok(TOK_BREAK);
"byte"             return tok(TOK_BYTE);
"case"             return tok(TOK_CASE);
"catch"            return tok(TOK_CATCH);
"char"             return tok(TOK_CHAR);
"class"            return tok(TOK_CLASS);
"const"            return tok(TOK_CONST);
"continue"         return tok(TOK_CONTINUE);
"default"          return tok(TOK_DEFAULT);
"do"               return tok(TOK_DO);
"double"           return tok(TOK_DOUBLE);
"else"             return tok(TOK_ELSE);
"extends"          return tok(TOK_EXTENDS);
"false"            return tok(TOK_FALSE);
"final"            return tok(TOK_FINAL);
"finally"          return tok(TOK_FINALLY);
"float"            return tok(TOK_FLOAT);
"for"              return tok(TOK_FOR);
"goto"             return tok(TOK_GOTO);
"if"               return tok(TOK_IF);
"implements"       return tok(TOK_IMPLEMENTS);
"import"           return tok(TOK_IMPORT);
"instanceof"       return tok(TOK_INSTANCEOF);
"int"              return tok(TOK_INT);
"interface"        return tok(TOK_INTERFACE);
"long"             return tok(TOK_LONG);
"native"           return tok(TOK_NATIVE);
"new"              return tok(TOK_NEW);
"null"             return tok(TOK_NULL);
"package"          return tok(TOK_PACKAGE);
"private"          return tok(TOK_PRIVATE);
"protected"        return tok(TOK_PROTECTED);
"public"           return tok(TOK_PUBLIC);
"return"           return tok(TOK_RETURN);
"short"            return tok(TOK_SHORT);
"static"           return tok(TOK_STATIC);
"strictfp"         return tok(TOK_STRICTFP);
"super"            return tok(TOK_SUPER);
"switch"           return tok(TOK_SWITCH);
"synchronized"     return tok(TOK_SYNCHRONIZED);
"this"             return tok(TOK_THIS);
"throw"            return tok(TOK_THROW);
"throws"           return tok(TOK_THROWS);
"transient"        return tok(TOK_TRANSIENT);
"true"             return tok(TOK_TRUE);
"try"              return tok(TOK_TRY);
"void"             return tok(TOK_VOID);
"volatile"         return tok(TOK_VOLATILE);
"while"            return tok(TOK_WHILE);

"("                return tok(TOK_LPAREN);
")"                return tok(TOK_RPAREN);
"["                return tok(TOK_LBRACKET);
"]"                return tok(TOK_RBRACKET);
"."                return tok(TOK_DOT);
"!"                return tok(TOK_BANG);
"~"                return tok(TOK_TILDE);
"+"                return tok(TOK_PLUS);
"-"                return tok(TOK_MINUS);
"++"               return tok(TOK_PLUSPLUS);
"--"               return tok(TOK_MINUSMINUS);
"&"                return tok(TOK_AND);
"*"                return tok(TOK_STAR);
"/"                return tok(TOK_SLASH);
"%"                return tok(TOK_PERCENT);
"<<"               return tok(TOK_LEFTSHIFT);
">>"               return tok(TOK_RIGHTSHIFT);
">>>"              return tok(TOK_URIGHTSHIFT);
"<"                return tok(TOK_LESSTHAN);
"<="               return tok(TOK_LESSEQ);
">"                return tok(TOK_GREATERTHAN);
">="               return tok(TOK_GREATEREQ);
"=="               return tok(TOK_EQUALEQUAL);
"!="               return tok(TOK_NOTEQUAL);
"^"                return tok(TOK_XOR);
"|"                return tok(TOK_OR);
"&&"               return tok(TOK_ANDAND);
"||"               return tok(TOK_OROR);
"?"                return tok(TOK_QUESTION);
":"                return tok(TOK_COLON);
"="                return tok(TOK_EQUAL);
"*="               return tok(TOK_STAREQUAL);
"/="               return tok(TOK_SLASHEQUAL);
"%="               return tok(TOK_PERCENTEQUAL);
"+="               return tok(TOK_PLUSEQUAL);
"-="               return tok(TOK_MINUSEQUAL);
"&="               return tok(TOK_ANDEQUAL);
"^="               return tok(TOK_XOREQUAL);
"|="               return tok(TOK_OREQUAL);
"<<="              return tok(TOK_LEFTSHIFTEQUAL);
">>="              return tok(TOK_RIGHTSHIFTEQUAL);
">>>="             return tok(TOK_URIGHTSHIFTEQUAL);
","                return tok(TOK_COMMA);
";"                return tok(TOK_SEMICOLON);
"{"                return tok(TOK_LBRACE);
"}"                return tok(TOK_RBRACE);

  /* identifier: e.g. foo */
{LETTER}{ALNUM}* {
  return svalTok(TOK_NAME);
}

  /* integer literal; dec, oct, or hex */
[1-9][0-9]*{INT_SUFFIX}?           |
[0][0-7]*{INT_SUFFIX}?             |
[0][xX]{HEXDIGIT}+{INT_SUFFIX}?    {
  return svalTok(TOK_INT_LITERAL);
}

  /* hex literal with nothing after the 'x' */
[0][xX] {
  err("hexadecimal literal with nothing after the 'x'");
  return svalTok(TOK_INT_LITERAL);
}

  /* floating literal */
{DIGITS}"."{DIGITS}?{EXPONENT}?{FLOAT_SUFFIX}?   |
"."{DIGITS}{EXPONENT}?{FLOAT_SUFFIX}?	         |
{DIGITS}{EXPONENT}?{FLOAT_SUFFIX}?               {
  return svalTok(TOK_FLOAT_LITERAL);
}

  /* floating literal with no digits after the 'e' */
{DIGITS}"."{DIGITS}?[eE]{SIGN}?   |
"."{DIGITS}[eE]{SIGN}?            |
{DIGITS}[eE]{SIGN}?               {
  err("floating literal with no digits after the 'e'");
  
  /* in recovery rules like this it's best to yield the best-guess
   * token type, instead of some TOK_ERROR, so the parser can still
   * try to make sense of the input; having reported the error is
   * sufficient to ensure that later stages won't try to interpret
   * the lexical text of this token as a floating literal */
  return svalTok(TOK_FLOAT_LITERAL);
}

  /* string literal */
{QUOTE}({STRCHAR}|{ESCAPE})*{QUOTE}    {
  return svalTok(TOK_STRING_LITERAL);
}

  /* string literal missing final quote */
{QUOTE}({STRCHAR}|{ESCAPE})*{EOL}   {
  err("string literal missing final `\"'");
  return svalTok(TOK_STRING_LITERAL);     // error recovery
}

  /* unterminated string literal; maximal munch causes us to prefer
   * either of the above two rules when possible; the trailing
   * optional backslash is needed so the scanner won't back up in that
   * case; NOTE: this can only happen if the file ends in the string
   * and there is no newline before the EOF */
{QUOTE}({STRCHAR}|{ESCAPE})*{BACKSL}? {
  err("unterminated string literal");
  yyterminate();
}

  /* character literal */
{TICK}({CCHAR}|{ESCAPE}){TICK}   {
  return svalTok(TOK_CHAR_LITERAL);
}

  /* incomplete character literal */
{TICK}({CCHAR}|{ESCAPE})?{ANY}?  {
  err("incomplete/unterminated character literal");  
  return svalTok(TOK_CHAR_LITERAL);     // error recovery
}

  /* whitespace */
  /* 10/20/02: added '\r' to accomodate files coming from Windows; this
   * could be seen as part of the mapping from physical source file
   * characters to the basic character set (cppstd 2.1 para 1 phase 1),
   * except that it doesn't happen for chars in string/char literals... */
[ \t\n\f\v\r]+  {
  whitespace();
}

  /* C++ comment */
  /* we don't match the \n because that way this works at EOF */
"//"{NOTNL}*    {
  whitespace();
}

  /* C comment */
"/""*"([^*]|"*"*[^*/])*"*"+"/"     {
  // the pattern is a little complicated because the naive one,
  //   "/""*"([^*]|"*"[^/])*"*/"
  // fails to match e.g. "/***/" 
  whitespace();
}

  /* unterminated C comment */
"/""*"([^*]|"*"*[^*/])*"*"*        {
  err("unterminated /""*...*""/ comment");
  yyterminate();
}

  /* illegal */
.  {
  updLoc();
  err(stringc << "illegal character: `" << yytext[0] << "'");
}

<<EOF>> {
  srcFile->doneAdding();
  yyterminate();
}


%%
/**************/
/* extra code */
/**************/



// another C comment system using a start state; I chose to (fix and)
// use the single-line rule instead, so that the entire thing would be
// matched at once within the FSM instead of dropping out for user
// actions
#if 0
/* exclusive start state for when inside a slash-star style comment */
%x IN_C_COMMENT

  /* C comment; dsw: one that actually works! */
"/""*" {
  yymore();
  BEGIN IN_C_COMMENT;
}
<IN_C_COMMENT>[^*]+ {
  yymore();
}
<IN_C_COMMENT>"*"+"/" {
  whitespace();
  BEGIN INITIAL;
}
<IN_C_COMMENT>"*"+ {
  /* NOTE: this rule must come after the above rule */
  yymore();
}
<IN_C_COMMENT><<EOF>> {
  /* TODO: I don't know why flex doesn't give me an error if I omit this rule, since -f is used */
  err("unterminated /**/ comment");
  whitespace();
  /* dsw: TODO: I think I just have to replicate this here or we could factor it out */
  srcFile->doneAdding();
  yyterminate();
}
#endif // 0
