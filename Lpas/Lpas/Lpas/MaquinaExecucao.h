#ifndef MAQUINA_EXECUCAO_H
#define MAQUINA_EXECUCAO_H

#include "Programa.h"
#include "ErroExecucao.h"

#include<map>
#include<vector>


// Número máximo de variáveis do programa.
constexpr unsigned short NUMERO_MAXIMO_DE_VARIAVEIS = 25;

// Número máximo de programas da máquina de execução.
constexpr unsigned short NUMERO_MAXIMO_DE_PROGRAMAS = 5;

// Indica endereço inválido na memória da máquina de execução.
constexpr unsigned short ENDERECO_INVALIDO = 100;

// Esta classe representa a estrutura da máquina de execução de um programa LPAS.
class MaquinaExecucao {

public:

	// Inicia as variáveis da máquina de execução.
	MaquinaExecucao();

	/* Carrega um programa LPAS para a memória. Retorna true se o programa foi carregado,
	caso contrário retorna false.*/
	bool carregar(Programa programa);

	// Obtém o número de programas LPAS carregados na memória da máquina de execução.
	int getNumeroDeProgramas();

	/* Pesquisa o nome do programa LPAS na memória da máquina de execução.
	Retorna o endereço de memória do programa ou ENDERECO_INVALIDO se o nome não for localizado.*/
	unsigned short pesquisarPrograma(string nome);

	/* Obtém um programa LPAS armazenado na posição de memória indicada por endereco.
	Se o endereço de memória for inválido, retorna um objeto com atributos nulos.*/
	Programa obterPrograma(unsigned short endereco);

	/* Executa o programa armazenado na posição de memória indicada por endereco.
	Esta função deve usar a função obterCodigoInstrucao() para obter o código de máquina da instrução LPAS a ser executada.
	Retorna um objeto que permite identificar a instrução, o número da linha,
	o nome do programa e o tipo de erro que pode ocorrer durante a execução de um programa LPAS.*/
	ErroExecucao executarPrograma(unsigned short endereco);

	/* Retorna um objeto que permite identificar a instrução, o número da linha, o nome do programa
	e o tipo de erro que pode ocorrer durante a execução de um programa LPAS.*/
	ErroExecucao getErroExecucao();

private:

	enum Instruction {
		READ = 10,
		WRITE = 11,
		MOV = 20,
		LOAD = 21,
		STORE = 22,
		ADD = 30,
		SUB = 31,
		MUL = 32,
		DIV = 33,
		RDIV = 34,
		JUMP = 40,
		JPNEG = 41,
		JPZERO = 42,
		HALT = 50
	};

	const map<string, unsigned short> instructionCodes = {
		{"READ", READ},
		{"WRITE", WRITE},
		{"MOV", MOV},
		{"LOAD", LOAD},
		{"STORE", STORE},
		{"ADD", ADD},
		{"SUB", SUB},
		{"MUL", MUL},
		{"DIV", DIV},
		{"RDIV", RDIV},
		{"JUMP", JUMP},
		{"JPNEG", JPNEG},
		{"JPZERO", JPZERO},
		{"HALT", HALT}
	};


	// Número de programas LPAS carregados na memória da máquina de execução.
	unsigned short numeroDeProgramas;

	int currentLine;

	// Armazena os programas LPAS na memória da máquina de execução.
	Programa memoria[NUMERO_MAXIMO_DE_PROGRAMAS];

	// Registrador da máquina de execução LPAS.
	int registrador;

	// Variáveis do programa LPAS que está sendo executado na máquina de execução.
	int variaveis[NUMERO_MAXIMO_DE_VARIAVEIS];

	/* Identifica a instrução, o número da linha, o nome do programa e o tipo de erro que pode
	ocorrer durante a execução de um programa LPAS.*/
	ErroExecucao erroExecucao;

	/* Converte a instrução mnemônica LPAS para o seu código de máquina equivalente. Ver Tabela 1.
	Retorna o código de máquina da instrução LPAS.*/
	unsigned short obterCodigoInstrucao(string instrucao);

	/* Define a instrução, o número da linha, o nome do programa e o erro ocorrido na execução do programa.*/
	void definirErroExecucao(string nomePrograma, string instrucao, unsigned short linha, Erro erro);

	/* 
	Executa a instrução LPAS usando o valor armazenado em argumento ou na posição de memória indicada
	por enderecoVariavel. Retorna o código da instrução executada.*/
	unsigned short executarInstrucao(unsigned short codigoInstrucao, unsigned short enderecoVariavel, int argumento);

	vector<string> extractArgs(string instructionArgs);

	bool isAcceptedVariableName(string arg);

	rsize_t requiredArgs(Instruction instruction);

};
#endif