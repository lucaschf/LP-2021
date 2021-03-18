#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <sstream>

#include "CharSequence.h"

using namespace std;

class StringUtils {
public:

	template <typename T>
	static string toStringWithPrecision(const T a_value, const int n = 2)
	{
		ostringstream out;

		out.precision(n);
		out << std::fixed << a_value;

		return out.str();
	}

	/**
	 * Tests if this string ends with the specified suffix ignoring the case.
	 *
	 * @param str the string to be tested.
	 * @param suffix the suffix to be tested.
	 * @return true if ends with the suffix, false otherwise.
	 */
	static bool endsWithIgnoreCase(string const& str, string const& suffix);

	/**
	 * Tests if this string ends with the specified suffix.
	 *
	 * @param str the string to be tested.
	 * @param suffix the suffix to be tested.
	 * @return true if ends with the suffix, false otherwise.
	 */
	static bool endsWith(string const& str, string const& suffix);

	/**
	 * Tests if this string starts with the specified prefix.

	 * @param str the string to be tested.
	 * @param prefix the prefix to be tested.
	 * @return true if starts with the prefix, false otherwise.
	 */
	static bool startsWith(string const& str, string const& prefix);

	/**
	 * Tests if the string contains the specified sequence of char values.
	 *
	 * @param str the string to be tested.
	 * @param s the search string.
	 * @return true if contains, false otherwise.
	 */
	static bool contains(string const& str, const string& s);

	/**
	* Tests if the string contains the specified sequence of char values ignoring case considerations.
	*
	* @param str the string to be tested.
	* @param s the search string.
	* @return true if contains, false otherwise.
	*/
	static bool containsIgnoreCase(string const& str, const string& s);

	/**
	* Compares two string, ignoring case considerations.
	*
	* @param str the string to be tested.
	* @param s the search string.
	* @return true if contains, false otherwise.
	*/
	static bool equalsIgnoreCase(string const& str, string const& s);

	/**
	 * Tests if the string is formed only by numbers.
	 *
	 * @param str the string to be tested
	 * @return true if has only numbers, false otherwise.
	 */
	static bool isOnlyDigit(const string& str);

	/**
	 * Replaces all occurrences of target in this string with replacement.
	 *
	 * @param source the string to be changed.
	 * @param target the sequence to be replaced.
	 * @param replacement the new value of the sequence.
	 * @return the new string.
	 */
	static string& replaceAll(string& source, const string& target, const string& replacement);

	/**
	 * Retrieves a uppercase version of the string.
	 *
	 * @param str the string to be converted.
	 * @return the converted string;
	 */
	static string toUpperCase(const string& str);

	/**
	* Retrieves a lowercase version of the string.
	*
	* @param str the string to be converted.
	* @return the converted string;
	*/
	static string toLowerCase(const string& str);

	/**
	* Retrieves a capitalized version of the string.
	*
	* @param str the string to be converted.
	* @return the converted string;
	*/
	static string capitalize(const string& str);

	/**
	* Retrieves a full capitalized version of the string.
	*
	* @param str the string to be converted.
	* @return the converted string;
	*/
	static string capitalizeWords(const string& str);

	/**
	 * Copies a c ++ string to a c string of predefined length.
	 *
	 * @param source
	 * @param destination
	 * @return 1 if success 0 otherwise.
	 */
	static int toCharSequence(const string& source, CharSequence destination);

	// removes the leading and trailing spaces in a string and returns it
	static string trim(string& str);
};

#endif //STRING_UTILS_H