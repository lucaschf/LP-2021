#pragma once
#include <string>

using namespace std;

class Pixel
{
private:
	double x;
	double y;

public:
	Pixel();

	Pixel(double x, double y);

	void setX(double x);
	double getX();

	void setY(double y);
	double getY();

	string toString();
};