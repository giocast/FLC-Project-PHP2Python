#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "uthash.h"

#define SIZE 32768
#define VAR 1
#define FUN 2

struct sym_table_struct {
	int id; /* key of item: int hash generated from the name: in case of same name we generate new random key (iterative until unique)*/
	char name[30]; /* name of item */
	int type; /* type of item, in order to distinct identifier and function name */
	int scope; /* scope/context where item is valid/defined/... */
	int nscope; /* scope/context NUMBER where item is valid/defined/... -> at the end: scope like IF(8) 2*/
	int line; /* line where found */
	
	int isarray; //0 means is not an array. 1 means is an array
	int nparams; //n elements array or n params function
	
	UT_hash_handle hh; /* makes this structure hashable */ 
};

struct sym_table_struct *symbol_table = NULL;




#define LIMIT_ELEMENTS_ARRAY 100 //maximum limit of the array
#define LIMIT_LENGTH_ELEMENT_ARRAY 50 //maximum size of elements in array (in order to avoid problems with dimensions)

char variables_to_check[LIMIT_ELEMENTS_ARRAY][LIMIT_LENGTH_ELEMENT_ARRAY];
char functions_to_check[LIMIT_ELEMENTS_ARRAY][LIMIT_LENGTH_ELEMENT_ARRAY]; 
int last_var; //index to current last element in the stack
int last_func; //index to current last element in the stack


int open_contexts[LIMIT_ELEMENTS_ARRAY]; //this structure contains infos about open context (where a particular variable is called and the context check must be performed in)....pair of records, e.g. |GLOBAL|0|
int last_context; //will be incremented by 2


int num_var_to_check_from_if = 0;
int num_var_to_check_from_else = 0;
int num_func_to_check_from_if = 0;
int num_func_to_check_from_else = 0;
int num_var_to_check_from_elseif = 0;
int num_func_to_check_from_elseif = 0;

void increase_var_if(){
	num_var_to_check_from_if++;
	printf("\nIncreasing number of variables to check in if %d \n",num_var_to_check_from_if);
}

void increase_var_else(){
	num_var_to_check_from_else++;
	printf("\nIncreasing number of variables to check in else  %d \n",num_var_to_check_from_else);
}

void increase_var_elseif(){
	num_var_to_check_from_elseif++;
	printf("\nIncreasing number of variables to check in elseif  %d \n",num_var_to_check_from_elseif);
}

void increase_func_if(){
	num_func_to_check_from_if++;
	printf("\nIncreasing number of functions to check in if %d \n",num_func_to_check_from_if);
}

void increase_func_else(){
	num_func_to_check_from_else++;
	printf("\nIncreasing number of functions to check in else %d \n",num_func_to_check_from_else);
}

void increase_func_elseif(){
	num_func_to_check_from_elseif++;
	printf("\nIncreasing number of functions to check in elseif %d \n",num_func_to_check_from_elseif);
}


int get_var_if(){
	
	return num_var_to_check_from_if;
}
int get_var_else(){
	
	return num_var_to_check_from_else;
}
int get_var_elseif(){
	
	return num_var_to_check_from_elseif;
}
int get_func_if(){
	
	return num_func_to_check_from_if;
}
int get_func_else(){
	
	return num_func_to_check_from_else;
}
int get_func_elseif(){
	
	return num_func_to_check_from_elseif;
}

void erase_var_if(){
	printf("\n Erasing variables to check in if \n");
	num_var_to_check_from_if = 0;
}

void erase_var_else(){
	printf("\n Erasing variables to check in else \n");
	num_var_to_check_from_else = 0;
}

void erase_var_elseif(){
	printf("\n Erasing variables to check in elseif \n");
	num_var_to_check_from_elseif = 0;
}

void erase_func_if(){
	printf("\n Erasing functions to check in if \n");
	num_func_to_check_from_if = 0;
}

void erase_func_else(){
	printf("\n Erasing functions to check in else \n");
	num_func_to_check_from_else = 0;
}
void erase_func_elseif(){
	printf("\n Erasing functions to check in elseif \n");
	num_func_to_check_from_elseif = 0;
}




