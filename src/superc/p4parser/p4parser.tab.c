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
#define YYLAST   4068

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  154
/* YYNRULES -- Number of rules.  */
#define YYNRULES  491
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  895

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
     680,   681,   686,   685,   691,   692,   693,   693,   698,   704,
     705,   706,   707,   708,   712,   713,   717,   718,   722,   726,
     730,   731,   735,   739,   740,   741,   742,   743,   744,   746,
     748,   751,   753,   755,   760,   761,   762,   767,   768,   772,
     776,   783,   789,   790,   792,   793,   797,   798,   799,   803,
     804,   805,   811,   812,   816,   817,   818,   819,   820,   824,
     825,   826,   827,   831,   831,   831,   840,   849,   849,   849,
     857,   858,   862,   867,   866,   872,   872,   880,   881,   885,
     889,   894,   900,   901,   905,   909,   913,   917,   927,   929,
     934,   936,   941,   945,   949,   950,   954,   956,   962,   966,
     967,   968,   969,   970,   971,   972,   973,   977,   977,   982,
     983,   987,   991,   992,   996,   997,  1001,  1002,  1006,  1007,
    1008,  1009,  1015,  1021,  1022,  1026,  1028,  1030,  1032,  1037,
    1038,  1042,  1047,  1048,  1053,  1057,  1059,  1064,  1069,  1070,
    1076,  1085,  1089,  1096,  1101,  1102,  1106,  1112,  1116,  1117,
    1121,  1122,  1126,  1127,  1128,  1132,  1133,  1134,  1138,  1139,
    1143,  1143,  1147,  1148,  1149,  1150,  1154,  1155,  1158,  1159,
    1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,
    1170,  1171,  1172,  1173,  1174,  1176,  1178,  1179,  1180,  1181,
    1182,  1183,  1184,  1185,  1186,  1187,  1189,  1190,  1191,  1193,
    1195,  1196,  1197,  1198,  1199,  1200,  1201,  1202,  1203,  1204,
    1206,  1207,  1209,  1211,  1213,  1217,  1218,  1219,  1220,  1221,
    1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,
    1233,  1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,
    1244,  1246,  1247,  1248,  1250,  1251,  1252,  1253,  1254,  1255,
    1256,  1257,  1258,  1259,  1260,  1262,  1264,  1266,  1289,  1289,
    1290,  1290
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

