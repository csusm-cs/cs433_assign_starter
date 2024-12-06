/**
* Assignment 5: Page replacement algorithms
 * @file replacement.h
 * @author Zach Miller and Erin Bailey
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code
#pragma once

#include "pagetable.h"


/**
 * @brief A base class to simulate page replacement algorithms.
 * A specific page replacement algorithm, e.g. FIFO or LRU, should be subclass of this.
 */
class Replacement
{
protected:      // subclasses can access these members
    // Member variable for the page table
    PageTable page_table;
	int num_fault = 0,  // number of page faults
		num_replace = 0,  // number of replacements
		num_pages = 0,  // number of pages
		num_frames = 0,  // number of frames
		used_frames = 0,  // number of used frames
		used_pages = 0;  // number of used pages
	unsigned int counter = 0; // counts number of accesses to measure how long ago a ref was accessed last.
	vector<int> frames;
	
public:
	/**
	 * @brief 
	 * @param num_pages Total number of logical pages for the simulation.
	 * @param num_frames Total number of available free frames.
	 */
	Replacement(int num_pages, int num_frames);

    /**
     * @brief Destructor
     */
    virtual ~Replacement();

	// TODO: Add additional member variables and functions if needed
    /**
	 * @brief Simulate a single page access.
     * @details If the page is valid, it calls the touch_page function. 
     *          If the page is not valid but free frames are available, it calls the load_page function.
     *          If the page is not valid and there is no free frame, it calls the replace_page function.
     * @param page_num The logical page number.
	 * @param is_write whether this access a memory write
	 * @return whether it's a page fault: true if it's a page fault
	 */
    virtual bool access_page(int page_num, bool is_write = false);

    /**
	 * @brief Accesss a page already in physical memory
	 * It may be overridden in a subclass 
	 * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available frame, not replacement needed
     * It may be overridden in a subclass 
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);


    /**
	 * @brief Access an invalid page and no free frame is available.
     * Select a victim page to be replaced.
	 * It is a pure virtual function to be implemented in specific replacement subclasses.
     * @param page_num  The logical page number of the desired page.
	 * @return Selected victim page #
	 */
    virtual int replace_page(int page_num) = 0;

    /**
	 * @brief Get the ith entry of the page table
	 */
    PageEntry getPageEntry(int page_num) {
        return page_table[page_num];
    }

    /**
	 * @brief Print the statistics of simulation
	 */
    void print_statistics() const;
};
