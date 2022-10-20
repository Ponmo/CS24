#include "Set.h"
#include <iostream>

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
        currTwo -> count++;
        return returnValue;
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

std::string global = "hello";

Set::Set() {
    mRoot = nullptr;
};

Set::Set(const Set& other) {

};

Set::Set(Set&& other) {

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

const std::string& Set::lookup(size_t n) const {
    n++;
    throw std::out_of_range("lookup out of range");
    return global;
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
    std::string a = value;
    return 1;
};

//so recursion works until you can find the address where it needs to be inserted at. If you insert inside the function, then you probably need a prevCurr or go one Ahead, if not then you need to 


//previous non recursion way of doing insert
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