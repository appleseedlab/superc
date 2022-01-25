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
#define YYLAST   3944

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  170
/* YYNRULES -- Number of rules.  */
#define YYNRULES  508
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  906

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
     461,   464,   466,   469,   475,   480,   481,   485,   486,   490,
     491,   495,   502,   502,   501,   508,   509,   513,   514,   515,
     516,   521,   522,   520,   530,   531,   535,   535,   541,   542,
     546,   547,   548,   549,   550,   551,   552,   556,   556,   561,
     562,   566,   567,   571,   576,   577,   581,   586,   587,   591,
     593,   597,   598,   603,   604,   605,   606,   610,   611,   612,
     613,   614,   618,   621,   624,   633,   635,   632,   641,   642,
     640,   650,   651,   655,   656,   657,   658,   659,   663,   670,
     674,   675,   675,   669,   676,   677,   681,   685,   686,   691,
     690,   696,   697,   698,   698,   703,   709,   710,   711,   712,
     713,   717,   718,   722,   723,   727,   731,   735,   736,   740,
     744,   745,   746,   747,   748,   749,   751,   753,   756,   758,
     760,   765,   766,   767,   772,   773,   777,   777,   777,   781,
     788,   794,   795,   797,   798,   802,   803,   804,   808,   809,
     810,   816,   817,   821,   822,   823,   824,   825,   829,   830,
     831,   832,   837,   838,   836,   848,   850,   847,   859,   861,
     858,   868,   869,   873,   878,   877,   883,   883,   891,   892,
     896,   900,   905,   911,   912,   916,   920,   924,   928,   938,
     940,   945,   947,   952,   956,   960,   961,   965,   967,   973,
     977,   978,   979,   980,   981,   982,   983,   984,   988,   988,
     993,   994,   998,  1002,  1003,  1007,  1008,  1012,  1013,  1017,
    1018,  1019,  1020,  1027,  1027,  1026,  1032,  1033,  1037,  1039,
    1041,  1043,  1048,  1049,  1053,  1058,  1059,  1064,  1068,  1070,
    1075,  1080,  1081,  1087,  1087,  1097,  1101,  1108,  1113,  1114,
    1118,  1124,  1124,  1128,  1129,  1133,  1134,  1138,  1139,  1140,
    1144,  1145,  1146,  1150,  1151,  1155,  1155,  1159,  1160,  1161,
    1162,  1166,  1167,  1170,  1171,  1172,  1173,  1174,  1175,  1176,
    1177,  1178,  1179,  1180,  1181,  1182,  1183,  1184,  1185,  1186,
    1188,  1190,  1191,  1192,  1193,  1194,  1195,  1196,  1197,  1198,
    1199,  1201,  1202,  1203,  1205,  1207,  1208,  1209,  1210,  1211,
    1212,  1213,  1214,  1215,  1216,  1218,  1219,  1221,  1223,  1225,
    1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,  1238,
    1239,  1240,  1241,  1242,  1243,  1245,  1247,  1248,  1249,  1250,
    1251,  1252,  1253,  1254,  1255,  1256,  1258,  1259,  1260,  1262,
    1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,
    1274,  1275,  1277,  1279,  1281,  1304,  1304,  1305,  1305
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
  "instantiationWithAssignment", "objInitializer", "objDeclarations",
  "objDeclaration", "optConstructorParameters", "dotPrefix",
  "parserDeclaration", "$@4", "$@5", "parserLocalElements",
  "parserLocalElement", "parserTypeDeclaration", "$@6", "$@7",
  "parserStates", "parserState", "$@8", "parserStatements",
  "parserStatement", "parserBlockStatement", "$@9", "transitionStatement",
  "stateExpression", "selectExpression", "selectCaseList", "selectCase",
  "keysetExpression", "tupleKeysetExpression", "simpleExpressionList",
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

