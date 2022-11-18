#include "StarMap.h"
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <iterator>
#include <fstream>
#include <algorithm>

void printRecursion(Node* curr) { 
    if (curr -> greater) {
        printRecursion(curr -> greater);
    }
    if (curr -> lesser) {
        printRecursion(curr -> lesser);
    }
    std::cout << curr->star.id;
    std::cout << " ";
    return;
};

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
  if (depth == 0 || depth % 3 == 0) {
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



  // std::vector<Star> list; 
  // std::string line;
  // int id = 1;
  // while (std::getline(stream, line)) {
  //   std::stringstream nLine(line);
  //   std::string token;
  //   Star star;
  //   star.id = id;
  //   int count = 0;
  //   while(std::getline(nLine, token, '\t')) {
  //     // std::cout << token;
  //     if (count == 0) {
  //       // std::cout << '1';
  //       star.x = std::stof(token);
  //     }
  //     if (count == 1) {
  //       // std::cout << '2';
  //       star.y = std::stof(token);
  //     }
  //     if (count == 2) {
  //       star.z = std::stof(token);
  //     }
  //     count++;
  //   }
  //   list.push_back(star);
  //   id++;
  // }
  // root = recurse(list, 0);
  // printRecursion(root);
}

void StarMap::find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth) {
  //First, just push everything it goes through onto the PQ
  float distance = sqrt((curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z)); //Distance to spaceship
  if(pq->size() < n) {
    starDistance obj = {distance, curr};
    pq->push(obj);
  }
  else if(pq->top().distance > distance) {
    pq->pop();
    starDistance obj = {distance, curr};
    pq->push(obj);
  }
  //Loops recursively through the KD tree until it finds the closest star. 
  if (depth == 0 || depth % 3 == 0) { //curr -> star.x >= x
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
    float tDistance = pq->top().distance;
    if((depth - 1) % 3 == 0) {
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

//multithreading
//https://yasenh.github.io/post/kd-tree/











// #include "StarMap.h"
// #include <sstream>
// #include <iostream>
// #include <map>
// #include <set>
// #include <stack>
// #include <cmath>
// #include <iterator>
// #include <fstream>
// #include <algorithm>

// void printRecursion(Node* curr) { 
//     if (curr -> greater) {
//         printRecursion(curr -> greater);
//     }
//     if (curr -> lesser) {
//         printRecursion(curr -> lesser);
//     }
//     std::cout << curr->star.id;
//     std::cout << " ";
//     return;
// };

// //Build a KD tree in place in a vector professor kevin says, most optimized way so far
// // std::vector<Star>& theFinishedVector as next parameter

// bool comparatorx(const Star& lhs, const Star& rhs) {
//    return lhs.x < rhs.x;
// }
// bool comparatory(const Star& lhs, const Star& rhs) {
//    return lhs.y < rhs.y;
// }
// bool comparatorz(const Star& lhs, const Star& rhs) {
//    return lhs.z < rhs.z;
// }

// //Vector in place? So swap curr and its next children into the first parts of the array on the heap, and then always just sort from count (currently number of things added) to the end of the array, half that

// // void StarMap::recurse(std::vector<Star>* data, unsigned long depth = 0) {
// //   auto m = data->begin() + (data->size() - 1)/2;
// //   if (depth == 0 || depth % 3 == 0) {
// //     std::nth_element(data->begin() + index, m, data->end(), &comparatorx);
// //   }
// //   else if (depth % 3 == 1) { 
// //     std::nth_element(data->begin() + index, m, data->end(), &comparatory);
// //   }
// //   else {
// //     std::nth_element(data->begin() + index, m, data->end(), &comparatorz);
// //   } 
// //   //nth = median. The median is the top. HOLD ONOEOEOPJFPO
// //   //[345,2,23,235345,3233,2435,235,32435,235,4,235,56,54,4235]
// //   //[345, 2, 1, 5, 2, 6, 7]
// //   //[345, 123, 2, 2, 2, 2, 2, 2]

// //   Star median = list[(list.size() - 1)/2];
// //   Node* med = new Node;
// //   med->star = median;

// //   if (list.size() > 2) {
// //     std::vector<Star> lesser(list.begin(), m);
// //     std::vector<Star> greater(m + 1, list.end());

// //     med->greater = recurse(greater, depth + 1);
// //     med->lesser = recurse(lesser, depth + 1);
// //   }
// //   else if (list.size() == 2) {
// //     Node* great = new Node; 
// //     great->star = list[1];
// //     med -> greater = great;
// //   }
// //   return med;
// // }
// // // unsigned long depth, size_t index, size_t start, size_t end
// // //Data Unsorted, Depth = 0, Index = 0, Start = 0, end = size of vector
// // void StarMap::recurse(std::vector<Star>* data) {
  
// //   std::vector<size_t> indexes;
// //   while(index < data->size()) {
// //     auto medianValue = //Get median index starting from its index in indexes to the next index in indexes

// //     // [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20]
// //     // [0 1 1 2 2 2 2 0 0 0 0  0  0  0  0  1  1  1  1  1  1
// //     // [1, 2, 4, 8, 16]
// //     if (index == 0 || depth % 3 == 0) { //Calculate Depth Based on Index see chart above
// //       std::nth_element(data->begin() + start, m, end, &comparatorx); //Sort from start of its index in indexes to the next index in indexes and get m 
// //     }
// //     else if (depth % 3 == 1) { //Calculate Depth Based on Index see chart above
// //       std::nth_element(data->begin() + start, m, end, &comparatory);
// //     }
// //     else {
// //       std::nth_element(data->begin() + start, m, end, &comparatorz);
// //     } 

// //     index++;  //swap the next index now with m in a specified range
// //   }
// //   //Sort by x, y or z, from given start to given end
// //   auto m = data->begin() + (data->size() - 1)/2;
// //   if (depth == 0 || depth % 3 == 0) {
// //     std::nth_element(data->begin() + start, m, end, &comparatorx);
// //   }
// //   else if (depth % 3 == 1) { 
// //     std::nth_element(data->begin() + start, m, end, &comparatory);
// //   }
// //   else {
// //     std::nth_element(data->begin() + start, m, end, &comparatorz);
// //   } 
// //   //Swap index with 
// //   //call recurse with index++
// //   //[A, less X, more X]
// //   //[A, B, less Y, more Y, more X]
// //   //[A, B, C, less Y, more Y, less Y, more Y]
// //   //[A, B, C, D, less Z, more Z, more Y, less Y, more Y]
// //   //[A, B, C, D, E, less Z, more Z, less Z, more Z, less Y, more Y]
// //   //[A, B, C, D, E, F, less Z, more Z, less Z,more Z, less Z, more Z, more Y]
// //   //[A, B, C, D, E, F, G, less Z, more Z, less Z, more Z, less Z, more Z, less Z, more Z]
// //   //[A, B, C, D, E, F, G, H, less X, more X, more Z, less Z, more Z, less Z, more Z, less Z, more Z]
// //   //[A, B, C, D, E, F, G, H, I, less X, more X, more Z, less Z, more Z, less Z, more Z, less Z, more Z]


// //   recurse(data, depth + 1, index++, data->begin() + index + start, end of half the sorted array);
  
// //   if (list.size() > 2) {
// //     std::vector<Star> lesser(list.begin(), m);
// //     std::vector<Star> greater(m + 1, list.end());

// //     med->greater = recurse(greater, depth + 1);
// //     med->lesser = recurse(lesser, depth + 1);
// //   }
// //   else if (list.size() == 2) {
// //     Node* great = new Node; 
// //     great->star = list[1];
// //     med -> greater = great;
// //   }
// //   return med;
// // }
// // StarMap::StarMap(std::istream& stream) {
// //   data = new std::vector<Star>[5000];
// //   //this should be data then?
// //   std::string line;
// //   unsigned long id = 1;
// //   while (std::getline(stream, line)) {
// //     std::stringstream nLine(line);
// //     float x, y, z;
// //     nLine >> x >> y >> z;
// //     Star star = {id++, x, y, z};
// //     data->push_back(star);
// //     // data->push_back(Star());
// //     // nLine >> data->back().x >> data->back().y >> data->back().z;
// //   }
// //   recurse(data, 0, 0);
// //   // root = recurse(list, 0);
// //   // maybe.............. yYES
// //   // printRecursion(root);yes now recursion to build it
// // }



// Node* StarMap::recurse(std::vector<Star> list, unsigned long depth = 0) {
//   auto m = list.begin() + (list.size() - 1)/2;
//   if (depth == 0 || depth % 3 == 0) {
//     std::nth_element(list.begin(), m, list.end(), &comparatorx);
//     // std::sort(list.begin(), list.end(), &comparatorx);
//   }
//   else if (depth % 3 == 1) { 
//     // std::sort(list.begin(), list.end(), &comparatory);
//     std::nth_element(list.begin(), m, list.end(), &comparatory);
//   }
//   else {
//     std::nth_element(list.begin(), m, list.end(), &comparatorz);
//     // std::sort(list.begin(), list.end(), &comparatorz); 
//   }
//   Star median = list[(list.size() - 1)/2];
//   Node* med = new Node;
//   med->star = median;

//   if (list.size() > 2) {
//     std::vector<Star> lesser(list.begin(), m);
//     std::vector<Star> greater(m + 1, list.end());

//     med->greater = recurse(greater, depth + 1);
//     med->lesser = recurse(lesser, depth + 1);
//   }
//   else if (list.size() == 2) {
//     Node* great = new Node; 
//     great->star = list[1];
//     med -> greater = great;
//   }
//   return med;
// }

// StarMap::StarMap(std::istream& stream) {
//   // std::vector<Star> list; 
//   // std::string line;
//   // unsigned long id = 1;
//   // while (std::getline(stream, line)) {
//   //   std::stringstream nLine(line);
//   //   float x, y, z;
//   //   nLine >> x >> y >> z;
//   //   Star star = {id++, x, y, z};
//   //   list.push_back(star);
//   //   // data->push_back(Star());
//   //   // nLine >> data->back().x >> data->back().y >> data->back().z;
//   // }
//   // root = recurse(list, 0);


//   std::vector<Star> list; 
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
//         star.z = std::stof(token);
//       }
//       count++;
//     }
//     list.push_back(star);
//     id++;
//   }
//   root = recurse(list, 0);
//   // printRecursion(root);
// }

// void StarMap::find_recurse(size_t n, float x, float y, float z, Node* curr, Node* parent, std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq, unsigned long depth) {
//   //First, just push everything it goes through onto the PQ
//   float distance = sqrt((curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z));
//   /////float distance = (curr->star.x - x)*(curr->star.x - x) + (curr->star.y - y)*(curr->star.y - y) + (curr->star.z - z)*(curr->star.z - z); //Distance to spaceship
//   if (pq->size() < n) {
//     pq->pop();
//     starDistance obj = {distance, curr};
//     pq->push(obj);
//   }
//   else if (pq->top().distance > distance) {
//     starDistance obj = {distance, curr};
//     pq->push(obj);
//   }
//   // if(pq->size() >= n && pq->top().distance > distance) {
//   //   pq->pop();
//   //   starDistance obj = {distance, curr};
//   //   pq->push(obj);
//   // }
//   // else if (pq->size() < n) {
//   //   starDistance obj = {distance, curr};
//   //   pq->push(obj);
//   // }  
//   //Loops recursively through the KD tree until it finds the closest star. 
//   if (depth == 0 || depth % 3 == 0) { //curr -> star.x >= x
//     if(curr -> star.x >= x && curr -> lesser != nullptr) {
//       find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1); //GOT RID OF >= FOR ALL OF THEMWIOHFIOWEFHIOEWHFIOWEHIFOEHWIFHIOEWFHWEIOFHIOEWHFIOEWHFIOHEIO
//     }
//     else if (curr -> greater != nullptr) {
//       find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
//     }
//   }
//   else if (depth % 3 == 1) {//y
//     if(curr -> star.y >= y && curr -> lesser != nullptr) {
//       find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
//     }
//     else if (curr -> greater != nullptr) {
//       find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
//     }
//   }
//   else { //z
//     if(curr -> star.z >= z && curr -> lesser != nullptr) {
//       find_recurse(n ,x, y, z, curr->lesser, curr, pq, depth + 1);
//     }
//     else if (curr -> greater != nullptr) {
//       find_recurse(n ,x, y, z, curr->greater, curr, pq, depth + 1);
//     }
//   }
//   //So now, we have a pq of the closest stars that we ran through, we want to check the other dimenseion
//   if(depth != 0) {
//   ////if(parent != nullptr) { //We are not at the root
//     //float pDistance = (parent->star.x - x)*(parent->star.x - x) + (parent->star.z - z)*(parent->star.z - z) + (parent->star.y - y)*(parent->star.y - y);
//     float tDistance = pq->top().distance;
//     if((depth - 1) % 3 == 0) {
//       ////float tDistance = sqrt(pq->top().distance);
//       if (tDistance > std::abs(parent->star.x - x)) {
//         if(curr == parent -> lesser && parent -> greater != nullptr) {
//           find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth); //I changed curr to nullptr for each of these
//         }
//         else if(curr == parent -> greater && parent -> lesser != nullptr) {
//           find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
//         }
//       }
//     }
//     else if ((depth - 1) % 3 == 1) {
//       ////float tDistance = sqrt(pq->top().distance);
//       if (tDistance > std::abs(parent->star.y - y)) {
//         if(curr == parent -> lesser && parent -> greater != nullptr) {
//           find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth);
//         }
//         else if(curr == parent -> greater && parent -> lesser != nullptr) {
//           find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
//         }
//       }
//     }
//     else {
//       ////float tDistance = sqrt(pq->top().distance);
//       if (tDistance > std::abs(parent->star.z - z)) {
//         if(curr == parent -> lesser && parent -> greater != nullptr) {
//           find_recurse(n ,x, y, z, parent->greater, nullptr, pq, depth);
//         }
//         else if(curr == parent -> greater && parent -> lesser != nullptr) {
//           find_recurse(n ,x, y, z, parent->lesser, nullptr, pq, depth);
//         }
//       }
//     }
//   }
//   // std::cout << sqrt(pq->top().distance);
//   // std:: cout << "\n";
// }

// //In place vector 

// std::vector<Star> StarMap::find(size_t n, float x, float y, float z) {
//   std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>* pq = new std::priority_queue<starDistance, std::vector<starDistance>, CompareAge>;
//   find_recurse(n, x, y, z, root, nullptr, pq, 0);
//   // std::cout << root->star.z;
//   std::vector<Star> nearest;
//   for(size_t i = 0; i < n; i++) {
//     // std::cout << pq->top().distance;
//     // std::cout << "\n";
//     nearest.insert(nearest.begin(), pq->top().star->star);
//     pq->pop();
//   }
//   delete pq;
//   return nearest;
// }

// void deleteRecursion(Node* curr) { 
//     if (curr -> greater) {
//         deleteRecursion(curr -> greater);
//     }
//     if (curr -> lesser) {
//         deleteRecursion(curr -> lesser);
//     }
//     delete curr;
//     return;
// };

// StarMap::~StarMap() {
//   if(root) {
//     deleteRecursion(root);
//   }
// }

// StarMap* StarMap::create(std::istream& stream) {
//   return new StarMap(stream);
// }

// //multithreading
// //https://yasenh.github.io/post/kd-tree/