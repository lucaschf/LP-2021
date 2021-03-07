#include "Instruction.h"

Instruction::Instruction()
{
    args = vector<string>();
    setName("");
}

string Instruction::getName()
{
    return this->name;
}

void Instruction::setName(string name)
{
    this->name = name;
}

const vector<string> Instruction::getArgs()
{
    return args;
}

void Instruction::addArgs(vector<string> args)
{
    for (auto arg : args)
        addArg(arg);
}

void Instruction::addArg(string arg)
{
    args.emplace_back(arg);
}
