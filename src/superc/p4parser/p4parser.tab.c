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
#define YYLAST   3924

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  156
/* YYNRULES -- Number of rules.  */
#define YYNRULES  489
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  877

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
     441,   442,   443,   444,   448,   449,   448,   457,   459,   461,
     464,   466,   469,   475,   480,   481,   485,   486,   490,   491,
     495,   501,   502,   501,   508,   509,   513,   514,   515,   516,
     521,   522,   520,   530,   531,   535,   535,   541,   542,   546,
     547,   548,   549,   550,   551,   552,   556,   556,   561,   562,
     566,   567,   571,   576,   577,   581,   586,   587,   591,   593,
     597,   598,   603,   604,   605,   606,   610,   611,   612,   613,
     614,   618,   621,   624,   632,   639,   640,   638,   648,   649,
     653,   654,   655,   656,   657,   661,   668,   672,   667,   674,
     675,   679,   683,   684,   689,   688,   694,   695,   696,   696,
     701,   707,   708,   709,   710,   711,   715,   716,   720,   721,
     725,   729,   733,   734,   738,   742,   743,   744,   745,   746,
     747,   749,   751,   754,   756,   758,   763,   764,   765,   770,
     771,   775,   779,   786,   792,   793,   795,   796,   800,   801,
     802,   806,   807,   808,   814,   815,   819,   820,   821,   822,
     823,   827,   828,   829,   830,   834,   834,   834,   843,   852,
     852,   852,   860,   861,   865,   870,   869,   875,   875,   883,
     884,   888,   892,   897,   903,   904,   908,   912,   916,   920,
     930,   932,   937,   939,   944,   948,   952,   953,   957,   959,
     965,   969,   970,   971,   972,   973,   974,   975,   976,   980,
     980,   985,   986,   990,   994,   995,   999,  1000,  1004,  1005,
    1009,  1010,  1011,  1012,  1018,  1024,  1025,  1029,  1031,  1033,
    1035,  1040,  1041,  1045,  1050,  1051,  1056,  1060,  1062,  1067,
    1072,  1073,  1079,  1088,  1092,  1099,  1104,  1105,  1109,  1115,
    1119,  1120,  1124,  1125,  1129,  1130,  1131,  1135,  1136,  1137,
    1141,  1142,  1146,  1146,  1150,  1151,  1152,  1153,  1157,  1158,
    1161,  1162,  1163,  1164,  1165,  1166,  1167,  1168,  1169,  1170,
    1171,  1172,  1173,  1174,  1175,  1176,  1177,  1179,  1181,  1182,
    1183,  1184,  1185,  1186,  1187,  1188,  1189,  1190,  1192,  1193,
    1194,  1196,  1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,
    1206,  1207,  1209,  1210,  1212,  1214,  1216,  1220,  1221,  1222,
    1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,  1231,  1232,
    1233,  1234,  1236,  1238,  1239,  1240,  1241,  1242,  1243,  1244,
    1245,  1246,  1247,  1249,  1250,  1251,  1253,  1254,  1255,  1256,
    1257,  1258,  1259,  1260,  1261,  1262,  1294,  1294,  1295,  1295
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
  "instantiationWithAssignment", "objInitializer", "objDeclarations",
  "objDeclaration", "optConstructorParameters", "dotPrefix",
  "parserDeclaration", "$@3", "$@4", "parserLocalElements",
  "parserLocalElement", "parserTypeDeclaration", "$@5", "$@6",
  "parserStates", "parserState", "$@7", "parserStatements",
  "parserStatement", "parserBlockStatement", "$@8", "transitionStatement",
  "stateExpression", "selectExpression", "selectCaseList", "selectCase",
  "keysetExpression", "tupleKeysetExpression", "simpleExpressionList",
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

