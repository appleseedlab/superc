/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 115 "p4parser.y"


import xtc.Constants;
import xtc.Limits;

import superc.p4parser.P4Context.SymbolTable.STField;

import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Visitor;

import xtc.util.Pair;

import superc.core.Syntax;
import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;
import superc.core.Syntax.Error;

import xtc.type.AliasT;
import xtc.type.ArrayT;
import xtc.type.BooleanT;
import xtc.type.C;
import xtc.type.CastReference;
import xtc.type.Constant;
import xtc.type.DynamicReference;
import xtc.type.EnumT;
import xtc.type.EnumeratorT;
import xtc.type.ErrorT;
import xtc.type.FieldReference;
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.Reference;
import xtc.type.StaticReference;
import xtc.type.StringReference;
import xtc.type.StructOrUnionT;
import xtc.type.StructT;
import xtc.type.Tagged;
import xtc.type.Type;
import xtc.type.Type.Tag;
import xtc.type.UnionT;
import xtc.type.VariableT;
import xtc.type.VoidT;

import xtc.util.SymbolTable;
import xtc.util.SymbolTable.Scope;
import xtc.util.SingletonIterator;
import xtc.util.Utilities;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.Clauses;

import superc.core.ForkMergeParser;
import superc.core.ForkMergeParser.StackFrame;

import java.util.ArrayList;
import java.util.List;

import org.sat4j.core.VecInt;
import org.sat4j.minisat.SolverFactory;
import org.sat4j.specs.ContradictionException;
import org.sat4j.specs.IConstr;
import org.sat4j.specs.IProblem;
import org.sat4j.specs.ISolver;
import org.sat4j.specs.TimeoutException;
import org.sat4j.tools.ModelIterator;


#line 153 "p4parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    START_PROGRAM = 258,
    START_EXPRESSION_LIST = 259,
    START_KV_LIST = 260,
    START_INTEGER_LIST = 261,
    START_INTEGER_OR_STRING_LITERAL_LIST = 262,
    START_STRING_LITERAL_LIST = 263,
    START_EXPRESSION = 264,
    START_INTEGER = 265,
    START_INTEGER_OR_STRING_LITERAL = 266,
    START_STRING_LITERAL = 267,
    START_EXPRESSION_PAIR = 268,
    START_INTEGER_PAIR = 269,
    START_STRING_LITERAL_PAIR = 270,
    START_EXPRESSION_TRIPLE = 271,
    START_INTEGER_TRIPLE = 272,
    START_STRING_LITERAL_TRIPLE = 273,
    START_P4RT_TRANSLATION_ANNOTATION = 274,
    END = 275,
    END_ANNOTATION = 276,
    UNEXPECTED_TOKEN = 277,
    END_PRAGMA = 278,
    HASH = 279,
    DHASH = 280,
    LE = 281,
    GE = 282,
    SHL = 283,
    AND = 284,
    OR = 285,
    NE = 286,
    EQ = 287,
    PLUS = 288,
    MINUS = 289,
    PLUS_SAT = 290,
    MINUS_SAT = 291,
    MUL = 292,
    DIV = 293,
    MOD = 294,
    BIT_OR = 295,
    BIT_AND = 296,
    BIT_XOR = 297,
    COMPLEMENT = 298,
    L_BRACKET = 299,
    R_BRACKET = 300,
    L_BRACE = 301,
    R_BRACE = 302,
    L_ANGLE = 303,
    L_ANGLE_ARGS = 304,
    R_ANGLE = 305,
    R_ANGLE_SHIFT = 306,
    L_PAREN = 307,
    R_PAREN = 308,
    NOT = 309,
    COLON = 310,
    COMMA = 311,
    QUESTION = 312,
    DOT = 313,
    ASSIGN = 314,
    SEMICOLON = 315,
    AT = 316,
    PP = 317,
    DONTCARE = 318,
    MASK = 319,
    RANGE = 320,
    TRUE = 321,
    FALSE = 322,
    THIS = 323,
    ABSTRACT = 324,
    ACTION = 325,
    ACTIONS = 326,
    APPLY = 327,
    BOOL = 328,
    BIT = 329,
    CONST = 330,
    CONTROL = 331,
    DEFAULT = 332,
    ELSE = 333,
    ENTRIES = 334,
    ENUM = 335,
    ERROR = 336,
    EXIT = 337,
    EXTERN = 338,
    HEADER = 339,
    HEADER_UNION = 340,
    IF = 341,
    IN = 342,
    INOUT = 343,
    INT = 344,
    KEY = 345,
    SELECT = 346,
    MATCH_KIND = 347,
    TYPE = 348,
    OUT = 349,
    PACKAGE = 350,
    PARSER = 351,
    PRAGMA = 352,
    RETURN = 353,
    STATE = 354,
    STRING = 355,
    STRUCT = 356,
    SWITCH = 357,
    TABLE = 358,
    TRANSITION = 359,
    TUPLE = 360,
    TYPEDEF = 361,
    VARBIT = 362,
    VALUESET = 363,
    VOID = 364,
    IDENTIFIER = 365,
    TYPE_IDENTIFIER = 366,
    STRING_LITERAL = 367,
    INTEGER = 368,
    FLOATING_CONSTANT = 369,
    PPNUM = 370,
    PREFIX = 371,
    THEN = 372
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4036

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  152
/* YYNRULES -- Number of rules.  */
#define YYNRULES  488
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  893

#define YYUNDEFTOK  2
#define YYMAXUTOK   372


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   239,   239,   244,   248,   249,   250,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   267,   268,   269,
     270,   271,   272,   273,   277,   278,   282,   283,   284,   285,
     286,   290,   291,   295,   296,   300,   301,   305,   307,   309,
     311,   315,   320,   321,   323,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   372,
     373,   375,   376,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   418,   419,   423,   427,   428,   432,   433,   437,   438,
     442,   443,   444,   445,   449,   450,   449,   458,   460,   463,
     466,   472,   477,   478,   482,   483,   487,   488,   492,   498,
     499,   498,   505,   506,   510,   511,   512,   513,   518,   519,
     517,   527,   528,   532,   532,   538,   539,   543,   544,   545,
     546,   547,   548,   549,   553,   553,   558,   559,   563,   564,
     568,   573,   574,   578,   583,   584,   588,   590,   594,   595,
     600,   601,   602,   603,   607,   608,   609,   610,   611,   615,
     618,   621,   629,   636,   637,   635,   645,   646,   650,   651,
     652,   653,   654,   658,   665,   669,   664,   671,   672,   676,
     677,   682,   681,   687,   688,   689,   696,   697,   698,   699,
     700,   704,   705,   709,   710,   714,   718,   722,   723,   727,
     731,   732,   733,   734,   735,   736,   738,   740,   743,   745,
     747,   752,   753,   754,   759,   760,   764,   768,   775,   781,
     782,   784,   785,   789,   790,   791,   795,   796,   797,   803,
     804,   808,   809,   810,   811,   812,   816,   817,   818,   819,
     823,   823,   823,   832,   841,   841,   841,   849,   850,   854,
     859,   858,   864,   864,   872,   873,   877,   881,   886,   892,
     893,   897,   901,   905,   909,   919,   921,   926,   928,   933,
     937,   941,   942,   946,   948,   954,   958,   959,   960,   961,
     962,   963,   964,   965,   969,   969,   974,   975,   979,   983,
     984,   988,   989,   993,   994,   998,   999,  1000,  1001,  1007,
    1013,  1014,  1018,  1020,  1022,  1024,  1029,  1030,  1034,  1039,
    1040,  1045,  1049,  1051,  1056,  1061,  1062,  1068,  1077,  1081,
    1088,  1093,  1094,  1098,  1104,  1108,  1109,  1113,  1114,  1118,
    1119,  1120,  1124,  1125,  1126,  1130,  1131,  1135,  1135,  1139,
    1140,  1141,  1142,  1146,  1147,  1150,  1151,  1152,  1153,  1154,
    1155,  1156,  1157,  1158,  1159,  1160,  1161,  1162,  1163,  1164,
    1165,  1166,  1168,  1170,  1171,  1172,  1173,  1174,  1175,  1176,
    1177,  1178,  1179,  1181,  1182,  1183,  1185,  1187,  1188,  1189,
    1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,  1200,  1202,
    1204,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,  1217,
    1218,  1219,  1220,  1221,  1222,  1223,  1225,  1227,  1228,  1229,
    1230,  1231,  1232,  1233,  1234,  1235,  1236,  1238,  1239,  1240,
    1242,  1243,  1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,
    1252,  1253,  1257,  1259,  1261,  1285,  1285,  1286,  1286
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "START_PROGRAM", "START_EXPRESSION_LIST",
  "START_KV_LIST", "START_INTEGER_LIST",
  "START_INTEGER_OR_STRING_LITERAL_LIST", "START_STRING_LITERAL_LIST",
  "START_EXPRESSION", "START_INTEGER", "START_INTEGER_OR_STRING_LITERAL",
  "START_STRING_LITERAL", "START_EXPRESSION_PAIR", "START_INTEGER_PAIR",
  "START_STRING_LITERAL_PAIR", "START_EXPRESSION_TRIPLE",
  "START_INTEGER_TRIPLE", "START_STRING_LITERAL_TRIPLE",
  "START_P4RT_TRANSLATION_ANNOTATION", "END", "END_ANNOTATION",
  "UNEXPECTED_TOKEN", "END_PRAGMA", "HASH", "DHASH", "LE", "GE", "SHL",
  "AND", "OR", "NE", "EQ", "PLUS", "MINUS", "PLUS_SAT", "MINUS_SAT", "MUL",
  "DIV", "MOD", "BIT_OR", "BIT_AND", "BIT_XOR", "COMPLEMENT", "L_BRACKET",
  "R_BRACKET", "L_BRACE", "R_BRACE", "L_ANGLE", "L_ANGLE_ARGS", "R_ANGLE",
  "R_ANGLE_SHIFT", "L_PAREN", "R_PAREN", "NOT", "COLON", "COMMA",
  "QUESTION", "DOT", "ASSIGN", "SEMICOLON", "AT", "PP", "DONTCARE", "MASK",
  "RANGE", "TRUE", "FALSE", "THIS", "ABSTRACT", "ACTION", "ACTIONS",
  "APPLY", "BOOL", "BIT", "CONST", "CONTROL", "DEFAULT", "ELSE", "ENTRIES",
  "ENUM", "ERROR", "EXIT", "EXTERN", "HEADER", "HEADER_UNION", "IF", "IN",
  "INOUT", "INT", "KEY", "SELECT", "MATCH_KIND", "TYPE", "OUT", "PACKAGE",
  "PARSER", "PRAGMA", "RETURN", "STATE", "STRING", "STRUCT", "SWITCH",
  "TABLE", "TRANSITION", "TUPLE", "TYPEDEF", "VARBIT", "VALUESET", "VOID",
  "IDENTIFIER", "TYPE_IDENTIFIER", "STRING_LITERAL", "INTEGER",
  "FLOATING_CONSTANT", "PPNUM", "PREFIX", "THEN", "$accept", "start",
  "program", "input", "declaration", "nonTypeName", "name",
  "nonTableKwName", "optCONST", "optAnnotations", "annotations",
  "annotation", "annotationBody", "annotationToken", "kvList", "kvPair",
  "parameterList", "nonEmptyParameterList", "parameter", "direction",
  "packageTypeDeclaration", "$@1", "$@2", "instantiation",
  "objInitializer", "objDeclarations", "objDeclaration",
  "optConstructorParameters", "dotPrefix", "parserDeclaration", "$@3",
  "$@4", "parserLocalElements", "parserLocalElement",
  "parserTypeDeclaration", "$@5", "$@6", "parserStates", "parserState",
  "$@7", "parserStatements", "parserStatement", "parserBlockStatement",
  "$@8", "transitionStatement", "stateExpression", "selectExpression",
  "selectCaseList", "selectCase", "keysetExpression",
  "tupleKeysetExpression", "simpleExpressionList",
  "reducedSimpleKeysetExpression", "simpleKeysetExpression",
  "valueSetDeclaration", "controlDeclaration", "controlTypeDeclaration",
  "$@9", "$@10", "controlLocalDeclarations", "controlLocalDeclaration",
  "controlBody", "externDeclaration", "$@11", "$@12", "methodPrototypes",
  "functionPrototype", "$@13", "methodPrototype", "typeRef", "namedType",
  "prefixedType", "typeName", "tupleType", "headerStackType",
  "specializedType", "baseType", "typeOrVoid", "optTypeParameters",
  "typeParameters", "typeParameterList", "typeArg", "typeArgumentList",
  "realTypeArg", "realTypeArgumentList", "typeDeclaration",
  "derivedTypeDeclaration", "headerTypeDeclaration", "$@14", "$@15",
  "structTypeDeclaration", "headerUnionDeclaration", "$@16", "$@17",
  "structFieldList", "structField", "enumDeclaration", "$@18", "$@19",
  "specifiedIdentifierList", "specifiedIdentifier", "errorDeclaration",
  "matchKindDeclaration", "identifierList", "typedefDeclaration",
  "assignmentOrMethodCallStatement", "methodCallStatements",
  "emptyStatement", "exitStatement", "returnStatement",
  "conditionalStatement", "directApplication", "statement",
  "blockStatement", "$@20", "statOrDeclList", "switchStatement",
  "switchCases", "switchCase", "switchLabel", "statementOrDeclaration",
  "tableDeclaration", "tablePropertyList", "tableProperty",
  "keyElementList", "keyElement", "actionList", "action", "actionRef",
  "entry", "entriesList", "actionDeclaration", "variableDeclaration",
  "constantDeclaration", "optInitializer", "initializer",
  "functionDeclaration", "argumentList", "nonEmptyArgList", "argument",
  "expressionList", "prefixedNonTypeName", "dot_name", "$@21", "lvalue",
  "lvalueExpression", "expression", "invokingExpression",
  "nonBraceExpression", "invokingNonBraceExpression", "l_angle", "r_angle", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372
};
# endif

