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
#line 1 "lab9.y" /* yacc.c:339  */

/*	
	Brady Scaggari Feb 27. 2024	LAB 6
	Implemented next connected for Param list local decls, statement list, 
	declaration list, and arg list.

	added node typings for the nonTerminals on lines 51,52,53 all of these nonterminals either create a node or have a reference to a created node. 

	Yacc has tokens from lex. These include things like operators, conditional operators. Relational operators etc. +,-,/,*,%,==, <=... etc.

	Type specifier is given a d_type from ast.h enum AST_MY_DATA_TYPE this is either VOID or INT type. 

	This program takes the token generated grammar from lex and uses NonTerminals to create a Abstract Syntax Tree. This is used for giving direction to an unambiguous language or grammar
	This program is LR(1) grammar for it has left recursion. The program is top down, but parses from the most bottom nonterminal upwards. The start of every language will always have declarations 
	these two declarations are called variable declarations and function declarations. Within each function/statement there is a compound statement. Compound statements have local declarations 
	these local declarations are designed to give a local scope within our AST. This is why compound statements are not next connected but, local declarations are next connected. 

	A statement list is also next connected. this ensures that our expression,compute are given a scope within each statmenet. we next connect the statment list so we can have multiple
	statments within a function or program, any expressions within each statmenet are either s1 connected and or s2 connected with if statement being unique for the conditon of there
	being an else statement, in case of this we s2->s1 connect the else statement.   

*/


/*begin specs*/
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "ast.h"
#include "emit.h"
#include "symtable.h"

ASTnode *PROGRAM;

int yylex();
extern int myDebug;
extern int lineCount;

int LEVEL = 0; // global var for levels
int OFFSET = 0; // global var for accumulating runtime spaces
int GOFFSET = 0; // glbal variable for accumulation of global offset
int maxoffset = 0; // largest off set needed for print

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("YACC PARSE ERROR: %s on line %d\n", s, lineCount);
}


#line 118 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    T_NUM = 258,
    T_ID = 259,
    T_STRING = 260,
    T_INT = 261,
    T_VOID = 262,
    T_READ = 263,
    T_RETURN = 264,
    T_WRITE = 265,
    T_WHILE = 266,
    T_IF = 267,
    T_ELSE = 268,
    T_LT = 269,
    T_GT = 270,
    T_EQ = 271,
    T_LE = 272,
    T_GE = 273,
    T_NE = 274,
    T_DIV = 275,
    T_MULT = 276,
    T_ADD = 277,
    T_SUB = 278,
    T_MOD = 279
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_ID 259
#define T_STRING 260
#define T_INT 261
#define T_VOID 262
#define T_READ 263
#define T_RETURN 264
#define T_WRITE 265
#define T_WHILE 266
#define T_IF 267
#define T_ELSE 268
#define T_LT 269
#define T_GT 270
#define T_EQ 271
#define T_LE 272
#define T_GE 273
#define T_NE 274
#define T_DIV 275
#define T_MULT 276
#define T_ADD 277
#define T_SUB 278
#define T_MOD 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "lab9.y" /* yacc.c:355  */

	int value; 
	char * string;
    ASTnode *node;
	enum AST_MY_DATA_TYPE d_type;
	enum AST_OPERATORS operator;

