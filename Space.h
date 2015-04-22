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
		int getLength() ;
};

#endif