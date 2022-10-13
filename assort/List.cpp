#include "List.h"
#include <iostream>

std::string global = ""; // necessary for return of std::string& type

List::List() {
   head = nullptr;
};
List::List(const List& other) { // copy constructor
    // List list;
    // head = other.head;
    // Node* curr = head;
    // // Copy every node
    // while(curr!=nullptr) {
    //     list.insert(curr->data);
	//     curr = curr->next;
    // }
};
List::List(List&& other) { //move constructor

};
List::~List() {
    // delete head;
    Node* curr = head;
    Node* prev = head;
    // Delete every node
    while(curr!=nullptr) {
	    curr = curr->next;
        delete prev;
        prev = curr;
    }
};
size_t List::count() const {
    Node* curr = head;
    size_t count = 0;
    // Delete every node
    while(curr!=nullptr) {
        count += 1;
	    curr = curr->next;
    }
    return count;
};
void List::insert(const std::string& value) {
    Node* node = new Node;
    node->data = value; 
    node->next = nullptr;

    Node* curr = head;
    Node* prevCurr = nullptr;

    if(head==nullptr) { //first insert edge case, just insert it at 0.
        head = node;
        return;
    }

    // Maybe needed?
    if(value <= head -> data) { //Second insert edge case, just it insert it, man
        node -> next = curr;
        head = node;
        return;
    };

    while(curr!=nullptr) {
        //if value is less or equal to the current, insert it there. Then Break
	    if(value <= curr->data) {
            prevCurr -> next = node;
            node -> next = curr;
            return;
        }
        prevCurr = curr;
	    curr = curr->next;
    }
    if(curr==nullptr) {
        //insert it at the end.
        prevCurr -> next = node;
    }
    return;
};
const std::string& List::lookup(size_t index) const {
    size_t currentIndex = 0;
    Node* curr = head;
    while(curr!=nullptr) {
        if (currentIndex == index) {
            return curr -> data;
        }
        currentIndex += 1;
        curr = curr -> next;
    }
    throw std::out_of_range("out of range index");
    return global;
};
void List::print(bool reverse) const {
    Node* curr = head;
    // std::cout << "[";
    std::string totalPrint = "[";
    if(!reverse) {
        while(curr!=nullptr) {
            if(curr->next != nullptr) {
                // std::cout << curr -> data + ", ";
                totalPrint += curr -> data + ", ";
            }
            else {
                totalPrint += curr -> data;
            }
            curr = curr -> next;
        }
    }
    else { //reverse print it out
        if(curr!=nullptr) {
            totalPrint.insert(1, curr->data);
            curr = curr -> next;
        }
        while(curr!=nullptr) {
            totalPrint.insert(1, curr->data + ", ");
            curr = curr -> next;
        }
    }
    std::cout << totalPrint;
    std::cout << "]\n";
    return;
};

std::string List::remove(size_t index) {
    size_t currentIndex = 0;
    Node* curr = head;
    Node* prevCurr = nullptr;
    std::string returnString = "";

    // if(curr==nullptr) {
    //     throw std::out_of_range("out of range remove");
    // }
    // std::cout << head -> data;
    while(curr!=nullptr) {
        if(currentIndex == index) {
            if(prevCurr != nullptr) {
                if(curr -> next) {
                    prevCurr -> next = curr -> next;
                    returnString = curr -> data;
                    delete curr;
                }
                else {
                    prevCurr -> next = nullptr;
                    returnString = curr -> data;
                    delete curr;
                }
            }
            else {
                if(curr -> next) {
                    head = curr -> next;
                    returnString = curr -> data;
                    delete curr;
                }
                else {
                    returnString = head -> data;
                    delete head;
                    head = nullptr;
                }

            }
            return returnString;
        }
        currentIndex += 1;
        prevCurr = curr;
        curr = curr -> next;
    }
    throw std::out_of_range("out of range remove");
    return returnString;
};




size_t List::remove(const std::string& value) {
    size_t numberRemoved = 0;
    Node* curr = head;
    Node* prevCurr = nullptr;

    while(curr!=nullptr) {
        if(value == curr -> data) {
            // if(prevCurr == head) {
            //     prevCurr = nullptr;
            //     curr = head;
            // }
            if(prevCurr != nullptr) { //if prevCurr is head, (when first one is removed)
                // if(prevCurr == head) {
                //     prevCurr = curr -> next;
                // }
                // else {
                //     prevCurr -> next = curr -> next;
                // }
                prevCurr -> next = curr -> next;
                delete curr;
                curr = prevCurr;
            }
            else {
                head = curr -> next;
                delete curr;
                curr = head;
            }
            numberRemoved += 1;
        }
        prevCurr = curr;
        curr = curr -> next;
    }
    return numberRemoved;
};
 
 
 
// List(); //Constructor
//     List(const List& other); // Copy
//     List(List&& other); // Move
//     ~List(); //Deconstructor
 
   // size_t             count() const;
   // void               insert(const std::string& value);
   // const std::string& lookup(size_t index) const;
   // void               print(bool reverse = false) const;
   // std::string        remove(size_t index);
   // size_t             remove(const std::string& value);
