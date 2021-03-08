#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils
{
public:

	// Tests if this string ends with the specified suffix.
	static bool endsWith(const string& str, const string& sufix);

	// Tests if this string starts with the specified prefix.
	static bool startsWith(const string& str, const string& prefix);

	/*
	* Get File Name from a Path with or without extension
	*/
	static string getFileName(const string& filePath, bool withExtension = true);

	// checks if the filepath contains the informed extension. If not adds to it
	static string addExtensionAsNeeded(const string& filePath, const string& extension);

	// Tests if a string can be parsed to int
	static bool isInteger(string str);

	// split a string into a vector based on a delimiter.
	static vector<string> tokenize(string const& str, const char delim, bool trimmed);

	// removes the leading and trailing spaces in a string and returns it
	static string trim(string& str);

	// tests if a string is formed by only uppercase chars
	static bool isUppercase(const string& str);

	// tests if a string contains another
	static bool contains(string const str, string const s);
};
#endif // !UTILS_H
