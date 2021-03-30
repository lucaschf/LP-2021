// Esta classe fornece os métodos básicos para manipular um arquivo texto em disco.
#ifndef ARQUIVO_TEXTO
#define ARQUIVO_TEXTO

#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Define os tipos de acesso que podem ser usados para acessar o arquivo. Os modos disponíveis são:

   ACRESCENTAR: abre o arquivo somente para acrescentar dados no fim do arquivo;
   ESCRITA: abre o arquivo somente para a escrita de dados;
   LEITURA: abre o arquivo somente para a leitura de seu conteúdo.
*/
enum class TipoDeAcesso { ACRESCENTAR, ESCRITA, LEITURA };

const unsigned char TAMANHO_LINHA = 180;

class ArquivoTexto {
public: 
	// Fecha o arquivo texto antes do objeto ser removido da memória.
	virtual ~ArquivoTexto();

	// Obtém o nome do arquivo texto.
	string getNomeArquivo();

	/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por 
	   uma das constantes de TipoDeAcesso. Se o arquivo não existir ele será criado. 
	   Se o modo for ESCRITA e o arquivo já existir em disco, todo o seu conteúdo será excluído.
	   Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	 */
	bool abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso);

	/* Escreve o conteúdo do objeto string no arquivo texto.
	   A escrita sempre ocorre no fim do arquivo.
	   Retorna true se a operação foi realizada com sucesso e false caso contrário.
	 */
	bool escrever(string conteudo);

	/* Lê o conteúdo do arquivo texto.
	   Retorna um ponteiro para o objeto string com todo o conteúdo do arquivo texto.
	   Se o arquivo não estiver aberto retorna nullptr.
	 */
	string* ler();

	/* Lê o conteúdo de uma linha de texto. A primeira linha de texto é de número zero (0).
	   Retorna um ponteiro para o objeto string com o conteúdo da linha de texto.
	   Se o arquivo não estiver aberto retorna nullptr.
	  
	   ATENÇÃO: Este método só irá recuperar a linha de texto correta do arquivo se todas  
	            as linhas de texto possuírem o mesmo comprimento em bytes.
	 */
	string* ler(int numeroLinha);

	// Fecha o arquivo texto.
	void fechar();

	vector<string> readAll();

private:
	string nomeArquivo, texto;
	ifstream inputFile;
	ofstream outputFile;
}; 
#endif 