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
#define YYLAST   4129

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  149
/* YYNRULES -- Number of rules.  */
#define YYNRULES  486
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  890

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
     893,   897,   901,   905,   909,   919,   922,   925,   931,   935,
     939,   940,   944,   946,   952,   956,   957,   958,   959,   960,
     961,   962,   963,   967,   967,   972,   973,   977,   981,   982,
     986,   987,   991,   992,   996,   997,   998,   999,  1005,  1011,
    1012,  1016,  1018,  1020,  1022,  1027,  1028,  1032,  1037,  1038,
    1043,  1047,  1049,  1054,  1059,  1060,  1066,  1075,  1079,  1086,
    1091,  1092,  1096,  1102,  1106,  1107,  1111,  1112,  1116,  1117,
    1118,  1122,  1123,  1124,  1128,  1129,  1133,  1133,  1137,  1138,
    1139,  1140,  1141,  1145,  1146,  1147,  1148,  1149,  1150,  1151,
    1152,  1153,  1154,  1155,  1156,  1157,  1158,  1159,  1160,  1161,
    1163,  1165,  1166,  1167,  1168,  1169,  1170,  1171,  1172,  1173,
    1174,  1176,  1177,  1178,  1180,  1182,  1183,  1184,  1185,  1186,
    1187,  1188,  1189,  1190,  1191,  1193,  1194,  1196,  1198,  1200,
    1204,  1205,  1206,  1207,  1208,  1209,  1210,  1211,  1212,  1213,
    1214,  1215,  1216,  1217,  1218,  1220,  1222,  1223,  1224,  1225,
    1226,  1227,  1228,  1229,  1230,  1231,  1233,  1234,  1235,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1249,  1251,  1253,  1276,  1276,  1277,  1277
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
  "assignmentOrMethodCallStatement", "emptyStatement", "exitStatement",
  "returnStatement", "conditionalStatement", "directApplication",
  "statement", "blockStatement", "$@20", "statOrDeclList",
  "switchStatement", "switchCases", "switchCase", "switchLabel",
  "statementOrDeclaration", "tableDeclaration", "tablePropertyList",
  "tableProperty", "keyElementList", "keyElement", "actionList", "action",
  "actionRef", "entry", "entriesList", "actionDeclaration",
  "variableDeclaration", "constantDeclaration", "optInitializer",
  "initializer", "functionDeclaration", "argumentList", "nonEmptyArgList",
  "argument", "expressionList", "prefixedNonTypeName", "dot_name", "$@21",
  "lvalue", "expression", "invokingExpression", "nonBraceExpression",
  "l_angle", "r_angle", YY_NULLPTR
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