void add_new_var_to_check(char *element)
{
	if(last_var == LIMIT_ELEMENTS_ARRAY)
	{
		printf("Overflow var\n");
	}
	else
	{
		
		variables_to_check[last_var][strlen(element) + 1];
		strcpy(variables_to_check[last_var], element);
		last_var++;
		printf("\nPutting element %s in VARIABLES TO CHECK\n",element);
	}
}

void print_var_to_check() {
	
	printf("\n\nVARIABLES TO CHECK: {");
	for(int i=0; i<last_var; i++) {	
		printf(" %s ",variables_to_check[i]);
	}
	printf("}\n\n");
}

void add_new_func_to_check(char *element)
{
	if(last_func == LIMIT_ELEMENTS_ARRAY)
	{
		printf("Overflow func\n");
	}
	else
	{
		
		functions_to_check[last_func][strlen(element) + 1];
		strcpy(functions_to_check[last_func], element);
		last_func++;
		printf("\n\nPutting element %s in FUNCTIONS TO CHECK\n\n",element);
	}
}

void print_func_to_check() {
	
	printf("\n\n FUNCTIONS TO CHECK: {");
	for(int i=0; i<last_func; i++) {	
		printf(" %s ",functions_to_check[i]);
	}
	printf("}\n\n");
}

void add_new_open_context(int scope, int scope_num)
{
	if(last_context == LIMIT_ELEMENTS_ARRAY)
	{
		printf("\nOverflow open contexts\n");
	}
	else
	{
		bool exists = false;
		
		for(int i=0; i<last_context; i+=2) {
		
			if(open_contexts[i]==scope && open_contexts[i+1]==scope_num) {
				printf("\n\nExists already open context %d-%d\n\n",scope,scope_num);
				exists=true;
				break;
			}
		
		}
		
		if(!exists) {
		
			open_contexts[last_context]=scope;
			open_contexts[last_context+1]=scope_num;
			
			last_context+=2;
			printf("\nCONTEXT RECORD %d-%d in open contexts\n",scope,scope_num);
		
		}
		
		
	}
}


int *get_last_open_context() {
	
	static int last_open_context[2];
	for(int i=0; i<last_context; i+=2) {
	
		printf("\nSearching LAST CONTEXT...%d-%d\n",open_contexts[i],open_contexts[i+1]);
		if(i==last_context-2) {
			printf("\nFound LAST CONTEXT...%d-%d\n",open_contexts[i],open_contexts[i+1]);
			last_open_context[0]=open_contexts[i];
			last_open_context[1]=open_contexts[i+1];
		}	
	}
	
	return last_open_context;
		
}


void close_context(int scope, int scope_num)
{	
	for(int i=0; i<last_context; i+=2) {
	
		printf("\nSearching context to close...actual one %d-%d\n",open_contexts[i],open_contexts[i+1]);
		
		if(open_contexts[i]==scope && open_contexts[i+1]==scope_num) {
			printf("Removed context: closed\n");
			open_contexts[i]=-1;
			open_contexts[i+1]=-1;
			
			last_context-=2;
			
			break;
		} 
	}
}



struct sym_table_struct *find_item(int item_id)
{
	struct sym_table_struct *s;
	HASH_FIND_INT(symbol_table, &item_id, s);
	return s; 
}


void delete_item(struct sym_table_struct *item)
{
	HASH_DEL(symbol_table, item);
	free(item);
}

void delete_all()
{
	struct sym_table_struct *current_item;
	struct sym_table_struct *tmp;
	HASH_ITER(hh, symbol_table, current_item, tmp) {
		HASH_DEL(symbol_table, current_item);
		free(current_item);		
	} 
}

char * isarray_conv(int code) {
	char *a = malloc(25);
	switch(code) {
		case 0:
			strcpy(a, "no");
			break;
		case 1:
			strcpy(a, "yes");
			break;
	return a;
}
}

