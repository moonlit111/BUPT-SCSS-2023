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
#line 1 "syntax.y"

    #include <stdio.h>
    #include <string.h>
    #include "lex.yy.c"
    #include "tree.h"
    #include "errlist.h"
    int exit_code = 0;
    Tree result = NULL;
    void yyerror(const char *s);
    void log_err(char type, size_t line_no, const char *msg);

#line 82 "syntax.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INT = 259,
    FLOAT = 260,
    CHAR = 261,
    STRUCT = 262,
    RETURN = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    PLUS = 267,
    MINUS = 268,
    MUL = 269,
    DIV = 270,
    AND = 271,
    OR = 272,
    LT = 273,
    LE = 274,
    GT = 275,
    GE = 276,
    NE = 277,
    EQ = 278,
    NOT = 279,
    ASSIGN = 280,
    TYPE = 281,
    LP = 282,
    RP = 283,
    LB = 284,
    RB = 285,
    LC = 286,
    RC = 287,
    SEMI = 288,
    COMMA = 289,
    DOT = 290,
    ILLEGAL = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 12 "syntax.y"

    struct Head *node;

#line 175 "syntax.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   415

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

#define YYUNDEFTOK  2
#define YYMAXUTOK   291


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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    32,    32,    36,    40,    43,    48,    52,    57,    60,
      63,    68,    73,    76,    79,    86,    92,    95,   101,   107,
     112,   115,   118,   123,   126,   132,   138,   142,   145,   148,
     152,   155,   160,   163,   170,   179,   186,   191,   195,   198,
     203,   206,   209,   214,   217,   220,   227,   232,   237,   242,
     247,   252,   257,   262,   267,   272,   277,   282,   287,   292,
     297,   301,   305,   311,   316,   319,   322,   328,   333,   336,
     339,   342,   345,   355,   358,   363
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INT", "FLOAT", "CHAR", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "PLUS", "MINUS", "MUL", "DIV", "AND",
  "OR", "LT", "LE", "GT", "GE", "NE", "EQ", "NOT", "ASSIGN", "TYPE", "LP",
  "RP", "LB", "RB", "LC", "RC", "SEMI", "COMMA", "DOT", "ILLEGAL",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      50,    19,   -61,    11,   -61,    50,    22,   -61,    -7,   -61,
     -61,   -61,     0,   -61,    27,   -19,    32,    50,    95,   -61,
     -61,    49,    65,    50,   -61,    16,    41,    50,   -61,   -61,
      65,    44,    61,    45,   -61,   -61,   180,    76,    37,    28,
      66,   -61,   -61,    69,   -61,   -61,    50,   -61,   -20,   -61,
     -61,   -61,   193,    51,    72,   193,   193,   193,   103,   -61,
      85,   151,    68,   -61,   193,   -61,   -61,    16,   -61,    43,
     193,    93,   193,   193,   165,    29,   218,   -61,   -61,   -61,
      50,   -61,   193,   193,   193,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   193,   -61,   117,   338,   -61,
     -61,   -61,   242,    64,   118,   -61,   -61,   266,   290,   -61,
     180,   165,   165,    29,    29,   380,   380,   136,   136,   136,
     136,   136,   136,   362,   314,   -61,   193,   -61,   -61,   -61,
     180,   180,   123,   -61,   -61,   115,   -61,   -61,   180,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,    12,     0,     2,     4,     0,    13,    15,     1,
       3,     9,    16,     6,     0,    11,     0,    38,     0,     8,
       5,     0,     0,    38,     7,     0,     0,    38,    21,    19,
       0,     0,    23,     0,    16,    10,    27,     0,    44,     0,
      41,    14,    37,    24,    20,    18,     0,    17,    68,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    27,     0,    43,     0,    40,    39,     0,    22,     0,
       0,     0,     0,     0,    60,    61,     0,    73,    25,    26,
      38,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,    45,    42,
      65,    63,    75,     0,     0,    32,    31,     0,     0,    59,
      27,    55,    56,    57,    58,    47,    48,    49,    50,    51,
      52,    53,    54,    46,     0,    67,     0,    64,    62,    72,
       0,     0,     0,    66,    74,    33,    35,    28,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   122,   -61,   107,     8,   -61,   -16,   -61,    96,
     -61,   130,   -60,    14,   -21,   100,    99,   -61,   -52,    42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    14,    25,     7,    15,    16,    31,
      32,    59,    60,    61,    26,    27,    39,    40,    62,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      71,    79,    36,    74,    75,    76,    42,    69,     6,    38,
      21,     9,    98,     6,    43,    22,    70,   102,   104,    34,
     107,   108,     8,    11,    17,    12,    30,    18,    19,    65,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   100,    44,    48,    49,    50,    51,
     132,    38,    37,    33,    30,    13,    55,     1,    95,   110,
      20,    66,    64,    23,    97,   127,    21,    56,    34,    81,
      57,   101,    45,    41,   102,    47,     2,    63,    72,    58,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,   128,    94,   105,    46,    28,    95,    21,    73,
      67,    96,     1,    97,    77,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    78,    94,   129,
     125,     2,    95,    29,   137,   138,   106,    10,    97,    35,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    68,    94,   135,   136,    24,    95,    82,    83,
      84,    85,   139,    97,    48,    49,    50,    51,     1,    52,
      53,    80,    54,     0,    55,    95,    99,     0,   134,     0,
       0,    97,     0,     0,     0,    56,     0,     2,    57,    84,
      85,     0,    23,    48,    49,    50,    51,    58,    52,    53,
       0,    54,     0,    55,    95,     0,    48,    49,    50,    51,
      97,     0,     0,     0,    56,     0,    55,    57,     0,     0,
       0,    23,     0,     0,     0,     0,    58,    56,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     0,    94,     0,     0,   109,    95,     0,     0,
       0,     0,     0,    97,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,     0,    94,     0,     0,
       0,    95,     0,     0,     0,     0,   126,    97,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
       0,    94,     0,     0,   130,    95,     0,     0,     0,     0,
       0,    97,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,     0,    94,     0,     0,   131,    95,
       0,     0,     0,     0,     0,    97,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,     0,    94,
       0,     0,     0,    95,   133,     0,     0,     0,     0,    97,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,     0,    94,     0,     0,     0,    95,     0,     0,
       0,     0,     0,    97,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,     0,     0,     0,     0,
       0,    95,    82,    83,    84,    85,     0,    97,    88,    89,
      90,    91,    92,    93,     0,     0,     0,     0,     0,    95,
       0,     0,     0,     0,     0,    97
};

