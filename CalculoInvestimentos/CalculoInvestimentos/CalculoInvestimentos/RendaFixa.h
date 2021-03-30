#ifndef RENDA_FIXA_H
#define RENDA_FIXA_H

#include "Investimento.h"
#include "Imposto.h"

class RendaFixa : public Investimento {

public:

	RendaFixa();

	RendaFixa(string nome);

	RendaFixa(
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
	<nome> | <rating> | <estratégia> | FGC: <sim | não> | Prazo: <X> anos [e <Y> meses] | [ <Y> meses]
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>. O caractere pipe (|) entre os parênteses angulares < > significa ou, por exemplo: <sim | não> resulta em sim ou não.
	Na renda fixa o prazo deve ser exibido em meses se o período de investimento for inferior a um ano (até 12 meses), caso contrário, em anos.
	Os colchetes indicam uso opcional e que será usado no caso em que o período de investimento não representar um ano completo, por exemplo, 5 anos e 6 meses.
	Exemplos:
	CDB Original Jan/2020 | BBB+ | Inflação | FGC: sim | Prazo: 3 anos e 4 meses
	CDB PAN Nov/2025 | BBB+ | Pós-fixado | FGC: sim | Prazo: 4 anos
	CRI WS | AA+ | Prefixado | FGC: não | Prazo: 11 meses
	*/
	virtual string toSring();

	/* Retorna o prazo em meses se o período de investimento for inferior a um ano (12 meses), caso contrário, em anos.*/
	virtual short getPrazo();

	/* Calcula o valor do Imposto de Renda (IR) sobre o rendimento obtido no investimento.
	Investimentos de renda fixa possuem quatro alíquotas de IR, definidas na classe Imposto segundo o prazo do investimento.*/
	virtual float calcularIR();

	virtual float getAliquota();
};
#endif // !RENDA_FIXA_H