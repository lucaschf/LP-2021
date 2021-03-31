#include "CalculoInvestimentos.h"
#include "ArquivoTexto.h"
#include "Constantes.h"
#include "InvestimentoFactory.h"
#include "StringUtils.h"
#include <iomanip>

void CalculoInvestimentos::obterInvestimentos(string caminhoArquivo)
{
	clearInvestimentos();

	ArquivoTexto arq;

	if (!arq.abrir(caminhoArquivo, TipoDeAcesso::LEITURA))
		throw INCAPAZ_DE_ABRIR_ARQUIVO;

	auto data = arq.readAll();
	arq.fechar();

	if (data.empty())
		throw ARQUIVO_DE_DADOS_VAZIO;

	for (unsigned int i = 0; i < data.size(); i++) {
		auto line = data.at(i);

		auto tokens = StringUtils::tokenize(line, ';', true);
		if (tokens.size() != 9) {
			clearInvestimentos();
			throw string("Dados invalidos na linha: " + to_string(i + 1));
		}

		try {
			auto i = InvestimentoFactory::create(
				tokens.at(0), // tipo
				tokens.at(2), // nome
				tokens.at(3), // rating
				StringUtils::equalsIgnoreCase(tokens.at(4), "sim"), // fgc
				Estrategia::from(tokens.at(1)), // estrategia
				StringUtils::toFloat(tokens.at(5)), // valor investido
				StringUtils::toFloat(tokens.at(6)), // taxa
				tokens.at(7), // data investimento
				tokens.at(8) // data resgate
			);

			// força uma validacao das datas.
			StringUtils::toTime(i->getDataInvestimento());
			StringUtils::toTime(i->getDataResgate());

			investimentos.emplace_back(i);
		}
		catch (string s) {
			clearInvestimentos();
			throw s + " - " + LINHA + ": " + to_string(i + 1);
		}
	}
}

void CalculoInvestimentos::relatorioPorTipoInvestimento()
{
	ArquivoTexto arq;

	if (investimentos.empty())
		throw string("Nenhum dado encontrado");

	if (!arq.abrir("Investimentos.rel", TipoDeAcesso::ESCRITA)) {
		throw string("Falha ao gerar arquivo de relatório");
	}

	auto comparator = [](Investimento* i, Investimento* another) {
		return i->getType().compare(another->getType()) < 0;
	};

	sort(investimentos.begin(), investimentos.end(), comparator);

	string strReport;

	int i = 0;
	string type = "";

	for (auto investiment : investimentos) {
		auto t = investiment->getType();

		if (t != type) {
			type = t;
			strReport.append("\n" + to_string(++i) + ". Renda: " + (t == "RF" ? "Fixa" : "Variável") + "\n\n");
		}

		strReport.append("- " + investiment->toSring() + "\n")
			.append(
				StringUtils::toRow(
					"\n\tValor investido:",
					StringUtils::toBrazilianCurrency(investiment->getValorInvestido()))
			)
			.append(
				StringUtils::toRow(
					"\n\tTaxa ao ano:",
					StringUtils::toPercentageString(investiment->getTaxa()) + " a.a.")
			)
			.append(
				StringUtils::toRow(
					"\n\tTaxa ao mês:",
					StringUtils::toPercentageString(investiment->getTaxaMensal() * 100.0) + " a.m.")
			)
			.append(
				StringUtils::toRow(
					"\n\tData do investimento:",
					investiment->getDataInvestimento())
			)
			.append(
				StringUtils::toRow(
					"\n\tData de resgate:",
					investiment->getDataResgate())
			)
			.append(StringUtils::toRow(
				"\n\tValor bruto:",
				StringUtils::toBrazilianCurrency(investiment->calculaValorRendimentoBruto()))
			)
			.append(
				StringUtils::toRow(
					"\n\tValor líquido:",
					StringUtils::toBrazilianCurrency(investiment->calculaValorLiquidoCumulativo()))
			)
			.append(
				StringUtils::toRow(
					"\n\tAliquota de IR:",
					StringUtils::toPercentageString(investiment->getAliquota()))
			)
			.append(
				StringUtils::toRow(
					"\n\tValor do IR:",
					StringUtils::toBrazilianCurrency(investiment->calcularIR()))
			)
			.append(
				StringUtils::toRow(
					"\n\tRendimento bruto:",
					StringUtils::toBrazilianCurrency(investiment->getRendaBrutaCumulativa()))
			)
			.append(
				StringUtils::toRow(
					"\n\tRendimento líquido:",
					StringUtils::toBrazilianCurrency(investiment->getRendaLiquidaCumulativa())
				)
			).append("\n\n");
	}

	auto success = arq.escrever(strReport);
	arq.fechar();

	if (!success)
		throw("Falha ao gravar dados");
}

