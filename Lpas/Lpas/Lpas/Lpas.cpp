#include "Lpas.h"

#include <iostream>

#include "ArquivoTexto.h"
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

	string parameterizedOperation = APP_NAME;

	do {
		if (!parameterizedOperation.empty())
			cout << APP_NAME << "> ";

		getline(cin, parameterizedOperation);
		if (Utils::trim(parameterizedOperation).empty())
			continue;

		run(extractOperation(parameterizedOperation));
	} while (parameterizedOperation.compare("exit") != 0);
}

void Lpas::run(Operation instruction)
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
	catch (string msg) {
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
			auto message = WHITE_SPACES + to_string(i + 1) + ": " + me.obterPrograma(i).getNome();
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
			try {
				showMessage(me.executarPrograma(pos).getErrorMessage());
			}
			catch (string msg) {
				showMessage(msg);
			}
		}
		else
			showMessage(PROGRAM + " '" + str + "' " + NOT_LOADED);
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
				showMessage(THERE_IS_ALREADY_A_PROGRAM + " '" + p.getNome() + "' " + LOADED);
				return;
			}

			showMessage(PROGRAM + " '" + p.getNome() + "' " + SUCCESSFUL_LOADED);
		}
		catch (string msg) {
			showMessage(msg);
		}
	}
}

Operation Lpas::extractOperation(const string parameterizedOperation)
{
	Operation operation;

	int argsBegin = parameterizedOperation.find(" ");

	operation.setName(parameterizedOperation.substr(0, argsBegin));

	if (argsBegin != string::npos)
	{
		char delimiter = ' ';
		auto args = parameterizedOperation.substr(argsBegin + 1);
		if (Utils::contains(args, "\""))
			delimiter = '"';

		operation.addArgs(Utils::tokenize(args, delimiter, delimiter == ' '));
	}

	return operation;
}

LpasOperation Lpas::getOperationCode(Operation operation) {
	auto it = operationsMapping.find(operation.getName());

	if (it == operationsMapping.end())
		throw INVALID_OPERATION;

	return it->second;
}

void Lpas::showMessage(const string& message, bool breakEndLine)
{
	cout << endl << WHITE_SPACES << message;

	if (breakEndLine)
		cout << endl << endl;
}
