#ifndef ARQUIVO_BINARIO
#define ARQUIVO_BINARIO

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ArquivoBinario {

public:

	~ArquivoBinario();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	Se o arquivo nao existir ele sera criado.
	Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	*/
	bool abrir(const string& nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obtem o nome do arquivo.
	string getNomeArquivo();

	// Obtem o tamanho do arquivo em bytes.
	unsigned long tamanho();

	/**
	 * Counts the number of records in the file.
	 *
	 * @tparam T the record type.
	 * @return the number of records in the file
	 */
	template<typename T>
	inline unsigned int countRegisters() {
		return tamanho() / sizeof(T);
	}

	/**
	 * Writes a record to the file.
	 *
	 * @tparam T the record type.
	 * @param obj the record to be written.
	 * @return true if successful false if failed.
	 */
	template<typename T>
	inline bool writeInto(T obj) {
		arquivoBinario.seekp(0, ios::end);
		if (arquivoBinario.write(reinterpret_cast<char*>(std::addressof(obj)), sizeof(T)))
			return true;

		return false;
	}

	/**
	 * Reads a record of the file and store it in the variable referenced by obj.
	 *
	 * @tparam T the record type.
	 * @param obj reference of a type T variable where the read register will be storing.
	 * @return true if successful false if failed.
	 */
	template<typename T>
	inline bool read(T& obj, unsigned int position) {
		unsigned int count = countRegisters<T>();

		if (count >= 0 && position < count) {
			auto p = position * sizeof(T);

			arquivoBinario.seekg(p, ios::beg);

			if (arquivoBinario.read(reinterpret_cast<char*>(std::addressof(obj)), sizeof(T)))
				return true;
		}

		return false;
	}

	/**
	 * Reads all records from the file and store in the variable referenced by all.
	 *
	 * @tparam T the record type.
	 * @param all reference of a vector where the registers will be stored.
	 */
	template <typename T>
	inline vector<T> readAll() {
		T obj;
		vector<T> all;

		unsigned int count = countRegisters<T>();
		arquivoBinario.seekp(0, ios::beg);

		if (count > 0) {
			for (unsigned int i = 0; i <= count; i++)
			{
				if (read(obj, i))
					all.emplace_back(obj);
			}
		}

		return all;
	}

	/**
	 * Searches a record in the file.
	 *
	 * @tparam T the record type.
	 * @tparam Key the search key type.
	 * @param obj reference of a variable where will be stored the record, if found.
	 * @param key the search key.
	 * @param comparator pointer to the compare function.
	 * @return the position in file if found, -1 otherwise.
	 */
	template<class T, typename Key>
	inline int find(T& obj, Key key, bool(*comparator)(T, Key)) {
		if (tamanho() > 0) {
			arquivoBinario.seekg(0, ios::beg);
			int counter = 0;

			while (arquivoBinario.good()) {
				arquivoBinario.read(reinterpret_cast<char*>(std::addressof(obj)), sizeof(T));
				if (comparator(obj, key))
					return counter;

				counter++;
			}
		}

		return -1;
	}

	/*
	 * Deletes a record from the file considering zero (0) as the first position.
	 *
	 * @tparam T the record type.
	 * @param position The position of the record in the file.
	 * @return true if removed, false otherwise.
	*/
	template <typename T>
	inline bool removeAt(unsigned int position) {
		unsigned int count = tamanho();

		if (count >= 0 && position < count) {
			vector<T> all = readAll<T>();

			fechar();
			remove(getNomeArquivo().c_str());
			abrir(getNomeArquivo());

			// Copy all records from file to temporary file.
			for (unsigned int i = 0; i < all.size(); i++) {
				if (i != position)
					writeInto(all.at(i));
			}

			return true;
		}

		return false;
	}

	void clear();

private:

	fstream arquivoBinario; // Arquivo binário para escrita e leitura de dados.
	string name;
};

#endif