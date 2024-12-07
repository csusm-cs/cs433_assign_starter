#include "lru_replacement.h"

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

// Destructor
LRUReplacement::~LRUReplacement() {}

// Access a page already in physical memory
void LRUReplacement::touch_page(int page_num) {
    // Remove the page from its current position in the list
    lru_list.erase(page_map[page_num]);
    // Move the page to the front of the list (most recently used)
    lru_list.push_front(page_num);
    // Update its iterator in the map
    page_map[page_num] = lru_list.begin();
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    num_fault++; // Increment page fault count
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = used_frames; // Assign a frame to the page
    page_table[page_num].last_access = counter;  // Update access time

    // Add the new page to the front of the list
    lru_list.push_front(page_num);
    // Store its iterator in the map
    page_map[page_num] = lru_list.begin();
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    num_fault++;  // Increment page fault count
    num_replace++; // Increment replacement count

    // The least recently used page is at the back of the list
    int lru_page = lru_list.back();
    lru_list.pop_back(); // Remove it from the list

    // Invalidate the evicted page in the page table
    page_table[lru_page].valid = false;
    int lru_frame = page_table[lru_page].frame_num;

    // Replace the evicted page with the new page
    frames[lru_frame] = page_num;
    page_table[page_num].valid = true;
    page_table[page_num].frame_num = lru_frame;
    page_table[page_num].last_access = counter;

    // Add the new page to the front of the list
    lru_list.push_front(page_num);
    // Update its iterator in the map
    page_map[page_num] = lru_list.begin();

    return lru_page; // Return the evicted page
}
