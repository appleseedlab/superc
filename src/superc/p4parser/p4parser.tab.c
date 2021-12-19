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
#define YYLAST   3937

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  155
/* YYNRULES -- Number of rules.  */
#define YYNRULES  487
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  876

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
     413,   417,   418,   422,   426,   427,   431,   432,   436,   437,
     441,   442,   443,   444,   448,   449,   448,   457,   459,   462,
     465,   471,   476,   477,   481,   482,   486,   487,   491,   497,
     498,   497,   504,   505,   509,   510,   511,   512,   517,   518,
     516,   526,   527,   531,   531,   537,   538,   542,   543,   544,
     545,   546,   547,   548,   552,   552,   557,   558,   562,   563,
     567,   572,   573,   577,   582,   583,   587,   589,   593,   594,
     599,   600,   601,   602,   606,   607,   608,   609,   610,   614,
     617,   620,   628,   635,   636,   634,   644,   645,   649,   650,
     651,   652,   653,   657,   664,   668,   663,   670,   671,   675,
     679,   680,   685,   684,   690,   691,   692,   692,   697,   703,
     704,   705,   706,   707,   711,   712,   716,   717,   721,   725,
     729,   730,   734,   738,   739,   740,   741,   742,   743,   745,
     747,   750,   752,   754,   759,   760,   761,   766,   767,   771,
     775,   782,   788,   789,   791,   792,   796,   797,   798,   802,
     803,   804,   810,   811,   815,   816,   817,   818,   819,   823,
     824,   825,   826,   830,   830,   830,   839,   848,   848,   848,
     856,   857,   861,   866,   865,   871,   871,   879,   880,   884,
     888,   893,   899,   900,   904,   908,   912,   916,   926,   928,
     933,   935,   940,   944,   948,   949,   953,   955,   961,   965,
     966,   967,   968,   969,   970,   971,   972,   976,   976,   981,
     982,   986,   990,   991,   995,   996,  1000,  1001,  1005,  1006,
    1007,  1008,  1014,  1020,  1021,  1025,  1027,  1029,  1031,  1036,
    1037,  1041,  1046,  1047,  1052,  1056,  1058,  1063,  1068,  1069,
    1075,  1084,  1088,  1095,  1100,  1101,  1105,  1111,  1115,  1116,
    1120,  1121,  1125,  1126,  1127,  1131,  1132,  1133,  1137,  1138,
    1142,  1142,  1146,  1147,  1148,  1149,  1153,  1154,  1157,  1158,
    1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  1171,  1172,  1173,  1175,  1177,  1178,  1179,  1180,
    1181,  1182,  1183,  1184,  1185,  1186,  1188,  1189,  1190,  1192,
    1194,  1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,  1203,
    1205,  1206,  1208,  1210,  1212,  1216,  1217,  1218,  1219,  1220,
    1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,
    1232,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,
    1243,  1245,  1246,  1247,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1290,  1290,  1291,  1291
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
  "annotationToken", "kvList", "kvPair", "parameterList",
  "nonEmptyParameterList", "parameter", "direction",
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
  "controlBody", "externDeclaration", "$@11", "$@12",
  "externFunctionDeclaration", "methodPrototypes", "functionPrototype",
  "$@13", "methodPrototype", "$@14", "constructorMethodPrototype",
  "typeRef", "namedType", "prefixedType", "typeName", "tupleType",
  "headerStackType", "specializedType", "baseType", "typeOrVoid",
  "optTypeParameters", "typeParameters", "typeParameterList", "typeArg",
  "typeArgumentList", "realTypeArg", "realTypeArgumentList",
  "typeDeclaration", "derivedTypeDeclaration", "headerTypeDeclaration",
  "$@15", "$@16", "structTypeDeclaration", "headerUnionDeclaration",
  "$@17", "$@18", "structFieldList", "structField", "enumDeclaration",
  "$@19", "$@20", "specifiedIdentifierList", "specifiedIdentifier",
  "errorDeclaration", "matchKindDeclaration", "identifierList",
  "typedefDeclaration", "assignmentOrMethodCallStatement",
  "methodCallStatements", "emptyStatement", "exitStatement",
  "returnStatement", "conditionalStatement", "directApplication",
  "statement", "blockStatement", "$@21", "statOrDeclList",
  "switchStatement", "switchCases", "switchCase", "switchLabel",
  "statementOrDeclaration", "tableDeclaration", "tablePropertyList",
  "tableProperty", "keyElementList", "keyElement", "actionList", "action",
  "actionRef", "entry", "entriesList", "actionDeclaration",
  "variableDeclaration", "constantDeclaration", "optInitializer",
  "initializer", "functionDeclaration", "argumentList", "nonEmptyArgList",
  "argument", "expressionList", "prefixedNonTypeName", "dot_name", "$@22",
  "lvalue", "lvalueExpression", "expression", "invokingExpression",
  "nonBraceExpression", "l_angle", "r_angle", YY_NULLPTR
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

