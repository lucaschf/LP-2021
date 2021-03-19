#include "Indice.h"

Indice::Indice(string chavePrimaria, int numeroRegistro)
{
    setChavePrimaria(chavePrimaria);
    setNumeroRegistro(numeroRegistro);
}

string Indice::getChavePrimaria()
{
    return chavePrimaria;
}

void Indice::setChavePrimaria(string chavePrimaria)
{
    this->chavePrimaria = chavePrimaria;
}

unsigned int Indice::getNumeroRegistro()
{
    return numeroRegistro;
}

void Indice::setNumeroRegistro(unsigned int numeroRegistro)
{
    this->numeroRegistro = numeroRegistro;
}

string Indice::toString()
{
    return to_string(numeroRegistro) + " - " + chavePrimaria  ;
}
