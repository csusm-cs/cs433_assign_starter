/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Nick F. Andrew & Julian Rangel
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:
    // TODO: add your private member variables here
    // choose a data structure for the ReadyQueue. No STL class is allowed.
    PCB** heaparray;
    int capacity;
    int count; 

public:
    
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    /**
     * @brief Destructor
     */
    ~ReadyQueue();

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief assignment operator to set one heap to another
     * @param the heap that you want to set your heap to
     */
    ReadyQueue& operator = (const ReadyQueue& heap);

    /**
     * @brief Copy constructor to build a heap from another heap
     * @param the heap to be copied
     */
    ReadyQueue(const ReadyQueue &heap);

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

    /**
     * @brief Heapify the list by comparing values from top to bottom
     * 
    */
    void percolateDown(int index);

    /**
     * @brief Swap the positions of two PCB's in queue based on priority
    */
    void swap(int index1, int index2);

    /**
     * @brief Heapify the lsit by comparing values from bottom to top
    */
    void percolateUp(int index);

    /**
     * @brief Returns the right child of the node at index
     * @return int: the priority of the PCB
     */
    int rightChild(int index)
    {
        return (2 * index) + 2;
    };
    /**
     * @brief Returns the left child of the node at index
     * @return int: the priority of the PCB
     */
    int leftChild(int index)
    {
        return (2 * index) + 1;
    }
    /**
     * @brief Returns the index of the parent of the child located at index
     * @return int: the priority of the PCB
     */
    int parent(int index)
    {
        if (index <= 0 || index >= count)
            return -1;
        return (index - 1) / 2;
    }

};