#define YYPACT_NINF (-762)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-386)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -762,    29,  -762,   679,  -762,  -762,  -762,   383,  -762,    60,
      14,    60,    52,  -762,    60,    60,  -762,  -762,  -762,  -762,
     833,  1616,  -762,    15,  -762,    36,  -762,    77,  -762,   161,
    -762,  -762,    58,    90,  -762,   256,  -762,  -762,   108,  -762,
     383,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,    97,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   211,  -762,  -762,   -29,   383,   -25,   383,   883,
     -20,   383,   135,   383,  1576,   963,   383,   383,  1616,   383,
     383,   383,  1616,  -762,  -762,   177,  -762,  -762,   219,  -762,
    -762,  -762,   141,   160,    58,  -762,  1474,  2323,   883,  2323,
      60,  -762,  1876,  -762,  2323,   278,  -762,   136,  2323,   278,
     139,  -762,  -762,  -762,  -762,  -762,   232,  2323,   278,   189,
     383,  -762,    -9,  -762,   383,   204,   185,   200,   205,  -762,
    -762,  -762,    81,   383,   383,  -762,  -762,    60,   383,   383,
    1474,   -40,   214,   221,  -762,   233,  -762,  -762,  2323,  2323,
    2323,  1925,  1264,  2323,  -762,  -762,  -762,  -762,   223,  -762,
    -762,   235,   238,   456,   257,   -13,  -762,   265,   229,  -762,
    3605,  -762,  -762,  2791,   232,  2828,  -762,  -762,   383,   277,
     289,   266,  -762,   297,  3605,  1703,  2865,  -762,  -762,  -762,
    -762,   383,  2902,  -762,  -762,   883,  -762,  2939,  -762,   219,
     280,    60,   310,  -762,    60,  -762,  -762,    60,    60,  -762,
    -762,    60,    60,   311,  -762,  -762,   312,  -762,  -762,  -762,
     135,  -762,    58,  -762,    62,  -762,    66,    66,    66,   154,
     158,   223,   319,   275,   226,  2976,    66,   383,  2323,  -762,
    1474,  -762,  -762,   383,  2127,  2323,  2323,  2323,  2323,  2323,
    2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,
    2323,  2323,  2323,  2323,   325,  1474,  2323,  2323,  -762,  1098,
    -762,  -762,  -762,   328,  -762,   260,  2323,  -762,   383,  2323,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   278,
    -762,   278,  -762,   278,   330,  2323,  -762,   383,   335,  -762,
    -762,  -762,  -762,  -762,  -762,   383,   383,  -762,  1616,    58,
     -32,  1616,  -762,  -762,   197,  -762,  -762,  -762,  -762,  2370,
    -762,  -762,  2323,  -762,  -762,  3605,   332,   383,   271,  -762,
    3813,  3813,   650,  3749,  3716,  3782,  3782,   101,   101,   101,
     101,    66,    66,    66,  3844,  1544,  3875,  2680,  3813,  2323,
     333,  3013,   101,  -762,  -762,  -762,  -762,   270,  3813,   219,
     383,  -762,  3605,  -762,  3605,  1795,  -762,  -762,  -762,    58,
     329,  3605,   336,   170,   383,   344,   353,   357,   352,   354,
      -6,   292,   346,    50,  -762,  -762,    -5,  -762,  -762,  -762,
    -762,   361,  -762,   383,   443,   351,  -762,  -762,  -762,   356,
     359,  2176,   362,  -762,     6,  -762,   456,   315,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   254,    66,  -762,  -762,   367,  -762,  -762,  2323,
     650,  -762,  2323,   883,   368,   366,  -762,  -762,  -762,  -762,
     219,  -762,   363,   192,  -762,  -762,  -762,  -762,   219,   219,
    -762,   135,  -762,   367,  -762,  2323,   383,    60,   322,   376,
    -762,  -762,   379,   351,  2323,   369,  -762,  2323,  -762,  3050,
    2323,  -762,   358,  2323,  1474,  2323,  -762,  -762,   883,  -762,
     378,  3087,  3642,  -762,  1474,  -762,   373,  2323,  -762,   383,
      94,    99,   107,   375,   381,   383,   380,  3605,  -762,   135,
    -762,    -8,   382,  -762,  -762,  3124,  -762,  3161,   384,  2717,
     391,  3198,   232,   838,  -762,  -762,   392,  -762,  -762,  -762,
    -762,   724,  -762,  -762,  -762,  -762,  -762,  -762,   400,  -762,
     415,   278,   278,   278,   404,   405,   390,    31,  -762,  -762,
    2514,   429,  1474,  -762,  2323,   418,  -762,   428,  -762,  1616,
    -762,  -762,  -762,  -762,  2510,   432,   421,  -762,  -762,  -762,
     434,   436,   437,   444,   445,  -762,   283,  -762,  -762,   439,
     423,  -762,   446,  3235,  -762,  1474,   442,   219,  -762,  2418,
    2323,  2323,  2323,  -762,  -762,  -762,   448,  -762,  -762,  -762,
    -762,   451,  2514,  2225,   452,  -762,   450,  -762,   458,   360,
      37,  1616,  -762,  -762,   457,   383,  -762,  -762,  -762,  -762,
    -762,  -762,  3272,  3309,  3346,   117,  2274,   459,  2323,  -762,
    2323,  2323,  2323,  -762,  2323,  2323,  -762,  -762,  -762,  -762,
     461,  -762,  -762,  -762,   456,   462,  -762,   468,  3679,  -762,
     464,   465,   469,   474,  -762,  -762,  -762,   383,  -762,   383,
     383,   383,  -762,   -14,  -762,  -762,  -762,  3383,  1976,   479,
      66,    66,    66,  3420,    66,   383,  -762,  -762,   -12,  2323,
    2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,
    2323,  2323,  2323,  2323,  2323,  2323,  2323,  2323,   490,  2323,
    2323,  -762,  2323,  -762,  -762,  2025,  -762,  -762,   483,   484,
     492,   466,   498,   508,   383,  1181,  -762,  -762,   495,  -762,
    -762,  -762,  1352,  2640,  -762,  -762,  -762,  -762,  3813,  3813,
     650,  3749,  3716,  3782,  3782,   101,   101,   101,   101,    66,
      66,    66,  3844,  1544,  3875,  2754,  3813,  2323,  3457,   101,
    3813,   175,  2466,  -762,  -762,  -762,  -762,  1474,    58,   460,
     505,   517,   515,  2600,   -14,  -762,  -762,  2323,  2323,  -762,
    2323,   650,  2323,   526,  -762,   520,   514,  -762,  2076,  2323,
    2323,    58,  3605,  3605,  3494,  3642,  -762,  -762,  -762,   198,
    -762,  3531,  3568,   522,  -762,  1403,  -762,  2076,  -762,  -762,
    -762,   528,  -762,   383,   525,  -762
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   158,     6,     0,   253,   255,
     254,   257,     0,   256,     0,     0,   265,   266,   246,     5,
       0,    34,    35,     0,    13,     0,    10,   156,    12,   156,
       8,   227,    33,   264,   248,   240,   243,   242,   241,   239,
       0,    11,   284,   289,   291,   290,   292,    14,    15,     0,
       9,     7,    16,    20,    18,    22,    19,    23,    21,    17,
      25,    24,    37,   484,   485,     0,     0,     0,     0,   276,
       0,     0,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,    33,   254,    36,     0,   288,   247,    33,   286,
     159,   287,     0,     0,    34,   377,   440,   440,   276,   440,
     267,   285,   440,    42,   440,     0,   312,     0,   440,     0,
       0,   275,   274,   273,   272,   277,     0,   440,     0,     0,
       0,   213,   246,   303,     0,   266,   224,     0,     0,   264,
     293,   297,     0,     0,     0,   144,   168,   267,     0,     0,
     440,   143,     0,   135,   136,     0,   216,   337,   440,   440,
     440,   440,   440,   440,   384,   400,   401,   402,     0,   399,
     398,   403,     0,     0,     0,   244,   245,     0,   379,   380,
     382,   439,   403,     0,     0,     0,   232,   268,     0,     0,
       0,    41,   131,    40,   386,     0,     0,   486,   487,   258,
     310,     0,     0,   259,   311,     0,   249,     0,   260,    33,
       0,   267,     0,   305,   267,   228,   229,   267,   267,   316,
     317,   267,   267,     0,   314,   315,     0,   140,   142,   141,
       0,   157,    33,   162,    33,   339,   413,   412,   411,     0,
       0,   254,     0,   240,   241,     0,   410,     0,   440,   404,
     440,   390,   414,     0,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,     0,   440,   440,   440,   416,   440,
     250,   252,   251,     0,   270,     0,   440,    39,     0,   440,
      45,   104,   103,    99,   100,   102,   101,   106,   108,   107,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    95,   122,    96,    42,    38,   123,   124,
     130,   125,   126,   127,   128,   129,   105,    90,    98,    97,
      84,    61,    82,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    62,    63,
      64,    65,    66,    67,    68,    76,    69,    70,    71,    73,
      72,    74,    75,    77,    78,    79,    80,    81,    83,    85,
      86,    87,    88,    89,    91,    92,    93,    94,    44,     0,
     313,     0,   278,     0,     0,   440,   214,     0,     0,   225,
     294,   298,   145,   169,   300,     0,     0,   137,    33,    33,
       0,    34,   221,   217,     0,   220,   219,   222,   218,    33,
     408,   407,   440,   409,   415,   383,     0,     0,     0,   381,
     426,   427,   424,   436,   437,   430,   431,   420,   421,   422,
     423,   417,   418,   419,   434,   432,   433,     0,   429,   440,
       0,     0,   435,   281,   280,   279,   282,     0,   428,    33,
       0,   269,   133,   132,   387,     0,   261,   262,   263,    33,
       0,   376,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,   138,     0,   165,   163,    33,   171,   167,   166,
     164,     0,   223,     0,     0,   374,   338,   322,   393,     0,
       0,   440,     0,   388,     0,   351,     0,   240,   329,   318,
     332,   335,   334,   331,   330,   350,   333,   336,   340,   348,
     349,   392,     0,   444,   443,   391,     0,   148,   405,   440,
     425,   442,   440,     0,     0,     0,   271,    43,   370,   373,
      33,   304,     0,     0,   307,   230,   300,   300,    33,    33,
     296,     0,   301,     0,   147,   440,     0,     0,     0,     0,
     172,   212,     0,   374,   440,     0,   323,   440,   324,     0,
     440,   389,     0,   440,   440,   440,   394,   395,   276,   152,
       0,     0,   438,   283,   440,   233,     0,   440,   306,     0,
      33,    33,    33,     0,     0,     0,     0,   139,   173,     0,
     161,    33,     0,   375,   372,     0,   325,     0,     0,     0,
       0,     0,     0,     0,   150,   406,     0,   215,   309,   308,
     226,     0,   231,   236,   295,   299,   146,   170,     0,   149,
       0,     0,     0,     0,     0,     0,    31,    33,   353,   371,
      33,     0,   440,   396,   440,     0,   319,     0,   151,     0,
     155,   153,   154,   441,     0,   246,     0,   237,   302,   175,
       0,     0,     0,     0,     0,    32,     0,   352,   354,     0,
     326,   342,     0,     0,   320,   440,     0,    33,   234,    33,
     440,   440,   440,   362,   359,    28,     0,    30,    29,    26,
      27,     0,    33,     0,     0,   397,     0,   235,     0,     0,
       0,    34,   176,   182,     0,     0,   177,   179,   183,   178,
     180,   181,     0,     0,     0,    33,   440,     0,   440,   327,
     440,   440,   440,   341,   440,   440,   447,   448,   449,   346,
       0,   446,   445,   450,     0,     0,   343,     0,   347,   328,
       0,     0,     0,     0,   187,   189,   184,     0,   174,     0,
       0,     0,   356,     0,   363,   355,   360,     0,   440,     0,
     458,   457,   456,     0,   455,     0,   451,   459,   345,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,     0,   440,
     440,   461,   440,   321,   238,   440,   188,   175,     0,     0,
       0,     0,     0,   365,     0,   440,   208,   207,     0,   194,
     195,   368,   440,   204,   358,   454,   460,   344,   471,   472,
     469,   481,   482,   475,   476,   465,   466,   467,   468,   462,
     463,   464,   479,   477,   478,     0,   474,   440,     0,   480,
     473,     0,    33,   211,   210,   209,   364,   440,    33,   203,
     202,     0,     0,   204,     0,   357,   369,   440,   440,   452,
     440,   470,   440,     0,   185,     0,     0,   197,   440,   440,
     440,    33,   205,   206,     0,   483,   191,   366,   361,     0,
     198,   200,   201,     0,   453,   440,   196,   440,   367,   190,
     192,     0,   199,     0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -762,  -762,  -762,  -762,  -762,    -7,   123,  -762,  -762,     8,
      10,   -17,  -762,   269,  -762,   435,   309,  -180,  -762,   370,
    -762,  -762,  -762,  -762,  -209,    55,  -762,  -762,   562,   217,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   127,
    -762,  -182,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -266,  -762,  -762,  -762,  -761,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   -70,  -762,
    -762,  -762,  -762,   272,  -762,  -762,   263,    21,  -762,   374,
      22,  -762,  -107,  -762,  -762,  -188,   -89,  -762,  -762,  -762,
     129,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -184,  -762,
    -762,  -762,  -762,  -762,    33,  -762,  -762,   -60,  -762,  -647,
    -762,  -645,  -762,  -762,  -642,  -641,  -592,   -31,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,   -11,  -762,  -762,
    -762,  -762,  -230,  -185,  -762,   393,  -214,     3,    71,  -528,
      25,  -137,  -762,   377,  -149,  -712,  -134,  -762,  -762,  -762,
     861,  -762,  -762,    11,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    19,   172,   162,   671,   646,   141,
      94,    22,   180,   185,   368,   181,   182,   142,   143,   144,
     220,    23,   211,   458,    24,   560,   593,   631,    90,   163,
      26,   145,   539,   388,   465,    27,   212,   459,   466,   467,
     610,   659,   682,   683,   777,   684,   724,   725,   865,   870,
     788,   789,   859,   831,   790,   468,    28,    29,   201,   452,
     224,   393,   471,    30,   204,   455,    31,   570,    32,   273,
     602,   637,   603,   114,   164,    34,   165,    36,    37,   166,
      39,    40,   176,   177,   275,   115,   116,   436,   437,    41,
      42,    43,   207,   456,    44,    45,   208,   457,   460,   532,
      46,   202,   378,   523,   524,    47,    48,   107,    49,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   225,   399,
     497,   673,   716,   717,   498,   395,   617,   618,   696,   736,
     695,   734,   782,   791,   792,    50,   690,   691,   545,   450,
      52,   167,   168,   169,   183,   501,   268,   407,   502,   557,
     170,   171,   718,   269,   189
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    95,   230,   216,    84,   128,    51,   372,   110,   174,
     397,    20,   686,    21,   687,   392,   583,   688,   689,   374,
      65,   783,    67,   104,   832,    69,    70,   108,   650,     4,
     213,   242,   117,    61,   -33,    63,    64,   -25,    71,   598,
      93,   530,  -160,    72,     5,   241,    98,   217,   218,     7,
     -25,   -25,   147,     7,   219,     7,     7,    53,    54,    61,
      66,    61,   113,   614,    61,    55,    61,    61,   126,    61,
      61,   473,    61,    61,    61,    86,    56,    84,   647,    57,
     699,    72,   615,   726,   105,    58,   132,   860,   109,   161,
     132,   113,     7,   118,   376,   161,    59,   379,    68,   242,
     380,   381,   614,   406,   382,   383,   872,   193,    63,    64,
     262,   178,    72,    61,   196,    64,   198,    61,   265,     7,
       5,   615,   783,     7,   241,    72,    61,    61,   430,    88,
      62,    61,    61,   161,   389,     8,     9,    89,   256,   257,
     258,   600,    96,    83,   161,   262,   604,    87,   178,   536,
      64,    11,    99,   265,   605,     7,   239,   101,   537,   241,
       7,    74,    13,   100,   732,    76,    77,    14,     7,    15,
     739,    61,   271,    18,   469,   686,    98,   687,     7,   464,
     688,   689,    81,   190,    61,   499,   194,   146,   113,   106,
     485,   106,   191,     5,   119,   191,   121,   123,   127,   130,
     131,   400,   135,   136,   137,   401,   147,   134,     8,     9,
     278,   139,   178,    88,   279,   178,    83,   521,   178,   178,
      25,    91,   178,   178,    11,   179,   191,   398,   843,   140,
      61,   279,   390,   161,   391,    13,    61,   161,    25,   568,
      14,   199,    15,   200,    98,   -24,    18,   203,   569,    96,
     -17,   866,   -17,   -17,   867,   102,   209,   210,   161,   515,
     205,   214,   215,   103,   -17,   206,    35,   221,    53,    54,
      99,    61,  -134,   441,   179,    33,    55,   222,  -245,   223,
       7,   237,   187,   188,    35,   244,    25,    56,   195,    25,
      57,    25,    25,    85,   -24,    25,    58,   238,   553,    25,
      97,   274,    63,    64,    63,    64,   554,    59,    60,   240,
     187,   188,   241,   555,   370,    25,   440,   453,   243,    97,
     187,   188,   278,    63,    64,   563,   513,  -244,   187,   188,
     506,   507,    35,   241,   277,    35,   276,    35,    35,   375,
     566,    35,   571,   572,   120,    35,   124,   129,   573,   574,
     133,   533,   534,   279,   138,   665,   377,   384,   472,    97,
     404,    35,   666,    63,    64,   385,   408,   446,   556,   447,
      61,   448,   402,   552,    84,   429,   667,    38,    61,    61,
     439,   454,   668,   449,   630,   504,   511,    61,   520,   519,
     525,   470,   483,   669,   670,    38,   463,    93,   391,   526,
      61,   179,   500,   527,   528,   535,   529,   484,   541,   391,
     544,   547,    25,   559,   550,   233,   546,   590,   518,   565,
     564,   536,   567,   580,   232,   581,   597,   596,   606,   584,
     588,    53,    54,    61,   607,   514,   622,    25,   594,    55,
     609,    25,   619,    38,   625,   633,    38,    61,    38,    38,
      56,   722,    38,    57,    53,    54,    38,    93,    35,    58,
     638,   639,    55,   643,   644,   645,    61,    61,   531,   592,
      59,    60,    38,    56,   538,   651,    57,   678,   654,   551,
     655,   658,    58,    35,   657,   652,   660,    35,   661,   662,
     663,   664,   386,    59,    60,   140,   394,   552,    98,   674,
     106,   672,   677,   720,   728,   738,   113,   697,   461,   462,
     698,   721,   719,   558,    53,    54,  -208,   475,   676,   745,
     241,   775,    55,   748,   773,   774,   234,    53,    54,    61,
     505,   636,   233,    56,   776,    55,    57,    53,    54,   794,
     817,   435,    58,   823,   824,    55,    56,   161,   579,    57,
     834,   113,   825,    59,    60,    58,    56,   161,   826,    57,
     827,  -207,    61,   516,   656,    58,    59,    87,    61,    38,
     847,   848,   856,   857,   858,   445,    59,   522,   601,   531,
     531,   747,   868,   873,   771,   875,   229,   443,   576,   616,
     627,    92,   387,   540,    38,   822,   542,   543,    38,   871,
     612,   613,   599,   629,   851,    25,   648,   836,    25,   640,
     641,   642,    84,   483,   582,   161,   486,   396,   632,     0,
       0,   409,     0,     0,     0,   616,   821,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,     0,     0,     0,     0,   161,     0,
       0,    35,   483,     0,    35,     0,     0,     0,     0,   578,
     394,     0,   487,   474,    84,   483,   713,   680,     0,   681,
       0,   394,    61,     0,     0,     0,     0,     0,    61,    -3,
      93,     0,     0,   252,   253,   254,   255,   256,   257,   258,
     845,     0,   522,     0,   262,     0,     0,     0,   608,    64,
       0,     0,   265,   733,     0,     0,     0,   746,   241,     0,
       0,     0,   267,     0,     0,     0,     0,   797,     0,     0,
      61,     0,    61,    61,    61,     0,   483,     0,     0,   772,
      25,     0,     0,     0,     0,     0,     0,     5,    61,     6,
       7,     0,     0,     0,     0,     0,     0,     0,    25,     0,
       0,     0,     8,     9,     0,     0,    93,     0,     0,     0,
      10,     0,    38,     0,     0,    38,     0,     0,    11,     0,
       0,    12,     0,    38,   551,    25,    35,    61,     0,    13,
       0,     0,     5,     0,    14,     0,    15,     0,    16,    17,
      18,     0,     0,   634,    35,     0,    25,     8,     9,     0,
       0,     0,   723,   575,     0,    83,     0,     0,   475,     0,
      25,     0,     0,    11,     0,   483,     0,     0,    25,     0,
     161,    35,     0,     0,    13,     0,     0,   483,     0,    14,
     680,    15,   681,    16,    17,   635,   846,   486,     0,     0,
       0,     0,   611,     0,     0,     0,    25,     0,     0,     0,
     543,    25,   778,   779,   780,     0,    35,     0,     0,   863,
       0,     0,     0,     0,    35,    33,    61,     0,   796,     0,
       0,     0,     0,   129,     0,     0,   486,     0,     0,     0,
       0,     0,     0,   649,     0,   628,     0,    38,     0,   486,
     714,     0,    35,     0,     0,     0,     5,    35,    25,     7,
       0,    85,     0,    71,     0,    38,   129,   828,    72,    73,
       0,     8,     9,    74,     0,     0,    75,    76,    77,    83,
       0,     0,   487,     0,     0,     0,    78,    11,    79,    80,
       0,   685,    38,     0,    81,   649,   715,     0,    13,    82,
       0,     5,     0,    14,    35,    15,   111,    16,    17,    18,
     781,     0,     0,   727,    53,    54,     8,     9,   173,     0,
     175,     0,    55,   184,    83,   186,     0,    38,     0,   192,
       0,     0,    11,    56,     0,    38,    57,     0,   197,     0,
       0,     0,    58,    13,     0,     0,     0,     0,    14,     0,
      15,     0,   112,    59,    18,     0,   874,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,     0,    38,   226,
     227,   228,   184,   235,   236,     0,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    53,    54,     8,     9,     0,   486,
       0,     0,    55,     0,    83,     0,     0,     0,   233,     0,
       0,   781,    11,    56,     0,    38,    57,   232,     0,     0,
       0,     0,    58,    13,     0,     0,     0,     0,    14,     0,
      15,     0,    16,   125,   122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   487,     0,     0,     0,     0,
       0,     0,     0,     0,   685,     0,     0,     0,     0,   405,
       0,     0,     0,     0,     0,     0,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,     0,     0,   431,   432,     0,
     438,   148,   149,     0,     0,     0,     0,   442,     0,     0,
     444,   150,     0,     0,   151,     0,     0,     0,     0,     0,
     152,     0,   153,     0,     0,     0,     5,     0,     0,   234,
       0,   433,     0,     0,   155,   156,   157,     0,     0,    53,
      54,     8,     9,     0,     0,     0,     0,    55,     0,   231,
       0,     0,     0,     0,     0,     0,     0,    11,    56,     0,
       0,    57,     0,     0,     0,     0,    38,    58,    13,     0,
       0,     0,     0,    14,     0,    15,     0,   434,    59,    18,
     159,   160,     0,     0,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,   150,     0,     0,   151,     0,     0,
       0,     0,     0,   152,     0,   153,   451,     0,     0,     5,
       0,     0,     0,     0,   829,     0,     0,   155,   156,   157,
       0,     0,    53,    54,     8,     9,     0,     0,   830,     0,
      55,     0,   231,   503,     0,     0,     0,     0,     0,     0,
      11,    56,     0,     0,    57,     0,     0,     0,     0,     0,
      58,    13,     0,     0,     0,     0,    14,     0,    15,     0,
     510,    59,    18,   159,   160,     0,     0,   148,   149,     0,
       0,     0,     0,     0,     0,     0,     0,   150,     0,     0,
     151,     0,     0,     0,     0,     0,   152,     0,   153,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,     0,     0,    53,    54,     8,     9,     0,
       0,     0,   549,    55,     0,   231,     0,     0,     0,     0,
       0,     0,     0,    11,    56,     0,     0,    57,     0,     0,
       0,     0,     0,    58,    13,     0,     0,     0,     0,    14,
     561,    15,     0,   562,    59,    18,   159,   160,     0,     0,
       0,     0,     0,     0,     0,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,   150,   577,     0,   151,   835,
       0,     0,     0,     0,   785,   451,   153,     0,   585,     0,
       5,   587,     0,     0,   589,   786,   591,     0,   155,   156,
     157,     0,     0,    53,    54,     0,     0,     0,   451,   787,
       0,    55,     0,   158,     0,     0,   148,   149,     0,     0,
       0,     0,    56,     0,     0,    57,   150,     0,     0,   151,
     869,    58,     0,     0,     0,   785,     0,   153,     0,     0,
       0,     5,    59,    18,   159,   160,   786,     0,     0,   155,
     156,   157,     0,     0,    53,    54,     0,     0,     0,     0,
     787,     0,    55,     0,   158,   653,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,     0,     0,     0,
       0,     0,    58,     0,     0,     0,     0,   148,   149,     0,
       0,     0,     0,    59,    18,   159,   160,   150,     0,     0,
     151,   692,   693,   694,     0,     0,   152,  -378,   153,     0,
       0,     0,     5,     0,     0,     0,     0,   154,     0,     0,
     155,   156,   157,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    55,     0,   158,     0,   737,     0,   451,
       0,   740,   741,   742,    56,   743,   744,    57,     0,     0,
       0,     0,   247,    58,     0,     0,     0,   252,   253,   254,
     255,   256,   257,   258,    59,   122,   159,   160,   262,     0,
       0,     0,     0,    64,     0,   264,   265,     0,     0,   793,
       0,     0,   241,     0,     0,     0,   267,     0,     0,     0,
     798,   799,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,     0,
     818,   819,     0,   820,     5,     0,   184,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   833,    53,    54,     8,
       9,     0,     0,   793,     0,    55,     0,    83,     0,     0,
       0,     0,     0,     0,     0,    11,    56,     0,     0,    57,
       0,     0,     0,     0,     5,    58,    13,     7,   841,     0,
       0,    14,     0,    15,     0,     0,    59,   122,     0,     8,
       9,     0,     0,     0,     0,     0,     0,    83,   852,   853,
       0,   854,     0,   855,     0,    11,     0,     0,     0,   793,
     861,   862,     0,     0,     0,     0,    13,     0,     0,     0,
       0,    14,     0,    15,     0,   280,   793,    18,   793,   281,
     282,     0,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   280,     0,     0,
       0,   281,   282,     0,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   517,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,   150,
       0,  -385,   151,     0,     0,     0,     0,     0,   152,     0,
     153,     0,  -385,     0,     5,     0,     0,     0,     0,     0,
       0,     0,   155,   156,   157,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   158,   148,   149,
       0,     0,     0,     0,     0,     0,    56,     0,   150,    57,
       0,   151,  -385,     0,     0,    58,     0,   152,     0,   153,
       0,  -385,     0,     5,     0,     0,    59,   122,   159,   160,
       0,   155,   156,   157,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,    55,     0,   158,     0,     0,   148,
     149,     0,     0,     0,     0,    56,     0,     0,    57,   150,
       0,     0,   151,     0,    58,     0,     0,     0,   785,     0,
     153,     0,     0,     0,     5,    59,   122,   159,   160,   786,
       0,     0,   155,   156,   157,     0,     0,    53,    54,     0,
       0,     0,     0,   787,     0,    55,     0,   158,   148,   149,
       0,     0,     0,     0,     0,     0,    56,     0,   150,    57,
       0,   151,     0,     0,     0,    58,     0,   152,  -385,   153,
       0,  -385,     0,     5,     0,     0,    59,    18,   159,   160,
       0,   155,   156,   157,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,    55,     0,   158,     0,     0,   148,
     149,     0,     0,     0,     0,    56,     0,     0,    57,   150,
       0,     0,   151,     0,    58,     0,     0,     0,   152,     0,
     153,     0,     0,     0,     5,    59,    18,   159,   160,   786,
       0,     0,   155,   156,   157,     0,     0,    53,    54,     0,
       0,     0,     0,   787,     0,    55,     0,   158,     0,     0,
     148,   149,     0,     0,     0,     0,    56,     0,     0,    57,
     150,     0,     0,   151,     0,    58,     0,     0,     0,   152,
       0,   153,     0,     0,     0,     5,    59,    18,   159,   160,
     154,     0,     0,   155,   156,   157,     0,     0,    53,    54,
       0,     0,     0,     0,     0,     0,    55,     0,   158,   148,
     149,     0,     0,     0,     0,     0,     0,    56,     0,   150,
      57,     0,   151,     0,     0,     0,    58,     0,   152,     0,
     153,     0,     0,     0,     5,     0,   548,    59,   122,   159,
     160,     0,   155,   156,   157,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   158,   700,   701,
       0,     0,     0,     0,     0,     0,    56,     0,   702,    57,
       0,     0,   703,     0,     0,    58,     0,   704,     0,   705,
       0,     0,     0,     5,     0,     0,    59,    18,   159,   160,
       0,   706,   707,   708,     0,     0,    53,    54,     0,     0,
       0,     0,   709,     0,    55,     0,   710,   148,   149,     0,
       0,     0,     0,     0,     0,    56,     0,   150,    57,     0,
     151,   735,     0,     0,    58,     0,   152,     0,   153,     0,
       0,     0,     5,     0,     0,    59,    18,   711,   712,     0,
     155,   156,   157,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    55,     0,   158,   148,   149,     0,     0,
       0,     0,     0,     0,    56,     0,   150,    57,     0,   151,
       0,     0,     0,    58,     0,   152,     0,   153,     0,     0,
       0,     5,     0,     0,    59,    18,   159,   160,     0,   155,
     156,   157,     0,     0,    53,    54,     0,     0,     0,     0,
       0,     0,    55,     0,   158,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,   476,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     5,     0,
     477,     7,     0,    59,    18,   159,   160,     0,   478,     0,
       0,    53,    54,     8,     9,     0,     0,     0,     0,    55,
       0,    83,   479,     0,     0,     0,   480,     0,     0,    11,
      56,     0,     0,    57,     0,  -186,     0,     0,   481,    58,
      13,     0,   482,     0,     0,    14,     5,    15,   477,     7,
      59,    18,     0,     0,     0,     0,   478,     0,     0,    53,
      54,     8,     9,     0,     0,     0,     0,    55,     0,    83,
       0,     0,     0,     0,   480,     0,     0,    11,    56,     0,
       0,    57,     0,   844,     0,     0,     0,    58,    13,     0,
       0,     0,   679,    14,     5,    15,   477,     7,    59,    18,
       0,     0,     0,     0,   478,     0,     0,    53,    54,     8,
       9,     0,     0,     0,     0,    55,     0,    83,     0,     0,
       0,     0,   480,     0,     0,    11,    56,     0,     0,    57,
       0,     0,     0,     0,     0,    58,    13,     0,     5,     0,
       0,    14,     5,    15,   477,     7,    59,    18,     0,     0,
       0,     0,   478,     8,     9,    53,    54,     0,     0,     0,
       0,    83,     0,    55,     0,     0,   479,     0,     0,    11,
     480,     0,     0,     0,    56,     0,     0,    57,     0,     0,
      13,     0,   481,    58,     0,    14,   482,    15,     0,    16,
      17,    18,     0,     0,    59,    18,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,     0,   262,     0,     0,     0,    63,    64,
     263,   264,   265,   403,     0,     0,     0,   266,   241,     0,
       0,     0,   267,     0,   849,   850,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,     0,   262,     0,     0,     0,    63,    64,
     263,   264,   265,     0,     0,     0,     0,   266,   241,     0,
       0,     0,   267,     0,   837,   838,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,     0,   262,   508,     0,     0,    63,    64,
     263,   264,   265,     0,     0,   509,     0,   266,   241,     0,
       0,     0,   267,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,   262,   623,     0,     0,    63,    64,   263,   264,   265,
       0,     0,   624,     0,   266,   241,     0,     0,     0,   267,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,     0,   262,   839,
       0,     0,    63,    64,   263,   264,   265,     0,     0,   840,
       0,   266,   241,     0,     0,     0,   267,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,     0,   262,   270,     0,     0,    63,
      64,   263,   264,   265,     0,     0,     0,     0,   266,   241,
       0,     0,     0,   267,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,     0,   262,   272,     0,     0,    63,    64,   263,   264,
     265,     0,     0,     0,     0,   266,   241,     0,     0,     0,
     267,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,     0,   262,
       0,     0,     0,    63,    64,   263,   264,   265,   369,     0,
       0,     0,   266,   241,     0,     0,     0,   267,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,     0,   262,     0,     0,     0,
      63,    64,   263,   264,   265,   371,     0,     0,     0,   266,
     241,     0,     0,     0,   267,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,     0,   262,     0,     0,     0,    63,    64,   263,
     264,   265,   373,     0,     0,     0,   266,   241,     0,     0,
       0,   267,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,     0,
     262,     0,     0,     0,    63,    64,   263,   264,   265,   403,
       0,     0,     0,   266,   241,     0,     0,     0,   267,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,     0,   262,     0,     0,
       0,    63,    64,   263,   264,   265,     0,     0,   512,     0,
     266,   241,     0,     0,     0,   267,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,     0,   262,     0,     0,     0,    63,    64,
     263,   264,   265,     0,     0,     0,     0,   266,   241,     0,
     586,     0,   267,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,   262,   595,     0,     0,    63,    64,   263,   264,   265,
       0,     0,     0,     0,   266,   241,     0,     0,     0,   267,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,     0,   262,     0,
       0,     0,    63,    64,   263,   264,   265,   620,     0,     0,
       0,   266,   241,     0,     0,     0,   267,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,     0,   262,     0,     0,     0,    63,
      64,   263,   264,   265,   621,     0,     0,     0,   266,   241,
       0,     0,     0,   267,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,     0,   262,     0,     0,     0,    63,    64,   263,   264,
     265,     0,     0,     0,     0,   266,   241,     0,   626,     0,
     267,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,     0,   262,
     675,     0,     0,    63,    64,   263,   264,   265,     0,     0,
       0,     0,   266,   241,     0,     0,     0,   267,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,     0,   262,     0,     0,     0,
      63,    64,   263,   264,   265,   729,     0,     0,     0,   266,
     241,     0,     0,     0,   267,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,     0,   262,     0,     0,     0,    63,    64,   263,
     264,   265,   730,     0,     0,     0,   266,   241,     0,     0,
       0,   267,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,     0,
     262,     0,     0,     0,    63,    64,   263,   264,   265,   731,
       0,     0,     0,   266,   241,     0,     0,     0,   267,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,     0,   262,     0,     0,
       0,    63,    64,   263,   264,   265,     0,     0,   784,     0,
     266,   241,     0,     0,     0,   267,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,     0,   262,     0,     0,     0,    63,    64,
     263,   264,   265,   795,     0,     0,     0,   266,   241,     0,
       0,     0,   267,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
       0,   262,     0,     0,     0,    63,    64,   263,   264,   265,
       0,     0,   842,     0,   266,   241,     0,     0,     0,   267,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,     0,   262,   864,
       0,     0,    63,    64,   263,   264,   265,     0,     0,     0,
       0,   266,   241,     0,     0,     0,   267,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,     0,   262,     0,     0,     0,    63,
      64,   263,   264,   265,     0,     0,     0,  -205,   266,   241,
       0,     0,     0,   267,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,     0,   262,     0,     0,     0,    63,    64,   263,   264,
     265,     0,     0,     0,  -206,   266,   241,     0,     0,     0,
     267,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,     0,   262,
       0,     0,     0,    63,    64,   263,   264,   265,     0,     0,
       0,     0,   266,   241,     0,     0,     0,   267,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,     0,   262,     0,     0,     0,
      63,    64,   263,   264,   265,     0,     0,     0,     0,     0,
     241,     0,     0,     0,   267,   749,   750,   751,   752,   753,
     754,   755,   756,   757,   758,   759,   760,   761,   762,   763,
     764,   765,     0,   766,     0,     0,     0,    63,    64,   767,
     768,     0,     0,     0,     0,     0,   769,   241,     0,     0,
       0,   770,   245,   246,   247,   248,     0,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,     0,
     262,     0,     0,     0,    63,    64,   263,   264,   265,     0,
       0,     0,     0,     0,   241,   245,   246,   247,   267,     0,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,     0,   262,     0,     0,     0,    63,    64,   263,
     264,   265,     0,     0,     0,     0,     0,   241,   245,   246,
     247,   267,     0,     0,     0,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,     0,   262,     0,     0,     0,
      63,    64,   263,   264,   265,     0,     0,     0,     0,     0,
     241,   247,     0,     0,   267,     0,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,     0,   262,     0,     0,
       0,     0,    64,     0,   264,   265,     0,     0,     0,     0,
       0,   241,   247,     0,     0,   267,     0,   252,   253,   254,
     255,   256,   257,   258,     0,   260,   261,     0,   262,     0,
       0,     0,     0,    64,     0,   264,   265,     0,     0,     0,
       0,     0,   241,   247,     0,     0,   267,     0,   252,   253,
     254,   255,   256,   257,   258,     0,   260,     0,     0,   262,
       0,     0,     0,     0,    64,     0,   264,   265,     0,     0,
       0,     0,     0,   241,     0,     0,     0,   267
};

