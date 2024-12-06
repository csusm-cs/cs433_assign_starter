/**
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
void FIFOReplacement::load_page(int page_num) {}

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
