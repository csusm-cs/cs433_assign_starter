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
   for(int i = 0; i < size; i++){
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
   if(idx << MAX && pcb_array[idx] == nullptr){
      return pcb_array[idx] = pcb;
   }else{
      cout << "Invalid input try again bud." << endl;
   }
}
