#include "Node.h"
#include "Path.h"
#include <algorithm>
#include "TravellingSalesman.h"

class BranchAndBound {
	TravellingSalesman salesman;
public:
	Path BranchAndBoundAlgorithm(TravellingSalesman p) {
		salesman = p;
		vector<pair<int, int>> possibleMoves;
		possibleMoves = findAllPossibleMoves(p.getNumberOfCities());
		Node bestSolutionNode;

		vector<Node> solutionTree; 
		Node treeRoot;
		lowBoundry2(treeRoot);
		solutionTree.push_back(treeRoot);
		make_heap(solutionTree.begin(), solutionTree.end());

		while(solutionTree.size()) {
			pop_heap(solutionTree.begin(), solutionTree.end());

			//if it is correct result check if it is best - if so remember it
			if(solutionTree.back().isFinal()) {
				Node solution = solutionTree.back();
				solutionTree.pop_back();
				if(solution.getLowBoundry() > bestSolutionNode.getLowBoundry()) {
					bestSolutionNode = solution;
				}

			//else find children of that node
			} else {
				Node actualNodeInc = solutionTree.back();
				Node actualNodeExc = actualNodeInc;
				solutionTree.pop_back();

				actualNodeInc.addIncludedPath(possibleMoves[actualNodeInc.getNodeLevel()]);
				actualNodeExc.addExcludedPath(possibleMoves[actualNodeExc.getNodeLevel()]);

				lowBoundry2(actualNodeInc);
				lowBoundry2(actualNodeExc);

				if(actualNodeInc.isCorrectNode() && actualNodeInc.getLowBoundry() >= treeRoot.getLowBoundry()) {
					solutionTree.push_back(actualNodeInc);
					push_heap(solutionTree.begin(), solutionTree.end());
				}

				if(actualNodeExc.isCorrectNode()&& actualNodeExc.getLowBoundry() >= treeRoot.getLowBoundry()) {
					solutionTree.push_back(actualNodeExc);
					push_heap(solutionTree.begin(), solutionTree.end());
				}
			}
		}
		
		return createPath(bestSolutionNode);
	}



	Path createPath(Node n) {
		Path end;
		int numberOfiterations = salesman.getNumberOfCities() + 1;
		int lastPosition = -1;

		//while(numberOfiterations--) {
		//	for(int i = 0; i < salesman.getNumberOfCities(); i++) {
		//		pair<int, int> pair = n.getPath()[i];
		//		if(pair.first == lastPosition) {
		//			//-TODO
		//		}
		//	}
		//}
		end.value = n.getLowBoundry();
		return end;
	}

	Node lowBoundry(Node n) {
		int pathValueCounter = 0;
		//counting included for each city
		int* cities = new int[salesman.getNumberOfCities()];
		//to checking if it's start vertex
		bool *start = new bool[salesman.getNumberOfCities()];
		int* groupOf = new int[salesman.getNumberOfCities()];
		int groupCounter = 0;
		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			cities[i] = 0;
			groupOf[i] = 0;
			start[i] = false;
		}