static const yytype_int16 yycheck[] =
{
      52,    61,    23,    55,    56,    57,    27,    27,     0,    25,
      29,     0,    64,     5,    30,    34,    36,    69,    70,     3,
      72,    73,     3,     1,    31,     3,    18,    27,     1,     1,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,     1,     1,     3,     4,     5,     6,
     110,    67,    36,     4,    46,    33,    13,     7,    29,    80,
      33,    33,    25,    31,    35,     1,    29,    24,     3,     1,
      27,    28,    28,    32,   126,    30,    26,     1,    27,    36,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    28,    25,     1,    34,     1,    29,    29,    27,
      34,    33,     7,    35,     1,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    32,    25,     1,
       3,    26,    29,    28,     1,    10,    33,     5,    35,    22,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    46,    25,   130,   131,    16,    29,    12,    13,
      14,    15,   138,    35,     3,     4,     5,     6,     7,     8,
       9,    61,    11,    -1,    13,    29,    67,    -1,   126,    -1,
      -1,    35,    -1,    -1,    -1,    24,    -1,    26,    27,    14,
      15,    -1,    31,     3,     4,     5,     6,    36,     8,     9,
      -1,    11,    -1,    13,    29,    -1,     3,     4,     5,     6,
      35,    -1,    -1,    -1,    24,    -1,    13,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    36,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    28,    29,    -1,    -1,
      -1,    -1,    -1,    35,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    -1,
      -1,    29,    -1,    -1,    -1,    -1,    34,    35,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      -1,    25,    -1,    -1,    28,    29,    -1,    -1,    -1,    -1,
      -1,    35,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    35,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    35,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    35,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,
      -1,    29,    12,    13,    14,    15,    -1,    35,    18,    19,
      20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    26,    38,    39,    40,    42,    43,     3,     0,
      39,     1,     3,    33,    41,    44,    45,    31,    27,     1,
      33,    29,    34,    31,    48,    42,    51,    52,     1,    28,
      42,    46,    47,     4,     3,    41,    51,    36,    44,    53,
      54,    32,    51,    44,     1,    28,    34,    30,     3,     4,
       5,     6,     8,     9,    11,    13,    24,    27,    36,    48,
      49,    50,    55,     1,    25,     1,    33,    34,    46,    27,
      36,    55,    27,    27,    55,    55,    55,     1,    32,    49,
      52,     1,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    25,    29,    33,    35,    55,    53,
       1,    28,    55,    56,    55,     1,    33,    55,    55,    28,
      51,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,     3,    34,     1,    28,     1,
      28,    28,    49,    30,    56,    50,    50,     1,    10,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    40,
      41,    41,    42,    42,    43,    43,    44,    44,    45,    45,
      45,    45,    46,    46,    47,    48,    49,    49,    49,    50,
      50,    50,    50,    50,    50,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       3,     1,     1,     1,     5,     2,     1,     4,     4,     3,
       4,     3,     3,     1,     2,     4,     2,     0,     5,     2,
       1,     3,     3,     5,     7,     5,     2,     2,     0,     3,
       3,     1,     3,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     4,     3,     1,     1,
       1,     1,     4,     2,     3,     1
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
  case 2:
#line 32 "syntax.y"
                    {
        (yyval.node) = new_node("Program", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
        result = (yyval.node);
    }
#line 1496 "syntax.tab.c"
    break;

  case 3:
#line 36 "syntax.y"
                              {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ExtDefList", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1505 "syntax.tab.c"
    break;

  case 4:
#line 40 "syntax.y"
                {
        (yyval.node) = new_node(NULL, 0, NULL, NULL, NULL);
    }
#line 1513 "syntax.tab.c"
    break;

  case 5:
#line 43 "syntax.y"
                                  {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ExtDef", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1523 "syntax.tab.c"
    break;

  case 6:
#line 48 "syntax.y"
                     {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ExtDef", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1532 "syntax.tab.c"
    break;

  case 7:
#line 52 "syntax.y"
                              {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node); 
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ExtDef", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1542 "syntax.tab.c"
    break;

  case 8:
#line 57 "syntax.y"
                                 {
        log_err(MISSING_SEMI, (yyvsp[-1].node)->line_no, "missing semicolon ';'");
    }
#line 1550 "syntax.tab.c"
    break;

  case 9:
#line 60 "syntax.y"
                      {
        log_err(MISSING_SEMI, (yyvsp[-1].node)->line_no, "missing semicolon ';'");
    }
#line 1558 "syntax.tab.c"
    break;

  case 10:
#line 63 "syntax.y"
                                    {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node); 
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ExtDecList", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1568 "syntax.tab.c"
    break;

  case 11:
#line 68 "syntax.y"
             {
        (yyval.node) = new_node("ExtDecList", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1576 "syntax.tab.c"
    break;

  case 12:
#line 73 "syntax.y"
                {
        (yyval.node) = new_node("Specifier", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1584 "syntax.tab.c"
    break;

  case 13:
#line 76 "syntax.y"
                      {
        (yyval.node) = new_node("Specifier", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1592 "syntax.tab.c"
    break;

  case 14:
#line 79 "syntax.y"
                                         {
        (yyvsp[-4].node)->sibling = (yyvsp[-3].node); 
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("StructSpecifier", (yyvsp[-4].node)->line_no, NULL, (yyvsp[-4].node), NULL);
    }
#line 1604 "syntax.tab.c"
    break;

  case 15:
#line 86 "syntax.y"
                {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("StructSpecifier", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1613 "syntax.tab.c"
    break;

  case 16:
#line 92 "syntax.y"
           {
        (yyval.node) = new_node("VarDec", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1621 "syntax.tab.c"
    break;

  case 17:
#line 95 "syntax.y"
                       {
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("VarDec", (yyvsp[-3].node)->line_no, NULL, (yyvsp[-3].node), NULL);
    }
#line 1632 "syntax.tab.c"
    break;

  case 18:
#line 101 "syntax.y"
                         {
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("FunDec", (yyvsp[-3].node)->line_no, NULL, (yyvsp[-3].node), NULL);
    }
#line 1643 "syntax.tab.c"
    break;

  case 19:
#line 107 "syntax.y"
               {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("FunDec", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1653 "syntax.tab.c"
    break;

  case 20:
#line 112 "syntax.y"
                          {
        log_err(MISSING_CLOSING, (yyvsp[-1].node)->line_no, "missing closing symbol ')'");
    }
#line 1661 "syntax.tab.c"
    break;

  case 21:
#line 115 "syntax.y"
                  {
        log_err(MISSING_CLOSING, (yyvsp[-1].node)->line_no, "missing closing symbol ')'");
    }
#line 1669 "syntax.tab.c"
    break;

  case 22:
#line 118 "syntax.y"
                                {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("VarList", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1679 "syntax.tab.c"
    break;

  case 23:
#line 123 "syntax.y"
               {
        (yyval.node) = new_node("VarList", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1687 "syntax.tab.c"
    break;

  case 24:
#line 126 "syntax.y"
                           {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("ParamDec", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1696 "syntax.tab.c"
    break;

  case 25:
#line 132 "syntax.y"
                               {
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("CompSt", (yyvsp[-3].node)->line_no, NULL, (yyvsp[-3].node), NULL);
    }
#line 1707 "syntax.tab.c"
    break;

  case 26:
#line 138 "syntax.y"
                        {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("StmtList", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1716 "syntax.tab.c"
    break;

  case 27:
#line 142 "syntax.y"
                {
        (yyval.node) = new_node(NULL, 0, NULL, NULL, NULL);
    }
#line 1724 "syntax.tab.c"
    break;

  case 28:
#line 145 "syntax.y"
                                      {
        log_err(DEF_AFTER_STMT, (yyvsp[-3].node)->line_no, "def after stmt");
    }
#line 1732 "syntax.tab.c"
    break;

  case 29:
#line 148 "syntax.y"
               {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Stmt", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1741 "syntax.tab.c"
    break;

  case 30:
#line 152 "syntax.y"
             {
        (yyval.node) = new_node("Stmt", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1749 "syntax.tab.c"
    break;

  case 31:
#line 155 "syntax.y"
                      {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Stmt", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1759 "syntax.tab.c"
    break;

  case 32:
#line 160 "syntax.y"
                       {
        log_err(MISSING_SEMI, (yyvsp[-1].node)->line_no, "missing semicolon ';'");
    }
#line 1767 "syntax.tab.c"
    break;

  case 33:
#line 163 "syntax.y"
                                   {
        (yyvsp[-4].node)->sibling = (yyvsp[-3].node);
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Stmt", (yyvsp[-4].node)->line_no, NULL, (yyvsp[-4].node), NULL);
    }
#line 1779 "syntax.tab.c"
    break;

  case 34:
#line 170 "syntax.y"
                                  {
        (yyvsp[-6].node)->sibling = (yyvsp[-5].node);
        (yyvsp[-5].node)->sibling = (yyvsp[-4].node);
        (yyvsp[-4].node)->sibling = (yyvsp[-3].node);
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Stmt", (yyvsp[-6].node)->line_no, NULL, (yyvsp[-6].node), NULL);
    }
#line 1793 "syntax.tab.c"
    break;

  case 35:
#line 179 "syntax.y"
                           {
        (yyvsp[-4].node)->sibling = (yyvsp[-3].node);
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Stmt", (yyvsp[-4].node)->line_no, NULL, (yyvsp[-4].node), NULL);
    }
#line 1805 "syntax.tab.c"
    break;

  case 36:
#line 186 "syntax.y"
                {
        log_err(MISSING_SEMI, (yyvsp[-1].node)->line_no, "missing semicolon ';'");
    }
#line 1813 "syntax.tab.c"
    break;

  case 37:
#line 191 "syntax.y"
                     {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("DefList", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 1822 "syntax.tab.c"
    break;

  case 38:
#line 195 "syntax.y"
                {
        (yyval.node) = new_node(NULL, 0, NULL, NULL, NULL);
    }
#line 1830 "syntax.tab.c"
    break;

  case 39:
#line 198 "syntax.y"
                            {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Def", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1840 "syntax.tab.c"
    break;

  case 40:
#line 203 "syntax.y"
                              {
        log_err(MISSING_SEMI, (yyvsp[-1].node)->line_no, "missing semicolon ';'");
    }
#line 1848 "syntax.tab.c"
    break;

  case 41:
#line 206 "syntax.y"
             {
        (yyval.node) = new_node("DecList", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1856 "syntax.tab.c"
    break;

  case 42:
#line 209 "syntax.y"
                        {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("DecList", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1866 "syntax.tab.c"
    break;

  case 43:
#line 214 "syntax.y"
                    {
        log_err(LEXEME_ERROR, (yyvsp[-1].node)->line_no, (yyvsp[-1].node)->property);
    }
#line 1874 "syntax.tab.c"
    break;

  case 44:
#line 217 "syntax.y"
            {
        (yyval.node) = new_node("Dec", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 1882 "syntax.tab.c"
    break;

  case 45:
#line 220 "syntax.y"
                        {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Dec", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1892 "syntax.tab.c"
    break;

  case 46:
#line 227 "syntax.y"
                    {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1902 "syntax.tab.c"
    break;

  case 47:
#line 232 "syntax.y"
                  {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1912 "syntax.tab.c"
    break;

  case 48:
#line 237 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1922 "syntax.tab.c"
    break;

  case 49:
#line 242 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1932 "syntax.tab.c"
    break;

  case 50:
#line 247 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1942 "syntax.tab.c"
    break;

  case 51:
#line 252 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1952 "syntax.tab.c"
    break;

  case 52:
#line 257 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1962 "syntax.tab.c"
    break;

  case 53:
#line 262 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1972 "syntax.tab.c"
    break;

  case 54:
#line 267 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1982 "syntax.tab.c"
    break;

  case 55:
#line 272 "syntax.y"
                   {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 1992 "syntax.tab.c"
    break;

  case 56:
#line 277 "syntax.y"
                    {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2002 "syntax.tab.c"
    break;

  case 57:
#line 282 "syntax.y"
                  {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2012 "syntax.tab.c"
    break;

  case 58:
#line 287 "syntax.y"
                  {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2022 "syntax.tab.c"
    break;

  case 59:
#line 292 "syntax.y"
                {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2032 "syntax.tab.c"
    break;

  case 60:
#line 297 "syntax.y"
                {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 2041 "syntax.tab.c"
    break;

  case 61:
#line 301 "syntax.y"
              {
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-1].node)->line_no, NULL, (yyvsp[-1].node), NULL);
    }
#line 2050 "syntax.tab.c"
    break;

  case 62:
#line 305 "syntax.y"
                    {
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-3].node)->line_no, NULL, (yyvsp[-3].node), NULL);
    }
#line 2061 "syntax.tab.c"
    break;

  case 63:
#line 311 "syntax.y"
               {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2071 "syntax.tab.c"
    break;

  case 64:
#line 316 "syntax.y"
                       {
        log_err(MISSING_CLOSING, (yyvsp[-1].node)->line_no, "missing closing symbol ')'");
    }
#line 2079 "syntax.tab.c"
    break;

  case 65:
#line 319 "syntax.y"
                  {
        log_err(MISSING_CLOSING, (yyvsp[-1].node)->line_no, "missing closing symbol ')'");
    }
#line 2087 "syntax.tab.c"
    break;

  case 66:
#line 322 "syntax.y"
                    {
        (yyvsp[-3].node)->sibling = (yyvsp[-2].node);
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-3].node)->line_no, NULL, (yyvsp[-3].node), NULL);
    }
#line 2098 "syntax.tab.c"
    break;

  case 67:
#line 328 "syntax.y"
                 {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Exp", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2108 "syntax.tab.c"
    break;

  case 68:
#line 333 "syntax.y"
         {
        (yyval.node) = new_node("Exp", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 2116 "syntax.tab.c"
    break;

  case 69:
#line 336 "syntax.y"
          {
        (yyval.node) = new_node("Exp", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 2124 "syntax.tab.c"
    break;

  case 70:
#line 339 "syntax.y"
            {
        (yyval.node) = new_node("Exp", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 2132 "syntax.tab.c"
    break;

  case 71:
#line 342 "syntax.y"
           {
        (yyval.node) = new_node("Exp", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 2140 "syntax.tab.c"
    break;

  case 72:
#line 345 "syntax.y"
                           {
        const char *prefix = "illegal symbol ";
        const char *sym = (yyvsp[-2].node)->property ? (yyvsp[-2].node)->property : "";
        if (!strncmp(sym, prefix, strlen(prefix))) {
            sym += strlen(prefix);
        }
        char buf[64];
        snprintf(buf, sizeof(buf), "illegal operator '%s'", sym);
        log_err(ILLEGAL_OP, (yyvsp[-2].node)->line_no, buf);
    }
#line 2155 "syntax.tab.c"
    break;

  case 73:
#line 355 "syntax.y"
                    {
        log_err(LEXEME_ERROR, (yyvsp[-1].node)->line_no, (yyvsp[-1].node)->property);
    }
#line 2163 "syntax.tab.c"
    break;

  case 74:
#line 358 "syntax.y"
                     {
        (yyvsp[-2].node)->sibling = (yyvsp[-1].node);
        (yyvsp[-1].node)->sibling = (yyvsp[0].node);
        (yyval.node) = new_node("Args", (yyvsp[-2].node)->line_no, NULL, (yyvsp[-2].node), NULL);
    }
#line 2173 "syntax.tab.c"
    break;

  case 75:
#line 363 "syntax.y"
          {
        (yyval.node) = new_node("Args", (yyvsp[0].node)->line_no, NULL, (yyvsp[0].node), NULL);
    }
#line 2181 "syntax.tab.c"
    break;


#line 2185 "syntax.tab.c"

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
#line 366 "syntax.y"


void yyerror(const char *s) { /* fprintf(stderr, "%s\n", s); */ }

void log_err(char type, size_t line_no, const char *msg) {
    fprintf(stdout, "Error type %c at Line %lu: %s\n", type, line_no, msg);
    exit_code = 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        exit(1);
    }
    FILE *fin = fopen(argv[1], "rb"), *fout = stdout;
    if (!fin) {
        exit(1);
    }
    size_t len = strlen(argv[1]);
    if (!strcmp(argv[1] + len - 4, ".bpl")) {
        strcpy(argv[1] + len - 3, "out");
        fout = freopen(argv[1], "wb", stdout);
    }
    if (!fout) {
        exit(1);
    }
    yyin = fin;
    yyparse();
    if (!exit_code) {
        print_tree(stdout, result, 0);
    }
    empty_tree(result);
    if (result) {
        free(result);
        result = NULL;
    }
    return exit_code;
}
