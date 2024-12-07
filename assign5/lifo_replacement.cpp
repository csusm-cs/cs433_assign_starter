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

  num_fault++;

  greatest_frame++;

  page_table[page_num].frame_num = used_frames;	// used_frames doubles as a frame number recorder here

  

  page_table[page_num].valid = true;		// make the new page valid

  frames[used_frames] = page_num;

}



// Access an invalid page and no free frames are available

int LIFOReplacement::replace_page(int page_num) {

  num_fault++;

  num_replace++;

  int bad_page = frames[greatest_frame];

  frames[greatest_frame] = page_num;

  page_table[bad_page].valid = false;

  page_table[page_num].frame_num = greatest_frame;

  page_table[page_num].valid = true;

	return 0;

}

