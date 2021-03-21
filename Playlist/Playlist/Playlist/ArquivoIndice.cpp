#include "ArquivoIndice.h"
#include "StringUtils.h"

ArquivoIndice::ArquivoIndice()
{
	file = new ArquivoBinario();
}

ArquivoIndice::ArquivoIndice(const string& nomeArquivo)
{
	initializeFile(nomeArquivo);
}

int ArquivoIndice::pesquisarChave(string* chave)
{
	Indice indice;

	auto it = findInSequentially<string>(indice, chave, Indice::hasSamePrimaryKey);

	if (it == nullptr)
		return -1;

	return it->getNumeroRegistro();
}

StctIndice ArquivoIndice::toStruct(Indice indice)
{
	StctIndice stctIndice;

	StringUtils::toCharSequence(indice.getChavePrimaria(), stctIndice.chavePrimaria);
	stctIndice.numeroRegistro = indice.getNumeroRegistro();

	return stctIndice;
}

Indice* ArquivoIndice::fromStruct(const StctIndice& stct)
{
	return new Indice(stct.chavePrimaria, stct.numeroRegistro);
}
