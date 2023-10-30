/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

// Constructor for the SchedulerPriority class
SchedulerPriority::SchedulerPriority(){
    this->current_time = 0; // Initialize the current_time to 0
};

// Destructor for the SchedulerPriority class
SchedulerPriority::~SchedulerPriority(){
    processes.clear(); // Clear the processes vector when the object is destroyed
};

// Initialize the Scheduler with a list of processes
void SchedulerPriority::init(vector<PCB>& process_list){
    this->processes = process_list; // Copy the provided process_list into the processes vector
    this->current_time = 0; // Reset the current_time to 0

    // Sort the processes based on their priority in descending order
    for (size_t i = 0; i < processes.size() - 1; ++i) {
        for (size_t j = 0; j < processes.size() - i - 1; ++j) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap processes if they are out of order based on priority
                PCB temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
};

// Print the results of the scheduling simulation
void SchedulerPriority::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    // Process each PCB and calculate turnaround time and waiting time
    for(PCB& process : processes){
        current_time += process.burst_time;
        cout << process.name << " turn-around time = " << current_time << ", waiting time = " << (current_time - process.arrival_time - process.burst_time) << endl;
        total_turnaround_time += (current_time - process.arrival_time);
        total_waiting_time += (current_time - process.arrival_time - process.burst_time);
    }

    // Calculate and print the average turnaround time and average waiting time
    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
};

// Simulate the execution of processes
void SchedulerPriority::simulate(){
    for(const PCB& process : processes){
        cout << "Running process " << process.name << " for " << process.burst_time << " time units" << endl;
    }
};
