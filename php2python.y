%{
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
%}

%define parse.error verbose

%union
{
	int intval;
	char *id;
	char *str;	
}


%start program

%token <intval> NUMBER
%token <id> VARIABLE
%token <str> STRING
%token <str> BOOL
%token <id> NAME
%token <str> COMMENT
%token STARTPHP ENDPHP

%type <str> expr vardeclaration readline arraypop arraysum strlen sort arraypush cond linesinifcondition lineinifcondition vardeclarationinifcondition vardeclarationinfunction vardeclarationinelsecondition vardeclarationinelseifcondition vardeclarationinwhile vardeclarationinforeach vardeclarationinswitch swcond case while funct foreach foreachvar params varparams

%token EQ SC CM NL PL PPL MN MMN DV ML MD EEQ NEQ GT LT GE LE AND OR NOT SQ1 SQ2 ARR RD1 RD2 ECH PRT CR1 CR2 IF ELS EIF SWH CSE BRK DFT CL FNC WHL FRC AS RDL APOP APUS ASUM SRT SOR SLE RTN CCTN


%left PL PPL MN MMN ML DV EQ MD EEQ NEQ GT LT GE LE AND OR AS SOR RTN CCTN
%right NOT PRT ECH CSE DFT FNC SWH IF ELS EIF WHL FRC RDL APOP APUS ASUM SRT SLE

%%

program: STARTPHP {open_dest_file(); add_new_open_context(GLOBALSCOPE, 0);}
		lines 
	   ENDPHP
	;
lines: /* empty string */
	| lines line
	;
line:	expr SC {translate_expr($1); printf("\nLINE EXPR\n"); check_all_items_in_context(GLOBALSCOPE, 0);}
	| vardeclaration SC {translate_declaration($1); printf("\nLINE VARDECLARATION\n"); check_all_items_in_context(GLOBALSCOPE, 0);}
	| cond {translate_cond($1); printf("\nLINE IF\n");}
	| swcond {translate_switch($1); printf("\nLINE SWITCH\n");}
	| funct {translate_funct($1); printf("\nLINE FUNCT\n");}
	| while {translate_while($1); printf("\nLINE WHILE\n");}
	| foreach {translate_foreach($1); printf("\nLINE FOREACH\n");}
	| arraypop SC {translate_expr($1); printf("\nLINE ARRAYPOP\n");}
	| arraypush SC {translate_expr($1); printf("\nLINE ARRAYPUSH\n");}
	| arraysum SC {translate_expr($1); printf("\nLINE ARRAYSUM\n");}
	| sort SC {translate_expr($1); printf("\nLINE SORT\n");}
	| COMMENT {translate_comment($1); printf("\nLINE COMMENT\n");} 
	;
linesinfunction: /* empty string */
	| linesinfunction lineinfunction {printf("\n\nTrying to add functional open scope\n\n");add_new_open_context(FUNCTIONSCOPE, function_number);}
	;
