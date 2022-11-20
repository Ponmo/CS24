#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

bool comparatorx(const Star& lhs, const Star& rhs) {
   return lhs.x < rhs.x;
}
bool comparatory(const Star& lhs, const Star& rhs) {
   return lhs.y < rhs.y;
}
bool comparatorz(const Star& lhs, const Star& rhs) {
   return lhs.z < rhs.z;
}
StarMap::StarMap(std::istream& stream) {
  data = new std::vector<Star>;
  std::string line;
  int id = 1;
  while (std::getline(stream, line)) {
    std::stringstream nLine(line);
    float x, y, z;
    nLine >> x >> y >> z;
    Star star = {id++, x, y, z};
    data->push_back(star);
    // data->push_back(Star());
    // nLine >> data->back().x >> data->back().y >> data->back().z;
  }
  createKD(data, 0, 0, data->size() - 1);
}
void StarMap::createKD(std::vector<Star>* data, unsigned long depth, int index, int endex) {
  int med = (endex-index)/2 + index; 
  auto m = data->begin() + med;
  if (depth == 0 || depth % 3 == 0) {
    std::nth_element(data->begin() + index, m, data->begin() + endex + 1, &comparatorx);
  }
  else if (depth % 3 == 1) { 
    std::nth_element(data->begin() + index, m, data->begin() + endex + 1, &comparatory);
  }
  else {
    std::nth_element(data->begin() + index, m, data->begin() + endex + 1, &comparatorz);
  }
  if(med-1-index >= 1) { 
    createKD(data, depth + 1, index, med-1); 
  }
  if(endex-med-1 >= 1) {
    createKD(data, depth + 1, med + 1, endex);
  }
}
std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {
  std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq = new std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>;
  find_recurse(n, x, y, z, pq, 0, (data->size()-1)/2, 0, data->size() - 1, -1, -1, -1, -1, -1);
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    nearest.insert(nearest.begin(), pq->top().star); //Optimize this by inserting backwards
    pq->pop();
  }
  delete pq;
  return nearest;
}
void StarMap::find_recurse(size_t n, float x, float y, float z, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth, int curr, int index, int endex, int parex, int leftex, int rightex, int parexEndex, int parexIndex) {
  // std::cout << "1 ";
  float distance = (data->at(curr).x - x)*(data->at(curr).x - x) + (data->at(curr).y - y)*(data->at(curr).y - y) + (data->at(curr).z - z)*(data->at(curr).z - z); //Distance to spaceship
  if(pq->size() >= n && pq->top().distance > distance) {
    pq->pop();
    starDistance obj = {distance, data->at(curr)};
    pq->push(obj);
  }
  else if (pq->size() < n) {
    starDistance obj = {distance, data->at(curr)};
    pq->push(obj);
  }  
  int leftChild = index+(curr-1-index)/2;
  int rightChild = curr+1+(endex-curr-1)/2;
  int d = depth % 3;
  int c = depth * 100/12*100/12*100/12*100/12*100/12*100/12*100/12*100/12;
  c++;
  
  if (depth == 0 || d == 0) {
    if(data->at(curr).x >= x && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, leftChild, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, rightChild, endex, index);
    }
  }
  else if (d == 1) {
    if(data->at(curr).y >= y && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, leftChild, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, rightChild, endex, index);
    }
  }
  else {
    if(data->at(curr).z >= z && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, leftChild, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, rightChild, endex, index);
    }
  }

  if(parex != -1) { 
    if((depth - 1) % 3 == 0) {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).x - x)) {
        if(curr == leftex && rightex > parex && rightex <= parexEndex) {
          find_recurse(n ,x, y, z, pq, depth, rightex, parex+1, parexEndex, -1, -1, -1, -1, -1);
        }
        else if(curr == rightex && leftex >= parexIndex && leftex < parex) { 
          find_recurse(n ,x, y, z, pq, depth, leftex, parexIndex, parex-1, -1, -1, -1, -1, -1);
        }
      }
    }
    else if ((depth - 1) % 3 == 1) {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).y - y)) {
        if(curr == leftex && rightex > parex && rightex <= parexEndex) { 
          find_recurse(n ,x, y, z, pq, depth, rightex, parex+1, parexEndex, -1, -1, -1, -1, -1);
        }
        else if(curr == rightex && leftex >= parexIndex && leftex < parex) {
          find_recurse(n ,x, y, z, pq, depth, leftex, parexIndex, parex-1, -1, -1, -1, -1, -1);
        }
      }
    }
    else {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).z - z)) {
        if(curr == leftex && rightex > parex && rightex <= parexEndex) {
          find_recurse(n ,x, y, z, pq, depth, rightex, parex+1, parexEndex, -1, -1, -1, -1, -1);
        }
        else if(curr == rightex && leftex >= parexIndex && leftex < parex) { 
          find_recurse(n ,x, y, z, pq, depth, leftex, parexIndex, parex-1, -1, -1, -1, -1, -1);
        }
      }
    }
  }
}

StarMap::~StarMap() {
  delete data;
}

StarMap* StarMap::create(std::istream& stream) {
  return new StarMap(stream);
}