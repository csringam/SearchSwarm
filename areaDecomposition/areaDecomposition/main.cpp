#include <iostream>
#include <memory>
#include <vector>
#include "occMap.h"

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

	return 0;
}