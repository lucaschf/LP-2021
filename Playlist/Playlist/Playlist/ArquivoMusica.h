#ifndef ARQUIVO_MUSICA_H
#define ARQUIVO_MUSICA_H

#include <string>
#include <vector>

#include "Musica.h"
#include "CharSequence.h"
#include "FilePersistence.h"

using namespace std;

typedef struct {
	CharSequence artista;
	CharSequence titulo;
} StctMusica;

class ArquivoMusica : public FilePersistence<Musica, StctMusica> {

public:

	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	ArquivoMusica();

	// Cria um objeto para manipular o arquivo binario com acesso aleatorio cujo nome de
	// arquivo esta especificado em nomeArquivo. Abre o arquivo para leitura e escrita.
	ArquivoMusica(const string& nomeArquivo);

	/*
	* Pesquisa o t�tulo de uma m�sica no arquivo. Em caso de sucesso retorna o numero
	* do registro onde a m�sica est� armazenada e -1 caso contrario.
	*/
	int pesquisarTituloMusica(const string& tituloMusica);

	/*
	* Pesquisa o artista de uma m�sica no arquivo. Em caso de sucesso retorna o numero
	* do registro onde a musica est� armazenada e -1 caso contr�rio.
	*/
	int pesquisarArtista(string *artista);

private:

	StctMusica toStruct(Musica musica) override;

	Musica* fromStruct(const StctMusica& stct) override;
};

#endif // !ARQUIVO_MUSICA_H