#define YYPACT_NINF (-767)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-382)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -767,    45,  -767,   816,  -767,  -767,  -767,   409,  -767,    -6,
       9,    -6,    11,   409,  -767,    -6,    -6,  -767,  -767,  -767,
    -767,  1487,   885,  -767,    12,  -767,   -76,  -767,   -11,  -767,
     205,  -767,   -37,    26,  -767,   269,  -767,  -767,    88,  -767,
     409,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,    84,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,   231,  -767,  -767,   -27,   409,   -25,   409,  -767,
    2549,   -24,   409,   387,   409,  2635,  2592,   409,   409,   885,
     409,   409,   409,   885,  -767,  -767,    87,  -767,  -767,     3,
    -767,  -767,  -767,   115,   129,   -37,  -767,  1608,  2373,  2549,
    2373,    -6,  -767,  1975,  -767,  2373,    47,  -767,   -17,  2373,
      47,    -9,  1710,  -767,  -767,  -767,  -767,  -767,   286,  2373,
      47,   128,   409,  -767,   148,  -767,   409,   133,   136,   142,
     172,  -767,  -767,  -767,    70,   409,   409,  -767,  -767,    -6,
     409,   409,  1608,   218,   198,   204,  -767,   208,  -767,  -767,
    2373,  2373,  2373,  2024,  1244,  2373,  -767,  -767,  -767,  -767,
     219,  -767,  -767,   207,   227,   862,   240,   162,  -767,   258,
     266,  -767,  3766,  -767,  -767,  2952,   286,  2989,  -767,  -767,
     409,   272,    71,  -767,   122,  3766,  1802,  3026,  -767,  -767,
    -767,  -767,   409,  3063,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  2549,  -767,  3100,  -767,     3,
     274,    -6,   298,  -767,    -6,  -767,  -767,    -6,    -6,  -767,
    -767,    -6,    -6,   305,  -767,  -767,   288,  -767,  -767,  -767,
     387,  -767,   -37,  -767,  2675,  -767,   104,   104,   104,   113,
     174,   219,   304,   321,   237,  3137,   104,   409,  2373,  -767,
    1608,  -767,  -767,   409,  2226,  2373,  2373,  2373,  2373,  2373,
    2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,
    2373,  2373,  2373,  2373,   309,  1608,  2373,  2373,  -767,  1003,
    -767,  -767,  -767,   311,  -767,   316,  2373,  -767,   409,  -767,
    2373,  -767,    47,  -767,    47,  1894,  -767,    47,   315,  2373,
    -767,   409,   329,  -767,  -767,  -767,  -767,  -767,  -767,   409,
     409,  -767,   885,   -37,    35,   885,  -767,  -767,    32,  -767,
    -767,  -767,  -767,  2420,  -767,  -767,  2373,  -767,  -767,  3766,
     325,   409,   249,  -767,  3974,  3974,   235,  3910,  3877,  3943,
    3943,   291,   291,   291,   291,   104,   104,   104,  4005,  4067,
    4036,  2841,  3974,  2373,   335,  3174,   291,  -767,  -767,  -767,
    -767,   330,  3974,     3,   409,  -767,  3766,  -767,  3766,  -767,
    -767,  -767,  -767,   -37,   332,  3766,   338,   196,   409,   347,
     351,   352,   348,   349,   -10,   295,   344,   -46,  -767,  -767,
      -3,  -767,  -767,  -767,  -767,   359,  -767,   409,   337,   355,
    -767,  -767,  -767,   360,   367,  2275,   371,  -767,    33,  -767,
     862,   252,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,   175,   104,  -767,  -767,   361,
    -767,  -767,  2373,   235,  -767,  2373,  2549,   374,   358,  -767,
    -767,  -767,     3,  -767,   369,   199,  -767,  -767,  -767,  -767,
       3,     3,  -767,   387,  -767,   361,  -767,  2373,   409,    -6,
     333,   382,  -767,  -767,   388,   355,  2373,   373,  -767,  2373,
    -767,  3211,  2373,  -767,   363,  2373,  1608,  2373,  -767,  2549,
    -767,   378,  3248,  3840,  -767,  1608,  -767,   386,  2373,  -767,
     409,    52,    60,    62,   389,   390,   409,   384,  3766,  -767,
     387,  -767,    80,   392,  -767,  -767,  3285,  -767,  3322,   394,
    2878,   400,  3359,   286,  2508,  -767,  -767,   401,  -767,  -767,
    -767,  -767,   605,  -767,  -767,  -767,  -767,  -767,   397,  -767,
     412,    47,    47,    47,   404,   405,   398,     5,  -767,  -767,
     686,   413,  1608,  -767,  2373,   407,  -767,   422,  -767,   885,
    -767,  -767,  -767,  -767,   953,   425,   418,  -767,  -767,   430,
     432,   433,   419,   440,  -767,    73,  -767,  -767,   431,   415,
    -767,   442,  3396,  -767,  1608,   437,     3,  -767,  1073,  2373,
    2373,  2373,  -767,  -767,  -767,   444,  -767,  -767,  -767,  -767,
     446,   686,  1466,   441,  -767,   454,  -767,   457,   618,    72,
     885,  -767,  -767,   464,   409,  -767,  -767,  -767,  -767,  -767,
    -767,  3433,  3470,  3507,    79,  2324,   468,  2373,  -767,  2373,
    2373,  2373,  -767,  1244,  2373,  -767,  -767,  -767,  -767,   458,
    -767,  -767,  -767,   862,   463,   162,  -767,   462,  3803,  -767,
     466,   467,   470,   472,  -767,  -767,  -767,   409,  -767,   409,
     409,   409,  -767,   157,  -767,  -767,  -767,  3544,  2075,   475,
     104,   104,   104,   465,  3581,   104,   409,  -767,  1608,  -767,
     -15,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,
    2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,  2373,
     478,  1608,  2373,  2373,  -767,  1003,  -767,  -767,  2124,  -767,
    -767,   476,   477,   479,   499,   480,   492,   409,  1181,  -767,
    -767,   490,  -767,  -767,  -767,  1344,  2801,  -767,  2373,  -767,
    -767,   493,  -767,  3974,  3974,   235,  3910,  3877,  3943,  3943,
     291,   291,   291,   291,   104,   104,   104,  4005,  4067,  4036,
    2915,  3974,  2373,   494,  3618,   291,   330,  3974,    64,  2468,
    -767,  -767,  -767,  -767,  1608,   -37,   474,   495,   497,   498,
    2761,   157,  -767,  -767,  2373,  2373,   104,  -767,  -767,  2373,
     235,  -767,  2373,   496,   507,  -767,   502,   501,  -767,  2175,
    2373,  2373,   -37,  3766,  3766,  3655,  3840,  1608,  -767,  -767,
    -767,   169,  -767,  3692,  3729,   504,  -767,   513,  1395,  -767,
    2175,  -767,  -767,  -767,  -767,   517,  -767,   409,   516,  -767
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
      25,    24,    37,   483,   484,     0,     0,     0,     0,    42,
     273,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    33,   251,    36,     0,   285,   244,    33,
     283,   159,   284,     0,     0,    34,   373,   435,   435,   273,
     435,   264,   282,   435,    42,   435,     0,   309,     0,   435,
       0,     0,     0,   272,   271,   270,   269,   274,     0,   435,
       0,     0,     0,   213,   243,   300,     0,   263,   224,     0,
       0,   261,   290,   294,     0,     0,     0,   144,   168,   264,
       0,     0,   435,   143,     0,   135,   136,     0,   216,   333,
     435,   435,   435,   435,   435,   435,   380,   395,   396,   397,
       0,   394,   393,   398,     0,     0,     0,   241,   242,     0,
     375,   376,   378,   434,   398,     0,     0,     0,   231,   265,
       0,     0,     0,   131,     0,   382,     0,     0,   485,   486,
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
       0,   157,    33,   162,    33,   335,   408,   407,   406,     0,
       0,   251,     0,   237,   238,     0,   405,     0,   435,   399,
     435,   386,   409,     0,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,     0,   435,   435,   435,   411,   435,
     247,   249,   248,     0,   267,     0,   435,    40,     0,    39,
     435,    38,     0,   310,     0,     0,   275,     0,     0,   435,
     214,     0,     0,   225,   291,   295,   145,   169,   297,     0,
       0,   137,    33,    33,     0,    34,   221,   217,     0,   220,
     219,   222,   218,    33,   403,   402,   435,   404,   410,   379,
       0,     0,     0,   377,   421,   422,   419,   431,   432,   425,
     426,   415,   416,   417,   418,   412,   413,   414,   429,   427,
     428,     0,   424,   435,     0,     0,   430,   278,   277,   276,
     279,     0,   423,    33,     0,   266,   133,   132,   383,   258,
     259,    43,   260,    33,     0,   372,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,   138,     0,   165,   163,
      33,   171,   167,   166,   164,     0,   223,     0,     0,   370,
     334,   318,   389,     0,     0,   435,     0,   384,     0,   347,
       0,   237,   325,   328,   331,   330,   327,   326,   346,   329,
     332,   336,   344,   345,   388,     0,   439,   438,   387,     0,
     148,   400,   435,   420,   437,   435,     0,     0,     0,   268,
     366,   369,    33,   301,     0,     0,   304,   229,   297,   297,
      33,    33,   293,     0,   298,     0,   147,   435,     0,     0,
       0,     0,   172,   212,     0,   370,   435,     0,   319,   435,
     320,     0,   435,   385,     0,   435,   435,   435,   390,   273,
     152,     0,     0,   433,   280,   435,   232,     0,   435,   303,
       0,    33,    33,    33,     0,     0,     0,     0,   139,   173,
       0,   161,    33,     0,   371,   368,     0,   321,     0,     0,
       0,     0,     0,     0,     0,   150,   401,     0,   215,   306,
     305,   226,     0,   230,   292,   296,   146,   170,     0,   149,
       0,     0,     0,     0,     0,     0,    31,    33,   349,   367,
      33,     0,   435,   391,   435,     0,   317,     0,   151,     0,
     155,   153,   154,   436,     0,   243,     0,   299,   175,     0,
       0,     0,     0,     0,    32,     0,   348,   350,     0,   322,
     338,     0,     0,   315,   435,     0,    33,   233,    33,   435,
     435,   435,   358,   355,    28,     0,    30,    29,    26,    27,
       0,    33,     0,     0,   392,     0,   234,     0,     0,     0,
      34,   176,   182,     0,     0,   177,   179,   183,   178,   180,
     181,     0,     0,     0,    33,   435,     0,   435,   323,   435,
     435,   435,   337,   435,   435,   442,   443,   444,   342,     0,
     441,   440,   445,     0,     0,   241,   339,     0,   343,   324,
       0,     0,     0,     0,   187,   189,   184,     0,   174,     0,
       0,     0,   352,     0,   359,   351,   356,     0,   435,     0,
     453,   452,   451,     0,     0,   450,     0,   446,   435,   454,
     341,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
       0,   435,   435,   435,   456,   435,   316,   235,   435,   188,
     175,     0,     0,     0,     0,     0,   361,     0,   435,   208,
     207,     0,   194,   195,   364,   435,   204,   354,   435,   449,
     455,     0,   340,   466,   467,   464,   476,   477,   470,   471,
     460,   461,   462,   463,   457,   458,   459,   474,   472,   473,
       0,   469,   435,     0,     0,   475,     0,   468,     0,    33,
     211,   210,   209,   360,   435,    33,   203,   202,     0,     0,
     204,     0,   353,   365,   435,   435,   482,   481,   447,   435,
     465,   480,   435,     0,     0,   185,     0,     0,   197,   435,
     435,   435,    33,   205,   206,     0,   478,   435,   191,   362,
     357,     0,   198,   200,   201,     0,   448,     0,   435,   196,
     435,   363,   479,   190,   192,     0,   199,     0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -767,  -767,  -767,  -767,  -767,    -7,   123,  -767,  -767,     2,
      10,   -18,   -86,  -767,   424,   211,  -269,  -767,   268,  -767,
    -767,  -767,  -767,  -312,    48,  -767,  -767,   552,   215,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,   116,  -767,
    -195,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -767,  -290,
    -767,  -767,  -767,  -766,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -767,  -767,   -69,  -767,  -767,   165,
     -82,  -767,   342,    13,  -767,   277,    14,  -767,   -85,  -767,
    -767,  -274,   -90,  -767,  -180,  -767,   152,  -767,  -767,  -767,
    -767,  -767,  -767,  -767,  -144,  -767,  -767,  -767,  -767,  -767,
      27,  -767,  -767,   -56,  -767,  -643,  -641,  -767,  -767,  -639,
    -637,  -588,   -31,  -767,  -767,  -767,  -767,  -767,  -767,  -767,
    -767,  -767,   -21,  -767,  -767,  -767,  -767,  -242,  -193,  -767,
     289,  -291,     7,    61,  -532,    18,  -116,  -767,   271,  -150,
    -717,  -159,  -767,  -767,   851,  -767,  -767,   323,   -70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    20,   174,   164,   670,   645,   143,
      95,    23,   112,   284,   182,   183,   144,   145,   146,   310,
      24,   301,   462,    25,   561,   594,   631,    91,   165,    27,
     147,   541,   392,   469,    28,   302,   463,   470,   471,   610,
     658,   681,   682,   780,   683,   724,   725,   878,   884,   791,
     792,   871,   838,   793,   472,    29,    30,   291,   456,   314,
     397,   475,    31,   294,   459,   571,    32,   363,   603,   116,
     166,    34,   167,    36,    37,   168,    39,    40,   178,   179,
     365,   117,   118,   440,   441,    41,    42,    43,   297,   460,
      44,    45,   298,   461,   464,   534,    46,   292,   382,   525,
     526,    47,    48,   108,    49,   492,   493,   494,   495,   496,
     497,   498,   499,   315,   403,   500,   672,   716,   717,   501,
     399,   617,   618,   695,   736,   694,   734,   785,   794,   795,
      50,   689,   690,   547,   454,    52,   169,   170,   171,   184,
     504,   358,   411,   505,   172,   173,   718,   359,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    96,   396,   320,    85,    21,    61,   130,   332,   176,
      51,   376,   111,    22,   584,   685,   786,   686,   186,   687,
     378,   688,   839,   401,     7,   105,   306,   109,   119,    73,
     191,   -33,   649,    61,    94,    88,   599,   532,   195,   192,
     194,    89,    63,    64,  -160,     4,     7,   192,   286,    90,
     288,     7,   646,   538,   303,    66,  -134,    68,     7,    61,
      13,    61,   539,   115,     7,    61,     7,    61,    61,   128,
      61,    61,    87,    61,    61,    61,   614,    85,    97,   149,
     468,   134,    13,   698,    97,   134,   106,    13,   110,   120,
     163,   489,   115,   872,    13,   615,   163,   188,   189,   601,
      13,   473,    13,    53,    54,    72,   361,   604,    73,   605,
      73,    55,   502,     7,   886,    61,   367,   854,   726,    61,
     370,     7,    56,     7,   786,    57,   732,   368,    61,    61,
      62,    58,   100,    61,    61,   163,    69,   375,   477,   142,
       7,     7,    59,    60,   102,   664,   163,    73,   352,    13,
      75,   614,   665,    64,    77,    78,   355,    13,   329,    13,
     404,   148,   331,   101,   332,   739,   666,   369,    33,   368,
     615,    82,   667,    61,   518,   149,    13,    13,   370,   -17,
     289,   -17,   -17,   668,   669,    61,   685,    86,   686,   107,
     687,   107,   688,   -17,   -25,   121,   -24,   123,   125,   129,
     132,   133,   295,   137,   138,   139,   380,   -25,   -25,   383,
      63,    64,   384,   385,   410,     5,   386,   387,    26,   555,
     331,   405,   879,    63,    64,   880,   181,   556,    53,    54,
     370,   136,   296,   331,   557,   141,    55,    26,   122,   434,
     126,   131,   564,   523,   135,   290,   569,    56,   140,   293,
      57,   311,   192,   567,   313,   570,    58,    89,   299,   300,
     312,   574,   575,   304,   305,    92,   -24,    59,   342,   343,
     344,   345,   346,   347,   348,   103,   181,   327,   115,   352,
      38,   100,   630,   104,    64,    26,   328,   355,    26,  -242,
      26,    26,   330,   331,    26,   445,    98,   357,    26,    38,
      63,    64,   449,   364,   450,   307,   308,   452,   509,   510,
     554,   333,   309,    98,    26,   373,   394,    63,    64,   322,
      61,   402,   334,   163,   395,   457,    61,   163,   346,   347,
     348,   366,    65,   379,    67,   352,   188,   189,    70,    71,
      64,   389,   285,   355,   381,    35,   558,    38,   163,   331,
      38,   388,    38,    38,   535,   536,    38,   406,    99,   433,
      38,    61,   476,   443,    35,    98,   188,   189,   453,    63,
      64,   517,   444,  -241,    61,   458,    38,    85,   507,   331,
     188,   189,    61,    61,   572,   573,   516,   677,   514,   142,
     522,    61,   521,   527,   467,    94,   487,   528,   529,   474,
     530,   531,   395,   537,    61,   488,   543,   560,    53,    54,
     503,   566,    35,   395,   546,    35,    55,    35,    35,   549,
     548,    35,   520,   552,   180,    35,   565,    56,   568,   581,
      57,   324,   538,   585,   582,   589,    58,    61,   595,   598,
     591,    35,   606,   607,   609,     5,   622,    59,    60,   597,
     408,    61,   619,   625,   633,    94,   412,   637,   638,   650,
       8,     9,   180,   642,   643,   662,   533,   653,    84,   593,
      61,    61,   540,   644,   654,   390,    11,   656,   657,   398,
      53,    54,   659,   553,   660,   661,   663,    14,    55,   554,
      99,   181,    15,   671,    16,   673,   323,   676,    19,    56,
      26,   719,    57,   696,   107,   697,   651,   720,    58,   115,
     721,   728,   465,   466,   738,   748,   746,   750,   798,    59,
      60,   479,   778,   627,   439,    26,   776,   777,   822,    26,
    -208,    61,   779,   636,   508,   797,   830,   831,   675,   832,
     833,   639,   640,   641,   834,   841,   847,   851,   867,   163,
     858,  -207,   115,   868,   859,   869,   749,   398,   163,   774,
     478,   870,    38,    61,   881,   655,   882,   519,   398,    61,
      53,    54,   887,   602,   533,   533,   889,   319,    55,   447,
     391,   524,    93,   577,   616,   829,   542,    38,   885,    56,
     714,    38,    57,   612,   613,   826,   647,   600,    58,   862,
     544,   545,   843,   400,   629,   413,   583,    26,     0,    59,
      26,    85,   632,   487,   180,   163,     0,   180,   490,   616,
     180,   180,    94,     0,   180,   180,     0,    35,   828,     0,
       0,     0,   801,     0,     0,     0,   324,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    99,   163,     0,     0,
       0,   487,    35,     0,     0,   823,    35,     0,     0,     0,
     679,   579,    85,     5,   487,   712,     0,     0,   680,    38,
       0,    61,    38,    94,   634,     0,     0,    61,     8,     9,
      38,     0,     0,     0,     0,     0,    84,     0,     0,    53,
      54,     0,     0,   524,    11,     0,   733,    55,   576,   608,
       0,   323,     0,     0,     0,    14,   747,     0,    56,   722,
      15,    57,    16,     0,    17,    18,   635,    58,   856,   802,
      61,     0,    61,    61,    61,     0,   487,     0,    59,    60,
       0,    26,     0,     0,    35,     0,     0,    35,     0,    61,
       0,   163,     0,     0,     5,   491,   481,     7,    26,     0,
       0,   877,    94,     0,   482,     0,   853,    53,    54,    33,
       0,     0,     0,     0,   163,    55,     0,   131,   483,     0,
       0,     0,   484,     0,    26,     0,    56,   553,     0,    57,
      61,     0,     0,    13,   485,    58,     0,     0,   486,     0,
       0,     0,     0,    38,    86,    26,    59,    19,     0,   131,
       0,   723,     0,     0,     0,     0,     0,   479,     0,    26,
      38,     0,     0,     0,    99,     0,    -3,    26,     0,     0,
       0,     0,   487,   684,     0,     0,     0,   163,   559,     0,
       0,   679,     0,     0,   487,   490,    38,   857,     0,   680,
       0,     0,     0,     0,    26,   727,     0,     0,     0,    26,
     545,     0,   781,   782,   783,     0,     0,     0,    35,     0,
     163,     0,   580,     0,   875,     0,     0,     0,   743,   800,
       0,    38,     0,   490,     5,    35,     6,     7,     0,    38,
      61,     0,     0,     0,     0,     0,   490,   713,     0,     8,
       9,     0,     0,     0,     0,    26,     0,    10,     0,     0,
       0,    35,     0,     0,     0,    11,    38,     0,    12,     0,
     835,    38,     0,    13,     0,     0,    14,     0,     0,     0,
       0,    15,   611,    16,     0,    17,    18,    19,     0,     0,
       0,     0,     0,    53,    54,    38,    35,     0,     0,     0,
     439,    55,     0,     5,    35,     0,     7,     0,   784,   175,
       0,   177,    56,   322,   185,    57,   187,    38,     8,     9,
     193,    58,   648,     0,     0,     0,    84,     0,     0,     0,
     287,    35,    59,    88,    11,     0,    35,     0,     0,     0,
     324,     0,    13,     0,     0,    14,     0,     0,     0,     0,
      15,     0,    16,     0,   684,     0,    19,     0,     0,     0,
     491,   316,   317,   318,   185,   325,   326,     0,     0,     0,
     888,     5,     0,   648,   715,     0,     0,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     8,     9,     0,     0,
       0,     0,     0,     0,    84,     0,   150,   151,    99,     0,
       0,   775,    11,     0,   490,   323,   152,     0,     0,   153,
       0,     0,   324,    14,     0,   154,   784,   155,    15,     0,
      16,     5,    17,    18,    19,   324,   437,     0,     0,   157,
     158,   159,     0,     0,    53,    54,     8,     9,     0,     0,
       0,     0,    55,     0,   321,     0,     0,     0,     0,     0,
       0,     0,    11,    56,     0,     0,    57,     0,     0,     0,
       0,     0,    58,    14,     0,     0,    38,     0,    15,     0,
      16,     0,   438,    59,    19,   161,   162,   323,     0,     0,
    -186,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     323,     5,     0,   481,     7,     0,     0,     0,     0,     0,
       0,   482,     0,     0,    53,    54,     8,     9,     0,     0,
       0,     0,    55,     0,    84,     0,     0,     0,     0,   484,
       0,     0,    11,    56,     0,     0,    57,     0,     0,     0,
      13,   491,    58,    14,     0,     0,     0,   678,    15,   409,
      16,     0,     0,    59,    19,     0,   414,   415,   416,   417,
     418,   419,   420,   421,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,   432,     0,     0,   435,   436,     0,
     442,     0,     0,     0,   150,   151,     0,   446,     0,     0,
       0,   448,     0,     0,   152,     0,     0,   153,     0,     0,
     455,     0,     0,   154,     0,   155,     0,     0,     0,     5,
       0,     0,     0,     0,   836,     0,     0,   157,   158,   159,
       0,     0,    53,    54,     8,     9,     0,   506,   837,     0,
      55,     0,   321,     0,     0,     0,     0,     0,     0,     0,
      11,    56,     0,     0,    57,     0,     0,   150,   151,     0,
      58,    14,     0,     0,   513,     0,    15,   152,    16,     0,
     153,    59,    19,   161,   162,     0,   154,     0,   155,     0,
       0,     0,     5,     0,     0,     0,     0,     0,     0,     0,
     157,   158,   159,     0,     0,    53,    54,     8,     9,     0,
       0,     0,     0,    55,     0,   321,     0,     0,     0,     0,
       0,     0,     0,    11,    56,     0,   551,    57,     0,     0,
       0,     0,     0,    58,    14,     0,     0,     0,     0,    15,
       0,    16,     0,     0,    59,    19,   161,   162,     0,     0,
       0,     0,     0,   562,     0,     0,   563,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,   152,   578,     0,
     153,   842,     0,     0,     0,     0,   788,   455,   155,     0,
     586,     0,     5,   588,     0,     0,   590,   789,   592,     0,
     157,   158,   159,     0,     0,    53,    54,     0,     0,   455,
       0,   790,     0,    55,     0,   160,     0,     0,   150,   151,
       0,     0,     0,     0,    56,     0,     0,    57,   152,     0,
       0,   153,   883,    58,     0,     0,     0,   788,     0,   155,
       0,     0,     0,     5,    59,    19,   161,   162,   789,     0,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,   790,     0,    55,   652,   160,     0,     0,     0,
       0,     0,     0,     0,     0,    56,     0,     0,    57,     0,
       0,     0,     0,     0,    58,     0,     0,     0,     0,   699,
     700,     0,     0,     0,     0,    59,    19,   161,   162,   701,
     691,   692,   693,   702,     0,     0,     0,     0,   703,     0,
     704,     0,     0,     0,     5,     0,     0,     0,     0,     0,
       0,     0,   705,   706,   707,     0,     0,    53,    54,     0,
       0,     0,     0,   708,     0,    55,   737,   709,   455,     0,
     740,   741,   742,     0,   744,   745,    56,    72,     0,    57,
       0,     0,    73,    74,     0,    58,     0,    75,     0,     0,
      76,    77,    78,     0,     0,     0,    59,    19,   710,   711,
      79,     0,    80,    81,     0,     0,     0,     0,    82,   796,
       0,     0,     0,    83,     0,     0,     0,     0,     0,     0,
       0,     0,   803,   804,   805,   806,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     821,     0,     0,   824,   825,     0,   827,     0,     0,   185,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   840,
       0,   150,   151,     0,     0,     0,   796,     0,     0,   846,
       0,   152,     0,     0,   153,     0,     0,     0,     0,     0,
     154,  -374,   155,     0,     0,     0,     5,     0,     0,     0,
       0,   156,     0,   850,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,     0,     0,    55,     0,   160,
       0,     0,     0,     0,     0,   863,   864,     0,    56,     0,
     865,    57,     0,   866,     0,     0,     0,    58,     0,     0,
     796,   873,   874,     0,     0,     0,     0,     0,    59,   124,
     161,   162,     0,     0,     0,     0,     0,     0,     0,   796,
       0,   796,   196,   197,     0,     0,   198,   199,     0,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   223,     0,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   196,     0,     0,     0,   198,   199,
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   371,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   196,     0,     0,     0,
     198,   199,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   451,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   150,   151,
       0,     0,     0,     0,     0,     0,     0,     0,   152,     0,
    -381,   153,     0,     0,     0,     0,     0,   154,     0,   155,
       0,  -381,     0,     5,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,    55,     0,   160,   150,   151,     0,
       0,     0,     0,     0,     0,    56,     0,   152,    57,     0,
     153,  -381,     0,     0,    58,     0,   154,     0,   155,     0,
    -381,     0,     5,     0,     0,    59,   124,   161,   162,     0,
     157,   158,   159,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    55,     0,   160,     0,     0,   150,   151,
       0,     0,     0,     0,    56,     0,     0,    57,   152,     0,
       0,   153,     0,    58,     0,     0,     0,   788,     0,   155,
       0,     0,     0,     5,    59,   124,   161,   162,   789,     0,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,   790,     0,    55,     0,   160,   150,   151,     0,
       0,     0,     0,     0,     0,    56,     0,   152,    57,     0,
     153,     0,     0,     0,    58,     0,   154,  -381,   155,     0,
    -381,     0,     5,     0,     0,    59,    19,   161,   162,     0,
     157,   158,   159,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    55,     0,   160,     0,     0,   150,   151,
       0,     0,     0,     0,    56,     0,     0,    57,   152,     0,
       0,   153,     0,    58,     0,     0,     0,   154,     0,   155,
       0,     0,     0,     5,    59,    19,   161,   162,   789,     0,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,   790,     0,    55,     0,   160,     0,     0,   150,
     151,     0,     0,     0,     0,    56,     0,     0,    57,   152,
       0,     0,   153,     0,    58,     0,     0,     0,   154,     0,
     155,     0,     0,     0,     5,    59,    19,   161,   162,   156,
       0,     0,   157,   158,   159,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   160,   150,   151,
       0,     0,     0,     0,     0,     0,    56,     0,   152,    57,
       0,   153,     0,     0,     0,    58,     0,   154,     0,   155,
       0,     0,     0,     5,     0,   550,    59,   124,   161,   162,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,    55,     0,   160,   150,   151,     0,
       0,     0,     0,     0,     0,    56,     0,   152,    57,     0,
     153,   735,     0,     0,    58,     0,   154,     0,   155,     0,
       0,     0,     5,     0,     0,    59,    19,   161,   162,     0,
     157,   158,   159,     0,     0,    53,    54,     0,     0,     0,
       0,     0,     0,    55,     0,   160,   150,   151,     0,     0,
       0,     0,     0,     0,    56,     0,   152,    57,     0,   153,
       0,     0,     0,    58,     0,   154,     0,   155,     0,     0,
       0,     5,     0,     0,    59,    19,   161,   162,     0,   157,
     158,   159,     0,     0,    53,    54,     0,     0,     0,     0,
       0,     0,    55,     0,   160,     0,     0,     0,     0,     0,
       0,     0,     0,    56,     0,     0,    57,   480,     0,     0,
       0,     0,    58,     0,     0,     0,     0,     0,     5,     0,
     481,     7,     0,    59,    19,   161,   162,     0,   482,     0,
       0,    53,    54,     8,     9,     0,     0,     0,     0,    55,
       0,    84,   483,     0,     0,     0,   484,     0,     0,    11,
      56,     0,     0,    57,     0,   855,     0,    13,   485,    58,
      14,     0,   486,     0,     0,    15,     5,    16,   481,     7,
      59,    19,     0,     0,     0,     0,   482,     0,     0,    53,
      54,     8,     9,     0,     0,     0,     0,    55,     0,    84,
       0,     0,     0,     0,   484,   628,     0,    11,    56,     0,
       0,    57,     0,     0,     0,    13,     5,    58,    14,     7,
       0,     0,     0,    15,     0,    16,     0,     0,    59,    19,
       0,     8,     9,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     5,    14,     0,
       0,     0,   113,    15,     0,    16,     0,    17,    18,    19,
      53,    54,     8,     9,     0,     0,     0,     0,    55,     0,
      84,     0,     0,     0,     0,     0,     0,     0,    11,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,    14,
       5,     0,     0,     0,    15,     0,    16,     0,   114,    59,
      19,     0,     0,    53,    54,     8,     9,     0,     0,     0,
       0,    55,     0,    84,     0,     0,     0,     0,     0,     0,
       0,    11,    56,     0,     0,    57,     0,     0,     0,     0,
       0,    58,    14,     5,     0,     0,     0,    15,     0,    16,
       0,    17,   127,   124,     0,     0,    53,    54,     8,     9,
       0,     0,     0,     0,    55,     0,    84,     0,     0,     0,
       0,     0,     0,     0,    11,    56,     0,     0,    57,     0,
       0,     0,     0,     5,    58,    14,     7,     0,     0,     0,
      15,     0,    16,     0,     0,    59,   124,   393,     8,     9,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,     0,    11,     0,     0,     0,     0,     0,
       0,     0,    13,     0,     0,    14,     0,     0,     0,     0,
      15,     0,    16,     0,     0,     0,    19,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,   407,     0,     0,     0,   356,   331,
       0,     0,     0,   357,     0,   860,   861,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,     0,   356,   331,
       0,     0,     0,   357,     0,   844,   845,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,   511,     0,     0,    63,
      64,   353,   354,   355,     0,     0,   512,     0,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,   623,     0,     0,    63,    64,   353,   354,
     355,     0,     0,   624,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
     848,     0,     0,    63,    64,   353,   354,   355,     0,     0,
     849,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,   360,     0,     0,
      63,    64,   353,   354,   355,     0,     0,     0,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,   362,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,     0,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,    63,    64,   353,   354,   355,   372,
       0,     0,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,   374,     0,     0,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,   377,     0,     0,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
     407,     0,     0,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,     0,     0,   515,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,     0,   356,   331,
       0,   587,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,   596,     0,     0,    63,    64,   353,   354,
     355,     0,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,   620,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,   621,     0,     0,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,     0,   356,   331,     0,   626,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,   674,     0,     0,    63,    64,   353,   354,   355,     0,
       0,     0,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,   729,     0,     0,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,   730,     0,     0,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
     731,     0,     0,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,     0,     0,   787,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,   799,     0,     0,     0,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,     0,     0,   852,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
     876,     0,     0,    63,    64,   353,   354,   355,     0,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,     0,     0,     0,  -205,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,  -206,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,    63,    64,   353,   354,   355,     0,
       0,     0,     0,   356,   331,     0,     0,     0,   357,   751,
     752,   753,   754,   755,   756,   757,   758,   759,   760,   761,
     762,   763,   764,   765,   766,   767,     0,   768,     0,     0,
       0,    63,    64,   769,   770,   771,     0,     0,     0,     0,
     772,   331,     0,     0,     0,   773,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,     0,     0,     0,     0,     0,   331,     0,
       0,     0,   357,   335,   336,   337,   338,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
       0,     0,     0,     0,     0,   331,   335,   336,   337,   357,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,     0,     0,     0,     0,     0,   331,   335,
     336,   337,   357,     0,     0,     0,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,     0,     0,     0,     0,
       0,   331,   337,     0,     0,   357,     0,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,     0,    64,     0,   354,   355,     0,     0,     0,
       0,     0,   331,   337,     0,     0,   357,     0,   342,   343,
     344,   345,   346,   347,   348,     0,   350,   351,     0,   352,
       0,     0,     0,     0,    64,     0,   354,   355,     0,     0,
       0,     0,     0,   331,   337,     0,     0,   357,     0,   342,
     343,   344,   345,   346,   347,   348,     0,   350,     0,     0,
     352,     0,     0,     0,     0,    64,     0,   354,   355,     0,
       0,     0,     0,     0,   331,   337,     0,     0,   357,     0,
     342,   343,   344,   345,   346,   347,   348,     0,     0,     0,
       0,   352,     0,     0,     0,     0,    64,     0,   354,   355,
       0,     0,     0,     0,     0,   331,     0,     0,     0,   357
};