#line 214 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   118

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

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
      29,    30,     2,     2,    28,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    26,     2,    27,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    78,    78,    82,    86,    93,    99,   105,   134,   137,
     143,   149,   158,   159,   163,   178,   162,   196,   200,   206,
     210,   217,   231,   247,   247,   260,   267,   273,   276,   283,
     284,   285,   286,   287,   288,   289,   290,   293,   299,   305,
     313,   324,   332,   338,   343,   350,   356,   364,   381,   405,
     427,   430,   431,   447,   448,   449,   450,   451,   452,   455,
     459,   476,   480,   486,   490,   508,   512,   516,   522,   526,
     532,   536,   540,   558,   587,   592,   597,   608
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUM", "T_ID", "T_STRING", "T_INT",
  "T_VOID", "T_READ", "T_RETURN", "T_WRITE", "T_WHILE", "T_IF", "T_ELSE",
  "T_LT", "T_GT", "T_EQ", "T_LE", "T_GE", "T_NE", "T_DIV", "T_MULT",
  "T_ADD", "T_SUB", "T_MOD", "';'", "'['", "']'", "','", "'('", "')'",
  "'{'", "'}'", "'='", "$accept", "Program", "Declaration_List",
  "Declaration", "Var_Declaration", "Var_List", "Type_Specifier",
  "Fun_Declaration", "$@1", "$@2", "Params", "Param_List", "Param",
  "Compound_Statement", "$@3", "Local_Declarations", "Statement_List",
  "Statement", "Expression_Statement", "Selection_Statement",
  "Iteration_Statement", "Return_Statement", "Read_Statement",
  "Write_Statement", "Assignment_Statement", "Var", "Expression",
  "Simple_Expression", "Relop", "Additive_Expression", "Addop", "Term",
  "Multop", "Factor", "Call", "Args", "Arg_List", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    59,    91,    93,    44,    40,
      41,   123,   125,    61
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       6,   -53,   -53,    33,   -53,     6,   -53,     2,   -53,   -53,
     -53,    48,    12,    36,    43,    26,   -53,    35,    54,   -53,
      45,    38,    51,    71,    53,   -53,    59,    43,    62,   -53,
       6,   -53,    64,    58,   -53,   -53,   -53,   -53,     6,     6,
      43,     7,   -53,   -53,   -21,    86,    17,    40,    65,    66,
      25,   -53,    25,   -53,    60,     7,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,    67,    68,   -53,    42,     3,   -53,   -53,
      25,    25,    70,    72,   -53,   -53,    73,    74,    76,    25,
      25,   -53,    75,   -53,   -53,    25,   -53,   -53,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,    25,    25,   -53,   -53,   -53,
      25,    77,    78,    79,   -53,   -53,   -53,   -53,   -53,    80,
      81,   -53,    82,    63,     3,   -53,   -53,    25,   -53,     7,
       7,   -53,   -53,   -53,    89,     7,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    12,    13,     0,     2,     3,     5,     0,     6,     1,
       4,     8,     0,     0,     0,     0,     7,     0,     8,    10,
       0,     9,    13,     0,     0,    18,    19,     0,    21,    15,
       0,    11,     0,     0,    20,    22,    23,    16,    26,    26,
       0,    27,    25,    69,    48,     0,     0,     0,     0,     0,
       0,    38,     0,    31,     0,    27,    32,    33,    36,    34,
      29,    30,    35,    70,     0,    50,    51,    59,    63,    71,
       0,    75,    48,     0,    43,    70,     0,     0,     0,     0,
       0,    72,     0,    24,    28,     0,    37,    54,    55,    57,
      56,    53,    58,    61,    62,     0,     0,    66,    65,    67,
       0,     0,    76,     0,    74,    44,    42,    46,    45,     0,
       0,    68,     0,    52,    60,    64,    49,     0,    73,     0,
       0,    47,    77,    41,    39,     0,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -53,   -53,    98,   -53,    32,    -5,    11,   -53,   -53,   -53,
     -53,    83,   -53,    84,   -53,    69,    57,   -52,   -53,   -53,
     -53,   -53,   -53,   -53,   -53,   -41,   -45,    29,   -53,    20,
     -53,    22,   -53,   -47,   -53,   -53,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,     7,     8,    15,    33,
      24,    25,    26,    53,    38,    41,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    75,    64,    65,    95,    66,
      96,    67,   100,    68,    69,   103,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      63,    76,    78,    81,    73,    70,    11,    82,    71,    19,
      43,    44,     1,     2,    63,    45,    46,    47,    48,    49,
      43,    44,    31,    97,    98,   101,   102,    99,    43,    44,
      50,    23,    51,     9,   109,   110,    52,    16,    36,    17,
      50,    23,    74,    43,    44,    77,    52,    18,    50,    40,
      40,     1,    22,   115,    52,    20,    87,    88,    89,    90,
      91,    92,    21,    50,    93,    94,    27,   123,   124,    52,
      39,    39,   102,   126,    13,    28,    14,   -14,    63,    63,
      13,   -17,    14,    29,    63,    93,    94,    30,    32,    36,
      72,    35,    83,    86,    79,    80,    70,   105,   106,   107,
      85,   108,   125,    10,   116,   111,   117,   121,    42,   118,
     119,   120,    84,    34,   112,   113,   122,    37,   114
};

