/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

    #include <cstdio>
    #include "ql.h"
    #include "utils.h"
    // extern class QL_QueryManager;
    extern "C"
    {
        void yyerror(const char *s);
        extern int yylex(void);
    };
    extern QL_QueryManager* qm;

#line 79 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    DATABASE = 258,
    DATABASES = 259,
    TABLE = 260,
    TABLES = 261,
    SHOW = 262,
    CREATE = 263,
    DROP = 264,
    USE = 265,
    PRIMARY = 266,
    KEY = 267,
    NOT = 268,
    SQLNULL = 269,
    INSERT = 270,
    INTO = 271,
    VALUES = 272,
    DELETE = 273,
    FROM = 274,
    WHERE = 275,
    UPDATE = 276,
    SET = 277,
    SELECT = 278,
    IS = 279,
    TOKEN_INT = 280,
    VARCHAR = 281,
    DEFAULT = 282,
    CONSTRAINT = 283,
    CHANGE = 284,
    ALTER = 285,
    ADD = 286,
    RENAME = 287,
    DESC = 288,
    INDEX = 289,
    AND = 290,
    DATE = 291,
    FLOAT = 292,
    FOREIGN = 293,
    REFERENCES = 294,
    ON = 295,
    TO = 296,
    EXIT = 297,
    EQ = 298,
    NE = 299,
    LT = 300,
    GT = 301,
    LE = 302,
    GE = 303,
    IDENTIFIER = 304,
    VALUE_INT = 305,
    VALUE_FLOAT = 306,
    VALUE_STRING = 307
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 178 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   212

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  209

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,    55,    58,     2,    56,     2,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    53,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    52,    55,    57,    59,    61,    63,    65,
      73,    76,    79,    82,    85,    89,    92,    95,    98,   101,
     104,   107,   111,   118,   121,   124,   127,   133,   137,   141,
     145,   148,   151,   154,   157,   160,   166,   167,   171,   175,
     180,   184,   189,   194,   203,   207,   211,   215,   222,   223,
     227,   228,   232,   237,   241,   245,   249,   254,   260,   269,
     272,   278,   282,   290,   293,   298,   298,   298,   298,   298,
     298,   301,   302,   306,   312,   321,   322,   328,   333,   341,
     348,   357,   359,   361,   363,   365,   367
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATABASE", "DATABASES", "TABLE",
  "TABLES", "SHOW", "CREATE", "DROP", "USE", "PRIMARY", "KEY", "NOT",
  "SQLNULL", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "WHERE",
  "UPDATE", "SET", "SELECT", "IS", "TOKEN_INT", "VARCHAR", "DEFAULT",
  "CONSTRAINT", "CHANGE", "ALTER", "ADD", "RENAME", "DESC", "INDEX", "AND",
  "DATE", "FLOAT", "FOREIGN", "REFERENCES", "ON", "TO", "EXIT", "EQ", "NE",
  "LT", "GT", "LE", "GE", "IDENTIFIER", "VALUE_INT", "VALUE_FLOAT",
  "VALUE_STRING", "';'", "'('", "')'", "','", "'.'", "'*'", "$accept",
  "program", "stmt", "sysStmt", "dbStmt", "tbStmt", "idxStmt", "alterStmt",
  "fieldList", "field", "type", "valueLists", "valueList", "value",
  "whereClause", "whereClauseList", "col", "colList", "op", "expr",
  "setClause", "selector", "tableList", "columnList", "dbName", "tbName",
  "colName", "pkName", "fkName", "idxName", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    59,    40,    41,    44,    46,    42
};
# endif

#define YYPACT_NINF -132

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-132)))