#define YYPACT_NINF (-772)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-388)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -772,    44,  -772,   846,  -772,  -772,  -772,   142,  -772,   271,
      13,   271,    26,  -772,   271,   271,  -772,  -772,  -772,  -772,
     717,  1517,  -772,    41,  -772,  -772,    37,  -772,   165,  -772,
     187,  -772,  -772,    76,   115,  -772,   309,  -772,  -772,   111,
    -772,   142,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
     109,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,   226,  -772,  -772,   -33,   142,   -29,   142,
    1477,   -25,   142,   502,   142,  2453,  2410,   142,   142,  1517,
     142,   142,   142,  1517,  -772,  -772,   129,  -772,  -772,   232,
    -772,  -772,  -772,   150,   176,    76,  -772,  1375,  2224,  1477,
    2224,   271,  -772,  1777,  -772,  2224,   313,  -772,    -8,  2224,
     313,   105,  -772,  -772,  -772,  -772,  -772,   254,  2224,   313,
     175,   142,  -772,    -6,  -772,   142,   114,   164,   180,   183,
    -772,  -772,  -772,    86,   142,   142,  -772,  -772,   271,   142,
     142,  1375,   124,   229,   198,  -772,   255,  -772,  -772,  2224,
    2224,  2224,  1826,  1165,  2224,  -772,  -772,  -772,  -772,   239,
    -772,  -772,   257,   264,   529,   275,   158,  -772,   288,   274,
    -772,  3592,  -772,  -772,  2778,   254,  2815,  -772,  -772,   142,
     285,   302,   296,  -772,   298,  3592,  1604,  2852,  -772,  -772,
    -772,  -772,   142,  2889,  -772,  -772,  1477,  -772,  2926,  -772,
     232,   306,   271,   322,  -772,   271,  -772,  -772,   271,   271,
    -772,  -772,   271,   271,   326,  -772,  -772,   324,  -772,  -772,
    -772,   502,  -772,    76,  -772,   860,  -772,   107,   107,   107,
     172,   208,   239,   328,    77,   251,  2963,   107,   142,  2224,
    -772,  1375,  -772,  -772,   142,  2028,  2224,  2224,  2224,  2224,
    2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,
    2224,  2224,  2224,  2224,  2224,   335,  1375,  2224,  2224,  -772,
     999,  -772,  -772,  -772,   334,  -772,   281,  2224,  -772,   142,
    2224,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
     313,  -772,   313,  -772,   313,   336,  2224,  -772,   142,   341,
    -772,  -772,  -772,  -772,  -772,  -772,   142,   142,  -772,  1517,
      76,   -20,  1517,  -772,  -772,   197,  -772,  -772,  -772,  -772,
    2271,  -772,  -772,  2224,  -772,  -772,  3592,   337,   142,   310,
    -772,  3800,  3800,  1246,  3736,  3703,  3769,  3769,   171,   171,
     171,   171,   107,   107,   107,  3831,  1445,  3862,  2667,  3800,
    2224,   338,  3000,   171,  -772,  -772,  -772,  -772,   300,  3800,
     232,   142,  -772,  3592,  -772,  3592,  1696,  -772,  -772,  -772,
      76,   332,  3592,   343,   227,   142,   350,   353,   354,   352,
     355,   -19,   316,   366,   -50,  -772,  -772,   -15,  -772,  -772,
    -772,  -772,   362,  -772,   142,   351,   367,  -772,  -772,  -772,
     371,   358,  2077,   359,  -772,    10,  -772,   529,   202,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,    50,   107,  -772,  -772,   368,  -772,  -772,
    2224,  1246,  -772,  2224,  1477,   360,   374,  -772,  -772,  -772,
    -772,   232,  -772,   376,   242,  -772,  -772,  -772,  -772,   232,
     232,  -772,   502,  -772,   368,  -772,  2224,   142,   271,   314,
     386,  -772,  -772,   391,   367,  2224,   378,  -772,  2224,  -772,
    3037,  2224,  -772,   370,  2224,  1375,  2224,  -772,  -772,  1477,
    -772,   379,  3074,  3629,  -772,  1375,  -772,   392,  2224,  -772,
     142,    -9,    46,    56,   394,   396,   142,   393,  3592,  -772,
     502,  -772,   -26,   395,  -772,  -772,  3111,  -772,  3148,   399,
    2704,   401,  3185,   254,   725,  -772,  -772,   403,  -772,  -772,
    -772,  -772,    31,  -772,  -772,  -772,  -772,  -772,  -772,   397,
    -772,   406,   313,   313,   313,   407,   411,   385,   -14,  -772,
    -772,  2501,   419,  1375,  -772,  2224,   412,  -772,   421,  -772,
    1517,  -772,  -772,  -772,  -772,  2497,   422,   416,  -772,  -772,
    -772,   425,   426,   429,   437,   441,  -772,   201,  -772,  -772,
     413,   415,  -772,   438,  3222,  -772,  1375,   434,   232,  -772,
    2319,  2224,  2224,  2224,  -772,  -772,  -772,   440,  -772,  -772,
    -772,  -772,   443,  2501,  2126,   436,  -772,   444,  -772,   452,
     657,    20,  1517,  -772,  -772,   459,   142,  -772,  -772,  -772,
    -772,  -772,  -772,  3259,  3296,  3333,    97,  2175,   462,  2224,
    -772,  2224,  2224,  2224,  -772,  2224,  2224,  -772,  -772,  -772,
    -772,   454,  -772,  -772,  -772,   529,   455,  -772,   461,  3666,
    -772,   463,   464,   465,   466,  -772,  -772,  -772,   142,  -772,
     142,   142,   142,  -772,   457,  -772,  -772,  -772,  3370,  1877,
     467,   107,   107,   107,  3407,   107,   142,  -772,  -772,   -10,
    2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,
    2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,  2224,   472,
    2224,  2224,  -772,  2224,  -772,  -772,  1926,  -772,  -772,   474,
     475,   478,   250,   479,   473,   142,  1082,  -772,  -772,   485,
    -772,  -772,  -772,  1253,  2627,  -772,  -772,  -772,  -772,  3800,
    3800,  1246,  3736,  3703,  3769,  3769,   171,   171,   171,   171,
     107,   107,   107,  3831,  1445,  3862,  2741,  3800,  2224,  3444,
     171,  3800,   253,  2367,  -772,  -772,  -772,  -772,  1375,    76,
     458,   486,   488,   487,  2587,   457,  -772,  -772,  2224,  2224,
    -772,  2224,  1246,  2224,   498,  -772,   492,   489,  -772,  1977,
    2224,  2224,    76,  3592,  3592,  3481,  3629,  -772,  -772,  -772,
     261,  -772,  3518,  3555,   491,  -772,  1304,  -772,  1977,  -772,
    -772,  -772,   500,  -772,   142,   493,  -772
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       4,     0,     2,    33,     1,   160,     6,     0,   255,   257,
     256,   259,     0,   258,     0,     0,   267,   268,   248,     5,
       0,    34,    35,     0,    13,   149,     0,    10,   158,    12,
     158,     8,   229,    33,   266,   250,   242,   245,   244,   243,
     241,     0,    11,   286,   291,   293,   292,   294,    14,    15,
       0,     9,     7,    16,    20,    18,    22,    19,    23,    21,
      17,    25,    24,    37,   486,   487,     0,     0,     0,     0,
     278,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,    33,   256,    36,     0,   290,   249,    33,
     288,   161,   289,     0,     0,    34,   379,   442,   442,   278,
     442,   269,   287,   442,    42,   442,     0,   314,     0,   442,
       0,     0,   277,   276,   275,   274,   279,     0,   442,     0,
       0,     0,   215,   248,   305,     0,   268,   226,     0,     0,
     266,   295,   299,     0,     0,     0,   144,   170,   269,     0,
       0,   442,   143,     0,   135,   136,     0,   218,   339,   442,
     442,   442,   442,   442,   442,   386,   402,   403,   404,     0,
     401,   400,   405,     0,     0,     0,   246,   247,     0,   381,
     382,   384,   441,   405,     0,     0,     0,   234,   270,     0,
       0,     0,    41,   131,    40,   388,     0,     0,   488,   489,
     260,   312,     0,     0,   261,   313,     0,   251,     0,   262,
      33,     0,   269,     0,   307,   269,   230,   231,   269,   269,
     318,   319,   269,   269,     0,   316,   317,     0,   140,   142,
     141,     0,   159,    33,   164,    33,   341,   415,   414,   413,
       0,     0,   256,     0,   242,   243,     0,   412,     0,   442,
     406,   442,   392,   416,     0,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,     0,   442,   442,   442,   418,
     442,   252,   254,   253,     0,   272,     0,   442,    39,     0,
     442,    45,   104,   103,    99,   100,   102,   101,   106,   108,
     107,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,    95,   122,    96,    42,    38,   123,
     124,   130,   125,   126,   127,   128,   129,   105,    90,    98,
      97,    84,    61,    82,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    62,
      63,    64,    65,    66,    67,    68,    76,    69,    70,    71,
      73,    72,    74,    75,    77,    78,    79,    80,    81,    83,
      85,    86,    87,    88,    89,    91,    92,    93,    94,    44,
       0,   315,     0,   280,     0,     0,   442,   216,     0,     0,
     227,   296,   300,   145,   171,   302,     0,     0,   137,    33,
      33,     0,    34,   223,   219,     0,   222,   221,   224,   220,
      33,   410,   409,   442,   411,   417,   385,     0,     0,     0,
     383,   428,   429,   426,   438,   439,   432,   433,   422,   423,
     424,   425,   419,   420,   421,   436,   434,   435,     0,   431,
     442,     0,     0,   437,   283,   282,   281,   284,     0,   430,
      33,     0,   271,   133,   132,   389,     0,   263,   264,   265,
      33,     0,   378,     0,     0,     0,     0,     0,     0,     0,
       0,    33,     0,   138,     0,   167,   165,    33,   173,   169,
     168,   166,     0,   225,     0,     0,   376,   340,   324,   395,
       0,     0,   442,     0,   390,     0,   353,     0,   242,   331,
     320,   334,   337,   336,   333,   332,   352,   335,   338,   342,
     350,   351,   394,     0,   446,   445,   393,     0,   148,   407,
     442,   427,   444,   442,     0,     0,     0,   273,    43,   372,
     375,    33,   306,     0,     0,   309,   232,   302,   302,    33,
      33,   298,     0,   303,     0,   147,   442,     0,     0,     0,
       0,   174,   214,     0,   376,   442,     0,   325,   442,   326,
       0,   442,   391,     0,   442,   442,   442,   396,   397,   278,
     154,     0,     0,   440,   285,   442,   235,     0,   442,   308,
       0,    33,    33,    33,     0,     0,     0,     0,   139,   175,
       0,   163,    33,     0,   377,   374,     0,   327,     0,     0,
       0,     0,     0,     0,     0,   152,   408,     0,   217,   311,
     310,   228,     0,   233,   238,   297,   301,   146,   172,     0,
     151,     0,     0,     0,     0,     0,     0,    31,    33,   355,
     373,    33,     0,   442,   398,   442,     0,   321,     0,   153,
       0,   157,   155,   156,   443,     0,   248,     0,   239,   304,
     177,     0,     0,     0,     0,     0,    32,     0,   354,   356,
       0,   328,   344,     0,     0,   322,   442,     0,    33,   236,
      33,   442,   442,   442,   364,   361,    28,     0,    30,    29,
      26,    27,     0,    33,     0,     0,   399,     0,   237,     0,
       0,     0,    34,   178,   184,     0,     0,   179,   181,   185,
     180,   182,   183,     0,     0,     0,    33,   442,     0,   442,
     329,   442,   442,   442,   343,   442,   442,   449,   450,   451,
     348,     0,   448,   447,   452,     0,     0,   345,     0,   349,
     330,     0,     0,     0,     0,   189,   191,   186,     0,   176,
       0,     0,     0,   358,     0,   365,   357,   362,     0,   442,
       0,   460,   459,   458,     0,   457,     0,   453,   461,   347,
     442,   442,   442,   442,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   442,   442,   442,   442,     0,
     442,   442,   463,   442,   323,   240,   442,   190,   177,     0,
       0,     0,     0,     0,   367,     0,   442,   210,   209,     0,
     196,   197,   370,   442,   206,   360,   456,   462,   346,   473,
     474,   471,   483,   484,   477,   478,   467,   468,   469,   470,
     464,   465,   466,   481,   479,   480,     0,   476,   442,     0,
     482,   475,     0,    33,   213,   212,   211,   366,   442,    33,
     205,   204,     0,     0,   206,     0,   359,   371,   442,   442,
     454,   442,   472,   442,     0,   187,     0,     0,   199,   442,
     442,   442,    33,   207,   208,     0,   485,   193,   368,   363,
       0,   200,   202,   203,     0,   455,   442,   198,   442,   369,
     192,   194,     0,   201,     0,     0,   195
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -772,  -772,  -772,  -772,  -772,    -7,   123,  -772,  -772,     8,
      17,   -18,  -772,   252,  -772,   405,   267,  -195,  -772,   339,
    -772,  -772,  -772,  -772,  -212,  -772,    27,  -772,  -772,   543,
      40,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
     110,  -772,  -204,  -772,  -772,  -772,  -772,  -772,  -772,  -772,
    -772,  -284,  -772,  -772,  -772,  -771,  -772,  -772,  -772,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,   -70,
    -772,  -772,  -772,  -772,   345,  -772,  -772,   263,     4,  -772,
     103,     6,  -772,   -59,  -772,  -772,  -189,   -95,  -772,  -772,
    -772,   188,  -772,  -772,  -772,  -772,  -772,  -772,  -772,  -144,
    -772,  -772,  -772,  -772,  -772,    15,  -772,  -772,   -60,  -772,
    -648,  -772,  -639,  -772,  -772,  -630,  -629,  -592,   -31,  -772,
    -772,  -772,  -772,  -772,  -772,  -772,  -772,  -772,   -30,  -772,
    -772,  -772,  -772,  -248,  -201,  -772,   364,  -209,     5,    49,
    -531,     0,  -119,  -772,   361,  -151,  -724,  -148,  -772,  -772,
    -772,   761,  -772,  -772,   277,   -93
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,    19,   173,   163,   672,   647,   142,
      95,    22,   181,   186,   369,   182,   183,   143,   144,   145,
     221,    23,   212,   459,    24,    25,   561,   594,   632,    91,
     164,    27,   146,   540,   389,   466,    28,   213,   460,   467,
     468,   611,   660,   683,   684,   778,   685,   725,   726,   866,
     871,   789,   790,   860,   832,   791,   469,    29,    30,   202,
     453,   225,   394,   472,    31,   205,   456,    32,   571,    33,
     274,   603,   638,   604,   115,   165,    35,   166,    37,    38,
     167,    40,    41,   177,   178,   276,   116,   117,   437,   438,
      42,    43,    44,   208,   457,    45,    46,   209,   458,   461,
     533,    47,   203,   379,   524,   525,    48,    49,   108,    50,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   226,
     400,   498,   674,   717,   718,   499,   396,   618,   619,   697,
     737,   696,   735,   783,   792,   793,    51,   691,   692,   546,
     451,    53,   168,   169,   170,   184,   502,   269,   408,   503,
     558,   171,   172,   719,   270,   190
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   231,    96,    85,   175,   375,   129,   373,    52,   111,
     784,    20,   687,   393,   584,   833,   398,   194,   243,   105,
      21,   688,   217,   109,   197,    73,   199,   118,   531,   651,
     689,   690,  -162,   648,    62,     7,   -33,   599,   601,   191,
     -25,    94,     7,    26,     4,   615,     7,     7,   192,   537,
      72,     7,     7,   -25,   -25,    73,   148,   615,   538,    67,
      62,    26,    62,   114,   616,    62,   727,    62,    62,   127,
      62,    62,    69,    62,    62,    62,   616,    85,   861,   214,
     106,   700,   272,   474,   110,    73,   243,   133,   119,     5,
     162,   133,   114,   605,   554,    73,   162,   873,    64,    65,
     635,    87,   555,   606,     8,     9,    39,     7,   242,   556,
      26,   784,    84,    26,    62,    26,    26,     7,    62,    26,
      11,    98,   407,    26,    39,    64,    65,    62,    62,  -246,
      63,    13,    62,    62,   162,   242,    14,     7,    15,    26,
      16,    17,   636,   377,   733,   162,   380,   431,    88,   381,
     382,   263,   195,   383,   384,   100,    65,   240,     7,   266,
     -17,   192,   -17,   -17,   101,   242,    75,    97,   740,   102,
      77,    78,    62,    39,   -17,   687,    39,   465,    39,    39,
     470,   141,    39,   442,   688,    62,    39,    82,   486,   114,
     107,   500,   107,   689,   690,   120,   147,   122,   124,   128,
     131,   132,    39,   136,   137,   138,    64,    65,   257,   258,
     259,   218,   219,    54,    55,   263,   242,    89,   220,   401,
      65,    56,   148,   266,   -24,    90,   180,   200,   279,   242,
     399,    62,    57,   391,   162,    58,    26,    62,   162,    89,
     206,    59,   392,   207,   201,   516,    98,    92,   204,    97,
      64,    65,    60,    61,   223,   402,   235,   210,   211,   162,
     553,    26,   215,   216,   280,    26,    36,   135,    54,    55,
     103,   140,    62,   666,   522,   180,    56,   447,   104,   448,
     667,   449,   222,   192,    36,  -134,    66,    57,    68,   569,
      58,    70,    71,     7,   668,   100,    59,   238,   570,    39,
     669,   224,   275,  -247,   188,   189,   844,    60,    61,   280,
     196,   670,   671,    99,   867,   371,   -24,   868,   454,    64,
      65,    54,    55,   239,    39,   564,   567,   241,    39,    56,
     245,   188,   189,    36,   574,   575,    36,   441,    36,    36,
      57,   244,    36,    58,   277,   515,    36,   278,    34,    59,
     188,   189,   279,    98,   280,   557,   514,    64,    65,   473,
      60,   405,    36,   188,   189,   376,    86,   409,   378,   507,
     508,    62,   385,   235,    85,   534,   535,   386,   179,    62,
      62,   403,   631,   572,   573,   430,   440,   455,    62,   450,
     505,   512,   520,   484,   471,   521,   526,   464,    94,   527,
     528,    62,   180,   141,   529,   501,   392,   530,   485,   542,
     548,   551,   565,   537,   560,   179,   234,   392,   121,   519,
     125,   130,    54,    55,   134,   536,   545,   566,   139,    26,
      56,   547,    26,   581,    62,   568,   591,   582,   585,   595,
     487,    57,   589,    99,    58,   598,   597,   607,    62,   608,
      59,   623,   640,   610,   626,   620,   634,   639,    94,    36,
     646,    60,    61,   679,   593,   652,   644,    62,    62,   532,
     645,   553,   655,   656,   658,   539,   659,   661,   662,   179,
     552,   663,   179,   664,    36,   179,   179,   665,    36,   179,
     179,   675,    39,   673,   678,    39,   720,   721,   233,   698,
     628,   107,   699,    39,   653,   722,   729,   114,   739,   462,
     463,    99,   746,   242,  -210,     5,   749,   776,   476,   641,
     642,   643,   818,   774,   775,   828,   777,   795,    54,    55,
      62,   506,   637,   234,   824,   825,    56,   677,   826,   827,
     835,   848,  -209,   849,   857,   858,   444,    57,   162,   859,
      58,   869,   114,   876,    26,   874,    59,   230,   162,   446,
       5,   577,   388,    62,   517,   657,   387,    60,   748,    62,
     395,   772,    26,    93,   823,     8,     9,   541,   523,   602,
     532,   532,   872,    84,   613,   600,   614,   852,   649,   397,
     617,    11,   837,   583,   633,     0,     0,   543,   544,    26,
      54,    55,    13,     0,     0,     0,   410,    14,    56,    15,
       0,   630,    85,    18,   484,   436,   162,    39,     0,    57,
      26,     0,    58,     0,     0,   822,   617,     0,    59,    94,
       0,     0,     0,     0,    26,    39,     0,     0,     0,    60,
      88,     0,    26,     0,     0,     0,     0,     0,     0,   162,
       0,     0,    36,   484,     0,    36,     0,     0,     0,     0,
     579,   487,    39,   488,    85,     0,   484,   714,   681,     0,
      26,     0,     0,    62,     0,    26,     0,   682,     0,    62,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   523,     0,     0,     0,    39,     0,   609,
     487,     0,     0,     0,   734,    39,     0,     0,   747,   846,
       0,     0,     0,   487,   715,     0,     0,     0,   798,     0,
       0,    62,    26,    62,    62,    62,     0,   484,    54,    55,
       0,     0,     0,    39,   395,     0,    56,   475,    39,    62,
       0,     0,     0,     0,     0,   395,     0,    57,   723,     0,
      58,     0,     0,     0,     0,     0,    59,    94,     0,     0,
       0,     0,     0,    39,     0,    99,     0,    60,    61,     0,
       0,     0,   629,     0,   782,   552,     0,    36,    62,     0,
     559,     0,     0,     5,     0,    39,     7,    72,     0,     0,
       0,     0,    73,    74,     0,    36,     0,    75,     8,     9,
      76,    77,    78,   724,     0,     0,    84,     0,     0,   476,
      79,     0,    80,    81,    11,   580,   484,     0,    82,     0,
       0,   162,    36,    83,     0,    13,     0,     0,   484,     0,
      14,   681,    15,     0,    16,    17,    18,   847,     0,     0,
     682,     0,     0,   612,     0,     0,    -3,     0,     0,     0,
       0,   544,     0,   779,   780,   781,     0,    36,     0,   174,
     864,   176,     0,   487,   185,    36,   187,    62,     0,   797,
     193,     0,     0,     0,     0,   782,     0,   576,     0,   198,
       0,     0,     0,     0,   650,     0,     0,     0,     0,   235,
       0,     0,     0,    36,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     5,     0,     6,     7,   829,     0,
     227,   228,   229,   185,   236,   237,     0,     0,     5,     8,
       9,     7,     0,   488,     0,     0,    39,    10,     0,     0,
       0,     0,   390,     8,     9,    11,   650,   716,    12,    34,
       0,    84,     0,     0,     0,    36,    13,   130,     0,    11,
       0,    14,     0,    15,     0,    16,    17,    18,     0,     0,
      13,     0,     0,     0,     0,    14,     0,    15,     0,     0,
       0,    18,     0,     0,     0,    86,     0,     0,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   773,   875,     0,     0,
     406,     0,     0,     0,     0,   686,     0,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   422,   423,
     424,   425,   426,   427,   428,   429,     0,   728,   432,   433,
       0,   439,   149,   150,     0,     0,     0,     0,   443,     0,
       0,   445,   151,     0,     0,   152,     0,     0,     0,   234,
       0,   153,     0,   154,     0,     0,     0,     5,     0,     0,
       0,     0,   434,     0,     0,   156,   157,   158,     0,     0,
      54,    55,     8,     9,     0,     0,     0,     0,    56,     0,
     232,     0,     0,     0,     0,     0,   488,     0,    11,    57,
       0,     0,    58,     0,     0,     0,     0,     0,    59,    13,
       0,     0,     0,     0,    14,     0,    15,     0,   435,    60,
      18,   160,   161,     0,     0,   149,   150,     0,     0,     0,
       0,     0,     0,     0,     0,   151,     0,     0,   152,     0,
       0,   233,     0,     0,   153,     0,   154,   452,     0,     0,
       5,     0,     0,     0,     0,   830,     0,     0,   156,   157,
     158,     0,     0,    54,    55,     8,     9,     0,     0,   831,
       0,    56,     0,   232,   504,     0,     0,     0,   686,     0,
       0,    11,    57,     0,     0,    58,     0,     0,     0,     0,
       0,    59,    13,     0,     0,     0,     0,    14,     0,    15,
       0,   511,    60,    18,   160,   161,     0,     0,   149,   150,
       0,     0,     0,     0,     0,     0,     0,     0,   151,     0,
       0,   152,     0,     0,     0,     0,     0,   153,     0,   154,
       0,     0,     0,     5,     0,     0,     0,     0,     0,     0,
       0,   156,   157,   158,     0,     0,    54,    55,     8,     9,
       0,     0,     0,   550,    56,     0,   232,     0,     0,     0,
       0,     0,     0,     0,    11,    57,     0,     0,    58,     0,
       0,     0,     0,     0,    59,    13,     0,     0,     0,     0,
      14,   562,    15,     0,   563,    60,    18,   160,   161,   253,
     254,   255,   256,   257,   258,   259,   149,   150,     0,     0,
     263,     0,     0,     0,     0,    65,   151,   578,   266,   152,
     836,     0,     0,     0,   242,   786,   452,   154,   268,   586,
       0,     5,   588,     0,     0,   590,   787,   592,     0,   156,
     157,   158,     0,     0,    54,    55,     0,     0,     0,   452,
     788,     0,    56,     0,   159,     0,     0,   149,   150,     0,
       0,     0,     0,    57,     0,     0,    58,   151,     0,     0,
     152,   870,    59,     0,     0,     0,   786,     0,   154,     0,
       0,     0,     5,    60,    18,   160,   161,   787,     0,     0,
     156,   157,   158,     0,     0,    54,    55,     0,     0,     0,
       0,   788,     0,    56,     0,   159,   654,     0,     0,     0,
       0,     0,     0,     0,    57,     0,     0,    58,     0,     0,
       0,     0,     0,    59,     0,     0,     0,     0,   149,   150,
       0,     0,     0,     0,    60,    18,   160,   161,   151,     0,
       0,   152,   693,   694,   695,     0,     0,   153,  -380,   154,
       0,     0,     0,     5,     0,     0,     0,     0,   155,     0,
       0,   156,   157,   158,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,    56,     0,   159,     0,   738,     0,
     452,     0,   741,   742,   743,    57,   744,   745,    58,     0,
       0,     0,     0,   248,    59,     0,     0,     0,   253,   254,
     255,   256,   257,   258,   259,    60,   123,   160,   161,   263,
       0,     0,     0,     0,    65,     0,   265,   266,     0,     0,
     794,     0,     0,   242,     0,     0,     0,   268,     0,     0,
       0,   799,   800,   801,   802,   803,   804,   805,   806,   807,
     808,   809,   810,   811,   812,   813,   814,   815,   816,   817,
       0,   819,   820,     0,   821,     5,     0,   185,     0,     0,
     112,     0,     0,     0,     0,     0,     0,   834,    54,    55,
       8,     9,     0,     0,   794,     0,    56,     0,    84,     0,
       0,     0,     0,     0,     0,     0,    11,    57,     0,     0,
      58,     0,     0,     0,     0,     5,    59,    13,     7,   842,
       0,     0,    14,     0,    15,     0,   113,    60,    18,     0,
       8,     9,     0,     0,     0,     0,     0,     0,    84,   853,
     854,     0,   855,     0,   856,     0,    11,     0,     0,     0,
     794,   862,   863,     0,     0,     0,     0,    13,     0,     0,
       0,     0,    14,     0,    15,     0,   281,   794,    18,   794,
     282,   283,     0,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   281,     0,
       0,     0,   282,   283,     0,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,   298,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   518,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     149,   150,     0,     0,     0,     0,     0,     0,     0,     0,
     151,     0,  -387,   152,     0,     0,     0,     0,     0,   153,
       0,   154,     0,  -387,     0,     5,     0,     0,     0,     0,
       0,     0,     0,   156,   157,   158,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,    56,     0,   159,   149,
     150,     0,     0,     0,     0,     0,     0,    57,     0,   151,
      58,     0,   152,  -387,     0,     0,    59,     0,   153,     0,
     154,     0,  -387,     0,     5,     0,     0,    60,   123,   160,
     161,     0,   156,   157,   158,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,    56,     0,   159,     0,     0,
     149,   150,     0,     0,     0,     0,    57,     0,     0,    58,
     151,     0,     0,   152,     0,    59,     0,     0,     0,   786,
       0,   154,     0,     0,     0,     5,    60,   123,   160,   161,
     787,     0,     0,   156,   157,   158,     0,     0,    54,    55,
       0,     0,     0,     0,   788,     0,    56,     0,   159,   149,
     150,     0,     0,     0,     0,     0,     0,    57,     0,   151,
      58,     0,   152,     0,     0,     0,    59,     0,   153,  -387,
     154,     0,  -387,     0,     5,     0,     0,    60,    18,   160,
     161,     0,   156,   157,   158,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,    56,     0,   159,     0,     0,
     149,   150,     0,     0,     0,     0,    57,     0,     0,    58,
     151,     0,     0,   152,     0,    59,     0,     0,     0,   153,
       0,   154,     0,     0,     0,     5,    60,    18,   160,   161,
     787,     0,     0,   156,   157,   158,     0,     0,    54,    55,
       0,     0,     0,     0,   788,     0,    56,     0,   159,     0,
       0,   149,   150,     0,     0,     0,     0,    57,     0,     0,
      58,   151,     0,     0,   152,     0,    59,     0,     0,     0,
     153,     0,   154,     0,     0,     0,     5,    60,    18,   160,
     161,   155,     0,     0,   156,   157,   158,     0,     0,    54,
      55,     0,     0,     0,     0,     0,     0,    56,     0,   159,
     149,   150,     0,     0,     0,     0,     0,     0,    57,     0,
     151,    58,     0,   152,     0,     0,     0,    59,     0,   153,
       0,   154,     0,     0,     0,     5,     0,   549,    60,   123,
     160,   161,     0,   156,   157,   158,     0,     0,    54,    55,
       0,     0,     0,     0,     0,     0,    56,     0,   159,   701,
     702,     0,     0,     0,     0,     0,     0,    57,     0,   703,
      58,     0,     0,   704,     0,     0,    59,     0,   705,     0,
     706,     0,     0,     0,     5,     0,     0,    60,    18,   160,
     161,     0,   707,   708,   709,     0,     0,    54,    55,     0,
       0,     0,     0,   710,     0,    56,     0,   711,   149,   150,
       0,     0,     0,     0,     0,     0,    57,     0,   151,    58,
       0,   152,   736,     0,     0,    59,     0,   153,     0,   154,
       0,     0,     0,     5,     0,     0,    60,    18,   712,   713,
       0,   156,   157,   158,     0,     0,    54,    55,     0,     0,
       0,     0,     0,     0,    56,     0,   159,   149,   150,     0,
       0,     0,     0,     0,     0,    57,     0,   151,    58,     0,
     152,     0,     0,     0,    59,     0,   153,     0,   154,     0,
       0,     0,     5,     0,     0,    60,    18,   160,   161,     0,
     156,   157,   158,     0,     0,    54,    55,     0,     0,     0,
       0,     0,     0,    56,     0,   159,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,     0,    58,   477,     0,
       0,     0,     0,    59,     0,     0,     0,     0,     0,     5,
       0,   478,     7,     0,    60,    18,   160,   161,     0,   479,
       0,     0,    54,    55,     8,     9,     0,     0,     0,     0,
      56,     0,    84,   480,     0,     0,     0,   481,     0,     0,
      11,    57,     0,     0,    58,     0,  -188,     0,     0,   482,
      59,    13,     0,   483,     0,     0,    14,     5,    15,   478,
       7,    60,    18,     0,     0,     0,     0,   479,     0,     0,
      54,    55,     8,     9,     0,     0,     0,     0,    56,     0,
      84,     0,     0,     0,     0,   481,     0,     0,    11,    57,
       0,     0,    58,     0,   845,     0,     0,     0,    59,    13,
       0,     0,     0,   680,    14,     5,    15,   478,     7,    60,
      18,     0,     0,     0,     0,   479,     0,     0,    54,    55,
       8,     9,     0,     0,     0,     0,    56,     0,    84,     0,
       0,     0,     0,   481,     0,     0,    11,    57,     0,     0,
      58,     0,     0,     0,     0,     0,    59,    13,     5,     0,
       0,     0,    14,     0,    15,     0,     0,    60,    18,     0,
       0,    54,    55,     8,     9,     0,     0,     0,     0,    56,
       0,    84,     0,     0,     0,     0,     0,     0,     0,    11,
      57,     0,     0,    58,     0,     0,     0,     0,     0,    59,
      13,     5,     0,     0,     0,    14,     0,    15,     0,    16,
     126,   123,     0,     0,    54,    55,     8,     9,     0,     0,
       0,     0,    56,     0,    84,     0,     0,     0,     0,     0,
       0,     0,    11,    57,     0,     0,    58,     0,     0,     0,
       0,     0,    59,    13,     0,     5,     0,     0,    14,     5,
      15,   478,     7,    60,   123,     0,     0,     0,     0,   479,
       8,     9,    54,    55,     0,     0,     0,     0,    84,     0,
      56,     0,     0,   480,     0,     0,    11,   481,     0,     0,
       0,    57,     0,     0,    58,     0,     0,    13,     0,   482,
      59,     0,    14,   483,    15,     0,    16,    17,    18,     0,
       0,    60,    18,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
       0,   263,     0,     0,     0,    64,    65,   264,   265,   266,
     404,     0,     0,     0,   267,   242,     0,     0,     0,   268,
       0,   850,   851,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
       0,   263,     0,     0,     0,    64,    65,   264,   265,   266,
       0,     0,     0,     0,   267,   242,     0,     0,     0,   268,
       0,   838,   839,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
       0,   263,   509,     0,     0,    64,    65,   264,   265,   266,
       0,     0,   510,     0,   267,   242,     0,     0,     0,   268,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,   624,
       0,     0,    64,    65,   264,   265,   266,     0,     0,   625,
       0,   267,   242,     0,     0,     0,   268,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,     0,   263,   840,     0,     0,    64,
      65,   264,   265,   266,     0,     0,   841,     0,   267,   242,
       0,     0,     0,   268,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,   271,     0,     0,    64,    65,   264,   265,
     266,     0,     0,     0,     0,   267,   242,     0,     0,     0,
     268,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,     0,   263,
     273,     0,     0,    64,    65,   264,   265,   266,     0,     0,
       0,     0,   267,   242,     0,     0,     0,   268,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,     0,     0,     0,
      64,    65,   264,   265,   266,   370,     0,     0,     0,   267,
     242,     0,     0,     0,   268,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,     0,   263,     0,     0,     0,    64,    65,   264,
     265,   266,   372,     0,     0,     0,   267,   242,     0,     0,
       0,   268,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,     0,
     263,     0,     0,     0,    64,    65,   264,   265,   266,   374,
       0,     0,     0,   267,   242,     0,     0,     0,   268,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,     0,   263,     0,     0,
       0,    64,    65,   264,   265,   266,   404,     0,     0,     0,
     267,   242,     0,     0,     0,   268,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,     0,   263,     0,     0,     0,    64,    65,
     264,   265,   266,     0,     0,   513,     0,   267,   242,     0,
       0,     0,   268,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
       0,   263,     0,     0,     0,    64,    65,   264,   265,   266,
       0,     0,     0,     0,   267,   242,     0,   587,     0,   268,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,   596,
       0,     0,    64,    65,   264,   265,   266,     0,     0,     0,
       0,   267,   242,     0,     0,     0,   268,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,     0,   263,     0,     0,     0,    64,
      65,   264,   265,   266,   621,     0,     0,     0,   267,   242,
       0,     0,     0,   268,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,     0,     0,     0,    64,    65,   264,   265,
     266,   622,     0,     0,     0,   267,   242,     0,     0,     0,
     268,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,     0,   263,
       0,     0,     0,    64,    65,   264,   265,   266,     0,     0,
       0,     0,   267,   242,     0,   627,     0,   268,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,   676,     0,     0,
      64,    65,   264,   265,   266,     0,     0,     0,     0,   267,
     242,     0,     0,     0,   268,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,     0,   263,     0,     0,     0,    64,    65,   264,
     265,   266,   730,     0,     0,     0,   267,   242,     0,     0,
       0,   268,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,     0,
     263,     0,     0,     0,    64,    65,   264,   265,   266,   731,
       0,     0,     0,   267,   242,     0,     0,     0,   268,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,     0,   263,     0,     0,
       0,    64,    65,   264,   265,   266,   732,     0,     0,     0,
     267,   242,     0,     0,     0,   268,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,     0,   263,     0,     0,     0,    64,    65,
     264,   265,   266,     0,     0,   785,     0,   267,   242,     0,
       0,     0,   268,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
       0,   263,     0,     0,     0,    64,    65,   264,   265,   266,
     796,     0,     0,     0,   267,   242,     0,     0,     0,   268,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,     0,   263,     0,
       0,     0,    64,    65,   264,   265,   266,     0,     0,   843,
       0,   267,   242,     0,     0,     0,   268,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,     0,   263,   865,     0,     0,    64,
      65,   264,   265,   266,     0,     0,     0,     0,   267,   242,
       0,     0,     0,   268,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,     0,   263,     0,     0,     0,    64,    65,   264,   265,
     266,     0,     0,     0,  -207,   267,   242,     0,     0,     0,
     268,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,     0,   263,
       0,     0,     0,    64,    65,   264,   265,   266,     0,     0,
       0,  -208,   267,   242,     0,     0,     0,   268,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,     0,   263,     0,     0,     0,
      64,    65,   264,   265,   266,     0,     0,     0,     0,   267,
     242,     0,     0,     0,   268,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,     0,   263,     0,     0,     0,    64,    65,   264,
     265,   266,     0,     0,     0,     0,     0,   242,     0,     0,
       0,   268,   750,   751,   752,   753,   754,   755,   756,   757,
     758,   759,   760,   761,   762,   763,   764,   765,   766,     0,
     767,     0,     0,     0,    64,    65,   768,   769,     0,     0,
       0,     0,     0,   770,   242,     0,     0,     0,   771,   246,
     247,   248,   249,     0,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,     0,   263,     0,     0,
       0,    64,    65,   264,   265,   266,     0,     0,     0,     0,
       0,   242,   246,   247,   248,   268,     0,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,     0,
     263,     0,     0,     0,    64,    65,   264,   265,   266,     0,
       0,     0,     0,     0,   242,   246,   247,   248,   268,     0,
       0,     0,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,     0,   263,     0,     0,     0,    64,    65,   264,
     265,   266,     0,     0,     0,     0,     0,   242,   248,     0,
       0,   268,     0,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,     0,   263,     0,     0,     0,     0,    65,
       0,   265,   266,     0,     0,     0,     0,     0,   242,   248,
       0,     0,   268,     0,   253,   254,   255,   256,   257,   258,
     259,     0,   261,   262,     0,   263,     0,     0,     0,     0,
      65,     0,   265,   266,     0,     0,     0,     0,     0,   242,
     248,     0,     0,   268,     0,   253,   254,   255,   256,   257,
     258,   259,     0,   261,     0,     0,   263,     0,     0,     0,
       0,    65,     0,   265,   266,     0,     0,     0,     0,     0,
     242,     0,     0,     0,   268
};

