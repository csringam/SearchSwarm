#include "diffusionDecomp.h"

occMap diffusionDecomp::getMap() const {
	return *m_map;
}

void diffusionDecomp::setMap(const occMap& map) {
	*m_map = map;
}

void diffusionDecomp::insertBoundary(int idx, direction dir) {
	switch (dir) {
		case HORIZONTAL:
			if (idx < 0 || idx >= m_map->getHeight()) {
				cerr << "Invalid index for horizontal boundary insertion." << endl;
				return;
			}
			m_map->insertRow(idx, vector<int>(m_map->getWidth(), 2));
			break;
		case VERTICAL:
			if (idx < 0 || idx >= m_map->getWidth()) {
				cerr << "Invalid index for vertical boundary insertion." << endl;
				return;
			}
			m_map->insertColumn(idx, vector<int>(m_map->getHeight(), 2));
			break;
		default:
			cerr << "Invalid direction for boundary insertion." << endl;
			return;
	}
	return;
}

void diffusionDecomp::padMap() {
	m_map->insertRow(0, vector<int>(m_map->getWidth(), 2)); // Top padding
	m_map->insertRow(m_map->getHeight(), vector<int>(m_map->getWidth(), 2)); //Bottom padding
	m_map->insertColumn(0, vector<int>(m_map->getHeight(), 2)); // Left padding
	m_map->insertColumn(m_map->getWidth(), vector<int>(m_map->getHeight(), 2)); // Right padding
	return;
}

vector<vector<int>> diffusionDecomp::findTLBoundCorner() {
	vector<vector<int>> corners;
	size_t width = m_map->getWidth();
	size_t height = m_map->getHeight();

	for (size_t i = 1; i < height; ++i) {
		for (size_t j = 1; j < width; ++j) {
			if ((*m_map).getMap()[i-1][j] == 2 && (*m_map).getMap()[i][j-1] == 2 && j < width-1 && (*m_map).getMap()[i][j + 1] != 2) {
				corners.push_back({static_cast<int>(i), static_cast<int>(j)});
			}
		}
	}
	return corners;
}

vector<vector<int>> diffusionDecomp::findHBoundaries() {
	vector<vector<int>> boundaries;
	size_t width = m_map->getWidth();
	size_t height = m_map->getHeight();

	for (size_t i = 0; i < height; ++i) {
		int boundaryPos = 0;
		vector<int> curBoundary;
		for (size_t j = 0; j < width; ++j) {
			if (i < height - 1) {
				if (j < width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
						if (j < width - 1 && (*m_map).getMap()[i][j + 1] == 2) {
							cout << "start nex" << endl;
							curBoundary.push_back(static_cast<int>(i));
							curBoundary.push_back(static_cast<int>(j));
							boundaryPos = 1;
						}
					}
				}
				else if (j == width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
						boundaries.push_back(curBoundary);
					}
				}
			}
			else if (i == height - 1) {
				if (j < width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
						if (j < width - 1 && (*m_map).getMap()[i][j + 1] == 2) {
							curBoundary.push_back(static_cast<int>(i));
							curBoundary.push_back(static_cast<int>(j + 1));
							boundaryPos = 1;
						}
					}
				}
				else if (j == width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						curBoundary.push_back(static_cast<int>(i));
						curBoundary.push_back(static_cast<int>(j));
						boundaries.push_back(curBoundary);
					}
				}
			}
		}
	}
	return boundaries;
}

vector<occMap> diffusionDecomp::getAreas() {
	vector<vector<int>> corners = findTLBoundCorner();
	vector<vector<int>> mapInts = m_map->getMap();
	vector<occMap> vecMap;
	return vecMap;
}