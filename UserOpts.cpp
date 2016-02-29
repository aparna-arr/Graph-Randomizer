#include"UserOpts.h"
using namespace std;

UserOpts::UserOpts(int argc, char * argv[])
{
	if (argc != 2)
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
