#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"

#include <istream>
#include <vector>
#include <queue>

struct Node {
  //Star, the median node inside the list of nodes.
  //Depth?
  //list of nodes on a given side, becomes obsolete once constructed..
  Star star;
  Node* lesser = nullptr;
  Node* greater = nullptr;
};

struct starDistance {
    float distance;
    Node* star;
    // int id;
};

struct CompareAge {
    bool operator()(starDistance const & p1, starDistance const & p2) {
        return p1.distance < p2.distance;
    }
};

class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream);

private:
    // Member Variables
    // std::vector<Star> *data;
    Node* root;

public:
    // Constructor & Destructor
    StarMap(std::istream& stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);
    Node* recurse(std::vector<Star> list, unsigned long depth);
    void find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth);
    //std::vector<Star>&) if want to pass by reference

    // Other Member Functions
};
#endif