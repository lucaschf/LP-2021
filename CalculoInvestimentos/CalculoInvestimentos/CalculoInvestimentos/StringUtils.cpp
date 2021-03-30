#include "StringUtils.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include <atlconv.h>

#pragma warning(disable : 4996)

bool StringUtils::endsWithIgnoreCase(string const& str, string const& suffix)
{
	if (endsWith(str, suffix))
		return true;

	return endsWith(toUpperCase(str), toUpperCase(suffix));
}

bool StringUtils::endsWith(string const& str, string const& suffix) {
	if (suffix.size() > str.size())
		return false;

	return equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

bool StringUtils::startsWith(string const& str, string const& prefix)
{
	return str.rfind(prefix, 0) == 0;
}

bool StringUtils::contains(string const& str, string const& s) {
	return str.find(s) != string::npos;
}

bool StringUtils::containsIgnoreCase(string const& str, string const& s)
{
	if (contains(str, s))
		return true;

	return contains(toUpperCase(str), toUpperCase(s));
}

bool StringUtils::equalsIgnoreCase(string const& str, string const& s)
{
	return toUpperCase(str) == toUpperCase(s);
}

bool StringUtils::isOnlyDigit(const string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}

string& StringUtils::replaceAll(string& source, const string& from, const string& to)
{
	string newString;
	newString.reserve(source.length());  // avoids a few memory allocations

	string::size_type lastPos = 0;
	string::size_type findPos;

	if (from == to)
		return source;

	while (std::string::npos != (findPos = source.find(from, lastPos)))
	{
		newString.append(source, lastPos, findPos - lastPos);
		newString += to;
		lastPos = findPos + from.length();
	}

	// Care for the rest after last occurrence
	newString += source.substr(lastPos);

	if (contains(newString, from))
		source = replaceAll(newString, from, to);

	source.swap(newString);

	return source;
}

string StringUtils::toUpperCase(const string& str)
{
	string strCopy = string(str);

	for (auto& c : strCopy) c = toupper(c);

	return strCopy;
}

string StringUtils::toLowerCase(const string& str)
{
	string strCopy = string(str);

	for (auto& c : strCopy) c = tolower(c);

	return strCopy;
}

string StringUtils::trim(string& str) {
	const char* typeOfWhitespaces = " \t\n\r\f\v";
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
	str.erase(0, str.find_first_not_of(typeOfWhitespaces));
	return str;
}

vector<string> StringUtils::tokenize(string const& str, const char delim, bool trimmed)
{
	vector<string> out;
	std::stringstream ss(str);

	std::string s;
	while (std::getline(ss, s, delim)) {
		if (trimmed)
			s = StringUtils::trim(s);

		if (!s.empty())
			out.push_back(s);
	}

	return out;
}

double StringUtils::toDouble(const string source)
{
	string s = source;

	StringUtils::replaceAll(s, ".", "");
	StringUtils::replaceAll(s, ",", ".");

	return atof(s.c_str());
}

int StringUtils::toInt(const string source)
{
	string s = source;

	StringUtils::replaceAll(s, ".", "");
	StringUtils::replaceAll(s, ",", ".");

	return atoi(s.c_str());
}

struct tm StringUtils::toTime(const string& source, int hora)
{
	struct tm tm;
	time_t rawtime;
	time(&rawtime);

	auto tokens = tokenize(source, '/', true);

	if (tokens.size() != 3)
		throw string("Data inválida");

	int day = toInt(tokens.at(0));
	int month = toInt(tokens.at(1));
	int year = toInt(tokens.at(2));

	tm = *localtime(&rawtime);
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hora;
	tm.tm_min = 0;
	tm.tm_sec = 0;

	if(tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mday < 0)
		throw string("Data inválida");

	//mktime(&tm);

	return tm;
}