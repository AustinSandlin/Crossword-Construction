/* Author: Austin Sandlin & Victoria Chuba
 * Title: Crossword Solver
 * Description: This is the blank word, stores the string and whether or not
 *              it's being used in the crossword.
 */

#ifndef _WORD_H
#define _WORD_H

#include <string>

using namespace std;

struct Word {
    private:
        string word;
        bool used;
    
    public:
        Word(string w);
        
        string getWord();
        bool isUsed();
    
        void setUsed(bool u);
};

#endif