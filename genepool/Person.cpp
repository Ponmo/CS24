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
std::set<Person*> Person::ancestors(PMod pmod) { //return parent(s), and then the parents of their parent(s)
    std::set<Person*> result;
    if(pmod == PMod::PATERNAL) {
        if(fatherV) {
            result.insert(fatherV);
            std::set<Person*> resultOne = fatherV->ancestors(PMod::ANY);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    if(pmod == PMod::MATERNAL) {
        if(motherV) {
            result.insert(motherV);
            std::set<Person*> resultOne = motherV->ancestors(PMod::ANY);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    if(pmod == PMod::ANY) {
        if(motherV) {
            result.insert(motherV);
            std::set<Person*> resultOne = motherV->ancestors(PMod::ANY);
            result.insert(resultOne.begin(), resultOne.end());
        }
        if(fatherV) {
            result.insert(fatherV);
            std::set<Person*> resultOne = fatherV->ancestors(PMod::ANY);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    return result;
}
//TODO
std::set<Person*> Person::aunts(PMod pmod, SMod smod) { //First, get pointers to your parents (pmod). Then, their brothers or sisters!
    std::set<Person*> result;
    if(pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if(fatherV){ 
            std::set<Person*> resultOne = fatherV->sisters(PMod::ANY, smod);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    if(pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if(motherV){ 
            std::set<Person*> resultOne = motherV->sisters(PMod::ANY, smod);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    return result;
}
std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> result = siblings(pmod, smod);
    std::set<Person*> resultIterator = result;
    for (auto itr : resultIterator)
    {
        if(itr->genderV == Gender::FEMALE) {
            result.erase(itr);
        }
    } 
    return result;
}
std::set<Person*> Person::children() { //Return a set of children
    std::set<Person*> result;
    for(Person* i : theChildren) {
        result.insert(i);
    }
    return result;
}
//TODO
std::set<Person*> Person::cousins(PMod pmod, SMod smod) { //pmodY smodY???? Uncles and Aunts children
    std::set<Person*> result;
    std::set<Person*> resultOne = aunts(pmod, smod); 
    for(auto itr : resultOne) {
        std::set<Person*> resultItr = itr->children();
        result.insert(resultItr.begin(), resultItr.end());
    }
    resultOne = uncles(pmod, smod); 
    for(auto itr : resultOne) {
        std::set<Person*> resultItr = itr->children();
        result.insert(resultItr.begin(), resultItr.end());
    }
    return result;
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
std::set<Person*> Person::descendants() { //Insert each children, and then all of their children
    std::set<Person*> result;
    for(Person* i : theChildren) {
        result.insert(i);
        std::set<Person*> resultOne = i->descendants();
        result.insert(resultOne.begin(), resultOne.end());
    }
    return result;
}
std::set<Person*> Person::grandchildren() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            result.insert(j);
        }
    }
    return result;
}
std::set<Person*> Person::granddaughters() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            if(j->genderV == Gender::FEMALE) {
                result.insert(j);
            }
        }
    }
    return result;
}
std::set<Person*> Person::grandfathers(PMod pmod) { //return father of father, father of mother, father of mother, etc.
    std::set<Person*> result;
    if(pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if(motherV) {
            if(Person* i = motherV->fatherV) {
                result.insert(i);
            }
        }
    }
    if(pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if(fatherV) {
            if(Person* i = fatherV->fatherV) {
                result.insert(i);
            }
        }
    }
    return result;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> result;
    if(pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if(motherV) {
            if(Person* i = motherV->motherV) {
                result.insert(i);
            }
        }
    }
    if(pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if(fatherV) {
            if(Person* i = fatherV->motherV) {
                result.insert(i);
            }
        }
    }
    return result;
}
std::set<Person*> Person::grandparents(PMod pmod) { // Maternal Grandparents Return Your Mothers Parents. Paternal Grandparents return your father's parent. All should return both.
    std::set<Person*> result;
    std::set<Person*> resultOne = grandmothers(pmod);
    result.insert(resultOne.begin(), resultOne.end());
    resultOne = grandfathers(pmod);
    result.insert(resultOne.begin(), resultOne.end());
    return result;
}
std::set<Person*> Person::grandsons() {
    std::set<Person*> result;
    for(Person* i : theChildren) {
        for(Person* j : i->theChildren) {
            if(j->genderV == Gender::MALE) {
                result.insert(j);
            }
        }
    }
    return result;
}
//TODO
std::set<Person*> Person::nephews(PMod pmod, SMod smod) { //sons of your siblings (half or full) and (mother only or father only)
    std::set<Person*> result;
    std::set<Person*> resultIterator = siblings(pmod, smod);
    for (auto itr : resultIterator)
    {
        std::set<Person*> nephews = itr -> sons();
        result.insert(nephews.begin(), nephews.end());
    } 
    return result;
}
//TODO
std::set<Person*> Person::nieces(PMod pmod, SMod smod) { //daughters of your siblings
    std::set<Person*> result;
    std::set<Person*> resultIterator = siblings(pmod, smod);
    for (auto itr : resultIterator)
    {
        std::set<Person*> nieces = itr -> sons();
        result.insert(nieces.begin(), nieces.end());
    } 
    return result;
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
std::set<Person*> Person::siblings(PMod pmod, SMod smod) { //OK lets pretend I'm looking for maternal half siblings.
    std::set<Person*> result;
    if(pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if(fatherV) {
            if(smod == SMod::FULL || smod == SMod::ANY) {
                for(Person* i : fatherV->theChildren) { //Paternal Full
                    if (motherV && i->motherV && i->motherV == motherV) {
                        result.insert(i);
                    }
                }
            }
            if(smod == SMod::HALF || smod == SMod::ANY) {
                for(Person* i : fatherV->theChildren) { //Paternal Half
                    if (!motherV || i->motherV != motherV) {
                        result.insert(i);
                    }
                }
            }
        }
    }
    if(pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if(motherV) {
            if(smod == SMod::FULL || smod == SMod::ANY) {
                for(Person* i : motherV->theChildren) { //Maternal Full
                    if (fatherV && i->fatherV && i->fatherV == fatherV) {
                        result.insert(i);
                    }
                }
            }
            if(smod == SMod::HALF || smod == SMod::ANY) {
                for(Person* i : motherV->theChildren) { //MAternal Half
                    if (!fatherV || i->fatherV != fatherV) {
                        result.insert(i);
                    }
                }
            }
        }
    }
    result.erase(this);
    return result;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> result = siblings(pmod, smod);
    std::set<Person*> resultIterator = result;
    for (auto itr : resultIterator)
    {
        if(itr->genderV == Gender::MALE) {
            result.erase(itr);
        }
    } 
    return result;
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
//TODO
std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> result;
    if(pmod == PMod::PATERNAL || pmod == PMod::ANY) {
        if(fatherV){ 
            std::set<Person*> resultOne = fatherV->brothers(PMod::ANY, smod);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    if(pmod == PMod::MATERNAL || pmod == PMod::ANY) {
        if(motherV){ 
            std::set<Person*> resultOne = motherV->brothers(PMod::ANY, smod);
            result.insert(resultOne.begin(), resultOne.end());
        }
    }
    return result;  
}