#define YYPACT_NINF (-771)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-386)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -771,    24,  -771,   687,  -771,  -771,  -771,   841,  -771,    78,
      15,    78,    27,   841,  -771,    78,    78,  -771,  -771,  -771,
    -771,  1051,  1381,  -771,   -27,  -771,    -3,  -771,    62,  -771,
      98,  -771,  -771,   -30,    32,  -771,   211,  -771,  -771,   124,
    -771,   841,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
     111,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,   129,  -771,  -771,   -25,   841,   -24,   841,
    -771,  2543,   -23,   841,   328,   841,  2586,   816,   841,   841,
    1381,   841,   841,   841,  1381,  -771,  -771,   132,  -771,  -771,
     -17,  -771,  -771,  -771,   145,   170,   -30,  -771,  1958,  2405,
    2543,  2405,    78,  -771,  2007,  -771,  2405,   191,  -771,    -1,
    2405,   191,    85,  1693,  -771,  -771,  -771,  -771,  -771,   248,
    2405,   191,   142,   841,  -771,   152,  -771,   841,   116,   118,
     168,   171,  -771,  -771,  -771,    71,   841,   841,  -771,  -771,
      78,   841,   841,  1958,   195,   182,   205,  -771,   228,  -771,
    -771,  2405,  2405,  2405,  1012,  1591,  2405,  -771,  -771,  -771,
    -771,   186,  -771,  -771,   217,   246,   900,   258,   175,  -771,
     261,   264,  -771,  3705,  -771,  -771,  2891,   248,  2928,  -771,
    -771,   841,   276,    -4,  -771,     3,  3705,  1785,  2965,  -771,
    -771,  -771,  -771,   841,  3002,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  2543,  -771,  3039,  -771,
     -17,   277,    78,   287,  -771,    78,  -771,  -771,    78,    78,
    -771,  -771,    78,    78,   292,  -771,  -771,   286,  -771,  -771,
    -771,   328,  -771,   -30,  -771,  1133,  -771,   315,   315,   315,
      96,   114,   186,   293,   148,   229,  3076,   315,   841,  2405,
    -771,  1958,  -771,  -771,   841,  2209,  2405,  2405,  2405,  2405,
    2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,
    2405,  2405,  2405,  2405,  2405,   298,  1958,  2405,  2405,  -771,
    1183,  -771,  -771,  -771,   290,  -771,   365,  2405,  -771,   841,
    -771,  2405,  -771,   191,  -771,   191,  1877,  -771,   191,   299,
    2405,  -771,   841,   307,  -771,  -771,  -771,  -771,  -771,  -771,
     841,   841,  -771,  1381,   -30,   -38,  1381,  -771,  -771,   198,
    -771,  -771,  -771,  -771,  1259,  -771,  -771,  2405,  -771,  -771,
    3705,   301,   841,   212,  -771,  3913,  3913,  1264,  3849,  3816,
    3882,  3882,   274,   274,   274,   274,   315,   315,   315,  3944,
    4006,  3975,  2780,  3913,  2405,   302,  3113,   274,  -771,  -771,
    -771,  -771,   369,  3913,   -17,   841,  -771,  3705,  -771,  3705,
    -771,  -771,  -771,  -771,   -30,   296,  3705,   305,   119,   841,
     319,   325,   330,   322,   329,    -5,   226,   318,    20,  -771,
    -771,    40,  -771,  -771,  -771,  -771,   340,  -771,   841,   279,
     332,  -771,  -771,  -771,   334,   346,  2258,   351,  -771,     4,
    -771,   900,   364,  -771,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,   188,   315,  -771,
    -771,   361,  -771,  -771,  2405,  1264,  -771,  2405,  2543,   358,
     371,  -771,  -771,  -771,   -17,  -771,   367,   173,  -771,  -771,
    -771,  -771,   -17,   -17,  -771,   328,  -771,   361,  -771,  2405,
     841,    78,   331,   380,  -771,  -771,   383,   332,  2405,   372,
    -771,  2405,  -771,  3150,  2405,  -771,   359,  2405,  1958,  2405,
    -771,  -771,  2543,  -771,   377,  3187,  3779,  -771,  1958,  -771,
     387,  2405,  -771,   841,    49,    56,    57,   389,   390,   841,
     384,  3705,  -771,   328,  -771,    41,   386,  -771,  -771,  3224,
    -771,  3261,   395,  2817,   400,  3298,   248,  1466,  -771,  -771,
     405,  -771,  -771,  -771,  -771,   376,  -771,  -771,  -771,  -771,
    -771,  -771,   388,  -771,   413,   191,   191,   191,   402,   403,
     391,    52,  -771,  -771,   582,   418,  1958,  -771,  2405,   408,
    -771,   417,  -771,  1381,  -771,  -771,  -771,  -771,  2614,   423,
     419,  -771,  -771,  -771,   425,   426,   428,   436,   442,  -771,
     155,  -771,  -771,   378,   411,  -771,   437,  3335,  -771,  1958,
     431,   -17,  -771,  2452,  2405,  2405,  2405,  -771,  -771,  -771,
     433,  -771,  -771,  -771,  -771,   434,   582,  2307,   438,  -771,
     441,  -771,   444,   491,     8,  1381,  -771,  -771,   453,   841,
    -771,  -771,  -771,  -771,  -771,  -771,  3372,  3409,  3446,    60,
    2356,   455,  2405,  -771,  2405,  2405,  2405,  -771,  1591,  2405,
    -771,  -771,  -771,  -771,   445,  -771,  -771,  -771,   900,   454,
     175,  -771,   449,  3742,  -771,   450,   458,   460,   459,  -771,
    -771,  -771,   841,  -771,   841,   841,   841,  -771,   289,  -771,
    -771,  -771,  3483,  2058,   461,   315,   315,   315,   462,  3520,
     315,   841,  -771,  1958,  -771,   -16,  2405,  2405,  2405,  2405,
    2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,  2405,
    2405,  2405,  2405,  2405,  2405,   463,  1958,  2405,  2405,  -771,
    1183,  -771,  -771,  2107,  -771,  -771,   470,   477,   479,   185,
     480,   468,   841,  1338,  -771,  -771,   467,  -771,  -771,  -771,
     961,  2740,  -771,  2405,  -771,  -771,   488,  -771,  3913,  3913,
    1264,  3849,  3816,  3882,  3882,   274,   274,   274,   274,   315,
     315,   315,  3944,  4006,  3975,  2854,  3913,  2405,   493,  3557,
     274,   369,  3913,   -13,  2500,  -771,  -771,  -771,  -771,  1958,
     -30,   492,   494,   500,   498,  2700,   289,  -771,  -771,  2405,
    2405,   315,  -771,  -771,  2405,  1264,  -771,  2405,   495,   511,
    -771,   505,   504,  -771,  2158,  2405,  2405,   -30,  3705,  3705,
    3594,  3779,  1958,  -771,  -771,  -771,    92,  -771,  3631,  3668,
     507,  -771,   512,  1433,  -771,  2158,  -771,  -771,  -771,  -771,
     514,  -771,   841,   513,  -771
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   158,     6,     0,   253,   255,
     254,   257,     0,     0,   256,     0,     0,   265,   266,   246,
       5,     0,    34,    35,     0,    13,     0,    10,   156,    12,
     156,     8,   227,    33,   264,   248,   240,   243,   242,   241,
     239,     0,    11,   284,   289,   291,   290,   292,    14,    15,
       0,     9,     7,    16,    20,    18,    22,    19,    23,    21,
      17,    25,    24,    37,   488,   489,     0,     0,     0,     0,
      42,   276,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,    33,   254,    36,     0,   288,   247,
      33,   286,   159,   287,     0,     0,    34,   377,   440,   440,
     276,   440,   267,   285,   440,    42,   440,     0,   312,     0,
     440,     0,     0,     0,   275,   274,   273,   272,   277,     0,
     440,     0,     0,     0,   213,   246,   303,     0,   266,   224,
       0,     0,   264,   293,   297,     0,     0,     0,   144,   168,
     267,     0,     0,   440,   143,     0,   135,   136,     0,   216,
     337,   440,   440,   440,   440,   440,   440,   384,   400,   401,
     402,     0,   399,   398,   403,     0,     0,     0,   244,   245,
       0,   379,   380,   382,   439,   403,     0,     0,     0,   232,
     268,     0,     0,     0,   131,     0,   386,     0,     0,   490,
     491,   258,   310,     0,     0,   259,   311,    45,    41,   104,
     103,    99,   100,   102,   101,   106,   108,   107,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    95,   122,    96,    42,   123,   124,   130,   125,   126,
     127,   128,   129,   105,    90,    98,    97,    84,    61,    82,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    62,    63,    64,    65,    66,
      67,    68,    76,    69,    70,    71,    73,    72,    74,    75,
      77,    78,    79,    80,    81,    83,    85,    86,    87,    88,
      89,    91,    92,    93,    94,    44,     0,   249,     0,   260,
      33,     0,   267,     0,   305,   267,   228,   229,   267,   267,
     316,   317,   267,   267,     0,   314,   315,     0,   140,   142,
     141,     0,   157,    33,   162,    33,   339,   413,   412,   411,
       0,     0,   254,     0,   240,   241,     0,   410,     0,   440,
     404,   440,   390,   414,     0,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,     0,   440,   440,   440,   416,
     440,   250,   252,   251,     0,   270,     0,   440,    40,     0,
      39,   440,    38,     0,   313,     0,     0,   278,     0,     0,
     440,   214,     0,     0,   225,   294,   298,   145,   169,   300,
       0,     0,   137,    33,    33,     0,    34,   221,   217,     0,
     220,   219,   222,   218,    33,   408,   407,   440,   409,   415,
     383,     0,     0,     0,   381,   426,   427,   424,   436,   437,
     430,   431,   420,   421,   422,   423,   417,   418,   419,   434,
     432,   433,     0,   429,   440,     0,     0,   435,   281,   280,
     279,   282,     0,   428,    33,     0,   269,   133,   132,   387,
     261,   262,    43,   263,    33,     0,   376,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,   138,     0,   165,
     163,    33,   171,   167,   166,   164,     0,   223,     0,     0,
     374,   338,   322,   393,     0,     0,   440,     0,   388,     0,
     351,     0,   240,   329,   318,   332,   335,   334,   331,   330,
     350,   333,   336,   340,   348,   349,   392,     0,   444,   443,
     391,     0,   148,   405,   440,   425,   442,   440,     0,     0,
       0,   271,   370,   373,    33,   304,     0,     0,   307,   230,
     300,   300,    33,    33,   296,     0,   301,     0,   147,   440,
       0,     0,     0,     0,   172,   212,     0,   374,   440,     0,
     323,   440,   324,     0,   440,   389,     0,   440,   440,   440,
     394,   395,   276,   152,     0,     0,   438,   283,   440,   233,
       0,   440,   306,     0,    33,    33,    33,     0,     0,     0,
       0,   139,   173,     0,   161,    33,     0,   375,   372,     0,
     325,     0,     0,     0,     0,     0,     0,     0,   150,   406,
       0,   215,   309,   308,   226,     0,   231,   236,   295,   299,
     146,   170,     0,   149,     0,     0,     0,     0,     0,     0,
      31,    33,   353,   371,    33,     0,   440,   396,   440,     0,
     319,     0,   151,     0,   155,   153,   154,   441,     0,   246,
       0,   237,   302,   175,     0,     0,     0,     0,     0,    32,
       0,   352,   354,     0,   326,   342,     0,     0,   320,   440,
       0,    33,   234,    33,   440,   440,   440,   362,   359,    28,
       0,    30,    29,    26,    27,     0,    33,     0,     0,   397,
       0,   235,     0,     0,     0,    34,   176,   182,     0,     0,
     177,   179,   183,   178,   180,   181,     0,     0,     0,    33,
     440,     0,   440,   327,   440,   440,   440,   341,   440,   440,
     447,   448,   449,   346,     0,   446,   445,   450,     0,     0,
     244,   343,     0,   347,   328,     0,     0,     0,     0,   187,
     189,   184,     0,   174,     0,     0,     0,   356,     0,   363,
     355,   360,     0,   440,     0,   458,   457,   456,     0,     0,
     455,     0,   451,   440,   459,   345,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,     0,   440,   440,   440,   461,
     440,   321,   238,   440,   188,   175,     0,     0,     0,     0,
       0,   365,     0,   440,   208,   207,     0,   194,   195,   368,
     440,   204,   358,   440,   454,   460,     0,   344,   471,   472,
     469,   481,   482,   475,   476,   465,   466,   467,   468,   462,
     463,   464,   479,   477,   478,     0,   474,   440,     0,     0,
     480,     0,   473,     0,    33,   211,   210,   209,   364,   440,
      33,   203,   202,     0,     0,   204,     0,   357,   369,   440,
     440,   487,   486,   452,   440,   470,   485,   440,     0,     0,
     185,     0,     0,   197,   440,   440,   440,    33,   205,   206,
       0,   483,   440,   191,   366,   361,     0,   198,   200,   201,
       0,   453,     0,   440,   196,   440,   367,   484,   190,   192,
       0,   199,     0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -771,  -771,  -771,  -771,  -771,    -7,   126,  -771,  -771,     2,
       0,   -11,   -84,  -771,   360,   136,  -281,  -771,   262,  -771,
    -771,  -771,  -771,  -295,    37,  -771,  -771,   550,   216,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,   115,  -771,
    -197,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -771,  -294,
    -771,  -771,  -771,  -770,  -771,  -771,  -771,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,   -70,  -771,  -771,
    -771,  -771,   103,   -86,  -771,   452,     9,  -771,   557,    10,
    -771,   -77,  -771,  -771,  -273,   -92,  -771,  -186,  -771,   133,
    -771,  -771,  -771,  -771,  -771,  -771,  -771,  -201,  -771,  -771,
    -771,  -771,  -771,    22,  -771,  -771,   -57,  -771,  -649,  -771,
    -646,  -771,  -771,  -645,  -644,  -599,   -31,  -771,  -771,  -771,
    -771,  -771,  -771,  -771,  -771,  -771,   -22,  -771,  -771,  -771,
    -771,  -250,  -202,  -771,   285,  -293,     7,    59,  -533,     6,
    -117,  -771,   273,  -153,  -722,  -164,  -771,  -771,  -771,   829,
    -771,  -771,    42,   -72
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    20,   175,   165,   675,   650,   144,
      96,    23,   113,   285,   183,   184,   145,   146,   147,   311,
      24,   302,   463,    25,   564,   597,   635,    92,   166,    27,
     148,   543,   393,   470,    28,   303,   464,   471,   472,   614,
     663,   686,   687,   785,   688,   729,   730,   883,   889,   796,
     797,   876,   843,   798,   473,    29,    30,   292,   457,   315,
     398,   476,    31,   295,   460,    32,   574,    33,   364,   606,
     641,   607,   117,   167,    35,   168,    37,    38,   169,    40,
      41,   179,   180,   366,   118,   119,   441,   442,    42,    43,
      44,   298,   461,    45,    46,   299,   462,   465,   536,    47,
     293,   383,   527,   528,    48,    49,   109,    50,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   316,   404,   502,
     677,   721,   722,   503,   400,   621,   622,   700,   741,   699,
     739,   790,   799,   800,    51,   694,   695,   549,   455,    53,
     170,   171,   172,   185,   506,   359,   412,   507,   561,   173,
     174,   723,   360,   191
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   321,    97,    22,   333,    21,    62,   131,   177,   379,
      52,    86,   112,   377,   690,   587,   791,   691,   692,   693,
     397,   187,   402,   844,     4,   654,   307,   106,   110,   120,
     -33,     7,    73,    88,    62,    95,  -134,    74,   602,   195,
     859,   368,   534,   371,     7,     7,   192,   287,   370,   289,
     150,    66,   369,    68,   731,   193,     7,    71,    72,   371,
      62,    67,    62,   304,   116,   478,    62,    13,    62,    62,
     129,    62,    62,    69,    62,    62,    62,   703,   100,    74,
      13,    13,   135,    74,    98,    86,   135,  -160,   107,   111,
     121,   164,    13,   116,   877,    74,   604,   164,   469,   651,
     474,     7,     7,   608,   609,   362,    34,   737,    89,   490,
       7,   504,   618,     7,    90,   891,    62,     7,     7,   540,
      62,     7,    91,   618,   791,    87,    64,    65,   541,    62,
      62,   619,   196,    63,    62,    62,   164,    13,    13,    70,
     376,   193,   619,   405,   181,   884,    13,   164,   885,    13,
      90,    76,   369,    13,    13,    78,    79,    13,    93,   330,
     333,   406,   -17,   520,   -17,   -17,   525,   102,   101,   744,
     371,   103,    83,   104,    62,   193,   -17,   123,   -24,   127,
     132,   105,   181,   136,   143,   690,    62,   141,   691,   692,
     693,   149,    99,   108,   290,   108,    64,    65,   -25,   122,
    -244,   124,   126,   130,   133,   134,   332,   138,   139,   140,
     100,   -25,   -25,   137,   411,   381,   150,   142,   384,    26,
     572,   385,   386,    64,    65,   387,   388,   669,   296,   573,
     182,   297,   557,   332,   670,   312,    64,    65,    26,   435,
     558,   189,   190,   570,   328,   567,   332,   559,   671,   291,
      98,   577,   578,   294,   672,    99,    54,    55,   323,    64,
      65,   313,   300,   301,    56,   673,   674,   305,   306,    54,
      55,   511,   512,   101,   314,    57,   -24,    56,    58,   116,
     182,  -245,   308,   309,    59,   537,   538,    26,    57,   310,
      26,    58,    26,    26,   446,    60,    26,    59,   189,   190,
      26,   450,   634,   451,   286,   329,   453,   365,    60,    61,
     331,   347,   348,   349,   334,   396,    26,   395,   353,   374,
     335,    62,   403,    65,   164,   458,   356,    62,   164,   575,
     576,   143,   332,   382,   181,   367,   380,   181,   389,   390,
     181,   181,   444,   560,   181,   181,   407,     5,   434,   164,
      54,    55,   454,   459,   509,   516,   523,   524,    56,   353,
      54,    55,    62,   477,    65,   529,   100,   356,    56,    57,
     519,   530,    58,   332,   532,    62,   531,   539,    59,    57,
     682,   533,    58,    62,    62,    86,     5,   545,    59,    60,
      61,   548,    62,   396,   550,   468,    95,   488,   551,    60,
     475,     8,     9,   554,   396,    62,   489,   563,    99,    85,
     568,   505,    64,    65,   391,   189,   190,    11,   399,   189,
     190,   445,   556,   522,   569,   518,   571,   584,    14,   585,
     540,   592,   588,    15,     5,    16,   556,   598,    62,    19,
     601,   594,   610,   611,   613,   638,   623,   626,   642,     8,
       9,   600,    62,   629,   409,    36,    95,    85,   637,   643,
     413,   647,   648,   440,   655,    11,   649,   535,   658,   659,
     596,    62,    62,   542,    36,   661,    14,   664,   665,   662,
     666,    15,   667,    16,   555,    17,    18,   639,   668,   676,
     678,   681,   701,   702,   725,   182,   399,   726,   724,   479,
     733,   743,    26,   751,   755,   448,   753,   399,   108,   656,
     781,   116,   783,   827,   320,   803,   466,   467,   782,   784,
     839,   802,   846,    36,   631,   480,    36,    26,    36,    36,
     835,    26,    36,    62,   100,   640,    36,   836,   510,   837,
     838,   852,   680,   644,   645,   646,   856,   872,  -208,   562,
    -207,   164,    36,   863,   864,   116,   754,   873,   874,   779,
      39,   164,    54,    55,   875,   887,    62,   886,   660,   892,
      56,   521,    62,   894,   580,   392,   605,   535,   535,    39,
      94,    57,   727,   583,    58,   526,   544,   620,   834,   890,
      59,   719,   616,   617,   831,   603,   867,   633,   848,   652,
     401,    60,    61,   636,   546,   547,   586,   324,   414,    26,
       0,     0,    26,     0,     0,     0,     0,   488,     0,   164,
     491,     0,    86,   620,     0,     0,    95,     0,    39,     0,
     833,    39,     0,    39,    39,     0,   806,    39,   579,     0,
       5,    39,   482,     7,     0,     0,     0,     0,     0,     0,
     483,     0,   164,    54,    55,     0,   488,    39,     0,   828,
       0,    56,     0,   685,   484,   684,   582,     0,   485,   488,
     717,     0,    57,     0,    86,    58,    62,     0,    95,    13,
     486,    59,    62,     0,   487,     0,     0,    -3,     0,     0,
       0,     0,    60,    19,     0,     0,     0,     0,     0,   526,
      34,   738,     0,     0,     0,   612,     0,     0,   132,     0,
       0,   752,   325,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   861,     0,   807,    62,     0,    62,    62,    62,
       0,   488,     0,     0,    26,     0,    87,     0,    36,     0,
       0,   132,     0,     0,    62,     5,   164,     6,     7,     0,
       0,    26,     0,     0,     0,   882,     0,    95,     0,   858,
       8,     9,   100,    36,     0,   780,   689,    36,    10,   164,
       0,     0,     0,     0,     0,     0,    11,     0,    26,    12,
       0,     0,   555,     0,    13,    62,     0,    14,   732,     0,
       0,     0,    15,     0,    16,     0,    17,    18,    19,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   728,
       0,   748,   324,    26,     0,   480,     0,     0,     0,     0,
       0,    26,     0,     0,     0,     0,     0,   488,     0,     0,
       0,     0,   164,     0,   685,     0,   684,     0,     0,   488,
     491,     0,   862,    39,     0,    36,     0,     0,    36,    26,
       0,     0,     0,     0,    26,     0,   492,     0,   547,     0,
     786,   787,   788,     0,     0,   164,     0,     0,    39,   880,
       0,     0,    39,     0,     5,     0,     0,   805,     0,   491,
       0,     0,     0,   440,     0,    62,     0,    54,    55,     8,
       9,     0,   491,   718,     0,    56,   323,    85,     0,     0,
       0,    26,     0,     0,     0,    11,    57,     0,     0,    58,
       0,     0,    54,    55,     0,    59,    14,   325,   840,     0,
      56,    15,     0,    16,     0,    17,   128,   125,   176,     0,
     178,    57,     0,   186,    58,   188,     0,   689,     0,   194,
      59,     0,     0,     0,     0,     0,     0,     0,     0,   288,
      39,    60,    61,    39,   789,     0,     0,     0,     0,     0,
       0,    39,     0,     0,     0,     0,     0,     0,     0,     0,
      36,    54,    55,     0,     0,     0,     0,     0,     0,    56,
     317,   318,   319,   186,   326,   327,     0,    36,     0,     0,
      57,     0,     0,    58,   151,   152,     0,     0,     0,    59,
       0,     0,     0,     0,   153,     0,     0,   154,   847,     0,
      60,    89,     0,   793,    36,   156,     0,     0,   893,     5,
       0,     0,     0,     0,   794,     0,     0,   158,   159,   160,
       0,     0,    54,    55,     0,   615,     0,     0,   795,     0,
      56,     0,   161,     0,     0,   151,   152,     0,     0,    36,
     491,    57,     0,     0,    58,   153,     0,    36,   154,  -385,
      59,     0,   789,     0,   155,     0,   156,     0,  -385,     0,
       5,    60,    19,   162,   163,    39,   653,     0,   158,   159,
     160,     0,     0,    54,    55,    36,     0,     0,     0,     0,
      36,    56,    39,   161,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,     0,    58,     0,     0,     0,     0,
       0,    59,     0,     0,     0,   492,     0,     0,     0,    39,
       0,    73,    60,   125,   162,   163,    74,    75,   653,   720,
       0,    76,     0,     0,    77,    78,    79,    36,     0,     0,
       0,     0,     0,     0,    80,     0,    81,    82,     0,     0,
       0,     0,    83,     0,    39,     0,     0,    84,   410,     0,
     324,     0,    39,     0,     0,   415,   416,   417,   418,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,     0,     0,   436,   437,     0,   443,
      39,     5,     0,     0,     7,    39,   447,     0,     0,     0,
     449,     0,     0,     0,     0,   394,     8,     9,     0,   456,
       0,     0,     0,     0,    85,     0,   151,   152,     0,     0,
      39,     0,    11,     0,     0,     0,   153,     0,     0,   154,
      13,     0,   324,    14,     0,   155,   508,   156,    15,     0,
      16,     5,    39,     0,    19,   324,   438,     0,     0,   158,
     159,   160,     0,     0,    54,    55,     8,     9,     0,     0,
       0,     0,    56,   515,   322,   325,     0,     0,     0,     0,
       0,     0,    11,    57,     0,     0,    58,     0,     0,     0,
       0,     0,    59,    14,     0,     0,   492,     0,    15,     0,
      16,     0,   439,    60,    19,   162,   163,   343,   344,   345,
     346,   347,   348,   349,     0,     0,   481,     0,   353,     0,
       0,     0,     0,    65,     0,   553,   356,     5,     0,   482,
       7,     0,   332,     0,     0,     0,   358,   483,     0,     0,
      54,    55,     8,     9,     0,     0,     0,   325,    56,     0,
      85,   484,     0,   565,     0,   485,   566,     0,    11,    57,
     325,     0,    58,     0,     0,     0,    13,   486,    59,    14,
       0,   487,     0,     0,    15,     0,    16,     0,   581,    60,
      19,   151,   152,     0,     0,     0,     0,   456,     0,     0,
     589,   153,     0,   591,   154,     0,   593,     0,   595,     0,
     155,    39,   156,     0,     0,     0,     5,     0,     0,     0,
     456,   841,     0,     0,   158,   159,   160,     0,     0,    54,
      55,     8,     9,     0,     0,   842,     0,    56,     0,   322,
       0,     0,     0,     0,     0,     0,     0,    11,    57,     0,
       0,    58,     0,     0,     0,     0,     0,    59,    14,     5,
       0,     0,     7,    15,     0,    16,     0,     0,    60,    19,
     162,   163,     0,     0,     8,     9,     0,   657,     0,     0,
       0,     0,    85,     0,     0,     0,   151,   152,     0,     0,
      11,     0,     0,     0,     0,     0,   153,     0,    13,   154,
     888,    14,     0,     0,     0,   793,    15,   156,    16,     0,
       0,     5,    19,   696,   697,   698,   794,     0,     0,   158,
     159,   160,     0,     0,    54,    55,     0,     0,     0,     0,
     795,     0,    56,   632,   161,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     5,     0,    58,     7,     0,   742,
       0,   456,    59,   745,   746,   747,     0,   749,   750,     8,
       9,     0,     0,    60,    19,   162,   163,    85,     0,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,     0,
       0,     0,     0,    13,     0,     0,    14,     0,     0,     0,
       0,    15,   801,    16,     0,    17,    18,    19,     0,     0,
       0,     0,     0,     0,     0,   808,   809,   810,   811,   812,
     813,   814,   815,   816,   817,   818,   819,   820,   821,   822,
     823,   824,   825,   826,     0,     0,   829,   830,     0,   832,
       0,     0,   186,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   845,     0,   151,   152,     0,     0,     0,   801,
       0,     0,   851,     0,   153,     0,     0,   154,     0,     0,
       0,     0,     0,   155,     0,   156,     0,     0,     0,     5,
       0,     0,     0,     0,     0,     0,   855,   158,   159,   160,
       0,     0,    54,    55,     8,     9,     0,     0,     0,     0,
      56,     0,   322,     0,     0,     0,     0,     0,   868,   869,
      11,    57,     0,   870,    58,     0,   871,     0,     0,     0,
      59,    14,     0,   801,   878,   879,    15,     0,    16,     0,
       0,    60,    19,   162,   163,     0,     0,     0,     0,     0,
       0,     0,   801,     0,   801,   197,   198,     0,     0,   199,
     200,     0,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,     0,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   197,     0,     0,
       0,   199,   200,     0,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   372,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   197,
       0,     0,     0,   199,   200,     0,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     452,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,   153,     0,     0,   154,     0,     0,     0,     0,     0,
     155,  -378,   156,     0,     0,     0,     5,     0,     0,     0,
       0,   157,     0,     0,   158,   159,   160,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,    56,     0,   161,
     151,   152,     0,     0,     0,     0,     0,     0,    57,     0,
     153,    58,  -385,   154,     0,     0,     0,    59,     0,   155,
       0,   156,     0,  -385,     0,     5,     0,     0,    60,   125,
     162,   163,     0,   158,   159,   160,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,    56,     0,   161,     0,
       0,   151,   152,     0,     0,     0,     0,    57,     0,     0,
      58,   153,     0,     0,   154,     0,    59,     0,     0,     0,
     793,     0,   156,     0,     0,     0,     5,    60,   125,   162,
     163,   794,     0,     0,   158,   159,   160,     0,     0,    54,
      55,     0,     0,     0,     0,   795,     0,    56,     0,   161,
     151,   152,     0,     0,     0,     0,     0,     0,    57,     0,
     153,    58,     0,   154,     0,     0,     0,    59,     0,   155,
    -385,   156,     0,  -385,     0,     5,     0,     0,    60,    19,
     162,   163,     0,   158,   159,   160,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,    56,     0,   161,     0,
       0,   151,   152,     0,     0,     0,     0,    57,     0,     0,
      58,   153,     0,     0,   154,     0,    59,     0,     0,     0,
     155,     0,   156,     0,     0,     0,     5,    60,    19,   162,
     163,   794,     0,     0,   158,   159,   160,     0,     0,    54,
      55,     0,     0,     0,     0,   795,     0,    56,     0,   161,
       0,     0,   151,   152,     0,     0,     0,     0,    57,     0,
       0,    58,   153,     0,     0,   154,     0,    59,     0,     0,
       0,   155,     0,   156,     0,     0,     0,     5,    60,    19,
     162,   163,   157,     0,     0,   158,   159,   160,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,    56,     0,
     161,   151,   152,     0,     0,     0,     0,     0,     0,    57,
       0,   153,    58,     0,   154,     0,     0,     0,    59,     0,
     155,     0,   156,     0,     0,     0,     5,     0,   552,    60,
     125,   162,   163,     0,   158,   159,   160,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,    56,     0,   161,
     704,   705,     0,     0,     0,     0,     0,     0,    57,     0,
     706,    58,     0,     0,   707,     0,     0,    59,     0,   708,
       0,   709,     0,     0,     0,     5,     0,     0,    60,    19,
     162,   163,     0,   710,   711,   712,     0,     0,    54,    55,
       0,     0,     0,     0,   713,     0,    56,     0,   714,   151,
     152,     0,     0,     0,     0,     0,     0,    57,     0,   153,
      58,     0,   154,   740,     0,     0,    59,     0,   155,     0,
     156,     0,     0,     0,     5,     0,     0,    60,    19,   715,
     716,     0,   158,   159,   160,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,    56,     0,   161,   151,   152,
       0,     0,     0,     0,     0,     0,    57,     0,   153,    58,
       0,   154,     0,     0,     0,    59,     0,   155,     0,   156,
       0,     0,     0,     5,     0,     0,    60,    19,   162,   163,
       0,   158,   159,   160,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,    56,     0,   161,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,     0,    58,  -186,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       5,     0,   482,     7,     0,    60,    19,   162,   163,     0,
     483,     0,     0,    54,    55,     8,     9,     0,     0,     0,
       0,    56,     0,    85,     0,     0,     0,     0,   485,     0,
       0,    11,    57,     0,     0,    58,     0,   860,     0,    13,
       0,    59,    14,     0,     0,     0,   683,    15,     5,    16,
     482,     7,    60,    19,     0,     0,     0,     0,   483,     0,
       0,    54,    55,     8,     9,     0,     0,     0,     0,    56,
       0,    85,     0,     0,     0,     0,   485,     0,     0,    11,
      57,     0,     0,    58,     0,     0,     0,    13,     0,    59,
      14,     5,     0,     0,     0,    15,   114,    16,     0,     0,
      60,    19,     0,     0,    54,    55,     8,     9,     0,     0,
       0,     0,    56,     0,    85,     0,     0,     0,     0,     0,
       0,     0,    11,    57,     0,     0,    58,     0,     0,     0,
       0,     0,    59,    14,     5,     0,     0,     0,    15,     0,
      16,     0,   115,    60,    19,     0,     0,    54,    55,     8,
       9,     0,     0,     0,     0,    56,     0,    85,     0,     0,
       0,     0,     5,     0,     0,    11,    57,     0,     0,    58,
       0,     0,     0,     0,     0,    59,    14,     8,     9,     0,
       0,    15,     0,    16,     0,    85,    60,   125,     0,     0,
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,     0,     0,     0,    15,
       0,    16,     0,    17,    18,    19,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,   408,     0,     0,     0,   357,   332,     0,
       0,     0,   358,     0,   865,   866,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,     0,     0,     0,     0,   357,   332,     0,
       0,     0,   358,     0,   849,   850,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,   513,     0,     0,    64,    65,
     354,   355,   356,     0,     0,   514,     0,   357,   332,     0,
       0,     0,   358,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,   627,     0,     0,    64,    65,   354,   355,   356,
       0,     0,   628,     0,   357,   332,     0,     0,     0,   358,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,   853,
       0,     0,    64,    65,   354,   355,   356,     0,     0,   854,
       0,   357,   332,     0,     0,     0,   358,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,   361,     0,     0,    64,
      65,   354,   355,   356,     0,     0,     0,     0,   357,   332,
       0,     0,     0,   358,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,   363,     0,     0,    64,    65,   354,   355,
     356,     0,     0,     0,     0,   357,   332,     0,     0,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
       0,     0,     0,    64,    65,   354,   355,   356,   373,     0,
       0,     0,   357,   332,     0,     0,     0,   358,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,     0,     0,     0,
      64,    65,   354,   355,   356,   375,     0,     0,     0,   357,
     332,     0,     0,     0,   358,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,   378,     0,     0,     0,   357,   332,     0,     0,
       0,   358,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,     0,     0,     0,    64,    65,   354,   355,   356,   408,
       0,     0,     0,   357,   332,     0,     0,     0,   358,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,     0,     0,
       0,    64,    65,   354,   355,   356,     0,     0,   517,     0,
     357,   332,     0,     0,     0,   358,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,     0,     0,     0,     0,   357,   332,     0,
     590,     0,   358,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,   599,     0,     0,    64,    65,   354,   355,   356,
       0,     0,     0,     0,   357,   332,     0,     0,     0,   358,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,     0,
       0,     0,    64,    65,   354,   355,   356,   624,     0,     0,
       0,   357,   332,     0,     0,     0,   358,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,     0,     0,     0,    64,
      65,   354,   355,   356,   625,     0,     0,     0,   357,   332,
       0,     0,     0,   358,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,     0,     0,     0,     0,   357,   332,     0,   630,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
     679,     0,     0,    64,    65,   354,   355,   356,     0,     0,
       0,     0,   357,   332,     0,     0,     0,   358,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,     0,     0,     0,
      64,    65,   354,   355,   356,   734,     0,     0,     0,   357,
     332,     0,     0,     0,   358,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,   735,     0,     0,     0,   357,   332,     0,     0,
       0,   358,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,     0,     0,     0,    64,    65,   354,   355,   356,   736,
       0,     0,     0,   357,   332,     0,     0,     0,   358,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,     0,     0,
       0,    64,    65,   354,   355,   356,     0,     0,   792,     0,
     357,   332,     0,     0,     0,   358,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,   804,     0,     0,     0,   357,   332,     0,
       0,     0,   358,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,     0,     0,     0,    64,    65,   354,   355,   356,
       0,     0,   857,     0,   357,   332,     0,     0,     0,   358,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,   881,
       0,     0,    64,    65,   354,   355,   356,     0,     0,     0,
       0,   357,   332,     0,     0,     0,   358,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,     0,     0,     0,    64,
      65,   354,   355,   356,     0,     0,     0,  -205,   357,   332,
       0,     0,     0,   358,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,     0,     0,     0,  -206,   357,   332,     0,     0,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
       0,     0,     0,    64,    65,   354,   355,   356,     0,     0,
       0,     0,   357,   332,     0,     0,     0,   358,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   766,   767,
     768,   769,   770,   771,   772,     0,   773,     0,     0,     0,
      64,    65,   774,   775,   776,     0,     0,     0,     0,   777,
     332,     0,     0,     0,   778,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,     0,     0,     0,     0,     0,   332,     0,     0,
       0,   358,   336,   337,   338,   339,     0,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,     0,     0,     0,    64,    65,   354,   355,   356,     0,
       0,     0,     0,     0,   332,   336,   337,   338,   358,     0,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,     0,     0,     0,     0,     0,   332,   336,   337,
     338,   358,     0,     0,     0,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,     0,     0,     0,
      64,    65,   354,   355,   356,     0,     0,     0,     0,     0,
     332,   338,     0,     0,   358,     0,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,     0,     0,
       0,     0,    65,     0,   355,   356,     0,     0,     0,     0,
       0,   332,   338,     0,     0,   358,     0,   343,   344,   345,
     346,   347,   348,   349,     0,   351,   352,     0,   353,     0,
       0,     0,     0,    65,     0,   355,   356,     0,     0,     0,
       0,     0,   332,   338,     0,     0,   358,     0,   343,   344,
     345,   346,   347,   348,   349,     0,   351,     0,     0,   353,
       0,     0,     0,     0,    65,     0,   355,   356,     0,     0,
       0,     0,     0,   332,   338,     0,     0,   358,     0,   343,
     344,   345,   346,   347,   348,   349,     0,     0,     0,     0,
     353,     0,     0,     0,     0,    65,     0,   355,   356,     0,
       0,     0,     0,     0,   332,     0,     0,     0,   358
};