static const yytype_uint8 yycheck[] =
{
      41,    46,    47,    50,    45,    26,     4,    52,    29,    14,
       3,     4,     6,     7,    55,     8,     9,    10,    11,    12,
       3,     4,    27,    20,    21,    70,    71,    24,     3,     4,
      23,    20,    25,     0,    79,    80,    29,    25,    31,     3,
      23,    30,    25,     3,     4,     5,    29,     4,    23,    38,
      39,     6,     7,   100,    29,    29,    14,    15,    16,    17,
      18,    19,    27,    23,    22,    23,    28,   119,   120,    29,
      38,    39,   117,   125,    26,     4,    28,    29,   119,   120,
      26,    30,    28,    30,   125,    22,    23,    28,    26,    31,
       4,    27,    32,    25,    29,    29,    26,    25,    25,    25,
      33,    25,    13,     5,    27,    30,    28,    25,    39,    30,
      30,    30,    55,    30,    85,    95,   117,    33,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    35,    36,    37,    38,    40,    41,     0,
      36,     4,    39,    26,    28,    42,    25,     3,     4,    39,
      29,    27,     7,    40,    44,    45,    46,    28,     4,    30,
      28,    39,    26,    43,    45,    27,    31,    47,    48,    38,
      40,    49,    49,     3,     4,     8,     9,    10,    11,    12,
      23,    25,    29,    47,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    63,    65,    67,    68,
      26,    29,     4,    59,    25,    59,    60,     5,    60,    29,
      29,    67,    60,    32,    50,    33,    25,    14,    15,    16,
      17,    18,    19,    22,    23,    62,    64,    20,    21,    24,
      66,    60,    60,    69,    70,    25,    25,    25,    25,    60,
      60,    30,    61,    63,    65,    67,    27,    28,    30,    30,
      30,    25,    70,    51,    51,    13,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    38,    39,    39,
      39,    39,    40,    40,    42,    43,    41,    44,    44,    45,
      45,    46,    46,    48,    47,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    57,    57,    58,    59,    59,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    67,    68,    69,    69,    70,    70
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     4,
       3,     6,     1,     1,     0,     0,     8,     1,     1,     1,
       3,     2,     4,     0,     5,     2,     0,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     5,
       7,     5,     3,     2,     3,     3,     3,     4,     1,     4,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1,     2,     4,     1,     0,     1,     3
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
        case 2:
#line 78 "lab9.y" /* yacc.c:1646  */
    {PROGRAM = (yyvsp[0].node); }
#line 1397 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 83 "lab9.y" /* yacc.c:1646  */
    {	
						(yyval.node) = (yyvsp[0].node);
					}
#line 1405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 87 "lab9.y" /* yacc.c:1646  */
    {
                        (yyval.node) = (yyvsp[-1].node);
                        (yyval.node) ->next = (yyvsp[0].node); // next connect declarations 
                    }
#line 1414 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 94 "lab9.y" /* yacc.c:1646  */
    {   
					(yyval.node)=(yyvsp[0].node);  
				}
#line 1422 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 100 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node)=(yyvsp[0].node);
                }
#line 1430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 106 "lab9.y" /* yacc.c:1646  */
    { /*update all elements to the list to the type*/
						
						/*populate s1 connected list with defined type @$1*/
						ASTnode *p = (yyvsp[-1].node);
						while(p != NULL){
							p->my_data_type = (yyvsp[-2].d_type);
							//check each variable to see if already defined @ given level
							if(Search(p->name, LEVEL,0) != NULL)
							{	//Symbol defined BARF
								yyerror(p->name);
								yyerror("Symbol already defined");
								exit(1);
							}
							if(p->value == 0){
								p->symbol = Insert(p->name, p->my_data_type, SYM_SCALAR,LEVEL,1,OFFSET);
								OFFSET = OFFSET + 1;
							}
							else {
								p->symbol = Insert(p->name, p->my_data_type, SYM_ARRAY,LEVEL,p->value,OFFSET);
								OFFSET = OFFSET + p->value;
							}
							p = p->s1;
						}
                        (yyval.node) = (yyvsp[-1].node);/*dollar dollar = dolar two*/
                    }
#line 1460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 134 "lab9.y" /* yacc.c:1646  */
    {   (yyval.node)=ASTCreateNode(A_VARDEC); 
                            (yyval.node)->name = (yyvsp[0].string);
                        }
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 138 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node)=ASTCreateNode(A_VARDEC);
							(yyval.node)->name = (yyvsp[-3].string);
							(yyval.node)->value = (yyvsp[-1].value); //size of array
						}
