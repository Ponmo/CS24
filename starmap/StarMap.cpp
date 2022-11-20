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
    std::string token;
    Star star;
    star.id = id++;
    int count = 0;
    while(std::getline(nLine, token, '\t')) {
      if (count == 0) {
        star.x = std::stof(token);
      }
      else if (count == 1) {
        star.y = std::stof(token);
      }
      else {
        star.z = std::stof(token);
      }
      count++;
    }
    data->push_back(star);
  }
  createKD(data, 0, 0, data->size() - 1);
}
void StarMap::createKD(std::vector<Star>* data, unsigned long depth, int index, int endex) { //Sort by Variance Helps with Disks 
  int med = (endex-index)/2 + index; 
  // auto m = data->begin() + med;
  if (depth % 3 == 2) {
    std::nth_element(data->begin() + index, data->begin() + med, data->begin() + endex + 1, &comparatorx);
  }
  else if (depth % 3 == 1) { 
    std::nth_element(data->begin() + index, data->begin() + med, data->begin() + endex + 1, &comparatory);
  }
  else {
    std::nth_element(data->begin() + index, data->begin() + med, data->begin() + endex + 1, &comparatorz);
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
  find_recurse(n, x, y, z, pq, 0, (data->size()-1)/2, 0, data->size() - 1, -1, -1, -1, -1);
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    nearest.insert(nearest.begin(), pq->top().star); //Optimize this by inserting backwards
    pq->pop();
  }
  delete pq;
  return nearest;
}
void StarMap::find_recurse(size_t n, float x, float y, float z, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex) {
  // std::cout << "1 ";
  if (pq->size() < n) {
    starDistance obj = {(data->at(curr).x - x)*(data->at(curr).x - x) + (data->at(curr).y - y)*(data->at(curr).y - y) + (data->at(curr).z - z)*(data->at(curr).z - z), data->at(curr)};
    pq->push(obj);
  }
  else {
    float distance = (data->at(curr).x - x)*(data->at(curr).x - x) + (data->at(curr).y - y)*(data->at(curr).y - y) + (data->at(curr).z - z)*(data->at(curr).z - z);
    if(pq->top().distance > distance) {
      pq->pop();
      starDistance obj = {distance, data->at(curr)};
      pq->push(obj);
    }
  }
  int leftChild = index+(curr-1-index)/2;
  int rightChild = curr+1+(endex-curr-1)/2;
  
  if (depth % 3 == 2) {
    if(data->at(curr).x >= x && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
    }
  }
  else if (depth % 3 == 1) {
    if(data->at(curr).y >= y && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
    }
  }
  else {
    if(data->at(curr).z >= z && leftChild >= index && leftChild < curr) {
      find_recurse(n ,x, y, z, pq, depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
    }
    else if (rightChild > curr && rightChild <= endex) {
      find_recurse(n ,x, y, z, pq, depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
    }
  }

  if(parex != -1) { 
    if((depth - 1) % 3 == 2) {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).x - x)) { //WHEN TWO THINGS LEFT, RIGHT CHILD ONLY NEEDS TO CHECK LEFT CHILD
        if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
          find_recurse(n ,x, y, z, pq, depth, oppex, parex+1, parexEndex, -1, -1, -1,-1);
        }
        else if(oppex >= parexIndex && oppex < parex) {  //curr >= parex
          find_recurse(n ,x, y, z, pq, depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
        }
      }
    }
    else if ((depth - 1) % 3 == 1) {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).y - y)) {
        if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
          find_recurse(n ,x, y, z, pq, depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
        }
        else if(oppex >= parexIndex && oppex < parex) {
          find_recurse(n ,x, y, z, pq, depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
        }
      }
    }
    else {
      if (sqrt(pq->top().distance) > std::abs(data->at(parex).z - z)) {
        if(oppex > parex && oppex <= parexEndex) {//curr <= parex && 
          find_recurse(n ,x, y, z, pq, depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
        }
        else if(oppex >= parexIndex && oppex < parex) { //curr >= parex && 
          find_recurse(n ,x, y, z, pq, depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
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