#define YYPACT_NINF (-768)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-243)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -768,    31,  -768,   915,  -768,  -768,  -768,   480,  -768,     7,
      -8,     7,    35,   480,  -768,     7,     7,  -768,  -768,  -768,
    -768,   852,  2613,  -768,   -24,  -768,     9,  -768,    87,  -768,
     100,  -768,    11,    73,  -768,   286,  -768,  -768,    60,  -768,
     480,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   106,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,   150,  -768,  -768,   -30,   480,   -27,   480,  -768,
    2426,   -25,   480,   347,   480,  2556,  2469,   480,   480,  2613,
     480,   480,   480,  2613,  -768,  -768,    80,  -768,  -768,    56,
    -768,  -768,  -768,    91,   122,    11,  -768,  2043,  2239,  2426,
    2239,     7,  -768,  2288,  -768,  2239,   170,  -768,     4,  2239,
     170,   103,  1676,  -768,  -768,  -768,  -768,  -768,   229,  2239,
     170,   120,   480,  -768,   118,  -768,   480,   162,   110,   127,
     155,  -768,  -768,  -768,    95,   480,   480,  -768,  -768,     7,
     480,   480,  2043,   131,   183,   200,  -768,   221,  -768,  -768,
    2239,  2239,  2239,  2288,  1308,  2239,  -768,  -768,  -768,  -768,
     212,  -768,  -768,   215,   222,   798,   264,   235,  -768,   265,
     261,  -768,  3704,  -768,  -768,  2890,   229,  2927,  -768,  -768,
     480,   266,    -6,  -768,    66,  3704,  1768,  2964,  -768,  -768,
    -768,  -768,   480,  3001,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  2426,  -768,  3038,  -768,    56,
     277,     7,   293,  -768,     7,  -768,  -768,     7,     7,  -768,
    -768,     7,     7,   296,  -768,  -768,   300,  -768,  -768,  -768,
     347,  -768,    11,  -768,  2596,  -768,   202,   202,   202,   137,
     167,   212,   303,   252,   190,  3075,   202,   480,  2239,  -768,
    2043,  -768,  -768,   480,  2043,  2239,  2239,  2239,  2239,  2239,
    2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,
    2239,  2239,  2239,  2239,   317,  2043,  2239,  2239,  -768,  1019,
    -768,  -768,  -768,   321,  -768,   304,  2239,  -768,   480,  -768,
    2239,  -768,   170,  -768,   170,  1860,  -768,   170,   316,  2239,
    -768,   480,   329,  -768,  -768,  -768,  -768,  -768,  -768,   480,
     480,  -768,  2613,    11,   -23,  2613,  -768,  -768,    72,  -768,
    -768,  -768,  -768,  1212,  -768,  -768,  2239,  -768,  -768,  3704,
     323,   480,   246,  -768,  3912,  3912,  1301,  3848,  3815,  3881,
    3881,   294,   294,   294,   294,   202,   202,   202,   999,  3974,
    3943,  2779,  3912,  2239,   324,  3112,   294,  -768,  -768,  -768,
    -768,   307,  3912,    56,   480,  -768,  3704,  -768,  3704,  -768,
    -768,  -768,  -768,    11,   318,  3704,   332,   184,   480,   335,
     343,   344,   340,   341,   -15,   248,   336,    46,  -768,  -768,
     -13,  -768,  -768,  -768,  -768,   352,  -768,   480,   176,   350,
    -768,  -768,  -768,   334,   354,  2092,   358,  -768,    -9,  -768,
     798,   224,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   440,   202,  -768,  -768,
     366,  -768,  -768,  2239,  1301,  -768,  2239,  2426,   362,   363,
    -768,  -768,  -768,    56,  -768,   356,   205,  -768,  -768,  -768,
    -768,    56,    56,  -768,   347,  -768,   366,  -768,  2239,   480,
       7,   325,   370,  -768,  -768,   377,   350,  2239,   365,  -768,
    2239,  -768,  3149,  2239,  -768,   355,  2239,  2043,  2239,  -768,
    -768,  2426,  -768,   369,  3186,  3778,  -768,  2043,  -768,   373,
    2239,  -768,   480,    -3,    15,    17,   379,   380,   480,   375,
    3704,  -768,   347,  -768,    77,   378,  -768,  -768,  3223,  -768,
    3260,   388,  2816,   389,  3297,   229,  1433,  -768,  -768,   392,
    -768,  -768,  -768,  -768,   240,  -768,  -768,  -768,  -768,  -768,
     381,  -768,   402,   170,   170,   170,   390,   394,   382,    52,
    -768,  -768,  2523,   409,  2043,  -768,  2239,   399,  -768,   408,
    -768,  2613,  -768,  -768,  -768,  -768,   688,   410,   401,  -768,
    -768,   417,   420,   423,   421,   430,  -768,   178,  -768,  -768,
     419,   400,  -768,   426,  3334,  -768,  2043,   422,    56,  -768,
    2335,  2239,  2239,  2239,  -768,  -768,  -768,   431,  -768,  -768,
    -768,  -768,   434,  2523,  2141,   425,  -768,   428,  -768,   442,
     566,    81,  2613,  -768,  -768,   449,   480,  -768,  -768,  -768,
    -768,  -768,  -768,  3371,  3408,  3445,    44,  2190,   451,  2239,
    -768,  2239,  2239,  2239,  -768,  1308,  2239,  -768,  -768,  -768,
    -768,   444,  -768,  -768,  -768,   798,   448,   235,  -768,   452,
    3741,  -768,  -768,   446,   455,   457,   463,  -768,  -768,  -768,
     480,  -768,   480,   480,   480,  -768,   415,  -768,  -768,  -768,
    3482,  1941,   464,   202,   202,   202,   450,  3519,   202,   480,
    -768,  2043,  -768,   -20,  2239,  2239,  2239,  2239,  2239,  2239,
    2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,  2239,
    2239,  2239,  2239,   461,  2043,  2239,  2239,  -768,  1019,  -768,
    -768,  2239,  -768,  -768,   467,   468,   469,   308,   470,   465,
     480,  1156,  -768,  -768,   481,  -768,  -768,  -768,  1389,  2739,
    -768,  2239,  -768,  -768,   482,  -768,  3912,  3912,  1301,  3848,
    3815,  3881,  3881,   294,   294,   294,   294,   202,   202,   202,
     999,  3974,  3943,  2853,  3912,  2239,   484,  3556,   294,   307,
    3912,   185,  2383,  -768,  -768,  -768,  -768,  2043,    11,   485,
     486,   490,   489,  2699,   415,  -768,  -768,  2239,  2239,   202,
    -768,  -768,  2239,  1301,  -768,  2239,   495,   502,  -768,   500,
     496,  -768,  1992,  2239,  2239,    11,  3704,  3704,  3593,  3778,
    2043,  -768,  -768,  -768,   209,  -768,  3630,  3667,   504,  -768,
     509,  1574,  -768,  1992,  -768,  -768,  -768,  -768,   511,  -768,
     480,   508,  -768
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   158,     6,     0,   250,   252,
     251,   254,     0,     0,   253,     0,     0,   262,   263,   243,
       5,     0,    34,    35,     0,    13,     0,    10,   156,    12,
     156,     8,    33,   261,   245,   237,   240,   239,   238,   236,
       0,    11,   281,   286,   288,   287,   289,    14,    15,     0,
       9,     7,    16,    20,    18,    22,    19,    23,    21,    17,
      25,    24,    37,   485,   486,     0,     0,     0,     0,    42,
     273,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    33,   251,    36,     0,   285,   244,    33,
     283,   159,   284,     0,     0,    34,   374,   375,     0,   273,
       0,   264,   282,   382,    42,     0,     0,   309,     0,     0,
       0,     0,     0,   272,   271,   270,   269,   274,     0,     0,
       0,     0,     0,   213,   243,   300,     0,   263,   224,     0,
       0,   261,   290,   294,     0,     0,     0,   144,   168,   264,
       0,     0,   375,   143,     0,   135,   136,     0,   216,   334,
       0,     0,     0,   382,     0,     0,   381,   397,   398,   399,
       0,   396,   395,   400,     0,     0,     0,   241,   242,     0,
     376,   377,   379,   437,   400,     0,     0,     0,   231,   265,
       0,     0,     0,   131,     0,   383,     0,     0,   487,   488,
     255,   307,     0,     0,   256,   308,    45,    41,   104,   103,
      99,   100,   102,   101,   106,   108,   107,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
      95,   122,    96,    42,   123,   124,   130,   125,   126,   127,
     128,   129,   105,    90,    98,    97,    84,    61,    82,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    62,    63,    64,    65,    66,    67,
      68,    76,    69,    70,    71,    73,    72,    74,    75,    77,
      78,    79,    80,    81,    83,    85,    86,    87,    88,    89,
      91,    92,    93,    94,    44,     0,   246,     0,   257,    33,
       0,   264,     0,   302,   264,   228,   227,   264,   264,   313,
     314,   264,   264,     0,   311,   312,     0,   140,   142,   141,
       0,   157,    33,   162,    33,   336,   410,   409,   408,     0,
       0,   251,     0,   237,   238,     0,   407,     0,     0,   401,
     375,   387,   411,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   375,     0,     0,   413,     0,
     247,   249,   248,     0,   267,     0,     0,    40,     0,    39,
       0,    38,     0,   310,     0,     0,   275,     0,     0,     0,
     214,     0,     0,   225,   291,   295,   145,   169,   297,     0,
       0,   137,    33,    33,     0,    34,   221,   217,     0,   220,
     219,   222,   218,    33,   405,   404,     0,   406,   412,   380,
       0,     0,     0,   378,   423,   424,   421,   433,   434,   427,
     428,   417,   418,   419,   420,   414,   415,   416,   431,   429,
     430,     0,   426,     0,     0,     0,   432,   278,   277,   276,
     279,     0,   425,    33,     0,   266,   133,   132,   384,   258,
     259,    43,   260,    33,     0,   373,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,   138,     0,   165,   163,
      33,   171,   167,   166,   164,     0,   223,     0,     0,   371,
     335,   319,   390,     0,     0,     0,     0,   385,     0,   348,
       0,   237,   326,   315,   329,   332,   331,   328,   327,   347,
     330,   333,   337,   345,   346,   389,     0,   436,   440,   388,
       0,   148,   402,     0,   422,   439,     0,     0,     0,     0,
     268,   367,   370,    33,   301,     0,     0,   304,   229,   297,
     297,    33,    33,   293,     0,   298,     0,   147,     0,     0,
       0,     0,     0,   172,   212,     0,   371,     0,     0,   320,
       0,   321,     0,     0,   386,     0,     0,   375,     0,   391,
     392,   273,   152,     0,     0,   435,   280,   375,   232,     0,
       0,   303,     0,    33,    33,    33,     0,     0,     0,     0,
     139,   173,     0,   161,    33,     0,   372,   369,     0,   322,
       0,     0,     0,     0,     0,     0,     0,   150,   403,     0,
     215,   306,   305,   226,     0,   230,   292,   296,   146,   170,
       0,   149,     0,     0,     0,     0,     0,     0,    31,    33,
     350,   368,    33,     0,   375,   393,     0,     0,   316,     0,
     151,     0,   155,   153,   154,   438,     0,   243,     0,   299,
     175,     0,     0,     0,     0,     0,    32,     0,   349,   351,
       0,   323,   339,     0,     0,   317,   375,     0,    33,   233,
      33,     0,     0,     0,   359,   356,    28,     0,    30,    29,
      26,    27,     0,    33,     0,     0,   394,     0,   234,     0,
       0,     0,    34,   176,   182,     0,     0,   177,   179,   183,
     178,   180,   181,     0,     0,     0,    33,     0,     0,     0,
     324,     0,     0,     0,   338,     0,     0,   443,   444,   445,
     343,     0,   442,   441,   446,     0,     0,   241,   340,     0,
     344,   481,   325,     0,     0,     0,     0,   187,   189,   184,
       0,   174,     0,     0,     0,   353,     0,   360,   352,   357,
       0,     0,     0,   454,   453,   452,     0,     0,   451,     0,
     447,   375,   455,   342,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   375,     0,     0,   457,     0,   318,
     235,   382,   188,   175,     0,     0,     0,     0,     0,   362,
       0,     0,   208,   207,     0,   194,   195,   365,     0,   204,
     355,     0,   450,   456,     0,   341,   467,   468,   465,   477,
     478,   471,   472,   461,   462,   463,   464,   458,   459,   460,
     475,   473,   474,     0,   470,     0,     0,     0,   476,     0,
     469,     0,    33,   211,   210,   209,   361,   375,    33,   203,
     202,     0,     0,   204,     0,   354,   366,     0,     0,   480,
     484,   448,     0,   466,   483,     0,     0,     0,   185,     0,
       0,   197,     0,     0,     0,    33,   205,   206,     0,   479,
     375,   191,   363,   358,     0,   198,   200,   201,     0,   449,
       0,     0,   196,     0,   364,   482,   190,   192,     0,   199,
       0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -768,  -768,  -768,  -768,  -768,    -7,   123,  -768,  -768,    10,
       8,   -10,   -83,  -768,   416,   204,  -288,  -768,   263,  -768,
    -768,  -768,  -768,  -305,    40,  -768,  -768,   547,   154,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,   108,  -768,
    -203,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -768,  -299,
    -768,  -768,  -768,  -767,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -768,  -768,   -73,  -768,  -768,   443,
     -88,  -768,   289,    13,  -768,    27,    14,  -768,   -85,  -768,
    -768,  -278,   -95,  -768,  -191,  -768,   -26,  -768,  -768,  -768,
    -768,  -768,  -768,  -768,  -235,  -768,  -768,  -768,  -768,  -768,
      20,  -768,  -768,   -53,  -768,  -646,  -768,  -644,  -768,  -768,
    -642,  -640,  -594,   -22,  -768,  -768,  -768,  -768,  -768,  -768,
    -768,  -768,  -768,   -21,  -768,  -768,  -768,  -768,  -255,  -205,
    -768,   288,  -285,     5,    59,  -530,    12,  -123,  -768,   272,
    -151,  -713,  -162,  -768,  -768,  -768,   814,  -768,  -768,  -768,
     598,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    20,   174,   164,   672,   647,   143,
      95,    23,   112,   284,   182,   183,   144,   145,   146,   310,
      24,   301,   462,    25,   563,   596,   633,    91,   165,    27,
     147,   542,   392,   469,    28,   302,   463,   470,   471,   612,
     660,   683,   684,   783,   685,   727,   728,   881,   887,   794,
     795,   874,   841,   796,   472,    29,    30,   291,   456,   314,
     397,   475,    31,   294,   459,   573,    32,   363,   605,   116,
     166,    34,   167,    36,    37,   168,    39,    40,   178,   179,
     365,   117,   118,   440,   441,    41,    42,    43,   297,   460,
      44,    45,   298,   461,   464,   535,    46,   292,   382,   526,
     527,    47,    48,   108,    49,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   315,   403,   501,   674,   718,   719,
     502,   399,   619,   620,   697,   739,   696,   737,   788,   797,
     798,    50,   691,   692,   548,   454,    52,   169,   170,   171,
     184,   505,   358,   411,   506,   560,   172,   173,   720,   721,
     359,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   378,   320,   130,   176,   332,    61,   376,    51,   396,
      96,    22,    85,    21,   687,   111,   688,   586,   689,   306,
     690,   186,   105,   789,   842,   109,   -33,   119,   651,   401,
      38,     4,   533,    61,  -160,   194,    87,   149,    66,   367,
     601,     7,    94,   286,   603,   288,     7,    72,     7,    38,
     368,   191,    73,   136,   303,    63,    64,   141,     7,    61,
     192,    61,   606,   115,   607,    61,    73,    61,    61,   128,
      61,    61,     7,    61,    61,    61,     7,    13,     7,   700,
     477,    68,    13,   106,    13,    85,   110,   468,   120,   134,
     163,   735,   115,   134,    13,   875,   163,    38,   489,   648,
      38,   361,    38,    38,   100,     7,    38,   473,    13,  -134,
      38,   369,    13,     7,    13,    61,   889,     7,   503,    61,
      88,    73,   370,   616,    97,    97,    38,   729,    61,    61,
      62,   789,   142,    61,    61,   163,    69,   148,     7,    89,
     375,    13,   617,    53,    54,   539,   163,    90,   616,    13,
     195,    55,    89,    13,   540,   519,    73,    26,   329,   192,
      92,   332,    56,   101,   -25,    57,   102,   617,   149,   742,
     -24,    58,   289,    61,    13,    75,    26,   -25,   -25,    77,
      78,   324,    59,    60,   404,    61,   687,   295,   688,   107,
     689,   107,   690,   368,   103,   121,    82,   123,   125,   129,
     132,   133,   104,   137,   138,   139,   380,   410,   -17,   383,
     -17,   -17,   384,   385,   405,   296,   386,   387,   307,   308,
     188,   189,   -17,   370,    26,   309,   181,    26,   142,    26,
      26,   524,   434,    26,   100,   569,   311,    26,   857,   566,
     192,   370,  -242,   576,   577,   290,   352,    53,    54,   293,
     666,    64,   571,    26,   355,    55,   312,   667,   299,   300,
     331,   572,   882,   304,   305,   883,    56,   313,    98,    57,
     327,   668,    63,    64,   -24,    58,   181,   669,   115,   188,
     189,   328,   555,    63,    64,   285,    59,    60,   670,   671,
     445,   632,    35,   331,   574,   575,    98,   449,     5,   450,
      63,    64,   452,   364,  -241,   510,   511,   536,   537,   636,
     331,    35,    38,     8,     9,   373,   330,   334,   333,   402,
      61,    84,   395,   163,   394,   366,    61,   163,   457,    11,
      98,   346,   347,   348,    63,    64,   379,    38,   352,   381,
      14,    38,   388,    64,   559,    15,   355,    16,   163,    17,
      18,   637,   331,   389,   188,   189,   406,   188,   189,    35,
     444,    61,    35,   517,    35,    35,   518,   433,    35,   453,
     679,   476,    35,   443,    61,   458,   508,   515,   522,    53,
      54,   528,    61,    61,   523,    85,   324,    55,    35,   529,
     530,    61,   531,   532,   549,   538,   487,   474,    56,   544,
     395,    57,   467,    94,    61,     5,   550,    58,   504,   547,
     553,   395,   562,   488,   567,   570,   568,   583,    59,    38,
       8,     9,    38,   584,   539,   587,   600,   591,    84,   597,
      38,   521,   608,   609,   593,   611,    11,    61,   621,    26,
     624,   639,   627,   323,   599,   635,    33,    14,   640,   644,
     408,    61,    15,   645,    16,   652,   412,   646,    19,   655,
     656,   659,   658,    94,    26,    86,   595,   664,    26,   661,
      61,    61,   662,     5,   534,   663,   665,   555,   673,   675,
     541,   723,   678,   554,   556,   722,    53,    54,    63,    64,
     698,   181,   557,   699,    55,   724,   731,   741,   331,   558,
     751,   653,   749,   801,   107,    56,   779,   753,    57,   781,
     115,   825,   465,   466,    58,   780,   122,   837,   126,   131,
     629,   479,   135,   782,   800,    59,   140,   833,   834,   835,
     836,   638,    61,   677,   509,   850,   844,   854,   641,   642,
     643,  -208,  -207,   861,    38,   862,    26,   870,   871,    26,
     163,    53,    54,   872,   115,   752,   873,   490,   777,    55,
     163,    38,   885,   657,   884,    61,   890,   520,   892,   319,
      56,    61,   447,    57,    35,   391,   579,    93,   543,    58,
     832,   525,   888,   604,   534,   534,   716,   829,    38,   865,
      59,    60,   602,   846,   618,   614,   615,   322,   649,    35,
     545,   546,   400,    35,   631,   585,   413,    65,   634,    67,
       0,     0,     0,    70,    71,   487,     0,   163,     0,     0,
       0,    85,     0,    38,     0,     0,     0,     0,   804,   618,
     831,    38,    94,    99,     0,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,     0,   323,   163,
       0,   826,     0,   487,     0,     0,    56,   725,    38,    57,
       0,     0,   581,    38,     0,    58,   487,   714,   682,     0,
     681,    26,    85,    61,     0,     0,    59,    60,     0,    61,
       0,    35,     0,    94,    35,     0,     0,    38,    26,     0,
       0,     0,   491,     0,     0,   525,     0,     0,     0,   180,
       0,   610,     0,     0,     0,     0,   736,     0,   750,    38,
       0,     0,     0,     0,   859,    26,     0,     0,     0,     0,
       0,     0,     0,    61,     0,    61,    61,    61,     0,   487,
       0,   805,   324,     0,     0,     0,    26,   180,     0,     0,
       0,     0,    61,     0,   163,     0,     5,   880,     0,     0,
      26,     0,     0,   390,   856,     0,     0,   398,    26,     0,
       0,     8,     9,    94,     0,    99,     0,   163,     0,    84,
       0,     0,     0,     0,     0,     0,   490,    11,     0,     0,
     554,     0,     0,    61,     0,    26,     0,     0,    14,     0,
      26,     0,     0,    15,     0,    16,     0,    17,    18,    19,
       0,     0,   439,   726,     0,   324,    35,     0,     0,   479,
       0,     0,     0,     0,   490,     0,     0,     0,   324,     0,
       0,     0,     0,    35,     0,   487,     0,   490,   715,     0,
     163,     0,     0,     0,     0,   398,    26,   487,   478,     0,
     682,     0,   681,     0,     0,     0,   398,     0,   860,     0,
      35,     0,     0,   546,     0,   784,   785,   786,     0,    38,
       0,     0,     0,   163,     0,     0,     0,     0,     0,    53,
      54,   613,   803,     0,     0,   878,     0,    55,     0,     0,
       0,     0,     0,    61,     0,    35,     0,     0,    56,   180,
     787,    57,   180,    35,     0,   180,   180,    58,     0,   180,
     180,     0,     0,     0,     0,     0,     0,     0,    59,    88,
       0,   650,   175,   838,   177,    -3,     0,   185,     0,   187,
      35,    99,    72,   193,     0,    35,     0,    73,    74,     0,
       0,     0,    75,   287,     0,    76,    77,    78,     0,     0,
       0,     0,     0,     0,     0,    79,     0,    80,    81,   491,
       0,     0,     0,    82,     0,     0,     0,     0,    83,     0,
       0,     0,   650,   717,   316,   317,   318,   185,   325,   326,
       0,    35,     0,     5,     0,     6,     7,   578,     0,     0,
       0,     0,     0,     0,     0,     0,   490,     0,     8,     9,
       0,     0,     0,     0,   323,     0,    10,     0,   787,     0,
       0,     0,     0,     0,    11,     0,     0,    12,     0,     0,
       0,     0,    13,   891,     0,    14,     0,     0,     0,     0,
      15,     0,    16,     0,    17,    18,    19,   337,     0,     0,
       0,     0,   342,   343,   344,   345,   346,   347,   348,    33,
     350,   351,     0,   352,     0,     0,     0,   131,    64,     0,
     354,   355,   150,   151,     0,     0,     0,   331,     0,     0,
       0,   357,   152,     0,     0,   153,     0,   323,     0,     0,
       0,   154,     0,   155,    86,     0,     0,     5,     0,   131,
     323,     0,   437,     0,     0,   157,   158,   159,     0,    99,
      53,    54,     8,     9,     0,     0,     0,     0,    55,     0,
     321,     0,     0,   686,   561,     0,     0,     0,    11,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,    14,
       0,   491,     0,     0,    15,   730,    16,     0,   438,    59,
      19,   161,   162,     0,     0,     0,     0,     0,   582,     0,
       0,     0,   409,     0,     0,     0,     0,     0,   746,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,     0,     0,
     435,   436,     0,   442,     0,     0,     0,     0,     0,     0,
     446,     0,     0,     0,   448,     0,     0,     0,     0,   150,
     151,     0,     0,   455,     0,     0,     0,     0,     0,   152,
       0,     0,   153,     0,     0,     0,     0,     0,   154,     0,
     155,     0,     0,     0,     5,     0,     0,     0,     0,   839,
     507,   439,   157,   158,   159,     0,     0,    53,    54,     8,
       9,     0,     0,   840,   322,    55,     0,   321,     0,     0,
       0,     0,     0,     0,     0,    11,    56,   514,     0,    57,
       0,     0,     0,     0,     0,    58,    14,     0,     0,   480,
       0,    15,     0,    16,     0,     0,    59,    19,   161,   162,
       5,     0,   481,     7,     0,   686,     0,     0,     0,     0,
     482,     0,     0,    53,    54,     8,     9,     0,     0,     0,
       0,    55,     0,    84,   483,     0,     0,     0,   484,   552,
       0,    11,    56,     0,     0,    57,     0,     0,     0,    13,
     485,    58,    14,     0,   486,    99,     0,    15,   778,    16,
       0,     0,    59,    19,     0,     0,     0,   564,     0,     0,
     565,     0,     0,     0,   342,   343,   344,   345,   346,   347,
     348,   150,   151,     0,     0,   352,     0,     0,     0,     0,
      64,   152,   580,   355,   153,     0,     0,     0,     0,   331,
     154,   455,   155,   357,   588,     0,     5,   590,     0,     0,
     592,     0,   594,     0,   157,   158,   159,     0,     0,    53,
      54,     8,     9,     0,   455,     0,     0,    55,     0,   321,
       0,     0,     0,     0,     0,     0,     0,    11,    56,     0,
       0,    57,     0,     0,     0,     0,     0,    58,    14,     0,
       0,     0,     0,    15,     0,    16,     0,     0,    59,    19,
     161,   162,   150,   151,     0,     0,     0,     0,     0,     0,
       0,     0,   152,     0,     0,   153,   845,     0,     0,     0,
     654,   791,     0,   155,     0,     0,     0,     5,     0,     0,
       0,     0,   792,     0,     0,   157,   158,   159,     0,     0,
      53,    54,     0,     0,     0,     0,   793,     0,    55,     0,
     160,     0,     0,     0,     0,   693,   694,   695,     0,    56,
     630,     0,    57,     0,     0,     0,     0,     0,    58,     0,
       0,     5,     0,     0,     7,     0,     0,     0,     0,    59,
      19,   161,   162,     0,     0,     0,     8,     9,     0,     0,
       0,   740,     0,   455,    84,   743,   744,   745,     0,   747,
     748,     0,    11,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,    14,     0,     0,     0,     0,    15,     0,
      16,     0,    17,    18,    19,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   799,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   823,   824,     0,     0,   827,
     828,     0,   830,     0,     0,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   843,     0,   150,   151,     0,
       0,     0,   799,     0,     0,   849,     0,   152,     0,     0,
     153,   886,     0,     0,     0,     0,   791,     0,   155,     0,
       0,     0,     5,     0,     0,     0,     0,   792,     0,   853,
     157,   158,   159,     0,     0,    53,    54,     0,     0,     0,
       0,   793,     0,    55,     0,   160,     0,     0,     0,     0,
       0,   866,   867,     0,    56,     0,   868,    57,     0,   869,
       0,     0,     0,    58,     0,     0,   799,   876,   877,     0,
       0,     0,     0,     0,    59,    19,   161,   162,     0,     0,
       0,     0,     0,     0,     0,   799,     0,   799,   196,   197,
       0,     0,   198,   199,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,     0,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     196,     0,     0,     0,   198,   199,     0,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     223,   371,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   196,     0,     0,     0,   198,   199,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   451,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   150,   151,     0,     0,     0,     0,
       0,     0,     0,     0,   152,     0,     0,   153,     0,     0,
       0,     0,     0,   791,     0,   155,     0,     0,     0,     5,
       0,     0,     0,     0,   792,     0,     0,   157,   158,   159,
       0,     0,    53,    54,     0,     0,     0,     0,   793,     0,
      55,     0,   160,     0,     0,   150,   151,     0,     0,     0,
       0,    56,     0,     0,    57,   152,     0,     0,   153,     0,
      58,     0,     0,     0,   154,     0,   155,     0,     0,     0,
       5,    59,    19,   161,   162,   792,     0,     0,   157,   158,
     159,     0,     0,    53,    54,     0,     0,     0,     0,   793,
       0,    55,     0,   160,     0,     0,   150,   151,     0,     0,
       0,     0,    56,     0,     0,    57,   152,     0,     0,   153,
       0,    58,     0,     0,     0,   154,     0,   155,     0,     0,
       0,     5,    59,    19,   161,   162,   156,     0,     0,   157,
     158,   159,     0,     0,    53,    54,     0,     0,     0,     0,
       0,     0,    55,     0,   160,   150,   151,     0,     0,     0,
       0,     0,     0,    56,     0,   152,    57,     0,   153,     0,
       0,     0,    58,     0,   154,     0,   155,     0,     0,     0,
       5,     0,   551,    59,   124,   161,   162,     0,   157,   158,
     159,     0,     0,    53,    54,     0,     0,     0,     0,     0,
       0,    55,     0,   160,   701,   702,     0,     0,     0,     0,
       0,     0,    56,     0,   703,    57,     0,     0,   704,     0,
       0,    58,     0,   705,     0,   706,     0,     0,     0,     5,
       0,     0,    59,    19,   161,   162,     0,   707,   708,   709,
       0,     0,    53,    54,     0,     0,     0,     0,   710,     0,
      55,     0,   711,   150,   151,     0,     0,     0,     0,     0,
       0,    56,     0,   152,    57,     0,   153,   738,     0,     0,
      58,     0,   154,     0,   155,     0,     0,     0,     5,     0,
       0,    59,    19,   712,   713,     0,   157,   158,   159,     0,
       0,    53,    54,     0,     0,     0,     0,     0,     0,    55,
       0,   160,   150,   151,     0,     0,     0,     0,     0,     0,
      56,     0,   152,    57,     0,   153,     0,     0,     0,    58,
       0,   154,     0,   155,     0,     0,     0,     5,     0,     0,
      59,    19,   161,   162,     0,   157,   158,   159,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,    55,     0,
     160,   150,   151,     0,     0,     0,     0,     0,     0,    56,
       0,   152,    57,     0,   153,     0,     0,     0,    58,     0,
     154,     0,   155,     0,     0,     0,     5,     0,     0,    59,
      19,   161,   162,     0,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,     0,     0,    55,     0,   160,
       0,     0,     0,     0,     0,     0,     0,     0,    56,     0,
       0,    57,  -186,     0,     0,     0,     0,    58,     0,     0,
       0,     0,     0,     5,     0,   481,     7,     0,    59,   124,
     161,   162,     0,   482,     0,     0,    53,    54,     8,     9,
       0,     0,     0,     0,    55,     0,    84,     0,     0,     0,
       0,   484,     0,     0,    11,    56,     0,     0,    57,     0,
     858,     0,    13,     0,    58,    14,     0,     0,     0,   680,
      15,     5,    16,   481,     7,    59,    19,     0,     0,     0,
       0,   482,     0,     0,    53,    54,     8,     9,     0,     0,
       0,     0,    55,     0,    84,     0,     0,     0,     0,   484,
       0,     0,    11,    56,     0,     0,    57,     0,     0,     0,
      13,     0,    58,    14,     5,     0,     0,     0,    15,   113,
      16,     0,     0,    59,    19,     0,     0,    53,    54,     8,
       9,     0,     0,     0,     0,    55,     0,    84,     0,     0,
       0,     0,     0,     0,     0,    11,    56,     0,     0,    57,
       0,     0,     0,     0,     0,    58,    14,     5,     0,     0,
       0,    15,     0,    16,     0,   114,    59,    19,     0,     0,
      53,    54,     8,     9,     0,     0,     0,     0,    55,     0,
      84,     0,     0,     0,     0,     0,     0,     0,    11,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,    14,
       0,     0,     0,     0,    15,     0,    16,     0,    17,   127,
     124,     5,     0,   481,     7,     0,     0,     0,     0,     0,
       0,   482,     0,     0,    53,    54,     0,     0,     0,     0,
       0,     0,    55,     0,     0,   483,     0,     0,     0,   484,
       0,     0,     0,    56,     5,     0,    57,     0,     0,     0,
      13,   485,    58,     0,     0,   486,     0,    53,    54,     8,
       9,     0,     0,    59,    19,    55,     0,    84,     0,     0,
       0,     0,     0,     0,     0,    11,    56,     0,     0,    57,
       0,     0,     0,     0,     5,    58,    14,     7,     0,     0,
       0,    15,     0,    16,     0,     0,    59,   124,   393,     8,
       9,     5,     0,     0,     7,     0,     0,    84,     0,     0,
       0,     0,     0,     0,     0,    11,     8,     9,     0,     0,
       0,     0,     0,    13,    84,     0,    14,     0,     0,     0,
       0,    15,    11,    16,     0,     0,     0,    19,     0,     0,
      13,     0,     0,    14,     0,     0,     0,     0,    15,     0,
      16,     0,     0,     0,    19,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,   407,     0,     0,     0,   356,   331,     0,     0,
       0,   357,     0,   863,   864,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,     0,   356,   331,     0,     0,
       0,   357,     0,   847,   848,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,   512,     0,     0,    63,    64,   353,
     354,   355,     0,     0,   513,     0,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,   625,     0,     0,    63,    64,   353,   354,   355,     0,
       0,   626,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,   851,     0,
       0,    63,    64,   353,   354,   355,     0,     0,   852,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,   360,     0,     0,    63,    64,
     353,   354,   355,     0,     0,     0,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,   362,     0,     0,    63,    64,   353,   354,   355,
       0,     0,     0,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,   372,     0,     0,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,   374,     0,     0,     0,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,   377,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,   407,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,     0,     0,   516,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,     0,   356,   331,     0,   589,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,   598,     0,     0,    63,    64,   353,   354,   355,     0,
       0,     0,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,   622,     0,     0,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,   623,     0,     0,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
       0,     0,     0,     0,   356,   331,     0,   628,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,   676,
       0,     0,    63,    64,   353,   354,   355,     0,     0,     0,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,   732,     0,     0,     0,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,   733,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,   734,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,     0,     0,   790,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,   802,     0,     0,     0,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,    63,    64,   353,   354,   355,     0,
       0,   855,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,   879,     0,
       0,    63,    64,   353,   354,   355,     0,     0,     0,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,     0,     0,     0,  -205,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
       0,     0,     0,  -206,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,     0,     0,     0,
       0,   356,   331,     0,     0,     0,   357,   754,   755,   756,
     757,   758,   759,   760,   761,   762,   763,   764,   765,   766,
     767,   768,   769,   770,     0,   771,     0,     0,     0,    63,
      64,   772,   773,   774,     0,     0,     0,     0,   775,   331,
       0,     0,     0,   776,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,     0,     0,     0,     0,     0,   331,     0,     0,     0,
     357,   335,   336,   337,   338,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,     0,     0,
       0,     0,     0,   331,   335,   336,   337,   357,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,     0,     0,     0,     0,     0,   331,   335,   336,   337,
     357,     0,     0,     0,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,     0,     0,   331,
     337,     0,     0,   357,     0,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
       0,    64,     0,   354,   355,     0,     0,     0,     0,     0,
     331,   337,     0,     0,   357,     0,   342,   343,   344,   345,
     346,   347,   348,     0,   350,     0,     0,   352,     0,     0,
       0,     0,    64,     0,   354,   355,     0,     0,     0,     0,
       0,   331,   337,     0,     0,   357,     0,   342,   343,   344,
     345,   346,   347,   348,     0,     0,     0,     0,   352,     0,
       0,     0,     0,    64,     0,   354,   355,     0,     0,     0,
       0,     0,   331,     0,     0,     0,   357
};