		for(int i = 0; i < n.getIncludedSize(); i++) {
			pair<int, int> citiesPair = n.getIncludedAt(i);
			cities[citiesPair.first]++;
			cities[citiesPair.second]++;

			if(groupOf[citiesPair.first] != 0 || groupOf[citiesPair.second] != 0) {
				if(groupOf[citiesPair.first] != 0 && groupOf[citiesPair.second] ==0) {
					groupOf[citiesPair.second] = groupOf[citiesPair.first];
				} else
					if(groupOf[citiesPair.first] == 0 && groupOf[citiesPair.second] != 0) {
						groupOf[citiesPair.first] = groupOf[citiesPair.second];
					} else {
						for(int j = 0; j < salesman.getNumberOfCities(); j++) {
							if(groupOf[citiesPair.second] > groupOf[citiesPair.first]) {
								if(groupOf[j] == groupOf[citiesPair.second]) {
									groupOf[j] = groupOf[citiesPair.first];
								} else {
									if(groupOf[j] > groupOf[citiesPair.second]) {
										groupOf[j]--;
									}
								}
							} else {
								if(groupOf[j] == groupOf[citiesPair.first]) {
									groupOf[j] = groupOf[citiesPair.second];
								} else {
									if(groupOf[j] > groupOf[citiesPair.first]) {
										groupOf[j]--;
									}
								}
							}
						}
						groupCounter--;
					}
			} else {
				start[citiesPair.first] = true;
				groupCounter++;
				groupOf[citiesPair.first] = groupCounter;
				groupOf[citiesPair.second] = groupCounter;
			}


			pathValueCounter += salesman.getPathValue(citiesPair.first, citiesPair.second);
		}
		//checking possibility of existence
		n.setIsCorrectNode(true);
		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			if(cities[i]>2) {
				n.setIsCorrectNode(false);
			}
		}

		int least = INT_MAX;
		if(n.isCorrectNode()) {
			for(int i = 0; i < salesman.getNumberOfCities(); i++) {
				//jeœli to nie koniec - w sumie to pewnie gdzies wyzej bedziesz sprawdzal,
				//bo nie liczy sie dla koncowego przypadku ograniczenia tylko wartosc...
				if(n.getIncludedSize() != salesman.getNumberOfCities()) {
					if(cities[i] == 0) {
						for(int j = 0; j < salesman.getNumberOfCities(); j++) {
							if(i != j && salesman.getPathValue(i, j) < least && (cities[j] ==0 || start[j] == true)) {
								//checking excluded
								if(!isExcluded(n, i, j)) {
									least = salesman.getPathValue(i, j);
								}
							}
						}
						pathValueCounter += least;
						least = INT_MAX;
					} else
						if(cities[i] == 1 && !start[i]) {
							for(int j = 0; j < salesman.getNumberOfCities(); j++) {
								if(i != j && salesman.getPathValue(i, j) < least && (cities[j] == 0 
										|| start[j] == true) && groupOf[i]!= groupOf[j]) {
								
									if(!isExcluded(n, i, j)) {
										least = salesman.getPathValue(i, j);
									}
								}
							}
							pathValueCounter += least;
							least = INT_MAX;
						}
				}
			}
			n.setLowBoundry(pathValueCounter);
		}
		return n;
	}


	bool isExcluded(Node n, int start, int end) {
		bool isExcluded = false;
		for(int k = 0; k < n.getExcludedSize(); k++) {
			pair<int, int> cities = n.getExcludedAt(k);
			if(cities.first == start) {
				if(cities.second == end) {
					isExcluded = true;
					break;
				}
			}
			if(cities.second == start) {
				if(cities.first == end) {
					isExcluded = true;
					break;
				}
			}
		}
		return isExcluded;
	}



	void lowBoundry2(Node &n) {
		float sumOfPaths = 0;

		pair<pair<int, int>, pair<int, int>> smallestPaths;
		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			smallestPaths = find2IncludedOrSmallest(n, i);
			if(!n.isCorrectNode()) {
				return;
			}
			sumOfPaths += smallestPaths.first.second;
			sumOfPaths += smallestPaths.second.second;
		}
		sumOfPaths /= 2;
		n.setLowBoundry(sumOfPaths);
		setIsFinalAndIsCorrectNodeIfNecessary(n);
	}

	//@return 2 pairs of cities in format: city number-cost
	pair<pair<int, int>, pair<int,int>> find2IncludedOrSmallest(Node &n, int from) {
		int firstLowest = INT_MAX;
		int firstIndex = -1;
		int secondLowest = INT_MAX;
		int secondIndex = -1;

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			int value = salesman.getPathValue(from, i);

			if(value == 0 || isExcluded(n, from, i))
				continue;
			
			if(value < firstLowest) {				
				secondLowest = firstLowest;
				secondIndex = firstIndex;
				firstLowest = value;
				firstIndex = i;
			} else if(value < secondLowest) {
				secondLowest = value;
				secondIndex = i;
			}
		}
		pair<int, int> first(firstIndex, firstLowest);
		pair<int, int> second(secondIndex, secondLowest);

		
		pair<pair<int, int>, pair<int, int>> end = getIncluded(n, from);
		if(end.second.first == -1 ) {
			if(end.first.first == -1) {
				end.second = second;
			} else {
				end.second = first;
			}
		}

		if(end.first.first == -1) {
			end.first = first;
		}

		return end;
	}


	void setIsFinalAndIsCorrectNodeIfNecessary(Node &n) {
		int* counterIncluded = new int[salesman.getNumberOfCities()];
		int* counterExcluded = new int[salesman.getNumberOfCities()];

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			counterIncluded[i] = 0;
			counterExcluded[i] = 0;
		}

		for(int i = 0; i < n.getExcludedSize(); i++) {
			counterExcluded[n.getExcludedAt(i).first]++;
			counterExcluded[n.getExcludedAt(i).second]++;
		}		
		
		for(int i = 0; i < n.getIncludedSize(); i++) {
			counterIncluded[n.getIncludedAt(i).first]++;
			counterIncluded[n.getIncludedAt(i).second]++;
		}

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			if(counterIncluded[i] > 2) {
				n.setIsCorrectNode(false);
				break;
			}

			if(counterIncluded[i] < 2) {
				n.setIsFinal(false);
			}
		}

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			//if all paths to the city besides one have been excluded 
			if(counterExcluded[i] > salesman.getNumberOfCities() - 2) {
				n.setIsCorrectNode(false);
				break;
			}

		}
	}

	pair<pair<int, int>, pair<int, int>> getIncluded(Node &n, int start) {
		pair<int, int> result1(-1, -1);
		pair<int, int> result2(-1, -1);
		int counter = 0;

		for(int k = 0; k < n.getIncludedSize(); k++) {
			pair<int, int> cities = n.getIncludedAt(k);
			if(cities.first == start) {
				if(counter == 0) {
					result1.first = cities.second;
					result1.second = salesman.getPathValue(start, cities.second);
					counter++;
				} else if(counter == 1) {
					result2.first = cities.second;
					result2.second = salesman.getPathValue(start, cities.second);
					counter++;
				} else {
					n.setIsCorrectNode(false);
					break;
				}

			}
			//if(cities.second == start) {
			//	if(counter == 0) {
			//		result1.first = cities.second;
			//		result1.second = salesman.getPathValue(start, cities.second);
			//		counter++;
			//	} else if(counter == 1) {
			//		result2.first = cities.first;
			//		result2.second = salesman.getPathValue(start, cities.first);
			//		counter++;
			//	} else {
			//		n.setIsCorrectNode(false);
			//		break;
			//	}
			//}
		}

		pair<pair<int, int>, pair<int, int>> result(result1, result2);
		return result;
	}


	vector<pair<int, int>> findAllPossibleMoves(const int numberOfCities) {
		vector<pair<int, int>> paths;

		for(int i = 0; i <= numberOfCities; i++) {
			for(int j = i+1; j < numberOfCities; j++) {
				pair<int, int> path(i, j);
				paths.push_back(path);
			}
		}

		return paths;
	
	}
};