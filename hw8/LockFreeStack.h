#ifndef LOCK_FREE_STACK_H
#  define LOCK_FREE_STACK_H
#include<atomic>
#include <iostream>
#include<memory>
using std::atomic;

namespace mpcs51044 {
// Linked list of integers
struct StackItem {
  StackItem(int val) : next(0), value(val) {}
  StackItem *next; // Next item, 0 if this is last
  int value;
};

struct StackHead {
  StackItem *link;      // First item, 0 if list empty
  unsigned count;      // How many times the list has changed (see lecture notes)
};

struct Stack {
  Stack();
  int pop();
  void push(int);
private:
  atomic<StackHead> head;
};

Stack::Stack()
{
  StackHead init;
  init.link = 0;
  init.count = 0;
  head.store(init);
}

// Pop value off list
int
Stack::pop()
{
    // What the head will be if nothing messed with it
    StackHead expected = head.load();
    StackHead newHead;
    bool succeeded = false;
    while(!succeeded) {
        if(expected.link == 0) {
            return 0; // List is empty
        }
        // What the head will be after the pop:
        newHead.link = expected.link->next;
        newHead.count = expected.count + 1;
        // Even if the compare_exchange fails, it updates expected.
        succeeded = head.compare_exchange_weak(expected, newHead);
    }
    int value = expected.link->value;
    delete expected.link;
    return value;
}

// Push an item onto the list with the given head
void
Stack::push(int val)
{
    /* Homework */
    StackItem* newitem = new StackItem(val);

    StackHead expected = head.load();
    bool succeeded = false;
    while(!succeeded)
    {
        StackHead newHead;
        newHead.count = expected.count + 1;
        newHead.link = newitem;
        newitem->next = expected.link;
        succeeded = head.compare_exchange_weak(expected, newHead);
    }
    //std::cout<<"pushed "<<val<<std::endl;
}
}
#endif
