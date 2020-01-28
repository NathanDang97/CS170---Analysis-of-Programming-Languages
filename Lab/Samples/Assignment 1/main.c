/****************************************************************
 File: main.c
 ------------
 A main program to demonstrate the IntQueue ADT.
 It enqueues the numbers 0 through 99 and then dequeues
 them.
*/

#include <stdio.h>
#include <stdlib.h>
#include "IntQueue.h"

int main(void) 
{ 
	int i;
	int data;
	IntQueue queue = createQueue();

	for (i=0; i<100; i++) { 
		data = i;
		printf("Enqueuing %d\n", data);
		enqueue(queue, data);
	} 

	if (!isEmpty(queue))
	{
		while (!isEmpty(queue))
		{
			data = dequeue(queue);
			printf("Dequeued %d\n", data); 
		}
	}
	else
		printf("Queue is empty.\n");

	deleteQueue(queue);

	return 0;
}