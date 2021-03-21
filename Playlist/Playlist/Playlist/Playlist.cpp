#include <iostream>

#include <string>
#include "Constants.h"
#include "Playlist.h"
#include "Utils.h"
#include "Musica.h"
#include "ArquivoMusica.h"
#include <algorithm> 
#include "StringUtils.h"

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

/*
* Menu da aplicacao
* 
* NOTA:  
* verifiquei em varios lugares e na documentação da linguagem e nao consegui encontrar uma forma de implementar
* essa pesquisa usando o binary_search, a propria documentacao da linguagem na funcao, sugere que para pegarmos um iterador
* usemos a funcao std::find ou a uma funcao especializada como pode ver na imagem 'binary_search_info.png' que coloquei no
* diretorio de recuros(obtive acesso a essa documentacao usando a IDE Clion da jetbrains).
*/
int PlayList::menu()
{
	string read;
	int choosen;

	do {
		cout << "Playlist ==============\n\n";
		cout << "1 - " << CREATE_PLAYLIST << endl;
		cout << "2 - " << DISPLAY_BY_MUSIC_NAME << endl;
		cout << "3 - " << DISPLAY_BY_ARTIST << endl;
		cout << "4 - " << SEARCH_BY_TITLE << endl;
		cout << "5 - " << SEARCH_BY_ARTIST << endl;
		cout << "6 - " << EXIT << endl;
		cout << "\nOpcao: ";

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
		case 4:
			searchByName();
			break;
		case 5:
			searchByArtist();
			break;
		default:
			break;
		}

		cout << endl;
	} while (choosen != 6);

	return 0;
}

void PlayList::showTitle(const string& title)
{
	cout << "\n>> " << title << "\n\n";
}

void PlayList::createPlaylist()
{
	showTitle(CREATE_PLAYLIST);

	string path;

	cout << "\t" << DIRETORY << ": ";
	getline(cin, path);

	cout << endl;

	if (!Utils::exists(path)) {
		cout << "\t" << DIRECTORY_NOT_FOUND << endl;
		return;
	}

	clearFiles();
	Musica::resetQuantidadeMusicas();

	auto musicFiles = extractMusic(path);
	vector<Indice> indiceMusicas;
	vector<Indice> indiceArtistas;

	if (musicFiles.empty()) {
		cout << "\t" << NO_SONGS_FOUND << endl;
		return;
	}
	
	for (unsigned int index = 0; index < musicFiles.size(); index++) {
		auto m = musicFiles.at(index);

		arquivoMusica.escrever(m);
		indiceArtistas.emplace_back(Indice(m.getArtista(), index));
		indiceMusicas.emplace_back(Indice(m.getTitulo(), index));
	}

	generateIndexes(indiceMusicas, indiceArtistas);

	cout << "\t" << PLAYLIST_CREATED_WITH << " " << Musica::getQuantidadeMusicas() << " " << MUSIC_S << endl;
	cout << "\t" << INDEX_FILES_CREATED << endl;
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
			auto data = StringUtils::tokenize(f, '-', true);

			if (data.size() == 2)
				music.emplace_back(Musica(data[1], data[0]));
		}
	}

	return music;
}

void PlayList::displayOrdered(string message, bool(*sorted)(Musica, Musica))
{
	auto music = arquivoMusica.readAll();

	sort(music.begin(), music.end(), sorted);

	cout << "\t" << message << endl;
	cout << "\t" << NUMBER_OF_MUSIC << music.size() << endl << endl;

	for (unsigned int i = 0; i < music.size(); i++) {
		cout << "\t" << i + 1 << ". ";

		if (message == PLAYLIST_ORDERED_BY_ARTIST)
		{
			cout << music.at(i).displayByArtist() << endl;
			continue;
		}

		cout << music.at(i).toString() << endl;
	}
}

void PlayList::displayByMusicName()
{
	showTitle(DISPLAY_BY_MUSIC_NAME);

	displayOrdered(PLAYLIST_ORDERED_BY_MUSIC_NAME, Musica::compareTitleAndArtist);
}

void PlayList::displayByArtist()
{
	showTitle(DISPLAY_BY_ARTIST);

	displayOrdered(PLAYLIST_ORDERED_BY_ARTIST, Musica::compareArtistAndTitle);
}

void PlayList::searchByName()
{
	showTitle(SEARCH_BY_TITLE);

	string title;

	cout << "\t" << TITLE << ": ";
	getline(cin, title);

	int pos = arquivoMusica.pesquisarTituloMusica(title);

	cout << endl << "\t";

	if (pos == -1)
	{
		cout << MUSIC_NOT_FOUND << endl;
		return;
	}

	cout << (unique_ptr<Musica>(arquivoMusica.ler(pos)))->toString() << endl;
}

void PlayList::searchByArtist()
{
	showTitle(SEARCH_BY_ARTIST);

	string name;
	cout << "\t" << ARTIST << ": ";
	getline(cin, name);

	int pos = arquivoIndiceArtista.pesquisarChave(&name);

	cout << endl;

	if (pos == -1)
	{
		cout << "\t" << ARTIST_NOT_FOUND << endl;
		return;
	}

	while (pos != -1) {
		cout << "\t" << (unique_ptr<Musica>(arquivoMusica.ler(pos)))->displayByArtist() << endl;
		pos = arquivoIndiceArtista.pesquisarChave(NULL);
	}
}