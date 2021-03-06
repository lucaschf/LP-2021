#ifndef MAQUINA_EXECUCAO_H
#define MAQUINA_EXECUCAO_H

#include "Programa.h"
#include "ErroExecucao.h"

#include<map>
#include<vector>


// N�mero m�ximo de vari�veis do programa.
constexpr unsigned short NUMERO_MAXIMO_DE_VARIAVEIS = 25;

// N�mero m�ximo de programas da m�quina de execu��o.
constexpr unsigned short NUMERO_MAXIMO_DE_PROGRAMAS = 5;

// Indica endere�o inv�lido na mem�ria da m�quina de execu��o.
constexpr unsigned short ENDERECO_INVALIDO = 100;

// Esta classe representa a estrutura da m�quina de execu��o de um programa LPAS.
class MaquinaExecucao {

public:

	// Inicia as vari�veis da m�quina de execu��o.
	MaquinaExecucao();

	/* Carrega um programa LPAS para a mem�ria. Retorna true se o programa foi carregado,
	caso contr�rio retorna false.*/
	bool carregar(Programa programa);

	// Obt�m o n�mero de programas LPAS carregados na mem�ria da m�quina de execu��o.
	int getNumeroDeProgramas();

	/* Pesquisa o nome do programa LPAS na mem�ria da m�quina de execu��o.
	Retorna o endere�o de mem�ria do programa ou ENDERECO_INVALIDO se o nome n�o for localizado.*/
	unsigned short pesquisarPrograma(string nome);

	/* Obt�m um programa LPAS armazenado na posi��o de mem�ria indicada por endereco.
	Se o endere�o de mem�ria for inv�lido, retorna um objeto com atributos nulos.*/
	Programa obterPrograma(unsigned short endereco);

	/* Executa o programa armazenado na posi��o de mem�ria indicada por endereco.
	Esta fun��o deve usar a fun��o obterCodigoInstrucao() para obter o c�digo de m�quina da instru��o LPAS a ser executada.
	Retorna um objeto que permite identificar a instru��o, o n�mero da linha,
	o nome do programa e o tipo de erro que pode ocorrer durante a execu��o de um programa LPAS.*/
	ErroExecucao executarPrograma(unsigned short endereco);

	/* Retorna um objeto que permite identificar a instru��o, o n�mero da linha, o nome do programa
	e o tipo de erro que pode ocorrer durante a execu��o de um programa LPAS.*/
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


	// N�mero de programas LPAS carregados na mem�ria da m�quina de execu��o.
	unsigned short numeroDeProgramas;

	int currentLine;

	// Armazena os programas LPAS na mem�ria da m�quina de execu��o.
	Programa memoria[NUMERO_MAXIMO_DE_PROGRAMAS];

	// Registrador da m�quina de execu��o LPAS.
	int registrador;

	// Vari�veis do programa LPAS que est� sendo executado na m�quina de execu��o.
	int variaveis[NUMERO_MAXIMO_DE_VARIAVEIS];

	/* Identifica a instru��o, o n�mero da linha, o nome do programa e o tipo de erro que pode
	ocorrer durante a execu��o de um programa LPAS.*/
	ErroExecucao erroExecucao;

	/* Converte a instru��o mnem�nica LPAS para o seu c�digo de m�quina equivalente. Ver Tabela 1.
	Retorna o c�digo de m�quina da instru��o LPAS.*/
	unsigned short obterCodigoInstrucao(string instrucao);

	/* Define a instru��o, o n�mero da linha, o nome do programa e o erro ocorrido na execu��o do programa.*/
	void definirErroExecucao(string nomePrograma, string instrucao, unsigned short linha, Erro erro);

	/* 
	Executa a instru��o LPAS usando o valor armazenado em argumento ou na posi��o de mem�ria indicada
	por enderecoVariavel. Retorna o c�digo da instru��o executada.*/
	unsigned short executarInstrucao(unsigned short codigoInstrucao, unsigned short enderecoVariavel, int argumento);

	vector<string> extractArgs(string instructionArgs);

	bool isAcceptedVariableName(string arg);

	rsize_t requiredArgs(Instruction instruction);

};
#endif