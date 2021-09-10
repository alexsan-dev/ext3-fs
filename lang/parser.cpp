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
#line 7 "parser.y" /* yacc.c:339  */

#include "scanner.h"
#include <iostream>
#include <string.h>

#include "../permissions/index.h"
#include "../partitions/index.h"
#include "../utils/exec/index.h"
#include "../graphs/index.h"
#include "../groups/index.h"
#include "../disks/index.h"
#include "../nodes/index.h"
#include "../users/index.h"

using namespace std;

extern int yylineno; 
extern char *yytext;
extern int col;

int yyerror(const char* mens) {
    std::cout << mens << " " << yytext << std::endl;
    return 0;
}

#line 92 "parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 34 "parser.y" /* yacc.c:355  */

    struct PropVariant {
        char *value;
        char *name;
    };

#line 129 "parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    equals = 258,
    mkdisk = 259,
    rmdisk = 260,
    fdisk = 261,
    mount = 262,
    unmount = 263,
    mkfs = 264,
    login = 265,
    logout = 266,
    mkgrp = 267,
    rmgrp = 268,
    mkusr = 269,
    rmusr = 270,
    chmod = 271,
    touch = 272,
    cat = 273,
    mkdir = 274,
    execR = 275,
    repR = 276,
    sizeP = 277,
    path = 278,
    unit = 279,
    fit = 280,
    type = 281,
    name = 282,
    add = 283,
    del = 284,
    idP = 285,
    pPr = 286,
    fs = 287,
    pwd = 288,
    user = 289,
    usr = 290,
    grp = 291,
    ugo = 292,
    rPr = 293,
    cont = 294,
    stdinR = 295,
    filePr = 296,
    rootR = 297,
    ruta = 298,
    likepath = 299,
    strtext = 300,
    letter = 301,
    number = 302,
    word = 303,
    comment = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 50 "parser.y" /* yacc.c:355  */

    struct PartitionCommandsProps *PTCMDPROPS;
    struct DiskCommandsProps *DKCMDPROPS;
    struct PartitionFsProps *FSCMDPROPS;
    struct UserCommandsProps *USRCMDPROPS;
    struct MkUserProps *MKUSRCMDPROPS;
    struct ChmodProps *CHMODCMDPROPS;
    struct TouchProps *TOUCHCMDPROPS;
    struct RepProps *REPCMDPROPS;
    struct ListProp *FILELIST;
    struct PropVariant PROP;
    char *TEXT;

#line 205 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 236 "parser.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 42 "parser.y" /* yacc.c:359  */

    PropVariant set_prop(char *value, char *key){
        PropVariant prop = { value, key };
        return prop;
    }