static const yytype_int16 yycheck[] =
{
       7,    32,   314,   153,    22,     3,    13,    76,   167,    99,
       3,   285,    68,     3,   546,   658,   733,   658,   104,   658,
     289,   658,   788,   314,    61,    52,   142,    52,    52,    75,
      47,    46,   620,    40,    32,   111,   568,    47,    47,    56,
     110,    52,    48,    49,    47,     0,    61,    56,   118,    60,
     120,    61,    47,    99,   139,    46,    53,    46,    61,    66,
      97,    68,   108,    70,    61,    72,    61,    74,    75,    76,
      77,    78,    60,    80,    81,    82,    71,    95,    52,    46,
     392,    79,    97,   671,    52,    83,   113,    97,   113,   113,
      97,   403,    99,   859,    97,    90,   103,    50,    51,    47,
      97,   392,    97,    71,    72,    70,   176,    47,    75,    47,
      75,    79,   403,    61,   880,   122,    45,    53,    46,   126,
      56,    61,    90,    61,   841,    93,    47,    56,   135,   136,
       7,    99,    44,   140,   141,   142,    13,   223,   103,    52,
      61,    61,   110,   111,    60,    72,   153,    75,    44,    97,
      80,    71,    79,    49,    84,    85,    52,    97,   165,    97,
      47,    46,    58,    40,   323,   697,    93,    45,     3,    56,
      90,   101,    99,   180,   443,    46,    97,    97,    56,    46,
      52,    48,    49,   110,   111,   192,   829,    22,   829,    66,
     829,    68,   829,    60,    46,    72,    60,    74,    75,    76,
      77,    78,    60,    80,    81,    82,   291,    59,    60,   294,
      48,    49,   297,   298,   330,    58,   301,   302,     3,    44,
      58,    47,    53,    48,    49,    56,   103,    52,    71,    72,
      56,    79,    60,    58,    59,    83,    79,    22,    73,   355,
      75,    76,   516,    47,    79,   122,    47,    90,    83,   126,
      93,    53,    56,   522,    46,    56,    99,    52,   135,   136,
      56,   530,   531,   140,   141,    60,    59,   110,    33,    34,
      35,    36,    37,    38,    39,    44,   153,    58,   285,    44,
       3,    44,   594,    52,    49,    70,    59,    52,    73,    52,
      75,    76,    52,    58,    79,   365,    44,    62,    83,    22,
      48,    49,   372,   180,   374,    87,    88,   377,    59,    60,
      58,    53,    94,    44,    99,   192,   314,    48,    49,   154,
     327,   314,    56,   330,   314,   381,   333,   334,    37,    38,
      39,    59,     9,    59,    11,    44,    50,    51,    15,    16,
      49,    53,    56,    52,    46,     3,   505,    70,   355,    58,
      73,    46,    75,    76,    59,    60,    79,    53,    35,    50,
      83,   368,   393,    52,    22,    44,    50,    51,    53,    48,
      49,   441,    56,    52,   381,    46,    99,   395,    53,    58,
      50,    51,   389,   390,   528,   529,    56,   656,    53,    52,
      52,   398,    60,    46,   392,   393,   403,    46,    46,   392,
      52,    52,   392,    59,   411,   403,    47,    46,    71,    72,
     403,    53,    70,   403,    59,    73,    79,    75,    76,    52,
      60,    79,   453,    52,   101,    83,    52,    90,    59,    47,
      93,   154,    99,    60,    46,    72,    99,   444,    60,    53,
     556,    99,    53,    53,    60,    58,    52,   110,   111,   565,
     327,   458,    60,    53,    53,   453,   333,    60,    46,    46,
      73,    74,   139,    59,    59,    46,   464,    60,    81,   559,
     477,   478,   470,    75,    52,   310,    89,    52,    60,   314,
      71,    72,    52,   490,    52,    52,    46,   100,    79,    58,
     167,   368,   105,    78,   107,    53,   154,    60,   111,    90,
     285,    60,    93,    59,   381,    59,   622,    53,    99,   516,
      53,    47,   389,   390,    46,    52,    58,    55,    53,   110,
     111,   398,    52,   593,   359,   310,    60,    60,    50,   314,
      56,   538,    60,   602,   411,    60,    60,    60,   654,    60,
      60,   611,   612,   613,    52,    55,    53,    53,    52,   556,
      53,    56,   559,    46,    56,    53,   715,   392,   565,   718,
     395,    60,   285,   570,    60,   634,    53,   444,   403,   576,
      71,    72,    55,   571,   572,   573,    60,   153,    79,   368,
     312,   458,    30,   535,   582,   780,   470,   310,   878,    90,
     672,   314,    93,   580,   580,   775,   617,   570,    99,   841,
     477,   478,   795,   314,   594,   334,   545,   392,    -1,   110,
     395,   629,   594,   620,   291,   622,    -1,   294,   403,   617,
     297,   298,   620,    -1,   301,   302,    -1,   285,   778,    -1,
      -1,    -1,   748,    -1,    -1,    -1,   359,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   323,   654,    -1,    -1,
      -1,   658,   310,    -1,    -1,   771,   314,    -1,    -1,    -1,
     658,   538,   680,    58,   671,   672,    -1,    -1,   658,   392,
      -1,   678,   395,   671,    69,    -1,    -1,   684,    73,    74,
     403,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    71,
      72,    -1,    -1,   570,    89,    -1,   694,    79,   533,   576,
      -1,   359,    -1,    -1,    -1,   100,   713,    -1,    90,    91,
     105,    93,   107,    -1,   109,   110,   111,    99,   834,   750,
     727,    -1,   729,   730,   731,    -1,   733,    -1,   110,   111,
      -1,   516,    -1,    -1,   392,    -1,    -1,   395,    -1,   746,
      -1,   748,    -1,    -1,    58,   403,    60,    61,   533,    -1,
      -1,   867,   750,    -1,    68,    -1,   826,    71,    72,   594,
      -1,    -1,    -1,    -1,   771,    79,    -1,   602,    82,    -1,
      -1,    -1,    86,    -1,   559,    -1,    90,   784,    -1,    93,
     787,    -1,    -1,    97,    98,    99,    -1,    -1,   102,    -1,
      -1,    -1,    -1,   516,   629,   580,   110,   111,    -1,   634,
      -1,   678,    -1,    -1,    -1,    -1,    -1,   684,    -1,   594,
     533,    -1,    -1,    -1,   491,    -1,     0,   602,    -1,    -1,
      -1,    -1,   829,   658,    -1,    -1,    -1,   834,   505,    -1,
      -1,   829,    -1,    -1,   841,   620,   559,   835,    -1,   829,
      -1,    -1,    -1,    -1,   629,   680,    -1,    -1,    -1,   634,
     727,    -1,   729,   730,   731,    -1,    -1,    -1,   516,    -1,
     867,    -1,   539,    -1,   862,    -1,    -1,    -1,   703,   746,
      -1,   594,    -1,   658,    58,   533,    60,    61,    -1,   602,
     887,    -1,    -1,    -1,    -1,    -1,   671,   672,    -1,    73,
      74,    -1,    -1,    -1,    -1,   680,    -1,    81,    -1,    -1,
      -1,   559,    -1,    -1,    -1,    89,   629,    -1,    92,    -1,
     787,   634,    -1,    97,    -1,    -1,   100,    -1,    -1,    -1,
      -1,   105,   580,   107,    -1,   109,   110,   111,    -1,    -1,
      -1,    -1,    -1,    71,    72,   658,   594,    -1,    -1,    -1,
     775,    79,    -1,    58,   602,    -1,    61,    -1,   733,    98,
      -1,   100,    90,   788,   103,    93,   105,   680,    73,    74,
     109,    99,   620,    -1,    -1,    -1,    81,    -1,    -1,    -1,
     119,   629,   110,   111,    89,    -1,   634,    -1,    -1,    -1,
     703,    -1,    97,    -1,    -1,   100,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,   829,    -1,   111,    -1,    -1,    -1,
     658,   150,   151,   152,   153,   154,   155,    -1,    -1,    -1,
     887,    58,    -1,   671,   672,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   680,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    33,    34,   715,    -1,
      -1,   718,    89,    -1,   829,   703,    43,    -1,    -1,    46,
      -1,    -1,   775,   100,    -1,    52,   841,    54,   105,    -1,
     107,    58,   109,   110,   111,   788,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,    -1,   829,    -1,   105,    -1,
     107,    -1,   109,   110,   111,   112,   113,   775,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     788,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      97,   829,    99,   100,    -1,    -1,    -1,   104,   105,   328,
     107,    -1,    -1,   110,   111,    -1,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,    -1,    -1,   356,   357,    -1,
     359,    -1,    -1,    -1,    33,    34,    -1,   366,    -1,    -1,
      -1,   370,    -1,    -1,    43,    -1,    -1,    46,    -1,    -1,
     379,    -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    73,    74,    -1,   406,    77,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    -1,    33,    34,    -1,
      99,   100,    -1,    -1,   433,    -1,   105,    43,   107,    -1,
      46,   110,   111,   112,   113,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    -1,   485,    93,    -1,    -1,
      -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,
      -1,   107,    -1,    -1,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,   512,    -1,    -1,   515,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,   537,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,   546,    54,    -1,
     549,    -1,    58,   552,    -1,    -1,   555,    63,   557,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,   568,
      -1,    77,    -1,    79,    -1,    81,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,    -1,
      -1,    46,    47,    99,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,   110,   111,   112,   113,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,   624,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,   110,   111,   112,   113,    43,
     659,   660,   661,    47,    -1,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,   695,    81,   697,    -1,
     699,   700,   701,    -1,   703,   704,    90,    70,    -1,    93,
      -1,    -1,    75,    76,    -1,    99,    -1,    80,    -1,    -1,
      83,    84,    85,    -1,    -1,    -1,   110,   111,   112,   113,
      93,    -1,    95,    96,    -1,    -1,    -1,    -1,   101,   738,
      -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,    -1,    -1,   772,   773,    -1,   775,    -1,    -1,   778,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   788,
      -1,    33,    34,    -1,    -1,    -1,   795,    -1,    -1,   798,
      -1,    43,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    63,    -1,   822,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,   844,   845,    -1,    90,    -1,
     849,    93,    -1,   852,    -1,    -1,    -1,    99,    -1,    -1,
     859,   860,   861,    -1,    -1,    -1,    -1,    -1,   110,   111,
     112,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   878,
      -1,   880,    22,    23,    -1,    -1,    26,    27,    -1,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    22,    -1,    -1,    -1,    26,    27,
      -1,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    22,    -1,    -1,    -1,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    56,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,
      46,    47,    -1,    -1,    99,    -1,    52,    -1,    54,    -1,
      56,    -1,    58,    -1,    -1,   110,   111,   112,   113,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,    -1,
      -1,    46,    -1,    99,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,   110,   111,   112,   113,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,    -1,    81,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,
      46,    -1,    -1,    -1,    99,    -1,    52,    53,    54,    -1,
      56,    -1,    58,    -1,    -1,   110,   111,   112,   113,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,    -1,
      -1,    46,    -1,    99,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,   110,   111,   112,   113,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,    -1,    81,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    43,
      -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,   110,   111,   112,   113,    63,
      -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    46,    -1,    -1,    -1,    99,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    60,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,    -1,
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
      90,    -1,    -1,    93,    -1,    47,    -1,    97,    98,    99,
     100,    -1,   102,    -1,    -1,   105,    58,   107,    60,    61,
     110,   111,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    86,    47,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    97,    58,    99,   100,    61,
      -1,    -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    58,   100,    -1,
      -1,    -1,    63,   105,    -1,   107,    -1,   109,   110,   111,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      58,    -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,
     111,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,   100,    58,    -1,    -1,    -1,   105,    -1,   107,
      -1,   109,   110,   111,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    58,    99,   100,    61,    -1,    -1,    -1,
     105,    -1,   107,    -1,    -1,   110,   111,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,   100,    -1,    -1,    -1,    -1,
     105,    -1,   107,    -1,    -1,    -1,   111,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    -1,    64,    65,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    -1,    64,    65,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    45,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    45,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
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
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    60,    -1,    62,    26,    27,    28,    29,    30,    31,
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
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    56,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    26,    27,    28,    62,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    26,
      27,    28,    62,    -1,    -1,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    28,    -1,    -1,    62,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    -1,    58,    28,    -1,    -1,    62,    -1,    33,    34,
      35,    36,    37,    38,    39,    -1,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    28,    -1,    -1,    62,    -1,    33,
      34,    35,    36,    37,    38,    39,    -1,    41,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    28,    -1,    -1,    62,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62
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
     248,   250,   253,    71,    72,    79,    90,    93,    99,   110,
     111,   123,   124,    48,    49,   265,    46,   265,    46,   124,
     265,   265,    70,    75,    76,    80,    83,    84,    85,    93,
      95,    96,   101,   106,    81,   129,   187,    60,   111,    52,
      60,   145,    60,   145,   127,   128,   230,    52,    44,   265,
      44,   124,    60,    44,    52,    52,   113,   124,   221,    52,
     113,   221,   130,    63,   109,   123,   187,   199,   200,    52,
     113,   124,   187,   124,   111,   124,   187,   110,   123,   124,
     184,   187,   124,   124,   127,   187,   204,   124,   124,   124,
     187,   204,    52,   127,   134,   135,   136,   148,    46,    46,
      33,    34,    43,    46,    52,    54,    63,    66,    67,    68,
      81,   112,   113,   123,   124,   146,   188,   190,   193,   254,
     255,   256,   262,   263,   123,   262,   200,   262,   196,   197,
     265,   124,   132,   133,   257,   262,   130,   262,    50,    51,
     266,    47,    56,   262,   266,    47,    22,    23,    26,    27,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   131,    56,   266,   262,   266,    52,
     124,   175,   215,   124,   181,    60,    60,   206,   210,   124,
     124,   139,   153,   196,   124,   124,   254,    87,    88,    94,
     137,    53,    56,    46,   177,   231,   262,   262,   262,   132,
     257,    81,   187,   190,   193,   262,   262,    58,    59,   123,
      52,    58,   259,    53,    56,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    50,    51,    52,    57,    62,   259,   265,
      45,   266,    45,   185,   124,   198,    59,    45,    56,    45,
      56,    53,    53,   124,    53,   130,   199,    53,   134,    59,
     196,    46,   216,   196,   196,   196,   196,   196,    46,    53,
     187,   136,   150,    72,   127,   128,   141,   178,   187,   238,
     248,   249,   250,   232,    47,    47,    53,    53,   124,   262,
     254,   260,   124,   256,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,    50,   254,   262,   262,    63,   109,   187,
     201,   202,   262,    52,    56,   266,   262,   133,   262,   266,
     266,    53,   266,    53,   252,   262,   176,   221,    46,   182,
     207,   211,   140,   154,   212,   124,   124,   127,   141,   151,
     155,   156,   172,   249,   250,   179,   230,   103,   187,   124,
      47,    60,    68,    82,    86,    98,   102,   123,   127,   141,
     146,   190,   223,   224,   225,   226,   227,   228,   229,   230,
     233,   237,   249,   250,   258,   261,   262,    53,   124,    59,
      60,    45,    55,   262,    53,    55,    56,   266,   134,   124,
     230,    60,    52,    47,   124,   217,   218,    46,    46,    46,
      52,    52,    47,   127,   213,    59,    60,    59,    99,   108,
     127,   149,   156,    47,   124,   124,    59,   251,    60,    52,
      60,   262,    52,   123,    58,    44,    52,    59,   259,   265,
      46,   142,   262,   262,   199,    52,    53,   134,    59,    47,
      56,   183,   212,   212,   134,   134,   187,   142,   262,   124,
     265,    47,    46,   251,   252,    60,   262,    60,   262,    72,
     262,   254,   262,   200,   143,    60,    45,   254,    53,   252,
     218,    47,   127,   186,    47,    47,    53,    53,   124,    60,
     157,   190,   191,   194,    71,    90,   127,   239,   240,    60,
      53,    53,    52,    45,    55,    53,    60,   266,    47,   128,
     141,   144,   253,    53,    69,   111,   184,    60,    46,   266,
     266,   266,    59,    59,    75,   126,    47,   240,   190,   229,
      46,   254,   262,    60,    52,   184,    52,    60,   158,    52,
      52,    52,    46,    46,    72,    79,    93,    99,   110,   111,
     125,    78,   234,    53,    45,   254,    60,   134,   104,   127,
     128,   159,   160,   162,   187,   223,   224,   227,   228,   249,
     250,   262,   262,   262,   243,   241,    59,    59,   229,    33,
      34,    43,    47,    52,    54,    66,    67,    68,    77,    81,
     112,   113,   123,   146,   188,   190,   235,   236,   264,    60,
      53,    53,    91,   124,   163,   164,    46,   187,    47,    53,
      53,    53,    47,   127,   244,    47,   242,   262,    46,   252,
     262,   262,   262,   187,   262,   262,    58,   123,    52,   259,
      55,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    44,    50,
      51,    52,    57,    62,   259,   265,    60,    60,    52,    60,
     161,   124,   124,   124,   146,   245,   258,    55,    52,    63,
      77,   167,   168,   171,   246,   247,   262,    60,    53,    53,
     124,   254,   230,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,    50,   254,   262,   262,   202,   262,   257,   158,
      60,    60,    60,    60,    52,   124,    63,    77,   170,   171,
     262,    55,    47,   246,    64,    65,   262,    53,    45,    55,
     262,    53,    55,   266,    53,    47,   254,   127,    53,    56,
      64,    65,   245,   262,   262,   262,   262,    52,    46,    53,
      60,   169,   171,   262,   262,   127,    45,   254,   165,    53,
      56,    60,    53,    47,   166,   167,   171,    55,   124,    60
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
     221,   222,   222,   222,   222,   223,   223,   223,   224,   225,
     226,   226,   227,   227,   228,   229,   229,   229,   229,   229,
     229,   229,   229,   231,   230,   232,   232,   233,   234,   234,
     235,   235,   236,   236,   237,   237,   237,   237,   238,   239,
     239,   240,   240,   240,   240,   241,   241,   242,   243,   243,
     244,   245,   245,   246,   247,   247,   248,   249,   249,   250,
     251,   251,   252,   253,   254,   254,   255,   255,   256,   256,
     256,   257,   257,   257,   258,   258,   260,   259,   261,   261,
     261,   261,   261,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   262,   262,   262,   262,   262,
     262,   262,   262,   262,   262,   263,   263,   263,   263,   263,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,   264,   264,
     264,   264,   264,   265,   265,   266,   266
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
       3,     4,     4,     4,     4,     5,     8,     4,     1,     2,
       2,     3,     5,     7,     7,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     5,     0,     2,     7,     0,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     6,     1,
       2,     5,     5,     7,     6,     0,     2,     5,     0,     2,
       3,     1,     4,     5,     1,     2,     7,     5,     4,     7,
       0,     2,     1,     2,     0,     1,     1,     3,     1,     3,
       1,     0,     1,     3,     1,     2,     0,     3,     1,     1,
       2,     4,     6,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     3,     3,     3,     2,     2,     2,     2,     2,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     1,     0,     7,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     2,     4,     6,     3,
       2,     2,     2,     2,     2,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     7,
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
#line 2819 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2825 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2831 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2837 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2843 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2849 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2855 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2861 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2867 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2873 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2879 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2885 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2891 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2897 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2903 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2909 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2915 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2921 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2927 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2933 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2939 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2945 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2951 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2957 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2963 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2969 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2975 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2981 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2987 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2993 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2999 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 3005 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 3011 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3017 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3023 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3029 "p4parser.tab.c"
    break;

  case 40:
#line 312 "p4parser.y"
        {}
#line 3035 "p4parser.tab.c"
    break;

  case 41:
#line 316 "p4parser.y"
        {}
#line 3041 "p4parser.tab.c"
    break;

  case 42:
#line 320 "p4parser.y"
              {}
#line 3047 "p4parser.tab.c"
    break;

  case 43:
#line 322 "p4parser.y"
        {}
#line 3053 "p4parser.tab.c"
    break;

  case 44:
#line 324 "p4parser.y"
        {}
#line 3059 "p4parser.tab.c"
    break;

  case 45:
#line 328 "p4parser.y"
                       {}
#line 3065 "p4parser.tab.c"
    break;

  case 46:
#line 329 "p4parser.y"
                       {}
#line 3071 "p4parser.tab.c"
    break;

  case 47:
#line 330 "p4parser.y"
                       {}
#line 3077 "p4parser.tab.c"
    break;

  case 48:
#line 331 "p4parser.y"
                       {}
#line 3083 "p4parser.tab.c"
    break;

  case 49:
#line 332 "p4parser.y"
                       {}
#line 3089 "p4parser.tab.c"
    break;

  case 50:
#line 333 "p4parser.y"
                       {}
#line 3095 "p4parser.tab.c"
    break;

  case 51:
#line 334 "p4parser.y"
                       {}
#line 3101 "p4parser.tab.c"
    break;

  case 52:
#line 335 "p4parser.y"
                       {}
#line 3107 "p4parser.tab.c"
    break;

  case 53:
#line 336 "p4parser.y"
                       {}
#line 3113 "p4parser.tab.c"
    break;

  case 54:
#line 337 "p4parser.y"
                       {}
#line 3119 "p4parser.tab.c"
    break;

  case 55:
#line 338 "p4parser.y"
                       {}
#line 3125 "p4parser.tab.c"
    break;

  case 56:
#line 339 "p4parser.y"
                       {}
#line 3131 "p4parser.tab.c"
    break;

  case 57:
#line 340 "p4parser.y"
                       {}
#line 3137 "p4parser.tab.c"
    break;

  case 58:
#line 341 "p4parser.y"
                       {}
#line 3143 "p4parser.tab.c"
    break;

  case 59:
#line 342 "p4parser.y"
                       {}
#line 3149 "p4parser.tab.c"
    break;

  case 60:
#line 343 "p4parser.y"
                       {}
#line 3155 "p4parser.tab.c"
    break;

  case 61:
#line 344 "p4parser.y"
                       {}
#line 3161 "p4parser.tab.c"
    break;

  case 62:
#line 345 "p4parser.y"
                       {}
#line 3167 "p4parser.tab.c"
    break;

  case 63:
#line 346 "p4parser.y"
                       {}
#line 3173 "p4parser.tab.c"
    break;

  case 64:
#line 347 "p4parser.y"
                       {}
#line 3179 "p4parser.tab.c"
    break;

  case 65:
#line 348 "p4parser.y"
                       {}
#line 3185 "p4parser.tab.c"
    break;

  case 66:
#line 349 "p4parser.y"
                       {}
#line 3191 "p4parser.tab.c"
    break;

  case 67:
#line 350 "p4parser.y"
                       {}
#line 3197 "p4parser.tab.c"
    break;

  case 68:
#line 351 "p4parser.y"
                       {}
#line 3203 "p4parser.tab.c"
    break;

  case 69:
#line 352 "p4parser.y"
                       {}
#line 3209 "p4parser.tab.c"
    break;

  case 70:
#line 353 "p4parser.y"
                       {}
#line 3215 "p4parser.tab.c"
    break;

  case 71:
#line 354 "p4parser.y"
                       {}
#line 3221 "p4parser.tab.c"
    break;

  case 72:
#line 355 "p4parser.y"
                       {}
#line 3227 "p4parser.tab.c"
    break;

  case 73:
#line 356 "p4parser.y"
                       {}
#line 3233 "p4parser.tab.c"
    break;

  case 74:
#line 357 "p4parser.y"
                       {}
#line 3239 "p4parser.tab.c"
    break;

  case 75:
#line 358 "p4parser.y"
                       {}
#line 3245 "p4parser.tab.c"
    break;

  case 76:
#line 359 "p4parser.y"
                       {}
#line 3251 "p4parser.tab.c"
    break;

  case 77:
#line 360 "p4parser.y"
                       {}
#line 3257 "p4parser.tab.c"
    break;

  case 78:
#line 361 "p4parser.y"
                       {}
#line 3263 "p4parser.tab.c"
    break;

  case 79:
#line 362 "p4parser.y"
                       {}
#line 3269 "p4parser.tab.c"
    break;

  case 80:
#line 363 "p4parser.y"
                       {}
#line 3275 "p4parser.tab.c"
    break;

  case 81:
#line 364 "p4parser.y"
                       {}
#line 3281 "p4parser.tab.c"
    break;

  case 82:
#line 365 "p4parser.y"
                       {}
#line 3287 "p4parser.tab.c"
    break;

  case 83:
#line 366 "p4parser.y"
                       {}
#line 3293 "p4parser.tab.c"
    break;

  case 84:
#line 367 "p4parser.y"
                       {}
#line 3299 "p4parser.tab.c"
    break;

  case 85:
#line 368 "p4parser.y"
                       {}
#line 3305 "p4parser.tab.c"
    break;

  case 86:
#line 369 "p4parser.y"
                       {}
#line 3311 "p4parser.tab.c"
    break;

  case 87:
#line 370 "p4parser.y"
                       {}
#line 3317 "p4parser.tab.c"
    break;

  case 88:
#line 371 "p4parser.y"
                       {}
#line 3323 "p4parser.tab.c"
    break;

  case 89:
#line 372 "p4parser.y"
                       {}
#line 3329 "p4parser.tab.c"
    break;

  case 90:
#line 373 "p4parser.y"
                            {}
#line 3335 "p4parser.tab.c"
    break;

  case 91:
#line 375 "p4parser.y"
                       {}
#line 3341 "p4parser.tab.c"
    break;

  case 92:
#line 376 "p4parser.y"
                       {}
#line 3347 "p4parser.tab.c"
    break;

  case 93:
#line 377 "p4parser.y"
                       {}
#line 3353 "p4parser.tab.c"
    break;

  case 94:
#line 378 "p4parser.y"
                       {}
#line 3359 "p4parser.tab.c"
    break;

  case 95:
#line 379 "p4parser.y"
                       {}
#line 3365 "p4parser.tab.c"
    break;

  case 96:
#line 380 "p4parser.y"
                       {}
#line 3371 "p4parser.tab.c"
    break;

  case 97:
#line 381 "p4parser.y"
                       {}
#line 3377 "p4parser.tab.c"
    break;

  case 98:
#line 382 "p4parser.y"
                       {}
#line 3383 "p4parser.tab.c"
    break;

  case 99:
#line 383 "p4parser.y"
                       {}
#line 3389 "p4parser.tab.c"
    break;

  case 100:
#line 384 "p4parser.y"
                       {}
#line 3395 "p4parser.tab.c"
    break;

  case 101:
#line 385 "p4parser.y"
                       {}
#line 3401 "p4parser.tab.c"
    break;

  case 102:
#line 386 "p4parser.y"
                       {}
#line 3407 "p4parser.tab.c"
    break;

  case 103:
#line 387 "p4parser.y"
                       {}
#line 3413 "p4parser.tab.c"
    break;

  case 104:
#line 388 "p4parser.y"
                       {}
#line 3419 "p4parser.tab.c"
    break;

  case 105:
#line 389 "p4parser.y"
                       {}
#line 3425 "p4parser.tab.c"
    break;

  case 106:
#line 390 "p4parser.y"
                       {}
#line 3431 "p4parser.tab.c"
    break;

  case 108:
#line 392 "p4parser.y"
                       {}
#line 3437 "p4parser.tab.c"
    break;

  case 109:
#line 393 "p4parser.y"
                       {}
#line 3443 "p4parser.tab.c"
    break;

  case 110:
#line 394 "p4parser.y"
                       {}
#line 3449 "p4parser.tab.c"
    break;

  case 111:
#line 395 "p4parser.y"
                       {}
#line 3455 "p4parser.tab.c"
    break;

  case 112:
#line 396 "p4parser.y"
                       {}
#line 3461 "p4parser.tab.c"
    break;

  case 113:
#line 397 "p4parser.y"
                       {}
#line 3467 "p4parser.tab.c"
    break;

  case 114:
#line 398 "p4parser.y"
                       {}
#line 3473 "p4parser.tab.c"
    break;

  case 115:
#line 399 "p4parser.y"
                       {}
#line 3479 "p4parser.tab.c"
    break;

  case 116:
#line 400 "p4parser.y"
                       {}
#line 3485 "p4parser.tab.c"
    break;

  case 117:
#line 401 "p4parser.y"
                       {}
#line 3491 "p4parser.tab.c"
    break;

  case 118:
#line 402 "p4parser.y"
                       {}
#line 3497 "p4parser.tab.c"
    break;

  case 119:
#line 403 "p4parser.y"
                       {}
#line 3503 "p4parser.tab.c"
    break;

  case 120:
#line 404 "p4parser.y"
                       {}
#line 3509 "p4parser.tab.c"
    break;

  case 121:
#line 405 "p4parser.y"
                       {}
#line 3515 "p4parser.tab.c"
    break;

  case 122:
#line 406 "p4parser.y"
                       {}
#line 3521 "p4parser.tab.c"
    break;

  case 123:
#line 407 "p4parser.y"
                       {}
#line 3527 "p4parser.tab.c"
    break;

  case 124:
#line 408 "p4parser.y"
                       {}
#line 3533 "p4parser.tab.c"
    break;

  case 125:
#line 409 "p4parser.y"
                       {}
#line 3539 "p4parser.tab.c"
    break;

  case 126:
#line 410 "p4parser.y"
                       {}
#line 3545 "p4parser.tab.c"
    break;

  case 127:
#line 411 "p4parser.y"
                       {}
#line 3551 "p4parser.tab.c"
    break;

  case 128:
#line 412 "p4parser.y"
                       {}
#line 3557 "p4parser.tab.c"
    break;

  case 129:
#line 413 "p4parser.y"
                       {}
#line 3563 "p4parser.tab.c"
    break;

  case 130:
#line 414 "p4parser.y"
                       {}
#line 3569 "p4parser.tab.c"
    break;

  case 131:
#line 418 "p4parser.y"
                                      {}
#line 3575 "p4parser.tab.c"
    break;

  case 132:
#line 419 "p4parser.y"
                                        {}
#line 3581 "p4parser.tab.c"
    break;

  case 133:
#line 423 "p4parser.y"
                                         {}
#line 3587 "p4parser.tab.c"
    break;

  case 134:
#line 427 "p4parser.y"
                                      {}
#line 3593 "p4parser.tab.c"
    break;

  case 135:
#line 428 "p4parser.y"
                                      {}
#line 3599 "p4parser.tab.c"
    break;

  case 136:
#line 432 "p4parser.y"
                                          {}
#line 3605 "p4parser.tab.c"
    break;

  case 137:
#line 433 "p4parser.y"
                                            {}
#line 3611 "p4parser.tab.c"
    break;

  case 138:
#line 437 "p4parser.y"
                                            {}
#line 3617 "p4parser.tab.c"
    break;

  case 139:
#line 438 "p4parser.y"
                                                              {}
#line 3623 "p4parser.tab.c"
    break;

  case 140:
#line 442 "p4parser.y"
                 {}
#line 3629 "p4parser.tab.c"
    break;

  case 141:
#line 443 "p4parser.y"
                   {}
#line 3635 "p4parser.tab.c"
    break;

  case 142:
#line 444 "p4parser.y"
                   {}
#line 3641 "p4parser.tab.c"
    break;

  case 143:
#line 445 "p4parser.y"
                   {}
#line 3647 "p4parser.tab.c"
    break;

  case 144:
#line 449 "p4parser.y"
                                  {}
#line 3653 "p4parser.tab.c"
    break;

  case 145:
#line 450 "p4parser.y"
                        {}
#line 3659 "p4parser.tab.c"
    break;

  case 146:
#line 451 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3668 "p4parser.tab.c"
    break;

  case 147:
#line 459 "p4parser.y"
                     {}
#line 3674 "p4parser.tab.c"
    break;

  case 148:
#line 461 "p4parser.y"
                     {}
#line 3680 "p4parser.tab.c"
    break;

  case 149:
#line 464 "p4parser.y"
                     {}
#line 3686 "p4parser.tab.c"
    break;

  case 150:
#line 467 "p4parser.y"
                     {}
#line 3692 "p4parser.tab.c"
    break;

  case 151:
#line 473 "p4parser.y"
                               {}
#line 3698 "p4parser.tab.c"
    break;

  case 152:
#line 477 "p4parser.y"
                                     {}
#line 3704 "p4parser.tab.c"
    break;

  case 153:
#line 478 "p4parser.y"
                                     {}
#line 3710 "p4parser.tab.c"
    break;

  case 154:
#line 482 "p4parser.y"
                               {}
#line 3716 "p4parser.tab.c"
    break;

  case 155:
#line 483 "p4parser.y"
                               {}
#line 3722 "p4parser.tab.c"
    break;

  case 156:
#line 487 "p4parser.y"
                           {}
#line 3728 "p4parser.tab.c"
    break;

  case 157:
#line 488 "p4parser.y"
                                     {}
#line 3734 "p4parser.tab.c"
    break;

  case 158:
#line 492 "p4parser.y"
                             {}
#line 3740 "p4parser.tab.c"
    break;

  case 159:
#line 498 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3746 "p4parser.tab.c"
    break;

  case 160:
#line 499 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3752 "p4parser.tab.c"
    break;

  case 161:
#line 500 "p4parser.y"
                             {}
#line 3758 "p4parser.tab.c"
    break;

  case 162:
#line 505 "p4parser.y"
                                           {}
#line 3764 "p4parser.tab.c"
    break;

  case 163:
#line 506 "p4parser.y"
                                             {}
#line 3770 "p4parser.tab.c"
    break;

  case 164:
#line 510 "p4parser.y"
                                    {}
#line 3776 "p4parser.tab.c"
    break;

  case 165:
#line 511 "p4parser.y"
                                      {}
#line 3782 "p4parser.tab.c"
    break;

  case 166:
#line 512 "p4parser.y"
                                      {}
#line 3788 "p4parser.tab.c"
    break;

  case 167:
#line 513 "p4parser.y"
                                      {}
#line 3794 "p4parser.tab.c"
    break;

  case 168:
#line 518 "p4parser.y"
                          {}
#line 3800 "p4parser.tab.c"
    break;

  case 169:
#line 519 "p4parser.y"
                          {}
#line 3806 "p4parser.tab.c"
    break;

  case 170:
#line 520 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3815 "p4parser.tab.c"
    break;

  case 171:
#line 527 "p4parser.y"
                                    {}
#line 3821 "p4parser.tab.c"
    break;

  case 172:
#line 528 "p4parser.y"
                                      {}
#line 3827 "p4parser.tab.c"
    break;

  case 173:
#line 532 "p4parser.y"
                              {}
#line 3833 "p4parser.tab.c"
    break;

  case 174:
#line 534 "p4parser.y"
                                      {}
#line 3839 "p4parser.tab.c"
    break;

  case 175:
#line 538 "p4parser.y"
                                     {}
#line 3845 "p4parser.tab.c"
    break;

  case 176:
#line 539 "p4parser.y"
                                       {}
#line 3851 "p4parser.tab.c"
    break;

  case 177:
#line 543 "p4parser.y"
                                    {}
#line 3857 "p4parser.tab.c"
    break;

  case 178:
#line 544 "p4parser.y"
                                      {}
#line 3863 "p4parser.tab.c"
    break;

  case 179:
#line 545 "p4parser.y"
                                      {}
#line 3869 "p4parser.tab.c"
    break;

  case 180:
#line 546 "p4parser.y"
                                      {}
#line 3875 "p4parser.tab.c"
    break;

  case 181:
#line 547 "p4parser.y"
                                      {}
#line 3881 "p4parser.tab.c"
    break;

  case 182:
#line 548 "p4parser.y"
                                      {}
#line 3887 "p4parser.tab.c"
    break;

  case 183:
#line 549 "p4parser.y"
                                      {}
#line 3893 "p4parser.tab.c"
    break;

  case 184:
#line 553 "p4parser.y"
                           {}
#line 3899 "p4parser.tab.c"
    break;

  case 185:
#line 554 "p4parser.y"
                               {}
#line 3905 "p4parser.tab.c"
    break;

  case 186:
#line 558 "p4parser.y"
                                {}
#line 3911 "p4parser.tab.c"
    break;

  case 187:
#line 559 "p4parser.y"
                                  {}
#line 3917 "p4parser.tab.c"
    break;

  case 188:
#line 563 "p4parser.y"
                           {}
#line 3923 "p4parser.tab.c"
    break;

  case 189:
#line 564 "p4parser.y"
                       {}
#line 3929 "p4parser.tab.c"
    break;

  case 190:
#line 569 "p4parser.y"
                              {}
#line 3935 "p4parser.tab.c"
    break;

  case 191:
#line 573 "p4parser.y"
                               {}
#line 3941 "p4parser.tab.c"
    break;

  case 192:
#line 574 "p4parser.y"
                                 {}
#line 3947 "p4parser.tab.c"
    break;

  case 193:
#line 579 "p4parser.y"
      {}
#line 3953 "p4parser.tab.c"
    break;

  case 194:
#line 583 "p4parser.y"
                              {}
#line 3959 "p4parser.tab.c"
    break;

  case 195:
#line 584 "p4parser.y"
                                {}
#line 3965 "p4parser.tab.c"
    break;

  case 196:
#line 589 "p4parser.y"
                                {}
#line 3971 "p4parser.tab.c"
    break;

  case 197:
#line 590 "p4parser.y"
                                                    {}
#line 3977 "p4parser.tab.c"
    break;

  case 198:
#line 594 "p4parser.y"
                           {}
#line 3983 "p4parser.tab.c"
    break;

  case 199:
#line 595 "p4parser.y"
                                                        {}
#line 3989 "p4parser.tab.c"
    break;

  case 200:
#line 600 "p4parser.y"
                                 {}
#line 3995 "p4parser.tab.c"
    break;

  case 201:
#line 601 "p4parser.y"
                                   {}
#line 4001 "p4parser.tab.c"
    break;

  case 202:
#line 602 "p4parser.y"
                                  {}
#line 4007 "p4parser.tab.c"
    break;

  case 203:
#line 603 "p4parser.y"
                                       {}
#line 4013 "p4parser.tab.c"
    break;

  case 204:
#line 607 "p4parser.y"
                                {}
#line 4019 "p4parser.tab.c"
    break;

  case 205:
#line 608 "p4parser.y"
                                 {}
#line 4025 "p4parser.tab.c"
    break;

  case 206:
#line 609 "p4parser.y"
                                   {}
#line 4031 "p4parser.tab.c"
    break;

  case 207:
#line 610 "p4parser.y"
                                  {}
#line 4037 "p4parser.tab.c"
    break;

  case 208:
#line 611 "p4parser.y"
                                       {}
#line 4043 "p4parser.tab.c"
    break;

  case 209:
#line 617 "p4parser.y"
        {}
#line 4049 "p4parser.tab.c"
    break;

  case 210:
#line 620 "p4parser.y"
        {}
#line 4055 "p4parser.tab.c"
    break;

  case 211:
#line 623 "p4parser.y"
        {}
#line 4061 "p4parser.tab.c"
    break;

  case 212:
#line 631 "p4parser.y"
        {}
#line 4067 "p4parser.tab.c"
    break;

  case 213:
#line 636 "p4parser.y"
                     {}
#line 4073 "p4parser.tab.c"
    break;

  case 214:
#line 637 "p4parser.y"
                          {}
#line 4079 "p4parser.tab.c"
    break;

  case 215:
#line 638 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4088 "p4parser.tab.c"
    break;

  case 216:
#line 645 "p4parser.y"
           {}
#line 4094 "p4parser.tab.c"
    break;

  case 217:
#line 646 "p4parser.y"
                                                       {}
#line 4100 "p4parser.tab.c"
    break;

  case 218:
#line 650 "p4parser.y"
                             {}
#line 4106 "p4parser.tab.c"
    break;

  case 219:
#line 651 "p4parser.y"
                               {}
#line 4112 "p4parser.tab.c"
    break;

  case 220:
#line 652 "p4parser.y"
                               {}
#line 4118 "p4parser.tab.c"
    break;

  case 221:
#line 653 "p4parser.y"
                               {}
#line 4124 "p4parser.tab.c"
    break;

  case 222:
#line 654 "p4parser.y"
                               {}
#line 4130 "p4parser.tab.c"
    break;

  case 223:
#line 658 "p4parser.y"
                   {}
#line 4136 "p4parser.tab.c"
    break;

  case 224:
#line 665 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4145 "p4parser.tab.c"
    break;

  case 225:
#line 669 "p4parser.y"
                          {}
#line 4151 "p4parser.tab.c"
    break;

  case 227:
#line 671 "p4parser.y"
                                                        { bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 2)); }
