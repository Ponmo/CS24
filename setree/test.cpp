#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
  set.insert("P");
    set.insert("G");
      set.insert("U");
        set.insert("E");
         set.insert("X");
    set.insert("E");
      set.insert("Y");
        set.insert("J");
        set.insert("K");
      set.insert("I");
        set.insert("M");
        set.insert("N");
        set.insert("O");
        set.insert("C");
        set.print();
        set.lookup(10);
        set.clear();
        set.insert("B");
        // set.lookup(10);
  return 0;
}
