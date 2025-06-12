## Area Decomposition Research

# Papers:
https://www.ri.cmu.edu/pub_files/pub4/choset_howie_1997_3/choset_howie_1997_3.pdf

https://cim.mcgill.ca/~yiannis/Publications/RekleitisCoverageJournal.pdf

https://biorobotics.ri.cmu.edu/papers/paperUploads/A028807.pdf

https://jenjenchung.github.io/anthropomorphic/Papers/Baehnemann2019revisiting.pdf

Additional Paper: 
- 2308.11478-coverage
- jaist_coverage_paper

https://brilliant.org/wiki/graph-theory/

# Considerations for each paper
- What is considered an efficient area decomp algo? Is it speed of the solver itself? Is it the actual shapes that are decomposed?
- Make sure that the number of subdivisions is controllable
- How easy is each one to implement? What are the required dependencies?

# Notes
Intro
- Vertices or nodes connected by edges
- Non-trivial graph has one or more nodes connected by edges
	- Each edge connects exactly 2 nodes
- Degree of node is num of edges connected to that node
	- if the degree of each vertex is same for a graph, that is the "degree of the graph"
- Connected graph: can reach any vertex by traversing edges
	- set of edges used is called path
- Complete graph: exists an edge connecting every two pairs of nodes
  - Number of edges correspond to this:
  - ![image](https://github.com/user-attachments/assets/f44ab456-735b-4632-b664-fcd4b97680d5)
- Can be directed or undirected
Eulerian Graphs
- All edges are visited exactly once in a sincle path
	- aka [Eulerian path](https://brilliant.org/wiki/eulerian-path/)
	- "A Eulerian graph has at most two vertices of odd degree."
- [Hamiltonian path](https://brilliant.org/wiki/hamiltonian-path/): possible to traverse graph by visiting each vertex exactly one
Planar Graphs
- Can be drawn on flat plane without any edges crossing
	- can define "face" of graph as any region bounded by edges, and containing no edges on interior
- Following must hold true, considering V as vertices, F as faces, and E as edges:
  - ![image](https://github.com/user-attachments/assets/224759b6-fa5a-478d-8ee2-85aa0b259b54)
[Graph Coloring](https://brilliant.org/wiki/graph-coloring-and-chromatic-numbers/)
- How can a graph's nodes be colored such that no adjacent vertices contain the same color
- Complete graphs have colors = num nodes
- Chromatic number (k): minimum number of colors (k - colorable)
- Can be seen when coloring a map, reduces to a graph coloring problem
	- [Four color theorem](https://brilliant.org/wiki/four-color-theorem/) - no graph corresponding to a map has a chromatic number greater than 4
