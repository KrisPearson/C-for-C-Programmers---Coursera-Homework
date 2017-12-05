#include "stdafx.h"
#include "Graph.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <iomanip>



inline const int Edge::GetEndNodeIndex() { return endNode->GetIndex(); } // Defined in .cpp as Node member function requires definition before Edge can use it.


Graph::Graph(int numberOfNodes, double edgeDensity, int rangeMin, int rangeMax) {
	if (numberOfNodes <= 0) {
		return;
	}

	nodes = vector<Node*>(numberOfNodes);
	for (int i = 0; i < numberOfNodes; i++) {
		Node *newNode = new Node(i); //we use i so that each Node possesses a unique index
		nodes[i] = newNode; // add the new node to the nodes vector
	}

	//Itterate through all possible undirected edges and place the edge in the graph if a random probability calculation is less than the density.
	srand(static_cast<int>(time(NULL))); // set a random seed for generating edges throughout the graph
	for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
		for (vector<Node*>::iterator it2 = nodes.begin(); it2 != nodes.end(); ++it2) {
			// Compares the edge density to a randomly generated double between 0 and 1.
			// bHasEdge should be true approximately n percent of times, where n is edgeDensity as a value between 0 and 1.

			bool bHasEdge = ((rand() % 100) / 100.0 <= edgeDensity ? true : false);
			if (bHasEdge) {
				int edgeWeight = rand() % (((rangeMax + 1) - rangeMin)) + rangeMin; // generate a randome number between the minimum and maximum range

																					// Add an undirected edge for both nodes towards oneanother
																					// If the Edge already exists, then no new Edge is added 
				(*it1)->AddEdge((*it2), edgeWeight);
				(*it2)->AddEdge((*it1), edgeWeight);
			}

			//vector< pair<int, int> > newVector = (*it1)->GetAllNeighboursIndicesAndWeight();
			//if (newVector.size() > 0)
			//	cout <<   "Node ID = " << newVector[0].first << ". Weight = " << newVector[0].second << endl;
		}
	}
}

// Destructor
Graph::~Graph() {
	// Delete the Nodes when the Graph goes out of scope
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}

// Prints the adjecency matrix for this Graph, showing the existence of edges between nodes 
void Graph::PrintAdjecencyMatrix() {
	PrintDivideLineAndTitle(" Adjecency Matrix ");

	int nodeNo = 1;
	for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
		cout << "node:" << setw(3) << nodeNo << "|";

		for (vector<Node*>::iterator it2 = nodes.begin(); it2 != nodes.end(); ++it2) {
			cout << (*it1)->CheckForEdge(*it2);
		}
		nodeNo++;
		cout << endl;
	}
}

void Graph::PrintGraphData() {
	PrintDivideLineAndTitle(" Graph Data ");
	cout << "================================" << endl;
	cout << "           Node Count = " << nodes.size() << endl;
	cout << "           Edge Count = " << GetNumberOfEdges() << endl;
	cout << "        Graph Density = " << setprecision(1) << CalculateGraphDensity() << endl;
	cout << "Average Shortest Path = " << "?" << endl;
	cout << "================================" << endl;
	// TODO: provide prompt to calculate shortest path?
}

// Prints a line to separate sections of the output stream. Also has the option to display a title message below.
void Graph::PrintDivideLineAndTitle(string stringToPrint) {
	for (int i = 0; i < 60; i++) {
		cout << "_";
	}
	cout << endl;
	cout << stringToPrint.c_str() << endl;

	for (int i = 0; i < stringToPrint.length(); i++) {
		cout << "=";
	}
	cout << endl << endl;
}
