#include <vector>

using namespace std;
	 
class TravellingSalesman {
	int numberOfCities;
	vector<vector<int>> pathsValue;
public:
	TravellingSalesman();
	~TravellingSalesman();
	void loadPaths(istream&);
	void printPaths(ostream&);
	int getPathValue(int, int);
};