#pragma once
#include <vector>
#include <algorithm> 
#include <iterator>
#include <iostream> // temp

using namespace std;

// Used to prevent large numbers of Nodes consuming too much memory
const int MAXNODECOUNT = 500;

// forward declare the Node type
struct Node;

struct Edge {
public:
	/*
	Edge(Node* startNode, Node* endNode, int edgeWeight) {
	this->startNode = startNode;
	this->endNode = endNode;
	this->edgeWeight = edgeWeight;
	}
	*/


	Edge(const Node* startNode, const Node* endNode, int edgeWeight) :startNode(startNode), endNode(endNode), edgeWeight(edgeWeight) {}

	inline const int GetEndNodeIndex();

	inline const int GetEdgeWeight() { return edgeWeight; }

	inline friend bool operator==(const Edge& edge1, const Edge& edge2) {
		return (edge1.endNode == edge2.endNode &&
			edge1.startNode == edge2.startNode);
	};

private:

	// the Node at which this edge starts and ends respectively (i.e the direction of the edge)
	const Node *startNode;
	const Node *endNode;

	//the cost to travel between nodes along this edge
	int edgeWeight;

};


//TODO: consider using friend bool operator== () 
// Overload the == operator for comparing Edge structs for equality
// Notice, we don't compare the weight. This is because no two edges should point between the same two Nodes, so the weight neeed not be considered.

struct Node {
public:

	Node(int index) :index(index) {}

	inline int GetNumberOfEdges() { return adjecentEdges.size(); }

	// If one deoes not exists, then adds an Edge pointing from the fromNode to the toNode, with a given weight value.
	// will return true if an edge did not already exist, and so was added. False if an edge already existed.
	bool AddEdge(const Node* toNode, const int edgeWeight) {
		if (CheckForEdge(toNode)) {
			return false; // Edge not added, as one already existed
		}
		else {
			Edge newEdge(this, toNode, edgeWeight);
			adjecentEdges.push_back(newEdge);

			int edgeIndexTest = 0;

			CheckForEdge(toNode, &edgeIndexTest);

			return true; // Edge added
		}
	};

	// If an Edge exists between the fromNode and toNode, then remove it.
	// True will be returned if an Edge was found and deleted, otherwise false will be returned.
	bool DeleteEdge(const Node* toNode) {
		int edgeIndex = 0;
		if (CheckForEdge(toNode, &edgeIndex)) {

			// use the edgeIndex to erase the element containing the Edge
			adjecentEdges.erase(adjecentEdges.begin() + edgeIndex);

			//Search for the edgeusing an iterator, caching said iterator.
			//vector<Edge>::iterator newEnd = std::remove(adjecentEdges.begin(), adjecentEdges.end(), Edge(this, toNode, 0));
			//adjecentEdges.erase(newEnd, adjecentEdges.end());

		}
		else return false;
	}

	// Compares this node and the toNode to see if an edge exists between them. If so, then returns true.
	// An integer can be provided to the edgeIndex pointer in order to obtain the index of a found element, if such an element is found
	inline bool CheckForEdge(const Node* toNode, int *edgeIndex = nullptr) {
		vector<Edge>::iterator edgeIt = std::find(adjecentEdges.begin(), adjecentEdges.end(), Edge(this, toNode, 0));
		if (edgeIt == adjecentEdges.end()) {
			return false; 	// Edge not in vector
		}
		else {
			// if edgeIndex has been specified, then assign the index of the located element to it.
			if (edgeIndex != nullptr) {
				*edgeIndex = std::distance(adjecentEdges.begin(), edgeIt);

			}
			return true;
		}
	}

	int GetEdgeWeight(const Node* endNode) {
		if (CheckForEdge(endNode)) {

		}
		else return 0; // TODO: consider - could return an unreasonably large number here?
	}

	// Returns a vector of pairs containing the index ID of the neighbour on the graph and the weight of the edge in that order
	// This ID can then be used to access the neighbouring Node and its values.
	vector< pair<int, int> > GetAllNeighboursIndicesAndWeight() {
		vector< pair<int, int> > returnVector(0);
		for (vector<Edge>::iterator edgeIt = adjecentEdges.begin(); edgeIt != adjecentEdges.end(); ++edgeIt) {
			returnVector.push_back(make_pair(edgeIt->GetEndNodeIndex(), edgeIt->GetEdgeWeight()));
		}
		return returnVector;
	}

	// Returns the index value of this node
	inline const int GetIndex() const { return index; }



private:
	// the index value asociated with this node
	const int index;

	// stores all Edges associated with this Node
	vector<Edge> adjecentEdges;
	//std::vector<std::pair<int, int>, int> edges;

};

class Graph {
public:
	Graph(int numberOfNodes = 50, double edgeDensity = 0.1f, int rangeMin = 1, int rangeMax = 8);
	~Graph();

	// Uses a matrix, as opposed to a list due to the relatively low density
	// vector <vector<int> > adjecencyMatrix;

	// Returns the edge weight between the nodes
	int GetEdgeValue(int n1, int n2) { return nodes[n1]->GetEdgeWeight(nodes[n2]); };
	int GetEdgeValue(Node* n1, Node* n2) { return n1->GetEdgeWeight(n2); }

	// returns whether there is an edge from node n1 to node n2
	bool Adjecent(int n1, int n2);


#pragma region Print Functions

	// Prints a line to separate sections of the output stream. Also has the option to display a title message below.
	void PrintDivideLineAndTitle(string stringToPrint = "");

	// Prints the adjecency matrix for this Graph, showing the existence of edges between nodes 
	void PrintAdjecencyMatrix();

	void PrintGraphData();

#pragma endregion

private:


	//Performs the density equation D = (E) / (V(V -1))
	float CalculateGraphDensity() {
		float density = (/*2* not required due to the way edges are created in pairs*/static_cast<float>(GetNumberOfEdges()) / 2.f)
			/ (static_cast<float>(nodes.size()) * (static_cast<float>(nodes.size()) - 1.f)
				);
		return density;
	}

	int GetNumberOfEdges() {
		int numberOfEdges = 0;
		for (vector<Node*>::iterator it1 = nodes.begin(); it1 != nodes.end(); ++it1) {
			int noToAdd = 0;
			noToAdd = (*it1)->GetNumberOfEdges();

			numberOfEdges += noToAdd;
		}
		return numberOfEdges;
	}

	// All of the nodes belonging to this graph
	vector<Node*> nodes;

};

