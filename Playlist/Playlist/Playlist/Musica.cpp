#include "Musica.h"
#include <filesystem>

int Musica::quantidadeMusicas = 0;

Musica::Musica()
{
	quantidadeMusicas++;
}

Musica::Musica(string titulo_, string artista_)
{
	setTitulo(std::move(titulo_));
	setArtista(std::move(artista_));
	quantidadeMusicas++;
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

string Musica::displayByArtist()
{
	return  artista + " - " + titulo;
}

bool Musica::isSameTitle(Musica musica, const string& titulo)
{
	return musica.getTitulo() == titulo;
}

bool Musica::isSameArtist(Musica musica, string artista)
{
	return musica.getArtista() == artista;
}

bool Musica::compareTitleAndArtist(Musica musica, Musica another)
{
	auto titleResult = musica.getTitulo().compare(another.getTitulo());

	return titleResult < 0 || titleResult == 0 &&
		musica.getArtista().compare(another.getArtista()) <= 0;
}

bool Musica::compareArtistAndTitle(Musica musica, Musica another)
{
	auto artistResult = musica.getArtista().compare(another.getArtista());

	return artistResult < 0 || artistResult == 0 &&
		musica.getTitulo().compare(another.getTitulo()) <= 0;
}

void Musica::resetQuantidadeMusicas()
{
	quantidadeMusicas = 0;
}
