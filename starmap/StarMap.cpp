#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <queue>
// template <class T, class Container = std::vector<T>,  class Compare = std::less<typename Container::value_type> > class priority_queue;


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
      std::cout << token;
      if (count == 0) {
        star.x = std::stof(token);
      }
      if (count == 1) {
        star.y = std::stof(token);
      }
      if (count == 2) {
        star.z = std::stof(token);
      }
    }
    data->push_back(star);
    id++;
  }
}

StarMap::~StarMap() {
  delete data;
}

//Use floats, don't use square roots, kevin used multiply (power)

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}


std::vector<Star> StarMap::find(size_t n, float x, float y, float z) { //find function
  // priority_queue<Star, std::vector<Star>, std::greater<int>> nearStars;
  std::priority_queue<Star> nearestStars;
  x++;
  y++;
  z++;
  std::vector<Star> hello;
  return hello;
};