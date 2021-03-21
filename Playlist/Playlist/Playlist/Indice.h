#ifndef INDICE_H
#define INDICE_H

#include<string>

using namespace std;

class Indice
{
public:

	Indice() = default;

	Indice(string chavePrimaria, int numeroRegistro);

	string getChavePrimaria();

	void setChavePrimaria(string chavePrimaria);

	unsigned int getNumeroRegistro();

	void setNumeroRegistro(unsigned int numeroRegistro);

	string toString();

	static bool hasSamePrimaryKey(Indice indice, string chave);

private:

	string chavePrimaria;

	unsigned int numeroRegistro = 0;
};

#endif // !INDICE_H
