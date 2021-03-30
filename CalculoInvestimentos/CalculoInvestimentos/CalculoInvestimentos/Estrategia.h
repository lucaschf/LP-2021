#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <string>
#include <map>

using namespace std;

enum class EstrategiaInvestimento {
	INFLACAO,
	PREFIXADO,
	POS_FIXADO,
	RENDA_VARIAVEL,
	INTERNACIONAL,
	MULTIMERCADO,
	ALTERNATIVO
};

/*
Define as estratégias dos diferentes tipos de investimento.
*/
class Estrategia {

public:

	Estrategia() = default;

	Estrategia(EstrategiaInvestimento estrategia);

	/* Obtém uma descrição corresponde ao tipo de estratégia de um investimento.
	O valor resultante, segundo uma das constantes definidas na enumeração EstrategiaInvestimento, corresponde a uma string literal a seguir:
	"Inflação", "Prefixado", "Pós-fixado", "Renda Variável", "Internacional", "Multimercado" ou "Alternativo".
	*/
	static string obterEstrategia(EstrategiaInvestimento estrategia);

	Estrategia& setEstrategia(EstrategiaInvestimento estrategia);

	EstrategiaInvestimento getEstrategia();

	static EstrategiaInvestimento from(string str);

private:

	static map<EstrategiaInvestimento, string> estrategiaToStringMap;

	EstrategiaInvestimento estrategia;

};
#endif