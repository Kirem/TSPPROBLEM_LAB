#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Path {
public:
	int value;
	string path;
	Path(const Path& p) {
		path = p.path;
		value = p.value;
	}

	Path() {
		value = 0;
		path = "";
	}
	void addIntToPath(int a) {
		ostringstream s;
		s << path << " " <<a;
		path = s.str();

	}

	void printPath() {
		cout << path;
	}
};