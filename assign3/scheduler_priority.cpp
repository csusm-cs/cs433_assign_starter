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

// TODO: add implementation of SchedulerPriority constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerPriority::SchedulerPriority(){
    this->current_time = 0;
};

SchedulerPriority::~SchedulerPriority(){
    processes.clear();
};

void SchedulerPriority::init(vector<PCB>& process_list){
    this->processes = process_list;
    this->current_time = 0;
    

    for (size_t i = 0; i < processes.size() - 1; ++i) {
        for (size_t j = 0; j < processes.size() - i - 1; ++j) {
            if (processes[j].priority < processes[j + 1].priority) {
                PCB temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
};

void SchedulerPriority::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for(PCB& process : processes){
        current_time += process.burst_time;
        cout << process.name << " turn-around time = " << current_time << ", waiting time = " << (current_time - process.arrival_time - process.burst_time) << endl;
        total_turnaround_time += (current_time - process.arrival_time);
        total_waiting_time += (current_time - process.arrival_time - process.burst_time);
    }

    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;

};

void SchedulerPriority::simulate(){
    for(const PCB& process : processes){
        
        cout << "Running process " << process.name << " for " << process.burst_time << " time units" << endl;
        
    }
};