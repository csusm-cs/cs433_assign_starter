/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Caden Jamason, Adrian Reyes
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be
 * scheduled to run. It should be a priority queue such that the process with
 * the highest priority can be selected next.
 * @version 0.1
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient comments to your code.

#pragma once

#include "pcb.h"
#include <vector>

/**
 * @brief A queue of PCBs that are in the `READY` state to be scheduled to run.
 *
 * It should be a priority queue such that the process with the highest priority
 * can be selected next.
 */
class ReadyQueue {
private:
  // Choose a data structure for the ReadyQueue. No STL class is allowed.

  // Data structure: max heap

  /**
   * @brief The vector of PCBs in the queue.
   */
  vector<PCB> queue;

  /**
   * @brief Swaps the elements at the given indices in the heap.
   * @param `PCB*`: the first PCB to swap
   * @param `PCB*`: the second PCB to swap
   */
  void swap(PCB *, PCB *);

  /**
   * @brief Trickles down the element at the given index in the heap.
   * @param `int`: the index of the element to heapify
   */
  void heapify(int = 0);

public:
  /**
   * @brief Constructor for the ReadyQueue class.
   */
  ReadyQueue();

  /**
   * @brief Destructor for the ReadyQueue class.
   */
  ~ReadyQueue();

  // You may add additional member functions, but don't change the definitions
  // of the following four member functions.

  /**
   * @brief Add a PCB representing a process into the ready queue.
   *
   * @param `pcbPtr`: the pointer to the PCB to be added
   */
  void addPCB(PCB *pcbPtr);

  /**
   * @brief Remove and return the PCB with the highest priority from the queue
   *
   * @return `PCB*` – the pointer to the PCB with the highest priority
   */
  PCB *removePCB();

  /**
   * @brief Returns the number of elements in the queue.
   *
   * @return `int` – the number of PCBs in the queue
   */
  int size();

  /**
   * @brief Display the PCBs in the queue.
   */
  void displayAll();
};
