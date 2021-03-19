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
	static int getAllFiles(const string& path, vector<string>& files, const string& extension, bool namesOnly = true, bool withExtension = true);


	/*
	* Generic function to find an element in vector and also its position.
	* @return  a pair of bool & int. bool : Represents if element is present in vector or not.
	* int : Represents the index of element in vector if its found else -1
	*/
	template < typename T>
	static inline std::pair<bool, int> findInVector(const std::vector<T>& vecOfElements, const T& element)
	{
		std::pair<bool, int > result;
		// Find given element in vector
		auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
		if (it != vecOfElements.end())
		{
			result.second = distance(vecOfElements.begin(), it);
			result.first = true;
		}
		else
		{
			result.first = false;
			result.second = -1;
		}

		return result;
	}
};
#endif // !UTILS_H
