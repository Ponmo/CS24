#include "Person.h"

// Person Member Functions
Person* a;
std::set<Person*> ba;
std::string apple = "apple";


//Constructor?
Person::Person () {

};
//Desconstructor?
Person::~Person() {

};

// basic get functions because class variables are private.
const std::string& Person::name() const {
    return nameV;
}
Gender Person::gender() const {
    return genderV;
}
Person* Person::mother() {
    return motherV;
}
Person* Person::father() {
    return fatherV;
}


//Relationship Functions:
std::set<Person*> Person::ancestors(PMod pmod) {
    ba.insert(a);
    return ba;
}
std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    ba.insert(a);
    return ba;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    ba.insert(a);
    return ba;
}
std::set<Person*> Person::children() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::cousins(PMod pmodY, SMod smodY) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::daughters() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::descendants() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandchildren() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::granddaughters() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandfathers(PMod pmod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandparents(PMod pmod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandsons() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::parents(PMod pmod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::sons() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}