#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils
{
public:

	static bool endsWith(const string& str, const string& sufix);

	static bool startsWith(const string& str, const string& prefix);

	static string basename(const string& pathname);

	/*
	* Get File Name from a Path with or without extension
	*/
	static string getFileName(const string& filePath, bool withExtension = true);

	static string addExtensionAsNeeded(const string& filePath, const string& extension);

	static bool isInteger(string str);

	static vector<string> tokenize(string const& str, const char delim, bool eraseWhiteSpaces);

	static string trim(string& str);
};
#endif // !UTILS_H
