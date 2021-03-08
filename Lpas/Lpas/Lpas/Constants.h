#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

const string APP_NAME = "lpas";
const string LPAS_EXTENSION = ".lpas";

const string WHITE_SPACES = "      ";
const string ABSENT_PARAMETER = "Parametro ausente.";
const string NO_PROGRAMS_IN_MEMORY = "Nenhum programa em memória.";
const string THE_LPAS_PROGRAMS_IN_THE_EXECUTION_MACHINE_MEMORY_ARE = "Os programas LPAS na memória da máquina de execução são:";
const string THERE_IS_ALREADY_A_PROGRAM = "Já existe um programa";
const string LOADED = "carregado";
const string INVALID_OPERATION = "Operação inválida";
const string NOT_FOUND_OR_NOT_ACCEPTED = "não encontrado ou não é um arquivo aceito.";
const string PROGRAM_NAME = "Nome do programa: ";
const string FAILED_TO_LOAD_PROGRAM = "Falha ao carregar programa";
const string FILE_ = "Arquivo";
const string FAILED_TO_OPEN_FILE = "Falha ao abrir o arquivo";
const string PROGRAM = "Programa";
const string SUCCESSFUL_LOADED = "carregado com sucesso.";
const string NOT_LOADED = "não carregado.";
const string MACHINE_MEMORY_FULL = "Memória da maquina de execução cheia.\n" + WHITE_SPACES 
	+ "Use o comando 'replace [NOME_PROGRAMA_EM_MEMORIA] [CAMINHO_NOVO_PROGRAMA]' para substituir um programa em memória.";
const string NO_INSTRUCTIONS = "Nenhuma instrução.";
const string UP_AND_RUNNING = "carregado e executando...";
const string VALUE = "valor";


#endif // !CONSTANTS_H