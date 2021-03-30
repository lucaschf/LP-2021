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
	<nome> | <rating> | <estrat�gia> | FGC: <sim | n�o> | Prazo: <X> anos [e <Y> meses] | [ <Y> dias]
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>. O caractere pipe (|) entre os par�nteses angulares < > 
	significa ou, por exemplo: <sim | n�o> resulta em sim ou n�o.
	Na renda vari�vel o prazo deve ser exibido em dias se o per�odo de investimento for inferior a um ano (at� 252 dias �teis), caso contr�rio, em anos.
	Os colchetes indicam uso opcional e que ser� usado no caso em que o per�odo de investimento n�o representar um ano completo, por exemplo, 5 anos e 6 meses.
	Exemplos:
	Real FIA | BBB+ | Renda Vari�vel | FGC: n�o | Prazo: 3 anos e 4 meses
	CS Sa�de Digital | AA+ | Alternativos | FGC: n�o | Prazo: 5 anos
	Trend Bolsa Americana | A+ | Internacional | FGC: n�o | Prazo: 180 dias
	*/
	virtual string toSring();

	/* Retorna o prazo em dias se o per�odo de investimento for inferior a um ano (252 dias �teis), caso contr�rio, em anos.
	*/
	virtual short getPrazo();

	/* Calcula o valor do Imposto de Renda (IR) sobre o rendimento obtido no investimento.
	Investimentos de renda vari�vel possui uma �nica al�quota de IR de 15%, definida na classe Imposto como a constante TAXA_IR_15.
	7 / 11
	*/
	virtual float calcularIR();

	virtual float getAliquota();
};
#endif // !RENDA_VARIAVEL_H