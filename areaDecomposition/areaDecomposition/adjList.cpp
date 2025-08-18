#include "adjList.h"

/*
name:		addEdge

inputs:		f: index of the first vertex
			s: index of the second vertex

outputs:	none

descr:		Adds an undirected edge between vertices f and s in the adjacency list.
			If either vertex index is out of bounds, an error message is printed.
*/
void adjList::addEdge(int f, int s) {
	if (f >= m_adjList.size() || s >= m_adjList.size()) {
		cerr << "Error: Vertex index out of bounds." << endl;
		return;
	}
	m_adjList[f].push_back(s);
	m_adjList[s].push_back(f); // For undirected graph
}

void adjList::printAdjList() const {
	for (size_t i = 0; i < m_adjList.size(); ++i) {
		cout << i << ": ";
		for (const auto& neighbor : m_adjList[i]) {
			cout << neighbor << " ";
		}
		cout << endl;
	}
}

void adjList::printProportions() const {
	for (size_t i = 0; i < m_proportions.size(); ++i) {
		cout << "Vertex " << i << ": " << m_proportions[i] << endl;
	}
}

void adjList::printAdjListWithProportions() const {
	for (size_t i = 0; i < m_adjList.size(); ++i) {
		cout << "Vertex " << i << ": ";
		for (const auto& neighbor : m_adjList[i]) {
			cout << fixed << setprecision(4) << (neighbor < m_proportions.size() ? m_proportions[neighbor] : 0) << " ";
		}
		cout << endl;
	}
}

/*
name:		getNeighbors

inputs:		node: index of the vertex whose neighbors are to be retrieved

outputs:	Vector of indices representing the neighbors of the specified vertex

descr:		Retrieves the neighbors of the specified vertex in the adjacency list.
			If the vertex index is out of bounds, an error message is printed.
*/
vector<int> adjList::getNeighbors(int node) const {
	if (node < 0 || node >= m_adjList.size()) {
		cerr << "Error: Node index out of bounds." << endl;
	}
	return m_adjList[node];
}