#define YYTABLE_NINF (-401)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -815,    33,  -815,   244,  -815,  -815,  -815,   873,  -815,   252,
      -8,   252,    13,  -815,   252,   252,  -815,  -815,  -815,  -815,
    1549,   179,  -815,    76,  -815,  -815,   -30,  -815,   -12,  -815,
       4,  -815,  -815,  -815,    95,  -815,   247,  -815,  -815,   142,
    -815,   873,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
     122,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,    41,  -815,  -815,   -36,   873,   -34,   873,
    2478,   -13,   873,   721,   873,   869,  2521,   873,   873,   179,
     873,   873,   873,   179,  -815,  -815,   176,  -815,  -815,   141,
    -815,   192,  -815,   202,   197,  1429,  2340,  2478,  2340,   252,
    -815,  1500,  -815,  2340,   256,  -815,     2,  2340,   256,   143,
    -815,  -815,  -815,  -815,  -815,    53,  2340,   256,   210,   873,
    -815,    -5,  -815,   873,   116,   206,   227,   229,  -815,   252,
     252,    88,   197,   873,   873,  -815,  -815,   252,   873,   873,
    1429,   240,   197,  -815,  -815,   263,  -815,  2340,  2340,  2340,
    1942,  1187,  2340,  -815,  -815,  -815,  -815,   258,  -815,  -815,
     251,   264,   943,   270,   250,  -815,   271,   273,  -815,  3612,
    -815,  -815,  2798,    53,  2835,  -815,  -815,  -815,   267,   282,
     274,  -815,   275,  3612,  1769,  2872,  -815,  -815,  -815,  -815,
     873,  2909,  -815,  -815,  2478,  -815,  2946,  -815,   141,   280,
     252,   288,  -815,   252,  -815,  -815,   294,   296,  -815,  -815,
     252,   252,   297,  -815,  -815,   293,  -815,   186,   292,  -815,
    -815,  -815,  -815,   126,   126,   126,   170,   189,   258,   299,
      86,    85,  2983,   126,   873,  2340,  -815,  1429,  -815,  -815,
     873,  2144,  2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,
    2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,
    2340,   310,  1429,  2340,  2340,  -815,  1006,  -815,  -815,  -815,
     309,   873,  2340,  -815,   873,  2340,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,   256,  -815,   256,  -815,   256,
     311,  2340,  -815,   873,   316,  -815,  -815,  -815,  -815,  -815,
    -815,   873,  -815,  -815,  -815,   721,   197,   179,   385,  -815,
    -815,  -815,  2340,  -815,  -815,  3612,   314,   873,   254,  -815,
    1653,  1653,  1213,  3756,  3723,  3789,  3789,   319,   319,   319,
     319,   126,   126,   126,  3820,  3882,  3851,  2687,  1653,  2340,
     317,  3020,   319,  -815,  -815,  -815,  -815,   219,  1653,   141,
    -815,   313,  3612,  -815,  3612,  1861,  -815,  -815,  -815,  -815,
     320,  3612,   321,   203,   873,   330,  -815,  -815,   327,   329,
    -815,   261,   873,  -815,   -47,   179,  -815,  -815,    92,  -815,
    -815,    70,  -815,  -815,   197,   -25,  -815,  -815,  -815,  -815,
    -815,  -815,  1649,   126,  -815,  -815,   336,  -815,  -815,  2340,
    1213,  -815,  2340,  2478,   332,   333,   873,   256,  -815,   197,
    -815,   141,  -815,   326,   207,  -815,  -815,   105,   130,   141,
     141,   150,   336,  -815,   337,   873,   252,   339,   290,   345,
    -815,   338,  -815,  -815,   873,  -815,  -815,  -815,   335,   346,
    2193,   347,  -815,     1,  -815,   943,   198,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,   144,  -815,   342,  3057,  3686,  -815,  1429,  -815,  -815,
    -815,  -815,   355,  2340,  -815,   873,  -815,   721,   368,  -815,
     369,   371,   372,   374,   362,  2340,  -815,   721,   338,  -815,
    2340,   366,   381,   384,  -815,  2340,  -815,  3094,  2340,  -815,
     359,  2340,  1429,  2340,  -815,  -815,  2478,   511,  -815,  -815,
     382,  -815,  -815,  -815,   182,   873,  -815,  -815,  -815,  -815,
    -815,  -815,  3612,   388,   256,   256,   256,   379,  -815,  -815,
    -815,  -815,  3131,  -815,  3168,   390,  2724,   387,  3205,    53,
    -815,   179,  -815,  -815,  -815,  -815,   762,   397,  -815,  -815,
     391,  -815,   395,   396,   400,  -815,    25,   818,   407,  1429,
    -815,  2340,   401,  -815,   403,   456,   408,   402,  -815,  -815,
    -815,  2387,  2340,  2340,  2340,   404,   405,   392,    50,  -815,
     411,   406,  -815,   417,  3242,  -815,  1429,   413,   141,  -815,
     460,     7,   179,  -815,  -815,   428,   873,  -815,  -815,  -815,
    -815,  -815,  -815,  3279,  3316,  3353,   435,   436,   410,     8,
     439,  -815,   818,  2242,   423,  -815,   434,  -815,   441,   445,
     442,  -815,  -815,  -815,   873,  -815,   873,   873,   873,  -815,
    -815,   440,  -815,  -815,  -815,  -815,  -815,   444,  -815,  -815,
    2340,  2340,  2340,  -815,  1187,  2340,  -815,  -815,  -815,  -815,
     443,  -815,  -815,  -815,   943,   452,   250,  -815,   450,  3649,
    -815,  -815,   446,   448,  1991,  -815,  -815,   449,   455,   461,
     188,  2291,   476,  2340,   126,   126,   126,   470,  3390,   126,
     873,  -815,  1429,  -815,   -15,  2340,  2340,  2340,  2340,  2340,
    2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,  2340,
    2340,  2340,  2340,  2340,   474,  1429,  2340,  2340,  -815,  1006,
    -815,  -815,   118,  2435,  -815,  -815,  -815,  -815,   631,  -815,
    -815,  -815,  3427,  2042,   466,  2340,  -815,  -815,   480,  -815,
    1653,  1653,  1213,  3756,  3723,  3789,  3789,   319,   319,   319,
     319,   126,   126,   126,  3820,  3882,  3851,  2761,  1653,  2340,
     481,  3464,   319,   219,  1653,   490,  -815,   991,   483,   489,
     873,  1124,  -815,  -815,   494,  -815,  -815,  -815,  1270,  2647,
    -815,   126,  -815,  -815,  2340,  1213,  -815,  2340,   502,  -815,
    -815,  1429,   197,   499,   504,   515,   508,  2607,   631,  -815,
    -815,  2340,  2340,  3501,  3686,  1429,  1343,   521,   517,  -815,
    2093,  2340,  2340,   197,  3612,  3612,  -815,   530,  -815,  -815,
     531,  -815,  -815,   153,  -815,  3538,  3575,   529,  -815,   873,
    -815,  2093,  -815,   533,  -815,  -815
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   161,     6,     0,   260,   262,
     261,   264,     0,   263,     0,     0,   272,   273,   253,     5,
       0,    34,    35,     0,    13,   150,     0,    10,   159,    12,
     159,     8,   234,   391,   271,   255,   247,   250,   249,   248,
     246,     0,    11,   293,   298,   300,   299,   301,    14,    15,
       0,     9,     7,    16,    20,    18,    22,    19,    23,    21,
      17,    25,    24,    37,   505,   506,     0,     0,     0,     0,
     285,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    33,   261,    36,     0,   297,   254,   135,
     295,     0,   296,     0,    33,   455,   455,   285,   455,   274,
     294,   455,    42,   455,     0,   323,     0,   455,     0,     0,
     284,   283,   282,   281,   286,     0,   455,     0,     0,     0,
     218,   253,   314,     0,   273,   229,     0,     0,   271,   274,
     274,     0,    34,     0,     0,   145,   171,   274,     0,     0,
     455,     0,    33,   162,   215,     0,   392,   455,   455,   455,
     455,   455,   455,   399,   415,   416,   417,     0,   414,   413,
     418,     0,     0,     0,   251,   252,     0,   394,   395,   397,
     454,   418,     0,     0,     0,   239,   275,   276,     0,     0,
      41,   131,    40,   401,     0,     0,   507,   508,   265,   321,
       0,     0,   266,   322,     0,   256,     0,   267,   135,     0,
     274,     0,   316,   274,   235,   236,     0,     0,   327,   328,
     274,   274,     0,   325,   326,     0,   160,   144,   136,   137,
     165,   221,   348,   428,   427,   426,     0,     0,   261,     0,
     247,   248,     0,   425,     0,   455,   419,   455,   405,   429,
       0,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,     0,   455,   455,   455,   431,   455,   257,   259,   258,
       0,     0,   455,    39,     0,   455,    45,   104,   103,    99,
     100,   102,   101,   106,   108,   107,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,    95,
     122,    96,    42,    38,   123,   124,   130,   125,   126,   127,
     128,   129,   105,    90,    98,    97,    84,    61,    82,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    62,    63,    64,    65,    66,    67,
      68,    76,    69,    70,    71,    73,    72,    74,    75,    77,
      78,    79,    80,    81,    83,    85,    86,    87,    88,    89,
      91,    92,    93,    94,    44,     0,   324,     0,   287,     0,
       0,   455,   219,     0,     0,   230,   302,   308,   146,   172,
     305,     0,   141,   143,   142,     0,    33,    33,    33,   350,
     423,   422,   455,   424,   430,   398,     0,     0,     0,   396,
     441,   442,   439,   451,   452,   445,   446,   435,   436,   437,
     438,   432,   433,   434,   449,   447,   448,     0,   444,   455,
       0,     0,   450,   290,   289,   288,   291,     0,   443,   135,
     279,   277,   133,   132,   402,     0,   268,   269,   270,   383,
       0,   390,     0,     0,     0,     0,   311,   311,     0,     0,
     311,     0,     0,   138,     0,    34,   168,   166,    33,   174,
     170,     0,   169,   167,    33,     0,   226,   222,   225,   224,
     227,   223,    33,   459,   458,   406,     0,   149,   420,   455,
     440,   457,   455,     0,     0,     0,     0,     0,    43,    33,
     387,   135,   315,     0,     0,   318,   231,    33,    33,   135,
     135,    33,     0,   148,   139,     0,     0,     0,     0,     0,
     175,   388,   216,   228,     0,   349,   333,   408,     0,     0,
     455,     0,   403,     0,   362,     0,   247,   340,   329,   343,
     346,   345,   342,   341,   361,   344,   347,   351,   359,   360,
     407,     0,   155,     0,     0,   453,   292,   455,   240,   280,
     278,   384,     0,   455,   317,     0,   237,     0,     0,   312,
       0,     0,     0,     0,     0,   455,   176,     0,   388,   164,
     455,     0,     0,     0,   334,   455,   335,     0,   455,   404,
       0,   455,   455,   455,   409,   410,   285,     0,   153,   421,
       0,   220,   320,   319,    33,     0,   304,   310,   147,   173,
     307,   152,   140,     0,     0,     0,     0,     0,   389,   386,
     217,   363,     0,   336,     0,     0,     0,     0,     0,     0,
     154,     0,   158,   156,   157,   456,     0,     0,   238,   243,
       0,   178,     0,     0,     0,   385,    33,    33,     0,   455,
     411,   455,     0,   330,     0,     0,   253,     0,   233,   244,
     313,    33,   455,   455,   455,     0,     0,    31,    33,   366,
       0,   337,   353,     0,     0,   331,   455,     0,   135,   241,
       0,     0,    34,   179,   185,     0,     0,   180,   182,   186,
     181,   183,   184,     0,     0,     0,     0,     0,    32,     0,
       0,   367,    33,   500,     0,   412,     0,   242,     0,     0,
       0,   190,   192,   187,     0,   177,     0,     0,     0,   375,
     372,     0,    28,    30,    29,    26,    27,     0,   365,   338,
     455,   455,   455,   352,   455,   455,   462,   463,   464,   357,
       0,   461,   460,   465,     0,     0,   251,   354,     0,   358,
     499,   339,     0,     0,   455,   191,   178,     0,     0,     0,
      33,   455,     0,   455,   473,   472,   471,     0,     0,   470,
       0,   466,   455,   474,   356,   455,   455,   455,   455,   455,
     455,   455,   455,   455,   455,   455,   455,   455,   455,   455,
     455,   455,   455,   455,     0,   455,   455,   455,   476,   455,
     332,   245,     0,    33,   214,   213,   212,   369,     0,   376,
     368,   373,     0,   455,     0,   455,   469,   475,     0,   355,
     486,   487,   484,   496,   497,   490,   491,   480,   481,   482,
     483,   477,   478,   479,   494,   492,   493,     0,   489,   455,
       0,     0,   495,     0,   488,     0,   188,     0,     0,   378,
       0,   455,   211,   210,     0,   197,   198,   381,   455,   207,
     371,   504,   503,   467,   455,   485,   502,   455,     0,   194,
     377,   455,    33,   206,   205,     0,     0,   207,     0,   370,
     382,   455,   455,     0,   498,   455,   455,     0,     0,   200,
     455,   455,   455,    33,   208,   209,   468,     0,   193,   195,
       0,   379,   374,     0,   201,   203,   204,     0,   501,     0,
     199,   455,   380,     0,   202,   196
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -815,  -815,  -815,  -815,  -815,    -7,   138,  -815,  -815,    19,
       0,   -19,  -815,   289,  -815,   451,   322,  -188,  -815,  -815,
     208,  -815,  -815,  -815,  -815,  -364,  -815,    96,  -815,  -815,
     575,   125,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,   148,  -815,  -139,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -267,  -815,  -815,  -815,  -814,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,
    -815,  -815,  -815,  -815,   -69,  -815,  -815,  -815,  -815,    16,
     -81,  -815,   262,    47,  -815,   344,    48,  -815,   -86,  -815,
    -815,  -815,  -815,  -186,   -93,  -815,  -172,  -815,    27,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -169,  -815,
    -815,  -815,  -815,  -815,    64,  -815,  -815,   -58,  -815,  -639,
    -815,  -637,  -815,  -815,  -636,  -634,  -608,   -89,  -815,  -815,
    -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,  -815,   -35,
    -815,  -815,  -815,  -815,  -243,  -222,  -815,   239,  -815,  -367,
       6,    60,  -528,    42,  -815,  -114,  -815,   393,  -149,  -785,
    -158,  -815,  -815,  -815,   896,  -815,  -815,  -815,    21,   177
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    19,   171,   161,   717,   689,   145,
     132,    22,   179,   184,   364,   180,   181,   141,   142,   218,
     219,   385,    23,   210,   448,    24,    25,   543,   587,   623,
      91,   162,    27,   220,   509,   387,   457,    28,   211,   449,
     458,   459,   603,   651,   673,   674,   746,   675,   701,   702,
     876,   889,   844,   845,   893,   865,   846,   460,    29,   221,
     572,    30,   200,   442,   388,   467,   512,    31,   203,   445,
     556,   627,    32,   594,    33,   270,   628,   649,   629,   113,
     163,    35,   164,    37,    38,   165,    40,    41,   175,   176,
     271,   487,   431,   114,   115,   426,   427,    42,    43,    44,
     446,   558,    45,   450,   563,    46,   447,   560,   497,   559,
      47,   201,   374,   494,   495,    48,    49,   106,    50,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   389,   472,
     536,   693,   737,   738,   537,   468,   636,   690,   658,   659,
     751,   801,   750,   799,   838,   847,   848,    51,   489,   681,
     682,   571,   440,    53,    94,   166,   167,   168,   182,   540,
     265,   397,   541,   585,   169,   170,   739,   740,   266,   188
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   227,    85,    21,   173,   146,   239,   127,   368,    52,
     370,   109,   677,   839,   678,   679,   103,   680,   107,    34,
     462,   470,    20,   456,   466,   592,   215,   866,    73,   661,
      66,   -33,    68,     4,    62,    70,    71,    86,    67,   116,
      89,   -25,   608,   206,   207,    72,     7,   222,    90,   189,
      73,   212,   505,   703,   -25,   -25,    89,    97,   190,    69,
      62,   506,    62,   112,    92,    62,   894,    62,    62,   125,
      62,    62,   239,    62,    62,    62,    73,   104,   514,   108,
     712,    88,    73,   839,   719,   101,     7,   904,   160,   119,
     112,   123,   128,   102,   160,   133,   655,  -364,   131,   138,
     117,   713,   131,   186,   187,   538,   134,   714,   524,   194,
     139,     7,    62,    85,   372,   656,    62,   375,   715,   716,
     177,   655,    95,   396,   378,   379,    62,    62,    26,    98,
      96,    62,    62,   160,    64,    65,    87,  -252,  -251,  -163,
     656,    54,    55,   160,   238,    63,    26,    95,   420,    56,
     177,   177,  -303,     7,   677,   236,   678,   679,   177,   680,
      57,   217,   -17,    58,   -17,   -17,     7,   229,    75,    59,
     259,   835,    77,    78,   275,    65,   -17,  -309,   262,    99,
      60,    61,   100,    62,   238,    97,    98,   112,   581,    82,
     193,     7,    64,    65,  -134,    26,   582,  -306,    26,   190,
      26,    26,   238,   583,    26,   105,   900,   105,    26,   901,
     118,     7,   120,   122,   126,   129,   130,   390,   135,   136,
     137,   177,    26,   622,   177,   804,   274,    62,   140,  -232,
     160,   177,   177,    62,   160,   797,   391,     5,   143,   178,
       7,   485,    96,     7,    -3,   275,    64,    65,   144,     7,
     492,    97,     8,     9,   554,   160,   580,   199,     7,   190,
      84,   202,   198,   555,    62,    36,   -24,    62,    11,   186,
     187,   208,   209,   382,   383,   483,   213,   214,   498,    13,
     384,   501,   425,    36,    14,   192,    15,   204,   178,   205,
      18,    96,   195,   216,   197,    64,    65,   546,    64,    65,
      64,    65,     5,   552,     6,     7,   186,   187,   238,   222,
     -24,   561,   562,   476,   477,   443,   234,     8,     9,    26,
     502,   503,   237,   235,   240,    10,   272,   273,   366,   241,
     274,   275,    36,    11,   373,    36,    12,    36,    36,   371,
     376,    36,   377,   380,    13,    36,   381,    39,   386,    14,
     268,    15,   392,    16,    17,    18,   253,   254,   255,    36,
     419,   429,   444,   259,   439,    39,    62,   474,    65,   486,
     481,   262,   394,   491,    62,   513,   496,   238,   398,   499,
     490,   500,   542,   584,   547,   553,   548,   455,   455,   505,
      62,   140,   569,   463,   471,   574,   565,   570,   575,   578,
     551,   452,   588,   461,   461,   217,   454,   465,   591,   430,
      54,    55,   178,   230,    39,   596,   597,    39,    56,    39,
      39,   600,   601,    39,   598,   599,   609,    39,   610,    57,
     611,   615,    58,   590,   631,   625,    85,    62,    59,   635,
     642,    39,   639,     5,   648,    62,     7,   652,   653,    60,
      61,   650,   654,   662,    62,   666,    36,   464,     8,     9,
     668,   665,   669,   686,   687,   522,    84,   688,   617,   580,
     694,   507,   455,   697,    11,   705,   112,   508,   539,    62,
     698,   709,   710,   741,   692,    13,   718,   742,   461,   711,
      14,   523,    15,   619,   743,   231,    18,   744,    62,   752,
      62,   760,   745,   753,   762,   764,   790,    62,   791,   794,
      26,   105,    26,    26,     5,   795,   557,   557,   579,   451,
     557,   796,   803,   805,   829,   663,   850,   567,   230,     8,
       9,    54,    55,   852,   856,   475,   859,    84,    39,    56,
     160,   861,   436,   860,   437,    11,   438,    97,    62,   868,
      57,   699,   696,    58,   875,  -211,    13,   647,   620,    59,
    -210,    14,   586,    15,   880,    16,    17,    18,   879,     5,
      60,    61,     7,   595,   891,   160,   667,   892,   763,   112,
      26,   788,   493,   898,     8,     9,   899,   621,    62,   902,
     504,   435,    84,   905,   453,   792,   433,   525,   564,   511,
      11,   226,    85,    34,   484,    93,   510,   793,    26,   890,
     231,    13,   735,   626,   605,   606,    14,   833,    15,   593,
      16,    17,    18,   691,   549,   883,   870,   469,   607,   624,
     522,     0,   160,     0,   399,     0,     0,    86,     0,     0,
       0,     0,   128,   566,   522,   568,     0,    36,   808,    36,
      36,   672,   573,    85,     0,   657,     0,     0,     0,   160,
       0,   128,     0,    62,   550,     0,     0,   676,     0,    62,
     671,   830,     0,     0,     0,   809,     0,   657,     0,     0,
       0,     0,    26,     0,     0,   522,   733,     0,   704,     5,
       0,     0,    26,   493,     0,     0,     0,    62,     0,    62,
      62,    62,    54,    55,     0,     0,     0,     0,     0,     0,
      56,    26,    26,     0,     0,     0,     0,    36,     0,     0,
       0,    57,     0,     0,    58,     0,     0,   761,     0,    39,
      59,    39,    39,   630,   526,     0,     0,     0,     0,     0,
     757,    60,     0,     0,     0,    36,    26,   877,     0,     0,
       0,    26,     0,    62,     0,   160,     0,    97,     0,     0,
     789,   887,   525,     0,     0,     0,     0,     0,     0,   798,
      26,     0,     0,     0,     0,     0,   525,     0,   160,     5,
       0,   632,   633,   634,     0,     0,   522,     0,     0,     0,
       0,   522,     0,   672,     8,     9,   644,    26,     0,    39,
       0,     0,    84,     0,     0,   425,     0,     0,   700,   676,
      11,     0,   671,     0,   511,     0,    39,   525,   734,    36,
       5,    13,     0,     0,     0,     0,    14,    39,    15,   604,
     579,   645,    18,    62,     0,     8,     9,     0,     0,     0,
       0,     0,   568,    84,   747,   748,   749,     0,    36,    36,
       0,    11,     0,     0,   160,     0,     0,   229,     0,     0,
       0,   522,    13,     0,     0,     0,     0,    14,   160,    15,
       0,    16,    17,   646,     0,     0,     5,     0,   516,     7,
       0,   878,     0,    36,     0,     0,   517,     0,    36,    54,
      55,     0,    62,     0,     0,     0,     0,    56,   807,   660,
     518,    39,   897,     0,   519,     0,     0,    36,    57,     0,
       0,    58,     0,   526,     0,     0,   520,    59,   525,     0,
     521,     0,     0,   837,     0,     0,     0,     5,    60,    18,
      39,    39,     0,     0,    36,     0,     0,     0,     0,     0,
      54,    55,     8,     9,    54,    55,     0,     0,    56,     0,
      84,     0,    56,     0,   660,   736,     0,     0,    11,    57,
       0,     0,    58,    57,     0,    39,    58,     0,    59,    13,
      39,     0,    59,     0,    14,     0,    15,     0,   862,    60,
     121,     0,     0,    60,    61,     0,   230,     0,     0,    39,
       0,     0,   172,   837,   174,    39,     0,   183,     0,   185,
       0,     0,     0,   191,     0,     0,     0,     0,     0,     0,
     858,     0,   196,     0,    54,    55,    39,     0,     0,     0,
       0,     0,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,     0,    58,   903,     0,   147,
     148,     0,    59,   223,   224,   225,   183,   232,   233,   149,
       0,   230,   150,    60,    88,   526,     0,     0,   151,     0,
     152,     0,    54,    55,     5,     0,     0,     0,   231,   423,
      56,     0,   154,   155,   156,     0,     0,    54,    55,     8,
       9,    57,     0,     0,    58,    56,     0,   228,     0,     0,
      59,     0,     0,     0,     0,    11,    57,     0,     0,    58,
       0,    60,     0,   230,     0,    59,    13,     0,     0,     0,
       0,    14,     0,    15,     0,   424,    60,    18,   158,   159,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   395,     0,   231,     0,     0,     0,    39,   400,   401,
     402,   403,   404,   405,   406,   407,   408,   409,   410,   411,
     412,   413,   414,   415,   416,   417,   418,   147,   148,   421,
     422,     0,   428,     0,     0,     0,     0,   149,   432,     0,
     150,   434,     0,     0,     0,     0,   151,     0,   152,     0,
       0,     0,     5,     0,     0,   231,     0,   863,     0,     0,
     154,   155,   156,     0,     0,    54,    55,     8,     9,     0,
       0,   864,     0,    56,     0,   228,     0,     0,     0,     0,
       0,     0,     0,    11,    57,     0,     0,    58,     0,     0,
     147,   148,     0,    59,    13,     0,     0,     0,     0,    14,
     149,    15,     0,   150,    60,    18,   158,   159,     0,   151,
       0,   152,     0,     0,     0,     5,   249,   250,   251,   252,
     253,   254,   255,   154,   155,   156,     0,   259,    54,    55,
       8,     9,    65,     0,     0,   262,    56,   441,   228,     0,
       0,   238,     0,     0,     0,   264,    11,    57,     0,     0,
      58,     0,     0,     0,     0,     0,    59,    13,   473,     0,
       0,     0,    14,     0,    15,     0,     0,    60,    18,   158,
     159,     0,     0,   147,   148,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,   480,   150,   869,     0,     0,
       0,     0,   841,     0,   152,     0,     0,     0,     5,     0,
       0,     0,     0,   842,     0,     0,   154,   155,   156,     0,
       0,    54,    55,     0,     0,     0,     0,   843,     0,    56,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,     0,    58,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,   544,   147,   148,   545,     0,
      60,    18,   158,   159,     0,     0,   149,     0,     0,   150,
     888,     0,     0,     0,     0,   841,     0,   152,     0,     0,
       0,     5,     0,     0,     0,     0,   842,     0,     0,   154,
     155,   156,     0,     0,    54,    55,   577,     0,     0,     0,
     843,     0,    56,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,     0,    58,     0,     0,     0,
       0,     0,    59,     0,     0,     0,     0,     0,     0,   441,
       0,     0,     0,    60,    18,   158,   159,     0,     0,     0,
       0,   602,   147,   148,     0,     0,   441,     0,     0,     0,
       0,   612,   149,     0,   614,   150,     0,   616,     0,   618,
       0,   151,  -393,   152,     0,     0,     0,     5,     0,     0,
       0,     0,   153,     0,     0,   154,   155,   156,     0,     0,
      54,    55,     0,     0,     0,     0,     0,     0,    56,     0,
     157,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,     0,    58,     0,     0,     0,     0,     0,    59,     0,
       0,     0,     0,   147,   148,     0,     0,   664,     0,    60,
     121,   158,   159,   149,     0,  -400,   150,     0,   683,   684,
     685,     0,   151,     0,   152,     0,  -400,     0,     5,     0,
       0,     0,     0,     0,     0,     0,   154,   155,   156,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,    56,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,     0,    58,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      60,   121,   158,   159,     0,     0,   754,   755,   756,    72,
     758,   759,     0,     0,    73,    74,     0,     0,     0,    75,
       0,     0,    76,    77,    78,     0,     0,     0,     0,     0,
     183,     0,    79,     0,    80,    81,     0,   802,     0,   441,
      82,     0,     0,     0,     0,    83,     0,     0,     0,     0,
       0,   810,   811,   812,   813,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   824,   825,   826,   827,   828,
       0,   244,   831,   832,     0,   834,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   515,   259,     0,   849,
       0,   851,    65,     0,   261,   262,     0,     5,     0,   516,
       7,   238,     0,     0,     0,   264,     0,   517,     0,     0,
      54,    55,     8,     9,     0,   855,     0,     0,    56,     0,
      84,   518,     0,     0,     0,   519,     0,   867,    11,    57,
       0,     0,    58,     0,   849,     0,     0,   520,    59,    13,
     873,   521,     0,   874,    14,     0,    15,     0,     0,    60,
      18,     0,     0,     0,     0,     0,     0,   884,   885,     0,
       0,     0,   849,     0,     0,     0,   849,   895,   896,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   276,     0,     0,     0,   277,   278,   849,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   276,     0,     0,     0,   277,   278,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   488,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   147,   148,     0,     0,     0,
       0,     0,     0,     0,     0,   149,     0,     0,   150,  -400,
       0,     0,     0,     0,   151,     0,   152,     0,  -400,     0,
       5,     0,     0,     0,     0,     0,     0,     0,   154,   155,
     156,     0,     0,    54,    55,     0,     0,     0,     0,     0,
       0,    56,     0,   157,   147,   148,     0,     0,     0,     0,
       0,     0,    57,     0,   149,    58,     0,   150,     0,     0,
       0,    59,     0,   151,  -400,   152,     0,  -400,     0,     5,
       0,     0,    60,   121,   158,   159,     0,   154,   155,   156,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
      56,     0,   157,     0,     0,   147,   148,     0,     0,     0,
       0,    57,     0,     0,    58,   149,     0,     0,   150,     0,
      59,     0,     0,     0,   841,     0,   152,     0,     0,     0,
       5,    60,    18,   158,   159,   842,     0,     0,   154,   155,
     156,     0,     0,    54,    55,     0,     0,     0,     0,   843,
       0,    56,     0,   157,     0,     0,   147,   148,     0,     0,
       0,     0,    57,     0,     0,    58,   149,     0,     0,   150,
       0,    59,     0,     0,     0,   151,     0,   152,     0,     0,
       0,     5,    60,    18,   158,   159,   842,     0,     0,   154,
     155,   156,     0,     0,    54,    55,     0,     0,     0,     0,
     843,     0,    56,     0,   157,     0,     0,   147,   148,     0,
       0,     0,     0,    57,     0,     0,    58,   149,     0,     0,
     150,     0,    59,     0,     0,     0,   151,     0,   152,     0,
       0,     0,     5,    60,    18,   158,   159,   153,     0,     0,
     154,   155,   156,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,    56,     0,   157,   147,   148,     0,     0,
       0,     0,     0,     0,    57,     0,   149,    58,     0,   150,
       0,     0,     0,    59,     0,   151,     0,   152,     0,     0,
       0,     5,     0,   576,    60,   121,   158,   159,     0,   154,
     155,   156,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,    56,     0,   157,   720,   721,     0,     0,     0,
       0,     0,     0,    57,     0,   722,    58,     0,     0,   723,
       0,     0,    59,     0,   724,     0,   725,     0,     0,     0,
       5,     0,     0,    60,    18,   158,   159,     0,   726,   727,
     728,     0,     0,    54,    55,     0,     0,     0,     0,   729,
       0,    56,     0,   730,   147,   148,     0,     0,     0,     0,
       0,     0,    57,     0,   149,    58,     0,   150,   800,     0,
       0,    59,     0,   151,     0,   152,     0,     0,     0,     5,
       0,     0,    60,    18,   731,   732,     0,   154,   155,   156,
       0,     0,    54,    55,     0,     0,     0,     0,     0,     0,
      56,     0,   157,   147,   148,     0,     0,     0,     0,     0,
       0,    57,     0,   149,    58,     0,   150,     0,     0,     0,
      59,     0,   151,     0,   152,     0,     0,     0,     5,     0,
       0,    60,    18,   158,   159,     0,   154,   155,   156,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,    56,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,     0,    58,  -189,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     5,     0,   516,     7,     0,
      60,    18,   158,   159,     0,   517,     0,     0,    54,    55,
       8,     9,     0,     0,     0,     0,    56,     0,    84,     0,
       0,     0,     0,   519,     0,     0,    11,    57,     0,     0,
      58,     0,   836,     0,     0,     0,    59,    13,     0,     0,
       0,   670,    14,     5,    15,   516,     7,    60,    18,     0,
       0,     0,     0,   517,     0,     0,    54,    55,     8,     9,
       0,     0,     0,     0,    56,     0,    84,     0,     0,     0,
       0,   519,     0,     0,    11,    57,     0,     0,    58,     0,
       0,     0,     0,     0,    59,    13,     5,     0,     0,     0,
      14,   110,    15,     0,     0,    60,    18,     0,     0,    54,
      55,     8,     9,     0,     0,     0,     0,    56,     0,    84,
       0,     0,     0,     0,     0,     0,     0,    11,    57,     0,
       0,    58,     0,     0,     0,     0,     0,    59,    13,     5,
       0,     0,     0,    14,     0,    15,     0,   111,    60,    18,
       0,     0,    54,    55,     8,     9,     0,     0,     0,     0,
      56,     0,    84,     0,     0,     0,     0,     0,     0,     0,
      11,    57,     0,     0,    58,     0,     0,     0,     0,     0,
      59,    13,     0,     0,     0,     0,    14,     0,    15,     0,
      16,   124,   121,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   259,     0,     0,     0,    64,    65,   260,   261,   262,
     393,     0,     0,     0,   263,   238,     0,     0,     0,   264,
       0,   881,   882,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   259,     0,     0,     0,    64,    65,   260,   261,   262,
       0,     0,     0,     0,   263,   238,     0,     0,     0,   264,
       0,   871,   872,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   259,   478,     0,     0,    64,    65,   260,   261,   262,
       0,     0,   479,     0,   263,   238,     0,     0,     0,   264,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,     0,   259,   640,
       0,     0,    64,    65,   260,   261,   262,     0,     0,   641,
       0,   263,   238,     0,     0,     0,   264,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   259,   853,     0,     0,    64,
      65,   260,   261,   262,     0,     0,   854,     0,   263,   238,
       0,     0,     0,   264,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,     0,   259,   267,     0,     0,    64,    65,   260,   261,
     262,     0,     0,     0,     0,   263,   238,     0,     0,     0,
     264,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,     0,   259,
     269,     0,     0,    64,    65,   260,   261,   262,     0,     0,
       0,     0,   263,   238,     0,     0,     0,   264,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,     0,   259,     0,     0,     0,
      64,    65,   260,   261,   262,   365,     0,     0,     0,   263,
     238,     0,     0,     0,   264,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,   259,     0,     0,     0,    64,    65,   260,
     261,   262,   367,     0,     0,     0,   263,   238,     0,     0,
       0,   264,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
     259,     0,     0,     0,    64,    65,   260,   261,   262,   369,
       0,     0,     0,   263,   238,     0,     0,     0,   264,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,     0,   259,     0,     0,
       0,    64,    65,   260,   261,   262,   393,     0,     0,     0,
     263,   238,     0,     0,     0,   264,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,     0,   259,     0,     0,     0,    64,    65,
     260,   261,   262,     0,     0,   482,     0,   263,   238,     0,
       0,     0,   264,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   259,   589,     0,     0,    64,    65,   260,   261,   262,
       0,     0,     0,     0,   263,   238,     0,     0,     0,   264,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,     0,   259,     0,
       0,     0,    64,    65,   260,   261,   262,     0,     0,     0,
       0,   263,   238,     0,   613,     0,   264,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   259,     0,     0,     0,    64,
      65,   260,   261,   262,   637,     0,     0,     0,   263,   238,
       0,     0,     0,   264,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,     0,   259,     0,     0,     0,    64,    65,   260,   261,
     262,   638,     0,     0,     0,   263,   238,     0,     0,     0,
     264,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,     0,   259,
       0,     0,     0,    64,    65,   260,   261,   262,     0,     0,
       0,     0,   263,   238,     0,   643,     0,   264,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,     0,   259,   695,     0,     0,
      64,    65,   260,   261,   262,     0,     0,     0,     0,   263,
     238,     0,     0,     0,   264,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,   259,     0,     0,     0,    64,    65,   260,
     261,   262,   706,     0,     0,     0,   263,   238,     0,     0,
       0,   264,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
     259,     0,     0,     0,    64,    65,   260,   261,   262,   707,
       0,     0,     0,   263,   238,     0,     0,     0,   264,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,     0,   259,     0,     0,
       0,    64,    65,   260,   261,   262,   708,     0,     0,     0,
     263,   238,     0,     0,     0,   264,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,     0,   259,     0,     0,     0,    64,    65,
     260,   261,   262,   806,     0,     0,     0,   263,   238,     0,
       0,     0,   264,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   259,     0,     0,     0,    64,    65,   260,   261,   262,
       0,     0,   840,     0,   263,   238,     0,     0,     0,   264,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,     0,   259,     0,
       0,     0,    64,    65,   260,   261,   262,     0,     0,   857,
       0,   263,   238,     0,     0,     0,   264,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   259,   886,     0,     0,    64,
      65,   260,   261,   262,     0,     0,     0,     0,   263,   238,
       0,     0,     0,   264,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,     0,   259,     0,     0,     0,    64,    65,   260,   261,
     262,     0,     0,     0,  -208,   263,   238,     0,     0,     0,
     264,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,     0,   259,
       0,     0,     0,    64,    65,   260,   261,   262,     0,     0,
       0,  -209,   263,   238,     0,     0,     0,   264,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,     0,   259,     0,     0,     0,
      64,    65,   260,   261,   262,     0,     0,     0,     0,   263,
     238,     0,     0,     0,   264,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,   777,   778,   779,
     780,   781,     0,   782,     0,     0,     0,    64,    65,   783,
     784,   785,     0,     0,     0,     0,   786,   238,     0,     0,
       0,   787,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
     259,     0,     0,     0,    64,    65,   260,   261,   262,     0,
       0,     0,     0,     0,   238,     0,     0,     0,   264,   242,
     243,   244,   245,     0,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,     0,   259,     0,     0,
       0,    64,    65,   260,   261,   262,     0,     0,     0,     0,
       0,   238,   242,   243,   244,   264,     0,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,     0,
     259,     0,     0,     0,    64,    65,   260,   261,   262,     0,
       0,     0,     0,     0,   238,   242,   243,   244,   264,     0,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,     0,   259,     0,     0,     0,    64,    65,   260,
     261,   262,     0,     0,     0,     0,     0,   238,   244,     0,
       0,   264,     0,   249,   250,   251,   252,   253,   254,   255,
       0,   257,   258,     0,   259,     0,     0,     0,     0,    65,
       0,   261,   262,     0,     0,     0,     0,     0,   238,   244,
       0,     0,   264,     0,   249,   250,   251,   252,   253,   254,
     255,     0,   257,     0,     0,   259,     0,     0,     0,     0,
      65,     0,   261,   262,     0,     0,     0,     0,     0,   238,
     244,     0,     0,   264,     0,   249,   250,   251,   252,   253,
     254,   255,     0,     0,     0,     0,   259,     0,     0,     0,
       0,    65,     0,   261,   262,     0,     0,     0,     0,     0,
     238,     0,     0,     0,   264
};

