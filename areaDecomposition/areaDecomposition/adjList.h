#pragma once
#include <vector>
#include <iostream>

using namespace std;

class adjList
{
	vector<vector<int>> m_adjList; // Adjacency list representation of a graph
	vector<float> m_proportions; // Proportions associated with vertices (optional)

public:
	// Constructors and Destructor
	adjList() = default;
	adjList(const vector<vector<int>>& adjList) : m_adjList(adjList) {}
	adjList(size_t numVertices) : m_adjList(numVertices), m_proportions(numVertices) {} // Initialize with number of vertices
	~adjList() = default;

	// Getters and Setters
	vector<vector<int>> getAdjList() const { return m_adjList; }
	void setAdjList(const vector<vector<int>>& adjList) { m_adjList = adjList; }
	void setProportions(const vector<float>& proportions) { m_proportions = proportions; }
	
	// Utility Functions
	void addEdge(int f, int s);
	void printAdjList() const;
	void printProportions() const;
};

