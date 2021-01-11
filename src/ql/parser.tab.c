/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
/* Tokens.  */
#define DATABASE 258
#define DATABASES 259
#define TABLE 260
#define TABLES 261
#define SHOW 262
#define CREATE 263
#define DROP 264
#define USE 265
#define PRIMARY 266
#define KEY 267
#define NOT 268
#define SQLNULL 269
#define INSERT 270
#define INTO 271
#define VALUES 272
#define DELETE 273
#define FROM 274
#define WHERE 275
#define UPDATE 276
#define SET 277
#define SELECT 278
#define IS 279
#define TOKEN_INT 280
#define VARCHAR 281
#define DEFAULT 282
#define CONSTRAINT 283
#define CHANGE 284
#define ALTER 285
#define ADD 286
#define RENAME 287
#define DESC 288
#define INDEX 289
#define AND 290
#define DATE 291
#define FLOAT 292
#define FOREIGN 293
#define REFERENCES 294
#define ON 295
#define TO 296
#define EXIT 297
#define EQ 298
#define NE 299
#define LT 300
#define GT 301
#define LE 302
#define GE 303
#define IDENTIFIER 304
#define VALUE_INT 305
#define VALUE_FLOAT 306
#define VALUE_STRING 307




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 223 "parser.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  209

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      25,    28,    32,    36,    39,    42,    49,    53,    56,    62,
      68,    75,    82,    87,    96,   100,   110,   117,   123,   129,
     136,   143,   150,   162,   170,   187,   195,   197,   201,   204,
     209,   214,   221,   227,   238,   243,   248,   250,   252,   256,
     262,   264,   268,   270,   272,   274,   276,   280,   284,   289,
     291,   295,   297,   301,   303,   307,   309,   311,   313,   315,
     317,   319,   321,   323,   327,   333,   335,   337,   339,   343,
     345,   349,   351,   353,   355,   357,   359
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      60,     0,    -1,    -1,    60,    61,    -1,    62,    53,    -1,
      63,    53,    -1,    64,    53,    -1,    65,    53,    -1,    66,
      53,    -1,    42,    53,    -1,     7,     4,    -1,     8,     3,
      83,    -1,     9,     3,    83,    -1,    10,    83,    -1,     7,
       6,    -1,     8,     5,    84,    54,    67,    55,    -1,     9,
       5,    84,    -1,    33,    84,    -1,    15,    16,    84,    17,
      70,    -1,    18,    19,    84,    20,    74,    -1,    21,    84,
      22,    79,    20,    74,    -1,    23,    80,    19,    81,    20,
      74,    -1,    23,    80,    19,    81,    -1,     8,    34,    88,
      40,    84,    54,    82,    55,    -1,     9,    34,    88,    -1,
      30,     5,    84,    31,    34,    88,    54,    82,    55,    -1,
      30,     5,    84,     9,    34,    88,    -1,    30,     5,    84,
      31,    68,    -1,    30,     5,    84,     9,    85,    -1,    30,
       5,    84,    29,    85,    68,    -1,    30,     5,    84,    32,
      41,    84,    -1,    30,     5,    84,     9,    11,    12,    -1,
      30,     5,    84,    31,    28,    86,    11,    12,    54,    82,
      55,    -1,    30,     5,    84,     9,    11,    12,    86,    -1,
      30,     5,    84,    31,    28,    87,    38,    12,    54,    82,
      55,    39,    84,    54,    82,    55,    -1,    30,     5,    84,
       9,    38,    12,    87,    -1,    68,    -1,    67,    56,    68,
      -1,    85,    69,    -1,    85,    69,    13,    14,    -1,    85,
      69,    27,    72,    -1,    85,    69,    13,    14,    27,    72,
      -1,    11,    12,    54,    82,    55,    -1,    38,    12,    54,
      85,    55,    39,    84,    54,    85,    55,    -1,    25,    54,
      50,    55,    -1,    26,    54,    50,    55,    -1,    36,    -1,
      37,    -1,    54,    71,    55,    -1,    70,    56,    54,    71,
      55,    -1,    72,    -1,    71,    56,    72,    -1,    50,    -1,
      51,    -1,    52,    -1,    14,    -1,    75,    77,    78,    -1,
      75,    24,    14,    -1,    75,    24,    13,    14,    -1,    73,
      -1,    74,    35,    73,    -1,    85,    -1,    84,    57,    85,
      -1,    75,    -1,    76,    56,    75,    -1,    43,    -1,    44,
      -1,    47,    -1,    48,    -1,    45,    -1,    46,    -1,    72,
      -1,    75,    -1,    85,    43,    72,    -1,    79,    56,    85,
      43,    72,    -1,    58,    -1,    76,    -1,    84,    -1,    81,
      56,    84,    -1,    85,    -1,    82,    56,    85,    -1,    49,
      -1,    49,    -1,    49,    -1,    49,    -1,    49,    -1,    49,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
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

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "colName", "pkName", "fkName", "idxName", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    14,    15,    16,    17,    18,    19,    80,    81,
     111,    85,   117,   118,    86,    87,    88,    37,   128,   160,
      68,    38,    71,   150,    29,    39,    40,   139,   140,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   -65,
    -132,  -132,    46,   -90,    84,   -44,    -6,  -132,  -132,  -132,
    -132,  -132,  -132,  -131,    61,    -9,   -56,    69,    76,   -21
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -86
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

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 65 "parser.y"
    {
      cout << "exit db" << endl;
      qm->sm->closeDB();
      exit(0);
    ;}
    break;

  case 10:
#line 73 "parser.y"
    {qm->showDatabases();;}
    break;

  case 11:
#line 76 "parser.y"
    {
        qm->createDatabase((yyvsp[(3) - (3)].id));
      ;}
    break;

  case 12:
#line 79 "parser.y"
    {
      qm->dropDatabase((yyvsp[(3) - (3)].id));
    ;}
    break;

  case 13:
#line 82 "parser.y"
    {
      qm->useDatabase((yyvsp[(2) - (2)].id));
    ;}
    break;

  case 14:
#line 85 "parser.y"
    {qm->showTables();;}
    break;

  case 15:
#line 89 "parser.y"
    {
        qm->createTable((yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].fieldList));
      ;}
    break;

  case 16:
#line 92 "parser.y"
    {
        qm->dropTable((yyvsp[(3) - (3)].id));
    ;}
    break;

  case 17:
#line 95 "parser.y"
    {
        qm->descTable((yyvsp[(2) - (2)].id));
    ;}
    break;

  case 18:
#line 98 "parser.y"
    {
        qm->insertIntoTable((yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].valueLists));
    ;}
    break;

  case 19:
#line 101 "parser.y"
    {
        qm->deleteFromTable((yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].whereClauseList));
    ;}
    break;

  case 20:
#line 104 "parser.y"
    {
        qm->updateTable((yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].setClauseList), (yyvsp[(6) - (6)].whereClauseList));
    ;}
    break;

  case 21:
#line 108 "parser.y"
    {
        qm->selectFromTables((yyvsp[(2) - (6)].selector), (yyvsp[(4) - (6)].tableList), (yyvsp[(6) - (6)].whereClauseList));
      ;}
    break;

  case 22:
#line 112 "parser.y"
    {
        qm->selectFromTables((yyvsp[(2) - (4)].selector), (yyvsp[(4) - (4)].tableList));
      ;}
    break;

  case 23:
#line 118 "parser.y"
    {
        qm->createIndex((yyvsp[(5) - (8)].id), (yyvsp[(3) - (8)].id), (yyvsp[(7) - (8)].colList));
      ;}
    break;

  case 24:
#line 121 "parser.y"
    {
        qm->dropIndex((yyvsp[(3) - (3)].id));
    ;}
    break;

  case 25:
