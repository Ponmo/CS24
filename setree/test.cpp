#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
        for (int i = 0; i < 12040; i++) {
          set.insert("N" + std::to_string(i));
        }
        set.print();
        // set.lookup(10);
  return 0;
}
