#ifndef USEROPTS_H
#define USEROPTS_H

#include<iostream>
#include<string>
#include<sstream>


class UserOpts
{
public:
	UserOpts(int argc, char *argv[]);

	void printUsage(void);
	int getStateNum(void);
	double getProb(void);

private:
	int states;
	double prob;
};

#endif
