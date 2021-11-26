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
#define YYLAST   4136

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  152
/* YYNRULES -- Number of rules.  */
#define YYNRULES  489
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
     680,   681,   686,   685,   691,   692,   693,   700,   701,   702,
     703,   704,   708,   709,   713,   714,   718,   722,   726,   727,
     731,   735,   736,   737,   738,   739,   740,   742,   744,   747,
     749,   751,   756,   757,   758,   763,   764,   768,   772,   779,
     785,   786,   788,   789,   793,   794,   795,   799,   800,   801,
     807,   808,   812,   813,   814,   815,   816,   820,   821,   822,
     823,   827,   827,   827,   836,   845,   845,   845,   853,   854,
     858,   863,   862,   868,   868,   876,   877,   881,   885,   890,
     896,   897,   901,   905,   909,   913,   923,   925,   930,   932,
     937,   941,   945,   946,   950,   952,   958,   962,   963,   964,
     965,   966,   967,   968,   969,   973,   973,   978,   979,   983,
     987,   988,   992,   993,   997,   998,  1002,  1003,  1004,  1005,
    1011,  1017,  1018,  1022,  1024,  1026,  1028,  1033,  1034,  1038,
    1043,  1044,  1049,  1053,  1055,  1060,  1065,  1066,  1072,  1081,
    1085,  1092,  1097,  1098,  1102,  1108,  1112,  1113,  1117,  1118,
    1122,  1123,  1124,  1128,  1129,  1130,  1134,  1135,  1139,  1139,
    1143,  1144,  1145,  1146,  1150,  1151,  1154,  1155,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1163,  1164,  1165,  1166,  1167,
    1168,  1169,  1170,  1172,  1174,  1175,  1176,  1177,  1178,  1179,
    1180,  1181,  1182,  1183,  1185,  1186,  1187,  1189,  1191,  1192,
    1193,  1194,  1195,  1196,  1197,  1198,  1199,  1200,  1202,  1203,
    1205,  1207,  1209,  1213,  1214,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,  1229,  1231,
    1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,  1240,  1242,
    1243,  1244,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,
    1254,  1255,  1256,  1258,  1260,  1262,  1285,  1285,  1286,  1286
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
  "$@13", "methodPrototype", "typeRef", "namedType", "prefixedType",
  "typeName", "tupleType", "headerStackType", "specializedType",
  "baseType", "typeOrVoid", "optTypeParameters", "typeParameters",
  "typeParameterList", "typeArg", "typeArgumentList", "realTypeArg",
  "realTypeArgumentList", "typeDeclaration", "derivedTypeDeclaration",
  "headerTypeDeclaration", "$@14", "$@15", "structTypeDeclaration",
  "headerUnionDeclaration", "$@16", "$@17", "structFieldList",
  "structField", "enumDeclaration", "$@18", "$@19",
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

