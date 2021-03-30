#include "Investimento.h"
#include "RendaVariavel.h"
#include "ArquivoTexto.h"
#include "StringUtils.h"

#include <iostream>
#include "InvestimentoFactory.h"
#include "CalculoInvestimentos.h"
#include <clocale>

using namespace std;

int main() {

	setlocale(LC_ALL, "pt-BR");

	CalculoInvestimentos c;

	try {
		c.obterInvestimentos("C:\\Users\\lucas\\Desktop\\investimentos.txt");
		for (auto i : c.relatorioPorTipoInvestimento()) {
			cout << i;
		}
	}
	catch (string ex) {
		cout << endl << ex << endl;
	}
	return 0;
}