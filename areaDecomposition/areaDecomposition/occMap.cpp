#include "occMap.h"

occMap::occMap(size_t width, size_t height) : m_width(width), m_height(height) {
	m_map.resize(height, vector<int>(width, 0)); // Initialize with zeros
}

occMap::occMap(vector<vector<int>> map) : m_map(std::move(map)) {
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