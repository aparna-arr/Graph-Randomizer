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

private:
	int states;
};

#endif
