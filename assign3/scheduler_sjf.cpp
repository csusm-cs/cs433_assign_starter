/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"
#include <algorithm>
#include <vector>
#include <iostream>


// Constructor for SchedulerSJF class.
SchedulerSJF::SchedulerSJF(){
    // Initialize the current time to 0.
    this->current_time = 0;
};

// Destructor for SchedulerSJF class.
SchedulerSJF:: ~SchedulerSJF(){
    // Clear the list of processes when an instance is destroyed.
    processes.clear();
};

// Initialize the scheduler with a list of processes.
void SchedulerSJF::init(std::vector<PCB>& process_list) {
    // Copy the provided process list into the scheduler's processes.
    this->processes = process_list;
    // Reset the current time to 0.
    this->current_time = 0;

    // Sort the processes in ascending order of burst time (Shortest Job First).
    for (int i = 0; i < processes.size() - 1; ++i) {
        for (int j = 0; j < processes.size() - i - 1; ++j) {
            // Compare the burst times of adjacent processes.
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap the positions of two processes if they are out of order.
                PCB temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
};
// Print the results of the scheduling algorithm, including turnaround and waiting times.
void SchedulerSJF::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    for(PCB& process : processes){
        // Update the current time with the process's burst time.
        current_time += process.burst_time;

        // Print the results for the current process.
        cout << process.name << " turn-around time = " << current_time << ", waiting time = " << (current_time - process.arrival_time - process.burst_time) << endl;

        // Update the total turnaround and waiting times.
        total_turnaround_time += (current_time - process.arrival_time);
        total_waiting_time += (current_time - process.arrival_time - process.burst_time);
    }

    // Calculate and print the average turnaround and waiting times.
    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
};

// Simulate the execution of processes.
void SchedulerSJF::simulate(){
    for(const PCB& process : processes){
        // Print a message indicating the execution of each process.
        cout << "Running process " << process.name << " for " << process.burst_time << " time units" << endl;
    }
};
