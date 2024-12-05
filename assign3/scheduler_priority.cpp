/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Erin Bailey(433.01), Zach Miller(433.02)
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
        proc_li.push_back(A);    //getting all the PCB's in the list and putting them into a deque because i want to be able to remove from the front.
        count++;
        times.push_back({0,0});  //at the end, times has the exact number of entries as there are pcb's in the list
    }

    std::sort(proc_li.begin(), proc_li.end()); // sort proc_li in ascending order by priority
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriority::print_results(){

    for(int i = 0; i < count; i++){ // note: times.at(i).at(0) is the i'th PCB's wait time, .at(1) is the i'th PCB's runtime
        int ttime = times.at(i).at(0) + times.at(i).at(1);
        int wtime = times.at(i).at(0);
        avg_turnaround += ttime;      //sums ttimes and wtimes in preparation for averaging
        avg_wait += wtime;

        std::cout << "T" << i + 1 << " turn-around time = " << ttime << ", waiting time = " << wtime << std::endl;
    }

    avg_turnaround = avg_turnaround / count;    // the averaging
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
        
        std::cout << "Running Process " << proc_li.front().name << " for " << proc_li.front().burst_time << " time units" << std::endl;
        times.at(proc_li.front().id).at(0) = elapsed_time;            //record the current time at which the process was removed as i'th processes wait time
        times.at(proc_li.front().id).at(1) = proc_li.front().burst_time;   //record the current processes burst time as the i'th processes runtime
        elapsed_time += proc_li.front().burst_time;                   //record the passage of time as though i'th process just completed running
        proc_li.pop_front();          // remove highest priority process from list
    }

}

/**
 * @brief overloads the < operator so that it works on PCB objects
 *        this causes proc_li to sort in ascending order when std::sort is called
 */
bool operator< (PCB A, PCB B){
    return A.priority > B.priority;
}
