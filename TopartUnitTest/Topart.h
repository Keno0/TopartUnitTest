#pragma once
// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>

#define READ_DATA_FROM_FILE 0
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
	int maxDistance = 0;
	int numberOfCity = 0;	
	int compNumber = 0;
	int *distanceArray;
	string *city;
	// Pointer to an array containing adjacency lists
	list<AdjListNode> *adj;

public:
	int compCounter = 0;
	list < vector<size_t>> finalPath;
	int V; // No. of vertices’

	void addEdge(int u, int v, int weight, int isItComp);

	// Finds longest distances from given source vertex
	void printAllPaths(int s, int d);
	void dfs(size_t, size_t, const vector<vector<size_t> > &);
	void ReadDatasFromConsole();
	void ReadDatasFromFile(string path);
	void CheckNumberOfCompTravel();
	void StartProgram(string path);

};

