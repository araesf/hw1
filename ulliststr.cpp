#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// push_back
void ULListStr::push_back(const std::string& val) {
  // if no nodes exist yet
  if (tail_ == nullptr) {
    Item* newItem = new Item();
    head_ = tail_ = newItem;
    tail_->first = 0;
    tail_->last = 1;
    tail_->val[tail_->first] = val;
  } 
  
  // if previous node's array is full
  else if (tail_->last == ARRSIZE) {
    Item* newItem = new Item();
    newItem->first = 0;
    newItem->last = 1;
    newItem->val[newItem->first] = val;
    tail_->next = newItem;
    newItem->prev = tail_;
    tail_ = newItem;
  }
  
  // if there is space in current array
  else {
    tail_->val[tail_->last] = val;
    tail_->last++;
  }

  size_++;
}


// push_front
void ULListStr::push_front(const std::string& val) {
  // if no nodes exist yet
  if (head_ == nullptr) {
    Item* newItem = new Item();
    head_ = tail_ = newItem;
    head_->first = ARRSIZE - 1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val;
  } 
  
  // if previous node's array is full
  else if (head_->first == 0) {
    Item* newItem = new Item();
    newItem->first = ARRSIZE - 1;
    newItem->last = ARRSIZE;
    newItem->val[newItem->first] = val;

    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
  }
  
  // if there is space in current array
  else {
    head_->first--;
    head_->val[head_->first] = val;
  }

  size_++;
}

// pop_back
void ULListStr::pop_back() {
  if (tail_ == nullptr) {
    return;
  }

  // still elements in array:
  if (tail_->first < tail_->last - 1) {
    tail_->last--;
    size_--;
  }

  // if only one element in array
  else if (tail_->first == tail_->last - 1) {
    // if only one node in list
    if (head_ == tail_) {
      delete tail_;
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    }

    // if element is last in array
    else {
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = nullptr;
      delete temp;
      size_--;
    }
  }
}

// pop_front
void ULListStr::pop_front() {
  if (head_ == nullptr) {
    return;
  }

  // still elements in array
  if (head_->first < head_->last - 1) {
    head_->first++;
    size_--;
  }

  // only one element in array
  else if (head_->first == head_->last - 1) {
    // if only one node in list
    if (head_ == tail_) {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      size_ = 0;
    }

    // if element is last in the array
    else {
      Item* temp = head_;
      head_ = head_->next;
      head_->prev = nullptr;
      delete temp;
      size_--;
    }
  }
}

// back
std::string const & ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}


// front
std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}


// getValAtLoc
std::string* ULListStr::getValAtLoc(size_t loc) const {
  Item* curr_ = head_;
  size_t count = 0;

  // location does not exist
  if (size_ <= loc){
    return NULL;
  }

  // iterate though each node, from the node's first to last pointers.
  // increment count until last occurance of last pointer or until loc is achieved.
  while (curr_) {
    for (int i = curr_->first; i < curr_->last; i++) {
      if (count == loc) {
        std::string* valAtLoc = &curr_->val[i];
        return valAtLoc;
      }
      
      count++;
    }

    curr_ = curr_->next;
  }
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
