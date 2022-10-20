#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
  set.insert("G");
    set.insert("B");
      set.insert("A");
        set.insert("C");
         set.insert("F");
    set.insert("U");
      set.insert("E");
        set.insert("H");
        set.print();
        set.remove("A");
        // set.lookup(10);
  return 0;
}
