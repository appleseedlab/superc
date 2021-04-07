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

#ifndef LANGUAGE_TAGS

/**
 * Create a C Language Syntax object.  The "text" parameter must have
 * quotes, since it will be used as a Java string constant.
 */
# define LANGUAGE(token, text)                                        \
  text {                                                              \
    Language<P4Tag> syntax = new Language<P4Tag>(P4Tag.token);           \
                                                                      \
    syntax.setLocation(new Location(fileName, yyline+1, yycolumn+1)); \
                                                                      \
    return syntax;                                                    \
  }

/**
 * Create a C Text Syntax object.
 */
# define TEXT(token, regex, hasName)                                \
  regex {                                                           \
    Text<P4Tag> syntax = new Text<P4Tag>(P4Tag.token, yytext());       \
                                                                    \
    syntax.setLocation(new Location(fileName, yyline+1, yycolumn)); \
                                                                    \
    return syntax;                                                  \
  }

/**
 * Create a preprocessor language token.
 */
# define PREPROCESSOR(token, pptag, text) LANGUAGE(token, text)

/**
 * Create a preprocessor text language token.
 */
# define PREPROCESSOR_TEXT(token, pptag, regex, hasname) TEXT(token, regex, false)

/**
 * Create a language token when jflex regex
 */
# define LANGUAGE_FULL(token, jflex_text, tag_text) LANGUAGE(token, jflex_text)

