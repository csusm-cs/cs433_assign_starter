/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Zach Miller
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <iostream>

// TODO: add implementation of SchedulerSJF constructor, destrcutor and 
// member functions init, print_results, and simulate here

/**
 * Algorithm:
 * - Sort all processes according to arrival time
 * - Then select the process that has the minimum CPU burst
 * - After completion, make a pool of processes that arrives afterward
 * till the completion of the previous procecss and select that process
 * among the pool which is having minimum CPU burst.
*/


/**
 * @brief SchedulerSJF constructor to initialize member functions
 */
SchedulerSJF::SchedulerSJF() {
    // member variables initialized here
}

/**
 * @brief SchedulerSJF deconstructor
 */
SchedulerSJF::~SchedulerSJF() {

}

/**
 * @brief Called once before simulation starts
 * @param process_list List of processes in the simulation
 */
void SchedulerSJF::init(std::vector<PCB>& process_list) {
   for (int i = 0; i < process_list.size(); i++) {  // iterate through process_list
     PCB process = process_list[i];  // create new process object and save from process_list
        process.print();  // prints each process using print() function
   }
}

/**
 * @brief Called once after the simulation ends to print sim results
 */
void SchedulerSJF::print_results() {
    // print results
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 * It stops when all processes are finished.
 */
void SchedulerSJF::simulate() {
    // run simulation (somehow)
}
