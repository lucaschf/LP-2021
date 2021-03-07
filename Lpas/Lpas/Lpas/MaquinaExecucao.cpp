#include "MaquinaExecucao.h"

#include <iostream>
#include <sstream>

#include <algorithm>
#include <string>

#include "Utils.h"


MaquinaExecucao::MaquinaExecucao()
{
	numeroDeProgramas = 0;
	registrador = 0;
}

bool MaquinaExecucao::carregar(Programa programa)
{
	if ((numeroDeProgramas >= NUMERO_MAXIMO_DE_PROGRAMAS - 1))
		throw("Mem�ria da maquina de execu��o cheia\n");

	if(pesquisarPrograma(programa.getNome()) != ENDERECO_INVALIDO)
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
		if (memoria[i].getNome().compare(nome) == 0)
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
	const int maxArgsKnown = 2;

	registrador = 0;
	map<string, int> variables;
	unsigned short quantidadeVariaveis = 0;

	Programa programa = obterPrograma(endereco);

	if (programa.getNumeroDeInstrucoes() == 0)
	{
		cout << "No instructions" << endl;
		return ErroExecucao();
	}

	currentLine = 0;

	cout << "Program " << programa.getNome() << " running....." << endl;

	while (currentLine < programa.getNumeroDeInstrucoes() - 1) {
		string parameterizedInstruction = programa.obterInstrucao(currentLine);

		auto error = ErroExecucao(parameterizedInstruction, programa.getNome(),
			currentLine, Erro::INSTRUCAO_LPAS_INVALIDA);

		if (Utils::startsWith(Utils::trim(parameterizedInstruction), ";")) { // is a comment line, nothing to do
			currentLine++;
			continue;
		}

		int instructionBegin = parameterizedInstruction.find(" ");

		Instruction instruction = static_cast<Instruction>(
			obterCodigoInstrucao(parameterizedInstruction.substr(0, instructionBegin)));

		if (instruction == HALT)
			break;

		if (instructionBegin != string::npos) {
			auto args = extractArgs(parameterizedInstruction.substr(instructionBegin + 1));

			auto expectedArgs = requiredArgs(instruction);

			if (args.size() != expectedArgs || args.size() > maxArgsKnown) {
				error.setErro(args.size() > expectedArgs ? Erro::MUITAS_INSTRUCOES : Erro::ARGUMENTO_INSTRUCAO_LPAS_AUSENTE);
				return error;
			}

			unsigned short address = ENDERECO_INVALIDO;
			int arg = 0;

			for (string strArg : args) {
				strArg = Utils::trim(strArg);

				if (isAcceptedVariableName(strArg)) // arg is a variable
				{
					auto it = variables.find(strArg);
					if (it == variables.end())
					{
						if (variables.size() == NUMERO_MAXIMO_DE_VARIAVEIS)
						{
							error.setErro(Erro::MUITAS_INSTRUCOES);
							return error;
						}

						variables.insert(make_pair(strArg, quantidadeVariaveis));
						variaveis[quantidadeVariaveis] = 0;
						if (address == ENDERECO_INVALIDO)
							address = quantidadeVariaveis;
						else
							arg = quantidadeVariaveis;

						quantidadeVariaveis++;
					}
					else {
						if (address == ENDERECO_INVALIDO)
							address = it->second;
						else
							arg = variaveis[it->second];
					}
				}
				else { // arg is a literal
					try {
						arg = stoi(strArg);
					}
					catch (...) {
						error.setErro(Erro::ARGUMENTO_INSTRUCAO_LPAS_INVALIDO);
						return error;
					}
				}
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
		}
	}

	return ErroExecucao();
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

unsigned short MaquinaExecucao::executarInstrucao(unsigned short codigoInstrucao, unsigned short enderecoVariavel, int argumento)
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
		cout << "value: ";
		cin >> variaveis[enderecoVariavel];
		break;
	case WRITE:
		cout << variaveis[enderecoVariavel] << endl;
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
	return !Utils::isInteger(arg);
}

size_t MaquinaExecucao::requiredArgs(Instruction instruction)
{
	return instruction == Instruction::MOV ? 2 : 1;
}