static const yytype_int16 yycheck[] =
{
       7,   289,   153,    76,    99,   167,    13,   285,     3,   314,
      32,     3,    22,     3,   660,    68,   660,   547,   660,   142,
     660,   104,    52,   736,   791,    52,    46,    52,   622,   314,
       3,     0,    47,    40,    47,   110,    60,    46,    46,    45,
     570,    61,    32,   118,    47,   120,    61,    70,    61,    22,
      56,    47,    75,    79,   139,    48,    49,    83,    61,    66,
      56,    68,    47,    70,    47,    72,    75,    74,    75,    76,
      77,    78,    61,    80,    81,    82,    61,    97,    61,   673,
     103,    46,    97,   113,    97,    95,   113,   392,   113,    79,
      97,    47,    99,    83,    97,   862,   103,    70,   403,    47,
      73,   176,    75,    76,    44,    61,    79,   392,    97,    53,
      83,    45,    97,    61,    97,   122,   883,    61,   403,   126,
     111,    75,    56,    71,    52,    52,    99,    46,   135,   136,
       7,   844,    52,   140,   141,   142,    13,    46,    61,    52,
     223,    97,    90,    71,    72,    99,   153,    60,    71,    97,
      47,    79,    52,    97,   108,   443,    75,     3,   165,    56,
      60,   323,    90,    40,    46,    93,    60,    90,    46,   699,
      60,    99,    52,   180,    97,    80,    22,    59,    60,    84,
      85,   154,   110,   111,    47,   192,   832,    60,   832,    66,
     832,    68,   832,    56,    44,    72,   101,    74,    75,    76,
      77,    78,    52,    80,    81,    82,   291,   330,    46,   294,
      48,    49,   297,   298,    47,    60,   301,   302,    87,    88,
      50,    51,    60,    56,    70,    94,   103,    73,    52,    75,
      76,    47,   355,    79,    44,   523,    53,    83,    53,   517,
      56,    56,    52,   531,   532,   122,    44,    71,    72,   126,
      72,    49,    47,    99,    52,    79,    56,    79,   135,   136,
      58,    56,    53,   140,   141,    56,    90,    46,    44,    93,
      58,    93,    48,    49,    59,    99,   153,    99,   285,    50,
      51,    59,    58,    48,    49,    56,   110,   111,   110,   111,
     365,   596,     3,    58,   529,   530,    44,   372,    58,   374,
      48,    49,   377,   180,    52,    59,    60,    59,    60,    69,
      58,    22,   285,    73,    74,   192,    52,    56,    53,   314,
     327,    81,   314,   330,   314,    59,   333,   334,   381,    89,
      44,    37,    38,    39,    48,    49,    59,   310,    44,    46,
     100,   314,    46,    49,   506,   105,    52,   107,   355,   109,
     110,   111,    58,    53,    50,    51,    53,    50,    51,    70,
      56,   368,    73,    56,    75,    76,   441,    50,    79,    53,
     658,   393,    83,    52,   381,    46,    53,    53,    60,    71,
      72,    46,   389,   390,    52,   395,   359,    79,    99,    46,
      46,   398,    52,    52,    60,    59,   403,   392,    90,    47,
     392,    93,   392,   393,   411,    58,    52,    99,   403,    59,
      52,   403,    46,   403,    52,    59,    53,    47,   110,   392,
      73,    74,   395,    46,    99,    60,    53,    72,    81,    60,
     403,   453,    53,    53,   557,    60,    89,   444,    60,   285,
      52,    60,    53,   154,   567,    53,     3,   100,    46,    59,
     327,   458,   105,    59,   107,    46,   333,    75,   111,    60,
      52,    60,    52,   453,   310,    22,   561,    46,   314,    52,
     477,   478,    52,    58,   464,    52,    46,    58,    78,    53,
     470,    53,    60,   490,    44,    60,    71,    72,    48,    49,
      59,   368,    52,    59,    79,    53,    47,    46,    58,    59,
      52,   624,    58,    53,   381,    90,    60,    55,    93,    52,
     517,    50,   389,   390,    99,    60,    73,    52,    75,    76,
     595,   398,    79,    60,    60,   110,    83,    60,    60,    60,
      60,   604,   539,   656,   411,    53,    55,    53,   613,   614,
     615,    56,    56,    53,   517,    56,   392,    52,    46,   395,
     557,    71,    72,    53,   561,   717,    60,   403,   720,    79,
     567,   534,    53,   636,    60,   572,    55,   444,    60,   153,
      90,   578,   368,    93,   285,   312,   536,    30,   470,    99,
     783,   458,   881,   573,   574,   575,   674,   778,   561,   844,
     110,   111,   572,   798,   584,   582,   582,   154,   619,   310,
     477,   478,   314,   314,   596,   546,   334,     9,   596,    11,
      -1,    -1,    -1,    15,    16,   622,    -1,   624,    -1,    -1,
      -1,   631,    -1,   596,    -1,    -1,    -1,    -1,   751,   619,
     781,   604,   622,    35,    -1,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,   359,   656,
      -1,   774,    -1,   660,    -1,    -1,    90,    91,   631,    93,
      -1,    -1,   539,   636,    -1,    99,   673,   674,   660,    -1,
     660,   517,   682,   680,    -1,    -1,   110,   111,    -1,   686,
      -1,   392,    -1,   673,   395,    -1,    -1,   660,   534,    -1,
      -1,    -1,   403,    -1,    -1,   572,    -1,    -1,    -1,   101,
      -1,   578,    -1,    -1,    -1,    -1,   696,    -1,   715,   682,
      -1,    -1,    -1,    -1,   837,   561,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   730,    -1,   732,   733,   734,    -1,   736,
      -1,   753,   705,    -1,    -1,    -1,   582,   139,    -1,    -1,
      -1,    -1,   749,    -1,   751,    -1,    58,   870,    -1,    -1,
     596,    -1,    -1,   310,   829,    -1,    -1,   314,   604,    -1,
      -1,    73,    74,   753,    -1,   167,    -1,   774,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,   622,    89,    -1,    -1,
     787,    -1,    -1,   790,    -1,   631,    -1,    -1,   100,    -1,
     636,    -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,
      -1,    -1,   359,   680,    -1,   778,   517,    -1,    -1,   686,
      -1,    -1,    -1,    -1,   660,    -1,    -1,    -1,   791,    -1,
      -1,    -1,    -1,   534,    -1,   832,    -1,   673,   674,    -1,
     837,    -1,    -1,    -1,    -1,   392,   682,   844,   395,    -1,
     832,    -1,   832,    -1,    -1,    -1,   403,    -1,   838,    -1,
     561,    -1,    -1,   730,    -1,   732,   733,   734,    -1,   832,
      -1,    -1,    -1,   870,    -1,    -1,    -1,    -1,    -1,    71,
      72,   582,   749,    -1,    -1,   865,    -1,    79,    -1,    -1,
      -1,    -1,    -1,   890,    -1,   596,    -1,    -1,    90,   291,
     736,    93,   294,   604,    -1,   297,   298,    99,    -1,   301,
     302,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   110,   111,
      -1,   622,    98,   790,   100,     0,    -1,   103,    -1,   105,
     631,   323,    70,   109,    -1,   636,    -1,    75,    76,    -1,
      -1,    -1,    80,   119,    -1,    83,    84,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    -1,    95,    96,   660,
      -1,    -1,    -1,   101,    -1,    -1,    -1,    -1,   106,    -1,
      -1,    -1,   673,   674,   150,   151,   152,   153,   154,   155,
      -1,   682,    -1,    58,    -1,    60,    61,   534,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   832,    -1,    73,    74,
      -1,    -1,    -1,    -1,   705,    -1,    81,    -1,   844,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    -1,    -1,
      -1,    -1,    97,   890,    -1,   100,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,   109,   110,   111,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,   596,
      41,    42,    -1,    44,    -1,    -1,    -1,   604,    49,    -1,
      51,    52,    33,    34,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    62,    43,    -1,    -1,    46,    -1,   778,    -1,    -1,
      -1,    52,    -1,    54,   631,    -1,    -1,    58,    -1,   636,
     791,    -1,    63,    -1,    -1,    66,    67,    68,    -1,   491,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,   660,   506,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,   832,    -1,    -1,   105,   682,   107,    -1,   109,   110,
     111,   112,   113,    -1,    -1,    -1,    -1,    -1,   540,    -1,
      -1,    -1,   328,    -1,    -1,    -1,    -1,    -1,   705,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,    -1,    -1,
     356,   357,    -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,
     366,    -1,    -1,    -1,   370,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,   379,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,
     406,   778,    66,    67,    68,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    77,   791,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,   433,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    47,
      -1,   105,    -1,   107,    -1,    -1,   110,   111,   112,   113,
      58,    -1,    60,    61,    -1,   832,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    -1,    -1,    -1,    86,   485,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    97,
      98,    99,   100,    -1,   102,   717,    -1,   105,   720,   107,
      -1,    -1,   110,   111,    -1,    -1,    -1,   513,    -1,    -1,
     516,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    33,    34,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      49,    43,   538,    52,    46,    -1,    -1,    -1,    -1,    58,
      52,   547,    54,    62,   550,    -1,    58,   553,    -1,    -1,
     556,    -1,   558,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    73,    74,    -1,   570,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,
      -1,    -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,
     112,   113,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    -1,    -1,    -1,
     626,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,   661,   662,   663,    -1,    90,
      47,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,   110,
     111,   112,   113,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,   697,    -1,   699,    81,   701,   702,   703,    -1,   705,
     706,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,   109,   110,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   741,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   754,   755,
     756,   757,   758,   759,   760,   761,   762,   763,   764,   765,
     766,   767,   768,   769,   770,   771,   772,    -1,    -1,   775,
     776,    -1,   778,    -1,    -1,   781,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   791,    -1,    33,    34,    -1,
      -1,    -1,   798,    -1,    -1,   801,    -1,    43,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,   825,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    77,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,   847,   848,    -1,    90,    -1,   852,    93,    -1,   855,
      -1,    -1,    -1,    99,    -1,    -1,   862,   863,   864,    -1,
      -1,    -1,    -1,    -1,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   881,    -1,   883,    22,    23,
      -1,    -1,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
      22,    -1,    -1,    -1,    26,    27,    -1,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    22,    -1,    -1,    -1,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    -1,    81,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    90,    -1,    -1,    93,    43,    -1,    -1,    46,    -1,
      99,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,
      58,   110,   111,   112,   113,    63,    -1,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,
      -1,    79,    -1,    81,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    93,    43,    -1,    -1,    46,
      -1,    99,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,   110,   111,   112,   113,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    43,    93,    -1,    46,    -1,
      -1,    -1,    99,    -1,    52,    -1,    54,    -1,    -1,    -1,
      58,    -1,    60,   110,   111,   112,   113,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    43,    93,    -1,    -1,    47,    -1,
      -1,    99,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,   110,   111,   112,   113,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,
      79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    43,    93,    -1,    46,    47,    -1,    -1,
      99,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,   110,   111,   112,   113,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    43,    93,    -1,    46,    -1,    -1,    -1,    99,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
     110,   111,   112,   113,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    43,    93,    -1,    46,    -1,    -1,    -1,    99,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,
     111,   112,   113,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    93,    47,    -1,    -1,    -1,    -1,    99,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    60,    61,    -1,   110,   111,
     112,   113,    -1,    68,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      47,    -1,    97,    -1,    99,   100,    -1,    -1,    -1,   104,
     105,    58,   107,    60,    61,   110,   111,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      97,    -1,    99,   100,    58,    -1,    -1,    -1,   105,    63,
     107,    -1,    -1,   110,   111,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    58,    -1,    -1,
      -1,   105,    -1,   107,    -1,   109,   110,   111,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,
     111,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    -1,    90,    58,    -1,    93,    -1,    -1,    -1,
      97,    98,    99,    -1,    -1,   102,    -1,    71,    72,    73,
      74,    -1,    -1,   110,   111,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    58,    99,   100,    61,    -1,    -1,
      -1,   105,    -1,   107,    -1,    -1,   110,   111,    72,    73,
      74,    58,    -1,    -1,    61,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    73,    74,    -1,    -1,
      -1,    -1,    -1,    97,    81,    -1,   100,    -1,    -1,    -1,
      -1,   105,    89,   107,    -1,    -1,    -1,   111,    -1,    -1,
      97,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,    -1,    -1,   111,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    -1,    64,    65,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    -1,    64,    65,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    45,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    60,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    -1,    60,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    53,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    56,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    26,    27,    28,    62,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    26,    27,    28,
      62,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      28,    -1,    -1,    62,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    28,    -1,    -1,    62,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,    41,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    28,    -1,    -1,    62,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,    97,   100,   105,   107,   109,   110,   111,
     122,   127,   128,   129,   138,   141,   146,   147,   152,   173,
     174,   180,   184,   187,   189,   190,   191,   192,   193,   194,
     195,   203,   204,   205,   208,   209,   214,   219,   220,   222,
     249,   251,   254,    71,    72,    79,    90,    93,    99,   110,
     111,   123,   124,    48,    49,   268,    46,   268,    46,   124,
     268,   268,    70,    75,    76,    80,    83,    84,    85,    93,
      95,    96,   101,   106,    81,   129,   187,    60,   111,    52,
      60,   145,    60,   145,   127,   128,   231,    52,    44,   268,
      44,   124,    60,    44,    52,    52,   113,   124,   221,    52,
     113,   221,   130,    63,   109,   123,   187,   199,   200,    52,
     113,   124,   187,   124,   111,   124,   187,   110,   123,   124,
     184,   187,   124,   124,   127,   187,   204,   124,   124,   124,
     187,   204,    52,   127,   134,   135,   136,   148,    46,    46,
      33,    34,    43,    46,    52,    54,    63,    66,    67,    68,
      81,   112,   113,   123,   124,   146,   188,   190,   193,   255,
     256,   257,   264,   265,   123,   264,   200,   264,   196,   197,
     268,   124,   132,   133,   258,   264,   130,   264,    50,    51,
     269,    47,    56,   264,   269,    47,    22,    23,    26,    27,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   131,    56,   269,   264,   269,    52,
     124,   175,   215,   124,   181,    60,    60,   206,   210,   124,
     124,   139,   153,   196,   124,   124,   255,    87,    88,    94,
     137,    53,    56,    46,   177,   232,   264,   264,   264,   132,
     258,    81,   187,   190,   193,   264,   264,    58,    59,   123,
      52,    58,   260,    53,    56,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    50,    51,    52,    57,    62,   260,   268,
      45,   269,    45,   185,   124,   198,    59,    45,    56,    45,
      56,    53,    53,   124,    53,   130,   199,    53,   134,    59,
     196,    46,   216,   196,   196,   196,   196,   196,    46,    53,
     187,   136,   150,    72,   127,   128,   141,   178,   187,   239,
     249,   250,   251,   233,    47,    47,    53,    53,   124,   264,
     255,   261,   124,   257,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,    50,   255,   264,   264,    63,   109,   187,
     201,   202,   264,    52,    56,   269,   264,   133,   264,   269,
     269,    53,   269,    53,   253,   264,   176,   221,    46,   182,
     207,   211,   140,   154,   212,   124,   124,   127,   141,   151,
     155,   156,   172,   250,   251,   179,   231,   103,   187,   124,
      47,    60,    68,    82,    86,    98,   102,   123,   127,   141,
     146,   190,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   234,   238,   250,   251,   259,   262,   264,    53,   124,
      59,    60,    45,    55,   264,    53,    55,    56,   269,   134,
     124,   231,    60,    52,    47,   124,   217,   218,    46,    46,
      46,    52,    52,    47,   127,   213,    59,    60,    59,    99,
     108,   127,   149,   156,    47,   124,   124,    59,   252,    60,
      52,    60,   264,    52,   123,    58,    44,    52,    59,   260,
     263,   268,    46,   142,   264,   264,   199,    52,    53,   134,
      59,    47,    56,   183,   212,   212,   134,   134,   187,   142,
     264,   124,   268,    47,    46,   252,   253,    60,   264,    60,
     264,    72,   264,   255,   264,   200,   143,    60,    45,   255,
      53,   253,   218,    47,   127,   186,    47,    47,    53,    53,
     124,    60,   157,   190,   191,   194,    71,    90,   127,   240,
     241,    60,    53,    53,    52,    45,    55,    53,    60,   269,
      47,   128,   141,   144,   254,    53,    69,   111,   184,    60,
      46,   269,   269,   269,    59,    59,    75,   126,    47,   241,
     190,   230,    46,   255,   264,    60,    52,   184,    52,    60,
     158,    52,    52,    52,    46,    46,    72,    79,    93,    99,
     110,   111,   125,    78,   235,    53,    45,   255,    60,   134,
     104,   127,   128,   159,   160,   162,   187,   223,   225,   228,
     229,   250,   251,   264,   264,   264,   244,   242,    59,    59,
     230,    33,    34,    43,    47,    52,    54,    66,    67,    68,
      77,    81,   112,   113,   123,   146,   188,   190,   236,   237,
     266,   267,    60,    53,    53,    91,   124,   163,   164,    46,
     187,    47,    53,    53,    53,    47,   127,   245,    47,   243,
     264,    46,   253,   264,   264,   264,   187,   264,   264,    58,
     123,    52,   260,    55,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    44,    50,    51,    52,    57,    62,   260,   268,    60,
      60,    52,    60,   161,   124,   124,   124,   146,   246,   259,
      55,    52,    63,    77,   167,   168,   171,   247,   248,   264,
      60,    53,    53,   124,   255,   231,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,    50,   255,   264,   264,   202,
     264,   258,   158,    60,    60,    60,    60,    52,   124,    63,
      77,   170,   171,   264,    55,    47,   247,    64,    65,   264,
      53,    45,    55,   264,    53,    55,   269,    53,    47,   255,
     127,    53,    56,    64,    65,   246,   264,   264,   264,   264,
      52,    46,    53,    60,   169,   171,   264,   264,   127,    45,
     255,   165,    53,    56,    60,    53,    47,   166,   167,   171,
      55,   124,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   118,   119,   120,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   125,   125,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   129,
     129,   129,   130,   130,   130,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   132,   132,   133,   134,   134,   135,   135,   136,   136,
     137,   137,   137,   137,   139,   140,   138,   141,   141,   141,
     141,   142,   143,   143,   144,   144,   145,   145,   146,   148,
     149,   147,   150,   150,   151,   151,   151,   151,   153,   154,
     152,   155,   155,   157,   156,   158,   158,   159,   159,   159,
     159,   159,   159,   159,   161,   160,   162,   162,   163,   163,
     164,   165,   165,   166,   167,   167,   168,   168,   169,   169,
     170,   170,   170,   170,   171,   171,   171,   171,   171,   172,
     172,   172,   173,   175,   176,   174,   177,   177,   178,   178,
     178,   178,   178,   179,   181,   182,   180,   180,   180,   183,
     183,   185,   184,   186,   186,   186,   187,   187,   187,   187,
     187,   188,   188,   189,   189,   190,   191,   192,   192,   193,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   195,   195,   195,   196,   196,   197,   198,   198,   199,
     199,   199,   199,   200,   200,   200,   201,   201,   201,   202,
     202,   203,   203,   203,   203,   203,   204,   204,   204,   204,
     206,   207,   205,   208,   210,   211,   209,   212,   212,   213,
     215,   214,   216,   214,   217,   217,   218,   219,   220,   221,
     221,   222,   222,   222,   222,   223,   223,   224,   224,   225,
     226,   227,   227,   228,   228,   229,   230,   230,   230,   230,
     230,   230,   230,   230,   232,   231,   233,   233,   234,   235,
     235,   236,   236,   237,   237,   238,   238,   238,   238,   239,
     240,   240,   241,   241,   241,   241,   242,   242,   243,   244,
     244,   245,   246,   246,   247,   248,   248,   249,   250,   250,
     251,   252,   252,   253,   254,   255,   255,   256,   256,   257,
     257,   257,   258,   258,   258,   259,   259,   261,   260,   262,
     262,   262,   262,   263,   263,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   265,   265,
     265,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   266,   266,   266,   266,   266,   266,   266,   266,
     266,   266,   267,   267,   267,   268,   268,   269,   269
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     1,     1,     2,     2,     5,     5,
       5,     4,     0,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     0,     1,     1,     3,     4,     6,
       1,     1,     1,     0,     0,     0,     9,     7,     6,     9,
       8,     3,     0,     2,     1,     1,     0,     3,     1,     0,
       0,     8,     0,     2,     1,     1,     1,     1,     0,     0,
       9,     1,     2,     0,     8,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     5,     0,     2,     2,     1,
       7,     0,     2,     4,     1,     1,     5,     3,     1,     3,
       3,     3,     1,     1,     1,     3,     3,     1,     1,    10,
      10,    10,     7,     0,     0,     9,     0,     2,     1,     1,
       1,     1,     1,     1,     0,     0,     9,     4,     4,     0,
       2,     0,     7,     3,     4,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     4,     4,     4,     6,     6,
       6,     1,     1,     1,     0,     1,     3,     1,     3,     1,
       1,     1,     1,     0,     1,     3,     1,     1,     1,     1,
       3,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       0,     0,     9,     7,     0,     0,     9,     0,     2,     4,
       0,     7,     0,     8,     1,     3,     3,     4,     4,     1,
       3,     4,     4,     4,     4,     1,     4,     5,     8,     1,
       2,     2,     3,     5,     7,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     5,     0,     2,     7,     0,
       2,     3,     2,     1,     1,     1,     1,     1,     1,     6,
       1,     2,     5,     5,     7,     6,     0,     2,     5,     0,
       2,     3,     1,     4,     5,     1,     2,     7,     5,     4,
       7,     0,     2,     1,     2,     0,     1,     1,     3,     1,
       3,     1,     0,     1,     3,     1,     2,     0,     3,     1,
       1,     2,     2,     3,     5,     1,     1,     1,     1,     1,
       1,     2,     4,     6,     3,     3,     3,     2,     2,     2,
       2,     2,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     4,     1,     7,     4,
       4,     1,     1,     1,     1,     1,     1,     2,     4,     6,
       3,     2,     2,     2,     2,     2,     3,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     5,
       4,     1,     7,     4,     4,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3:
#line 244 "p4parser.y"
            {}
#line 2807 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2813 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2819 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2825 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2831 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2837 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2843 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2849 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2855 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2861 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2867 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2873 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2879 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2885 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2891 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2897 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2903 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2909 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2915 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2921 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2927 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2933 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2939 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2945 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2951 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2957 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2963 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2969 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2975 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2981 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2987 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 2993 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 2999 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3005 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3011 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3017 "p4parser.tab.c"
    break;

  case 40:
#line 312 "p4parser.y"
        {}
#line 3023 "p4parser.tab.c"
    break;

  case 41:
#line 316 "p4parser.y"
        {}
#line 3029 "p4parser.tab.c"
    break;

  case 42:
#line 320 "p4parser.y"
              {}
#line 3035 "p4parser.tab.c"
    break;

  case 43:
#line 322 "p4parser.y"
        {}
#line 3041 "p4parser.tab.c"
    break;

  case 44:
#line 324 "p4parser.y"
        {}
#line 3047 "p4parser.tab.c"
    break;

  case 45:
#line 328 "p4parser.y"
                       {}
#line 3053 "p4parser.tab.c"
    break;

  case 46:
#line 329 "p4parser.y"
                       {}
#line 3059 "p4parser.tab.c"
    break;

  case 47:
#line 330 "p4parser.y"
                       {}
#line 3065 "p4parser.tab.c"
    break;

  case 48:
#line 331 "p4parser.y"
                       {}
#line 3071 "p4parser.tab.c"
    break;

  case 49:
#line 332 "p4parser.y"
                       {}
#line 3077 "p4parser.tab.c"
    break;

  case 50:
#line 333 "p4parser.y"
                       {}
#line 3083 "p4parser.tab.c"
    break;

  case 51:
#line 334 "p4parser.y"
                       {}
#line 3089 "p4parser.tab.c"
    break;

  case 52:
#line 335 "p4parser.y"
                       {}
#line 3095 "p4parser.tab.c"
    break;

  case 53:
#line 336 "p4parser.y"
                       {}
#line 3101 "p4parser.tab.c"
    break;

  case 54:
#line 337 "p4parser.y"
                       {}
#line 3107 "p4parser.tab.c"
    break;

  case 55:
#line 338 "p4parser.y"
                       {}
#line 3113 "p4parser.tab.c"
    break;

  case 56:
#line 339 "p4parser.y"
                       {}
#line 3119 "p4parser.tab.c"
    break;

  case 57:
#line 340 "p4parser.y"
                       {}
#line 3125 "p4parser.tab.c"
    break;

  case 58:
#line 341 "p4parser.y"
                       {}
#line 3131 "p4parser.tab.c"
    break;

  case 59:
#line 342 "p4parser.y"
                       {}
#line 3137 "p4parser.tab.c"
    break;

  case 60:
#line 343 "p4parser.y"
                       {}
#line 3143 "p4parser.tab.c"
    break;

  case 61:
#line 344 "p4parser.y"
                       {}
#line 3149 "p4parser.tab.c"
    break;

  case 62:
#line 345 "p4parser.y"
                       {}
#line 3155 "p4parser.tab.c"
    break;

  case 63:
#line 346 "p4parser.y"
                       {}
#line 3161 "p4parser.tab.c"
    break;

  case 64:
#line 347 "p4parser.y"
                       {}
#line 3167 "p4parser.tab.c"
    break;

  case 65:
#line 348 "p4parser.y"
                       {}
#line 3173 "p4parser.tab.c"
    break;

  case 66:
#line 349 "p4parser.y"
                       {}
#line 3179 "p4parser.tab.c"
    break;

  case 67:
#line 350 "p4parser.y"
                       {}
#line 3185 "p4parser.tab.c"
    break;

  case 68:
#line 351 "p4parser.y"
                       {}
#line 3191 "p4parser.tab.c"
    break;

  case 69:
#line 352 "p4parser.y"
                       {}
#line 3197 "p4parser.tab.c"
    break;

  case 70:
#line 353 "p4parser.y"
                       {}
#line 3203 "p4parser.tab.c"
    break;

  case 71:
#line 354 "p4parser.y"
                       {}
#line 3209 "p4parser.tab.c"
    break;

  case 72:
#line 355 "p4parser.y"
                       {}
#line 3215 "p4parser.tab.c"
    break;

  case 73:
#line 356 "p4parser.y"
                       {}
#line 3221 "p4parser.tab.c"
    break;

  case 74:
#line 357 "p4parser.y"
                       {}
#line 3227 "p4parser.tab.c"
    break;

  case 75:
#line 358 "p4parser.y"
                       {}
#line 3233 "p4parser.tab.c"
    break;

  case 76:
#line 359 "p4parser.y"
                       {}
#line 3239 "p4parser.tab.c"
    break;

  case 77:
#line 360 "p4parser.y"
                       {}
#line 3245 "p4parser.tab.c"
    break;

  case 78:
#line 361 "p4parser.y"
                       {}
#line 3251 "p4parser.tab.c"
    break;

  case 79:
#line 362 "p4parser.y"
                       {}
#line 3257 "p4parser.tab.c"
    break;

  case 80:
#line 363 "p4parser.y"
                       {}
#line 3263 "p4parser.tab.c"
    break;

  case 81:
#line 364 "p4parser.y"
                       {}
#line 3269 "p4parser.tab.c"
    break;

  case 82:
#line 365 "p4parser.y"
                       {}
#line 3275 "p4parser.tab.c"
    break;

  case 83:
#line 366 "p4parser.y"
                       {}
#line 3281 "p4parser.tab.c"
    break;

  case 84:
#line 367 "p4parser.y"
                       {}
#line 3287 "p4parser.tab.c"
    break;

  case 85:
#line 368 "p4parser.y"
                       {}
#line 3293 "p4parser.tab.c"
    break;

  case 86:
#line 369 "p4parser.y"
                       {}
#line 3299 "p4parser.tab.c"
    break;

  case 87:
#line 370 "p4parser.y"
                       {}
#line 3305 "p4parser.tab.c"
    break;

  case 88:
#line 371 "p4parser.y"
                       {}
#line 3311 "p4parser.tab.c"
    break;

  case 89:
#line 372 "p4parser.y"
                       {}
#line 3317 "p4parser.tab.c"
    break;

  case 90:
#line 373 "p4parser.y"
                            {}
#line 3323 "p4parser.tab.c"
    break;

  case 91:
#line 375 "p4parser.y"
                       {}
#line 3329 "p4parser.tab.c"
    break;

  case 92:
#line 376 "p4parser.y"
                       {}
#line 3335 "p4parser.tab.c"
    break;

  case 93:
#line 377 "p4parser.y"
                       {}
#line 3341 "p4parser.tab.c"
    break;

  case 94:
#line 378 "p4parser.y"
                       {}
#line 3347 "p4parser.tab.c"
    break;

  case 95:
#line 379 "p4parser.y"
                       {}
#line 3353 "p4parser.tab.c"
    break;

  case 96:
#line 380 "p4parser.y"
                       {}
#line 3359 "p4parser.tab.c"
    break;

  case 97:
#line 381 "p4parser.y"
                       {}
#line 3365 "p4parser.tab.c"
    break;

  case 98:
#line 382 "p4parser.y"
                       {}
#line 3371 "p4parser.tab.c"
    break;

  case 99:
#line 383 "p4parser.y"
                       {}
#line 3377 "p4parser.tab.c"
    break;

  case 100:
#line 384 "p4parser.y"
                       {}
#line 3383 "p4parser.tab.c"
    break;

  case 101:
#line 385 "p4parser.y"
                       {}
#line 3389 "p4parser.tab.c"
    break;

  case 102:
#line 386 "p4parser.y"
                       {}
#line 3395 "p4parser.tab.c"
    break;

  case 103:
#line 387 "p4parser.y"
                       {}
#line 3401 "p4parser.tab.c"
    break;

  case 104:
#line 388 "p4parser.y"
                       {}
#line 3407 "p4parser.tab.c"
    break;

  case 105:
#line 389 "p4parser.y"
                       {}
#line 3413 "p4parser.tab.c"
    break;

  case 106:
#line 390 "p4parser.y"
                       {}
#line 3419 "p4parser.tab.c"
    break;

  case 108:
#line 392 "p4parser.y"
                       {}
#line 3425 "p4parser.tab.c"
    break;

  case 109:
#line 393 "p4parser.y"
                       {}
#line 3431 "p4parser.tab.c"
    break;

  case 110:
#line 394 "p4parser.y"
                       {}
#line 3437 "p4parser.tab.c"
    break;

  case 111:
#line 395 "p4parser.y"
                       {}
#line 3443 "p4parser.tab.c"
    break;

  case 112:
#line 396 "p4parser.y"
                       {}
#line 3449 "p4parser.tab.c"
    break;

  case 113:
#line 397 "p4parser.y"
                       {}
#line 3455 "p4parser.tab.c"
    break;

  case 114:
#line 398 "p4parser.y"
                       {}
#line 3461 "p4parser.tab.c"
    break;

  case 115:
#line 399 "p4parser.y"
                       {}
#line 3467 "p4parser.tab.c"
    break;

  case 116:
#line 400 "p4parser.y"
                       {}
#line 3473 "p4parser.tab.c"
    break;

  case 117:
#line 401 "p4parser.y"
                       {}
#line 3479 "p4parser.tab.c"
    break;

  case 118:
#line 402 "p4parser.y"
                       {}
#line 3485 "p4parser.tab.c"
    break;

  case 119:
#line 403 "p4parser.y"
                       {}
#line 3491 "p4parser.tab.c"
    break;

  case 120:
#line 404 "p4parser.y"
                       {}
#line 3497 "p4parser.tab.c"
    break;

  case 121:
#line 405 "p4parser.y"
                       {}
#line 3503 "p4parser.tab.c"
    break;

  case 122:
#line 406 "p4parser.y"
                       {}
#line 3509 "p4parser.tab.c"
    break;

  case 123:
#line 407 "p4parser.y"
                       {}
#line 3515 "p4parser.tab.c"
    break;

  case 124:
#line 408 "p4parser.y"
                       {}
#line 3521 "p4parser.tab.c"
    break;

  case 125:
#line 409 "p4parser.y"
                       {}
#line 3527 "p4parser.tab.c"
    break;

  case 126:
#line 410 "p4parser.y"
                       {}
#line 3533 "p4parser.tab.c"
    break;

  case 127:
#line 411 "p4parser.y"
                       {}
#line 3539 "p4parser.tab.c"
    break;

  case 128:
#line 412 "p4parser.y"
                       {}
#line 3545 "p4parser.tab.c"
    break;

  case 129:
#line 413 "p4parser.y"
                       {}
#line 3551 "p4parser.tab.c"
    break;

  case 130:
#line 414 "p4parser.y"
                       {}
#line 3557 "p4parser.tab.c"
    break;

  case 131:
#line 418 "p4parser.y"
                                      {}
#line 3563 "p4parser.tab.c"
    break;

  case 132:
#line 419 "p4parser.y"
                                        {}
#line 3569 "p4parser.tab.c"
    break;

  case 133:
#line 423 "p4parser.y"
                                         {}
#line 3575 "p4parser.tab.c"
    break;

  case 134:
#line 427 "p4parser.y"
                                      {}
#line 3581 "p4parser.tab.c"
    break;

  case 135:
#line 428 "p4parser.y"
                                      {}
#line 3587 "p4parser.tab.c"
    break;

  case 136:
#line 432 "p4parser.y"
                                          {}
#line 3593 "p4parser.tab.c"
    break;

  case 137:
#line 433 "p4parser.y"
                                            {}
#line 3599 "p4parser.tab.c"
    break;

  case 138:
#line 437 "p4parser.y"
                                            {}
#line 3605 "p4parser.tab.c"
    break;

  case 139:
#line 438 "p4parser.y"
                                                              {}
#line 3611 "p4parser.tab.c"
    break;

  case 140:
#line 442 "p4parser.y"
                 {}
#line 3617 "p4parser.tab.c"
    break;

  case 141:
#line 443 "p4parser.y"
                   {}
#line 3623 "p4parser.tab.c"
    break;

  case 142:
#line 444 "p4parser.y"
                   {}
#line 3629 "p4parser.tab.c"
    break;

  case 143:
#line 445 "p4parser.y"
                   {}
#line 3635 "p4parser.tab.c"
    break;

  case 144:
#line 449 "p4parser.y"
                                  {}
#line 3641 "p4parser.tab.c"
    break;

  case 145:
#line 450 "p4parser.y"
                        {}
#line 3647 "p4parser.tab.c"
    break;

  case 146:
#line 451 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3656 "p4parser.tab.c"
    break;

  case 147:
#line 459 "p4parser.y"
                     {}
#line 3662 "p4parser.tab.c"
    break;

  case 148:
#line 461 "p4parser.y"
                     {}
#line 3668 "p4parser.tab.c"
    break;

  case 149:
#line 464 "p4parser.y"
                     {}
#line 3674 "p4parser.tab.c"
    break;

  case 150:
#line 467 "p4parser.y"
                     {}
#line 3680 "p4parser.tab.c"
    break;

  case 151:
#line 473 "p4parser.y"
                               {}
#line 3686 "p4parser.tab.c"
    break;

  case 152:
#line 477 "p4parser.y"
                                     {}
#line 3692 "p4parser.tab.c"
    break;

  case 153:
#line 478 "p4parser.y"
                                     {}
#line 3698 "p4parser.tab.c"
    break;

  case 154:
#line 482 "p4parser.y"
                               {}
#line 3704 "p4parser.tab.c"
    break;

  case 155:
#line 483 "p4parser.y"
                               {}
#line 3710 "p4parser.tab.c"
    break;

  case 156:
#line 487 "p4parser.y"
                           {}
#line 3716 "p4parser.tab.c"
    break;

  case 157:
#line 488 "p4parser.y"
                                     {}
#line 3722 "p4parser.tab.c"
    break;

  case 158:
#line 492 "p4parser.y"
                             {}
#line 3728 "p4parser.tab.c"
    break;

  case 159:
#line 498 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3734 "p4parser.tab.c"
    break;

  case 160:
#line 499 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3740 "p4parser.tab.c"
    break;

  case 161:
#line 500 "p4parser.y"
                             {}
#line 3746 "p4parser.tab.c"
    break;

  case 162:
#line 505 "p4parser.y"
                                           {}
#line 3752 "p4parser.tab.c"
    break;

  case 163:
#line 506 "p4parser.y"
                                             {}
#line 3758 "p4parser.tab.c"
    break;

  case 164:
#line 510 "p4parser.y"
                                    {}
#line 3764 "p4parser.tab.c"
    break;

  case 165:
#line 511 "p4parser.y"
                                      {}
#line 3770 "p4parser.tab.c"
    break;

  case 166:
#line 512 "p4parser.y"
                                      {}
#line 3776 "p4parser.tab.c"
    break;

  case 167:
#line 513 "p4parser.y"
                                      {}
#line 3782 "p4parser.tab.c"
    break;

  case 168:
#line 518 "p4parser.y"
                          {}
#line 3788 "p4parser.tab.c"
    break;

  case 169:
#line 519 "p4parser.y"
                          {}
#line 3794 "p4parser.tab.c"
    break;

  case 170:
#line 520 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3803 "p4parser.tab.c"
    break;

  case 171:
#line 527 "p4parser.y"
                                    {}
#line 3809 "p4parser.tab.c"
    break;

  case 172:
#line 528 "p4parser.y"
                                      {}
#line 3815 "p4parser.tab.c"
    break;

  case 173:
#line 532 "p4parser.y"
                              {}
#line 3821 "p4parser.tab.c"
    break;

  case 174:
#line 534 "p4parser.y"
                                      {}
#line 3827 "p4parser.tab.c"
    break;

  case 175:
#line 538 "p4parser.y"
                                     {}
#line 3833 "p4parser.tab.c"
    break;

  case 176:
#line 539 "p4parser.y"
                                       {}
#line 3839 "p4parser.tab.c"
    break;

  case 177:
#line 543 "p4parser.y"
                                    {}
#line 3845 "p4parser.tab.c"
    break;

  case 178:
#line 544 "p4parser.y"
                                      {}
#line 3851 "p4parser.tab.c"
    break;

  case 179:
#line 545 "p4parser.y"
                                      {}
#line 3857 "p4parser.tab.c"
    break;

  case 180:
#line 546 "p4parser.y"
                                      {}
#line 3863 "p4parser.tab.c"
    break;

  case 181:
#line 547 "p4parser.y"
                                      {}
#line 3869 "p4parser.tab.c"
    break;

  case 182:
#line 548 "p4parser.y"
                                      {}
#line 3875 "p4parser.tab.c"
    break;

  case 183:
#line 549 "p4parser.y"
                                      {}
#line 3881 "p4parser.tab.c"
    break;

  case 184:
#line 553 "p4parser.y"
                           {}
#line 3887 "p4parser.tab.c"
    break;

  case 185:
#line 554 "p4parser.y"
                               {}
#line 3893 "p4parser.tab.c"
    break;

  case 186:
#line 558 "p4parser.y"
                                {}
#line 3899 "p4parser.tab.c"
    break;

  case 187:
#line 559 "p4parser.y"
                                  {}
#line 3905 "p4parser.tab.c"
    break;

  case 188:
#line 563 "p4parser.y"
                           {}
#line 3911 "p4parser.tab.c"
    break;

  case 189:
#line 564 "p4parser.y"
                       {}
#line 3917 "p4parser.tab.c"
    break;

  case 190:
#line 569 "p4parser.y"
                              {}
#line 3923 "p4parser.tab.c"
    break;

  case 191:
#line 573 "p4parser.y"
                               {}
#line 3929 "p4parser.tab.c"
    break;

  case 192:
#line 574 "p4parser.y"
                                 {}
#line 3935 "p4parser.tab.c"
    break;

  case 193:
#line 579 "p4parser.y"
      {}
#line 3941 "p4parser.tab.c"
    break;

  case 194:
#line 583 "p4parser.y"
                              {}
#line 3947 "p4parser.tab.c"
    break;

  case 195:
#line 584 "p4parser.y"
                                {}
#line 3953 "p4parser.tab.c"
    break;

  case 196:
#line 589 "p4parser.y"
                                {}
#line 3959 "p4parser.tab.c"
    break;

  case 197:
#line 590 "p4parser.y"
                                                    {}
#line 3965 "p4parser.tab.c"
    break;

  case 198:
#line 594 "p4parser.y"
                           {}
#line 3971 "p4parser.tab.c"
    break;

  case 199:
#line 595 "p4parser.y"
                                                        {}
#line 3977 "p4parser.tab.c"
    break;

  case 200:
#line 600 "p4parser.y"
                                 {}
#line 3983 "p4parser.tab.c"
    break;

  case 201:
#line 601 "p4parser.y"
                                   {}
#line 3989 "p4parser.tab.c"
    break;

  case 202:
#line 602 "p4parser.y"
                                  {}
#line 3995 "p4parser.tab.c"
    break;

  case 203:
#line 603 "p4parser.y"
                                       {}
#line 4001 "p4parser.tab.c"
    break;

  case 204:
#line 607 "p4parser.y"
                                {}
#line 4007 "p4parser.tab.c"
    break;

  case 205:
#line 608 "p4parser.y"
                                 {}
#line 4013 "p4parser.tab.c"
    break;

  case 206:
#line 609 "p4parser.y"
                                   {}
#line 4019 "p4parser.tab.c"
    break;

  case 207:
#line 610 "p4parser.y"
                                  {}
#line 4025 "p4parser.tab.c"
    break;

  case 208:
#line 611 "p4parser.y"
                                       {}
#line 4031 "p4parser.tab.c"
    break;

  case 209:
#line 617 "p4parser.y"
        {}
#line 4037 "p4parser.tab.c"
    break;

  case 210:
#line 620 "p4parser.y"
        {}
#line 4043 "p4parser.tab.c"
    break;

  case 211:
#line 623 "p4parser.y"
        {}
#line 4049 "p4parser.tab.c"
    break;

  case 212:
#line 631 "p4parser.y"
        {}
#line 4055 "p4parser.tab.c"
    break;

  case 213:
#line 636 "p4parser.y"
                     {}
#line 4061 "p4parser.tab.c"
    break;

  case 214:
#line 637 "p4parser.y"
                          {}
#line 4067 "p4parser.tab.c"
    break;

  case 215:
#line 638 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4076 "p4parser.tab.c"
    break;

  case 216:
#line 645 "p4parser.y"
           {}
#line 4082 "p4parser.tab.c"
    break;

  case 217:
#line 646 "p4parser.y"
                                                       {}
#line 4088 "p4parser.tab.c"
    break;

  case 218:
#line 650 "p4parser.y"
                             {}
#line 4094 "p4parser.tab.c"
    break;

  case 219:
#line 651 "p4parser.y"
                               {}
#line 4100 "p4parser.tab.c"
    break;

  case 220:
#line 652 "p4parser.y"
                               {}
#line 4106 "p4parser.tab.c"
    break;

  case 221:
#line 653 "p4parser.y"
                               {}
#line 4112 "p4parser.tab.c"
    break;

  case 222:
#line 654 "p4parser.y"
                               {}
#line 4118 "p4parser.tab.c"
    break;

  case 223:
#line 658 "p4parser.y"
                   {}
#line 4124 "p4parser.tab.c"
    break;

  case 224:
#line 665 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4133 "p4parser.tab.c"
    break;

  case 225:
#line 669 "p4parser.y"
                          {}
#line 4139 "p4parser.tab.c"
    break;

  case 227:
#line 671 "p4parser.y"
                                                        { bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 2)); }
