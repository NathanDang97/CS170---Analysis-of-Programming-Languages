/****************************************************************
 File: Stack.c
 ----------------
 This file implements the Stack interface given in Stack.h.
 ****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"


/****************************************************************
 The stack is implemented as a linked list of nodes, each
 containing an int stack entry and a pointer to the next node.
*/
struct node { 
	int data;
	struct node *next; 
};
typedef struct node Node;

/****************************************************************
 The state of the stack is encapsulated in this struct, which
 contains a pointer to the top of the stack. The Stack ADT is 
 a pointer to a struct of this type.
*/
struct stack {
	Node *top;
};

/*****************************************************************/
Stack createStack() 
{ 

	Stack stack = (Stack) malloc(sizeof(struct stack));
	
	if (stack == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	stack->top = NULL;
	
	return stack;
} 

/*****************************************************************/
int isEmpty (Stack stack)
{
	return stack->top == NULL;
}

/****************************************************************
 Implementation note: Each pop both removes the element from
 the stack and deallocates the node. The last call to free()
 deallocates the stack struct.
*/
void deleteStack(Stack stack) 
{ 

	do { 
		pop(stack);
	} while (!isEmpty(stack));
	
	free(stack);
} 

/****************************************************************
 Implementation note: This is a private function for creating
 an stack node pointer with given data contents. It's only
 here to make push() a little easier to read.
*/
static Node *createNode(int data) 
{ 
	Node *node = (Node *) malloc(sizeof(Node));
	
	if (node == NULL) { 
		printf("Out of memory!\n");
		exit(1);
	} 
	
	node->data = data;
	node->next = NULL;

	return node;
} 

/*****************************************************************/
void push(Stack stack, int data) 
{ 
	Node *newNode = createNode(data);
	
	newNode->data = data;
	newNode->next = stack->top;
	stack->top = newNode;
}

/*****************************************************************/
int pop(Stack stack) 
{ 
	Node *temp;
	int data;

	if (isEmpty(stack)) { 
		// Stack is empty
		return 0;
	} 
	else { 
		temp = stack->top;
		stack->top = stack->top->next;
		temp->next = NULL;
		data = temp->data;
		free(temp);
		return data;
	}
} 

/*****************************************************************/
void printStack (Stack stack)
{
	Node *current;

	if (isEmpty(stack)) {
		printf("Attempt to print empty stack failed.\n");
		return;
	}

	current = stack->top;

	printf("%d  ", current->data);
	while (current->next != NULL) {
		current = current->next;
		printf("%d  ", current->data);
	}
	printf("\n");
}