#line 4157 "p4parser.tab.c"
    break;

  case 229:
#line 676 "p4parser.y"
                                     {}
#line 4163 "p4parser.tab.c"
    break;

  case 230:
#line 677 "p4parser.y"
                                       {}
#line 4169 "p4parser.tab.c"
    break;

  case 231:
#line 682 "p4parser.y"
                               {}
#line 4175 "p4parser.tab.c"
    break;

  case 232:
#line 683 "p4parser.y"
                                      {}
#line 4181 "p4parser.tab.c"
    break;

  case 233:
#line 687 "p4parser.y"
                                               {}
#line 4187 "p4parser.tab.c"
    break;

  case 234:
#line 688 "p4parser.y"
                                                          {}
#line 4193 "p4parser.tab.c"
    break;

  case 235:
#line 690 "p4parser.y"
                                        {}
#line 4199 "p4parser.tab.c"
    break;

  case 236:
#line 696 "p4parser.y"
                                     {}
#line 4205 "p4parser.tab.c"
    break;

  case 237:
#line 697 "p4parser.y"
                                       {}
#line 4211 "p4parser.tab.c"
    break;

  case 238:
#line 698 "p4parser.y"
                                       {}
#line 4217 "p4parser.tab.c"
    break;

  case 239:
#line 699 "p4parser.y"
                                       {}
