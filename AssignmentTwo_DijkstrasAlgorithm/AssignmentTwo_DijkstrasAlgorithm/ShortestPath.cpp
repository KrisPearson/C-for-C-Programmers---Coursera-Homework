#include "stdafx.h"
#include "ShortestPath.h"
#include "Graph.h"
#include "Heap.h"

#include <vector>
#include <map>

#include <queue>

#include <iostream> // TODO: remove me

using namespace std;

ShortestPath::ShortestPath() {

}

ShortestPath::~ShortestPath() {


}






vector< int >  ShortestPath::FindShortestPath(const Graph & graph, int startNodeIndex, int targetNodeIndex) {

	/*
	1.Add starting node to closed set.
	2.For every node in the closed set, find all the adjacent nodes and add the distance traveled from 
		the parent node to the distance to the next node.
		If there are two nodes in the closed set that share a neighbor, give the neighboring node the shorter distance.
	3.Find the node with the shortest distance.
	4.Add node to closed set.
	If node is the goal, end the process.
	Otherwise, repeat from step 2.
	*/




	// Store the number of Nodes in the graph
	const int graphSize = graph.GetSize();

	if (targetNodeIndex > graphSize-1 || targetNodeIndex < 0) {
		cout << "Pathfinding Failed - targetNode not in range";
		return{};
	}
	if (startNodeIndex > graphSize-1 || startNodeIndex < 0) {
		cout << "Pathfinding Failed - startNode not in range";
		return{};
	}

	Node* startNode = graph.GetNodeByIndex(startNodeIndex);
	Node* targetNode = graph.GetNodeByIndex(targetNodeIndex);

				//https://www.youtube.com/watch?v=LDCa4U-ZbJ0

	// Contains the shortest distance so far from the start to a given Node
	map<const Node*, int> distancesMap;

	// Used to recall the path taken, by storing a "trail" of Nodes
	map< const Node*, Node*> predecessorNodeMap;

	// All Nodes that are unvisited
	//vector<Node*> unexploredNodes(graphSize); // Does this need to be a priority Queue? https://stackoverflow.com/questions/20503059/using-dijkstras-algorithm-with-an-unordered-map-graph
	
	// Unexplored Nodes
	Heap<Node*> openSet(graphSize);


	for (int i = 0; i < graphSize; i++) {
		Node* tempNodeRef = graph.GetNodeByIndex(i);

		// If a Node is found to have zero Edges, then skip it as it is unreachable.
		if (tempNodeRef->GetEdgeCount() <= 0) continue; 
		
		distancesMap[tempNodeRef] = INT_MAX; // Assign the distance from the start Node to all over Nodes as infinity

		//predecessorNodeMap[tempNodeRef] = nullptr; // Initially, no Node has any parent/predecessor
		//unexploredNodes[i] = tempNodeRef; // Add all unexplored nodes to 
		//openSet.Add(tempNodeRef); // TODO: consider do we want to fill open set now?
	}

	openSet.Add(startNode); 

	//
	predecessorNodeMap.insert({ startNode, nullptr });

	// Set the distance from the startNode to the StartNode to zero.
	distancesMap[startNode] = 0;
	
	// TODO:Check to see whether end node is in unexploredNodes, if so then fail pathfinding

	std::cout << "openset size = " << openSet.GetCurrentItemCount() << endl;

	while (openSet.GetCurrentItemCount() > 0) {

		//foreach(Node* n in unexploredNodes) {}	
		//sort(unexploredNodes.begin(), unexploredNodes.end(), CompareNodes(distancesMap) );
		//need to sort unexplored nodes by values in distanceMap

		Node* currentNode = openSet.RemoveFirst();
		std::cout << "openset size = " << openSet.GetCurrentItemCount() << endl;

		if (currentNode == nullptr) { break; }


		cout << "-----------------------------------" << endl;
		cout << "Current Node index = " << currentNode->GetIndex() << endl;
		cout << "-----------------------------------" << endl;


		if (currentNode == targetNode) {
			//pathSuccess = true;
			cout << "Path Search Succeeded" << endl;
			cout << "Distance from start = " << distancesMap[currentNode] << endl;
			cout << " Target's parent Node = " << predecessorNodeMap[targetNode] << " - " << distancesMap[predecessorNodeMap[targetNode]] << endl; // ISSUE HERE distance is apparently 1 from start to target's parent?
																	// could possible just record the nodes, and use the node reference to get the distance. (predecessorMap)
			break;
		}

		predecessorNodeMap.insert({ currentNode, nullptr } );

		vector< pair< Node*, int> > neighbours = currentNode->GetAllNeighbours();

		for (vector<pair<Node*, int> >::iterator edgeIt = neighbours.begin(); edgeIt != neighbours.end(); ++edgeIt) {

			if (predecessorNodeMap.find(edgeIt->first) != predecessorNodeMap.end()) {
				cout << "Node " << edgeIt->first <<" in closed list. Skipped. " << endl;
				continue;
			}

			int tempDist = distancesMap[currentNode] + edgeIt->second; // cost to the current node from the start plus the edge weight

			cout << "edgeIt Node index = " << edgeIt->first->GetIndex() << ". edgeIt Weight = " << edgeIt->second << endl;
			cout << "distance to current node from start = " << distancesMap[currentNode] << ". plus distance along current edge = " << tempDist << endl;

			if (tempDist < distancesMap[edgeIt->first] || !openSet.Contains(edgeIt->first) ) {
				distancesMap[edgeIt->first] = tempDist;
				predecessorNodeMap[edgeIt->first] = currentNode; // neighbour's parent = current node




				// Add the node to the open set, if it is not already added
				if (!openSet.Contains(edgeIt->first)) {
						cout << "Add Node index " << edgeIt->first->GetIndex() << " Node Address = " << edgeIt->first << endl;
						openSet.Add(edgeIt->first);
					}
				//else openSet.UpdateItem(edgeIt->first);
			//	}
			}
			/*
			if (predecessorNodeMap.Contains(neighbour)) {  // Ignore/skip nodes in closed set
				continue;
			}

			int newCostToNeighbour = currentNode.gCost + GetDistance(currentNode, neighbour);
			if (newCostToNeighbour < neighbour.gCost || !openSet.Contains(neighbour)) {
				neighbour.gCost = newCostToNeighbour;
				neighbour.hCost = GetDistance(neighbour, targetNode);
				neighbour.parent = currentNode;

				if (!openSet.Contains(neighbour))
					openSet.Add(neighbour);
				else openSet.UpdateItem(neighbour);
			}
			*/
		}
		std::cout << "End while loop openset size = " << openSet.GetCurrentItemCount() << endl;
		cout << endl << endl;
	}

	cout << "Path Search Loop Ended" << endl;


	//TODO: RetracePath() and make a proper return value from pred node map
	vector<int> tempReturnVector;

	//for (int i = 0; i < predecessorNodeMap.size(); i++) {
	//Node* n = predecessorNodeMap.
	//tempReturnVector.push_back([i]->Get);
	// }


	//openSet.RemoveFirst();


	//Node* c;
	//Implementation<Node*> i;

	//i.index;

	//i.func(c);


	return vector<int>();
}


	/*


	if (startNode != targetNode) {
		Heap<Node*> openSet(graphSize); // Unvisited Nodes
		vector<int> closedSet(graphSize); // the indecies of visited nodes
		openSet.Add(startNode);

		//get the best distance so far to a node
		vector< pair<int, int> > distances; 



		

		while (openSet.GetCurrentItemCount() > 0) {

			Node* currentNode = openSet.RemoveFirst();

			// Check whetehr the current node is the target node
			if (currentNode == targetNode) {
				foundTargetNode = true;
				break;
			}

			if (breakPoint > graphSize) {
				// no path found
				break;
			}
			
			closedSet.Add(currentNode);

			List<Node> neighbourNodes = new List<Node>();
			foreach(Node neighbour in currentNode.neighbours) {
				if (neighbour != null && neighbour.isWalkable) {
					neighbourNodes.Add(neighbour);
				}
			}
			

			vector<pair<int, int> > neighbourNodes = currentNode->GetAllNeighboursIndicesAndWeight();

			for (vector<pair<int, int> >::iterator neighbourIt = neighbourNodes.begin(); neighbourIt != neighbourNodes.end(); ++neighbourIt) {
				
				if (std::find(closedSet.begin(), closedSet.end(), neighbourIt->first) != closedSet.end()) continue; //Ignore nodes in the closed set

				int newCostToNeighbour = currentNode->GetEdgeWeight( (graph.GetNodeByIndex(neighbourIt->first)) );
				//if (newCostToNeighbour < )
			}

		}
		*/


	/*
	Is-Connected Algorithm
	1. Start with startNode, and determine which Nodes can be reached from startNode
	2. Place them in the openSet
	3. Each iteration adds one node to the closed set.
	4. This stops when there are no further reachable nodes and no connection is made or all nodes are included in the closed set
	*/





	/*


	vector<int> distance(graphSize); // the distance from the start Node

	// contains all of the Nodes that have been visited
	vector<const Node*> visitedNodes(graphSize); 

	vector<int> unvisitedNodeIndices(graphSize);

	// contains the path taken. This will be the return value.
	vector<int> pathIndices(graphSize); 

	int nextNodeIndex = 0;


	for (int i = 0; i < graphSize; i++) { // need 1 to n here?
		distance[i] = INF; // Unknown distance from source to v
		unvisitedNodeIndices[i]; // Add all nodes to unvisited vector
	}

	distance[startNodeIndex] = 0; // The distance from startNode to startNode is set to 0

	// while there are still nodes that remain unvisited
	//while (unvisitedNodeIndices.size() > 0) { 
		//
		//

		//int weight = 

	//}


	//vector<const Node*> closedSet(graphSize);
	//vector<const Node*> openSet(graphSize);
	//openSet.push_back(startNode); // add the start node to the openSet
	*/