char * item_type_conv(int code) {
	char *a = malloc(25);
	
	switch(code){
	
		case 1:
			strcpy(a, "VAR");
			break;
		case 2:
			strcpy(a, "FUN");
			break;
	
	}
	return a;
}


const char * sym_conv(int code) {

	static char a[25];
	switch(code) {
		case 6:
			strcpy(a, "GLOBAL");
			break;
		case 7:
			strcpy(a, "FUNC");
			break;
		case 8:
			strcpy(a, "IF");
			break;
		case 9:
			strcpy(a, "ELSE");
			break;
		case 10:
			strcpy(a, "ELSEIF");
			break;
		case 11:
			strcpy(a, "WHILE");
			break;
		case 12:
			strcpy(a, "FOREACH");
			break;
		case 13:
			strcpy(a, "SWITCHCASEDEFAULT");
			break;
			
	}
	
	return a;
}

void print_items()
{
	struct sym_table_struct *s;
	
	for (s = symbol_table; s != NULL; s = (struct sym_table_struct*)(s->hh.next)) {
		printf("item id: %d --- name: %s --- type: %s  --- is_array: %s --- n params: %d--- scope: %s - %d \n", s->id, s->name, item_type_conv(s->type), isarray_conv(s->isarray), s-> nparams, sym_conv(s->scope), s->nscope); 
	}
}

//int ids[100] array globale contenente id degli item che hanno stesso name dell'item considerato(WHY? IN DIVERSI SCOPES, es. 2 if diversi posso avere stessi nomi di var, controllare conflitti)
#define UNINITIALIZED -1
int ids[100]={ [0 ... 99 ] = UNINITIALIZED };

int *return_items_id_by_name(const char *item_name)
{
	int i=0;
	struct sym_table_struct *s;
	
	for (s = symbol_table; s != NULL; s = (struct sym_table_struct*)(s->hh.next)) {
		printf("###FOR LOOP##\n");
		if(strcmp(s->name,item_name)==0)
		{
			printf("\n~~~~~~~~~~FOUND EQUAL NAME  %s WITH id: %d type: %d  AND scope: %d %d\n", s->name, s->id,  s->type, s->scope, s->nscope);
			ids[i]=s->id;
			i++;
		}
		 
	}
	
	
	//PRINTING IDS
	printf("IDS [");
	for (int i=0; i<100; i++)
		printf("%d ",ids[i]);
	printf("]");
	return ids;
}


static int rand_int(){

	return (int) (rand() % 32768);
}


