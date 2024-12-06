/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Zach Miller and Erin Bailey 
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"

// TODO: Add your implementation of the Replacement member functions here

// Constructor
Replacement::Replacement(int num_pages, int num_frames) : page_table(num_pages)
{
	//TODO: Add your implementation here
	this->num_frames = num_frames;
	this->num_pages = num_pages;
    
}

// Destructor
Replacement::~Replacement() {}


// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
    // TODO: Add your implementation here
    // If the page is valid, it calls the touch_page function. 
    // If the page is not valid but free frames are available, it calls the load_page function.
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    PageEntry& page = page_table[page_num];

    if (page.valid) {   // if page is valid
        touch_page(page_num);   // call touch_page function
        return false;   // no page fault
    } 
    else {  // page is invalid
		num_fault++;
        if (num_frames > used_frames) {  // if there are more available frames than used frames
            page.valid = true;  // move this into load_page function when defined in subclasses
            load_page(page_num);
			used_frames++;
        } else {           // if there are no free frames
            replace_page(page_num);
            num_replace++; // counter for the number of page replacements
        }
        num_fault++;    // if page is invalid, we have a page fault
        return true;    // page fault
    }
	counter++;
}

void Replacement::touch_page(int page_num) {
	page_table[page_num].last_access = counter;
}

// Access an invalid page, but free frames are available
void Replacement::load_page(int page_num) {}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        // TODO: print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: \t\t"  << counter << std::endl;
		std::cout << "Number of page faults: \t\t" << num_fault << std::endl;
		std::cout << "Number of page replacements: \t"  << num_replace << std::endl;
}
