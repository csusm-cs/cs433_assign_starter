/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here

Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
	//TODO: Add your implementation here
}

Replacement::~Replacement()
{
    // TOOD: Add your code here
}

bool Replacement::access_page(int page_num, bool is_write)
{
    // TODO: Add your implementation here
}