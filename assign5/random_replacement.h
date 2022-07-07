/**
* Assignment 5: Page replacement algorithms
 * @file random_replacement.h
 * @author ??? (TODO: your name)
 * @brief A class implementing the Random page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#pragma once

// Remember to add comments to your code

#include "replacement.h"

/**
 * @brief A class to simulate the random page replacement algorithm.
 */
class RandomReplacement : public Replacement
{
	// TODO: Add your implementation to this class
public:
	/**
	 * @brief Constructor
	 * @param num_pages
	 * @param num_frames
	 */
	RandomReplacement(int num_pages, int num_frames);

    /**
    * @brief Destructor
    */
    virtual ~RandomReplacement();

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
     * @brief Accesss a page alreay in physical memory
     * It may be overridden in a subclass
     * @param page_num The logical page number.
     */
    virtual void touch_page(int page_num);

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);
};