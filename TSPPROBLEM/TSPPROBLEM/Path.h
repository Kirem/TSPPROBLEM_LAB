#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Path {
public:
	int value;
	string path;
	void addIntToPath(int a) {
		ostringstream s;
		s << path << " " <<a;

	}

	void printPath() {
		cout << path;
	}
};