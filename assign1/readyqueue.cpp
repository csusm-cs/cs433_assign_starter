#include <iostream>
#include "readyqueue.h"
#include "pcbtable.h"
#include "pcb.h"

using namespace std;

/**
 * @brief Constructor for the ReadyQueue class. has a count of current number of values
 * 
 */
ReadyQueue::ReadyQueue()  {
    capacity = 500;                     
    heaparray = new PCB*[capacity];     //creates a new heaparray and sets its size to our capacity
    count = 0;
 }

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] heaparray;                 //standard array destructor
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    if (count == capacity) {
        std::cout << "Queue is full" << endl;       //If queue is full, rejects input
        return;
    }
    pcbPtr->setState(ProcState::READY);             //sets our given PCB state to READY
    heaparray[count] = pcbPtr;                      //adds new PCB to the bottom of our heaparray
    count++;                                        //increments our heaparray's count
    if (count > 1) {
        percolateUp(count - 1);                     //if needed due to multiple values in array, calls the percolateUp function
    }
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    if(capacity == 0){
        std::cout << "ReadyQueue is empty " << std::endl;       //if our array is empty, rejects request
        return nullptr;
    }
    PCB* retval = heaparray[0];                                 //creates a temp retval to hold top of array
    heaparray[0]->setState(ProcState::RUNNING);                 //sets our top value state ro RUNNING
    count--;                                                    //decrement out array count
    heaparray[0] = heaparray[count];                            //sets the top of our array to be eqaul to bottommost value
    percolateDown(0);                                           //calls the percolateDown function to heapify our stack
    return retval;                                              //Returns our requested value
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return count;                                               //returns the total number of PCBs in our stack
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < count; i++){
        heaparray[i]->display();                                //iterates through the heaparray and calls display() for each PCB
    }
}

void ReadyQueue::percolateDown(int index) {
    int greater = index;
    if (leftChild(index) < count && rightChild(index) < count) {
        if (heaparray[leftChild(index)]->priority > heaparray[rightChild(index)]->priority) {
            greater = leftChild(index);                                                         //Compares each of the children nodes to
        } else {                                                                                //our given parent node. Prioritizes the
            greater = rightChild(index);                                                        //largest of the two children
        }
    } else if (leftChild(index) < count) {
        greater = leftChild(index);
    }
    if (greater != index) {
        PCB* temp = heaparray[index];                                                           //If a larger child has been found, then
        heaparray[index] = heaparray[greater];                                                  //we proceed to swap the positions of the
        heaparray[greater] = temp;                                                              //given child and the parent. After which,
        percolateDown(greater);                                                                 //We call the percolateDown again
    }
}

void ReadyQueue::swap(int index1, int index2) {
    std::swap(heaparray[index1],heaparray[index2]);                                             //Custom swap function for percolateUp
}

void ReadyQueue::percolateUp(int index) {
    while(heaparray[index]->priority > heaparray[parent(index)]->priority){                     //If the parent is found to be smaller 
        swap(index,parent(index));                                                              //than the child node, we swap the two
        index = parent(index);
    }
}

ReadyQueue::ReadyQueue(const ReadyQueue& heap) {
    capacity = heap.capacity;                                                                   //Standard copy function for our heaparray
    for (int i = 0; i < heap.count; i++)                                                        //takes an array and sets our current array
    {                                                                                           //to it
        heaparray[i] = heap.heaparray[i];
    }
    count = heap.count;
}

/**
  * @brief assignment operator to set one heap to another
  * @param the heap that you want to set your heap to
  */
ReadyQueue& ReadyQueue::operator = (const ReadyQueue& heap)
{
    if (this != &heap)
    {
        capacity = heap.capacity;                                                               //allows the calling of the copy construct
        for (int i = 0; i < heap.count; i++)                                                    // with an = sign. sets one array equal to
        {                                                                                       //the other
            heaparray[i] = heap.heaparray[i];
        }
        count = heap.count;
    }
    return *this;
}
