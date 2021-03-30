#ifndef INVESTIMENTO_FACTORY_H
#define INVESTIMENTO_FACTORY_H

#include <string>
#include "Investimento.h"

class InvestimentoFactory
{
public:

	static Investimento* create(string type);

	static Investimento* create(
		string type,
		string nome,
		string rating,
		bool protecaoFgc,
		Estrategia estrategia,
		float valorInvestido,
		float taxa,
		string dataInvestimento,
		string dataResgate
	);

private:

	// prevents instantiation
	InvestimentoFactory() = default;
};

#endif // !INVESTIMENTO_FACTORY_H