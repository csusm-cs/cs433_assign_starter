/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author ??? (TODO: your name)
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>

using namespace std;

// global buffer object
Buffer buffer;

// Producer thread function
// TODO: Add your implementation of the producer thread here
void *producer(void *param) {
    // Each producer insert its own ID into the buffer
    // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
    buffer_item item = *((int *) param);

    while (true) {
        /* sleep for a random period of time */
        usleep(rand()%1000000);
        // TODO: Add synchronization code here
        if (buffer.insert_item(item)) {
            cout << "Producer " << item << ": Inserted item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Producer error condition"  << endl;    // shouldn't come here
        }
    }
}

// Consumer thread function
// TODO: Add your implementation of the consumer thread here
void *consumer(void *param) {
    buffer_item item;

    while (true) {
        /* sleep for a random period of time */
        usleep(rand() % 1000000);
        // TODO: Add synchronization code here
        if (buffer.remove_item(&item)) {
            cout << "Consumer " << item << ": Removed item " << item << endl;
            buffer.print_buffer();
        } else {
            cout << "Consumer error condition" << endl;    // shouldn't come here
        }
    }
}

int main(int argc, char *argv[]) {
    /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
    /* TODO: 2. Initialize buffer and synchronization primitives */
    /* TODO: 3. Create producer thread(s).
     * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    /* TODO: 4. Create consumer thread(s) */
    /* TODO: 5. Main thread sleep */
    /* TODO: 6. Exit */
}
