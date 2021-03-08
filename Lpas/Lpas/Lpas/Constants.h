#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

using namespace std;

const string APP_NAME = "lpas";
const string LPAS_EXTENSION = ".lpas";

const string WHITE_SPACES = "      ";
const string ABSENT_PARAMETER = "Parametro ausente.";
const string NO_PROGRAMS_IN_MEMORY = "Nenhum programa em mem�ria.";
const string THE_LPAS_PROGRAMS_IN_THE_EXECUTION_MACHINE_MEMORY_ARE = "Os programas LPAS na mem�ria da m�quina de execu��o s�o:";
const string THERE_IS_ALREADY_A_PROGRAM = "J� existe um programa";
const string LOADED = "carregado";
const string INVALID_OPERATION = "Opera��o inv�lida";
const string NOT_FOUND_OR_NOT_ACCEPTED = "n�o encontrado ou n�o � um arquivo aceito.";
const string PROGRAM_NAME = "Nome do programa: ";
const string FAILED_TO_LOAD_PROGRAM = "Falha ao carregar programa";
const string FILE_ = "Arquivo";
const string FAILED_TO_OPEN_FILE = "Falha ao abrir o arquivo";
const string PROGRAM = "Programa";
const string SUCCESSFUL_LOADED = "carregado com sucesso.";
const string NOT_LOADED = "n�o carregado.";
const string MACHINE_MEMORY_FULL = "Mem�ria da maquina de execu��o cheia.\n" + WHITE_SPACES 
	+ "Use o comando 'replace [NOME_PROGRAMA_EM_MEMORIA] [CAMINHO_NOVO_PROGRAMA]' para substituir um programa em mem�ria.";
const string NO_INSTRUCTIONS = "Nenhuma instru��o.";
const string UP_AND_RUNNING = "carregado e executando...";
const string VALUE = "valor";


#endif // !CONSTANTS_H