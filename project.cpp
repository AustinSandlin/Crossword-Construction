#include <iostream>
#include <GLUT/glut.h>
#include "Crossword.h"

using namespace std;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 768;

enum GAME_STATE{EMPTY_BOARD, };

Crossword* puzzle;

void init(string board_file, string dict_file) {
	puzzle = new Crossword(board_file, dict_file);

	// cout << "Validity Check: " << puzzle->isValid() << endl;

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("CROSSWORD CONSTRUCTION");
	// glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
    // glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 64*puzzle->getWidth(), 0, 64*puzzle->getWidth());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboardCallback(unsigned char key, int x, int y) {
	if(key == 'q' || key == 'Q') {
		exit(1);
	}
    else if(key == 's' || key == 'S') {
        if(puzzle->isValid()) {
            cout << "valid" << endl;
        }
        else {
            cout << "invalid" << endl;
        }
        glutPostRedisplay();
    }
}

void displayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	puzzle->draw();

    glutSwapBuffers();

    glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

    string board_file, dict_file;
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
	init(board_file, dict_file);

    glutKeyboardFunc(keyboardCallback);
    glutDisplayFunc(displayCallback);
    // glutTimerFunc(16, updateTimerCallback, 0);

    glutMainLoop();

	return 0;
}