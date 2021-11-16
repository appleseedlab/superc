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
#define YYLAST   4110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  148
/* YYNRULES -- Number of rules.  */
#define YYNRULES  485
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  889

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
    1043,  1045,  1050,  1055,  1056,  1062,  1071,  1075,  1082,  1087,
    1088,  1092,  1098,  1102,  1103,  1107,  1108,  1112,  1113,  1114,
    1118,  1119,  1120,  1124,  1125,  1129,  1129,  1133,  1134,  1135,
    1136,  1137,  1141,  1142,  1143,  1144,  1145,  1146,  1147,  1148,
    1149,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1159,
    1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,
    1172,  1173,  1174,  1176,  1178,  1179,  1180,  1181,  1182,  1183,
    1184,  1185,  1186,  1187,  1189,  1190,  1192,  1194,  1196,  1200,
    1201,  1202,  1203,  1204,  1205,  1206,  1207,  1208,  1209,  1210,
    1211,  1212,  1213,  1214,  1216,  1218,  1219,  1220,  1221,  1222,
    1223,  1224,  1225,  1226,  1227,  1229,  1230,  1231,  1233,  1234,
    1235,  1236,  1237,  1238,  1239,  1240,  1241,  1242,  1243,  1245,
    1247,  1249,  1272,  1272,  1273,  1273
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
  "tableProperty", "keyElementList", "keyElement", "actionList",
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

