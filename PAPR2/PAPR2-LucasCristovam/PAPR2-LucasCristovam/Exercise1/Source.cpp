#include <iostream>
#include <bitset>

using namespace std;

int main(void)
{
	int hexadecimal;

	cout << "Enter a hexadecimal value: ";
	cin >> hex >> hexadecimal;

	bitset<16> binary(hexadecimal);
	cout << "Binary: " << binary << endl;

	return (0);
}