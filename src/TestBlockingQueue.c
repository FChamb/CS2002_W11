/*
 * TestBlockingQueue.c
 *
 * Very simple unit test file for BlockingQueue functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>

#include "BlockingQueue.h"
#include "myassert.h"


#define DEFAULT_MAX_QUEUE_SIZE 20
#define NUM_THREADS 2

/*
 * The queue to use during tests
 */
static BlockingQueue *queue;

/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test
 */
void setup(){
    queue = new_BlockingQueue(DEFAULT_MAX_QUEUE_SIZE);
    total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
    BlockingQueue_destroy(queue);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
    setup();

    if (testFunction()) success_count++;

    teardown();
}


/*
 * Two sample user-defined tests included below.
 * You will have to write many more tests.
 *
 * Each test function should return TEST_SUCCESS at the end.
 * Test functions can contain more than one assertion.
 *
 * If any assertion fails, the function name and line number
 * will be printed and the test will return a failure value.
 *
 * You will have to call runTest on your test functions in main below.
 */


/*
 * Checks that the BlockingQueue constructor returns a non-NULL pointer.
 */
int newQueueIsNotNull() {
    assert(queue != NULL);

    return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty blocking queue is 0.
 */
int newQueueSizeZero() {
    assert(BlockingQueue_size(queue) == 0);

    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqOneElement. Makes use of thread.
 */
void *enqOneElement(void *arg) {
    queue = (BlockingQueue *) arg;
    int* element = malloc(sizeof(int));
    *element = 1;
    assert(BlockingQueue_enq(queue, element) == true);
    free(element);

    return (void *) TEST_SUCCESS;
}

/*
 * Checks that enqueue adds only one value.
 */
int testEnqOneElement() {
    pthread_t thread;
    pthread_create(&thread, NULL, enqOneElement, (void *) queue);
    pthread_join(thread, NULL);
    assert(BlockingQueue_size(queue) == 1);
    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqNullElement. Makes use of thread.
 */
void *enqNullElement(void *arg) {
    queue = (BlockingQueue *) arg;
    assert(BlockingQueue_enq(queue, NULL) == false);

    return (void *) TEST_SUCCESS;
}

/*
 * Checks that enqueueing a NULL element returns false.
 */
int testEnqNullElement() {
    pthread_t thread;
    pthread_create(&thread, NULL, enqNullElement, (void *) queue);
    pthread_join(thread, NULL);
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqAndDeqOneElement. Makes use of thread.
 */
void *enqAndDeqOneElement(void *arg) {
    queue = (BlockingQueue *) arg;
    int* element = malloc(sizeof(int));
    *element = 1;
    BlockingQueue_enq(queue, &element);
    assert(BlockingQueue_size(queue) == 1);

    assert(BlockingQueue_deq(queue) == &element);
    free(element);

    return (void *) TEST_SUCCESS;
}

/*
 * Checks that enqueue and dequeue only add and remove the correct value and that size is valid.
 */
int testEnqAndDeqOneElement() {
    pthread_t thread;
    pthread_create(&thread, NULL, enqAndDeqOneElement, (void *) queue);
    pthread_join(thread, NULL);
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqTwoAndDeqAndEnq. Makes use of thread.
 */
void *enqTwoAndDeqAndEnq(void *arg) {
    queue = (BlockingQueue *) arg;
    int* element = malloc(sizeof(int));
    *element = 1;
    int* element2 = malloc(sizeof(int));
    *element2 = 2;
    int* element3 = malloc(sizeof(int));
    *element3 = 1;
    BlockingQueue_enq(queue, &element);
    BlockingQueue_enq(queue, &element2);
    assert(BlockingQueue_size(queue) == 2);

    assert(BlockingQueue_deq(queue) == &element);
    free(element);
    BlockingQueue_enq(queue, &element3);
    assert(BlockingQueue_size(queue) == 2);

    assert(BlockingQueue_deq(queue) == &element2);
    assert(BlockingQueue_deq(queue) == &element3);
    free(element2);
    free(element3);

    return (void *) TEST_SUCCESS;
}

/*
 * Check that enqueue adds two elements, dequeue removes and item and enqueue adds one more.
 */
int testEnqTwoAndDeqAndEnq() {
    pthread_t thread;
    pthread_create(&thread, NULL, enqTwoAndDeqAndEnq, (void *) queue);
    pthread_join(thread, NULL);
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqAlldeqAll. Makes use of thread.
 */
void *enqAlldeqAll(void *arg) {
    queue = (BlockingQueue *) arg;
    void **array[DEFAULT_MAX_QUEUE_SIZE];
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = malloc(sizeof(int));
        *element = i;
        array[i - 1] = (void *) element;
        assert(BlockingQueue_enq(queue, (void *) element) == true);
    }
    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);

    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        void* element = array[i - 1];
        assert(BlockingQueue_deq(queue) == element);
        free(element);
    }

    return (void *) TEST_SUCCESS;
}

/*
 * Checks that adding several elements to a queue also dequeues the correct results.
 */
int testEnqAlldeqAll() {
    pthread_t thread;
    pthread_create(&thread, NULL, enqAlldeqAll, (void *) queue);
    pthread_join(thread, NULL);
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Helper function for testDeqBlocking. Makes use of thread.
 */
void *deqBlocking(void *arg) {
    queue = (BlockingQueue *) arg;
    BlockingQueue_deq(queue);
    return (void *) TEST_SUCCESS;
}

/*
 * Checks that blocking waits for element to be added before removing additional elements.
 */
int testDeqBlocking() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, deqBlocking, (void *) queue);
    assert(result == 0);

    int* element = malloc(sizeof(int));
    *element = 1;
    BlockingQueue_enq(queue, &element);
    usleep(100);

    result = pthread_join(thread, NULL);
    assert(result == 0);
    assert(BlockingQueue_isEmpty(queue) == true);
    free(element);

    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqBlocking. Makes use of thread.
 */
void *enqBlocking(void *arg) {
    queue = (BlockingQueue *) arg;
    int* element = malloc(sizeof(int));
    *element = 1;
    BlockingQueue_enq(queue, &element);
    free(element);
    return (void *) TEST_SUCCESS;
}

/*
 * Checks that blocking waits for element to be removed before adding additional elements.
 */
int testEnqBlocking() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = malloc(sizeof(int));
        *element = i;
        assert(BlockingQueue_enq(queue, (void *) element) == true);
        free(element);
    }

    pthread_t thread;
    int result = pthread_create(&thread, NULL, enqBlocking, (void *) queue);
    assert(result == 0);

    BlockingQueue_deq(queue);
    usleep(100);

    result = pthread_join(thread, NULL);
    assert(result == 0);
    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);

    return TEST_SUCCESS;
}