#define YYPACT_NINF (-762)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-381)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -762,    30,  -762,   823,  -762,  -762,  -762,   374,  -762,   100,
     -11,   100,    14,   374,  -762,   100,   100,  -762,  -762,  -762,
    -762,   136,  1188,  -762,     6,  -762,   -54,  -762,   155,  -762,
     170,  -762,   -19,    42,  -762,   261,  -762,  -762,    66,  -762,
     374,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   110,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,   239,  -762,  -762,   -27,   374,   -25,   374,  -762,
    2641,   -24,   374,   166,   374,  2727,  2684,   374,   374,  1188,
     374,   374,   374,  1188,  -762,  -762,    61,  -762,  -762,   -21,
    -762,  -762,  -762,   122,   148,   -19,  -762,  1641,  2455,  2641,
    2455,   100,  -762,  2008,  -762,  2455,   129,  -762,   171,  2455,
     129,   194,  1743,  -762,  -762,  -762,  -762,  -762,   281,  2455,
     129,   144,   374,  -762,   221,  -762,   374,   -10,   150,   168,
     174,  -762,  -762,  -762,    82,   374,   374,  -762,  -762,   100,
     374,   374,  1641,   220,   185,   190,  -762,   250,  -762,  -762,
    2455,  2455,  2455,  2057,  1378,  2455,  -762,  -762,  -762,  -762,
     227,  -762,  -762,   241,   260,   531,   210,   103,  -762,   277,
     290,  -762,  3778,  -762,  -762,  2964,   281,  3001,  -762,  -762,
     374,   293,    99,  -762,   108,  3778,  1835,  3038,  -762,  -762,
    -762,  -762,   374,  3075,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  2641,  -762,  3112,  -762,   -21,
     300,   100,   319,  -762,   100,  -762,  -762,   100,   100,  -762,
    -762,   100,   100,   320,  -762,  -762,   322,  -762,  -762,  -762,
     166,  -762,   -19,  -762,   944,  -762,    -3,    -3,    -3,   201,
     204,   227,   327,     4,   254,  3149,    -3,   374,  2455,  -762,
    1641,  -762,  -762,   374,  2259,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,   323,  1641,  2455,  2455,  -762,  1052,
    -762,  -762,  -762,   333,  -762,   284,  2455,  -762,   374,  -762,
    2455,  -762,   129,  -762,   129,  1927,  -762,   129,   334,  2455,
    -762,   374,   326,  -762,  -762,  -762,  -762,  -762,  -762,   374,
     374,  -762,  1188,   -19,    57,  1188,  -762,  -762,    12,  -762,
    -762,  -762,  -762,  2502,  -762,  -762,  2455,  -762,  -762,  3778,
     335,   374,   252,  -762,  3986,  3986,   722,  3922,  3889,  3955,
    3955,   332,   332,   332,   332,    -3,    -3,    -3,  4017,  1045,
    4048,  2853,  3986,  2455,   336,  3186,   332,  -762,  -762,  -762,
    -762,   307,  3986,   -21,   374,  -762,  3778,  -762,  3778,  -762,
    -762,  -762,  -762,   -19,   341,  3778,   345,   209,   374,   340,
     357,   360,   355,   367,    11,   279,   364,    94,  -762,  -762,
      48,  -762,  -762,  -762,  -762,   377,  -762,   374,    27,   373,
    -762,  -762,  -762,   369,   381,  2308,   386,  -762,    41,  -762,
     531,   165,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,   430,    -3,  -762,  -762,   393,
    -762,  -762,  2455,   722,  -762,  2455,  2641,   388,   391,  -762,
    -762,  -762,   -21,  -762,   398,   232,  -762,  -762,  -762,  -762,
     -21,   -21,  -762,   166,  -762,   393,  -762,  2455,   374,   100,
     353,   411,  -762,  -762,   413,   373,  2455,   400,  -762,  2455,
    -762,  3223,  2455,  -762,   389,  2455,  1641,  2455,  -762,  2641,
    -762,   402,  3260,  3852,  -762,  1641,  -762,   412,  2455,  -762,
     374,    60,    78,    93,   422,   423,   374,   417,  3778,  -762,
     166,  -762,   164,   426,  -762,  -762,  3297,  -762,  3334,   435,
    2890,   437,  3371,   281,  1518,  -762,  -762,   439,  -762,  -762,
    -762,  -762,   605,  -762,  -762,  -762,  -762,  -762,   433,  -762,
     448,   129,   129,   129,   436,   438,   427,    53,  -762,  -762,
     882,   452,  1641,  -762,  2455,   441,  -762,   451,  -762,  1188,
    -762,  -762,  -762,  -762,   244,   454,   450,  -762,  -762,   462,
     464,   465,   473,   476,  -762,   370,  -762,  -762,   467,   445,
    -762,   474,  3408,  -762,  1641,   466,   -21,  -762,  2550,  2455,
    2455,  2455,  -762,  -762,  -762,   470,  -762,  -762,  -762,  -762,
     471,   882,  2357,   475,  -762,   483,  -762,   488,   337,   101,
    1188,  -762,  -762,   495,   374,  -762,  -762,  -762,  -762,  -762,
    -762,  3445,  3482,  3519,    95,  2406,   497,  2455,  -762,  2455,
    2455,  2455,  -762,  1378,  2455,  -762,  -762,  -762,  -762,   486,
    -762,  -762,  -762,   531,   493,   103,  -762,   491,  3815,  -762,
     487,   499,   496,   502,  -762,  -762,  -762,   374,  -762,   374,
     374,   374,  -762,   321,  -762,  -762,  3556,  2108,   504,    -3,
      -3,    -3,   513,  3593,    -3,   374,  -762,  1641,  -762,   -17,
    2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,
    2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,  2455,   505,
    1641,  2455,  2455,  -762,  1052,  -762,  -762,  2157,  -762,  -762,
     508,   510,   511,   257,   512,   524,   374,  1240,  -762,  -762,
     522,  -762,  -762,  -762,  1315,  2813,  -762,  2455,  -762,  -762,
     525,  -762,  3986,  3986,   722,  3922,  3889,  3955,  3955,   332,
     332,   332,   332,    -3,    -3,    -3,  4017,  1045,  4048,  2927,
    3986,  2455,   526,  3630,   332,   307,  3986,    -2,  2598,  -762,
    -762,  -762,  -762,  1641,   -19,   527,   533,   534,   536,  1150,
     321,  -762,  -762,  2455,  2455,    -3,  -762,  -762,  2455,   722,
    -762,  2455,   528,   547,  -762,   542,   537,  -762,  2208,  2455,
    2455,   -19,  3778,  3778,  3667,  3852,  1641,  -762,  -762,  -762,
     216,  -762,  3704,  3741,   539,  -762,   543,  1459,  -762,  2208,
    -762,  -762,  -762,  -762,   550,  -762,   374,   548,  -762
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
      25,    24,    37,   482,   483,     0,     0,     0,     0,    42,
     273,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    33,   251,    36,     0,   285,   244,    33,
     283,   159,   284,     0,     0,    34,   372,   434,   434,   273,
     434,   264,   282,   434,    42,   434,     0,   309,     0,   434,
       0,     0,     0,   272,   271,   270,   269,   274,     0,   434,
       0,     0,     0,   213,   243,   300,     0,   263,   224,     0,
       0,   261,   290,   294,     0,     0,     0,   144,   168,   264,
       0,     0,   434,   143,     0,   135,   136,     0,   216,   333,
     434,   434,   434,   434,   434,   434,   379,   394,   395,   396,
       0,   393,   392,   397,     0,     0,     0,   241,   242,     0,
     374,   375,   377,   433,   397,     0,     0,     0,   231,   265,
       0,     0,     0,   131,     0,   381,     0,     0,   484,   485,
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
       0,   157,    33,   162,    33,   335,   407,   406,   405,     0,
       0,   251,     0,   237,   238,     0,   404,     0,   434,   398,
     434,   385,   408,     0,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,     0,   434,   434,   434,   410,   434,
     247,   249,   248,     0,   267,     0,   434,    40,     0,    39,
     434,    38,     0,   310,     0,     0,   275,     0,     0,   434,
     214,     0,     0,   225,   291,   295,   145,   169,   297,     0,
       0,   137,    33,    33,     0,    34,   221,   217,     0,   220,
     219,   222,   218,    33,   402,   401,   434,   403,   409,   378,
       0,     0,     0,   376,   420,   421,   418,   430,   431,   424,
     425,   414,   415,   416,   417,   411,   412,   413,   428,   426,
     427,     0,   423,   434,     0,     0,   429,   278,   277,   276,
     279,     0,   422,    33,     0,   266,   133,   132,   382,   258,
     259,    43,   260,    33,     0,   371,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,   138,     0,   165,   163,
      33,   171,   167,   166,   164,     0,   223,     0,     0,   369,
     334,   318,   388,     0,     0,   434,     0,   383,     0,   347,
       0,   237,   325,   328,   331,   330,   327,   326,   346,   329,
     332,   336,   344,   345,   387,     0,   438,   437,   386,     0,
     148,   399,   434,   419,   436,   434,     0,     0,     0,   268,
     365,   368,    33,   301,     0,     0,   304,   229,   297,   297,
      33,    33,   293,     0,   298,     0,   147,   434,     0,     0,
       0,     0,   172,   212,     0,   369,   434,     0,   319,   434,
     320,     0,   434,   384,     0,   434,   434,   434,   389,   273,
     152,     0,     0,   432,   280,   434,   232,     0,   434,   303,
       0,    33,    33,    33,     0,     0,     0,     0,   139,   173,
       0,   161,    33,     0,   370,   367,     0,   321,     0,     0,
       0,     0,     0,     0,     0,   150,   400,     0,   215,   306,
     305,   226,     0,   230,   292,   296,   146,   170,     0,   149,
       0,     0,     0,     0,     0,     0,    31,    33,   349,   366,
      33,     0,   434,   390,   434,     0,   317,     0,   151,     0,
     155,   153,   154,   435,     0,   243,     0,   299,   175,     0,
       0,     0,     0,     0,    32,     0,   348,   350,     0,   322,
     338,     0,     0,   315,   434,     0,    33,   233,    33,   434,
     434,   434,   358,   355,    28,     0,    30,    29,    26,    27,
       0,    33,     0,     0,   391,     0,   234,     0,     0,     0,
      34,   176,   182,     0,     0,   177,   179,   183,   178,   180,
     181,     0,     0,     0,    33,   434,     0,   434,   323,   434,
     434,   434,   337,   434,   434,   441,   442,   443,   342,     0,
     440,   439,   444,     0,     0,   241,   339,     0,   343,   324,
       0,     0,     0,     0,   187,   189,   184,     0,   174,     0,
       0,     0,   352,     0,   351,   356,     0,   434,     0,   452,
     451,   450,     0,     0,   449,     0,   445,   434,   453,   341,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,     0,
     434,   434,   434,   455,   434,   316,   235,   434,   188,   175,
       0,     0,     0,     0,     0,   360,     0,   434,   208,   207,
       0,   194,   195,   363,   434,   204,   354,   434,   448,   454,
       0,   340,   465,   466,   463,   475,   476,   469,   470,   459,
     460,   461,   462,   456,   457,   458,   473,   471,   472,     0,
     468,   434,     0,     0,   474,     0,   467,     0,    33,   211,
     210,   209,   359,   434,    33,   203,   202,     0,     0,   204,
       0,   353,   364,   434,   434,   481,   480,   446,   434,   464,
     479,   434,     0,     0,   185,     0,     0,   197,   434,   434,
     434,    33,   205,   206,     0,   477,   434,   191,   361,   357,
       0,   198,   200,   201,     0,   447,     0,   434,   196,   434,
     362,   478,   190,   192,     0,   199,     0,     0,   193
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -762,  -762,  -762,  -762,  -762,    -7,   123,  -762,  -762,     2,
      10,   -18,   -82,  -762,   459,   248,  -278,  -762,   295,  -762,
    -762,  -762,  -762,  -299,    83,  -762,  -762,   590,   214,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,   153,  -762,
    -150,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -762,  -249,
    -762,  -762,  -762,  -761,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -762,  -762,   -69,  -762,  -762,   432,
     -41,  -762,   342,    52,  -762,   515,    54,  -762,  -120,  -762,
    -762,  -273,   -91,  -762,  -141,  -762,   203,  -762,  -762,  -762,
    -762,  -762,  -762,  -762,  -186,  -762,  -762,  -762,  -762,  -762,
      65,  -762,  -762,   -59,  -762,  -644,  -642,  -762,  -762,  -641,
    -640,  -589,   -31,  -762,  -762,  -762,  -762,  -762,  -762,  -762,
    -762,  -762,    19,  -762,  -762,  -762,  -203,  -156,  -762,   325,
    -291,     7,    98,  -525,    46,  -122,  -762,   310,  -151,  -709,
    -164,  -762,  -762,   885,  -762,  -762,   259,   -73
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    20,   174,   164,   670,   645,   143,
      95,    23,   112,   284,   182,   183,   144,   145,   146,   310,
      24,   301,   462,    25,   561,   594,   631,    91,   165,    27,
     147,   541,   392,   469,    28,   302,   463,   470,   471,   610,
     658,   681,   682,   779,   683,   724,   725,   877,   883,   790,
     791,   870,   837,   792,   472,    29,    30,   291,   456,   314,
     397,   475,    31,   294,   459,   571,    32,   363,   603,   116,
     166,    34,   167,    36,    37,   168,    39,    40,   178,   179,
     365,   117,   118,   440,   441,    41,    42,    43,   297,   460,
      44,    45,   298,   461,   464,   534,    46,   292,   382,   525,
     526,    47,    48,   108,    49,   492,   493,   494,   495,   496,
     497,   498,   499,   315,   403,   500,   672,   716,   717,   501,
     399,   617,   618,   695,   735,   694,   784,   793,   794,    50,
     689,   690,   547,   454,    52,   169,   170,   171,   184,   504,
     358,   411,   505,   172,   173,   718,   359,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      61,    96,   320,   332,    85,    21,    61,   130,   176,   111,
      51,   378,   376,    22,   685,   396,   686,   687,   688,   303,
     306,   584,   186,   401,   785,   105,   838,   109,   119,   -33,
       4,   649,  -134,    61,    94,    66,   -17,   194,   -17,   -17,
       7,   352,     7,   599,     7,   286,    64,   288,    98,   355,
     -17,   853,    63,    64,   370,   331,  -241,    88,   532,    61,
      68,    61,   331,   115,    97,    61,    87,    61,    61,   128,
      61,    61,     7,    61,    61,    61,    13,    85,    13,   142,
      13,   134,   698,    53,    54,   134,   106,   149,   110,   120,
     163,    55,   115,   468,    97,  -160,   163,   871,    53,    54,
     646,   473,    56,   361,   489,    57,    55,   601,    13,     7,
     100,    58,   502,   142,     7,    61,    73,    56,   885,    61,
      57,     7,    59,    60,   614,   604,    58,    72,    61,    61,
      62,   785,    73,    61,    61,   163,    69,    59,    60,     7,
     605,   375,   732,   615,   367,    13,   163,   726,    63,    64,
      13,    63,    64,   369,     7,   368,     7,    13,   329,   332,
     477,   331,    75,   101,   370,   518,    77,    78,   148,    73,
     102,   380,   738,    61,   383,    13,    73,   384,   385,   188,
     189,   386,   387,    82,   685,    61,   686,   687,   688,   107,
      13,   107,    13,   538,   149,   121,   289,   123,   125,   129,
     132,   133,   539,   137,   138,   139,    72,    89,   410,    98,
     -24,    73,    74,    63,    64,    90,    75,    26,   191,    76,
      77,    78,    89,   554,     5,     7,   181,   192,   295,    79,
      92,    80,    81,   434,   296,   614,    26,    82,   311,     8,
       9,   195,    83,   564,   567,   290,   312,    84,   404,   293,
     192,   405,   574,   575,   615,    11,   523,   368,   299,   300,
     370,    13,   330,   304,   305,   192,    14,   -25,    65,   878,
      67,    15,   879,    16,    70,    71,   181,    19,   115,   569,
     -25,   -25,   136,   103,    26,   327,   141,    26,   570,    26,
      26,   104,   445,    26,    99,   630,   313,    26,   100,   449,
     -24,   450,     5,   364,   452,    98,  -242,   307,   308,    63,
      64,   509,   510,    26,   309,   373,   394,     8,     9,   328,
      61,   402,   457,   163,   395,    84,    61,   163,    53,    54,
     333,   188,   189,    11,   188,   189,    55,   285,   535,   536,
     444,   558,   572,   573,    14,    35,   334,    56,   163,    15,
      57,    16,   366,    17,    18,    19,    58,   188,   189,   379,
     180,    61,   476,   516,    35,   381,   388,    59,   517,   346,
     347,   348,   458,   433,    61,   389,   352,    85,   677,     5,
     406,    64,    61,    61,   355,   443,   527,   453,   507,   514,
     331,    61,    53,    54,   467,    94,   487,   522,   180,   474,
      55,   521,   395,   528,    61,   488,   529,   530,    53,    54,
     503,    56,    35,   395,    57,    35,    55,    35,    35,   531,
      58,    35,   520,   537,   543,    35,    99,    56,   722,   548,
      57,    59,   546,   549,   591,    33,    58,    61,   552,   560,
     565,    35,   664,   597,   566,    53,    54,    59,    60,   665,
     408,    61,   538,    55,    86,    94,   412,   568,   581,   582,
     585,   589,   595,   666,    56,   598,   533,    57,   593,   667,
      61,    61,   540,    58,   555,   606,   607,   609,    63,    64,
     668,   669,   556,   553,    59,    60,   619,   622,   331,   557,
     625,   181,   633,   637,   638,   642,   323,   643,   650,    26,
     651,   653,   644,   654,   107,   122,   656,   126,   131,   115,
     657,   135,   465,   466,   659,   140,   660,   661,    38,   662,
     627,   479,   663,   671,    26,   554,   676,   673,    26,   696,
     697,    61,   675,   636,   508,   719,   720,    38,   639,   640,
     641,   721,   728,   737,   745,   747,   749,   775,   777,   163,
     180,   748,   115,   180,   773,   821,   180,   180,   163,   776,
     180,   180,   778,    61,   796,   655,   797,   519,   829,    61,
     830,   831,   832,   602,   533,   533,   833,   840,   846,   850,
     866,   524,    99,  -208,   616,    38,   322,   857,    38,  -207,
      38,    38,   858,   867,    38,   868,   881,   869,    38,   880,
     544,   545,    53,    54,   629,   886,    26,   391,   888,    26,
      55,    85,   319,   487,    38,   163,   447,   490,   577,   616,
      93,    56,    94,   542,    57,   800,   827,    35,   884,   828,
      58,   714,   612,   825,   613,   600,   647,   861,   842,   400,
     632,    59,    88,   583,   413,     0,     0,   163,   822,     0,
       0,   487,    35,     0,     0,     0,    35,     0,     0,     0,
     679,   579,    85,     5,   487,   712,     0,     0,   680,   324,
       0,    61,     0,    94,   634,     0,     0,    61,     8,     9,
       0,     0,     0,     0,     0,     0,    84,     0,     0,     0,
       0,     0,     0,   524,    11,     0,   733,     0,     0,   608,
       0,   323,     0,     0,     0,    14,   746,     0,     0,     0,
      15,   855,    16,     0,    17,    18,   635,     0,   801,     0,
      61,     0,    61,    61,    61,     0,   487,     0,     0,     0,
      26,     0,     0,     0,    35,     0,     0,    35,    61,     0,
     163,     0,   390,     0,   876,   491,   398,    26,     0,     0,
      99,    94,   852,     0,     0,   342,   343,   344,   345,   346,
     347,   348,     0,   163,   559,     0,   352,     0,     0,     0,
       0,    64,     0,    26,   355,     0,   553,     0,     0,    61,
     331,     0,     0,     0,   357,     0,     0,     0,     0,     0,
       0,   439,     0,     0,    26,     0,     0,     0,   580,     0,
      38,   723,     0,     0,     0,     0,     0,   479,    26,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     0,
       0,   487,     0,    -3,   398,    38,   163,   478,     0,    38,
     679,     0,     0,   487,   490,   398,   856,     0,   680,     0,
       0,     0,     0,    26,     0,     0,     0,     0,    26,     0,
     545,     0,   780,   781,   782,     0,     0,     0,    35,   163,
       0,     0,     0,   874,     0,     0,     0,     0,   799,     0,
       0,     0,   490,     0,   324,    35,     0,     0,     0,    61,
       0,     5,     0,     6,     7,   490,   713,     0,     0,     0,
       0,     0,     0,     0,    26,     0,     8,     9,     0,     0,
       0,    35,     0,     0,    10,     0,     0,    38,     0,   834,
      38,     0,    11,     0,     0,    12,     0,     0,    38,     0,
      13,     0,   611,    14,     0,     0,     0,     0,    15,     0,
      16,     0,    17,    18,    19,     0,    35,     0,     0,     0,
       5,     0,   481,     7,    35,     0,     0,   783,     0,     0,
     482,     0,     0,    53,    54,     0,     0,     0,     0,     0,
       0,    55,   648,     0,   483,   576,     0,     0,   484,     0,
       0,    35,    56,     0,    99,    57,    35,   774,     0,    13,
     485,    58,     0,   175,   486,   177,     0,     0,   185,     0,
     187,     0,    59,    19,   193,     0,     0,     0,     0,     0,
     491,     0,     5,     0,   287,     7,     0,     0,     0,   887,
       0,     0,     0,   648,   715,     0,   393,     8,     9,     0,
       0,     0,    35,     0,     0,    84,    33,     0,     0,     0,
       0,    38,     0,    11,   131,   316,   317,   318,   185,   325,
     326,    13,   490,     0,    14,   323,     0,     0,    38,    15,
       0,    16,     0,     0,   783,    19,     0,     0,     0,     0,
       0,    86,     0,     0,     0,     0,   131,     0,     0,     0,
       0,     0,     0,   337,    38,     0,     0,     0,   342,   343,
     344,   345,   346,   347,   348,   150,   151,     0,     0,   352,
     684,     0,     0,     0,    64,   152,   354,   355,   153,     0,
       0,     0,     0,   331,   154,     0,   155,   357,     0,    38,
       5,     0,   727,     0,     0,   437,   323,    38,   157,   158,
     159,     0,     0,    53,    54,     8,     9,     0,     0,   323,
       0,    55,     0,   321,     0,   742,     0,     0,     0,     0,
       0,    11,    56,     0,    38,    57,     0,     0,     0,    38,
       0,    58,    14,     0,     0,     0,     0,    15,     0,    16,
       0,   438,    59,    19,   161,   162,     0,     0,     0,     0,
     491,     0,     0,    38,     0,     0,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,    38,     0,     0,    63,    64,
     353,   354,   355,   407,     0,     0,   439,   356,   331,     0,
       0,     0,   357,   409,   859,   860,     0,     0,   324,   322,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,   430,   431,   432,     0,
       0,   435,   436,     0,   442,     0,     5,     0,     0,     7,
       0,   446,     0,     0,     0,   448,     0,     0,     0,     0,
     684,     8,     9,     0,   455,     0,     0,     0,     0,    84,
       0,     0,     0,   150,   151,     0,     0,    11,     0,     0,
       0,     0,     0,   152,     0,    13,   153,     0,    14,   324,
       0,   506,   154,    15,   155,    16,     0,     0,     5,    19,
       0,     0,   324,   835,     0,     0,   157,   158,   159,     0,
       0,    53,    54,     8,     9,     0,     0,   836,   513,    55,
       0,   321,     0,     0,     0,     0,     0,     0,     0,    11,
      56,     0,     0,    57,     0,     0,     0,     0,     0,    58,
      14,     0,     0,    38,     0,    15,     0,    16,   150,   151,
      59,    19,   161,   162,     0,     0,     0,     0,   152,     0,
       0,   153,   841,     0,     0,     0,     0,   787,     0,   155,
     551,     0,     0,     5,     0,     0,     0,     0,   788,     0,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,   789,     0,    55,     0,   160,   562,     0,     0,
     563,     0,     0,     0,     0,    56,     0,     0,    57,     0,
       0,   150,   151,     0,    58,     0,     0,     0,     0,     0,
       0,   152,   578,     0,   153,    59,    19,   161,   162,     0,
     154,   455,   155,     0,   586,     0,     5,   588,     0,     0,
     590,     0,   592,     0,   157,   158,   159,     0,     0,    53,
      54,     8,     9,   455,     0,     0,     0,    55,     0,   321,
       0,     0,     0,     0,     0,     0,     0,    11,    56,     0,
       0,    57,     0,     0,     0,     0,     0,    58,    14,     0,
       0,     0,     0,    15,     0,    16,     0,     0,    59,    19,
     161,   162,   150,   151,     0,     0,     0,     0,     0,     0,
       0,     0,   152,     0,     0,   153,   882,     0,     0,   652,
       0,   787,     0,   155,     0,     0,     0,     5,     0,     0,
       0,     0,   788,     0,     0,   157,   158,   159,     0,     0,
      53,    54,     0,     0,     0,     0,   789,     0,    55,     0,
     160,     0,     0,     0,   691,   692,   693,     0,     0,    56,
       0,     0,    57,     0,     0,     0,     0,     0,    58,     0,
       0,     0,     0,     0,     0,   628,     0,     0,     0,    59,
      19,   161,   162,     0,     0,     0,     5,     0,     0,     7,
     736,     0,   455,     0,   739,   740,   741,     0,   743,   744,
       0,     8,     9,     0,     0,     0,     0,     0,     0,    84,
       0,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,    14,     0,
       0,     0,   795,    15,     0,    16,     0,    17,    18,    19,
       0,     0,     0,     0,     0,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   811,   812,   813,   814,   815,   816,
     817,   818,   819,   820,     0,     0,   823,   824,     0,   826,
       0,     0,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   839,     0,   150,   151,     0,     0,     0,   795,
       0,     0,   845,     0,   152,     0,     0,   153,     0,     0,
       0,     0,     0,   154,  -373,   155,     0,     0,     0,     5,
       0,     0,     0,     0,   156,     0,   849,   157,   158,   159,
       0,     0,    53,    54,     0,     0,     0,     0,     0,     0,
      55,     0,   160,     0,     0,     0,     0,     0,   862,   863,
       0,    56,     0,   864,    57,     0,   865,     0,     0,     0,
      58,     0,     0,   795,   872,   873,     0,     0,     0,     0,
       0,    59,   124,   161,   162,     0,     0,     0,     0,     0,
       0,     0,   795,     0,   795,   196,   197,     0,     0,   198,
     199,     0,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,     0,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   196,     0,     0,
       0,   198,   199,     0,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   371,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   196,
       0,     0,     0,   198,   199,     0,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     451,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   150,   151,     0,     0,     0,     0,     0,     0,     0,
       0,   152,     0,  -380,   153,     0,     0,     0,     0,     0,
     154,     0,   155,     0,  -380,     0,     5,     0,     0,     0,
       0,     0,     0,     0,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,     0,     0,    55,     0,   160,
     150,   151,     0,     0,     0,     0,     0,     0,    56,     0,
     152,    57,     0,   153,  -380,     0,     0,    58,     0,   154,
       0,   155,     0,  -380,     0,     5,     0,     0,    59,   124,
     161,   162,     0,   157,   158,   159,     0,     0,    53,    54,
       0,     0,     0,     0,     0,     0,    55,     0,   160,     0,
       0,   150,   151,     0,     0,     0,     0,    56,     0,     0,
      57,   152,     0,     0,   153,     0,    58,     0,     0,     0,
     787,     0,   155,     0,     0,     0,     5,    59,   124,   161,
     162,   788,     0,     0,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,   789,     0,    55,     0,   160,
     150,   151,     0,     0,     0,     0,     0,     0,    56,     0,
     152,    57,     0,   153,     0,     0,     0,    58,     0,   154,
    -380,   155,     0,  -380,     0,     5,     0,     0,    59,    19,
     161,   162,     0,   157,   158,   159,     0,     0,    53,    54,
       0,     0,     0,     0,     0,     0,    55,     0,   160,     0,
       0,   150,   151,     0,     0,     0,     0,    56,     0,     0,
      57,   152,     0,     0,   153,     0,    58,     0,     0,     0,
     154,     0,   155,     0,     0,     0,     5,    59,    19,   161,
     162,   788,     0,     0,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,   789,     0,    55,     0,   160,
       0,     0,   150,   151,     0,     0,     0,     0,    56,     0,
       0,    57,   152,     0,     0,   153,     0,    58,     0,     0,
       0,   154,     0,   155,     0,     0,     0,     5,    59,    19,
     161,   162,   156,     0,     0,   157,   158,   159,     0,     0,
      53,    54,     0,     0,     0,     0,     0,     0,    55,     0,
     160,   150,   151,     0,     0,     0,     0,     0,     0,    56,
       0,   152,    57,     0,   153,     0,     0,     0,    58,     0,
     154,     0,   155,     0,     0,     0,     5,     0,   550,    59,
     124,   161,   162,     0,   157,   158,   159,     0,     0,    53,
      54,     0,     0,     0,     0,     0,     0,    55,     0,   160,
     699,   700,     0,     0,     0,     0,     0,     0,    56,     0,
     701,    57,     0,     0,   702,     0,     0,    58,     0,   703,
       0,   704,     0,     0,     0,     5,     0,     0,    59,    19,
     161,   162,     0,   705,   706,   707,     0,     0,    53,    54,
       0,     0,     0,     0,   708,     0,    55,     0,   709,   150,
     151,     0,     0,     0,     0,     0,     0,    56,     0,   152,
      57,     0,   153,   734,     0,     0,    58,     0,   154,     0,
     155,     0,     0,     0,     5,     0,     0,    59,    19,   710,
     711,     0,   157,   158,   159,     0,     0,    53,    54,     0,
       0,     0,     0,     0,     0,    55,     0,   160,   150,   151,
       0,     0,     0,     0,     0,     0,    56,     0,   152,    57,
       0,   153,     0,     0,     0,    58,     0,   154,     0,   155,
       0,     0,     0,     5,     0,     0,    59,    19,   161,   162,
       0,   157,   158,   159,     0,     0,    53,    54,     0,     0,
       0,     0,     0,     0,    55,     0,   160,     0,     0,     0,
       0,     0,     0,     0,     0,    56,     0,     0,    57,   480,
       0,     0,     0,     0,    58,     0,     0,     0,     0,     0,
       5,     0,   481,     7,     0,    59,    19,   161,   162,     0,
     482,     0,     0,    53,    54,     8,     9,     0,     0,     0,
       0,    55,     0,    84,   483,     0,     0,     0,   484,     0,
       0,    11,    56,     0,     0,    57,     0,  -186,     0,    13,
     485,    58,    14,     0,   486,     0,     0,    15,     5,    16,
     481,     7,    59,    19,     0,     0,     0,     0,   482,     0,
       0,    53,    54,     8,     9,     0,     0,     0,     0,    55,
       0,    84,     0,     0,     0,     0,   484,     0,     0,    11,
      56,     0,     0,    57,     0,   854,     0,    13,     0,    58,
      14,     0,     0,     0,   678,    15,     5,    16,   481,     7,
      59,    19,     0,     0,     0,     0,   482,     0,     0,    53,
      54,     8,     9,     0,     0,     0,     0,    55,     0,    84,
       0,     0,     0,     0,   484,     0,     0,    11,    56,     0,
       0,    57,     0,     0,     0,    13,     0,    58,    14,     5,
       0,     0,     0,    15,   113,    16,     0,     0,    59,    19,
       0,     0,    53,    54,     8,     9,     0,     0,     0,     0,
      55,     0,    84,     0,     0,     0,     0,     0,     0,     0,
      11,    56,     0,     0,    57,     0,     0,     0,     0,     0,
      58,    14,     5,     0,     0,     0,    15,     0,    16,     0,
     114,    59,    19,     0,     0,    53,    54,     8,     9,     0,
       0,     0,     0,    55,     0,    84,     0,     0,     0,     0,
       0,     0,     0,    11,    56,     0,     0,    57,     0,     0,
       0,     0,     0,    58,    14,     5,     0,     0,     0,    15,
       0,    16,     0,    17,   127,   124,     0,     0,    53,    54,
       8,     9,     0,     0,     0,     0,    55,     0,    84,     0,
       0,     0,     0,     0,     0,     0,    11,    56,     0,     0,
      57,     0,     0,     0,     0,     0,    58,    14,     0,     0,
       0,     0,    15,     0,    16,     0,     0,    59,   124,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,     0,     0,     0,     0,
     356,   331,     0,     0,     0,   357,     0,   843,   844,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,   511,     0,
       0,    63,    64,   353,   354,   355,     0,     0,   512,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,   623,     0,     0,    63,    64,
     353,   354,   355,     0,     0,   624,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,   847,     0,     0,    63,    64,   353,   354,   355,
       0,     0,   848,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,   360,
       0,     0,    63,    64,   353,   354,   355,     0,     0,     0,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,   362,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,     0,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,   372,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,   374,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,   377,     0,     0,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,   407,     0,     0,     0,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,    63,    64,   353,   354,   355,     0,
       0,   515,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,     0,     0,     0,     0,
     356,   331,     0,   587,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,   596,     0,     0,    63,    64,
     353,   354,   355,     0,     0,     0,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,     0,     0,     0,    63,    64,   353,   354,   355,
     620,     0,     0,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,   621,     0,     0,
       0,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,     0,   356,   331,
       0,   626,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,   674,     0,     0,    63,    64,   353,   354,
     355,     0,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,   729,     0,
       0,     0,   356,   331,     0,     0,     0,   357,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,   730,     0,     0,     0,   356,
     331,     0,     0,     0,   357,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,   731,     0,     0,     0,   356,   331,     0,     0,
       0,   357,   335,   336,   337,   338,   339,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,    63,    64,   353,   354,   355,     0,
       0,   786,     0,   356,   331,     0,     0,     0,   357,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,     0,   352,     0,     0,
       0,    63,    64,   353,   354,   355,   798,     0,     0,     0,
     356,   331,     0,     0,     0,   357,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,     0,   352,     0,     0,     0,    63,    64,
     353,   354,   355,     0,     0,   851,     0,   356,   331,     0,
       0,     0,   357,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
       0,   352,   875,     0,     0,    63,    64,   353,   354,   355,
       0,     0,     0,     0,   356,   331,     0,     0,     0,   357,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,     0,   352,     0,
       0,     0,    63,    64,   353,   354,   355,     0,     0,     0,
    -205,   356,   331,     0,     0,     0,   357,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,     0,   352,     0,     0,     0,    63,
      64,   353,   354,   355,     0,     0,     0,  -206,   356,   331,
       0,     0,     0,   357,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,     0,   352,     0,     0,     0,    63,    64,   353,   354,
     355,     0,     0,     0,     0,   356,   331,     0,     0,     0,
     357,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,     0,   767,
       0,     0,     0,    63,    64,   768,   769,   770,     0,     0,
       0,     0,   771,   331,     0,     0,     0,   772,   335,   336,
     337,   338,   339,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,     0,     0,     0,     0,     0,
     331,     0,     0,     0,   357,   335,   336,   337,   338,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,     0,   352,     0,     0,     0,    63,    64,   353,
     354,   355,     0,     0,     0,     0,     0,   331,   335,   336,
     337,   357,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,     0,   352,     0,     0,     0,
      63,    64,   353,   354,   355,     0,     0,     0,     0,     0,
     331,   335,   336,   337,   357,     0,     0,     0,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,     0,   352,
       0,     0,     0,    63,    64,   353,   354,   355,     0,     0,
       0,     0,     0,   331,   337,     0,     0,   357,     0,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,     0,
     352,     0,     0,     0,     0,    64,     0,   354,   355,     0,
       0,     0,     0,     0,   331,   337,     0,     0,   357,     0,
     342,   343,   344,   345,   346,   347,   348,     0,   350,   351,
       0,   352,     0,     0,     0,     0,    64,     0,   354,   355,
       0,     0,     0,     0,     0,   331,   337,     0,     0,   357,
       0,   342,   343,   344,   345,   346,   347,   348,     0,   350,
       0,     0,   352,     0,     0,     0,     0,    64,     0,   354,
     355,     0,     0,     0,     0,     0,   331,     0,     0,     0,
     357
};

