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
#line 1 "php2python.y"

	#include <stdio.h>
	#include <ctype.h>
	#include <regex.h>
	#include <stdbool.h>
	#include "symtable.h"
	#include "gencode.h"
	
	
	#define VAR 1
	#define FUN 2
	
	
	#define GLOBALSCOPE 6
	#define FUNCTIONSCOPE 7
	#define IFCONDITIONSCOPE 8
	#define ELSECONDITIONSCOPE 9
	#define ELSEIFCONDITIONSCOPE 10
	#define WHILESCOPE 11
	#define FOREACHSCOPE 12
	#define SWITCHCASEDEFAULTSCOPE 13
	
	int while_number = 0;
	int foreach_number = 0;
	int switch_case_default_number = 0;
	int if_number = 0;
	int elseif_number = 0;
	int else_number = 0;
	int function_number = 0;
	
	char switch_cases[50][800]; //max 50 cases/default of dimension 800 char.
	int switch_cases_index = 0;
	
	int is_an_array=0; //0 no, 1 yes it is an array
	int n_params = 0; //n params array
	
	char *if_or_elseif="";
	bool flag_close_if_elseif = true;
	
	bool added_var_to_check = false;
	bool added_func_to_check = false;
	
	char numbers[100][10]; //stack
	int numbers_index = 0;
	
	int yylex();
	int yyerror(char* s);
	
	extern int yylineno;
	
	
	FILE *fptr;
	
	
	
	/*Context imp*/
	
	void increaseIfNumber(){
		printf("INCREASING NUMBER SCOPE FOR IF");
		if_number++;
	}
	
	void increaseElseIfNumber(){
		printf("INCREASING NUMBER SCOPE FOR ELSE IF");
		elseif_number++;
	}
	
	void increaseElseNumber(){
		printf("INCREASING NUMBER SCOPE FOR ELSE");
		else_number++;
	}
	
	void increaseWhileNumber(){
		printf("INCREASING NUMBER SCOPE FOR WHILE");
		while_number++;
	}
	
	void increaseForeachNumber(){
		printf("INCREASING NUMBER SCOPE FOR FOREACH");
		foreach_number++;
	}
	
	void increaseSwitchCaseDefaultNumber(){
		printf("INCREASING NUMBER SCOPE FOR SWITCH CASE/DEAFULT");
		switch_case_default_number++;
	}
	
	void increaseFunctionNumber(){
		printf("INCREASING NUMBER SCOPE FOR FUNCTION");
		function_number++;
	}
	
	/* Useful with switch cases */
	
	void add_in_switch_cases(char *organized_case) {
		
		printf("Adding new case: %s", organized_case);
		
		switch_cases[switch_cases_index][strlen(organized_case) + 1];
		strcpy(switch_cases[switch_cases_index], organized_case);
		
		switch_cases_index++;
		
	}
	
	char *merge_switch_cases(char *var) {
	
		char *string_switch_cases = malloc(800*switch_cases_index+50);
		string_switch_cases[0] = '\0';
		
		strcat(string_switch_cases, "match ");
		strcat(string_switch_cases, var);
		strcat(string_switch_cases, ":\n ");
		
		for(int i=0; i<switch_cases_index; i++) {
			
			printf("New merged cases string: %s", string_switch_cases);
			strcat(string_switch_cases, "\t");
			strcat(string_switch_cases, switch_cases[i]);
			strcat(string_switch_cases, "\n");	
		}
		
		printf("Final cases string: %s", string_switch_cases);
		
		return string_switch_cases;	
	}
	
	/* Useful with binary operations with only numbers */
	
	void push_num(char *num) {
		numbers_index++;
		printf("\nPushing number %s in temp mem for operands\n",num);
		numbers[numbers_index][10];
		strcpy(numbers[numbers_index], num);
		
		
		
	}
	
	char *pop_num() {
	
		char *element = NULL;
		
		if(numbers_index != -1)
		{
			element=numbers[numbers_index];
			numbers_index--;
		}
		printf("\nPopping number %s from temp mem for operands\n",element);
		return element;
	}
	
	
	/*Useful for showing error message in a human-readable way*/
	
	char *convert_symbols(char *message) {
		
		char* token = strtok(message, " ");
		int length = strlen(message);
		
		
		char *new_message= malloc(length+800);
		new_message[0]='\0';
		while (token) {
			
			//problem if PL, -> not recognized: solution ...>
			if(ispunct(token[strlen(token)-1])!=0) {
			
				token[strlen(token)-1] = '\0';
			
			}
			
    			
    			if(strcmp(token,"PL")==0) {
    				strcat(new_message,"\"+\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"BOOL")==0) {
    				strcat(new_message,"boolean");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"VARIABLE")==0) {
    				strcat(new_message,"variable");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"NUMBER")==0) {
    				strcat(new_message,"number");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"STRING")==0) {
    				strcat(new_message,"string");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"NAME")==0) {
    				strcat(new_message,"function name");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"RTN")==0) {
    				strcat(new_message,"return");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"EQ")==0) {
    				strcat(new_message,"\"=\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"SC")==0) {
    				strcat(new_message,"\";\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"CL")==0) {
    				strcat(new_message,"\":\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"CM")==0) {
    				strcat(new_message,"\",\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"MN")==0) {
    				strcat(new_message,"\"-\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"DV")==0) {
    				strcat(new_message,"\"/\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"ML")==0) {
    				strcat(new_message,"\"*\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"MD")==0) {
    				strcat(new_message,"\"%\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"EEQ")==0) {
    				strcat(new_message,"\"==\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"NEQ")==0) {
    				strcat(new_message,"\"!=\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"GT")==0) {
    				strcat(new_message,"\">\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"LT")==0) {
    				strcat(new_message,"\"<\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"GE")==0) {
    				strcat(new_message,"\">=\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"LE")==0) {
    				strcat(new_message,"\"<=\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"AND")==0) {
    				strcat(new_message,"\"&&\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"OR")==0) {
    				strcat(new_message,"\"||\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"PPL")==0) {
    				strcat(new_message,"\"++\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"MMN")==0) {
    				strcat(new_message,"\"--\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"CCTN")==0) {
    				strcat(new_message,"\".\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"SOR")==0) {
    				strcat(new_message,"\"|\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"NOT")==0) {
    				strcat(new_message,"\"!\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"SQ1")==0) {
    				strcat(new_message,"\"[\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"SQ2")==0) {
    				strcat(new_message,"\"]\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"RD1")==0) {
    				strcat(new_message,"\"(\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"RD2")==0) {
    				strcat(new_message,"\")\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"CR1")==0) {
    				strcat(new_message,"\"{\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"CR2")==0) {
    				strcat(new_message,"\"}\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"STARTPHP")==0) {
    				strcat(new_message,"\"<?php\"");
    				strcat(new_message," ");
    			}
    			else if(strcmp(token,"ENDPHP")==0) {
    				strcat(new_message,"\"?>\"");
    				strcat(new_message," ");
    			}
    			
    			else
    			{
    				strcat(new_message,token);
    				strcat(new_message," ");
    			}
    			
    			
    			
    			
    			
    			token = strtok(NULL, " ");
		}
		
		
		
		return new_message;
	}
	
	char *adjust_indentation(char *set_of_statements) {
	
		char* token = strtok(set_of_statements, "\n");
		int length = strlen(set_of_statements);
		
		
		char *new_message = malloc(length+1000);
		new_message[0]='\0';
		
		strcat(new_message,"\n"); //if removed, check and not tab the first line (already tab)
		
		while (token) {
    			
    			strcat(new_message,"\t");
    			strcat(new_message,token);
    			strcat(new_message,"\n");
    			
    			token = strtok(NULL, "\n");
    			
    			
		}
		
		return new_message;
	}
	
	char *adjust_indentation_case_default(char *set_of_statements) {
	
		char* token = strtok(set_of_statements, "\n");
		int length = strlen(set_of_statements);
		
		
		char *new_message = malloc(length+1000);
		new_message[0]='\0';
		
		strcat(new_message,"\n"); //if removed, check and not tab the first line (already tab)
		
		while (token) {
    			
    			strcat(new_message,"\t\t");
    			strcat(new_message,token);
    			strcat(new_message,"\n");
    			
    			token = strtok(NULL, "\n");
    			
    			
		}
		
		return new_message;
	}
	
	char *adjust_indentation_case_expr_vardecl(char *set_of_statements) {
	
		char* token = strtok(set_of_statements, "\n");
		int length = strlen(set_of_statements);
		
		
		char *new_message = malloc(length+1000);
		new_message[0]='\0';
		
		int i=0;
		
		while (token) {
    			if(i!=0){
    				strcat(new_message,"\t\t");
    				strcat(new_message,token);
    				strcat(new_message,"\n");
    				
    				token = strtok(NULL, "\n");
    			}
    			
    			i++;
    			
		}
		
		return new_message;
	}
	
	void set_if_or_elseif(char *val) {
	
		
		if_or_elseif = malloc(strlen(val) + 1);
		strcpy(if_or_elseif,val);
		printf("VAL: %s",val);
		printf("\nMoving from [%s] to else/elseif\n",if_or_elseif);
	}
	
	void close_and_check_if_or_elseif() {
	
		//in order to make this code work only one time per else, we use this flag
		
		if(flag_close_if_elseif) {
			if(strcmp(if_or_elseif,"if")==0){
			
				printf("\n\nI am in else and now checking variables and functions caught in if\n\n");
				
				int *actual_context = get_last_open_context(); 
				printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); 
		
				//check all_items var.....
				print_var_to_check();
				printf("Variables to check in if: %d",get_var_if());
				check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],0,get_var_if());
				
				//check all_items funct.....
				print_func_to_check();
				printf("Function to check in if: %d",get_func_if());
				check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],0,get_func_if());
				
				
				close_context(IFCONDITIONSCOPE,if_number); 
			}
			else if(strcmp(if_or_elseif,"elseif")==0) {
			
				printf("\n\nI am in else and now checking variables and functions caught in elseif\n\n");
				
				int *actual_context = get_last_open_context(); 
				printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); 
				
				//check all_items var.....
				print_var_to_check();
				printf("Variables to check in elseif: %d",get_var_elseif());
				printf("CONTEXT act %d-%d",actual_context[0],actual_context[1]);
				check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif());
				
				//check all_items funct.....
				print_func_to_check();
				check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif());
				
				
				close_context(ELSEIFCONDITIONSCOPE,elseif_number);
			
			
			}
	
			
			flag_close_if_elseif=false;
		}
		
		
	}
	
	bool match_number(char *operand) {
		
		regex_t regex;
		int result;
		
		result = regcomp(&regex, "^[0-9]*$", 0);
		result = regexec(&regex, operand, 0, NULL, 0);
		
		if(!result)
			return true;
		else if(result==REG_NOMATCH){
		    return false;
		}  
		else {
			    return false;
			}
	}

#line 566 "php2python.tab.c"

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
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 685 "php2python.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PHP2PYTHON_TAB_H_INCLUDED  */



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
#define YYLAST   2331

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  424

#define YYUNDEFTOK  2
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   527,   527,   527,   531,   532,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   547,   548,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   563,   564,   565,   567,   568,   569,   570,   571,
     572,   573,   574,   575,   576,   577,   578,   580,   581,   582,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   597,   598,   599,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   614,   615,   617,
     618,   619,   620,   621,   622,   623,   624,   625,   626,   627,
     628,   630,   631,   633,   634,   635,   636,   637,   638,   639,
     640,   641,   642,   643,   644,   646,   647,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   662,
     663,   665,   666,   667,   668,   669,   670,   671,   672,   673,
     674,   675,   676,   678,   680,   682,   684,   686,   688,   690,
     692,   694,   695,   696,   697,   698,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   708,   709,   710,   711,   712,
     713,   714,   715,   716,   717,   718,   719,   720,   721,   722,
     723,   724,   725,   726,   727,   728,   729,   731,   732,   733,
     735,   736,   737,   739,   740,   742,   743,   744,   745,   746,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
     757,   759,   761,   762,   763,   765,   766,   768,   769,   771,
     773,   775,   776,   778,   780,   782,   784,   786,   787,   789,
     790
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "VARIABLE", "STRING", "BOOL",
  "NAME", "COMMENT", "STARTPHP", "ENDPHP", "EQ", "SC", "CM", "NL", "PL",
  "PPL", "MN", "MMN", "DV", "ML", "MD", "EEQ", "NEQ", "GT", "LT", "GE",
  "LE", "AND", "OR", "NOT", "SQ1", "SQ2", "ARR", "RD1", "RD2", "ECH",
  "PRT", "CR1", "CR2", "IF", "ELS", "EIF", "SWH", "CSE", "BRK", "DFT",
  "CL", "FNC", "WHL", "FRC", "AS", "RDL", "APOP", "APUS", "ASUM", "SRT",
  "SOR", "SLE", "RTN", "CCTN", "$accept", "program", "$@1", "lines",
  "line", "linesinfunction", "lineinfunction", "linesinifcondition",
  "lineinifcondition", "linesinelsecondition", "lineinelsecondition",
  "linesinelseifcondition", "lineinelseifcondition", "linesinwhile",
  "lineinwhile", "linesinforeach", "lineinforeach", "linesinswitchcase",
  "lineinswitchcase", "linesinswitchdefault", "lineinswitchdefault",
  "vardeclaration", "vardeclarationinfunction",
  "vardeclarationinifcondition", "vardeclarationinelsecondition",
  "vardeclarationinelseifcondition", "vardeclarationinwhile",
  "vardeclarationinforeach", "vardeclarationinswitch", "expr", "params",
  "varparams", "optionsort", "cond", "swcond", "cases", "case", "funct",
  "while", "foreachvar", "foreach", "readline", "arraypop", "arraypush",
  "arraysum", "sort", "strlen", YY_NULLPTR
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
     315
};
# endif

#define YYPACT_NINF (-288)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,  -288,    25,  -288,  -288,    12,  -288,    66,  -288,  -288,
     -25,  -288,  -288,  2272,  2272,     5,  2207,  2264,    10,    16,
      82,    73,    78,    86,    88,    94,   101,   102,   104,  2272,
    -288,    34,     9,  -288,  -288,  -288,  -288,  -288,  -288,   122,
     127,   132,   139,  -288,  2272,  -288,  -288,   146,  2272,    67,
     120,  -288,  -288,  -288,  -288,  -288,  1569,    -9,  2272,  2272,
    -288,  2272,  -288,  2272,   151,   123,  2272,     7,   156,   163,
     166,   167,   168,    83,  -288,  -288,  -288,  2272,  2272,  2272,
    2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,  2272,
    2272,  -288,  -288,  -288,  -288,  1569,   141,    28,  2272,  2272,
    -288,    41,   531,  1227,  1284,   140,   190,  1341,   144,   171,
     161,   172,   184,   175,    43,   176,   180,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,   189,    44,  1569,  -288,  -288,  -288,   110,   164,
    -288,    45,   186,   202,  2272,  -288,  -288,  2272,  -288,   211,
    -288,  -288,  -288,  -288,  -288,    75,  -288,  2028,    59,   208,
     162,  -288,  -288,  -288,  -288,  -288,   214,   216,   218,   219,
     -38,   229,   203,  -288,  -288,   207,    46,    60,  -288,    39,
    2272,   534,  -288,   786,   213,  -288,  -288,  -288,  -288,  -288,
    -288,  2272,   204,   -32,  -288,  -288,  -288,   939,   210,   205,
    -288,  -288,   230,  1569,    85,  -288,    92,  -288,  2085,  -288,
     240,   617,  -288,  -288,  -288,  -288,  -288,   242,   243,   246,
     247,  2272,  1398,  -288,  -288,  -288,  1002,    93,  -288,  -288,
    -288,   248,   711,  -288,  -288,  -288,  -288,  -288,   249,   250,
     251,   252,  -288,   202,  -288,  1059,   231,  2272,  1116,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  1455,  -288,  2142,   114,
    -288,  -288,  -288,   254,   936,  -288,  -288,  -288,  -288,  -288,
     255,   257,   259,   260,  2272,  -288,  -288,  -288,  -288,  -288,
    -288,  1173,   238,  2085,  -288,  2272,  1569,  -288,  -288,  1230,
    1287,   182,  -288,  -288,   262,   999,  -288,  -288,  -288,  -288,
    -288,   265,   267,   268,   270,  2272,  -288,  -288,  -288,  -288,
    -288,  -288,  1569,   198,  -288,  -288,  -288,   276,  1056,  -288,
    -288,  -288,  -288,  -288,   277,   279,   280,   281,   258,  1344,
    1512,   201,  -288,  2199,   261,   283,  1113,  -288,  -288,  -288,
    -288,  -288,   286,   287,   289,   291,  -288,   292,  -288,   293,
    1170,  -288,  -288,  -288,  -288,  -288,   294,   295,   297,   298,
    2272,  -288,  -288,  -288,  -288,  -288,  -288,  1569,  2272,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  1401,  2272,  1458,
    -288,  1515,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  1569,  1569,  1572,  2199,   271,
    1569,   272,  -288,  2085,  -288,  -288,  1629,  1686,  1743,  1800,
     273,  2085,  -288,  2085,  -288,  -288,   278,  1857,  1914,  2085,
    -288,  -288,  1971,  -288
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     2,     0,     4,     1,     0,   141,   142,   143,   144,
       0,    17,     3,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     0,     8,     9,    10,    11,    12,   171,   172,
     175,   173,   176,   174,     0,   162,   163,     0,   179,   142,
       0,   164,   172,   175,   173,   176,   177,     0,   179,     0,
     166,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   169,     7,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,    14,    15,    16,   133,     0,     0,   179,     0,
     147,     0,     0,     0,     0,     0,   182,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   148,   150,   152,
     151,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     149,   145,   170,     0,   178,   146,   165,   167,     0,     0,
     180,     0,     0,     0,   179,   213,   214,   179,   216,     0,
     217,   219,   220,   208,   170,   142,    46,    34,   185,     0,
       0,    37,    38,    39,    40,    41,   172,   175,   173,   176,
     204,     0,     0,    77,   210,     0,     0,     0,   183,     0,
       0,     0,    32,     0,     0,    36,    35,    42,    43,    44,
      45,     0,     0,     0,   202,   181,    18,     0,     0,     0,
     215,   218,     0,   135,   188,    33,   142,    61,    49,   186,
       0,     0,    52,    53,    54,    55,    56,   172,   175,   173,
     176,     0,     0,   119,   201,   203,     0,   142,    90,   209,
      78,     0,     0,    81,    82,    83,    84,    85,   172,   175,
     173,   176,    91,     0,   184,     0,     0,     0,     0,    47,
      51,    50,    57,    58,    59,    60,     0,   105,   206,   142,
      31,   207,    19,     0,     0,    22,    23,    24,    25,    26,
     172,   175,   173,   176,     0,    80,    79,    86,    87,    88,
      89,     0,     0,    49,   190,     0,   136,   191,    48,     0,
       0,   142,   132,   120,     0,     0,   123,   124,   125,   126,
     127,   172,   175,   173,   176,     0,    21,    20,    27,    28,
      29,    30,   138,   142,   104,   211,    92,     0,     0,    95,
      96,    97,    98,    99,   172,   175,   173,   176,     0,     0,
       0,   142,    76,    64,   187,     0,     0,    67,    68,    69,
      70,    71,   172,   175,   173,   176,   118,     0,   106,     0,
       0,   109,   110,   111,   112,   113,   172,   175,   173,   176,
       0,   122,   121,   128,   129,   130,   131,   134,     0,    94,
      93,   100,   101,   102,   103,    91,   192,     0,     0,     0,
      62,     0,    66,    65,    72,    73,    74,    75,   205,   108,
     107,   114,   115,   116,   117,   140,   139,     0,    64,   193,
     137,     0,    63,    49,   189,   212,     0,     0,     0,     0,
     194,    49,   198,    49,   200,   195,     0,     0,     0,    49,
     196,   199,     0,   197
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,  -130,  -282,
    -173,   -87,  -287,  -288,  -288,   -58,  -288,  -288,  -288,  -288,
    -288,  -288,  -288,  -288,  -288,  -288,  -288,  -288,    29,   606,
     -45,  -288,  -288,    89,   137,  -288,   128,   471,   521,    77,
     525,  -288,    -5,    42,   100,   199,  -288
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     5,    30,   226,   262,   181,   158,   248,
     249,   379,   380,   197,   230,   281,   316,   290,   348,   258,
     293,    31,   263,   159,   210,   335,   231,   317,   294,   211,
      57,   141,   179,   212,   213,   193,   194,   214,   215,   175,
     216,    38,    52,    53,    54,    55,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   329,   334,    97,    99,     1,   191,   224,   192,    48,
     209,   108,   191,   101,   192,     6,     7,     8,     9,    10,
      11,    76,    12,   100,    77,     4,    78,   182,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    58,
     109,    99,    13,    14,    63,    15,    75,    40,    16,    17,
      64,   205,    18,   133,    99,    19,   149,    99,   171,    99,
      20,    21,    22,   132,    23,    24,    25,    26,    27,    90,
      28,    29,   284,    99,   201,   288,   135,    44,   150,   154,
     172,   199,    45,    45,    46,    46,   180,   115,   116,    65,
     399,    45,   402,    46,    33,   200,   202,    47,    47,   176,
     183,   184,   177,   247,   274,    41,    47,    66,    45,    45,
      46,    46,    67,     6,   155,     8,     9,    10,   156,   402,
      68,   409,    69,    47,    47,   305,   245,   246,    70,   417,
      45,   418,    46,   166,    91,    71,    72,   422,    73,    92,
      13,    14,    34,    15,    93,    47,    16,    17,   157,    96,
      18,    94,   166,    19,    98,   105,   288,   106,    20,    21,
      22,   110,    23,    24,    25,    26,    27,   111,    28,    29,
     112,   113,   114,   131,   186,   139,   166,    77,   217,    78,
     167,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,   238,   360,   140,   143,   145,   147,    45,   167,
      46,   153,   170,   217,    42,   144,   174,   146,   404,   368,
     148,   151,   378,    47,    45,   152,    46,    45,   178,    46,
     185,   270,    90,   167,   173,   218,   187,   161,   188,    47,
     189,   190,    47,   195,   412,   414,   288,   244,   168,   239,
     217,   196,   198,   217,   288,   288,   161,   221,   242,   288,
     218,   223,   250,   301,   252,   253,   243,   168,   254,   255,
     275,   277,   278,   279,   280,   285,   306,   308,   271,   309,
     161,   310,   311,   328,   361,   162,   324,   363,   217,   364,
     365,   168,   366,   219,   342,   356,   233,   218,   369,   371,
     218,   372,   373,   374,   162,   382,   375,   240,   384,   385,
     302,   386,   381,   387,   388,   389,   391,   392,   219,   393,
     394,   406,   407,   408,   416,   265,   419,   397,   162,   349,
     282,   225,     0,   325,   217,   218,   272,     0,   342,     0,
       0,   343,   357,     0,   234,     0,     0,   169,     0,     0,
       0,     0,     0,     0,     0,   219,     0,   296,   219,     0,
       0,     0,     0,     0,     0,     0,   169,     0,   303,     0,
       0,     0,     0,   266,     0,     0,     0,     0,     0,     0,
     319,   218,   342,     0,   342,   343,   217,     0,   337,   351,
     169,   326,   220,   219,     0,     0,     0,     0,     0,   344,
     358,     0,   324,   342,     0,   297,   241,     0,   217,     0,
       0,   342,   217,   217,   217,     0,   217,   220,   217,     0,
       0,     0,   217,   217,   217,     0,     0,   217,   320,   343,
       0,   343,   337,   218,     0,   273,   338,   352,     0,   219,
       0,     0,     0,   344,     0,     0,     0,     0,     0,   325,
     343,     0,     0,     0,   220,   218,     0,   220,   343,   218,
     218,   218,     0,   218,     0,   218,     0,   304,     0,   218,
     218,   218,     0,     0,   218,     0,   337,     0,   337,     0,
     338,     0,     0,     0,     0,     0,    35,   344,     0,   344,
     327,   219,   220,     0,     0,     0,   319,   337,   345,   359,
       0,     0,     0,     0,     0,   337,     0,   326,   344,     0,
       0,     0,     0,   219,     0,     0,   344,   219,   219,   219,
       0,   219,     0,   219,   338,     0,   338,   219,   219,   219,
       0,     0,   219,     0,     0,     0,    36,     0,   220,     0,
      37,     0,   345,     0,   320,   338,     0,     6,   155,     8,
       9,    10,   156,   338,     0,     0,    77,     0,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,     0,     0,    13,    14,   136,    15,     0,     0,
      16,    17,     0,   204,    18,     0,   345,    19,   345,     0,
     220,     0,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    90,    28,    29,     0,     0,   327,   345,     0,     0,
       0,     0,   220,     0,     0,   345,   220,   220,   220,   163,
     220,    32,   220,     0,     0,     0,   220,   220,   220,    51,
      56,   220,    60,    62,     0,     0,     0,     0,   163,   251,
       0,     0,    77,     0,    78,    74,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,     0,     0,     0,
      95,     0,   163,     0,    56,     0,     0,     0,     0,   164,
       0,     0,     0,   165,    56,   102,     0,   103,   235,   104,
       0,     0,   107,     0,     0,     0,     0,    90,   164,     0,
       0,     0,   165,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   267,     0,     0,
       0,     0,   164,     0,    56,   134,   165,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   236,     0,
       0,     0,   237,   276,     0,     0,    77,     0,    78,   298,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,     0,     0,   160,     0,     0,   268,     0,     0,
      56,   269,   321,    56,     0,     0,     0,     0,     0,     0,
     339,   353,     0,   160,     0,     0,     0,     0,     0,     0,
       0,    90,     0,     0,     0,     0,     0,     0,     0,   299,
       0,     0,     0,   300,     0,     0,   203,   160,     0,     6,
     206,     8,     9,    10,   207,     0,     0,   222,     0,     0,
       0,     0,   322,   232,   339,     0,   323,     0,     0,     0,
     340,   354,     0,     0,   341,   355,    13,    14,     0,    15,
       0,     0,    16,    17,   208,     0,    18,   256,     0,    19,
       0,     0,   264,     0,    20,    21,    22,     0,    23,    24,
      25,    26,    27,     0,    28,    29,     0,     0,   339,     0,
     339,     0,     0,   286,   340,     0,     0,     0,   341,     0,
       0,     0,     0,     0,   295,     0,     0,     0,   321,   339,
       0,     0,     0,     0,     0,     0,     0,   339,     0,     0,
     312,     0,     0,     0,     0,     0,     0,   318,     0,     0,
       0,   330,     0,     0,     0,   336,   350,     0,   340,     0,
     340,     0,   341,     0,   341,     0,     0,     0,     0,     0,
       0,   367,     0,     0,     0,     0,     0,     0,   322,   340,
       0,     0,   323,   341,     0,     0,     0,   340,     0,     0,
       0,   341,     0,     0,     0,     0,     0,     0,     0,   336,
       0,     0,     6,   227,     8,     9,    10,   228,   307,     0,
       0,    77,     0,    78,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   395,     0,     0,    13,
      14,     0,    15,     0,   396,    16,    17,     0,   229,    18,
       0,     0,    19,   336,   400,   336,     0,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    90,    28,    29,     0,
       0,     0,     0,   318,   336,     6,   259,     8,     9,    10,
     260,   362,   336,     0,    77,     0,    78,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,     0,    13,    14,     0,    15,     0,     0,    16,    17,
       0,   261,    18,     0,     0,    19,     0,     0,     0,     0,
      20,    21,    22,     0,    23,    24,    25,    26,    27,    90,
      28,    29,     6,   206,     8,     9,    10,   207,   370,     0,
       0,    77,     0,    78,     0,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,     0,    13,
      14,     0,    15,     0,     0,    16,    17,   283,     0,    18,
       0,     0,    19,     0,     0,     0,     0,    20,    21,    22,
       0,    23,    24,    25,    26,    27,    90,    28,    29,     6,
     206,     8,     9,    10,   207,   383,     0,     0,    77,     0,
      78,     0,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,     0,     0,     0,    13,    14,     0,    15,
       0,     0,    16,    17,     0,   287,    18,     0,     0,    19,
       0,     0,     0,     0,    20,    21,    22,     0,    23,    24,
      25,    26,    27,    90,    28,    29,     6,   313,     8,     9,
      10,   314,   390,     0,     0,    77,     0,    78,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,     0,    13,    14,     0,    15,     0,     0,    16,
      17,     0,   315,    18,     0,     0,    19,     0,     0,     0,
       0,    20,    21,    22,     0,    23,    24,    25,    26,    27,
      90,    28,    29,     6,   331,     8,     9,    10,   332,     0,
       0,     0,    77,     0,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,     0,     0,     0,
      13,    14,   137,    15,     0,     0,    16,    17,   333,     0,
      18,     0,     0,    19,     0,     0,     0,     0,    20,    21,
      22,     0,    23,    24,    25,    26,    27,    90,    28,    29,
       6,   291,     8,     9,    10,   346,     0,     0,     0,    77,
       0,    78,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    13,    14,   138,
      15,     0,     0,    16,    17,     0,     0,    18,     0,     0,
      19,     0,   347,     0,     0,    20,    21,    22,     0,    23,
      24,    25,    26,    27,    90,    28,    29,     6,   206,     8,
       9,    10,   207,     0,     0,     0,    77,     0,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,     0,     0,     0,    13,    14,   142,    15,     0,     0,
      16,    17,     0,   376,    18,     0,     0,    19,     0,     0,
       0,     0,    20,    21,    22,     0,    23,    24,    25,    26,
      27,    90,    28,    29,     6,   331,     8,     9,    10,   332,
       0,     0,     0,    77,     0,    78,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
       0,    13,    14,     0,    15,     0,     0,    16,    17,   398,
       0,    18,     0,     0,    19,   257,     0,     0,     0,    20,
      21,    22,     0,    23,    24,    25,    26,    27,    90,    28,
      29,     6,   331,     8,     9,    10,   332,     0,     0,     0,
      77,     0,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,     0,     0,     0,    13,    14,
     289,    15,     0,     0,    16,    17,     0,   401,    18,     0,
       0,    19,     0,     0,     0,     0,    20,    21,    22,     0,
      23,    24,    25,    26,    27,    90,    28,    29,     6,   206,
       8,     9,    10,   207,     0,     0,     0,    77,     0,    78,
       0,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,     0,    13,    14,   377,    15,     0,
       0,    16,    17,   403,     0,    18,     0,     0,    19,     0,
       0,     0,     0,    20,    21,    22,     0,    23,    24,    25,
      26,    27,    90,    28,    29,     6,   313,     8,     9,    10,
     314,     0,     0,     0,    77,     0,    78,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     0,
       0,     0,    13,    14,     0,    15,     0,     0,    16,    17,
       0,   405,    18,     0,     0,    19,     0,     0,     0,     0,
      20,    21,    22,     0,    23,    24,    25,    26,    27,    90,
      28,    29,     6,   331,     8,     9,    10,   332,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      14,     0,    15,     0,     0,    16,    17,     0,   410,    18,
       0,     0,    19,     0,     0,     0,     0,    20,    21,    22,
       0,    23,    24,    25,    26,    27,     0,    28,    29,     6,
     206,     8,     9,    10,   207,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    13,    14,     0,    15,
       0,     0,    16,    17,   411,     0,    18,     0,     0,    19,
       0,     0,     0,     0,    20,    21,    22,     0,    23,    24,
      25,    26,    27,     0,    28,    29,     6,   206,     8,     9,
      10,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    13,    14,     0,    15,     0,     0,    16,
      17,   413,     0,    18,     0,     0,    19,     0,     0,     0,
       0,    20,    21,    22,     0,    23,    24,    25,    26,    27,
       0,    28,    29,     6,   206,     8,     9,    10,   207,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,     0,    15,     0,     0,    16,    17,     0,   415,
      18,     0,     0,    19,     0,     0,     0,     0,    20,    21,
      22,     0,    23,    24,    25,    26,    27,     0,    28,    29,
       6,   206,     8,     9,    10,   207,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    13,    14,     0,
      15,     0,     0,    16,    17,     0,   420,    18,     0,     0,
      19,     0,     0,     0,     0,    20,    21,    22,     0,    23,
      24,    25,    26,    27,     0,    28,    29,     6,   206,     8,
       9,    10,   207,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    14,     0,    15,     0,     0,
      16,    17,     0,   421,    18,     0,     0,    19,     0,     0,
       0,     0,    20,    21,    22,     0,    23,    24,    25,    26,
      27,     0,    28,    29,     6,   206,     8,     9,    10,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,    14,     0,    15,     0,     0,    16,    17,     0,
     423,    18,     0,     0,    19,     0,     0,     0,     0,    20,
      21,    22,     0,    23,    24,    25,    26,    27,     0,    28,
      29,     6,   155,     8,     9,    10,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,    14,
       0,    15,     0,     0,    16,    17,     0,     0,    18,     0,
       0,    19,     0,     0,     0,     0,    20,    21,    22,     0,
      23,    24,    25,    26,    27,     0,    28,    29,     6,   206,
       8,     9,    10,   207,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    14,     0,    15,     0,
       0,    16,    17,     0,     0,    18,     0,     0,    19,     0,
       0,     0,     0,    20,    21,    22,     0,    23,    24,    25,
      26,    27,     0,    28,    29,     6,   291,     8,     9,    10,
     292,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    13,    14,     0,    15,     0,     0,    16,    17,
       0,     0,    18,     0,     0,    19,     0,     0,     0,     0,
      20,    21,    22,     0,    23,    24,    25,    26,    27,     0,
      28,    29,     6,   331,     8,     9,    10,   332,     0,     0,
       6,    49,     8,     9,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
      14,     0,    15,     0,     0,    16,    17,    13,    14,    18,
      15,    59,    19,    16,    17,     0,     0,    20,    21,    22,
       0,    23,    24,    25,    26,    27,     0,    28,    29,    23,
      24,    25,    26,    27,     0,    28,    29,     6,    49,     8,
       9,    50,     0,     0,     0,     6,    49,     8,     9,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,    14,     0,    15,    61,     0,
      16,    17,    13,    14,     0,    15,     0,     0,    16,    17,
       0,     0,     0,     0,     0,     0,    23,    24,    25,    26,
      27,     0,    28,    29,    23,    24,    25,    26,    27,     0,
      28,    29
};

static const yytype_int16 yycheck[] =
{
       5,   283,   289,    48,    13,     9,    44,    39,    46,    34,
     183,     4,    44,    58,    46,     3,     4,     5,     6,     7,
       8,    12,    10,    32,    15,     0,    17,   157,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    34,
      33,    13,    30,    31,    34,    33,    12,     5,    36,    37,
      34,   181,    40,    98,    13,    43,    13,    13,    13,    13,
      48,    49,    50,    35,    52,    53,    54,    55,    56,    60,
      58,    59,   245,    13,    35,   248,    35,    11,    35,    35,
      35,    35,    16,    16,    18,    18,    11,     4,     5,     7,
     377,    16,   379,    18,     5,    35,    57,    31,    31,   144,
      41,    42,   147,    11,    11,     5,    31,    34,    16,    16,
      18,    18,    34,     3,     4,     5,     6,     7,     8,   406,
      34,   403,    34,    31,    31,    11,    41,    42,    34,   411,
      16,   413,    18,   138,    12,    34,    34,   419,    34,    12,
      30,    31,     5,    33,    12,    31,    36,    37,    38,     3,
      40,    12,   157,    43,    34,     4,   329,    34,    48,    49,
      50,     5,    52,    53,    54,    55,    56,     4,    58,    59,
       4,     4,     4,    32,    12,    35,   181,    15,   183,    17,
     138,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,   197,    11,     4,    51,    35,    13,    16,   157,
      18,    12,    38,   208,     5,    34,     4,    35,   381,    11,
      35,    35,    11,    31,    16,    35,    18,    16,     7,    18,
      12,   226,    60,   181,    38,   183,    12,   138,    12,    31,
      12,    12,    31,     4,   407,   408,   409,     7,   138,   197,
     245,    38,    35,   248,   417,   418,   157,    34,    38,   422,
     208,    47,    12,   258,    12,    12,    51,   157,    12,    12,
      12,    12,    12,    12,    12,    34,    12,    12,   226,    12,
     181,    12,    12,    35,    12,   138,   281,    12,   283,    12,
      12,   181,    12,   183,   289,   290,   197,   245,    12,    12,
     248,    12,    12,    12,   157,    12,    38,   197,    12,    12,
     258,    12,    41,    12,    12,    12,    12,    12,   208,    12,
      12,   398,    41,    41,    41,   226,    38,   375,   181,   290,
     243,   193,    -1,   281,   329,   283,   226,    -1,   333,    -1,
      -1,   289,   290,    -1,   197,    -1,    -1,   138,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   245,    -1,   258,   248,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,   258,    -1,
      -1,    -1,    -1,   226,    -1,    -1,    -1,    -1,    -1,    -1,
     281,   329,   377,    -1,   379,   333,   381,    -1,   289,   290,
     181,   281,   183,   283,    -1,    -1,    -1,    -1,    -1,   289,
     290,    -1,   397,   398,    -1,   258,   197,    -1,   403,    -1,
      -1,   406,   407,   408,   409,    -1,   411,   208,   413,    -1,
      -1,    -1,   417,   418,   419,    -1,    -1,   422,   281,   377,
      -1,   379,   333,   381,    -1,   226,   289,   290,    -1,   329,
      -1,    -1,    -1,   333,    -1,    -1,    -1,    -1,    -1,   397,
     398,    -1,    -1,    -1,   245,   403,    -1,   248,   406,   407,
     408,   409,    -1,   411,    -1,   413,    -1,   258,    -1,   417,
     418,   419,    -1,    -1,   422,    -1,   377,    -1,   379,    -1,
     333,    -1,    -1,    -1,    -1,    -1,     5,   377,    -1,   379,
     281,   381,   283,    -1,    -1,    -1,   397,   398,   289,   290,
      -1,    -1,    -1,    -1,    -1,   406,    -1,   397,   398,    -1,
      -1,    -1,    -1,   403,    -1,    -1,   406,   407,   408,   409,
      -1,   411,    -1,   413,   377,    -1,   379,   417,   418,   419,
      -1,    -1,   422,    -1,    -1,    -1,     5,    -1,   329,    -1,
       5,    -1,   333,    -1,   397,   398,    -1,     3,     4,     5,
       6,     7,     8,   406,    -1,    -1,    15,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    -1,    30,    31,    35,    33,    -1,    -1,
      36,    37,    -1,    39,    40,    -1,   377,    43,   379,    -1,
     381,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    60,    58,    59,    -1,    -1,   397,   398,    -1,    -1,
      -1,    -1,   403,    -1,    -1,   406,   407,   408,   409,   138,
     411,     5,   413,    -1,    -1,    -1,   417,   418,   419,    13,
      14,   422,    16,    17,    -1,    -1,    -1,    -1,   157,    12,
      -1,    -1,    15,    -1,    17,    29,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      44,    -1,   181,    -1,    48,    -1,    -1,    -1,    -1,   138,
      -1,    -1,    -1,   138,    58,    59,    -1,    61,   197,    63,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    60,   157,    -1,
      -1,    -1,   157,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,   226,    -1,    -1,
      -1,    -1,   181,    -1,    98,    99,   181,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   197,    -1,
      -1,    -1,   197,    12,    -1,    -1,    15,    -1,    17,   258,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    -1,   138,    -1,    -1,   226,    -1,    -1,
     144,   226,   281,   147,    -1,    -1,    -1,    -1,    -1,    -1,
     289,   290,    -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   258,
      -1,    -1,    -1,   258,    -1,    -1,   180,   181,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,   191,    -1,    -1,
      -1,    -1,   281,   197,   333,    -1,   281,    -1,    -1,    -1,
     289,   290,    -1,    -1,   289,   290,    30,    31,    -1,    33,
      -1,    -1,    36,    37,    38,    -1,    40,   221,    -1,    43,
      -1,    -1,   226,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    -1,    58,    59,    -1,    -1,   377,    -1,
     379,    -1,    -1,   247,   333,    -1,    -1,    -1,   333,    -1,
      -1,    -1,    -1,    -1,   258,    -1,    -1,    -1,   397,   398,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   406,    -1,    -1,
     274,    -1,    -1,    -1,    -1,    -1,    -1,   281,    -1,    -1,
      -1,   285,    -1,    -1,    -1,   289,   290,    -1,   377,    -1,
     379,    -1,   377,    -1,   379,    -1,    -1,    -1,    -1,    -1,
      -1,   305,    -1,    -1,    -1,    -1,    -1,    -1,   397,   398,
      -1,    -1,   397,   398,    -1,    -1,    -1,   406,    -1,    -1,
      -1,   406,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   333,
      -1,    -1,     3,     4,     5,     6,     7,     8,    12,    -1,
      -1,    15,    -1,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   360,    -1,    -1,    30,
      31,    -1,    33,    -1,   368,    36,    37,    -1,    39,    40,
      -1,    -1,    43,   377,   378,   379,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    60,    58,    59,    -1,
      -1,    -1,    -1,   397,   398,     3,     4,     5,     6,     7,
       8,    12,   406,    -1,    15,    -1,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    -1,    36,    37,
      -1,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,    60,
      58,    59,     3,     4,     5,     6,     7,     8,    12,    -1,
      -1,    15,    -1,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    30,
      31,    -1,    33,    -1,    -1,    36,    37,    38,    -1,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    60,    58,    59,     3,
       4,     5,     6,     7,     8,    12,    -1,    -1,    15,    -1,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    -1,    30,    31,    -1,    33,
      -1,    -1,    36,    37,    -1,    39,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    60,    58,    59,     3,     4,     5,     6,
       7,     8,    12,    -1,    -1,    15,    -1,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    30,    31,    -1,    33,    -1,    -1,    36,
      37,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      60,    58,    59,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    15,    -1,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    -1,
      30,    31,    35,    33,    -1,    -1,    36,    37,    38,    -1,
      40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,
      50,    -1,    52,    53,    54,    55,    56,    60,    58,    59,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    15,
      -1,    17,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    30,    31,    35,
      33,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      43,    -1,    45,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    60,    58,    59,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    15,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    -1,    30,    31,    35,    33,    -1,    -1,
      36,    37,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    60,    58,    59,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    15,    -1,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      -1,    30,    31,    -1,    33,    -1,    -1,    36,    37,    38,
      -1,    40,    -1,    -1,    43,    47,    -1,    -1,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    60,    58,
      59,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      15,    -1,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    30,    31,
      35,    33,    -1,    -1,    36,    37,    -1,    39,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    60,    58,    59,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    15,    -1,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    30,    31,    35,    33,    -1,
      -1,    36,    37,    38,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    60,    58,    59,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    15,    -1,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    -1,    36,    37,
      -1,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,    60,
      58,    59,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    -1,    -1,    36,    37,    -1,    39,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    -1,    58,    59,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,
      -1,    -1,    36,    37,    38,    -1,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    55,    56,    -1,    58,    59,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    -1,    33,    -1,    -1,    36,
      37,    38,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    53,    54,    55,    56,
      -1,    58,    59,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    -1,    -1,    36,    37,    -1,    39,
      40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,    49,
      50,    -1,    52,    53,    54,    55,    56,    -1,    58,    59,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    -1,    -1,    36,    37,    -1,    39,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    55,    56,    -1,    58,    59,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    -1,    -1,
      36,    37,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    55,
      56,    -1,    58,    59,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    31,    -1,    33,    -1,    -1,    36,    37,    -1,
      39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    50,    -1,    52,    53,    54,    55,    56,    -1,    58,
      59,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    33,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,
      52,    53,    54,    55,    56,    -1,    58,    59,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,    54,
      55,    56,    -1,    58,    59,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    53,    54,    55,    56,    -1,
      58,    59,     3,     4,     5,     6,     7,     8,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    -1,    33,    -1,    -1,    36,    37,    30,    31,    40,
      33,    34,    43,    36,    37,    -1,    -1,    48,    49,    50,
      -1,    52,    53,    54,    55,    56,    -1,    58,    59,    52,
      53,    54,    55,    56,    -1,    58,    59,     3,     4,     5,
       6,     7,    -1,    -1,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,    33,    34,    -1,
      36,    37,    30,    31,    -1,    33,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    -1,    58,    59,    52,    53,    54,    55,    56,    -1,
      58,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    62,    63,     0,    64,     3,     4,     5,     6,
       7,     8,    10,    30,    31,    33,    36,    37,    40,    43,
      48,    49,    50,    52,    53,    54,    55,    56,    58,    59,
      65,    82,    90,    94,    95,    98,    99,   101,   102,   103,
     104,   105,   106,   107,    11,    16,    18,    31,    34,     4,
       7,    90,   103,   104,   105,   106,    90,    91,    34,    34,
      90,    34,    90,    34,    34,     7,    34,    34,    34,    34,
      34,    34,    34,    34,    90,    12,    12,    15,    17,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      60,    12,    12,    12,    12,    90,     3,    91,    34,    13,
      32,    91,    90,    90,    90,     4,    34,    90,     4,    33,
       5,     4,     4,     4,     4,     4,     5,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    32,    35,    91,    90,    35,    35,    35,    35,    35,
       4,    92,    35,    51,    34,    35,    35,    13,    35,    13,
      35,    35,    35,    12,    35,     4,     8,    38,    69,    84,
      90,    94,    95,    98,    99,   101,   103,   104,   105,   106,
      38,    13,    35,    38,     4,   100,    91,    91,     7,    93,
      11,    68,    69,    41,    42,    12,    12,    12,    12,    12,
      12,    44,    46,    96,    97,     4,    38,    74,    35,    35,
      35,    35,    57,    90,    39,    69,     4,     8,    38,    71,
      85,    90,    94,    95,    98,    99,   101,   103,   104,   105,
     106,    34,    90,    47,    39,    97,    66,     4,     8,    39,
      75,    87,    90,    94,    95,    98,    99,   101,   103,   104,
     105,   106,    38,    51,     7,    41,    42,    11,    70,    71,
      12,    12,    12,    12,    12,    12,    90,    47,    80,     4,
       8,    39,    67,    83,    90,    94,    95,    98,    99,   101,
     103,   104,   105,   106,    11,    12,    12,    12,    12,    12,
      12,    76,   100,    38,    71,    34,    90,    39,    71,    35,
      78,     4,     8,    81,    89,    90,    94,    95,    98,    99,
     101,   103,   104,   105,   106,    11,    12,    12,    12,    12,
      12,    12,    90,     4,     8,    39,    77,    88,    90,    94,
      95,    98,    99,   101,   103,   104,   105,   106,    35,    70,
      90,     4,     8,    38,    73,    86,    90,    94,    95,    98,
      99,   101,   103,   104,   105,   106,     8,    45,    79,    89,
      90,    94,    95,    98,    99,   101,   103,   104,   105,   106,
      11,    12,    12,    12,    12,    12,    12,    90,    11,    12,
      12,    12,    12,    12,    12,    38,    39,    35,    11,    72,
      73,    41,    12,    12,    12,    12,    12,    12,    12,    12,
      12,    12,    12,    12,    12,    90,    90,    76,    38,    73,
      90,    39,    73,    38,    71,    39,    72,    41,    41,    70,
      39,    38,    71,    38,    71,    39,    41,    70,    70,    38,
      39,    39,    70,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    63,    62,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    72,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    80,
      80,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    93,    93,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    96,    96,    96,    97,    97,    98,    98,    99,
     100,   101,   101,   102,   103,   104,   105,   106,   106,   107,
     107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     0,     2,     2,     2,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     1,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     1,     1,     2,     0,     2,     2,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     1,     2,     0,
       2,     2,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     1,     1,     2,     0,     2,     2,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     1,     0,     2,     2,
       2,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       1,     0,     2,     2,     2,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     1,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     0,
       2,     2,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     4,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     4,     2,     4,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       1,     3,     0,     1,     3,     5,     7,    10,     7,    12,
       9,     9,    11,    12,    14,    14,    16,    18,    14,    16,
      14,     7,     1,     2,     0,     6,     3,     8,     5,     7,
       1,     9,    12,     4,     4,     6,     4,     4,     6,     4,
       4
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
#line 527 "php2python.y"
                  {open_dest_file(); add_new_open_context(GLOBALSCOPE, 0);}
#line 2542 "php2python.tab.c"
    break;

  case 6:
#line 534 "php2python.y"
                {translate_expr((yyvsp[-1].str)); printf("\nLINE EXPR\n"); check_all_items_in_context(GLOBALSCOPE, 0);}
#line 2548 "php2python.tab.c"
    break;

  case 7:
#line 535 "php2python.y"
                            {translate_declaration((yyvsp[-1].str)); printf("\nLINE VARDECLARATION\n"); check_all_items_in_context(GLOBALSCOPE, 0);}
#line 2554 "php2python.tab.c"
    break;

  case 8:
#line 536 "php2python.y"
               {translate_cond((yyvsp[0].str)); printf("\nLINE IF\n");}
#line 2560 "php2python.tab.c"
    break;

  case 9:
#line 537 "php2python.y"
                 {translate_switch((yyvsp[0].str)); printf("\nLINE SWITCH\n");}
#line 2566 "php2python.tab.c"
    break;

  case 10:
#line 538 "php2python.y"
                {translate_funct((yyvsp[0].str)); printf("\nLINE FUNCT\n");}
#line 2572 "php2python.tab.c"
    break;

  case 11:
#line 539 "php2python.y"
                {translate_while((yyvsp[0].str)); printf("\nLINE WHILE\n");}
#line 2578 "php2python.tab.c"
    break;

  case 12:
#line 540 "php2python.y"
                  {translate_foreach((yyvsp[0].str)); printf("\nLINE FOREACH\n");}
#line 2584 "php2python.tab.c"
    break;

  case 13:
#line 541 "php2python.y"
                      {translate_expr((yyvsp[-1].str)); printf("\nLINE ARRAYPOP\n");}
#line 2590 "php2python.tab.c"
    break;

  case 14:
#line 542 "php2python.y"
                       {translate_expr((yyvsp[-1].str)); printf("\nLINE ARRAYPUSH\n");}
#line 2596 "php2python.tab.c"
    break;

  case 15:
#line 543 "php2python.y"
                      {translate_expr((yyvsp[-1].str)); printf("\nLINE ARRAYSUM\n");}
#line 2602 "php2python.tab.c"
    break;

  case 16:
#line 544 "php2python.y"
                  {translate_expr((yyvsp[-1].str)); printf("\nLINE SORT\n");}
#line 2608 "php2python.tab.c"
    break;

  case 17:
#line 545 "php2python.y"
                  {translate_comment((yyvsp[0].str)); printf("\nLINE COMMENT\n");}
#line 2614 "php2python.tab.c"
    break;

  case 19:
#line 548 "php2python.y"
                                         {printf("\n\nTrying to add functional open scope\n\n");add_new_open_context(FUNCTIONSCOPE, function_number);}
#line 2620 "php2python.tab.c"
    break;

  case 20:
#line 550 "php2python.y"
                        { increase_number_instr_funct(); push((yyvsp[-1].str)); printf("\nLINEINFUNCTION EXPR\n");}
#line 2626 "php2python.tab.c"
    break;

  case 21:
#line 551 "php2python.y"
                                      {increase_number_instr_funct(); push((yyvsp[-1].str)); printf("\nLINEINFUNCTION VARDECLARATION\n");}
#line 2632 "php2python.tab.c"
    break;

  case 22:
#line 552 "php2python.y"
               {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION IF \n");}
#line 2638 "php2python.tab.c"
    break;

  case 23:
#line 553 "php2python.y"
                 {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION SWITCH\n");}
#line 2644 "php2python.tab.c"
    break;

  case 24:
#line 554 "php2python.y"
                {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION FUNCTION\n");}
#line 2650 "php2python.tab.c"
    break;

  case 25:
#line 555 "php2python.y"
                {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION WHILE\n");}
#line 2656 "php2python.tab.c"
    break;

  case 26:
#line 556 "php2python.y"
                  {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION FOREACH\n");}
#line 2662 "php2python.tab.c"
    break;

  case 27:
#line 557 "php2python.y"
                      {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFUNCTION ARRAYPOP\n");}
#line 2668 "php2python.tab.c"
    break;

  case 28:
#line 558 "php2python.y"
                       {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFUNCTION ARRAYPUSH\n");}
#line 2674 "php2python.tab.c"
    break;

  case 29:
#line 559 "php2python.y"
                      {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFUNCTION ARRAYSUM\n");}
#line 2680 "php2python.tab.c"
    break;

  case 30:
#line 560 "php2python.y"
                  {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFUNCTION SORT\n");}
#line 2686 "php2python.tab.c"
    break;

  case 31:
#line 561 "php2python.y"
                  {increase_number_instr_funct(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFUNCTION COMMENT\n");}
#line 2692 "php2python.tab.c"
    break;

  case 34:
#line 565 "php2python.y"
                               {printf("NO LINES IN IF");}
#line 2698 "php2python.tab.c"
    break;

  case 35:
#line 567 "php2python.y"
                                { increase_number_instr_if(); push((yyvsp[-1].str)); printf("\nLINEINIF EXPR\n"); printf("\n\nTrying to add if condition open scope\n\n"); if(added_var_to_check) {increase_var_if(); added_var_to_check=false;} if(added_func_to_check) {increase_func_if(); added_func_to_check=false;} set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2704 "php2python.tab.c"
    break;

  case 36:
#line 568 "php2python.y"
                                         {increase_number_instr_if(); push((yyvsp[-1].str)); printf("\nLINEINIF VARDECLARATION\n"); printf("\n\nTrying to add if condition open scope\n\n"); if(added_var_to_check) {increase_var_if(); added_var_to_check=false;} if(added_func_to_check) {increase_func_if(); added_func_to_check=false;} set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2710 "php2python.tab.c"
    break;

  case 37:
#line 569 "php2python.y"
               {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF IF\n");}
#line 2716 "php2python.tab.c"
    break;

  case 38:
#line 570 "php2python.y"
                 {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF SWITCH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2722 "php2python.tab.c"
    break;

  case 39:
#line 571 "php2python.y"
                {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF FUNCTION\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2728 "php2python.tab.c"
    break;

  case 40:
#line 572 "php2python.y"
                {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF WHILE\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2734 "php2python.tab.c"
    break;

  case 41:
#line 573 "php2python.y"
                  {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF FOREACH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2740 "php2python.tab.c"
    break;

  case 42:
#line 574 "php2python.y"
                      {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINIF ARRAYPOP\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2746 "php2python.tab.c"
    break;

  case 43:
#line 575 "php2python.y"
                       {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINIF ARRAYPUSH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2752 "php2python.tab.c"
    break;

  case 44:
#line 576 "php2python.y"
                      {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINIF ARRAYSUM\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2758 "php2python.tab.c"
    break;

  case 45:
#line 577 "php2python.y"
                  {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINIF SORT\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
#line 2764 "php2python.tab.c"
    break;

  case 46:
#line 578 "php2python.y"
                  {increase_number_instr_if(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINIF COMMENT\n");}
#line 2770 "php2python.tab.c"
    break;

  case 49:
#line 582 "php2python.y"
                                 {printf("NO LINES IN ELSE");}
#line 2776 "php2python.tab.c"
    break;

  case 50:
#line 584 "php2python.y"
                                { increase_number_instr_else(); push((yyvsp[-1].str)); printf("\nLINEINELSE EXPR\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} if(added_var_to_check) {increase_var_else(); added_var_to_check=false;} if(added_func_to_check) {increase_func_else(); added_func_to_check=false;} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2782 "php2python.tab.c"
    break;

  case 51:
#line 585 "php2python.y"
                                           {increase_number_instr_else(); push((yyvsp[-1].str)); printf("\nLINEINELSE VARDECLARATION\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} if(added_var_to_check) {increase_var_else(); added_var_to_check=false;} if(added_func_to_check) {increase_func_else(); added_func_to_check=false;} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2788 "php2python.tab.c"
    break;

  case 52:
#line 586 "php2python.y"
               {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE IF\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2794 "php2python.tab.c"
    break;

  case 53:
#line 587 "php2python.y"
                 {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE SWITCH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2800 "php2python.tab.c"
    break;

  case 54:
#line 588 "php2python.y"
                {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE FUNCTION\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2806 "php2python.tab.c"
    break;

  case 55:
#line 589 "php2python.y"
                {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE WHILE\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2812 "php2python.tab.c"
    break;

  case 56:
#line 590 "php2python.y"
                  {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE FOREACH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2818 "php2python.tab.c"
    break;

  case 57:
#line 591 "php2python.y"
                      {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSE ARRAHYPOP\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2824 "php2python.tab.c"
    break;

  case 58:
#line 592 "php2python.y"
                       {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSE ARRAYPUSH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2830 "php2python.tab.c"
    break;

  case 59:
#line 593 "php2python.y"
                      {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSE ARRAYSUM\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2836 "php2python.tab.c"
    break;

  case 60:
#line 594 "php2python.y"
                  {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSE SORT\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
#line 2842 "php2python.tab.c"
    break;

  case 61:
#line 595 "php2python.y"
                  {increase_number_instr_else(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSE COMMENT\n");}
#line 2848 "php2python.tab.c"
    break;

  case 65:
#line 601 "php2python.y"
                                { increase_number_instr_elseif(); push((yyvsp[-1].str)); printf("\nLINEINELSEIF EXPR\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2854 "php2python.tab.c"
    break;

  case 66:
#line 602 "php2python.y"
                                             {increase_number_instr_elseif(); push((yyvsp[-1].str)); printf("\nLINEINELSEIF VARDECLARATION\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2860 "php2python.tab.c"
    break;

  case 67:
#line 603 "php2python.y"
               {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF IF\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2866 "php2python.tab.c"
    break;

  case 68:
#line 604 "php2python.y"
                 {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF SWITCH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2872 "php2python.tab.c"
    break;

  case 69:
#line 605 "php2python.y"
                {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF FUNCTION\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2878 "php2python.tab.c"
    break;

  case 70:
#line 606 "php2python.y"
                {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF WHILE\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2884 "php2python.tab.c"
    break;

  case 71:
#line 607 "php2python.y"
                  {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF FOREACH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2890 "php2python.tab.c"
    break;

  case 72:
#line 608 "php2python.y"
                      {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSEIF ARRAYPOP\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2896 "php2python.tab.c"
    break;

  case 73:
#line 609 "php2python.y"
                       {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSEIF ARRAYPUSH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2902 "php2python.tab.c"
    break;

  case 74:
#line 610 "php2python.y"
                      {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSEIF ARRAYSUM\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2908 "php2python.tab.c"
    break;

  case 75:
#line 611 "php2python.y"
                  {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINELSEIF SORT\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
#line 2914 "php2python.tab.c"
    break;

  case 76:
#line 612 "php2python.y"
                  {increase_number_instr_elseif(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINELSEIF COMMENT\n");}
#line 2920 "php2python.tab.c"
    break;

  case 78:
#line 615 "php2python.y"
                                   {printf("\n\nTrying to add while open scope\n\n"); add_new_open_context(WHILESCOPE, while_number);}
#line 2926 "php2python.tab.c"
    break;

  case 79:
#line 617 "php2python.y"
                        { increase_number_instr_while(); push((yyvsp[-1].str)); printf("\nLINEINWHILE EXPR\n");}
#line 2932 "php2python.tab.c"
    break;

  case 80:
#line 618 "php2python.y"
                                   {increase_number_instr_while(); push((yyvsp[-1].str)); printf("\nLINEINWHILE VARDECLARATION\n");}
#line 2938 "php2python.tab.c"
    break;

  case 81:
#line 619 "php2python.y"
               {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE IF\n");}
#line 2944 "php2python.tab.c"
    break;

  case 82:
#line 620 "php2python.y"
                 {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE SWITCH\n");}
#line 2950 "php2python.tab.c"
    break;

  case 83:
#line 621 "php2python.y"
                {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE FUNCTION\n");}
#line 2956 "php2python.tab.c"
    break;

  case 84:
#line 622 "php2python.y"
                {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE WHILE\n");}
#line 2962 "php2python.tab.c"
    break;

  case 85:
#line 623 "php2python.y"
                  {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE FOREACH\n");}
#line 2968 "php2python.tab.c"
    break;

  case 86:
#line 624 "php2python.y"
                      {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINWHILE ARRAYPOP\n");}
#line 2974 "php2python.tab.c"
    break;

  case 87:
#line 625 "php2python.y"
                       {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINWHILE ARRAYPUSH\n");}
#line 2980 "php2python.tab.c"
    break;

  case 88:
#line 626 "php2python.y"
                      {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINWHILE ARRAYSUM\n");}
#line 2986 "php2python.tab.c"
    break;

  case 89:
#line 627 "php2python.y"
                  {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINWHILE SORT\n");}
#line 2992 "php2python.tab.c"
    break;

  case 90:
#line 628 "php2python.y"
                  {increase_number_instr_while(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINWHILE COMMENT\n");}
#line 2998 "php2python.tab.c"
    break;

  case 92:
#line 631 "php2python.y"
                                       {printf("\n\nTrying to add foreach open scope\n\n"); add_new_open_context(FOREACHSCOPE, foreach_number);}
#line 3004 "php2python.tab.c"
    break;

  case 93:
#line 633 "php2python.y"
                        { increase_number_instr_foreach(); push((yyvsp[-1].str)); printf("\nLINEINFOREACH EXPR\n");}
#line 3010 "php2python.tab.c"
    break;

  case 94:
#line 634 "php2python.y"
                                     {increase_number_instr_foreach(); push((yyvsp[-1].str)); printf("\nLINEINFOREACH VARDECLARATION\n");}
#line 3016 "php2python.tab.c"
    break;

  case 95:
#line 635 "php2python.y"
               {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH IF\n");}
#line 3022 "php2python.tab.c"
    break;

  case 96:
#line 636 "php2python.y"
                 {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH SWITCH\n");}
#line 3028 "php2python.tab.c"
    break;

  case 97:
#line 637 "php2python.y"
                {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH FUNCTION\n");}
#line 3034 "php2python.tab.c"
    break;

  case 98:
#line 638 "php2python.y"
                {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH WHILE\n");}
#line 3040 "php2python.tab.c"
    break;

  case 99:
#line 639 "php2python.y"
                  {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH FOREACH\n");}
#line 3046 "php2python.tab.c"
    break;

  case 100:
#line 640 "php2python.y"
                      {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFOREACH ARRAYPOP\n");}
#line 3052 "php2python.tab.c"
    break;

  case 101:
#line 641 "php2python.y"
                       {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFOREACH ARRAYPUSH\n");}
#line 3058 "php2python.tab.c"
    break;

  case 102:
#line 642 "php2python.y"
                      {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFOREACH ARRAYSUM\n");}
#line 3064 "php2python.tab.c"
    break;

  case 103:
#line 643 "php2python.y"
                  {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[-1].str)); push(adjust); printf("\nLINEINFOREACH SORT\n");}
#line 3070 "php2python.tab.c"
    break;

  case 104:
#line 644 "php2python.y"
                  {increase_number_instr_foreach(); char *adjust = adjust_indentation((yyvsp[0].str)); push(adjust); printf("\nLINEINFOREACH COMMENT\n");}
#line 3076 "php2python.tab.c"
    break;

  case 106:
#line 647 "php2python.y"
                                             {printf("\n\nTrying to add a new switch CASE/DEFAULT open scope\n\n"); add_new_open_context(SWITCHCASEDEFAULTSCOPE, switch_case_default_number);}
#line 3082 "php2python.tab.c"
    break;

  case 107:
#line 649 "php2python.y"
                                { increase_number_instr_case(); /*push($1);*/ char *adjust = adjust_indentation_case_expr_vardecl((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE EXPR\n");}
#line 3088 "php2python.tab.c"
    break;

  case 108:
#line 650 "php2python.y"
                                    {increase_number_instr_case(); /*push($1);*/ char *adjust = adjust_indentation_case_expr_vardecl((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE VARDECLARATION\n");}
#line 3094 "php2python.tab.c"
    break;

  case 109:
#line 651 "php2python.y"
               {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE IF\n");}
#line 3100 "php2python.tab.c"
    break;

  case 110:
#line 652 "php2python.y"
                 {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE SWITCH\n");}
#line 3106 "php2python.tab.c"
    break;

  case 111:
#line 653 "php2python.y"
                {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE FUNCITON\n");}
#line 3112 "php2python.tab.c"
    break;

  case 112:
#line 654 "php2python.y"
                {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE WHILE\n");}
#line 3118 "php2python.tab.c"
    break;

  case 113:
#line 655 "php2python.y"
                  {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE FOREACH\n");}
#line 3124 "php2python.tab.c"
    break;

  case 114:
#line 656 "php2python.y"
                      {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE ARRAYPOP\n");}
#line 3130 "php2python.tab.c"
    break;

  case 115:
#line 657 "php2python.y"
                       {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE ARRAYPUSH\n");}
#line 3136 "php2python.tab.c"
    break;

  case 116:
#line 658 "php2python.y"
                      {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE ARRAYSUM\n");}
#line 3142 "php2python.tab.c"
    break;

  case 117:
#line 659 "php2python.y"
                  {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHCASE SORT\n");}
#line 3148 "php2python.tab.c"
    break;

  case 118:
#line 660 "php2python.y"
                  {increase_number_instr_case(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHCASE COMMENT\n");}
#line 3154 "php2python.tab.c"
    break;

  case 120:
#line 663 "php2python.y"
                                                   {printf("\n\nTrying to add a new switch CASE/DEFAULT open scope\n\n"); add_new_open_context(SWITCHCASEDEFAULTSCOPE, switch_case_default_number);}
#line 3160 "php2python.tab.c"
    break;

  case 121:
#line 665 "php2python.y"
                                { increase_number_instr_default(); push((yyvsp[-1].str)); printf("\nLINEINSWITCHDEFAULT EXPR\n");}
#line 3166 "php2python.tab.c"
    break;

  case 122:
#line 666 "php2python.y"
                                    {increase_number_instr_default(); push((yyvsp[-1].str)); printf("\nLINEINSWITCHDEFAULT VARDECLARATION\n");}
#line 3172 "php2python.tab.c"
    break;

  case 123:
#line 667 "php2python.y"
               {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT IF\n");}
#line 3178 "php2python.tab.c"
    break;

  case 124:
#line 668 "php2python.y"
                 {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT SWITCH\n");}
#line 3184 "php2python.tab.c"
    break;

  case 125:
#line 669 "php2python.y"
                {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT FUCNTION\n");}
#line 3190 "php2python.tab.c"
    break;

  case 126:
#line 670 "php2python.y"
                {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT WHILE\n");}
#line 3196 "php2python.tab.c"
    break;

  case 127:
#line 671 "php2python.y"
                  {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT FOREACH\n");}
#line 3202 "php2python.tab.c"
    break;

  case 128:
#line 672 "php2python.y"
                      {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYPOP\n");}
#line 3208 "php2python.tab.c"
    break;

  case 129:
#line 673 "php2python.y"
                       {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYPUSH\n");}
#line 3214 "php2python.tab.c"
    break;

  case 130:
#line 674 "php2python.y"
                      {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYSUM\n");}
#line 3220 "php2python.tab.c"
    break;

  case 131:
#line 675 "php2python.y"
                  {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[-1].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT SORT\n");}
#line 3226 "php2python.tab.c"
    break;

  case 132:
#line 676 "php2python.y"
                  {increase_number_instr_default(); char *adjust = adjust_indentation_case_default((yyvsp[0].str)); push(adjust); printf("\nLINEINSWITCHDEFAULT COMMENT\n");}
#line 3232 "php2python.tab.c"
    break;

  case 133:
#line 678 "php2python.y"
                                 {printf("\nexpr is a variable in declaration line IN GLOBAL SCOPE\n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) {/*is an array*/ printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,GLOBALSCOPE,0,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,GLOBALSCOPE,0,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN GLOBAL SCOPE\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3238 "php2python.tab.c"
    break;

  case 134:
#line 680 "php2python.y"
                                           {printf("\nexpr is a variable in declaration line IN A FUNCTION \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,FUNCTIONSCOPE,function_number,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,FUNCTIONSCOPE,function_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A FUNCTION\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3244 "php2python.tab.c"
    break;

  case 135:
#line 682 "php2python.y"
                                              {printf("\nexpr is a variable in declaration line IN A IF CONDITION \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1));if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,IFCONDITIONSCOPE,if_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,IFCONDITIONSCOPE,if_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A IF\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3250 "php2python.tab.c"
    break;

  case 136:
#line 684 "php2python.y"
                                                {printf("\nexpr is a variable in declaration line IN A ELSE CONDITION \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,ELSECONDITIONSCOPE,else_number,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,ELSECONDITIONSCOPE,else_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A ELSE\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3256 "php2python.tab.c"
    break;

  case 137:
#line 686 "php2python.y"
                                                  {printf("\nexpr is a variable in declaration line IN A ELSE IF CONDITION \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,ELSEIFCONDITIONSCOPE,elseif_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,ELSEIFCONDITIONSCOPE,elseif_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A ELSEIF\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3262 "php2python.tab.c"
    break;

  case 138:
#line 688 "php2python.y"
                                        {printf("\nexpr is a variable in declaration line IN WHILE SCOPE\n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,WHILESCOPE,while_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,WHILESCOPE,while_number,0,0); }fprintf(fptr,"FOUND VARIABLE DECL IN A WHILE\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3268 "php2python.tab.c"
    break;

  case 139:
#line 690 "php2python.y"
                                          {printf("\nexpr is a variable in declaration line IN A FOREACH  \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,FOREACHSCOPE,foreach_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,FOREACHSCOPE,foreach_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A FOREACH\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3274 "php2python.tab.c"
    break;

  case 140:
#line 692 "php2python.y"
                                         {printf("\nexpr is a variable in declaration line IN A SWITCH \n"); printf("My variable name %s and its hash %d",(yyvsp[-2].id)+1,hash((yyvsp[-2].id)+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,SWITCHCASEDEFAULTSCOPE,switch_case_default_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash((yyvsp[-2].id)+1),(yyvsp[-2].id)+1,VAR,SWITCHCASEDEFAULTSCOPE,switch_case_default_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A SWITCH\n"); (yyval.str)=organize_declaration((yyvsp[-2].id)+1,(yyvsp[0].str));}
#line 3280 "php2python.tab.c"
    break;

  case 141:
#line 694 "php2python.y"
                {printf("\nexpr is a number\n"); fprintf(fptr,"FOUND NUMBER\n"); char str[10]; char *temp; temp=itoa((yyvsp[0].intval),str); push_num(temp); (yyval.str)=itoa((yyvsp[0].intval),str);}
#line 3286 "php2python.tab.c"
    break;

  case 142:
#line 695 "php2python.y"
                        {printf("\nexpr is a variable\n"); printf("\n HERE CHECK IF DECLARED\n"); fprintf(fptr,"FOUND VARIABLE\n"); add_new_var_to_check((yyvsp[0].id)+1); added_var_to_check=true; (yyval.str)=(yyvsp[0].id)+1; }
#line 3292 "php2python.tab.c"
    break;

  case 143:
#line 696 "php2python.y"
                        {printf("\nexpr is a string\n"); fprintf(fptr,"FOUND STRING\n"); (yyval.str)=(yyvsp[0].str);}
#line 3298 "php2python.tab.c"
    break;

  case 144:
#line 697 "php2python.y"
                {printf("\nexpr is a bool\n"); fprintf(fptr,"FOUND BOOL\n"); (yyval.str)=translate_bool((yyvsp[0].str));}
#line 3304 "php2python.tab.c"
    break;

  case 145:
#line 698 "php2python.y"
                                  {printf("\nexpr is an array access through index\n"); printf("Accessing the position %d of array %s\n",(yyvsp[-1].intval),(yyvsp[-3].id)); fprintf(fptr,"FOUND ARRAY ACCESS\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); /*check n params*/ check_n_params_match(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1],(yyvsp[-1].intval)); char str[10]; (yyval.str) = translate_array_access((yyvsp[-3].id)+1,itoa((yyvsp[-1].intval),str));}
#line 3310 "php2python.tab.c"
    break;

  case 146:
#line 699 "php2python.y"
                                {printf("\nexpr is an array definition through keyword array\n"); fprintf(fptr,"FOUND ARRAY DEFINITION\n"); is_an_array=1; n_params = get_number_params(); (yyval.str)=translate_array_definition();}
#line 3316 "php2python.tab.c"
    break;

  case 147:
#line 700 "php2python.y"
                                {printf("\nexpr is an array definition through classic squared brackets\n"); fprintf(fptr,"FOUND ARRAY DEFINITION\n");  is_an_array=1; n_params = get_number_params(); (yyval.str)=translate_array_definition();}
#line 3322 "php2python.tab.c"
    break;

  case 148:
#line 701 "php2python.y"
                        {printf("\nFOUND PLUS OPERATION\n"); fprintf(fptr,"FOUND PLUS\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"+",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"+",(yyvsp[0].str));} }
#line 3328 "php2python.tab.c"
    break;

  case 149:
#line 702 "php2python.y"
                                {printf("\nFOUND CONCATENATION OPERATION\n"); fprintf(fptr,"FOUND CCTN\n"); (yyval.str)=translate_operation((yyvsp[-2].str),"+",(yyvsp[0].str)); }
#line 3334 "php2python.tab.c"
    break;

  case 150:
#line 703 "php2python.y"
                        {printf("\nFOUND MINUS OPERATION\n"); fprintf(fptr,"FOUND MINUS\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"-",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"-",(yyvsp[0].str));} }
#line 3340 "php2python.tab.c"
    break;

  case 151:
#line 704 "php2python.y"
                        {printf("\nFOUND MULT OPERATION\n"); fprintf(fptr,"FOUND MULTIPLICATION\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"*",second_num_op);} else{ (yyval.str)=translate_operation((yyvsp[-2].str),"*",(yyvsp[0].str));}}
#line 3346 "php2python.tab.c"
    break;

  case 152:
#line 705 "php2python.y"
                        {printf("\nFOUND DIV OPERATION\n"); fprintf(fptr,"FOUND DIVISION\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"/",second_num_op);} else {(yyval.str)=translate_operation((yyvsp[-2].str),"/",(yyvsp[0].str));}}
#line 3352 "php2python.tab.c"
    break;

  case 153:
#line 706 "php2python.y"
                        {printf("\nFOUND MODULUS OPERATION\n"); fprintf(fptr,"FOUND MODULUS\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"%",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"%",(yyvsp[0].str));}}
#line 3358 "php2python.tab.c"
    break;

  case 154:
#line 707 "php2python.y"
                                {printf("\nFOUND IS EQUAL OPERATION\n"); fprintf(fptr,"FOUND IS EQUAL\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"==",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"==",(yyvsp[0].str));}}
#line 3364 "php2python.tab.c"
    break;

  case 155:
#line 708 "php2python.y"
                                {printf("\nFOUND IS NOT EQUAL OPERATION\n"); fprintf(fptr,"FOUND NOT EQUAL\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"!=",second_num_op);} else {(yyval.str)=translate_operation((yyvsp[-2].str),"!=",(yyvsp[0].str));} }
#line 3370 "php2python.tab.c"
    break;

  case 156:
#line 709 "php2python.y"
                        {printf("\nFOUND IS GREATER THAN OPERATION\n"); fprintf(fptr,"FOUND GREATER THAN\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,">",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),">",(yyvsp[0].str));} }
#line 3376 "php2python.tab.c"
    break;

  case 157:
#line 710 "php2python.y"
                        {printf("\nFOUND IS LESS THAN OPERATION\n"); fprintf(fptr,"FOUND LESS THAN\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"<",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"<",(yyvsp[0].str));}}
#line 3382 "php2python.tab.c"
    break;

  case 158:
#line 711 "php2python.y"
                        {printf("\nFOUND IS GREATER EQUAL OPERATION\n"); fprintf(fptr,"FOUND GREATER EQUAL\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,">=",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),">=",(yyvsp[0].str));} }
#line 3388 "php2python.tab.c"
    break;

  case 159:
#line 712 "php2python.y"
                        {printf("\nFOUND IS LESS EQUAL OPERATION\n"); fprintf(fptr,"FOUND LESS EQUAL\n"); if(match_number((yyvsp[-2].str))&&match_number((yyvsp[0].str))){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); (yyval.str)=translate_operation(first_num_op,"<=",second_num_op);} else{(yyval.str)=translate_operation((yyvsp[-2].str),"<=",(yyvsp[0].str));}}
#line 3394 "php2python.tab.c"
    break;

  case 160:
#line 713 "php2python.y"
                                {printf("\nFOUND AND OPERATION\n"); fprintf(fptr,"FOUND AND\n"); (yyval.str)=translate_operation((yyvsp[-2].str),"and",(yyvsp[0].str));}
#line 3400 "php2python.tab.c"
    break;

  case 161:
#line 714 "php2python.y"
                        {printf("\nFOUND OR OPERATION\n"); fprintf(fptr,"FOUND OR\n"); (yyval.str)=translate_operation((yyvsp[-2].str),"or",(yyvsp[0].str));}
#line 3406 "php2python.tab.c"
    break;

  case 162:
#line 715 "php2python.y"
                        {printf("\nexpr is a variable increment\n"); printf("Increment variable %s\n",(yyvsp[-1].id)); add_new_var_to_check((yyvsp[-1].id)+1); added_var_to_check=true; fprintf(fptr,"FOUND VAR INCREM\n");  (yyval.str)=translate_increment("++",(yyvsp[-1].id)+1);}
#line 3412 "php2python.tab.c"
    break;

  case 163:
#line 716 "php2python.y"
                        {printf("\nexpr is a variable decrement\n"); printf("decrement variable %s\n",(yyvsp[-1].id)); add_new_var_to_check((yyvsp[-1].id)+1); added_var_to_check=true; fprintf(fptr,"FOUND VAR DECREM\n");  (yyval.str)=translate_increment("--",(yyvsp[-1].id)+1);}
#line 3418 "php2python.tab.c"
    break;

  case 164:
#line 717 "php2python.y"
                                {printf("\nFOUND NOT OPERATION\n"); fprintf(fptr,"FOUND NOT\n"); (yyval.str)=translate_not_operation("not",(yyvsp[0].str));}
#line 3424 "php2python.tab.c"
    break;

  case 165:
#line 718 "php2python.y"
                                {printf("\nFOUND ECHO OPERATION WITH ROUND BRACKETS \n"); fprintf(fptr,"FOUND ECHO\n"); (yyval.str)=translate_print((yyvsp[-1].str));}
#line 3430 "php2python.tab.c"
    break;

  case 166:
#line 719 "php2python.y"
                        {printf("\nFOUND ECHO OPERATION\n"); fprintf(fptr,"FOUND ECHO\n"); (yyval.str)=translate_print((yyvsp[0].str));}
#line 3436 "php2python.tab.c"
    break;

  case 167:
#line 720 "php2python.y"
                                {printf("\nFOUND PRINT OPERATION WITH ROUND BRACKETS\n"); fprintf(fptr,"FOUND PRINT\n"); (yyval.str)=translate_print((yyvsp[-1].str));}
#line 3442 "php2python.tab.c"
    break;

  case 168:
#line 721 "php2python.y"
                        {printf("\nFOUND PRINT OPERATION\n"); fprintf(fptr,"FOUND PRINT\n"); (yyval.str)=translate_print((yyvsp[0].str));}
#line 3448 "php2python.tab.c"
    break;

  case 169:
#line 722 "php2python.y"
                        {printf("\nFOUND RETURN OPERATION\n"); fprintf(fptr,"FOUND RETURN\n"); (yyval.str)=translate_return((yyvsp[0].str));}
#line 3454 "php2python.tab.c"
    break;

  case 170:
#line 723 "php2python.y"
                                {printf("\nFOUND FUNCT CALL here since semicolon problems\n"); fprintf(fptr,"FOUND FUNCTION CALL\n"); add_new_func_to_check((yyvsp[-3].id)); added_func_to_check=true; /*check n params*/ int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n %s",actual_context[0],actual_context[1],(yyvsp[-3].id)); check_n_params_match(hash((yyvsp[-3].id)),(yyvsp[-3].id),FUN,actual_context[0],actual_context[1],get_number_params()); (yyval.str)=translate_function_call((yyvsp[-3].id));}
#line 3460 "php2python.tab.c"
    break;

  case 171:
#line 724 "php2python.y"
                        {printf("\nFOUND READLINE CALL\n"); fprintf(fptr,"FOUND READLINE CALL\n");}
#line 3466 "php2python.tab.c"
    break;

  case 172:
#line 725 "php2python.y"
                        {printf("\nFOUND ARRAYPOP CALL\n"); fprintf(fptr,"FOUND ARRAYPOP CALL\n");}
#line 3472 "php2python.tab.c"
    break;

  case 173:
#line 726 "php2python.y"
                        {printf("\nFOUND ARRAY SUM \n"); fprintf(fptr,"FOUND ARRAYSUM CALL\n");}
#line 3478 "php2python.tab.c"
    break;

  case 174:
#line 727 "php2python.y"
                        {printf("\nFOUND A STRLEN \n"); fprintf(fptr,"FOUND STRLEN CALL\n");}
#line 3484 "php2python.tab.c"
    break;

  case 175:
#line 728 "php2python.y"
                        {printf("\nFOUND ARRAYPUSH CALL \n"); fprintf(fptr,"FOUND ARRAYPUSH CALL\n");}
#line 3490 "php2python.tab.c"
    break;

  case 176:
#line 729 "php2python.y"
                {printf("\nFOUND SORT CALL \n"); fprintf(fptr,"FOUND SORT CALL\n");}
#line 3496 "php2python.tab.c"
    break;

  case 177:
#line 731 "php2python.y"
                {printf("\n FOUND NEW PARAMS_ \n"); increase_number_params(); push((yyvsp[0].str));}
#line 3502 "php2python.tab.c"
    break;

  case 178:
#line 732 "php2python.y"
                         {printf("\nFOUND PARAMS\n"); increase_number_params(); push((yyvsp[0].str));}
#line 3508 "php2python.tab.c"
    break;

  case 179:
#line 733 "php2python.y"
                          {(yyval.str)=NULL;}
#line 3514 "php2python.tab.c"
    break;

  case 180:
#line 735 "php2python.y"
                        {printf("found varparam\n"); fprintf(fptr,"FOUND PARAMETER VARIABLE\n"); add_item(hash((yyvsp[0].id)+1),(yyvsp[0].id)+1,VAR,FUNCTIONSCOPE,function_number,0,0); increase_number_varparams(); push((yyvsp[0].id)+1);}
#line 3520 "php2python.tab.c"
    break;

  case 181:
#line 736 "php2python.y"
                                {printf("found varparamsss\n"); fprintf(fptr,"FOUND PARAMETER VARIABLE\n"); add_item(hash((yyvsp[0].id)+1),(yyvsp[0].id)+1,VAR,FUNCTIONSCOPE,function_number,0,0); increase_number_varparams(); push((yyvsp[0].id)+1);}
#line 3526 "php2python.tab.c"
    break;

  case 182:
#line 737 "php2python.y"
                          {(yyval.str)=NULL;}
#line 3532 "php2python.tab.c"
    break;

  case 183:
#line 739 "php2python.y"
                        {printf("\nFOUND SORT OPTIION \n"); fprintf(fptr,"FOUND SORT OPTION \n"); increase_number_params(); push((yyvsp[0].id));}
#line 3538 "php2python.tab.c"
    break;

  case 184:
#line 740 "php2python.y"
                              {increase_number_params(); push((yyvsp[0].id));}
#line 3544 "php2python.tab.c"
    break;

  case 185:
#line 742 "php2python.y"
                                        {printf("\nFOUND IF WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(IFCONDITIONSCOPE,if_number); check_all_items_in_context(actual_context[0],actual_context[1]); erase_var_if(); erase_func_if(); increaseIfNumber(); (yyval.str)=organize_if((yyvsp[-2].str));}
#line 3550 "php2python.tab.c"
    break;

  case 186:
#line 743 "php2python.y"
                                                                        {printf("\nFOUND IF WITH ONE LINE BODY AND ELSE WITH ONE LINE  BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSE WITH ONE LINE  BODY\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number);  print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else();  (yyval.str)=merge_condition(2,organize_if((yyvsp[-4].str)),organize_else());}
#line 3556 "php2python.tab.c"
    break;

  case 187:
#line 744 "php2python.y"
                                                                                        {printf("\nFOUND IF WITH ONE LINE BODY AND ELSEIF WITH ONE LINE  BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSEIF WITH ONE LINE  BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-7].str)),organize_elseif((yyvsp[-2].str)));}
#line 3562 "php2python.tab.c"
    break;

  case 188:
#line 745 "php2python.y"
                                                        {printf("\nFOUND IF WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(IFCONDITIONSCOPE,if_number); check_all_items_in_context(actual_context[0],actual_context[1]); erase_var_if(); erase_func_if(); increaseIfNumber(); (yyval.str)=organize_if((yyvsp[-4].str));}
#line 3568 "php2python.tab.c"
    break;

  case 189:
#line 746 "php2python.y"
                                                                                                                {printf("\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-9].str)),organize_elseif((yyvsp[-4].str)),organize_else());}
#line 3574 "php2python.tab.c"
    break;

  case 190:
#line 747 "php2python.y"
                                                                                {printf("\nFOUND IF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-6].str)),organize_else());}
#line 3580 "php2python.tab.c"
    break;

  case 191:
#line 748 "php2python.y"
                                                                                {printf("\nFOUND IF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true;  erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-6].str)),organize_else());}
#line 3586 "php2python.tab.c"
    break;

  case 192:
#line 749 "php2python.y"
                                                                                        {printf("\nFOUND IF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-8].str)),organize_else());}
#line 3592 "php2python.tab.c"
    break;

  case 193:
#line 750 "php2python.y"
                                                                                                {printf("\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-9].str)),organize_elseif((yyvsp[-2].str)));}
#line 3598 "php2python.tab.c"
    break;

  case 194:
#line 751 "php2python.y"
                                                                                                        {printf("\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); (yyval.str)=merge_condition(2,organize_if((yyvsp[-11].str)),organize_elseif((yyvsp[-4].str)));}
#line 3604 "php2python.tab.c"
    break;

  case 195:
#line 752 "php2python.y"
                                                                                                                        {printf("\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber(); increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-11].str)),organize_elseif((yyvsp[-6].str)),organize_else());}
#line 3610 "php2python.tab.c"
    break;

  case 196:
#line 753 "php2python.y"
                                                                                                                                {printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-13].str)),organize_elseif((yyvsp[-6].str)), organize_else());}
#line 3616 "php2python.tab.c"
    break;

  case 197:
#line 754 "php2python.y"
                                                                                                                                        {printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-15].str)),organize_elseif((yyvsp[-8].str)), organize_else());}
#line 3622 "php2python.tab.c"
    break;

  case 198:
#line 755 "php2python.y"
                                                                                                                        {printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-11].str)),organize_elseif((yyvsp[-4].str)),organize_else());}
#line 3628 "php2python.tab.c"
    break;

  case 199:
#line 756 "php2python.y"
                                                                                                                                {printf("\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-13].str)),organize_elseif((yyvsp[-8].str)), organize_else());}
#line 3634 "php2python.tab.c"
    break;

  case 200:
#line 757 "php2python.y"
                                                                                                                        {printf("\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); (yyval.str)=merge_condition(3,organize_if((yyvsp[-11].str)),organize_elseif((yyvsp[-6].str)), organize_else());}
#line 3640 "php2python.tab.c"
    break;

  case 201:
#line 759 "php2python.y"
                                                {printf("\nFOUND SWITCH STATEMENT\n"); fprintf(fptr,"FOUND SWITCH\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-4].id)+1),(yyvsp[-4].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=merge_switch_cases((yyvsp[-4].id)+1);}
#line 3646 "php2python.tab.c"
    break;

  case 205:
#line 765 "php2python.y"
                                                {printf("\nFOUND A CASE \n"); fprintf(fptr,"FOUND CASE\n"); close_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); check_all_items_in_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); add_in_switch_cases(organize_case((yyvsp[-4].str))); increaseSwitchCaseDefaultNumber();}
#line 3652 "php2python.tab.c"
    break;

  case 206:
#line 766 "php2python.y"
                                                        {printf("\nFOUND A DEFAULT \n"); fprintf(fptr,"FOUND DEFAULT CASE\n"); close_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); check_all_items_in_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); add_in_switch_cases(organize_default()); increaseSwitchCaseDefaultNumber();}
#line 3658 "php2python.tab.c"
    break;

  case 207:
#line 768 "php2python.y"
                                                                {printf("\nFOUND FUNCTION DEFINITION\n"); fprintf(fptr,"FOUND FUNCTION DEFINITION\n"); printf("My function name %s and its hash %d",(yyvsp[-6].id),hash((yyvsp[-6].id))); close_context(FUNCTIONSCOPE,function_number); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); add_item(hash((yyvsp[-6].id)),(yyvsp[-6].id),FUN,actual_context[0],actual_context[1],0,get_number_varparams()); /*check variables in this block*/  check_all_items_in_context(FUNCTIONSCOPE,function_number);  increaseFunctionNumber(); (yyval.str)=organize_function_def((yyvsp[-6].id));}
#line 3664 "php2python.tab.c"
    break;

  case 208:
#line 769 "php2python.y"
                                        {printf("\nFOUND FUNCTION CALL\n"); fprintf(fptr,"FOUND FUNCTION CALL\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-4].id)),(yyvsp[-4].id),FUN,actual_context[0],actual_context[1]); check_n_params_match(hash((yyvsp[-4].id)),(yyvsp[-4].id),FUN,actual_context[0],actual_context[1],get_number_params()); (yyval.str)=organize_function_call((yyvsp[-4].id));}
#line 3670 "php2python.tab.c"
    break;

  case 209:
#line 771 "php2python.y"
                                                {printf("\nFOUND WHILE LOOP\n"); fprintf(fptr,"FOUND WHILE\n"); close_context(WHILESCOPE,while_number); check_all_items_in_context(WHILESCOPE,while_number); increaseWhileNumber(); (yyval.str)=organize_while((yyvsp[-4].str));}
#line 3676 "php2python.tab.c"
    break;

  case 210:
#line 773 "php2python.y"
                     {printf("\nexpr is a foreach variable\n");  add_item(hash((yyvsp[0].id)+1),(yyvsp[0].id)+1,VAR,FOREACHSCOPE,foreach_number,0,0); add_new_open_context(FOREACHSCOPE, foreach_number); (yyval.str)=(yyvsp[0].id)+1; }
#line 3682 "php2python.tab.c"
    break;

  case 211:
#line 775 "php2python.y"
                                                                        {printf("\nFOUND FOREACH with array into variable - check in semantic later\n"); fprintf(fptr,"FOUND FOREACH\n"); close_context(FOREACHSCOPE,foreach_number); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-6].id)+1),(yyvsp[-6].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is array*/ check_if_var_is_array(hash((yyvsp[-6].id)+1),(yyvsp[-6].id)+1,VAR,actual_context[0],actual_context[1]); check_all_items_in_context(FOREACHSCOPE,foreach_number); add_item(hash((yyvsp[-4].str)),(yyvsp[-4].str),VAR,FOREACHSCOPE,foreach_number,0,0); increaseForeachNumber(); (yyval.str)=organize_foreach((yyvsp[-6].id)+1,(yyvsp[-4].str));}
#line 3688 "php2python.tab.c"
    break;

  case 212:
#line 776 "php2python.y"
                                                                                {printf("\nFOUND FOREACH with array definition into the construct\n");fprintf(fptr,"FOUND FOREACH\n"); close_context(FOREACHSCOPE,foreach_number); check_all_items_in_context(FOREACHSCOPE,foreach_number); (yyval.str)=organize_foreach_arraydef((yyvsp[-4].str));}
#line 3694 "php2python.tab.c"
    break;

  case 213:
#line 778 "php2python.y"
                                {printf("\nFOUND READLINE\n");fprintf(fptr,"FOUND READLINE\n"); (yyval.str)=translate_readline((yyvsp[-1].str));}
#line 3700 "php2python.tab.c"
    break;

  case 214:
#line 780 "php2python.y"
                                {printf("\nFOUND ARRAYPOP\n");fprintf(fptr,"FOUND ARRAYPOP\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=translate_arraypop((yyvsp[-1].id)+1);}
#line 3706 "php2python.tab.c"
    break;

  case 215:
#line 782 "php2python.y"
                                                {printf("\nFOUND ARRAYPUSH\n");fprintf(fptr,"FOUND ARRAYPUSH\n");   int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=translate_arraypush((yyvsp[-3].id)+1);}
#line 3712 "php2python.tab.c"
    break;

  case 216:
#line 784 "php2python.y"
                                {printf("\nFOUND ARRAYSUM\n");fprintf(fptr,"FOUND ARRAYSUM\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]);  check_item_in_context(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=translate_arraysum((yyvsp[-1].id)+1);}
#line 3718 "php2python.tab.c"
    break;

  case 217:
#line 786 "php2python.y"
                                {printf("\nFOUND SORT \n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/check_if_var_is_array(hash((yyvsp[-1].id)+1),(yyvsp[-1].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=translate_sort((yyvsp[-1].id)+1);}
#line 3724 "php2python.tab.c"
    break;

  case 218:
#line 787 "php2python.y"
                                                {printf("\nFOUND SORT WITH OPTIIONS \n");fprintf(fptr,"FOUND SORT WITH OPTIONS\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash((yyvsp[-3].id)+1),(yyvsp[-3].id)+1,VAR,actual_context[0],actual_context[1]); (yyval.str)=translate_sort_options((yyvsp[-3].id)+1);}
#line 3730 "php2python.tab.c"
    break;

  case 219:
#line 789 "php2python.y"
                                {printf("\nFOUND STRLEN WITH VARIABLE \n"); fprintf(fptr,"FOUND STRLEN WITH VARIABLE\n"); add_new_var_to_check((yyvsp[-1].id)+1); added_var_to_check=true; (yyval.str)=translate_strlen((yyvsp[-1].id));}
#line 3736 "php2python.tab.c"
    break;

  case 220:
#line 790 "php2python.y"
                                {printf("\nFOUND STRLEN WITH STRING \n"); fprintf(fptr,"FOUND STRLEN WITH STRING\n"); (yyval.str)=translate_strlen((yyvsp[-1].str));}
#line 3742 "php2python.tab.c"
    break;


#line 3746 "php2python.tab.c"

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
#line 792 "php2python.y"


int main (int argc, char *argv[]) {
	
	if (remove("abstract_tree.txt") == 0) {
        fptr = fopen("abstract_tree.txt","a");
    	}
	
	remove("output_traslated.py");
	
	return yyparse();
}

int read_prev_lines(const char* file_name)
{
 	FILE *file;
 	int num;
 	
 	file = fopen(file_name, "r");
	
	
  	if(file!=NULL)
  	{	
    		while (fscanf(file, "%d", &num) == 1)
        	{
        		return num;
    		}
  	}
  	else {
  	printf("\n NO LINES BEFORE PHP\n");
  	}
  	fclose(file);
  	
}

int yyerror(char *s) {
	printf ("\n\nPHP warning: %sat line %d (line %d of PHP code segment)\n", convert_symbols(s), yylineno, yylineno-read_prev_lines("startLinePhp.txt"));
	return 0;
	exit(0);
}


