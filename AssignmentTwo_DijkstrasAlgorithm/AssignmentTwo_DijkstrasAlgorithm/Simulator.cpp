#include "stdafx.h"
#include "Simulator.h"
#include "Graph.h"
#include "DijkstrasPath.h"

using namespace std;

// A "Monte Carlo Simulation" which generates a series of graphs and records the average path length from Node 0 to every other Node.
// An average path length is calculates from the results of all of the tests.
void Simulator::SimulateGraph() {

	// Stores the averages of all path finding tests
	double average = 0;

	for (int i = 0; i < simLoops; i++) {
		system("cls"); // I know system commands are "Evil" but it's fine here. Honest!
		cout << " Simulating Loop #" << i << endl;

		Graph graphData(simName, numberOfNodes, graphDensity, rangeMin, rangeMax);
		graphData.PrintGraphData();

		// Loop for each of the nodes in the graph (excluding the starting node (0)), setting each one as the target node
		for (int n = 1; n < numberOfNodes; n++) {
			cout << "\rTargetNode = " << n;

			DijkstrasPath path;

			double tempAverage = path.FindShortestPath(graphData, 0, n);
			if (tempAverage < INF) {
				// add to the average the value of each of the shortest paths found
				average += tempAverage;
			}

			if (n == numberOfNodes - 1 && i == simLoops - 1 ) { // On the final loop
				// calculate the mean average from the average divided by the number of path tests
				average = (average /  static_cast<double>( (numberOfNodes * simLoops) ) );
				graphData.SetAverageShortestPath(average);
				system("cls"); // nothing to see here either. Move along.
				graphData.PrintGraphData();
			}
		}
	}
}

