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