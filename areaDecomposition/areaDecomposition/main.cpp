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

	std::cout << "Occupancy map width: " << map1.getWidth() << std::endl;
	std::cout << "Occupancy map height: " << map1.getHeight() << std::endl;

	std::cout << "Occupancy map:" << std::endl;

	map1.printMap();

	std::cout << std::endl;
	map1.setHeight(5);
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
	decomp.padMap();

	cout << endl;
	map1.printMap();

	return 0;
}