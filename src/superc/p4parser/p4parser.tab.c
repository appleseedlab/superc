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
#define YYLAST   3953

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  169
/* YYNRULES -- Number of rules.  */
#define YYNRULES  506
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  905

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
     314,   315,   319,   320,   322,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371,
     372,   374,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   417,   418,   422,   426,   427,   427,   431,   432,   436,
     437,   441,   442,   443,   444,   448,   449,   448,   457,   459,
     461,   463,   468,   473,   474,   478,   479,   483,   484,   488,
     495,   495,   494,   501,   502,   506,   507,   508,   509,   514,
     515,   513,   523,   524,   528,   528,   534,   535,   539,   540,
     541,   542,   543,   544,   545,   549,   549,   554,   555,   559,
     560,   564,   569,   570,   574,   579,   580,   584,   586,   590,
     591,   596,   597,   598,   599,   603,   604,   605,   606,   607,
     611,   614,   617,   626,   628,   625,   634,   635,   633,   643,
     644,   648,   649,   650,   651,   652,   656,   663,   667,   668,
     668,   662,   669,   670,   674,   678,   679,   684,   683,   689,
     690,   691,   691,   696,   702,   703,   704,   705,   706,   710,
     711,   715,   716,   720,   724,   728,   729,   733,   737,   738,
     739,   740,   741,   742,   744,   746,   749,   751,   753,   758,
     759,   760,   765,   766,   770,   770,   770,   774,   781,   787,
     788,   790,   791,   795,   796,   797,   801,   802,   803,   809,
     810,   814,   815,   816,   817,   818,   822,   823,   824,   825,
     830,   831,   829,   841,   843,   840,   852,   854,   851,   861,
     862,   866,   871,   870,   876,   876,   884,   885,   889,   893,
     898,   904,   905,   909,   913,   917,   921,   931,   933,   938,
     940,   945,   949,   953,   954,   958,   960,   966,   970,   971,
     972,   973,   974,   975,   976,   977,   981,   981,   986,   987,
     991,   995,   996,  1000,  1001,  1005,  1006,  1010,  1011,  1012,
    1013,  1020,  1020,  1019,  1025,  1026,  1030,  1032,  1034,  1036,
    1041,  1042,  1046,  1051,  1052,  1057,  1061,  1063,  1068,  1073,
    1074,  1080,  1080,  1090,  1094,  1101,  1106,  1107,  1111,  1117,
    1117,  1121,  1122,  1126,  1127,  1131,  1132,  1133,  1137,  1138,
    1139,  1143,  1144,  1148,  1148,  1152,  1153,  1154,  1155,  1159,
    1160,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,  1171,
    1172,  1173,  1174,  1175,  1176,  1177,  1178,  1179,  1181,  1183,
    1184,  1185,  1186,  1187,  1188,  1189,  1190,  1191,  1192,  1194,
    1195,  1196,  1198,  1200,  1201,  1202,  1203,  1204,  1205,  1206,
    1207,  1208,  1209,  1211,  1212,  1214,  1216,  1218,  1222,  1223,
    1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,  1233,
    1234,  1235,  1236,  1238,  1240,  1241,  1242,  1243,  1244,  1245,
    1246,  1247,  1248,  1249,  1251,  1252,  1253,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,  1267,  1268,
    1270,  1272,  1274,  1297,  1297,  1298,  1298
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
  "annotation", "structuredAnnotationBody", "annotationBody",
  "annotationToken", "kvList", "kvPair", "parameterList", "$@1",
  "nonEmptyParameterList", "parameter", "direction",
  "packageTypeDeclaration", "$@2", "$@3", "instantiation",
  "objInitializer", "objDeclarations", "objDeclaration",
  "optConstructorParameters", "dotPrefix", "parserDeclaration", "$@4",
  "$@5", "parserLocalElements", "parserLocalElement",
  "parserTypeDeclaration", "$@6", "$@7", "parserStates", "parserState",
  "$@8", "parserStatements", "parserStatement", "parserBlockStatement",
  "$@9", "transitionStatement", "stateExpression", "selectExpression",
  "selectCaseList", "selectCase", "keysetExpression",
  "tupleKeysetExpression", "simpleExpressionList",
  "reducedSimpleKeysetExpression", "simpleKeysetExpression",
  "valueSetDeclaration", "controlDeclaration", "$@10", "$@11",
  "controlTypeDeclaration", "$@12", "$@13", "controlLocalDeclarations",
  "controlLocalDeclaration", "controlBody", "externDeclaration", "$@14",
  "$@15", "$@16", "$@17", "externFunctionDeclaration", "methodPrototypes",
  "functionPrototype", "$@18", "methodPrototype", "$@19",
  "constructorMethodPrototype", "typeRef", "namedType", "prefixedType",
  "typeName", "tupleType", "headerStackType", "specializedType",
  "baseType", "typeOrVoid", "optTypeParameters", "typeParameters", "$@20",
  "$@21", "typeParameterList", "typeArg", "typeArgumentList",
  "realTypeArg", "realTypeArgumentList", "typeDeclaration",
  "derivedTypeDeclaration", "headerTypeDeclaration", "$@22", "$@23",
  "structTypeDeclaration", "$@24", "$@25", "headerUnionDeclaration",
  "$@26", "$@27", "structFieldList", "structField", "enumDeclaration",
  "$@28", "$@29", "specifiedIdentifierList", "specifiedIdentifier",
  "errorDeclaration", "matchKindDeclaration", "identifierList",
  "typedefDeclaration", "assignmentOrMethodCallStatement",
  "methodCallStatements", "emptyStatement", "exitStatement",
  "returnStatement", "conditionalStatement", "directApplication",
  "statement", "blockStatement", "$@30", "statOrDeclList",
  "switchStatement", "switchCases", "switchCase", "switchLabel",
  "statementOrDeclaration", "tableDeclaration", "$@31", "$@32",
  "tablePropertyList", "tableProperty", "keyElementList", "keyElement",
  "actionList", "action", "actionRef", "entry", "entriesList",
  "actionDeclaration", "$@33", "variableDeclaration",
  "constantDeclaration", "optInitializer", "initializer",
  "functionDeclaration", "$@34", "argumentList", "nonEmptyArgList",
  "argument", "expressionList", "prefixedNonTypeName", "dot_name", "$@35",
  "lvalue", "lvalueExpression", "expression", "invokingExpression",
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