#line 4223 "p4parser.tab.c"
    break;

  case 240:
#line 700 "p4parser.y"
                                       {}
#line 4229 "p4parser.tab.c"
    break;

  case 241:
#line 704 "p4parser.y"
                                     {}
#line 4235 "p4parser.tab.c"
    break;

  case 242:
#line 705 "p4parser.y"
                                       {}
#line 4241 "p4parser.tab.c"
    break;

  case 243:
#line 709 "p4parser.y"
                                     {}
#line 4247 "p4parser.tab.c"
    break;

  case 244:
#line 710 "p4parser.y"
                                       {}
#line 4253 "p4parser.tab.c"
    break;

  case 245:
#line 714 "p4parser.y"
                                     {}
#line 4259 "p4parser.tab.c"
    break;

  case 246:
#line 718 "p4parser.y"
                                              {}
#line 4265 "p4parser.tab.c"
    break;

  case 247:
#line 722 "p4parser.y"
                                                    {}
#line 4271 "p4parser.tab.c"
    break;

  case 248:
#line 723 "p4parser.y"
                                                      {}
#line 4277 "p4parser.tab.c"
    break;

  case 249:
#line 727 "p4parser.y"
                                              {}
#line 4283 "p4parser.tab.c"
    break;

  case 250:
#line 731 "p4parser.y"
           {}
