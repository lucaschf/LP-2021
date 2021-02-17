#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include <vector>
#include "Product.h"

class ProductList
{
public:

	void insertAtStart(const Product& product);

	void insertAtEnd(const Product& product);

	bool removeAtStart(Product& product);

	bool removeAtEnd(Product& product);

	Product& fetch(string name);

	bool isEmpty();

	bool show();

	int size();

private:

	vector<Product> items;

};

#endif