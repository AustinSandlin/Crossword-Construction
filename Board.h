#include "Word.h"
#include <GLUT/glut.h>
#include <iostream>

using namespace std;

class Board {
	private:
		int width;
		char** board;

		vector<Word> words;

		void setupWords();

	public:
		Board(int);
		~Board();

		int getNumWords();
		bool isValidBoard();

		vector<Word> getWords();
		vector<Point> getInter();

		void draw(int);

		void read(istream&);
		//friend istream& operator>> (istream&, Board&);
		friend ostream& operator<< (ostream&, Board&);
};