#line 245 "parser.cpp" /* yacc.c:359  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  121
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  59
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   183,   183,   189,   194,   201,   203,   207,   209,   209,
     211,   211,   211,   212,   212,   212,   212,   213,   213,   213,
     213,   214,   214,   214,   214,   215,   215,   215,   215,   219,
     225,   229,   234,   235,   236,   237,   239,   240,   241,   242,
     246,   255,   261,   265,   270,   271,   272,   273,   274,   275,
     276,   277,   279,   280,   281,   282,   286,   290,   298,   305,
     309,   315,   319,   324,   325,   326,   328,   329,   333,   339,
     343,   348,   349,   350,   352,   352,   356,   364,   372,   380,
     386,   390,   395,   396,   397,   399,   400,   404,   412,   418,
     422,   427,   428,   429,   431,   431,   435,   441,   445,   450,
     451,   452,   453,   454,   456,   460,   466,   470,   477,   482,
     487,   496,   502,   506,   511,   512,   513,   514,   515,   517,
     518,   522
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "equals", "mkdisk", "rmdisk", "fdisk",
  "mount", "unmount", "mkfs", "login", "logout", "mkgrp", "rmgrp", "mkusr",
  "rmusr", "chmod", "touch", "cat", "mkdir", "execR", "repR", "sizeP",
  "path", "unit", "fit", "type", "name", "add", "del", "idP", "pPr", "fs",
  "pwd", "user", "usr", "grp", "ugo", "rPr", "cont", "stdinR", "filePr",
  "rootR", "ruta", "likepath", "strtext", "letter", "number", "word",
  "comment", "$accept", "STRVALUE", "NUMVALUE", "START", "COMMANDS",
  "COMMAND", "MKDISKCMD", "MKDISKPROPS", "MKDISKPROP", "UNITPARAM",
  "PATHPARAM", "SIZEPARAM", "FITPARAM", "RMDISKCMD", "FDISKCMD",
  "FDISKPROPS", "FDISKPROP", "TYPEPARAM", "DELPARAM", "NAMEPARAM",
  "ADDPARAM", "MOUNTCMD", "UNMOUNTCMD", "IDPARAM", "MKFSCMD", "MKFSPROPS",
  "MKFSPROP", "TYPEEXTPARAM", "FSPARAM", "LOGINCMD", "LOGINPROPS",
  "LOGINPROP", "PWDPARAM", "LOGOUTCMD", "MKGRPCMD", "RMGRPCMD", "MKUSRCMD",
  "MKUSRPROPS", "MKUSRPROP", "USRPARAM", "GRPPARAM", "RMUSRCMD",
  "CHMODCMD", "CHMODPROPS", "CHMODPROP", "UGOPARAM", "TOUCHCMD",
  "TOUCHPROPS", "TOUCHPROP", "CONTPARAM", "CATCMD", "FILELIST", "MKDIRCMD",
  "REPCMD", "REPPROPS", "REPPROP", "RUTAPARAM", "ROOTPARAM", "EXECCMD", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -107

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-107)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     115,    86,    14,    60,    -1,    22,    27,    38,  -107,    29,
      29,    15,    28,    -6,     5,    26,    18,    14,    12,  -107,
      69,   115,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,    73,    87,    88,    95,    86,  -107,  -107,  -107,  -107,
    -107,  -107,    98,   101,   102,   103,  -107,  -107,  -107,  -107,
      60,  -107,  -107,  -107,  -107,  -107,    29,    14,   109,  -107,
     110,   113,  -107,    27,  -107,  -107,  -107,   134,   135,  -107,
      38,  -107,  -107,  -107,  -107,  -107,   136,  -107,    15,  -107,
    -107,  -107,  -107,   137,  -107,  -107,    -6,  -107,  -107,  -107,
     138,  -107,  -107,  -107,     5,  -107,  -107,    96,   104,    14,
     111,  -107,   141,   143,  -107,  -107,  -107,    12,  -107,  -107,
    -107,  -107,  -107,    13,    55,   105,   106,  -107,   107,    55,
      13,    55,  -107,  -107,  -107,    55,    55,   100,  -107,    30,
      55,  -107,    55,  -107,    48,  -107,    55,  -107,   145,   108,
    -107,  -107,    55,    55,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,   112,  -107,  -107,  -107,  -107,  -107,  -107,
     114,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    55,   146,
    -107,  -107,  -107,   116,  -107,    55,  -107,  -107
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,    76,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,     7,     9,    10,    11,    12,    13,    14,    15,    17,
      18,    20,    21,    19,    22,    23,    24,    25,    16,    27,
      26,     0,     0,     0,     0,    29,    30,    34,    33,    32,
      35,    40,     0,     0,     0,     0,    46,    45,    44,    47,
      41,    42,    48,    49,    50,    51,     0,     0,     0,    58,
       0,     0,    63,    60,    61,    64,    65,     0,     0,    71,
      68,    69,    73,    72,    77,    78,     0,    82,    79,    80,
      83,    84,    87,     0,    93,    91,    88,    89,    92,   102,
       0,   103,    99,   100,    96,    97,   101,     0,   105,     0,
     110,   121,     0,     0,   115,   114,   116,   111,   112,   117,
     118,     1,     8,     0,     0,     0,     0,    31,     0,     0,
       0,     0,    43,    56,    57,     0,     0,     0,    62,     0,
       0,    70,     0,    81,     0,    90,     0,    98,     0,     0,
     109,   108,     0,     0,   113,     6,     5,    38,     3,     2,
       4,    37,    36,     0,    52,    54,    55,    53,    59,    66,
       0,    75,    74,    85,    86,    95,    94,   104,     0,     0,
     120,   119,    39,     0,   106,     0,    67,   107
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -106,    20,  -107,  -107,   133,  -107,  -107,   118,     2,
      -2,    10,     4,  -107,  -107,  -107,    97,  -107,  -107,     0,
    -107,  -107,  -107,     1,  -107,  -107,    83,  -107,  -107,  -107,
    -107,    79,    -8,  -107,  -107,  -107,  -107,  -107,    77,     9,
    -107,  -107,  -107,  -107,    65,  -107,  -107,  -107,    62,  -107,
    -107,  -107,  -107,  -107,  -107,    50,  -107,  -107,  -107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   161,   157,    20,    21,    22,    23,    45,    46,    47,
      48,    49,    50,    24,    25,    60,    61,    62,    63,    64,
      65,    26,    27,    72,    28,    73,    74,    75,    76,    29,
      80,    81,    82,    30,    31,    32,    33,    88,    89,    83,
      91,    34,    35,    96,    97,    98,    36,   104,   105,   106,
      37,   108,    38,    39,   117,   118,   119,   120,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      51,    57,    66,    87,    67,    56,    69,    59,    79,    84,
      85,    95,   102,    58,   110,   111,   114,    42,   115,   116,
      90,    92,    42,   165,   103,   167,    53,    41,    42,   168,
     169,    93,    94,   172,   173,    42,   174,    42,   176,    53,
     177,    42,    68,    99,   100,   101,   180,   181,    77,   109,
      78,    86,    68,    70,   112,   113,    53,    68,    57,    71,
     155,   156,    56,    78,    59,   134,   133,   107,    68,   121,
      58,    77,   184,    78,   158,   159,   123,   171,   160,   187,
      87,    79,    41,    42,    43,    44,    52,    53,    54,    55,
     124,   125,   158,   159,    95,   175,   160,    90,   126,   158,
     159,   128,   102,   160,   129,   130,   131,   150,    41,    42,
      43,    44,   135,   136,   103,   114,   137,   115,   116,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,   139,   140,   142,
     144,   146,   151,   148,   152,   149,   153,   170,   178,   185,
     166,   162,   163,   164,   122,   179,   138,   132,   182,   141,
     183,   145,   186,   127,    19,   143,   147,   154
};

