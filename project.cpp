/* Author: Austin Sandlin & Victoria Chuba
 * Title: Crossword Solver
 * Description: This file is the main file that runs the program and deals with
 *              the graphics behind the program.
 */

#include <iostream>
#include <GLUT/glut.h>
#include "Crossword.h"

using namespace std;

// Screen sizes preset. Should work on smaller resolution monitors...
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 868;

// Simple enumerated data type for states.
enum GAME_STATE{EMPTY_BOARD, VALID, INVALID, PROCESSING};

// Global game state for program state changing
GAME_STATE state;
// Global crossword puzzle.
Crossword* puzzle;

void init(string board_file, string dict_file) {
    // Create the puzzle with the board and word list file.
	puzzle = new Crossword(board_file, dict_file);

    // Perform basic glut window setup
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CROSSWORD CONSTRUCTION");
	glClear(GL_COLOR_BUFFER_BIT);

    // Set the background as black. This is VERY important for the black background of the crossword.
	glClearColor(0.0, 0.0, 0.0, 0.0);

    // Switch to the projection matrix to set the orth size.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Declare the ortho with the parameters given. The -100 allocates a 100 pixel space at the bottom for state output.
    gluOrtho2D(0, boxSize*puzzle->getWidth(), -100, boxSize*puzzle->getWidth());
    
    // Switch to modelview for drawing.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboardCallback(unsigned char key, int x, int y) {
    // We quit if the user hits q.
	if(key == 'q' || key == 'Q') {
		exit(1);
	}
    // We reset the board if the user hits r.
    else if(key == 'r' || key == 'R') {
        puzzle->reset();
        state = EMPTY_BOARD;
    }
    // We shuffle the words if the user hits s.
    else if(key == 's' || key == 'S') {
        puzzle->shuffle();
        state = EMPTY_BOARD;
    }
    // We switch states to processing if the user hits v.
    else if(key == 'v' || key == 'V') {
        state = PROCESSING;
    }
    glutPostRedisplay();
}

void displayCallback() {
    // OpengGl window stuff.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the board WITHOUT swapping buffers.
    puzzle->draw(false);

    // Draw over the currently writen state at the bottom with a black box.
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(0, -100);
    glVertex2i(boxSize*puzzle->getWidth(), -100);
    glVertex2i(boxSize*puzzle->getWidth(), 0);
    glVertex2i(0, 0);
    glEnd();

    // Go through the possible states of the board.
    string temp;
    if(state == EMPTY_BOARD) {
        // If the state is empty, simple write that state in white to the screen.
        glColor3f(1.0, 1.0, 1.0);
        temp = "EMPTY";
        glRasterPos2i(SCREEN_WIDTH/2, -38);
        for(int i = 0; i < temp.size(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
        }
    }
    else if(state == PROCESSING) {
        // If the state is processing, write processing to the screen in red and
        // then attempt to solve the puzzle. Calling it in the glut display
        // callback actually allows us to (in the recursive function) display
        // words as they are added and removed. glutPostRedisplay is called
        // because the state will have changed when it's finished processing.
        glColor3f(1.0, 0.0, 0.0);
        temp = "PROCESSING";
        glRasterPos2i(SCREEN_WIDTH/2, -38);
        for(int i = 0; i < temp.size(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
        }
        if(puzzle->isValid()) {
            state = VALID;
        }
        else {
            state = INVALID;
        }
        glutPostRedisplay();
    }
    else if(state == VALID) {
        // If it's valid, write valid in a very happy green.
        glColor3f(0.0, 1.0, 0.0);
        temp = "VALID";
        glRasterPos2i(SCREEN_WIDTH/2, -38);
        for(int i = 0; i < temp.size(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
        }
    }
    else if(state == INVALID) {
        // If it's invalid, write invalid in a very sad red.
        glColor3f(1.0, 0.0, 0.0);
        temp = "INVALID";
        glRasterPos2i(SCREEN_WIDTH/2, -38);
        for(int i = 0; i < temp.size(); ++i) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i]);
        }
    }

    // Swap buffers to display what's been drawn to the screen.
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // call the glut initializer function.
	glutInit(&argc, argv);

    // String variables for filenames of the instance variables.
    string board_file, dict_file;

    // If the instance variable files are given in the command line, ask for them.
    if(argc < 3) {
        cout << "Please enter a filename for the crossword board: " << endl;
        cin >> board_file;
        cout << "Please enter a filename for the dictionary: " << endl;
        cin >> dict_file;
    }
    else {
        board_file = argv[1];
        dict_file = argv[2];
    }

    // Call the custom made initialization function with the filenames given.
	init(board_file, dict_file);

    // Register the keyboard and display callbacks for OpenGL.
    glutKeyboardFunc(keyboardCallback);
    glutDisplayFunc(displayCallback);

    // Start the glut event listening.
    glutMainLoop();

	return 0;
}