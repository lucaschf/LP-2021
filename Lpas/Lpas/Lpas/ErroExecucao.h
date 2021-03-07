#ifndef ERRO_EXECUCAO_H
#define ERRO_EXECUCAO_H

#include <string>

using namespace std;

/* Códigos resultantes da execução do programa LPAS. Os códigos válidos são:
0 = execução bem sucedida;
1 = instrução LPAS inválida;
2 = argumento de instrução LPAS inválido;
3 = argumento de instrução LPAS ausente;
4 = duas ou mais instruções LPAS na mesma linha de código;
5 = símbolo inválido.
*/
enum class Erro {
	EXECUCAO_BEM_SUCEDIDA,
	INSTRUCAO_LPAS_INVALIDA,
	ARGUMENTO_INSTRUCAO_LPAS_INVALIDO,
	ARGUMENTO_INSTRUCAO_LPAS_AUSENTE,
	MUITAS_INSTRUCOES,
	SIMBOLO_INVALIDO
};

/*
Esta classe representa a instrução, o número da linha, o nome do programa e o tipo de erro
que pode ocorrer durante a execução de um programa LPAS.
*/
class ErroExecucao {

public:

	ErroExecucao();

	ErroExecucao(string instrucao, string nomePrograma, unsigned short numeroLinha, Erro erro);

	string getInstrucao();

	string getNomePrograma();

	unsigned short getNumeroLinha();

	Erro getErro();

	void setInstrucao(string instrucao);

	void setNomePrograma(string nomePrograma);

	void setNumeroLinha(unsigned short numeroLinha);

	void setErro(Erro erro);

	string getErrorMessage();

private:

	string instrucao;

	string nomePrograma;

	unsigned short numeroLinha = 0;

	Erro erro;
};
#endif