#line 4145 "p4parser.tab.c"
    break;

  case 229:
#line 676 "p4parser.y"
                                     {}
#line 4151 "p4parser.tab.c"
    break;

  case 230:
#line 677 "p4parser.y"
                                       {}
#line 4157 "p4parser.tab.c"
    break;

  case 231:
#line 682 "p4parser.y"
                               {}
#line 4163 "p4parser.tab.c"
    break;

  case 232:
#line 683 "p4parser.y"
                                      {}
#line 4169 "p4parser.tab.c"
    break;

  case 233:
#line 687 "p4parser.y"
                                               {}
#line 4175 "p4parser.tab.c"
    break;

  case 234:
#line 688 "p4parser.y"
                                                          {}
#line 4181 "p4parser.tab.c"
    break;

  case 235:
#line 690 "p4parser.y"
                                        {}
#line 4187 "p4parser.tab.c"
    break;

  case 236:
#line 696 "p4parser.y"
                                     {}
#line 4193 "p4parser.tab.c"
    break;

  case 237:
#line 697 "p4parser.y"
                                       {}
#line 4199 "p4parser.tab.c"
    break;

  case 238:
#line 698 "p4parser.y"
                                       {}
#line 4205 "p4parser.tab.c"
    break;

  case 239:
#line 699 "p4parser.y"
                                       {}
