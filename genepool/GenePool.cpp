#include "GenePool.h"
#include <iostream>
#include <sstream>

// GenePool Member Functions

//This function finds the person with name and returns its pointer.
Person* GenePool::find(const std::string& name) const {
    Person* node = new Person;
    std::string stump = name;
    return node;
};

//This function takes in a tsv file in the form of a istream and is suppose to store it. Like parse in previous lab.
GenePool::GenePool(std::istream& stream) {
    std::cout << "Reached Here";

    // Loop through each line in the file.
    std::string line;
    while (std::getline(stream, line))
    {
        // If the line starts with # or is empty, then go to next line.
        if(line == "" || line[0] == '#') {
            break;
        }
        Person* newNode = new Person;
        //Loop through each token seperated by a tab character.
        std::stringstream nLine(line);
        std::string currentToken;
        std::string tempName;
        size_t count = 0;
        while(std::getline(nLine, currentToken, '\t')) {
            if (count == 0) { //set nameV
                newNode->nameV = currentToken;
            }
            else if (count == 2) { //set mother name... needs to look up mother in the map and set the pointer to them. feck?
                if(currentToken == "???") {
                    newNode->motherV = nullptr;
                }
                else {
                    newNode->motherV = GeneMap.find(currentToken)->second;
                }
            }
            else if (currentToken == "male") {
                // Gender ge;
                // newNode->genderV = Gender MALE;
            }
            else if(currentToken == "female") {
                // newNode->genderV = FEMALE;
            }
            else { //set father name

            }
            count++;
        }
        GeneMap.insert({tempName, newNode});

    }
};

//Destructor. Should destruct all Person nodes inside it as well.
GenePool::~GenePool() {

}

















 //Find how many tokens there are in the line, in order to see how many tokens are part of their name (Some names are like Windsor Edward Batten-Barrow Smith)
        // std::istringstream mLine(line);
        // size_t count = std::distance(std::istream_iterator<std::string>(mLine), std::istream_iterator<std::string>());
        
        //Tokenize the line into seperate strings and then loop through them.
        // std::istringstream nLine(line);
        // std::string arrayTokens[count];
        // Gender gender;
        // Person* father;
        // Person* mother;

        //Put each token of the line into the array.
        // for (int i = 0; i < count; i++) {
        //     if (!(nLine >> arrayTokens[count])) { break; }
        // }

        // if (!(nLine >> arrayTokens[0] >> arrayTokens[1])) { break; } 
        //process pair (a,b)
        // while(nLine >> currentToken) {
        //     currentCount++;
        //     if(currentCount > count) {

        //     }
        // }