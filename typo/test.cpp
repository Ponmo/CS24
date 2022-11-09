#include "Heap.h"
#include <iostream>

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main() {
    Heap heap(8);
    heap.push("Hello", 4);
    heap.push("ByeBye", 1);
    heap.push("SeeYa", 3);
    heap.push("OK", 2);
    heap.pop();

    return 0;
}
