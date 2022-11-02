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
    while (std::getline(stream, line)) {
        // If the line starts with # or is empty, then go to next line.
        if(line == "" || line[0] == '#') {
            continue;
        }
        Person* newNode = new Person;
        //Get each token seperated by a tab character.
        std::stringstream nLine(line);
        std::string currentToken;
        std::string tempName;
        size_t count = 0;
        while(std::getline(nLine, currentToken, '\t')) {
            if(count == 0) {
                tempName = currentToken;
                newNode->nameV = currentToken;
            }
            else if (count == 2) {
                if(currentToken == "???") {
                    newNode -> motherV = nullptr;
                }
                else {
                    newNode -> motherV = GeneMap.find(currentToken) -> second;
                    newNode->motherV->theChildren.push_back(newNode);
                }
            }
            else if (count == 1) {
                if (currentToken == "male") {
                    newNode->genderV = Gender::MALE;
                }
                else if (currentToken == "female") {
                    newNode->genderV = Gender::FEMALE;
                }
            }
            else {
                if(currentToken == "???") {
                    newNode -> fatherV = nullptr;
                }
                else {
                    newNode -> fatherV = GeneMap.find(currentToken) -> second;
                    newNode->fatherV->theChildren.push_back(newNode);
                }
            }
            count++;
        }
        GeneMap.insert({tempName, newNode});
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

// make
// ./genepool data/Olympians.tsv
// make clean


        // std::string theirName, theirGender, theirMother, theirFather;
        // if (!(nLine >> theirName >> theirGender >> theirMother >> theirFather)) { break; } // error (may not be needed if already checked in main)
        // newNode->nameV = theirName; //Set Name
        // if(theirFather == "???") { //Set Father Pointer, and set Father's children pointer to this node
        //     newNode->fatherV = nullptr;
        // }
        // else {
        //     newNode->fatherV = GeneMap.find(theirFather)->second;
        //     newNode->fatherV->theChildren.push_back(newNode);
        // }
        // if(theirMother == "???") { //Set Mother Pointer, and set Mother's children pointer to this node
        //     newNode->motherV = nullptr;
        // }
        // else {
        //     newNode->motherV = GeneMap.find(theirMother)->second;
        //     newNode->motherV->theChildren.push_back(newNode);
        // }
        // if(theirGender == "male") { //set gender
        //     newNode->genderV = Gender::MALE;
        // }
        // else {
        //     newNode->genderV = Gender::FEMALE;
        // }
// std::stringstream nLine(line);
//         std::string currentToken;
//         std::string tempName;
//         size_t count = 0;
//         while(std::getline(nLine, currentToken, '\t')) {
//             if (count == 0) { //set nameV
//                 newNode->nameV = currentToken;
//             }
//             else if (count == 2) { //set mother name... needs to look up mother in the map and set the pointer to them. feck?
//                 if(currentToken == "???") {
//                     newNode->motherV = nullptr;
//                 }
//                 else {
//                     newNode->motherV = GeneMap.find(currentToken)->second;
//                 }
//             }
//             else if (currentToken == "male") {
//                 // Gender ge;
//                 // newNode->genderV = Gender MALE;
//             }
//             else if(currentToken == "female") {
//                 // newNode->genderV = FEMALE;
//             }
//             else { //set father name

//             }
//             count++;
//         }
//         GeneMap.insert({tempName, newNode});

//     }