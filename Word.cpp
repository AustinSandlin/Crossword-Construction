#include "Word.h"

Word::Word(Point p, int l, Direction d){
	start = p;
	length = l;
	dir = d;
}
Word::~Word(){
	
}

Direction Word::getDir(){
	return dir;
}

Point Word::getStart(){
	return start;
}

int Word::getLength(){
	return length;
}

void Word::setLength(int l){
	length = l;
}

void Word::clearWord() {
	w = "";
	for(int i = 0; i < length; ++i) {
		w += " ";
	}
}

void Word::setWord(string word) {
	w = word;
}

void Word::addIntersection(int index, Point p) {
	intersections.push_back(make_pair(index, p));
}

char Word::getIntersection(int index) {
	char toReturn = ' ';

	for(int i = 0; i < intersections.size(); ++i) {
		if(intersections[i].first == index) {
			if(dir == DOWN) {
				toReturn = w[intersections[i].second.i-start.i];
			}
			else if(dir == ACROSS) {
				toReturn = w[intersections[i].second.j-start.j];
			}
		}
	}

	return toReturn;
}

string Word::getWord() {
	return w;
}