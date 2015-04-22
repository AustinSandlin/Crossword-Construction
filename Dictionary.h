#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Word.h"

using namespace std;

class Dictionary {
	private:
		map<int, vector<Word> > wordMap;

	public:
		Dictionary();
		Dictionary(string);
		
		void open(string);
		vector<Word>& getWordsByLength(int);
};

#endif