#line 1478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 144 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node)=ASTCreateNode(A_VARDEC);
							(yyval.node)->name = (yyvsp[-2].string);
							(yyval.node)->s1 = (yyvsp[0].node); // s1 connect var list
						}
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 150 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node)=ASTCreateNode(A_VARDEC);
							(yyval.node)->name = (yyvsp[-5].string);
							(yyval.node)->value = (yyvsp[-3].value); // size of array
							(yyval.node)->s1 = (yyvsp[0].node); // s1 connect var list
						}
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 158 "lab9.y" /* yacc.c:1646  */
    {	(yyval.d_type) = A_INTTYPE;}
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 159 "lab9.y" /* yacc.c:1646  */
    {	(yyval.d_type) = A_VOIDTYPE;}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 163 "lab9.y" /* yacc.c:1646  */
    {//check if function is defined
						if(Search((yyvsp[0].string),LEVEL,0) != NULL) {
							//id already used for func
							yyerror((yyvsp[0].string));
							yyerror("function name already in use");
							exit(1);
						}	
						//put into symbol table 
						Insert((yyvsp[0].string),  (yyvsp[-1].d_type),  SYM_FUNCTION,	LEVEL,	0,	0);

						GOFFSET = OFFSET;
						OFFSET = 2;
						maxoffset = OFFSET;
					}
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 178 "lab9.y" /* yacc.c:1646  */
    {
						Search((yyvsp[-4].string), LEVEL, 0)->fparms = (yyvsp[-1].node);
					}
#line 1538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 182 "lab9.y" /* yacc.c:1646  */
    {		
						(yyval.node) = ASTCreateNode(A_FUNCTIONDEC);
						(yyval.node)->name = (yyvsp[-6].string);
						(yyval.node)->my_data_type = (yyvsp[-7].d_type); // INT OR VOID
						(yyval.node)->s1 = (yyvsp[-3].node); // PARAMS LIST
						(yyval.node)->s2 = (yyvsp[0].node); // S2 connect compound statement
						(yyval.node)->symbol = Search((yyvsp[-6].string),LEVEL,0);
						(yyval.node)->symbol->offset = maxoffset;
						OFFSET -= Delete(1);
						LEVEL = 0;
						OFFSET = GOFFSET; // resets offset for global vars
					}
#line 1555 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 197 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.node) = NULL;
			}
#line 1563 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 201 "lab9.y" /* yacc.c:1646  */
    {
			(yyval.node) = (yyvsp[0].node);// fixme
			}
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 207 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[0].node); // param
				}
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 211 "lab9.y" /* yacc.c:1646  */
    {
					(yyvsp[-2].node)->next = (yyvsp[0].node); //next connect param list
					(yyval.node) = (yyvsp[-2].node); 
				}
