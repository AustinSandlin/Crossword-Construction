#include <vector>
#include <string>

using namespace std;

enum Direction{ACROSS, DOWN};

struct Point {
	int i;
	int j;

	Point() {
		i = -1;
		j = -1;
	}

	Point(int x, int y) {
		i = x;
		j = y;
	}
};

class Word {
	public:	
		int length;
		string w;

		Point start;
		Direction dir;
		vector<pair<int, Point> > intersections;

		Word(Point, int, Direction);
		~Word();

		void clearWord();
		void setWord(string);
		void addIntersection(int, Point);

		int getLength();
		Point getStart();
		string getWord();
		Direction getDir();
		char getIntersection(int);

		void setLength(int);
};