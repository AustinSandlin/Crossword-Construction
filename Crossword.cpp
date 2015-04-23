
#include "Crossword.h"
/* Function for comparing spaces. */
bool compareSpaces(Space i, Space j) {
    return j.getLength() < i.getLength();
}

void Crossword::initialize() {
    /* Find all the spaces on the board. 
     */
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < width; ++j) {
            if(board[i][j] == BLANK && ((i-1 < 0 || ((i-1) >= 0 && board[i-1][j] == FILLED)) && (i+1) < width && board[i+1][j] == BLANK)) {
                int length = 1;
                while(i+length < width && board[i+length][j] == BLANK) {
                    ++length;
                }
                spaces.push_back(Space(Point(i, j), Point(1, 0), length));
            }
            if(board[i][j] == BLANK && ((j-1 < 0 || ((j-1) >= 0 && board[i][j-1] == FILLED)) && (j+1) < width && board[i][j+1] == BLANK)) {
                int length = 1;
                while(j+length < width && board[i][j+length] == BLANK) {
                    ++length;
                }
                spaces.push_back(Space(Point(i, j), Point(0, 1), length));
            }
        }
    }

    /* Sort the spaces, largest first. This is a general improvement in the
     * solution finding, since there usually are fewer large words. 
     */
    stable_sort(spaces.begin(), spaces.end(), compareSpaces);
}

bool Crossword::fillPuzzle(int index) {
    /* If we reached the end of the spaces vector, we found a solution.
     */
    if(index == spaces.size()) {
        return true;
    }
    
    // Fetch the length for fewer map lookups.
    int length = spaces[index].getLength();

    // For each word that matches the slot's length:
    for(int i = 0; i < wordMap[length].size(); ++i) {
        // And if the word can fit in the slot:
        if(canWordFit(wordMap[length][i], spaces[index])) {
            // Insert the word into the slot.
            insertWord(wordMap[length][i], spaces[index]);

            // Draw the board. This is only possible because 
            draw(true);

            if(fillPuzzle(index+1)) {
                return true;
            }

            removeWord(wordMap[length][i], spaces[index]);

            draw(true);
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

    infile.close();
    infile.clear();

    infile.open(dict_file.c_str());
    
    string temp;
    while(infile >> temp) {
        wordMap[temp.size()].push_back(Word(temp));
    }
    
    infile.close();

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
            if(board[i][j] != '1') {
                board[i][j] = '0';
            }
        }
    }
    map<int, vector<Word> >::iterator it = wordMap.begin();
    while(it != wordMap.end()){
        for(int i = 0; i < it->second.size(); ++i) {
            it->second[i].setUsed(false);
        }
        ++it;
    }
}

void Crossword::shuffle() {
    reset();
    map<int, vector<Word> >::iterator it = wordMap.begin();
    while(it != wordMap.end()){
        random_shuffle(it->second.begin(), it->second.end());
        ++it;
    }
}

bool Crossword::canWordFit(Word& w, Space s) {
    if(w.isUsed()) {
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

void Crossword::draw(bool swapBuffers) {
    for(int i = width; i > 0; --i) {
        for(int j = 0; j < width; ++j) {
            if(board[width-i][j] != FILLED) {
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
            if(board[width-i][j] != BLANK) {
                glColor3f(0.0, 0.0, 0.0);
                glRasterPos2i(j*boxSize+24, i*boxSize-40);
                char temp = board[width-i][j];
                temp &= 0xFFDF;
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp);
            }
        }
    }

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(0, -100);
    glVertex2i(boxSize*width, -100);
    glVertex2i(boxSize*width, 0);
    glVertex2i(0, 0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    string temp = "PROCESSING";
    glRasterPos2i(384, -38);
    for(int i = 0; i < temp.size(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
    }

    if(swapBuffers) {
        glutSwapBuffers();
    }

    /*
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
            glRasterPos2i(spaces[i].getStart().j*boxSize+4, (width-spaces[i].getStart().i)*boxSize-12);

            int num = ++wordCount;
            string s = "";
            while(num != 0) {
                char c = BLANK;
                c += (num%10);
                num /= 10;
                s = c + s;
            }
            for(int j = 0; j < s.size(); ++j) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[j]);
            }
        }
    }
    */
}