static const yytype_int16 yycheck[] =
{
       7,    32,   153,   167,    22,     3,    13,    76,    99,    68,
       3,   289,   285,     3,   658,   314,   658,   658,   658,   139,
     142,   546,   104,   314,   733,    52,   787,    52,    52,    46,
       0,   620,    53,    40,    32,    46,    46,   110,    48,    49,
      61,    44,    61,   568,    61,   118,    49,   120,    44,    52,
      60,    53,    48,    49,    56,    58,    52,   111,    47,    66,
      46,    68,    58,    70,    52,    72,    60,    74,    75,    76,
      77,    78,    61,    80,    81,    82,    97,    95,    97,    52,
      97,    79,   671,    71,    72,    83,   113,    46,   113,   113,
      97,    79,    99,   392,    52,    47,   103,   858,    71,    72,
      47,   392,    90,   176,   403,    93,    79,    47,    97,    61,
      44,    99,   403,    52,    61,   122,    75,    90,   879,   126,
      93,    61,   110,   111,    71,    47,    99,    70,   135,   136,
       7,   840,    75,   140,   141,   142,    13,   110,   111,    61,
      47,   223,    47,    90,    45,    97,   153,    46,    48,    49,
      97,    48,    49,    45,    61,    56,    61,    97,   165,   323,
     103,    58,    80,    40,    56,   443,    84,    85,    46,    75,
      60,   291,   697,   180,   294,    97,    75,   297,   298,    50,
      51,   301,   302,   101,   828,   192,   828,   828,   828,    66,
      97,    68,    97,    99,    46,    72,    52,    74,    75,    76,
      77,    78,   108,    80,    81,    82,    70,    52,   330,    44,
      60,    75,    76,    48,    49,    60,    80,     3,    47,    83,
      84,    85,    52,    58,    58,    61,   103,    56,    60,    93,
      60,    95,    96,   355,    60,    71,    22,   101,    53,    73,
      74,    47,   106,   516,   522,   122,    56,    81,    47,   126,
      56,    47,   530,   531,    90,    89,    47,    56,   135,   136,
      56,    97,    52,   140,   141,    56,   100,    46,     9,    53,
      11,   105,    56,   107,    15,    16,   153,   111,   285,    47,
      59,    60,    79,    44,    70,    58,    83,    73,    56,    75,
      76,    52,   365,    79,    35,   594,    46,    83,    44,   372,
      59,   374,    58,   180,   377,    44,    52,    87,    88,    48,
      49,    59,    60,    99,    94,   192,   314,    73,    74,    59,
     327,   314,   381,   330,   314,    81,   333,   334,    71,    72,
      53,    50,    51,    89,    50,    51,    79,    56,    59,    60,
      56,   505,   528,   529,   100,     3,    56,    90,   355,   105,
      93,   107,    59,   109,   110,   111,    99,    50,    51,    59,
     101,   368,   393,    56,    22,    46,    46,   110,   441,    37,
      38,    39,    46,    50,   381,    53,    44,   395,   656,    58,
      53,    49,   389,   390,    52,    52,    46,    53,    53,    53,
      58,   398,    71,    72,   392,   393,   403,    52,   139,   392,
      79,    60,   392,    46,   411,   403,    46,    52,    71,    72,
     403,    90,    70,   403,    93,    73,    79,    75,    76,    52,
      99,    79,   453,    59,    47,    83,   167,    90,    91,    60,
      93,   110,    59,    52,   556,     3,    99,   444,    52,    46,
      52,    99,    72,   565,    53,    71,    72,   110,   111,    79,
     327,   458,    99,    79,    22,   453,   333,    59,    47,    46,
      60,    72,    60,    93,    90,    53,   464,    93,   559,    99,
     477,   478,   470,    99,    44,    53,    53,    60,    48,    49,
     110,   111,    52,   490,   110,   111,    60,    52,    58,    59,
      53,   368,    53,    60,    46,    59,   154,    59,    46,   285,
     622,    60,    75,    52,   381,    73,    52,    75,    76,   516,
      60,    79,   389,   390,    52,    83,    52,    52,     3,    46,
     593,   398,    46,    78,   310,    58,    60,    53,   314,    59,
      59,   538,   654,   602,   411,    60,    53,    22,   611,   612,
     613,    53,    47,    46,    58,    52,    55,    60,    52,   556,
     291,   715,   559,   294,   718,    50,   297,   298,   565,    60,
     301,   302,    60,   570,    60,   634,    53,   444,    60,   576,
      60,    60,    60,   571,   572,   573,    52,    55,    53,    53,
      52,   458,   323,    56,   582,    70,   154,    53,    73,    56,
      75,    76,    56,    46,    79,    53,    53,    60,    83,    60,
     477,   478,    71,    72,   594,    55,   392,   312,    60,   395,
      79,   629,   153,   620,    99,   622,   368,   403,   535,   617,
      30,    90,   620,   470,    93,   747,   777,   285,   877,   779,
      99,   672,   580,   774,   580,   570,   617,   840,   794,   314,
     594,   110,   111,   545,   334,    -1,    -1,   654,   770,    -1,
      -1,   658,   310,    -1,    -1,    -1,   314,    -1,    -1,    -1,
     658,   538,   680,    58,   671,   672,    -1,    -1,   658,   154,
      -1,   678,    -1,   671,    69,    -1,    -1,   684,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,   570,    89,    -1,   694,    -1,    -1,   576,
      -1,   359,    -1,    -1,    -1,   100,   713,    -1,    -1,    -1,
     105,   833,   107,    -1,   109,   110,   111,    -1,   749,    -1,
     727,    -1,   729,   730,   731,    -1,   733,    -1,    -1,    -1,
     516,    -1,    -1,    -1,   392,    -1,    -1,   395,   745,    -1,
     747,    -1,   310,    -1,   866,   403,   314,   533,    -1,    -1,
     491,   749,   825,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,   770,   505,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,   559,    52,    -1,   783,    -1,    -1,   786,
      58,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,   359,    -1,    -1,   580,    -1,    -1,    -1,   539,    -1,
     285,   678,    -1,    -1,    -1,    -1,    -1,   684,   594,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   602,    -1,    -1,    -1,
      -1,   828,    -1,     0,   392,   310,   833,   395,    -1,   314,
     828,    -1,    -1,   840,   620,   403,   834,    -1,   828,    -1,
      -1,    -1,    -1,   629,    -1,    -1,    -1,    -1,   634,    -1,
     727,    -1,   729,   730,   731,    -1,    -1,    -1,   516,   866,
      -1,    -1,    -1,   861,    -1,    -1,    -1,    -1,   745,    -1,
      -1,    -1,   658,    -1,   359,   533,    -1,    -1,    -1,   886,
      -1,    58,    -1,    60,    61,   671,   672,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   680,    -1,    73,    74,    -1,    -1,
      -1,   559,    -1,    -1,    81,    -1,    -1,   392,    -1,   786,
     395,    -1,    89,    -1,    -1,    92,    -1,    -1,   403,    -1,
      97,    -1,   580,   100,    -1,    -1,    -1,    -1,   105,    -1,
     107,    -1,   109,   110,   111,    -1,   594,    -1,    -1,    -1,
      58,    -1,    60,    61,   602,    -1,    -1,   733,    -1,    -1,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    79,   620,    -1,    82,   533,    -1,    -1,    86,    -1,
      -1,   629,    90,    -1,   715,    93,   634,   718,    -1,    97,
      98,    99,    -1,    98,   102,   100,    -1,    -1,   103,    -1,
     105,    -1,   110,   111,   109,    -1,    -1,    -1,    -1,    -1,
     658,    -1,    58,    -1,   119,    61,    -1,    -1,    -1,   886,
      -1,    -1,    -1,   671,   672,    -1,    72,    73,    74,    -1,
      -1,    -1,   680,    -1,    -1,    81,   594,    -1,    -1,    -1,
      -1,   516,    -1,    89,   602,   150,   151,   152,   153,   154,
     155,    97,   828,    -1,   100,   703,    -1,    -1,   533,   105,
      -1,   107,    -1,    -1,   840,   111,    -1,    -1,    -1,    -1,
      -1,   629,    -1,    -1,    -1,    -1,   634,    -1,    -1,    -1,
      -1,    -1,    -1,    28,   559,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    33,    34,    -1,    -1,    44,
     658,    -1,    -1,    -1,    49,    43,    51,    52,    46,    -1,
      -1,    -1,    -1,    58,    52,    -1,    54,    62,    -1,   594,
      58,    -1,   680,    -1,    -1,    63,   774,   602,    66,    67,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,   787,
      -1,    79,    -1,    81,    -1,   703,    -1,    -1,    -1,    -1,
      -1,    89,    90,    -1,   629,    93,    -1,    -1,    -1,   634,
      -1,    99,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,
      -1,   109,   110,   111,   112,   113,    -1,    -1,    -1,    -1,
     828,    -1,    -1,   658,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,   680,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,   774,    57,    58,    -1,
      -1,    -1,    62,   328,    64,    65,    -1,    -1,   703,   787,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,    -1,
      -1,   356,   357,    -1,   359,    -1,    58,    -1,    -1,    61,
      -1,   366,    -1,    -1,    -1,   370,    -1,    -1,    -1,    -1,
     828,    73,    74,    -1,   379,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    33,    34,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    43,    -1,    97,    46,    -1,   100,   774,
      -1,   406,    52,   105,    54,   107,    -1,    -1,    58,   111,
      -1,    -1,   787,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    77,   433,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
     100,    -1,    -1,   828,    -1,   105,    -1,   107,    33,    34,
     110,   111,   112,   113,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    -1,    54,
     485,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    77,    -1,    79,    -1,    81,   512,    -1,    -1,
     515,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    -1,
      -1,    33,    34,    -1,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    43,   537,    -1,    46,   110,   111,   112,   113,    -1,
      52,   546,    54,    -1,   549,    -1,    58,   552,    -1,    -1,
     555,    -1,   557,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    73,    74,   568,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,
      -1,    -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,
     112,   113,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    46,    47,    -1,    -1,   624,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,    -1,
      81,    -1,    -1,    -1,   659,   660,   661,    -1,    -1,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,   110,
     111,   112,   113,    -1,    -1,    -1,    58,    -1,    -1,    61,
     695,    -1,   697,    -1,   699,   700,   701,    -1,   703,   704,
      -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,   100,    -1,
      -1,    -1,   737,   105,    -1,   107,    -1,   109,   110,   111,
      -1,    -1,    -1,    -1,    -1,   750,   751,   752,   753,   754,
     755,   756,   757,   758,   759,   760,   761,   762,   763,   764,
     765,   766,   767,   768,    -1,    -1,   771,   772,    -1,   774,
      -1,    -1,   777,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   787,    -1,    33,    34,    -1,    -1,    -1,   794,
      -1,    -1,   797,    -1,    43,    -1,    -1,    46,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    -1,    63,    -1,   821,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,   843,   844,
      -1,    90,    -1,   848,    93,    -1,   851,    -1,    -1,    -1,
      99,    -1,    -1,   858,   859,   860,    -1,    -1,    -1,    -1,
      -1,   110,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   877,    -1,   879,    22,    23,    -1,    -1,    26,
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
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    54,    -1,    56,    -1,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    46,    47,    -1,    -1,    99,    -1,    52,
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
      -1,    79,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    47,    -1,    97,
      98,    99,   100,    -1,   102,    -1,    -1,   105,    58,   107,
      60,    61,   110,   111,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    47,    -1,    97,    -1,    99,
     100,    -1,    -1,    -1,   104,   105,    58,   107,    60,    61,
     110,   111,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    97,    -1,    99,   100,    58,
      -1,    -1,    -1,   105,    63,   107,    -1,    -1,   110,   111,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      99,   100,    58,    -1,    -1,    -1,   105,    -1,   107,    -1,
     109,   110,   111,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,   100,    58,    -1,    -1,    -1,   105,
      -1,   107,    -1,   109,   110,   111,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    99,   100,    -1,    -1,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    -1,    64,    65,    26,
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
      -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
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
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      57,    58,    -1,    60,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    45,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,
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
      51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,
      56,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    56,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    26,    27,
      28,    62,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    26,    27,    28,    62,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    -1,    58,    28,    -1,    -1,    62,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    28,    -1,    -1,    62,    -1,
      33,    34,    35,    36,    37,    38,    39,    -1,    41,    42,
      -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    58,    28,    -1,    -1,    62,
      -1,    33,    34,    35,    36,    37,    38,    39,    -1,    41,
      -1,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      62
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
     247,   249,   252,    71,    72,    79,    90,    93,    99,   110,
     111,   123,   124,    48,    49,   264,    46,   264,    46,   124,
     264,   264,    70,    75,    76,    80,    83,    84,    85,    93,
      95,    96,   101,   106,    81,   129,   187,    60,   111,    52,
      60,   145,    60,   145,   127,   128,   230,    52,    44,   264,
      44,   124,    60,    44,    52,    52,   113,   124,   221,    52,
     113,   221,   130,    63,   109,   123,   187,   199,   200,    52,
     113,   124,   187,   124,   111,   124,   187,   110,   123,   124,
     184,   187,   124,   124,   127,   187,   204,   124,   124,   124,
     187,   204,    52,   127,   134,   135,   136,   148,    46,    46,
      33,    34,    43,    46,    52,    54,    63,    66,    67,    68,
      81,   112,   113,   123,   124,   146,   188,   190,   193,   253,
     254,   255,   261,   262,   123,   261,   200,   261,   196,   197,
     264,   124,   132,   133,   256,   261,   130,   261,    50,    51,
     265,    47,    56,   261,   265,    47,    22,    23,    26,    27,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   131,    56,   265,   261,   265,    52,
     124,   175,   215,   124,   181,    60,    60,   206,   210,   124,
     124,   139,   153,   196,   124,   124,   253,    87,    88,    94,
     137,    53,    56,    46,   177,   231,   261,   261,   261,   132,
     256,    81,   187,   190,   193,   261,   261,    58,    59,   123,
      52,    58,   258,    53,    56,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    50,    51,    52,    57,    62,   258,   264,
      45,   265,    45,   185,   124,   198,    59,    45,    56,    45,
      56,    53,    53,   124,    53,   130,   199,    53,   134,    59,
     196,    46,   216,   196,   196,   196,   196,   196,    46,    53,
     187,   136,   150,    72,   127,   128,   141,   178,   187,   238,
     247,   248,   249,   232,    47,    47,    53,    53,   124,   261,
     253,   259,   124,   255,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,    50,   253,   261,   261,    63,   109,   187,
     201,   202,   261,    52,    56,   265,   261,   133,   261,   265,
     265,    53,   265,    53,   251,   261,   176,   221,    46,   182,
     207,   211,   140,   154,   212,   124,   124,   127,   141,   151,
     155,   156,   172,   248,   249,   179,   230,   103,   187,   124,
      47,    60,    68,    82,    86,    98,   102,   123,   127,   141,
     146,   190,   223,   224,   225,   226,   227,   228,   229,   230,
     233,   237,   248,   249,   257,   260,   261,    53,   124,    59,
      60,    45,    55,   261,    53,    55,    56,   265,   134,   124,
     230,    60,    52,    47,   124,   217,   218,    46,    46,    46,
      52,    52,    47,   127,   213,    59,    60,    59,    99,   108,
     127,   149,   156,    47,   124,   124,    59,   250,    60,    52,
      60,   261,    52,   123,    58,    44,    52,    59,   258,   264,
      46,   142,   261,   261,   199,    52,    53,   134,    59,    47,
      56,   183,   212,   212,   134,   134,   187,   142,   261,   124,
     264,    47,    46,   250,   251,    60,   261,    60,   261,    72,
     261,   253,   261,   200,   143,    60,    45,   253,    53,   251,
     218,    47,   127,   186,    47,    47,    53,    53,   124,    60,
     157,   190,   191,   194,    71,    90,   127,   239,   240,    60,
      53,    53,    52,    45,    55,    53,    60,   265,    47,   128,
     141,   144,   252,    53,    69,   111,   184,    60,    46,   265,
     265,   265,    59,    59,    75,   126,    47,   240,   190,   229,
      46,   253,   261,    60,    52,   184,    52,    60,   158,    52,
      52,    52,    46,    46,    72,    79,    93,    99,   110,   111,
     125,    78,   234,    53,    45,   253,    60,   134,   104,   127,
     128,   159,   160,   162,   187,   223,   224,   227,   228,   248,
     249,   261,   261,   261,   243,   241,    59,    59,   229,    33,
      34,    43,    47,    52,    54,    66,    67,    68,    77,    81,
     112,   113,   123,   146,   188,   190,   235,   236,   263,    60,
      53,    53,    91,   124,   163,   164,    46,   187,    47,    53,
      53,    53,    47,   127,    47,   242,   261,    46,   251,   261,
     261,   261,   187,   261,   261,    58,   123,    52,   258,    55,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    44,    50,    51,
      52,    57,    62,   258,   264,    60,    60,    52,    60,   161,
     124,   124,   124,   146,   244,   257,    55,    52,    63,    77,
     167,   168,   171,   245,   246,   261,    60,    53,    53,   124,
     253,   230,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,    50,   253,   261,   261,   202,   261,   256,   158,    60,
      60,    60,    60,    52,   124,    63,    77,   170,   171,   261,
      55,    47,   245,    64,    65,   261,    53,    45,    55,   261,
      53,    55,   265,    53,    47,   253,   127,    53,    56,    64,
      65,   244,   261,   261,   261,   261,    52,    46,    53,    60,
     169,   171,   261,   261,   127,    45,   253,   165,    53,    56,
      60,    53,    47,   166,   167,   171,    55,   124,    60
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
     244,   244,   245,   246,   246,   247,   248,   248,   249,   250,
     250,   251,   252,   253,   253,   254,   254,   255,   255,   255,
     256,   256,   256,   257,   257,   259,   258,   260,   260,   260,
     260,   260,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,   261,   261,   261,   262,   262,   262,   262,   262,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   264,   264,   265,   265
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
       2,     5,     5,     7,     6,     0,     2,     5,     0,     4,
       1,     4,     5,     1,     2,     7,     5,     4,     7,     0,
       2,     1,     2,     0,     1,     1,     3,     1,     3,     1,
       0,     1,     3,     1,     2,     0,     3,     1,     1,     2,
       4,     6,     1,     1,     1,     1,     1,     1,     2,     4,
       6,     3,     3,     3,     2,     2,     2,     2,     2,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     5,     1,     0,     7,     4,     4,     4,     1,
       1,     1,     1,     1,     1,     2,     4,     6,     3,     2,
       2,     2,     2,     2,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     5,     7,     4,
       4,     4,     1,     1,     1,     1
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

  case 227:
#line 671 "p4parser.y"
                                                        { bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 2)); }
