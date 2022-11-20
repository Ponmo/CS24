
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
        static StarMap* create(std::istream& stream);

    private:
        std::vector<Star> *data;
        Node* root;

    public:
        StarMap(std::istream& stream);
        ~StarMap();

        std::vector<Star> find(size_t n, float x, float y, float z);
        Node* recurse(std::vector<Star> list, unsigned long depth);
        void find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth);
        //std::vector<Star>&) if want to pass by reference
};
#endif
// #ifndef STARMAP_H
// #define STARMAP_H

// #include "Star.h"

// #include <istream>
// #include <vector>
// #include <queue>


// struct starDistance {
//     float distance;
//     Star star;
// };

// struct CompareAge {
//     bool operator()(starDistance const & p1, starDistance const & p2) {
//         return p1.distance < p2.distance;
//     }
// };

// class StarMap {
//     public:
//         static StarMap* create(std::istream& stream);

//     private:
//         std::vector<Star> *data;

//     public:
//         StarMap(std::istream& stream);
//         ~StarMap();

//         std::vector<Star> find(size_t n, float x, float y, float z);
//         void createKD(std::vector<Star>* data, unsigned long depth, int index, int endex);
//         void find_recurse(size_t n, float x, float y, float z, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex);
// };
// #endif