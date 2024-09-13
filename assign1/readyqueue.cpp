#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue() : pQueue() {
     
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    //TODO: add your code to release dynamically allocate memory
    pQueue.clear();
}



/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    //TODO: add your code here
    // When adding a PCB to the queue, you must change its state to READY.
    pcbPtr->setState(ProcState::READY);     // changes state of pointer to READY
    //pQueue[pQueue.size()] = pcbPtr;     adds the PCB object pointer to rear of queue (size)
    pQueue.push_back(pcbPtr);   // add PCB to back of the queue 


    //  bubble up ---
    int currentLoc = pQueue.size() - 1;     // get index of newly added PCB
    while (currentLoc > 0) {
        int parentLoc = (currentLoc - 1) / 2;   // get the index of parent

        // Compare current PCB with its parent
        if (pQueue[parentLoc]->getPriority() < pQueue[currentLoc]->getPriority()) {
            // swap the parent and current PCB if parent has lower priority
            swap(pQueue[parentLoc], pQueue[currentLoc]);

            // Update the current location to the parent location
            currentLoc = parentLoc;
        } else {
            break;  // if parent has a higher or equal priority, then do nothing
        }
    }

}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
    if (pQueue.size() == 0) {
        return nullptr;
    }
    // store PCB with highest priority in var
    PCB* largest = pQueue[0];   // PCB object at index 0 will be the largest
    largest->setState(ProcState::RUNNING);     // sets state of largest PCB to RUNNING
    pQueue.pop_back();
    heapify();     
    return largest;     // return the PCB with the highest priority
    
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    //TODO: add your code here
    return pQueue.size();
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //TODO: add your code here
    for(PCB *ptr : pQueue) {
        ptr->display();
    }
}

void ReadyQueue::swap(PCB *a, PCB *b) {     // simple swap function that swaps PCB object pointers
    PCB *temp = a;
    a = b;
    b = temp;
}

void ReadyQueue::heapify(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    int size = pQueue.size();   // get size of pqueue

    if (left < size && pQueue[left]->getPriority() > pQueue[largest]->getPriority()) {
        largest = left;
    }

    if (right < size && pQueue[right]->getPriority() > pQueue[largest]->getPriority()) {
        largest = right;
    }

    if (largest != i) {
        swap(pQueue[i], pQueue[largest]);
        heapify(largest);
    }


}

// void ReadyQueue::heapify(int i)
// Get the left child, right child, and largest value (set to the parameter value for now) WITH their priorities

// If the left child has a higher priority than the parent...
// Update the largest index
// If the right child has a larger priority than the parent...
// Update the largest index
// If the largest index is not the parent...
// Swap the parent and largest PCBs
// Heapify the largest PCB

// /**
//  * @brief Returns the smaller child of a specified index in heap
//  */
// int ReadyQueue::getLargerChild(int i) {
//     int LC, RC; // locations of children
//     LC = 2 * i + 1; // sets LC and RC 
//     RC = 2 * i + 2;
//     int pQueueSize = pQueue.size();

//     // check if both children are in bounds
//     if (RC > pQueueSize - 1 && LC > pQueueSize - 1) {
//         return -1;
//     }

//     // Check if only the left child is in bounds
//     if (LC <= pQueueSize - 1 && RC > pQueueSize - 1) {
//         return LC;
//     }

//     // Check if only right child is in bounds
//     if (RC <= pQueueSize - 1 && LC > pQueueSize - 1) {
//         return RC;
//     }

//     // Both children are in bounds, return index of larger child
//     if (pQueue[RC]->getPriority() > pQueue[LC]->getPriority()) {
//         return RC;
//     } else {
//         return LC;
//     }
// }