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

	// Define o prazo em dias �teis.
	Investimento& setPrazo(short prazo);

	// Retorna o prazo em dias �teis.
	virtual short getPrazo();

	// Define a taxa percentual ao ano (a.a.).
	Investimento& setTaxa(float taxa);

	// Retorna a taxa percentual ao ano (a.a.).
	float getTaxa();

	Investimento& setImposto(Imposto imposto);

	Imposto getImposto();

	/* Retorna uma string que representa os dados do investimento. Usa o formato abaixo:
	<nome> | <rating> | <estrat�gia> | FGC: <sim | n�o>
	Veja nos exemplos abaixo como os valores devem substituir as strings no formato acima representadas por <>.
	O caractere pipe (|) entre os par�nteses angulares < > significa ou, por exemplo: <sim | n�o> resulta em sim ou n�o.
	Exemplos:
	CDB Original Jan/2020 | BBB+ | Prefixado | FGC: sim
	A��es da Vale | AA+ | Renda Vari�vel | FGC: n�o
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

	// Nome do investimento, por exemplo, CDB, Tesouro Direto, LCI, LCA , A��es, etc.
	string nome;

	/* O rating, ou classifica��o de risco, � a nota dada a uma empresa, um pa�s, um t�tulo ou uma opera��o financeira para medir o risco de cr�dito.
	Serve para indicar a capacidade de um pa�s ou empresa de pagar suas d�vidas e as chances de n�o conseguir, atrasando o pagamento ou dando calote.
	Os investidores usam os �ratings� para tomarem decis�es na hora de aplicar seu dinheiro.
	Valores v�lidos de rating, do menor risco, alto grau de investimento (AAA), para o maior risco, baixo grau de investimento (D).
	Grau de investimento com qualidade alta e baixo risco: AAA, AA+, AA, AA-, A+, A, A-
	Grau de investimento com qualidade baixa: BBB+, BBB, BBB-
	Categoria de especula��o, baixa classifica��o: BB+, BB, BB-, B+, B, B-
	Risco de inadimpl�ncia (calote) e baixo interesse: CCC+, CCC, CCC-, CC, C, D
	*/
	string rating;

	/* Indica se o investimento tem prote��o do Fundo Garantidor de Cr�ditos (FGC).
	true: tem prote��o
	false: sem prote��o
	Os investimento que tem prote��o do FGC s�o: Poupan�a, CDB, LCI, LCA e Letras de C�mbio (LC).
	*/
	bool protecaoFgc;

	// Indica o tipo de estrat�gia usada no Investimento.
	Estrategia estrategia;

	// Valor investido no investimento.
	float valorInvestido;

	// Data em que o investimento foi realizado, ou seja, em que o dinheiro foi investido.
	string dataInvestimento;

	// Data em que o dinheiro pode ser resgatado do investimento.
	string dataResgate;
	
	/* Per�odo em dias �teis do investimento. Representa a diferen�a entre as datas de resgate e investimento.*/
	short prazo;

	/* Valor percentual usado para rentabilizar ou remunerar o valor investido. A taxa (juros) deve ser especificada ao ano (a.a.).
	Na renda fixa a taxa do investimento � conhecida na data em que o dinheiro � investido, e na renda vari�vel a taxa s� � conhecida na data de resgate do investimento.*/
	float taxa;
	
	/* Taxa de imposto de renda a ser calculado sobre o rendimento bruto de um investimento de acordo com o seu prazo em dias.*/
	Imposto imposto;

	Periodo intervaloInvestimento;

	string type;
};
#endif // !INVESTIMENTO_H