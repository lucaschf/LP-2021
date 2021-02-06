#include "Pixel.h"

Pixel::Pixel()
{
	x = 0;
	y = 0;
}

Pixel::Pixel(double x, double y)
{
	setX(x);
	setY(y);
}

void Pixel::setX(double x)
{
	this->x = x;
}

double Pixel::getX()
{
	return this->x;
}

void Pixel::setY(double y)
{
	this->y = y;
}

double Pixel::getY()
{
	return this->y;
}

string Pixel::toString()
{
	return "P(" + to_string(x) + ", " + to_string(y) + ")";
}
