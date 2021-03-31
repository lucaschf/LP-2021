#include "Investimento.h"
#include "RendaVariavel.h"
#include "ArquivoTexto.h"
#include "StringUtils.h"

#include <iostream>
#include "InvestimentoFactory.h"
#include "CalculoInvestimentos.h"
#include <clocale>
#include <vector>

using namespace std;

int main() {

	setlocale(LC_ALL, "pt-BR");

	CalculoInvestimentos c;

	try {
		c.obterInvestimentos("C:\\Users\\lucas\\Desktop\\investimentos.txt");
		for (auto i : c.relatorioPorTipoInvestimento()) {
			cout << "\n\t" << i;
		}
	}
	catch (string ex) {
		cout << endl << ex << endl;
	}


	vector <reference_wrapper<Investimento>> v;



	RendaVariavel iv = RendaVariavel();
	cout << typeid(iv).name() << endl;

	v.emplace_back(iv);
	cout << v.size();
	


	/*Periodo p = Periodo(StringUtils::toTime("15/01/2017"),
		StringUtils::toTime("15/12/2017"));

	cout << p.getMonths();*/
	return 0;
}