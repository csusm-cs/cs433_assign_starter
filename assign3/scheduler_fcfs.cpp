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

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerFCFS::SchedulerFCFS(){
    this->current_time = 0;
};

SchedulerFCFS::~SchedulerFCFS(){
    processes.clear();
};

void SchedulerFCFS::init(vector<PCB>& process_list){
  this->processes = process_list;
  this->current_time = 0;
   
};

void SchedulerFCFS::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for(PCB& process : processes){
        current_time += process.burst_time;
        //T1 turn-around time = 20, waiting time = 0
        cout << process.name << " turn-around time = " << current_time << ", waiting time = " << (current_time - process.arrival_time - process.burst_time) << endl;
        total_turnaround_time += (current_time - process.arrival_time);
        total_waiting_time += (current_time - process.arrival_time - process.burst_time);
    }

    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;

};

void SchedulerFCFS::simulate(){
    for(const PCB& process : processes){
        
        cout << "Running process " << process.name << " for " << process.burst_time << " time units" << endl;
        
    }
};

