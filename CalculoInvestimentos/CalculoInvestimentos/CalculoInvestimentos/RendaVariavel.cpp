#include "RendaVariavel.h"

RendaVariavel::RendaVariavel()
{
	settype("RV");
}

RendaVariavel::RendaVariavel(string nome) : Investimento(nome)
{
	settype("RV");
	setNome(nome);
}

RendaVariavel::RendaVariavel(
	string nome,
	string rating,
	bool protecaoFgc,
	Estrategia estrategia,
	float valorInvestido,
	float taxa,
	string dataInvestimento,
	string dataResgate
) : Investimento(
	"RV",
	nome,
	rating,
	protecaoFgc,
	estrategia,
	valorInvestido,
	taxa,
	dataInvestimento,
	dataResgate
)
{
	// nothing to do
}

string RendaVariavel::toSring()
{
	auto intervalo = getIntervaloInvestimento();

	string append = "Prazo: ";

	if (intervalo.getYears() > 0) {
		append += to_string(intervalo.getYears()) + " anos";
	}
	else {
		append += to_string(intervalo.getWorkingDays()) + " dias";
	}

	return Investimento::toSring() + " | " + append;
}

short RendaVariavel::getPrazo()
{
	auto p = getIntervaloInvestimento();
	return p.getYears() == 0 ? p.getWorkingDays() : p.getYears();
}

float RendaVariavel::calcularIR()
{
	return Investimento::calcularIR();
}

float RendaVariavel::getAliquota()
{
	return Imposto::TAXA_IR_15;
}
