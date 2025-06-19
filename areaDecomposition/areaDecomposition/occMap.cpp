#include "occMap.h"

occMap::occMap(size_t width, size_t height) : m_width(width), m_height(height) {
	m_map.resize(height, vector<int>(width, 0)); // Initialize with zeros
}

occMap::occMap(const vector<vector<int>>& map) : m_map(std::move(map)) {
	if (!m_map.empty()) {
		m_height = m_map.size();
		m_width = m_map[0].size();
	}
	else {
		m_width = 0;
		m_height = 0;
	}
}

size_t occMap::getWidth() {
	return m_width;
}

size_t occMap::getHeight() {
	return m_height;
}

vector<vector<int>> occMap::getMap() {
	return m_map;
}

void occMap::setWidth(size_t width) {
	m_width = width;
	for (auto& i : m_map) {
		i.resize(width, 0); //Resize each row to "width" and fill with 0
	}
}

void occMap::setHeight(size_t height) {
	m_height = height;
	m_map.resize(height, vector<int>(m_width, 0)); //Resize height and fill new rows with 0s
}

void occMap::setMap(const vector<vector<int>>& map) {
	m_map = map;
	if (!m_map.empty()) {
		m_height = m_map.size();
		m_width = m_map[0].size();
	}
	else {
		m_width = 0;
		m_height = 0;
	}
}

void occMap::printMap() {
	for (const auto& i : m_map) {
		for (const auto& j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
}