#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
  set.insert("D");
    set.insert("B");
      set.insert("A");
        set.insert("C");
        set.lookup(2);
  return 0;
}
