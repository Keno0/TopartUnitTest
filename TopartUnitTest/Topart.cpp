// A C++ program to find single source longest distances in a DAG
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <fstream>
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


void Graph::StartProgram(string path)
{
#if READ_DATA_FROM_FILE
	ReadDatasFromFile(path);
#else
	ReadDatasFromConsole();
#endif

	printAllPaths(0, numberOfCity);
	CheckNumberOfCompTravel();
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
				finalPath.push_back(path);//found a way!
			}

							//backtrack:
			visited[current.first] = false;//no longer considered visited
			path.pop_back();//go a step back
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
			}
		}
	}
}

void Graph::addEdge(int u, int v, int weight, int isItComp)
{
	AdjListNode node(v, weight, isItComp);
	adj[u].push_back(node); // Add v to u’s list
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	//Store the grapth in vector to handle easier
	vector < vector<size_t>> graph;

	graph.resize(V);
	for (int j = 0; j < V; j++)
	{
		list<AdjListNode>::iterator i;
		int k = 0;
		graph[j].resize(adj[j].size());
		for (i = adj[j].begin(); i != adj[j].end(); ++i)
		{
			graph[j][k] = i->getV();
			k++;
		}
	}
	// Call the non recursive helper function to find all paths
	dfs(s, d, graph);
}

void Graph::ReadDatasFromConsole() 
{

	int tempNumber = 0;
	int modifiedV = 0; // A városok plusz kompok száma

	//Read the number of cities
	cin >> V;
	numberOfCity = V;

	//Increase because the endpoint is the first city
	V++;

	//Read name of cities
	city = new string[V];
	for (int i = 0; i < V - 1; i++)
	{
		cin >> city[i];
	}
	city[V - 1] = city[0];

	//Read distance of cities
	int *distanceArray = new int[V];
	for (int i = 0; i < V - 1; i++)
	{
		cin >> distanceArray[i];
	}

	//Number of comps
	cin >> compNumber;

	//Number of points in graph
	modifiedV = V + compNumber;
	adj = new list<AdjListNode>[modifiedV]; //The graph

	//Store the edge between cities
	for (int i = 0; i < V - 1; i++)
	{
		addEdge(i, i + 1, distanceArray[i], false);
	}

	//Store edges comp city pairs
	string firstCity = "";
	string secondCity = "";
	int indexOfFirstCity = 0;
	int indexOfSecondCity = 0;
	int compDis = 0;
	int tempV = V - 1;
	for (int i = 0; i < compNumber; i++)
	{
		//store comp data line by line
		cin >> firstCity;
		cin >> secondCity;
		cin >> compDis;
		tempV++;

		//Find comp city index
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
		addEdge(indexOfFirstCity, tempV, compDis, true);
		addEdge(tempV, indexOfSecondCity, 0, true);

	}

	//Store max distance
	cin >> maxDistance;
	V = modifiedV;
}

void Graph::ReadDatasFromFile(string path)
{
	ifstream infile;
	infile.open(path);
	int tempNumber = 0;
	int modifiedV = 0; // A városok plusz kompok száma
	
	//Read the number of cities
	infile >> V;
	numberOfCity = V;

	//Increase because the endpoint is the first city
	V++;

	//Read name of cities
	city = new string[V];
	for (int i = 0; i < V - 1; i++)
	{
		infile >> city[i];
	}
	city[V - 1] = city[0];

	//Read distance of cities
	int *distanceArray = new int[V];
	for (int i = 0; i < V - 1; i++)
	{
		infile >> distanceArray[i];		
	}

	//Number of comps
	infile >> compNumber;

	//Number of points in graph
	modifiedV =V + compNumber;
	adj = new list<AdjListNode>[modifiedV]; //The graph
	
	//Store the edge between cities
	for (int i = 0; i < V - 1; i++)
	{
		addEdge(i, i + 1, distanceArray[i], false);
	}

	//Store edges comp city pairs
	string firstCity = "";
	string secondCity = "";
	int indexOfFirstCity = 0;
	int indexOfSecondCity = 0;
	int compDis = 0;
	int tempV = V - 1;
	for (int i = 0; i < compNumber; i++)
	{
		//store comp data line by line
		infile >> firstCity;
		infile >> secondCity;
		infile >> compDis;
		tempV++;
		
		//Find comp city index
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
		addEdge(indexOfFirstCity, tempV, compDis, true);
		addEdge(tempV, indexOfSecondCity, 0, true);

	}

	//Store max distance
	infile >> maxDistance;
	V = modifiedV;
	infile.close();
}

void Graph::CheckNumberOfCompTravel()
{
	int tempDistance = 0;
	int distance = 0;
	compCounter = 0;
	list < vector<size_t>>::iterator bestPath;
	
	for (list < vector<size_t>>::iterator i=finalPath.begin(); i != finalPath.end(); i++)
	{
	
		for (size_t j = 0; j < i->size()-1; j++)
		{
			for (list<AdjListNode>::iterator k = adj[i->at(j)].begin(); k != adj[i->at(j)].end(); k++)
			{
				if (k->getV() == i->at(j+1))
				{
					tempDistance += k->getWeight();
				}
			}
		}

		if (tempDistance <= maxDistance)
		{
			if (tempDistance > distance)
			{
				distance = tempDistance;
				bestPath = i;
			}
		}

		tempDistance = 0;
	}

	for (int i = 0; i < bestPath->size(); i++)
	{
		if (bestPath->at(i) > numberOfCity )
		{
			compCounter++;
		}
	}

	cout << compCounter << endl;

	for (int i = 0; i < bestPath->size(); i++)
	{
		if (bestPath->at(i) > numberOfCity )
		{
			cout << city[bestPath->at(i - 1)] << " "<< city[bestPath->at(i +1)] << endl;
		}
	}
}
