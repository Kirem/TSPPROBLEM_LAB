#include "TravellingSalesman.h"
#include <istream>
#include <ostream>
TravellingSalesman::TravellingSalesman():numberOfCities(0) {}

TravellingSalesman::~TravellingSalesman(){}

void TravellingSalesman::loadPaths(istream& stream) {
	stream >> numberOfCities;

	for(int i = 0; i < numberOfCities; i++) {
		vector<int> n;
		pathsValue.push_back(n);
		for(int j = 0; j < numberOfCities; j++) {
			int value;
			stream >> value;
			pathsValue[i].push_back(value);
		}
	}
}

void TravellingSalesman::printPaths(ostream& stream) {

	for(int i = 0; i < numberOfCities; i++) {
		for(int j = 0; j < numberOfCities; j++) {
			stream << pathsValue[i][j]<< "	";
		}
		stream << endl;
	}
}

int TravellingSalesman::getPathValue(int fromCity, int toCity) {
	return pathsValue[fromCity][toCity];
}