#line 4211 "p4parser.tab.c"
    break;

  case 240:
#line 700 "p4parser.y"
                                       {}
#line 4217 "p4parser.tab.c"
    break;

  case 241:
#line 704 "p4parser.y"
                                     {}
#line 4223 "p4parser.tab.c"
    break;

  case 242:
#line 705 "p4parser.y"
                                       {}
#line 4229 "p4parser.tab.c"
    break;

  case 243:
#line 709 "p4parser.y"
                                     {}
#line 4235 "p4parser.tab.c"
    break;

  case 244:
#line 710 "p4parser.y"
                                       {}
#line 4241 "p4parser.tab.c"
    break;

  case 245:
#line 714 "p4parser.y"
                                     {}
#line 4247 "p4parser.tab.c"
    break;

  case 246:
#line 718 "p4parser.y"
                                              {}
#line 4253 "p4parser.tab.c"
    break;

  case 247:
#line 722 "p4parser.y"
                                                    {}
#line 4259 "p4parser.tab.c"
    break;

  case 248:
#line 723 "p4parser.y"
                                                      {}
#line 4265 "p4parser.tab.c"
    break;

  case 249:
#line 727 "p4parser.y"
                                              {}
#line 4271 "p4parser.tab.c"
    break;

  case 250:
#line 731 "p4parser.y"
           {}
#line 4277 "p4parser.tab.c"
    break;

  case 251:
#line 732 "p4parser.y"
             {}
#line 4283 "p4parser.tab.c"
    break;

  case 252:
#line 733 "p4parser.y"
             {}
#line 4289 "p4parser.tab.c"
    break;

  case 253:
#line 734 "p4parser.y"
             {}
#line 4295 "p4parser.tab.c"
    break;

  case 254:
#line 735 "p4parser.y"
             {}
#line 4301 "p4parser.tab.c"
    break;

  case 255:
#line 737 "p4parser.y"
      {}
#line 4307 "p4parser.tab.c"
    break;

  case 256:
#line 739 "p4parser.y"
      {}
#line 4313 "p4parser.tab.c"
    break;

  case 257:
#line 741 "p4parser.y"
      {}
#line 4319 "p4parser.tab.c"
    break;

  case 258:
#line 744 "p4parser.y"
      {}
#line 4325 "p4parser.tab.c"
    break;

  case 259:
#line 746 "p4parser.y"
      {}
#line 4331 "p4parser.tab.c"
    break;

  case 260:
#line 748 "p4parser.y"
      {}
#line 4337 "p4parser.tab.c"
    break;

  case 261:
#line 752 "p4parser.y"
                {}
#line 4343 "p4parser.tab.c"
    break;

  case 262:
#line 753 "p4parser.y"
                  {}
#line 4349 "p4parser.tab.c"
    break;

  case 263:
#line 754 "p4parser.y"
                  {}
#line 4355 "p4parser.tab.c"
    break;

  case 264:
#line 759 "p4parser.y"
                              {}
#line 4361 "p4parser.tab.c"
    break;

  case 265:
#line 760 "p4parser.y"
                                {}
#line 4367 "p4parser.tab.c"
    break;

  case 266:
#line 764 "p4parser.y"
                                      {}
#line 4373 "p4parser.tab.c"
    break;

  case 267:
#line 768 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4385 "p4parser.tab.c"
    break;

  case 268:
#line 775 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4393 "p4parser.tab.c"
    break;

  case 269:
#line 781 "p4parser.y"
                                {}
#line 4399 "p4parser.tab.c"
    break;

  case 270:
#line 782 "p4parser.y"
                                  {}
#line 4405 "p4parser.tab.c"
    break;

  case 271:
#line 784 "p4parser.y"
                                  {}
#line 4411 "p4parser.tab.c"
    break;

  case 272:
#line 785 "p4parser.y"
                                       {}
#line 4417 "p4parser.tab.c"
    break;

  case 273:
#line 789 "p4parser.y"
                                   {}
#line 4423 "p4parser.tab.c"
    break;

  case 274:
#line 790 "p4parser.y"
                                     {}
#line 4429 "p4parser.tab.c"
    break;

  case 275:
#line 791 "p4parser.y"
                                       {}
#line 4435 "p4parser.tab.c"
    break;

  case 276:
#line 795 "p4parser.y"
                                {}
#line 4441 "p4parser.tab.c"
    break;

  case 277:
#line 796 "p4parser.y"
                                  {}
#line 4447 "p4parser.tab.c"
    break;

  case 278:
#line 797 "p4parser.y"
                                       {}
#line 4453 "p4parser.tab.c"
    break;

  case 279:
#line 803 "p4parser.y"
                                       {}
#line 4459 "p4parser.tab.c"
    break;

  case 280:
#line 804 "p4parser.y"
                                           {}
#line 4465 "p4parser.tab.c"
    break;

  case 281:
#line 808 "p4parser.y"
                               {}
#line 4471 "p4parser.tab.c"
    break;

  case 282:
#line 809 "p4parser.y"
                                       {}
#line 4477 "p4parser.tab.c"
    break;

  case 283:
#line 810 "p4parser.y"
                                       {}
#line 4483 "p4parser.tab.c"
    break;

  case 284:
#line 811 "p4parser.y"
                                       {}
#line 4489 "p4parser.tab.c"
    break;

  case 285:
#line 812 "p4parser.y"
                                       {}
#line 4495 "p4parser.tab.c"
    break;

  case 286:
#line 816 "p4parser.y"
                                     {}
#line 4501 "p4parser.tab.c"
    break;

  case 287:
#line 817 "p4parser.y"
                                       {}
#line 4507 "p4parser.tab.c"
    break;

  case 288:
#line 818 "p4parser.y"
                                       {}
#line 4513 "p4parser.tab.c"
    break;

  case 289:
#line 819 "p4parser.y"
                                       {}
#line 4519 "p4parser.tab.c"
    break;

  case 290:
#line 823 "p4parser.y"
                               {}
#line 4525 "p4parser.tab.c"
    break;

  case 291:
#line 823 "p4parser.y"
                                                    {}
#line 4531 "p4parser.tab.c"
    break;

  case 292:
#line 825 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4540 "p4parser.tab.c"
    break;

  case 293:
#line 834 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4549 "p4parser.tab.c"
    break;

  case 294:
#line 841 "p4parser.y"
                                     {}
#line 4555 "p4parser.tab.c"
    break;

  case 295:
#line 841 "p4parser.y"
                                                          {}
#line 4561 "p4parser.tab.c"
    break;

  case 296:
#line 842 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4570 "p4parser.tab.c"
    break;

  case 297:
#line 849 "p4parser.y"
                                     {}
#line 4576 "p4parser.tab.c"
    break;

  case 298:
#line 850 "p4parser.y"
                                       {}
#line 4582 "p4parser.tab.c"
    break;

  case 299:
#line 854 "p4parser.y"
                                           {}
#line 4588 "p4parser.tab.c"
    break;

  case 300:
#line 859 "p4parser.y"
                  {}
#line 4594 "p4parser.tab.c"
    break;

  case 301:
#line 860 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4603 "p4parser.tab.c"
    break;

  case 302:
#line 864 "p4parser.y"
                                       {}
#line 4609 "p4parser.tab.c"
    break;

  case 303:
#line 865 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4618 "p4parser.tab.c"
    break;

  case 304:
#line 872 "p4parser.y"
                            {}
#line 4624 "p4parser.tab.c"
    break;

  case 305:
#line 873 "p4parser.y"
                                                        {}
