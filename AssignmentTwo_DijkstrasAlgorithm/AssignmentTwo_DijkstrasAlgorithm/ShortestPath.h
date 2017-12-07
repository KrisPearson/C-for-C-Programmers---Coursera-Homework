#pragma once

#include <vector>

class Graph;

class ShortestPath {
public:

	ShortestPath();
	~ShortestPath();
	

	std::vector< int > FindShortestPath(const Graph& graph, int startNodeIndex, int targetNodeIndex);




};

