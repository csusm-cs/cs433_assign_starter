#include "readyqueue.h"
#include <iostream>

using namespace std;

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient comments to your code.

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue() : count(0) {
  // TODO: add your code here
  // Implement heap data structure for the ReadyQueue
}

/**
 * @brief Destructor for the ReadyQueue class.
 */
ReadyQueue::~ReadyQueue() {
  // TODO: add your code to release dynamically allocated memory
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
  // When adding a PCB to the queue, you must change its state to READY.
  // TODO: add your code here

}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB *ReadyQueue::removePCB() {
  // TODO: add your code here
  // When removing a PCB from the queue, you must change its state to RUNNING.
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
  // TODO: add your code here
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
  // TODO: add your code here
}
