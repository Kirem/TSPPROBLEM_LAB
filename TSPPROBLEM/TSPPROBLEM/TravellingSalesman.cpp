#include "TravellingSalesman.h"
#include <istream>
#include <ostream>
#include <string>
#include <sstream>
TravellingSalesman::TravellingSalesman():numberOfCities(0) {}

TravellingSalesman::~TravellingSalesman(){}


void TravellingSalesman::loadPaths(istream& stream) {
		string checker;
		stream >> checker;
		if(checker.compare("NAME:") == 0) {
			loadSpecialPaths(stream);
		} else {
			std::istringstream stringStream(checker);
			int size;
			stringStream >> size;
			numberOfCities = size;
			loadNormalPaths(stream);
		}


	}


void TravellingSalesman::loadNormalPaths(istream& stream) {
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

void TravellingSalesman::generateRandomPath(int nrOfCities){
	numberOfCities = nrOfCities;
	random_device generator;
	uniform_int_distribution<int> distribution(1, numberOfCities);
	for (int i = 0; i < numberOfCities; i++) {
		vector<int> n;
		pathsValue.push_back(n);
		for (int j = 0; j < numberOfCities; j++) {
			if (i == j){
				pathsValue[i].push_back(-1);
			}
			else{
				if (j>i){
					pathsValue[i].push_back(distribution(generator));
				}
				else{
					pathsValue[i].push_back(pathsValue[j][i]);
				}
			}
		}
	}

}

void TravellingSalesman::loadSpecialPaths(istream& stream) {
	string s;
	while(s.compare("DIMENSION:") != 0) {
		stream >> s;
	}
	int size;
	stream >> size;
	this->numberOfCities = size;
	pathsValue.clear();
	while(s.compare("EDGE_WEIGHT_SECTION") != 0) {
		stream >> s;
	}
	pathsValue.resize(size);

	for(int i = 0; i < size; i++) {
		pathsValue[i].resize(size);
		for(int j = 0; j < i + 1; j++) {
			int value;
			stream >> value;
			pathsValue[i][j] = pathsValue[j][i] = value;
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

int TravellingSalesman::getNumberOfCities() {
	return numberOfCities;
}