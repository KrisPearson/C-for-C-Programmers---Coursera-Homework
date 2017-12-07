// AssignmentTwo_DijkstrasAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Graph.h"
#include "ShortestPath.h"

using namespace std;

const int NUMBER_OF_NODES = 10;

int main() {

	/*
	TODO:
	1. Generate UNDIRECTED graph - randomly generated set of edges with posative distance values
	2. The random graph procedure should have edge density as a parameter and distance range as a parameter. So a graph whose density is 0.1 would have 10% of its edges picked at random and its edge distance would be selected at random from the distance range.
	3. 
	4. In an instance where there is no path between 1 and n, omit that value from the average. This should be very rare for the chosen density and size in this homework
	5. Output an average shortest path length calculated for a graph with .4 density and .2 density
	*/

	double edgeDensityInput;

	cout << "Please define the edge density for the graph: ";
	cin >> edgeDensityInput;

	Graph graphData(NUMBER_OF_NODES, edgeDensityInput, 1, 5);

	graphData.PrintAdjecencyMatrix();
	graphData.PrintGraphData();

	ShortestPath path = ShortestPath();

	vector<int> shortestPath = path.FindShortestPath(graphData, 0, 5);
	for (int i = 0; i < shortestPath.size(); i++) {
		cout << shortestPath[i];
	}

	int n;
	cin>>n;

    return 0;
}



