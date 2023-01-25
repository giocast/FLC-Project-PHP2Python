/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PHP2PYTHON_TAB_H_INCLUDED
# define YY_YY_PHP2PYTHON_TAB_H_INCLUDED
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
    NUMBER = 258,
    VARIABLE = 259,
    STRING = 260,
    BOOL = 261,
    NAME = 262,
    COMMENT = 263,
    STARTPHP = 264,
    ENDPHP = 265,
    EQ = 266,
    SC = 267,
    CM = 268,
    NL = 269,
    PL = 270,
    PPL = 271,
    MN = 272,
    MMN = 273,
    DV = 274,
    ML = 275,
    MD = 276,
    EEQ = 277,
    NEQ = 278,
    GT = 279,
    LT = 280,
    GE = 281,
    LE = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    SQ1 = 286,
    SQ2 = 287,
    ARR = 288,
    RD1 = 289,
    RD2 = 290,
    ECH = 291,
    PRT = 292,
    CR1 = 293,
    CR2 = 294,
    IF = 295,
    ELS = 296,
    EIF = 297,
    SWH = 298,
    CSE = 299,
    BRK = 300,
    DFT = 301,
    CL = 302,
    FNC = 303,
    WHL = 304,
    FRC = 305,
    AS = 306,
    RDL = 307,
    APOP = 308,
    APUS = 309,
    ASUM = 310,
    SRT = 311,
    SOR = 312,
    SLE = 313,
    RTN = 314,
    CCTN = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 500 "php2python.y"

	int intval;
	char *id;
	char *str;	

#line 124 "php2python.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PHP2PYTHON_TAB_H_INCLUDED  */
