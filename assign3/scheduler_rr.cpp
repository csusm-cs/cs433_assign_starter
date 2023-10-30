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

// TODO: add implementation of SchedulerRR constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerRR::SchedulerRR(int time_quantum){
    this->current_time = 0;
    this->quantum = time_quantum;
};

SchedulerRR::~SchedulerRR(){
    processes.clear();
    remainingBurst.clear();
    turnaroundTime.clear();
};

void SchedulerRR::init(vector<PCB>& process_list){
    this->processes = process_list;
    this->current_time = 0;
    
    for (size_t i = 0; i < processes.size(); i++) {
        remainingBurst.push_back(processes[i].burst_time);
        turnaroundTime.push_back(0);
    }
    
};

void SchedulerRR::print_results(){
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    for(size_t i = 0; i < processes.size(); i++){
        cout << processes[i].name << " turn-around time = " << turnaroundTime[i] << ", waiting time = " << (turnaroundTime[i] - processes[i].arrival_time - processes[i].burst_time) << endl;
        total_turnaround_time += (turnaroundTime[i] - processes[i].arrival_time);
        total_waiting_time += (turnaroundTime[i] - processes[i].arrival_time - processes[i].burst_time);
    }

    double avg_waiting_time = total_waiting_time / processes.size();
    double avg_turnaround_time = total_turnaround_time / processes.size();

    cout << "Average turn-around time = " << avg_turnaround_time << ", Average waiting time = " << avg_waiting_time << endl;
    

};

void SchedulerRR::simulate(){
    int timeRemaining = 0;
    int timePassed = 0;
    for (size_t i = 0; i < remainingBurst.size(); i ++){
        timeRemaining += remainingBurst[i];
    }
    while(timeRemaining > 0){
        for(size_t i = 0; i < processes.size(); i ++){
            if (remainingBurst[i] > quantum) {
                cout << "Running process " << processes[i].name << " for " << quantum << " time units" << endl;
                timePassed += quantum;
                remainingBurst[i] -= quantum;
                timeRemaining -= quantum;
            } else if (remainingBurst[i] <= quantum && remainingBurst[i] > 0) {
                cout << "Running process " << processes[i].name << " for " << remainingBurst[i] << " time units" << endl;
                timePassed += remainingBurst[i];
                turnaroundTime[i] = timePassed;
                timeRemaining -= remainingBurst[i];
                remainingBurst[i] = 0;
            } else {
                //remaning time for process is already 0
            }
        }
    }
};