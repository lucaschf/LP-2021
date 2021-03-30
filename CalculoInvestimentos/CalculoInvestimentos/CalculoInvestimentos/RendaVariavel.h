#ifndef RENDA_VARIAVEL_H
#define RENDA_VARIAVEL_H

#include "Investimento.h"

class RendaVariavel : public Investimento {
public:

	RendaVariavel();

	RendaVariavel(string nome);

	RendaVariavel(
		string nome,
		string rating,
		bool protecaoFgc,
		Estrategia estrategia,
		float valorInvestido,
		float taxa,
		string dataInvestimento,
		string dataResgate
	);

	/* Retorna uma string que representa os dados do investimento. Usa o formato abaixo:
	<nome> | <rating> | <estratégia> | FGC: <sim | não> | Prazo: <X> anos [e <Y> meses] | [ <Y> dias]
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>. O caractere pipe (|) entre os parênteses angulares < > 
	significa ou, por exemplo: <sim | não> resulta em sim ou não.
	Na renda variável o prazo deve ser exibido em dias se o período de investimento for inferior a um ano (até 252 dias úteis), caso contrário, em anos.
	Os colchetes indicam uso opcional e que será usado no caso em que o período de investimento não representar um ano completo, por exemplo, 5 anos e 6 meses.
	Exemplos:
	Real FIA | BBB+ | Renda Variável | FGC: não | Prazo: 3 anos e 4 meses
	CS Saúde Digital | AA+ | Alternativos | FGC: não | Prazo: 5 anos
	Trend Bolsa Americana | A+ | Internacional | FGC: não | Prazo: 180 dias
	*/
	virtual string toSring();

	/* Retorna o prazo em dias se o período de investimento for inferior a um ano (252 dias úteis), caso contrário, em anos.
	*/
	virtual short getPrazo();

	/* Calcula o valor do Imposto de Renda (IR) sobre o rendimento obtido no investimento.
	Investimentos de renda variável possui uma única alíquota de IR de 15%, definida na classe Imposto como a constante TAXA_IR_15.
	7 / 11
	*/
	virtual float calcularIR();

	virtual float getAliquota();
};
#endif // !RENDA_VARIAVEL_H