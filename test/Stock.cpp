#include "Stock.h"

Stock::Stock()
{
	storage = vector<Product>(0);
	productCount = 0;
}

Stock::Stock(int capacity)
{
	storage = vector<Product>(capacity);
	productCount = 0;
}

void Stock::addProduct(Product p)
{
	productCount++;
	storage.emplace_back(p);
}

Product& Stock::getProduct(int position)
{
	return storage[position];
}

int Stock::fetchProductPosition(string name)
{
	for (unsigned int i = 0; i < storage.size(); i++) {
		if (storage[i].getName() == name)
			return i;
	}

	return -1;
}

bool Stock::removeProduct(int position)
{
	if (!isValidPostion(position))
		return false;

	storage.erase(storage.begin() + position);
	productCount--;
	
	return true;
}

double Stock::getTotalValue()
{
	double total = 0;

	for (auto p : storage) {
		total += p.getPriceForQuantity();
	}

	return total;
}

int Stock::getProductCount()
{
	return productCount;
}

int Stock::countItemsInStock()
{
	int count = 0;

	for (auto p : storage)
		count += p.getQuantity();

	return count;
}

bool Stock::isValidPostion(int position)
{
	return position >= 0 && position < static_cast<int>(storage.size());
}
