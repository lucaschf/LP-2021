#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>

using namespace std;


class Operation
{
private:

	string name;
	vector<string> args;

public:
	
	Operation();

	string getName();

	void setName(string name);

	const vector<string> getArgs();

	void addArgs(vector<string> args);

	void addArg(string arg);
};

#endif // ! INSTRUCTION_H

