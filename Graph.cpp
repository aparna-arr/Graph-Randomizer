#include"Graph.h"

using namespace std;

Graph::Graph(int stateNum, double edgeProbability)
{
	edgeProb = edgeProbability; 
	states = stateNum;

	adj = new bool*[states];
	tadj = new bool*[states];
	

	for (int i = 0; i < states; i++)
	{
		adj[i] = new bool[states];
		tadj[i] = new bool[states];

		for (int j = 0; j < states; j++)
		{
			adj[i][j] = false;
			tadj[i][j] = false;
		}
	}
}

void Graph::generate(void)
{
 	// randomize edges
	for (int i = 0; i < states; i++)
		for (int j = 0; j < states; j++)
			if ( ((double) rand() / RAND_MAX ) < edgeProb && i != j)
			{
				adj[i][j] = true;
				tadj[j][i] = true;
			}

	vector< vector<int>* > SCCs = dijkstraAlg();

	cout << "SCCS: " << SCCs.size() << endl;

	for (vector<vector<int>*>::iterator it = SCCs.begin(); it != SCCs.end(); it++)
	{
		cout << "Group " << it - SCCs.begin() << " of size: " << (*it)->size() << endl;
		for (vector<int>::iterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
		{
			char letter = 'A';
			letter += *it2;
			cout << letter << " ";
		}
		cout << endl;
	}

	if (SCCs.size() > 1) // multiple sccs that must be joined
		joinSCCs(SCCs);
/*
	vector<vector<int>*> debug = dijkstraAlg();
	cout << "SCCS: " << debug.size() << endl;

	for (vector<vector<int>*>::iterator it = debug.begin(); it != debug.end(); it++)
	{
		cout << "Group " << it - debug.begin() << " of size: " << (*it)->size() << endl;
		for (vector<int>::iterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
		{
			char letter = 'A';
			letter += *it2;
			cout << letter << " ";
		}
		cout << endl;
	}
*/

	// now add self-cycles
	for (int i = 0; i < states; i++)
		adj[i][i] = tadj[i][i] = true;
}

void Graph::joinSCCs(vector< vector<int> * >& SCCs)
{
	while(SCCs.size() > 1)
	{
//		cerr << "SCCs.size is " << SCCs.size() << endl;
		int randIndex = rand() % (SCCs.size() - 1);

		int index1 = *(SCCs[randIndex]->begin() + (rand() % SCCs[randIndex]->size()));
		int index2 = *(SCCs[SCCs.size() - 1]->begin() + (rand() % SCCs[SCCs.size() - 1]->size()));


//		cerr << "randIndex is " << randIndex << " index1 is " << index1 << " index2 is " << index2 << endl;

		adj[index1][index2] = adj[index2][index1] = true;
		tadj[index1][index2] = adj[index2][index1] = true;

		// now join SCCs and pop_back()
		SCCs[randIndex]->reserve(SCCs[randIndex]->size() + SCCs[SCCs.size() - 1]->size());
		SCCs[randIndex]->insert(SCCs[randIndex]->end(), SCCs[SCCs.size()-1]->begin(), SCCs[SCCs.size()-1]->end());
		SCCs.pop_back();
	}
}
/*
void uniqueRandom(int *& ptr, int maxSize, int numNumbers)
{
	int array[maxSize+1];

	for (int i = 0; i <= maxSize; i++)
		array[i] = i;

	// numNumbers MUST be < maxSize else undefined ptr errors
	ptr = new int[numNumbers];

	for (int i = 0; i < numNumbers; i++)
	{
		int index = rand() % (maxSize + 1);
		ptr[i] = array[index];

		int tmp = array[maxSize];
		array[maxSize] = array[index];
		array[index] = tmp;
		maxSize--;
	}
}
*/
void Graph::dumpMatrix(void)
{
	// print graph adjacency matrix
	for (int i = 0; i < states; i++)
	{
		for (int j = 0; j < states; j++)
			cout << adj[i][j] << " ";

		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < states; i++)
	{
		for (int j = 0; j < states; j++)
			cout << tadj[i][j] << " ";

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

vector < vector <int> *> Graph::dijkstraAlg(void)
{
	vector< vector <int> *> masterVector ;
	Vertex * V = new Vertex[states];
	stack<Vertex *> S;

	for (int i = 0; i < states; i++)
	{
		V[i].number = i;
		V[i].index = 0; // == white
		V[i].visited = false;
		V[i].onStack = false;
	}

	for (int i = 0; i < states; i++)
		if (V[i].visited == false)
			DFS(V, S, i, false);

	for (int i = 0; i < states; i++)
	{
		V[i].index = 0; // == white
		V[i].visited = false;
	}

	while (!S.empty())
	{
		Vertex * v = S.top();
		S.pop();

		if (v->onStack == false)
			continue;

		vector<int> * currSCC = new vector<int>;

		stack<Vertex*> workingSCC;

		v->onStack = false;

		if (v->visited == false)
			DFS(V, workingSCC, v->number, true);

		while(!workingSCC.empty())
		{
			Vertex * vn = workingSCC.top();
			workingSCC.pop();

			vn->onStack = false;

			currSCC->push_back(vn->number);
		}

		masterVector.push_back(currSCC);
	}	

	return masterVector;
}

void Graph::DFS(Vertex *& V, stack<Vertex*>& S, int vertIndex, bool transpose)
{
	V[vertIndex].visited = true;
	V[vertIndex].index = 1; // grey

	for (int i = 0; i < states; i++)
		if ((!transpose && (adj[vertIndex][i] == true && V[i].visited == false)) || (transpose && (tadj[vertIndex][i] == true && V[i].visited == false)))
			DFS(V, S, i, transpose);

	V[vertIndex].index = 2;
	S.push(&V[vertIndex]);
	V[vertIndex].onStack = true;
}
