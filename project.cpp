#include <iostream>
#include <GLUT/glut.h>
#include "Crossword.h"

using namespace std;

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 768;

Crossword* puzzle;

void init(string filename) {
	puzzle = new Crossword(filename);

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
}

void displayCallback() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	puzzle->draw();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

    string filename;
    if(argc < 2) {
        cout << "Please enter a filename: " << endl;
        cin >> filename;
    }
    else {
        filename = argv[1];
    }
	init(filename);

    glutKeyboardFunc(keyboardCallback);
    glutDisplayFunc(displayCallback);
    // glutTimerFunc(16, updateTimerCallback, 0);

    glutMainLoop();

	return 0;
}