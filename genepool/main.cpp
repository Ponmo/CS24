#include "Person.h"
#include "GenePool.h"
#include "Query.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

// This file provides a standard main loop.
// You can edit it if you want, but you shouldn't need to.
// Gradescope will use the original version.


// Helper class to sort person pointers by name:
struct Compare {
  bool operator () (const Person* a, const Person* b) const {
    if(a == nullptr || b == nullptr) {
      throw std::invalid_argument("Null pointer in result set.");
    }

    return a->name() < b->name();
  }
};


int main(int argc, char** argv) {
  if(argc != 2) { //If it does not have two arguments, repeat (needs a dataset)
    std::cerr << "USAGE: ./genepool [datafile.tsv]\n";
    std::exit(1);
  }

  GenePool* pool = nullptr;

  try { 
    // Read the database file:
    std::ifstream stream(argv[1]);
    pool = new GenePool(stream);

  }
  catch(const std::exception& e) {
    std::cerr << "Error reading database: " << e.what() << "\n";
    std::exit(1);
  }

  // This then tells the user to input a query that they want to use to search the database.
  std::string line;
  std::cout << "> ";
  while(std::getline(std::cin, line)) {
    try {
      // Parse and run the query:
      Query query(line);
      std::set<Person*> result = query.run(*pool); //Calls our person functions in the Query.cpp

      // Sort the people by name for consistent output:
      std::vector<Person*> people(result.begin(), result.end());
      std::sort(people.begin(), people.end(), Compare());

      // Print the result:
      for(Person* person: people) {
        std::cout << " - " << person->name() << std::endl;
      }
      if(people.empty()) {
        std::cout << " (no results)\n";
      }
    }
    catch(const std::exception& e) {
      // Print the error message:
      std::cout << e.what() << std::endl;
    }

    std::cout << "> ";
  }

  std::cout << '\n';
  delete pool;
  return 0;
}
