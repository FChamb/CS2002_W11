# CS2002 Week 11 Practical - Queues and Thread Safety #
### Introduction: ###
This project directory consists of a complete and specification accurate implementation of both Queue.c and BlockingQueue.c as well as Test classes for both of the queues. The code for both Queue.c and BlockingQueue.c follow the requirements provided in the corresponding header files. The test files test all aspects of both queues and all pass.

### Instruction: ###
1. Open the terminal and cd into src of project directory
    ```console
    cd path/to/directory/CS2002_W11/src
    ```
2. Run the make clean command
    ```console
    make clean
    ```
3. Run the make command
    ```console
    make all
    ```
4. Run Test Queue
    ```console
    ./TestQueue
    ```
    or Test Blocking Queue
    ```console
    ./TestBlockingQueue
    ```
    or stacscheck
    ```console
    stacscheck /cs/studres/CS2002/Coursework/W11-SP/Tests
    ```
5. To show no memory leakage run
    ```console
    valgrind --leak-check=full ./TestQueue
    ```
   or
    ```console
    valgrind --leak-check=full ./TestBlockingQueue
    ```