#else
# define LANGUAGE(token, text) token(getID(#token), text),
# define TEXT(token, regex, hasName) token(getID(#token), null, hasName),
# define PREPROCESSOR(token, pptag, text) \
  token(getID(#token), text, PreprocessorTag.pptag),
# define PREPROCESSOR_TEXT(token, pptag, regex, hasName) \
  token(getID(#token), null, hasName, PreprocessorTag.pptag),
# define LANGUAGE_FULL(token, jflex_text, tag_text) LANGUAGE(token, tag_text)
#endif


#ifndef LANGUAGE_TAGS // Generate the lexer specification.
package PACKAGE_NAME;

import xtc.tree.Location;

import superc.core.Syntax;
import superc.core.Syntax.Language;
import superc.core.Syntax.PreprocessorTag;
import superc.core.Syntax.Text;
import superc.core.Syntax.Layout;
import superc.core.Syntax.EOF;

%%

%{

  /** Used to build strings of comments. */
  private StringBuilder comment = null;

  /** Used to track whether comments have newline characters. */
  private boolean commentnl = false;

  /** The name of the file being lexed. */
  private String fileName = null;

  private int saveState = 0;

  /** Returns the name of the file being lexed. */
  public void setFileName(String fileName) {
    this.fileName = fileName;
  }

%}

%eofval{
  // System.err.println("hereatend");
  EOF syntax = new EOF();

  syntax.setLocation(new Location(fileName, yyline+1, yycolumn));
  return syntax;
%eofval}

%class P4Lexer
%implements superc.core.Lexer
%unicode
%type Syntax

%line
%column

%state COMMENT PRAGMA_LINE

/* Uncomment this for a lexer debugging.  See the JFlex manual. */
// %debug

identifier=[A-Za-z_][A-Za-z0-9_]*

simple_escape=[nrt\'\"?\\]
escape_sequence=[\\]({simple_escape})
s_char=[^\"\\]|{escape_sequence}|\\\n

// /* Haven't done for the rest of the number types who last make value is true (numberUnparsed) */

numbersReg=0[xX][0-9a-fA-F_]+|0[dD][0-9_]+|0[oO][0-7_]+|0[bB][01_]+|[0-9][0-9_]*
numberUnparsed=[0-9]+[ws]0[xX][0-9a-fA-F_]+|[0-9]+[ws]0[dD][0-9_]+|[0-9]+[ws]0[oO][0-7_]+|[0-9]+[ws]0[bB][01_]+|[0-9]+[ws][0-9_]+
numbers=({numbersReg}|{numberUnparsed})

/* Define floating point number constants. */
exponent_part=([eE]|[pP])[-+]?[0-9]+
fractional_constant=([0-9]*"."[0-9]+)|([0-9]+".")
floating_constant=(({fractional_constant}{exponent_part}?)|([0-9]+{exponent_part}))[FfLl]?

/* Define a catch-all for preprocessor numbers.  These may not
necessarily be valid P4 numeric constants, but they are valid
preprocessor numbers. */
preprocessing_number="."?[0-9]+([0-9a-zA-Z._]|{exponent_part})*

whitespace=[ \t\r]+
newline=\n
linecomment="//"[^\r\n]*{newline}


%%

<YYINITIAL> {

// yyline + 1, yychar, yychar + yylength()

// JFLex increments its line counter for form-feeds, but GCC does not.
// {form_feed}
// { yyline--; return new Layout(yytext(), false); }

{whitespace}+
{ return new Layout(yytext(), false); }

{whitespace}*({newline}|{linecomment})+{whitespace}*
{
  if (saveState == PRAGMA_LINE) {
    for (int i = 0; i < yytext().length(); i++) {
        if (yytext().charAt(i) == '\n') {
          saveState = 0 ; 
          Language<P4Tag> syntax = new Language<P4Tag>(P4Tag.END_PRAGMA);                                                                
          syntax.setLocation(new Location(fileName, yyline+1, yycolumn+1));                                                        
          return syntax;
        }
    }
  } 
  return new Layout(yytext(), true); 
}

#else // Generate the P4Tag enumeration.
package PACKAGE_NAME;

import superc.core.Syntax.Layout;
import superc.core.Syntax.PreprocessorTag;
import superc.core.Syntax.Language;

public enum P4Tag implements superc.core.Syntax.LanguageTag {
#endif

LANGUAGE(ABSTRACT,"abstract")
LANGUAGE(ACTION,"action")
LANGUAGE(ACTIONS,"actions")
LANGUAGE(APPLY,"apply")
LANGUAGE(BOOL,"bool")
LANGUAGE(BIT,"bit")
LANGUAGE(CONST,"const")
LANGUAGE(CONTROL,"control")
LANGUAGE(DEFAULT,"default")
LANGUAGE(ELSE,"else")
LANGUAGE(ENTRIES,"entries")
LANGUAGE(ENUM,"enum")
LANGUAGE(ERROR,"error")
LANGUAGE(EXIT,"exit")
LANGUAGE(EXTERN,"extern")
LANGUAGE(FALSE,"false")
LANGUAGE(HEADER,"header")
LANGUAGE(HEADER_UNION,"header_union")
LANGUAGE(IF,"if")
LANGUAGE(IN,"in")
LANGUAGE(INOUT,"inout")
LANGUAGE(INT,"int")
LANGUAGE(KEY,"key")
LANGUAGE(MATCH_KIND,"match_kind")
LANGUAGE(TYPE,"type")
LANGUAGE(OUT,"out")
LANGUAGE(PARSER,"parser")
LANGUAGE(PACKAGE,"package")
LANGUAGE(RETURN,"return")
LANGUAGE(SELECT,"select")
LANGUAGE(STATE,"state")
LANGUAGE(STRING,"string")
LANGUAGE(STRUCT,"struct")
LANGUAGE(SWITCH,"switch")
LANGUAGE(TABLE,"table")
LANGUAGE(THIS,"this")
LANGUAGE(TRANSITION,"transition")
LANGUAGE(TRUE,"true")
LANGUAGE(TUPLE,"tuple")
LANGUAGE(TYPEDEF,"typedef")
LANGUAGE(VARBIT,"varbit")
LANGUAGE(VALUESET,"value_set")
LANGUAGE(VOID,"void")
LANGUAGE(DONTCARE,"_")

TEXT(IDENTIFIER,{identifier},true)
PREPROCESSOR_TEXT(INTEGER,NUMBER,{numbers},false)
PREPROCESSOR_TEXT(FLOATING_CONSTANT,NUMBER,{floating_constant},false)
PREPROCESSOR_TEXT(PPNUM,NUMBER,{preprocessing_number},false)
PREPROCESSOR(L_PAREN,OPEN_PAREN,"(")
PREPROCESSOR(R_PAREN,CLOSE_PAREN,")")
PREPROCESSOR(COMMA,COMMA,",")
PREPROCESSOR(HASH,HASH,"#")
PREPROCESSOR(DHASH,DOUBLE_HASH,"##")

LANGUAGE(RANGE,"..")
LANGUAGE(MASK,"&&&")
LANGUAGE(SHL,"<<")
LANGUAGE(AND,"&&")
LANGUAGE(OR,"||")
LANGUAGE(EQ,"==")
LANGUAGE(NE,"!=")
LANGUAGE(GE,">=")
LANGUAGE(LE,"<=")
LANGUAGE(PP,"++")

LANGUAGE(PLUS,"+")

LANGUAGE(PLUS_SAT,"|+|")

LANGUAGE(MINUS,"-")

LANGUAGE(MINUS_SAT,"|-|")
LANGUAGE(MUL,"*")
LANGUAGE(DIV,"/")
LANGUAGE(MOD,"%")
LANGUAGE(BIT_OR,"|")
LANGUAGE(BIT_AND,"&")
LANGUAGE(BIT_XOR,"^")
LANGUAGE(COMPLEMENT,"~")
LANGUAGE(L_BRACKET,"[")
LANGUAGE(R_BRACKET,"]")

LANGUAGE(L_BRACE,"{")
LANGUAGE(R_BRACE,"}")
LANGUAGE(L_ANGLE,"<")
LANGUAGE_FULL(R_ANGLE_SHIFT,">"/">", ">")
LANGUAGE(R_ANGLE,">")

LANGUAGE(NOT,"!")
LANGUAGE(COLON,":")
LANGUAGE(QUESTION,"?")

LANGUAGE(DOT,".")
LANGUAGE(ASSIGN,"=")
LANGUAGE(SEMICOLON,";")
LANGUAGE(AT,"@")

// LANGUAGE(PRAGMA, "@pragma")

// LANGUAGE(BACKSLASH,"\\")

// #define CHARACTER_CONSTANT_regex "L"?\'{c_char}+\'
#define STRING_LITERAL_regex \"{s_char}*\"
// TEXT(STRING_LITERAL,CHARACTER_CONSTANT_regex,false)
TEXT(STRING_LITERAL,STRING_LITERAL_regex,false)

#ifndef LANGUAGE_TAGS

"/*" {
yybegin(COMMENT);
comment = new StringBuilder();
comment.append(yytext());
commentnl = false;
}
"# "[0-9]+[ ]*\"[^\"]*\"[ \t]*[ 0-9]*         { return new Layout(yytext(), true); }

"@pragma"       { saveState = PRAGMA_LINE; 
                  yybegin(YYINITIAL);
                  Language<P4Tag> syntax = new Language<P4Tag>(P4Tag.PRAGMA);                                                                
                  syntax.setLocation(new Location(fileName, yyline+1, yycolumn+1));                                                 
                  return syntax; 
                }
}

<COMMENT> {
"*/" {
comment.append(yytext()); yybegin(YYINITIAL);
return new Layout(comment.toString(), false);
}

[^*\n]+ {comment.append(yytext());}
"*" {comment.append(yytext());}
\n {comment.append(yytext()); commentnl = true;}
}

#else
TYPE_IDENTIFIER(getID("TYPE_IDENTIFIER"), null, true),
END_PRAGMA(getID("END_PRAGMA"), null),
PRAGMA(getID("PRAGMA"), "@pragma")
;

  private final int id;
  private final String text;
  private final boolean hasName;
  private final PreprocessorTag ppTag;

  P4Tag(int id, String text, boolean hasName, PreprocessorTag ppTag) {
    this.id = id;
    this.text = text;
    this.hasName = hasName;
    this.ppTag = ppTag;
  }

  P4Tag(int id, String text, boolean hasName) {
    this(id, text, hasName, PreprocessorTag.NONE);
  }

  P4Tag(int id, String text) {
    this(id, text, isName(text), PreprocessorTag.NONE);
  }

  P4Tag(int id, String text, PreprocessorTag ppTag) {
    this(id, text, isName(text), ppTag);
  }

  public int getID() {
    return id;
  }

  public String getText() {
    return text;
  }

  public boolean hasName() {
    return hasName;
  }

  public PreprocessorTag ppTag() {
    return ppTag;
  }

  static boolean isName(String name) {
    if (null == name || name.length() == 0) return false;

    return Character.isLetter(name.charAt(0)) || '_' == name.charAt(0);
  }

  static int getID(String token) {
    for (int id = 0; id < P4ParseTables.getInstance().YYNTOKENS; id++) {
      if (P4ParseTables.getInstance().yytname[id].equals(token)) {
        return id;
      }
    }
    System.err.println(token);
    System.err.println("error: invalid token name");
    System.exit(1);

    return -1;
  }

}
#endif
