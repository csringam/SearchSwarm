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