#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <string>

using namespace std;

// N�mero m�ximo de instru��es do programa.
constexpr unsigned short NUMERO_MAXIMO_DE_INSTRUCOES = 100;

// Esta classe representa a estrutura de um programa LPAS. 
class Programa {

public:

	// Inicia as vari�veis do programa com valores default.
	Programa();

	// Inicia o programa com o nome especificado.
	Programa(string nome);

	/*
	L� as instru��es de um programa LPAS para a mem�ria.
	Retorna true se as instru��es foram lidas com sucesso e false se ocorreu algum erro durante a leitura.
	*/
	bool carregar();

	/*
	L� as instru��es de um programa LPAS armazenadas em um arquivo para a mem�ria.
	Retorna true se as instru��es foram lidas com sucesso e false se ocorreu algum erro durante a leitura.
	*/
	bool carregar(string filePath);

	// Obt�m o n�mero de instru��es do programa LPAS.
	unsigned short getNumeroDeInstrucoes();

	/* Obt�m uma instru��o LPAS armazenada na posi��o de mem�ria indicada por endereco.
	Se o endere�o de mem�ria for inv�lido, retorna uma string nula.*/
	string obterInstrucao(unsigned short endereco);

	/* Altera uma instru��o armazenada na posi��o de mem�ria indicada por endereco por uma nova instrucao.
		Retorna true se a instru��o foi alterada. Se o endere�o de mem�ria for inv�lido, retorna false.
	*/
	bool alterarInstrucao(string instrucao, unsigned short endereco);

	// Exibe na tela as instru��es do programa.
	void exibir();

	void setNome(string nome);

	string getNome();

private:

	// N�mero de instru��es do programa.
	unsigned short numeroDeInstrucoes;

	// Nome do programa.
	string nome;

	/* Mem�ria que armazena as instru��es LPAS que comp�em o programa.
	Cada linha do programa � armazenada em uma posi��o do vetor.*/
	string instrucoes[NUMERO_MAXIMO_DE_INSTRUCOES];

	/*
	* Adiciona uma nova instru��o ao programa.
	*/
	bool addInstrucao(string instrucao);
};
#endif