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

// TODO: Add your implementation here
LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames)
{
    // TODO: Complete this constructor
}

// TODO: Add your implementations for desctructor, touch_page, load_page, replace_page here
LRUReplacement::~LRUReplacement()
{
    // TODO: Add necessary code here
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
    // TODO: Update your data structure LRU replacement
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    // TODO: Update your data structure LRU replacement and pagetable
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    // TODO: Update your data structure LRU replacement and pagetable
    return 0;
}