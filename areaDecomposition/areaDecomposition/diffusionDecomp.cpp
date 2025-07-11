#include "diffusionDecomp.h"

diffusionDecomp::~diffusionDecomp() {
	if (m_map) {
		m_map = nullptr;
	}
}

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

vector<vector<pair<int, int>>> diffusionDecomp::findHBoundaries() {
	vector<vector<pair<int, int>>> boundaries;
	size_t width = m_map->getWidth();
	size_t height = m_map->getHeight();

	for (size_t i = 0; i < height; ++i) {
		int boundaryPos = 0;
		vector<pair<int, int>> curBoundary;
		for (size_t j = 0; j < width; ++j) {
			if (i < height - 1) {
				if (j < width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (j < width - 1 && (*m_map).getMap()[i][j + 1] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (j == width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
			else if (i == height - 1) {
				if (j < width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (j < width - 1 && (*m_map).getMap()[i][j + 1] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (j == width - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i - 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
		}
	}
	return boundaries;
}

vector<vector<pair<int, int>>> diffusionDecomp::findVBoundaries() {
	vector<vector<pair<int, int>>> boundaries;
	size_t width = m_map->getWidth();
	size_t height = m_map->getHeight();
	for (size_t j = 0; j < width; ++j) {
		int boundaryPos = 0;
		vector<pair<int, int>> curBoundary;
		for (size_t i = 0; i < height; ++i) {
			if (j < width - 1) {
				if (i < height - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (i < height - 1 && (*m_map).getMap()[i + 1][j] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (i == height - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j + 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
			else if (j == width - 1) {
				if (i < height - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j - 1] == 2 && (*m_map).getMap()[i + 1][j] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j - 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (i < height - 1 && (*m_map).getMap()[i + 1][j] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (i == height - 1) {
					if ((*m_map).getMap()[i][j] == 2 && (*m_map).getMap()[i][j - 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
		}
	}
	return boundaries;
}

vector<vector<pair<int, int>>> diffusionDecomp::findAllBoundaries() {
	// Combine horizontal and vertical boundaries as below:
	// Horizontal			
	// First row of boundaries:		(s1, s1) (e1, e1) (s2, s2) (e2, e2) (s3, s3) (e3, e3)
	// Second row of boundaries:	(s4, s4) (e4, e4) (s5, s5) (e5, e5)
	// Vertical
	// First col of boundaries:		(s1, s1) (e1, e1) (s2, s2) (e2, e2) (s3, s3) (e3, e3)
	// Second col of boundaries:	(s4, s4) (e4, e4) (s5, s5) (e5, e5)

	vector<vector<pair<int, int>>> boundaries;
	vector<vector<pair<int, int>>> hBoundaries = findHBoundaries();
	vector<vector<pair<int, int>>> vBoundaries = findVBoundaries();
	boundaries.insert(boundaries.end(), hBoundaries.begin(), hBoundaries.end());
	boundaries.insert(boundaries.end(), vBoundaries.begin(), vBoundaries.end());
	return boundaries;
}

vector<occMap> diffusionDecomp::getAreas() {
	vector<vector<int>> corners = findTLBoundCorner();
	vector<vector<int>> mapInts = m_map->getMap();
	vector<occMap> vecMap;
	return vecMap;
}

vector<pair<int, int>> diffusionDecomp::findPerimeter(pair<int, int> sIdx) {
	vector<pair<int, int>> perimeter;
	vector<vector<pair<int, int>>> hBoundaries = findHBoundaries();
	vector<vector<pair<int, int>>> vBoundaries = findVBoundaries();

	int row = sIdx.first;
	int col = sIdx.second;
	if (row < 0 || row >= m_map->getHeight() || col < 0 || col >= m_map->getWidth()) {
		cerr << "Starting index out of bounds." << endl;
		return perimeter;
	}
	if (m_map->getMap()[row][col] != 2) {
		cerr << "Starting index is not a boundary." << endl;
		return perimeter;
	}
	perimeter.push_back(sIdx);
	
	pair<int, int> currentHBound{ -1, -1 }, currentVBound{ -1, -1 }, curBound{ -1, -1 };

	for(int i = 0; i < hBoundaries.size(); ++i) {
		for (int j = 0; j < hBoundaries[i].size(); ++j) {
			if (hBoundaries[i][j] == sIdx) {
				currentHBound = { i, j };
				break;
			}
		}
	}

	if (currentHBound == make_pair(-1, -1)) {
		cerr << "Starting index not found in boundaries." << endl;
		return perimeter;
	}

	bool looped = false;
	int loopCounter = 0;
	direction dir = HORIZONTAL;

	while (!looped) {
		loopCounter++;
		if(currentVBound == sIdx || currentHBound == sIdx) {
			if (perimeter.size() > 1) {
				looped = true;
				break;
			}
		}
		if(loopCounter > 100) {
			cerr << "Loop counter exceeded 100 iterations. Exiting loop." << endl;
			break;
		}
		if (dir == HORIZONTAL && currentHBound.first % 2 == 0) {
			currentHBound.first++;
			curBound = hBoundaries[currentHBound.first][currentHBound.second];
			perimeter.push_back(curBound);
			dir = VERTICAL;
			for (int i = 0; i < vBoundaries.size(); ++i) {
				for (int j = 0; j < vBoundaries[i].size(); ++j) {
					if (vBoundaries[i][j] == curBound) {
						currentVBound = { i, j };
						break;
					}
				}
			}
		}
		else if (dir == VERTICAL && currentVBound.first % 2 == 0) {
			currentVBound.first++;
			curBound = vBoundaries[currentVBound.first][currentVBound.second];
			perimeter.push_back(curBound);
			dir = HORIZONTAL;
			for (int i = 0; i < hBoundaries.size(); ++i) {
				for (int j = 0; j < hBoundaries[i].size(); ++j) {
					if (hBoundaries[i][j] == curBound) {
						currentHBound = { i, j };
						break;
					}
				}
			}
		}
		else if (dir == HORIZONTAL && currentHBound.first % 2 == 1) {
			currentHBound.first--;
			curBound = hBoundaries[currentHBound.first][currentHBound.second];
			perimeter.push_back(curBound);
			dir = VERTICAL;
			for (int i = 0; i < vBoundaries.size(); ++i) {
				for (int j = 0; j < vBoundaries[i].size(); ++j) {
					if (vBoundaries[i][j] == curBound) {
						currentVBound = { i, j };
						break;
					}
				}
			}
		}
		else if (dir == VERTICAL && currentVBound.first % 2 == 1) {
			currentVBound.first--;
			curBound = vBoundaries[currentVBound.first][currentVBound.second];
			perimeter.push_back(curBound);
			dir = HORIZONTAL;
			for (int i = 0; i < hBoundaries.size(); ++i) {
				for (int j = 0; j < hBoundaries[i].size(); ++j) {
					if (hBoundaries[i][j] == curBound) {
						currentHBound = { i, j };
						break;
					}
				}
			}
		}
	}

	perimeter.pop_back();
	return perimeter;
}