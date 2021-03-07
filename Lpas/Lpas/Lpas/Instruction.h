#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <vector>
#include <string>

using namespace std;


class Instruction
{
private:

	string name;
	vector<string> args;

public:
	
	Instruction();

	string getName();

	void setName(string name);

	const vector<string> getArgs();

	void addArgs(vector<string> args);

	void addArg(string arg);
};

#endif // ! INSTRUCTION_H