static const yytype_int16 yycheck[] =
{
       7,    32,   151,   140,    21,    75,     3,   195,    68,    98,
     224,     3,   659,     3,   659,   224,   544,   659,   659,   199,
       9,   733,    11,    52,   785,    14,    15,    52,   620,     0,
     137,   165,    52,    40,    46,    48,    49,    46,    70,   567,
      32,    47,    47,    75,    58,    58,    35,    87,    88,    61,
      59,    60,    46,    61,    94,    61,    61,    71,    72,    66,
      46,    68,    69,    71,    71,    79,    73,    74,    75,    76,
      77,   103,    79,    80,    81,    60,    90,    94,    47,    93,
     672,    75,    90,    46,   113,    99,    78,   848,   113,    96,
      82,    98,    61,   113,   201,   102,   110,   204,    46,   233,
     207,   208,    71,   240,   211,   212,   867,   109,    48,    49,
      44,   100,    75,   120,   116,    49,   118,   124,    52,    61,
      58,    90,   834,    61,    58,    75,   133,   134,   265,    52,
       7,   138,   139,   140,    72,    73,    74,    60,    37,    38,
      39,    47,    52,    81,   151,    44,    47,   111,   137,    99,
      49,    89,    44,    52,    47,    61,   163,    60,   108,    58,
      61,    80,   100,    40,    47,    84,    85,   105,    61,   107,
     698,   178,   174,   111,   388,   822,   165,   822,    61,   388,
     822,   822,   101,    47,   191,   399,    47,    46,   195,    66,
     399,    68,    56,    58,    71,    56,    73,    74,    75,    76,
      77,    47,    79,    80,    81,    47,    46,    78,    73,    74,
      56,    82,   201,    52,    56,   204,    81,    47,   207,   208,
       3,    60,   211,   212,    89,   102,    56,   224,    53,    52,
     237,    56,   224,   240,   224,   100,   243,   244,    21,    47,
     105,    52,   107,   120,   233,    60,   111,   124,    56,    52,
      46,    53,    48,    49,    56,    44,   133,   134,   265,   439,
      60,   138,   139,    52,    60,    60,     3,    53,    71,    72,
      44,   278,    53,   275,   151,     3,    79,    56,    52,    46,
      61,    58,    50,    51,    21,    56,    69,    90,    56,    72,
      93,    74,    75,    21,    59,    78,    99,    59,    44,    82,
      44,   178,    48,    49,    48,    49,    52,   110,   111,    52,
      50,    51,    58,    59,   191,    98,    56,   377,    53,    44,
      50,    51,    56,    48,    49,   513,    56,    52,    50,    51,
      59,    60,    69,    58,    45,    72,    59,    74,    75,    59,
     520,    78,   526,   527,    72,    82,    74,    75,   528,   529,
      78,    59,    60,    56,    82,    72,    46,    46,   389,    44,
     237,    98,    79,    48,    49,    53,   243,   369,   502,   371,
     377,   373,    53,    58,   391,    50,    93,     3,   385,   386,
      52,    46,    99,    53,   593,    53,    53,   394,    52,    60,
      46,   388,   399,   110,   111,    21,   388,   389,   388,    46,
     407,   278,   399,    46,    52,    59,    52,   399,    47,   399,
      59,    52,   195,    46,    52,   152,    60,   554,   449,    53,
      52,    99,    59,    47,   152,    46,    53,   564,    53,    60,
      72,    71,    72,   440,    53,   437,    52,   220,    60,    79,
      60,   224,    60,    69,    53,    53,    72,   454,    74,    75,
      90,    91,    78,    93,    71,    72,    82,   449,   195,    99,
      60,    46,    79,    59,    59,    75,   473,   474,   460,   558,
     110,   111,    98,    90,   466,    46,    93,   657,    60,   486,
      52,    60,    99,   220,    52,   622,    52,   224,    52,    52,
      46,    46,   220,   110,   111,    52,   224,    58,   487,    53,
     377,    78,    60,    53,    47,    46,   513,    59,   385,   386,
      59,    53,    60,   502,    71,    72,    56,   394,   655,    58,
      58,    52,    79,    55,    60,    60,   152,    71,    72,   536,
     407,   601,   269,    90,    60,    79,    93,    71,    72,    60,
      50,   269,    99,    60,    60,    79,    90,   554,   537,    93,
      55,   558,    60,   110,   111,    99,    90,   564,    60,    93,
      52,    56,   569,   440,   634,    99,   110,   111,   575,   195,
      53,    56,    46,    53,    60,   306,   110,   454,   570,   571,
     572,   715,    60,    55,   718,    60,   151,   278,   533,   581,
     592,    29,   222,   466,   220,   777,   473,   474,   224,   865,
     579,   579,   569,   593,   834,   388,   617,   792,   391,   611,
     612,   613,   629,   620,   543,   622,   399,   224,   593,    -1,
      -1,   244,    -1,    -1,    -1,   617,   775,    -1,   620,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   269,    -1,    -1,    -1,    -1,   655,    -1,
      -1,   388,   659,    -1,   391,    -1,    -1,    -1,    -1,   536,
     388,    -1,   399,   391,   681,   672,   673,   659,    -1,   659,
      -1,   399,   679,    -1,    -1,    -1,    -1,    -1,   685,     0,
     672,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
     827,    -1,   569,    -1,    44,    -1,    -1,    -1,   575,    49,
      -1,    -1,    52,   695,    -1,    -1,    -1,   714,    58,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,   748,    -1,    -1,
     727,    -1,   729,   730,   731,    -1,   733,    -1,    -1,   718,
     513,    -1,    -1,    -1,    -1,    -1,    -1,    58,   745,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   531,    -1,
      -1,    -1,    73,    74,    -1,    -1,   748,    -1,    -1,    -1,
      81,    -1,   388,    -1,    -1,   391,    -1,    -1,    89,    -1,
      -1,    92,    -1,   399,   781,   558,   513,   784,    -1,   100,
      -1,    -1,    58,    -1,   105,    -1,   107,    -1,   109,   110,
     111,    -1,    -1,    69,   531,    -1,   579,    73,    74,    -1,
      -1,    -1,   679,   531,    -1,    81,    -1,    -1,   685,    -1,
     593,    -1,    -1,    89,    -1,   822,    -1,    -1,   601,    -1,
     827,   558,    -1,    -1,   100,    -1,    -1,   834,    -1,   105,
     822,   107,   822,   109,   110,   111,   828,   620,    -1,    -1,
      -1,    -1,   579,    -1,    -1,    -1,   629,    -1,    -1,    -1,
     727,   634,   729,   730,   731,    -1,   593,    -1,    -1,   851,
      -1,    -1,    -1,    -1,   601,   593,   873,    -1,   745,    -1,
      -1,    -1,    -1,   601,    -1,    -1,   659,    -1,    -1,    -1,
      -1,    -1,    -1,   620,    -1,    47,    -1,   513,    -1,   672,
     673,    -1,   629,    -1,    -1,    -1,    58,   634,   681,    61,
      -1,   629,    -1,    70,    -1,   531,   634,   784,    75,    76,
      -1,    73,    74,    80,    -1,    -1,    83,    84,    85,    81,
      -1,    -1,   659,    -1,    -1,    -1,    93,    89,    95,    96,
      -1,   659,   558,    -1,   101,   672,   673,    -1,   100,   106,
      -1,    58,    -1,   105,   681,   107,    63,   109,   110,   111,
     733,    -1,    -1,   681,    71,    72,    73,    74,    97,    -1,
      99,    -1,    79,   102,    81,   104,    -1,   593,    -1,   108,
      -1,    -1,    89,    90,    -1,   601,    93,    -1,   117,    -1,
      -1,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,   109,   110,   111,    -1,   873,    -1,    -1,    -1,
      -1,    -1,    -1,   629,    -1,    -1,    -1,    -1,   634,   148,
     149,   150,   151,   152,   153,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   659,    71,    72,    73,    74,    -1,   822,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,   785,    -1,
      -1,   834,    89,    90,    -1,   681,    93,   785,    -1,    -1,
      -1,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,   109,   110,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   822,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   822,    -1,    -1,    -1,    -1,   238,
      -1,    -1,    -1,    -1,    -1,    -1,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,    -1,    -1,   266,   267,    -1,
     269,    33,    34,    -1,    -1,    -1,    -1,   276,    -1,    -1,
     279,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   785,
      -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,   822,    99,   100,    -1,
      -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,
     112,   113,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,   375,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    77,    -1,
      79,    -1,    81,   402,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      99,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,    -1,
     429,   110,   111,   112,   113,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,   481,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,
     509,   107,    -1,   512,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,   535,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,   544,    54,    -1,   547,    -1,
      58,   550,    -1,    -1,   553,    63,   555,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,   567,    77,
      -1,    79,    -1,    81,    -1,    -1,    33,    34,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    93,    43,    -1,    -1,    46,
      47,    99,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,   110,   111,   112,   113,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      77,    -1,    79,    -1,    81,   624,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,   110,   111,   112,   113,    43,    -1,    -1,
      46,   660,   661,   662,    -1,    -1,    52,    53,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,   696,    -1,   698,
      -1,   700,   701,   702,    90,   704,   705,    93,    -1,    -1,
      -1,    -1,    28,    99,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,   110,   111,   112,   113,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,   738,
      -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    -1,
     749,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,    -1,
     769,   770,    -1,   772,    58,    -1,   775,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   785,    71,    72,    73,
      74,    -1,    -1,   792,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    58,    99,   100,    61,   817,    -1,
      -1,   105,    -1,   107,    -1,    -1,   110,   111,    -1,    73,
      74,    -1,    -1,    -1,    -1,    -1,    -1,    81,   837,   838,
      -1,   840,    -1,   842,    -1,    89,    -1,    -1,    -1,   848,
     849,   850,    -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,
      -1,   105,    -1,   107,    -1,    22,   865,   111,   867,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    22,    -1,    -1,
      -1,    26,    27,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      54,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    46,    47,    -1,    -1,    99,    -1,    52,    -1,    54,
      -1,    56,    -1,    58,    -1,    -1,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,
      -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,   110,   111,   112,   113,    63,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    46,    -1,    -1,    -1,    99,    -1,    52,    53,    54,
      -1,    56,    -1,    58,    -1,    -1,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,
      -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,   110,   111,   112,   113,    63,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    -1,    81,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,
      43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,   113,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    60,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    -1,    47,    -1,    -1,    99,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,    -1,    81,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,
      46,    47,    -1,    -1,    99,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,   110,   111,   112,   113,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,    46,
      -1,    -1,    -1,    99,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,    -1,    -1,   110,   111,   112,   113,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,    47,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      60,    61,    -1,   110,   111,   112,   113,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    81,    82,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    47,    -1,    -1,    98,    99,
     100,    -1,   102,    -1,    -1,   105,    58,   107,    60,    61,
     110,   111,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    47,    -1,    -1,    -1,    99,   100,    -1,
      -1,    -1,   104,   105,    58,   107,    60,    61,   110,   111,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    86,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    -1,    58,    -1,
      -1,   105,    58,   107,    60,    61,   110,   111,    -1,    -1,
      -1,    -1,    68,    73,    74,    71,    72,    -1,    -1,    -1,
      -1,    81,    -1,    79,    -1,    -1,    82,    -1,    -1,    89,
      86,    -1,    -1,    -1,    90,    -1,    -1,    93,    -1,    -1,
     100,    -1,    98,    99,    -1,   105,   102,   107,    -1,   109,
     110,   111,    -1,    -1,   110,   111,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    -1,    64,    65,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    -1,    64,    65,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    45,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
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
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      60,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
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
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    60,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
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
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    55,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    26,    27,    28,    62,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    26,    27,
      28,    62,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    28,    -1,    -1,    62,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    28,    -1,    -1,    62,    -1,    33,    34,    35,
      36,    37,    38,    39,    -1,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    28,    -1,    -1,    62,    -1,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,   100,   105,   107,   109,   110,   111,   122,
     127,   128,   129,   139,   142,   147,   148,   153,   174,   175,
     181,   184,   186,   191,   193,   194,   195,   196,   197,   198,
     199,   207,   208,   209,   212,   213,   218,   223,   224,   226,
     253,   255,   258,    71,    72,    79,    90,    93,    99,   110,
     111,   123,   124,    48,    49,   271,    46,   271,    46,   271,
     271,    70,    75,    76,    80,    83,    84,    85,    93,    95,
      96,   101,   106,    81,   129,   191,    60,   111,    52,    60,
     146,    60,   146,   127,   128,   235,    52,    44,   271,    44,
     124,    60,    44,    52,    52,   113,   124,   225,    52,   113,
     225,    63,   109,   123,   191,   203,   204,    52,   113,   124,
     191,   124,   111,   124,   191,   110,   123,   124,   186,   191,
     124,   124,   127,   191,   208,   124,   124,   124,   191,   208,
      52,   127,   135,   136,   137,   149,    46,    46,    33,    34,
      43,    46,    52,    54,    63,    66,    67,    68,    81,   112,
     113,   123,   124,   147,   192,   194,   197,   259,   260,   261,
     268,   269,   123,   268,   204,   268,   200,   201,   271,   124,
     130,   133,   134,   262,   268,   131,   268,    50,    51,   272,
      47,    56,   268,   272,    47,    56,   272,   268,   272,    52,
     124,   176,   219,   124,   182,    60,    60,   210,   214,   124,
     124,   140,   154,   200,   124,   124,   259,    87,    88,    94,
     138,    53,    56,    46,   178,   236,   268,   268,   268,   133,
     262,    81,   191,   194,   197,   268,   268,    58,    59,   123,
      52,    58,   264,    53,    56,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    50,    51,    52,    57,    62,   264,   271,
      45,   272,    45,   187,   124,   202,    59,    45,    56,    56,
      22,    26,    27,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   132,    53,
     124,    53,   203,    53,   135,    59,   200,    46,   220,   200,
     200,   200,   200,   200,    46,    53,   191,   137,   151,    72,
     127,   128,   142,   179,   191,   243,   253,   254,   255,   237,
      47,    47,    53,    53,   124,   268,   259,   265,   124,   261,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,    50,
     259,   268,   268,    63,   109,   191,   205,   206,   268,    52,
      56,   272,   268,   134,   268,   131,   272,   272,   272,    53,
     257,   268,   177,   225,    46,   183,   211,   215,   141,   155,
     216,   124,   124,   127,   142,   152,   156,   157,   173,   254,
     255,   180,   235,   103,   191,   124,    47,    60,    68,    82,
      86,    98,   102,   123,   127,   142,   147,   194,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   238,   242,   254,
     255,   263,   266,   268,    53,   124,    59,    60,    45,    55,
     268,    53,    55,    56,   272,   135,   124,    53,   235,    60,
      52,    47,   124,   221,   222,    46,    46,    46,    52,    52,
      47,   127,   217,    59,    60,    59,    99,   108,   127,   150,
     157,    47,   124,   124,    59,   256,    60,    52,    60,   268,
      52,   123,    58,    44,    52,    59,   264,   267,   271,    46,
     143,   268,   268,   203,    52,    53,   135,    59,    47,    56,
     185,   216,   216,   135,   135,   191,   143,   268,   124,   271,
      47,    46,   256,   257,    60,   268,    60,   268,    72,   268,
     259,   268,   204,   144,    60,    45,   259,    53,   257,   222,
      47,   127,   188,   190,    47,    47,    53,    53,   124,    60,
     158,   194,   195,   198,    71,    90,   127,   244,   245,    60,
      53,    53,    52,    45,    55,    53,    60,   272,    47,   128,
     142,   145,   258,    53,    69,   111,   186,   189,    60,    46,
     272,   272,   272,    59,    59,    75,   126,    47,   245,   194,
     234,    46,   259,   268,    60,    52,   186,    52,    60,   159,
      52,    52,    52,    46,    46,    72,    79,    93,    99,   110,
     111,   125,    78,   239,    53,    45,   259,    60,   135,   104,
     127,   128,   160,   161,   163,   191,   227,   229,   232,   233,
     254,   255,   268,   268,   268,   248,   246,    59,    59,   234,
      33,    34,    43,    47,    52,    54,    66,    67,    68,    77,
      81,   112,   113,   123,   147,   194,   240,   241,   270,    60,
      53,    53,    91,   124,   164,   165,    46,   191,    47,    53,
      53,    53,    47,   127,   249,    47,   247,   268,    46,   257,
     268,   268,   268,   268,   268,    58,   123,   264,    55,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    44,    50,    51,    57,
      62,   264,   271,    60,    60,    52,    60,   162,   124,   124,
     124,   147,   250,   263,    55,    52,    63,    77,   168,   169,
     172,   251,   252,   268,    60,    53,   124,   235,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,    50,   268,   268,
     268,   262,   159,    60,    60,    60,    60,    52,   124,    63,
      77,   171,   172,   268,    55,    47,   251,    64,    65,    45,
      55,   268,    55,    53,    47,   259,   127,    53,    56,    64,
      65,   250,   268,   268,   268,   268,    46,    53,    60,   170,
     172,   268,   268,   127,    45,   166,    53,    56,    60,    47,
     167,   168,   172,    55,   124,    60
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
     132,   133,   133,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   138,   138,   140,   141,   139,   142,   142,   142,
     142,   143,   144,   144,   145,   145,   146,   146,   147,   149,
     150,   148,   151,   151,   152,   152,   152,   152,   154,   155,
     153,   156,   156,   158,   157,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   162,   161,   163,   163,   164,   164,
     165,   166,   166,   167,   168,   168,   169,   169,   170,   170,
     171,   171,   171,   171,   172,   172,   172,   172,   172,   173,
     173,   173,   174,   176,   177,   175,   178,   178,   179,   179,
     179,   179,   179,   180,   182,   183,   181,   181,   181,   184,
     185,   185,   187,   186,   188,   188,   189,   188,   190,   191,
     191,   191,   191,   191,   192,   192,   193,   193,   194,   195,
     196,   196,   197,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   199,   199,   199,   200,   200,   201,
     202,   202,   203,   203,   203,   203,   204,   204,   204,   205,
     205,   205,   206,   206,   207,   207,   207,   207,   207,   208,
     208,   208,   208,   210,   211,   209,   212,   214,   215,   213,
     216,   216,   217,   219,   218,   220,   218,   221,   221,   222,
     223,   224,   225,   225,   226,   226,   226,   226,   227,   227,
     228,   228,   229,   230,   231,   231,   232,   232,   233,   234,
     234,   234,   234,   234,   234,   234,   234,   236,   235,   237,
     237,   238,   239,   239,   240,   240,   241,   241,   242,   242,
     242,   242,   243,   244,   244,   245,   245,   245,   245,   246,
     246,   247,   248,   248,   249,   250,   250,   251,   252,   252,
     253,   254,   254,   255,   256,   256,   257,   258,   259,   259,
     260,   260,   261,   261,   261,   262,   262,   262,   263,   263,
     265,   264,   266,   266,   266,   266,   267,   267,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     269,   269,   269,   269,   269,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   271,   271,   272,   272
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
       1,     1,     3,     3,     0,     1,     1,     3,     4,     6,
       1,     1,     1,     0,     0,     0,     9,     7,     6,     9,
       8,     3,     0,     2,     1,     1,     0,     3,     1,     0,
       0,     8,     0,     2,     1,     1,     1,     1,     0,     0,
       9,     1,     2,     0,     8,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     5,     0,     2,     2,     1,
       7,     0,     2,     4,     1,     1,     5,     3,     1,     3,
       3,     3,     1,     1,     1,     3,     3,     1,     1,    10,
      10,    10,     7,     0,     0,     9,     0,     2,     1,     1,
       1,     1,     1,     1,     0,     0,     9,     1,     4,     4,
       0,     2,     0,     7,     3,     4,     0,     2,     6,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     4,
       4,     4,     4,     1,     1,     1,     1,     1,     4,     4,
       4,     6,     6,     6,     1,     1,     1,     0,     1,     3,
       1,     3,     1,     1,     1,     1,     0,     1,     3,     1,
       1,     1,     1,     3,     1,     2,     2,     2,     2,     1,
       1,     1,     1,     0,     0,     9,     7,     0,     0,     9,
       0,     2,     4,     0,     7,     0,     8,     1,     3,     3,
       4,     4,     1,     3,     4,     4,     4,     4,     1,     4,
       5,     8,     1,     2,     2,     3,     5,     7,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     5,     0,
       2,     7,     0,     2,     3,     2,     1,     1,     1,     1,
       1,     1,     6,     1,     2,     5,     5,     7,     6,     0,
       2,     5,     0,     2,     3,     1,     4,     5,     1,     2,
       7,     5,     4,     7,     0,     2,     1,     2,     0,     1,
       1,     3,     1,     3,     1,     0,     1,     3,     1,     2,
       0,     3,     1,     1,     2,     2,     3,     5,     1,     1,
       1,     1,     1,     1,     2,     4,     6,     3,     3,     3,
       2,     2,     2,     2,     2,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     1,
       0,     7,     4,     4,     4,     1,     1,     1,     1,     1,
       1,     2,     4,     6,     3,     2,     2,     2,     2,     2,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     1,     1,     1,     1
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
#line 2783 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2789 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2795 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2801 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2807 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2813 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2819 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2825 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2831 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2837 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2843 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2849 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2855 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2861 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2867 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2873 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2879 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2885 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2891 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2897 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2903 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2909 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2915 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2921 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2927 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2933 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2939 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2945 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2951 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2957 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2963 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 2969 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 2975 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 2981 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 2987 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 2993 "p4parser.tab.c"
    break;

  case 42:
#line 319 "p4parser.y"
              {}
#line 2999 "p4parser.tab.c"
    break;

  case 43:
#line 321 "p4parser.y"
        {}
#line 3005 "p4parser.tab.c"
    break;

  case 44:
#line 323 "p4parser.y"
        {}
#line 3011 "p4parser.tab.c"
    break;

  case 45:
#line 327 "p4parser.y"
                       {}
#line 3017 "p4parser.tab.c"
    break;

  case 46:
#line 328 "p4parser.y"
                       {}
#line 3023 "p4parser.tab.c"
    break;

  case 47:
#line 329 "p4parser.y"
                       {}
#line 3029 "p4parser.tab.c"
    break;

  case 48:
#line 330 "p4parser.y"
                       {}
#line 3035 "p4parser.tab.c"
    break;

  case 49:
#line 331 "p4parser.y"
                       {}
#line 3041 "p4parser.tab.c"
    break;

  case 50:
#line 332 "p4parser.y"
                       {}
#line 3047 "p4parser.tab.c"
    break;

  case 51:
#line 333 "p4parser.y"
                       {}
#line 3053 "p4parser.tab.c"
    break;

  case 52:
#line 334 "p4parser.y"
                       {}
#line 3059 "p4parser.tab.c"
    break;

  case 53:
#line 335 "p4parser.y"
                       {}
#line 3065 "p4parser.tab.c"
    break;

  case 54:
#line 336 "p4parser.y"
                       {}
#line 3071 "p4parser.tab.c"
    break;

  case 55:
#line 337 "p4parser.y"
                       {}
#line 3077 "p4parser.tab.c"
    break;

  case 56:
#line 338 "p4parser.y"
                       {}
#line 3083 "p4parser.tab.c"
    break;

  case 57:
#line 339 "p4parser.y"
                       {}
#line 3089 "p4parser.tab.c"
    break;

  case 58:
#line 340 "p4parser.y"
                       {}
#line 3095 "p4parser.tab.c"
    break;

  case 59:
#line 341 "p4parser.y"
                       {}
#line 3101 "p4parser.tab.c"
    break;

  case 60:
#line 342 "p4parser.y"
                       {}
#line 3107 "p4parser.tab.c"
    break;

  case 61:
#line 343 "p4parser.y"
                       {}
#line 3113 "p4parser.tab.c"
    break;

  case 62:
#line 344 "p4parser.y"
                       {}
#line 3119 "p4parser.tab.c"
    break;

  case 63:
#line 345 "p4parser.y"
                       {}
#line 3125 "p4parser.tab.c"
    break;

  case 64:
#line 346 "p4parser.y"
                       {}
#line 3131 "p4parser.tab.c"
    break;

  case 65:
#line 347 "p4parser.y"
                       {}
#line 3137 "p4parser.tab.c"
    break;

  case 66:
#line 348 "p4parser.y"
                       {}
#line 3143 "p4parser.tab.c"
    break;

  case 67:
#line 349 "p4parser.y"
                       {}
#line 3149 "p4parser.tab.c"
    break;

  case 68:
#line 350 "p4parser.y"
                       {}
#line 3155 "p4parser.tab.c"
    break;

  case 69:
#line 351 "p4parser.y"
                       {}
#line 3161 "p4parser.tab.c"
    break;

  case 70:
#line 352 "p4parser.y"
                       {}
#line 3167 "p4parser.tab.c"
    break;

  case 71:
#line 353 "p4parser.y"
                       {}
#line 3173 "p4parser.tab.c"
    break;

  case 72:
#line 354 "p4parser.y"
                       {}
#line 3179 "p4parser.tab.c"
    break;

  case 73:
#line 355 "p4parser.y"
                       {}
#line 3185 "p4parser.tab.c"
    break;

  case 74:
#line 356 "p4parser.y"
                       {}
#line 3191 "p4parser.tab.c"
    break;

  case 75:
#line 357 "p4parser.y"
                       {}
#line 3197 "p4parser.tab.c"
    break;

  case 76:
#line 358 "p4parser.y"
                       {}
#line 3203 "p4parser.tab.c"
    break;

  case 77:
#line 359 "p4parser.y"
                       {}
#line 3209 "p4parser.tab.c"
    break;

  case 78:
#line 360 "p4parser.y"
                       {}
#line 3215 "p4parser.tab.c"
    break;

  case 79:
#line 361 "p4parser.y"
                       {}
#line 3221 "p4parser.tab.c"
    break;

  case 80:
#line 362 "p4parser.y"
                       {}
#line 3227 "p4parser.tab.c"
    break;

  case 81:
#line 363 "p4parser.y"
                       {}
#line 3233 "p4parser.tab.c"
    break;

  case 82:
#line 364 "p4parser.y"
                       {}
#line 3239 "p4parser.tab.c"
    break;

  case 83:
#line 365 "p4parser.y"
                       {}
#line 3245 "p4parser.tab.c"
    break;

  case 84:
#line 366 "p4parser.y"
                       {}
#line 3251 "p4parser.tab.c"
    break;

  case 85:
#line 367 "p4parser.y"
                       {}
#line 3257 "p4parser.tab.c"
    break;

  case 86:
#line 368 "p4parser.y"
                       {}
#line 3263 "p4parser.tab.c"
    break;

  case 87:
#line 369 "p4parser.y"
                       {}
#line 3269 "p4parser.tab.c"
    break;

  case 88:
#line 370 "p4parser.y"
                       {}
#line 3275 "p4parser.tab.c"
    break;

  case 89:
#line 371 "p4parser.y"
                       {}
#line 3281 "p4parser.tab.c"
    break;

  case 90:
#line 372 "p4parser.y"
                            {}
#line 3287 "p4parser.tab.c"
    break;

  case 91:
#line 374 "p4parser.y"
                       {}
#line 3293 "p4parser.tab.c"
    break;

  case 92:
#line 375 "p4parser.y"
                       {}
#line 3299 "p4parser.tab.c"
    break;

  case 93:
#line 376 "p4parser.y"
                       {}
#line 3305 "p4parser.tab.c"
    break;

  case 94:
#line 377 "p4parser.y"
                       {}
#line 3311 "p4parser.tab.c"
    break;

  case 95:
#line 378 "p4parser.y"
                       {}
#line 3317 "p4parser.tab.c"
    break;

  case 96:
#line 379 "p4parser.y"
                       {}
#line 3323 "p4parser.tab.c"
    break;

  case 97:
#line 380 "p4parser.y"
                       {}
#line 3329 "p4parser.tab.c"
    break;

  case 98:
#line 381 "p4parser.y"
                       {}
#line 3335 "p4parser.tab.c"
    break;

  case 99:
#line 382 "p4parser.y"
                       {}
#line 3341 "p4parser.tab.c"
    break;

  case 100:
#line 383 "p4parser.y"
                       {}
#line 3347 "p4parser.tab.c"
    break;

  case 101:
#line 384 "p4parser.y"
                       {}
#line 3353 "p4parser.tab.c"
    break;

  case 102:
#line 385 "p4parser.y"
                       {}
#line 3359 "p4parser.tab.c"
    break;

  case 103:
#line 386 "p4parser.y"
                       {}
#line 3365 "p4parser.tab.c"
    break;

  case 104:
#line 387 "p4parser.y"
                       {}
#line 3371 "p4parser.tab.c"
    break;

  case 105:
#line 388 "p4parser.y"
                       {}
#line 3377 "p4parser.tab.c"
    break;

  case 106:
#line 389 "p4parser.y"
                       {}
#line 3383 "p4parser.tab.c"
    break;

  case 108:
#line 391 "p4parser.y"
                       {}
#line 3389 "p4parser.tab.c"
    break;

  case 109:
#line 392 "p4parser.y"
                       {}
#line 3395 "p4parser.tab.c"
    break;

  case 110:
#line 393 "p4parser.y"
                       {}
#line 3401 "p4parser.tab.c"
    break;

  case 111:
#line 394 "p4parser.y"
                       {}
#line 3407 "p4parser.tab.c"
    break;

  case 112:
#line 395 "p4parser.y"
                       {}
#line 3413 "p4parser.tab.c"
    break;

  case 113:
#line 396 "p4parser.y"
                       {}
#line 3419 "p4parser.tab.c"
    break;

  case 114:
#line 397 "p4parser.y"
                       {}
#line 3425 "p4parser.tab.c"
    break;

  case 115:
#line 398 "p4parser.y"
                       {}
#line 3431 "p4parser.tab.c"
    break;

  case 116:
#line 399 "p4parser.y"
                       {}
#line 3437 "p4parser.tab.c"
    break;

  case 117:
#line 400 "p4parser.y"
                       {}
#line 3443 "p4parser.tab.c"
    break;

  case 118:
#line 401 "p4parser.y"
                       {}
#line 3449 "p4parser.tab.c"
    break;

  case 119:
#line 402 "p4parser.y"
                       {}
#line 3455 "p4parser.tab.c"
    break;

  case 120:
#line 403 "p4parser.y"
                       {}
#line 3461 "p4parser.tab.c"
    break;

  case 121:
#line 404 "p4parser.y"
                       {}
#line 3467 "p4parser.tab.c"
    break;

  case 122:
#line 405 "p4parser.y"
                       {}
#line 3473 "p4parser.tab.c"
    break;

  case 123:
#line 406 "p4parser.y"
                       {}
#line 3479 "p4parser.tab.c"
    break;

  case 124:
#line 407 "p4parser.y"
                       {}
#line 3485 "p4parser.tab.c"
    break;

  case 125:
#line 408 "p4parser.y"
                       {}
#line 3491 "p4parser.tab.c"
    break;

  case 126:
#line 409 "p4parser.y"
                       {}
#line 3497 "p4parser.tab.c"
    break;

  case 127:
#line 410 "p4parser.y"
                       {}
#line 3503 "p4parser.tab.c"
    break;

  case 128:
#line 411 "p4parser.y"
                       {}
#line 3509 "p4parser.tab.c"
    break;

  case 129:
#line 412 "p4parser.y"
                       {}
#line 3515 "p4parser.tab.c"
    break;

  case 130:
#line 413 "p4parser.y"
                       {}
#line 3521 "p4parser.tab.c"
    break;

  case 131:
#line 417 "p4parser.y"
                                      {}
#line 3527 "p4parser.tab.c"
    break;

  case 132:
#line 418 "p4parser.y"
                                        {}
#line 3533 "p4parser.tab.c"
    break;

  case 133:
#line 422 "p4parser.y"
                                         {}
#line 3539 "p4parser.tab.c"
    break;

  case 134:
#line 426 "p4parser.y"
                                      {}
#line 3545 "p4parser.tab.c"
    break;

  case 135:
#line 427 "p4parser.y"
                                      {}
#line 3551 "p4parser.tab.c"
    break;

  case 136:
#line 431 "p4parser.y"
                                          {}
#line 3557 "p4parser.tab.c"
    break;

  case 137:
#line 432 "p4parser.y"
                                            {}
#line 3563 "p4parser.tab.c"
    break;

  case 138:
#line 436 "p4parser.y"
                                            {}
#line 3569 "p4parser.tab.c"
    break;

  case 139:
#line 437 "p4parser.y"
                                                              {}
#line 3575 "p4parser.tab.c"
    break;

  case 140:
#line 441 "p4parser.y"
                 {}
#line 3581 "p4parser.tab.c"
    break;

  case 141:
#line 442 "p4parser.y"
                   {}
#line 3587 "p4parser.tab.c"
    break;

  case 142:
#line 443 "p4parser.y"
                   {}
#line 3593 "p4parser.tab.c"
    break;

  case 143:
#line 444 "p4parser.y"
                   {}
#line 3599 "p4parser.tab.c"
    break;

  case 144:
#line 448 "p4parser.y"
                                  {}
#line 3605 "p4parser.tab.c"
    break;

  case 145:
#line 449 "p4parser.y"
                        {}
#line 3611 "p4parser.tab.c"
    break;

  case 146:
#line 450 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3620 "p4parser.tab.c"
    break;

  case 147:
#line 458 "p4parser.y"
                     {}
#line 3626 "p4parser.tab.c"
    break;

  case 148:
#line 460 "p4parser.y"
                     {}
#line 3632 "p4parser.tab.c"
    break;

  case 149:
#line 463 "p4parser.y"
                     {}
#line 3638 "p4parser.tab.c"
    break;

  case 150:
#line 466 "p4parser.y"
                     {}
#line 3644 "p4parser.tab.c"
    break;

  case 151:
#line 472 "p4parser.y"
                               {}
#line 3650 "p4parser.tab.c"
    break;

  case 152:
#line 476 "p4parser.y"
                                     {}
#line 3656 "p4parser.tab.c"
    break;

  case 153:
#line 477 "p4parser.y"
                                     {}
#line 3662 "p4parser.tab.c"
    break;

  case 154:
#line 481 "p4parser.y"
                               {}
#line 3668 "p4parser.tab.c"
    break;

  case 155:
#line 482 "p4parser.y"
                               {}
#line 3674 "p4parser.tab.c"
    break;

  case 156:
#line 486 "p4parser.y"
                           {}
#line 3680 "p4parser.tab.c"
    break;

  case 157:
#line 487 "p4parser.y"
                                     {}
#line 3686 "p4parser.tab.c"
    break;

  case 158:
#line 491 "p4parser.y"
                             {}
#line 3692 "p4parser.tab.c"
    break;

  case 159:
#line 497 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3698 "p4parser.tab.c"
    break;

  case 160:
#line 498 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3704 "p4parser.tab.c"
    break;

  case 161:
#line 499 "p4parser.y"
                             {}
#line 3710 "p4parser.tab.c"
    break;

  case 162:
#line 504 "p4parser.y"
                                           {}
#line 3716 "p4parser.tab.c"
    break;

  case 163:
#line 505 "p4parser.y"
                                             {}
#line 3722 "p4parser.tab.c"
    break;

  case 164:
#line 509 "p4parser.y"
                                    {}
#line 3728 "p4parser.tab.c"
    break;

  case 165:
#line 510 "p4parser.y"
                                      {}
#line 3734 "p4parser.tab.c"
    break;

  case 166:
#line 511 "p4parser.y"
                                      {}
#line 3740 "p4parser.tab.c"
    break;

  case 167:
#line 512 "p4parser.y"
                                      {}
#line 3746 "p4parser.tab.c"
    break;

  case 168:
#line 517 "p4parser.y"
                          {}
#line 3752 "p4parser.tab.c"
    break;

  case 169:
#line 518 "p4parser.y"
                          {}
#line 3758 "p4parser.tab.c"
    break;

  case 170:
#line 519 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3767 "p4parser.tab.c"
    break;

  case 171:
#line 526 "p4parser.y"
                                    {}
#line 3773 "p4parser.tab.c"
    break;

  case 172:
#line 527 "p4parser.y"
                                      {}
#line 3779 "p4parser.tab.c"
    break;

  case 173:
#line 531 "p4parser.y"
                              {}
#line 3785 "p4parser.tab.c"
    break;

  case 174:
#line 533 "p4parser.y"
                                      {}
#line 3791 "p4parser.tab.c"
    break;

  case 175:
#line 537 "p4parser.y"
                                     {}
#line 3797 "p4parser.tab.c"
    break;

  case 176:
#line 538 "p4parser.y"
                                       {}
#line 3803 "p4parser.tab.c"
    break;

  case 177:
#line 542 "p4parser.y"
                                    {}
#line 3809 "p4parser.tab.c"
    break;

  case 178:
#line 543 "p4parser.y"
                                      {}
#line 3815 "p4parser.tab.c"
    break;

  case 179:
#line 544 "p4parser.y"
                                      {}
#line 3821 "p4parser.tab.c"
    break;

  case 180:
#line 545 "p4parser.y"
                                      {}
#line 3827 "p4parser.tab.c"
    break;

  case 181:
#line 546 "p4parser.y"
                                      {}
#line 3833 "p4parser.tab.c"
    break;

  case 182:
#line 547 "p4parser.y"
                                      {}
#line 3839 "p4parser.tab.c"
    break;

  case 183:
#line 548 "p4parser.y"
                                      {}
#line 3845 "p4parser.tab.c"
    break;

  case 184:
#line 552 "p4parser.y"
                           {}
#line 3851 "p4parser.tab.c"
    break;

  case 185:
#line 553 "p4parser.y"
                               {}
#line 3857 "p4parser.tab.c"
    break;

  case 186:
#line 557 "p4parser.y"
                                {}
#line 3863 "p4parser.tab.c"
    break;

  case 187:
#line 558 "p4parser.y"
                                  {}
#line 3869 "p4parser.tab.c"
    break;

  case 188:
#line 562 "p4parser.y"
                           {}
#line 3875 "p4parser.tab.c"
    break;

  case 189:
#line 563 "p4parser.y"
                       {}
#line 3881 "p4parser.tab.c"
    break;

  case 190:
#line 568 "p4parser.y"
                              {}
#line 3887 "p4parser.tab.c"
    break;

  case 191:
#line 572 "p4parser.y"
                               {}
#line 3893 "p4parser.tab.c"
    break;

  case 192:
#line 573 "p4parser.y"
                                 {}
#line 3899 "p4parser.tab.c"
    break;

  case 193:
#line 578 "p4parser.y"
      {}
#line 3905 "p4parser.tab.c"
    break;

  case 194:
#line 582 "p4parser.y"
                              {}
#line 3911 "p4parser.tab.c"
    break;

  case 195:
#line 583 "p4parser.y"
                                {}
#line 3917 "p4parser.tab.c"
    break;

  case 196:
#line 588 "p4parser.y"
                                {}
#line 3923 "p4parser.tab.c"
    break;

  case 197:
#line 589 "p4parser.y"
                                                    {}
#line 3929 "p4parser.tab.c"
    break;

  case 198:
#line 593 "p4parser.y"
                           {}
#line 3935 "p4parser.tab.c"
    break;

  case 199:
#line 594 "p4parser.y"
                                                        {}
#line 3941 "p4parser.tab.c"
    break;

  case 200:
#line 599 "p4parser.y"
                                 {}
#line 3947 "p4parser.tab.c"
    break;

  case 201:
#line 600 "p4parser.y"
                                   {}
#line 3953 "p4parser.tab.c"
    break;

  case 202:
#line 601 "p4parser.y"
                                  {}
#line 3959 "p4parser.tab.c"
    break;

  case 203:
#line 602 "p4parser.y"
                                       {}
#line 3965 "p4parser.tab.c"
    break;

  case 204:
#line 606 "p4parser.y"
                                {}
#line 3971 "p4parser.tab.c"
    break;

  case 205:
#line 607 "p4parser.y"
                                 {}
#line 3977 "p4parser.tab.c"
    break;

  case 206:
#line 608 "p4parser.y"
                                   {}
#line 3983 "p4parser.tab.c"
    break;

  case 207:
#line 609 "p4parser.y"
                                  {}
#line 3989 "p4parser.tab.c"
    break;

  case 208:
#line 610 "p4parser.y"
                                       {}
#line 3995 "p4parser.tab.c"
    break;

  case 209:
#line 616 "p4parser.y"
        {}
#line 4001 "p4parser.tab.c"
    break;

  case 210:
#line 619 "p4parser.y"
        {}
#line 4007 "p4parser.tab.c"
    break;

  case 211:
#line 622 "p4parser.y"
        {}
#line 4013 "p4parser.tab.c"
    break;

  case 212:
#line 630 "p4parser.y"
        {}
#line 4019 "p4parser.tab.c"
    break;

  case 213:
#line 635 "p4parser.y"
                     {}
#line 4025 "p4parser.tab.c"
    break;

  case 214:
#line 636 "p4parser.y"
                          {}
#line 4031 "p4parser.tab.c"
    break;

  case 215:
#line 637 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4040 "p4parser.tab.c"
    break;

  case 216:
#line 644 "p4parser.y"
           {}
#line 4046 "p4parser.tab.c"
    break;

  case 217:
#line 645 "p4parser.y"
                                                       {}
#line 4052 "p4parser.tab.c"
    break;

  case 218:
#line 649 "p4parser.y"
                             {}
#line 4058 "p4parser.tab.c"
    break;

  case 219:
#line 650 "p4parser.y"
                               {}
#line 4064 "p4parser.tab.c"
    break;

  case 220:
#line 651 "p4parser.y"
                               {}
#line 4070 "p4parser.tab.c"
    break;

  case 221:
#line 652 "p4parser.y"
                               {}
#line 4076 "p4parser.tab.c"
    break;

  case 222:
#line 653 "p4parser.y"
                               {}
#line 4082 "p4parser.tab.c"
    break;

  case 223:
#line 657 "p4parser.y"
                   {}
#line 4088 "p4parser.tab.c"
    break;

  case 224:
#line 664 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4097 "p4parser.tab.c"
    break;

  case 225:
#line 668 "p4parser.y"
                          {}
#line 4103 "p4parser.tab.c"
    break;

  case 230:
#line 679 "p4parser.y"
                                     {}
#line 4109 "p4parser.tab.c"
    break;

  case 231:
#line 680 "p4parser.y"
                                       {}
#line 4115 "p4parser.tab.c"
    break;

  case 232:
#line 685 "p4parser.y"
                               {}
#line 4121 "p4parser.tab.c"
    break;

  case 233:
#line 686 "p4parser.y"
                                      {}
#line 4127 "p4parser.tab.c"
    break;

  case 234:
#line 690 "p4parser.y"
                                               {}
#line 4133 "p4parser.tab.c"
    break;

  case 235:
#line 691 "p4parser.y"
                                                          {}
#line 4139 "p4parser.tab.c"
    break;

  case 236:
#line 692 "p4parser.y"
                                 {}
#line 4145 "p4parser.tab.c"
    break;

  case 237:
#line 693 "p4parser.y"
                                        {}
#line 4151 "p4parser.tab.c"
    break;

  case 239:
#line 703 "p4parser.y"
                                     {}
#line 4157 "p4parser.tab.c"
    break;

  case 240:
#line 704 "p4parser.y"
                                       {}
#line 4163 "p4parser.tab.c"
    break;

  case 241:
#line 705 "p4parser.y"
                                       {}
#line 4169 "p4parser.tab.c"
    break;

  case 242:
#line 706 "p4parser.y"
                                       {}
#line 4175 "p4parser.tab.c"
    break;

  case 243:
#line 707 "p4parser.y"
                                       {}
#line 4181 "p4parser.tab.c"
    break;

  case 244:
#line 711 "p4parser.y"
                                     {}
#line 4187 "p4parser.tab.c"
    break;

  case 245:
#line 712 "p4parser.y"
                                       {}
#line 4193 "p4parser.tab.c"
    break;

  case 246:
#line 716 "p4parser.y"
                                     {}
#line 4199 "p4parser.tab.c"
    break;

  case 247:
#line 717 "p4parser.y"
                                       {}
#line 4205 "p4parser.tab.c"
    break;

  case 248:
#line 721 "p4parser.y"
                                     {}
#line 4211 "p4parser.tab.c"
    break;

  case 249:
#line 725 "p4parser.y"
                                              {}
#line 4217 "p4parser.tab.c"
    break;

  case 250:
#line 729 "p4parser.y"
                                                    {}
#line 4223 "p4parser.tab.c"
    break;

  case 251:
#line 730 "p4parser.y"
                                                      {}
#line 4229 "p4parser.tab.c"
    break;

  case 252:
#line 734 "p4parser.y"
                                              {}
#line 4235 "p4parser.tab.c"
    break;

  case 253:
#line 738 "p4parser.y"
           {}
#line 4241 "p4parser.tab.c"
    break;

  case 254:
#line 739 "p4parser.y"
             {}
#line 4247 "p4parser.tab.c"
    break;

  case 255:
#line 740 "p4parser.y"
             {}
#line 4253 "p4parser.tab.c"
    break;

  case 256:
#line 741 "p4parser.y"
             {}
#line 4259 "p4parser.tab.c"
    break;

  case 257:
#line 742 "p4parser.y"
             {}
#line 4265 "p4parser.tab.c"
    break;

  case 258:
#line 744 "p4parser.y"
      {}
#line 4271 "p4parser.tab.c"
    break;

  case 259:
#line 746 "p4parser.y"
      {}
#line 4277 "p4parser.tab.c"
    break;

  case 260:
#line 748 "p4parser.y"
      {}
#line 4283 "p4parser.tab.c"
    break;

  case 261:
#line 751 "p4parser.y"
      {}
#line 4289 "p4parser.tab.c"
    break;

  case 262:
#line 753 "p4parser.y"
      {}
#line 4295 "p4parser.tab.c"
    break;

  case 263:
#line 755 "p4parser.y"
      {}
#line 4301 "p4parser.tab.c"
    break;

  case 264:
#line 759 "p4parser.y"
                {}
#line 4307 "p4parser.tab.c"
    break;

  case 265:
#line 760 "p4parser.y"
                  {}
#line 4313 "p4parser.tab.c"
    break;

  case 266:
#line 761 "p4parser.y"
                  {}
#line 4319 "p4parser.tab.c"
    break;

  case 267:
#line 766 "p4parser.y"
                              {}
#line 4325 "p4parser.tab.c"
    break;

  case 268:
#line 767 "p4parser.y"
                                {}
#line 4331 "p4parser.tab.c"
    break;

  case 269:
#line 771 "p4parser.y"
                                      {}
#line 4337 "p4parser.tab.c"
    break;

  case 270:
#line 775 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4349 "p4parser.tab.c"
    break;

  case 271:
#line 782 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4357 "p4parser.tab.c"
    break;

  case 272:
#line 788 "p4parser.y"
                                {}
#line 4363 "p4parser.tab.c"
    break;

  case 273:
#line 789 "p4parser.y"
                                  {}
#line 4369 "p4parser.tab.c"
    break;

  case 274:
#line 791 "p4parser.y"
                                  {}
#line 4375 "p4parser.tab.c"
    break;

  case 275:
#line 792 "p4parser.y"
                                       {}
#line 4381 "p4parser.tab.c"
    break;

  case 276:
#line 796 "p4parser.y"
                                   {}
#line 4387 "p4parser.tab.c"
    break;

  case 277:
#line 797 "p4parser.y"
                                     {}
#line 4393 "p4parser.tab.c"
    break;

  case 278:
#line 798 "p4parser.y"
                                       {}
#line 4399 "p4parser.tab.c"
    break;

  case 279:
#line 802 "p4parser.y"
                                {}
#line 4405 "p4parser.tab.c"
    break;

  case 280:
#line 803 "p4parser.y"
                                  {}
#line 4411 "p4parser.tab.c"
    break;

  case 281:
#line 804 "p4parser.y"
                                       {}
#line 4417 "p4parser.tab.c"
    break;

  case 282:
#line 810 "p4parser.y"
                                       {}
#line 4423 "p4parser.tab.c"
    break;

  case 283:
#line 811 "p4parser.y"
                                           {}
#line 4429 "p4parser.tab.c"
    break;

  case 284:
#line 815 "p4parser.y"
                               {}
#line 4435 "p4parser.tab.c"
    break;

  case 285:
#line 816 "p4parser.y"
                                       {}
#line 4441 "p4parser.tab.c"
    break;

  case 286:
#line 817 "p4parser.y"
                                       {}
#line 4447 "p4parser.tab.c"
    break;

  case 287:
#line 818 "p4parser.y"
                                       {}
#line 4453 "p4parser.tab.c"
    break;

  case 288:
#line 819 "p4parser.y"
                                       {}
#line 4459 "p4parser.tab.c"
    break;

  case 289:
#line 823 "p4parser.y"
                                     {}
#line 4465 "p4parser.tab.c"
    break;

  case 290:
#line 824 "p4parser.y"
                                       {}
#line 4471 "p4parser.tab.c"
    break;

  case 291:
#line 825 "p4parser.y"
                                       {}
#line 4477 "p4parser.tab.c"
    break;

  case 292:
#line 826 "p4parser.y"
                                       {}
#line 4483 "p4parser.tab.c"
    break;

  case 293:
#line 830 "p4parser.y"
                               {}
#line 4489 "p4parser.tab.c"
    break;

  case 294:
#line 830 "p4parser.y"
                                                    {}
#line 4495 "p4parser.tab.c"
    break;

  case 295:
#line 832 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4504 "p4parser.tab.c"
    break;

  case 296:
#line 841 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4513 "p4parser.tab.c"
    break;

  case 297:
#line 848 "p4parser.y"
                                     {}
#line 4519 "p4parser.tab.c"
    break;

  case 298:
#line 848 "p4parser.y"
                                                          {}
#line 4525 "p4parser.tab.c"
    break;

  case 299:
#line 849 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4534 "p4parser.tab.c"
    break;

  case 300:
#line 856 "p4parser.y"
                                     {}
#line 4540 "p4parser.tab.c"
    break;

  case 301:
#line 857 "p4parser.y"
                                       {}
#line 4546 "p4parser.tab.c"
    break;

  case 302:
#line 861 "p4parser.y"
                                           {}
#line 4552 "p4parser.tab.c"
    break;

  case 303:
#line 866 "p4parser.y"
                  {}
#line 4558 "p4parser.tab.c"
    break;

  case 304:
#line 867 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4567 "p4parser.tab.c"
    break;

  case 305:
#line 871 "p4parser.y"
                                       {}
#line 4573 "p4parser.tab.c"
    break;

  case 306:
#line 872 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4582 "p4parser.tab.c"
    break;

  case 307:
#line 879 "p4parser.y"
                            {}
#line 4588 "p4parser.tab.c"
    break;

  case 308:
#line 880 "p4parser.y"
                                                        {}
#line 4594 "p4parser.tab.c"
    break;

  case 309:
#line 884 "p4parser.y"
                               {}
#line 4600 "p4parser.tab.c"
    break;

  case 310:
#line 889 "p4parser.y"
        {}
#line 4606 "p4parser.tab.c"
    break;

  case 311:
#line 894 "p4parser.y"
        {}
#line 4612 "p4parser.tab.c"
    break;

  case 312:
#line 899 "p4parser.y"
                            {}
#line 4618 "p4parser.tab.c"
    break;

  case 313:
#line 900 "p4parser.y"
                                {}
#line 4624 "p4parser.tab.c"
    break;

  case 314:
#line 904 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4633 "p4parser.tab.c"
    break;

  case 315:
#line 908 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4642 "p4parser.tab.c"
    break;

  case 316:
#line 912 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4651 "p4parser.tab.c"
    break;

  case 317:
#line 916 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4660 "p4parser.tab.c"
    break;

  case 318:
#line 927 "p4parser.y"
        {}
#line 4666 "p4parser.tab.c"
    break;

  case 319:
#line 929 "p4parser.y"
        {}
#line 4672 "p4parser.tab.c"
    break;

  case 320:
#line 934 "p4parser.y"
        {}
#line 4678 "p4parser.tab.c"
    break;

  case 321:
#line 936 "p4parser.y"
        {}
#line 4684 "p4parser.tab.c"
    break;

  case 322:
#line 940 "p4parser.y"
                   {}
#line 4690 "p4parser.tab.c"
    break;

  case 323:
#line 944 "p4parser.y"
                   {}
#line 4696 "p4parser.tab.c"
    break;

  case 324:
#line 948 "p4parser.y"
                                {}
#line 4702 "p4parser.tab.c"
    break;

  case 325:
#line 949 "p4parser.y"
                                  {}
#line 4708 "p4parser.tab.c"
    break;

  case 326:
#line 954 "p4parser.y"
        {}
#line 4714 "p4parser.tab.c"
    break;

  case 327:
#line 956 "p4parser.y"
        {}
#line 4720 "p4parser.tab.c"
    break;

  case 328:
#line 961 "p4parser.y"
                                                              {}
#line 4726 "p4parser.tab.c"
    break;

  case 329:
#line 965 "p4parser.y"
                                     {}
#line 4732 "p4parser.tab.c"
    break;

  case 330:
#line 966 "p4parser.y"
                                       {}
#line 4738 "p4parser.tab.c"
    break;

  case 331:
#line 967 "p4parser.y"
                                       {}
#line 4744 "p4parser.tab.c"
    break;

  case 332:
#line 968 "p4parser.y"
                                       {}
#line 4750 "p4parser.tab.c"
    break;

  case 333:
#line 969 "p4parser.y"
                                       {}
#line 4756 "p4parser.tab.c"
    break;

  case 334:
#line 970 "p4parser.y"
                                       {}
#line 4762 "p4parser.tab.c"
    break;

  case 335:
#line 971 "p4parser.y"
                                       {}
#line 4768 "p4parser.tab.c"
    break;

  case 336:
#line 972 "p4parser.y"
                                       {}
#line 4774 "p4parser.tab.c"
    break;

  case 337:
#line 976 "p4parser.y"
                           {}
#line 4780 "p4parser.tab.c"
    break;

  case 338:
#line 977 "p4parser.y"
                             {}
#line 4786 "p4parser.tab.c"
    break;

  case 339:
#line 981 "p4parser.y"
                                          {}
#line 4792 "p4parser.tab.c"
    break;

  case 340:
#line 982 "p4parser.y"
                                            {}
#line 4798 "p4parser.tab.c"
    break;

  case 341:
#line 986 "p4parser.y"
                                                                  {}
#line 4804 "p4parser.tab.c"
    break;

  case 342:
#line 990 "p4parser.y"
                             {}
#line 4810 "p4parser.tab.c"
    break;

  case 343:
#line 991 "p4parser.y"
                               {}
#line 4816 "p4parser.tab.c"
    break;

  case 344:
#line 995 "p4parser.y"
                                     {}
#line 4822 "p4parser.tab.c"
    break;

  case 345:
#line 996 "p4parser.y"
                                       {}
#line 4828 "p4parser.tab.c"
    break;

  case 346:
#line 1000 "p4parser.y"
                             {}
#line 4834 "p4parser.tab.c"
    break;

  case 347:
#line 1001 "p4parser.y"
                               {}
#line 4840 "p4parser.tab.c"
    break;

  case 348:
#line 1005 "p4parser.y"
                             {}
#line 4846 "p4parser.tab.c"
    break;

  case 349:
#line 1006 "p4parser.y"
                               {}
#line 4852 "p4parser.tab.c"
    break;

  case 350:
#line 1007 "p4parser.y"
                               {}
#line 4858 "p4parser.tab.c"
    break;

  case 351:
#line 1008 "p4parser.y"
                               {}
#line 4864 "p4parser.tab.c"
    break;

  case 352:
#line 1016 "p4parser.y"
          {}
#line 4870 "p4parser.tab.c"
    break;

  case 353:
#line 1020 "p4parser.y"
                                       {}
#line 4876 "p4parser.tab.c"
    break;

  case 354:
#line 1021 "p4parser.y"
                                         {}
#line 4882 "p4parser.tab.c"
    break;

  case 355:
#line 1026 "p4parser.y"
        {}
#line 4888 "p4parser.tab.c"
    break;

  case 356:
#line 1028 "p4parser.y"
        {}
#line 4894 "p4parser.tab.c"
    break;

  case 357:
#line 1030 "p4parser.y"
        {}
#line 4900 "p4parser.tab.c"
    break;

  case 358:
#line 1032 "p4parser.y"
        {}
#line 4906 "p4parser.tab.c"
    break;

  case 359:
#line 1036 "p4parser.y"
                                       {}
#line 4912 "p4parser.tab.c"
    break;

  case 360:
#line 1037 "p4parser.y"
                                         {}
#line 4918 "p4parser.tab.c"
    break;

  case 361:
#line 1042 "p4parser.y"
                                         {}
#line 4924 "p4parser.tab.c"
    break;

  case 362:
#line 1046 "p4parser.y"
           {}
#line 4930 "p4parser.tab.c"
    break;

  case 363:
#line 1048 "p4parser.y"
        {}
#line 4936 "p4parser.tab.c"
    break;

  case 365:
#line 1057 "p4parser.y"
        {}
#line 4942 "p4parser.tab.c"
    break;

  case 366:
#line 1059 "p4parser.y"
        {}
#line 4948 "p4parser.tab.c"
    break;

  case 367:
#line 1064 "p4parser.y"
        {}
#line 4954 "p4parser.tab.c"
    break;

  case 368:
#line 1068 "p4parser.y"
                                   {}
#line 4960 "p4parser.tab.c"
    break;

  case 369:
#line 1069 "p4parser.y"
                                     {}
#line 4966 "p4parser.tab.c"
    break;

  case 370:
#line 1075 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4975 "p4parser.tab.c"
    break;

  case 371:
#line 1084 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 4984 "p4parser.tab.c"
    break;

  case 372:
#line 1088 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 4993 "p4parser.tab.c"
    break;

  case 373:
#line 1096 "p4parser.y"
                                     {}
#line 4999 "p4parser.tab.c"
    break;

  case 374:
#line 1100 "p4parser.y"
                                     {}
#line 5005 "p4parser.tab.c"
    break;

  case 375:
#line 1101 "p4parser.y"
                                          {}
#line 5011 "p4parser.tab.c"
    break;

  case 376:
#line 1105 "p4parser.y"
                                        {}
#line 5017 "p4parser.tab.c"
    break;

  case 377:
#line 1111 "p4parser.y"
                                       {}
#line 5023 "p4parser.tab.c"
    break;

  case 378:
#line 1115 "p4parser.y"
                                       {}
#line 5029 "p4parser.tab.c"
    break;

  case 379:
#line 1116 "p4parser.y"
                                         {}
#line 5035 "p4parser.tab.c"
    break;

  case 380:
#line 1120 "p4parser.y"
                                       {}
#line 5041 "p4parser.tab.c"
    break;

  case 381:
#line 1121 "p4parser.y"
                                           {}
#line 5047 "p4parser.tab.c"
    break;

  case 382:
#line 1125 "p4parser.y"
                                       {}
#line 5053 "p4parser.tab.c"
    break;

  case 383:
#line 1126 "p4parser.y"
                                            {}
#line 5059 "p4parser.tab.c"
    break;

  case 384:
#line 1127 "p4parser.y"
                                              {}
#line 5065 "p4parser.tab.c"
    break;

  case 385:
#line 1131 "p4parser.y"
                                       {}
#line 5071 "p4parser.tab.c"
    break;

  case 386:
#line 1132 "p4parser.y"
                                         {}
#line 5077 "p4parser.tab.c"
    break;

  case 387:
#line 1133 "p4parser.y"
                                           {}
#line 5083 "p4parser.tab.c"
    break;

  case 388:
#line 1137 "p4parser.y"
                                       {}
#line 5089 "p4parser.tab.c"
    break;

  case 389:
#line 1138 "p4parser.y"
                                         {}
#line 5095 "p4parser.tab.c"
    break;

  case 390:
#line 1142 "p4parser.y"
        {}
#line 5101 "p4parser.tab.c"
    break;

  case 391:
#line 1142 "p4parser.y"
                {}
#line 5107 "p4parser.tab.c"
    break;

  case 392:
#line 1146 "p4parser.y"
                                       {}
#line 5113 "p4parser.tab.c"
    break;

  case 393:
#line 1147 "p4parser.y"
                                         {}
#line 5119 "p4parser.tab.c"
    break;

  case 394:
#line 1148 "p4parser.y"
                                         {}
#line 5125 "p4parser.tab.c"
    break;

  case 395:
#line 1149 "p4parser.y"
                                       {}
#line 5131 "p4parser.tab.c"
    break;

  case 396:
#line 1153 "p4parser.y"
                                            {}
#line 5137 "p4parser.tab.c"
    break;

  case 397:
#line 1154 "p4parser.y"
                                                      {}
#line 5143 "p4parser.tab.c"
    break;

  case 398:
#line 1157 "p4parser.y"
                                       {}
#line 5149 "p4parser.tab.c"
    break;

  case 399:
#line 1158 "p4parser.y"
                                         {}
#line 5155 "p4parser.tab.c"
    break;

  case 400:
#line 1159 "p4parser.y"
                                         {}
#line 5161 "p4parser.tab.c"
    break;

  case 401:
#line 1160 "p4parser.y"
                                         {}
#line 5167 "p4parser.tab.c"
    break;

  case 402:
#line 1161 "p4parser.y"
                                         {}
#line 5173 "p4parser.tab.c"
    break;

  case 403:
#line 1162 "p4parser.y"
                                         {}
#line 5179 "p4parser.tab.c"
    break;

  case 404:
#line 1163 "p4parser.y"
                                         {}
#line 5185 "p4parser.tab.c"
    break;

  case 405:
#line 1164 "p4parser.y"
                                                     {}
#line 5191 "p4parser.tab.c"
    break;

  case 406:
#line 1165 "p4parser.y"
                                                                 {}
#line 5197 "p4parser.tab.c"
    break;

  case 407:
#line 1166 "p4parser.y"
                                                 {}
#line 5203 "p4parser.tab.c"
    break;

  case 408:
#line 1167 "p4parser.y"
                                                 {}
#line 5209 "p4parser.tab.c"
    break;

  case 409:
#line 1168 "p4parser.y"
                                                 {}
#line 5215 "p4parser.tab.c"
    break;

  case 410:
#line 1169 "p4parser.y"
                                         {}
#line 5221 "p4parser.tab.c"
    break;

  case 411:
#line 1170 "p4parser.y"
                                                {}
#line 5227 "p4parser.tab.c"
    break;

  case 412:
#line 1171 "p4parser.y"
                                           {}
#line 5233 "p4parser.tab.c"
    break;

  case 413:
#line 1172 "p4parser.y"
                                          {}
#line 5239 "p4parser.tab.c"
    break;

  case 414:
#line 1174 "p4parser.y"
        {}
#line 5245 "p4parser.tab.c"
    break;

  case 415:
#line 1176 "p4parser.y"
        {}
#line 5251 "p4parser.tab.c"
    break;

  case 416:
#line 1177 "p4parser.y"
                                         {}
#line 5257 "p4parser.tab.c"
    break;

  case 417:
#line 1178 "p4parser.y"
                                         {}
#line 5263 "p4parser.tab.c"
    break;

  case 418:
#line 1179 "p4parser.y"
                                         {}
#line 5269 "p4parser.tab.c"
    break;

  case 419:
#line 1180 "p4parser.y"
                                         {}
#line 5275 "p4parser.tab.c"
    break;

  case 420:
#line 1181 "p4parser.y"
                                          {}
#line 5281 "p4parser.tab.c"
    break;

  case 421:
#line 1182 "p4parser.y"
                                           {}
#line 5287 "p4parser.tab.c"
    break;

  case 422:
#line 1183 "p4parser.y"
                                            {}
#line 5293 "p4parser.tab.c"
    break;

  case 423:
#line 1184 "p4parser.y"
                                             {}
#line 5299 "p4parser.tab.c"
    break;

  case 424:
#line 1185 "p4parser.y"
                                        {}
#line 5305 "p4parser.tab.c"
    break;

  case 425:
#line 1187 "p4parser.y"
        {}
#line 5311 "p4parser.tab.c"
    break;

  case 426:
#line 1188 "p4parser.y"
                                       {}
#line 5317 "p4parser.tab.c"
    break;

  case 427:
#line 1189 "p4parser.y"
                                       {}
#line 5323 "p4parser.tab.c"
    break;

  case 428:
#line 1191 "p4parser.y"
                                         {}
#line 5329 "p4parser.tab.c"
    break;

  case 429:
#line 1192 "p4parser.y"
                                             {}
#line 5335 "p4parser.tab.c"
    break;

  case 430:
#line 1194 "p4parser.y"
                                       {}
#line 5341 "p4parser.tab.c"
    break;

  case 431:
#line 1195 "p4parser.y"
                                       {}
#line 5347 "p4parser.tab.c"
    break;

  case 432:
#line 1196 "p4parser.y"
                                             {}
#line 5353 "p4parser.tab.c"
    break;

  case 433:
#line 1197 "p4parser.y"
                                             {}
#line 5359 "p4parser.tab.c"
    break;

  case 434:
#line 1198 "p4parser.y"
                                            {}
#line 5365 "p4parser.tab.c"
    break;

  case 435:
#line 1199 "p4parser.y"
                                       {}
#line 5371 "p4parser.tab.c"
    break;

  case 436:
#line 1200 "p4parser.y"
                                        {}
#line 5377 "p4parser.tab.c"
    break;

  case 437:
#line 1201 "p4parser.y"
                                       {}
#line 5383 "p4parser.tab.c"
    break;

  case 438:
#line 1202 "p4parser.y"
                                                      {}
#line 5389 "p4parser.tab.c"
    break;

  case 439:
#line 1203 "p4parser.y"
                         {}
#line 5395 "p4parser.tab.c"
    break;

  case 441:
#line 1207 "p4parser.y"
        {}
#line 5401 "p4parser.tab.c"
    break;

  case 442:
#line 1209 "p4parser.y"
        {}
#line 5407 "p4parser.tab.c"
    break;

  case 443:
#line 1211 "p4parser.y"
        {}
#line 5413 "p4parser.tab.c"
    break;

  case 444:
#line 1212 "p4parser.y"
                                                      {}
#line 5419 "p4parser.tab.c"
    break;

  case 445:
#line 1216 "p4parser.y"
                                       {}
#line 5425 "p4parser.tab.c"
    break;

  case 446:
#line 1217 "p4parser.y"
                                         {}
#line 5431 "p4parser.tab.c"
    break;

  case 447:
#line 1218 "p4parser.y"
                                         {}
#line 5437 "p4parser.tab.c"
    break;

  case 448:
#line 1219 "p4parser.y"
                                         {}
#line 5443 "p4parser.tab.c"
    break;

  case 449:
#line 1220 "p4parser.y"
                                         {}
#line 5449 "p4parser.tab.c"
    break;

  case 450:
#line 1221 "p4parser.y"
                                         {}
#line 5455 "p4parser.tab.c"
    break;

  case 451:
#line 1222 "p4parser.y"
                                         {}
#line 5461 "p4parser.tab.c"
    break;

  case 452:
#line 1223 "p4parser.y"
                                                             {}
#line 5467 "p4parser.tab.c"
    break;

  case 453:
#line 1224 "p4parser.y"
                                                                         {}
#line 5473 "p4parser.tab.c"
    break;

  case 454:
#line 1225 "p4parser.y"
                                                 {}
#line 5479 "p4parser.tab.c"
    break;

  case 455:
#line 1226 "p4parser.y"
                                         {}
#line 5485 "p4parser.tab.c"
    break;

  case 456:
#line 1227 "p4parser.y"
                                                {}
#line 5491 "p4parser.tab.c"
    break;

  case 457:
#line 1228 "p4parser.y"
                                           {}
#line 5497 "p4parser.tab.c"
    break;

  case 458:
#line 1229 "p4parser.y"
                                          {}
#line 5503 "p4parser.tab.c"
    break;

  case 459:
#line 1231 "p4parser.y"
        {}
#line 5509 "p4parser.tab.c"
    break;

  case 460:
#line 1233 "p4parser.y"
        {}
#line 5515 "p4parser.tab.c"
    break;

  case 461:
#line 1234 "p4parser.y"
                                                 {}
#line 5521 "p4parser.tab.c"
    break;

  case 462:
#line 1235 "p4parser.y"
                                                 {}
#line 5527 "p4parser.tab.c"
    break;

  case 463:
#line 1236 "p4parser.y"
                                                 {}
#line 5533 "p4parser.tab.c"
    break;

  case 464:
#line 1237 "p4parser.y"
                                                 {}
#line 5539 "p4parser.tab.c"
    break;

  case 465:
#line 1238 "p4parser.y"
                                                  {}
#line 5545 "p4parser.tab.c"
    break;

  case 466:
#line 1239 "p4parser.y"
                                                   {}
#line 5551 "p4parser.tab.c"
    break;

  case 467:
#line 1240 "p4parser.y"
                                                    {}
#line 5557 "p4parser.tab.c"
    break;

  case 468:
#line 1241 "p4parser.y"
                                                     {}
#line 5563 "p4parser.tab.c"
    break;

  case 469:
#line 1242 "p4parser.y"
                                                {}
#line 5569 "p4parser.tab.c"
    break;

  case 470:
#line 1244 "p4parser.y"
        {}
#line 5575 "p4parser.tab.c"
    break;

  case 471:
#line 1245 "p4parser.y"
                                               {}
#line 5581 "p4parser.tab.c"
    break;

  case 472:
#line 1246 "p4parser.y"
                                               {}
#line 5587 "p4parser.tab.c"
    break;

  case 473:
#line 1248 "p4parser.y"
                                         {}
#line 5593 "p4parser.tab.c"
    break;

  case 474:
#line 1249 "p4parser.y"
                                                     {}
#line 5599 "p4parser.tab.c"
    break;

  case 475:
#line 1250 "p4parser.y"
                                               {}
#line 5605 "p4parser.tab.c"
    break;

  case 476:
#line 1251 "p4parser.y"
                                               {}
#line 5611 "p4parser.tab.c"
    break;

  case 477:
#line 1252 "p4parser.y"
                                                     {}
#line 5617 "p4parser.tab.c"
    break;

  case 478:
#line 1253 "p4parser.y"
                                                     {}
#line 5623 "p4parser.tab.c"
    break;

  case 479:
#line 1254 "p4parser.y"
                                                    {}
#line 5629 "p4parser.tab.c"
    break;

  case 480:
#line 1255 "p4parser.y"
                                               {}
#line 5635 "p4parser.tab.c"
    break;

  case 481:
#line 1256 "p4parser.y"
                                                {}
#line 5641 "p4parser.tab.c"
    break;

  case 482:
#line 1257 "p4parser.y"
                                               {}
#line 5647 "p4parser.tab.c"
    break;

  case 483:
#line 1258 "p4parser.y"
                                                              {}
#line 5653 "p4parser.tab.c"
    break;


#line 5657 "p4parser.tab.c"

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
#line 1295 "p4parser.y"


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