#define YYTABLE_NINF -86

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -132,    95,  -132,   111,    65,    77,   -39,     7,    33,    32,
     -34,    80,    32,    37,  -132,    41,    53,    56,    66,    73,
    -132,  -132,   -39,    32,    72,   -39,    32,    72,  -132,  -132,
      32,    32,  -132,    92,    70,  -132,  -132,    75,   125,    89,
    -132,    32,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
      93,  -132,   109,  -132,  -132,  -132,   131,   137,   110,   112,
      32,   110,    60,    -2,    32,   104,   112,  -132,    -7,   117,
    -132,     6,  -132,  -132,     5,   110,    -3,   121,   151,   152,
     -28,  -132,    71,   113,    26,   114,  -132,   130,   108,   112,
     110,    26,   112,    32,   154,    72,   156,  -132,    -2,   120,
      72,  -132,    32,   118,   119,  -132,    -2,   122,   123,  -132,
    -132,    17,   110,  -132,  -132,  -132,  -132,     2,  -132,   124,
     112,    59,  -132,  -132,  -132,  -132,  -132,  -132,    15,   130,
     128,  -132,   130,  -132,   126,  -132,   132,  -132,   136,   168,
     142,   129,  -132,   110,   110,  -132,   134,   138,   172,    26,
      45,  -132,  -132,    26,    26,  -132,   173,  -132,  -132,  -132,
    -132,    26,  -132,  -132,  -132,  -132,   170,   177,   110,    68,
     135,   139,   140,   164,  -132,  -132,   110,  -132,    74,  -132,
    -132,   143,   144,    78,  -132,   153,  -132,  -132,    26,  -132,
    -132,   110,   110,  -132,    32,  -132,    83,    85,   145,  -132,
     157,   110,    32,   146,   148,  -132,   110,    87,  -132
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
      10,    14,     0,     0,     0,     0,     0,     0,    81,    13,
       0,     0,    82,     0,    83,    75,    63,    76,     0,     0,
      61,     0,    17,     9,     4,     5,     6,     7,     8,    11,
       0,    86,     0,    12,    16,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,     0,
      64,    22,    77,    62,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,    18,    59,    19,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,    27,     0,     0,     0,    15,     0,     0,     0,    46,
      47,    38,     0,    55,    52,    53,    54,     0,    50,     0,
       0,     0,    65,    66,    69,    70,    67,    68,     0,    20,
       0,    73,    21,    78,    31,    26,     0,    29,    84,     0,
       0,     0,    30,     0,     0,    37,     0,     0,     0,     0,
       0,    79,    48,     0,     0,    60,     0,    57,    71,    72,
      56,     0,    84,    33,    85,    35,     0,     0,     0,     0,
       0,     0,     0,    39,    40,    23,     0,    51,     0,    58,
      74,     0,     0,     0,    42,     0,    44,    45,     0,    80,
      49,     0,     0,    25,     0,    41,     0,     0,     0,    32,
       0,     0,     0,     0,     0,    43,     0,     0,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   -65,
    -132,  -132,    46,   -90,    84,   -44,    -6,  -132,  -132,  -132,
    -132,  -132,  -132,  -131,    61,    -9,   -56,    69,    76,   -21
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    14,    15,    16,    17,    18,    19,    80,    81,
     111,    85,   117,   118,    86,    87,    88,    37,   128,   160,
      68,    38,    71,   150,    29,    39,    40,   139,   140,    52
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,   131,    69,    42,    36,    73,    55,    82,    78,    78,
      28,   101,   169,    89,    50,    34,    94,    54,    97,    98,
      82,    56,    57,    30,    35,    99,    92,   105,   106,   113,
     148,   100,    62,   137,   130,    79,    79,   183,   158,    95,
     113,   145,    82,    96,   149,   129,    67,    67,   132,    90,
      82,    72,    31,    70,    67,    83,   151,   152,   153,   174,
     196,   197,    93,   177,    34,   114,   115,   116,    22,    74,
      23,   180,   156,   157,   135,   207,   114,   115,   116,   141,
      25,    32,    26,    49,   133,    41,    53,   151,   170,    75,
      43,    76,    77,   142,    44,     2,   107,   108,   195,    24,
     175,   176,     3,     4,     5,     6,    45,   109,   110,    46,
       7,    27,   151,     8,    58,    20,     9,    21,    10,    47,
     189,    51,   159,   184,   176,    11,    48,   -82,    12,   190,
     153,    59,   121,   193,   176,   151,   151,    13,   199,   176,
     200,   176,   208,   176,    60,   203,    61,    63,    65,    64,
     151,   122,   123,   124,   125,   126,   127,    66,    84,    67,
      91,    34,   102,   103,   104,   120,   134,   112,   136,   138,
     119,   161,   143,   144,   -85,   162,   146,   147,   154,   166,
     167,   164,   181,   168,   171,   198,   173,   179,   172,   182,
     185,   188,   194,   204,   186,   187,   202,   191,   192,   201,
     178,   205,   206,   163,   155,     0,     0,     0,     0,     0,
       0,     0,   165
};