#define YYPACT_NINF (-769)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-384)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -769,   109,  -769,   854,  -769,  -769,  -769,   301,  -769,   227,
      31,   227,    50,   301,  -769,   227,   227,  -769,  -769,  -769,
    -769,  1618,   936,  -769,    46,  -769,    27,  -769,   179,  -769,
     180,  -769,  -769,   -30,    74,  -769,   307,  -769,  -769,   129,
    -769,   301,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
     117,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,   225,  -769,  -769,   -27,   301,   -26,   301,
    -769,  2552,   -25,   301,   370,   301,  2682,  2595,   301,   301,
     936,   301,   301,   301,   936,  -769,  -769,    89,  -769,  -769,
     -24,  -769,  -769,  -769,   145,   150,   -30,  -769,  2041,  2537,
    2552,  2537,   227,  -769,  2090,  -769,  2537,   244,  -769,   -14,
    2537,   244,    -6,  1776,  -769,  -769,  -769,  -769,  -769,   275,
    2537,   244,   158,   301,  -769,   123,  -769,   301,   260,   153,
     155,   168,  -769,  -769,  -769,    96,   301,   301,  -769,  -769,
     227,   301,   301,  2041,    37,   184,   177,  -769,   198,  -769,
    -769,  2537,  2537,  2537,  2139,  1409,  2537,  -769,  -769,  -769,
    -769,   190,  -769,  -769,   206,   223,   395,   233,    59,  -769,
     235,   243,  -769,  3773,  -769,  -769,  2959,   275,  2996,  -769,
    -769,   301,   242,   -21,  -769,    -5,  3773,  1868,  3033,  -769,
    -769,  -769,  -769,   301,  3070,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  2552,  -769,  3107,  -769,
     -24,   255,   227,   270,  -769,   227,  -769,  -769,   227,   227,
    -769,  -769,   227,   227,   276,  -769,  -769,   283,  -769,  -769,
    -769,   370,  -769,   -30,  -769,   271,  -769,   102,   102,   102,
     106,   128,   190,   286,   208,   266,  3144,   102,   301,  2537,
    -769,  2041,  -769,  -769,   301,  2341,  2537,  2537,  2537,  2537,
    2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,
    2537,  2537,  2537,  2537,  2537,   296,  2041,  2537,  2537,  -769,
    1040,  -769,  -769,  -769,   305,  -769,   284,  2537,  -769,   301,
    -769,  2537,  -769,   244,  -769,   244,  1960,  -769,   244,   308,
    2537,  -769,   301,   312,  -769,  -769,  -769,  -769,  -769,  -769,
     301,   301,  -769,   936,   -30,   -23,   936,  -769,  -769,    11,
    -769,  -769,  -769,  -769,  1122,  -769,  -769,  2537,  -769,  -769,
    3773,   310,   301,   245,  -769,  3981,  3981,  1123,  3917,  3884,
    3950,  3950,   234,   234,   234,   234,   102,   102,   102,  4012,
    4074,  4043,  2848,  3981,  2537,   311,  3181,   234,  -769,  -769,
    -769,  -769,   303,  3981,   -24,   301,  -769,  3773,  -769,  3773,
    -769,  -769,  -769,  -769,   -30,   306,  3773,   318,   142,   301,
     328,   331,   333,   334,   335,    -8,   252,   329,   -43,  -769,
    -769,    51,  -769,  -769,  -769,  -769,   342,  -769,   301,   148,
     337,  -769,  -769,  -769,   330,   346,  2390,   349,  -769,     3,
    -769,   395,   289,  -769,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   397,   102,  -769,
    -769,   353,  -769,  -769,  2537,  1123,  -769,  2537,  2552,   350,
     354,  -769,  -769,  -769,   -24,  -769,   344,   178,  -769,  -769,
    -769,  -769,   -24,   -24,  -769,   370,  -769,   353,  -769,  2537,
     301,   227,   314,   363,  -769,  -769,   368,   337,  2537,   355,
    -769,  2537,  -769,  3218,  2537,  -769,   345,  2537,  2041,  2537,
    -769,  -769,  2552,  -769,   356,  3255,  3847,  -769,  2041,  -769,
     367,  2537,  -769,   301,    58,    67,    71,   369,   377,   301,
     374,  3773,  -769,   370,  -769,    81,   375,  -769,  -769,  3292,
    -769,  3329,   387,  2885,   389,  3366,   275,  1534,  -769,  -769,
     404,  -769,  -769,  -769,  -769,   867,  -769,  -769,  -769,  -769,
    -769,   380,  -769,   402,   244,   244,   244,   391,   403,   386,
      66,  -769,  -769,  2649,   422,  2041,  -769,  2537,   405,  -769,
     421,  -769,   936,  -769,  -769,  -769,  -769,  1551,   424,   418,
    -769,  -769,   427,   430,   431,   441,   443,  -769,   113,  -769,
    -769,   434,   415,  -769,   444,  3403,  -769,  2041,   436,   -24,
    -769,   698,  2537,  2537,  2537,  -769,  -769,  -769,   442,  -769,
    -769,  -769,  -769,   445,  2649,  2439,   440,  -769,   450,  -769,
     460,   419,     9,   936,  -769,  -769,   467,   301,  -769,  -769,
    -769,  -769,  -769,  -769,  3440,  3477,  3514,    97,  2488,   469,
    2537,  -769,  2537,  2537,  2537,  -769,  1409,  2537,  -769,  -769,
    -769,  -769,   461,  -769,  -769,  -769,   395,   470,    59,  -769,
     468,  3810,  -769,   471,   472,   475,   474,  -769,  -769,  -769,
     301,  -769,   301,   301,   301,  -769,   171,  -769,  -769,  -769,
    3551,  2190,   476,   102,   102,   102,   484,  3588,   102,   301,
    -769,  2041,  -769,   -16,  2537,  2537,  2537,  2537,  2537,  2537,
    2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,  2537,
    2537,  2537,  2537,   492,  2041,  2537,  2537,  -769,  1040,  -769,
    -769,  2239,  -769,  -769,   483,   485,   486,   503,   487,   496,
     301,  1266,  -769,  -769,   489,  -769,  -769,  -769,  1490,  2808,
    -769,  2537,  -769,  -769,   497,  -769,  3981,  3981,  1123,  3917,
    3884,  3950,  3950,   234,   234,   234,   234,   102,   102,   102,
    4012,  4074,  4043,  2922,  3981,  2537,   500,  3625,   234,   303,
    3981,     1,  1322,  -769,  -769,  -769,  -769,  2041,   -30,   493,
     498,   505,   501,  2768,   171,  -769,  -769,  2537,  2537,   102,
    -769,  -769,  2537,  1123,  -769,  2537,   508,   510,  -769,   511,
     509,  -769,  2290,  2537,  2537,   -30,  3773,  3773,  3662,  3847,
    2041,  -769,  -769,  -769,     5,  -769,  3699,  3736,   513,  -769,
     512,  1674,  -769,  2290,  -769,  -769,  -769,  -769,   515,  -769,
     301,   516,  -769
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   158,     6,     0,   251,   253,
     252,   255,     0,     0,   254,     0,     0,   263,   264,   244,
       5,     0,    34,    35,     0,    13,     0,    10,   156,    12,
     156,     8,   227,    33,   262,   246,   238,   241,   240,   239,
     237,     0,    11,   282,   287,   289,   288,   290,    14,    15,
       0,     9,     7,    16,    20,    18,    22,    19,    23,    21,
      17,    25,    24,    37,   486,   487,     0,     0,     0,     0,
      42,   274,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,    33,   252,    36,     0,   286,   245,
      33,   284,   159,   285,     0,     0,    34,   375,   438,   438,
     274,   438,   265,   283,   438,    42,   438,     0,   310,     0,
     438,     0,     0,     0,   273,   272,   271,   270,   275,     0,
     438,     0,     0,     0,   213,   244,   301,     0,   264,   224,
       0,     0,   262,   291,   295,     0,     0,     0,   144,   168,
     265,     0,     0,   438,   143,     0,   135,   136,     0,   216,
     335,   438,   438,   438,   438,   438,   438,   382,   398,   399,
     400,     0,   397,   396,   401,     0,     0,     0,   242,   243,
       0,   377,   378,   380,   437,   401,     0,     0,     0,   232,
     266,     0,     0,     0,   131,     0,   384,     0,     0,   488,
     489,   256,   308,     0,     0,   257,   309,    45,    41,   104,
     103,    99,   100,   102,   101,   106,   108,   107,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,    95,   122,    96,    42,   123,   124,   130,   125,   126,
     127,   128,   129,   105,    90,    98,    97,    84,    61,    82,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    62,    63,    64,    65,    66,
      67,    68,    76,    69,    70,    71,    73,    72,    74,    75,
      77,    78,    79,    80,    81,    83,    85,    86,    87,    88,
      89,    91,    92,    93,    94,    44,     0,   247,     0,   258,
      33,     0,   265,     0,   303,   265,   228,   229,   265,   265,
     314,   315,   265,   265,     0,   312,   313,     0,   140,   142,
     141,     0,   157,    33,   162,    33,   337,   411,   410,   409,
       0,     0,   252,     0,   238,   239,     0,   408,     0,   438,
     402,   438,   388,   412,     0,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,     0,   438,   438,   438,   414,
     438,   248,   250,   249,     0,   268,     0,   438,    40,     0,
      39,   438,    38,     0,   311,     0,     0,   276,     0,     0,
     438,   214,     0,     0,   225,   292,   296,   145,   169,   298,
       0,     0,   137,    33,    33,     0,    34,   221,   217,     0,
     220,   219,   222,   218,    33,   406,   405,   438,   407,   413,
     381,     0,     0,     0,   379,   424,   425,   422,   434,   435,
     428,   429,   418,   419,   420,   421,   415,   416,   417,   432,
     430,   431,     0,   427,   438,     0,     0,   433,   279,   278,
     277,   280,     0,   426,    33,     0,   267,   133,   132,   385,
     259,   260,    43,   261,    33,     0,   374,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,   138,     0,   165,
     163,    33,   171,   167,   166,   164,     0,   223,     0,     0,
     372,   336,   320,   391,     0,     0,   438,     0,   386,     0,
     349,     0,   238,   327,   316,   330,   333,   332,   329,   328,
     348,   331,   334,   338,   346,   347,   390,     0,   442,   441,
     389,     0,   148,   403,   438,   423,   440,   438,     0,     0,
       0,   269,   368,   371,    33,   302,     0,     0,   305,   230,
     298,   298,    33,    33,   294,     0,   299,     0,   147,   438,
       0,     0,     0,     0,   172,   212,     0,   372,   438,     0,
     321,   438,   322,     0,   438,   387,     0,   438,   438,   438,
     392,   393,   274,   152,     0,     0,   436,   281,   438,   233,
       0,   438,   304,     0,    33,    33,    33,     0,     0,     0,
       0,   139,   173,     0,   161,    33,     0,   373,   370,     0,
     323,     0,     0,     0,     0,     0,     0,     0,   150,   404,
       0,   215,   307,   306,   226,     0,   231,   293,   297,   146,
     170,     0,   149,     0,     0,     0,     0,     0,     0,    31,
      33,   351,   369,    33,     0,   438,   394,   438,     0,   317,
       0,   151,     0,   155,   153,   154,   439,     0,   244,     0,
     300,   175,     0,     0,     0,     0,     0,    32,     0,   350,
     352,     0,   324,   340,     0,     0,   318,   438,     0,    33,
     234,    33,   438,   438,   438,   360,   357,    28,     0,    30,
      29,    26,    27,     0,    33,     0,     0,   395,     0,   235,
       0,     0,     0,    34,   176,   182,     0,     0,   177,   179,
     183,   178,   180,   181,     0,     0,     0,    33,   438,     0,
     438,   325,   438,   438,   438,   339,   438,   438,   445,   446,
     447,   344,     0,   444,   443,   448,     0,     0,   242,   341,
       0,   345,   326,     0,     0,     0,     0,   187,   189,   184,
       0,   174,     0,     0,     0,   354,     0,   361,   353,   358,
       0,   438,     0,   456,   455,   454,     0,     0,   453,     0,
     449,   438,   457,   343,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,     0,   438,   438,   438,   459,   438,   319,
     236,   438,   188,   175,     0,     0,     0,     0,     0,   363,
       0,   438,   208,   207,     0,   194,   195,   366,   438,   204,
     356,   438,   452,   458,     0,   342,   469,   470,   467,   479,
     480,   473,   474,   463,   464,   465,   466,   460,   461,   462,
     477,   475,   476,     0,   472,   438,     0,     0,   478,     0,
     471,     0,    33,   211,   210,   209,   362,   438,    33,   203,
     202,     0,     0,   204,     0,   355,   367,   438,   438,   485,
     484,   450,   438,   468,   483,   438,     0,     0,   185,     0,
       0,   197,   438,   438,   438,    33,   205,   206,     0,   481,
     438,   191,   364,   359,     0,   198,   200,   201,     0,   451,
       0,   438,   196,   438,   365,   482,   190,   192,     0,   199,
       0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -769,  -769,  -769,  -769,  -769,    -7,   126,  -769,  -769,    15,
       0,   -11,   -84,  -769,   409,   199,  -278,  -769,   264,  -769,
    -769,  -769,  -769,  -301,    42,  -769,  -769,   553,   213,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,   115,  -769,
    -196,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -769,  -289,
    -769,  -769,  -769,  -768,  -769,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -769,  -769,   -70,  -769,  -769,
     504,   -80,  -769,   347,    16,  -769,   608,    18,  -769,   -81,
    -769,  -769,  -273,   -98,  -769,  -184,  -769,    77,  -769,  -769,
    -769,  -769,  -769,  -769,  -769,  -189,  -769,  -769,  -769,  -769,
    -769,    25,  -769,  -769,   -59,  -769,  -653,  -769,  -645,  -769,
    -769,  -644,  -642,  -595,   -29,  -769,  -769,  -769,  -769,  -769,
    -769,  -769,  -769,  -769,   -17,  -769,  -769,  -769,  -769,  -237,
    -190,  -769,   295,  -293,     2,    65,  -528,    17,  -105,  -769,
     280,  -153,  -721,  -159,  -769,  -769,  -769,   914,  -769,  -769,
     134,   -75
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    20,   175,   165,   673,   648,   144,
      96,    23,   113,   285,   183,   184,   145,   146,   147,   311,
      24,   302,   463,    25,   564,   597,   634,    92,   166,    27,
     148,   543,   393,   470,    28,   303,   464,   471,   472,   613,
     661,   684,   685,   783,   686,   727,   728,   881,   887,   794,
     795,   874,   841,   796,   473,    29,    30,   292,   457,   315,
     398,   476,    31,   295,   460,    32,   574,    33,   364,   606,
     117,   167,    35,   168,    37,    38,   169,    40,    41,   179,
     180,   366,   118,   119,   441,   442,    42,    43,    44,   298,
     461,    45,    46,   299,   462,   465,   536,    47,   293,   383,
     527,   528,    48,    49,   109,    50,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   316,   404,   502,   675,   719,
     720,   503,   400,   620,   621,   698,   739,   697,   737,   788,
     797,   798,    51,   692,   693,   549,   455,    53,   170,   171,
     172,   185,   506,   359,   412,   507,   561,   173,   174,   721,
     360,   191
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   321,   177,    22,    97,    52,    62,   131,   688,   333,
     112,    86,   379,   377,   397,   789,   689,   690,    21,   691,
     587,   187,   402,   842,   368,   106,   110,   120,   652,  -134,
     -33,     7,    74,   192,    62,   369,   195,     7,   307,   534,
     370,   196,   193,   602,   287,     7,   289,    73,    95,   150,
     193,   371,    74,     7,   857,   729,   540,   371,   882,   304,
      62,   883,    62,    98,   116,   541,    62,    13,    62,    62,
     129,    62,    62,    13,    62,    62,    62,    67,    74,   701,
     478,    13,    54,    55,    74,    86,   107,   111,   121,    13,
      56,   164,   469,   116,   875,   135,    69,   164,  -160,   135,
     474,    57,   362,   490,    58,   604,    88,    64,    65,     4,
      59,   504,     7,   649,   607,   889,    62,   332,   608,     7,
      62,    60,    61,   789,   308,   309,    98,     7,     7,    62,
      62,   310,     7,    63,    62,    62,   164,   617,    89,    70,
     376,   143,     7,    66,   735,    68,   353,   164,    13,    71,
      72,    65,   617,   405,   356,    13,   618,   137,     7,   330,
     332,   142,   369,    13,    13,   333,   520,   102,    13,   -25,
     100,   618,   742,   101,    62,   406,    76,   103,    13,   688,
      78,    79,   -25,   -25,   371,   667,    62,   689,   690,   525,
     691,   149,   668,   108,    13,   108,   150,    83,   193,   122,
     143,   124,   126,   130,   133,   134,   669,   138,   139,   140,
     290,   381,   670,   -24,   384,   296,    26,   385,   386,    54,
      55,   387,   388,   671,   672,   572,   411,    56,   297,     5,
     182,    90,    90,   313,   573,    26,   181,   312,    57,    91,
      93,    58,    54,    55,   314,   567,   570,    59,   328,   291,
      56,   435,    99,   294,   577,   578,    64,    65,    60,    61,
    -242,    57,   300,   301,    58,   -24,   332,   305,   306,   104,
      59,   347,   348,   349,   181,    64,    65,   105,   353,   116,
     182,    60,   329,    65,    26,   331,   356,    26,   334,    26,
      26,   446,   332,    26,   189,   190,   633,    26,   450,   335,
     451,   367,   100,   453,   511,   512,   -17,   365,   -17,   -17,
     101,   537,   538,    26,   380,   396,   382,   403,  -243,   374,
     -17,    62,   389,   458,   164,   189,   190,    62,   164,     5,
     395,   286,     7,    99,   189,   190,   390,    64,    65,   407,
     445,   575,   576,   394,     8,     9,   434,   556,   560,   164,
      36,    99,    85,   189,   190,    64,    65,   444,   459,   518,
      11,   454,    62,   509,   516,   477,   523,   519,    13,    36,
     524,    14,    54,    55,   529,    62,    15,   530,    16,   531,
      56,   680,    19,    62,    62,    86,   532,   533,   539,   545,
     550,    57,    62,   396,    58,   475,   548,   488,   551,   563,
      59,   554,   568,   571,   396,    62,   505,   569,   468,    95,
     584,    60,    61,   540,   585,   588,   598,   592,    36,   489,
     601,    36,   609,    36,    36,   522,   181,    36,     5,   181,
     610,    36,   181,   181,   612,   622,   181,   181,    62,   625,
     640,   557,   628,     8,     9,    64,    65,    36,   641,   558,
     645,    85,    62,   594,   409,   332,   559,   636,   100,    11,
     413,   647,   646,   600,   596,   656,    54,    55,   653,    95,
      14,    62,    62,   657,    56,    15,   659,    16,   660,   662,
     535,    19,   663,   664,   555,    57,   542,   665,    58,   666,
      54,    55,   556,   674,    59,   182,   679,   676,    56,    26,
     722,   699,   324,   723,   700,    60,    89,    34,   108,    57,
     725,   116,    58,   724,   731,   741,   466,   467,    59,   749,
     654,   630,   751,   753,    26,   480,    87,   781,    26,    60,
      61,   779,   780,    62,   782,   639,   800,   801,   510,   642,
     643,   644,   825,   833,   844,   834,   835,   836,   837,  -208,
     850,   164,   678,   854,  -207,   116,   871,   862,   861,   752,
     870,   164,   777,   320,   872,   885,    62,   658,   448,   873,
     890,   521,    62,   884,    54,    55,   892,   392,   123,   580,
     127,   132,    56,    94,   136,   526,   544,   832,   141,   605,
     535,   535,   888,    57,   829,   717,    58,   632,   603,   615,
     619,   616,    59,   650,   546,   547,    26,   865,   846,    26,
     401,    39,   586,    60,   635,   414,   488,   491,   164,     0,
       0,    86,     0,     0,     0,     0,   100,     0,   831,     0,
      39,     0,     0,    36,     0,   619,     0,     0,    95,     0,
       0,   562,     0,     0,     0,     0,   804,     0,     0,     0,
     164,     0,     0,     0,   488,     0,     0,     0,    36,   323,
       0,   683,    36,     0,     0,     0,   582,   488,   715,   826,
       0,     0,    86,     0,    62,   583,   682,     0,     0,    39,
      62,     0,    39,     0,    39,    39,     0,     0,    39,    95,
       0,     0,    39,     0,     0,     0,     0,     0,     0,   526,
       0,     0,     0,     0,     0,   611,     0,   324,    39,   750,
       0,     0,   736,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    62,   805,    62,    62,    62,     0,   488,
       0,    26,   859,     0,     0,     0,     0,     0,     0,     0,
      36,     0,    62,    36,   164,  -186,     0,     0,    26,     0,
       0,   492,     0,     0,   856,     0,     5,     0,   482,     7,
       0,     0,     0,   325,     0,   880,   483,   164,    95,    54,
      55,     8,     9,     0,     0,    26,     0,    56,     0,    85,
     555,     0,     0,    62,   485,     0,     0,    11,    57,     0,
       0,    58,     0,     0,     0,    13,    26,    59,    14,     0,
       0,     0,   681,    15,     0,    16,     0,   726,    60,    19,
      26,     0,     0,   480,     0,   391,     0,     0,    26,   399,
       0,     0,     0,     0,     0,   488,     0,     0,     0,     0,
     164,     0,   683,     0,     0,     0,   491,   488,     0,     0,
       0,     0,     0,     0,     0,    26,     0,   682,     0,     0,
      26,     0,   100,   860,    -3,   778,   547,     0,   784,   785,
     786,     0,     0,   164,   440,    36,     0,     0,     0,     0,
       0,     0,     0,     0,   491,   803,     0,     0,     0,     0,
     878,     0,    36,    62,     0,     0,     0,   491,   716,     0,
       0,     0,     0,     0,    39,     0,    26,   399,     0,     0,
     479,     0,     0,     0,     0,     0,     0,     0,   399,    36,
       0,     0,     5,     0,     6,     7,   838,     0,     0,    39,
       0,     0,     0,    39,     0,     5,     0,     8,     9,     0,
     614,     0,     0,     0,     0,    10,   637,     0,     0,     0,
       8,     9,     0,    11,    36,     0,    12,     0,    85,   787,
       0,    13,    36,     0,    14,     0,    11,     0,     0,    15,
       0,    16,     0,    17,    18,    19,     0,    14,   325,     0,
     651,     0,    15,     0,    16,     0,    17,    18,   638,    36,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     0,     0,     7,     0,     0,
       0,    39,     0,     0,    39,     0,     0,     0,   492,     8,
       9,     0,    39,   176,     0,   178,   891,    85,   186,     0,
     188,   651,   718,     0,   194,    11,     0,     0,     0,     0,
      36,     0,     0,    13,   288,     0,    14,     0,     0,   579,
       0,    15,     0,    16,     0,   491,     0,    19,     0,     0,
       0,     0,     0,   324,     0,     0,     0,   787,     0,     0,
       0,     0,     0,     0,     0,   317,   318,   319,   186,   326,
     327,     0,     0,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,     0,     0,     0,
       0,     0,   155,     0,   156,     0,     0,     0,     5,     0,
       0,    34,     0,   438,     0,     0,   158,   159,   160,   132,
       0,    54,    55,     8,     9,     0,     0,     0,     0,    56,
       0,   322,     0,     0,     0,   324,    39,     0,     0,    11,
      57,     0,     0,    58,     0,     0,    87,     0,   324,    59,
      14,   132,     0,    39,     0,    15,     0,    16,     0,   439,
      60,    19,   162,   163,     0,     0,   343,   344,   345,   346,
     347,   348,   349,     0,     0,   687,     0,   353,     0,   481,
      39,     0,    65,     0,     0,   356,     0,     0,     0,   492,
       5,   332,   482,     7,     0,   358,     0,   730,     0,     0,
     483,     0,     0,    54,    55,     8,     9,     0,     0,     0,
       0,    56,     0,    85,   484,    39,     0,     0,   485,     0,
     746,    11,    57,    39,     0,    58,     0,     0,     0,    13,
     486,    59,    14,     0,   487,     0,     0,    15,     0,    16,
       0,     0,    60,    19,     0,     0,     0,     0,     0,     0,
      39,     0,     0,   410,     0,    39,     0,     0,     0,     0,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,    39,
       0,   436,   437,     0,   443,     0,     0,     0,     0,     0,
       0,   447,   440,     0,     0,   449,     0,     0,     0,     0,
       0,    39,     0,     0,   456,   323,     0,     0,     0,   151,
     152,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,   154,     0,   325,     0,     0,     0,   155,     0,
     156,   508,     0,     0,     5,     0,     0,     0,     0,   839,
       0,     0,   158,   159,   160,     0,   687,    54,    55,     8,
       9,     0,     0,   840,     0,    56,     0,   322,   515,     0,
       0,     0,     0,     0,     0,    11,    57,     0,     0,    58,
       0,     0,     0,     0,     0,    59,    14,     0,     0,   858,
       0,    15,     0,    16,     0,     0,    60,    19,   162,   163,
       5,     0,   482,     7,     0,     0,   325,     0,     0,     0,
     483,     0,     0,    54,    55,     8,     9,     0,     0,   325,
     553,    56,     0,    85,     0,     0,     0,     0,   485,     0,
       0,    11,    57,     0,     0,    58,     0,     0,     0,    13,
       0,    59,    14,     0,     0,     0,     0,    15,   565,    16,
       0,   566,    60,    19,     0,     0,     0,     0,     0,     0,
      39,     0,   151,   152,     0,     0,     0,     0,     0,     0,
       0,     0,   153,   581,     0,   154,     0,     0,     0,     0,
       0,   155,   456,   156,     0,   589,     0,     5,   591,     0,
       0,   593,     0,   595,     0,   158,   159,   160,     0,     0,
      54,    55,     8,     9,     0,   456,     0,     0,    56,     0,
     322,     0,     0,     0,     0,     0,     0,     0,    11,    57,
       0,     0,    58,     0,     0,     0,     0,     0,    59,    14,
       0,     0,     0,     0,    15,     0,    16,     0,     0,    60,
      19,   162,   163,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   154,   845,     0,     0,
       0,   655,   791,     0,   156,     0,     0,     0,     5,     0,
       0,     0,     0,   792,     0,     0,   158,   159,   160,     0,
       0,    54,    55,     0,     0,     0,     0,   793,     0,    56,
       0,   161,     0,     0,     0,     0,   694,   695,   696,     0,
      57,   631,     0,    58,     0,     0,     0,     0,     0,    59,
       0,     0,     5,     0,     0,     7,     0,     0,     0,     0,
      60,    19,   162,   163,     0,     0,     0,     8,     9,     5,
       0,     0,   740,     0,   456,    85,   743,   744,   745,     0,
     747,   748,     0,    11,     8,     9,     0,     0,     0,     0,
       0,    13,    85,     0,    14,     0,     0,     0,     0,    15,
      11,    16,     0,    17,    18,    19,     0,     0,     0,     0,
       0,    14,     0,     0,     0,   799,    15,     0,    16,     0,
      17,    18,    19,     0,     0,     0,     0,     0,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   823,   824,     0,    73,   827,
     828,     0,   830,    74,    75,   186,     0,     0,    76,     0,
       0,    77,    78,    79,     0,   843,     0,   151,   152,     0,
       0,    80,   799,    81,    82,   849,     0,   153,     0,    83,
     154,   886,     0,     0,    84,     0,   791,     0,   156,     0,
       0,     0,     5,     0,     0,     0,     0,   792,     0,   853,
     158,   159,   160,     0,     0,    54,    55,     0,     0,     0,
       0,   793,     0,    56,     0,   161,     0,     0,     0,     0,
       0,   866,   867,     0,    57,     0,   868,    58,     0,   869,
       0,     0,     0,    59,     0,     0,   799,   876,   877,     0,
       0,     0,     0,     0,    60,    19,   162,   163,     0,     0,
       0,     0,     0,     0,     0,   799,     0,   799,   197,   198,
       0,     0,   199,   200,     0,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,     0,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     197,     0,     0,     0,   199,   200,     0,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   372,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   197,     0,     0,     0,   199,   200,     0,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   452,   225,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   151,   152,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   154,     0,     0,
       0,     0,     0,   155,  -376,   156,     0,     0,     0,     5,
       0,     0,     0,     0,   157,     0,     0,   158,   159,   160,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
      56,     0,   161,   151,   152,     0,     0,     0,     0,     0,
       0,    57,     0,   153,    58,  -383,   154,     0,     0,     0,
      59,     0,   155,     0,   156,     0,  -383,     0,     5,     0,
       0,    60,   125,   162,   163,     0,   158,   159,   160,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,    56,
       0,   161,   151,   152,     0,     0,     0,     0,     0,     0,
      57,     0,   153,    58,     0,   154,  -383,     0,     0,    59,
       0,   155,     0,   156,     0,  -383,     0,     5,     0,     0,
      60,   125,   162,   163,     0,   158,   159,   160,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,    56,     0,
     161,     0,     0,   151,   152,     0,     0,     0,     0,    57,
       0,     0,    58,   153,     0,     0,   154,     0,    59,     0,
       0,     0,   791,     0,   156,     0,     0,     0,     5,    60,
     125,   162,   163,   792,     0,     0,   158,   159,   160,     0,
       0,    54,    55,     0,     0,     0,     0,   793,     0,    56,
       0,   161,   151,   152,     0,     0,     0,     0,     0,     0,
      57,     0,   153,    58,     0,   154,     0,     0,     0,    59,
       0,   155,  -383,   156,     0,  -383,     0,     5,     0,     0,
      60,    19,   162,   163,     0,   158,   159,   160,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,    56,     0,
     161,     0,     0,   151,   152,     0,     0,     0,     0,    57,
       0,     0,    58,   153,     0,     0,   154,     0,    59,     0,
       0,     0,   155,     0,   156,     0,     0,     0,     5,    60,
      19,   162,   163,   792,     0,     0,   158,   159,   160,     0,
       0,    54,    55,     0,     0,     0,     0,   793,     0,    56,
       0,   161,     0,     0,   151,   152,     0,     0,     0,     0,
      57,     0,     0,    58,   153,     0,     0,   154,     0,    59,
       0,     0,     0,   155,     0,   156,     0,     0,     0,     5,
      60,    19,   162,   163,   157,     0,     0,   158,   159,   160,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
      56,     0,   161,   151,   152,     0,     0,     0,     0,     0,
       0,    57,     0,   153,    58,     0,   154,     0,     0,     0,
      59,     0,   155,     0,   156,     0,     0,     0,     5,     0,
     552,    60,   125,   162,   163,     0,   158,   159,   160,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,    56,
       0,   161,   702,   703,     0,     0,     0,     0,     0,     0,
      57,     0,   704,    58,     0,     0,   705,     0,     0,    59,
       0,   706,     0,   707,     0,     0,     0,     5,     0,     0,
      60,    19,   162,   163,     0,   708,   709,   710,     0,     0,
      54,    55,     0,     0,     0,     0,   711,     0,    56,     0,
     712,   151,   152,     0,     0,     0,     0,     0,     0,    57,
       0,   153,    58,     0,   154,   738,     0,     0,    59,     0,
     155,     0,   156,     0,     0,     0,     5,     0,     0,    60,
      19,   713,   714,     0,   158,   159,   160,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,    56,     0,   161,
     151,   152,     0,     0,     0,     0,     0,     0,    57,     0,
     153,    58,     0,   154,     0,     0,     0,    59,     0,   155,
       0,   156,     0,     0,     0,     5,     0,     0,    60,    19,
     162,   163,     0,   158,   159,   160,     0,     0,    54,    55,
       5,     0,     0,     0,     0,   114,    56,     0,   161,     0,
       0,     0,     0,    54,    55,     8,     9,    57,     0,     0,
      58,    56,     0,    85,     0,     0,    59,     0,     0,     0,
       0,    11,    57,     0,     0,    58,     0,    60,    19,   162,
     163,    59,    14,     5,     0,     0,     0,    15,     0,    16,
       0,   115,    60,    19,     0,     0,    54,    55,     8,     9,
       0,     0,     0,     0,    56,     0,    85,     0,     0,     0,
       0,     0,     0,     0,    11,    57,     0,     0,    58,     0,
       0,     0,     0,     0,    59,    14,     0,     0,     0,     0,
      15,     0,    16,     0,    17,   128,   125,     5,     0,   482,
       7,     0,     0,     0,     0,     0,     0,   483,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,    56,     0,
       0,   484,     0,     0,     0,   485,     0,     0,     0,    57,
       5,     0,    58,     0,     0,     0,    13,   486,    59,     0,
       0,   487,     0,    54,    55,     8,     9,     0,     0,    60,
      19,    56,     0,    85,     0,     0,     0,     0,     0,     0,
       0,    11,    57,     0,     0,    58,     0,     0,     0,     0,
       0,    59,    14,     0,     0,     0,     0,    15,     0,    16,
       0,     0,    60,   125,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,   408,     0,     0,     0,   357,   332,     0,     0,     0,
     358,     0,   863,   864,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,     0,     0,     0,     0,   357,   332,     0,     0,     0,
     358,     0,   847,   848,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,   513,     0,     0,    64,    65,   354,   355,
     356,     0,     0,   514,     0,   357,   332,     0,     0,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
     626,     0,     0,    64,    65,   354,   355,   356,     0,     0,
     627,     0,   357,   332,     0,     0,     0,   358,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,   851,     0,     0,
      64,    65,   354,   355,   356,     0,     0,   852,     0,   357,
     332,     0,     0,     0,   358,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,   361,     0,     0,    64,    65,   354,
     355,   356,     0,     0,     0,     0,   357,   332,     0,     0,
       0,   358,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,   363,     0,     0,    64,    65,   354,   355,   356,     0,
       0,     0,     0,   357,   332,     0,     0,     0,   358,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,     0,     0,
       0,    64,    65,   354,   355,   356,   373,     0,     0,     0,
     357,   332,     0,     0,     0,   358,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,   375,     0,     0,     0,   357,   332,     0,
       0,     0,   358,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,     0,     0,     0,    64,    65,   354,   355,   356,
     378,     0,     0,     0,   357,   332,     0,     0,     0,   358,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,     0,
       0,     0,    64,    65,   354,   355,   356,   408,     0,     0,
       0,   357,   332,     0,     0,     0,   358,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,     0,     0,     0,    64,
      65,   354,   355,   356,     0,     0,   517,     0,   357,   332,
       0,     0,     0,   358,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,     0,     0,     0,     0,   357,   332,     0,   590,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
     599,     0,     0,    64,    65,   354,   355,   356,     0,     0,
       0,     0,   357,   332,     0,     0,     0,   358,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,     0,     0,     0,
      64,    65,   354,   355,   356,   623,     0,     0,     0,   357,
     332,     0,     0,     0,   358,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,   624,     0,     0,     0,   357,   332,     0,     0,
       0,   358,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,     0,     0,     0,    64,    65,   354,   355,   356,     0,
       0,     0,     0,   357,   332,     0,   629,     0,   358,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,   677,     0,
       0,    64,    65,   354,   355,   356,     0,     0,     0,     0,
     357,   332,     0,     0,     0,   358,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,   732,     0,     0,     0,   357,   332,     0,
       0,     0,   358,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,     0,     0,     0,    64,    65,   354,   355,   356,
     733,     0,     0,     0,   357,   332,     0,     0,     0,   358,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,     0,
       0,     0,    64,    65,   354,   355,   356,   734,     0,     0,
       0,   357,   332,     0,     0,     0,   358,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,     0,     0,     0,    64,
      65,   354,   355,   356,     0,     0,   790,     0,   357,   332,
       0,     0,     0,   358,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,     0,   353,     0,     0,     0,    64,    65,   354,   355,
     356,   802,     0,     0,     0,   357,   332,     0,     0,     0,
     358,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,     0,   353,
       0,     0,     0,    64,    65,   354,   355,   356,     0,     0,
     855,     0,   357,   332,     0,     0,     0,   358,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   353,   879,     0,     0,
      64,    65,   354,   355,   356,     0,     0,     0,     0,   357,
     332,     0,     0,     0,   358,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,     0,   353,     0,     0,     0,    64,    65,   354,
     355,   356,     0,     0,     0,  -205,   357,   332,     0,     0,
       0,   358,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,     0,
     353,     0,     0,     0,    64,    65,   354,   355,   356,     0,
       0,     0,  -206,   357,   332,     0,     0,     0,   358,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,     0,   353,     0,     0,
       0,    64,    65,   354,   355,   356,     0,     0,     0,     0,
     357,   332,     0,     0,     0,   358,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   766,   767,
     768,   769,   770,     0,   771,     0,     0,     0,    64,    65,
     772,   773,   774,     0,     0,     0,     0,   775,   332,     0,
       0,     0,   776,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,     0,     0,     0,    64,    65,   354,   355,   356,
       0,     0,     0,     0,     0,   332,     0,     0,     0,   358,
     336,   337,   338,   339,     0,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,     0,   353,     0,
       0,     0,    64,    65,   354,   355,   356,     0,     0,     0,
       0,     0,   332,   336,   337,   338,   358,     0,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
       0,   353,     0,     0,     0,    64,    65,   354,   355,   356,
       0,     0,     0,     0,     0,   332,   336,   337,   338,   358,
       0,     0,     0,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,     0,   353,     0,     0,     0,    64,    65,
     354,   355,   356,     0,     0,     0,     0,     0,   332,   338,
       0,     0,   358,     0,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,     0,   353,     0,     0,     0,     0,
      65,     0,   355,   356,     0,     0,     0,     0,     0,   332,
     338,     0,     0,   358,     0,   343,   344,   345,   346,   347,
     348,   349,     0,   351,   352,     0,   353,     0,     0,     0,
       0,    65,     0,   355,   356,     0,     0,     0,     0,     0,
     332,   338,     0,     0,   358,     0,   343,   344,   345,   346,
     347,   348,   349,     0,   351,     0,     0,   353,     0,     0,
       0,     0,    65,     0,   355,   356,     0,     0,     0,     0,
       0,   332,   338,     0,     0,   358,     0,   343,   344,   345,
     346,   347,   348,   349,     0,     0,     0,     0,   353,     0,
       0,     0,     0,    65,     0,   355,   356,     0,     0,     0,
       0,     0,   332,     0,     0,     0,   358
};

