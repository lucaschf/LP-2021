#ifndef MUSIC_H
#define MUSIC_H

#include<string>

using namespace std;

class Musica
{
public:

	Musica() = default;

	Musica(string titulo, string artista);

	static int getQuantidadeMusicas();

	string getTitulo();

	void setTitulo(string titulo_);

	string getArtista();

	void setArtista(string artista);

	string toString();

	string displayByArtist();

	static bool compareTitulo(Musica musica, const string& titulo);

	static bool compareArtista(Musica musica, const string& artista);

	static bool compareTitleAndArtist(Musica musica, Musica another);

	static bool compareArtistAndTitle(Musica musica, Musica another);

private:

	static int quantidadeMusicas;

	static int geradorIndice;

	string titulo;

	string artista;
};


#endif // MUSIC_H
