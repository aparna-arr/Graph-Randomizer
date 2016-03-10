#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<stack>
#include<vector>
#include<iterator>

typedef struct {
	int number;
	int index;
	bool onStack;
	bool visited;
} Vertex;

class Graph 
{
public:
	Graph(int stateNum, double edgeProbability);

	void generate(void);
	void dumpMatrix(void);
	void outputDot(void);

private:
	std::vector< std::vector <int> * > dijkstraAlg(void);
	void DFS(Vertex*& V, std::stack<Vertex*>& S, int vertIndex, bool transpose);

	void joinSCCs(std::vector< std::vector<int> * >& SCCs);

	// cool algorithm, not needed.
//	void uniqueRandom(int *& ptr, int maxSize, int numNumbers);

	int states;
	bool ** adj;
	bool ** tadj; // transposition of matrix
	double edgeProb;
};
#endif