#line 4155 "p4parser.tab.c"
    break;

  case 229:
#line 676 "p4parser.y"
                                     {}
#line 4161 "p4parser.tab.c"
    break;

  case 230:
#line 677 "p4parser.y"
                                       {}
#line 4167 "p4parser.tab.c"
    break;

  case 231:
#line 682 "p4parser.y"
                               {}
#line 4173 "p4parser.tab.c"
    break;

  case 232:
#line 683 "p4parser.y"
                                      {}
#line 4179 "p4parser.tab.c"
    break;

  case 233:
#line 687 "p4parser.y"
                                               {}
#line 4185 "p4parser.tab.c"
    break;

  case 234:
#line 688 "p4parser.y"
                                                          {}
#line 4191 "p4parser.tab.c"
    break;

  case 235:
#line 690 "p4parser.y"
                                        {}
#line 4197 "p4parser.tab.c"
    break;

  case 236:
#line 696 "p4parser.y"
                                     {}
#line 4203 "p4parser.tab.c"
    break;

  case 237:
#line 697 "p4parser.y"
                                       {}
#line 4209 "p4parser.tab.c"
    break;

  case 238:
#line 698 "p4parser.y"
                                       {}
#line 4215 "p4parser.tab.c"
    break;

  case 239:
#line 699 "p4parser.y"
                                       {}