/*
 * Helper function for testEnqAll. Makes use of thread.
 */
void *enqAll(void *arg) {
    queue = (BlockingQueue *) arg;
    int* element = malloc(sizeof(int));
    *element = 1;
    BlockingQueue_enq(queue, &element);
    free(element);
    return (void *) TEST_SUCCESS;
}

/*
 * Checks that blocking waits when queue is full.
 */
int testEnqAll() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = malloc(sizeof(int));
        *element = i;
        assert(BlockingQueue_enq(queue, (void *) element) == true);
        free(element);
    }

    pthread_t thread;
    int result = pthread_create(&thread, NULL, enqAll, (void *) queue);
    assert(result == 0);

    result = pthread_join(thread, NULL);
    assert(result == 0);
    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);

    return TEST_SUCCESS;
}

/*
 * Helper function for testDeqBlocking. Makes use of thread.
 */
void *deqAll(void *arg) {
    queue = (BlockingQueue *) arg;
    BlockingQueue_deq(queue);
    return (void *) TEST_SUCCESS;
}

/*
 * Checks that blocking waits for element to be added before removing additional elements.
 */
int testDeqAll() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = malloc(sizeof(int));
        *element = i;
        assert(BlockingQueue_enq(queue, (void *) element) == true);
        free(element);
    }
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        BlockingQueue_deq(queue);
    }

    pthread_t thread;
    int result = pthread_create(&thread, NULL, deqAll, (void *) queue);
    assert(result == 0);

    result = pthread_join(thread, NULL);
    assert(result == 0);
    assert(BlockingQueue_size(queue) == 0);

    return TEST_SUCCESS;
}

