#pragma once
#include <string>

using namespace std;

enum class Region {
	NORTH,
	NORTH_EAST,
	MIDWEST,
	SOUTHEAST,
	SOUTH
};

class State
{
public:

	State(string name, string initials, Region region);

	string getName();

	string getInitials();

	string getDisplayName();

	Region getRegion();

private:

	string name;
	string initials;
	Region region;
};

