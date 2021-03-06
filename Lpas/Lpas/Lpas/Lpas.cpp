#include "ArquivoTexto.h"
#include <iostream>
#include "Programa.h"
#include "Utils.h"
#include "MaquinaExecucao.h"

using namespace std;

int main() {

	string path = "C:\\Users\\lucas\\Desktop\\New folder\\count1-15";


	Programa program;

	program.carregar(path);


	MaquinaExecucao maquinaExecucao;
	maquinaExecucao.carregar(program);

	maquinaExecucao.executarPrograma(0);


	return 0;
}