static const yytype_int16 yycheck[] =
{
       7,   150,    21,     3,    97,    94,   164,    76,   194,     3,
     198,    69,   651,   798,   651,   651,    52,   651,    52,     3,
     387,   388,     3,   387,   388,   553,   140,   841,    75,   637,
       9,    46,    11,     0,    41,    14,    15,    21,    46,    52,
      52,    46,   570,   129,   130,    70,    61,    46,    60,    47,
      75,   137,    99,    46,    59,    60,    52,    36,    56,    46,
      67,   108,    69,    70,    60,    72,   880,    74,    75,    76,
      77,    78,   230,    80,    81,    82,    75,   113,   103,   113,
      72,   111,    75,   868,   692,    44,    61,   901,    95,    73,
      97,    75,    76,    52,   101,    79,    71,    47,    79,    83,
     113,    93,    83,    50,    51,   472,    79,    99,   472,    56,
      83,    61,   119,   132,   200,    90,   123,   203,   110,   111,
      99,    71,    52,   237,   210,   211,   133,   134,     3,    44,
      44,   138,   139,   140,    48,    49,    60,    52,    52,    47,
      90,    71,    72,   150,    58,     7,    21,    52,   262,    79,
     129,   130,    47,    61,   793,   162,   793,   793,   137,   793,
      90,   142,    46,    93,    48,    49,    61,   151,    80,    99,
      44,    53,    84,    85,    56,    49,    60,    47,    52,    41,
     110,   111,    60,   190,    58,   164,    44,   194,    44,   101,
      47,    61,    48,    49,    53,    70,    52,    47,    73,    56,
      75,    76,    58,    59,    79,    67,    53,    69,    83,    56,
      72,    61,    74,    75,    76,    77,    78,    47,    80,    81,
      82,   200,    97,   587,   203,   753,    56,   234,    52,    47,
     237,   210,   211,   240,   241,    47,    47,    58,    46,   101,
      61,   429,    44,    61,     0,    56,    48,    49,    46,    61,
      47,   230,    73,    74,    47,   262,    58,   119,    61,    56,
      81,   123,    52,    56,   271,     3,    60,   274,    89,    50,
      51,   133,   134,    87,    88,    56,   138,   139,   447,   100,
      94,   450,   266,    21,   105,   108,   107,    60,   150,    60,
     111,    44,   115,    53,   117,    48,    49,   483,    48,    49,
      48,    49,    58,   491,    60,    61,    50,    51,    58,    46,
      59,   499,   500,    59,    60,   373,    58,    73,    74,   194,
      59,    60,    52,    59,    53,    81,    59,    45,   190,    56,
      56,    56,    70,    89,    46,    73,    92,    75,    76,    59,
      46,    79,    46,    46,   100,    83,    53,     3,    56,   105,
     173,   107,    53,   109,   110,   111,    37,    38,    39,    97,
      50,    52,    46,    44,    53,    21,   373,    53,    49,    56,
      53,    52,   234,    52,   381,   464,    46,    58,   240,    52,
      60,    52,    46,   541,    52,    59,    53,   387,   388,    99,
     397,    52,    47,   387,   388,    60,    59,    59,    52,    52,
     489,   385,    60,   387,   388,   386,   387,   388,    53,   271,
      71,    72,   274,   151,    70,    47,    47,    73,    79,    75,
      76,    47,    60,    79,    53,    53,    60,    83,    47,    90,
      46,    72,    93,   547,    46,    53,   455,   444,    99,    60,
      53,    97,    52,    58,    47,   452,    61,    52,    52,   110,
     111,    60,    52,    46,   461,    52,   194,    72,    73,    74,
      52,    60,    60,    59,    59,   472,    81,    75,   582,    58,
      53,   455,   472,    60,    89,    47,   483,   458,   472,   486,
     668,    46,    46,    60,    78,   100,    47,    53,   472,    79,
     105,   472,   107,   586,    53,   151,   111,    52,   505,    59,
     507,    58,    60,    59,    52,    55,    60,   514,    60,    60,
     385,   373,   387,   388,    58,    60,   497,   498,   525,   381,
     501,    60,    46,    53,    50,   639,    60,   506,   266,    73,
      74,    71,    72,    53,    53,   397,    46,    81,   194,    79,
     547,    52,   365,    60,   367,    89,   369,   526,   555,    55,
      90,    91,   666,    93,    52,    56,   100,   626,    47,    99,
      56,   105,   541,   107,    56,   109,   110,   111,    53,    58,
     110,   111,    61,   557,    53,   582,   645,    60,   736,   586,
     455,   739,   444,    53,    73,    74,    55,   587,   595,    60,
     452,   302,    81,    60,   386,   744,   274,   472,   502,   461,
      89,   150,   621,   587,   427,    30,   458,   746,   483,   876,
     266,   100,   693,   594,   567,   567,   105,   789,   107,   555,
     109,   110,   111,   658,   486,   868,   848,   388,   568,   587,
     637,    -1,   639,    -1,   241,    -1,    -1,   621,    -1,    -1,
      -1,    -1,   626,   505,   651,   507,    -1,   385,   762,   387,
     388,   651,   514,   672,    -1,   636,    -1,    -1,    -1,   666,
      -1,   645,    -1,   670,   487,    -1,    -1,   651,    -1,   676,
     651,   785,    -1,    -1,    -1,   764,    -1,   658,    -1,    -1,
      -1,    -1,   557,    -1,    -1,   692,   693,    -1,   672,    58,
      -1,    -1,   567,   555,    -1,    -1,    -1,   704,    -1,   706,
     707,   708,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,   586,   587,    -1,    -1,    -1,    -1,   455,    -1,    -1,
      -1,    90,    -1,    -1,    93,    -1,    -1,   734,    -1,   385,
      99,   387,   388,   595,   472,    -1,    -1,    -1,    -1,    -1,
     724,   110,    -1,    -1,    -1,   483,   621,   861,    -1,    -1,
      -1,   626,    -1,   760,    -1,   762,    -1,   736,    -1,    -1,
     739,   875,   637,    -1,    -1,    -1,    -1,    -1,    -1,   750,
     645,    -1,    -1,    -1,    -1,    -1,   651,    -1,   785,    58,
      -1,   604,   605,   606,    -1,    -1,   793,    -1,    -1,    -1,
      -1,   798,    -1,   793,    73,    74,   619,   672,    -1,   455,
      -1,    -1,    81,    -1,    -1,   789,    -1,    -1,   670,   793,
      89,    -1,   793,    -1,   676,    -1,   472,   692,   693,   557,
      58,   100,    -1,    -1,    -1,    -1,   105,   483,   107,   567,
     837,    69,   111,   840,    -1,    73,    74,    -1,    -1,    -1,
      -1,    -1,   704,    81,   706,   707,   708,    -1,   586,   587,
      -1,    89,    -1,    -1,   861,    -1,    -1,   841,    -1,    -1,
      -1,   868,   100,    -1,    -1,    -1,    -1,   105,   875,   107,
      -1,   109,   110,   111,    -1,    -1,    58,    -1,    60,    61,
      -1,   862,    -1,   621,    -1,    -1,    68,    -1,   626,    71,
      72,    -1,   899,    -1,    -1,    -1,    -1,    79,   760,   637,
      82,   557,   883,    -1,    86,    -1,    -1,   645,    90,    -1,
      -1,    93,    -1,   651,    -1,    -1,    98,    99,   793,    -1,
     102,    -1,    -1,   798,    -1,    -1,    -1,    58,   110,   111,
     586,   587,    -1,    -1,   672,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    71,    72,    -1,    -1,    79,    -1,
      81,    -1,    79,    -1,   692,   693,    -1,    -1,    89,    90,
      -1,    -1,    93,    90,    -1,   621,    93,    -1,    99,   100,
     626,    -1,    99,    -1,   105,    -1,   107,    -1,   840,   110,
     111,    -1,    -1,   110,   111,    -1,   724,    -1,    -1,   645,
      -1,    -1,    96,   868,    98,   651,    -1,   101,    -1,   103,
      -1,    -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,    -1,
     833,    -1,   116,    -1,    71,    72,   672,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,   899,    -1,    33,
      34,    -1,    99,   147,   148,   149,   150,   151,   152,    43,
      -1,   789,    46,   110,   111,   793,    -1,    -1,    52,    -1,
      54,    -1,    71,    72,    58,    -1,    -1,    -1,   724,    63,
      79,    -1,    66,    67,    68,    -1,    -1,    71,    72,    73,
      74,    90,    -1,    -1,    93,    79,    -1,    81,    -1,    -1,
      99,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,
      -1,   110,    -1,   841,    -1,    99,   100,    -1,    -1,    -1,
      -1,   105,    -1,   107,    -1,   109,   110,   111,   112,   113,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   235,    -1,   789,    -1,    -1,    -1,   793,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,    33,    34,   263,
     264,    -1,   266,    -1,    -1,    -1,    -1,    43,   272,    -1,
      46,   275,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,   841,    -1,    63,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    73,    74,    -1,
      -1,    77,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,
      33,    34,    -1,    99,   100,    -1,    -1,    -1,    -1,   105,
      43,   107,    -1,    46,   110,   111,   112,   113,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    33,    34,    35,    36,
      37,    38,    39,    66,    67,    68,    -1,    44,    71,    72,
      73,    74,    49,    -1,    -1,    52,    79,   371,    81,    -1,
      -1,    58,    -1,    -1,    -1,    62,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    99,   100,   392,    -1,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,   112,
     113,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    -1,   419,    46,    47,    -1,    -1,
      -1,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    77,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,   479,    33,    34,   482,    -1,
     110,   111,   112,   113,    -1,    -1,    43,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,
      67,    68,    -1,    -1,    71,    72,   520,    -1,    -1,    -1,
      77,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    -1,   553,
      -1,    -1,    -1,   110,   111,   112,   113,    -1,    -1,    -1,
      -1,   565,    33,    34,    -1,    -1,   570,    -1,    -1,    -1,
      -1,   575,    43,    -1,   578,    46,    -1,   581,    -1,   583,
      -1,    52,    53,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,    -1,
      -1,    -1,    -1,    33,    34,    -1,    -1,   641,    -1,   110,
     111,   112,   113,    43,    -1,    45,    46,    -1,   652,   653,
     654,    -1,    52,    -1,    54,    -1,    56,    -1,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   111,   112,   113,    -1,    -1,   720,   721,   722,    70,
     724,   725,    -1,    -1,    75,    76,    -1,    -1,    -1,    80,
      -1,    -1,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,
     744,    -1,    93,    -1,    95,    96,    -1,   751,    -1,   753,
     101,    -1,    -1,    -1,    -1,   106,    -1,    -1,    -1,    -1,
      -1,   765,   766,   767,   768,   769,   770,   771,   772,   773,
     774,   775,   776,   777,   778,   779,   780,   781,   782,   783,
      -1,    28,   786,   787,    -1,   789,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    47,    44,    -1,   803,
      -1,   805,    49,    -1,    51,    52,    -1,    58,    -1,    60,
      61,    58,    -1,    -1,    -1,    62,    -1,    68,    -1,    -1,
      71,    72,    73,    74,    -1,   829,    -1,    -1,    79,    -1,
      81,    82,    -1,    -1,    -1,    86,    -1,   841,    89,    90,
      -1,    -1,    93,    -1,   848,    -1,    -1,    98,    99,   100,
     854,   102,    -1,   857,   105,    -1,   107,    -1,    -1,   110,
     111,    -1,    -1,    -1,    -1,    -1,    -1,   871,   872,    -1,
      -1,    -1,   876,    -1,    -1,    -1,   880,   881,   882,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    26,    27,   901,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,    22,    -1,    -1,    -1,    26,    27,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    -1,    54,    -1,    56,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    43,    93,    -1,    46,    -1,    -1,
      -1,    99,    -1,    52,    53,    54,    -1,    56,    -1,    58,
      -1,    -1,   110,   111,   112,   113,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
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
      77,    -1,    79,    -1,    81,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,    43,    -1,    -1,
      46,    -1,    99,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,   110,   111,   112,   113,    63,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,    46,
      -1,    -1,    -1,    99,    -1,    52,    -1,    54,    -1,    -1,
      -1,    58,    -1,    60,   110,   111,   112,   113,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    81,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    43,    93,    -1,    -1,    47,
      -1,    -1,    99,    -1,    52,    -1,    54,    -1,    -1,    -1,
      58,    -1,    -1,   110,   111,   112,   113,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    77,
      -1,    79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    90,    -1,    43,    93,    -1,    46,    47,    -1,
      -1,    99,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,
      -1,    -1,   110,   111,   112,   113,    -1,    66,    67,    68,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    81,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    43,    93,    -1,    46,    -1,    -1,    -1,
      99,    -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,
      -1,   110,   111,   112,   113,    -1,    66,    67,    68,    -1,
      -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,    -1,    93,    47,    -1,    -1,    -1,    -1,    99,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    60,    61,    -1,
     110,   111,   112,   113,    -1,    68,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    -1,
      93,    -1,    47,    -1,    -1,    -1,    99,   100,    -1,    -1,
      -1,   104,   105,    58,   107,    60,    61,   110,   111,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,   100,    58,    -1,    -1,    -1,
     105,    63,   107,    -1,    -1,   110,   111,    -1,    -1,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,    58,
      -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      99,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,    -1,
     109,   110,   111,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      -1,    64,    65,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
      -1,    64,    65,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    45,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    55,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    45,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
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
      -1,    57,    58,    -1,    60,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,
      49,    50,    51,    52,    53,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    58,    -1,    60,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    45,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
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
      -1,    48,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      57,    58,    -1,    -1,    -1,    62,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      -1,    -1,    55,    -1,    57,    58,    -1,    -1,    -1,    62,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,    55,
      -1,    57,    58,    -1,    -1,    -1,    62,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    -1,    44,    45,    -1,    -1,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    58,
      -1,    -1,    -1,    62,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,    -1,
      62,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,    -1,
      -1,    56,    57,    58,    -1,    -1,    -1,    62,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      58,    -1,    -1,    -1,    62,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    58,    26,    27,    28,    62,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    26,    27,    28,    62,    -1,
      -1,    -1,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,    -1,
      -1,    62,    -1,    33,    34,    35,    36,    37,    38,    39,
      -1,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,    49,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,
      -1,    -1,    62,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      28,    -1,    -1,    62,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,   100,   105,   107,   109,   110,   111,   122,
     127,   128,   129,   140,   143,   144,   149,   150,   155,   176,
     179,   185,   190,   192,   197,   199,   200,   201,   202,   203,
     204,   205,   215,   216,   217,   220,   223,   228,   233,   234,
     236,   265,   268,   271,    71,    72,    79,    90,    93,    99,
     110,   111,   123,   124,    48,    49,   286,    46,   286,    46,
     286,   286,    70,    75,    76,    80,    83,    84,    85,    93,
      95,    96,   101,   106,    81,   129,   197,    60,   111,    52,
      60,   148,    60,   148,   272,    52,    44,   286,    44,   124,
      60,    44,    52,    52,   113,   124,   235,    52,   113,   235,
      63,   109,   123,   197,   211,   212,    52,   113,   124,   197,
     124,   111,   124,   197,   110,   123,   124,   192,   197,   124,
     124,   127,   128,   197,   216,   124,   124,   124,   197,   216,
      52,   135,   136,    46,    46,   127,   245,    33,    34,    43,
      46,    52,    54,    63,    66,    67,    68,    81,   112,   113,
     123,   124,   149,   198,   200,   203,   273,   274,   275,   282,
     283,   123,   282,   212,   282,   206,   207,   286,   124,   130,
     133,   134,   276,   282,   131,   282,    50,    51,   287,    47,
      56,   282,   287,    47,    56,   287,   282,   287,    52,   124,
     180,   229,   124,   186,    60,    60,   206,   206,   124,   124,
     141,   156,   206,   124,   124,   273,    53,   127,   137,   138,
     151,   177,    46,   282,   282,   282,   133,   276,    81,   197,
     200,   203,   282,   282,    58,    59,   123,    52,    58,   278,
      53,    56,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    44,
      50,    51,    52,    57,    62,   278,   286,    45,   287,    45,
     193,   208,    59,    45,    56,    56,    22,    26,    27,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   132,    53,   124,    53,   211,    53,
     135,    59,   206,    46,   230,   206,    46,    46,   206,   206,
      46,    53,    87,    88,    94,   139,    56,   153,   182,   246,
      47,    47,    53,    53,   124,   282,   273,   279,   124,   275,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,    50,
     273,   282,   282,    63,   109,   197,   213,   214,   282,    52,
     124,   210,   282,   134,   282,   131,   287,   287,   287,    53,
     270,   282,   181,   235,    46,   187,   218,   224,   142,   157,
     221,   124,   197,   138,   127,   128,   143,   154,   158,   159,
     175,   197,   267,   268,    72,   127,   143,   183,   253,   265,
     267,   268,   247,   282,    53,   124,    59,    60,    45,    55,
     282,    53,    55,    56,   287,   135,    56,   209,    53,   266,
      60,    52,    47,   124,   231,   232,    46,   226,   226,    52,
      52,   226,    59,    60,   124,    99,   108,   197,   127,   152,
     159,   124,   184,   245,   103,    47,    60,    68,    82,    86,
      98,   102,   123,   127,   143,   149,   200,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   248,   252,   267,   268,
     277,   280,    46,   145,   282,   282,   211,    52,    53,   124,
     287,   245,   135,    59,    47,    56,   188,   127,   219,   227,
     225,   135,   135,   222,   145,    59,   124,   286,   124,    47,
      59,   269,   178,   124,    60,    52,    60,   282,    52,   123,
      58,    44,    52,    59,   278,   281,   286,   146,    60,    45,
     273,    53,   270,   232,   191,   197,    47,    47,    53,    53,
      47,    60,   282,   160,   200,   201,   204,   269,   270,    60,
      47,    46,   282,    60,   282,    72,   282,   273,   282,   212,
      47,   128,   143,   147,   271,    53,   127,   189,   194,   196,
     124,    46,   287,   287,   287,    60,   254,    53,    53,    52,
      45,    55,    53,    60,   287,    69,   111,   192,    47,   195,
      60,   161,    52,    52,    52,    71,    90,   127,   256,   257,
     200,   244,    46,   273,   282,    60,    52,   192,    52,    60,
     104,   127,   128,   162,   163,   165,   197,   237,   239,   242,
     243,   267,   268,   282,   282,   282,    59,    59,    75,   126,
     255,   257,    78,   249,    53,    45,   273,    60,   135,    91,
     124,   166,   167,    46,   197,    47,    53,    53,    53,    46,
      46,    79,    72,    93,    99,   110,   111,   125,    47,   244,
      33,    34,    43,    47,    52,    54,    66,    67,    68,    77,
      81,   112,   113,   123,   149,   198,   200,   250,   251,   284,
     285,    60,    53,    53,    52,    60,   164,   124,   124,   124,
     260,   258,    59,    59,   282,   282,   282,   197,   282,   282,
      58,   123,    52,   278,    55,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    44,    50,    51,    52,    57,    62,   278,   286,
      60,    60,   276,   161,    60,    60,    60,    47,   127,   261,
      47,   259,   282,    46,   270,    53,    53,   124,   273,   245,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,    50,
     273,   282,   282,   214,   282,    53,    47,   149,   262,   277,
      55,    52,    63,    77,   170,   171,   174,   263,   264,   282,
      60,   282,    53,    45,    55,   282,    53,    55,   287,    46,
      60,    52,   124,    63,    77,   173,   174,   282,    55,    47,
     263,    64,    65,   282,   282,    52,   168,   273,   127,    53,
      56,    64,    65,   262,   282,   282,    45,   273,    47,   169,
     170,    53,    60,   172,   174,   282,   282,   127,    53,    55,
      53,    56,    60,   124,   174,    60
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
     143,   144,   144,   144,   145,   146,   146,   147,   147,   148,
     148,   149,   151,   152,   150,   153,   153,   154,   154,   154,
     154,   156,   157,   155,   158,   158,   160,   159,   161,   161,
     162,   162,   162,   162,   162,   162,   162,   164,   163,   165,
     165,   166,   166,   167,   168,   168,   169,   170,   170,   171,
     171,   172,   172,   173,   173,   173,   173,   174,   174,   174,
     174,   174,   175,   175,   175,   177,   178,   176,   180,   181,
     179,   182,   182,   183,   183,   183,   183,   183,   184,   186,
     187,   188,   189,   185,   185,   185,   190,   191,   191,   193,
     192,   194,   194,   195,   194,   196,   197,   197,   197,   197,
     197,   198,   198,   199,   199,   200,   201,   202,   202,   203,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   205,   205,   205,   206,   206,   208,   209,   207,   210,
     210,   211,   211,   211,   211,   212,   212,   212,   213,   213,
     213,   214,   214,   215,   215,   215,   215,   215,   216,   216,
     216,   216,   218,   219,   217,   221,   222,   220,   224,   225,
     223,   226,   226,   227,   229,   228,   230,   228,   231,   231,
     232,   233,   234,   235,   235,   236,   236,   236,   236,   237,
     237,   238,   238,   239,   240,   241,   241,   242,   242,   243,
     244,   244,   244,   244,   244,   244,   244,   244,   246,   245,
     247,   247,   248,   249,   249,   250,   250,   251,   251,   252,
     252,   252,   252,   254,   255,   253,   256,   256,   257,   257,
     257,   257,   258,   258,   259,   260,   260,   261,   262,   262,
     263,   264,   264,   266,   265,   267,   267,   268,   269,   269,
     270,   272,   271,   273,   273,   274,   274,   275,   275,   275,
     276,   276,   276,   277,   277,   279,   278,   280,   280,   280,
     280,   281,   281,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   283,   283,   283,   283,   283,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     285,   285,   285,   285,   285,   286,   286,   287,   287
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
       1,     0,     9,     8,     3,     0,     2,     1,     1,     0,
       3,     1,     0,     0,     8,     0,     2,     1,     1,     1,
       1,     0,     0,     9,     1,     2,     0,     8,     0,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     5,     0,
       2,     2,     1,     7,     0,     2,     4,     1,     1,     5,
       3,     1,     3,     3,     3,     1,     1,     1,     3,     3,
       1,     1,    10,    10,    10,     0,     0,     9,     0,     0,
       9,     0,     2,     1,     1,     1,     1,     1,     1,     0,
       0,     0,     0,    11,     1,     4,     4,     0,     2,     0,
       7,     3,     4,     0,     2,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     4,     4,     4,     6,     6,
       6,     1,     1,     1,     0,     1,     0,     0,     5,     1,
       3,     1,     1,     1,     1,     0,     1,     3,     1,     1,
       1,     1,     3,     1,     2,     2,     2,     2,     1,     1,
       1,     1,     0,     0,     9,     0,     0,     9,     0,     0,
       9,     0,     2,     4,     0,     7,     0,     8,     1,     3,
       3,     4,     4,     1,     3,     4,     4,     4,     4,     1,
       4,     5,     8,     1,     2,     2,     3,     5,     7,     7,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     5,
       0,     2,     7,     0,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     0,     0,     8,     1,     2,     5,     5,
       7,     6,     0,     2,     5,     0,     2,     3,     1,     4,
       5,     1,     2,     0,     8,     5,     4,     7,     0,     2,
       1,     0,     3,     0,     1,     1,     3,     1,     3,     1,
       0,     1,     3,     1,     2,     0,     3,     1,     1,     2,
       2,     3,     5,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     3,     3,     3,     2,     2,     2,     2,     2,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     5,     1,     0,     7,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     2,     4,     6,     3,
       2,     2,     2,     2,     2,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     1,
       0,     7,     4,     4,     4,     1,     1,     1,     1
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
#line 2804 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2810 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2816 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2822 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2828 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2834 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2840 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2846 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2852 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2858 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2864 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2870 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2876 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2882 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2888 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2894 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2900 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2906 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2912 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2918 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2924 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2930 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2936 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2942 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2948 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2954 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2960 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2966 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2972 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2978 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2984 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 2990 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 2996 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 3002 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 3008 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 3014 "p4parser.tab.c"
    break;

  case 42:
#line 319 "p4parser.y"
              {}
#line 3020 "p4parser.tab.c"
    break;

  case 43:
#line 321 "p4parser.y"
        {}
#line 3026 "p4parser.tab.c"
    break;

  case 44:
#line 323 "p4parser.y"
        {}
#line 3032 "p4parser.tab.c"
    break;

  case 45:
#line 327 "p4parser.y"
                       {}
#line 3038 "p4parser.tab.c"
    break;

  case 46:
#line 328 "p4parser.y"
                       {}
#line 3044 "p4parser.tab.c"
    break;

  case 47:
#line 329 "p4parser.y"
                       {}
#line 3050 "p4parser.tab.c"
    break;

  case 48:
#line 330 "p4parser.y"
                       {}
#line 3056 "p4parser.tab.c"
    break;

  case 49:
#line 331 "p4parser.y"
                       {}
#line 3062 "p4parser.tab.c"
    break;

  case 50:
#line 332 "p4parser.y"
                       {}
#line 3068 "p4parser.tab.c"
    break;

  case 51:
#line 333 "p4parser.y"
                       {}
#line 3074 "p4parser.tab.c"
    break;

  case 52:
#line 334 "p4parser.y"
                       {}
#line 3080 "p4parser.tab.c"
    break;

  case 53:
#line 335 "p4parser.y"
                       {}
#line 3086 "p4parser.tab.c"
    break;

  case 54:
#line 336 "p4parser.y"
                       {}
#line 3092 "p4parser.tab.c"
    break;

  case 55:
#line 337 "p4parser.y"
                       {}
#line 3098 "p4parser.tab.c"
    break;

  case 56:
#line 338 "p4parser.y"
                       {}
#line 3104 "p4parser.tab.c"
    break;

  case 57:
#line 339 "p4parser.y"
                       {}
#line 3110 "p4parser.tab.c"
    break;

  case 58:
#line 340 "p4parser.y"
                       {}
#line 3116 "p4parser.tab.c"
    break;

  case 59:
#line 341 "p4parser.y"
                       {}
#line 3122 "p4parser.tab.c"
    break;

  case 60:
#line 342 "p4parser.y"
                       {}
#line 3128 "p4parser.tab.c"
    break;

  case 61:
#line 343 "p4parser.y"
                       {}
#line 3134 "p4parser.tab.c"
    break;

  case 62:
#line 344 "p4parser.y"
                       {}
#line 3140 "p4parser.tab.c"
    break;

  case 63:
#line 345 "p4parser.y"
                       {}
#line 3146 "p4parser.tab.c"
    break;

  case 64:
#line 346 "p4parser.y"
                       {}
#line 3152 "p4parser.tab.c"
    break;

  case 65:
#line 347 "p4parser.y"
                       {}
#line 3158 "p4parser.tab.c"
    break;

  case 66:
#line 348 "p4parser.y"
                       {}
#line 3164 "p4parser.tab.c"
    break;

  case 67:
#line 349 "p4parser.y"
                       {}
#line 3170 "p4parser.tab.c"
    break;

  case 68:
#line 350 "p4parser.y"
                       {}
#line 3176 "p4parser.tab.c"
    break;

  case 69:
#line 351 "p4parser.y"
                       {}
#line 3182 "p4parser.tab.c"
    break;

  case 70:
#line 352 "p4parser.y"
                       {}
#line 3188 "p4parser.tab.c"
    break;

  case 71:
#line 353 "p4parser.y"
                       {}
#line 3194 "p4parser.tab.c"
    break;

  case 72:
#line 354 "p4parser.y"
                       {}
#line 3200 "p4parser.tab.c"
    break;

  case 73:
#line 355 "p4parser.y"
                       {}
#line 3206 "p4parser.tab.c"
    break;

  case 74:
#line 356 "p4parser.y"
                       {}
#line 3212 "p4parser.tab.c"
    break;

  case 75:
#line 357 "p4parser.y"
                       {}
#line 3218 "p4parser.tab.c"
    break;

  case 76:
#line 358 "p4parser.y"
                       {}
#line 3224 "p4parser.tab.c"
    break;

  case 77:
#line 359 "p4parser.y"
                       {}
#line 3230 "p4parser.tab.c"
    break;

  case 78:
#line 360 "p4parser.y"
                       {}
#line 3236 "p4parser.tab.c"
    break;

  case 79:
#line 361 "p4parser.y"
                       {}
#line 3242 "p4parser.tab.c"
    break;

  case 80:
#line 362 "p4parser.y"
                       {}
#line 3248 "p4parser.tab.c"
    break;

  case 81:
#line 363 "p4parser.y"
                       {}
#line 3254 "p4parser.tab.c"
    break;

  case 82:
#line 364 "p4parser.y"
                       {}
#line 3260 "p4parser.tab.c"
    break;

  case 83:
#line 365 "p4parser.y"
                       {}
#line 3266 "p4parser.tab.c"
    break;

  case 84:
#line 366 "p4parser.y"
                       {}
#line 3272 "p4parser.tab.c"
    break;

  case 85:
#line 367 "p4parser.y"
                       {}
#line 3278 "p4parser.tab.c"
    break;

  case 86:
#line 368 "p4parser.y"
                       {}
#line 3284 "p4parser.tab.c"
    break;

  case 87:
#line 369 "p4parser.y"
                       {}
#line 3290 "p4parser.tab.c"
    break;

  case 88:
#line 370 "p4parser.y"
                       {}
#line 3296 "p4parser.tab.c"
    break;

  case 89:
#line 371 "p4parser.y"
                       {}
#line 3302 "p4parser.tab.c"
    break;

  case 90:
#line 372 "p4parser.y"
                            {}
#line 3308 "p4parser.tab.c"
    break;

  case 91:
#line 374 "p4parser.y"
                       {}
#line 3314 "p4parser.tab.c"
    break;

  case 92:
#line 375 "p4parser.y"
                       {}
#line 3320 "p4parser.tab.c"
    break;

  case 93:
#line 376 "p4parser.y"
                       {}
#line 3326 "p4parser.tab.c"
    break;

  case 94:
#line 377 "p4parser.y"
                       {}
#line 3332 "p4parser.tab.c"
    break;

  case 95:
#line 378 "p4parser.y"
                       {}
#line 3338 "p4parser.tab.c"
    break;

  case 96:
#line 379 "p4parser.y"
                       {}
#line 3344 "p4parser.tab.c"
    break;

  case 97:
#line 380 "p4parser.y"
                       {}
#line 3350 "p4parser.tab.c"
    break;

  case 98:
#line 381 "p4parser.y"
                       {}
#line 3356 "p4parser.tab.c"
    break;

  case 99:
#line 382 "p4parser.y"
                       {}
#line 3362 "p4parser.tab.c"
    break;

  case 100:
#line 383 "p4parser.y"
                       {}
#line 3368 "p4parser.tab.c"
    break;

  case 101:
#line 384 "p4parser.y"
                       {}
#line 3374 "p4parser.tab.c"
    break;

  case 102:
#line 385 "p4parser.y"
                       {}
#line 3380 "p4parser.tab.c"
    break;

  case 103:
#line 386 "p4parser.y"
                       {}
#line 3386 "p4parser.tab.c"
    break;

  case 104:
#line 387 "p4parser.y"
                       {}
#line 3392 "p4parser.tab.c"
    break;

  case 105:
#line 388 "p4parser.y"
                       {}
#line 3398 "p4parser.tab.c"
    break;

  case 106:
#line 389 "p4parser.y"
                       {}
#line 3404 "p4parser.tab.c"
    break;

  case 108:
#line 391 "p4parser.y"
                       {}
#line 3410 "p4parser.tab.c"
    break;

  case 109:
#line 392 "p4parser.y"
                       {}
#line 3416 "p4parser.tab.c"
    break;

  case 110:
#line 393 "p4parser.y"
                       {}
#line 3422 "p4parser.tab.c"
    break;

  case 111:
#line 394 "p4parser.y"
                       {}
#line 3428 "p4parser.tab.c"
    break;

  case 112:
#line 395 "p4parser.y"
                       {}
#line 3434 "p4parser.tab.c"
    break;

  case 113:
#line 396 "p4parser.y"
                       {}
#line 3440 "p4parser.tab.c"
    break;

  case 114:
#line 397 "p4parser.y"
                       {}
#line 3446 "p4parser.tab.c"
    break;

  case 115:
#line 398 "p4parser.y"
                       {}
#line 3452 "p4parser.tab.c"
    break;

  case 116:
#line 399 "p4parser.y"
                       {}
#line 3458 "p4parser.tab.c"
    break;

  case 117:
#line 400 "p4parser.y"
                       {}
#line 3464 "p4parser.tab.c"
    break;

  case 118:
#line 401 "p4parser.y"
                       {}
#line 3470 "p4parser.tab.c"
    break;

  case 119:
#line 402 "p4parser.y"
                       {}
#line 3476 "p4parser.tab.c"
    break;

  case 120:
#line 403 "p4parser.y"
                       {}
#line 3482 "p4parser.tab.c"
    break;

  case 121:
#line 404 "p4parser.y"
                       {}
#line 3488 "p4parser.tab.c"
    break;

  case 122:
#line 405 "p4parser.y"
                       {}
#line 3494 "p4parser.tab.c"
    break;

  case 123:
#line 406 "p4parser.y"
                       {}
#line 3500 "p4parser.tab.c"
    break;

  case 124:
#line 407 "p4parser.y"
                       {}
#line 3506 "p4parser.tab.c"
    break;

  case 125:
#line 408 "p4parser.y"
                       {}
#line 3512 "p4parser.tab.c"
    break;

  case 126:
#line 409 "p4parser.y"
                       {}
#line 3518 "p4parser.tab.c"
    break;

  case 127:
#line 410 "p4parser.y"
                       {}
#line 3524 "p4parser.tab.c"
    break;

  case 128:
#line 411 "p4parser.y"
                       {}
#line 3530 "p4parser.tab.c"
    break;

  case 129:
#line 412 "p4parser.y"
                       {}
#line 3536 "p4parser.tab.c"
    break;

  case 130:
#line 413 "p4parser.y"
                       {}
#line 3542 "p4parser.tab.c"
    break;

  case 131:
#line 417 "p4parser.y"
                                      {}
#line 3548 "p4parser.tab.c"
    break;

  case 132:
#line 418 "p4parser.y"
                                        {}
#line 3554 "p4parser.tab.c"
    break;

  case 133:
#line 422 "p4parser.y"
                                         {}
#line 3560 "p4parser.tab.c"
    break;

  case 134:
#line 426 "p4parser.y"
                                      {}
#line 3566 "p4parser.tab.c"
    break;

  case 135:
#line 427 "p4parser.y"
      { ReenterScope(subparser); }
#line 3572 "p4parser.tab.c"
    break;

  case 136:
#line 427 "p4parser.y"
                                                         { ExitReentrantScope(subparser); }
#line 3578 "p4parser.tab.c"
    break;

  case 137:
#line 431 "p4parser.y"
                                          {}
#line 3584 "p4parser.tab.c"
    break;

  case 138:
#line 432 "p4parser.y"
                                            {}
#line 3590 "p4parser.tab.c"
    break;

  case 139:
#line 436 "p4parser.y"
                                            {}
#line 3596 "p4parser.tab.c"
    break;

  case 140:
#line 437 "p4parser.y"
                                                              {}
#line 3602 "p4parser.tab.c"
    break;

  case 141:
#line 441 "p4parser.y"
                 {}
#line 3608 "p4parser.tab.c"
    break;

  case 142:
#line 442 "p4parser.y"
                   {}
#line 3614 "p4parser.tab.c"
    break;

  case 143:
#line 443 "p4parser.y"
                   {}
#line 3620 "p4parser.tab.c"
    break;

  case 144:
#line 444 "p4parser.y"
                   {}
#line 3626 "p4parser.tab.c"
    break;

  case 145:
#line 448 "p4parser.y"
                                  {}
#line 3632 "p4parser.tab.c"
    break;

  case 146:
#line 449 "p4parser.y"
                        {}
#line 3638 "p4parser.tab.c"
    break;

  case 147:
#line 450 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3647 "p4parser.tab.c"
    break;

  case 148:
#line 458 "p4parser.y"
                     {}
#line 3653 "p4parser.tab.c"
    break;

  case 149:
#line 460 "p4parser.y"
                     {}
#line 3659 "p4parser.tab.c"
    break;

  case 152:
#line 467 "p4parser.y"
                     {}
#line 3665 "p4parser.tab.c"
    break;

  case 153:
#line 470 "p4parser.y"
                     {}
#line 3671 "p4parser.tab.c"
    break;

  case 154:
#line 476 "p4parser.y"
                               {}
#line 3677 "p4parser.tab.c"
    break;

  case 155:
#line 480 "p4parser.y"
                                     {}
#line 3683 "p4parser.tab.c"
    break;

  case 156:
#line 481 "p4parser.y"
                                     {}
#line 3689 "p4parser.tab.c"
    break;

  case 157:
#line 485 "p4parser.y"
                               {}
#line 3695 "p4parser.tab.c"
    break;

  case 158:
#line 486 "p4parser.y"
                               {}
#line 3701 "p4parser.tab.c"
    break;

  case 159:
#line 490 "p4parser.y"
                           {}
#line 3707 "p4parser.tab.c"
    break;

  case 160:
#line 491 "p4parser.y"
                                     {}
#line 3713 "p4parser.tab.c"
    break;

  case 161:
#line 495 "p4parser.y"
                             {}
#line 3719 "p4parser.tab.c"
    break;

  case 162:
#line 502 "p4parser.y"
              { EnterScope(subparser); }
#line 3725 "p4parser.tab.c"
    break;

  case 163:
#line 502 "p4parser.y"
                                                                          { ExitScope(subparser); }
#line 3731 "p4parser.tab.c"
    break;

  case 164:
#line 503 "p4parser.y"
                             {}
#line 3737 "p4parser.tab.c"
    break;

  case 165:
#line 508 "p4parser.y"
                                           {}
#line 3743 "p4parser.tab.c"
    break;

  case 166:
#line 509 "p4parser.y"
                                             {}
#line 3749 "p4parser.tab.c"
    break;

  case 167:
#line 513 "p4parser.y"
                                    {}
#line 3755 "p4parser.tab.c"
    break;

  case 168:
#line 514 "p4parser.y"
                                      {}
#line 3761 "p4parser.tab.c"
    break;

  case 169:
#line 515 "p4parser.y"
                                      {}
#line 3767 "p4parser.tab.c"
    break;

  case 170:
#line 516 "p4parser.y"
                                      {}
#line 3773 "p4parser.tab.c"
    break;

  case 171:
#line 521 "p4parser.y"
                          {}
#line 3779 "p4parser.tab.c"
    break;

  case 172:
#line 522 "p4parser.y"
                          {}
#line 3785 "p4parser.tab.c"
    break;

  case 173:
#line 523 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3794 "p4parser.tab.c"
    break;

  case 174:
#line 530 "p4parser.y"
                                    {}
#line 3800 "p4parser.tab.c"
    break;

  case 175:
#line 531 "p4parser.y"
                                      {}
#line 3806 "p4parser.tab.c"
    break;

  case 176:
#line 535 "p4parser.y"
                              {}
#line 3812 "p4parser.tab.c"
    break;

  case 177:
#line 537 "p4parser.y"
                                      {}
#line 3818 "p4parser.tab.c"
    break;

  case 178:
#line 541 "p4parser.y"
                                     {}
#line 3824 "p4parser.tab.c"
    break;

  case 179:
#line 542 "p4parser.y"
                                       {}
#line 3830 "p4parser.tab.c"
    break;

  case 180:
#line 546 "p4parser.y"
                                    {}
#line 3836 "p4parser.tab.c"
    break;

  case 181:
#line 547 "p4parser.y"
                                      {}
#line 3842 "p4parser.tab.c"
    break;

  case 182:
#line 548 "p4parser.y"
                                      {}
#line 3848 "p4parser.tab.c"
    break;

  case 183:
#line 549 "p4parser.y"
                                      {}
#line 3854 "p4parser.tab.c"
    break;

  case 184:
#line 550 "p4parser.y"
                                      {}
#line 3860 "p4parser.tab.c"
    break;

  case 185:
#line 551 "p4parser.y"
                                      {}
#line 3866 "p4parser.tab.c"
    break;

  case 186:
#line 552 "p4parser.y"
                                      {}
#line 3872 "p4parser.tab.c"
    break;

  case 187:
#line 556 "p4parser.y"
                           {}
#line 3878 "p4parser.tab.c"
    break;

  case 188:
#line 557 "p4parser.y"
                               {}
#line 3884 "p4parser.tab.c"
    break;

  case 189:
#line 561 "p4parser.y"
                                {}
#line 3890 "p4parser.tab.c"
    break;

  case 190:
#line 562 "p4parser.y"
                                  {}
#line 3896 "p4parser.tab.c"
    break;

  case 191:
#line 566 "p4parser.y"
                           {}
#line 3902 "p4parser.tab.c"
    break;

  case 192:
#line 567 "p4parser.y"
                       {}
#line 3908 "p4parser.tab.c"
    break;

  case 193:
#line 572 "p4parser.y"
                              {}
#line 3914 "p4parser.tab.c"
    break;

  case 194:
#line 576 "p4parser.y"
                               {}
#line 3920 "p4parser.tab.c"
    break;

  case 195:
#line 577 "p4parser.y"
                                 {}
#line 3926 "p4parser.tab.c"
    break;

  case 196:
#line 582 "p4parser.y"
      {}
#line 3932 "p4parser.tab.c"
    break;

  case 197:
#line 586 "p4parser.y"
                              {}
#line 3938 "p4parser.tab.c"
    break;

  case 198:
#line 587 "p4parser.y"
                                {}
#line 3944 "p4parser.tab.c"
    break;

  case 199:
#line 592 "p4parser.y"
                                {}
#line 3950 "p4parser.tab.c"
    break;

  case 200:
#line 593 "p4parser.y"
                                                    {}
#line 3956 "p4parser.tab.c"
    break;

  case 201:
#line 597 "p4parser.y"
                           {}
#line 3962 "p4parser.tab.c"
    break;

  case 202:
#line 598 "p4parser.y"
                                                        {}
#line 3968 "p4parser.tab.c"
    break;

  case 203:
#line 603 "p4parser.y"
                                 {}
#line 3974 "p4parser.tab.c"
    break;

  case 204:
#line 604 "p4parser.y"
                                   {}
#line 3980 "p4parser.tab.c"
    break;

  case 205:
#line 605 "p4parser.y"
                                  {}
#line 3986 "p4parser.tab.c"
    break;

  case 206:
#line 606 "p4parser.y"
                                       {}
#line 3992 "p4parser.tab.c"
    break;

  case 207:
#line 610 "p4parser.y"
                                {}
#line 3998 "p4parser.tab.c"
    break;

  case 208:
#line 611 "p4parser.y"
                                 {}
#line 4004 "p4parser.tab.c"
    break;

  case 209:
#line 612 "p4parser.y"
                                   {}
#line 4010 "p4parser.tab.c"
    break;

  case 210:
#line 613 "p4parser.y"
                                  {}
#line 4016 "p4parser.tab.c"
    break;

  case 211:
#line 614 "p4parser.y"
                                       {}
#line 4022 "p4parser.tab.c"
    break;

  case 212:
#line 620 "p4parser.y"
        {}
#line 4028 "p4parser.tab.c"
    break;

  case 213:
#line 623 "p4parser.y"
        {}
#line 4034 "p4parser.tab.c"
    break;

  case 214:
#line 626 "p4parser.y"
        {}
#line 4040 "p4parser.tab.c"
    break;

  case 215:
#line 633 "p4parser.y"
              { EnterScope(subparser); }
#line 4046 "p4parser.tab.c"
    break;

  case 216:
#line 635 "p4parser.y"
      { ExitScope(subparser); }
#line 4052 "p4parser.tab.c"
    break;

  case 217:
#line 636 "p4parser.y"
        {}
#line 4058 "p4parser.tab.c"
    break;

  case 218:
#line 641 "p4parser.y"
                     {}
#line 4064 "p4parser.tab.c"
    break;

  case 219:
#line 642 "p4parser.y"
                          {}
#line 4070 "p4parser.tab.c"
    break;

  case 220:
#line 643 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4079 "p4parser.tab.c"
    break;

  case 221:
#line 650 "p4parser.y"
           {}
#line 4085 "p4parser.tab.c"
    break;

  case 222:
#line 651 "p4parser.y"
                                                       {}
#line 4091 "p4parser.tab.c"
    break;

  case 223:
#line 655 "p4parser.y"
                             {}
#line 4097 "p4parser.tab.c"
    break;

  case 224:
#line 656 "p4parser.y"
                               {}
#line 4103 "p4parser.tab.c"
    break;

  case 225:
#line 657 "p4parser.y"
                               {}
#line 4109 "p4parser.tab.c"
    break;

  case 226:
#line 658 "p4parser.y"
                               {}
#line 4115 "p4parser.tab.c"
    break;

  case 227:
#line 659 "p4parser.y"
                               {}
#line 4121 "p4parser.tab.c"
    break;

  case 228:
#line 663 "p4parser.y"
                   {}
#line 4127 "p4parser.tab.c"
    break;

  case 229:
#line 670 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4136 "p4parser.tab.c"
    break;

  case 230:
#line 674 "p4parser.y"
                          {}
#line 4142 "p4parser.tab.c"
    break;

  case 231:
#line 675 "p4parser.y"
                { ReenterScope(subparser); }
#line 4148 "p4parser.tab.c"
    break;

  case 232:
#line 675 "p4parser.y"
                                                              { ExitScope(subparser); }
#line 4154 "p4parser.tab.c"
    break;

  case 237:
#line 685 "p4parser.y"
                                     {}
#line 4160 "p4parser.tab.c"
    break;

  case 238:
#line 686 "p4parser.y"
                                       {}
#line 4166 "p4parser.tab.c"
    break;

  case 239:
#line 691 "p4parser.y"
                               {}
#line 4172 "p4parser.tab.c"
    break;

  case 240:
#line 692 "p4parser.y"
                                      {}
#line 4178 "p4parser.tab.c"
    break;

  case 241:
#line 696 "p4parser.y"
                                               {}
#line 4184 "p4parser.tab.c"
    break;

  case 242:
#line 697 "p4parser.y"
                                                          {}
#line 4190 "p4parser.tab.c"
    break;

  case 243:
#line 698 "p4parser.y"
                                 {}
#line 4196 "p4parser.tab.c"
    break;

  case 244:
#line 699 "p4parser.y"
                                        {}
#line 4202 "p4parser.tab.c"
    break;

  case 246:
#line 709 "p4parser.y"
                                     {}
#line 4208 "p4parser.tab.c"
    break;

  case 247:
#line 710 "p4parser.y"
                                       {}
#line 4214 "p4parser.tab.c"
    break;

  case 248:
#line 711 "p4parser.y"
                                       {}
#line 4220 "p4parser.tab.c"
    break;

  case 249:
#line 712 "p4parser.y"
                                       {}
#line 4226 "p4parser.tab.c"
    break;

  case 250:
#line 713 "p4parser.y"
                                       {}
#line 4232 "p4parser.tab.c"
    break;

  case 251:
#line 717 "p4parser.y"
                                     {}
#line 4238 "p4parser.tab.c"
    break;

  case 252:
#line 718 "p4parser.y"
                                       {}
#line 4244 "p4parser.tab.c"
    break;

  case 253:
#line 722 "p4parser.y"
                                     {}
#line 4250 "p4parser.tab.c"
    break;

  case 254:
#line 723 "p4parser.y"
                                       {}
#line 4256 "p4parser.tab.c"
    break;

  case 255:
#line 727 "p4parser.y"
                                     {}
#line 4262 "p4parser.tab.c"
    break;

  case 256:
#line 731 "p4parser.y"
                                              {}
#line 4268 "p4parser.tab.c"
    break;

  case 257:
#line 735 "p4parser.y"
                                                    {}
#line 4274 "p4parser.tab.c"
    break;

  case 258:
#line 736 "p4parser.y"
                                                      {}
#line 4280 "p4parser.tab.c"
    break;

  case 259:
#line 740 "p4parser.y"
                                              {}
#line 4286 "p4parser.tab.c"
    break;

  case 260:
#line 744 "p4parser.y"
           {}
#line 4292 "p4parser.tab.c"
    break;

  case 261:
#line 745 "p4parser.y"
             {}
#line 4298 "p4parser.tab.c"
    break;

  case 262:
#line 746 "p4parser.y"
             {}
#line 4304 "p4parser.tab.c"
    break;

  case 263:
#line 747 "p4parser.y"
             {}
#line 4310 "p4parser.tab.c"
    break;

  case 264:
#line 748 "p4parser.y"
             {}
#line 4316 "p4parser.tab.c"
    break;

  case 265:
#line 750 "p4parser.y"
      {}
#line 4322 "p4parser.tab.c"
    break;

  case 266:
#line 752 "p4parser.y"
      {}
#line 4328 "p4parser.tab.c"
    break;

  case 267:
#line 754 "p4parser.y"
      {}
#line 4334 "p4parser.tab.c"
    break;

  case 268:
#line 757 "p4parser.y"
      {}
#line 4340 "p4parser.tab.c"
    break;

  case 269:
#line 759 "p4parser.y"
      {}
#line 4346 "p4parser.tab.c"
    break;

  case 270:
#line 761 "p4parser.y"
      {}
#line 4352 "p4parser.tab.c"
    break;

  case 271:
#line 765 "p4parser.y"
                {}
#line 4358 "p4parser.tab.c"
    break;

  case 272:
#line 766 "p4parser.y"
                  {}
#line 4364 "p4parser.tab.c"
    break;

  case 273:
#line 767 "p4parser.y"
                  {}
#line 4370 "p4parser.tab.c"
    break;

  case 274:
#line 772 "p4parser.y"
                              {}
#line 4376 "p4parser.tab.c"
    break;

  case 275:
#line 773 "p4parser.y"
                                {}
#line 4382 "p4parser.tab.c"
    break;

  case 276:
#line 777 "p4parser.y"
            { EnterScope(subparser); }
#line 4388 "p4parser.tab.c"
    break;

  case 277:
#line 777 "p4parser.y"
                                                         { ExitReentrantScope(subparser); }
#line 4394 "p4parser.tab.c"
    break;

  case 278:
#line 777 "p4parser.y"
                                                                                                    {}
#line 4400 "p4parser.tab.c"
    break;

  case 279:
#line 781 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4412 "p4parser.tab.c"
    break;

  case 280:
#line 788 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4420 "p4parser.tab.c"
    break;

  case 281:
#line 794 "p4parser.y"
                                {}
#line 4426 "p4parser.tab.c"
    break;

  case 282:
#line 795 "p4parser.y"
                                  {}
#line 4432 "p4parser.tab.c"
    break;

  case 283:
#line 797 "p4parser.y"
                                  {}
#line 4438 "p4parser.tab.c"
    break;

  case 284:
#line 798 "p4parser.y"
                                       {}
#line 4444 "p4parser.tab.c"
    break;

  case 285:
#line 802 "p4parser.y"
                                   {}
#line 4450 "p4parser.tab.c"
    break;

  case 286:
#line 803 "p4parser.y"
                                     {}
#line 4456 "p4parser.tab.c"
    break;

  case 287:
#line 804 "p4parser.y"
                                       {}
#line 4462 "p4parser.tab.c"
    break;

  case 288:
#line 808 "p4parser.y"
                                {}
#line 4468 "p4parser.tab.c"
    break;

  case 289:
#line 809 "p4parser.y"
                                  {}
#line 4474 "p4parser.tab.c"
    break;

  case 290:
#line 810 "p4parser.y"
                                       {}
#line 4480 "p4parser.tab.c"
    break;

  case 291:
#line 816 "p4parser.y"
                                       {}
#line 4486 "p4parser.tab.c"
    break;

  case 292:
#line 817 "p4parser.y"
                                           {}
#line 4492 "p4parser.tab.c"
    break;

  case 293:
#line 821 "p4parser.y"
                               {}
#line 4498 "p4parser.tab.c"
    break;

  case 294:
#line 822 "p4parser.y"
                                       {}
#line 4504 "p4parser.tab.c"
    break;

  case 295:
#line 823 "p4parser.y"
                                       {}
#line 4510 "p4parser.tab.c"
    break;

  case 296:
#line 824 "p4parser.y"
                                       {}
#line 4516 "p4parser.tab.c"
    break;

  case 297:
#line 825 "p4parser.y"
                                       {}
#line 4522 "p4parser.tab.c"
    break;

  case 298:
#line 829 "p4parser.y"
                                     {}
#line 4528 "p4parser.tab.c"
    break;

  case 299:
#line 830 "p4parser.y"
                                       {}
#line 4534 "p4parser.tab.c"
    break;

  case 300:
#line 831 "p4parser.y"
                                       {}
#line 4540 "p4parser.tab.c"
    break;

  case 301:
#line 832 "p4parser.y"
                                       {}
#line 4546 "p4parser.tab.c"
    break;

  case 302:
#line 837 "p4parser.y"
              { ReenterScope(subparser); }
#line 4552 "p4parser.tab.c"
    break;

  case 303:
#line 838 "p4parser.y"
                      { ExitScope(subparser); }
#line 4558 "p4parser.tab.c"
    break;

  case 304:
#line 840 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4567 "p4parser.tab.c"
    break;

  case 305:
#line 848 "p4parser.y"
              { ReenterScope(subparser); }
#line 4573 "p4parser.tab.c"
    break;

  case 306:
#line 850 "p4parser.y"
      { ExitScope(subparser); }
#line 4579 "p4parser.tab.c"
    break;

  case 307:
#line 851 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4588 "p4parser.tab.c"
    break;

  case 308:
#line 859 "p4parser.y"
              { ReenterScope(subparser); }
#line 4594 "p4parser.tab.c"
    break;

  case 309:
#line 861 "p4parser.y"
      { ExitScope(subparser); }
#line 4600 "p4parser.tab.c"
    break;

  case 310:
#line 861 "p4parser.y"
                                        {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4609 "p4parser.tab.c"
    break;

  case 311:
#line 868 "p4parser.y"
                                     {}
#line 4615 "p4parser.tab.c"
    break;

  case 312:
#line 869 "p4parser.y"
                                       {}
#line 4621 "p4parser.tab.c"
    break;

  case 313:
#line 873 "p4parser.y"
                                           {}
#line 4627 "p4parser.tab.c"
    break;

  case 314:
#line 878 "p4parser.y"
                  {}
#line 4633 "p4parser.tab.c"
    break;

  case 315:
#line 879 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4642 "p4parser.tab.c"
    break;

  case 316:
#line 883 "p4parser.y"
                                       {}
#line 4648 "p4parser.tab.c"
    break;

  case 317:
#line 884 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4657 "p4parser.tab.c"
    break;

  case 318:
#line 891 "p4parser.y"
                            {}
#line 4663 "p4parser.tab.c"
    break;

  case 319:
#line 892 "p4parser.y"
                                                        {}
#line 4669 "p4parser.tab.c"
    break;

  case 320:
#line 896 "p4parser.y"
                               {}
#line 4675 "p4parser.tab.c"
    break;

  case 321:
#line 901 "p4parser.y"
        {}
#line 4681 "p4parser.tab.c"
    break;

  case 322:
#line 906 "p4parser.y"
        {}
#line 4687 "p4parser.tab.c"
    break;

  case 323:
#line 911 "p4parser.y"
                            {}
#line 4693 "p4parser.tab.c"
    break;

  case 324:
#line 912 "p4parser.y"
                                {}
#line 4699 "p4parser.tab.c"
    break;

  case 325:
#line 916 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4708 "p4parser.tab.c"
    break;

  case 326:
#line 920 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4717 "p4parser.tab.c"
    break;

  case 327:
#line 924 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4726 "p4parser.tab.c"
    break;

  case 328:
#line 928 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4735 "p4parser.tab.c"
    break;

  case 329:
#line 939 "p4parser.y"
        {}
#line 4741 "p4parser.tab.c"
    break;

  case 330:
#line 941 "p4parser.y"
        {}
#line 4747 "p4parser.tab.c"
    break;

  case 331:
#line 946 "p4parser.y"
        {}
#line 4753 "p4parser.tab.c"
    break;

  case 332:
#line 948 "p4parser.y"
        {}
#line 4759 "p4parser.tab.c"
    break;

  case 333:
#line 952 "p4parser.y"
                   {}
#line 4765 "p4parser.tab.c"
    break;

  case 334:
#line 956 "p4parser.y"
                   {}
#line 4771 "p4parser.tab.c"
    break;

  case 335:
#line 960 "p4parser.y"
                                {}
#line 4777 "p4parser.tab.c"
    break;

  case 336:
#line 961 "p4parser.y"
                                  {}
#line 4783 "p4parser.tab.c"
    break;

  case 337:
#line 966 "p4parser.y"
        {}
#line 4789 "p4parser.tab.c"
    break;

  case 338:
#line 968 "p4parser.y"
        {}
#line 4795 "p4parser.tab.c"
    break;

  case 339:
#line 973 "p4parser.y"
                                                              {}
#line 4801 "p4parser.tab.c"
    break;

  case 340:
#line 977 "p4parser.y"
                                     {}
#line 4807 "p4parser.tab.c"
    break;

  case 341:
#line 978 "p4parser.y"
                                       {}
#line 4813 "p4parser.tab.c"
    break;

  case 342:
#line 979 "p4parser.y"
                                       {}
#line 4819 "p4parser.tab.c"
    break;

  case 343:
#line 980 "p4parser.y"
                                       {}
#line 4825 "p4parser.tab.c"
    break;

  case 344:
#line 981 "p4parser.y"
                                       {}
#line 4831 "p4parser.tab.c"
    break;

  case 345:
#line 982 "p4parser.y"
                                       {}
#line 4837 "p4parser.tab.c"
    break;

  case 346:
#line 983 "p4parser.y"
                                       {}
#line 4843 "p4parser.tab.c"
    break;

  case 347:
#line 984 "p4parser.y"
                                       {}
#line 4849 "p4parser.tab.c"
    break;

  case 348:
#line 988 "p4parser.y"
                           {}
#line 4855 "p4parser.tab.c"
    break;

  case 349:
#line 989 "p4parser.y"
                             {}
#line 4861 "p4parser.tab.c"
    break;

  case 350:
#line 993 "p4parser.y"
                                          {}
#line 4867 "p4parser.tab.c"
    break;

  case 351:
#line 994 "p4parser.y"
                                            {}
#line 4873 "p4parser.tab.c"
    break;

  case 352:
#line 998 "p4parser.y"
                                                                  {}
#line 4879 "p4parser.tab.c"
    break;

  case 353:
#line 1002 "p4parser.y"
                             {}
#line 4885 "p4parser.tab.c"
    break;

  case 354:
#line 1003 "p4parser.y"
                               {}
#line 4891 "p4parser.tab.c"
    break;

  case 355:
#line 1007 "p4parser.y"
                                     {}
#line 4897 "p4parser.tab.c"
    break;

  case 356:
#line 1008 "p4parser.y"
                                       {}
#line 4903 "p4parser.tab.c"
    break;

  case 357:
#line 1012 "p4parser.y"
                             {}
#line 4909 "p4parser.tab.c"
    break;

  case 358:
#line 1013 "p4parser.y"
                               {}
#line 4915 "p4parser.tab.c"
    break;

  case 359:
#line 1017 "p4parser.y"
                             {}
#line 4921 "p4parser.tab.c"
    break;

  case 360:
#line 1018 "p4parser.y"
                               {}
#line 4927 "p4parser.tab.c"
    break;

  case 361:
#line 1019 "p4parser.y"
                               {}
#line 4933 "p4parser.tab.c"
    break;

  case 362:
#line 1020 "p4parser.y"
                               {}
#line 4939 "p4parser.tab.c"
    break;

  case 363:
#line 1027 "p4parser.y"
                           { EnterScope(subparser); }
#line 4945 "p4parser.tab.c"
    break;

  case 364:
#line 1027 "p4parser.y"
                                                                        { ExitScope(subparser); }
#line 4951 "p4parser.tab.c"
    break;

  case 365:
#line 1028 "p4parser.y"
          {}
#line 4957 "p4parser.tab.c"
    break;

  case 366:
#line 1032 "p4parser.y"
                                       {}
#line 4963 "p4parser.tab.c"
    break;

  case 367:
#line 1033 "p4parser.y"
                                         {}
#line 4969 "p4parser.tab.c"
    break;

  case 368:
#line 1038 "p4parser.y"
        {}
#line 4975 "p4parser.tab.c"
    break;

  case 369:
#line 1040 "p4parser.y"
        {}
#line 4981 "p4parser.tab.c"
    break;

  case 370:
#line 1042 "p4parser.y"
        {}
#line 4987 "p4parser.tab.c"
    break;

  case 371:
#line 1044 "p4parser.y"
        {}
#line 4993 "p4parser.tab.c"
    break;

  case 372:
#line 1048 "p4parser.y"
                                       {}
#line 4999 "p4parser.tab.c"
    break;

  case 373:
#line 1049 "p4parser.y"
                                         {}
#line 5005 "p4parser.tab.c"
    break;

  case 374:
#line 1054 "p4parser.y"
                                         {}
#line 5011 "p4parser.tab.c"
    break;

  case 375:
#line 1058 "p4parser.y"
           {}
#line 5017 "p4parser.tab.c"
    break;

  case 376:
#line 1060 "p4parser.y"
        {}
#line 5023 "p4parser.tab.c"
    break;

  case 378:
#line 1069 "p4parser.y"
        {}
#line 5029 "p4parser.tab.c"
    break;

  case 379:
#line 1071 "p4parser.y"
        {}
#line 5035 "p4parser.tab.c"
    break;

  case 380:
#line 1076 "p4parser.y"
        {}
#line 5041 "p4parser.tab.c"
    break;

  case 381:
#line 1080 "p4parser.y"
                                   {}
#line 5047 "p4parser.tab.c"
    break;

  case 382:
#line 1081 "p4parser.y"
                                     {}
#line 5053 "p4parser.tab.c"
    break;

  case 383:
#line 1087 "p4parser.y"
                                                             { EnterScope(subparser); }
#line 5059 "p4parser.tab.c"
    break;

  case 384:
#line 1087 "p4parser.y"
                                                                                                       {
        saveBaseType(subparser, getNodeAt(subparser, 7));
        bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 6));
        ExitScope(subparser);
      }
