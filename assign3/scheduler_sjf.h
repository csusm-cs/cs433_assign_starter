/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Zach Miller
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#ifndef ASSIGN3_SCHEDULER_SJF_H
#define ASSIGN3_SCHEDULER_SJF_H

#include "scheduler.h"
#include <deque>

class SchedulerSJF : public Scheduler {
private:
    deque<PCB> processes;  // deque to hold processes locally
    vector<double> completionTimes;  // vector to hold completion time for each process
    PCB *currentProc;  // local PCB 
    int currentTime;  // current time of scheduler
    int proc_count;  // processor counter
    unsigned int elapsed_time;
    double avgWT;  // avg wait time
    double avgTT;  // avg turnaround time

public:
    /**
     * @brief Construct a new SchedulerSJF object
     */
    SchedulerSJF();
    /**
     * @brief Destroy the SchedulerSJF object
     */
    ~SchedulerSJF() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

    friend bool operator< (PCB A, PCB B);
};
#endif //ASSIGN3_SCHEDULER_SJF_H
