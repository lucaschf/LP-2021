#include<iomanip>
#include <iostream>
#include <Windows.h>

using namespace std;

void display(int asciiPage) {
	const int leftBorder = 128;
	const int rightBorder = 255;
	const int step = 20;


	cout << ">> Código ASCII: página de código " << asciiPage; 

	cout << (asciiPage == 850 ? " - Multilingual Latin 1; Western European (DOS)" : " - ANSI Latin 1; Western European (Windows)") 
		<< endl 
		<< endl;



	SetConsoleOutputCP(asciiPage);
	SetConsoleCP(asciiPage);
	
	for (int i = leftBorder; i < leftBorder + step; i++) {
		for (int row = i; row <= rightBorder; row += step) {
			cout << row << " = " << char(row) << setw(5) << " ";
		}

		cout << endl;
	}

	cout << endl;

}

int main()
{
	display(850);
	display(1252);

	return 0;
}