void add_item(int item_id, const char *name, int item_type, int item_scope, int number_scope, int is_array, int n_params)
{
	printf("\n\n******SCOPE IS è %d - %d\n\n",item_scope, number_scope);
	srand(time(NULL)); //useful for random integer seed
	
	struct sym_table_struct *s;
	HASH_FIND_INT(symbol_table, &item_id, s);  /* id already in the hash? */
	if (s == NULL) {
		s = (struct sym_table_struct*)malloc(sizeof *s);
		s->id = item_id;
		HASH_ADD_INT(symbol_table, id, s); /* id is the key field */
		s->type = item_type;
		s->scope = item_scope;
		s->nscope = number_scope;
		s->isarray = is_array;
		s->nparams = n_params;
		strcpy(s->name, name);
	}
	else {
		int *test = return_items_id_by_name(name);
		
		if(test[0]!=UNINITIALIZED) {
			
			bool outcome = false;
			
			//es: sto inserendo item var X in contesto IF2 (dove cè già questa variabile)
			
			for(int i=0; test[i]!=UNINITIALIZED; i++) {
				//test[i] conterrà gli id degli item con stesso nome: CIO CHE FACCIO è CHECK CHE CONTESTO SIA STESSO MA TIPO NON LO STESSO: INSERISCO
				printf("ACTUAL test[i] = %d\n",test[i]);
				struct sym_table_struct *x; 
				x = find_item(test[i]);
				if(x->scope==item_scope && x->nscope==number_scope){
					//STESSO SCOPE E STESSO NOME, MI VA BENE
					if(x->type!=item_type){
						//QUI INSERISCO
						printf("\nINSERTING\n");
						outcome=true;
						
					} 
					else{
					//else NON INSERISCO
					}
					
				}
				
				else{
				//ELSE: DIVERSO SCOPE E STESSO NOME, NON MI INTERESSA: sto tentando di inserire in certo scope, controllo solo quello
				}
			}
			
			if(outcome) {
			
				//INSERISCO NELLO SCOPE CORRISP
				
				struct sym_table_struct *a;
						
				int new_ida = rand_int();
				printf("aNEW GENERATED ID %d",new_ida);
				HASH_FIND_INT(symbol_table, &new_ida, a);
				
				while(a!=NULL) {
					
					new_ida=rand_int();
					printf("\naREGEN ID %d \n",new_ida);
					HASH_FIND_INT(symbol_table, &new_ida, a);
				}
				
				a = (struct sym_table_struct*)malloc(sizeof *a);
				a->id = new_ida;
				HASH_ADD_INT(symbol_table, id, a);
				a->type = item_type;
				a->scope = item_scope;
				a->nscope = number_scope;
				a->isarray = is_array;
				a->nparams = n_params;
				strcpy(a->name, name);
	
			
			
			} else {
				printf("\nGOING TO OTHER CHECKS\n");
				goto inserimento;
			}
			
		
			//AZZERO IDS
			int ids[100] ={ [0 ... 99 ] = UNINITIALIZED };
		}
			
		
		
		
		else {
		
		//FLAG PER GOTO
		inserimento:
			printf("\nTYPE OF ITEM CURRENTLY PRESENT WITH THAT ID: %d\n SCOPE OF ITEM CURRENTLY PRESENT: %d\n TYPE OF ITEM TO INSERT: %d\n SCOPE OF ITEM TO INSERT: %d\n",s->type, s->scope,item_type,item_scope);
				if(s->scope==item_scope&&s->nscope==number_scope) {
					
					
					if(s->type==item_type)
					{
						//actual type is the same of the new one -> ACTION: I don't change the type and name
						printf("\nFOUND COMMON HASH IN TABLE...BUT SAME SCOPE AND TYPE. NO ACTIONS\n");
						s->type = item_type; //will not change anything
						s->scope = item_scope; //will not change anything
						s->nscope = number_scope;
						s->isarray = is_array;
						s->nparams = n_params;
						strcpy(s->name, name); //will not change anything
					}
					else {
						//ACTION: I should create a new element of different type (item_type) and scope (item_scope) and WITH A NEW ID
						struct sym_table_struct *n;
						
						int new_id = rand_int();
						printf("NEW GENERATED ID %d",new_id);
						HASH_FIND_INT(symbol_table, &new_id, n);
						
						while(n!=NULL) {
							
							new_id=rand_int();
							printf("\nREGEN ID %d \n",new_id);
							HASH_FIND_INT(symbol_table, &new_id, n);
						}
						
						n = (struct sym_table_struct*)malloc(sizeof *n);
						n->id = new_id;
						HASH_ADD_INT(symbol_table, id, n);
						n->type = item_type;
						n->scope = item_scope;
						n->nscope = number_scope;
						n->isarray = is_array;
						n->nparams = n_params;
						strcpy(n->name, name);
					
					}
					
				}
				else {
					
					
					//CHECK THAT THERE ARE NO ITEMS WITH THAT NAME IN THE SAME CONTEXT (IN WHICH I'M GOING TO INSERT: PARAMETER OF THE additem function)
					struct sym_table_struct *a;
					bool proceed = true;
					for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
						//printf("item id: %d --- name: %s --- type: %d  --- scope: %s - %d \n", s->id, s->name, s->type, sym_conv(s->scope), s->nscope); 
						if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope)
						{
							proceed=false;
							break;
						}
					
					}
					
					if(proceed) {
					
						//ACTION: I should create a new element of different scope and WITH A NEW ID (because of same name)
						struct sym_table_struct *n;
						
						int new_id = rand_int();
						printf("NEW GENERATED ID %d",new_id);
						HASH_FIND_INT(symbol_table, &new_id, n);
						
						while(n!=NULL) {
							
							new_id=rand_int();
							printf("\nREGEN ID %d \n",new_id);
							HASH_FIND_INT(symbol_table, &new_id, n);
						}
						
						n = (struct sym_table_struct*)malloc(sizeof *n);
						n->id = new_id;
						HASH_ADD_INT(symbol_table, id, n);
						n->type = item_type;
						n->scope = item_scope;
						n->nscope = number_scope;
						n->isarray = is_array;
						n->nparams = n_params;
						strcpy(n->name, name);
					}
					
				}
			
		}
	}
	
	
	printf("\n\n**************** UPDATED ITEMS IN SYMBOL TABLE **********************************\n");
	print_items();
	printf("************************************************************************************\n");
}


