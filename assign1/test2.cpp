/**
 * Assignment 1: priority queue of processes
 * @file test1.cpp
 * @author
 * @brief This file tests the correctness of your implementation of the readyqueue and pcbtable
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */
#include <chrono>
#include <iostream>
#include <random>
#include "readyqueue.h"
#include "pcbtable.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "CS 433 Programming assignment 1" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
    std::cout << "************Performing Test 2********************" << std::endl;
    std::cout << "=================================" << std::endl;

    // random seed. 
    srand(1);
    int size = 200;

    ReadyQueue q2;    // Ready Queue
    PCBTable table(size);  // PCBTable of given size

    // Create initial 200 PCBs with random priorities, add them to the PCB table
    // Randomly choose to add half of the processes into the ready queue
    for (int i = 0; i < size; i++) {
        int priority = rand() % 50 + 1;
        PCB *pcbPtr = new PCB(i + 1, priority);
        table.addPCB(pcbPtr, i);
        if (rand() % 2 == 0) q2.addPCB(pcbPtr);
    }
    cout << "ReadyQueue size = " << q2.size() << endl;
    //q2.display();
    auto t1 = std::chrono::high_resolution_clock::now();
    int idx = 0;
    for (int i = 0; i < 1000000; i++) {
        int x = rand();
        if (x % 2 == 0) {
            // Remove a proc from ReadyQueue
            if (q2.size() > 0) {
                q2.removePCB();
            }
        } else {
            // Add a PCB into ReadyQueue
            idx = rand() % size;
            if (table.getPCB(idx)->getState() !=
                ProcState::READY) { // if the PCB is not in READY state, add it into ReadyQueue
                int priority = rand() % 50 + 1;  
                table.getPCB(idx)->setPriority(priority);  // change its priority to a random value
                q2.addPCB(table.getPCB(idx));
            }
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> runtime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Time taken: " << runtime.count() << " seconds" << std::endl;
    cout << "ReadyQueue size = " << q2.size() << endl;
    q2.displayAll();
    return 0;
}