static const yytype_int16 yycheck[] =
{
       7,   152,    33,    21,    99,   200,    76,   196,     3,    69,
     734,     3,   660,   225,   545,   786,   225,   110,   166,    52,
       3,   660,   141,    52,   117,    75,   119,    52,    47,   621,
     660,   660,    47,    47,    41,    61,    46,   568,    47,    47,
      46,    33,    61,     3,     0,    71,    61,    61,    56,    99,
      70,    61,    61,    59,    60,    75,    46,    71,   108,    46,
      67,    21,    69,    70,    90,    72,    46,    74,    75,    76,
      77,    78,    46,    80,    81,    82,    90,    95,   849,   138,
     113,   673,   175,   103,   113,    75,   234,    79,   113,    58,
      97,    83,    99,    47,    44,    75,   103,   868,    48,    49,
      69,    60,    52,    47,    73,    74,     3,    61,    58,    59,
      70,   835,    81,    73,   121,    75,    76,    61,   125,    79,
      89,    44,   241,    83,    21,    48,    49,   134,   135,    52,
       7,   100,   139,   140,   141,    58,   105,    61,   107,    99,
     109,   110,   111,   202,    47,   152,   205,   266,   111,   208,
     209,    44,    47,   212,   213,    44,    49,   164,    61,    52,
      46,    56,    48,    49,    41,    58,    80,    52,   699,    60,
      84,    85,   179,    70,    60,   823,    73,   389,    75,    76,
     389,    52,    79,   276,   823,   192,    83,   101,   400,   196,
      67,   400,    69,   823,   823,    72,    46,    74,    75,    76,
      77,    78,    99,    80,    81,    82,    48,    49,    37,    38,
      39,    87,    88,    71,    72,    44,    58,    52,    94,    47,
      49,    79,    46,    52,    60,    60,   103,    52,    56,    58,
     225,   238,    90,   225,   241,    93,   196,   244,   245,    52,
      60,    99,   225,    60,   121,   440,    44,    60,   125,    52,
      48,    49,   110,   111,    56,    47,   153,   134,   135,   266,
      58,   221,   139,   140,    56,   225,     3,    79,    71,    72,
      44,    83,   279,    72,    47,   152,    79,   370,    52,   372,
      79,   374,    53,    56,    21,    53,     9,    90,    11,    47,
      93,    14,    15,    61,    93,    44,    99,    58,    56,   196,
      99,    46,   179,    52,    50,    51,    53,   110,   111,    56,
      56,   110,   111,    36,    53,   192,    59,    56,   378,    48,
      49,    71,    72,    59,   221,   514,   521,    52,   225,    79,
      56,    50,    51,    70,   529,   530,    73,    56,    75,    76,
      90,    53,    79,    93,    59,   438,    83,    45,     3,    99,
      50,    51,    56,    44,    56,   503,    56,    48,    49,   390,
     110,   238,    99,    50,    51,    59,    21,   244,    46,    59,
      60,   378,    46,   270,   392,    59,    60,    53,   101,   386,
     387,    53,   594,   527,   528,    50,    52,    46,   395,    53,
      53,    53,    60,   400,   389,    52,    46,   389,   390,    46,
      46,   408,   279,    52,    52,   400,   389,    52,   400,    47,
      52,    52,    52,    99,    46,   138,   153,   400,    73,   450,
      75,    76,    71,    72,    79,    59,    59,    53,    83,   389,
      79,    60,   392,    47,   441,    59,   555,    46,    60,    60,
     400,    90,    72,   166,    93,    53,   565,    53,   455,    53,
      99,    52,    46,    60,    53,    60,    53,    60,   450,   196,
      75,   110,   111,   658,   559,    46,    59,   474,   475,   461,
      59,    58,    60,    52,    52,   467,    60,    52,    52,   202,
     487,    52,   205,    46,   221,   208,   209,    46,   225,   212,
     213,    53,   389,    78,    60,   392,    60,    53,   153,    59,
     593,   378,    59,   400,   623,    53,    47,   514,    46,   386,
     387,   234,    58,    58,    56,    58,    55,    52,   395,   612,
     613,   614,    50,    60,    60,    52,    60,    60,    71,    72,
     537,   408,   602,   270,    60,    60,    79,   656,    60,    60,
      55,    53,    56,    56,    46,    53,   279,    90,   555,    60,
      93,    60,   559,    60,   514,    55,    99,   152,   565,   307,
      58,   534,   223,   570,   441,   635,   221,   110,   716,   576,
     225,   719,   532,    30,   778,    73,    74,   467,   455,   571,
     572,   573,   866,    81,   580,   570,   580,   835,   618,   225,
     582,    89,   793,   544,   594,    -1,    -1,   474,   475,   559,
      71,    72,   100,    -1,    -1,    -1,   245,   105,    79,   107,
      -1,   594,   630,   111,   621,   270,   623,   514,    -1,    90,
     580,    -1,    93,    -1,    -1,   776,   618,    -1,    99,   621,
      -1,    -1,    -1,    -1,   594,   532,    -1,    -1,    -1,   110,
     111,    -1,   602,    -1,    -1,    -1,    -1,    -1,    -1,   656,
      -1,    -1,   389,   660,    -1,   392,    -1,    -1,    -1,    -1,
     537,   621,   559,   400,   682,    -1,   673,   674,   660,    -1,
     630,    -1,    -1,   680,    -1,   635,    -1,   660,    -1,   686,
      -1,   673,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   570,    -1,    -1,    -1,   594,    -1,   576,
     660,    -1,    -1,    -1,   696,   602,    -1,    -1,   715,   828,
      -1,    -1,    -1,   673,   674,    -1,    -1,    -1,   749,    -1,
      -1,   728,   682,   730,   731,   732,    -1,   734,    71,    72,
      -1,    -1,    -1,   630,   389,    -1,    79,   392,   635,   746,
      -1,    -1,    -1,    -1,    -1,   400,    -1,    90,    91,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    99,   749,    -1,    -1,
      -1,    -1,    -1,   660,    -1,   488,    -1,   110,   111,    -1,
      -1,    -1,    47,    -1,   734,   782,    -1,   514,   785,    -1,
     503,    -1,    -1,    58,    -1,   682,    61,    70,    -1,    -1,
      -1,    -1,    75,    76,    -1,   532,    -1,    80,    73,    74,
      83,    84,    85,   680,    -1,    -1,    81,    -1,    -1,   686,
      93,    -1,    95,    96,    89,   538,   823,    -1,   101,    -1,
      -1,   828,   559,   106,    -1,   100,    -1,    -1,   835,    -1,
     105,   823,   107,    -1,   109,   110,   111,   829,    -1,    -1,
     823,    -1,    -1,   580,    -1,    -1,     0,    -1,    -1,    -1,
      -1,   728,    -1,   730,   731,   732,    -1,   594,    -1,    98,
     852,   100,    -1,   823,   103,   602,   105,   874,    -1,   746,
     109,    -1,    -1,    -1,    -1,   835,    -1,   532,    -1,   118,
      -1,    -1,    -1,    -1,   621,    -1,    -1,    -1,    -1,   786,
      -1,    -1,    -1,   630,    -1,    -1,    -1,    -1,   635,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    60,    61,   785,    -1,
     149,   150,   151,   152,   153,   154,    -1,    -1,    58,    73,
      74,    61,    -1,   660,    -1,    -1,   823,    81,    -1,    -1,
      -1,    -1,    72,    73,    74,    89,   673,   674,    92,   594,
      -1,    81,    -1,    -1,    -1,   682,   100,   602,    -1,    89,
      -1,   105,    -1,   107,    -1,   109,   110,   111,    -1,    -1,
     100,    -1,    -1,    -1,    -1,   105,    -1,   107,    -1,    -1,
      -1,   111,    -1,    -1,    -1,   630,    -1,    -1,    -1,    -1,
     635,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   719,   874,    -1,    -1,
     239,    -1,    -1,    -1,    -1,   660,    -1,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    -1,   682,   267,   268,
      -1,   270,    33,    34,    -1,    -1,    -1,    -1,   277,    -1,
      -1,   280,    43,    -1,    -1,    46,    -1,    -1,    -1,   786,
      -1,    52,    -1,    54,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    63,    -1,    -1,    66,    67,    68,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    -1,   823,    -1,    89,    90,
      -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,    -1,   105,    -1,   107,    -1,   109,   110,
     111,   112,   113,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    46,    -1,
      -1,   786,    -1,    -1,    52,    -1,    54,   376,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    63,    -1,    -1,    66,    67,
      68,    -1,    -1,    71,    72,    73,    74,    -1,    -1,    77,
      -1,    79,    -1,    81,   403,    -1,    -1,    -1,   823,    -1,
      -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,    -1,
      -1,    99,   100,    -1,    -1,    -1,    -1,   105,    -1,   107,
      -1,   430,   110,   111,   112,   113,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    73,    74,
      -1,    -1,    -1,   482,    79,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    90,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    99,   100,    -1,    -1,    -1,    -1,
     105,   510,   107,    -1,   513,   110,   111,   112,   113,    33,
      34,    35,    36,    37,    38,    39,    33,    34,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    49,    43,   536,    52,    46,
      47,    -1,    -1,    -1,    58,    52,   545,    54,    62,   548,
      -1,    58,   551,    -1,    -1,   554,    63,   556,    -1,    66,
      67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,   568,
      77,    -1,    79,    -1,    81,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,    90,    -1,    -1,    93,    43,    -1,    -1,
      46,    47,    99,    -1,    -1,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,   110,   111,   112,   113,    63,    -1,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    77,    -1,    79,    -1,    81,   625,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    33,    34,
      -1,    -1,    -1,    -1,   110,   111,   112,   113,    43,    -1,
      -1,    46,   661,   662,   663,    -1,    -1,    52,    53,    54,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,    -1,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    -1,   697,    -1,
     699,    -1,   701,   702,   703,    90,   705,   706,    93,    -1,
      -1,    -1,    -1,    28,    99,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    39,   110,   111,   112,   113,    44,
      -1,    -1,    -1,    -1,    49,    -1,    51,    52,    -1,    -1,
     739,    -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,
      -1,   750,   751,   752,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
      -1,   770,   771,    -1,   773,    58,    -1,   776,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,   786,    71,    72,
      73,    74,    -1,    -1,   793,    -1,    79,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    58,    99,   100,    61,   818,
      -1,    -1,   105,    -1,   107,    -1,   109,   110,   111,    -1,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,   838,
     839,    -1,   841,    -1,   843,    -1,    89,    -1,    -1,    -1,
     849,   850,   851,    -1,    -1,    -1,    -1,   100,    -1,    -1,
      -1,    -1,   105,    -1,   107,    -1,    22,   866,   111,   868,
      26,    27,    -1,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    22,    -1,
      -1,    -1,    26,    27,    -1,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    -1,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    54,    -1,    56,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    46,    47,    -1,    -1,    99,    -1,    52,    -1,
      54,    -1,    56,    -1,    58,    -1,    -1,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,
      43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,   113,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,    53,
      54,    -1,    56,    -1,    58,    -1,    -1,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,    -1,
      33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,    93,
      43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,   113,
      63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    77,    -1,    79,    -1,    81,    -1,
      -1,    33,    34,    -1,    -1,    -1,    -1,    90,    -1,    -1,
      93,    43,    -1,    -1,    46,    -1,    99,    -1,    -1,    -1,
      52,    -1,    54,    -1,    -1,    -1,    58,   110,   111,   112,
     113,    63,    -1,    -1,    66,    67,    68,    -1,    -1,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,
      33,    34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,
      43,    93,    -1,    46,    -1,    -1,    -1,    99,    -1,    52,
      -1,    54,    -1,    -1,    -1,    58,    -1,    60,   110,   111,
     112,   113,    -1,    66,    67,    68,    -1,    -1,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,
      93,    -1,    -1,    47,    -1,    -1,    99,    -1,    52,    -1,
      54,    -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,
     113,    -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,
      -1,    -1,    -1,    77,    -1,    79,    -1,    81,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,
      -1,    46,    47,    -1,    -1,    99,    -1,    52,    -1,    54,
      -1,    -1,    -1,    58,    -1,    -1,   110,   111,   112,   113,
      -1,    66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    81,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    90,    -1,    43,    93,    -1,
      46,    -1,    -1,    -1,    99,    -1,    52,    -1,    54,    -1,
      -1,    -1,    58,    -1,    -1,   110,   111,   112,   113,    -1,
      66,    67,    68,    -1,    -1,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    93,    47,    -1,
      -1,    -1,    -1,    99,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    60,    61,    -1,   110,   111,   112,   113,    -1,    68,
      -1,    -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    81,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    90,    -1,    -1,    93,    -1,    47,    -1,    -1,    98,
      99,   100,    -1,   102,    -1,    -1,   105,    58,   107,    60,
      61,   110,   111,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,    -1,
      81,    -1,    -1,    -1,    -1,    86,    -1,    -1,    89,    90,
      -1,    -1,    93,    -1,    47,    -1,    -1,    -1,    99,   100,
      -1,    -1,    -1,   104,   105,    58,   107,    60,    61,   110,
     111,    -1,    -1,    -1,    -1,    68,    -1,    -1,    71,    72,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    81,    -1,
      -1,    -1,    -1,    86,    -1,    -1,    89,    90,    -1,    -1,
      93,    -1,    -1,    -1,    -1,    -1,    99,   100,    58,    -1,
      -1,    -1,   105,    -1,   107,    -1,    -1,   110,   111,    -1,
      -1,    71,    72,    73,    74,    -1,    -1,    -1,    -1,    79,
      -1,    81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    99,
     100,    58,    -1,    -1,    -1,   105,    -1,   107,    -1,   109,
     110,   111,    -1,    -1,    71,    72,    73,    74,    -1,    -1,
      -1,    -1,    79,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    90,    -1,    -1,    93,    -1,    -1,    -1,
      -1,    -1,    99,   100,    -1,    58,    -1,    -1,   105,    58,
     107,    60,    61,   110,   111,    -1,    -1,    -1,    -1,    68,
      73,    74,    71,    72,    -1,    -1,    -1,    -1,    81,    -1,
      79,    -1,    -1,    82,    -1,    -1,    89,    86,    -1,    -1,
      -1,    90,    -1,    -1,    93,    -1,    -1,   100,    -1,    98,
      99,    -1,   105,   102,   107,    -1,   109,   110,   111,    -1,
      -1,   110,   111,    26,    27,    28,    29,    30,    31,    32,
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
      50,    51,    52,    -1,    -1,    55,    -1,    57,    58,    -1,
      -1,    -1,    62,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    48,    49,    50,    51,    52,
      53,    -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,
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
      51,    52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    62,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    57,    58,    -1,    -1,    -1,    62,    26,
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
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,    49,
      -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,    28,
      -1,    -1,    62,    -1,    33,    34,    35,    36,    37,    38,
      39,    -1,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      28,    -1,    -1,    62,    -1,    33,    34,    35,    36,    37,
      38,    39,    -1,    41,    -1,    -1,    44,    -1,    -1,    -1,
      -1,    49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   119,   120,   121,     0,    58,    60,    61,    73,    74,
      81,    89,    92,   100,   105,   107,   109,   110,   111,   122,
     127,   128,   129,   139,   142,   143,   148,   149,   154,   175,
     176,   182,   185,   187,   192,   194,   195,   196,   197,   198,
     199,   200,   208,   209,   210,   213,   214,   219,   224,   225,
     227,   254,   256,   259,    71,    72,    79,    90,    93,    99,
     110,   111,   123,   124,    48,    49,   272,    46,   272,    46,
     272,   272,    70,    75,    76,    80,    83,    84,    85,    93,
      95,    96,   101,   106,    81,   129,   192,    60,   111,    52,
      60,   147,    60,   147,   127,   128,   236,    52,    44,   272,
      44,   124,    60,    44,    52,    52,   113,   124,   226,    52,
     113,   226,    63,   109,   123,   192,   204,   205,    52,   113,
     124,   192,   124,   111,   124,   192,   110,   123,   124,   187,
     192,   124,   124,   127,   192,   209,   124,   124,   124,   192,
     209,    52,   127,   135,   136,   137,   150,    46,    46,    33,
      34,    43,    46,    52,    54,    63,    66,    67,    68,    81,
     112,   113,   123,   124,   148,   193,   195,   198,   260,   261,
     262,   269,   270,   123,   269,   205,   269,   201,   202,   272,
     124,   130,   133,   134,   263,   269,   131,   269,    50,    51,
     273,    47,    56,   269,   273,    47,    56,   273,   269,   273,
      52,   124,   177,   220,   124,   183,    60,    60,   211,   215,
     124,   124,   140,   155,   201,   124,   124,   260,    87,    88,
      94,   138,    53,    56,    46,   179,   237,   269,   269,   269,
     133,   263,    81,   192,   195,   198,   269,   269,    58,    59,
     123,    52,    58,   265,    53,    56,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    44,    50,    51,    52,    57,    62,   265,
     272,    45,   273,    45,   188,   124,   203,    59,    45,    56,
      56,    22,    26,    27,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   132,
      53,   124,    53,   204,    53,   135,    59,   201,    46,   221,
     201,   201,   201,   201,   201,    46,    53,   192,   137,   152,
      72,   127,   128,   142,   180,   192,   244,   254,   255,   256,
     238,    47,    47,    53,    53,   124,   269,   260,   266,   124,
     262,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
      50,   260,   269,   269,    63,   109,   192,   206,   207,   269,
      52,    56,   273,   269,   134,   269,   131,   273,   273,   273,
      53,   258,   269,   178,   226,    46,   184,   212,   216,   141,
     156,   217,   124,   124,   127,   142,   153,   157,   158,   174,
     255,   256,   181,   236,   103,   192,   124,    47,    60,    68,
      82,    86,    98,   102,   123,   127,   142,   148,   195,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   239,   243,
     255,   256,   264,   267,   269,    53,   124,    59,    60,    45,
      55,   269,    53,    55,    56,   273,   135,   124,    53,   236,
      60,    52,    47,   124,   222,   223,    46,    46,    46,    52,
      52,    47,   127,   218,    59,    60,    59,    99,   108,   127,
     151,   158,    47,   124,   124,    59,   257,    60,    52,    60,
     269,    52,   123,    58,    44,    52,    59,   265,   268,   272,
      46,   144,   269,   269,   204,    52,    53,   135,    59,    47,
      56,   186,   217,   217,   135,   135,   192,   144,   269,   124,
     272,    47,    46,   257,   258,    60,   269,    60,   269,    72,
     269,   260,   269,   205,   145,    60,    45,   260,    53,   258,
     223,    47,   127,   189,   191,    47,    47,    53,    53,   124,
      60,   159,   195,   196,   199,    71,    90,   127,   245,   246,
      60,    53,    53,    52,    45,    55,    53,    60,   273,    47,
     128,   142,   146,   259,    53,    69,   111,   187,   190,    60,
      46,   273,   273,   273,    59,    59,    75,   126,    47,   246,
     195,   235,    46,   260,   269,    60,    52,   187,    52,    60,
     160,    52,    52,    52,    46,    46,    72,    79,    93,    99,
     110,   111,   125,    78,   240,    53,    45,   260,    60,   135,
     104,   127,   128,   161,   162,   164,   192,   228,   230,   233,
     234,   255,   256,   269,   269,   269,   249,   247,    59,    59,
     235,    33,    34,    43,    47,    52,    54,    66,    67,    68,
      77,    81,   112,   113,   123,   148,   195,   241,   242,   271,
      60,    53,    53,    91,   124,   165,   166,    46,   192,    47,
      53,    53,    53,    47,   127,   250,    47,   248,   269,    46,
     258,   269,   269,   269,   269,   269,    58,   123,   265,    55,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    44,    50,    51,
      57,    62,   265,   272,    60,    60,    52,    60,   163,   124,
     124,   124,   148,   251,   264,    55,    52,    63,    77,   169,
     170,   173,   252,   253,   269,    60,    53,   124,   236,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,    50,   269,
     269,   269,   263,   160,    60,    60,    60,    60,    52,   124,
      63,    77,   172,   173,   269,    55,    47,   252,    64,    65,
      45,    55,   269,    55,    53,    47,   260,   127,    53,    56,
      64,    65,   251,   269,   269,   269,   269,    46,    53,    60,
     171,   173,   269,   269,   127,    45,   167,    53,    56,    60,
      47,   168,   169,   173,    55,   124,    60
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
     143,   143,   143,   144,   145,   145,   146,   146,   147,   147,
     148,   150,   151,   149,   152,   152,   153,   153,   153,   153,
     155,   156,   154,   157,   157,   159,   158,   160,   160,   161,
     161,   161,   161,   161,   161,   161,   163,   162,   164,   164,
     165,   165,   166,   167,   167,   168,   169,   169,   170,   170,
     171,   171,   172,   172,   172,   172,   173,   173,   173,   173,
     173,   174,   174,   174,   175,   177,   178,   176,   179,   179,
     180,   180,   180,   180,   180,   181,   183,   184,   182,   182,
     182,   185,   186,   186,   188,   187,   189,   189,   190,   189,
     191,   192,   192,   192,   192,   192,   193,   193,   194,   194,
     195,   196,   197,   197,   198,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   200,   200,   200,   201,
     201,   202,   203,   203,   204,   204,   204,   204,   205,   205,
     205,   206,   206,   206,   207,   207,   208,   208,   208,   208,
     208,   209,   209,   209,   209,   211,   212,   210,   213,   215,
     216,   214,   217,   217,   218,   220,   219,   221,   219,   222,
     222,   223,   224,   225,   226,   226,   227,   227,   227,   227,
     228,   228,   229,   229,   230,   231,   232,   232,   233,   233,
     234,   235,   235,   235,   235,   235,   235,   235,   235,   237,
     236,   238,   238,   239,   240,   240,   241,   241,   242,   242,
     243,   243,   243,   243,   244,   245,   245,   246,   246,   246,
     246,   247,   247,   248,   249,   249,   250,   251,   251,   252,
     253,   253,   254,   255,   255,   256,   257,   257,   258,   259,
     260,   260,   261,   261,   262,   262,   262,   263,   263,   263,
     264,   264,   266,   265,   267,   267,   267,   267,   268,   268,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   270,   270,   270,   270,   270,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   271,   272,   272,   273,   273
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
       1,     1,     1,     0,     0,     0,     9,     7,     6,     1,
       0,     9,     8,     3,     0,     2,     1,     1,     0,     3,
       1,     0,     0,     8,     0,     2,     1,     1,     1,     1,
       0,     0,     9,     1,     2,     0,     8,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     0,     5,     0,     2,
       2,     1,     7,     0,     2,     4,     1,     1,     5,     3,
       1,     3,     3,     3,     1,     1,     1,     3,     3,     1,
       1,    10,    10,    10,     7,     0,     0,     9,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     0,     9,     1,
       4,     4,     0,     2,     0,     7,     3,     4,     0,     2,
       6,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     4,     4,     4,     4,     1,     1,     1,     1,     1,
       4,     4,     4,     6,     6,     6,     1,     1,     1,     0,
       1,     3,     1,     3,     1,     1,     1,     1,     0,     1,
       3,     1,     1,     1,     1,     3,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     0,     0,     9,     7,     0,
       0,     9,     0,     2,     4,     0,     7,     0,     8,     1,
       3,     3,     4,     4,     1,     3,     4,     4,     4,     4,
       1,     4,     5,     8,     1,     2,     2,     3,     5,     7,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       5,     0,     2,     7,     0,     2,     3,     2,     1,     1,
       1,     1,     1,     1,     6,     1,     2,     5,     5,     7,
       6,     0,     2,     5,     0,     2,     3,     1,     4,     5,
       1,     2,     7,     5,     4,     7,     0,     2,     1,     2,
       0,     1,     1,     3,     1,     3,     1,     0,     1,     3,
       1,     2,     0,     3,     1,     1,     2,     2,     3,     5,
       1,     1,     1,     1,     1,     1,     2,     4,     6,     3,
       3,     3,     2,     2,     2,     2,     2,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     1,     0,     7,     4,     4,     4,     1,     1,     1,
       1,     1,     1,     2,     4,     6,     3,     2,     2,     2,
       2,     2,     3,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     1,     1,     1,     1
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
#line 2781 "p4parser.tab.c"
    break;

  case 5:
#line 249 "p4parser.y"
                         {}
#line 2787 "p4parser.tab.c"
    break;

  case 6:
#line 250 "p4parser.y"
                               {}
#line 2793 "p4parser.tab.c"
    break;

  case 7:
#line 254 "p4parser.y"
                              {}
#line 2799 "p4parser.tab.c"
    break;

  case 8:
#line 255 "p4parser.y"
                              {}
#line 2805 "p4parser.tab.c"
    break;

  case 9:
#line 256 "p4parser.y"
                              {}
#line 2811 "p4parser.tab.c"
    break;

  case 10:
#line 257 "p4parser.y"
                              {}
#line 2817 "p4parser.tab.c"
    break;

  case 11:
#line 258 "p4parser.y"
                              {}
#line 2823 "p4parser.tab.c"
    break;

  case 12:
#line 259 "p4parser.y"
                              {}
#line 2829 "p4parser.tab.c"
    break;

  case 13:
#line 260 "p4parser.y"
                              {}
#line 2835 "p4parser.tab.c"
    break;

  case 14:
#line 261 "p4parser.y"
                              {}
#line 2841 "p4parser.tab.c"
    break;

  case 15:
#line 262 "p4parser.y"
                              {}
#line 2847 "p4parser.tab.c"
    break;

  case 16:
#line 263 "p4parser.y"
                              {}
#line 2853 "p4parser.tab.c"
    break;

  case 17:
#line 267 "p4parser.y"
                {}
#line 2859 "p4parser.tab.c"
    break;

  case 18:
#line 268 "p4parser.y"
                  {}
#line 2865 "p4parser.tab.c"
    break;

  case 19:
#line 269 "p4parser.y"
                  {}
#line 2871 "p4parser.tab.c"
    break;

  case 20:
#line 270 "p4parser.y"
                  {}
#line 2877 "p4parser.tab.c"
    break;

  case 21:
#line 271 "p4parser.y"
                  {}
#line 2883 "p4parser.tab.c"
    break;

  case 22:
#line 272 "p4parser.y"
                  {}
#line 2889 "p4parser.tab.c"
    break;

  case 23:
#line 273 "p4parser.y"
                  {}
#line 2895 "p4parser.tab.c"
    break;

  case 24:
#line 277 "p4parser.y"
                {}
#line 2901 "p4parser.tab.c"
    break;

  case 25:
#line 278 "p4parser.y"
                       {}
#line 2907 "p4parser.tab.c"
    break;

  case 26:
#line 282 "p4parser.y"
                     {}
#line 2913 "p4parser.tab.c"
    break;

  case 27:
#line 283 "p4parser.y"
                       {}
#line 2919 "p4parser.tab.c"
    break;

  case 28:
#line 284 "p4parser.y"
                       {}
#line 2925 "p4parser.tab.c"
    break;

  case 29:
#line 285 "p4parser.y"
                       {}
#line 2931 "p4parser.tab.c"
    break;

  case 30:
#line 286 "p4parser.y"
                       {}
#line 2937 "p4parser.tab.c"
    break;

  case 31:
#line 290 "p4parser.y"
                {}
#line 2943 "p4parser.tab.c"
    break;

  case 32:
#line 291 "p4parser.y"
                  {}
#line 2949 "p4parser.tab.c"
    break;

  case 33:
#line 295 "p4parser.y"
                  {}
#line 2955 "p4parser.tab.c"
    break;

  case 34:
#line 296 "p4parser.y"
                  {}
#line 2961 "p4parser.tab.c"
    break;

  case 35:
#line 300 "p4parser.y"
                  {}
#line 2967 "p4parser.tab.c"
    break;

  case 36:
#line 301 "p4parser.y"
                             {}
#line 2973 "p4parser.tab.c"
    break;

  case 37:
#line 306 "p4parser.y"
        {}
#line 2979 "p4parser.tab.c"
    break;

  case 38:
#line 308 "p4parser.y"
        {}
#line 2985 "p4parser.tab.c"
    break;

  case 39:
#line 310 "p4parser.y"
        {}
#line 2991 "p4parser.tab.c"
    break;

  case 42:
#line 319 "p4parser.y"
              {}
#line 2997 "p4parser.tab.c"
    break;

  case 43:
#line 321 "p4parser.y"
        {}
#line 3003 "p4parser.tab.c"
    break;

  case 44:
#line 323 "p4parser.y"
        {}
#line 3009 "p4parser.tab.c"
    break;

  case 45:
#line 327 "p4parser.y"
                       {}
#line 3015 "p4parser.tab.c"
    break;

  case 46:
#line 328 "p4parser.y"
                       {}
#line 3021 "p4parser.tab.c"
    break;

  case 47:
#line 329 "p4parser.y"
                       {}
#line 3027 "p4parser.tab.c"
    break;

  case 48:
#line 330 "p4parser.y"
                       {}
#line 3033 "p4parser.tab.c"
    break;

  case 49:
#line 331 "p4parser.y"
                       {}
#line 3039 "p4parser.tab.c"
    break;

  case 50:
#line 332 "p4parser.y"
                       {}
#line 3045 "p4parser.tab.c"
    break;

  case 51:
#line 333 "p4parser.y"
                       {}
#line 3051 "p4parser.tab.c"
    break;

  case 52:
#line 334 "p4parser.y"
                       {}
#line 3057 "p4parser.tab.c"
    break;

  case 53:
#line 335 "p4parser.y"
                       {}
#line 3063 "p4parser.tab.c"
    break;

  case 54:
#line 336 "p4parser.y"
                       {}
#line 3069 "p4parser.tab.c"
    break;

  case 55:
#line 337 "p4parser.y"
                       {}
#line 3075 "p4parser.tab.c"
    break;

  case 56:
#line 338 "p4parser.y"
                       {}
#line 3081 "p4parser.tab.c"
    break;

  case 57:
#line 339 "p4parser.y"
                       {}
#line 3087 "p4parser.tab.c"
    break;

  case 58:
#line 340 "p4parser.y"
                       {}
#line 3093 "p4parser.tab.c"
    break;

  case 59:
#line 341 "p4parser.y"
                       {}
#line 3099 "p4parser.tab.c"
    break;

  case 60:
#line 342 "p4parser.y"
                       {}
#line 3105 "p4parser.tab.c"
    break;

  case 61:
#line 343 "p4parser.y"
                       {}
#line 3111 "p4parser.tab.c"
    break;

  case 62:
#line 344 "p4parser.y"
                       {}
#line 3117 "p4parser.tab.c"
    break;

  case 63:
#line 345 "p4parser.y"
                       {}
#line 3123 "p4parser.tab.c"
    break;

  case 64:
#line 346 "p4parser.y"
                       {}
#line 3129 "p4parser.tab.c"
    break;

  case 65:
#line 347 "p4parser.y"
                       {}
#line 3135 "p4parser.tab.c"
    break;

  case 66:
#line 348 "p4parser.y"
                       {}
#line 3141 "p4parser.tab.c"
    break;

  case 67:
#line 349 "p4parser.y"
                       {}
#line 3147 "p4parser.tab.c"
    break;

  case 68:
#line 350 "p4parser.y"
                       {}
#line 3153 "p4parser.tab.c"
    break;

  case 69:
#line 351 "p4parser.y"
                       {}
#line 3159 "p4parser.tab.c"
    break;

  case 70:
#line 352 "p4parser.y"
                       {}
#line 3165 "p4parser.tab.c"
    break;

  case 71:
#line 353 "p4parser.y"
                       {}
#line 3171 "p4parser.tab.c"
    break;

  case 72:
#line 354 "p4parser.y"
                       {}
#line 3177 "p4parser.tab.c"
    break;

  case 73:
#line 355 "p4parser.y"
                       {}
#line 3183 "p4parser.tab.c"
    break;

  case 74:
#line 356 "p4parser.y"
                       {}
#line 3189 "p4parser.tab.c"
    break;

  case 75:
#line 357 "p4parser.y"
                       {}
#line 3195 "p4parser.tab.c"
    break;

  case 76:
#line 358 "p4parser.y"
                       {}
#line 3201 "p4parser.tab.c"
    break;

  case 77:
#line 359 "p4parser.y"
                       {}
#line 3207 "p4parser.tab.c"
    break;

  case 78:
#line 360 "p4parser.y"
                       {}
#line 3213 "p4parser.tab.c"
    break;

  case 79:
#line 361 "p4parser.y"
                       {}
#line 3219 "p4parser.tab.c"
    break;

  case 80:
#line 362 "p4parser.y"
                       {}
#line 3225 "p4parser.tab.c"
    break;

  case 81:
#line 363 "p4parser.y"
                       {}
#line 3231 "p4parser.tab.c"
    break;

  case 82:
#line 364 "p4parser.y"
                       {}
#line 3237 "p4parser.tab.c"
    break;

  case 83:
#line 365 "p4parser.y"
                       {}
#line 3243 "p4parser.tab.c"
    break;

  case 84:
#line 366 "p4parser.y"
                       {}
#line 3249 "p4parser.tab.c"
    break;

  case 85:
#line 367 "p4parser.y"
                       {}
#line 3255 "p4parser.tab.c"
    break;

  case 86:
#line 368 "p4parser.y"
                       {}
#line 3261 "p4parser.tab.c"
    break;

  case 87:
#line 369 "p4parser.y"
                       {}
#line 3267 "p4parser.tab.c"
    break;

  case 88:
#line 370 "p4parser.y"
                       {}
#line 3273 "p4parser.tab.c"
    break;

  case 89:
#line 371 "p4parser.y"
                       {}
#line 3279 "p4parser.tab.c"
    break;

  case 90:
#line 372 "p4parser.y"
                            {}
#line 3285 "p4parser.tab.c"
    break;

  case 91:
#line 374 "p4parser.y"
                       {}
#line 3291 "p4parser.tab.c"
    break;

  case 92:
#line 375 "p4parser.y"
                       {}
#line 3297 "p4parser.tab.c"
    break;

  case 93:
#line 376 "p4parser.y"
                       {}
#line 3303 "p4parser.tab.c"
    break;

  case 94:
#line 377 "p4parser.y"
                       {}
#line 3309 "p4parser.tab.c"
    break;

  case 95:
#line 378 "p4parser.y"
                       {}
#line 3315 "p4parser.tab.c"
    break;

  case 96:
#line 379 "p4parser.y"
                       {}
#line 3321 "p4parser.tab.c"
    break;

  case 97:
#line 380 "p4parser.y"
                       {}
#line 3327 "p4parser.tab.c"
    break;

  case 98:
#line 381 "p4parser.y"
                       {}
#line 3333 "p4parser.tab.c"
    break;

  case 99:
#line 382 "p4parser.y"
                       {}
#line 3339 "p4parser.tab.c"
    break;

  case 100:
#line 383 "p4parser.y"
                       {}
#line 3345 "p4parser.tab.c"
    break;

  case 101:
#line 384 "p4parser.y"
                       {}
#line 3351 "p4parser.tab.c"
    break;

  case 102:
#line 385 "p4parser.y"
                       {}
#line 3357 "p4parser.tab.c"
    break;

  case 103:
#line 386 "p4parser.y"
                       {}
#line 3363 "p4parser.tab.c"
    break;

  case 104:
#line 387 "p4parser.y"
                       {}
#line 3369 "p4parser.tab.c"
    break;

  case 105:
#line 388 "p4parser.y"
                       {}
#line 3375 "p4parser.tab.c"
    break;

  case 106:
#line 389 "p4parser.y"
                       {}
#line 3381 "p4parser.tab.c"
    break;

  case 108:
#line 391 "p4parser.y"
                       {}
#line 3387 "p4parser.tab.c"
    break;

  case 109:
#line 392 "p4parser.y"
                       {}
#line 3393 "p4parser.tab.c"
    break;

  case 110:
#line 393 "p4parser.y"
                       {}
#line 3399 "p4parser.tab.c"
    break;

  case 111:
#line 394 "p4parser.y"
                       {}
#line 3405 "p4parser.tab.c"
    break;

  case 112:
#line 395 "p4parser.y"
                       {}
#line 3411 "p4parser.tab.c"
    break;

  case 113:
#line 396 "p4parser.y"
                       {}
#line 3417 "p4parser.tab.c"
    break;

  case 114:
#line 397 "p4parser.y"
                       {}
#line 3423 "p4parser.tab.c"
    break;

  case 115:
#line 398 "p4parser.y"
                       {}
#line 3429 "p4parser.tab.c"
    break;

  case 116:
#line 399 "p4parser.y"
                       {}
#line 3435 "p4parser.tab.c"
    break;

  case 117:
#line 400 "p4parser.y"
                       {}
#line 3441 "p4parser.tab.c"
    break;

  case 118:
#line 401 "p4parser.y"
                       {}
#line 3447 "p4parser.tab.c"
    break;

  case 119:
#line 402 "p4parser.y"
                       {}
#line 3453 "p4parser.tab.c"
    break;

  case 120:
#line 403 "p4parser.y"
                       {}
#line 3459 "p4parser.tab.c"
    break;

  case 121:
#line 404 "p4parser.y"
                       {}
#line 3465 "p4parser.tab.c"
    break;

  case 122:
#line 405 "p4parser.y"
                       {}
#line 3471 "p4parser.tab.c"
    break;

  case 123:
#line 406 "p4parser.y"
                       {}
#line 3477 "p4parser.tab.c"
    break;

  case 124:
#line 407 "p4parser.y"
                       {}
#line 3483 "p4parser.tab.c"
    break;

  case 125:
#line 408 "p4parser.y"
                       {}
#line 3489 "p4parser.tab.c"
    break;

  case 126:
#line 409 "p4parser.y"
                       {}
#line 3495 "p4parser.tab.c"
    break;

  case 127:
#line 410 "p4parser.y"
                       {}
#line 3501 "p4parser.tab.c"
    break;

  case 128:
#line 411 "p4parser.y"
                       {}
#line 3507 "p4parser.tab.c"
    break;

  case 129:
#line 412 "p4parser.y"
                       {}
#line 3513 "p4parser.tab.c"
    break;

  case 130:
#line 413 "p4parser.y"
                       {}
#line 3519 "p4parser.tab.c"
    break;

  case 131:
#line 417 "p4parser.y"
                                      {}
#line 3525 "p4parser.tab.c"
    break;

  case 132:
#line 418 "p4parser.y"
                                        {}
#line 3531 "p4parser.tab.c"
    break;

  case 133:
#line 422 "p4parser.y"
                                         {}
#line 3537 "p4parser.tab.c"
    break;

  case 134:
#line 426 "p4parser.y"
                                      {}
#line 3543 "p4parser.tab.c"
    break;

  case 135:
#line 427 "p4parser.y"
                                      {}
#line 3549 "p4parser.tab.c"
    break;

  case 136:
#line 431 "p4parser.y"
                                          {}
#line 3555 "p4parser.tab.c"
    break;

  case 137:
#line 432 "p4parser.y"
                                            {}
#line 3561 "p4parser.tab.c"
    break;

  case 138:
#line 436 "p4parser.y"
                                            {}
#line 3567 "p4parser.tab.c"
    break;

  case 139:
#line 437 "p4parser.y"
                                                              {}
#line 3573 "p4parser.tab.c"
    break;

  case 140:
#line 441 "p4parser.y"
                 {}
#line 3579 "p4parser.tab.c"
    break;

  case 141:
#line 442 "p4parser.y"
                   {}
#line 3585 "p4parser.tab.c"
    break;

  case 142:
#line 443 "p4parser.y"
                   {}
#line 3591 "p4parser.tab.c"
    break;

  case 143:
#line 444 "p4parser.y"
                   {}
#line 3597 "p4parser.tab.c"
    break;

  case 144:
#line 448 "p4parser.y"
                                  {}
#line 3603 "p4parser.tab.c"
    break;

  case 145:
#line 449 "p4parser.y"
                        {}
#line 3609 "p4parser.tab.c"
    break;

  case 146:
#line 450 "p4parser.y"
                                    {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 3618 "p4parser.tab.c"
    break;

  case 147:
#line 458 "p4parser.y"
                     {}
#line 3624 "p4parser.tab.c"
    break;

  case 148:
#line 460 "p4parser.y"
                     {}
#line 3630 "p4parser.tab.c"
    break;

  case 151:
#line 467 "p4parser.y"
                     {}
#line 3636 "p4parser.tab.c"
    break;

  case 152:
#line 470 "p4parser.y"
                     {}
#line 3642 "p4parser.tab.c"
    break;

  case 153:
#line 476 "p4parser.y"
                               {}
#line 3648 "p4parser.tab.c"
    break;

  case 154:
#line 480 "p4parser.y"
                                     {}
#line 3654 "p4parser.tab.c"
    break;

  case 155:
#line 481 "p4parser.y"
                                     {}
#line 3660 "p4parser.tab.c"
    break;

  case 156:
#line 485 "p4parser.y"
                               {}
#line 3666 "p4parser.tab.c"
    break;

  case 157:
#line 486 "p4parser.y"
                               {}
#line 3672 "p4parser.tab.c"
    break;

  case 158:
#line 490 "p4parser.y"
                           {}
#line 3678 "p4parser.tab.c"
    break;

  case 159:
#line 491 "p4parser.y"
                                     {}
#line 3684 "p4parser.tab.c"
    break;

  case 160:
#line 495 "p4parser.y"
                             {}
#line 3690 "p4parser.tab.c"
    break;

  case 161:
#line 501 "p4parser.y"
                                                   { EnterScope(subparser); }
#line 3696 "p4parser.tab.c"
    break;

  case 162:
#line 502 "p4parser.y"
                                               { ExitScope(subparser); }
#line 3702 "p4parser.tab.c"
    break;

  case 163:
#line 503 "p4parser.y"
                             {}
#line 3708 "p4parser.tab.c"
    break;

  case 164:
#line 508 "p4parser.y"
                                           {}
#line 3714 "p4parser.tab.c"
    break;

  case 165:
#line 509 "p4parser.y"
                                             {}
#line 3720 "p4parser.tab.c"
    break;

  case 166:
#line 513 "p4parser.y"
                                    {}
#line 3726 "p4parser.tab.c"
    break;

  case 167:
#line 514 "p4parser.y"
                                      {}
#line 3732 "p4parser.tab.c"
    break;

  case 168:
#line 515 "p4parser.y"
                                      {}
#line 3738 "p4parser.tab.c"
    break;

  case 169:
#line 516 "p4parser.y"
                                      {}
#line 3744 "p4parser.tab.c"
    break;

  case 170:
#line 521 "p4parser.y"
                          {}
#line 3750 "p4parser.tab.c"
    break;

  case 171:
#line 522 "p4parser.y"
                          {}
#line 3756 "p4parser.tab.c"
    break;

  case 172:
#line 523 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 3765 "p4parser.tab.c"
    break;

  case 173:
#line 530 "p4parser.y"
                                    {}
#line 3771 "p4parser.tab.c"
    break;

  case 174:
#line 531 "p4parser.y"
                                      {}
#line 3777 "p4parser.tab.c"
    break;

  case 175:
#line 535 "p4parser.y"
                              {}
#line 3783 "p4parser.tab.c"
    break;

  case 176:
#line 537 "p4parser.y"
                                      {}
#line 3789 "p4parser.tab.c"
    break;

  case 177:
#line 541 "p4parser.y"
                                     {}
#line 3795 "p4parser.tab.c"
    break;

  case 178:
#line 542 "p4parser.y"
                                       {}
#line 3801 "p4parser.tab.c"
    break;

  case 179:
#line 546 "p4parser.y"
                                    {}
#line 3807 "p4parser.tab.c"
    break;

  case 180:
#line 547 "p4parser.y"
                                      {}
#line 3813 "p4parser.tab.c"
    break;

  case 181:
#line 548 "p4parser.y"
                                      {}
#line 3819 "p4parser.tab.c"
    break;

  case 182:
#line 549 "p4parser.y"
                                      {}
#line 3825 "p4parser.tab.c"
    break;

  case 183:
#line 550 "p4parser.y"
                                      {}
#line 3831 "p4parser.tab.c"
    break;

  case 184:
#line 551 "p4parser.y"
                                      {}
#line 3837 "p4parser.tab.c"
    break;

  case 185:
#line 552 "p4parser.y"
                                      {}
#line 3843 "p4parser.tab.c"
    break;

  case 186:
#line 556 "p4parser.y"
                           {}
#line 3849 "p4parser.tab.c"
    break;

  case 187:
#line 557 "p4parser.y"
                               {}
#line 3855 "p4parser.tab.c"
    break;

  case 188:
#line 561 "p4parser.y"
                                {}
#line 3861 "p4parser.tab.c"
    break;

  case 189:
#line 562 "p4parser.y"
                                  {}
#line 3867 "p4parser.tab.c"
    break;

  case 190:
#line 566 "p4parser.y"
                           {}
#line 3873 "p4parser.tab.c"
    break;

  case 191:
#line 567 "p4parser.y"
                       {}
#line 3879 "p4parser.tab.c"
    break;

  case 192:
#line 572 "p4parser.y"
                              {}
#line 3885 "p4parser.tab.c"
    break;

  case 193:
#line 576 "p4parser.y"
                               {}
#line 3891 "p4parser.tab.c"
    break;

  case 194:
#line 577 "p4parser.y"
                                 {}
#line 3897 "p4parser.tab.c"
    break;

  case 195:
#line 582 "p4parser.y"
      {}
#line 3903 "p4parser.tab.c"
    break;

  case 196:
#line 586 "p4parser.y"
                              {}
#line 3909 "p4parser.tab.c"
    break;

  case 197:
#line 587 "p4parser.y"
                                {}
#line 3915 "p4parser.tab.c"
    break;

  case 198:
#line 592 "p4parser.y"
                                {}
#line 3921 "p4parser.tab.c"
    break;

  case 199:
#line 593 "p4parser.y"
                                                    {}
#line 3927 "p4parser.tab.c"
    break;

  case 200:
#line 597 "p4parser.y"
                           {}
#line 3933 "p4parser.tab.c"
    break;

  case 201:
#line 598 "p4parser.y"
                                                        {}
#line 3939 "p4parser.tab.c"
    break;

  case 202:
#line 603 "p4parser.y"
                                 {}
#line 3945 "p4parser.tab.c"
    break;

  case 203:
#line 604 "p4parser.y"
                                   {}
#line 3951 "p4parser.tab.c"
    break;

  case 204:
#line 605 "p4parser.y"
                                  {}
#line 3957 "p4parser.tab.c"
    break;

  case 205:
#line 606 "p4parser.y"
                                       {}
#line 3963 "p4parser.tab.c"
    break;

  case 206:
#line 610 "p4parser.y"
                                {}
#line 3969 "p4parser.tab.c"
    break;

  case 207:
#line 611 "p4parser.y"
                                 {}
#line 3975 "p4parser.tab.c"
    break;

  case 208:
#line 612 "p4parser.y"
                                   {}
#line 3981 "p4parser.tab.c"
    break;

  case 209:
#line 613 "p4parser.y"
                                  {}
#line 3987 "p4parser.tab.c"
    break;

  case 210:
#line 614 "p4parser.y"
                                       {}
#line 3993 "p4parser.tab.c"
    break;

  case 211:
#line 620 "p4parser.y"
        {}
#line 3999 "p4parser.tab.c"
    break;

  case 212:
#line 623 "p4parser.y"
        {}
#line 4005 "p4parser.tab.c"
    break;

  case 213:
#line 626 "p4parser.y"
        {}
#line 4011 "p4parser.tab.c"
    break;

  case 214:
#line 634 "p4parser.y"
        {}
#line 4017 "p4parser.tab.c"
    break;

  case 215:
#line 639 "p4parser.y"
                     {}
#line 4023 "p4parser.tab.c"
    break;

  case 216:
#line 640 "p4parser.y"
                          {}
#line 4029 "p4parser.tab.c"
    break;

  case 217:
#line 641 "p4parser.y"
                                      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
        }
#line 4038 "p4parser.tab.c"
    break;

  case 218:
#line 648 "p4parser.y"
           {}
#line 4044 "p4parser.tab.c"
    break;

  case 219:
#line 649 "p4parser.y"
                                                       {}
#line 4050 "p4parser.tab.c"
    break;

  case 220:
#line 653 "p4parser.y"
                             {}
#line 4056 "p4parser.tab.c"
    break;

  case 221:
#line 654 "p4parser.y"
                               {}
#line 4062 "p4parser.tab.c"
    break;

  case 222:
#line 655 "p4parser.y"
                               {}
#line 4068 "p4parser.tab.c"
    break;

  case 223:
#line 656 "p4parser.y"
                               {}
#line 4074 "p4parser.tab.c"
    break;

  case 224:
#line 657 "p4parser.y"
                               {}
#line 4080 "p4parser.tab.c"
    break;

  case 225:
#line 661 "p4parser.y"
                   {}
#line 4086 "p4parser.tab.c"
    break;

  case 226:
#line 668 "p4parser.y"
                           {
            saveBaseType(subparser, getNodeAt(subparser, 2));
            bindIdent(subparser, getNodeAt(subparser, 2), getNodeAt(subparser, 1));
          }
#line 4095 "p4parser.tab.c"
    break;

  case 227:
#line 672 "p4parser.y"
                          {}
#line 4101 "p4parser.tab.c"
    break;

  case 232:
#line 683 "p4parser.y"
                                     {}
#line 4107 "p4parser.tab.c"
    break;

  case 233:
#line 684 "p4parser.y"
                                       {}
#line 4113 "p4parser.tab.c"
    break;

  case 234:
#line 689 "p4parser.y"
                               {}
#line 4119 "p4parser.tab.c"
    break;

  case 235:
#line 690 "p4parser.y"
                                      {}
#line 4125 "p4parser.tab.c"
    break;

  case 236:
#line 694 "p4parser.y"
                                               {}
#line 4131 "p4parser.tab.c"
    break;

  case 237:
#line 695 "p4parser.y"
                                                          {}
#line 4137 "p4parser.tab.c"
    break;

  case 238:
#line 696 "p4parser.y"
                                 {}
#line 4143 "p4parser.tab.c"
    break;

  case 239:
#line 697 "p4parser.y"
                                        {}
#line 4149 "p4parser.tab.c"
    break;

  case 241:
#line 707 "p4parser.y"
                                     {}
#line 4155 "p4parser.tab.c"
    break;

  case 242:
#line 708 "p4parser.y"
                                       {}
#line 4161 "p4parser.tab.c"
    break;

  case 243:
#line 709 "p4parser.y"
                                       {}
#line 4167 "p4parser.tab.c"
    break;

  case 244:
#line 710 "p4parser.y"
                                       {}
#line 4173 "p4parser.tab.c"
    break;

  case 245:
#line 711 "p4parser.y"
                                       {}
#line 4179 "p4parser.tab.c"
    break;

  case 246:
#line 715 "p4parser.y"
                                     {}
#line 4185 "p4parser.tab.c"
    break;

  case 247:
#line 716 "p4parser.y"
                                       {}
#line 4191 "p4parser.tab.c"
    break;

  case 248:
#line 720 "p4parser.y"
                                     {}
#line 4197 "p4parser.tab.c"
    break;

  case 249:
#line 721 "p4parser.y"
                                       {}
#line 4203 "p4parser.tab.c"
    break;

  case 250:
#line 725 "p4parser.y"
                                     {}
#line 4209 "p4parser.tab.c"
    break;

  case 251:
#line 729 "p4parser.y"
                                              {}
#line 4215 "p4parser.tab.c"
    break;

  case 252:
#line 733 "p4parser.y"
                                                    {}
#line 4221 "p4parser.tab.c"
    break;

  case 253:
#line 734 "p4parser.y"
                                                      {}
#line 4227 "p4parser.tab.c"
    break;

  case 254:
#line 738 "p4parser.y"
                                              {}
#line 4233 "p4parser.tab.c"
    break;

  case 255:
#line 742 "p4parser.y"
           {}
#line 4239 "p4parser.tab.c"
    break;

  case 256:
#line 743 "p4parser.y"
             {}
#line 4245 "p4parser.tab.c"
    break;

  case 257:
#line 744 "p4parser.y"
             {}
#line 4251 "p4parser.tab.c"
    break;

  case 258:
#line 745 "p4parser.y"
             {}
#line 4257 "p4parser.tab.c"
    break;

  case 259:
#line 746 "p4parser.y"
             {}
#line 4263 "p4parser.tab.c"
    break;

  case 260:
#line 748 "p4parser.y"
      {}
#line 4269 "p4parser.tab.c"
    break;

  case 261:
#line 750 "p4parser.y"
      {}
#line 4275 "p4parser.tab.c"
    break;

  case 262:
#line 752 "p4parser.y"
      {}
#line 4281 "p4parser.tab.c"
    break;

  case 263:
#line 755 "p4parser.y"
      {}
#line 4287 "p4parser.tab.c"
    break;

  case 264:
#line 757 "p4parser.y"
      {}
#line 4293 "p4parser.tab.c"
    break;

  case 265:
#line 759 "p4parser.y"
      {}
#line 4299 "p4parser.tab.c"
    break;

  case 266:
#line 763 "p4parser.y"
                {}
#line 4305 "p4parser.tab.c"
    break;

  case 267:
#line 764 "p4parser.y"
                  {}
#line 4311 "p4parser.tab.c"
    break;

  case 268:
#line 765 "p4parser.y"
                  {}
#line 4317 "p4parser.tab.c"
    break;

  case 269:
#line 770 "p4parser.y"
                              {}
#line 4323 "p4parser.tab.c"
    break;

  case 270:
#line 771 "p4parser.y"
                                {}
#line 4329 "p4parser.tab.c"
    break;

  case 271:
#line 775 "p4parser.y"
                                      {}
#line 4335 "p4parser.tab.c"
    break;

  case 272:
#line 779 "p4parser.y"
         {
        //  ASK possible to get the production name? (typeParameterList)
        // // saveBaseType(subparser, getNodeAt(subparser, 12));
        // if(getNodeAt(subparser, 5).isToken()){
          bindIdent(subparser, null, getNodeAt(subparser, 1), true);
        // }
      }
#line 4347 "p4parser.tab.c"
    break;

  case 273:
#line 786 "p4parser.y"
                                   {
        bindIdent(subparser, null, getNodeAt(subparser, 1), true);
      }
#line 4355 "p4parser.tab.c"
    break;

  case 274:
#line 792 "p4parser.y"
                                {}
#line 4361 "p4parser.tab.c"
    break;

  case 275:
#line 793 "p4parser.y"
                                  {}
#line 4367 "p4parser.tab.c"
    break;

  case 276:
#line 795 "p4parser.y"
                                  {}
#line 4373 "p4parser.tab.c"
    break;

  case 277:
#line 796 "p4parser.y"
                                       {}
#line 4379 "p4parser.tab.c"
    break;

  case 278:
#line 800 "p4parser.y"
                                   {}
#line 4385 "p4parser.tab.c"
    break;

  case 279:
#line 801 "p4parser.y"
                                     {}
#line 4391 "p4parser.tab.c"
    break;

  case 280:
#line 802 "p4parser.y"
                                       {}
#line 4397 "p4parser.tab.c"
    break;

  case 281:
#line 806 "p4parser.y"
                                {}
#line 4403 "p4parser.tab.c"
    break;

  case 282:
#line 807 "p4parser.y"
                                  {}
#line 4409 "p4parser.tab.c"
    break;

  case 283:
#line 808 "p4parser.y"
                                       {}
#line 4415 "p4parser.tab.c"
    break;

  case 284:
#line 814 "p4parser.y"
                                       {}
#line 4421 "p4parser.tab.c"
    break;

  case 285:
#line 815 "p4parser.y"
                                           {}
#line 4427 "p4parser.tab.c"
    break;

  case 286:
#line 819 "p4parser.y"
                               {}
#line 4433 "p4parser.tab.c"
    break;

  case 287:
#line 820 "p4parser.y"
                                       {}
#line 4439 "p4parser.tab.c"
    break;

  case 288:
#line 821 "p4parser.y"
                                       {}
#line 4445 "p4parser.tab.c"
    break;

  case 289:
#line 822 "p4parser.y"
                                       {}
#line 4451 "p4parser.tab.c"
    break;

  case 290:
#line 823 "p4parser.y"
                                       {}
#line 4457 "p4parser.tab.c"
    break;

  case 291:
#line 827 "p4parser.y"
                                     {}
#line 4463 "p4parser.tab.c"
    break;

  case 292:
#line 828 "p4parser.y"
                                       {}
#line 4469 "p4parser.tab.c"
    break;

  case 293:
#line 829 "p4parser.y"
                                       {}
#line 4475 "p4parser.tab.c"
    break;

  case 294:
#line 830 "p4parser.y"
                                       {}
#line 4481 "p4parser.tab.c"
    break;

  case 295:
#line 834 "p4parser.y"
                               {}
#line 4487 "p4parser.tab.c"
    break;

  case 296:
#line 834 "p4parser.y"
                                                    {}
#line 4493 "p4parser.tab.c"
    break;

  case 297:
#line 836 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 8));
          bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4502 "p4parser.tab.c"
    break;

  case 298:
#line 845 "p4parser.y"
      {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4511 "p4parser.tab.c"
    break;

  case 299:
#line 852 "p4parser.y"
                                     {}
#line 4517 "p4parser.tab.c"
    break;

  case 300:
#line 852 "p4parser.y"
                                                          {}
#line 4523 "p4parser.tab.c"
    break;

  case 301:
#line 853 "p4parser.y"
                                      {
        saveBaseType(subparser, getNodeAt(subparser, 8));
        bindIdent(subparser, getNodeAt(subparser, 8), getNodeAt(subparser, 7));
      }
#line 4532 "p4parser.tab.c"
    break;

  case 302:
#line 860 "p4parser.y"
                                     {}
#line 4538 "p4parser.tab.c"
    break;

  case 303:
#line 861 "p4parser.y"
                                       {}
#line 4544 "p4parser.tab.c"
    break;

  case 304:
#line 865 "p4parser.y"
                                           {}
#line 4550 "p4parser.tab.c"
    break;

  case 305:
#line 870 "p4parser.y"
                  {}
#line 4556 "p4parser.tab.c"
    break;

  case 306:
#line 871 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 6));
          bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
        }
#line 4565 "p4parser.tab.c"
    break;

  case 307:
#line 875 "p4parser.y"
                                       {}
#line 4571 "p4parser.tab.c"
    break;

  case 308:
#line 876 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 7));
          bindIdent(subparser, getNodeAt(subparser, 7), getNodeAt(subparser, 5));
        }
