/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Zach Miller
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

using namespace std;


/**
 * Implementation:
 * 1. Input processes along with their burst time
 * 2. Find waiting time for all processes
 * 3. First process does not need to wait so its waiting time is 0.
 * 4. Find waiting time for all other processes via wt[i] = bt[i - 1] + wt[i - 1].
 * 5. Find turnaround time via waiting_time + burst_time.
 * 6. Find avg waiting time = total_waiting_time / no_of_processes
 * 7. Find avg turnaround time = total_turnaround_time / no_of_processes.
 */
                       
/**
 * @brief SchedulerFCFS constructor to initialize member functions
 */
SchedulerFCFS::SchedulerFCFS() {
    currentTime = 0;
}

/**
 * @brief SchedulerFCFS deconstructor
 */
SchedulerFCFS::~SchedulerFCFS(){};

/**
 * @brief This function is called once before the sim starts, it is used to initialize the scheduler
 */
void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    processes = process_list;
    completionTimes.resize(process_list.size(), 0);
}

/**
 * @brief This function is called once after the sim ends, it is used to print out the results of the sim
 */
void SchedulerFCFS::print_results() {
    // for(int i = 0; i < process_list.size(); i++) {  // iterate through filled local vector
    //     process_list[i].print();  // use print PCB function to print process data
    // }
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;
    double sizeOfProcesses = processes.size();

    cout << "Name\tPID\tPriority\tBurst\tCompletion\tTurnaround\tWaiting\n";

    for (size_t i = 0; i < processes.size(); i++) {  // iterates through processes vector
        double turnaroundTime = completionTimes[i] - processes[i].arrival_time;  // set turnaround time
        double waitingTime = turnaroundTime - processes[i].burst_time;  // set waiting time
        

        totalTurnaroundTime += turnaroundTime;  // save turnaround time into total to be used later
        totalWaitingTime += waitingTime;  // save waiting time into total to be used later

        // prints out process information
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t"
        << processes[i].burst_time << "\t" << completionTimes[i] << "\t\t"
        << turnaroundTime << "\t\t" << waitingTime << endl;
    }
    double avgTT = totalTurnaroundTime / sizeOfProcesses;  // Calculate average turn-around time
    double avgWT = totalWaitingTime / sizeOfProcesses;  // Calculate average waiting time

    // prints out average turn-around and waiting times
    cout << "Average turn-around time = " << avgTT << " " << "Average waiting time = " << avgWT << endl;
}

/**
 * @brief This function sims the scheduling of processes in the ready queue, it stops when all processes are finished.
*/
void SchedulerFCFS::simulate() {
    for (size_t i = 0; i < processes.size(); i++) {
        // If the current time is less than the arrival time of the process, wait until it arrives (not applicable in this scheduling method)
        if (currentTime < processes[i].arrival_time) {
            currentTime = processes[i].arrival_time;
        }

        // Calculate completion time for the process
        currentTime += processes[i].burst_time;
        completionTimes[i] = currentTime;

        // prints which process is running with information
        cout << "Running Process " << processes[i].name << " for " << processes[i].burst_time << " time units.\n";
    }
}

