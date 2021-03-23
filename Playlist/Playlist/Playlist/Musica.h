#ifndef MUSIC_H
#define MUSIC_H

#include<string>

using namespace std;

class Musica
{
public:

	Musica();

	Musica(string titulo, string artista);

	static int getQuantidadeMusicas();

	string getTitulo();

	void setTitulo(string titulo_);

	string getArtista();

	void setArtista(string artista);

	string toString();

	string displayByArtist();

	static bool isSameTitle(Musica musica, const string& titulo);

	static bool isSameArtist(Musica musica, string artista);

	static bool compareTitleAndArtist(Musica musica, Musica another);

	static bool compareArtistAndTitle(Musica musica, Musica another);

	static void resetQuantidadeMusicas();

private:

	static int quantidadeMusicas;

	string titulo;

	string artista;
};


#endif // MUSIC_H
