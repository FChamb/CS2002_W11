/*
 * BlockingQueue.c
 *
 * Fixed-size generic array-based BlockingQueue implementation.
 *
 */

#include <stddef.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#include "BlockingQueue.h"

/*
 * The functions below all return default values and don't work.
 * You will need to provide a correct implementation of the BlockingQueue module interface as documented in BlockingQueue.h.
 */


BlockingQueue *new_BlockingQueue(int max_size) {
    BlockingQueue* queue = (BlockingQueue*) malloc(sizeof(BlockingQueue));
    if (queue == NULL) {
        free(queue);
        return NULL;
    }

    queue->array = (void**) malloc(sizeof(void*) * max_size);
    if (queue->array == NULL) {
        free(queue->array);
        return NULL;
    }

    queue->maxSize = max_size;
    queue->size = 0;
    pthread_mutex_init(&(queue->mutex), NULL);
    sem_init(&(queue->full), 0, 0);
    sem_init(&(queue->empty), 0, max_size);

    return queue;
}

bool BlockingQueue_enq(BlockingQueue* this, void* element) {
    if (element == NULL) {
        return false;
    }

    sem_wait(&(this->full));
    pthread_mutex_lock(&(this->mutex));

    if (this->size < this->maxSize) {
        this->array[this->size] = element;
        this->size++;
    }

    pthread_mutex_unlock(&(this->mutex));
    sem_post(&(this->empty));

    return true;
}

void* BlockingQueue_deq(BlockingQueue* this) {
    void* data = NULL;
    sem_wait(&(this->empty));
    pthread_mutex_lock(&(this->mutex));

    if (this->size != 0) {
        data = this->array[0];
        for (int i = 1; i < this->size; i++) {
            this->array[i - 1] = this->array[i];
        }
        this->size--;
    }

    pthread_mutex_unlock(&(this->mutex));
    sem_post(&(this->full));

    return data;
}

int BlockingQueue_size(BlockingQueue* this) {
    pthread_mutex_lock(&(this->mutex));
    int size = this->size;
    pthread_mutex_unlock(&(this->mutex));
    return size;
}

bool BlockingQueue_isEmpty(BlockingQueue* this) {
    pthread_mutex_lock(&(this->mutex));
    bool empty = (this->size == 0);
    pthread_mutex_unlock(&(this->mutex));
    return empty;
}

void BlockingQueue_clear(BlockingQueue* this) {
    pthread_mutex_lock(&(this->mutex));
    this->size = 0;
    pthread_mutex_unlock(&(this->mutex));
}

void BlockingQueue_destroy(BlockingQueue* this) {
    free(this->array);
    pthread_mutex_destroy(&(this->mutex));
    sem_destroy(&(this->full));
    sem_destroy(&(this->empty));
    free(this);
}
