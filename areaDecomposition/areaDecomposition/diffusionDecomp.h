#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "occMap.h"

using namespace std;

enum direction {HORIZONTAL, VERTICAL};

class diffusionDecomp
{
	occMap* m_map; // Occupancy map for diffusion decomposition
public:

	//Constructors and Destructor
	diffusionDecomp() = default;
	diffusionDecomp(occMap *map) : m_map(map) {}
	~diffusionDecomp() = default;
	
	// Getters and Setters
	occMap getMap() const;
	void setMap(const occMap& map);

	//Utility Functions
	void insertBoundary(int idx, direction dir);
	void padMap();

	vector<vector<int>> findTLBoundCorner();
	vector<vector<int>> findHBoundaries();
	vector<vector<int>> findVBoundaries();
	vector<vector<int>> findAllBoundaries();
	vector<occMap> getAreas();
};

