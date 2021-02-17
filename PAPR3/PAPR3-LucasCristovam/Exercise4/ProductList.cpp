#include "ProductList.h"
#include <iostream>
#include <iomanip>

void ProductList::insertAtStart(const Product& product)
{
	items.insert(items.begin(), product);
}

void ProductList::insertAtEnd(const Product& product)
{
	items.emplace_back(product);
}

bool ProductList::removeAtStart(Product& product)
{
	if (isEmpty())
		return false;

	product = items.front();
	items.erase(items.begin());

	return true;
}

bool ProductList::removeAtEnd(Product& product)
{
	if (isEmpty())
		return false;

	product = items.back();
	items.pop_back();
	return true;
}

Product& ProductList::fetch(string name)
{
	auto it = find_if(
		items.begin(),
		items.end(),
		[&](Product& p) {return p.getName() == name; });

	return *it._Unwrapped();
}

bool ProductList::isEmpty()
{
	return items.empty();
}

bool ProductList::show()
{
	if (isEmpty())
		return false;

	cout << setw(21) << left << "Product"
		<< setw(21) << left << "Quantity"
		<< setw(21) << left << "Unitary price"
		<< setw(21) << left << "Total value" << endl;

	for (auto p : items) {
		auto price = "R$ " + to_string(p.getPriceForQuantity());

		cout << setw(21) << left << p.getName()
			<< setw(21) << left << p.getQuantity()
			<< setw(21) << left << p.getPrice()
			<< setw(21) << left << price << endl;
	}

	return true;
}

int ProductList::size()
{
	return items.size();
}
