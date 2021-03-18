#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

class Utils
{
public:

	/*
	* Get File Name from a Path with or without extension
	*/
	static string getFileName(const string& filePath, bool withExtension = true);

	// split a string into a vector based on a delimiter.
	static vector<string> tokenize(string const& str, const char delim, bool trimmed);

	/**
	 * Check if there is a directory with a certain path.
	 *
	 * @param path the path to be checked.
	 * @return true if exists, false otherwise.
	 */
	static bool exists(const string& path);

	/**
	* Retrieve a listing of all directory files
	*
	* @param path the absolute path of the directory.
	* @param files The reference of a variable where the record will be stored.
	* @param extension the extension to be listed.
	* @return the number files of the directory.
	*/
	static int getAllFiles(const string& path, vector<string>& files, const string& extension, bool namesOnly = true);
};
#endif // !UTILS_H
