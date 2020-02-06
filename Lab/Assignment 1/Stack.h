/****************************************************************
 File: Stack.h
 ----------------
 This is an interface for a stack ADT. The ADT supports routines 
 for stack creation, deletion, pushing (inserting), popping and 
 printing in an interpreted way.
 ****************************************************************/

#ifndef UTILS_STACK
#define UTILS_STACK

/****************************************************************
 Type: Stack
 --------------
 Declaration of a Stack object takes the form,

   Stack st;
 */
 typedef struct stack *Stack;


/****************************************************************
 Function: createStack()
 -----------------------
 Creates a new stack and returns it.

 Example usages:
   Stack q1;
   q1 = Stack();

   Stack q2 = createStack();
 */
 Stack createStack(void);


/****************************************************************
 Function: isEmpty(Stack)
 ---------------------------
 Returns true if the argument is an empty stack, false otherwise.

 Example usage, given the Stack variable st:

   if (!isEmpty(st))
     printf("This is not an empty stack.\n");
 */
 int isEmpty (Stack st);


/****************************************************************
 Function: deleteStack(stack)
 -------------------------------
 Destroys the stack given as an argument. Always call this after
 a Stack st is no longer needed, as:

    deleteStack(st);
 */
 void deleteStack(Stack st); 

/****************************************************************
 Function: push(stack, int)
 --------------------------------
 pushes the second argument to the stack. The data is put on the
 top of the stack.

 Example usage, given Stack variable st:

    push(st, 2);

 pushed the number 2 on top of the stack.
 */
 void push(Stack st, int data);

/****************************************************************
 Function: pop(Stack)
 ---------------------------
 Removes the item on the top of the stack and returns its value.

 Example usage, given Stack variable st and int variable data:

     data = pop(st);

 If 2 were at the top of the stack, data now contains the
 value 2.

 WARNING: pop will return 0 if an attempt is made to pop
 from the empty stack. It is the client's responsibility to
 determine if the stack is empty before calling pop.
 */
 int pop(Stack st);

/****************************************************************
 Function: printStack(Stack)
 ------------------------------
Prints the current stack, if not empty, each element is separated 
by a space

Example of usage, given Stack variable st:

	push(st, 1);
	push(st, 2);
	push(st, 3);
 	printStack(st);

 ---> "3 2 1"
 */
void printStack (Stack st);

#endif