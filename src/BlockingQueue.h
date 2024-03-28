/*
 * BlockingQueue.h
 *
 * Module interface for a generic fixed-size Blocking Queue implementation.
 *
 */

#ifndef BLOCKING_QUEUE_H_
#define BLOCKING_QUEUE_H_

#include <stdbool.h>

#include "Queue.h"

typedef struct BlockingQueue BlockingQueue;

/* You should define your struct BlockingQueue here */
struct BlockingQueue {
};

/*
 * Creates a new BlockingQueue for at most max_size void* elements.
 * Returns a pointer to a new BlockingQueue on success and NULL on failure.
 */
BlockingQueue* new_BlockingQueue(int max_size);

/*
 * Enqueues the given void* element at the back of this Queue.
 * If the queue is full, the function will block the calling thread until there is space in the queue.
 * Returns false when element is NULL and true on success.
 */
bool BlockingQueue_enq(BlockingQueue* this, void* element);

/*
 * Dequeues an element from the front of this Queue.
 * If the queue is empty, the function will block until an element can be dequeued.
 * Returns the dequeued void* element.
 */
void* BlockingQueue_deq(BlockingQueue* this);

/*
 * Returns the number of elements currently in this Queue.
 */
int BlockingQueue_size(BlockingQueue* this);

/*
 * Returns true if this Queue is empty, false otherwise.
 */
bool BlockingQueue_isEmpty(BlockingQueue* this);

/*
 * Clears this Queue returning it to an empty state.
 */
void BlockingQueue_clear(BlockingQueue* this);

/*
 * Destroys this Queue by freeing the memory used by the Queue.
 */
void BlockingQueue_destroy(BlockingQueue* this);

#endif /* BLOCKING_QUEUE_H_ */
