#include "CalculoInvestimentos.h"
#include "ArquivoTexto.h"
#include "Constantes.h"
#include "InvestimentoFactory.h"
#include "StringUtils.h"

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

	for (int i = 0; i < data.size(); i++) {
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
				StringUtils::toDouble(tokens.at(5)), // valor investido
				StringUtils::toDouble(tokens.at(6)), // taxa
				tokens.at(7), // data investimento
				tokens.at(8) // data resgate
			);

			// força uma validacao das datas.
			StringUtils::toTime(i->getDataInvestimento(), 0);
			StringUtils::toTime(i->getDataResgate(), 1);

			investimentos.emplace_back(i);
		}
		catch (string s) {
			clearInvestimentos();
			throw s + " - " + LINHA + ": " + to_string(i + 1);
		}
	}
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

vector<string> CalculoInvestimentos::relatorioPorTipoInvestimento()
{
	vector<string> report;

	auto comparator = [](Investimento* i, Investimento* another) {
		return i->getType().compare(another->getType()) < 0;
	};

	sort(investimentos.begin(), investimentos.end(), comparator);

	for (auto investiment : investimentos) {
		report.emplace_back("- " + investiment->toSring());
		report.emplace_back("\n\nValor investido:\tR$ " + StringUtils::toStringWithPrecision(investiment->getValorInvestido()));
		report.emplace_back("\nTaxa ao ano:\t" + StringUtils::toStringWithPrecision(investiment->getTaxa()) +"% a.a.");
		report.emplace_back("\nTaxa ao mês:\t" + StringUtils::toStringWithPrecision(investiment->getTaxaMensal() * 100.0) + "% a.m.");
		report.emplace_back("\nData do investimento:\t" + investiment->getDataInvestimento());
		report.emplace_back("\nData de resgate:\t" + investiment->getDataResgate());
		report.emplace_back("\nValor bruto:\t" + StringUtils::toStringWithPrecision(investiment->calculaValorRendimentoBruto()));
		report.emplace_back("\nValor líquido:\t" + StringUtils::toStringWithPrecision(investiment->calculaValorLiquidoCumulativo()));
		report.emplace_back("\nAliquota de IR:\t" + StringUtils::toStringWithPrecision(investiment->getAliquota()) + "%");
		report.emplace_back("\nValor do IR:\t" + StringUtils::toStringWithPrecision(investiment->calcularIR()));
		report.emplace_back("\n\n");

	}

	return report;
}


