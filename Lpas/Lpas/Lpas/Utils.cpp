#include "Utils.h"

#include <iostream>
#include <sstream>

#include <filesystem>

namespace fs = std::filesystem;

bool Utils::endsWith(const string& str, const string& suffix)
{
	if (str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0)
		return true;

	return false;
}

bool Utils::startsWith(const string& str, const string& prefix)
{
	return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

string Utils::getFileName(const string& filePath, bool withExtension)
{
	fs::path pathObj(filePath);

	if (withExtension)
		return pathObj.filename().string();

	if (pathObj.has_stem())
	{
		return pathObj.stem().string();
	}

	return "";
}

string Utils::addExtensionAsNeeded(const string& filePath, const string& extension)
{
	auto targetExtension = extension;

	if (!Utils::startsWith(extension, "."))
		targetExtension = "." + extension;

	if (Utils::endsWith(filePath, targetExtension))
		return filePath;

	return filePath + targetExtension;
}

bool Utils::isInteger(string str)
{
	try {
		std::stoi(str);
		return true;
	}
	catch (...) {
		return false;
	}
}

vector<string>Utils::tokenize(std::string const& str, const char delim, bool trimmed)
{
	vector<string> out;
	std::stringstream ss(str);

	std::string s;
	while (std::getline(ss, s, delim)) {
		if (trimmed)
			s = trim(s);

		if (!s.empty())
			out.push_back(s);
	}

	return out;
}

string Utils::trim(string& str)
{
	const char* typeOfWhitespaces = " \t\n\r\f\v";
	str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
	str.erase(0, str.find_first_not_of(typeOfWhitespaces));
	return str;
}

bool Utils::isUppercase(const string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!isupper(str[i]))
		{
			return false;
		}
	}

	return true;
}

bool Utils::contains(string const str, string const s) {
	return str.find(s) != string::npos;
}
