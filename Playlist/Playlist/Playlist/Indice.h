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

private:

	string chavePrimaria; // nome da musica ou artista 

	unsigned int numeroRegistro;
};

#endif // !INDICE_H
