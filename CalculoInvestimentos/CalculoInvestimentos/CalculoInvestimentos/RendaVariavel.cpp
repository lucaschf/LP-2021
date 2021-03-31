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
	return Investimento::toSring() + " | " + to_string(getPrazo()) + " dias";
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
