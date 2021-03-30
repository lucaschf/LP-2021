#ifndef TIME_DIFF_H
#define TIME_DIFF_H

#include <ctime>

class Periodo
{
public:

	Periodo();

	Periodo(time_t first, time_t second);

	Periodo(struct tm first, struct tm second);

	long int getYears();

	long int getMonths();

	long int getWorkingDays();

	time_t getBegin();

	time_t getEnd();

private:

	time_t first;
	time_t second;

	long int years;
	long int months;
	long int workingDays;

	void calculateDiff();
};
#endif // !TIME_DIFF_H