#define YYPACT_NINF (-815)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-399)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -815,    39,  -815,   765,  -815,  -815,  -815,    24,  -815,   297,
       4,   297,    35,  -815,   297,   297,  -815,  -815,  -815,  -815,
      68,  1443,  -815,   -14,  -815,   -26,  -815,    69,  -815,   123,
    -815,  -815,  -815,    31,  -815,   294,  -815,  -815,    60,  -815,
      24,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,   130,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,   141,  -815,  -815,   -37,    24,   -34,    24,  2396,
     -21,    24,   867,    24,  2482,  2439,    24,    24,  1443,    24,
      24,    24,  1443,  -815,  -815,   156,  -815,  -815,   196,  -815,
     164,  -815,   176,   201,  1416,  2306,  2396,  2306,   297,  -815,
    1859,  -815,  2306,   298,  -815,    77,  2306,   298,   121,  -815,
    -815,  -815,  -815,  -815,   234,  2306,   298,   205,    24,  -815,
      81,  -815,    24,   188,   204,   209,   217,  -815,   297,   297,
      87,   201,    24,    24,  -815,  -815,   297,    24,    24,  1416,
     233,   201,  -815,  -815,   259,  -815,  2306,  2306,  2306,  1908,
    1204,  2306,  -815,  -815,  -815,  -815,   249,  -815,  -815,   270,
     273,   710,   283,   194,  -815,   300,   304,  -815,  3621,  -815,
    -815,  2807,   234,  2844,  -815,  -815,  -815,   288,   321,   311,
    -815,   312,  3621,  1686,  2881,  -815,  -815,  -815,  -815,    24,
    2918,  -815,  -815,  2396,  -815,  2955,  -815,   196,   310,   297,
     324,  -815,   297,  -815,  -815,   329,   330,  -815,  -815,   297,
     297,   332,  -815,  -815,   326,  -815,   157,   325,  -815,  -815,
    -815,  -815,   265,   265,   265,   142,   149,   249,   327,   272,
     183,  2992,   265,    24,  2306,  -815,  1416,  -815,  -815,    24,
    2110,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,
    2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,
     333,  1416,  2306,  2306,  -815,  1047,  -815,  -815,  -815,   336,
      24,  2306,  -815,    24,  2306,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,   298,  -815,   298,  -815,   298,   331,
    2306,  -815,    24,   339,  -815,  -815,  -815,  -815,  -815,  -815,
      24,  -815,  -815,  -815,   867,   201,  1443,   464,  -815,  -815,
    -815,  2306,  -815,  -815,  3621,   341,    24,   291,  -815,  1570,
    1570,  1885,  3765,  3732,  3798,  3798,   402,   402,   402,   402,
     265,   265,   265,  3829,  3891,  3860,  2696,  1570,  2306,   342,
    3029,   402,  -815,  -815,  -815,  -815,   238,  1570,   196,  -815,
     335,  3621,  -815,  3621,  1778,  -815,  -815,  -815,  -815,   337,
    3621,   344,   169,    24,   352,  -815,  -815,   349,   355,  -815,
     296,    24,  -815,   -48,  1443,  -815,  -815,    -4,  -815,  -815,
     338,  -815,  -815,   201,   -28,  -815,  -815,  -815,  -815,  -815,
    -815,   942,   265,  -815,  -815,   367,  -815,  -815,  2306,  1885,
    -815,  2306,  2396,   362,   363,    24,   298,  -815,   201,  -815,
     196,  -815,   356,   199,  -815,  -815,     2,    55,   196,   196,
      59,   367,  -815,   359,    24,   297,   630,   320,   374,  -815,
     368,  -815,  -815,    24,  -815,  -815,  -815,   370,   382,  2159,
     386,  -815,     9,  -815,   710,   224,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
     143,  -815,   383,  3066,  3695,  -815,  1416,  -815,  -815,  -815,
    -815,   369,  2306,  -815,    24,  -815,   867,   395,  -815,   398,
     397,   399,   409,   401,  2306,  -815,   867,   368,  -815,  2306,
     403,   410,   412,  -815,  2306,  -815,  3103,  2306,  -815,   387,
    2306,  1416,  2306,  -815,  -815,  2396,   252,  -815,  -815,   413,
    -815,  -815,  -815,   115,    24,  -815,  -815,  -815,  -815,  -815,
    -815,  3621,   416,   298,   298,   298,   405,  -815,  -815,  -815,
    -815,  3140,  -815,  3177,   417,  2733,   415,  3214,   234,  -815,
    1443,  -815,  -815,  -815,  -815,   821,   425,  -815,  -815,   414,
    -815,   421,   427,   429,  -815,    47,  2530,   436,  1416,  -815,
    2306,   423,  -815,   432,   510,   433,   426,  -815,  -815,  -815,
    1576,  2306,  2306,  2306,   430,   434,   419,   -13,  -815,   438,
     420,  -815,   435,  3251,  -815,  1416,   431,   196,  -815,   168,
      34,  1443,  -815,  -815,   445,    24,  -815,  -815,  -815,  -815,
    -815,  -815,  3288,  3325,  3362,   454,   456,   424,   181,   457,
    -815,  2530,  2208,   447,  -815,   452,  -815,   455,   461,   460,
    -815,  -815,  -815,    24,  -815,    24,    24,    24,  -815,  -815,
     462,  -815,  -815,  -815,  -815,  -815,   469,  -815,  -815,  2306,
    2306,  2306,  -815,  1204,  2306,  -815,  -815,  -815,  -815,   465,
    -815,  -815,  -815,   710,   477,   194,  -815,   459,  3658,  -815,
    -815,   470,   471,  1957,  -815,  -815,   472,   473,   475,   118,
    2257,   494,  2306,   265,   265,   265,   495,  3399,   265,    24,
    -815,  1416,  -815,    -8,  2306,  2306,  2306,  2306,  2306,  2306,
    2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,  2306,
    2306,  2306,  2306,   499,  1416,  2306,  2306,  -815,  1047,  -815,
    -815,    83,  2353,  -815,  -815,  -815,  -815,   880,  -815,  -815,
    -815,  3436,  2008,   490,  2306,  -815,  -815,   501,  -815,  1570,
    1570,  1885,  3765,  3732,  3798,  3798,   402,   402,   402,   402,
     265,   265,   265,  3829,  3891,  3860,  2770,  1570,  2306,   502,
    3473,   402,   238,  1570,   506,  -815,   229,   498,   507,    24,
    1129,  -815,  -815,   505,  -815,  -815,  -815,  1291,  2656,  -815,
     265,  -815,  -815,  2306,  1885,  -815,  2306,   511,  -815,  -815,
    1416,   201,   509,   514,   513,   517,  2616,   880,  -815,  -815,
    2306,  2306,  3510,  3695,  1416,  1365,   529,   525,  -815,  2059,
    2306,  2306,   201,  3621,  3621,  -815,   535,  -815,  -815,   512,
    -815,  -815,   240,  -815,  3547,  3584,   530,  -815,    24,  -815,
    2059,  -815,   532,  -815,  -815
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   159,     6,     0,   258,   260,
     259,   262,     0,   261,     0,     0,   270,   271,   251,     5,
       0,    34,    35,     0,    13,     0,    10,   157,    12,   157,
       8,   232,   389,   269,   253,   245,   248,   247,   246,   244,
       0,    11,   291,   296,   298,   297,   299,    14,    15,     0,
       9,     7,    16,    20,    18,    22,    19,    23,    21,    17,
      25,    24,    37,   503,   504,     0,     0,     0,     0,   283,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,    33,   259,    36,     0,   295,   252,   135,   293,
       0,   294,     0,    33,   453,   453,   283,   453,   272,   292,
     453,    42,   453,     0,   321,     0,   453,     0,     0,   282,
     281,   280,   279,   284,     0,   453,     0,     0,     0,   216,
     251,   312,     0,   271,   227,     0,     0,   269,   272,   272,
       0,    34,     0,     0,   145,   169,   272,     0,     0,   453,
       0,    33,   160,   213,     0,   390,   453,   453,   453,   453,
     453,   453,   397,   413,   414,   415,     0,   412,   411,   416,
       0,     0,     0,   249,   250,     0,   392,   393,   395,   452,
     416,     0,     0,     0,   237,   273,   274,     0,     0,    41,
     131,    40,   399,     0,     0,   505,   506,   263,   319,     0,
       0,   264,   320,     0,   254,     0,   265,   135,     0,   272,
       0,   314,   272,   233,   234,     0,     0,   325,   326,   272,
     272,     0,   323,   324,     0,   158,   144,   136,   137,   163,
     219,   346,   426,   425,   424,     0,     0,   259,     0,   245,
     246,     0,   423,     0,   453,   417,   453,   403,   427,     0,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
       0,   453,   453,   453,   429,   453,   255,   257,   256,     0,
       0,   453,    39,     0,   453,    45,   104,   103,    99,   100,
     102,   101,   106,   108,   107,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,    95,   122,
      96,    42,    38,   123,   124,   130,   125,   126,   127,   128,
     129,   105,    90,    98,    97,    84,    61,    82,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    62,    63,    64,    65,    66,    67,    68,
      76,    69,    70,    71,    73,    72,    74,    75,    77,    78,
      79,    80,    81,    83,    85,    86,    87,    88,    89,    91,
      92,    93,    94,    44,     0,   322,     0,   285,     0,     0,
     453,   217,     0,     0,   228,   300,   306,   146,   170,   303,
       0,   141,   143,   142,     0,    33,    33,    33,   348,   421,
     420,   453,   422,   428,   396,     0,     0,     0,   394,   439,
     440,   437,   449,   450,   443,   444,   433,   434,   435,   436,
     430,   431,   432,   447,   445,   446,     0,   442,   453,     0,
       0,   448,   288,   287,   286,   289,     0,   441,   135,   277,
     275,   133,   132,   400,     0,   266,   267,   268,   381,     0,
     388,     0,     0,     0,     0,   309,   309,     0,     0,   309,
       0,     0,   138,     0,    34,   166,   164,    33,   172,   168,
       0,   167,   165,    33,     0,   224,   220,   223,   222,   225,
     221,    33,   457,   456,   404,     0,   149,   418,   453,   438,
     455,   453,     0,     0,     0,     0,     0,    43,    33,   385,
     135,   313,     0,     0,   316,   229,    33,    33,   135,   135,
      33,     0,   148,   139,     0,     0,     0,     0,     0,   173,
     386,   214,   226,     0,   347,   331,   406,     0,     0,   453,
       0,   401,     0,   360,     0,   245,   338,   327,   341,   344,
     343,   340,   339,   359,   342,   345,   349,   357,   358,   405,
       0,   153,     0,     0,   451,   290,   453,   238,   278,   276,
     382,     0,   453,   315,     0,   235,     0,     0,   310,     0,
       0,     0,     0,     0,   453,   174,     0,   386,   162,   453,
       0,     0,     0,   332,   453,   333,     0,   453,   402,     0,
     453,   453,   453,   407,   408,   283,     0,   151,   419,     0,
     218,   318,   317,    33,     0,   302,   308,   147,   171,   305,
     150,   140,     0,     0,     0,     0,     0,   387,   384,   215,
     361,     0,   334,     0,     0,     0,     0,     0,     0,   152,
       0,   156,   154,   155,   454,     0,     0,   236,   241,     0,
     176,     0,     0,     0,   383,    33,    33,     0,   453,   409,
     453,     0,   328,     0,     0,   251,     0,   231,   242,   311,
      33,   453,   453,   453,     0,     0,    31,    33,   364,     0,
     335,   351,     0,     0,   329,   453,     0,   135,   239,     0,
       0,    34,   177,   183,     0,     0,   178,   180,   184,   179,
     181,   182,     0,     0,     0,     0,     0,    32,     0,     0,
     365,    33,   498,     0,   410,     0,   240,     0,     0,     0,
     188,   190,   185,     0,   175,     0,     0,     0,   373,   370,
       0,    28,    30,    29,    26,    27,     0,   363,   336,   453,
     453,   453,   350,   453,   453,   460,   461,   462,   355,     0,
     459,   458,   463,     0,     0,   249,   352,     0,   356,   497,
     337,     0,     0,   453,   189,   176,     0,     0,     0,    33,
     453,     0,   453,   471,   470,   469,     0,     0,   468,     0,
     464,   453,   472,   354,   453,   453,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   453,   453,   453,   453,
     453,   453,   453,     0,   453,   453,   453,   474,   453,   330,
     243,     0,    33,   212,   211,   210,   367,     0,   374,   366,
     371,     0,   453,     0,   453,   467,   473,     0,   353,   484,
     485,   482,   494,   495,   488,   489,   478,   479,   480,   481,
     475,   476,   477,   492,   490,   491,     0,   487,   453,     0,
       0,   493,     0,   486,     0,   186,     0,     0,   376,     0,
     453,   209,   208,     0,   195,   196,   379,   453,   205,   369,
     502,   501,   465,   453,   483,   500,   453,     0,   192,   375,
     453,    33,   204,   203,     0,     0,   205,     0,   368,   380,
     453,   453,     0,   496,   453,   453,     0,     0,   198,   453,
     453,   453,    33,   206,   207,   466,     0,   191,   193,     0,
     377,   372,     0,   199,   201,   202,     0,   499,     0,   197,
     453,   378,     0,   200,   194
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -815,  -815,  -815,  -815,  -815,    -7,   138,  -815,  -815,    19,
       0,   -19,  -815,   261,  -815,   444,   340,  -187,  -815,  -815,
     212,  -815,  -815,  -815,  -815,  -358,    93,  -815,  -815,   571,
     125,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
     146,  -815,  -141,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -270,  -815,  -815,  -815,  -814,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,   -68,  -815,  -815,  -815,  -815,    16,   -86,
    -815,   262,    42,  -815,   351,    43,  -815,   -29,  -815,  -815,
    -815,  -815,  -185,   -90,  -815,  -177,  -815,   -38,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -151,  -815,  -815,
    -815,  -815,  -815,    64,  -815,  -815,   -57,  -815,  -637,  -815,
    -636,  -815,  -815,  -634,  -633,  -613,   -89,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,   -43,  -815,
    -815,  -815,  -815,  -245,  -223,  -815,   239,  -815,  -366,     6,
      58,  -528,    41,  -815,  -114,  -815,   388,  -148,  -785,  -158,
    -815,  -815,  -815,   814,  -815,  -815,  -815,    21,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    19,   170,   160,   716,   688,   144,
     131,    22,   178,   183,   363,   179,   180,   140,   141,   217,
     218,   384,    23,   209,   447,    24,   542,   586,   622,    90,
     161,    26,   219,   508,   386,   456,    27,   210,   448,   457,
     458,   602,   650,   672,   673,   745,   674,   700,   701,   875,
     888,   843,   844,   892,   864,   845,   459,    28,   220,   571,
      29,   199,   441,   387,   466,   511,    30,   202,   444,   555,
     626,    31,   593,    32,   269,   627,   648,   628,   112,   162,
      34,   163,    36,    37,   164,    39,    40,   174,   175,   270,
     486,   430,   113,   114,   425,   426,    41,    42,    43,   445,
     557,    44,   449,   562,    45,   446,   559,   496,   558,    46,
     200,   373,   493,   494,    47,    48,   105,    49,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   388,   471,   535,
     692,   736,   737,   536,   467,   635,   689,   657,   658,   750,
     800,   749,   798,   837,   846,   847,    50,   488,   680,   681,
     570,   439,    52,    93,   165,   166,   167,   181,   539,   264,
     396,   540,   584,   168,   169,   738,   739,   265,   187
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,   226,    84,    21,   145,   238,   172,   126,   367,    51,
     369,   108,   838,   676,   677,   102,   678,   679,   106,    33,
     461,   469,    20,   660,   591,   214,   865,    72,   455,   465,
      65,   115,    67,    61,  -362,    69,    70,    85,   -33,     4,
     133,   607,    71,  -161,   138,   191,    86,    72,     7,  -301,
      66,   504,   194,     7,   196,   221,    96,     7,   654,    61,
     505,    61,   111,     7,    61,   893,    61,    61,   124,    61,
      61,   238,    61,    61,    61,   513,   103,   655,   718,   107,
     702,    68,   838,    94,    72,    87,   903,   159,   118,   111,
     122,   127,   116,   159,   132,    53,    54,   130,   137,   205,
     206,   130,  -307,    55,    97,   537,  -304,   211,     7,    72,
     267,    61,    84,   523,    56,    61,     7,    57,   654,   176,
       7,    88,   395,    58,   188,    61,    61,   -25,    25,    89,
      61,    61,   159,   189,    59,    60,   834,   655,    71,   274,
     -25,   -25,   159,    72,    73,    62,    25,   419,    74,   176,
     176,    75,    76,    77,   235,   676,   677,   176,   678,   679,
     216,    78,  -230,    79,    80,   796,   228,    74,   192,    81,
     371,    76,    77,   374,    82,    88,     7,   189,    98,     7,
     377,   378,    61,    91,    96,   100,   111,   580,    81,   389,
      99,    63,    64,   101,    25,   581,   390,    25,   273,    25,
      25,   237,   582,    25,   104,   274,   104,    25,   139,   117,
     142,   119,   121,   125,   128,   129,   491,   134,   135,   136,
     176,    25,   143,   176,   803,   189,    61,    97,   621,   159,
     176,   176,    61,   159,   -17,  -250,   -17,   -17,   177,    53,
      54,   484,    63,    64,   381,   382,   553,    55,   -17,  -134,
      96,   383,   237,   711,   159,   554,   198,   197,    56,   698,
     201,    57,     7,    61,   -24,    35,    61,    58,    95,   203,
     207,   208,    63,    64,   712,   212,   213,   204,    59,    60,
     713,   424,   579,    35,   185,   186,   215,   177,   185,   186,
     193,   714,   715,   899,   482,   497,   900,   545,   500,   619,
      53,    54,   435,   551,   436,   221,   437,   233,    55,   258,
       5,   560,   561,     7,    64,   442,    95,   261,    25,    56,
      63,    64,    57,   237,  -249,     8,     9,   365,    58,   -24,
     237,    35,   234,    83,    35,   236,    35,    35,    95,    59,
      35,    11,    63,    64,    35,    63,    64,   271,   185,   186,
     475,   476,    13,   239,    38,   501,   502,    14,    35,    15,
     240,    16,    17,    18,   483,    61,   272,   273,   274,   370,
     372,   393,    38,    61,   512,   375,   376,   397,   379,   380,
     391,   385,   583,   418,   438,   443,   454,   454,   428,    61,
      94,   485,   462,   470,   473,   480,   490,   489,   495,   550,
     451,   498,   460,   460,   216,   453,   464,   499,   429,    53,
      54,   177,   229,   541,   546,   552,   547,    55,   564,   504,
      38,   568,   590,    38,   549,    38,    38,   569,    56,    38,
     573,    57,   589,    38,   574,    84,    61,    58,   577,   252,
     253,   254,   595,   587,    61,   596,   258,    38,    59,    60,
     597,    64,   598,    61,   261,    35,   599,   609,   610,   614,
     237,   600,   630,   608,   521,   634,   624,   616,   641,   638,
     506,   454,   647,   651,   649,   111,   507,   538,    61,   652,
     697,   653,   661,   664,   665,   667,   668,   460,   693,   685,
     522,   696,   704,   686,   687,   618,   579,    61,   691,    61,
     708,   230,   709,   710,   717,   741,    61,   740,   742,    25,
     104,    25,    25,   743,   763,   556,   556,   578,   450,   556,
     744,   751,     5,   759,   662,     7,   566,   229,   752,   761,
     789,   790,   793,   794,   474,   795,   463,     8,     9,   159,
     802,   631,   632,   633,    38,    83,    96,    61,   804,   828,
     849,   695,   858,    11,   851,   855,   643,   646,   859,   860,
     867,   585,   434,   874,    13,  -209,   878,   898,     5,    14,
    -208,    15,   594,   879,   159,    18,   666,   762,   111,    25,
     787,   492,   890,     8,     9,   891,   620,    61,   897,   503,
     901,    83,   904,   225,   563,   791,   524,   452,   510,    11,
      92,    84,    33,   509,   792,   889,   734,    25,   604,   605,
      13,   832,   625,   432,   690,    14,   230,    15,   592,    16,
      17,    18,   882,   548,   869,   606,   468,   623,   398,   521,
       0,   159,     0,     0,     0,     0,    85,     0,     0,     0,
       0,   127,   565,   521,   567,     0,    35,   807,    35,    35,
     671,   572,    84,     0,   656,     0,     0,     0,   159,     0,
     127,     0,    61,     0,     0,     0,   675,     0,    61,   670,
     829,     0,     0,     0,   808,     0,   656,     0,     0,     0,
       0,    25,   139,     0,   521,   732,     0,   703,     0,     0,
       0,    25,   492,     0,     0,     0,    61,     0,    61,    61,
      61,    53,    54,     0,     0,     0,     0,     0,     0,    55,
      25,    25,     0,     0,     0,     0,    35,     0,     0,     0,
      56,     0,     0,    57,     0,     0,   760,     0,     0,    58,
       0,     0,   629,   525,     0,    38,     0,    38,    38,   756,
      59,    60,     0,     0,    35,    25,   876,     0,     0,     0,
      25,     0,    61,     0,   159,     0,    96,     0,     0,   788,
     886,   524,     0,     0,     0,    -3,     0,     0,   797,    25,
     857,     0,     0,     0,     0,   524,     0,   159,     0,     0,
       0,    53,    54,     0,     0,   521,     0,     0,     0,    55,
     521,     0,   671,     0,     0,     0,    25,     0,     0,     0,
      56,     0,     0,    57,   424,    38,     0,   699,   675,    58,
       0,   670,     0,   510,     0,     0,   524,   733,    35,     0,
      59,    87,    38,     5,     0,     6,     7,     0,   603,   578,
       0,     0,    61,    38,     0,     0,     0,     0,     8,     9,
       0,   567,     0,   746,   747,   748,    10,    35,    35,     0,
       0,     0,     0,   159,    11,     0,   228,    12,     0,     0,
     521,     0,     0,     0,     0,    13,     0,   159,     0,     0,
      14,     0,    15,     0,    16,    17,    18,     0,     0,     5,
     877,     0,    35,     0,     0,     0,     0,    35,     0,     0,
     644,    61,     0,     0,     8,     9,     0,   806,   659,     0,
       0,   896,    83,     0,     0,     0,    35,    38,     0,   171,
      11,   173,   525,     0,   182,     0,   184,   524,     0,     0,
     190,    13,   836,     0,     0,     5,    14,     0,    15,   195,
      16,    17,   645,    35,     0,     0,    38,    38,     5,     0,
       8,     9,     0,     0,     0,     0,     0,     0,    83,     0,
       0,    53,    54,   659,   735,     0,    11,     0,     0,    55,
     222,   223,   224,   182,   231,   232,     0,    13,     0,     0,
      56,    38,    14,    57,    15,     0,    38,   861,    18,    58,
       0,     0,     0,     0,     0,   229,     0,     0,     0,   514,
      59,     0,   836,     0,     0,    38,     0,     0,     0,     0,
       5,    38,   515,     7,     0,     0,     0,     0,     0,     0,
     516,     0,     0,    53,    54,     8,     9,     0,     0,     0,
       0,    55,    38,    83,   517,     0,     0,     0,   518,     0,
       0,    11,    56,     0,     0,    57,   902,     0,     0,     0,
     519,    58,    13,     0,   520,     0,     0,    14,   394,    15,
     229,     0,    59,    18,   525,   399,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   230,     0,   420,   421,     0,   427,
     146,   147,     0,     0,     0,   431,     0,     0,   433,     0,
     148,     0,     0,   149,     0,     0,     0,     0,     0,   150,
       0,   151,   229,     0,     0,     5,     0,     0,     0,     0,
     422,     0,     0,   153,   154,   155,     0,     0,    53,    54,
       8,     9,     0,     0,     0,     0,    55,     0,   227,     0,
       0,     0,     0,     0,     0,     0,    11,    56,     0,   230,
      57,     0,     0,    38,     0,     0,    58,    13,     0,     0,
       0,     0,    14,     0,    15,     0,   423,    59,    18,   157,
     158,     0,   146,   147,     0,     0,     0,     0,     0,     0,
       0,     0,   148,     0,     0,   149,     0,     0,     0,     0,
       0,   150,     0,   151,   440,     0,     0,     5,     0,     0,
       0,   230,   862,     0,     0,   153,   154,   155,     0,     0,
      53,    54,     8,     9,     0,   472,   863,     0,    55,     0,
     227,     0,     0,     0,     0,     0,     0,     0,    11,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,    13,
       0,     0,   479,     0,    14,     0,    15,   146,   147,    59,
      18,   157,   158,     0,     0,     0,     0,   148,     0,     0,
     149,     0,     0,     0,     0,     0,   150,     0,   151,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,     0,     0,    53,    54,     8,     9,     0,
       0,     0,     0,    55,     0,   227,     0,     0,     0,     0,
       0,     0,   543,    11,    56,   544,     0,    57,     0,     0,
       0,     0,     0,    58,    13,     0,     0,     0,     0,    14,
       0,    15,     0,     0,    59,    18,   157,   158,     0,     0,
       0,     0,     0,     0,   146,   147,     0,     0,     0,     0,
       0,     0,     0,   576,   148,     0,     0,   149,   868,     0,
       0,     0,     0,   840,     0,   151,     0,     0,     0,     5,
       0,     0,     0,     0,   841,     0,     0,   153,   154,   155,
       0,     0,    53,    54,     0,     0,   440,     0,   842,     0,
      55,     0,   156,     0,     0,     0,     0,     0,   601,     0,
       0,    56,     0,   440,    57,     0,     0,     0,   611,     0,
      58,   613,     0,     0,   615,     0,   617,     0,   146,   147,
       0,    59,    18,   157,   158,     0,     0,     0,   148,     0,
       0,   149,   887,     0,     0,     0,     0,   840,     0,   151,
       0,     0,     0,     5,     0,     0,     0,     0,   841,     0,
       0,   153,   154,   155,     0,     0,    53,    54,     0,     0,
       0,     0,   842,     0,    55,     0,   156,     0,     0,   146,
     147,     0,     0,     0,   663,    56,     0,     0,    57,   148,
       0,     0,   149,     0,    58,   682,   683,   684,   150,  -391,
     151,     0,     0,     0,     5,    59,    18,   157,   158,   152,
       0,     0,   153,   154,   155,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   156,     0,     0,
       0,     5,     0,     0,     7,     0,    56,     0,     0,    57,
       0,     0,     0,     0,     0,    58,     8,     9,     0,     0,
       0,     0,     0,     0,    83,     0,    59,   120,   157,   158,
       0,     0,    11,   753,   754,   755,     0,   757,   758,     0,
       0,     0,     0,    13,     0,     0,     0,     0,    14,     0,
      15,     0,     0,     0,    18,     0,     0,   182,     0,     0,
       0,     0,     0,     0,   801,     0,   440,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,   824,   825,   826,   827,     0,   243,   830,
     831,     0,   833,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,     0,   258,     0,   848,     0,   850,    64,
       0,   260,   261,  -187,     0,     0,     0,     0,   237,     0,
       0,     0,   263,     0,     5,     0,   515,     7,     0,     0,
       0,     0,   854,     0,   516,     0,     0,    53,    54,     8,
       9,     0,     0,     0,   866,    55,     0,    83,     0,     0,
       0,   848,   518,     0,     0,    11,    56,   872,     0,    57,
     873,     0,     0,     0,     0,    58,    13,     0,     0,     0,
     669,    14,     0,    15,   883,   884,    59,    18,     0,   848,
       0,     0,     0,   848,   894,   895,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   275,     0,
       0,     0,   276,   277,   848,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     275,     0,     0,     0,   276,   277,     0,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   487,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   146,   147,     0,     0,     0,     0,     0,     0,
       0,     0,   148,     0,  -398,   149,     0,     0,     0,     0,
       0,   150,     0,   151,     0,  -398,     0,     5,   248,   249,
     250,   251,   252,   253,   254,   153,   154,   155,     0,   258,
      53,    54,     0,     0,    64,     0,     0,   261,    55,     0,
     156,   146,   147,   237,     0,     0,     0,   263,     0,    56,
       0,   148,    57,     0,   149,  -398,     0,     0,    58,     0,
     150,     0,   151,     0,  -398,     0,     5,     0,     0,    59,
     120,   157,   158,     0,   153,   154,   155,     0,     0,    53,
      54,     0,     0,     0,     0,     0,     0,    55,     0,   156,
     146,   147,     0,     0,     0,     0,     0,     0,    56,     0,
     148,    57,     0,   149,     0,     0,     0,    58,     0,   150,
    -398,   151,     0,  -398,     0,     5,     0,     0,    59,   120,
     157,   158,     0,   153,   154,   155,     0,     0,    53,    54,
       0,     0,     0,     0,     0,     0,    55,     0,   156,     0,
       0,   146,   147,     0,     0,     0,     0,    56,     0,     0,
      57,   148,     0,     0,   149,     0,    58,     0,     0,     0,
     840,     0,   151,     0,     0,     0,     5,    59,    18,   157,
     158,   841,     0,     0,   153,   154,   155,     0,     0,    53,
      54,     0,     0,     0,     0,   842,     0,    55,     0,   156,
       0,     0,   146,   147,     0,     0,     0,     0,    56,     0,
       0,    57,   148,     0,     0,   149,     0,    58,     0,     0,
       0,   150,     0,   151,     0,     0,     0,     5,    59,    18,
     157,   158,   841,     0,     0,   153,   154,   155,     0,     0,
      53,    54,     0,     0,     0,     0,   842,     0,    55,     0,
     156,     0,     0,   146,   147,     0,     0,     0,     0,    56,
       0,     0,    57,   148,     0,     0,   149,     0,    58,     0,
       0,     0,   150,     0,   151,     0,     0,     0,     5,    59,
      18,   157,   158,   152,     0,     0,   153,   154,   155,     0,
       0,    53,    54,     0,     0,     0,     0,     0,     0,    55,
       0,   156,   146,   147,     0,     0,     0,     0,     0,     0,
      56,     0,   148,    57,     0,   149,     0,     0,     0,    58,
       0,   150,     0,   151,     0,     0,     0,     5,     0,   575,
      59,   120,   157,   158,     0,   153,   154,   155,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,    55,     0,
     156,   719,   720,     0,     0,     0,     0,     0,     0,    56,
       0,   721,    57,     0,     0,   722,     0,     0,    58,     0,
     723,     0,   724,     0,     0,     0,     5,     0,     0,    59,
      18,   157,   158,     0,   725,   726,   727,     0,     0,    53,
      54,     0,     0,     0,     0,   728,     0,    55,     0,   729,
     146,   147,     0,     0,     0,     0,     0,     0,    56,     0,
     148,    57,     0,   149,   799,     0,     0,    58,     0,   150,
       0,   151,     0,     0,     0,     5,     0,     0,    59,    18,
     730,   731,     0,   153,   154,   155,     0,     0,    53,    54,
       0,     0,     0,     0,     0,     0,    55,     0,   156,   146,
     147,     0,     0,     0,     0,     0,     0,    56,     0,   148,
      57,     0,   149,     0,     0,     0,    58,     0,   150,     0,
     151,     0,     0,     0,     5,     0,     0,    59,    18,   157,
     158,     0,   153,   154,   155,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   156,     0,     0,
       0,     0,     0,     0,     0,     0,    56,     0,     0,    57,
     835,     0,     0,     0,     0,    58,     0,     0,     0,     0,
       0,     5,     0,   515,     7,     0,    59,    18,   157,   158,
       0,   516,     0,     0,    53,    54,     8,     9,     0,     0,
       0,     0,    55,     0,    83,     0,     0,     0,     0,   518,
       0,     0,    11,    56,     0,     0,    57,     0,     0,     0,
       0,     0,    58,    13,     5,     0,     0,     0,    14,   109,
      15,     0,     0,    59,    18,     0,     0,    53,    54,     8,
       9,     0,     0,     0,     0,    55,     0,    83,     0,     0,
       0,     0,     0,     0,     0,    11,    56,     0,     0,    57,
       0,     0,     0,     0,     0,    58,    13,     5,     0,     0,
       0,    14,     0,    15,     0,   110,    59,    18,     0,     0,
      53,    54,     8,     9,     0,     0,     0,     0,    55,     0,
      83,     0,     0,     0,     0,     0,     0,     0,    11,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,    13,
       5,     0,     0,     0,    14,     0,    15,     0,    16,   123,
     120,     0,     0,    53,    54,     8,     9,     0,     0,     0,
       0,    55,     0,    83,     0,     0,     0,     0,     0,     0,
       0,    11,    56,     0,     0,    57,     0,     0,     0,     0,
       0,    58,    13,     0,     0,     0,     0,    14,     5,    15,
     515,     7,    59,   120,     0,     0,     0,     0,   516,     0,
       0,    53,    54,     0,     0,     0,     0,     0,     0,    55,
       0,     0,   517,     0,     0,     0,   518,     0,     0,     0,
      56,     0,     0,    57,     0,     0,     0,     0,   519,    58,
       0,     0,   520,     0,     0,     0,     0,     0,     0,     0,
      59,    18,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,     0,     0,     0,    63,    64,   259,   260,   261,   392,
       0,     0,     0,   262,   237,     0,     0,     0,   263,     0,
     880,   881,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,     0,     0,     0,    63,    64,   259,   260,   261,     0,
       0,     0,     0,   262,   237,     0,     0,     0,   263,     0,
     870,   871,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,   477,     0,     0,    63,    64,   259,   260,   261,     0,
       0,   478,     0,   262,   237,     0,     0,     0,   263,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,     0,   258,   639,     0,
       0,    63,    64,   259,   260,   261,     0,     0,   640,     0,
     262,   237,     0,     0,     0,   263,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,     0,   258,   852,     0,     0,    63,    64,
     259,   260,   261,     0,     0,   853,     0,   262,   237,     0,
       0,     0,   263,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
       0,   258,   266,     0,     0,    63,    64,   259,   260,   261,
       0,     0,     0,     0,   262,   237,     0,     0,     0,   263,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,     0,   258,   268,
       0,     0,    63,    64,   259,   260,   261,     0,     0,     0,
       0,   262,   237,     0,     0,     0,   263,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,     0,   258,     0,     0,     0,    63,
      64,   259,   260,   261,   364,     0,     0,     0,   262,   237,
       0,     0,     0,   263,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,     0,   258,     0,     0,     0,    63,    64,   259,   260,
     261,   366,     0,     0,     0,   262,   237,     0,     0,     0,
     263,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,     0,   258,
       0,     0,     0,    63,    64,   259,   260,   261,   368,     0,
       0,     0,   262,   237,     0,     0,     0,   263,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,     0,   258,     0,     0,     0,
      63,    64,   259,   260,   261,   392,     0,     0,     0,   262,
     237,     0,     0,     0,   263,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,     0,   258,     0,     0,     0,    63,    64,   259,
     260,   261,     0,     0,   481,     0,   262,   237,     0,     0,
       0,   263,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,   588,     0,     0,    63,    64,   259,   260,   261,     0,
       0,     0,     0,   262,   237,     0,     0,     0,   263,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,     0,   258,     0,     0,
       0,    63,    64,   259,   260,   261,     0,     0,     0,     0,
     262,   237,     0,   612,     0,   263,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,     0,   258,     0,     0,     0,    63,    64,
     259,   260,   261,   636,     0,     0,     0,   262,   237,     0,
       0,     0,   263,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
       0,   258,     0,     0,     0,    63,    64,   259,   260,   261,
     637,     0,     0,     0,   262,   237,     0,     0,     0,   263,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,     0,   258,     0,
       0,     0,    63,    64,   259,   260,   261,     0,     0,     0,
       0,   262,   237,     0,   642,     0,   263,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,     0,   258,   694,     0,     0,    63,
      64,   259,   260,   261,     0,     0,     0,     0,   262,   237,
       0,     0,     0,   263,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,     0,   258,     0,     0,     0,    63,    64,   259,   260,
     261,   705,     0,     0,     0,   262,   237,     0,     0,     0,
     263,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,     0,   258,
       0,     0,     0,    63,    64,   259,   260,   261,   706,     0,
       0,     0,   262,   237,     0,     0,     0,   263,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,     0,   258,     0,     0,     0,
      63,    64,   259,   260,   261,   707,     0,     0,     0,   262,
     237,     0,     0,     0,   263,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,     0,   258,     0,     0,     0,    63,    64,   259,
     260,   261,   805,     0,     0,     0,   262,   237,     0,     0,
       0,   263,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,     0,
     258,     0,     0,     0,    63,    64,   259,   260,   261,     0,
       0,   839,     0,   262,   237,     0,     0,     0,   263,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,     0,   258,     0,     0,
       0,    63,    64,   259,   260,   261,     0,     0,   856,     0,
     262,   237,     0,     0,     0,   263,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,     0,   258,   885,     0,     0,    63,    64,
     259,   260,   261,     0,     0,     0,     0,   262,   237,     0,
       0,     0,   263,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
       0,   258,     0,     0,     0,    63,    64,   259,   260,   261,
       0,     0,     0,  -206,   262,   237,     0,     0,     0,   263,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,     0,   258,     0,
       0,     0,    63,    64,   259,   260,   261,     0,     0,     0,
    -207,   262,   237,     0,     0,     0,   263,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,     0,   258,     0,     0,     0,    63,
      64,   259,   260,   261,     0,     0,     0,     0,   262,   237,
       0,     0,     0,   263,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,     0,   781,     0,     0,     0,    63,    64,   782,   783,
     784,     0,     0,     0,     0,   785,   237,     0,     0,     0,
     786,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,     0,   258,
       0,     0,     0,    63,    64,   259,   260,   261,     0,     0,
       0,     0,     0,   237,     0,     0,     0,   263,   241,   242,
     243,   244,     0,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,     0,   258,     0,     0,     0,
      63,    64,   259,   260,   261,     0,     0,     0,     0,     0,
     237,   241,   242,   243,   263,     0,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,     0,   258,
       0,     0,     0,    63,    64,   259,   260,   261,     0,     0,
       0,     0,     0,   237,   241,   242,   243,   263,     0,     0,
       0,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,     0,   258,     0,     0,     0,    63,    64,   259,   260,
     261,     0,     0,     0,     0,     0,   237,   243,     0,     0,
     263,     0,   248,   249,   250,   251,   252,   253,   254,     0,
     256,   257,     0,   258,     0,     0,     0,     0,    64,     0,
     260,   261,     0,     0,     0,     0,     0,   237,   243,     0,
       0,   263,     0,   248,   249,   250,   251,   252,   253,   254,
       0,   256,     0,     0,   258,     0,     0,     0,     0,    64,
       0,   260,   261,     0,     0,     0,     0,     0,   237,   243,
       0,     0,   263,     0,   248,   249,   250,   251,   252,   253,
     254,     0,     0,     0,     0,   258,     0,     0,     0,     0,
      64,     0,   260,   261,     0,     0,     0,     0,     0,   237,
       0,     0,     0,   263
};

