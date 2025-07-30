#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <utility>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include "occMap.h"
#include "adjList.h"

using namespace std;

enum direction {HORIZONTAL, VERTICAL};
enum cardinal { NORTH, EAST, SOUTH, WEST };

class diffusionDecomp
{
	occMap mapIn;
	occMap *m_map; // Occupancy map for diffusion decomposition
	vector<vector<int>> hBorders; // 2D array to represent num of horizontal boundaries
	vector<vector<int>> vBorders; // 2D array to represent num of vertical boundaries
	
public:

	//Constructors and Destructor
	diffusionDecomp() = default;
	diffusionDecomp(occMap &map) : m_map(&map) {}
	~diffusionDecomp();
	
	// Getters and Setters
	occMap getMap() const;
	void setMap(const occMap& map);

	//Utility Functions
	void insertBoundary(int idx, direction dir);
	void padMap();

	vector<vector<int>> findTLBoundCorner();
	vector<vector<pair<int, int>>> findHBoundaries();
	vector<vector<pair<int, int>>> findVBoundaries();
	vector<vector<pair<int, int>>> findAllBoundaries();

	vector<pair<int, int>> findPerimeter(pair<int, int> sIdx);
	vector<vector<pair<int, int>>> findAllPerimeters();
	vector<vector<pair<int, int>>> findIntCorners();

	vector<occMap> getSubAreas();
	vector<int> getSubAreaOcc();

	bool isCoincident(pair<int, int> ls, pair<int, int> lf, pair<int, int> p);
	bool isAdjacent(vector<pair<int, int>> target, vector<pair<int, int>> origin);
	
	direction boundaryType(int targetArea, int srcArea);
	vector<vector<int>> sharedBoundary(int targetArea, int srcArea);
	cardinal boundaryOrientation(int targetArea, int srcArea);

	adjList getAdjacencyList();

	vector<float> getAreaProportions();

	void assignProportions(adjList* adj);

	int getGreatestDiffIdx(adjList* adj);
	pair<int, float> greatestDiffAtIdx(adjList* adj, int idx);
	vector<int> getGreatestUnrelatedDiffIdxs(adjList* adj);

	void horizantalBoundaryMap();
	void verticalBoundaryMap();
};

/* Visualization for moving boundaries:
* might have to move away from inserting 2's for boundaries, can still use 2's for initial
* boundary and visualization, but after that, track the boundaries in the original occupancy
* map using just the corner indices
2 2 2 2 2 2 2 2
2 1 1 1 2 0 0 2
2 1 1 1 2 0 0 2
2 2 2 2 2 0 0 2
2 0 0 0 2 0 0 2
2 0 0 0 2 0 0 2
2 0 0 0 2 2 2 2
2 0 0 0 2 1 1 2
2 0 0 0 2 1 1 2
2 2 2 2 2 2 2 2

1 1 1  0 0
1 1 1  0 0
       0 0
0 0 0  0 0
0 0 0  0 0
0 0 0 
0 0 0  1 1
0 0 0  1 1

2 2 2 2 2 2 2 2
2 1 1 1 0 2 0 2
2 1 1 1 0 2 0 2
2 2 2 2 2 0 0 2
2 0 0 0 2 0 0 2
2 0 0 0 2 0 0 2
2 0 0 0 2 2 2 2
2 0 0 0 2 1 1 2
2 0 0 0 2 1 1 2
2 2 2 2 2 2 2 2

1 1 1 0  0
1 1 1 0  0
       0 0
0 0 0  0 0
0 0 0  0 0
0 0 0
0 0 0  1 1
0 0 0  1 1

2 2 2 2 2 2 2 2
2 1 1 1 0 2 0 2
2 1 1 1 0 2 0 2
2 0 0 0 0 2 0 2
2 2 2 2 2 0 0 2
2 0 0 0 2 0 0 2
2 0 0 0 2 2 2 2
2 0 0 0 2 1 1 2
2 0 0 0 2 1 1 2
2 2 2 2 2 2 2 2

1 1 1 0  0
1 1 1 0  0
0 0 0 0  0
       0 0
0 0 0  0 0
0 0 0
0 0 0  1 1
0 0 0  1 1

*/
