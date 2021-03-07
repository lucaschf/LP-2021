#include "Lpas.h"

#include "ArquivoTexto.h"
#include <iostream>
#include "Programa.h"
#include "Utils.h"
#include "Constants.h"


using namespace std;

int main() {

	setlocale(LC_ALL, "Portuguese");
	Lpas().run();
	return 0;
}

void Lpas::run()
{
	MaquinaExecucao me = MaquinaExecucao();

	string parameterizedInstruction = APP_NAME;

	string instruction;
	vector<string> args;

	do {
		if (!parameterizedInstruction.empty())
			cout << APP_NAME << "> ";

		getline(cin, parameterizedInstruction);
		if (Utils::trim(parameterizedInstruction).empty())
			continue;

		run(extractInstruction(parameterizedInstruction));
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
		showMessage(msg);
		return;
	}
}

void Lpas::show(const vector<string>& args)
{
	if (args.size() == 0) {
		showMessage(ABSENT_PARAMETER);
		return;
	}

	if (me.getNumeroDeProgramas() == 0)
	{
		showMessage(NO_PROGRAMS_IN_MEMORY);
		return;
	}

	if (args.size() == 1 && args[0] == "me") // display all stored
	{
		showMessage(THE_LPAS_PROGRAMS_IN_THE_EXECUTION_MACHINE_MEMORY_ARE);

		for (int i = 0; i < me.getNumeroDeProgramas(); i++)
		{
			auto message = LEFT_MARGIN + to_string(i + 1) + ": " + me.obterPrograma(i).getNome();
			showMessage(message, false);
		}

		cout << endl;

		return;
	}

	for (auto str : args) {
		auto pos = me.pesquisarPrograma(str);

		if (pos != ENDERECO_INVALIDO) {
			me.obterPrograma(pos).exibir();
			cout << endl;
		}
		else
			showMessage(PROGRAM + " '" + str + "' ." + NOT_LOADED);
	}
}

void Lpas::run(const vector<string>& args)
{
	if (args.size() == 0) {
		showMessage(ABSENT_PARAMETER);
		return;
	}

	for (auto str : args) {
		auto pos = me.pesquisarPrograma(str);

		if (pos != ENDERECO_INVALIDO) {
			me.executarPrograma(pos);
			cout << endl;
		}
		else
			showMessage(PROGRAM + " '" + str + "' ." + NOT_LOADED);
	}
}

void Lpas::load(const vector<string>& args)
{
	if (args.size() == 0) {
		showMessage(ABSENT_PARAMETER);
		return;
	}

	for (auto str : args) {
		Programa p;
		try {
			if (!p.carregar(str)) {
				showMessage(FILE_ + " '" + str + "' " + NOT_FOUND_OR_NOT_ACCEPTED);
				return;
			}

			if (!me.carregar(p)) {
				showMessage(THERE_IS_ALREADY_A_PROGRAM + " '" + p.getNome() + "'" + LOADED);
				return;
			}

			showMessage(PROGRAM + " '" + p.getNome() + "' " + SUCCESSFUL_LOADED);
		}
		catch (const char* msg) {
			showMessage(msg);
		}
	}
}

Instruction Lpas::extractInstruction(const string parameterizedInstruction)
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
		throw INVALID_OPERATION;

	return it->second;
}

void Lpas::showMessage(const string& message, bool breakEndLine)
{
	cout << endl << LEFT_MARGIN << message;

	if (breakEndLine)
		cout << endl;
}
