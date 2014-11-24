#pragma once
#include <vector>

using namespace std;
	 
class TravellingSalesman {
	int numberOfCities;
	vector<vector<int>> pathsValue;
	void loadNormalPaths(istream&);
	void loadSpecialPaths(istream&);
public:
	TravellingSalesman();
	~TravellingSalesman();
	void loadPaths(istream&);
	void printPaths(ostream&);
	int getPathValue(int, int);
	int getNumberOfCities();
};