#line 124 "parser.y"
    {
      qm->alterAddIndex((yyvsp[(3) - (9)].id), (yyvsp[(6) - (9)].id), (yyvsp[(8) - (9)].colList));
    ;}
    break;

  case 26:
#line 127 "parser.y"
    {
      qm->alterDropIndex((yyvsp[(3) - (6)].id), (yyvsp[(6) - (6)].id));
    ;}
    break;

  case 27:
#line 133 "parser.y"
    {
        qm->alterAddfield();
        cout << "Not Supported" << endl;
      ;}
    break;

  case 28:
#line 137 "parser.y"
    {
      qm->alterDropCol();
      cout << "Not Supported" << endl;
    ;}
    break;

  case 29:
#line 141 "parser.y"
    {
      qm->alterChange();
      cout << "Not Supported" << endl;
    ;}
    break;

  case 30:
#line 145 "parser.y"
    {
      qm->alterRename((yyvsp[(3) - (6)].id), (yyvsp[(6) - (6)].id));
    ;}
    break;

  case 31:
#line 148 "parser.y"
    {
      qm->alterDropPrimaryKey((yyvsp[(3) - (6)].id), "", false);
    ;}
    break;

  case 32:
#line 151 "parser.y"
    {
      qm->alterAddPrimaryKey((yyvsp[(3) - (11)].id), (yyvsp[(6) - (11)].id), (yyvsp[(10) - (11)].colList));
    ;}
    break;

  case 33:
#line 154 "parser.y"
    {
      qm->alterDropPrimaryKey((yyvsp[(3) - (7)].id), (yyvsp[(7) - (7)].id), true);
    ;}
    break;

  case 34:
#line 157 "parser.y"
    {
      qm->alterAddForeignKey((yyvsp[(3) - (16)].id), (yyvsp[(6) - (16)].id), (yyvsp[(10) - (16)].colList), (yyvsp[(13) - (16)].id), (yyvsp[(15) - (16)].colList));
    ;}
    break;

  case 35:
#line 160 "parser.y"
    {
      qm->alterDropForeignKey((yyvsp[(3) - (7)].id), (yyvsp[(7) - (7)].id));
    ;}
    break;

  case 36:
#line 166 "parser.y"
    {(yyval.fieldList).push_back((yyvsp[(1) - (1)]._field));;}
    break;

  case 37:
#line 167 "parser.y"
    {(yyval.fieldList).push_back((yyvsp[(3) - (3)]._field));;}
    break;

  case 38:
#line 171 "parser.y"
    {
        (yyval._field).colName = (yyvsp[(1) - (2)].id);
        (yyval._field).type = (yyvsp[(2) - (2)]._type);
      ;}
    break;

  case 39:
#line 175 "parser.y"
    {
        (yyval._field).colName = (yyvsp[(1) - (4)].id);
        (yyval._field).type = (yyvsp[(2) - (4)]._type);
        (yyval._field).is_not_null = true;
    ;}
    break;

  case 40:
#line 180 "parser.y"
    {
        (yyval._field).colName = (yyvsp[(1) - (4)].id);
        (yyval._field).type = (yyvsp[(2) - (4)]._type);
    ;}
    break;

  case 41:
#line 184 "parser.y"
    {
        (yyval._field).colName = (yyvsp[(1) - (6)].id);
        (yyval._field).type = (yyvsp[(2) - (6)]._type);
        (yyval._field).is_not_null = true;
    ;}
    break;

  case 42:
#line 189 "parser.y"
    {
        (yyval._field).isPrimaryKey = true;
        (yyval._field).is_not_null = true;
        (yyval._field).colList = (yyvsp[(4) - (5)].colList);
    ;}
    break;

  case 43:
