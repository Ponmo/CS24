#include "List.h"
#include <iostream>

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main() {
  List list;
  list.insert("hi");
  list.insert("hi");
  list.insert("hi");
  list.insert("bye");
  // std::cout << list.remove(0);
  std::cout << list.remove("hi");

  return 0;
}
