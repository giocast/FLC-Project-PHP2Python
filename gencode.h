#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include "valuesmemory.h"

FILE *outputptr;

int counter_params = 0;
int counter_varparams = 0;

int counter_instr_if = 0;
int counter_instr_else = 0;
int counter_instr_elseif = 0;

int counter_instr_case = 0;
int counter_instr_default = 0;

int counter_instr_while = 0;

int counter_instr_funct = 0;

int counter_instr_foreach = 0;

int counter_instr_sub_block = 0;

int array_accesses = 0; //useful to count number of accesses to array if we have them in one operation e.g. translate properly a[1]+a[3]
char *array_access = "false"; //true if we have an array access (useful when 1+ operator of operation is an array access)





void open_dest_file()
{
	outputptr = fopen("output_traslated.py","a");
}


void increase_number_params()
{
	counter_params++;
	printf("\n\n*****Increased number params %d\n\n",counter_params);
}

int get_number_params() 
{
	return counter_params;
}

void increase_number_varparams()
{
	counter_varparams++;
	printf("\n\n*****Increased number varparams %d\n\n",counter_varparams);
}

int get_number_varparams()
{
	return counter_varparams;
}

void increase_number_instr_if()
{
	counter_instr_if++;
	printf("\n\n*****Increased number instr if %d\n\n",counter_instr_if);
}

void increase_number_instr_else()
{
	counter_instr_else++;
	printf("\n\n*****Increased number instr else %d\n\n",counter_instr_else);
}

void increase_number_instr_elseif()
{
	counter_instr_elseif++;
	printf("\n\n*****Increased number instr elseif %d\n\n",counter_instr_elseif);
}

void increase_number_instr_case()
{
	counter_instr_case++;
	printf("\n\n*****Increased number instr case %d\n\n",counter_instr_case);
}

void increase_number_instr_default()
{
	counter_instr_default++;
	printf("\n\n*****Increased number instr default %d\n\n",counter_instr_default);
}

void increase_number_instr_while()
{
	counter_instr_while++;
	printf("\n\n*****Increased number instr while %d\n\n",counter_instr_while);
}

void increase_number_instr_funct()
{
	counter_instr_funct++;
	printf("\n\n*****Increased number instr funct %d\n\n",counter_instr_funct);
}

void increase_number_instr_foreach()
{
	counter_instr_foreach++;
	printf("\n\n*****Increased number instr foreach %d\n\n",counter_instr_foreach);
}

int get_number_instr_if()
{
	return counter_instr_if;
}

int get_number_instr_else()
{
	return counter_instr_else;
}

int get_number_instr_elseif()
{
	return counter_instr_elseif;
}


char *translate_bool(char *php_bool)
{
	char *py_bool = malloc(strlen(php_bool)+1);
	py_bool[0] = '\0';
	
	if(strcmp(php_bool,"true")==0||strcmp(php_bool,"false")==0)
	{
		strcpy(py_bool,php_bool);
		py_bool[0]-=32;
	}
	return py_bool;
}

char *translate_array_access(char *array, char *index)
{
	char *array_access = malloc(strlen(array) + 6);
	array_access[0] = '\0';
	strcat(array_access,array);
	strcat(array_access,"[");
	strcat(array_access,index);
	strcat(array_access,"]");
	
	return array_access;

}

char *translate_array_definition()
{
	char *params[counter_params];
	
	char *array_definition = malloc(100);
	array_definition[0] = '\0';
	for(int i=0; i<counter_params; i++) {
			
		params[i]=pop();
	}

	strcat(array_definition,"[");
				
	for(int i=counter_params-1; i>=0; i--) {
		strcat(array_definition, params[i]);
				
		if(i!=0)
			strcat(array_definition,", ");
		}
			
	strcat(array_definition,"]");

	counter_params = 0;
	
	return array_definition;
}


char *translate_function_call(char *function_name)
{
	char *params[counter_params];
	
	char *function_call = malloc(strlen(function_name)+100);
	function_call[0] = '\0';
	for(int i=0; i<counter_params; i++) {
			
		params[i]=pop();
	}
			
	strcat(function_call,function_name);
	strcat(function_call,"(");
				
	for(int i=counter_params-1; i>=0; i--) {
		strcat(function_call, params[i]);
				
		if(i!=0)
			strcat(function_call,", ");
		}
			
	strcat(function_call,")");

	counter_params = 0;
	
	return function_call;
}


