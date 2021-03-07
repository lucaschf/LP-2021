#include "ErroExecucao.h"

ErroExecucao::ErroExecucao()
{
	setErro(Erro::EXECUCAO_BEM_SUCEDIDA);
	setInstrucao("");
	setNomePrograma("");
	setNumeroLinha(0);
}

ErroExecucao::ErroExecucao(string instrucao, string nomePrograma, unsigned short numeroLinha, Erro erro)
{
	setInstrucao(instrucao);
	setNomePrograma(nomePrograma);
	setNumeroLinha(numeroLinha);
	setErro(erro);
}

string ErroExecucao::getInstrucao()
{
	return this->instrucao;
}

string ErroExecucao::getNomePrograma()
{
	return this->nomePrograma;
}

unsigned short ErroExecucao::getNumeroLinha()
{
	return this->numeroLinha;
}

Erro ErroExecucao::getErro()
{
	return this->erro;
}

void ErroExecucao::setInstrucao(string instrucao)
{
	this->instrucao = instrucao;
}

void ErroExecucao::setNomePrograma(string nomePrograma)
{
	this->nomePrograma = nomePrograma;
}

void ErroExecucao::setNumeroLinha(unsigned short numeroLinha)
{
	this->numeroLinha = numeroLinha;
}

void ErroExecucao::setErro(Erro erro)
{
	this->erro = erro;
}

string ErroExecucao::getErrorMessage() {

	string message = "Erro na linha " + to_string(getNumeroLinha()) + ": " + getInstrucao() + "\n";

	switch (getErro())
	{
	case Erro::EXECUCAO_BEM_SUCEDIDA:
		message = "Execucao bem sucedida";
		break;
	case Erro::ARGUMENTO_INSTRUCAO_LPAS_AUSENTE:
		message += "Argumento ausente";
		break;
	case Erro::ARGUMENTO_INSTRUCAO_LPAS_INVALIDO:
		message += "Argumento inválido";
		break;
	case Erro::INSTRUCAO_LPAS_INVALIDA:
		message += "Instrução inválida";
		break;
	case Erro::MUITAS_INSTRUCOES:
		message += "Muitas instruçoes em uma unica linha";
		break;
	case Erro::SIMBOLO_INVALIDO:
		message += "Simbolo inválido";
		break;
	default:
		break;
	}

	return message;
}
