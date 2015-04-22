/* Author: Austin Sandlin
 *
 *
 */
#include <GLUT/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Dictionary.h"
#include "Space.h"
#include "Word.h"

using namespace std;

const char BLANK = '0';
const char FILLED = '1';
const int boxSize = 64;

class Crossword {
	private:
		int width;
		char** board;
		int** numCharsUsed;
		vector<Word> words;
		vector<Space> spaces;
		Dictionary dict;
		
		void initialize();
		bool fillPuzzle(int index);
		
	public:
		Crossword(string filename);
		~Crossword();
		
		bool isValid();
		int getWidth();
		
		void reset();
		
		bool canWordFit(Word w, Space s);
		void insertWord(Word w, Space s);
		void removeWord(Word w, Space s);
		
		//COPY OVER
		void draw();
};
