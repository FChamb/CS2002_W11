/*
 * BlockingQueue.c
 *
 * Fixed-size generic array-based BlockingQueue implementation.
 *
 */

#include <stddef.h>

#include "BlockingQueue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the BlockingQueue module interface as documented in BlockingQueue.h.
 */


BlockingQueue *new_BlockingQueue(int max_size) {
    return NULL;
}

bool BlockingQueue_enq(BlockingQueue* this, void* element) {
    return false;
}

void* BlockingQueue_deq(BlockingQueue* this) {
    return NULL;
}

int BlockingQueue_size(BlockingQueue* this) {
    return -1;
}

bool BlockingQueue_isEmpty(BlockingQueue* this) {
    return false;
}

void BlockingQueue_clear(BlockingQueue* this) {
}

void BlockingQueue_destroy(BlockingQueue* this) {
}