#line 1588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 218 "lab9.y" /* yacc.c:1646  */
    {
				if(Search((yyvsp[0].string), LEVEL+1,0) != NULL ) {
					yyerror((yyvsp[0].string));
					yyerror("parameter already used");
					exit(1);
				}
				
				(yyval.node) = ASTCreateNode(A_PARAM);
				(yyval.node)->my_data_type = (yyvsp[-1].d_type); // INT OR VOID
				(yyval.node)->name = (yyvsp[0].string); // ID
				(yyval.node)->symbol = Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_SCALAR, LEVEL + 1, 1,OFFSET);
				OFFSET = OFFSET + 1;
			}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 232 "lab9.y" /* yacc.c:1646  */
    {	
				if(Search((yyvsp[-2].string), LEVEL+1,0) != NULL ) {
					yyerror((yyvsp[-2].string));
					yyerror("parameter already used");
					exit(1);
				}
				(yyval.node)= ASTCreateNode(A_PARAM);
				(yyval.node)->my_data_type = (yyvsp[-3].d_type); // INT OR VOID 
				(yyval.node)->name = (yyvsp[-2].string); // ID
				(yyval.node)->value = 777; //specify passing array
				(yyval.node)->symbol = Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_ARRAY, LEVEL + 1, 1,OFFSET);
				OFFSET = OFFSET + 1;
			}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 247 "lab9.y" /* yacc.c:1646  */
    { LEVEL++; }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 248 "lab9.y" /* yacc.c:1646  */
    {
							
							(yyval.node) = ASTCreateNode(A_COMPOUND);
							(yyval.node)->s1 = (yyvsp[-2].node);
							(yyval.node)->s2 = (yyvsp[-1].node);
							if(myDebug) 	Display();
							if(OFFSET > maxoffset) maxoffset = OFFSET;
							OFFSET -= Delete(LEVEL);
							LEVEL--;
						}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 261 "lab9.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						(yyval.node)->next = (yyvsp[0].node); // next connect local declarations/var decls
					}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 267 "lab9.y" /* yacc.c:1646  */
    {
						(yyval.node) = NULL; 
					}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 273 "lab9.y" /* yacc.c:1646  */
    {
						(yyval.node) = NULL;
					}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 277 "lab9.y" /* yacc.c:1646  */
    {
						(yyval.node) = (yyvsp[-1].node);
						(yyval.node)->next = (yyvsp[0].node);
					}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 283 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node);}
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 284 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 285 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 286 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 287 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 288 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 289 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 290 "lab9.y" /* yacc.c:1646  */
    {	(yyval.node) = (yyvsp[0].node); }
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 294 "lab9.y" /* yacc.c:1646  */
    {
								(yyval.node) = ASTCreateNode(A_EXPRSTMT);
								(yyval.node)->s1 = (yyvsp[-1].node); //expression
							}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 300 "lab9.y" /* yacc.c:1646  */
    {
								(yyval.node) = ASTCreateNode(A_EXPRSTMT);
							}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 306 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node) = ASTCreateNode(A_IF);
							(yyval.node)->s1 = (yyvsp[-2].node); // if expression
							(yyval.node)->s2 = ASTCreateNode(AIF_BODY);
							(yyval.node)->s2->s1 = (yyvsp[0].node); // if statment
						}
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 314 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node) = ASTCreateNode(A_IF);
							(yyval.node)->s1 = (yyvsp[-4].node); // if expression
							(yyval.node)->s2 = ASTCreateNode(AIF_BODY);
							(yyval.node)->s2->s1 = (yyvsp[-2].node); // if statement
							(yyval.node)->s2->s2 = (yyvsp[0].node); // else statment

						}
