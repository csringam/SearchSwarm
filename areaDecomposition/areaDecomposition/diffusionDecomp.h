#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include "occMap.h"

using namespace std;

enum direction {HORIZONTAL, VERTICAL};

class diffusionDecomp
{
	occMap *m_map; // Occupancy map for diffusion decomposition
	
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

	vector<occMap> getSubAreas();
	vector<int> getSubAreaOcc();
};

