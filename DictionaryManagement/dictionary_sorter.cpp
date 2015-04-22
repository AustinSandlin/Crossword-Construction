#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct alpha_compare {
    bool operator()(const string& first, const string& second) {
        if(first.compare(second) < 0) {
        	return true;
        }
        return false;
    }
};

struct size_compare {
    bool operator()(const string& first, const string& second) {
        return first.size() < second.size();
    }
};

int main() {

	vector<string> list;
	ifstream infile;
	infile.open("dictionary_unsorted.txt");

	ofstream outfile;
	outfile.open("../dictionary_sorted.txt");

	string temp;
	while(infile >> temp){
		list.push_back(temp);
	}

	infile.close();

	size_compare s_comp;
	alpha_compare a_comp;

	stable_sort(list.begin(), list.end(), a_comp);
	stable_sort(list.begin(), list.end(), s_comp);

	for(int i = 0; i < list.size(); ++i) {
		outfile << list[i] << endl;
	}

	outfile.close();

	return 0;
}