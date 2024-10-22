/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Zach Miller
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

using namespace std;


/**
 * Implementation:
 * 1. Input processes along with their burst time
 * 2. Find waiting time for all processes
 * 3. First process does not need to wait so its waiting time is 0.
 * 4. Find waiting time for all other processes via wt[i] = bt[i - 1] + wt[i - 1].
 * 5. Find turnaround time via waiting_time + burst_time.
 * 6. Find avg waiting time = total_waiting_time / no_of_processes
 * 7. Find avg turnaround time = total_turnaround_time / no_of_processes.
 */

double waitingTime;  // waiting time for a process
double burstTime;  // burst time of a process
double arrTime;  // arrival time
double avgWT;  // average waiting time
double avgTT;  // average turnaround time 
                       


/**
 * @brief SchedulerFCFS constructor to initialize member functions
 */
SchedulerFCFS::SchedulerFCFS() {
    waitingTime = 0;
    burstTime = 0;
    arrTime = 0;
    avgWT = 0;
    avgTT = 0;
 
    
}

/**
 * @brief SchedulerFCFS deconstructor
 */
SchedulerFCFS::~SchedulerFCFS(){};

/**
 * @brief This function is called once before the sim starts, it is used to initialize the scheduler
 */
void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    // for (int i = 0; i < process_list.size(); i++) {  // iterates through passed process list
    //     process_list[i] = this->process_list[i];  // adds information from passed process list into local vector
    // }
}

/**
 * @brief This function is called once after the sim ends, it is used to print out the results of the sim
 */
void SchedulerFCFS::print_results() {
    // for(int i = 0; i < process_list.size(); i++) {  // iterate through filled local vector
    //     process_list[i].print();  // use print PCB function to print process data
    // }
}

/**
 * @brief This function sims the scheduling of processes in the ready queue, it stops when all processes are finished.
*/
void SchedulerFCFS::simulate() {

}

