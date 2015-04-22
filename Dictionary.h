#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class Dictionary {
	private:
		map<int, vector<string> > wordMap;

	public:
		Dictionary() {

		}
		Dictionary(string filename) {
			open(filename);
		}
		
		void open(string filename) {
			ifstream infile(filename.c_str());
			
			string temp;
			while(infile >> temp) {
				wordMap[temp.size()].push_back(temp);
			}
			
			infile.close();
		}
		vector<string> getWordsByLength(int length) {
			return wordMap[length];
		}
};