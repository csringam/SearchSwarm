#include <iostream>
#include <memory>
#include <vector>
#include "occMap.h"
#include "diffusionDecomp.h"

int main() {
	std::vector<std::vector<int>> mapData = {
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0},
		{1, 1, 0, 1}
	};

	occMap map1 = occMap(mapData);

	std::cout << std::endl;
	map1.setHeight(5);
	map1.setIndex(4, 2, OBSTACLE);
	map1.printMap();

	occMap sec = map1.getSection(1, 2, 1, 2);
	std::cout << std::endl;
	sec.printMap();

	sec.insertRow(0, { 1, 1 });
	sec.insertColumn(0, { 1, 0, 1 });

	sec.insertRow(1, { 0, 1, 0 });

	std::cout << std::endl;
	sec.printMap();

	occMap* mapPtr = &map1;
	//unique_ptr<occMap> mapPtr (new occMap(map1); // Using smart pointer for memory management

	diffusionDecomp decomp(map1);

	decomp.insertBoundary(1, HORIZONTAL);
	decomp.insertBoundary(2, VERTICAL);
	decomp.padMap();

	cout << endl;
	map1.printMap();

	vector<vector<pair<int, int>>> boundaries = decomp.findAllBoundaries();

	cout << endl;
	for (auto& boundary : boundaries) {
		for (auto& idx : boundary) {
			cout << "[" << idx.first << "," << idx.second << "] ";
		}
		cout << endl;
	}

	pair<int, int> sIdx = { 0, 0 };
	vector<pair<int, int>> perimeter = decomp.findPerimeter(sIdx);
	cout << endl;

	for (auto& idx : perimeter) {
		cout << "[" << idx.first << "," << idx.second << "] ";
	}
	cout << endl;

	vector<pair<int, int>> perimeter2 = decomp.findPerimeter({ 2, 0 });
	cout << endl;

	for (auto& idx : perimeter2) {
		cout << "[" << idx.first << "," << idx.second << "] ";
	}
	cout << endl;

	vector<vector<pair<int, int>>> allPerimeter = decomp.findAllPerimeters();
	cout << endl;

	for (auto& perim : allPerimeter) {
		for (auto& idx : perim) {
			cout << "[" << idx.first << "," << idx.second << "] ";
		}
		cout << endl;
	}
	cout << endl;

	vector<vector<int>> sharedBound = decomp.sharedBoundary(1, 0);

	map1.printMap();

	cout << endl << "Shared Boundary between area 1 and 0: " << endl;
	cout << sharedBound[0][0] << "," << sharedBound[0][1] << endl;
	cout << sharedBound[1][0] << "," << sharedBound[1][1] << endl << endl;

	vector<occMap> areas = decomp.getSubAreas();

	for (auto& area : areas) {
		int curOcc = area.getOccupancy();
		area.printMap();
		cout << "Occupancy: " << curOcc << endl;
		cout << endl;
	}

	vector<int> occCounts = decomp.getSubAreaOcc();

	for (auto& occ : occCounts) {
		cout << "Occupancy Count: " << occ << endl;
	}

	bool coIn = decomp.isAdjacent(allPerimeter[1], allPerimeter[2]);
	int ar1{ 2 }, ar2{ 3 };
	direction boundType = decomp.boundaryType(ar1, ar2);

	cout << coIn << "\nBoundary Direction at " << ar1 << " and " << ar2 << " is: " << boundType << endl;

	adjList adj = decomp.getAdjacencyList();
	adj.printAdjList();

	vector<float> propors = decomp.getAreaProportions();

	for (auto& prop : propors) {
		cout << "Occupancy Proportion: " << prop << endl;
	}

	adjList* adjPtr = &adj;
	decomp.assignProportions(adjPtr);

	adj.printProportions();
	cout << endl;
	adj.printAdjListWithProportions();

	vector<int> maxDiffIdx = decomp.getGreatestUnrelatedDiffIdxs(adjPtr);

	for (const auto& idx : maxDiffIdx) {
		cout << "List of nodes with greatest difference from neighbors: " << idx << " ; At " <<
			decomp.greatestDiffAtIdx(adjPtr, idx).first << " diff is greatest: " << decomp.greatestDiffAtIdx(adjPtr, idx).second << endl;
	}
	cout << endl;
	map1.swapIndex(1, 1, 1, 2);
	map1.printMap();

	occMap map2 = map1;

	cout << endl;
	map2.removeBorders();
	map2.printMap();
	cout << endl;

	cout << "Latest map 1:" << endl;
	map1.printMap();
	decomp.horizantalBoundaryMap();
	decomp.verticalBoundaryMap();

	vector<pair<int, int>> intCorners = decomp.getIntCorners(allPerimeter[3]);
	cout << endl;
	for (const auto& corner : intCorners) {
		cout << "[" << corner.first << "," << corner.second << "], ";
	}

	return 0;
}