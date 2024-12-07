/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.h
 * @author Zach Miller and Erin Bailey
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
#include "lru_replacement.h"

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

// Destructor
LRUReplacement::~LRUReplacement() {}

// Access a page already in physical memory
void LRUReplacement::touch_page(int page_num) {
    // remove the page from its current position in the list
    lru_list.erase(page_map[page_num]);
    // move page to the front of the list (most recently used)
    lru_list.push_front(page_num);
    // update its iterator in the map
    page_map[page_num] = lru_list.begin();
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    num_fault++; // increment page fault count
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = used_frames; // assign a frame to the page
    page_table[page_num].last_access = counter;  // update access time

    // add the new page to the front of the list
    lru_list.push_front(page_num);
    // store its iterator in the map
    page_map[page_num] = lru_list.begin();
}

// access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    num_fault++;  // increment page fault count
    num_replace++; // increment replacement count

    // the least recently used page is at the back of the list
    int lru_page = lru_list.back();
    lru_list.pop_back(); // remove it from the list

    // invalidate the evicted page in the page table
    page_table[lru_page].valid = false;
    int lru_frame = page_table[lru_page].frame_num;

    // replace the removed page with the new page
    frames[lru_frame] = page_num;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = lru_frame;
    page_table[page_num].last_access = counter;

    // add the new page to the front of the list
    lru_list.push_front(page_num);
    // update its iterator in the map
    page_map[page_num] = lru_list.begin();

    return lru_page; // return the removed page
}
