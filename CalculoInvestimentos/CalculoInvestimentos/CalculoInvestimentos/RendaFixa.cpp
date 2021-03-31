#include "RendaFixa.h"

RendaFixa::RendaFixa()
{
	settype("RF");
}

RendaFixa::RendaFixa(string nome) : Investimento(nome)
{
	setNome(nome);
	settype("RF");
}

RendaFixa::RendaFixa(
	string nome,
	string rating,
	bool protecaoFgc,
	Estrategia estrategia,
	float valorInvestido,
	float taxa,
	string dataInvestimento,
	string dataResgate
) : Investimento(
	"RF",
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

string RendaFixa::toSring()
{
	auto intervalo = getIntervaloInvestimento();

	string append = "Prazo: ";

	if (intervalo.getYears() > 0) {
		append += to_string(intervalo.getYears()) + " anos";
	}
	else {
		append += to_string(intervalo.getMonths()) + " meses";
	}

	auto test = intervalo.getMonths() % 12;
	if (test != 0) {
		append += " e " + to_string(test) + " meses";
	}

	return Investimento::toSring() + " | " + append;
}

short RendaFixa::getPrazo()
{
	auto p = getIntervaloInvestimento();

	return p.getYears() == 0 ? p.getMonths() : p.getYears();
}

float RendaFixa::calcularIR()
{
	return Investimento::calcularIR();
}

float RendaFixa::getAliquota()
{
	auto dias = Investimento::getPrazo();

	if (dias > 720)
		return Imposto::TAXA_IR_15;

	if (dias > 360)
		return Imposto::TAXA_IR_17_5;

	if (dias > 180)
		return Imposto::TAXA_IR_20;

	return Imposto::TAXA_IR_22_5;
}