static const yytype_int16 yycheck[] =
{
       9,    91,    58,    12,    10,    61,    27,    63,    11,    11,
      49,    76,   143,    20,    23,    49,    11,    26,    74,    75,
      76,    30,    31,    16,    58,    28,    20,    55,    56,    14,
      13,    34,    41,    98,    90,    38,    38,   168,   128,    34,
      14,   106,    98,    38,    27,    89,    49,    49,    92,    56,
     106,    60,    19,    59,    49,    64,   112,    55,    56,   149,
     191,   192,    56,   153,    49,    50,    51,    52,     3,     9,
       5,   161,    13,    14,    95,   206,    50,    51,    52,   100,
       3,    49,     5,    22,    93,     5,    25,   143,   144,    29,
      53,    31,    32,   102,    53,     0,    25,    26,   188,    34,
      55,    56,     7,     8,     9,    10,    53,    36,    37,    53,
      15,    34,   168,    18,    22,     4,    21,     6,    23,    53,
     176,    49,   128,    55,    56,    30,    53,    57,    33,    55,
      56,    56,    24,    55,    56,   191,   192,    42,    55,    56,
      55,    56,    55,    56,    19,   201,    57,    54,    17,    40,
     206,    43,    44,    45,    46,    47,    48,    20,    54,    49,
      43,    49,    41,    12,    12,    35,    12,    54,    12,    49,
      56,    43,    54,    54,    38,    49,    54,    54,    54,    11,
      38,    49,    12,    54,    50,   194,    14,    14,    50,    12,
      55,    27,    39,   202,    55,    55,    39,    54,    54,    54,
     154,    55,    54,   134,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   136
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    60,     0,     7,     8,     9,    10,    15,    18,    21,
      23,    30,    33,    42,    61,    62,    63,    64,    65,    66,
       4,     6,     3,     5,    34,     3,     5,    34,    49,    83,
      16,    19,    49,    84,    49,    58,    75,    76,    80,    84,
      85,     5,    84,    53,    53,    53,    53,    53,    53,    83,
      84,    49,    88,    83,    84,    88,    84,    84,    22,    56,
      19,    57,    84,    54,    40,    17,    20,    49,    79,    85,
      75,    81,    84,    85,     9,    29,    31,    32,    11,    38,
      67,    68,    85,    84,    54,    70,    73,    74,    75,    20,
      56,    43,    20,    56,    11,    34,    38,    85,    85,    28,
      34,    68,    41,    12,    12,    55,    56,    25,    26,    36,
      37,    69,    54,    14,    50,    51,    52,    71,    72,    56,
      35,    24,    43,    44,    45,    46,    47,    48,    77,    74,
      85,    72,    74,    84,    12,    88,    12,    68,    49,    86,
      87,    88,    84,    54,    54,    68,    54,    54,    13,    27,
      82,    85,    55,    56,    54,    73,    13,    14,    72,    75,
      78,    43,    49,    86,    49,    87,    11,    38,    54,    82,
      85,    50,    50,    14,    72,    55,    56,    72,    71,    14,
      72,    12,    12,    82,    55,    55,    55,    55,    27,    85,
      55,    54,    54,    55,    39,    72,    82,    82,    84,    55,
      55,    54,    39,    85,    84,    55,    54,    82,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      62,    63,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    65,    65,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    69,    69,    69,    69,    70,    70,
      71,    71,    72,    72,    72,    72,    73,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    77,    77,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    84,    85,    86,    87,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     3,     2,     2,     6,     3,     2,     5,     5,
       6,     6,     4,     8,     3,     9,     6,     5,     5,     6,
       6,     6,    11,     7,    16,     7,     1,     3,     2,     4,
       4,     6,     5,    10,     4,     4,     1,     1,     3,     5,
       1,     3,     1,     1,     1,     1,     3,     3,     4,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     5,     1,     1,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 9:
#line 65 "parser.y" /* yacc.c:1646  */
    {
      cout << "exit db" << endl;
      qm->sm->closeDB();
      exit(0);
    }
#line 1398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 73 "parser.y" /* yacc.c:1646  */
    {qm->showDatabases();}
#line 1404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 76 "parser.y" /* yacc.c:1646  */
    {
        qm->createDatabase((yyvsp[0].id));
      }
#line 1412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 79 "parser.y" /* yacc.c:1646  */
    {
      qm->dropDatabase((yyvsp[0].id));
    }
#line 1420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "parser.y" /* yacc.c:1646  */
    {
      qm->useDatabase((yyvsp[0].id));
    }
#line 1428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 85 "parser.y" /* yacc.c:1646  */
    {qm->showTables();}
#line 1434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 89 "parser.y" /* yacc.c:1646  */
    {
        qm->createTable((yyvsp[-3].id), (yyvsp[-1].fieldList));
      }
#line 1442 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 92 "parser.y" /* yacc.c:1646  */
    {
        qm->dropTable((yyvsp[0].id));
    }
#line 1450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 95 "parser.y" /* yacc.c:1646  */
    {
        qm->descTable((yyvsp[0].id));
    }
#line 1458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 98 "parser.y" /* yacc.c:1646  */
    {
        qm->insertIntoTable((yyvsp[-2].id), (yyvsp[0].valueLists));
    }
#line 1466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 101 "parser.y" /* yacc.c:1646  */
    {
        qm->deleteFromTable((yyvsp[-2].id), (yyvsp[0].whereClauseList));
    }
#line 1474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 104 "parser.y" /* yacc.c:1646  */
    {
        qm->updateTable((yyvsp[-4].id), (yyvsp[-2].setClauseList), (yyvsp[0].whereClauseList));
    }
#line 1482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 108 "parser.y" /* yacc.c:1646  */
    {
        qm->selectFromTables((yyvsp[-4].selector), (yyvsp[-2].tableList), (yyvsp[0].whereClauseList));
      }
#line 1490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 112 "parser.y" /* yacc.c:1646  */
    {
        qm->selectFromTables((yyvsp[-2].selector), (yyvsp[0].tableList));
      }
#line 1498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 118 "parser.y" /* yacc.c:1646  */
    {
        qm->createIndex((yyvsp[-3].id), (yyvsp[-5].id), (yyvsp[-1].colList));
      }
#line 1506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 121 "parser.y" /* yacc.c:1646  */
    {
        qm->dropIndex((yyvsp[0].id));
    }
#line 1514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 124 "parser.y" /* yacc.c:1646  */
    {
      qm->alterAddIndex((yyvsp[-6].id), (yyvsp[-3].id), (yyvsp[-1].colList));
    }
#line 1522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 127 "parser.y" /* yacc.c:1646  */
    {
      qm->alterDropIndex((yyvsp[-3].id), (yyvsp[0].id));
    }
#line 1530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 133 "parser.y" /* yacc.c:1646  */
    {
        qm->alterAddfield();
        cout << "Not Supported" << endl;
      }
#line 1539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 137 "parser.y" /* yacc.c:1646  */
    {
      qm->alterDropCol();
      cout << "Not Supported" << endl;
    }
#line 1548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 141 "parser.y" /* yacc.c:1646  */
    {
      qm->alterChange();
      cout << "Not Supported" << endl;
    }
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 145 "parser.y" /* yacc.c:1646  */
    {
      qm->alterRename((yyvsp[-3].id), (yyvsp[0].id));
    }
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 148 "parser.y" /* yacc.c:1646  */
    {
      qm->alterDropPrimaryKey((yyvsp[-3].id), "", false);
    }
#line 1573 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 151 "parser.y" /* yacc.c:1646  */
    {
      qm->alterAddPrimaryKey((yyvsp[-8].id), (yyvsp[-5].id), (yyvsp[-1].colList));
    }
#line 1581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 154 "parser.y" /* yacc.c:1646  */
    {
      qm->alterDropPrimaryKey((yyvsp[-4].id), (yyvsp[0].id), true);
    }
#line 1589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 157 "parser.y" /* yacc.c:1646  */
    {
      qm->alterAddForeignKey((yyvsp[-13].id), (yyvsp[-10].id), (yyvsp[-6].colList), (yyvsp[-3].id), (yyvsp[-1].colList));
    }
#line 1597 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 160 "parser.y" /* yacc.c:1646  */
    {
      qm->alterDropForeignKey((yyvsp[-4].id), (yyvsp[0].id));
    }
#line 1605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 166 "parser.y" /* yacc.c:1646  */
    {(yyval.fieldList).push_back((yyvsp[0]._field));}
#line 1611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 167 "parser.y" /* yacc.c:1646  */
    {(yyval.fieldList).push_back((yyvsp[0]._field));}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 171 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).colName = (yyvsp[-1].id);
        (yyval._field).type = (yyvsp[0]._type);
      }
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 175 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).colName = (yyvsp[-3].id);
        (yyval._field).type = (yyvsp[-2]._type);
        (yyval._field).is_not_null = true;
    }