int check_if_var_is_array_in_other_context(int item_id,const char *name, int item_type, int item_scope, int number_scope)
{
	
	struct sym_table_struct *a;
	bool error = true;
	
	for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
		
		if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==1) {
			
			error=false;
			break;
		}
	
	}
	
	if(error) {
		//ERROR IS 0
		printf("\n%s is not an array in scope  %s-%d\n", name, sym_conv(item_scope),number_scope);	
		return 0; 
	
	} else {
		//OK IS 1
		printf("\n%s  IS AN ARRAY in scope %s-%d, no problem \n",name,sym_conv(item_scope),number_scope);
		return 1; 	
	}
	
}


void check_if_var_is_array(int item_id,const char *name, int item_type, int item_scope, int number_scope){

	printf("\n\nCHECKING VAR %s IF IS AN ARRAY\n\n",name);
	
	
	struct sym_table_struct *a;
		bool error = true;
		
		for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
			
			if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==1) {
				
				error=false;
				break;
			}
		
		}
		
		if(error) {
		char str[80];
  	
			if(item_type==1) {
				char *mes = "Variable %s is not an array in scope %s-%d";
				sprintf(str, mes, name, sym_conv(item_scope),number_scope);
			}
			
			
			//iterate over OPEN CONTEXTS and check if present in any of them: open means GLOBAL FOR SURE AND POSSIBLE CONTEXTS THAT CONTAIN THE ACTUAL ONE
			
			//....check_item_in_other_context(,,,,)
			// from smaller to bigger (GLOBAL)
			
			int checks_on_cntx[last_context/2];
			int index_cntx = 0;
			for(int i=last_context-1; i>0; i-=2) {
				checks_on_cntx[index_cntx]=check_if_var_is_array_in_other_context(item_id,name, item_type, open_contexts[i-1], open_contexts[i]);
				index_cntx++;
			}
			
			//str cat to increase info in str
			
			bool check_other_cntx = false;
			
			
			//true if there is one+ reference in AN OPEN CONTEXT!!
			for(int i=0; i<last_context/2; i++) {
				if(checks_on_cntx[i]==1) {
					check_other_cntx = true;
					break;
				}
			
			}
			
			
			if(!check_other_cntx) {
				strcat(str," and in higher contexts");
				yyerror(str);
				exit(0);
			}
			else{
				//do nothing, the variable is declared before IN HIGHER OPEN CONTEXT (NOT CLOSED!!!!)
				printf("\nThe variable is declared as array before IN HIGHER OPEN CONTEXT (NOT CLOSED!!!!)\n");
			}
			
			
		
		} else{
			if(item_type==1)
				printf("%s VARIABLE IS AN ARRAY, no problem \n",name);
		}
	


}