static const yytype_int16 yycheck[] =
{
       7,   154,   100,     3,    33,     3,    13,    77,   661,   168,
      69,    22,   290,   286,   315,   736,   661,   661,     3,   661,
     548,   105,   315,   791,    45,    52,    52,    52,   623,    53,
      46,    61,    75,    47,    41,    56,   111,    61,   143,    47,
      45,    47,    56,   571,   119,    61,   121,    70,    33,    46,
      56,    56,    75,    61,    53,    46,    99,    56,    53,   140,
      67,    56,    69,    52,    71,   108,    73,    97,    75,    76,
      77,    78,    79,    97,    81,    82,    83,    46,    75,   674,
     103,    97,    71,    72,    75,    96,   113,   113,   113,    97,
      79,    98,   393,   100,   862,    80,    46,   104,    47,    84,
     393,    90,   177,   404,    93,    47,    60,    48,    49,     0,
      99,   404,    61,    47,    47,   883,   123,    58,    47,    61,
     127,   110,   111,   844,    87,    88,    52,    61,    61,   136,
     137,    94,    61,     7,   141,   142,   143,    71,   111,    13,
     224,    52,    61,     9,    47,    11,    44,   154,    97,    15,
      16,    49,    71,    47,    52,    97,    90,    80,    61,   166,
      58,    84,    56,    97,    97,   324,   444,    41,    97,    46,
      36,    90,   700,    44,   181,    47,    80,    60,    97,   832,
      84,    85,    59,    60,    56,    72,   193,   832,   832,    47,
     832,    46,    79,    67,    97,    69,    46,   101,    56,    73,
      52,    75,    76,    77,    78,    79,    93,    81,    82,    83,
      52,   292,    99,    60,   295,    60,     3,   298,   299,    71,
      72,   302,   303,   110,   111,    47,   331,    79,    60,    58,
     104,    52,    52,    56,    56,    22,   102,    53,    90,    60,
      60,    93,    71,    72,    46,   518,   524,    99,    58,   123,
      79,   356,    44,   127,   532,   533,    48,    49,   110,   111,
      52,    90,   136,   137,    93,    59,    58,   141,   142,    44,
      99,    37,    38,    39,   140,    48,    49,    52,    44,   286,
     154,   110,    59,    49,    71,    52,    52,    74,    53,    76,
      77,   366,    58,    80,    50,    51,   597,    84,   373,    56,
     375,    59,   168,   378,    59,    60,    46,   181,    48,    49,
      44,    59,    60,   100,    59,   315,    46,   315,    52,   193,
      60,   328,    46,   382,   331,    50,    51,   334,   335,    58,
     315,    56,    61,    44,    50,    51,    53,    48,    49,    53,
      56,   530,   531,    72,    73,    74,    50,    58,   507,   356,
       3,    44,    81,    50,    51,    48,    49,    52,    46,    56,
      89,    53,   369,    53,    53,   394,    60,   442,    97,    22,
      52,   100,    71,    72,    46,   382,   105,    46,   107,    46,
      79,   659,   111,   390,   391,   396,    52,    52,    59,    47,
      60,    90,   399,   393,    93,   393,    59,   404,    52,    46,
      99,    52,    52,    59,   404,   412,   404,    53,   393,   394,
      47,   110,   111,    99,    46,    60,    60,    72,    71,   404,
      53,    74,    53,    76,    77,   454,   292,    80,    58,   295,
      53,    84,   298,   299,    60,    60,   302,   303,   445,    52,
      60,    44,    53,    73,    74,    48,    49,   100,    46,    52,
      59,    81,   459,   558,   328,    58,    59,    53,   324,    89,
     334,    75,    59,   568,   562,    60,    71,    72,    46,   454,
     100,   478,   479,    52,    79,   105,    52,   107,    60,    52,
     465,   111,    52,    52,   491,    90,   471,    46,    93,    46,
      71,    72,    58,    78,    99,   369,    60,    53,    79,   286,
      60,    59,   155,    53,    59,   110,   111,     3,   382,    90,
      91,   518,    93,    53,    47,    46,   390,   391,    99,    58,
     625,   596,    52,    55,   311,   399,    22,    52,   315,   110,
     111,    60,    60,   540,    60,   605,    60,    53,   412,   614,
     615,   616,    50,    60,    55,    60,    60,    60,    52,    56,
      53,   558,   657,    53,    56,   562,    46,    56,    53,   718,
      52,   568,   721,   154,    53,    53,   573,   637,   369,    60,
      55,   445,   579,    60,    71,    72,    60,   313,    74,   537,
      76,    77,    79,    30,    80,   459,   471,   783,    84,   574,
     575,   576,   881,    90,   778,   675,    93,   597,   573,   583,
     585,   583,    99,   620,   478,   479,   393,   844,   798,   396,
     315,     3,   547,   110,   597,   335,   623,   404,   625,    -1,
      -1,   632,    -1,    -1,    -1,    -1,   492,    -1,   781,    -1,
      22,    -1,    -1,   286,    -1,   620,    -1,    -1,   623,    -1,
      -1,   507,    -1,    -1,    -1,    -1,   751,    -1,    -1,    -1,
     657,    -1,    -1,    -1,   661,    -1,    -1,    -1,   311,   155,
      -1,   661,   315,    -1,    -1,    -1,   540,   674,   675,   774,
      -1,    -1,   683,    -1,   681,   541,   661,    -1,    -1,    71,
     687,    -1,    74,    -1,    76,    77,    -1,    -1,    80,   674,
      -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,    -1,   573,
      -1,    -1,    -1,    -1,    -1,   579,    -1,   360,   100,   716,
      -1,    -1,   697,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   730,   753,   732,   733,   734,    -1,   736,
      -1,   518,   837,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     393,    -1,   749,   396,   751,    47,    -1,    -1,   535,    -1,
      -1,   404,    -1,    -1,   829,    -1,    58,    -1,    60,    61,
      -1,    -1,    -1,   155,    -1,   870,    68,   774,   753,    71,
      72,    73,    74,    -1,    -1,   562,    -1,    79,    -1,    81,
     787,    -1,    -1,   790,    86,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    97,   583,    99,   100,    -1,
      -1,    -1,   104,   105,    -1,   107,    -1,   681,   110,   111,
     597,    -1,    -1,   687,    -1,   311,    -1,    -1,   605,   315,
      -1,    -1,    -1,    -1,    -1,   832,    -1,    -1,    -1,    -1,
     837,    -1,   832,    -1,    -1,    -1,   623,   844,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   632,    -1,   832,    -1,    -1,
     637,    -1,   718,   838,     0,   721,   730,    -1,   732,   733,
     734,    -1,    -1,   870,   360,   518,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   661,   749,    -1,    -1,    -1,    -1,
     865,    -1,   535,   890,    -1,    -1,    -1,   674,   675,    -1,
      -1,    -1,    -1,    -1,   286,    -1,   683,   393,    -1,    -1,
     396,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,   562,
      -1,    -1,    58,    -1,    60,    61,   790,    -1,    -1,   311,
      -1,    -1,    -1,   315,    -1,    58,    -1,    73,    74,    -1,
     583,    -1,    -1,    -1,    -1,    81,    69,    -1,    -1,    -1,
      73,    74,    -1,    89,   597,    -1,    92,    -1,    81,   736,
      -1,    97,   605,    -1,   100,    -1,    89,    -1,    -1,   105,
      -1,   107,    -1,   109,   110,   111,    -1,   100,   360,    -1,
     623,    -1,   105,    -1,   107,    -1,   109,   110,   111,   632,
      -1,    -1,    -1,    -1,   637,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    61,    -1,    -1,
      -1,   393,    -1,    -1,   396,    -1,    -1,    -1,   661,    73,
      74,    -1,   404,    99,    -1,   101,   890,    81,   104,    -1,
     106,   674,   675,    -1,   110,    89,    -1,    -1,    -1,    -1,
     683,    -1,    -1,    97,   120,    -1,   100,    -1,    -1,   535,
      -1,   105,    -1,   107,    -1,   832,    -1,   111,    -1,    -1,
      -1,    -1,    -1,   706,    -1,    -1,    -1,   844,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   151,   152,   153,   154,   155,
     156,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,   597,    -1,    63,    -1,    -1,    66,    67,    68,   605,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,   778,   518,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    -1,   632,    -1,   791,    99,
     100,   637,    -1,   535,    -1,   105,    -1,   107,    -1,   109,
     110,   111,   112,   113,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,   661,    -1,    44,    -1,    47,
     562,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,   832,
      58,    58,    60,    61,    -1,    62,    -1,   683,    -1,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,   597,    -1,    -1,    86,    -1,
     706,    89,    90,   605,    -1,    93,    -1,    -1,    -1,    97,
      98,    99,   100,    -1,   102,    -1,    -1,   105,    -1,   107,
      -1,    -1,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,
     632,    -1,    -1,   329,    -1,   637,    -1,    -1,    -1,    -1,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   661,
      -1,   357,   358,    -1,   360,    -1,    -1,    -1,    -1,    -1,
      -1,   367,   778,    -1,    -1,   371,    -1,    -1,    -1,    -1,
      -1,   683,    -1,    -1,   380,   791,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    46,    -1,   706,    -1,    -1,    -1,    52,    -1,
      54,   407,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,
      -1,    -1,    66,    67,    68,    -1,   832,    71,    72,    73,
      74,    -1,    -1,    77,    -1,    79,    -1,    81,   434,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    47,
      -1,   105,    -1,   107,    -1,    -1,   110,   111,   112,   113,
      58,    -1,    60,    61,    -1,    -1,   778,    -1,    -1,    -1,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,   791,
     486,    79,    -1,    81,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    97,
      -1,    99,   100,    -1,    -1,    -1,    -1,   105,   514,   107,
      -1,   517,   110,   111,    -1,    -1,    -1,    -1,    -1,    -1,
     832,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,   539,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    52,   548,    54,    -1,   551,    -1,    58,   554,    -1,
      -1,   557,    -1,   559,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    73,    74,    -1,   571,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,   105,    -1,   107,    -1,    -1,   110,
     111,   112,   113,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    46,    47,    -1,    -1,
      -1,   627,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,   662,   663,   664,    -1,
      90,    47,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    58,    -1,    -1,    61,    -1,    -1,    -1,    -1,
     110,   111,   112,   113,    -1,    -1,    -1,    73,    74,    58,
      -1,    -1,   698,    -1,   700,    81,   702,   703,   704,    -1,
     706,   707,    -1,    89,    73,    74,    -1,    -1,    -1,    -1,
      -1,    97,    81,    -1,   100,    -1,    -1,    -1,    -1,   105,
      89,   107,    -1,   109,   110,   111,    -1,    -1,    -1,    -1,
      -1,   100,    -1,    -1,    -1,   741,   105,    -1,   107,    -1,
     109,   110,   111,    -1,    -1,    -1,    -1,    -1,   754,   755,
     756,   757,   758,   759,   760,   761,   762,   763,   764,   765,
     766,   767,   768,   769,   770,   771,   772,    -1,    70,   775,
     776,    -1,   778,    75,    76,   781,    -1,    -1,    80,    -1,
      -1,    83,    84,    85,    -1,   791,    -1,    33,    34,    -1,
      -1,    93,   798,    95,    96,   801,    -1,    43,    -1,   101,
      46,    47,    -1,    -1,   106,    -1,    52,    -1,    54,    -1,
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
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    43,    93,    45,    46,    -1,    -1,    -1,
      99,    -1,    52,    -1,    54,    -1,    56,    -1,    58,    -1,
      -1,   110,   111,   112,   113,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    43,    93,    -1,    46,    47,    -1,    -1,    99,
      -1,    52,    -1,    54,    -1,    56,    -1,    58,    -1,    -1,
     110,   111,   112,   113,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    93,    43,    -1,    -1,    46,    -1,    99,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,   110,
     111,   112,   113,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    43,    93,    -1,    46,    -1,    -1,    -1,    99,
      -1,    52,    53,    54,    -1,    56,    -1,    58,    -1,    -1,
     110,   111,   112,   113,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    93,    43,    -1,    -1,    46,    -1,    99,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,   110,
     111,   112,   113,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    93,    43,    -1,    -1,    46,    -1,    99,
      -1,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
     110,   111,   112,   113,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    43,    93,    -1,    46,    -1,    -1,    -1,
      99,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      60,   110,   111,   112,   113,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    43,    93,    -1,    -1,    47,    -1,    -1,    99,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
     110,   111,   112,   113,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,
      81,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    43,    93,    -1,    46,    47,    -1,    -1,    99,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,
     111,   112,   113,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      58,    -1,    -1,    -1,    -1,    63,    79,    -1,    81,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    90,    -1,    -1,
      93,    79,    -1,    81,    -1,    -1,    99,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,   110,   111,   112,
     113,    99,   100,    58,    -1,    -1,    -1,   105,    -1,   107,
      -1,   109,   110,   111,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,   109,   110,   111,    58,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    -1,    90,
      58,    -1,    93,    -1,    -1,    -1,    97,    98,    99,    -1,
      -1,   102,    -1,    71,    72,    73,    74,    -1,    -1,   110,
     111,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,
      -1,    -1,   110,   111,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    -1,    64,    65,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    -1,    64,    65,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    45,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    55,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    45,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
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
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    -1,    57,    58,
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
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    60,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    45,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    53,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    56,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    26,    27,    28,    62,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    26,    27,    28,    62,
      -1,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,
      -1,    -1,    62,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      28,    -1,    -1,    62,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    42,    -1,    44,    -1,    -1,    -1,
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
     174,   180,   183,   185,   188,   190,   191,   192,   193,   194,
     195,   196,   204,   205,   206,   209,   210,   215,   220,   221,
     223,   250,   252,   255,    71,    72,    79,    90,    93,    99,
     110,   111,   123,   124,    48,    49,   268,    46,   268,    46,
     124,   268,   268,    70,    75,    76,    80,    83,    84,    85,
      93,    95,    96,   101,   106,    81,   129,   188,    60,   111,
      52,    60,   145,    60,   145,   127,   128,   232,    52,    44,
     268,    44,   124,    60,    44,    52,    52,   113,   124,   222,
      52,   113,   222,   130,    63,   109,   123,   188,   200,   201,
      52,   113,   124,   188,   124,   111,   124,   188,   110,   123,
     124,   185,   188,   124,   124,   127,   188,   205,   124,   124,
     124,   188,   205,    52,   127,   134,   135,   136,   148,    46,
      46,    33,    34,    43,    46,    52,    54,    63,    66,    67,
      68,    81,   112,   113,   123,   124,   146,   189,   191,   194,
     256,   257,   258,   265,   266,   123,   265,   201,   265,   197,
     198,   268,   124,   132,   133,   259,   265,   130,   265,    50,
      51,   269,    47,    56,   265,   269,    47,    22,    23,    26,
      27,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   131,    56,   269,   265,   269,
      52,   124,   175,   216,   124,   181,    60,    60,   207,   211,
     124,   124,   139,   153,   197,   124,   124,   256,    87,    88,
      94,   137,    53,    56,    46,   177,   233,   265,   265,   265,
     132,   259,    81,   188,   191,   194,   265,   265,    58,    59,
     123,    52,    58,   261,    53,    56,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    50,    51,    52,    57,    62,   261,
     268,    45,   269,    45,   186,   124,   199,    59,    45,    56,
      45,    56,    53,    53,   124,    53,   130,   200,    53,   134,
      59,   197,    46,   217,   197,   197,   197,   197,   197,    46,
      53,   188,   136,   150,    72,   127,   128,   141,   178,   188,
     240,   250,   251,   252,   234,    47,    47,    53,    53,   124,
     265,   256,   262,   124,   258,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,    50,   256,   265,   265,    63,   109,
     188,   202,   203,   265,    52,    56,   269,   265,   133,   265,
     269,   269,    53,   269,    53,   254,   265,   176,   222,    46,
     182,   208,   212,   140,   154,   213,   124,   124,   127,   141,
     151,   155,   156,   172,   251,   252,   179,   232,   103,   188,
     124,    47,    60,    68,    82,    86,    98,   102,   123,   127,
     141,   146,   191,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   235,   239,   251,   252,   260,   263,   265,    53,
     124,    59,    60,    45,    55,   265,    53,    55,    56,   269,
     134,   124,   232,    60,    52,    47,   124,   218,   219,    46,
      46,    46,    52,    52,    47,   127,   214,    59,    60,    59,
      99,   108,   127,   149,   156,    47,   124,   124,    59,   253,
      60,    52,    60,   265,    52,   123,    58,    44,    52,    59,
     261,   264,   268,    46,   142,   265,   265,   200,    52,    53,
     134,    59,    47,    56,   184,   213,   213,   134,   134,   188,
     142,   265,   124,   268,    47,    46,   253,   254,    60,   265,
      60,   265,    72,   265,   256,   265,   201,   143,    60,    45,
     256,    53,   254,   219,    47,   127,   187,    47,    47,    53,
      53,   124,    60,   157,   191,   192,   195,    71,    90,   127,
     241,   242,    60,    53,    53,    52,    45,    55,    53,    60,
     269,    47,   128,   141,   144,   255,    53,    69,   111,   185,
      60,    46,   269,   269,   269,    59,    59,    75,   126,    47,
     242,   191,   231,    46,   256,   265,    60,    52,   185,    52,
      60,   158,    52,    52,    52,    46,    46,    72,    79,    93,
      99,   110,   111,   125,    78,   236,    53,    45,   256,    60,
     134,   104,   127,   128,   159,   160,   162,   188,   224,   226,
     229,   230,   251,   252,   265,   265,   265,   245,   243,    59,
      59,   231,    33,    34,    43,    47,    52,    54,    66,    67,
      68,    77,    81,   112,   113,   123,   146,   189,   191,   237,
     238,   267,    60,    53,    53,    91,   124,   163,   164,    46,
     188,    47,    53,    53,    53,    47,   127,   246,    47,   244,
     265,    46,   254,   265,   265,   265,   188,   265,   265,    58,
     123,    52,   261,    55,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    44,    50,    51,    52,    57,    62,   261,   268,    60,
      60,    52,    60,   161,   124,   124,   124,   146,   247,   260,
      55,    52,    63,    77,   167,   168,   171,   248,   249,   265,
      60,    53,    53,   124,   256,   232,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,    50,   256,   265,   265,   203,
     265,   259,   158,    60,    60,    60,    60,    52,   124,    63,
      77,   170,   171,   265,    55,    47,   248,    64,    65,   265,
      53,    45,    55,   265,    53,    55,   269,    53,    47,   256,
     127,    53,    56,    64,    65,   247,   265,   265,   265,   265,
      52,    46,    53,    60,   169,   171,   265,   265,   127,    45,
     256,   165,    53,    56,    60,    53,    47,   166,   167,   171,
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
     184,   184,   186,   185,   187,   187,   187,   188,   188,   188,
     188,   188,   189,   189,   190,   190,   191,   192,   193,   193,
     194,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   196,   196,   196,   197,   197,   198,   199,   199,
     200,   200,   200,   200,   201,   201,   201,   202,   202,   202,
     203,   203,   204,   204,   204,   204,   204,   205,   205,   205,
     205,   207,   208,   206,   209,   211,   212,   210,   213,   213,
     214,   216,   215,   217,   215,   218,   218,   219,   220,   221,
     222,   222,   223,   223,   223,   223,   224,   224,   225,   225,
     226,   227,   228,   228,   229,   229,   230,   231,   231,   231,
     231,   231,   231,   231,   231,   233,   232,   234,   234,   235,
     236,   236,   237,   237,   238,   238,   239,   239,   239,   239,
     240,   241,   241,   242,   242,   242,   242,   243,   243,   244,
     245,   245,   246,   247,   247,   248,   249,   249,   250,   251,
     251,   252,   253,   253,   254,   255,   256,   256,   257,   257,
     258,   258,   258,   259,   259,   259,   260,   260,   262,   261,
     263,   263,   263,   263,   264,   264,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   266,   266,
     266,   266,   266,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   268,   268,   269,   269
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
       0,     2,     0,     7,     3,     4,     6,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     4,     4,     4,
       4,     1,     1,     1,     1,     1,     4,     4,     4,     6,
       6,     6,     1,     1,     1,     0,     1,     3,     1,     3,
       1,     1,     1,     1,     0,     1,     3,     1,     1,     1,
       1,     3,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     0,     0,     9,     7,     0,     0,     9,     0,     2,
       4,     0,     7,     0,     8,     1,     3,     3,     4,     4,
       1,     3,     4,     4,     4,     4,     1,     4,     5,     8,
       1,     2,     2,     3,     5,     7,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     5,     0,     2,     7,
       0,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       6,     1,     2,     5,     5,     7,     6,     0,     2,     5,
       0,     2,     3,     1,     4,     5,     1,     2,     7,     5,
       4,     7,     0,     2,     1,     2,     0,     1,     1,     3,
       1,     3,     1,     0,     1,     3,     1,     2,     0,     3,
       1,     1,     2,     2,     3,     5,     1,     1,     1,     1,
       1,     1,     2,     4,     6,     3,     3,     3,     2,     2,
       2,     2,     2,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     5,     1,     0,     7,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     3,     2,     2,     2,     2,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     5,     7,     4,     4,     4,     1,     1,     1,     1
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
#line 2828 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2834 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2840 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2846 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2852 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2858 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2864 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2870 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2876 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2882 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2888 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2894 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2900 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2906 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2912 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2918 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2924 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2930 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2936 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2942 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2948 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2954 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2960 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2966 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2972 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2978 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2984 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2990 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2996 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 3002 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 3008 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 3014 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 3020 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3026 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3032 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3038 "p4parser.tab.c"
    break;

  case 40:
#line 312 "p4parser.y"
        {}
#line 3044 "p4parser.tab.c"
    break;

  case 41:
#line 316 "p4parser.y"
        {}
#line 3050 "p4parser.tab.c"
    break;

  case 42:
#line 320 "p4parser.y"
              {}
#line 3056 "p4parser.tab.c"
    break;

  case 43:
#line 322 "p4parser.y"
        {}
#line 3062 "p4parser.tab.c"
    break;

  case 44:
#line 324 "p4parser.y"
        {}
#line 3068 "p4parser.tab.c"
    break;

  case 45:
#line 328 "p4parser.y"
                       {}
#line 3074 "p4parser.tab.c"
    break;

  case 46:
#line 329 "p4parser.y"
                       {}
#line 3080 "p4parser.tab.c"
    break;

  case 47:
#line 330 "p4parser.y"
                       {}
#line 3086 "p4parser.tab.c"
    break;

  case 48:
#line 331 "p4parser.y"
                       {}
#line 3092 "p4parser.tab.c"
    break;

  case 49:
#line 332 "p4parser.y"
                       {}
#line 3098 "p4parser.tab.c"
    break;

  case 50:
#line 333 "p4parser.y"
                       {}
#line 3104 "p4parser.tab.c"
    break;

  case 51:
#line 334 "p4parser.y"
                       {}
#line 3110 "p4parser.tab.c"
    break;

  case 52:
#line 335 "p4parser.y"
                       {}
#line 3116 "p4parser.tab.c"
    break;

  case 53:
#line 336 "p4parser.y"
                       {}
#line 3122 "p4parser.tab.c"
    break;

  case 54:
#line 337 "p4parser.y"
                       {}
#line 3128 "p4parser.tab.c"
    break;

  case 55:
#line 338 "p4parser.y"
                       {}
#line 3134 "p4parser.tab.c"
    break;

  case 56:
#line 339 "p4parser.y"
                       {}
#line 3140 "p4parser.tab.c"
    break;

  case 57:
#line 340 "p4parser.y"
                       {}
#line 3146 "p4parser.tab.c"
    break;

  case 58:
#line 341 "p4parser.y"
                       {}
#line 3152 "p4parser.tab.c"
    break;

  case 59:
#line 342 "p4parser.y"
                       {}
#line 3158 "p4parser.tab.c"
    break;

  case 60:
#line 343 "p4parser.y"
                       {}
#line 3164 "p4parser.tab.c"
    break;

  case 61:
#line 344 "p4parser.y"
                       {}
#line 3170 "p4parser.tab.c"
    break;

  case 62:
#line 345 "p4parser.y"
                       {}
#line 3176 "p4parser.tab.c"
    break;

  case 63:
#line 346 "p4parser.y"
                       {}
#line 3182 "p4parser.tab.c"
    break;

  case 64:
#line 347 "p4parser.y"
                       {}
#line 3188 "p4parser.tab.c"
    break;

  case 65:
#line 348 "p4parser.y"
                       {}
#line 3194 "p4parser.tab.c"
    break;

  case 66:
#line 349 "p4parser.y"
                       {}
#line 3200 "p4parser.tab.c"
    break;

  case 67:
#line 350 "p4parser.y"
                       {}
#line 3206 "p4parser.tab.c"
    break;

  case 68:
#line 351 "p4parser.y"
                       {}
#line 3212 "p4parser.tab.c"
    break;

  case 69:
#line 352 "p4parser.y"
                       {}
#line 3218 "p4parser.tab.c"
    break;

  case 70:
#line 353 "p4parser.y"
                       {}
#line 3224 "p4parser.tab.c"
    break;

  case 71:
#line 354 "p4parser.y"
                       {}
#line 3230 "p4parser.tab.c"
    break;

  case 72:
#line 355 "p4parser.y"
                       {}
#line 3236 "p4parser.tab.c"
    break;

  case 73:
#line 356 "p4parser.y"
                       {}
#line 3242 "p4parser.tab.c"
    break;

  case 74:
#line 357 "p4parser.y"
                       {}
#line 3248 "p4parser.tab.c"
    break;

  case 75:
#line 358 "p4parser.y"
                       {}
#line 3254 "p4parser.tab.c"
    break;

  case 76:
#line 359 "p4parser.y"
                       {}
#line 3260 "p4parser.tab.c"
    break;

  case 77:
#line 360 "p4parser.y"
                       {}
#line 3266 "p4parser.tab.c"
    break;

  case 78:
#line 361 "p4parser.y"
                       {}
#line 3272 "p4parser.tab.c"
    break;

  case 79:
#line 362 "p4parser.y"
                       {}
#line 3278 "p4parser.tab.c"
    break;

  case 80:
#line 363 "p4parser.y"
                       {}
#line 3284 "p4parser.tab.c"
    break;

  case 81:
#line 364 "p4parser.y"
                       {}
#line 3290 "p4parser.tab.c"
    break;

  case 82:
#line 365 "p4parser.y"
                       {}
#line 3296 "p4parser.tab.c"
    break;

  case 83:
#line 366 "p4parser.y"
                       {}
#line 3302 "p4parser.tab.c"
    break;

  case 84:
#line 367 "p4parser.y"
                       {}
#line 3308 "p4parser.tab.c"
    break;

  case 85:
#line 368 "p4parser.y"
                       {}
#line 3314 "p4parser.tab.c"
    break;

  case 86:
#line 369 "p4parser.y"
                       {}
#line 3320 "p4parser.tab.c"
    break;

  case 87:
#line 370 "p4parser.y"
                       {}
#line 3326 "p4parser.tab.c"
    break;

  case 88:
#line 371 "p4parser.y"
                       {}
#line 3332 "p4parser.tab.c"
    break;

  case 89:
#line 372 "p4parser.y"
                       {}
#line 3338 "p4parser.tab.c"
    break;

  case 90:
#line 373 "p4parser.y"
                            {}
#line 3344 "p4parser.tab.c"
    break;

  case 91:
#line 375 "p4parser.y"
                       {}
#line 3350 "p4parser.tab.c"
    break;

  case 92:
#line 376 "p4parser.y"
                       {}
#line 3356 "p4parser.tab.c"
    break;

  case 93:
#line 377 "p4parser.y"
                       {}
#line 3362 "p4parser.tab.c"
    break;

  case 94:
#line 378 "p4parser.y"
                       {}
#line 3368 "p4parser.tab.c"
    break;

  case 95:
#line 379 "p4parser.y"
                       {}
#line 3374 "p4parser.tab.c"
    break;

  case 96:
#line 380 "p4parser.y"
                       {}
#line 3380 "p4parser.tab.c"
    break;

  case 97:
#line 381 "p4parser.y"
                       {}
#line 3386 "p4parser.tab.c"
    break;

  case 98:
#line 382 "p4parser.y"
                       {}
#line 3392 "p4parser.tab.c"
    break;

  case 99:
#line 383 "p4parser.y"
                       {}
#line 3398 "p4parser.tab.c"
    break;

  case 100:
#line 384 "p4parser.y"
                       {}
#line 3404 "p4parser.tab.c"
    break;

  case 101:
#line 385 "p4parser.y"
                       {}
#line 3410 "p4parser.tab.c"
    break;

  case 102:
#line 386 "p4parser.y"
                       {}
#line 3416 "p4parser.tab.c"
    break;

  case 103:
#line 387 "p4parser.y"
                       {}
#line 3422 "p4parser.tab.c"
    break;

  case 104:
#line 388 "p4parser.y"
                       {}
#line 3428 "p4parser.tab.c"
    break;

  case 105:
#line 389 "p4parser.y"
                       {}
#line 3434 "p4parser.tab.c"
    break;

  case 106:
#line 390 "p4parser.y"
                       {}
#line 3440 "p4parser.tab.c"
    break;

  case 108:
#line 392 "p4parser.y"
                       {}
#line 3446 "p4parser.tab.c"
    break;

  case 109:
#line 393 "p4parser.y"
                       {}
#line 3452 "p4parser.tab.c"
    break;

  case 110:
#line 394 "p4parser.y"
                       {}
#line 3458 "p4parser.tab.c"
    break;

  case 111:
#line 395 "p4parser.y"
                       {}
#line 3464 "p4parser.tab.c"
    break;

  case 112:
#line 396 "p4parser.y"
                       {}
#line 3470 "p4parser.tab.c"
    break;

  case 113:
#line 397 "p4parser.y"
                       {}
#line 3476 "p4parser.tab.c"
    break;

  case 114:
#line 398 "p4parser.y"
                       {}
#line 3482 "p4parser.tab.c"
    break;

  case 115:
#line 399 "p4parser.y"
                       {}
#line 3488 "p4parser.tab.c"
    break;

  case 116:
#line 400 "p4parser.y"
                       {}
#line 3494 "p4parser.tab.c"
    break;

  case 117:
#line 401 "p4parser.y"
                       {}
#line 3500 "p4parser.tab.c"
    break;

  case 118:
#line 402 "p4parser.y"
                       {}
#line 3506 "p4parser.tab.c"
    break;

  case 119:
#line 403 "p4parser.y"
                       {}
#line 3512 "p4parser.tab.c"
    break;

  case 120:
#line 404 "p4parser.y"
                       {}
#line 3518 "p4parser.tab.c"
    break;

  case 121:
#line 405 "p4parser.y"
                       {}
#line 3524 "p4parser.tab.c"
    break;

  case 122:
#line 406 "p4parser.y"
                       {}
#line 3530 "p4parser.tab.c"
    break;

  case 123:
#line 407 "p4parser.y"
                       {}
#line 3536 "p4parser.tab.c"
    break;

  case 124:
#line 408 "p4parser.y"
                       {}
#line 3542 "p4parser.tab.c"
    break;

  case 125:
#line 409 "p4parser.y"
                       {}
#line 3548 "p4parser.tab.c"
    break;

  case 126:
#line 410 "p4parser.y"
                       {}
#line 3554 "p4parser.tab.c"
    break;

  case 127:
#line 411 "p4parser.y"
                       {}
#line 3560 "p4parser.tab.c"
    break;

  case 128:
#line 412 "p4parser.y"
                       {}
#line 3566 "p4parser.tab.c"
    break;

  case 129:
#line 413 "p4parser.y"
                       {}
#line 3572 "p4parser.tab.c"
    break;

  case 130:
#line 414 "p4parser.y"
                       {}
#line 3578 "p4parser.tab.c"
    break;

  case 131:
#line 418 "p4parser.y"
                                      {}
#line 3584 "p4parser.tab.c"
    break;

  case 132:
#line 419 "p4parser.y"
                                        {}
#line 3590 "p4parser.tab.c"
    break;

  case 133:
#line 423 "p4parser.y"
                                         {}
#line 3596 "p4parser.tab.c"
    break;

  case 134:
#line 427 "p4parser.y"
                                      {}
#line 3602 "p4parser.tab.c"
    break;

  case 135:
#line 428 "p4parser.y"
                                      {}
#line 3608 "p4parser.tab.c"
    break;

  case 136:
#line 432 "p4parser.y"
                                          {}
#line 3614 "p4parser.tab.c"
    break;

  case 137:
#line 433 "p4parser.y"
                                            {}
#line 3620 "p4parser.tab.c"
    break;

  case 138:
#line 437 "p4parser.y"
                                            {}
#line 3626 "p4parser.tab.c"
    break;

  case 139:
#line 438 "p4parser.y"
                                                              {}
#line 3632 "p4parser.tab.c"
    break;

  case 140:
#line 442 "p4parser.y"
                 {}
#line 3638 "p4parser.tab.c"
    break;

  case 141:
#line 443 "p4parser.y"
                   {}
#line 3644 "p4parser.tab.c"
    break;

  case 142:
#line 444 "p4parser.y"
                   {}
#line 3650 "p4parser.tab.c"
    break;

  case 143:
#line 445 "p4parser.y"
                   {}
#line 3656 "p4parser.tab.c"
    break;

  case 144:
#line 449 "p4parser.y"
                                  {}
#line 3662 "p4parser.tab.c"
    break;

  case 145:
#line 450 "p4parser.y"
                        {}
#line 3668 "p4parser.tab.c"
    break;

  case 146:
#line 451 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3677 "p4parser.tab.c"
    break;

  case 147:
#line 459 "p4parser.y"
                     {}
#line 3683 "p4parser.tab.c"
    break;

  case 148:
#line 461 "p4parser.y"
                     {}
#line 3689 "p4parser.tab.c"
    break;

  case 149:
#line 464 "p4parser.y"
                     {}
#line 3695 "p4parser.tab.c"
    break;

  case 150:
#line 467 "p4parser.y"
                     {}
#line 3701 "p4parser.tab.c"
    break;

  case 151:
#line 473 "p4parser.y"
                               {}
#line 3707 "p4parser.tab.c"
    break;

  case 152:
#line 477 "p4parser.y"
                                     {}
#line 3713 "p4parser.tab.c"
    break;

  case 153:
#line 478 "p4parser.y"
                                     {}
#line 3719 "p4parser.tab.c"
    break;

  case 154:
#line 482 "p4parser.y"
                               {}
#line 3725 "p4parser.tab.c"
    break;

  case 155:
#line 483 "p4parser.y"
                               {}
#line 3731 "p4parser.tab.c"
    break;

  case 156:
#line 487 "p4parser.y"
                           {}
#line 3737 "p4parser.tab.c"
    break;

  case 157:
#line 488 "p4parser.y"
                                     {}
#line 3743 "p4parser.tab.c"
    break;

  case 158:
#line 492 "p4parser.y"
                             {}
#line 3749 "p4parser.tab.c"
    break;

  case 159:
#line 498 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3755 "p4parser.tab.c"
    break;

  case 160:
#line 499 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3761 "p4parser.tab.c"
    break;

  case 161:
#line 500 "p4parser.y"
                             {}
#line 3767 "p4parser.tab.c"
    break;

  case 162:
#line 505 "p4parser.y"
                                           {}
#line 3773 "p4parser.tab.c"
    break;

  case 163:
#line 506 "p4parser.y"
                                             {}
#line 3779 "p4parser.tab.c"
    break;

  case 164:
#line 510 "p4parser.y"
                                    {}
#line 3785 "p4parser.tab.c"
    break;

  case 165:
#line 511 "p4parser.y"
                                      {}
#line 3791 "p4parser.tab.c"
    break;

  case 166:
#line 512 "p4parser.y"
                                      {}
#line 3797 "p4parser.tab.c"
    break;

  case 167:
#line 513 "p4parser.y"
                                      {}
#line 3803 "p4parser.tab.c"
    break;

  case 168:
#line 518 "p4parser.y"
                          {}
#line 3809 "p4parser.tab.c"
    break;

  case 169:
#line 519 "p4parser.y"
                          {}
#line 3815 "p4parser.tab.c"
    break;

  case 170:
#line 520 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3824 "p4parser.tab.c"
    break;

  case 171:
#line 527 "p4parser.y"
                                    {}
#line 3830 "p4parser.tab.c"
    break;

  case 172:
#line 528 "p4parser.y"
                                      {}
#line 3836 "p4parser.tab.c"
    break;

  case 173:
#line 532 "p4parser.y"
                              {}
#line 3842 "p4parser.tab.c"
    break;

  case 174:
#line 534 "p4parser.y"
                                      {}
#line 3848 "p4parser.tab.c"
    break;

  case 175:
#line 538 "p4parser.y"
                                     {}
#line 3854 "p4parser.tab.c"
    break;

  case 176:
#line 539 "p4parser.y"
                                       {}
#line 3860 "p4parser.tab.c"
    break;

  case 177:
#line 543 "p4parser.y"
                                    {}
#line 3866 "p4parser.tab.c"
    break;

  case 178:
#line 544 "p4parser.y"
                                      {}
#line 3872 "p4parser.tab.c"
    break;

  case 179:
#line 545 "p4parser.y"
                                      {}
#line 3878 "p4parser.tab.c"
    break;

  case 180:
#line 546 "p4parser.y"
                                      {}
#line 3884 "p4parser.tab.c"
    break;

  case 181:
#line 547 "p4parser.y"
                                      {}
#line 3890 "p4parser.tab.c"
    break;

  case 182:
#line 548 "p4parser.y"
                                      {}
#line 3896 "p4parser.tab.c"
    break;

  case 183:
#line 549 "p4parser.y"
                                      {}
#line 3902 "p4parser.tab.c"
    break;

  case 184:
#line 553 "p4parser.y"
                           {}
#line 3908 "p4parser.tab.c"
    break;

  case 185:
#line 554 "p4parser.y"
                               {}
#line 3914 "p4parser.tab.c"
    break;

  case 186:
#line 558 "p4parser.y"
                                {}
#line 3920 "p4parser.tab.c"
    break;

  case 187:
#line 559 "p4parser.y"
                                  {}
#line 3926 "p4parser.tab.c"
    break;

  case 188:
#line 563 "p4parser.y"
                           {}
#line 3932 "p4parser.tab.c"
    break;

  case 189:
#line 564 "p4parser.y"
                       {}
#line 3938 "p4parser.tab.c"
    break;

  case 190:
#line 569 "p4parser.y"
                              {}
#line 3944 "p4parser.tab.c"
    break;

  case 191:
#line 573 "p4parser.y"
                               {}
#line 3950 "p4parser.tab.c"
    break;

  case 192:
#line 574 "p4parser.y"
                                 {}
#line 3956 "p4parser.tab.c"
    break;

  case 193:
#line 579 "p4parser.y"
      {}
#line 3962 "p4parser.tab.c"
    break;

  case 194:
#line 583 "p4parser.y"
                              {}
#line 3968 "p4parser.tab.c"
    break;

  case 195:
#line 584 "p4parser.y"
                                {}
#line 3974 "p4parser.tab.c"
    break;

  case 196:
#line 589 "p4parser.y"
                                {}
#line 3980 "p4parser.tab.c"
    break;

  case 197:
#line 590 "p4parser.y"
                                                    {}
#line 3986 "p4parser.tab.c"
    break;

  case 198:
#line 594 "p4parser.y"
                           {}
#line 3992 "p4parser.tab.c"
    break;

  case 199:
#line 595 "p4parser.y"
                                                        {}
#line 3998 "p4parser.tab.c"
    break;

  case 200:
#line 600 "p4parser.y"
                                 {}
#line 4004 "p4parser.tab.c"
    break;

  case 201:
#line 601 "p4parser.y"
                                   {}
#line 4010 "p4parser.tab.c"
    break;

  case 202:
#line 602 "p4parser.y"
                                  {}
#line 4016 "p4parser.tab.c"
    break;

  case 203:
#line 603 "p4parser.y"
                                       {}
#line 4022 "p4parser.tab.c"
    break;

  case 204:
#line 607 "p4parser.y"
                                {}
#line 4028 "p4parser.tab.c"
    break;

  case 205:
#line 608 "p4parser.y"
                                 {}
#line 4034 "p4parser.tab.c"
    break;

  case 206:
#line 609 "p4parser.y"
                                   {}
#line 4040 "p4parser.tab.c"
    break;

  case 207:
#line 610 "p4parser.y"
                                  {}
#line 4046 "p4parser.tab.c"
    break;

  case 208:
#line 611 "p4parser.y"
                                       {}
#line 4052 "p4parser.tab.c"
    break;

  case 209:
#line 617 "p4parser.y"
        {}
#line 4058 "p4parser.tab.c"
    break;

  case 210:
#line 620 "p4parser.y"
        {}
#line 4064 "p4parser.tab.c"
    break;

  case 211:
#line 623 "p4parser.y"
        {}
#line 4070 "p4parser.tab.c"
    break;

  case 212:
#line 631 "p4parser.y"
        {}
#line 4076 "p4parser.tab.c"
    break;

  case 213:
#line 636 "p4parser.y"
                     {}
#line 4082 "p4parser.tab.c"
    break;

  case 214:
#line 637 "p4parser.y"
                          {}
#line 4088 "p4parser.tab.c"
    break;

  case 215:
#line 638 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4097 "p4parser.tab.c"
    break;

  case 216:
#line 645 "p4parser.y"
           {}
#line 4103 "p4parser.tab.c"
    break;

  case 217:
#line 646 "p4parser.y"
                                                       {}
#line 4109 "p4parser.tab.c"
    break;

  case 218:
#line 650 "p4parser.y"
                             {}
#line 4115 "p4parser.tab.c"
    break;

  case 219:
#line 651 "p4parser.y"
                               {}
#line 4121 "p4parser.tab.c"
    break;

  case 220:
#line 652 "p4parser.y"
                               {}
#line 4127 "p4parser.tab.c"
    break;

  case 221:
#line 653 "p4parser.y"
                               {}
#line 4133 "p4parser.tab.c"
    break;

  case 222:
#line 654 "p4parser.y"
                               {}
#line 4139 "p4parser.tab.c"
    break;

  case 223:
#line 658 "p4parser.y"
                   {}
#line 4145 "p4parser.tab.c"
    break;

  case 224:
#line 665 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4154 "p4parser.tab.c"
    break;

  case 225:
#line 669 "p4parser.y"
                          {}
#line 4160 "p4parser.tab.c"
    break;

  case 230:
#line 680 "p4parser.y"
                                     {}
#line 4166 "p4parser.tab.c"
    break;

  case 231:
#line 681 "p4parser.y"
                                       {}
#line 4172 "p4parser.tab.c"
    break;

  case 232:
#line 686 "p4parser.y"
                               {}
#line 4178 "p4parser.tab.c"
    break;

  case 233:
#line 687 "p4parser.y"
                                      {}
#line 4184 "p4parser.tab.c"
    break;

  case 234:
#line 691 "p4parser.y"
                                               {}
#line 4190 "p4parser.tab.c"
    break;

  case 235:
#line 692 "p4parser.y"
                                                          {}
#line 4196 "p4parser.tab.c"
    break;

  case 236:
#line 694 "p4parser.y"
                                        {}
#line 4202 "p4parser.tab.c"
    break;

  case 237:
#line 700 "p4parser.y"
                                     {}
#line 4208 "p4parser.tab.c"
    break;

  case 238:
#line 701 "p4parser.y"
                                       {}
#line 4214 "p4parser.tab.c"
    break;

  case 239:
#line 702 "p4parser.y"
                                       {}
#line 4220 "p4parser.tab.c"
    break;

  case 240:
#line 703 "p4parser.y"
                                       {}
#line 4226 "p4parser.tab.c"
    break;

  case 241:
#line 704 "p4parser.y"
                                       {}
#line 4232 "p4parser.tab.c"
    break;

  case 242:
#line 708 "p4parser.y"
                                     {}
#line 4238 "p4parser.tab.c"
    break;

  case 243:
#line 709 "p4parser.y"
                                       {}
#line 4244 "p4parser.tab.c"
    break;

  case 244:
#line 713 "p4parser.y"
                                     {}
#line 4250 "p4parser.tab.c"
    break;

  case 245:
#line 714 "p4parser.y"
                                       {}
#line 4256 "p4parser.tab.c"
    break;

  case 246:
#line 718 "p4parser.y"
                                     {}
#line 4262 "p4parser.tab.c"
    break;

  case 247:
#line 722 "p4parser.y"
                                              {}
#line 4268 "p4parser.tab.c"
    break;

  case 248:
#line 726 "p4parser.y"
                                                    {}
#line 4274 "p4parser.tab.c"
    break;

  case 249:
#line 727 "p4parser.y"
                                                      {}
#line 4280 "p4parser.tab.c"
    break;

  case 250:
#line 731 "p4parser.y"
                                              {}
#line 4286 "p4parser.tab.c"
    break;

  case 251:
#line 735 "p4parser.y"
           {}
#line 4292 "p4parser.tab.c"
    break;

  case 252:
#line 736 "p4parser.y"
             {}
#line 4298 "p4parser.tab.c"
    break;

  case 253:
#line 737 "p4parser.y"
             {}
#line 4304 "p4parser.tab.c"
    break;

  case 254:
#line 738 "p4parser.y"
             {}
#line 4310 "p4parser.tab.c"
    break;

  case 255:
#line 739 "p4parser.y"
             {}
#line 4316 "p4parser.tab.c"
    break;

  case 256:
#line 741 "p4parser.y"
      {}
#line 4322 "p4parser.tab.c"
    break;

  case 257:
#line 743 "p4parser.y"
      {}
#line 4328 "p4parser.tab.c"
    break;

  case 258:
#line 745 "p4parser.y"
      {}
#line 4334 "p4parser.tab.c"
    break;

  case 259:
#line 748 "p4parser.y"
      {}
#line 4340 "p4parser.tab.c"
    break;

  case 260:
#line 750 "p4parser.y"
      {}
#line 4346 "p4parser.tab.c"
    break;

  case 261:
#line 752 "p4parser.y"
      {}
#line 4352 "p4parser.tab.c"
    break;

  case 262:
#line 756 "p4parser.y"
                {}
#line 4358 "p4parser.tab.c"
    break;

  case 263:
#line 757 "p4parser.y"
                  {}
#line 4364 "p4parser.tab.c"
    break;

  case 264:
#line 758 "p4parser.y"
                  {}
#line 4370 "p4parser.tab.c"
    break;

  case 265:
#line 763 "p4parser.y"
                              {}
#line 4376 "p4parser.tab.c"
    break;

  case 266:
#line 764 "p4parser.y"
                                {}
#line 4382 "p4parser.tab.c"
    break;

  case 267:
#line 768 "p4parser.y"
                                      {}
#line 4388 "p4parser.tab.c"
    break;

  case 268:
#line 772 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4400 "p4parser.tab.c"
    break;

  case 269:
#line 779 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4408 "p4parser.tab.c"
    break;

  case 270:
#line 785 "p4parser.y"
                                {}
#line 4414 "p4parser.tab.c"
    break;

  case 271:
#line 786 "p4parser.y"
                                  {}
#line 4420 "p4parser.tab.c"
    break;

  case 272:
#line 788 "p4parser.y"
                                  {}
#line 4426 "p4parser.tab.c"
    break;

  case 273:
#line 789 "p4parser.y"
                                       {}
#line 4432 "p4parser.tab.c"
    break;

  case 274:
#line 793 "p4parser.y"
                                   {}
#line 4438 "p4parser.tab.c"
    break;

  case 275:
#line 794 "p4parser.y"
                                     {}
#line 4444 "p4parser.tab.c"
    break;

  case 276:
#line 795 "p4parser.y"
                                       {}
#line 4450 "p4parser.tab.c"
    break;

  case 277:
#line 799 "p4parser.y"
                                {}
#line 4456 "p4parser.tab.c"
    break;

  case 278:
#line 800 "p4parser.y"
                                  {}
#line 4462 "p4parser.tab.c"
    break;

  case 279:
#line 801 "p4parser.y"
                                       {}
#line 4468 "p4parser.tab.c"
    break;

  case 280:
#line 807 "p4parser.y"
                                       {}
#line 4474 "p4parser.tab.c"
    break;

  case 281:
#line 808 "p4parser.y"
                                           {}
#line 4480 "p4parser.tab.c"
    break;

  case 282:
#line 812 "p4parser.y"
                               {}
#line 4486 "p4parser.tab.c"
    break;

  case 283:
#line 813 "p4parser.y"
                                       {}
#line 4492 "p4parser.tab.c"
    break;

  case 284:
#line 814 "p4parser.y"
                                       {}
#line 4498 "p4parser.tab.c"
    break;

  case 285:
#line 815 "p4parser.y"
                                       {}
#line 4504 "p4parser.tab.c"
    break;

  case 286:
#line 816 "p4parser.y"
                                       {}
#line 4510 "p4parser.tab.c"
    break;

  case 287:
#line 820 "p4parser.y"
                                     {}
#line 4516 "p4parser.tab.c"
    break;

  case 288:
#line 821 "p4parser.y"
                                       {}
#line 4522 "p4parser.tab.c"
    break;

  case 289:
#line 822 "p4parser.y"
                                       {}
#line 4528 "p4parser.tab.c"
    break;

  case 290:
#line 823 "p4parser.y"
                                       {}
#line 4534 "p4parser.tab.c"
    break;

  case 291:
#line 827 "p4parser.y"
                               {}
#line 4540 "p4parser.tab.c"
    break;

  case 292:
#line 827 "p4parser.y"
                                                    {}
#line 4546 "p4parser.tab.c"
    break;

  case 293:
#line 829 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4555 "p4parser.tab.c"
    break;

  case 294:
#line 838 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4564 "p4parser.tab.c"
    break;

  case 295:
#line 845 "p4parser.y"
                                     {}
#line 4570 "p4parser.tab.c"
    break;

  case 296:
#line 845 "p4parser.y"
                                                          {}
#line 4576 "p4parser.tab.c"
    break;

  case 297:
#line 846 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4585 "p4parser.tab.c"
    break;

  case 298:
#line 853 "p4parser.y"
                                     {}
#line 4591 "p4parser.tab.c"
    break;

  case 299:
#line 854 "p4parser.y"
                                       {}
#line 4597 "p4parser.tab.c"
    break;

  case 300:
#line 858 "p4parser.y"
                                           {}
#line 4603 "p4parser.tab.c"
    break;

  case 301:
#line 863 "p4parser.y"
                  {}
#line 4609 "p4parser.tab.c"
    break;

  case 302:
#line 864 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4618 "p4parser.tab.c"
    break;

  case 303:
#line 868 "p4parser.y"
                                       {}
#line 4624 "p4parser.tab.c"
    break;

  case 304:
#line 869 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4633 "p4parser.tab.c"
    break;

  case 305:
#line 876 "p4parser.y"
                            {}
#line 4639 "p4parser.tab.c"
    break;

  case 306:
#line 877 "p4parser.y"
                                                        {}
#line 4645 "p4parser.tab.c"
    break;

  case 307:
#line 881 "p4parser.y"
                               {}
#line 4651 "p4parser.tab.c"
    break;

  case 308:
#line 886 "p4parser.y"
        {}
#line 4657 "p4parser.tab.c"
    break;

  case 309:
#line 891 "p4parser.y"
        {}
#line 4663 "p4parser.tab.c"
    break;

  case 310:
#line 896 "p4parser.y"
                            {}
#line 4669 "p4parser.tab.c"
    break;

  case 311:
#line 897 "p4parser.y"
                                {}
#line 4675 "p4parser.tab.c"
    break;

  case 312:
#line 901 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4684 "p4parser.tab.c"
    break;

  case 313:
#line 905 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4693 "p4parser.tab.c"
    break;

  case 314:
#line 909 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4702 "p4parser.tab.c"
    break;

  case 315:
#line 913 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4711 "p4parser.tab.c"
    break;

  case 316:
#line 924 "p4parser.y"
        {}
#line 4717 "p4parser.tab.c"
    break;

  case 317:
#line 926 "p4parser.y"
        {}
#line 4723 "p4parser.tab.c"
    break;

  case 318:
#line 931 "p4parser.y"
        {}
#line 4729 "p4parser.tab.c"
    break;

  case 319:
#line 933 "p4parser.y"
        {}
#line 4735 "p4parser.tab.c"
    break;

  case 320:
#line 937 "p4parser.y"
                   {}
#line 4741 "p4parser.tab.c"
    break;

  case 321:
#line 941 "p4parser.y"
                   {}
#line 4747 "p4parser.tab.c"
    break;

  case 322:
#line 945 "p4parser.y"
                                {}
#line 4753 "p4parser.tab.c"
    break;

  case 323:
#line 946 "p4parser.y"
                                  {}
#line 4759 "p4parser.tab.c"
    break;

  case 324:
#line 951 "p4parser.y"
        {}
#line 4765 "p4parser.tab.c"
    break;

  case 325:
#line 953 "p4parser.y"
        {}
#line 4771 "p4parser.tab.c"
    break;

  case 326:
#line 958 "p4parser.y"
                                                              {}
#line 4777 "p4parser.tab.c"
    break;

  case 327:
#line 962 "p4parser.y"
                                     {}
#line 4783 "p4parser.tab.c"
    break;

  case 328:
#line 963 "p4parser.y"
                                       {}
#line 4789 "p4parser.tab.c"
    break;

  case 329:
#line 964 "p4parser.y"
                                       {}
#line 4795 "p4parser.tab.c"
    break;

  case 330:
#line 965 "p4parser.y"
                                       {}
#line 4801 "p4parser.tab.c"
    break;

  case 331:
#line 966 "p4parser.y"
                                       {}
#line 4807 "p4parser.tab.c"
    break;

  case 332:
#line 967 "p4parser.y"
                                       {}
#line 4813 "p4parser.tab.c"
    break;

  case 333:
#line 968 "p4parser.y"
                                       {}
#line 4819 "p4parser.tab.c"
    break;

  case 334:
#line 969 "p4parser.y"
                                       {}
#line 4825 "p4parser.tab.c"
    break;

  case 335:
#line 973 "p4parser.y"
                           {}
#line 4831 "p4parser.tab.c"
    break;

  case 336:
#line 974 "p4parser.y"
                             {}
#line 4837 "p4parser.tab.c"
    break;

  case 337:
#line 978 "p4parser.y"
                                          {}
#line 4843 "p4parser.tab.c"
    break;

  case 338:
#line 979 "p4parser.y"
                                            {}
#line 4849 "p4parser.tab.c"
    break;

  case 339:
#line 983 "p4parser.y"
                                                                  {}
#line 4855 "p4parser.tab.c"
    break;

  case 340:
#line 987 "p4parser.y"
                             {}
#line 4861 "p4parser.tab.c"
    break;

  case 341:
#line 988 "p4parser.y"
                               {}
#line 4867 "p4parser.tab.c"
    break;

  case 342:
#line 992 "p4parser.y"
                                     {}
#line 4873 "p4parser.tab.c"
    break;

  case 343:
#line 993 "p4parser.y"
                                       {}
#line 4879 "p4parser.tab.c"
    break;

  case 344:
#line 997 "p4parser.y"
                             {}
#line 4885 "p4parser.tab.c"
    break;

  case 345:
#line 998 "p4parser.y"
                               {}
#line 4891 "p4parser.tab.c"
    break;

  case 346:
#line 1002 "p4parser.y"
                             {}
#line 4897 "p4parser.tab.c"
    break;

  case 347:
#line 1003 "p4parser.y"
                               {}
#line 4903 "p4parser.tab.c"
    break;

  case 348:
#line 1004 "p4parser.y"
                               {}
#line 4909 "p4parser.tab.c"
    break;

  case 349:
#line 1005 "p4parser.y"
                               {}
#line 4915 "p4parser.tab.c"
    break;

  case 350:
#line 1013 "p4parser.y"
          {}
#line 4921 "p4parser.tab.c"
    break;

  case 351:
#line 1017 "p4parser.y"
                                       {}
#line 4927 "p4parser.tab.c"
    break;

  case 352:
#line 1018 "p4parser.y"
                                         {}
#line 4933 "p4parser.tab.c"
    break;

  case 353:
#line 1023 "p4parser.y"
        {}
#line 4939 "p4parser.tab.c"
    break;

  case 354:
#line 1025 "p4parser.y"
        {}
#line 4945 "p4parser.tab.c"
    break;

  case 355:
#line 1027 "p4parser.y"
        {}
#line 4951 "p4parser.tab.c"
    break;

  case 356:
#line 1029 "p4parser.y"
        {}
#line 4957 "p4parser.tab.c"
    break;

  case 357:
#line 1033 "p4parser.y"
                                       {}
#line 4963 "p4parser.tab.c"
    break;

  case 358:
#line 1034 "p4parser.y"
                                         {}
#line 4969 "p4parser.tab.c"
    break;

  case 359:
#line 1039 "p4parser.y"
                                         {}
#line 4975 "p4parser.tab.c"
    break;

  case 360:
#line 1043 "p4parser.y"
           {}
#line 4981 "p4parser.tab.c"
    break;

  case 361:
#line 1045 "p4parser.y"
        {}
#line 4987 "p4parser.tab.c"
    break;

  case 363:
#line 1054 "p4parser.y"
        {}
#line 4993 "p4parser.tab.c"
    break;

  case 364:
#line 1056 "p4parser.y"
        {}
#line 4999 "p4parser.tab.c"
    break;

  case 365:
#line 1061 "p4parser.y"
        {}
#line 5005 "p4parser.tab.c"
    break;

  case 366:
#line 1065 "p4parser.y"
                                   {}
#line 5011 "p4parser.tab.c"
    break;

  case 367:
#line 1066 "p4parser.y"
                                     {}
#line 5017 "p4parser.tab.c"
    break;

  case 368:
#line 1072 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 5026 "p4parser.tab.c"
    break;

  case 369:
#line 1081 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5035 "p4parser.tab.c"
    break;

  case 370:
#line 1085 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5044 "p4parser.tab.c"
    break;

  case 371:
#line 1093 "p4parser.y"
                                     {}
#line 5050 "p4parser.tab.c"
    break;

  case 372:
#line 1097 "p4parser.y"
                                     {}
#line 5056 "p4parser.tab.c"
    break;

  case 373:
#line 1098 "p4parser.y"
                                          {}
#line 5062 "p4parser.tab.c"
    break;

  case 374:
#line 1102 "p4parser.y"
                                        {}
#line 5068 "p4parser.tab.c"
    break;

  case 375:
#line 1108 "p4parser.y"
                                       {}
#line 5074 "p4parser.tab.c"
    break;

  case 376:
#line 1112 "p4parser.y"
                                       {}
#line 5080 "p4parser.tab.c"
    break;

  case 377:
#line 1113 "p4parser.y"
                                         {}
#line 5086 "p4parser.tab.c"
    break;

  case 378:
#line 1117 "p4parser.y"
                                       {}
#line 5092 "p4parser.tab.c"
    break;

  case 379:
#line 1118 "p4parser.y"
                                           {}
#line 5098 "p4parser.tab.c"
    break;

  case 380:
#line 1122 "p4parser.y"
                                       {}
#line 5104 "p4parser.tab.c"
    break;

  case 381:
#line 1123 "p4parser.y"
                                            {}
#line 5110 "p4parser.tab.c"
    break;

  case 382:
#line 1124 "p4parser.y"
                                              {}
#line 5116 "p4parser.tab.c"
    break;

  case 383:
#line 1128 "p4parser.y"
                                       {}
#line 5122 "p4parser.tab.c"
    break;

  case 384:
#line 1129 "p4parser.y"
                                         {}
#line 5128 "p4parser.tab.c"
    break;

  case 385:
#line 1130 "p4parser.y"
                                           {}
#line 5134 "p4parser.tab.c"
    break;

  case 386:
#line 1134 "p4parser.y"
                                       {}
#line 5140 "p4parser.tab.c"
    break;

  case 387:
#line 1135 "p4parser.y"
                                         {}
#line 5146 "p4parser.tab.c"
    break;

  case 388:
#line 1139 "p4parser.y"
        {}
#line 5152 "p4parser.tab.c"
    break;

  case 389:
#line 1139 "p4parser.y"
                {}
#line 5158 "p4parser.tab.c"
    break;

  case 390:
#line 1143 "p4parser.y"
                                       {}
#line 5164 "p4parser.tab.c"
    break;

  case 391:
#line 1144 "p4parser.y"
                                         {}
#line 5170 "p4parser.tab.c"
    break;

  case 392:
#line 1145 "p4parser.y"
                                         {}
#line 5176 "p4parser.tab.c"
    break;

  case 393:
#line 1146 "p4parser.y"
                                       {}
#line 5182 "p4parser.tab.c"
    break;

  case 394:
#line 1150 "p4parser.y"
                                            {}
#line 5188 "p4parser.tab.c"
    break;

  case 395:
#line 1151 "p4parser.y"
                                                      {}
#line 5194 "p4parser.tab.c"
    break;

  case 396:
#line 1154 "p4parser.y"
                                       {}
#line 5200 "p4parser.tab.c"
    break;

  case 397:
#line 1155 "p4parser.y"
                                         {}
#line 5206 "p4parser.tab.c"
    break;

  case 398:
#line 1156 "p4parser.y"
                                         {}
#line 5212 "p4parser.tab.c"
    break;

  case 399:
#line 1157 "p4parser.y"
                                         {}
#line 5218 "p4parser.tab.c"
    break;

  case 400:
#line 1158 "p4parser.y"
                                         {}
#line 5224 "p4parser.tab.c"
    break;

  case 401:
#line 1159 "p4parser.y"
                                         {}
#line 5230 "p4parser.tab.c"
    break;

  case 402:
#line 1160 "p4parser.y"
                                         {}
#line 5236 "p4parser.tab.c"
    break;

  case 403:
#line 1161 "p4parser.y"
                                                     {}
#line 5242 "p4parser.tab.c"
    break;

  case 404:
#line 1162 "p4parser.y"
                                                                 {}
#line 5248 "p4parser.tab.c"
    break;

  case 405:
#line 1163 "p4parser.y"
                                                 {}
#line 5254 "p4parser.tab.c"
    break;

  case 406:
#line 1164 "p4parser.y"
                                                 {}
#line 5260 "p4parser.tab.c"
    break;

  case 407:
#line 1165 "p4parser.y"
                                                 {}
#line 5266 "p4parser.tab.c"
    break;

  case 408:
#line 1166 "p4parser.y"
                                         {}
#line 5272 "p4parser.tab.c"
    break;

  case 409:
#line 1167 "p4parser.y"
                                                {}
#line 5278 "p4parser.tab.c"
    break;

  case 410:
#line 1168 "p4parser.y"
                                           {}
#line 5284 "p4parser.tab.c"
    break;

  case 411:
#line 1169 "p4parser.y"
                                          {}
#line 5290 "p4parser.tab.c"
    break;

  case 412:
#line 1171 "p4parser.y"
        {}
#line 5296 "p4parser.tab.c"
    break;

  case 413:
#line 1173 "p4parser.y"
        {}
#line 5302 "p4parser.tab.c"
    break;

  case 414:
#line 1174 "p4parser.y"
                                         {}
#line 5308 "p4parser.tab.c"
    break;

  case 415:
#line 1175 "p4parser.y"
                                         {}
#line 5314 "p4parser.tab.c"
    break;

  case 416:
#line 1176 "p4parser.y"
                                         {}
#line 5320 "p4parser.tab.c"
    break;

  case 417:
#line 1177 "p4parser.y"
                                         {}
#line 5326 "p4parser.tab.c"
    break;

  case 418:
#line 1178 "p4parser.y"
                                          {}
#line 5332 "p4parser.tab.c"
    break;

  case 419:
#line 1179 "p4parser.y"
                                           {}
#line 5338 "p4parser.tab.c"
    break;

  case 420:
#line 1180 "p4parser.y"
                                            {}
#line 5344 "p4parser.tab.c"
    break;

  case 421:
#line 1181 "p4parser.y"
                                             {}
#line 5350 "p4parser.tab.c"
    break;

  case 422:
#line 1182 "p4parser.y"
                                        {}
#line 5356 "p4parser.tab.c"
    break;

  case 423:
#line 1184 "p4parser.y"
        {}
#line 5362 "p4parser.tab.c"
    break;

  case 424:
#line 1185 "p4parser.y"
                                       {}
#line 5368 "p4parser.tab.c"
    break;

  case 425:
#line 1186 "p4parser.y"
                                       {}
#line 5374 "p4parser.tab.c"
    break;

  case 426:
#line 1188 "p4parser.y"
                                         {}
#line 5380 "p4parser.tab.c"
    break;

  case 427:
#line 1189 "p4parser.y"
                                             {}
#line 5386 "p4parser.tab.c"
    break;

  case 428:
#line 1191 "p4parser.y"
                                       {}
#line 5392 "p4parser.tab.c"
    break;

  case 429:
#line 1192 "p4parser.y"
                                       {}
#line 5398 "p4parser.tab.c"
    break;

  case 430:
#line 1193 "p4parser.y"
                                             {}
#line 5404 "p4parser.tab.c"
    break;

  case 431:
#line 1194 "p4parser.y"
                                             {}
#line 5410 "p4parser.tab.c"
    break;

  case 432:
#line 1195 "p4parser.y"
                                            {}
#line 5416 "p4parser.tab.c"
    break;

  case 433:
#line 1196 "p4parser.y"
                                       {}
#line 5422 "p4parser.tab.c"
    break;

  case 434:
#line 1197 "p4parser.y"
                                        {}
#line 5428 "p4parser.tab.c"
    break;

  case 435:
#line 1198 "p4parser.y"
                                       {}
#line 5434 "p4parser.tab.c"
    break;

  case 436:
#line 1199 "p4parser.y"
                                                      {}
#line 5440 "p4parser.tab.c"
    break;

  case 437:
#line 1200 "p4parser.y"
                         {}
#line 5446 "p4parser.tab.c"
    break;

  case 439:
#line 1204 "p4parser.y"
        {}
#line 5452 "p4parser.tab.c"
    break;

  case 440:
#line 1206 "p4parser.y"
        {}
#line 5458 "p4parser.tab.c"
    break;

  case 441:
#line 1208 "p4parser.y"
        {}
#line 5464 "p4parser.tab.c"
    break;

  case 442:
#line 1209 "p4parser.y"
                                                      {}
#line 5470 "p4parser.tab.c"
    break;

  case 443:
#line 1213 "p4parser.y"
                                       {}
#line 5476 "p4parser.tab.c"
    break;

  case 444:
#line 1214 "p4parser.y"
                                         {}
#line 5482 "p4parser.tab.c"
    break;

  case 445:
#line 1215 "p4parser.y"
                                         {}
#line 5488 "p4parser.tab.c"
    break;

  case 446:
#line 1216 "p4parser.y"
                                         {}
#line 5494 "p4parser.tab.c"
    break;

  case 447:
#line 1217 "p4parser.y"
                                         {}
#line 5500 "p4parser.tab.c"
    break;

  case 448:
#line 1218 "p4parser.y"
                                         {}
#line 5506 "p4parser.tab.c"
    break;

  case 449:
#line 1219 "p4parser.y"
                                         {}
#line 5512 "p4parser.tab.c"
    break;

  case 450:
#line 1220 "p4parser.y"
                                                             {}
#line 5518 "p4parser.tab.c"
    break;

  case 451:
#line 1221 "p4parser.y"
                                                                         {}
#line 5524 "p4parser.tab.c"
    break;

  case 452:
#line 1222 "p4parser.y"
                                                 {}
#line 5530 "p4parser.tab.c"
    break;

  case 453:
#line 1223 "p4parser.y"
                                         {}
#line 5536 "p4parser.tab.c"
    break;

  case 454:
#line 1224 "p4parser.y"
                                                {}
#line 5542 "p4parser.tab.c"
    break;

  case 455:
#line 1225 "p4parser.y"
                                           {}
#line 5548 "p4parser.tab.c"
    break;

  case 456:
#line 1226 "p4parser.y"
                                          {}
#line 5554 "p4parser.tab.c"
    break;

  case 457:
#line 1228 "p4parser.y"
        {}
#line 5560 "p4parser.tab.c"
    break;

  case 458:
#line 1230 "p4parser.y"
        {}
#line 5566 "p4parser.tab.c"
    break;

  case 459:
#line 1231 "p4parser.y"
                                                 {}
#line 5572 "p4parser.tab.c"
    break;

  case 460:
#line 1232 "p4parser.y"
                                                 {}
#line 5578 "p4parser.tab.c"
    break;

  case 461:
#line 1233 "p4parser.y"
                                                 {}
#line 5584 "p4parser.tab.c"
    break;

  case 462:
#line 1234 "p4parser.y"
                                                 {}
#line 5590 "p4parser.tab.c"
    break;

  case 463:
#line 1235 "p4parser.y"
                                                  {}
#line 5596 "p4parser.tab.c"
    break;

  case 464:
#line 1236 "p4parser.y"
                                                   {}
#line 5602 "p4parser.tab.c"
    break;

  case 465:
#line 1237 "p4parser.y"
                                                    {}
#line 5608 "p4parser.tab.c"
    break;

  case 466:
#line 1238 "p4parser.y"
                                                     {}
#line 5614 "p4parser.tab.c"
    break;

  case 467:
#line 1239 "p4parser.y"
                                                {}
#line 5620 "p4parser.tab.c"
    break;

  case 468:
#line 1241 "p4parser.y"
        {}
#line 5626 "p4parser.tab.c"
    break;

  case 469:
#line 1242 "p4parser.y"
                                               {}
#line 5632 "p4parser.tab.c"
    break;

  case 470:
#line 1243 "p4parser.y"
                                               {}
#line 5638 "p4parser.tab.c"
    break;

  case 471:
#line 1245 "p4parser.y"
                                         {}
#line 5644 "p4parser.tab.c"
    break;

  case 472:
#line 1246 "p4parser.y"
                                                     {}
#line 5650 "p4parser.tab.c"
    break;

  case 473:
#line 1247 "p4parser.y"
                                               {}
#line 5656 "p4parser.tab.c"
    break;

  case 474:
#line 1248 "p4parser.y"
                                               {}
#line 5662 "p4parser.tab.c"
    break;

  case 475:
#line 1249 "p4parser.y"
                                                     {}
#line 5668 "p4parser.tab.c"
    break;

  case 476:
#line 1250 "p4parser.y"
                                                     {}
#line 5674 "p4parser.tab.c"
    break;

  case 477:
#line 1251 "p4parser.y"
                                                    {}
#line 5680 "p4parser.tab.c"
    break;

  case 478:
#line 1252 "p4parser.y"
                                               {}
#line 5686 "p4parser.tab.c"
    break;

  case 479:
#line 1253 "p4parser.y"
                                                {}
#line 5692 "p4parser.tab.c"
    break;

  case 480:
#line 1254 "p4parser.y"
                                               {}
#line 5698 "p4parser.tab.c"
    break;

  case 481:
#line 1255 "p4parser.y"
                                                              {}
#line 5704 "p4parser.tab.c"
    break;

  case 482:
#line 1257 "p4parser.y"
        {}
#line 5710 "p4parser.tab.c"
    break;

  case 483:
#line 1259 "p4parser.y"
        {}
#line 5716 "p4parser.tab.c"
    break;

  case 484:
#line 1261 "p4parser.y"
        {}
#line 5722 "p4parser.tab.c"
    break;

  case 485:
#line 1262 "p4parser.y"
                                                      {}
#line 5728 "p4parser.tab.c"
    break;


#line 5732 "p4parser.tab.c"

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
