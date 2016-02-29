#include"Graph.h"

using namespace std;

Graph::Graph(int stateNum, double edgeProbability)
{
	edgeProb = edgeProbability; // probability to flip edge bit is 50%
	states = stateNum;

	adj = new bool*[states];
	

	for (int i = 0; i < states; i++)
	{
		adj[i] = new bool[states];

		for (int j = 0; j < states; j++)
			adj[i][j] = false;
	}
}

void Graph::generate(void)
{
 	// randomize edges
	for (int i = 0; i < states; i++)
		for (int j = 0; j < states; j++)
			if ( ((double) rand() / RAND_MAX ) < edgeProb)
				adj[i][j] = true;
}

void Graph::dumpMatrix(void)
{
	// print graph adjacency matrix
	for (int i = 0; i < states; i++)
	{
		for (int j = 0; j < states; j++)
			cout << adj[i][j] << " ";

		cout << endl;
	}
}

void Graph::outputDot(void)
{
	// output dot file for graphviz corresponding to adj matrix
	ofstream file("output_graph.dot");

	file << "digraph G {" << endl;

	char first, second, ref = 'A'; 


	for (int i = 0; i < states; i++)
		for (int j = 0; j < states; j++)
		{
			if (adj[i][j] == true)
			{
				first = ref + i;
				second = ref + j; 
			       	file << first << " -> " << second << endl;	
			}
		}

	file << "}";
}

bool Graph::isConnected(void)
{
	// check if randomized graph is a connected graph
}
