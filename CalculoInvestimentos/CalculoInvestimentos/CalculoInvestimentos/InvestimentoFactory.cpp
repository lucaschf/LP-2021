#include "InvestimentoFactory.h"

#include "RendaFixa.h"
#include "RendaVariavel.h"


Investimento* InvestimentoFactory::create(string type)
{
	if (type == "RF")
		return new RendaFixa();

	if (type == "RV")
		return new RendaVariavel();

	throw string("Tipo de investimento inválido");
}

Investimento* InvestimentoFactory::create(
	string type,
	string nome,
	string rating,
	bool protecaoFgc,
	Estrategia estrategia,
	float valorInvestido,
	float taxa,
	string dataInvestimento,
	string dataResgate
)
{
	if (type == "RF")
		return new RendaFixa(
			nome,
			rating,
			protecaoFgc,
			estrategia,
			valorInvestido,
			taxa,
			dataInvestimento,
			dataResgate);

	if (type == "RV")
		return new RendaVariavel(
			nome,
			rating,
			protecaoFgc,
			estrategia,
			valorInvestido,
			taxa,
			dataInvestimento,
			dataResgate);

	throw string("Tipo de investimento inválido");
}