#line 4630 "p4parser.tab.c"
    break;

  case 306:
#line 877 "p4parser.y"
                               {}
#line 4636 "p4parser.tab.c"
    break;

  case 307:
#line 882 "p4parser.y"
        {}
#line 4642 "p4parser.tab.c"
    break;

  case 308:
#line 887 "p4parser.y"
        {}
#line 4648 "p4parser.tab.c"
    break;

  case 309:
#line 892 "p4parser.y"
                            {}
#line 4654 "p4parser.tab.c"
    break;

  case 310:
#line 893 "p4parser.y"
                                {}
#line 4660 "p4parser.tab.c"
    break;

  case 311:
#line 897 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4669 "p4parser.tab.c"
    break;

  case 312:
#line 901 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4678 "p4parser.tab.c"
    break;

  case 313:
#line 905 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4687 "p4parser.tab.c"
    break;

  case 314:
#line 909 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4696 "p4parser.tab.c"
    break;

  case 315:
#line 920 "p4parser.y"
        {}
#line 4702 "p4parser.tab.c"
    break;

  case 316:
#line 922 "p4parser.y"
        {}
#line 4708 "p4parser.tab.c"
    break;

  case 317:
#line 927 "p4parser.y"
        {}
#line 4714 "p4parser.tab.c"
    break;

  case 318:
#line 929 "p4parser.y"
        {}
#line 4720 "p4parser.tab.c"
    break;

  case 319:
#line 933 "p4parser.y"
                   {}
#line 4726 "p4parser.tab.c"
    break;

  case 320:
#line 937 "p4parser.y"
                   {}
#line 4732 "p4parser.tab.c"
    break;

  case 321:
#line 941 "p4parser.y"
                                {}
#line 4738 "p4parser.tab.c"
    break;

  case 322:
#line 942 "p4parser.y"
                                  {}
#line 4744 "p4parser.tab.c"
    break;

  case 323:
#line 947 "p4parser.y"
        {}
#line 4750 "p4parser.tab.c"
    break;

  case 324:
#line 949 "p4parser.y"
        {}
#line 4756 "p4parser.tab.c"
    break;

  case 325:
#line 954 "p4parser.y"
                                                              {}
#line 4762 "p4parser.tab.c"
    break;

  case 326:
#line 958 "p4parser.y"
                                     {}
#line 4768 "p4parser.tab.c"
    break;

  case 327:
#line 959 "p4parser.y"
                                       {}
#line 4774 "p4parser.tab.c"
    break;

  case 328:
#line 960 "p4parser.y"
                                       {}
#line 4780 "p4parser.tab.c"
    break;

  case 329:
#line 961 "p4parser.y"
                                       {}
#line 4786 "p4parser.tab.c"
    break;

  case 330:
#line 962 "p4parser.y"
                                       {}
#line 4792 "p4parser.tab.c"
    break;

  case 331:
#line 963 "p4parser.y"
                                       {}
#line 4798 "p4parser.tab.c"
    break;

  case 332:
#line 964 "p4parser.y"
                                       {}
#line 4804 "p4parser.tab.c"
    break;

  case 333:
#line 965 "p4parser.y"
                                       {}
#line 4810 "p4parser.tab.c"
    break;

  case 334:
#line 969 "p4parser.y"
                           {}
#line 4816 "p4parser.tab.c"
    break;

  case 335:
#line 970 "p4parser.y"
                             {}
#line 4822 "p4parser.tab.c"
    break;

  case 336:
#line 974 "p4parser.y"
                                          {}
#line 4828 "p4parser.tab.c"
    break;

  case 337:
#line 975 "p4parser.y"
                                            {}
#line 4834 "p4parser.tab.c"
    break;

  case 338:
#line 979 "p4parser.y"
                                                                  {}
#line 4840 "p4parser.tab.c"
    break;

  case 339:
#line 983 "p4parser.y"
                             {}
#line 4846 "p4parser.tab.c"
    break;

  case 340:
#line 984 "p4parser.y"
                               {}
#line 4852 "p4parser.tab.c"
    break;

  case 341:
#line 988 "p4parser.y"
                                     {}
#line 4858 "p4parser.tab.c"
    break;

  case 342:
#line 989 "p4parser.y"
                                       {}
#line 4864 "p4parser.tab.c"
    break;

  case 343:
#line 993 "p4parser.y"
                             {}
#line 4870 "p4parser.tab.c"
    break;

  case 344:
#line 994 "p4parser.y"
                               {}
#line 4876 "p4parser.tab.c"
    break;

  case 345:
#line 998 "p4parser.y"
                             {}
#line 4882 "p4parser.tab.c"
    break;

  case 346:
#line 999 "p4parser.y"
                               {}
#line 4888 "p4parser.tab.c"
    break;

  case 347:
#line 1000 "p4parser.y"
                               {}
#line 4894 "p4parser.tab.c"
    break;

  case 348:
#line 1001 "p4parser.y"
                               {}
#line 4900 "p4parser.tab.c"
    break;

  case 349:
#line 1009 "p4parser.y"
          {}
#line 4906 "p4parser.tab.c"
    break;

  case 350:
#line 1013 "p4parser.y"
                                       {}
#line 4912 "p4parser.tab.c"
    break;

  case 351:
#line 1014 "p4parser.y"
                                         {}
#line 4918 "p4parser.tab.c"
    break;

  case 352:
#line 1019 "p4parser.y"
        {}
#line 4924 "p4parser.tab.c"
    break;

  case 353:
#line 1021 "p4parser.y"
        {}
#line 4930 "p4parser.tab.c"
    break;

  case 354:
#line 1023 "p4parser.y"
        {}
#line 4936 "p4parser.tab.c"
    break;

  case 355:
#line 1025 "p4parser.y"
        {}
#line 4942 "p4parser.tab.c"
    break;

  case 356:
#line 1029 "p4parser.y"
                                       {}
#line 4948 "p4parser.tab.c"
    break;

  case 357:
#line 1030 "p4parser.y"
                                         {}
#line 4954 "p4parser.tab.c"
    break;

  case 358:
#line 1035 "p4parser.y"
                                         {}
#line 4960 "p4parser.tab.c"
    break;

  case 359:
#line 1039 "p4parser.y"
           {}
#line 4966 "p4parser.tab.c"
    break;

  case 360:
#line 1041 "p4parser.y"
        {}
#line 4972 "p4parser.tab.c"
    break;

  case 362:
#line 1050 "p4parser.y"
        {}
#line 4978 "p4parser.tab.c"
    break;

  case 363:
#line 1052 "p4parser.y"
        {}
#line 4984 "p4parser.tab.c"
    break;

  case 364:
#line 1057 "p4parser.y"
        {}
#line 4990 "p4parser.tab.c"
    break;

  case 365:
#line 1061 "p4parser.y"
                                   {}
#line 4996 "p4parser.tab.c"
    break;

  case 366:
#line 1062 "p4parser.y"
                                     {}
#line 5002 "p4parser.tab.c"
    break;

  case 367:
#line 1068 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 5011 "p4parser.tab.c"
    break;

  case 368:
#line 1077 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5020 "p4parser.tab.c"
    break;

  case 369:
#line 1081 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5029 "p4parser.tab.c"
    break;

  case 370:
#line 1089 "p4parser.y"
                                     {}
#line 5035 "p4parser.tab.c"
    break;

  case 371:
#line 1093 "p4parser.y"
                                     {}
#line 5041 "p4parser.tab.c"
    break;

  case 372:
#line 1094 "p4parser.y"
                                          {}
#line 5047 "p4parser.tab.c"
    break;

  case 373:
#line 1098 "p4parser.y"
                                        {}
#line 5053 "p4parser.tab.c"
    break;

  case 374:
#line 1104 "p4parser.y"
                                       {}
#line 5059 "p4parser.tab.c"
    break;

  case 375:
#line 1108 "p4parser.y"
                                       {}
#line 5065 "p4parser.tab.c"
    break;

  case 376:
#line 1109 "p4parser.y"
                                         {}
#line 5071 "p4parser.tab.c"
    break;

  case 377:
#line 1113 "p4parser.y"
                                       {}
#line 5077 "p4parser.tab.c"
    break;

  case 378:
#line 1114 "p4parser.y"
                                           {}
#line 5083 "p4parser.tab.c"
    break;

  case 379:
#line 1118 "p4parser.y"
                                       {}
#line 5089 "p4parser.tab.c"
    break;

  case 380:
#line 1119 "p4parser.y"
                                            {}
#line 5095 "p4parser.tab.c"
    break;

  case 381:
#line 1120 "p4parser.y"
                                              {}
#line 5101 "p4parser.tab.c"
    break;

  case 382:
#line 1124 "p4parser.y"
                                       {}
#line 5107 "p4parser.tab.c"
    break;

  case 383:
#line 1125 "p4parser.y"
                                         {}
#line 5113 "p4parser.tab.c"
    break;

  case 384:
#line 1126 "p4parser.y"
                                           {}
#line 5119 "p4parser.tab.c"
    break;

  case 385:
#line 1130 "p4parser.y"
                                       {}
#line 5125 "p4parser.tab.c"
    break;

  case 386:
#line 1131 "p4parser.y"
                                         {}
#line 5131 "p4parser.tab.c"
    break;

  case 387:
#line 1135 "p4parser.y"
        {}
#line 5137 "p4parser.tab.c"
    break;

  case 388:
#line 1135 "p4parser.y"
                {}
#line 5143 "p4parser.tab.c"
    break;

  case 389:
#line 1139 "p4parser.y"
                                       {}
#line 5149 "p4parser.tab.c"
    break;

  case 390:
#line 1140 "p4parser.y"
                                         {}
#line 5155 "p4parser.tab.c"
    break;

  case 391:
#line 1141 "p4parser.y"
                                         {}
#line 5161 "p4parser.tab.c"
    break;

  case 392:
#line 1142 "p4parser.y"
                                       {}
#line 5167 "p4parser.tab.c"
    break;

  case 393:
#line 1146 "p4parser.y"
                                            {}
#line 5173 "p4parser.tab.c"
    break;

  case 394:
#line 1147 "p4parser.y"
                                                      {}
#line 5179 "p4parser.tab.c"
    break;

  case 395:
#line 1150 "p4parser.y"
                                       {}
#line 5185 "p4parser.tab.c"
    break;

  case 396:
#line 1151 "p4parser.y"
                                         {}
#line 5191 "p4parser.tab.c"
    break;

  case 397:
#line 1152 "p4parser.y"
                                         {}
#line 5197 "p4parser.tab.c"
    break;

  case 398:
#line 1153 "p4parser.y"
                                         {}
#line 5203 "p4parser.tab.c"
    break;

  case 399:
#line 1154 "p4parser.y"
                                         {}
#line 5209 "p4parser.tab.c"
    break;

  case 400:
#line 1155 "p4parser.y"
                                         {}
#line 5215 "p4parser.tab.c"
    break;

  case 401:
#line 1156 "p4parser.y"
                                         {}
#line 5221 "p4parser.tab.c"
    break;

  case 402:
#line 1157 "p4parser.y"
                                                     {}
#line 5227 "p4parser.tab.c"
    break;

  case 403:
#line 1158 "p4parser.y"
                                                                 {}
#line 5233 "p4parser.tab.c"
    break;

  case 404:
#line 1159 "p4parser.y"
                                                 {}
#line 5239 "p4parser.tab.c"
    break;

  case 405:
#line 1160 "p4parser.y"
                                                 {}
#line 5245 "p4parser.tab.c"
    break;

  case 406:
#line 1161 "p4parser.y"
                                                 {}
#line 5251 "p4parser.tab.c"
    break;

  case 407:
#line 1162 "p4parser.y"
                                         {}
#line 5257 "p4parser.tab.c"
    break;

  case 408:
#line 1163 "p4parser.y"
                                                {}
#line 5263 "p4parser.tab.c"
    break;

  case 409:
#line 1164 "p4parser.y"
                                           {}
#line 5269 "p4parser.tab.c"
    break;

  case 410:
#line 1165 "p4parser.y"
                                          {}
#line 5275 "p4parser.tab.c"
    break;

  case 411:
#line 1167 "p4parser.y"
        {}
#line 5281 "p4parser.tab.c"
    break;

  case 412:
#line 1169 "p4parser.y"
        {}
#line 5287 "p4parser.tab.c"
    break;

  case 413:
#line 1170 "p4parser.y"
                                         {}
#line 5293 "p4parser.tab.c"
    break;

  case 414:
#line 1171 "p4parser.y"
                                         {}
#line 5299 "p4parser.tab.c"
    break;

  case 415:
#line 1172 "p4parser.y"
                                         {}
#line 5305 "p4parser.tab.c"
    break;

  case 416:
#line 1173 "p4parser.y"
                                         {}
#line 5311 "p4parser.tab.c"
    break;

  case 417:
#line 1174 "p4parser.y"
                                          {}
#line 5317 "p4parser.tab.c"
    break;

  case 418:
#line 1175 "p4parser.y"
                                           {}
#line 5323 "p4parser.tab.c"
    break;

  case 419:
#line 1176 "p4parser.y"
                                            {}
#line 5329 "p4parser.tab.c"
    break;

  case 420:
#line 1177 "p4parser.y"
                                             {}
#line 5335 "p4parser.tab.c"
    break;

  case 421:
#line 1178 "p4parser.y"
                                        {}
#line 5341 "p4parser.tab.c"
    break;

  case 422:
#line 1180 "p4parser.y"
        {}
#line 5347 "p4parser.tab.c"
    break;

  case 423:
#line 1181 "p4parser.y"
                                       {}
#line 5353 "p4parser.tab.c"
    break;

  case 424:
#line 1182 "p4parser.y"
                                       {}
#line 5359 "p4parser.tab.c"
    break;

  case 425:
#line 1184 "p4parser.y"
                                         {}
#line 5365 "p4parser.tab.c"
    break;

  case 426:
#line 1185 "p4parser.y"
                                             {}
#line 5371 "p4parser.tab.c"
    break;

  case 427:
#line 1187 "p4parser.y"
                                       {}
#line 5377 "p4parser.tab.c"
    break;

  case 428:
#line 1188 "p4parser.y"
                                       {}
#line 5383 "p4parser.tab.c"
    break;

  case 429:
#line 1189 "p4parser.y"
                                             {}
#line 5389 "p4parser.tab.c"
    break;

  case 430:
#line 1190 "p4parser.y"
                                             {}
#line 5395 "p4parser.tab.c"
    break;

  case 431:
#line 1191 "p4parser.y"
                                            {}
#line 5401 "p4parser.tab.c"
    break;

  case 432:
#line 1192 "p4parser.y"
                                       {}
#line 5407 "p4parser.tab.c"
    break;

  case 433:
#line 1193 "p4parser.y"
                                        {}
#line 5413 "p4parser.tab.c"
    break;

  case 434:
#line 1194 "p4parser.y"
                                       {}
#line 5419 "p4parser.tab.c"
    break;

  case 435:
#line 1195 "p4parser.y"
                                                      {}
#line 5425 "p4parser.tab.c"
    break;

  case 436:
#line 1196 "p4parser.y"
                                                      {}
#line 5431 "p4parser.tab.c"
    break;

  case 437:
#line 1197 "p4parser.y"
                         {}
#line 5437 "p4parser.tab.c"
    break;

  case 438:
#line 1201 "p4parser.y"
        {}
#line 5443 "p4parser.tab.c"
    break;

  case 439:
#line 1203 "p4parser.y"
        {}
#line 5449 "p4parser.tab.c"
    break;

  case 440:
#line 1205 "p4parser.y"
        {}
#line 5455 "p4parser.tab.c"
    break;

  case 441:
#line 1209 "p4parser.y"
                                       {}
#line 5461 "p4parser.tab.c"
    break;

  case 442:
#line 1210 "p4parser.y"
                                         {}
#line 5467 "p4parser.tab.c"
    break;

  case 443:
#line 1211 "p4parser.y"
                                         {}
#line 5473 "p4parser.tab.c"
    break;

  case 444:
#line 1212 "p4parser.y"
                                         {}
#line 5479 "p4parser.tab.c"
    break;

  case 445:
#line 1213 "p4parser.y"
                                         {}
#line 5485 "p4parser.tab.c"
    break;

  case 446:
#line 1214 "p4parser.y"
                                         {}
#line 5491 "p4parser.tab.c"
    break;

  case 447:
#line 1215 "p4parser.y"
                                         {}
#line 5497 "p4parser.tab.c"
    break;

  case 448:
#line 1216 "p4parser.y"
                                                             {}
#line 5503 "p4parser.tab.c"
    break;

  case 449:
#line 1217 "p4parser.y"
                                                                         {}
#line 5509 "p4parser.tab.c"
    break;

  case 450:
#line 1218 "p4parser.y"
                                                 {}
#line 5515 "p4parser.tab.c"
    break;

  case 451:
#line 1219 "p4parser.y"
                                         {}
#line 5521 "p4parser.tab.c"
    break;

  case 452:
#line 1220 "p4parser.y"
                                                {}
#line 5527 "p4parser.tab.c"
    break;

  case 453:
#line 1221 "p4parser.y"
                                           {}
#line 5533 "p4parser.tab.c"
    break;

  case 454:
#line 1222 "p4parser.y"
                                          {}
#line 5539 "p4parser.tab.c"
    break;

  case 455:
#line 1224 "p4parser.y"
        {}
#line 5545 "p4parser.tab.c"
    break;

  case 456:
#line 1226 "p4parser.y"
        {}
#line 5551 "p4parser.tab.c"
    break;

  case 457:
#line 1227 "p4parser.y"
                                                 {}
#line 5557 "p4parser.tab.c"
    break;

  case 458:
#line 1228 "p4parser.y"
                                                 {}
#line 5563 "p4parser.tab.c"
    break;

  case 459:
#line 1229 "p4parser.y"
                                                 {}
#line 5569 "p4parser.tab.c"
    break;

  case 460:
#line 1230 "p4parser.y"
                                                 {}
#line 5575 "p4parser.tab.c"
    break;

  case 461:
#line 1231 "p4parser.y"
                                                  {}
#line 5581 "p4parser.tab.c"
    break;

  case 462:
#line 1232 "p4parser.y"
                                                   {}
#line 5587 "p4parser.tab.c"
    break;

  case 463:
#line 1233 "p4parser.y"
                                                    {}
#line 5593 "p4parser.tab.c"
    break;

  case 464:
#line 1234 "p4parser.y"
                                                     {}
#line 5599 "p4parser.tab.c"
    break;

  case 465:
#line 1235 "p4parser.y"
                                                {}
#line 5605 "p4parser.tab.c"
    break;

  case 466:
#line 1237 "p4parser.y"
        {}
#line 5611 "p4parser.tab.c"
    break;

  case 467:
#line 1238 "p4parser.y"
                                               {}
#line 5617 "p4parser.tab.c"
    break;

  case 468:
#line 1239 "p4parser.y"
                                               {}
#line 5623 "p4parser.tab.c"
    break;

  case 469:
#line 1241 "p4parser.y"
                                         {}
#line 5629 "p4parser.tab.c"
    break;

  case 470:
#line 1242 "p4parser.y"
                                                     {}
#line 5635 "p4parser.tab.c"
    break;

  case 471:
#line 1243 "p4parser.y"
                                               {}
#line 5641 "p4parser.tab.c"
    break;

  case 472:
#line 1244 "p4parser.y"
                                               {}
#line 5647 "p4parser.tab.c"
    break;

  case 473:
#line 1245 "p4parser.y"
                                                     {}
#line 5653 "p4parser.tab.c"
    break;

  case 474:
#line 1246 "p4parser.y"
                                                     {}
#line 5659 "p4parser.tab.c"
    break;

  case 475:
#line 1247 "p4parser.y"
                                                    {}
#line 5665 "p4parser.tab.c"
    break;

  case 476:
#line 1248 "p4parser.y"
                                               {}
#line 5671 "p4parser.tab.c"
    break;

  case 477:
#line 1249 "p4parser.y"
                                                {}
#line 5677 "p4parser.tab.c"
    break;

  case 478:
#line 1250 "p4parser.y"
                                               {}
#line 5683 "p4parser.tab.c"
    break;

  case 479:
#line 1251 "p4parser.y"
                                                              {}
#line 5689 "p4parser.tab.c"
    break;

  case 480:
#line 1252 "p4parser.y"
                                                      {}
#line 5695 "p4parser.tab.c"
    break;

  case 482:
#line 1258 "p4parser.y"
        {}
