#include "Periodo.h"

Periodo::Periodo()
{
	first = time(NULL);
	second = time(NULL);

	calculateDiff();
}

Periodo::Periodo(time_t start, time_t end)
{
	this->first = start;
	this->second = end;

	calculateDiff();
}

Periodo::Periodo(tm first, tm second)
{
	this->first = mktime(&first);
	this->second = mktime(&second);

	calculateDiff();
}

long int Periodo::getYears()
{
	return this->years;
}

long int Periodo::getMonths()
{
	return this->months;
}

long int Periodo::getWorkingDays()
{
	return this->workingDays;
}

time_t Periodo::getBegin()
{
	return this->first;
}

time_t Periodo::getEnd()
{
	return this->second;
}

void Periodo::calculateDiff()
{
	const double t = 2628002.88;

	auto seconds = difftime(second, first);

	this->months = (long int)seconds / t;
	this->years = getMonths() / 12;
	this->workingDays = getMonths() * 21;
}
