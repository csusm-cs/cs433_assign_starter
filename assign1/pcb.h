/**
 * Assignment 1: priority queue of processes
 * @file pcb.h
 * @author Nick F. Andrew & Julian Rangel
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to addPCB sufficient comments to your code

#pragma once
#include <iostream>
using namespace std;

// enum class of process state
// A process (PCB) in ready queue should be in READY state
enum class ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/**
 * @brief A process control block (PCB) Process control block(PCB) is a data structure representing a process in the system.
   A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
   It may also have other attributes, such as scheduling information (e.g. priority)
 *
 */
class PCB {
public:
    // The unique process ID
	unsigned int id;
    // The priority of a process valued between 1-50. Larger number represents higher priority
	unsigned int priority;
	// The current state of the process.
	// A process in the ReadyQueue should be in READY state
	ProcState state;

	/**
	 * @brief Construct a new PCB object
	 * @param id: each process has a unique ID
	 * @param priority: the priority of the process in the range 1-50. Larger number represents higher priority
	 * @param state the state of the process.
     */
    PCB(unsigned int id = 0, unsigned int priority = 1, ProcState state = ProcState::NEW) {
        this->id = id;
        this->priority = priority;
        this->state = state;
    }

    /**
     * @brief Destroy the PCB object.
     *
     */
    ~PCB() {}

    /**
     * @brief Get the ID of the PCB.
     *
     * @return unsigned int: the ID of the PCB
     */
    unsigned int getID() {
        return id;
    }

    /**
     * @brief Get the priority of the PCB.
     *
     * @return unsigned int: the priority of the PCB
     */
    unsigned int getPriority() {
        return priority;
    }

    /**
     * @brief Get the state of the PCB.
     *
     * @return ProcState: the state of the PCB
     */
    ProcState getState() {
        return state;
    }

    /**
     * @brief Change the state of the PCB.
     * @param state
     */
    void setState(ProcState state) {
	    this->state = state;
    }

    /**
     * @brief Change the priority of the PCB.
     * @param priority
     */
    void setPriority(unsigned int priority) {
	    this->priority = priority; //set the priority of the pcb table or changes it
    }

    /**
     * @brief Print the PCB.
     *
     */
    void display() const {
        cout << "ID: " << id;
        cout << ", Priority: " << priority;
        cout << ", State: " ;
        switch(state) {
            case ProcState::NEW:
                cout << "NEW";
                break;
            case ProcState::READY:
                cout << "READY";
                break;
            case ProcState::RUNNING:
                cout << "RUNNING";
                break;
            case ProcState::WAITING:
                cout << "WAITING";
                break;
            case ProcState::TERMINATED:
                cout << "TERMINATED";
                break;
        } 
        cout << endl;
    }
};