#line 5069 "p4parser.tab.c"
    break;

  case 385:
#line 1097 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5078 "p4parser.tab.c"
    break;

  case 386:
#line 1101 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 5087 "p4parser.tab.c"
    break;

  case 387:
#line 1109 "p4parser.y"
                                     {}
#line 5093 "p4parser.tab.c"
    break;

  case 388:
#line 1113 "p4parser.y"
                                     {}
#line 5099 "p4parser.tab.c"
    break;

  case 389:
#line 1114 "p4parser.y"
                                          {}
#line 5105 "p4parser.tab.c"
    break;

  case 390:
#line 1118 "p4parser.y"
                                        {}
#line 5111 "p4parser.tab.c"
    break;

  case 391:
#line 1124 "p4parser.y"
                      { ReenterScope(subparser); }
#line 5117 "p4parser.tab.c"
    break;

  case 392:
#line 1124 "p4parser.y"
                                                                  { ExitScope(subparser); }
#line 5123 "p4parser.tab.c"
    break;

  case 393:
#line 1128 "p4parser.y"
                                       {}
#line 5129 "p4parser.tab.c"
    break;

  case 394:
#line 1129 "p4parser.y"
                                         {}
#line 5135 "p4parser.tab.c"
    break;

  case 395:
#line 1133 "p4parser.y"
                                       {}