#line 4221 "p4parser.tab.c"
    break;

  case 240:
#line 700 "p4parser.y"
                                       {}
#line 4227 "p4parser.tab.c"
    break;

  case 241:
#line 704 "p4parser.y"
                                     {}
#line 4233 "p4parser.tab.c"
    break;

  case 242:
#line 705 "p4parser.y"
                                       {}
#line 4239 "p4parser.tab.c"
    break;

  case 243:
#line 709 "p4parser.y"
                                     {}
#line 4245 "p4parser.tab.c"
    break;

  case 244:
#line 710 "p4parser.y"
                                       {}
#line 4251 "p4parser.tab.c"
    break;

  case 245:
#line 714 "p4parser.y"
                                     {}
#line 4257 "p4parser.tab.c"
    break;

  case 246:
#line 718 "p4parser.y"
                                              {}
#line 4263 "p4parser.tab.c"
    break;

  case 247:
#line 722 "p4parser.y"
                                                    {}
#line 4269 "p4parser.tab.c"
    break;

  case 248:
#line 723 "p4parser.y"
                                                      {}
#line 4275 "p4parser.tab.c"
    break;

  case 249:
#line 727 "p4parser.y"
                                              {}
#line 4281 "p4parser.tab.c"
    break;

  case 250:
#line 731 "p4parser.y"
           {}
