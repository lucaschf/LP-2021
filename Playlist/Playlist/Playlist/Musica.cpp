#include "Musica.h"

int Musica::quantidadeMusicas = 0;
int Musica::geradorIndice = 0;

Musica::Musica(string titulo_, string artista_)
{
	setTitulo(std::move(titulo_));
	setArtista(std::move(artista_));
}

int Musica::getQuantidadeMusicas()
{
	return quantidadeMusicas;
}

string Musica::getTitulo()
{
	return this->titulo;
}

void Musica::setTitulo(string titulo_)
{
	this->titulo = std::move(titulo_);
}

string Musica::getArtista()
{
	return this->artista;
}

void Musica::setArtista(string artista_)
{
	this->artista = std::move(artista_);
}

string Musica::toString()
{
	return titulo + " - " + artista;
}

bool Musica::compareTitulo(Musica musica, const string& titulo)
{
	return musica.getTitulo() == titulo;
}

bool Musica::compareArtista(Musica musica, const string& artista)
{
	return musica.getArtista() == artista;
}