char *translate_operation(char *operator1, char *operation, char *operator2)
{
	printf("\n\nOPERANDS: %s and %s\n\n",operator1, operator2);
	char *op = malloc(strlen(operator1)+strlen(operator2)+15);
	op[0] = '\0';
	strcat(op,operator1);
	strcat(op," ");
	strcat(op,operation);
	strcat(op," ");
	strcat(op,operator2);
	
	return op;
}

char *translate_not_operation(char *not, char *operator1)
{
	char *op = malloc(strlen(operator1)+5);
	op[0] = '\0';
	strcat(op,not);
	strcat(op," ");
	strcat(op,operator1);
	
	return op;
}

char *translate_increment(char *oper, char *operator1)
{
	char *op = malloc(strlen(operator1)+5);
	op[0] = '\0';
	strcat(op,operator1);
	if(strcmp(oper,"++")==0) {
	strcat(op,"+=1");
	}
	else if(strcmp(oper,"--")==0) {
	strcat(op,"-=1");
	}
	
	return op;
}


char *translate_print(char *content)
{	
	char *print = malloc(strlen(content)+50);
	print[0] = '\0';
	strcat(print,"print(");
	strcat(print,content);
	strcat(print,")");
	
	return print;
}


char *translate_readline(char *string)
{
	
	char *readline= malloc(strlen(string)+10);
	readline[0] = '\0';
	strcat(readline,"input(");
	strcat(readline,string);
	strcat(readline,")");
	
	return readline;

}

char *translate_arraypop(char *var)
{
	char *arraypop= malloc(strlen(var)+6);
	arraypop[0] = '\0';
	strcat(arraypop,var);
	strcat(arraypop,".pop()");
	
	return arraypop;
}

char *translate_arraypush(char *var)
{
	char *params[counter_params];
	
	char *array_push = malloc(strlen(var)+100);
	array_push[0] = '\0';
	for(int i=0; i<counter_params; i++) {
			
		params[i]=pop();
	}
		
	strcat(array_push,var);
	strcat(array_push,".push");
	strcat(array_push,"(");
				
	for(int i=counter_params-1; i>=0; i--) {
		strcat(array_push, params[i]);
				
		if(i!=0)
			strcat(array_push,", ");
		}
			
	strcat(array_push,")");

	counter_params = 0;
	
	return array_push;

}

char *translate_arraysum(char *var)
{
	char *arraysum= malloc(strlen(var)+6);
	arraysum[0] = '\0';
	strcat(arraysum,"sum(");
	strcat(arraysum,var);
	strcat(arraysum,")");
	
	return arraysum;
}

char *translate_sort(char *var)
{
	char *sort= malloc(strlen(var)+6);
	sort[0] = '\0';
	strcat(sort,var);
	strcat(sort,".sort()");
	
	return sort;
}

char *translate_strlen(char *var)
{
	char *str= malloc(strlen(var)+10);
	str[0] = '\0';
	strcat(str,"len(");
	strcat(str,var);
	strcat(str,")");
	
	return str;

}

char *translate_sort_options(char *var)
{
	char *params[counter_params];
	
	char *sort = malloc(strlen(var)+100);
	sort[0] = '\0';
	for(int i=0; i<counter_params; i++) {
			
		params[i]=pop();
	}
	
	strcat(sort,var);
	strcat(sort,".sort");
	strcat(sort,"(");
	
	
	for(int i=counter_params-1; i>=0; i--) {
		
		if(strcmp(params[i],"SORT_NUMERIC")==0) {
			strcat(sort,"key = int");
		}
		else if(strcmp(params[i],"SORT_REGULAR")==0||strcmp(params[i],"SORT_STRING")==0||strcmp(params[i],"SORT_LOCALE_STRING")==0||strcmp(params[i],"SORT_FLAG_CASE")==0) {
			//do nothing
		}
		else if(strcmp(params[i],"SORT_NATURAL")==0) {
			//do nothing
			char *temp = strdup(sort);
			char *imports = "from natsort import natsort_keygen\nnatsort_key = natsort_keygen(key=lambda y: y.lower())\n";
			strcpy(sort,imports);
			strcat(sort,temp);
			strcat(sort,"key=natsort_key");
		}
				
			
	strcat(sort,")");

	counter_params = 0;
	
	return sort;
}
}



