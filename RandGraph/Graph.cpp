﻿#include<iostream>
#include<list>
#include<set>
#include<vector>
#include<algorithm>
#define INF 2 << 22 // ~~83k
using namespace std;

struct Graph {
	int V; // count of the nodes in the graph
	set<int, greater<int> >* adjList;
};

//fucntions:
void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& dist);
void addEdge(Graph* graph, int src, int dest);
Graph* build_random_graph(int V, float p);
int diameter(Graph* graph);
bool Is_Isolated(Graph* graph);
bool connectivity(Graph* graph);



// A utility function that creates a graph of V vertices
Graph* createGraph(int V)
{
	Graph* graph = new Graph;
	graph->V = V;

	// Create an array of sets representing
	// adjacency lists.  Size of the array will be V
	graph->adjList = new set<int, greater<int> >[V];

	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest)
{
	// Add an edge from src to dest.  A new
	// element is inserted to the adjacent
	// list of src.
	graph->adjList[src].insert(dest);

	// Since graph is undirected, add an edge
	// from dest to src also
	graph->adjList[dest].insert(src);
}


//A utility function to print the adjacency
//list representation of graph
void printGraph(Graph* graph)
{
	for (int i = 0; i < graph->V; ++i) {
		set<int, greater<int> > lst = graph->adjList[i];
		cout << i << ": ";
		for (auto itr = lst.begin(); itr != lst.end(); ++itr)
			cout << *itr << " ";
		cout << endl;
	}

}

//Searches for a given edge in the graph
int searchEdge(Graph* graph, int src, int dest)
{
	auto itr = graph->adjList[src].find(dest);

	if (itr == graph->adjList[src].end())
		/*cout << endl << "Edge from " << src
		<< " to " << dest << " not found."
		<< endl;*/
		return 0;
	else
		/*cout << endl << "Edge from " << src
		<< " to " << dest << " found."
		<< endl;*/
		return 1;
}


Graph* build_random_graph(int V, float p) {
	Graph* graph;
	graph = createGraph(V);
	for (int i = 0; i < V; i++) {
		for (int j = i + 1; j < V; j++)
		{
			float r = ((float)rand() / (RAND_MAX + 1.0)); //rolls "random" theta
			if (r <= p)
				addEdge(graph, i, j);
		}
	}
	return graph;
}

int diameter(Graph* graph) {

	int diameter = 0;
	//for each vertex in the graph 
	for (int i = 0; i < graph->V; i++) {
		vector<bool> visited;
		vector<int> dist;
		BFS(graph, i, visited, dist);
		// distance from the start vertex to the farthest leaf
		int max_dist = *max_element(dist.begin(), dist.end());
		if (max_dist == INF)
			return INF;
		if (diameter < max_dist)
			diameter = max_dist;
	}
	return diameter;
}

bool Is_Isolated(Graph* graph) {

	for (int i = 0; i < graph->V; i++) {
		// check if the "i" node has neighbors attached with an edge
		if (graph->adjList[i].empty())
			return true;
		continue; /* למה אנחנו צריכים את זה?*/
	}
	return false;
}

bool connectivity(Graph* graph) {
	vector<bool> visited;
	vector<int> dist;

	BFS(graph, 0, visited, dist);

	//stating from the second vertex
	for (int i = 1; i < graph->V; i++) {
		if (!visited[i]) // if not visited that means BFS fucntion hasn't reached all the nodes
			return false;
	}
	return true;
}

void BFS(Graph* graph, int startVertex, vector<bool>& visited, vector<int>& distance) {
	// resize the vectors (visited and distance arrays) and intialise with false
	visited.resize(graph->V, false);
	distance.resize(graph->V, INF);

	for (int v = 0; v < graph->V; ++v) {
		distance[v] = INF;
		visited[v] = false;
	}
	// initialising the start vertex
	distance[startVertex] = 0;
	visited[startVertex] = true;

	//create queue for bfs and push the start vertex
	list<int> queue;
	queue.push_back(startVertex);

	while (!queue.empty())
	{
		startVertex = queue.front();
		queue.pop_front();
		// for each neighbors of 'i' vertex
		for (auto i : graph->adjList[startVertex])
		{
			// mark as visited, push into the queue, save distance from starting node
			if (!visited[i])
			{
				visited[i] = true;
				queue.push_back(i);
				distance[i] = distance[startVertex] + 1;
			}
		}
	}
}


int main() {
	int ok = 0;
	//printGraph(graph1);
	for (int i = 0; i < 100; i++) {
		Graph* graph1 = build_random_graph(1000, 0.012);
		if (connectivity(graph1))
			ok++;
		delete[] graph1->adjList;
		delete graph1;
	}
	cout << ok;
	//cout << is_isolated(graph1)<<endl;
	//cout << diameter(graph1);
	return 0;
}