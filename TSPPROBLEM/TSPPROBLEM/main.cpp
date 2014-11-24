#include <iostream>
#include <fstream>
#include "BranchAndBound.h"
#include "Path.h"
#include "TravellingSalesman.h"
#include "Timer.h"
void runSimulation(int, int);
int NUMBER_OF_SAMPLES = 5;
int NUMBER_OF_REPEATANCE = 5;

BranchAndBound BandB;
TravellingSalesman salesman;


int main(void) {
	for(int i = 4; i <= NUMBER_OF_SAMPLES; i++) {
		fstream fileWithCitiesMatrix;
		stringstream s;
		s << "komiwojazer"<<i<<".txt";
		fileWithCitiesMatrix.open(s.str(), ios::in);
		salesman.loadPaths(fileWithCitiesMatrix);
		runSimulation(NUMBER_OF_REPEATANCE, i);
		fileWithCitiesMatrix.close();

	}

	//fstream fileWithCitiesMatrix; 
	//TravellingSalesman salesman;
	//BranchAndBound BandB;
	//fileWithCitiesMatrix.open("komiwojazer5.txt", ios::in);
	//salesman.loadPaths(fileWithCitiesMatrix);
	//salesman.printPaths(std::cout);
	//Path p = BandB.BranchAndBoundAlgorithm(salesman);
	//cout << "path value = " << p.value << endl;
	//cout << "path: "<<p.path<<endl;


	//fileWithCitiesMatrix.close();
	getchar();
}

void runSimulation(int numberOfTimes, int count) {
	std::fstream dataToSave;
	stringstream s;
	s <<"data/symulacja-" << count << ".txt";
	dataToSave.open(s.str(), ios::trunc|ios::out);
	int sum = 0;

	for(int i = 0; i < numberOfTimes; i++) {
		cout << i << endl;
		Timer timer;
		timer.startTimer();
		//sum += simmulation.runAlgorithm().value;
		BandB.BranchAndBoundAlgorithm(salesman);
		double time = timer.endTimer();
		dataToSave << time << " ";
	}
	dataToSave.close();
	//return (float)sum/numberOfTimes;
}