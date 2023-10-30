/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Julian Rangel & Nick F Andrew
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
//

#include "scheduler_rr.h"

// Constructor for the Round-Robin scheduler, sets the time quantum.
SchedulerRR::SchedulerRR(int time_quantum) {
    this->current_time = 0; // Initialize the current time to 0.
    this->quantum = time_quantum; // Set the time quantum for each process.
};

// Destructor for the Round-Robin scheduler, clears data structures.
SchedulerRR::~SchedulerRR(){
    processes.clear(); // Clear the list of processes.
    remainingBurst.clear(); // Clear the list of remaining burst times for processes.
    turnaroundTime.clear(); // Clear the list of turnaround times for processes.
};

// Initializes the scheduler with a list of processes.
void SchedulerRR::init(vector<PCB>& process_list){
    this->processes = process_list; // Set the list of processes.
    this->current_time = 0; // Initialize the current time to 0.

    // Initialize the remaining burst times and turnaround times for each process.
    for (size_t i = 0; i < processes.size(); i++) {
        remainingBurst.push_back(processes[i].burst_time); // Set remaining burst time.
        turnaroundTime.push_back(0); // Initialize turnaround time to 0.
    }
};

// Prints the results of the Round-Robin scheduling simulation.
void SchedulerRR::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    // Iterate through the processes and print their turnaround and waiting times.
    for(size_t i = 0; i < processes.size(); i++){
        cout << processes[i].name << " turn-around time = " << turnaroundTime[i] << ", waiting time = " << (turnaroundTime[i] - processes[i].arrival_time - processes[i].burst_time) << endl;
        total_turnaround_time += (turnaroundTime[i] - processes[i].arrival_time);
        total_waiting_time += (turnaroundTime[i] - processes[i].arrival_time - processes[i].burst_time);
    }

    // Calculate and print the average turnaround and waiting times.
    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
};

// Simulates the Round-Robin scheduling algorithm.
void SchedulerRR::simulate(){
    int timeRemaining = 0;
    int timePassed = 0;

    // Calculate the total remaining time across all processes.
    for (size_t i = 0; i < remainingBurst.size(); i ++){
        timeRemaining += remainingBurst[i];
    }

    // Continue the simulation until all processes have completed.
    while(timeRemaining > 0){
        for(size_t i = 0; i < processes.size(); i ++){
            if (remainingBurst[i] > quantum) {
                // Execute a process for the time quantum and update times.
                cout << "Running process " << processes[i].name << " for " << quantum << " time units" << endl;
                timePassed += quantum;
                remainingBurst[i] -= quantum;
                timeRemaining -= quantum;
            } else if (remainingBurst[i] <= quantum && remainingBurst[i] > 0) {
                // Execute a process for its remaining burst time and update times.
                cout << "Running process " << processes[i].name << " for " << remainingBurst[i] << " time units" << endl;
                timePassed += remainingBurst[i];
                turnaroundTime[i] = timePassed;
                timeRemaining -= remainingBurst[i];
                remainingBurst[i] = 0;
            } else {
                // The remaining time for the process is already 0.
            }
        }
    }
};
