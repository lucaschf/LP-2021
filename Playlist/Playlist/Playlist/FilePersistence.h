#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include "ArquivoBinario.h"
#include "Utils.h"

using namespace std;

template <class T, typename StructType>
class FilePersistence {
public:

	// Obtém o tamanho do registro em bytes.
	inline size_t tamanhoRegistro() {
		return sizeof(StructType);
	}

	/*
	*   Lê os dados de um registro do arquivo e armazena-os no objeto T.
	*   Retorna o objeto T, e em caso de erro nullptr.
	*/
	inline T* ler(unsigned int numeroRegistro) {
		StructType stct;

		if (file->read(stct, numeroRegistro))
			return fromStruct(stct);

		return nullptr;
	}

	/*
	* Lê todos os itens do arquivo
	*/
	inline vector<T> readAll() {
		vector<T> all;

		for (const StructType& obj : file->readAll<StructType>()) {
			all.emplace_back((*(fromStruct(obj))));
		}

		return all;
	}

	// Obtem o nome do arquivo
	inline string getNomeArquivo() {
		return file->getNomeArquivo();
	}

	// Fecha o arquivo
	inline void fechar() {
		file->fechar();
	}

	/*
	*	Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	*	Retorna true se o arquivo foi aberto com sucesso e false caso contrario.
	*/
	inline bool abrir(const string& nomeArquivo) {
		return file->abrir(nomeArquivo);
	}

	// Escreve o objeto T como um registro do arquivo.
	inline void escrever(T obj) {
		file->writeInto(toStruct(obj));
	}

	// Obtem o numero de registros do arquivo
	inline unsigned int numeroRegistros() {
		return file->tamanho() / tamanhoRegistro();
	}

	template<class Key>
	int find(T& obj, Key key, bool (*compare)(T, Key)) {
		for (unsigned int i = 0; i <= numeroRegistros(); i++) {
			auto result = unique_ptr<T>(ler(i));

			if (result != nullptr && compare((*result), key)) {
				obj = (*result);
				return (int)i;
			}
		}

		return -1;
	}

	/**
	 * Searches a record in the file.
	 *
	 * @tparam Key the search key type.
	 * @param obj reference of a variable where will be stored the record, if found.
	 * @param key the pointer to the search key.
	 * @param comparator pointer to the compare function.
	 * @return the position in file if found, -1 otherwise.
	 */
	template<class Key>
	int findInSequence(T& obj, Key* key, bool(*comparator)(T, Key)) {
		static unsigned int index;
		static Key k;

		if (key != nullptr) {
			index = 0;
			k = (*key);
		}

		for (; index <= numeroRegistros(); index++) {
			auto result = unique_ptr<T>(ler(index));

			if (result != nullptr && comparator((*result), k)) {
				obj = (*result);
				return (int)index++;
			}
		}

		return -1;
	}

	/**
	 * Searches a record in the file.
	 *
	 * @tparam Key the search key type.
	 * @param obj reference of a variable where will be stored the record, if found.
	 * @param key the pointer to the search key.
	 * @param comparator pointer to the compare function.
	 * @return the position in file if found, -1 otherwise.
	 */
	template<class Key>
	T* findInSequentially(T& obj, Key* key, bool(*comparator)(T, Key)) {
		static vector<T> records;

		if (key != nullptr) {
			records = readAll();
		}
	
		auto r = Utils::findInVectorSequentially(records, key, comparator);

		if (r.first) {
			return &records.at(r.second);
		}

		return nullptr;
	}

	template<class Key, class Key2>
	int find(T& obj, Key key, Key2 anotherKey, bool (*compare)(T, Key, Key2)) {
		for (int i = 0; i < numeroRegistros(); i++) {
			auto result = unique_ptr<T>(ler(i));

			if (result != nullptr && compare(obj, key, anotherKey)) {
				obj = (*result);
				return i;
			}
		}

		return -1;
	}

	inline void clear() {
		file->clear();
	}

	// Exclui o objeto arquivo binario
	~FilePersistence() {
		cout << "Deleting file pointer: " << file->getNomeArquivo() << endl;
		delete file;
	}

protected:

	ArquivoBinario* file = new ArquivoBinario();

	inline bool initializeFile(const string& fileName) {
		file = new ArquivoBinario();
		return file->abrir(fileName);
	}

	// 
	virtual StructType toStruct(T obj) = 0;

	virtual T* fromStruct(const StructType& stct) = 0;
};

#endif // !PERSISTENCE_H