#line 4289 "p4parser.tab.c"
    break;

  case 251:
#line 732 "p4parser.y"
             {}
#line 4295 "p4parser.tab.c"
    break;

  case 252:
#line 733 "p4parser.y"
             {}
#line 4301 "p4parser.tab.c"
    break;

  case 253:
#line 734 "p4parser.y"
             {}
#line 4307 "p4parser.tab.c"
    break;

  case 254:
#line 735 "p4parser.y"
             {}
#line 4313 "p4parser.tab.c"
    break;

  case 255:
#line 737 "p4parser.y"
      {}
#line 4319 "p4parser.tab.c"
    break;

  case 256:
#line 739 "p4parser.y"
      {}
#line 4325 "p4parser.tab.c"
    break;

  case 257:
#line 741 "p4parser.y"
      {}
#line 4331 "p4parser.tab.c"
    break;

  case 258:
#line 744 "p4parser.y"
      {}
#line 4337 "p4parser.tab.c"
    break;

  case 259:
#line 746 "p4parser.y"
      {}
#line 4343 "p4parser.tab.c"
    break;

  case 260:
#line 748 "p4parser.y"
      {}
#line 4349 "p4parser.tab.c"
    break;

  case 261:
#line 752 "p4parser.y"
                {}
#line 4355 "p4parser.tab.c"
    break;

  case 262:
