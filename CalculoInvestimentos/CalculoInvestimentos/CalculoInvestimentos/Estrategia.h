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
Define as estrat�gias dos diferentes tipos de investimento.
*/
class Estrategia {

public:

	Estrategia() = default;

	Estrategia(EstrategiaInvestimento estrategia);

	/* Obt�m uma descri��o corresponde ao tipo de estrat�gia de um investimento.
	O valor resultante, segundo uma das constantes definidas na enumera��o EstrategiaInvestimento, corresponde a uma string literal a seguir:
	"Infla��o", "Prefixado", "P�s-fixado", "Renda Vari�vel", "Internacional", "Multimercado" ou "Alternativo".
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