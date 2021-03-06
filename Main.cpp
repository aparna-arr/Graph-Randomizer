#include"Main.h"
#include"UserOpts.h"
#include"Graph.h"

using namespace std;

int main (int argc, char * argv[]) 
{
	try{
		UserOpts inputObj(argc, argv);
		cout << "Your number of states is: " << inputObj.getStateNum() << endl;
		cout << "Your prob is: " << inputObj.getProb() << endl;
		Graph randGraph(inputObj.getStateNum(), inputObj.getProb());

		randGraph.generate();
//		randGraph.dumpMatrix();
		randGraph.outputDot();
	}
	catch (int e)
	{
		if (e == 1)
		{
			cout << "Exiting!" << endl;
			return 1;
		}
	}
}