#line 4287 "p4parser.tab.c"
    break;

  case 251:
#line 732 "p4parser.y"
             {}
#line 4293 "p4parser.tab.c"
    break;

  case 252:
#line 733 "p4parser.y"
             {}
#line 4299 "p4parser.tab.c"
    break;

  case 253:
#line 734 "p4parser.y"
             {}
#line 4305 "p4parser.tab.c"
    break;

  case 254:
#line 735 "p4parser.y"
             {}
#line 4311 "p4parser.tab.c"
    break;

  case 255:
#line 737 "p4parser.y"
      {}
#line 4317 "p4parser.tab.c"
    break;

  case 256:
#line 739 "p4parser.y"
      {}
#line 4323 "p4parser.tab.c"
    break;

  case 257:
#line 741 "p4parser.y"
      {}
#line 4329 "p4parser.tab.c"
    break;

  case 258:
#line 744 "p4parser.y"
      {}
#line 4335 "p4parser.tab.c"
    break;

  case 259:
#line 746 "p4parser.y"
      {}
#line 4341 "p4parser.tab.c"
    break;

  case 260:
#line 748 "p4parser.y"
      {}
#line 4347 "p4parser.tab.c"
    break;

  case 261:
#line 752 "p4parser.y"
                {}
#line 4353 "p4parser.tab.c"
    break;

  case 262:
#line 753 "p4parser.y"
                  {}
#line 4359 "p4parser.tab.c"
    break;

  case 263:
#line 754 "p4parser.y"
                  {}
#line 4365 "p4parser.tab.c"
    break;

  case 264:
#line 759 "p4parser.y"
                              {}
#line 4371 "p4parser.tab.c"
    break;

  case 265:
#line 760 "p4parser.y"
                                {}
#line 4377 "p4parser.tab.c"
    break;

  case 266:
#line 764 "p4parser.y"
                                      {}
#line 4383 "p4parser.tab.c"
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
#line 4395 "p4parser.tab.c"
    break;

  case 268:
#line 775 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4403 "p4parser.tab.c"
    break;

  case 269:
#line 781 "p4parser.y"
                                {}
#line 4409 "p4parser.tab.c"
    break;

  case 270:
#line 782 "p4parser.y"
                                  {}
#line 4415 "p4parser.tab.c"
    break;

  case 271:
#line 784 "p4parser.y"
                                  {}
#line 4421 "p4parser.tab.c"
    break;

  case 272:
#line 785 "p4parser.y"
                                       {}
#line 4427 "p4parser.tab.c"
    break;

  case 273:
#line 789 "p4parser.y"
                                   {}
#line 4433 "p4parser.tab.c"
    break;

  case 274:
#line 790 "p4parser.y"
                                     {}
#line 4439 "p4parser.tab.c"
    break;

  case 275:
#line 791 "p4parser.y"
                                       {}
#line 4445 "p4parser.tab.c"
    break;

  case 276:
#line 795 "p4parser.y"
                                {}
#line 4451 "p4parser.tab.c"
    break;

  case 277:
#line 796 "p4parser.y"
                                  {}
#line 4457 "p4parser.tab.c"
    break;

  case 278:
#line 797 "p4parser.y"
                                       {}
#line 4463 "p4parser.tab.c"
    break;

  case 279:
#line 803 "p4parser.y"
                                       {}
#line 4469 "p4parser.tab.c"
    break;

  case 280:
#line 804 "p4parser.y"
                                           {}
#line 4475 "p4parser.tab.c"
    break;

  case 281:
#line 808 "p4parser.y"
                               {}
#line 4481 "p4parser.tab.c"
    break;

  case 282:
#line 809 "p4parser.y"
                                       {}
#line 4487 "p4parser.tab.c"
    break;

  case 283:
#line 810 "p4parser.y"
                                       {}
#line 4493 "p4parser.tab.c"
    break;

  case 284:
#line 811 "p4parser.y"
                                       {}
#line 4499 "p4parser.tab.c"
    break;

  case 285:
#line 812 "p4parser.y"
                                       {}
#line 4505 "p4parser.tab.c"
    break;

  case 286:
#line 816 "p4parser.y"
                                     {}
#line 4511 "p4parser.tab.c"
    break;

  case 287:
#line 817 "p4parser.y"
                                       {}
#line 4517 "p4parser.tab.c"
    break;

  case 288:
#line 818 "p4parser.y"
                                       {}
#line 4523 "p4parser.tab.c"
    break;

  case 289:
#line 819 "p4parser.y"
                                       {}
#line 4529 "p4parser.tab.c"
    break;

  case 290:
#line 823 "p4parser.y"
                               {}
#line 4535 "p4parser.tab.c"
    break;

  case 291:
#line 823 "p4parser.y"
                                                    {}
#line 4541 "p4parser.tab.c"
    break;

  case 292:
#line 825 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4550 "p4parser.tab.c"
    break;

  case 293:
#line 834 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4559 "p4parser.tab.c"
    break;

  case 294:
#line 841 "p4parser.y"
                                     {}
#line 4565 "p4parser.tab.c"
    break;

  case 295:
#line 841 "p4parser.y"
                                                          {}
#line 4571 "p4parser.tab.c"
    break;

  case 296:
#line 842 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4580 "p4parser.tab.c"
    break;

  case 297:
#line 849 "p4parser.y"
                                     {}
