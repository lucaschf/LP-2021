#ifndef PROGRAMA_H
#define PROGRAMA_H

#include <string>

using namespace std;

// Número máximo de instruções do programa.
constexpr unsigned short NUMERO_MAXIMO_DE_INSTRUCOES = 100;

// Esta classe representa a estrutura de um programa LPAS. 
class Programa {

public:

	// Inicia as variáveis do programa com valores default.
	Programa();

	// Inicia o programa com o nome especificado.
	Programa(string nome);

	/*
	Lê as instruções de um programa LPAS para a memória.
	Retorna true se as instruções foram lidas com sucesso e false se ocorreu algum erro durante a leitura.
	*/
	bool carregar();

	/*
	Lê as instruções de um programa LPAS armazenadas em um arquivo para a memória.
	Retorna true se as instruções foram lidas com sucesso e false se ocorreu algum erro durante a leitura.
	*/
	bool carregar(string filePath);

	// Obtém o número de instruções do programa LPAS.
	unsigned short getNumeroDeInstrucoes();

	/* Obtém uma instrução LPAS armazenada na posição de memória indicada por endereco.
	Se o endereço de memória for inválido, retorna uma string nula.*/
	string obterInstrucao(unsigned short endereco);

	/* Altera uma instrução armazenada na posição de memória indicada por endereco por uma nova instrucao.
		Retorna true se a instrução foi alterada. Se o endereço de memória for inválido, retorna false.
	*/
	bool alterarInstrucao(string instrucao, unsigned short endereco);

	// Exibe na tela as instruções do programa.
	void exibir();

	void setNome(string nome);

	string getNome();

private:

	// Número de instruções do programa.
	unsigned short numeroDeInstrucoes;

	// Nome do programa.
	string nome;

	/* Memória que armazena as instruções LPAS que compõem o programa.
	Cada linha do programa é armazenada em uma posição do vetor.*/
	string instrucoes[NUMERO_MAXIMO_DE_INSTRUCOES];

	/*
	* Adiciona uma nova instrução ao programa.
	*/
	bool addInstrucao(string instrucao);
};
#endif