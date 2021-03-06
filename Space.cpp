/* Author: Austin Sandlin & Victoria Chuba
 * Title: Crossword Solver
 * Description: This is the blank space in the crossword, it has the start
 *				location, the direction, as well as how long the word is.
 */

#include "Space.h"

Point::Point() {
	i = 0;
	j = 0;
}

Point::Point(int a, int b) {
	i = a;
	j = b;
}

Point::Point(const Point& p) {
	i = p.i;
	j = p.j;
}

Space::Space(Point s, Point d, int l) {
	start = s;
	direction = d;
	length = l;
}

Point Space::getStart() {
	return start;
}

Point Space::getDirection() {
	return direction;
}

int Space::getLength() {
	return length;
}