#line 4586 "p4parser.tab.c"
    break;

  case 298:
#line 850 "p4parser.y"
                                       {}
#line 4592 "p4parser.tab.c"
    break;

  case 299:
#line 854 "p4parser.y"
                                           {}
#line 4598 "p4parser.tab.c"
    break;

  case 300:
#line 859 "p4parser.y"
                  {}
#line 4604 "p4parser.tab.c"
    break;

  case 301:
#line 860 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4613 "p4parser.tab.c"
    break;

  case 302:
#line 864 "p4parser.y"
                                       {}
#line 4619 "p4parser.tab.c"
    break;

  case 303:
#line 865 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4628 "p4parser.tab.c"
    break;

  case 304:
#line 872 "p4parser.y"
                            {}
#line 4634 "p4parser.tab.c"
    break;

  case 305:
#line 873 "p4parser.y"
                                                        {}
#line 4640 "p4parser.tab.c"
    break;

  case 306:
#line 877 "p4parser.y"
                               {}
#line 4646 "p4parser.tab.c"
    break;

  case 307:
#line 882 "p4parser.y"
        {}
#line 4652 "p4parser.tab.c"
    break;

  case 308:
#line 887 "p4parser.y"
        {}
#line 4658 "p4parser.tab.c"
    break;

  case 309:
#line 892 "p4parser.y"
                            {}
#line 4664 "p4parser.tab.c"
    break;

  case 310:
#line 893 "p4parser.y"
                                {}
#line 4670 "p4parser.tab.c"
    break;

  case 311:
#line 897 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4679 "p4parser.tab.c"
    break;

  case 312:
#line 901 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4688 "p4parser.tab.c"
    break;

  case 313:
#line 905 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4697 "p4parser.tab.c"
    break;

  case 314:
#line 909 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4706 "p4parser.tab.c"
    break;

  case 315:
#line 920 "p4parser.y"
        {}
#line 4712 "p4parser.tab.c"
    break;

  case 316:
#line 923 "p4parser.y"
        {}
#line 4718 "p4parser.tab.c"
    break;

  case 317:
#line 926 "p4parser.y"
        {}
#line 4724 "p4parser.tab.c"
    break;

  case 318:
#line 931 "p4parser.y"
                   {}
#line 4730 "p4parser.tab.c"
    break;

  case 319:
#line 935 "p4parser.y"
                   {}
#line 4736 "p4parser.tab.c"
    break;

  case 320:
#line 939 "p4parser.y"
                                {}
#line 4742 "p4parser.tab.c"
    break;

  case 321:
#line 940 "p4parser.y"
                                  {}
#line 4748 "p4parser.tab.c"
    break;

  case 322:
#line 945 "p4parser.y"
        {}
#line 4754 "p4parser.tab.c"
    break;

  case 323:
#line 947 "p4parser.y"
        {}
#line 4760 "p4parser.tab.c"
    break;

  case 324:
#line 952 "p4parser.y"
                                                              {}
#line 4766 "p4parser.tab.c"
    break;

  case 325:
#line 956 "p4parser.y"
                                     {}
#line 4772 "p4parser.tab.c"
    break;

  case 326:
#line 957 "p4parser.y"
                                       {}
#line 4778 "p4parser.tab.c"
    break;

  case 327:
#line 958 "p4parser.y"
                                       {}
#line 4784 "p4parser.tab.c"
    break;

  case 328:
#line 959 "p4parser.y"
                                       {}
#line 4790 "p4parser.tab.c"
    break;

  case 329:
#line 960 "p4parser.y"
                                       {}
#line 4796 "p4parser.tab.c"
    break;

  case 330:
#line 961 "p4parser.y"
                                       {}
#line 4802 "p4parser.tab.c"
    break;

  case 331:
#line 962 "p4parser.y"
                                       {}
#line 4808 "p4parser.tab.c"
    break;

  case 332:
#line 963 "p4parser.y"
                                       {}
#line 4814 "p4parser.tab.c"
    break;

  case 333:
#line 967 "p4parser.y"
                           {}
#line 4820 "p4parser.tab.c"
    break;

  case 334:
#line 968 "p4parser.y"
                             {}
#line 4826 "p4parser.tab.c"
    break;

  case 335:
#line 972 "p4parser.y"
                                          {}
#line 4832 "p4parser.tab.c"
    break;

  case 336:
#line 973 "p4parser.y"
                                            {}
#line 4838 "p4parser.tab.c"
    break;

  case 337:
#line 977 "p4parser.y"
                                                                  {}
#line 4844 "p4parser.tab.c"
    break;

  case 338:
#line 981 "p4parser.y"
                             {}
#line 4850 "p4parser.tab.c"
    break;

  case 339:
#line 982 "p4parser.y"
                               {}
#line 4856 "p4parser.tab.c"
    break;

  case 340:
#line 986 "p4parser.y"
                                     {}
#line 4862 "p4parser.tab.c"
    break;

  case 341:
#line 987 "p4parser.y"
                                       {}
#line 4868 "p4parser.tab.c"
    break;

  case 342:
#line 991 "p4parser.y"
                             {}
#line 4874 "p4parser.tab.c"
    break;

  case 343:
#line 992 "p4parser.y"
                               {}
#line 4880 "p4parser.tab.c"
    break;

  case 344:
#line 996 "p4parser.y"
                             {}
#line 4886 "p4parser.tab.c"
    break;

  case 345:
#line 997 "p4parser.y"
                               {}
#line 4892 "p4parser.tab.c"
    break;

  case 346:
#line 998 "p4parser.y"
                               {}
#line 4898 "p4parser.tab.c"
    break;

  case 347:
#line 999 "p4parser.y"
                               {}
#line 4904 "p4parser.tab.c"
    break;

  case 348:
#line 1007 "p4parser.y"
          {}
#line 4910 "p4parser.tab.c"
    break;

  case 349:
#line 1011 "p4parser.y"
                                       {}
#line 4916 "p4parser.tab.c"
    break;

  case 350:
#line 1012 "p4parser.y"
                                         {}
#line 4922 "p4parser.tab.c"
    break;

  case 351:
#line 1017 "p4parser.y"
        {}
#line 4928 "p4parser.tab.c"
    break;

  case 352:
#line 1019 "p4parser.y"
        {}
#line 4934 "p4parser.tab.c"
    break;

  case 353:
#line 1021 "p4parser.y"
        {}
#line 4940 "p4parser.tab.c"
    break;

  case 354:
#line 1023 "p4parser.y"
        {}
#line 4946 "p4parser.tab.c"
    break;

  case 355:
#line 1027 "p4parser.y"
                                       {}
#line 4952 "p4parser.tab.c"
    break;

  case 356:
#line 1028 "p4parser.y"
                                         {}
#line 4958 "p4parser.tab.c"
    break;

  case 357:
#line 1033 "p4parser.y"
                                         {}
#line 4964 "p4parser.tab.c"
    break;

  case 358:
#line 1037 "p4parser.y"
           {}
#line 4970 "p4parser.tab.c"
    break;

  case 359:
#line 1039 "p4parser.y"
        {}
#line 4976 "p4parser.tab.c"
    break;

  case 360:
#line 1044 "p4parser.y"
        {}
#line 4982 "p4parser.tab.c"
    break;

  case 361:
#line 1046 "p4parser.y"
        {}
#line 4988 "p4parser.tab.c"
    break;

  case 362:
#line 1051 "p4parser.y"
        {}
#line 4994 "p4parser.tab.c"
    break;

  case 363:
#line 1055 "p4parser.y"
                                   {}
#line 5000 "p4parser.tab.c"
    break;

  case 364:
#line 1056 "p4parser.y"
                                     {}
#line 5006 "p4parser.tab.c"
    break;

  case 365:
#line 1062 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 5015 "p4parser.tab.c"
    break;

  case 366:
#line 1071 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5024 "p4parser.tab.c"
    break;

  case 367:
#line 1075 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5033 "p4parser.tab.c"
    break;

  case 368:
#line 1083 "p4parser.y"
                                     {}
#line 5039 "p4parser.tab.c"
    break;

  case 369:
#line 1087 "p4parser.y"
                                     {}
#line 5045 "p4parser.tab.c"
    break;

  case 370:
#line 1088 "p4parser.y"
                                          {}
#line 5051 "p4parser.tab.c"
    break;

  case 371:
#line 1092 "p4parser.y"
                                        {}
#line 5057 "p4parser.tab.c"
    break;

  case 372:
#line 1098 "p4parser.y"
                                       {}
#line 5063 "p4parser.tab.c"
    break;

  case 373:
#line 1102 "p4parser.y"
                                       {}
#line 5069 "p4parser.tab.c"
    break;

  case 374:
#line 1103 "p4parser.y"
                                         {}
#line 5075 "p4parser.tab.c"
    break;

  case 375:
#line 1107 "p4parser.y"
                                       {}
#line 5081 "p4parser.tab.c"
    break;

  case 376:
#line 1108 "p4parser.y"
                                           {}
#line 5087 "p4parser.tab.c"
    break;

  case 377:
#line 1112 "p4parser.y"
                                       {}
#line 5093 "p4parser.tab.c"
    break;

  case 378:
#line 1113 "p4parser.y"
                                            {}
#line 5099 "p4parser.tab.c"
    break;

  case 379:
#line 1114 "p4parser.y"
                                              {}
#line 5105 "p4parser.tab.c"
    break;

  case 380:
#line 1118 "p4parser.y"
                                       {}
#line 5111 "p4parser.tab.c"
    break;

  case 381:
#line 1119 "p4parser.y"
                                         {}
#line 5117 "p4parser.tab.c"
    break;

  case 382:
#line 1120 "p4parser.y"
                                           {}
#line 5123 "p4parser.tab.c"
    break;

  case 383:
#line 1124 "p4parser.y"
                                       {}
#line 5129 "p4parser.tab.c"
    break;

  case 384:
#line 1125 "p4parser.y"
                                         {}
#line 5135 "p4parser.tab.c"
    break;

  case 385:
#line 1129 "p4parser.y"
        {}
#line 5141 "p4parser.tab.c"
    break;

  case 386:
#line 1129 "p4parser.y"
                {}
#line 5147 "p4parser.tab.c"
    break;

  case 387:
#line 1133 "p4parser.y"
                                       {}
#line 5153 "p4parser.tab.c"
    break;

  case 388:
#line 1134 "p4parser.y"
                                         {}
#line 5159 "p4parser.tab.c"
    break;

  case 389:
#line 1135 "p4parser.y"
                                         {}
#line 5165 "p4parser.tab.c"
    break;

  case 390:
#line 1136 "p4parser.y"
                                                     {}
#line 5171 "p4parser.tab.c"
    break;

  case 391:
#line 1137 "p4parser.y"
                                                             {}
#line 5177 "p4parser.tab.c"
    break;

  case 392:
