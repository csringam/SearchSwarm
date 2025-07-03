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

occMap occMap::getSection(int t_row, int b_row, int l_col, int r_col) {
	if (b_row >= m_height || t_row < 0 || l_col < 0 || r_col >= m_width) {
		cout << "Error: row or column index out of bounds." << endl;
		return occMap();
	}
	vector<vector<int>> section;

	for (int i = t_row; i <= b_row; i++) {
		vector<int> curRow;
		for (int j = l_col; j <= r_col; j++) {
			curRow.push_back(m_map[i][j]);
		}
		section.push_back(curRow);
	}

	occMap sectionMap(section);
	return sectionMap;
}

void occMap::insertRow(int row, const vector<int>& newRow) {
	if (row < 0 || row > m_height) {
		cerr << "Error: Row index out of bounds." << endl;
		return;
	}
	if (newRow.size() != m_width) {
		cerr << "Error: New row size does not match map width." << endl;
		return;
	}
	m_map.insert(m_map.begin() + row, newRow);
	m_height++;
	return;
}

void occMap::insertColumn(int col, const vector<int>& newCol) {
	if (col < 0 || col > m_width) {
		cerr << "Error: Column index out of bounds." << endl;
		return;
	}
	if (newCol.size() != m_height) {
		cerr << "Error: New column size does not match map height." << endl;
		return;
	}
	for (int i = 0; i < m_height; i++) {
		m_map[i].insert(m_map[i].begin() + col, newCol[i]);
	}
	m_width++;
	return;
}

void occMap::setIndex(int row, int col, occupancy val) {
	if (row < 0 || row >= m_height || col < 0 || col >= m_width) {
		cerr << "Error: Index out of bounds." << endl;
		return;
	}
	m_map[row][col] = val;
	return;
}