#line 4580 "p4parser.tab.c"
    break;

  case 309:
#line 883 "p4parser.y"
                            {}
#line 4586 "p4parser.tab.c"
    break;

  case 310:
#line 884 "p4parser.y"
                                                        {}
#line 4592 "p4parser.tab.c"
    break;

  case 311:
#line 888 "p4parser.y"
                               {}
#line 4598 "p4parser.tab.c"
    break;

  case 312:
#line 893 "p4parser.y"
        {}
#line 4604 "p4parser.tab.c"
    break;

  case 313:
#line 898 "p4parser.y"
        {}
#line 4610 "p4parser.tab.c"
    break;

  case 314:
#line 903 "p4parser.y"
                            {}
#line 4616 "p4parser.tab.c"
    break;

  case 315:
#line 904 "p4parser.y"
                                {}
#line 4622 "p4parser.tab.c"
    break;

  case 316:
#line 908 "p4parser.y"
                                        {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4631 "p4parser.tab.c"
    break;

  case 317:
#line 912 "p4parser.y"
                                                         {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4640 "p4parser.tab.c"
    break;

  case 318:
#line 916 "p4parser.y"
                                       {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4649 "p4parser.tab.c"
    break;

  case 319:
#line 920 "p4parser.y"
                                                      {
          saveBaseType(subparser, getNodeAt(subparser, 3));
          bindIdent(subparser, getNodeAt(subparser, 3), getNodeAt(subparser, 1));
        }
#line 4658 "p4parser.tab.c"
    break;

  case 320:
#line 931 "p4parser.y"
        {}
#line 4664 "p4parser.tab.c"
    break;

  case 321:
#line 933 "p4parser.y"
        {}
#line 4670 "p4parser.tab.c"
    break;

  case 322:
#line 938 "p4parser.y"
        {}
#line 4676 "p4parser.tab.c"
    break;

  case 323:
#line 940 "p4parser.y"
        {}
#line 4682 "p4parser.tab.c"
    break;

  case 324:
#line 944 "p4parser.y"
                   {}
#line 4688 "p4parser.tab.c"
    break;

  case 325:
#line 948 "p4parser.y"
                   {}
#line 4694 "p4parser.tab.c"
    break;

  case 326:
#line 952 "p4parser.y"
                                {}
#line 4700 "p4parser.tab.c"
    break;

  case 327:
#line 953 "p4parser.y"
                                  {}
#line 4706 "p4parser.tab.c"
    break;

  case 328:
#line 958 "p4parser.y"
        {}
#line 4712 "p4parser.tab.c"
    break;

  case 329:
#line 960 "p4parser.y"
        {}
#line 4718 "p4parser.tab.c"
    break;

  case 330:
#line 965 "p4parser.y"
                                                              {}
#line 4724 "p4parser.tab.c"
    break;

  case 331:
#line 969 "p4parser.y"
                                     {}
#line 4730 "p4parser.tab.c"
    break;

  case 332:
#line 970 "p4parser.y"
                                       {}
#line 4736 "p4parser.tab.c"
    break;

  case 333:
#line 971 "p4parser.y"
                                       {}
#line 4742 "p4parser.tab.c"
    break;

  case 334:
#line 972 "p4parser.y"
                                       {}
#line 4748 "p4parser.tab.c"
    break;

  case 335:
#line 973 "p4parser.y"
                                       {}
#line 4754 "p4parser.tab.c"
    break;

  case 336:
#line 974 "p4parser.y"
                                       {}
#line 4760 "p4parser.tab.c"
    break;

  case 337:
#line 975 "p4parser.y"
                                       {}
#line 4766 "p4parser.tab.c"
    break;

  case 338:
#line 976 "p4parser.y"
                                       {}
#line 4772 "p4parser.tab.c"
    break;

  case 339:
#line 980 "p4parser.y"
                           {}
#line 4778 "p4parser.tab.c"
    break;

  case 340:
#line 981 "p4parser.y"
                             {}
#line 4784 "p4parser.tab.c"
    break;

  case 341:
#line 985 "p4parser.y"
                                          {}
#line 4790 "p4parser.tab.c"
    break;

  case 342:
#line 986 "p4parser.y"
                                            {}
#line 4796 "p4parser.tab.c"
    break;

  case 343:
#line 990 "p4parser.y"
                                                                  {}
#line 4802 "p4parser.tab.c"
    break;

  case 344:
#line 994 "p4parser.y"
                             {}
#line 4808 "p4parser.tab.c"
    break;

  case 345:
#line 995 "p4parser.y"
                               {}
#line 4814 "p4parser.tab.c"
    break;

  case 346:
#line 999 "p4parser.y"
                                     {}
#line 4820 "p4parser.tab.c"
    break;

  case 347:
#line 1000 "p4parser.y"
                                       {}
#line 4826 "p4parser.tab.c"
    break;

  case 348:
#line 1004 "p4parser.y"
                             {}
#line 4832 "p4parser.tab.c"
    break;

  case 349:
#line 1005 "p4parser.y"
                               {}
#line 4838 "p4parser.tab.c"
    break;

  case 350:
#line 1009 "p4parser.y"
                             {}
#line 4844 "p4parser.tab.c"
    break;

  case 351:
#line 1010 "p4parser.y"
                               {}
#line 4850 "p4parser.tab.c"
    break;

  case 352:
#line 1011 "p4parser.y"
                               {}
#line 4856 "p4parser.tab.c"
    break;

  case 353:
#line 1012 "p4parser.y"
                               {}
#line 4862 "p4parser.tab.c"
    break;

  case 354:
#line 1020 "p4parser.y"
          {}
#line 4868 "p4parser.tab.c"
    break;

  case 355:
#line 1024 "p4parser.y"
                                       {}
#line 4874 "p4parser.tab.c"
    break;

  case 356:
#line 1025 "p4parser.y"
                                         {}
#line 4880 "p4parser.tab.c"
    break;

  case 357:
#line 1030 "p4parser.y"
        {}
#line 4886 "p4parser.tab.c"
    break;

  case 358:
#line 1032 "p4parser.y"
        {}
#line 4892 "p4parser.tab.c"
    break;

  case 359:
#line 1034 "p4parser.y"
        {}
#line 4898 "p4parser.tab.c"
    break;

  case 360:
#line 1036 "p4parser.y"
        {}
#line 4904 "p4parser.tab.c"
    break;

  case 361:
#line 1040 "p4parser.y"
                                       {}
#line 4910 "p4parser.tab.c"
    break;

  case 362:
#line 1041 "p4parser.y"
                                         {}
#line 4916 "p4parser.tab.c"
    break;

  case 363:
#line 1046 "p4parser.y"
                                         {}
#line 4922 "p4parser.tab.c"
    break;

  case 364:
#line 1050 "p4parser.y"
           {}
#line 4928 "p4parser.tab.c"
    break;

  case 365:
#line 1052 "p4parser.y"
        {}
#line 4934 "p4parser.tab.c"
    break;

  case 367:
#line 1061 "p4parser.y"
        {}
#line 4940 "p4parser.tab.c"
    break;

  case 368:
#line 1063 "p4parser.y"
        {}
#line 4946 "p4parser.tab.c"
    break;

  case 369:
#line 1068 "p4parser.y"
        {}
#line 4952 "p4parser.tab.c"
    break;

  case 370:
#line 1072 "p4parser.y"
                                   {}
#line 4958 "p4parser.tab.c"
    break;

  case 371:
#line 1073 "p4parser.y"
                                     {}
#line 4964 "p4parser.tab.c"
    break;

  case 372:
#line 1079 "p4parser.y"
                                                                            {
        saveBaseType(subparser, getNodeAt(subparser, 6));
        bindIdent(subparser, getNodeAt(subparser, 6), getNodeAt(subparser, 5));
      }
#line 4973 "p4parser.tab.c"
    break;

  case 373:
#line 1088 "p4parser.y"
                                                      {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 4982 "p4parser.tab.c"
    break;

  case 374:
#line 1092 "p4parser.y"
                                            {
        saveBaseType(subparser, getNodeAt(subparser, 4));
        bindIdent(subparser, getNodeAt(subparser, 4), getNodeAt(subparser, 3));
      }
#line 4991 "p4parser.tab.c"
    break;

  case 375:
#line 1100 "p4parser.y"
                                     {}
#line 4997 "p4parser.tab.c"
    break;

  case 376:
#line 1104 "p4parser.y"
                                     {}
#line 5003 "p4parser.tab.c"
    break;

  case 377:
#line 1105 "p4parser.y"
                                          {}
#line 5009 "p4parser.tab.c"
    break;

  case 378:
#line 1109 "p4parser.y"
                                        {}
#line 5015 "p4parser.tab.c"
    break;

  case 379:
#line 1115 "p4parser.y"
                                       {}
#line 5021 "p4parser.tab.c"
    break;

  case 380:
#line 1119 "p4parser.y"
                                       {}
#line 5027 "p4parser.tab.c"
    break;

  case 381:
#line 1120 "p4parser.y"
                                         {}
#line 5033 "p4parser.tab.c"
    break;

  case 382:
#line 1124 "p4parser.y"
                                       {}
#line 5039 "p4parser.tab.c"
    break;

  case 383:
#line 1125 "p4parser.y"
                                           {}
#line 5045 "p4parser.tab.c"
    break;

  case 384:
#line 1129 "p4parser.y"
                                       {}
#line 5051 "p4parser.tab.c"
    break;

  case 385:
#line 1130 "p4parser.y"
                                            {}
#line 5057 "p4parser.tab.c"
    break;

  case 386:
#line 1131 "p4parser.y"
                                              {}
#line 5063 "p4parser.tab.c"
    break;

  case 387:
#line 1135 "p4parser.y"
                                       {}
#line 5069 "p4parser.tab.c"
    break;

  case 388:
#line 1136 "p4parser.y"
                                         {}
#line 5075 "p4parser.tab.c"
    break;

  case 389:
#line 1137 "p4parser.y"
                                           {}
#line 5081 "p4parser.tab.c"
    break;

  case 390:
#line 1141 "p4parser.y"
                                       {}
#line 5087 "p4parser.tab.c"
    break;

  case 391:
#line 1142 "p4parser.y"
                                         {}
#line 5093 "p4parser.tab.c"
    break;

  case 392:
#line 1146 "p4parser.y"
        {}
#line 5099 "p4parser.tab.c"
    break;

  case 393:
#line 1146 "p4parser.y"
                {}
#line 5105 "p4parser.tab.c"
    break;

  case 394:
#line 1150 "p4parser.y"
                                       {}
#line 5111 "p4parser.tab.c"
    break;

  case 395:
#line 1151 "p4parser.y"
                                         {}
#line 5117 "p4parser.tab.c"
    break;

  case 396:
#line 1152 "p4parser.y"
                                         {}
#line 5123 "p4parser.tab.c"
    break;

  case 397:
#line 1153 "p4parser.y"
                                       {}
#line 5129 "p4parser.tab.c"
    break;

  case 398:
#line 1157 "p4parser.y"
                                            {}
#line 5135 "p4parser.tab.c"
    break;

  case 399:
#line 1158 "p4parser.y"
                                                      {}
#line 5141 "p4parser.tab.c"
    break;

  case 400:
#line 1161 "p4parser.y"
                                       {}
#line 5147 "p4parser.tab.c"
    break;

  case 401:
#line 1162 "p4parser.y"
                                         {}
#line 5153 "p4parser.tab.c"
    break;

  case 402:
#line 1163 "p4parser.y"
                                         {}
#line 5159 "p4parser.tab.c"
    break;

  case 403:
#line 1164 "p4parser.y"
                                         {}
#line 5165 "p4parser.tab.c"
    break;

  case 404:
#line 1165 "p4parser.y"
                                         {}
#line 5171 "p4parser.tab.c"
    break;

  case 405:
#line 1166 "p4parser.y"
                                         {}
#line 5177 "p4parser.tab.c"
    break;

  case 406:
#line 1167 "p4parser.y"
                                         {}
#line 5183 "p4parser.tab.c"
    break;

  case 407:
#line 1168 "p4parser.y"
                                                     {}
#line 5189 "p4parser.tab.c"
    break;

  case 408:
#line 1169 "p4parser.y"
                                                                 {}
#line 5195 "p4parser.tab.c"
    break;

  case 409:
#line 1170 "p4parser.y"
                                                 {}
#line 5201 "p4parser.tab.c"
    break;

  case 410:
#line 1171 "p4parser.y"
                                                 {}
#line 5207 "p4parser.tab.c"
    break;

  case 411:
#line 1172 "p4parser.y"
                                                 {}
#line 5213 "p4parser.tab.c"
    break;

  case 412:
#line 1173 "p4parser.y"
                                         {}
#line 5219 "p4parser.tab.c"
    break;

  case 413:
#line 1174 "p4parser.y"
                                                {}
#line 5225 "p4parser.tab.c"
    break;

  case 414:
#line 1175 "p4parser.y"
                                           {}
#line 5231 "p4parser.tab.c"
    break;

  case 415:
#line 1176 "p4parser.y"
                                          {}
#line 5237 "p4parser.tab.c"
    break;

  case 416:
#line 1178 "p4parser.y"
        {}
#line 5243 "p4parser.tab.c"
    break;

  case 417:
#line 1180 "p4parser.y"
        {}
#line 5249 "p4parser.tab.c"
    break;

  case 418:
#line 1181 "p4parser.y"
                                         {}
#line 5255 "p4parser.tab.c"
    break;

  case 419:
#line 1182 "p4parser.y"
                                         {}
#line 5261 "p4parser.tab.c"
    break;

  case 420:
#line 1183 "p4parser.y"
                                         {}
#line 5267 "p4parser.tab.c"
    break;

  case 421:
#line 1184 "p4parser.y"
                                         {}
#line 5273 "p4parser.tab.c"
    break;

  case 422:
#line 1185 "p4parser.y"
                                          {}
#line 5279 "p4parser.tab.c"
    break;

  case 423:
#line 1186 "p4parser.y"
                                           {}
#line 5285 "p4parser.tab.c"
    break;

  case 424:
#line 1187 "p4parser.y"
                                            {}
#line 5291 "p4parser.tab.c"
    break;

  case 425:
#line 1188 "p4parser.y"
                                             {}
#line 5297 "p4parser.tab.c"
    break;

  case 426:
#line 1189 "p4parser.y"
                                        {}
#line 5303 "p4parser.tab.c"
    break;

  case 427:
#line 1191 "p4parser.y"
        {}
#line 5309 "p4parser.tab.c"
    break;

  case 428:
#line 1192 "p4parser.y"
                                       {}
#line 5315 "p4parser.tab.c"
    break;

  case 429:
#line 1193 "p4parser.y"
                                       {}
#line 5321 "p4parser.tab.c"
    break;

  case 430:
#line 1195 "p4parser.y"
                                         {}
#line 5327 "p4parser.tab.c"
    break;

  case 431:
#line 1196 "p4parser.y"
                                             {}
#line 5333 "p4parser.tab.c"
    break;

  case 432:
#line 1198 "p4parser.y"
                                       {}
#line 5339 "p4parser.tab.c"
    break;

  case 433:
#line 1199 "p4parser.y"
                                       {}
#line 5345 "p4parser.tab.c"
    break;

  case 434:
#line 1200 "p4parser.y"
                                             {}
#line 5351 "p4parser.tab.c"
    break;

  case 435:
#line 1201 "p4parser.y"
                                             {}
#line 5357 "p4parser.tab.c"
    break;

  case 436:
#line 1202 "p4parser.y"
                                            {}
#line 5363 "p4parser.tab.c"
    break;

  case 437:
#line 1203 "p4parser.y"
                                       {}
#line 5369 "p4parser.tab.c"
    break;

  case 438:
#line 1204 "p4parser.y"
                                        {}
#line 5375 "p4parser.tab.c"
    break;

  case 439:
#line 1205 "p4parser.y"
                                       {}
#line 5381 "p4parser.tab.c"
    break;

  case 440:
#line 1206 "p4parser.y"
                                                      {}
#line 5387 "p4parser.tab.c"
    break;

  case 441:
#line 1207 "p4parser.y"
                         {}
#line 5393 "p4parser.tab.c"
    break;

  case 443:
#line 1211 "p4parser.y"
        {}
#line 5399 "p4parser.tab.c"
    break;

  case 444:
#line 1213 "p4parser.y"
        {}
#line 5405 "p4parser.tab.c"
    break;

  case 445:
#line 1215 "p4parser.y"
        {}
#line 5411 "p4parser.tab.c"
    break;

  case 446:
#line 1216 "p4parser.y"
                                                      {}
#line 5417 "p4parser.tab.c"
    break;

  case 447:
#line 1220 "p4parser.y"
                                       {}
#line 5423 "p4parser.tab.c"
    break;

  case 448:
#line 1221 "p4parser.y"
                                         {}
#line 5429 "p4parser.tab.c"
    break;

  case 449:
#line 1222 "p4parser.y"
                                         {}
#line 5435 "p4parser.tab.c"
    break;

  case 450:
#line 1223 "p4parser.y"
                                         {}
#line 5441 "p4parser.tab.c"
    break;

  case 451:
#line 1224 "p4parser.y"
                                         {}
#line 5447 "p4parser.tab.c"
    break;

  case 452:
#line 1225 "p4parser.y"
                                         {}
#line 5453 "p4parser.tab.c"
    break;

  case 453:
#line 1226 "p4parser.y"
                                         {}
#line 5459 "p4parser.tab.c"
    break;

  case 454:
#line 1227 "p4parser.y"
                                                             {}
#line 5465 "p4parser.tab.c"
    break;

  case 455:
#line 1228 "p4parser.y"
                                                                         {}
#line 5471 "p4parser.tab.c"
    break;

  case 456:
#line 1229 "p4parser.y"
                                                 {}
#line 5477 "p4parser.tab.c"
    break;

  case 457:
#line 1230 "p4parser.y"
                                         {}
#line 5483 "p4parser.tab.c"
    break;

  case 458:
#line 1231 "p4parser.y"
                                                {}
#line 5489 "p4parser.tab.c"
    break;

  case 459:
#line 1232 "p4parser.y"
                                           {}
#line 5495 "p4parser.tab.c"
    break;

  case 460:
#line 1233 "p4parser.y"
                                          {}
#line 5501 "p4parser.tab.c"
    break;

  case 461:
#line 1235 "p4parser.y"
        {}
#line 5507 "p4parser.tab.c"
    break;

  case 462:
#line 1237 "p4parser.y"
        {}
#line 5513 "p4parser.tab.c"
    break;

  case 463:
#line 1238 "p4parser.y"
                                                 {}
#line 5519 "p4parser.tab.c"
    break;

  case 464:
#line 1239 "p4parser.y"
                                                 {}
#line 5525 "p4parser.tab.c"
    break;

  case 465:
#line 1240 "p4parser.y"
                                                 {}
#line 5531 "p4parser.tab.c"
    break;

  case 466:
#line 1241 "p4parser.y"
                                                 {}
#line 5537 "p4parser.tab.c"
    break;

  case 467:
#line 1242 "p4parser.y"
                                                  {}
#line 5543 "p4parser.tab.c"
    break;

  case 468:
#line 1243 "p4parser.y"
                                                   {}
#line 5549 "p4parser.tab.c"
    break;

  case 469:
#line 1244 "p4parser.y"
                                                    {}
#line 5555 "p4parser.tab.c"
    break;

  case 470:
#line 1245 "p4parser.y"
                                                     {}
#line 5561 "p4parser.tab.c"
    break;

  case 471:
#line 1246 "p4parser.y"
                                                {}
#line 5567 "p4parser.tab.c"
    break;

  case 472:
#line 1248 "p4parser.y"
        {}
#line 5573 "p4parser.tab.c"
    break;

  case 473:
#line 1249 "p4parser.y"
                                               {}
#line 5579 "p4parser.tab.c"
    break;

  case 474:
#line 1250 "p4parser.y"
                                               {}
#line 5585 "p4parser.tab.c"
    break;

  case 475:
#line 1252 "p4parser.y"
                                         {}
#line 5591 "p4parser.tab.c"
    break;

  case 476:
#line 1253 "p4parser.y"
                                                     {}
#line 5597 "p4parser.tab.c"
    break;

  case 477:
#line 1254 "p4parser.y"
                                               {}
#line 5603 "p4parser.tab.c"
    break;

  case 478:
#line 1255 "p4parser.y"
                                               {}
#line 5609 "p4parser.tab.c"
    break;

  case 479:
#line 1256 "p4parser.y"
                                                     {}
#line 5615 "p4parser.tab.c"
    break;

  case 480:
#line 1257 "p4parser.y"
                                                     {}
#line 5621 "p4parser.tab.c"
    break;

  case 481:
#line 1258 "p4parser.y"
                                                    {}
#line 5627 "p4parser.tab.c"
    break;

  case 482:
#line 1259 "p4parser.y"
                                               {}
#line 5633 "p4parser.tab.c"
    break;

  case 483:
#line 1260 "p4parser.y"
                                                {}
#line 5639 "p4parser.tab.c"
    break;

  case 484:
#line 1261 "p4parser.y"
                                               {}
#line 5645 "p4parser.tab.c"
    break;

  case 485:
#line 1262 "p4parser.y"
                                                              {}
#line 5651 "p4parser.tab.c"
    break;


#line 5655 "p4parser.tab.c"

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
#line 1299 "p4parser.y"


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