/*
 * Checks that return result of Queue_isEmpty is correct.
 */
int queueEmpty() {
    assert(BlockingQueue_isEmpty(queue) == true);

    return TEST_SUCCESS;
}

/*
 * Checks that queue is cleared when Queue_clear is called.
 */
int queueClear() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(BlockingQueue_enq(queue, (void *) &i) == true);
    }
    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);

    BlockingQueue_clear(queue);
    assert(BlockingQueue_size(queue) == 0);

    return TEST_SUCCESS;
}

/*
 * Checks that clearing an empty queue provides an empty queue.
 */
int queueClearEmpty() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(BlockingQueue_enq(queue, (void *) &i) == true);
    }
    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);

    BlockingQueue_clear(queue);
    assert(BlockingQueue_size(queue) == 0);

    BlockingQueue_clear(queue);
    assert(BlockingQueue_size(queue) == 0);

    return TEST_SUCCESS;
}

/*
 * Helper function for what the threads should do in concurrentThreadMultiple.
 * Add values to the queue.
 */
void *threadEnqFunction(void *arg) {
    queue = (BlockingQueue *) arg;
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = malloc(sizeof(int));
        *element = i;
        assert(BlockingQueue_enq(queue, element));
    }
    pthread_exit(NULL);
}

/*
 * Helper function for what the threads should do in concurrentThreadMultiple.
 * Remove values from the queue.
 */
void *threadDeqFunction(void *arg) {
    queue = (BlockingQueue *) arg;
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        int* element = (int*) BlockingQueue_deq(queue);
        if (element != NULL) {
            free(element);
        }
    }
    pthread_exit(NULL);
}

/*
 * Checks that blocking functionality enables multi threading interaction for enqueue.
 */
int concurrentThreadMultipleEnq() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, threadEnqFunction, (void *) queue);
            usleep(1000);
        } else {
            pthread_create(&threads[i], NULL, threadDeqFunction, (void *) queue);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    assert(BlockingQueue_size(queue) == 0);
    assert(BlockingQueue_isEmpty(queue) == true);

    return TEST_SUCCESS;
}

/*
 * Checks that blocking functionality enables multi threading interaction for dequeue.
 */
int concurrentThreadMultipleDeq() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i % 2 == 0) {
            pthread_create(&threads[i], NULL, threadDeqFunction, (void *) queue);
            usleep(1000);
        } else {
            pthread_create(&threads[i], NULL, threadEnqFunction, (void *) queue);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    assert(BlockingQueue_size(queue) == DEFAULT_MAX_QUEUE_SIZE);
    assert(BlockingQueue_isEmpty(queue) == false);

    return TEST_SUCCESS;
}

/*
 * Write more of your own test functions below (such as enqOneElement, enqAndDeqOneElement, ...)
 * to help you verify correctness of your BlockingQueue.
 */


/*
 * Main function for the BlockingQueue tests which will run each user-defined test in turn.
 */

int main() {
    runTest(newQueueIsNotNull);
    runTest(newQueueSizeZero);
    runTest(testEnqOneElement);
    runTest(testEnqNullElement);
    runTest(testEnqAndDeqOneElement);
    runTest(testEnqTwoAndDeqAndEnq);
    runTest(testEnqAlldeqAll);
    runTest(testDeqBlocking);
    runTest(testEnqBlocking);
    runTest(testEnqAll);
    runTest(testDeqAll);
    runTest(queueEmpty);
    runTest(queueClear);
    runTest(queueClearEmpty);
    runTest(concurrentThreadMultipleEnq);
    runTest(concurrentThreadMultipleDeq);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(enqOneElement);
     * runTest(enqAndDeqOneElement);
     *
     */

    printf("\nBlockingQueue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
