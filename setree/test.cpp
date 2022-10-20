#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
  std::cout << set.count();
  set.insert("hello");
    std::cout << set.count();
  set.insert("hello");
    std::cout << set.count();
  set.insert("john");
  std::cout << set.count();
  set.insert("a");
    std::cout << set.count();
  set.insert("wefs");
    std::cout << set.count();
  set.insert("weopcjpoew");
  std::cout << set.count();

  return 0;
}