#line 5141 "p4parser.tab.c"
    break;

  case 396:
#line 1134 "p4parser.y"
                                           {}
#line 5147 "p4parser.tab.c"
    break;

  case 397:
#line 1138 "p4parser.y"
                                       {}
#line 5153 "p4parser.tab.c"
    break;

  case 398:
#line 1139 "p4parser.y"
                                            {}
#line 5159 "p4parser.tab.c"
    break;

  case 399:
#line 1140 "p4parser.y"
                                              {}
#line 5165 "p4parser.tab.c"
    break;

  case 400:
#line 1144 "p4parser.y"
                                       {}
#line 5171 "p4parser.tab.c"
    break;

  case 401:
#line 1145 "p4parser.y"
                                         {}
#line 5177 "p4parser.tab.c"
    break;

  case 402:
#line 1146 "p4parser.y"
                                           {}
#line 5183 "p4parser.tab.c"
    break;

  case 403:
#line 1150 "p4parser.y"
                                       {}
#line 5189 "p4parser.tab.c"
    break;

  case 404:
#line 1151 "p4parser.y"
                                         {}
#line 5195 "p4parser.tab.c"
    break;

  case 405:
#line 1155 "p4parser.y"
        {}
#line 5201 "p4parser.tab.c"
    break;

  case 406:
#line 1155 "p4parser.y"
                {}
#line 5207 "p4parser.tab.c"
    break;

  case 407:
#line 1159 "p4parser.y"
                                       {}
#line 5213 "p4parser.tab.c"
    break;

  case 408:
#line 1160 "p4parser.y"
                                         {}
#line 5219 "p4parser.tab.c"
    break;

  case 409:
#line 1161 "p4parser.y"
                                         {}
#line 5225 "p4parser.tab.c"
    break;

  case 410:
#line 1162 "p4parser.y"
                                       {}
#line 5231 "p4parser.tab.c"
    break;

  case 411:
#line 1166 "p4parser.y"
                                            {}
#line 5237 "p4parser.tab.c"
    break;

  case 412:
#line 1167 "p4parser.y"
                                                      {}
#line 5243 "p4parser.tab.c"
    break;

  case 413:
#line 1170 "p4parser.y"
                                       {}
#line 5249 "p4parser.tab.c"
    break;

  case 414:
#line 1171 "p4parser.y"
                                         {}
#line 5255 "p4parser.tab.c"
    break;

  case 415:
#line 1172 "p4parser.y"
                                         {}
#line 5261 "p4parser.tab.c"
    break;

  case 416:
#line 1173 "p4parser.y"
                                         {}
#line 5267 "p4parser.tab.c"
    break;

  case 417:
