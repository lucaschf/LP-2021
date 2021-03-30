#ifndef IMPOSTO_H
#define IMPOSTO_H
/*
Define as alíquotas de Imposto de Renda (IR) a serem aplicadas sobre o rendimento bruto do investimento.
*/
class Imposto {
public:
	
	// Taxa de 22.5% de IR a ser calculado sobre o rendimento bruto de um investimento de até 180 dias.
	static const float TAXA_IR_22_5;
	
	// Taxa de 20% de IR a ser calculado sobre o rendimento bruto de um investimento de 181 a 360 dias.
	static const float TAXA_IR_20;
	
	// Taxa de 17.5% de IR a ser calculado sobre o rendimento bruto de um investimento de 361 a 720 dias.
	static const float TAXA_IR_17_5;
	
	// Taxa de 15% de IR a ser calculado sobre o rendimento bruto de um investimento acima de 720 dias.
	static const float TAXA_IR_15;
	
	Imposto();
	
	Imposto(float valor);

	Imposto& setImposto(float valor);
	
	float getImposto();

private:
	
	float valor;
};
#endif