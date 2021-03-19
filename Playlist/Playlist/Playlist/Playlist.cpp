#include <iostream>

#include <string>
#include "Constants.h"
#include "Playlist.h"
#include "Utils.h"
#include "Musica.h"
#include "ArquivoMusica.h"
#include <algorithm> 

using namespace std;


int main() {
	return PlayList().menu();
}

PlayList::PlayList()
{
	arquivoMusica.abrir("Playlist.dat");
	arquivoIndiceArtista.abrir("indiceArtista.dat");
	arquivoIndiceMusica.abrir("indiceMusica.dat");
}

int PlayList::menu()
{
	string read;
	char choosen;

	do {
		cout << "1 - " << CREATE_PLAYLIST << endl;
		cout << "2 - " << DISPLAY_BY_MUSIC_NAME << endl;
		cout << "3 - " << DISPLAY_BY_ARTIST << endl;
		cout << "4 - " << SEARCH_BY_NAME << endl;
		cout << "5 - " << SEARCH_BY_ARTIST << endl;
		cout << "6 - " << EXIT << endl;

		getline(cin, read);
		choosen = atoi(read.c_str());

		switch (choosen)
		{
		case 1:
			createPlaylist();
			break;
		case 2:
			displayByMusicName();
			break;
		case 3:
			displayByArtist();
			break;
		case 5:
			searchByArtist();
			break;
		case 7:
			for (auto i : arquivoIndiceMusica.readAll())
				cout << i.toString() << endl;
			break;
		default:
			for (auto i : arquivoIndiceArtista.readAll())
				cout << i.toString() << endl;
			break;
		}

	} while (choosen != 6);

	return 0;
}

void PlayList::createPlaylist()
{
	string path;

	cout << DIRETORY << ": ";

	getline(cin, path);

	if (!Utils::exists(path)) {
		cout << DIRECTORY_NOT_FOUND << endl;
		return;
	}

	clearFiles();

	auto musicFiles = extractMusic(path);
	vector<Indice> indiceMusicas;
	vector<Indice> indiceArtistas;

	if (musicFiles.empty()) {
		cout << NO_SONGS_FOUND << endl;
		return;
	}

	unsigned int index = 0;
	for (auto m : musicFiles) {
		arquivoMusica.escrever(m);
		indiceArtistas.emplace_back(Indice(m.getArtista(), index));
		indiceMusicas.emplace_back(Indice(m.getTitulo(), index));
		index++;
	}

	generateIndexes(indiceMusicas, indiceArtistas);

	cout << PLAYLIST_CREATED_WITH << " " << musicFiles.size() << " " << MUSIC_S << endl;
}

void PlayList::generateIndexes(vector<Indice> musicIndices, vector<Indice> artistIndices)
{
	auto comparator = [](Indice indice, Indice another) {
		return indice.getChavePrimaria().compare(another.getChavePrimaria()) < 0;
	};

	sort(musicIndices.begin(), musicIndices.end(), comparator);

	for (auto index : musicIndices) {
		arquivoIndiceMusica.escrever(index);
	}

	sort(artistIndices.begin(), artistIndices.end(), comparator);

	for (auto index : artistIndices) {
		arquivoIndiceArtista.escrever(index);
	}
}

void PlayList::clearFiles()
{
	arquivoMusica.clear();
	arquivoIndiceArtista.clear();
	arquivoIndiceMusica.clear();
}

vector<Musica> PlayList::extractMusic(string folderPaht)
{
	vector<Musica> music;
	vector<string> filesInFolder;

	if (Utils::getAllFiles(folderPaht, filesInFolder, MPEG_EXTENSION, true, false) > 0)
	{
		for (auto& f : filesInFolder) {
			auto data = Utils::tokenize(f, '-', true);
			if (data.size() == 2)
				music.emplace_back(Musica(data[1], data[0]));
		}
	}

	return music;
}

void PlayList::displayByMusicName()
{
	auto music = arquivoMusica.readAll();

	sort(music.begin(), music.end(), Musica::compareTitleAndArtist);

	cout << PLAYLIST_ORDERED_BY_MUSIC_NAME << endl;
	cout << NUMBER_OF_MUSIC << music.size() << endl << endl;

	for (int i = 0; i < music.size(); i++) {
		cout << "\t" << i + 1 << ". " << music.at(i).toString() << endl;
	}
}

void PlayList::displayByArtist()
{
	auto music = arquivoMusica.readAll();

	sort(music.begin(), music.end(), Musica::compareArtistAndTitle);

	cout << PLAYLIST_ORDERED_BY_ARTIST << endl;
	cout << NUMBER_OF_MUSIC << music.size() << endl << endl;

	for (int i = 0; i < music.size(); i++) {
		cout << "\t" << i + 1 << ". " << music.at(i).displayByArtist() << endl;
	}
}

void PlayList::searchByArtist()
{
	/*string name;

	getline(cin, name);

	auto pos = arquivoMusica.pesquisarArtista(&name);

	if (pos == -1)
	{
		cout << ARTIST_NOT_FOUND << endl;
		return;
	}

	while (pos != -1) {
		cout << arquivoMusica.ler(pos)->toString() << endl;
		pos = arquivoMusica.pesquisarArtista(NULL);
	}*/


	string name;

	getline(cin, name);

	arquivoIndiceArtista.pes
}
