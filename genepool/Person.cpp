#include "Person.h"

// Person Member Functions
Person* a;
std::set<Person*> ba;
std::string apple = "apple";

//Constructor? Not needed.
Person::Person () {

};
//Desconstructor? Not needed.
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
    if(motherV) {
        return motherV;
    }
    return nullptr;
}
Person* Person::father() {
    if(fatherV) {
        return fatherV;
    }
    return nullptr;
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
std::set<Person*> Person::children() { //Return a set of children
    std::set<Person*> result;
    for(Person* i : theChildren) {
        result.insert(i);
    }
    return result;
}
std::set<Person*> Person::cousins(PMod pmodY, SMod smodY) {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::daughters() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        if (i->genderV == Gender::FEMALE) {
            result.insert(i);
        }
    }
    return result;
}
std::set<Person*> Person::descendants() {
ba.insert(a);
    return ba;
}
std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            result.insert(i);
        }
    }
    return result;
}
std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            if(j->genderV == Gender::FEMALE) {
                result.insert(i);
            }
        }
    }
    return result;
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
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            if(j->genderV == Gender::MALE) {
                result.insert(i);
            }
        }
    }
    return result;
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
    std::set<Person*> result;
    if ((pmod == PMod::ANY || pmod == PMod::MATERNAL) && mother()) {
        result.insert(mother());
    }
    if ((pmod == PMod::ANY || pmod == PMod::PATERNAL) && father()) {
        result.insert(father());
    }
    return result;
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
    std::set<Person*> result;
    for(Person* i : theChildren) {
        if (i->genderV == Gender::MALE) {
            result.insert(i);
        }
    }
    return result;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
ba.insert(a);
    return ba;
}