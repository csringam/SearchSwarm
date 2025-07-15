#pragma once
#include <vector>
#include <iostream>

using namespace std;

class adjList
{
	vector<vector<int>> m_adjList; // Adjacency list representation of a graph

public:
	// Constructors and Destructor
	adjList() = default;
	adjList(const vector<vector<int>>& adjList) : m_adjList(adjList) {}
	adjList(size_t numVertices) : m_adjList(numVertices) {} // Initialize with number of vertices
	~adjList() = default;

	// Getters and Setters
	vector<vector<int>> getAdjList() const { return m_adjList; }
	void setAdjList(const vector<vector<int>>& adjList) { m_adjList = adjList; }
	
	// Utility Functions
	void addEdge(int f, int s);
	void printAdjList() const;
	
};

