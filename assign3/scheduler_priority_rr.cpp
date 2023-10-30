/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Julian Rangel & Nick F Andrew
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerPriorityRR constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    this->current_time = 0;
    this->quantum = time_quantum;
};

SchedulerPriorityRR::~SchedulerPriorityRR(){
    processes.clear();
    remainingBurst.clear();
    turnaroundTime.clear();
};

void SchedulerPriorityRR::init(vector<PCB>& process_list){
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
    for (size_t i = 0; i < processes.size(); i++) {
        remainingBurst.push_back(processes[i].burst_time);
        turnaroundTime.push_back(0);
    }
    
};

void SchedulerPriorityRR::print_results(){
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

void SchedulerPriorityRR::simulate(){
    int timeRemaining = 0;
    int timePassed = 0;
    int currentPrio = processes[0].priority;
    int nextPrio = 0;
    int didNothing = 0;
    for (size_t i = 0; i < remainingBurst.size(); i ++){
        timeRemaining += remainingBurst[i];
    }
    while(timeRemaining > 0){
        for(size_t i = 0; i < processes.size(); i ++){
            if (processes[i].priority == currentPrio) {
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
                    for (size_t i = 0; i < processes.size(); i++) {
                        if (processes[i].priority < currentPrio) {
                            nextPrio = processes[i].priority;
                            break;
                        }
                    }
                } else {
                    //remaning time for process is already 0
                    didNothing++;
                    if(didNothing > processes.size()){
                        currentPrio = nextPrio;
                        didNothing = 0;
                    }
                }
            } else {

            }
        }
    }
};