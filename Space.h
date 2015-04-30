/* Author: Austin Sandlin & Victoria Chuba
 * Title: Crossword Solver
 * Description: This is the blank space in the crossword, it has the start
 *				location, the direction, as well as how long the word is.
 */

#ifndef _SPACE_H
#define _SPACE_H

struct Point {
	public:
		int i;
		int j;

		Point();
		Point(int a, int b);
		Point(const Point& p) ;
};

struct Space {
	private:
		Point start;
		Point direction;
		int length;
	
	public:
		Space(Point s, Point d, int l);
	
		Point getStart();	
		Point getDirection();
		int getLength();
};

#endif