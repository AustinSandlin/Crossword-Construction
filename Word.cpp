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