#line 5701 "p4parser.tab.c"
    break;

  case 483:
#line 1260 "p4parser.y"
        {}
#line 5707 "p4parser.tab.c"
    break;

  case 484:
#line 1262 "p4parser.y"
        {}
#line 5713 "p4parser.tab.c"
    break;


#line 5717 "p4parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1290 "p4parser.y"


/** True when statistics should be output. */
private boolean languageStatistics = false;

/** Turn on error reporting. */
private static boolean showErrors = false;

/** Turn on debugging messages. */
private static boolean debug = false;

/** Turn on checkers. */
private static boolean enableCheckers = false;

/** Turn on checkers. */
private static List<String> extraConstraints = null;

/** Turn on function analysis. */
private static boolean enableFunctionAnalysis = false;

/** A symbol table for analysis. */
private P4Context.SymbolTable functionTable;

/** Turn on kconfig feature model clauses. */
private boolean hasClauses = false;

/** The clauses for the kconfig feature model. */
private Clauses featureClauses = null;

/** The kconfig feature model solver. */
private ISolver featureSolver;

/** The assumptions of the feature model, i.e., non-arch config vars. */
private VecInt modelAssumptions;

/**
 * Turn language statistics collection on.  Default is off.
 *
 * @param b True is on.
 */
public void collectStatistics(boolean b) {
  languageStatistics = b;
}

/**
 * Show errors.
 *
 * @param b True is on.
 */
public void showErrors(boolean b) {
  showErrors = b;
}

/**
 * Show debugging messages.
 *
 * @param b True is on.
 */
public void debug(boolean b) {
  debug = b;
}

/**
 * Enable checkers.
 *
 * @param b Enable checkers if true.
 */
public void enableCheckers(boolean b) {
  this.enableCheckers(b, null);
}

/**
 * Enable checkers.
 *
 * @param b Enable checkers if true.
 * @param extraConstraints Extra constraints to SAT solver.
 */
public void enableCheckers(boolean b, List<String> extraConstraints) {
  this.enableCheckers = b;
  if (null == extraConstraints) {
    // avoid having to check for null
    extraConstraints = new ArrayList<String>();
  }
  this.extraConstraints = extraConstraints;
}

/**
 * Enable function analysis.
 */
public void enableFunctionAnalysis() {
  this.enableFunctionAnalysis = true;
  this.functionTable = new P4Context.SymbolTable();
}

/**
 * Add kconfig feature model clauses.
 *
 * @param clauses The clauses.
 */
public void addClauses(Clauses clauses, int[] assumptions) {
  if (null != assumptions) {
    this.modelAssumptions = new VecInt(assumptions);
  } else {
    this.modelAssumptions = new VecInt(new int[0]);
  }

  if (null != clauses) {
    this.hasClauses = true;
    this.featureClauses = clauses;
    this.featureSolver = SolverFactory.newDefault();
    this.featureSolver.newVar(clauses.getNumVars());
    this.featureSolver.setExpectedNumberOfClauses(clauses.size());

    try {
      for (List<Integer> clause : clauses) {
        int[] cint = new int[clause.size()];
        int i = 0;
        for (Integer val : clause) {
          cint[i++] = val;
        }
        this.featureSolver.addClause(new VecInt(cint));
      }
    } catch (ContradictionException e) {
      e.printStackTrace();
      System.exit(1);
    }
  } else {
    this.hasClauses = false;
    this.featureClauses = null;
  }
}

/**
 * Get the checker symbol table.
 *
 * @return The checker symbol table.
 */
public P4Context.SymbolTable getFunctionTable() {
  return this.functionTable;
}

/**
 * A helper function to get the value of a node on the stack, which
 * corresponds to the value of the component of a production.  Unlike
 * bison, this is numbered by the stack, i.e., the closest component
 * to the action has the lowest number, starting with 1.
 *
 * @param subparser The reference to the subparser.
 * @param number The component number, where 1 is the component to the
 * left of the action, and increasing in number while going towards
 * the beginning of the production.
 * @return The node value of the component.
 */
private static Node getNodeAt(Subparser subparser, int component) {
  return (Node) (subparser.stack.get(component).value);
}

private static String getStringAt(Subparser subparser, int component) {
  return ((Syntax) getNodeAt(subparser, component)).toLanguage().getTokenText();
}

/**
 * A helper function to set the type property of the given node.  The
 * given value will be first cast to a Node.
 *
 * @param value A node object.
 * @param type The type to set.
 */
private static void setType(Object value, Type type) {
  ((Node) value).setProperty(Constants.TYPE, type);
}

private static void error(String msg) {
  if (showErrors) {
    System.err.println("error: " + msg);
  }
  /* System.exit(1); */
}

// ---------- Parsing-only context

/**
 * Compute and store the base type indicated by the specifications
 * property of the given node.
 */
public void saveBaseType(Subparser subparser, Node typespec) {
  if (typespec.getProperty(SPECS) == null) {
    if (showErrors) {
      System.err.println("error: no specs available");
    }
    return;
  }
  ((P4Context) subparser.scope).lastSeenType =
    ((Specifiers) typespec.getProperty(SPECS)).getType();
}

/**
 * Return the last seen type.
 */
public Type lastSeenType(Subparser subparser) {
  return ((P4Context) subparser.scope).lastSeenType;
}

private static class Binding {
  public Language ident;
  public Type type;

  public Binding(Language ident, Type type) {
    this.ident = ident;
    this.type = type;
  }
}

private boolean findToken(Object n, P4Tag tag) {
  if (n instanceof Language && ((Language) n).tag() == tag) {
    return true;
  } else if (n instanceof Syntax) {
    return ((Syntax) n).getTokenText().equals(tag.getText());
  } else if (n instanceof Node) {
    boolean b = false;
    for (Object o : ((Node) n)) {
      b |= findToken(o, tag);
      if (b) return true;
    }
    return false;
  } else if (n instanceof PresenceCondition) {
    // ignore
    return false;
  } else {
    System.err.println(n.getClass().getSimpleName());
    return false;
  }
}

public void bindFunDef(Subparser subparser, Node typespec, Node declarator) {
  if (getident(declarator).equals("ERR_PTR")) {
    System.err.println(typespec);
    System.err.println(declarator);
  }

  bindIdent(subparser, typespec, declarator, STField.GLOBAL_FUNDEF);
}

public void bindIdent(Subparser subparser, Node typespec, Node declarator) {
   bindIdent(subparser, typespec, declarator, null, false);
}


/** Another overloaded function for bindIdent to explicity specify it's a TYPDEF value
 * 
 * Cases like typeParameterList don't have a unique preceding value to identify
 * the value as a typedef value. So can use this overloaded function to explicity
 * specify that the value is a typedef.
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, boolean typeVar) {
   bindIdent(subparser, typespec, declarator, null, typeVar);
}

/** Overloaded function with original parameters
 *
 * Original bindIdent (from cparser.y) function is modified with a new parameter,
 * this functions overloads the modified function to behave like how it is in cparser
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, STField alsoSet) {
  bindIdent(subparser, typespec, declarator, alsoSet, false);
}

/** typespec might be null for declarations and definitions without a
 * type spec; alsoSet is used to set another symbol table bit and
 * might be null.
 */
public void bindIdent(Subparser subparser, Node typespec, Node declarator, STField alsoSet, boolean typeVar) {
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // TODO need to hoist conditionals from typespec and declarator
  // around entire declaration by combining with each other

  // TODO causing an infinite loop on 3.12 init/main.c
  /* if (typespec.getProperty(SPECS) == null) { */
  /*   System.err.println("error: no specs available"); */
  /* } else { */
  /*   Type baseType = ((Specifiers) typespec.getProperty(SPECS)).getType(); */
  /*   Binding binding = grokdeclarator(declarator, baseType); */
  /*   Type type = binding.type; */
  /*   Language ident = binding.ident; */

  /*   System.err.println(ident + " = " + type); */
  /* } */

  // TODO replace old-style typedef checking by using specs above
  Language ident = getident(declarator);


  // Check whether the declaration is a typedef.  This assumes that
  // the typedef keyword is the first token of the declaration.
  boolean typedef = false;

  if (null != typespec) {
    Object a = typespec;
    while (true) {
      if ( ! (a instanceof Syntax)) {
        Node n = (Node) a;
        if (n.hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
          // When it's a conditional node, the first child is a
          // presence condition, the second is the first AST child.
          a = n.get(1);
        } else {
          a = n.get(0);
        }
      } else if (a instanceof Pair) {
        a = ((Pair) a).head();
      } else {
        break;
      }
    }
    Language t = (Language) a;
    if (P4Tag.TYPEDEF == t.tag() || P4Tag.STRUCT == t.tag() || P4Tag.CONTROL == t.tag() || 
        P4Tag.PACKAGE == t.tag() || P4Tag.EXTERN == t.tag() || P4Tag.HEADER == t.tag() ||
        P4Tag.ENUM == t.tag() || P4Tag.PARSER == t.tag() || P4Tag.HEADER_UNION == t.tag() ||
        P4Tag.TYPE == t.tag()) {
      // Bind a typedef name.
      typedef = true;

      if (languageStatistics) {
        if (typedef) {
          Location location = subparser.lookahead.token.syntax.getLocation();
          System.err.println(String.format("typedef %s %s", ident, location));
        }
      }
    } else {
      // Binding a variable name.
      typedef = false;
    }
  }

  if (showErrors) {
    System.err.println("bind: " + ident.getTokenText() + " " + typedef);
  }
  if (debug) {
    System.err.println("def: " + ident.getTokenText() + " " + alsoSet);
  }
  // System.err.println("Setting variable: " + ident.getTokenText() + " to type: " + ((typedef || typeVar) ? "TYPDEF" : "IDENT"));
  STField field = (typedef || typeVar) ? STField.TYPEDEF : STField.IDENT;
  scope.getSymbolTable().setbool(ident.getTokenText(), field, true, presenceCondition);
  if (null != alsoSet) {
    scope.getSymbolTable().setbool(ident.getTokenText(), alsoSet, true, presenceCondition);
  }
  /* if (typedef) { */
  /*   scope.getSymbolTable().setbool(ident.getTokenText(), STField.TYPEDEF, true, presenceCondition); */
  /* } else { */
  /*   scope.getSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition); */
  /* } */
  /* scope.bind(ident.getTokenText(), typedef, presenceCondition); */
}

private static Binding grokdeclarator(Node declarator, Type type) {
  Language ident = null;
  
  while (null != declarator) {
    if (declarator.getName().equals("SimpleDeclarator")) {
      ident = ((Syntax) declarator.get(0)).toLanguage();
      declarator = null;
      
    } else if (declarator.getName().equals("ParenIdentifierDeclarator")) {
      Node parenIdentDecl = null;

      switch (declarator.size()) {
      case 3:
      parenIdentDecl = (Node) declarator.get(1);
        break;
      default:
      error("unexpected grammar structure for " + declarator.getName());
        break;
      }
      declarator = parenIdentDecl;
      
    } else if (declarator.getName().equals("UnaryIdentifierDeclarator")) {
      Node typeQual;
      Node identDecl;
      switch (declarator.size()) {
      case 2:
      typeQual = null;
        identDecl = (Node) declarator.get(1);
        break;
      case 3:
      typeQual = (Node) declarator.get(1);
        identDecl = (Node) declarator.get(2);
        break;
      default:
      typeQual = null;
        identDecl = null;
        error("unexpected grammar structure for " + declarator.getName());
        break;
      }
      
      if (null != typeQual) {
        Specifiers specs = (Specifiers) typeQual.getProperty(SPECS);
        type = specs.annotateBase(new PointerT(type).annotate());
      } else {
        type = new PointerT(type);
      }

      declarator = identDecl;
      
    } else if (declarator.getName().equals("ArrayDeclarator")) {
      Node parenIdentDecl = (Node) declarator.get(0);
      Node arrayAbsDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(arrayAbsDecl, type);
      declarator = parenIdentDecl;
      
    } else if (declarator.getName().equals("PostfixIdentifierDeclarator")) {
      Node unaryIdentDecl = (Node) declarator.get(0);
      Node postfixAbsDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(postfixAbsDecl, type);
      declarator = unaryIdentDecl;

    } else if (declarator.getName().equals("FunctionDeclarator")) {
      Node parenIdentDecl = (Node) declarator.get(0);
      Node postfixFuncDecl = (Node) declarator.get(1);

      type = grokabsdeclarator(postfixFuncDecl, type);
      declarator = parenIdentDecl;

    } else {
      if (debug) {
        System.err.println("TODO support declarator " + declarator.getName());
      }
      declarator = null;
    }
  }

  return new Binding(ident, type);
}

private static Type grokabsdeclarator(Node absdeclarator, Type type) {
  if (absdeclarator.getName().equals("ArrayAbstractDeclarator")) {
    while (null != absdeclarator) {
      Node arraySize = null;
      switch (absdeclarator.size()) {
      case 0:
      arraySize = null;
        absdeclarator = null;
        break;
      case 1:
      arraySize = (Node) absdeclarator.get(0);
        absdeclarator = null;
        break;
      case 2:
      arraySize = (Node) absdeclarator.get(1);
        absdeclarator = (Node) absdeclarator.get(0);
        break;
      default:
      error("unexpected grammar structure for " + absdeclarator.getName());
      }
      type = new ArrayT(type);
    }
      
  } else if (absdeclarator.getName().equals("PostfixingFunctionDeclarator")) {
    Node parms = null;
    switch (absdeclarator.size()) {
    case 1:
    parms = (Node) absdeclarator.get(0);
      break;
    default:
    error("unexpected grammar structure for " + absdeclarator.getName());
      break;
    }

    FunctionT function = getParameterTypes(parms);

    function.setResult(type);
    type = function;

  } else {
    if (debug) {
      System.err.println("TODO support absdeclarator " + absdeclarator.getName());
    }
  }
  
  return type;
}

private static FunctionT getParameterTypes(Node parms) {
  // TODO flesh this out and do type checking
  boolean varArgs = false;
  ArrayList<Type> types = new ArrayList<Type>();

  if (parms != null && parms.size() > 0) {
    parms = (Node) parms.get(0);
    /* System.err.println(parms); */
    switch (parms.size()) {
    case 2:
    varArgs = true;
      // fall through
    case 1:
    parms = (Node) parms.get(0);
      break;
    default:
    error("unexpected grammar structure for " + parms.getName());
      break;
    }
    // parms is now a list node containing ParameterDeclaration elements
    if (parms.getName().equals("ParameterList")) {
      for (Object o : parms) {
        GNode n = (GNode) o;
        if (n.getName().equals("Conditional")) {
          boolean isCond = true;
          for (Object o_parm : n) {
            if (isCond) {
              // TODO get presence condition
            } else {
              GNode parm = (GNode) o_parm;
              Node typespec = (Node) parm.get(0);
              // TODO remove once specs are done
              if (typespec.getProperty(SPECS) == null) continue;
              Type baseType = ((Specifiers) typespec.getProperty(SPECS)).getType();
              if (parm.size() > 1) {
                Node declarator = (Node) parm.get(1);
                if (parm.getName().equals("ParameterIdentifierDeclaration")) {
                  Binding binding = grokdeclarator(declarator, baseType);
                  Language ident = binding.ident;
                  Type type = binding.type;
                  String name = binding.ident.getTokenText();
                  types.add(VariableT.newParam(type, name));

                } else if (parm.getName().equals("ParameterAbstractDeclaration")) {
                  Type type = grokabsdeclarator(declarator, baseType);
                  types.add(type);
                } else {
                  if (showErrors) {
                    System.err.println("unsupported parameter declaration " + parm.getName());
                  }
                }
              } else {
                types.add(baseType);
              }
            }
            isCond = isCond ? false : true;
          }
        } else {
          if (showErrors) {
            System.err.println("parameter is no conditional");
          }
        }
      }
    } else {
      if (showErrors) {
        System.err.println("unexpected parameter list node");
      }
    }
  }

  FunctionT function = new FunctionT(null, types, varArgs);
  function.addAttribute(Constants.ATT_STYLE_NEW);
  return function;
}

public void BindVar(Subparser subparser) {
  StackFrame stack = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // Get the identifier in the declarator.
  Object b = stack.get(1).value;
  Language<?> ident = getident(b);

  // Bind variable name.
  scope.getSymbolTable().setbool(ident.getTokenText(), STField.IDENT, true, presenceCondition);
  /* scope.bind(ident.getTokenText(), false, presenceCondition); */
}

public void BindEnum(Subparser subparser) {
  StackFrame stack  = subparser.stack;
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
  P4Context scope = (P4Context) subparser.scope;

  // Get the identifier in the declarator.  The identifier must
  // occur after an IdentifierOrTypedefName token.
  Object b = stack.get(1).value;
  String ident = getident(b).getTokenText();

  // Bind variable name.
  scope.getSymbolTable().setbool(ident, STField.IDENT, true, presenceCondition);
  /* scope.bind(ident, false, presenceCondition); */
}

public void useIdent(Subparser subparser, Node ident) {
  P4Context scope = (P4Context) subparser.scope;
  String name = ident.getTokenText();

  if (debug) {
    System.err.println("use: " + name);
  }
  if (enableCheckers) {
    PresenceCondition identPresenceCond = scope.symbolPresenceCond(name, STField.IDENT);
    if (null != identPresenceCond && ! identPresenceCond.isFalse()) {
      PresenceCondition not = identPresenceCond.not();
      PresenceCondition andnot = subparser.getPresenceCondition().and(not);
      /* not.delRef(); */
      if (! andnot.isFalse()) {
        boolean satWithKconfig = true;
        boolean contradiction = false;
        int[] model = null;
        // check andnot against kconfig feature model
        if (this.hasClauses) {
          // use double negation to get andnot in cnf form
          PresenceCondition notandnot = andnot.not();
          /* System.err.println(notandnot); */
          List allsat = (List) notandnot.getBDD().allsat();
          ArrayList<ArrayList<Integer>> bugClauses =
            new ArrayList<ArrayList<Integer>>();
      
          for (Object o : allsat) {        
            byte[] sat = (byte[]) o;
            ArrayList<Integer> clause = new ArrayList<Integer>();
            for (int i = 0; i < sat.length; i++) {
              // convert to solver's varnum
              // look up i in variable manager
              // if varname exists in clauses, then add to clause
              int sign = 1;
              
              switch (sat[i]) {
              case 1:
              // negate again
                sign = -1;
              case 0:
              String varname = notandnot.presenceConditionManager().getVariableManager().getName(i);
                if (varname.startsWith("(defined ")) {
                  varname = varname.substring(9, varname.length() - 1);
                  /* System.err.println(varname); */
                  if (this.featureClauses.getVarmap().containsKey(varname)) {
                    int var = this.featureClauses.getVarmap().get(varname);
                    var = sign * var;
                    clause.add(var);
                  }
                }
                break;
              }
            }
            if (clause.size() > 0) {
              /* System.err.println(clause); */
              bugClauses.add(clause);
            }
          }

          // add extra constraints
          for (String extraConstraint : extraConstraints) {
            this.featureClauses.addClauses(extraConstraint);
          }
          // remove them to avoid adding them again the next check
          extraConstraints.clear();

          try {
            ISolver featureSolver = SolverFactory.newDefault();
            featureSolver.newVar(this.featureClauses.getNumVars());
            /* featureSolver.setExpectedNumberOfClauses(this.featureClauses.size() + bugClauses.size()); */

            for (List<Integer> clause : this.featureClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              featureSolver.addClause(new VecInt(cint));
            }

            for (List<Integer> clause : bugClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              IConstr curConstr =
                featureSolver.addClause(new VecInt(cint));
            }

            ISolver bugSolver = SolverFactory.newDefault();
            bugSolver.newVar(this.featureClauses.getNumVars());
            bugSolver.setExpectedNumberOfClauses(bugClauses.size());

            for (List<Integer> clause : bugClauses) {
              int[] cint = new int[clause.size()];
              int i = 0;
              for (Integer val : clause) {
                cint[i++] = val;
              }
              IConstr curConstr =
                bugSolver.addClause(new VecInt(cint));
            }

            IProblem simpleProblem = new ModelIterator(bugSolver);
            boolean satWithoutKconfig = simpleProblem.isSatisfiable();
            
            /* IProblem problem = featureSolver; */
            IProblem problem = new ModelIterator(featureSolver);
            if (problem.isSatisfiable(modelAssumptions)) {
              satWithKconfig = true;
              if (debug) {
                System.err.println("computing model");
              }
              model = problem.model();
            } else {
              satWithKconfig = false;
              if (satWithoutKconfig) {
                System.err.print("invalid config invalidated by kconfig ");
              } else {
                System.err.print("invalid config invalidated by bug clauses alone ");
              }
              System.err.println(name + " at " + ident.getLocation());
            }
          } catch (ContradictionException e) {
            contradiction = true;
          } catch (TimeoutException e) {
            e.printStackTrace();
            /* System.exit(1); */
          }
          notandnot.delRef();
        }
        if (contradiction) {
          System.err.print("invalid config invalidated by contradiction " + name + " at " + ident.getLocation());
        } else if (satWithKconfig) {
          /* PresenceCondition sat = andnot.satOne(); */
          if (null != scope.symbolPresenceCond(name, STField.GLOBAL_FUNDEF) || null != scope.symbolPresenceCond(name, STField.STATIC_FUNDEF)) {
            System.err.println("found for function def");
          }
          System.err.println("found invalid configuration on "
                             + name + " at " + ident.getLocation());
          /* System.err.println("config " + andnot); */
          /* System.err.println("identPresenceCond: " + identPresenceCond); */
          /* /\* System.err.println("undefined under " + not); *\/ */
          /* /\* System.err.println("used under      " + subparser.getPresenceCondition()); *\/ */
          /* if (this.showExample) { */
          if (true) {
            if (null != model) {
              System.err.print("model: ");
              String delim = "[";
              for (int i = 0; i < model.length; i++) {
                if (model[i] > 0) {
                  System.err.print(delim + featureClauses.getVarName(model[i]));
                  delim = ",";
                }
              }
              System.err.println("]");
            }
          }
          /* sat.delRef(); */
        }
      } else {
        if (debug) {
          System.err.println("valid function call " + name + " at " + ident.getLocation());
          /* System.err.println("not: " + not); */
          /* System.err.println("subparser.getPresenceCondition() " + subparser.getPresenceCondition()); */
        }
      }
      not.delRef();
      andnot.delRef();

      /* PresenceCondition and = subparser.getPresenceCondition().and(identPresenceCond); */
      /* if (and.isFalse()) { */
      /*   System.err.println("found infeasible configuration on " + name + " at " + ident.getLocation() + " defined in " + identPresenceCond); */
      /* } */
      /* and.delRef(); */

      // update configurations the identifier is used in
      scope.getSymbolTable().setbool(name, STField.USED, true, subparser.getPresenceCondition());
    } else {
      if (debug) {
        System.err.println("not an identifier in any config " + name + " at " + ident.getLocation());
      }
    }
  }
}

