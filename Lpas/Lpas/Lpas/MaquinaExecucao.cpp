#include "MaquinaExecucao.h"

#include <iostream>
#include <sstream>

#include <algorithm>
#include <string>

#include "Utils.h"
#include "Constants.h"


MaquinaExecucao::MaquinaExecucao()
{
	numeroDeProgramas = 0;
	registrador = 0;
}

bool MaquinaExecucao::carregar(Programa programa)
{
	if ((numeroDeProgramas >= NUMERO_MAXIMO_DE_PROGRAMAS))
		throw(MACHINE_MEMORY_FULL);

	if (pesquisarPrograma(programa.getNome()) != ENDERECO_INVALIDO)
		return false;

	memoria[numeroDeProgramas++] = programa;
	return true;
}

int MaquinaExecucao::getNumeroDeProgramas()
{
	return numeroDeProgramas;
}

unsigned short MaquinaExecucao::pesquisarPrograma(string nome)
{
	for (unsigned short i = 0; i < numeroDeProgramas; i++) {
		if (memoria[i].getNome().compare(nome) == 0 || memoria[i].getNome().compare(nome + LPAS_EXTENSION) == 0)
			return i;
	}

	return ENDERECO_INVALIDO;
}

Programa MaquinaExecucao::obterPrograma(unsigned short endereco)
{
	if (endereco < numeroDeProgramas)
		return memoria[endereco];

	return Programa();
}

ErroExecucao MaquinaExecucao::executarPrograma(unsigned short endereco)
{
	variablesMapping.clear();
	allocatedVariables = 0;

	Programa programa = obterPrograma(endereco);

	cout << endl << WHITE_SPACES << PROGRAM << " '" << programa.getNome() << "' " << UP_AND_RUNNING << endl << endl;

	if (programa.getNumeroDeInstrucoes() == 0) // nothing to do
	{
		cout << NO_INSTRUCTIONS << endl;
		return ErroExecucao();
	}

	registrador = 0; // resets the recorder
	currentLine = 0; // back to the first line of the program

	while (currentLine < programa.getNumeroDeInstrucoes()) {
		try {
			string parameterizedInstruction = programa.obterInstrucao(currentLine);

			auto error = ErroExecucao(parameterizedInstruction, programa.getNome(),
				currentLine, Erro::INSTRUCAO_LPAS_INVALIDA);

			// check if is a comment line meaning that is nothing to do
			if (Utils::startsWith(Utils::trim(parameterizedInstruction), ";")) {
				currentLine++;
				continue;
			}

			int argsBegin = parameterizedInstruction.find_first_of(" ");

			if (!Utils::contains(parameterizedInstruction, " ")) // pottentialy a non parameterized instruction
				argsBegin = parameterizedInstruction.find_first_of(";");

			auto instruction = static_cast<Instruction>(
				obterCodigoInstrucao(parameterizedInstruction.substr(0, argsBegin)));

			if (instruction == HALT) {
				error.setErro(Erro::EXECUCAO_BEM_SUCEDIDA);
				return error;
			}

			if (argsBegin != string::npos) { // args passed
				unsigned short address = ENDERECO_INVALIDO;
				int arg = 0;

				auto err = retriveVariableAndLiteralFromArgs(
					instruction,
					extractArgs(parameterizedInstruction.substr(argsBegin + 1)),
					address,
					arg
				);

				if (err != Erro::EXECUCAO_BEM_SUCEDIDA)
				{
					error.setErro(err);
					return error;
				}

				if (executarInstrucao(instruction, address, arg) == USHRT_MAX)
				{
					error.setErro(Erro::INSTRUCAO_LPAS_INVALIDA);
					return error;
				}
			}
			else // no argument given
			{
				error.setErro(Erro::ARGUMENTO_INSTRUCAO_LPAS_AUSENTE);
				return error;
			}
		}
		catch (...) {
			throw "Failed to execute instruction at line: " + currentLine;
		}
	}

	return ErroExecucao();
}

