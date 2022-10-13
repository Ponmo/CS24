#include "List.h"
#include <iostream>

std::string global = "hello"; // necessary for return of std::string& type

List::List() {
   head = nullptr;
};
List::List(const List& other) {
    // head = other.head;
    // if (other.head -> next) {
    //     head->next = other.head -> next;
    // }
};
List::List(List&& other) {

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
        head = node;
        node -> next = curr;
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
        }
        curr = curr -> next;
        while(curr!=nullptr) {
            if(curr->next != nullptr) {
                // std::cout << curr -> data + ", ";
                totalPrint.insert(1, curr->data + ", ");
            }
            curr = curr -> next;
        }
    }
    std::cout << totalPrint;
    std::cout << "]\n";
    return;
};
std::string List::remove(size_t index) {
    return "helllo";
};
size_t List::remove(const std::string& value) {
    return 1;
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
