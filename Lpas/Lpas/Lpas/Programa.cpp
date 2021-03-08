#include "Programa.h"

#include <iostream>
#include <iomanip>
#include "ArquivoTexto.h"
#include "Utils.h"
#include "Constants.h"

Programa::Programa()
{
	setNome("");
	numeroDeInstrucoes = 0;
}

Programa::Programa(string nome)
{
	setNome(nome);
	numeroDeInstrucoes = 0;
}

bool Programa::carregar()
{
	string instruction;
	numeroDeInstrucoes = 0;

	do {
		fflush(stdin);
		cout << WHITE_SPACES << setfill('0') << setw(2) << numeroDeInstrucoes << " ";

		getline(cin, instruction);
		fflush(stdin);

		if (!instruction.empty())
			instrucoes[numeroDeInstrucoes++] = instruction;

	} while (instruction.compare("HALT") != 0 && numeroDeInstrucoes < NUMERO_MAXIMO_DE_INSTRUCOES);

	return numeroDeInstrucoes > 0;
}

bool Programa::carregar(string filePath)
{
	ArquivoTexto file;
	bool success = true;

	auto fullPath = Utils::addExtensionAsNeeded(filePath, "lpas");

	if (!file.abrir(fullPath, TipoDeAcesso::LEITURA))
		throw FAILED_TO_OPEN_FILE + " '" + filePath + "'";

	auto name = Utils::getFileName(fullPath, false);
	setNome(Utils::trim(name));

	for (auto str : file.readAllLines()) {
		int instructionStart = str.find(" ");
		
		auto instruction = str.substr(0, instructionStart);

		if (Utils::isInteger(instruction)) // has line counter
			instruction = str.substr(instructionStart + 1);
		else
			instruction = Utils::trim(str);

		if (!instruction.empty())
			if (!addInstrucao(instruction)) {
				success = false;
				break;
			}
	}

	file.fechar();
	return success;
}

unsigned short Programa::getNumeroDeInstrucoes()\
{
	return numeroDeInstrucoes;
}

string Programa::obterInstrucao(unsigned short endereco)
{
	if (endereco < numeroDeInstrucoes)
		return instrucoes[endereco];

	return NULL;
}

bool Programa::alterarInstrucao(string instrucao, unsigned short endereco)
{
	if (endereco >= numeroDeInstrucoes)
		return false;

	instrucoes[endereco] = instrucao;
	return true;
}

bool Programa::addInstrucao(string instrucao)
{
	if (numeroDeInstrucoes == NUMERO_MAXIMO_DE_INSTRUCOES)
		return false;

	instrucoes[numeroDeInstrucoes++] = instrucao;
	return true;
}

void Programa::exibir()
{
	cout << endl << WHITE_SPACES << "Programa - " << getNome() << endl << endl;

	for (int i = 0; i < numeroDeInstrucoes; i++)
		cout << WHITE_SPACES << setfill('0') << setw(2) << i << " " << instrucoes[i] << endl;
}

void Programa::setNome(string nome)
{
	this->nome = nome;
}

string Programa::getNome()
{
	return this->nome;
}