void CalculoInvestimentos::relatorioPorEstrategia()
{
	auto comparator = [](Investimento* i, Investimento* another) {
		return i->getEstrategia().getEstrategia() < another->getEstrategia().getEstrategia();
	};

	sort(investimentos.begin(), investimentos.end(), comparator);

	int width = 20;

	EstrategiaInvestimento estrategia = EstrategiaInvestimento::INFLACAO;
	int i = 0;

	for (auto investiment : investimentos) {
		auto e = investiment->getEstrategia().getEstrategia();

		if (e != estrategia || i == 0) {
			estrategia = e;
			std::cout << endl << to_string(++i) + ". Estratégia: " + Estrategia::obterEstrategia(estrategia) << endl << endl;
		}

		std::cout << "- " << investiment->getNome() << endl << endl;
		std::cout << "\t";
		std::cout << setw(width) << left << "Valor investido";
		std::cout << setw(width) << left << "Valor bruto";
		std::cout << setw(width) << left << "Valor líquido";
		std::cout << setw(width) << left << "Rendimento bruto";
		std::cout << setw(width) << left << "Rentabilidade\n";
		std::cout << "\t";
		std::cout << setw(width) << left << StringUtils::toBrazilianCurrency(investiment->getValorInvestido());
		std::cout << setw(width) << left << StringUtils::toBrazilianCurrency(investiment->calculaValorRendimentoBruto());
		std::cout << setw(width) << left << StringUtils::toBrazilianCurrency(investiment->calculaValorLiquidoCumulativo());
		std::cout << setw(width) << left << StringUtils::toBrazilianCurrency(investiment->getRendaBrutaCumulativa());
		std::cout << setw(width) << left << StringUtils::toPercentageString(investiment->getRentabilidadeToDisplay());
		std::cout << endl << endl;
	}
}

int CalculoInvestimentos::menu()
{
	int choice;

	do {
		cout << "Cálculo de investimentos ========= \n\n";
		string strChoice;
		cout << "1. Importar dados\n2. Relatorio por tipo\n3. Relatório por estratégia\n4. Sair\n\nOpção: ";

		getline(cin, strChoice);

		choice = atoi(strChoice.c_str());

		switch (choice)
		{
		case 1:
			importaDados();
			break;

		case 2:
			cout << "\nRelatório de investimentos por tipo >>\n\n";
			try {
				relatorioPorTipoInvestimento();
				cout << "Relatorio gerado com sucesso.\n\n";
			}
			catch (string ex) {
				cout << ex << endl << endl;
			}
			break;

		case 3:
			cout << "\nRelatório de investimentos por estratégia >>\n\n";
			if (investimentos.empty()) {
				cout << "Nenhum dado encontrado\n\n";
			}
			else
				relatorioPorEstrategia();
			break;
		default:
			cout << "\n";
			break;
		}
	} while (choice != 4);

	return 0;
}

CalculoInvestimentos::~CalculoInvestimentos()
{
	clearInvestimentos();
}

void CalculoInvestimentos::clearInvestimentos()
{
	for (auto i : investimentos) {
		delete i;
	}

	investimentos.clear();
}

void CalculoInvestimentos::importaDados()
{
	string path;

	cout << "\nImportação de dados >> \n";

	do {
		cout << endl << "Caminho do arquivo de investimentos: ";

		getline(cin, path);

		try {
			obterInvestimentos(path);
			cout << endl << investimentos.size() << " investimentos importados\n\n";
		}
		catch (string ex) {
			cout << endl << "Falha na importação: " <<    ex << endl << endl;
		}
	} while (path.empty());
}

int main() {
	setlocale(LC_ALL, "pt-Br");
	return CalculoInvestimentos().menu();
}