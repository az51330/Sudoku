#include <iostream>
#include <cassert>
#include "stack.h"

stack::node::node() {}  // node constructor leaving fields uninitialized

stack::node::node(const element & item, node * n) {
  data = item;
  next = n;
}

stack::stack() {
  _top = nullptr;
}

void stack::push(const element & e)
{
  // make a new node baby and make its next the beginning of the list
  // make the list start at baby
  _top = new node(e, _top);
}

void stack::pop()
{
  // check that the list has an item
  assert(!empty());
  // move top to the second item and delete the first
  node* garbage = _top;
  _top = _top -> next;
  delete garbage;
}

stack::element stack::top() const
{
  // check that the list has an item
  assert(!empty());
  // return the data of the first item
  return _top -> data;
}

bool stack::empty() const
{
  return _top == nullptr;
}
