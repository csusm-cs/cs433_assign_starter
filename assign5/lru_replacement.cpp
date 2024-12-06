/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author ??? (TODO: your name)
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

// Destructor
LRUReplacement::~LRUReplacement() {}

// Access a page already in physical memory
void LRUReplacement::touch_page(int page_num) {
    // find page in lru_list and move to front
    lru_list.remove(page_num); 
    lru_list.push_front(page_num); // add it to front
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    num_fault++; // Increment page fault count
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = used_frames; // Assign a frame to the page
    page_table[page_num].last_access = counter;  // Update access time

    // Add the page to the front of the LRU list
    lru_list.push_front(page_num);
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    num_fault++;  // Increment page fault count
    num_replace++; // Increment replacement count

    // least recently used page is at the back of the list, save into lru_page
    int lru_page = lru_list.back();
    lru_list.pop_back(); // Remove lru_page from the list

    // set removed page to invalid
    page_table[lru_page].valid = false;
    int lru_frame = page_table[lru_page].frame_num;

    // replace removed page with new page
    frames[lru_frame] = page_num;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = lru_frame;

    // add new page to the front of the LRU list
    lru_list.push_front(page_num);

    return lru_page;
}
