#include "Estrategia.h"

map<EstrategiaInvestimento, string> Estrategia::estrategiaToStringMap = {
        {EstrategiaInvestimento::INFLACAO, "Infla��o"},
        {EstrategiaInvestimento::PREFIXADO, "Prefixado"},
        {EstrategiaInvestimento::POS_FIXADO, "P�s-fixado"},
        {EstrategiaInvestimento::RENDA_VARIAVEL, "Renda Vari�vel"},
        {EstrategiaInvestimento::INTERNACIONAL, "Internacional"},
        {EstrategiaInvestimento::MULTIMERCADO, "Multimercado"},
        {EstrategiaInvestimento::ALTERNATIVO, "Alternativo"}
};

Estrategia::Estrategia(EstrategiaInvestimento estrategia)
{
	setEstrategia(estrategia);
}

string Estrategia::obterEstrategia(EstrategiaInvestimento estrategia)
{
	return estrategiaToStringMap.find(estrategia)->second;
}

Estrategia& Estrategia::setEstrategia(EstrategiaInvestimento estrategia)
{
	this->estrategia = estrategia;
	return *this;
}

EstrategiaInvestimento Estrategia::getEstrategia()
{
	return this->estrategia;
}

EstrategiaInvestimento Estrategia::from(string str)
{
    for (auto& it : estrategiaToStringMap) {
        if (it.second == str)
            return it.first;
    }

    throw string("Estrategia de investimento inv�lida");
}
