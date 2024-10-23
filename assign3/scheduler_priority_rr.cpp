/**
* Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Erin Bailey(433.01) and Zach Miller(433.02)
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority_rr.h"

/**
 * @brief Construct a new SchedulerPriorityRR object
 */
SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum){
    this->time_quantum = time_quantum;
}

/**
 * @brief Destroy the SchedulerPriorityRR object
 */
SchedulerPriorityRR::~SchedulerPriorityRR() {}

/**
 * @brief This function is called once before the simulation starts.
 *        It is used to initialize the scheduler.
 * @param process_list The list of processes in the simulation.
 */
void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    for(PCB A: process_list){
        proc_li.push_back(A);
        count++;
        times.push_back({0,0});
    }

    std::sort(proc_li.begin(), proc_li.end());
}

/**
 * @brief This function is called once after the simulation ends.
 *        It is used to print out the results of the simulation.
 */
void SchedulerPriorityRR::print_results() {

    for(int i = 0; i < count; i++){
        int ttime = times.at(i).at(0);
        int wtime = times.at(i).at(0) - times.at(i).at(1);
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
void SchedulerPriorityRR::simulate() {
    while(proc_li.size() > 0){
        curr_proc = &proc_li.front(); // curr_proc holds the highest priority process
        proc_li.pop_front();          // remove highest priority process from list
        
        if(unsigned(time_quantum) < curr_proc->burst_time){       // if burst time is longer than the quantum
            if(curr_proc->priority <= proc_li.front().priority && proc_li.size() != 0){
                std::cout << "Running Process " << curr_proc->name << " for " << time_quantum << " time units" << std::endl;
            }
            elapsed_time += time_quantum;               // only record passage of the time quantum
            times.at(curr_proc->id).at(1) += time_quantum;
            curr_proc->burst_time -= time_quantum;
            proc_li.push_back(*curr_proc);
        }else {
            if(curr_proc->priority <= proc_li.front().priority && proc_li.size() != 0){
                std::cout << "Running Process " << curr_proc->name << " for " << curr_proc->burst_time << " time units" << std::endl;
            }
            elapsed_time += curr_proc->burst_time;    // if burst time is shorter, record passage of burst time
            times.at(curr_proc->id).at(1) += curr_proc->burst_time;
            curr_proc->burst_time = 0;
            times.at(curr_proc->id).at(0) = elapsed_time;
            if(curr_proc->priority > proc_li.front().priority || proc_li.size() == 0){
                cout << "Running Process " << curr_proc->name << " for " << times.at(curr_proc->id).at(1) << " time units" << std::endl;
            }
        }

        std::sort(proc_li.begin(), proc_li.end());
    }

}

/**
 * @brief overloads the < operator so that it works on PCB objects
 *        this causes proc_li to sort in ascending order
 */
bool operator< (PCB A, PCB B){
    return A.priority > B.priority;
}
