package superc.p4parser;

import superc.core.Syntax.Layout;
import superc.core.Syntax.PreprocessorTag;
import superc.core.Syntax.Language;

public enum P4Tag implements superc.core.Syntax.LanguageTag {


ABSTRACT(getID("ABSTRACT"), "abstract"),
ACTION(getID("ACTION"), "action"),
ACTIONS(getID("ACTIONS"), "actions"),
APPLY(getID("APPLY"), "apply"),
BOOL(getID("BOOL"), "bool"),
BIT(getID("BIT"), "bit"),
CONST(getID("CONST"), "const"),
CONTROL(getID("CONTROL"), "control"),
DEFAULT(getID("DEFAULT"), "default"),
ELSE(getID("ELSE"), "else"),
ENTRIES(getID("ENTRIES"), "entries"),
ENUM(getID("ENUM"), "enum"),
ERROR(getID("ERROR"), "error"),
EXIT(getID("EXIT"), "exit"),
EXTERN(getID("EXTERN"), "extern"),
FALSE(getID("FALSE"), "false"),
HEADER(getID("HEADER"), "header"),
HEADER_UNION(getID("HEADER_UNION"), "header_union"),
IF(getID("IF"), "if"),
IN(getID("IN"), "in"),
INOUT(getID("INOUT"), "inout"),
INT(getID("INT"), "int"),
KEY(getID("KEY"), "key"),
MATCH_KIND(getID("MATCH_KIND"), "match_kind"),
TYPE(getID("TYPE"), "type"),
OUT(getID("OUT"), "out"),
PARSER(getID("PARSER"), "parser"),
PACKAGE(getID("PACKAGE"), "package"),
RETURN(getID("RETURN"), "return"),
SELECT(getID("SELECT"), "select"),
STATE(getID("STATE"), "state"),
STRING(getID("STRING"), "string"),
STRUCT(getID("STRUCT"), "struct"),
SWITCH(getID("SWITCH"), "switch"),
TABLE(getID("TABLE"), "table"),
THIS(getID("THIS"), "this"),
TRANSITION(getID("TRANSITION"), "transition"),
TRUE(getID("TRUE"), "true"),
TUPLE(getID("TUPLE"), "tuple"),
TYPEDEF(getID("TYPEDEF"), "typedef"),
VARBIT(getID("VARBIT"), "varbit"),
VALUESET(getID("VALUESET"), "value_set"),
VOID(getID("VOID"), "void"),
DONTCARE(getID("DONTCARE"), "_"),

IDENTIFIER(getID("IDENTIFIER"), null, true),
INTEGER(getID("INTEGER"), null, false, PreprocessorTag.NUMBER),
FLOATING_CONSTANT(getID("FLOATING_CONSTANT"), null, false, PreprocessorTag.NUMBER),
PPNUM(getID("PPNUM"), null, false, PreprocessorTag.NUMBER),
L_PAREN(getID("L_PAREN"), "(", PreprocessorTag.OPEN_PAREN),
R_PAREN(getID("R_PAREN"), ")", PreprocessorTag.CLOSE_PAREN),
COMMA(getID("COMMA"), ",", PreprocessorTag.COMMA),
HASH(getID("HASH"), "#", PreprocessorTag.HASH),
DHASH(getID("DHASH"), "##", PreprocessorTag.DOUBLE_HASH),

RANGE(getID("RANGE"), ".."),
MASK(getID("MASK"), "&&&"),
SHL(getID("SHL"), "<<"),
AND(getID("AND"), "&&"),
OR(getID("OR"), "||"),
EQ(getID("EQ"), "=="),
NE(getID("NE"), "!="),
GE(getID("GE"), ">="),
LE(getID("LE"), "<="),
PP(getID("PP"), "++"),

PLUS(getID("PLUS"), "+"),

PLUS_SAT(getID("PLUS_SAT"), "|+|"),

MINUS(getID("MINUS"), "-"),

MINUS_SAT(getID("MINUS_SAT"), "|-|"),
MUL(getID("MUL"), "*"),
DIV(getID("DIV"), "/"),
MOD(getID("MOD"), "%"),
BIT_OR(getID("BIT_OR"), "|"),
BIT_AND(getID("BIT_AND"), "&"),
BIT_XOR(getID("BIT_XOR"), "^"),
COMPLEMENT(getID("COMPLEMENT"), "~"),
L_BRACKET(getID("L_BRACKET"), "["),
R_BRACKET(getID("R_BRACKET"), "]"),

L_BRACE(getID("L_BRACE"), "{"),
R_BRACE(getID("R_BRACE"), "}"),
L_ANGLE(getID("L_ANGLE"), "<"),
R_ANGLE_SHIFT(getID("R_ANGLE_SHIFT"), ">"),
R_ANGLE(getID("R_ANGLE"), ">"),

NOT(getID("NOT"), "!"),
COLON(getID("COLON"), ":"),
QUESTION(getID("QUESTION"), "?"),

DOT(getID("DOT"), "."),
ASSIGN(getID("ASSIGN"), "="),
SEMICOLON(getID("SEMICOLON"), ";"),
AT(getID("AT"), "@"),
STRING_LITERAL(getID("STRING_LITERAL"), null, false),
TYPE_IDENTIFIER(getID("TYPE_IDENTIFIER"), null, true),
END_PRAGMA(getID("END_PRAGMA"), null, PreprocessorTag.END_PRAGMA),
PRAGMA(getID("PRAGMA"), null, PreprocessorTag.PRAGMA)
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
