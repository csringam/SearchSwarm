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

/*
name:		insertBoundary

inputs:		idx: index at which to insert boundary
			dir: direction (HORIZONTAL or VERTICAL) to insert boundary

outputs:	none

descr:		Inserts a boundary (row or column of 2's) into the occupancy map
			at the specified index and direction.
			Modifies the occupancy map in place.
*/
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

/*
name:		padMap

inputs:		none

outputs:	none

descr:		Pads the occupancy map with a border of 2's (BORDER) on all sides.
			Modifies the occupancy map in place.
*/
void diffusionDecomp::padMap() {
	m_map->insertRow(0, vector<int>(m_map->getWidth(), 2)); // Top padding
	m_map->insertRow(static_cast<int>(m_map->getHeight()), vector<int>(m_map->getWidth(), 2)); //Bottom padding
	m_map->insertColumn(0, vector<int>(m_map->getHeight(), 2)); // Left padding
	m_map->insertColumn(static_cast<int>(m_map->getWidth()), vector<int>(m_map->getHeight(), 2)); // Right padding
	return;
}

/*
name:		findTLBoundCorner

intputs:	none

outputs:	Vector of corner indices (row, col) where top-left corners of
			each area are located

descr:		Finds the top-left corners of each area in the occupancy map.
			A top-left corner is defined as a cell with value 2 (BORDER)
			that has a cell with value 2 directly below it and a cell
			with value 2 directly to its right.
			Returns a vector of pairs of indices representing the corners.
*/
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

