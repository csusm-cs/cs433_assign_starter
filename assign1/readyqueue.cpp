#include "readyqueue.h"
#include <iostream>

using namespace std;

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient comments to your code.

/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue() : queue() {}

/**
 * @brief Destructor for the ReadyQueue class.
 */
ReadyQueue::~ReadyQueue() {}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
  // TODO: make sure this works
  pcbPtr->setState(ProcState::READY); // Set the state of the PCB to READY
  queue.push_back(*pcbPtr);           // Add PCB to back of queue
  int currentIdx = size() - 1;        // Get index of current PCB

  // Bubble up
  while (currentIdx > 0) {
    // Get the index of the parent PCB
    int parentIdx = (currentIdx - 1) / 2;

    // Get the current PCB and its parent PCB
    PCB &current = queue[currentIdx];
    PCB &parent = queue[parentIdx];

    // If the parent PCB has a lower priority than the current PCB...
    if (current.getPriority() > parent.getPriority()) {
      swap(&current, &parent); // Swap the parent and current PCBs
      currentIdx = parentIdx;  // Update the index of the current PCB
    } else {
      return; // Exit the loop
    }
  }
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB *ReadyQueue::removePCB() {
  // TODO: make sure this works
  if (size() == 0) {
    return nullptr; // Return nullptr if the queue is empty
  }

  PCB *pcb = &queue[0];              // Get the PCB with the highest priority
  pcb->setState(ProcState::RUNNING); // Set the state of the PCB to RUNNING

  // Remove the PCB with the highest priority
  swap(&queue[0], &queue[size() - 1]);
  queue.pop_back();

  // Heapify the queue
  heapify();

  return pcb; // Return the PCB with the highest priority
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() { return queue.size(); }

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
  // For each PCB in the queue, display its ID, priority, and state
  cout << "Display Processes in ReadyQueue:" << endl;
  for (PCB pcb : queue) {
    cout << "\t";
    pcb.display();
  }
}

// Helper functions
/**
 * @brief Swaps the elements at the given indices in the heap.
 *
 * @param a: the first PCB to swap
 * @param b: the second PCB to swap
 */
void ReadyQueue::swap(PCB *a, PCB *b) {
  PCB temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief Trickles down the element at the given index in the heap.
 *
 * @param i: the index of the element to heapify
 */
void ReadyQueue::heapify(int i) {
  int left = 2 * i + 1;                               // Left child index
  int leftPriority = queue[left].getPriority();       // Left child priority
  int right = 2 * i + 2;                              // Right child index
  int rightPriority = queue[right].getPriority();     // Right child priority
  int largest = i;                                    // Largest index
  int largestPriority = queue[largest].getPriority(); // Largest priority

  // If the left child has a higher priority than the parent...
  if (left < size() && leftPriority > largestPriority) {
    largest = left; // Update the largest index
  }

  // If the right child has a higher priority than the parent...
  if (right < size() && rightPriority > largestPriority) {
    largest = right; // Update the largest index
  }

  // If the largest index is not the parent...
  if (largest != i) {
    swap(&queue[i], &queue[largest]); // Swap the parent and largest PCBs
    heapify(largest);                 // Heapify the largest PCB
  }
}
