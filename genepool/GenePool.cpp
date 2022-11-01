#include "GenePool.h"
#include <iostream>
#include <sstream>

// GenePool Member Functions

//This function finds the person with name and returns its pointer.
Person* GenePool::find(const std::string& name) const {
    if (Person* temp = GeneMap.find(name)->second) {
        return temp;
    }
    return nullptr;
};

//This function takes in a tsv file in the form of a istream and is suppose to store it. Like parse in previous lab.
GenePool::GenePool(std::istream& stream) {

    // Loop through each line in the file.
    std::string line;
    while (std::getline(stream, line))
    {
        // If the line starts with # or is empty, then go to next line.
        if(line == "" || line[0] == '#') {
            continue;
        }

        Person* newNode = new Person;

        //Loop through each token seperated by a tab character.
        std::stringstream nLine(line);

        std::string theirName, theirGender, theirMother, theirFather;
        if (!(nLine >> theirName >> theirGender >> theirMother >> theirFather)) { break; } // error (may not be needed if already checked in main)
        newNode->nameV = theirName; //Set Name
        if(theirFather == "???") { //Set Father Pointer, and set Father's children pointer to this node
            newNode->fatherV = nullptr;
        }
        else {
            newNode->fatherV = GeneMap.find(theirFather)->second;
            newNode->fatherV->children.push_back(newNode);
        }
        if(theirMother == "???") { //Set Mother Pointer, and set Mother's children pointer to this node
            newNode->motherV = nullptr;
        }
        else {
            newNode->motherV = GeneMap.find(theirMother)->second;
            newNode->motherV->children.push_back(newNode);
        }
        if(theirGender == "male") { //set gender
            newNode->genderV = Gender::MALE;
        }
        else {
            newNode->genderV = Gender::FEMALE;
        }
        GeneMap.insert({theirName, newNode});
    }
};

//Destructor. Should destruct all Person nodes inside it as well.
GenePool::~GenePool() {
    //loop through the map to delete all nodes in it!
    for (auto const& x : GeneMap)
    {
        delete x.second;
    }
}