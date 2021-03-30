// Esta classe fornece os m�todos b�sicos para manipular um arquivo texto em disco.
#ifndef ARQUIVO_TEXTO
#define ARQUIVO_TEXTO

#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Define os tipos de acesso que podem ser usados para acessar o arquivo. Os modos dispon�veis s�o:

   ACRESCENTAR: abre o arquivo somente para acrescentar dados no fim do arquivo;
   ESCRITA: abre o arquivo somente para a escrita de dados;
   LEITURA: abre o arquivo somente para a leitura de seu conte�do.
*/
enum class TipoDeAcesso { ACRESCENTAR, ESCRITA, LEITURA };

const unsigned char TAMANHO_LINHA = 180;

class ArquivoTexto {
public: 
	// Fecha o arquivo texto antes do objeto ser removido da mem�ria.
	virtual ~ArquivoTexto();

	// Obt�m o nome do arquivo texto.
	string getNomeArquivo();

	/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por 
	   uma das constantes de TipoDeAcesso. Se o arquivo n�o existir ele ser� criado. 
	   Se o modo for ESCRITA e o arquivo j� existir em disco, todo o seu conte�do ser� exclu�do.
	   Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	 */
	bool abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso);

	/* Escreve o conte�do do objeto string no arquivo texto.
	   A escrita sempre ocorre no fim do arquivo.
	   Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
	 */
	bool escrever(string conteudo);

	/* L� o conte�do do arquivo texto.
	   Retorna um ponteiro para o objeto string com todo o conte�do do arquivo texto.
	   Se o arquivo n�o estiver aberto retorna nullptr.
	 */
	string* ler();

	/* L� o conte�do de uma linha de texto. A primeira linha de texto � de n�mero zero (0).
	   Retorna um ponteiro para o objeto string com o conte�do da linha de texto.
	   Se o arquivo n�o estiver aberto retorna nullptr.
	  
	   ATEN��O: Este m�todo s� ir� recuperar a linha de texto correta do arquivo se todas  
	            as linhas de texto possu�rem o mesmo comprimento em bytes.
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