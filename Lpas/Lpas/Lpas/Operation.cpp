#include "Operation.h"

Operation::Operation()
{
	args = vector<string>();
	setName("");
}

string Operation::getName()
{
	return this->name;
}

void Operation::setName(string name)
{
	this->name = name;
}

const vector<string> Operation::getArgs()
{
	return args;
}

void Operation::addArgs(vector<string> args)
{
	for (auto arg : args)
		addArg(arg);
}

void Operation::addArg(string arg)
{
	args.emplace_back(arg);
}
