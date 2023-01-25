#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT_ELEMENTS 100 //maximum limit of the stack
#define LIMIT_LENGTH_ELEMENT 1500 //maximum size of elements in stack (in order to avoid problems with dimensions)

char stack[LIMIT_ELEMENTS][LIMIT_LENGTH_ELEMENT]; //stack
int top; //index to current top element in the stack


char *itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str,"%d",num);
        return str;
}





void push(char *element)
{
	if(top == LIMIT_ELEMENTS- 1)
	{
		printf("Stack underflow in stack memory for values\n");
	}
	else
	{
		top++;
		stack[top][strlen(element) + 1];
		strcpy(stack[top], element);
		printf("Putting element %s in stack memory for values\n",element);
	}
}

char *pop()
{
	char *element = NULL;
	if(top == -1)
	{
		printf("Stack underflow in stack memory for values\n");
	}
	else
	{
		element=stack[top];
		printf("The extracted item from stack memory for values is %s\n",stack[top]);
		top--; // The element below the topmost element is deleted
		
	}
	
	return element;
}

void display()
{
	if(top == -1)
	{
		printf("Stack underflow in stack memory for values\n"); // Stack is empty
	}
	else if(top > 0)
	{
		printf("The elements of the stack memory for values are:\n");
		for(int i = top; i >= 0; i--) // top to bottom traversal
		{
			printf("%s\n",stack[i]);
		}
	}
}

