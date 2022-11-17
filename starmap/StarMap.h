#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"

#include <istream>
#include <vector>


struct Node {
  //Star, the median node inside the list of nodes.
  //Depth?
  //list of nodes on a given side, becomes obsolete once constructed..
  Star* star;
  Node* left = nullptr;
  Node* right = nullptr;
};

class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream);

private:
    // Member Variables
    std::vector<Star> *data;

public:
    // Constructor & Destructor
    StarMap(std::istream& stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);
    // void recurse(Node* curr, std::vector<Star> list, unsigned long depth);

    // Other Member Functions
};
#endif
