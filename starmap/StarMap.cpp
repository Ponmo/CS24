
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
  std::string line;
  int id = 1;
  std::string token;
  Star star;
  int count = 0;
  while (std::getline(stream, line)) {
    std::stringstream nLine(line);
    count = 0;
    star.id = id;
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
    data.push_back(star);
    id++;
  } //Approx Variance with randomly selected stars, setting beginning depth to that, 
  std::srand(time(0));
  Star A;
  float xAvg = 0;
  float yAvg = 0;
  float zAvg = 0;
  float xAvgSq = 0;
  float yAvgSq = 0;
  float zAvgSq = 0;
  for (int i = 0; i < 100; i++) {
    A = data.at(std::rand()%(data.size()));
    xAvg += A.x;
    yAvg += A.y;
    zAvg += A.z;
    xAvgSq += A.x*A.x;
    yAvgSq += A.y*A.y;
    zAvgSq += A.z*A.y;
  }
  xAvg = xAvg/100;
  yAvg = yAvg/100;
  zAvg = zAvg/100;
  xAvgSq = xAvgSq/100; //Maybe uniform z is just skewed  ok
  yAvgSq = yAvgSq/100; //yep i am not messing with this anymore though ???
  zAvgSq = zAvgSq/100;
  float xVar = std::abs(xAvgSq - xAvg*xAvg);
  float yVar = std::abs(yAvgSq - yAvg*yAvg);
  float zVar = std::abs(zAvgSq - zAvg*zAvg);
  // std::cout << xVar << " " << yVar << " " << " " << zVar << "\n";
  if(xVar >= yVar && xVar >= zVar) { //X is largest
    begDepth = 0;
  }
  else if (yVar >= xVar && yVar >= zVar) { //Y is largest
    begDepth = 1;
  }
  else { //z is largest 
    begDepth = 2;
  }
  createKD(begDepth, 0, data.size() - 1);
}
void StarMap::createKD(unsigned long depth, int index, int endex) { 
  if (endex - index > 200) {
    int med = (endex-index)/2 + index; 
    if (depth % 3 == 0) {
      std::nth_element(data.begin() + index, data.begin() + med, data.begin() + endex + 1, &comparatorx);
    }
    else if (depth % 3 == 1) { 
      std::nth_element(data.begin() + index, data.begin() + med, data.begin() + endex + 1, &comparatory);
    }
    else {
      std::nth_element(data.begin() + index, data.begin() + med, data.begin() + endex + 1, &comparatorz);
    }
    if(med-1-index >= 1) { 
      createKD(depth + 1, index, med-1); 
    }
    if(endex-med-1 >= 1) {
      createKD(depth + 1, med + 1, endex);
    }
  }
}
std::vector<Star> StarMap::find(size_t vn, float vx, float vy, float vz) {
  n = vn;
  x = vx;
  y = vy;
  z = vz;
  pq = std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>();
  find_recurse(begDepth, (data.size()-1)/2, 0, data.size() - 1, -1, -1, -1, -1);
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    nearest.insert(nearest.begin(), pq.top().star); //Optimize this by inserting backwards
    pq.pop();
  }
  return nearest;
}
//Store current best squared distance at top
void StarMap::find_recurse(unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex) { //Remove extraneous parameters?
  if(endex - index <= 200) {
    for (int i = index; i <= endex; i++) {
      if (pq.size() < n) {
        starDistance obj = {(data.at(i).x - x)*(data.at(i).x - x) + (data.at(i).y - y)*(data.at(i).y - y) + (data.at(i).z - z)*(data.at(i).z - z), data.at(i)};
        pq.push(obj);
      }
      else {
        float distance = (data.at(i).x - x)*(data.at(i).x - x) + (data.at(i).y - y)*(data.at(i).y - y) + (data.at(i).z - z)*(data.at(i).z - z);
        if(pq.top().distance > distance) {
          pq.pop();
          starDistance obj = {distance, data.at(i)};
          pq.push(obj);
        }
      }
    }
    if(parex != -1) { 
    if((depth - 1) % 3 == 0) {
      if (sqrt(pq.top().distance) > std::abs(data.at(parex).x - x)) { //WHEN TWO THINGS LEFT, RIGHT CHILD ONLY NEEDS TO CHECK LEFT CHILD
                if(oppex > parex) { //curr <= parex && 
                  find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1,-1);
                }
                else {  //curr >= parex
                  find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
                }
              }
    }
    else if ((depth - 1) % 3 == 1) {
      if (sqrt(pq.top().distance) > std::abs(data.at(parex).y - y)) {
                if(oppex > parex) { //curr <= parex && 
                  find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
                }
                else {
                  find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
                }
              }
    }
    else {
      if (sqrt(pq.top().distance) > std::abs(data.at(parex).z - z)) {
        if(oppex > parex) {//curr <= parex &&
          find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
        }
        else { //curr >= parex && 
          find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
        }
      }
    }
  }
  }
  else {
          if (pq.size() < n) {
            starDistance obj = {(data.at(curr).x - x)*(data.at(curr).x - x) + (data.at(curr).y - y)*(data.at(curr).y - y) + (data.at(curr).z - z)*(data.at(curr).z - z), data.at(curr)};
            pq.push(obj);
          }
          else {
            float distance = (data.at(curr).x - x)*(data.at(curr).x - x) + (data.at(curr).y - y)*(data.at(curr).y - y) + (data.at(curr).z - z)*(data.at(curr).z - z);
            if(pq.top().distance > distance) {
              pq.pop();
              starDistance obj = {distance, data.at(curr)};
              pq.push(obj);
            }
          }
          int leftChild = index+(curr-1-index)/2;
          int rightChild = curr+1+(endex-curr-1)/2;
          if (depth % 3 == 0) {
            if(data.at(curr).x >= x && leftChild >= index && leftChild < curr) {
              find_recurse(depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
            }
            else if (rightChild > curr && rightChild <= endex) {
              find_recurse(depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
            }
            if(parex != -1) {
              if (sqrt(pq.top().distance) > std::abs(data.at(parex).z - z)) {
                if(oppex > parex) {//curr <= parex &&
                  find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
                }
                else { //curr >= parex && 
                  find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
                }
              }
            }
          }
          else if (depth % 3 == 1) {
            if(data.at(curr).y >= y && leftChild >= index && leftChild < curr) {
              find_recurse(depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
            }
            else if (rightChild > curr && rightChild <= endex) {
              find_recurse(depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
            }
            if(parex != -1) { 
              if (sqrt(pq.top().distance) > std::abs(data.at(parex).x - x)) { //WHEN TWO THINGS LEFT, RIGHT CHILD ONLY NEEDS TO CHECK LEFT CHILD
                if(oppex > parex) { //curr <= parex && 
                  find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1,-1);
                }
                else {  //curr >= parex
                  find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
                }
              }
            }
          }
          else {
            if(data.at(curr).z >= z && leftChild >= index && leftChild < curr) {
              find_recurse(depth + 1, leftChild, index, curr - 1, curr, rightChild, endex, index);
            }
            else if (rightChild > curr && rightChild <= endex) {
              find_recurse(depth + 1, rightChild, curr + 1, endex, curr, leftChild, endex, index);
            }
            if(parex != -1) {
              if (sqrt(pq.top().distance) > std::abs(data.at(parex).y - y)) {
                if(oppex > parex) { //curr <= parex && 
                  find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
                }
                else {
                  find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
                }
              }
            }
          }
  }
}

StarMap::~StarMap() {
}

StarMap* StarMap::create(std::istream& stream) {
  return new StarMap(stream);
}