#line 194 "parser.y"
    {
        (yyval._field).isForeignKey = true;
        (yyval._field).colName = (yyvsp[(4) - (10)].id);
        (yyval._field).refTableName = (yyvsp[(7) - (10)].id);
        (yyval._field).refColName = (yyvsp[(9) - (10)].id); 
    ;}
    break;

  case 44:
#line 203 "parser.y"
    {
        (yyval._type).type = INTEGER_TYPE;
        (yyval._type).attrLen = 4;
      ;}
    break;

  case 45:
#line 207 "parser.y"
    {
        (yyval._type).type = STRING_TYPE;
        (yyval._type).attrLen = atoi((yyvsp[(3) - (4)].id).c_str());
    ;}
    break;

  case 46:
#line 211 "parser.y"
    {
        (yyval._type).type = STRING_TYPE;
        (yyval._type).attrLen = 10;
    ;}
    break;

  case 47:
#line 215 "parser.y"
    {
        (yyval._type).type = FLOAT_TYPE;
        (yyval._type).attrLen = 4;
    ;}
    break;

  case 48:
#line 222 "parser.y"
    {(yyval.valueLists).push_back((yyvsp[(2) - (3)].valueList));;}
    break;

  case 49:
#line 223 "parser.y"
    {(yyval.valueLists).push_back((yyvsp[(4) - (5)].valueList));;}
    break;

  case 50:
#line 227 "parser.y"
    {(yyval.valueList).push_back((yyvsp[(1) - (1)]._value));;}
    break;

  case 51:
#line 228 "parser.y"
    {(yyval.valueList).push_back((yyvsp[(3) - (3)]._value));;}
    break;

  case 52:
#line 232 "parser.y"
    {
        (yyval._value).valueType = INTEGER_TYPE; 
        (yyval._value).value_int = atoi((yyvsp[(1) - (1)].id).c_str());
        // printf("in %d\n", $$.value_int);
      ;}
    break;

  case 53:
#line 237 "parser.y"
    {
        (yyval._value).valueType = FLOAT_TYPE; 
        (yyval._value).value_float = (float)(atof((yyvsp[(1) - (1)].id).c_str()));
      ;}
    break;

  case 54:
#line 241 "parser.y"
    {
        (yyval._value).valueType = STRING_TYPE; 
        (yyval._value).value_string = (yyvsp[(1) - (1)].id);
      ;}
    break;

  case 55:
#line 245 "parser.y"
    {(yyval._value).value_null = true;;}
    break;

  case 56:
#line 249 "parser.y"
    {
        (yyval._whereClause).col = (yyvsp[(1) - (3)]._col);
        (yyval._whereClause).op = (yyvsp[(2) - (3)]._op);
        (yyval._whereClause).expr = (yyvsp[(3) - (3)]._expr);
      ;}
    break;

  case 57:
#line 254 "parser.y"
    {
        (yyval._whereClause).col = (yyvsp[(1) - (3)]._col);
        (yyval._whereClause).op = EQ_OP;
        (yyval._whereClause).expr.isValue = true;
        (yyval._whereClause).expr.value.value_null = true;
    ;}
    break;

  case 58:
#line 260 "parser.y"
    {
        (yyval._whereClause).col = (yyvsp[(1) - (4)]._col);
        (yyval._whereClause).op = NE_OP;
        (yyval._whereClause).expr.isValue = true;
        (yyval._whereClause).expr.value.value_null = true;
    ;}
    break;

  case 59:
#line 269 "parser.y"
    {
        (yyval.whereClauseList).push_back((yyvsp[(1) - (1)]._whereClause));
      ;}
    break;

  case 60:
#line 272 "parser.y"
    {
      (yyval.whereClauseList).push_back((yyvsp[(3) - (3)]._whereClause));
    ;}
    break;

  case 61:
#line 278 "parser.y"
    {
        (yyval._col).colName = (yyvsp[(1) - (1)].id);
        (yyval._col).hasTableName = false;
      ;}
    break;

  case 62:
#line 282 "parser.y"
    {
        (yyval._col).tableName = (yyvsp[(1) - (3)].id);
        (yyval._col).colName = (yyvsp[(3) - (3)].id);
        (yyval._col).hasTableName = true;
    ;}
    break;

  case 63:
#line 290 "parser.y"
    {
		  (yyval.colList).push_back((yyvsp[(1) - (1)]._col));
    ;}
    break;

  case 64:
#line 293 "parser.y"
    {
      (yyval.colList).push_back((yyvsp[(3) - (3)]._col));
  ;}
    break;

  case 65:
#line 298 "parser.y"
    {(yyval._op) = EQ_OP;;}
    break;

  case 66:
#line 298 "parser.y"
    {(yyval._op) = NE_OP;;}
    break;

  case 67:
#line 298 "parser.y"
    {(yyval._op) = LE_OP;;}
    break;

  case 68:
#line 298 "parser.y"
    {(yyval._op) = GE_OP;;}
    break;

  case 69:
#line 298 "parser.y"
    {(yyval._op) = LT_OP;;}
    break;

  case 70:
#line 298 "parser.y"
    {(yyval._op) = GT_OP;;}
    break;

  case 71:
#line 301 "parser.y"
    {(yyval._expr).isValue = true; (yyval._expr).value = (yyvsp[(1) - (1)]._value);;}
    break;

  case 72:
#line 302 "parser.y"
    {(yyval._expr).isValue = false; (yyval._expr).col = (yyvsp[(1) - (1)]._col);;}
    break;

  case 73:
#line 306 "parser.y"
    {
        SetClauseInfo temp;
        temp.colName = (yyvsp[(1) - (3)].id);
        temp.value = (yyvsp[(3) - (3)]._value);
        (yyval.setClauseList).push_back(temp);
      ;}
    break;

  case 74:
#line 312 "parser.y"
    {
        SetClauseInfo temp;
        temp.colName = (yyvsp[(3) - (5)].id);
        temp.value = (yyvsp[(5) - (5)]._value);
        (yyval.setClauseList).push_back(temp);
    ;}
    break;

  case 75:
#line 321 "parser.y"
    {(yyval.selector).isSelectAll = true;;}
    break;

  case 76:
#line 322 "parser.y"
    {(yyval.selector).isSelectAll = false; (yyval.selector).colList = (yyvsp[(1) - (1)].colList);;}
    break;

  case 77:
#line 328 "parser.y"
    {
		  TableInfo temp;
		  temp.tableName = (yyvsp[(1) - (1)].id);
		  (yyval.tableList).push_back(temp);
	  ;}
    break;

  case 78:
#line 333 "parser.y"
    {
		  TableInfo temp;
		  temp.tableName = (yyvsp[(3) - (3)].id);
		  (yyval.tableList).push_back(temp);
	;}
    break;

  case 79:
#line 341 "parser.y"
    {
		  ColInfo temp;
		  temp.colName = (yyvsp[(1) - (1)].id);
      temp.hasTableName = false;
		  (yyval.colList).push_back(temp);
		  // printf("push back %s\n", $1.c_str());
		;}
    break;

  case 80:
#line 348 "parser.y"
    {
		ColInfo temp;
		temp.colName = (yyvsp[(3) - (3)].id);
    temp.hasTableName = false;
		(yyval.colList).push_back(temp);
		// printf("push back %s\n", $3.c_str());
	;}
    break;

  case 81:
#line 357 "parser.y"
    {(yyval.id) = (yyvsp[(1) - (1)].id);;}
    break;

  case 82:
#line 359 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id);;}
    break;

  case 83:
#line 361 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id);;}
    break;

  case 84:
#line 363 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id);;}
    break;

  case 85:
#line 365 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id);;}
    break;

  case 86:
#line 367 "parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2146 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 370 "parser.y"


void yyerror(const char *s)
{
    printf("SYNTAX ERROR\n");
}
