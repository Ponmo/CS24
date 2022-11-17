#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <iterator>
#include <fstream>

//Build a KD tree in place in a vector kevin says, most optimized way so far
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
  if (depth == 0 || depth % 3 == 0) {
    std::sort(list.begin(), list.end(), &comparatorx);
  }
  else if (depth % 3 == 1) { 
    std::sort(list.begin(), list.end(), &comparatory);
  }
  else {
    std::sort(list.begin(), list.end(), &comparatorz);
  }
  size_t half_size = list.size() / 2;
  Star median = list[half_size];
  Node* med = new Node;
  med->star = median;

  if (list.size() > 2) {
    std::vector<Star> lesser(list.begin(), list.begin() + half_size);
    std::vector<Star> greater(list.begin() + half_size + 1, list.end());

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
    std::string token;
    Star star;
    star.id = id;
    int count = 0;
    while(std::getline(nLine, token, '\t')) {
      // std::cout << token;
      if (count == 0) {
        // std::cout << '1';
        star.x = std::stof(token);
      }
      if (count == 1) {
        // std::cout << '2';
        star.y = std::stof(token);
      }
      if (count == 2) {
        // std::cout << '3';
        star.z = std::stof(token);
      }
      count++;
    }
    list.push_back(star);
    id++;
  }
  root = recurse(list, 0);
}

void StarMap::find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth) {
  //First, just push everything it goes through onto the PQ
  float distance = (curr->star.x - x)*(curr->star.x - x) + (curr->star.z - z)*(curr->star.z - z) + (curr->star.y - y)*(curr->star.y - y); //Distance to spaceship
  if(pq->size() >= n && pq->top().distance > distance) {
    pq->pop();
    starDistance obj = {distance, curr};
    pq->push(obj);
  }
  else if (pq->size() < n) {
    starDistance obj = {distance, curr};
    pq->push(obj);
  }  
  //Loops recursively through the KD tree until it finds the closest star. 
  if (depth == 0 || depth % 3 == 0) { //curr -> star.x >= x
    if(curr -> star.x >= x && curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
    else if (curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
    }
  }
  else if (depth % 3 == 1) {//y
    if(curr -> star.y >= y && curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
    else if (curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
    }
  }
  else { //z
    if(curr -> star.z >= z && curr -> greater != nullptr) {
      find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
    }
    else if (curr -> lesser != nullptr) {
      find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
    }
  }
  //So now, we have a pq of the closest stars that we ran through, we want to check the other dimenseion

  if(parent != nullptr) { //We are not at the root
    float tDistance = pq->top().distance;
    //float pDistance = (parent->star.x - x)*(parent->star.x - x) + (parent->star.z - z)*(parent->star.z - z) + (parent->star.y - y)*(parent->star.y - y);
    if(depth % 3 == 0) {
      if (tDistance > (parent->star.x - x)) {
        if(curr == parent -> lesser) {
          find_recurse(n ,x, y, z, parent->greater, curr, pq, depth);
        }
        else if(curr == parent -> greater) {
          find_recurse(n ,x, y, z, parent->lesser, curr, pq, depth);
        }
      }
    }
    else if (depth % 3 == 1) {
      if (tDistance > (parent->star.y - y)) {
        if(curr == parent -> lesser) {
          find_recurse(n ,x, y, z, parent->greater, curr, pq, depth);
        }
        else if(curr == parent -> greater) {
          find_recurse(n ,x, y, z, parent->lesser, curr, pq, depth);
        }
      }
    }
    else {
      if (tDistance > (parent->star.z - z)) {
        if(curr == parent -> lesser) {
          find_recurse(n ,x, y, z, parent->greater, curr, pq, depth);
        }
        else if(curr == parent -> greater) {
          find_recurse(n ,x, y, z, parent->lesser, curr, pq, depth);
        }
      }
    }
  }
  else { //We are at the root

  }
}



std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {
  std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq = new std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>;
  find_recurse(n, x, y, z, root, nullptr, pq, 0);
  std::vector<Star> nearest;
  for(size_t i = 0; i < n; i++) {
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

//So we split the data up into two halves. Find the two medium value of the axis and recurse on those. Only pass in the list on that side of the node. What about node on the same divison..? Just pick a random side (lesser) optimize later based on count

//https://yasenh.github.io/post/kd-tree/

//For step 2, another way to choose the cutting dimension is to calculate the variance of all values in each dimension and the largest one will be chosen as the cutting dimension. The larger variance means data is more scatter on the axis, so that we can split data better in this way.
//Multithreading?





// std::vector<Star> StarMap::find(size_t n, float x, float y, float z) { //find function
  // std::priority_queue<starDistance, std::vector<starDistance>, CompareAge> pq;
//   for(Star star : *data) {
//     // float distance = pow(star.x - x, 2) + pow(star.y - y, 2) + pow(star.z - z, 2);
//     float distance = (star.x - x)*(star.x - x) + (star.z - z)*(star.z - z) + (star.y - y)*(star.y - y);
//     starDistance curr = {distance, star.id};
    // if(pq.size() >= n && pq.top().distance > distance) {
    //   // std::cout << pq.top().id;
    //   pq.pop();
    //   pq.push(curr);
    // }
    // else if (pq.size() < n) {
    //   pq.push(curr);
    // }
//   }
//   std::vector<Star> nearest;
  // for(size_t i = 0; i < n; i++) { //print backwards
  //   // std::cout << pq.top().id;
  //   // std::cout << " ";
  //   nearest.insert(nearest.begin(), data->at(pq.top().id - 1));
  //   // nearest.push_back(data->at(pq.top().id - 1));
  //   pq.pop();
  // }
//   return nearest;
// };



// template <class T, class Container = std::vector<T>,  class Compare = std::less<typename Container::value_type> > class priority_queue;



//Find if it is a disk or whatever

// StarMap::StarMap(std::istream& stream) {
//   data = new std::vector<Star>; 
//   std::string line;
//   int id = 1;
//   while (std::getline(stream, line)) {
//     std::stringstream nLine(line);
//     std::string token;
//     Star star;
//     star.id = id;
//     int count = 0;
//     while(std::getline(nLine, token, '\t')) {
//       // std::cout << token;
//       if (count == 0) {
//         // std::cout << '1';
//         star.x = std::stof(token);
//       }
//       if (count == 1) {
//         // std::cout << '2';
//         star.y = std::stof(token);
//       }
//       if (count == 2) {
//         // std::cout << '3';
//         star.z = std::stof(token);
//       }
//       count++;
//     }
//     data->push_back(star);
//     id++;
//   }
// }