#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>

class Graph 
{
public:
	Graph(int stateNum, double edgeProbability = 0.5);

	void generate(void);
	void dumpMatrix(void);
	void outputDot(void);

private:
	bool isConnected(void);
	
	int states;
	bool ** adj;
	double edgeProb;
};
#endif