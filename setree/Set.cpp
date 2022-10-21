#include "Set.h"
#include <iostream>
#include <tuple>

Node* nodeGlobal = new Node;

size_t insertRecursion(Node* curr, const std::string& value, Node* mRoot) { 
    //First, set a node to equal the current node so that you can increase its count.
    //Then check curr if its greater than or less than or nullptr or equal than. If its greater than, then set curr -> left, and continue.
    Node* currTwo = curr;
    
    if (value > curr -> data) {
        if (curr -> right == nullptr) { // Create newNode here and set curr -> right to it. Then return the address.
            Node* newNode = new Node;
            newNode -> data = value;
            curr -> right = newNode;
            if(curr == mRoot) {
                mRoot -> count++;
            }
            else {
                currTwo -> count++;
            }
            return 1;
        }
        curr = curr -> right;
    }
    else if (value < curr -> data) {
        if (curr -> left == nullptr) { // Create newNode here and set curr -> left to it
            Node* newNode = new Node;
            newNode -> data = value;
            curr -> left = newNode;
            if(curr == mRoot) {
                mRoot -> count++;
            }
            else {
                currTwo -> count++;
            }
            return 1;
        }
        curr = curr -> left;
    }
    else if (value == curr -> data) {
        return 0;
    }
    // else { //curr == nullptr
    //     return prevCurr;
    // }

     //if currTwo is nullptr, then set the address of left or right to the newNode... which might mean checking one ahead of curr and adding another special case to the insert function before recursion.
    size_t returnValue = insertRecursion(curr, value, mRoot);
    
    if (returnValue != 0) {
        currTwo -> count += 1;
        return 1;
    }
    else {
        return 0;
    }
}

void deleteRecursion(Node* curr) { 
    if (curr -> right) {
        deleteRecursion(curr -> right);
    }
    if (curr -> left) {
        deleteRecursion(curr -> left);
    }
    delete curr;
    return;
};
std::string recursivePrint(Node* curr) { // 
    if(curr->left && curr-> right) {
        return "(" + recursivePrint(curr->left) + " " + curr->data + " " + recursivePrint(curr->right) + ")";
    }
    else if(curr->right) {
        return "(- " + curr->data + " " + recursivePrint(curr->right) + ")";
    }
    else if(curr->left) {
        return "(" + recursivePrint(curr->left) + " " + curr->data + " -)";
    }
    return curr->data;
};
// std::pair<Node*, size_t> recursiveMove(Node* curr, Node* mRoot) {
//     // For each node except mRoot, create a new node with the same data, pointers to other nodes (either return a pointer or nullptr), and set the count ++
//     Node* newNode = new Node;
//     newNode -> data = curr->data;
//     //mRoot needs to be set.
//     if (mRoot == nullptr) {
//         mRoot = newNode;
//     }
//     Node* a = nullptr;
//     size_t b = 0;
//     if (curr -> left != nullptr) {
//         std::tie(a, b) = recursiveMove(curr->left, mRoot);
//         b++;
//         newNode -> left = a;
//         newNode -> count += b;
//     }
//     if (curr -> right != nullptr) {
//         std::tie(a, b) = recursiveMove(curr->right, mRoot);
//         b++;
//         newNode -> right = a;
//         newNode -> count += b;
//     }
//     return std::make_pair(newNode, b);
// };

std::string global = "hello";

Set::Set() {
    mRoot = nullptr;
};

Set::Set(const Set& other) { //copy constructor
    // mRoot = nullptr;
    // Node* oldCurr = other.mRoot;
    // if (mRoot) {
    //     recursiveMove(oldCurr, mRoot);
    // }
};

Set::Set(Set&& other) { //move constructor
    mRoot = other.mRoot;
    other.mRoot = nullptr;
};

Set::~Set() {
    if (mRoot) {
        deleteRecursion(mRoot);
    }
};

