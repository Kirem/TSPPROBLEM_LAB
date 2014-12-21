#include <iostream>
#include <fstream>
#include "BranchAndBound.h"
#include "Path.h"
#include "TravellingSalesman.h"
#include "Timer.h"
#include "DynamicProgramming.h"

void runSimulation(int, int);
bool menu();
int NUMBER_OF_SAMPLES = 5;
int NUMBER_OF_REPEATANCE = 100;

BranchAndBound BandB;
TravellingSalesman salesman;
DynamicProgramming Dyn;


int main(void) {
//	for(int i = 4; i < NUMBER_OF_SAMPLES; i++) {
//		fstream fileWithCitiesMatrix;
//		stringstream s;
//		s << "komiwojazer"<<4<<".txt";
//		fileWithCitiesMatrix.open(s.str(), ios::in);
//		salesman.loadPaths(fileWithCitiesMatrix);
//		salesman.generateRandomPath(7);
//		salesman.printPaths(cout);
//		runSimulation(NUMBER_OF_REPEATANCE, 7);		//czy jakieœ 7, 12, 17, 22, 27? czy wieksze? ja nie wiem jak to pojdzie -.-
//		runSimulation(NUMBER_OF_REPEATANCE, 8);
//		runSimulation(NUMBER_OF_REPEATANCE, 9);
//		runSimulation(NUMBER_OF_REPEATANCE, 10);
//		runSimulation(NUMBER_OF_REPEATANCE, 11);
//		runSimulation(NUMBER_OF_REPEATANCE, 12);
//		fileWithCitiesMatrix.close();

		while (menu());



//		Path p = BandB.BranchAndBoundAlgorithm(salesman);
//		Path p = Dyn.DynamicProgrammingAlgorithm(salesman);

//		cout << "path value = " << p.value << endl;
//		cout << "path: "<<p.path<<endl;



//	}

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


bool menu(){

	int wybor;
	cout << "\t\tProjektowanie efektywnych algorytmow" << endl << endl;
	cout << "Implementacja i analiza efektywnosci algorytmu programowania dynamicznego dla problemu komiwojazera." << endl << endl;
	cout << "1. Wczytaj z pliku \n";
	cout << "2. Uzyj domyslnego pliku \n";
	cout << "3. Wyswietl macierz sasiedztwa \n";
	cout << "4. Algorytm programowania dynamicznego \n";
	cout << "5. Koniec \n";

	cin >> wybor;
	string sciezka;
	fstream fileWithCitiesMatrix;
	Path p;

	switch (wybor){

	case 1:
		cout << endl << endl;
		cout << "Podaj sciezke do pliku dla problemu komiwojazera:\n";
		cin.clear();
		cin >> sciezka;

		
		fileWithCitiesMatrix.open(sciezka, ios::in);
		salesman.loadPaths(fileWithCitiesMatrix);
		fileWithCitiesMatrix.close();
		return true;

	case 2:

		sciezka = "komiwojazer1.txt";
		fileWithCitiesMatrix.open(sciezka, ios::in);
		salesman.loadPaths(fileWithCitiesMatrix);
		fileWithCitiesMatrix.close();
		return true;
	
	case 3:
		salesman.printPaths(cout);
		return true;

	case 4:
		p = Dyn.DynamicProgrammingAlgorithm(salesman);

		cout << "path value = " << p.value << endl;
		cout << "path: "<<p.path<<endl;
		return true;
		
	case 5:
		return false;
	default:
		menu();
	}
	return true;

}

void runSimulation(int numberOfTimes, int count) {
	std::fstream dataToSave;
	stringstream s;
	s <<"data/symulacja-" << count << ".txt";
	dataToSave.open(s.str(), ios::trunc|ios::out);
	int sum = 0;

	for(int i = 0; i < numberOfTimes; i++) {
		TravellingSalesman salesman;
		cout << i << endl;
		salesman.generateRandomPath(count);
		Timer timer;
		timer.startTimer();
//		sum += simmulation.runAlgorithm().value;
		Dyn.DynamicProgrammingAlgorithm(salesman);
		double time = timer.endTimer();
		dataToSave << time << " ";
	}
	dataToSave.close();
	//return (float)sum/numberOfTimes;
}