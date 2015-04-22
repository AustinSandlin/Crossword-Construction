#include "Board.h"

Board::Board(int w) {
	width = w;
	board = new char*[width];
	for(int i = 0; i < width; ++i) {
		board[i] = new char[width];
		for(int j = 0; j < width; ++j) {
			board[i][j] = '1';
		}
	}
}

Board::~Board() {
	for(int i = 0; i < width; ++i) {
		delete board[i];
	}
	delete board;
}

void Board::setupWords() {
	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < width; ++j) {
			if(board[i][j] == '0' && ((i-1 < 0 || ((i-1) >= 0 && board[i-1][j] == '1')) && (i+1) < width && board[i+1][j] == '0')) {
				int length = 1;
				while(i+length < width && board[i+length][j] == '0') {
					++length;
				}
				words.push_back(Word(Point(i, j), length, DOWN));
			}
			if(board[i][j] == '0' && ((j-1 < 0 || ((j-1) >= 0 && board[i][j-1] == '1')) && (j+1) < width && board[i][j+1] == '0')) {
				int length = 1;
				while(j+length < width && board[i][j+length] == '0') {
					++length;
				}
				words.push_back(Word(Point(i, j), length, ACROSS));
			}
		}
	}

	for(int i = 0; i < words.size(); ++i) {
		for(int j = i+1; j < words.size(); ++j) {
			if(words[i].dir == ACROSS && words[j].dir == DOWN) {
				if(words[j].start.j >= words[i].start.j && words[j].start.j < words[i].start.j+words[i].length &&
				   words[i].start.i >= words[j].start.i && words[i].start.i < words[j].start.i+words[j].length) {
					words[i].addIntersection(j, Point(words[i].start.i, words[j].start.j));
					words[j].addIntersection(i, Point(words[i].start.i, words[j].start.j));
				}
			}
			else if(words[i].dir == DOWN && words[j].dir == ACROSS) {
				if(words[i].start.j >= words[j].start.j && words[i].start.j < words[j].start.j+words[j].length &&
				   words[j].start.i >= words[i].start.i && words[j].start.i < words[i].start.i+words[i].length) {
					words[i].addIntersection(j, Point(words[j].start.i, words[i].start.j));
					words[j].addIntersection(i, Point(words[j].start.i, words[i].start.j));
				}

			}
		}
	}
}

vector<Word> Board::getWords() {
	return words;
}

bool Board::isValidBoard() {
	return false;
}

void Board::draw(int boxSize) {
	for(int i = width; i > 0; --i) {
		for(int j = 0; j < width; ++j) {
			if(board[width-i][j] == '0') {
				glColor3f(1.0, 1.0, 1.0);
				glBegin(GL_QUADS);
				glVertex2i(j*boxSize+1, i*boxSize-1);
				glVertex2i(j*boxSize+1, i*boxSize-boxSize+1);
				glVertex2i(j*boxSize+boxSize-1, i*boxSize-boxSize+1);
				glVertex2i(j*boxSize+boxSize-1, i*boxSize-1);
				glEnd();

				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINE_LOOP);
				glVertex2i(j*boxSize+1, i*boxSize-1);
				glVertex2i(j*boxSize+1, i*boxSize-boxSize+1);
				glVertex2i(j*boxSize+boxSize-1, i*boxSize-boxSize+1);
				glVertex2i(j*boxSize+boxSize-1, i*boxSize-1);
				glEnd();
			}
		}
	}
	glColor3f(0.0, 0.0, 0.0);
	int wordCount = 0;
	for(int i = 0; i < words.size(); ++i) {
		Word temp = words[i];
		
		bool numberWritten = false;
		for(int j = 0; i != 0 && j < i; ++j) {
			if(temp.start.i == words[j].start.i && temp.start.j == words[j].start.j) {
				numberWritten = true;
			}
		}
		if(!numberWritten) {
			glRasterPos2i(temp.start.j*64+4, (width-temp.start.i)*64-10);

			int num = ++wordCount;
			string s = "";
			while(num != 0) {
				char c = '0';
				c += (num%10);
				num /= 10;
				s = c + s;
			}
			for(int j = 0; j < s.size(); ++j) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[j]);
			}
		}

		for(int j = 0; j < words[i].length; ++j) {
			if(words[i].dir == DOWN) {
				glRasterPos2i(temp.start.j*64+20, (width-temp.start.i-j)*64-44);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, words[i].w[j]);
			}
			else {
				glRasterPos2i((temp.start.j+j)*64+24, (width-temp.start.i)*64-40);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, words[i].w[j]);
			}
		}
	}
}

void Board::read(istream& in) {
	for(int i = 0; i < width; ++i) {
		for(int j = 0; j < width; ++j) {
			in >> board[i][j];
		}
	}

	setupWords();
}

// istream& operator>> (istream& in, Board& b) {
// 	for(int i = 0; i < b.width; ++i) {
// 		for(int j = 0; j < b.width; ++j) {
// 			in >> b.board[i][j];
// 		}
// 	}

// 	b.setupWords();

// 	return in;
// }

ostream& operator<< (ostream& out, Board& b) {
	for(int i = 0; i < b.width; ++i) {
		for(int j = 0; j < b.width; ++j) {
			out << b.board[i][j];
		}
		out << endl;
	}

	return out;
}