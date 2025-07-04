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

	sec.insertRow( 0, {1, 1} );
	sec.insertColumn(0, { 1, 0, 1 });

	sec.insertRow(1, { 0, 1, 0 });

	std::cout << std::endl;
	sec.printMap();

	occMap* mapPtr = &map1;

	diffusionDecomp decomp(mapPtr);

	decomp.insertBoundary(1, HORIZONTAL);
	decomp.insertBoundary(2, VERTICAL);
	decomp.padMap();

	cout << endl;
	map1.printMap();

	vector<vector<int>> boundaries = decomp.findVBoundaries();

	cout << endl;
	for (auto& boundary : boundaries) {
		for (auto& idx : boundary) {
			cout << idx << " ";
		}
		cout << endl;
	}

	return 0;
}