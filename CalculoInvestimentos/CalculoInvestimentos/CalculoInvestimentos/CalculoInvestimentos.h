#ifndef CALCULO_INVESTIMENTOS_H
#define CALCULO_INVESTIMENTOS_H

#include<vector>
#include "Investimento.h"

using namespace std;

class CalculoInvestimentos
{
public:

	void obterInvestimentos(string caminhoArquivo);

	~CalculoInvestimentos();

	vector<string> relatorioPorTipoInvestimento();

private:

	vector<Investimento*> investimentos;

	void clearInvestimentos();

};

#endif // !CALCULO_INVESTIMENTOS_H