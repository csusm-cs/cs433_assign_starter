/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Caden Jamason, Adrian Reyes
 * @brief This is the implementation file for the PCBTable class.
 */

// You must complete the all parts marked as "TODO". Delete "TODO" after you are
// done. Remember to add sufficient comments to your code.

#include "pcbtable.h"

/**
 * @brief Construct a new `PCBTable` object of the given size (number of PCBs)
 *
 * @param size: the capacity of the `PCBTable`
 */
PCBTable::PCBTable(int size) {
  // TODO: make sure this works
  this->pcbTable.resize(size);
}

/**
 * @brief Destroy the `PCBTable` object.
 *
 * @note Make sure to delete all the PCBs in the table.
 */
PCBTable::~PCBTable() {
  // TODO: make sure this works
  // Deletes all the PCBs in the table.
  for (unsigned int i = 0; i < pcbTable.size(); i++) {
    delete pcbTable[i];
  }
}

/**
 * @brief Get the PCB at index `idx` of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return `PCB*` – pointer to the PCB at index `idx`
 */
PCB *PCBTable::getPCB(unsigned int idx) {
  // TODO: make sure this works
  // Check if index exists in PCBTable.
  // If it does, return the PCB at the index.
  // Otherwise, return NULL.
  if (idx < pcbTable.size()) {
    return pcbTable[idx];
  }
  return NULL;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
  // TODO: make sure this works
  // If index is within bounds of PCBTable, add PCB pointer to PCBTable at
  // index.
  // Otherwise, delete PCB pointer to prevent memory leak.
  if (idx < pcbTable.size()) {
    pcbTable[idx] = pcb;
  } else {
    delete pcb;
  }
}
