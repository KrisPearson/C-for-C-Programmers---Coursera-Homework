#include "stdafx.h"
#include "Graph.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <iomanip>



// Defined in .cpp as Node member function requires definition before Edge can use it.
inline  int Edge::GetEndNodeIndex() { return endNode->GetIndex(); } 

// Randomly generates a graph of Nodes and Edges using given values.
Graph::Graph(string graphName, int numberOfNodes, double edgeDensity, int rangeMin, int rangeMax) {
	if (numberOfNodes <= 0) {
		return;
	}

	this->graphName = graphName;

	nodes = vector<Node*>(numberOfNodes);
	for (int i = 0; i < numberOfNodes; i++) {
		Node *newNode = new Node(i); //we use i so that each Node possesses a unique index
		nodes[i] = newNode; // add the new node to the nodes vector
	}

	//Itterate through all possible undirected edges and place the edge in the graph if a random probability calculation is less than the density.
	srand(static_cast<int>(time(0))); // set a random seed for generating edges throughout the graph
	for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
		for (vector<Node*>::iterator it2 = nodes.begin(); it2 != nodes.end(); ++it2) {

			// If the iterators point to the same Node, then don't add any edges.
			if ((*it1) != (*it2)) {
				// Compares the edge density to a randomly generated double between 0 and 1.
				// bHasEdge should be true approximately n percent of times, where n is edgeDensity as a value between 0 and 1.
				bool bHasEdge = ((rand() % 100) / 100.0 <= edgeDensity ? true : false);
				if (bHasEdge) {
					int edgeWeight = rand() % (((rangeMax + 1) - rangeMin)) + rangeMin; // generate a randome number between the minimum and maximum range

					// Add an undirected edge for both nodes towards oneanother
					// If the Edge already exists, then no new Edge is added. 
					(*it1)->AddEdge((*it2), edgeWeight);
					(*it2)->AddEdge((*it1), edgeWeight);
				}
			}
		}
	}
}

// Destructor
Graph::~Graph() {
	// Delete the Nodes when the Graph goes out of scope
	for ( unsigned int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}

// Prints the adjecency matrix for this Graph, showing the existence of edges between nodes 
// Primarily used for debugging purpo
void Graph::PrintAdjecencyMatrix() {
	PrintDivideLineAndTitle(" Adjecency Matrix ");

	int nodeNo = 0;
	for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
		cout << "node:" << setw(3) << nodeNo << "|";

		for (vector<Node*>::iterator it2 = nodes.begin(); it2 != nodes.end(); ++it2) {
			cout << (*it1)->CheckForEdge(*it2);
		}
		nodeNo++;
		cout << endl;
	}
}

// Prints information about this graph
void Graph::PrintGraphData() {
	string s;
	s.append("Graph Data for ");
	s.append(graphName);

	PrintDivideLineAndTitle( s );
	cout << "================================" << endl;
	cout << "           Node Count = " << nodes.size() << endl;
	cout << "           Edge Count = " << GetNumberOfEdges() << endl;
	cout << "        Graph Density = " << setprecision(2) << CalculateGraphDensity() << endl;
	cout << "Average Shortest Path = " << averageShortestPath << endl;
	cout << "================================" << endl;
}

// Populates the Adjecency list passed as a parameter.
// This array contains the neighbours for each node, along with the weight of the edge between the two nodes.
// A list is used as it complements the way Edges are stored within Nodes, allowing itteration through edges via their owning Node
void Graph::PopulateAdjecencyList(std::vector<std::pair<int, int>>* adjacencyList) {
	// for each node, get the neighbours and add them to the Adjecency List
	for (int n = 0; n < GetSize(); n++) { // for each node	
		Node* node = GetNodeByIndex(n);
		adjacencyList[n] = node->GetAllNeighboursIndicesAndWeight();
	}
}


// Prints a line to separate sections of the output stream. Also has the option to display a title message below.
void Graph::PrintDivideLineAndTitle(string stringToPrint) {
	for (int i = 0; i < 60; i++) {
		cout << "_";
	}
	cout << endl;
	cout << stringToPrint.c_str() << endl;

	for (unsigned int i = 0; i < stringToPrint.length(); i++) {
		cout << "=";
	}
	cout << endl << endl;
}
