#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"

#include <istream>
#include <vector>
#include <queue>


struct starDistance {
    float distance;
    Star star;
};

struct Frame {
    unsigned long depth;
    int curr;
    int index;
    int endex;
    int parex;
    int oppex;
    int parexEndex;
    int parexIndex;
};

//size_t n, float x, float y, float z, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex

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
        int begDepth;
        size_t n;
        float x;
        float y;
        float z;
        int count;
        std::priority_queue<starDistance, std::vector<starDistance>, CompareAge> pq;

    public:
        StarMap(std::istream& stream);
        ~StarMap();

        std::vector<Star> find(size_t vn, float vx, float vy, float vz);
        void createKD(std::vector<Star>* data, unsigned long depth, int index, int endex);
        void find_recurse(unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex);
        std::vector<Star> find_recurse_iter(size_t n, float x, float y, float z);
};
#endif