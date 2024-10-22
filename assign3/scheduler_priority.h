/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.h
 * @author ??? (TODO: your name)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#ifndef ASSIGN3_SCHEDULER_PRIORITY_H
#define ASSIGN3_SCHEDULER_PRIORITY_H

#include "scheduler.h"

class SchedulerPriority : public Scheduler {
private:
    std::vector<PCB>* proc_li;
    std::vector<int> times; // vector.at(i) is ith wait time
    PCB* curr_proc;
    int elapsed_time = 0;

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

    friend bool operator< (PCB A, PCB B);

};


#endif //ASSIGN3_SCHEDULER_PRIORITY_H


/*
*   Good way to sort a vector of PCB's 
*   https://www.geeksforgeeks.org/how-to-sort-vector-of-custom-objects-in-cpp/
*       overload comparison operator for the PCB then the normal <= >= < > will work (whichever gets used)
*/
