#include "Dictionary.h"

Dictionary::Dictionary() {
	
}

Dictionary::Dictionary(string filename) {
	open(filename);
}

void Dictionary::open(string filename) {
	ifstream infile;
	infile.open(filename.c_str());
	
	string temp;
	while(infile >> temp) {
		wordMap[temp.size()].push_back(temp);
	}
	
	infile.close();
}

vector<string> Dictionary::getWordsByLength(int length) {
	return wordMap[length];
}
