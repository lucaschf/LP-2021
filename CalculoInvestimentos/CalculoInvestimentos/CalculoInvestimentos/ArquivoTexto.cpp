#include <iostream>
#include <locale>
#include "ArquivoTexto.h"
#include <algorithm>

// Fecha o arquivo texto antes do objeto ser removido da mem�ria.
ArquivoTexto::~ArquivoTexto() 
{
	fechar();
}

// Obt�m o nome do arquivo texto.
string ArquivoTexto::getNomeArquivo() 
{
	return nomeArquivo;
}

/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por
   uma das constantes de TipoDeAcesso. Se o arquivo n�o existir ele ser� criado.
   Se o modo for ESCRITA e o arquivo j� existir em disco, todo o seu conte�do ser� exclu�do.
   Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool ArquivoTexto::abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso) 
{
	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo segundo o modo de abertura ou tipo de acesso escolhido.
	switch (tipoDeAcesso) {
	case TipoDeAcesso::ACRESCENTAR: outputFile.open(nomeArquivo, ios::app);
								    return outputFile.is_open() ? true : false;
						   
	case TipoDeAcesso::ESCRITA: outputFile.open(nomeArquivo, ios::out);
							    return outputFile.is_open() ? true : false;

	case TipoDeAcesso::LEITURA: inputFile.open(nomeArquivo, ios::in);
								return inputFile.is_open() ? true : false;
	}
	return false;
} 

/* Escreve no arquivo texto o conte�do do objeto string usando a codifica��o UTF-8.
   A escrita sempre ocorre no fim do arquivo.
   Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
 */
bool ArquivoTexto::escrever(wstring conteudo) 
{
	return escrever(conteudo, ".UTF8");
}

bool ArquivoTexto::escrever(string str)
{
	std::wstring wstr(str.length(), L' '); // Make room for characters

   // Copy string to wstring.
	std::copy(str.begin(), str.end(), wstr.begin());

	return escrever(wstr);
}

/* Escreve no arquivo texto o conte�do do objeto string usando a codifica��o especificada, p. ex., ".1252".
   A escrita sempre ocorre no fim do arquivo.
   Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
*/
bool ArquivoTexto::escrever(wstring conteudo, const char* codificacao)
{
	// Cria um objeto locale com a codifica��o especificada.
	const locale local(codificacao);

	// Define o locale do arquivo.
	outputFile.imbue(local);

	// Verifica se o arquivo est� aberto. 
	if (outputFile.is_open())
	{
		// Posiciona o ponteiro no fim do arquivo e escreve o conte�do.
		outputFile.seekp(0, ios::end);
		outputFile << conteudo << endl;
		return true;
	}
	return false;
}

/* L� o conte�do do arquivo texto usando a codifica��o UTF-8.
   Retorna uma string com todo o conte�do do arquivo texto.
 */
wstring ArquivoTexto::ler() 
{
	return ler(".UTF8");
}


/* L� o conte�do do arquivo texto usando a codifica��o especificada.
   Retorna uma string com todo o conte�do do arquivo texto.
*/
wstring ArquivoTexto::ler(const char* codificacao) 
{
	wstring linha;
	
	// Cria um objeto locale com a codifica��o especificada.
	const locale local(codificacao);

	// Define o locale do arquivo.
	inputFile.imbue(local);

	// L� o conte�do do arquivo at� atingir o fim do arquivo.
	do { // L� o conte�do de uma linha do arquivo at� encontrar o caractere nova linha ('\n'). 
		getline(inputFile, linha);

	     // Verifica se atingiu o fim do arquivo. Se n�o atingiu armazena as linhas lidas do texto em um objeto string.
		 if (!inputFile.eof()) 
		 {
			 texto.append(linha);
			 texto.append(NOVA_LINHA);
		 }
	} while (!inputFile.eof());

	// Cria um objeto string e inicializa-o com as linhas do texto.
   return texto;
} 

/* L� o conte�do de uma linha de texto. A primeira linha de texto � de n�mero zero (0).
   Retorna um objeto string com o conte�do da linha de texto.

   ATEN��O: Este m�todo s� ir� recuperar a linha de texto correta do arquivo se todas as linhas possu�rem o mesmo comprimento em bytes.
 */
wstring ArquivoTexto::ler(int numeroLinha) 
{
	wstring linha;

	// L� o conte�do do arquivo at� atingir o fim do arquivo.
	if (numeroLinha >= 0) 
	{
		inputFile.seekg(numeroLinha);
		getline(inputFile, linha);
	}

	// Cria um objeto string e inicializa-o com o conte�do da linha.
	return linha;
} 

// Fecha o arquivo texto.
void ArquivoTexto::fechar() 
{
	// Verifica se o arquivo est� aberto.
	if (inputFile.is_open()) inputFile.close();
	if (outputFile.is_open()) outputFile.close();

	// Apaga o conte�do do texto.
	texto.clear();
}

vector<string> ArquivoTexto::readAll(const char* codificacao)
{
	vector<string> lines;

	if (!inputFile)
		return lines;

	// Cria um objeto locale com a codifica��o especificada.
	const locale local(codificacao);

	// Define o locale do arquivo. 
	inputFile.imbue(local);

	inputFile.seekg(0);

	wstring line;
	while (getline(inputFile, line)) {
		lines.emplace_back(string().append(line.begin(), line.end()));
	}

	return lines;
}