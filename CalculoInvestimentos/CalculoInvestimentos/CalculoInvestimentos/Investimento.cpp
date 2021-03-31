#include "Investimento.h"
#include "StringUtils.h"

Investimento::Investimento()
{
	setEstrategia(Estrategia());
}

Investimento::Investimento(string nome)
{
	setNome(nome);
	setEstrategia(Estrategia());
}

Investimento::Investimento(
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
	setNome(nome);
	setRating(rating);
	setProtecaoFgc(protecaoFgc);
	setEstrategia(estrategia);
	setValorInvestido(valorInvestido);
	setTaxa(taxa);
	setDataInvestimento(dataInvestimento);
	setDataResgate(dataResgate);
	this->type = type;

	intervaloInvestimento = Periodo(
		StringUtils::toTime(dataInvestimento),
		StringUtils::toTime(dataResgate)
	);

	setPrazo(intervaloInvestimento.getWorkingDays());
}

Investimento& Investimento::setNome(string nome)
{
	this->nome = nome;
	return (*this);
}

string Investimento::getNome() const
{
	return this->nome;
}

Investimento& Investimento::setRating(string rating)
{
	this->rating = rating;
	return *this;
}

string Investimento::getRating() const
{
	return this->rating;
}

Investimento& Investimento::setProtecaoFgc(bool protecaoFgc)
{
	this->protecaoFgc = protecaoFgc;
	return *this;
}

bool Investimento::getProtecaoFgc()
{
	return this->protecaoFgc;
}

Investimento& Investimento::setEstrategia(Estrategia estrategia)
{
	this->estrategia = estrategia;
	return *this;
}

Estrategia Investimento::getEstrategia()
{
	return this->estrategia;
}

Investimento& Investimento::setValorInvestido(float valorInvestido)
{
	this->valorInvestido = valorInvestido;
	return *this;
}

float Investimento::getValorInvestido()
{
	return this->valorInvestido;
}

Investimento& Investimento::setDataInvestimento(string dataInvestimento)
{
	this->dataInvestimento = dataInvestimento;
	return *this;
}

string Investimento::getDataInvestimento()
{
	return this->dataInvestimento;
}

Investimento& Investimento::setDataResgate(string dataResgate)
{
	this->dataResgate = dataResgate;
	return *this;
}

string Investimento::getDataResgate()
{
	return this->dataResgate;
}

Investimento& Investimento::setPrazo(short prazo)
{
	this->prazo = prazo;
	return*this;
}

short Investimento::getPrazo()
{
	return this->prazo;
}

Investimento& Investimento::setTaxa(float taxa)
{
	this->taxa = taxa;
	return *this;
}

float Investimento::getTaxa()
{
	return this->taxa;
}

Investimento& Investimento::setImposto(Imposto imposto)
{
	this->imposto = imposto;
	return*this;
}

Imposto Investimento::getImposto()
{
	return this->imposto;
}

/* Retorna uma string que representa os dados do investimento. Usa o formato abaixo:
	<nome> | <rating> | <estratégia> | FGC: <sim | não>
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>.
	O caractere pipe (|) entre os parênteses angulares < > significa ou, por exemplo: <sim | não> resulta em sim ou não.
	Exemplos:
	CDB Original Jan/2020 | BBB+ | Prefixado | FGC: sim
	Ações da Vale | AA+ | Renda Variável | FGC: não
	*/
string Investimento::toSring()
{
	return getNome() + " | " +
		getRating() + " | " +
		getEstrategia().obterEstrategia(getEstrategia().getEstrategia()) + " | " +
		"FGC: " + (protecaoFgc ? "sim" : "não")
		;
}

float Investimento::calcularIR()
{
	return (float)((getAliquota() / 100) * getRendaBrutaCumulativa());
}

double Investimento::getTaxaMensal()
{
	return pow((1 + getTaxa() / 100.0), (1.0 / 12.0)) - 1;
}

double Investimento::calculaValorRendimentoBruto()
{
	return getValorInvestido() * pow(1 + getTaxaMensal(), getPrazoEmMeses());
}

double Investimento::getRendaBrutaCumulativa()
{
	return calculaValorRendimentoBruto() - getValorInvestido();
}

double Investimento::getRendaLiquidaCumulativa()
{
	return calculaValorLiquidoCumulativo() - getValorInvestido();
}

double Investimento::calculaValorLiquidoCumulativo()
{
	return calculaValorRendimentoBruto() - calcularIR();
}

double Investimento::getRentabilidade()
{
	return getRendaBrutaCumulativa() / getValorInvestido();
}

double Investimento::getRentabilidadeToDisplay()
{
	return getRentabilidade() * 100;
}

short Investimento::getPrazoEmMeses()
{
	return intervaloInvestimento.getMonths();
}

Periodo Investimento::getIntervaloInvestimento() const
{
	return this->intervaloInvestimento;
}

string Investimento::getType()
{
	return type;
}

void Investimento::settype(string type)
{
	this->type = type;
}