static const yytype_int16 yycheck[] =
{
       7,   154,    33,     3,   168,     3,    13,    77,   100,   290,
       3,    22,    69,   286,   663,   548,   738,   663,   663,   663,
     315,   105,   315,   793,     0,   624,   143,    52,    52,    52,
      46,    61,    70,    60,    41,    33,    53,    75,   571,   111,
      53,    45,    47,    56,    61,    61,    47,   119,    45,   121,
      46,     9,    56,    11,    46,    56,    61,    15,    16,    56,
      67,    46,    69,   140,    71,   103,    73,    97,    75,    76,
      77,    78,    79,    46,    81,    82,    83,   676,    36,    75,
      97,    97,    80,    75,    52,    96,    84,    47,   113,   113,
     113,    98,    97,   100,   864,    75,    47,   104,   393,    47,
     393,    61,    61,    47,    47,   177,     3,    47,   111,   404,
      61,   404,    71,    61,    52,   885,   123,    61,    61,    99,
     127,    61,    60,    71,   846,    22,    48,    49,   108,   136,
     137,    90,    47,     7,   141,   142,   143,    97,    97,    13,
     224,    56,    90,    47,   102,    53,    97,   154,    56,    97,
      52,    80,    56,    97,    97,    84,    85,    97,    60,   166,
     324,    47,    46,   444,    48,    49,    47,    41,    44,   702,
      56,    60,   101,    44,   181,    56,    60,    74,    60,    76,
      77,    52,   140,    80,    52,   834,   193,    84,   834,   834,
     834,    46,    44,    67,    52,    69,    48,    49,    46,    73,
      52,    75,    76,    77,    78,    79,    58,    81,    82,    83,
     168,    59,    60,    80,   331,   292,    46,    84,   295,     3,
      47,   298,   299,    48,    49,   302,   303,    72,    60,    56,
     104,    60,    44,    58,    79,    53,    48,    49,    22,   356,
      52,    50,    51,   524,    58,   518,    58,    59,    93,   123,
      52,   532,   533,   127,    99,    44,    71,    72,   155,    48,
      49,    56,   136,   137,    79,   110,   111,   141,   142,    71,
      72,    59,    60,    44,    46,    90,    59,    79,    93,   286,
     154,    52,    87,    88,    99,    59,    60,    71,    90,    94,
      74,    93,    76,    77,   366,   110,    80,    99,    50,    51,
      84,   373,   597,   375,    56,    59,   378,   181,   110,   111,
      52,    37,    38,    39,    53,   315,   100,   315,    44,   193,
      56,   328,   315,    49,   331,   382,    52,   334,   335,   530,
     531,    52,    58,    46,   292,    59,    59,   295,    46,    53,
     298,   299,    52,   507,   302,   303,    53,    58,    50,   356,
      71,    72,    53,    46,    53,    53,    60,    52,    79,    44,
      71,    72,   369,   394,    49,    46,   324,    52,    79,    90,
     442,    46,    93,    58,    52,   382,    46,    59,    99,    90,
     661,    52,    93,   390,   391,   396,    58,    47,    99,   110,
     111,    59,   399,   393,    60,   393,   394,   404,    52,   110,
     393,    73,    74,    52,   404,   412,   404,    46,    44,    81,
      52,   404,    48,    49,   311,    50,    51,    89,   315,    50,
      51,    56,    58,   454,    53,    56,    59,    47,   100,    46,
      99,    72,    60,   105,    58,   107,    58,    60,   445,   111,
      53,   558,    53,    53,    60,    69,    60,    52,    60,    73,
      74,   568,   459,    53,   328,     3,   454,    81,    53,    46,
     334,    59,    59,   360,    46,    89,    75,   465,    60,    52,
     562,   478,   479,   471,    22,    52,   100,    52,    52,    60,
      52,   105,    46,   107,   491,   109,   110,   111,    46,    78,
      53,    60,    59,    59,    53,   369,   393,    53,    60,   396,
      47,    46,   286,    58,    55,   369,    52,   404,   382,   626,
      60,   518,    52,    50,   154,    53,   390,   391,    60,    60,
      52,    60,    55,    71,   596,   399,    74,   311,    76,    77,
      60,   315,    80,   540,   492,   605,    84,    60,   412,    60,
      60,    53,   659,   615,   616,   617,    53,    52,    56,   507,
      56,   558,   100,    53,    56,   562,   720,    46,    53,   723,
       3,   568,    71,    72,    60,    53,   573,    60,   638,    55,
      79,   445,   579,    60,   537,   313,   574,   575,   576,    22,
      30,    90,    91,   541,    93,   459,   471,   585,   785,   883,
      99,   677,   583,   583,   780,   573,   846,   597,   800,   621,
     315,   110,   111,   597,   478,   479,   547,   155,   335,   393,
      -1,    -1,   396,    -1,    -1,    -1,    -1,   624,    -1,   626,
     404,    -1,   633,   621,    -1,    -1,   624,    -1,    71,    -1,
     783,    74,    -1,    76,    77,    -1,   753,    80,   535,    -1,
      58,    84,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,   659,    71,    72,    -1,   663,   100,    -1,   776,
      -1,    79,    -1,   663,    82,   663,   540,    -1,    86,   676,
     677,    -1,    90,    -1,   685,    93,   683,    -1,   676,    97,
      98,    99,   689,    -1,   102,    -1,    -1,     0,    -1,    -1,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,   573,
     597,   699,    -1,    -1,    -1,   579,    -1,    -1,   605,    -1,
      -1,   718,   155,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   839,    -1,   755,   732,    -1,   734,   735,   736,
      -1,   738,    -1,    -1,   518,    -1,   633,    -1,   286,    -1,
      -1,   638,    -1,    -1,   751,    58,   753,    60,    61,    -1,
      -1,   535,    -1,    -1,    -1,   872,    -1,   755,    -1,   831,
      73,    74,   720,   311,    -1,   723,   663,   315,    81,   776,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,   562,    92,
      -1,    -1,   789,    -1,    97,   792,    -1,   100,   685,    -1,
      -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,   583,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   683,
      -1,   708,   360,   597,    -1,   689,    -1,    -1,    -1,    -1,
      -1,   605,    -1,    -1,    -1,    -1,    -1,   834,    -1,    -1,
      -1,    -1,   839,    -1,   834,    -1,   834,    -1,    -1,   846,
     624,    -1,   840,   286,    -1,   393,    -1,    -1,   396,   633,
      -1,    -1,    -1,    -1,   638,    -1,   404,    -1,   732,    -1,
     734,   735,   736,    -1,    -1,   872,    -1,    -1,   311,   867,
      -1,    -1,   315,    -1,    58,    -1,    -1,   751,    -1,   663,
      -1,    -1,    -1,   780,    -1,   892,    -1,    71,    72,    73,
      74,    -1,   676,   677,    -1,    79,   793,    81,    -1,    -1,
      -1,   685,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    71,    72,    -1,    99,   100,   360,   792,    -1,
      79,   105,    -1,   107,    -1,   109,   110,   111,    99,    -1,
     101,    90,    -1,   104,    93,   106,    -1,   834,    -1,   110,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     393,   110,   111,   396,   738,    -1,    -1,    -1,    -1,    -1,
      -1,   404,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     518,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
     151,   152,   153,   154,   155,   156,    -1,   535,    -1,    -1,
      90,    -1,    -1,    93,    33,    34,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,    -1,
     110,   111,    -1,    52,   562,    54,    -1,    -1,   892,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,   583,    -1,    -1,    77,    -1,
      79,    -1,    81,    -1,    -1,    33,    34,    -1,    -1,   597,
     834,    90,    -1,    -1,    93,    43,    -1,   605,    46,    47,
      99,    -1,   846,    -1,    52,    -1,    54,    -1,    56,    -1,
      58,   110,   111,   112,   113,   518,   624,    -1,    66,    67,
      68,    -1,    -1,    71,    72,   633,    -1,    -1,    -1,    -1,
     638,    79,   535,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,    -1,    -1,    -1,   663,    -1,    -1,    -1,   562,
      -1,    70,   110,   111,   112,   113,    75,    76,   676,   677,
      -1,    80,    -1,    -1,    83,    84,    85,   685,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    95,    96,    -1,    -1,
      -1,    -1,   101,    -1,   597,    -1,    -1,   106,   329,    -1,
     708,    -1,   605,    -1,    -1,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,    -1,    -1,   357,   358,    -1,   360,
     633,    58,    -1,    -1,    61,   638,   367,    -1,    -1,    -1,
     371,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,   380,
      -1,    -1,    -1,    -1,    81,    -1,    33,    34,    -1,    -1,
     663,    -1,    89,    -1,    -1,    -1,    43,    -1,    -1,    46,
      97,    -1,   780,   100,    -1,    52,   407,    54,   105,    -1,
     107,    58,   685,    -1,   111,   793,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,   434,    81,   708,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,    -1,   834,    -1,   105,    -1,
     107,    -1,   109,   110,   111,   112,   113,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    47,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,   486,    52,    58,    -1,    60,
      61,    -1,    58,    -1,    -1,    -1,    62,    68,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,   780,    79,    -1,
      81,    82,    -1,   514,    -1,    86,   517,    -1,    89,    90,
     793,    -1,    93,    -1,    -1,    -1,    97,    98,    99,   100,
      -1,   102,    -1,    -1,   105,    -1,   107,    -1,   539,   110,
     111,    33,    34,    -1,    -1,    -1,    -1,   548,    -1,    -1,
     551,    43,    -1,   554,    46,    -1,   557,    -1,   559,    -1,
      52,   834,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
     571,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    77,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,    58,
      -1,    -1,    61,   105,    -1,   107,    -1,    -1,   110,   111,
     112,   113,    -1,    -1,    73,    74,    -1,   628,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    33,    34,    -1,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    43,    -1,    97,    46,
      47,   100,    -1,    -1,    -1,    52,   105,    54,   107,    -1,
      -1,    58,   111,   664,   665,   666,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      77,    -1,    79,    47,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    58,    -1,    93,    61,    -1,   700,
      -1,   702,    99,   704,   705,   706,    -1,   708,   709,    73,
      74,    -1,    -1,   110,   111,   112,   113,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    -1,    -1,   100,    -1,    -1,    -1,
      -1,   105,   743,   107,    -1,   109,   110,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   756,   757,   758,   759,   760,
     761,   762,   763,   764,   765,   766,   767,   768,   769,   770,
     771,   772,   773,   774,    -1,    -1,   777,   778,    -1,   780,
      -1,    -1,   783,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   793,    -1,    33,    34,    -1,    -1,    -1,   800,
      -1,    -1,   803,    -1,    43,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    -1,    -1,   827,    66,    67,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,   849,   850,
      89,    90,    -1,   854,    93,    -1,   857,    -1,    -1,    -1,
      99,   100,    -1,   864,   865,   866,   105,    -1,   107,    -1,
      -1,   110,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   883,    -1,   885,    22,    23,    -1,    -1,    26,
      27,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    -1,    54,    55,    56,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,    22,
      -1,    -1,    -1,    26,    27,    -1,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    45,    46,    -1,    -1,    -1,    99,    -1,    52,
      -1,    54,    -1,    56,    -1,    58,    -1,    -1,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      93,    43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,
     113,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,
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
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    43,    93,    -1,    46,    -1,    -1,    -1,    99,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,    -1,    60,   110,
     111,   112,   113,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    -1,    47,    -1,    -1,    99,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    46,    47,    -1,    -1,    99,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    46,    -1,    -1,    -1,    99,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    47,
      -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    60,    61,    -1,   110,   111,   112,   113,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    47,    -1,    97,
      -1,    99,   100,    -1,    -1,    -1,   104,   105,    58,   107,
      60,    61,   110,   111,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    -1,    -1,    97,    -1,    99,
     100,    58,    -1,    -1,    -1,   105,    63,   107,    -1,    -1,
     110,   111,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,   100,    58,    -1,    -1,    -1,   105,    -1,
     107,    -1,   109,   110,   111,    -1,    -1,    71,    72,    73,
      74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    73,    74,    -1,
      -1,   105,    -1,   107,    -1,    81,   110,   111,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,    -1,   105,
      -1,   107,    -1,   109,   110,   111,    26,    27,    28,    29,
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
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
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
      -1,    -1,    -1,    58,    28,    -1,    -1,    62,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,    97,   100,   105,   107,   109,   110,   111,
     122,   127,   128,   129,   138,   141,   146,   147,   152,   173,
     174,   180,   183,   185,   190,   192,   193,   194,   195,   196,
     197,   198,   206,   207,   208,   211,   212,   217,   222,   223,
     225,   252,   254,   257,    71,    72,    79,    90,    93,    99,
     110,   111,   123,   124,    48,    49,   270,    46,   270,    46,
     124,   270,   270,    70,    75,    76,    80,    83,    84,    85,
      93,    95,    96,   101,   106,    81,   129,   190,    60,   111,
      52,    60,   145,    60,   145,   127,   128,   234,    52,    44,
     270,    44,   124,    60,    44,    52,    52,   113,   124,   224,
      52,   113,   224,   130,    63,   109,   123,   190,   202,   203,
      52,   113,   124,   190,   124,   111,   124,   190,   110,   123,
     124,   185,   190,   124,   124,   127,   190,   207,   124,   124,
     124,   190,   207,    52,   127,   134,   135,   136,   148,    46,
      46,    33,    34,    43,    46,    52,    54,    63,    66,    67,
      68,    81,   112,   113,   123,   124,   146,   191,   193,   196,
     258,   259,   260,   267,   268,   123,   267,   203,   267,   199,
     200,   270,   124,   132,   133,   261,   267,   130,   267,    50,
      51,   271,    47,    56,   267,   271,    47,    22,    23,    26,
      27,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   131,    56,   271,   267,   271,
      52,   124,   175,   218,   124,   181,    60,    60,   209,   213,
     124,   124,   139,   153,   199,   124,   124,   258,    87,    88,
      94,   137,    53,    56,    46,   177,   235,   267,   267,   267,
     132,   261,    81,   190,   193,   196,   267,   267,    58,    59,
     123,    52,    58,   263,    53,    56,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    50,    51,    52,    57,    62,   263,
     270,    45,   271,    45,   186,   124,   201,    59,    45,    56,
      45,    56,    53,    53,   124,    53,   130,   202,    53,   134,
      59,   199,    46,   219,   199,   199,   199,   199,   199,    46,
      53,   190,   136,   150,    72,   127,   128,   141,   178,   190,
     242,   252,   253,   254,   236,    47,    47,    53,    53,   124,
     267,   258,   264,   124,   260,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,    50,   258,   267,   267,    63,   109,
     190,   204,   205,   267,    52,    56,   271,   267,   133,   267,
     271,   271,    53,   271,    53,   256,   267,   176,   224,    46,
     182,   210,   214,   140,   154,   215,   124,   124,   127,   141,
     151,   155,   156,   172,   253,   254,   179,   234,   103,   190,
     124,    47,    60,    68,    82,    86,    98,   102,   123,   127,
     141,   146,   193,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   237,   241,   253,   254,   262,   265,   267,    53,
     124,    59,    60,    45,    55,   267,    53,    55,    56,   271,
     134,   124,   234,    60,    52,    47,   124,   220,   221,    46,
      46,    46,    52,    52,    47,   127,   216,    59,    60,    59,
      99,   108,   127,   149,   156,    47,   124,   124,    59,   255,
      60,    52,    60,   267,    52,   123,    58,    44,    52,    59,
     263,   266,   270,    46,   142,   267,   267,   202,    52,    53,
     134,    59,    47,    56,   184,   215,   215,   134,   134,   190,
     142,   267,   124,   270,    47,    46,   255,   256,    60,   267,
      60,   267,    72,   267,   258,   267,   203,   143,    60,    45,
     258,    53,   256,   221,    47,   127,   187,   189,    47,    47,
      53,    53,   124,    60,   157,   193,   194,   197,    71,    90,
     127,   243,   244,    60,    53,    53,    52,    45,    55,    53,
      60,   271,    47,   128,   141,   144,   257,    53,    69,   111,
     185,   188,    60,    46,   271,   271,   271,    59,    59,    75,
     126,    47,   244,   193,   233,    46,   258,   267,    60,    52,
     185,    52,    60,   158,    52,    52,    52,    46,    46,    72,
      79,    93,    99,   110,   111,   125,    78,   238,    53,    45,
     258,    60,   134,   104,   127,   128,   159,   160,   162,   190,
     226,   228,   231,   232,   253,   254,   267,   267,   267,   247,
     245,    59,    59,   233,    33,    34,    43,    47,    52,    54,
      66,    67,    68,    77,    81,   112,   113,   123,   146,   191,
     193,   239,   240,   269,    60,    53,    53,    91,   124,   163,
     164,    46,   190,    47,    53,    53,    53,    47,   127,   248,
      47,   246,   267,    46,   256,   267,   267,   267,   190,   267,
     267,    58,   123,    52,   263,    55,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    50,    51,    52,    57,    62,   263,
     270,    60,    60,    52,    60,   161,   124,   124,   124,   146,
     249,   262,    55,    52,    63,    77,   167,   168,   171,   250,
     251,   267,    60,    53,    53,   124,   258,   234,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,    50,   258,   267,
     267,   205,   267,   261,   158,    60,    60,    60,    60,    52,
     124,    63,    77,   170,   171,   267,    55,    47,   250,    64,
      65,   267,    53,    45,    55,   267,    53,    55,   271,    53,
      47,   258,   127,    53,    56,    64,    65,   249,   267,   267,
     267,   267,    52,    46,    53,    60,   169,   171,   267,   267,
     127,    45,   258,   165,    53,    56,    60,    53,    47,   166,
     167,   171,    55,   124,    60
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
     184,   184,   186,   185,   187,   187,   188,   187,   189,   190,
     190,   190,   190,   190,   191,   191,   192,   192,   193,   194,
     195,   195,   196,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   198,   198,   198,   199,   199,   200,
     201,   201,   202,   202,   202,   202,   203,   203,   203,   204,
     204,   204,   205,   205,   206,   206,   206,   206,   206,   207,
     207,   207,   207,   209,   210,   208,   211,   213,   214,   212,
     215,   215,   216,   218,   217,   219,   217,   220,   220,   221,
     222,   223,   224,   224,   225,   225,   225,   225,   226,   226,
     227,   227,   228,   229,   230,   230,   231,   231,   232,   233,
     233,   233,   233,   233,   233,   233,   233,   235,   234,   236,
     236,   237,   238,   238,   239,   239,   240,   240,   241,   241,
     241,   241,   242,   243,   243,   244,   244,   244,   244,   245,
     245,   246,   247,   247,   248,   249,   249,   250,   251,   251,
     252,   253,   253,   254,   255,   255,   256,   257,   258,   258,
     259,   259,   260,   260,   260,   261,   261,   261,   262,   262,
     264,   263,   265,   265,   265,   265,   266,   266,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     268,   268,   268,   268,   268,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   270,   270,
     271,   271
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
       3,     3,     3,     5,     7,     4,     4,     4,     1,     1,
       1,     1
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
#line 2817 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2823 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2829 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2835 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2841 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2847 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2853 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2859 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2865 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2871 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2877 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2883 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2889 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2895 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2901 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2907 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2913 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2919 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2925 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2931 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2937 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2943 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2949 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2955 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2961 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2967 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2973 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2979 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2985 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2991 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2997 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 3003 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 3009 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3015 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3021 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3027 "p4parser.tab.c"
    break;

  case 40:
#line 312 "p4parser.y"
        {}
#line 3033 "p4parser.tab.c"
    break;

  case 41:
#line 316 "p4parser.y"
        {}
#line 3039 "p4parser.tab.c"
    break;

  case 42:
#line 320 "p4parser.y"
              {}
#line 3045 "p4parser.tab.c"
    break;

  case 43:
#line 322 "p4parser.y"
        {}
#line 3051 "p4parser.tab.c"
    break;

  case 44:
#line 324 "p4parser.y"
        {}
#line 3057 "p4parser.tab.c"
    break;

  case 45:
#line 328 "p4parser.y"
                       {}
#line 3063 "p4parser.tab.c"
    break;

  case 46:
#line 329 "p4parser.y"
                       {}
#line 3069 "p4parser.tab.c"
    break;

  case 47:
#line 330 "p4parser.y"
                       {}
#line 3075 "p4parser.tab.c"
    break;

  case 48:
#line 331 "p4parser.y"
                       {}
#line 3081 "p4parser.tab.c"
    break;

  case 49:
#line 332 "p4parser.y"
                       {}
#line 3087 "p4parser.tab.c"
    break;

  case 50:
#line 333 "p4parser.y"
                       {}
#line 3093 "p4parser.tab.c"
    break;

  case 51:
#line 334 "p4parser.y"
                       {}
#line 3099 "p4parser.tab.c"
    break;

  case 52:
#line 335 "p4parser.y"
                       {}
#line 3105 "p4parser.tab.c"
    break;

  case 53:
#line 336 "p4parser.y"
                       {}
#line 3111 "p4parser.tab.c"
    break;

  case 54:
#line 337 "p4parser.y"
                       {}
#line 3117 "p4parser.tab.c"
    break;

  case 55:
#line 338 "p4parser.y"
                       {}
#line 3123 "p4parser.tab.c"
    break;

  case 56:
#line 339 "p4parser.y"
                       {}
#line 3129 "p4parser.tab.c"
    break;

  case 57:
#line 340 "p4parser.y"
                       {}
#line 3135 "p4parser.tab.c"
    break;

  case 58:
#line 341 "p4parser.y"
                       {}
#line 3141 "p4parser.tab.c"
    break;

  case 59:
#line 342 "p4parser.y"
                       {}
#line 3147 "p4parser.tab.c"
    break;

  case 60:
#line 343 "p4parser.y"
                       {}
#line 3153 "p4parser.tab.c"
    break;

  case 61:
#line 344 "p4parser.y"
                       {}
#line 3159 "p4parser.tab.c"
    break;

  case 62:
#line 345 "p4parser.y"
                       {}
#line 3165 "p4parser.tab.c"
    break;

  case 63:
#line 346 "p4parser.y"
                       {}
#line 3171 "p4parser.tab.c"
    break;

  case 64:
#line 347 "p4parser.y"
                       {}
#line 3177 "p4parser.tab.c"
    break;

  case 65:
#line 348 "p4parser.y"
                       {}
#line 3183 "p4parser.tab.c"
    break;

  case 66:
#line 349 "p4parser.y"
                       {}
#line 3189 "p4parser.tab.c"
    break;

  case 67:
#line 350 "p4parser.y"
                       {}
#line 3195 "p4parser.tab.c"
    break;

  case 68:
#line 351 "p4parser.y"
                       {}
#line 3201 "p4parser.tab.c"
    break;

  case 69:
#line 352 "p4parser.y"
                       {}
#line 3207 "p4parser.tab.c"
    break;

  case 70:
#line 353 "p4parser.y"
                       {}
#line 3213 "p4parser.tab.c"
    break;

  case 71:
#line 354 "p4parser.y"
                       {}
#line 3219 "p4parser.tab.c"
    break;

  case 72:
#line 355 "p4parser.y"
                       {}
#line 3225 "p4parser.tab.c"
    break;

  case 73:
#line 356 "p4parser.y"
                       {}
#line 3231 "p4parser.tab.c"
    break;

  case 74:
#line 357 "p4parser.y"
                       {}
#line 3237 "p4parser.tab.c"
    break;

  case 75:
#line 358 "p4parser.y"
                       {}
#line 3243 "p4parser.tab.c"
    break;

  case 76:
#line 359 "p4parser.y"
                       {}
#line 3249 "p4parser.tab.c"
    break;

  case 77:
#line 360 "p4parser.y"
                       {}
#line 3255 "p4parser.tab.c"
    break;

  case 78:
#line 361 "p4parser.y"
                       {}
#line 3261 "p4parser.tab.c"
    break;

  case 79:
#line 362 "p4parser.y"
                       {}
#line 3267 "p4parser.tab.c"
    break;

  case 80:
#line 363 "p4parser.y"
                       {}
#line 3273 "p4parser.tab.c"
    break;

  case 81:
#line 364 "p4parser.y"
                       {}
#line 3279 "p4parser.tab.c"
    break;

  case 82:
#line 365 "p4parser.y"
                       {}
#line 3285 "p4parser.tab.c"
    break;

  case 83:
#line 366 "p4parser.y"
                       {}
#line 3291 "p4parser.tab.c"
    break;

  case 84:
#line 367 "p4parser.y"
                       {}
#line 3297 "p4parser.tab.c"
    break;

  case 85:
#line 368 "p4parser.y"
                       {}
#line 3303 "p4parser.tab.c"
    break;

  case 86:
#line 369 "p4parser.y"
                       {}
#line 3309 "p4parser.tab.c"
    break;

  case 87:
#line 370 "p4parser.y"
                       {}
#line 3315 "p4parser.tab.c"
    break;

  case 88:
#line 371 "p4parser.y"
                       {}
#line 3321 "p4parser.tab.c"
    break;

  case 89:
#line 372 "p4parser.y"
                       {}
#line 3327 "p4parser.tab.c"
    break;

  case 90:
#line 373 "p4parser.y"
                            {}
#line 3333 "p4parser.tab.c"
    break;

  case 91:
#line 375 "p4parser.y"
                       {}
#line 3339 "p4parser.tab.c"
    break;

  case 92:
#line 376 "p4parser.y"
                       {}
#line 3345 "p4parser.tab.c"
    break;

  case 93:
#line 377 "p4parser.y"
                       {}
#line 3351 "p4parser.tab.c"
    break;

  case 94:
#line 378 "p4parser.y"
                       {}
#line 3357 "p4parser.tab.c"
    break;

  case 95:
#line 379 "p4parser.y"
                       {}
#line 3363 "p4parser.tab.c"
    break;

  case 96:
#line 380 "p4parser.y"
                       {}
#line 3369 "p4parser.tab.c"
    break;

  case 97:
#line 381 "p4parser.y"
                       {}
#line 3375 "p4parser.tab.c"
    break;

  case 98:
#line 382 "p4parser.y"
                       {}
#line 3381 "p4parser.tab.c"
    break;

  case 99:
#line 383 "p4parser.y"
                       {}
#line 3387 "p4parser.tab.c"
    break;

  case 100:
#line 384 "p4parser.y"
                       {}
#line 3393 "p4parser.tab.c"
    break;

  case 101:
#line 385 "p4parser.y"
                       {}
#line 3399 "p4parser.tab.c"
    break;

  case 102:
#line 386 "p4parser.y"
                       {}
#line 3405 "p4parser.tab.c"
    break;

  case 103:
#line 387 "p4parser.y"
                       {}
#line 3411 "p4parser.tab.c"
    break;

  case 104:
#line 388 "p4parser.y"
                       {}
#line 3417 "p4parser.tab.c"
    break;

  case 105:
#line 389 "p4parser.y"
                       {}
#line 3423 "p4parser.tab.c"
    break;

  case 106:
#line 390 "p4parser.y"
                       {}
#line 3429 "p4parser.tab.c"
    break;

  case 108:
#line 392 "p4parser.y"
                       {}
#line 3435 "p4parser.tab.c"
    break;

  case 109:
#line 393 "p4parser.y"
                       {}
#line 3441 "p4parser.tab.c"
    break;

  case 110:
#line 394 "p4parser.y"
                       {}
#line 3447 "p4parser.tab.c"
    break;

  case 111:
#line 395 "p4parser.y"
                       {}
#line 3453 "p4parser.tab.c"
    break;

  case 112:
#line 396 "p4parser.y"
                       {}
#line 3459 "p4parser.tab.c"
    break;

  case 113:
#line 397 "p4parser.y"
                       {}
#line 3465 "p4parser.tab.c"
    break;

  case 114:
#line 398 "p4parser.y"
                       {}
#line 3471 "p4parser.tab.c"
    break;

  case 115:
#line 399 "p4parser.y"
                       {}
#line 3477 "p4parser.tab.c"
    break;

  case 116:
#line 400 "p4parser.y"
                       {}
#line 3483 "p4parser.tab.c"
    break;

  case 117:
#line 401 "p4parser.y"
                       {}
#line 3489 "p4parser.tab.c"
    break;

  case 118:
#line 402 "p4parser.y"
                       {}
#line 3495 "p4parser.tab.c"
    break;

  case 119:
#line 403 "p4parser.y"
                       {}
#line 3501 "p4parser.tab.c"
    break;

  case 120:
#line 404 "p4parser.y"
                       {}
#line 3507 "p4parser.tab.c"
    break;

  case 121:
#line 405 "p4parser.y"
                       {}
#line 3513 "p4parser.tab.c"
    break;

  case 122:
#line 406 "p4parser.y"
                       {}
#line 3519 "p4parser.tab.c"
    break;

  case 123:
#line 407 "p4parser.y"
                       {}
#line 3525 "p4parser.tab.c"
    break;

  case 124:
#line 408 "p4parser.y"
                       {}
#line 3531 "p4parser.tab.c"
    break;

  case 125:
#line 409 "p4parser.y"
                       {}
#line 3537 "p4parser.tab.c"
    break;

  case 126:
#line 410 "p4parser.y"
                       {}
#line 3543 "p4parser.tab.c"
    break;

  case 127:
#line 411 "p4parser.y"
                       {}
#line 3549 "p4parser.tab.c"
    break;

  case 128:
#line 412 "p4parser.y"
                       {}
#line 3555 "p4parser.tab.c"
    break;

  case 129:
#line 413 "p4parser.y"
                       {}
#line 3561 "p4parser.tab.c"
    break;

  case 130:
#line 414 "p4parser.y"
                       {}
#line 3567 "p4parser.tab.c"
    break;

  case 131:
#line 418 "p4parser.y"
                                      {}
#line 3573 "p4parser.tab.c"
    break;

  case 132:
#line 419 "p4parser.y"
                                        {}
#line 3579 "p4parser.tab.c"
    break;

  case 133:
#line 423 "p4parser.y"
                                         {}
#line 3585 "p4parser.tab.c"
    break;

  case 134:
#line 427 "p4parser.y"
                                      {}
#line 3591 "p4parser.tab.c"
    break;

  case 135:
#line 428 "p4parser.y"
                                      {}
#line 3597 "p4parser.tab.c"
    break;

  case 136:
#line 432 "p4parser.y"
                                          {}
#line 3603 "p4parser.tab.c"
    break;

  case 137:
#line 433 "p4parser.y"
                                            {}
#line 3609 "p4parser.tab.c"
    break;

  case 138:
#line 437 "p4parser.y"
                                            {}
#line 3615 "p4parser.tab.c"
    break;

  case 139:
#line 438 "p4parser.y"
                                                              {}
#line 3621 "p4parser.tab.c"
    break;

  case 140:
#line 442 "p4parser.y"
                 {}
#line 3627 "p4parser.tab.c"
    break;

  case 141:
#line 443 "p4parser.y"
                   {}
#line 3633 "p4parser.tab.c"
    break;

  case 142:
#line 444 "p4parser.y"
                   {}
#line 3639 "p4parser.tab.c"
    break;

  case 143:
#line 445 "p4parser.y"
                   {}
#line 3645 "p4parser.tab.c"
    break;

  case 144:
#line 449 "p4parser.y"
                                  {}
#line 3651 "p4parser.tab.c"
    break;

  case 145:
#line 450 "p4parser.y"
                        {}
#line 3657 "p4parser.tab.c"
    break;

  case 146:
#line 451 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3666 "p4parser.tab.c"
    break;

  case 147:
#line 459 "p4parser.y"
                     {}
#line 3672 "p4parser.tab.c"
    break;

  case 148:
#line 461 "p4parser.y"
                     {}
#line 3678 "p4parser.tab.c"
    break;

  case 149:
#line 464 "p4parser.y"
                     {}
#line 3684 "p4parser.tab.c"
    break;

  case 150:
#line 467 "p4parser.y"
                     {}
#line 3690 "p4parser.tab.c"
    break;

  case 151:
#line 473 "p4parser.y"
                               {}
#line 3696 "p4parser.tab.c"
    break;

  case 152:
#line 477 "p4parser.y"
                                     {}
#line 3702 "p4parser.tab.c"
    break;

  case 153:
#line 478 "p4parser.y"
                                     {}
#line 3708 "p4parser.tab.c"
    break;

  case 154:
#line 482 "p4parser.y"
                               {}
#line 3714 "p4parser.tab.c"
    break;

  case 155:
#line 483 "p4parser.y"
                               {}
#line 3720 "p4parser.tab.c"
    break;

  case 156:
#line 487 "p4parser.y"
                           {}
#line 3726 "p4parser.tab.c"
    break;

  case 157:
#line 488 "p4parser.y"
                                     {}
#line 3732 "p4parser.tab.c"
    break;

  case 158:
#line 492 "p4parser.y"
                             {}
#line 3738 "p4parser.tab.c"
    break;

  case 159:
#line 498 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3744 "p4parser.tab.c"
    break;

  case 160:
#line 499 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3750 "p4parser.tab.c"
    break;

  case 161:
#line 500 "p4parser.y"
                             {}
#line 3756 "p4parser.tab.c"
    break;

  case 162:
#line 505 "p4parser.y"
                                           {}
#line 3762 "p4parser.tab.c"
    break;

  case 163:
#line 506 "p4parser.y"
                                             {}
#line 3768 "p4parser.tab.c"
    break;

  case 164:
#line 510 "p4parser.y"
                                    {}
#line 3774 "p4parser.tab.c"
    break;

  case 165:
#line 511 "p4parser.y"
                                      {}
#line 3780 "p4parser.tab.c"
    break;

  case 166:
#line 512 "p4parser.y"
                                      {}
#line 3786 "p4parser.tab.c"
    break;

  case 167:
#line 513 "p4parser.y"
                                      {}
#line 3792 "p4parser.tab.c"
    break;

  case 168:
#line 518 "p4parser.y"
                          {}
#line 3798 "p4parser.tab.c"
    break;

  case 169:
#line 519 "p4parser.y"
                          {}
#line 3804 "p4parser.tab.c"
    break;

  case 170:
#line 520 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3813 "p4parser.tab.c"
    break;

  case 171:
#line 527 "p4parser.y"
                                    {}
#line 3819 "p4parser.tab.c"
    break;

  case 172:
#line 528 "p4parser.y"
                                      {}
#line 3825 "p4parser.tab.c"
    break;

  case 173:
#line 532 "p4parser.y"
                              {}
#line 3831 "p4parser.tab.c"
    break;

  case 174:
#line 534 "p4parser.y"
                                      {}
#line 3837 "p4parser.tab.c"
    break;

  case 175:
#line 538 "p4parser.y"
                                     {}
#line 3843 "p4parser.tab.c"
    break;

  case 176:
#line 539 "p4parser.y"
                                       {}
#line 3849 "p4parser.tab.c"
    break;

  case 177:
#line 543 "p4parser.y"
                                    {}
#line 3855 "p4parser.tab.c"
    break;

  case 178:
#line 544 "p4parser.y"
                                      {}
#line 3861 "p4parser.tab.c"
    break;

  case 179:
#line 545 "p4parser.y"
                                      {}
#line 3867 "p4parser.tab.c"
    break;

  case 180:
#line 546 "p4parser.y"
                                      {}
#line 3873 "p4parser.tab.c"
    break;

  case 181:
#line 547 "p4parser.y"
                                      {}
#line 3879 "p4parser.tab.c"
    break;

  case 182:
#line 548 "p4parser.y"
                                      {}
#line 3885 "p4parser.tab.c"
    break;

  case 183:
#line 549 "p4parser.y"
                                      {}
#line 3891 "p4parser.tab.c"
    break;

  case 184:
#line 553 "p4parser.y"
                           {}
#line 3897 "p4parser.tab.c"
    break;

  case 185:
#line 554 "p4parser.y"
                               {}
#line 3903 "p4parser.tab.c"
    break;

  case 186:
#line 558 "p4parser.y"
                                {}
#line 3909 "p4parser.tab.c"
    break;

  case 187:
#line 559 "p4parser.y"
                                  {}
#line 3915 "p4parser.tab.c"
    break;

  case 188:
#line 563 "p4parser.y"
                           {}
#line 3921 "p4parser.tab.c"
    break;

  case 189:
#line 564 "p4parser.y"
                       {}
#line 3927 "p4parser.tab.c"
    break;

  case 190:
#line 569 "p4parser.y"
                              {}
#line 3933 "p4parser.tab.c"
    break;

  case 191:
#line 573 "p4parser.y"
                               {}
#line 3939 "p4parser.tab.c"
    break;

  case 192:
#line 574 "p4parser.y"
                                 {}
#line 3945 "p4parser.tab.c"
    break;

  case 193:
#line 579 "p4parser.y"
      {}
#line 3951 "p4parser.tab.c"
    break;

  case 194:
#line 583 "p4parser.y"
                              {}
#line 3957 "p4parser.tab.c"
    break;

  case 195:
#line 584 "p4parser.y"
                                {}
#line 3963 "p4parser.tab.c"
    break;

  case 196:
#line 589 "p4parser.y"
                                {}
#line 3969 "p4parser.tab.c"
    break;

  case 197:
#line 590 "p4parser.y"
                                                    {}
#line 3975 "p4parser.tab.c"
    break;

  case 198:
#line 594 "p4parser.y"
                           {}
#line 3981 "p4parser.tab.c"
    break;

  case 199:
#line 595 "p4parser.y"
                                                        {}
#line 3987 "p4parser.tab.c"
    break;

  case 200:
#line 600 "p4parser.y"
                                 {}
#line 3993 "p4parser.tab.c"
    break;

  case 201:
#line 601 "p4parser.y"
                                   {}
#line 3999 "p4parser.tab.c"
    break;

  case 202:
#line 602 "p4parser.y"
                                  {}
#line 4005 "p4parser.tab.c"
    break;

  case 203:
#line 603 "p4parser.y"
                                       {}
#line 4011 "p4parser.tab.c"
    break;

  case 204:
#line 607 "p4parser.y"
                                {}
#line 4017 "p4parser.tab.c"
    break;

  case 205:
#line 608 "p4parser.y"
                                 {}
#line 4023 "p4parser.tab.c"
    break;

  case 206:
#line 609 "p4parser.y"
                                   {}
#line 4029 "p4parser.tab.c"
    break;

  case 207:
#line 610 "p4parser.y"
                                  {}
#line 4035 "p4parser.tab.c"
    break;

  case 208:
#line 611 "p4parser.y"
                                       {}
#line 4041 "p4parser.tab.c"
    break;

  case 209:
#line 617 "p4parser.y"
        {}
#line 4047 "p4parser.tab.c"
    break;

  case 210:
#line 620 "p4parser.y"
        {}
#line 4053 "p4parser.tab.c"
    break;

  case 211:
#line 623 "p4parser.y"
        {}
#line 4059 "p4parser.tab.c"
    break;

  case 212:
#line 631 "p4parser.y"
        {}
#line 4065 "p4parser.tab.c"
    break;

  case 213:
#line 636 "p4parser.y"
                     {}
#line 4071 "p4parser.tab.c"
    break;

  case 214:
#line 637 "p4parser.y"
                          {}
#line 4077 "p4parser.tab.c"
    break;

  case 215:
#line 638 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4086 "p4parser.tab.c"
    break;

  case 216:
#line 645 "p4parser.y"
           {}
#line 4092 "p4parser.tab.c"
    break;

  case 217:
#line 646 "p4parser.y"
                                                       {}
#line 4098 "p4parser.tab.c"
    break;

  case 218:
#line 650 "p4parser.y"
                             {}
#line 4104 "p4parser.tab.c"
    break;

  case 219:
#line 651 "p4parser.y"
                               {}
#line 4110 "p4parser.tab.c"
    break;

  case 220:
#line 652 "p4parser.y"
                               {}
#line 4116 "p4parser.tab.c"
    break;

  case 221:
#line 653 "p4parser.y"
                               {}
#line 4122 "p4parser.tab.c"
    break;

  case 222:
#line 654 "p4parser.y"
                               {}
#line 4128 "p4parser.tab.c"
    break;

  case 223:
#line 658 "p4parser.y"
                   {}
#line 4134 "p4parser.tab.c"
    break;

  case 224:
#line 665 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4143 "p4parser.tab.c"
    break;

  case 225:
#line 669 "p4parser.y"
                          {}
#line 4149 "p4parser.tab.c"
    break;

  case 230:
#line 680 "p4parser.y"
                                     {}
#line 4155 "p4parser.tab.c"
    break;

  case 231:
#line 681 "p4parser.y"
                                       {}
#line 4161 "p4parser.tab.c"
    break;

  case 232:
#line 686 "p4parser.y"
                               {}
#line 4167 "p4parser.tab.c"
    break;

  case 233:
#line 687 "p4parser.y"
                                      {}
#line 4173 "p4parser.tab.c"
    break;

  case 234:
#line 691 "p4parser.y"
                                               {}
#line 4179 "p4parser.tab.c"
    break;

  case 235:
#line 692 "p4parser.y"
                                                          {}
#line 4185 "p4parser.tab.c"
    break;

  case 236:
#line 693 "p4parser.y"
                                 {}
#line 4191 "p4parser.tab.c"
    break;

  case 237:
#line 694 "p4parser.y"
                                        {}
#line 4197 "p4parser.tab.c"
    break;

  case 239:
#line 704 "p4parser.y"
                                     {}
#line 4203 "p4parser.tab.c"
    break;

  case 240:
#line 705 "p4parser.y"
                                       {}
#line 4209 "p4parser.tab.c"
    break;

  case 241:
#line 706 "p4parser.y"
                                       {}
#line 4215 "p4parser.tab.c"
    break;

  case 242:
#line 707 "p4parser.y"
                                       {}
#line 4221 "p4parser.tab.c"
    break;

  case 243:
#line 708 "p4parser.y"
                                       {}
#line 4227 "p4parser.tab.c"
    break;

  case 244:
#line 712 "p4parser.y"
                                     {}
#line 4233 "p4parser.tab.c"
    break;

  case 245:
#line 713 "p4parser.y"
                                       {}
#line 4239 "p4parser.tab.c"
    break;

  case 246:
#line 717 "p4parser.y"
                                     {}
#line 4245 "p4parser.tab.c"
    break;

  case 247:
#line 718 "p4parser.y"
                                       {}
#line 4251 "p4parser.tab.c"
    break;

  case 248:
#line 722 "p4parser.y"
                                     {}
#line 4257 "p4parser.tab.c"
    break;

  case 249:
#line 726 "p4parser.y"
                                              {}
#line 4263 "p4parser.tab.c"
    break;

  case 250:
#line 730 "p4parser.y"
                                                    {}
#line 4269 "p4parser.tab.c"
    break;

  case 251:
#line 731 "p4parser.y"
                                                      {}
#line 4275 "p4parser.tab.c"
    break;

  case 252:
#line 735 "p4parser.y"
                                              {}
#line 4281 "p4parser.tab.c"
    break;

  case 253:
#line 739 "p4parser.y"
           {}
#line 4287 "p4parser.tab.c"
    break;

  case 254:
#line 740 "p4parser.y"
             {}
#line 4293 "p4parser.tab.c"
    break;

  case 255:
#line 741 "p4parser.y"
             {}
#line 4299 "p4parser.tab.c"
    break;

  case 256:
#line 742 "p4parser.y"
             {}
#line 4305 "p4parser.tab.c"
    break;

  case 257:
#line 743 "p4parser.y"
             {}
#line 4311 "p4parser.tab.c"
    break;

  case 258:
#line 745 "p4parser.y"
      {}
#line 4317 "p4parser.tab.c"
    break;

  case 259:
#line 747 "p4parser.y"
      {}
#line 4323 "p4parser.tab.c"
    break;

  case 260:
#line 749 "p4parser.y"
      {}
#line 4329 "p4parser.tab.c"
    break;

  case 261:
#line 752 "p4parser.y"
      {}
#line 4335 "p4parser.tab.c"
    break;

  case 262:
#line 754 "p4parser.y"
      {}
#line 4341 "p4parser.tab.c"
    break;

  case 263:
#line 756 "p4parser.y"
      {}
#line 4347 "p4parser.tab.c"
    break;

  case 264:
#line 760 "p4parser.y"
                {}
#line 4353 "p4parser.tab.c"
    break;

  case 265:
#line 761 "p4parser.y"
                  {}
#line 4359 "p4parser.tab.c"
    break;

  case 266:
#line 762 "p4parser.y"
                  {}
#line 4365 "p4parser.tab.c"
    break;

  case 267:
#line 767 "p4parser.y"
                              {}
#line 4371 "p4parser.tab.c"
    break;

  case 268:
#line 768 "p4parser.y"
                                {}
#line 4377 "p4parser.tab.c"
    break;

  case 269:
#line 772 "p4parser.y"
                                      {}
#line 4383 "p4parser.tab.c"
    break;

  case 270:
#line 776 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4395 "p4parser.tab.c"
    break;

  case 271:
#line 783 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4403 "p4parser.tab.c"
    break;

  case 272:
#line 789 "p4parser.y"
                                {}
#line 4409 "p4parser.tab.c"
    break;

  case 273:
#line 790 "p4parser.y"
                                  {}
#line 4415 "p4parser.tab.c"
    break;

  case 274:
#line 792 "p4parser.y"
                                  {}
#line 4421 "p4parser.tab.c"
    break;

  case 275:
#line 793 "p4parser.y"
                                       {}
#line 4427 "p4parser.tab.c"
    break;

  case 276:
#line 797 "p4parser.y"
                                   {}
#line 4433 "p4parser.tab.c"
    break;

  case 277:
#line 798 "p4parser.y"
                                     {}
#line 4439 "p4parser.tab.c"
    break;

  case 278:
#line 799 "p4parser.y"
                                       {}
#line 4445 "p4parser.tab.c"
    break;

  case 279:
#line 803 "p4parser.y"
                                {}
#line 4451 "p4parser.tab.c"
    break;

  case 280:
#line 804 "p4parser.y"
                                  {}
#line 4457 "p4parser.tab.c"
    break;

  case 281:
#line 805 "p4parser.y"
                                       {}
#line 4463 "p4parser.tab.c"
    break;

  case 282:
#line 811 "p4parser.y"
                                       {}
#line 4469 "p4parser.tab.c"
    break;

  case 283:
#line 812 "p4parser.y"
                                           {}
#line 4475 "p4parser.tab.c"
    break;

  case 284:
#line 816 "p4parser.y"
                               {}
#line 4481 "p4parser.tab.c"
    break;

  case 285:
#line 817 "p4parser.y"
                                       {}
#line 4487 "p4parser.tab.c"
    break;

  case 286:
#line 818 "p4parser.y"
                                       {}
#line 4493 "p4parser.tab.c"
    break;

  case 287:
#line 819 "p4parser.y"
                                       {}
#line 4499 "p4parser.tab.c"
    break;

  case 288:
#line 820 "p4parser.y"
                                       {}
#line 4505 "p4parser.tab.c"
    break;

  case 289:
#line 824 "p4parser.y"
                                     {}
#line 4511 "p4parser.tab.c"
    break;

  case 290:
#line 825 "p4parser.y"
                                       {}
#line 4517 "p4parser.tab.c"
    break;

  case 291:
#line 826 "p4parser.y"
                                       {}
#line 4523 "p4parser.tab.c"
    break;

  case 292:
#line 827 "p4parser.y"
                                       {}
#line 4529 "p4parser.tab.c"
    break;

  case 293:
#line 831 "p4parser.y"
                               {}
#line 4535 "p4parser.tab.c"
    break;

  case 294:
#line 831 "p4parser.y"
                                                    {}
#line 4541 "p4parser.tab.c"
    break;

  case 295:
#line 833 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4550 "p4parser.tab.c"
    break;

  case 296:
#line 842 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4559 "p4parser.tab.c"
    break;

  case 297:
#line 849 "p4parser.y"
                                     {}
#line 4565 "p4parser.tab.c"
    break;

  case 298:
#line 849 "p4parser.y"
                                                          {}
#line 4571 "p4parser.tab.c"
    break;

  case 299:
#line 850 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4580 "p4parser.tab.c"
    break;

  case 300:
#line 857 "p4parser.y"
                                     {}
#line 4586 "p4parser.tab.c"
    break;

  case 301:
#line 858 "p4parser.y"
                                       {}
#line 4592 "p4parser.tab.c"
    break;

  case 302:
#line 862 "p4parser.y"
                                           {}
#line 4598 "p4parser.tab.c"
    break;

  case 303:
#line 867 "p4parser.y"
                  {}
#line 4604 "p4parser.tab.c"
    break;

  case 304:
#line 868 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4613 "p4parser.tab.c"
    break;

  case 305:
#line 872 "p4parser.y"
                                       {}
#line 4619 "p4parser.tab.c"
    break;

  case 306:
#line 873 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4628 "p4parser.tab.c"
    break;

  case 307:
#line 880 "p4parser.y"
                            {}
#line 4634 "p4parser.tab.c"
    break;

  case 308:
#line 881 "p4parser.y"
                                                        {}
#line 4640 "p4parser.tab.c"
    break;

  case 309:
#line 885 "p4parser.y"
                               {}
#line 4646 "p4parser.tab.c"
    break;

  case 310:
#line 890 "p4parser.y"
        {}
#line 4652 "p4parser.tab.c"
    break;

  case 311:
#line 895 "p4parser.y"
        {}
#line 4658 "p4parser.tab.c"
    break;

  case 312:
#line 900 "p4parser.y"
                            {}
#line 4664 "p4parser.tab.c"
    break;

  case 313:
#line 901 "p4parser.y"
                                {}
#line 4670 "p4parser.tab.c"
    break;

  case 314:
#line 905 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4679 "p4parser.tab.c"
    break;

  case 315:
#line 909 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4688 "p4parser.tab.c"
    break;

  case 316:
#line 913 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4697 "p4parser.tab.c"
    break;

  case 317:
#line 917 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4706 "p4parser.tab.c"
    break;

  case 318:
#line 928 "p4parser.y"
        {}
#line 4712 "p4parser.tab.c"
    break;

  case 319:
#line 930 "p4parser.y"
        {}
#line 4718 "p4parser.tab.c"
    break;

  case 320:
#line 935 "p4parser.y"
        {}
#line 4724 "p4parser.tab.c"
    break;

  case 321:
#line 937 "p4parser.y"
        {}
#line 4730 "p4parser.tab.c"
    break;

  case 322:
#line 941 "p4parser.y"
                   {}
#line 4736 "p4parser.tab.c"
    break;

  case 323:
#line 945 "p4parser.y"
                   {}
#line 4742 "p4parser.tab.c"
    break;

  case 324:
#line 949 "p4parser.y"
                                {}
#line 4748 "p4parser.tab.c"
    break;

  case 325:
#line 950 "p4parser.y"
                                  {}
#line 4754 "p4parser.tab.c"
    break;

  case 326:
#line 955 "p4parser.y"
        {}
#line 4760 "p4parser.tab.c"
    break;

  case 327:
#line 957 "p4parser.y"
        {}
#line 4766 "p4parser.tab.c"
    break;

  case 328:
#line 962 "p4parser.y"
                                                              {}
#line 4772 "p4parser.tab.c"
    break;

  case 329:
#line 966 "p4parser.y"
                                     {}
#line 4778 "p4parser.tab.c"
    break;

  case 330:
#line 967 "p4parser.y"
                                       {}
#line 4784 "p4parser.tab.c"
    break;

  case 331:
#line 968 "p4parser.y"
                                       {}
#line 4790 "p4parser.tab.c"
    break;

  case 332:
#line 969 "p4parser.y"
                                       {}
#line 4796 "p4parser.tab.c"
    break;

  case 333:
#line 970 "p4parser.y"
                                       {}
#line 4802 "p4parser.tab.c"
    break;

  case 334:
#line 971 "p4parser.y"
                                       {}
#line 4808 "p4parser.tab.c"
    break;

  case 335:
#line 972 "p4parser.y"
                                       {}
#line 4814 "p4parser.tab.c"
    break;

  case 336:
#line 973 "p4parser.y"
                                       {}
#line 4820 "p4parser.tab.c"
    break;

  case 337:
#line 977 "p4parser.y"
                           {}
#line 4826 "p4parser.tab.c"
    break;

  case 338:
#line 978 "p4parser.y"
                             {}
#line 4832 "p4parser.tab.c"
    break;

  case 339:
#line 982 "p4parser.y"
                                          {}
#line 4838 "p4parser.tab.c"
    break;

  case 340:
#line 983 "p4parser.y"
                                            {}
#line 4844 "p4parser.tab.c"
    break;

  case 341:
#line 987 "p4parser.y"
                                                                  {}
#line 4850 "p4parser.tab.c"
    break;

  case 342:
#line 991 "p4parser.y"
                             {}
#line 4856 "p4parser.tab.c"
    break;

  case 343:
#line 992 "p4parser.y"
                               {}
#line 4862 "p4parser.tab.c"
    break;

  case 344:
#line 996 "p4parser.y"
                                     {}
#line 4868 "p4parser.tab.c"
    break;

  case 345:
#line 997 "p4parser.y"
                                       {}
#line 4874 "p4parser.tab.c"
    break;

  case 346:
#line 1001 "p4parser.y"
                             {}
#line 4880 "p4parser.tab.c"
    break;

  case 347:
#line 1002 "p4parser.y"
                               {}
#line 4886 "p4parser.tab.c"
    break;

  case 348:
#line 1006 "p4parser.y"
                             {}
#line 4892 "p4parser.tab.c"
    break;

  case 349:
#line 1007 "p4parser.y"
                               {}
#line 4898 "p4parser.tab.c"
    break;

  case 350:
#line 1008 "p4parser.y"
                               {}
#line 4904 "p4parser.tab.c"
    break;

  case 351:
#line 1009 "p4parser.y"
                               {}
#line 4910 "p4parser.tab.c"
    break;

  case 352:
#line 1017 "p4parser.y"
          {}
#line 4916 "p4parser.tab.c"
    break;

  case 353:
#line 1021 "p4parser.y"
                                       {}
#line 4922 "p4parser.tab.c"
    break;

  case 354:
#line 1022 "p4parser.y"
                                         {}
#line 4928 "p4parser.tab.c"
    break;

  case 355:
#line 1027 "p4parser.y"
        {}
#line 4934 "p4parser.tab.c"
    break;

  case 356:
#line 1029 "p4parser.y"
        {}
#line 4940 "p4parser.tab.c"
    break;

  case 357:
#line 1031 "p4parser.y"
        {}
#line 4946 "p4parser.tab.c"
    break;

  case 358:
#line 1033 "p4parser.y"
        {}
#line 4952 "p4parser.tab.c"
    break;

  case 359:
#line 1037 "p4parser.y"
                                       {}
#line 4958 "p4parser.tab.c"
    break;

  case 360:
#line 1038 "p4parser.y"
                                         {}
#line 4964 "p4parser.tab.c"
    break;

  case 361:
#line 1043 "p4parser.y"
                                         {}
#line 4970 "p4parser.tab.c"
    break;

  case 362:
#line 1047 "p4parser.y"
           {}
#line 4976 "p4parser.tab.c"
    break;

  case 363:
#line 1049 "p4parser.y"
        {}
#line 4982 "p4parser.tab.c"
    break;

  case 365:
#line 1058 "p4parser.y"
        {}
#line 4988 "p4parser.tab.c"
    break;

  case 366:
#line 1060 "p4parser.y"
        {}
#line 4994 "p4parser.tab.c"
    break;

  case 367:
#line 1065 "p4parser.y"
        {}
#line 5000 "p4parser.tab.c"
    break;

  case 368:
#line 1069 "p4parser.y"
                                   {}
#line 5006 "p4parser.tab.c"
    break;

  case 369:
#line 1070 "p4parser.y"
                                     {}
#line 5012 "p4parser.tab.c"
    break;

  case 370:
#line 1076 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 5021 "p4parser.tab.c"
    break;

  case 371:
#line 1085 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5030 "p4parser.tab.c"
    break;

  case 372:
#line 1089 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5039 "p4parser.tab.c"
    break;

  case 373:
#line 1097 "p4parser.y"
                                     {}
#line 5045 "p4parser.tab.c"
    break;

  case 374:
#line 1101 "p4parser.y"
                                     {}
#line 5051 "p4parser.tab.c"
    break;

  case 375:
#line 1102 "p4parser.y"
                                          {}
#line 5057 "p4parser.tab.c"
    break;

  case 376:
#line 1106 "p4parser.y"
                                        {}
#line 5063 "p4parser.tab.c"
    break;

  case 377:
#line 1112 "p4parser.y"
                                       {}
#line 5069 "p4parser.tab.c"
    break;

  case 378:
#line 1116 "p4parser.y"
                                       {}
#line 5075 "p4parser.tab.c"
    break;

  case 379:
#line 1117 "p4parser.y"
                                         {}
#line 5081 "p4parser.tab.c"
    break;

  case 380:
#line 1121 "p4parser.y"
                                       {}
#line 5087 "p4parser.tab.c"
    break;

  case 381:
#line 1122 "p4parser.y"
                                           {}
#line 5093 "p4parser.tab.c"
    break;

  case 382:
#line 1126 "p4parser.y"
                                       {}
#line 5099 "p4parser.tab.c"
    break;

  case 383:
#line 1127 "p4parser.y"
                                            {}
#line 5105 "p4parser.tab.c"
    break;

  case 384:
#line 1128 "p4parser.y"
                                              {}
#line 5111 "p4parser.tab.c"
    break;

  case 385:
#line 1132 "p4parser.y"
                                       {}
#line 5117 "p4parser.tab.c"
    break;

  case 386:
#line 1133 "p4parser.y"
                                         {}
#line 5123 "p4parser.tab.c"
    break;

  case 387:
#line 1134 "p4parser.y"
                                           {}
#line 5129 "p4parser.tab.c"
    break;

  case 388:
#line 1138 "p4parser.y"
                                       {}
#line 5135 "p4parser.tab.c"
    break;

  case 389:
#line 1139 "p4parser.y"
                                         {}
#line 5141 "p4parser.tab.c"
    break;

  case 390:
#line 1143 "p4parser.y"
        {}
#line 5147 "p4parser.tab.c"
    break;

  case 391:
#line 1143 "p4parser.y"
                {}
#line 5153 "p4parser.tab.c"
    break;

  case 392:
#line 1147 "p4parser.y"
                                       {}
#line 5159 "p4parser.tab.c"
    break;

  case 393:
#line 1148 "p4parser.y"
                                         {}
#line 5165 "p4parser.tab.c"
    break;

  case 394:
#line 1149 "p4parser.y"
                                         {}
#line 5171 "p4parser.tab.c"
    break;

  case 395:
#line 1150 "p4parser.y"
                                       {}
#line 5177 "p4parser.tab.c"
    break;

  case 396:
#line 1154 "p4parser.y"
                                            {}
#line 5183 "p4parser.tab.c"
    break;

  case 397:
#line 1155 "p4parser.y"
                                                      {}
#line 5189 "p4parser.tab.c"
    break;

  case 398:
#line 1158 "p4parser.y"
                                       {}
#line 5195 "p4parser.tab.c"
    break;

  case 399:
#line 1159 "p4parser.y"
                                         {}
#line 5201 "p4parser.tab.c"
    break;

  case 400:
#line 1160 "p4parser.y"
                                         {}
#line 5207 "p4parser.tab.c"
    break;

  case 401:
#line 1161 "p4parser.y"
                                         {}
#line 5213 "p4parser.tab.c"
    break;

  case 402:
#line 1162 "p4parser.y"
                                         {}
#line 5219 "p4parser.tab.c"
    break;

  case 403:
#line 1163 "p4parser.y"
                                         {}
#line 5225 "p4parser.tab.c"
    break;

  case 404:
#line 1164 "p4parser.y"
                                         {}
#line 5231 "p4parser.tab.c"
    break;

  case 405:
#line 1165 "p4parser.y"
                                                     {}
#line 5237 "p4parser.tab.c"
    break;

  case 406:
#line 1166 "p4parser.y"
                                                                 {}
#line 5243 "p4parser.tab.c"
    break;

  case 407:
#line 1167 "p4parser.y"
                                                 {}
#line 5249 "p4parser.tab.c"
    break;

  case 408:
#line 1168 "p4parser.y"
                                                 {}
#line 5255 "p4parser.tab.c"
    break;

  case 409:
#line 1169 "p4parser.y"
                                                 {}
#line 5261 "p4parser.tab.c"
    break;

  case 410:
#line 1170 "p4parser.y"
                                         {}
#line 5267 "p4parser.tab.c"
    break;

  case 411:
#line 1171 "p4parser.y"
                                                {}
#line 5273 "p4parser.tab.c"
    break;

  case 412:
#line 1172 "p4parser.y"
                                           {}
#line 5279 "p4parser.tab.c"
    break;

  case 413:
#line 1173 "p4parser.y"
                                          {}
#line 5285 "p4parser.tab.c"
    break;

  case 414:
#line 1175 "p4parser.y"
        {}
#line 5291 "p4parser.tab.c"
    break;

  case 415:
#line 1177 "p4parser.y"
        {}
#line 5297 "p4parser.tab.c"
    break;

  case 416:
#line 1178 "p4parser.y"
                                         {}
#line 5303 "p4parser.tab.c"
    break;

  case 417:
#line 1179 "p4parser.y"
                                         {}
#line 5309 "p4parser.tab.c"
    break;

  case 418:
#line 1180 "p4parser.y"
                                         {}
#line 5315 "p4parser.tab.c"
    break;

  case 419:
#line 1181 "p4parser.y"
                                         {}
#line 5321 "p4parser.tab.c"
    break;

  case 420:
#line 1182 "p4parser.y"
                                          {}
#line 5327 "p4parser.tab.c"
    break;

  case 421:
#line 1183 "p4parser.y"
                                           {}
#line 5333 "p4parser.tab.c"
    break;

  case 422:
#line 1184 "p4parser.y"
                                            {}
#line 5339 "p4parser.tab.c"
    break;

  case 423:
#line 1185 "p4parser.y"
                                             {}
#line 5345 "p4parser.tab.c"
    break;

  case 424:
#line 1186 "p4parser.y"
                                        {}
#line 5351 "p4parser.tab.c"
    break;

  case 425:
#line 1188 "p4parser.y"
        {}
#line 5357 "p4parser.tab.c"
    break;

  case 426:
#line 1189 "p4parser.y"
                                       {}
#line 5363 "p4parser.tab.c"
    break;

  case 427:
#line 1190 "p4parser.y"
                                       {}
#line 5369 "p4parser.tab.c"
    break;

  case 428:
#line 1192 "p4parser.y"
                                         {}
#line 5375 "p4parser.tab.c"
    break;

  case 429:
#line 1193 "p4parser.y"
                                             {}
#line 5381 "p4parser.tab.c"
    break;

  case 430:
#line 1195 "p4parser.y"
                                       {}
#line 5387 "p4parser.tab.c"
    break;

  case 431:
#line 1196 "p4parser.y"
                                       {}
#line 5393 "p4parser.tab.c"
    break;

  case 432:
#line 1197 "p4parser.y"
                                             {}
#line 5399 "p4parser.tab.c"
    break;

  case 433:
#line 1198 "p4parser.y"
                                             {}
#line 5405 "p4parser.tab.c"
    break;

  case 434:
#line 1199 "p4parser.y"
                                            {}
#line 5411 "p4parser.tab.c"
    break;

  case 435:
#line 1200 "p4parser.y"
                                       {}
#line 5417 "p4parser.tab.c"
    break;

  case 436:
#line 1201 "p4parser.y"
                                        {}
#line 5423 "p4parser.tab.c"
    break;

  case 437:
#line 1202 "p4parser.y"
                                       {}
#line 5429 "p4parser.tab.c"
    break;

  case 438:
#line 1203 "p4parser.y"
                                                      {}
#line 5435 "p4parser.tab.c"
    break;

  case 439:
#line 1204 "p4parser.y"
                         {}
#line 5441 "p4parser.tab.c"
    break;

  case 441:
#line 1208 "p4parser.y"
        {}
#line 5447 "p4parser.tab.c"
    break;

  case 442:
#line 1210 "p4parser.y"
        {}
#line 5453 "p4parser.tab.c"
    break;

  case 443:
#line 1212 "p4parser.y"
        {}
#line 5459 "p4parser.tab.c"
    break;

  case 444:
#line 1213 "p4parser.y"
                                                      {}
#line 5465 "p4parser.tab.c"
    break;

  case 445:
#line 1217 "p4parser.y"
                                       {}
#line 5471 "p4parser.tab.c"
    break;

  case 446:
#line 1218 "p4parser.y"
                                         {}
#line 5477 "p4parser.tab.c"
    break;

  case 447:
#line 1219 "p4parser.y"
                                         {}
#line 5483 "p4parser.tab.c"
    break;

  case 448:
#line 1220 "p4parser.y"
                                         {}
#line 5489 "p4parser.tab.c"
    break;

  case 449:
#line 1221 "p4parser.y"
                                         {}
#line 5495 "p4parser.tab.c"
    break;

  case 450:
#line 1222 "p4parser.y"
                                         {}
#line 5501 "p4parser.tab.c"
    break;

  case 451:
#line 1223 "p4parser.y"
                                         {}
#line 5507 "p4parser.tab.c"
    break;

  case 452:
#line 1224 "p4parser.y"
                                                             {}
#line 5513 "p4parser.tab.c"
    break;

  case 453:
#line 1225 "p4parser.y"
                                                                         {}
#line 5519 "p4parser.tab.c"
    break;

  case 454:
#line 1226 "p4parser.y"
                                                 {}
#line 5525 "p4parser.tab.c"
    break;

  case 455:
#line 1227 "p4parser.y"
                                         {}
#line 5531 "p4parser.tab.c"
    break;

  case 456:
#line 1228 "p4parser.y"
                                                {}
#line 5537 "p4parser.tab.c"
    break;

  case 457:
#line 1229 "p4parser.y"
                                           {}
#line 5543 "p4parser.tab.c"
    break;

  case 458:
#line 1230 "p4parser.y"
                                          {}
#line 5549 "p4parser.tab.c"
    break;

  case 459:
#line 1232 "p4parser.y"
        {}
#line 5555 "p4parser.tab.c"
    break;

  case 460:
#line 1234 "p4parser.y"
        {}
#line 5561 "p4parser.tab.c"
    break;

  case 461:
#line 1235 "p4parser.y"
                                                 {}
#line 5567 "p4parser.tab.c"
    break;

  case 462:
#line 1236 "p4parser.y"
                                                 {}
#line 5573 "p4parser.tab.c"
    break;

  case 463:
#line 1237 "p4parser.y"
                                                 {}
#line 5579 "p4parser.tab.c"
    break;

  case 464:
#line 1238 "p4parser.y"
                                                 {}
#line 5585 "p4parser.tab.c"
    break;

  case 465:
#line 1239 "p4parser.y"
                                                  {}
#line 5591 "p4parser.tab.c"
    break;

  case 466:
#line 1240 "p4parser.y"
                                                   {}
#line 5597 "p4parser.tab.c"
    break;

  case 467:
#line 1241 "p4parser.y"
                                                    {}
#line 5603 "p4parser.tab.c"
    break;

  case 468:
#line 1242 "p4parser.y"
                                                     {}
#line 5609 "p4parser.tab.c"
    break;

  case 469:
#line 1243 "p4parser.y"
                                                {}
#line 5615 "p4parser.tab.c"
    break;

  case 470:
#line 1245 "p4parser.y"
        {}
#line 5621 "p4parser.tab.c"
    break;

  case 471:
#line 1246 "p4parser.y"
                                               {}
#line 5627 "p4parser.tab.c"
    break;

  case 472:
#line 1247 "p4parser.y"
                                               {}
#line 5633 "p4parser.tab.c"
    break;

  case 473:
#line 1249 "p4parser.y"
                                         {}
#line 5639 "p4parser.tab.c"
    break;

  case 474:
#line 1250 "p4parser.y"
                                                     {}
#line 5645 "p4parser.tab.c"
    break;

  case 475:
#line 1251 "p4parser.y"
                                               {}
#line 5651 "p4parser.tab.c"
    break;

  case 476:
#line 1252 "p4parser.y"
                                               {}
#line 5657 "p4parser.tab.c"
    break;

  case 477:
#line 1253 "p4parser.y"
                                                     {}
#line 5663 "p4parser.tab.c"
    break;

  case 478:
#line 1254 "p4parser.y"
                                                     {}
#line 5669 "p4parser.tab.c"
    break;

  case 479:
#line 1255 "p4parser.y"
                                                    {}
#line 5675 "p4parser.tab.c"
    break;

  case 480:
#line 1256 "p4parser.y"
                                               {}
#line 5681 "p4parser.tab.c"
    break;

  case 481:
#line 1257 "p4parser.y"
                                                {}
#line 5687 "p4parser.tab.c"
    break;

  case 482:
#line 1258 "p4parser.y"
                                               {}
#line 5693 "p4parser.tab.c"
    break;

  case 483:
#line 1259 "p4parser.y"
                                                              {}
#line 5699 "p4parser.tab.c"
    break;

  case 484:
#line 1261 "p4parser.y"
        {}
#line 5705 "p4parser.tab.c"
    break;

  case 485:
#line 1263 "p4parser.y"
        {}
#line 5711 "p4parser.tab.c"
    break;

  case 486:
#line 1265 "p4parser.y"
        {}
#line 5717 "p4parser.tab.c"
    break;

  case 487:
#line 1266 "p4parser.y"
                                                      {}
#line 5723 "p4parser.tab.c"
    break;


#line 5727 "p4parser.tab.c"

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
#line 1294 "p4parser.y"


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
