#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>
#include <sstream>

#include <time.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include<time.h>

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
	
	template <typename T>
	static string toBrazilianCurrency(const T a_value)
	{
		return "R$ " + toStringWithPrecision(a_value);
	}
	
	template <typename T>
	static string toPercentageString(const T a_value)
	{
		return toStringWithPrecision(a_value) + "%";
	}
	
	static inline string toRow(string first, string second, int width = 30)
	{
		ostringstream out;

		out << setw(width) << left << first;
		out << setw(width) << left << second;

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

	// removes the leading and trailing spaces in a string and returns it
	static string trim(string& str);

	// split a string into a vector based on a delimiter.
	static vector<string> tokenize(string const& str, const char delim, bool trimmed);

	/**
	 * Retrieves the double value contained in the string.
	 *
	 * @param source the string containing the value.
	 * @return the parsed value.
	 */
	static double toDouble(const string source);

	/**
	 * Retrieves the float value contained in the string.
	 *
	 * @param source the string containing the value.
	 * @return the parsed value.
	 */
	static float toFloat(const string source);


	/**
	  * Retrieves the int value contained in the string.
	 *
	 * @param source the string containing the value.
	 * @return the parsed value.
	 */
	static int toInt(const string source);

	static struct tm toTime(const string& source);
};

#endif //STRING_UTILS_H