/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Erin Bailey(433.01), Zack Miller(433.?)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_RR_H
#define ASSIGN3_SCHEDULER_RR_H

#include "scheduler.h"
#include <deque>

class SchedulerRR : public Scheduler {
private:
    std::deque<PCB> proc_li;
    std::vector<vector<unsigned int>> times; // vector.at(i).at(0) is ith wait time, .at(1) is the ith turnaround time
    PCB* curr_proc;
    int time_quantum = 0;
    unsigned int elapsed_time = 0,
                 count = 0;
    float avg_wait = 0,
          avg_turnaround = 0;

public:
    /**
     * @brief Construct a new SchedulerRR object
     */
    SchedulerRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerRR object
     */
    ~SchedulerRR() override;

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
};


#endif //ASSIGN3_SCHEDULER_RR_H
