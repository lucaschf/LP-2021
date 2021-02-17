#include "State.h"


State::State(string name, string initials, Region region)
{
	this->name = name;
	this->initials = initials;
	this->region = region;
}

string State::getName()
{
	return this->name;
}

string State::getInitials()
{
	return this->initials;
}

string State::getDisplayName()
{
	return getName() + " (" + getInitials() + ")";
}

Region State::getRegion()
{
	return region;
}
