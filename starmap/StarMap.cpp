#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <time.h>

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
  // std::srand(time(0));
  // Star A = data.at(std::rand()%(data.size()));
  // Star B = data.at(std::rand()%(data.size()));
  // Star C = data.at(std::rand()%(data.size()));
  // Star D = data.at(std::rand()%(data.size()));
  // Star E = data.at(std::rand()%(data.size()));
  // Star F = data.at(std::rand()%(data.size()));
  // Star G = data.at(std::rand()%(data.size()));
  // Star H = data.at(std::rand()%(data.size()));
  // Star I = data.at(std::rand()%(data.size()));
  // Star J = data.at(std::rand()%(data.size()));
  // Star K = data.at(std::rand()%(data.size()));
  // Star L = data.at(std::rand()%(data.size()));
  // float xAvg = (A.x+B.x+C.x+D.x+E.x+F.x+G.x+H.x+I.x+J.x+K.x+L.x)/12;
  // float yAvg = (A.y+B.y+C.y+D.y+E.y+F.y+G.y+H.y+I.y+J.y+K.y+L.y)/12;
  // float zAvg = (A.z+B.z+C.z+D.z+E.z+F.z+G.z+H.z+I.z+J.z+K.z+L.z)/12;
  // float xAvgSq = (A.x*A.x+B.x*B.x+C.x*C.x+D.x*D.x+E.x*E.x+F.x*F.x+G.x*G.x+H.x*H.x+I.x*I.x+J.x*J.x+K.x*K.x+L.x*L.x)/12;
  // float yAvgSq = (A.y*A.y+B.y*B.y+C.y*C.y+D.y*D.y+E.y*E.y+F.y*F.y+G.y*G.y+H.y*H.y+I.y*I.y+J.y*J.y+K.y*K.y+L.y*L.y)/12;
  // float zAvgSq = (A.z*A.z+B.z*B.z+C.z*C.z+D.z*D.z+E.z*E.z+F.z*F.z+G.z*G.z+H.z*H.z+I.z*I.z+J.z*J.z+K.z*K.z+L.z*L.z)/12;
  // float xVar = std::abs(xAvgSq - xAvg*xAvg);
  // float yVar = std::abs(yAvgSq - yAvg*yAvg);
  // float zVar = std::abs(zAvgSq - zAvg*zAvg);
  // std::cout << xVar << " " << yVar << " " << zVar << "\n";
  // if(xVar >= yVar && xVar >= zVar) { //X is largest
  //   begDepth = 0;
  // }
  // else if (yVar >= xVar && yVar >= zVar) { //Y is largest
  //   begDepth = 1;
  // }
  // else { //z is largest 
  //   begDepth = 2;
  // }
  createKD(0, 0, data.size() - 1);
}
void StarMap::createKD(unsigned long depth, int index, int endex) { 
  if (endex - index > 400) {
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
  find_recurse(0, (data.size()-1)/2, 0, data.size() - 1, -1, -1, -1, -1);
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    nearest.insert(nearest.begin(), pq.top().star); //Optimize this by inserting backwards
    pq.pop();
  }
  return nearest;
}
//Store current best squared distance at top
void StarMap::find_recurse(unsigned long depth, int curr, int index, int endex, int parex, int oppex, int parexEndex, int parexIndex) { //Remove extraneous parameters?
  if(endex - index <= 400) {
    float distance;
    for (int i = index; i <= endex; i++) {
      distance = (data.at(i).x - x)*(data.at(i).x - x) + (data.at(i).y - y)*(data.at(i).y - y) + (data.at(i).z - z)*(data.at(i).z - z);
      if (pq.size() < n) {
        starDistance obj = {distance, data.at(i)};
        pq.push(obj);
        best = sqrt(pq.top().distance);
      }
      else if(pq.top().distance > distance) {
        pq.pop();
        starDistance obj = {distance, data.at(i)};
        pq.push(obj);
        best = sqrt(pq.top().distance);
      }
    }
    if(parex != -1) { 
    if((depth - 1) % 3 == 0) {
      if (best > std::abs(data.at(parex).x - x)) { //WHEN TWO THINGS LEFT, RIGHT CHILD ONLY NEEDS TO CHECK LEFT CHILD
        if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
          find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1,-1);
        }
        else if(oppex >= parexIndex && oppex < parex) {  //curr >= parex
          find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
        }
      }
    }
    else if ((depth - 1) % 3 == 1) {
      if (best > std::abs(data.at(parex).y - y)) {
        if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
          find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
        }
        else if(oppex >= parexIndex && oppex < parex) {
          find_recurse(depth, oppex, parexIndex, parex-1, -1, -1, -1, -1);
        }
      }
    }
    else {
      if (best > std::abs(data.at(parex).z - z)) {
        if(oppex > parex && oppex <= parexEndex) {//curr <= parex &&
          find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
        }
        else if(oppex >= parexIndex && oppex < parex) { //curr >= parex && 
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
      best = sqrt(pq.top().distance);
    }
    else {
      float distance = (data.at(curr).x - x)*(data.at(curr).x - x) + (data.at(curr).y - y)*(data.at(curr).y - y) + (data.at(curr).z - z)*(data.at(curr).z - z);
      if(pq.top().distance > distance) {
        pq.pop();
        starDistance obj = {distance, data.at(curr)};
        pq.push(obj);
        best = sqrt(pq.top().distance);
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
        if (best > std::abs(data.at(parex).z - z)) {
          if(oppex > parex && oppex <= parexEndex) {//curr <= parex &&
            find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
          }
          else if(oppex >= parexIndex && oppex < parex) { //curr >= parex && 
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
        if (best > std::abs(data.at(parex).x - x)) { //WHEN TWO THINGS LEFT, RIGHT CHILD ONLY NEEDS TO CHECK LEFT CHILD
          if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
            find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1,-1);
          }
          else if(oppex >= parexIndex && oppex < parex) {  //curr >= parex
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
        if (best > std::abs(data.at(parex).y - y)) {
          if(oppex > parex && oppex <= parexEndex) { //curr <= parex && 
            find_recurse(depth, oppex, parex+1, parexEndex, -1, -1, -1, -1);
          }
          else if(oppex >= parexIndex && oppex < parex) {
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