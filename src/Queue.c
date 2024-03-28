/*
 * Queue.c
 *
 * Fixed-size generic array-based Queue implementation.
 *
 */

#include <stddef.h>
#include <malloc.h>

#include "Queue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Queue module interface as documented in Queue.h.
 */


Queue *new_Queue(int max_size) {
    Queue* queue1 = malloc(sizeof(Queue));
    void *array1 = malloc(sizeof(int) * max_size);
    queue1->array=array1;
    queue1->maxSize = max_size;
    struct Queue *queue = queue1;
    return queue;
}

bool Queue_enq(Queue* this, void* element) {
    if (this->size == this->maxSize - 1) {
        return false;
    } else if (element == NULL) {
        return false;
    } else {
        this->array[this->size + 1] = element;
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
