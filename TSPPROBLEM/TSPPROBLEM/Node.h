#include <string>
#include <vector>

using namespace std;
class Node {
	bool isPossible;
	float lowBoundry;
	bool finalNode;
	vector<pair<int, int>> included;
	vector<pair<int, int>> excluded;
	vector<pair<int, int>> path;
public:
	Node(const Node& n) {
		included = n.included;
		excluded = n.excluded;
		lowBoundry = n.lowBoundry;
		isPossible = n.isPossible;
		path = n.path;
		finalNode = n.finalNode;
	}

	Node() {
		isPossible = true;
		finalNode = true;
		lowBoundry = INT_MAX;
	}

	~Node() {}

	void addIncludedPath(pair<int, int> p) {
		included.push_back(p);
	}

	void addExcludedPath(pair<int, int> p) {
		excluded.push_back(p);
	}	
	
	void addToFinalPath(pair<int, int> p) {
		path.push_back(p);
	}


	vector<pair<int, int>> getPath() {
		return path;
	}

	bool isFinal() {
		return finalNode;
	}

	void setIsFinal(bool finalNode) {
		this->finalNode = finalNode;
	}

	int getLowBoundry() {
		return lowBoundry;
	}


	//used to create min heap
	bool operator<(const Node &n) {
		return lowBoundry > n.lowBoundry;
	}

	int getNodeLevel() {
		return included.size() + excluded.size();
	}

	int getIncludedSize() {
		return included.size();
	}

	int getExcludedSize() {
		return excluded.size();
	}

	pair<int, int> getIncludedAt(int pos) {
		return included[pos];
	}

	pair<int, int> getExcludedAt(int pos) {
		return excluded[pos];
	}

	bool isCorrectNode() {
		return isPossible;
	}

	void setIsCorrectNode(bool isPossible) {
		this->isPossible = isPossible;
	}

	void setLowBoundry(float value) {
		lowBoundry = value;
	}

	


};