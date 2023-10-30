/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// Constructor for the SchedulerFCFS class.
SchedulerFCFS::SchedulerFCFS(){
    // Initializes the current_time variable to 0.
    this->current_time = 0;
};

// Destructor for the SchedulerFCFS class.
SchedulerFCFS::~SchedulerFCFS(){
    // Clears the processes vector, which contains process control blocks (PCBs).
    processes.clear();
};

// Initialization function for the scheduler.
void SchedulerFCFS::init(vector<PCB>& process_list){
    // Sets the processes vector to the provided process_list.
    this->processes = process_list;
    // Resets the current_time to 0.
    this->current_time = 0;
};

// Prints the results of the First-Come-First-Served (FCFS) scheduling simulation.
void SchedulerFCFS::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    // Loop through each process in the processes vector.
    for(PCB& process : processes){
        // Update the current time by adding the process's burst time.
        current_time += process.burst_time;
        // Print the process name, its turn-around time, and waiting time.
        cout << process.name << " turn-around time = " << current_time << ", waiting time = " << (current_time - process.arrival_time - process.burst_time) << endl;
        // Update the total turnaround time and waiting time.
        total_turnaround_time += (current_time - process.arrival_time);
        total_waiting_time += (current_time - process.arrival_time - process.burst_time);
    }

    // Calculate the average waiting time and average turn-around time.
    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    // Print the average values.
    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
};

// Simulates the FCFS scheduling by running each process in the order they appear in the processes vector.
void SchedulerFCFS::simulate(){
    for(const PCB& process : processes){
        // Print a message indicating the name of the process and the time it is running for.
        cout << "Running process " << process.name << " for " << process.burst_time << " time units" << endl;
    }
};