#line 753 "p4parser.y"
                  {}
#line 4361 "p4parser.tab.c"
    break;

  case 263:
#line 754 "p4parser.y"
                  {}
#line 4367 "p4parser.tab.c"
    break;

  case 264:
#line 759 "p4parser.y"
                              {}
#line 4373 "p4parser.tab.c"
    break;

  case 265:
#line 760 "p4parser.y"
                                {}
#line 4379 "p4parser.tab.c"
    break;

  case 266:
#line 764 "p4parser.y"
                                      {}
#line 4385 "p4parser.tab.c"
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
#line 4397 "p4parser.tab.c"
    break;

  case 268:
#line 775 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4405 "p4parser.tab.c"
    break;

  case 269:
#line 781 "p4parser.y"
                                {}
#line 4411 "p4parser.tab.c"
    break;

  case 270:
#line 782 "p4parser.y"
                                  {}
#line 4417 "p4parser.tab.c"
    break;

  case 271:
#line 784 "p4parser.y"
                                  {}
#line 4423 "p4parser.tab.c"
    break;

  case 272:
#line 785 "p4parser.y"
                                       {}
#line 4429 "p4parser.tab.c"
    break;

  case 273:
#line 789 "p4parser.y"
                                   {}
#line 4435 "p4parser.tab.c"
    break;

  case 274:
#line 790 "p4parser.y"
                                     {}
#line 4441 "p4parser.tab.c"
    break;

  case 275:
#line 791 "p4parser.y"
                                       {}
#line 4447 "p4parser.tab.c"
    break;

  case 276:
#line 795 "p4parser.y"
                                {}
#line 4453 "p4parser.tab.c"
    break;

  case 277:
#line 796 "p4parser.y"
                                  {}
#line 4459 "p4parser.tab.c"
    break;

  case 278:
#line 797 "p4parser.y"
                                       {}
#line 4465 "p4parser.tab.c"
    break;

  case 279:
#line 803 "p4parser.y"
                                       {}
#line 4471 "p4parser.tab.c"
    break;

  case 280:
#line 804 "p4parser.y"
                                           {}
#line 4477 "p4parser.tab.c"
    break;

  case 281:
#line 808 "p4parser.y"
                               {}
#line 4483 "p4parser.tab.c"
    break;

  case 282:
#line 809 "p4parser.y"
                                       {}
#line 4489 "p4parser.tab.c"
    break;

  case 283:
#line 810 "p4parser.y"
                                       {}
#line 4495 "p4parser.tab.c"
    break;

  case 284:
#line 811 "p4parser.y"
                                       {}
#line 4501 "p4parser.tab.c"
    break;

  case 285:
#line 812 "p4parser.y"
                                       {}
#line 4507 "p4parser.tab.c"
    break;

  case 286:
#line 816 "p4parser.y"
                                     {}
#line 4513 "p4parser.tab.c"
    break;

  case 287:
#line 817 "p4parser.y"
                                       {}
#line 4519 "p4parser.tab.c"
    break;

  case 288:
#line 818 "p4parser.y"
                                       {}
#line 4525 "p4parser.tab.c"
    break;

  case 289:
#line 819 "p4parser.y"
                                       {}
#line 4531 "p4parser.tab.c"
    break;

  case 290:
#line 823 "p4parser.y"
                               {}
#line 4537 "p4parser.tab.c"
    break;

  case 291:
#line 823 "p4parser.y"
                                                    {}
#line 4543 "p4parser.tab.c"
    break;

  case 292:
#line 825 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4552 "p4parser.tab.c"
    break;

  case 293:
#line 834 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4561 "p4parser.tab.c"
    break;

  case 294:
#line 841 "p4parser.y"
                                     {}
#line 4567 "p4parser.tab.c"
    break;

  case 295:
#line 841 "p4parser.y"
                                                          {}
#line 4573 "p4parser.tab.c"
    break;

  case 296:
#line 842 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4582 "p4parser.tab.c"
    break;

  case 297:
#line 849 "p4parser.y"
                                     {}
#line 4588 "p4parser.tab.c"
    break;

  case 298:
#line 850 "p4parser.y"
                                       {}
#line 4594 "p4parser.tab.c"
    break;

  case 299:
#line 854 "p4parser.y"
                                           {}
#line 4600 "p4parser.tab.c"
    break;

  case 300:
#line 859 "p4parser.y"
                  {}
#line 4606 "p4parser.tab.c"
    break;

  case 301:
#line 860 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4615 "p4parser.tab.c"
    break;

  case 302:
#line 864 "p4parser.y"
                                       {}
#line 4621 "p4parser.tab.c"
    break;

  case 303:
#line 865 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4630 "p4parser.tab.c"
    break;

  case 304:
#line 872 "p4parser.y"
                            {}
#line 4636 "p4parser.tab.c"
    break;

  case 305:
#line 873 "p4parser.y"
                                                        {}
#line 4642 "p4parser.tab.c"
    break;

  case 306:
#line 877 "p4parser.y"
                               {}
#line 4648 "p4parser.tab.c"
    break;

  case 307:
#line 882 "p4parser.y"
        {}
#line 4654 "p4parser.tab.c"
    break;

  case 308:
#line 887 "p4parser.y"
        {}
#line 4660 "p4parser.tab.c"
    break;

  case 309:
#line 892 "p4parser.y"
                            {}
#line 4666 "p4parser.tab.c"
    break;

  case 310:
#line 893 "p4parser.y"
                                {}
#line 4672 "p4parser.tab.c"
    break;

  case 311:
#line 897 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4681 "p4parser.tab.c"
    break;

  case 312:
#line 901 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4690 "p4parser.tab.c"
    break;

  case 313:
#line 905 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4699 "p4parser.tab.c"
    break;

  case 314:
#line 909 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4708 "p4parser.tab.c"
    break;

  case 315:
#line 920 "p4parser.y"
        {}
#line 4714 "p4parser.tab.c"
    break;

  case 316:
#line 923 "p4parser.y"
        {}
#line 4720 "p4parser.tab.c"
    break;

  case 317:
#line 926 "p4parser.y"
        {}
#line 4726 "p4parser.tab.c"
    break;

  case 318:
#line 931 "p4parser.y"
                   {}
#line 4732 "p4parser.tab.c"
    break;

  case 319:
#line 935 "p4parser.y"
                   {}
#line 4738 "p4parser.tab.c"
    break;

  case 320:
#line 939 "p4parser.y"
                                {}
#line 4744 "p4parser.tab.c"
    break;

  case 321:
#line 940 "p4parser.y"
                                  {}
#line 4750 "p4parser.tab.c"
    break;

  case 322:
#line 945 "p4parser.y"
        {}
#line 4756 "p4parser.tab.c"
    break;

  case 323:
#line 947 "p4parser.y"
        {}
#line 4762 "p4parser.tab.c"
    break;

  case 324:
#line 952 "p4parser.y"
                                                              {}
#line 4768 "p4parser.tab.c"
    break;

  case 325:
#line 956 "p4parser.y"
                                     {}
#line 4774 "p4parser.tab.c"
    break;

  case 326:
#line 957 "p4parser.y"
                                       {}
#line 4780 "p4parser.tab.c"
    break;

  case 327:
#line 958 "p4parser.y"
                                       {}
#line 4786 "p4parser.tab.c"
    break;

  case 328:
#line 959 "p4parser.y"
                                       {}
#line 4792 "p4parser.tab.c"
    break;

  case 329:
#line 960 "p4parser.y"
                                       {}
#line 4798 "p4parser.tab.c"
    break;

  case 330:
#line 961 "p4parser.y"
                                       {}
#line 4804 "p4parser.tab.c"
    break;

  case 331:
#line 962 "p4parser.y"
                                       {}
#line 4810 "p4parser.tab.c"
    break;

  case 332:
#line 963 "p4parser.y"
                                       {}
#line 4816 "p4parser.tab.c"
    break;

  case 333:
#line 967 "p4parser.y"
                           {}
#line 4822 "p4parser.tab.c"
    break;

  case 334:
#line 968 "p4parser.y"
                             {}
#line 4828 "p4parser.tab.c"
    break;

  case 335:
#line 972 "p4parser.y"
                                          {}
#line 4834 "p4parser.tab.c"
    break;

  case 336:
#line 973 "p4parser.y"
                                            {}
#line 4840 "p4parser.tab.c"
    break;

  case 337:
#line 977 "p4parser.y"
                                                                  {}
#line 4846 "p4parser.tab.c"
    break;

  case 338:
#line 981 "p4parser.y"
                             {}
#line 4852 "p4parser.tab.c"
    break;

  case 339:
#line 982 "p4parser.y"
                               {}
#line 4858 "p4parser.tab.c"
    break;

  case 340:
#line 986 "p4parser.y"
                                     {}
#line 4864 "p4parser.tab.c"
    break;

  case 341:
#line 987 "p4parser.y"
                                       {}
#line 4870 "p4parser.tab.c"
    break;

  case 342:
#line 991 "p4parser.y"
                             {}
#line 4876 "p4parser.tab.c"
    break;

  case 343:
#line 992 "p4parser.y"
                               {}
#line 4882 "p4parser.tab.c"
    break;

  case 344:
#line 996 "p4parser.y"
                             {}
#line 4888 "p4parser.tab.c"
    break;

  case 345:
#line 997 "p4parser.y"
                               {}
#line 4894 "p4parser.tab.c"
    break;

  case 346:
#line 998 "p4parser.y"
                               {}
#line 4900 "p4parser.tab.c"
    break;

  case 347:
#line 999 "p4parser.y"
                               {}
#line 4906 "p4parser.tab.c"
    break;

  case 348:
#line 1007 "p4parser.y"
          {}
#line 4912 "p4parser.tab.c"
    break;

  case 349:
#line 1011 "p4parser.y"
                                       {}
#line 4918 "p4parser.tab.c"
    break;

  case 350:
#line 1012 "p4parser.y"
                                         {}
#line 4924 "p4parser.tab.c"
    break;

  case 351:
#line 1017 "p4parser.y"
        {}
#line 4930 "p4parser.tab.c"
    break;

  case 352:
#line 1019 "p4parser.y"
        {}
#line 4936 "p4parser.tab.c"
    break;

  case 353:
#line 1021 "p4parser.y"
        {}
#line 4942 "p4parser.tab.c"
    break;

  case 354:
#line 1023 "p4parser.y"
        {}
#line 4948 "p4parser.tab.c"
    break;

  case 355:
#line 1027 "p4parser.y"
                                       {}
#line 4954 "p4parser.tab.c"
    break;

  case 356:
#line 1028 "p4parser.y"
                                         {}
#line 4960 "p4parser.tab.c"
    break;

  case 357:
#line 1033 "p4parser.y"
                                         {}
#line 4966 "p4parser.tab.c"
    break;

  case 358:
#line 1037 "p4parser.y"
           {}
#line 4972 "p4parser.tab.c"
    break;

  case 359:
#line 1039 "p4parser.y"
        {}
#line 4978 "p4parser.tab.c"
    break;

  case 361:
#line 1048 "p4parser.y"
        {}
#line 4984 "p4parser.tab.c"
    break;

  case 362:
#line 1050 "p4parser.y"
        {}
#line 4990 "p4parser.tab.c"
    break;

  case 363:
#line 1055 "p4parser.y"
        {}
#line 4996 "p4parser.tab.c"
    break;

  case 364:
#line 1059 "p4parser.y"
                                   {}
#line 5002 "p4parser.tab.c"
    break;

  case 365:
#line 1060 "p4parser.y"
                                     {}
#line 5008 "p4parser.tab.c"
    break;

  case 366:
#line 1066 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 5017 "p4parser.tab.c"
    break;

  case 367:
#line 1075 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5026 "p4parser.tab.c"
    break;

  case 368:
#line 1079 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5035 "p4parser.tab.c"
    break;

  case 369:
#line 1087 "p4parser.y"
                                     {}
#line 5041 "p4parser.tab.c"
    break;

  case 370:
