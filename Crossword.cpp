#include "Crossword.h"

void Crossword::initialize() {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < width; ++j) {
            if(board[i][j] == '0' && ((i-1 < 0 || ((i-1) >= 0 && board[i-1][j] == '1')) && (i+1) < width && board[i+1][j] == '0')) {
                int length = 1;
                while(i+length < width && board[i+length][j] == '0') {
                    ++length;
                }
                spaces.push_back(Space(Point(i, j), Point(1, 0), length));
            }
            if(board[i][j] == '0' && ((j-1 < 0 || ((j-1) >= 0 && board[i][j-1] == '1')) && (j+1) < width && board[i][j+1] == '0')) {
                int length = 1;
                while(j+length < width && board[i][j+length] == '0') {
                    ++length;
                }

                spaces.push_back(Space(Point(i, j), Point(0, 1), length));
            }
        }
    }
}

bool Crossword::fillPuzzle(int index) {
    if(index == spaces.size()) {
        return true;
    }
    
    vector<Word> words = dict.getWordsByLength(spaces[index].getLength());

    //DON'T TRY EVERY WORD, TRY WORDS THAT FIT THIS ONE
    for(int i = 0; i < words.size(); ++i) {
        if(canWordFit(words[i], spaces[index])) {
            insertWord(words[i], spaces[index]);

            if(fillPuzzle(index+1)) {
                return true;
            }
            removeWord(words[i], spaces[index]);
        }
    }
    return false;
}

Crossword::Crossword(string board_file, string dict_file) {
    // *TODO* Add file checking.
    ifstream infile;
    infile.open(board_file.c_str());

    int length;
    infile >> length;

    width = length;
    board = new char*[width];
    numCharsUsed = new int*[width];
    for(int i = 0; i < width; ++i) {
        board[i] = new char[width];
        numCharsUsed[i] = new int[width];
        for(int j = 0; j < width; ++j) {
            infile >> board[i][j];
            numCharsUsed[i][j] = 0;
        }
    }

    dict.open(dict_file.c_str());

    initialize();
}

Crossword::~Crossword() {
    for(int i = 0; i < width; ++i) {
        delete[] board;
        delete[] numCharsUsed;
    }
    delete board;
    delete numCharsUsed;
}

bool Crossword::isValid() {
    reset();
    return fillPuzzle(0);
}

int Crossword::getWidth() {
    return width;
}

void Crossword::reset() {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < width; ++j) {
            numCharsUsed[i][j] = 0;
        }
    }
    
    initialize();
}

bool Crossword::canWordFit(Word& w, Space s) {
    if(w.getWord().size() != s.getLength() || w.isUsed()) {
        return false;
    }
    Point position = s.getStart();
    
    for(int i = 0; i < s.getLength(); ++i) {
        if(board[position.i][position.j] != BLANK &&
           board[position.i][position.j] != w.getWord()[i]) {
            return false;
        }
        position.i += s.getDirection().i;
        position.j += s.getDirection().j;
    }
    return true;
}

void Crossword::insertWord(Word& w, Space s) {
    Point position = s.getStart();
    
    for(int i = 0; i < s.getLength(); ++i) {
        board[position.i][position.j] = w.getWord()[i];
        ++numCharsUsed[position.i][position.j];
        position.i += s.getDirection().i;
        position.j += s.getDirection().j;
    }
    
    w.setUsed(true);
}

void Crossword::removeWord(Word& w, Space s) {
    Point position = s.getStart();
    
    for(int i = 0; i < s.getLength(); ++i) {
        --numCharsUsed[position.i][position.j];
        if(numCharsUsed[position.i][position.j] == 0) {
            board[position.i][position.j] = BLANK;
        }
        position.i += s.getDirection().i;
        position.j += s.getDirection().j;
    }
    
    w.setUsed(false);
}

void Crossword::draw() {
    for(int i = width; i > 0; --i) {
        for(int j = 0; j < width; ++j) {
            if(board[width-i][j] != '1') {
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
            if(board[width-i][j] != '0') {
                glColor3f(0.0, 0.0, 0.0);
                glRasterPos2i(j*boxSize+24, i*boxSize-40);
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, board[width-i][j]);
            }
        }
    }
    glColor3f(0.0, 0.0, 0.0);
    int wordCount = 0;
    for(int i = 0; i < spaces.size(); ++i) {
        bool numberWritten = false;
        for(int j = 0; i != 0 && j < i; ++j) {
            if(spaces[i].getStart().i == spaces[j].getStart().i && spaces[i].getStart().j == spaces[j].getStart().j) {
                numberWritten = true;
            }
        }
        if(!numberWritten) {
            glRasterPos2i(spaces[i].getStart().j*boxSize+4, (width-spaces[i].getStart().i)*boxSize-10);

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
    }
}