#line 1141 "p4parser.y"
                                       {}
#line 5183 "p4parser.tab.c"
    break;

  case 393:
#line 1142 "p4parser.y"
                                         {}
#line 5189 "p4parser.tab.c"
    break;

  case 394:
#line 1143 "p4parser.y"
                                         {}
#line 5195 "p4parser.tab.c"
    break;

  case 395:
#line 1144 "p4parser.y"
                                         {}
#line 5201 "p4parser.tab.c"
    break;

  case 396:
#line 1145 "p4parser.y"
                                         {}
#line 5207 "p4parser.tab.c"
    break;

  case 397:
#line 1146 "p4parser.y"
                                         {}
#line 5213 "p4parser.tab.c"
    break;

  case 398:
#line 1147 "p4parser.y"
                                         {}
#line 5219 "p4parser.tab.c"
    break;

  case 399:
#line 1148 "p4parser.y"
                                                     {}
#line 5225 "p4parser.tab.c"
    break;

  case 400:
#line 1149 "p4parser.y"
                                                                 {}
#line 5231 "p4parser.tab.c"
    break;

  case 401:
#line 1150 "p4parser.y"
                                                 {}
#line 5237 "p4parser.tab.c"
    break;

  case 402:
#line 1151 "p4parser.y"
                                                 {}
#line 5243 "p4parser.tab.c"
    break;

  case 403:
#line 1152 "p4parser.y"
                                                 {}
#line 5249 "p4parser.tab.c"
    break;

  case 404:
#line 1153 "p4parser.y"
                                         {}
#line 5255 "p4parser.tab.c"
    break;

  case 405:
#line 1154 "p4parser.y"
                                                {}
#line 5261 "p4parser.tab.c"
    break;

  case 406:
#line 1155 "p4parser.y"
                                           {}
#line 5267 "p4parser.tab.c"
    break;

  case 407:
#line 1156 "p4parser.y"
                                          {}
#line 5273 "p4parser.tab.c"
    break;

  case 408:
#line 1158 "p4parser.y"
        {}
#line 5279 "p4parser.tab.c"
    break;

  case 409:
#line 1160 "p4parser.y"
        {}
#line 5285 "p4parser.tab.c"
    break;

  case 410:
#line 1161 "p4parser.y"
                                         {}
#line 5291 "p4parser.tab.c"
    break;

  case 411:
#line 1162 "p4parser.y"
                                         {}
#line 5297 "p4parser.tab.c"
    break;

  case 412:
#line 1163 "p4parser.y"
                                         {}
#line 5303 "p4parser.tab.c"
    break;

  case 413:
#line 1164 "p4parser.y"
                                         {}
#line 5309 "p4parser.tab.c"
    break;

  case 414:
#line 1165 "p4parser.y"
                                          {}
#line 5315 "p4parser.tab.c"
    break;

  case 415:
#line 1166 "p4parser.y"
                                           {}
#line 5321 "p4parser.tab.c"
    break;

  case 416:
#line 1167 "p4parser.y"
                                            {}
#line 5327 "p4parser.tab.c"
    break;

  case 417:
#line 1168 "p4parser.y"
                                             {}
#line 5333 "p4parser.tab.c"
    break;

  case 418:
#line 1169 "p4parser.y"
                                        {}
#line 5339 "p4parser.tab.c"
    break;

  case 419:
#line 1171 "p4parser.y"
        {}
#line 5345 "p4parser.tab.c"
    break;

  case 420:
#line 1172 "p4parser.y"
                                       {}
#line 5351 "p4parser.tab.c"
    break;

  case 421:
#line 1173 "p4parser.y"
                                       {}
#line 5357 "p4parser.tab.c"
    break;

  case 422:
#line 1175 "p4parser.y"
                                         {}
#line 5363 "p4parser.tab.c"
    break;

  case 423:
#line 1176 "p4parser.y"
                                             {}
#line 5369 "p4parser.tab.c"
    break;

  case 424:
#line 1178 "p4parser.y"
                                       {}
#line 5375 "p4parser.tab.c"
    break;

  case 425:
#line 1179 "p4parser.y"
                                       {}
#line 5381 "p4parser.tab.c"
    break;

  case 426:
#line 1180 "p4parser.y"
                                             {}
#line 5387 "p4parser.tab.c"
    break;

  case 427:
#line 1181 "p4parser.y"
                                             {}
#line 5393 "p4parser.tab.c"
    break;

  case 428:
#line 1182 "p4parser.y"
                                            {}
#line 5399 "p4parser.tab.c"
    break;

  case 429:
#line 1183 "p4parser.y"
                                       {}
#line 5405 "p4parser.tab.c"
    break;

  case 430:
#line 1184 "p4parser.y"
                                        {}
#line 5411 "p4parser.tab.c"
    break;

  case 431:
#line 1185 "p4parser.y"
                                       {}
#line 5417 "p4parser.tab.c"
    break;

  case 432:
#line 1186 "p4parser.y"
                                                      {}
#line 5423 "p4parser.tab.c"
    break;

  case 433:
#line 1187 "p4parser.y"
                         {}
#line 5429 "p4parser.tab.c"
    break;

  case 435:
#line 1191 "p4parser.y"
        {}
#line 5435 "p4parser.tab.c"
    break;

  case 436:
#line 1193 "p4parser.y"
        {}
#line 5441 "p4parser.tab.c"
    break;

  case 437:
#line 1195 "p4parser.y"
        {}
#line 5447 "p4parser.tab.c"
    break;

  case 438:
#line 1196 "p4parser.y"
                                                      {}
#line 5453 "p4parser.tab.c"
    break;

  case 439:
#line 1200 "p4parser.y"
                                       {}
#line 5459 "p4parser.tab.c"
    break;

  case 440:
#line 1201 "p4parser.y"
                                         {}
#line 5465 "p4parser.tab.c"
    break;

  case 441:
#line 1202 "p4parser.y"
                                         {}
#line 5471 "p4parser.tab.c"
    break;

  case 442:
#line 1203 "p4parser.y"
                                         {}
#line 5477 "p4parser.tab.c"
    break;

  case 443:
#line 1204 "p4parser.y"
                                         {}
#line 5483 "p4parser.tab.c"
    break;

  case 444:
#line 1205 "p4parser.y"
                                         {}
#line 5489 "p4parser.tab.c"
    break;

  case 445:
#line 1206 "p4parser.y"
                                         {}
#line 5495 "p4parser.tab.c"
    break;

  case 446:
#line 1207 "p4parser.y"
                                                             {}
#line 5501 "p4parser.tab.c"
    break;

  case 447:
#line 1208 "p4parser.y"
                                                                         {}
#line 5507 "p4parser.tab.c"
    break;

  case 448:
#line 1209 "p4parser.y"
                                                 {}
#line 5513 "p4parser.tab.c"
    break;

  case 449:
#line 1210 "p4parser.y"
                                         {}
#line 5519 "p4parser.tab.c"
    break;

  case 450:
#line 1211 "p4parser.y"
                                                {}
#line 5525 "p4parser.tab.c"
    break;

  case 451:
#line 1212 "p4parser.y"
                                           {}
#line 5531 "p4parser.tab.c"
    break;

  case 452:
#line 1213 "p4parser.y"
                                          {}
#line 5537 "p4parser.tab.c"
    break;

  case 453:
#line 1215 "p4parser.y"
        {}
#line 5543 "p4parser.tab.c"
    break;

  case 454:
#line 1217 "p4parser.y"
        {}
#line 5549 "p4parser.tab.c"
    break;

  case 455:
#line 1218 "p4parser.y"
                                                 {}
#line 5555 "p4parser.tab.c"
    break;

  case 456:
#line 1219 "p4parser.y"
                                                 {}
#line 5561 "p4parser.tab.c"
    break;

  case 457:
#line 1220 "p4parser.y"
                                                 {}
#line 5567 "p4parser.tab.c"
    break;

  case 458:
#line 1221 "p4parser.y"
                                                 {}
#line 5573 "p4parser.tab.c"
    break;

  case 459:
#line 1222 "p4parser.y"
                                                  {}
#line 5579 "p4parser.tab.c"
    break;

  case 460:
#line 1223 "p4parser.y"
                                                   {}
#line 5585 "p4parser.tab.c"
    break;

  case 461:
#line 1224 "p4parser.y"
                                                    {}
#line 5591 "p4parser.tab.c"
    break;

  case 462:
#line 1225 "p4parser.y"
                                                     {}
#line 5597 "p4parser.tab.c"
    break;

  case 463:
#line 1226 "p4parser.y"
                                                {}
#line 5603 "p4parser.tab.c"
    break;

  case 464:
#line 1228 "p4parser.y"
        {}
#line 5609 "p4parser.tab.c"
    break;

  case 465:
#line 1229 "p4parser.y"
                                               {}
#line 5615 "p4parser.tab.c"
    break;

  case 466:
#line 1230 "p4parser.y"
                                               {}
#line 5621 "p4parser.tab.c"
    break;

  case 467:
#line 1232 "p4parser.y"
                                         {}
#line 5627 "p4parser.tab.c"
    break;

  case 468:
#line 1233 "p4parser.y"
                                                     {}
#line 5633 "p4parser.tab.c"
    break;

  case 469:
#line 1234 "p4parser.y"
                                               {}
#line 5639 "p4parser.tab.c"
    break;

  case 470:
#line 1235 "p4parser.y"
                                               {}
#line 5645 "p4parser.tab.c"
    break;

  case 471:
#line 1236 "p4parser.y"
                                                     {}
#line 5651 "p4parser.tab.c"
    break;

  case 472:
#line 1237 "p4parser.y"
                                                     {}
#line 5657 "p4parser.tab.c"
    break;

  case 473:
#line 1238 "p4parser.y"
                                                    {}
#line 5663 "p4parser.tab.c"
    break;

  case 474:
#line 1239 "p4parser.y"
                                               {}
#line 5669 "p4parser.tab.c"
    break;

  case 475:
#line 1240 "p4parser.y"
                                                {}
#line 5675 "p4parser.tab.c"
    break;

  case 476:
#line 1241 "p4parser.y"
                                               {}
#line 5681 "p4parser.tab.c"
    break;

  case 477:
#line 1242 "p4parser.y"
                                                              {}
#line 5687 "p4parser.tab.c"
    break;

  case 478:
#line 1244 "p4parser.y"
        {}
#line 5693 "p4parser.tab.c"
    break;

  case 479:
#line 1246 "p4parser.y"
        {}
#line 5699 "p4parser.tab.c"
    break;

  case 480:
#line 1248 "p4parser.y"
        {}
#line 5705 "p4parser.tab.c"
    break;

  case 481:
#line 1249 "p4parser.y"
                                                      {}
#line 5711 "p4parser.tab.c"
    break;


#line 5715 "p4parser.tab.c"

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
#line 1277 "p4parser.y"


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
