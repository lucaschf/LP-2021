#include "StringUtils.h"
#include <iostream>
#include <algorithm>
#include <cstring>

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

string StringUtils::capitalize(const string& str)
{
	if (str.empty())
		return str;

	string s = toLowerCase(str);
	s[0] = toupper(s[0]);

	return s;
}

string StringUtils::capitalizeWords(const string& str)
{
	if (str.empty())
		return str;

	string s = capitalize(str);
	for (unsigned int i = 1; i < s.size(); i++)
	{
		if (s[i - 1] == ' ')
			s[i] = toupper(s[i]);
	}

	return s;
}

int StringUtils::toCharSequence(const string& source, CharSequence destination)
{
	return strncpy_s(destination, SEQUENCE_LENGHT, source.c_str(), source.length());
}

string StringUtils::trim(string& str){
	const char* typeOfWhitespaces = " \t\n\r\f\v";
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
	str.erase(0, str.find_first_not_of(typeOfWhitespaces));
	return str;
}