lineinfunction:	expr SC { increase_number_instr_funct(); push($1); printf("\nLINEINFUNCTION EXPR\n");}
	| vardeclarationinfunction SC {increase_number_instr_funct(); push($1); printf("\nLINEINFUNCTION VARDECLARATION\n");}
	| cond {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION IF \n");}
	| swcond {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION SWITCH\n");}
	| funct {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION FUNCTION\n");}
	| while {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION WHILE\n");}
	| foreach {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION FOREACH\n");}
	| arraypop SC {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION ARRAYPOP\n");}
	| arraypush SC {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION ARRAYPUSH\n");}
	| arraysum SC {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION ARRAYSUM\n");}
	| sort SC {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION SORT\n");}
	| COMMENT {increase_number_instr_funct(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFUNCTION COMMENT\n");}
	;
linesinifcondition: lineinifcondition
	| linesinifcondition lineinifcondition
	| /* no lines in if */ {printf("NO LINES IN IF");}
	;
lineinifcondition:	expr SC { increase_number_instr_if(); push($1); printf("\nLINEINIF EXPR\n"); printf("\n\nTrying to add if condition open scope\n\n"); if(added_var_to_check) {increase_var_if(); added_var_to_check=false;} if(added_func_to_check) {increase_func_if(); added_func_to_check=false;} set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| vardeclarationinifcondition SC {increase_number_instr_if(); push($1); printf("\nLINEINIF VARDECLARATION\n"); printf("\n\nTrying to add if condition open scope\n\n"); if(added_var_to_check) {increase_var_if(); added_var_to_check=false;} if(added_func_to_check) {increase_func_if(); added_func_to_check=false;} set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| cond {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF IF\n");}
	| swcond {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF SWITCH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| funct {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF FUNCTION\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| while {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF WHILE\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| foreach {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF FOREACH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| arraypop SC {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF ARRAYPOP\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| arraypush SC {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF ARRAYPUSH\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| arraysum SC {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF ARRAYSUM\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| sort SC {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF SORT\n"); printf("\n\nTrying to add if condition open scope\n\n"); set_if_or_elseif("if"); add_new_open_context(IFCONDITIONSCOPE, if_number);}
	| COMMENT {increase_number_instr_if(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINIF COMMENT\n");}
	;
linesinelsecondition: lineinelsecondition
	| linesinelsecondition lineinelsecondition
	| /* no lines in else */ {printf("NO LINES IN ELSE");}
	;
lineinelsecondition:	expr SC { increase_number_instr_else(); push($1); printf("\nLINEINELSE EXPR\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} if(added_var_to_check) {increase_var_else(); added_var_to_check=false;} if(added_func_to_check) {increase_func_else(); added_func_to_check=false;} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| vardeclarationinelsecondition SC {increase_number_instr_else(); push($1); printf("\nLINEINELSE VARDECLARATION\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} if(added_var_to_check) {increase_var_else(); added_var_to_check=false;} if(added_func_to_check) {increase_func_else(); added_func_to_check=false;} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| cond {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE IF\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| swcond {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE SWITCH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| funct {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE FUNCTION\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| while {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE WHILE\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| foreach {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE FOREACH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| arraypop SC {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE ARRAHYPOP\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| arraypush SC {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE ARRAYPUSH\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| arraysum SC {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE ARRAYSUM\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| sort SC {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE SORT\n"); printf("\n\nTrying to add else condition open scope\n\n"); if(strcmp(if_or_elseif,"elseif")==0){flag_close_if_elseif=true; close_and_check_if_or_elseif(); strcpy(if_or_elseif,"ended"); /*arbitrary value to end*/ } else{close_and_check_if_or_elseif();} add_new_open_context(ELSECONDITIONSCOPE, else_number);}
	| COMMENT {increase_number_instr_else(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSE COMMENT\n");}
	;
linesinelseifcondition: lineinelseifcondition
	| linesinelseifcondition lineinelseifcondition
	| /* no lines in elseif */
	;
lineinelseifcondition:	expr SC { increase_number_instr_elseif(); push($1); printf("\nLINEINELSEIF EXPR\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| vardeclarationinelseifcondition SC {increase_number_instr_elseif(); push($1); printf("\nLINEINELSEIF VARDECLARATION\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| cond {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF IF\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| swcond {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF SWITCH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| funct {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF FUNCTION\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| while {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF WHILE\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| foreach {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF FOREACH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| arraypop SC {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF ARRAYPOP\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| arraypush SC {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF ARRAYPUSH\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| arraysum SC {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF ARRAYSUM\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| sort SC {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF SORT\n"); printf("\n\nTrying to add elseif condition open scope\n\n"); close_and_check_if_or_elseif(); set_if_or_elseif("elseif"); if(added_var_to_check) {increase_var_elseif(); added_var_to_check=false;} if(added_func_to_check) {increase_func_elseif(); added_func_to_check=false;} add_new_open_context(ELSEIFCONDITIONSCOPE, elseif_number);}
	| COMMENT {increase_number_instr_elseif(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINELSEIF COMMENT\n");}
	;
linesinwhile: /* empty string */
	| linesinwhile lineinwhile {printf("\n\nTrying to add while open scope\n\n"); add_new_open_context(WHILESCOPE, while_number);}
	;
lineinwhile:	expr SC { increase_number_instr_while(); push($1); printf("\nLINEINWHILE EXPR\n");}
	| vardeclarationinwhile SC {increase_number_instr_while(); push($1); printf("\nLINEINWHILE VARDECLARATION\n");}
	| cond {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE IF\n");}
	| swcond {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE SWITCH\n");}
	| funct {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE FUNCTION\n");}
	| while {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE WHILE\n");}
	| foreach {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE FOREACH\n");}
	| arraypop SC {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE ARRAYPOP\n");}
	| arraypush SC {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE ARRAYPUSH\n");}
	| arraysum SC {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE ARRAYSUM\n");}
	| sort SC {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE SORT\n");}
	| COMMENT {increase_number_instr_while(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINWHILE COMMENT\n");}
	;
linesinforeach: /* empty string */
	| linesinforeach lineinforeach {printf("\n\nTrying to add foreach open scope\n\n"); add_new_open_context(FOREACHSCOPE, foreach_number);}
	;
lineinforeach:	expr SC { increase_number_instr_foreach(); push($1); printf("\nLINEINFOREACH EXPR\n");}
	| vardeclarationinforeach SC {increase_number_instr_foreach(); push($1); printf("\nLINEINFOREACH VARDECLARATION\n");}
	| cond {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH IF\n");}
	| swcond {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH SWITCH\n");}
	| funct {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH FUNCTION\n");}
	| while {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH WHILE\n");}
	| foreach {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH FOREACH\n");}
	| arraypop SC {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH ARRAYPOP\n");}
	| arraypush SC {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH ARRAYPUSH\n");}
	| arraysum SC {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH ARRAYSUM\n");}
	| sort SC {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH SORT\n");}
	| COMMENT {increase_number_instr_foreach(); char *adjust = adjust_indentation($1); push(adjust); printf("\nLINEINFOREACH COMMENT\n");}
	;
linesinswitchcase: /* empty string */
	| linesinswitchcase lineinswitchcase {printf("\n\nTrying to add a new switch CASE/DEFAULT open scope\n\n"); add_new_open_context(SWITCHCASEDEFAULTSCOPE, switch_case_default_number);}
	;
lineinswitchcase:	expr SC { increase_number_instr_case(); /*push($1);*/ char *adjust = adjust_indentation_case_expr_vardecl($1); push(adjust); printf("\nLINEINSWITCHCASE EXPR\n");}
	| vardeclarationinswitch SC {increase_number_instr_case(); /*push($1);*/ char *adjust = adjust_indentation_case_expr_vardecl($1); push(adjust); printf("\nLINEINSWITCHCASE VARDECLARATION\n");}
	| cond {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE IF\n");}
	| swcond {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE SWITCH\n");}
	| funct {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE FUNCITON\n");}
	| while {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE WHILE\n");}
	| foreach {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE FOREACH\n");}
	| arraypop SC {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE ARRAYPOP\n");}
	| arraypush SC {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE ARRAYPUSH\n");}
	| arraysum SC {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE ARRAYSUM\n");}
	| sort SC {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE SORT\n");}
	| COMMENT {increase_number_instr_case(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHCASE COMMENT\n");}
	;
linesinswitchdefault: /* empty string */
	| linesinswitchdefault lineinswitchdefault {printf("\n\nTrying to add a new switch CASE/DEFAULT open scope\n\n"); add_new_open_context(SWITCHCASEDEFAULTSCOPE, switch_case_default_number);}
	;
lineinswitchdefault:	expr SC { increase_number_instr_default(); push($1); printf("\nLINEINSWITCHDEFAULT EXPR\n");}
	| vardeclarationinswitch SC {increase_number_instr_default(); push($1); printf("\nLINEINSWITCHDEFAULT VARDECLARATION\n");}
	| cond {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT IF\n");}
	| swcond {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT SWITCH\n");}
	| funct {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT FUCNTION\n");}
	| while {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT WHILE\n");}
	| foreach {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT FOREACH\n");}
	| arraypop SC {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYPOP\n");}
	| arraypush SC {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYPUSH\n");}
	| arraysum SC {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT ARRAYSUM\n");}
	| sort SC {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT SORT\n");}
	| COMMENT {increase_number_instr_default(); char *adjust = adjust_indentation_case_default($1); push(adjust); printf("\nLINEINSWITCHDEFAULT COMMENT\n");}
	;
vardeclaration: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN GLOBAL SCOPE\n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) {/*is an array*/ printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,GLOBALSCOPE,0,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash($1+1),$1+1,VAR,GLOBALSCOPE,0,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN GLOBAL SCOPE\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinfunction: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A FUNCTION \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,FUNCTIONSCOPE,function_number,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash($1+1),$1+1,VAR,FUNCTIONSCOPE,function_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A FUNCTION\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinifcondition: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A IF CONDITION \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1));if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,IFCONDITIONSCOPE,if_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash($1+1),$1+1,VAR,IFCONDITIONSCOPE,if_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A IF\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinelsecondition: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A ELSE CONDITION \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,ELSECONDITIONSCOPE,else_number,1,n_params); is_an_array=0; n_params=0;} else {add_item(hash($1+1),$1+1,VAR,ELSECONDITIONSCOPE,else_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A ELSE\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinelseifcondition: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A ELSE IF CONDITION \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,ELSEIFCONDITIONSCOPE,elseif_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash($1+1),$1+1,VAR,ELSEIFCONDITIONSCOPE,elseif_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A ELSEIF\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinwhile: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN WHILE SCOPE\n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,WHILESCOPE,while_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash($1+1),$1+1,VAR,WHILESCOPE,while_number,0,0); }fprintf(fptr,"FOUND VARIABLE DECL IN A WHILE\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinforeach: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A FOREACH  \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) { printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,FOREACHSCOPE,foreach_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash($1+1),$1+1,VAR,FOREACHSCOPE,foreach_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A FOREACH\n"); $$=organize_declaration($1+1,$3);}
	;
vardeclarationinswitch: VARIABLE EQ expr {printf("\nexpr is a variable in declaration line IN A SWITCH \n"); printf("My variable name %s and its hash %d",$1+1,hash($1+1)); if(is_an_array==1) {printf("\nThis var is an array\n"); add_item(hash($1+1),$1+1,VAR,SWITCHCASEDEFAULTSCOPE,switch_case_default_number,1,n_params); is_an_array=0; n_params=0;} else{ add_item(hash($1+1),$1+1,VAR,SWITCHCASEDEFAULTSCOPE,switch_case_default_number,0,0);} fprintf(fptr,"FOUND VARIABLE DECL IN A SWITCH\n"); $$=organize_declaration($1+1,$3);}
	;	
expr:	NUMBER	{printf("\nexpr is a number\n"); fprintf(fptr,"FOUND NUMBER\n"); char str[10]; char *temp; temp=itoa($1,str); push_num(temp); $$=itoa($1,str);}
	| VARIABLE	{printf("\nexpr is a variable\n"); printf("\n HERE CHECK IF DECLARED\n"); fprintf(fptr,"FOUND VARIABLE\n"); add_new_var_to_check($1+1); added_var_to_check=true; $$=$1+1; }
	| STRING	{printf("\nexpr is a string\n"); fprintf(fptr,"FOUND STRING\n"); $$=$1;}
	| BOOL	{printf("\nexpr is a bool\n"); fprintf(fptr,"FOUND BOOL\n"); $$=translate_bool($1);}
	| VARIABLE SQ1 NUMBER SQ2 {printf("\nexpr is an array access through index\n"); printf("Accessing the position %d of array %s\n",$3,$1); fprintf(fptr,"FOUND ARRAY ACCESS\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($1+1),$1+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash($1+1),$1+1,VAR,actual_context[0],actual_context[1]); /*check n params*/ check_n_params_match(hash($1+1),$1+1,VAR,actual_context[0],actual_context[1],$3); char str[10]; $$ = translate_array_access($1+1,itoa($3,str));} 
	| ARR RD1 params RD2	{printf("\nexpr is an array definition through keyword array\n"); fprintf(fptr,"FOUND ARRAY DEFINITION\n"); is_an_array=1; n_params = get_number_params(); $$=translate_array_definition();}
	| SQ1 params SQ2	{printf("\nexpr is an array definition through classic squared brackets\n"); fprintf(fptr,"FOUND ARRAY DEFINITION\n");  is_an_array=1; n_params = get_number_params(); $$=translate_array_definition();}
	| expr PL expr 	{printf("\nFOUND PLUS OPERATION\n"); fprintf(fptr,"FOUND PLUS\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"+",second_num_op);} else{$$=translate_operation($1,"+",$3);} }
	| expr CCTN expr 	{printf("\nFOUND CONCATENATION OPERATION\n"); fprintf(fptr,"FOUND CCTN\n"); $$=translate_operation($1,"+",$3); }
	| expr MN expr 	{printf("\nFOUND MINUS OPERATION\n"); fprintf(fptr,"FOUND MINUS\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"-",second_num_op);} else{$$=translate_operation($1,"-",$3);} }
	| expr ML expr 	{printf("\nFOUND MULT OPERATION\n"); fprintf(fptr,"FOUND MULTIPLICATION\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"*",second_num_op);} else{ $$=translate_operation($1,"*",$3);}}
	| expr DV expr 	{printf("\nFOUND DIV OPERATION\n"); fprintf(fptr,"FOUND DIVISION\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"/",second_num_op);} else {$$=translate_operation($1,"/",$3);}}
	| expr MD expr 	{printf("\nFOUND MODULUS OPERATION\n"); fprintf(fptr,"FOUND MODULUS\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"%",second_num_op);} else{$$=translate_operation($1,"%",$3);}}
	| expr EEQ expr 	{printf("\nFOUND IS EQUAL OPERATION\n"); fprintf(fptr,"FOUND IS EQUAL\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"==",second_num_op);} else{$$=translate_operation($1,"==",$3);}}
	| expr NEQ expr 	{printf("\nFOUND IS NOT EQUAL OPERATION\n"); fprintf(fptr,"FOUND NOT EQUAL\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"!=",second_num_op);} else {$$=translate_operation($1,"!=",$3);} }
	| expr GT expr 	{printf("\nFOUND IS GREATER THAN OPERATION\n"); fprintf(fptr,"FOUND GREATER THAN\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,">",second_num_op);} else{$$=translate_operation($1,">",$3);} }
	| expr LT expr 	{printf("\nFOUND IS LESS THAN OPERATION\n"); fprintf(fptr,"FOUND LESS THAN\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"<",second_num_op);} else{$$=translate_operation($1,"<",$3);}}
	| expr GE expr 	{printf("\nFOUND IS GREATER EQUAL OPERATION\n"); fprintf(fptr,"FOUND GREATER EQUAL\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,">=",second_num_op);} else{$$=translate_operation($1,">=",$3);} }
	| expr LE expr 	{printf("\nFOUND IS LESS EQUAL OPERATION\n"); fprintf(fptr,"FOUND LESS EQUAL\n"); if(match_number($1)&&match_number($3)){/*do 2 pop operations*/ char *second_num_op=pop_num(); char *first_num_op=pop_num(); $$=translate_operation(first_num_op,"<=",second_num_op);} else{$$=translate_operation($1,"<=",$3);}}
	| expr AND expr 	{printf("\nFOUND AND OPERATION\n"); fprintf(fptr,"FOUND AND\n"); $$=translate_operation($1,"and",$3);}
	| expr OR expr 	{printf("\nFOUND OR OPERATION\n"); fprintf(fptr,"FOUND OR\n"); $$=translate_operation($1,"or",$3);}
	| VARIABLE PPL	{printf("\nexpr is a variable increment\n"); printf("Increment variable %s\n",$1); add_new_var_to_check($1+1); added_var_to_check=true; fprintf(fptr,"FOUND VAR INCREM\n");  $$=translate_increment("++",$1+1);}
	| VARIABLE MMN	{printf("\nexpr is a variable decrement\n"); printf("decrement variable %s\n",$1); add_new_var_to_check($1+1); added_var_to_check=true; fprintf(fptr,"FOUND VAR DECREM\n");  $$=translate_increment("--",$1+1);}
	| NOT expr 		{printf("\nFOUND NOT OPERATION\n"); fprintf(fptr,"FOUND NOT\n"); $$=translate_not_operation("not",$2);}
	| ECH RD1 expr RD2	{printf("\nFOUND ECHO OPERATION WITH ROUND BRACKETS \n"); fprintf(fptr,"FOUND ECHO\n"); $$=translate_print($3);}
	| ECH expr	{printf("\nFOUND ECHO OPERATION\n"); fprintf(fptr,"FOUND ECHO\n"); $$=translate_print($2);}
	| PRT RD1 expr RD2	{printf("\nFOUND PRINT OPERATION WITH ROUND BRACKETS\n"); fprintf(fptr,"FOUND PRINT\n"); $$=translate_print($3);}
	| PRT expr	{printf("\nFOUND PRINT OPERATION\n"); fprintf(fptr,"FOUND PRINT\n"); $$=translate_print($2);}
	| RTN expr	{printf("\nFOUND RETURN OPERATION\n"); fprintf(fptr,"FOUND RETURN\n"); $$=translate_return($2);}
	| NAME RD1 params RD2	{printf("\nFOUND FUNCT CALL here since semicolon problems\n"); fprintf(fptr,"FOUND FUNCTION CALL\n"); add_new_func_to_check($1); added_func_to_check=true; /*check n params*/ int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n %s",actual_context[0],actual_context[1],$1); check_n_params_match(hash($1),$1,FUN,actual_context[0],actual_context[1],get_number_params()); $$=translate_function_call($1);}
	| readline	{printf("\nFOUND READLINE CALL\n"); fprintf(fptr,"FOUND READLINE CALL\n");}
	| arraypop	{printf("\nFOUND ARRAYPOP CALL\n"); fprintf(fptr,"FOUND ARRAYPOP CALL\n");}
	| arraysum	{printf("\nFOUND ARRAY SUM \n"); fprintf(fptr,"FOUND ARRAYSUM CALL\n");}
	| strlen	{printf("\nFOUND A STRLEN \n"); fprintf(fptr,"FOUND STRLEN CALL\n");}
	| arraypush	{printf("\nFOUND ARRAYPUSH CALL \n"); fprintf(fptr,"FOUND ARRAYPUSH CALL\n");}
	| sort	{printf("\nFOUND SORT CALL \n"); fprintf(fptr,"FOUND SORT CALL\n");}
	;
params: expr	{printf("\n FOUND NEW PARAMS_ \n"); increase_number_params(); push($1);}
	| params CM expr {printf("\nFOUND PARAMS\n"); increase_number_params(); push($3);}
	| /* no params */ {$$=NULL;}
	;
varparams: VARIABLE	{printf("found varparam\n"); fprintf(fptr,"FOUND PARAMETER VARIABLE\n"); add_item(hash($1+1),$1+1,VAR,FUNCTIONSCOPE,function_number,0,0); increase_number_varparams(); push($1+1);}
	| varparams CM VARIABLE {printf("found varparamsss\n"); fprintf(fptr,"FOUND PARAMETER VARIABLE\n"); add_item(hash($3+1),$3+1,VAR,FUNCTIONSCOPE,function_number,0,0); increase_number_varparams(); push($3+1);}
	| /* no params */ {$$=NULL;}
	;
optionsort: NAME	{printf("\nFOUND SORT OPTIION \n"); fprintf(fptr,"FOUND SORT OPTION \n"); increase_number_params(); push($1);}
	| optionsort SOR NAME {increase_number_params(); push($3);}
	;
cond: IF RD1 expr RD2 lineinifcondition	{printf("\nFOUND IF WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(IFCONDITIONSCOPE,if_number); check_all_items_in_context(actual_context[0],actual_context[1]); erase_var_if(); erase_func_if(); increaseIfNumber(); $$=organize_if($3);}
	| IF RD1 expr RD2 lineinifcondition ELS lineinelsecondition	{printf("\nFOUND IF WITH ONE LINE BODY AND ELSE WITH ONE LINE  BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSE WITH ONE LINE  BODY\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number);  print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else();  $$=merge_condition(2,organize_if($3),organize_else());}
	| IF RD1 expr RD2 lineinifcondition EIF RD1 expr RD2 lineinelseifcondition	{printf("\nFOUND IF WITH ONE LINE BODY AND ELSEIF WITH ONE LINE  BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSEIF WITH ONE LINE  BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); $$=merge_condition(2,organize_if($3),organize_elseif($8));}		
	| IF RD1 expr RD2 CR1 linesinifcondition CR2	{printf("\nFOUND IF WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(IFCONDITIONSCOPE,if_number); check_all_items_in_context(actual_context[0],actual_context[1]); erase_var_if(); erase_func_if(); increaseIfNumber(); $$=organize_if($3);}
	| IF RD1 expr RD2 lineinifcondition EIF RD1 expr RD2 lineinelseifcondition ELS lineinelsecondition	{printf("\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($8),organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 ELS lineinelsecondition	{printf("\nFOUND IF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); $$=merge_condition(2,organize_if($3),organize_else());}
	| IF RD1 expr RD2 lineinifcondition ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true;  erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); $$=merge_condition(2,organize_if($3),organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_else()); increaseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_func_if(); erase_func_else(); $$=merge_condition(2,organize_if($3),organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 EIF RD1 expr RD2 lineinelseifcondition	{printf("\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); $$=merge_condition(2,organize_if($3),organize_elseif($10));}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 EIF RD1 expr RD2 CR1 linesinelseifcondition CR2	{printf("\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY AND ELSEIF WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSEIFCONDITIONSCOPE,elseif_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_if(),get_var_if()+get_var_elseif()); check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_if(),get_func_if()+get_func_elseif()); increaseIfNumber();increaseElseIfNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_elseif(); erase_func_if(); erase_func_elseif(); $$=merge_condition(2,organize_if($3),organize_elseif($10));}
	| IF RD1 expr RD2 lineinifcondition EIF RD1 expr RD2 lineinelseifcondition ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY , ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber(); increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($8),organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 EIF RD1 expr RD2 lineinelseifcondition ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($10), organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 EIF RD1 expr RD2 CR1 linesinelseifcondition CR2 ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($10), organize_else());}
	| IF RD1 expr RD2 CR1 linesinifcondition CR2 EIF RD1 expr RD2 lineinelseifcondition ELS lineinelsecondition	{printf("\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n");fprintf(fptr,"\nFOUND IF WITH MORE LINES BODY, ELSEIF WITH ONE LINE BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($10),organize_else());}
	| IF RD1 expr RD2 lineinifcondition EIF RD1 expr RD2 CR1 linesinelseifcondition CR2 ELS CR1 linesinelsecondition CR2	{printf("\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH MORE LINES BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($8), organize_else());}
	| IF RD1 expr RD2 lineinifcondition EIF RD1 expr RD2 CR1 linesinelseifcondition CR2 ELS lineinelsecondition	{printf("\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); fprintf(fptr,"\nFOUND IF WITH ONE LINE BODY, ELSEIF WITH MORE LINES BODY AND ELSE WITH ONE LINE BODY\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); close_context(ELSECONDITIONSCOPE,else_number); print_var_to_check(); print_func_to_check(); check_all_items_var_in_context_cond_specific(actual_context[0],actual_context[1],get_var_elseif(),get_var_if()+get_var_elseif()+get_var_else());  check_all_items_funct_in_context_cond_specific(actual_context[0],actual_context[1],get_func_elseif(),get_func_if()+get_func_elseif()+get_func_else()); increaseIfNumber();increaseElseIfNumber();increaseElseNumber(); flag_close_if_elseif=true; erase_var_if(); erase_var_else(); erase_var_elseif(); erase_func_if(); erase_func_else(); erase_func_elseif(); $$=merge_condition(3,organize_if($3),organize_elseif($8), organize_else());}
 	;
swcond: SWH RD1 VARIABLE RD2 CR1 cases CR2	{printf("\nFOUND SWITCH STATEMENT\n"); fprintf(fptr,"FOUND SWITCH\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=merge_switch_cases($3+1);}
	;
cases: case
	| cases case 
	| /* no cases */
	;	
case: CSE expr CL linesinswitchcase BRK SC	{printf("\nFOUND A CASE \n"); fprintf(fptr,"FOUND CASE\n"); close_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); check_all_items_in_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); add_in_switch_cases(organize_case($2)); increaseSwitchCaseDefaultNumber();}
	| DFT CL linesinswitchdefault			{printf("\nFOUND A DEFAULT \n"); fprintf(fptr,"FOUND DEFAULT CASE\n"); close_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); check_all_items_in_context(SWITCHCASEDEFAULTSCOPE,switch_case_default_number); add_in_switch_cases(organize_default()); increaseSwitchCaseDefaultNumber();}
	;
funct: FNC NAME RD1 varparams RD2 CR1 linesinfunction CR2	{printf("\nFOUND FUNCTION DEFINITION\n"); fprintf(fptr,"FOUND FUNCTION DEFINITION\n"); printf("My function name %s and its hash %d",$2,hash($2)); close_context(FUNCTIONSCOPE,function_number); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); add_item(hash($2),$2,FUN,actual_context[0],actual_context[1],0,get_number_varparams()); /*check variables in this block*/  check_all_items_in_context(FUNCTIONSCOPE,function_number);  increaseFunctionNumber(); $$=organize_function_def($2);}
	| NAME RD1 params RD2 SC	{printf("\nFOUND FUNCTION CALL\n"); fprintf(fptr,"FOUND FUNCTION CALL\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($1),$1,FUN,actual_context[0],actual_context[1]); check_n_params_match(hash($1),$1,FUN,actual_context[0],actual_context[1],get_number_params()); $$=organize_function_call($1);}
	;
while: WHL RD1 expr RD2 CR1 linesinwhile CR2	{printf("\nFOUND WHILE LOOP\n"); fprintf(fptr,"FOUND WHILE\n"); close_context(WHILESCOPE,while_number); check_all_items_in_context(WHILESCOPE,while_number); increaseWhileNumber(); $$=organize_while($3);}
	;
foreachvar: VARIABLE {printf("\nexpr is a foreach variable\n");  add_item(hash($1+1),$1+1,VAR,FOREACHSCOPE,foreach_number,0,0); add_new_open_context(FOREACHSCOPE, foreach_number); $$=$1+1; }
	;
foreach: FRC RD1 VARIABLE AS foreachvar RD2 CR1 linesinforeach CR2	{printf("\nFOUND FOREACH with array into variable - check in semantic later\n"); fprintf(fptr,"FOUND FOREACH\n"); close_context(FOREACHSCOPE,foreach_number); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is array*/ check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); check_all_items_in_context(FOREACHSCOPE,foreach_number); add_item(hash($5),$5,VAR,FOREACHSCOPE,foreach_number,0,0); increaseForeachNumber(); $$=organize_foreach($3+1,$5);}
	| FRC RD1 ARR RD1 params RD2 AS foreachvar RD2 CR1 linesinforeach CR2	{printf("\nFOUND FOREACH with array definition into the construct\n");fprintf(fptr,"FOUND FOREACH\n"); close_context(FOREACHSCOPE,foreach_number); check_all_items_in_context(FOREACHSCOPE,foreach_number); $$=organize_foreach_arraydef($8);}
	;
readline: RDL RD1 STRING RD2	{printf("\nFOUND READLINE\n");fprintf(fptr,"FOUND READLINE\n"); $$=translate_readline($3);}
	;
arraypop: APOP RD1 VARIABLE RD2	{printf("\nFOUND ARRAYPOP\n");fprintf(fptr,"FOUND ARRAYPOP\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=translate_arraypop($3+1);}
	;
arraypush: APUS RD1 VARIABLE CM params RD2	{printf("\nFOUND ARRAYPUSH\n");fprintf(fptr,"FOUND ARRAYPUSH\n");   int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=translate_arraypush($3+1);}
	;
arraysum: ASUM RD1 VARIABLE RD2	{printf("\nFOUND ARRAYSUM\n");fprintf(fptr,"FOUND ARRAYSUM\n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]);  check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=translate_arraysum($3+1);}
	;
sort: SRT RD1 VARIABLE RD2	{printf("\nFOUND SORT \n");  int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=translate_sort($3+1);}
	| SRT RD1 VARIABLE CM optionsort RD2	{printf("\nFOUND SORT WITH OPTIIONS \n");fprintf(fptr,"FOUND SORT WITH OPTIONS\n"); int *actual_context = get_last_open_context(); printf("\nCONTEXT: %d-%d\n",actual_context[0],actual_context[1]); check_item_in_context(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); /*check if var is an array*/ check_if_var_is_array(hash($3+1),$3+1,VAR,actual_context[0],actual_context[1]); $$=translate_sort_options($3+1);}
	;
strlen: SLE RD1 VARIABLE RD2	{printf("\nFOUND STRLEN WITH VARIABLE \n"); fprintf(fptr,"FOUND STRLEN WITH VARIABLE\n"); add_new_var_to_check($3+1); added_var_to_check=true; $$=translate_strlen($3);}
	| SLE RD1 STRING RD2	{printf("\nFOUND STRLEN WITH STRING \n"); fprintf(fptr,"FOUND STRLEN WITH STRING\n"); $$=translate_strlen($3);}
	;
%%

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


