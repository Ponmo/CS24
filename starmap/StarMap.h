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

struct CompareAge {
    bool operator()(starDistance const & p1, starDistance const & p2) {
        return p1.distance < p2.distance;
    }
};

class StarMap {
    public:
        static StarMap* create(std::istream& stream);

    private:
        std::vector<Star> data;
        float best;
        size_t n;
        float x;
        float y;
        float z;
        std::priority_queue<starDistance, std::vector<starDistance>, CompareAge> pq;

    public:
        StarMap(std::istream& stream);
        ~StarMap();

        std::vector<Star> find(size_t vn, float vx, float vy, float vz);
        void createKD(unsigned long depth, int index, int endex);
        void find_recurse(unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex);
};
#endif