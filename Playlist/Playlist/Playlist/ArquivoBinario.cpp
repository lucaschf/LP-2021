#include <iostream>
#include "ArquivoBinario.h"

bool ArquivoBinario::abrir(const string& nomeArquivo) {
	this->name = nomeArquivo;

	arquivoBinario.open(nomeArquivo, ios::app | ios::in | ios::binary);

	return arquivoBinario ? true : false;
}

void ArquivoBinario::fechar() {
	if (arquivoBinario.is_open())
		arquivoBinario.close();
}

string ArquivoBinario::getNomeArquivo() {
	return name;
}

unsigned long ArquivoBinario::tamanho() {
	arquivoBinario.seekp(0, ios::beg);
	unsigned long inicio = static_cast<unsigned long>(arquivoBinario.tellp());

	arquivoBinario.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(arquivoBinario.tellp());

	return fim - inicio;
}

void ArquivoBinario::clear()
{
	fechar();
	remove(getNomeArquivo().c_str());
	abrir(getNomeArquivo());
}
