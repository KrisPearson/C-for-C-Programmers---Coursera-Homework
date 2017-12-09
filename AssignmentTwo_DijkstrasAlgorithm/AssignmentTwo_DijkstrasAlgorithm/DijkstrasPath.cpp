#include "stdafx.h"
#include "DijkstrasPath.h"

//Implementation for Dijkstra's SSSP(Single source shortest path) algorithm
//This is an optimized algorithm running in O(E*log(V))

#include <iostream>
#include <queue>
//#include <vector>
#include <climits>
#include "Graph.h"

using namespace std;

DijkstrasPath::DijkstrasPath() {
}


DijkstrasPath::~DijkstrasPath() {
}


// The following method was largely influenced by Shreyans Sheth on Quora 
// Link:https://www.quora.com/What-is-the-most-simple-efficient-C++-code-for-Dijkstras-shortest-path-algorithm
int DijkstrasPath::FindShortestPath(Graph& graph, int startNodeIndex, int targetNodeIndex) {

	//Set initial distances to Infinity
	for (int i = 0; i < MAX_NODE_COUNT; i++)
		shortestDistance[i] = INF;

	// populate the adjecency list array
	graph.PopulateAdjecencyList(adjacencyList);

	// Custom Comparator for Determining priority for priority queue (shortest edge comes first)
	class prioritize { public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2) { return p1.second > p2.second; } };
	priority_queue<pair<int, int>, vector<pair<int, int> >, prioritize> priorityQueue; //Priority queue to store vertex,weight pairs
	priorityQueue.push(make_pair(startNodeIndex, shortestDistance[startNodeIndex] = 0)); //Pushing the source with distance from itself as 0

	bool foundTarget = false;

	while (!priorityQueue.empty()) {
		pair<int, int> currentNode = priorityQueue.top(); // Current Node. The shortest distance for this has been found
		priorityQueue.pop();
		int currentNodeIndex = currentNode.first; // The Node index for the current Node
		int currentWeight = currentNode.second; // The final shortest distance for this Node

		//cout << "loop start. Node = " << currentNodeIndex << " Shortest path to this node = " << shortestDistance[currentNodeIndex] << " Queue count  = " << priorityQueue.size() << endl;

		// check to see if the current node is the target
		if (currentNodeIndex == targetNodeIndex) foundTarget = true;	

		if (closedSet[currentNodeIndex]) {// If the Node is already closedSet, skip it
			continue;
		}
		closedSet[currentNodeIndex] = true;



		// Iterate through all neighbours

		//cout << "Current Node  = " << currentNodeIndex << endl;
		for (unsigned int i = 0; i < adjacencyList[currentNodeIndex].size(); i++) {

			// If the Node has already been visited, then skip it.
			if (closedSet[adjacencyList[currentNodeIndex][i].first]) continue;		

			// If this node is not present in the closedSet, and the current parent node distance+distance from there to this node is shorter than the initial distace set to this node, then update it
			if(adjacencyList[currentNodeIndex][i].second + currentWeight < shortestDistance[adjacencyList[currentNodeIndex][i].first]) {
				
				// Set the new distance and add the Node to priority queue
				priorityQueue.push(
					make_pair(adjacencyList[currentNodeIndex][i].first, 
					(shortestDistance[adjacencyList[currentNodeIndex][i].first] = adjacencyList[currentNodeIndex][i].second + currentWeight))
				);

			}

		}
	}

	return shortestDistance[targetNodeIndex];
}