static const yytype_uint8 yycheck[] =
{
       2,     3,     4,    11,     4,     3,     5,     3,     7,     9,
      10,    13,    14,     3,    16,    17,    18,    23,    18,    18,
      11,    12,    23,   129,    14,   131,    27,    22,    23,   135,
     136,    37,    38,   139,   140,    23,   142,    23,   144,    27,
     146,    23,    30,    38,    39,    40,   152,   153,    33,    31,
      35,    36,    30,    26,    42,    43,    27,    30,    60,    32,
      47,    48,    60,    35,    60,    67,    66,    41,    30,     0,
      60,    33,   178,    35,    44,    45,     3,    47,    48,   185,
      88,    80,    22,    23,    24,    25,    26,    27,    28,    29,
       3,     3,    44,    45,    96,    47,    48,    88,     3,    44,
      45,     3,   104,    48,     3,     3,     3,   109,    22,    23,
      24,    25,     3,     3,   104,   117,     3,   117,   117,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     3,     3,     3,
       3,     3,    31,    47,     3,    41,     3,    47,     3,     3,
     130,    46,    46,    46,    21,    47,    73,    60,    46,    80,
      46,    96,    46,    45,    49,    88,   104,   117
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    49,
      53,    54,    55,    56,    63,    64,    71,    72,    74,    79,
      83,    84,    85,    86,    91,    92,    96,   100,   102,   103,
     108,    22,    23,    24,    25,    57,    58,    59,    60,    61,
      62,    60,    26,    27,    28,    29,    59,    60,    61,    62,
      65,    66,    67,    68,    69,    70,    60,    69,    30,    73,
      26,    32,    73,    75,    76,    77,    78,    33,    35,    73,
      80,    81,    82,    89,    69,    69,    36,    82,    87,    88,
      89,    90,    89,    37,    38,    60,    93,    94,    95,    38,
      39,    40,    60,    61,    97,    98,    99,    41,   101,    31,
      60,    60,    42,    43,    60,    69,    73,   104,   105,   106,
     107,     0,    55,     3,     3,     3,     3,    58,     3,     3,
       3,     3,    66,    69,    60,     3,     3,     3,    76,     3,
       3,    81,     3,    88,     3,    94,     3,    98,    47,    41,
      60,    31,     3,     3,   105,    47,    48,    52,    44,    45,
      48,    51,    46,    46,    46,    51,    52,    51,    51,    51,
      47,    47,    51,    51,    51,    47,    51,    51,     3,    47,
      51,    51,    46,    46,    51,     3,    46,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    52,    52,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    57,    58,    58,    58,    58,    59,    60,    61,    62,
      63,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    68,    69,    70,    71,    71,    72,    73,
      74,    75,    75,    76,    76,    76,    77,    78,    79,    80,
      80,    81,    81,    81,    82,    82,    83,    84,    85,    86,
      87,    87,    88,    88,    88,    89,    90,    91,    92,    93,
      93,    94,    94,    94,    95,    95,    96,    97,    97,    98,
      98,    98,    98,    98,    99,   100,   101,   101,   102,   102,
     102,   103,   104,   104,   105,   105,   105,   105,   105,   106,
     107,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     3,     3,     3,     4,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     2,     3,
       2,     1,     2,     1,     1,     1,     3,     5,     2,     1,
       2,     1,     1,     1,     3,     3,     1,     2,     2,     2,
       1,     2,     1,     1,     1,     3,     3,     2,     2,     1,
       2,     1,     1,     1,     3,     3,     2,     1,     2,     1,
       1,     1,     1,     1,     3,     2,     4,     5,     3,     3,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       3,     2
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 183 "parser.y" /* yacc.c:1646  */
    {
    string value = (yyvsp[0].TEXT);
    value = value.substr(1, value.size() - 2);
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    (yyval.TEXT) = text;
}
#line 1567 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 189 "parser.y" /* yacc.c:1646  */
    {
    string value = (yyvsp[0].TEXT);
    char *text = new char[value.length() + 1];
    strcpy(text, value.c_str());
    (yyval.TEXT) = text;
}
#line 1578 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 194 "parser.y" /* yacc.c:1646  */
    {
    string value = (yyvsp[0].TEXT);
    char *text =  new char[value.length() + 1];
    strcpy(text, value.c_str());
    (yyval.TEXT) = text;
}
#line 1589 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 201 "parser.y" /* yacc.c:1646  */
    {
    (yyval.TEXT) = (yyvsp[0].TEXT);
}
#line 1597 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 203 "parser.y" /* yacc.c:1646  */
    {
    (yyval.TEXT) = (yyvsp[0].TEXT);
}
#line 1605 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 207 "parser.y" /* yacc.c:1646  */
    { }
#line 1611 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 209 "parser.y" /* yacc.c:1646  */
    { }
#line 1617 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 215 "parser.y" /* yacc.c:1646  */
    { }
#line 1623 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 219 "parser.y" /* yacc.c:1646  */
    { 
    disk_commands *disk_cmd = new disk_commands();
    disk_cmd->mkdisk(*(yyvsp[0].DKCMDPROPS));  
    delete disk_cmd;
}
#line 1633 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 225 "parser.y" /* yacc.c:1646  */
    {
    DiskCommandsProps *props = new DiskCommandsProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.DKCMDPROPS) = props;
}
#line 1643 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 229 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].DKCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.DKCMDPROPS) = (yyvsp[-1].DKCMDPROPS);
}
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "size"); }
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "path"); }
#line 1664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "unit"); }
#line 1670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "fit"); }
#line 1676 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[-1].TEXT); }
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 246 "parser.y" /* yacc.c:1646  */
    { 
    disk_commands *disk_cmd = new disk_commands();
    string path = (yyvsp[0].TEXT);
    disk_cmd->rmdisk(path);
    delete disk_cmd;
}
#line 1711 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 255 "parser.y" /* yacc.c:1646  */
    { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->fdisk(*(yyvsp[0].PTCMDPROPS)); 
    delete part_cmd; 
}
#line 1721 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 261 "parser.y" /* yacc.c:1646  */
    {
    PartitionCommandsProps *props = new PartitionCommandsProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.PTCMDPROPS) = props;
}
#line 1731 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 265 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].PTCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.PTCMDPROPS) = (yyvsp[-1].PTCMDPROPS);
}
#line 1740 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 270 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "size"); }
#line 1746 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 271 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "path"); }
#line 1752 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 272 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "unit"); }
#line 1758 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 273 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "fit"); }
#line 1764 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 274 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "type"); }
#line 1770 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 275 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "del"); }
#line 1776 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 276 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "name"); }
#line 1782 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 277 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "add"); }
#line 1788 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 279 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1794 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 280 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1800 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 281 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1806 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 282 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1812 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 286 "parser.y" /* yacc.c:1646  */
    { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mount((yyvsp[-1].TEXT), (yyvsp[0].TEXT));  
    delete part_cmd;
}
#line 1822 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 290 "parser.y" /* yacc.c:1646  */
    { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mount((yyvsp[0].TEXT),(yyvsp[-1].TEXT)); 
    delete part_cmd; 
}
#line 1832 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 298 "parser.y" /* yacc.c:1646  */
    { 
    partition_commands *part_cmd = new partition_commands();
    string id = (yyvsp[0].TEXT);
    part_cmd->unmount(id);  
    delete part_cmd;
}
#line 1843 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 305 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1849 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 309 "parser.y" /* yacc.c:1646  */
    { 
    partition_commands *part_cmd = new partition_commands();
    part_cmd->mkfs(*(yyvsp[0].FSCMDPROPS));  
    delete part_cmd;
}
#line 1859 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 315 "parser.y" /* yacc.c:1646  */
    {
    PartitionFsProps *props = new PartitionFsProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.FSCMDPROPS) = props;
}
#line 1869 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 319 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].FSCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.FSCMDPROPS) = (yyvsp[-1].FSCMDPROPS);
}
#line 1878 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 324 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "id"); }
#line 1884 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 325 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "type"); }
#line 1890 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 326 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "fs"); }
#line 1896 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1902 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 329 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[-2].TEXT); }
#line 1908 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 333 "parser.y" /* yacc.c:1646  */
    { 
    user_commands *user_cmd = new user_commands();
    user_cmd->login(*(yyvsp[0].USRCMDPROPS));  
    delete user_cmd;
}
#line 1918 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 339 "parser.y" /* yacc.c:1646  */
    {
    UserCommandsProps *props = new UserCommandsProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.USRCMDPROPS) = props;
}
#line 1928 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 343 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].USRCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.USRCMDPROPS) = (yyvsp[-1].USRCMDPROPS);
}
#line 1937 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 348 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "id"); }
#line 1943 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 349 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "user"); }
#line 1949 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 350 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "pwd"); }
#line 1955 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 352 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1961 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 352 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 1967 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 356 "parser.y" /* yacc.c:1646  */
    { 
    user_commands *user_cmd = new user_commands();
    user_cmd->logout(); 
    delete user_cmd; 
}
#line 1977 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 364 "parser.y" /* yacc.c:1646  */
    { 
    group_commands *grp_cmd = new group_commands();
    grp_cmd->mkgrp((yyvsp[0].TEXT)); 
    delete grp_cmd; 
}
#line 1987 "parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 372 "parser.y" /* yacc.c:1646  */
    { 
    group_commands *grp_cmd = new group_commands();
    grp_cmd->rmgrp((yyvsp[0].TEXT)); 
    delete grp_cmd; 
}
#line 1997 "parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 380 "parser.y" /* yacc.c:1646  */
    { 
    user_commands *user_cmd = new user_commands();
    user_cmd->mkusr(*(yyvsp[0].MKUSRCMDPROPS)); 
    delete user_cmd;
}
#line 2007 "parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 386 "parser.y" /* yacc.c:1646  */
    {
    MkUserProps *props = new MkUserProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.MKUSRCMDPROPS) = props;
}
#line 2017 "parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 390 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].MKUSRCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.MKUSRCMDPROPS) = (yyvsp[-1].MKUSRCMDPROPS);
}
#line 2026 "parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 395 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "pwd"); }
#line 2032 "parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 396 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "usr"); }
#line 2038 "parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 397 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "grp"); }
#line 2044 "parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 399 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2050 "parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 400 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2056 "parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 404 "parser.y" /* yacc.c:1646  */
    { 
    user_commands *user_cmd = new user_commands();
    user_cmd->rmusr((yyvsp[0].TEXT)); 
    delete user_cmd; 
}
#line 2066 "parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 412 "parser.y" /* yacc.c:1646  */
    { 
    permission_commands *perm_cmd = new permission_commands();
    perm_cmd->chmod(*(yyvsp[0].CHMODCMDPROPS));  
    delete perm_cmd;
}
#line 2076 "parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 418 "parser.y" /* yacc.c:1646  */
    {
    ChmodProps *props = new ChmodProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.CHMODCMDPROPS) = props;
}
#line 2086 "parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 422 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].CHMODCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.CHMODCMDPROPS) = (yyvsp[-1].CHMODCMDPROPS);
}
#line 2095 "parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 427 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "path"); }
#line 2101 "parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 428 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "ugo"); }
#line 2107 "parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 429 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "r"); }
#line 2113 "parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 431 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2119 "parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 431 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2125 "parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 435 "parser.y" /* yacc.c:1646  */
    { 
    node_commands *node_cmd = new node_commands();
    node_cmd->touch(*(yyvsp[0].TOUCHCMDPROPS)); 
    delete node_cmd;
}
#line 2135 "parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 441 "parser.y" /* yacc.c:1646  */
    {
    TouchProps *props = new TouchProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.TOUCHCMDPROPS) = props;
}
#line 2145 "parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 445 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].TOUCHCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.TOUCHCMDPROPS) = (yyvsp[-1].TOUCHCMDPROPS);
}
#line 2154 "parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 450 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "path"); }
#line 2160 "parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 451 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "size"); }
#line 2166 "parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 452 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "cont"); }
#line 2172 "parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 453 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "r"); }
#line 2178 "parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 454 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "stdin"); }
#line 2184 "parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 456 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2190 "parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 460 "parser.y" /* yacc.c:1646  */
    {
    node_commands *node_cmd = new node_commands();
    node_cmd->cat(*(yyvsp[0].FILELIST)); 
    delete node_cmd;
}
#line 2200 "parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 466 "parser.y" /* yacc.c:1646  */
    {
    ListProp *props = new ListProp();
    props->list.push_back((yyvsp[-1].TEXT));
    (yyval.FILELIST) = props;
}
#line 2210 "parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 470 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-4].FILELIST)->list.push_back((yyvsp[-1].TEXT));
    (yyval.FILELIST) = (yyvsp[-4].FILELIST);
}
#line 2219 "parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 477 "parser.y" /* yacc.c:1646  */
    { 
    node_commands *node_cmd = new node_commands();
    string path = (yyvsp[-1].TEXT);
    node_cmd->mkdir(path, 1); 
    delete node_cmd;
}
#line 2230 "parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 482 "parser.y" /* yacc.c:1646  */
    { 
    node_commands *node_cmd = new node_commands();
    string path = (yyvsp[0].TEXT);
    node_cmd->mkdir(path, 1); 
    delete node_cmd; 
}
#line 2241 "parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 487 "parser.y" /* yacc.c:1646  */
    { 
    node_commands *node_cmd = new node_commands();
    string path = (yyvsp[0].TEXT);
    node_cmd->mkdir(path, 0); 
    delete node_cmd; 
}
#line 2252 "parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 496 "parser.y" /* yacc.c:1646  */
    { 
    graph_commands *graph_cmd = new graph_commands();
    graph_cmd->rep(*(yyvsp[0].REPCMDPROPS)); 
    delete graph_cmd;
}
#line 2262 "parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 502 "parser.y" /* yacc.c:1646  */
    {
    RepProps *props = new RepProps();
    props->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.REPCMDPROPS) = props;
}
#line 2272 "parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 506 "parser.y" /* yacc.c:1646  */
    {
    (yyvsp[-1].REPCMDPROPS)->set_prop((yyvsp[0].PROP).value, (yyvsp[0].PROP).name);
    (yyval.REPCMDPROPS) = (yyvsp[-1].REPCMDPROPS);
}
#line 2281 "parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "name"); }
#line 2287 "parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 512 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "path"); }
#line 2293 "parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 513 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "id"); }
#line 2299 "parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "ruta"); }
#line 2305 "parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 515 "parser.y" /* yacc.c:1646  */
    { (yyval.PROP) = set_prop((yyvsp[0].TEXT), (char*) "root"); }
#line 2311 "parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 517 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2317 "parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 518 "parser.y" /* yacc.c:1646  */
    { (yyval.TEXT) = (yyvsp[0].TEXT); }
#line 2323 "parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 522 "parser.y" /* yacc.c:1646  */
    {
    exec_file((yyvsp[0].TEXT));
}
#line 2331 "parser.cpp" /* yacc.c:1646  */
    break;


#line 2335 "parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 526 "parser.y" /* yacc.c:1906  */
