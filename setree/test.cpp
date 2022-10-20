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
        set.insert("D");
      set.insert("I");
        set.insert("J");
        set.insert("L");
        set.insert("M");
        set.insert("K");
        set.print();
        set.remove("L");
        set.print();
        // set.lookup(10);
  return 0;
}
