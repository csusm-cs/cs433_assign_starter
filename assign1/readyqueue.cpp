#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class. has a count of current number of values
 * 
 */
ReadyQueue::ReadyQueue()  {
    PCB* heaparray = new PCB[50];
    count = 0;
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] heaparray;
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    // When adding a PCB to the queue, you must change its state to READY.
    heaparray[count] = *pcbPtr;
    count++;
    pcbPtr->setState(ProcState::READY);
    percolateUp(count-1);

}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    //TODO: add your code here
    // When removing a PCB from the queue, you must change its state to RUNNING.
    PCB* retval = new PCB;
    //check if heap is empty, if not, then proceed

    heaparray[0].setState(ProcState::RUNNING);
    *retval = heaparray[0];
    heaparray[0] = heaparray[count-1];
    heaparray[count-1].~PCB();
    count--;
    percolateDown(0);

    return retval;

}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    //TODO: add your code here
    cout << "Did we even get here?";
    for (int i = 0; i < count - 1; i++){
        heaparray[i].display();
    }
}

void ReadyQueue::percolateDown(int index) {
    // Run recursively until the current node is bigger than its children
    while(heaparray[index].getPriority() < heaparray[leftChild(index)].getPriority() || heaparray[index].getPriority() < heaparray[rightChild(index)].getPriority()){
        if(heaparray[leftChild(index)].getPriority() > heaparray[rightChild(index)].getPriority()){
            swap(index,leftChild(index));
            index = leftChild(index);
        } else {
            swap(index,rightChild(index));
            index = rightChild(index);
        }
    }
}

void ReadyQueue::swap(int index1, int index2) {
    PCB temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

void ReadyQueue::percolateUp( int index) {
    // run recursively until the current node is small than its parent
    while(heaparray[index].getPriority() > heaparray[parent(index)].getPriority()){
        swap(index,parent(index));
        index = parent(index);
    }
}

