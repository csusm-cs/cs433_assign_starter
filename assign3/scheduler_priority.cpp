/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Erin Bailey(433.01), Zach Miller(433.?)
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */


#include "scheduler_priority.h"

/**
 * @brief Construct a new SchedulerPriority object
 */
SchedulerPriority::SchedulerPriority(){}

/**
 * @brief Destroy the SchedulerPriority object
 */
SchedulerPriority::~SchedulerPriority(){}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriority::init(std::vector<PCB>& process_list){
    for(PCB A: process_list){
        proc_li.push_back(A);
        count++;
        times.push_back({0,0});
    }

    std::sort(proc_li.begin(), proc_li.end()); // sort proc_li in ascending order by priority
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriority::print_results(){

    for(int i = 0; i < count; i++){
        int ttime = times.at(i).at(0) + times.at(i).at(1);
        int wtime = times.at(i).at(0);
        avg_turnaround += ttime;
        avg_wait += wtime;

        std::cout << "T" << i + 1 << " turn-around time = " << ttime << ", waiting time = " << wtime << std::endl;
    }

    avg_turnaround = avg_turnaround / count;
    avg_wait = avg_wait / count;
    std::cout << "Average turn-around time = " << avg_turnaround << ", Average waiting time = " << avg_wait << std::endl;

}

/**
 * @brief This function simulates the scheduling of processes in the ready queue.
 *        It stops when all processes are finished.
 */
void SchedulerPriority::simulate(){
    // at this point, proc_li was initialized, atd sorted into descending order
    
    while(proc_li.size() > 0){
        curr_proc = &proc_li.front(); // curr_proc holds the highest priority process
        
        std::cout << "Running Process " << curr_proc->name << " for " << curr_proc->burst_time << " time units" << std::endl;
        
        proc_li.pop_front();          // remove highest priority process from list
        times.at(curr_proc->id).at(0) = elapsed_time;
        times.at(curr_proc->id).at(1) = curr_proc->burst_time;
        elapsed_time += curr_proc->burst_time;
    }

}

/**
 * @brief overloads the < operator so that it works on PCB objects
 *        this causes proc_li to sort in ascending order
 */
bool operator< (PCB A, PCB B){
    return A.priority > B.priority;
}