#line 1636 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 180 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).colName = (yyvsp[-3].id);
        (yyval._field).type = (yyvsp[-2]._type);
    }
#line 1645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 184 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).colName = (yyvsp[-5].id);
        (yyval._field).type = (yyvsp[-4]._type);
        (yyval._field).is_not_null = true;
    }
#line 1655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 189 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).isPrimaryKey = true;
        (yyval._field).is_not_null = true;
        (yyval._field).colList = (yyvsp[-1].colList);
    }
#line 1665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 194 "parser.y" /* yacc.c:1646  */
    {
        (yyval._field).isForeignKey = true;
        (yyval._field).colName = (yyvsp[-6].id);
        (yyval._field).refTableName = (yyvsp[-3].id);
        (yyval._field).refColName = (yyvsp[-1].id); 
    }
#line 1676 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 203 "parser.y" /* yacc.c:1646  */
    {
        (yyval._type).type = INTEGER_TYPE;
        (yyval._type).attrLen = 4;
      }
#line 1685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 207 "parser.y" /* yacc.c:1646  */
    {
        (yyval._type).type = STRING_TYPE;
        (yyval._type).attrLen = atoi((yyvsp[-1].id).c_str());
    }
#line 1694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 211 "parser.y" /* yacc.c:1646  */
    {
        (yyval._type).type = STRING_TYPE;
        (yyval._type).attrLen = 10;
    }
