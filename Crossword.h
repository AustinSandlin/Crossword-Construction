#ifndef _CROSSWORD_H
#define _CROSSWORD_H

#include <GLUT/glut.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
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
		vector<Space> spaces;
		map<int, vector<Word> > wordMap;
		
		void initialize();
		bool fillPuzzle(int);
		
	public:
		Crossword(string, string);
		~Crossword();
		
		bool isValid();
		int getWidth();
		
		void reset();
		void shuffle();
		
		bool canWordFit(Word&, Space);
		void insertWord(Word&, Space);
		void removeWord(Word&, Space);
		
		//COPY OVER
		void draw();
};

#endif