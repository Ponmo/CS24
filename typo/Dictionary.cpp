
#include "Dictionary.h"
#include "Heap.h"
#include <cmath>
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

Heap Dictionary::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const { // Return a Heap array of probable words that are similar to what the user has typed in through points arranged by highest score to lowest score.
    Heap typoCorrections(maxcount);
    size_t wordLength = points.size();
    for(std::string word : mWords) { //loop through each word in our mWords
        //Find all words with the correct length
        if (word.length() == wordLength) {
            size_t count = 0;
            float meanScore = 0;
            for(char a : word) { //loop through each character of the word, and compute its distance from the points
                //Find x and y of a through point.cpp
                size_t ascii = a - 97; //Finds the corresponding QWERTY point
                float distance = sqrt(pow(abs(QWERTY[ascii].x - points[count].x), 2) + pow(abs(QWERTY[ascii].y - points[count].y), 2));
                //Calculate abs(hypotenuse distance) between a and point[count]
                //Then calculate s with that distance
                float s = 1 / (10*pow(distance,2)+1);
                //Add it to the score total
                meanScore += s;
                count++;
            }
            //If the score total/number of characters is lower than the cutoff, don't do anything. Else append to the heap through push or pushpop UNLESS its score is not higher than the top()
            float score = meanScore/float(count); //count + 1?? FLOAT COnversion?
            if(score >= cutoff) {
                if (typoCorrections.count() > 0 && typoCorrections.top().score > score) { //This score is not greater than tops score
                    continue;
                }
                else {
                    if(typoCorrections.count() == typoCorrections.capacity())  {
                        typoCorrections.pushpop(word, score);
                    }
                    else {
                        typoCorrections.push(word, score);
                    }
                }
            }
        }
    }
    return typoCorrections;

}

// - The `correct()` function  is where the important stuff happens.  It takes in a
//   sequence of points; these are the points where the user touched the screen. It
//   then finds all the words  of the correct length,  scores them according to the
//   scoring algorithm below, and uses a `Heap` with capacity `maxcount` to collect
//   the most likely words.  Words with scores lower than `cutoff` are not included
//   in the output.


// ### Scoring

// To score a word, compare each character to the corresponding point in the points
// sequence.  Calculate `d`,  the  Euclidean  distance  between  the point  and the
// location of that letter on a QWERTY keyboard.  Then calculate `s`, the score for
// that character: `s = 1 / (10 d² + 1)`.  The score for the word is the mean score
// of all of its letters.  The higher the score, the better the match.

// A score is only defined for words with the same length as the point sequence.