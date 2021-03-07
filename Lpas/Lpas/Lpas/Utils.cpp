#include "Utils.h"

#include <iostream>
#include <sstream>

#include <filesystem>

namespace fs = std::filesystem;


bool Utils::endsWith(const string& str, const string& sufix)
{
	if (str.size() >= sufix.size() &&
		str.compare(str.size() - sufix.size(), sufix.size(), sufix) == 0)
		return true;

	return false;
}

bool Utils::startsWith(const string& str, const string& prefix)
{
	return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

string Utils::basename(const string& pathname)
{
	return { std::find_if(pathname.rbegin(), pathname.rend(),
						 [](char c) { return c == '/'; }).base(),
			pathname.end() };
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

vector<string>Utils::tokenize(std::string const& str, const char delim, bool eraseWhiteSpaces)
{
	vector<string> out;
	std::stringstream ss(str);

	std::string s;
	while (std::getline(ss, s, delim)) {
		if (eraseWhiteSpaces)
			s.erase(remove(s.begin(), s.end(), ' '), s.end());

		if (!s.empty())
			out.push_back(s);
	}

	return out;
}

string Utils::trim(string& str)
{
	str.erase(0, str.find_first_not_of(' '));//prefixing spaces
	str.erase(str.find_last_not_of(' ') + 1);//sufixing spaces
	return str;
}
