/****************************************************************
 File: IntQueue.h
 ----------------
 This is an interface for a queue of integer ADT. The ADT
 supports routines for queue creation, deletion, enqueueing,
 dequeueing and printing.
 ****************************************************************/

#ifndef UTILS_INTQUEUE
#define UTILS_INTQUEUE

/****************************************************************
 Type: IntQueue
 --------------
 Declaration of an IntQueue object takes the form,

   IntQueue q;
 */
 typedef struct intqueue *IntQueue;


/****************************************************************
 Function: createQueue()
 -----------------------
 Creates a new queue and returns it.

 Example usages:
   IntQueue q1;
   q1 = createQueue();

   IntQueue q2 = createQueue();
 */
 IntQueue createQueue(void);


/****************************************************************
 Function: isEmpty(IntQueue)
 ---------------------------
 Returns true if the argument is the empty queue, false otherwise.

 Example usage, given the IntQueue variable q:

   if (!isEmpty(q))
     printf("This is not an empty queue.\n");
 */
 int isEmpty (IntQueue queue);


/****************************************************************
 Function: deleteQueue(IntQueue)
 -------------------------------
 Destroys the queue given as argument. Always call this after
 an IntQueue q is no longer needed, as:

    deleteQueue(q);
 */
 void deleteQueue(IntQueue queue); 

/****************************************************************
 Function: enqueue(IntQueue, int)
 --------------------------------
 enqueues the second argument in the first. The int is put at the
 rear of the queue.

 Example usage, given IntQueue variable q:

    enqueue(q, 2);

 enqueues the number 2 at the rear of the queue q.
 */
 void enqueue(IntQueue queue, int data);

/****************************************************************
 Function: dequeue(IntQueue)
 ---------------------------
 Removes the item at the front of the queue and returns its value.

 Example usage, given IntQueue variable q and int variable front:

     front = dequeue(q);

 If 2 were at the front of the queue, front now contains the
 value 2.

 WARNING: dequeue will return 0 if an attempt is made to dequeue
 from the empty queue. It is the client's responsibility to
 determine if the queue is empty before calling dequeue.
 */
 int dequeue(IntQueue queue);

/****************************************************************
 Function: printQueue(IntQueue)
 ------------------------------
 Prints the contents of the queue at the console, starting with
 the front and going to the rear. There is a space between each
 number, and all appear on one line.
 */
void printQueue (IntQueue queue);

#endif