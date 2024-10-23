/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author Erin Bailey(433.01), Zach Miller(433.02)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 42(did you bring your towel?)
 */


#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"
#include <algorithm>
#include <deque>

class SchedulerPriority : public Scheduler {
private:
    std::deque<PCB> proc_li;
    std::vector<vector<unsigned int>> times; // vector.at(i).at(0) is ith wait time
    PCB* curr_proc;
    unsigned int elapsed_time = 0;
    int count = 0;
    float avg_wait = 0,
          avg_turnaround = 0;

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriority();

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriority() override;

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


#endif //ASSIGN3_SCHEDULER_PRIORITY_H
