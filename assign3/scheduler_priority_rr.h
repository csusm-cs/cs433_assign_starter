/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.h
 * @author Erin Bailey(433.01), Zack Miller(433.02)
 * @brief This Scheduler class implements the Priority RoundRobin (PriorityRR) scheduling algorithm.
 * @version 9001
 */

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include <deque>
#include <algorithm>

class SchedulerPriorityRR : public Scheduler {
private:
    std::deque<PCB> proc_li;
    std::vector<vector<unsigned int>> times; // vector.at(i).at(0) is ith turnaround time, .at(1) is the ith run time
    PCB* curr_proc;
    int time_quantum = 0,
        count = 0;
    unsigned int elapsed_time = 0;
                 
    float avg_wait = 0,
          avg_turnaround = 0;

public:
    /**
     * @brief Construct a new SchedulerRR object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     */
    ~SchedulerPriorityRR() override;

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

    /**
     * @brief overload < operator so it works on PCB objects
     */
    friend bool operator< (PCB A, PCB B);
};


#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
