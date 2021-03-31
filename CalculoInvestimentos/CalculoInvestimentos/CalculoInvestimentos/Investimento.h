#ifndef INVESTIMENTO_H
#define INVESTIMENTO_H

#include <string>
#include "Estrategia.h"
#include "Imposto.h"
#include "Periodo.h"

using namespace std;

class Investimento {

public:

	Investimento();

	Investimento(string nome);

	Investimento(
		string type,
		string nome, 
		string rating, 
		bool protecaoFgc, 
		Estrategia estrategia, 
		float valorInvestido,
		float taxa,
		string dataInvestimento, 
		string dataResgate
	);

	Investimento& setNome(string nome);

	string getNome() const;

	Investimento& setRating(string rating);

	string getRating() const;

	Investimento& setProtecaoFgc(bool protecaoFgc);

	bool getProtecaoFgc();

	Investimento& setEstrategia(Estrategia estrategia);

	Estrategia getEstrategia();

	Investimento& setValorInvestido(float valorInvestido);

	float getValorInvestido();

	Investimento& setDataInvestimento(string dataInvestimento);

	string getDataInvestimento();

	Investimento& setDataResgate(string dataResgate);

	string getDataResgate();

	// Define o prazo em dias úteis.
	Investimento& setPrazo(short prazo);

	// Retorna o prazo em dias úteis.
	virtual short getPrazo();

	// Define a taxa percentual ao ano (a.a.).
	Investimento& setTaxa(float taxa);

	// Retorna a taxa percentual ao ano (a.a.).
	float getTaxa();

	Investimento& setImposto(Imposto imposto);

	Imposto getImposto();

	/* Retorna uma string que representa os dados do investimento. Usa o formato abaixo:
	<nome> | <rating> | <estratégia> | FGC: <sim | não>
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>.
	O caractere pipe (|) entre os parênteses angulares < > significa ou, por exemplo: <sim | não> resulta em sim ou não.
	Exemplos:
	CDB Original Jan/2020 | BBB+ | Prefixado | FGC: sim
	Ações da Vale | AA+ | Renda Variável | FGC: não
	*/
	virtual string toSring();

	// Calcula o valor do Imposto de Renda (IR) sobre o rendimento obtido no investimento.
	virtual float calcularIR();

	double getTaxaMensal();

	double calculaValorRendimentoBruto();

	double getRendaBrutaCumulativa();

	double getRendaLiquidaCumulativa();

	double calculaValorLiquidoCumulativo();

	short getPrazoEmMeses();

	Periodo getIntervaloInvestimento() const;

	virtual float getAliquota() = 0;

	string getType();

protected:
	
	void settype(string type);

private:

	// Nome do investimento, por exemplo, CDB, Tesouro Direto, LCI, LCA , Ações, etc.
	string nome;

	/* O rating, ou classificação de risco, é a nota dada a uma empresa, um país, um título ou uma operação financeira para medir o risco de crédito.
	Serve para indicar a capacidade de um país ou empresa de pagar suas dívidas e as chances de não conseguir, atrasando o pagamento ou dando calote.
	Os investidores usam os “ratings” para tomarem decisões na hora de aplicar seu dinheiro.
	Valores válidos de rating, do menor risco, alto grau de investimento (AAA), para o maior risco, baixo grau de investimento (D).
	Grau de investimento com qualidade alta e baixo risco: AAA, AA+, AA, AA-, A+, A, A-
	Grau de investimento com qualidade baixa: BBB+, BBB, BBB-
	Categoria de especulação, baixa classificação: BB+, BB, BB-, B+, B, B-
	Risco de inadimplência (calote) e baixo interesse: CCC+, CCC, CCC-, CC, C, D
	*/
	string rating;

	/* Indica se o investimento tem proteção do Fundo Garantidor de Créditos (FGC).
	true: tem proteção
	false: sem proteção
	Os investimento que tem proteção do FGC são: Poupança, CDB, LCI, LCA e Letras de Câmbio (LC).
	*/
	bool protecaoFgc;

	// Indica o tipo de estratégia usada no Investimento.
	Estrategia estrategia;

	// Valor investido no investimento.
	float valorInvestido;

	// Data em que o investimento foi realizado, ou seja, em que o dinheiro foi investido.
	string dataInvestimento;

	// Data em que o dinheiro pode ser resgatado do investimento.
	string dataResgate;
	
	/* Período em dias úteis do investimento. Representa a diferença entre as datas de resgate e investimento.*/
	short prazo;

	/* Valor percentual usado para rentabilizar ou remunerar o valor investido. A taxa (juros) deve ser especificada ao ano (a.a.).
	Na renda fixa a taxa do investimento é conhecida na data em que o dinheiro é investido, e na renda variável a taxa só é conhecida na data de resgate do investimento.*/
	float taxa;
	
	/* Taxa de imposto de renda a ser calculado sobre o rendimento bruto de um investimento de acordo com o seu prazo em dias.*/
	Imposto imposto;

	Periodo intervaloInvestimento;

	string type;
};
#endif // !INVESTIMENTO_H