/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.h
 * @author Zach Miller(433.02) and Erin Bailey(433.01) 
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
    deque<PCB> proc_li;  // deque to hold processes
    vector<vector<unsigned int>> times;  // vector to hold completion times
    unsigned int elapsed_time = 0;  // total scheduler time
    int count = 0;  // local variable count
    float avg_wait = 0, avg_turnaround = 0;  // average turn-around and wait times

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