size_t Set::clear() {
    if (mRoot) {
        size_t numberDeleted = mRoot -> count;
        deleteRecursion(mRoot);
        mRoot = nullptr;
        return numberDeleted;
    }
    return 0;
};
bool Set::contains(const std::string& value) const {
    Node* curr = mRoot;
    while(curr!=nullptr) {
        if(value > curr->data) {
            curr = curr -> right;
        }
        else if (value < curr -> data) {
            curr = curr -> left;
        }
        else {
            return true;
        }
    }
    return false;
};

size_t Set::count() const {
    if (mRoot) {
        return mRoot -> count;
    }
    return 0;
};

void Set::debug() {
    return;
};

size_t Set::insert(const std::string& value) {
    //if mRoot is nullptr/first insert
    if (mRoot == nullptr) {
        Node* newNode = new Node;
        newNode -> data = value;
        mRoot = newNode;
        return 1;
    }
    //Search through the tree until you get to the address where it needs to be inserted, unless it returns nullptr, which means it is an equal value
    //you can probably return insertRecursion.
    //This either become nullptr or the address of the place you want to insert it at
    return insertRecursion(mRoot, value, mRoot);
};

// Node* lookupRecursion(Node* curr, size_t n) {
    // if (curr->left) {
    //     if(curr -> left -> count == n) {
    //         nodeGlobal = curr;
    //         return curr;
    //     }
    //     Node* node = lookupRecursion(curr->left, n);
    //     if (node) {
    //         return node;
    //     }
    // }
    // if(curr->right) {
    //     Node* node = lookupRecursion(curr->right, n);
    //     if (node) {
    //         return node;
    //     }
    // }
    // return nullptr;
// };

const std::string& Set::lookup(size_t n) const {
    //So recursion through every single node should check its left child's count. If it is equal then return that node's pointer;
    // std::cout << "An iteration" + std::to_string(mRoot -> count);
    // std::cout << "An iteration" + std::to_string(mRoot -> left -> count);
    // std::cout << "An iteration" + std::to_string(mRoot -> left -> left -> count);
    // std::cout << "An iteration" + std::to_string(mRoot -> count);


    // if (mRoot) {

    //     Node* node = lookupRecursion(mRoot, n);
    //     if(nodeGlobal) {
    //         return nodeGlobal -> data;
    //     }
    // }
    n++;
    throw std::out_of_range("lookup out of range");
    // std::cout << "somehow out of range\n";
    // return "hi";
};

void Set::print() const {
    if (mRoot) {
        std::cout << recursivePrint(mRoot);
    }
    else {
        std::cout << "-";
    }
    std::cout << "\n";
    return;
};

