#include <iostream>
#include <fstream>
#include "BranchAndBound.h"
#include "Path.h"
#include "TravellingSalesman.h"

int main(void) {

	fstream fileWithCitiesMatrix; 
	TravellingSalesman salesman;
	BranchAndBound BandB;
	fileWithCitiesMatrix.open("komiwojazer1.txt", ios::in);
	salesman.loadPaths(fileWithCitiesMatrix);
	salesman.printPaths(std::cout);
	Path p = BandB.BranchAndBoundAlgorithm(salesman);
	cout << "path value = " << p.value << endl;



	fileWithCitiesMatrix.close();
	getchar();
}