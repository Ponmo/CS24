#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
//Build a KD tree in place in a vector professor kevin says, most optimized way so far
// std::vector<Star>& theFinishedVector as next parameter

bool comparatorx(const Star& lhs, const Star& rhs) {
   return lhs.x < rhs.x;
}
bool comparatory(const Star& lhs, const Star& rhs) {
   return lhs.y < rhs.y;
}
bool comparatorz(const Star& lhs, const Star& rhs) {
   return lhs.z < rhs.z;
}

//Vector in place? So swap curr and its next children into the first parts of the array on the heap, and then always just sort from count (currently number of things added) to the end of the array, half that

Node* StarMap::recurse(std::vector<Star> list, unsigned long depth = 0) {
  auto m = list.begin() + (list.size() - 1)/2;
  if (depth % 3 == 0) {
    std::nth_element(list.begin(), m, list.end(), &comparatorx);
    // std::sort(list.begin(), list.end(), &comparatorx);
  }
  else if (depth % 3 == 1) { 
    // std::sort(list.begin(), list.end(), &comparatory);
    std::nth_element(list.begin(), m, list.end(), &comparatory);
  }
  else {
    std::nth_element(list.begin(), m, list.end(), &comparatorz);
    // std::sort(list.begin(), list.end(), &comparatorz); 
  }
  Star median = list[(list.size() - 1)/2];
  Node* med = new Node;
  med->star = median;

  if (list.size() > 2) {
    std::vector<Star> lesser(list.begin(), m);
    std::vector<Star> greater(m + 1, list.end());

    med->greater = recurse(greater, depth + 1);
    med->lesser = recurse(lesser, depth + 1);
  }
  else if (list.size() == 2) {
    Node* great = new Node; 
    great->star = list[1];
    med -> greater = great;
  }
  return med;
}

StarMap::StarMap(std::istream& stream) {
  std::vector<Star> list; 
  std::string line;
  int id = 1;
  while (std::getline(stream, line)) {
    std::stringstream nLine(line);
    float x, y, z;
    nLine >> x >> y >> z;
    Star star = {id++, x, y, z};
    list.push_back(star);
    // data->push_back(Star());
    // nLine >> data->back().x >> data->back().y >> data->back().z;
  }
  root = recurse(list, 0);
  // printRecursion(root);
}

void StarMap::find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth) {
  //First, just push everything it goes through onto the PQ
  if (pq->size() < n) {
    starDistance obj = {(curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z), curr};
    pq->push(obj);
  }  
  else if (pq->top().distance > (curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z)) {
      pq->pop();
      starDistance obj = {(curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z), curr};
      pq->push(obj);
  }
  //Loops recursively through the KD tree until it finds the closest star. 
  if (depth % 3 == 0) { //curr -> star.x >= x
    if(curr -> star.x >= x && curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1); //GOT RID OF >= FOR ALL OF THEMWIOHFIOWEFHIOEWHFIOWEHIFOEHWIFHIOEWFHWEIOFHIOEWHFIOEWHFIOHEIO
    }
    else if (curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
  }
  else if (depth % 3 == 1) {//y
    if(curr -> star.y >= y && curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
    }
    else if (curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
  }
  else { //z
    if(curr -> star.z >= z && curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
    }
    else if (curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
  }
  //So now, we have a pq of the closest stars that we ran through, we want to check the other dimenseion

  if(parent != nullptr) { //We are not at the root
    //float pDistance = (parent->star.x - x)*(parent->star.x - x) + (parent->star.z - z)*(parent->star.z - z) + (parent->star.y - y)*(parent->star.y - y);
    if((depth - 1) % 3 == 0) {
      float tDistance = sqrt(pq->top().distance);
      if (tDistance > std::abs(parent->star.x - x)) {
        if(curr == parent -> lesser && parent -> greater != nullptr) {
          find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth); //I changed curr to nullptr for each of these
        }
        else if(curr == parent -> greater && parent -> lesser != nullptr) {
          find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
        }
      }
    }
    
    else if ((depth - 1) % 3 == 1) {
      float tDistance = sqrt(pq->top().distance);
      if (tDistance > std::abs(parent->star.y - y)) {
        if(curr == parent -> lesser && parent -> greater != nullptr) {
          find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth);
        }
        else if(curr == parent -> greater && parent -> lesser != nullptr) {
          find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
        }
      }
    }
    else {
      float tDistance = sqrt(pq->top().distance);
      if (tDistance > std::abs(parent->star.z - z)) {
        if(curr == parent -> lesser && parent -> greater != nullptr) {
          find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth);
        }
        else if(curr == parent -> greater && parent -> lesser != nullptr) {
          find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
        }
      }
    }
  }
  // std::cout << sqrt(pq->top().distance);
  // std:: cout << "\n";
}

//In place vector 

std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {
  std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq = new std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>;
  find_recurse(n, x, y, z, root, nullptr, pq, 0);
  // std::cout << root->star.z;
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
    // std::cout << pq->top().distance;
    // std::cout << "\n";
    nearest.insert(nearest.begin(), pq->top().star->star);
    pq->pop();
  }
  delete pq;
  return nearest;
}

void deleteRecursion(Node* curr) { 
    if (curr -> greater) {
        deleteRecursion(curr -> greater);
    }
    if (curr -> lesser) {
        deleteRecursion(curr -> lesser);
    }
    delete curr;
    return;
};
StarMap::~StarMap() {
  if(root) {
    deleteRecursion(root);
  }
}

StarMap* StarMap::create(std::istream& stream) {
  return new StarMap(stream);
}