#line 1174 "p4parser.y"
                                         {}
#line 5273 "p4parser.tab.c"
    break;

  case 418:
#line 1175 "p4parser.y"
                                         {}
#line 5279 "p4parser.tab.c"
    break;

  case 419:
#line 1176 "p4parser.y"
                                         {}
#line 5285 "p4parser.tab.c"
    break;

  case 420:
#line 1177 "p4parser.y"
                                                     {}
#line 5291 "p4parser.tab.c"
    break;

  case 421:
#line 1178 "p4parser.y"
                                                                 {}
#line 5297 "p4parser.tab.c"
    break;

  case 422:
#line 1179 "p4parser.y"
                                                 {}
#line 5303 "p4parser.tab.c"
    break;

  case 423:
#line 1180 "p4parser.y"
                                                 {}
#line 5309 "p4parser.tab.c"
    break;

  case 424:
#line 1181 "p4parser.y"
                                                 {}
#line 5315 "p4parser.tab.c"
    break;

  case 425:
#line 1182 "p4parser.y"
                                         {}
#line 5321 "p4parser.tab.c"
    break;

  case 426:
#line 1183 "p4parser.y"
                                                {}
#line 5327 "p4parser.tab.c"
    break;

  case 427:
#line 1184 "p4parser.y"
                                           {}
