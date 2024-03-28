/*
 * TestBlockingQueue.c
 *
 * Very simple unit test file for BlockingQueue functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>

#include "BlockingQueue.h"
#include "myassert.h"


#define DEFAULT_MAX_QUEUE_SIZE 20

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
 * Write more of your own test functions below (such as enqOneElement, enqAndDeqOneElement, ...)
 * to help you verify correctness of your BlockingQueue.
 */


/*
 * Main function for the BlockingQueue tests which will run each user-defined test in turn.
 */

int main() {
    runTest(newQueueIsNotNull);
    runTest(newQueueSizeZero);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(enqOneElement);
     * runTest(enqAndDeqOneElement);
     *
     */

    printf("\nBlockingQueue Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
