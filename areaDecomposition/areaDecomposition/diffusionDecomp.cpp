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
	m_map->insertRow(static_cast<int>(m_map->getHeight()), vector<int>(m_map->getWidth(), 2)); //Bottom padding
	m_map->insertColumn(0, vector<int>(m_map->getHeight(), 2)); // Left padding
	m_map->insertColumn(static_cast<int>(m_map->getWidth()), vector<int>(m_map->getHeight(), 2)); // Right padding
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