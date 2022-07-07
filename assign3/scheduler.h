/**
* Assignment 3: CPU Scheduler
 * @file scheduler.h
 * @author ??? (TODO: your name)
 * @brief This is the header file for the base Scheduler class. Specific schedulers, e.g. FCFS, SJF and RR, inherit
 *        this base class.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#pragma once

#include <vector>
#include "pcb.h"

using namespace std;
/**
 * @brief This is the base class for the scheduler.
 */
class Scheduler {
public:
    /**
     * @brief Construct a new Scheduler object
     */
    Scheduler() {}
    /**
     * @brief Destroy the Scheduler object
     */
    virtual ~Scheduler() {}
    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    virtual void init(std::vector<PCB>& process_list) = 0;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    virtual void print_results() = 0;


    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    virtual void simulate() = 0;
};