int check_n_params_match_in_other_context(int item_id,const char *name, int item_type, int item_scope, int number_scope, int index)
{
	
	struct sym_table_struct *a;
	bool error = true;
	
	for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
		
		if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==1&&(a->nparams > index && index>=0)&&item_type==1) {
			
			error=false;
			break;
		}
		else if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==0&&a->nparams==index&&item_type==2){
			error=false;
			break;
		}
	}
	
	if(error) {
		//ERROR IS 0
		if(item_type==1) {
			printf("Out of bounds on array variable %s on index %d in scope in scope  %s-%d\n", name, index, sym_conv(item_scope),number_scope);	
			return 0;
		}
		else if(item_type==2) {
			printf("Not matching number of parameters for function %s in scope in scope  %s-%d\n", name, sym_conv(item_scope),number_scope);	
			return 0;
		}
	
	} else {
		//OK IS 1
		printf("No out of bound on array variable/ correct matching number of params for  %s  in scope %s-%d, no problem \n",name,sym_conv(item_scope),number_scope);
		return 1; 	
	}
	
}


void check_n_params_match(int item_id,const char *name, int item_type, int item_scope, int number_scope, int index){
	
	struct sym_table_struct *a;
		bool error = true;
		
		for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
			
			if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==1&&(a->nparams > index && index>=0)&&item_type==1) {
				
				error=false;
				break;
			}
			else if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->isarray==0&&a->nparams==index&&item_type==2){
				error=false;
				break;
			}
		
		}
		
		if(error) {
		char str[80];
  	
			if(item_type==1) {
				char *mes = "Out of bounds on array variable %s on index %d in scope %s-%d";
				sprintf(str, mes, name, index, sym_conv(item_scope),number_scope);
			}
			else if(item_type==2) {
				char *mes = "Not matching number of parameters for function %s in scope %s-%d";
				sprintf(str, mes, name, sym_conv(item_scope),number_scope);
			}
			
			
			//iterate over OPEN CONTEXTS and check if present in any of them: open means GLOBAL FOR SURE AND POSSIBLE CONTEXTS THAT CONTAIN THE ACTUAL ONE
			
			//....check_item_in_other_context(,,,,)
			// from smaller to bigger (GLOBAL)
			
			int checks_on_cntx[last_context/2];
			int index_cntx = 0;
			for(int i=last_context-1; i>0; i-=2) {
				checks_on_cntx[index_cntx]=check_n_params_match_in_other_context(item_id,name, item_type, open_contexts[i-1], open_contexts[i],index);
				index_cntx++;
			}
			
			//str cat to increase info in str
			
			bool check_other_cntx = false;
			
			
			//true if there is one+ reference in AN OPEN CONTEXT!!
			for(int i=0; i<last_context/2; i++) {
				if(checks_on_cntx[i]==1) {
					check_other_cntx = true;
					break;
				}
			
			}
			
			
			if(!check_other_cntx) {
				strcat(str," and in higher contexts");
				yyerror(str);
				exit(0);
			}
			else{
				//do nothing, the variable is declared before IN HIGHER OPEN CONTEXT (NOT CLOSED!!!!)
				printf("\nThe variable declared as array/function is ok also in HIGHER OPEN CONTEXT (NOT CLOSED!!!!)\n");
			}	
		
		} else{
			if(item_type==1)
				printf("NO OUT OF BOUNDS DETECTED ON VARIABLE(array) %s WITH INDEX %d, no problem \n",name,index);
			else if(item_type==2)
				printf("MATCHING NUMBER OF PARAMS FOR FUNCTION CALL %s, no problem \n",name);
		}
	


}






int check_item_in_other_context(int item_id,const char *name, int item_type, int item_scope, int number_scope)
{
	
	struct sym_table_struct *a;
	bool error = true;
	
	for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
		
		if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->type==item_type) {
			
			error=false;
			break;
		}
	
	}
	
	if(error) {
		//ERROR IS 0
		printf(" %s undefined in scope  %s-%d\n", name, sym_conv(item_scope),number_scope);	
		return 0; 
	
	} else {
		//OK IS 1
		printf("%s  declared in scope %s-%d, no problem \n",name,sym_conv(item_scope),number_scope);
		return 1; 	
	}
	
}



