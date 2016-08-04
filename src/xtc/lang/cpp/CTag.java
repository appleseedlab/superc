package xtc.lang.cpp;

import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.PreprocessorTag;
import xtc.lang.cpp.Syntax.Language;

public enum CTag implements xtc.lang.cpp.Syntax.LanguageTag {


AUTO(getID("AUTO"), "auto"),
BREAK(getID("BREAK"), "break"),
CASE(getID("CASE"), "case"),
CHAR(getID("CHAR"), "char"),
CONST(getID("CONST"), "const"),
CONTINUE(getID("CONTINUE"), "continue"),
DEFAULT(getID("DEFAULT"), "default"),
DO(getID("DO"), "do"),
DOUBLE(getID("DOUBLE"), "double"),
ELSE(getID("ELSE"), "else"),
ENUM(getID("ENUM"), "enum"),
EXTERN(getID("EXTERN"), "extern"),
FLOAT(getID("FLOAT"), "float"),
FOR(getID("FOR"), "for"),
GOTO(getID("GOTO"), "goto"),
IF(getID("IF"), "if"),
INT(getID("INT"), "int"),
LONG(getID("LONG"), "long"),
REGISTER(getID("REGISTER"), "register"),
RETURN(getID("RETURN"), "return"),
SHORT(getID("SHORT"), "short"),
SIGNED(getID("SIGNED"), "signed"),
SIZEOF(getID("SIZEOF"), "sizeof"),
STATIC(getID("STATIC"), "static"),
STRUCT(getID("STRUCT"), "struct"),
SWITCH(getID("SWITCH"), "switch"),
TYPEDEF(getID("TYPEDEF"), "typedef"),
UNION(getID("UNION"), "union"),
UNSIGNED(getID("UNSIGNED"), "unsigned"),
VOID(getID("VOID"), "void"),
VOLATILE(getID("VOLATILE"), "volatile"),
WHILE(getID("WHILE"), "while"),


_BOOL(getID("_BOOL"), "_Bool"),
_COMPLEX(getID("_COMPLEX"), "_Complex"),
INLINE(getID("INLINE"), "inline"),




__ALIGNOF(getID("__ALIGNOF"), "__alignof"),
__ALIGNOF__(getID("__ALIGNOF__"), "__alignof__"),
ASM(getID("ASM"), "asm"),
__ASM(getID("__ASM"), "__asm"),
__ASM__(getID("__ASM__"), "__asm__"),
__ATTRIBUTE(getID("__ATTRIBUTE"), "__attribute"),
__ATTRIBUTE__(getID("__ATTRIBUTE__"), "__attribute__"),
__BUILTIN_OFFSETOF(getID("__BUILTIN_OFFSETOF"), "__builtin_offsetof"),
__BUILTIN_TYPES_COMPATIBLE_P(getID("__BUILTIN_TYPES_COMPATIBLE_P"), "__builtin_types_compatible_p"),
__BUILTIN_VA_ARG(getID("__BUILTIN_VA_ARG"), "__builtin_va_arg"),
__BUILTIN_VA_LIST(getID("__BUILTIN_VA_LIST"), "__builtin_va_list"),
__COMPLEX__(getID("__COMPLEX__"), "__complex__"),
__CONST(getID("__CONST"), "__const"),
__CONST__(getID("__CONST__"), "__const__"),
__EXTENSION__(getID("__EXTENSION__"), "__extension__"),
__INLINE(getID("__INLINE"), "__inline"),
__INLINE__(getID("__INLINE__"), "__inline__"),
__LABEL__(getID("__LABEL__"), "__label__"),
__RESTRICT(getID("__RESTRICT"), "__restrict"),
__RESTRICT__(getID("__RESTRICT__"), "__restrict__"),
__SIGNED(getID("__SIGNED"), "__signed"),
__SIGNED__(getID("__SIGNED__"), "__signed__"),
__THREAD(getID("__THREAD"), "__thread"),
TYPEOF(getID("TYPEOF"), "typeof"),
__TYPEOF(getID("__TYPEOF"), "__typeof"),
__TYPEOF__(getID("__TYPEOF__"), "__typeof__"),
__VOLATILE(getID("__VOLATILE"), "__volatile"),
__VOLATILE__(getID("__VOLATILE__"), "__volatile__"),
__INT128(getID("__INT128"), "__int128"),

IDENTIFIER(getID("IDENTIFIER"), null, true),
INTEGERconstant(getID("INTEGERconstant"), null, false, PreprocessorTag.NUMBER),
OCTALconstant(getID("OCTALconstant"), null, false, PreprocessorTag.NUMBER),
HEXconstant(getID("HEXconstant"), null, false, PreprocessorTag.NUMBER),
FLOATINGconstant(getID("FLOATINGconstant"), null, false, PreprocessorTag.NUMBER),
PPNUM(getID("PPNUM"), null, false, PreprocessorTag.NUMBER),
CHARACTERconstant(getID("CHARACTERconstant"), null, false),
STRINGliteral(getID("STRINGliteral"), null, false),

ARROW(getID("ARROW"), "->"),
ICR(getID("ICR"), "++"),
DECR(getID("DECR"), "--"),
LS(getID("LS"), "<<"),
RS(getID("RS"), ">>"),
LE(getID("LE"), "<="),
GE(getID("GE"), ">="),
EQ(getID("EQ"), "=="),
NE(getID("NE"), "!="),
ANDAND(getID("ANDAND"), "&&"),
OROR(getID("OROR"), "||"),
PLUSassign(getID("PLUSassign"), "+="),
MINUSassign(getID("MINUSassign"), "-="),
MULTassign(getID("MULTassign"), "*="),
DIVassign(getID("DIVassign"), "/="),
MODassign(getID("MODassign"), "%="),
LSassign(getID("LSassign"), "<<="),
RSassign(getID("RSassign"), ">>="),
ANDassign(getID("ANDassign"), "&="),
ERassign(getID("ERassign"), "^="),
ORassign(getID("ORassign"), "|="),

LPAREN(getID("LPAREN"), "(", PreprocessorTag.OPEN_PAREN),
RPAREN(getID("RPAREN"), ")", PreprocessorTag.CLOSE_PAREN),
COMMA(getID("COMMA"), ",", PreprocessorTag.COMMA),
HASH(getID("HASH"), "#", PreprocessorTag.HASH),
DHASH(getID("DHASH"), "##", PreprocessorTag.DOUBLE_HASH),
ELLIPSIS(getID("ELLIPSIS"), "...", PreprocessorTag.ELLIPSIS),

LBRACE(getID("LBRACE"), "{"),
RBRACE(getID("RBRACE"), "}"),
LBRACK(getID("LBRACK"), "["),
RBRACK(getID("RBRACK"), "]"),
DOT(getID("DOT"), "."),
AND(getID("AND"), "&"),
STAR(getID("STAR"), "*"),
PLUS(getID("PLUS"), "+"),
MINUS(getID("MINUS"), "-"),
NEGATE(getID("NEGATE"), "~"),
NOT(getID("NOT"), "!"),
DIV(getID("DIV"), "/"),
MOD(getID("MOD"), "%"),
LT(getID("LT"), "<"),
GT(getID("GT"), ">"),
XOR(getID("XOR"), "^"),
PIPE(getID("PIPE"), "|"),
QUESTION(getID("QUESTION"), "?"),
COLON(getID("COLON"), ":"),
SEMICOLON(getID("SEMICOLON"), ";"),
ASSIGN(getID("ASSIGN"), "="),

AT(getID("AT"), "@"),
USD(getID("USD"), "$"),
BACKSLASH(getID("BACKSLASH"), "\\"),
TYPEDEFname(getID("TYPEDEFname"), null, true);

  private final int id;
  private final String text;
  private final boolean hasName;
  private final PreprocessorTag ppTag;

  CTag(int id, String text, boolean hasName, PreprocessorTag ppTag) {
    this.id = id;
    this.text = text;
    this.hasName = hasName;
    this.ppTag = ppTag;
  }

  CTag(int id, String text, boolean hasName) {
    this(id, text, hasName, PreprocessorTag.NONE);
  }

  CTag(int id, String text) {
    this(id, text, isName(text), PreprocessorTag.NONE);
  }

  CTag(int id, String text, PreprocessorTag ppTag) {
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
    for (int id = 0; id < CParseTables.getInstance().YYNTOKENS; id++) {
      if (CParseTables.getInstance().yytname[id].equals(token)) {
        return id;
      }
    }

    System.err.println("error: invalid token name");
    System.exit(1);

    return -1;
  }

}