#line 1703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 215 "parser.y" /* yacc.c:1646  */
    {
        (yyval._type).type = FLOAT_TYPE;
        (yyval._type).attrLen = 4;
    }
#line 1712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 222 "parser.y" /* yacc.c:1646  */
    {(yyval.valueLists).push_back((yyvsp[-1].valueList));}
#line 1718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 223 "parser.y" /* yacc.c:1646  */
    {(yyval.valueLists).push_back((yyvsp[-1].valueList));}
#line 1724 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 227 "parser.y" /* yacc.c:1646  */
    {(yyval.valueList).push_back((yyvsp[0]._value));}
#line 1730 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 228 "parser.y" /* yacc.c:1646  */
    {(yyval.valueList).push_back((yyvsp[0]._value));}
#line 1736 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 232 "parser.y" /* yacc.c:1646  */
    {
        (yyval._value).valueType = INTEGER_TYPE; 
        (yyval._value).value_int = atoi((yyvsp[0].id).c_str());
        // printf("in %d\n", $$.value_int);
      }
#line 1746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 237 "parser.y" /* yacc.c:1646  */
    {
        (yyval._value).valueType = FLOAT_TYPE; 
        (yyval._value).value_float = (float)(atof((yyvsp[0].id).c_str()));
      }
#line 1755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 241 "parser.y" /* yacc.c:1646  */
    {
        (yyval._value).valueType = STRING_TYPE; 
        (yyval._value).value_string = (yyvsp[0].id);
      }
#line 1764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 245 "parser.y" /* yacc.c:1646  */
    {(yyval._value).value_null = true;}
#line 1770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 249 "parser.y" /* yacc.c:1646  */
    {
        (yyval._whereClause).col = (yyvsp[-2]._col);
        (yyval._whereClause).op = (yyvsp[-1]._op);
        (yyval._whereClause).expr = (yyvsp[0]._expr);
      }
#line 1780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 254 "parser.y" /* yacc.c:1646  */
    {
        (yyval._whereClause).col = (yyvsp[-2]._col);
        (yyval._whereClause).op = EQ_OP;
        (yyval._whereClause).expr.isValue = true;
        (yyval._whereClause).expr.value.value_null = true;
    }
#line 1791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 260 "parser.y" /* yacc.c:1646  */
    {
        (yyval._whereClause).col = (yyvsp[-3]._col);
        (yyval._whereClause).op = NE_OP;
        (yyval._whereClause).expr.isValue = true;
        (yyval._whereClause).expr.value.value_null = true;
    }
