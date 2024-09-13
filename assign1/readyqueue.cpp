#include "readyqueue.h"
#include <iostream>

using namespace std;

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient comments to your code.

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
  int largest = i;       // Initialize largest as root index
  int left = 2 * i + 1;  // Left child index
  int right = 2 * i + 2; // Right child index

  // Check if left child exists and is larger than root
  if (left < size() - 1 &&
      queue[left].getPriority() > queue[largest].getPriority()) {
    largest = left;
  }

  // Check if right child exists and is larger than root
  if (right < size() - 1 &&
      queue[right].getPriority() > queue[largest].getPriority()) {
    largest = right;
  }

  // Swap and continue heapifying if root is not largest
  if (largest != i) {
    swap(&queue[i], &queue[largest]); // Swap the parent and largest PCBs
    heapify(largest);                 // Heapify the largest PCB
  }
}

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
  pcbPtr->setState(ProcState::READY); // Set the state of the PCB to READY
  queue.push_back(*pcbPtr);           // Add PCB to back of queue
  int currentIdx = size() - 1;        // Get index of current PCB

  // Bubble up
  while (currentIdx > 0) {
    int parentIdx = (currentIdx - 1) / 2; // Get the index of the parent PCB

    // Get the current PCB and its parent PCB
    PCB &current = queue[currentIdx];
    PCB &parent = queue[parentIdx];

    // If the parent PCB has a lower priority than the current PCB...
    if (current.getPriority() > parent.getPriority()) {
      swap(&current, &parent); // Swap the parent and current PCBs
      currentIdx = parentIdx;  // Update the index of the current PCB
    } else {                   // Otherwise...
      break;                   // Exit the loop
    }
  }
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB *ReadyQueue::removePCB() {
  if (size() == 0) { // If the queue is empty...
    return nullptr;  // Return nullptr
  }

  swap(&queue[0], &queue[size() - 1]); // Swap the first and last PCBs
  PCB *largest = &queue[size() - 1];   // Get the PCB with the highest priority
  largest->setState(ProcState::RUNNING); // Set the state of the PCB to RUNNING
  queue.pop_back();                      // Remove the last PCB from the queue

  // Heapify the queue to maintain the max heap property
  if (!queue.empty()) { // If the queue is not empty...
    heapify(0);         // Heapify the queue
  }

  return largest; // Return the PCB with the highest priority
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
  for (PCB &pcb : queue) {
    pcb.display(); // Display the PCB
  }
}
