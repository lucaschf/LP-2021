#include "Lpas.h"

#include "ArquivoTexto.h"
#include <iostream>
#include "Programa.h"
#include "Utils.h"


using namespace std;

int main() {

	setlocale(LC_ALL, "Portuguese");
	Lpas().run();
	return 0;
}

void Lpas::run()
{
	MaquinaExecucao me = MaquinaExecucao();

	string parameterizedInstruction;

	string instruction;
	vector<string> args;

	do {
		cout << "lpas> ";
		getline(cin, parameterizedInstruction);
		run(splitInstruction(parameterizedInstruction));
	} while (parameterizedInstruction.compare("exit") != 0);
}

void Lpas::run(Instruction instruction)
{
	LpasOperation operation;

	try {
		operation = getOperationCode(instruction);
		switch (operation)
		{
		case LpasOperation::LOAD:
			load(instruction.getArgs());
			break;
		case LpasOperation::RUN:
			run(instruction.getArgs());
			break;
		case LpasOperation::SHOW:
			show(instruction.getArgs());
			break;
		default:
			break;
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return;
	}


}

void Lpas::show(const vector<string>& args)
{
	if (args.size() == 0) {
		cout << "Parametro ausente \n";
		return;
	}

	if (me.getNumeroDeProgramas() == 0)
	{
		cout << "Nenhum programa em memória" << endl;
		return;
	}

	if (args.size() == 1 && args[0] == "me") // display all stored
	{
		for (int i = 0; i < me.getNumeroDeProgramas(); i++)
		{
			me.obterPrograma(i).exibir();
			cout << endl;
		}

		return;
	}

	for (auto str : args) {
		auto pos = me.pesquisarPrograma(str);
		if (pos == ENDERECO_INVALIDO)
			pos = me.pesquisarPrograma(str + ".lpas");

		if (pos != ENDERECO_INVALIDO) {
			me.obterPrograma(pos).exibir();
			cout << endl;
		}
		else
			cout << "Program - " << str << " not loaded.\n";
	}
}

void Lpas::run(const vector<string>& args)
{
	if (args.size() == 0) {
		cout << "Parametro ausente \n";
		return;
	}

	for (auto str : args) {
		auto pos = me.pesquisarPrograma(str);

		if (pos == ENDERECO_INVALIDO)
			pos = me.pesquisarPrograma(str + ".lpas");

		if (pos != ENDERECO_INVALIDO) {
			me.executarPrograma(pos);
			cout << endl;
		}
		else
			cout << "Program - " << str << " not loaded.\n";
	}
}

void Lpas::load(const vector<string>& args)
{
	if (args.size() == 0) {
		cout << "Parametro ausente \n";
		return;
	}

	for (auto str : args) {
		Programa p;
		try {
			p.carregar(str);
			if (me.carregar(p)) {
				cout << "Programa " << p.getNome() << "carregado com sucesso!" << endl;
			}
			else
				cout << "Já existe um programa com este nome em memória" << endl;
		}
		catch (const char* msg) {
			cerr << msg << endl;
		}
	}
}

Instruction Lpas::splitInstruction(const string parameterizedInstruction)
{
	Instruction instruction;

	int argsBegin = parameterizedInstruction.find(" ");

	instruction.setName(parameterizedInstruction.substr(0, argsBegin));

	if (argsBegin != string::npos)
		instruction.addArgs(Utils::tokenize(parameterizedInstruction.substr(argsBegin + 1), ' ', true));

	return instruction;
}

LpasOperation Lpas::getOperationCode(Instruction instruction) {
	auto it = operations.find(instruction.getName());

	if (it == operations.end())
		throw "Ivalid operation";

	return it->second;
}
