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
        if (num_frames > used_frames) {  // if there are more available frames than used frames
            page.valid = true;  // move this into load_page function when defined in subclasses
            used_frames++; 
            load_page(page_num);
        } else {           // if there are no free frames
            replace_page(page_num);
            num_replace++;
        }
        num_fault++;    // if page is invalid, we have a page fault
        return true;    // page fault
    }/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Erin Bailey and Zach Miller
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) {}

FIFOReplacement::~FIFOReplacement() {}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
  page_table[page_num].frame_num = used_frames - 1;	// used_frames doubles as a frame number recorder here
  page_table[page_num].valid = true;			// make the new page valid
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    for(int i = 0; i < num_pages; i++){
        if(page_table[i].valid == true && page_table[i].frame_num == least_frame){ // if the page is a valid frame ref AND it's frame is least_frame
            page_table[i].valid = false;			// make found page invalid
            page_table[page_num].frame_num = least_frame;		// make new page have the least_frame
            page_table[page_num].valid = true;			// make new page valid
            least_frame = (least_frame + 1) % num_frames;	// increment least_frame to the next value, resets to 0 after reaching the max num_frames
        }
    }
    return 0;
}
	counter++;
}

void Replacement::touch_page(int page_num) {
	page_table[page_num].last_access = counter;
}

// Access an invalid page, but free frames are available
void Replacement::load_page(int page_num) {
  page_table[page_num].frame_num = used_frames;	// used_frames doubles as a frame number recorder here
    page_table[page_num].valid = true;			// make the new page valid
	used_frames++;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
        // TODO: print out the number of references, number of page faults and number of page replacements
		std::cout << "Number of references: \t\t"  << std::endl;
		std::cout << "Number of page faults: \t\t" << std::endl;
		std::cout << "Number of page replacements: \t"  << std::endl;
}
