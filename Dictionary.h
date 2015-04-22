#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Dictionary {
	private:
		map<int, vector<string> > wordMap;

	public:
		Dictionary();
		Dictionary(string filename);
		
		void open(string filename);
		vector<string> getWordsByLength(int length);
};