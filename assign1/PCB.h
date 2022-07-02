#pragma once

// Remember to add comments to your code
// ...

// enum class of process state
// A process (PCB) in ready queue should be in READY state
enum class ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/* 
Process control block(PCB) is a data structure representing a process in the system.
A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
It may also have other attributes, such as scheduling information (e.g. priority)
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

	// TODO: Add constructor and other necessary functions for the PCB class
};
