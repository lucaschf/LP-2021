#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {

public:

	Product();
	
	Product(string name, int quantity, double price);
	
	void setName(string name);
	
	void setQuantity(int quantity);
	
	void setPrice(double price);

	string getName();

	int getQuantity();
	
	double getPrice();

	double getPriceForQuantity();

	string toString();

private:

	string name;
	int quantity;
	double price;
};
#endif