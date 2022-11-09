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
    for(size_t i = 0; i<other.mCount; i++) {  // Loop through all entries in the other data, and put it into our own.
        mData[i] = other.mData[i];
    }
}
Heap::Heap(Heap&& other) { //Move
    mCapacity = other.mCapacity;
    mCount = other.mCount;
    if(other.mData != nullptr) {
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
    if(index >= mCount) {
        throw std::out_of_range("Out of range on lookup");
    }
    return mData[index];
}
Heap::Entry Heap::pop() { //Remove word with the lowest score. Use this if inserting a high-scoring word into a full heap as well. Needs percolation
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty on pop");
    }
    Heap::Entry lowestEntry = mData[0];
    mData[0] = mData[mCount-1];
    if(mCount >= 2) {
        Heap::Entry entryIterator = mData[0];
        size_t currentPosition = 0;
        while(((currentPosition * 2) + 1) < mCount) { //Loop until it reaches the end or finds it (break;)
            if(((currentPosition * 2) + 2) < mCount && entryIterator.score > mData[(currentPosition * 2) + 2].score && mData[(currentPosition * 2) + 1].score > mData[(currentPosition * 2) + 2].score) { //Swap right child
                mData[currentPosition] =  mData[(currentPosition * 2) + 2];
                currentPosition = currentPosition * 2 + 2;
                mData[currentPosition] = entryIterator;
            }
            else if (((currentPosition * 2) + 1) < mCount && entryIterator.score > mData[(currentPosition * 2) + 1].score) { //Swap Left Child  && mData[(currentPosition * 2) + 1].score < mData[(currentPosition * 2) + 2].score
                mData[currentPosition] =  mData[(currentPosition * 2) + 1];
                currentPosition = currentPosition * 2 + 1;
                mData[currentPosition] = entryIterator;
            }
            else {
                break;
            }
        }
    }
    mCount--;
    return lowestEntry;
}
Heap::Entry Heap::pushpop(const std::string& value, float score) { //First it pops the value, then it pushes the value. Needs percolation
    if(mCount == 0) {
        throw std::underflow_error("Heap is empty on pushpop");
    }
    // Removes top value, inserts "value" then percolates down. Pop() then Push()
    Heap::Entry lowestEntry = mData[0];
    Heap::Entry newEntry = {value, score};
    mData[0] = newEntry;
    // Heap::Entry entryIterator = mData[0];
    size_t currentPosition = 0;
    if(mCount >= 2) {
        while(((currentPosition * 2) + 1) < mCount) { //Loop until it reaches the end or finds it (break;)
            if(((currentPosition * 2) + 2) < mCount && score > mData[(currentPosition * 2) + 2].score && mData[(currentPosition * 2) + 1].score > mData[(currentPosition * 2) + 2].score) { //Swap right child
                mData[currentPosition] =  mData[(currentPosition * 2) + 2];
                currentPosition = currentPosition * 2 + 2;
                mData[currentPosition] = newEntry;
            }
            else if (((currentPosition * 2) + 1) < mCount && score > mData[(currentPosition * 2) + 1].score) { //Swap Left Child && mData[(currentPosition * 2) + 1].score < mData[(currentPosition * 2) + 2].score
                mData[currentPosition] =  mData[(currentPosition * 2) + 1];
                currentPosition = currentPosition * 2 + 1;
                mData[currentPosition] = newEntry;
            }
            else {
                break;
            }
        }
    }
    return lowestEntry;
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
    while(currentPosition != 0 && score < mData[(currentPosition - 1) / 2].score) {
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