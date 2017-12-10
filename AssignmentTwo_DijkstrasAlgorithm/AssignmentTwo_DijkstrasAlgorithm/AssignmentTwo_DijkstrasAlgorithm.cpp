// C++ for C Programmers, Part A
// Homework 2 - Implement Dijkstra's Algorithm
//
// Description:This program runs repeated path finding simulations on  randomly generated graphs and finds the average shortest path
// Author: Kristian Pearson
// Date: 09/12/2017

#include "stdafx.h"
#include "Simulator.h"
#include "DijkstrasPath.h"
#include <iostream>

using namespace std;

int main() {

	// declare and define some value sfor graph generation
	// One could permit this data to be input by the user instead, but for the sake of rapid testing, it has been predefined.
	const int numOfNodes = 50;
	double graphDensity = 0.2;
	const int rangeMin = 1;
	const int rangeMax = 10;
	const int numOfLoops = 10;

	string simName = "20% Graph";
	const Simulator sim2(simName, numOfNodes, graphDensity, rangeMin, rangeMax, numOfLoops);
	sim2.SimulateGraph();

	cout << "Press any key to run second simulation..." << endl;
	cin.ignore();

	simName = "40% Graph";
	graphDensity = 0.4;
	const Simulator sim4(simName, numOfNodes, graphDensity, rangeMin, rangeMax, numOfLoops);
	sim4.SimulateGraph();

	cin.ignore();

    return 0;
}







