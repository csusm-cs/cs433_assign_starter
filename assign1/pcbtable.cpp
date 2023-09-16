/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Nick F. Andrew & Julian Rangel
 * @brief This is the implementation file for the PCBTable class.
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   pcb_array = new PCB*[size];         //Make a new pcb_array
   MAX = size;                         //set our MAX to the given size
   for (int i = 0; i < MAX; ++i) {     //Fill our new array with null pointers
      pcb_array[i] = nullptr; 
   }
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   for(int i = 0; i < MAX; i++){       //Delete all the PCBs in the table
      delete pcb_array[i];
   }
   delete[] pcb_array;                 //delete the array 
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
   if(idx < MAX){
      return pcb_array[idx];           //after checking for proper calling, return the requested PCB
   }
   return NULL;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
   // Add a PCB pointer to the PCBTable at index idx.
   if (idx < MAX) {
        pcb_array[idx] = pcb;             //sets the given PCB to the bottom of the list
    } else {
        cout << "Invalid input" << endl;  //catches invalid indexs
    }
}
