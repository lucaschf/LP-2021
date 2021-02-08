#include "Pixel.h"
#include <iostream>


void runTests() {

	Pixel pixel = Pixel();

	pixel.setX(3);
	pixel.setY(4);

	Pixel pixel2 = Pixel(10, 8);

	cout << "Pixel 1: " << pixel.toString() << endl;
	cout << "Pixel 2: " << pixel2.toString();
}

int main() {

	runTests();
	return 0;
}
