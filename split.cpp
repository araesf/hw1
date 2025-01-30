/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  if (!in) {
    return;
  }

  // detatch head of input list so we can append it to either
  // odd or even list. in order to do this, we need to detatch
  // the next node
  Node* curr_ = in;
  in = in->next;
  curr_->next = nullptr;

  // if even, recursively find the last node in even list 
  // and append the current node from input list to next node in even list.
  // vice versa if odd.
  if (curr_->value % 2 == 0) {
    if (evens == nullptr) {
      evens = curr_;
    } else {
      Node* temp = findLastNode(evens);
      temp->next = curr_;
    }
  }
  
  else {
      if (odds == nullptr) {
      odds = curr_;
      } else {
      Node* temp = findLastNode(odds);
      temp->next = curr_;
    }
  }

  split(in, odds, evens);
}


// helper function to recursively find the last node in either odd or even
// linked lists.
Node* findLastNode(Node*& n) {
  if (n->next == nullptr) {
    return n;
  }

  findLastNode(n->next);
}