#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;

  std::cout << set.insert("hello \n");
  std::cout << set.insert("hello \n");
  std::cout << set.insert("john \n");
  std::cout << set.count();

  return 0;
}
