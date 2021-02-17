#include <iostream>

#include<string.h>
#include <map>
#include "State.h"

using namespace std;


enum class FederativeUnits {
	AM, RR, AP, PA, TO, RO, AC, // North
	MA, PI, CE, RN, PE, PB, SE, AL, BA, // NorthEast
	MT, MS, GO, // Midwest
	SP, RJ, ES, MG, // Southeast
	PR, RS, SC // South
};

void enumerations() {

	setlocale(LC_ALL, "");

	string regions[] = {
		"Norte",
		"Nordeste",
		"Centro-Oeste",
		"Sudeste",
		"Sul"
	};

	map<FederativeUnits, State*> states = {
		// North
		{FederativeUnits::AM, new State("Amazonas", "AM", Region::NORTH)},
		{FederativeUnits::RR, new State("Roraima", "RR", Region::NORTH)},
		{FederativeUnits::AP, new State("Amapá", "AP", Region::NORTH)},
		{FederativeUnits::PA, new State("Pará", "PA", Region::NORTH)},
		{FederativeUnits::TO, new State("Tocantins", "TO", Region::NORTH)},
		{FederativeUnits::RO, new State("Rondônia", "RO", Region::NORTH)},
		{FederativeUnits::AC, new State("Acre", "AC", Region::NORTH)},
		// NorthEast
		{FederativeUnits::MA, new State("Maranhão ", "MA", Region::NORTH_EAST)},
		{FederativeUnits::PI, new State("Piauí", "PI", Region::NORTH_EAST)},
		{FederativeUnits::CE, new State("Ceará ", "CE", Region::NORTH_EAST)},
		{FederativeUnits::RN, new State("Rio Grande do Norte", "RN", Region::NORTH_EAST)},
		{FederativeUnits::PE, new State("Pernambuco", "PE", Region::NORTH_EAST)},
		{FederativeUnits::PB, new State("Paraíba", "PB", Region::NORTH_EAST)},
		{FederativeUnits::SE, new State("Sergipe", "SE", Region::NORTH_EAST)},
		{FederativeUnits::AL, new State("Alagoas", "AL", Region::NORTH_EAST)},
		{FederativeUnits::BA, new State("Bahia", "BA", Region::NORTH_EAST)},
		// Midwest
		{FederativeUnits::MT, new State("Mato Grosso", "MT", Region::MIDWEST)},
		{FederativeUnits::MS, new State("Mato Grosso do Sul", "MS", Region::MIDWEST)},
		{FederativeUnits::GO, new State("Goiás", "GO", Region::MIDWEST)},
		// Southeast
		{FederativeUnits::SP, new State("São Paulo", "SP", Region::SOUTHEAST)},
		{FederativeUnits::RJ, new State("Rio de Janeiro", "RJ", Region::SOUTHEAST)},
		{FederativeUnits::ES, new State("Espírito Santo", "ES", Region::SOUTHEAST)},
		{FederativeUnits::MG, new State("Minas Gerais", "MG", Region::SOUTHEAST)},
		// South
		{FederativeUnits::PR, new State("Paraná", "PR", Region::SOUTH)},
		{FederativeUnits::RS, new State("Rio Grande do Sul", "RS", Region::SOUTH)},
		{FederativeUnits::SC, new State("Santa Catarina", "SC", Region::SOUTH)},
	};

	Region displayingRegion = Region::SOUTH;

	const string spaces = "\t";

	for (FederativeUnits uf = FederativeUnits::AM; uf <= FederativeUnits::SC; uf = static_cast<FederativeUnits>(static_cast<int>(uf) + 1))
	{
		auto state = states[uf];
		if (state->getRegion() != displayingRegion) {
			displayingRegion = state->getRegion();
			cout << "\n>> regiao " << regions[static_cast<int>(displayingRegion)] << endl << endl;
		}

		cout << spaces << state->getDisplayName() << endl;
	}
}

int main() {
	enumerations();
	return 0;
}