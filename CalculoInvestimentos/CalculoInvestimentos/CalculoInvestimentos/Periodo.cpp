#include "Periodo.h"

Periodo::Periodo()
{
	first = time(NULL);
	second = time(NULL);
	this->second += 24 * 3600; // forces second date to be ahead one day 

	calculateDiff();
}

Periodo::Periodo(time_t start, time_t end)
{
	this->first = start;
	this->second = end;
	this->second += 24 * 3600; // forces second date to be ahead one day 

	calculateDiff();
}

Periodo::Periodo(tm first, tm second)
{
	this->first = mktime(&first);
	this->second = mktime(&second);
	this->second += 24 * 3600; // forces second date to be ahead one day 

	calculateDiff();
}

short Periodo::getYears()
{
	return this->years;
}

short Periodo::getMonths()
{
	return this->months;
}

short Periodo::getWorkingDays()
{
	return this->workingDays;
}

time_t Periodo::getBegin()
{
	return this->first;
}

time_t Periodo::getEnd()
{
	return this->second - 24 * 3600;
}

void Periodo::calculateDiff()
{
	const double t = 2628002.88;

	auto seconds = difftime(second, first);

	this->months = (int)(seconds / t);
	this->years = getMonths() / 12;
	this->workingDays = getMonths() * 21;
}
