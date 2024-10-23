/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Zach Miller
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <iostream>
#include <bits/stdc++.h>

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
SchedulerSJF::SchedulerSJF()
{
   // currentTime = 0;
}

/**
 * @brief SchedulerSJF deconstructor
 */
SchedulerSJF::~SchedulerSJF()
{
}

/**
 * @brief Called once before simulation starts. This initializes the scheduler.
 * @param process_list List of processes in the simulation
 */
void SchedulerSJF::init(std::vector<PCB> &process_list)
{
    for (PCB A : process_list) {
        processes.push_back(A);
        proc_count ++;
        completionTimes.push_back(0); 
    }
    cout << "processes size: " << processes.size() << endl;

    sort(processes.begin(), processes.end());  // sort processes list in ascending order by priority
    proc_count = processes.size();
    cout << "processes size after sorting: " << proc_count << endl;


    int testCount = 0;
    for (PCB A :processes) {
        testCount++;
    }
    cout << "There are " << testCount << " processes in processes vector." << endl;

}

/**
 * @brief Called once after the simulation ends to print sim results
 */
void SchedulerSJF::print_results()
{
    deque<PCB> localProc = processes;
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    int count = 0;

    avgTT = 0;
    avgWT = 0;

    cout << "Original process count: " << processes.size() << endl;


    for (int i = 0; i < processes.size(); i++) {  // iterate through proceses vector
        double turnaroundTime = completionTimes[processes[i].id] - processes[i].arrival_time;
        double waitTime = turnaroundTime - processes[i].burst_time;

        avgTT += turnaroundTime;
        avgWT += waitTime;
        count ++;

        cout << processes[i].name << " turn-around time = " << turnaroundTime << ", waiting time = " << waitTime << std::endl;
       
    }
    cout << "proc_count: " << count << endl;
    avgTT = avgTT /  count;
    avgWT = avgWT / count;
    cout << "Average turn-around time = " << avgTT << ", Average waiting time = " << avgWT << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 * It stops when all processes are finished.
 */
void SchedulerSJF::simulate()
{
    int procPriority = 0;  // local variable to store priority of process
    deque<PCB> localProc = processes;

    for (size_t i = 0; i < processes.size(); i++) {
        if (currentTime < processes[i].arrival_time) {
            currentTime = processes[i].arrival_time;
        }

    while (localProc.size() > 0) {
        currentProc = &localProc.front();  // currentProc holds first object in sorted processes list

        cout << "Running Process " << currentProc->name << " for " << currentProc->burst_time << " time units" << std::endl;
        localProc.pop_front();
    }
        

    }
}

/**
 * @brief overloads < operator to work with PCB objects
 */
bool operator< (PCB A, PCB B) {
    return A.burst_time < B.burst_time;
}