static const yytype_int16 yycheck[] =
{
       7,   149,    21,     3,    93,   163,    96,    75,   193,     3,
     197,    68,   797,   650,   650,    52,   650,   650,    52,     3,
     386,   387,     3,   636,   552,   139,   840,    75,   386,   387,
       9,    52,    11,    40,    47,    14,    15,    21,    46,     0,
      78,   569,    70,    47,    82,   107,    60,    75,    61,    47,
      46,    99,   114,    61,   116,    46,    35,    61,    71,    66,
     108,    68,    69,    61,    71,   879,    73,    74,    75,    76,
      77,   229,    79,    80,    81,   103,   113,    90,   691,   113,
      46,    46,   867,    52,    75,   111,   900,    94,    72,    96,
      74,    75,   113,   100,    78,    71,    72,    78,    82,   128,
     129,    82,    47,    79,    44,   471,    47,   136,    61,    75,
     172,   118,   131,   471,    90,   122,    61,    93,    71,    98,
      61,    52,   236,    99,    47,   132,   133,    46,     3,    60,
     137,   138,   139,    56,   110,   111,    53,    90,    70,    56,
      59,    60,   149,    75,    76,     7,    21,   261,    80,   128,
     129,    83,    84,    85,   161,   792,   792,   136,   792,   792,
     141,    93,    47,    95,    96,    47,   150,    80,    47,   101,
     199,    84,    85,   202,   106,    52,    61,    56,    40,    61,
     209,   210,   189,    60,   163,    44,   193,    44,   101,    47,
      60,    48,    49,    52,    69,    52,    47,    72,    56,    74,
      75,    58,    59,    78,    66,    56,    68,    82,    52,    71,
      46,    73,    74,    75,    76,    77,    47,    79,    80,    81,
     199,    96,    46,   202,   752,    56,   233,    44,   586,   236,
     209,   210,   239,   240,    46,    52,    48,    49,   100,    71,
      72,   428,    48,    49,    87,    88,    47,    79,    60,    53,
     229,    94,    58,    72,   261,    56,   118,    52,    90,    91,
     122,    93,    61,   270,    60,     3,   273,    99,    44,    60,
     132,   133,    48,    49,    93,   137,   138,    60,   110,   111,
      99,   265,    58,    21,    50,    51,    53,   149,    50,    51,
      56,   110,   111,    53,    56,   446,    56,   482,   449,    47,
      71,    72,   364,   490,   366,    46,   368,    58,    79,    44,
      58,   498,   499,    61,    49,   372,    44,    52,   193,    90,
      48,    49,    93,    58,    52,    73,    74,   189,    99,    59,
      58,    69,    59,    81,    72,    52,    74,    75,    44,   110,
      78,    89,    48,    49,    82,    48,    49,    59,    50,    51,
      59,    60,   100,    53,     3,    59,    60,   105,    96,   107,
      56,   109,   110,   111,   426,   372,    45,    56,    56,    59,
      46,   233,    21,   380,   463,    46,    46,   239,    46,    53,
      53,    56,   540,    50,    53,    46,   386,   387,    52,   396,
      52,    56,   386,   387,    53,    53,    52,    60,    46,   488,
     384,    52,   386,   387,   385,   386,   387,    52,   270,    71,
      72,   273,   150,    46,    52,    59,    53,    79,    59,    99,
      69,    47,    53,    72,   486,    74,    75,    59,    90,    78,
      60,    93,   546,    82,    52,   454,   443,    99,    52,    37,
      38,    39,    47,    60,   451,    47,    44,    96,   110,   111,
      53,    49,    53,   460,    52,   193,    47,    47,    46,    72,
      58,    60,    46,    60,   471,    60,    53,   581,    53,    52,
     454,   471,    47,    52,    60,   482,   457,   471,   485,    52,
     667,    52,    46,    60,    52,    52,    60,   471,    53,    59,
     471,    60,    47,    59,    75,   585,    58,   504,    78,   506,
      46,   150,    46,    79,    47,    53,   513,    60,    53,   384,
     372,   386,   387,    52,    55,   496,   497,   524,   380,   500,
      60,    59,    58,    58,   638,    61,   505,   265,    59,    52,
      60,    60,    60,    60,   396,    60,    72,    73,    74,   546,
      46,   603,   604,   605,   193,    81,   525,   554,    53,    50,
      60,   665,    46,    89,    53,    53,   618,   625,    60,    52,
      55,   540,   301,    52,   100,    56,    53,    55,    58,   105,
      56,   107,   556,    56,   581,   111,   644,   735,   585,   454,
     738,   443,    53,    73,    74,    60,   586,   594,    53,   451,
      60,    81,    60,   149,   501,   743,   471,   385,   460,    89,
      29,   620,   586,   457,   745,   875,   692,   482,   566,   566,
     100,   788,   593,   273,   657,   105,   265,   107,   554,   109,
     110,   111,   867,   485,   847,   567,   387,   586,   240,   636,
      -1,   638,    -1,    -1,    -1,    -1,   620,    -1,    -1,    -1,
      -1,   625,   504,   650,   506,    -1,   384,   761,   386,   387,
     650,   513,   671,    -1,   635,    -1,    -1,    -1,   665,    -1,
     644,    -1,   669,    -1,    -1,    -1,   650,    -1,   675,   650,
     784,    -1,    -1,    -1,   763,    -1,   657,    -1,    -1,    -1,
      -1,   556,    52,    -1,   691,   692,    -1,   671,    -1,    -1,
      -1,   566,   554,    -1,    -1,    -1,   703,    -1,   705,   706,
     707,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
     585,   586,    -1,    -1,    -1,    -1,   454,    -1,    -1,    -1,
      90,    -1,    -1,    93,    -1,    -1,   733,    -1,    -1,    99,
      -1,    -1,   594,   471,    -1,   384,    -1,   386,   387,   723,
     110,   111,    -1,    -1,   482,   620,   860,    -1,    -1,    -1,
     625,    -1,   759,    -1,   761,    -1,   735,    -1,    -1,   738,
     874,   636,    -1,    -1,    -1,     0,    -1,    -1,   749,   644,
     832,    -1,    -1,    -1,    -1,   650,    -1,   784,    -1,    -1,
      -1,    71,    72,    -1,    -1,   792,    -1,    -1,    -1,    79,
     797,    -1,   792,    -1,    -1,    -1,   671,    -1,    -1,    -1,
      90,    -1,    -1,    93,   788,   454,    -1,   669,   792,    99,
      -1,   792,    -1,   675,    -1,    -1,   691,   692,   556,    -1,
     110,   111,   471,    58,    -1,    60,    61,    -1,   566,   836,
      -1,    -1,   839,   482,    -1,    -1,    -1,    -1,    73,    74,
      -1,   703,    -1,   705,   706,   707,    81,   585,   586,    -1,
      -1,    -1,    -1,   860,    89,    -1,   840,    92,    -1,    -1,
     867,    -1,    -1,    -1,    -1,   100,    -1,   874,    -1,    -1,
     105,    -1,   107,    -1,   109,   110,   111,    -1,    -1,    58,
     861,    -1,   620,    -1,    -1,    -1,    -1,   625,    -1,    -1,
      69,   898,    -1,    -1,    73,    74,    -1,   759,   636,    -1,
      -1,   882,    81,    -1,    -1,    -1,   644,   556,    -1,    95,
      89,    97,   650,    -1,   100,    -1,   102,   792,    -1,    -1,
     106,   100,   797,    -1,    -1,    58,   105,    -1,   107,   115,
     109,   110,   111,   671,    -1,    -1,   585,   586,    58,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    71,    72,   691,   692,    -1,    89,    -1,    -1,    79,
     146,   147,   148,   149,   150,   151,    -1,   100,    -1,    -1,
      90,   620,   105,    93,   107,    -1,   625,   839,   111,    99,
      -1,    -1,    -1,    -1,    -1,   723,    -1,    -1,    -1,    47,
     110,    -1,   867,    -1,    -1,   644,    -1,    -1,    -1,    -1,
      58,   650,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,   671,    81,    82,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    -1,    93,   898,    -1,    -1,    -1,
      98,    99,   100,    -1,   102,    -1,    -1,   105,   234,   107,
     788,    -1,   110,   111,   792,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   723,    -1,   262,   263,    -1,   265,
      33,    34,    -1,    -1,    -1,   271,    -1,    -1,   274,    -1,
      43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    54,   840,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,   788,
      93,    -1,    -1,   792,    -1,    -1,    99,   100,    -1,    -1,
      -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,   112,
     113,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    54,   370,    -1,    -1,    58,    -1,    -1,
      -1,   840,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    73,    74,    -1,   391,    77,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,   418,    -1,   105,    -1,   107,    33,    34,   110,
     111,   112,   113,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,   478,    89,    90,   481,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,
      -1,   107,    -1,    -1,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   519,    43,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,   552,    -1,    77,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,   564,    -1,
      -1,    90,    -1,   569,    93,    -1,    -1,    -1,   574,    -1,
      99,   577,    -1,    -1,   580,    -1,   582,    -1,    33,    34,
      -1,   110,   111,   112,   113,    -1,    -1,    -1,    43,    -1,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,    -1,    81,    -1,    -1,    33,
      34,    -1,    -1,    -1,   640,    90,    -1,    -1,    93,    43,
      -1,    -1,    46,    -1,    99,   651,   652,   653,    52,    53,
      54,    -1,    -1,    -1,    58,   110,   111,   112,   113,    63,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    58,    -1,    -1,    61,    -1,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,   110,   111,   112,   113,
      -1,    -1,    89,   719,   720,   721,    -1,   723,   724,    -1,
      -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,    -1,    -1,   111,    -1,    -1,   743,    -1,    -1,
      -1,    -1,    -1,    -1,   750,    -1,   752,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   764,   765,
     766,   767,   768,   769,   770,   771,   772,   773,   774,   775,
     776,   777,   778,   779,   780,   781,   782,    -1,    28,   785,
     786,    -1,   788,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,   802,    -1,   804,    49,
      -1,    51,    52,    47,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    58,    -1,    60,    61,    -1,    -1,
      -1,    -1,   828,    -1,    68,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,   840,    79,    -1,    81,    -1,    -1,
      -1,   847,    86,    -1,    -1,    89,    90,   853,    -1,    93,
     856,    -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    -1,
     104,   105,    -1,   107,   870,   871,   110,   111,    -1,   875,
      -1,    -1,    -1,   879,   880,   881,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    26,    27,   900,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
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
     112,   113,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    54,    -1,    56,    -1,    58,    33,    34,
      35,    36,    37,    38,    39,    66,    67,    68,    -1,    44,
      71,    72,    -1,    -1,    49,    -1,    -1,    52,    79,    -1,
      81,    33,    34,    58,    -1,    -1,    -1,    62,    -1,    90,
      -1,    43,    93,    -1,    46,    47,    -1,    -1,    99,    -1,
      52,    -1,    54,    -1,    56,    -1,    58,    -1,    -1,   110,
     111,   112,   113,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,
      53,    54,    -1,    56,    -1,    58,    -1,    -1,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      93,    43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,
     113,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,
      -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    93,    43,    -1,    -1,    46,    -1,    99,    -1,    -1,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,   110,   111,
     112,   113,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,
      81,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    93,    43,    -1,    -1,    46,    -1,    99,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,   110,
     111,   112,   113,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    43,    93,    -1,    46,    -1,    -1,    -1,    99,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    60,
     110,   111,   112,   113,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    43,    93,    -1,    -1,    47,    -1,    -1,    99,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,
     111,   112,   113,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    46,    47,    -1,    -1,    99,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,
      47,    -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    60,    61,    -1,   110,   111,   112,   113,
      -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,   100,    58,    -1,    -1,    -1,   105,    63,
     107,    -1,    -1,   110,   111,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    58,    -1,    -1,
      -1,   105,    -1,   107,    -1,   109,   110,   111,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      58,    -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,
     111,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,   100,    -1,    -1,    -1,    -1,   105,    58,   107,
      60,    61,   110,   111,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    -1,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    98,    99,
      -1,    -1,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   111,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    -1,
      64,    65,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    -1,
      64,    65,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
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
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    45,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    60,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    -1,    60,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
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
      48,    49,    50,    51,    52,    53,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    26,    27,    28,    62,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    26,    27,    28,    62,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    28,    -1,    -1,
      62,    -1,    33,    34,    35,    36,    37,    38,    39,    -1,
      41,    42,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,    -1,
      -1,    62,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    -1,    -1,    44,    -1,    -1,    -1,    -1,    49,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,
      -1,    -1,    62,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,   100,   105,   107,   109,   110,   111,   122,
     127,   128,   129,   140,   143,   148,   149,   154,   175,   178,
     184,   189,   191,   196,   198,   199,   200,   201,   202,   203,
     204,   214,   215,   216,   219,   222,   227,   232,   233,   235,
     264,   267,   270,    71,    72,    79,    90,    93,    99,   110,
     111,   123,   124,    48,    49,   285,    46,   285,    46,   285,
     285,    70,    75,    76,    80,    83,    84,    85,    93,    95,
      96,   101,   106,    81,   129,   196,    60,   111,    52,    60,
     147,    60,   147,   271,    52,    44,   285,    44,   124,    60,
      44,    52,    52,   113,   124,   234,    52,   113,   234,    63,
     109,   123,   196,   210,   211,    52,   113,   124,   196,   124,
     111,   124,   196,   110,   123,   124,   191,   196,   124,   124,
     127,   128,   196,   215,   124,   124,   124,   196,   215,    52,
     135,   136,    46,    46,   127,   244,    33,    34,    43,    46,
      52,    54,    63,    66,    67,    68,    81,   112,   113,   123,
     124,   148,   197,   199,   202,   272,   273,   274,   281,   282,
     123,   281,   211,   281,   205,   206,   285,   124,   130,   133,
     134,   275,   281,   131,   281,    50,    51,   286,    47,    56,
     281,   286,    47,    56,   286,   281,   286,    52,   124,   179,
     228,   124,   185,    60,    60,   205,   205,   124,   124,   141,
     155,   205,   124,   124,   272,    53,   127,   137,   138,   150,
     176,    46,   281,   281,   281,   133,   275,    81,   196,   199,
     202,   281,   281,    58,    59,   123,    52,    58,   277,    53,
      56,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    44,    50,
      51,    52,    57,    62,   277,   285,    45,   286,    45,   192,
     207,    59,    45,    56,    56,    22,    26,    27,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   132,    53,   124,    53,   210,    53,   135,
      59,   205,    46,   229,   205,    46,    46,   205,   205,    46,
      53,    87,    88,    94,   139,    56,   152,   181,   245,    47,
      47,    53,    53,   124,   281,   272,   278,   124,   274,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,    50,   272,
     281,   281,    63,   109,   196,   212,   213,   281,    52,   124,
     209,   281,   134,   281,   131,   286,   286,   286,    53,   269,
     281,   180,   234,    46,   186,   217,   223,   142,   156,   220,
     124,   196,   138,   127,   128,   143,   153,   157,   158,   174,
     196,   266,   267,    72,   127,   143,   182,   252,   264,   266,
     267,   246,   281,    53,   124,    59,    60,    45,    55,   281,
      53,    55,    56,   286,   135,    56,   208,    53,   265,    60,
      52,    47,   124,   230,   231,    46,   225,   225,    52,    52,
     225,    59,    60,   124,    99,   108,   196,   127,   151,   158,
     124,   183,   244,   103,    47,    60,    68,    82,    86,    98,
     102,   123,   127,   143,   148,   199,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   247,   251,   266,   267,   276,
     279,    46,   144,   281,   281,   210,    52,    53,   124,   286,
     244,   135,    59,    47,    56,   187,   127,   218,   226,   224,
     135,   135,   221,   144,    59,   124,   285,   124,    47,    59,
     268,   177,   124,    60,    52,    60,   281,    52,   123,    58,
      44,    52,    59,   277,   280,   285,   145,    60,    45,   272,
      53,   269,   231,   190,   196,    47,    47,    53,    53,    47,
      60,   281,   159,   199,   200,   203,   268,   269,    60,    47,
      46,   281,    60,   281,    72,   281,   272,   281,   211,    47,
     128,   143,   146,   270,    53,   127,   188,   193,   195,   124,
      46,   286,   286,   286,    60,   253,    53,    53,    52,    45,
      55,    53,    60,   286,    69,   111,   191,    47,   194,    60,
     160,    52,    52,    52,    71,    90,   127,   255,   256,   199,
     243,    46,   272,   281,    60,    52,   191,    52,    60,   104,
     127,   128,   161,   162,   164,   196,   236,   238,   241,   242,
     266,   267,   281,   281,   281,    59,    59,    75,   126,   254,
     256,    78,   248,    53,    45,   272,    60,   135,    91,   124,
     165,   166,    46,   196,    47,    53,    53,    53,    46,    46,
      79,    72,    93,    99,   110,   111,   125,    47,   243,    33,
      34,    43,    47,    52,    54,    66,    67,    68,    77,    81,
     112,   113,   123,   148,   197,   199,   249,   250,   283,   284,
      60,    53,    53,    52,    60,   163,   124,   124,   124,   259,
     257,    59,    59,   281,   281,   281,   196,   281,   281,    58,
     123,    52,   277,    55,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    44,    50,    51,    52,    57,    62,   277,   285,    60,
      60,   275,   160,    60,    60,    60,    47,   127,   260,    47,
     258,   281,    46,   269,    53,    53,   124,   272,   244,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,    50,   272,
     281,   281,   213,   281,    53,    47,   148,   261,   276,    55,
      52,    63,    77,   169,   170,   173,   262,   263,   281,    60,
     281,    53,    45,    55,   281,    53,    55,   286,    46,    60,
      52,   124,    63,    77,   172,   173,   281,    55,    47,   262,
      64,    65,   281,   281,    52,   167,   272,   127,    53,    56,
      64,    65,   261,   281,   281,    45,   272,    47,   168,   169,
      53,    60,   171,   173,   281,   281,   127,    53,    55,    53,
      56,    60,   124,   173,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int16 yyr1[] =
{
       0,   118,   119,   120,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   125,   125,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   129,
     130,   130,   131,   131,   131,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   133,   133,   134,   135,   136,   135,   137,   137,   138,
     138,   139,   139,   139,   139,   141,   142,   140,   143,   143,
     143,   143,   144,   145,   145,   146,   146,   147,   147,   148,
     150,   151,   149,   152,   152,   153,   153,   153,   153,   155,
     156,   154,   157,   157,   159,   158,   160,   160,   161,   161,
     161,   161,   161,   161,   161,   163,   162,   164,   164,   165,
     165,   166,   167,   167,   168,   169,   169,   170,   170,   171,
     171,   172,   172,   172,   172,   173,   173,   173,   173,   173,
     174,   174,   174,   176,   177,   175,   179,   180,   178,   181,
     181,   182,   182,   182,   182,   182,   183,   185,   186,   187,
     188,   184,   184,   184,   189,   190,   190,   192,   191,   193,
     193,   194,   193,   195,   196,   196,   196,   196,   196,   197,
     197,   198,   198,   199,   200,   201,   201,   202,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   204,
     204,   204,   205,   205,   207,   208,   206,   209,   209,   210,
     210,   210,   210,   211,   211,   211,   212,   212,   212,   213,
     213,   214,   214,   214,   214,   214,   215,   215,   215,   215,
     217,   218,   216,   220,   221,   219,   223,   224,   222,   225,
     225,   226,   228,   227,   229,   227,   230,   230,   231,   232,
     233,   234,   234,   235,   235,   235,   235,   236,   236,   237,
     237,   238,   239,   240,   240,   241,   241,   242,   243,   243,
     243,   243,   243,   243,   243,   243,   245,   244,   246,   246,
     247,   248,   248,   249,   249,   250,   250,   251,   251,   251,
     251,   253,   254,   252,   255,   255,   256,   256,   256,   256,
     257,   257,   258,   259,   259,   260,   261,   261,   262,   263,
     263,   265,   264,   266,   266,   267,   268,   268,   269,   271,
     270,   272,   272,   273,   273,   274,   274,   274,   275,   275,
     275,   276,   276,   278,   277,   279,   279,   279,   279,   280,
     280,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   281,   281,   281,   281,   281,   281,   281,
     281,   281,   281,   282,   282,   282,   282,   282,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   284,   284,
     284,   284,   284,   285,   285,   286,   286
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     1,     1,     2,     2,     5,     5,
       1,     1,     0,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     0,     0,     2,     1,     3,     4,
       6,     1,     1,     1,     0,     0,     0,     9,     7,     6,
       9,     8,     3,     0,     2,     1,     1,     0,     3,     1,
       0,     0,     8,     0,     2,     1,     1,     1,     1,     0,
       0,     9,     1,     2,     0,     8,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     5,     0,     2,     2,
       1,     7,     0,     2,     4,     1,     1,     5,     3,     1,
       3,     3,     3,     1,     1,     1,     3,     3,     1,     1,
      10,    10,    10,     0,     0,     9,     0,     0,     9,     0,
       2,     1,     1,     1,     1,     1,     1,     0,     0,     0,
       0,    11,     1,     4,     4,     0,     2,     0,     7,     3,
       4,     0,     2,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     4,     4,     4,     4,     1,     1,
       1,     1,     1,     4,     4,     4,     6,     6,     6,     1,
       1,     1,     0,     1,     0,     0,     5,     1,     3,     1,
       1,     1,     1,     0,     1,     3,     1,     1,     1,     1,
       3,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       0,     0,     9,     0,     0,     9,     0,     0,     9,     0,
       2,     4,     0,     7,     0,     8,     1,     3,     3,     4,
       4,     1,     3,     4,     4,     4,     4,     1,     4,     5,
       8,     1,     2,     2,     3,     5,     7,     7,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     5,     0,     2,
       7,     0,     2,     3,     2,     1,     1,     1,     1,     1,
       1,     0,     0,     8,     1,     2,     5,     5,     7,     6,
       0,     2,     5,     0,     2,     3,     1,     4,     5,     1,
       2,     0,     8,     5,     4,     7,     0,     2,     1,     0,
       3,     0,     1,     1,     3,     1,     3,     1,     0,     1,
       3,     1,     2,     0,     3,     1,     1,     2,     2,     3,
       5,     1,     1,     1,     1,     1,     1,     2,     4,     6,
       3,     3,     3,     2,     2,     2,     2,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     1,     0,     7,     4,     4,     4,     1,     1,
       1,     1,     1,     1,     2,     4,     6,     3,     2,     2,
       2,     2,     2,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     1,     0,     7,
       4,     4,     4,     1,     1,     1,     1
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
#line 2806 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2812 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2818 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2824 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2830 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2836 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2842 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2848 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2854 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2860 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2866 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2872 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2878 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2884 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2890 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2896 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2902 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2908 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2914 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2920 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2926 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2932 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2938 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2944 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2950 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2956 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2962 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2968 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2974 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2980 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2986 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 2992 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 2998 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3004 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3010 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3016 "p4parser.tab.c"
    break;

  case 42:
#line 319 "p4parser.y"
              {}
#line 3022 "p4parser.tab.c"
    break;

  case 43:
#line 321 "p4parser.y"
        {}
#line 3028 "p4parser.tab.c"
    break;

  case 44:
#line 323 "p4parser.y"
        {}
#line 3034 "p4parser.tab.c"
    break;

  case 45:
#line 327 "p4parser.y"
                       {}
#line 3040 "p4parser.tab.c"
    break;

  case 46:
#line 328 "p4parser.y"
                       {}
#line 3046 "p4parser.tab.c"
    break;

  case 47:
#line 329 "p4parser.y"
                       {}
#line 3052 "p4parser.tab.c"
    break;

  case 48:
#line 330 "p4parser.y"
                       {}
#line 3058 "p4parser.tab.c"
    break;

  case 49:
#line 331 "p4parser.y"
                       {}
#line 3064 "p4parser.tab.c"
    break;

  case 50:
#line 332 "p4parser.y"
                       {}
#line 3070 "p4parser.tab.c"
    break;

  case 51:
#line 333 "p4parser.y"
                       {}
#line 3076 "p4parser.tab.c"
    break;

  case 52:
#line 334 "p4parser.y"
                       {}
#line 3082 "p4parser.tab.c"
    break;

  case 53:
#line 335 "p4parser.y"
                       {}
#line 3088 "p4parser.tab.c"
    break;

  case 54:
#line 336 "p4parser.y"
                       {}
#line 3094 "p4parser.tab.c"
    break;

  case 55:
#line 337 "p4parser.y"
                       {}
#line 3100 "p4parser.tab.c"
    break;

  case 56:
#line 338 "p4parser.y"
                       {}
#line 3106 "p4parser.tab.c"
    break;

  case 57:
#line 339 "p4parser.y"
                       {}
#line 3112 "p4parser.tab.c"
    break;

  case 58:
#line 340 "p4parser.y"
                       {}
#line 3118 "p4parser.tab.c"
    break;

  case 59:
#line 341 "p4parser.y"
                       {}
#line 3124 "p4parser.tab.c"
    break;

  case 60:
#line 342 "p4parser.y"
                       {}
#line 3130 "p4parser.tab.c"
    break;

  case 61:
#line 343 "p4parser.y"
                       {}
#line 3136 "p4parser.tab.c"
    break;

  case 62:
#line 344 "p4parser.y"
                       {}
#line 3142 "p4parser.tab.c"
    break;

  case 63:
#line 345 "p4parser.y"
                       {}
#line 3148 "p4parser.tab.c"
    break;

  case 64:
#line 346 "p4parser.y"
                       {}
#line 3154 "p4parser.tab.c"
    break;

  case 65:
#line 347 "p4parser.y"
                       {}
#line 3160 "p4parser.tab.c"
    break;

  case 66:
#line 348 "p4parser.y"
                       {}
#line 3166 "p4parser.tab.c"
    break;

  case 67:
#line 349 "p4parser.y"
                       {}
#line 3172 "p4parser.tab.c"
    break;

  case 68:
#line 350 "p4parser.y"
                       {}
#line 3178 "p4parser.tab.c"
    break;

  case 69:
#line 351 "p4parser.y"
                       {}
#line 3184 "p4parser.tab.c"
    break;

  case 70:
#line 352 "p4parser.y"
                       {}
#line 3190 "p4parser.tab.c"
    break;

  case 71:
#line 353 "p4parser.y"
                       {}
#line 3196 "p4parser.tab.c"
    break;

  case 72:
#line 354 "p4parser.y"
                       {}
#line 3202 "p4parser.tab.c"
    break;

  case 73:
#line 355 "p4parser.y"
                       {}
#line 3208 "p4parser.tab.c"
    break;

  case 74:
#line 356 "p4parser.y"
                       {}
#line 3214 "p4parser.tab.c"
    break;

  case 75:
#line 357 "p4parser.y"
                       {}
#line 3220 "p4parser.tab.c"
    break;

  case 76:
#line 358 "p4parser.y"
                       {}
#line 3226 "p4parser.tab.c"
    break;

  case 77:
#line 359 "p4parser.y"
                       {}
#line 3232 "p4parser.tab.c"
    break;

  case 78:
#line 360 "p4parser.y"
                       {}
#line 3238 "p4parser.tab.c"
    break;

  case 79:
#line 361 "p4parser.y"
                       {}
#line 3244 "p4parser.tab.c"
    break;

  case 80:
#line 362 "p4parser.y"
                       {}
#line 3250 "p4parser.tab.c"
    break;

  case 81:
#line 363 "p4parser.y"
                       {}
#line 3256 "p4parser.tab.c"
    break;

  case 82:
#line 364 "p4parser.y"
                       {}
#line 3262 "p4parser.tab.c"
    break;

  case 83:
#line 365 "p4parser.y"
                       {}
#line 3268 "p4parser.tab.c"
    break;

  case 84:
#line 366 "p4parser.y"
                       {}
#line 3274 "p4parser.tab.c"
    break;

  case 85:
#line 367 "p4parser.y"
                       {}
#line 3280 "p4parser.tab.c"
    break;

  case 86:
#line 368 "p4parser.y"
                       {}
#line 3286 "p4parser.tab.c"
    break;

  case 87:
#line 369 "p4parser.y"
                       {}
#line 3292 "p4parser.tab.c"
    break;

  case 88:
#line 370 "p4parser.y"
                       {}
#line 3298 "p4parser.tab.c"
    break;

  case 89:
#line 371 "p4parser.y"
                       {}
#line 3304 "p4parser.tab.c"
    break;

  case 90:
#line 372 "p4parser.y"
                            {}
#line 3310 "p4parser.tab.c"
    break;

  case 91:
#line 374 "p4parser.y"
                       {}
#line 3316 "p4parser.tab.c"
    break;

  case 92:
#line 375 "p4parser.y"
                       {}
#line 3322 "p4parser.tab.c"
    break;

  case 93:
#line 376 "p4parser.y"
                       {}
#line 3328 "p4parser.tab.c"
    break;

  case 94:
#line 377 "p4parser.y"
                       {}
#line 3334 "p4parser.tab.c"
    break;

  case 95:
#line 378 "p4parser.y"
                       {}
#line 3340 "p4parser.tab.c"
    break;

  case 96:
#line 379 "p4parser.y"
                       {}
#line 3346 "p4parser.tab.c"
    break;

  case 97:
#line 380 "p4parser.y"
                       {}
#line 3352 "p4parser.tab.c"
    break;

  case 98:
#line 381 "p4parser.y"
                       {}
#line 3358 "p4parser.tab.c"
    break;

  case 99:
#line 382 "p4parser.y"
                       {}
#line 3364 "p4parser.tab.c"
    break;

  case 100:
#line 383 "p4parser.y"
                       {}
#line 3370 "p4parser.tab.c"
    break;

  case 101:
#line 384 "p4parser.y"
                       {}
#line 3376 "p4parser.tab.c"
    break;

  case 102:
#line 385 "p4parser.y"
                       {}
#line 3382 "p4parser.tab.c"
    break;

  case 103:
#line 386 "p4parser.y"
                       {}
#line 3388 "p4parser.tab.c"
    break;

  case 104:
#line 387 "p4parser.y"
                       {}
#line 3394 "p4parser.tab.c"
    break;

  case 105:
#line 388 "p4parser.y"
                       {}
#line 3400 "p4parser.tab.c"
    break;

  case 106:
#line 389 "p4parser.y"
                       {}
#line 3406 "p4parser.tab.c"
    break;

  case 108:
#line 391 "p4parser.y"
                       {}
#line 3412 "p4parser.tab.c"
    break;

  case 109:
#line 392 "p4parser.y"
                       {}
#line 3418 "p4parser.tab.c"
    break;

  case 110:
#line 393 "p4parser.y"
                       {}
#line 3424 "p4parser.tab.c"
    break;

  case 111:
#line 394 "p4parser.y"
                       {}
#line 3430 "p4parser.tab.c"
    break;

  case 112:
#line 395 "p4parser.y"
                       {}
#line 3436 "p4parser.tab.c"
    break;

  case 113:
#line 396 "p4parser.y"
                       {}
#line 3442 "p4parser.tab.c"
    break;

  case 114:
#line 397 "p4parser.y"
                       {}
#line 3448 "p4parser.tab.c"
    break;

  case 115:
#line 398 "p4parser.y"
                       {}
#line 3454 "p4parser.tab.c"
    break;

  case 116:
#line 399 "p4parser.y"
                       {}
#line 3460 "p4parser.tab.c"
    break;

  case 117:
#line 400 "p4parser.y"
                       {}
#line 3466 "p4parser.tab.c"
    break;

  case 118:
#line 401 "p4parser.y"
                       {}
#line 3472 "p4parser.tab.c"
    break;

  case 119:
#line 402 "p4parser.y"
                       {}
#line 3478 "p4parser.tab.c"
    break;

  case 120:
#line 403 "p4parser.y"
                       {}
#line 3484 "p4parser.tab.c"
    break;

  case 121:
#line 404 "p4parser.y"
                       {}
#line 3490 "p4parser.tab.c"
    break;

  case 122:
#line 405 "p4parser.y"
                       {}
#line 3496 "p4parser.tab.c"
    break;

  case 123:
#line 406 "p4parser.y"
                       {}
#line 3502 "p4parser.tab.c"
    break;

  case 124:
#line 407 "p4parser.y"
                       {}
#line 3508 "p4parser.tab.c"
    break;

  case 125:
#line 408 "p4parser.y"
                       {}
#line 3514 "p4parser.tab.c"
    break;

  case 126:
#line 409 "p4parser.y"
                       {}
#line 3520 "p4parser.tab.c"
    break;

  case 127:
#line 410 "p4parser.y"
                       {}
#line 3526 "p4parser.tab.c"
    break;

  case 128:
#line 411 "p4parser.y"
                       {}
#line 3532 "p4parser.tab.c"
    break;

  case 129:
#line 412 "p4parser.y"
                       {}
#line 3538 "p4parser.tab.c"
    break;

  case 130:
#line 413 "p4parser.y"
                       {}
#line 3544 "p4parser.tab.c"
    break;

  case 131:
#line 417 "p4parser.y"
                                      {}
#line 3550 "p4parser.tab.c"
    break;

  case 132:
#line 418 "p4parser.y"
                                        {}
#line 3556 "p4parser.tab.c"
    break;

  case 133:
#line 422 "p4parser.y"
                                         {}
#line 3562 "p4parser.tab.c"
    break;

  case 134:
#line 426 "p4parser.y"
                                      {}
#line 3568 "p4parser.tab.c"
    break;

  case 135:
#line 427 "p4parser.y"
      { ReenterScope(subparser); }
#line 3574 "p4parser.tab.c"
    break;

  case 136:
#line 427 "p4parser.y"
                                                         { ExitReentrantScope(subparser); }
#line 3580 "p4parser.tab.c"
    break;

  case 137:
#line 431 "p4parser.y"
                                          {}
#line 3586 "p4parser.tab.c"
    break;

  case 138:
#line 432 "p4parser.y"
                                            {}
#line 3592 "p4parser.tab.c"
    break;

  case 139:
#line 436 "p4parser.y"
                                            {}
#line 3598 "p4parser.tab.c"
    break;

  case 140:
#line 437 "p4parser.y"
                                                              {}
#line 3604 "p4parser.tab.c"
    break;

  case 141:
#line 441 "p4parser.y"
                 {}
#line 3610 "p4parser.tab.c"
    break;

  case 142:
#line 442 "p4parser.y"
                   {}
#line 3616 "p4parser.tab.c"
    break;

  case 143:
#line 443 "p4parser.y"
                   {}
#line 3622 "p4parser.tab.c"
    break;

  case 144:
#line 444 "p4parser.y"
                   {}
#line 3628 "p4parser.tab.c"
    break;

  case 145:
#line 448 "p4parser.y"
                                  {}
#line 3634 "p4parser.tab.c"
    break;

  case 146:
#line 449 "p4parser.y"
                        {}
#line 3640 "p4parser.tab.c"
    break;

  case 147:
#line 450 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3649 "p4parser.tab.c"
    break;

  case 148:
#line 458 "p4parser.y"
                     {}
#line 3655 "p4parser.tab.c"
    break;

  case 149:
#line 460 "p4parser.y"
                     {}
#line 3661 "p4parser.tab.c"
    break;

  case 152:
#line 469 "p4parser.y"
                               {}
#line 3667 "p4parser.tab.c"
    break;

  case 153:
#line 473 "p4parser.y"
                                     {}
#line 3673 "p4parser.tab.c"
    break;

  case 154:
#line 474 "p4parser.y"
                                     {}
#line 3679 "p4parser.tab.c"
    break;

  case 155:
#line 478 "p4parser.y"
                               {}
#line 3685 "p4parser.tab.c"
    break;

  case 156:
#line 479 "p4parser.y"
                               {}
#line 3691 "p4parser.tab.c"
    break;

  case 157:
#line 483 "p4parser.y"
                           {}
#line 3697 "p4parser.tab.c"
    break;

  case 158:
#line 484 "p4parser.y"
                                     {}
#line 3703 "p4parser.tab.c"
    break;

  case 159:
#line 488 "p4parser.y"
                             {}
#line 3709 "p4parser.tab.c"
    break;

  case 160:
#line 495 "p4parser.y"
              { EnterScope(subparser); }
#line 3715 "p4parser.tab.c"
    break;

  case 161:
#line 495 "p4parser.y"
                                                                          { ExitScope(subparser); }
#line 3721 "p4parser.tab.c"
    break;

  case 162:
#line 496 "p4parser.y"
                             {}
#line 3727 "p4parser.tab.c"
    break;

  case 163:
#line 501 "p4parser.y"
                                           {}
#line 3733 "p4parser.tab.c"
    break;

  case 164:
#line 502 "p4parser.y"
                                             {}
#line 3739 "p4parser.tab.c"
    break;

  case 165:
#line 506 "p4parser.y"
                                    {}
#line 3745 "p4parser.tab.c"
    break;

  case 166:
#line 507 "p4parser.y"
                                      {}
#line 3751 "p4parser.tab.c"
    break;

  case 167:
#line 508 "p4parser.y"
                                      {}
#line 3757 "p4parser.tab.c"
    break;

  case 168:
#line 509 "p4parser.y"
                                      {}
#line 3763 "p4parser.tab.c"
    break;

  case 169:
#line 514 "p4parser.y"
                          {}
#line 3769 "p4parser.tab.c"
    break;

  case 170:
#line 515 "p4parser.y"
                          {}
#line 3775 "p4parser.tab.c"
    break;

  case 171:
#line 516 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3784 "p4parser.tab.c"
    break;

  case 172:
#line 523 "p4parser.y"
                                    {}
#line 3790 "p4parser.tab.c"
    break;

  case 173:
#line 524 "p4parser.y"
                                      {}
#line 3796 "p4parser.tab.c"
    break;

  case 174:
#line 528 "p4parser.y"
                              {}
#line 3802 "p4parser.tab.c"
    break;

  case 175:
#line 530 "p4parser.y"
                                      {}
#line 3808 "p4parser.tab.c"
    break;

  case 176:
#line 534 "p4parser.y"
                                     {}
#line 3814 "p4parser.tab.c"
    break;

  case 177:
#line 535 "p4parser.y"
                                       {}
#line 3820 "p4parser.tab.c"
    break;

  case 178:
#line 539 "p4parser.y"
                                    {}
#line 3826 "p4parser.tab.c"
    break;

  case 179:
#line 540 "p4parser.y"
                                      {}
#line 3832 "p4parser.tab.c"
    break;

  case 180:
#line 541 "p4parser.y"
                                      {}
#line 3838 "p4parser.tab.c"
    break;

  case 181:
#line 542 "p4parser.y"
                                      {}
#line 3844 "p4parser.tab.c"
    break;

  case 182:
#line 543 "p4parser.y"
                                      {}
#line 3850 "p4parser.tab.c"
    break;

  case 183:
#line 544 "p4parser.y"
                                      {}
#line 3856 "p4parser.tab.c"
    break;

  case 184:
#line 545 "p4parser.y"
                                      {}
#line 3862 "p4parser.tab.c"
    break;

  case 185:
#line 549 "p4parser.y"
                           {}
#line 3868 "p4parser.tab.c"
    break;

  case 186:
#line 550 "p4parser.y"
                               {}
#line 3874 "p4parser.tab.c"
    break;

  case 187:
#line 554 "p4parser.y"
                                {}
#line 3880 "p4parser.tab.c"
    break;

  case 188:
#line 555 "p4parser.y"
                                  {}
#line 3886 "p4parser.tab.c"
    break;

  case 189:
#line 559 "p4parser.y"
                           {}
#line 3892 "p4parser.tab.c"
    break;

  case 190:
#line 560 "p4parser.y"
                       {}
#line 3898 "p4parser.tab.c"
    break;

  case 191:
#line 565 "p4parser.y"
                              {}
#line 3904 "p4parser.tab.c"
    break;

  case 192:
#line 569 "p4parser.y"
                               {}
#line 3910 "p4parser.tab.c"
    break;

  case 193:
#line 570 "p4parser.y"
                                 {}
#line 3916 "p4parser.tab.c"
    break;

  case 194:
#line 575 "p4parser.y"
      {}
#line 3922 "p4parser.tab.c"
    break;

  case 195:
#line 579 "p4parser.y"
                              {}
#line 3928 "p4parser.tab.c"
    break;

  case 196:
#line 580 "p4parser.y"
                                {}
#line 3934 "p4parser.tab.c"
    break;

  case 197:
#line 585 "p4parser.y"
                                {}
#line 3940 "p4parser.tab.c"
    break;

  case 198:
#line 586 "p4parser.y"
                                                    {}
#line 3946 "p4parser.tab.c"
    break;

  case 199:
#line 590 "p4parser.y"
                           {}
#line 3952 "p4parser.tab.c"
    break;

  case 200:
#line 591 "p4parser.y"
                                                        {}
#line 3958 "p4parser.tab.c"
    break;

  case 201:
#line 596 "p4parser.y"
                                 {}
#line 3964 "p4parser.tab.c"
    break;

  case 202:
#line 597 "p4parser.y"
                                   {}
#line 3970 "p4parser.tab.c"
    break;

  case 203:
#line 598 "p4parser.y"
                                  {}
#line 3976 "p4parser.tab.c"
    break;

  case 204:
#line 599 "p4parser.y"
                                       {}
#line 3982 "p4parser.tab.c"
    break;

  case 205:
#line 603 "p4parser.y"
                                {}
#line 3988 "p4parser.tab.c"
    break;

  case 206:
#line 604 "p4parser.y"
                                 {}
#line 3994 "p4parser.tab.c"
    break;

  case 207:
#line 605 "p4parser.y"
                                   {}
#line 4000 "p4parser.tab.c"
    break;

  case 208:
#line 606 "p4parser.y"
                                  {}
#line 4006 "p4parser.tab.c"
    break;

  case 209:
#line 607 "p4parser.y"
                                       {}
#line 4012 "p4parser.tab.c"
    break;

  case 210:
#line 613 "p4parser.y"
        {}
#line 4018 "p4parser.tab.c"
    break;

  case 211:
#line 616 "p4parser.y"
        {}
#line 4024 "p4parser.tab.c"
    break;

  case 212:
#line 619 "p4parser.y"
        {}
#line 4030 "p4parser.tab.c"
    break;

  case 213:
#line 626 "p4parser.y"
              { EnterScope(subparser); }
#line 4036 "p4parser.tab.c"
    break;

  case 214:
#line 628 "p4parser.y"
      { ExitScope(subparser); }
#line 4042 "p4parser.tab.c"
    break;

  case 215:
#line 629 "p4parser.y"
        {}
#line 4048 "p4parser.tab.c"
    break;

  case 216:
#line 634 "p4parser.y"
                     {}
#line 4054 "p4parser.tab.c"
    break;

  case 217:
#line 635 "p4parser.y"
                          {}
#line 4060 "p4parser.tab.c"
    break;

  case 218:
#line 636 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4069 "p4parser.tab.c"
    break;

  case 219:
#line 643 "p4parser.y"
           {}
#line 4075 "p4parser.tab.c"
    break;

  case 220:
#line 644 "p4parser.y"
                                                       {}
#line 4081 "p4parser.tab.c"
    break;

  case 221:
#line 648 "p4parser.y"
                             {}
#line 4087 "p4parser.tab.c"
    break;

  case 222:
#line 649 "p4parser.y"
                               {}
#line 4093 "p4parser.tab.c"
    break;

  case 223:
#line 650 "p4parser.y"
                               {}
#line 4099 "p4parser.tab.c"
    break;

  case 224:
#line 651 "p4parser.y"
                               {}
#line 4105 "p4parser.tab.c"
    break;

  case 225:
#line 652 "p4parser.y"
                               {}
#line 4111 "p4parser.tab.c"
    break;

  case 226:
#line 656 "p4parser.y"
                   {}
#line 4117 "p4parser.tab.c"
    break;

  case 227:
#line 663 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4126 "p4parser.tab.c"
    break;

  case 228:
#line 667 "p4parser.y"
                          {}
#line 4132 "p4parser.tab.c"
    break;

  case 229:
#line 668 "p4parser.y"
                { ReenterScope(subparser); }
#line 4138 "p4parser.tab.c"
    break;

  case 230:
#line 668 "p4parser.y"
                                                              { ExitScope(subparser); }
#line 4144 "p4parser.tab.c"
    break;

  case 235:
#line 678 "p4parser.y"
                                     {}
#line 4150 "p4parser.tab.c"
    break;

  case 236:
#line 679 "p4parser.y"
                                       {}
#line 4156 "p4parser.tab.c"
    break;

  case 237:
#line 684 "p4parser.y"
                               {}
#line 4162 "p4parser.tab.c"
    break;

  case 238:
#line 685 "p4parser.y"
                                      {}
#line 4168 "p4parser.tab.c"
    break;

  case 239:
#line 689 "p4parser.y"
                                               {}
#line 4174 "p4parser.tab.c"
    break;

  case 240:
#line 690 "p4parser.y"
                                                          {}
#line 4180 "p4parser.tab.c"
    break;

  case 241:
#line 691 "p4parser.y"
                                 {}
#line 4186 "p4parser.tab.c"
    break;

  case 242:
#line 692 "p4parser.y"
                                        {}
#line 4192 "p4parser.tab.c"
    break;

  case 244:
#line 702 "p4parser.y"
                                     {}
#line 4198 "p4parser.tab.c"
    break;

  case 245:
#line 703 "p4parser.y"
                                       {}
#line 4204 "p4parser.tab.c"
    break;

  case 246:
#line 704 "p4parser.y"
                                       {}
#line 4210 "p4parser.tab.c"
    break;

  case 247:
#line 705 "p4parser.y"
                                       {}
#line 4216 "p4parser.tab.c"
    break;

  case 248:
#line 706 "p4parser.y"
                                       {}
#line 4222 "p4parser.tab.c"
    break;

  case 249:
#line 710 "p4parser.y"
                                     {}
#line 4228 "p4parser.tab.c"
    break;

  case 250:
#line 711 "p4parser.y"
                                       {}
#line 4234 "p4parser.tab.c"
    break;

  case 251:
#line 715 "p4parser.y"
                                     {}
#line 4240 "p4parser.tab.c"
    break;

  case 252:
#line 716 "p4parser.y"
                                       {}
#line 4246 "p4parser.tab.c"
    break;

  case 253:
#line 720 "p4parser.y"
                                     {}
#line 4252 "p4parser.tab.c"
    break;

  case 254:
#line 724 "p4parser.y"
                                              {}
#line 4258 "p4parser.tab.c"
    break;

  case 255:
#line 728 "p4parser.y"
                                                    {}
#line 4264 "p4parser.tab.c"
    break;

  case 256:
#line 729 "p4parser.y"
                                                      {}
#line 4270 "p4parser.tab.c"
    break;

  case 257:
#line 733 "p4parser.y"
                                              {}
#line 4276 "p4parser.tab.c"
    break;

  case 258:
#line 737 "p4parser.y"
           {}
#line 4282 "p4parser.tab.c"
    break;

  case 259:
#line 738 "p4parser.y"
             {}
#line 4288 "p4parser.tab.c"
    break;

  case 260:
#line 739 "p4parser.y"
             {}
#line 4294 "p4parser.tab.c"
    break;

  case 261:
#line 740 "p4parser.y"
             {}
#line 4300 "p4parser.tab.c"
    break;

  case 262:
#line 741 "p4parser.y"
             {}
#line 4306 "p4parser.tab.c"
    break;

  case 263:
#line 743 "p4parser.y"
      {}
#line 4312 "p4parser.tab.c"
    break;

  case 264:
#line 745 "p4parser.y"
      {}
#line 4318 "p4parser.tab.c"
    break;

  case 265:
#line 747 "p4parser.y"
      {}
#line 4324 "p4parser.tab.c"
    break;

  case 266:
#line 750 "p4parser.y"
      {}
#line 4330 "p4parser.tab.c"
    break;

  case 267:
#line 752 "p4parser.y"
      {}
#line 4336 "p4parser.tab.c"
    break;

  case 268:
#line 754 "p4parser.y"
      {}
#line 4342 "p4parser.tab.c"
    break;

  case 269:
#line 758 "p4parser.y"
                {}
#line 4348 "p4parser.tab.c"
    break;

  case 270:
#line 759 "p4parser.y"
                  {}
#line 4354 "p4parser.tab.c"
    break;

  case 271:
#line 760 "p4parser.y"
                  {}
#line 4360 "p4parser.tab.c"
    break;

  case 272:
#line 765 "p4parser.y"
                              {}
#line 4366 "p4parser.tab.c"
    break;

  case 273:
#line 766 "p4parser.y"
                                {}
#line 4372 "p4parser.tab.c"
    break;

  case 274:
#line 770 "p4parser.y"
            { EnterScope(subparser); }
#line 4378 "p4parser.tab.c"
    break;

  case 275:
#line 770 "p4parser.y"
                                                         { ExitReentrantScope(subparser); }
#line 4384 "p4parser.tab.c"
    break;

  case 276:
#line 770 "p4parser.y"
                                                                                                    {}
#line 4390 "p4parser.tab.c"
    break;

  case 277:
#line 774 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4402 "p4parser.tab.c"
    break;

  case 278:
#line 781 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4410 "p4parser.tab.c"
    break;

  case 279:
#line 787 "p4parser.y"
                                {}
#line 4416 "p4parser.tab.c"
    break;

  case 280:
#line 788 "p4parser.y"
                                  {}
#line 4422 "p4parser.tab.c"
    break;

  case 281:
#line 790 "p4parser.y"
                                  {}
#line 4428 "p4parser.tab.c"
    break;

  case 282:
#line 791 "p4parser.y"
                                       {}
#line 4434 "p4parser.tab.c"
    break;

  case 283:
#line 795 "p4parser.y"
                                   {}
#line 4440 "p4parser.tab.c"
    break;

  case 284:
#line 796 "p4parser.y"
                                     {}
#line 4446 "p4parser.tab.c"
    break;

  case 285:
#line 797 "p4parser.y"
                                       {}
#line 4452 "p4parser.tab.c"
    break;

  case 286:
#line 801 "p4parser.y"
                                {}
#line 4458 "p4parser.tab.c"
    break;

  case 287:
#line 802 "p4parser.y"
                                  {}
#line 4464 "p4parser.tab.c"
    break;

  case 288:
#line 803 "p4parser.y"
                                       {}
#line 4470 "p4parser.tab.c"
    break;

  case 289:
#line 809 "p4parser.y"
                                       {}
#line 4476 "p4parser.tab.c"
    break;

  case 290:
#line 810 "p4parser.y"
                                           {}
#line 4482 "p4parser.tab.c"
    break;

  case 291:
#line 814 "p4parser.y"
                               {}
#line 4488 "p4parser.tab.c"
    break;

  case 292:
#line 815 "p4parser.y"
                                       {}
#line 4494 "p4parser.tab.c"
    break;

  case 293:
#line 816 "p4parser.y"
                                       {}
#line 4500 "p4parser.tab.c"
    break;

  case 294:
#line 817 "p4parser.y"
                                       {}
#line 4506 "p4parser.tab.c"
    break;

  case 295:
#line 818 "p4parser.y"
                                       {}
#line 4512 "p4parser.tab.c"
    break;

  case 296:
#line 822 "p4parser.y"
                                     {}
#line 4518 "p4parser.tab.c"
    break;

  case 297:
#line 823 "p4parser.y"
                                       {}
#line 4524 "p4parser.tab.c"
    break;

  case 298:
#line 824 "p4parser.y"
                                       {}
#line 4530 "p4parser.tab.c"
    break;

  case 299:
#line 825 "p4parser.y"
                                       {}
#line 4536 "p4parser.tab.c"
    break;

  case 300:
#line 830 "p4parser.y"
              { ReenterScope(subparser); }
#line 4542 "p4parser.tab.c"
    break;

  case 301:
#line 831 "p4parser.y"
                      { ExitScope(subparser); }
#line 4548 "p4parser.tab.c"
    break;

  case 302:
#line 833 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4557 "p4parser.tab.c"
    break;

  case 303:
#line 841 "p4parser.y"
              { ReenterScope(subparser); }
#line 4563 "p4parser.tab.c"
    break;

  case 304:
#line 843 "p4parser.y"
      { ExitScope(subparser); }
#line 4569 "p4parser.tab.c"
    break;

  case 305:
#line 844 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4578 "p4parser.tab.c"
    break;

  case 306:
#line 852 "p4parser.y"
              { ReenterScope(subparser); }
#line 4584 "p4parser.tab.c"
    break;

  case 307:
#line 854 "p4parser.y"
      { ExitScope(subparser); }
#line 4590 "p4parser.tab.c"
    break;

  case 308:
#line 854 "p4parser.y"
                                        {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4599 "p4parser.tab.c"
    break;

  case 309:
#line 861 "p4parser.y"
                                     {}
#line 4605 "p4parser.tab.c"
    break;

  case 310:
#line 862 "p4parser.y"
                                       {}
#line 4611 "p4parser.tab.c"
    break;

  case 311:
#line 866 "p4parser.y"
                                           {}
#line 4617 "p4parser.tab.c"
    break;

  case 312:
#line 871 "p4parser.y"
                  {}
#line 4623 "p4parser.tab.c"
    break;

  case 313:
#line 872 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4632 "p4parser.tab.c"
    break;

  case 314:
#line 876 "p4parser.y"
                                       {}
#line 4638 "p4parser.tab.c"
    break;

  case 315:
#line 877 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4647 "p4parser.tab.c"
    break;

  case 316:
#line 884 "p4parser.y"
                            {}
#line 4653 "p4parser.tab.c"
    break;

  case 317:
#line 885 "p4parser.y"
                                                        {}
#line 4659 "p4parser.tab.c"
    break;

  case 318:
#line 889 "p4parser.y"
                               {}
#line 4665 "p4parser.tab.c"
    break;

  case 319:
#line 894 "p4parser.y"
        {}
#line 4671 "p4parser.tab.c"
    break;

  case 320:
#line 899 "p4parser.y"
        {}
#line 4677 "p4parser.tab.c"
    break;

  case 321:
#line 904 "p4parser.y"
                            {}
#line 4683 "p4parser.tab.c"
    break;

  case 322:
#line 905 "p4parser.y"
                                {}
#line 4689 "p4parser.tab.c"
    break;

  case 323:
#line 909 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4698 "p4parser.tab.c"
    break;

  case 324:
#line 913 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4707 "p4parser.tab.c"
    break;

  case 325:
#line 917 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4716 "p4parser.tab.c"
    break;

  case 326:
#line 921 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4725 "p4parser.tab.c"
    break;

  case 327:
#line 932 "p4parser.y"
        {}
#line 4731 "p4parser.tab.c"
    break;

  case 328:
#line 934 "p4parser.y"
        {}
#line 4737 "p4parser.tab.c"
    break;

  case 329:
#line 939 "p4parser.y"
        {}
#line 4743 "p4parser.tab.c"
    break;

  case 330:
#line 941 "p4parser.y"
        {}
#line 4749 "p4parser.tab.c"
    break;

  case 331:
#line 945 "p4parser.y"
                   {}
#line 4755 "p4parser.tab.c"
    break;

  case 332:
#line 949 "p4parser.y"
                   {}
#line 4761 "p4parser.tab.c"
    break;

  case 333:
#line 953 "p4parser.y"
                                {}
#line 4767 "p4parser.tab.c"
    break;

  case 334:
#line 954 "p4parser.y"
                                  {}
#line 4773 "p4parser.tab.c"
    break;

  case 335:
#line 959 "p4parser.y"
        {}
#line 4779 "p4parser.tab.c"
    break;

  case 336:
#line 961 "p4parser.y"
        {}
#line 4785 "p4parser.tab.c"
    break;

  case 337:
#line 966 "p4parser.y"
                                                              {}
#line 4791 "p4parser.tab.c"
    break;

  case 338:
#line 970 "p4parser.y"
                                     {}
#line 4797 "p4parser.tab.c"
    break;

  case 339:
#line 971 "p4parser.y"
                                       {}
#line 4803 "p4parser.tab.c"
    break;

  case 340:
#line 972 "p4parser.y"
                                       {}
#line 4809 "p4parser.tab.c"
    break;

  case 341:
#line 973 "p4parser.y"
                                       {}
#line 4815 "p4parser.tab.c"
    break;

  case 342:
#line 974 "p4parser.y"
                                       {}
#line 4821 "p4parser.tab.c"
    break;

  case 343:
#line 975 "p4parser.y"
                                       {}
#line 4827 "p4parser.tab.c"
    break;

  case 344:
#line 976 "p4parser.y"
                                       {}
#line 4833 "p4parser.tab.c"
    break;

  case 345:
#line 977 "p4parser.y"
                                       {}
#line 4839 "p4parser.tab.c"
    break;

  case 346:
#line 981 "p4parser.y"
                           {}
#line 4845 "p4parser.tab.c"
    break;

  case 347:
#line 982 "p4parser.y"
                             {}
#line 4851 "p4parser.tab.c"
    break;

  case 348:
#line 986 "p4parser.y"
                                          {}
#line 4857 "p4parser.tab.c"
    break;

  case 349:
#line 987 "p4parser.y"
                                            {}
#line 4863 "p4parser.tab.c"
    break;

  case 350:
#line 991 "p4parser.y"
                                                                  {}
#line 4869 "p4parser.tab.c"
    break;

  case 351:
#line 995 "p4parser.y"
                             {}
#line 4875 "p4parser.tab.c"
    break;

  case 352:
#line 996 "p4parser.y"
                               {}
#line 4881 "p4parser.tab.c"
    break;

  case 353:
#line 1000 "p4parser.y"
                                     {}
#line 4887 "p4parser.tab.c"
    break;

  case 354:
#line 1001 "p4parser.y"
                                       {}
#line 4893 "p4parser.tab.c"
    break;

  case 355:
#line 1005 "p4parser.y"
                             {}
#line 4899 "p4parser.tab.c"
    break;

  case 356:
#line 1006 "p4parser.y"
                               {}
#line 4905 "p4parser.tab.c"
    break;

  case 357:
#line 1010 "p4parser.y"
                             {}
#line 4911 "p4parser.tab.c"
    break;

  case 358:
#line 1011 "p4parser.y"
                               {}
#line 4917 "p4parser.tab.c"
    break;

  case 359:
#line 1012 "p4parser.y"
                               {}
#line 4923 "p4parser.tab.c"
    break;

  case 360:
#line 1013 "p4parser.y"
                               {}
#line 4929 "p4parser.tab.c"
    break;

  case 361:
#line 1020 "p4parser.y"
                           { EnterScope(subparser); }
#line 4935 "p4parser.tab.c"
    break;

  case 362:
#line 1020 "p4parser.y"
                                                                        { ExitScope(subparser); }
#line 4941 "p4parser.tab.c"
    break;

  case 363:
#line 1021 "p4parser.y"
          {}
#line 4947 "p4parser.tab.c"
    break;

  case 364:
#line 1025 "p4parser.y"
                                       {}
#line 4953 "p4parser.tab.c"
    break;

  case 365:
#line 1026 "p4parser.y"
                                         {}
#line 4959 "p4parser.tab.c"
    break;

  case 366:
#line 1031 "p4parser.y"
        {}
#line 4965 "p4parser.tab.c"
    break;

  case 367:
#line 1033 "p4parser.y"
        {}
#line 4971 "p4parser.tab.c"
    break;

  case 368:
#line 1035 "p4parser.y"
        {}
#line 4977 "p4parser.tab.c"
    break;

  case 369:
#line 1037 "p4parser.y"
        {}
#line 4983 "p4parser.tab.c"
    break;

  case 370:
#line 1041 "p4parser.y"
                                       {}
#line 4989 "p4parser.tab.c"
    break;

  case 371:
#line 1042 "p4parser.y"
                                         {}
#line 4995 "p4parser.tab.c"
    break;

  case 372:
#line 1047 "p4parser.y"
                                         {}
#line 5001 "p4parser.tab.c"
    break;

  case 373:
#line 1051 "p4parser.y"
           {}
#line 5007 "p4parser.tab.c"
    break;

  case 374:
#line 1053 "p4parser.y"
        {}
#line 5013 "p4parser.tab.c"
    break;

  case 376:
#line 1062 "p4parser.y"
        {}
#line 5019 "p4parser.tab.c"
    break;

  case 377:
#line 1064 "p4parser.y"
        {}
#line 5025 "p4parser.tab.c"
    break;

  case 378:
#line 1069 "p4parser.y"
        {}
#line 5031 "p4parser.tab.c"
    break;

  case 379:
#line 1073 "p4parser.y"
                                   {}
#line 5037 "p4parser.tab.c"
    break;

  case 380:
#line 1074 "p4parser.y"
                                     {}
#line 5043 "p4parser.tab.c"
    break;

  case 381:
#line 1080 "p4parser.y"
                                                             { EnterScope(subparser); }
#line 5049 "p4parser.tab.c"
    break;

  case 382:
#line 1080 "p4parser.y"
                                                                                                       {
        saveBaseType(subparser, getNodeAt(subparser, 7));
        bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 6));
        ExitScope(subparser);
      }
#line 5059 "p4parser.tab.c"
    break;

  case 383:
#line 1090 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5068 "p4parser.tab.c"
    break;

  case 384:
#line 1094 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5077 "p4parser.tab.c"
    break;

  case 385:
#line 1102 "p4parser.y"
                                     {}
#line 5083 "p4parser.tab.c"
    break;

  case 386:
#line 1106 "p4parser.y"
                                     {}
#line 5089 "p4parser.tab.c"
    break;

  case 387:
#line 1107 "p4parser.y"
                                          {}
#line 5095 "p4parser.tab.c"
    break;

  case 388:
#line 1111 "p4parser.y"
                                        {}
#line 5101 "p4parser.tab.c"
    break;

  case 389:
#line 1117 "p4parser.y"
                      { ReenterScope(subparser); }
#line 5107 "p4parser.tab.c"
    break;

  case 390:
#line 1117 "p4parser.y"
                                                                  { ExitScope(subparser); }
#line 5113 "p4parser.tab.c"
    break;

  case 391:
#line 1121 "p4parser.y"
                                       {}
#line 5119 "p4parser.tab.c"
    break;

  case 392:
#line 1122 "p4parser.y"
                                         {}
#line 5125 "p4parser.tab.c"
    break;

  case 393:
#line 1126 "p4parser.y"
                                       {}
#line 5131 "p4parser.tab.c"
    break;

  case 394:
#line 1127 "p4parser.y"
                                           {}
#line 5137 "p4parser.tab.c"
    break;

  case 395:
#line 1131 "p4parser.y"
                                       {}
#line 5143 "p4parser.tab.c"
    break;

  case 396:
#line 1132 "p4parser.y"
                                            {}
#line 5149 "p4parser.tab.c"
    break;

  case 397:
#line 1133 "p4parser.y"
                                              {}
#line 5155 "p4parser.tab.c"
    break;

  case 398:
#line 1137 "p4parser.y"
                                       {}
#line 5161 "p4parser.tab.c"
    break;

  case 399:
#line 1138 "p4parser.y"
                                         {}
#line 5167 "p4parser.tab.c"
    break;

  case 400:
#line 1139 "p4parser.y"
                                           {}
#line 5173 "p4parser.tab.c"
    break;

  case 401:
#line 1143 "p4parser.y"
                                       {}
#line 5179 "p4parser.tab.c"
    break;

  case 402:
#line 1144 "p4parser.y"
                                         {}
#line 5185 "p4parser.tab.c"
    break;

  case 403:
#line 1148 "p4parser.y"
        {}
#line 5191 "p4parser.tab.c"
    break;

  case 404:
#line 1148 "p4parser.y"
                {}
#line 5197 "p4parser.tab.c"
    break;

  case 405:
#line 1152 "p4parser.y"
                                       {}
#line 5203 "p4parser.tab.c"
    break;

  case 406:
#line 1153 "p4parser.y"
                                         {}
#line 5209 "p4parser.tab.c"
    break;

  case 407:
#line 1154 "p4parser.y"
                                         {}
#line 5215 "p4parser.tab.c"
    break;

  case 408:
#line 1155 "p4parser.y"
                                       {}
#line 5221 "p4parser.tab.c"
    break;

  case 409:
#line 1159 "p4parser.y"
                                            {}
#line 5227 "p4parser.tab.c"
    break;

  case 410:
#line 1160 "p4parser.y"
                                                      {}
#line 5233 "p4parser.tab.c"
    break;

  case 411:
#line 1163 "p4parser.y"
                                       {}
#line 5239 "p4parser.tab.c"
    break;

  case 412:
#line 1164 "p4parser.y"
                                         {}
#line 5245 "p4parser.tab.c"
    break;

  case 413:
#line 1165 "p4parser.y"
                                         {}
#line 5251 "p4parser.tab.c"
    break;

  case 414:
#line 1166 "p4parser.y"
                                         {}
#line 5257 "p4parser.tab.c"
    break;

  case 415:
#line 1167 "p4parser.y"
                                         {}
#line 5263 "p4parser.tab.c"
    break;

  case 416:
#line 1168 "p4parser.y"
                                         {}
#line 5269 "p4parser.tab.c"
    break;

  case 417:
#line 1169 "p4parser.y"
                                         {}
#line 5275 "p4parser.tab.c"
    break;

  case 418:
#line 1170 "p4parser.y"
                                                     {}
#line 5281 "p4parser.tab.c"
    break;

  case 419:
#line 1171 "p4parser.y"
                                                                 {}
#line 5287 "p4parser.tab.c"
    break;

  case 420:
#line 1172 "p4parser.y"
                                                 {}
#line 5293 "p4parser.tab.c"
    break;

  case 421:
#line 1173 "p4parser.y"
                                                 {}
#line 5299 "p4parser.tab.c"
    break;

  case 422:
#line 1174 "p4parser.y"
                                                 {}
#line 5305 "p4parser.tab.c"
    break;

  case 423:
#line 1175 "p4parser.y"
                                         {}
#line 5311 "p4parser.tab.c"
    break;

  case 424:
#line 1176 "p4parser.y"
                                                {}
#line 5317 "p4parser.tab.c"
    break;

  case 425:
#line 1177 "p4parser.y"
                                           {}
#line 5323 "p4parser.tab.c"
    break;

  case 426:
#line 1178 "p4parser.y"
                                          {}
#line 5329 "p4parser.tab.c"
    break;

  case 427:
#line 1180 "p4parser.y"
        {}
#line 5335 "p4parser.tab.c"
    break;

  case 428:
#line 1182 "p4parser.y"
        {}
#line 5341 "p4parser.tab.c"
    break;

  case 429:
#line 1183 "p4parser.y"
                                         {}
#line 5347 "p4parser.tab.c"
    break;

  case 430:
#line 1184 "p4parser.y"
                                         {}
#line 5353 "p4parser.tab.c"
    break;

  case 431:
#line 1185 "p4parser.y"
                                         {}
#line 5359 "p4parser.tab.c"
    break;

  case 432:
#line 1186 "p4parser.y"
                                         {}
#line 5365 "p4parser.tab.c"
    break;

  case 433:
#line 1187 "p4parser.y"
                                          {}
#line 5371 "p4parser.tab.c"
    break;

  case 434:
#line 1188 "p4parser.y"
                                           {}
#line 5377 "p4parser.tab.c"
    break;

  case 435:
#line 1189 "p4parser.y"
                                            {}
#line 5383 "p4parser.tab.c"
    break;

  case 436:
#line 1190 "p4parser.y"
                                             {}
#line 5389 "p4parser.tab.c"
    break;

  case 437:
#line 1191 "p4parser.y"
                                        {}
#line 5395 "p4parser.tab.c"
    break;

  case 438:
#line 1193 "p4parser.y"
        {}
#line 5401 "p4parser.tab.c"
    break;

  case 439:
#line 1194 "p4parser.y"
                                       {}
#line 5407 "p4parser.tab.c"
    break;

  case 440:
#line 1195 "p4parser.y"
                                       {}
#line 5413 "p4parser.tab.c"
    break;

  case 441:
#line 1197 "p4parser.y"
                                         {}
#line 5419 "p4parser.tab.c"
    break;

  case 442:
#line 1198 "p4parser.y"
                                             {}
#line 5425 "p4parser.tab.c"
    break;

  case 443:
#line 1200 "p4parser.y"
                                       {}
#line 5431 "p4parser.tab.c"
    break;

  case 444:
#line 1201 "p4parser.y"
                                       {}
#line 5437 "p4parser.tab.c"
    break;

  case 445:
#line 1202 "p4parser.y"
                                             {}
#line 5443 "p4parser.tab.c"
    break;

  case 446:
#line 1203 "p4parser.y"
                                             {}
#line 5449 "p4parser.tab.c"
    break;

  case 447:
#line 1204 "p4parser.y"
                                            {}
#line 5455 "p4parser.tab.c"
    break;

  case 448:
#line 1205 "p4parser.y"
                                       {}
#line 5461 "p4parser.tab.c"
    break;

  case 449:
#line 1206 "p4parser.y"
                                        {}
#line 5467 "p4parser.tab.c"
    break;

  case 450:
#line 1207 "p4parser.y"
                                       {}
#line 5473 "p4parser.tab.c"
    break;

  case 451:
#line 1208 "p4parser.y"
                                                      {}
#line 5479 "p4parser.tab.c"
    break;

  case 452:
#line 1209 "p4parser.y"
                         {}
#line 5485 "p4parser.tab.c"
    break;

  case 454:
#line 1213 "p4parser.y"
        {}
#line 5491 "p4parser.tab.c"
    break;

  case 455:
#line 1215 "p4parser.y"
        {}
#line 5497 "p4parser.tab.c"
    break;

  case 456:
#line 1217 "p4parser.y"
        {}
#line 5503 "p4parser.tab.c"
    break;

  case 457:
#line 1218 "p4parser.y"
                                                      {}
#line 5509 "p4parser.tab.c"
    break;

  case 458:
#line 1222 "p4parser.y"
                                       {}
#line 5515 "p4parser.tab.c"
    break;

  case 459:
#line 1223 "p4parser.y"
                                         {}
#line 5521 "p4parser.tab.c"
    break;

  case 460:
#line 1224 "p4parser.y"
                                         {}
#line 5527 "p4parser.tab.c"
    break;

  case 461:
#line 1225 "p4parser.y"
                                         {}
#line 5533 "p4parser.tab.c"
    break;

  case 462:
#line 1226 "p4parser.y"
                                         {}
#line 5539 "p4parser.tab.c"
    break;

  case 463:
#line 1227 "p4parser.y"
                                         {}
#line 5545 "p4parser.tab.c"
    break;

  case 464:
#line 1228 "p4parser.y"
                                         {}
#line 5551 "p4parser.tab.c"
    break;

  case 465:
#line 1229 "p4parser.y"
                                                             {}
#line 5557 "p4parser.tab.c"
    break;

  case 466:
#line 1230 "p4parser.y"
                                                                         {}
#line 5563 "p4parser.tab.c"
    break;

  case 467:
#line 1231 "p4parser.y"
                                                 {}
#line 5569 "p4parser.tab.c"
    break;

  case 468:
#line 1232 "p4parser.y"
                                         {}
#line 5575 "p4parser.tab.c"
    break;

  case 469:
#line 1233 "p4parser.y"
                                                {}
#line 5581 "p4parser.tab.c"
    break;

  case 470:
#line 1234 "p4parser.y"
                                           {}
#line 5587 "p4parser.tab.c"
    break;

  case 471:
#line 1235 "p4parser.y"
                                          {}
#line 5593 "p4parser.tab.c"
    break;

  case 472:
#line 1237 "p4parser.y"
        {}
#line 5599 "p4parser.tab.c"
    break;

  case 473:
#line 1239 "p4parser.y"
        {}
#line 5605 "p4parser.tab.c"
    break;

  case 474:
#line 1240 "p4parser.y"
                                                 {}
#line 5611 "p4parser.tab.c"
    break;

  case 475:
#line 1241 "p4parser.y"
                                                 {}
#line 5617 "p4parser.tab.c"
    break;

  case 476:
#line 1242 "p4parser.y"
                                                 {}
#line 5623 "p4parser.tab.c"
    break;

  case 477:
#line 1243 "p4parser.y"
                                                 {}
#line 5629 "p4parser.tab.c"
    break;

  case 478:
#line 1244 "p4parser.y"
                                                  {}
#line 5635 "p4parser.tab.c"
    break;

  case 479:
#line 1245 "p4parser.y"
                                                   {}
#line 5641 "p4parser.tab.c"
    break;

  case 480:
#line 1246 "p4parser.y"
                                                    {}
#line 5647 "p4parser.tab.c"
    break;

  case 481:
#line 1247 "p4parser.y"
                                                     {}
#line 5653 "p4parser.tab.c"
    break;

  case 482:
#line 1248 "p4parser.y"
                                                {}
#line 5659 "p4parser.tab.c"
    break;

  case 483:
#line 1250 "p4parser.y"
        {}
#line 5665 "p4parser.tab.c"
    break;

  case 484:
#line 1251 "p4parser.y"
                                               {}
#line 5671 "p4parser.tab.c"
    break;

  case 485:
#line 1252 "p4parser.y"
                                               {}
#line 5677 "p4parser.tab.c"
    break;

  case 486:
#line 1254 "p4parser.y"
                                         {}
#line 5683 "p4parser.tab.c"
    break;

  case 487:
#line 1255 "p4parser.y"
                                                     {}
#line 5689 "p4parser.tab.c"
    break;

  case 488:
#line 1256 "p4parser.y"
                                               {}
#line 5695 "p4parser.tab.c"
    break;

  case 489:
#line 1257 "p4parser.y"
                                               {}
#line 5701 "p4parser.tab.c"
    break;

  case 490:
#line 1258 "p4parser.y"
                                                     {}
#line 5707 "p4parser.tab.c"
    break;

  case 491:
#line 1259 "p4parser.y"
                                                     {}
#line 5713 "p4parser.tab.c"
    break;

  case 492:
#line 1260 "p4parser.y"
                                                    {}
#line 5719 "p4parser.tab.c"
    break;

  case 493:
#line 1261 "p4parser.y"
                                               {}
#line 5725 "p4parser.tab.c"
    break;

  case 494:
#line 1262 "p4parser.y"
                                                {}
#line 5731 "p4parser.tab.c"
    break;

  case 495:
#line 1263 "p4parser.y"
                                               {}
#line 5737 "p4parser.tab.c"
    break;

  case 496:
#line 1264 "p4parser.y"
                                                              {}
#line 5743 "p4parser.tab.c"
    break;

  case 497:
#line 1265 "p4parser.y"
                                 {}
#line 5749 "p4parser.tab.c"
    break;

  case 499:
#line 1269 "p4parser.y"
        {}
#line 5755 "p4parser.tab.c"
    break;

  case 500:
#line 1271 "p4parser.y"
        {}
#line 5761 "p4parser.tab.c"
    break;

  case 501:
#line 1273 "p4parser.y"
        {}
#line 5767 "p4parser.tab.c"
    break;

  case 502:
#line 1274 "p4parser.y"
                                                      {}
#line 5773 "p4parser.tab.c"
    break;


#line 5777 "p4parser.tab.c"

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
#line 1302 "p4parser.y"


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
