#include "Heap.h"
#include <iostream>
#include <stdexcept>
//An binary heap array that stores entries by score of each entry. Each entry is one word with its score. 

// Its parent is at index `(i - 1) / 2`.
// - Its left child is at index `i * 2 + 1`.
// - Its right child is at index `i * 2 + 2`.

Heap::Heap(size_t capacity) { //Constructor
    mData = new Heap::Entry[capacity];
    mCapacity = capacity;
    mCount = 0;
}

Heap::Heap(const Heap& other) { //Copy
    mData = new Heap::Entry[other.mCapacity];
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    for(size_t i; i<other.mCount; i++) {  // Loop through all entries in the other data, and put it into our own.
        mData[i] = other.mData[i];
    }
}
Heap::Heap(Heap&& other) { //Move
    if(other.mData) {
        mData = other.mData;
        delete[] other.mData;
        other.mData = nullptr;
    }
}
Heap::~Heap() { //Destructor
    delete[] mData;
}

size_t Heap::capacity() const { //Returns capacity
    return mCapacity;
}
size_t Heap::count() const { //Returns # of things in the array
    return mCount;
}
const Heap::Entry& Heap::lookup(size_t index) const { // Finds a value
    index++;
    return mData[0];
}
Heap::Entry Heap::pop() { //Remove word with the lowest score. Use this if inserting a high-scoring word into a full heap as well. Needs percolation
    return mData[0];
}
Heap::Entry Heap::pushpop(const std::string& value, float score) { //Needs percolation
    std::string hello = value;
    float hell = score;
    hell++;
    return mData[0];
}
void Heap::push(const std::string& value, float score) { //Needs percolation, pushes into the next possible space.
    //check if heap is already full...
    if(mCount == mCapacity) {
        throw std::overflow_error("Heap is already full");
    }

    //Insert it at the end (closest empty spot).
    Heap::Entry newEntry = {value, score};
    mData[mCount] = newEntry;

    //start percolating/swapping until it is in the right place with its parent.
    size_t currentPosition = mCount;
    while(currentPosition != 0 && score > mData[(currentPosition - 1) / 2].score) {
        mData[currentPosition] = mData[(currentPosition - 1) / 2];
        currentPosition = (currentPosition - 1) / 2;
        mData[currentPosition] = newEntry;
    }
    mCount++;
}
const Heap::Entry& Heap::top() const { // Returns the entry with the lowest score.
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}