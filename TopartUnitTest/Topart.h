#pragma once
// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#define NINF INT_MIN
#define READ_DATA_FROM_FILE 1
using namespace std;

// Graph is represented using adjacency list. Every node of adjacency list
// contains vertex number of the vertex to which edge connects. It also
// contains weight of the edge
class AdjListNode
{
	int v;
	int weight;
public:
	AdjListNode(int _v, int _w);
	int getV();
	int getWeight();
};

// Class to represent a graph using adjacency list representation
class Graph
{
	int distance = 0;
	int bestPath[10000];
	int bestPathIndex = 0;
	int maxDistance = 0;
	int bestDistance = 0;
	
	int compNumber = 0;
	bool **indexOfPairCompCity;
	string *city;

	

		   // Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

	// A function used by longestPath
	void printAllPathsUtil(int, int, bool[], int[], int &);
public:
	int compCounter = 0;
	int V; // No. of vertices’

				  // function to add an edge to graph
	void addEdge(int u, int v, int weight);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);

	void PrintBestPathEndDistance();
	void ReadDatasFromConsole();
	void ReadDatasFromFile(string path);
	void CheckNumberOfCompTravel();
	void Init();
	void StartProgram(string path);
	void DFS(int s, int d);
	void DFSUtil(int s, int d, vector<bool> &visited);


};