size_t Set::remove(const std::string& value) {
    //Loop through the tree until you find the value, if you don't find it, do nothing and return 0. If you do, remove it either by erasing it or swapping and then return 1
    Node* curr = mRoot;
    Node* prevCurr = nullptr;
    bool leftOrRight = false;
    //to keep track of what counts need to go up or down
    size_t trackLength = 0;

    // std::cout << "remove function starts\n";
    if(!mRoot) {
        // std::cout << "mRoot does not exist return 0\n";
        return 0;
    }
    else {
        trackLength = mRoot -> count;
    }
    Node* track[trackLength];
    int i = 0;
    //Two things , set leftOr Right based on , and check if mRoot is the thing being removed, then set mRoot to node
    while(curr) { // loop through until curr is nullptr
        // std::cout << "One Loop 0\n";
        track[i] = curr;
        if (value > curr -> data) {
            // std::cout << "Value Greater 0\n";
            prevCurr = curr;
            curr = curr -> right;
            leftOrRight = true;
        }
        else if (value < curr -> data) {
            // std::cout << "Value Lesser 0\n";
            prevCurr = curr;
            curr = curr -> left;
            leftOrRight = false;
        }
        else { 
            if(curr->left && curr->right) { //if it has both children
                Node* prevCurrTwo = curr;
                Node* currTwo = curr->left;
                while(currTwo -> right != nullptr) {
                    track[i] = currTwo;
                    prevCurrTwo = currTwo;
                    currTwo = currTwo -> right;
                    i++;
                }
                track[i] = nullptr;
                curr -> data = currTwo -> data;
                if(prevCurrTwo != curr) {
                    prevCurrTwo -> right = nullptr;
                    if(currTwo->left) {
                        prevCurrTwo -> right = currTwo -> left;
                    }
                }
                else {
                    if(currTwo->left) {
                        prevCurrTwo -> left = currTwo -> left;
                    }
                    else {
                        prevCurrTwo -> left = nullptr;
                    }
                }
                delete currTwo;

                int j = 0;
                while (track[j]) {
                    track[j]->count--;
                    j++;
                }
                return 1;
            }
            else if(curr->left) { //if it has one child to the left
                // std::cout << "Node Låeft Child 0\n";
                if (curr != mRoot) {
                    if(leftOrRight) {
                        prevCurr->left = curr -> left;
                    }
                    else {
                        prevCurr -> left = curr -> left;
                    }
                }
                else {
                    mRoot = curr -> left;
                }
                track[i] = nullptr;
                delete curr;

                // Loop through track until nullptr to decrease each count by one
                int j = 0;
                while (track[j]) {
                    track[j]->count--;
                    j++;
                }

                return 1;
            }
            else if(curr->right) {
                // std::cout << "Node Right Child 0\n";
                if (curr != mRoot) {
                    if(leftOrRight) {
                        prevCurr->right = curr -> right;
                    }
                    else {
                        prevCurr -> left = curr -> right;
                    }
                }
                else {
                    mRoot = curr -> right;
                }
                track[i] = nullptr;
                delete curr;

                int j = 0;
                while (track[j]) {
                    track[j]->count--;
                    j++;
                }

                return 1;
            }
            else { //if it has no children
                // std::cout << "Node no children 0\n";
                if (curr!= mRoot) {
                    if(leftOrRight) {
                        // std::cout << "Node no children left 0\n";
                        prevCurr->right = nullptr;
                    }
                    else {
                        // std::cout << "Node no children right 0\n";
                        prevCurr -> left = nullptr;
                    }
                }
                else {
                    mRoot = nullptr;
                }
                delete curr;

                track[i] = nullptr;
                int j = 0;
                while (track[j]) {
                    track[j]->count--;
                    j++;
                }

                return 1;
            }
            // std::cout << "Somehow didn't find it 0\n";
            return 0;
        }
        i++;
    }
    
    // std::cout << "Not found 0\n";
    return 0;
};


// `remove(value)` removes a value from the set.  If the value to remove  is on a
//   node with less than two children,  it removes that node.  If the value is on a
//   node with two children, it finds the next smallest value in the set, copies it
//   over  the value to remove,  and then removes  the node it copied from.  If the
//   value to remove is not in the set,  it does nothing.  It returns the number of
//   values that were removed.


































//so recursion works until you can find the address where it needs to be inserted at. If you insert inside the function, then you probably need a prevCurr or go one Ahead, if not then you need to 


//previous non recursion way of doing insert, but couldn't keep track of count very well. recursion is still slower though
    // if (returnValue != nullptr) {
    //     // Set the newNode here
    //     return 1;
    // }
    // //else delete newNode and return 0
    // delete newNode;
    // return 0;
    

    // Inserting a value
    // So loop through the tree until you reach a nullptr, then insert it there. For each interation, check greater or less than, then update the ptr to left and right
    // Node* curr = mRoot;
    // // prevCurr is used to 
    // Node* prevCurr = nullptr;
    // Node* newNode = new Node;
    // newNode -> count = 1;
    // if (!mRoot) { //If nothing is in the tree yet, insert at at root.
    //     mRoot = newNode;
    //     return 1;
    // };
    // while(curr) { // loop through until curr is nullptr
    //     if (value > curr -> data) {
    //         prevCurr = curr;
    //         curr = curr -> right;
    //     }
    //     else if (value < curr -> data) {
    //         prevCurr = curr;
    //         curr = curr -> left;
    //     }
    //     else { // it equals a value so thats not good. Get it outta here.
    //         delete newNode;
    //         return 0;
    //     }
    // };
    // // Once curr is nullptr, then insert it at that leaf. Increase the count of everything that needs count to be increased (this might need recursion to check every node before it increases count).
    
    // return 1;