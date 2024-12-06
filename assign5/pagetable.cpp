/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Zach Miller and Erin Bailey
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) {
    for(int i = 0; i < num_pages; i++){
        pages.emplace_back(PageEntry());
    }
}

// Destructor
PageTable::~PageTable() {}