#line 5333 "p4parser.tab.c"
    break;

  case 428:
#line 1185 "p4parser.y"
                                          {}
#line 5339 "p4parser.tab.c"
    break;

  case 429:
#line 1187 "p4parser.y"
        {}
#line 5345 "p4parser.tab.c"
    break;

  case 430:
#line 1189 "p4parser.y"
        {}
#line 5351 "p4parser.tab.c"
    break;

  case 431:
#line 1190 "p4parser.y"
                                         {}
#line 5357 "p4parser.tab.c"
    break;

  case 432:
#line 1191 "p4parser.y"
                                         {}
#line 5363 "p4parser.tab.c"
    break;

  case 433:
#line 1192 "p4parser.y"
                                         {}
#line 5369 "p4parser.tab.c"
    break;

  case 434:
#line 1193 "p4parser.y"
                                         {}
#line 5375 "p4parser.tab.c"
    break;

  case 435:
#line 1194 "p4parser.y"
                                          {}
#line 5381 "p4parser.tab.c"
    break;

  case 436:
#line 1195 "p4parser.y"
                                           {}
#line 5387 "p4parser.tab.c"
    break;

  case 437:
#line 1196 "p4parser.y"
                                            {}
#line 5393 "p4parser.tab.c"
    break;

  case 438:
#line 1197 "p4parser.y"
                                             {}
#line 5399 "p4parser.tab.c"
    break;

  case 439:
#line 1198 "p4parser.y"
                                        {}
#line 5405 "p4parser.tab.c"
    break;

  case 440:
#line 1200 "p4parser.y"
        {}
#line 5411 "p4parser.tab.c"
    break;

  case 441:
#line 1201 "p4parser.y"
                                       {}
#line 5417 "p4parser.tab.c"
    break;

  case 442:
#line 1202 "p4parser.y"
                                       {}
#line 5423 "p4parser.tab.c"
    break;

  case 443:
#line 1204 "p4parser.y"
                                         {}
#line 5429 "p4parser.tab.c"
    break;

  case 444:
#line 1205 "p4parser.y"
                                             {}
#line 5435 "p4parser.tab.c"
    break;

  case 445:
#line 1207 "p4parser.y"
                                       {}
#line 5441 "p4parser.tab.c"
    break;

  case 446:
#line 1208 "p4parser.y"
                                       {}
#line 5447 "p4parser.tab.c"
    break;

  case 447:
#line 1209 "p4parser.y"
                                             {}
#line 5453 "p4parser.tab.c"
    break;

  case 448:
#line 1210 "p4parser.y"
                                             {}
#line 5459 "p4parser.tab.c"
    break;

  case 449:
#line 1211 "p4parser.y"
                                            {}
#line 5465 "p4parser.tab.c"
    break;

  case 450:
#line 1212 "p4parser.y"
                                       {}
#line 5471 "p4parser.tab.c"
    break;

  case 451:
#line 1213 "p4parser.y"
                                        {}
#line 5477 "p4parser.tab.c"
    break;

  case 452:
#line 1214 "p4parser.y"
                                       {}
#line 5483 "p4parser.tab.c"
    break;

  case 453:
#line 1215 "p4parser.y"
                                                      {}
#line 5489 "p4parser.tab.c"
    break;

  case 454:
#line 1216 "p4parser.y"
                         {}
#line 5495 "p4parser.tab.c"
    break;

  case 456:
#line 1220 "p4parser.y"
        {}
#line 5501 "p4parser.tab.c"
    break;

  case 457:
#line 1222 "p4parser.y"
        {}
#line 5507 "p4parser.tab.c"
    break;

  case 458:
#line 1224 "p4parser.y"
        {}
#line 5513 "p4parser.tab.c"
    break;

  case 459:
#line 1225 "p4parser.y"
                                                      {}
#line 5519 "p4parser.tab.c"
    break;

  case 460:
#line 1229 "p4parser.y"
                                       {}
#line 5525 "p4parser.tab.c"
    break;

  case 461:
#line 1230 "p4parser.y"
                                         {}
#line 5531 "p4parser.tab.c"
    break;

  case 462:
#line 1231 "p4parser.y"
                                         {}
#line 5537 "p4parser.tab.c"
    break;

  case 463:
#line 1232 "p4parser.y"
                                         {}
#line 5543 "p4parser.tab.c"
    break;

  case 464:
#line 1233 "p4parser.y"
                                         {}
#line 5549 "p4parser.tab.c"
    break;

  case 465:
#line 1234 "p4parser.y"
                                         {}
#line 5555 "p4parser.tab.c"
    break;

  case 466:
#line 1235 "p4parser.y"
                                         {}
#line 5561 "p4parser.tab.c"
    break;

  case 467:
#line 1236 "p4parser.y"
                                                             {}
#line 5567 "p4parser.tab.c"
    break;

  case 468:
#line 1237 "p4parser.y"
                                                                         {}
#line 5573 "p4parser.tab.c"
    break;

  case 469:
#line 1238 "p4parser.y"
                                                 {}
#line 5579 "p4parser.tab.c"
    break;

  case 470:
#line 1239 "p4parser.y"
                                         {}
#line 5585 "p4parser.tab.c"
    break;

  case 471:
#line 1240 "p4parser.y"
                                                {}
#line 5591 "p4parser.tab.c"
    break;

  case 472:
#line 1241 "p4parser.y"
                                           {}
#line 5597 "p4parser.tab.c"
    break;

  case 473:
#line 1242 "p4parser.y"
                                          {}
#line 5603 "p4parser.tab.c"
    break;

  case 474:
#line 1244 "p4parser.y"
        {}
#line 5609 "p4parser.tab.c"
    break;

  case 475:
#line 1246 "p4parser.y"
        {}
#line 5615 "p4parser.tab.c"
    break;

  case 476:
#line 1247 "p4parser.y"
                                                 {}
#line 5621 "p4parser.tab.c"
    break;

  case 477:
#line 1248 "p4parser.y"
                                                 {}
#line 5627 "p4parser.tab.c"
    break;

  case 478:
#line 1249 "p4parser.y"
                                                 {}
#line 5633 "p4parser.tab.c"
    break;

  case 479:
#line 1250 "p4parser.y"
                                                 {}
#line 5639 "p4parser.tab.c"
    break;

  case 480:
#line 1251 "p4parser.y"
                                                  {}
#line 5645 "p4parser.tab.c"
    break;

  case 481:
#line 1252 "p4parser.y"
                                                   {}
#line 5651 "p4parser.tab.c"
    break;

  case 482:
#line 1253 "p4parser.y"
                                                    {}
#line 5657 "p4parser.tab.c"
    break;

  case 483:
#line 1254 "p4parser.y"
                                                     {}
#line 5663 "p4parser.tab.c"
    break;

  case 484:
#line 1255 "p4parser.y"
                                                {}
#line 5669 "p4parser.tab.c"
    break;

  case 485:
#line 1257 "p4parser.y"
        {}
#line 5675 "p4parser.tab.c"
    break;

  case 486:
#line 1258 "p4parser.y"
                                               {}
#line 5681 "p4parser.tab.c"
    break;

  case 487:
#line 1259 "p4parser.y"
                                               {}
#line 5687 "p4parser.tab.c"
    break;

  case 488:
#line 1261 "p4parser.y"
                                         {}
#line 5693 "p4parser.tab.c"
    break;

  case 489:
#line 1262 "p4parser.y"
                                                     {}
#line 5699 "p4parser.tab.c"
    break;

  case 490:
#line 1263 "p4parser.y"
                                               {}
#line 5705 "p4parser.tab.c"
    break;

  case 491:
#line 1264 "p4parser.y"
                                               {}
#line 5711 "p4parser.tab.c"
    break;

  case 492:
#line 1265 "p4parser.y"
                                                     {}
#line 5717 "p4parser.tab.c"
    break;

  case 493:
#line 1266 "p4parser.y"
                                                     {}
#line 5723 "p4parser.tab.c"
    break;

  case 494:
#line 1267 "p4parser.y"
                                                    {}
#line 5729 "p4parser.tab.c"
    break;

  case 495:
#line 1268 "p4parser.y"
                                               {}
#line 5735 "p4parser.tab.c"
    break;

  case 496:
#line 1269 "p4parser.y"
                                                {}
#line 5741 "p4parser.tab.c"
    break;

  case 497:
#line 1270 "p4parser.y"
                                               {}
#line 5747 "p4parser.tab.c"
    break;

  case 498:
#line 1271 "p4parser.y"
                                                              {}
#line 5753 "p4parser.tab.c"
    break;

  case 499:
#line 1272 "p4parser.y"
                                 {}
#line 5759 "p4parser.tab.c"
    break;

  case 501:
#line 1276 "p4parser.y"
        {}
#line 5765 "p4parser.tab.c"
    break;

  case 502:
#line 1278 "p4parser.y"
        {}
#line 5771 "p4parser.tab.c"
    break;

  case 503:
#line 1280 "p4parser.y"
        {}
#line 5777 "p4parser.tab.c"
    break;

  case 504:
#line 1281 "p4parser.y"
                                                      {}
#line 5783 "p4parser.tab.c"
    break;


#line 5787 "p4parser.tab.c"

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
#line 1309 "p4parser.y"


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
