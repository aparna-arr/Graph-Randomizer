#include"UserOpts.h"
using namespace std;

UserOpts::UserOpts(int argc, char * argv[])
{
	if (argc < 2)
		printUsage();

	int stateNum;

	stringstream input;
	input << argv[1];

	if (!(input >> stateNum))
	{
		printUsage();
		throw 1;
	}

	states = stateNum;

	input.str("");
	input.clear();

	if (argc == 2)
		prob = 0.5;
	else
	{
	        input << argv[2];
		input >> prob;

// no idea why this doesn't work but the above does		
//		if (!(input >> prob))
//			prob = 0.5;
	}
}

void UserOpts::printUsage(void)
{
	cout << "usage: graphmaker <INT: number of states>" << endl;
	throw 1;
}

int UserOpts::getStateNum(void)
{
	return states;
}

double UserOpts::getProb(void)
{
	return prob;
}
