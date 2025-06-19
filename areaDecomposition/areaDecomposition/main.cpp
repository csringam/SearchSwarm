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

	for (int i = 0; i < map1.getHeight(); i++) {
		for (int j = 0; j < map1.getWidth(); j++) {
			std::cout << map1.getMap()[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}