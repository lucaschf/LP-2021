// Implementa os servi�os da classe ArquivoTexto.
#include <iostream>
#include <cstring>
#include "ArquivoTexto.h"

// Fecha o arquivo texto antes do objeto ser removido da mem�ria.
ArquivoTexto::~ArquivoTexto() {
	fechar();
}

// Obt�m o nome do arquivo texto.
string ArquivoTexto::getNomeArquivo() {
	return nomeArquivo;
}

/* Abre um arquivo texto identificado por nomeArquivo. O modo de abertura do arquivo deve ser especificado por
   uma das constantes de TipoDeAcesso. Se o arquivo n�o existir ele ser� criado.
   Se o modo for ESCRITA e o arquivo j� existir em disco, todo o seu conte�do ser� exclu�do.
   Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool ArquivoTexto::abrir(string nomeArquivo, TipoDeAcesso tipoDeAcesso) {
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

/* Escreve o conte�do do objeto string no arquivo texto .
   A escrita sempre ocorre no fim do arquivo.
   Retorna true se a opera��o foi realizada com sucesso e false caso contr�rio.
*/
bool ArquivoTexto::escrever(string conteudo) {
	// Verifica se o arquivo est� aberto. 
	if (outputFile.is_open()) {
		// Posiciona o ponteiro no fim do arquivo e escreve o conte�do.
		outputFile.seekp(0, ios::end);
		outputFile << conteudo << endl;
		return true;
	}
	return false;
}

/* L� o conte�do do arquivo texto.
   Retorna um ponteiro para o objeto string com todo o conte�do do arquivo texto.
   Se o arquivo n�o estiver aberto retorna nullptr.
*/
string* ArquivoTexto::ler() {
	char linha[TAMANHO_LINHA];

	// Se o arquivo n�o estiver aberto retorna nullptr. 
	if (!inputFile) return nullptr;

	// L� o conte�do do arquivo at� atingir o fim do arquivo.
	do { // L� o conte�do de uma linha limitada a TAMANHO_LINHA caracteres ou at� encontrar o caractere nova linha ('\n'). 
		inputFile.getline(linha, TAMANHO_LINHA);

		// Verifica se atingiu o fim do arquivo. Se n�o atingiu armazena as linhas lidas do texto em um objeto string.
		if (!inputFile.eof()) {
			texto.append(linha);
			texto.append("\n");
		}
	} while (!inputFile.eof());
	// Cria um objeto string e inicializa-o com as linhas do texto.
	return new string(texto);
}

/* L� o conte�do de uma linha de texto. A primeira linha de texto � de n�mero zero (0).
   Retorna um ponteiro para o objeto string com o conte�do da linha de texto.
   Se o arquivo n�o estiver aberto retorna nullptr.

   ATEN��O: Este m�todo s� ir� recuperar a linha de texto correta do arquivo se todas
			as linhas de texto possu�rem o mesmo comprimento em bytes.
*/
string* ArquivoTexto::ler(int numeroLinha) {
	char linha[TAMANHO_LINHA] = "";

	// Se o arquivo n�o estiver aberto retorna nullptr. 
	if (!inputFile) return nullptr;

	// L� o conte�do do arquivo at� atingir o fim do arquivo.
	if (numeroLinha >= 0) {
		inputFile.seekg(numeroLinha);
		inputFile.getline(linha, TAMANHO_LINHA);
	}
	// Cria um objeto string e inicializa-o com o conte�do da linha.
	return new string(linha);
}

// Fecha o arquivo texto.
void ArquivoTexto::fechar() {
	// Verifica se o arquivo est� aberto.
	if (inputFile.is_open()) inputFile.close();
	if (outputFile.is_open()) outputFile.close();

	// Apaga o conte�do do texto.
	texto.clear();
}

vector<string> ArquivoTexto::readAll()
{
	vector<string> lines;

	if (!inputFile)
		return lines;

	inputFile.seekg(0);

	string line;
	while (getline(inputFile, line)) {
		lines.emplace_back(line);
	}

	return lines;
}