void *check_item_in_context(int item_id, const char *name, int item_type, int item_scope, int number_scope)
{
	
	struct sym_table_struct *a;
	bool error = true;
	
	for (a = symbol_table; a != NULL; a = (struct sym_table_struct*)(a->hh.next)) {
		
		if(strcmp(a->name,name)==0&&a->scope==item_scope&&a->nscope==number_scope&&a->type==item_type) {
			
			error=false;
			break;
		}
	
	}
	
	if(error) {
	char str[80];
  
		if(item_type==1) {
			char *mes = "Undefined variable %s in scope %s-%d";
			sprintf(str, mes, name, sym_conv(item_scope),number_scope);
		}
		else if(item_type==2) {
			char *mes = "Undefined function %s in scope %s-%d";
			sprintf(str, mes, name, sym_conv(item_scope),number_scope);
		}
		
		
		//iterate over OPEN CONTEXTS and check if present in any of them: open means GLOBAL FOR SURE AND POSSIBLE CONTEXTS THAT CONTAIN THE ACTUAL ONE
		
		//....check_item_in_other_context(,,,,)
		// from smaller to bigger (GLOBAL)
		
		int checks_on_cntx[last_context/2];
		int index_cntx = 0;
		for(int i=last_context-1; i>0; i-=2) {
			checks_on_cntx[index_cntx]=check_item_in_other_context(item_id,name, item_type, open_contexts[i-1], open_contexts[i]);
			index_cntx++;
		}
		
		//str cat to increase info in str
		
		bool check_other_cntx = false;
		
		
		//true if there is one+ reference in AN OPEN CONTEXT!!
		for(int i=0; i<last_context/2; i++) {
			if(checks_on_cntx[i]==1) {
				check_other_cntx = true;
				break;
			}
		
		}
		
		
		if(!check_other_cntx) {
			strcat(str," and in higher contexts");
			yyerror(str);
			exit(0);
		}
		else{
			//do nothing, the variable is declared before IN HIGHER OPEN CONTEXT (NOT CLOSED!!!!)
			printf("\nThe variable is declared before IN HIGHER OPEN CONTEXT (NOT CLOSED!!!!)\n");
		}
		
		
	
	} else{
		if(item_type==1)
			printf("%s VARIABLE IS DECLARED, no problem \n",name);
		else if(item_type==2)
			printf("%s FUNCTION IS DECLARED, no problem \n",name);
	}
	
}


int hash (const char* word) {
    	unsigned int hash = 0;
    	for (int i = 0 ; word[i] != '\0' ; i++)
    	{
        	hash = 31*hash + word[i];
    	}
    	return hash % SIZE;
}

void check_all_items_in_context(int item_scope, int number_scope) {
	char *element = NULL;
	
		
	for(int i=0; i<last_var; i++) {
		
		printf("\n\nCHECKING THE ELEMENT FROM VAR LIST: %s\n\n",variables_to_check[i]);
		element=variables_to_check[i];
		check_item_in_context(hash(element),element,VAR,item_scope,number_scope);
		
	}
		
	last_var=0;

	for(int i=0; i<last_func; i++) {
	
		printf("\n\nCHECKING THE ELEMENT FROM FUNC LIST: (%s)\n\n",functions_to_check[i]);
		element=functions_to_check[i];
		check_item_in_context(hash(element),element,FUN,item_scope,number_scope);
			
	}
	
	last_func=0;
}


void check_all_items_var_in_context_cond_specific(int item_scope, int number_scope, int start_num_var, int num_var) {
	char *element = NULL;
	
		
	for(int i=start_num_var; i<num_var; i++) {
		
		printf("\n\nCHECKING THE ELEMENT FROM VAR LIST: %s\n\n",variables_to_check[i]);
		element=variables_to_check[i];
		check_item_in_context(hash(element),element,VAR,item_scope,number_scope);
			
		
	}
		
	

}

void check_all_items_funct_in_context_cond_specific(int item_scope, int number_scope, int start_num_func, int num_func) {

	char *element = NULL;
	for(int i=start_num_func; i<num_func; i++) {
		
		printf("\n\nCHECKING THE ELEMENT FROM FUNC LIST: (%s)\n\n",functions_to_check[i]);
		element=functions_to_check[i];
		check_item_in_context(hash(element),element,FUN,item_scope,number_scope);
			
	}
	
	

}


 




























