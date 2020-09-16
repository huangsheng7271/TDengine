/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
#include <assert.h>
/************ Begin %include sections from the grammar ************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "qSqlparser.h"
#include "tcmdtype.h"
#include "tstoken.h"
#include "ttokendef.h"
#include "tutil.h"
#include "tvariant.h"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ParseCTX_*         As ParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned short int
#define YYNOCODE 270
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE SStrToken
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  int yy112;
  SCreateDBInfo yy118;
  tVariantList* yy156;
  tSQLExprList* yy158;
  tSQLExpr* yy190;
  SSubclauseInfo* yy333;
  SIntervalVal yy340;
  TAOS_FIELD yy343;
  int64_t yy369;
  SCreateTableSQL* yy398;
  SLimitVal yy414;
  SQuerySQL* yy444;
  SCreateAcctSQL yy479;
  tVariant yy506;
  tFieldList* yy511;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL SSqlInfo* pInfo;
#define ParseARG_PDECL ,SSqlInfo* pInfo
#define ParseARG_PARAM ,pInfo
#define ParseARG_FETCH SSqlInfo* pInfo=yypParser->pInfo;
#define ParseARG_STORE yypParser->pInfo=pInfo;
#define ParseCTX_SDECL
#define ParseCTX_PDECL
#define ParseCTX_PARAM
#define ParseCTX_FETCH
#define ParseCTX_STORE
#define YYFALLBACK 1
#define YYNSTATE             246
#define YYNRULE              226
#define YYNRULE_WITH_ACTION  226
#define YYNTOKEN             206
#define YY_MAX_SHIFT         245
#define YY_MIN_SHIFTREDUCE   406
#define YY_MAX_SHIFTREDUCE   631
#define YY_ERROR_ACTION      632
#define YY_ACCEPT_ACTION     633
#define YY_NO_ACTION         634
#define YY_MIN_REDUCE        635
#define YY_MAX_REDUCE        860
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (552)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   735,  447,  223,  733,  734,  633,  245,  513,  736,  448,
 /*    10 */   738,  739,  737,   41,   43,  529,   35,   36,  526,   11,
 /*    20 */   527,   29,  528,  447,  201,   39,   37,   40,   38,  156,
 /*    30 */   243,  448,  752,   34,   33,  221,  220,   32,   31,   30,
 /*    40 */    41,   43,  765,   35,   36,  137,  174,  175,   29,  138,
 /*    50 */    21,  201,   39,   37,   40,   38,  186,  142,  162,  848,
 /*    60 */    34,   33,  844,  776,   32,   31,   30,  407,  408,  409,
 /*    70 */   410,  411,  412,  413,  414,  415,  416,  417,  418,  244,
 /*    80 */    41,   43,  232,   35,   36,  750,   62,  138,   29,  138,
 /*    90 */    21,  201,   39,   37,   40,   38,  161,  848,   27,  847,
 /*   100 */    34,   33,   56,  843,   32,   31,   30,  106,   43,    8,
 /*   110 */    35,   36,   63,  116,  773,   29,  765,  530,  201,   39,
 /*   120 */    37,   40,   38,  170,  542,  751,  587,   34,   33,   18,
 /*   130 */   157,   32,   31,   30,   16,  212,  238,  237,  211,  210,
 /*   140 */   209,  236,  208,  235,  234,  233,  207,  731,  106,  719,
 /*   150 */   720,  721,  722,  723,  724,  725,  726,  727,  728,  729,
 /*   160 */   730,   35,   36,  803,  842,  196,   29,  179,  159,  201,
 /*   170 */    39,   37,   40,   38,  183,  182,   21,   21,   34,   33,
 /*   180 */   447,   12,   32,   31,   30,  166,  600,  754,  448,  591,
 /*   190 */   154,  594,  155,  597,  106,  166,  600,   21,   17,  591,
 /*   200 */   151,  594,  198,  597,   60,   26,   90,   89,  145,  171,
 /*   210 */   219,  751,  751,   16,  150,  238,  237,  163,  164,  169,
 /*   220 */   236,  200,  235,  234,  233,  568,  569,  163,  164,  100,
 /*   230 */   224,  545,  751,  166,  600,   17,   26,  591,  754,  594,
 /*   240 */   106,  597,   26,   39,   37,   40,   38,  537,  172,  239,
 /*   250 */   802,   34,   33,  101,  188,   32,   31,   30,   32,   31,
 /*   260 */    30,   78,  185,   75,   74,  163,  164,  232,  754,  153,
 /*   270 */   857,   76,   80,   85,   88,   79,  242,  241,   97,   34,
 /*   280 */    33,   82,   42,   32,   31,   30,  119,  120,   70,   66,
 /*   290 */    69,  674,   42,  599,  129,  593,   61,  596,  133,  131,
 /*   300 */    93,   92,   91,  599,  683,  189,  675,  129,  598,  129,
 /*   310 */   555,  589,  173,  559,  103,  218,  217,   46,  598,  560,
 /*   320 */   165,  143,  617,   14,  601,  592,   13,  595,   13,   47,
 /*   330 */    42,  533,   50,  534,  519,  518,  205,  813,   46,   22,
 /*   340 */    22,  599,  144,   10,    9,   87,   86,  590,   48,   51,
 /*   350 */   531,  146,  532,  753,  147,  148,  598,  149,  140,    3,
 /*   360 */   136,  141,  139,  812,  167,  809,  808,  168,  775,  780,
 /*   370 */   745,  782,  222,  767,  102,  795,  117,  794,  118,  685,
 /*   380 */   115,  206,  134,   24,  215,  682,  216,  856,   26,   72,
 /*   390 */   855,  853,  121,  187,   95,  703,   25,   23,  554,  135,
 /*   400 */   672,   81,  670,  190,   83,   84,  668,  667,  176,  130,
 /*   410 */   665,  664,  663,  662,  661,  653,  158,  132,  659,  657,
 /*   420 */   194,  655,   52,   57,  764,   49,  107,   58,  199,  796,
 /*   430 */    44,  197,  191,  195,  193,  214,   28,   77,  225,  226,
 /*   440 */   228,  227,  229,  230,  231,  240,  631,  178,  630,  203,
 /*   450 */   181,   53,  177,  180,  152,  629,   64,   67,  622,  184,
 /*   460 */   188,  104,  666,  539,   94,  556,  124,  128,  660,  704,
 /*   470 */   122,  123,  125,  126,   96,  127,  749,    1,  108,  111,
 /*   480 */   109,  112,  110,    2,   55,   59,  160,  113,  114,  192,
 /*   490 */    19,  561,  105,    5,    6,  602,   20,    4,   15,   65,
 /*   500 */     7,  202,  488,  204,  484,  482,  481,  480,  477,  451,
 /*   510 */   213,   68,   45,   71,   73,   22,  515,  514,  512,   54,
 /*   520 */   472,  470,  462,  468,  464,  466,  460,  458,  487,  486,
 /*   530 */   485,  483,  479,  478,   46,  449,  422,  420,  635,  634,
 /*   540 */   634,  634,  634,  634,  634,  634,  634,  634,  634,  634,
 /*   550 */    98,   99,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   225,    1,  209,  228,  229,  206,  207,    5,  233,    9,
 /*    10 */   235,  236,  237,   13,   14,    2,   16,   17,    5,  259,
 /*    20 */     7,   21,    9,    1,   24,   25,   26,   27,   28,  208,
 /*    30 */   209,    9,  239,   33,   34,   33,   34,   37,   38,   39,
 /*    40 */    13,   14,  243,   16,   17,  259,   33,   34,   21,  259,
 /*    50 */   209,   24,   25,   26,   27,   28,  257,  259,  268,  269,
 /*    60 */    33,   34,  259,  209,   37,   38,   39,   45,   46,   47,
 /*    70 */    48,   49,   50,   51,   52,   53,   54,   55,   56,   57,
 /*    80 */    13,   14,   78,   16,   17,  244,  246,  259,   21,  259,
 /*    90 */   209,   24,   25,   26,   27,   28,  268,  269,  258,  269,
 /*   100 */    33,   34,  102,  259,   37,   38,   39,  209,   14,   98,
 /*   110 */    16,   17,  101,  102,  260,   21,  243,  104,   24,   25,
 /*   120 */    26,   27,   28,  242,  103,  244,   99,   33,   34,  108,
 /*   130 */   257,   37,   38,   39,   85,   86,   87,   88,   89,   90,
 /*   140 */    91,   92,   93,   94,   95,   96,   97,  225,  209,  227,
 /*   150 */   228,  229,  230,  231,  232,  233,  234,  235,  236,  237,
 /*   160 */   238,   16,   17,  265,  259,  267,   21,  126,  226,   24,
 /*   170 */    25,   26,   27,   28,  133,  134,  209,  209,   33,   34,
 /*   180 */     1,   44,   37,   38,   39,    1,    2,  245,    9,    5,
 /*   190 */   259,    7,  259,    9,  209,    1,    2,  209,   98,    5,
 /*   200 */    63,    7,  263,    9,  265,  105,   69,   70,   71,  242,
 /*   210 */   242,  244,  244,   85,   77,   87,   88,   33,   34,  226,
 /*   220 */    92,   37,   94,   95,   96,  115,  116,   33,   34,   98,
 /*   230 */   242,   37,  244,    1,    2,   98,  105,    5,  245,    7,
 /*   240 */   209,    9,  105,   25,   26,   27,   28,   99,   63,  226,
 /*   250 */   265,   33,   34,  209,  106,   37,   38,   39,   37,   38,
 /*   260 */    39,   72,  125,  128,  129,   33,   34,   78,  245,  132,
 /*   270 */   245,   64,   65,   66,   67,   68,   60,   61,   62,   33,
 /*   280 */    34,   74,   98,   37,   38,   39,   64,   65,   66,   67,
 /*   290 */    68,  213,   98,  109,  216,    5,  265,    7,   64,   65,
 /*   300 */    66,   67,   68,  109,  213,  261,  213,  216,  124,  216,
 /*   310 */    99,    1,  127,   99,  103,  130,  131,  103,  124,   99,
 /*   320 */    59,  259,   99,  103,   99,    5,  103,    7,  103,  103,
 /*   330 */    98,    5,  103,    7,   99,   99,   99,  240,  103,  103,
 /*   340 */   103,  109,  259,  128,  129,   72,   73,   37,  122,  120,
 /*   350 */     5,  259,    7,  245,  259,  259,  124,  259,  259,   98,
 /*   360 */   259,  259,  259,  240,  240,  240,  240,  240,  209,  209,
 /*   370 */   241,  209,  240,  243,  209,  266,  209,  266,  209,  209,
 /*   380 */   247,  209,  209,  209,  209,  209,  209,  209,  105,  209,
 /*   390 */   209,  209,  209,  243,   59,  209,  209,  209,  109,  209,
 /*   400 */   209,  209,  209,  262,  209,  209,  209,  209,  209,  209,
 /*   410 */   209,  209,  209,  209,  209,  209,  262,  209,  209,  209,
 /*   420 */   262,  209,  119,  210,  256,  121,  255,  210,  113,  210,
 /*   430 */   118,  117,  110,  112,  111,   75,  123,   84,   83,   49,
 /*   440 */    82,   80,   53,   81,   79,   75,    5,    5,    5,  210,
 /*   450 */     5,  210,  135,  135,  210,    5,  214,  214,   86,  126,
 /*   460 */   106,   98,  210,   99,  211,   99,  218,  217,  210,  224,
 /*   470 */   223,  222,  221,  219,  211,  220,  243,  215,  254,  251,
 /*   480 */   253,  250,  252,  212,  107,  103,    1,  249,  248,   98,
 /*   490 */   103,   99,   98,  114,  114,   99,  103,   98,   98,   72,
 /*   500 */    98,  100,    9,  100,    5,    5,    5,    5,    5,   76,
 /*   510 */    15,   72,   16,  129,  129,  103,    5,    5,   99,   98,
 /*   520 */     5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
 /*   530 */     5,    5,    5,    5,  103,   76,   59,   58,    0,  270,
 /*   540 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   550 */    21,   21,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   560 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   570 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   580 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   590 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   600 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   610 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   620 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   630 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   640 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   650 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   660 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   670 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   680 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   690 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   700 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   710 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   720 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   730 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   740 */   270,  270,  270,  270,  270,  270,  270,  270,  270,  270,
 /*   750 */   270,  270,  270,  270,  270,  270,  270,  270,
};
#define YY_SHIFT_COUNT    (245)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (538)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   137,   49,  128,  184,  232,  179,  179,  179,  179,  179,
 /*    10 */   179,    0,   22,  232,   13,   13,   13,  100,  179,  179,
 /*    20 */   179,  179,  179,  189,    4,    4,  552,  194,  232,  232,
 /*    30 */   232,  232,  232,  232,  232,  232,  232,  232,  232,  232,
 /*    40 */   232,  232,  232,  232,  232,   13,   13,    2,    2,    2,
 /*    50 */     2,    2,    2,   11,    2,  131,  179,  179,  179,  179,
 /*    60 */   110,  110,   21,  179,  179,  179,  179,  179,  179,  179,
 /*    70 */   179,  179,  179,  179,  179,  179,  179,  179,  179,  179,
 /*    80 */   179,  179,  179,  179,  179,  179,  179,  179,  179,  179,
 /*    90 */   179,  179,  179,  179,  179,  179,  179,  179,  179,  179,
 /*   100 */   283,  335,  335,  289,  289,  289,  335,  303,  304,  312,
 /*   110 */   315,  314,  321,  323,  322,  313,  283,  335,  335,  360,
 /*   120 */   360,  335,  353,  355,  390,  361,  358,  389,  362,  365,
 /*   130 */   335,  370,  335,  370,  552,  552,   27,   67,   67,   67,
 /*   140 */    94,  145,  218,  218,  218,  207,  246,  246,  246,  246,
 /*   150 */   222,  234,  185,   41,  221,  221,  216,  148,  211,  214,
 /*   160 */   220,  223,  225,  290,  320,  310,  261,  226,  229,  235,
 /*   170 */   236,  237,  135,  215,  326,  345,  273,  441,  317,  442,
 /*   180 */   443,  318,  445,  450,  372,  333,  354,  364,  377,  382,
 /*   190 */   366,  363,  485,  391,  392,  394,  387,  379,  393,  380,
 /*   200 */   396,  399,  400,  401,  402,  403,  427,  493,  499,  500,
 /*   210 */   501,  502,  503,  433,  495,  439,  496,  384,  385,  412,
 /*   220 */   511,  512,  419,  421,  412,  515,  516,  517,  518,  519,
 /*   230 */   520,  521,  522,  523,  524,  525,  526,  527,  528,  431,
 /*   240 */   459,  529,  530,  477,  479,  538,
};
#define YY_REDUCE_COUNT (135)
#define YY_REDUCE_MIN   (-240)
#define YY_REDUCE_MAX   (271)
static const short yy_reduce_ofst[] = {
 /*     0 */  -201,  -78, -225, -210, -172, -102,  -61, -119,  -33,  -32,
 /*    10 */   -12, -146, -179, -170,  -58,   -7,   23, -127,   44,  -15,
 /*    20 */    31, -207, -159,   78,   91,   93, -160, -240, -214, -202,
 /*    30 */  -197, -156,  -95,  -69,  -67,   62,   83,   92,   95,   96,
 /*    40 */    98,   99,  101,  102,  103,   25,  108,   97,  123,  124,
 /*    50 */   125,  126,  127,  129,  132,  130,  159,  160,  162,  165,
 /*    60 */   109,  111,  133,  167,  169,  170,  172,  173,  174,  175,
 /*    70 */   176,  177,  178,  180,  181,  182,  183,  186,  187,  188,
 /*    80 */   190,  191,  192,  193,  195,  196,  197,  198,  199,  200,
 /*    90 */   201,  202,  203,  204,  205,  206,  208,  209,  210,  212,
 /*   100 */   150,  213,  217,  141,  154,  158,  219,  168,  171,  224,
 /*   110 */   227,  230,  228,  231,  238,  240,  233,  239,  241,  242,
 /*   120 */   243,  244,  245,  247,  249,  248,  251,  254,  255,  250,
 /*   130 */   252,  253,  258,  263,  262,  271,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   632,  684,  673,  850,  850,  632,  632,  632,  632,  632,
 /*    10 */   632,  777,  650,  850,  632,  632,  632,  632,  632,  632,
 /*    20 */   632,  632,  632,  686,  686,  686,  772,  632,  632,  632,
 /*    30 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  632,
 /*    40 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  632,
 /*    50 */   632,  632,  632,  632,  632,  632,  632,  779,  781,  632,
 /*    60 */   799,  799,  770,  632,  632,  632,  632,  632,  632,  632,
 /*    70 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  632,
 /*    80 */   632,  671,  632,  669,  632,  632,  632,  632,  632,  632,
 /*    90 */   632,  632,  632,  632,  632,  632,  632,  658,  632,  632,
 /*   100 */   632,  652,  652,  632,  632,  632,  652,  806,  810,  804,
 /*   110 */   792,  800,  791,  787,  786,  814,  632,  652,  652,  681,
 /*   120 */   681,  652,  702,  700,  698,  690,  696,  692,  694,  688,
 /*   130 */   652,  679,  652,  679,  718,  732,  632,  815,  849,  805,
 /*   140 */   833,  832,  845,  839,  838,  632,  837,  836,  835,  834,
 /*   150 */   632,  632,  632,  632,  841,  840,  632,  632,  632,  632,
 /*   160 */   632,  632,  632,  632,  632,  632,  817,  811,  807,  632,
 /*   170 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  632,
 /*   180 */   632,  632,  632,  632,  632,  632,  769,  632,  632,  778,
 /*   190 */   632,  632,  632,  632,  632,  632,  801,  632,  793,  632,
 /*   200 */   632,  632,  632,  632,  632,  746,  632,  632,  632,  632,
 /*   210 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  854,
 /*   220 */   632,  632,  632,  740,  852,  632,  632,  632,  632,  632,
 /*   230 */   632,  632,  632,  632,  632,  632,  632,  632,  632,  705,
 /*   240 */   632,  656,  654,  632,  648,  632,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         ID => nothing */
    1,  /*       BOOL => ID */
    1,  /*    TINYINT => ID */
    1,  /*   SMALLINT => ID */
    1,  /*    INTEGER => ID */
    1,  /*     BIGINT => ID */
    1,  /*      FLOAT => ID */
    1,  /*     DOUBLE => ID */
    1,  /*     STRING => ID */
    1,  /*  TIMESTAMP => ID */
    1,  /*     BINARY => ID */
    1,  /*      NCHAR => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*        NOT => nothing */
    0,  /*         EQ => nothing */
    0,  /*         NE => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         IS => nothing */
    1,  /*       LIKE => ID */
    1,  /*       GLOB => ID */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*         GT => nothing */
    0,  /*         GE => nothing */
    0,  /*         LT => nothing */
    0,  /*         LE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     DIVIDE => nothing */
    0,  /*      TIMES => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     CONCAT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*     MNODES => nothing */
    0,  /*     DNODES => nothing */
    0,  /*   ACCOUNTS => nothing */
    0,  /*      USERS => nothing */
    0,  /*    MODULES => nothing */
    0,  /*    QUERIES => nothing */
    0,  /* CONNECTIONS => nothing */
    0,  /*    STREAMS => nothing */
    0,  /*  VARIABLES => nothing */
    0,  /*     SCORES => nothing */
    0,  /*     GRANTS => nothing */
    0,  /*     VNODES => nothing */
    1,  /*    IPTOKEN => ID */
    0,  /*        DOT => nothing */
    0,  /*     TABLES => nothing */
    0,  /*    STABLES => nothing */
    0,  /*    VGROUPS => nothing */
    0,  /*       DROP => nothing */
    0,  /*      TABLE => nothing */
    1,  /*   DATABASE => ID */
    0,  /*      DNODE => nothing */
    0,  /*       USER => nothing */
    0,  /*    ACCOUNT => nothing */
    0,  /*        USE => nothing */
    0,  /*   DESCRIBE => nothing */
    0,  /*      ALTER => nothing */
    0,  /*       PASS => nothing */
    0,  /*  PRIVILEGE => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*         IF => nothing */
    0,  /*     EXISTS => nothing */
    0,  /*     CREATE => nothing */
    0,  /*        PPS => nothing */
    0,  /*    TSERIES => nothing */
    0,  /*        DBS => nothing */
    0,  /*    STORAGE => nothing */
    0,  /*      QTIME => nothing */
    0,  /*      CONNS => nothing */
    0,  /*      STATE => nothing */
    0,  /*       KEEP => nothing */
    0,  /*      CACHE => nothing */
    0,  /*    REPLICA => nothing */
    0,  /*     QUORUM => nothing */
    0,  /*       DAYS => nothing */
    0,  /*    MINROWS => nothing */
    0,  /*    MAXROWS => nothing */
    0,  /*     BLOCKS => nothing */
    0,  /*      CTIME => nothing */
    0,  /*        WAL => nothing */
    0,  /*      FSYNC => nothing */
    0,  /*       COMP => nothing */
    0,  /*  PRECISION => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*       TAGS => nothing */
    0,  /*      USING => nothing */
    0,  /*         AS => nothing */
    0,  /*      COMMA => nothing */
    1,  /*       NULL => ID */
    0,  /*     SELECT => nothing */
    0,  /*      UNION => nothing */
    1,  /*        ALL => ID */
    0,  /*       FROM => nothing */
    0,  /*   VARIABLE => nothing */
    0,  /*   INTERVAL => nothing */
    0,  /*       FILL => nothing */
    0,  /*    SLIDING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    1,  /*        ASC => ID */
    1,  /*       DESC => ID */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    1,  /*     OFFSET => ID */
    0,  /*     SLIMIT => nothing */
    0,  /*    SOFFSET => nothing */
    0,  /*      WHERE => nothing */
    1,  /*        NOW => ID */
    0,  /*      RESET => nothing */
    0,  /*      QUERY => nothing */
    0,  /*        ADD => nothing */
    0,  /*     COLUMN => nothing */
    0,  /*        TAG => nothing */
    0,  /*     CHANGE => nothing */
    0,  /*        SET => nothing */
    0,  /*       KILL => nothing */
    0,  /* CONNECTION => nothing */
    0,  /*     STREAM => nothing */
    0,  /*      COLON => nothing */
    1,  /*      ABORT => ID */
    1,  /*      AFTER => ID */
    1,  /*     ATTACH => ID */
    1,  /*     BEFORE => ID */
    1,  /*      BEGIN => ID */
    1,  /*    CASCADE => ID */
    1,  /*    CLUSTER => ID */
    1,  /*   CONFLICT => ID */
    1,  /*       COPY => ID */
    1,  /*   DEFERRED => ID */
    1,  /* DELIMITERS => ID */
    1,  /*     DETACH => ID */
    1,  /*       EACH => ID */
    1,  /*        END => ID */
    1,  /*    EXPLAIN => ID */
    1,  /*       FAIL => ID */
    1,  /*        FOR => ID */
    1,  /*     IGNORE => ID */
    1,  /*  IMMEDIATE => ID */
    1,  /*  INITIALLY => ID */
    1,  /*    INSTEAD => ID */
    1,  /*      MATCH => ID */
    1,  /*        KEY => ID */
    1,  /*         OF => ID */
    1,  /*      RAISE => ID */
    1,  /*    REPLACE => ID */
    1,  /*   RESTRICT => ID */
    1,  /*        ROW => ID */
    1,  /*  STATEMENT => ID */
    1,  /*    TRIGGER => ID */
    1,  /*       VIEW => ID */
    1,  /*      COUNT => ID */
    1,  /*        SUM => ID */
    1,  /*        AVG => ID */
    1,  /*        MIN => ID */
    1,  /*        MAX => ID */
    1,  /*      FIRST => ID */
    1,  /*       LAST => ID */
    1,  /*        TOP => ID */
    1,  /*     BOTTOM => ID */
    1,  /*     STDDEV => ID */
    1,  /* PERCENTILE => ID */
    1,  /* APERCENTILE => ID */
    1,  /* LEASTSQUARES => ID */
    1,  /*  HISTOGRAM => ID */
    1,  /*       DIFF => ID */
    1,  /*     SPREAD => ID */
    1,  /*        TWA => ID */
    1,  /*     INTERP => ID */
    1,  /*   LAST_ROW => ID */
    1,  /*       RATE => ID */
    1,  /*      IRATE => ID */
    1,  /*   SUM_RATE => ID */
    1,  /*  SUM_IRATE => ID */
    1,  /*   AVG_RATE => ID */
    1,  /*  AVG_IRATE => ID */
    1,  /*       TBID => ID */
    1,  /*       SEMI => ID */
    1,  /*       NONE => ID */
    1,  /*       PREV => ID */
    1,  /*     LINEAR => ID */
    1,  /*     IMPORT => ID */
    1,  /*     METRIC => ID */
    1,  /*     TBNAME => ID */
    1,  /*       JOIN => ID */
    1,  /*    METRICS => ID */
    1,  /*     STABLE => ID */
    1,  /*     INSERT => ID */
    1,  /*       INTO => ID */
    1,  /*     VALUES => ID */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
  ParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "ID",
  /*    2 */ "BOOL",
  /*    3 */ "TINYINT",
  /*    4 */ "SMALLINT",
  /*    5 */ "INTEGER",
  /*    6 */ "BIGINT",
  /*    7 */ "FLOAT",
  /*    8 */ "DOUBLE",
  /*    9 */ "STRING",
  /*   10 */ "TIMESTAMP",
  /*   11 */ "BINARY",
  /*   12 */ "NCHAR",
  /*   13 */ "OR",
  /*   14 */ "AND",
  /*   15 */ "NOT",
  /*   16 */ "EQ",
  /*   17 */ "NE",
  /*   18 */ "ISNULL",
  /*   19 */ "NOTNULL",
  /*   20 */ "IS",
  /*   21 */ "LIKE",
  /*   22 */ "GLOB",
  /*   23 */ "BETWEEN",
  /*   24 */ "IN",
  /*   25 */ "GT",
  /*   26 */ "GE",
  /*   27 */ "LT",
  /*   28 */ "LE",
  /*   29 */ "BITAND",
  /*   30 */ "BITOR",
  /*   31 */ "LSHIFT",
  /*   32 */ "RSHIFT",
  /*   33 */ "PLUS",
  /*   34 */ "MINUS",
  /*   35 */ "DIVIDE",
  /*   36 */ "TIMES",
  /*   37 */ "STAR",
  /*   38 */ "SLASH",
  /*   39 */ "REM",
  /*   40 */ "CONCAT",
  /*   41 */ "UMINUS",
  /*   42 */ "UPLUS",
  /*   43 */ "BITNOT",
  /*   44 */ "SHOW",
  /*   45 */ "DATABASES",
  /*   46 */ "MNODES",
  /*   47 */ "DNODES",
  /*   48 */ "ACCOUNTS",
  /*   49 */ "USERS",
  /*   50 */ "MODULES",
  /*   51 */ "QUERIES",
  /*   52 */ "CONNECTIONS",
  /*   53 */ "STREAMS",
  /*   54 */ "VARIABLES",
  /*   55 */ "SCORES",
  /*   56 */ "GRANTS",
  /*   57 */ "VNODES",
  /*   58 */ "IPTOKEN",
  /*   59 */ "DOT",
  /*   60 */ "TABLES",
  /*   61 */ "STABLES",
  /*   62 */ "VGROUPS",
  /*   63 */ "DROP",
  /*   64 */ "TABLE",
  /*   65 */ "DATABASE",
  /*   66 */ "DNODE",
  /*   67 */ "USER",
  /*   68 */ "ACCOUNT",
  /*   69 */ "USE",
  /*   70 */ "DESCRIBE",
  /*   71 */ "ALTER",
  /*   72 */ "PASS",
  /*   73 */ "PRIVILEGE",
  /*   74 */ "LOCAL",
  /*   75 */ "IF",
  /*   76 */ "EXISTS",
  /*   77 */ "CREATE",
  /*   78 */ "PPS",
  /*   79 */ "TSERIES",
  /*   80 */ "DBS",
  /*   81 */ "STORAGE",
  /*   82 */ "QTIME",
  /*   83 */ "CONNS",
  /*   84 */ "STATE",
  /*   85 */ "KEEP",
  /*   86 */ "CACHE",
  /*   87 */ "REPLICA",
  /*   88 */ "QUORUM",
  /*   89 */ "DAYS",
  /*   90 */ "MINROWS",
  /*   91 */ "MAXROWS",
  /*   92 */ "BLOCKS",
  /*   93 */ "CTIME",
  /*   94 */ "WAL",
  /*   95 */ "FSYNC",
  /*   96 */ "COMP",
  /*   97 */ "PRECISION",
  /*   98 */ "LP",
  /*   99 */ "RP",
  /*  100 */ "TAGS",
  /*  101 */ "USING",
  /*  102 */ "AS",
  /*  103 */ "COMMA",
  /*  104 */ "NULL",
  /*  105 */ "SELECT",
  /*  106 */ "UNION",
  /*  107 */ "ALL",
  /*  108 */ "FROM",
  /*  109 */ "VARIABLE",
  /*  110 */ "INTERVAL",
  /*  111 */ "FILL",
  /*  112 */ "SLIDING",
  /*  113 */ "ORDER",
  /*  114 */ "BY",
  /*  115 */ "ASC",
  /*  116 */ "DESC",
  /*  117 */ "GROUP",
  /*  118 */ "HAVING",
  /*  119 */ "LIMIT",
  /*  120 */ "OFFSET",
  /*  121 */ "SLIMIT",
  /*  122 */ "SOFFSET",
  /*  123 */ "WHERE",
  /*  124 */ "NOW",
  /*  125 */ "RESET",
  /*  126 */ "QUERY",
  /*  127 */ "ADD",
  /*  128 */ "COLUMN",
  /*  129 */ "TAG",
  /*  130 */ "CHANGE",
  /*  131 */ "SET",
  /*  132 */ "KILL",
  /*  133 */ "CONNECTION",
  /*  134 */ "STREAM",
  /*  135 */ "COLON",
  /*  136 */ "ABORT",
  /*  137 */ "AFTER",
  /*  138 */ "ATTACH",
  /*  139 */ "BEFORE",
  /*  140 */ "BEGIN",
  /*  141 */ "CASCADE",
  /*  142 */ "CLUSTER",
  /*  143 */ "CONFLICT",
  /*  144 */ "COPY",
  /*  145 */ "DEFERRED",
  /*  146 */ "DELIMITERS",
  /*  147 */ "DETACH",
  /*  148 */ "EACH",
  /*  149 */ "END",
  /*  150 */ "EXPLAIN",
  /*  151 */ "FAIL",
  /*  152 */ "FOR",
  /*  153 */ "IGNORE",
  /*  154 */ "IMMEDIATE",
  /*  155 */ "INITIALLY",
  /*  156 */ "INSTEAD",
  /*  157 */ "MATCH",
  /*  158 */ "KEY",
  /*  159 */ "OF",
  /*  160 */ "RAISE",
  /*  161 */ "REPLACE",
  /*  162 */ "RESTRICT",
  /*  163 */ "ROW",
  /*  164 */ "STATEMENT",
  /*  165 */ "TRIGGER",
  /*  166 */ "VIEW",
  /*  167 */ "COUNT",
  /*  168 */ "SUM",
  /*  169 */ "AVG",
  /*  170 */ "MIN",
  /*  171 */ "MAX",
  /*  172 */ "FIRST",
  /*  173 */ "LAST",
  /*  174 */ "TOP",
  /*  175 */ "BOTTOM",
  /*  176 */ "STDDEV",
  /*  177 */ "PERCENTILE",
  /*  178 */ "APERCENTILE",
  /*  179 */ "LEASTSQUARES",
  /*  180 */ "HISTOGRAM",
  /*  181 */ "DIFF",
  /*  182 */ "SPREAD",
  /*  183 */ "TWA",
  /*  184 */ "INTERP",
  /*  185 */ "LAST_ROW",
  /*  186 */ "RATE",
  /*  187 */ "IRATE",
  /*  188 */ "SUM_RATE",
  /*  189 */ "SUM_IRATE",
  /*  190 */ "AVG_RATE",
  /*  191 */ "AVG_IRATE",
  /*  192 */ "TBID",
  /*  193 */ "SEMI",
  /*  194 */ "NONE",
  /*  195 */ "PREV",
  /*  196 */ "LINEAR",
  /*  197 */ "IMPORT",
  /*  198 */ "METRIC",
  /*  199 */ "TBNAME",
  /*  200 */ "JOIN",
  /*  201 */ "METRICS",
  /*  202 */ "STABLE",
  /*  203 */ "INSERT",
  /*  204 */ "INTO",
  /*  205 */ "VALUES",
  /*  206 */ "program",
  /*  207 */ "cmd",
  /*  208 */ "dbPrefix",
  /*  209 */ "ids",
  /*  210 */ "cpxName",
  /*  211 */ "ifexists",
  /*  212 */ "alter_db_optr",
  /*  213 */ "acct_optr",
  /*  214 */ "ifnotexists",
  /*  215 */ "db_optr",
  /*  216 */ "pps",
  /*  217 */ "tseries",
  /*  218 */ "dbs",
  /*  219 */ "streams",
  /*  220 */ "storage",
  /*  221 */ "qtime",
  /*  222 */ "users",
  /*  223 */ "conns",
  /*  224 */ "state",
  /*  225 */ "keep",
  /*  226 */ "tagitemlist",
  /*  227 */ "cache",
  /*  228 */ "replica",
  /*  229 */ "quorum",
  /*  230 */ "days",
  /*  231 */ "minrows",
  /*  232 */ "maxrows",
  /*  233 */ "blocks",
  /*  234 */ "ctime",
  /*  235 */ "wal",
  /*  236 */ "fsync",
  /*  237 */ "comp",
  /*  238 */ "prec",
  /*  239 */ "typename",
  /*  240 */ "signed",
  /*  241 */ "create_table_args",
  /*  242 */ "columnlist",
  /*  243 */ "select",
  /*  244 */ "column",
  /*  245 */ "tagitem",
  /*  246 */ "selcollist",
  /*  247 */ "from",
  /*  248 */ "where_opt",
  /*  249 */ "interval_opt",
  /*  250 */ "fill_opt",
  /*  251 */ "sliding_opt",
  /*  252 */ "groupby_opt",
  /*  253 */ "orderby_opt",
  /*  254 */ "having_opt",
  /*  255 */ "slimit_opt",
  /*  256 */ "limit_opt",
  /*  257 */ "union",
  /*  258 */ "sclp",
  /*  259 */ "expr",
  /*  260 */ "as",
  /*  261 */ "tablelist",
  /*  262 */ "tmvar",
  /*  263 */ "sortlist",
  /*  264 */ "sortitem",
  /*  265 */ "item",
  /*  266 */ "sortorder",
  /*  267 */ "grouplist",
  /*  268 */ "exprlist",
  /*  269 */ "expritem",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= cmd",
 /*   1 */ "cmd ::= SHOW DATABASES",
 /*   2 */ "cmd ::= SHOW MNODES",
 /*   3 */ "cmd ::= SHOW DNODES",
 /*   4 */ "cmd ::= SHOW ACCOUNTS",
 /*   5 */ "cmd ::= SHOW USERS",
 /*   6 */ "cmd ::= SHOW MODULES",
 /*   7 */ "cmd ::= SHOW QUERIES",
 /*   8 */ "cmd ::= SHOW CONNECTIONS",
 /*   9 */ "cmd ::= SHOW STREAMS",
 /*  10 */ "cmd ::= SHOW VARIABLES",
 /*  11 */ "cmd ::= SHOW SCORES",
 /*  12 */ "cmd ::= SHOW GRANTS",
 /*  13 */ "cmd ::= SHOW VNODES",
 /*  14 */ "cmd ::= SHOW VNODES IPTOKEN",
 /*  15 */ "dbPrefix ::=",
 /*  16 */ "dbPrefix ::= ids DOT",
 /*  17 */ "cpxName ::=",
 /*  18 */ "cpxName ::= DOT ids",
 /*  19 */ "cmd ::= SHOW dbPrefix TABLES",
 /*  20 */ "cmd ::= SHOW dbPrefix TABLES LIKE ids",
 /*  21 */ "cmd ::= SHOW dbPrefix STABLES",
 /*  22 */ "cmd ::= SHOW dbPrefix STABLES LIKE ids",
 /*  23 */ "cmd ::= SHOW dbPrefix VGROUPS",
 /*  24 */ "cmd ::= SHOW dbPrefix VGROUPS ids",
 /*  25 */ "cmd ::= DROP TABLE ifexists ids cpxName",
 /*  26 */ "cmd ::= DROP DATABASE ifexists ids",
 /*  27 */ "cmd ::= DROP DNODE ids",
 /*  28 */ "cmd ::= DROP USER ids",
 /*  29 */ "cmd ::= DROP ACCOUNT ids",
 /*  30 */ "cmd ::= USE ids",
 /*  31 */ "cmd ::= DESCRIBE ids cpxName",
 /*  32 */ "cmd ::= ALTER USER ids PASS ids",
 /*  33 */ "cmd ::= ALTER USER ids PRIVILEGE ids",
 /*  34 */ "cmd ::= ALTER DNODE ids ids",
 /*  35 */ "cmd ::= ALTER DNODE ids ids ids",
 /*  36 */ "cmd ::= ALTER LOCAL ids",
 /*  37 */ "cmd ::= ALTER LOCAL ids ids",
 /*  38 */ "cmd ::= ALTER DATABASE ids alter_db_optr",
 /*  39 */ "cmd ::= ALTER ACCOUNT ids acct_optr",
 /*  40 */ "cmd ::= ALTER ACCOUNT ids PASS ids acct_optr",
 /*  41 */ "ids ::= ID",
 /*  42 */ "ids ::= STRING",
 /*  43 */ "ifexists ::= IF EXISTS",
 /*  44 */ "ifexists ::=",
 /*  45 */ "ifnotexists ::= IF NOT EXISTS",
 /*  46 */ "ifnotexists ::=",
 /*  47 */ "cmd ::= CREATE DNODE ids",
 /*  48 */ "cmd ::= CREATE ACCOUNT ids PASS ids acct_optr",
 /*  49 */ "cmd ::= CREATE DATABASE ifnotexists ids db_optr",
 /*  50 */ "cmd ::= CREATE USER ids PASS ids",
 /*  51 */ "pps ::=",
 /*  52 */ "pps ::= PPS INTEGER",
 /*  53 */ "tseries ::=",
 /*  54 */ "tseries ::= TSERIES INTEGER",
 /*  55 */ "dbs ::=",
 /*  56 */ "dbs ::= DBS INTEGER",
 /*  57 */ "streams ::=",
 /*  58 */ "streams ::= STREAMS INTEGER",
 /*  59 */ "storage ::=",
 /*  60 */ "storage ::= STORAGE INTEGER",
 /*  61 */ "qtime ::=",
 /*  62 */ "qtime ::= QTIME INTEGER",
 /*  63 */ "users ::=",
 /*  64 */ "users ::= USERS INTEGER",
 /*  65 */ "conns ::=",
 /*  66 */ "conns ::= CONNS INTEGER",
 /*  67 */ "state ::=",
 /*  68 */ "state ::= STATE ids",
 /*  69 */ "acct_optr ::= pps tseries storage streams qtime dbs users conns state",
 /*  70 */ "keep ::= KEEP tagitemlist",
 /*  71 */ "cache ::= CACHE INTEGER",
 /*  72 */ "replica ::= REPLICA INTEGER",
 /*  73 */ "quorum ::= QUORUM INTEGER",
 /*  74 */ "days ::= DAYS INTEGER",
 /*  75 */ "minrows ::= MINROWS INTEGER",
 /*  76 */ "maxrows ::= MAXROWS INTEGER",
 /*  77 */ "blocks ::= BLOCKS INTEGER",
 /*  78 */ "ctime ::= CTIME INTEGER",
 /*  79 */ "wal ::= WAL INTEGER",
 /*  80 */ "fsync ::= FSYNC INTEGER",
 /*  81 */ "comp ::= COMP INTEGER",
 /*  82 */ "prec ::= PRECISION STRING",
 /*  83 */ "db_optr ::=",
 /*  84 */ "db_optr ::= db_optr cache",
 /*  85 */ "db_optr ::= db_optr replica",
 /*  86 */ "db_optr ::= db_optr quorum",
 /*  87 */ "db_optr ::= db_optr days",
 /*  88 */ "db_optr ::= db_optr minrows",
 /*  89 */ "db_optr ::= db_optr maxrows",
 /*  90 */ "db_optr ::= db_optr blocks",
 /*  91 */ "db_optr ::= db_optr ctime",
 /*  92 */ "db_optr ::= db_optr wal",
 /*  93 */ "db_optr ::= db_optr fsync",
 /*  94 */ "db_optr ::= db_optr comp",
 /*  95 */ "db_optr ::= db_optr prec",
 /*  96 */ "db_optr ::= db_optr keep",
 /*  97 */ "alter_db_optr ::=",
 /*  98 */ "alter_db_optr ::= alter_db_optr replica",
 /*  99 */ "alter_db_optr ::= alter_db_optr quorum",
 /* 100 */ "alter_db_optr ::= alter_db_optr keep",
 /* 101 */ "alter_db_optr ::= alter_db_optr blocks",
 /* 102 */ "alter_db_optr ::= alter_db_optr comp",
 /* 103 */ "alter_db_optr ::= alter_db_optr wal",
 /* 104 */ "alter_db_optr ::= alter_db_optr fsync",
 /* 105 */ "typename ::= ids",
 /* 106 */ "typename ::= ids LP signed RP",
 /* 107 */ "signed ::= INTEGER",
 /* 108 */ "signed ::= PLUS INTEGER",
 /* 109 */ "signed ::= MINUS INTEGER",
 /* 110 */ "cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args",
 /* 111 */ "create_table_args ::= LP columnlist RP",
 /* 112 */ "create_table_args ::= LP columnlist RP TAGS LP columnlist RP",
 /* 113 */ "create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP",
 /* 114 */ "create_table_args ::= AS select",
 /* 115 */ "columnlist ::= columnlist COMMA column",
 /* 116 */ "columnlist ::= column",
 /* 117 */ "column ::= ids typename",
 /* 118 */ "tagitemlist ::= tagitemlist COMMA tagitem",
 /* 119 */ "tagitemlist ::= tagitem",
 /* 120 */ "tagitem ::= INTEGER",
 /* 121 */ "tagitem ::= FLOAT",
 /* 122 */ "tagitem ::= STRING",
 /* 123 */ "tagitem ::= BOOL",
 /* 124 */ "tagitem ::= NULL",
 /* 125 */ "tagitem ::= MINUS INTEGER",
 /* 126 */ "tagitem ::= MINUS FLOAT",
 /* 127 */ "tagitem ::= PLUS INTEGER",
 /* 128 */ "tagitem ::= PLUS FLOAT",
 /* 129 */ "select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt",
 /* 130 */ "union ::= select",
 /* 131 */ "union ::= LP union RP",
 /* 132 */ "union ::= union UNION ALL select",
 /* 133 */ "union ::= union UNION ALL LP select RP",
 /* 134 */ "cmd ::= union",
 /* 135 */ "select ::= SELECT selcollist",
 /* 136 */ "sclp ::= selcollist COMMA",
 /* 137 */ "sclp ::=",
 /* 138 */ "selcollist ::= sclp expr as",
 /* 139 */ "selcollist ::= sclp STAR",
 /* 140 */ "as ::= AS ids",
 /* 141 */ "as ::= ids",
 /* 142 */ "as ::=",
 /* 143 */ "from ::= FROM tablelist",
 /* 144 */ "tablelist ::= ids cpxName",
 /* 145 */ "tablelist ::= ids cpxName ids",
 /* 146 */ "tablelist ::= tablelist COMMA ids cpxName",
 /* 147 */ "tablelist ::= tablelist COMMA ids cpxName ids",
 /* 148 */ "tmvar ::= VARIABLE",
 /* 149 */ "interval_opt ::= INTERVAL LP tmvar RP",
 /* 150 */ "interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP",
 /* 151 */ "interval_opt ::=",
 /* 152 */ "fill_opt ::=",
 /* 153 */ "fill_opt ::= FILL LP ID COMMA tagitemlist RP",
 /* 154 */ "fill_opt ::= FILL LP ID RP",
 /* 155 */ "sliding_opt ::= SLIDING LP tmvar RP",
 /* 156 */ "sliding_opt ::=",
 /* 157 */ "orderby_opt ::=",
 /* 158 */ "orderby_opt ::= ORDER BY sortlist",
 /* 159 */ "sortlist ::= sortlist COMMA item sortorder",
 /* 160 */ "sortlist ::= item sortorder",
 /* 161 */ "item ::= ids cpxName",
 /* 162 */ "sortorder ::= ASC",
 /* 163 */ "sortorder ::= DESC",
 /* 164 */ "sortorder ::=",
 /* 165 */ "groupby_opt ::=",
 /* 166 */ "groupby_opt ::= GROUP BY grouplist",
 /* 167 */ "grouplist ::= grouplist COMMA item",
 /* 168 */ "grouplist ::= item",
 /* 169 */ "having_opt ::=",
 /* 170 */ "having_opt ::= HAVING expr",
 /* 171 */ "limit_opt ::=",
 /* 172 */ "limit_opt ::= LIMIT signed",
 /* 173 */ "limit_opt ::= LIMIT signed OFFSET signed",
 /* 174 */ "limit_opt ::= LIMIT signed COMMA signed",
 /* 175 */ "slimit_opt ::=",
 /* 176 */ "slimit_opt ::= SLIMIT signed",
 /* 177 */ "slimit_opt ::= SLIMIT signed SOFFSET signed",
 /* 178 */ "slimit_opt ::= SLIMIT signed COMMA signed",
 /* 179 */ "where_opt ::=",
 /* 180 */ "where_opt ::= WHERE expr",
 /* 181 */ "expr ::= LP expr RP",
 /* 182 */ "expr ::= ID",
 /* 183 */ "expr ::= ID DOT ID",
 /* 184 */ "expr ::= ID DOT STAR",
 /* 185 */ "expr ::= INTEGER",
 /* 186 */ "expr ::= MINUS INTEGER",
 /* 187 */ "expr ::= PLUS INTEGER",
 /* 188 */ "expr ::= FLOAT",
 /* 189 */ "expr ::= MINUS FLOAT",
 /* 190 */ "expr ::= PLUS FLOAT",
 /* 191 */ "expr ::= STRING",
 /* 192 */ "expr ::= NOW",
 /* 193 */ "expr ::= VARIABLE",
 /* 194 */ "expr ::= BOOL",
 /* 195 */ "expr ::= ID LP exprlist RP",
 /* 196 */ "expr ::= ID LP STAR RP",
 /* 197 */ "expr ::= expr AND expr",
 /* 198 */ "expr ::= expr OR expr",
 /* 199 */ "expr ::= expr LT expr",
 /* 200 */ "expr ::= expr GT expr",
 /* 201 */ "expr ::= expr LE expr",
 /* 202 */ "expr ::= expr GE expr",
 /* 203 */ "expr ::= expr NE expr",
 /* 204 */ "expr ::= expr EQ expr",
 /* 205 */ "expr ::= expr PLUS expr",
 /* 206 */ "expr ::= expr MINUS expr",
 /* 207 */ "expr ::= expr STAR expr",
 /* 208 */ "expr ::= expr SLASH expr",
 /* 209 */ "expr ::= expr REM expr",
 /* 210 */ "expr ::= expr LIKE expr",
 /* 211 */ "expr ::= expr IN LP exprlist RP",
 /* 212 */ "exprlist ::= exprlist COMMA expritem",
 /* 213 */ "exprlist ::= expritem",
 /* 214 */ "expritem ::= expr",
 /* 215 */ "expritem ::=",
 /* 216 */ "cmd ::= RESET QUERY CACHE",
 /* 217 */ "cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist",
 /* 218 */ "cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids",
 /* 219 */ "cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist",
 /* 220 */ "cmd ::= ALTER TABLE ids cpxName DROP TAG ids",
 /* 221 */ "cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids",
 /* 222 */ "cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem",
 /* 223 */ "cmd ::= KILL CONNECTION INTEGER",
 /* 224 */ "cmd ::= KILL STREAM INTEGER COLON INTEGER",
 /* 225 */ "cmd ::= KILL QUERY INTEGER COLON INTEGER",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypRawParser ParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ParseCTX_STORE
    ParseInit(yypParser ParseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH
  ParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 225: /* keep */
    case 226: /* tagitemlist */
    case 250: /* fill_opt */
    case 252: /* groupby_opt */
    case 253: /* orderby_opt */
    case 263: /* sortlist */
    case 267: /* grouplist */
{
tVariantListDestroy((yypminor->yy156));
}
      break;
    case 242: /* columnlist */
{
tFieldListDestroy((yypminor->yy511));
}
      break;
    case 243: /* select */
{
doDestroyQuerySql((yypminor->yy444));
}
      break;
    case 246: /* selcollist */
    case 258: /* sclp */
    case 268: /* exprlist */
{
tSQLExprListDestroy((yypminor->yy158));
}
      break;
    case 248: /* where_opt */
    case 254: /* having_opt */
    case 259: /* expr */
    case 269: /* expritem */
{
tSQLExprDestroy((yypminor->yy190));
}
      break;
    case 257: /* union */
{
destroyAllSelectClause((yypminor->yy333));
}
      break;
    case 264: /* sortitem */
{
tVariantDestroy(&(yypminor->yy506));
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    assert( i<=YY_ACTTAB_COUNT );
    assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    assert( i<(int)YY_NLOOKAHEAD );
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      assert( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0]) );
      iFallback = yyFallback[iLookAhead];
      if( iFallback!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        assert( j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) );
        if( yy_lookahead[j]==YYWILDCARD && iLookAhead>0 ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      assert( i>=0 && i<sizeof(yy_action)/sizeof(yy_action[0]) );
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH
   ParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
   206,  /* (0) program ::= cmd */
   207,  /* (1) cmd ::= SHOW DATABASES */
   207,  /* (2) cmd ::= SHOW MNODES */
   207,  /* (3) cmd ::= SHOW DNODES */
   207,  /* (4) cmd ::= SHOW ACCOUNTS */
   207,  /* (5) cmd ::= SHOW USERS */
   207,  /* (6) cmd ::= SHOW MODULES */
   207,  /* (7) cmd ::= SHOW QUERIES */
   207,  /* (8) cmd ::= SHOW CONNECTIONS */
   207,  /* (9) cmd ::= SHOW STREAMS */
   207,  /* (10) cmd ::= SHOW VARIABLES */
   207,  /* (11) cmd ::= SHOW SCORES */
   207,  /* (12) cmd ::= SHOW GRANTS */
   207,  /* (13) cmd ::= SHOW VNODES */
   207,  /* (14) cmd ::= SHOW VNODES IPTOKEN */
   208,  /* (15) dbPrefix ::= */
   208,  /* (16) dbPrefix ::= ids DOT */
   210,  /* (17) cpxName ::= */
   210,  /* (18) cpxName ::= DOT ids */
   207,  /* (19) cmd ::= SHOW dbPrefix TABLES */
   207,  /* (20) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   207,  /* (21) cmd ::= SHOW dbPrefix STABLES */
   207,  /* (22) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   207,  /* (23) cmd ::= SHOW dbPrefix VGROUPS */
   207,  /* (24) cmd ::= SHOW dbPrefix VGROUPS ids */
   207,  /* (25) cmd ::= DROP TABLE ifexists ids cpxName */
   207,  /* (26) cmd ::= DROP DATABASE ifexists ids */
   207,  /* (27) cmd ::= DROP DNODE ids */
   207,  /* (28) cmd ::= DROP USER ids */
   207,  /* (29) cmd ::= DROP ACCOUNT ids */
   207,  /* (30) cmd ::= USE ids */
   207,  /* (31) cmd ::= DESCRIBE ids cpxName */
   207,  /* (32) cmd ::= ALTER USER ids PASS ids */
   207,  /* (33) cmd ::= ALTER USER ids PRIVILEGE ids */
   207,  /* (34) cmd ::= ALTER DNODE ids ids */
   207,  /* (35) cmd ::= ALTER DNODE ids ids ids */
   207,  /* (36) cmd ::= ALTER LOCAL ids */
   207,  /* (37) cmd ::= ALTER LOCAL ids ids */
   207,  /* (38) cmd ::= ALTER DATABASE ids alter_db_optr */
   207,  /* (39) cmd ::= ALTER ACCOUNT ids acct_optr */
   207,  /* (40) cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
   209,  /* (41) ids ::= ID */
   209,  /* (42) ids ::= STRING */
   211,  /* (43) ifexists ::= IF EXISTS */
   211,  /* (44) ifexists ::= */
   214,  /* (45) ifnotexists ::= IF NOT EXISTS */
   214,  /* (46) ifnotexists ::= */
   207,  /* (47) cmd ::= CREATE DNODE ids */
   207,  /* (48) cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
   207,  /* (49) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   207,  /* (50) cmd ::= CREATE USER ids PASS ids */
   216,  /* (51) pps ::= */
   216,  /* (52) pps ::= PPS INTEGER */
   217,  /* (53) tseries ::= */
   217,  /* (54) tseries ::= TSERIES INTEGER */
   218,  /* (55) dbs ::= */
   218,  /* (56) dbs ::= DBS INTEGER */
   219,  /* (57) streams ::= */
   219,  /* (58) streams ::= STREAMS INTEGER */
   220,  /* (59) storage ::= */
   220,  /* (60) storage ::= STORAGE INTEGER */
   221,  /* (61) qtime ::= */
   221,  /* (62) qtime ::= QTIME INTEGER */
   222,  /* (63) users ::= */
   222,  /* (64) users ::= USERS INTEGER */
   223,  /* (65) conns ::= */
   223,  /* (66) conns ::= CONNS INTEGER */
   224,  /* (67) state ::= */
   224,  /* (68) state ::= STATE ids */
   213,  /* (69) acct_optr ::= pps tseries storage streams qtime dbs users conns state */
   225,  /* (70) keep ::= KEEP tagitemlist */
   227,  /* (71) cache ::= CACHE INTEGER */
   228,  /* (72) replica ::= REPLICA INTEGER */
   229,  /* (73) quorum ::= QUORUM INTEGER */
   230,  /* (74) days ::= DAYS INTEGER */
   231,  /* (75) minrows ::= MINROWS INTEGER */
   232,  /* (76) maxrows ::= MAXROWS INTEGER */
   233,  /* (77) blocks ::= BLOCKS INTEGER */
   234,  /* (78) ctime ::= CTIME INTEGER */
   235,  /* (79) wal ::= WAL INTEGER */
   236,  /* (80) fsync ::= FSYNC INTEGER */
   237,  /* (81) comp ::= COMP INTEGER */
   238,  /* (82) prec ::= PRECISION STRING */
   215,  /* (83) db_optr ::= */
   215,  /* (84) db_optr ::= db_optr cache */
   215,  /* (85) db_optr ::= db_optr replica */
   215,  /* (86) db_optr ::= db_optr quorum */
   215,  /* (87) db_optr ::= db_optr days */
   215,  /* (88) db_optr ::= db_optr minrows */
   215,  /* (89) db_optr ::= db_optr maxrows */
   215,  /* (90) db_optr ::= db_optr blocks */
   215,  /* (91) db_optr ::= db_optr ctime */
   215,  /* (92) db_optr ::= db_optr wal */
   215,  /* (93) db_optr ::= db_optr fsync */
   215,  /* (94) db_optr ::= db_optr comp */
   215,  /* (95) db_optr ::= db_optr prec */
   215,  /* (96) db_optr ::= db_optr keep */
   212,  /* (97) alter_db_optr ::= */
   212,  /* (98) alter_db_optr ::= alter_db_optr replica */
   212,  /* (99) alter_db_optr ::= alter_db_optr quorum */
   212,  /* (100) alter_db_optr ::= alter_db_optr keep */
   212,  /* (101) alter_db_optr ::= alter_db_optr blocks */
   212,  /* (102) alter_db_optr ::= alter_db_optr comp */
   212,  /* (103) alter_db_optr ::= alter_db_optr wal */
   212,  /* (104) alter_db_optr ::= alter_db_optr fsync */
   239,  /* (105) typename ::= ids */
   239,  /* (106) typename ::= ids LP signed RP */
   240,  /* (107) signed ::= INTEGER */
   240,  /* (108) signed ::= PLUS INTEGER */
   240,  /* (109) signed ::= MINUS INTEGER */
   207,  /* (110) cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
   241,  /* (111) create_table_args ::= LP columnlist RP */
   241,  /* (112) create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
   241,  /* (113) create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
   241,  /* (114) create_table_args ::= AS select */
   242,  /* (115) columnlist ::= columnlist COMMA column */
   242,  /* (116) columnlist ::= column */
   244,  /* (117) column ::= ids typename */
   226,  /* (118) tagitemlist ::= tagitemlist COMMA tagitem */
   226,  /* (119) tagitemlist ::= tagitem */
   245,  /* (120) tagitem ::= INTEGER */
   245,  /* (121) tagitem ::= FLOAT */
   245,  /* (122) tagitem ::= STRING */
   245,  /* (123) tagitem ::= BOOL */
   245,  /* (124) tagitem ::= NULL */
   245,  /* (125) tagitem ::= MINUS INTEGER */
   245,  /* (126) tagitem ::= MINUS FLOAT */
   245,  /* (127) tagitem ::= PLUS INTEGER */
   245,  /* (128) tagitem ::= PLUS FLOAT */
   243,  /* (129) select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
   257,  /* (130) union ::= select */
   257,  /* (131) union ::= LP union RP */
   257,  /* (132) union ::= union UNION ALL select */
   257,  /* (133) union ::= union UNION ALL LP select RP */
   207,  /* (134) cmd ::= union */
   243,  /* (135) select ::= SELECT selcollist */
   258,  /* (136) sclp ::= selcollist COMMA */
   258,  /* (137) sclp ::= */
   246,  /* (138) selcollist ::= sclp expr as */
   246,  /* (139) selcollist ::= sclp STAR */
   260,  /* (140) as ::= AS ids */
   260,  /* (141) as ::= ids */
   260,  /* (142) as ::= */
   247,  /* (143) from ::= FROM tablelist */
   261,  /* (144) tablelist ::= ids cpxName */
   261,  /* (145) tablelist ::= ids cpxName ids */
   261,  /* (146) tablelist ::= tablelist COMMA ids cpxName */
   261,  /* (147) tablelist ::= tablelist COMMA ids cpxName ids */
   262,  /* (148) tmvar ::= VARIABLE */
   249,  /* (149) interval_opt ::= INTERVAL LP tmvar RP */
   249,  /* (150) interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
   249,  /* (151) interval_opt ::= */
   250,  /* (152) fill_opt ::= */
   250,  /* (153) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   250,  /* (154) fill_opt ::= FILL LP ID RP */
   251,  /* (155) sliding_opt ::= SLIDING LP tmvar RP */
   251,  /* (156) sliding_opt ::= */
   253,  /* (157) orderby_opt ::= */
   253,  /* (158) orderby_opt ::= ORDER BY sortlist */
   263,  /* (159) sortlist ::= sortlist COMMA item sortorder */
   263,  /* (160) sortlist ::= item sortorder */
   265,  /* (161) item ::= ids cpxName */
   266,  /* (162) sortorder ::= ASC */
   266,  /* (163) sortorder ::= DESC */
   266,  /* (164) sortorder ::= */
   252,  /* (165) groupby_opt ::= */
   252,  /* (166) groupby_opt ::= GROUP BY grouplist */
   267,  /* (167) grouplist ::= grouplist COMMA item */
   267,  /* (168) grouplist ::= item */
   254,  /* (169) having_opt ::= */
   254,  /* (170) having_opt ::= HAVING expr */
   256,  /* (171) limit_opt ::= */
   256,  /* (172) limit_opt ::= LIMIT signed */
   256,  /* (173) limit_opt ::= LIMIT signed OFFSET signed */
   256,  /* (174) limit_opt ::= LIMIT signed COMMA signed */
   255,  /* (175) slimit_opt ::= */
   255,  /* (176) slimit_opt ::= SLIMIT signed */
   255,  /* (177) slimit_opt ::= SLIMIT signed SOFFSET signed */
   255,  /* (178) slimit_opt ::= SLIMIT signed COMMA signed */
   248,  /* (179) where_opt ::= */
   248,  /* (180) where_opt ::= WHERE expr */
   259,  /* (181) expr ::= LP expr RP */
   259,  /* (182) expr ::= ID */
   259,  /* (183) expr ::= ID DOT ID */
   259,  /* (184) expr ::= ID DOT STAR */
   259,  /* (185) expr ::= INTEGER */
   259,  /* (186) expr ::= MINUS INTEGER */
   259,  /* (187) expr ::= PLUS INTEGER */
   259,  /* (188) expr ::= FLOAT */
   259,  /* (189) expr ::= MINUS FLOAT */
   259,  /* (190) expr ::= PLUS FLOAT */
   259,  /* (191) expr ::= STRING */
   259,  /* (192) expr ::= NOW */
   259,  /* (193) expr ::= VARIABLE */
   259,  /* (194) expr ::= BOOL */
   259,  /* (195) expr ::= ID LP exprlist RP */
   259,  /* (196) expr ::= ID LP STAR RP */
   259,  /* (197) expr ::= expr AND expr */
   259,  /* (198) expr ::= expr OR expr */
   259,  /* (199) expr ::= expr LT expr */
   259,  /* (200) expr ::= expr GT expr */
   259,  /* (201) expr ::= expr LE expr */
   259,  /* (202) expr ::= expr GE expr */
   259,  /* (203) expr ::= expr NE expr */
   259,  /* (204) expr ::= expr EQ expr */
   259,  /* (205) expr ::= expr PLUS expr */
   259,  /* (206) expr ::= expr MINUS expr */
   259,  /* (207) expr ::= expr STAR expr */
   259,  /* (208) expr ::= expr SLASH expr */
   259,  /* (209) expr ::= expr REM expr */
   259,  /* (210) expr ::= expr LIKE expr */
   259,  /* (211) expr ::= expr IN LP exprlist RP */
   268,  /* (212) exprlist ::= exprlist COMMA expritem */
   268,  /* (213) exprlist ::= expritem */
   269,  /* (214) expritem ::= expr */
   269,  /* (215) expritem ::= */
   207,  /* (216) cmd ::= RESET QUERY CACHE */
   207,  /* (217) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   207,  /* (218) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   207,  /* (219) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   207,  /* (220) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   207,  /* (221) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   207,  /* (222) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   207,  /* (223) cmd ::= KILL CONNECTION INTEGER */
   207,  /* (224) cmd ::= KILL STREAM INTEGER COLON INTEGER */
   207,  /* (225) cmd ::= KILL QUERY INTEGER COLON INTEGER */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -1,  /* (0) program ::= cmd */
   -2,  /* (1) cmd ::= SHOW DATABASES */
   -2,  /* (2) cmd ::= SHOW MNODES */
   -2,  /* (3) cmd ::= SHOW DNODES */
   -2,  /* (4) cmd ::= SHOW ACCOUNTS */
   -2,  /* (5) cmd ::= SHOW USERS */
   -2,  /* (6) cmd ::= SHOW MODULES */
   -2,  /* (7) cmd ::= SHOW QUERIES */
   -2,  /* (8) cmd ::= SHOW CONNECTIONS */
   -2,  /* (9) cmd ::= SHOW STREAMS */
   -2,  /* (10) cmd ::= SHOW VARIABLES */
   -2,  /* (11) cmd ::= SHOW SCORES */
   -2,  /* (12) cmd ::= SHOW GRANTS */
   -2,  /* (13) cmd ::= SHOW VNODES */
   -3,  /* (14) cmd ::= SHOW VNODES IPTOKEN */
    0,  /* (15) dbPrefix ::= */
   -2,  /* (16) dbPrefix ::= ids DOT */
    0,  /* (17) cpxName ::= */
   -2,  /* (18) cpxName ::= DOT ids */
   -3,  /* (19) cmd ::= SHOW dbPrefix TABLES */
   -5,  /* (20) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   -3,  /* (21) cmd ::= SHOW dbPrefix STABLES */
   -5,  /* (22) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   -3,  /* (23) cmd ::= SHOW dbPrefix VGROUPS */
   -4,  /* (24) cmd ::= SHOW dbPrefix VGROUPS ids */
   -5,  /* (25) cmd ::= DROP TABLE ifexists ids cpxName */
   -4,  /* (26) cmd ::= DROP DATABASE ifexists ids */
   -3,  /* (27) cmd ::= DROP DNODE ids */
   -3,  /* (28) cmd ::= DROP USER ids */
   -3,  /* (29) cmd ::= DROP ACCOUNT ids */
   -2,  /* (30) cmd ::= USE ids */
   -3,  /* (31) cmd ::= DESCRIBE ids cpxName */
   -5,  /* (32) cmd ::= ALTER USER ids PASS ids */
   -5,  /* (33) cmd ::= ALTER USER ids PRIVILEGE ids */
   -4,  /* (34) cmd ::= ALTER DNODE ids ids */
   -5,  /* (35) cmd ::= ALTER DNODE ids ids ids */
   -3,  /* (36) cmd ::= ALTER LOCAL ids */
   -4,  /* (37) cmd ::= ALTER LOCAL ids ids */
   -4,  /* (38) cmd ::= ALTER DATABASE ids alter_db_optr */
   -4,  /* (39) cmd ::= ALTER ACCOUNT ids acct_optr */
   -6,  /* (40) cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
   -1,  /* (41) ids ::= ID */
   -1,  /* (42) ids ::= STRING */
   -2,  /* (43) ifexists ::= IF EXISTS */
    0,  /* (44) ifexists ::= */
   -3,  /* (45) ifnotexists ::= IF NOT EXISTS */
    0,  /* (46) ifnotexists ::= */
   -3,  /* (47) cmd ::= CREATE DNODE ids */
   -6,  /* (48) cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
   -5,  /* (49) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   -5,  /* (50) cmd ::= CREATE USER ids PASS ids */
    0,  /* (51) pps ::= */
   -2,  /* (52) pps ::= PPS INTEGER */
    0,  /* (53) tseries ::= */
   -2,  /* (54) tseries ::= TSERIES INTEGER */
    0,  /* (55) dbs ::= */
   -2,  /* (56) dbs ::= DBS INTEGER */
    0,  /* (57) streams ::= */
   -2,  /* (58) streams ::= STREAMS INTEGER */
    0,  /* (59) storage ::= */
   -2,  /* (60) storage ::= STORAGE INTEGER */
    0,  /* (61) qtime ::= */
   -2,  /* (62) qtime ::= QTIME INTEGER */
    0,  /* (63) users ::= */
   -2,  /* (64) users ::= USERS INTEGER */
    0,  /* (65) conns ::= */
   -2,  /* (66) conns ::= CONNS INTEGER */
    0,  /* (67) state ::= */
   -2,  /* (68) state ::= STATE ids */
   -9,  /* (69) acct_optr ::= pps tseries storage streams qtime dbs users conns state */
   -2,  /* (70) keep ::= KEEP tagitemlist */
   -2,  /* (71) cache ::= CACHE INTEGER */
   -2,  /* (72) replica ::= REPLICA INTEGER */
   -2,  /* (73) quorum ::= QUORUM INTEGER */
   -2,  /* (74) days ::= DAYS INTEGER */
   -2,  /* (75) minrows ::= MINROWS INTEGER */
   -2,  /* (76) maxrows ::= MAXROWS INTEGER */
   -2,  /* (77) blocks ::= BLOCKS INTEGER */
   -2,  /* (78) ctime ::= CTIME INTEGER */
   -2,  /* (79) wal ::= WAL INTEGER */
   -2,  /* (80) fsync ::= FSYNC INTEGER */
   -2,  /* (81) comp ::= COMP INTEGER */
   -2,  /* (82) prec ::= PRECISION STRING */
    0,  /* (83) db_optr ::= */
   -2,  /* (84) db_optr ::= db_optr cache */
   -2,  /* (85) db_optr ::= db_optr replica */
   -2,  /* (86) db_optr ::= db_optr quorum */
   -2,  /* (87) db_optr ::= db_optr days */
   -2,  /* (88) db_optr ::= db_optr minrows */
   -2,  /* (89) db_optr ::= db_optr maxrows */
   -2,  /* (90) db_optr ::= db_optr blocks */
   -2,  /* (91) db_optr ::= db_optr ctime */
   -2,  /* (92) db_optr ::= db_optr wal */
   -2,  /* (93) db_optr ::= db_optr fsync */
   -2,  /* (94) db_optr ::= db_optr comp */
   -2,  /* (95) db_optr ::= db_optr prec */
   -2,  /* (96) db_optr ::= db_optr keep */
    0,  /* (97) alter_db_optr ::= */
   -2,  /* (98) alter_db_optr ::= alter_db_optr replica */
   -2,  /* (99) alter_db_optr ::= alter_db_optr quorum */
   -2,  /* (100) alter_db_optr ::= alter_db_optr keep */
   -2,  /* (101) alter_db_optr ::= alter_db_optr blocks */
   -2,  /* (102) alter_db_optr ::= alter_db_optr comp */
   -2,  /* (103) alter_db_optr ::= alter_db_optr wal */
   -2,  /* (104) alter_db_optr ::= alter_db_optr fsync */
   -1,  /* (105) typename ::= ids */
   -4,  /* (106) typename ::= ids LP signed RP */
   -1,  /* (107) signed ::= INTEGER */
   -2,  /* (108) signed ::= PLUS INTEGER */
   -2,  /* (109) signed ::= MINUS INTEGER */
   -6,  /* (110) cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
   -3,  /* (111) create_table_args ::= LP columnlist RP */
   -7,  /* (112) create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
   -7,  /* (113) create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
   -2,  /* (114) create_table_args ::= AS select */
   -3,  /* (115) columnlist ::= columnlist COMMA column */
   -1,  /* (116) columnlist ::= column */
   -2,  /* (117) column ::= ids typename */
   -3,  /* (118) tagitemlist ::= tagitemlist COMMA tagitem */
   -1,  /* (119) tagitemlist ::= tagitem */
   -1,  /* (120) tagitem ::= INTEGER */
   -1,  /* (121) tagitem ::= FLOAT */
   -1,  /* (122) tagitem ::= STRING */
   -1,  /* (123) tagitem ::= BOOL */
   -1,  /* (124) tagitem ::= NULL */
   -2,  /* (125) tagitem ::= MINUS INTEGER */
   -2,  /* (126) tagitem ::= MINUS FLOAT */
   -2,  /* (127) tagitem ::= PLUS INTEGER */
   -2,  /* (128) tagitem ::= PLUS FLOAT */
  -12,  /* (129) select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
   -1,  /* (130) union ::= select */
   -3,  /* (131) union ::= LP union RP */
   -4,  /* (132) union ::= union UNION ALL select */
   -6,  /* (133) union ::= union UNION ALL LP select RP */
   -1,  /* (134) cmd ::= union */
   -2,  /* (135) select ::= SELECT selcollist */
   -2,  /* (136) sclp ::= selcollist COMMA */
    0,  /* (137) sclp ::= */
   -3,  /* (138) selcollist ::= sclp expr as */
   -2,  /* (139) selcollist ::= sclp STAR */
   -2,  /* (140) as ::= AS ids */
   -1,  /* (141) as ::= ids */
    0,  /* (142) as ::= */
   -2,  /* (143) from ::= FROM tablelist */
   -2,  /* (144) tablelist ::= ids cpxName */
   -3,  /* (145) tablelist ::= ids cpxName ids */
   -4,  /* (146) tablelist ::= tablelist COMMA ids cpxName */
   -5,  /* (147) tablelist ::= tablelist COMMA ids cpxName ids */
   -1,  /* (148) tmvar ::= VARIABLE */
   -4,  /* (149) interval_opt ::= INTERVAL LP tmvar RP */
   -6,  /* (150) interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
    0,  /* (151) interval_opt ::= */
    0,  /* (152) fill_opt ::= */
   -6,  /* (153) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   -4,  /* (154) fill_opt ::= FILL LP ID RP */
   -4,  /* (155) sliding_opt ::= SLIDING LP tmvar RP */
    0,  /* (156) sliding_opt ::= */
    0,  /* (157) orderby_opt ::= */
   -3,  /* (158) orderby_opt ::= ORDER BY sortlist */
   -4,  /* (159) sortlist ::= sortlist COMMA item sortorder */
   -2,  /* (160) sortlist ::= item sortorder */
   -2,  /* (161) item ::= ids cpxName */
   -1,  /* (162) sortorder ::= ASC */
   -1,  /* (163) sortorder ::= DESC */
    0,  /* (164) sortorder ::= */
    0,  /* (165) groupby_opt ::= */
   -3,  /* (166) groupby_opt ::= GROUP BY grouplist */
   -3,  /* (167) grouplist ::= grouplist COMMA item */
   -1,  /* (168) grouplist ::= item */
    0,  /* (169) having_opt ::= */
   -2,  /* (170) having_opt ::= HAVING expr */
    0,  /* (171) limit_opt ::= */
   -2,  /* (172) limit_opt ::= LIMIT signed */
   -4,  /* (173) limit_opt ::= LIMIT signed OFFSET signed */
   -4,  /* (174) limit_opt ::= LIMIT signed COMMA signed */
    0,  /* (175) slimit_opt ::= */
   -2,  /* (176) slimit_opt ::= SLIMIT signed */
   -4,  /* (177) slimit_opt ::= SLIMIT signed SOFFSET signed */
   -4,  /* (178) slimit_opt ::= SLIMIT signed COMMA signed */
    0,  /* (179) where_opt ::= */
   -2,  /* (180) where_opt ::= WHERE expr */
   -3,  /* (181) expr ::= LP expr RP */
   -1,  /* (182) expr ::= ID */
   -3,  /* (183) expr ::= ID DOT ID */
   -3,  /* (184) expr ::= ID DOT STAR */
   -1,  /* (185) expr ::= INTEGER */
   -2,  /* (186) expr ::= MINUS INTEGER */
   -2,  /* (187) expr ::= PLUS INTEGER */
   -1,  /* (188) expr ::= FLOAT */
   -2,  /* (189) expr ::= MINUS FLOAT */
   -2,  /* (190) expr ::= PLUS FLOAT */
   -1,  /* (191) expr ::= STRING */
   -1,  /* (192) expr ::= NOW */
   -1,  /* (193) expr ::= VARIABLE */
   -1,  /* (194) expr ::= BOOL */
   -4,  /* (195) expr ::= ID LP exprlist RP */
   -4,  /* (196) expr ::= ID LP STAR RP */
   -3,  /* (197) expr ::= expr AND expr */
   -3,  /* (198) expr ::= expr OR expr */
   -3,  /* (199) expr ::= expr LT expr */
   -3,  /* (200) expr ::= expr GT expr */
   -3,  /* (201) expr ::= expr LE expr */
   -3,  /* (202) expr ::= expr GE expr */
   -3,  /* (203) expr ::= expr NE expr */
   -3,  /* (204) expr ::= expr EQ expr */
   -3,  /* (205) expr ::= expr PLUS expr */
   -3,  /* (206) expr ::= expr MINUS expr */
   -3,  /* (207) expr ::= expr STAR expr */
   -3,  /* (208) expr ::= expr SLASH expr */
   -3,  /* (209) expr ::= expr REM expr */
   -3,  /* (210) expr ::= expr LIKE expr */
   -5,  /* (211) expr ::= expr IN LP exprlist RP */
   -3,  /* (212) exprlist ::= exprlist COMMA expritem */
   -1,  /* (213) exprlist ::= expritem */
   -1,  /* (214) expritem ::= expr */
    0,  /* (215) expritem ::= */
   -3,  /* (216) cmd ::= RESET QUERY CACHE */
   -7,  /* (217) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   -7,  /* (218) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   -7,  /* (219) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   -7,  /* (220) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   -8,  /* (221) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   -9,  /* (222) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   -3,  /* (223) cmd ::= KILL CONNECTION INTEGER */
   -5,  /* (224) cmd ::= KILL STREAM INTEGER COLON INTEGER */
   -5,  /* (225) cmd ::= KILL QUERY INTEGER COLON INTEGER */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s, pop back to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action",
        yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s]%s.\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno],
        yyruleno<YYNRULE_WITH_ACTION ? "" : " without external action");
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= cmd */
{}
        break;
      case 1: /* cmd ::= SHOW DATABASES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DB, 0, 0);}
        break;
      case 2: /* cmd ::= SHOW MNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MNODE, 0, 0);}
        break;
      case 3: /* cmd ::= SHOW DNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_DNODE, 0, 0);}
        break;
      case 4: /* cmd ::= SHOW ACCOUNTS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_ACCT, 0, 0);}
        break;
      case 5: /* cmd ::= SHOW USERS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_USER, 0, 0);}
        break;
      case 6: /* cmd ::= SHOW MODULES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_MODULE, 0, 0);  }
        break;
      case 7: /* cmd ::= SHOW QUERIES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_QUERIES, 0, 0);  }
        break;
      case 8: /* cmd ::= SHOW CONNECTIONS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_CONNS, 0, 0);}
        break;
      case 9: /* cmd ::= SHOW STREAMS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_STREAMS, 0, 0);  }
        break;
      case 10: /* cmd ::= SHOW VARIABLES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VARIABLES, 0, 0);  }
        break;
      case 11: /* cmd ::= SHOW SCORES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_SCORES, 0, 0);   }
        break;
      case 12: /* cmd ::= SHOW GRANTS */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_GRANTS, 0, 0);   }
        break;
      case 13: /* cmd ::= SHOW VNODES */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, 0, 0); }
        break;
      case 14: /* cmd ::= SHOW VNODES IPTOKEN */
{ setShowOptions(pInfo, TSDB_MGMT_TABLE_VNODES, &yymsp[0].minor.yy0, 0); }
        break;
      case 15: /* dbPrefix ::= */
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.type = 0;}
        break;
      case 16: /* dbPrefix ::= ids DOT */
{yylhsminor.yy0 = yymsp[-1].minor.yy0;  }
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 17: /* cpxName ::= */
{yymsp[1].minor.yy0.n = 0;  }
        break;
      case 18: /* cpxName ::= DOT ids */
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; yymsp[-1].minor.yy0.n += 1;    }
        break;
      case 19: /* cmd ::= SHOW dbPrefix TABLES */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-1].minor.yy0, 0);
}
        break;
      case 20: /* cmd ::= SHOW dbPrefix TABLES LIKE ids */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_TABLE, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0);
}
        break;
      case 21: /* cmd ::= SHOW dbPrefix STABLES */
{
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &yymsp[-1].minor.yy0, 0);
}
        break;
      case 22: /* cmd ::= SHOW dbPrefix STABLES LIKE ids */
{
    SStrToken token;
    setDBName(&token, &yymsp[-3].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_METRIC, &token, &yymsp[0].minor.yy0);
}
        break;
      case 23: /* cmd ::= SHOW dbPrefix VGROUPS */
{
    SStrToken token;
    setDBName(&token, &yymsp[-1].minor.yy0);
    setShowOptions(pInfo, TSDB_MGMT_TABLE_VGROUP, &token, 0);
}
        break;
      case 24: /* cmd ::= SHOW dbPrefix VGROUPS ids */
{
    SStrToken token;
    setDBName(&token, &yymsp[-2].minor.yy0);    
    setShowOptions(pInfo, TSDB_MGMT_TABLE_VGROUP, &token, &yymsp[0].minor.yy0);
}
        break;
      case 25: /* cmd ::= DROP TABLE ifexists ids cpxName */
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDropDBTableInfo(pInfo, TSDB_SQL_DROP_TABLE, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0);
}
        break;
      case 26: /* cmd ::= DROP DATABASE ifexists ids */
{ setDropDBTableInfo(pInfo, TSDB_SQL_DROP_DB, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0); }
        break;
      case 27: /* cmd ::= DROP DNODE ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_DROP_DNODE, 1, &yymsp[0].minor.yy0);    }
        break;
      case 28: /* cmd ::= DROP USER ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_DROP_USER, 1, &yymsp[0].minor.yy0);     }
        break;
      case 29: /* cmd ::= DROP ACCOUNT ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_DROP_ACCT, 1, &yymsp[0].minor.yy0);  }
        break;
      case 30: /* cmd ::= USE ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_USE_DB, 1, &yymsp[0].minor.yy0);}
        break;
      case 31: /* cmd ::= DESCRIBE ids cpxName */
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDCLSQLElems(pInfo, TSDB_SQL_DESCRIBE_TABLE, 1, &yymsp[-1].minor.yy0);
}
        break;
      case 32: /* cmd ::= ALTER USER ids PASS ids */
{ setAlterUserSQL(pInfo, TSDB_ALTER_USER_PASSWD, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0, NULL);    }
        break;
      case 33: /* cmd ::= ALTER USER ids PRIVILEGE ids */
{ setAlterUserSQL(pInfo, TSDB_ALTER_USER_PRIVILEGES, &yymsp[-2].minor.yy0, NULL, &yymsp[0].minor.yy0);}
        break;
      case 34: /* cmd ::= ALTER DNODE ids ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_CFG_DNODE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
        break;
      case 35: /* cmd ::= ALTER DNODE ids ids ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_CFG_DNODE, 3, &yymsp[-2].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);      }
        break;
      case 36: /* cmd ::= ALTER LOCAL ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_CFG_LOCAL, 1, &yymsp[0].minor.yy0);              }
        break;
      case 37: /* cmd ::= ALTER LOCAL ids ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_CFG_LOCAL, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
        break;
      case 38: /* cmd ::= ALTER DATABASE ids alter_db_optr */
{ SStrToken t = {0};  setCreateDBSQL(pInfo, TSDB_SQL_ALTER_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy118, &t);}
        break;
      case 39: /* cmd ::= ALTER ACCOUNT ids acct_optr */
{ setCreateAcctSQL(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-1].minor.yy0, NULL, &yymsp[0].minor.yy479);}
        break;
      case 40: /* cmd ::= ALTER ACCOUNT ids PASS ids acct_optr */
{ setCreateAcctSQL(pInfo, TSDB_SQL_ALTER_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy479);}
        break;
      case 41: /* ids ::= ID */
      case 42: /* ids ::= STRING */ yytestcase(yyruleno==42);
{yylhsminor.yy0 = yymsp[0].minor.yy0; }
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 43: /* ifexists ::= IF EXISTS */
{yymsp[-1].minor.yy0.n = 1;}
        break;
      case 44: /* ifexists ::= */
      case 46: /* ifnotexists ::= */ yytestcase(yyruleno==46);
{yymsp[1].minor.yy0.n = 0;}
        break;
      case 45: /* ifnotexists ::= IF NOT EXISTS */
{yymsp[-2].minor.yy0.n = 1;}
        break;
      case 47: /* cmd ::= CREATE DNODE ids */
{ setDCLSQLElems(pInfo, TSDB_SQL_CREATE_DNODE, 1, &yymsp[0].minor.yy0);}
        break;
      case 48: /* cmd ::= CREATE ACCOUNT ids PASS ids acct_optr */
{ setCreateAcctSQL(pInfo, TSDB_SQL_CREATE_ACCT, &yymsp[-3].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy479);}
        break;
      case 49: /* cmd ::= CREATE DATABASE ifnotexists ids db_optr */
{ setCreateDBSQL(pInfo, TSDB_SQL_CREATE_DB, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy118, &yymsp[-2].minor.yy0);}
        break;
      case 50: /* cmd ::= CREATE USER ids PASS ids */
{ setCreateUserSQL(pInfo, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);}
        break;
      case 51: /* pps ::= */
      case 53: /* tseries ::= */ yytestcase(yyruleno==53);
      case 55: /* dbs ::= */ yytestcase(yyruleno==55);
      case 57: /* streams ::= */ yytestcase(yyruleno==57);
      case 59: /* storage ::= */ yytestcase(yyruleno==59);
      case 61: /* qtime ::= */ yytestcase(yyruleno==61);
      case 63: /* users ::= */ yytestcase(yyruleno==63);
      case 65: /* conns ::= */ yytestcase(yyruleno==65);
      case 67: /* state ::= */ yytestcase(yyruleno==67);
{yymsp[1].minor.yy0.n = 0;   }
        break;
      case 52: /* pps ::= PPS INTEGER */
      case 54: /* tseries ::= TSERIES INTEGER */ yytestcase(yyruleno==54);
      case 56: /* dbs ::= DBS INTEGER */ yytestcase(yyruleno==56);
      case 58: /* streams ::= STREAMS INTEGER */ yytestcase(yyruleno==58);
      case 60: /* storage ::= STORAGE INTEGER */ yytestcase(yyruleno==60);
      case 62: /* qtime ::= QTIME INTEGER */ yytestcase(yyruleno==62);
      case 64: /* users ::= USERS INTEGER */ yytestcase(yyruleno==64);
      case 66: /* conns ::= CONNS INTEGER */ yytestcase(yyruleno==66);
      case 68: /* state ::= STATE ids */ yytestcase(yyruleno==68);
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;     }
        break;
      case 69: /* acct_optr ::= pps tseries storage streams qtime dbs users conns state */
{
    yylhsminor.yy479.maxUsers   = (yymsp[-2].minor.yy0.n>0)?atoi(yymsp[-2].minor.yy0.z):-1;
    yylhsminor.yy479.maxDbs     = (yymsp[-3].minor.yy0.n>0)?atoi(yymsp[-3].minor.yy0.z):-1;
    yylhsminor.yy479.maxTimeSeries = (yymsp[-7].minor.yy0.n>0)?atoi(yymsp[-7].minor.yy0.z):-1;
    yylhsminor.yy479.maxStreams = (yymsp[-5].minor.yy0.n>0)?atoi(yymsp[-5].minor.yy0.z):-1;
    yylhsminor.yy479.maxPointsPerSecond     = (yymsp[-8].minor.yy0.n>0)?atoi(yymsp[-8].minor.yy0.z):-1;
    yylhsminor.yy479.maxStorage = (yymsp[-6].minor.yy0.n>0)?strtoll(yymsp[-6].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy479.maxQueryTime   = (yymsp[-4].minor.yy0.n>0)?strtoll(yymsp[-4].minor.yy0.z, NULL, 10):-1;
    yylhsminor.yy479.maxConnections   = (yymsp[-1].minor.yy0.n>0)?atoi(yymsp[-1].minor.yy0.z):-1;
    yylhsminor.yy479.stat    = yymsp[0].minor.yy0;
}
  yymsp[-8].minor.yy479 = yylhsminor.yy479;
        break;
      case 70: /* keep ::= KEEP tagitemlist */
{ yymsp[-1].minor.yy156 = yymsp[0].minor.yy156; }
        break;
      case 71: /* cache ::= CACHE INTEGER */
      case 72: /* replica ::= REPLICA INTEGER */ yytestcase(yyruleno==72);
      case 73: /* quorum ::= QUORUM INTEGER */ yytestcase(yyruleno==73);
      case 74: /* days ::= DAYS INTEGER */ yytestcase(yyruleno==74);
      case 75: /* minrows ::= MINROWS INTEGER */ yytestcase(yyruleno==75);
      case 76: /* maxrows ::= MAXROWS INTEGER */ yytestcase(yyruleno==76);
      case 77: /* blocks ::= BLOCKS INTEGER */ yytestcase(yyruleno==77);
      case 78: /* ctime ::= CTIME INTEGER */ yytestcase(yyruleno==78);
      case 79: /* wal ::= WAL INTEGER */ yytestcase(yyruleno==79);
      case 80: /* fsync ::= FSYNC INTEGER */ yytestcase(yyruleno==80);
      case 81: /* comp ::= COMP INTEGER */ yytestcase(yyruleno==81);
      case 82: /* prec ::= PRECISION STRING */ yytestcase(yyruleno==82);
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; }
        break;
      case 83: /* db_optr ::= */
{setDefaultCreateDbOption(&yymsp[1].minor.yy118);}
        break;
      case 84: /* db_optr ::= db_optr cache */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.cacheBlockSize = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 85: /* db_optr ::= db_optr replica */
      case 98: /* alter_db_optr ::= alter_db_optr replica */ yytestcase(yyruleno==98);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.replica = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 86: /* db_optr ::= db_optr quorum */
      case 99: /* alter_db_optr ::= alter_db_optr quorum */ yytestcase(yyruleno==99);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.quorum = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 87: /* db_optr ::= db_optr days */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.daysPerFile = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 88: /* db_optr ::= db_optr minrows */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.minRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 89: /* db_optr ::= db_optr maxrows */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.maxRowsPerBlock = strtod(yymsp[0].minor.yy0.z, NULL); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 90: /* db_optr ::= db_optr blocks */
      case 101: /* alter_db_optr ::= alter_db_optr blocks */ yytestcase(yyruleno==101);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.numOfBlocks = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 91: /* db_optr ::= db_optr ctime */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.commitTime = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 92: /* db_optr ::= db_optr wal */
      case 103: /* alter_db_optr ::= alter_db_optr wal */ yytestcase(yyruleno==103);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.walLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 93: /* db_optr ::= db_optr fsync */
      case 104: /* alter_db_optr ::= alter_db_optr fsync */ yytestcase(yyruleno==104);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.fsyncPeriod = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 94: /* db_optr ::= db_optr comp */
      case 102: /* alter_db_optr ::= alter_db_optr comp */ yytestcase(yyruleno==102);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.compressionLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 95: /* db_optr ::= db_optr prec */
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.precision = yymsp[0].minor.yy0; }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 96: /* db_optr ::= db_optr keep */
      case 100: /* alter_db_optr ::= alter_db_optr keep */ yytestcase(yyruleno==100);
{ yylhsminor.yy118 = yymsp[-1].minor.yy118; yylhsminor.yy118.keep = yymsp[0].minor.yy156; }
  yymsp[-1].minor.yy118 = yylhsminor.yy118;
        break;
      case 97: /* alter_db_optr ::= */
{ setDefaultCreateDbOption(&yymsp[1].minor.yy118);}
        break;
      case 105: /* typename ::= ids */
{ 
  yymsp[0].minor.yy0.type = 0;
  tSQLSetColumnType (&yylhsminor.yy343, &yymsp[0].minor.yy0); 
}
  yymsp[0].minor.yy343 = yylhsminor.yy343;
        break;
      case 106: /* typename ::= ids LP signed RP */
{
    if (yymsp[-1].minor.yy369 <= 0) {
      yymsp[-3].minor.yy0.type = 0;
      tSQLSetColumnType(&yylhsminor.yy343, &yymsp[-3].minor.yy0);
    } else {
      yymsp[-3].minor.yy0.type = -yymsp[-1].minor.yy369;          // negative value of name length
      tSQLSetColumnType(&yylhsminor.yy343, &yymsp[-3].minor.yy0);
    }
}
  yymsp[-3].minor.yy343 = yylhsminor.yy343;
        break;
      case 107: /* signed ::= INTEGER */
{ yylhsminor.yy369 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
  yymsp[0].minor.yy369 = yylhsminor.yy369;
        break;
      case 108: /* signed ::= PLUS INTEGER */
{ yymsp[-1].minor.yy369 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
        break;
      case 109: /* signed ::= MINUS INTEGER */
{ yymsp[-1].minor.yy369 = -strtol(yymsp[0].minor.yy0.z, NULL, 10);}
        break;
      case 110: /* cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
{
    yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
    setCreatedTableName(pInfo, &yymsp[-2].minor.yy0, &yymsp[-3].minor.yy0);
}
        break;
      case 111: /* create_table_args ::= LP columnlist RP */
{
    yymsp[-2].minor.yy398 = tSetCreateSQLElems(yymsp[-1].minor.yy511, NULL, NULL, NULL, NULL, TSQL_CREATE_TABLE);
    setSQLInfo(pInfo, yymsp[-2].minor.yy398, NULL, TSDB_SQL_CREATE_TABLE);
}
        break;
      case 112: /* create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
{
    yymsp[-6].minor.yy398 = tSetCreateSQLElems(yymsp[-5].minor.yy511, yymsp[-1].minor.yy511, NULL, NULL, NULL, TSQL_CREATE_STABLE);
    setSQLInfo(pInfo, yymsp[-6].minor.yy398, NULL, TSDB_SQL_CREATE_TABLE);
}
        break;
      case 113: /* create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
    yymsp[-6].minor.yy398 = tSetCreateSQLElems(NULL, NULL, &yymsp[-5].minor.yy0, yymsp[-1].minor.yy156, NULL, TSQL_CREATE_TABLE_FROM_STABLE);
    setSQLInfo(pInfo, yymsp[-6].minor.yy398, NULL, TSDB_SQL_CREATE_TABLE);
}
        break;
      case 114: /* create_table_args ::= AS select */
{
    yymsp[-1].minor.yy398 = tSetCreateSQLElems(NULL, NULL, NULL, NULL, yymsp[0].minor.yy444, TSQL_CREATE_STREAM);
    setSQLInfo(pInfo, yymsp[-1].minor.yy398, NULL, TSDB_SQL_CREATE_TABLE);
}
        break;
      case 115: /* columnlist ::= columnlist COMMA column */
{yylhsminor.yy511 = tFieldListAppend(yymsp[-2].minor.yy511, &yymsp[0].minor.yy343);   }
  yymsp[-2].minor.yy511 = yylhsminor.yy511;
        break;
      case 116: /* columnlist ::= column */
{yylhsminor.yy511 = tFieldListAppend(NULL, &yymsp[0].minor.yy343);}
  yymsp[0].minor.yy511 = yylhsminor.yy511;
        break;
      case 117: /* column ::= ids typename */
{
    tSQLSetColumnInfo(&yylhsminor.yy343, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy343);
}
  yymsp[-1].minor.yy343 = yylhsminor.yy343;
        break;
      case 118: /* tagitemlist ::= tagitemlist COMMA tagitem */
{ yylhsminor.yy156 = tVariantListAppend(yymsp[-2].minor.yy156, &yymsp[0].minor.yy506, -1);    }
  yymsp[-2].minor.yy156 = yylhsminor.yy156;
        break;
      case 119: /* tagitemlist ::= tagitem */
{ yylhsminor.yy156 = tVariantListAppend(NULL, &yymsp[0].minor.yy506, -1); }
  yymsp[0].minor.yy156 = yylhsminor.yy156;
        break;
      case 120: /* tagitem ::= INTEGER */
      case 121: /* tagitem ::= FLOAT */ yytestcase(yyruleno==121);
      case 122: /* tagitem ::= STRING */ yytestcase(yyruleno==122);
      case 123: /* tagitem ::= BOOL */ yytestcase(yyruleno==123);
{toTSDBType(yymsp[0].minor.yy0.type); tVariantCreate(&yylhsminor.yy506, &yymsp[0].minor.yy0); }
  yymsp[0].minor.yy506 = yylhsminor.yy506;
        break;
      case 124: /* tagitem ::= NULL */
{ yymsp[0].minor.yy0.type = 0; tVariantCreate(&yylhsminor.yy506, &yymsp[0].minor.yy0); }
  yymsp[0].minor.yy506 = yylhsminor.yy506;
        break;
      case 125: /* tagitem ::= MINUS INTEGER */
      case 126: /* tagitem ::= MINUS FLOAT */ yytestcase(yyruleno==126);
      case 127: /* tagitem ::= PLUS INTEGER */ yytestcase(yyruleno==127);
      case 128: /* tagitem ::= PLUS FLOAT */ yytestcase(yyruleno==128);
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    yymsp[-1].minor.yy0.type = yymsp[0].minor.yy0.type;
    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantCreate(&yylhsminor.yy506, &yymsp[-1].minor.yy0);
}
  yymsp[-1].minor.yy506 = yylhsminor.yy506;
        break;
      case 129: /* select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
{
  yylhsminor.yy444 = tSetQuerySQLElems(&yymsp[-11].minor.yy0, yymsp[-10].minor.yy158, yymsp[-9].minor.yy156, yymsp[-8].minor.yy190, yymsp[-4].minor.yy156, yymsp[-3].minor.yy156, &yymsp[-7].minor.yy340, &yymsp[-5].minor.yy0, yymsp[-6].minor.yy156, &yymsp[0].minor.yy414, &yymsp[-1].minor.yy414);
}
  yymsp[-11].minor.yy444 = yylhsminor.yy444;
        break;
      case 130: /* union ::= select */
{ yylhsminor.yy333 = setSubclause(NULL, yymsp[0].minor.yy444); }
  yymsp[0].minor.yy333 = yylhsminor.yy333;
        break;
      case 131: /* union ::= LP union RP */
{ yymsp[-2].minor.yy333 = yymsp[-1].minor.yy333; }
        break;
      case 132: /* union ::= union UNION ALL select */
{ yylhsminor.yy333 = appendSelectClause(yymsp[-3].minor.yy333, yymsp[0].minor.yy444); }
  yymsp[-3].minor.yy333 = yylhsminor.yy333;
        break;
      case 133: /* union ::= union UNION ALL LP select RP */
{ yylhsminor.yy333 = appendSelectClause(yymsp[-5].minor.yy333, yymsp[-1].minor.yy444); }
  yymsp[-5].minor.yy333 = yylhsminor.yy333;
        break;
      case 134: /* cmd ::= union */
{ setSQLInfo(pInfo, yymsp[0].minor.yy333, NULL, TSDB_SQL_SELECT); }
        break;
      case 135: /* select ::= SELECT selcollist */
{
  yylhsminor.yy444 = tSetQuerySQLElems(&yymsp[-1].minor.yy0, yymsp[0].minor.yy158, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}
  yymsp[-1].minor.yy444 = yylhsminor.yy444;
        break;
      case 136: /* sclp ::= selcollist COMMA */
{yylhsminor.yy158 = yymsp[-1].minor.yy158;}
  yymsp[-1].minor.yy158 = yylhsminor.yy158;
        break;
      case 137: /* sclp ::= */
{yymsp[1].minor.yy158 = 0;}
        break;
      case 138: /* selcollist ::= sclp expr as */
{
   yylhsminor.yy158 = tSQLExprListAppend(yymsp[-2].minor.yy158, yymsp[-1].minor.yy190, yymsp[0].minor.yy0.n?&yymsp[0].minor.yy0:0);
}
  yymsp[-2].minor.yy158 = yylhsminor.yy158;
        break;
      case 139: /* selcollist ::= sclp STAR */
{
   tSQLExpr *pNode = tSQLExprIdValueCreate(NULL, TK_ALL);
   yylhsminor.yy158 = tSQLExprListAppend(yymsp[-1].minor.yy158, pNode, 0);
}
  yymsp[-1].minor.yy158 = yylhsminor.yy158;
        break;
      case 140: /* as ::= AS ids */
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;    }
        break;
      case 141: /* as ::= ids */
{ yylhsminor.yy0 = yymsp[0].minor.yy0;    }
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 142: /* as ::= */
{ yymsp[1].minor.yy0.n = 0;  }
        break;
      case 143: /* from ::= FROM tablelist */
{yymsp[-1].minor.yy156 = yymsp[0].minor.yy156;}
        break;
      case 144: /* tablelist ::= ids cpxName */
{
  toTSDBType(yymsp[-1].minor.yy0.type);
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy156 = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);
  yylhsminor.yy156 = tVariantListAppendToken(yylhsminor.yy156, &yymsp[-1].minor.yy0, -1);  // table alias name
}
  yymsp[-1].minor.yy156 = yylhsminor.yy156;
        break;
      case 145: /* tablelist ::= ids cpxName ids */
{
   toTSDBType(yymsp[-2].minor.yy0.type);
   toTSDBType(yymsp[0].minor.yy0.type);
   yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
   yylhsminor.yy156 = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1);
   yylhsminor.yy156 = tVariantListAppendToken(yylhsminor.yy156, &yymsp[0].minor.yy0, -1);
}
  yymsp[-2].minor.yy156 = yylhsminor.yy156;
        break;
      case 146: /* tablelist ::= tablelist COMMA ids cpxName */
{
  toTSDBType(yymsp[-1].minor.yy0.type);
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
  yylhsminor.yy156 = tVariantListAppendToken(yymsp[-3].minor.yy156, &yymsp[-1].minor.yy0, -1);
  yylhsminor.yy156 = tVariantListAppendToken(yylhsminor.yy156, &yymsp[-1].minor.yy0, -1);
}
  yymsp[-3].minor.yy156 = yylhsminor.yy156;
        break;
      case 147: /* tablelist ::= tablelist COMMA ids cpxName ids */
{
   toTSDBType(yymsp[-2].minor.yy0.type);
   toTSDBType(yymsp[0].minor.yy0.type);
   yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
   yylhsminor.yy156 = tVariantListAppendToken(yymsp[-4].minor.yy156, &yymsp[-2].minor.yy0, -1);
   yylhsminor.yy156 = tVariantListAppendToken(yylhsminor.yy156, &yymsp[0].minor.yy0, -1);
}
  yymsp[-4].minor.yy156 = yylhsminor.yy156;
        break;
      case 148: /* tmvar ::= VARIABLE */
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 149: /* interval_opt ::= INTERVAL LP tmvar RP */
{yymsp[-3].minor.yy340.interval = yymsp[-1].minor.yy0; yymsp[-3].minor.yy340.offset.n = 0; yymsp[-3].minor.yy340.offset.z = NULL; yymsp[-3].minor.yy340.offset.type = 0;}
        break;
      case 150: /* interval_opt ::= INTERVAL LP tmvar COMMA tmvar RP */
{yymsp[-5].minor.yy340.interval = yymsp[-3].minor.yy0; yymsp[-5].minor.yy340.offset = yymsp[-1].minor.yy0;}
        break;
      case 151: /* interval_opt ::= */
{memset(&yymsp[1].minor.yy340, 0, sizeof(yymsp[1].minor.yy340));}
        break;
      case 152: /* fill_opt ::= */
{yymsp[1].minor.yy156 = 0;     }
        break;
      case 153: /* fill_opt ::= FILL LP ID COMMA tagitemlist RP */
{
    tVariant A = {0};
    toTSDBType(yymsp[-3].minor.yy0.type);
    tVariantCreate(&A, &yymsp[-3].minor.yy0);

    tVariantListInsert(yymsp[-1].minor.yy156, &A, -1, 0);
    yymsp[-5].minor.yy156 = yymsp[-1].minor.yy156;
}
        break;
      case 154: /* fill_opt ::= FILL LP ID RP */
{
    toTSDBType(yymsp[-1].minor.yy0.type);
    yymsp[-3].minor.yy156 = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);
}
        break;
      case 155: /* sliding_opt ::= SLIDING LP tmvar RP */
{yymsp[-3].minor.yy0 = yymsp[-1].minor.yy0;     }
        break;
      case 156: /* sliding_opt ::= */
{yymsp[1].minor.yy0.n = 0; yymsp[1].minor.yy0.z = NULL; yymsp[1].minor.yy0.type = 0;   }
        break;
      case 157: /* orderby_opt ::= */
      case 165: /* groupby_opt ::= */ yytestcase(yyruleno==165);
{yymsp[1].minor.yy156 = 0;}
        break;
      case 158: /* orderby_opt ::= ORDER BY sortlist */
      case 166: /* groupby_opt ::= GROUP BY grouplist */ yytestcase(yyruleno==166);
{yymsp[-2].minor.yy156 = yymsp[0].minor.yy156;}
        break;
      case 159: /* sortlist ::= sortlist COMMA item sortorder */
{
    yylhsminor.yy156 = tVariantListAppend(yymsp[-3].minor.yy156, &yymsp[-1].minor.yy506, yymsp[0].minor.yy112);
}
  yymsp[-3].minor.yy156 = yylhsminor.yy156;
        break;
      case 160: /* sortlist ::= item sortorder */
{
  yylhsminor.yy156 = tVariantListAppend(NULL, &yymsp[-1].minor.yy506, yymsp[0].minor.yy112);
}
  yymsp[-1].minor.yy156 = yylhsminor.yy156;
        break;
      case 161: /* item ::= ids cpxName */
{
  toTSDBType(yymsp[-1].minor.yy0.type);
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;

  tVariantCreate(&yylhsminor.yy506, &yymsp[-1].minor.yy0);
}
  yymsp[-1].minor.yy506 = yylhsminor.yy506;
        break;
      case 162: /* sortorder ::= ASC */
{yymsp[0].minor.yy112 = TSDB_ORDER_ASC; }
        break;
      case 163: /* sortorder ::= DESC */
{yymsp[0].minor.yy112 = TSDB_ORDER_DESC;}
        break;
      case 164: /* sortorder ::= */
{yymsp[1].minor.yy112 = TSDB_ORDER_ASC;}
        break;
      case 167: /* grouplist ::= grouplist COMMA item */
{
  yylhsminor.yy156 = tVariantListAppend(yymsp[-2].minor.yy156, &yymsp[0].minor.yy506, -1);
}
  yymsp[-2].minor.yy156 = yylhsminor.yy156;
        break;
      case 168: /* grouplist ::= item */
{
  yylhsminor.yy156 = tVariantListAppend(NULL, &yymsp[0].minor.yy506, -1);
}
  yymsp[0].minor.yy156 = yylhsminor.yy156;
        break;
      case 169: /* having_opt ::= */
      case 179: /* where_opt ::= */ yytestcase(yyruleno==179);
      case 215: /* expritem ::= */ yytestcase(yyruleno==215);
{yymsp[1].minor.yy190 = 0;}
        break;
      case 170: /* having_opt ::= HAVING expr */
      case 180: /* where_opt ::= WHERE expr */ yytestcase(yyruleno==180);
{yymsp[-1].minor.yy190 = yymsp[0].minor.yy190;}
        break;
      case 171: /* limit_opt ::= */
      case 175: /* slimit_opt ::= */ yytestcase(yyruleno==175);
{yymsp[1].minor.yy414.limit = -1; yymsp[1].minor.yy414.offset = 0;}
        break;
      case 172: /* limit_opt ::= LIMIT signed */
      case 176: /* slimit_opt ::= SLIMIT signed */ yytestcase(yyruleno==176);
{yymsp[-1].minor.yy414.limit = yymsp[0].minor.yy369;  yymsp[-1].minor.yy414.offset = 0;}
        break;
      case 173: /* limit_opt ::= LIMIT signed OFFSET signed */
      case 177: /* slimit_opt ::= SLIMIT signed SOFFSET signed */ yytestcase(yyruleno==177);
{yymsp[-3].minor.yy414.limit = yymsp[-2].minor.yy369;  yymsp[-3].minor.yy414.offset = yymsp[0].minor.yy369;}
        break;
      case 174: /* limit_opt ::= LIMIT signed COMMA signed */
      case 178: /* slimit_opt ::= SLIMIT signed COMMA signed */ yytestcase(yyruleno==178);
{yymsp[-3].minor.yy414.limit = yymsp[0].minor.yy369;  yymsp[-3].minor.yy414.offset = yymsp[-2].minor.yy369;}
        break;
      case 181: /* expr ::= LP expr RP */
{yymsp[-2].minor.yy190 = yymsp[-1].minor.yy190; }
        break;
      case 182: /* expr ::= ID */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_ID);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 183: /* expr ::= ID DOT ID */
{yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[-2].minor.yy0, TK_ID);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 184: /* expr ::= ID DOT STAR */
{yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[-2].minor.yy0, TK_ALL);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 185: /* expr ::= INTEGER */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_INTEGER);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 186: /* expr ::= MINUS INTEGER */
      case 187: /* expr ::= PLUS INTEGER */ yytestcase(yyruleno==187);
{yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_INTEGER; yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[-1].minor.yy0, TK_INTEGER);}
  yymsp[-1].minor.yy190 = yylhsminor.yy190;
        break;
      case 188: /* expr ::= FLOAT */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_FLOAT);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 189: /* expr ::= MINUS FLOAT */
      case 190: /* expr ::= PLUS FLOAT */ yytestcase(yyruleno==190);
{yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_FLOAT; yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[-1].minor.yy0, TK_FLOAT);}
  yymsp[-1].minor.yy190 = yylhsminor.yy190;
        break;
      case 191: /* expr ::= STRING */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_STRING);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 192: /* expr ::= NOW */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_NOW); }
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 193: /* expr ::= VARIABLE */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_VARIABLE);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 194: /* expr ::= BOOL */
{yylhsminor.yy190 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_BOOL);}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 195: /* expr ::= ID LP exprlist RP */
{
  yylhsminor.yy190 = tSQLExprCreateFunction(yymsp[-1].minor.yy158, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type);
}
  yymsp[-3].minor.yy190 = yylhsminor.yy190;
        break;
      case 196: /* expr ::= ID LP STAR RP */
{
  yylhsminor.yy190 = tSQLExprCreateFunction(NULL, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type);
}
  yymsp[-3].minor.yy190 = yylhsminor.yy190;
        break;
      case 197: /* expr ::= expr AND expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_AND);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 198: /* expr ::= expr OR expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_OR); }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 199: /* expr ::= expr LT expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_LT);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 200: /* expr ::= expr GT expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_GT);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 201: /* expr ::= expr LE expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_LE);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 202: /* expr ::= expr GE expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_GE);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 203: /* expr ::= expr NE expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_NE);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 204: /* expr ::= expr EQ expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_EQ);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 205: /* expr ::= expr PLUS expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_PLUS);  }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 206: /* expr ::= expr MINUS expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_MINUS); }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 207: /* expr ::= expr STAR expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_STAR);  }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 208: /* expr ::= expr SLASH expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_DIVIDE);}
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 209: /* expr ::= expr REM expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_REM);   }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 210: /* expr ::= expr LIKE expr */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-2].minor.yy190, yymsp[0].minor.yy190, TK_LIKE);  }
  yymsp[-2].minor.yy190 = yylhsminor.yy190;
        break;
      case 211: /* expr ::= expr IN LP exprlist RP */
{yylhsminor.yy190 = tSQLExprCreate(yymsp[-4].minor.yy190, (tSQLExpr*)yymsp[-1].minor.yy158, TK_IN); }
  yymsp[-4].minor.yy190 = yylhsminor.yy190;
        break;
      case 212: /* exprlist ::= exprlist COMMA expritem */
{yylhsminor.yy158 = tSQLExprListAppend(yymsp[-2].minor.yy158,yymsp[0].minor.yy190,0);}
  yymsp[-2].minor.yy158 = yylhsminor.yy158;
        break;
      case 213: /* exprlist ::= expritem */
{yylhsminor.yy158 = tSQLExprListAppend(0,yymsp[0].minor.yy190,0);}
  yymsp[0].minor.yy158 = yylhsminor.yy158;
        break;
      case 214: /* expritem ::= expr */
{yylhsminor.yy190 = yymsp[0].minor.yy190;}
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 216: /* cmd ::= RESET QUERY CACHE */
{ setDCLSQLElems(pInfo, TSDB_SQL_RESET_CACHE, 0);}
        break;
      case 217: /* cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, yymsp[0].minor.yy511, NULL, TSDB_ALTER_TABLE_ADD_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 218: /* cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    tVariantList* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, NULL, K, TSDB_ALTER_TABLE_DROP_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 219: /* cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, yymsp[0].minor.yy511, NULL, TSDB_ALTER_TABLE_ADD_TAG_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 220: /* cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, NULL, A, TSDB_ALTER_TABLE_DROP_TAG_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 221: /* cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-5].minor.yy0, NULL, A, TSDB_ALTER_TABLE_CHANGE_TAG_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 222: /* cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1);
    A = tVariantListAppend(A, &yymsp[0].minor.yy506, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-6].minor.yy0, NULL, A, TSDB_ALTER_TABLE_UPDATE_TAG_VAL);
    setSQLInfo(pInfo, pAlterTable, NULL, TSDB_SQL_ALTER_TABLE);
}
        break;
      case 223: /* cmd ::= KILL CONNECTION INTEGER */
{setKillSQL(pInfo, TSDB_SQL_KILL_CONNECTION, &yymsp[0].minor.yy0);}
        break;
      case 224: /* cmd ::= KILL STREAM INTEGER COLON INTEGER */
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSQL(pInfo, TSDB_SQL_KILL_STREAM, &yymsp[-2].minor.yy0);}
        break;
      case 225: /* cmd ::= KILL QUERY INTEGER COLON INTEGER */
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setKillSQL(pInfo, TSDB_SQL_KILL_QUERY, &yymsp[-2].minor.yy0);}
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/

  pInfo->valid = false;
  int32_t outputBufLen = tListLen(pInfo->pzErrMsg);
  int32_t len = 0;

  if(TOKEN.z) {
    char msg[] = "syntax error near \"%s\"";
    int32_t sqlLen = strlen(&TOKEN.z[0]);

    if (sqlLen + sizeof(msg)/sizeof(msg[0]) + 1 > outputBufLen) {
        char tmpstr[128] = {0};
        memcpy(tmpstr, &TOKEN.z[0], sizeof(tmpstr)/sizeof(tmpstr[0]) - 1);
        len = sprintf(pInfo->pzErrMsg, msg, tmpstr);
    } else {
        len = sprintf(pInfo->pzErrMsg, msg, &TOKEN.z[0]);
    }

  } else {
    len = sprintf(pInfo->pzErrMsg, "Incomplete SQL statement");
  }

  assert(len <= outputBufLen);
/************ End %syntax_error code ******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/

/*********** End %parse_accept code *******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ParseCTX_FETCH
  ParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ParseFallback(int iToken){
#ifdef YYFALLBACK
  assert( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) );
  return yyFallback[iToken];
#else
  (void)iToken;
  return 0;
#endif
}
