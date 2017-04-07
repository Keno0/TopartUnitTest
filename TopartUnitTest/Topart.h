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
	bool isItComp;
public:
	AdjListNode(int _v, int _w, int isItComp);
	int getIsItComp();
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
	int compIndex = 0;
	int finalCompIndex = 0;
	int *startPointsOfComps;
	int *finalStartPointsOfComps;
	vector<size_t> distanceArray;
	list < vector<size_t>> finalPath;
	int V; // No. of vertices’

				  // function to add an edge to graph
	void addEdge(int u, int v, int weight, int isItComp);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);
	void Graph::dfs(size_t, size_t, const vector<vector<size_t> > &);
	void Graph::print(vector<size_t>);
	void PrintBestPathEndDistance();
	void ReadDatasFromConsole();
	void ReadDatasFromFile(string path);
	void CheckNumberOfCompTravel();
	void Init();
	void StartProgram(string path);
	void DFS(int s, int d);
	void DFSUtil(int s, int d, vector<bool> &visited);


};