public void callFunction(Subparser subparser, Node fun, Node parms) {
  if (fun.getName().equals("PrimaryIdentifier") && enableFunctionAnalysis) {
    /* P4Context scope = (P4Context) subparser.scope; */
    /* String name = ((Language<?>) fun.get(0)).getTokenText(); */
    /* scope.getSymbolTable().setbool(name, STField.FUNCALL, true, subparser.getPresenceCondition()); */
    String name = ((Language<?>) fun.get(0)).getTokenText();
    functionTable.setbool(name, STField.FUNCALL, true, subparser.getPresenceCondition());
    return;
  }

  // TODO do later
  if (true) {
    return;
  }
  
  String name = ((Syntax) fun.get(0)).getTokenText();
  P4Context scope = (P4Context) subparser.scope;

  if (debug) {
    System.err.println("function call: " + name);
  }
  if (enableCheckers) {
    PresenceCondition funPresenceCond = scope.symbolPresenceCond(name, STField.GLOBAL_FUNDEF).or(scope.symbolPresenceCond(name, STField.STATIC_FUNDEF));
    if (null != funPresenceCond && ! funPresenceCond.isFalse()) {
      PresenceCondition not = funPresenceCond.not();
      PresenceCondition andnot = subparser.getPresenceCondition().and(not);
      not.delRef();
      if (! andnot.isFalse()) {
        /* PresenceCondition sat = andnot.satOne(); */
        /* System.err.println("found invalid configuration on function call " + name + " at " + fun.getLocation() + " config " + sat);        sat.delRef(); */
      }
      andnot.delRef();

      PresenceCondition and = subparser.getPresenceCondition().and(funPresenceCond);
      if (and.isFalse()) {
        System.err.println("found infeasible configuration on function call " + name + " at " + fun.getLocation() + " defined in " + funPresenceCond);
      }
      and.delRef();

      // update configurations the function is used in
      scope.getSymbolTable().setbool(name, STField.USED, true, subparser.getPresenceCondition());
    } else {
      if (debug) {
        System.err.println("checker error: " + name + " not a function in any configuration");
      }
    }
    funPresenceCond.delRef();
  }
}

public void EnterScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope = ((P4Context) subparser.scope).enterScope(presenceCondition);
}

public void ExitScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope = ((P4Context) subparser.scope).exitScope(presenceCondition);
}

public void ExitReentrantScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).exitReentrantScope(presenceCondition);
}

public void ReenterScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).reenterScope(presenceCondition);
}

public void KillReentrantScope(Subparser subparser) {
  PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();

  subparser.scope
    = ((P4Context) subparser.scope).killReentrantScope(presenceCondition);
}

/**
 * Find the identifier or typedef name in a declarator.  Assume
 * the first identifier in the subtree is the var or typedef name.
 *
 * @param o The semantic value.
 * @return The first identifier in the subtree or null if there is
 * none.
 */
private static Language getident(Object o) {
  if (o instanceof Language) {
    Language token = ((Language) o);

    if (P4Tag.IDENTIFIER == token.tag() || P4Tag.TYPE_IDENTIFIER == token.tag()) {
      return token;

    } else {
      return null;
    }

  } else if (o instanceof Pair) {
    Pair<?> b = (Pair<?>) o;

    while (b != Pair.empty()) {
      Object child = b.head();

      if (null != child) {
        Language ident = getident(child);

        if (null != ident) {
          return ident;
        }
      }

      b = b.tail();
    }

    return null;
  } else if (o instanceof PresenceConditionManager.PresenceCondition) {
    return null;
  } else if (o instanceof Error) {
    return null;
  } else {
    Node b = (Node) o;

    for (int i = 0; i < b.size(); i++) {
      Object child = b.get(i);

      if (null != child) {
        Language ident = getident(child);

        if (null != ident) {
          return ident;
        }
      }
    }

    return null;
  }
}

// ---------- Specifiers

private static String SPECS = "superc.p4parser.Specifiers";

private static class Specifiers {
  /** Presence condition. */
  public PresenceCondition pc;

  /** True if there is a type error. */
  public boolean error;

  /** The type-error message. */
  public String error_message;

  /** The flag for whether a tag reference is a declaration. */
  public boolean refIsDecl;

  /** The type, if any. */
  public Type type;

  /** The storage class attribute, if any. */
  public Attribute storage;

  /** The thread-local attribute, if any. */
  public Attribute threadlocal;

  /** The inline attribute, if any. */
  public Attribute function;

  /** Any other attributes. */
  public List<Attribute> attributes;

  // The internal state for tracking type specifiers.
  public boolean seenSigned;
  public boolean seenUnsigned;
  public boolean seenBool;
  public boolean seenChar;
  public boolean seenShort;
  public boolean seenInt;
  public int     longCount;
  public boolean seenFloat;
  public boolean seenDouble;
  public boolean seenComplex;

  public Specifiers() {
  }

  /* public Specifiers(PresenceCondition pc) { */
  /*   this.pc = pc.addRef(); */
  /* } */

  public Specifiers(PresenceCondition pc, Specifiers s) {
    /* this(pc); */
    this.error = s.error;
    this.error_message = s.error_message;
    this.refIsDecl = s.refIsDecl;
    this.type = s.type;
    this.storage = s.storage;
    this.threadlocal = s.threadlocal;
    this.function = s.function;
    this.attributes = s.attributes;
    this.seenSigned = s.seenSigned;
    this.seenUnsigned = s.seenUnsigned;
    this.seenBool = s.seenBool;
    this.seenChar = s.seenChar;
    this.seenShort = s.seenShort;
    this.seenInt = s.seenInt;
    this.longCount = s.longCount;
    this.seenFloat = s.seenFloat;
    this.seenDouble = s.seenDouble;
    this.seenComplex = s.seenComplex;
  }

  /**
   * Add given specs to this set of specs.  Adds in-place and returns
   * this updated specs object.
   **/
  public Specifiers addSpecs(Specifiers other) {
    if (other.error) {
      this.setError(other.error_message);
      return this;
    }

    if (null != other.type) {
      if (null != this.type) {
        /* System.err.println("1"); */
        this.multipleTypes();
      } else {
        this.type = other.type;
      }
    }

    if (other.seenChar) {
      if (this.hasType()) {
        /* System.err.println("2"); */
        this.multipleTypes();
      } else {
        this.seenChar = true;
      }
    }

    if (other.seenShort) {
      if (this.seenBool || this.seenChar || this.seenShort || (0 < this.longCount) ||
          this.seenFloat || this.seenDouble || this.seenComplex ||
          (null != this.type)) {
        /* System.err.println("3"); */
        this.multipleTypes();
      } else {
        this.seenShort = true;
      }
    }

    if (other.seenInt) {
      if (this.seenBool || this.seenChar || this.seenInt ||
          this.seenFloat || this.seenDouble || this.seenComplex ||
          (null != this.type)) {
        /* System.err.println("4"); */
        this.multipleTypes();
      } else {
        this.seenInt = true;
      }
    }

    for (int i = 0; i < other.longCount; i++) {
      if (this.seenBool || this.seenChar || this.seenShort || (1 < this.longCount) ||
          this.seenFloat ||
          ((this.seenDouble || this.seenComplex) &&
           (0 < this.longCount)) ||
          (null != this.type)) {
        /* System.err.println("5"); */
        this.multipleTypes();
      } else {
        this.longCount++;
      }
    }

    if (other.seenFloat) {
      if (this.seenBool || this.seenChar || this.seenShort || this.seenInt || (0 < this.longCount) ||
          this.seenDouble ||
          (null != this.type)) {
        /* System.err.println("6"); */
        this.multipleTypes();
      } else {
        this.seenFloat = true;
      }
    }

    if (other.seenDouble) {
      if (this.seenBool || this.seenChar || this.seenShort || this.seenInt || (1 < this.longCount) ||
          this.seenFloat ||
          (null != this.type)) {
        /* System.err.println("7"); */
        this.multipleTypes();
      } else {
        this.seenDouble = true;
      }
    }

    if (other.seenSigned) {
      if (this.seenUnsigned) {
        this.seenSigned = true;
        this.setError("both 'signed' and 'unsigned' in declaration specifiers");
      } else if (this.seenSigned) {
        this.setError("duplicate 'signed'");
      } else {
        this.seenSigned = true;
      }
    }

    if (other.seenUnsigned) {
      if (this.seenSigned) {
        this.seenUnsigned = true;
        this.setError("both 'signed' and 'unsigned' in declaration specifiers");
      } else if (this.seenUnsigned) {
        this.setError("duplicate 'unsigned'");
      } else {
        this.seenUnsigned = true;
      }
    }

    if (other.seenBool) {
      if (this.hasType()) {
        /* System.err.println("8"); */
        this.multipleTypes();
      } else {
        this.seenBool = true;
      }
    }

    if (null != other.storage) {
      if (null == this.storage) {
        this.storage = other.storage;
      } else if (this.storage.equals(other.storage)) {
        this.setError("duplicate storage class");
      } else {
        this.setError("multiple storage classes in declaration specifiers");
      }
    }

    return this;
  }

  /**
   * Annotate the specified base type.  This method annotates the
   * specified type with all attributes besides the storage class,
   * thread-local specifier, and function specifier attributes.
   *
   * @param base The base type.
   * @return The annnotated base type.
   */
  public Type annotateBase(Type base) {
    return (null != attributes)? base.attribute(attributes) : base;
  }

  /**
   * Get the resulting type.
   */
  public Type getType() {
    Type type;
    if (seenBool) {
      type = BooleanT.TYPE;
    } else if (seenChar) {
      if (seenUnsigned) {
        type = NumberT.U_CHAR;
      } else if (seenSigned) {
        type = NumberT.S_CHAR;
      } else {
        type = NumberT.CHAR;
      }
    } else if (seenShort) {
      if (seenUnsigned) {
        type = NumberT.U_SHORT;
      } else {
        type = NumberT.SHORT;
      }
    } else if (seenFloat) {
      if (seenComplex) {
        type = NumberT.FLOAT_COMPLEX;
      } else {
        type = NumberT.FLOAT;
      }
    } else if (seenDouble) {
      if (0 < longCount) {
        if (seenComplex) {
          type = NumberT.LONG_DOUBLE_COMPLEX;
        } else {
          type = NumberT.LONG_DOUBLE;
        }
      } else {
        if (seenComplex) {
          type = NumberT.DOUBLE_COMPLEX;
        } else {
          type = NumberT.DOUBLE;
        }
      }
    } else if (1 == longCount) {
      if (seenUnsigned) {
        type = NumberT.U_LONG;
      } else {
        type = NumberT.LONG;
      }
    } else if (1 < longCount) {
      if (seenUnsigned) {
        type = NumberT.U_LONG_LONG;
      } else {
        type = NumberT.LONG_LONG;
      }
    } else if (seenUnsigned) {
      type = NumberT.U_INT;
    } else if (seenSigned) {
      type = NumberT.S_INT;
    } else if (seenInt) {
      type = NumberT.INT;
    } else {
      type = C.IMPLICIT;
    }

    // Annotate the type.
    if ((! type.hasError()) && (null != attributes)) {
      type = type.annotate().attribute(attributes);
    }

    return type;
  }

  /** Test for previous type. */
  protected boolean hasType() {
    return
      (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
       seenFloat || seenDouble || seenComplex ||
       (null != type));
  }

  /** Report error indicating multiple types. */
  protected void multipleTypes() {
    this.setError("multiple data types in declaration specifiers");
  }

  /** Add the specified attribute. */
  protected void add(Attribute att) {
    if (null == attributes) {
      attributes = new ArrayList<Attribute>();
      attributes.add(att);
    } else if (! attributes.contains(att)) {
      attributes.add(att);
    }
  }

  public void setError(String msg) {
    this.error = true;
    this.error_message = msg;
    type = ErrorT.TYPE;
    if (showErrors) {  // showErrors is true
      System.err.println("error in specifiers: " + msg);
    }
  }

  // Get specs.  Gets list of specifiers, checking for type errors.
  // Also need to hoist conditionals around complete type
  // specifiers.  Is it possible to make a hoisting tree-walker?
  // Walk tree, when encountering conditional, fork the spec state
  // and walk both.  No need for merge, since there are two
  // different declarations.
}

/**
 * A helper function to get the specifiers of the value of a component
 * node from the stack.
 *
 * @param subparser The reference to the subparser.
 * @param number The component number.
 * @return The specifiers for the component.
 */
private static Specifiers getSpecsAt(Subparser subparser, int component) {
  Node n = getNodeAt(subparser, component);

  if (n.hasProperty(SPECS)) {
    return (Specifiers) n.getProperty(SPECS);
  } else {
    Specifiers specs = new Specifiers();

    n.setProperty(SPECS, specs);
    return specs;
  }
}

private static void updateSpecs(Subparser subparser,
                                Specifiers new_specs,
                                Object value) {
  updateSpecs(subparser, null, new_specs, value);
}

private static void updateSpecs(Subparser subparser,
                                Specifiers specs,
                                Specifiers new_specs,
                                Object value) {
  if (null == specs) {
    specs = new_specs;
  } else {
    specs = specs.addSpecs(new_specs);
  }

  ((P4Context) subparser.scope).lastSeenType = specs.getType();
  ((Node) value).setProperty(SPECS, specs);
}

private static Specifiers makeUnionSpec(Subparser subparser,
                                        Node tagNode,
                                        Node membersNode,
                                        Node attrsNode) {
  Specifiers specs = new Specifiers();

  return specs;
}

private static Specifiers makeStructSpec(Subparser subparser,
                                         Node tagNode,
                                         Node membersNode,
                                         Node attrsNode) {
  String tag;
  String name;
  if (null == tagNode) {
    // TODO struct tag creation
    /* tag = table.freshName("tag"); */
    tag = "tag(untagged)";
    name = tag;
  } else {
    // TODO check for conditional here
    /* tag = ((Syntax) tagNode.get(0)).toLanguage().getTokenText(); */
    /* name = SymbolTable.toTagName(tag); */
  }

  // TODO remove this once above code is complete
  tag = "tag(untagged)";
  name = tag;

  Type type;

  // TODO struct tag is defined
  /* if (table.current().isDefinedLocally(name)) { */
  /*   final Type t = (Type)table.current().lookupLocally(name); */

  /*   if (! t.isStruct()) { */
  /*     runtime.error("'" + tag + "' defined as wrong kind of tag", n); */
  /*     reportPreviousTag(t); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else if (null != t.toTagged().getMembers()) { */
  /*     runtime.error("redefinition of 'struct " + tag + "'", n); */
  /*     reportPreviousTag(t); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else if (t.hasAttribute(Constants.ATT_DEFINED)) { */
  /*     runtime.error("nested redefinition of 'struct " + tag + "'", n); */
  /*     type = ErrorT.TYPE; */
  /*     return; */

  /*   } else { */
  /*     type = t; */
  /*   } */
  /* } else { */
    // TODO checkNotParameter
    /* checkNotParameter(n, "struct"); */
 
    // Declare the struct so that members can reference it.
    type = new StructT(tag);
    /* table.current().define(name, type); */
  /* } */

  // TODO location
  /* // Update the location. */
  /* type.setLocation(n); */

  // TODO struct attributes
  /* // Update the GCC attributes. */
  /* for (Attribute a : toAttributeList(n.getGeneric(0))) { */
  /*   type.addAttribute(a); */
  /* } */
  /* for (Attribute a : toAttributeList(n.getGeneric(3))) { */
  /*   type.addAttribute(a); */
  /* } */

  // Process the members and update the struct declaration.  Use
  // defined attribute to protect against nested redefinition.
  type.addAttribute(Constants.ATT_DEFINED);
  // TODO struct members
  /* List<VariableT> members = processMembers(n.getGeneric(2), true); */
  List<VariableT> members = null;
  type.toStruct().setMembers(members);
  type.removeAttribute(Constants.ATT_DEFINED);

  Specifiers specs = new Specifiers();
  specs.type = type;

  return specs;
}

/**
 * Check that the tag declaration is not located within a
 * parameter list.  If the declaration is located within a
 * parameter list, this method prints the appropriate warning.
 *
 * @param node The node.
 * @param kind The kind of tag.
 */
private void checkNotParameter(Node node, String kind) {
  // TODO checkNotParameter implementation
  /* if (TMP_SCOPE.equals(table.current().getName())) { */
  /*   final String tag = node.getString(1); */
  /*   final String msg; */
  /*   if (null == tag) { */
  /*     msg = "anonymous " + kind + " declared inside parameter list"; */
  /*   } else { */
  /*     msg = "'" + kind + " " + tag + "' declared inside parameter list"; */
  /*   } */

  /*   runtime.warning(msg, node); */
  /* } */
}

// ---------- Declarators

/* private static String DECL = "superc.p4parser.Declarator"; */

/* private static String NAME = "superc.p4parser.Name"; */

/* private static void setDecl(Object n, Type type) { */
/*   ((Node) n).setProperty(DECL, type); */
/* } */

/* private static Type getDecl(Object n) { */
/*   return ((Type) ((Node) n).getProperty(DECL)); */
/* } */

/* private static void setName(Object n, String name) { */
/*   ((Node) n).setProperty(NAME, name); */
/* } */

/* private static String getName(Object n) { */
/*   return ((String) ((Node) n).getProperty(NAME)); */
/* } */

/* private static void setDecl(Object n, Type type, String name) { */
/*   setDecl(n, type); */
/*   setName(n, name); */
/* } */

/* private static void copyDecl(Subparser subparser, Object value, int from) { */
/*   setDecl(value, (Type) (getNodeAt(subparser, from).getProperty(DECL))); */
/* } */

/* private static void copyName(Subparser subparser, Object value, int from) { */
/*   setName(value, (String) (getNodeAt(subparser, from).getProperty(NAME))); */
/* } */

/* private static void copyDeclName(Subparser subparser, Object value, int from){ */
/*   copyDecl(subparser, value, from); */
/*   copyName(subparser, value, from); */
/* } */