/*
name:		findHBoundaries

inputs:		none

outputs:	Vector of horizontal boundaries, each represented as a vector of
			pairs of indices (row, col) marking the start and end of each
			horizontal boundary segment.

descr:		Finds all horizontal boundaries in the occupancy map.
			A horizontal boundary is defined as a contiguous sequence of
			cells with value 2 (BORDER) that have cells with value 2
			directly to the left and/or right.
			Returns a vector of vectors, where each inner vector contains
			pairs of indices marking the start and end of each horizontal
			boundary segment.
*/
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
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i + 1][j] == 2 && m_map->getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i + 1][j] == 2 && boundaryPos == 1) {
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
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i + 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
			else if (i == height - 1) {
				if (j < width - 1) {
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i - 1][j] == 2 && m_map->getMap()[i][j + 1] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i - 1][j] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (j < width - 1 && m_map->getMap()[i][j + 1] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (j == width - 1) {
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i - 1][j] == 2 && boundaryPos == 1) {
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

/*
name:		findVBoundaries

inputs:		none

outputs:	Vector of vertical boundaries, each represented as a vector of
			pairs of indices (row, col) marking the start and end of each
			vertical boundary segment.

descr:		Finds all vertical boundaries in the occupancy map.
			A vertical boundary is defined as a contiguous sequence of
			cells with value 2 (BORDER) that have cells with value 2
			directly to the top and/or bottom.
			Returns a vector of vectors, where each inner vector contains
			pairs of indices marking the start and end of each vertical
			boundary segment.
*/
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
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j + 1] == 2 && m_map->getMap()[i + 1][j] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j + 1] == 2 && boundaryPos == 1) {
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
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j + 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						boundaries.push_back(curBoundary);
					}
				}
			}
			else if (j == width - 1) {
				if (i < height - 1) {
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j - 1] == 2 && m_map->getMap()[i + 1][j] == 2 && boundaryPos == 0) {
						boundaryPos++;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
					}
					else if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j - 1] == 2 && boundaryPos == 1) {
						boundaryPos = 0;
						pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
						curBoundary.push_back(idxPair);
						if (i < height - 1 && m_map->getMap()[i + 1][j] == 2) {
							pair<int, int> idxPair = make_pair(static_cast<int>(i), static_cast<int>(j));
							curBoundary.push_back(idxPair);
							boundaryPos = 1;
						}
					}
				}
				else if (i == height - 1) {
					if (m_map->getMap()[i][j] == 2 && m_map->getMap()[i][j - 1] == 2 && boundaryPos == 1) {
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

/*
name:		findAllBoundaries

inputs:		none

outputs:	Vector of all boundaries (horizontal and vertical), each represented
			as a vector of pairs of indices (row, col) marking the start and
			end of each boundary segment.

descr:		Finds all boundaries (both horizontal and vertical) in the occupancy map.
*/
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

/*
name:		findPerimeter

inputs:		sIdx: starting index (row, col) on the boundary to trace the perimeter from

outputs:	Vector of pairs of indices (row, col) representing the traced perimeter.

descr:		Traces the perimeter of an area starting from the given index on the boundary.
			The function follows the boundary in a clockwise manner until it returns
			to the starting index, collecting all indices along the way.
			Returns a vector of pairs of indices representing the traced perimeter.
			If the starting index is out of bounds or not on a boundary, an error
			message is printed and an empty vector is returned.
			To prevent infinite loops, a loop counter is implemented that breaks
			the loop after 100 iterations if the perimeter has not been closed.
			This function assumes that boundaries are well-formed and connected.
*/
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
	
	pair<int, int> sHbound{ -1, -1 }, currentHBound{ -1, -1 }, currentVBound{ -1, -1 }, curBound{ -1, -1 };
	direction dir = HORIZONTAL;

	for(int i = 0; i < hBoundaries.size(); ++i) {
		bool foundStart{ false };
		for (int j = 0; j < hBoundaries[i].size(); ++j) {
			if (hBoundaries[i][j] == sIdx) {
				if (i == hBoundaries.size() - 1 && j < hBoundaries[i].size() - 1) {
					if (hBoundaries[i][j + 1] == sIdx) {
						currentHBound = { i, j + 1 };
					} 
					else {
						currentHBound = { i, j };
					}
					curBound = hBoundaries[currentHBound.first][currentHBound.second];
					dir = VERTICAL;
					for (int i = 0; i < vBoundaries.size(); ++i) {
						for (int j = 0; j < vBoundaries[i].size(); ++j) {
							if (vBoundaries[i][j] == curBound) {
								currentVBound = {i, j};
								break;
							}
						}
					}
				}
				else if (j < hBoundaries[i].size() - 1 && hBoundaries[i][j + 1] == sIdx) {
					currentHBound = { i, j + 1 };
				}
				else if (j == hBoundaries[i].size() - 1 && i < hBoundaries.size() - 1) {
					currentHBound = { i, j };
					curBound = hBoundaries[currentHBound.first][currentHBound.second];
					dir = VERTICAL;
					for (int i = 0; i < vBoundaries.size(); ++i) {
						for (int j = 0; j < vBoundaries[i].size(); ++j) {
							if (vBoundaries[i][j] == curBound) {
								if (j < vBoundaries[i].size() - 1 && vBoundaries[i][j + 1] == sIdx) {
									currentVBound = { i, j + 1 };
								}
								else {
									currentVBound = { i, j };
								}
								break;
							}
						}
					}
				}
				else {
					currentHBound = { i, j };
				}
				sHbound = currentHBound;
				foundStart = true;
				break;
			}
		}
		if (foundStart) break;
	}

	if (currentHBound == make_pair(-1, -1)) {
		cerr << "Starting index not found in boundaries." << endl;
		return perimeter;
	}

	bool looped = false;
	int loopCounter = 0;

	while (!looped) {
		loopCounter++;
		if(currentHBound == sHbound) {
			if (perimeter.size() > 1) {
				looped = true;
				break;
			}
		}
		if(loopCounter > 100) {
			cerr << "Loop counter exceeded 100 iterations. Exiting loop." << endl;
			break;
		}
		if (dir == HORIZONTAL && currentHBound.second % 2 == 0) {
			currentHBound.second++;
			curBound = hBoundaries[currentHBound.first][currentHBound.second];
			perimeter.push_back(curBound);
			dir = VERTICAL;
			for (int i = 0; i < vBoundaries.size(); ++i) {
				for (int j = 0; j < vBoundaries[i].size(); ++j) {
					if (vBoundaries[i][j] == curBound) {
						if (j < vBoundaries[i].size() - 1 && vBoundaries[i][j + 1] == curBound) {
							currentVBound = { i, j + 1 };
						}
						
						else {
							currentVBound = { i, j };
						}
						break;
					}
				}
			}
		}
		else if (dir == VERTICAL && currentVBound.second % 2 == 0) {
			currentVBound.second++;
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
		else if (dir == HORIZONTAL && currentHBound.second % 2 == 1) {
			currentHBound.second--;
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
		else if (dir == VERTICAL && currentVBound.second % 2 == 1) {
			currentVBound.second--;
			curBound = vBoundaries[currentVBound.first][currentVBound.second];
			perimeter.push_back(curBound);
			dir = HORIZONTAL;
			for (int i = 0; i < hBoundaries.size(); ++i) {
				bool found{ false };
				for (int j = 0; j < hBoundaries[i].size(); ++j) {
					if (hBoundaries[i][j] == curBound) {
						if (j < hBoundaries[i].size() - 1 && hBoundaries[i][j + 1] == curBound) {
							currentHBound = { i, j + 1 };
						}
						else {
							currentHBound = { i, j };
						}
						found = true;
						break;
					}
				}
				if (found) break;
			}
		}
	}
	if (perimeter.front() == perimeter.back() && perimeter.size() > 1) { // Remove duplicate start/end point if looped
		perimeter.pop_back();
	}
	return perimeter;
}

/*
name:		findAllPerimeters

inputs:		none

outputs:	Vector of all boundaries (horizontal and vertical), each represented
			as a vector of pairs of indices (row, col) marking the start and
			end of each boundary segment.
			Each vector oof pairs corresponds to one boundary enclosing an area.

descr:		Finds all boundaries (both horizontal and vertical) in the occupancy map
			by combining the results of findHBoundaries and findVBoundaries.
			Returns a vector of vectors, where each inner vector contains
			pairs of indices marking the start and end of each boundary segment, and
			each vector represents the boundary enclosing an area.
*/
vector<vector<pair<int, int>>> diffusionDecomp::findAllPerimeters() {
	vector<vector<pair<int, int>>> perimeters, visitedPerimeters; // To track visited perimeters
	vector<vector<pair<int, int>>> boundaries = findAllBoundaries();

	for (const auto& boundary : boundaries) {
		for (const auto& idxPair : boundary) {
			vector<pair<int, int>> curBoundary = findPerimeter(idxPair);
			vector<pair<int, int>> sortedBoundary = curBoundary;
			sort(sortedBoundary.begin(), sortedBoundary.end());
			bool alreadyVisited{ false };

			for (const auto& visited : visitedPerimeters) {
				if (visited == sortedBoundary) {
					alreadyVisited = true;
					break;
				}
			}

			if(!alreadyVisited && !curBoundary.empty()) {
				perimeters.push_back(curBoundary);
				visitedPerimeters.push_back(sortedBoundary);
			}
		}
	}
	
	return perimeters;
}

vector<vector<pair<int, int>>> diffusionDecomp::findIntCorners() {
	vector<pair<int, int>> corners;
	return vector<vector<pair<int, int>>>{corners};
}

vector<occMap> diffusionDecomp::getSubAreas() {
	vector<vector<pair<int, int>>> perimeters = findAllPerimeters();
	vector<vector<int>> mapInts = m_map->getMap();
	vector<occMap> occVec;

	for (const auto& perimeter : perimeters) {
		if (perimeter.empty()) continue;
		int minRow = static_cast<int>(mapInts.size()), maxRow = -1, minCol = static_cast<int>(mapInts[0].size()), maxCol = -1;
		for (const auto& idx : perimeter) {
			minRow = min(minRow, idx.first);
			maxRow = max(maxRow, idx.first);
			minCol = min(minCol, idx.second);
			maxCol = max(maxCol, idx.second);
		}
		if (minRow < 0 || maxRow >= mapInts.size() || minCol < 0 || maxCol >= mapInts[0].size()) continue;
		occMap areaMap = m_map->getSection(minRow, maxRow, minCol, maxCol);
		occVec.push_back(areaMap);
	}

	return occVec;
}

vector<int> diffusionDecomp::getSubAreaOcc() {
	vector<occMap> subAreas = getSubAreas();
	vector<int> occCounts;
	for (auto& area : subAreas) {
		int curOcc = area.getOccupancy();
		occCounts.push_back(curOcc);
	}
	return occCounts;
}

bool diffusionDecomp::isCoincident(pair<int, int> ls, pair<int, int> lf, pair<int, int> p) {
	if (p.first <= max(ls.first, lf.first) && p.first >= min(ls.first, lf.first)
		&& p.second <= max(ls.second, lf.second) && p.second >= min(ls.second, lf.second)) return true;
	return false;
}

bool diffusionDecomp::isAdjacent(vector<pair<int, int>> target, vector<pair<int, int>> origin) {
	int onBoundary = 0;
	for (int i = 0; i < target.size(); ++i) {
		int j = (i + 1) % target.size();
		for(const auto& p : origin) {
			if (isCoincident(target[i], target[j], p)) {
				if (p != target[i] && p != target[j]) return true;
				else if (p == target[i] || p == target[j]) ++onBoundary;
				if (onBoundary > 2)	return true;
			}
		}
	}
	return false;
}

direction diffusionDecomp::boundaryType(int targetArea, int srcArea) {
	vector<vector<pair<int, int>>> perimeters = findAllPerimeters();
	if (targetArea < 0 || targetArea >= perimeters.size() || srcArea < 0 || srcArea >= perimeters.size()) {
		cerr << "Target or source out of bounds." << endl;
		return HORIZONTAL;
	}
	if (!isAdjacent(perimeters[targetArea], perimeters[srcArea])) {
		cerr << "Target and source areas are not adjacent." << endl;
		return HORIZONTAL;
	}
	vector<pair<int, int>> target{ perimeters[targetArea] }, src{ perimeters[srcArea] };
	for (int i = 0; i < target.size(); ++i) {
		int j = (i + 1) % target.size();
		for (const auto& pt: src) {
			if (isCoincident(target[i], target[j], pt)) {
				if (target[i].first == target[j].first) return VERTICAL;
				else if (target[i].second == target[j].second) return HORIZONTAL;
			}
		}
	}
}

vector<vector<int>> diffusionDecomp::sharedBoundary(int targetArea, int srcArea) {
	vector<vector<pair<int, int>>> perimeters = findAllPerimeters();
	vector<vector<int>> sharedBound;
	vector<pair<int, int>> target{ perimeters[targetArea] }, src{ perimeters[srcArea] };
	direction bType = boundaryType(targetArea, srcArea);
	for (int i = 0; i < target.size(); ++i) {
		int j = (i + 1) % target.size();
		if (bType == HORIZONTAL && target[i].first == target[j].first) {
			for (int k = 0; k < src.size(); ++k) {
				int l = (k + 1) % src.size();
				if (src[k].first == src[l].first && isCoincident(target[i], target[j], src[k])) {
					sharedBound.push_back({ i, j });
					sharedBound.push_back({ k, l });
					return sharedBound;
				}
			}
		}
		else if (bType == VERTICAL && target[i].second == target[j].second) {
			for (int k = 0; k < src.size(); ++k) {
				int l = (k + 1) % src.size();
				if (src[k].second == src[l].second && isCoincident(target[i], target[j], src[k])) {
					sharedBound.push_back({ i, j });
					sharedBound.push_back({ k, l });
					return sharedBound;
				}

			}
		}
	}
	return sharedBound;
}

cardinal diffusionDecomp::boundaryOrientation(int targetArea, int srcArea) {
	vector<vector<pair<int, int>>> perimeters = findAllPerimeters();
	vector<pair<int, int>> target{ perimeters[targetArea] }, src{ perimeters[srcArea] };
	vector<vector<int>> sharedBound = sharedBoundary(targetArea, srcArea);
	direction bType = boundaryType(targetArea, srcArea);
	if (sharedBound.size() != 2) {
		cerr << "Shared boundary not found or invalid." << endl;
		return NORTH;
	}

	if (bType == HORIZONTAL) {
		for (auto s : src) {
			for (auto t : target) {
				if (t.second > s.second) return NORTH;
				else if (t.second < s.second) return SOUTH;

			}
		}
	}

	if (bType == VERTICAL) {
		for (auto s : src) {
			for (auto t : target) {
				if (t.second > s.second) return EAST;
				else if (t.second < s.second) return WEST;

			}
		}
	}

	return NORTH;
}

adjList diffusionDecomp::getAdjacencyList() {
	vector<vector<pair<int, int>>> perimeters = findAllPerimeters();
	adjList adjacency(perimeters.size());
	for (int i = 0; i < perimeters.size(); ++i) {
		for (int j = i + 1; j < perimeters.size(); ++j) {
			if (i != j && isAdjacent(perimeters[i], perimeters[j])) {
				adjacency.addEdge(i, j);
			}
		}
	}
	return adjacency;
}

vector<float> diffusionDecomp::getAreaProportions() {
	vector<int> occCounts = getSubAreaOcc();
	int totalOcc = accumulate(occCounts.begin(), occCounts.end(), 0);
	vector<float> proportions;
	for (const auto& occ : occCounts) {
		if (totalOcc == 0) proportions.push_back(0.0f);
		else proportions.push_back(static_cast<float>(occ) / totalOcc);
	}
	return proportions;
}

void diffusionDecomp::assignProportions(adjList* adj) {
	unique_ptr<vector<float>> proportions = make_unique<vector<float>>(getAreaProportions());
	adj->setProportions(*proportions);
}

int diffusionDecomp::getGreatestDiffIdx(adjList* adj) {
	if (adj->getProportions().empty()) {
		cerr << "Proportions not assigned to adjacency list." << endl;
		return -1;
	}
	int maxIdx = -1;
	float maxDiff = -1.0f;
	for (int i = 0; i < adj->getAdjList().size(); ++i) {
		for (const auto& neighbor : adj->getNeighbors(i)) {
			float diff = abs(adj->getProportions()[i] - adj->getProportions()[neighbor]);
			if (diff > maxDiff) {
				maxDiff = diff;
				maxIdx = i;
			}
		}
	}
	return maxIdx;
}

/*
name:		greatestDiffAtIdx

inputs:		adj: adjacency list for area to decompose
			idx: index of node of interest in adjacency list

outputs:	pair containing the index of the node with the greatest
			difference in occupied area proportion in the first position
			and the value of that difference in the second position

descr:		Finds the neighbor of the node at idx with the greatest
			difference in occupied area proportion.
*/
pair<int, float> diffusionDecomp::greatestDiffAtIdx(adjList* adj, int idx) {
	pair<int, float> out{ -1, -1.0f };
	if (adj->getProportions().empty()) {
		cerr << "Proportions not assigned to adjacency list." << endl;
		return out;
	}
	if (idx < 0 || idx >= adj->getAdjList().size()) {
		cerr << "Index out of bounds." << endl;
		return out;
	}
	for (const auto& neighbor : adj->getNeighbors(idx)) {
		float diff = abs(adj->getProportions()[idx] - adj->getProportions()[neighbor]);
		if (diff > out.second) {
			out.second = diff;
			out.first = neighbor;
		}
	}
	return out;
}

/*
name:		getGreatestUnrelatedDiffIdxs

inputs:		adj: adjacency list for area to decompose

outputs:	vector of indices of nodes with the greatest differences
			in occupied area proportion that are not adjacent to another
			node in the output vector

descr:		Finds the nodes with the greatest differences in occupied area
			proportion that are not adjacent to another node in the output vector.
			Stops when only two nodes remain in the adjacency list, as one node
			will always be adjacent to at least one other node.
*/
vector<int> diffusionDecomp::getGreatestUnrelatedDiffIdxs(adjList* adj) {
	if (adj->getProportions().empty()) {
		cerr << "Proportions not assigned to adjacency list." << endl;
		return {};
	}
	vector<int> maxIdxs;
	float maxDiff = -1.0f;
	unordered_map<int, float> diffMap;
	for (int i = 0; i < adj->getProportions().size(); ++i) {
		diffMap[i] = adj->getProportions()[i];
	}
	while (diffMap.size() > 2) { // This is 2 because one node will always be adjacent to at least one other node
		int curDiffIdx = getGreatestDiffIdx(adj);
		maxIdxs.push_back(curDiffIdx);
		vector<int> neighbors = adj->getNeighbors(curDiffIdx);
		for (const auto& neighbor : neighbors) {
			diffMap.erase(neighbor);
		}
	}

	return maxIdxs;
}

/*
name:		horizantalBoundaryMap

inputs:		none

outputs:	none

descr:		Generates a map of the number of horizontal boundaries encountered
			at each index when traversing top to bottom.
*/
void diffusionDecomp::horizantalBoundaryMap() {
	size_t width{ m_map->getWidth() }, height{ m_map->getHeight() };
	int numBorders{ 0 };
	bool pastBorder{ false };

	for (int i = 0; i < height; ++i) {
		vector<int> curRow(width, 0);
		for (int j = 0; j < width; ++j) {
			if (m_map->getMap()[i][j] == 2) {
				if (!pastBorder) {
					pastBorder = true;
					numBorders++;
				}
				curRow.push_back(numBorders);
			}
			else {
				pastBorder = false;
				curRow.push_back(numBorders);
			}
		}
		hBorders.push_back(curRow);
		pastBorder = false;
		numBorders = 0;
	}
	return;
}

/*
name:		verticalBoundaryMap

inputs:		none

outputs:	none

descr:		Generates a map of the number of vertical boundaries encountered
			at each index when traversing left to right.
*/
void diffusionDecomp::verticalBoundaryMap() {
	size_t width{ m_map->getWidth() }, height{ m_map->getHeight() };
	int numBorders{ 0 };
	bool pastBorder{ false };
	vector<vector<int>> temp;

	for (int j = 0; j < width; ++j) {
		vector<int> curCol;
		for (int i = 0; i < height; ++i) {
			if (m_map->getMap()[i][j] == 2) {
				if (!pastBorder) {
					pastBorder = true;
					numBorders++;
				}
				curCol.push_back(numBorders);
			}
			else {
				pastBorder = false;
				curCol.push_back(numBorders);
			}
		}
		temp.push_back(curCol);
		pastBorder = false;
		numBorders = 0;
	}


	for (int i = 0; i < temp.size(); ++i) {
		for (int j = 0; j < temp[i].size(); ++j) {
			if (vBorders.size() <= j) {
				vBorders.push_back(vector<int>(width, 0));
			}
			vBorders[j][i] = temp[i][j];
		}
	}

	return;
}

bool diffusionDecomp::cornerIsBelow(pair<int, int> target, pair<int, int> src) {
	if (target.first > src.first && target.second == src.second) return true;
	return false;
}

bool diffusionDecomp::cornerIsAbove(pair<int, int> target, pair<int, int> src) {
	if (target.first < src.first && target.second == src.second) return true;
	return false;
}

bool diffusionDecomp::cornerIsLeft(pair<int, int> target, pair<int, int> src) {
	if (target.first == src.first && target.second > src.second) return true;
	return false;
}

bool diffusionDecomp::cornerIsRight(pair<int, int> target, pair<int, int> src) {
	if (target.first == src.first && target.second < src.second) return true;
	return false;
}

vector<pair<int, int>> diffusionDecomp::getIntCorners(vector<pair<int, int>> perimeter) {
	vector<pair<int, int>> out;
	int n{ static_cast<int>(perimeter.size()) };
	for (int j = 0; j < n; ++j) {
		int i{(n - 1 + j) % n }, k{(j + 1) % n };
		pair<int, int> prevCorn{ perimeter[i] }, curCorn{ perimeter[j] }, nextCorn{ perimeter[k] };
		if (cornerIsBelow(prevCorn, curCorn) && cornerIsRight(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first + 1, curCorn.second + 1 };
			out.push_back(cur);
		} else if (cornerIsLeft(prevCorn, curCorn) && cornerIsBelow(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first - 1, curCorn.second + 1 };
			out.push_back(cur);
		}
		else if (cornerIsAbove(prevCorn, curCorn) && cornerIsLeft(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first - 1, curCorn.second - 1 };
			out.push_back(cur);
		}
		else if (cornerIsRight(prevCorn, curCorn) && cornerIsAbove(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first + 1, curCorn.second - 1 };
			out.push_back(cur);
		}
		else if (cornerIsLeft(prevCorn, curCorn) && cornerIsAbove(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first + 1, curCorn.second + 1 };
			out.push_back(cur);
		}
		else if (cornerIsAbove(prevCorn, curCorn) && cornerIsRight(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first - 1, curCorn.second + 1 };
			out.push_back(cur);
		}
		else if (cornerIsRight(prevCorn, curCorn) && cornerIsBelow(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first - 1, curCorn.second - 1 };
			out.push_back(cur);
		}
		else if (cornerIsBelow(prevCorn, curCorn) && cornerIsLeft(curCorn, nextCorn)) {
			pair<int, int> cur{ curCorn.first + 1, curCorn.second - 1 };
			out.push_back(cur);
		}

	}
	return out;
}