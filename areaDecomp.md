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

# Notes on Graph Theorey
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
    
- Edges can be directed or undirected
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

# Notes on Area Decomp

- Proposed Methodology
	- Exact Cellular Decomposition:
 		- Environment is divided into **non-overlapping cells**.
  		- Coverage within each cell is simple (e.g., back-and-forth motions).
  		- The global coverage problem reduces to planning transitions between cells.
	- Boustrophedon Decomposition:
		- New decomposition technique introduced in this paper.
	 	- Name means "the way of the ox" — inspired by how an ox plows a field (straight line, turn, repeat).
	  	- Decomposes free space so each cell can be covered using boustrophedon (back-and-forth) motions.
	  	- Validated with simulations and tested on a **Nomadic 200 mobile robot**.
- Background and Prior Work
 	- Manual Programming Approaches:
 		- Early work like \[Colegrave and Branch, 1994] required explicit programming of paths.
   		- Relied on environmental landmarks.
	- Demeter Project \[Ollis and Stentz, 1996]:
		 - Used vision to follow previous crop cuts.
		 - Limited to rectangular fields.
   	- Non-holonomic Robot Constraints**:
   		- \[Hofner and Schmidt, 1995]: Used templates to handle motion constraints, but only in bounded, obstacle-free regions.
	- Resolution-Complete Algorithms**:
 		- \[Zelinsky et al., 1993]: Worked in discretized environments; suitable for unstructured terrain.
   	- Multi-Robot and Incremental Approaches:
		- \[Kurabayashi et al., 1996]: Similar method using cooperating robots, but no proof.
		- \[Hert et al., 1996]: Similar in the planar case but:
			- Less complete than the proposed method.
			- More complex (many special cases).
			- Their main strength: **incremental design** useful for sensor-based robot implementation.
- Exact Cellular Decomposition
	- Cellular Decomp: free configuration space decomposed into cells so union of cells is original free space
		- free configuration space: et of all robot configurations where the robot does not overlap an obstacle
	- Each cell is node in graph, adjacent cells have edge connecting nodes (adjacency graph)
		- walk though boils down to TSP (traveling salesman problem)
	- Trapezoidal Decomposition: robot free space path decomposed into trapezoidal cells
		- each cell can be covered in back and forth motions
		- coverage achieved through TSP of adjacency graph
		- vertical line (slice) sweeps left - right through bounded environment populated w/ polygonal obstacles
		- cells formed through "open" and "close" operations when slice encounters an event
			- event: instance which slice intersects vertex of polygon
			- 3 types: IN (current cell closed and 2 opened), OUT (2 cells closed and 1 open), MIDDLE (1 close 1 open)
   			- ![image](https://github.com/user-attachments/assets/e95fdb25-3513-49e3-bdec-6231e5696a13)

		- Too much redundant back and forth motion
		- Requires environment to be polygonal
			- ![image](https://github.com/user-attachments/assets/0728859c-6222-4828-b07f-7edb2714ff91)
2.2
