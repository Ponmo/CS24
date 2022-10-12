#include "List.h"
 
List::List() {
   head = nullptr;
};
List::List(const List& other) {
 
};
List::List(List&& other) {
 
};
List::~List() {
 
};
size_t List::count() const {
    return 1;
};
void List::insert(const std::string& value) {
    return;
};
const std::string& List::lookup(size_t index) const {
    std::string temporary = new std::string("Hello");
    return temporary;
};
void List::print(bool reverse) const {
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