#line 1091 "p4parser.y"
                                     {}
#line 5047 "p4parser.tab.c"
    break;

  case 371:
#line 1092 "p4parser.y"
                                          {}
#line 5053 "p4parser.tab.c"
    break;

  case 372:
#line 1096 "p4parser.y"
                                        {}
#line 5059 "p4parser.tab.c"
    break;

  case 373:
#line 1102 "p4parser.y"
                                       {}
#line 5065 "p4parser.tab.c"
    break;

  case 374:
#line 1106 "p4parser.y"
                                       {}
#line 5071 "p4parser.tab.c"
    break;

  case 375:
#line 1107 "p4parser.y"
                                         {}
#line 5077 "p4parser.tab.c"
    break;

  case 376:
#line 1111 "p4parser.y"
                                       {}
#line 5083 "p4parser.tab.c"
    break;

  case 377:
#line 1112 "p4parser.y"
                                           {}
#line 5089 "p4parser.tab.c"
    break;

  case 378:
#line 1116 "p4parser.y"
                                       {}
#line 5095 "p4parser.tab.c"
    break;

  case 379:
#line 1117 "p4parser.y"
                                            {}
#line 5101 "p4parser.tab.c"
    break;

  case 380:
#line 1118 "p4parser.y"
                                              {}
#line 5107 "p4parser.tab.c"
    break;

  case 381:
#line 1122 "p4parser.y"
                                       {}
#line 5113 "p4parser.tab.c"
    break;

  case 382:
#line 1123 "p4parser.y"
                                         {}
#line 5119 "p4parser.tab.c"
    break;

  case 383:
#line 1124 "p4parser.y"
                                           {}
#line 5125 "p4parser.tab.c"
    break;

  case 384:
#line 1128 "p4parser.y"
                                       {}
#line 5131 "p4parser.tab.c"
    break;

  case 385:
#line 1129 "p4parser.y"
                                         {}
#line 5137 "p4parser.tab.c"
    break;

  case 386:
#line 1133 "p4parser.y"
        {}
#line 5143 "p4parser.tab.c"
    break;

  case 387:
#line 1133 "p4parser.y"
                {}
#line 5149 "p4parser.tab.c"
    break;

  case 388:
#line 1137 "p4parser.y"
                                       {}
#line 5155 "p4parser.tab.c"
    break;

  case 389:
#line 1138 "p4parser.y"
                                         {}
#line 5161 "p4parser.tab.c"
    break;

  case 390:
#line 1139 "p4parser.y"
                                         {}
#line 5167 "p4parser.tab.c"
    break;

  case 391:
#line 1140 "p4parser.y"
                                                     {}
#line 5173 "p4parser.tab.c"
    break;

  case 392:
#line 1141 "p4parser.y"
                                                             {}
#line 5179 "p4parser.tab.c"
    break;

  case 393:
#line 1145 "p4parser.y"
                                       {}
#line 5185 "p4parser.tab.c"
    break;

  case 394:
#line 1146 "p4parser.y"
                                         {}
#line 5191 "p4parser.tab.c"
    break;

  case 395:
#line 1147 "p4parser.y"
                                         {}
#line 5197 "p4parser.tab.c"
    break;

  case 396:
#line 1148 "p4parser.y"
                                         {}
#line 5203 "p4parser.tab.c"
    break;

  case 397:
#line 1149 "p4parser.y"
                                         {}
#line 5209 "p4parser.tab.c"
    break;

  case 398:
#line 1150 "p4parser.y"
                                         {}
#line 5215 "p4parser.tab.c"
    break;

  case 399:
#line 1151 "p4parser.y"
                                         {}
#line 5221 "p4parser.tab.c"
    break;

  case 400:
#line 1152 "p4parser.y"
                                                     {}
#line 5227 "p4parser.tab.c"
    break;

  case 401:
#line 1153 "p4parser.y"
                                                                 {}
#line 5233 "p4parser.tab.c"
    break;

  case 402:
#line 1154 "p4parser.y"
                                                 {}
#line 5239 "p4parser.tab.c"
    break;

  case 403:
#line 1155 "p4parser.y"
                                                 {}
#line 5245 "p4parser.tab.c"
    break;

  case 404:
#line 1156 "p4parser.y"
                                                 {}
#line 5251 "p4parser.tab.c"
    break;

  case 405:
#line 1157 "p4parser.y"
                                         {}
#line 5257 "p4parser.tab.c"
    break;

  case 406:
#line 1158 "p4parser.y"
                                                {}
#line 5263 "p4parser.tab.c"
    break;

  case 407:
#line 1159 "p4parser.y"
                                           {}
#line 5269 "p4parser.tab.c"
    break;

  case 408:
#line 1160 "p4parser.y"
                                          {}
#line 5275 "p4parser.tab.c"
    break;

  case 409:
#line 1162 "p4parser.y"
        {}
#line 5281 "p4parser.tab.c"
    break;

  case 410:
#line 1164 "p4parser.y"
        {}
#line 5287 "p4parser.tab.c"
    break;

  case 411:
#line 1165 "p4parser.y"
                                         {}
#line 5293 "p4parser.tab.c"
    break;

  case 412:
#line 1166 "p4parser.y"
                                         {}
#line 5299 "p4parser.tab.c"
    break;

  case 413:
#line 1167 "p4parser.y"
                                         {}
#line 5305 "p4parser.tab.c"
    break;

  case 414:
#line 1168 "p4parser.y"
                                         {}
#line 5311 "p4parser.tab.c"
    break;

  case 415:
#line 1169 "p4parser.y"
                                          {}
#line 5317 "p4parser.tab.c"
    break;

  case 416:
#line 1170 "p4parser.y"
                                           {}
#line 5323 "p4parser.tab.c"
    break;

  case 417:
#line 1171 "p4parser.y"
                                            {}
#line 5329 "p4parser.tab.c"
    break;

  case 418:
#line 1172 "p4parser.y"
                                             {}
#line 5335 "p4parser.tab.c"
    break;

  case 419:
#line 1173 "p4parser.y"
                                        {}
#line 5341 "p4parser.tab.c"
    break;

  case 420:
#line 1175 "p4parser.y"
        {}
#line 5347 "p4parser.tab.c"
    break;

  case 421:
#line 1176 "p4parser.y"
                                       {}
#line 5353 "p4parser.tab.c"
    break;

  case 422:
#line 1177 "p4parser.y"
                                       {}
#line 5359 "p4parser.tab.c"
    break;

  case 423:
#line 1179 "p4parser.y"
                                         {}
#line 5365 "p4parser.tab.c"
    break;

  case 424:
#line 1180 "p4parser.y"
                                             {}
#line 5371 "p4parser.tab.c"
    break;

  case 425:
#line 1182 "p4parser.y"
                                       {}
#line 5377 "p4parser.tab.c"
    break;

  case 426:
#line 1183 "p4parser.y"
                                       {}
#line 5383 "p4parser.tab.c"
    break;

  case 427:
#line 1184 "p4parser.y"
                                             {}
#line 5389 "p4parser.tab.c"
    break;

  case 428:
#line 1185 "p4parser.y"
                                             {}
#line 5395 "p4parser.tab.c"
    break;

  case 429:
#line 1186 "p4parser.y"
                                            {}
#line 5401 "p4parser.tab.c"
    break;

  case 430:
#line 1187 "p4parser.y"
                                       {}
#line 5407 "p4parser.tab.c"
    break;

  case 431:
#line 1188 "p4parser.y"
                                        {}
#line 5413 "p4parser.tab.c"
    break;

  case 432:
#line 1189 "p4parser.y"
                                       {}
#line 5419 "p4parser.tab.c"
    break;

  case 433:
#line 1190 "p4parser.y"
                                                      {}
#line 5425 "p4parser.tab.c"
    break;

  case 434:
#line 1191 "p4parser.y"
                         {}
#line 5431 "p4parser.tab.c"
    break;

  case 436:
#line 1195 "p4parser.y"
        {}
#line 5437 "p4parser.tab.c"
    break;

  case 437:
#line 1197 "p4parser.y"
        {}
#line 5443 "p4parser.tab.c"
    break;

  case 438:
#line 1199 "p4parser.y"
        {}
#line 5449 "p4parser.tab.c"
    break;

  case 439:
#line 1200 "p4parser.y"
                                                      {}
#line 5455 "p4parser.tab.c"
    break;

  case 440:
#line 1204 "p4parser.y"
                                       {}
#line 5461 "p4parser.tab.c"
    break;

  case 441:
#line 1205 "p4parser.y"
                                         {}
#line 5467 "p4parser.tab.c"
    break;

  case 442:
#line 1206 "p4parser.y"
                                         {}
#line 5473 "p4parser.tab.c"
    break;

  case 443:
#line 1207 "p4parser.y"
                                         {}
#line 5479 "p4parser.tab.c"
    break;

  case 444:
#line 1208 "p4parser.y"
                                         {}
#line 5485 "p4parser.tab.c"
    break;

  case 445:
#line 1209 "p4parser.y"
                                         {}
#line 5491 "p4parser.tab.c"
    break;

  case 446:
#line 1210 "p4parser.y"
                                         {}
#line 5497 "p4parser.tab.c"
    break;

  case 447:
#line 1211 "p4parser.y"
                                                             {}
#line 5503 "p4parser.tab.c"
    break;

  case 448:
#line 1212 "p4parser.y"
                                                                         {}
#line 5509 "p4parser.tab.c"
    break;

  case 449:
#line 1213 "p4parser.y"
                                                 {}
#line 5515 "p4parser.tab.c"
    break;

  case 450:
#line 1214 "p4parser.y"
                                         {}
#line 5521 "p4parser.tab.c"
    break;

  case 451:
#line 1215 "p4parser.y"
                                                {}
#line 5527 "p4parser.tab.c"
    break;

  case 452:
#line 1216 "p4parser.y"
                                           {}
#line 5533 "p4parser.tab.c"
    break;

  case 453:
#line 1217 "p4parser.y"
                                          {}
#line 5539 "p4parser.tab.c"
    break;

  case 454:
#line 1219 "p4parser.y"
        {}
#line 5545 "p4parser.tab.c"
    break;

  case 455:
#line 1221 "p4parser.y"
        {}
#line 5551 "p4parser.tab.c"
    break;

  case 456:
#line 1222 "p4parser.y"
                                                 {}
#line 5557 "p4parser.tab.c"
    break;

  case 457:
#line 1223 "p4parser.y"
                                                 {}
#line 5563 "p4parser.tab.c"
    break;

  case 458:
#line 1224 "p4parser.y"
                                                 {}
#line 5569 "p4parser.tab.c"
    break;

  case 459:
#line 1225 "p4parser.y"
                                                 {}
#line 5575 "p4parser.tab.c"
    break;

  case 460:
#line 1226 "p4parser.y"
                                                  {}
#line 5581 "p4parser.tab.c"
    break;

  case 461:
#line 1227 "p4parser.y"
                                                   {}
#line 5587 "p4parser.tab.c"
    break;

  case 462:
#line 1228 "p4parser.y"
                                                    {}
#line 5593 "p4parser.tab.c"
    break;

  case 463:
#line 1229 "p4parser.y"
                                                     {}
#line 5599 "p4parser.tab.c"
    break;

  case 464:
#line 1230 "p4parser.y"
                                                {}
#line 5605 "p4parser.tab.c"
    break;

  case 465:
#line 1232 "p4parser.y"
        {}
#line 5611 "p4parser.tab.c"
    break;

  case 466:
#line 1233 "p4parser.y"
                                               {}
#line 5617 "p4parser.tab.c"
    break;

  case 467:
#line 1234 "p4parser.y"
                                               {}
#line 5623 "p4parser.tab.c"
    break;

  case 468:
#line 1236 "p4parser.y"
                                         {}
#line 5629 "p4parser.tab.c"
    break;

  case 469:
#line 1237 "p4parser.y"
                                                     {}
#line 5635 "p4parser.tab.c"
    break;

  case 470:
#line 1238 "p4parser.y"
                                               {}
#line 5641 "p4parser.tab.c"
    break;

  case 471:
#line 1239 "p4parser.y"
                                               {}
#line 5647 "p4parser.tab.c"
    break;

  case 472:
#line 1240 "p4parser.y"
                                                     {}
#line 5653 "p4parser.tab.c"
    break;

  case 473:
#line 1241 "p4parser.y"
                                                     {}
#line 5659 "p4parser.tab.c"
    break;

  case 474:
#line 1242 "p4parser.y"
                                                    {}
#line 5665 "p4parser.tab.c"
    break;

  case 475:
#line 1243 "p4parser.y"
                                               {}
#line 5671 "p4parser.tab.c"
    break;

  case 476:
#line 1244 "p4parser.y"
                                                {}
#line 5677 "p4parser.tab.c"
    break;

  case 477:
#line 1245 "p4parser.y"
                                               {}
#line 5683 "p4parser.tab.c"
    break;

  case 478:
#line 1246 "p4parser.y"
                                                              {}
#line 5689 "p4parser.tab.c"
    break;

  case 479:
#line 1248 "p4parser.y"
        {}
#line 5695 "p4parser.tab.c"
    break;

  case 480:
#line 1250 "p4parser.y"
        {}
#line 5701 "p4parser.tab.c"
    break;

  case 481:
#line 1252 "p4parser.y"
        {}
#line 5707 "p4parser.tab.c"
    break;

  case 482:
#line 1253 "p4parser.y"
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
#line 1281 "p4parser.y"


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
