#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <stack>
// #include <cassert>
#include <cmath>
// template <class T, class Container = std::vector<T>,  class Compare = std::less<typename Container::value_type> > class priority_queue;

struct starDistance {
    float distance;
    int id;
};

//Find if it is a disk or whatever
StarMap::StarMap(std::istream& stream) {
  data = new std::vector<Star>; 
  std::string line;
  int id = 1;
  while (std::getline(stream, line)) {
    std::stringstream nLine(line);
    std::string token;
    Star star;
    star.id = id;
    int count = 0;
    while(std::getline(nLine, token, '\t')) {
      // std::cout << token;
      if (count == 0) {
        std::cout << '1';
        star.x = std::stof(token);
      }
      if (count == 1) {
        std::cout << '2';
        star.y = std::stof(token);
      }
      if (count == 2) {
        std::cout << '3';
        star.z = std::stof(token);
      }
      count++;
    }
    data->push_back(star);
    id++;
  }
}

StarMap::~StarMap() {
  delete data;
}

//Use floats, don't use square roots, kevin used multiply (power), mutliple kd trees for each block

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}

struct CompareAge {
    bool operator()(starDistance const & p1, starDistance const & p2) {
        return p1.distance < p2.distance;
    }
};

std::vector<Star> StarMap::find(size_t n, float x, float y, float z) { //find function
  std::priority_queue<starDistance, std::vector<starDistance>, CompareAge> pq;
  for(Star star : *data) {
    float distance = sqrt(pow(star.x - x, 2) + pow(star.y - y, 2) + pow(star.z - z, 2));
    starDistance curr = {distance, star.id};
    if(pq.size() >= n && pq.top().distance > distance) {
      pq.pop();
      pq.push(curr);
    }
    else {
      pq.push(curr);
    }
  }
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    std::cout << pq.top().id;
    std::cout << " ";
    nearest.push_back(data->at(pq.top().id - 1));
    pq.pop();
  }
  return nearest;
};




// std::vector<Star> StarMap::find(size_t n, float x, float y, float z) { //find function
//   float highestDistance = 100000000;
//   std::vector<std::pair<Star, float>> closest;

//   for(Star star : *data) {
//     float distance = sqrt(pow(star.x - x, 2) + pow(star.y-y, 2) + pow(star.z-z, 2));
//     closest.push_back({star, distance});
//     }
//   sort(closest.begin(), closest.end());
//   std::vector<Star> stars;
//   int count = 0;
//   for (auto s : closest) {
//     std::cout << s.first.id;
//     std::cout << s.second;
//     std::cout << "\n";
//     if (count != n) {
//       stars.push_back(s.first);
//     }
//   }
//   return stars;
// };