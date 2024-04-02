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
#define NUM_THREADS 5
#define NUM_OPERATIONS 100

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
 * Checks that enqueue adds only one value.
 */
int enqOneElement() {
    BlockingQueue_enq(queue, (void*) 1);
    assert(BlockingQueue_size(queue) == 1);
    return TEST_SUCCESS;
}

/*
 * Checks that enqueue and dequeue only add and remove the correct value and that size is valid.
 */
int enqAndDeqOneElement() {
    BlockingQueue_enq(queue, (void *) 1);
    assert(BlockingQueue_size(queue) == 1);

    assert(BlockingQueue_deq(queue) == (void *) 1);
    assert(BlockingQueue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Check that enqueue adds two elements, dequeue removes and item and enqueue adds one more.
 */
int enqTwoAndDeqAndEnq() {
    BlockingQueue_enq(queue, (void *) 1);
    BlockingQueue_enq(queue, (void *) 2);
    assert(BlockingQueue_size(queue) == 2);

    assert(BlockingQueue_deq(queue) == (void *) 1);
    BlockingQueue_enq(queue, (void *) 3);
    assert(BlockingQueue_size(queue) == 2);

    assert(BlockingQueue_deq(queue) == (void *) 2);
    assert(BlockingQueue_deq(queue) == (void *) 3);
    return TEST_SUCCESS;
}

/*
 * Checks that NULL is returned when dequeue is called on empty queue.
 */
int deqAll() {
    assert(BlockingQueue_deq(queue) == NULL);
    return TEST_SUCCESS;
}

/*
 * Checks that blocking waits for space in the queue before adding additional elements.
 */
int enqAll() {
    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        assert(BlockingQueue_enq(queue, (void *) &i) == true);
    }

    BlockingQueue_enq(queue, (void *) 2);

    for (int i = 1; i <= DEFAULT_MAX_QUEUE_SIZE; i++) {
        BlockingQueue_deq(queue);
    }

    assert(BlockingQueue_size(queue) == 1);
    assert(BlockingQueue_deq(queue) == (void *) 2);
    return TEST_SUCCESS;
}

/*
 * Helper function for what the threads should do in concurrentThreadMultiple.
 */
void *threadFunction(void *arg) {
    queue = (BlockingQueue *) arg;
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        assert(BlockingQueue_enq(queue, (void *) (intptr_t) i));
        usleep(1000);
        assert((intptr_t) BlockingQueue_deq(queue) == i);
    }
    pthread_exit(NULL);
}

/*
 * Checks that blocking functionality enables multi threading interaction.
 */
int concurrentThreadMultiple() {
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunction, (void *) queue) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    assert(BlockingQueue_isEmpty(queue));

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
    runTest(enqOneElement);
    runTest(enqAndDeqOneElement);
    runTest(enqTwoAndDeqAndEnq);
    //runTest(deqAll);
    //runTest(enqAll);
    //runTest(concurrentThreadMultiple);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(enqOneElement);
     * runTest(enqAndDeqOneElement);
     *
     */

    printf("\nBlockingQueue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