#line 1768 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 325 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node) = ASTCreateNode(A_ITERATE);
							(yyval.node)->s1 = (yyvsp[-2].node); // while expression
							(yyval.node)->s2 = ASTCreateNode(AWHILE_BODY);
							(yyval.node)->s2->s1 = (yyvsp[0].node); // while statement
						}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 333 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node) = ASTCreateNode(A_RETURN);
							(yyval.node)->s1 = (yyvsp[-1].node); //expression
						}
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 339 "lab9.y" /* yacc.c:1646  */
    {
							(yyval.node) = ASTCreateNode(A_RETURN);
						}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 344 "lab9.y" /* yacc.c:1646  */
    {
						(yyval.node) = ASTCreateNode(A_READ);
						(yyval.node)->s1 = (yyvsp[-1].node); //s1 connect var to read
					}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 351 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->s1 = (yyvsp[-1].node); // s1 expression
				}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 357 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = ASTCreateNode(A_WRITE);
					(yyval.node)->label = generateLabel();
					(yyval.node)->name = (yyvsp[-1].string); //give string name for Write node
				}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 365 "lab9.y" /* yacc.c:1646  */
    {
								if((yyvsp[-3].node)->my_data_type != (yyvsp[-1].node)->my_data_type) {
									yyerror("TyP3 mismatch");
									exit(1);
								}

								(yyval.node) = ASTCreateNode(A_ASSIGN);
								(yyval.node)->s1 = (yyvsp[-3].node); // s1 var to be assigned
								(yyval.node)->operator = A_EQ; // give assign node =
								(yyval.node)->s2 = (yyvsp[-1].node); // s2 expression to assign
								(yyval.node)->name = CreateTemp();
								(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[-3].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
								OFFSET = OFFSET + 1;
							}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 382 "lab9.y" /* yacc.c:1646  */
    {
			struct SymbTab *p;
			p = Search((yyvsp[0].string),LEVEL, 1);
			if(p == NULL){
				//not in symbol table
				yyerror((yyvsp[0].string));
				yyerror("Symbol used but not defined");
				exit(1);
			}

			if(p->SubType != SYM_SCALAR){
				//not a scalar type
				yyerror((yyvsp[0].string));
				yyerror("SYMBOL IS NOT A SCALAR");
				exit(1);
			}

			(yyval.node) = ASTCreateNode(A_VAR);
			(yyval.node)->name = (yyvsp[0].string);
			(yyval.node)->symbol = p;
			(yyval.node)->my_data_type = p->Declared_Type;
		}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 406 "lab9.y" /* yacc.c:1646  */
    {
			struct SymbTab *p;
			p = Search((yyvsp[-3].string), LEVEL, 1);
			if(p == NULL){
				yyerror((yyvsp[-3].string));
				yyerror("Symbol Used But Not Defined for Array");
				exit(1);
			}
			if(p->SubType != SYM_ARRAY){
				yyerror((yyvsp[-3].string));
				yyerror("Symbol is not an ARRAY");
				exit(1);
			}
			(yyval.node) = ASTCreateNode(A_VAR);
			(yyval.node)->name = (yyvsp[-3].string);
			(yyval.node)->s1 = (yyvsp[-1].node);
			(yyval.node)->value = 77; //specifiy that var is array. 
			(yyval.node)->symbol = p;
		}
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 427 "lab9.y" /* yacc.c:1646  */
    {  (yyval.node) = (yyvsp[0].node); }
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 430 "lab9.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1906 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 431 "lab9.y" /* yacc.c:1646  */
    {
									if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node)->my_data_type) {
										yyerror("type MISMATCHED");
										exit(1);
									}
									(yyval.node) = ASTCreateNode(A_EXPR);
									(yyval.node)->s1 = (yyvsp[-2].node); //s1 connect left most expression
									(yyval.node)->s2 = (yyvsp[0].node); // s2 connect right most expresstion
									(yyval.node)->operator = (yyvsp[-1].operator); // operator to assign
									(yyval.node)->name = CreateTemp();
									(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[-2].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
									OFFSET = OFFSET + 1;
									(yyval.node)->my_data_type = (yyvsp[-2].node)->my_data_type;
								}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 447 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_GE; }
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 448 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_LT; }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 449 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_GT; }
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 450 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_LE; }
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 451 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_EQ; }
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 452 "lab9.y" /* yacc.c:1646  */
    { (yyval.operator) = A_NE; }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 456 "lab9.y" /* yacc.c:1646  */
    {		
							(yyval.node) = (yyvsp[0].node);
						}
#line 1969 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 460 "lab9.y" /* yacc.c:1646  */
    {
							if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node)->my_data_type)	{
								yyerror("type is mismatched");
								exit(1);
							}	
							(yyval.node) = ASTCreateNode(A_EXPR);
							(yyval.node)->s1 = (yyvsp[-2].node); //additive expression
							(yyval.node)->operator = (yyvsp[-1].operator);
							(yyval.node)->s2 = (yyvsp[0].node); //term
							(yyval.node)->name = CreateTemp();
							(yyval.node)->my_data_type = (yyvsp[-2].node)->my_data_type;
							(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[-2].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
							OFFSET = OFFSET + 1;
						}
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 477 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.operator) = A_PLUS;
			}
#line 1996 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 481 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.operator) = A_SUB;
			}
#line 2004 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 487 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.node) = (yyvsp[0].node);
			}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 491 "lab9.y" /* yacc.c:1646  */
    {
				if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node)->my_data_type) {
					yyerror("Type mismatch term");
					exit(1);
				}
				
				(yyval.node) = ASTCreateNode(A_EXPR);
				(yyval.node)->s1 = (yyvsp[-2].node); //term
				(yyval.node)->operator = (yyvsp[-1].operator);
				(yyval.node)->my_data_type = (yyvsp[-2].node)->my_data_type;
				(yyval.node)->s2 = (yyvsp[0].node);  //factor
				(yyval.node)->name = CreateTemp();
				(yyval.node)->symbol = Insert((yyval.node)->name, (yyval.node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
				OFFSET = OFFSET + 1;
			}
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 509 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.operator) = A_TIMES;
			}
#line 2040 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 513 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.operator) = A_DIV;
			}
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 517 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.operator) = A_MOD;
			}
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 523 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[-1].node); 	
				}
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 527 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = ASTCreateNode(A_NUM);
					(yyval.node)->value = (yyvsp[0].value);	
					(yyval.node)->my_data_type = A_INTTYPE;
				}
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 533 "lab9.y" /* yacc.c:1646  */
    {	
					(yyval.node) = (yyvsp[0].node);
				}
