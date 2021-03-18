#include "ArquivoMusica.h"

#include <utility>
#include "StringUtils.h"

ArquivoMusica::ArquivoMusica()
{
    file = new ArquivoBinario();
}

ArquivoMusica::ArquivoMusica(const string& nomeArquivo) {
    initializeFile(nomeArquivo);
}

int ArquivoMusica::pesquisarTituloMusica(const string& tituloMusica) {
    Musica musica;

    return find<const string&>(musica, tituloMusica, Musica::compareTitulo);
}

int ArquivoMusica::pesquisarArtista(const string& artista) {
    Musica musica;

    return find<const string&>(musica, artista, Musica::compareArtista);
}

StctMusica ArquivoMusica::toStruct(Musica musica) {
    StctMusica stctMusica;

    StringUtils::toCharSequence(musica.getArtista(), stctMusica.artista);
    StringUtils::toCharSequence(musica.getTitulo(), stctMusica.titulo);

    return stctMusica;
}

Musica* ArquivoMusica::fromStruct(const StctMusica &stct)
{
    return new Musica(stct.titulo, stct.artista);
}