#include "Utils.h"

#include <iostream>
#include <sstream>

#include <filesystem>
#include "StringUtils.h"

namespace fs = std::filesystem;

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

vector<string>Utils::tokenize(std::string const& str, const char delim, bool trimmed)
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

bool Utils::exists(const string& path)
{
	return fs::exists(path);
}

int Utils::getAllFiles(const string& path, vector<string>& files, const string& extension, bool namesOnly, bool withExtension)
{
	int counter = 0;

	if (exists(path)) {
		for (const auto& entry : fs::directory_iterator(path)) {
			string s = entry.path().u8string();

			if (s.length() < path.length()) // pottentialy a parent folder
				continue;

			if (entry.is_directory()) {
				counter += getAllFiles(s, files, extension, namesOnly, withExtension);
				continue;
			}

			if (StringUtils::endsWithIgnoreCase(s, extension))
			{
				if (namesOnly) {
					s = getFileName(s, withExtension);

					if (findInVector<string>(files, s).first) // there is already a file with this name
						continue;
				}

				files.emplace_back(s);
				counter++;
			}
		}
	}

	return counter;
}


