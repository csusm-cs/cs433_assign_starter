/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Nick F. Andrew & Julian Rangel
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   this->MAX = size;
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
   // Delete all the PCBs in the table
   for(int i = 0; i < MAX; i++){
      delete pcb_array[i];
   }
   delete[] pcb_array;
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
   if(idx < MAX){
      std::cout << "Got the PCB" << endl;
      return pcb_array[idx];
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
        // If idx is larger than maxSize and array idx assign ptr to index
        pcb_array[idx] = pcb;
    } else {
        // If idx is smaller than maxSize and array idx display error message
        cout << "Invalid index or PCB already exists at the specified index." << endl;
    }
}
