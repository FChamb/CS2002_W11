/*
 * Queue.c
 *
 * Fixed-size generic array-based Queue implementation.
 *
 */

#include <stddef.h>
#include <stdlib.h>

#include "Queue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Queue module interface as documented in Queue.h.
 */


Queue *new_Queue(int max_size) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }

    queue->array = malloc(sizeof(void*) * max_size);
    if (queue->array == NULL) {
        return NULL;
    }

    queue->maxSize = max_size;
    queue->size = 0;

    return queue;
}

bool Queue_enq(Queue* this, void* element) {
    if (this->size == this->maxSize - 1) {
        return false;
    } else if (element == NULL) {
        return false;
    } else {
        this->array[this->size] = element;
        this->size++;
    }
    return true;
}

void* Queue_deq(Queue* this) {
    void* data;
    if (this->size == 0) {
        data = NULL;
    } else {
        data = this->array[0];
        for (int i = 1; i < this->size; i++) {
            this->array[i - 1] = this->array[i];
        }
        this->size--;
    }
    return data;
}

int Queue_size(Queue* this) {
    return this->size;
}

bool Queue_isEmpty(Queue* this) {
    return this->size == 0;
}

void Queue_clear(Queue* this) {
    this->size = 0;
}

void Queue_destroy(Queue* this) {
    free(this->array);
    free(this);
}
