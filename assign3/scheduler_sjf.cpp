/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Zach Miller(433.02) and Erin Bailey(433.01)
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
//  Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <iostream>
#include <bits/stdc++.h>

/**
 * @brief SchedulerSJF constructor to initialize member functions
 */
SchedulerSJF::SchedulerSJF() {}

/**
 * @brief SchedulerSJF deconstructor
 */
SchedulerSJF::~SchedulerSJF() {}

/**
 * @brief Called once before simulation starts. This initializes the scheduler.
 * @param process_list List of processes in the simulation
 */
void SchedulerSJF::init(std::vector<PCB> &process_list)
{
    // iterate through process_list and populate proc_li deque and initialize times vector
    for (PCB A : process_list) {
        proc_li.push_back(A);
        count++;
        times.push_back({0, 0});
    }

    // sort proc_li by priority, using overloaded <  operator
    sort(proc_li.begin(), proc_li.end());
}

/**
 * @brief Called once after the simulation ends to print sim results
 */
void SchedulerSJF::print_results()
{
    // iterate for each process and calculate average wait and turnaround times
    for (int i = 0; i < count; i++) {
        int ttime = times.at(i).at(0) + times.at(i).at(1);
        int wtime = times.at(i).at(0);
        avg_turnaround += ttime;
        avg_wait += wtime;

        cout << "T" << i + 1 << " turn-around time = " << avg_turnaround << ", waiting time = " << wtime << endl;
    }

    avg_turnaround = avg_turnaround / count;
    avg_wait = avg_wait / count;
    cout << "Average turn-around time = " << "turn-around time = " << avg_turnaround << " Average waiting time = " << avg_wait << endl;
}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 * It stops when all processes are finished.
 */
void SchedulerSJF::simulate()
{
    while (!proc_li.empty()) {
     // while proc_li is not empty pop off and run each process
        curr_proc = &proc_li.front();

        cout << "Running Process " << curr_proc->name << " for " << curr_proc->burst_time << " time units " << endl;

        proc_li.pop_front();
        times.at(curr_proc->id).at(0) = elapsed_time;
        times.at(curr_proc->id).at(1) = curr_proc->burst_time;
        elapsed_time += curr_proc->burst_time;
    }
}

/**
 * @brief overloads < operator to work with PCB objects. This will be used for the sort function so that it sorts by burst time.
 * @param PCB objects A and B to be compared.
 */
bool operator<(PCB A, PCB B)
{
    return A.burst_time < B.burst_time;
}
