#ifndef CALCULO_INVESTIMENTOS_H
#define CALCULO_INVESTIMENTOS_H

#include<vector>
#include "Investimento.h"

using namespace std;

class CalculoInvestimentos
{
public:

	int menu();

	~CalculoInvestimentos();

private:

	void obterInvestimentos(string caminhoArquivo);

	void relatorioPorTipoInvestimento();

	void relatorioPorEstrategia();

	vector<Investimento*> investimentos;

	void clearInvestimentos();

	void importaDados();
};

#endif // !CALCULO_INVESTIMENTOS_H