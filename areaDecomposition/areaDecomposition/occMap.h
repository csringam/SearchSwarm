#pragma once
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class occMap
{
	vector<vector<int>> m_map; // 2D array to prepresent occupancy map, (0 or 1)
	size_t m_width{ 0 };
	size_t m_height{ 0 };

public:
	// Constructors and Destructor
	occMap() = default;
	occMap(size_t width, size_t height);
	occMap(const vector<vector<int>>& map);
	~occMap() = default;

	// Getters and Setters
	size_t getWidth();
	size_t getHeight();
	vector<vector<int>> getMap();

	void setWidth(size_t width);
	void setHeight(size_t height);
	void setMap(const vector<vector<int>>& map);

	// Utility Functions
	void printMap();
};

