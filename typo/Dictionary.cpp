
#include "Dictionary.h"
#include "Heap.h"

//Your dictionary is declared for you in `Dictionary.h`.  It's a simple class with
// two important jobs: it holds a list of all valid words, and owns the `correct()`
// function that translates sequences of points into probable words.

Dictionary::Dictionary(std::istream& stream) { //Ignore if line starts with # PARSING
    std::string line;
    while (std::getline(stream, line)) {
        if(line == "" || line[0] == '#') {  //Lines that are not entirely lowercase ASCII are ignored
            continue;
        }
        else {
            mWords.push_back(line);
        }
    }
}

Heap correct(const std::vector<Point>& points, size_t maxcount, float cutoff) { // Return a Heap array of probable words that are similar to what the user has typed in through points arranged by highest score to lowest score.

}