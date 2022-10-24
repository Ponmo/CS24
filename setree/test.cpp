#include "Set.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set set;
        
       set.insert("1000");
        set.insert("500");
         set.insert("1500");
          set.insert("225");
           set.insert("725");
            set.insert("1250");
             set.insert("1750");
              set.insert("125");
               set.insert("625");
                set.insert("825");
                 set.insert("1790");
                  set.insert("1720");
                   set.insert("1400");
                    set.insert("2000");
                     set.insert("1001");
                      set.insert("10002");


        set.print();
        std::cout << "\n";

        set.remove("825");
        
        set.print();
                std::cout << "\n";
         set.remove("1001");
         set.print();
                 std::cout << "\n";
          set.remove("725");
        // set.lookup(10);
  return 0;
}
