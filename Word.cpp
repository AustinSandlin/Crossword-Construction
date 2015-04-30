/* Author: Austin Sandlin & Victoria Chuba
 * Title: Crossword Solver
 * Description: This is the blank word, stores the string and whether or not
 *              it's being used in the crossword.
 */

#include "Word.h"

Word::Word(string w) {
    word = w;
    used = false;
}

string Word::getWord() {
    return word;
}

bool Word::isUsed() {
    return used;
}

void Word::setUsed(bool u){
    used = u;
}