#line 2082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 537 "lab9.y" /* yacc.c:1646  */
    {
					(yyval.node) = (yyvsp[0].node);
				}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 541 "lab9.y" /* yacc.c:1646  */
    {
					if((yyvsp[0].node)->my_data_type != A_INTTYPE) {
						yyerror("Type mismatch unary minus");
						exit(1);
					}

					(yyval.node) = ASTCreateNode(A_EXPR);
					(yyval.node)->operator = A_UMINUS;
					(yyval.node)->s1 = (yyvsp[0].node); // factor
					(yyval.node)->name = CreateTemp();
					(yyval.node)->my_data_type = A_INTTYPE;
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[0].node)->my_data_type, 
					SYM_SCALAR, LEVEL, 1, OFFSET);

				}
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 559 "lab9.y" /* yacc.c:1646  */
    { 
					struct SymbTab *p;
					p = Search((yyvsp[-3].string),0,0);
					if(p ==NULL)	{
						yyerror((yyvsp[-3].string));
						yyerror("function call not known");
						exit(1);
					}

					if(p->SubType != SYM_FUNCTION)	{
						yyerror((yyvsp[-3].string));
						yyerror("not defined as function");
						exit(1);
					}
					//check if formal and actual parameters are same
					if(check_params((yyvsp[-1].node),	p->fparms) == 0)	{
						yyerror((yyvsp[-3].string));
						yyerror("Actuals and Formals do not Match");
						exit(1);
					}
					(yyval.node) = ASTCreateNode(A_CALL);
					(yyval.node)->name = (yyvsp[-3].string);
					(yyval.node)->s1 = (yyvsp[-1].node); //args list   
					(yyval.node)->symbol = p;
					(yyval.node)->my_data_type = p->Declared_Type;
				}
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 588 "lab9.y" /* yacc.c:1646  */
    {
				(yyval.node) = (yyvsp[0].node);
			}
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 592 "lab9.y" /* yacc.c:1646  */
    {

			}
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 598 "lab9.y" /* yacc.c:1646  */
    {
					
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[0].node); // s1 connect expression for arg node
					(yyval.node)->name = CreateTemp();
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[0].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					(yyval.node)->my_data_type = (yyvsp[0].node)->my_data_type;
					OFFSET = OFFSET + 1;
					
				}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 609 "lab9.y" /* yacc.c:1646  */
    {
					if((yyvsp[-2].node)->my_data_type != (yyvsp[0].node)->my_data_type)  {
						yyerror("TYPE mismatch");
						exit(1);
					}
					(yyval.node) = ASTCreateNode(A_ARG);
					(yyval.node)->s1 = (yyvsp[-2].node); //s1 connect expression for arg node
					(yyval.node)->next = (yyvsp[0].node); // next connect other expressions. 
					(yyval.node)->name = CreateTemp();
					(yyval.node)->symbol = Insert((yyval.node)->name, (yyvsp[0].node)->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					(yyval.node)->my_data_type = (yyvsp[0].node)->my_data_type;
					OFFSET = OFFSET + 1;
				}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2194 "y.tab.c" /* yacc.c:1646  */
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
#line 624 "lab9.y" /* yacc.c:1906  */
	/*end of rules*/

/*start of program*/
void main(int argc, char * argv[])
{	
	FILE *fp;
	int i;
	char s[100];
	//option for -d to turn on debug 
	//option for -o next arg is output file name
	for(i=0; i < argc; i++) {
		if(strcmp(argv[i], "-d") == 0) myDebug = 1;
		if(strcmp(argv[i], "-o") == 0) {
			// file input
			strcpy(s,argv[i + 1]);
			strcat(s,".asm");
			/* printf(" File name is %s \n", s); */
		}
	}

	fp = fopen(s, "w");
	if(fp == NULL) { 
		printf("cannot open file %s\n", s);
		exit(1);
	}



	yyparse();
    if(myDebug) printf("\nfinished parsing\n\n\n");
	if(myDebug) Display();
    if(myDebug) printf("\n\n\nASTprint\n\n\n");
	if(myDebug) ASTprint(0,PROGRAM);

	EMIT(PROGRAM, fp);
}
