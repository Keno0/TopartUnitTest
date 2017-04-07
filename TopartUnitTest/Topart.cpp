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

AdjListNode::AdjListNode(int _v, int _w, int isItComp)
{
	v = _v;
	weight = _w;
	this->isItComp = isItComp;
}

int AdjListNode::getV()
{
	return v;
}

int AdjListNode::getIsItComp()
{
	return isItComp;
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

void Graph::print(vector<size_t> path)
{
	distance = 0;
	for (size_t i = 0; i < distanceArray.size(); i++)
		distance += distanceArray[i];
	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i] << " ";
	}
	cout << "legth: " << distance <<endl;
	finalPath.push_back(path);
}

//graph[i][j] stores the j-th neighbour of the node i
void Graph::dfs(size_t start, size_t end, const vector<vector<size_t> > &graph)
{

	//initialize:
	//remember the node (first) and the index of the next neighbour (second)
	typedef pair<size_t, size_t> State;
	stack<State> to_do_stack;
	vector<size_t> path; //remembering the way
	
	vector<bool> visited(graph.size(), false); //caching visited - no need for searching in the path-vector 
	int prevDistance = 0;

											   //start in start!
	to_do_stack.push(make_pair(start, 0));
	visited[start] = true;
	path.push_back(start);

	while (!to_do_stack.empty())
	{
		State &current = to_do_stack.top();//current stays on the stack for the time being...

		if (current.first == end || current.second == graph[current.first].size())//goal reached or done with neighbours?
		{
			if (current.first == end)
			{
				print(path);//found a way!
				distance = 0;
			}

							//backtrack:
			visited[current.first] = false;//no longer considered visited
			path.pop_back();//go a step back
			distanceArray.pop_back();
			to_do_stack.pop();//no need to explore further neighbours         
		}
		else {//normal case: explore neighbours
			size_t next = graph[current.first][current.second];
			current.second++;//update the next neighbour in the stack!
			if (!visited[next]) {
				//putting the neighbour on the todo-list
				to_do_stack.push(make_pair(next, 0));
				visited[next] = true;
				path.push_back(next);
				list<AdjListNode>::iterator i = adj[current.first].begin();
				while (i->getV() != next)
					i++;
				distanceArray.push_back(i->getWeight());
				prevDistance = distance;
			}
		}
	}
}

void Graph::addEdge(int u, int v, int weight, int isItComp)
{
	AdjListNode node(v, weight, isItComp);
	adj[u].push_back(node); // Add v to u�s list
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	vector < vector<size_t>> graph;

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

						// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;
	graph.resize(V);
	for (int j = 0; j < V; j++)
	{
		list<AdjListNode>::iterator i;
		int k = 0;
		graph[j].resize(V);
		for (i = adj[j].begin(); i != adj[j].end(); ++i)
		{
			graph[j][k] = i->getV();
			k++;
		}
	}
	// Call the recursive helper function to print all paths

		dfs(s, d, graph);
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

			finalCompIndex = compIndex;
			for (int i = 0; i < finalCompIndex; i++)
			{
				finalStartPointsOfComps[i] = startPointsOfComps[i];
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
				if (i->getIsItComp())
				{
					startPointsOfComps[compIndex] = u;
					compIndex++;
					distance += i->getWeight();
					printAllPathsUtil(i->getV(), d, visited, path, path_index);
					distance -= i->getWeight();
					compIndex--;
				}
				else
				{
					distance += i->getWeight();
					printAllPathsUtil(i->getV(), d, visited, path, path_index);
					distance -= i->getWeight();
				}
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
		addEdge(i, i + 1, tempNumber, false);
	}

	//Number of comps
	cin >> compNumber;
	startPointsOfComps = new int[compNumber];
	finalStartPointsOfComps = new int[compNumber];

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
		addEdge(indexOfFirstCity, indexOfSecondCity, compDis, true);
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
		addEdge(i, i + 1, tempNumber, false);
	}

	//Number of comps
	infile >> compNumber;
	startPointsOfComps = new int[compNumber];
	finalStartPointsOfComps = new int[compNumber];

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
		addEdge(indexOfFirstCity, indexOfSecondCity, compDis, true);
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
	compCounter = finalCompIndex;

	cout << compCounter << endl;
	if (compCounter != 0)
	{
		string secondCity = "";
		for (int i = 0; i < compCounter; i++)
		{
			if (adj[finalStartPointsOfComps[i]].begin()->getIsItComp())
			{
				secondCity = city[adj[finalStartPointsOfComps[i]].begin()->getV()];
			}
			else
			{
				
				secondCity = city[(++adj[finalStartPointsOfComps[i]].begin())->getV()];
			}
			cout << city[finalStartPointsOfComps[i]] << " " << secondCity << endl;
		}
	}

}
