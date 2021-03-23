#ifndef  PLAYLIST_H
#define  PLAYLIST_H

#include "ArquivoMusica.h"
#include "ArquivoIndice.h"

class PlayList {

public:

	PlayList();

	int menu();

private :

	ArquivoMusica arquivoMusica;
	ArquivoIndice arquivoIndiceMusica;
	ArquivoIndice arquivoIndiceArtista;

	void showTitle(const string& title);

	void createPlaylist();

	void generateIndexes(vector<Indice> music, vector<Indice> artist);

	void clearFiles();

	vector<unique_ptr<Musica>> extractMusic(string folderPaht);

	void displayOrdered(string message, bool(*sorted)(Musica, Musica));

	void displayByMusicName();

	void displayByArtist();

	void searchByName();

	void searchByArtist();
};

#endif // ! PLAYLIST_H

