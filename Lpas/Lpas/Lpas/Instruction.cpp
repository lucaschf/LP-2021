#include "Instruction.h"

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

void Instruction::addArg(string arg)
{
    args.emplace_back(arg);
}
