/**
 * Assignment 1: priority queue of processes
 * @file test1.cpp
 * @author
 * @brief This file tests the correctness of your implementation of the readyqueue and pcbtable
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include <iostream>
#include "readyqueue.h"
#include "pcbtable.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "CS 433 Programming assignment 1" << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl;
    std::cout << "************Performing Test 1********************" << std::endl;
    std::cout << "=================================" << std::endl;

    ReadyQueue q1;
    PCBTable table;

    for (int i = 1; i <= 50; i++) {
        // Add a new PCB with id = i, priority = i to the table at index i
        table.addNewPCB(i, i, i);
    }

    std::cout << "Add process 15, 6, 23, 39 and 8 to q1. Display the content of q1" << std::endl;
    q1.addPCB(table.getPCB(15));
    q1.addPCB(table.getPCB(6));
    q1.addPCB(table.getPCB(23));
    q1.addPCB(table.getPCB(39));
    q1.addPCB(table.getPCB(8));
    q1.displayAll();

    std::cout << "remove the process with the highest priority from q1 and display q1." << std::endl;
    PCB* p = q1.removePCB();
    q1.displayAll();

    std::cout << "add processes 47, 1, 37 and 5 into q1 and display q1" << std::endl;
    q1.addPCB(table.getPCB(47));
    q1.addPCB(table.getPCB(1));
    q1.addPCB(table.getPCB(37));
    q1.addPCB(table.getPCB(5));
    q1.displayAll();
    std::cout << "remove the process with the highest priority from q1 and display q1." << std::endl;
    p = q1.removePCB();
    q1.displayAll();
    
    std::cout << "Insert processes 47, 17, 39, 12 and 19  to q1and display q1." << std::endl;
    q1.addPCB(table.getPCB(47));
    q1.addPCB(table.getPCB(17));
    q1.addPCB(table.getPCB(39));
    q1.addPCB(table.getPCB(12));
    q1.addPCB(table.getPCB(19));
    q1.displayAll();
    std::cout << "One by one remove the process with the highest priority from the queue q1" << std::endl;
    while(q1.size() > 0)
    {
        p = q1.removePCB();
        q1.displayAll();
    }
    return 0;
}



