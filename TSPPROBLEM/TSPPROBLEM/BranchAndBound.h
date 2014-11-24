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
			Node actualNodeInc = solutionTree.back();
			Node actualNodeExc = actualNodeInc;
			int localLowBoundry = actualNodeInc.getLowBoundry();
			solutionTree.pop_back();
			if(actualNodeInc.getNodeLevel() == 27) {
				int i = 0;
				i++;
			}

			actualNodeInc.addIncludedPath(possibleMoves[actualNodeInc.getNodeLevel()]);
			actualNodeExc.addExcludedPath(possibleMoves[actualNodeExc.getNodeLevel()]);

			if(actualNodeInc.getIncludedSize() > salesman.getNumberOfCities() + 1) {
				actualNodeInc.setIsCorrectNode(false);
			} else {
				lowBoundry2(actualNodeInc);
			}
			if(actualNodeExc.getIncludedSize() > salesman.getNumberOfCities() + 1) {
				actualNodeExc.setIsCorrectNode(false);
			} else {
				lowBoundry2(actualNodeExc);
			}

			if(actualNodeInc.isFinal() && actualNodeInc.isCorrectNode()) {
				int c = 0;
				c++;
				if(actualNodeInc.getLowBoundry() < bestSolutionNode.getLowBoundry()) {
					if(actualNodeInc.getLowBoundry() > 0)
						bestSolutionNode = actualNodeInc;
				}
			} else if(actualNodeInc.isCorrectNode() && actualNodeInc.getLowBoundry() >= localLowBoundry) {
				solutionTree.push_back(actualNodeInc);
				push_heap(solutionTree.begin(), solutionTree.end());
			}

			if(actualNodeExc.isFinal() && actualNodeExc.isCorrectNode()) {
				int c = 0;
				c++;
				if(actualNodeExc.getLowBoundry() < bestSolutionNode.getLowBoundry()) {
					if(actualNodeExc.getLowBoundry() > 0)
						bestSolutionNode = actualNodeExc;
				}
			} else if(actualNodeExc.isCorrectNode()&& actualNodeExc.getLowBoundry() >= localLowBoundry) {
				solutionTree.push_back(actualNodeExc);
				push_heap(solutionTree.begin(), solutionTree.end());
			}

		}
		//bestSolutionNode
		Path fin;
		fin.value = bestSolutionNode.getLowBoundry();
		fin.path = bestSolutionNode.getFinalPath();
		return fin;

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
		n.clearFinalPath();
		pair<pair<int, int>, pair<int, int>> smallestPaths;
		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			smallestPaths = find2IncludedOrSmallest(n, i);
			if(smallestPaths.first.first == -1 || smallestPaths.second.first == -1) {
				n.setIsCorrectNode(false);
			}

			if(!n.isCorrectNode()) {
				return;
			}
			pair<int, int> path1(i, smallestPaths.first.first);
			pair<int, int> path2(i, smallestPaths.second.first);
			n.addToFinalPath(path1);
			n.addToFinalPath(path2);
			sumOfPaths += smallestPaths.first.second;
			sumOfPaths += smallestPaths.second.second;
			
		}
		if(sumOfPaths > 0) {
			sumOfPaths /= 2;
		} else {
			int i = 0;
			int j = 1;
			i+=j;
		}

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
			if(end.first.first == -1 ) {
				end.second = second;
			} else {
				if(end.first != first)
					end.second = first;
				else
					end.second = second;
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
		int* counterFinal	 = new int[salesman.getNumberOfCities()];

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			counterIncluded[i] = 0;
			counterExcluded[i] = 0;
			counterFinal[i] = 0;
		}

		for(int i = 0; i < n.getExcludedSize(); i++) {
			counterExcluded[n.getExcludedAt(i).first]++;
			counterExcluded[n.getExcludedAt(i).second]++;
		}		
		
		for(int i = 0; i < n.getIncludedSize(); i++) {
			counterIncluded[n.getIncludedAt(i).first]++;
			counterIncluded[n.getIncludedAt(i).second]++;
		}
		int counter = 0;
		for each (pair<int, int> finalPair in n.getPath()) {
			//counterFinal[finalPair.first]++;
			counterFinal[finalPair.second]++;
		}


		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			if(counterIncluded[i] > 2) {
				n.setIsCorrectNode(false);
				break;
			}
		}

		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			//if all paths to the city besides one have been excluded 
			if(counterExcluded[i] > salesman.getNumberOfCities() - 2) {
				n.setIsCorrectNode(false);
				break;
			}
		}
		n.setIsFinal(true);
		for(int i = 0; i < salesman.getNumberOfCities(); i++) {
			//cout << counterFinal[i] << " ";

			if(counterFinal[i] != 2) {
				n.setIsFinal(false);
				break;
			}
		}
		if(n.isCorrectNode() && n.isFinal())
			uncheckIsCorrectIfHasOneLoopAndCreatePath(n);
		//cout << endl<<endl;

		delete[] counterIncluded;
		delete[] counterExcluded;
		delete[] counterFinal;
	}

	void uncheckIsCorrectIfHasOneLoopAndCreatePath(Node& n) {
		vector<pair<int, int>> allPaths = n.getPath();
		vector<int> overallPath;
		bool* checked = new bool[allPaths.size()];
		int* repeats = new int[salesman.getNumberOfCities()];
		for(int i = 0; i < allPaths.size(); i++) {
			checked[i] = false;
			if(i < salesman.getNumberOfCities())
				repeats[i] = 0;
		}

		overallPath.push_back(allPaths[0].first);
		overallPath.push_back(allPaths[0].second);
		checked[0] = true;
		repeats[allPaths[0].first]++;
		repeats[allPaths[0].second]++;
		while(overallPath.size() != salesman.getNumberOfCities()) {
			int actual = overallPath.back();
			int counter = -1;
  			for each(pair<int, int> path in allPaths) {
				if(!checked[++counter]) {
					if(actual == path.first && overallPath[overallPath.size() - 2] != path.second) {
						if(repeats[path.second] == 1 && overallPath.size() < allPaths.size()) {
							n.setIsCorrectNode(false);
							break;
						} 

						overallPath.push_back(path.second);
						checked[counter] = true;
						repeats[path.second]++;
						break;
					}
				}
			}
			if(!n.isCorrectNode()) {
				return;
			}
		}
		Path p;
		for each(int node in overallPath) {
			p.addIntToPath(node);
		}
		p.addIntToPath(overallPath.front());
		n.setOverallFinalPath(p.path);
		
		delete[] checked;
		delete[] repeats;

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