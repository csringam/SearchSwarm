#include "adjList.h"

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