#include "ProductList.h"
#include <iostream>

using namespace std;

void search(ProductList& list) {
	string name;

	cout << "\nName: ";
	cin >> name;

	auto p = list.fetch(name);

	cout << p.toString();
}

Product readProduct() {
	string name;
	double price;
	int quantity;

	cout << "name: ";
	cin >> name;

	cout << "Price: ";
	cin >> price;

	cout << "Quantity: ";
	cin >> quantity;

	return Product(name, quantity, price);
}

void menu() {

	ProductList list = ProductList();
	Product product;

	int choosen;

	do {
		cout << "Choose an option: \n\n1 - Add a product at start\n2 - Add a product at end";
		cout << "\n3 - Remove at start \n4 - Remove at end\n5 - Search\n6 - Show products\n7 - Count items\n8 - Exit: ";

		cin >> choosen;
		cout << endl;

		switch (choosen)
		{
		case 1:
			list.insertAtStart(readProduct());
			break;
		case 2:
			list.insertAtEnd(readProduct());
			break;
		case 3:
			list.removeAtStart(product);
			list.show();
			break;
		case 4:
			list.removeAtEnd(product);
			list.show();
			break;
		case 5:
			search(list);
			break;
		case 6:
			list.show();
			break;
		case 7:
			cout << list.size() << " products in list\n";
			break;
		default:
			break;
		}

	} while (choosen != 8);
}


int main() {
	menu();

	return 0;
}