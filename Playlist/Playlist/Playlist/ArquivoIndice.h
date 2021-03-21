#ifndef ARQUIVO_INDICE_H
#define ARQUIVO_INDICE_H

#include "Indice.h"
#include "FilePersistence.h"
#include "CharSequence.h"


typedef struct {
	CharSequence chavePrimaria;
	unsigned int numeroRegistro;
} StctIndice;


class ArquivoIndice : public FilePersistence<Indice, StctIndice>
{
public:
	
	ArquivoIndice();

	ArquivoIndice(const string& nomeArquivo);

	int pesquisarChave(string* chave);

private:

	 StctIndice toStruct(Indice indice) override;

	 Indice* fromStruct(const StctIndice &stct) override;
};


#endif // ARQUIVO_INDICE_H

