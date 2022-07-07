/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.h
 * @author ??? (TODO: your name)
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#pragma once

// Remember to add comments to your code
#include <vector>
using namespace std;

// A page table entry
/**
 * @brief A page table entry. This class is used to represent a page table entry.
 * @details Each page has one entry in the page table. It contains the following fields:
 * - frame number
 * - valid bit
 */
class PageEntry
{
public:
	// Physical frame number for a given page
	int frame_num;
	// valid bit represents whether a page is in the physical memory
	bool valid = false;
    // dirty bit represents whether a page is changed
    bool dirty = false;
};


/**
 * @brief A page table is like an array of page entries.
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
private:
    // A page table is like an array of page entries.
    vector<PageEntry> pages;
public:
    // Constructor
    PageTable(int num_pages);
    // Destructor
    ~PageTable();

	// TODO: Add your implementation of the page table here

    /**
     * @brief Access a page in the page table.
     * @param i
     * @return
     */
    PageEntry& operator [] (int i) {
        return pages[i];
    }
};