#ifndef ARQUIVO_TEXTO
#define ARQUIVO_TEXTO

#include <fstream>
#include <string>
#include <vector>

using namespace std;

/* Define os tipos de acesso que podem ser usados para acessar o arquivo. Os modos dispon�veis s�o:

   ACRESCENTAR: abre o arquivo apenas para acrescentar dados no fim do arquivo;
   ESCRITA: abre o arquivo apenas para a escrita de dados;
   LEITURA: abre o arquivo apenas para a leitura de dados.
*/
enum class TipoDeAcesso { ACRESCENTAR, ESCRITA, LEITURA };

// A letra L mai�scula � usada para definir uma string literal do tipo wstring.
const wstring NOVA_LINHA = L"\n";

/*
	Esta classe fornece os m�todos b�sicos para manipular um arquivo texto.
*/
class ArquivoTexto {
public: 
	ArquivoTexto() = default;

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

	/* Escreve no arquivo texto o conte�do do objeto string usando a codifica��o UTF-8.
       A escrita sempre ocorre no fim do arquivo.
       Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
     */
	bool escrever(wstring conteudo);

	/* Escreve no arquivo texto o conte�do do objeto string usando a codifica��o UTF-8.
       A escrita sempre ocorre no fim do arquivo.
       Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
     */
	bool escrever(string str);

	/* Escreve no arquivo texto o conte�do do objeto string usando a codifica��o especificada, p. ex., ".1252".
	   A escrita sempre ocorre no fim do arquivo.
	   Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
	 */
	bool escrever(wstring conteudo, const char* codificacao);

	/* L� o conte�do do arquivo texto usando a codifica��o UTF-8.
	   Retorna uma string com todo o conte�do do arquivo texto.
	 */
	wstring ler();

	/* L� o conte�do do arquivo texto usando a codifica��o especificada, p. ex., ".1252".
	   Retorna uma string com todo o conte�do do arquivo texto.
	 */
	wstring ler(const char* codificacao);

	/* L� o conte�do de uma linha de texto. A primeira linha de texto � de n�mero zero (0).
	   Retorna um objeto string com o conte�do da linha de texto.
	  
	   ATEN��O: Este m�todo s� ir� recuperar a linha de texto correta do arquivo se todas as linhas possu�rem o mesmo comprimento em bytes.
	 */
	wstring ler(int numeroLinha);

	// Fecha o arquivo texto.
	void fechar();

	vector<string> readAll(const char* codificacao = ".UTF8");

private:
	string nomeArquivo;
	wstring texto;

	// Objeto para ler caracteres de 2 bytes (wchar_t), tamanho usado pelo UTF-8. 
	wifstream inputFile;  

	// Objeto para escrever caracteres de 2 bytes (wchar_t), tamanho usado pelo UTF-8. 
	wofstream outputFile;
}; 
#endif 