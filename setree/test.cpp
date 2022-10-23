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
        set.lookup(0);
        set.remove("A");
        set.insert("B");
        set.insert("P");
        set.insert("opwF");
        set.insert("mxicw");
        set.insert("pewojvm");
        set.lookup(0);
        set.clear();
        set.insert("B");
        set.lookup(0);
        // set.lookup(10);
  return 0;
}