char *merge_condition(int numberblocks, ...) {
	
	
	va_list list;
	int length = 0;
	char *p;
	
   	va_start(list, numberblocks); 
	int j=0;
	while(j<numberblocks) {
		p = va_arg(list, char *);
		length += strlen(p);
		j++;
	}
   	va_end(list);

	

	char *ret = malloc(length+300);
	ret[0] = '\0';
	va_start(list, numberblocks); 
   	for(int i=0; i < numberblocks; i++)
   	{
   		strcat(ret,va_arg(list, char*));
		strcat(ret,"\n");
   	}
   	va_end(list);
	
	return ret;
	
}

char *organize_if(char *cond) {
	char *params[counter_instr_if];
	
	char *condition = malloc(strlen(cond)+800);
	condition[0] = '\0';
	strcat(condition,"if ");
	strcat(condition,cond);
	strcat(condition,":");
	
	if(counter_instr_if!=0) {
		for(int i=0; i<counter_instr_if; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		for(int i=counter_instr_if-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty if block!\n");
	}
	
	
	counter_instr_if = 0;
	
	return condition;

}


char *organize_elseif(char *cond) {
	char *params[counter_instr_elseif];
	
	char *condition = malloc(strlen(cond)+800);
	condition[0] = '\0';
	strcat(condition,"elif ");
	strcat(condition,cond);
	strcat(condition,":");
	
	if(counter_instr_elseif!=0) {
		for(int i=0; i<counter_instr_elseif; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_instr_elseif-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty elseif block!\n");
	}
	
	
	
	counter_instr_elseif = 0;
	
	return condition;

}

char *organize_else() {

	char *params[counter_instr_else];
	
	char *condition = malloc(800);
	condition[0] = '\0';
	strcat(condition,"else:");
	
	
	if(counter_instr_else!=0) {
		for(int i=0; i<counter_instr_else; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		for(int i=counter_instr_else-1; i>=0; i--) {
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty else block!\n");
	}
	
	
	
	counter_instr_else = 0;
	
	return condition;

}


char *organize_case(char *case_value) {

	char *params[counter_instr_case];
	
	char *condition = malloc(strlen(case_value)+800);
	condition[0] = '\0';
	strcat(condition,"case ");
	strcat(condition,case_value);
	strcat(condition,":");
	
	
	if(counter_instr_case!=0) {
		for(int i=0; i<counter_instr_case; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_instr_case-1; i>=0; i--) {
		
				strcat(condition, "\t\t\n");
				strcat(condition, params[i]);	
		}
		// Not needed by syntax -> strcat(condition, "\n\t\tbreak");
		
	}
	else {
		printf("\nEmpty if block!\n");
	}
	
	
	counter_instr_case = 0;
	
	return condition;

}


char *organize_default() {

	char *params[counter_instr_default];
	
	char *condition = malloc(800);
	condition[0] = '\0';
	strcat(condition,"case _:");
	
	
	
	if(counter_instr_default!=0) {
		for(int i=0; i<counter_instr_default; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_instr_default-1; i>=0; i--) {
		
				strcat(condition, "\n\t\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty if block!\n");
	}
	
	
	counter_instr_default = 0;
	
	return condition;

}


char *organize_while(char *cond) {
	char *params[counter_instr_while];
	
	char *condition = malloc(strlen(cond)+800);
	condition[0] = '\0';
	strcat(condition,"while ");
	strcat(condition,cond);
	strcat(condition,":");
	
	
	
	if(counter_instr_while!=0) {
		for(int i=0; i<counter_instr_while; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_instr_while-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty while block!\n");
	}
	
	
	counter_instr_while = 0;
	
	return condition;

}

char *organize_function_call(char *name) {

	char *params[counter_params];
	
	char *condition = malloc(strlen(name)+800);
	condition[0] = '\0';
	strcat(condition,name);
	
	
	
	if(counter_params!=0) {
		strcat(condition,"(");
		for(int i=0; i<counter_params; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_params-1; i>=0; i--) {
				
				strcat(condition, params[i]);
				
				if(i!=0) {
					strcat(condition, ", ");
				}
				
		}
		
		
		strcat(condition,")");
	}
	else {
		strcat(condition,"()");
		printf("\nEmpty params in func!\n");
	}
	
	
	counter_params = 0;
	
	return condition;

}


char *organize_function_def(char *name) {
	char *params[counter_varparams];
	char *params2[counter_instr_funct];
	
	
	char *condition = malloc(strlen(name)+1800);
	condition[0] = '\0';
	//write the name and params
	strcat(condition,"def ");
	strcat(condition,name);
	
	
	//body
	if(counter_instr_funct!=0) {
		for(int i=0; i<counter_instr_funct; i++) {
				
			params2[i]=pop();
			printf("\nP O P %s\n\n",params2[i]);
		}
	}
	else {
		printf("\nEmpty else block!\n");
	}
	
	
	//params
	if(counter_varparams!=0) {
		
		for(int i=0; i<counter_varparams; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n\n",params[i]);
		}
	}
	else {
		printf("\nEmpty params in func!\n");
	}
	
	
	
	//organizing...
	
	if(counter_varparams!=0) {
		strcat(condition,"(");
		
		for(int i=counter_varparams-1; i>=0; i--) {
				
				strcat(condition, params[i]);
				
				if(i!=0) {
					strcat(condition, ", ");
				}
					
		}
		
		
		strcat(condition,"):");
	}
	else {
		strcat(condition,"():");
	}
	
	
	
	
	if(counter_instr_funct!=0) {
		for(int i=counter_instr_funct-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params2[i]);
		}
		
	}
	else {
		printf("\nEmpty else block!\n");
	}
	
	
	
	counter_varparams = 0;
	counter_instr_funct = 0;
	
	
	return condition;
	

}


char *organize_foreach(char *array, char *var) {
	
	char *params[counter_instr_foreach];
	
	char *condition = malloc(strlen(array)+strlen(var)+800);
	condition[0] = '\0';
	strcat(condition,"for ");
	strcat(condition,var);
	strcat(condition," in ");
	strcat(condition,array);
	strcat(condition,":");
	
	
	
	if(counter_instr_foreach!=0) {
		for(int i=0; i<counter_instr_foreach; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
		
		
		for(int i=counter_instr_foreach-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty foreach block!\n");
	}
	
	
	counter_instr_foreach = 0;
	
	return condition;

}

char *organize_foreach_arraydef(char *var){

	char *condition = malloc(strlen(var)+900);
	
	char *arraydef = malloc(100);
	char *params[counter_instr_foreach];
	condition[0] = '\0';
	arraydef[0] = '\0';
	
	
	if(counter_instr_foreach!=0) {
		for(int i=0; i<counter_instr_foreach; i++) {
				
			params[i]=pop();
			printf("\nP O P %s\n\n",params[i]);
		}
	}
	
	arraydef=translate_array_definition();
	
	
	strcat(condition,"for ");
	strcat(condition,var);
	strcat(condition," in ");
	strcat(condition,arraydef);
	strcat(condition,":");
	
	if(counter_instr_foreach!=0) {
		
		for(int i=counter_instr_foreach-1; i>=0; i--) {
		
				strcat(condition, "\n\t");
				strcat(condition, params[i]);
		}
		
	}
	else {
		printf("\nEmpty foreach block!\n");
	}
	
	
	counter_instr_foreach = 0;
	
	return condition;

}


char *organize_declaration(char *var, char *expr)
{	
	char *declaration = malloc(strlen(var)+strlen(expr)+100);
	declaration[0] = '\0';
	strcat(declaration,var);
	strcat(declaration," = ");
	strcat(declaration,expr);

	return declaration;
	
}


void translate_cond(char *ifblock)
{
	fprintf(outputptr,"%s\n\n",ifblock);
}

char *translate_return(char *returnblock)
{
	char *returning = malloc(strlen(returnblock) + 6);
	returning[0] = '\0';
	strcat(returning,"return ");
	strcat(returning,returnblock);
	strcat(returning,"\n");
	return returning;
}

void translate_switch(char *switchblock)
{
	fprintf(outputptr,"%s\n\n",switchblock);
}

void translate_funct(char *functblock)
{
	fprintf(outputptr,"%s\n\n",functblock);
}

void translate_while(char *whileblock)
{
	fprintf(outputptr,"%s\n\n",whileblock);	
}

void translate_foreach(char *foreachblock)
{
	fprintf(outputptr,"%s\n\n",foreachblock);
}

void translate_declaration(char *decl)
{
	fprintf(outputptr,"%s\n",decl);
}

void translate_comment(char *decl)
{
	fprintf(outputptr,"%s\n",decl);
}

void translate_expr(char *expr)
{
	fprintf(outputptr,"%s\n",expr);
}





