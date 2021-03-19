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

	void createPlaylist();

	void generateIndexes(vector<Indice> music, vector<Indice> artist);

	void clearFiles();

	vector<Musica> extractMusic(string folderPaht);

	void displayByMusicName();

	void displayByArtist();

	void searchByArtist();
};

#endif // ! PLAYLIST_H

