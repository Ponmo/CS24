#include "List.h"
#include <iostream>

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main() {
  List list;
  list.insert("hi");
  list.insert("bye");
  list.insert("seven");
  std::cout << list.remove(1);

  std::cout << "This program doesn't do anything interesting yet...\n";

  return 0;
}
