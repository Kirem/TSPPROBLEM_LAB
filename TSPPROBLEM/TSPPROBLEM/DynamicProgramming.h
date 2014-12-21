#include "TravellingSalesman.h"
#include "Path.h"

class DynamicProgramming{
	Path finally;
	TravellingSalesman salesman;
	vector<int> citiesToVisit;
	

public:
	Path DynamicProgrammingAlgorithm(TravellingSalesman t){
		int numOfCities = t.getNumberOfCities();
		salesman = t;
		
		for (int i = 1; i < numOfCities; i++){		
			citiesToVisit.push_back(i);
		}

		return getSolution(0, citiesToVisit);


	}

	Path getSolution(int k, vector<int> citiesLeft){
		int smallestPath = INT_MAX;
		vector<Path> paths;
		Path smallest;


		if (citiesLeft.size() == 1){
			smallest.value = salesman.getPathValue(0, citiesLeft[0]);
			smallest.addIntToPath(0);
			smallest.addIntToPath(citiesLeft[0]);
			return smallest;
		}
		else{
			for (int i = 0; i < citiesLeft.size(); i++){
				vector<int> citiesWithoutI;
				for (int j = 0; j < citiesLeft.size(); j++){
					if (i != j){
						citiesWithoutI.push_back(citiesLeft[j]);
					}
				}

			
				if (k != citiesLeft[i]){
					Path pom = getSolution(citiesLeft[i], citiesWithoutI);		
					int current = salesman.getPathValue(k, citiesLeft[i]) + pom.value;
				
					if (citiesWithoutI.size() == 2){
						current += salesman.getPathValue(citiesWithoutI[0], citiesWithoutI[1]);
					}
					if (current < smallestPath){
						pom.addIntToPath(citiesLeft[i]);
						pom.value = current;
						smallest = pom;
						smallestPath = current;

					}
				}

			}

			return smallest;
		}
	}


};