#line 1802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 269 "parser.y" /* yacc.c:1646  */
    {
        (yyval.whereClauseList).push_back((yyvsp[0]._whereClause));
      }
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 272 "parser.y" /* yacc.c:1646  */
    {
      (yyval.whereClauseList).push_back((yyvsp[0]._whereClause));
    }
#line 1818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 278 "parser.y" /* yacc.c:1646  */
    {
        (yyval._col).colName = (yyvsp[0].id);
        (yyval._col).hasTableName = false;
      }
#line 1827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 282 "parser.y" /* yacc.c:1646  */
    {
        (yyval._col).tableName = (yyvsp[-2].id);
        (yyval._col).colName = (yyvsp[0].id);
        (yyval._col).hasTableName = true;
    }
#line 1837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 290 "parser.y" /* yacc.c:1646  */
    {
		  (yyval.colList).push_back((yyvsp[0]._col));
    }
#line 1845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 293 "parser.y" /* yacc.c:1646  */
    {
      (yyval.colList).push_back((yyvsp[0]._col));
  }
#line 1853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = EQ_OP;}
#line 1859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = NE_OP;}
#line 1865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = LE_OP;}
#line 1871 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = GE_OP;}
#line 1877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = LT_OP;}
#line 1883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 298 "parser.y" /* yacc.c:1646  */
    {(yyval._op) = GT_OP;}
#line 1889 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 301 "parser.y" /* yacc.c:1646  */
    {(yyval._expr).isValue = true; (yyval._expr).value = (yyvsp[0]._value);}
#line 1895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 302 "parser.y" /* yacc.c:1646  */
    {(yyval._expr).isValue = false; (yyval._expr).col = (yyvsp[0]._col);}
#line 1901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 306 "parser.y" /* yacc.c:1646  */
    {
        SetClauseInfo temp;
        temp.colName = (yyvsp[-2].id);
        temp.value = (yyvsp[0]._value);
        (yyval.setClauseList).push_back(temp);
      }
#line 1912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 312 "parser.y" /* yacc.c:1646  */
    {
        SetClauseInfo temp;
        temp.colName = (yyvsp[-2].id);
        temp.value = (yyvsp[0]._value);
        (yyval.setClauseList).push_back(temp);
    }
#line 1923 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 321 "parser.y" /* yacc.c:1646  */
    {(yyval.selector).isSelectAll = true;}
#line 1929 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 322 "parser.y" /* yacc.c:1646  */
    {(yyval.selector).isSelectAll = false; (yyval.selector).colList = (yyvsp[0].colList);}
#line 1935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 328 "parser.y" /* yacc.c:1646  */
    {
		  TableInfo temp;
		  temp.tableName = (yyvsp[0].id);
		  (yyval.tableList).push_back(temp);
	  }
#line 1945 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 333 "parser.y" /* yacc.c:1646  */
    {
		  TableInfo temp;
		  temp.tableName = (yyvsp[0].id);
		  (yyval.tableList).push_back(temp);
	}
#line 1955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 341 "parser.y" /* yacc.c:1646  */
    {
		  ColInfo temp;
		  temp.colName = (yyvsp[0].id);
      temp.hasTableName = false;
		  (yyval.colList).push_back(temp);
		  // printf("push back %s\n", $1.c_str());
		}
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 348 "parser.y" /* yacc.c:1646  */
    {
		ColInfo temp;
		temp.colName = (yyvsp[0].id);
    temp.hasTableName = false;
		(yyval.colList).push_back(temp);
		// printf("push back %s\n", $3.c_str());
	}
#line 1979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 357 "parser.y" /* yacc.c:1646  */
    {(yyval.id) = (yyvsp[0].id);}
#line 1985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 359 "parser.y" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id);}
#line 1991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 361 "parser.y" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id);}
#line 1997 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 363 "parser.y" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id);}
#line 2003 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 365 "parser.y" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id);}
#line 2009 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 367 "parser.y" /* yacc.c:1646  */
    { (yyval.id) = (yyvsp[0].id); }
#line 2015 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2019 "parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 370 "parser.y" /* yacc.c:1906  */


void yyerror(const char *s)
{
    printf("yy err\n");
}