Erro MaquinaExecucao::retriveVariableAndLiteralFromArgs(Instruction instruction, vector<string> args,
	unsigned short& address, int& param)
{
	// number of maximum known arguments for an instruction in this case MOV has the greatest number of args (2)
	const int maxArgsKnown = 2;

	auto expectedArgs = requiredArgs(instruction);

	if (args.size() != expectedArgs || args.size() > maxArgsKnown) {
		return (args.size() > expectedArgs ? Erro::MUITAS_INSTRUCOES : Erro::ARGUMENTO_INSTRUCAO_LPAS_AUSENTE);
	}

	for (string strArg : args) {
		strArg = Utils::trim(strArg);

		if (isAcceptedVariableName(strArg)) // arg is a variable
		{
			auto it = variablesMapping.find(strArg);
			if (it == variablesMapping.end())
			{
				if (variablesMapping.size() == NUMERO_MAXIMO_DE_VARIAVEIS)
				{
					return Erro::MUITAS_INSTRUCOES;
				}

				variablesMapping.insert(make_pair(strArg, allocatedVariables));
				variaveis[allocatedVariables] = 0;
				if (address == ENDERECO_INVALIDO)
					address = allocatedVariables;
				else
					param = allocatedVariables;

				allocatedVariables++;
			}
			else {
				if (address == ENDERECO_INVALIDO)
					address = it->second;
				else
					param = variaveis[it->second];
			}
		}
		else { // arg is a literal
			try {
				param = stoi(strArg);
			}
			catch (...) {
				return Erro::ARGUMENTO_INSTRUCAO_LPAS_INVALIDO;
			}
		}
	}

	return Erro::EXECUCAO_BEM_SUCEDIDA;
}

ErroExecucao MaquinaExecucao::getErroExecucao()
{
	return erroExecucao;
}

unsigned short MaquinaExecucao::obterCodigoInstrucao(string instrucao)
{
	auto it = instructionCodes.find(instrucao);

	if (it == instructionCodes.end())
		return USHRT_MAX;

	return it->second;
}

void MaquinaExecucao::definirErroExecucao(string nomePrograma, string instrucao, unsigned short linha, Erro erro)
{
	erroExecucao = ErroExecucao(instrucao, nomePrograma, linha, erro);
}

unsigned short MaquinaExecucao::executarInstrucao(unsigned short codigoInstrucao,
	unsigned short enderecoVariavel, int argumento)
{
	currentLine++;

	switch (codigoInstrucao)
	{
	case JUMP:
		currentLine = argumento;
		break;
	case JPNEG:
		if (registrador < 0)
			currentLine = argumento;
		break;
	case JPZERO:
		if (registrador == 0)
			currentLine = argumento;
		break;
	case READ:
		cout << WHITE_SPACES << VALUE << ": ";
		cin >> variaveis[enderecoVariavel];
		break;
	case WRITE:
		cout << WHITE_SPACES << variaveis[enderecoVariavel] << endl;
		break;
	case MOV:
		variaveis[enderecoVariavel] = argumento;
		break;
	case LOAD:
		registrador = variaveis[enderecoVariavel];
		break;
	case STORE:
		variaveis[enderecoVariavel] = registrador;
		break;
	case ADD:
		registrador += (enderecoVariavel != ENDERECO_INVALIDO ? variaveis[enderecoVariavel] : argumento);
		break;
	case SUB:
		registrador -= (enderecoVariavel != ENDERECO_INVALIDO ? variaveis[enderecoVariavel] : argumento);
		break;
	case MUL:
		registrador *= (enderecoVariavel != ENDERECO_INVALIDO ? variaveis[enderecoVariavel] : argumento);
		break;
	case DIV:
		registrador /= (enderecoVariavel != ENDERECO_INVALIDO ? variaveis[enderecoVariavel] : argumento);
		break;
	case RDIV:
		registrador = registrador % (enderecoVariavel != ENDERECO_INVALIDO ? variaveis[enderecoVariavel] : argumento);
		break;
	case HALT:
		break;
	default:
		return USHRT_MAX;
	}

	return codigoInstrucao;
}

vector<string> MaquinaExecucao::extractArgs(string instructionArgs)
{
	vector<string> splitted;

	auto noComments = instructionArgs.substr(0, instructionArgs.find_first_of(";"));

	return Utils::tokenize(noComments, ',', true);
}

bool MaquinaExecucao::isAcceptedVariableName(string arg)
{
	return !Utils::isInteger(arg) && Utils::isUppercase(arg);
}

size_t MaquinaExecucao::requiredArgs(Instruction instruction)
{
	return instruction == Instruction::MOV ? 2 : 1;
}