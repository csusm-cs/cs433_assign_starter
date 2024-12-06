/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Zach Miller and Erin Bailey
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) {}

LIFOReplacement::~LIFOReplacement() {}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
	greatest_frame = used_frames;			// records the last assigned frame number
	page_table[page_num].frame_num = used_frames;	// used_frames doubles as a frame number recorder here
	page_table[page_num].valid = true;		// make the new page valid
	used_frames++;
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
	for(int i = 0; i < num_pages; i++){
		if(page_table[i].valid == true && page_table[i].frame_num == greatest_frame){ // if the page is a valid frame ref AND it's frame is greatest_frame
			page_table[i].valid = false;			// make found page invalid
			page_table[page_num].frame_num = greatest_frame;	// make new page have the greatest_frame
			page_table[page_num].valid = true;		// make new page valid
			if(greatest_frame == 0){			// decrements greatest_frame, resets to num_frames if decrement would result in negative value
				greatest_frame = num_frames - 1;
			}else greatest_frame--;
		}
	}
	return 0;
}
