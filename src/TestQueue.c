/*
 * TestQueue.c
 *
 * Very simple unit test file for Queue functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>

#include "myassert.h"
#include "Queue.h"


#define DEFAULT_MAX_QUEUE_SIZE 20

/*
 * The queue to use during tests
 */
static Queue *queue;

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
    queue = new_Queue(DEFAULT_MAX_QUEUE_SIZE);
    total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
    Queue_destroy(queue);
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
 * Checks that the Queue constructor returns a non-NULL pointer.
 */
int newQueueIsNotNull() {
    assert(queue != NULL);
    return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty queue is 0.
 */
int newQueueSizeZero() {
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}

/*
 * Checks that enqueue adds only one value.
 */
int enqOneElement() {
    Queue_enq(queue, (void *) 1);
    assert(Queue_size(queue) == 1);
    return TEST_SUCCESS;
}

/*
 * Checks that enqueue and dequeue only add and remove the correct value and that size is valid.
 */
int enqAndDeqOneElement() {
    Queue_enq(queue, (void *) 1);
    assert(Queue_size(queue) == 1);
    assert(Queue_deq(queue) == (void *) 1);
    assert(Queue_size(queue) == 0);
    return TEST_SUCCESS;
}


/*
 * Write more of your own test functions below (such as enqOneElement, enqAndDeqOneElement, ...)
 * to help you verify correctness of your Queue
 */

/*
 * Main function for the Queue tests which will run each user-defined test in turn.
 */

int main() {
    runTest(newQueueIsNotNull);
    runTest(newQueueSizeZero);
    runTest(enqOneElement);
    runTest(enqAndDeqOneElement);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(enqOneElement);
     * runTest(enqAndDeqOneElement);
     *
     */

    printf("Queue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
