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

const char BLANK = '0';						/* Character for empty space. */
const char FILLED = '1';					/* Character for black space. */
const int boxSize = 64;						/* Best pixel width for a box. */

class Crossword {
	private:
		int width;							/* Width of the board. */
		char** board;						/* The board matrix. */
		int** numCharsUsed;					/* Used for erasing words. */
		vector<Space> spaces;				/* Places to put words. */
		map<int, vector<Word> > wordMap;	/* All words mapped by length. */
		
		/* Initializer function, simply sets up the spaces vector from the 0s
		 * and 1s read in from the file.
		 */
		void initialize();

		/* This is the recursive function that actually solves the puzzle by
		 * inserting and removing words until a solution is found.
		 */
		bool fillPuzzle(int);
		
		/* Checks if a word can fit in the space and if the word isn't already
		 * used.
		 */
		bool canWordFit(Word&, Space);

		/* Places the word in the character matrix.
		 */
		void insertWord(Word&, Space);

		/* Removes the word from the character matrix.
		 */
		void removeWord(Word&, Space);

	public:

		/* Constructor with two filenames for the matrix and the word list.
		 */
		Crossword(string, string);

		/* Destructor that cleans up memory usage.
		 */
		~Crossword();
		
		/* This is the function to be called by the main function to start the
		 * solving problem.
		 */
		bool isValid();

		/* Returns the matrix width.
		 */
		int getWidth();
		
		/* Clears the board so we can restart without issues.
		 */
		void reset();

		/* First clears the board and then shuffles all the words in the wordMap
		 * so that the next runs of the program can be different from the last.
		 */
		void shuffle();
		
		/* This function draws the board with OpenGL functions. Pretty! :)
		 */
		void draw(bool);
};

#endif