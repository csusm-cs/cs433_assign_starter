/**
* Assignment 5: Page replacement algorithms
 * @file pagetable.h
 * @author Zach Miller and Erin Bailey
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
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
	// last_access records the step in the algorithm when this page was last accessed
	unsigned int last_access = 0;

	PageEntry(int frame = 0){
		frame_num = frame;
		if(frame != 0){
			valid = true;
		}
	}
	~PageEntry(){}
};


/**
 * @brief A page table is like an array of page entries.
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
private:
    // A page table is like an array of page entries.

	vector<PageEntry>::iterator pageIt;
	vector<PageEntry> pages;
public:
	// Constructor
	PageTable(int num_pages);
	// Destructor
	~PageTable();

    // returns size of the page table
    int PageTable::getSize();
	
	/**
	* @brief Access a page in the page table.
	* @param i
	* @return
	*/
	PageEntry& operator [] (int i) {
		return pages[i];
	}
};