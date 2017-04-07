// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Topart.h"

using namespace std;

AdjListNode::AdjListNode(int _v, int _w)
{
	v = _v;
	weight = _w;
}

int AdjListNode::getV()
{
	return v;
}

int AdjListNode::getWeight()
{
	return weight;
}


void Graph::PrintBestPathEndDistance()
{
	cout << "Best distance: " << bestDistance << endl;
	cout << "Best Path: ";
	for (int i = 0; i < bestPathIndex; i++)
	{
		cout << bestPath[i] << " ";
	}
	cout << endl;
}



void Graph::StartProgram(string path)
{
#if READ_DATA_FROM_FILE
	ReadDatasFromFile(path);
#else
	ReadDatasFromConsole();
#endif

	printAllPaths(0, V - 1);
	CheckNumberOfCompTravel();
}

void Graph::Init()
{
	city = new string[V];
	adj = new list<AdjListNode>[V];
	indexOfPairCompCity = new bool*[V];
	for (int i = 0; i < V; i++)
	{
		indexOfPairCompCity[i] = new bool[V];
	}

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			indexOfPairCompCity[i][j] = false;
		}
	}
}

void Graph::addEdge(int u, int v, int weight)
{
	AdjListNode node(v, weight);
	adj[u].push_back(node); // Add v to u’s list
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

						// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited,
		path, path_index);
}



// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[],
	int path[], int &path_index)
{
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{
		if (distance > bestDistance && distance <= maxDistance)
		{
			bestDistance = distance;
			bestPathIndex = path_index;
			for (int i = 0; i < path_index; i++)
			{
				bestPath[i] = path[i];
			}
		}
	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current vertex
		list<AdjListNode>::iterator i;

		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			if (!visited[i->getV()])
			{
				distance += i->getWeight();
				printAllPathsUtil(i->getV(), d, visited, path, path_index);
				distance -= i->getWeight();
			}
		}
	}

	// Remove current vertex from path[] and mark it as unvisited

	path_index--;
	visited[u] = false;
}




void Graph::ReadDatasFromConsole()
{
	//Read the number of cities
	cin >> V;

	//Increase because the endpoint is the first city
	V++;

	Init();

	//Read name of cities
	for (int i = 0; i < V - 1; i++)
	{
		cin >> city[i];
	}
	city[V - 1] = city[0];

	//Read distance of cities
	int tempNumber = 0;
	for (int i = 0; i < V - 1; i++)
	{
		cin >> tempNumber;
		addEdge(i, i + 1, tempNumber);
	}

	//Number of comps
	cin >> compNumber;

	//Store indexes comp city pairs
	string firstCity = "";
	string secondCity = "";
	int indexOfFirstCity = 0;
	int indexOfSecondCity = 0;
	int compDis = 0;
	for (int i = 0; i < compNumber; i++)
	{
		//store comp data line by line
		cin >> firstCity;
		cin >> secondCity;
		cin >> compDis;

		//Finc comp city index
		for (int i = 0; i < V; i++)
		{
			if (city[i].compare(firstCity) == 0)
			{
				indexOfFirstCity = i;
			}

			if (city[i].compare(secondCity) == 0)
			{
				indexOfSecondCity = i;
			}
		}

		//Comp representation edge
		addEdge(indexOfFirstCity, indexOfSecondCity, compDis);
		//Set the true value in comp list
		indexOfPairCompCity[indexOfFirstCity][indexOfSecondCity] = true;
		indexOfPairCompCity[indexOfSecondCity][indexOfFirstCity] = true;

	}

	//Store max distance
	cin >> maxDistance;
}

void Graph::ReadDatasFromFile(string path)
{
	ifstream infile;
	infile.open(path);
	int tempNumber = 0;
	
	//Read the number of cities
	infile >> V;

	//Increase because the endpoint is the first city
	V++;

	Init();	

	//Read name of cities
	for (int i = 0; i < V - 1; i++)
	{
		infile >> city[i];
	}
	city[V - 1] = city[0];

	//Read distance of cities
	for (int i = 0; i < V-1; i++)
	{
		infile >> tempNumber;
		addEdge(i, i + 1, tempNumber);
	}

	//Number of comps
	infile >> compNumber;

	//Store indexes comp city pairs
	string firstCity = "";
	string secondCity = "";
	int indexOfFirstCity = 0;
	int indexOfSecondCity = 0;
	int compDis = 0;
	for (int i = 0; i < compNumber; i++)
	{
		//store comp data line by line
		infile >> firstCity;
		infile >> secondCity;
		infile >> compDis;
		
		//Finc comp city index
		for (int i = 0; i < V; i++)
		{
			if (city[i].compare(firstCity) == 0)
			{
				indexOfFirstCity = i;
			}

			if (city[i].compare(secondCity) == 0)
			{
				indexOfSecondCity = i;
			}
		}

		//Comp representation edge
		addEdge(indexOfFirstCity, indexOfSecondCity, compDis);
		//Set the true value in comp list
		indexOfPairCompCity[indexOfFirstCity][indexOfSecondCity] = true;
		indexOfPairCompCity[indexOfSecondCity][indexOfFirstCity] = true;

	}

	//Store max distance
	infile >> maxDistance;
	infile.close();
}

void Graph::CheckNumberOfCompTravel()
{
	compCounter = 0;
	for (int i = 0; i < bestPathIndex - 1; i++)
	{
		if (indexOfPairCompCity[bestPath[i]][bestPath[i + 1]])
		{
			compCounter++;
		}
	}
	cout << compCounter << endl;
	for (int i = 0; i < bestPathIndex - 1; i++)
	{
		if (indexOfPairCompCity[bestPath[i]][bestPath[i + 1]])
		{
			cout << city[bestPath[i]] << " " << city[bestPath[i + 1]] << endl;
		}
	}

}
