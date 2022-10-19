#include "Set.h"

std::string global = "hello";

Set::Set() {

};

Set::Set(const Set& other) {

};

Set::Set(Set&& other) {

};

Set::~Set() {

};

size_t Set::clear() {
    return 0;
};

bool Set::contains(const std::string& value) const {
    std::string a = value;
    return true;
};

size_t Set::count() const {
    return 0;
};

void Set::debug() {
    return;
};

size_t Set::insert(const std::string& value) {
    std::string a = value;
    return 0;
};
const std::string& Set::lookup(size_t n) const {
    n++;
    return global;
};
void Set::print() const {
    return;
};
size_t Set::remove(const std::string& value) {
    std::string a = value;
    return 1;
};