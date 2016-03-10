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
	Graph(int stateNum, double edgeProbability = 0.5);

	void generate(void);
	void dumpMatrix(void);
	void outputDot(void);

private:
	std::vector< std::vector <int> * > dijkstraAlg(void);
	void DFS(Vertex*& V, std::stack<Vertex*>& S, int vertIndex, bool transpose);

	int states;
	bool ** adj;
	bool ** tadj; // transposition of matrix
	double edgeProb;
};
#endif
